# -*- coding: utf-8 -*-
#!/usr/bin/env python

import sys

status = 0
f = open('output.log')
#with open('output.log') as f:
for l in f.readlines():
    
    if l.find('SIGABRT') != -1:
        status = 1
        print "error detected"
            
sys.exit(status)
