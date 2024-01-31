import requests
from bs4 import BeautifulSoup

def fetch_and_print(url):
    try:
        response = requests.get(url)
        response.raise_for_status()
        return response.text
    except requests.exceptions.RequestException as e:
        print(f"Erreur lors de la requête vers {url}: {e}")
        return None

def extract_links(html):
    soup = BeautifulSoup(html, 'html.parser')
    links = soup.find_all('a', href=True)
    tmp =[link['href'] for link in links]
    if '../' in tmp:
        tmp.remove('../')
    return tmp

def get_page_names(base_url):
    html = fetch_and_print(base_url)
    if html is not None:
        soup = BeautifulSoup(html, 'html.parser')
        links = soup.find_all('a', href=True)
        return [link['href'] for link in links]
    return []

def verifie_absence_string(chaine, liste_strings):
    for s in liste_strings:
        if s in chaine:
            return False
    return True

def find_readme_recursive(current_url):
    html = fetch_and_print(current_url)
    if html is not None:
        links = extract_links(html)
        if 'README' in links:
            readme_url = current_url + 'README'
            readme_content = fetch_and_print(readme_url)
            if (verifie_absence_string(readme_content, ['Demande', 'Non', 'Tu', 'Toujours'])):
                print(f"Le flag est : {readme_content.split(':')[1]}")
                return
            for link in links:
                next_url = current_url + link
                find_readme_recursive(next_url)


base_url = "http://localhost:8080/.hidden/"
print("Cela va prendre un petit peu de temps...")
find_readme_recursive(base_url)
