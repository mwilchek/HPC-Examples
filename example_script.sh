#!/bin/bash

echo "You are :" `whoami`
echo "The time is :" `date +%s`
echo "The system load is currently :" `uptime`
echo "There are currently "`who|wc -l`" users logged into "`hostname`"."
