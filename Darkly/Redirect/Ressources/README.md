# Redirect

En bas du site on peut trouver 3 liens pour facebook, twitter et instagram. Ces trois liens sont comme ci:

        http://localhost:8080/index.php?page=redirect&site=facebook
        http://localhost:8080/index.php?page=redirect&site=twitter
        http://localhost:8080/index.php?page=redirect&site=instagram

Le site nous redirige en fonction du site indique dans l'URL.
Or, on peut passer n'importe quoi en parametre et rediriger un utilisateur vers le site qu'on veut, aussi frauduleux soit-il.

On essaye donc avec `http://localhost:8080/index.php?page=redirect&site=pornhub.com` et le site nous recompense avec le flag:

        b9e775a0291fed784a2d9680fcfad7edd6b8cdf87648da647aaf4bba288bcab3

## Eviter cette faille

Une solution pour securiser cette faille serait que le site verifie la valeur du parametre `site` avant de rediriger l'utilisateur. Dans cette exemple, il devrait seulement autoriser facebook, twitter et instagram.
