README.txt

software needed:
  BoxTreeMesh
  Cubit 14.1
  exodus2dgm.py
  <MeshLab - optional>

--
To create a dgm mesh:

From a directory that has surface files defined in it, 

run BoxtreeMesh c++ program 
  this creates inclusion.con inclusion.msh hex meshes, 
  including warping hexes to the acoustic surface, if any.
  This creates cubit_inclusion_mesh.py and some temporary facet files as input
  to cubit.

run Cubit 14.1, copy and paste the python script into the "script" tab window
  this creates a tet mesh for each connected component between inclusion and
  elastic surfaces, volume?.exo 

use dgm/util/exodus2dgm.py to convert volume?.exo to dgm mesh files
  combine the dgm hex and tet meshes into a single mesh
  assign materials to each of the volumes, and the hexes above and below 
  the acoustic surface. <James Overfelt is developing a combination script.>
procede with dgm setup as normal, for setting source and observer

-
Input surface files:
  topInclusion1.xyz, botInclusion1.xyz, topInclusion2.xyz, etc.
  acousticsurface.xyz

- 
Intermediate files:
  cubit_inclusion_mesh.py
  *.facet

-
Output mesh files:
  inclusion.con and inclusion.msh  defining hex meshes
  volume?.exo  defining tet meshes, one file for each region between inclusion-
  elastic interface surfaces

To visualize the full mesh in Cubit, at the command line do
    import mesh geom "volume?.exo"
    import facets "hexes.facet")


The following are useful for defining boundary conditions and material 
properties and interfaces:

zone*txt
Tets and hexes in each material region, e.g. acoustic, elastic, and inclusion.
Specifically:
zone_elastic_inclusion_tet_exo.txt 
Lists the material type for tet Volume1.exo, Volume2.exo, etc.
zone_{acoustic|elastic|inclusion}_hex.txt
Lists the ids of the hexes in the inclusion.msh file of each type.

inclusion_surface_triangulation_?.facet  
Triangles of the contiguous elastic-inclusion surface interface.

box_tet_faces_layer_0.exo        
Quads split into two triangles, at hex-tet interface.

----  CUBIT

The Cubit script window is hidden by default. 
To turn it on
<Unix? PC?>  open the Tools-Options dialog and check the "Show Script Tab under
 Layout/Cubit Layout.
<Mac> Cubit->preferences->Layout->Cubit Layout, then check the "show script tab
 button"

Cubit python script interface help:
https://cubit.sandia.gov/public/14.1/help_manual/WebHelp/cubithelp.htm
Click "show" box to open the left sidebar with table of contents
Expand "Appendix" then "Python"

Cubit->view->command Line

The cubit imprint commands take a long time, appears to be O(n^2) or worse. 
Be patient where there are a lot of boxes

--
To visualize the mesh in cubit:
import mesh "volume1.exo" no_geom
<repeat for volume2.exo, etc.>
import facet "hexes.facet" no_geom


Some of the example python scripts have been hand edited. In a few cases this
was done to do some manual bookkeeping; see surface limitation below.
For the "full" model, it is due to memory limitations: using the surface
triangulations of the full data runs out of memory, so each one was remeshed
to reduce its size, outside cubit, inside meshlab.

----  BOXTREEMESH

BoxTreeMesh is a c++ program, developed on Mac OS/X using the Xcode IDE.
the "code" directory contains the .h and .cpp files
the "BoxTreeMesh" directory contains the project file BoxTreeMesh.xcodeproj 

-
The user interface is underdeveloped. 

Internal parameters include the z-depth of domain, which part of the domain gets
exported as a mesh, scaling of the domain, file names of inclusion and
oceanbottom surfaces; the size of the mesh based on proximity to surfaces and
absolute spatial coordinates.

These are controlled by the following variables within the 
Example::inclusion_manifold() method in the example.cpp file

exactly_two_triangles (Boolean)
true means that every hex-tet interface quad has to be split into exactly two triangles, which precludes size transitions.

toy (Boolean) 
This is a flag that switches between small models, roughly 200 x 200 x 200
units, and large models, roughly 20,000 x 20,000 x 20,000 units.

do_inclusion, do_acousticsurface, (Boolean)
If true, then read and process inclusion surfaces, acoustic surfaces.
Auto-switches to false if files are not present in the current directory.

min_dxy, max_z (double)
Boxes with dimensions larger than these values will be refined if they
intersect the acoustic surface

inclusion_min_dxy, inclusion_max_z (double)
Boxes with dimensions larger than these values will be refined if they
intersect an inclusion surface

max_box (double)
Large boxes are subdivided so that the ratio of the largest box to the smallest
box side length is at most max_box

The length of the edges in the triangulation of the surface in the hex-tet mesh. 

Domain:
z-extent is determined by the third parameter passed to bwt.set_domain_size().
xy-extent is determined from the xy extent of the surface files.

bt.root->create_children( Index(1,1,2) )
This call divides the box equal to the domain extent into x,y,z (1,1,2)
immediate children. This controls the aspect ratio of the boxes.
The number of top level children should be selected based on the domain extent.

To control the size of the hexes (boxes), one must change the source code to use
a different "Refiner" sizing functions, and perhaps balancer. These have many
parameters and can be fully customized as any C++ function.
For the acoustic surface, use
    bwt.set_refiner_near_surface(refiner);
    bwt.refine_near_surface();
For the inclusion surfaces, use


tri_edge_length (double)
To control the triangle and tet sizes, one must change either the source code,
or the "cubit.cmd('curve all size 10')" line in the cubit_inclusion_mesh.py
script. By default, the triangle edge lengths are about the same as the length
of the box sides bounding the region being tet-meshed. The tets are uniform.

----
Surface Limitations:

Waterbottom surface must span the entire xy domain, and intersect the sides of
the domain at some depth strictly between the maximum and minimum (0) depth of
the domain. The hexes must be small enough that there is at least one hex above
the acousticbottom.

Inclusionsurfaces must either enclose a shell inside the domain, not
intersecting the boundary, or be an xy-layer spanning the xy-extent of the
domain as with a acousticbottom surface.

Shells are not nested.

These limitations are not fundamental to the boxtreemesh software, but the cubit
script to create the tet meshes depends on this structure to keep track of which
facets make up a complete boundary of a 3d region to be tet meshed.

--

Contact Scott Mitchell samitch@sandia.gov for help.

