
These scripts can be used to perform checkouts, build and tests each night.  
Most of these files are self explanatory.

The tests are executed using a command like:

  env DGM_DIST=$HOME/dgm ./dgm_master.sh

There seems to be a little bit of a chicken and egg issue here in that
you need to specifiy a current DGM_DIST so that the scripts can be 
executed.  There is no real bootstrap mechanism right now.

BvBW 4/09
SSC  12/10
-------------------------------------------------------------------------------
crontab.txt         - sample crontab file
dgm_master.sh       - master script that controls subscsripts
dgm_setup.in        - environment variables - likely the only script 
                      that needs to be changed
dgm_build.sh        - build dgm script
dgm_testlist.sh     - list of all tests to be run
dgm_runtest.sh      - run all the test that are listed in the 
                      testlist.sh script
dgm_parse.py        - python script to parses the output from dgm_out directory
dgm_email.sh        - script to send email and reports on the the 
                      build and runtests
dakota_build.sh     - dakota build script
trilinos_build.sh   - trilinos build script
