# XSS basic

Il suffit de mettre une lettre dans `Name` parmis `s`, `i`, `r`, `c`, `t`, `p`, `l`, et d'autres, sans `Message` pour debloquer le flag:

        0fbb54bbf7d099713ca4be297e1bc7da0173d8b3c21c1811b916a3a86652724e

Normalement, une faille XSS ne devrait pas etre aussi simple, mais il faudrait injecter un code HTML ou JS, comme par exemple une balise `<script />` qui executerait du code pour recuperer le flag dans les cookies.

## Eviter cette faille

Pour eviter ce genre de faille, il suffit de `sanitize` tous les mots et caracteres ayant un rapport avec du code avant de le publier dans la base de donnee ou de l'afficher sur la page d'un utilisateur.
