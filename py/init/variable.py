"""
comment
"""

i1 = 1                 # 整数
i2 = 1.1               # 浮点数
i3 = 1 + 4j            # 复数
i4 = True              # 布尔
i5 = "test"            # 字符串
i6 = 'test'            # 字符串
i7 = """testtest"""    # 字符串
i8 = [1, 2]            # 列表
i9 = {1, 2}            # 集合
i10 = {1 : "", 2 : ""} # 字典

print(i7)
print(type(1))                # int
print(type(1.1))              # float
print(type(""))               # str
print(type([1, 2]))           # list
print(type({1, 2}))           # set
print(type({1 : "", 2 : ""})) # dict

j1 = int(1.1)
j2 = float(1.1)
j3 = bool(0)
j4 = str(1.2)
j5 = int("1")
j6 = float("1.1")
print(j4)
print(j5)
print(j6)

print(1 / 1)         # 1.0
print(type(1 / 1))   # float
print(type(1 / 1.0)) # float

# %
print(3 // 2)
print(3 // 2.0) # 1.0

# pow
print(2 ** 3.1)

x = 1
x -= 1
# x-- error
# --x error
print(x)

print("str1" "str2")
# + 只能拼接字符串
print("str1" + "str2")
tmp = 1
# print("tmp: " + tmp)
print("tmp:", tmp)

print(len("str1"))

# format
print("%s" %tmp) 
print("%d" %tmp)
print("%s %s" %(tmp, tmp))

tmp2 = 110.011
print("%f" %tmp2)
print("%.0f" %tmp2)
print("%.1f" %tmp2)
print("%.2f" %tmp2)
print("%2.0f" %tmp2)
print("%4.0f" %tmp2)

print(f"{tmp}" " - " f"{tmp2}")

k1, k2, k3 = 1, 2.2, True
print(k1, k2, k3)

# input -> str -> type()
# l = input("input: ")
# print("l: ", int(l))

if None: # False
    print()
else:
    print()