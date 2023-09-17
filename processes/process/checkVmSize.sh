#!/bin/bash

egrep '(^VmSize|^VmRSS)' /proc/$1/status