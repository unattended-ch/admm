#!/bin/bash
#----------------------------------------------------------------------
# Description : Start all autostart VMs
# Author      : Automatix <automatix@unattended.ch>
# Created at  : Sun Aug  8 11:40:17 UTC 2021
#
# (c) 2021 Automatix  All rights reserved.
#----------------------------------------------------------------------
#
. $INC
export GPG_TTY=$(tty)
PWD=$(pwd)
DST=~
HEADER "$SWD/vms/vms-startauto.sh"
FOUND=$(find $VMDIR -type f -name *.box | sort)
FOUND=$(vboxmanage list vms | cut -d " " -f1 | sed 's/"//g' | sort)
echo "$FOUND"
for VAR in $FOUND; do
    AUTO=$(cat $VMDIR/$VAR/$VAR.vbox | grep Autostart | grep true)
    if [ ! "$AUTO" == "" ]; then
        echo "Starting $VAR..."
        VBoxManage startvm $VAR --type headless
        sleep 3
    fi
done