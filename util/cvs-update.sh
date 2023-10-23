#!/bin/sh
#
# Use this script to change the repository from one root to another
#
sed -is "s|$1|$2|" `find . -name Root`
exit
