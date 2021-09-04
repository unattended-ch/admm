#!/bin/bash
#----------------------------------------------------------------------
# Description : Export VDI file to ISO
# Author      : Automatix <automatix@unattended.ch>
# Created at  : Tue Aug 10 14:18:51 UTC 2021
#
# (c) 2021 Automatix  All rights reserved.
#----------------------------------------------------------------------
#
. $INC
DST=~
HHEADER "$SWD/vms/vms-toiso.sh"
if [ "$1" == "" ]; then
    vboxmanage list vms | sort
    printf "VMname: "
    read VMNAME
else
    VMNAME=$1
fi
VDD=$VMDIR/$VMNAME/$VMNAME.vdi
ISO=$ISODIR/$VMNAME.iso
if [ -f "$ISO" ]; then
    sudo rm -vf $ISO
fi
if [ ! "$VMNAME" == "" ]; then
    HEADER "Input  [$VDD]"
    HHEADER "Output [$ISO]"
    VBoxManage clonehd "$VDD" "$ISO" --format RAW
fi
