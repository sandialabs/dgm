#!/bin/bash
if [ $VERBOSE ]; then
  set -x
fi
sed "s/__REVISION__/`cat $1`/" < $2 > $3
exit
