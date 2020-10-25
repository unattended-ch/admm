#!/bin/bash
. $INC
set_starttime
sudo apt clean -y
sudo apt autoremove -y
elapsed $START
