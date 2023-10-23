#! /usr/bin/env python

#TESTING active
#TESTING -n 2
#TESTING -k Trilinos

# System imports
from optparse import OptionParser
import os
import sys

try:
    import numpy
except ImportError:
    numpy = None

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
                      action="store", type="int", dest="numproc", default=2,
                      help="number of processors")
    (options, args) = parser.parse_args()

    # Clean option
    if options.clean:
        runCommand("../make_test -c", True)
        sys.exit(0)

    # Make the unit test
    runCommand("../make_test testField", True)

    # Run the unit test
    filename = "field.bin"
    runCommand(("mpiexec -np %d ../testField --dims=4,4,4"
                + " --bndryPad=2,2,2 --writeto=%s") % (options.numproc, filename),
               True)

    # Read the generated output and compare it to the reference values
    if numpy:
        print
        print "Reading and verifying the Field ...",
        ref = numpy.arange(512,dtype="d").reshape((8,8,8))
        f = numpy.fromfile(filename).reshape((4,4,4))
        assert((f[:,:,:] == ref[2:-2,2:-2,2:-2]).all())
        print "success!"

    # Run the unit test with communication padding
    filename = "field.bin"
    print
    print "-----------------------------------------------------------------"
    runCommand(("mpiexec -np %d ../testField --dims=4,4,4"
                + " --commPads=1,1,1 --bndryPad=2,2,2 --writeto=%s") %
               (options.numproc, filename), True)

    # Read the generated output and compare it to the reference values
    if numpy:
        print
        print "Reading and verifying the Field ...",
        ref = numpy.arange(512,dtype="d").reshape((8,8,8))
        f = numpy.fromfile(filename).reshape((4,4,4))
        assert((f[:,:,:] == ref[2:-2,2:-2,2:-2]).all())
        print "success!"

    # Print result
    print
    print "-----------------------------------------------------------------"
    print "Test", os.path.splitext(os.path.basename(__file__))[0], "PASSED"

#####

if __name__ == "__main__":
    main()
