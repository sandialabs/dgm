#!/usr/bin/python

import sys
import json
import getopt
import string
import struct
import optparse


LINE         =0     # Line element in 1d
QUAD         =1     # Quad element in 2d
TRI          =2     # Triangular element in 2d
HEX          =3     # Hexahedral element in 3d
TET          =4     # Tetahedral element in 3d
PYRAMID      =5     # Pyramid element in 3d
NODALLINE    =6     # Nodal 1d line element
NODALQUAD    =7     # Nodal 2d quad element
NODALHEX     =8     # Nodal 3d hex element
NODALTRI     =9     # Nodal 2d triangular element
NODALTET     =10    # Nodal 3d tetrahedral element
SPECTRALLINE =11    # Spectral 1d line element
SPECTRALQUAD =12    # Spectral Quad 2d element
SPECTRALHEX  =13    # Spectral Hex 3d element


nodes = ( 2, 4, 3, 8, 4, 5, 2, 4, 8, 3, 4, 2, 4, 8 );
types = ( "LINE", 
          "QUAD", 
          "TRI", 
          "HEX", 
          "TET", 
          "PYRAMID", 
          "NODALLINE", 
          "NODALQUAD", 
          "NODALHEX", 
          "NODALTRI", 
          "NODALTET", 
          "SPECTRALLINE", 
          "SPECTRALQUAD", 
          "SPECTRALHEX" );

class Element(object) :
  def __init__(self) :
    self.type = TRI       # TRI, QUAD, TET, HEX
    self.x = []
    self.y = []
    self.z = []

def read_binary_mesh (root) :
  elements = []
  try :
    b = open('%s.grd' %(root), 'rb')
  except IOError :
    sys.exit("Mesh file *.grd not found")

  char = '' 
  while '{' != char : char = b.read(1)
  if ('{' == char) : 
    header = char;
    lb = 1 
    while lb :
      char = b.read(1)
      header = header + char 
      if '{' == char : lb = lb + 1;
      if '}' == char : lb = lb - 1;
    char = b.read(1)
    header = header + char 
    json.loads(header)
  else : b.seek(0)
     

  num_ele = struct.unpack('i',b.read(struct.calcsize('i')))[0]
  d       = struct.unpack('i',b.read(struct.calcsize('i')))[0]
  glen    = struct.unpack('i',b.read(struct.calcsize('i')))[0]
  for i in range(num_ele) : elements.append(Element())
   
  for i in range(len(elements)) : elements[i].type = struct.unpack('i',b.read(struct.calcsize('i')))[0]
  disp = [] 
  for i in range(len(elements)) : disp.append(       struct.unpack('i',b.read(struct.calcsize('i')))[0])

  x = []
  y = []
  z = []
  for i in range(glen) :   x.append(struct.unpack('d',b.read(struct.calcsize('d')))[0])
  if (1<d) :
    for i in range(glen) : y.append(struct.unpack('d',b.read(struct.calcsize('d')))[0])
  if (2<d) :
    for i in range(glen) : z.append(struct.unpack('d',b.read(struct.calcsize('d')))[0])
  
  j = 0
  for e in elements :
    for i in range(nodes[e.type]) :
      e.x.append(x[j])
      if (1<d) : e.y.append(y[j])
      if (2<d) : e.z.append(z[j])
      j += 1;
  b.close()
  return elements, d

def read_binary_connectivity_file(root, ne) :
  b = open('%s.cn' %(root), 'rb')

  char = '' 
  while '{' != char : char = b.read(1)
  if ('{' == char) : 
    header = char;
    lb = 1 
    while lb :
      char = b.read(1)
      header = header + char 
      if '{' == char : lb = lb + 1;
      if '}' == char : lb = lb - 1;
    char = b.read(1)
    header = header + char 
    json.loads(header)
  else : b.seek(0)

  displacements = []
  lengths       = []
  graph         = []
  for i in range(ne) : displacements.append(struct.unpack('i',b.read(struct.calcsize('i')))[0])
  for i in range(ne) : lengths      .append(struct.unpack('i',b.read(struct.calcsize('i')))[0])
  L = 0;
  for l in lengths : L += l
  L /= 5
  for i in range(L) : 
    g = struct.unpack('5i',b.read(5*struct.calcsize('i')))
    graph.append(g)
  b.close()
  return graph


def write_ascii_mesh (elements, root, dim) :
  try :
    f = open('%s.msh' %(root), 'w')
  except IOError :
    sys.exit("Mesh file *.msh could not be opened")

  print >>f, "**MESH DATA**"
  print >>f, len(elements),dim,"NE","NSD"

  for i,e in enumerate(elements) :
    print >>f, "ELEMENT",
    print >>f, '%3d ' % i,  
    print >>f, types[e.type]
    for x in e.x : print >>f, '%22.15e' % x,
    print >>f
    for y in e.y  : print >>f,'%22.15e' % y,
    if (len(e.y)) : print >>f
    for z in e.z  : print >>f,'%22.15e' % z,
    if (len(e.z)) : print >>f
  return 


def write_ascii_graph(graph, ne, root) :
  try :
    f = open('%s.con' %(root), 'w')
  except IOError  :
    sys.exit("Connectivity file *.con could not be opened")
  print >>f, "**CONNECTIVITY DATA**"
  print >>f, ne, "ne"
  for g in graph :
    print >>f, "E",
    for i in range(4) : print >>f, '%7d' % g[i],
    print >>f
  return 



def parse_command_line() :
  p = optparse.OptionParser()
  options,arguments = p.parse_args()
  if not len(arguments) : sys.exit ("ERROR: must specify base name: refine.py root")
  root = arguments[0]
  return root
  

#  ***************** BEGINNING OF MAIN *****************


def main() :
  root = parse_command_line() 
  elements = []

  print "suck_in_mesh_file...."
  elements,dim        = read_binary_mesh(root)
  print "suck_in_connectivity_file...."
  graph               = read_binary_connectivity_file(root, len(elements))
  print "write_ascii_mesh...."
  write_ascii_mesh  (elements, root, dim)
  print "write_ascii_graph...."
  write_ascii_graph (graph, len(elements), root)
  print "done"
  return


main()
