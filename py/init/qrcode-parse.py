from PIL import Image
from pyzbar.pyzbar import decode

# 载入图像
image_path = 'qrcode_example.png'
image = Image.open(image_path)

# 解析二维码
decoded_objects = decode(image)

# 输出解析结果
for obj in decoded_objects:
    print(f"类型: {obj.type}")
    print(f"数据: {obj.data.decode('utf-8')}")