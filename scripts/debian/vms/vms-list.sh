#!/bin/bash
#----------------------------------------------------------------------
# Description : List all VMs
# Author      : Automatix <automatix@unattended.ch>
# Created at  : Sun Aug  8 11:37:30 UTC 2021
#
# (c) 2021 Automatix  All rights reserved.
#----------------------------------------------------------------------
#
vboxmanage list vms | sort
