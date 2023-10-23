#!/usr/bin/env python
'''
little helper to visualize the result of all tests without a lot of scrolling

  Axel Gerstenberger
  agerste@sandia.gov
'''

import sys
import string

def readTestsFromInputFile(testlistfilename):
    'check for available test'
    testfile = open(testlistfilename, 'r', 1)
    test_names_given = []
    for line in testfile.readlines(): # remove leading white space, if any
        linetmp = string.lstrip(line) # ignore comments
        empty_line = len(linetmp) == 0
        if not empty_line:
            comment = linetmp[0] == '#'
            if not comment:
                if linetmp.find('.tst') != -1: # lines with .tst indicate tests
                    words = linetmp.split()
                    for w in words:
                        if w.find('.tst') != -1: # if tst is part of the word
                            rstfile = w 
                    root = rstfile[:-4]          # remove extension
                    if root[0:2] == "./":        # remove leading "./"
                        root = root[2:]
                    test_names_given.append(root)
    testfile.close()
    
    return test_names_given

def parseLogFileForTestResults(logfilename):
    'parse output - relies on dgm_diff screen output'
    logfile = open(logfilename, 'r', 1)
    test_names = []
    test_success = {} # using a dictionary has the problem if tests in
                      # subfolders have the same name as in the top folder
                      # might need fixing -> A. Gerstenberger
    for line in logfile.readlines():
        words = line.split()
        if line.find('DGM_diff:') == 0:
            rstfile = words[-1] # last word is the test name
            root = rstfile[:-4] # remove extension
            test_names.append(root)
        if line.find('No differences found.') == 0:
            test_success[test_names[-1]] = True
        if line.find('Found differences.') == 0:
            test_success[test_names[-1]] = False
    logfile.close()
    
    return test_names, test_success

def main(argv):
    'main entry'

    assert len(argv) == 2, 'wrong input parameters! Use: whatever.log testlist.sh'

    testlistfilename = argv[0]
    logfilename = argv[1]
    
    test_names_given = readTestsFromInputFile(testlistfilename)

    test_names, test_success = parseLogFileForTestResults(logfilename)
            
    # count good and bad results
    good = 0
    bad = 0
    for result in test_success.values():
        if result == True:
            good += 1
        elif result == False:
            bad += 1
            
    # check whether number of tests matches number of results
    if (good + bad != len(test_names_given)):
        print "good tests:", good
        print "bad tests: ", bad
        print "number of tests in testlist.sh: ", len(test_names_given)
        print "given tests in", testlistfilename, ": ", test_names_given
        print "actual tests logfile (", logfilename, "): ", test_names
        sys.exit("number of results does not match number of test cases")
    assert good + bad == len(test_names_given), "less results than tests"
    
    # print a summary and tell which test cases need fixing
    print
    print "------------------------------\\"
    print "| DGM Test Summary"
    print "|  number of tests: ", len(test_success)
    if good > 0:
        print "|  ->", good, "good tests:"
        for test in sorted(test_success.keys()):
            if test_success[test] == True:
                print "|       ", test
    if bad > 0:
        print "|  ->", bad, "failed tests:"    
        for test in sorted(test_success.keys()):
            if test_success[test] == False:
                print "|       ", test
    else:
        print "| All tests passed!"
    print "------------------------------/"
    print

if __name__ == "__main__":
    #for arg in sys.argv:
    #    print arg
    main(sys.argv[1:]) # arg[0] is the executable file name...-> not needed here
