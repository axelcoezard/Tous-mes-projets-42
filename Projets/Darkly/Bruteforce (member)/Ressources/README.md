# Bruteforce (member)

Pour cette faille, il suffit de se rendre sur la page de connexion `http://localhost:8080/?page=signin` et de soumettre le formulaire avec un mot de passe incorrect.

On obtient une erreur mais on peut voir qu'on est maintenant sur la page `http://localhost:8080/?page=signin&username=jaguards&password=haribo+c%27est+dragolo&Login=Login#`.

On peut donc voir que le mot de passe est passé en clair dans l'url.

On peut donc essayer de bruteforcer le mot de passe en utilisant un script python qui utilisera une liste des mots de passe les plus utilisés en France et dans le monde.

On va remplir le fichier passwords.txt avec une liste de mots de passe à tester.
Pour cela, on recupere une liste de mots de passe les plus utilisés en France et dans le monde, via:
 - `https://www.capital.fr/votre-argent/decouvrez-les-20-mots-de-passe-les-plus-choisis-en-france-et-ceux-a-ne-surtout-pas-utiliser-1467550`
 - `https://fr.wikipedia.org/wiki/Liste_des_mots_de_passe_les_plus_courants`

## Eviter cette faille

Pour eviter de se faire bruteforce, le site pourrait mettre en place un systeme de captcha, ou de bloquer l'ip apres un certain nombre de tentatives de connexion. Il pourrait aussi demander un delais de quelques secondes entre chaque tentative de connexion.

