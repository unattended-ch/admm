#!/bin/bash
#----------------------------------------------------------------------
# Description : Edit VM configuration
# Author      : Automatix <automatix@unattended.ch>
# Created at  : Sun Aug  8 11:40:47 UTC 2021
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
    printf "VMname to edit : "
    read NAME
fi
if [ "$NAME" == "" ]; then
    exit 0
fi
if [ -f "$VMDIR/$NAME/$NAME.vbox" ]; then
    $EDITOR $VMDIR/$NAME/$NAME.vbox
else
    printf "File not found [$VMDIR/$NAME/$NAME.vbox] !\n"
fi
