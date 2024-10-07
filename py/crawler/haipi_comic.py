import undetected_chromedriver as uc
from selenium import webdriver
from selenium.webdriver.common.by import By
from selenium.webdriver.common.keys import Keys
from selenium.webdriver.chrome.options import Options
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
import time

url = 'https://m.happymh.com/'

options = uc.ChromeOptions()
options.add_argument('--user-agent=Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/91.0.4472.124 Safari/537.36')
# options.headless = False

service = webdriver.ChromeService(executable_path='/usr/bin/chromedriver')

# driver = webdriver.Chrome(options=options, service=service)
driver = uc.Chrome(options=options, service=service)

try:
    driver.get(url)
    driver.implicitly_wait(1)

    search_btn = driver.find_element(By.CLASS_NAME, 'search')
    search_btn.click()

    # time.sleep(10)
    # verify_btn = driver.find_element(By.XPATH, '//label[@class="cb-lb"]//span[@class="cb-lb-t"]')
    # verify_btn.click()
    print('iframe begin')

    # iframe = WebDriverWait(driver, 30).until(
    #     EC.frame_to_be_available_and_switch_to_it((By.TAG_NAME, "iframe"))
    # )
    WebDriverWait(driver, 10).until(
        EC.presence_of_element_located((By.TAG_NAME, "iframe"))
    )
    print('iframe end')

    verify_btn = WebDriverWait(driver, 10).until(
        EC.element_to_be_clickable((By.XPATH, '//label[@class="cb-lb"]//span[@class="cb-lb-t"]'))
    )

    print('verify_btn finished')
    time.sleep(2)
    verify_btn.click()
    time.sleep(20)

    driver.switch_to.default_content()

except Exception as e:
    print(e)