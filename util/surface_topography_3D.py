#!/usr/bin/env python
from __future__ import print_function

import sys
import getopt
import string
import struct
import optparse
import copy
import json
import numpy
import math
from scipy import spatial

TO_INT = 10000
TRI    = 0 
QUAD   = 1 
SPECTRALQUAD   = 2 
TET    = 3 
HEX    = 4 
SPECTRALHEX   = 5 

def to_int(x) :
  return int(TO_INT*float(x))

class Element(object) :
  def __init__(self) :
    type   = HEX
    self.x = []
    self.y = []
    self.z = []

def determine_dimension (root) :
  f = open('%s.msh' %(root), 'r')
  lines = f.readlines()
  f.close()
  dim=0
  words = lines[1].split()
  if (3<len(words) and words[3] == "NSD") : dim = int(words[1])
  else : sys.exit("Did not find NSD in mesh file.")
  return dim 

def suck_in_surface_file (root) :
  try :
    f = open('%s.sur' %(root), 'r')
  except IOError :
    sys.exit("Surface file *.sur not found")
  lines = f.readlines()
  f.close()
  surface = []
  for i in range(len(lines)): 
    words = lines[i].split()
    surface.append((float(words[0]), float(words[1]), float(words[2])))
  return surface

def suck_in_curve_file (root) :
  try :
    f = open('%s.crv' %(root), 'r')
    lines = f.readlines()
    f.close()
  except IOError :
    lines = """{
  "Title" : "Curved side specification",
  "Curved side location" : "Inline",
  "Curve types" : [
    {
      "Verbosity" : 0,
      "Type" : "Straight",
      "Name" : "skew"
    }
  ],
  "Curved sides" : [ ]
   }"""
  try :
    curves = json.loads(lines) 
  except  JSONDecodeError as e:
    print ("JSON decoder error on %s.crv file."%(root))
    print ("Message:",e.msg)
    print ("Line:",e.lineno)
    print ("Column:",e.colno)
    sys.exit("Curve file *.crv must be in JSON format.")
    
  if "Inline" != curves["Curved side location"] :
    print ("Curve %s.crv file must have 'Curved side location : Inline'"%(root))
  types = curves["Curve types"];
  found_skew = False
  for type in types :
    if "Straight" == type["Type"] and "skew" == type["Name"] : 
      found_skew = True
  if not found_skew :
    types.append({u"Type" : u"Straight",  u"Name" : u"skew"})
  return curves

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
  max_depth = 0
  min_depth = 0
  while i < len(lines):
    words = lines[i].split()
    i = i + 1 
    if (words[0] != "ELEMENT") : sys.exit( "Parser Error 'ELEMENT' not found.")
    el = Element()
    if    (words[2] == "TRI")  : el.type = TRI 
    elif  (words[2] == "QUAD") : el.type = QUAD
    elif  (words[2] == "SPECTRALQUAD") : el.type = SPECTRALQUAD
    elif  (words[2] == "TET")  : el.type = TET 
    elif  (words[2] == "HEX")  : el.type = HEX 
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
    maxd = 0
    mind = 0
    if (3==dim) :
      maxd = max(el.z)
      mind = min(el.z)
    else :
      maxd = max(el.y)
      mind = min(el.y)
    if (max_depth < maxd) : max_depth = maxd
    if (mind < min_depth) : min_depth = maxd
    elements.append(el)

  return elements, min_depth, max_depth

def suck_in_connectivity_file(root) :
  try :
    f = open('%s.con' %(root), 'r')
  except IOError  :
    sys.exit("Connectivity file *.con not found")
  lines = f.readlines()
  f.close()
  graph = []
  for i in range(2,len(lines)):
    words = lines[i].split()
    c = (int(words[1]), int(words[2]), int(words[3]), int(words[4]))
    graph.append(c)
  print
  return graph

def snap_mesh_to_surf (elements, min_depth, max_depth, ref_depth, surface) :
  network = [] 
  for x in surface : network.append([x[0],x[1]])
  print ("Construct spatial.KDTree....")
  sys.stdout.flush()
  tree = spatial.KDTree(network)
  skewed = []
  print ("Snap nodes to surface....")
  sys.stdout.flush()
  for n,e in enumerate(elements) :
    x = e.x 
    y = e.y 
    for i in range(len(x)) :
      z = -999999
      p = [x[i],y[i]]
      dist, indexes = tree.query(p,3)
      p0 = network[indexes[0]]
      p1 = network[indexes[1]]
      p2 = network[indexes[2]]
      m  = (p1[1]-p2[1])*(p0[0]-p2[0]) + (p2[0]-p1[0])*(p0[1]-p2[1])
      if (0==m) : 
        z = surface[indexes[0]][2]
      else :
        w0 = (p1[1]-p2[1])*( p[0]-p2[0]) + (p2[0]-p1[0])*( p[1]-p2[1])
        w1 = (p2[1]-p0[1])*( p[0]-p2[0]) + (p0[0]-p2[0])*( p[1]-p2[1])
     
        w0 = w0 / m
        w1 = w1 / m
        w2 = 1 - w0 - w1
        z = w0*surface[indexes[0]][2] + w1*surface[indexes[1]][2] + w2*surface[indexes[2]][2]
      
#      if z != -999999  and e.z[i] < max_depth :
#        r = (z-min_depth)/(max_depth-min_depth)
#        e.z[i] = (1-r)*e.z[i] + r*max_depth
#        skewed.append(n)

      # convert depth into relative to ref_depth
      t = e.z[i] - ref_depth

      if z != -999999 and t >= min_depth and t <= max_depth :

        # deform upward
        if t < 0 :
          r = -z/min_depth
          t = (1-r)*t-z
          pass
        # deform downward
        else :
          r = z/max_depth
          t = (1-r)*t+z

        e.z[i] = t + ref_depth

        skewed.append(n)
  return frozenset(skewed)

def interpolation_coeff (x,y,p) :
# Given 
#   phi_0 = (1-l)(1-m)/4
#   phi_1 = (1+l)(1-m)/4
#   phi_2 = (1+l)(1+m)/4
#   phi_3 = (1-l)(1+m)/4
# and
# Phi_x = x_0 phi_0 + x_1 phi_1 + x_2 phi_2 + x_3 phi_3 = p_x
# Phi_x = y_0 phi_0 + y_1 phi_1 + y_2 phi_2 + x_3 phi_3 = p_y
# 
# Solve for l and m.  This could be done with a Newton
# method.  But it is only slighlty non-linear and can be
# solved directly.

  invA =[[ 0.25,  0.25, 0.25,  0.25], 
         [-0.25,  0.25, 0.25, -0.25], 
         [-0.25, -0.25, 0.25,  0.25], 
         [ 0.25, -0.25, 0.25, -0.25],]
  a=numpy.zeros(4)
  b=numpy.zeros(4)

# Find the coefficients, a and b for:
#  a_0 + a_1 l + a_2 m + a_3 l m = p_x -> a_0 + (a_1+a_3 m)l + a_2 m = p_x
#  b_0 + b_1 l + b_2 m + b_3 l m = p_y -> b_0 + (b_1+b_3 m)l + b_2 m = p_y
  for i in range(4) : a[i] = numpy.dot(numpy.array(invA[i]), numpy.array(x))
  for i in range(4) : b[i] = numpy.dot(numpy.array(invA[i]), numpy.array(y))

# Eliminate l to get a quadradic in m: a m^2 + b m + c = 0
  aa = a[3] * b[2] - a[2] * b[3]
  bb = a[3] * b[0] - a[0] * b[3] + a[1] * b[2] - a[2] * b[1] + p[0] * b[3] - p[1] * a[3]
  cc = a[1] * b[0] - a[0] * b[1] + p[0] * b[1] - p[1] * a[1]
# apply quadratic formula
  if abs(aa) < .0000000001 :  # degenerate linear case
    m = -cc / bb; 
  else :
    if bb*bb - 4*aa*cc < 0: sys.exit("Invalid element found. bb*bb - 4*aa*cc")
    det = math.sqrt(bb*bb - 4*aa*cc)
    m = (-bb+det)/(2*aa)
  
  if 0 == a[1]+a[3]*m and 0 == b[1]+b[3]*m : 
    # not sure what would cause this
    print ("X coordinates of quad:",x)
    print ("Y coordinates of quad:",y)
    print ("Point to interpolate to:",p)
    sys.exit("Invalid element found. Can not find parametric point of p in quad.") 
  if 0 != a[1]+a[3]*m :
    l = (p[0]-a[0]-a[2]*m)/(a[1]+a[3]*m)
  else :
    l = (p[1]-b[0]-b[2]*m)/(b[1]+b[3]*m)

  coeff = [.25*(1-l)*(1-m), .25*(1+l)*(1-m), .25*(1+l)*(1+m), .25*(1-l)*(1+m)]
# Check
  P0 = coeff[0]*x[0] + coeff[1]*x[1] + coeff[2]*x[2] + coeff[3]*x[3]
  P1 = coeff[0]*y[0] + coeff[1]*y[1] + coeff[2]*y[2] + coeff[3]*y[3]
  d0 = abs(P0 - p[0])/(.000000001 + abs(max(p[0],P0)))
  d1 = abs(P1 - p[1])/(.000000001 + abs(max(p[1],P1)))
  if .00001 < d0 or .00001 < abs(P0 - p[0]): 
    print (" P0 Check:",P0," verses ",p[0]," abs:",P0 - p[0]," rel:",d0,aa,bb,cc)
  if .00001 < d1 or .00001 < abs(P1 - p[1]): 
    print (" P1 Check:",P1," verses ",p[1]," abs:",P1 - p[1]," rel:",d1,aa,bb,cc)
  return coeff
 
def snap_hanging_nodes_to_sides(elements, graph) :
  changed = False
  V = [[0,1,2,3],[0,1,5,4],[1,2,6,5],[3,2,6,7],[0,3,7,4],[4,5,6,7]]
  graph.sort()
  side_map = {} 
  for g in graph :
    k = (g[0],g[1])
    l = [g[2],g[3]]
    side_map.setdefault(k,[]).append(l)

  for key, value in side_map.items() :
# Is this a hanging node side:
    if 1 < len(value) :
      E = elements[key[0]]
      if E.type == TET : sys.exit("Tet elements not sypported yet.")
      S = key[1]
      X = E.x
      Y = E.y
      Z = E.z
      v = V[S]
      CX = [X[v[0]],X[v[1]],X[v[2]],X[v[3]]]
      CY = [Y[v[0]],Y[v[1]],Y[v[2]],Y[v[3]]]
      CZ = [Z[v[0]],Z[v[1]],Z[v[2]],Z[v[3]]]
      nodes = []
      for i in range(len(CX)) : nodes.append((CX[i], CY[i]))
# Is side vertial or horizontal:
      if max(CX) != min(CY) and max(CY) != min(CY) : 
# Iterate sub-sides:
        for sub in value :
          e = elements[sub[0]]
          s = sub[1]
          x = e.x 
          y = e.y 
          v = V[s]
          Cx = [x[v[0]],x[v[1]],x[v[2]],x[v[3]]]
          Cy = [y[v[0]],y[v[1]],y[v[2]],y[v[3]]]
          for i in range(len(Cx)) :
            if (Cx[i], Cy[i]) not in nodes :
              coeff = interpolation_coeff (CX,CY,[Cx[i],Cy[i]]) 
              e.z[v[i]] = numpy.dot(coeff, CZ)
  return    

def write_ascii_mesh(elements, root, d) :
  f = open('%s_sur.msh' %(root), 'w')
  print("**MESH DATA**", file=f)
  print(len(elements), d, "NE NSD", file=f)

  for i in range(len(elements)) :
    x = [float(j) for j in elements[i].x]
    y = [float(j) for j in elements[i].y]
    z = [float(j) for j in elements[i].z]
    if    (elements[i].type == QUAD)       : s = " QUAD"
    elif  (elements[i].type==SPECTRALQUAD) : s = " SPECTRALQUAD"
    elif  (elements[i].type==SPECTRALHEX ) : s = " SPECTRALHEX"
    else                                   : s = " HEX"
    print("ELEMENT %3d %s" % (i,s), file=f)
    for j in range(len(x)) : print( "%22.15e " % (x[j]), file=f, end=''),
    print(file=f)
    for j in range(len(y)) : print( "%22.15e " % (y[j]), file=f, end=''),
    print(file=f)
    if (3==d) :
      for j in range(len(y)) : print("%22.15e " % (z[j]), file=f, end=''),
      print(file=f)
  f.close()

def print_dat(f,x) :
  if (8==len(x)) :
    print (\
    " %13.9e %13.9e %13.9e %13.9e %13.9e %13.9e %13.9e %13.9e"  \
    % (x[0],x[1],x[3],x[2],x[4],x[5],x[7],x[6]), file=f)
  else :
    print (" %13.9e  %13.9e  %13.9e  %13.9e" % (x[0], x[1], x[3], x[2]), file=f)

def write_crv_file  (curves, root, skewed) :
  f = open('%s_sur.crv' %(root), 'w')
  sides = curves["Curved sides"];
  for e in skewed :
    side = {"Element" : e, "Side" : 0, "Curve" : "skew"}
    sides.append(side)
  json_string = json.dumps(curves, indent=2, sort_keys=True)
  print (json_string, file=f)

def write_tecplot(elements, root, d) :
  f = open('%s_sur.dat' %(root), 'w')
  print ("TITLE=\"Mesh Check\"", file=f)
  if (2==d) : print ("VARIABLES= x  y", file=f)
  else      : print ("VARIABLES= x  y  z", file=f)
  for i in range(len(elements)) :
    x = [ float(j) for j in elements[i].x ]
    y = [ float(j) for j in elements[i].y ]
    z = [ float(j) for j in elements[i].z ]
    if (d==2) : print( "ZONE T=\"Element ",i,"\", I=2, J=2, F=BLOCK", file=f)
    else      : print( "ZONE T=\"Element ",i,"\", I=2, J=2, K=2, F=BLOCK", file=f)
    print_dat(f,x)
    print_dat(f,y)
    if (d==3) : print_dat(f,z)

def parse_command_line() :
  p = optparse.OptionParser()
  p.add_option('--max_depth', '-d', action='store', type='string')
  p.add_option('--min_depth', '-m', action='store', type='string')
  p.add_option('--ref_depth', '-r', action='store', type='string')
  p.set_defaults(max_depth=0)
  p.set_defaults(min_depth=0)
  p.set_defaults(ref_depth=0)
  options,arguments = p.parse_args()
  if not len(arguments) : sys.exit ("ERROR: must specify base:surface_topography.py root")
  root  = arguments[0]
  max_depth = float(options.max_depth)
  min_depth = float(options.min_depth)
  ref_depth = float(options.ref_depth)
  return root, min_depth, max_depth, ref_depth
  

def main () :
  root, arg_min_depth, arg_max_depth, arg_ref_depth = parse_command_line() 
  dim      = determine_dimension(root)
  if not dim == 3  : sys.exit ("ERROR: only 3D meshes supported.")

  if arg_min_depth > 0:
    raise RuntimeError('ERROR: min_depth should <= 0.')
  if arg_max_depth < 0:
    raise RuntimeError('ERROR: max_depth should >= 0.')

  print ("suck_in_mesh_fil....")
  sys.stdout.flush()
  elements, min_depth, max_depth = suck_in_mesh_file(root,dim)

  print ("suck_in_connectivity_file....")
  sys.stdout.flush()
  graph                          = suck_in_connectivity_file(root)

  print ("suck_in_surface_file....")
  sys.stdout.flush()
  surface                        = suck_in_surface_file(root)

  print ("suck_in_curve_fil....")
  sys.stdout.flush()
  curves                         = suck_in_curve_file(root)
#  if arg_max_depth != 0 : max_depth = arg_max_depth

  print ("snap_mesh_to_surf....")
  sys.stdout.flush()
  skewed = snap_mesh_to_surf(elements, arg_min_depth, arg_max_depth, arg_ref_depth, surface)

  print ("snap_hanging_nodes_to_sides....")
  sys.stdout.flush()
  snap_hanging_nodes_to_sides(elements, graph)

  print ("write_crv_file....")
  sys.stdout.flush()
  write_crv_file  (curves, root, skewed)

  print ("write_ascii_mesh....")
  sys.stdout.flush()
  write_ascii_mesh(elements,root, dim)

  print ("write_tecplot....")
  sys.stdout.flush()
  write_tecplot   (elements, root, dim) 

main()
                               

