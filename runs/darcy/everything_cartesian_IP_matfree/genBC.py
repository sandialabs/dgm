#!/usr/bin/env python
'Generate setup based on config file'

import sys
import subprocess

import dgm.BCtools

def main(argv):

    source = 'problem_template/'
        
    ne = [20]
    for ine in ne:
        
        nx = int(argv[0])
        ny = int(argv[1])
        
        print nx, ny
        
        root = 'darcy'
        
        
        print
        print 'Generating problemsize '+root
        
        print "\nexecute dgm_mesh.exe...\n"
        subprocess.call('dgm_mesh.exe -verb 2 -tecplot 1 -nsd 2 -Lx 8 -Ly 4 -nx '+str(nx)+' -ny '+str(ny)+' -r '+root, shell=True)

        xm, xp, ym, yp = dgm.BCtools.create_BC_2d(nx,ny)
        dgm.BCtools.write_BC_2d(root+'.bc', xm, xp, ym, yp)
        
if __name__ == "__main__":
    main(sys.argv[1:])