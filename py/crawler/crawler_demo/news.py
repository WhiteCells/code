from playwright.sync_api import sync_playwright
from lxml import etree


url = 'https://top.baidu.com/board?platform=pc&tab=homepage&sa=pc_index_homepage_all'

with sync_playwright() as sp:
    browser = sp.chromium.launch()
    page = browser.new_page()
    page.goto(url)
    html_content = page.content()
    browser.close()

# print(html_content)

with open('news.html', 'w', encoding='utf-8') as f:
    f.write(html_content)

"""
xpath 筛选
"""
with open('news.html', 'r', encoding='utf-8') as f:
    html_content = f.read()

# root = etree.fromstring(html_content)
root = etree.HTML(html_content)

# 获取榜单
# ranking_list = root.xpath('//span[@class="title_jDbBV c-theme-color"]/text()')
# for ranking in ranking_list:
#     print(ranking)
#
# # 找每个榜下的内容 + 链接
# titles = root.xpath('//a[@target="_blank"]//div[]')
# # 榜单名
# realtime_title = root.xpath(realtime_id + ranking_title_id + '/text()')
# print(realtime_title[0])

ranking_title_id = '//span[@class="title_jDbBV c-theme-color"]'

# realtime 模块
realtime_id = '//div[@theme="realtime"]'


print('===> realtime')
# 榜单内容
realtime_names = root.xpath('//div[@theme="realtime"]//div[@class="normal_1fQqB"]//div[@class="c-single-text-ellipsis"]')
for realtime_name in realtime_names:
    print(realtime_name.text)

print('===> novel')
novel_names = root.xpath('//div[@theme="novel"]//a[@class="title_ZsyAw"]')
for novel_name in novel_names:
    print(novel_name.text)

print('===> movie')
movie_names = root.xpath('//div[@theme="movie"]//a[@class="title_ZsyAw"]')
for movie_name in movie_names:
    print(movie_name.text)
    
print('===> teleplay')
movie_names = root.xpath('//div[@theme="teleplay"]//a[@class="title_ZsyAw"]')
for movie_name in movie_names:
    print(movie_name.text)
    
print('===> car')
movie_names = root.xpath('//div[@theme="car"]//a[@class="title_ZsyAw"]')
for movie_name in movie_names:
    print(movie_name.text)
    
print('===> game')
movie_names = root.xpath('//div[@theme="game"]//a[@class="title_ZsyAw"]')
for movie_name in movie_names:
    print(movie_name.text)

"""
selenium
"""


"""
requests
"""

import requests


url = 'https://top.baidu.com/board?tab=realtime'

headers = {
    'content-type': 'text/html; charset=utf-8'
}

response = requests.get(url, headers=headers)

print(response.text)

with open('new2.html', 'a', encoding='utf-8') as f:
    f.write(response.text)