import requests


url = 'https://weathernew.pae.baidu.com/weathernew/pc?query=%E6%B9%96%E5%8C%97%E6%AD%A6%E6%B1%89%E5%A4%A9%E6%B0%94&srcid=4982&forecast=long_day_forecast'

headers = {
    'content-type': 'text/html;charset=utf-8'
}

response = requests.get(url, headers=headers)

print(response.text)

with open('weath.html', 'a', encoding='utf-8') as f:
    f.write(response.text)