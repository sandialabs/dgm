#ifndef DGM_CLEARDBS_HPP
#define DGM_CLEARDBS_HPP

/** \file ClearDBs.hpp
    \brief Clears all DGM::Element databases 
    \author 
    \copyright 2014(c) Sandia National Laboratories
*/

#include "Hex.hpp"
#include "Line.hpp"
#include "NodalHex.hpp"
#include "NodalLine.hpp"
#include "NodalQuad.hpp"
#include "NodalTet.hpp"
#include "NodalTri.hpp"
#include "Quad.hpp"
#include "SpectralHex.hpp"
#include "SpectralLine.hpp"
#include "SpectralQuad.hpp"
#include "Tri.hpp"

namespace DGM {
void ClearDBs() {
  Hex::ClearDBs();
  Line::ClearDBs();
  NodalHex::ClearDBs();
  NodalLine::ClearDBs();
  NodalQuad::ClearDBs();
  NodalTet::ClearDBs();
  NodalTri::ClearDBs();
  Quad::ClearDBs();
  SpectralHex::ClearDBs();
  SpectralLine::ClearDBs();
  SpectralQuad::ClearDBs();
  Tri::ClearDBs();
}
}
#endif
