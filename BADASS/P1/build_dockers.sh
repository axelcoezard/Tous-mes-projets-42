#!/bin/bash

# Define paths to the directories containing the Dockerfiles
ALPINE_BUSYBOX_PATH="./dockers/alpine_busybox"
FRR_PATH="./dockers/frr"

# Define the names of the Docker images
HOST_IMAGE_NAME="host_jbertin"
ROUTER_IMAGE_NAME="routeur_jbertin"

# Define color codes
RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m' # No Color

build_docker_image()
{
	local dockerfile_path=$1
	local image_name=$2
	cd "$dockerfile_path" ||
	{
		echo -e "${RED}Error: Unable to access the directory '$dockerfile_path'.${NC}"
		exit 1
	}
	docker build -t "$image_name" -f Dockerfile . > /dev/null 2>&1 ||
	{
		echo -e "${RED}Error: Failed to build the Docker image '$image_name' at '$dockerfile_path'.${NC}"
		exit 1
	}
	cd - > /dev/null 2>&1 ||
	{
		echo -e "${RED}Error: Unable to return to the previous directory.${NC}"
		exit 1
	}
	echo -e "${GREEN}The Docker image '$image_name' was successfully built.${NC}"
}

build_docker_image "$ALPINE_BUSYBOX_PATH" "$HOST_IMAGE_NAME"
build_docker_image "$FRR_PATH" "$ROUTER_IMAGE_NAME"

echo -e "${GREEN}All Docker images have been successfully built.${NC}"
