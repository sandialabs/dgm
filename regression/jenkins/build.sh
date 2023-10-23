
# Currently tailored to godel for Hudson building.
# Need to generalize dgm for builds on any platform, e.g., cmake, autoconf?

if [ $# != 1 ]; then
  echo "build.sh: $# arguments when 1 is required!"
  exit 1
fi

# Builds
# GCC  - serial gcc 
# GCCd - debug serial gcc 
# GCCp - parallel MPI gcc 
# GCCe - experimental gcc with "all" defines turned on.
if [[ ("$1" == "GCC") || ("$1" == "GCCd") || ("$1" == "GCCp") || ("$1" == "GCCe") ]]; then
  export COMP=$1
else
  echo "build.sh: $1 is an invalid compile option."
  exit 1
fi


if [ `uname` = "Linux" ]; then
  export DGM_HOME=/home/dgm
  export LD_LIBRARY_PATH=$DGM_HOME/local/lib:$DGM_HOME/local/openmpi/lib:/usr/local/gcc-4.3.1/lib64:$LD_LIBRARY_PATH
  export PATH=$WORKSPACE/$COMP:$WORKSPACE/util:$DGM_HOME/local/openmpi/bin:$PATH
elif [ `uname` = "Darwin" ]; then
  export DGM_HOME=/Users/dgm
  export PATH=$HOME/local/flex/bin:$WORKSPACE/$COMP:$WORKSPACE/util:$HOME/local/openmpi/bin:$PATH
else
  echo Unknown OS `uname`
  exit 1
fi


if [ -e build-utils/print.sh ]; then
  build-utils/print.sh
fi

if [ ! -e ~/local ]; then
  if [ `uname` = "Darwin" ]; then
    rm ~/local
    ln -s ~sscoll/local ~/local      # permissions messed up on /Users/dgm
  else
    ln -s $DGM_HOME/local ~/local
  fi
fi

# perform build

#rm -rf $COMP
if [ ! -d $COMP ]; then
  mkdir $COMP
fi
cd $COMP
if [ ! -e Makefile ]; then
  ln -s ../src/Makefile Makefile
fi

case $COMP in
GCC) 
      make -j `$WORKSPACE/util/ncpus` all;;
GCCd) 
      make -j `$WORKSPACE/util/ncpus` dall;;
GCCp) 
      if [ ! -e mpi ]; then
        ln -s ~/local/openmpi mpi
      fi
      make -j `$WORKSPACE/util/ncpus` pall;;
GCCe) 
      if [ ! -e mpi ]; then
        ln -s ~/local/openmpi mpi
      fi
      make -j `$WORKSPACE/util/ncpus` pdgm ADDONS="DGM_USE_BSTATS DGM_USE_ANALYZER DGM_USE_PLOT3D DGM_USE_ITL DGM_USE_FFTW DGM_USE_BOOST_RANDOM DGM_USE_GSL DGM_OBJFUNC_TIME_INT DGM_CONSISTENT_BC DGM_BURGERS_AVG_FLUX DGM_USE_GEOM_DB DGM_USE_WJ CMC_FLUX_INLINED_BLAS DGM_GROUPS DGM_PARALLEL=1 USE_TEMPORAL_REGULARIZATION DGM_USE_MONITOR DGM_STORE_METRICS DGM_CHOLESKY_MASS_MATRIX DGM_ELEMENT_BLOCK=2 DGM_INTEGRATE_INLINE DGM_USE_MALLINFO DGM_USE_ELEMENT_SOURCE_BLOCKS DGM_IEULER_MODAL_LAPLACE DGM_IEULER_LAPLACE_MATRIX";;
*)
      echo "build.sh: $1 is an invalid compile option."
      exit 1;;
esac
   
cd ..


#if [ -e $DGM_HOME ]; then
#  mkdir $DGM_HOME/$COMP.tmp
#  cp -p $COMP/*.exe $DGM_HOME/$COMP.tmp
#  rm -rf $DGM_HOME/$COMP
#  mv $DGM_HOME/$COMP.tmp $DGM_HOME/$COMP
#  mkdir $DGM_HOME/util.tmp
#  cp -p util/ctl2aux $DGM_HOME/util.tmp
#  cp -p util/ctl2tec $DGM_HOME/util.tmp
#  cp -p util/dgm2aux $DGM_HOME/util.tmp
#  cp -p util/dgm2p3d $DGM_HOME/util.tmp
#  cp -p util/dgm2q   $DGM_HOME/util.tmp
#  cp -p util/dgm2tec $DGM_HOME/util.tmp
#  cp -p util/dgm_clean $DGM_HOME/util.tmp
#  cp -p util/ncpus   $DGM_HOME/util.tmp
#  rm -rf $DGM_HOME/util
#  mv $DGM_HOME/util.tmp $DGM_HOME/util
#fi

exit 0
