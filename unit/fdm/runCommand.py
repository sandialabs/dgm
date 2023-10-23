#! /usr/bin/env python

# Imports
import shlex
import subprocess
import sys

# RunCommand function
def runCommand(cmd, verbose=False, exitOnError=True, **kwargs):
    """
    Run a command, given as a single string argument.  If the verbose flag is
    set, print the command.  Run the command and wait for the process to end.
    The **kwargs argument can be used to pass any keyword arguments that are
    appropriate for the constructor for subprocess.Popen.  If the command
    returns with a non-zero code, print a warning message and exit if
    exitOnError is True, else return the subprocess return code.
    """

    if verbose: print "$", cmd
    args = shlex.split(cmd)
    p = subprocess.Popen(args, **kwargs)
    returncode = p.wait()
    if returncode:
        print "Command '%s' exited with code %s" % (args[0], str(returncode))
        if exitOnError: sys.exit(returncode)
    return returncode
