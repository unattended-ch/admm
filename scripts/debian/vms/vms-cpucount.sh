#!/bin/bash
#----------------------------------------------------------------------
# Description : Change CPU count
# Author      : Automatix <automatix@unattended.ch>
# Created at  : Tue Aug 10 14:17:19 UTC 2021
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
if [ "$2" == "" ]; then
    printf "CPU count: "
    read VMCPUS
else
    VMCPUS=$2
fi
if [ "$VMCPUS" == "" ]; then
    echo "Using: $0 VMName CPUs"
    exit 1
fi
CMD=modifyvm
if [ ! "$VMNAME" == "" ]; then
    echo "Change [$VMNAME] CPU count to [$VMCPUS]"
    VBoxManage $CMD $VMNAME --cpus $VMCPUS
else
    echo "Using: $0 VMName CPUs"
fi
