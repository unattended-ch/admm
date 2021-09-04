#!/bin/bash
#----------------------------------------------------------------------
# Description : Display VM informations
# Author      : Automatix <automatix@unattended.ch>
# Created at  : Sun Aug  8 11:41:19 UTC 2021
#
# (c) 2021 Automatix  All rights reserved.
#----------------------------------------------------------------------
#
if [ "$VMDIR" == "" ]; then
    VMDIR=/archiv/VMs
fi
if [ ! "$1" == "" ]; then
    NAME=$1
fi
if [ "$NAME" == "" ]; then
    vboxmanage list vms | sort
    printf "VMname to view : "
    read NAME
fi
if [ "$NAME" == "" ]; then
    exit 0
fi
vboxmanage showvminfo $NAME
