# Include

Ici, on a affaire a une faille de type Path Traversal (`https://www.vaadata.com/blog/fr/comprendre-se-proteger-vulnerabilite-path-traversal/`).
En effet, le site utilise `?page=` pour afficher les pages, et il est possible de remonter dans l'arborescence du site en utilisant `../` dans l'url.

Quand on fait `?page=../` ou `?page=../../` on obtient des messages tels que `WTF ?` ou `Wrong..`.
Du coup, on continue de rajouter des `../` jusqu'a avoir `You can DO it !!!  :]` en ayant `?page=../../../../../../../`.
Ensuite, on accede au fichier `/etc/passwd` comme ca: `http://localhost:8080/?page=../../../../../../../etc/passwd`.
Et la page nous donne le flag:

		b12c4b2cb8094750ae121a676269aa9e2872d07c06e429d25a63196ec1c8c1d0

## Eviter cette faille

Le fichier `/etc/passwd` est un l'un des fichiers les plus recherchés par les hackers via cette car il contient les informations des utilisateurs du système.
Il est donc important de ne pas laisser ce fichier accessible depuis le web.

Pour eviter cette faille, il faut verifier que le chemin du fichier demandé est bien dans un dossier autorisé.
