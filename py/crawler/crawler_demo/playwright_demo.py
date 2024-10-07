from playwright.sync_api import sync_playwright


url = 'https://www.baidu.com'

with sync_playwright() as p:
    browser = p.chromium.launch()
    page = browser.new_page()
    page.goto(url)
    content = page.content()
    with open('demo.html', 'w', encoding='utf-8') as f:
        f.write(content)

    print(content)
    browser.close()
