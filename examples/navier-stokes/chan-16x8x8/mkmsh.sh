#!/bin/bash
dgm_mesh.exe -nsd 3 -nx 16 -ny 8 -nz 8 \
-Lx 12.56637062 -Ly 4.188790205 -Lz 2.0 \
-tecplot 0 -ascii 0 -binary 1 -nograph -Cz 1.75 -r chan
