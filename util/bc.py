#!/usr/bin/env python

import sys
import getopt
import string
import struct
import optparse
import math

TO_INT = 10000
TRI    = 0 
QUAD   = 1 
TET    = 2 
HEX    = 3 
SPECTRALQUAD   = 4 
SPECTRALHEX    = 5 


def to_int(x) :
  return int(math.floor(.5+TO_INT*float(x)))

class BC(object) :
  def __init__(self) :
    self.top       = 'U'
    self.botom     = 'U'
    self.left      = 'U'
    self.right     = 'U'
    self.front     = 'U'
    self.back      = 'U'

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
    for j in range(len(words)): el.x.append(to_int(float(words[j])))
    words = lines[i].split()
    i = i + 1
    for j in range(len(words)): el.y.append(to_int(float(words[j])))
    if (3==dim) :
      words = lines[i].split()
      i = i + 1
      for j in range(len(words)) : el.z.append(to_int(float(words[j])))
    else :
      for j in range(len(words)) : el.z.append(to_int(float(0)))
    elements.append(el)

  return elements



def find_limits(elements) :
  Max   =  3*[-sys.maxint]
  Min   =  3*[ sys.maxint]
  for e in elements :
    if (min(e.x) < Min[0]) : Min[0] = min(e.x) 
    if (Max[0] < max(e.x)) : Max[0] = max(e.x) 
    if (min(e.y) < Min[1]) : Min[1] = min(e.y) 
    if (Max[1] < max(e.y)) : Max[1] = max(e.y) 
    if (min(e.z) < Min[2]) : Min[2] = min(e.z) 
    if (Max[2] < max(e.z)) : Max[2] = max(e.z) 

  return Min, Max

def hex_node_to_side(X,y) :
 v_num = [[0,1,2,3], [0,1,5,4], [1,2,6,5], [3,2,6,7], [0,3,7,4], [4,5,6,7]]
 for i,s in enumerate(v_num) :
   found = True
   for j in s :
     if X[j] != y : found = False
   if found : 
     side = i 
     break
 if not found : side = -1
 return side 

def create_bc_file_3D(elements,Min,Max,BC) :
  print "**BOUNDARY CONDITION DATA**"
  num = 0
  for e in elements :
    if BC.front  != 'U' and  0<=hex_node_to_side(e.x, Min[0]) : num += 1
    if BC.back   != 'U' and  0<=hex_node_to_side(e.x, Max[0]) : num += 1
    if BC.left   != 'U' and  0<=hex_node_to_side(e.y, Min[1]) : num += 1
    if BC.right  != 'U' and  0<=hex_node_to_side(e.y, Max[1]) : num += 1
    if BC.top    != 'U' and  0<=hex_node_to_side(e.z, Min[2]) : num += 1
    if BC.bottom != 'U' and  0<=hex_node_to_side(e.z, Max[2]) : num += 1

  print num,"number of boundary condition sides "

  if (BC.top    != 'U')   :
    for k,e in enumerate(elements) :
      if ( Min[2] in e.z) :  
        side = hex_node_to_side(e.z,Min[2]) 
        if (0<=side) : print  BC.top,    k, side 
                                           
  if (BC.bottom != 'U')   :
    for k,e in enumerate(elements) :
      if ( Max[2] in e.z) : 
        side = hex_node_to_side(e.z,Max[2]) 
        if (0<=side) : print  BC.bottom, k, side
                                           
  if (BC.front  != 'U')   :
    for k,e in enumerate(elements) :
      if ( Min[0] in e.x) : 
        side = hex_node_to_side(e.x,Min[0]) 
        if (0<=side) : print  BC.front,  k, side
                                           
  if (BC.back   != 'U')   :
    for k,e in enumerate(elements) :
      if ( Max[0] in e.x) : 
        side = hex_node_to_side(e.x,Max[0]) 
        if (0<=side) : print  BC.back,   k, side
                                           
  if (BC.left   != 'U')   :
    for k,e in enumerate(elements) :
      if ( Min[1] in e.y) : 
        side = hex_node_to_side(e.y,Min[1]) 
        if (0<=side) : print  BC.left,   k, side
                                           
  if (BC.right  != 'U')   :
    for k,e in enumerate(elements) :
      if ( Max[1] in e.y) : 
        side = hex_node_to_side(e.y,Max[1]) 
        if (0<=side) : print  BC.right,  k, side


def create_bc_file_2D(elements,Min,Max,BC) :
  print "** Boundary Conditions **"       
  num = 0
  for e in elements :
    if BC.top    != 'U' and Min[1] in e.y : num += 1
    if BC.bottom != 'U' and Max[1] in e.y : num += 1
    if BC.left   != 'U' and Min[0] in e.x : num += 1
    if BC.right  != 'U' and Max[0] in e.x : num += 1

  print num,"nbc"

  for k,e in enumerate(elements) :
    if BC.top    != 'U' and Min[1] in e.y : print  BC.top,    k, e.y.index(Min[1])
  for k,e in enumerate(elements) :
    if BC.bottom != 'U' and Max[1] in e.y : print  BC.bottom, k, e.y.index(Max[1])
  for k,e in enumerate(elements) :
    if BC.left   != 'U' and Min[0] in e.x : 
      if (Min[0] == e.x[3])               : print  BC.left,   k, 3
      else                                : print  BC.left,   k, e.x.index(Min[0])
  for k,e in enumerate(elements) :
    if BC.right  != 'U' and Max[0] in e.x : print  BC.right,  k, e.x.index(Max[0])

def parse_command_line() :
  p = optparse.OptionParser()
  p.add_option('--root',   '-r',   action='store', type='string')
  p.add_option('--top',    '--tp', action='store', type='choice', choices=['Z','F','U','A'], default='U')
  p.add_option('--bottom', '--bm', action='store', type='choice', choices=['Z','F','U'], default='U')
  p.add_option('--left',   '--lt', action='store', type='choice', choices=['Z','F','U'], default='U')
  p.add_option('--right',  '--rt', action='store', type='choice', choices=['Z','F','U'], default='U')
  p.add_option('--front',  '--ft', action='store', type='choice', choices=['Z','F','U'], default='U')
  p.add_option('--back',   '--bk', action='store', type='choice', choices=['Z','F','U'], default='U')
  options,arguments = p.parse_args()
  if not options.root : sys.exit ("ERROR: must specify --root option")
  root       = options.root
  b          = BC()
  b.top      = options.top
  b.bottom   = options.bottom
  b.left     = options.left
  b.right    = options.right
  b.front    = options.front
  b.back     = options.back
  return root, b
  

def main () :
  root, bc = parse_command_line() 
  dim      = determine_dimension(root)
  elements = suck_in_mesh_file(root,dim)
  Min,Max  = find_limits(elements) 
  if dim == 3 : create_bc_file_3D(elements, Min,Max,bc)
  else        : create_bc_file_2D(elements, Min,Max,bc)
  
main()

