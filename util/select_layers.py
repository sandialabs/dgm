#!/usr/bin/env python

import sys
import getopt
import string
import struct
import optparse
import copy

TO_INT = 10000
TRI    = 0 
QUAD   = 1 
TET    = 2 
HEX    = 3 

def to_int(x) :
  return int(TO_INT*float(x))

class Element(object) :
  def __init__(self) :
    type   = HEX
    self.x = []
    self.y = []
    self.z = []

class Box(object) :
  def __init__(self) :
    self.lower = 3*[None]
    self.upper = 3*[None]
    self.cuts  = 3*[None]

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

  return elements

def longest_dim(x, p,dim) :
  d = 3*[None]
  for i in range(dim) : d[i] = to_int(abs(x[pow(2,i)] - x[0]))
  longest = 0 
  for i in range(dim) :
    j = (i+1)%3
    if p[i] == p[j] and d[i] == d[j] and d[i] == max(d) : longest = -1 

  if -1 < longest :
    for i in p : 
      if i != -1 : d[i] = -1
    longest = d.index(max(d))

  return longest

def determine_cut_direction (b,e,dim) :
  d = 3*[None]
  for i in range(3) : d[i] = -1
  while min(d) == -1 :
    d[0] = longest_dim(e.x, d,dim)
    if min(d) == 0 : break
    d[1] = longest_dim(e.y, d,dim)
    if min(d) == 0 : break
    d[2] = longest_dim(e.z, d,dim)
  c = dim*[None]
  for i in range(dim) : c[d[i]] = b.cuts[i]
  return c

def create_rfn_file (elements, b, dim) :
  centroid = 3*[None]
  for i,e in enumerate(elements) :
    centroid[0] = 0
    centroid[1] = 0
    centroid[2] = 0
    for x in e.x : centroid[0] += x 
    for y in e.y : centroid[1] += y 
    for z in e.z : centroid[2] += z 
    for j in range(3) : centroid[j] /= len(e.x)
    for j in range(3) : centroid[j] = to_int(centroid[j])
    inside = True
    for j in range(3) :
      if centroid[j] < b.lower[j] or b.upper[j] < centroid[j] : inside = False
    if inside :
      c = determine_cut_direction(b,e,dim);
      if (3==dim) :
        print i, c[0], c[1], c[2]
      else :
        print i, c[0], c[1]
  return    

def parse_command_line() :
  p = optparse.OptionParser()
  p.add_option('--root', '-r', action='store', type='string')
  p.add_option('--x_lower', '--xl',  action='store', type='float', default='-9999999')
  p.add_option('--y_lower', '--yl',  action='store', type='float', default='-9999999')
  p.add_option('--z_lower', '--zl',  action='store', type='float', default='-9999999')
  p.add_option('--x_upper', '--xu',  action='store', type='float', default='9999999')
  p.add_option('--y_upper', '--yu',  action='store', type='float', default='9999999')
  p.add_option('--z_upper', '--zu',  action='store', type='float', default='9999999')
  p.add_option('--x_cuts',  '--xc',  action='store', type='int',   default='0')
  p.add_option('--y_cuts',  '--yc',  action='store', type='int',   default='0')
  p.add_option('--z_cuts',  '--zc',  action='store', type='int',   default='0')
  options,arguments = p.parse_args()
  print options
  if not options.root : sys.exit ("ERROR: must specify --root option")
  b = Box()
  root       = options.root
  b.lower[0] = to_int(options.x_lower)
  b.lower[1] = to_int(options.y_lower)
  b.lower[2] = to_int(options.z_lower)
  b.upper[0] = to_int(options.x_upper)
  b.upper[1] = to_int(options.y_upper)
  b.upper[2] = to_int(options.z_upper)
  b.cuts[0]  = options.x_cuts
  b.cuts[1]  = options.y_cuts
  b.cuts[2]  = options.z_cuts
  return root, b
  

def main () :
  root, bounds = parse_command_line() 
  dim      = determine_dimension(root)
  elements = suck_in_mesh_file(root,dim)
  create_rfn_file(elements, bounds, dim)
  


main()
                               

