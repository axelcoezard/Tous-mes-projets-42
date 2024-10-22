# Zappy
Mon projet Zappy du cursus de 42, réalisé avec [Loan](https://github.com/Kalinololo).

## Description
> Vous allez maintenant créer une partie multi-joueurs dans un réseau TCP/IP. Le jeu sera composé d'un serveur gérant le terrain de jeu, d'un client graphique qui affiche l'état du plateau et de clients IA qui se connectent au serveur pour piloter un joueur sur le terrain. Il s'agit d'un véritable projet complet qui vous permettra d'exprimer votre créativité en plus de vos connaissances techniques.

## Fonctionnalites:
- [x] Serveur non-bloquant
- [ ] Client intelligent (IA)
- [x] Client graphique (SDL2)
  - [x] Affichage du terrain avec les ressources
  - [x] Affichage des joueurs
  - [x] Affichage d'une légende a la selection d'une ressource
  - [x] Affichage du classement
  - [x] Suivi d'un joueur et affichage de ses informations
  - [x] Affichage des oeufs
  - [x] Affichage des sons

## Commandes possibles
- [x] `avance` : Avancer d'une case dans la direction actuelle.
- [x] `droite` : Changer d'orientation de 90 degrés vers la droite.
- [x] `gauche` : Changer d'orientation de 90 degrés vers la gauche.
- [x] `voir` : Prendre connaissance de ce que voit le joueur sur le terrain.
- [x] `inventaire` : Prendre connaissance de l'inventaire du joueur.
- [x] `prend` : Prendre un objet sur la case où se trouve le joueur.
- [x] `pose` : Poser un objet de l'inventaire du joueur sur la case où se trouve le joueur.
- [x] `expulse` : Expulser tous les joueurs présents sur la case où se trouve le joueur.
- [x] `broadcast` : Envoyer un message à tous les joueurs du jeu.
- [x] `incantation` : Commencer une incantation.
- [x] `fork` : Pondre un œuf.
- [x] `connect_nbr` : Demander le nombre de slot restant dans l'equipe du joueur.
