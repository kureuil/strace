#!/bin/bash
## syscall.sh for  in /home/querat_g/tmp/syscall
## 
## Made by querat_g
## Login   <querat_g@epitech.net>
## 
## Started on  Thu Apr  7 15:05:46 2016 querat_g
## Last update Fri Apr  8 11:07:48 2016 querat_g
##

#set -x

if [ ! -d man ]
then
    mkdir man
fi

function echolor { echo -e "$@"; }
function color() { echo -ne "$@";}

LRED="\e[1;31m";
RED="\e[0;31m";
LGREEN="\e[1;32m";
GREEN="\e[0;32m";
YELLOW="\e[1;33m";
BROWN="\e[0;33m";
BLUE="\e[1;34m";
PINK="\e[1;35m";
CYAN="\e[1;36m";
WHITE="\e[0m";

failFile=failedSyscalls.txt
echo "" > $failFile

listFile=$(find /usr/include -name unistd_64.h | head -n1)

listSysCalls="$(cat $listFile | grep __NR_)"

IFS="
"

for sysCall in $listSysCalls
do
    # on enlève le _NR__, les #define et autres crasses
    line=$(echo $sysCall | sed -E "s/__NR_//g" | sed -E "s/#define //g" | sed -E 's/64//g')
    
    
    sysCallId=$(echo $line | cut -d\  -f2)
    sysCallName=$(echo $line | cut -d\  -f1)

    # (rt_)sigaction et autres saletés en début de nom de fonction
    sysCallName=$(echo $sysCallName | sed -E 's/^rt_//g')

    # on ouvre le man
    sysCallManName=$(echo $sysCallName | sed -E 's/[0-9]+$//g' | sed -E 's/^rt_//g')
    echo $sysCallManName
    manFile="./man/$sysCallManName.man"
    echolor $CYAN"reading man $sysCallName"
    man 2 $sysCallName 1> $manFile 2> /dev/null

    # si il est pas trouvé, on gueule
    if [ ! -s $manFile ]
    then
	echolor $RED"man $sysCallName not found"$WHITE;
	echo $sysCallName >> $failFile
	continue
    fi;
    
    # récupération du man de son Synopsis à sa Description
    synopsisStart=$(cat $manFile | grep -n SYNOPSIS | cut -d ':' -f1)
    synopsisEnd=$(cat $manFile | grep -n DESCRIPTION | cut -d ':' -f1)
    protos=$(cat $manFile | sed -n "$synopsisStart, $synopsisEnd p ")
    
    # espaces multiples
    protos=$(echo $protos | sed -E 's/\s+/ /g')
    
    
    proto1=$(echo $protos | cut -d\; -f1 | egrep -o '((static|internal|extern)\s+)?([a-zA-Z0-9_]+)[\t ]+([a-zA-Z0-9_]+)\((.)+\)')
    proto2=$(echo $protos | cut -d\; -f2 | egrep -o '((static|internal|extern)\s+)?([a-zA-Z0-9_]+)[\t ]+([a-zA-Z0-9_]+)\((.)+\)')
    proto3=$(echo $protos | cut -d\; -f3 | egrep -o '((static|internal|extern)\s+)?([a-zA-Z0-9_]+)[\t ]+([a-zA-Z0-9_]+)\((.)+\)')
    proto4=$(echo $protos | cut -d\; -f4 | egrep -o '((static|internal|extern)\s+)?([a-zA-Z0-9_]+)[\t ]+([a-zA-Z0-9_]+)\((.)+\)')
    proto1=$(echo $protos | cut -d\; -f1 | egrep -o "([a-zA-Z0-9_]+)[\t ]+(\*)?([a-zA-Z0-9_]+)\((.)+\)")
    proto2=$(echo $protos | cut -d\; -f2 | egrep -o "([a-zA-Z0-9_]+)[\t ]+(\*)?([a-zA-Z0-9_]+)\((.)+\)")
    proto3=$(echo $protos | cut -d\; -f3 | egrep -o "([a-zA-Z0-9_]+)[\t ]+(\*)?([a-zA-Z0-9_]+)\((.)+\)")
    proto4=$(echo $protos | cut -d\; -f4 | egrep -o "([a-zA-Z0-9_]+)[\t ]+(\*)?([a-zA-Z0-9_]+)\((.)+\)")
    
    # on cherche ou se trouve le bon proto
    echo $proto1 | egrep "$sysCallName\(" > /dev/null
    proto1Match=$?
    echo $proto2 | egrep "$sysCallName\(" > /dev/null
    proto2Match=$?
    echo $proto3 | egrep "$sysCallName\(" > /dev/null
    proto3Match=$?
    echo $proto4 | egrep "$sysCallName\(" > /dev/null
    proto4Match=$?
    proto=""
    if [ $proto1Match -eq 0 ]
    then
     	proto=$proto1;
    elif [ $proto2Match -eq 0 ]
    then
     	proto=$proto2;
     	
    elif [ $proto3Match -eq 0 ]
    then
     	proto=$proto3;
    elif [ $proto4Match -eq 0 ]
    then
     	proto=$proto4;
    else
	echolor $LRED "Proto not found for $sysCallName !"
	echo $sysCallName >> $failFile
	# on sort de la boucle générale sans parser de proto pour cette fonction
	continue;
    fi

    # des fois il reste un bout du synopsis
    proto=$(echo $proto | egrep "([a-zA-Z0-9_]+)(\s+)(\*?)$sysCallName\(.*\)$")
    proto=$(echo $proto | sed -E "s/(.*>)//g")
    
    # Du coup, je décline toute responsabilité en cas de proto disparu 
    if [ -z $proto ]
    then
	echolor $LRED "Empty proto $sysCallName" $WHITE
	echo $sysCallName >> $failFile
	continue
    fi

    echolor $LGREEN "proto ! >> $proto" $WHITE;
    
    echo
done
