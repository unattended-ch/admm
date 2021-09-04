#!/bin/bash
#----------------------------------------------------------------------
# Description : Restart running VMs
# Author      : Automatix <automatix@unattended.ch>
# Created at  : Sun Aug  8 11:39:57 UTC 2021
#
# (c) 2021 Automatix  All rights reserved.
#----------------------------------------------------------------------
#
RUN=$(vboxmanage list runningvms | cut -d " " -f1 | sed 's/"//g' | sort)
stop() {
    sudo -c "VBoxManage controlvm $1 acpipowerbutton" -s /bin/bash $USER
    while [ "`sudo -c 'VBoxManage list runningvms' -s /bin/bash $USER`" != "" ]
    do
        echo "Waiting for [$1] to shutdown"
        sleep 3
    done
}
for val in $RUN; do
    echo "Stopping VM [$val]"
    #vboxmanage controlvm $val poweroff soft
    vboxmanage controlvm $val acpipowerbutton
    sleep 3
done
sleep 5
for val in $RUN; do
    echo "Starting VM [$val]"
    VBoxManage startvm $val --type headless
    sleep 3
done
