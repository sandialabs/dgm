#!/usr/bin/python

import sys, os

from shutil import copy

if __name__ == '__main__':

    # Number of command line arguments
    narg = len(sys.argv)
 
    source_specified  = ( narg >= 2 )
    install_specified = ( narg >= 3 )

    docstring = \
    """
    You must run this script with at least the ROL source path specified
    Where SOURCE_PATH=/PathToTrilinos/packages/rol/src

    Example Usage:

    $ python rol_install.py ${SOURCE_PATH} ${INSTALL_PATH} OPTS

    If INSTALL_PATH is not specified, the script will attempt to install to
 
    /usr/local/include 

    Optional arguments can also be provided through OPTS. Currently the 
    only supported option is shared_ptr to use the std::shared_ptr instead
    of Teuchos::RCP.

    """
    
    if not source_specified:
        print(docstring)
        os._exit(1)   

    src_path = sys.argv[1]
    install_path = '/usr/local/include'
    options = sys.argv[3:]

    if narg > 2:
        install_path = sys.argv[2]

    if not os.access(install_path, os.W_OK):
        print("You do not have write permissions to the designated install path {0}".format(install_path))
        os._exit(1)

    shared_ptr = 'shared_ptr' in options

    numfiles = 0

    for root, dirs, files in os.walk(src_path):
        path = root.split(os.sep)
        headers = [ os.path.join(root,file) for file in files if '.hpp' in file and file[0] != '.' ]

        if shared_ptr:
            headers = [ h for h in headers if 'rcp' not in h ]
        else:
            headers = [ h for h in headers if 'shared_ptr' not in h ]
    
        for h in headers:
            copy(h, install_path)
            print("Copying {0}".format(os.path.split(h)[-1]))
            numfiles += 1

    print("Copied {0} header files from {1} to {2}".format(numfiles,src_path,install_path))
    print("Installation complete.")
    
    
