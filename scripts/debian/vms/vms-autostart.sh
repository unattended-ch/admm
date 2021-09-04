#!/bin/bash
#----------------------------------------------------------------------
# Description : Set autostart ON or OFF for VM
# Author      : Automatix <automatix@unattended.ch>
# Created at  : Tue Aug 10 14:18:07 UTC 2021
#
# (c) 2021 Automatix  All rights reserved.
#----------------------------------------------------------------------
#
LIST=""
MODE="on"
if [ ! "$1" == "" ]; then
    MODE=$1
fi
if [ ! "$2" == "" ]; then
    LIST=$2
fi
if [ "$LIST" == "" ]; then
    vboxmanage list vms | sort
    printf "VMname: "
    read LIST
fi
for var in $LIST; do
    echo "Autostart VM [$var] $MODE"
    VBoxManage modifyvm $var --autostart-enabled $MODE --autostop-type acpishutdown
done
