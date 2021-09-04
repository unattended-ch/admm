#!/bin/bash
#----------------------------------------------------------------------
# Description : Change memory size
# Author      : Automatix <automatix@unattended.ch>
# Created at  : Tue Aug 10 14:17:31 UTC 2021
#
# (c) 2021 Automatix  All rights reserved.
#----------------------------------------------------------------------
#
if [ "$1" == "" ]; then
    vboxmanage list vms | sort
    printf "VMname: "
    read VMNAME
else
    VMNAME=$1
fi
if [ "$2" == "" ]; then
    printf "Memorysize in GB: "
    read VMSIZE
else
    VMSIZE=$2
fi
if [ "$VMSIZE" == "" ]; then
    echo "Using: $0 VMName Memorysize"
    exit 1
else
    VMSIZE=$(($VMSIZE * 1024))
fi
CMD="modifyvm"
if [ ! "$VMNAME" == "" ]; then
    echo "Change [$VMNAME] disk size to [$VMSIZE] MB"
    VBoxManage $CMD $VMNAME --memory $VMSIZE
else
    echo "Using: $0 VMName Memorysize"
fi
