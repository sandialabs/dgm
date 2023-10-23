#!/usr/bin/python

import sys
import json
import time
import getopt
import string
import struct
import optparse


def read_ascii_orders(root) :
  try :
    f = open('%s.ord' %(root), 'r')
  except IOError  :
    sys.exit("Order file *.con not found")
  lines = f.readlines()
  f.close()
  orders = []
  for i in range(1,len(lines)):
    words = lines[i].split()
    c = (int(words[0]), int(words[1]), int(words[2]))
    orders.append(c)
  return orders

def write_binary_orders (ord,root) :
  b = open('%s.od' %(root), 'wb')
  b.write(struct.pack('i',len(ord)))
  ord.sort()
  for i in range(len(ord)) :
    b.write(struct.pack('i',ord[i][1]))
  for i in range(len(ord)) :
    b.write(struct.pack('i',ord[i][2]))
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
  orders = []
  print "read_ascii_oders..."
  orders  = read_ascii_orders(root)
  print "write_binary_orders...."
  write_binary_orders (orders, root)
  print "done"
  return



main()
