#!/usr/bin/python

import getopt
import optparse
import string
import struct
import sys
import time
import json 

TO_INT = 10000
TRI    = 0
QUAD   = 1
TET    = 2
HEX    = 3
SPECTRALQUAD   = 4
SPECTRALHEX    = 5

class Element(object) :
  def __init__(self) :
    self.type = TRI       # TRI, QUAD, TET, HEX
    self.x = []
    self.y = []
    self.z = []

def to_int(x) :
  return int(TO_INT*float(x))


def point_on_segment(p,s) :
  p_on_s = False
  x  = to_int(p[0])
  y  = to_int(p[1])
  x1 = to_int(min(s[0][0], s[1][0]))
  x2 = to_int(max(s[0][0], s[1][0]))
  y1 = to_int(min(s[0][1], s[1][1]))
  y2 = to_int(max(s[0][1], s[1][1]))
  if   (x1 == x2) :
    if (x == x1 and y1 <= y and y <= y2) : p_on_s = True
  elif (y1 == y2) :
    if (y == y1 and x1 <= x and x <= x2) : p_on_s = True
  elif (x1 <= x and x <= x2 and y1 <= y and y <= y2) :
      xr = to_int((p[0]-s[0][0])/(s[1][0]-s[0][0]))
      yr = to_int((p[1]-s[0][1])/(s[1][1]-s[0][1]))
      if (xr == yr) : p_on_s = True
  return p_on_s

def point_in_quad(p,s) :
  p_in_s = True
  for i in range(len(s)) :
    a = [ s[(i+1)%4][j] - s[i][j] for j in range(len(s[i])) ]
    b = [          p[j] - s[i][j] for j in range(len(s[i])) ]
    d = [ a[j]*b[j]               for j in range(len(a))    ]
    if (to_int(sum(d))<0) : p_in_s = False
  return p_in_s

def point_in_side(p,s) :
  if (2==len(p)) :
    inside = point_on_segment(p,s)
  else :
    inside = point_in_quad(p,s)
  return inside

def overlap(s1,s2,MAX,MIN) :
  in_all = True
  p1 = zip(*s1)
  p2 = zip(*s2)
  for i in range(len(p1)) :
    inside = point_in_side(p1[i],p2)
    in_all = in_all and inside
  if (not in_all) :
    t1 = [ [ y for y in x ]  for x in s1 ]
    t2 = [ [ y for y in x ]  for x in s2 ]
    found_periodic = False
    for i in range(len(t1)) :
      if (to_int(max(t1[i])) == to_int(MAX[i]) and
          to_int(min(t1[i])) == to_int(MAX[i])) :
        for j in range(len(t1[i])) : t1[i][j] = MIN[i]
        found_periodic = True
      if (to_int(max(t2[i])) == to_int(MAX[i]) and
          to_int(min(t2[i])) == to_int(MAX[i])) :
        for j in range(len(t2[i])) : t2[i][j] = MIN[i]
        found_periodic = True
    if (found_periodic) :
      p1 = zip(*t1)
      p2 = zip(*t2)
      in_all = True
      for i in range(len(p1)) :
        inside = point_in_side(p1[i],p2)
        in_all = in_all and inside
  return in_all

def overlaps(s1,s2,max,min) :
  in1 = overlap(s1,s2,max,min)
  in2 = overlap(s2,s1,max,min)
  either = in1 or in2
  return either

def node_indexes(type,i) :
  if   (QUAD==type or SPECTRALQUAD==type) : indexes = (i, (i+1)%4)
  elif (HEX==type  or SPECTRALHEX ==type) :
    if   (0==i) : indexes = (0,1,2,3)
    elif (1==i) : indexes = (0,1,5,4)
    elif (2==i) : indexes = (1,2,6,5)
    elif (3==i) : indexes = (2,3,7,6)
    elif (4==i) : indexes = (3,0,4,7)
    elif (5==i) : indexes = (4,5,6,7)
  else : sys.exit(" TRI and TET not supported yet.")
  return indexes;

def determine_dimension (root) :
  f = open('%s.msh' %(root), 'r')
  lines = f.readlines()
  f.close()
  dim=0
  words = lines[1].split()
  if (3<len(words) and words[3] == "NSD") :
    dim = int(words[1])
    print dim,"dimentional mesh with ",words[0],"elements."
  else : sys.exit("Did not find NSD in mesh file.")
  return dim

def suck_in_mesh_file (root, dim) :
  try :
    f = open('%s.msh' %(root), 'r')
  except IOError :
    sys.exit("Mesh file *.msh not found")
  elements = []
  lines = f.readlines()
  f.close()
  words = lines[1].split()
  if (dim != int(words[1])) : sys.exit("Error in msh file: DIM not found.")
  i = 2
  elem_no = 0
  while i < len(lines):
    words = lines[i].split()
    i = i + 1
    if (words[0] != "ELEMENT") : sys.exit( "Parser Error 'ELEMENT' not found.")
    el = Element()
    if    (words[2] == "TRI")  : el.type = TRI
    elif  (words[2] == "QUAD") : el.type = QUAD
    elif  (words[2] == "TET")  : el.type = TET
    elif  (words[2] == "HEX")  : el.type = HEX
    elif  (words[2] == "SPECTRALQUAD") : el.type = SPECTRALQUAD
    elif  (words[2] == "SPECTRALHEX")  : el.type = SPECTRALHEX
    else :  sys.exit( "Parser Error element type not found.")

    words = lines[i].split()
    i = i + 1
    for j in range(len(words)): el.x.append(float(words[j]))
    words = lines[i].split()
    i = i + 1
    for j in range(len(words)): el.y.append(float(words[j]))
    if (3==dim) :
      words = lines[i].split()
      i = i + 1
      for j in range(len(words)) : el.z.append(float(words[j]))
    else :
      for j in range(len(words)) : el.z.append(float(0))
    elements.append(el)
    ++elem_no

  return elements


def suck_in_connectivity_file(root) :
  try :
    f = open('%s.con' %(root), 'r')
  except IOError  :
    sys.exit("Connectivity file *.con not found")
  lines = f.readlines()
  f.close()
  graph = []
  for i in range(2,len(lines)):
    if (not i%1000) : sys.stdout.write("\r Connect: "+str(i))
    words = lines[i].split()
    c = (int(words[1]), int(words[2]), int(words[3]), int(words[4]))
    graph.append(c)
  print
  return graph

def suck_in_refinement_file(root, dim, max_elem) :
  try :
    f = open('%s.rfn' %(root), 'r')
  except IOError  :
    sys.exit("Refinement file *.rfn not found")
  lines = f.readlines()
  f.close()
  elem = set()
  refine = []
  for i in range(1,len(lines)):
    if (not i%1000) : sys.stdout.write("\r Refinement: "+str(i))
    words = lines[i].split()
    while len(words) < 4 : words.append(0)
    if dim == 2 : words[3] = 0
    for i in range(len(words)) : words[i] = int(words[i])
    for i in words : 
      if i < 0 : sys.exit("A side refinement number found to be negative.")
    if (max_elem <= words[0]) : sys.exit("Element num in refine file out of bounds")
    c = (words[0], 1+words[1], 1+words[2], 1+words[3])
    refine.append(c)
    if words[0] in elem : sys.exit("Duplicate element in refine file")
    elem.add(words[0])
  # refine.sort() #comment out for testing purposes
  print
  return refine



def collect_side_connectivity(graph, elem) :
  sides = [ [] for i in range(6) ]
  for g in graph :
    if (g[0] == elem) :
      sides[g[1]].append( (g[2], g[3]) )
  return sides

def phi1(x) : return   x
def phi0(x) : return 1-x

def quad_phi(x,y) :
  phi = []
  phi.append(phi0(x)*phi0(y))
  phi.append(phi1(x)*phi0(y))
  phi.append(phi1(x)*phi1(y))
  phi.append(phi0(x)*phi1(y))
  return phi

def tri_phi(x,y) :
  phi = []
  phi.append(phi0(x+y))
  phi.append(phi1(x))
  phi.append(phi1(y))

def hex_phi(x,y,z) :
  phi = []
  phi.append(phi0(x)*phi0(y)*phi0(z))
  phi.append(phi1(x)*phi0(y)*phi0(z))
  phi.append(phi1(x)*phi1(y)*phi0(z))
  phi.append(phi0(x)*phi1(y)*phi0(z))
  phi.append(phi0(x)*phi0(y)*phi1(z))
  phi.append(phi1(x)*phi0(y)*phi1(z))
  phi.append(phi1(x)*phi1(y)*phi1(z))
  phi.append(phi0(x)*phi1(y)*phi1(z))
  return phi

def tet_phi(x,y,z) :
  phi = []
  phi.append(phi0(x+y+z))
  phi.append(phi1(x))
  phi.append(phi1(y))
  phi.append(phi1(z))

def eval_basis(type, xi) :
  if   (type == TRI)  : return  tri_phi(xi[0],xi[1])
  elif (type == QUAD or type == SPECTRALQUAD) : return quad_phi(xi[0],xi[1])
  elif (type == HEX  or type == SPECTRALHEX)  : return  hex_phi(xi[0],xi[1],xi[2])
  else                : return  tet_phi(xi[0],xi[1],xi[2])

def dot (x,y) :
  d = 0
  for i in range(len(x)) : d += x[i]*y[i]
  return d

def quad_nodes (x,k,m) :
  y = []
  for n in range(4) :
    xi = 2*[None]
    i = k[:]
    if (1==n or 2==n) : i[0] += 1
    if (2==n or 3==n) : i[1] += 1
    for j in range(2) : xi[j] = float(i[j])/m[j]
    phi = quad_phi(xi[0],xi[1])
    y.append(dot(phi,x))
  return y

def hex_nodes (x,k,m) :
  y = []
  for n in range(8) :
    xi = 3*[None]
    i = k[:]
    if (1==n%4 or 2==n%4) : i[0] += 1
    if (2==n%4 or 3==n%4) : i[1] += 1
    if (3 < n)            : i[2] += 1
    for j in range(3) : xi[j] = float(i[j])/m[j]
    phi = hex_phi(xi[0],xi[1],xi[2])
    y.append(dot(phi,x))
  return y

def elem_nodes (type, x,i,m) :
  if   (type == TRI)  : return  tri_nodes(x,i,m)
  elif (type == QUAD or type == SPECTRALQUAD) : return quad_nodes(x,i,m)
  elif (type == HEX  or type == SPECTRALHEX)  : return  hex_nodes(x,i,m)
  else                : return  tet_nodes(x,i,m)

def refine_element(elem, refine_info) :
  sub_elem = []
  m = refine_info[:]
  i = 3*[None]
  for i[0] in range(m[0]) :
    for i[1] in range(m[1]) :
      for i[2] in range(m[2]) :
         el = Element()
         el.type = elem.type
         el.x = elem_nodes(elem.type,elem.x,i,m)
         el.y = elem_nodes(elem.type,elem.y,i,m)
         el.z = elem_nodes(elem.type,elem.z,i,m)
         sub_elem.append(el)
  return sub_elem

def quad_graph(l,m) :
  graph = []
  for i in range(m[0]) :
    for j in range(m[1]) :
      n = l + j + i*m[1]
      north = -1
      south = -1
      east  = -1
      west  = -1
      if  j<m[1]-1  : north = n+1
      if  j         : south = n-1
      if  i<m[0]-1  : east  = n+m[1]
      if  i         : west  = n-m[1]
      graph.append( (n,0, south,2) )
      graph.append( (n,1, east ,3) )
      graph.append( (n,2, north,0) )
      graph.append( (n,3, west, 1) )
  return graph

def hex_graph(l,m) :
  graph = []
  for i in range(m[0]) :
    for j in range(m[1]) :
      for k in range(m[2]) :
        n = l + k + j*m[2] + i*m[1]*m[2]
        top      = -1
        bottom   = -1
        north    = -1
        south    = -1
        east     = -1
        west     = -1
        if  k<m[2]-1   : top    =   n+1         
        if  k          : bottom =   n-1         
        if  j<m[1]-1   : north  =   n+m[2]      
        if  j          : south  =   n-m[2]      
        if  i<m[0]-1   : east   =   n+m[1]*m[2] 
        if  i          : west   =   n-m[1]*m[2] 
        graph.append( (n,0, bottom, 5) )
        graph.append( (n,1, south,  3) )
        graph.append( (n,2, east,   4) )
        graph.append( (n,3, north,  1) )
        graph.append( (n,4, west,   2) )
        graph.append( (n,5, top,    0) )
  return graph

def refine_sub_graph (type, new_num, refine_info) :
  if   (type == TRI)  : return tri_graph (new_num, refine_info)
  elif (type == QUAD or type == SPECTRALQUAD) : return quad_graph(new_num, refine_info)
  elif (type == HEX  or type == SPECTRALHEX)  : return hex_graph (new_num, refine_info)
  else                : return tet_graph (new_num, refine_info)



def get_side_values (type, val, side) :
  x = []
  ind = node_indexes (type, side);
  for i in ind : x.append(val[i])
  return x


def line_parametric_coord (x,s) :
  r = []
  n = len(x)
  d = n*[None]
  y = n*[None]
  for i in range(n) : d[i] = s[1][i] - s[0][i]
  for i in range(n) : y[i] = x[i]-s[0][i]
  r.append(dot(y,d)/dot(d,d));
  return r

def shape_fcn_deriv(dNds, pc) :
  dNds[0][0] = - 0.25 * (1.0 - pc[1])
  dNds[0][1] = - 0.25 * (1.0 - pc[0])

  dNds[1][0] =   0.25 * (1.0 - pc[1])
  dNds[1][1] = - 0.25 * (1.0 + pc[0])

  dNds[2][0] =   0.25 * (1.0 + pc[1])
  dNds[2][1] =   0.25 * (1.0 + pc[0])

  dNds[3][0] = - 0.25 * (1.0 + pc[1])
  dNds[3][1] =   0.25 * (1.0 - pc[0])


def inv_2x2(A_inv, A) :
  det = A[0][0] * A[1][1] - A[1][0] * A[0][1]
  denom = 1/det
  # inverse:
  A_inv[0][0] =  denom * A[1][1] # dxidx
  A_inv[1][0] = -denom * A[1][0] # detadx
  A_inv[0][1] = -denom * A[0][1] # dxidy
  A_inv[1][1] =  denom * A[0][0] # detady
  return det

def ATA(ata, A) :
  for i in range(2) :
    for j in range(2) :
      ata[i][j] = 0
  for i in range(2) :
    for j in range(2) :
      for k in range(3) :
        ata[i][j] += A[k][i]*A[k][j]

def BAT(bat, B, A) :
  for i in range(2) :
    for j in range(3) :
      bat[i][j] = 0
  for i in range(2) :
    for j in range(3) :
      for k in range(2) :
        bat[i][j] += B[i][k]*A[j][k]


def DXDS (dxds, coord, dNds) :
  for i in range(3) :
    for j in range(2) :
      dxds[i][j] = 0;
  for k in range(4) :
    for i in range(3) :
      for j in range(2) :
        dxds[i][j] += coord[k][i] * dNds[k][j]


def DSDX(dsdx, coord, dNds) :
  dxds    = [ [ [] for j in range(2) ] for i in range(3) ]
  ata     = [ [ [] for j in range(2) ] for i in range(2) ]
  ata_inv = [ [ [] for j in range(2) ] for i in range(2) ]
  DXDS(dxds, coord, dNds)
  #    dsdx = |  dxidx   dxidy   dxidz |
  #    dxds = | dxdxi   dxdeta |
  #           | dydxi   dydeta |
  #           | dzdxi   dzdeta |
  ATA(ata, dxds)
  det = inv_2x2(ata_inv, ata)
  BAT(dsdx, ata_inv, dxds)
  #    dsdx = |  dxidx   dxidy   dxidz |
  #           | detadx  detady  detadz |
  id = [ [ [] for j in range(2) ] for i in range(2) ]
  for i in range(2) :
    for j in range(2) : id[i][j] = 0
  for i in range(2) :
    for j in range(2) :
      for k in range(3) :
        id[i][j] += dsdx[i][k] * dxds[k][j]
  I = 4*[None]
  I[0]  =  int(.00001+id[0][0]);
  I[1]  =  int(.00001+id[1][1]);
  I[2]  =  int(1000000*id[0][1]);
  I[3]  =  int(1000000*id[1][0]);
  if (not I[0] or not I[1] or I[2] or I[3]) :
    print ":",id[0][0]," ",id[0][1]," ",id[1][0]," ",id[1][1]
  return (det < 1.0E-16)

def shape_fcn(N, pc) :
  # shape function for each node evaluated at param_coords
  N[0] = 0.25 * (1.0 - pc[0]) * (1.0 - pc[1])
  N[1] = 0.25 * (1.0 + pc[0]) * (1.0 - pc[1])
  N[2] = 0.25 * (1.0 + pc[0]) * (1.0 + pc[1])
  N[3] = 0.25 * (1.0 - pc[0]) * (1.0 + pc[1])


def fcn(pc, coords) :
  n = len(coords[0])
  N = 4*[None]
  g = n*[None]
  shape_fcn(N,pc)
  for k in range(n) : g[k] = 0
  for i in range(4) :
    for k in range(n) : g[k] += N[i] * coords[i][k]
  return g;


def quad_parametric_coord(p,C) :

  corner = -1
  for j in range(len(C)) :
    corner = j
    c = C[j]
    for i in range(len(p)) :
      if to_int(c[i]) != to_int(p[i]) : corner = -1
    if -1 < corner : break
  if -1 < corner :
    if   (corner == 0) : return (0,0)
    elif (corner == 1) : return (1,0)
    elif (corner == 2) : return (1,1)
    else               : return (0,1)

  MAXIT = 20
  TOL   = 1.0E-9

  if (len(C)!=4) :
    sys.error("quad_parametric_coord:Wrong number nodes.")

  M = [ [] for i in range(4) ]

#  t = [0,1,3,2]
#  coords = [ [] for i in range(3) ]
#  for i in t :
#    coords[i][0] = C[0][i]
#    coords[i][1] = C[1][i]
#    coords[i][2] = C[2][i]

  dx = 3*[None]
  ds = 2*[None]
  dNds = [ [ [] for j in range(2) ] for i in range(4) ]
  dsdx = [ [ [] for j in range(3) ] for i in range(2) ]

  #Initial guess, center of element
  pc = 2*[None]
  pc[0] = 0
  pc[1] = 0
  dist = 9999999.0
  step = 9999999.0
  iter = 0

  while ( TOL*TOL < dist and iter < MAXIT and TOL*TOL < step) :
    iter += 1

    shape_fcn_deriv  (dNds, pc)
    DSDX   (dsdx, C, dNds)
    g = fcn(pc,C)

    dist = 0.0
    for j in range(3) : dx[j] = g[j] - p[j]
    for j in range(3) : dist += dx[j]*dx[j]

    for j in range(2) : ds[j] = 0
    for i in range(2) :
      for j in range(3) : ds[i] += dsdx[i][j] * dx[j]

    for j in range(2) : pc[j] -= ds[j];
    step = ds[0]*ds[0] + ds[1]*ds[1];

  r = MAXIT==iter;
  if (r) : sys.exit("Newton Iteration Failed")
  pc[0] = (pc[0]+1)/2
  pc[1] = (pc[1]+1)/2
  return pc

def parametric_coord (x,s) :
  if   (2==len(s)) : return line_parametric_coord(x,s)
  elif (3==len(s)) : return  tri_parametric_coord(x,s)
  elif (4==len(s)) : return quad_parametric_coord(x,s)
  else             : sys.exit("Parametric coord size error")

def inside(x,s) :
  z = parametric_coord(x,s)
  r = True
  for i in z :
    j = to_int(i);
    r = (r and 0 <= j and j <= TO_INT)
  return r

def subset(a,b) :
  sub = True
  for i in a : sub = sub and inside(i,b)
  return sub

def overlap (a,b) :
  sub = subset(a,b)
  sub = sub or subset(b,a)
  return sub

def get_side_nodes(element, side) :
  d = 2
  if element.type == HEX or element.type == TET : d = 3 
  if   (element.type == HEX) : n = 4
  elif (element.type == TET) : n = 3
  else                       : n = 2
  XYZ = d*[None]
  XYZ[0]          = get_side_values(element.type, element.x, side)
  XYZ[1]          = get_side_values(element.type, element.y, side)
  if 3==d : XYZ[2]= get_side_values(element.type, element.z, side)
  side_nodes = n*[None]
  for j in range (n) :
    N = []
    for i in range (d) : N.append(XYZ[i][j])
    side_nodes[j] = N
  return side_nodes

def check_subside(ref_elem, ref_side, nbr_elem, nbr_side) :
  ref_nodes = get_side_nodes(ref_elem, ref_side)
  nbr_nodes = get_side_nodes(nbr_elem, nbr_side)
  return overlap(ref_nodes, nbr_nodes)

def fill_out_sub_graph (sub_graph, ref_elem, elements, graph) :
  side_connectivity = collect_side_connectivity(graph, ref_elem)
  new_sub_graph = []
  for g in sub_graph :
    if (0<g[2]) : new_sub_graph.append(g)
    else :
      this_elem = elements[g[0]]
      this_side = g[1]
      neighbors = side_connectivity[this_side]
      found_a_neighbor = 0==len(neighbors)
      for neighbor in neighbors :
        nbor_elem = elements[neighbor[0]]
        nbor_side = neighbor[1]
        is_still_neighbor = check_subside(this_elem, this_side, nbor_elem, nbor_side)
        if (is_still_neighbor) :
          new_record = (g[0], g[1], neighbor[0], nbor_side)
          new_sub_graph.append( new_record  )
          found_a_neighbor = True
      if (not found_a_neighbor) :
        print " Looking for a side for new element",g[0],"side",this_side
        sys.exit("Side with no neighbor")
  return new_sub_graph

def insert_sub_graph_into_graph(sub_graph, graph, refine_elem) :
  new_graph = []
  for g in graph :
    if    (g[0] == refine_elem) : continue
    elif  (g[2] == refine_elem) :
      for s in sub_graph :
        if (g[0] == s[2] and g[1] == s[3]) : new_graph.append( (g[0],g[1],s[0],s[1]))
    else : new_graph.append(g)
  for s in sub_graph : new_graph.append(s)
  return new_graph

def refine_element_into_sub_elem(elements, refine_info) :
  refine_elem_num   = refine_info[0]
  refine_sides      = refine_info[1:4]
  refine_elem       = elements[refine_elem_num]

  # Refine single element and return list of sub-elements
  sub_elements      = refine_element(refine_elem, refine_sides)
  elements.extend(sub_elements)
  return elements


def refine_graph_for_new_sub_elem(elements, graph, refine_info, new_elem_num) :
  refine_elem_num   = refine_info[0]
  refine_sides      = refine_info[1:4]
  refine_elem       = elements[refine_elem_num]

  # At this point a bunch of elements have been added to the end, but they are
  # not connected to any other elements since graph has not changed.
  # This works fine for quad and hexes where the refinement is easy and the
  # graph can be updated just knowing the refine_info and the old graph, but
  # for tri and tet the refine_graph function might have to be merged with the
  # refine_element function to generate the new graph during refinement.

  # Determine new connectivity within patch of elements. Since refinement is
  # deterministic this can be done independently of refine_element.
  sub_graph         = refine_sub_graph   (refine_elem.type, new_elem_num,  refine_sides)

  # Now fix up the part of sub_graph that connects to the old graph
  sub_graph         = fill_out_sub_graph (sub_graph, refine_elem_num, elements, graph)
  graph             = insert_sub_graph_into_graph(sub_graph, graph, refine_elem_num)

  for g in graph :
    if (g[0]==refine_elem_num or g[2]==refine_elem_num) :
      sys.exit("Internal Refinement Error: 28743")

  return graph


def remove_refined_elements_from_graph(graph, elements_to_refine, num_ele) :
  n = []
  for e in elements_to_refine : n.append(e[0])
  n.sort()
  graph.sort()

  rev_num = []
  j = 0
  for i in range(num_ele) :
    if   (j < len(n) and i == n[j]) : j += 1
    else                            : rev_num.append(i)
  new_num = [None]*num_ele
  for i in range(len(rev_num)) : new_num[rev_num[i]] = i
  new_graph = []
  for g in  graph : new_graph.append( (new_num[g[0]], g[1], new_num[g[2]], g[3]) )
  new_graph.sort()
  return new_graph

def delete_refined_elements(elements, elements_to_refine) :
  n = []
  for e in elements_to_refine : n.append(e[0])
  n.sort()
  new_elements = []
  j = 0
  for i in range(len(elements)) :
    if   (j < len(n) and i == n[j]) : j += 1
    else                            : new_elements.append(elements[i])
  return new_elements


def write_binary_mesh (elements,root,d) :
  b = open('%s_ref.grd' %(root), 'w')
  header = {}
  header["Date"]= time.asctime()
  header["Name"]= '%s_ref.grd' % (root)
  header["Nel"] = len(elements)
  header["Nsd"] = d
  header["Types"] = {}
  header["Types"]["ByteOrder"] = "LittleEndian"
  header["Types"]["GlobalSize"]= "int32"
  header["Types"]["LocalSize"] = "int32"
  header["Types"]["Scalar"]    = "float64"
  header["Version"] = 1.0 
  print >> b, json.dumps(header,indent=2,sort_keys=True) 
  b.close()

  
  b = open('%s_ref.grd' %(root), 'ab')
  b.write(struct.pack('i', len(elements)))
  b.write(struct.pack('i', d))
  b.write(struct.pack('i', (2**d)*len(elements)))
  for i in range(len(elements)) :
    s = 0
    if (elements[i].type ==         QUAD) : s = 1
    if (elements[i].type ==          HEX) : s = 3
    if (elements[i].type == SPECTRALQUAD) : s = 12
    if (elements[i].type ==  SPECTRALHEX) : s = 13
    b.write(struct.pack('i', s))
  disp = 0
  for i in range(len(elements)) :
    b.write(struct.pack('i', disp))
    disp += 2**d
  for e in elements :
    for x in e.x : b.write(struct.pack('d',float(x)))
  for e in elements :
    for y in e.y : b.write(struct.pack('d',float(y)))
  if (3==d) :
    for e in elements :
      for z in e.z : b.write(struct.pack('d',float(z)))
  b.close()

def write_ascii_mesh(elements, root, d) :
  f = open('%s_ref.msh' %(root), 'w')
  print >>f, "**MESH DATA**"
  print >>f, len(elements), d, "NE NSD"
  for i in range(len(elements)) :
    x = [float(j) for j in elements[i].x]
    y = [float(j) for j in elements[i].y]
    z = [float(j) for j in elements[i].z]
    if    (elements[i].type == QUAD)       : s = " QUAD"
    elif  (elements[i].type==SPECTRALQUAD) : s = " SPECTRALQUAD"
    elif  (elements[i].type==SPECTRALHEX ) : s = " SPECTRALHEX"
    else                                   : s = " HEX"
    print >>f, "ELEMENT %3d %s" % (i,s)
    for j in range(len(x)) : print >>f, "%22.15e" % (x[j]),
    print >> f
    for j in range(len(y)) : print >>f, "%22.15e" % (y[j]),
    print >> f
    if (3==d) :
      for j in range(len(y)) : print >>f, "%22.15e" % (z[j]),
      print >> f
  f.close()


def write_binary_graph(graph, root, d, ne) :
  b = open('%s_ref.cn' %(root), 'w')
  header = {}
  header["Date"]= time.asctime()
  header["Name"]= '%s_ref.cn' % (root)
  header["Nel"] = ne 
  header["Nsd"] = d
  header["Types"] = {}
  header["Types"]["ByteOrder"] = "LittleEndian"
  header["Types"]["GlobalSize"]= "int32"
  header["Types"]["LocalSize"] = "int32"
  header["Types"]["Scalar"]    = "float64"
  header["Version"] = 1.0 
  print >> b, json.dumps(header,indent=2,sort_keys=True) 
  b.close()


  b = open('%s_ref.cn' %(root), 'ab')
  gid = 0
  gids = {}
  for g in graph :
    if (not gids.has_key(g)) :
      gids[g] = gid
      gids[ (g[2],g[3],g[0],g[1]) ] = gid
      gid += 1

  lengths = []
  for g in graph :
    # pad with 0s for missing element numbers
    while len(lengths) <= g[0] : lengths.append(0)
    lengths[g[0]] += 1;

  displacements = []
  displacements.append(0);
  for i in range(len(lengths)) :
    displacements.append(displacements[i]+lengths[i])
  displacements.pop()

  for i in displacements : b.write(struct.pack('i', i))
  for i in lengths       : b.write(struct.pack('i', i))

  for i in graph :
    data = struct.pack('5i', i[0], i[1], i[2], i[3], gids[i])
    b.write(data)
  b.close()


def write_ascii_graph(graph, root, ne) :
  f = open('%s_ref.con' %(root), 'w')
  print >>f, "**CONNECTIVITY DATA**"
  print >>f, ne, "ne"
  for i in graph : print >>f, "E %7d %7d %7d %7d" % (i[0], i[1], i[2], i[3])
  f.close()


def print_dat(f,x) :
  if (8==len(x)) :
    print >>f, \
    " %13.9e %13.9e %13.9e %13.9e %13.9e %13.9e %13.9e %13.9e"  \
    % (x[0],x[1],x[3],x[2],x[4],x[5],x[7],x[6])
  else :
    print >>f, " %13.9e  %13.9e  %13.9e  %13.9e" % (x[0], x[1], x[3], x[2])

def write_tecplot(elements, root, d) :
  f = open('%s_ref.dat' %(root), 'w')
  print >>f, "TITLE=\"Mesh Check\""
  if (2==d) : print >>f, "VARIABLES= x  y"
  else      : print >>f, "VARIABLES= x  y  z"
  for i in range(len(elements)) :
    x = [ float(j) for j in elements[i].x ]
    y = [ float(j) for j in elements[i].y ]
    z = [ float(j) for j in elements[i].z ]
    if (d==2) : print >>f, "ZONE T=\"Element ",i,"\", I=2, J=2, F=BLOCK"
    else      : print >>f, "ZONE T=\"Element ",i,"\", I=2, J=2, K=2, F=BLOCK"
    print_dat(f,x)
    print_dat(f,y)
    if (d==3) : print_dat(f,z)
  f.close()

def refine_elements (elements, graph, elements_to_refine) :
  print "Refining Elements:"
  for k in elements_to_refine :
    sys.stdout.write(" Refining: "+str(k[0]))
    sys.stdout.flush()
    new_elem_num      = len(elements)
    elements = refine_element_into_sub_elem (elements, k);
    graph    = refine_graph_for_new_sub_elem(elements, graph, k, new_elem_num)
    sys.stdout.write("\r")

  print
  graph    = remove_refined_elements_from_graph(graph, elements_to_refine, len(elements))
  elements = delete_refined_elements(elements, elements_to_refine)
  return (elements, graph)

def fold_back_into_list(elements, graph, elements_to_refine, orig_num) :
  new_num = dict()
  r = orig_num - len(elements_to_refine)
  for e in elements_to_refine :
    n = e[1]*e[2]*e[3]
    new_num [e[0]] =  ( r, r+n )
    r += n
  new_elements = []
  k = 0
  elem_map = len(elements)*[None]
  for i in range(orig_num) :
    if (not i%1000) : sys.stdout.write("\r Folding: "+str(i))
    if i in new_num :
      for j in range(new_num[i][0], new_num[i][1]) :
        elem_map[j] = len(new_elements)
        new_elements.append(elements[j])
    else :
      elem_map[k] = len(new_elements)
      new_elements.append(elements[k]);
      k += 1
  if len(new_elements) != len(elements) : sys.exit("Folding of elements failed")
  new_graph = []
  for g in graph :
    h = ( elem_map[g[0]], g[1], elem_map[g[2]], g[3] )
    new_graph.append(h)
  new_graph.sort()
  return new_elements, new_graph


def standard_checks(elements,graph,elements_to_refine,orig_num_elem) :

  # for quad:
  additional_elem = 0
  for r in elements_to_refine : additional_elem += r[1]*r[2]*r[3] - 1
  if (len(elements) != orig_num_elem + additional_elem) : sys.exit("Gauss check element fail")
  # graph is unique
  for i in range(len(graph)) :
    for j in range(len(graph)) :
      if (i != j and graph[i] == graph[j]) : sys.exit("Failed uniqueness check")
  # graph is symmetric
  for g in graph :
    found = False
    for h in graph :
      if (g[0]==h[2] and g[1]==h[3] and g[2]==h[0] and g[3]==h[1] ) : found = True; break
    if not found :
      print "Found a connectivity record:",g,"with no matching reverse record."
      sys.exit("Failed symmetry check")

  prev_elem = -1
  prev_side = -1
  for g in graph :
    ref_elem = elements[g[0]]
    ref_side = g[1]
    nbr_elem = elements[g[2]]
    nbr_side = g[3]
    ok = check_subside(ref_elem, ref_side, nbr_elem, nbr_side)
    if not ok : sys.exit("Failed subset check")
    if prev_elem == g[0] and prev_side == g[1] :
      # multiple sides on same element have to be subset of neighbor
      ref_nodes = get_side_nodes(ref_elem, ref_side)
      nbr_nodes = get_side_nodes(nbr_elem, nbr_side)
      ok = subset(nbr_nodes, ref_nodes)
      if not ok : sys.exit("Failed subset handing node check")
    prev_elem = g[0]
    prev_side = g[1]
  return


def parse_command_line() :
  p = optparse.OptionParser()
  options,arguments = p.parse_args()
  if not len(arguments) : sys.exit ("ERROR: must specify base name: refine.py root")
  root = arguments[0]
  return root
  

#  ***************** BEGINNING OF MAIN *****************


def main() :
  start_time = time.time()
  root = parse_command_line() 
  elements = []

  dim                 = determine_dimension(root)
  print "suck_in_mesh_file...."
  elements            = suck_in_mesh_file(root, dim)
  print "suck_in_connectivity_file...."
  graph               = suck_in_connectivity_file(root)
  print "suck_in_refinement_file...."
  elements_to_refine  = suck_in_refinement_file(root, dim, len(elements))

  orig_num_elem      = len(elements)
  orig_num_side      = len(graph)
  elements,graph     = refine_elements (elements, graph, elements_to_refine)

  # Make the refinement independent of the order the elements were refined in.
  elements,graph     = fold_back_into_list(elements,graph,elements_to_refine,orig_num_elem)

  print
  print "Write binary mesh...."
  write_binary_mesh  (elements, root, dim)
  print "Write ascii mesh...."
  write_ascii_mesh   (elements, root, dim)
  print "Write binary graph...."
  write_binary_graph (graph,    root, dim, len(elements))
  print "Write ascii graph...."
  write_ascii_graph  (graph,    root, len(elements))
  print "Write tecplot...."
  write_tecplot      (elements, root, dim)
  # Add sleep to help Cray finish writing files
  time.sleep(5)

  # print "Perform standard checks...."
  # standard_checks    (elements, graph, elements_to_refine, orig_num_elem)

  print "Total wall clock run time in seconds:", time.time()-start_time
  return



main()
