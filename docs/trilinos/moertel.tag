<?xml version='1.0' encoding='UTF-8' standalone='yes' ?>
<tagfile>
  <compound kind="file">
    <name>mrtr_function.H</name>
    <path>/Users/sscoll/dist/trilinos/packages/moertel/src/mortar/</path>
    <filename>mrtr__function_8H</filename>
    <class kind="class">MOERTEL::Function</class>
    <namespace>MOERTEL</namespace>
  </compound>
  <compound kind="file">
    <name>mrtr_functions.H</name>
    <path>/Users/sscoll/dist/trilinos/packages/moertel/src/mortar/</path>
    <filename>mrtr__functions_8H</filename>
    <includes id="mrtr__function_8H" name="mrtr_function.H" local="yes" imported="no">mrtr_function.H</includes>
    <class kind="class">MOERTEL::Function_Constant1D</class>
    <class kind="class">MOERTEL::Function_Linear1D</class>
    <class kind="class">MOERTEL::Function_DualLinear1D</class>
    <class kind="class">MOERTEL::Function_LinearTri</class>
    <class kind="class">MOERTEL::Function_DualLinearTri</class>
    <class kind="class">MOERTEL::Function_ConstantTri</class>
    <class kind="class">MOERTEL::Function_BiLinearQuad</class>
    <class kind="class">MOERTEL::Function_DualBiLinearQuad</class>
    <namespace>MOERTEL</namespace>
  </compound>
  <compound kind="file">
    <name>mrtr_integrator.H</name>
    <path>/Users/sscoll/dist/trilinos/packages/moertel/src/mortar/</path>
    <filename>mrtr__integrator_8H</filename>
    <includes id="mrtr__overlap_8H" name="mrtr_overlap.H" local="yes" imported="no">mrtr_overlap.H</includes>
    <class kind="class">MOERTEL::Integrator</class>
    <namespace>MOERTEL</namespace>
  </compound>
  <compound kind="file">
    <name>mrtr_interface.H</name>
    <path>/Users/sscoll/dist/trilinos/packages/moertel/src/mortar/</path>
    <filename>mrtr__interface_8H</filename>
    <includes id="mrtr__lm__selector_8H" name="mrtr_lm_selector.H" local="yes" imported="no">mrtr_lm_selector.H</includes>
    <includes id="mrtr__segment_8H" name="mrtr_segment.H" local="yes" imported="no">mrtr_segment.H</includes>
    <includes id="mrtr__node_8H" name="mrtr_node.H" local="yes" imported="no">mrtr_node.H</includes>
    <includes id="mrtr__projector_8H" name="mrtr_projector.H" local="yes" imported="no">mrtr_projector.H</includes>
    <class kind="class">MOERTEL::Interface</class>
    <namespace>MOERTEL</namespace>
  </compound>
  <compound kind="file">
    <name>mrtr_lm_selector.H</name>
    <path>/Users/sscoll/dist/trilinos/packages/moertel/src/mortar/</path>
    <filename>mrtr__lm__selector_8H</filename>
    <includes id="mrtr__node_8H" name="mrtr_node.H" local="yes" imported="no">mrtr_node.H</includes>
    <class kind="class">MOERTEL::Lmselector</class>
    <namespace>MOERTEL</namespace>
  </compound>
  <compound kind="file">
    <name>mrtr_manager.H</name>
    <path>/Users/sscoll/dist/trilinos/packages/moertel/src/mortar/</path>
    <filename>mrtr__manager_8H</filename>
    <includes id="mrtr__segment_8H" name="mrtr_segment.H" local="yes" imported="no">mrtr_segment.H</includes>
    <includes id="mrtr__node_8H" name="mrtr_node.H" local="yes" imported="no">mrtr_node.H</includes>
    <includes id="mrtr__interface_8H" name="mrtr_interface.H" local="yes" imported="no">mrtr_interface.H</includes>
    <includes id="mrtr__lm__selector_8H" name="mrtr_lm_selector.H" local="yes" imported="no">mrtr_lm_selector.H</includes>
    <includes id="mrtr__solver_8H" name="mrtr_solver.H" local="yes" imported="no">mrtr_solver.H</includes>
    <includes id="mrtr__utils_8H" name="mrtr_utils.H" local="yes" imported="no">mrtr_utils.H</includes>
    <class kind="class">MOERTEL::Manager</class>
    <namespace>MOERTEL</namespace>
    <member kind="function">
      <type>std::ostream &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>mrtr__manager_8H.html</anchorfile>
      <anchor>af74be61f4f45e27c1a49e427da92c958</anchor>
      <arglist>(std::ostream &amp;os, const MOERTEL::Manager &amp;node)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>mrtr_ml_preconditioner.H</name>
    <path>/Users/sscoll/dist/trilinos/packages/moertel/src/mortar/</path>
    <filename>mrtr__ml__preconditioner_8H</filename>
    <includes id="mrtr__utils_8H" name="mrtr_utils.H" local="yes" imported="no">mrtr_utils.H</includes>
    <class kind="class">MOERTEL::Mortar_ML_Preconditioner</class>
    <namespace>MOERTEL</namespace>
  </compound>
  <compound kind="file">
    <name>mrtr_node.H</name>
    <path>/Users/sscoll/dist/trilinos/packages/moertel/src/mortar/</path>
    <filename>mrtr__node_8H</filename>
    <class kind="class">MOERTEL::Node</class>
    <namespace>MOERTEL</namespace>
  </compound>
  <compound kind="file">
    <name>mrtr_overlap.H</name>
    <path>/Users/sscoll/dist/trilinos/packages/moertel/src/mortar/</path>
    <filename>mrtr__overlap_8H</filename>
    <includes id="mrtr__point_8H" name="mrtr_point.H" local="yes" imported="no">mrtr_point.H</includes>
    <class kind="class">MOERTEL::Overlap</class>
    <namespace>MOERTEL</namespace>
  </compound>
  <compound kind="file">
    <name>mrtr_pnode.H</name>
    <path>/Users/sscoll/dist/trilinos/packages/moertel/src/mortar/</path>
    <filename>mrtr__pnode_8H</filename>
    <includes id="mrtr__node_8H" name="mrtr_node.H" local="yes" imported="no">mrtr_node.H</includes>
    <class kind="class">MOERTEL::ProjectedNode</class>
    <namespace>MOERTEL</namespace>
  </compound>
  <compound kind="file">
    <name>mrtr_point.H</name>
    <path>/Users/sscoll/dist/trilinos/packages/moertel/src/mortar/</path>
    <filename>mrtr__point_8H</filename>
    <includes id="mrtr__node_8H" name="mrtr_node.H" local="yes" imported="no">mrtr_node.H</includes>
    <class kind="class">MOERTEL::Point</class>
    <namespace>MOERTEL</namespace>
  </compound>
  <compound kind="file">
    <name>mrtr_projector.H</name>
    <path>/Users/sscoll/dist/trilinos/packages/moertel/src/mortar/</path>
    <filename>mrtr__projector_8H</filename>
    <class kind="class">MOERTEL::Projector</class>
    <namespace>MOERTEL</namespace>
  </compound>
  <compound kind="file">
    <name>mrtr_segment.H</name>
    <path>/Users/sscoll/dist/trilinos/packages/moertel/src/mortar/</path>
    <filename>mrtr__segment_8H</filename>
    <includes id="mrtr__function_8H" name="mrtr_function.H" local="yes" imported="no">mrtr_function.H</includes>
    <class kind="class">MOERTEL::Segment</class>
    <namespace>MOERTEL</namespace>
  </compound>
  <compound kind="file">
    <name>mrtr_segment_bilinearquad.H</name>
    <path>/Users/sscoll/dist/trilinos/packages/moertel/src/mortar/</path>
    <filename>mrtr__segment__bilinearquad_8H</filename>
    <includes id="mrtr__segment_8H" name="mrtr_segment.H" local="yes" imported="no">mrtr_segment.H</includes>
    <includes id="mrtr__functions_8H" name="mrtr_functions.H" local="yes" imported="no">mrtr_functions.H</includes>
    <includes id="mrtr__utils_8H" name="mrtr_utils.H" local="yes" imported="no">mrtr_utils.H</includes>
    <class kind="class">MOERTEL::Segment_BiLinearQuad</class>
    <namespace>MOERTEL</namespace>
  </compound>
  <compound kind="file">
    <name>mrtr_segment_bilineartri.H</name>
    <path>/Users/sscoll/dist/trilinos/packages/moertel/src/mortar/</path>
    <filename>mrtr__segment__bilineartri_8H</filename>
    <includes id="mrtr__segment_8H" name="mrtr_segment.H" local="yes" imported="no">mrtr_segment.H</includes>
    <includes id="mrtr__functions_8H" name="mrtr_functions.H" local="yes" imported="no">mrtr_functions.H</includes>
    <includes id="mrtr__utils_8H" name="mrtr_utils.H" local="yes" imported="no">mrtr_utils.H</includes>
    <class kind="class">MOERTEL::Segment_BiLinearTri</class>
    <namespace>MOERTEL</namespace>
  </compound>
  <compound kind="file">
    <name>mrtr_segment_linear1D.H</name>
    <path>/Users/sscoll/dist/trilinos/packages/moertel/src/mortar/</path>
    <filename>mrtr__segment__linear1D_8H</filename>
    <includes id="mrtr__segment_8H" name="mrtr_segment.H" local="yes" imported="no">mrtr_segment.H</includes>
    <includes id="mrtr__functions_8H" name="mrtr_functions.H" local="yes" imported="no">mrtr_functions.H</includes>
    <includes id="mrtr__utils_8H" name="mrtr_utils.H" local="yes" imported="no">mrtr_utils.H</includes>
    <class kind="class">MOERTEL::Segment_Linear1D</class>
    <namespace>MOERTEL</namespace>
  </compound>
  <compound kind="file">
    <name>mrtr_solver.H</name>
    <path>/Users/sscoll/dist/trilinos/packages/moertel/src/mortar/</path>
    <filename>mrtr__solver_8H</filename>
    <includes id="mrtr__utils_8H" name="mrtr_utils.H" local="yes" imported="no">mrtr_utils.H</includes>
    <includes id="mrtr__ml__preconditioner_8H" name="mrtr_ml_preconditioner.H" local="yes" imported="no">mrtr_ml_preconditioner.H</includes>
    <class kind="class">MOERTEL::Solver</class>
    <namespace>MOERTEL</namespace>
  </compound>
  <compound kind="file">
    <name>mrtr_utils.H</name>
    <path>/Users/sscoll/dist/trilinos/packages/moertel/src/mortar/</path>
    <filename>mrtr__utils_8H</filename>
    <includes id="mrtr__segment_8H" name="mrtr_segment.H" local="yes" imported="no">mrtr_segment.H</includes>
    <includes id="mrtr__functions_8H" name="mrtr_functions.H" local="yes" imported="no">mrtr_functions.H</includes>
    <includes id="mrtr__node_8H" name="mrtr_node.H" local="yes" imported="no">mrtr_node.H</includes>
    <includes id="mrtr__point_8H" name="mrtr_point.H" local="yes" imported="no">mrtr_point.H</includes>
    <namespace>MOERTEL</namespace>
    <member kind="function">
      <type>MOERTEL::Function *</type>
      <name>AllocateFunction</name>
      <anchorfile>namespaceMOERTEL.html</anchorfile>
      <anchor>a2292a15a5612751f7592d7fc01a6bee6</anchor>
      <arglist>(MOERTEL::Function::FunctionType type, int out)</arglist>
    </member>
    <member kind="function">
      <type>MOERTEL::Segment *</type>
      <name>AllocateSegment</name>
      <anchorfile>namespaceMOERTEL.html</anchorfile>
      <anchor>a1e478269c2d3471a05bb1f04b5b74c78</anchor>
      <arglist>(int type, int out)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>cross</name>
      <anchorfile>namespaceMOERTEL.html</anchorfile>
      <anchor>a95a4ac68471ca7763e345c3b3fc1d3f8</anchor>
      <arglist>(double *out, const double *g1, const double *g2)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>dot</name>
      <anchorfile>namespaceMOERTEL.html</anchorfile>
      <anchor>a151477363f39b69025ed229098218007</anchor>
      <arglist>(const double *g1, const double *g2, const int dim)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>length</name>
      <anchorfile>namespaceMOERTEL.html</anchorfile>
      <anchor>ac09fcdda79447314bf6e7497af4a81ee</anchor>
      <arglist>(const double *g, const int dim)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>solve22</name>
      <anchorfile>namespaceMOERTEL.html</anchorfile>
      <anchor>a748d6409f9535bea245d74ceb6ed302e</anchor>
      <arglist>(const double A[][2], double *x, const double *b)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>solve33</name>
      <anchorfile>namespaceMOERTEL.html</anchorfile>
      <anchor>aa7c36f24184e3884b1325c0158424e79</anchor>
      <arglist>(const double A[][3], double *x, const double *b)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>digit_ten</name>
      <anchorfile>namespaceMOERTEL.html</anchorfile>
      <anchor>a1f0d3e57b39b23f6c8d7f16db0a92c44</anchor>
      <arglist>(int i)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>sort</name>
      <anchorfile>namespaceMOERTEL.html</anchorfile>
      <anchor>aaa1156aa4052469008fb714d754c5125</anchor>
      <arglist>(double *dlist, int N, int *list2)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>swap</name>
      <anchorfile>namespaceMOERTEL.html</anchorfile>
      <anchor>ae9d58fa193829f56ff8402e00df4302c</anchor>
      <arglist>(kind &amp;a, kind &amp;b)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>MatrixMatrixAdd</name>
      <anchorfile>namespaceMOERTEL.html</anchorfile>
      <anchor>acc436dd612f949b54aef7a890acffc50</anchor>
      <arglist>(const Epetra_CrsMatrix &amp;A, bool transposeA, double scalarA, Epetra_CrsMatrix &amp;B, double scalarB)</arglist>
    </member>
    <member kind="function">
      <type>Epetra_CrsMatrix *</type>
      <name>MatMatMult</name>
      <anchorfile>namespaceMOERTEL.html</anchorfile>
      <anchor>aaf50d9d9fb22d187ae54c9699c166714</anchor>
      <arglist>(const Epetra_CrsMatrix &amp;A, bool transA, const Epetra_CrsMatrix &amp;B, bool transB, int outlevel)</arglist>
    </member>
    <member kind="function">
      <type>Epetra_CrsMatrix *</type>
      <name>PaddedMatrix</name>
      <anchorfile>namespaceMOERTEL.html</anchorfile>
      <anchor>a98c6fa42cc989f9b95b5c5940d763d40</anchor>
      <arglist>(const Epetra_Map rowmap, double val, const int numentriesperrow)</arglist>
    </member>
    <member kind="function">
      <type>Epetra_CrsMatrix *</type>
      <name>StripZeros</name>
      <anchorfile>namespaceMOERTEL.html</anchorfile>
      <anchor>ac5fa3b515f001b60ca6ff8ff1123b46d</anchor>
      <arglist>(Epetra_CrsMatrix &amp;A, double eps)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>SplitMatrix2x2</name>
      <anchorfile>namespaceMOERTEL.html</anchorfile>
      <anchor>a22fe81ebc38fae7cc0862ef6997deb12</anchor>
      <arglist>(Teuchos::RCP&lt; Epetra_CrsMatrix &gt; A, Teuchos::RCP&lt; Epetra_Map &gt; &amp;A11rowmap, Teuchos::RCP&lt; Epetra_Map &gt; &amp;A22rowmap, Teuchos::RCP&lt; Epetra_CrsMatrix &gt; &amp;A11, Teuchos::RCP&lt; Epetra_CrsMatrix &gt; &amp;A12, Teuchos::RCP&lt; Epetra_CrsMatrix &gt; &amp;A21, Teuchos::RCP&lt; Epetra_CrsMatrix &gt; &amp;A22)</arglist>
    </member>
    <member kind="function">
      <type>Epetra_Map *</type>
      <name>SplitMap</name>
      <anchorfile>namespaceMOERTEL.html</anchorfile>
      <anchor>abf22072c2c1aebe092b2167d7b5acdf7</anchor>
      <arglist>(const Epetra_Map &amp;Amap, const Epetra_Map &amp;Agiven)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>SplitVector</name>
      <anchorfile>namespaceMOERTEL.html</anchorfile>
      <anchor>a6a3aaccc52d72ae389518058d5c4d338</anchor>
      <arglist>(const Epetra_Vector &amp;x, const Epetra_Map &amp;x1map, Epetra_Vector *&amp;x1, const Epetra_Map &amp;x2map, Epetra_Vector *&amp;x2)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>MergeVector</name>
      <anchorfile>namespaceMOERTEL.html</anchorfile>
      <anchor>aa11e72d437f3e34b1f209215ca0bbf3d</anchor>
      <arglist>(const Epetra_Vector &amp;x1, const Epetra_Vector &amp;x2, Epetra_Vector &amp;xresult)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>Print_Matrix</name>
      <anchorfile>namespaceMOERTEL.html</anchorfile>
      <anchor>a6fde3a1a5ad6639904f6f783378227fa</anchor>
      <arglist>(std::string name, Epetra_CrsMatrix &amp;A, int ibase)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>Print_Graph</name>
      <anchorfile>namespaceMOERTEL.html</anchorfile>
      <anchor>a41cdcc4d764c3da0b3c62f8d4c5b98a6</anchor>
      <arglist>(std::string name, Epetra_CrsGraph &amp;A, int ibase)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>Print_Vector</name>
      <anchorfile>namespaceMOERTEL.html</anchorfile>
      <anchor>ac1995680e59c21d20debffb5e814f496</anchor>
      <arglist>(std::string name, Epetra_Vector &amp;v, int ibase)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ReportError</name>
      <anchorfile>namespaceMOERTEL.html</anchorfile>
      <anchor>ad2279567e4edf7e5a9024e236b84e17d</anchor>
      <arglist>(const std::stringstream &amp;Message)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>TwoSquares.cpp</name>
    <path>/Users/sscoll/dist/trilinos/packages/moertel/example/TwoSquares/</path>
    <filename>TwoSquares_8cpp</filename>
    <includes id="mrtr__manager_8H" name="mrtr_manager.H" local="yes" imported="no">mrtr_manager.H</includes>
    <includes id="mrtr__segment__linear1D_8H" name="mrtr_segment_linear1D.H" local="yes" imported="no">mrtr_segment_linear1D.H</includes>
  </compound>
  <compound kind="class">
    <name>MOERTEL::Function</name>
    <filename>classMOERTEL_1_1Function.html</filename>
    <member kind="enumeration">
      <type></type>
      <name>FunctionType</name>
      <anchorfile>classMOERTEL_1_1Function.html</anchorfile>
      <anchor>ad090ca512a1986d3879c2966cf9c98f2</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Function</name>
      <anchorfile>classMOERTEL_1_1Function.html</anchorfile>
      <anchor>a859d39beef1290a33fbc49f4c5ea8d37</anchor>
      <arglist>(int outlevel, MOERTEL::Function::FunctionType type)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Function</name>
      <anchorfile>classMOERTEL_1_1Function.html</anchorfile>
      <anchor>a409fd2dc45fc20313581ab659976a319</anchor>
      <arglist>(const MOERTEL::Function &amp;old)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~Function</name>
      <anchorfile>classMOERTEL_1_1Function.html</anchorfile>
      <anchor>a2dd8e6229ac400bf3ce0afab025eb18e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual MOERTEL::Function *</type>
      <name>Clone</name>
      <anchorfile>classMOERTEL_1_1Function.html</anchorfile>
      <anchor>a8f6be8286d15eb7c5a5d66e69d878e4b</anchor>
      <arglist>() const  =0</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>OutLevel</name>
      <anchorfile>classMOERTEL_1_1Function.html</anchorfile>
      <anchor>adc8e463a779f5faf66e1a7a4612b39c8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>MOERTEL::Function::FunctionType</type>
      <name>Type</name>
      <anchorfile>classMOERTEL_1_1Function.html</anchorfile>
      <anchor>acbc2c10a47a95f4ab8739566f00774f3</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>EvaluateFunction</name>
      <anchorfile>classMOERTEL_1_1Function.html</anchorfile>
      <anchor>a907153fb4c9effaa744af47f2694bd61</anchor>
      <arglist>(const MOERTEL::Segment &amp;seg, const double *xi, double *val, const int valdim, double *deriv)=0</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Function</name>
      <anchorfile>classMOERTEL_1_1Function.html</anchorfile>
      <anchor>a859d39beef1290a33fbc49f4c5ea8d37</anchor>
      <arglist>(int outlevel, MOERTEL::Function::FunctionType type)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Function</name>
      <anchorfile>classMOERTEL_1_1Function.html</anchorfile>
      <anchor>a409fd2dc45fc20313581ab659976a319</anchor>
      <arglist>(const MOERTEL::Function &amp;old)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~Function</name>
      <anchorfile>classMOERTEL_1_1Function.html</anchorfile>
      <anchor>a2dd8e6229ac400bf3ce0afab025eb18e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual MOERTEL::Function *</type>
      <name>Clone</name>
      <anchorfile>classMOERTEL_1_1Function.html</anchorfile>
      <anchor>a8f6be8286d15eb7c5a5d66e69d878e4b</anchor>
      <arglist>() const  =0</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>OutLevel</name>
      <anchorfile>classMOERTEL_1_1Function.html</anchorfile>
      <anchor>adc8e463a779f5faf66e1a7a4612b39c8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>MOERTEL::Function::FunctionType</type>
      <name>Type</name>
      <anchorfile>classMOERTEL_1_1Function.html</anchorfile>
      <anchor>acbc2c10a47a95f4ab8739566f00774f3</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>EvaluateFunction</name>
      <anchorfile>classMOERTEL_1_1Function.html</anchorfile>
      <anchor>a907153fb4c9effaa744af47f2694bd61</anchor>
      <arglist>(const MOERTEL::Segment &amp;seg, const double *xi, double *val, const int valdim, double *deriv)=0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>MOERTEL::Function_BiLinearQuad</name>
    <filename>classMOERTEL_1_1Function__BiLinearQuad.html</filename>
    <base>MOERTEL::Function</base>
    <member kind="function">
      <type></type>
      <name>Function_BiLinearQuad</name>
      <anchorfile>classMOERTEL_1_1Function__BiLinearQuad.html</anchorfile>
      <anchor>a164a9bbcdd09875214c0332149b5e779</anchor>
      <arglist>(int out)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Function_BiLinearQuad</name>
      <anchorfile>classMOERTEL_1_1Function__BiLinearQuad.html</anchorfile>
      <anchor>a6ffb5b2aaf78aad71c49f12e87cfa571</anchor>
      <arglist>(const MOERTEL::Function_BiLinearQuad &amp;old)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual MOERTEL::Function *</type>
      <name>Clone</name>
      <anchorfile>classMOERTEL_1_1Function__BiLinearQuad.html</anchorfile>
      <anchor>a77c75edf0ffd5f0eb734b2a8bb35d412</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~Function_BiLinearQuad</name>
      <anchorfile>classMOERTEL_1_1Function__BiLinearQuad.html</anchorfile>
      <anchor>af58a61b3d05ef07322b36080abb2e534</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>EvaluateFunction</name>
      <anchorfile>classMOERTEL_1_1Function__BiLinearQuad.html</anchorfile>
      <anchor>a22a17272234421a7d69fb7e663b79a62</anchor>
      <arglist>(const MOERTEL::Segment &amp;seg, const double *xi, double *val, const int valdim, double *deriv)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>MOERTEL::Function_Constant1D</name>
    <filename>classMOERTEL_1_1Function__Constant1D.html</filename>
    <base>MOERTEL::Function</base>
    <member kind="function">
      <type></type>
      <name>Function_Constant1D</name>
      <anchorfile>classMOERTEL_1_1Function__Constant1D.html</anchorfile>
      <anchor>aec2e002a012b971ec60c51ef2513096e</anchor>
      <arglist>(int out)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Function_Constant1D</name>
      <anchorfile>classMOERTEL_1_1Function__Constant1D.html</anchorfile>
      <anchor>a2e29cfff526ad481cb45d08548be74ab</anchor>
      <arglist>(const MOERTEL::Function_Constant1D &amp;old)</arglist>
    </member>
    <member kind="function">
      <type>MOERTEL::Function *</type>
      <name>Clone</name>
      <anchorfile>classMOERTEL_1_1Function__Constant1D.html</anchorfile>
      <anchor>a39381ba73c8e65dc6a14c87e0f22b5e1</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~Function_Constant1D</name>
      <anchorfile>classMOERTEL_1_1Function__Constant1D.html</anchorfile>
      <anchor>a95338482f8d6d9bc6a429b146752dfae</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>EvaluateFunction</name>
      <anchorfile>classMOERTEL_1_1Function__Constant1D.html</anchorfile>
      <anchor>a7541439fe90a18b7aa9a75fade241e05</anchor>
      <arglist>(const MOERTEL::Segment &amp;seg, const double *xi, double *val, const int valdim, double *deriv)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>MOERTEL::Function_ConstantTri</name>
    <filename>classMOERTEL_1_1Function__ConstantTri.html</filename>
    <base>MOERTEL::Function</base>
    <member kind="function">
      <type></type>
      <name>Function_ConstantTri</name>
      <anchorfile>classMOERTEL_1_1Function__ConstantTri.html</anchorfile>
      <anchor>ac47e5474027f4d089425e6b7afeb79d5</anchor>
      <arglist>(int out)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Function_ConstantTri</name>
      <anchorfile>classMOERTEL_1_1Function__ConstantTri.html</anchorfile>
      <anchor>ad900f803230230c12d74de17d0c101bf</anchor>
      <arglist>(const MOERTEL::Function_ConstantTri &amp;old)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual MOERTEL::Function *</type>
      <name>Clone</name>
      <anchorfile>classMOERTEL_1_1Function__ConstantTri.html</anchorfile>
      <anchor>a66a0032b0f91362f0fe194b64a72277b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~Function_ConstantTri</name>
      <anchorfile>classMOERTEL_1_1Function__ConstantTri.html</anchorfile>
      <anchor>a1ae6b5d5e2aa60471252329a154f13fe</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>EvaluateFunction</name>
      <anchorfile>classMOERTEL_1_1Function__ConstantTri.html</anchorfile>
      <anchor>adc426d87ed2cbe2b0cd7edb25128c2c7</anchor>
      <arglist>(const MOERTEL::Segment &amp;seg, const double *xi, double *val, const int valdim, double *deriv)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>MOERTEL::Function_DualBiLinearQuad</name>
    <filename>classMOERTEL_1_1Function__DualBiLinearQuad.html</filename>
    <base>MOERTEL::Function</base>
    <member kind="function">
      <type></type>
      <name>Function_DualBiLinearQuad</name>
      <anchorfile>classMOERTEL_1_1Function__DualBiLinearQuad.html</anchorfile>
      <anchor>a0a5f6781f3420a17c9814fbd4ea7bd0e</anchor>
      <arglist>(int out)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Function_DualBiLinearQuad</name>
      <anchorfile>classMOERTEL_1_1Function__DualBiLinearQuad.html</anchorfile>
      <anchor>acea0f1b18b01f18cc09d089445642547</anchor>
      <arglist>(const MOERTEL::Function_DualBiLinearQuad &amp;old)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual MOERTEL::Function *</type>
      <name>Clone</name>
      <anchorfile>classMOERTEL_1_1Function__DualBiLinearQuad.html</anchorfile>
      <anchor>a4678629700d47a25474bac91cd34b4d2</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~Function_DualBiLinearQuad</name>
      <anchorfile>classMOERTEL_1_1Function__DualBiLinearQuad.html</anchorfile>
      <anchor>a30debe8af41a13b6cd626e6be51cfffb</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>EvaluateFunction</name>
      <anchorfile>classMOERTEL_1_1Function__DualBiLinearQuad.html</anchorfile>
      <anchor>a03dc1c21639c5a5354c1808bec67c2c7</anchor>
      <arglist>(const MOERTEL::Segment &amp;seg, const double *xi, double *val, const int valdim, double *deriv)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>MOERTEL::Function_DualLinear1D</name>
    <filename>classMOERTEL_1_1Function__DualLinear1D.html</filename>
    <base>MOERTEL::Function</base>
    <member kind="function">
      <type></type>
      <name>Function_DualLinear1D</name>
      <anchorfile>classMOERTEL_1_1Function__DualLinear1D.html</anchorfile>
      <anchor>a92892e4d90b806c84fe1fb63313e4d04</anchor>
      <arglist>(int out)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Function_DualLinear1D</name>
      <anchorfile>classMOERTEL_1_1Function__DualLinear1D.html</anchorfile>
      <anchor>aa270f63f417bd01706df1dc2b4b51741</anchor>
      <arglist>(const MOERTEL::Function_DualLinear1D &amp;old)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual MOERTEL::Function *</type>
      <name>Clone</name>
      <anchorfile>classMOERTEL_1_1Function__DualLinear1D.html</anchorfile>
      <anchor>a486cb182fb09308d481447896c15d81a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~Function_DualLinear1D</name>
      <anchorfile>classMOERTEL_1_1Function__DualLinear1D.html</anchorfile>
      <anchor>a0fa3e5e6ccfe206754a96c0194639b75</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>EvaluateFunction</name>
      <anchorfile>classMOERTEL_1_1Function__DualLinear1D.html</anchorfile>
      <anchor>ae13b77621b2aef869b1831ee17f08d81</anchor>
      <arglist>(const MOERTEL::Segment &amp;seg, const double *xi, double *val, const int valdim, double *deriv)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>MOERTEL::Function_DualLinearTri</name>
    <filename>classMOERTEL_1_1Function__DualLinearTri.html</filename>
    <base>MOERTEL::Function</base>
    <member kind="function">
      <type></type>
      <name>Function_DualLinearTri</name>
      <anchorfile>classMOERTEL_1_1Function__DualLinearTri.html</anchorfile>
      <anchor>a73a646d2ccefb0c10559e3a7a67d0290</anchor>
      <arglist>(int out)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Function_DualLinearTri</name>
      <anchorfile>classMOERTEL_1_1Function__DualLinearTri.html</anchorfile>
      <anchor>a61f6971a73e254cbbed1d6c0d3e3a207</anchor>
      <arglist>(const MOERTEL::Function_DualLinearTri &amp;old)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual MOERTEL::Function *</type>
      <name>Clone</name>
      <anchorfile>classMOERTEL_1_1Function__DualLinearTri.html</anchorfile>
      <anchor>a540c9bfcabda57eb0d8a372334127fc1</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~Function_DualLinearTri</name>
      <anchorfile>classMOERTEL_1_1Function__DualLinearTri.html</anchorfile>
      <anchor>ae467227c91253bb17ad46b189d1470bd</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>EvaluateFunction</name>
      <anchorfile>classMOERTEL_1_1Function__DualLinearTri.html</anchorfile>
      <anchor>a070a68b6ace81372f8e99de40b8113ee</anchor>
      <arglist>(const MOERTEL::Segment &amp;seg, const double *xi, double *val, const int valdim, double *deriv)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>MOERTEL::Function_Linear1D</name>
    <filename>classMOERTEL_1_1Function__Linear1D.html</filename>
    <base>MOERTEL::Function</base>
    <member kind="function">
      <type></type>
      <name>Function_Linear1D</name>
      <anchorfile>classMOERTEL_1_1Function__Linear1D.html</anchorfile>
      <anchor>a22dcba23f5965de9689bca1d62490d2e</anchor>
      <arglist>(int out)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Function_Linear1D</name>
      <anchorfile>classMOERTEL_1_1Function__Linear1D.html</anchorfile>
      <anchor>ac64a7ad4c13aedb35b4b3634d30f0038</anchor>
      <arglist>(const MOERTEL::Function_Linear1D &amp;old)</arglist>
    </member>
    <member kind="function">
      <type>MOERTEL::Function *</type>
      <name>Clone</name>
      <anchorfile>classMOERTEL_1_1Function__Linear1D.html</anchorfile>
      <anchor>ab3c0215d587eb79e5ff462cf6cb9de15</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~Function_Linear1D</name>
      <anchorfile>classMOERTEL_1_1Function__Linear1D.html</anchorfile>
      <anchor>ad590a7693ba8b834618ededef616669b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>EvaluateFunction</name>
      <anchorfile>classMOERTEL_1_1Function__Linear1D.html</anchorfile>
      <anchor>a7a18c3460d23921e8ac6ac19eabb8500</anchor>
      <arglist>(const MOERTEL::Segment &amp;seg, const double *xi, double *val, const int valdim, double *deriv)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>MOERTEL::Function_LinearTri</name>
    <filename>classMOERTEL_1_1Function__LinearTri.html</filename>
    <base>MOERTEL::Function</base>
    <member kind="function">
      <type></type>
      <name>Function_LinearTri</name>
      <anchorfile>classMOERTEL_1_1Function__LinearTri.html</anchorfile>
      <anchor>a84cf788fad991f621d42ee8562456885</anchor>
      <arglist>(int out)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Function_LinearTri</name>
      <anchorfile>classMOERTEL_1_1Function__LinearTri.html</anchorfile>
      <anchor>a86113eb1d3f1e1696a31e475c69f40d6</anchor>
      <arglist>(const MOERTEL::Function_LinearTri &amp;old)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual MOERTEL::Function *</type>
      <name>Clone</name>
      <anchorfile>classMOERTEL_1_1Function__LinearTri.html</anchorfile>
      <anchor>af7886661f47b6002e07682c97686860f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~Function_LinearTri</name>
      <anchorfile>classMOERTEL_1_1Function__LinearTri.html</anchorfile>
      <anchor>aa8c72c236d0ec09420e9f7cdb6003c5f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>EvaluateFunction</name>
      <anchorfile>classMOERTEL_1_1Function__LinearTri.html</anchorfile>
      <anchor>a3fa84892b0e33d21077e8bef1f50faa6</anchor>
      <arglist>(const MOERTEL::Segment &amp;seg, const double *xi, double *val, const int valdim, double *deriv)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>MOERTEL::Integrator</name>
    <filename>classMOERTEL_1_1Integrator.html</filename>
    <member kind="function">
      <type></type>
      <name>Integrator</name>
      <anchorfile>classMOERTEL_1_1Integrator.html</anchorfile>
      <anchor>a4a7704d5cc75107e8728554eb6d9e9da</anchor>
      <arglist>(int ngp, bool oneD, int outlevel)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~Integrator</name>
      <anchorfile>classMOERTEL_1_1Integrator.html</anchorfile>
      <anchor>a48a3a6135622eb6087800fafa8b4a54b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>OutLevel</name>
      <anchorfile>classMOERTEL_1_1Integrator.html</anchorfile>
      <anchor>af8ea7e58de600e68df11a148a5c9e8af</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Ngp</name>
      <anchorfile>classMOERTEL_1_1Integrator.html</anchorfile>
      <anchor>ae56a72380a3afa68471811eda40d5f3f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>Coordinate</name>
      <anchorfile>classMOERTEL_1_1Integrator.html</anchorfile>
      <anchor>afd63dc0c98fcbada150fbd28b15ae546</anchor>
      <arglist>(int gp)</arglist>
    </member>
    <member kind="function">
      <type>double *</type>
      <name>Coordinate</name>
      <anchorfile>classMOERTEL_1_1Integrator.html</anchorfile>
      <anchor>a9da61f9fbb786faad257a15d6374aa82</anchor>
      <arglist>(int *gp)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>Weight</name>
      <anchorfile>classMOERTEL_1_1Integrator.html</anchorfile>
      <anchor>a57acebf03a9ac2511943e46ae46ca083</anchor>
      <arglist>(int gp)</arglist>
    </member>
    <member kind="function">
      <type>Epetra_SerialDenseMatrix *</type>
      <name>Integrate</name>
      <anchorfile>classMOERTEL_1_1Integrator.html</anchorfile>
      <anchor>a2faed76747fc4b1d0310fa53d80689b7</anchor>
      <arglist>(MOERTEL::Segment &amp;sseg, double sxia, double sxib, MOERTEL::Segment &amp;mseg, double mxia, double mxib)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>Assemble</name>
      <anchorfile>classMOERTEL_1_1Integrator.html</anchorfile>
      <anchor>a130e255785dd9201ea47c36ea6d581d5</anchor>
      <arglist>(MOERTEL::Interface &amp;inter, MOERTEL::Segment &amp;sseg, MOERTEL::Segment &amp;mseg, Epetra_CrsMatrix &amp;M, Epetra_SerialDenseMatrix &amp;Mdense)</arglist>
    </member>
    <member kind="function">
      <type>Epetra_SerialDenseMatrix *</type>
      <name>Integrate</name>
      <anchorfile>classMOERTEL_1_1Integrator.html</anchorfile>
      <anchor>a6cb9458232b327d4301c851629311ee6</anchor>
      <arglist>(MOERTEL::Segment &amp;sseg, double sxia, double sxib)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>Assemble</name>
      <anchorfile>classMOERTEL_1_1Integrator.html</anchorfile>
      <anchor>a63c7a20818b471cbc6d2b4e06fd329e6</anchor>
      <arglist>(MOERTEL::Interface &amp;inter, MOERTEL::Segment &amp;sseg, Epetra_CrsMatrix &amp;D, Epetra_SerialDenseMatrix &amp;Ddense)</arglist>
    </member>
    <member kind="function">
      <type>Epetra_SerialDenseMatrix *</type>
      <name>Integrate_2D_Mmod</name>
      <anchorfile>classMOERTEL_1_1Integrator.html</anchorfile>
      <anchor>a5009f9ba0b9605af96ba722409fa8e01</anchor>
      <arglist>(MOERTEL::Segment &amp;sseg, double sxia, double sxib, MOERTEL::Segment &amp;mseg, double mxia, double mxib)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>Assemble_2D_Mod</name>
      <anchorfile>classMOERTEL_1_1Integrator.html</anchorfile>
      <anchor>a0e17d500b9d45da50afdc4445e016023</anchor>
      <arglist>(MOERTEL::Interface &amp;inter, MOERTEL::Segment &amp;sseg, MOERTEL::Segment &amp;mseg, Epetra_SerialDenseMatrix &amp;Mmod)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>Integrate</name>
      <anchorfile>classMOERTEL_1_1Integrator.html</anchorfile>
      <anchor>aec9f196cd64853ddce55f1eda8abd068</anchor>
      <arglist>(Teuchos::RCP&lt; MOERTEL::Segment &gt; actseg, MOERTEL::Segment &amp;sseg, MOERTEL::Segment &amp;mseg, Epetra_SerialDenseMatrix **Ddense, Epetra_SerialDenseMatrix **Mdense, MOERTEL::Overlap &amp;overlap, double eps, bool exactvalues)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>Assemble</name>
      <anchorfile>classMOERTEL_1_1Integrator.html</anchorfile>
      <anchor>a22bc51b923d472fa27d5a0eb0d289d9a</anchor>
      <arglist>(MOERTEL::Interface &amp;inter, MOERTEL::Segment &amp;sseg, Epetra_SerialDenseMatrix &amp;Ddense)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>Assemble</name>
      <anchorfile>classMOERTEL_1_1Integrator.html</anchorfile>
      <anchor>a7e59083fb003230d3cfbbb4058e2f7d7</anchor>
      <arglist>(MOERTEL::Interface &amp;inter, MOERTEL::Segment &amp;sseg, MOERTEL::Segment &amp;mseg, Epetra_SerialDenseMatrix &amp;Mdense)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Integrator</name>
      <anchorfile>classMOERTEL_1_1Integrator.html</anchorfile>
      <anchor>a4a7704d5cc75107e8728554eb6d9e9da</anchor>
      <arglist>(int ngp, bool oneD, int outlevel)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~Integrator</name>
      <anchorfile>classMOERTEL_1_1Integrator.html</anchorfile>
      <anchor>a48a3a6135622eb6087800fafa8b4a54b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>OutLevel</name>
      <anchorfile>classMOERTEL_1_1Integrator.html</anchorfile>
      <anchor>af8ea7e58de600e68df11a148a5c9e8af</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Ngp</name>
      <anchorfile>classMOERTEL_1_1Integrator.html</anchorfile>
      <anchor>ae56a72380a3afa68471811eda40d5f3f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>Coordinate</name>
      <anchorfile>classMOERTEL_1_1Integrator.html</anchorfile>
      <anchor>afd63dc0c98fcbada150fbd28b15ae546</anchor>
      <arglist>(int gp)</arglist>
    </member>
    <member kind="function">
      <type>double *</type>
      <name>Coordinate</name>
      <anchorfile>classMOERTEL_1_1Integrator.html</anchorfile>
      <anchor>a9da61f9fbb786faad257a15d6374aa82</anchor>
      <arglist>(int *gp)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>Weight</name>
      <anchorfile>classMOERTEL_1_1Integrator.html</anchorfile>
      <anchor>a57acebf03a9ac2511943e46ae46ca083</anchor>
      <arglist>(int gp)</arglist>
    </member>
    <member kind="function">
      <type>Epetra_SerialDenseMatrix *</type>
      <name>Integrate</name>
      <anchorfile>classMOERTEL_1_1Integrator.html</anchorfile>
      <anchor>a2faed76747fc4b1d0310fa53d80689b7</anchor>
      <arglist>(MOERTEL::Segment &amp;sseg, double sxia, double sxib, MOERTEL::Segment &amp;mseg, double mxia, double mxib)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>Assemble</name>
      <anchorfile>classMOERTEL_1_1Integrator.html</anchorfile>
      <anchor>a130e255785dd9201ea47c36ea6d581d5</anchor>
      <arglist>(MOERTEL::Interface &amp;inter, MOERTEL::Segment &amp;sseg, MOERTEL::Segment &amp;mseg, Epetra_CrsMatrix &amp;M, Epetra_SerialDenseMatrix &amp;Mdense)</arglist>
    </member>
    <member kind="function">
      <type>Epetra_SerialDenseMatrix *</type>
      <name>Integrate</name>
      <anchorfile>classMOERTEL_1_1Integrator.html</anchorfile>
      <anchor>a6cb9458232b327d4301c851629311ee6</anchor>
      <arglist>(MOERTEL::Segment &amp;sseg, double sxia, double sxib)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>Assemble</name>
      <anchorfile>classMOERTEL_1_1Integrator.html</anchorfile>
      <anchor>a63c7a20818b471cbc6d2b4e06fd329e6</anchor>
      <arglist>(MOERTEL::Interface &amp;inter, MOERTEL::Segment &amp;sseg, Epetra_CrsMatrix &amp;D, Epetra_SerialDenseMatrix &amp;Ddense)</arglist>
    </member>
    <member kind="function">
      <type>Epetra_SerialDenseMatrix *</type>
      <name>Integrate_2D_Mmod</name>
      <anchorfile>classMOERTEL_1_1Integrator.html</anchorfile>
      <anchor>a5009f9ba0b9605af96ba722409fa8e01</anchor>
      <arglist>(MOERTEL::Segment &amp;sseg, double sxia, double sxib, MOERTEL::Segment &amp;mseg, double mxia, double mxib)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>Assemble_2D_Mod</name>
      <anchorfile>classMOERTEL_1_1Integrator.html</anchorfile>
      <anchor>a0e17d500b9d45da50afdc4445e016023</anchor>
      <arglist>(MOERTEL::Interface &amp;inter, MOERTEL::Segment &amp;sseg, MOERTEL::Segment &amp;mseg, Epetra_SerialDenseMatrix &amp;Mmod)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>Integrate</name>
      <anchorfile>classMOERTEL_1_1Integrator.html</anchorfile>
      <anchor>aec9f196cd64853ddce55f1eda8abd068</anchor>
      <arglist>(Teuchos::RCP&lt; MOERTEL::Segment &gt; actseg, MOERTEL::Segment &amp;sseg, MOERTEL::Segment &amp;mseg, Epetra_SerialDenseMatrix **Ddense, Epetra_SerialDenseMatrix **Mdense, MOERTEL::Overlap &amp;overlap, double eps, bool exactvalues)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>Assemble</name>
      <anchorfile>classMOERTEL_1_1Integrator.html</anchorfile>
      <anchor>a22bc51b923d472fa27d5a0eb0d289d9a</anchor>
      <arglist>(MOERTEL::Interface &amp;inter, MOERTEL::Segment &amp;sseg, Epetra_SerialDenseMatrix &amp;Ddense)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>Assemble</name>
      <anchorfile>classMOERTEL_1_1Integrator.html</anchorfile>
      <anchor>a7e59083fb003230d3cfbbb4058e2f7d7</anchor>
      <arglist>(MOERTEL::Interface &amp;inter, MOERTEL::Segment &amp;sseg, MOERTEL::Segment &amp;mseg, Epetra_SerialDenseMatrix &amp;Mdense)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>MOERTEL::Interface</name>
    <filename>classMOERTEL_1_1Interface.html</filename>
    <member kind="enumeration">
      <type></type>
      <name>ProjectionType</name>
      <anchorfile>classMOERTEL_1_1Interface.html</anchorfile>
      <anchor>a1ac105ad74aead73814f754e8ab35507</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Interface</name>
      <anchorfile>classMOERTEL_1_1Interface.html</anchorfile>
      <anchor>a9c9ac1cd7010fbd158fc32ece93958b5</anchor>
      <arglist>(int Id, bool oneD, Epetra_Comm &amp;comm, int outlevel)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Interface</name>
      <anchorfile>classMOERTEL_1_1Interface.html</anchorfile>
      <anchor>a9e9f9525e39efcf7e4ab8cab8706143a</anchor>
      <arglist>(MOERTEL::Interface &amp;old)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~Interface</name>
      <anchorfile>classMOERTEL_1_1Interface.html</anchorfile>
      <anchor>a8a6fbb43f130990a1511409dad80ec5f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>OutLevel</name>
      <anchorfile>classMOERTEL_1_1Interface.html</anchorfile>
      <anchor>a32f0f4810570cf8fce62e20b233f9c82</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>IsOneDimensional</name>
      <anchorfile>classMOERTEL_1_1Interface.html</anchorfile>
      <anchor>ab868199b6be6bd6c3a067134b84310ab</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>Print</name>
      <anchorfile>classMOERTEL_1_1Interface.html</anchorfile>
      <anchor>a461bc5eeab1a7d6ef23c0c5c1f1a313f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>IsComplete</name>
      <anchorfile>classMOERTEL_1_1Interface.html</anchorfile>
      <anchor>ae58b91d9230cd8535076d637fa87c391</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>IsIntegrated</name>
      <anchorfile>classMOERTEL_1_1Interface.html</anchorfile>
      <anchor>ad587b665efe9450f288f811822d61c49</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Id</name>
      <anchorfile>classMOERTEL_1_1Interface.html</anchorfile>
      <anchor>aa8c138614fc1c08d0fdc7163efd73ffe</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_Comm &amp;</type>
      <name>gComm</name>
      <anchorfile>classMOERTEL_1_1Interface.html</anchorfile>
      <anchor>adfa64f0946bbd0cb9f7c23f43865dfaa</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_Comm *</type>
      <name>lComm</name>
      <anchorfile>classMOERTEL_1_1Interface.html</anchorfile>
      <anchor>aec0ee4817bc6a0215c9a3e4a41dd8310</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>MortarSide</name>
      <anchorfile>classMOERTEL_1_1Interface.html</anchorfile>
      <anchor>a6fbb7587062e0f06b4241860009f41d4</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>OtherSide</name>
      <anchorfile>classMOERTEL_1_1Interface.html</anchorfile>
      <anchor>afffa2840081af9a867601f2a54e7d106</anchor>
      <arglist>(int side) const </arglist>
    </member>
    <member kind="function">
      <type>ProjectionType</type>
      <name>GetProjectionType</name>
      <anchorfile>classMOERTEL_1_1Interface.html</anchorfile>
      <anchor>a55ba92904a1cc22d3f29a2fad68bee79</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetSide</name>
      <anchorfile>classMOERTEL_1_1Interface.html</anchorfile>
      <anchor>a136c33efb54832eba4b1226ec19f0844</anchor>
      <arglist>(MOERTEL::Segment *seg)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetSide</name>
      <anchorfile>classMOERTEL_1_1Interface.html</anchorfile>
      <anchor>af79518202f291766beef7e3f073e930a</anchor>
      <arglist>(MOERTEL::Node *node)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetSide</name>
      <anchorfile>classMOERTEL_1_1Interface.html</anchorfile>
      <anchor>a998d2271d11bfe8829f92a2260411f1a</anchor>
      <arglist>(int nodeid)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>MyNsegment</name>
      <anchorfile>classMOERTEL_1_1Interface.html</anchorfile>
      <anchor>a4bfd23b82b1a1e4f705039008d05e0ab</anchor>
      <arglist>(int side)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GlobalNsegment</name>
      <anchorfile>classMOERTEL_1_1Interface.html</anchorfile>
      <anchor>a205856eff5faf68920eae724a247b7b2</anchor>
      <arglist>(int side)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>MyNsegment</name>
      <anchorfile>classMOERTEL_1_1Interface.html</anchorfile>
      <anchor>a97f0c8ca11e80a6b3b80fb2417c87eaa</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GlobalNsegment</name>
      <anchorfile>classMOERTEL_1_1Interface.html</anchorfile>
      <anchor>a2ebc6cfe940015f15567a1b6d39fdf64</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>MyNnode</name>
      <anchorfile>classMOERTEL_1_1Interface.html</anchorfile>
      <anchor>a166f5d03bf85eb9eed8bc6ff92d93c89</anchor>
      <arglist>(int side)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>MyNnode</name>
      <anchorfile>classMOERTEL_1_1Interface.html</anchorfile>
      <anchor>a892a218e302bb14205d892f71ae04f51</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GlobalNnode</name>
      <anchorfile>classMOERTEL_1_1Interface.html</anchorfile>
      <anchor>a867faf795ff77c868c5ced7705adf4ac</anchor>
      <arglist>(int side)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GlobalNnode</name>
      <anchorfile>classMOERTEL_1_1Interface.html</anchorfile>
      <anchor>a36595d4a416c9e19755454176d0d1cce</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NodePID</name>
      <anchorfile>classMOERTEL_1_1Interface.html</anchorfile>
      <anchor>a48713779a33020cd9aa05c08ab883009</anchor>
      <arglist>(int nid) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SegPID</name>
      <anchorfile>classMOERTEL_1_1Interface.html</anchorfile>
      <anchor>ae108cb55a3dde1e40f0ce7495841322f</anchor>
      <arglist>(int sid) const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; MOERTEL::Node &gt;</type>
      <name>GetNodeView</name>
      <anchorfile>classMOERTEL_1_1Interface.html</anchorfile>
      <anchor>a4f61b687dfb2634a10c073a8fff578d3</anchor>
      <arglist>(int nid)</arglist>
    </member>
    <member kind="function">
      <type>MOERTEL::Node **</type>
      <name>GetNodeView</name>
      <anchorfile>classMOERTEL_1_1Interface.html</anchorfile>
      <anchor>a174baa3db594adb5e528daf16716b2de</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>GetNodeView</name>
      <anchorfile>classMOERTEL_1_1Interface.html</anchorfile>
      <anchor>a2371d619147d6ade93967d0445c2f5c3</anchor>
      <arglist>(std::vector&lt; MOERTEL::Node * &gt; &amp;nodes)</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; MOERTEL::Segment &gt;</type>
      <name>GetSegmentView</name>
      <anchorfile>classMOERTEL_1_1Interface.html</anchorfile>
      <anchor>a8c47941b32886261e7ce31057f63c033</anchor>
      <arglist>(int sid)</arglist>
    </member>
    <member kind="function">
      <type>MOERTEL::Segment **</type>
      <name>GetSegmentView</name>
      <anchorfile>classMOERTEL_1_1Interface.html</anchorfile>
      <anchor>a51f388f87eb6418fb9aba404248c1c4d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>Complete</name>
      <anchorfile>classMOERTEL_1_1Interface.html</anchorfile>
      <anchor>ac015c8de85586afbecf27ec09d340fa5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>AddSegment</name>
      <anchorfile>classMOERTEL_1_1Interface.html</anchorfile>
      <anchor>aeedde6fb30dbfb6c4e25ee87f0470642</anchor>
      <arglist>(MOERTEL::Segment &amp;seg, int side)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>AddNode</name>
      <anchorfile>classMOERTEL_1_1Interface.html</anchorfile>
      <anchor>a8e5d2daea474a8239e3988c670cc1a89</anchor>
      <arglist>(MOERTEL::Node &amp;node, int side)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>SetMortarSide</name>
      <anchorfile>classMOERTEL_1_1Interface.html</anchorfile>
      <anchor>a897954d9e2b02c2f728ca1c68a514a0d</anchor>
      <arglist>(int side)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>SetFunctionAllSegmentsSide</name>
      <anchorfile>classMOERTEL_1_1Interface.html</anchorfile>
      <anchor>acdcd75a1c41989cbd0dd38e3a55fa26d</anchor>
      <arglist>(int side, int id, MOERTEL::Function *func)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>Mortar_Integrate_2D</name>
      <anchorfile>classMOERTEL_1_1Interface.html</anchorfile>
      <anchor>ad9f1eb9e225fb0431c2c7cbb4c391b88</anchor>
      <arglist>(Teuchos::RCP&lt; Teuchos::ParameterList &gt; intparams)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>Mortar_Integrate</name>
      <anchorfile>classMOERTEL_1_1Interface.html</anchorfile>
      <anchor>a8e7de54ba2508e9d71e2320ae58568db</anchor>
      <arglist>(Teuchos::RCP&lt; Teuchos::ParameterList &gt; intparams)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>Mortar_Assemble</name>
      <anchorfile>classMOERTEL_1_1Interface.html</anchorfile>
      <anchor>ae07dd17da7109b3361984321431d9f18</anchor>
      <arglist>(Epetra_CrsMatrix &amp;D, Epetra_CrsMatrix &amp;M)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetProjectionType</name>
      <anchorfile>classMOERTEL_1_1Interface.html</anchorfile>
      <anchor>a24abcd3af10c17d9156e1facc4dd73d8</anchor>
      <arglist>(MOERTEL::Interface::ProjectionType typ)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>Project</name>
      <anchorfile>classMOERTEL_1_1Interface.html</anchorfile>
      <anchor>a773616d6b4396e39a1bfb68e5f23c403</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>BuildNormals</name>
      <anchorfile>classMOERTEL_1_1Interface.html</anchorfile>
      <anchor>ae89e40c818bae9f39693d1ffe2e96e8d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetLMDofs</name>
      <anchorfile>classMOERTEL_1_1Interface.html</anchorfile>
      <anchor>a073e8e54c0ec22cbb4057c4ba5e5ae3e</anchor>
      <arglist>(int minLMGID)</arglist>
    </member>
    <member kind="function">
      <type>std::vector&lt; int &gt; *</type>
      <name>MyLMIds</name>
      <anchorfile>classMOERTEL_1_1Interface.html</anchorfile>
      <anchor>ab093f8b3516ac0aed031a723e3465775</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>DetectEndSegmentsandReduceOrder</name>
      <anchorfile>classMOERTEL_1_1Interface.html</anchorfile>
      <anchor>a61a679e2a6bfed6d4032e009aec628b8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>SetFunctionTypes</name>
      <anchorfile>classMOERTEL_1_1Interface.html</anchorfile>
      <anchor>a6bf0ed6e31e0e497f55804a0944d8b72</anchor>
      <arglist>(MOERTEL::Function::FunctionType primal, MOERTEL::Function::FunctionType dual)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>SetFunctionsFromFunctionTypes</name>
      <anchorfile>classMOERTEL_1_1Interface.html</anchorfile>
      <anchor>aff67ed62eeed67b9ee4613492cbe883d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="friend">
      <type>friend class</type>
      <name>Integrator</name>
      <anchorfile>classMOERTEL_1_1Interface.html</anchorfile>
      <anchor>ace5bb0fe4232b9b0ced67ff743994e71</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Interface</name>
      <anchorfile>classMOERTEL_1_1Interface.html</anchorfile>
      <anchor>a9c9ac1cd7010fbd158fc32ece93958b5</anchor>
      <arglist>(int Id, bool oneD, Epetra_Comm &amp;comm, int outlevel)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Interface</name>
      <anchorfile>classMOERTEL_1_1Interface.html</anchorfile>
      <anchor>a9e9f9525e39efcf7e4ab8cab8706143a</anchor>
      <arglist>(MOERTEL::Interface &amp;old)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~Interface</name>
      <anchorfile>classMOERTEL_1_1Interface.html</anchorfile>
      <anchor>a8a6fbb43f130990a1511409dad80ec5f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>OutLevel</name>
      <anchorfile>classMOERTEL_1_1Interface.html</anchorfile>
      <anchor>a32f0f4810570cf8fce62e20b233f9c82</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>IsOneDimensional</name>
      <anchorfile>classMOERTEL_1_1Interface.html</anchorfile>
      <anchor>ab868199b6be6bd6c3a067134b84310ab</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>Print</name>
      <anchorfile>classMOERTEL_1_1Interface.html</anchorfile>
      <anchor>a461bc5eeab1a7d6ef23c0c5c1f1a313f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>IsComplete</name>
      <anchorfile>classMOERTEL_1_1Interface.html</anchorfile>
      <anchor>ae58b91d9230cd8535076d637fa87c391</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>IsIntegrated</name>
      <anchorfile>classMOERTEL_1_1Interface.html</anchorfile>
      <anchor>ad587b665efe9450f288f811822d61c49</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Id</name>
      <anchorfile>classMOERTEL_1_1Interface.html</anchorfile>
      <anchor>aa8c138614fc1c08d0fdc7163efd73ffe</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_Comm &amp;</type>
      <name>gComm</name>
      <anchorfile>classMOERTEL_1_1Interface.html</anchorfile>
      <anchor>adfa64f0946bbd0cb9f7c23f43865dfaa</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_Comm *</type>
      <name>lComm</name>
      <anchorfile>classMOERTEL_1_1Interface.html</anchorfile>
      <anchor>aec0ee4817bc6a0215c9a3e4a41dd8310</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>MortarSide</name>
      <anchorfile>classMOERTEL_1_1Interface.html</anchorfile>
      <anchor>a6fbb7587062e0f06b4241860009f41d4</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>OtherSide</name>
      <anchorfile>classMOERTEL_1_1Interface.html</anchorfile>
      <anchor>afffa2840081af9a867601f2a54e7d106</anchor>
      <arglist>(int side) const </arglist>
    </member>
    <member kind="function">
      <type>ProjectionType</type>
      <name>GetProjectionType</name>
      <anchorfile>classMOERTEL_1_1Interface.html</anchorfile>
      <anchor>a55ba92904a1cc22d3f29a2fad68bee79</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetSide</name>
      <anchorfile>classMOERTEL_1_1Interface.html</anchorfile>
      <anchor>a136c33efb54832eba4b1226ec19f0844</anchor>
      <arglist>(MOERTEL::Segment *seg)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetSide</name>
      <anchorfile>classMOERTEL_1_1Interface.html</anchorfile>
      <anchor>af79518202f291766beef7e3f073e930a</anchor>
      <arglist>(MOERTEL::Node *node)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetSide</name>
      <anchorfile>classMOERTEL_1_1Interface.html</anchorfile>
      <anchor>a998d2271d11bfe8829f92a2260411f1a</anchor>
      <arglist>(int nodeid)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>MyNsegment</name>
      <anchorfile>classMOERTEL_1_1Interface.html</anchorfile>
      <anchor>a4bfd23b82b1a1e4f705039008d05e0ab</anchor>
      <arglist>(int side)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GlobalNsegment</name>
      <anchorfile>classMOERTEL_1_1Interface.html</anchorfile>
      <anchor>a205856eff5faf68920eae724a247b7b2</anchor>
      <arglist>(int side)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>MyNsegment</name>
      <anchorfile>classMOERTEL_1_1Interface.html</anchorfile>
      <anchor>a97f0c8ca11e80a6b3b80fb2417c87eaa</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GlobalNsegment</name>
      <anchorfile>classMOERTEL_1_1Interface.html</anchorfile>
      <anchor>a2ebc6cfe940015f15567a1b6d39fdf64</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>MyNnode</name>
      <anchorfile>classMOERTEL_1_1Interface.html</anchorfile>
      <anchor>a166f5d03bf85eb9eed8bc6ff92d93c89</anchor>
      <arglist>(int side)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>MyNnode</name>
      <anchorfile>classMOERTEL_1_1Interface.html</anchorfile>
      <anchor>a892a218e302bb14205d892f71ae04f51</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GlobalNnode</name>
      <anchorfile>classMOERTEL_1_1Interface.html</anchorfile>
      <anchor>a867faf795ff77c868c5ced7705adf4ac</anchor>
      <arglist>(int side)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GlobalNnode</name>
      <anchorfile>classMOERTEL_1_1Interface.html</anchorfile>
      <anchor>a36595d4a416c9e19755454176d0d1cce</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NodePID</name>
      <anchorfile>classMOERTEL_1_1Interface.html</anchorfile>
      <anchor>a48713779a33020cd9aa05c08ab883009</anchor>
      <arglist>(int nid) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SegPID</name>
      <anchorfile>classMOERTEL_1_1Interface.html</anchorfile>
      <anchor>ae108cb55a3dde1e40f0ce7495841322f</anchor>
      <arglist>(int sid) const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; MOERTEL::Node &gt;</type>
      <name>GetNodeView</name>
      <anchorfile>classMOERTEL_1_1Interface.html</anchorfile>
      <anchor>a4f61b687dfb2634a10c073a8fff578d3</anchor>
      <arglist>(int nid)</arglist>
    </member>
    <member kind="function">
      <type>MOERTEL::Node **</type>
      <name>GetNodeView</name>
      <anchorfile>classMOERTEL_1_1Interface.html</anchorfile>
      <anchor>a174baa3db594adb5e528daf16716b2de</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>GetNodeView</name>
      <anchorfile>classMOERTEL_1_1Interface.html</anchorfile>
      <anchor>a2371d619147d6ade93967d0445c2f5c3</anchor>
      <arglist>(std::vector&lt; MOERTEL::Node * &gt; &amp;nodes)</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; MOERTEL::Segment &gt;</type>
      <name>GetSegmentView</name>
      <anchorfile>classMOERTEL_1_1Interface.html</anchorfile>
      <anchor>a8c47941b32886261e7ce31057f63c033</anchor>
      <arglist>(int sid)</arglist>
    </member>
    <member kind="function">
      <type>MOERTEL::Segment **</type>
      <name>GetSegmentView</name>
      <anchorfile>classMOERTEL_1_1Interface.html</anchorfile>
      <anchor>a51f388f87eb6418fb9aba404248c1c4d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>Complete</name>
      <anchorfile>classMOERTEL_1_1Interface.html</anchorfile>
      <anchor>ac015c8de85586afbecf27ec09d340fa5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>AddSegment</name>
      <anchorfile>classMOERTEL_1_1Interface.html</anchorfile>
      <anchor>aeedde6fb30dbfb6c4e25ee87f0470642</anchor>
      <arglist>(MOERTEL::Segment &amp;seg, int side)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>AddNode</name>
      <anchorfile>classMOERTEL_1_1Interface.html</anchorfile>
      <anchor>a8e5d2daea474a8239e3988c670cc1a89</anchor>
      <arglist>(MOERTEL::Node &amp;node, int side)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>SetMortarSide</name>
      <anchorfile>classMOERTEL_1_1Interface.html</anchorfile>
      <anchor>a897954d9e2b02c2f728ca1c68a514a0d</anchor>
      <arglist>(int side)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>SetFunctionAllSegmentsSide</name>
      <anchorfile>classMOERTEL_1_1Interface.html</anchorfile>
      <anchor>acdcd75a1c41989cbd0dd38e3a55fa26d</anchor>
      <arglist>(int side, int id, MOERTEL::Function *func)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>Mortar_Integrate_2D</name>
      <anchorfile>classMOERTEL_1_1Interface.html</anchorfile>
      <anchor>ad9f1eb9e225fb0431c2c7cbb4c391b88</anchor>
      <arglist>(Teuchos::RCP&lt; Teuchos::ParameterList &gt; intparams)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>Mortar_Integrate</name>
      <anchorfile>classMOERTEL_1_1Interface.html</anchorfile>
      <anchor>a8e7de54ba2508e9d71e2320ae58568db</anchor>
      <arglist>(Teuchos::RCP&lt; Teuchos::ParameterList &gt; intparams)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>Mortar_Assemble</name>
      <anchorfile>classMOERTEL_1_1Interface.html</anchorfile>
      <anchor>ae07dd17da7109b3361984321431d9f18</anchor>
      <arglist>(Epetra_CrsMatrix &amp;D, Epetra_CrsMatrix &amp;M)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetProjectionType</name>
      <anchorfile>classMOERTEL_1_1Interface.html</anchorfile>
      <anchor>a24abcd3af10c17d9156e1facc4dd73d8</anchor>
      <arglist>(MOERTEL::Interface::ProjectionType typ)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>Project</name>
      <anchorfile>classMOERTEL_1_1Interface.html</anchorfile>
      <anchor>a773616d6b4396e39a1bfb68e5f23c403</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>BuildNormals</name>
      <anchorfile>classMOERTEL_1_1Interface.html</anchorfile>
      <anchor>ae89e40c818bae9f39693d1ffe2e96e8d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetLMDofs</name>
      <anchorfile>classMOERTEL_1_1Interface.html</anchorfile>
      <anchor>a073e8e54c0ec22cbb4057c4ba5e5ae3e</anchor>
      <arglist>(int minLMGID)</arglist>
    </member>
    <member kind="function">
      <type>std::vector&lt; int &gt; *</type>
      <name>MyLMIds</name>
      <anchorfile>classMOERTEL_1_1Interface.html</anchorfile>
      <anchor>ab093f8b3516ac0aed031a723e3465775</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>DetectEndSegmentsandReduceOrder</name>
      <anchorfile>classMOERTEL_1_1Interface.html</anchorfile>
      <anchor>a61a679e2a6bfed6d4032e009aec628b8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>SetFunctionTypes</name>
      <anchorfile>classMOERTEL_1_1Interface.html</anchorfile>
      <anchor>a6bf0ed6e31e0e497f55804a0944d8b72</anchor>
      <arglist>(MOERTEL::Function::FunctionType primal, MOERTEL::Function::FunctionType dual)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>SetFunctionsFromFunctionTypes</name>
      <anchorfile>classMOERTEL_1_1Interface.html</anchorfile>
      <anchor>aff67ed62eeed67b9ee4613492cbe883d</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>MOERTEL::Lmselector</name>
    <filename>classMOERTEL_1_1Lmselector.html</filename>
    <member kind="function">
      <type></type>
      <name>Lmselector</name>
      <anchorfile>classMOERTEL_1_1Lmselector.html</anchorfile>
      <anchor>a3a7e0750e7a858869d8bbdd604c86190</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Lmselector</name>
      <anchorfile>classMOERTEL_1_1Lmselector.html</anchorfile>
      <anchor>a1c09be132ff8927e4ab740b7c47cdfad</anchor>
      <arglist>(const MOERTEL::Lmselector &amp;old)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~Lmselector</name>
      <anchorfile>classMOERTEL_1_1Lmselector.html</anchorfile>
      <anchor>a90502e9cd2dd2384cdf1a9d67ada7643</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>EvaluateLM</name>
      <anchorfile>classMOERTEL_1_1Lmselector.html</anchorfile>
      <anchor>a950a55625ba1210d8ee908c0cfc49407</anchor>
      <arglist>(Teuchos::RCP&lt; MOERTEL::Node &gt; node, const int LMDof)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>AccumulateRHS</name>
      <anchorfile>classMOERTEL_1_1Lmselector.html</anchorfile>
      <anchor>a6a95678c946b83e6027b5b6abec612fb</anchor>
      <arglist>(Teuchos::RCP&lt; MOERTEL::Node &gt; node)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>AssembleNodeVal</name>
      <anchorfile>classMOERTEL_1_1Lmselector.html</anchorfile>
      <anchor>a65b2f9bbf73ac89e674ba88e392387cf</anchor>
      <arglist>(int row, int col, double val)=0</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Lmselector</name>
      <anchorfile>classMOERTEL_1_1Lmselector.html</anchorfile>
      <anchor>a3a7e0750e7a858869d8bbdd604c86190</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Lmselector</name>
      <anchorfile>classMOERTEL_1_1Lmselector.html</anchorfile>
      <anchor>a1c09be132ff8927e4ab740b7c47cdfad</anchor>
      <arglist>(const MOERTEL::Lmselector &amp;old)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~Lmselector</name>
      <anchorfile>classMOERTEL_1_1Lmselector.html</anchorfile>
      <anchor>a90502e9cd2dd2384cdf1a9d67ada7643</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>EvaluateLM</name>
      <anchorfile>classMOERTEL_1_1Lmselector.html</anchorfile>
      <anchor>a950a55625ba1210d8ee908c0cfc49407</anchor>
      <arglist>(Teuchos::RCP&lt; MOERTEL::Node &gt; node, const int LMDof)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>AccumulateRHS</name>
      <anchorfile>classMOERTEL_1_1Lmselector.html</anchorfile>
      <anchor>a6a95678c946b83e6027b5b6abec612fb</anchor>
      <arglist>(Teuchos::RCP&lt; MOERTEL::Node &gt; node)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>AssembleNodeVal</name>
      <anchorfile>classMOERTEL_1_1Lmselector.html</anchorfile>
      <anchor>a65b2f9bbf73ac89e674ba88e392387cf</anchor>
      <arglist>(int row, int col, double val)=0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>MOERTEL::Manager</name>
    <filename>classMOERTEL_1_1Manager.html</filename>
    <member kind="enumeration">
      <type></type>
      <name>DimensionType</name>
      <anchorfile>classMOERTEL_1_1Manager.html</anchorfile>
      <anchor>ad9d1e07dbc55ed792595af2fd163355d</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Manager</name>
      <anchorfile>classMOERTEL_1_1Manager.html</anchorfile>
      <anchor>af469287fa83a3d07d4efec3d55c09db8</anchor>
      <arglist>(Epetra_Comm &amp;comm, MOERTEL::Manager::DimensionType dimension, int outlevel)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Manager</name>
      <anchorfile>classMOERTEL_1_1Manager.html</anchorfile>
      <anchor>a5db9e95952ad87d6d7e3c5bde1907c58</anchor>
      <arglist>(Epetra_Comm &amp;comm, int outlevel)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~Manager</name>
      <anchorfile>classMOERTEL_1_1Manager.html</anchorfile>
      <anchor>a6db4fcc12d4062e385f90362e6be22a4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Epetra_Comm &amp;</type>
      <name>Comm</name>
      <anchorfile>classMOERTEL_1_1Manager.html</anchorfile>
      <anchor>afbff2cef3bd1c6120fd656ba9f8028d6</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>OutLevel</name>
      <anchorfile>classMOERTEL_1_1Manager.html</anchorfile>
      <anchor>a0ddb91b1eb0e34bf112924cbe5a9e3e4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>MOERTEL::Manager::DimensionType</type>
      <name>Dimension</name>
      <anchorfile>classMOERTEL_1_1Manager.html</anchorfile>
      <anchor>a544d5050782aa2df1a7c0afff9e2233a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Ninterfaces</name>
      <anchorfile>classMOERTEL_1_1Manager.html</anchorfile>
      <anchor>af2976edeb7cb59720d76e10858a209c4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>Print</name>
      <anchorfile>classMOERTEL_1_1Manager.html</anchorfile>
      <anchor>a8e3dcfc6333972889a404f7bbb5bf87b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetDimension</name>
      <anchorfile>classMOERTEL_1_1Manager.html</anchorfile>
      <anchor>a44d1c29b145b899095af8c603851efc6</anchor>
      <arglist>(MOERTEL::Manager::DimensionType type)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>AddInterface</name>
      <anchorfile>classMOERTEL_1_1Manager.html</anchorfile>
      <anchor>a9f95216f9cd51ef43f38796b25ec9cbf</anchor>
      <arglist>(MOERTEL::Interface &amp;interface)</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::ParameterList &amp;</type>
      <name>Default_Parameters</name>
      <anchorfile>classMOERTEL_1_1Manager.html</anchorfile>
      <anchor>aa8a1ea07d4e302b5d297d1c201f47322</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>Mortar_Integrate</name>
      <anchorfile>classMOERTEL_1_1Manager.html</anchorfile>
      <anchor>aee35ebab2e5ace20abbe73847f5f3ac2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>Integrate_Interfaces</name>
      <anchorfile>classMOERTEL_1_1Manager.html</anchorfile>
      <anchor>aca05643d1b443abdea55fb3baf6f9282</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>AssembleInterfacesIntoResidual</name>
      <anchorfile>classMOERTEL_1_1Manager.html</anchorfile>
      <anchor>ab0681a1908c22ec0c18cc6adc82ac89f</anchor>
      <arglist>(Lmselector *sel)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>SetProblemMap</name>
      <anchorfile>classMOERTEL_1_1Manager.html</anchorfile>
      <anchor>ac30d15ab48b912fd44fec3276830021b</anchor>
      <arglist>(const Epetra_Map *map)</arglist>
    </member>
    <member kind="function">
      <type>Epetra_Map *</type>
      <name>ProblemMap</name>
      <anchorfile>classMOERTEL_1_1Manager.html</anchorfile>
      <anchor>afd6673269234678485e2095c7bd0f428</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>SetInputMatrix</name>
      <anchorfile>classMOERTEL_1_1Manager.html</anchorfile>
      <anchor>a64b39680ca67c4e484770f3297fffc12</anchor>
      <arglist>(Epetra_CrsMatrix *inputmatrix, bool DeepCopy=false)</arglist>
    </member>
    <member kind="function">
      <type>Epetra_CrsMatrix *</type>
      <name>MakeSaddleProblem</name>
      <anchorfile>classMOERTEL_1_1Manager.html</anchorfile>
      <anchor>aa714d43eeb3a1bfe87a852ff63dfd0b0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Epetra_CrsMatrix *</type>
      <name>MakeSPDProblem</name>
      <anchorfile>classMOERTEL_1_1Manager.html</anchorfile>
      <anchor>a62022035cc8a74458cea506c4ec30e90</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Epetra_CrsMatrix *</type>
      <name>GetRHSMatrix</name>
      <anchorfile>classMOERTEL_1_1Manager.html</anchorfile>
      <anchor>a774063e4e711cede2872279ddc8a37f9</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetSolverParameters</name>
      <anchorfile>classMOERTEL_1_1Manager.html</anchorfile>
      <anchor>a414afa3e814199f73f438b8930e73011</anchor>
      <arglist>(Teuchos::ParameterList &amp;params)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>Solve</name>
      <anchorfile>classMOERTEL_1_1Manager.html</anchorfile>
      <anchor>a81cbc2177b937cda43e626b4b6ed0e98</anchor>
      <arglist>(Teuchos::ParameterList &amp;params, Epetra_Vector &amp;sol, const Epetra_Vector &amp;rhs)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>Solve</name>
      <anchorfile>classMOERTEL_1_1Manager.html</anchorfile>
      <anchor>a2986d1b7b2201ab1af311597442258da</anchor>
      <arglist>(Epetra_Vector &amp;sol, const Epetra_Vector &amp;rhs)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>ResetSolver</name>
      <anchorfile>classMOERTEL_1_1Manager.html</anchorfile>
      <anchor>ac3680ef229b4012cf8a70310fef32a30</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const Epetra_CrsMatrix *</type>
      <name>D</name>
      <anchorfile>classMOERTEL_1_1Manager.html</anchorfile>
      <anchor>a2afabb76e25b12cafa29cfb558045be5</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_CrsMatrix *</type>
      <name>M</name>
      <anchorfile>classMOERTEL_1_1Manager.html</anchorfile>
      <anchor>a258b142653edc105ba37ce01df8533f7</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; MOERTEL::Interface &gt;</type>
      <name>GetInterface</name>
      <anchorfile>classMOERTEL_1_1Manager.html</anchorfile>
      <anchor>a80066678738b05ed8905148b5333b7ab</anchor>
      <arglist>(int idx)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Manager</name>
      <anchorfile>classMOERTEL_1_1Manager.html</anchorfile>
      <anchor>af469287fa83a3d07d4efec3d55c09db8</anchor>
      <arglist>(Epetra_Comm &amp;comm, MOERTEL::Manager::DimensionType dimension, int outlevel)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Manager</name>
      <anchorfile>classMOERTEL_1_1Manager.html</anchorfile>
      <anchor>a5db9e95952ad87d6d7e3c5bde1907c58</anchor>
      <arglist>(Epetra_Comm &amp;comm, int outlevel)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~Manager</name>
      <anchorfile>classMOERTEL_1_1Manager.html</anchorfile>
      <anchor>a6db4fcc12d4062e385f90362e6be22a4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Epetra_Comm &amp;</type>
      <name>Comm</name>
      <anchorfile>classMOERTEL_1_1Manager.html</anchorfile>
      <anchor>afbff2cef3bd1c6120fd656ba9f8028d6</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>OutLevel</name>
      <anchorfile>classMOERTEL_1_1Manager.html</anchorfile>
      <anchor>a0ddb91b1eb0e34bf112924cbe5a9e3e4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>MOERTEL::Manager::DimensionType</type>
      <name>Dimension</name>
      <anchorfile>classMOERTEL_1_1Manager.html</anchorfile>
      <anchor>a544d5050782aa2df1a7c0afff9e2233a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Ninterfaces</name>
      <anchorfile>classMOERTEL_1_1Manager.html</anchorfile>
      <anchor>af2976edeb7cb59720d76e10858a209c4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>Print</name>
      <anchorfile>classMOERTEL_1_1Manager.html</anchorfile>
      <anchor>a8e3dcfc6333972889a404f7bbb5bf87b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetDimension</name>
      <anchorfile>classMOERTEL_1_1Manager.html</anchorfile>
      <anchor>a44d1c29b145b899095af8c603851efc6</anchor>
      <arglist>(MOERTEL::Manager::DimensionType type)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>AddInterface</name>
      <anchorfile>classMOERTEL_1_1Manager.html</anchorfile>
      <anchor>a9f95216f9cd51ef43f38796b25ec9cbf</anchor>
      <arglist>(MOERTEL::Interface &amp;interface)</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::ParameterList &amp;</type>
      <name>Default_Parameters</name>
      <anchorfile>classMOERTEL_1_1Manager.html</anchorfile>
      <anchor>aa8a1ea07d4e302b5d297d1c201f47322</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>Mortar_Integrate</name>
      <anchorfile>classMOERTEL_1_1Manager.html</anchorfile>
      <anchor>aee35ebab2e5ace20abbe73847f5f3ac2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>Integrate_Interfaces</name>
      <anchorfile>classMOERTEL_1_1Manager.html</anchorfile>
      <anchor>aca05643d1b443abdea55fb3baf6f9282</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>AssembleInterfacesIntoResidual</name>
      <anchorfile>classMOERTEL_1_1Manager.html</anchorfile>
      <anchor>ab0681a1908c22ec0c18cc6adc82ac89f</anchor>
      <arglist>(Lmselector *sel)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>SetProblemMap</name>
      <anchorfile>classMOERTEL_1_1Manager.html</anchorfile>
      <anchor>ac30d15ab48b912fd44fec3276830021b</anchor>
      <arglist>(const Epetra_Map *map)</arglist>
    </member>
    <member kind="function">
      <type>Epetra_Map *</type>
      <name>ProblemMap</name>
      <anchorfile>classMOERTEL_1_1Manager.html</anchorfile>
      <anchor>afd6673269234678485e2095c7bd0f428</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>SetInputMatrix</name>
      <anchorfile>classMOERTEL_1_1Manager.html</anchorfile>
      <anchor>a64b39680ca67c4e484770f3297fffc12</anchor>
      <arglist>(Epetra_CrsMatrix *inputmatrix, bool DeepCopy=false)</arglist>
    </member>
    <member kind="function">
      <type>Epetra_CrsMatrix *</type>
      <name>MakeSaddleProblem</name>
      <anchorfile>classMOERTEL_1_1Manager.html</anchorfile>
      <anchor>aa714d43eeb3a1bfe87a852ff63dfd0b0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Epetra_CrsMatrix *</type>
      <name>MakeSPDProblem</name>
      <anchorfile>classMOERTEL_1_1Manager.html</anchorfile>
      <anchor>a62022035cc8a74458cea506c4ec30e90</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Epetra_CrsMatrix *</type>
      <name>GetRHSMatrix</name>
      <anchorfile>classMOERTEL_1_1Manager.html</anchorfile>
      <anchor>a774063e4e711cede2872279ddc8a37f9</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetSolverParameters</name>
      <anchorfile>classMOERTEL_1_1Manager.html</anchorfile>
      <anchor>a414afa3e814199f73f438b8930e73011</anchor>
      <arglist>(Teuchos::ParameterList &amp;params)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>Solve</name>
      <anchorfile>classMOERTEL_1_1Manager.html</anchorfile>
      <anchor>a81cbc2177b937cda43e626b4b6ed0e98</anchor>
      <arglist>(Teuchos::ParameterList &amp;params, Epetra_Vector &amp;sol, const Epetra_Vector &amp;rhs)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>Solve</name>
      <anchorfile>classMOERTEL_1_1Manager.html</anchorfile>
      <anchor>a2986d1b7b2201ab1af311597442258da</anchor>
      <arglist>(Epetra_Vector &amp;sol, const Epetra_Vector &amp;rhs)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>ResetSolver</name>
      <anchorfile>classMOERTEL_1_1Manager.html</anchorfile>
      <anchor>ac3680ef229b4012cf8a70310fef32a30</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const Epetra_CrsMatrix *</type>
      <name>D</name>
      <anchorfile>classMOERTEL_1_1Manager.html</anchorfile>
      <anchor>a2afabb76e25b12cafa29cfb558045be5</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_CrsMatrix *</type>
      <name>M</name>
      <anchorfile>classMOERTEL_1_1Manager.html</anchorfile>
      <anchor>a258b142653edc105ba37ce01df8533f7</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; MOERTEL::Interface &gt;</type>
      <name>GetInterface</name>
      <anchorfile>classMOERTEL_1_1Manager.html</anchorfile>
      <anchor>a80066678738b05ed8905148b5333b7ab</anchor>
      <arglist>(int idx)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>MOERTEL::Mortar_ML_Preconditioner</name>
    <filename>classMOERTEL_1_1Mortar__ML__Preconditioner.html</filename>
    <member kind="function">
      <type></type>
      <name>Mortar_ML_Preconditioner</name>
      <anchorfile>classMOERTEL_1_1Mortar__ML__Preconditioner.html</anchorfile>
      <anchor>ab4e58eb950da9e68fc30870f562dbe72</anchor>
      <arglist>(Teuchos::RCP&lt; Epetra_CrsMatrix &gt; Atilde, Teuchos::RCP&lt; Epetra_CrsMatrix &gt; A, Teuchos::RCP&lt; Epetra_CrsMatrix &gt; WT, Teuchos::RCP&lt; Epetra_CrsMatrix &gt; B, Teuchos::RCP&lt; Epetra_Map &gt; Annmap, Teuchos::ParameterList &amp;mlparams, bool constructnow=true)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~Mortar_ML_Preconditioner</name>
      <anchorfile>classMOERTEL_1_1Mortar__ML__Preconditioner.html</anchorfile>
      <anchor>a7fa78756ce6081ba4497bee138db88ff</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const char *</type>
      <name>Label</name>
      <anchorfile>classMOERTEL_1_1Mortar__ML__Preconditioner.html</anchorfile>
      <anchor>ad0e3965ff3913f7b3ad76f3b9f30a82c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_Comm &amp;</type>
      <name>Comm</name>
      <anchorfile>classMOERTEL_1_1Mortar__ML__Preconditioner.html</anchorfile>
      <anchor>a92ad769c4f9e28f7fc400581502b59e7</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_Map &amp;</type>
      <name>OperatorDomainMap</name>
      <anchorfile>classMOERTEL_1_1Mortar__ML__Preconditioner.html</anchorfile>
      <anchor>a4f08b67bfa594dbf177781cd461bd341</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_Map &amp;</type>
      <name>OperatorRangeMap</name>
      <anchorfile>classMOERTEL_1_1Mortar__ML__Preconditioner.html</anchorfile>
      <anchor>a70211ee09523533bbe027336d5d89482</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>Compute</name>
      <anchorfile>classMOERTEL_1_1Mortar__ML__Preconditioner.html</anchorfile>
      <anchor>a744695a1ffe32746f9bf9a2edc3003b0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ApplyInverse</name>
      <anchorfile>classMOERTEL_1_1Mortar__ML__Preconditioner.html</anchorfile>
      <anchor>aefad1fd938cf64a11bd6ba9c8329c10f</anchor>
      <arglist>(const Epetra_MultiVector &amp;X, Epetra_MultiVector &amp;Y) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Apply</name>
      <anchorfile>classMOERTEL_1_1Mortar__ML__Preconditioner.html</anchorfile>
      <anchor>ac29e3365aadc1e6bfd80d2419726f90a</anchor>
      <arglist>(const Epetra_MultiVector &amp;X, Epetra_MultiVector &amp;Y) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetUseTranspose</name>
      <anchorfile>classMOERTEL_1_1Mortar__ML__Preconditioner.html</anchorfile>
      <anchor>a9041f696e766482ac443cc3026f4ec16</anchor>
      <arglist>(bool UseTranspose)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>NormInf</name>
      <anchorfile>classMOERTEL_1_1Mortar__ML__Preconditioner.html</anchorfile>
      <anchor>a0c451a071019c29f63216012248e40d9</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>UseTranspose</name>
      <anchorfile>classMOERTEL_1_1Mortar__ML__Preconditioner.html</anchorfile>
      <anchor>aa8deac4538b653bf141bfc5d44f353c5</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>HasNormInf</name>
      <anchorfile>classMOERTEL_1_1Mortar__ML__Preconditioner.html</anchorfile>
      <anchor>a36cd69766fe19de4bd493871e9f129f1</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Mortar_ML_Preconditioner</name>
      <anchorfile>classMOERTEL_1_1Mortar__ML__Preconditioner.html</anchorfile>
      <anchor>ab4e58eb950da9e68fc30870f562dbe72</anchor>
      <arglist>(Teuchos::RCP&lt; Epetra_CrsMatrix &gt; Atilde, Teuchos::RCP&lt; Epetra_CrsMatrix &gt; A, Teuchos::RCP&lt; Epetra_CrsMatrix &gt; WT, Teuchos::RCP&lt; Epetra_CrsMatrix &gt; B, Teuchos::RCP&lt; Epetra_Map &gt; Annmap, Teuchos::ParameterList &amp;mlparams, bool constructnow=true)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~Mortar_ML_Preconditioner</name>
      <anchorfile>classMOERTEL_1_1Mortar__ML__Preconditioner.html</anchorfile>
      <anchor>a7fa78756ce6081ba4497bee138db88ff</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const char *</type>
      <name>Label</name>
      <anchorfile>classMOERTEL_1_1Mortar__ML__Preconditioner.html</anchorfile>
      <anchor>ad0e3965ff3913f7b3ad76f3b9f30a82c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_Comm &amp;</type>
      <name>Comm</name>
      <anchorfile>classMOERTEL_1_1Mortar__ML__Preconditioner.html</anchorfile>
      <anchor>a92ad769c4f9e28f7fc400581502b59e7</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_Map &amp;</type>
      <name>OperatorDomainMap</name>
      <anchorfile>classMOERTEL_1_1Mortar__ML__Preconditioner.html</anchorfile>
      <anchor>a4f08b67bfa594dbf177781cd461bd341</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_Map &amp;</type>
      <name>OperatorRangeMap</name>
      <anchorfile>classMOERTEL_1_1Mortar__ML__Preconditioner.html</anchorfile>
      <anchor>a70211ee09523533bbe027336d5d89482</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>Compute</name>
      <anchorfile>classMOERTEL_1_1Mortar__ML__Preconditioner.html</anchorfile>
      <anchor>a744695a1ffe32746f9bf9a2edc3003b0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ApplyInverse</name>
      <anchorfile>classMOERTEL_1_1Mortar__ML__Preconditioner.html</anchorfile>
      <anchor>aefad1fd938cf64a11bd6ba9c8329c10f</anchor>
      <arglist>(const Epetra_MultiVector &amp;X, Epetra_MultiVector &amp;Y) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Apply</name>
      <anchorfile>classMOERTEL_1_1Mortar__ML__Preconditioner.html</anchorfile>
      <anchor>ac29e3365aadc1e6bfd80d2419726f90a</anchor>
      <arglist>(const Epetra_MultiVector &amp;X, Epetra_MultiVector &amp;Y) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetUseTranspose</name>
      <anchorfile>classMOERTEL_1_1Mortar__ML__Preconditioner.html</anchorfile>
      <anchor>a9041f696e766482ac443cc3026f4ec16</anchor>
      <arglist>(bool UseTranspose)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>NormInf</name>
      <anchorfile>classMOERTEL_1_1Mortar__ML__Preconditioner.html</anchorfile>
      <anchor>a0c451a071019c29f63216012248e40d9</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>UseTranspose</name>
      <anchorfile>classMOERTEL_1_1Mortar__ML__Preconditioner.html</anchorfile>
      <anchor>aa8deac4538b653bf141bfc5d44f353c5</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>HasNormInf</name>
      <anchorfile>classMOERTEL_1_1Mortar__ML__Preconditioner.html</anchorfile>
      <anchor>a36cd69766fe19de4bd493871e9f129f1</anchor>
      <arglist>() const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>MOERTEL::Node</name>
    <filename>classMOERTEL_1_1Node.html</filename>
    <member kind="function">
      <type></type>
      <name>Node</name>
      <anchorfile>classMOERTEL_1_1Node.html</anchorfile>
      <anchor>a69a95249630352e1236cec0d813de46d</anchor>
      <arglist>(int Id, const double *x, int ndof, const int *dof, bool isonboundary, int out)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Node</name>
      <anchorfile>classMOERTEL_1_1Node.html</anchorfile>
      <anchor>af1c3be0eca2a078a9df8373b5a439899</anchor>
      <arglist>(int out)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Node</name>
      <anchorfile>classMOERTEL_1_1Node.html</anchorfile>
      <anchor>a4c03818815c9ea716b174c5c4853c927</anchor>
      <arglist>(const MOERTEL::Node &amp;old)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~Node</name>
      <anchorfile>classMOERTEL_1_1Node.html</anchorfile>
      <anchor>a29b73002bd38d94d3714dbc51e0de6eb</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>OutLevel</name>
      <anchorfile>classMOERTEL_1_1Node.html</anchorfile>
      <anchor>aeed660e8e22a9c8d5c86faf8f7782650</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Id</name>
      <anchorfile>classMOERTEL_1_1Node.html</anchorfile>
      <anchor>aeee578cfadb8fefc2e55e7bbc91563ce</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>Print</name>
      <anchorfile>classMOERTEL_1_1Node.html</anchorfile>
      <anchor>a1c3c828cb77f0a5ceb1ce8e652582b17</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Reset</name>
      <anchorfile>classMOERTEL_1_1Node.html</anchorfile>
      <anchor>a81ce3d38251ca11af3020d8b0864b76b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const double *</type>
      <name>X</name>
      <anchorfile>classMOERTEL_1_1Node.html</anchorfile>
      <anchor>a31753898196fe24ed588de8521d53b01</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>SetX</name>
      <anchorfile>classMOERTEL_1_1Node.html</anchorfile>
      <anchor>a7238e4ba1c013b25ac01bd11893f8bbc</anchor>
      <arglist>(double *x)</arglist>
    </member>
    <member kind="function">
      <type>const double *</type>
      <name>N</name>
      <anchorfile>classMOERTEL_1_1Node.html</anchorfile>
      <anchor>a5f06d8da54e642c6b73fce93399fd431</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>SetN</name>
      <anchorfile>classMOERTEL_1_1Node.html</anchorfile>
      <anchor>a6c998a513a1703cebab7412d1f298aba</anchor>
      <arglist>(double *n)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Ndof</name>
      <anchorfile>classMOERTEL_1_1Node.html</anchorfile>
      <anchor>a0e5bcec4b7b282f9c7514a109750681b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Nlmdof</name>
      <anchorfile>classMOERTEL_1_1Node.html</anchorfile>
      <anchor>a686fa9201e2fd0d40568615ac197f540</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const int *</type>
      <name>Dof</name>
      <anchorfile>classMOERTEL_1_1Node.html</anchorfile>
      <anchor>a14fc0e8fe693fd71cc2cf0661f435fc4</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const int *</type>
      <name>LMDof</name>
      <anchorfile>classMOERTEL_1_1Node.html</anchorfile>
      <anchor>a93b65e8cc598771c95434feb99549306</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Nseg</name>
      <anchorfile>classMOERTEL_1_1Node.html</anchorfile>
      <anchor>a8d5e9c827742812c3f9d822dae08768a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int *</type>
      <name>SegmentIds</name>
      <anchorfile>classMOERTEL_1_1Node.html</anchorfile>
      <anchor>aaa7d1724361b13174db6592e046d0c36</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>MOERTEL::Segment **</type>
      <name>Segments</name>
      <anchorfile>classMOERTEL_1_1Node.html</anchorfile>
      <anchor>a216cc677711e535c64caa7d0d8c6f953</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>AddSegment</name>
      <anchorfile>classMOERTEL_1_1Node.html</anchorfile>
      <anchor>ae0caae84eae94ef1ece21d86f36120a9</anchor>
      <arglist>(int sid)</arglist>
    </member>
    <member kind="function">
      <type>double *</type>
      <name>Pack</name>
      <anchorfile>classMOERTEL_1_1Node.html</anchorfile>
      <anchor>ab405029ece0eadf346b75c08d3325334</anchor>
      <arglist>(int *size)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>UnPack</name>
      <anchorfile>classMOERTEL_1_1Node.html</anchorfile>
      <anchor>aa8ea276b4ba7bf3c8ca78a11e5d111ec</anchor>
      <arglist>(double *pack)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>BuildAveragedNormal</name>
      <anchorfile>classMOERTEL_1_1Node.html</anchorfile>
      <anchor>ae66c5efbdf4eafac41015f649535fdd0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>GetPtrstoSegments</name>
      <anchorfile>classMOERTEL_1_1Node.html</anchorfile>
      <anchor>a0efc8f7f1e56a877ce5d67428850bcac</anchor>
      <arglist>(MOERTEL::Interface &amp;interface)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>SetProjectedNode</name>
      <anchorfile>classMOERTEL_1_1Node.html</anchorfile>
      <anchor>a074e788852e6de9332c7fdabe1ddcc17</anchor>
      <arglist>(MOERTEL::ProjectedNode *pnode)</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; MOERTEL::ProjectedNode &gt; *</type>
      <name>GetProjectedNode</name>
      <anchorfile>classMOERTEL_1_1Node.html</anchorfile>
      <anchor>acc3ace27417138c9c2597bd2153b6823</anchor>
      <arglist>(int &amp;length)</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; MOERTEL::ProjectedNode &gt;</type>
      <name>GetProjectedNode</name>
      <anchorfile>classMOERTEL_1_1Node.html</anchorfile>
      <anchor>a11faef583920450639a73fad6df52b93</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>SetLagrangeMultiplierId</name>
      <anchorfile>classMOERTEL_1_1Node.html</anchorfile>
      <anchor>a36e73ad8a19424247754f510b281bef2</anchor>
      <arglist>(int LMId)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>AddDValue</name>
      <anchorfile>classMOERTEL_1_1Node.html</anchorfile>
      <anchor>a69c7c4542ff1599505dd22c0f7f3fb69</anchor>
      <arglist>(double val, int col)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>AddMValue</name>
      <anchorfile>classMOERTEL_1_1Node.html</anchorfile>
      <anchor>ae502d24c8f9e00975c468ed2a3fab8ed</anchor>
      <arglist>(double val, int col)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>AddMmodValue</name>
      <anchorfile>classMOERTEL_1_1Node.html</anchorfile>
      <anchor>a5f31fab9f7251d8c8e14e6b422b15c1f</anchor>
      <arglist>(int row, double val, int col)</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; std::map&lt; int, double &gt; &gt;</type>
      <name>GetD</name>
      <anchorfile>classMOERTEL_1_1Node.html</anchorfile>
      <anchor>a7b133f17a18f1ffea0020bb31f415007</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; std::map&lt; int, double &gt; &gt;</type>
      <name>GetM</name>
      <anchorfile>classMOERTEL_1_1Node.html</anchorfile>
      <anchor>a09ba9f87072cd75c5459b559a6c9b595</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; std::vector&lt; std::map&lt; int, double &gt; &gt; &gt;</type>
      <name>GetMmod</name>
      <anchorfile>classMOERTEL_1_1Node.html</anchorfile>
      <anchor>a8c3384a3bc0335d7a4d1a02130da1178</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetCorner</name>
      <anchorfile>classMOERTEL_1_1Node.html</anchorfile>
      <anchor>ad0b9be2b1c6185c3deae21f3e51d2e9e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>IsCorner</name>
      <anchorfile>classMOERTEL_1_1Node.html</anchorfile>
      <anchor>aee52e4deda6b81b5ddb32646867edb8f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>IsOnBoundary</name>
      <anchorfile>classMOERTEL_1_1Node.html</anchorfile>
      <anchor>ae9e804028dbbc74440d13d31654dfa84</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NSupportSet</name>
      <anchorfile>classMOERTEL_1_1Node.html</anchorfile>
      <anchor>af75d9e167a59122245945dd73e51a1f3</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>AddSupportedByNode</name>
      <anchorfile>classMOERTEL_1_1Node.html</anchorfile>
      <anchor>ad916d7e7cc3d8ea78ffe53b484e2be91</anchor>
      <arglist>(MOERTEL::Node *suppnode)</arglist>
    </member>
    <member kind="function">
      <type>std::map&lt; int, MOERTEL::Node * &gt; &amp;</type>
      <name>GetSupportedByNode</name>
      <anchorfile>classMOERTEL_1_1Node.html</anchorfile>
      <anchor>af776248034fea05ffc0d4ef3051b199b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>Gap</name>
      <anchorfile>classMOERTEL_1_1Node.html</anchorfile>
      <anchor>a96ae62fd419c3c7e3e47b63eb8d9c38a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetGap</name>
      <anchorfile>classMOERTEL_1_1Node.html</anchorfile>
      <anchor>a42674d61e4f689e5fcca3c43277f458e</anchor>
      <arglist>(double gap)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Node</name>
      <anchorfile>classMOERTEL_1_1Node.html</anchorfile>
      <anchor>a69a95249630352e1236cec0d813de46d</anchor>
      <arglist>(int Id, const double *x, int ndof, const int *dof, bool isonboundary, int out)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Node</name>
      <anchorfile>classMOERTEL_1_1Node.html</anchorfile>
      <anchor>af1c3be0eca2a078a9df8373b5a439899</anchor>
      <arglist>(int out)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Node</name>
      <anchorfile>classMOERTEL_1_1Node.html</anchorfile>
      <anchor>a4c03818815c9ea716b174c5c4853c927</anchor>
      <arglist>(const MOERTEL::Node &amp;old)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~Node</name>
      <anchorfile>classMOERTEL_1_1Node.html</anchorfile>
      <anchor>a29b73002bd38d94d3714dbc51e0de6eb</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>OutLevel</name>
      <anchorfile>classMOERTEL_1_1Node.html</anchorfile>
      <anchor>aeed660e8e22a9c8d5c86faf8f7782650</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Id</name>
      <anchorfile>classMOERTEL_1_1Node.html</anchorfile>
      <anchor>aeee578cfadb8fefc2e55e7bbc91563ce</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>Print</name>
      <anchorfile>classMOERTEL_1_1Node.html</anchorfile>
      <anchor>a1c3c828cb77f0a5ceb1ce8e652582b17</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Reset</name>
      <anchorfile>classMOERTEL_1_1Node.html</anchorfile>
      <anchor>a81ce3d38251ca11af3020d8b0864b76b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const double *</type>
      <name>X</name>
      <anchorfile>classMOERTEL_1_1Node.html</anchorfile>
      <anchor>a31753898196fe24ed588de8521d53b01</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>SetX</name>
      <anchorfile>classMOERTEL_1_1Node.html</anchorfile>
      <anchor>a7238e4ba1c013b25ac01bd11893f8bbc</anchor>
      <arglist>(double *x)</arglist>
    </member>
    <member kind="function">
      <type>const double *</type>
      <name>N</name>
      <anchorfile>classMOERTEL_1_1Node.html</anchorfile>
      <anchor>a5f06d8da54e642c6b73fce93399fd431</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>SetN</name>
      <anchorfile>classMOERTEL_1_1Node.html</anchorfile>
      <anchor>a6c998a513a1703cebab7412d1f298aba</anchor>
      <arglist>(double *n)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Ndof</name>
      <anchorfile>classMOERTEL_1_1Node.html</anchorfile>
      <anchor>a0e5bcec4b7b282f9c7514a109750681b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Nlmdof</name>
      <anchorfile>classMOERTEL_1_1Node.html</anchorfile>
      <anchor>a686fa9201e2fd0d40568615ac197f540</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const int *</type>
      <name>Dof</name>
      <anchorfile>classMOERTEL_1_1Node.html</anchorfile>
      <anchor>a14fc0e8fe693fd71cc2cf0661f435fc4</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const int *</type>
      <name>LMDof</name>
      <anchorfile>classMOERTEL_1_1Node.html</anchorfile>
      <anchor>a93b65e8cc598771c95434feb99549306</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Nseg</name>
      <anchorfile>classMOERTEL_1_1Node.html</anchorfile>
      <anchor>a8d5e9c827742812c3f9d822dae08768a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int *</type>
      <name>SegmentIds</name>
      <anchorfile>classMOERTEL_1_1Node.html</anchorfile>
      <anchor>aaa7d1724361b13174db6592e046d0c36</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>MOERTEL::Segment **</type>
      <name>Segments</name>
      <anchorfile>classMOERTEL_1_1Node.html</anchorfile>
      <anchor>a216cc677711e535c64caa7d0d8c6f953</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>AddSegment</name>
      <anchorfile>classMOERTEL_1_1Node.html</anchorfile>
      <anchor>ae0caae84eae94ef1ece21d86f36120a9</anchor>
      <arglist>(int sid)</arglist>
    </member>
    <member kind="function">
      <type>double *</type>
      <name>Pack</name>
      <anchorfile>classMOERTEL_1_1Node.html</anchorfile>
      <anchor>ab405029ece0eadf346b75c08d3325334</anchor>
      <arglist>(int *size)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>UnPack</name>
      <anchorfile>classMOERTEL_1_1Node.html</anchorfile>
      <anchor>aa8ea276b4ba7bf3c8ca78a11e5d111ec</anchor>
      <arglist>(double *pack)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>BuildAveragedNormal</name>
      <anchorfile>classMOERTEL_1_1Node.html</anchorfile>
      <anchor>ae66c5efbdf4eafac41015f649535fdd0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>GetPtrstoSegments</name>
      <anchorfile>classMOERTEL_1_1Node.html</anchorfile>
      <anchor>a0efc8f7f1e56a877ce5d67428850bcac</anchor>
      <arglist>(MOERTEL::Interface &amp;interface)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>SetProjectedNode</name>
      <anchorfile>classMOERTEL_1_1Node.html</anchorfile>
      <anchor>a074e788852e6de9332c7fdabe1ddcc17</anchor>
      <arglist>(MOERTEL::ProjectedNode *pnode)</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; MOERTEL::ProjectedNode &gt; *</type>
      <name>GetProjectedNode</name>
      <anchorfile>classMOERTEL_1_1Node.html</anchorfile>
      <anchor>acc3ace27417138c9c2597bd2153b6823</anchor>
      <arglist>(int &amp;length)</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; MOERTEL::ProjectedNode &gt;</type>
      <name>GetProjectedNode</name>
      <anchorfile>classMOERTEL_1_1Node.html</anchorfile>
      <anchor>a11faef583920450639a73fad6df52b93</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>SetLagrangeMultiplierId</name>
      <anchorfile>classMOERTEL_1_1Node.html</anchorfile>
      <anchor>a36e73ad8a19424247754f510b281bef2</anchor>
      <arglist>(int LMId)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>AddDValue</name>
      <anchorfile>classMOERTEL_1_1Node.html</anchorfile>
      <anchor>a69c7c4542ff1599505dd22c0f7f3fb69</anchor>
      <arglist>(double val, int col)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>AddMValue</name>
      <anchorfile>classMOERTEL_1_1Node.html</anchorfile>
      <anchor>ae502d24c8f9e00975c468ed2a3fab8ed</anchor>
      <arglist>(double val, int col)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>AddMmodValue</name>
      <anchorfile>classMOERTEL_1_1Node.html</anchorfile>
      <anchor>a5f31fab9f7251d8c8e14e6b422b15c1f</anchor>
      <arglist>(int row, double val, int col)</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; std::map&lt; int, double &gt; &gt;</type>
      <name>GetD</name>
      <anchorfile>classMOERTEL_1_1Node.html</anchorfile>
      <anchor>a7b133f17a18f1ffea0020bb31f415007</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; std::map&lt; int, double &gt; &gt;</type>
      <name>GetM</name>
      <anchorfile>classMOERTEL_1_1Node.html</anchorfile>
      <anchor>a09ba9f87072cd75c5459b559a6c9b595</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; std::vector&lt; std::map&lt; int, double &gt; &gt; &gt;</type>
      <name>GetMmod</name>
      <anchorfile>classMOERTEL_1_1Node.html</anchorfile>
      <anchor>a8c3384a3bc0335d7a4d1a02130da1178</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetCorner</name>
      <anchorfile>classMOERTEL_1_1Node.html</anchorfile>
      <anchor>ad0b9be2b1c6185c3deae21f3e51d2e9e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>IsCorner</name>
      <anchorfile>classMOERTEL_1_1Node.html</anchorfile>
      <anchor>aee52e4deda6b81b5ddb32646867edb8f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>IsOnBoundary</name>
      <anchorfile>classMOERTEL_1_1Node.html</anchorfile>
      <anchor>ae9e804028dbbc74440d13d31654dfa84</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NSupportSet</name>
      <anchorfile>classMOERTEL_1_1Node.html</anchorfile>
      <anchor>af75d9e167a59122245945dd73e51a1f3</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>AddSupportedByNode</name>
      <anchorfile>classMOERTEL_1_1Node.html</anchorfile>
      <anchor>ad916d7e7cc3d8ea78ffe53b484e2be91</anchor>
      <arglist>(MOERTEL::Node *suppnode)</arglist>
    </member>
    <member kind="function">
      <type>std::map&lt; int, MOERTEL::Node * &gt; &amp;</type>
      <name>GetSupportedByNode</name>
      <anchorfile>classMOERTEL_1_1Node.html</anchorfile>
      <anchor>af776248034fea05ffc0d4ef3051b199b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>Gap</name>
      <anchorfile>classMOERTEL_1_1Node.html</anchorfile>
      <anchor>a96ae62fd419c3c7e3e47b63eb8d9c38a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetGap</name>
      <anchorfile>classMOERTEL_1_1Node.html</anchorfile>
      <anchor>a42674d61e4f689e5fcca3c43277f458e</anchor>
      <arglist>(double gap)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>MOERTEL::Overlap</name>
    <filename>classMOERTEL_1_1Overlap.html</filename>
    <member kind="function">
      <type></type>
      <name>Overlap</name>
      <anchorfile>classMOERTEL_1_1Overlap.html</anchorfile>
      <anchor>a5e68fdbb3a90098307b98a10493ce1a4</anchor>
      <arglist>(MOERTEL::Segment &amp;sseg, MOERTEL::Segment &amp;mseg, MOERTEL::Interface &amp;inter, bool exactvalues, int outlevel)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~Overlap</name>
      <anchorfile>classMOERTEL_1_1Overlap.html</anchorfile>
      <anchor>affe7e2eca4fabcf9742ed7c7bc9eb31b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>ComputeOverlap</name>
      <anchorfile>classMOERTEL_1_1Overlap.html</anchorfile>
      <anchor>ad34457f6d675ea7c6f6617ac467238d1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>OutLevel</name>
      <anchorfile>classMOERTEL_1_1Overlap.html</anchorfile>
      <anchor>a918ff0fd0646421e2c07c90fc0efd1e1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="friend">
      <type>friend class</type>
      <name>Interface</name>
      <anchorfile>classMOERTEL_1_1Overlap.html</anchorfile>
      <anchor>ab2d499aedae98d5bb86006432c06888f</anchor>
      <arglist></arglist>
    </member>
    <member kind="friend">
      <type>friend class</type>
      <name>Integrator</name>
      <anchorfile>classMOERTEL_1_1Overlap.html</anchorfile>
      <anchor>ace5bb0fe4232b9b0ced67ff743994e71</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Overlap</name>
      <anchorfile>classMOERTEL_1_1Overlap.html</anchorfile>
      <anchor>a5e68fdbb3a90098307b98a10493ce1a4</anchor>
      <arglist>(MOERTEL::Segment &amp;sseg, MOERTEL::Segment &amp;mseg, MOERTEL::Interface &amp;inter, bool exactvalues, int outlevel)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~Overlap</name>
      <anchorfile>classMOERTEL_1_1Overlap.html</anchorfile>
      <anchor>affe7e2eca4fabcf9742ed7c7bc9eb31b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>ComputeOverlap</name>
      <anchorfile>classMOERTEL_1_1Overlap.html</anchorfile>
      <anchor>ad34457f6d675ea7c6f6617ac467238d1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>OutLevel</name>
      <anchorfile>classMOERTEL_1_1Overlap.html</anchorfile>
      <anchor>a918ff0fd0646421e2c07c90fc0efd1e1</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>MOERTEL::Point</name>
    <filename>classMOERTEL_1_1Point.html</filename>
    <member kind="function">
      <type></type>
      <name>Point</name>
      <anchorfile>classMOERTEL_1_1Point.html</anchorfile>
      <anchor>a5e4601cca82bb185756bba2f4b997713</anchor>
      <arglist>(const int id, const double *xi, int out)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~Point</name>
      <anchorfile>classMOERTEL_1_1Point.html</anchorfile>
      <anchor>ad191355757bff4223c04a203cc9033c2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>OutLevel</name>
      <anchorfile>classMOERTEL_1_1Point.html</anchorfile>
      <anchor>ad64efea136b7ff102ae2b311f12402bf</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Print</name>
      <anchorfile>classMOERTEL_1_1Point.html</anchorfile>
      <anchor>ab24242afeae5890b6958fdf6a8884b70</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Id</name>
      <anchorfile>classMOERTEL_1_1Point.html</anchorfile>
      <anchor>a36eef837dbd4f1eb8d4cbca9abbdd275</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const double *</type>
      <name>Xi</name>
      <anchorfile>classMOERTEL_1_1Point.html</anchorfile>
      <anchor>ad2728f987d0e8fcb44b1f3405dfc86b0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const double *</type>
      <name>X</name>
      <anchorfile>classMOERTEL_1_1Point.html</anchorfile>
      <anchor>a096dd1197f7024798640af384a7b73d5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; MOERTEL::Node &gt;</type>
      <name>Node</name>
      <anchorfile>classMOERTEL_1_1Point.html</anchorfile>
      <anchor>ab46ed5920931f3b4320574baa6b0cc20</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>SetXi</name>
      <anchorfile>classMOERTEL_1_1Point.html</anchorfile>
      <anchor>ab25dea65bb894dad277593dd0629acf6</anchor>
      <arglist>(const double *xi)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>SetNode</name>
      <anchorfile>classMOERTEL_1_1Point.html</anchorfile>
      <anchor>a75bffccff77a3a3db67a8e0769188309</anchor>
      <arglist>(MOERTEL::Node *node)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>StoreFunctionValues</name>
      <anchorfile>classMOERTEL_1_1Point.html</anchorfile>
      <anchor>af4cc84f14150c9f23e5361ed76552bd6</anchor>
      <arglist>(int place, double *val, int valdim)</arglist>
    </member>
    <member kind="function">
      <type>std::vector&lt; double &gt; *</type>
      <name>FunctionValues</name>
      <anchorfile>classMOERTEL_1_1Point.html</anchorfile>
      <anchor>a21ad2ba2124cc6b316142b705db71cbc</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Point</name>
      <anchorfile>classMOERTEL_1_1Point.html</anchorfile>
      <anchor>a5e4601cca82bb185756bba2f4b997713</anchor>
      <arglist>(const int id, const double *xi, int out)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~Point</name>
      <anchorfile>classMOERTEL_1_1Point.html</anchorfile>
      <anchor>ad191355757bff4223c04a203cc9033c2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>OutLevel</name>
      <anchorfile>classMOERTEL_1_1Point.html</anchorfile>
      <anchor>ad64efea136b7ff102ae2b311f12402bf</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Print</name>
      <anchorfile>classMOERTEL_1_1Point.html</anchorfile>
      <anchor>ab24242afeae5890b6958fdf6a8884b70</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Id</name>
      <anchorfile>classMOERTEL_1_1Point.html</anchorfile>
      <anchor>a36eef837dbd4f1eb8d4cbca9abbdd275</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const double *</type>
      <name>Xi</name>
      <anchorfile>classMOERTEL_1_1Point.html</anchorfile>
      <anchor>ad2728f987d0e8fcb44b1f3405dfc86b0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const double *</type>
      <name>X</name>
      <anchorfile>classMOERTEL_1_1Point.html</anchorfile>
      <anchor>a096dd1197f7024798640af384a7b73d5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; MOERTEL::Node &gt;</type>
      <name>Node</name>
      <anchorfile>classMOERTEL_1_1Point.html</anchorfile>
      <anchor>ab46ed5920931f3b4320574baa6b0cc20</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>SetXi</name>
      <anchorfile>classMOERTEL_1_1Point.html</anchorfile>
      <anchor>ab25dea65bb894dad277593dd0629acf6</anchor>
      <arglist>(const double *xi)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>SetNode</name>
      <anchorfile>classMOERTEL_1_1Point.html</anchorfile>
      <anchor>a75bffccff77a3a3db67a8e0769188309</anchor>
      <arglist>(MOERTEL::Node *node)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>StoreFunctionValues</name>
      <anchorfile>classMOERTEL_1_1Point.html</anchorfile>
      <anchor>af4cc84f14150c9f23e5361ed76552bd6</anchor>
      <arglist>(int place, double *val, int valdim)</arglist>
    </member>
    <member kind="function">
      <type>std::vector&lt; double &gt; *</type>
      <name>FunctionValues</name>
      <anchorfile>classMOERTEL_1_1Point.html</anchorfile>
      <anchor>a21ad2ba2124cc6b316142b705db71cbc</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>MOERTEL::ProjectedNode</name>
    <filename>classMOERTEL_1_1ProjectedNode.html</filename>
    <base>MOERTEL::Node</base>
    <member kind="function">
      <type></type>
      <name>ProjectedNode</name>
      <anchorfile>classMOERTEL_1_1ProjectedNode.html</anchorfile>
      <anchor>ad168d536d07cbd03291cab147e26492f</anchor>
      <arglist>(const MOERTEL::Node &amp;basenode, const double *xi, MOERTEL::Segment *pseg)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ProjectedNode</name>
      <anchorfile>classMOERTEL_1_1ProjectedNode.html</anchorfile>
      <anchor>a4a0d6f12798bfb69afa84c562dca33c1</anchor>
      <arglist>(const MOERTEL::Node &amp;basenode, const double *xi, MOERTEL::Segment *pseg, int orthseg)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ProjectedNode</name>
      <anchorfile>classMOERTEL_1_1ProjectedNode.html</anchorfile>
      <anchor>ae5900a1791663874ca6f69dde5721715</anchor>
      <arglist>(MOERTEL::ProjectedNode &amp;old)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~ProjectedNode</name>
      <anchorfile>classMOERTEL_1_1ProjectedNode.html</anchorfile>
      <anchor>a7b1c4dd017b105b03e8eecba72168ad7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>Print</name>
      <anchorfile>classMOERTEL_1_1ProjectedNode.html</anchorfile>
      <anchor>a55be69a4fdb1d70ec282484970448cff</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>double *</type>
      <name>Xi</name>
      <anchorfile>classMOERTEL_1_1ProjectedNode.html</anchorfile>
      <anchor>a08d27a73c437906874be5e04576e9c34</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>MOERTEL::Segment *</type>
      <name>Segment</name>
      <anchorfile>classMOERTEL_1_1ProjectedNode.html</anchorfile>
      <anchor>a7b51d5b6825ee3073dec927924bc08f0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>OrthoSegment</name>
      <anchorfile>classMOERTEL_1_1ProjectedNode.html</anchorfile>
      <anchor>a96edb3031061ce4e3800f95fabc6589d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ProjectedNode</name>
      <anchorfile>classMOERTEL_1_1ProjectedNode.html</anchorfile>
      <anchor>ad168d536d07cbd03291cab147e26492f</anchor>
      <arglist>(const MOERTEL::Node &amp;basenode, const double *xi, MOERTEL::Segment *pseg)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ProjectedNode</name>
      <anchorfile>classMOERTEL_1_1ProjectedNode.html</anchorfile>
      <anchor>a4a0d6f12798bfb69afa84c562dca33c1</anchor>
      <arglist>(const MOERTEL::Node &amp;basenode, const double *xi, MOERTEL::Segment *pseg, int orthseg)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ProjectedNode</name>
      <anchorfile>classMOERTEL_1_1ProjectedNode.html</anchorfile>
      <anchor>ae5900a1791663874ca6f69dde5721715</anchor>
      <arglist>(MOERTEL::ProjectedNode &amp;old)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~ProjectedNode</name>
      <anchorfile>classMOERTEL_1_1ProjectedNode.html</anchorfile>
      <anchor>a7b1c4dd017b105b03e8eecba72168ad7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>Print</name>
      <anchorfile>classMOERTEL_1_1ProjectedNode.html</anchorfile>
      <anchor>a55be69a4fdb1d70ec282484970448cff</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>double *</type>
      <name>Xi</name>
      <anchorfile>classMOERTEL_1_1ProjectedNode.html</anchorfile>
      <anchor>a08d27a73c437906874be5e04576e9c34</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>MOERTEL::Segment *</type>
      <name>Segment</name>
      <anchorfile>classMOERTEL_1_1ProjectedNode.html</anchorfile>
      <anchor>a7b51d5b6825ee3073dec927924bc08f0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>OrthoSegment</name>
      <anchorfile>classMOERTEL_1_1ProjectedNode.html</anchorfile>
      <anchor>a96edb3031061ce4e3800f95fabc6589d</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>MOERTEL::Projector</name>
    <filename>classMOERTEL_1_1Projector.html</filename>
    <member kind="function">
      <type></type>
      <name>Projector</name>
      <anchorfile>classMOERTEL_1_1Projector.html</anchorfile>
      <anchor>ae991249e05f1f50c347714437c016158</anchor>
      <arglist>(bool twoD, int outlevel)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~Projector</name>
      <anchorfile>classMOERTEL_1_1Projector.html</anchorfile>
      <anchor>a4ba9f5f66f3a601bfb9b4da73b617148</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>OutLevel</name>
      <anchorfile>classMOERTEL_1_1Projector.html</anchorfile>
      <anchor>a737638bfb3deb8b67a3c35da4545153d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>IsTwoDimensional</name>
      <anchorfile>classMOERTEL_1_1Projector.html</anchorfile>
      <anchor>ab157df12a10a131f9df0ed0da4404090</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>ProjectNodetoSegment_NodalNormal</name>
      <anchorfile>classMOERTEL_1_1Projector.html</anchorfile>
      <anchor>a0cf4bc63ae17b0f80789ad22f642e9a2</anchor>
      <arglist>(MOERTEL::Node &amp;node, MOERTEL::Segment &amp;seg, double xi[], double &amp;gap)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>ProjectNodetoSegment_SegmentNormal</name>
      <anchorfile>classMOERTEL_1_1Projector.html</anchorfile>
      <anchor>a7cbca45dd27dc0888c17e68e5943c2d8</anchor>
      <arglist>(MOERTEL::Node &amp;node, MOERTEL::Segment &amp;seg, double xi[], double &amp;gap)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>ProjectNodetoSegment_SegmentOrthogonal</name>
      <anchorfile>classMOERTEL_1_1Projector.html</anchorfile>
      <anchor>aa9649485f4af19586a319d5ec2002fde</anchor>
      <arglist>(MOERTEL::Node &amp;node, MOERTEL::Segment &amp;seg, double xi[], double &amp;gap)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>ProjectNodetoSegment_Orthogonal_to_Slave</name>
      <anchorfile>classMOERTEL_1_1Projector.html</anchorfile>
      <anchor>a59cd160e0f17c04ceecb322cb9066ecf</anchor>
      <arglist>(MOERTEL::Node &amp;snode, MOERTEL::Segment &amp;seg, double xi[], double &amp;gap, MOERTEL::Segment &amp;sseg)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Projector</name>
      <anchorfile>classMOERTEL_1_1Projector.html</anchorfile>
      <anchor>ae991249e05f1f50c347714437c016158</anchor>
      <arglist>(bool twoD, int outlevel)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~Projector</name>
      <anchorfile>classMOERTEL_1_1Projector.html</anchorfile>
      <anchor>a4ba9f5f66f3a601bfb9b4da73b617148</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>OutLevel</name>
      <anchorfile>classMOERTEL_1_1Projector.html</anchorfile>
      <anchor>a737638bfb3deb8b67a3c35da4545153d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>IsTwoDimensional</name>
      <anchorfile>classMOERTEL_1_1Projector.html</anchorfile>
      <anchor>ab157df12a10a131f9df0ed0da4404090</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>ProjectNodetoSegment_NodalNormal</name>
      <anchorfile>classMOERTEL_1_1Projector.html</anchorfile>
      <anchor>a0cf4bc63ae17b0f80789ad22f642e9a2</anchor>
      <arglist>(MOERTEL::Node &amp;node, MOERTEL::Segment &amp;seg, double xi[], double &amp;gap)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>ProjectNodetoSegment_SegmentNormal</name>
      <anchorfile>classMOERTEL_1_1Projector.html</anchorfile>
      <anchor>a7cbca45dd27dc0888c17e68e5943c2d8</anchor>
      <arglist>(MOERTEL::Node &amp;node, MOERTEL::Segment &amp;seg, double xi[], double &amp;gap)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>ProjectNodetoSegment_SegmentOrthogonal</name>
      <anchorfile>classMOERTEL_1_1Projector.html</anchorfile>
      <anchor>aa9649485f4af19586a319d5ec2002fde</anchor>
      <arglist>(MOERTEL::Node &amp;node, MOERTEL::Segment &amp;seg, double xi[], double &amp;gap)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>ProjectNodetoSegment_Orthogonal_to_Slave</name>
      <anchorfile>classMOERTEL_1_1Projector.html</anchorfile>
      <anchor>a59cd160e0f17c04ceecb322cb9066ecf</anchor>
      <arglist>(MOERTEL::Node &amp;snode, MOERTEL::Segment &amp;seg, double xi[], double &amp;gap, MOERTEL::Segment &amp;sseg)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>MOERTEL::Segment</name>
    <filename>classMOERTEL_1_1Segment.html</filename>
    <member kind="enumeration">
      <type></type>
      <name>SegmentType</name>
      <anchorfile>classMOERTEL_1_1Segment.html</anchorfile>
      <anchor>a153a77b06b89ef3cb0d24a68c64bb838</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Segment</name>
      <anchorfile>classMOERTEL_1_1Segment.html</anchorfile>
      <anchor>aff566d71e36389ae3a6c2e28565ad3eb</anchor>
      <arglist>(int id, int nnode, int *nodeId, int outlevel)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Segment</name>
      <anchorfile>classMOERTEL_1_1Segment.html</anchorfile>
      <anchor>a66296930768546ce729531d46248ed47</anchor>
      <arglist>(int outlevel)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Segment</name>
      <anchorfile>classMOERTEL_1_1Segment.html</anchorfile>
      <anchor>aed53625a734b3d05daae67bdca068896</anchor>
      <arglist>(MOERTEL::Segment &amp;old)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~Segment</name>
      <anchorfile>classMOERTEL_1_1Segment.html</anchorfile>
      <anchor>a02f7880b93e5ca3c6aec5f5b696145e4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>OutLevel</name>
      <anchorfile>classMOERTEL_1_1Segment.html</anchorfile>
      <anchor>a76c2a80bc1674e454a55f18c7d51178a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Id</name>
      <anchorfile>classMOERTEL_1_1Segment.html</anchorfile>
      <anchor>ad928358469d4f6803c0d5a099448f8c7</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Nnode</name>
      <anchorfile>classMOERTEL_1_1Segment.html</anchorfile>
      <anchor>a56a4ce7a060febcc07866327c6239a80</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>MOERTEL::Segment::SegmentType</type>
      <name>Type</name>
      <anchorfile>classMOERTEL_1_1Segment.html</anchorfile>
      <anchor>af0e88bf70a81a465752c5f42ee2070fa</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const int *</type>
      <name>NodeIds</name>
      <anchorfile>classMOERTEL_1_1Segment.html</anchorfile>
      <anchor>a8e83313d0c190493521500a23579fa92</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>MOERTEL::Node **</type>
      <name>Nodes</name>
      <anchorfile>classMOERTEL_1_1Segment.html</anchorfile>
      <anchor>aacdc33b4f7af0726a712b20d0b4e9810</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Nfunctions</name>
      <anchorfile>classMOERTEL_1_1Segment.html</anchorfile>
      <anchor>ab425d7b19767251bc9b7eba60e3a9d14</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>MOERTEL::Function::FunctionType</type>
      <name>FunctionType</name>
      <anchorfile>classMOERTEL_1_1Segment.html</anchorfile>
      <anchor>a0bea5c37fb76cee2d51a7db758d499d9</anchor>
      <arglist>(int id)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>SetFunction</name>
      <anchorfile>classMOERTEL_1_1Segment.html</anchorfile>
      <anchor>accb222d4165a0b370a321ba230eb498e</anchor>
      <arglist>(int id, MOERTEL::Function *func)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>EvaluateFunction</name>
      <anchorfile>classMOERTEL_1_1Segment.html</anchorfile>
      <anchor>a43a1e9e2eacb1dda7690058814d28340</anchor>
      <arglist>(int id, const double *xi, double *val, int valdim, double *deriv)</arglist>
    </member>
    <member kind="function">
      <type>double *</type>
      <name>BuildNormalAtNode</name>
      <anchorfile>classMOERTEL_1_1Segment.html</anchorfile>
      <anchor>aac9f279fe5bb15c8a121c3d426665995</anchor>
      <arglist>(int nid)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>GetPtrstoNodes</name>
      <anchorfile>classMOERTEL_1_1Segment.html</anchorfile>
      <anchor>ad142b3547d5565e9f150653f2c307533</anchor>
      <arglist>(MOERTEL::Interface &amp;interface)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>GetPtrstoNodes</name>
      <anchorfile>classMOERTEL_1_1Segment.html</anchorfile>
      <anchor>ae49fbfcf3f7261591d84bae9c2221c15</anchor>
      <arglist>(std::vector&lt; MOERTEL::Node * &gt; &amp;nodes)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>Print</name>
      <anchorfile>classMOERTEL_1_1Segment.html</anchorfile>
      <anchor>acc394d5ce15c0a47d01899f10f308fbd</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetLocalNodeId</name>
      <anchorfile>classMOERTEL_1_1Segment.html</anchorfile>
      <anchor>aefe4f7b9b3e9872a429a2eea1a35350d</anchor>
      <arglist>(int nid)</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual MOERTEL::Segment *</type>
      <name>Clone</name>
      <anchorfile>classMOERTEL_1_1Segment.html</anchorfile>
      <anchor>a6eba54d2d88fd885423abcb6c37c0636</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int *</type>
      <name>Pack</name>
      <anchorfile>classMOERTEL_1_1Segment.html</anchorfile>
      <anchor>ab81f39c087094351b44ab86dff664b88</anchor>
      <arglist>(int *size)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>UnPack</name>
      <anchorfile>classMOERTEL_1_1Segment.html</anchorfile>
      <anchor>a144e0ae0407571afd3382a46260ba390</anchor>
      <arglist>(int *pack)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual double *</type>
      <name>BuildNormal</name>
      <anchorfile>classMOERTEL_1_1Segment.html</anchorfile>
      <anchor>a516eaa8a8048173da6a2e8ad3e2f3c17</anchor>
      <arglist>(double *xi)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual double</type>
      <name>Area</name>
      <anchorfile>classMOERTEL_1_1Segment.html</anchorfile>
      <anchor>a4b61e84527a1814c4fa5486ab9a3d801</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual double</type>
      <name>Metric</name>
      <anchorfile>classMOERTEL_1_1Segment.html</anchorfile>
      <anchor>a20249f667825e0938e5e5ac6decf7ac7</anchor>
      <arglist>(double *xi, double g[], double G[][3])=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>LocalCoordinatesOfNode</name>
      <anchorfile>classMOERTEL_1_1Segment.html</anchorfile>
      <anchor>acdbb9577b6c645c6e054783c5af88e3d</anchor>
      <arglist>(int lid, double *xi)=0</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Segment</name>
      <anchorfile>classMOERTEL_1_1Segment.html</anchorfile>
      <anchor>aff566d71e36389ae3a6c2e28565ad3eb</anchor>
      <arglist>(int id, int nnode, int *nodeId, int outlevel)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Segment</name>
      <anchorfile>classMOERTEL_1_1Segment.html</anchorfile>
      <anchor>a66296930768546ce729531d46248ed47</anchor>
      <arglist>(int outlevel)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Segment</name>
      <anchorfile>classMOERTEL_1_1Segment.html</anchorfile>
      <anchor>aed53625a734b3d05daae67bdca068896</anchor>
      <arglist>(MOERTEL::Segment &amp;old)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~Segment</name>
      <anchorfile>classMOERTEL_1_1Segment.html</anchorfile>
      <anchor>a02f7880b93e5ca3c6aec5f5b696145e4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>OutLevel</name>
      <anchorfile>classMOERTEL_1_1Segment.html</anchorfile>
      <anchor>a76c2a80bc1674e454a55f18c7d51178a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Id</name>
      <anchorfile>classMOERTEL_1_1Segment.html</anchorfile>
      <anchor>ad928358469d4f6803c0d5a099448f8c7</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Nnode</name>
      <anchorfile>classMOERTEL_1_1Segment.html</anchorfile>
      <anchor>a56a4ce7a060febcc07866327c6239a80</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>MOERTEL::Segment::SegmentType</type>
      <name>Type</name>
      <anchorfile>classMOERTEL_1_1Segment.html</anchorfile>
      <anchor>af0e88bf70a81a465752c5f42ee2070fa</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const int *</type>
      <name>NodeIds</name>
      <anchorfile>classMOERTEL_1_1Segment.html</anchorfile>
      <anchor>a8e83313d0c190493521500a23579fa92</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>MOERTEL::Node **</type>
      <name>Nodes</name>
      <anchorfile>classMOERTEL_1_1Segment.html</anchorfile>
      <anchor>aacdc33b4f7af0726a712b20d0b4e9810</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Nfunctions</name>
      <anchorfile>classMOERTEL_1_1Segment.html</anchorfile>
      <anchor>ab425d7b19767251bc9b7eba60e3a9d14</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>MOERTEL::Function::FunctionType</type>
      <name>FunctionType</name>
      <anchorfile>classMOERTEL_1_1Segment.html</anchorfile>
      <anchor>a0bea5c37fb76cee2d51a7db758d499d9</anchor>
      <arglist>(int id)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>SetFunction</name>
      <anchorfile>classMOERTEL_1_1Segment.html</anchorfile>
      <anchor>accb222d4165a0b370a321ba230eb498e</anchor>
      <arglist>(int id, MOERTEL::Function *func)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>EvaluateFunction</name>
      <anchorfile>classMOERTEL_1_1Segment.html</anchorfile>
      <anchor>a43a1e9e2eacb1dda7690058814d28340</anchor>
      <arglist>(int id, const double *xi, double *val, int valdim, double *deriv)</arglist>
    </member>
    <member kind="function">
      <type>double *</type>
      <name>BuildNormalAtNode</name>
      <anchorfile>classMOERTEL_1_1Segment.html</anchorfile>
      <anchor>aac9f279fe5bb15c8a121c3d426665995</anchor>
      <arglist>(int nid)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>GetPtrstoNodes</name>
      <anchorfile>classMOERTEL_1_1Segment.html</anchorfile>
      <anchor>ad142b3547d5565e9f150653f2c307533</anchor>
      <arglist>(MOERTEL::Interface &amp;interface)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>GetPtrstoNodes</name>
      <anchorfile>classMOERTEL_1_1Segment.html</anchorfile>
      <anchor>ae49fbfcf3f7261591d84bae9c2221c15</anchor>
      <arglist>(std::vector&lt; MOERTEL::Node * &gt; &amp;nodes)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>Print</name>
      <anchorfile>classMOERTEL_1_1Segment.html</anchorfile>
      <anchor>acc394d5ce15c0a47d01899f10f308fbd</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetLocalNodeId</name>
      <anchorfile>classMOERTEL_1_1Segment.html</anchorfile>
      <anchor>aefe4f7b9b3e9872a429a2eea1a35350d</anchor>
      <arglist>(int nid)</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual MOERTEL::Segment *</type>
      <name>Clone</name>
      <anchorfile>classMOERTEL_1_1Segment.html</anchorfile>
      <anchor>a6eba54d2d88fd885423abcb6c37c0636</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int *</type>
      <name>Pack</name>
      <anchorfile>classMOERTEL_1_1Segment.html</anchorfile>
      <anchor>ab81f39c087094351b44ab86dff664b88</anchor>
      <arglist>(int *size)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>UnPack</name>
      <anchorfile>classMOERTEL_1_1Segment.html</anchorfile>
      <anchor>a144e0ae0407571afd3382a46260ba390</anchor>
      <arglist>(int *pack)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual double *</type>
      <name>BuildNormal</name>
      <anchorfile>classMOERTEL_1_1Segment.html</anchorfile>
      <anchor>a516eaa8a8048173da6a2e8ad3e2f3c17</anchor>
      <arglist>(double *xi)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual double</type>
      <name>Area</name>
      <anchorfile>classMOERTEL_1_1Segment.html</anchorfile>
      <anchor>a4b61e84527a1814c4fa5486ab9a3d801</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual double</type>
      <name>Metric</name>
      <anchorfile>classMOERTEL_1_1Segment.html</anchorfile>
      <anchor>a20249f667825e0938e5e5ac6decf7ac7</anchor>
      <arglist>(double *xi, double g[], double G[][3])=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>LocalCoordinatesOfNode</name>
      <anchorfile>classMOERTEL_1_1Segment.html</anchorfile>
      <anchor>acdbb9577b6c645c6e054783c5af88e3d</anchor>
      <arglist>(int lid, double *xi)=0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>MOERTEL::Segment_BiLinearQuad</name>
    <filename>classMOERTEL_1_1Segment__BiLinearQuad.html</filename>
    <base>MOERTEL::Segment</base>
    <member kind="function">
      <type></type>
      <name>Segment_BiLinearQuad</name>
      <anchorfile>classMOERTEL_1_1Segment__BiLinearQuad.html</anchorfile>
      <anchor>a4d194ecfeb4d8724bc2c31a64771b248</anchor>
      <arglist>(int id, int nnode, int *nodeId, int out)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Segment_BiLinearQuad</name>
      <anchorfile>classMOERTEL_1_1Segment__BiLinearQuad.html</anchorfile>
      <anchor>a1676fdce155631a7c99d4d292468b435</anchor>
      <arglist>(int out)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Segment_BiLinearQuad</name>
      <anchorfile>classMOERTEL_1_1Segment__BiLinearQuad.html</anchorfile>
      <anchor>a632793ff0ffaa55877a29b4db7c0ee69</anchor>
      <arglist>(MOERTEL::Segment_BiLinearQuad &amp;old)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~Segment_BiLinearQuad</name>
      <anchorfile>classMOERTEL_1_1Segment__BiLinearQuad.html</anchorfile>
      <anchor>ad97ae77cc0e5fd47d8853ce016f531c8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>MOERTEL::Segment *</type>
      <name>Clone</name>
      <anchorfile>classMOERTEL_1_1Segment__BiLinearQuad.html</anchorfile>
      <anchor>a1c3eb2631f0bbe39fa85e5597f24e75f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int *</type>
      <name>Pack</name>
      <anchorfile>classMOERTEL_1_1Segment__BiLinearQuad.html</anchorfile>
      <anchor>ae5faf61bb3d53f6364dbe4a0861013a6</anchor>
      <arglist>(int *size)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>UnPack</name>
      <anchorfile>classMOERTEL_1_1Segment__BiLinearQuad.html</anchorfile>
      <anchor>a155e49593513677d73faa31eadab94d2</anchor>
      <arglist>(int *pack)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>Area</name>
      <anchorfile>classMOERTEL_1_1Segment__BiLinearQuad.html</anchorfile>
      <anchor>a6af0d5e018faffc6c9f00432cbdf6f98</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>double *</type>
      <name>BuildNormal</name>
      <anchorfile>classMOERTEL_1_1Segment__BiLinearQuad.html</anchorfile>
      <anchor>a2e7768c40105b4c5d5d522ee8e5cec42</anchor>
      <arglist>(double *xi)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>Metric</name>
      <anchorfile>classMOERTEL_1_1Segment__BiLinearQuad.html</anchorfile>
      <anchor>af8f890fa579dddcce60b5426fa1d2705</anchor>
      <arglist>(double *xi, double g[], double G[][3])</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>LocalCoordinatesOfNode</name>
      <anchorfile>classMOERTEL_1_1Segment__BiLinearQuad.html</anchorfile>
      <anchor>a1dfc8320da08924317d2d366346aa3df</anchor>
      <arglist>(int lid, double *xi)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Segment_BiLinearQuad</name>
      <anchorfile>classMOERTEL_1_1Segment__BiLinearQuad.html</anchorfile>
      <anchor>a4d194ecfeb4d8724bc2c31a64771b248</anchor>
      <arglist>(int id, int nnode, int *nodeId, int out)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Segment_BiLinearQuad</name>
      <anchorfile>classMOERTEL_1_1Segment__BiLinearQuad.html</anchorfile>
      <anchor>a1676fdce155631a7c99d4d292468b435</anchor>
      <arglist>(int out)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Segment_BiLinearQuad</name>
      <anchorfile>classMOERTEL_1_1Segment__BiLinearQuad.html</anchorfile>
      <anchor>a632793ff0ffaa55877a29b4db7c0ee69</anchor>
      <arglist>(MOERTEL::Segment_BiLinearQuad &amp;old)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~Segment_BiLinearQuad</name>
      <anchorfile>classMOERTEL_1_1Segment__BiLinearQuad.html</anchorfile>
      <anchor>ad97ae77cc0e5fd47d8853ce016f531c8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>MOERTEL::Segment *</type>
      <name>Clone</name>
      <anchorfile>classMOERTEL_1_1Segment__BiLinearQuad.html</anchorfile>
      <anchor>a1c3eb2631f0bbe39fa85e5597f24e75f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int *</type>
      <name>Pack</name>
      <anchorfile>classMOERTEL_1_1Segment__BiLinearQuad.html</anchorfile>
      <anchor>ae5faf61bb3d53f6364dbe4a0861013a6</anchor>
      <arglist>(int *size)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>UnPack</name>
      <anchorfile>classMOERTEL_1_1Segment__BiLinearQuad.html</anchorfile>
      <anchor>a155e49593513677d73faa31eadab94d2</anchor>
      <arglist>(int *pack)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>Area</name>
      <anchorfile>classMOERTEL_1_1Segment__BiLinearQuad.html</anchorfile>
      <anchor>a6af0d5e018faffc6c9f00432cbdf6f98</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>double *</type>
      <name>BuildNormal</name>
      <anchorfile>classMOERTEL_1_1Segment__BiLinearQuad.html</anchorfile>
      <anchor>a2e7768c40105b4c5d5d522ee8e5cec42</anchor>
      <arglist>(double *xi)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>Metric</name>
      <anchorfile>classMOERTEL_1_1Segment__BiLinearQuad.html</anchorfile>
      <anchor>af8f890fa579dddcce60b5426fa1d2705</anchor>
      <arglist>(double *xi, double g[], double G[][3])</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>LocalCoordinatesOfNode</name>
      <anchorfile>classMOERTEL_1_1Segment__BiLinearQuad.html</anchorfile>
      <anchor>a1dfc8320da08924317d2d366346aa3df</anchor>
      <arglist>(int lid, double *xi)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>MOERTEL::Segment_BiLinearTri</name>
    <filename>classMOERTEL_1_1Segment__BiLinearTri.html</filename>
    <base>MOERTEL::Segment</base>
    <member kind="function">
      <type></type>
      <name>Segment_BiLinearTri</name>
      <anchorfile>classMOERTEL_1_1Segment__BiLinearTri.html</anchorfile>
      <anchor>ad16b721ee03ba73096a1feaec5694e77</anchor>
      <arglist>(int id, int nnode, int *nodeId, int out)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Segment_BiLinearTri</name>
      <anchorfile>classMOERTEL_1_1Segment__BiLinearTri.html</anchorfile>
      <anchor>aab4ab89adf6978181295bec031da8cf6</anchor>
      <arglist>(int out)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Segment_BiLinearTri</name>
      <anchorfile>classMOERTEL_1_1Segment__BiLinearTri.html</anchorfile>
      <anchor>acd4f71db52bdbed1727a569230388e15</anchor>
      <arglist>(MOERTEL::Segment_BiLinearTri &amp;old)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~Segment_BiLinearTri</name>
      <anchorfile>classMOERTEL_1_1Segment__BiLinearTri.html</anchorfile>
      <anchor>a40107e909d7c72523aaffe169732e5bb</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>MOERTEL::Segment *</type>
      <name>Clone</name>
      <anchorfile>classMOERTEL_1_1Segment__BiLinearTri.html</anchorfile>
      <anchor>a1008b12774c1e959433b3be9df3bbc42</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int *</type>
      <name>Pack</name>
      <anchorfile>classMOERTEL_1_1Segment__BiLinearTri.html</anchorfile>
      <anchor>ac9eb24c8b5f6a013055347796c4ad873</anchor>
      <arglist>(int *size)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>UnPack</name>
      <anchorfile>classMOERTEL_1_1Segment__BiLinearTri.html</anchorfile>
      <anchor>a815f892008ebfa813aa72d495f3ccfb8</anchor>
      <arglist>(int *pack)</arglist>
    </member>
    <member kind="function">
      <type>double *</type>
      <name>BuildNormal</name>
      <anchorfile>classMOERTEL_1_1Segment__BiLinearTri.html</anchorfile>
      <anchor>af4052e72f3f396b6e06f36d84881d4d8</anchor>
      <arglist>(double *xi)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>Area</name>
      <anchorfile>classMOERTEL_1_1Segment__BiLinearTri.html</anchorfile>
      <anchor>a88f5807b4fca02b7dc0b3e72c493e8eb</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>Metric</name>
      <anchorfile>classMOERTEL_1_1Segment__BiLinearTri.html</anchorfile>
      <anchor>afa9c715ff1dc47b4870b1f564e2da83b</anchor>
      <arglist>(double *xi, double g[], double G[][3])</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>LocalCoordinatesOfNode</name>
      <anchorfile>classMOERTEL_1_1Segment__BiLinearTri.html</anchorfile>
      <anchor>a3c387f61437cb9addee41cea5f581e47</anchor>
      <arglist>(int lid, double *xi)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Segment_BiLinearTri</name>
      <anchorfile>classMOERTEL_1_1Segment__BiLinearTri.html</anchorfile>
      <anchor>ad16b721ee03ba73096a1feaec5694e77</anchor>
      <arglist>(int id, int nnode, int *nodeId, int out)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Segment_BiLinearTri</name>
      <anchorfile>classMOERTEL_1_1Segment__BiLinearTri.html</anchorfile>
      <anchor>aab4ab89adf6978181295bec031da8cf6</anchor>
      <arglist>(int out)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Segment_BiLinearTri</name>
      <anchorfile>classMOERTEL_1_1Segment__BiLinearTri.html</anchorfile>
      <anchor>acd4f71db52bdbed1727a569230388e15</anchor>
      <arglist>(MOERTEL::Segment_BiLinearTri &amp;old)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~Segment_BiLinearTri</name>
      <anchorfile>classMOERTEL_1_1Segment__BiLinearTri.html</anchorfile>
      <anchor>a40107e909d7c72523aaffe169732e5bb</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>MOERTEL::Segment *</type>
      <name>Clone</name>
      <anchorfile>classMOERTEL_1_1Segment__BiLinearTri.html</anchorfile>
      <anchor>a1008b12774c1e959433b3be9df3bbc42</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int *</type>
      <name>Pack</name>
      <anchorfile>classMOERTEL_1_1Segment__BiLinearTri.html</anchorfile>
      <anchor>ac9eb24c8b5f6a013055347796c4ad873</anchor>
      <arglist>(int *size)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>UnPack</name>
      <anchorfile>classMOERTEL_1_1Segment__BiLinearTri.html</anchorfile>
      <anchor>a815f892008ebfa813aa72d495f3ccfb8</anchor>
      <arglist>(int *pack)</arglist>
    </member>
    <member kind="function">
      <type>double *</type>
      <name>BuildNormal</name>
      <anchorfile>classMOERTEL_1_1Segment__BiLinearTri.html</anchorfile>
      <anchor>af4052e72f3f396b6e06f36d84881d4d8</anchor>
      <arglist>(double *xi)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>Area</name>
      <anchorfile>classMOERTEL_1_1Segment__BiLinearTri.html</anchorfile>
      <anchor>a88f5807b4fca02b7dc0b3e72c493e8eb</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>Metric</name>
      <anchorfile>classMOERTEL_1_1Segment__BiLinearTri.html</anchorfile>
      <anchor>afa9c715ff1dc47b4870b1f564e2da83b</anchor>
      <arglist>(double *xi, double g[], double G[][3])</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>LocalCoordinatesOfNode</name>
      <anchorfile>classMOERTEL_1_1Segment__BiLinearTri.html</anchorfile>
      <anchor>a3c387f61437cb9addee41cea5f581e47</anchor>
      <arglist>(int lid, double *xi)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>MOERTEL::Segment_Linear1D</name>
    <filename>classMOERTEL_1_1Segment__Linear1D.html</filename>
    <base>MOERTEL::Segment</base>
    <member kind="function">
      <type></type>
      <name>Segment_Linear1D</name>
      <anchorfile>classMOERTEL_1_1Segment__Linear1D.html</anchorfile>
      <anchor>acdb93a8e0b1716d9bf7634aded8a308e</anchor>
      <arglist>(int id, int nnode, int *nodeId, int out)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Segment_Linear1D</name>
      <anchorfile>classMOERTEL_1_1Segment__Linear1D.html</anchorfile>
      <anchor>a2bc5fce60025248b6e378d138f340331</anchor>
      <arglist>(int out)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Segment_Linear1D</name>
      <anchorfile>classMOERTEL_1_1Segment__Linear1D.html</anchorfile>
      <anchor>a7c0893fd3c5520f6c587f0dd7619d1d1</anchor>
      <arglist>(MOERTEL::Segment_Linear1D &amp;old)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~Segment_Linear1D</name>
      <anchorfile>classMOERTEL_1_1Segment__Linear1D.html</anchorfile>
      <anchor>a33de3ef53ef4235ba3bd2e76399a1f6f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>MOERTEL::Segment *</type>
      <name>Clone</name>
      <anchorfile>classMOERTEL_1_1Segment__Linear1D.html</anchorfile>
      <anchor>aa085b46132b99d98a04dd15b18a91983</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int *</type>
      <name>Pack</name>
      <anchorfile>classMOERTEL_1_1Segment__Linear1D.html</anchorfile>
      <anchor>a7a47888f47a04e53eeea94f79795c958</anchor>
      <arglist>(int *size)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>UnPack</name>
      <anchorfile>classMOERTEL_1_1Segment__Linear1D.html</anchorfile>
      <anchor>aac8b2adad1aeccd7e3aa9912c21500ed</anchor>
      <arglist>(int *pack)</arglist>
    </member>
    <member kind="function">
      <type>double *</type>
      <name>BuildNormal</name>
      <anchorfile>classMOERTEL_1_1Segment__Linear1D.html</anchorfile>
      <anchor>aee58918f5d531f7e472a276044ab5013</anchor>
      <arglist>(double *xi)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>Area</name>
      <anchorfile>classMOERTEL_1_1Segment__Linear1D.html</anchorfile>
      <anchor>a8fa6c85a4907ebcbbacb35dd9447edff</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>Metric</name>
      <anchorfile>classMOERTEL_1_1Segment__Linear1D.html</anchorfile>
      <anchor>a34a7720bbdbd66ecf03ec77d9bcaebcd</anchor>
      <arglist>(double *xi, double g[], double G[][3])</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>LocalCoordinatesOfNode</name>
      <anchorfile>classMOERTEL_1_1Segment__Linear1D.html</anchorfile>
      <anchor>a9dc4354eb28d00164b9148b6873bf940</anchor>
      <arglist>(int lid, double *xi)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Segment_Linear1D</name>
      <anchorfile>classMOERTEL_1_1Segment__Linear1D.html</anchorfile>
      <anchor>acdb93a8e0b1716d9bf7634aded8a308e</anchor>
      <arglist>(int id, int nnode, int *nodeId, int out)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Segment_Linear1D</name>
      <anchorfile>classMOERTEL_1_1Segment__Linear1D.html</anchorfile>
      <anchor>a2bc5fce60025248b6e378d138f340331</anchor>
      <arglist>(int out)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Segment_Linear1D</name>
      <anchorfile>classMOERTEL_1_1Segment__Linear1D.html</anchorfile>
      <anchor>a7c0893fd3c5520f6c587f0dd7619d1d1</anchor>
      <arglist>(MOERTEL::Segment_Linear1D &amp;old)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~Segment_Linear1D</name>
      <anchorfile>classMOERTEL_1_1Segment__Linear1D.html</anchorfile>
      <anchor>a33de3ef53ef4235ba3bd2e76399a1f6f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>MOERTEL::Segment *</type>
      <name>Clone</name>
      <anchorfile>classMOERTEL_1_1Segment__Linear1D.html</anchorfile>
      <anchor>aa085b46132b99d98a04dd15b18a91983</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int *</type>
      <name>Pack</name>
      <anchorfile>classMOERTEL_1_1Segment__Linear1D.html</anchorfile>
      <anchor>a7a47888f47a04e53eeea94f79795c958</anchor>
      <arglist>(int *size)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>UnPack</name>
      <anchorfile>classMOERTEL_1_1Segment__Linear1D.html</anchorfile>
      <anchor>aac8b2adad1aeccd7e3aa9912c21500ed</anchor>
      <arglist>(int *pack)</arglist>
    </member>
    <member kind="function">
      <type>double *</type>
      <name>BuildNormal</name>
      <anchorfile>classMOERTEL_1_1Segment__Linear1D.html</anchorfile>
      <anchor>aee58918f5d531f7e472a276044ab5013</anchor>
      <arglist>(double *xi)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>Area</name>
      <anchorfile>classMOERTEL_1_1Segment__Linear1D.html</anchorfile>
      <anchor>a8fa6c85a4907ebcbbacb35dd9447edff</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>Metric</name>
      <anchorfile>classMOERTEL_1_1Segment__Linear1D.html</anchorfile>
      <anchor>a34a7720bbdbd66ecf03ec77d9bcaebcd</anchor>
      <arglist>(double *xi, double g[], double G[][3])</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>LocalCoordinatesOfNode</name>
      <anchorfile>classMOERTEL_1_1Segment__Linear1D.html</anchorfile>
      <anchor>a9dc4354eb28d00164b9148b6873bf940</anchor>
      <arglist>(int lid, double *xi)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>MOERTEL::Solver</name>
    <filename>classMOERTEL_1_1Solver.html</filename>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~Solver</name>
      <anchorfile>classMOERTEL_1_1Solver.html</anchorfile>
      <anchor>ac25087db0939c8369382fd70c7ca60d5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Epetra_Comm &amp;</type>
      <name>Comm</name>
      <anchorfile>classMOERTEL_1_1Solver.html</anchorfile>
      <anchor>a10f03c744b1832217d28dbabdd619ba5</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>OutLevel</name>
      <anchorfile>classMOERTEL_1_1Solver.html</anchorfile>
      <anchor>af863302ed843892f4354c655ee4b8147</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetParameters</name>
      <anchorfile>classMOERTEL_1_1Solver.html</anchorfile>
      <anchor>a20fd059818e247f779048e01b70c1d9d</anchor>
      <arglist>(Teuchos::ParameterList *params)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetSystem</name>
      <anchorfile>classMOERTEL_1_1Solver.html</anchorfile>
      <anchor>a746054394a89db65c9d3090d0ee98946</anchor>
      <arglist>(Teuchos::RCP&lt; Epetra_CrsMatrix &gt; matrix, Teuchos::RCP&lt; Epetra_Vector &gt; x, Teuchos::RCP&lt; Epetra_Vector &gt; b)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>Solve</name>
      <anchorfile>classMOERTEL_1_1Solver.html</anchorfile>
      <anchor>a62705518e351c4c7f4b7da9cbe60b3d7</anchor>
      <arglist>(Teuchos::RCP&lt; Teuchos::ParameterList &gt; params, Teuchos::RCP&lt; Epetra_CrsMatrix &gt; matrix, Teuchos::RCP&lt; Epetra_Vector &gt; x, Teuchos::RCP&lt; Epetra_Vector &gt; b, MOERTEL::Manager &amp;manager)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~Solver</name>
      <anchorfile>classMOERTEL_1_1Solver.html</anchorfile>
      <anchor>ac25087db0939c8369382fd70c7ca60d5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Epetra_Comm &amp;</type>
      <name>Comm</name>
      <anchorfile>classMOERTEL_1_1Solver.html</anchorfile>
      <anchor>a10f03c744b1832217d28dbabdd619ba5</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>OutLevel</name>
      <anchorfile>classMOERTEL_1_1Solver.html</anchorfile>
      <anchor>af863302ed843892f4354c655ee4b8147</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetParameters</name>
      <anchorfile>classMOERTEL_1_1Solver.html</anchorfile>
      <anchor>a20fd059818e247f779048e01b70c1d9d</anchor>
      <arglist>(Teuchos::ParameterList *params)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetSystem</name>
      <anchorfile>classMOERTEL_1_1Solver.html</anchorfile>
      <anchor>a746054394a89db65c9d3090d0ee98946</anchor>
      <arglist>(Teuchos::RCP&lt; Epetra_CrsMatrix &gt; matrix, Teuchos::RCP&lt; Epetra_Vector &gt; x, Teuchos::RCP&lt; Epetra_Vector &gt; b)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>Solve</name>
      <anchorfile>classMOERTEL_1_1Solver.html</anchorfile>
      <anchor>a62705518e351c4c7f4b7da9cbe60b3d7</anchor>
      <arglist>(Teuchos::RCP&lt; Teuchos::ParameterList &gt; params, Teuchos::RCP&lt; Epetra_CrsMatrix &gt; matrix, Teuchos::RCP&lt; Epetra_Vector &gt; x, Teuchos::RCP&lt; Epetra_Vector &gt; b, MOERTEL::Manager &amp;manager)</arglist>
    </member>
  </compound>
  <compound kind="namespace">
    <name>MOERTEL</name>
    <filename>namespaceMOERTEL.html</filename>
    <class kind="class">MOERTEL::Function</class>
    <class kind="class">MOERTEL::Function_BiLinearQuad</class>
    <class kind="class">MOERTEL::Function_Constant1D</class>
    <class kind="class">MOERTEL::Function_ConstantTri</class>
    <class kind="class">MOERTEL::Function_DualBiLinearQuad</class>
    <class kind="class">MOERTEL::Function_DualLinear1D</class>
    <class kind="class">MOERTEL::Function_DualLinearTri</class>
    <class kind="class">MOERTEL::Function_Linear1D</class>
    <class kind="class">MOERTEL::Function_LinearTri</class>
    <class kind="class">MOERTEL::Integrator</class>
    <class kind="class">MOERTEL::Interface</class>
    <class kind="class">MOERTEL::Lmselector</class>
    <class kind="class">MOERTEL::Manager</class>
    <class kind="class">MOERTEL::Mortar_ML_Preconditioner</class>
    <class kind="class">MOERTEL::Node</class>
    <class kind="class">MOERTEL::Overlap</class>
    <class kind="class">MOERTEL::Point</class>
    <class kind="class">MOERTEL::ProjectedNode</class>
    <class kind="class">MOERTEL::Projector</class>
    <class kind="class">MOERTEL::Segment</class>
    <class kind="class">MOERTEL::Segment_BiLinearQuad</class>
    <class kind="class">MOERTEL::Segment_BiLinearTri</class>
    <class kind="class">MOERTEL::Segment_Linear1D</class>
    <class kind="class">MOERTEL::Solver</class>
    <member kind="function">
      <type>MOERTEL::Function *</type>
      <name>AllocateFunction</name>
      <anchorfile>namespaceMOERTEL.html</anchorfile>
      <anchor>a2292a15a5612751f7592d7fc01a6bee6</anchor>
      <arglist>(MOERTEL::Function::FunctionType type, int out)</arglist>
    </member>
    <member kind="function">
      <type>MOERTEL::Segment *</type>
      <name>AllocateSegment</name>
      <anchorfile>namespaceMOERTEL.html</anchorfile>
      <anchor>a1e478269c2d3471a05bb1f04b5b74c78</anchor>
      <arglist>(int type, int out)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>cross</name>
      <anchorfile>namespaceMOERTEL.html</anchorfile>
      <anchor>a95a4ac68471ca7763e345c3b3fc1d3f8</anchor>
      <arglist>(double *out, const double *g1, const double *g2)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>dot</name>
      <anchorfile>namespaceMOERTEL.html</anchorfile>
      <anchor>a151477363f39b69025ed229098218007</anchor>
      <arglist>(const double *g1, const double *g2, const int dim)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>length</name>
      <anchorfile>namespaceMOERTEL.html</anchorfile>
      <anchor>ac09fcdda79447314bf6e7497af4a81ee</anchor>
      <arglist>(const double *g, const int dim)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>solve22</name>
      <anchorfile>namespaceMOERTEL.html</anchorfile>
      <anchor>a748d6409f9535bea245d74ceb6ed302e</anchor>
      <arglist>(const double A[][2], double *x, const double *b)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>solve33</name>
      <anchorfile>namespaceMOERTEL.html</anchorfile>
      <anchor>aa7c36f24184e3884b1325c0158424e79</anchor>
      <arglist>(const double A[][3], double *x, const double *b)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>digit_ten</name>
      <anchorfile>namespaceMOERTEL.html</anchorfile>
      <anchor>a1f0d3e57b39b23f6c8d7f16db0a92c44</anchor>
      <arglist>(int i)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>sort</name>
      <anchorfile>namespaceMOERTEL.html</anchorfile>
      <anchor>aaa1156aa4052469008fb714d754c5125</anchor>
      <arglist>(double *dlist, int N, int *list2)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>swap</name>
      <anchorfile>namespaceMOERTEL.html</anchorfile>
      <anchor>ae9d58fa193829f56ff8402e00df4302c</anchor>
      <arglist>(kind &amp;a, kind &amp;b)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>MatrixMatrixAdd</name>
      <anchorfile>namespaceMOERTEL.html</anchorfile>
      <anchor>acc436dd612f949b54aef7a890acffc50</anchor>
      <arglist>(const Epetra_CrsMatrix &amp;A, bool transposeA, double scalarA, Epetra_CrsMatrix &amp;B, double scalarB)</arglist>
    </member>
    <member kind="function">
      <type>Epetra_CrsMatrix *</type>
      <name>MatMatMult</name>
      <anchorfile>namespaceMOERTEL.html</anchorfile>
      <anchor>aaf50d9d9fb22d187ae54c9699c166714</anchor>
      <arglist>(const Epetra_CrsMatrix &amp;A, bool transA, const Epetra_CrsMatrix &amp;B, bool transB, int outlevel)</arglist>
    </member>
    <member kind="function">
      <type>Epetra_CrsMatrix *</type>
      <name>PaddedMatrix</name>
      <anchorfile>namespaceMOERTEL.html</anchorfile>
      <anchor>a98c6fa42cc989f9b95b5c5940d763d40</anchor>
      <arglist>(const Epetra_Map rowmap, double val, const int numentriesperrow)</arglist>
    </member>
    <member kind="function">
      <type>Epetra_CrsMatrix *</type>
      <name>StripZeros</name>
      <anchorfile>namespaceMOERTEL.html</anchorfile>
      <anchor>ac5fa3b515f001b60ca6ff8ff1123b46d</anchor>
      <arglist>(Epetra_CrsMatrix &amp;A, double eps)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>SplitMatrix2x2</name>
      <anchorfile>namespaceMOERTEL.html</anchorfile>
      <anchor>a22fe81ebc38fae7cc0862ef6997deb12</anchor>
      <arglist>(Teuchos::RCP&lt; Epetra_CrsMatrix &gt; A, Teuchos::RCP&lt; Epetra_Map &gt; &amp;A11rowmap, Teuchos::RCP&lt; Epetra_Map &gt; &amp;A22rowmap, Teuchos::RCP&lt; Epetra_CrsMatrix &gt; &amp;A11, Teuchos::RCP&lt; Epetra_CrsMatrix &gt; &amp;A12, Teuchos::RCP&lt; Epetra_CrsMatrix &gt; &amp;A21, Teuchos::RCP&lt; Epetra_CrsMatrix &gt; &amp;A22)</arglist>
    </member>
    <member kind="function">
      <type>Epetra_Map *</type>
      <name>SplitMap</name>
      <anchorfile>namespaceMOERTEL.html</anchorfile>
      <anchor>abf22072c2c1aebe092b2167d7b5acdf7</anchor>
      <arglist>(const Epetra_Map &amp;Amap, const Epetra_Map &amp;Agiven)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>SplitVector</name>
      <anchorfile>namespaceMOERTEL.html</anchorfile>
      <anchor>a6a3aaccc52d72ae389518058d5c4d338</anchor>
      <arglist>(const Epetra_Vector &amp;x, const Epetra_Map &amp;x1map, Epetra_Vector *&amp;x1, const Epetra_Map &amp;x2map, Epetra_Vector *&amp;x2)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>MergeVector</name>
      <anchorfile>namespaceMOERTEL.html</anchorfile>
      <anchor>aa11e72d437f3e34b1f209215ca0bbf3d</anchor>
      <arglist>(const Epetra_Vector &amp;x1, const Epetra_Vector &amp;x2, Epetra_Vector &amp;xresult)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>Print_Matrix</name>
      <anchorfile>namespaceMOERTEL.html</anchorfile>
      <anchor>a6fde3a1a5ad6639904f6f783378227fa</anchor>
      <arglist>(std::string name, Epetra_CrsMatrix &amp;A, int ibase)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>Print_Graph</name>
      <anchorfile>namespaceMOERTEL.html</anchorfile>
      <anchor>a41cdcc4d764c3da0b3c62f8d4c5b98a6</anchor>
      <arglist>(std::string name, Epetra_CrsGraph &amp;A, int ibase)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>Print_Vector</name>
      <anchorfile>namespaceMOERTEL.html</anchorfile>
      <anchor>ac1995680e59c21d20debffb5e814f496</anchor>
      <arglist>(std::string name, Epetra_Vector &amp;v, int ibase)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ReportError</name>
      <anchorfile>namespaceMOERTEL.html</anchorfile>
      <anchor>ad2279567e4edf7e5a9024e236b84e17d</anchor>
      <arglist>(const std::stringstream &amp;Message)</arglist>
    </member>
  </compound>
  <compound kind="page">
    <name>index</name>
    <title>Moertel: Mortar Methods Package.</title>
    <filename>index</filename>
    <docanchor file="index" title="Introduction">Moertel_intro</docanchor>
    <docanchor file="index" title="Overview of Moertel.">Moertel_overview</docanchor>
    <docanchor file="index" title="Capabilities">Capabilities</docanchor>
    <docanchor file="index" title="Configuration">Configuration</docanchor>
    <docanchor file="index" title="User interface">User_interface</docanchor>
    <docanchor file="index" title="Examples">Examples</docanchor>
    <docanchor file="index" title="Documentation">Documentation</docanchor>
    <docanchor file="index" title="Literature">Literature</docanchor>
    <docanchor file="index" title="Author and Acknowledgements">author</docanchor>
  </compound>
</tagfile>
