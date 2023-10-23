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


def create_ord_file(elements,L,O) :
  print "** Order data **"
  dim = 3*[None]
  for i,e in enumerate(elements) :
    dim[0] = max(e.x) - min(e.x) 
    dim[1] = max(e.y) - min(e.y) 
    dim[2] = max(e.z) - min(e.z) 
    elem_size = min(dim)
    for j in range(len(L)) :
      if elem_size <= L[j] and 0 < O[j] : 
        print i, O[j], 0
        break



def parse_command_line() :
  p = optparse.OptionParser()
  p.add_option('--root',   '-r',   action='store', type='string')
  p.add_option('--length_0', '--L0', action='store', type='float',  default='-1')
  p.add_option('--length_1', '--L1', action='store', type='float',  default='-1')
  p.add_option('--length_2', '--L2', action='store', type='float',  default='-1')
  p.add_option('--length_3', '--L3', action='store', type='float',  default='-1')
  p.add_option('--order_0',  '--O0', action='store', type='int',    default='-1')
  p.add_option('--order_1',  '--O1', action='store', type='int',    default='-1')
  p.add_option('--order_2',  '--O2', action='store', type='int',    default='-1')
  p.add_option('--order_3',  '--O3', action='store', type='int',    default='-1')
  options,arguments = p.parse_args()
  if not options.root : sys.exit ("ERROR: must specify --root option")
  root       = options.root
  L          = 4*[None]
  O          = 4*[None]
  L   [0]    = to_int(options.length_0)
  L   [1]    = to_int(options.length_1)
  L   [2]    = to_int(options.length_2)
  L   [3]    = to_int(options.length_3)
  O   [0]    = options.order_0
  O   [1]    = options.order_1
  O   [2]    = options.order_2
  O   [3]    = options.order_3
  return root,L,O   
  

def main () :
  root, L, O = parse_command_line() 
  dim        = determine_dimension(root)
  elements   = suck_in_mesh_file(root,dim)
  create_ord_file(elements,L,O)


main()

