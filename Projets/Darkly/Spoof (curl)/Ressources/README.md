# Spoof (curl)

Quand on va au niveau du footer et qu'on clique sur le copyright BornToSec, on atteri sur une page `http://localhost:8080/?page=b7e44c7a40c5f80139f0a50f3650fb2bd8d00b0d24667c4c2ca32c88e13b758f`.

Sur cette page, il y a seulement du texte, et une image d'albatroz.

En inspectant la page, on voit un commentaire qui nous explique qu'on doit venir depuis `https://www.nsa.gov/` et utiliser le navigateur `ft_bornToSec`.

Du coup, on va modifier la requete GET vers cette page via Mozilla Firefox et on va ajouter le header `Referer: https://www.nsa.gov/` et modifier l'agent en `User-Agent: ft_bornToSec`.

En faisant ça, on obtient le flag:

		f2a29020ef3132e01dd61df97fd33ec8d7fcd1388cc9601e7db691d17d4d6188

## Eviter cette faille

Pour securiser cette page, on pourrait eventuellement ajouter un token/mot de passe suplementaire a passer en parametre GET ou POST. Cependant, cette faille n'existe pas vraiment dans la realite car personne ne securiser des pages comme ca.
