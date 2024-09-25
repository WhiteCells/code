##################################################
##################################################
##################################################
### list

list = []

list.append(1)
list.append(1.1)
list.append("str")

for ele in list:
    print(type(ele))
    print(ele)

for i in range(0, len(list)):
    print(list[i])
    
for i in range(1, len(list) + 1):
    print(list[-i])
    
print(list.index("str"))

list.insert(0, [1.1, "str1"])

print(list[0][1])

# 用于将一个可迭代对象（如列表、元组、集合等）的所有元素添加到列表的末尾。
list.extend([1, 2, 3])

list.append([3, 4, 5])

print(list[len(list) - 1]) # [3, 4, 5]
print(list[len(list) - 2]) # 3

pop_ele = list.pop(0)
print(pop_ele) # [1.1, "str1"]
print(list[0]) # 1

del list[0]
print(list[0])

del list[0]
print(list[0])

list = [0, 1, 1, 2]

print(list.count(1)) # 2

list.remove(1)
print(list) # [0, 1, 2]

list.clear()
print(list) # []

##################################################
##################################################
##################################################
### tuple

tuple1 = (1, 2.2, "str")
# tuple() 构造函数创建元组，你需要传递一个可迭代对象
tuple2 = tuple([1, 2, "str"])
# tuple2 = tuple(1, 2.2, "str")

print(len(tuple1))

print(tuple1.index(1))

print(tuple1.count(1))

for ele in tuple1:
    print(ele)

for ele in tuple2:
    print(ele)

t = (1)
print(type(t)) # <class 'int'>

t2 = (1, )
print(type(t2)) # <class 'tuple'>

##################################################
##################################################
##################################################
### str

string1 = "string"
print(string1[1])
print(string1.index('r'))
print(string1.index("tr"))
print(string1.count('s'))
print(string1.find('t'))
print(string1.islower())

string2 = "this  is test"
word_list = string2.split(' ') # ['this', '', 'is', 'test']
print(word_list)

string3 = "  this "
print(string3.strip()) # this

string4 = "is this si"
print(string4.strip("is")) #  this

##################################################
##################################################
##################################################
# (序列)切片，得到一个新序列
list3 = [1, 2, 3, 4, 5, 6]

# [)
new_list = list3[1:2]
print(new_list) # [2]

new_list = list3[1:5:2]
print(new_list) # [2, 4]

new_list = list3[5:1:-1]
print(new_list) # [6, 5, 4, 3]

##################################################
##################################################
##################################################
### set
set1 = {1, 2.2, 2.2, "str"}
print(set1) # {1, 2.2, 'str'}
for ele in set1:
    print(ele)
set1.remove(2.2)
set1.pop()
set1.add(True)
print(len(set1))
print(set1)

set2 = {1, 2, 3}
set3 = {1, 2.2, 3}
# set3.union(set2)
# print(set3)

# print(set3.difference(set2))
# print(set2)

# set3.difference_update(set2)
# print(set3)

set1.clear()

##################################################
##################################################
##################################################
### dict
dict1 = {1: "str1", 2: "str2"}
for key in dict1:
    print(key)
    print(dict1[key])

print(len(dict1))
