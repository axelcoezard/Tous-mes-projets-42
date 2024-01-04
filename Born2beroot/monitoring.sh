#!/bin/bash

architecture=`uname -a`
pCPU=`grep "physical id" /proc/cpuinfo | wc -l`
vCPU=`grep "processor" /proc/cpuinfo | wc -l`
memory=`free -m | awk 'NR==2{printf "%s/%sMB (%.2f%%)", $3,$2,$3*100/$2 }'`
disk=`df -h | awk '$NF=="/"{printf "%d/%dGB (%s)", $3,$2,$5}'`
lCPU=`top -bn1 | grep load | awk '{printf "%.1f%%\n", $(NF-2) * 100}'`
lastboot=`who -b | cut -c23-`
lvmuse=`lsblk |grep lvm | awk '{if ($1) {print "yes";exit;} else {print "no"} }'`
tcp=`netstat -an | grep ESTABLISHED |  wc -l`
userlog=`who | cut -d " " -f 1 | sort -u | wc -l`
networkIP=`hostname -I`
networkMAC=`ip a | grep link/ether | cut -d ' ' -f6`
sudo=`journalctl _COMM=sudo | grep COMMAND | wc -l`

wall $'#Achitecture:' "$architecture" \
$'\n#CPU physical :' "$pCPU" \
$'\n#vCPU :' "$vCPU" \
$'\n#Memory Usage:' "$memory" \
$'\n#Disk Usage:' "$disk"\
$'\n#CPU Load:' "$lCPU"\
$'\n#Last boot:' "$lastboot" \
$'\n#LVM use:' "$lvmuse"\
$'\n#Connexions TCP :' "$tcp"\
$'\n#User log:' "$userlog"\
$'\n#Network: IP' "$networkIP"'('"$networkMAC"')' \
$'\n#Sudo :' "$sudo"

