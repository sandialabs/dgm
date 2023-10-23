#!/bin/bash
#
# This sets the proper name (id) of dylibs
# on Mac OS X
#
for f in $( ls *.dylib ); do
  install_name_tool -id `pwd -P`/$f $f
done
#
# boost_filesystem depends on boost_system so you need to do this too
#
install_name_tool -change libboost_system.dylib \
 `pwd -P`/libboost_system.dylib libboost_filesystem.dylib
install_name_tool -change libboost_serialization.dylib \
  `pwd -P`/libboost_serialization.dylib libboost_mpi.dylib 
exit
