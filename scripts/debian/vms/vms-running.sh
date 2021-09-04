#!/bin/bash
#----------------------------------------------------------------------
# Description : List running VMs
# Author      : Automatix <automatix@unattended.ch>
# Created at  : Sun Aug  8 11:37:46 UTC 2021
#
# (c) 2021 Automatix  All rights reserved.
#----------------------------------------------------------------------
#
VBoxManage list runningvms | sort
