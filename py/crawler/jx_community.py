from selenium import webdriver
from selenium.webdriver.support import expected_conditions as EC
from selenium.webdriver.common.by import By
from selenium.webdriver.chrome.options import Options
import os
import re


url = 'http://spfxm.whfgxx.org.cn:8083/spfxmcx/spfcx_index.aspx'

chrome_options = Options()
chrome_options.add_argument('--headless')

service = webdriver.ChromeService(executable_path='/usr/bin/chromedriver')

driver = webdriver.Chrome(service=service, options=chrome_options)

community_path = './jx_community'

def clean_name(name):
    return re.sub(r'[<>:"/\\|?*]', '', name)

try:
    driver.get(url)
    driver.implicitly_wait(1)

    # 行政选择
    state_select_ele = driver.find_element(By.ID, value='DropDownList_xzq')
    state_select_ele.click()

    # 江夏选项
    jx_option_ele = driver.find_element(By.XPATH, value='//select/option[@value="江夏区"]')
    jx_option_ele.click()

    # 查询按钮
    query_button_ele = driver.find_element(By.XPATH, value='//input[@id="query"]')
    query_button_ele.click()
    
    main_window = driver.current_window_handle

    def query_one_html():
        # main_window = driver.current_window_handle
        
        communities_ele = driver.find_elements(By.XPATH, '//table[@id="tables"]//td/a[@target="_blank"]')

        for community in communities_ele:
            community_str = clean_name(community.text)
            print('===> ', community_str)
            one_community_path = f'{community_path}/{community_str}'
            if not os.path.exists(one_community_path):
                os.makedirs(one_community_path)
                
            community.click()

            # 切换到小区详细页面
            driver.switch_to.window(driver.window_handles[-1])
            print('[title]: ', driver.title)
            table_link = driver.find_element(By.XPATH, '//table[@id="table_mx"]//a[@id="href1"]')
            print('---> ', table_link.text)
            table_link.click()

            driver.switch_to.window(driver.window_handles[-1])
            buildings = driver.find_elements(By.XPATH, '//tbody[@style="text-align:center;"]//td/a[@target="_blank"]')

            building_window = driver.current_window_handle
            for building in buildings:
                building_str = clean_name(building.text)
                
                print("[building name]", building_str)
                # 点击栋名
                building.click()
                # 切换到栋的页面
                print('build title: ', driver.current_window_handle.title)
                driver.switch_to.window(driver.window_handles[-1])
                details = driver.find_elements(By.XPATH, '//table[@class="tab_style"]//tr')
                
                for detail in details:
                    print(detail.text)
                    with open(f'{one_community_path}/{building_str}.txt', 'a', encoding='utf-8') as f:
                        f.write(detail.text + '\n')

                driver.close()
                driver.switch_to.window(building_window)

            # 切换回小区名列表
            driver.switch_to.window(main_window)
                
    
    def click_next_page(x: int):
        next_page_ele_attribute = f'//a[@href="javascript:__doPostBack(\'AspNetPager1\',\'{x}\')"]'
        print(next_page_ele_attribute)
        next_page_ele = driver.find_element(By.XPATH, value=next_page_ele_attribute)
        next_page_ele.click()

    # 总页数
    page_count_ele = driver.find_element(By.XPATH, value='//div[@class="pages"]/font')
    page_count = int(page_count_ele.text)
    print(page_count)

    for i in range(2, page_count + 2):
        query_one_html()
        driver.switch_to.window(main_window)
        # 最后一页不翻页
        if i - 1 < page_count:
            click_next_page(i)

finally:
    driver.quit()
