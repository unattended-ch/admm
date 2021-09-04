#!/bin/bash
#----------------------------------------------------------------------
# Description : Stop running VMs
# Author      : Automatix <automatix@unattended.ch>
# Created at  : Sun Aug  8 11:38:31 UTC 2021
#
# (c) 2021 Automatix  All rights reserved.
#----------------------------------------------------------------------
#
RUN=$(vboxmanage list runningvms | cut -d " " -f1 | sed 's/"//g' | sort)
stop() {
    su -c "VBoxManage controlvm $1 acpipowerbutton" -s /bin/bash theuser
    while [ "`su -c 'VBoxManage list runningvms' -s /bin/bash theuser`" != "" ]
    do
        echo waiting for VMs to shutdown
        sleep 3
    done
}

for val in $RUN; do
    echo "Stopping VM [$val]"
    #vboxmanage controlvm $val poweroff soft
    vboxmanage controlvm $val acpipowerbutton
done
