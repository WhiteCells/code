from lxml import etree

xml_data = '''
<parent>
    <son id="1">
        <weight>1</weight>
        <name>xxx</name>
        <age>10</age>
    </son>
    <son id="2">
        <weight>2</weight>
        <name>yyy</name>
        <age>20</age>
    </son>
    <son id="3" xyz="111">
        <weight>3</weight>
        <name>zzz</name>
        <age>30</age>
    </son>
    <son id="4">
        <weight>4.4</weight>
        <name>eee</name>
        <age>40</age>
    </son>
</parent>
'''

root = etree.fromstring(xml_data)

# xpath -> tuple

# 通过指定标签，获取标签内容
all_son_weight = root.xpath('/parent/son/weight/text()')
print('all son weight: ', all_son_weight)

# 通过索引标签（下标从 1 开始），获取标签内容
son2_age = root.xpath('/parent/son[2]/age/text()')
print('son2 age: ', son2_age)

# name yyy
# yyy_name_son = root.xpath('/parent/son[name=yyy]/name/text()') # error
yyy_name_son = root.xpath('/parent/son[name="yyy"]/name/text()')
print('name yyy son: ', yyy_name_son)

# weight 4.4
# weight_4_4_son = root.xpath('/parent/son[weight=4.4]/name/text()') # ok
weight_4_4_son = root.xpath('/parent/son[weight="4.4"]/name/text()')
print('weight 4.4 son: ', weight_4_4_son)

# 筛选标签
grate_20_son = root.xpath('/parent/son[age >= 20]/name/text()') # list
print('age grate 20: ', grate_20_son)

all_son_name = root.xpath('/parent/son/name/text()')
print('all son name: ', all_son_name)

# 不完全指定路径
all_names = root.xpath('//name/text()')
print('all names: ', all_names)

# 通过属性筛选标签
id_3_son_name = root.xpath('//son[@id="3"]/name/text()')
print('id=3 son name: ', id_3_son_name)

id_3_xyz_yyy_son_name = root.xpath('//son[@id="3" and @xyz="111"]/name/text()')
print('id=3 xyz="111" son name', id_3_xyz_yyy_son_name)

# 通过属性查找属性
id_3_son_xyz = root.xpath('//son[@id="3"]/@xyz')
print('id=3 son xyz: ', id_3_son_xyz)

# 获取第一个 <son> 的 <name>
first_son_name = root.xpath('(//son/name)[1]/text()')
print('first son name: ', first_son_name)

# 获取所有元素
all_elements = root.xpath('//*')
print('all elements: ', all_elements)