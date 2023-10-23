

if [ $# != 1 ]; then
  echo "$0: $# arguments when 1 is required!"
  exit 1
fi

# Install
# GCC  - serial gcc 
# GCCd - debug serial gcc 
# GCCp - parallel MPI gcc 
if [[ ("$1" == "GCC") || ("$1" == "GCCd") || ("$1" == "GCCp") ]]; then
  export COMP=$1
else
  echo "$0: $1 is an invalid install option."
  exit 1
fi


if [ `uname` = "Linux" ]; then
  export DGM_HOME=/home/dgm
  export DGM_GROUP=dgm
  export LD_LIBRARY_PATH=$DGM_HOME/local/lib:$DGM_HOME/local/openmpi/lib:/usr/local/gcc-4.3.1/lib64:$LD_LIBRARY_PATH
  export PATH=$WORKSPACE/$COMP:$WORKSPACE/util:$DGM_HOME/local/openmpi/bin:$PATH
elif [ `uname` = "Darwin" ]; then
  export DGM_HOME=/Users/dgm
  export DGM_GROUP=wg-dgm
  export PATH=$HOME/local/flex/bin:$WORKSPACE/$COMP:$WORKSPACE/util:$HOME/local/openmpi/bin:$PATH
else
  echo Unknown OS `uname`
  exit 1
fi


if [ -e build-utils/print.sh ]; then
  build-utils/print.sh
fi


if [ -d $DGM_HOME ]; then
  if [ ! -d $DGM_HOME/dgm ]; then
    mkdir $DGM_HOME/dgm
  fi
  chgrp -R $DGM_GROUP $DGM_HOME/dgm
  chmod -R g+rwx $DGM_HOME/dgm

  rm -rf $DGM_HOME/dgm/$COMP.tmp
  mkdir $DGM_HOME/dgm/$COMP.tmp
  cp -p $COMP/*.exe $DGM_HOME/dgm/$COMP.tmp
  rm -rf $DGM_HOME/dgm/$COMP
  mv $DGM_HOME/dgm/$COMP.tmp $DGM_HOME/dgm/$COMP
  chgrp -R $DGM_GROUP $DGM_HOME/dgm/$COMP
  chmod -R g+rwx $DGM_HOME/dgm/$COMP
  
  rm -rf $DGM_HOME/dgm/util.tmp
  mkdir $DGM_HOME/dgm/util.tmp
  chgrp $DGM_GROUP $DGM_HOME/dgm/util.tmp
  chmod g+rwx $DGM_HOME/dgm/util.tmp
  cd util
  for f in *
  do
    if [ $f != 'CVS' ]; then
      cp -p $f $DGM_HOME/dgm/util.tmp
      chgrp $DGM_GROUP $DGM_HOME/dgm/util.tmp/$f
      if [ -x $DGM_HOME/dgm/util.tmp/$f ]; then
        chmod 770 $DGM_HOME/dgm/util.tmp/$f
      else
        chmod 660 $DGM_HOME/dgm/util.tmp/$f
      fi
    fi
  done
  cd ..
  rm -rf $DGM_HOME/dgm/util.tmp/CVS
  rm -rf $DGM_HOME/dgm/util
  mv $DGM_HOME/dgm/util.tmp $DGM_HOME/dgm/util
fi

exit 0
