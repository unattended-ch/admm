#!/bin/bash
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
    echo "$VERS"
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
        LIST=$(ls $1 | sort -r | tail -n +2)
        if [ ! "$LIST" == "" ]; then
            for VAR in $LIST; do
                sudo rm -vf $VAR
            done
        fi
    fi
}

#----------------------------------------------------------------------
# Function    : mysql_exec_root [sqlquery]
# Description : Execute mysql query as root
# Parameters  : [sqlquery]
#----------------------------------------------------------------------
mysql_exec_root() {
    if [ "$STATS" == "" ]; then
        STATS=localhost
    fi
    if [ ! "$1" == "" ]; then
mysql --host=$STATS --user=root --password=$PAS admm  << EOF
$1
EOF
    fi
}

#----------------------------------------------------------------------
# Function    : mysql_exec [sqlquery]
# Description : Execute mysql query
# Parameters  : [sqlquery]
#----------------------------------------------------------------------
mysql_exec() {
    if [ "$STATS" == "" ]; then
        STATS=localhost
    fi
    if [ ! "$1" == "" ]; then
mysql --host=$STATS --user=support --password=$PAS admm  << EOF
$1
EOF
    fi
}

#----------------------------------------------------------------------
# Function    : stats_check_text
# Description : 
# Parameters  : 
#----------------------------------------------------------------------
stats_check_text() {
    stats_text $1
    if [ "$TEXTID" == "" ]; then
        #echo "Text does not exists in the database"
        stats_check_text="$(cat $PLG/template/admm-newtext.tmpl)"
        stats_check_text=${stats_check_text/(TEXT)/$1}
        #echo "$stats_check_text"
        mysql_exec "$stats_check_text"
        stats_text "$1"
    fi
}

#----------------------------------------------------------------------
# Function    : stats_text
# Description : 
# Parameters  : 
#----------------------------------------------------------------------
stats_text() {
    if [ ! "$1" == "" ]; then
        stats_text="$(cat $PLG/template/admm-text.tmpl)"
        stats_text=${stats_text/(TEXT)/$1}
        #echo "$stats_text"
        export TEXTID=$(mysql_exec "$stats_text" | tail -n +2)
        #echo "$TEXTID"
    fi
}

#----------------------------------------------------------------------
# Function    : stats_add_user
# Description : 
# Parameters  : 
#----------------------------------------------------------------------
stats_add_user() {
    stats_check_user="$(cat $PLG/template/admm-checkuser.tmpl)"
    FOUND=$(mysql_exec_root "$stats_check_user")
    HEADER "$FOUND"
    if [ "$FOUND" == "1" ]; then
        stats_check_database=$(cat $PLG/template/admm-base.tmpl)
        #echo "$stats_check_database"
        DATABASE=$(mysql_exec "$stats_check_database")
        echo "$DATABASE"
        if [ "$DATABASE" == "" ]; then
            stats_add_database="$(cat $PLG/template/admm-newbase.tmpl)"
            mysql_exec "$stats_add_database"
        fi
    else
        stats_add_user="$(cat $PLG/template/admm-adduser.tmpl)"
        mysql_exec_root "$stats_add_user"
    fi
}

#----------------------------------------------------------------------
# Function    : stats_check_database
# Description : 
# Parameters  : 
#----------------------------------------------------------------------
stats_check_database() {
    stats_check_database="$(cat $PLG/template/admm-base.tmpl)"
    #echo "$stats_check_database"
    DATABASE=$(mysql_exec "$stats_check_database")
    echo "$DATABASE"
    if [ "$DATABASE" == "" ]; then
        stats_check_database="$(cat $PLG/template/admm-newbase.tmpl)"
        mysql_exec "$stats_check_database"
    fi
}

#----------------------------------------------------------------------
# Function    : stats_check_host
# Description : 
# Parameters  : 
#----------------------------------------------------------------------
stats_check_host() {
    #stats_check_database
    stats_host
    if [ "$HOSTID" == "" ]; then
        #echo "Host does not exists in the database"
        CONTENT="$(cat $PLG/template/admm-newhost.tmpl)"
        CONTENT=${CONTENT/(HOST)/$(hostname)}
        #echo "$CONTENT"
        mysql_exec "$CONTENT"
        stats_host
    fi
}

#----------------------------------------------------------------------
# Function    : stats_host
# Description : 
# Parameters  : 
#----------------------------------------------------------------------
stats_host() {
    CONTENT="$(cat $PLG/template/admm-host.tmpl)"
    CONTENT=${CONTENT/(HOST)/$(hostname)}
    #echo "$CONTENT"
    export HOSTID=$(mysql_exec "$CONTENT" | tail -n +2)
    #echo "$HOSTID"
}

#------------------------------------------------------------------------------------------
stats_cpu() {
    stats_check_host
    TM=1
    if [ ! "$1" = "" ]; then
        TM=$1
    fi
    USE=$(echo $[100-$(vmstat 1 $TM|tail -1|awk '{print $15}')])
    CONTENT="$(cat $PLG/template/admm-cpu.tmpl)"
    CONTENT=${CONTENT/(HOST)/$HOSTID}
    CONTENT=${CONTENT/(DATA)/$USE}
    #echo "$CONTENT"
    if [ ! "$USE" == "" ]; then
        echo "CPU : $USE%"
        mysql_exec "$CONTENT"
    fi
}

#------------------------------------------------------------------------------------------
stats_disk() {
    stats_check_host
    USE=$(df -k | grep sd | awk '{print $1" "$5" "$6}')
    if [ ! "$USE" == "" ]; then
        while IFS= read -r line; do
            echo "$line"
            DEV=$(echo "$line" | awk '{print $1}')
            SIZ=$(echo "$line" | awk '{print $2}')
            FOL=$(echo "$line" | awk '{print $3}')
            CONTENT="$(cat $PLG/template/admm-disk.tmpl)"
            CONTENT=${CONTENT/(HOST)/$HOSTID}
            stats_check_text "$DEV"
            CONTENT=${CONTENT/(DEVICE)/$TEXTID}
            stats_check_text "$FOL"
            CONTENT=${CONTENT/(FOLDER)/$TEXTID}
            CONTENT=${CONTENT/(DATA)/${SIZ//%}}
            #echo "$CONTENT"
            mysql_exec "$CONTENT"
        done < <(printf '%s\n' "$USE")
    fi
}

#------------------------------------------------------------------------------------------
stats_mem() {
    stats_check_host
    MAX=$(cat /proc/meminfo | grep MemTotal: | awk '{print $2}')
    FREE=$(cat /proc/meminfo | grep MemAvailable: | awk '{print $2}')
    #echo "$MAX"
    #echo "$FREE"
    ONE=$(calc 100/$MAX)
    USE=$(calc $MAX-$FREE)
    USE=$(calc $ONE*$USE | tr "." " " | awk '{print $1}')
    if [ ! "$USE" == "" ]; then
        echo "MEM : $USE%"
        CONTENT="$(cat $PLG/template/admm-mem.tmpl)"
        CONTENT=${CONTENT/(HOST)/$HOSTID}
        CONTENT=${CONTENT/(DATA)/$USE}
        #echo "$CONTENT"
        mysql_exec "$CONTENT"
    fi
}

#------------------------------------------------------------------------------------------
stats_net() {
    stats_check_host
    get_network_device
    TM=1
    if [ ! "$1" = "" ]; then
        TM=1
    fi
    USE=$(ifstat -i $ETHER $TM 1 | tail -n +3)
    #echo "$USE"
    IN=$(echo $USE | awk '{print $1}')
    OUT=$(echo $USE | awk '{print $2}')
    ONE=$(calc 100/125000)
    #echo "$ONE"
    #echo "$IN"
    #echo "$OUT"
    IN=$(calc $ONE*$IN | tr "." " " | awk '{print $1}')
    OUT=$(calc $ONE*$OUT | tr "." " " | awk '{print $1}')
    if [ ! "$USE" == "" ]; then
        echo "$ETHER : IN=$IN% OUT=$OUT%"
        CONTENT="$(cat $PLG/template/admm-net.tmpl)"
        CONTENT=${CONTENT/(HOST)/$HOSTID}
        CONTENT=${CONTENT/(IN)/$IN}
        CONTENT=${CONTENT/(OUT)/$OUT}
        #echo "$CONTENT"
        mysql_exec "$CONTENT"
    fi
}

#------------------------------------------------------------------------------------------
stats_sensors() {
    stats_check_host
    USE=$(sensors)
    CPU=$(sensors | grep "CPU Temperature" | awk '{print $3}')
    IPMI=$(sudo ipmitool sdr list full 2>/dev/null)
    echo "$IPMI"
    if [ "$CPU" == "" ]; then
        CPU=$(sensors | grep "Package id 0:" | awk '{print $4}')
    fi
    CPU=${CPU/+/}
    CPU=${CPU/°C/}
    CPU=$(echo $CPU | tr "." " " | awk '{print $1}')
    FANRPM=$(sensors | grep "CPU FAN Speed" | awk '{print $4}')
    FANMAX=$(sensors | grep "CPU FAN Speed" | awk '{print $12}')
    if [ ! "$FANRPM" == "" ]; then
        FAN=$(calc 100/$FANMAX*$FANRPM)
        FAN=$(echo "$FAN" | tr "." " " | awk '{print $1}')
    else
        FAN="0"
    fi
    FAN1=$(echo "$IPMI" | grep "Fan1 RPM" | awk '{print $4}')
    FAN2=$(echo "$IPMI" | grep "Fan2 RPM" | awk '{print $4}')
    FAN3=$(echo "$IPMI" | grep "Fan3 RPM" | awk '{print $4}')
    FAN4=$(echo "$IPMI" | grep "Fan4 RPM" | awk '{print $4}')
    FAN5=$(echo "$IPMI" | grep "Fan5 RPM" | awk '{print $4}')
    FAN6=$(echo "$IPMI" | grep "Fan6 RPM" | awk '{print $4}')
    CHASSIS=$(echo "$IPMI" | grep "Temp" | head -1 | awk '{print $4}')
    INLET=$(echo "$IPMI" | grep "Inlet Temp" | awk '{print $4}')
    EXHAUST=$(echo "$IPMI" | grep "Exhaust Temp" | awk '{print $4}')
    POWER=$(echo "$IPMI" | grep "Pwr Consumption" | awk '{print $4}')
    if [ "$FAN1" == "" ]; then
        FAN1=0
    fi
    if [ "$FAN2" == "" ]; then
        FAN2=0
    fi
    if [ "$FAN3" == "" ]; then
        FAN3=0
    fi
    if [ "$FAN4" == "" ]; then
        FAN4=0
    fi
    if [ "$FAN5" == "" ]; then
        FAN5=0
    fi
    if [ "$FAN6" == "" ]; then
        FAN6=0
    fi
    if [ "$CHASSIS" == "" ]; then
        CHASSIS=0
    fi
    if [ "$INLET" == "" ]; then
        INLET=0
    fi
    if [ "$EXHAUST" == "" ]; then
        EXHAUST=0
    fi
    if [ "$POWER" == "" ]; then
        POWER=0
    fi
    FAN1=$(calc "100/12000*$FAN1")
    FAN1=$(echo "$FAN1" | tr "." " " | awk '{print $1}')
    FAN2=$(calc "100/12000*$FAN2")
    FAN2=$(echo "$FAN2" | tr "." " " | awk '{print $1}')
    FAN3=$(calc "100/12000*$FAN3")
    FAN3=$(echo "$FAN3" | tr "." " " | awk '{print $1}')
    FAN4=$(calc "100/12000*$FAN4")
    FAN4=$(echo "$FAN4" | tr "." " " | awk '{print $1}')
    FAN5=$(calc "100/12000*$FAN5")
    FAN5=$(echo "$FAN5" | tr "." " " | awk '{print $1}')
    FAN6=$(calc "100/12000*$FAN6")
    FAN6=$(echo "$FAN6" | tr "." " " | awk '{print $1}')
    POWER=$(calc "100/980*$POWER")
    POWER=$(echo "$POWER" | tr "." " " | awk '{print $1}')
    if [ ! "$USE" == "" ]; then
        echo "CPU     : $CPU °C"
        echo "FAN     : $FAN %"
        echo "FAN1    : $FAN1 %"
        echo "FAN2    : $FAN2 %"
        echo "FAN3    : $FAN3 %"
        echo "FAN4    : $FAN4 %"
        echo "FAN5    : $FAN5 %"
        echo "FAN6    : $FAN6 %"
        echo "CHASSIS : $CHASSIS °C"
        echo "INLET   : $INLET °C"
        echo "EXHAUST : $EXHAUST °C"
        echo "POWER   : $POWER %"
        CONTENT="$(cat $PLG/template/admm-sensors.tmpl)"
        CONTENT=${CONTENT/(HOST)/$HOSTID}
        CONTENT=${CONTENT/(CPU)/$CPU}
        CONTENT=${CONTENT/(FAN0)/$FAN}
        CONTENT=${CONTENT/(FAN1)/$FAN1}
        CONTENT=${CONTENT/(FAN2)/$FAN2}
        CONTENT=${CONTENT/(FAN3)/$FAN3}
        CONTENT=${CONTENT/(FAN4)/$FAN4}
        CONTENT=${CONTENT/(FAN5)/$FAN5}
        CONTENT=${CONTENT/(FAN6)/$FAN6}
        CONTENT=${CONTENT/(CHASSIS)/$CHASSIS}
        CONTENT=${CONTENT/(INLET)/$INLET}
        CONTENT=${CONTENT/(EXHAUST)/$EXHAUST}
        CONTENT=${CONTENT/(POWER)/$POWER}
        #echo "$CONTENT"
        mysql_exec "$CONTENT"
    fi
}

#----------------------------------------------------------------------
# Function    : coin_price [coin] [currency]
# Description : Get crypto coin price from coingecko.com
# Parameters  : [coin]     Name of the coin
#               [currency] Currency
#----------------------------------------------------------------------
coin_price() {
    if [ ! "$1" == "" ]; then
        COIN="$1"
    else
        COIN=bitcoin
    fi
    if [ ! "$2" == "" ]; then
        CURR="$2"
    else
        CURR=chf
    fi
    URL="https://api.coingecko.com/api/v3/simple/price?ids=$COIN&vs_currencies=$CURR"
    RES=$(curl --silent $URL)
    RES=${RES//-/}
    #echo "$RES"
    COIN=${COIN//,/ }
    COIN=${COIN//-/}
    CURR=${CURR//,/ }
    #echo "$COIN"
    #echo "$RES" | jq '.'
    for CUR in $CURR; do
        for VAR in $COIN; do
            echo "--------------------------------"
            NAME=.$VAR.$CUR
            #echo "$NAME"
            PRICE=$(echo "$RES" | jq $NAME)
            echo "$VAR = $PRICE $CUR"
        done
    done
    echo "--------------------------------"
}
