#!/bin/bash
#----------------------------------------------------------------------
# Description : Change boot order
# Author      : Automatix <automatix@unattended.ch>
# Created at  : Tue Aug 10 14:17:48 UTC 2021
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
    printf "1. --boot1 disk --boot2 none --boot3 none --boot4 none\n"
    printf "2. --boot1 disk --boot2 dvd --boot3 none --boot4 none\n"
    printf "3. --boot1 net --boot2 disk --boot3 none --boot4 none\n"
    printf "4. --boot1 dvd --boot2 disk --boot3 none --boot4 none\n"
    printf "Select Bootorder [] :"
    read BOOT
    if [ "$BOOT" == "1" ]; then
	BOOT="--boot1 disk --boot2 none --boot3 none --boot4 none"
    fi
    if [ "$BOOT" == "2" ]; then
	BOOT="--boot1 disk --boot2 dvd --boot3 none --boot4 none"
    fi
    if [ "$BOOT" == "3" ]; then
	BOOT="--boot1 net --boot2 disk --boot3 none --boot4 none"
    fi
    if [ "$BOOT" == "4" ]; then
	BOOT="--boot1 dvd --boot2 disk --boot3 none --boot4 none"
    fi
else
    BOOT=$2
fi
if [ "$BOOT" == "" ]; then
    exit 1
fi
CMD="modifyvm"
if [ ! "$VMNAME" == "" ]; then
    echo "Change [$VMNAME] Bootorder to [$BOOT]"
    VBoxManage $CMD $VMNAME $BOOT
else
    echo "Using: $0 VMName Bootorder"
fi
