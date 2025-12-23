import wave
import os


def get_input(prompt, default=None, type_func=int):
    while True:
        value = input(
            f"{prompt} [{'默认: ' + str(default) if default is not None else '必填'}]: "
        ).strip()
        if value == "":
            if default is not None:
                return default
            else:
                print("输入不能为空，请重新输入。")
                continue
        try:
            return type_func(value)
        except ValueError:
            print("输入格式不正确，请重新输入。")


def pcm_to_wav(pcm_path, wav_path, channels, sample_width, sample_rate):
    try:
        pcm_size = os.path.getsize(pcm_path)
        print(f"PCM 文件大小：{pcm_size} 字节")
    except FileNotFoundError:
        print("PCM 文件不存在。")
        return False

    print(f"声道数：{channels}")
    print(f"采样位宽：{sample_width} 字节")
    print(f"采样率：{sample_rate} Hz")

    if sample_width not in [1, 2, 4]:
        print("不支持的 sample_width（位深）。必须是 1、2、4 字节。")
        return False

    with open(pcm_path, "rb") as pcm_file:
        pcm_data = pcm_file.read()

    wav_file = wave.open(wav_path, "wb")
    wav_file.setnchannels(channels)
    wav_file.setsampwidth(sample_width)
    wav_file.setframerate(sample_rate)

    wav_file.writeframes(pcm_data)
    wav_file.close()

    print(f"WAV 文件已保存到：{wav_path}")
    return True


def main():
    while True:
        pcm_path = input("请输入 PCM 文件路径：").strip()
        if os.path.isfile(pcm_path):
            break
        else:
            print("文件不存在，请重新输入。\n")

    default_wav = pcm_path.rsplit(".", 1)[0] + ".wav"
    wav_path = input(f"请输入输出 WAV 文件路径 [默认: {default_wav}]: ").strip()
    if wav_path == "":
        wav_path = default_wav

    print("输入 PCM 参数:\n")

    channels = get_input("声道数 (1=单声道, 2=双声道), 默认 1", default=1)
    sample_width = get_input(
        "采样位宽（字节）(1=8bit, 2=16bit, 4=32bit), 默认 2", default=2
    )
    sample_rate = get_input("采样率 (如 16000, 44100), 默认 16000", default=16000)

    pcm_to_wav(pcm_path, wav_path, channels, sample_width, sample_rate)


if __name__ == "__main__":
    main()
