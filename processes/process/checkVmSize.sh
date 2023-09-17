#!/bin/bash

for (( ; ; ))
do
    egrep '(^VmSize|^VmRSS)' /proc/$1/status;
    sleep 1
done
