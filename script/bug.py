import requests
from bs4 import BeautifulSoup

url = 'https://blog.030215.xyz'
response = requests.get(url)
soup = BeautifulSoup(response.content, 'html.parser')
print(soup.prettify())