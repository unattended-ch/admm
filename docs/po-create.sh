#!/bin/bash
MAN=admm.man
RED=../README.md
LNG="de fr"
PAR="-f man"
for VAR in $LNG; do
    if [ ! -f "$VAR/admm.po" ]; then
        echo "$VAR/admm.po"
        po4a-gettextize $PAR -m $MAN -p $VAR/admm.po
    fi
done
PAR="-f text"
for VAR in $LNG; do
    if [ ! -f "$VAR/README.po" ]; then
        echo "$VAR/README.po"
        po4a-gettextize $PAR -m $RED -p $VAR/README.po
    fi
done
