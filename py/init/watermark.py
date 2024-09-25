import os
from PIL import Image, ImageDraw, ImageFont

def add_watermark(input_image_path, output_image_path, watermark_text, font_path, font_size, color):
    image = Image.open(input_image_path).convert("RGBA")  # 确保图像为 RGBA 模式

    # 创建一个与原图大小相同的透明图层
    txt_layer = Image.new("RGBA", image.size, (255, 255, 255, 0))

    # 加载字体
    font = ImageFont.truetype(font_path, font_size)

    # 初始化绘图对象
    draw = ImageDraw.Draw(txt_layer)

    # 计算水印文字的边界框
    text_bbox = draw.textbbox((0, 0), watermark_text, font=font)
    text_width = text_bbox[2] - text_bbox[0]
    text_height = text_bbox[3] - text_bbox[1]

    # 计算水印位置 (右下角)
    width, height = image.size
    position = (width - text_width - 30, height - text_height - 30)

    # 添加水印（设置成指定颜色和透明度）
    draw.text(position, watermark_text, font=font, fill=color)  # 使用指定的颜色

    # 合并图像
    watermarked_image = Image.alpha_composite(image, txt_layer)

    # 保存结果
    watermarked_image.convert("RGB").save(output_image_path, "JPEG")

def process_images(input_dir, output_dir, watermark_text, font_path, font_size, color, text_file_path):
    if not os.path.exists(output_dir):
        os.makedirs(output_dir)

    # 获取所有图片文件，并根据文件名中的数字进行排序
    files = [f for f in os.listdir(input_dir) if f.lower().endswith(('.png', '.jpg', '.jpeg'))]
    
    # 排序函数：提取文件名中的数字部分进行排序
    def extract_number(filename):
        base_name = os.path.splitext(filename)[0]  # 去掉扩展名
        try:
            return int(base_name)
        except ValueError:
            return float('inf')  # 非数字文件排到最后

    sorted_files = sorted(files, key=extract_number)

    # 读取文本文件中的内容
    with open(text_file_path, 'r', encoding='utf-8') as f:
        lines = f.readlines()

    # 遍历排序后的文件
    for i, filename in enumerate(sorted_files):
        if i >= len(lines):  # 如果文本文件中的行数不足，剩下的文件不处理
            print(f"Warning: Not enough lines in text file for remaining images.")
            break

        input_image_path = os.path.join(input_dir, filename)
        output_image_path = os.path.join(output_dir, filename)
        date_text = lines[i].strip()  # 获取文件中的一行，去掉前后的空白字符

        add_watermark(input_image_path, output_image_path, watermark_text + date_text, font_path, font_size, color)
        print(f"Processed: {filename}")

# 获取用户输入
input_directory = "/home/cells/下载/img"      # 输入图片的目录
output_directory = "/home/cells/下载/out"     # 输出图片的目录
watermark = "喜洋洋生鲜超市 2024/"              # 水印文本
font_path = "/usr/share/fonts/msyh.ttc"      # 字体路径
font_size = 120                              # 修改水印字体大小
color = (255, 0, 0, 128)  # 半透明红色水印
text_file_path = "/home/cells/下载/times.txt"  # 文本文件路径

# 批量处理
process_images(input_directory, output_directory, watermark, font_path, font_size, color, text_file_path)