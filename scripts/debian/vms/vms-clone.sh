#!/bin/bash
#----------------------------------------------------------------------
# Description : Clone VM
# Author      : Automatix <automatix@unattended.ch>
# Created at  : Sun Aug  8 11:41:04 UTC 2021
#
# (c) 2021 Automatix  All rights reserved.
#----------------------------------------------------------------------
#
if [ ! "$1" == "" ]; then
    NAME=$1
fi
if [ "$NAME" == "" ]; then
    vboxmanage list vms | sort
    printf "VMname to clone : "
    read NAME
fi
if [ "$NAME" == "" ]; then
    exit 0
fi
if [ "$NEW" == "" ]; then
    printf "New name for clone : "
    read NEW
fi
if [ "$NEW" == "" ]; then
    exit 0
fi
if [ ! "$NAME" == "" ]; then
    VBoxManage clonevm $NAME --name="$NEW" --register --mode=all
fi
