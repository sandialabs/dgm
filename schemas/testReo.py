#!/usr/bin/env python
import os
import json
from jsonschema import Draft4Validator, RefResolver
home = os.environ['HOME']
path = 'file://%s/dgm/schemas/' % (home)
print 'Validating testReo.json against Reo.json schema'
print 'Resolving JSON references from URI =',path
file = open("Reo.json"); schema = json.load(file)
file = open("testReo.json"); root = json.load(file)
base = RefResolver(path,{})
Draft4Validator(schema,resolver=base).validate(root)
