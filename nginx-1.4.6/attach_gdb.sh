#!/bin/bash

pid=`ps aux | grep nginx | grep master | awk '{print $2}'`

if [ "$1" = "w" ]; then
    pid=`ps aux | grep nginx | grep worker | awk '{print $2}' | head -1`
fi
#echo $pid
sudo gdb ./nginx $pid