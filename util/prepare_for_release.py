#! /usr/bin/env python

"""
This script is designed to remove lines from source code that have been marked
for removal.  This demarcation is achieved by using the DGM_REMOVE_FOR_RELEASE
macro within the code.  There are two forms that the script looks for: without
or with an #else clause.  The first form is as follows:

  #ifndef DGM_REMOVE_FOR_RELEASE
  ...
  #endif // DGM_REMOVE_FOR_RELEASE

Note that the #endif line uses a comment to denote that it closes the
corresponding #ifndef block.  The script expects a single space surrounding the
double-slash C++ comment.  The #ifndef line, the #endif line and everything in
between is removed by the script.

The second form is

  #ifndef DGM_REMOVE_FOR_RELEASE
  ...
  #else // DGM_REMOVE_FOR_RELEASE
  ...
  #endif // DGM_REMOVE_FOR_RELEASE

Again, the comments are required for properly matching statements in the
presence of nested preprocessor commands.  In this case, the #ifndef line, the
#else line, everything in between those two lines, and the #endif line is
removed by the script.

If you want the macro to use a prefix other than 'DGM', this can be specified
with the -p or --product command line options.

The script will loop over the filename(s) listed on the command line, create a
backup file with a "~" suffix, and then generate a new file with the original
filename and the specified lines removed.  If zero lines were removed, the
backup file is deleted.  If run in verbose mode, and the number of lines removed
is greater than zero, the script will print out the total number of lines removed
for each file.
"""

#
# Author: Bill Spotz, Sandia National Laboratories
#

# System imports
import optparse
import os

# Declare a new parser class in which we override the print_help() method.
# Ideally, we would just use the "epilog" keyword in the OptionParser
# constructor and set it to __doc__, but this script should be compatible with
# Python version 2.4, so we do it this way.
class MyParser(optparse.OptionParser):
    def print_help(self):
        optparse.OptionParser.print_help(self)
        print __doc__

# Main routine
def main():

    # Parse the command line
    parser = MyParser(usage="%prog [options] filename1 ...", version="%prog "
                      "version 1.1", description="Prepare source files for "
                      "release")
    parser.add_option("-q", "--quiet", action="store_false", dest="verbose",
                      help="run without output to screen")
    parser.add_option("-v", "--verbose", action="store_true", dest="verbose",
                      help="run with output to screen (default)")
    parser.add_option("-p", "--product", action="store", dest="product",
                      help="software product (default %default)")
    parser.set_defaults(verbose=True,
                        product="DGM")
    options, filenames = parser.parse_args()

    # Build some string constants
    macro      = options.product.upper() + "_REMOVE_FOR_RELEASE"
    ifndef_str = "#ifndef " + macro
    else_str   = "#else // " + macro
    endif_str  = "#endif // " + macro

    # Process each file
    for filename in filenames:

        # Initialize
        copy_line         = True
        looking_for_endif = False
        removed_lines     = 0

        # Create a backup and open the original filename for writing
        backup = filename + "~"
        os.rename(filename, backup)
        new_file = open(filename, "w")

        # Iterate over the lines of the backup file
        for line in open(backup, "r"):
            if copy_line:
                if line.count(ifndef_str):
                    copy_line = False
                    removed_lines += 1
                elif (looking_for_endif and
                      line.count(endif_str)):
                    looking_for_endif = False
                    removed_lines += 1
                else:
                    new_file.write(line)
            else:
                removed_lines += 1
                if line.count(else_str):
                    copy_line = True
                    looking_for_endif = True
                elif line.count(endif_str):
                    copy_line = True

        # Cleanup
        new_file.close()
        if (options.verbose and removed_lines):
            print "%s: %d lines removed" % (filename, removed_lines)
        if (looking_for_endif or not copy_line):
            print "  ***WARNING*** '" + ifndef_str + "' not closed with comment"
        if (removed_lines == 0):
            os.remove(backup)

if __name__ == "__main__":
    main()
