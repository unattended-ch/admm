#!/bin/bashF
#----------------------------------------------------------------------
# Description: Internal functions for admm menu scripts
# Author: Automatix <github@unattended.ch>
# Created at: Sat Oct 31 00:55:09 UTC 2020
#
# (c) 2020 Automatix  All rights reserved.
#----------------------------------------------------------------------
#
TRN="-------------------------------------------------------------------------------"
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
        #MSG=$(echo "$1" | more)
        MSG=$1
        printf "%s\n%s\n%s\n" "$TRN" "$MSG" "$TRN"
    fi
}

#----------------------------------------------------------------------
# Function    : HEADER [message]
# Description : Display a header with message
# Parameters  : [message] Message to display
#----------------------------------------------------------------------
HEADER() {
	printf "%s\n%s\n%s\n" "$TRN" "--- $1" "$TRN"
}
#----------------------------------------------------------------------
# Function    : HHEADER [message]
# Description : Display a half header with message
# Parameters  : [message] Message to display
#----------------------------------------------------------------------
HHEADER() {
	printf "%s\n%s\n" "--- $1" "$TRN"
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
	HEADER "ADMin Menu (c) unattended.ch"
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
    PAC="$(basename $1)"
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
    PAC="$(basename $1)"
    FOUND=$(cat $2 | grep -m1 "^${PAC}")
    REPL="s/$FOUND/$PAC=$3/g"
    HEADER "$PAC [$FOUND]"
    if [ ! "$FOUND" == "" ]; then
        sed -i $REPL $2
        #sed -i '/$PAC=$LAST/c\/' $2
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
    curl --silent "https://api.github.com/repos/$1/releases/latest" -o $(pwd)/latest  # Get latest release from GitHub api
    VERS=$(cat $(pwd)/latest | grep '"tag_name":' | sed -E 's/.*"([^"]+)".*/\1/')             # Pluck JSON value
    rm -f $(pwd)/latest
}

#----------------------------------------------------------------------
# Function    : git_latest [repo name] [logfile]
# Description : Get latest version of github repository
#               Send email if new version is available
# Parameters  : [repo name]  Name of repository
#               [logfile]    Logfile name
#----------------------------------------------------------------------
git_latest() {
    curl --silent "https://api.github.com/repos/$1/releases/latest" -o $(pwd)/latest  # Get latest release from GitHub api
    VERS=$(cat $(pwd)/latest | grep '"tag_name":' | sed -E 's/.*"([^"]+)".*/\1/')             # Pluck JSON value
    BODY=$(cat $(pwd)/latest | grep '"body":' | sed -E 's/.*"([^"]+)".*/\1/')
    NAME=$(cat $(pwd)/latest | grep -m 1 '"name":' | sed -E 's/.*"([^"]+)".*/\1/')
    if [ "$NAME" == ": " ]; then
        NAME=$VERS
    fi
    git_version $1 $2 "$VERS"
    if [ ! "$VERS" == "$LAST" ]; then
        printf "GITHUB - NEW Version available [$1 - $VERS] !\n"
        if [ "$INFORM" == "" ]; then
            printf "$1\n$TRN\n$NAME\n$TRN\n$BODY\n$TRN\n"
        fi
        if [ ! "$INFORM" == "" ]; then
            send_email "$INFORM" "GITHUB - NEW Version available [$1 - $VERS] !\n" "$BODY"
        fi
        if [ ! "$INFORMCC" == "" ]; then
            send_email "$INFORMCC" "GITHUB - NEW Version available [$1 - $VERS] !\n" "$BODY"
        fi
    else
        printf "$1 - $VERS\nNothing new...\n"
    fi
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
