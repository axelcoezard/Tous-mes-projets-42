#!/bin/bash

PURPLE="\e[1;35m"
YELLOW="\e[1;33m"
ENDCOLOR="\e[0m"

echo -e "${PURPLE}--------- ${YELLOW}Creating \"iot\" cluster ${PURPLE}---------${ENDCOLOR}"

sudo k3d cluster delete iot
sudo k3d cluster create iot

echo -e "${PURPLE}--------- ${YELLOW}Creating namespaces ${PURPLE}---------${ENDCOLOR}"

sudo kubectl create namespace argocd
sudo kubectl create namespace dev

echo -e "${PURPLE}--------- ${YELLOW}Installing argocd ${PURPLE}---------${ENDCOLOR}"

sudo kubectl apply -n argocd -f https://raw.githubusercontent.com/argoproj/argo-cd/stable/manifests/install.yaml

echo -e "${PURPLE}--------- ${YELLOW}Waiting for all pods to start. ${PURPLE}---------${ENDCOLOR}"

ready=$(sudo kubectl get pods -n argocd | grep Running | wc -l)

while [ $ready != 7 ]
do
    echo "$ready/7 pods are running"
    sleep 10
    ready=$(sudo kubectl get pods -n argocd | grep Running | wc -l)
done

echo -e "${PURPLE}--------- ${YELLOW}All pods started. ${PURPLE}---------${ENDCOLOR}"
echo -e "${PURPLE}--------- ${YELLOW}Forwarding server port ${PURPLE}---------${ENDCOLOR}"

sudo kubectl port-forward -n argocd svc/argocd-server 8080:443 &>/dev/null &

echo -e "${PURPLE}--------- ${YELLOW}You can now connect on localhost:8080 ${PURPLE}---------${ENDCOLOR}"

username="admin"
password=$(sudo kubectl -n argocd get secret argocd-initial-admin-secret -o jsonpath="{.data.password}" | base64 -d)

echo -e "${PURPLE}--------- ${YELLOW}Login with default credentials : $username:$password ${PURPLE}---------${ENDCOLOR}"

argocd login localhost:8080 \
	--insecure \
	--username $username \
	--password $password

echo -e "${PURPLE}--------- ${YELLOW}Update password to : inception ${PURPLE}---------${ENDCOLOR}"

argocd account update-password \
	--current-password $password \
	--new-password "inception"

password="inception"

echo -e "${PURPLE}--------- ${YELLOW}Creating \"wil\" app ${PURPLE}---------${ENDCOLOR}"

argocd app delete wil -y \
	--insecure \
	--server localhost:8080 &>/dev/null

sleep 5

argocd app create wil \
	--insecure \
	--repo https://github.com/Kalinololo/asebrech-iot-deploy.git \
	--dest-server https://kubernetes.default.svc \
	--dest-namespace dev \
	--path . \
	--server localhost:8080

argocd app set wil \
	--sync-policy automated --self-heal --auto-prune

argocd app sync wil \
	--insecure \
	--server localhost:8080

ready=$(sudo kubectl get pods -n dev | grep Running | wc -l)

while [ $ready != 1 ]
do
    sleep 5
    ready=$(sudo kubectl get pods -n dev | grep Running | wc -l)
done

while [ true ]
do
    sudo kubectl port-forward svc/wil -n dev 8888:8888
    sleep 5
done
