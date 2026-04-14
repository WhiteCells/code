import requests


def create_custom_voice(audio_sample_path: str, consent: str, name: str, ref_text: str, base_url: str = "http://172.16.20.231:8000/v1"):
    """
    创建自定义语音

    Args:
        audio_sample_path: 音频样本文件路径
        consent: 用户同意标识
        name: 自定义语音名称
        ref_text: 音频样本的转录文本
        base_url: API 基础 URL

    Returns:
        API 响应结果
    """
    url = f"{base_url}/audio/voices"

    with open(audio_sample_path, "rb") as audio_file:
        files = {
            "audio_sample": (audio_sample_path, audio_file, "audio/wav")
        }
        data = {
            "consent": consent,
            "name": name,
            "ref_text": ref_text
        }

        response = requests.post(url, files=files, data=data)
        response.raise_for_status()
        return response.json()


if __name__ == '__main__':
    # audio_sample_path = "转人工.wav"
    audio_sample_path = "1.mp3"
    consent = "user_consent_id_3"
    name = "custom_voice_3"
    ref_text = "哦对，你已经还了一部分是吗，然后没换完，对呀，你这边没有处理完的话，你点一下，你看一下能不能再处理，如果不能的话你可以点app直接处理啊"

    try:
        result = create_custom_voice(audio_sample_path, consent, name, ref_text)
        print("创建自定义语音成功:")
        print(result)
    except requests.exceptions.RequestException as e:
        print(f"请求失败: {e}")
    except FileNotFoundError:
        print(f"音频文件未找到: {audio_sample_path}")

"""
{
    "success": true,
    "voice": {
        "name": "custom_voice_3",
        "consent": "user_consent_id_3",
        "created_at": 1775034572,
        "mime_type": "audio/wav",
        "file_size": 364510,
        "ref_text": "哦对，你已经还了一部分是吗，然后没换完，对呀，你这边没有处理完的话，"
    }
}
"""