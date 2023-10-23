#!/bin/bash
dgm_clean ; ./mkmesh; 
dgm.exe ex9 ; 
dgm_post.exe -paraview -notec -start 0 -end 1800 -inc 50 ex9
