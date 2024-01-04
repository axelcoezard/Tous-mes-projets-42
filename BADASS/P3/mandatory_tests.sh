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

title() {
	clear
	sleep 0.5

	echo -e "${LIGHT_BLUE}-------------------------------------------------------------------------------------------------------${NC}"
	echo -e "${GREEN} $1 ${NC}"
	echo -e "${LIGHT_BLUE}-------------------------------------------------------------------------------------------------------${NC}"
}

separator() {
	echo -e "${LIGHT_BLUE}Press Enter to continue...${NC}"
	read -r
}

select_container() {
	local container_name=$1
	local containers=$(docker ps -q)

	if [[ -n $containers ]]; then
		for container_id in $containers; do
			hostname=$(docker exec "$container_id" hostname)
			if [[ $hostname == $container_name ]]; then
				echo -e "$container_id"
				return 1
			fi
		done
	fi
	return 0
}

screenshot_test() {
	local target_hostname=$1
	local test_title=$2
	local config_file=$3

	title "$test_title"

	target_container=$(select_container $target_hostname)
	docker exec -i $target_container vtysh < $config_file

	separator
}


screenshot_test $hostname_router4 "Test 1: IP route visibility for $hostname_router4" ./tests/ip_route.test.conf
screenshot_test $hostname_router4 "Test 2: Bgp Summary for $hostname_router4" ./tests/bgp_summary.test.conf
screenshot_test $hostname_router4 "Test 3: VNI for $hostname_router4" ./tests/bgp_l2vpn_evpn.test.conf

screenshot_test $hostname_router2 "Test 4-1: VNI and route creation for $hostname_router2" ./tests/bgp_l2vpn_evpn.test.conf

{
	title "Test 4-2: Check for $hostname_host1 network config"

	target_container=$(select_container $hostname_host1)

	echo -e "/ # hostname"
	docker exec -i $target_container hostname

	echo -e "/ # ifconfig eth1"
	docker exec -i $target_container ifconfig eth1

	separator
}

screenshot_test $hostname_router4 "Test 5: VNI for $hostname_router4" ./tests/bgp_l2vpn_evpn.test.conf
screenshot_test $hostname_router2 "Test 6: VNI for $hostname_router2" ./tests/bgp_l2vpn_evpn.test.conf

{
	title "Test 7-1: Check for $hostname_host1 network config and ping 20.1.1.2"

	target_container=$(select_container $hostname_host1)

	echo -e "/ # hostname"
	docker exec -i $target_container hostname

	echo -e "/ # ping 20.1.1.2"
	docker exec -i $target_container ping -c3 20.1.1.2

	echo -e "/ # ifconfig eth1"
	docker exec -i $target_container ifconfig eth1

	separator
}

{
	title "Test 7-2: Check for $hostname_host3 network config"

	target_container=$(select_container $hostname_host3)

	echo -e "/ # hostname"
	docker exec -i $target_container hostname

	echo -e "/ # ifconfig eth0"
	docker exec -i $target_container ifconfig eth0

	separator
}
