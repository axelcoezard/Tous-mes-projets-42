#!/bin/bash

# Change the following variables to match your configuration
hostname_router1=routeur_jbertin-1
hostname_router2=routeur_jbertin-2
hostname_host1=host_jbertin-1
hostname_host2=host_jbertin-2

# Define color codes
RED='\033[0;31m'
GREEN='\033[0;32m'
BLUE='\033[0;34m'
LIGHT_BLUE='\033[1;34m'
NC='\033[0m' # No Color

config_host()
{
	local container_id=$1
	local ip_addr=$2
	local hostname=$3

	echo -e "${BLUE}Assign IP address to the eth1 interface of $hostname${NC}"
	docker exec $container_id sh -c "ip addr add $ip_addr dev eth1" > /dev/null 2>&1
	echo -e "-------------------------------------------------------------------------------------------------------"
	echo -e "${GREEN}Network configured for $hostname${NC}"
	echo -e "-------------------------------------------------------------------------------------------------------"
	echo -e ""
}

config_router()
{
	local container_id=$1
	local ip_addr=$2
	local hostname=$3

	echo -e "${BLUE}Assign IP address to the eth0 interface of $hostname${NC}"
	docker exec $container_id sh -c "ip addr add $ip_addr dev eth0" > /dev/null 2>&1

	echo -e "${BLUE}Create a VXLAN interface with specific parameters${NC}"
	docker exec $container_id sh -c "ip link add name vxlan10 type vxlan id 10 dev eth0 group 239.1.1.1 dstport 4789" > /dev/null 2>&1

	echo -e "${BLUE}Bring the VXLAN interface vxlan10 up${NC}"
	docker exec $container_id sh -c "ip link set dev vxlan10 up" > /dev/null 2>&1

	echo -e "${BLUE}Create a new bridge and bring it up${NC}"
	docker exec $container_id sh -c "ip link add br0 type bridge" > /dev/null 2>&1
	docker exec $container_id sh -c "ip link set dev br0 up" > /dev/null 2>&1

	echo -e "${BLUE}Add eth1 and vxlan10 interfaces to the bridge${NC}"
	docker exec $container_id sh -c "brctl addif br0 eth1" > /dev/null 2>&1
	docker exec $container_id sh -c "brctl addif br0 vxlan10" > /dev/null 2>&1

	echo -e "-------------------------------------------------------------------------------------------------------"
	echo -e "${GREEN}Network configured for $hostname${NC}"
	echo -e "-------------------------------------------------------------------------------------------------------"
	echo -e ""
}

configure_network()
{
	local container_id=$1
	# Get the hostname of the current container
	local hostname=$(docker exec "$container_id" hostname)

	# Increment the counter for each container that matches the predefined hostnames
	case $hostname in
		$hostname_host1|$hostname_host2|$hostname_router1|$hostname_router2)
			echo -e "-------------------------------------------------------------------------------------------------------"
			echo -e "${LIGHT_BLUE}Configuring network for container $container_id (Hostname: $hostname):${NC}"
			echo -e "-------------------------------------------------------------------------------------------------------"
			((counter++))
			;;
	esac

	# Configure the network settings for each specific hostname
	case $hostname in
		$hostname_host1)
			config_host $container_id "30.1.1.1/24" "$hostname_host1"
			;;
		$hostname_host2)
			config_host $container_id "30.1.1.2/24" "$hostname_host2"
			;;
		$hostname_router1)
			config_router $container_id "10.1.1.1/24" "$hostname_router1"
			;;
		$hostname_router2)
			config_router $container_id "10.1.1.2/24" "$hostname_router2"
			;;
	esac
}

# Get the list of running container IDs
containers=$(docker ps -q)
counter=0

# If there are running containers, configure the network for each one
if [[ -n $containers ]]; then
	for container_id in $containers; do
		configure_network $container_id
	done
else
	echo -e "${RED}No docker container running.${NC}"
fi

# Check if all 4 containers were configured and display a corresponding message
if [[ $counter -eq 4 ]]; then
	echo -e ""
	echo -e "-------------------------------------------------------------------------------------------------------"
	echo -e "${GREEN}Network configuration completed successfully for all 4 containers.${NC}"
	echo -e "-------------------------------------------------------------------------------------------------------"
else
	echo -e ""
	echo -e "-------------------------------------------------------------------------------------------------------"
	echo -e "${RED}Network configuration completed with errors. Not all 4 containers were configured.${NC}"
	echo -e "-------------------------------------------------------------------------------------------------------"
fi
