#!/usr/bin/env python

try:
  import simplejson as json
except:
  import json

import validictory as val
import argparse
import re

parser = argparse.ArgumentParser(description='Validate a DGM input file')
parser.add_argument("filename")
args = parser.parse_args()

filename = args.filename

#data = json.load(open(filename))
data = open(filename).read()
data = re.sub("//.*?\n","\n" ,data) 
data = json.loads(data)

schema = json.load(open('dgm.v4.json'))

try:
  val.validate(data,schema,required_by_default=False)
  print 'Json file',filename,'is valid.'
except ValueError, error:
  print 'Error in Json file',filename,':\n', error
