#!/bin/bash
#
# Fix the Boost dynamic library names for the parts of Boost needed by DGM
# Author:    S. Scott Collis
# Date:      12/3/2019
# Copyright: Sandia National Laboratories
# 
# NOTE:  must be run in the installed boost/lib directory
#
# Initial condition 
#
echo
echo Initial Boost configuration
otool -L libboost_filesystem.dylib
otool -L libboost_system.dylib
otool -L libboost_serialization.dylib
otool -L libboost_mpi.dylib
otool -L libboost_random.dylib
otool -L libboost_program_options.dylib
#
# boost_filesystem
#
install_name_tool -id $PWD/libboost_filesystem.dylib libboost_filesystem.dylib
install_name_tool -change libboost_system.dylib $PWD/libboost_system.dylib libboost_filesystem.dylib
#
# boost_system
#
install_name_tool -id $PWD/libboost_system.dylib libboost_system.dylib
#
# boost_serialization
#
install_name_tool -id $PWD/libboost_serialization.dylib libboost_serialization.dylib
#
# boost_mpi
#
install_name_tool -id $PWD/libboost_mpi.dylib libboost_mpi.dylib
install_name_tool -change libboost_serialization.dylib $PWD/libboost_serialization.dylib libboost_mpi.dylib
#
# boost_random
#
install_name_tool -id $PWD/libboost_random.dylib libboost_random.dylib
install_name_tool -change libboost_system.dylib $PWD/libboost_system.dylib libboost_random.dylib
#
# boost_program_options
#
install_name_tool -id $PWD/libboost_program_options.dylib libboost_program_options.dylib
#
# Verify changes
#
echo
echo
echo Final Boost configuration
otool -L libboost_filesystem.dylib
otool -L libboost_system.dylib
otool -L libboost_serialization.dylib
otool -L libboost_mpi.dylib
otool -L libboost_random.dylib
otool -L libboost_program_options.dylib
