/**
   \file ReoConfig.hpp
   \brief Reo BC and Flux configuration
   \author James Overfelt
   \author Scott Collis
*/

#ifndef REO_CONFIG_HPP
#define REO_CONFIG_HPP

//==============================================================================
//                 The following are ON by default
//==============================================================================

// REO_CONSISTENT_BC (uses adjoint consistent boundary conditions)
#define REO_CONSISTENT_BC 1

// REO_BURGERS_AVG_FLUX (uses a average flux)
#define REO_BURGERS_AVG_FLUX 1

//==============================================================================
//                 The following are OFF by default
//==============================================================================

// Needed to protect documentation for defines that are off by default
#ifdef DGM_DOXYGEN

/// REO_BURGERS_NO_CONVECTION (turns off convection term in Burgers module)
#define REO_BURGERS_NO_CONVECTION

/// REO_BURGERS_HACK_FLUX (uses a modified flux that is adjoint consistent)
#define REO_BURGERS_HACK_FLUX

/// REO_BURGERS_CENTRAL_FLUX (uses a modified flux that is adjoint consistent)
#define REO_BURGERS_CENTRAL_FLUX

/// REO_IEULER_MODAL_LAPLACE (uses modal in lieu nodal Laplace operator)
#define REO_IEULER_MODAL_LAPLACE

/// REO_IEULER_LAPLACE_MATRIX (builds a Laplace matrix operator)
#define REO_IEULER_LAPLACE_MATRIX

/// REO_IEULER_CONVECTION_OFF (turns off convection)
#define REO_IEULER_CONVECTION_OFF

#endif // DGM_DOXYGEN

#endif // REO_CONFIG_HPP
