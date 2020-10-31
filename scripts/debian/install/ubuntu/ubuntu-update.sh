#!/bin/bash
#----------------------------------------------------------------------
# Description: Upgrade distribution
# Author: Automatix <github@unattended.ch>
# Created at: Sat Oct 31 16:19:22 UTC 2020
#
# (c) 2020 Automatix  All rights reserved.
#----------------------------------------------------------------------
#
. $INC
if [ -f "/var/lib/apt/periodic/update-success-stamp" ]; then
    # Get last apt update success time
    LAST=$(sudo date -r /var/lib/apt/periodic/update-success-stamp +%s)
    NOW=$(date +%s)
    DIFF=$(($NOW-$LAST))
    # If it's more than 1 hour reload it
    if [ "$DIFF" -gt "60" ]; then
        sudo apt update 2>/dev/null
    fi
else
    sudo apt update 2>/dev/null
fi
sudo apt dist-upgrade -y 2>/dev/null
