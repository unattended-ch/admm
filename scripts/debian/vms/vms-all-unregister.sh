#!/bin/bash
#----------------------------------------------------------------------
# Description : Unregister all VMs in $VMDIR
# Author      : Automatix <automatix@unattended.ch>
# Created at  : Tue Aug 10 14:16:00 UTC 2021
#
# (c) 2021 Automatix  All rights reserved.
#----------------------------------------------------------------------
#
if [ "$VMDIR" == "" ]; then
    VMDIR=/archiv/VMs
fi
FOUND=$(find $VMDIR/ -type f -name "*.vbox")
for VAR in $FOUND; do
    echo "Unregister [$VAR]"
    vboxmanage unregistervm $VAR
done
