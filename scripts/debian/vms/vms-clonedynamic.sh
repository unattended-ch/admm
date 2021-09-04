#!/bin/bash
#----------------------------------------------------------------------
# Description : Change allocation from dynamic to static
# Author      : Automatix <automatix@unattended.ch>
# Created at  : Tue Aug 10 14:19:09 UTC 2021
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
NEW=$VMDIR/$VMNAME/$VMNAME-fixed.vdi
if [ ! "$VMNAME" == "" ]; then
    echo "Clone [$VDD] to [$NEW]"
    VBoxManage $CMD "$VDD" "$NEW" --variant Fixed
else
    echo "Using: $0 VMName"
fi
