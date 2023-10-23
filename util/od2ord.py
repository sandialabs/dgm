#!/usr/bin/python

import sys
import json
import time
import getopt
import string
import struct
import optparse


def read_binary_orders(root) :
  try :
    b = open('%s.od' %(root), 'rb')
  except IOError  :
    sys.exit("Order file *.con not found")

  gne = struct.unpack('i',b.read(struct.calcsize('i')))[0]

  orders=[None]*gne
  p=[None]*gne
  q=[None]*gne
  for i in range(gne) :
    p[i] = struct.unpack('i',b.read(struct.calcsize('i')))[0]
  for i in range(gne) :
    q[i] = struct.unpack('i',b.read(struct.calcsize('i')))[0]
  for i in range(gne) :
    orders[i] = (p[i],q[i])
  b.close()
  return orders

def write_ascii_orders (ord,root) :
  f = open('%s.ord' %(root), 'w')

  print >>f, "** Order Data **"
  for i in range(len(ord)):
    print >>f, ' %12d %12d %12d' % (i,ord[i][0],ord[i][1])

def parse_command_line() :
  p = optparse.OptionParser()
  options,arguments = p.parse_args()
  if not len(arguments) : sys.exit ("ERROR: must specify base name: refine.py root")
  root = arguments[0]
  return root
  

#  ***************** BEGINNING OF MAIN *****************


def main() :
  root = parse_command_line() 
  orders = []
  print "read_binary_oders..."
  orders  = read_binary_orders(root)
  print "write_ascii_orders...."
  write_ascii_orders (orders, root)
  print "done"
  return



main()
