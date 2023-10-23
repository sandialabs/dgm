//
//  example.h
//  BoxTreeMesh
//
//  Created by Mitchell, Scott A on 2/16/16.
//  Copyright (c) 2016 Sandia National Labs. All rights reserved.
//
//  Create example boxtree meshes, and write them out to file
//  Refinement is hard-coded

#ifndef __BoxTreeMesh__example__
#define __BoxTreeMesh__example__

#include "boxtree.h"
#include "testboxtree.h"
#include "boxtreetool.h"

class Example
{
public:
  void create_1(); // 8x8x8
  void create_2(); // 64x64x64 262,144 elements
  void create_3(); // some adjacent box sizes differ by 2
  void create_4(); // some adjacent box sizes differ by 2,3,4
  void create_5(); // refined in a z layer
  void create_6(); // refined in a jagged z layer

  void create_7(); // how big can we go...

  void create_8(); // unbalanced: refine the upper corner of the lower 1st child

  // acousticsurface examples
  void create_test_suite_A();

  void make_surface_1();
  void make_surface_2();
  void make_surface_3();
  
  // hextet examples
  // Pass a bigger number for larger elements, and fewer of them. Does not affect domain size.
  void slide(double element_size=1.);
  
  void inclusion_manifold();
  
  void create_miniinclusion(); // single layer
  void create_mini2inclusion(); // two layers with bubble between
  void volume_mesh_workflow();
  void full_mesh();

  BoxTree tree;
  BoxTreeTool tool;
  TestBoxTree test;
  
  Example() : tree(), tool(&tree) {;}
  
};
#include <stdio.h>

#endif /* defined(__BoxTreeMesh__example__) */
