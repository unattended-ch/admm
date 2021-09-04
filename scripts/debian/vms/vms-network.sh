#!/bin/bash
#----------------------------------------------------------------------
# Description : Change network card
# Author      : Automatix <automatix@unattended.ch>
# Created at  : Tue Aug 10 14:16:35 UTC 2021
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
    printf "Device [bond0]: "
    read VMDEV
    if [ "$VMDEV" == "" ]; then
	VMDEV=bond0
    fi
else
    VMDEV=$2
fi
RUN=$(vboxmanage list runningvms | grep "$VMNAME" | cut -d " " -f1 | sed 's/"//g')
CMD=modifyvm
if [ ! "$RUN" == "" ]; then
    CMD=controlvm
fi
if [ ! "$VMNAME" == "" ]; then
    echo "Change [$VMNAME] to [$VMDEV]"
    VBoxManage $CMD $VMNAME --bridgeadapter1 $VMDEV
else
    echo "Using: $0 VMName eth0"
fi
