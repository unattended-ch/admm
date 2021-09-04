#!/bin/bash
#----------------------------------------------------------------------
# Description : Change allocation from static to dynamic
# Author      : Automatix <automatix@unattended.ch>
# Created at  : Tue Aug 10 14:19:38 UTC 2021
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
CMD="clonemedium disk"
VDD=$VMDIR/$VMNAME/$VMNAME.vdi
NEW=$VMDIR/$VMNAME/$VMNAME-standard.vdi
if [ ! "$VMNAME" == "" ]; then
    echo "Clone [$VDD] to [$NEW]"
    VBoxManage $CMD "$VDD" "$NEW" --variant Standard
else
    echo "Using: $0 VMName"
fi
