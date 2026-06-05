import argparse
import os
import shutil
import subprocess
import sys


def build_parser():
    parser = argparse.ArgumentParser(description="将 MP3 文件转换为 WAV 文件")
    parser.add_argument("input", nargs="?", help="输入 MP3 文件路径")
    parser.add_argument("output", nargs="?", help="输出 WAV 文件路径")
    parser.add_argument(
        "-ar",
        "--sample-rate",
        type=int,
        help="输出采样率，例如 16000、44100",
    )
    parser.add_argument(
        "-ac",
        "--channels",
        type=int,
        choices=[1, 2],
        help="输出声道数，1=单声道，2=双声道",
    )
    parser.add_argument(
        "-n",
        "--no-overwrite",
        action="store_true",
        help="如果输出文件已存在，则不覆盖",
    )
    return parser


def prompt_for_file(prompt_text):
    while True:
        file_path = input(prompt_text).strip()
        if os.path.isfile(file_path):
            return file_path
        print("文件不存在，请重新输入。\n")


def prompt_optional_int(prompt_text):
    while True:
        value = input(prompt_text).strip()
        if value == "":
            return None
        try:
            number = int(value)
            if number > 0:
                return number
        except ValueError:
            pass
        print("请输入正整数，或直接回车跳过。\n")


def collect_inputs(args):
    input_path = args.input
    if not input_path:
        input_path = prompt_for_file("请输入 MP3 文件路径：")
    elif not os.path.isfile(input_path):
        print(f"输入文件不存在：{input_path}")
        return None

    output_path = args.output
    if not output_path:
        default_output = os.path.splitext(input_path)[0] + ".wav"
        output_path = input(f"请输入输出 WAV 文件路径 [默认: {default_output}]: ").strip()
        if output_path == "":
            output_path = default_output

    sample_rate = args.sample_rate
    channels = args.channels

    if args.input is None:
        print("可选输出参数，直接回车则保持 ffmpeg 默认设置。\n")
        if sample_rate is None:
            sample_rate = prompt_optional_int("输出采样率（例如 16000、44100，可留空）：")
        if channels is None:
            while True:
                raw_channels = input("输出声道数（1=单声道，2=双声道，可留空）：").strip()
                if raw_channels == "":
                    channels = None
                    break
                if raw_channels in {"1", "2"}:
                    channels = int(raw_channels)
                    break
                print("请输入 1、2，或直接回车跳过。\n")

    return input_path, output_path, sample_rate, channels


def convert_mp3_to_wav(input_path, output_path, sample_rate=None, channels=None, overwrite=True):
    ffmpeg_path = shutil.which("ffmpeg")
    if ffmpeg_path is None:
        print("未找到 ffmpeg，请先安装 ffmpeg 后再运行。")
        return False

    output_dir = os.path.dirname(os.path.abspath(output_path))
    if output_dir and not os.path.exists(output_dir):
        os.makedirs(output_dir, exist_ok=True)

    cmd = [ffmpeg_path, "-v", "error", "-i", input_path]
    if sample_rate is not None:
        cmd.extend(["-ar", str(sample_rate)])
    if channels is not None:
        cmd.extend(["-ac", str(channels)])
    cmd.extend(["-y" if overwrite else "-n", output_path])

    try:
        subprocess.run(cmd, check=True)
    except subprocess.CalledProcessError:
        print("转换失败，请确认输入文件是有效的 MP3，并检查输出路径是否可写。")
        return False

    print(f"WAV 文件已保存到：{output_path}")
    return True


def main():
    parser = build_parser()
    args = parser.parse_args()

    collected = collect_inputs(args)
    if collected is None:
        sys.exit(1)

    input_path, output_path, sample_rate, channels = collected
    success = convert_mp3_to_wav(
        input_path=input_path,
        output_path=output_path,
        sample_rate=sample_rate,
        channels=channels,
        overwrite=not args.no_overwrite,
    )
    sys.exit(0 if success else 1)


if __name__ == "__main__":
    main()
