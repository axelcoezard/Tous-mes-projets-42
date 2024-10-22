# Admin (htpasswd)

Dans le fichier `robots.txt` on peut voir qu'il y a une page `/whatever`.
Quand on va sur cette page on trouve un fichier htpasswd.

Dans ce fichier on trouve un username et un hash `root:437394baff5aa33daa618be47b75cb49`.

En utilisant le site `https://www.tunnelsup.com/hash-analyzer/` on sait que c'est un hash `md5`.
En utilisant le site `https://www.dcode.fr/md5-hash` on decouvre que sa valeur vaut `qwerty123@`.

Il ne reste plus qu'a se rendre sur la page `http://localhost:8080/admin` ou on peut se connecter avec le username `root` et le mot de passe `qwerty123@`.

La page nous donne le flag:

		d19b4823e0d5600ceed56d5e896ef328d7a2b9e7ac7e80f4fcdb9b10bcb3e7ff

## Eviter cette faille

On peut eviter cette faille en evitant de faire confiance aux fichiers robots.txt et en protegeant  avec un .htaccess.
