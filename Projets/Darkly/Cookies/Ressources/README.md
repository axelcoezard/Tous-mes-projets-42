# Cookies

Ici la faille `Cookies` porte plutot bien son nom.

En effet, il suffit de regarder dans les cookies du sites via `Inspecter -> Stockage -> Cookies` sur Firefox (plutot similaire sur Chrome), pour decouvrir qu'un cookie se nomme `I_am_admin` et contient un hash `68934a3e9455fa72420237eb05902327`.

En utilisant le site `https://www.tunnelsup.com/hash-analyzer/` on sait que c'est un hash `md5`.
En utilisant le site `https://www.dcode.fr/md5-hash` on decouvre que sa valeur vaut `false`.
On hash donc `true` en `md5` via le meme site et on obtient `b326b5062b2f0e69046810717534cb09` qu'on met dans le cookie.

En rafraichissant la page, une alert JS nous donne le flag:

        df2eb4ba34ed059a1e3e89ff4dfc13445f104a1a52295214def1c4fb1693a5c3

## Eviter cette faille

Pour eviter cette faille, il suffit deja de ne pas stocker l'information des droits au niveau des cookies/local storage. Ensuite, il faudrait envisager une gestion des droits cote serveur, en fonction des utilisateurs.
