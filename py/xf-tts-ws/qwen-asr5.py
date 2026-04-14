import os
import time
import json
import threading
import base64
import websocket
import logging
import logging.handlers
from datetime import datetime
import pyaudio

# --- 配置区 ---
API_KEY = os.environ.get("DASHSCOPE_API_KEY", "sk-7c5db26726694a1eb4525f9ac173392d")
QWEN_MODEL = "qwen3-asr-flash-realtime-2026-02-10"
BASE_URL = "wss://dashscope.aliyuncs.com/api-ws/v1/realtime"
URL = f"{BASE_URL}?model={QWEN_MODEL}"

# 模式设置
ENABLE_SERVER_VAD = True  # 是否开启服务端语音活动检测
USE_MICROPHONE = True    # True: 麦克风录音, False: 读取本地PCM文件
LOCAL_AUDIO_PATH = "test.pcm" # 如果 USE_MICROPHONE 为 False，则读取此文件

# 音频参数 (16k, 16bit, 单声道)
FORMAT = pyaudio.paInt16
CHANNELS = 1
RATE = 16000
CHUNK_MS = 100 # 每次发送100ms的数据
CHUNK_SIZE = int(RATE * CHANNELS * (CHUNK_MS / 1000) * 2) # 2 是因为 paInt16 占 2 字节

logger = logging.getLogger(__name__)

def init_logger():
    logger.setLevel(logging.DEBUG)
    formatter = logging.Formatter('%(asctime)s|%(levelname)s|%(message)s')
    
    # 文件日志
    f_handler = logging.handlers.RotatingFileHandler(
        "omni_tester.log", maxBytes=10 * 1024 * 1024, backupCount=3
    )
    f_handler.setFormatter(formatter)
    
    # 控制台日志
    console = logging.StreamHandler()
    console.setFormatter(formatter)
    
    logger.addHandler(f_handler)
    logger.addHandler(console)

class RealtimeASRClient:
    def __init__(self):
        self.ws = None
        self.is_running = False
        self.p = pyaudio.PyAudio()

    def on_open(self, ws):
        logger.info("--- 建立连接成功 ---")
        # 构造会话配置
        session_config = {
            "type": "session.update",
            "session": {
                "modalities": ["text"],
                "input_audio_format": "pcm",
                "sample_rate": RATE,
                "input_audio_transcription": {"language": "zh"},
                "turn_detection": {
                    "type": "server_vad",
                    "threshold": 0.5,
                    "silence_duration_ms": 500
                } if ENABLE_SERVER_VAD else None
            }
        }
        ws.send(json.dumps(session_config))
        logger.info(f"已发送 Session Update: {json.dumps(session_config)}")
        self.is_running = True

    def on_message(self, ws, message):
        data = json.loads(message)
        msg_type = data.get("type")
        print("message type:", msg_type)

        # 实时识别结果通常在 response.audio_transcription.delta 或类似事件中
        # 阿里云 Realtime 模型会返回多种事件，以下为核心逻辑
        if msg_type == "input_audio_buffer.speech_started":
            print("\n[检测到说话...]", end="", flush=True)
        
        elif msg_type == "conversation.item.input_audio_transcription.completed":
            transcript = data.get("transcript", "")
            print(f"\n最终识别结果: {transcript}")
            
        elif msg_type == "conversation.item.input_audio_transcription.delta":
            delta = data.get("delta", "")
            print(delta, end="", flush=True) # 实时流式打印

        elif msg_type == "error":
            logger.error(f"服务器报错: {data}")

    def on_error(self, ws, error):
        logger.error(f"WebSocket 错误: {error}")

    def on_close(self, ws, code, msg):
        logger.info(f"### 连接关闭: {code} - {msg} ###")
        self.is_running = False

    def send_audio_loop(self):
        """发送音频的逻辑"""
        while not self.is_running:
            time.sleep(0.1)
        
        try:
            if USE_MICROPHONE:
                self._stream_from_mic()
            else:
                self._stream_from_file()
        except Exception as e:
            logger.error(f"发送音频时出错: {e}")
        finally:
            self.stop()

    def _stream_from_mic(self):
        logger.info("开始麦克风实时录音...")
        stream = self.p.open(format=FORMAT, channels=CHANNELS, rate=RATE, 
                             input=True, frames_per_buffer=int(RATE/10))
        
        while self.is_running:
            audio_data = stream.read(int(RATE * CHUNK_MS / 1000), exception_on_overflow=False)
            # print(audio_data)
            self._send_payload(audio_data)
        
        stream.stop_stream()
        stream.close()

    def _stream_from_file(self):
        if not os.path.exists(LOCAL_AUDIO_PATH):
            logger.error(f"文件不存在: {LOCAL_AUDIO_PATH}")
            return

        logger.info(f"开始读取文件: {LOCAL_AUDIO_PATH}")
        with open(LOCAL_AUDIO_PATH, 'rb') as f:
            while self.is_running:
                audio_data = f.read(CHUNK_SIZE)
                if not audio_data:
                    break
                self._send_payload(audio_data)
                time.sleep(CHUNK_MS / 1000) # 模拟真实语速
        
        # 文件结束后，如果是非VAD模式，需要手动commit
        if not ENABLE_SERVER_VAD:
            self.ws.send(json.dumps({"type": "input_audio_buffer.commit"}))
        logger.info("文件发送完毕。")

    def _send_payload(self, audio_data):
        base64_audio = base64.b64encode(audio_data).decode('ascii')
        payload = {
            "type": "input_audio_buffer.append",
            "audio": base64_audio
        }
        self.ws.send(json.dumps(payload))

    def stop(self):
        self.is_running = False
        if self.ws:
            self.ws.close()
        self.p.terminate()

    def run(self):
        headers = [f"Authorization: Bearer {API_KEY}", "OpenAI-Beta: realtime=v1"]
        self.ws = websocket.WebSocketApp(
            URL,
            header=headers,
            on_open=self.on_open,
            on_message=self.on_message,
            on_error=self.on_error,
            on_close=self.on_close
        )
        
        # 启动发送线程
        send_thread = threading.Thread(target=self.send_audio_loop)
        send_thread.daemon = True
        send_thread.start()
        
        # 运行 WS (阻塞主线程)
        self.ws.run_forever()

if __name__ == "__main__":
    init_logger()
    client = RealtimeASRClient()
    try:
        client.run()
    except KeyboardInterrupt:
        client.stop()