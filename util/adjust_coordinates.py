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
    self.fr    = 3*[None]
    self.to    = 3*[None]

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

def longest_dim(x, p) :
  d = 3*[None]
  for i in range(3) : d[i] = to_int(abs(x[pow(2,i)] - x[0]))
  longest = 0 
  for i in range(3) :
    j = (i+1)%3
    if p[i] == p[j] and d[i] == d[j] and d[i] == max(d) : longest = -1 

  if -1 < longest :
    for i in p : 
      if i != -1 : d[i] = -1
    longest = d.index(max(d))

  return longest

def determine_cut_direction (b,e) :
  d = 3*[None]
  for i in range(3) : d[i] = -1
  while min(d) == -1 :
    d[0] = longest_dim(e.x, d)
    if min(d) == 0 : break
    d[1] = longest_dim(e.y, d)
    if min(d) == 0 : break
    d[2] = longest_dim(e.z, d)
  c = 3*[None]
  return c

def adjust_coordinates (elements, b) :
  centroid = 3*[None]
  for e in elements :
    for i in range(len(e.x)) : 
      for j in range(len(b.fr[0])) :
        if (to_int(e.x[i]) == to_int(b.fr[0][j])) : 
          e.x[i] = b.to[0][j]
    for i in range(len(e.y)) : 
      for j in range(len(b.fr[1])) :
        if (to_int(e.y[i]) == to_int(b.fr[1][j])) : 
          e.y[i] = b.to[1][j]
    for i in range(len(e.z)) : 
      for j in range(len(b.fr[2])) :
        if (to_int(e.z[i]) == to_int(b.fr[2][j])) : 
          e.z[i] = b.to[2][j]
  return  elements

def write_ascii_mesh(elements, root, d) :
  f = open('%s_adj.msh' %(root), 'w')
  if (2==d) : s = " QUAD"
  else        : s = " HEX"
  print >>f, "**MESH DATA**"
  print >>f, len(elements), d, "NE NSD"
  for i in range(len(elements)) :
    x = [float(j) for j in elements[i].x]
    y = [float(j) for j in elements[i].y]
    z = [float(j) for j in elements[i].z]
    print >>f, "ELEMENT %3d %s" % (i,s)
    for j in range(len(x)) : print >>f, "%22.15e" % (x[j]),
    print >> f
    for j in range(len(y)) : print >>f, "%22.15e" % (y[j]),
    print >> f
    if (3==d) :
      for j in range(len(y)) : print >>f, "%22.15e" % (z[j]),
      print >> f
  f.close()

def parse_command_line() :
  p = optparse.OptionParser()
  p.add_option('--root', '-r', action='store', type='string')
  p.add_option('--x_from', '--xf',   action='append', type='float')
  p.add_option('--y_from', '--yf',   action='append', type='float')
  p.add_option('--z_from', '--zf',   action='append', type='float')
  p.add_option('--x_to',   '--xt',   action='append', type='float')
  p.add_option('--y_to',   '--yt',   action='append', type='float')
  p.add_option('--z_to',   '--zt',   action='append', type='float')
  options,arguments = p.parse_args()
  print options
  if not options.root : sys.exit ("ERROR: must specify --root option")
  b = Box()
  root       = options.root
  if (options.x_from != None and options.x_to == None) : sys.exit("x_from w/o x_to")
  if (options.x_from == None and options.x_to != None) : sys.exit("x_from w/o x_to")
  if (options.y_from != None and options.y_to == None) : sys.exit("x_from w/o x_to")
  if (options.y_from == None and options.y_to != None) : sys.exit("x_from w/o x_to")
  if (options.z_from != None and options.z_to == None) : sys.exit("x_from w/o x_to")
  if (options.z_from == None and options.z_to != None) : sys.exit("x_from w/o x_to")
  if (options.x_from != None) :
    if (len(options.x_from) != len(options.x_to)) : sys.exit("# x_from != # x_to")
  if (options.y_from != None) :
    if (len(options.y_from) != len(options.y_to)) : sys.exit("# y_from != # y_to")
  if (options.z_from != None) :
    if (len(options.z_from) != len(options.z_to)) : sys.exit("# z_from != # z_to")
  b.fr[0] = []
  b.fr[1] = []
  b.fr[2] = []
  b.to[0] = []
  b.to[1] = []
  b.to[2] = []
  if (options.x_from != None) : 
    for i in options.x_from : b.fr[0].append(i)
  if (options.y_from != None) : 
    for i in options.y_from : b.fr[1].append(i)
  if (options.z_from != None) : 
    for i in options.z_from : b.fr[2].append(i)
  if (options.x_to   != None) : 
    for i in options.x_to   : b.to[0].append(i)
  if (options.y_to   != None) : 
    for i in options.y_to   : b.to[1].append(i)
  if (options.z_to   != None) : 
    for i in options.z_to   : b.to[2].append(i)
  print b.fr, b.to 
  return root, b


def main () :
  root, bounds = parse_command_line() 
  dim      = determine_dimension(root)
  elements = suck_in_mesh_file(root,dim)
  elements = adjust_coordinates(elements, bounds)
  write_ascii_mesh  (elements, root, dim)
  exit()
  


main()
                               

