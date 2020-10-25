#!/bin/bash
. $INC
set_starttime
if [ -f "/var/lib/apt/periodic/update-success-stamp" ]; then
    # Get last apt update success time
    LAST=$(sudo date -r /var/lib/apt/periodic/update-success-stamp +%s)
    NOW=$(date +%s)
    DIFF=$(($NOW-$LAST))
    # If it's more than 1 hour reload it
    if [ "$DIFF" -gt "60" ]; then
        sudo apt update
    fi
else
    sudo apt update
fi
sudo apt dist-upgrade -y
elapsed $START
