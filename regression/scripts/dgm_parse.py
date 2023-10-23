#!/usr/bin/env python

import sys, os, stat
import math

sys.stdout = open('dgm_email.out', 'a')
#
# Build phase
#
if "Error " in open(r"dgm_build.out").read():
    print "-- error detected in dgm build process --"
elif "error " in open(r"dgm_build.out").read():
    print "-- error detected in dgm build process --"
else:
    print "-- dgm built successfully --"
#
# Run phase
#
if "Failed" in open(r"dgm_runtest.out").read():
    print "-- failure detected in dgm tests.--"
elif "failed" in open(r"dgm_runtest.out").read():
    print "-- failure detected in dgm tests.--"
elif "Error " in open(r"dgm_runtest.out").read():
    print "-- error detected in dgm tests --"
elif "error " in open(r"dgm_runtest.out").read():
    print "-- error detected in dgm tests --"    
else:
    print "-- dgm tests passed--"
