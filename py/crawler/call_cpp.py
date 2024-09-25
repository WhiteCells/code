import subprocess


# 编译 C++ 文件
subprocess.run(['g++', 'test.cpp', '-o', 'test'])

# 运行编译的 C++ 程序
result = subprocess.run(['./test'], capture_output=True, text=True)

# 打印 C++ 程序的输出
print(result.stdout)