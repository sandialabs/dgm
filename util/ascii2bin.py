#!/usr/bin/python

import sys
import json
import time
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

def read_ascii_mesh (root, dim) :
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
    el.type = -1
    for j, t in enumerate(types) :
      if (words[2] == t) : el.type = j
    if (el.type == -1) : sys.exit( "Parser Error element type not found.")

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


def read_ascii_graph(root) :
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
  return graph


def write_binary_mesh (elements,root,d) :

  b = open('%s.grd' %(root), 'w')
  header = {}
  header["Date"]= time.asctime()
  header["Name"]= '%s.grd' % (root)
  header["Nel"] = len(elements)
  header["Nsd"] = d
  header["Types"] = {}
  header["Types"]["ByteOrder"] = "LittleEndian"
  header["Types"]["GlobalSize"]= "int32" 
  header["Types"]["LocalSize"] = "int32" 
  header["Types"]["Scalar"]    = "float64"
  header["Version"] = 1
  print >> b, json.dumps(header,indent=2,sort_keys=True) 
  b.close()


  b = open('%s.grd' %(root), 'ab')
  b.write(struct.pack('i', len(elements)))
  b.write(struct.pack('i', d))
  glen = 0;
  for e in elements : glen += nodes[e.type]

  b.write(struct.pack('i', glen))
  for e in elements : b.write(struct.pack('i', e.type))
  disp = 0

  for i in range(len(elements)) :
    b.write(struct.pack('i', disp))
    disp += nodes[elements[i].type] 

  for e in elements :
    for x in e.x : b.write(struct.pack('d',float(x)))
  if (1<d) :
    for e in elements :
      for y in e.y : b.write(struct.pack('d',float(y)))
  if (2<d) :
    for e in elements :
      for z in e.z : b.write(struct.pack('d',float(z)))
  b.close()


def write_binary_graph(graph, root, d, ne) :

  b = open('%s.cn' %(root), 'w')
  header = {}
  header["Date"]= time.asctime()
  header["Name"]= '%s.cn' % (root)
  header["Nel"] = ne 
  header["Nsd"] = d
  header["Types"] = {}
  header["Types"]["ByteOrder"] = "LittleEndian"
  header["Types"]["GlobalSize"]= "int32" 
  header["Types"]["LocalSize"] = "int32" 
  header["Types"]["Scalar"]    = "float64"
  header["Version"] = 1 
  print >> b, json.dumps(header,indent=2,sort_keys=True) 
  b.close()

  b = open('%s.cn' %(root), 'ab')
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

  dim                 = determine_dimension(root)
  print "read_ascii_mesh...."
  elements            = read_ascii_mesh(root, dim)
  print "read_ascii_graph...."
  graph               = read_ascii_graph(root)
  print "write_binary_mesh...."
  write_binary_mesh  (elements, root, dim)
  print "write_binary_graph...."
  write_binary_graph (graph,    root, dim, len(elements))
  print "done"
  return



main()
