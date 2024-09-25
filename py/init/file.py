"""
file
"""

# mode
# r: 读取
# w: 写入
# a: 追加，文件不存在就创建

# read
import readline
import time


file = open("./text.txt", "r", encoding="utf-8") 

# # 读当前指针后面的指定长度
# print(file.read(5)) # Hello

# # 读当前指针后面的所有内容
# print(file.read()) # , this is a test file.

# # 读当前指针后面的所有内容，存放至列表
# lines = file.readlines()
# print(lines) # ['Hello, this is a test file.\n', 'append content']

# # 读取当前指针后面的一行内容
# print(file.readline())

# for
for line in file:
    print(line)

line = str()

# time.sleep(100000)
\
# 不关闭文件，进程会占用文件
file.close()

# 自动 f.close()
with open("./text.txt", "r", encoding="utf-8") as f:
    for line in f:
        print(line)

# write
file = open("./text.txt", "w", -1, "utf-8")  # 写入模式，文件不存在则创建
file.write("Hello, this is a test file.")
file.flush() # 刷新缓冲区
file.close()

# append
file = open("./text.txt", "a", -1, "utf-8")
file.write("\nappend content")
file.close()

