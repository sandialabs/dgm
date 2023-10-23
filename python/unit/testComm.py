#! /usr/bin/env python

import os.path
import sys
dir = os.path.split(os.path.abspath(__file__))[0]
sys.path.append(os.path.abspath(os.path.join(dir, '..')))
import dgm
import pdgm

comm = dgm.SerialComm()
assert isinstance(comm, dgm.SerialComm)
assert isinstance(comm, dgm.Comm)

comm = pdgm.MpiComm(pdgm.MPI.COMM_WORLD)
assert isinstance(comm, pdgm.MpiComm)
assert isinstance(comm, pdgm.Comm)
