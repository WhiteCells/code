from PIL import Image
import numpy as np
import paddlehub as hub
import os
import cv2

# 设置最大图像像素数
Image.MAX_IMAGE_PIXELS = None
os.environ["OPENCV_IO_MAX_IMAGE_PIXELS"] = pow(2, 40).__str__()

# 加载OCR模型
ocr = hub.Module(name="chinese_ocr_db_crnn_server")

# 打开图像
pil_img = Image.open('D:\map\\tile-merge\\z=16.png')
img_width, img_height = pil_img.size

# 窗口大小
window_width = 1024
window_height = 1024

# 计算整个需要划分的次数
# 向下取整，不足窗口大小的直接融入上一个窗口
division_width_count = img_width // window_width
division_height_count = img_height // window_height

# 先按固定窗口大小遍历整个地图
# 记录找到最长的地址名
# 将 (最长的地址名 * 2) 作为需要额外需要考虑的区域
max_address_name_len = 0

for i in range(division_height_count):
    for j in range(division_width_count):
        left = j * window_width
        top = i * window_height
        right = left + window_width
        bottom = top + window_height
        block_img = pil_img.crop((left, top, right, bottom))
        block_cv = np.array(block_img)

        if len(block_cv.shape) == 3:
            if block_cv.shape[2] == 4:
                block_cv = cv2.cvtColor(block_cv, cv2.COLOR_RGBA2BGR)
            elif block_cv.shape[2] == 3:
                block_cv = block_cv[:, :, ::-1]  # RGB to BGR

        ocr_res = ocr.recognize_text(
            images=[block_cv],
            use_gpu=False,
            output_dir='ocr_res',
            visualization=True,
            box_thresh=0.5,
            text_thresh=0.5
        )

        for res in ocr_res:
            data = res['data']
            for info in data:
                text_box_pos = [
                    [pos[0] + j * ] for pos in info['text_box_position']
                ]


# 考虑可能被切割的部分
# x: 1024 2048 3144
# y: 1024 2048 3144

# left   x - max_addres_name_len
# top    0
# right  x + max_addres_name_len
# bottom img_height

# left   0
# top    y - max_addres_name_len
# right  img_width
# bottom y + max_addres_name_len


