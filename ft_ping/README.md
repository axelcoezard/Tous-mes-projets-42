# ft_ping
Mon projet ft_ping du cursus de 42.

## Résumé
>	Recoder la commande ping va vous permettre d'avoir une première approche dans la communication (TCP/IP) entre deux machines dans un réseau.

## Wiki
##### Usage

	./ft_ping [-DhnoqvV] [-c count] [-i interval] [-s packetsize] [-t ttl] destination

##### Options:

-	**-c count** : S'arrête après l'envoi de `count` fois `ECHO_REQUEST`.

-	**-D** : Affiche l'horodatage (temps unix + microsecondes comme dans gettimeofday) avant chaque ligne.

-	**-h** : Affiche l'aide.

-	**-i interval** : Attend `interval` secondes entre l'envoi de chaque paquet.

-	**-n** : Sortie numérique uniquement. Aucune tentative ne sera faite pour rechercher les noms symboliques des adresses.

-	**-o** : S'arrête avec succès après avoir reçu un paquet de réponses.

-	**-q** : Output silencieux.  Rien n'est affiché à l'exception des lignes de résumé au démarrage et à la fin de l'opération.

-	**-s packetsize** : Spécifie le nombre d'octets de données à envoyer. La valeur par défaut est `56`, ce qui correspond à `84 octets` de données `ICMP` lorsqu'ils sont combinés aux `28 octets` de données d'en-tête `ICMP`.

-	**-t ttl** : Définir le temps de vie de l'IP.

-	**-v** : Affiche des logs supplémentaires.

-	**-V** : Affiche la version et s'arrête.
