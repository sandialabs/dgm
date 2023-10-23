#!/bin/bash
#echo $1
sysctl -a | grep "machdep.cpu.*features.*" | grep $1 >> /dev/null
STATUS=$?
if [ $STATUS == 0 ]; then
  echo 1
else
  echo 0
fi
exit $STATUS 
