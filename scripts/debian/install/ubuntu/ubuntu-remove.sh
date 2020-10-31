#!/bin/bash
#----------------------------------------------------------------------
# Description: Remove no longer needed packages
# Author: Automatix <github@unattended.ch>
# Created at: Sat Oct 31 16:18:59 UTC 2020
#
# (c) 2020 Automatix  All rights reserved.
#----------------------------------------------------------------------
#
. $INC
sudo apt clean -y 2>/dev/null
sudo apt autoremove -y 2>/dev/null
