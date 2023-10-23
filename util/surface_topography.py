#!/usr/bin/env python
from __future__ import print_function

import sys
import getopt
import string
import struct
import optparse
import copy
import json

TO_INT = 10000
TRI    = 0 
QUAD   = 1 
SPECTRALQUAD   = 2 
TET    = 3 
HEX    = 4 

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
  for i in range(len(lines)) :
    words = lines[i].split()
    surface.append((float(words[0]), float(words[1])))
  return surface

def suck_in_curve_file (root) :
  try :
    f = open('%s.crv' %(root), 'r')
    lines = f.readlines()
    f.close()
    s = " "
    lines = s.join(lines)
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
  except  json.JSONDecodeError as e:
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

def snap_mesh_to_surf(elements, min_depth, max_depth, ref_depth, surface) :
  skewed = []
  for n,e in enumerate(elements) :
    x = e.x 
    y = e.y 

    for i in range(len(x)) :
      d0 = -999999
      # interploate surface to element grid
      # interpolated surface value is relative to ref_depth
      for j in range(len(surface)-1) :
        if surface[j][0] <= x[i] and x[i] <= surface[j+1][0] :
          r  = (x[i]-surface[j][0])/(surface[j+1][0]-surface[j][0])
          d0 = (1-r)*surface[j][1] + r*surface[j+1][1] 
          break

      # deform elements

      # convert depth into relative to ref_depth
      t = y[i] - ref_depth

      if d0 != -999999 and t >= min_depth and t <= max_depth :

        # deform upward
        if t < 0 :
          r = -d0/min_depth
          t = (1-r)*t-d0
          pass
        # deform downward
        else :
          r = d0/max_depth
          t = (1-r)*t+d0

        y[i] = t + ref_depth

        skewed.append(n)

  return frozenset(skewed)

def snap_hanging_nodes_to_sides(elements, graph) :
  graph.sort()
  side_map = {} 
  for g in graph :
    k = (g[0],g[1])
    v = [g[2],g[3]]
    side_map.setdefault(k,[]).append(v)
  for n,e in enumerate(elements) :
    x = e.x 
    y = e.y 
    for s in range(len(x)) :
      k = (n,s)
      if k in side_map :
        l = side_map[k]
        if 1 == len(l) :
          k = tuple(l[0])
          l = side_map[k]
          if 1 < len(l) :
            E = elements[k[0]]
            S = k[1]
            X = E.x
            Y = E.y
            x1 = x[s]
            x2 = x[(s++1)%4]
            X1 = X[S]
            X2 = X[(S+1)%4]
            if X1 != X2 : 
              if x1 != X1 and x1 != X2:
                r = (X2 - x1)/(X2 - X1)
                y[s] = r*Y[S]+(1-r)*Y[(S+1)%4]
              if x2 != X1 and x2 != X2:
                r = (X2 - x2)/(X2 - X1)
                y[(s++1)%4] = r*Y[S]+(1-r)*Y[(S+1)%4]
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
  p.add_option('--max_depth', '-d', action='store', type='float')
  p.add_option('--min_depth', '-m', action='store', type='float')
  p.add_option('--ref_depth', '-r', action='store', type='float')
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

  if arg_min_depth > 0:
    raise RuntimeError('ERROR: min_depth should <= 0.')
  if arg_max_depth < 0:
    raise RuntimeError('ERROR: max_depth should >= 0.')

  dim = determine_dimension(root)

  if not dim == 2:
    raise RuntimeError('ERROR: only 2D meshes supported.')

  elements, min_depth, max_depth = suck_in_mesh_file(root,dim)
  graph                          = suck_in_connectivity_file(root)
  surface                        = suck_in_surface_file(root)
  curves                         = suck_in_curve_file(root)

  if arg_ref_depth+arg_min_depth < min_depth:
    raise RuntimeError('ERROR: ref_depth+min_depth smaller than mesh min_depth!')

  if arg_ref_depth+arg_max_depth > max_depth:
    raise RuntimeError('ERROR: ref_depth+max_depth larger than mesh max_depth!')

  #if arg_max_depth != 0 : max_depth = arg_max_depth

  #if arg_min_depth != 0 : min_depth = arg_min_depth

  skewed = snap_mesh_to_surf(elements, arg_min_depth, arg_max_depth, arg_ref_depth, surface)
  snap_hanging_nodes_to_sides(elements, graph)
  write_crv_file  (curves, root, skewed)
  write_ascii_mesh(elements, root, dim)
  #write_tecplot   (elements, root, dim) 

main()
                               

