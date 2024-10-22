# Guess (hidden file)

En testant l'URL suivante [http://localhost/.hidden/](http://localhost/.hidden/), nous accédons à une page contenant une liste de liens indexés.

En explorant chaque lien, nous sommes redirigés vers d'autres pages, chacune d'entre elles renfermant à son tour de nouvelles listes.

Nous remarquons que chaque page, en plus des liens, contient un fichier README, nous incitant à fouiller ces pages à la recherche d'un flag.

Pour ce faire, nous avons créé un script qui vérifie de manière récursive dans chaque page si le README contient une phrase commençant par un mot que nous n'avons pas trouvé lors de notre recherche manuelle.

Après un certain temps, notre script nous livre enfin le README contenant une phrase différente, renfermant ainsi notre fameux flag.

## Eviter cette faille

Il faut retenir qu'il ne faut pas se croire plus intelligent qu'un robot ; même un fichier très bien caché peut être découvert sans grande difficulté par un script de scraping.
