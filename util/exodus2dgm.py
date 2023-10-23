#!/usr/bin/env python
"""
translate a (e.g. Cubit generated) exodusII file to dgm input

- assumes that 'exo2ien' and 'dgm_n2e.exe' are in your PATH

Author: A. Gerstenberger <agerste@sandia.gov>
"""

import os
import sys


def exodus2dgm(argv):
    'main routine'

    assert len(argv) == 1, 'wrong input parameters! Use: exodus2dgm.py casename'
    casename = argv[0]

    # produce intermediate format
    exofile = casename+'.exo'
    if not os.path.exists(exofile):
        sys.exit('\n *** exodus2dgm: Specified file "'+exofile+'" does not exists! ***\n\n')
    task = 'exo2ien '+exofile
    print "performing: ", task
    os.system(task)

    # produce final result
    task = 'dgm_n2e.exe -r '+casename+' TFE'
    print "performing: ", task
    os.system(task)

    os.system('rm *.asc')
    os.system('rm *.asc.dgraph')


if __name__ == "__main__":
    #for arg in sys.argv:
    #    print arg
    exodus2dgm(sys.argv[1:])
