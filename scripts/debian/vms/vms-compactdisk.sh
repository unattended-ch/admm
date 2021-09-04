#!/bin/bash
#----------------------------------------------------------------------
# Description : Compact VDI file
# Author      : Automatix <automatix@unattended.ch>
# Created at  : Tue Aug 10 14:18:36 UTC 2021
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
CMD="modifymedium disk"
VDD=$VMDIR/$VMNAME/$VMNAME.vdi
if [ ! "$VMNAME" == "" ]; then
    echo "Compact [$VDD]"
    VBoxManage $CMD "$VDD" --compact
else
    echo "Using: $0 VMName"
fi
