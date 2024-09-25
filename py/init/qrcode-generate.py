import qrcode

# 数据
# data = "https://example.com"
data = "{\"data\":{\"asd\" : 1}}"

# 创建二维码对象
qr = qrcode.QRCode(
    version=1,  # 控制二维码的大小（1 到 40）
    error_correction=qrcode.constants.ERROR_CORRECT_L,  # 错误纠正级别
    box_size=10,  # 每个“点”的像素大小
    border=4,  # 边框宽度（点）
)

# 添加数据到二维码
qr.add_data(data)
qr.make(fit=True)

# 生成图像
img = qr.make_image(fill='black', back_color='white')

# 将图像转换为 Pillow 的 Image 对象
img = img.convert("RGB")

# 保存图像到文件
img.save("qrcode_example.png")

# 显示图像
img.show()