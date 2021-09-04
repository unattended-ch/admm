#!/bin/bash
#----------------------------------------------------------------------
# Description : Start mining pool for horizen
# Author      : Automatix <automatix@unattended.ch>
# Created at  : Wed Aug 11 12:20:41 UTC 2021
#
# (c) 2021 Automatix  All rights reserved.
#----------------------------------------------------------------------
#
COIN="Horizen1"
NOMP="PoolPrivate PoolPublic"
for var in $COIN; do
    echo "Starting VM [$var]"
    VBoxManage startvm $var --type headless
done
sleep 240
for var in $NOMP; do
    echo "Starting VM [$var]"
    VBoxManage startvm $var --type headless
done
