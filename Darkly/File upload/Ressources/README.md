# File upload

Quand on visite la page `?page=upload` on se retrouve face a un formulaire d'upload de fichier.

On peut donc essayer d'uploader un fichier php, sans succès car le serveur ne l'accepte pas.
On peut contaster que notre navigateur envoie dans les en-têtes HTTP le `Content-type` qui est `application/octet-stream` pour un fichier php et `image/jpeg` pour un fichier image.

Si on modifie le `Content-type` en `image/jpeg` on devrait pouvoir uploader notre fichier php.

Pour cela, on va utiliser un script python qui va nous permettre de modifier les en-têtes HTTP de notre requête (cf [script.py](./script.py)).
On lance le script et on obtient alors le flag:

		46910d9ce35b385885a9f7e2b336249d622f29b267a1771fbacf52133beddba8

# Eviter cette faille

Pour securiser cette faille, il faut verifier que le fichier uploadé est bien une image et non pas un fichier php.
Pour cela, on peut utiliser la fonction `exif_imagetype` qui va nous permettre de verifier le type de l'image.

```php
		<?php
		$allowed_types = array(IMAGETYPE_PNG, IMAGETYPE_JPEG, IMAGETYPE_GIF);
		$detected_type = exif_imagetype($_FILES['uploaded']['tmp_name']);
		if (!in_array($detected_type, $allowed_types)) {
			die("Invalid file type");
		}
		?>
```



