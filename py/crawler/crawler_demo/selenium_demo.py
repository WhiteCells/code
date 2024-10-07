from selenium import webdriver
from selenium.webdriver.common.by import By
from selenium.webdriver.common.keys import Keys
from selenium.webdriver.chrome.options import Options
from selenium.webdriver.common.proxy import Proxy, ProxyType
import time


url = 'https://www.baidu.com'

chrome_options = Options()
chrome_options.add_argument('--headless')
chrome_options.add_argument("--disable-gpu")
chrome_options.add_argument('--no-sandbox')

"""
normal	complete	默认值, 等待所有资源下载
eager	interactive	DOM 访问已准备就绪, 但诸如图像的其他资源可能仍在加载
none	Any	        完全不会阻塞 WebDriver
"""
chrome_options.page_load_strategy = 'normal'

chrome_options.accept_insecure_certs = False

# 指定中断正在执行脚本的时机
chrome_options.timeouts = {
    'script': 5000,
    'pageLoad': 5000,
    'implicit': 5000, # 指定定位元素时等待隐式元素定位策略的时间
}

chrome_options.enable_downloads = True

# chrome_options.set_window_rect = False


service = webdriver.ChromeService(executable_path='C:\Program Files\Google\Chrome\Application\chrome.exe', port=10101)

# driver = webdriver.Chrome(service=service, options=chrome_options) # ?
driver = webdriver.Chrome(options=chrome_options)


# proxy
"""
ProxyType
DIRECT: 直接连接
MANUAL: 手动配置
SYSTEM: 系统代理
PAC: 代理自动配置，指定 URL 下载 PAC 文件
AUTODETECT: 自动检测，通过 WPAD 自动查找合适的代理
"""
chrome_options.proxy = Proxy( {
    'proxyType': ProxyType.MANUAL,
    'httpProxy': '127.0.0.1:2080',
    'sslProxy': '127.0.0.1:2080'
})

try:
    driver.get(url)
    title = driver.title
    assert title == '百度一下，你就知道'
    cookies = driver.get_cookies() # [{}，{}]

    print('title: ', title)
    print('cookies: ', cookies)

    # 隐式等待
    driver.implicitly_wait(1)

    # 找元素之前需确保元素位于页面上
    # search_box = driver.find_element(By.NAME, "q")
    search_box = driver.find_element(By.NAME, value="wd")
    search_button = driver.find_element(By.ID, value='su')

    # 交互之前需确保元素处于可交互状态
    search_box.send_keys("测试")
    # search_box.send_keys(Keys.RETURN)
    search_button.click()

    time.sleep(2)

    # 截取屏幕
    driver.get_screenshot_as_file(filename='screen.png')
    # 获取窗口大小
    window_rect = driver.get_window_rect()
    print(window_rect) # {'height': 1012, 'width': 945, 'x': 10, 'y': 10}

    with open('url.txt', 'w') as f:
        pass

    # 获取 h3 标签内容
    results = driver.find_elements(By.CSS_SELECTOR, value='h3')
    for result in results:
        text = result.text
        print(text)
        with open('url.txt', 'a', encoding='utf-8') as f:
            f.write(text + '\n')

finally:
    driver.quit()
