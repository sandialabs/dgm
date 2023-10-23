# -*- cmake -*-

cmake_minimum_required(VERSION 2.8)

project(Unit_FDM)

#######################################################
# Initialize serial, parallel and debugging directories
#######################################################
if (SERIAL)
  set(PARALLEL_DIR    serial)
  set(PARALLEL_PREFIX ""    )
else()
  set(PARALLEL_DIR    mpi)
  set(PARALLEL_PREFIX p  )
endif()
if(CMAKE_BUILD_TYPE STREQUAL "DEBUG")
  set(OPT_DIR debug)
else()
  set(OPT_DIR opt)
endif()

#####################
# Initialize Trilinos
#####################
set(Trilinos_HOME $ENV{HOME}/local/trilinos
  CACHE PATH "Top-level path name for Trilinos installation, typically containing serial and mpi directories")
set(Trilinos_PREFIX ${Trilinos_HOME}/${PARALLEL_DIR}/${OPT_DIR}
  CACHE PATH "Trilinos installation directory containing include, lib, etc.")
#include(${Trilinos_PREFIX}/lib/cmake/Trilinos/TrilinosConfig.cmake)
#message(STATUS "Trilinos_LIBRARIES=${Trilinos_LIBRARIES}")

# Use Trilinos_PREFIX, if the user set it, to help find Trilinos.
# The final location will actually be held in Trilinos_DIR which must
# point at "<prefix>/lib/cmake/Trilinos", but this helps the search.
SET(CMAKE_PREFIX_PATH ${Trilinos_PREFIX} ${CMAKE_PREFIX_PATH})

# Get Trilinos as one entity
FIND_PACKAGE(Trilinos REQUIRED)

# Echo trilinos build info just for fun
MESSAGE("\nFound Trilinos!  Here are the details: ")
MESSAGE("   Trilinos_DIR = ${Trilinos_DIR}")
MESSAGE("   Trilinos_VERSION = ${Trilinos_VERSION}")
MESSAGE("   Trilinos_PACKAGE_LIST = ${Trilinos_PACKAGE_LIST}")
MESSAGE("   Trilinos_LIBRARIES = ${Trilinos_LIBRARIES}")
MESSAGE("   Trilinos_INCLUDE_DIRS = ${Trilinos_INCLUDE_DIRS}")
MESSAGE("   Trilinos_LIBRARY_DIRS = ${Trilinos_LIBRARY_DIRS}")
MESSAGE("   Trilinos_TPL_LIST = ${Trilinos_TPL_LIST}")
MESSAGE("   Trilinos_TPL_INCLUDE_DIRS = ${Trilinos_TPL_INCLUDE_DIRS}")
MESSAGE("   Trilinos_TPL_LIBRARIES = ${Trilinos_TPL_LIBRARIES}")
MESSAGE("   Trilinos_TPL_LIBRARY_DIRS = ${Trilinos_TPL_LIBRARY_DIRS}")
MESSAGE("   Trilinos_BUILD_SHARED_LIBS = ${Trilinos_BUILD_SHARED_LIBS}")
MESSAGE("End of Trilinos details\n")

# DTK Trilinos defines
set(Trilinos_DEFINITIONS "${Trilinos_CXX_COMPILER_FLAGS} -DDTK_USE_TEUCHOS_RCP")

######################
# Initialize DGM / FDM
######################
if("$ENV{DGM_TPL}" STREQUAL "")
  set(DGM_TPL $ENV{HOME}/local)
else()
  set(DGM_TPL $ENV{DGM_TPL})
endif()
set(DGM_HOME ${DGM_TPL}/dgm
  CACHE PATH "Top-level path name for DGM installation, typically containing trilinos directory or serial and mpi directories")
set(DGM_DIR ${DGM_HOME}/trilinos/${PARALLEL_DIR}/${OPT_DIR}
  CACHE PATH "DGM installation directory containing include, lib, etc.")
set(DGM_INCLUDE_DIRS ${DGM_DIR}/include)
set(DGM_INCLUDE_DIRS ${DGM_INCLUDE_DIRS} ${DGM_TPL}/atlas/include)
set(DGM_INCLUDE_DIRS ${DGM_INCLUDE_DIRS} ${DGM_TPL}/boost/include)
set(DGM_LIBRARY_DIRS ${DGM_DIR}/lib)
set(DGM_LIB_NAMES ${PARALLEL_PREFIX}dgm
  CACHE STRING "DGM library names")
set(DGM_LIBRARIES "")
foreach(DGM_LIB ${DGM_LIB_NAMES})
  find_library(LIBRARY ${DGM_LIB} ${DGM_LIBRARY_DIRS})
  set(DGM_LIBRARIES ${DGM_LIBRARIES} ${LIBRARY})
endforeach(DGM_LIB ${DGM_LIB_NAMES})
if(CMAKE_BUILD_TYPE STREQUAL "DEBUG")
  set(DGM_DEFINITIONS -DFDM_DEBUG)
endif()

##########
# Compiler
##########
set(CMAKE_CXX_COMPILER ${Trilinos_CXX_COMPILER})
set(CMAKE_C_COMPILER ${Trilinos_C_COMPILER})
include_directories(${DGM_INCLUDE_DIRS} ${Trilinos_TPL_INCLUDE_DIRS}
  ${Trilinos_INCLUDE_DIRS} ${CMAKE_CURRENT_BINARY_DIR})
add_definitions(${DGM_DEFINITIONS} ${Trilinos_DEFINITIONS})

###############
# Configuration
###############
configure_file(FDM_TestConfig.hpp.in FDM_TestConfig.hpp)

#######################
# Executable MDMap test
#######################
#add_executable(testMDMap testMDMap.cpp FDM_TestUtils.cpp)
#target_link_libraries(testMDMap ${DGM_LIBRARIES} ${Trilinos_LIBRARIES}
#  ${Trilinos_TPL_LIBRARIES})

##########################
# Executable MDVector test
##########################
#add_executable(testMDVector testMDVector.cpp FDM_TestUtils.cpp)
#target_link_libraries(testMDVector ${DGM_LIBRARIES} ${Trilinos_LIBRARIES}
#  ${Trilinos_TPL_LIBRARIES})

MESSAGE(STATUS "DGM_LIBRARIES = ${DGM_LIBRARIES}")

#######################
# Executable Field test
#######################
add_executable(testField testField.cpp FDM_TestUtils.cpp)
target_link_libraries(testField ${DGM_LIBRARIES} ${Trilinos_LIBRARIES}
  ${Trilinos_TPL_LIBRARIES})

#############################
# Executable VectorField test
#############################
add_executable(testVectorField testVectorField.cpp FDM_TestUtils.cpp)
target_link_libraries(testVectorField ${DGM_LIBRARIES} ${Trilinos_LIBRARIES}
  ${Trilinos_TPL_LIBRARIES})

###################
# Simple Field test
###################
add_executable(simpleTest simpleTest.cpp)
target_link_libraries(simpleTest ${DGM_LIBRARIES} ${Trilinos_LIBRARIES}
  ${Trilinos_TPL_LIBRARIES})
