#!/usr/bin/env python
import sys 
import argparse 
import os 
import re 
import json
import pprint
from jsonschema import Draft4Validator, RefResolver

home = os.environ['HOME']
schema_fname = "newSchema.json"
json_fname = "new.json"

parser = argparse.ArgumentParser(description='Validate JSON input against a JSON schema')
parser.add_argument("json", nargs='?', default=json_fname, \
help="file to validate")
parser.add_argument("schema",nargs='?', default=schema_fname, \
help="schema to validate against")
parser.add_argument('-v', '--verbose', action="store_true", \
default=False,help="print the JSON file");
args = parser.parse_args()

json_fname = args.json 
schema_fname = args.schema

path = 'file://%s/dgm/schemas/' % (home)
print 'Validating \"%(json)s\" against \"%(schema)s\"' % \
     {"json":json_fname,"schema":schema_fname}
print 'Resolving JSON references from URI = %s' % path

file = open(schema_fname); 
schema = json.load(file)

file = open(json_fname); 
text = file.read()
text = re.sub(r"([^/])//[^/].*",r"\1",text)            # C++ //  style comments
text = re.sub(r"/\*.*?\*/", "", text, flags=re.DOTALL) # C /* */ style comments
root = json.loads(text)

if args.verbose:
  print json.dumps(root,indent=2)

base = RefResolver(path,{})
Draft4Validator(schema,resolver=base).validate(root)
