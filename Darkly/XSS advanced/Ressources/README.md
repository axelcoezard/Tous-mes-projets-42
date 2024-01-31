# XSS advanced

Sur la page d'accueil, il y a plusieurs images, dont une clicable qui nous amene a `?page=media&src=nsa`.
On peut donc essayer de changer le `src` pour voir si on peut acceder a d'autres fichiers ou executer un script JS.

En essayant `?page=media&src=nsa` on obtient une image de la NSA, et en essayant `?page=media&src=nsa.jpg` on obtient une erreur `404 Not Found`.

Au niveau du code html, on a `<object data="nsa.jpg"></object>`.
Ce qui veut dire que la page se contente juste de mettre le contenu de `src` dans l'attribue `data` de la balise `<object>`.

On peut donc essayer de mettre du code JS dans `src` pour voir si on peut l'executer.

On essaye donc d'injecter le code suivant en base64 pour passer dans `src`:
```html
<script>alert('XSS')</script>
```

On accede a la page `?page=media&src=data:text/html;base64,PHNjcmlwdD5hbGVydCgnWFNTJyk8L3NjcmlwdD4=` et elle nous donne le flag:

		928d819fc19405ae09921a2b71227bd9aba106f9d2d37ac412e9e5a750f1506d

## Eviter cette faille

Pour eviter cette faille, il faut verifier que le chemin du fichier demandé est bien dans un dossier autorisé. On peut egalement verifier que le contenu de `src` est bien une image. Idealement, on preferera remplacer les nom de fichier par des UUID (Universally Unique IDentifier) impossibles a deviner.

Avec un UUID, on aurait un url du genre `?page=media&src=8b6c1c7e-4b8b-4b0e-8e0e-5e2e2a4e6b6e` et on pourrait verifier que le fichier `8b6c1c7e-4b8b-4b0e-8e0e-5e2e2a4e6b6e` existe bien dans la base de donnees et qu'il s'agit bien d'une image.
