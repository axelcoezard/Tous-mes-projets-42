#!/bin/bash

# Change the following variables to match your configuration
hostname_router1=routeur_jbertin-1

hostname_router2=routeur_jbertin-2
hostname_router3=routeur_jbertin-3
hostname_router4=routeur_jbertin-4

hostname_host1=host_jbertin-1
hostname_host2=host_jbertin-2
hostname_host3=host_jbertin-3

# Define color codes
RED='\033[0;31m'
GREEN='\033[0;32m'
BLUE='\033[0;34m'
LIGHT_BLUE='\033[1;34m'
NC='\033[0m' # No Color

exec_docker()
{
	docker exec $1 sh -c "$2" > /dev/null 2>&1
}

config_host()
{
	local container_id=$1
	local ip_addr=$2
	local hostname=$3
	local interface=$4

	echo -e "${BLUE}Assign IP address to the eth1 interface of $hostname${NC}"
	exec_docker $container_id "ip addr add $ip_addr dev $interface"

	echo -e "-------------------------------------------------------------------------------------------------------"
	echo -e "${GREEN}Network configured for $hostname${NC}"
	echo -e "-------------------------------------------------------------------------------------------------------"
	echo -e ""
}

config_router_exec()
{
	local container_id=$1
	local config_name=$2
	local hostname=$3

    docker exec -i $container_id vtysh < $config_name

	echo -e "-------------------------------------------------------------------------------------------------------"
	echo -e "${GREEN}Network configured for $hostname${NC}"
	echo -e "-------------------------------------------------------------------------------------------------------"

}

config_router_leaf()
{
    local container_id=$1
	local config_name=$2
	local ethA_name1=$3
	local ethB_name2=$4
	local hostname=$5

	exec_docker $container_id "ip link add name vxlan10 type vxlan id 10 dev $ethB_name2 dstport 4789"
	exec_docker $container_id "ip link set dev vxlan10 up"
	exec_docker $container_id "ip link add name br0 type bridge"
	exec_docker $container_id "ip link set dev br0 up"
	exec_docker $container_id "brctl addif br0 $ethA_name1"
	exec_docker $container_id "brctl addif br0 vxlan10"

	config_router_exec $container_id $config_name $hostname
}

configure_network()
{
	local container_id=$1
	# Get the hostname of the current container
	local hostname=$(docker exec "$container_id" hostname)

	# Increment the counter for each container that matches the predefined hostnames
	case $hostname in
		$hostname_host1|$hostname_host2|$hostname_host3|$hostname_router1|$hostname_router2|$hostname_router3|$hostname_router4)
			echo -e "-------------------------------------------------------------------------------------------------------"
			echo -e "${LIGHT_BLUE}Configuring network for container $container_id (Hostname: $hostname):${NC}"
			echo -e "-------------------------------------------------------------------------------------------------------"
			((counter++))
			;;
	esac

	# Configure the network settings for each specific hostname
	case $hostname in
		$hostname_host1)
			config_host $container_id "20.1.1.1/24" "$hostname_host1" "eth1"
			;;
		$hostname_host2)
			config_host $container_id "20.1.1.3/24" "$hostname_host2" "eth0"
			;;
		$hostname_host3)
			config_host $container_id "20.1.1.2/24" "$hostname_host3" "eth0"
			;;
		$hostname_router1)
			config_router_exec $container_id "routeur_jbertin-1.conf" $hostname
			;;
		$hostname_router2)
			config_router_leaf $container_id "routeur_jbertin-2.conf" "eth1" "eth0" $hostname
			;;
		$hostname_router3)
			config_router_leaf $container_id "routeur_jbertin-3.conf" "eth0" "eth1" $hostname
			;;
		$hostname_router4)
			config_router_leaf $container_id "routeur_jbertin-4.conf" "eth0" "eth2" $hostname
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
if [[ $counter -eq 7 ]]; then
	echo -e ""
	echo -e "-------------------------------------------------------------------------------------------------------"
	echo -e "${GREEN}Network configuration completed successfully for all 7 containers.${NC}"
	echo -e "-------------------------------------------------------------------------------------------------------"
else
	echo -e ""
	echo -e "-------------------------------------------------------------------------------------------------------"
	echo -e "${RED}Network configuration completed with errors. Not all 7 containers were configured.${NC}"
	echo -e "-------------------------------------------------------------------------------------------------------"
fi
