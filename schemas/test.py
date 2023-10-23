#!/usr/bin/env python
import os
import json
from jsonschema import Draft4Validator, RefResolver
home = os.environ['HOME']
schema_fname = "schema.json"
json_fname = "test.json"
path = 'file://%s/dgm/schemas/' % (home)
print 'Validating \"%(json)s\" against \"%(schema)s\"' % \
      {"json":"json_fname","schema":"schema_fname"}
print 'Resolving JSON references from URI = %s' % path
file = open(schema_fname); 
schema = json.load(file)
file = open(json_fname); 
root = json.load(file)
base = RefResolver(path,{})
Draft4Validator(schema,resolver=base).validate(root)
