from PIL import Image
import numpy as np
import paddlehub as hub
import os
import cv2
import math


# 设置最大图像像素数
Image.MAX_IMAGE_PIXELS = None
os.environ["OPENCV_IO_MAX_IMAGE_PIXELS"] = pow(2, 40).__str__()

# 加载OCR模型
ocr = hub.Module(name="chinese_ocr_db_crnn_server")

# 打开图像
pil_img = Image.open('D:\\py\\crawler\\ocr\\img\\test.png')
width, height = pil_img.size

# 设置窗口和步长大小
window_size = (1024, 1024)
step_size = (512,512)

# 计算滑动次数
num_steps_width = (width - window_size[0]) // step_size[0] + 1 if width > window_size[0] else 1
num_steps_height = (height - window_size[1]) // step_size[1] + 1 if height > window_size[1] else 1

# 计算文本框的中心点
def get_center(text_box):
    x_coords = [point[0] for point in text_box]
    y_coords = [point[1] for point in text_box]
    return [(min(x_coords) + max(x_coords)) / 2, (min(y_coords) + max(y_coords)) / 2]

# 合并逻辑只考虑垂直距离较小的文本框
def merge_text_boxes_by_vertical_distance(text_boxes, vertical_threshold=50):
    merged_boxes = []
    current_box = text_boxes[0]

    for i in range(1, len(text_boxes)):
        prev_center = get_center(current_box['text_box_position'])
        current_center = get_center(text_boxes[i]['text_box_position'])

        # 计算垂直距离
        vertical_distance = abs(prev_center[1] - current_center[1])

        # 如果垂直距离较小，合并文本框
        if vertical_distance < vertical_threshold:
            current_box['text'] += ' ' + text_boxes[i]['text']
            current_box['confidence'] = min(current_box['confidence'], text_boxes[i]['confidence'])
            current_box['text_box_position'] = [
                [min(current_box['text_box_position'][0][0], text_boxes[i]['text_box_position'][0][0]),
                 min(current_box['text_box_position'][0][1], text_boxes[i]['text_box_position'][0][1])],
                [max(current_box['text_box_position'][1][0], text_boxes[i]['text_box_position'][1][0]),
                 max(current_box['text_box_position'][1][1], text_boxes[i]['text_box_position'][1][1])]
            ]
        else:
            merged_boxes.append(current_box)
            current_box = text_boxes[i]

    # 把最后一个文本框加上
    merged_boxes.append(current_box)
    return merged_boxes


# 打开文件以写入识别结果
with open('ocr/res/jx_res.txt', 'a', encoding="utf-8") as f:
    # 遍历每个滑动窗口
    for i in range(num_steps_height):
        for j in range(num_steps_width):
            # 计算当前窗口的坐标
            left = j * step_size[0]
            top = i * step_size[1]
            right = min(left + window_size[0], width)
            bottom = min(top + window_size[1], height)

            # 裁剪当前窗口
            chunk_pil = pil_img.crop((left, top, right, bottom))
            chunk_cv = np.array(chunk_pil)


            if len(chunk_cv.shape) == 3:
                if chunk_cv.shape[2] == 4:
                    chunk_cv = cv2.cvtColor(chunk_cv, cv2.COLOR_RGBA2BGR)
                elif chunk_cv.shape[2] == 3:
                    chunk_cv = chunk_cv[:, :, ::-1]  # RGB to BGR

            # 使用OCR进行识别
            results = ocr.recognize_text(
                images=[chunk_cv],
                use_gpu=False,
                output_dir='ocr/chunk_img',
                visualization=True,
                box_thresh=0.5,
                text_thresh=0.5
            )

            # 处理识别结果
            for result in results:
                data = result['data']
                merge_data = merge_text_boxes_by_vertical_distance(data)  # 使用新的垂直距离合并函数
                for infomation in merge_data:
                    new_text_box_position = [
                        [point[0] + j*step_size[0], point[1] + i*step_size[1]]  # 对每个点的坐标进行修改
                        for point in infomation['text_box_position']
                    ]
                    infomation['text_box_position'] = new_text_box_position
                    print('text:', infomation['text'])
                    print('confidence:', infomation['confidence'])
                    print('text_box_position:', infomation['text_box_position'])
                    f.write('text: ' + str(infomation['text']) + ',confidence: ' + str(
                        infomation['confidence']) + ',text_box_position: ' + str(
                        infomation['text_box_position']) + '\n')

