#!/bin/bash

# Vérification des arguments
if [ "$#" -lt 2 ]; then
	echo "Usage: $0 <port> <nombre_joueurs_par_equipe>"
	exit 1
fi

# Récupération des arguments
port="$1"
max_joueurs="$2"
shift 2 # Pour ignorer les deux premiers arguments (port et nombre de joueurs par équipe)
equipes=("R" "N")

# Creation du dossier de logs
mkdir -p logs

# Boucle pour lancer les clients pour chaque équipe
for equipe in "${equipes[@]}"; do
    for ((i = 0; i < max_joueurs; i++)); do
        log_filename="logs/$equipe-$i.log"
        ./client -p "$port" -n "$equipe" &> "$log_filename" &
    done
    echo "$max_joueurs clients lancés pour l'équipe $equipe sur le port $port."
done
