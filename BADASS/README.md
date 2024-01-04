# BADASS (Bgp At Doors of Autonomous Systems is Simple)

## Definitions

### GNS3: Graphical Network Simulator-3

GNS3, short for Graphical Network Simulator-3, is a widely-used software for simulating and designing networks. It offers a virtual platform that mirrors real-world network environments. With its user-friendly interface, GNS3 supports a broad spectrum of devices from major vendors like Cisco and Juniper. It can integrate with virtual machines to emulate intricate network setups and provides real-time simulation to aid in understanding and diagnosing network configurations. Catering to both students and seasoned professionals, GNS3 stands as an essential tool for network planning, testing, and troubleshooting.

----

## Prerequisites

#### 1. Add Docker's official GPG key:
````
sudo apt-get update
sudo apt-get install ca-certificates curl gnupg
sudo install -m 0755 -d /etc/apt/keyrings
curl -fsSL https://download.docker.com/linux/ubuntu/gpg | sudo gpg --dearmor -o /etc/apt/keyrings/docker.gpg
sudo chmod a+r /etc/apt/keyrings/docker.gpg
````

#### 2. Add the repository to Apt sources:
````
echo \
  "deb [arch="$(dpkg --print-architecture)" signed-by=/etc/apt/keyrings/docker.gpg] https://download.docker.com/linux/ubuntu \
  "$(. /etc/os-release && echo "$VERSION_CODENAME")" stable" | \
  sudo tee /etc/apt/sources.list.d/docker.list > /dev/null
sudo apt-get update
````

#### 3. Install Docker
````
sudo apt-get install docker-ce docker-ce-cli containerd.io docker-buildx-plugin docker-compose-plugin
````

#### 4. Configure Docker Sudo
````
sudo groupadd docker
sudo usermod -aG docker ${USER}
````

#### 5. Install GNS3 :
````
sudo add-apt-repository ppa:gns3/ppa
sudo apt update
sudo apt install gns3-gui gns3-server
````

----

[Part 1: GNS3 configuration with Docker](./P1/README.md)

[Part 2: Discovering a VXLAN](./P2/README.md)

[Part 3: Discovering BGP with EVPN](./P3/README.md)
