#! /usr/bin/env python

#TESTING active
#TESTING -n 1
#TESTING -k Trilinos

# System imports
from optparse import OptionParser
import os
import sys

# Local import
sys.path.append("..")
from runCommand import runCommand

def main():

    # Parse the command line
    parser = OptionParser()
    parser.add_option("-c", "--clean",
                      action="store_true", dest="clean", default=False,
                      help="clean the unit test")
    parser.add_option("-n",
                      action="store", type="int", dest="numproc", default=1,
                      help="number of processors")
    (options, args) = parser.parse_args()

    # Clean option
    if options.clean:
        runCommand("../make_test -c", True)
        sys.exit(0)

    # Make the unit test
    runCommand("../make_test testField", True)

    # Run the unit test
    runCommand("mpiexec -np %d ../testField --test=1"
               % options.numproc, True)

#####

if __name__ == "__main__":
    main()
