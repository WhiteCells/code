import requests
import pyaudio


if __name__ == '__main__':
    base_url = "http://172.16.20.231:8000/v1"
    model = "/data/Qwen3-TTS-12Hz-1.7B-Base"
    voice = "custom_voice_2"
    input_text = "我这边投递的包裹怎么还没有收到确认呢？"

    url = f"{base_url}/audio/speech"
    headers = {"Content-Type": "application/json"}
    payload = {
        "model": model,
        "input": input_text,
        "voice": voice,
        "stream": True,
        "response_format": "pcm"
    }

    # 初始化 PyAudio
    p = pyaudio.PyAudio()
    # 打开音频流: 24kHz, 16bit, 单声道
    stream = p.open(
        format=pyaudio.paInt16,
        channels=1,
        rate=24000,
        output=True
    )

    try:
        print("正在请求 TTS 服务...")
        response = requests.post(url, headers=headers, json=payload, stream=True)
        response.raise_for_status()

        print("开始播放...")
        # 流式读取并播放音频数据
        for chunk in response.iter_content(chunk_size=1024):
            if chunk:
                print("chunk:", len(chunk))
                stream.write(chunk)

        print("播放完成")

    except requests.exceptions.RequestException as e:
        print(f"请求失败: {e}")
    finally:
        # 清理资源
        stream.stop_stream()
        stream.close()
        p.terminate()

