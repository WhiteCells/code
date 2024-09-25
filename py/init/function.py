"""
function
"""

def f1(
    x: int, 
    y: int
) -> int:
    """
    :param x: b
    :param y: a
    :return: a + b
    """
    print(x, y)
    return x + y


print(f1) # f ptr
print(type(f1)) # function
print(f1(1, 2))
print(f1(1.1, 2.2))
print(f1(1.1, 2.2))
print(f1(1.1, 2.2))

def f2() -> None:
    return 1

print(f2())

# 多返回值
def f2():
    return 1, "2", 3.3

x, y, z = f2()
print(x, y, z)

# 传参
def f3(str1: str, length: int):
    return str1 + str(length)

print(f3("string", 6))
# print(f3(6, "string")) # error
print(f3(str1="string", length=6))
print(f3(length=6, str1="string"))

# 缺省
def f4(length: int, str1="string"):
    return str1 + str(length)

print(f4(1)) # string1
print(f4(2, "str")) # str2

# 不定长
def f5(*arg):
    print(*arg)
    print(type(arg))
    for ele in arg:
        print(ele)
    print(arg[0])
    print(arg[1])
    print(arg[2])
    print(arg[3])
    # print(arg[4]) # error

f5(1, 2, 3, "123")


# 函数作为参数
from typing import Callable

def f6(func: Callable, *args):
    func(*args)

def foo(*args):
    print(*args)

f6(foo, 1, 2.2, "3.3")

# lambda
print("===")
f6(lambda *args: print(*args), 1, 2.2, "3.3")


# 位置传参
def f7(a, b, c):
    print(a, b, c)

f7(1, 2, 3)


# 关键字传参，位置参数必须在关键字参数之前
f7(1, c=2, b=3)


# 缺省参数
def f8(m, n='aaa'):
    print(m, n)
    

f8(1)
f8(1, 'bbb')


# 位置不定长
def f9(*args):
    print(args)

f9(1, 2.2,'123') # tuple


# 关键字不定长
def f10(**kwargs):
    print(kwargs)

f10(a=1, b=2.2, c='123') # dict


a = 10

def f():
    # a = 20
    global a
    a = 20
    
f()
print(a)

