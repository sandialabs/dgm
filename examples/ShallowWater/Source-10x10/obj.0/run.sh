#!/bin/bash
mpiexec -n 8 pdgm.exe Source | tee Source.log
exit
