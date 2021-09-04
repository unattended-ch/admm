#!/bin/bash
#----------------------------------------------------------------------
# Description : Start VM
# Author      : Automatix <automatix@unattended.ch>
# Created at  : Sun Aug  8 11:38:04 UTC 2021
#
# (c) 2021 Automatix  All rights reserved.
#----------------------------------------------------------------------
#
LIST=""
if [ ! "$1" == "" ]; then
    LIST=$1
fi
if [ "$LIST" == "" ]; then
    vboxmanage list vms | sort
    printf "VMname's with space: "
    read LIST
fi
for var in $LIST; do
    echo "Starting VM [$var]"
    VBoxManage startvm $var --type headless
done
