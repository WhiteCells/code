# file_byte / (sample_rate * (bits_per_sample/8) * channels)
import os
import wave

# 计算 PCM 文件的持续时间
def calculate_pcm_duration(pcm_path, channels, sample_width, sample_rate):
    try:
        pcm_size = os.path.getsize(pcm_path)
        print(f"PCM 文件大小：{pcm_size} 字节")
    except FileNotFoundError:
        print("PCM 文件不存在。")
        return None

    print(f"声道数：{channels}")
    print(f"采样位宽：{sample_width} 字节")
    print(f"采样率：{sample_rate} Hz")

    if sample_width not in [1, 2, 4]:
        print("不支持的 sample_width（位深）。必须是 1、2、4 字节。")
        return None

    bytes_per_second = sample_rate * (sample_width) * channels
    duration_seconds = pcm_size / bytes_per_second
    return duration_seconds

def get_input(prompt, default=None, type_func=str):
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

def main():
    while True:
        pcm_path = input("请输入 PCM 文件路径：").strip()
        if os.path.isfile(pcm_path):
            break
        else:
            print("文件不存在，请重新输入。\n")

    channels = get_input("请输入声道数", default=1, type_func=int)
    sample_width = get_input("请输入采样位宽（字节）", default=2, type_func=int)
    sample_rate = get_input("请输入采样率（Hz）", default=16000, type_func=int)

    duration = calculate_pcm_duration(pcm_path, channels, sample_width, sample_rate)
    if duration is not None:
        print(f"PCM 文件持续时间：{duration:.2f} 秒")

if __name__ == "__main__":
    main()
