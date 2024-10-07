from lxml import etree
from playwright.sync_api import sync_playwright

# html_path = './demo.html'
#
# with open(html_path, 'r', encoding='utf-8') as f:
#     html_content = f.read()

# print(html_content)

url = 'https://baidu.com'

with sync_playwright() as sp:
    browser = sp.chromium.launch()
    page = browser.new_page()
    page.goto(url)
    html_content = page.content()
    browser.close()

root = etree.HTML(html_content)

value = root.xpath('//form//input[@type="submit"]/@value')

print(value[0])

titles = root.xpath('//span[@class="title-content-title"]/text()')

for title in titles:
    print(title)