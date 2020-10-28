#!/bin/bash
MAN=admm.man
RED=../README.md
LNG="de fr"

PAR="-f man -k 10"
for VAR in $LNG; do
    if [ -f "$VAR/admm.po" ]; then
        echo "$VAR/admm.po"
        po4a-translate $PAR -m $MAN -p $VAR/admm.po -l $VAR/admm.man
    fi
done

PAR="-f text -k 10"
for VAR in $LNG; do
    if [ -f "$VAR/README.po" ]; then
        echo "$VAR/README.po"
        po4a-translate $PAR -m $RED -p $VAR/README.po -l $VAR/README.md
    fi
done
