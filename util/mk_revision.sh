#!/bin/bash
if [ $VERBOSE ]; then
  set -x
fi
if [ $# -ne 1 ]; then
  echo "Usage:  $0 <dir>"
  exit 1
fi
#
# Check if git or svn repository
#
export ISGIT=`git -C $1 rev-parse 2>/dev/null; echo $?`
#echo $ISGIT
#
# GIT repository
#
if [ $ISGIT == 0 ]; then
  if [[ -e revision ]]; then
    git -C $1 rev-parse HEAD > revision-new
    diff revision revision-new
    if [[ $? == 1 ]]; then
      mv revision-new revision
    else
      rm revision-new
    fi
  else
    git -C $1 rev-parse HEAD > revision-new
    mv revision-new revision
  fi
else
#
# SVN repository
#
  if [[ -e revision ]]; then
    svnversion $1 > revision-new
    diff revision revision-new
    if [[ $? == 1 ]]; then
      mv revision-new revision
    else
      rm revision-new
    fi
  else
    svnversion $1 > revision-new
    mv revision-new revision
  fi
fi
exit
