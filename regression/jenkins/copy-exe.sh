# Copy executables and utilities for general use

if [ `uname` = "Linux" ]; then
  export DGM_HOME=/home/dgm
  export LD_LIBRARY_PATH=$DGM_HOME/local/lib:$DGM_HOME/local/openmpi/lib:\
/usr/local/gcc-4.3.1/lib64:$LD_LIBRARY_PATH
  export DGM_GROUP=dgm
elif [ `uname` = "Darwin" ]; then
  export DGM_HOME=/Users/dgm
  export DGM_GROUP=wg-dgm
else
  echo Unknown OS `uname`
  exit 1
fi

if [ ! -d $DGM_HOME/bin ]; then
  mkdir $DGM_HOME/bin
fi
cd ../GCC
cp -p *.exe $DGM_HOME/bin
cd ../GCCp
cp -p *.exe $DGM_HOME/bin
cd ../util
cp -r dgm_clean dgm_test dgm2tec dgm2p3d dgm2aux ctl2tec /home/dgm/bin

chgrp $DGM_GROUP $DGM_HOME/bin/*

exit 0