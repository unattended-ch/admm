#!/bin/bash
#----------------------------------------------------------------------
# Description: Internals for admm menu scripts
# Author: Automatix <github@unattended.ch>
# Created at: Sat Oct 31 00:55:09 UTC 2020
#
# (c) 2020 Automatix  All rights reserved.
#----------------------------------------------------------------------
#
TRN="--------------------------------------------------------------------------------------------"
export GPG_TTY=$(tty)
export DISPLAY=:0.0
#----------------------------------------------------------------------
# Function    : pushd [folder]
# Description : Remove messages from pushd
# Parameters  : [folder] Folder to push
#----------------------------------------------------------------------
pushd() {
	command pushd "$@" > /dev/null
}

#----------------------------------------------------------------------
# Function    : popd
# Description : Remove messages from popd
# Parameters  :
#----------------------------------------------------------------------
popd() {
	command popd "$@" > /dev/null
}

#----------------------------------------------------------------------
# Function    : INFO [message]
# Description : Display info message if $DEBUG=1
# Parameters  : [message] Message to display
#----------------------------------------------------------------------
INFO() {
    if [ "$DEBUG" == "1" ]; then
        #MSG=$(printf "$1")
        MSG=$(echo "$1")
        printf "%s\n%s\n%s\n" "$TRN" "$MSG" "$TRN"
    fi
}

#----------------------------------------------------------------------
# Function    : HEADER [message]
# Description : Display a header with message
# Parameters  : [message] Message to display
#----------------------------------------------------------------------
HEADER() {
    MSG=$(printf "$1")
    printf "%s\n%s\n%s\n" "$TRN" "--- $MSG" "$TRN"
}

#----------------------------------------------------------------------
# Function    : HHEADER [message]
# Description : Display a half header with message
# Parameters  : [message] Message to display
#----------------------------------------------------------------------
HHEADER() {
    MSG=$(printf "$1")
    printf "%s\n%s\n" "--- $MSG" "$TRN"
}

#----------------------------------------------------------------------
# Function    : HEADER [message]
# Description : Display a header with pseudo picture
# Parameters  : [message] Message to display
#----------------------------------------------------------------------
PHEADER() {
    MSG=$(printf "$1")
    printf "%s\n%s\n" "$MSG" "$TRN"
}

#----------------------------------------------------------------------
# Function    : finish
# Description : Display finish message
# Parameters  :
#----------------------------------------------------------------------
finish() {
    HEADER "Finished"
}

#----------------------------------------------------------------------
# Function    : src_exists
# Description : Check if $SRC is defined else set pwd
# Parameters  : none
#----------------------------------------------------------------------
src_exists() {
	if [ "$SRC" == "" ]; then
		SRC=$(pwd)
	fi
}

#----------------------------------------------------------------------
# Function    : build_exists
# Description : Check if $BUILD is defined else exit with error
# Parameters  : none
#----------------------------------------------------------------------
build_exists() {
	if [ "$BUILD" == "" ]; then
		echo "BUILD is not defined !"
		exit 1
	else
		echo "BUILD=$BUILD"
	fi
}

#----------------------------------------------------------------------
# Function    : stick_exists
# Description : Check if $STICK is defined else exit with error
# Parameters  : none
#----------------------------------------------------------------------
stick_exists() {
	if [ "$STICK" == "" ]; then
		echo "STICK is not defined !"
		exit 1
	else
		echo "STICK=$STICK"
	fi
}

#----------------------------------------------------------------------
# Function    : set_now
# Description : Define variable $NOW with aktual time
# Parameters  : 
#----------------------------------------------------------------------
set_now() {
	NOW=$(date "+%Y.%m.%d %H:%M")
}

#----------------------------------------------------------------------
# Function    : folder_exists_old [folder]
# Description : If folder exists rename it to folder_YYYYMMDD_HHMM
# Parameters  : [folder] Folder to search
#----------------------------------------------------------------------
folder_exists_old() {
	if [ -d "$1" ]; then
		DT=$(date +%Y%m%d_%H%M)
		echo "Move folder [$1] to [$1_$DT]"
		mv $1 $1_$DT
	fi
}

#----------------------------------------------------------------------
# Function    : press_any_key
# Description : PressAnyKey message
# Parameters  : none
#----------------------------------------------------------------------
press_any_key() {
    printf "\nPress any key to continue\n"
    while [ true ] ; do
      read -t 3 -n 1
      if [ $? = 0 ] ; then
        #clear
        exit 0
      fi
    done
}

#----------------------------------------------------------------------
# Function    : wait_any_key
# Description : Wait for key press
# Parameters  : none
#----------------------------------------------------------------------
wait_any_key() {
    while [ true ] ; do
      read -t 3 -n 1
      if [ $? = 0 ] ; then
        exit 0
      fi
    done
}

#----------------------------------------------------------------------
# Function    : intro
# Description : Display intro header
# Parameters  : none
#----------------------------------------------------------------------
intro() {
    if [ -f "$PLG/logo/intro.logo" ]; then
        PHEADER "$(cat $PLG/logo/intro.logo)"
    else
        HEADER "ADMin Menu (c) unattended.ch"
    fi
}

#----------------------------------------------------------------------
# Function    : onlymsg [comment]
# Description : Display only last error message
# Parameters  : [comment]
#----------------------------------------------------------------------
onlymsg() {
	if [ $? -gt 0 ]; then
		echo "ERROR : $1"
	else
		echo "DONE"
	fi
}

#----------------------------------------------------------------------
# Function    : errmsg [comment]
# Description : Display last error message and terminate
# Parameters  : [comment]
#----------------------------------------------------------------------
errmsg() {
	if [ $? -gt 0 ]; then
		echo "ERROR : $1"
		exit $?
	fi
}

#------------------------------------------------------------------------------------------
retval() {
	if [ $? -gt 0 ]; then
		echo "ERROR : $1"
		exit $?
	else
		echo "DONE"
	fi
}

#------------------------------------------------------------------------------------------
calc() {
    awk "BEGIN { print "$*" }";
}

#----------------------------------------------------------------------
# Function    : set_starttime
# Description : Define variable $START with actual time
# Parameters  : none
#----------------------------------------------------------------------
set_starttime() {
	export START=$(date +%s)
}

#----------------------------------------------------------------------
# Function    : elapsed [$START]
# Description : Display elapsed time
# Parameters  : [$START] variable must be set with set_starttime()
#----------------------------------------------------------------------
elapsed() {
    if [ ! "$1" == "" ]; then
        ENDE=$(date +%s)
        T=$(($ENDE - $1))
        printf '\nTime elapsed : %02d:%02d:%02d:%02d\n' $((T/86400)) $((T/3600%24)) $((T/60%60)) $((T%60))
    fi
}

#----------------------------------------------------------------------
# Function    : send_email [email] [subject] [body]
# Description : Send email with new versions found
# Parameters  : [email]    Email address to send
#               [subject]  Subject text
#               [body]     Body text
#----------------------------------------------------------------------
send_email() {
    # Check if SSMTP or MSMTP is installed
    RUN="no"
    DST=~
    SSMTP=$(sudo ls /etc/ssmtp/ssmtp.conf)
    if [ ! "$SSMTP" == "" ]; then
        RUN="yes"
    fi
    if [ -f "$DST/.msmtprc" ]; then
        RUN="yes"
    fi
    if [ ! "$1" == "" ]; then
        if [ "$2" == "" ]; then
            SUB="No subject"
        else
            SUB=$2
        fi
        if [ "$RUN" == "yes" ]; then
            if [ "$4" == "" ]; then
                printf "To: $1\nSubject: $SUB\n\n$3" | /usr/sbin/sendmail $1
            else
                CONTENT="$(cat $PLG/template/email.tmpl)"
                CONTENT=${CONTENT/(TO)/$1}
                CONTENT=${CONTENT/(SUB)/$SUB}
                CONTENT=${CONTENT/(BODY)/$3}
                FNAME=$(basename $4)
                CONTENT=${CONTENT//(NAME)/$FNAME}
                ATTACH=$(uuencode --base64 $4 $FNAME | tail -n +2)
                CONTENT=${CONTENT/(ATTACH)/$ATTACH}
                #printf "$CONTENT" > $PWD/email.msg
                #printf "%s" "$CONTENT"
                printf "$CONTENT" | /usr/sbin/sendmail $1
                retval "SENDMAIL"
            fi
        else
            echo "You must first install SSMTP or MSMTP to send emails."
        fi
    else
        echo "No Recipients specified !"
    fi
}

#----------------------------------------------------------------------
# Function    : read_last_date [reponame] [logfile]
# Description : Read last date from logfile
# Parameters  : [repo name]  Name of repository
#               [logfile]    Logfile name
#----------------------------------------------------------------------
read_last_date() {
    #PAC="$(basename $1)"
    PAC=$(echo $1 | sed 's/\//_/g')
    DT=$(cat $2 | grep ^$PAC | cut -d '=' -f 2)
    if [ ! "$DT" == "" ]; then
        export LAST=$DT
    else
        export LAST=
    fi
}


#----------------------------------------------------------------------
# Function    : git_update_log  [version]
# Description : Update logfile with new version
# Parameters  : [repo name]  Name of repository
#               [logfile]    Logfile name
#               [version]    New version found
#----------------------------------------------------------------------
git_update_log() {
    #PAC="$(basename $1)"
    PAC=$(echo $1 | sed 's/\//_/g')
    FOUND=$(cat $2 | grep -m1 "^${PAC}")
    REPL="s/$FOUND/$PAC=$3/g"
    #HEADER "$PAC [$FOUND]"
    if [ ! "$FOUND" == "" ]; then
        sed -i $REPL $2
    else
        echo "$PAC=$3" >> $2
    fi
}

#----------------------------------------------------------------------
# Function    : git_version [reponame] [logfile] [version]
# Description : Get version of github repository
# Parameters  : [repo name]  Name of repository
#               [logfile]    Logfile name
#               [version]    New version found
#----------------------------------------------------------------------
git_version() {
    read_last_date $1 $2
    git_update_log $1 $2 $3
}

#----------------------------------------------------------------------
# Function    : git_ver [repo name]
# Description : Get version of github repository
# Parameters  : [repo name]  Name of repository
#----------------------------------------------------------------------
git_ver() {
    if [ ! -f "$(pwd)/latest" ]; then
        curl --silent "https://api.github.com/repos/$1/releases/latest" -o $(pwd)/latest  # Get latest release from GitHub api
    fi
    VERS=$(cat $(pwd)/latest | jq '.tag_name' | sed 's/\"//g' | sed 's/v//g')
    #NAME=$(cat $(pwd)/latest | jq '.name' | sed 's/\"//g')
    BODY=$(cat $(pwd)/latest | jq '.body' | sed 's/\"//g')
    PUBL=$(cat $(pwd)/latest | jq '.published_at' | sed 's/\"//g' | sed 's/[T|Z]/ /g')
    if [ "$NAME" == ": " ]; then
        NAME=$1
    fi
    rm -f $(pwd)/latest
}

#----------------------------------------------------------------------
# Function    : git_latest [repo name] [logfile]
# Description : Get latest version of github repository
#               Send email if new version is available
# Parameters  : [repo name]  Name of repository
#               [logfile]    Logfile name for version storage
#----------------------------------------------------------------------
git_latest() {
    if [ ! -f "$(pwd)/latest" ]; then
        curl --silent "https://api.github.com/repos/$1/releases/latest" -o $(pwd)/latest  # Get latest release from GitHub api
    fi
    VERS=$(cat $(pwd)/latest | jq '.tag_name' | sed 's/\"//g' | sed 's/v//g')
    #NAME=$(cat $(pwd)/latest | jq '.name' | sed 's/\"//g')
    BODY=$(cat $(pwd)/latest | jq '.body' | sed 's/\"//g')
    PUBL=$(cat $(pwd)/latest | jq '.published_at' | sed 's/\"//g' | sed 's/[T|Z]/ /g')
    #if [ "$NAME" == "" ]; then
        NAME=$1
    #fi
    git_version $1 $2 "$VERS"
    if [ ! "$VERS" == "$LAST" ]; then
        printf "GITHUB - NEW Version available [$NAME - $VERS] !\n"
        if [ "$INFORM" == "" ]; then
            printf "\n$TRN\n$NAME [$VERS] $PUBL\n$TRN\n$BODY\n$TRN\n"
        fi
        if [ ! "$INFORM" == "" ]; then
            send_email "$INFORM" "GITHUB NEW Version [$NAME - $VERS] $PUBL !\n" "\n$NAME [$VERS] $PUBL\n$BODY\n"
        fi
        if [ ! "$INFORMCC" == "" ]; then
            send_email "$INFORMCC" "GITHUB NEW Version [$NAME - $VERS] $PUBL !\n" "\n$NAME [$VERS] $PUBL\n$BODY\n"
        fi
    else
        printf "$NAME - $VERS\nNothing new...\n"
    fi
    rm -f $(pwd)/latest
}

#----------------------------------------------------------------------
# Function    : git_counter [repo name] [logfile]
# Description : Get counters of github repository
#               Send email if new version is available
# Parameters  : [repo name]  Name of repository
#               [logfile]    Logfile name for version storage
#----------------------------------------------------------------------
git_counter() {
    if [ ! -f "$(pwd)/latest" ]; then
        curl --silent "https://api.github.com/repos/$1/releases/latest" -o $(pwd)/latest  # Get latest release from GitHub api
    fi
    VERS=$(cat $(pwd)/latest | jq '.tag_name' | sed 's/\"//g' | sed 's/v//g')
    BODY=$(cat $(pwd)/latest | egrep '"name"|"download_count"')
    PUBL=$(cat $(pwd)/latest | jq '.published_at' | sed 's/\"//g' | sed 's/[T|Z]/ /g')
    #if [ "$NAME" == "" ]; then
        NAME=$1
    #fi
    printf "$VERS\n$PUBL\n$BODY\n\n"
    rm -f $(pwd)/latest
}

#----------------------------------------------------------------------
# Function    : is_mounted [folder]
# Description : Check if [folder] is mounted and return value in $MOUNTED
# Parameters  : [folder] Folder to check
#----------------------------------------------------------------------
is_mounted() {
    export MOUNTED="$(mount | grep $1)"
}

#----------------------------------------------------------------------
# Function    : get_network_device
# Description : Get list of network device
# Parameters  : none
#----------------------------------------------------------------------
get_network_device() {
    export ETHER=$(sudo ifconfig | grep -E "bond|eth|en" | head -n1 | awk '{print $1}' | tr ":" " ")
}

#----------------------------------------------------------------------
# Function    : purge_files [folder/filename.ext]
# Description : Purge give files and let only latest version
# Parameters  : [folder/filename.ext] Wildcards are allowed
#----------------------------------------------------------------------
purge_files() {
    if [ ! "$1" == "" ]; then
        LIST=$(ls $1 2>/dev/null | sort -r | tail -n +2)
        INFO "$LIST"
        if [ ! "$LIST" == "" ]; then
            for VAR in $LIST; do
                sudo rm -vf $VAR
            done
        fi
    fi
}

#----------------------------------------------------------------------
# Function    : read_input [message] [default]
# Description : Display a message and wait for key input
#               Return [default] if only enter is pressed
# Parameters  : [message] Message to display "$MSG [$DEF] : "
#               [default] Default value
#----------------------------------------------------------------------
read_input() {
    MSG=$1
    DEF=$2
    if [ "$MSG" == "" ]; then
        MSG=""
    fi
    printf "$MSG [$DEF] : "
    read INPUT
    if [ "$INPUT" == "" ]; then
        INPUT=$DEF
    fi
    printf "\n"
}

#----------------------------------------------------------------------
# Function    : log [file] [msg]
# Description : Add entry to log file
# Parameters  : [file] Log file name
#               [msg]  Message to add
#----------------------------------------------------------------------
log() {
    if [ ! "$1" == "" ]; then
        DT=$(date +%Y.%m.%d %H:%M:%s)
        printf "%s : %s" "$DT" "$2" | tee -a $1
    fi
}

#----------------------------------------------------------------------
# Function    : crontab_header [username]
# Description : Append header to crontab if not exists
# Parameters  : [username] Username
#----------------------------------------------------------------------
crontab_header() {
    EXISTS=$(sudo grep '# Example of job definition' /var/spool/cron/crontabs/$1)
    if [ "$EXISTS" == "" ]; then
    HEADER "Adding header"
    crontab -l ; (cat <<EOT) | crontab -
# Mail address for cron jobs
MAILTO=""
#
# Example of job definition:
# .---------------- minute (0 - 59)
# |  .------------- hour (0 - 23)
# |  |  .---------- day of month (1 - 31)
# |  |  |  .------- month (1 - 12) OR jan,feb,mar,apr ...
# |  |  |  |  .---- day of week (0 - 6) (Sunday=0 or 7) OR sun,mon,tue,wed,thu,fri,sat
# |  |  |  |  |
# *  *  *  *  * user-name command to be executed
EOT
    fi
}

#----------------------------------------------------------------------
# Function    : crontab_add [username] [shedule] [script]
# Description : Add entry to user crontab
# Parameters  : [username] Username
#               [shedule] See above for example
#               [script]  Full /path/filename.sh
#----------------------------------------------------------------------
crontab_add() {
INFO "User : $1\nTime : $2\nFile : $3"
FNAME=${3##*/}
EXISTS=$(sudo grep "$FNAME" /var/spool/cron/crontabs/$1)
if [ "$EXISTS" == "" ]; then
    (crontab -l ; echo "$2 $3 2>>/dev/null")| crontab -
fi
}

#----------------------------------------------------------------------
# Function    : update_apt
# Description : run apt update if the last run was more than 60 seconds
# Parameters  : none
#----------------------------------------------------------------------
update_apt() {
if [ -f "/var/lib/apt/periodic/update-success-stamp" ]; then
    # Get last apt update success time
    LAST=$(sudo date -r /var/lib/apt/periodic/update-success-stamp +%s)
    NOW=$(date +%s)
    DIFF=$(($NOW-$LAST))
    # If it's more than 1 minute reload it
    if [ "$DIFF" -gt "60" ]; then
        sudo apt update 2>/dev/null
    fi
else
    sudo apt update 2>/dev/null
fi
sudo apt list --upgradable 2>/dev/null
}

#----------------------------------------------------------------------
# Function    : errtrap
# Description : Catch trap and exit
# Parameters  : 
#----------------------------------------------------------------------
errtrap() {
    echo "Exit from errtrap()"
    exit 0
}

#----------------------------------------------------------------------
# Function    : set_errtrap 
# Description : Set trap for trap events
#               For a list of events use "trap -l"
# Parameters  : [trapnum] List of trap numbers eg. "1 2 3 6 9"
#----------------------------------------------------------------------
set_errtrap() {
    if [ "$1" == "" ]; then
        TRP="1 2 3 6 9"
    else
        TRP=$1
    fi
    trap errtrap $TRP
}

#----------------------------------------------------------------------
# Function    : load_globals [incfile]
# Description : Load global variables from admm
# Parameters  : [incfile] File name eg. "$INC"
#----------------------------------------------------------------------
load_globals() {
    GLOBALS=$(dirname $1)/globals.inc
    . $GLOBALS
}

#----------------------------------------------------------------------
# Function    : load_inc [folder]
# Description : Load .inc files from menu subfolder
# Parameters  : [folder] Menu subfolder to search
#----------------------------------------------------------------------
load_inc() {
    FOUND=$(ls $1/*.inc)
    INFO "$FOUND"
    if [ ! "$FOUND" == "" ]; then
        for VAR in $FOUND; do
            INCL="$VAR"
            . $INCL
        done
    fi
}

#----------------------------------------------------------------------
# Function    : clear_empty_files [folder]
# Description : Clear empty (zero size) files recursively from [folder]
# Parameters  : [folder]
#----------------------------------------------------------------------
clear_empty_files() {
    if [ ! "$1" == "" ]; then
        find $1 -name '*' -size 0 -exec rm {} \;
    fi
}

#----------------------------------------------------------------------
# Function    : php_version
# Description : Read PHP version
# Parameters  : none
#----------------------------------------------------------------------
php_version() {
    FOUND=$(php --version)
    if [ ! "$FOUND" == "" ]; then
        PHPVER=$(echo $FOUND | grep PHP | head -n1 | awk '{print $2}' | tr '-' ' ' | awk '{print $1}' | tr '.' ' ' | awk '{print $1"."$2}')
        echo "$PHPVER"
    fi
}
