#!/bin/bash
#----------------------------------------------------------------------
# Description : Unregister VM on virtualbox
# Author      : Automatix <automatix@unattended.ch>
# Created at  : Tue Aug 10 14:15:15 UTC 2021
#
# (c) 2021 Automatix  All rights reserved.
#----------------------------------------------------------------------
#
if [ "$VMDIR" == "" ]; then
    VMDIR=/archiv/VMs
fi
NAME=$1
if [ "$NAME" == "" ]; then
    FOUND=$(find $VMDIR/ -type f -name "*.vbox")
    printf "$FOUND\n\nEnter name : "
    read NAME
fi
if [ ! "$NAME" == "" ]; then
    vboxmanage unregistervm "$NAME"
else
    echo "Using : $0 VMname"
fi
