#!/bin/bash
dgm_clean ; ./mkmesh; 
dgm.exe ex9 ; 
dgm_post.exe -paraview -notec -start 0 -end 1000 -inc 10 ex9
