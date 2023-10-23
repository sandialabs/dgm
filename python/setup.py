# System imports
import os
import sys

# NumPy import
import numpy

# DistUtils imports
from distutils.core import setup
from distutils.extension import Extension
from distutils.sysconfig import get_config_vars
from Cython.Distutils import build_ext

config = get_config_vars()

HOME  = os.environ.get('HOME') 
LOCAL = '%s/local' % HOME

DGM_PARALLEL = os.environ.get("DGM_PARALLEL")

if DGM_PARALLEL:
	print "Building MPI-enabled version"

print 'Generate config.pxi'

with open('config.pxi', 'w') as fd:
	fd.write('DEF DGM_PARALLEL = %s\n' % DGM_PARALLEL)

if DGM_PARALLEL:
	MPIROOT = os.environ.get('MPIROOT')
	if MPIROOT:
		config['CC'] = '%s/bin/mpicxx' % MPIROOT
		config['CXX'] = '%s/bin/mpicxx' % MPIROOT
		config['LD'] = '%s/bin/mpicxx' % MPIROOT
	else:
		config['CC'] = 'mpicxx'
		config['CXX'] = 'mpicxx'
		config['LD'] = 'mpicxx'
	DGM_INC = '%s/dgm/mpi/opt/include' % LOCAL
	DGM_LIB = '%s/dgm/mpi/opt/lib' % LOCAL
	DGM = 'pdgm'
	REO = 'preo'
	NAME = 'dgm'
else:
	DGM_INC = '%s/dgm/serial/opt/include' % LOCAL
	DGM_LIB = '%s/dgm/serial/opt/lib' % LOCAL
	DGM = 'dgm'
	REO = 'reo'
	NAME = 'dgm'

print "Building", NAME

PYTHONROOT = '%s/python/lib/python' % LOCAL

include_dirs = [
	DGM_INC,
	'../json/include',
	'%s/fftw/include' % LOCAL,
	'%s/atlas/include' % LOCAL,
	'%s/boost/include' % LOCAL,
	'%s/itl' % LOCAL,
	'%s/gsl/include' % LOCAL,
	'%s/peopt' % LOCAL,
	'%s/mpi4py/include' % LOCAL,
	#numpy.get_include()
	]

define_macros = [
	('DGM_USE_BSTATS', None),
	('DGM_USE_ANALYZER', None),
	('DGM_USE_PLOT3D', None),
	('DGM_USE_ITL', None),
	('DGM_USE_GSL', None),
	('DGM_OBJFUNC_TIME_INT', None),
	('DGM_USE_GEOM_DB', None),
	('DGM_USE_WJ', None),
	('DGM_GRIEWANK', None),
	('DGM_NEW_ANALYZER', None),
	('DGM_PARALLEL_CONSTRUCTION', None),
	('DGM_TEST_PYTHON_INTERFACE', None),
	('DGM_USE_BOOST_FS', None),
	('DGM_USE_JSON', None),
	('GCC4', None),
	]

if DGM_PARALLEL:
	define_macros.extend( [
	('DGM_PARALLEL', None),
	('MPICH_IGNORE_CXX_SEEK', None),
	] )

extra_compile_args = [
        '-Wno-self-assign', '-Wno-unused-function', 
        '-Wno-unused-local-typedef', '-Wno-unused-private-field'
        ]

library_dirs = [
		'%s/atlas/lib' % LOCAL,
		'%s/fftw/lib' % LOCAL,
		'%s/gsl/lib' % LOCAL,
		'%s/boost/lib' % LOCAL,
		DGM_LIB,
		]

libraries = [
		DGM, REO, 'clapack', 'cblas', 
		'atlas', 'm',
		'gsl', 'gslcblas', 'pthread',
		]
		
ext_modules = [
	Extension(
		NAME,
		["dgm.pyx"],
		language = 'c++',
		include_dirs = include_dirs,
		define_macros = define_macros,
		library_dirs = library_dirs,
		libraries = libraries,
		extra_compile_args = extra_compile_args,
	)
]

setup(
	name = NAME,
	cmdclass = {'build_ext': build_ext},
	ext_modules = ext_modules
)
