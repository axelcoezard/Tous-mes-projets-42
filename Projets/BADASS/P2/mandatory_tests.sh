#!/bin/bash

# Change the following variables to match your configuration
hostname_router1=routeur_jbertin-1
hostname_router2=routeur_jbertin-2
hostname_host1=host_jbertin-1
hostname_host2=host_jbertin-2

# Define color codes
RED='\033[0;31m'
BLUE='\033[0;34m'
LIGHT_BLUE='\033[1;34m'
NC='\033[0m' # No Color

get_container_info()
{
	local container_id=$1
	local hostname=$(docker exec "$container_id" hostname)
	case $hostname in
		$hostname_host1)
			echo -e "-------------------------------------------------------------------------------------------------------"
			echo -e "${LIGHT_BLUE}Informations about container $container_id (Hostname: $hostname):${NC}"
			echo -e "-------------------------------------------------------------------------------------------------------"
			echo -e "${BLUE}Show the IP addresses of the eth1 interface:${NC}"
			docker exec $container_id sh -c "ifconfig eth1"
			echo -e "${BLUE}Perform a ping to 30.1.1.2 (limit to 5 requests)${NC}"
			docker exec $container_id sh -c "ping -c 5 30.1.1.2"
			echo -e "-------------------------------------------------------------------------------------------------------"
			echo -e ""
			;;
		$hostname_host2)
			echo -e "-------------------------------------------------------------------------------------------------------"
			echo -e "${LIGHT_BLUE}Informations about container $container_id (Hostname: $hostname):${NC}"
			echo -e "-------------------------------------------------------------------------------------------------------"
			echo -e "${BLUE}Show the IP addresses of the eth1 interface:${NC}"
			docker exec $container_id sh -c "ifconfig eth1"
			echo -e "${BLUE}Perform a ping to 30.1.1.1 (limit to 5 requests)${NC}"
			docker exec $container_id sh -c "ping -c 5 30.1.1.1"
			echo -e "-------------------------------------------------------------------------------------------------------"
			echo -e ""
			;;
		$hostname_router1|$hostname_router2)
			echo -e "-------------------------------------------------------------------------------------------------------"
			echo -e "${LIGHT_BLUE}Informations about container $container_id (Hostname: $hostname):${NC}"
			echo -e "-------------------------------------------------------------------------------------------------------"
			echo -e "${BLUE}Show the VXLAN interface vxlan10:${NC}"
			docker exec $container_id bash -c "ip -d link show vxlan10"
			echo -e ""
			echo -e "${BLUE}Show the MAC addresses of the bridge br0:${NC}"
			docker exec $container_id bash -c "brctl showmacs br0"
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
