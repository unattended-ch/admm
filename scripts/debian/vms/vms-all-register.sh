#!/bin/bash
#----------------------------------------------------------------------
# Description : Register all VM's in $VMDIR on virtualbox
# Author      : Automatix <automatix@unattended.ch>
# Created at  : Tue Aug 10 14:15:34 UTC 2021
#
# (c) 2021 Automatix  All rights reserved.
#----------------------------------------------------------------------
#
if [ "$VMDIR" == "" ]; then
    VMDIR=/archiv/VMs
fi
FOUND=$(find $VMDIR/ -type f -name "*.vbox")
for VAR in $FOUND; do
    echo "Register [$VAR]"
    vboxmanage registervm $VAR
done
