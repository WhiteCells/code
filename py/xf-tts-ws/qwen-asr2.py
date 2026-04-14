import logging
import os
import base64
import signal
import sys
import time
import pyaudio # 确保已安装: pip install pyaudio
import dashscope
from dashscope.audio.qwen_omni import *
from dashscope.audio.qwen_omni.omni_realtime import TranscriptionParams

# 配置参数（需与接口定义的 transcription_params 匹配）
FORMAT = pyaudio.paInt16
CHANNELS = 1
RATE = 16000
CHUNK = 3200  # 每次读取的采样数，约 200ms 的音频数据

def setup_logging():
    logger = logging.getLogger('dashscope')
    logger.setLevel(logging.INFO) # 实时模式下 INFO 即可，DEBUG 会刷屏
    handler = logging.StreamHandler(sys.stdout)
    formatter = logging.Formatter('%(asctime)s - %(levelname)s - %(message)s')
    handler.setFormatter(formatter)
    logger.addHandler(handler)
    return logger

def init_api_key():
    dashscope.api_key = os.environ.get('DASHSCOPE_API_KEY', 'sk-f81b254a7bc046d0bb41851d8d9d2df1')

class MyCallback(OmniRealtimeCallback):
    def on_open(self):
        print('--- 已建立连接，开始实时录音 ---')

    def on_close(self, code, msg):
        print(f'--- 连接关闭: {code} - {msg} ---')

    def on_event(self, response):
        t = response.get('type')
        if t == 'conversation.item.input_audio_transcription.completed':
            print(f"\n[最终识别]: {response['transcript']}")
        elif t == 'conversation.item.input_audio_transcription.text':
            # 实时滚动输出中间结果
            sys.stdout.write(f"\r[中间过程]: {response['stash']}")
            sys.stdout.flush()

def main():
    setup_logging()
    init_api_key()

    # 初始化 DashScope 会话
    conversation = OmniRealtimeConversation(
        model='qwen3-asr-flash-realtime',
        url='wss://dashscope.aliyuncs.com/api-ws/v1/realtime',
        callback=MyCallback()
    )

    # 初始化 PyAudio
    p = pyaudio.PyAudio()
    stream = p.open(format=FORMAT,
                    channels=CHANNELS,
                    rate=RATE,
                    input=True,
                    frames_per_buffer=CHUNK)

    def handle_exit(sig, frame):
        print('\n正在停止录音...')
        stream.stop_stream()
        stream.close()
        p.terminate()
        conversation.close()
        sys.exit(0)

    signal.signal(signal.SIGINT, handle_exit)

    # 建立 WebSocket 连接
    conversation.connect()

    # 更新会话配置
    conversation.update_session(
        output_modalities=[MultiModality.TEXT],
        enable_input_audio_transcription=True,
        transcription_params=TranscriptionParams(
            language='zh',
            sample_rate=RATE,
            input_audio_format="pcm"
        )
    )

    print(">>> 正在录音中（按 Ctrl+C 结束）...")

    try:
        while True:
            # 从麦克风读取原始字节数据
            data = stream.read(CHUNK, exception_on_overflow=False)
            # print("data:", data)
            # 转为 Base64 并发送
            audio_b64 = base64.b64encode(data).decode('ascii')
            conversation.append_audio(audio_b64)
            
    except Exception as e:
        print(f"\n运行时错误: {e}")
    finally:
        stream.stop_stream()
        stream.close()
        p.terminate()
        conversation.close()

if __name__ == '__main__':
    main()