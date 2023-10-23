# DAKOTA setup

ifndef DAKOTA
  DAKOTA = /usr/sharelan/dakota/test_linux/Dakota
endif
DAKOTA_BUILD = $(DAKOTA)/lib

DAKOTA_DEFS = \
	-DUNIX -DDARWIN -DMULTITASK \
	-DDAKOTA_DOT \
	-DDAKOTA_NPSOL \
	-DDAKOTA_CONMIN \
	-DDAKOTA_NL2SOL \
	-DDAKOTA_OPTPP -DSERIAL -DDAKOTA_NEWMAT \
	-DDAKOTA_DDACE -DUSEDLARAN -DNO_NAMESPACES -DNO_BLAS \
	-DDAKOTA_LHS \
	-DDAKOTA_JEGA -DOTB_RTTI \
	-DDAKOTA_KSM \
	-DDAKOTA_GRAPHICS \
	-DDAKOTA_ANN \
	-DDAKOTA_PETRA

DAKOTA_INCL = \
        -I$(DAKOTA)/src \
	-I$(DAKOTA)/VendorOptimizers/opt++/include \
	-I$(DAKOTA)/VendorOptimizers/opt++/newmat09 \
        -I$(DAKOTA)/VendorOptimizers/DDace/include \
	-I$(DAKOTA)/VendorOptimizers/DDace/CPPUtilities/src/PMachine \
	-I$(DAKOTA)/VendorOptimizers/DDace/CPPUtilities/src/Utils \
	-I$(DAKOTA)/VendorOptimizers/jega/include \
	-I$(DAKOTA)/VendorOptimizers/jega/Utilities/include \
	-I$(DAKOTA)/VendorOptimizers/jega/MOGA/include \
	-I$(DAKOTA)/VendorOptimizers/jega/SOGA/include \
	-I$(DAKOTA)/VendorPackages/idr \
	-I$(DAKOTA)/VendorPackages/motif/include \
	-I$(DAKOTA)/VendorPackages/plplot/include \
	-I$(DAKOTA)/VendorPackages/ann/include \
	-I$(DAKOTA)/VendorPackages/epetra \
	-I$(DAKOTA)/VendorPackages/motif/include \
	-I$(DAKOTA)/VendorPackages/plplot/include \

# DAKOTA libs
DAKOTA_LIB = \
	$(DAKOTA_BUILD)/libdakota.a \
	$(DAKOTA_BUILD)/libann.a \
	$(DAKOTA_BUILD)/libconmin.a \
	$(DAKOTA_BUILD)/libcport.a \
	$(DAKOTA_BUILD)/libddace.a \
	$(DAKOTA_BUILD)/libdot.a \
	$(DAKOTA_BUILD)/libepetra.a \
	$(DAKOTA_BUILD)/libidr.a \
	$(DAKOTA_BUILD)/libjega.a \
	$(DAKOTA_BUILD)/libkriging.a \
	$(DAKOTA_BUILD)/liblhs.a \
	$(DAKOTA_BUILD)/libnpsol.a \
	$(DAKOTA_BUILD)/liboptpp.a \
	$(DAKOTA_BUILD)/libnewmat.a \
	$(DAKOTA_BUILD)/libdakota.a

# PGI F90 libraries
F90_LIB_PATH = -L/opt/ibmcmp/xlf/8.1/lib
F90_LIBS = -lxlf90 -lxl -lxlfmath -lg2c

# X11 libraries
#X11_INCL= -I/usr/X11R6/include -I/usr/X11R6/include/X11
#X11_LIB_PATH = -L/usr/X11R6/lib
#X11_LIBS = -lXm -lXt -lXpm -lXmu -lXp -lXext -lSM -lICE -lX11 -lpthread -ldl

# Modify for DAKOTA
override INCS := $(INCS) $(DAKOTA_INCL) $(X11_INCL)
override LIBS := $(DAKOTA_LIB) $(F90_LIB_PATH) $(F90_LIBS) \
$(X11_LIB_PATH) $(X11_LIBS) $(LIBS) /home/sscoll/dist/atlas/lib/liblapack.a \
-lfl
override CPPFLAGS := $(CPPFLAGS)  $(DAKOTA_DEFS)
