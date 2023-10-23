#!/usr/bin/python
import sys
import getopt
import string
import struct
import optparse
import datetime
from array import array

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

def generate_mesh(root,n,L,d) :
  N = n[0]*n[1]*n[2]
  C = 2**d;
  dx = float(L[0])/n[0]
  dy = float(L[1])/n[1]
  dz = float(L[2])/n[2]
  file = root+".grd" 
  b = open(file, 'wb')
  print >>b, "{"
  print >>b, " \"Date\" : \"",datetime.datetime.today(),"\","
  print >>b, " \"Name\" : \""+file+"\","
  print >>b, " \"Nel\" :",    N, ","
  print >>b, " \"Nsd\" :",    d, ","
  print >>b, " \"Types\" :",  "{", "  "
  print >>b, "    \"ByteOrder\"   : \"LittleEndian\","
  print >>b, "    \"GlobalSize\"  : \"int32\","
  print >>b, "    \"LocalSize\"   : \"int32\","
  print >>b, "    \"Scalar\"      : \"float64\" "
  print >>b, " ",  "},"
  print >>b, " \"Version\" : 1.0"
  print >>b, "}"
  b.write(struct.pack('i',  N))
  b.write(struct.pack('i',  d))
  b.write(struct.pack('i',C*N))
  if (d==2) :
    array('i',[1 for i in range(N)]).tofile(b)
  else :      
    array('i',[3 for i in range(N)]).tofile(b)

  array('i',[C*i for i in range(N)]).tofile(b)

  print "Output X coordinates..."
  for k in range(n[2]) : 
    for j in range(n[1]) : 
      for i in range(n[0]) : 
        x0 =  i * dx 
        x1 = x0 + dx 
        array('d',[x0,  x1,  x1,  x0,  x0,  x1,  x1,  x0]).tofile(b)
  print "Output Y coordinates..."
  for i in range(n[0]) : 
    for j in range(n[1]) : 
      y0 =  j * dy 
      y1 = y0 + dy 
      for k in range(n[2]) : 
        array('d',[y0,  y0,  y1,  y1,  y0,  y0,  y1,  y1]).tofile(b)
  if (3==d) :
    print "Output Z coordinates..."
    for k in range(n[2]) : 
      z0 =  k * dz 
      z1 = z0 + dz 
      for j in range(n[1]) : 
        for i in range(n[0]) : 
          array('d',[z0,  z0,  z0,  z0,  z1,  z1,  z1,  z1]).tofile(b)
  b.close()
  return 

def write_binary_hex_graph_old(root,n,d) :
  file = root+".cn" 
  b = open(file, 'wb')

  N = n[0]*n[1]*n[2]
  print >>b, "{"
  print >>b, " \"Date\" : \"",datetime.datetime.today(),"\","
  print >>b, " \"Name\" : \"",file,"\","
  print >>b, " \"Nel\" :   ",    N, ","
  print >>b, " \"Nsd\" :   ",    d, ","
  print >>b, " \"Types\" :",  "{", "   "
  print >>b, "    \"ByteOrder\"  : \"LittleEndian\","
  print >>b, "    \"GlobalSize\" : \"int32\","
  print >>b, "    \"LocalSize\"  : \"int32\","
  print >>b, "    \"Scalar\"     : \"float64\" "
  print >>b, " ",  "},"
  print >>b, " \"Version\" : 1.0"
  print >>b, "}"

  print "Writing displacements...."
  array('i',[6*i for i in range(N)]).tofile(b)
  print "Writing lengths...."
  array('i',[6   for i in range(N)]).tofile(b)

  e   = 0
  gid = 0
  gids = (6*N)*[None]
  I = 3*[None]
  J = 3*[None]
  K = 3*[None]
  S = 6*[None]
  T =   [5,3,4,1,2,0]
  graph = array('i')
  print "Generating graph...."
  for i in range(n[0]) :
    I[0] = i*n[1]*n[2]
    I[1] = ((i+1)     %n[0])*n[1]*n[2]
    I[2] = ((i-1+n[0])%n[0])*n[1]*n[2]
    for j in range(n[1]) :
      J[0] = j*n[2]
      J[1] = ((j+1)     %n[1])*n[2]
      J[2] = ((j-1+n[1])%n[1])*n[2]
      for k in range(n[2]) :

        if (not e%1000) : sys.stdout.write("\r Elem: "+str(e))
        e += 1

        K[0] = k
        K[1] = (k+1)     %n[2]
        K[2] = (k-1+n[2])%n[2]

        me     = K[0] + J[0] + I[0]          
        S[0]   = K[0] + J[0] + I[2]                        
        S[1]   = K[0] + J[2] + I[0]          
        S[2]   = K[1] + J[0] + I[0]          
        S[3]   = K[0] + J[1] + I[0]          
        S[4]   = K[2] + J[0] + I[0]          
        S[5]   = K[0] + J[0] + I[1]                        

        for l in range(6) :
          if (S[l] < me) : gids[6*me+l] = gids[6*S[l]+T[l]]
          else             : 
            gids[6*me+l] = gid
            gid += 1
          array('i', [me, l, S[l]  , T[l], gids[6*me+l]] ).tofile(b)

  print
  b.close()
  return 

def write_binary_hex_graph(root,n,d) :
  file = root+".cn" 
  b = open(file, 'wb')

  N = n[0]*n[1]*n[2]
  print >>b, "{"
  print >>b, " \"Date\" : \"",datetime.datetime.today(),"\","
  print >>b, " \"Name\" : \"",file,"\","
  print >>b, " \"Nel\" :   ",    N, ","
  print >>b, " \"Nsd\" :   ",    d, ","
  print >>b, " \"Types\" :",  "{", "   "
  print >>b, "    \"ByteOrder\"  : \"LittleEndian\","
  print >>b, "    \"GlobalSize\" : \"int32\","
  print >>b, "    \"LocalSize\"  : \"int32\","
  print >>b, "    \"Scalar\"     : \"float64\" "
  print >>b, " ",  "},"
  print >>b, " \"Version\" : 1.0"
  print >>b, "}"

  print "Writing displacements...."
  array('i',[6*i for i in range(N)]).tofile(b)
  print "Writing lengths...."
  array('i',[6   for i in range(N)]).tofile(b)

  e   = 0
  I = 3*[None]
  J = 3*[None]
  K = 3*[None]
  S = 6*[None]
  T =   [5,3,4,1,2,0]
  graph = array('i')
  print "Generating graph...."
  for i in range(n[0]) :
    I[0] = i*n[1]*n[2]
    I[1] = ((i+1)     %n[0])*n[1]*n[2]
    I[2] = ((i-1+n[0])%n[0])*n[1]*n[2]
    for j in range(n[1]) :
      J[0] = j*n[2]
      J[1] = ((j+1)     %n[1])*n[2]
      J[2] = ((j-1+n[1])%n[1])*n[2]
      for k in range(n[2]) :

        if (not e%1000) : sys.stdout.write("\r Elem: "+str(e))
        e += 1

        K[0] = k
        K[1] = (k+1)     %n[2]
        K[2] = (k-1+n[2])%n[2]

        me     = K[0] + J[0] + I[0]          
        S[0]   = K[0] + J[0] + I[2]                        
        S[1]   = K[0] + J[2] + I[0]          
        S[2]   = K[1] + J[0] + I[0]          
        S[3]   = K[0] + J[1] + I[0]          
        S[4]   = K[2] + J[0] + I[0]          
        S[5]   = K[0] + J[0] + I[1]                        

        for l in range(0,3) : array('i', [me, l, S[l], T[l], 3*me  +  l] ).tofile(b)
        for l in range(3,6) : array('i', [me, l, S[l], T[l], 3*S[l]+T[l]]).tofile(b)

  print
  b.close()
  return 

def print_dat(f,x) :
  if (8==len(x)) :
    print >>f, \
    " %13.9e %13.9e %13.9e %13.9e %13.9e %13.9e %13.9e %13.9e"  \
    % (x[0],x[1],x[3],x[2],x[4],x[5],x[7],x[6])
  else :
    print >>f, " %13.9e  %13.9e  %13.9e  %13.9e" % (x[0], x[1], x[3], x[2])

def write_tecplot(elements, root, d) :
  file = root+".dat" 
  f = open(file, 'w')
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

def parse_command_line() :
  p = optparse.OptionParser()
  p.add_option('--root',   '-r',   action='store', type='string', default='new')
  p.add_option('--nx', '--nx',     action='store', type='int',  default='10')
  p.add_option('--ny', '--ny',     action='store', type='int',  default='10')
  p.add_option('--nz', '--nz',     action='store', type='int',  default='10')
  p.add_option('--Lx', '--Lx',     action='store', type='int',  default='1')
  p.add_option('--Ly', '--Ly',     action='store', type='int',  default='1')
  p.add_option('--Lz', '--Lz',     action='store', type='int',  default='1')
  p.add_option('--nsd', '--nsd',   action='store', type='int',  default='3')
  p.add_option('--old', '--old',   action='store', type='int',  default='0')
  options,arguments = p.parse_args()
  root       = options.root
  n          = 3*[None]
  L          = 3*[None]
  n[0]       = options.nx
  n[1]       = options.ny
  n[2]       = options.nz
  L[0]       = options.Lx
  L[1]       = options.Ly
  L[2]       = options.Lz
  dim        = options.nsd
  old_conn   = options.old
  if (dim<3) : n[2] = 1
  if (dim<2) : n[1] = 1
  return root,n,L,dim,old_conn

#  ***************** BEGINNING OF MAIN *****************

def main() :
  root,N,L,dim,old_connect = parse_command_line() 
  print "Write binary mesh...."
  generate_mesh(root,N,L,dim)
  print "Write binary graph...."
  if (3==dim) : 
    if (old_connect) : write_binary_hex_graph_old (root,N,dim)
    else             : write_binary_hex_graph     (root,N,dim)
  return

main()
