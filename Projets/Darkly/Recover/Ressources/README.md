# Recover

Sur la page de recuperation de mot de passe, il n'y a qu'un bouton et pas de champ pour mettre son email. En cherchant, on s'est apercu qu'un champ `hidden` d'email est dans l'HTML et contient un mail de destination.

Si on remplace par un autre mail et qu'on soumet le formulaire, le site nous donne le flag:

    1d4855f7337c0c14b6f44946872c4eb33853f40b2d54393fbe94f49f1e19bbb0

## Eviter cette faille

Cette faille permettrait via un script ou manuellement de spammer un email en utilisant le site et son identite.
Pour la corriger il suffirait deja de verifier que le mail de destination est affecte a un utilisateur existant, ainsi que de rajouter un champ email visible au formulaire.
