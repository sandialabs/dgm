#==============================================================================
#   Title:     Reo Objects
#
#   Author:    Scott Collis
#              sscoll@sandia.gov
#
#   Copyright: (C)2011 Sandia National Laboratories
#==============================================================================
#
# List the Reo object files here
#
REO_ALL = ReoProblem ReoOptProblem Adv_Diff Euler Navier_Stokes Euler3d	     \
Navier_Stokes3d Turbulence Wave Burgers LinEuler_quasi LinEuler_prim iEuler  \
iNS Couple EulerDC ArtDiff Helmholtz Poisson Burgers_Adjoint Euler_State     \
Euler_Adjoint Euler_Control NS_State NS_Control NS_Adjoint Adv_Diff_State    \
Adv_Diff_Adjoint LinBurgers LinBurgers_Adjoint Shallow Darcy ReoInfo	       \
Multi_Component_Transport Multi_Mat_Adv_Diff MiscibleTransport LinNS_quasi   \
ShallowAdjoint ShallowControl ShallowState Maxwell
#
# List the Reo optimization files here
#
REO_OPT = 
#
# At Reo peopt objects
#
ifdef PEOPT_HOME
override ALL_PEOPT := $(ALL_PEOPT) PEReo
endif
