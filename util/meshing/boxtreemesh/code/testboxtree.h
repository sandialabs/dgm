//
//  testboxtree.h
//  BoxTreeMesh
//
//  Created by Mitchell, Scott A on 1/5/16.
//  Copyright (c) 2016 Sandia National Labs. All rights reserved.
//

#ifndef __BoxTreeMesh__testboxtree__
#define __BoxTreeMesh__testboxtree__

#include <stdio.h>
#include "boxtree.h"
#include "surface.h"

class TestBoxTree
{
public:
  void create_tree();
  void refine_tree();
  void refine_tree( BoxTree *box_tree );
  void report_tree( BoxTree *box_tree );
  
  // return true if everything is OK
  bool test_adjacency();
  bool test_neighbor_functions();
  bool test_neighbor_functions( BoxTree *box_tree );
  
  // for when we start warping stuff
  bool test_adjacent_face_subsets( BoxTree *box_tree );
  bool test_box_overlaps( BoxTree *box_tree );
  
  bool test_balance(BoxTree *bt, int side_length_factor, SubBoxType balance_type);
  
  bool test_inclusionbodies();
};

#endif /* defined(__BoxTreeMesh__testboxtree__) */
