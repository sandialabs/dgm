#!/bin/bash
# DGM Jenkins testing
#
# Jenkins defines the $WORKSPACE
# We need to define $DGM_HOME and $DGM_TPL
#

CUR_DIR="$( cd "$( dirname "$0" )" && pwd )"

host=`hostname -s`
if [ `uname` = "Linux" ]; then
  if [ $host = "face" ]; then
    source $CUR_DIR/dgm-env-setup-face.bsh
  elif [ $host = "curie2" ]; then
    source $CUR_DIR/dgm-env-setup-curie.bsh
  elif [[ $host = *"skybridge"* ]]; then
    source $CUR_DIR/dgm-env-setup-skybridge.bsh
  elif [[ $host = "gretel" ]]; then
    source $CUR_DIR/dgm-env-setup-sems.bsh
  else
    if [[ $host = *"redsky"* ]]; then
      source $CUR_DIR/dgm-env-setup-redsky.bsh
    fi
  fi
elif [ `uname` = "Darwin" ]; then
  if [ $host = "sol" ]; then
    export DGM_TPL=/tmp/Data/dgm/local
    export DGM_HOME=/tmp/Data/dgm/local/dgm
    export TRILINOS_HOME=/tmp/Data/dgm/local/trilinos
    export DYLD_LIBRARY_PATH=$DGM_TPL/boost/lib:$DYLD_LIBRARY_PATH
    export DYLD_LIBRARY_PATH=$DGM_TPL/fftw/lib:$DYLD_LIBRARY_PATH
    source $CUR_DIR/dgm-env-setup-sol.bsh
  else
    export DGM_TPL=/Users/dgm/local
    export DGM_HOME=/Users/dgm/local/dgm
    export TRILINOS_HOME=/home/dgm/local/trilinos
    export DYLD_LIBRARY_PATH=$DGM_TPL/boost/lib:$DYLD_LIBRARY_PATH
    export DYLD_LIBRARY_PATH=$DGM_TPL/fftw/lib:$DYLD_LIBRARY_PATH
    if [ $host = "terra" ]; then
      source $CUR_DIR/dgm-env-setup-terra.bsh
    fi
  fi
else
  echo Unknown OS `uname`
  exit 1
fi

# if [ -e build-utils/print.sh ]; then
  # build-utils/print.sh
# fi

# Start Testing
rm -rf TESTING 
mkdir TESTING
cd TESTING

# Run DGM tests
if [[ $host = *"redsky"* ]]; then
  runtests.py -s -q -p Runs-Tests -d $WORKSPACE/runs -a "-vpedc" -K Trilinos
elif [[ $host = *"skybridge"* ]]; then
  runtests.py -v -q -p Runs-Tests -d $WORKSPACE/runs -a "-vpedc"
elif [ $host = "curie1" ] || [ $host = "curie2" ]; then
  # pass -y to signal cray
  runtests.py -s -p Runs-Tests -d $WORKSPACE/runs -a "-vpedcy"
else 
  runtests.py -s -p Runs-Tests -d $WORKSPACE/runs -a "-vpedc" -S
fi

exit 0
