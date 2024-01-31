# Survey

Cette faille se trouve sur la page `Survey` (`http://localhost:8080/?page=survey`) du site.
Sur cette page il y a un tableau avec 5 `form` contenant chacun un `select`.
Apres des tests, on a constate qu'il n'y a pas trop de securite, si on change l'option `2` en `4`, le formulaire se valide bien et ajoute `4` a la note moyenne.

Pour tester on ajoute un tres gros nombre, et on obtient le flag:

        03a944b434d5baff05f46c4bede5792551a2595574bcafc9a6e25f67c382ccaa

## Eviter cette faille

Cette faille est vraiment stupide, et pour la corriger il suffirait de verifier dans le front et le back que la valeur saisie se trouve bien entre 1 et 10.

```js
if (value >= 1 && value <= 10) {
    // valider le vote
} else {
    // envoyer un erreur
}
```
