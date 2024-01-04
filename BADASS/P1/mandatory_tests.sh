#!/bin/bash

# Change the following variables to match your configuration
hostname_routeur=routeur_jbertin
hostname_host=host_jbertin-1

# Define color codes
RED='\033[0;31m'
LIGHT_BLUE='\033[1;34m'
NC='\033[0m' # No Color

get_container_info()
{
	local container_id=$1
	local hostname=$(docker exec "$container_id" hostname)
	case $hostname in
		$hostname_host|$hostname_routeur)
			echo -e "-------------------------------------------------------------------------------------------------------"
			echo -e "${LIGHT_BLUE}Informations about container $container_id (Hostname: $hostname):${NC}"
			echo -e "-------------------------------------------------------------------------------------------------------"
			docker exec $container_id ps
			echo -e "-------------------------------------------------------------------------------------------------------"
			echo -e ""
			;;
	esac
}

containers=$(docker ps -q)

if [[ -n $containers ]]; then
	for container_id in $containers; do
		get_container_info $container_id
	done
else
	echo -e "${RED}No docker container running.${NC}"
fi
