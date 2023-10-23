# python script file to run inside cubit 14.1 or 14.0
# dgm mesh, to create tet mesh of domain interior
# cubit.cmd('label surface name')
cubit.cmd('set developer commands on')
# create smooth side faces of the domain, without unnecessary box imprints.

# making conformal triangle mesh for mesh-based geometry. Side 1
cubit.cmd('reset')
cubit.cmd('import facets "box_tet_faces_side1.facet"')
cubit.cmd('import facets "box_imprint.facet"')
dummy_imprint_id = cubit.get_last_id("body")
cubit.cmd('group "dummy_imprint" equals body ' + str(dummy_imprint_id) )
cubit.cmd('imprint all')
cubit.cmd('delete body in dummy_imprint')
cubit.cmd('merge vertex all')
cubit.cmd('merge curve all')
cubit.cmd('surface all scheme trimesh')
cubit.cmd('curve all interval 1')
cubit.cmd('mesh surface all')
cubit.cmd('block 1 surface all')
cubit.cmd('export mesh "box_tet_faces_side1.exo" dimension 3 block 1 overwrite')

# making conformal triangle mesh for mesh-based geometry. Side 2
cubit.cmd('reset')
cubit.cmd('import facets "box_tet_faces_side2.facet"')
cubit.cmd('import facets "box_imprint.facet"')
dummy_imprint_id = cubit.get_last_id("body")
cubit.cmd('group "dummy_imprint" equals body ' + str(dummy_imprint_id) )
cubit.cmd('imprint all')
cubit.cmd('delete body in dummy_imprint')
cubit.cmd('merge vertex all')
cubit.cmd('merge curve all')
cubit.cmd('surface all scheme trimesh')
cubit.cmd('curve all interval 1')
cubit.cmd('mesh surface all')
cubit.cmd('block 1 surface all')
cubit.cmd('export mesh "box_tet_faces_side2.exo" dimension 3 block 1 overwrite')

# making conformal triangle mesh for mesh-based geometry. Side 3
cubit.cmd('reset')
cubit.cmd('import facets "box_tet_faces_side3.facet"')
cubit.cmd('import facets "box_imprint.facet"')
dummy_imprint_id = cubit.get_last_id("body")
cubit.cmd('group "dummy_imprint" equals body ' + str(dummy_imprint_id) )
cubit.cmd('imprint all')
cubit.cmd('delete body in dummy_imprint')
cubit.cmd('merge vertex all')
cubit.cmd('merge curve all')
cubit.cmd('surface all scheme trimesh')
cubit.cmd('curve all interval 1')
cubit.cmd('mesh surface all')
cubit.cmd('block 1 surface all')
cubit.cmd('export mesh "box_tet_faces_side3.exo" dimension 3 block 1 overwrite')

# making conformal triangle mesh for mesh-based geometry. Side 4
cubit.cmd('reset')
cubit.cmd('import facets "box_tet_faces_side4.facet"')
cubit.cmd('import facets "box_imprint.facet"')
dummy_imprint_id = cubit.get_last_id("body")
cubit.cmd('group "dummy_imprint" equals body ' + str(dummy_imprint_id) )
cubit.cmd('imprint all')
cubit.cmd('delete body in dummy_imprint')
cubit.cmd('merge vertex all')
cubit.cmd('merge curve all')
cubit.cmd('surface all scheme trimesh')
cubit.cmd('curve all interval 1')
cubit.cmd('mesh surface all')
cubit.cmd('block 1 surface all')
cubit.cmd('export mesh "box_tet_faces_side4.exo" dimension 3 block 1 overwrite')

cubit.cmd('reset')

# Preparing faces of the non-hex boxes that bound the triangulation void and domain.
# Exactly_two_triangles == TRUE
# No need for box imprints, interface faces are already conformal.

# Preparing box faces before layer 0
cubit.cmd('reset')
cubit.cmd('import facets "box_tet_faces_0.facet"')
# Splitting interface quads into exactly two triangles
cubit.cmd('merge vertex all')
cubit.cmd('merge curve all')
cubit.cmd('surface all scheme trimesh')
cubit.cmd('curve all interval 1')
cubit.cmd('mesh surface all')
cubit.cmd('block 1 surface all')
cubit.cmd('export mesh "box_tet_faces_layer_0.exo" dimension 3 block 1 overwrite')

# Preparing box faces before layer 1
cubit.cmd('reset')
cubit.cmd('import facets "box_tet_faces_1.facet"')
# Splitting interface quads into exactly two triangles
cubit.cmd('merge vertex all')
cubit.cmd('merge curve all')
cubit.cmd('surface all scheme trimesh')
cubit.cmd('curve all interval 1')
cubit.cmd('mesh surface all')
cubit.cmd('block 1 surface all')
cubit.cmd('export mesh "box_tet_faces_layer_1.exo" dimension 3 block 1 overwrite')

# Preparing box faces before layer 3
cubit.cmd('reset')
cubit.cmd('import facets "box_tet_faces_3.facet"')
# Splitting interface quads into exactly two triangles
cubit.cmd('merge vertex all')
cubit.cmd('merge curve all')
cubit.cmd('surface all scheme trimesh')
cubit.cmd('curve all interval 1')
cubit.cmd('mesh surface all')
cubit.cmd('block 1 surface all')
cubit.cmd('export mesh "box_tet_faces_layer_3.exo" dimension 3 block 1 overwrite')

cubit.cmd('reset')

# reading smooth side faces of the domain.
cubit.cmd('group "g_domain_bdy_f0" equals surface with name "domain_bdy_f0"')
old_surf_id = cubit.get_last_id("surface")
cubit.cmd('import mesh geometry "box_tet_faces_side1.exo" feature_angle 135  merge')
new_surf_id = cubit.get_last_id("surface")
cubit.cmd('surface ' + str(old_surf_id+1) + ' to ' + str(new_surf_id) + ' name "domain_bdy_f1"')
cubit.cmd('group "g_domain_bdy_f1" equals surface with name "domain_bdy_f1"')
old_surf_id = cubit.get_last_id("surface")
cubit.cmd('import mesh geometry "box_tet_faces_side2.exo" feature_angle 135  merge')
new_surf_id = cubit.get_last_id("surface")
cubit.cmd('surface ' + str(old_surf_id+1) + ' to ' + str(new_surf_id) + ' name "domain_bdy_f2"')
cubit.cmd('group "g_domain_bdy_f2" equals surface with name "domain_bdy_f2"')
old_surf_id = cubit.get_last_id("surface")
cubit.cmd('import mesh geometry "box_tet_faces_side3.exo" feature_angle 135  merge')
new_surf_id = cubit.get_last_id("surface")
cubit.cmd('surface ' + str(old_surf_id+1) + ' to ' + str(new_surf_id) + ' name "domain_bdy_f3"')
cubit.cmd('group "g_domain_bdy_f3" equals surface with name "domain_bdy_f3"')
old_surf_id = cubit.get_last_id("surface")
cubit.cmd('import mesh geometry "box_tet_faces_side4.exo" feature_angle 135  merge')
new_surf_id = cubit.get_last_id("surface")
cubit.cmd('surface ' + str(old_surf_id+1) + ' to ' + str(new_surf_id) + ' name "domain_bdy_f4"')
cubit.cmd('group "g_domain_bdy_f4" equals surface with name "domain_bdy_f4"')
cubit.cmd('group "g_domain_bdy_f5" equals surface with name "domain_bdy_f5"')
# importing triangulations as surfaces in ascending z-coordinate order
t_id_begin = cubit.get_last_id("surface") + 1
cubit.cmd('import facets "inclusion_surface_triangulation_0.facet" feature_angle 135  merge')
t_id_end = cubit.get_last_id("surface")
cubit.cmd('surface ' + str(t_id_begin) + ' to ' + str(t_id_end) + ' name "inclusion_surface_triangulation_0"')
cubit.cmd('group "g_inclusion_surface_triangulation_0" equals surface with name "inclusion_surface_triangulation_0"')

t_id_begin = cubit.get_last_id("surface") + 1
cubit.cmd('import facets "inclusion_surface_triangulation_1.facet" feature_angle 135  merge')
t_id_end = cubit.get_last_id("surface")
cubit.cmd('surface ' + str(t_id_begin) + ' to ' + str(t_id_end) + ' name "inclusion_surface_triangulation_1"')
cubit.cmd('group "g_inclusion_surface_triangulation_1" equals surface with name "inclusion_surface_triangulation_1"')

t_id_begin = cubit.get_last_id("surface") + 1
cubit.cmd('import facets "inclusion_surface_triangulation_2.facet" feature_angle 135  merge')
t_id_end = cubit.get_last_id("surface")
cubit.cmd('surface ' + str(t_id_begin) + ' to ' + str(t_id_end) + ' name "inclusion_surface_triangulation_2"')
cubit.cmd('group "g_inclusion_surface_triangulation_2" equals surface with name "inclusion_surface_triangulation_2"')

cubit.cmd('# imprinting and merging the faceted geoemtry, for a contiguous mesh')

# importing hex-tet interface, the faces of the non-hex boxes that bound the triangulation void and domain.
old_surf_id = cubit.get_last_id("surface")
cubit.cmd('import mesh geom "box_tet_faces_layer_0.exo" feature_angle 0  merge')
new_surf_id = cubit.get_last_id("surface")
cubit.cmd('surface ' + str(old_surf_id+1) + ' to ' + str(new_surf_id) + ' name "hex_tet_faces_0"')
cubit.cmd('group "g_hex_tet_faces_0" equals surface with name "hex_tet_faces_0"')
old_surf_id = cubit.get_last_id("surface")
cubit.cmd('import mesh geom "box_tet_faces_layer_1.exo" feature_angle 0  merge')
new_surf_id = cubit.get_last_id("surface")
cubit.cmd('surface ' + str(old_surf_id+1) + ' to ' + str(new_surf_id) + ' name "hex_tet_faces_1"')
cubit.cmd('group "g_hex_tet_faces_1" equals surface with name "hex_tet_faces_1"')
cubit.cmd('group "g_hex_tet_faces_2" equals surface with name "hex_tet_faces_2"')
old_surf_id = cubit.get_last_id("surface")
cubit.cmd('import mesh geom "box_tet_faces_layer_3.exo" feature_angle 0  merge')
new_surf_id = cubit.get_last_id("surface")
cubit.cmd('surface ' + str(old_surf_id+1) + ' to ' + str(new_surf_id) + ' name "hex_tet_faces_3"')
cubit.cmd('group "g_hex_tet_faces_3" equals surface with name "hex_tet_faces_3"')

cubit.cmd('imprint all')

# imprint all just deleted all the mesh on the hex-tet box faces, and lost all their names and groups!
# Read the mesh in again and restore names and groups.
cubit.cmd('group "pre_meshed" equals surface meshed')
cubit.cmd('import mesh "box_tet_faces_layer_0.exo" ')
cubit.cmd('group "post_meshed" equals surface meshed')
cubit.cmd('group "just_meshed" subtract pre_meshed from post_meshed')
cubit.cmd('surface in just_meshed name "hex_tet_faces_0"')
cubit.cmd('group "g_hex_tet_faces_0" equals surface with name "hex_tet_faces_0"')
cubit.cmd('group "pre_meshed" equals surface meshed')
cubit.cmd('import mesh "box_tet_faces_layer_1.exo" ')
cubit.cmd('group "post_meshed" equals surface meshed')
cubit.cmd('group "just_meshed" subtract pre_meshed from post_meshed')
cubit.cmd('surface in just_meshed name "hex_tet_faces_1"')
cubit.cmd('group "g_hex_tet_faces_1" equals surface with name "hex_tet_faces_1"')
cubit.cmd('group "g_hex_tet_faces_2" equals surface with name "hex_tet_faces_2"')
cubit.cmd('group "pre_meshed" equals surface meshed')
cubit.cmd('import mesh "box_tet_faces_layer_3.exo" ')
cubit.cmd('group "post_meshed" equals surface meshed')
cubit.cmd('group "just_meshed" subtract pre_meshed from post_meshed')
cubit.cmd('surface in just_meshed name "hex_tet_faces_3"')
cubit.cmd('group "g_hex_tet_faces_3" equals surface with name "hex_tet_faces_3"')

#we just split the domain side faces by the boundaries of the triangulated surfaces
# unfortunately, facet-based imprinting does not propagate names!
# find domain side surfaces again and assign names and group them in the script
xmin = 0
ymin = 0
xmax = 100
ymax = 105
zmin = 0
zmax = 200
last_s = cubit.get_last_id("surface")
for s in range(1,last_s+1):
  n=cubit.get_entity_name("surface",s)
  # if surface exists
  if n!="":
    ct = cubit.get_surface_centroid(s)
    if abs(ct[0] - xmin) < xmax*1e-4:
      cubit.cmd('surface ' + str(s) + ' name "domain_bdy_f4"')
    elif abs(ct[0] - xmax) < xmax*1e-4:
      cubit.cmd('surface ' + str(s) + ' name "domain_bdy_f2"')
    elif abs(ct[1] - ymin) < ymax*1e-4:
      cubit.cmd('surface ' + str(s) + ' name "domain_bdy_f1"')
    elif abs(ct[1] - ymax) < ymax*1e-4:
      cubit.cmd('surface ' + str(s) + ' name "domain_bdy_f3"')

    elif abs(ct[2] - zmin) < zmax*1e-4:
      cubit.cmd('surface ' + str(s) + ' name "domain_bdy_f0"')
    elif abs(ct[2] - zmax) < zmax*1e-4:
      cubit.cmd('surface ' + str(s) + ' name "domain_bdy_f5"')

cubit.cmd('group "g_domain_bdy_f0" equals surface with name "domain_bdy_f0"')
g_id0 = cubit.get_id_from_name("g_domain_bdy_f0")
cubit.cmd('group "g_domain_bdy_f1" equals surface with name "domain_bdy_f1"')
g_id1 = cubit.get_id_from_name("g_domain_bdy_f1")
cubit.cmd('group "g_domain_bdy_f2" equals surface with name "domain_bdy_f2"')
g_id2 = cubit.get_id_from_name("g_domain_bdy_f2")
cubit.cmd('group "g_domain_bdy_f3" equals surface with name "domain_bdy_f3"')
g_id3 = cubit.get_id_from_name("g_domain_bdy_f3")
cubit.cmd('group "g_domain_bdy_f4" equals surface with name "domain_bdy_f4"')
g_id4 = cubit.get_id_from_name("g_domain_bdy_f4")
cubit.cmd('group "g_domain_bdy_f5" equals surface with name "domain_bdy_f5"')
g_id5 = cubit.get_id_from_name("g_domain_bdy_f5")

# gather vs<i> groups of surfaces, the domain-boundary surfaces bounding volume <i>
# assume each surface intersects the domain boundary in a single topological circle, spanning the domain and splitting it into an above and a below, or not at all
num_layers = len(cubit.get_group_surfaces( g_id1 ))
num_layers_expected = 2
# assume all the other side face groups have the same number of layers after imprinting
# closed shells should have no side layers assigned to them
# beware hexed boxes splitting sides into different ranges
import numpy #for argsort

# get domain boundary surfaces in sorted order by z-coorindate
s1 = cubit.get_group_surfaces( g_id1 )
zc=list()
for i in s1:
  ct = cubit.get_surface_centroid(i)
  zc.append(ct[2])
sz1 = numpy.argsort(zc)
# put surfaces into cubit groups by layer, vs0, vs1, vs2...
for i in range(num_layers):
  cubit.cmd('group "vs' + str(i+1) + '" add surface ' + str(s1[sz1[i]]) ) 
s2 = cubit.get_group_surfaces( g_id2 )
zc=list()
for i in s2:
  ct = cubit.get_surface_centroid(i)
  zc.append(ct[2])
sz2 = numpy.argsort(zc)
# put surfaces into cubit groups by layer, vs0, vs1, vs2...
for i in range(num_layers):
  cubit.cmd('group "vs' + str(i+1) + '" add surface ' + str(s2[sz2[i]]) ) 
s3 = cubit.get_group_surfaces( g_id3 )
zc=list()
for i in s3:
  ct = cubit.get_surface_centroid(i)
  zc.append(ct[2])
sz3 = numpy.argsort(zc)
# put surfaces into cubit groups by layer, vs0, vs1, vs2...
for i in range(num_layers):
  cubit.cmd('group "vs' + str(i+1) + '" add surface ' + str(s3[sz3[i]]) ) 
s4 = cubit.get_group_surfaces( g_id4 )
zc=list()
for i in s4:
  ct = cubit.get_surface_centroid(i)
  zc.append(ct[2])
sz4 = numpy.argsort(zc)
# put surfaces into cubit groups by layer, vs0, vs1, vs2...
for i in range(num_layers):
  cubit.cmd('group "vs' + str(i+1) + '" add surface ' + str(s4[sz4[i]]) ) 

# merge all
cubit.cmd('merge vertex all')
cubit.cmd('merge curve all')


# meshing the contiguous geometry.
cubit.cmd('surface all scheme trimesh')
# todo: replace next line with some real sizing information.
cubit.cmd('curve all size 11.6 ')
cubit.cmd('mesh surface all')
# put surfaces in groups that enclose volumes, for those volumes bounded by the domain boundary
cubit.cmd('group "vol1" add surface in g_domain_bdy_f0')
#if num_layers != num_layers_expected:
#  print("Automatic layer assignment will fail. You must manually edit the next lines to assign vs<i> domain-side surfaces to the correct vol<j>")
#  cubit.cmd('ERROR_Automatic_layer_assignment_will_fail._You_must_manually_edit_the_next_lines_to_assign_vs<i>_domain-side_surfaces_to_the_correct_vol<j>')
cubit.cmd('group "vol1" add surface in vs1')
cubit.cmd('group "vol1" add surface in g_hex_tet_faces_0')
cubit.cmd('group "vol1" add surface in g_inclusion_surface_triangulation_0')
#add last bottom triangulation as top of this layer
cubit.cmd('group "vol2" add surface in g_inclusion_surface_triangulation_0')
#if num_layers != num_layers_expected:
#  print("Automatic layer assignment will fail. You must manually edit the next lines to assign vs<i> domain-side surfaces to the correct vol<j>")
#  cubit.cmd('ERROR_Automatic_layer_assignment_will_fail._You_must_manually_edit_the_next_lines_to_assign_vs<i>_domain-side_surfaces_to_the_correct_vol<j>')
cubit.cmd('group "vol2" add surface in vs2')
cubit.cmd('group "vol2" add surface in vs3')
cubit.cmd('group "vol2" add surface in g_hex_tet_faces_1')
# enclosed shell surface triangulation
cubit.cmd('group "vol2" add surface in g_inclusion_surface_triangulation_1')
cubit.cmd('group "vol2" add surface in g_inclusion_surface_triangulation_2')
#add last bottom triangulation as top of this layer
cubit.cmd('group "vol3" add surface in g_inclusion_surface_triangulation_2')
#if num_layers != num_layers_expected:
#  print("Automatic layer assignment will fail. You must manually edit the next lines to assign vs<i> domain-side surfaces to the correct vol<j>")
#  cubit.cmd('ERROR_Automatic_layer_assignment_will_fail._You_must_manually_edit_the_next_lines_to_assign_vs<i>_domain-side_surfaces_to_the_correct_vol<j>')
cubit.cmd('group "vol3" add surface in vs4')
cubit.cmd('group "vol3" add surface in g_hex_tet_faces_3')
cubit.cmd('group "vol3" add surface in g_domain_bdy_f5')
# assign a volume for each closed shell surface
# assumption: all closed shells enclose a single volume, and are not nested
cubit.cmd('group "vol4" add surface in g_inclusion_surface_triangulation_1')
cubit.cmd('group "vol4" add surface in g_hex_tet_faces_2')
# export surface meshes needed for each volume as a single block in an individual exodus file
cubit.cmd('set  Default Block off')
cubit.cmd('reset block')
cubit.cmd('block 1 surface in vol1')
cubit.cmd('export mesh "surface_meshes_1.exo" dimension 3 overwrite')
cubit.cmd('reset block')
cubit.cmd('block 2 surface in vol2')
cubit.cmd('export mesh "surface_meshes_2.exo" dimension 3 overwrite')
cubit.cmd('reset block')
cubit.cmd('block 3 surface in vol3')
cubit.cmd('export mesh "surface_meshes_3.exo" dimension 3 overwrite')
cubit.cmd('reset block')
cubit.cmd('block 4 surface in vol4')
cubit.cmd('export mesh "surface_meshes_4.exo" dimension 3 overwrite')

# tet meshing
# import the triangulation for each shell and tet mesh the interior

cubit.cmd('reset')
cubit.cmd('import mesh "surface_meshes_1.exo" no_geom')
cubit.cmd('tetmesh tri all')
cubit.cmd('create mesh geometry tet all')
cubit.cmd('reset block ')
cubit.cmd('block 1 volume all')
cubit.cmd('export mesh "volume1.exo" overwrite')

cubit.cmd('reset')
cubit.cmd('import mesh "surface_meshes_2.exo" no_geom')
cubit.cmd('tetmesh tri all')
cubit.cmd('create mesh geometry tet all')
cubit.cmd('reset block ')
cubit.cmd('block 1 volume all')
cubit.cmd('export mesh "volume2.exo" overwrite')

cubit.cmd('reset')
cubit.cmd('import mesh "surface_meshes_3.exo" no_geom')
cubit.cmd('tetmesh tri all')
cubit.cmd('create mesh geometry tet all')
cubit.cmd('reset block ')
cubit.cmd('block 1 volume all')
cubit.cmd('export mesh "volume3.exo" overwrite')

cubit.cmd('reset')
cubit.cmd('import mesh "surface_meshes_4.exo" no_geom')
cubit.cmd('tetmesh tri all')
cubit.cmd('create mesh geometry tet all')
cubit.cmd('reset block ')
cubit.cmd('block 1 volume all')
cubit.cmd('export mesh "volume4.exo" overwrite')
