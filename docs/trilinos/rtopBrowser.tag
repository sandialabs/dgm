<?xml version='1.0' encoding='UTF-8' standalone='yes' ?>
<tagfile>
  <compound kind="file">
    <name>browser/doc/index.doc</name>
    <path>/Users/sscoll/dist/trilinos/packages/rtop/browser/doc/</path>
    <filename>browser_2doc_2index_8doc</filename>
  </compound>
  <compound kind="file">
    <name>src/interfaces/doc/index.doc</name>
    <path>/Users/sscoll/dist/trilinos/packages/rtop/src/interfaces/doc/</path>
    <filename>src_2interfaces_2doc_2index_8doc</filename>
  </compound>
  <compound kind="file">
    <name>src/ops_lib/doc/index.doc</name>
    <path>/Users/sscoll/dist/trilinos/packages/rtop/src/ops_lib/doc/</path>
    <filename>src_2ops__lib_2doc_2index_8doc</filename>
  </compound>
  <compound kind="file">
    <name>src/support/doc/index.doc</name>
    <path>/Users/sscoll/dist/trilinos/packages/rtop/src/support/doc/</path>
    <filename>src_2support_2doc_2index_8doc</filename>
  </compound>
  <compound kind="file">
    <name>RTOp_ConfigDefs.hpp</name>
    <path>/Users/sscoll/dist/trilinos/packages/rtop/src/</path>
    <filename>RTOp__ConfigDefs_8hpp</filename>
  </compound>
  <compound kind="file">
    <name>RTOp_parallel_helpers.c</name>
    <path>/Users/sscoll/dist/trilinos/packages/rtop/src/support/</path>
    <filename>RTOp__parallel__helpers_8c</filename>
    <includes id="RTOp__parallel__helpers_8h" name="RTOp_parallel_helpers.h" local="yes" imported="no">RTOp_parallel_helpers.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>MY_MIN</name>
      <anchorfile>RTOp__parallel__helpers_8c.html</anchorfile>
      <anchor>a384fcacf0b6110dc203b9944c94e2399</anchor>
      <arglist>(a, b)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>MY_MAX</name>
      <anchorfile>RTOp__parallel__helpers_8c.html</anchorfile>
      <anchor>ac0a25c397fc5134ad22c456587baf7a0</anchor>
      <arglist>(a, b)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>RTOp_parallel_calc_overlap</name>
      <anchorfile>RTOp__parallel__helpers_8c.html</anchorfile>
      <anchor>a43fefe9a4be562d1812910cb52bfe0f7</anchor>
      <arglist>(Teuchos_Ordinal global_dim_in, Teuchos_Ordinal local_sub_dim_in, Teuchos_Ordinal local_off_in, const Teuchos_Ordinal first_ele_off_in, const Teuchos_Ordinal sub_dim_in, const Teuchos_Ordinal global_off_in, Teuchos_Ordinal *overlap_first_local_ele_off, Teuchos_Ordinal *overalap_local_sub_dim, Teuchos_Ordinal *overlap_global_off)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>RTOp_parallel_helpers.h</name>
    <path>/Users/sscoll/dist/trilinos/packages/rtop/src/support/</path>
    <filename>RTOp__parallel__helpers_8h</filename>
    <includes id="RTOp__ConfigDefs_8hpp" name="RTOp_ConfigDefs.hpp" local="yes" imported="no">RTOp_ConfigDefs.hpp</includes>
    <member kind="function">
      <type>void</type>
      <name>RTOp_parallel_calc_overlap</name>
      <anchorfile>RTOp__parallel__helpers_8h.html</anchorfile>
      <anchor>a88724e344e1f798065071cd53216576c</anchor>
      <arglist>(Teuchos_Ordinal global_dim, Teuchos_Ordinal local_sub_dim, Teuchos_Ordinal local_off, const Teuchos_Ordinal first_ele_off, const Teuchos_Ordinal sub_dim, const Teuchos_Ordinal global_off, Teuchos_Ordinal *overlap_first_local_ele_off, Teuchos_Ordinal *overalap_local_sub_dim, Teuchos_Ordinal *overlap_global_off)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>RTOpPack_LapackWrappers.cpp</name>
    <path>/Users/sscoll/dist/trilinos/packages/rtop/src/lapack/</path>
    <filename>RTOpPack__LapackWrappers_8cpp</filename>
    <includes id="RTOpPack__LapackWrappers_8hpp" name="RTOpPack_LapackWrappers.hpp" local="yes" imported="no">RTOpPack_LapackWrappers.hpp</includes>
  </compound>
  <compound kind="file">
    <name>RTOpPack_LapackWrappers.hpp</name>
    <path>/Users/sscoll/dist/trilinos/packages/rtop/src/lapack/</path>
    <filename>RTOpPack__LapackWrappers_8hpp</filename>
    <includes id="RTOpPack__Types_8hpp" name="RTOpPack_Types.hpp" local="yes" imported="no">RTOpPack_Types.hpp</includes>
    <namespace>RTOpPack</namespace>
    <member kind="enumeration">
      <type></type>
      <name>ETransp</name>
      <anchorfile>namespaceRTOpPack.html</anchorfile>
      <anchor>a6dd686f0856f7da469fb22d7306586c2</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>NOTRANS</name>
      <anchorfile>namespaceRTOpPack.html</anchorfile>
      <anchor>a6dd686f0856f7da469fb22d7306586c2a88e45d282c9b05b40d977c19a3c7701a</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>TRANS</name>
      <anchorfile>namespaceRTOpPack.html</anchorfile>
      <anchor>a6dd686f0856f7da469fb22d7306586c2a3be8d472081a6dbe69bc75e16821f523</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CONJTRANS</name>
      <anchorfile>namespaceRTOpPack.html</anchorfile>
      <anchor>a6dd686f0856f7da469fb22d7306586c2a7d555adbebdbb628e639f4b311b6a2a3</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>getrf</name>
      <anchorfile>namespaceRTOpPack.html</anchorfile>
      <anchor>a49a263c6e33256cbcac68e3ba12176ea</anchor>
      <arglist>(const SubMultiVectorView&lt; Scalar &gt; &amp;A, const ArrayView&lt; int &gt; &amp;ipiv, const Ptr&lt; int &gt; &amp;rank)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>getrs</name>
      <anchorfile>namespaceRTOpPack.html</anchorfile>
      <anchor>a14ef611932a8c143190e2298dd57486a</anchor>
      <arglist>(const ConstSubMultiVectorView&lt; Scalar &gt; &amp;A, const ArrayView&lt; const int &gt; &amp;ipiv, const ETransp transp, const Ptr&lt; const SubMultiVectorView&lt; Scalar &gt; &gt; &amp;BX)</arglist>
    </member>
    <member kind="variable">
      <type>const int</type>
      <name>NUM_ETRANS_ARGS</name>
      <anchorfile>namespaceRTOpPack.html</anchorfile>
      <anchor>aa476f279820b4f1054fcc8ff7f24dbd5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const Teuchos::Tuple&lt; char, NUM_ETRANS_ARGS &gt;</type>
      <name>transpMap</name>
      <anchorfile>namespaceRTOpPack.html</anchorfile>
      <anchor>a0a534f2b7606752456764aa1e38ed86c</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>RTOpPack_ROpCountNanInf.hpp</name>
    <path>/Users/sscoll/dist/trilinos/packages/rtop/src/ops_lib/</path>
    <filename>RTOpPack__ROpCountNanInf_8hpp</filename>
    <namespace>RTOpPack</namespace>
    <member kind="function">
      <type></type>
      <name>RTOP_ROP_1_REDUCT_SCALAR</name>
      <anchorfile>namespaceRTOpPack.html</anchorfile>
      <anchor>a5896c1aea0d2c2b1e9f491b301f9f7fe</anchor>
      <arglist>(ROpCountNanInf, index_type, REDUCT_TYPE_SUM)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>RTOpPack_ROpDotProd.hpp</name>
    <path>/Users/sscoll/dist/trilinos/packages/rtop/src/ops_lib/</path>
    <filename>RTOpPack__ROpDotProd_8hpp</filename>
    <namespace>RTOpPack</namespace>
    <member kind="function">
      <type></type>
      <name>RTOP_ROP_2_REDUCT_SCALAR</name>
      <anchorfile>namespaceRTOpPack.html</anchorfile>
      <anchor>a588fefd89bf99744acc41ad10d12a3df</anchor>
      <arglist>(ROpDotProd, Scalar, REDUCT_TYPE_SUM)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>RTOpPack_ROpGetElement.hpp</name>
    <path>/Users/sscoll/dist/trilinos/packages/rtop/src/ops_lib/</path>
    <filename>RTOpPack__ROpGetElement_8hpp</filename>
    <class kind="class">RTOpPack::ROpGetElementEleWiseReductionOp</class>
    <class kind="class">RTOpPack::ROpGetElement</class>
    <namespace>RTOpPack</namespace>
  </compound>
  <compound kind="file">
    <name>RTOpPack_ROpGetSubVector.cpp</name>
    <path>/Users/sscoll/dist/trilinos/packages/rtop/src/ops_lib/</path>
    <filename>RTOpPack__ROpGetSubVector_8cpp</filename>
    <includes id="RTOpPack__ROpGetSubVector__decl_8hpp" name="RTOpPack_ROpGetSubVector_decl.hpp" local="yes" imported="no">RTOpPack_ROpGetSubVector_decl.hpp</includes>
  </compound>
  <compound kind="file">
    <name>RTOpPack_ROpGetSubVector_decl.hpp</name>
    <path>/Users/sscoll/dist/trilinos/packages/rtop/src/ops_lib/</path>
    <filename>RTOpPack__ROpGetSubVector__decl_8hpp</filename>
    <class kind="class">RTOpPack::ROpGetSubVector</class>
    <namespace>RTOpPack</namespace>
  </compound>
  <compound kind="file">
    <name>RTOpPack_ROpGetSubVector_def.hpp</name>
    <path>/Users/sscoll/dist/trilinos/packages/rtop/src/ops_lib/</path>
    <filename>RTOpPack__ROpGetSubVector__def_8hpp</filename>
    <includes id="RTOpPack__ROpGetSubVector__decl_8hpp" name="RTOpPack_ROpGetSubVector_decl.hpp" local="yes" imported="no">RTOpPack_ROpGetSubVector_decl.hpp</includes>
    <namespace>RTOpPack</namespace>
  </compound>
  <compound kind="file">
    <name>RTOpPack_ROpMax.hpp</name>
    <path>/Users/sscoll/dist/trilinos/packages/rtop/src/ops_lib/</path>
    <filename>RTOpPack__ROpMax_8hpp</filename>
    <namespace>RTOpPack</namespace>
    <member kind="function">
      <type></type>
      <name>RTOP_ROP_1_REDUCT_SCALAR_CUSTOM_DEFAULT</name>
      <anchorfile>namespaceRTOpPack.html</anchorfile>
      <anchor>af53bd72a1de3e27ebb658aecd8e067f0</anchor>
      <arglist>(ROpMax, Scalar, REDUCT_TYPE_MAX, Teuchos::as&lt; Scalar &gt;(-std::numeric_limits&lt; Scalar &gt;::max()))</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>RTOpPack_ROpMaxIndex.hpp</name>
    <path>/Users/sscoll/dist/trilinos/packages/rtop/src/ops_lib/</path>
    <filename>RTOpPack__ROpMaxIndex_8hpp</filename>
    <class kind="class">RTOpPack::ROpMaxIndexEleWiseReductionOp</class>
    <class kind="class">RTOpPack::ROpMaxIndexReductObjReductionOp</class>
    <class kind="class">RTOpPack::ROpMaxIndex</class>
    <namespace>RTOpPack</namespace>
  </compound>
  <compound kind="file">
    <name>RTOpPack_ROpMaxIndexLessThanBound.hpp</name>
    <path>/Users/sscoll/dist/trilinos/packages/rtop/src/ops_lib/</path>
    <filename>RTOpPack__ROpMaxIndexLessThanBound_8hpp</filename>
    <includes id="RTOpPack__ROpMaxIndex_8hpp" name="RTOpPack_ROpMaxIndex.hpp" local="yes" imported="no">RTOpPack_ROpMaxIndex.hpp</includes>
    <class kind="class">RTOpPack::ROpMaxIndexLessThanBoundEleWiseReductionOp</class>
    <class kind="class">RTOpPack::ROpMaxIndexLessThanBound</class>
    <namespace>RTOpPack</namespace>
  </compound>
  <compound kind="file">
    <name>RTOpPack_ROpMin.hpp</name>
    <path>/Users/sscoll/dist/trilinos/packages/rtop/src/ops_lib/</path>
    <filename>RTOpPack__ROpMin_8hpp</filename>
    <namespace>RTOpPack</namespace>
    <member kind="function">
      <type></type>
      <name>RTOP_ROP_1_REDUCT_SCALAR_CUSTOM_DEFAULT</name>
      <anchorfile>namespaceRTOpPack.html</anchorfile>
      <anchor>a9ed27681a391209cd325e9ef849fac6f</anchor>
      <arglist>(ROpMin, Scalar, REDUCT_TYPE_MIN, std::numeric_limits&lt; Scalar &gt;::max())</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>RTOpPack_ROpMinIndex.hpp</name>
    <path>/Users/sscoll/dist/trilinos/packages/rtop/src/ops_lib/</path>
    <filename>RTOpPack__ROpMinIndex_8hpp</filename>
    <class kind="class">RTOpPack::ROpMinIndexEleWiseReductionOp</class>
    <class kind="class">RTOpPack::ROpMinIndexReductObjReductionOp</class>
    <class kind="class">RTOpPack::ROpMinIndex</class>
    <namespace>RTOpPack</namespace>
  </compound>
  <compound kind="file">
    <name>RTOpPack_ROpMinIndexGreaterThanBound.hpp</name>
    <path>/Users/sscoll/dist/trilinos/packages/rtop/src/ops_lib/</path>
    <filename>RTOpPack__ROpMinIndexGreaterThanBound_8hpp</filename>
    <includes id="RTOpPack__ROpMinIndex_8hpp" name="RTOpPack_ROpMinIndex.hpp" local="yes" imported="no">RTOpPack_ROpMinIndex.hpp</includes>
    <class kind="class">RTOpPack::ROpMinIndexGreaterThanBoundEleWiseReductionOp</class>
    <class kind="class">RTOpPack::ROpMinIndexGreaterThanBound</class>
    <namespace>RTOpPack</namespace>
  </compound>
  <compound kind="file">
    <name>RTOpPack_ROpNorm1.hpp</name>
    <path>/Users/sscoll/dist/trilinos/packages/rtop/src/ops_lib/</path>
    <filename>RTOpPack__ROpNorm1_8hpp</filename>
    <namespace>RTOpPack</namespace>
    <member kind="function">
      <type></type>
      <name>RTOP_ROP_1_REDUCT_SCALAR</name>
      <anchorfile>namespaceRTOpPack.html</anchorfile>
      <anchor>afa7883b52ca3756eea4137592a583e76</anchor>
      <arglist>(ROpNorm1, typename ScalarTraits&lt; Scalar &gt;::magnitudeType, REDUCT_TYPE_SUM)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>RTOpPack_ROpNorm2.hpp</name>
    <path>/Users/sscoll/dist/trilinos/packages/rtop/src/ops_lib/</path>
    <filename>RTOpPack__ROpNorm2_8hpp</filename>
    <class kind="class">RTOpPack::ROpNorm2EleWiseReduction</class>
    <class kind="class">RTOpPack::ROpNorm2</class>
    <namespace>RTOpPack</namespace>
  </compound>
  <compound kind="file">
    <name>RTOpPack_ROpNormInf.hpp</name>
    <path>/Users/sscoll/dist/trilinos/packages/rtop/src/ops_lib/</path>
    <filename>RTOpPack__ROpNormInf_8hpp</filename>
    <namespace>RTOpPack</namespace>
    <member kind="function">
      <type></type>
      <name>RTOP_ROP_1_REDUCT_SCALAR</name>
      <anchorfile>namespaceRTOpPack.html</anchorfile>
      <anchor>a935d892d691cf26e285e5fdc202d6c1e</anchor>
      <arglist>(ROpNormInf, typename ScalarTraits&lt; Scalar &gt;::magnitudeType, REDUCT_TYPE_MAX)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>RTOpPack_ROpSum.hpp</name>
    <path>/Users/sscoll/dist/trilinos/packages/rtop/src/ops_lib/</path>
    <filename>RTOpPack__ROpSum_8hpp</filename>
    <namespace>RTOpPack</namespace>
    <member kind="function">
      <type></type>
      <name>RTOP_ROP_1_REDUCT_SCALAR</name>
      <anchorfile>namespaceRTOpPack.html</anchorfile>
      <anchor>a46219fb6aa99cab595fed75e4d4c05d6</anchor>
      <arglist>(ROpSum, Scalar, REDUCT_TYPE_SUM)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>RTOpPack_ROpWeightedNorm2.hpp</name>
    <path>/Users/sscoll/dist/trilinos/packages/rtop/src/ops_lib/</path>
    <filename>RTOpPack__ROpWeightedNorm2_8hpp</filename>
    <class kind="class">RTOpPack::ROpWeightedNorm2EleWiseReduction</class>
    <class kind="class">RTOpPack::ROpWeightedNorm2</class>
    <namespace>RTOpPack</namespace>
  </compound>
  <compound kind="file">
    <name>RTOpPack_RTOpServer.hpp</name>
    <path>/Users/sscoll/dist/trilinos/packages/rtop/src/support/</path>
    <filename>RTOpPack__RTOpServer_8hpp</filename>
    <includes id="RTOpPack__RTOpServerDecl_8hpp" name="RTOpPack_RTOpServerDecl.hpp" local="yes" imported="no">RTOpPack_RTOpServerDecl.hpp</includes>
    <namespace>RTOpPack</namespace>
  </compound>
  <compound kind="file">
    <name>RTOpPack_RTOpServerDecl.hpp</name>
    <path>/Users/sscoll/dist/trilinos/packages/rtop/src/support/</path>
    <filename>RTOpPack__RTOpServerDecl_8hpp</filename>
    <class kind="class">RTOpPack::RTOpServer</class>
    <namespace>RTOpPack</namespace>
  </compound>
  <compound kind="file">
    <name>RTOpPack_RTOpSubRangeDecorator.cpp</name>
    <path>/Users/sscoll/dist/trilinos/packages/rtop/src/support/</path>
    <filename>RTOpPack__RTOpSubRangeDecorator_8cpp</filename>
    <includes id="RTOpPack__RTOpSubRangeDecorator__decl_8hpp" name="RTOpPack_RTOpSubRangeDecorator_decl.hpp" local="yes" imported="no">RTOpPack_RTOpSubRangeDecorator_decl.hpp</includes>
  </compound>
  <compound kind="file">
    <name>RTOpPack_RTOpSubRangeDecorator_decl.hpp</name>
    <path>/Users/sscoll/dist/trilinos/packages/rtop/src/support/</path>
    <filename>RTOpPack__RTOpSubRangeDecorator__decl_8hpp</filename>
    <class kind="class">RTOpPack::RTOpSubRangeDecorator</class>
    <namespace>RTOpPack</namespace>
  </compound>
  <compound kind="file">
    <name>RTOpPack_RTOpSubRangeDecorator_def.hpp</name>
    <path>/Users/sscoll/dist/trilinos/packages/rtop/src/support/</path>
    <filename>RTOpPack__RTOpSubRangeDecorator__def_8hpp</filename>
    <includes id="RTOpPack__RTOpSubRangeDecorator__decl_8hpp" name="RTOpPack_RTOpSubRangeDecorator_decl.hpp" local="yes" imported="no">RTOpPack_RTOpSubRangeDecorator_decl.hpp</includes>
    <namespace>RTOpPack</namespace>
  </compound>
  <compound kind="file">
    <name>RTOpPack_RTOpT.cpp</name>
    <path>/Users/sscoll/dist/trilinos/packages/rtop/src/interfaces/</path>
    <filename>RTOpPack__RTOpT_8cpp</filename>
    <includes id="RTOpPack__RTOpT__decl_8hpp" name="RTOpPack_RTOpT_decl.hpp" local="yes" imported="no">RTOpPack_RTOpT_decl.hpp</includes>
  </compound>
  <compound kind="file">
    <name>RTOpPack_RTOpT_decl.hpp</name>
    <path>/Users/sscoll/dist/trilinos/packages/rtop/src/interfaces/</path>
    <filename>RTOpPack__RTOpT__decl_8hpp</filename>
    <includes id="RTOpPack__Types_8hpp" name="RTOpPack_Types.hpp" local="yes" imported="no">RTOpPack_Types.hpp</includes>
    <class kind="class">RTOpPack::ReductTarget</class>
    <class kind="class">RTOpPack::RTOpT</class>
    <namespace>RTOpPack</namespace>
  </compound>
  <compound kind="file">
    <name>RTOpPack_RTOpT_def.hpp</name>
    <path>/Users/sscoll/dist/trilinos/packages/rtop/src/interfaces/</path>
    <filename>RTOpPack__RTOpT__def_8hpp</filename>
    <includes id="RTOpPack__RTOpT__decl_8hpp" name="RTOpPack_RTOpT_decl.hpp" local="yes" imported="no">RTOpPack_RTOpT_decl.hpp</includes>
    <namespace>RTOpPack</namespace>
  </compound>
  <compound kind="file">
    <name>RTOpPack_RTOpTHelpers.cpp</name>
    <path>/Users/sscoll/dist/trilinos/packages/rtop/src/support/</path>
    <filename>RTOpPack__RTOpTHelpers_8cpp</filename>
    <includes id="RTOpPack__RTOpTHelpers__decl_8hpp" name="RTOpPack_RTOpTHelpers_decl.hpp" local="yes" imported="no">RTOpPack_RTOpTHelpers_decl.hpp</includes>
  </compound>
  <compound kind="file">
    <name>RTOpPack_RTOpTHelpers_decl.hpp</name>
    <path>/Users/sscoll/dist/trilinos/packages/rtop/src/support/</path>
    <filename>RTOpPack__RTOpTHelpers__decl_8hpp</filename>
    <class kind="struct">RTOpPack::ScalarIndex</class>
    <class kind="class">RTOpPack::PrimitiveTypeTraits&lt; Scalar, ScalarIndex&lt; Scalar &gt; &gt;</class>
    <class kind="class">RTOpPack::DefaultReductTarget</class>
    <class kind="class">RTOpPack::BasicReductObjReductionOp</class>
    <class kind="class">RTOpPack::BasicReductObjReductionOp&lt; ConcreteReductObj, REDUCT_TYPE_SUM &gt;</class>
    <class kind="class">RTOpPack::BasicReductObjReductionOp&lt; ConcreteReductObj, REDUCT_TYPE_MAX &gt;</class>
    <class kind="class">RTOpPack::BasicReductObjReductionOp&lt; ConcreteReductObj, REDUCT_TYPE_MIN &gt;</class>
    <class kind="class">RTOpPack::SumScalarReductObjReduction</class>
    <class kind="class">RTOpPack::ROpScalarReductionWithOpBase</class>
    <class kind="class">RTOpPack::ROp_1_ScalarReduction</class>
    <class kind="class">RTOpPack::ROp_1_CoordVariantScalarReduction</class>
    <class kind="class">RTOpPack::ROp_2_ScalarReduction</class>
    <class kind="class">RTOpPack::TOp_0_1_Base</class>
    <class kind="class">RTOpPack::TOp_0_1_CoordVariantBase</class>
    <class kind="class">RTOpPack::TOp_1_1_Base</class>
    <class kind="class">RTOpPack::TOp_2_1_Base</class>
    <class kind="class">RTOpPack::TOp_3_1_Base</class>
    <namespace>RTOpPack</namespace>
    <member kind="define">
      <type>#define</type>
      <name>RTOP_ROP_1_REDUCT_SCALAR_CUSTOM_DEFAULT</name>
      <anchorfile>RTOpPack__RTOpTHelpers__decl_8hpp.html</anchorfile>
      <anchor>a2c6d05df0ad9be93ddf2fe5125dcc20b</anchor>
      <arglist>(ROP_CLASS_NAME, REDUCT_SCALAR, BASIC_REDUCT_TYPE_ENUM, CUSTOM_DEFAULT   )</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>RTOP_ROP_1_REDUCT_SCALAR</name>
      <anchorfile>RTOpPack__RTOpTHelpers__decl_8hpp.html</anchorfile>
      <anchor>a3e3e522d04abee5e06721af60fd2c297</anchor>
      <arglist>(ROP_CLASS_NAME, REDUCT_SCALAR, BASIC_REDUCT_TYPE_ENUM   )</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>RTOP_ROP_2_REDUCT_SCALAR</name>
      <anchorfile>RTOpPack__RTOpTHelpers__decl_8hpp.html</anchorfile>
      <anchor>aa3bf9ee28e04640fc7949302df0701cf</anchor>
      <arglist>(ROP_CLASS_NAME, REDUCT_SCALAR, BASIC_REDUCT_TYPE_ENUM   )</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>RTOP_TOP_1_1</name>
      <anchorfile>RTOpPack__RTOpTHelpers__decl_8hpp.html</anchorfile>
      <anchor>a47d9fc7246ff5b6310a1991851a63e29</anchor>
      <arglist>(TOP_CLASS_NAME)</arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>EBasicReductTypes</name>
      <anchorfile>namespaceRTOpPack.html</anchorfile>
      <anchor>a0583d57eddf0f3d901a56dc18b768655</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>REDUCT_TYPE_SUM</name>
      <anchorfile>namespaceRTOpPack.html</anchorfile>
      <anchor>a0583d57eddf0f3d901a56dc18b768655a86fc347b5848f48b253893eb42ccac87</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>REDUCT_TYPE_MAX</name>
      <anchorfile>namespaceRTOpPack.html</anchorfile>
      <anchor>a0583d57eddf0f3d901a56dc18b768655a4fa151ed466569eceb6a0712499c2c1d</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>REDUCT_TYPE_MIN</name>
      <anchorfile>namespaceRTOpPack.html</anchorfile>
      <anchor>a0583d57eddf0f3d901a56dc18b768655a47f78de745f137e44fc0f5f6ed7071f2</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>validate_apply_op</name>
      <anchorfile>namespaceRTOpPack.html</anchorfile>
      <anchor>a2a35e8756c033d8b824e81be457e0e71</anchor>
      <arglist>(const RTOpT&lt; Scalar &gt; &amp;op, const int allowed_num_sub_vecs, const int allowed_num_targ_sub_vecs, const bool expect_reduct_obj, const ArrayView&lt; const ConstSubVectorView&lt; Scalar &gt; &gt; &amp;sub_vecs, const ArrayView&lt; const SubVectorView&lt; Scalar &gt; &gt; &amp;targ_sub_vecs, const Ptr&lt; const ReductTarget &gt; &amp;reduct_obj)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>RTOpPack_RTOpTHelpers_def.hpp</name>
    <path>/Users/sscoll/dist/trilinos/packages/rtop/src/support/</path>
    <filename>RTOpPack__RTOpTHelpers__def_8hpp</filename>
    <includes id="RTOpPack__RTOpTHelpers__decl_8hpp" name="RTOpPack_RTOpTHelpers_decl.hpp" local="yes" imported="no">RTOpPack_RTOpTHelpers_decl.hpp</includes>
    <namespace>RTOpPack</namespace>
    <member kind="define">
      <type>#define</type>
      <name>RTOPPACK_RTOPT_HELPERS_DEFAULTREDUCTTARGET_INSTANT</name>
      <anchorfile>RTOpPack__RTOpTHelpers__def_8hpp.html</anchorfile>
      <anchor>aad36086bc669ce9f2bac6d8eebba6a26</anchor>
      <arglist>(SCALAR)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>RTOPPACK_RTOPT_HELPERS_INSTANT_SCALAR</name>
      <anchorfile>RTOpPack__RTOpTHelpers__def_8hpp.html</anchorfile>
      <anchor>a11bada846fc4437fc94037eb3ddb4515</anchor>
      <arglist>(SCALAR)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>RTOpPack_SparseSubVectorT.hpp</name>
    <path>/Users/sscoll/dist/trilinos/packages/rtop/src/support/</path>
    <filename>RTOpPack__SparseSubVectorT_8hpp</filename>
    <includes id="RTOpPack__Types_8hpp" name="RTOpPack_Types.hpp" local="yes" imported="no">RTOpPack_Types.hpp</includes>
    <class kind="class">RTOpPack::SparseSubVectorT</class>
    <namespace>RTOpPack</namespace>
  </compound>
  <compound kind="file">
    <name>RTOpPack_SPMD_apply_op.cpp</name>
    <path>/Users/sscoll/dist/trilinos/packages/rtop/src/support/</path>
    <filename>RTOpPack__SPMD__apply__op_8cpp</filename>
    <includes id="RTOpPack__SPMD__apply__op__decl_8hpp" name="RTOpPack_SPMD_apply_op_decl.hpp" local="yes" imported="no">RTOpPack_SPMD_apply_op_decl.hpp</includes>
    <includes id="RTOpPack__SPMD__apply__op__def_8hpp" name="RTOpPack_SPMD_apply_op_def.hpp" local="yes" imported="no">RTOpPack_SPMD_apply_op_def.hpp</includes>
  </compound>
  <compound kind="file">
    <name>RTOpPack_SPMD_apply_op_decl.hpp</name>
    <path>/Users/sscoll/dist/trilinos/packages/rtop/src/support/</path>
    <filename>RTOpPack__SPMD__apply__op__decl_8hpp</filename>
    <class kind="class">Teuchos::Comm</class>
    <class kind="class">RTOpPack::ReductTargetSerializer</class>
    <class kind="class">RTOpPack::ReductTargetReductionOp</class>
    <namespace>Teuchos</namespace>
    <namespace>RTOpPack</namespace>
    <member kind="define">
      <type>#define</type>
      <name>RTOPPACK_ENABLE_SHOW_DUMP</name>
      <anchorfile>RTOpPack__SPMD__apply__op__decl_8hpp.html</anchorfile>
      <anchor>a8c7a1e11c00920c6d68962087e1ece69</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_SPMD_apply_op_dump_out</name>
      <anchorfile>namespaceRTOpPack.html</anchorfile>
      <anchor>a79aa1319c0b2c169083658709d72a5f3</anchor>
      <arglist>(const RCP&lt; FancyOStream &gt; &amp;dumpOut)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>serializedSize</name>
      <anchorfile>namespaceRTOpPack.html</anchorfile>
      <anchor>ab4bf0e860e3a4788782b7b452d84d7c3</anchor>
      <arglist>(int num_values, int num_indexes, int num_chars)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>serialize</name>
      <anchorfile>namespaceRTOpPack.html</anchorfile>
      <anchor>a4c4bb17b58ef8668015c2bb3fa00f18e</anchor>
      <arglist>(const RTOpT&lt; Scalar &gt; &amp;op, Ordinal num_values, Ordinal num_indexes, Ordinal num_chars, const ReductTarget &amp;reduct_obj, char reduct_obj_ext[])</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>deserialize</name>
      <anchorfile>namespaceRTOpPack.html</anchorfile>
      <anchor>a43c9194b7666e79077503930013a6a50</anchor>
      <arglist>(const RTOpT&lt; Scalar &gt; &amp;op, int num_values, int num_indexes, int num_chars, const char reduct_obj_ext[], ReductTarget *reduct_obj)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SPMD_all_reduce</name>
      <anchorfile>namespaceRTOpPack.html</anchorfile>
      <anchor>abab748acdfc57f0a0c07f023112d2c2f</anchor>
      <arglist>(const Teuchos::Comm&lt; index_type &gt; *comm, const RTOpT&lt; Scalar &gt; &amp;op, const int num_cols, const ReductTarget *const i_reduct_objs[], ReductTarget *const reduct_objs[])</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SPMD_apply_op</name>
      <anchorfile>namespaceRTOpPack.html</anchorfile>
      <anchor>ad0271ea1eccddfbf6f8b0736e619d77a</anchor>
      <arglist>(const Teuchos::Comm&lt; index_type &gt; *comm, const RTOpT&lt; Scalar &gt; &amp;op, const int num_vecs, const ConstSubVectorView&lt; Scalar &gt; sub_vecs[], const int num_targ_vecs, const SubVectorView&lt; Scalar &gt; targ_sub_vecs[], ReductTarget *reduct_obj)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SPMD_apply_op</name>
      <anchorfile>namespaceRTOpPack.html</anchorfile>
      <anchor>ae5f130891cf4ef23ff7da293367069e6</anchor>
      <arglist>(const Teuchos::Comm&lt; index_type &gt; *comm, const RTOpT&lt; Scalar &gt; &amp;op, const int num_cols, const int num_multi_vecs, const ConstSubMultiVectorView&lt; Scalar &gt; sub_multi_vecs[], const int num_targ_multi_vecs, const SubMultiVectorView&lt; Scalar &gt; targ_sub_multi_vecs[], ReductTarget *const reduct_objs[])</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SPMD_apply_op</name>
      <anchorfile>namespaceRTOpPack.html</anchorfile>
      <anchor>ac1c270f15e624e9f492f38dfb8f57cb2</anchor>
      <arglist>(const Teuchos::Comm&lt; index_type &gt; *comm, const RTOpT&lt; Scalar &gt; &amp;op, const int num_cols, const int num_vecs, const ConstSubVectorView&lt; Scalar &gt; sub_vecs[], const int num_targ_vecs, const SubVectorView&lt; Scalar &gt; sub_targ_vecs[], ReductTarget *const reduct_objs[])</arglist>
    </member>
    <member kind="variable">
      <type>RTOP_DEPRECATED bool</type>
      <name>show_spmd_apply_op_dump</name>
      <anchorfile>namespaceRTOpPack.html</anchorfile>
      <anchor>aeed3bfa798acb008d1b1bf5a5a210898</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>RTOpPack_SPMD_apply_op_def.hpp</name>
    <path>/Users/sscoll/dist/trilinos/packages/rtop/src/support/</path>
    <filename>RTOpPack__SPMD__apply__op__def_8hpp</filename>
    <includes id="RTOpPack__SPMD__apply__op__decl_8hpp" name="RTOpPack_SPMD_apply_op_decl.hpp" local="yes" imported="no">RTOpPack_SPMD_apply_op_decl.hpp</includes>
    <namespace>RTOpPack</namespace>
    <member kind="define">
      <type>#define</type>
      <name>RTOPPACK_SPMD_APPLY_OP_INSTANT_SCALAR</name>
      <anchorfile>RTOpPack__SPMD__apply__op__def_8hpp.html</anchorfile>
      <anchor>adbfcd5534bcb982a5b0478329ff16b51</anchor>
      <arglist>(SCALAR)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; FancyOStream &gt; &amp;</type>
      <name>spmdApplyOpDumpOut</name>
      <anchorfile>namespaceRTOpPack.html</anchorfile>
      <anchor>a3c8fbe70e5cd7aa5c0c38a0486748b68</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>print</name>
      <anchorfile>namespaceRTOpPack.html</anchorfile>
      <anchor>a7b263b8b71b8ac53e5756a4ef7e03cb6</anchor>
      <arglist>(const ConstSubVectorView&lt; Scalar &gt; &amp;v, Teuchos::FancyOStream &amp;out_arg)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>RTOpPack_TOpAbs.hpp</name>
    <path>/Users/sscoll/dist/trilinos/packages/rtop/src/ops_lib/</path>
    <filename>RTOpPack__TOpAbs_8hpp</filename>
    <namespace>RTOpPack</namespace>
    <member kind="function">
      <type></type>
      <name>RTOP_TOP_1_1</name>
      <anchorfile>namespaceRTOpPack.html</anchorfile>
      <anchor>ac8f14f954cb91c8b7ccabfd14adedcee</anchor>
      <arglist>(TOpAbs)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>RTOpPack_TOpAddScalar.hpp</name>
    <path>/Users/sscoll/dist/trilinos/packages/rtop/src/ops_lib/</path>
    <filename>RTOpPack__TOpAddScalar_8hpp</filename>
    <class kind="class">RTOpPack::TOpAddScalarEleWiseTransformation</class>
    <class kind="class">RTOpPack::TOpAddScalar</class>
    <namespace>RTOpPack</namespace>
  </compound>
  <compound kind="file">
    <name>RTOpPack_TOpAssignScalar.hpp</name>
    <path>/Users/sscoll/dist/trilinos/packages/rtop/src/ops_lib/</path>
    <filename>RTOpPack__TOpAssignScalar_8hpp</filename>
    <class kind="class">RTOpPack::TOpAssignScalarEleWiseTransformation</class>
    <class kind="class">RTOpPack::TOpAssignScalar</class>
    <namespace>RTOpPack</namespace>
  </compound>
  <compound kind="file">
    <name>RTOpPack_TOpAssignVectors.hpp</name>
    <path>/Users/sscoll/dist/trilinos/packages/rtop/src/ops_lib/</path>
    <filename>RTOpPack__TOpAssignVectors_8hpp</filename>
    <namespace>RTOpPack</namespace>
    <member kind="function">
      <type></type>
      <name>RTOP_TOP_1_1</name>
      <anchorfile>namespaceRTOpPack.html</anchorfile>
      <anchor>ac7eec09c3900fd08715afab7c7874916</anchor>
      <arglist>(TOpAssignVectors)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>RTOpPack_TOpAXPY.hpp</name>
    <path>/Users/sscoll/dist/trilinos/packages/rtop/src/ops_lib/</path>
    <filename>RTOpPack__TOpAXPY_8hpp</filename>
    <class kind="class">RTOpPack::TOpAXPYEleWiseTransformation</class>
    <class kind="class">RTOpPack::TOpAXPY</class>
    <namespace>RTOpPack</namespace>
  </compound>
  <compound kind="file">
    <name>RTOpPack_TOpEleWiseConjProd.hpp</name>
    <path>/Users/sscoll/dist/trilinos/packages/rtop/src/ops_lib/</path>
    <filename>RTOpPack__TOpEleWiseConjProd_8hpp</filename>
    <class kind="class">RTOpPack::TOpEleWiseConjProdEleWiseTransformation</class>
    <class kind="class">RTOpPack::TOpEleWiseConjProd</class>
    <namespace>RTOpPack</namespace>
  </compound>
  <compound kind="file">
    <name>RTOpPack_TOpEleWiseDivide.hpp</name>
    <path>/Users/sscoll/dist/trilinos/packages/rtop/src/ops_lib/</path>
    <filename>RTOpPack__TOpEleWiseDivide_8hpp</filename>
    <class kind="class">RTOpPack::TOpEleWiseDivideEleWiseTransformation</class>
    <class kind="class">RTOpPack::TOpEleWiseDivide</class>
    <namespace>RTOpPack</namespace>
  </compound>
  <compound kind="file">
    <name>RTOpPack_TOpEleWiseProd.hpp</name>
    <path>/Users/sscoll/dist/trilinos/packages/rtop/src/ops_lib/</path>
    <filename>RTOpPack__TOpEleWiseProd_8hpp</filename>
    <class kind="class">RTOpPack::TOpEleWiseProdEleWiseTransformation</class>
    <class kind="class">RTOpPack::TOpEleWiseProd</class>
    <namespace>RTOpPack</namespace>
  </compound>
  <compound kind="file">
    <name>RTOpPack_TOpEleWiseProdUpdate.hpp</name>
    <path>/Users/sscoll/dist/trilinos/packages/rtop/src/ops_lib/</path>
    <filename>RTOpPack__TOpEleWiseProdUpdate_8hpp</filename>
    <class kind="class">RTOpPack::TOpEleWiseProdUpdateEleWiseTransformation</class>
    <class kind="class">RTOpPack::TOpEleWiseProdUpdate</class>
    <namespace>RTOpPack</namespace>
  </compound>
  <compound kind="file">
    <name>RTOpPack_TOpEleWiseScale.hpp</name>
    <path>/Users/sscoll/dist/trilinos/packages/rtop/src/ops_lib/</path>
    <filename>RTOpPack__TOpEleWiseScale_8hpp</filename>
    <class kind="class">RTOpPack::TOpEleWiseScaleEleWiseTransformation</class>
    <class kind="class">RTOpPack::TOpEleWiseScale</class>
    <namespace>RTOpPack</namespace>
  </compound>
  <compound kind="file">
    <name>RTOpPack_TOpLinearCombination.cpp</name>
    <path>/Users/sscoll/dist/trilinos/packages/rtop/src/ops_lib/</path>
    <filename>RTOpPack__TOpLinearCombination_8cpp</filename>
  </compound>
  <compound kind="file">
    <name>RTOpPack_TOpLinearCombination_decl.hpp</name>
    <path>/Users/sscoll/dist/trilinos/packages/rtop/src/ops_lib/</path>
    <filename>RTOpPack__TOpLinearCombination__decl_8hpp</filename>
    <class kind="class">RTOpPack::TOpLinearCombination</class>
    <namespace>RTOpPack</namespace>
  </compound>
  <compound kind="file">
    <name>RTOpPack_TOpLinearCombination_def.hpp</name>
    <path>/Users/sscoll/dist/trilinos/packages/rtop/src/ops_lib/</path>
    <filename>RTOpPack__TOpLinearCombination__def_8hpp</filename>
    <namespace>RTOpPack</namespace>
  </compound>
  <compound kind="file">
    <name>RTOpPack_TOpRandomize.hpp</name>
    <path>/Users/sscoll/dist/trilinos/packages/rtop/src/ops_lib/</path>
    <filename>RTOpPack__TOpRandomize_8hpp</filename>
    <class kind="class">RTOpPack::TOpRandomize</class>
    <namespace>RTOpPack</namespace>
  </compound>
  <compound kind="file">
    <name>RTOpPack_TOpReciprocal.hpp</name>
    <path>/Users/sscoll/dist/trilinos/packages/rtop/src/ops_lib/</path>
    <filename>RTOpPack__TOpReciprocal_8hpp</filename>
    <namespace>RTOpPack</namespace>
    <member kind="function">
      <type></type>
      <name>RTOP_TOP_1_1</name>
      <anchorfile>namespaceRTOpPack.html</anchorfile>
      <anchor>ae94e5c3710a816d7606dfc1076837a6e</anchor>
      <arglist>(TOpReciprocal)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>RTOpPack_TOpScaleVector.hpp</name>
    <path>/Users/sscoll/dist/trilinos/packages/rtop/src/ops_lib/</path>
    <filename>RTOpPack__TOpScaleVector_8hpp</filename>
    <class kind="class">RTOpPack::TOpScaleVectorEleWiseTransformation</class>
    <class kind="class">RTOpPack::TOpScaleVector</class>
    <namespace>RTOpPack</namespace>
  </compound>
  <compound kind="file">
    <name>RTOpPack_TOpSetAssendingValues.hpp</name>
    <path>/Users/sscoll/dist/trilinos/packages/rtop/src/ops_lib/</path>
    <filename>RTOpPack__TOpSetAssendingValues_8hpp</filename>
    <class kind="class">RTOpPack::TOpSetAssendingValuesEleWiseTransformation</class>
    <class kind="class">RTOpPack::TOpSetAssendingValues</class>
    <namespace>RTOpPack</namespace>
  </compound>
  <compound kind="file">
    <name>RTOpPack_TOpSetElement.hpp</name>
    <path>/Users/sscoll/dist/trilinos/packages/rtop/src/ops_lib/</path>
    <filename>RTOpPack__TOpSetElement_8hpp</filename>
    <class kind="class">RTOpPack::TOpSetElementEleWiseTransformation</class>
    <class kind="class">RTOpPack::TOpSetElement</class>
    <namespace>RTOpPack</namespace>
  </compound>
  <compound kind="file">
    <name>RTOpPack_TOpSetSubVector.cpp</name>
    <path>/Users/sscoll/dist/trilinos/packages/rtop/src/ops_lib/</path>
    <filename>RTOpPack__TOpSetSubVector_8cpp</filename>
    <includes id="RTOpPack__TOpSetSubVector_8hpp" name="RTOpPack_TOpSetSubVector.hpp" local="yes" imported="no">RTOpPack_TOpSetSubVector.hpp</includes>
  </compound>
  <compound kind="file">
    <name>RTOpPack_TOpSetSubVector.hpp</name>
    <path>/Users/sscoll/dist/trilinos/packages/rtop/src/ops_lib/</path>
    <filename>RTOpPack__TOpSetSubVector_8hpp</filename>
    <includes id="RTOpPack__SparseSubVectorT_8hpp" name="RTOpPack_SparseSubVectorT.hpp" local="yes" imported="no">RTOpPack_SparseSubVectorT.hpp</includes>
    <includes id="RTOpPack__TOpSetSubVector__def_8hpp" name="RTOpPack_TOpSetSubVector_def.hpp" local="yes" imported="no">RTOpPack_TOpSetSubVector_def.hpp</includes>
    <class kind="class">RTOpPack::TOpSetSubVector</class>
    <namespace>RTOpPack</namespace>
  </compound>
  <compound kind="file">
    <name>RTOpPack_TOpSetSubVector_def.hpp</name>
    <path>/Users/sscoll/dist/trilinos/packages/rtop/src/ops_lib/</path>
    <filename>RTOpPack__TOpSetSubVector__def_8hpp</filename>
    <namespace>RTOpPack</namespace>
  </compound>
  <compound kind="file">
    <name>RTOpPack_TOpUnaryFuncPtr.hpp</name>
    <path>/Users/sscoll/dist/trilinos/packages/rtop/src/support/</path>
    <filename>RTOpPack__TOpUnaryFuncPtr_8hpp</filename>
    <includes id="RTOpPack__TOpUnaryFuncPtrDecl_8hpp" name="RTOpPack_TOpUnaryFuncPtrDecl.hpp" local="yes" imported="no">RTOpPack_TOpUnaryFuncPtrDecl.hpp</includes>
    <namespace>RTOpPack</namespace>
  </compound>
  <compound kind="file">
    <name>RTOpPack_TOpUnaryFuncPtrDecl.hpp</name>
    <path>/Users/sscoll/dist/trilinos/packages/rtop/src/support/</path>
    <filename>RTOpPack__TOpUnaryFuncPtrDecl_8hpp</filename>
    <class kind="class">RTOpPack::TOpUnaryFuncPtr</class>
    <namespace>RTOpPack</namespace>
  </compound>
  <compound kind="file">
    <name>RTOpPack_Types.hpp</name>
    <path>/Users/sscoll/dist/trilinos/packages/rtop/src/interfaces/</path>
    <filename>RTOpPack__Types_8hpp</filename>
    <includes id="RTOp__ConfigDefs_8hpp" name="RTOp_ConfigDefs.hpp" local="yes" imported="no">RTOp_ConfigDefs.hpp</includes>
    <class kind="class">RTOpPack::UnknownError</class>
    <class kind="class">RTOpPack::InvalidUsage</class>
    <class kind="class">RTOpPack::InvalidNumVecs</class>
    <class kind="class">RTOpPack::InvalidNumTargVecs</class>
    <class kind="class">RTOpPack::IncompatibleVecs</class>
    <class kind="class">RTOpPack::IncompatibleReductObj</class>
    <class kind="class">RTOpPack::ConstSubVectorView</class>
    <class kind="class">RTOpPack::SubVectorView</class>
    <class kind="class">RTOpPack::ConstSubMultiVectorView</class>
    <class kind="class">RTOpPack::SubMultiVectorView</class>
    <class kind="class">RTOpPack::PrimitiveTypeTraits</class>
    <class kind="class">RTOpPack::PrimitiveTypeTraits&lt; Scalar, Scalar &gt;</class>
    <class kind="class">RTOpPack::PrimitiveTypeTraits&lt; Scalar, index_type &gt;</class>
    <class kind="class">RTOpPack::RTOpT</class>
    <namespace>RTOpPack</namespace>
    <member kind="typedef">
      <type>Teuchos_Ordinal</type>
      <name>Ordinal</name>
      <anchorfile>namespaceRTOpPack.html</anchorfile>
      <anchor>a2748f9607cdb199b78e4fb3b1a0675c3</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Teuchos_Ordinal</type>
      <name>index_type</name>
      <anchorfile>namespaceRTOpPack.html</anchorfile>
      <anchor>a1ca78b0d4ddf52dc7f710bcca904b701</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>char</type>
      <name>char_type</name>
      <anchorfile>namespaceRTOpPack.html</anchorfile>
      <anchor>a6233a6700d436c31330a2a6d03750c40</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>assign_entries</name>
      <anchorfile>namespaceRTOpPack.html</anchorfile>
      <anchor>aaa21a11cf366b2ba786bd5e52678b4a2</anchor>
      <arglist>(const Ptr&lt; const SubVectorView&lt; Scalar &gt; &gt; &amp;msv, const ConstSubVectorView&lt; Scalar &gt; &amp;sv)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>assign_entries</name>
      <anchorfile>namespaceRTOpPack.html</anchorfile>
      <anchor>af3cb072a2b8d5123d616ba4057dd72b9</anchor>
      <arglist>(const Ptr&lt; const SubMultiVectorView&lt; Scalar &gt; &gt; &amp;msmv, const ConstSubMultiVectorView&lt; Scalar &gt; &amp;smv)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>RTOpPack_version.cpp</name>
    <path>/Users/sscoll/dist/trilinos/packages/rtop/src/</path>
    <filename>RTOpPack__version_8cpp</filename>
    <includes id="RTOpPack__version_8hpp" name="RTOpPack_version.hpp" local="yes" imported="no">RTOpPack_version.hpp</includes>
  </compound>
  <compound kind="file">
    <name>RTOpPack_version.hpp</name>
    <path>/Users/sscoll/dist/trilinos/packages/rtop/src/</path>
    <filename>RTOpPack__version_8hpp</filename>
    <includes id="RTOp__ConfigDefs_8hpp" name="RTOp_ConfigDefs.hpp" local="yes" imported="no">RTOp_ConfigDefs.hpp</includes>
    <namespace>RTOpPack</namespace>
    <member kind="function">
      <type>std::string</type>
      <name>version</name>
      <anchorfile>namespaceRTOpPack.html</anchorfile>
      <anchor>a377a459e637d300395ab32f30c225284</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>RTOpPack::BasicReductObjReductionOp</name>
    <filename>classRTOpPack_1_1BasicReductObjReductionOp.html</filename>
    <templarg></templarg>
    <templarg>ReductionType</templarg>
    <member kind="function">
      <type>void</type>
      <name>operator()</name>
      <anchorfile>classRTOpPack_1_1BasicReductObjReductionOp.html</anchorfile>
      <anchor>aa8b7b99c83e639a60041f1770383b2d3</anchor>
      <arglist>(const ConcreteReductObj &amp;in_reduct, ConcreteReductObj &amp;inout_reduct) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>RTOpPack::BasicReductObjReductionOp&lt; ConcreteReductObj, REDUCT_TYPE_MAX &gt;</name>
    <filename>classRTOpPack_1_1BasicReductObjReductionOp_3_01ConcreteReductObj_00_01REDUCT__TYPE__MAX_01_4.html</filename>
    <templarg></templarg>
    <member kind="function">
      <type>void</type>
      <name>operator()</name>
      <anchorfile>classRTOpPack_1_1BasicReductObjReductionOp_3_01ConcreteReductObj_00_01REDUCT__TYPE__MAX_01_4.html</anchorfile>
      <anchor>acd218d6201f1516c0e92b9ee57ddefda</anchor>
      <arglist>(const ConcreteReductObj &amp;in_reduct, ConcreteReductObj &amp;inout_reduct) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>RTOpPack::BasicReductObjReductionOp&lt; ConcreteReductObj, REDUCT_TYPE_MIN &gt;</name>
    <filename>classRTOpPack_1_1BasicReductObjReductionOp_3_01ConcreteReductObj_00_01REDUCT__TYPE__MIN_01_4.html</filename>
    <templarg></templarg>
    <member kind="function">
      <type>void</type>
      <name>operator()</name>
      <anchorfile>classRTOpPack_1_1BasicReductObjReductionOp_3_01ConcreteReductObj_00_01REDUCT__TYPE__MIN_01_4.html</anchorfile>
      <anchor>aa0c8c12cb7581da2661834cdfc618087</anchor>
      <arglist>(const ConcreteReductObj &amp;in_reduct, ConcreteReductObj &amp;inout_reduct) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>RTOpPack::BasicReductObjReductionOp&lt; ConcreteReductObj, REDUCT_TYPE_SUM &gt;</name>
    <filename>classRTOpPack_1_1BasicReductObjReductionOp_3_01ConcreteReductObj_00_01REDUCT__TYPE__SUM_01_4.html</filename>
    <templarg></templarg>
    <member kind="function">
      <type>void</type>
      <name>operator()</name>
      <anchorfile>classRTOpPack_1_1BasicReductObjReductionOp_3_01ConcreteReductObj_00_01REDUCT__TYPE__SUM_01_4.html</anchorfile>
      <anchor>a1624452498d51883aaeffcf21aa4aada</anchor>
      <arglist>(const ConcreteReductObj &amp;in_reduct, ConcreteReductObj &amp;inout_reduct) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Teuchos::Comm</name>
    <filename>classTeuchos_1_1Comm.html</filename>
    <templarg></templarg>
  </compound>
  <compound kind="class">
    <name>RTOpPack::ConstSubMultiVectorView</name>
    <filename>classRTOpPack_1_1ConstSubMultiVectorView.html</filename>
    <templarg>Scalar</templarg>
    <member kind="function">
      <type></type>
      <name>ConstSubMultiVectorView</name>
      <anchorfile>classRTOpPack_1_1ConstSubMultiVectorView.html</anchorfile>
      <anchor>a06671131eed2b2e41886a3e6f58b93ce</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ConstSubMultiVectorView</name>
      <anchorfile>classRTOpPack_1_1ConstSubMultiVectorView.html</anchorfile>
      <anchor>a89fcdfc32d434d094bdef2d90d4696d3</anchor>
      <arglist>(Ordinal globalOffset_in, Ordinal subDim_in, Ordinal colOffset_in, Ordinal numSubCols_in, const ArrayRCP&lt; const Scalar &gt; &amp;values_in, Ordinal leadingDim_in)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ConstSubMultiVectorView</name>
      <anchorfile>classRTOpPack_1_1ConstSubMultiVectorView.html</anchorfile>
      <anchor>ac59f14617098e01cb50fe8ed4547efd6</anchor>
      <arglist>(const ConstSubMultiVectorView&lt; Scalar &gt; &amp;smv)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initialize</name>
      <anchorfile>classRTOpPack_1_1ConstSubMultiVectorView.html</anchorfile>
      <anchor>a435021978a701627a8473f632f4c545d</anchor>
      <arglist>(Ordinal globalOffset_in, Ordinal subDim_in, Ordinal colOffset_in, Ordinal numSubCols_in, const ArrayRCP&lt; const Scalar &gt; &amp;values_in, Ordinal leadingDim_in)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>uninitialize</name>
      <anchorfile>classRTOpPack_1_1ConstSubMultiVectorView.html</anchorfile>
      <anchor>a62ddaa5c4019211e8bda412d1a1a9868</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setGlobalOffset</name>
      <anchorfile>classRTOpPack_1_1ConstSubMultiVectorView.html</anchorfile>
      <anchor>a6fbfba1b15d868aa2d2e6d5910e2c6fd</anchor>
      <arglist>(Ordinal globalOffset_in)</arglist>
    </member>
    <member kind="function">
      <type>Ordinal</type>
      <name>globalOffset</name>
      <anchorfile>classRTOpPack_1_1ConstSubMultiVectorView.html</anchorfile>
      <anchor>acff58f7092d52c10950f99e4947a18a7</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Ordinal</type>
      <name>subDim</name>
      <anchorfile>classRTOpPack_1_1ConstSubMultiVectorView.html</anchorfile>
      <anchor>a9dd5e38a38ff04e008bbdcc264416e3e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Ordinal</type>
      <name>colOffset</name>
      <anchorfile>classRTOpPack_1_1ConstSubMultiVectorView.html</anchorfile>
      <anchor>af302457440e9cbaa690b0db347583f5a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Ordinal</type>
      <name>numSubCols</name>
      <anchorfile>classRTOpPack_1_1ConstSubMultiVectorView.html</anchorfile>
      <anchor>adbcf0c2c7a4bb51f3b7e63795338538a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const ArrayRCP&lt; const Scalar &gt;</type>
      <name>values</name>
      <anchorfile>classRTOpPack_1_1ConstSubMultiVectorView.html</anchorfile>
      <anchor>ad1744d59bdc8b8bd90e5ba854c7d8e94</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Ordinal</type>
      <name>leadingDim</name>
      <anchorfile>classRTOpPack_1_1ConstSubMultiVectorView.html</anchorfile>
      <anchor>a87e4080c8d3fc73261cb8e4a78959508</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Scalar &amp;</type>
      <name>operator()</name>
      <anchorfile>classRTOpPack_1_1ConstSubMultiVectorView.html</anchorfile>
      <anchor>ae2c40dd787ae6f59a617f05ec0abe7f8</anchor>
      <arglist>(Ordinal i, Ordinal j) const </arglist>
    </member>
    <member kind="function">
      <type>ConstSubVectorView&lt; Scalar &gt;</type>
      <name>col</name>
      <anchorfile>classRTOpPack_1_1ConstSubMultiVectorView.html</anchorfile>
      <anchor>ad934a7af7617a3b3c11ed6f670c46fd6</anchor>
      <arglist>(const Ordinal j) const </arglist>
    </member>
    <member kind="variable" protection="private">
      <type>Ordinal</type>
      <name>globalOffset_</name>
      <anchorfile>classRTOpPack_1_1ConstSubMultiVectorView.html</anchorfile>
      <anchor>a88ade21cf82d42628d0a03ae4ecdcca5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>Ordinal</type>
      <name>subDim_</name>
      <anchorfile>classRTOpPack_1_1ConstSubMultiVectorView.html</anchorfile>
      <anchor>ad4cccd0aaebc760fcb1b202e9f1b9e24</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>Ordinal</type>
      <name>colOffset_</name>
      <anchorfile>classRTOpPack_1_1ConstSubMultiVectorView.html</anchorfile>
      <anchor>ae351f140319f3f72d679ca3e39267b53</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>Ordinal</type>
      <name>numSubCols_</name>
      <anchorfile>classRTOpPack_1_1ConstSubMultiVectorView.html</anchorfile>
      <anchor>ac6de0396562999e2f47663ee6d652a5b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>ArrayRCP&lt; const Scalar &gt;</type>
      <name>values_</name>
      <anchorfile>classRTOpPack_1_1ConstSubMultiVectorView.html</anchorfile>
      <anchor>a6997f7a1c83f54e140cdcbd1a119a8f0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>Ordinal</type>
      <name>leadingDim_</name>
      <anchorfile>classRTOpPack_1_1ConstSubMultiVectorView.html</anchorfile>
      <anchor>a2cc3c47254d5afdd82e7d93e95d32942</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>RTOpPack::ConstSubVectorView</name>
    <filename>classRTOpPack_1_1ConstSubVectorView.html</filename>
    <templarg>Scalar</templarg>
    <member kind="function">
      <type></type>
      <name>ConstSubVectorView</name>
      <anchorfile>classRTOpPack_1_1ConstSubVectorView.html</anchorfile>
      <anchor>a2ea1d12a0b57c608d86b3c75744986f7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ConstSubVectorView</name>
      <anchorfile>classRTOpPack_1_1ConstSubVectorView.html</anchorfile>
      <anchor>a9a706b89a5e2c1078b59edfe39b9142d</anchor>
      <arglist>(const ArrayRCP&lt; const Scalar &gt; &amp;values_in)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ConstSubVectorView</name>
      <anchorfile>classRTOpPack_1_1ConstSubVectorView.html</anchorfile>
      <anchor>a06f39b26905c75f408a10aaf09c41a61</anchor>
      <arglist>(Ordinal globalOffset_in, Ordinal subDim_in, const ArrayRCP&lt; const Scalar &gt; &amp;values_in, ptrdiff_t stride_in)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ConstSubVectorView</name>
      <anchorfile>classRTOpPack_1_1ConstSubVectorView.html</anchorfile>
      <anchor>a7683f6dce7847efd2efd10f805c93952</anchor>
      <arglist>(const ConstSubVectorView&lt; Scalar &gt; &amp;sv)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initialize</name>
      <anchorfile>classRTOpPack_1_1ConstSubVectorView.html</anchorfile>
      <anchor>ac8f9ee3c6326bd7bd21362564befb03a</anchor>
      <arglist>(Ordinal globalOffset_in, Ordinal subDim_in, const ArrayRCP&lt; const Scalar &gt; &amp;values_in, ptrdiff_t stride_in)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>uninitialize</name>
      <anchorfile>classRTOpPack_1_1ConstSubVectorView.html</anchorfile>
      <anchor>a98bcfa680895c47f7b32203d6ef472db</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setGlobalOffset</name>
      <anchorfile>classRTOpPack_1_1ConstSubVectorView.html</anchorfile>
      <anchor>a291448f924f1534d7e1033b847c2f992</anchor>
      <arglist>(Ordinal globalOffset_in)</arglist>
    </member>
    <member kind="function">
      <type>Ordinal</type>
      <name>globalOffset</name>
      <anchorfile>classRTOpPack_1_1ConstSubVectorView.html</anchorfile>
      <anchor>a0ba3d47be050fd13c9f8da9ca86aec8a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Ordinal</type>
      <name>subDim</name>
      <anchorfile>classRTOpPack_1_1ConstSubVectorView.html</anchorfile>
      <anchor>a992741a5d6ebf1d7a57ae15e631a1744</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const ArrayRCP&lt; const Scalar &gt;</type>
      <name>values</name>
      <anchorfile>classRTOpPack_1_1ConstSubVectorView.html</anchorfile>
      <anchor>a0341037f56bec412acaa40b5d88adc8a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>ptrdiff_t</type>
      <name>stride</name>
      <anchorfile>classRTOpPack_1_1ConstSubVectorView.html</anchorfile>
      <anchor>ad1c5bc5f548bfa4c5667523269f7b3c0</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Scalar &amp;</type>
      <name>operator[]</name>
      <anchorfile>classRTOpPack_1_1ConstSubVectorView.html</anchorfile>
      <anchor>a57a77fdc1a260e08484b596348362150</anchor>
      <arglist>(Ordinal i) const </arglist>
    </member>
    <member kind="function">
      <type>const Scalar &amp;</type>
      <name>operator()</name>
      <anchorfile>classRTOpPack_1_1ConstSubVectorView.html</anchorfile>
      <anchor>a9a33c3d39af666ab90c2c70a83bddadf</anchor>
      <arglist>(Ordinal i) const </arglist>
    </member>
    <member kind="function" protection="private">
      <type>const ArrayRCP&lt; const Scalar &gt;::iterator</type>
      <name>valuesBegin</name>
      <anchorfile>classRTOpPack_1_1ConstSubVectorView.html</anchorfile>
      <anchor>a3d078482318c9c52cbbbc6a41d5abcff</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="variable" protection="private">
      <type>Ordinal</type>
      <name>globalOffset_</name>
      <anchorfile>classRTOpPack_1_1ConstSubVectorView.html</anchorfile>
      <anchor>a59620fb29630da75dcfbf521e2a70bba</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>Ordinal</type>
      <name>subDim_</name>
      <anchorfile>classRTOpPack_1_1ConstSubVectorView.html</anchorfile>
      <anchor>a48c74ef439f58452d9fa8b86dc744bfe</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>ArrayRCP&lt; const Scalar &gt;</type>
      <name>values_</name>
      <anchorfile>classRTOpPack_1_1ConstSubVectorView.html</anchorfile>
      <anchor>a7033223dbf52fbcf46432952730e615b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>ptrdiff_t</type>
      <name>stride_</name>
      <anchorfile>classRTOpPack_1_1ConstSubVectorView.html</anchorfile>
      <anchor>acdd6d305dfffc970347c04f8dda53ecd</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>std::ostream &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>classRTOpPack_1_1ConstSubVectorView.html</anchorfile>
      <anchor>ac281c7853e26759d783e288b68267f28</anchor>
      <arglist>(std::ostream &amp;out, const ConstSubVectorView&lt; Scalar &gt; &amp;sv)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>RTOpPack::DefaultReductTarget</name>
    <filename>classRTOpPack_1_1DefaultReductTarget.html</filename>
    <templarg></templarg>
    <base>RTOpPack::ReductTarget</base>
    <member kind="function">
      <type></type>
      <name>DefaultReductTarget</name>
      <anchorfile>classRTOpPack_1_1DefaultReductTarget.html</anchorfile>
      <anchor>abff53e046562f0c6cc45502f244b0afb</anchor>
      <arglist>(const ConcreteReductObj &amp;concreteReductObj)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set</name>
      <anchorfile>classRTOpPack_1_1DefaultReductTarget.html</anchorfile>
      <anchor>a428f0aaa00db4f2022e88d50a6bfd1bf</anchor>
      <arglist>(const ConcreteReductObj &amp;concreteReductObj)</arglist>
    </member>
    <member kind="function">
      <type>const ConcreteReductObj &amp;</type>
      <name>get</name>
      <anchorfile>classRTOpPack_1_1DefaultReductTarget.html</anchorfile>
      <anchor>aad0326812b43043771c7fc6144aa4456</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>description</name>
      <anchorfile>classRTOpPack_1_1DefaultReductTarget.html</anchorfile>
      <anchor>aebaeeca9077809babfdafddfa87cee73</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="variable" protection="private">
      <type>ConcreteReductObj</type>
      <name>concreteReductObj_</name>
      <anchorfile>classRTOpPack_1_1DefaultReductTarget.html</anchorfile>
      <anchor>a19d498088ae1d95a493f6ecb465e0249</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>const RCP&lt; DefaultReductTarget&lt; ConcreteReductObj &gt; &gt;</type>
      <name>defaultReductTarget</name>
      <anchorfile>classRTOpPack_1_1DefaultReductTarget.html</anchorfile>
      <anchor>a007d2e9a229363bb514ae152957d19f3</anchor>
      <arglist>(const ConcreteReductObj &amp;concreteReductObj)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>RTOpPack::IncompatibleReductObj</name>
    <filename>classRTOpPack_1_1IncompatibleReductObj.html</filename>
    <member kind="function">
      <type></type>
      <name>IncompatibleReductObj</name>
      <anchorfile>classRTOpPack_1_1IncompatibleReductObj.html</anchorfile>
      <anchor>a25e679ebe7331a46abcb92c41bb4674a</anchor>
      <arglist>(const std::string &amp;what_arg)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>RTOpPack::IncompatibleVecs</name>
    <filename>classRTOpPack_1_1IncompatibleVecs.html</filename>
    <member kind="function">
      <type></type>
      <name>IncompatibleVecs</name>
      <anchorfile>classRTOpPack_1_1IncompatibleVecs.html</anchorfile>
      <anchor>a6885c6d80d273383c228abe5410ad114</anchor>
      <arglist>(const std::string &amp;what_arg)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>RTOpPack::InvalidNumTargVecs</name>
    <filename>classRTOpPack_1_1InvalidNumTargVecs.html</filename>
    <member kind="function">
      <type></type>
      <name>InvalidNumTargVecs</name>
      <anchorfile>classRTOpPack_1_1InvalidNumTargVecs.html</anchorfile>
      <anchor>a70ed0aeb264e061d0cd36557780c0ec3</anchor>
      <arglist>(const std::string &amp;what_arg)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>RTOpPack::InvalidNumVecs</name>
    <filename>classRTOpPack_1_1InvalidNumVecs.html</filename>
    <member kind="function">
      <type></type>
      <name>InvalidNumVecs</name>
      <anchorfile>classRTOpPack_1_1InvalidNumVecs.html</anchorfile>
      <anchor>ae4394509868be80f4b0893e9ef3183f9</anchor>
      <arglist>(const std::string &amp;what_arg)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>RTOpPack::InvalidUsage</name>
    <filename>classRTOpPack_1_1InvalidUsage.html</filename>
    <member kind="function">
      <type></type>
      <name>InvalidUsage</name>
      <anchorfile>classRTOpPack_1_1InvalidUsage.html</anchorfile>
      <anchor>af40a9c719f3715127af9f0b680041b68</anchor>
      <arglist>(const std::string &amp;what_arg)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>RTOpPack::PrimitiveTypeTraits</name>
    <filename>classRTOpPack_1_1PrimitiveTypeTraits.html</filename>
    <templarg>Scalar</templarg>
    <templarg>ConcreteObj</templarg>
    <member kind="typedef">
      <type>Scalar</type>
      <name>primitiveType</name>
      <anchorfile>classRTOpPack_1_1PrimitiveTypeTraits.html</anchorfile>
      <anchor>a4bf5a6b79378a62a3e768e7cc303025f</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" static="yes">
      <type>static int</type>
      <name>numPrimitiveObjs</name>
      <anchorfile>classRTOpPack_1_1PrimitiveTypeTraits.html</anchorfile>
      <anchor>a7dc3268a3cdcf4b37d019c9bec2ac337</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static int</type>
      <name>numIndexObjs</name>
      <anchorfile>classRTOpPack_1_1PrimitiveTypeTraits.html</anchorfile>
      <anchor>aab0194916dfa6ed678014398c7d86234</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static int</type>
      <name>numCharObjs</name>
      <anchorfile>classRTOpPack_1_1PrimitiveTypeTraits.html</anchorfile>
      <anchor>a454f7d46921951bbfdea58a6598a46e9</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>extractPrimitiveObjs</name>
      <anchorfile>classRTOpPack_1_1PrimitiveTypeTraits.html</anchorfile>
      <anchor>a0703a6363806bc3748b83b3268e066b6</anchor>
      <arglist>(const Scalar &amp;obj, const ArrayView&lt; primitiveType &gt; &amp;primitiveObjs, const ArrayView&lt; index_type &gt; &amp;indexObjs, const ArrayView&lt; char &gt; &amp;charObjs)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>loadPrimitiveObjs</name>
      <anchorfile>classRTOpPack_1_1PrimitiveTypeTraits.html</anchorfile>
      <anchor>ae9666435a26a7ed9a3783f8f23696d7d</anchor>
      <arglist>(const ArrayView&lt; const primitiveType &gt; &amp;primitiveObjs, const ArrayView&lt; const index_type &gt; &amp;indexObjs, const ArrayView&lt; const char &gt; &amp;charObjs, const Ptr&lt; Scalar &gt; &amp;obj)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>RTOpPack::PrimitiveTypeTraits&lt; Scalar, index_type &gt;</name>
    <filename>classRTOpPack_1_1PrimitiveTypeTraits_3_01Scalar_00_01index__type_01_4.html</filename>
    <templarg></templarg>
    <member kind="typedef">
      <type>PrimitiveTypeTraits&lt; Scalar, Scalar &gt;</type>
      <name>ScalarPrimitiveTypeTraits</name>
      <anchorfile>classRTOpPack_1_1PrimitiveTypeTraits_3_01Scalar_00_01index__type_01_4.html</anchorfile>
      <anchor>a23710c025634e3fd2bf9505cee7e0c57</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>ScalarPrimitiveTypeTraits::primitiveType</type>
      <name>primitiveType</name>
      <anchorfile>classRTOpPack_1_1PrimitiveTypeTraits_3_01Scalar_00_01index__type_01_4.html</anchorfile>
      <anchor>a8bb47070bdc5ab4335669c8af1f52431</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" static="yes">
      <type>static int</type>
      <name>numPrimitiveObjs</name>
      <anchorfile>classRTOpPack_1_1PrimitiveTypeTraits_3_01Scalar_00_01index__type_01_4.html</anchorfile>
      <anchor>acdc7bab11f2243913c772cf31d8364d1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static int</type>
      <name>numIndexObjs</name>
      <anchorfile>classRTOpPack_1_1PrimitiveTypeTraits_3_01Scalar_00_01index__type_01_4.html</anchorfile>
      <anchor>a49f5380de0988af07355c4f13987cda1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static int</type>
      <name>numCharObjs</name>
      <anchorfile>classRTOpPack_1_1PrimitiveTypeTraits_3_01Scalar_00_01index__type_01_4.html</anchorfile>
      <anchor>a9b76c0f8d8ceeff07688814eced09682</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>extractPrimitiveObjs</name>
      <anchorfile>classRTOpPack_1_1PrimitiveTypeTraits_3_01Scalar_00_01index__type_01_4.html</anchorfile>
      <anchor>acf0827b0286b67195cadd99fcbe3fe85</anchor>
      <arglist>(const index_type &amp;obj, const ArrayView&lt; primitiveType &gt; &amp;primitiveObjs, const ArrayView&lt; index_type &gt; &amp;indexObjs, const ArrayView&lt; char &gt; &amp;charObjs)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>loadPrimitiveObjs</name>
      <anchorfile>classRTOpPack_1_1PrimitiveTypeTraits_3_01Scalar_00_01index__type_01_4.html</anchorfile>
      <anchor>ad762d6ad79e7097620425cfd581d9ab4</anchor>
      <arglist>(const ArrayView&lt; const primitiveType &gt; &amp;primitiveObjs, const ArrayView&lt; const index_type &gt; &amp;indexObjs, const ArrayView&lt; const char &gt; &amp;charObjs, const Ptr&lt; index_type &gt; &amp;obj)</arglist>
    </member>
    <member kind="function" protection="private" static="yes">
      <type>static void</type>
      <name>assertInput</name>
      <anchorfile>classRTOpPack_1_1PrimitiveTypeTraits_3_01Scalar_00_01index__type_01_4.html</anchorfile>
      <anchor>afdeac0ec58bd597882ef3f0e2a980720</anchor>
      <arglist>(const ArrayView&lt; const primitiveType &gt; &amp;primitiveObjs, const ArrayView&lt; const index_type &gt; &amp;indexObjs, const ArrayView&lt; const char &gt; &amp;charObjs)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>RTOpPack::PrimitiveTypeTraits&lt; Scalar, Scalar &gt;</name>
    <filename>classRTOpPack_1_1PrimitiveTypeTraits_3_01Scalar_00_01Scalar_01_4.html</filename>
    <templarg></templarg>
    <member kind="typedef">
      <type>Scalar</type>
      <name>primitiveType</name>
      <anchorfile>classRTOpPack_1_1PrimitiveTypeTraits_3_01Scalar_00_01Scalar_01_4.html</anchorfile>
      <anchor>a251329023588e7cdae3b81b5227939ee</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" static="yes">
      <type>static int</type>
      <name>numPrimitiveObjs</name>
      <anchorfile>classRTOpPack_1_1PrimitiveTypeTraits_3_01Scalar_00_01Scalar_01_4.html</anchorfile>
      <anchor>a849768ebee49f95ae1ca1620d561ac3d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static int</type>
      <name>numIndexObjs</name>
      <anchorfile>classRTOpPack_1_1PrimitiveTypeTraits_3_01Scalar_00_01Scalar_01_4.html</anchorfile>
      <anchor>a1a72e3db6e798240a7cafffe823d774c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static int</type>
      <name>numCharObjs</name>
      <anchorfile>classRTOpPack_1_1PrimitiveTypeTraits_3_01Scalar_00_01Scalar_01_4.html</anchorfile>
      <anchor>a96028e38feba87ad37aa000662283064</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>extractPrimitiveObjs</name>
      <anchorfile>classRTOpPack_1_1PrimitiveTypeTraits_3_01Scalar_00_01Scalar_01_4.html</anchorfile>
      <anchor>a78b1e452e50057fb2ddee0d31f0d3f01</anchor>
      <arglist>(const Scalar &amp;obj, const ArrayView&lt; primitiveType &gt; &amp;primitiveObjs, const ArrayView&lt; index_type &gt; &amp;indexObjs, const ArrayView&lt; char &gt; &amp;charObjs)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>loadPrimitiveObjs</name>
      <anchorfile>classRTOpPack_1_1PrimitiveTypeTraits_3_01Scalar_00_01Scalar_01_4.html</anchorfile>
      <anchor>a5feeebfbcd72a36dc0e292c64dff13f5</anchor>
      <arglist>(const ArrayView&lt; const primitiveType &gt; &amp;primitiveObjs, const ArrayView&lt; const index_type &gt; &amp;indexObjs, const ArrayView&lt; const char &gt; &amp;charObjs, const Ptr&lt; Scalar &gt; &amp;obj)</arglist>
    </member>
    <member kind="function" protection="private" static="yes">
      <type>static void</type>
      <name>assertInput</name>
      <anchorfile>classRTOpPack_1_1PrimitiveTypeTraits_3_01Scalar_00_01Scalar_01_4.html</anchorfile>
      <anchor>a1cc0df3aed4c32428b52e71b4bc50504</anchor>
      <arglist>(const ArrayView&lt; const primitiveType &gt; &amp;primitiveObjs, const ArrayView&lt; const index_type &gt; &amp;indexObjs, const ArrayView&lt; const char &gt; &amp;charObjs)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>RTOpPack::PrimitiveTypeTraits&lt; Scalar, ScalarIndex&lt; Scalar &gt; &gt;</name>
    <filename>classRTOpPack_1_1PrimitiveTypeTraits_3_01Scalar_00_01ScalarIndex_3_01Scalar_01_4_01_4.html</filename>
    <templarg></templarg>
    <member kind="typedef">
      <type>PrimitiveTypeTraits&lt; Scalar, Scalar &gt;</type>
      <name>ScalarPrimitiveTypeTraits</name>
      <anchorfile>classRTOpPack_1_1PrimitiveTypeTraits_3_01Scalar_00_01ScalarIndex_3_01Scalar_01_4_01_4.html</anchorfile>
      <anchor>ae990dec86c04b4fbd198e68d96d79b3a</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>ScalarPrimitiveTypeTraits::primitiveType</type>
      <name>primitiveType</name>
      <anchorfile>classRTOpPack_1_1PrimitiveTypeTraits_3_01Scalar_00_01ScalarIndex_3_01Scalar_01_4_01_4.html</anchorfile>
      <anchor>ac8bf814e30e40f207cade55041bdcae3</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" static="yes">
      <type>static int</type>
      <name>numPrimitiveObjs</name>
      <anchorfile>classRTOpPack_1_1PrimitiveTypeTraits_3_01Scalar_00_01ScalarIndex_3_01Scalar_01_4_01_4.html</anchorfile>
      <anchor>a9bdba92ebdc9874b5ca3e2ca703cfdf2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static int</type>
      <name>numIndexObjs</name>
      <anchorfile>classRTOpPack_1_1PrimitiveTypeTraits_3_01Scalar_00_01ScalarIndex_3_01Scalar_01_4_01_4.html</anchorfile>
      <anchor>a31abf31f2c108217bc9fe54e8a70fea3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static int</type>
      <name>numCharObjs</name>
      <anchorfile>classRTOpPack_1_1PrimitiveTypeTraits_3_01Scalar_00_01ScalarIndex_3_01Scalar_01_4_01_4.html</anchorfile>
      <anchor>a4fac417a41396e1804e08e06492c405f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>extractPrimitiveObjs</name>
      <anchorfile>classRTOpPack_1_1PrimitiveTypeTraits_3_01Scalar_00_01ScalarIndex_3_01Scalar_01_4_01_4.html</anchorfile>
      <anchor>ae78fd63d1ee8938a15cb4aaa2b659d02</anchor>
      <arglist>(const ScalarIndex&lt; Scalar &gt; &amp;obj, const ArrayView&lt; primitiveType &gt; &amp;primitiveObjs, const ArrayView&lt; index_type &gt; &amp;indexObjs, const ArrayView&lt; char &gt; &amp;charObjs)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>loadPrimitiveObjs</name>
      <anchorfile>classRTOpPack_1_1PrimitiveTypeTraits_3_01Scalar_00_01ScalarIndex_3_01Scalar_01_4_01_4.html</anchorfile>
      <anchor>aff199847b2332629f21c21edc29428d7</anchor>
      <arglist>(const ArrayView&lt; const primitiveType &gt; &amp;primitiveObjs, const ArrayView&lt; const index_type &gt; &amp;indexObjs, const ArrayView&lt; const char &gt; &amp;charObjs, const Ptr&lt; ScalarIndex&lt; Scalar &gt; &gt; &amp;obj)</arglist>
    </member>
    <member kind="function" protection="private" static="yes">
      <type>static void</type>
      <name>assertInput</name>
      <anchorfile>classRTOpPack_1_1PrimitiveTypeTraits_3_01Scalar_00_01ScalarIndex_3_01Scalar_01_4_01_4.html</anchorfile>
      <anchor>a506a0bea7504b0a68d01c77891171b52</anchor>
      <arglist>(const ArrayView&lt; const primitiveType &gt; &amp;primitiveObjs, const ArrayView&lt; const index_type &gt; &amp;indexObjs, const ArrayView&lt; const char &gt; &amp;charObjs)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>RTOpPack::ReductTarget</name>
    <filename>classRTOpPack_1_1ReductTarget.html</filename>
  </compound>
  <compound kind="class">
    <name>RTOpPack::ReductTargetReductionOp</name>
    <filename>classRTOpPack_1_1ReductTargetReductionOp.html</filename>
    <templarg>Scalar</templarg>
    <member kind="typedef">
      <type>Teuchos_Ordinal</type>
      <name>Ordinal</name>
      <anchorfile>classRTOpPack_1_1ReductTargetReductionOp.html</anchorfile>
      <anchor>a3ef31c1f557c9f2f0ad83adfd0bad65f</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ReductTargetReductionOp</name>
      <anchorfile>classRTOpPack_1_1ReductTargetReductionOp.html</anchorfile>
      <anchor>a3eae33790a4ec34ddb1ba84741186914</anchor>
      <arglist>(const Teuchos::RCP&lt; const RTOpT&lt; Scalar &gt; &gt; &amp;op)</arglist>
    </member>
    <member kind="function" protection="private">
      <type></type>
      <name>ReductTargetReductionOp</name>
      <anchorfile>classRTOpPack_1_1ReductTargetReductionOp.html</anchorfile>
      <anchor>a8bf30cdeffcddf4a8dec283531d59e9a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private">
      <type></type>
      <name>ReductTargetReductionOp</name>
      <anchorfile>classRTOpPack_1_1ReductTargetReductionOp.html</anchorfile>
      <anchor>a76b1207396a44bc512e938bb0590c6c3</anchor>
      <arglist>(const ReductTargetReductionOp&lt; Scalar &gt; &amp;)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>ReductTargetReductionOp&lt; Scalar &gt; &amp;</type>
      <name>operator=</name>
      <anchorfile>classRTOpPack_1_1ReductTargetReductionOp.html</anchorfile>
      <anchor>a0e400f24e017cd4c7b57dd0b103ef14b</anchor>
      <arglist>(const ReductTargetReductionOp&lt; Scalar &gt; &amp;)</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>Teuchos::RCP&lt; const RTOpT&lt; Scalar &gt; &gt;</type>
      <name>op_</name>
      <anchorfile>classRTOpPack_1_1ReductTargetReductionOp.html</anchorfile>
      <anchor>aed3615203535cfd4ce4d13eb00111119</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>reduce</name>
      <anchorfile>classRTOpPack_1_1ReductTargetReductionOp.html</anchorfile>
      <anchor>a05c5d64167c5adc880645fde6d5a1425</anchor>
      <arglist>(const Ordinal count, const ReductTarget *const inBuffer[], ReductTarget *const inoutBuffer[]) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>RTOpPack::ReductTargetSerializer</name>
    <filename>classRTOpPack_1_1ReductTargetSerializer.html</filename>
    <templarg>Scalar</templarg>
    <member kind="function">
      <type></type>
      <name>ReductTargetSerializer</name>
      <anchorfile>classRTOpPack_1_1ReductTargetSerializer.html</anchorfile>
      <anchor>a86d72c73a5bb75ea5f4109f4ad60dc03</anchor>
      <arglist>(const Teuchos::RCP&lt; const RTOpT&lt; Scalar &gt; &gt; &amp;op)</arglist>
    </member>
    <member kind="function" protection="private">
      <type></type>
      <name>ReductTargetSerializer</name>
      <anchorfile>classRTOpPack_1_1ReductTargetSerializer.html</anchorfile>
      <anchor>a2b7734c19812000c513d11115d289564</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private">
      <type>ReductTargetSerializer &amp;</type>
      <name>operator=</name>
      <anchorfile>classRTOpPack_1_1ReductTargetSerializer.html</anchorfile>
      <anchor>ab2c5616e68ed61bd7235ed688a079eee</anchor>
      <arglist>(const ReductTargetSerializer &amp;)</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>Teuchos::RCP&lt; const RTOpT&lt; Scalar &gt; &gt;</type>
      <name>op_</name>
      <anchorfile>classRTOpPack_1_1ReductTargetSerializer.html</anchorfile>
      <anchor>a7d0bd7e84a02c165fc2e393a3e6c2936</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>int</type>
      <name>num_values_</name>
      <anchorfile>classRTOpPack_1_1ReductTargetSerializer.html</anchorfile>
      <anchor>a92bfd2df5a9b2a1af2d282b352fb3553</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>int</type>
      <name>num_indexes_</name>
      <anchorfile>classRTOpPack_1_1ReductTargetSerializer.html</anchorfile>
      <anchor>a4267d2c2419c7b493c95f572f7a44863</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>int</type>
      <name>num_chars_</name>
      <anchorfile>classRTOpPack_1_1ReductTargetSerializer.html</anchorfile>
      <anchor>a8093e288feff181adef124b1eafb7377</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>int</type>
      <name>reduct_obj_ext_size_</name>
      <anchorfile>classRTOpPack_1_1ReductTargetSerializer.html</anchorfile>
      <anchor>a45e8264181b08ae4aebfa62d1f1ae395</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>index_type</type>
      <name>getBufferSize</name>
      <anchorfile>classRTOpPack_1_1ReductTargetSerializer.html</anchorfile>
      <anchor>aac8b54abfa41cc4ff3474036b0e210cf</anchor>
      <arglist>(const index_type count) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>serialize</name>
      <anchorfile>classRTOpPack_1_1ReductTargetSerializer.html</anchorfile>
      <anchor>a288c191f2f3db00967b3dd207d2295e2</anchor>
      <arglist>(const index_type count, const ReductTarget *const reduct_objs[], const index_type bytes, char charBuffer[]) const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; ReductTarget &gt;</type>
      <name>createObj</name>
      <anchorfile>classRTOpPack_1_1ReductTargetSerializer.html</anchorfile>
      <anchor>a86e8854b82398fc915704d50668a0e9e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>deserialize</name>
      <anchorfile>classRTOpPack_1_1ReductTargetSerializer.html</anchorfile>
      <anchor>a4678b7be2c4145ba15241f2d4bb78471</anchor>
      <arglist>(const index_type bytes, const char charBuffer[], const index_type count, ReductTarget *const reduct_objs[]) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>RTOpPack::ROp_1_CoordVariantScalarReduction</name>
    <filename>classRTOpPack_1_1ROp__1__CoordVariantScalarReduction.html</filename>
    <templarg>Scalar</templarg>
    <templarg>ReductScalar</templarg>
    <templarg>EleWiseReduction</templarg>
    <templarg>ReductObjReduction</templarg>
    <base>ROpScalarReductionWithOpBase&lt; Scalar, ReductScalar, ReductObjReduction &gt;</base>
    <member kind="variable" protection="private">
      <type>EleWiseReduction</type>
      <name>eleWiseReduction_</name>
      <anchorfile>classRTOpPack_1_1ROp__1__CoordVariantScalarReduction.html</anchorfile>
      <anchor>a0f4938d611e98007a6b497f42d3a2393</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>ROpScalarReductionWithOpBase&lt; Scalar, ReductScalar, ReductObjReduction &gt;</type>
      <name>base_t</name>
      <anchorfile>classRTOpPack_1_1ROp__1__CoordVariantScalarReduction.html</anchorfile>
      <anchor>a0e2d39ee5c569b0e88ab28b5241aee70</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ROp_1_CoordVariantScalarReduction</name>
      <anchorfile>classRTOpPack_1_1ROp__1__CoordVariantScalarReduction.html</anchorfile>
      <anchor>a5300e755d50ade28832f38d17cfff700</anchor>
      <arglist>(const ReductScalar &amp;initReductObjValue_in=ReductScalar(), EleWiseReduction eleWiseReduction_in=EleWiseReduction(), ReductObjReduction reductObjReduction_in=ReductObjReduction())</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setEleWiseReduction</name>
      <anchorfile>classRTOpPack_1_1ROp__1__CoordVariantScalarReduction.html</anchorfile>
      <anchor>adb9209293464057b55563b716b46fc1c</anchor>
      <arglist>(EleWiseReduction eleWiseReduction_in)</arglist>
    </member>
    <member kind="function">
      <type>const EleWiseReduction &amp;</type>
      <name>getEleWiseReduction</name>
      <anchorfile>classRTOpPack_1_1ROp__1__CoordVariantScalarReduction.html</anchorfile>
      <anchor>aeeccc9baaefa5f7fbc3d200ad95f4ead</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>coord_invariant_impl</name>
      <anchorfile>classRTOpPack_1_1ROp__1__CoordVariantScalarReduction.html</anchorfile>
      <anchor>a58710ee1c85aa6e3d5533d0311f1a8ee</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>apply_op_impl</name>
      <anchorfile>classRTOpPack_1_1ROp__1__CoordVariantScalarReduction.html</anchorfile>
      <anchor>a01ad77a0786311b608d2e142f7d17c76</anchor>
      <arglist>(const ArrayView&lt; const ConstSubVectorView&lt; Scalar &gt; &gt; &amp;sub_vecs, const ArrayView&lt; const SubVectorView&lt; Scalar &gt; &gt; &amp;targ_sub_vecs, const Ptr&lt; ReductTarget &gt; &amp;reduct_obj_inout) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ROp_1_CoordVariantScalarReduction&lt; Scalar, Scalar, ROpGetElementEleWiseReductionOp&lt; Scalar &gt; &gt;</name>
    <filename>classRTOpPack_1_1ROp__1__CoordVariantScalarReduction.html</filename>
    <base>ROpScalarReductionWithOpBase&lt; Scalar, Scalar, SumScalarReductObjReduction&lt; Scalar &gt; &gt;</base>
    <member kind="variable" protection="private">
      <type>ROpGetElementEleWiseReductionOp&lt; Scalar &gt;</type>
      <name>eleWiseReduction_</name>
      <anchorfile>classRTOpPack_1_1ROp__1__CoordVariantScalarReduction.html</anchorfile>
      <anchor>a0f4938d611e98007a6b497f42d3a2393</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>ROpScalarReductionWithOpBase&lt; Scalar, Scalar, SumScalarReductObjReduction&lt; Scalar &gt; &gt;</type>
      <name>base_t</name>
      <anchorfile>classRTOpPack_1_1ROp__1__CoordVariantScalarReduction.html</anchorfile>
      <anchor>a0e2d39ee5c569b0e88ab28b5241aee70</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ROp_1_CoordVariantScalarReduction</name>
      <anchorfile>classRTOpPack_1_1ROp__1__CoordVariantScalarReduction.html</anchorfile>
      <anchor>a5300e755d50ade28832f38d17cfff700</anchor>
      <arglist>(const Scalar &amp;initReductObjValue_in=Scalar(), ROpGetElementEleWiseReductionOp&lt; Scalar &gt; eleWiseReduction_in=ROpGetElementEleWiseReductionOp&lt; Scalar &gt;(), SumScalarReductObjReduction&lt; Scalar &gt; reductObjReduction_in=SumScalarReductObjReduction&lt; Scalar &gt;())</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setEleWiseReduction</name>
      <anchorfile>classRTOpPack_1_1ROp__1__CoordVariantScalarReduction.html</anchorfile>
      <anchor>adb9209293464057b55563b716b46fc1c</anchor>
      <arglist>(ROpGetElementEleWiseReductionOp&lt; Scalar &gt; eleWiseReduction_in)</arglist>
    </member>
    <member kind="function">
      <type>const ROpGetElementEleWiseReductionOp&lt; Scalar &gt; &amp;</type>
      <name>getEleWiseReduction</name>
      <anchorfile>classRTOpPack_1_1ROp__1__CoordVariantScalarReduction.html</anchorfile>
      <anchor>aeeccc9baaefa5f7fbc3d200ad95f4ead</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>coord_invariant_impl</name>
      <anchorfile>classRTOpPack_1_1ROp__1__CoordVariantScalarReduction.html</anchorfile>
      <anchor>a58710ee1c85aa6e3d5533d0311f1a8ee</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>apply_op_impl</name>
      <anchorfile>classRTOpPack_1_1ROp__1__CoordVariantScalarReduction.html</anchorfile>
      <anchor>a01ad77a0786311b608d2e142f7d17c76</anchor>
      <arglist>(const ArrayView&lt; const ConstSubVectorView&lt; Scalar &gt; &gt; &amp;sub_vecs, const ArrayView&lt; const SubVectorView&lt; Scalar &gt; &gt; &amp;targ_sub_vecs, const Ptr&lt; ReductTarget &gt; &amp;reduct_obj_inout) const</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ROp_1_CoordVariantScalarReduction&lt; Scalar, ScalarIndex&lt; Scalar &gt;, ROpMaxIndexEleWiseReductionOp&lt; Scalar &gt;, ROpMaxIndexReductObjReductionOp&lt; Scalar &gt; &gt;</name>
    <filename>classRTOpPack_1_1ROp__1__CoordVariantScalarReduction.html</filename>
    <base>ROpScalarReductionWithOpBase&lt; Scalar, ScalarIndex&lt; Scalar &gt;, ROpMaxIndexReductObjReductionOp&lt; Scalar &gt; &gt;</base>
    <member kind="variable" protection="private">
      <type>ROpMaxIndexEleWiseReductionOp&lt; Scalar &gt;</type>
      <name>eleWiseReduction_</name>
      <anchorfile>classRTOpPack_1_1ROp__1__CoordVariantScalarReduction.html</anchorfile>
      <anchor>a0f4938d611e98007a6b497f42d3a2393</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>ROpScalarReductionWithOpBase&lt; Scalar, ScalarIndex&lt; Scalar &gt;, ROpMaxIndexReductObjReductionOp&lt; Scalar &gt; &gt;</type>
      <name>base_t</name>
      <anchorfile>classRTOpPack_1_1ROp__1__CoordVariantScalarReduction.html</anchorfile>
      <anchor>a0e2d39ee5c569b0e88ab28b5241aee70</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ROp_1_CoordVariantScalarReduction</name>
      <anchorfile>classRTOpPack_1_1ROp__1__CoordVariantScalarReduction.html</anchorfile>
      <anchor>a5300e755d50ade28832f38d17cfff700</anchor>
      <arglist>(const ScalarIndex&lt; Scalar &gt; &amp;initReductObjValue_in=ScalarIndex&lt; Scalar &gt;(), ROpMaxIndexEleWiseReductionOp&lt; Scalar &gt; eleWiseReduction_in=ROpMaxIndexEleWiseReductionOp&lt; Scalar &gt;(), ROpMaxIndexReductObjReductionOp&lt; Scalar &gt; reductObjReduction_in=ROpMaxIndexReductObjReductionOp&lt; Scalar &gt;())</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setEleWiseReduction</name>
      <anchorfile>classRTOpPack_1_1ROp__1__CoordVariantScalarReduction.html</anchorfile>
      <anchor>adb9209293464057b55563b716b46fc1c</anchor>
      <arglist>(ROpMaxIndexEleWiseReductionOp&lt; Scalar &gt; eleWiseReduction_in)</arglist>
    </member>
    <member kind="function">
      <type>const ROpMaxIndexEleWiseReductionOp&lt; Scalar &gt; &amp;</type>
      <name>getEleWiseReduction</name>
      <anchorfile>classRTOpPack_1_1ROp__1__CoordVariantScalarReduction.html</anchorfile>
      <anchor>aeeccc9baaefa5f7fbc3d200ad95f4ead</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>coord_invariant_impl</name>
      <anchorfile>classRTOpPack_1_1ROp__1__CoordVariantScalarReduction.html</anchorfile>
      <anchor>a58710ee1c85aa6e3d5533d0311f1a8ee</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>apply_op_impl</name>
      <anchorfile>classRTOpPack_1_1ROp__1__CoordVariantScalarReduction.html</anchorfile>
      <anchor>a01ad77a0786311b608d2e142f7d17c76</anchor>
      <arglist>(const ArrayView&lt; const ConstSubVectorView&lt; Scalar &gt; &gt; &amp;sub_vecs, const ArrayView&lt; const SubVectorView&lt; Scalar &gt; &gt; &amp;targ_sub_vecs, const Ptr&lt; ReductTarget &gt; &amp;reduct_obj_inout) const</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ROp_1_CoordVariantScalarReduction&lt; Scalar, ScalarIndex&lt; Scalar &gt;, ROpMaxIndexLessThanBoundEleWiseReductionOp&lt; Scalar &gt;, ROpMaxIndexReductObjReductionOp&lt; Scalar &gt; &gt;</name>
    <filename>classRTOpPack_1_1ROp__1__CoordVariantScalarReduction.html</filename>
    <base>ROpScalarReductionWithOpBase&lt; Scalar, ScalarIndex&lt; Scalar &gt;, ROpMaxIndexReductObjReductionOp&lt; Scalar &gt; &gt;</base>
    <member kind="variable" protection="private">
      <type>ROpMaxIndexLessThanBoundEleWiseReductionOp&lt; Scalar &gt;</type>
      <name>eleWiseReduction_</name>
      <anchorfile>classRTOpPack_1_1ROp__1__CoordVariantScalarReduction.html</anchorfile>
      <anchor>a0f4938d611e98007a6b497f42d3a2393</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>ROpScalarReductionWithOpBase&lt; Scalar, ScalarIndex&lt; Scalar &gt;, ROpMaxIndexReductObjReductionOp&lt; Scalar &gt; &gt;</type>
      <name>base_t</name>
      <anchorfile>classRTOpPack_1_1ROp__1__CoordVariantScalarReduction.html</anchorfile>
      <anchor>a0e2d39ee5c569b0e88ab28b5241aee70</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ROp_1_CoordVariantScalarReduction</name>
      <anchorfile>classRTOpPack_1_1ROp__1__CoordVariantScalarReduction.html</anchorfile>
      <anchor>a5300e755d50ade28832f38d17cfff700</anchor>
      <arglist>(const ScalarIndex&lt; Scalar &gt; &amp;initReductObjValue_in=ScalarIndex&lt; Scalar &gt;(), ROpMaxIndexLessThanBoundEleWiseReductionOp&lt; Scalar &gt; eleWiseReduction_in=ROpMaxIndexLessThanBoundEleWiseReductionOp&lt; Scalar &gt;(), ROpMaxIndexReductObjReductionOp&lt; Scalar &gt; reductObjReduction_in=ROpMaxIndexReductObjReductionOp&lt; Scalar &gt;())</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setEleWiseReduction</name>
      <anchorfile>classRTOpPack_1_1ROp__1__CoordVariantScalarReduction.html</anchorfile>
      <anchor>adb9209293464057b55563b716b46fc1c</anchor>
      <arglist>(ROpMaxIndexLessThanBoundEleWiseReductionOp&lt; Scalar &gt; eleWiseReduction_in)</arglist>
    </member>
    <member kind="function">
      <type>const ROpMaxIndexLessThanBoundEleWiseReductionOp&lt; Scalar &gt; &amp;</type>
      <name>getEleWiseReduction</name>
      <anchorfile>classRTOpPack_1_1ROp__1__CoordVariantScalarReduction.html</anchorfile>
      <anchor>aeeccc9baaefa5f7fbc3d200ad95f4ead</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>coord_invariant_impl</name>
      <anchorfile>classRTOpPack_1_1ROp__1__CoordVariantScalarReduction.html</anchorfile>
      <anchor>a58710ee1c85aa6e3d5533d0311f1a8ee</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>apply_op_impl</name>
      <anchorfile>classRTOpPack_1_1ROp__1__CoordVariantScalarReduction.html</anchorfile>
      <anchor>a01ad77a0786311b608d2e142f7d17c76</anchor>
      <arglist>(const ArrayView&lt; const ConstSubVectorView&lt; Scalar &gt; &gt; &amp;sub_vecs, const ArrayView&lt; const SubVectorView&lt; Scalar &gt; &gt; &amp;targ_sub_vecs, const Ptr&lt; ReductTarget &gt; &amp;reduct_obj_inout) const</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ROp_1_CoordVariantScalarReduction&lt; Scalar, ScalarIndex&lt; Scalar &gt;, ROpMinIndexEleWiseReductionOp&lt; Scalar &gt;, ROpMinIndexReductObjReductionOp&lt; Scalar &gt; &gt;</name>
    <filename>classRTOpPack_1_1ROp__1__CoordVariantScalarReduction.html</filename>
    <base>ROpScalarReductionWithOpBase&lt; Scalar, ScalarIndex&lt; Scalar &gt;, ROpMinIndexReductObjReductionOp&lt; Scalar &gt; &gt;</base>
    <member kind="variable" protection="private">
      <type>ROpMinIndexEleWiseReductionOp&lt; Scalar &gt;</type>
      <name>eleWiseReduction_</name>
      <anchorfile>classRTOpPack_1_1ROp__1__CoordVariantScalarReduction.html</anchorfile>
      <anchor>a0f4938d611e98007a6b497f42d3a2393</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>ROpScalarReductionWithOpBase&lt; Scalar, ScalarIndex&lt; Scalar &gt;, ROpMinIndexReductObjReductionOp&lt; Scalar &gt; &gt;</type>
      <name>base_t</name>
      <anchorfile>classRTOpPack_1_1ROp__1__CoordVariantScalarReduction.html</anchorfile>
      <anchor>a0e2d39ee5c569b0e88ab28b5241aee70</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ROp_1_CoordVariantScalarReduction</name>
      <anchorfile>classRTOpPack_1_1ROp__1__CoordVariantScalarReduction.html</anchorfile>
      <anchor>a5300e755d50ade28832f38d17cfff700</anchor>
      <arglist>(const ScalarIndex&lt; Scalar &gt; &amp;initReductObjValue_in=ScalarIndex&lt; Scalar &gt;(), ROpMinIndexEleWiseReductionOp&lt; Scalar &gt; eleWiseReduction_in=ROpMinIndexEleWiseReductionOp&lt; Scalar &gt;(), ROpMinIndexReductObjReductionOp&lt; Scalar &gt; reductObjReduction_in=ROpMinIndexReductObjReductionOp&lt; Scalar &gt;())</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setEleWiseReduction</name>
      <anchorfile>classRTOpPack_1_1ROp__1__CoordVariantScalarReduction.html</anchorfile>
      <anchor>adb9209293464057b55563b716b46fc1c</anchor>
      <arglist>(ROpMinIndexEleWiseReductionOp&lt; Scalar &gt; eleWiseReduction_in)</arglist>
    </member>
    <member kind="function">
      <type>const ROpMinIndexEleWiseReductionOp&lt; Scalar &gt; &amp;</type>
      <name>getEleWiseReduction</name>
      <anchorfile>classRTOpPack_1_1ROp__1__CoordVariantScalarReduction.html</anchorfile>
      <anchor>aeeccc9baaefa5f7fbc3d200ad95f4ead</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>coord_invariant_impl</name>
      <anchorfile>classRTOpPack_1_1ROp__1__CoordVariantScalarReduction.html</anchorfile>
      <anchor>a58710ee1c85aa6e3d5533d0311f1a8ee</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>apply_op_impl</name>
      <anchorfile>classRTOpPack_1_1ROp__1__CoordVariantScalarReduction.html</anchorfile>
      <anchor>a01ad77a0786311b608d2e142f7d17c76</anchor>
      <arglist>(const ArrayView&lt; const ConstSubVectorView&lt; Scalar &gt; &gt; &amp;sub_vecs, const ArrayView&lt; const SubVectorView&lt; Scalar &gt; &gt; &amp;targ_sub_vecs, const Ptr&lt; ReductTarget &gt; &amp;reduct_obj_inout) const</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ROp_1_CoordVariantScalarReduction&lt; Scalar, ScalarIndex&lt; Scalar &gt;, ROpMinIndexGreaterThanBoundEleWiseReductionOp&lt; Scalar &gt;, ROpMinIndexReductObjReductionOp&lt; Scalar &gt; &gt;</name>
    <filename>classRTOpPack_1_1ROp__1__CoordVariantScalarReduction.html</filename>
    <base>ROpScalarReductionWithOpBase&lt; Scalar, ScalarIndex&lt; Scalar &gt;, ROpMinIndexReductObjReductionOp&lt; Scalar &gt; &gt;</base>
    <member kind="variable" protection="private">
      <type>ROpMinIndexGreaterThanBoundEleWiseReductionOp&lt; Scalar &gt;</type>
      <name>eleWiseReduction_</name>
      <anchorfile>classRTOpPack_1_1ROp__1__CoordVariantScalarReduction.html</anchorfile>
      <anchor>a0f4938d611e98007a6b497f42d3a2393</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>ROpScalarReductionWithOpBase&lt; Scalar, ScalarIndex&lt; Scalar &gt;, ROpMinIndexReductObjReductionOp&lt; Scalar &gt; &gt;</type>
      <name>base_t</name>
      <anchorfile>classRTOpPack_1_1ROp__1__CoordVariantScalarReduction.html</anchorfile>
      <anchor>a0e2d39ee5c569b0e88ab28b5241aee70</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ROp_1_CoordVariantScalarReduction</name>
      <anchorfile>classRTOpPack_1_1ROp__1__CoordVariantScalarReduction.html</anchorfile>
      <anchor>a5300e755d50ade28832f38d17cfff700</anchor>
      <arglist>(const ScalarIndex&lt; Scalar &gt; &amp;initReductObjValue_in=ScalarIndex&lt; Scalar &gt;(), ROpMinIndexGreaterThanBoundEleWiseReductionOp&lt; Scalar &gt; eleWiseReduction_in=ROpMinIndexGreaterThanBoundEleWiseReductionOp&lt; Scalar &gt;(), ROpMinIndexReductObjReductionOp&lt; Scalar &gt; reductObjReduction_in=ROpMinIndexReductObjReductionOp&lt; Scalar &gt;())</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setEleWiseReduction</name>
      <anchorfile>classRTOpPack_1_1ROp__1__CoordVariantScalarReduction.html</anchorfile>
      <anchor>adb9209293464057b55563b716b46fc1c</anchor>
      <arglist>(ROpMinIndexGreaterThanBoundEleWiseReductionOp&lt; Scalar &gt; eleWiseReduction_in)</arglist>
    </member>
    <member kind="function">
      <type>const ROpMinIndexGreaterThanBoundEleWiseReductionOp&lt; Scalar &gt; &amp;</type>
      <name>getEleWiseReduction</name>
      <anchorfile>classRTOpPack_1_1ROp__1__CoordVariantScalarReduction.html</anchorfile>
      <anchor>aeeccc9baaefa5f7fbc3d200ad95f4ead</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>coord_invariant_impl</name>
      <anchorfile>classRTOpPack_1_1ROp__1__CoordVariantScalarReduction.html</anchorfile>
      <anchor>a58710ee1c85aa6e3d5533d0311f1a8ee</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>apply_op_impl</name>
      <anchorfile>classRTOpPack_1_1ROp__1__CoordVariantScalarReduction.html</anchorfile>
      <anchor>a01ad77a0786311b608d2e142f7d17c76</anchor>
      <arglist>(const ArrayView&lt; const ConstSubVectorView&lt; Scalar &gt; &gt; &amp;sub_vecs, const ArrayView&lt; const SubVectorView&lt; Scalar &gt; &gt; &amp;targ_sub_vecs, const Ptr&lt; ReductTarget &gt; &amp;reduct_obj_inout) const</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>RTOpPack::ROp_1_ScalarReduction</name>
    <filename>classRTOpPack_1_1ROp__1__ScalarReduction.html</filename>
    <templarg>Scalar</templarg>
    <templarg>ConcreteReductObj</templarg>
    <templarg>EleWiseReduction</templarg>
    <templarg>ReductObjReduction</templarg>
    <base>RTOpPack::ROpScalarReductionWithOpBase</base>
    <member kind="typedef">
      <type>ROpScalarReductionWithOpBase&lt; Scalar, ConcreteReductObj, ReductObjReduction &gt;</type>
      <name>base_t</name>
      <anchorfile>classRTOpPack_1_1ROp__1__ScalarReduction.html</anchorfile>
      <anchor>a73734dbd5aa512574dfef8aacc023006</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ROp_1_ScalarReduction</name>
      <anchorfile>classRTOpPack_1_1ROp__1__ScalarReduction.html</anchorfile>
      <anchor>a9b9bb705d81d1e4c6d770dc99cedba1c</anchor>
      <arglist>(const ConcreteReductObj &amp;initReductObjValue_in=ConcreteReductObj(), EleWiseReduction eleWiseReduction_in=EleWiseReduction(), ReductObjReduction reductObjReduction_in=ReductObjReduction())</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>EleWiseReduction</type>
      <name>eleWiseReduction_</name>
      <anchorfile>classRTOpPack_1_1ROp__1__ScalarReduction.html</anchorfile>
      <anchor>a1982f98038673224b7151b50ec885252</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>apply_op_impl</name>
      <anchorfile>classRTOpPack_1_1ROp__1__ScalarReduction.html</anchorfile>
      <anchor>a5458c8b883fa5b4e06ff9286e42bda4e</anchor>
      <arglist>(const ArrayView&lt; const ConstSubVectorView&lt; Scalar &gt; &gt; &amp;sub_vecs, const ArrayView&lt; const SubVectorView&lt; Scalar &gt; &gt; &amp;targ_sub_vecs, const Ptr&lt; ReductTarget &gt; &amp;reduct_obj_inout) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ROp_1_ScalarReduction&lt; Scalar, Scalar, ROpNorm2EleWiseReduction&lt; Scalar &gt; &gt;</name>
    <filename>classRTOpPack_1_1ROp__1__ScalarReduction.html</filename>
    <base>ROpScalarReductionWithOpBase&lt; Scalar, Scalar, SumScalarReductObjReduction&lt; Scalar &gt; &gt;</base>
    <member kind="typedef">
      <type>ROpScalarReductionWithOpBase&lt; Scalar, Scalar, SumScalarReductObjReduction&lt; Scalar &gt; &gt;</type>
      <name>base_t</name>
      <anchorfile>classRTOpPack_1_1ROp__1__ScalarReduction.html</anchorfile>
      <anchor>a73734dbd5aa512574dfef8aacc023006</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ROp_1_ScalarReduction</name>
      <anchorfile>classRTOpPack_1_1ROp__1__ScalarReduction.html</anchorfile>
      <anchor>a9b9bb705d81d1e4c6d770dc99cedba1c</anchor>
      <arglist>(const Scalar &amp;initReductObjValue_in=Scalar(), ROpNorm2EleWiseReduction&lt; Scalar &gt; eleWiseReduction_in=ROpNorm2EleWiseReduction&lt; Scalar &gt;(), SumScalarReductObjReduction&lt; Scalar &gt; reductObjReduction_in=SumScalarReductObjReduction&lt; Scalar &gt;())</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>ROpNorm2EleWiseReduction&lt; Scalar &gt;</type>
      <name>eleWiseReduction_</name>
      <anchorfile>classRTOpPack_1_1ROp__1__ScalarReduction.html</anchorfile>
      <anchor>a1982f98038673224b7151b50ec885252</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>apply_op_impl</name>
      <anchorfile>classRTOpPack_1_1ROp__1__ScalarReduction.html</anchorfile>
      <anchor>a5458c8b883fa5b4e06ff9286e42bda4e</anchor>
      <arglist>(const ArrayView&lt; const ConstSubVectorView&lt; Scalar &gt; &gt; &amp;sub_vecs, const ArrayView&lt; const SubVectorView&lt; Scalar &gt; &gt; &amp;targ_sub_vecs, const Ptr&lt; ReductTarget &gt; &amp;reduct_obj_inout) const</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>RTOpPack::ROp_2_ScalarReduction</name>
    <filename>classRTOpPack_1_1ROp__2__ScalarReduction.html</filename>
    <templarg>Scalar</templarg>
    <templarg>ReductScalar</templarg>
    <templarg>EleWiseReduction</templarg>
    <templarg>ReductObjReduction</templarg>
    <base>ROpScalarReductionWithOpBase&lt; Scalar, ReductScalar, ReductObjReduction &gt;</base>
    <member kind="typedef">
      <type>ROpScalarReductionWithOpBase&lt; Scalar, ReductScalar, ReductObjReduction &gt;</type>
      <name>base_t</name>
      <anchorfile>classRTOpPack_1_1ROp__2__ScalarReduction.html</anchorfile>
      <anchor>a9271fab0e2ddb77fadfc4bd024850e59</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ROp_2_ScalarReduction</name>
      <anchorfile>classRTOpPack_1_1ROp__2__ScalarReduction.html</anchorfile>
      <anchor>a14ab4cab1fd89ead3958cdfec0b7a508</anchor>
      <arglist>(const ReductScalar &amp;initReductObjValue_in=ReductScalar(), EleWiseReduction eleWiseReduction_in=EleWiseReduction(), ReductObjReduction reductObjReduction_in=ReductObjReduction())</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>EleWiseReduction</type>
      <name>eleWiseReduction_</name>
      <anchorfile>classRTOpPack_1_1ROp__2__ScalarReduction.html</anchorfile>
      <anchor>ade7c8461b849c20454c51a9383f01395</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>apply_op_impl</name>
      <anchorfile>classRTOpPack_1_1ROp__2__ScalarReduction.html</anchorfile>
      <anchor>a8cd09bbfc2914bb3550cb2243f7db4c6</anchor>
      <arglist>(const ArrayView&lt; const ConstSubVectorView&lt; Scalar &gt; &gt; &amp;sub_vecs, const ArrayView&lt; const SubVectorView&lt; Scalar &gt; &gt; &amp;targ_sub_vecs, const Ptr&lt; ReductTarget &gt; &amp;reduct_obj_inout) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ROp_2_ScalarReduction&lt; Scalar, Scalar, ROpWeightedNorm2EleWiseReduction&lt; Scalar &gt; &gt;</name>
    <filename>classRTOpPack_1_1ROp__2__ScalarReduction.html</filename>
    <base>ROpScalarReductionWithOpBase&lt; Scalar, Scalar, SumScalarReductObjReduction&lt; Scalar &gt; &gt;</base>
    <member kind="typedef">
      <type>ROpScalarReductionWithOpBase&lt; Scalar, Scalar, SumScalarReductObjReduction&lt; Scalar &gt; &gt;</type>
      <name>base_t</name>
      <anchorfile>classRTOpPack_1_1ROp__2__ScalarReduction.html</anchorfile>
      <anchor>a9271fab0e2ddb77fadfc4bd024850e59</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ROp_2_ScalarReduction</name>
      <anchorfile>classRTOpPack_1_1ROp__2__ScalarReduction.html</anchorfile>
      <anchor>a14ab4cab1fd89ead3958cdfec0b7a508</anchor>
      <arglist>(const Scalar &amp;initReductObjValue_in=Scalar(), ROpWeightedNorm2EleWiseReduction&lt; Scalar &gt; eleWiseReduction_in=ROpWeightedNorm2EleWiseReduction&lt; Scalar &gt;(), SumScalarReductObjReduction&lt; Scalar &gt; reductObjReduction_in=SumScalarReductObjReduction&lt; Scalar &gt;())</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>ROpWeightedNorm2EleWiseReduction&lt; Scalar &gt;</type>
      <name>eleWiseReduction_</name>
      <anchorfile>classRTOpPack_1_1ROp__2__ScalarReduction.html</anchorfile>
      <anchor>ade7c8461b849c20454c51a9383f01395</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>apply_op_impl</name>
      <anchorfile>classRTOpPack_1_1ROp__2__ScalarReduction.html</anchorfile>
      <anchor>a8cd09bbfc2914bb3550cb2243f7db4c6</anchor>
      <arglist>(const ArrayView&lt; const ConstSubVectorView&lt; Scalar &gt; &gt; &amp;sub_vecs, const ArrayView&lt; const SubVectorView&lt; Scalar &gt; &gt; &amp;targ_sub_vecs, const Ptr&lt; ReductTarget &gt; &amp;reduct_obj_inout) const</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>RTOpPack::ROpGetElement</name>
    <filename>classRTOpPack_1_1ROpGetElement.html</filename>
    <templarg></templarg>
    <base>ROp_1_CoordVariantScalarReduction&lt; Scalar, Scalar, ROpGetElementEleWiseReductionOp&lt; Scalar &gt; &gt;</base>
    <member kind="function">
      <type></type>
      <name>ROpGetElement</name>
      <anchorfile>classRTOpPack_1_1ROpGetElement.html</anchorfile>
      <anchor>ad5a916d601e086e885738866ea668fda</anchor>
      <arglist>(const Ordinal &amp;global_i)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initialize</name>
      <anchorfile>classRTOpPack_1_1ROpGetElement.html</anchorfile>
      <anchor>ae3a7d661cfe3d5698833a4ce58b12dd5</anchor>
      <arglist>(const Ordinal &amp;global_i)</arglist>
    </member>
    <member kind="function">
      <type>Scalar</type>
      <name>operator()</name>
      <anchorfile>classRTOpPack_1_1ROpGetElement.html</anchorfile>
      <anchor>afa0647ac3e82729987bc7d0f44bbcceb</anchor>
      <arglist>(const ReductTarget &amp;reduct_obj) const </arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual Range1D</type>
      <name>range_impl</name>
      <anchorfile>classRTOpPack_1_1ROpGetElement.html</anchorfile>
      <anchor>a2c2857bc3814e0fd4dd269cb7fd27ec3</anchor>
      <arglist>() const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>RTOpPack::ROpGetElementEleWiseReductionOp</name>
    <filename>classRTOpPack_1_1ROpGetElementEleWiseReductionOp.html</filename>
    <templarg></templarg>
    <member kind="function">
      <type></type>
      <name>ROpGetElementEleWiseReductionOp</name>
      <anchorfile>classRTOpPack_1_1ROpGetElementEleWiseReductionOp.html</anchorfile>
      <anchor>a1a62514cecbde3076992411821f54ed9</anchor>
      <arglist>(const Ordinal &amp;global_i_in=-1)</arglist>
    </member>
    <member kind="function">
      <type>Ordinal</type>
      <name>global_i</name>
      <anchorfile>classRTOpPack_1_1ROpGetElementEleWiseReductionOp.html</anchorfile>
      <anchor>a3b388d5c6f11aa0bd3d7e7ff7d59b1ef</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>operator()</name>
      <anchorfile>classRTOpPack_1_1ROpGetElementEleWiseReductionOp.html</anchorfile>
      <anchor>a65c48774b9c831a6571bf6af9c11da32</anchor>
      <arglist>(const index_type i, const Scalar &amp;v0, Scalar &amp;reduct) const </arglist>
    </member>
    <member kind="variable" protection="private">
      <type>Ordinal</type>
      <name>global_i_</name>
      <anchorfile>classRTOpPack_1_1ROpGetElementEleWiseReductionOp.html</anchorfile>
      <anchor>ae0e0457b388867b6ee75ff70888c72c2</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>RTOpPack::ROpGetSubVector</name>
    <filename>classRTOpPack_1_1ROpGetSubVector.html</filename>
    <templarg></templarg>
    <base>RTOpPack::RTOpT</base>
    <member kind="typedef">
      <type>RTOpT&lt; Scalar &gt;::primitive_value_type</type>
      <name>primitive_value_type</name>
      <anchorfile>classRTOpPack_1_1ROpGetSubVector.html</anchorfile>
      <anchor>ae0658408cbe62ad4afb70a94703614d3</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ROpGetSubVector</name>
      <anchorfile>classRTOpPack_1_1ROpGetSubVector.html</anchorfile>
      <anchor>a72674ddac48334c2edd8e79c1ea215f1</anchor>
      <arglist>(const index_type l=0, const index_type u=0)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_range</name>
      <anchorfile>classRTOpPack_1_1ROpGetSubVector.html</anchorfile>
      <anchor>a7c1e1f657b4f337d8930ce564a914db5</anchor>
      <arglist>(const index_type l, const index_type u)</arglist>
    </member>
    <member kind="function">
      <type>const ConstSubVectorView&lt; Scalar &gt;</type>
      <name>operator()</name>
      <anchorfile>classRTOpPack_1_1ROpGetSubVector.html</anchorfile>
      <anchor>a20d7022181aed283c3928dc244a6e1e3</anchor>
      <arglist>(const ReductTarget &amp;reduct_obj) const </arglist>
    </member>
    <member kind="variable" protection="private">
      <type>index_type</type>
      <name>l_</name>
      <anchorfile>classRTOpPack_1_1ROpGetSubVector.html</anchorfile>
      <anchor>a3c0c726feb7928d01d707df7d1ec1947</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>index_type</type>
      <name>u_</name>
      <anchorfile>classRTOpPack_1_1ROpGetSubVector.html</anchorfile>
      <anchor>ac9fba486c7fe9defa83dd9ab89a0fb60</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>get_reduct_type_num_entries_impl</name>
      <anchorfile>classRTOpPack_1_1ROpGetSubVector.html</anchorfile>
      <anchor>a8a7a95de8dacd5dc1f9e9361f871a4ab</anchor>
      <arglist>(const Ptr&lt; int &gt; &amp;num_values, const Ptr&lt; int &gt; &amp;num_indexes, const Ptr&lt; int &gt; &amp;num_chars) const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; ReductTarget &gt;</type>
      <name>reduct_obj_create_impl</name>
      <anchorfile>classRTOpPack_1_1ROpGetSubVector.html</anchorfile>
      <anchor>ad5ecd66b8d313a1bb62e9bc4ddc06ebd</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>reduce_reduct_objs_impl</name>
      <anchorfile>classRTOpPack_1_1ROpGetSubVector.html</anchorfile>
      <anchor>a68a56831eaad8d3dbaba1a7814a29a3c</anchor>
      <arglist>(const ReductTarget &amp;in_reduct_obj, const Ptr&lt; ReductTarget &gt; &amp;inout_reduct_obj) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>reduct_obj_reinit_impl</name>
      <anchorfile>classRTOpPack_1_1ROpGetSubVector.html</anchorfile>
      <anchor>ac13a3e6fa8a13d587bd6ef0a251d3fcb</anchor>
      <arglist>(const Ptr&lt; ReductTarget &gt; &amp;reduct_obj) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>extract_reduct_obj_state_impl</name>
      <anchorfile>classRTOpPack_1_1ROpGetSubVector.html</anchorfile>
      <anchor>adce9fba403efe4be3659d14ba1fa9dc5</anchor>
      <arglist>(const ReductTarget &amp;reduct_obj, const ArrayView&lt; primitive_value_type &gt; &amp;value_data, const ArrayView&lt; index_type &gt; &amp;index_data, const ArrayView&lt; char_type &gt; &amp;char_data) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>load_reduct_obj_state_impl</name>
      <anchorfile>classRTOpPack_1_1ROpGetSubVector.html</anchorfile>
      <anchor>af9cf422500d33ffff48f6a7657f3ba87</anchor>
      <arglist>(const ArrayView&lt; const primitive_value_type &gt; &amp;value_data, const ArrayView&lt; const index_type &gt; &amp;index_data, const ArrayView&lt; const char_type &gt; &amp;char_data, const Ptr&lt; ReductTarget &gt; &amp;reduct_obj) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>coord_invariant_impl</name>
      <anchorfile>classRTOpPack_1_1ROpGetSubVector.html</anchorfile>
      <anchor>a42ce6f43b22f955579f52428bd2864ad</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>apply_op_impl</name>
      <anchorfile>classRTOpPack_1_1ROpGetSubVector.html</anchorfile>
      <anchor>ab2cda9ca7c31b64c5e0a8b03ea5a1559</anchor>
      <arglist>(const ArrayView&lt; const ConstSubVectorView&lt; Scalar &gt; &gt; &amp;sub_vecs, const ArrayView&lt; const SubVectorView&lt; Scalar &gt; &gt; &amp;targ_sub_vecs, const Ptr&lt; ReductTarget &gt; &amp;reduct_obj) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>RTOpPack::ROpMaxIndex</name>
    <filename>classRTOpPack_1_1ROpMaxIndex.html</filename>
    <templarg></templarg>
    <base>ROp_1_CoordVariantScalarReduction&lt; Scalar, ScalarIndex&lt; Scalar &gt;, ROpMaxIndexEleWiseReductionOp&lt; Scalar &gt;, ROpMaxIndexReductObjReductionOp&lt; Scalar &gt; &gt;</base>
    <member kind="function">
      <type></type>
      <name>ROpMaxIndex</name>
      <anchorfile>classRTOpPack_1_1ROpMaxIndex.html</anchorfile>
      <anchor>a0aaec41e832ce5b364212e7b916345dc</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>ScalarIndex&lt; Scalar &gt;</type>
      <name>operator()</name>
      <anchorfile>classRTOpPack_1_1ROpMaxIndex.html</anchorfile>
      <anchor>a669ceada2646431e36b532be56c78df2</anchor>
      <arglist>(const ReductTarget &amp;reduct_obj) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>RTOpPack::ROpMaxIndexEleWiseReductionOp</name>
    <filename>classRTOpPack_1_1ROpMaxIndexEleWiseReductionOp.html</filename>
    <templarg></templarg>
    <member kind="function">
      <type>void</type>
      <name>operator()</name>
      <anchorfile>classRTOpPack_1_1ROpMaxIndexEleWiseReductionOp.html</anchorfile>
      <anchor>a5f6f3ba50b43873dc368b649c21fc730</anchor>
      <arglist>(const index_type i, const Scalar &amp;v0, ScalarIndex&lt; Scalar &gt; &amp;reduct) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>RTOpPack::ROpMaxIndexLessThanBound</name>
    <filename>classRTOpPack_1_1ROpMaxIndexLessThanBound.html</filename>
    <templarg></templarg>
    <base>ROp_1_CoordVariantScalarReduction&lt; Scalar, ScalarIndex&lt; Scalar &gt;, ROpMaxIndexLessThanBoundEleWiseReductionOp&lt; Scalar &gt;, ROpMaxIndexReductObjReductionOp&lt; Scalar &gt; &gt;</base>
    <member kind="function">
      <type></type>
      <name>ROpMaxIndexLessThanBound</name>
      <anchorfile>classRTOpPack_1_1ROpMaxIndexLessThanBound.html</anchorfile>
      <anchor>a20d5d4f898482344bbb395ef6b8fc6c3</anchor>
      <arglist>(const Scalar &amp;bound_in=Teuchos::ScalarTraits&lt; Scalar &gt;::zero())</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>bound</name>
      <anchorfile>classRTOpPack_1_1ROpMaxIndexLessThanBound.html</anchorfile>
      <anchor>a90509a9eeae938ac51e02b82cf06975c</anchor>
      <arglist>(const Scalar &amp;bound_in)</arglist>
    </member>
    <member kind="function">
      <type>ScalarIndex&lt; Scalar &gt;</type>
      <name>operator()</name>
      <anchorfile>classRTOpPack_1_1ROpMaxIndexLessThanBound.html</anchorfile>
      <anchor>aafa7cd3973e2ace6a9cb1f2876dad966</anchor>
      <arglist>(const ReductTarget &amp;reduct_obj) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>RTOpPack::ROpMaxIndexLessThanBoundEleWiseReductionOp</name>
    <filename>classRTOpPack_1_1ROpMaxIndexLessThanBoundEleWiseReductionOp.html</filename>
    <templarg></templarg>
    <member kind="function">
      <type></type>
      <name>ROpMaxIndexLessThanBoundEleWiseReductionOp</name>
      <anchorfile>classRTOpPack_1_1ROpMaxIndexLessThanBoundEleWiseReductionOp.html</anchorfile>
      <anchor>a6deee04269298ef8d028f6dc85469ca2</anchor>
      <arglist>(const Scalar &amp;bound=ScalarTraits&lt; Scalar &gt;::zero())</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>operator()</name>
      <anchorfile>classRTOpPack_1_1ROpMaxIndexLessThanBoundEleWiseReductionOp.html</anchorfile>
      <anchor>a3911b696f24edf0748103a6177bb523b</anchor>
      <arglist>(const index_type i, const Scalar &amp;v0, ScalarIndex&lt; Scalar &gt; &amp;reduct) const </arglist>
    </member>
    <member kind="variable" protection="private">
      <type>Scalar</type>
      <name>bound_</name>
      <anchorfile>classRTOpPack_1_1ROpMaxIndexLessThanBoundEleWiseReductionOp.html</anchorfile>
      <anchor>a25e6e46dd9e0fbc58f3294d0065d01cf</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>RTOpPack::ROpMaxIndexReductObjReductionOp</name>
    <filename>classRTOpPack_1_1ROpMaxIndexReductObjReductionOp.html</filename>
    <templarg></templarg>
    <member kind="function">
      <type>void</type>
      <name>operator()</name>
      <anchorfile>classRTOpPack_1_1ROpMaxIndexReductObjReductionOp.html</anchorfile>
      <anchor>ab78cb8148e81be1459634fa9e0824203</anchor>
      <arglist>(const ScalarIndex&lt; Scalar &gt; &amp;in_reduct, ScalarIndex&lt; Scalar &gt; &amp;inout_reduct) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>RTOpPack::ROpMinIndex</name>
    <filename>classRTOpPack_1_1ROpMinIndex.html</filename>
    <templarg></templarg>
    <base>ROp_1_CoordVariantScalarReduction&lt; Scalar, ScalarIndex&lt; Scalar &gt;, ROpMinIndexEleWiseReductionOp&lt; Scalar &gt;, ROpMinIndexReductObjReductionOp&lt; Scalar &gt; &gt;</base>
    <member kind="function">
      <type></type>
      <name>ROpMinIndex</name>
      <anchorfile>classRTOpPack_1_1ROpMinIndex.html</anchorfile>
      <anchor>a6de8ddf17b64d1f4c5d72a5c172b8643</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>ScalarIndex&lt; Scalar &gt;</type>
      <name>operator()</name>
      <anchorfile>classRTOpPack_1_1ROpMinIndex.html</anchorfile>
      <anchor>a1969162476cdaf1e196604b0ddee58b4</anchor>
      <arglist>(const ReductTarget &amp;reduct_obj) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>RTOpPack::ROpMinIndexEleWiseReductionOp</name>
    <filename>classRTOpPack_1_1ROpMinIndexEleWiseReductionOp.html</filename>
    <templarg></templarg>
    <member kind="function">
      <type>void</type>
      <name>operator()</name>
      <anchorfile>classRTOpPack_1_1ROpMinIndexEleWiseReductionOp.html</anchorfile>
      <anchor>ae5b8afc109bf6880ced50441ad6d7475</anchor>
      <arglist>(const index_type i, const Scalar &amp;v0, ScalarIndex&lt; Scalar &gt; &amp;reduct) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>RTOpPack::ROpMinIndexGreaterThanBound</name>
    <filename>classRTOpPack_1_1ROpMinIndexGreaterThanBound.html</filename>
    <templarg></templarg>
    <base>ROp_1_CoordVariantScalarReduction&lt; Scalar, ScalarIndex&lt; Scalar &gt;, ROpMinIndexGreaterThanBoundEleWiseReductionOp&lt; Scalar &gt;, ROpMinIndexReductObjReductionOp&lt; Scalar &gt; &gt;</base>
    <member kind="function">
      <type></type>
      <name>ROpMinIndexGreaterThanBound</name>
      <anchorfile>classRTOpPack_1_1ROpMinIndexGreaterThanBound.html</anchorfile>
      <anchor>abea58c0f7adf12239dcc24f035304df8</anchor>
      <arglist>(const Scalar &amp;bound_in=Teuchos::ScalarTraits&lt; Scalar &gt;::zero())</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>bound</name>
      <anchorfile>classRTOpPack_1_1ROpMinIndexGreaterThanBound.html</anchorfile>
      <anchor>af6fd3913fc7e0c4f7b3dc4ee7984904c</anchor>
      <arglist>(const Scalar &amp;bound_in)</arglist>
    </member>
    <member kind="function">
      <type>ScalarIndex&lt; Scalar &gt;</type>
      <name>operator()</name>
      <anchorfile>classRTOpPack_1_1ROpMinIndexGreaterThanBound.html</anchorfile>
      <anchor>a5a6c898a74faaad24d7a67c12c03a897</anchor>
      <arglist>(const ReductTarget &amp;reduct_obj) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>RTOpPack::ROpMinIndexGreaterThanBoundEleWiseReductionOp</name>
    <filename>classRTOpPack_1_1ROpMinIndexGreaterThanBoundEleWiseReductionOp.html</filename>
    <templarg></templarg>
    <member kind="function">
      <type></type>
      <name>ROpMinIndexGreaterThanBoundEleWiseReductionOp</name>
      <anchorfile>classRTOpPack_1_1ROpMinIndexGreaterThanBoundEleWiseReductionOp.html</anchorfile>
      <anchor>a59f1ef85ced7bc4a5a43ea90fe1eaafc</anchor>
      <arglist>(const Scalar &amp;bound=ScalarTraits&lt; Scalar &gt;::zero())</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>operator()</name>
      <anchorfile>classRTOpPack_1_1ROpMinIndexGreaterThanBoundEleWiseReductionOp.html</anchorfile>
      <anchor>a113a0d74484e81ee19d429e0c94e26a0</anchor>
      <arglist>(const index_type i, const Scalar &amp;v0, ScalarIndex&lt; Scalar &gt; &amp;reduct) const </arglist>
    </member>
    <member kind="variable" protection="private">
      <type>Scalar</type>
      <name>bound_</name>
      <anchorfile>classRTOpPack_1_1ROpMinIndexGreaterThanBoundEleWiseReductionOp.html</anchorfile>
      <anchor>acb8c2a911ec66eb2ed4a6a9da1a860fe</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>RTOpPack::ROpMinIndexReductObjReductionOp</name>
    <filename>classRTOpPack_1_1ROpMinIndexReductObjReductionOp.html</filename>
    <templarg></templarg>
    <member kind="function">
      <type>void</type>
      <name>operator()</name>
      <anchorfile>classRTOpPack_1_1ROpMinIndexReductObjReductionOp.html</anchorfile>
      <anchor>ab69d9a252de2bf3c70171ba5372697d0</anchor>
      <arglist>(const ScalarIndex&lt; Scalar &gt; &amp;in_reduct, ScalarIndex&lt; Scalar &gt; &amp;inout_reduct) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>RTOpPack::ROpNorm2</name>
    <filename>classRTOpPack_1_1ROpNorm2.html</filename>
    <templarg></templarg>
    <base>ROp_1_ScalarReduction&lt; Scalar, Scalar, ROpNorm2EleWiseReduction&lt; Scalar &gt; &gt;</base>
    <member kind="typedef">
      <type>Teuchos::ScalarTraits&lt; Scalar &gt;</type>
      <name>ST</name>
      <anchorfile>classRTOpPack_1_1ROpNorm2.html</anchorfile>
      <anchor>aa4a13ad8ac8f547d8ce24742dfd20b98</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ROpNorm2</name>
      <anchorfile>classRTOpPack_1_1ROpNorm2.html</anchorfile>
      <anchor>a4c666897029acde1b3b66ccfac86bdc7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>ST::magnitudeType</type>
      <name>operator()</name>
      <anchorfile>classRTOpPack_1_1ROpNorm2.html</anchorfile>
      <anchor>af7799c8bba9a6e5eaddbc2d159539410</anchor>
      <arglist>(const ReductTarget &amp;reduct_obj) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>RTOpPack::ROpNorm2EleWiseReduction</name>
    <filename>classRTOpPack_1_1ROpNorm2EleWiseReduction.html</filename>
    <templarg></templarg>
    <member kind="function">
      <type>void</type>
      <name>operator()</name>
      <anchorfile>classRTOpPack_1_1ROpNorm2EleWiseReduction.html</anchorfile>
      <anchor>a80857eeea2727b6a4a63c79923713b4a</anchor>
      <arglist>(const Scalar &amp;v0, Scalar &amp;reduct) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>RTOpPack::ROpScalarReductionWithOpBase</name>
    <filename>classRTOpPack_1_1ROpScalarReductionWithOpBase.html</filename>
    <templarg>Scalar</templarg>
    <templarg>ConcreteReductObj</templarg>
    <templarg>ReductObjReduction</templarg>
    <base>RTOpPack::RTOpT</base>
    <member kind="typedef">
      <type>RTOpT&lt; Scalar &gt;::primitive_value_type</type>
      <name>primitive_value_type</name>
      <anchorfile>classRTOpPack_1_1ROpScalarReductionWithOpBase.html</anchorfile>
      <anchor>ab55ff2c4e1f6a11e1f21af4eec4e6522</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ROpScalarReductionWithOpBase</name>
      <anchorfile>classRTOpPack_1_1ROpScalarReductionWithOpBase.html</anchorfile>
      <anchor>a317530d4050a195f71b3294b155e4d34</anchor>
      <arglist>(const ConcreteReductObj &amp;initReductObjValue_in=ScalarTraits&lt; Scalar &gt;::zero(), ReductObjReduction reductObjReduction_in=ReductObjReduction())</arglist>
    </member>
    <member kind="function">
      <type>const ConcreteReductObj &amp;</type>
      <name>getRawVal</name>
      <anchorfile>classRTOpPack_1_1ROpScalarReductionWithOpBase.html</anchorfile>
      <anchor>a003d82d6aec144efc6660ce6eb9d8ab0</anchor>
      <arglist>(const ReductTarget &amp;reduct_obj) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setRawVal</name>
      <anchorfile>classRTOpPack_1_1ROpScalarReductionWithOpBase.html</anchorfile>
      <anchor>a1df8c93f6594c0ffac82e089e14c9ccc</anchor>
      <arglist>(const ConcreteReductObj &amp;rawVal, const Ptr&lt; ReductTarget &gt; &amp;reduct_obj) const </arglist>
    </member>
    <member kind="function">
      <type>ConcreteReductObj</type>
      <name>operator()</name>
      <anchorfile>classRTOpPack_1_1ROpScalarReductionWithOpBase.html</anchorfile>
      <anchor>a7672316b3407511e563ac026351b0c31</anchor>
      <arglist>(const ReductTarget &amp;reduct_obj) const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classRTOpPack_1_1ROpScalarReductionWithOpBase.html</anchorfile>
      <anchor>a1123b072f525e06576e76887abf8bf2c</anchor>
      <arglist>(ConcreteReductObj, initReductObjValue)</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>ReductObjReduction</type>
      <name>reductObjReduction_</name>
      <anchorfile>classRTOpPack_1_1ROpScalarReductionWithOpBase.html</anchorfile>
      <anchor>a36d1996058f74e06c5650c8305c13f1b</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>get_reduct_type_num_entries_impl</name>
      <anchorfile>classRTOpPack_1_1ROpScalarReductionWithOpBase.html</anchorfile>
      <anchor>aa65c0b3842ac5d7063f11b6058812473</anchor>
      <arglist>(const Ptr&lt; int &gt; &amp;num_values, const Ptr&lt; int &gt; &amp;num_indexes, const Ptr&lt; int &gt; &amp;num_chars) const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; ReductTarget &gt;</type>
      <name>reduct_obj_create_impl</name>
      <anchorfile>classRTOpPack_1_1ROpScalarReductionWithOpBase.html</anchorfile>
      <anchor>aaed0b72221cba839f54121b5a7063ab3</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>reduce_reduct_objs_impl</name>
      <anchorfile>classRTOpPack_1_1ROpScalarReductionWithOpBase.html</anchorfile>
      <anchor>a5f7aedfd127cafe041ce7361315329d9</anchor>
      <arglist>(const ReductTarget &amp;in_reduct_obj, const Ptr&lt; ReductTarget &gt; &amp;inout_reduct_obj) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>reduct_obj_reinit_impl</name>
      <anchorfile>classRTOpPack_1_1ROpScalarReductionWithOpBase.html</anchorfile>
      <anchor>ac45636fec13010e8cd5a68f834e5c6ab</anchor>
      <arglist>(const Ptr&lt; ReductTarget &gt; &amp;reduct_obj) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>extract_reduct_obj_state_impl</name>
      <anchorfile>classRTOpPack_1_1ROpScalarReductionWithOpBase.html</anchorfile>
      <anchor>a6bb80030a72b65f37e747a559a99fba6</anchor>
      <arglist>(const ReductTarget &amp;reduct_obj, const ArrayView&lt; primitive_value_type &gt; &amp;value_data, const ArrayView&lt; index_type &gt; &amp;index_data, const ArrayView&lt; char_type &gt; &amp;char_data) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>load_reduct_obj_state_impl</name>
      <anchorfile>classRTOpPack_1_1ROpScalarReductionWithOpBase.html</anchorfile>
      <anchor>abc0e59373fe5a3b58a93d501c6a3df22</anchor>
      <arglist>(const ArrayView&lt; const primitive_value_type &gt; &amp;value_data, const ArrayView&lt; const index_type &gt; &amp;index_data, const ArrayView&lt; const char_type &gt; &amp;char_data, const Ptr&lt; ReductTarget &gt; &amp;reduct_obj) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ROpScalarReductionWithOpBase&lt; Scalar, ReductScalar, ReductObjReduction &gt;</name>
    <filename>classRTOpPack_1_1ROpScalarReductionWithOpBase.html</filename>
    <base>RTOpPack::RTOpT</base>
    <member kind="typedef">
      <type>RTOpT&lt; Scalar &gt;::primitive_value_type</type>
      <name>primitive_value_type</name>
      <anchorfile>classRTOpPack_1_1ROpScalarReductionWithOpBase.html</anchorfile>
      <anchor>ab55ff2c4e1f6a11e1f21af4eec4e6522</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ROpScalarReductionWithOpBase</name>
      <anchorfile>classRTOpPack_1_1ROpScalarReductionWithOpBase.html</anchorfile>
      <anchor>a317530d4050a195f71b3294b155e4d34</anchor>
      <arglist>(const ReductScalar &amp;initReductObjValue_in=ScalarTraits&lt; Scalar &gt;::zero(), ReductObjReduction reductObjReduction_in=ReductObjReduction())</arglist>
    </member>
    <member kind="function">
      <type>const ReductScalar &amp;</type>
      <name>getRawVal</name>
      <anchorfile>classRTOpPack_1_1ROpScalarReductionWithOpBase.html</anchorfile>
      <anchor>a003d82d6aec144efc6660ce6eb9d8ab0</anchor>
      <arglist>(const ReductTarget &amp;reduct_obj) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setRawVal</name>
      <anchorfile>classRTOpPack_1_1ROpScalarReductionWithOpBase.html</anchorfile>
      <anchor>a1df8c93f6594c0ffac82e089e14c9ccc</anchor>
      <arglist>(const ReductScalar &amp;rawVal, const Ptr&lt; ReductTarget &gt; &amp;reduct_obj) const</arglist>
    </member>
    <member kind="function">
      <type>ReductScalar</type>
      <name>operator()</name>
      <anchorfile>classRTOpPack_1_1ROpScalarReductionWithOpBase.html</anchorfile>
      <anchor>a7672316b3407511e563ac026351b0c31</anchor>
      <arglist>(const ReductTarget &amp;reduct_obj) const</arglist>
    </member>
    <member kind="function" protection="protected">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classRTOpPack_1_1ROpScalarReductionWithOpBase.html</anchorfile>
      <anchor>a1123b072f525e06576e76887abf8bf2c</anchor>
      <arglist>(ReductScalar, initReductObjValue)</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>ReductObjReduction</type>
      <name>reductObjReduction_</name>
      <anchorfile>classRTOpPack_1_1ROpScalarReductionWithOpBase.html</anchorfile>
      <anchor>a36d1996058f74e06c5650c8305c13f1b</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>get_reduct_type_num_entries_impl</name>
      <anchorfile>classRTOpPack_1_1ROpScalarReductionWithOpBase.html</anchorfile>
      <anchor>aa65c0b3842ac5d7063f11b6058812473</anchor>
      <arglist>(const Ptr&lt; int &gt; &amp;num_values, const Ptr&lt; int &gt; &amp;num_indexes, const Ptr&lt; int &gt; &amp;num_chars) const</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; ReductTarget &gt;</type>
      <name>reduct_obj_create_impl</name>
      <anchorfile>classRTOpPack_1_1ROpScalarReductionWithOpBase.html</anchorfile>
      <anchor>aaed0b72221cba839f54121b5a7063ab3</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>reduce_reduct_objs_impl</name>
      <anchorfile>classRTOpPack_1_1ROpScalarReductionWithOpBase.html</anchorfile>
      <anchor>a5f7aedfd127cafe041ce7361315329d9</anchor>
      <arglist>(const ReductTarget &amp;in_reduct_obj, const Ptr&lt; ReductTarget &gt; &amp;inout_reduct_obj) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>reduct_obj_reinit_impl</name>
      <anchorfile>classRTOpPack_1_1ROpScalarReductionWithOpBase.html</anchorfile>
      <anchor>ac45636fec13010e8cd5a68f834e5c6ab</anchor>
      <arglist>(const Ptr&lt; ReductTarget &gt; &amp;reduct_obj) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>extract_reduct_obj_state_impl</name>
      <anchorfile>classRTOpPack_1_1ROpScalarReductionWithOpBase.html</anchorfile>
      <anchor>a6bb80030a72b65f37e747a559a99fba6</anchor>
      <arglist>(const ReductTarget &amp;reduct_obj, const ArrayView&lt; primitive_value_type &gt; &amp;value_data, const ArrayView&lt; index_type &gt; &amp;index_data, const ArrayView&lt; char_type &gt; &amp;char_data) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>load_reduct_obj_state_impl</name>
      <anchorfile>classRTOpPack_1_1ROpScalarReductionWithOpBase.html</anchorfile>
      <anchor>abc0e59373fe5a3b58a93d501c6a3df22</anchor>
      <arglist>(const ArrayView&lt; const primitive_value_type &gt; &amp;value_data, const ArrayView&lt; const index_type &gt; &amp;index_data, const ArrayView&lt; const char_type &gt; &amp;char_data, const Ptr&lt; ReductTarget &gt; &amp;reduct_obj) const</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ROpScalarReductionWithOpBase&lt; Scalar, Scalar, SumScalarReductObjReduction&lt; Scalar &gt; &gt;</name>
    <filename>classRTOpPack_1_1ROpScalarReductionWithOpBase.html</filename>
    <base>RTOpPack::RTOpT</base>
    <member kind="typedef">
      <type>RTOpT&lt; Scalar &gt;::primitive_value_type</type>
      <name>primitive_value_type</name>
      <anchorfile>classRTOpPack_1_1ROpScalarReductionWithOpBase.html</anchorfile>
      <anchor>ab55ff2c4e1f6a11e1f21af4eec4e6522</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ROpScalarReductionWithOpBase</name>
      <anchorfile>classRTOpPack_1_1ROpScalarReductionWithOpBase.html</anchorfile>
      <anchor>a317530d4050a195f71b3294b155e4d34</anchor>
      <arglist>(const Scalar &amp;initReductObjValue_in=ScalarTraits&lt; Scalar &gt;::zero(), SumScalarReductObjReduction&lt; Scalar &gt; reductObjReduction_in=SumScalarReductObjReduction&lt; Scalar &gt;())</arglist>
    </member>
    <member kind="function">
      <type>const Scalar &amp;</type>
      <name>getRawVal</name>
      <anchorfile>classRTOpPack_1_1ROpScalarReductionWithOpBase.html</anchorfile>
      <anchor>a003d82d6aec144efc6660ce6eb9d8ab0</anchor>
      <arglist>(const ReductTarget &amp;reduct_obj) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setRawVal</name>
      <anchorfile>classRTOpPack_1_1ROpScalarReductionWithOpBase.html</anchorfile>
      <anchor>a1df8c93f6594c0ffac82e089e14c9ccc</anchor>
      <arglist>(const Scalar &amp;rawVal, const Ptr&lt; ReductTarget &gt; &amp;reduct_obj) const</arglist>
    </member>
    <member kind="function">
      <type>Scalar</type>
      <name>operator()</name>
      <anchorfile>classRTOpPack_1_1ROpScalarReductionWithOpBase.html</anchorfile>
      <anchor>a7672316b3407511e563ac026351b0c31</anchor>
      <arglist>(const ReductTarget &amp;reduct_obj) const</arglist>
    </member>
    <member kind="function" protection="protected">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classRTOpPack_1_1ROpScalarReductionWithOpBase.html</anchorfile>
      <anchor>a1123b072f525e06576e76887abf8bf2c</anchor>
      <arglist>(Scalar, initReductObjValue)</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>SumScalarReductObjReduction&lt; Scalar &gt;</type>
      <name>reductObjReduction_</name>
      <anchorfile>classRTOpPack_1_1ROpScalarReductionWithOpBase.html</anchorfile>
      <anchor>a36d1996058f74e06c5650c8305c13f1b</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>get_reduct_type_num_entries_impl</name>
      <anchorfile>classRTOpPack_1_1ROpScalarReductionWithOpBase.html</anchorfile>
      <anchor>aa65c0b3842ac5d7063f11b6058812473</anchor>
      <arglist>(const Ptr&lt; int &gt; &amp;num_values, const Ptr&lt; int &gt; &amp;num_indexes, const Ptr&lt; int &gt; &amp;num_chars) const</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; ReductTarget &gt;</type>
      <name>reduct_obj_create_impl</name>
      <anchorfile>classRTOpPack_1_1ROpScalarReductionWithOpBase.html</anchorfile>
      <anchor>aaed0b72221cba839f54121b5a7063ab3</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>reduce_reduct_objs_impl</name>
      <anchorfile>classRTOpPack_1_1ROpScalarReductionWithOpBase.html</anchorfile>
      <anchor>a5f7aedfd127cafe041ce7361315329d9</anchor>
      <arglist>(const ReductTarget &amp;in_reduct_obj, const Ptr&lt; ReductTarget &gt; &amp;inout_reduct_obj) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>reduct_obj_reinit_impl</name>
      <anchorfile>classRTOpPack_1_1ROpScalarReductionWithOpBase.html</anchorfile>
      <anchor>ac45636fec13010e8cd5a68f834e5c6ab</anchor>
      <arglist>(const Ptr&lt; ReductTarget &gt; &amp;reduct_obj) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>extract_reduct_obj_state_impl</name>
      <anchorfile>classRTOpPack_1_1ROpScalarReductionWithOpBase.html</anchorfile>
      <anchor>a6bb80030a72b65f37e747a559a99fba6</anchor>
      <arglist>(const ReductTarget &amp;reduct_obj, const ArrayView&lt; primitive_value_type &gt; &amp;value_data, const ArrayView&lt; index_type &gt; &amp;index_data, const ArrayView&lt; char_type &gt; &amp;char_data) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>load_reduct_obj_state_impl</name>
      <anchorfile>classRTOpPack_1_1ROpScalarReductionWithOpBase.html</anchorfile>
      <anchor>abc0e59373fe5a3b58a93d501c6a3df22</anchor>
      <arglist>(const ArrayView&lt; const primitive_value_type &gt; &amp;value_data, const ArrayView&lt; const index_type &gt; &amp;index_data, const ArrayView&lt; const char_type &gt; &amp;char_data, const Ptr&lt; ReductTarget &gt; &amp;reduct_obj) const</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ROpScalarReductionWithOpBase&lt; Scalar, ScalarIndex&lt; Scalar &gt;, ROpMaxIndexReductObjReductionOp&lt; Scalar &gt; &gt;</name>
    <filename>classRTOpPack_1_1ROpScalarReductionWithOpBase.html</filename>
    <base>RTOpPack::RTOpT</base>
    <member kind="typedef">
      <type>RTOpT&lt; Scalar &gt;::primitive_value_type</type>
      <name>primitive_value_type</name>
      <anchorfile>classRTOpPack_1_1ROpScalarReductionWithOpBase.html</anchorfile>
      <anchor>ab55ff2c4e1f6a11e1f21af4eec4e6522</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ROpScalarReductionWithOpBase</name>
      <anchorfile>classRTOpPack_1_1ROpScalarReductionWithOpBase.html</anchorfile>
      <anchor>a317530d4050a195f71b3294b155e4d34</anchor>
      <arglist>(const ScalarIndex&lt; Scalar &gt; &amp;initReductObjValue_in=ScalarTraits&lt; Scalar &gt;::zero(), ROpMaxIndexReductObjReductionOp&lt; Scalar &gt; reductObjReduction_in=ROpMaxIndexReductObjReductionOp&lt; Scalar &gt;())</arglist>
    </member>
    <member kind="function">
      <type>const ScalarIndex&lt; Scalar &gt; &amp;</type>
      <name>getRawVal</name>
      <anchorfile>classRTOpPack_1_1ROpScalarReductionWithOpBase.html</anchorfile>
      <anchor>a003d82d6aec144efc6660ce6eb9d8ab0</anchor>
      <arglist>(const ReductTarget &amp;reduct_obj) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setRawVal</name>
      <anchorfile>classRTOpPack_1_1ROpScalarReductionWithOpBase.html</anchorfile>
      <anchor>a1df8c93f6594c0ffac82e089e14c9ccc</anchor>
      <arglist>(const ScalarIndex&lt; Scalar &gt; &amp;rawVal, const Ptr&lt; ReductTarget &gt; &amp;reduct_obj) const</arglist>
    </member>
    <member kind="function">
      <type>ScalarIndex&lt; Scalar &gt;</type>
      <name>operator()</name>
      <anchorfile>classRTOpPack_1_1ROpScalarReductionWithOpBase.html</anchorfile>
      <anchor>a7672316b3407511e563ac026351b0c31</anchor>
      <arglist>(const ReductTarget &amp;reduct_obj) const</arglist>
    </member>
    <member kind="function" protection="protected">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classRTOpPack_1_1ROpScalarReductionWithOpBase.html</anchorfile>
      <anchor>a1123b072f525e06576e76887abf8bf2c</anchor>
      <arglist>(ScalarIndex&lt; Scalar &gt;, initReductObjValue)</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>ROpMaxIndexReductObjReductionOp&lt; Scalar &gt;</type>
      <name>reductObjReduction_</name>
      <anchorfile>classRTOpPack_1_1ROpScalarReductionWithOpBase.html</anchorfile>
      <anchor>a36d1996058f74e06c5650c8305c13f1b</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>get_reduct_type_num_entries_impl</name>
      <anchorfile>classRTOpPack_1_1ROpScalarReductionWithOpBase.html</anchorfile>
      <anchor>aa65c0b3842ac5d7063f11b6058812473</anchor>
      <arglist>(const Ptr&lt; int &gt; &amp;num_values, const Ptr&lt; int &gt; &amp;num_indexes, const Ptr&lt; int &gt; &amp;num_chars) const</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; ReductTarget &gt;</type>
      <name>reduct_obj_create_impl</name>
      <anchorfile>classRTOpPack_1_1ROpScalarReductionWithOpBase.html</anchorfile>
      <anchor>aaed0b72221cba839f54121b5a7063ab3</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>reduce_reduct_objs_impl</name>
      <anchorfile>classRTOpPack_1_1ROpScalarReductionWithOpBase.html</anchorfile>
      <anchor>a5f7aedfd127cafe041ce7361315329d9</anchor>
      <arglist>(const ReductTarget &amp;in_reduct_obj, const Ptr&lt; ReductTarget &gt; &amp;inout_reduct_obj) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>reduct_obj_reinit_impl</name>
      <anchorfile>classRTOpPack_1_1ROpScalarReductionWithOpBase.html</anchorfile>
      <anchor>ac45636fec13010e8cd5a68f834e5c6ab</anchor>
      <arglist>(const Ptr&lt; ReductTarget &gt; &amp;reduct_obj) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>extract_reduct_obj_state_impl</name>
      <anchorfile>classRTOpPack_1_1ROpScalarReductionWithOpBase.html</anchorfile>
      <anchor>a6bb80030a72b65f37e747a559a99fba6</anchor>
      <arglist>(const ReductTarget &amp;reduct_obj, const ArrayView&lt; primitive_value_type &gt; &amp;value_data, const ArrayView&lt; index_type &gt; &amp;index_data, const ArrayView&lt; char_type &gt; &amp;char_data) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>load_reduct_obj_state_impl</name>
      <anchorfile>classRTOpPack_1_1ROpScalarReductionWithOpBase.html</anchorfile>
      <anchor>abc0e59373fe5a3b58a93d501c6a3df22</anchor>
      <arglist>(const ArrayView&lt; const primitive_value_type &gt; &amp;value_data, const ArrayView&lt; const index_type &gt; &amp;index_data, const ArrayView&lt; const char_type &gt; &amp;char_data, const Ptr&lt; ReductTarget &gt; &amp;reduct_obj) const</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ROpScalarReductionWithOpBase&lt; Scalar, ScalarIndex&lt; Scalar &gt;, ROpMinIndexReductObjReductionOp&lt; Scalar &gt; &gt;</name>
    <filename>classRTOpPack_1_1ROpScalarReductionWithOpBase.html</filename>
    <base>RTOpPack::RTOpT</base>
    <member kind="typedef">
      <type>RTOpT&lt; Scalar &gt;::primitive_value_type</type>
      <name>primitive_value_type</name>
      <anchorfile>classRTOpPack_1_1ROpScalarReductionWithOpBase.html</anchorfile>
      <anchor>ab55ff2c4e1f6a11e1f21af4eec4e6522</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ROpScalarReductionWithOpBase</name>
      <anchorfile>classRTOpPack_1_1ROpScalarReductionWithOpBase.html</anchorfile>
      <anchor>a317530d4050a195f71b3294b155e4d34</anchor>
      <arglist>(const ScalarIndex&lt; Scalar &gt; &amp;initReductObjValue_in=ScalarTraits&lt; Scalar &gt;::zero(), ROpMinIndexReductObjReductionOp&lt; Scalar &gt; reductObjReduction_in=ROpMinIndexReductObjReductionOp&lt; Scalar &gt;())</arglist>
    </member>
    <member kind="function">
      <type>const ScalarIndex&lt; Scalar &gt; &amp;</type>
      <name>getRawVal</name>
      <anchorfile>classRTOpPack_1_1ROpScalarReductionWithOpBase.html</anchorfile>
      <anchor>a003d82d6aec144efc6660ce6eb9d8ab0</anchor>
      <arglist>(const ReductTarget &amp;reduct_obj) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setRawVal</name>
      <anchorfile>classRTOpPack_1_1ROpScalarReductionWithOpBase.html</anchorfile>
      <anchor>a1df8c93f6594c0ffac82e089e14c9ccc</anchor>
      <arglist>(const ScalarIndex&lt; Scalar &gt; &amp;rawVal, const Ptr&lt; ReductTarget &gt; &amp;reduct_obj) const</arglist>
    </member>
    <member kind="function">
      <type>ScalarIndex&lt; Scalar &gt;</type>
      <name>operator()</name>
      <anchorfile>classRTOpPack_1_1ROpScalarReductionWithOpBase.html</anchorfile>
      <anchor>a7672316b3407511e563ac026351b0c31</anchor>
      <arglist>(const ReductTarget &amp;reduct_obj) const</arglist>
    </member>
    <member kind="function" protection="protected">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classRTOpPack_1_1ROpScalarReductionWithOpBase.html</anchorfile>
      <anchor>a1123b072f525e06576e76887abf8bf2c</anchor>
      <arglist>(ScalarIndex&lt; Scalar &gt;, initReductObjValue)</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>ROpMinIndexReductObjReductionOp&lt; Scalar &gt;</type>
      <name>reductObjReduction_</name>
      <anchorfile>classRTOpPack_1_1ROpScalarReductionWithOpBase.html</anchorfile>
      <anchor>a36d1996058f74e06c5650c8305c13f1b</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>get_reduct_type_num_entries_impl</name>
      <anchorfile>classRTOpPack_1_1ROpScalarReductionWithOpBase.html</anchorfile>
      <anchor>aa65c0b3842ac5d7063f11b6058812473</anchor>
      <arglist>(const Ptr&lt; int &gt; &amp;num_values, const Ptr&lt; int &gt; &amp;num_indexes, const Ptr&lt; int &gt; &amp;num_chars) const</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; ReductTarget &gt;</type>
      <name>reduct_obj_create_impl</name>
      <anchorfile>classRTOpPack_1_1ROpScalarReductionWithOpBase.html</anchorfile>
      <anchor>aaed0b72221cba839f54121b5a7063ab3</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>reduce_reduct_objs_impl</name>
      <anchorfile>classRTOpPack_1_1ROpScalarReductionWithOpBase.html</anchorfile>
      <anchor>a5f7aedfd127cafe041ce7361315329d9</anchor>
      <arglist>(const ReductTarget &amp;in_reduct_obj, const Ptr&lt; ReductTarget &gt; &amp;inout_reduct_obj) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>reduct_obj_reinit_impl</name>
      <anchorfile>classRTOpPack_1_1ROpScalarReductionWithOpBase.html</anchorfile>
      <anchor>ac45636fec13010e8cd5a68f834e5c6ab</anchor>
      <arglist>(const Ptr&lt; ReductTarget &gt; &amp;reduct_obj) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>extract_reduct_obj_state_impl</name>
      <anchorfile>classRTOpPack_1_1ROpScalarReductionWithOpBase.html</anchorfile>
      <anchor>a6bb80030a72b65f37e747a559a99fba6</anchor>
      <arglist>(const ReductTarget &amp;reduct_obj, const ArrayView&lt; primitive_value_type &gt; &amp;value_data, const ArrayView&lt; index_type &gt; &amp;index_data, const ArrayView&lt; char_type &gt; &amp;char_data) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>load_reduct_obj_state_impl</name>
      <anchorfile>classRTOpPack_1_1ROpScalarReductionWithOpBase.html</anchorfile>
      <anchor>abc0e59373fe5a3b58a93d501c6a3df22</anchor>
      <arglist>(const ArrayView&lt; const primitive_value_type &gt; &amp;value_data, const ArrayView&lt; const index_type &gt; &amp;index_data, const ArrayView&lt; const char_type &gt; &amp;char_data, const Ptr&lt; ReductTarget &gt; &amp;reduct_obj) const</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>RTOpPack::ROpWeightedNorm2</name>
    <filename>classRTOpPack_1_1ROpWeightedNorm2.html</filename>
    <templarg></templarg>
    <base>ROp_2_ScalarReduction&lt; Scalar, Scalar, ROpWeightedNorm2EleWiseReduction&lt; Scalar &gt; &gt;</base>
    <member kind="typedef">
      <type>Teuchos::ScalarTraits&lt; Scalar &gt;</type>
      <name>ST</name>
      <anchorfile>classRTOpPack_1_1ROpWeightedNorm2.html</anchorfile>
      <anchor>aece3602479a439b818c57d3a5df000e2</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ROpWeightedNorm2</name>
      <anchorfile>classRTOpPack_1_1ROpWeightedNorm2.html</anchorfile>
      <anchor>ab0c5e5cb1ae41c07c38f784a131c59aa</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>ST::magnitudeType</type>
      <name>operator()</name>
      <anchorfile>classRTOpPack_1_1ROpWeightedNorm2.html</anchorfile>
      <anchor>a916e095ba8a2cf901ddd4bd81e4bc6dc</anchor>
      <arglist>(const ReductTarget &amp;reduct_obj) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>RTOpPack::ROpWeightedNorm2EleWiseReduction</name>
    <filename>classRTOpPack_1_1ROpWeightedNorm2EleWiseReduction.html</filename>
    <templarg></templarg>
    <member kind="function">
      <type>void</type>
      <name>operator()</name>
      <anchorfile>classRTOpPack_1_1ROpWeightedNorm2EleWiseReduction.html</anchorfile>
      <anchor>a11cb4c09f76602def378f2e8df82f8b9</anchor>
      <arglist>(const Scalar &amp;v0, const Scalar &amp;v1, Scalar &amp;reduct) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>RTOpPack::RTOpServer</name>
    <filename>classRTOpPack_1_1RTOpServer.html</filename>
    <templarg></templarg>
    <member kind="function">
      <type>void</type>
      <name>add_op_factory</name>
      <anchorfile>classRTOpPack_1_1RTOpServer.html</anchorfile>
      <anchor>a51f52fd3db29ad0a71a3715606d1e03c</anchor>
      <arglist>(const Teuchos::RCP&lt; Teuchos::AbstractFactory&lt; RTOpPack::RTOpT&lt; Scalar &gt; &gt; &gt; &amp;op_factory)</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; Teuchos::AbstractFactory&lt; RTOpPack::RTOpT&lt; Scalar &gt; &gt; &gt;</type>
      <name>get_op_factory</name>
      <anchorfile>classRTOpPack_1_1RTOpServer.html</anchorfile>
      <anchor>ab82ca2981acbb7100c95072e4e3852dd</anchor>
      <arglist>(const char op_name[]) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>print_op_factories</name>
      <anchorfile>classRTOpPack_1_1RTOpServer.html</anchorfile>
      <anchor>a6631e7dc974f7e8c5a396f93573f096f</anchor>
      <arglist>(std::ostream &amp;o) const </arglist>
    </member>
    <member kind="typedef" protection="private">
      <type>std::map&lt; std::string, Teuchos::RCP&lt; Teuchos::AbstractFactory&lt; RTOpT&lt; Scalar &gt; &gt; &gt; &gt;</type>
      <name>op_factories_t</name>
      <anchorfile>classRTOpPack_1_1RTOpServer.html</anchorfile>
      <anchor>a4e649c6de0e00259ea39a428c6d66271</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>op_factories_t</type>
      <name>op_factories_</name>
      <anchorfile>classRTOpPack_1_1RTOpServer.html</anchorfile>
      <anchor>a35367770ff4bd6e7c3087c28f1af1bb8</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>RTOpPack::RTOpSubRangeDecorator</name>
    <filename>classRTOpPack_1_1RTOpSubRangeDecorator.html</filename>
    <templarg></templarg>
    <base>RTOpPack::RTOpT</base>
    <member kind="variable" protection="private">
      <type>Teuchos::ConstNonconstObjectContainer&lt; RTOpT&lt; Scalar &gt; &gt;</type>
      <name>op_</name>
      <anchorfile>classRTOpPack_1_1RTOpSubRangeDecorator.html</anchorfile>
      <anchor>a15623e14e2ba4abda51f8205b71b14fc</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>Ordinal</type>
      <name>first_ele_offset_</name>
      <anchorfile>classRTOpPack_1_1RTOpSubRangeDecorator.html</anchorfile>
      <anchor>abe75c113597ef94c6e40e2f3b385ad6b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>Ordinal</type>
      <name>sub_dim_</name>
      <anchorfile>classRTOpPack_1_1RTOpSubRangeDecorator.html</anchorfile>
      <anchor>a950e65eaf8cacccb5ba5e3c0c0c1532e</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>RTOpT&lt; Scalar &gt;::primitive_value_type</type>
      <name>primitive_value_type</name>
      <anchorfile>classRTOpPack_1_1RTOpSubRangeDecorator.html</anchorfile>
      <anchor>a8c8c68677349190f75399e301e7f60f4</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>RTOpSubRangeDecorator</name>
      <anchorfile>classRTOpPack_1_1RTOpSubRangeDecorator.html</anchorfile>
      <anchor>a4a7002cc4af1a48cdd3a7e869dd7269b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>RTOpSubRangeDecorator</name>
      <anchorfile>classRTOpPack_1_1RTOpSubRangeDecorator.html</anchorfile>
      <anchor>a888eead158ad907a1920bf412feaa5fe</anchor>
      <arglist>(const RCP&lt; RTOpT&lt; Scalar &gt; &gt; &amp;op, const Ordinal first_ele_offset=0, const Ordinal sub_dim=-1)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>RTOpSubRangeDecorator</name>
      <anchorfile>classRTOpPack_1_1RTOpSubRangeDecorator.html</anchorfile>
      <anchor>afb3d88f3d76c3a9f3797fb090b8ee4f4</anchor>
      <arglist>(const RCP&lt; const RTOpT&lt; Scalar &gt; &gt; &amp;op, const Ordinal first_ele_offset=0, const Ordinal sub_dim=-1)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>nonconstInitialize</name>
      <anchorfile>classRTOpPack_1_1RTOpSubRangeDecorator.html</anchorfile>
      <anchor>af4a965c36dd2eee40696d76c0d5786dc</anchor>
      <arglist>(const RCP&lt; RTOpT&lt; Scalar &gt; &gt; &amp;op, const Ordinal first_ele_offset=0, const Ordinal sub_dim=-1)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initialize</name>
      <anchorfile>classRTOpPack_1_1RTOpSubRangeDecorator.html</anchorfile>
      <anchor>a28de290742475c119889ed8aedfd707c</anchor>
      <arglist>(const RCP&lt; const RTOpT&lt; Scalar &gt; &gt; &amp;op, const Ordinal first_ele_offset=0, const Ordinal sub_dim=-1)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; RTOpT&lt; Scalar &gt; &gt;</type>
      <name>getNonconstOp</name>
      <anchorfile>classRTOpPack_1_1RTOpSubRangeDecorator.html</anchorfile>
      <anchor>a518adcfb12edb727210c16ccdce0c081</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const RTOpT&lt; Scalar &gt; &gt;</type>
      <name>getOp</name>
      <anchorfile>classRTOpPack_1_1RTOpSubRangeDecorator.html</anchorfile>
      <anchor>aae6cdc01ead04baba8e450ca10f40cfc</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>get_reduct_type_num_entries_impl</name>
      <anchorfile>classRTOpPack_1_1RTOpSubRangeDecorator.html</anchorfile>
      <anchor>a067bb91e81035e344a07266a3f28d98d</anchor>
      <arglist>(const Ptr&lt; int &gt; &amp;num_values, const Ptr&lt; int &gt; &amp;num_indexes, const Ptr&lt; int &gt; &amp;num_chars) const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; ReductTarget &gt;</type>
      <name>reduct_obj_create_impl</name>
      <anchorfile>classRTOpPack_1_1RTOpSubRangeDecorator.html</anchorfile>
      <anchor>ad25bb78e6cca3079513740568f346742</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>reduce_reduct_objs_impl</name>
      <anchorfile>classRTOpPack_1_1RTOpSubRangeDecorator.html</anchorfile>
      <anchor>ab61eaaa44e1a3dd404b25d8102caeba2</anchor>
      <arglist>(const ReductTarget &amp;in_reduct_obj, const Ptr&lt; ReductTarget &gt; &amp;inout_reduct_obj) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>reduct_obj_reinit_impl</name>
      <anchorfile>classRTOpPack_1_1RTOpSubRangeDecorator.html</anchorfile>
      <anchor>a1f8d9eac8f379866fa6cec830e81c557</anchor>
      <arglist>(const Ptr&lt; ReductTarget &gt; &amp;reduct_obj) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>extract_reduct_obj_state_impl</name>
      <anchorfile>classRTOpPack_1_1RTOpSubRangeDecorator.html</anchorfile>
      <anchor>ab448b3f2a8441e241dea592632051eb7</anchor>
      <arglist>(const ReductTarget &amp;reduct_obj, const ArrayView&lt; primitive_value_type &gt; &amp;value_data, const ArrayView&lt; index_type &gt; &amp;index_data, const ArrayView&lt; char_type &gt; &amp;char_data) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>load_reduct_obj_state_impl</name>
      <anchorfile>classRTOpPack_1_1RTOpSubRangeDecorator.html</anchorfile>
      <anchor>ac925c861a9192eb32b2783c1b5a7b6d8</anchor>
      <arglist>(const ArrayView&lt; const primitive_value_type &gt; &amp;value_data, const ArrayView&lt; const index_type &gt; &amp;index_data, const ArrayView&lt; const char_type &gt; &amp;char_data, const Ptr&lt; ReductTarget &gt; &amp;reduct_obj) const </arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>op_name_impl</name>
      <anchorfile>classRTOpPack_1_1RTOpSubRangeDecorator.html</anchorfile>
      <anchor>a37aedfe324bf94ee57c081a8346e9be1</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>coord_invariant_impl</name>
      <anchorfile>classRTOpPack_1_1RTOpSubRangeDecorator.html</anchorfile>
      <anchor>a86e20040e514ba74581554e1be862eeb</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>apply_op_impl</name>
      <anchorfile>classRTOpPack_1_1RTOpSubRangeDecorator.html</anchorfile>
      <anchor>ac4b86b851b82b4ac3623110266167d04</anchor>
      <arglist>(const ArrayView&lt; const ConstSubVectorView&lt; Scalar &gt; &gt; &amp;sub_vecs, const ArrayView&lt; const SubVectorView&lt; Scalar &gt; &gt; &amp;targ_sub_vecs, const Ptr&lt; ReductTarget &gt; &amp;reduct_obj) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>RTOpPack::RTOpT</name>
    <filename>classRTOpPack_1_1RTOpT.html</filename>
    <templarg>Scalar</templarg>
    <member kind="function" protection="private">
      <type>void</type>
      <name>throwNoReductError</name>
      <anchorfile>classRTOpPack_1_1RTOpT.html</anchorfile>
      <anchor>aed3f5e275d2b6112c0b0d6e474eb876f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="variable" protection="private">
      <type>std::string</type>
      <name>op_name_</name>
      <anchorfile>classRTOpPack_1_1RTOpT.html</anchorfile>
      <anchor>a0e24c86b03f9e6c3d45fced82df53504</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>PrimitiveTypeTraits&lt; Scalar, Scalar &gt;::primitiveType</type>
      <name>primitive_value_type</name>
      <anchorfile>classRTOpPack_1_1RTOpT.html</anchorfile>
      <anchor>aa0cffb4cf4d012d40665d3925fdff278</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>get_reduct_type_num_entries</name>
      <anchorfile>classRTOpPack_1_1RTOpT.html</anchorfile>
      <anchor>ab985c68fbc35b4a7adb39a09fff59570</anchor>
      <arglist>(const Ptr&lt; int &gt; &amp;num_values, const Ptr&lt; int &gt; &amp;num_indexes, const Ptr&lt; int &gt; &amp;num_chars) const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; ReductTarget &gt;</type>
      <name>reduct_obj_create</name>
      <anchorfile>classRTOpPack_1_1RTOpT.html</anchorfile>
      <anchor>a9bfbf26046dca93ff637000a7c9d846c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>reduce_reduct_objs</name>
      <anchorfile>classRTOpPack_1_1RTOpT.html</anchorfile>
      <anchor>a80c3d54d2c774358f5bb1a7bf3658c4a</anchor>
      <arglist>(const ReductTarget &amp;in_reduct_obj, const Ptr&lt; ReductTarget &gt; &amp;inout_reduct_obj) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>reduct_obj_reinit</name>
      <anchorfile>classRTOpPack_1_1RTOpT.html</anchorfile>
      <anchor>a09d5de97113b3c8c5a325adc349e06ac</anchor>
      <arglist>(const Ptr&lt; ReductTarget &gt; &amp;reduct_obj) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>extract_reduct_obj_state</name>
      <anchorfile>classRTOpPack_1_1RTOpT.html</anchorfile>
      <anchor>af24f6f19d9bd078b71f04c03a51e16e7</anchor>
      <arglist>(const ReductTarget &amp;reduct_obj, const ArrayView&lt; primitive_value_type &gt; &amp;value_data, const ArrayView&lt; index_type &gt; &amp;index_data, const ArrayView&lt; char_type &gt; &amp;char_data) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>load_reduct_obj_state</name>
      <anchorfile>classRTOpPack_1_1RTOpT.html</anchorfile>
      <anchor>ae78bbd96bebd4403d865109384940728</anchor>
      <arglist>(const ArrayView&lt; const primitive_value_type &gt; &amp;value_data, const ArrayView&lt; const index_type &gt; &amp;index_data, const ArrayView&lt; const char_type &gt; &amp;char_data, const Ptr&lt; ReductTarget &gt; &amp;reduct_obj) const </arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>op_name</name>
      <anchorfile>classRTOpPack_1_1RTOpT.html</anchorfile>
      <anchor>af3779bd071199b19ab679dd1e070efc8</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>coord_invariant</name>
      <anchorfile>classRTOpPack_1_1RTOpT.html</anchorfile>
      <anchor>ae5a5a565a5e17b3d4249ca445404e84f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Range1D</type>
      <name>range</name>
      <anchorfile>classRTOpPack_1_1RTOpT.html</anchorfile>
      <anchor>ad35f8e367f61182ba59b3bb315883b78</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>apply_op</name>
      <anchorfile>classRTOpPack_1_1RTOpT.html</anchorfile>
      <anchor>a5a1cce16e17ef311d73763f98abd064c</anchor>
      <arglist>(const ArrayView&lt; const ConstSubVectorView&lt; Scalar &gt; &gt; &amp;sub_vecs, const ArrayView&lt; const SubVectorView&lt; Scalar &gt; &gt; &amp;targ_sub_vecs, const Ptr&lt; ReductTarget &gt; &amp;reduct_obj) const </arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual void</type>
      <name>get_reduct_type_num_entries_impl</name>
      <anchorfile>classRTOpPack_1_1RTOpT.html</anchorfile>
      <anchor>a7b92d4d4046df4097648b5400aecd306</anchor>
      <arglist>(const Ptr&lt; int &gt; &amp;num_values, const Ptr&lt; int &gt; &amp;num_indexes, const Ptr&lt; int &gt; &amp;num_chars) const </arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual Teuchos::RCP&lt; ReductTarget &gt;</type>
      <name>reduct_obj_create_impl</name>
      <anchorfile>classRTOpPack_1_1RTOpT.html</anchorfile>
      <anchor>a65b4920ebc2d0c793da4c50a6c3247b0</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual void</type>
      <name>reduce_reduct_objs_impl</name>
      <anchorfile>classRTOpPack_1_1RTOpT.html</anchorfile>
      <anchor>a16ba81d49c91da64a75e2f868d610b4c</anchor>
      <arglist>(const ReductTarget &amp;in_reduct_obj, const Ptr&lt; ReductTarget &gt; &amp;inout_reduct_obj) const </arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual void</type>
      <name>reduct_obj_reinit_impl</name>
      <anchorfile>classRTOpPack_1_1RTOpT.html</anchorfile>
      <anchor>a9db4c1bf1e4dea07e19c93dff9b2e963</anchor>
      <arglist>(const Ptr&lt; ReductTarget &gt; &amp;reduct_obj) const </arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual void</type>
      <name>extract_reduct_obj_state_impl</name>
      <anchorfile>classRTOpPack_1_1RTOpT.html</anchorfile>
      <anchor>a1b7e92f5ebf895f04072289602e542f4</anchor>
      <arglist>(const ReductTarget &amp;reduct_obj, const ArrayView&lt; primitive_value_type &gt; &amp;value_data, const ArrayView&lt; index_type &gt; &amp;index_data, const ArrayView&lt; char_type &gt; &amp;char_data) const </arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual void</type>
      <name>load_reduct_obj_state_impl</name>
      <anchorfile>classRTOpPack_1_1RTOpT.html</anchorfile>
      <anchor>a99cf3acf07663142c5260db786dcb73b</anchor>
      <arglist>(const ArrayView&lt; const primitive_value_type &gt; &amp;value_data, const ArrayView&lt; const index_type &gt; &amp;index_data, const ArrayView&lt; const char_type &gt; &amp;char_data, const Ptr&lt; ReductTarget &gt; &amp;reduct_obj) const </arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual std::string</type>
      <name>op_name_impl</name>
      <anchorfile>classRTOpPack_1_1RTOpT.html</anchorfile>
      <anchor>a8e336d86078061f8e749f66481fe373d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual bool</type>
      <name>coord_invariant_impl</name>
      <anchorfile>classRTOpPack_1_1RTOpT.html</anchorfile>
      <anchor>a86c1fd01b8f945adfa5bde2a7b0082ce</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual Range1D</type>
      <name>range_impl</name>
      <anchorfile>classRTOpPack_1_1RTOpT.html</anchorfile>
      <anchor>a65f71217c16b401b58b96c66973bb04f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual void</type>
      <name>apply_op_impl</name>
      <anchorfile>classRTOpPack_1_1RTOpT.html</anchorfile>
      <anchor>abf4692253c3e51f6d6db20dc58e8374d</anchor>
      <arglist>(const ArrayView&lt; const ConstSubVectorView&lt; Scalar &gt; &gt; &amp;sub_vecs, const ArrayView&lt; const SubVectorView&lt; Scalar &gt; &gt; &amp;targ_sub_vecs, const Ptr&lt; ReductTarget &gt; &amp;reduct_obj) const  =0</arglist>
    </member>
    <member kind="function" protection="protected">
      <type></type>
      <name>RTOpT</name>
      <anchorfile>classRTOpPack_1_1RTOpT.html</anchorfile>
      <anchor>ad3a3266159efe2e18f040d30615171d6</anchor>
      <arglist>(const std::string &amp;op_name_base=&quot;&quot;)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>setOpNameBase</name>
      <anchorfile>classRTOpPack_1_1RTOpT.html</anchorfile>
      <anchor>a96a27ecd32ac62733b8e8f297e347a31</anchor>
      <arglist>(const std::string &amp;op_name_base)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>RTOpPack::ScalarIndex</name>
    <filename>structRTOpPack_1_1ScalarIndex.html</filename>
    <templarg>Scalar</templarg>
    <member kind="function">
      <type></type>
      <name>ScalarIndex</name>
      <anchorfile>structRTOpPack_1_1ScalarIndex.html</anchorfile>
      <anchor>a286ae3db8fb06a924cb0b98f4a0c4915</anchor>
      <arglist>(const Scalar &amp;_scalar, const Ordinal &amp;_index)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ScalarIndex</name>
      <anchorfile>structRTOpPack_1_1ScalarIndex.html</anchorfile>
      <anchor>a3bad74258402b560c5fa8d79255f2d0b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable">
      <type>Scalar</type>
      <name>scalar</name>
      <anchorfile>structRTOpPack_1_1ScalarIndex.html</anchorfile>
      <anchor>a487c7bf0c943fb1822e7658b6e5a45d5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>Ordinal</type>
      <name>index</name>
      <anchorfile>structRTOpPack_1_1ScalarIndex.html</anchorfile>
      <anchor>a46edfb14605a9754eab69bca9600ed04</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>std::ostream &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>structRTOpPack_1_1ScalarIndex.html</anchorfile>
      <anchor>a14132f7cdde070266d3cd599a334d58f</anchor>
      <arglist>(std::ostream &amp;out, const ScalarIndex&lt; Scalar &gt; &amp;scalarIndex)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>RTOpPack::SparseSubVectorT</name>
    <filename>classRTOpPack_1_1SparseSubVectorT.html</filename>
    <templarg>Scalar</templarg>
    <member kind="function">
      <type></type>
      <name>SparseSubVectorT</name>
      <anchorfile>classRTOpPack_1_1SparseSubVectorT.html</anchorfile>
      <anchor>ac7de671efbbe711b50580c311d9ae29b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SparseSubVectorT</name>
      <anchorfile>classRTOpPack_1_1SparseSubVectorT.html</anchorfile>
      <anchor>a4381213710f9b2405c4f927047c80e3b</anchor>
      <arglist>(Teuchos_Ordinal globalOffset_in, Teuchos_Ordinal subDim_in, Teuchos_Ordinal subNz_in, const ArrayRCP&lt; const Scalar &gt; &amp;values_in, ptrdiff_t valuesStride_in, const ArrayRCP&lt; const Teuchos_Ordinal &gt; &amp;indices_in, ptrdiff_t indicesStride_in, ptrdiff_t localOffset_in, bool isSorted_in)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SparseSubVectorT</name>
      <anchorfile>classRTOpPack_1_1SparseSubVectorT.html</anchorfile>
      <anchor>ab64585bcc998159ed9c5fefed112f5c4</anchor>
      <arglist>(Teuchos_Ordinal globalOffset_in, Teuchos_Ordinal subDim_in, const ArrayRCP&lt; const Scalar &gt; &amp;values_in, ptrdiff_t valuesStride_in)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SparseSubVectorT</name>
      <anchorfile>classRTOpPack_1_1SparseSubVectorT.html</anchorfile>
      <anchor>abb7f889649226aa98ce506572f279aba</anchor>
      <arglist>(const ConstSubVectorView&lt; Scalar &gt; &amp;sv)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initialize</name>
      <anchorfile>classRTOpPack_1_1SparseSubVectorT.html</anchorfile>
      <anchor>aea45e1017b1c3da6732e44c6b688d823</anchor>
      <arglist>(Teuchos_Ordinal globalOffset_in, Teuchos_Ordinal subDim_in, Teuchos_Ordinal subNz_in, const ArrayRCP&lt; const Scalar &gt; &amp;values_in, ptrdiff_t valuesStride_in, const ArrayRCP&lt; const Teuchos_Ordinal &gt; &amp;indices_in, ptrdiff_t indicesStride_in, ptrdiff_t localOffset_in, bool isSorted_in)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initialize</name>
      <anchorfile>classRTOpPack_1_1SparseSubVectorT.html</anchorfile>
      <anchor>a51a9c841b5d521e3f696aff4f7665aec</anchor>
      <arglist>(Teuchos_Ordinal globalOffset_in, Teuchos_Ordinal subDim_in, const ArrayRCP&lt; const Scalar &gt; &amp;values_in, ptrdiff_t valuesStride_in)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>uninitialize</name>
      <anchorfile>classRTOpPack_1_1SparseSubVectorT.html</anchorfile>
      <anchor>a51ab021f289448c4e3c4a8f182bc2b16</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setGlobalOffset</name>
      <anchorfile>classRTOpPack_1_1SparseSubVectorT.html</anchorfile>
      <anchor>af9ace86db16a01e85b1b7dde6f3b0082</anchor>
      <arglist>(Teuchos_Ordinal globalOffset_in)</arglist>
    </member>
    <member kind="function">
      <type>Teuchos_Ordinal</type>
      <name>globalOffset</name>
      <anchorfile>classRTOpPack_1_1SparseSubVectorT.html</anchorfile>
      <anchor>adff0cc5bd76532c89fb5ee4a7f110b03</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos_Ordinal</type>
      <name>subDim</name>
      <anchorfile>classRTOpPack_1_1SparseSubVectorT.html</anchorfile>
      <anchor>aa79468364d8e433315cbcc6631d0e52f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos_Ordinal</type>
      <name>subNz</name>
      <anchorfile>classRTOpPack_1_1SparseSubVectorT.html</anchorfile>
      <anchor>a9f5656be556051b984524e937bf75dd6</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const ArrayRCP&lt; const Scalar &gt;</type>
      <name>values</name>
      <anchorfile>classRTOpPack_1_1SparseSubVectorT.html</anchorfile>
      <anchor>a74edeb7b17ca781a22f0bd5f355ff227</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>ptrdiff_t</type>
      <name>valuesStride</name>
      <anchorfile>classRTOpPack_1_1SparseSubVectorT.html</anchorfile>
      <anchor>acda7607f7300a85fb486e24f250a214a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const ArrayRCP&lt; const Teuchos_Ordinal &gt;</type>
      <name>indices</name>
      <anchorfile>classRTOpPack_1_1SparseSubVectorT.html</anchorfile>
      <anchor>a622230c142d95fe0b034ed36ae6994ca</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>ptrdiff_t</type>
      <name>indicesStride</name>
      <anchorfile>classRTOpPack_1_1SparseSubVectorT.html</anchorfile>
      <anchor>a4fb2e4b2be1b40bbf042995a93cf6a0e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>ptrdiff_t</type>
      <name>localOffset</name>
      <anchorfile>classRTOpPack_1_1SparseSubVectorT.html</anchorfile>
      <anchor>af43fe9e645473324c653973f9ca8767f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isSorted</name>
      <anchorfile>classRTOpPack_1_1SparseSubVectorT.html</anchorfile>
      <anchor>a0632cc6b364a7e75beae51301cef2ef0</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="variable" protection="private">
      <type>Teuchos_Ordinal</type>
      <name>globalOffset_</name>
      <anchorfile>classRTOpPack_1_1SparseSubVectorT.html</anchorfile>
      <anchor>a8c95a752e128bf701d0623f71f0c8054</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>Teuchos_Ordinal</type>
      <name>subDim_</name>
      <anchorfile>classRTOpPack_1_1SparseSubVectorT.html</anchorfile>
      <anchor>a156029a365fb079e31753f164cdb3fd0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>Teuchos_Ordinal</type>
      <name>subNz_</name>
      <anchorfile>classRTOpPack_1_1SparseSubVectorT.html</anchorfile>
      <anchor>a7fd981b978131b1cde94411076fa754e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>ArrayRCP&lt; const Scalar &gt;</type>
      <name>values_</name>
      <anchorfile>classRTOpPack_1_1SparseSubVectorT.html</anchorfile>
      <anchor>a4649e600b4a4c2271e7f0f464eae90bb</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>ptrdiff_t</type>
      <name>valuesStride_</name>
      <anchorfile>classRTOpPack_1_1SparseSubVectorT.html</anchorfile>
      <anchor>a5543246671131297171de8be08edf828</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>ArrayRCP&lt; const Teuchos_Ordinal &gt;</type>
      <name>indices_</name>
      <anchorfile>classRTOpPack_1_1SparseSubVectorT.html</anchorfile>
      <anchor>a6cff7fda51d0c36c1cb43a6e3bde6211</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>ptrdiff_t</type>
      <name>indicesStride_</name>
      <anchorfile>classRTOpPack_1_1SparseSubVectorT.html</anchorfile>
      <anchor>a1fb8355472baf0522b41a99547c39cb3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>ptrdiff_t</type>
      <name>localOffset_</name>
      <anchorfile>classRTOpPack_1_1SparseSubVectorT.html</anchorfile>
      <anchor>afaa7f8145b2e8dd6c9e8b6e334520ac2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>bool</type>
      <name>isSorted_</name>
      <anchorfile>classRTOpPack_1_1SparseSubVectorT.html</anchorfile>
      <anchor>aa4bff394edd00184d57cbc5cc4af5b26</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>RTOpPack::SubMultiVectorView</name>
    <filename>classRTOpPack_1_1SubMultiVectorView.html</filename>
    <templarg>Scalar</templarg>
    <base>RTOpPack::ConstSubMultiVectorView</base>
    <member kind="function">
      <type></type>
      <name>SubMultiVectorView</name>
      <anchorfile>classRTOpPack_1_1SubMultiVectorView.html</anchorfile>
      <anchor>a22dfdf0f6e099da98d5fa3f3159a24b9</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SubMultiVectorView</name>
      <anchorfile>classRTOpPack_1_1SubMultiVectorView.html</anchorfile>
      <anchor>a3427bf66a8d069d688f2a74146836eaf</anchor>
      <arglist>(Ordinal numRows_in, Ordinal numCols_in)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SubMultiVectorView</name>
      <anchorfile>classRTOpPack_1_1SubMultiVectorView.html</anchorfile>
      <anchor>ad84be966f3ceb4569898f32bdb3d8276</anchor>
      <arglist>(Ordinal globalOffset_in, Ordinal subDim_in, Ordinal colOffset_in, Ordinal numSubCols_in, const ArrayRCP&lt; Scalar &gt; &amp;values_in, Ordinal leadingDim_in)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SubMultiVectorView</name>
      <anchorfile>classRTOpPack_1_1SubMultiVectorView.html</anchorfile>
      <anchor>a04966632e72a50c29e44e2e828505e36</anchor>
      <arglist>(const SubMultiVectorView&lt; Scalar &gt; &amp;smv)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initialize</name>
      <anchorfile>classRTOpPack_1_1SubMultiVectorView.html</anchorfile>
      <anchor>a48204adbd4d7e30fa1d10fbb34536a2c</anchor>
      <arglist>(Ordinal globalOffset_in, Ordinal subDim_in, Ordinal colOffset_in, Ordinal numSubCols_in, const ArrayRCP&lt; Scalar &gt; &amp;values_in, Ordinal leadingDim_in)</arglist>
    </member>
    <member kind="function">
      <type>const ArrayRCP&lt; Scalar &gt;</type>
      <name>values</name>
      <anchorfile>classRTOpPack_1_1SubMultiVectorView.html</anchorfile>
      <anchor>a9d2b6b8517cc0dfe7cefb00a522dc4fb</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Scalar &amp;</type>
      <name>operator()</name>
      <anchorfile>classRTOpPack_1_1SubMultiVectorView.html</anchorfile>
      <anchor>a21746db5801068e261eb1759290746d3</anchor>
      <arglist>(Ordinal i, Ordinal j) const </arglist>
    </member>
    <member kind="function">
      <type>SubVectorView&lt; Scalar &gt;</type>
      <name>col</name>
      <anchorfile>classRTOpPack_1_1SubMultiVectorView.html</anchorfile>
      <anchor>a952ac097f9e010e0bd28280fc35c7ba4</anchor>
      <arglist>(const Ordinal j) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>RTOpPack::SubVectorView</name>
    <filename>classRTOpPack_1_1SubVectorView.html</filename>
    <templarg>Scalar</templarg>
    <base>RTOpPack::ConstSubVectorView</base>
    <member kind="function">
      <type></type>
      <name>SubVectorView</name>
      <anchorfile>classRTOpPack_1_1SubVectorView.html</anchorfile>
      <anchor>ad0c456b9ceca7298e4a9b8413ee54f86</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SubVectorView</name>
      <anchorfile>classRTOpPack_1_1SubVectorView.html</anchorfile>
      <anchor>a5f719bef1ab26110e0f4db3d313fe074</anchor>
      <arglist>(const ArrayRCP&lt; Scalar &gt; &amp;values_in)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SubVectorView</name>
      <anchorfile>classRTOpPack_1_1SubVectorView.html</anchorfile>
      <anchor>ada76e3541ef7e597288cb3b7546d087b</anchor>
      <arglist>(Ordinal globalOffset_in, Ordinal subDim_in, const ArrayRCP&lt; Scalar &gt; &amp;values_in, ptrdiff_t stride_in)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SubVectorView</name>
      <anchorfile>classRTOpPack_1_1SubVectorView.html</anchorfile>
      <anchor>a0d7210739293d45a41d1d2aa6bc48cad</anchor>
      <arglist>(Ordinal subDim_in)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SubVectorView</name>
      <anchorfile>classRTOpPack_1_1SubVectorView.html</anchorfile>
      <anchor>a5a5fdff71b140093d17ab6317f1e52cd</anchor>
      <arglist>(const SubVectorView&lt; Scalar &gt; &amp;sv)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initialize</name>
      <anchorfile>classRTOpPack_1_1SubVectorView.html</anchorfile>
      <anchor>a0e6209fdd6453d7b7548316ab8552ae2</anchor>
      <arglist>(Ordinal globalOffset_in, Ordinal subDim_in, const ArrayRCP&lt; Scalar &gt; &amp;values_in, ptrdiff_t stride_in)</arglist>
    </member>
    <member kind="function">
      <type>const ArrayRCP&lt; Scalar &gt;</type>
      <name>values</name>
      <anchorfile>classRTOpPack_1_1SubVectorView.html</anchorfile>
      <anchor>a69e00a9296312e834ab8b678dc145fb2</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Scalar &amp;</type>
      <name>operator[]</name>
      <anchorfile>classRTOpPack_1_1SubVectorView.html</anchorfile>
      <anchor>a8ad5713cc67af2b3d4c36966dff72ebe</anchor>
      <arglist>(Ordinal i) const </arglist>
    </member>
    <member kind="function">
      <type>Scalar &amp;</type>
      <name>operator()</name>
      <anchorfile>classRTOpPack_1_1SubVectorView.html</anchorfile>
      <anchor>ae40d52d401c637af309cdf38035f3cf6</anchor>
      <arglist>(Ordinal i) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>RTOpPack::SumScalarReductObjReduction</name>
    <filename>classRTOpPack_1_1SumScalarReductObjReduction.html</filename>
    <templarg></templarg>
    <member kind="function">
      <type>void</type>
      <name>operator()</name>
      <anchorfile>classRTOpPack_1_1SumScalarReductObjReduction.html</anchorfile>
      <anchor>a475941957c40ce34d6fcfaa253e71879</anchor>
      <arglist>(const Scalar &amp;in_reduct, Scalar &amp;inout_reduct) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>RTOpPack::TOp_0_1_Base</name>
    <filename>classRTOpPack_1_1TOp__0__1__Base.html</filename>
    <templarg>Scalar</templarg>
    <templarg>EleWiseTransformation</templarg>
    <base>RTOpPack::RTOpT</base>
    <member kind="function">
      <type></type>
      <name>TOp_0_1_Base</name>
      <anchorfile>classRTOpPack_1_1TOp__0__1__Base.html</anchorfile>
      <anchor>af3cc532735a0ca6a0689932b8f32ad0d</anchor>
      <arglist>(EleWiseTransformation eleWiseTransformation=EleWiseTransformation())</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>EleWiseTransformation</type>
      <name>eleWiseTransformation_</name>
      <anchorfile>classRTOpPack_1_1TOp__0__1__Base.html</anchorfile>
      <anchor>ae7711671c31d4b46d88ac9bf27022734</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>apply_op_impl</name>
      <anchorfile>classRTOpPack_1_1TOp__0__1__Base.html</anchorfile>
      <anchor>a40e2210b4f2388a6b59f522e12106072</anchor>
      <arglist>(const ArrayView&lt; const ConstSubVectorView&lt; Scalar &gt; &gt; &amp;sub_vecs, const ArrayView&lt; const SubVectorView&lt; Scalar &gt; &gt; &amp;targ_sub_vecs, const Ptr&lt; ReductTarget &gt; &amp;reduct_obj_inout) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>TOp_0_1_Base&lt; Scalar, TOpAddScalarEleWiseTransformation&lt; Scalar &gt; &gt;</name>
    <filename>classRTOpPack_1_1TOp__0__1__Base.html</filename>
    <base>RTOpPack::RTOpT</base>
    <member kind="function">
      <type></type>
      <name>TOp_0_1_Base</name>
      <anchorfile>classRTOpPack_1_1TOp__0__1__Base.html</anchorfile>
      <anchor>af3cc532735a0ca6a0689932b8f32ad0d</anchor>
      <arglist>(TOpAddScalarEleWiseTransformation&lt; Scalar &gt; eleWiseTransformation=TOpAddScalarEleWiseTransformation&lt; Scalar &gt;())</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>TOpAddScalarEleWiseTransformation&lt; Scalar &gt;</type>
      <name>eleWiseTransformation_</name>
      <anchorfile>classRTOpPack_1_1TOp__0__1__Base.html</anchorfile>
      <anchor>ae7711671c31d4b46d88ac9bf27022734</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>apply_op_impl</name>
      <anchorfile>classRTOpPack_1_1TOp__0__1__Base.html</anchorfile>
      <anchor>a40e2210b4f2388a6b59f522e12106072</anchor>
      <arglist>(const ArrayView&lt; const ConstSubVectorView&lt; Scalar &gt; &gt; &amp;sub_vecs, const ArrayView&lt; const SubVectorView&lt; Scalar &gt; &gt; &amp;targ_sub_vecs, const Ptr&lt; ReductTarget &gt; &amp;reduct_obj_inout) const</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>TOp_0_1_Base&lt; Scalar, TOpAssignScalarEleWiseTransformation&lt; Scalar &gt; &gt;</name>
    <filename>classRTOpPack_1_1TOp__0__1__Base.html</filename>
    <base>RTOpPack::RTOpT</base>
    <member kind="function">
      <type></type>
      <name>TOp_0_1_Base</name>
      <anchorfile>classRTOpPack_1_1TOp__0__1__Base.html</anchorfile>
      <anchor>af3cc532735a0ca6a0689932b8f32ad0d</anchor>
      <arglist>(TOpAssignScalarEleWiseTransformation&lt; Scalar &gt; eleWiseTransformation=TOpAssignScalarEleWiseTransformation&lt; Scalar &gt;())</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>TOpAssignScalarEleWiseTransformation&lt; Scalar &gt;</type>
      <name>eleWiseTransformation_</name>
      <anchorfile>classRTOpPack_1_1TOp__0__1__Base.html</anchorfile>
      <anchor>ae7711671c31d4b46d88ac9bf27022734</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>apply_op_impl</name>
      <anchorfile>classRTOpPack_1_1TOp__0__1__Base.html</anchorfile>
      <anchor>a40e2210b4f2388a6b59f522e12106072</anchor>
      <arglist>(const ArrayView&lt; const ConstSubVectorView&lt; Scalar &gt; &gt; &amp;sub_vecs, const ArrayView&lt; const SubVectorView&lt; Scalar &gt; &gt; &amp;targ_sub_vecs, const Ptr&lt; ReductTarget &gt; &amp;reduct_obj_inout) const</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>TOp_0_1_Base&lt; Scalar, TOpScaleVectorEleWiseTransformation&lt; Scalar &gt; &gt;</name>
    <filename>classRTOpPack_1_1TOp__0__1__Base.html</filename>
    <base>RTOpPack::RTOpT</base>
    <member kind="function">
      <type></type>
      <name>TOp_0_1_Base</name>
      <anchorfile>classRTOpPack_1_1TOp__0__1__Base.html</anchorfile>
      <anchor>af3cc532735a0ca6a0689932b8f32ad0d</anchor>
      <arglist>(TOpScaleVectorEleWiseTransformation&lt; Scalar &gt; eleWiseTransformation=TOpScaleVectorEleWiseTransformation&lt; Scalar &gt;())</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>TOpScaleVectorEleWiseTransformation&lt; Scalar &gt;</type>
      <name>eleWiseTransformation_</name>
      <anchorfile>classRTOpPack_1_1TOp__0__1__Base.html</anchorfile>
      <anchor>ae7711671c31d4b46d88ac9bf27022734</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>apply_op_impl</name>
      <anchorfile>classRTOpPack_1_1TOp__0__1__Base.html</anchorfile>
      <anchor>a40e2210b4f2388a6b59f522e12106072</anchor>
      <arglist>(const ArrayView&lt; const ConstSubVectorView&lt; Scalar &gt; &gt; &amp;sub_vecs, const ArrayView&lt; const SubVectorView&lt; Scalar &gt; &gt; &amp;targ_sub_vecs, const Ptr&lt; ReductTarget &gt; &amp;reduct_obj_inout) const</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>RTOpPack::TOp_0_1_CoordVariantBase</name>
    <filename>classRTOpPack_1_1TOp__0__1__CoordVariantBase.html</filename>
    <templarg>Scalar</templarg>
    <templarg>EleWiseTransformation</templarg>
    <base>RTOpPack::RTOpT</base>
    <member kind="function">
      <type></type>
      <name>TOp_0_1_CoordVariantBase</name>
      <anchorfile>classRTOpPack_1_1TOp__0__1__CoordVariantBase.html</anchorfile>
      <anchor>a084ef6aafa38777f605e2b0745823f4c</anchor>
      <arglist>(EleWiseTransformation eleWiseTransformation=EleWiseTransformation())</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setEleWiseTransformation</name>
      <anchorfile>classRTOpPack_1_1TOp__0__1__CoordVariantBase.html</anchorfile>
      <anchor>a2055d3ada1510f2e4fefe8900afa11df</anchor>
      <arglist>(EleWiseTransformation eleWiseTransformation)</arglist>
    </member>
    <member kind="function">
      <type>const EleWiseTransformation &amp;</type>
      <name>getEleWiseTransformation</name>
      <anchorfile>classRTOpPack_1_1TOp__0__1__CoordVariantBase.html</anchorfile>
      <anchor>af005d743a122a69b18475ab597deef02</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="variable" protection="private">
      <type>EleWiseTransformation</type>
      <name>eleWiseTransformation_</name>
      <anchorfile>classRTOpPack_1_1TOp__0__1__CoordVariantBase.html</anchorfile>
      <anchor>a92dad8896831c7a859c5f2167576a619</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>coord_invariant_impl</name>
      <anchorfile>classRTOpPack_1_1TOp__0__1__CoordVariantBase.html</anchorfile>
      <anchor>ae3907fdf2e1481c66fb8ee370b5519f4</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>apply_op_impl</name>
      <anchorfile>classRTOpPack_1_1TOp__0__1__CoordVariantBase.html</anchorfile>
      <anchor>ae6313bf6f3c36074d629c40e7e4f1f9a</anchor>
      <arglist>(const ArrayView&lt; const ConstSubVectorView&lt; Scalar &gt; &gt; &amp;sub_vecs, const ArrayView&lt; const SubVectorView&lt; Scalar &gt; &gt; &amp;targ_sub_vecs, const Ptr&lt; ReductTarget &gt; &amp;reduct_obj_inout) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>TOp_0_1_CoordVariantBase&lt; Scalar, TOpSetAssendingValuesEleWiseTransformation&lt; Scalar &gt; &gt;</name>
    <filename>classRTOpPack_1_1TOp__0__1__CoordVariantBase.html</filename>
    <base>RTOpPack::RTOpT</base>
    <member kind="function">
      <type></type>
      <name>TOp_0_1_CoordVariantBase</name>
      <anchorfile>classRTOpPack_1_1TOp__0__1__CoordVariantBase.html</anchorfile>
      <anchor>a084ef6aafa38777f605e2b0745823f4c</anchor>
      <arglist>(TOpSetAssendingValuesEleWiseTransformation&lt; Scalar &gt; eleWiseTransformation=TOpSetAssendingValuesEleWiseTransformation&lt; Scalar &gt;())</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setEleWiseTransformation</name>
      <anchorfile>classRTOpPack_1_1TOp__0__1__CoordVariantBase.html</anchorfile>
      <anchor>a2055d3ada1510f2e4fefe8900afa11df</anchor>
      <arglist>(TOpSetAssendingValuesEleWiseTransformation&lt; Scalar &gt; eleWiseTransformation)</arglist>
    </member>
    <member kind="function">
      <type>const TOpSetAssendingValuesEleWiseTransformation&lt; Scalar &gt; &amp;</type>
      <name>getEleWiseTransformation</name>
      <anchorfile>classRTOpPack_1_1TOp__0__1__CoordVariantBase.html</anchorfile>
      <anchor>af005d743a122a69b18475ab597deef02</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>TOpSetAssendingValuesEleWiseTransformation&lt; Scalar &gt;</type>
      <name>eleWiseTransformation_</name>
      <anchorfile>classRTOpPack_1_1TOp__0__1__CoordVariantBase.html</anchorfile>
      <anchor>a92dad8896831c7a859c5f2167576a619</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>coord_invariant_impl</name>
      <anchorfile>classRTOpPack_1_1TOp__0__1__CoordVariantBase.html</anchorfile>
      <anchor>ae3907fdf2e1481c66fb8ee370b5519f4</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>apply_op_impl</name>
      <anchorfile>classRTOpPack_1_1TOp__0__1__CoordVariantBase.html</anchorfile>
      <anchor>ae6313bf6f3c36074d629c40e7e4f1f9a</anchor>
      <arglist>(const ArrayView&lt; const ConstSubVectorView&lt; Scalar &gt; &gt; &amp;sub_vecs, const ArrayView&lt; const SubVectorView&lt; Scalar &gt; &gt; &amp;targ_sub_vecs, const Ptr&lt; ReductTarget &gt; &amp;reduct_obj_inout) const</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>TOp_0_1_CoordVariantBase&lt; Scalar, TOpSetElementEleWiseTransformation&lt; Scalar &gt; &gt;</name>
    <filename>classRTOpPack_1_1TOp__0__1__CoordVariantBase.html</filename>
    <base>RTOpPack::RTOpT</base>
    <member kind="function">
      <type></type>
      <name>TOp_0_1_CoordVariantBase</name>
      <anchorfile>classRTOpPack_1_1TOp__0__1__CoordVariantBase.html</anchorfile>
      <anchor>a084ef6aafa38777f605e2b0745823f4c</anchor>
      <arglist>(TOpSetElementEleWiseTransformation&lt; Scalar &gt; eleWiseTransformation=TOpSetElementEleWiseTransformation&lt; Scalar &gt;())</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setEleWiseTransformation</name>
      <anchorfile>classRTOpPack_1_1TOp__0__1__CoordVariantBase.html</anchorfile>
      <anchor>a2055d3ada1510f2e4fefe8900afa11df</anchor>
      <arglist>(TOpSetElementEleWiseTransformation&lt; Scalar &gt; eleWiseTransformation)</arglist>
    </member>
    <member kind="function">
      <type>const TOpSetElementEleWiseTransformation&lt; Scalar &gt; &amp;</type>
      <name>getEleWiseTransformation</name>
      <anchorfile>classRTOpPack_1_1TOp__0__1__CoordVariantBase.html</anchorfile>
      <anchor>af005d743a122a69b18475ab597deef02</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>TOpSetElementEleWiseTransformation&lt; Scalar &gt;</type>
      <name>eleWiseTransformation_</name>
      <anchorfile>classRTOpPack_1_1TOp__0__1__CoordVariantBase.html</anchorfile>
      <anchor>a92dad8896831c7a859c5f2167576a619</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>coord_invariant_impl</name>
      <anchorfile>classRTOpPack_1_1TOp__0__1__CoordVariantBase.html</anchorfile>
      <anchor>ae3907fdf2e1481c66fb8ee370b5519f4</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>apply_op_impl</name>
      <anchorfile>classRTOpPack_1_1TOp__0__1__CoordVariantBase.html</anchorfile>
      <anchor>ae6313bf6f3c36074d629c40e7e4f1f9a</anchor>
      <arglist>(const ArrayView&lt; const ConstSubVectorView&lt; Scalar &gt; &gt; &amp;sub_vecs, const ArrayView&lt; const SubVectorView&lt; Scalar &gt; &gt; &amp;targ_sub_vecs, const Ptr&lt; ReductTarget &gt; &amp;reduct_obj_inout) const</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>RTOpPack::TOp_1_1_Base</name>
    <filename>classRTOpPack_1_1TOp__1__1__Base.html</filename>
    <templarg>Scalar</templarg>
    <templarg>EleWiseTransformation</templarg>
    <base>RTOpPack::RTOpT</base>
    <member kind="function">
      <type></type>
      <name>TOp_1_1_Base</name>
      <anchorfile>classRTOpPack_1_1TOp__1__1__Base.html</anchorfile>
      <anchor>aa79c44874cddc34708fd23c6fbd054bd</anchor>
      <arglist>(EleWiseTransformation eleWiseTransformation=EleWiseTransformation())</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>EleWiseTransformation</type>
      <name>eleWiseTransformation_</name>
      <anchorfile>classRTOpPack_1_1TOp__1__1__Base.html</anchorfile>
      <anchor>a74a3408366cdea8d52cc20ae70bf6b37</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>apply_op_impl</name>
      <anchorfile>classRTOpPack_1_1TOp__1__1__Base.html</anchorfile>
      <anchor>a85adb95c6c037f9637f5efb85eb8ff37</anchor>
      <arglist>(const ArrayView&lt; const ConstSubVectorView&lt; Scalar &gt; &gt; &amp;sub_vecs, const ArrayView&lt; const SubVectorView&lt; Scalar &gt; &gt; &amp;targ_sub_vecs, const Ptr&lt; ReductTarget &gt; &amp;reduct_obj_inout) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>TOp_1_1_Base&lt; Scalar, TOpAXPYEleWiseTransformation&lt; Scalar &gt; &gt;</name>
    <filename>classRTOpPack_1_1TOp__1__1__Base.html</filename>
    <base>RTOpPack::RTOpT</base>
    <member kind="function">
      <type></type>
      <name>TOp_1_1_Base</name>
      <anchorfile>classRTOpPack_1_1TOp__1__1__Base.html</anchorfile>
      <anchor>aa79c44874cddc34708fd23c6fbd054bd</anchor>
      <arglist>(TOpAXPYEleWiseTransformation&lt; Scalar &gt; eleWiseTransformation=TOpAXPYEleWiseTransformation&lt; Scalar &gt;())</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>TOpAXPYEleWiseTransformation&lt; Scalar &gt;</type>
      <name>eleWiseTransformation_</name>
      <anchorfile>classRTOpPack_1_1TOp__1__1__Base.html</anchorfile>
      <anchor>a74a3408366cdea8d52cc20ae70bf6b37</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>apply_op_impl</name>
      <anchorfile>classRTOpPack_1_1TOp__1__1__Base.html</anchorfile>
      <anchor>a85adb95c6c037f9637f5efb85eb8ff37</anchor>
      <arglist>(const ArrayView&lt; const ConstSubVectorView&lt; Scalar &gt; &gt; &amp;sub_vecs, const ArrayView&lt; const SubVectorView&lt; Scalar &gt; &gt; &amp;targ_sub_vecs, const Ptr&lt; ReductTarget &gt; &amp;reduct_obj_inout) const</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>TOp_1_1_Base&lt; Scalar, TOpEleWiseProdUpdateEleWiseTransformation&lt; Scalar &gt; &gt;</name>
    <filename>classRTOpPack_1_1TOp__1__1__Base.html</filename>
    <base>RTOpPack::RTOpT</base>
    <member kind="function">
      <type></type>
      <name>TOp_1_1_Base</name>
      <anchorfile>classRTOpPack_1_1TOp__1__1__Base.html</anchorfile>
      <anchor>aa79c44874cddc34708fd23c6fbd054bd</anchor>
      <arglist>(TOpEleWiseProdUpdateEleWiseTransformation&lt; Scalar &gt; eleWiseTransformation=TOpEleWiseProdUpdateEleWiseTransformation&lt; Scalar &gt;())</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>TOpEleWiseProdUpdateEleWiseTransformation&lt; Scalar &gt;</type>
      <name>eleWiseTransformation_</name>
      <anchorfile>classRTOpPack_1_1TOp__1__1__Base.html</anchorfile>
      <anchor>a74a3408366cdea8d52cc20ae70bf6b37</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>apply_op_impl</name>
      <anchorfile>classRTOpPack_1_1TOp__1__1__Base.html</anchorfile>
      <anchor>a85adb95c6c037f9637f5efb85eb8ff37</anchor>
      <arglist>(const ArrayView&lt; const ConstSubVectorView&lt; Scalar &gt; &gt; &amp;sub_vecs, const ArrayView&lt; const SubVectorView&lt; Scalar &gt; &gt; &amp;targ_sub_vecs, const Ptr&lt; ReductTarget &gt; &amp;reduct_obj_inout) const</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>TOp_1_1_Base&lt; Scalar, TOpEleWiseScaleEleWiseTransformation&lt; Scalar &gt; &gt;</name>
    <filename>classRTOpPack_1_1TOp__1__1__Base.html</filename>
    <base>RTOpPack::RTOpT</base>
    <member kind="function">
      <type></type>
      <name>TOp_1_1_Base</name>
      <anchorfile>classRTOpPack_1_1TOp__1__1__Base.html</anchorfile>
      <anchor>aa79c44874cddc34708fd23c6fbd054bd</anchor>
      <arglist>(TOpEleWiseScaleEleWiseTransformation&lt; Scalar &gt; eleWiseTransformation=TOpEleWiseScaleEleWiseTransformation&lt; Scalar &gt;())</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>TOpEleWiseScaleEleWiseTransformation&lt; Scalar &gt;</type>
      <name>eleWiseTransformation_</name>
      <anchorfile>classRTOpPack_1_1TOp__1__1__Base.html</anchorfile>
      <anchor>a74a3408366cdea8d52cc20ae70bf6b37</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>apply_op_impl</name>
      <anchorfile>classRTOpPack_1_1TOp__1__1__Base.html</anchorfile>
      <anchor>a85adb95c6c037f9637f5efb85eb8ff37</anchor>
      <arglist>(const ArrayView&lt; const ConstSubVectorView&lt; Scalar &gt; &gt; &amp;sub_vecs, const ArrayView&lt; const SubVectorView&lt; Scalar &gt; &gt; &amp;targ_sub_vecs, const Ptr&lt; ReductTarget &gt; &amp;reduct_obj_inout) const</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>RTOpPack::TOp_2_1_Base</name>
    <filename>classRTOpPack_1_1TOp__2__1__Base.html</filename>
    <templarg>Scalar</templarg>
    <templarg>EleWiseTransformation</templarg>
    <base>RTOpPack::RTOpT</base>
    <member kind="function">
      <type></type>
      <name>TOp_2_1_Base</name>
      <anchorfile>classRTOpPack_1_1TOp__2__1__Base.html</anchorfile>
      <anchor>a5b993fcee3e81003b756faa9fea1e4ce</anchor>
      <arglist>(EleWiseTransformation eleWiseTransformation=EleWiseTransformation())</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>EleWiseTransformation</type>
      <name>eleWiseTransformation_</name>
      <anchorfile>classRTOpPack_1_1TOp__2__1__Base.html</anchorfile>
      <anchor>ad75a561442b131c15d12a9c302590ef4</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>apply_op_impl</name>
      <anchorfile>classRTOpPack_1_1TOp__2__1__Base.html</anchorfile>
      <anchor>aa3795b2a94ef8c4a2468d30913b2f111</anchor>
      <arglist>(const ArrayView&lt; const ConstSubVectorView&lt; Scalar &gt; &gt; &amp;sub_vecs, const ArrayView&lt; const SubVectorView&lt; Scalar &gt; &gt; &amp;targ_sub_vecs, const Ptr&lt; ReductTarget &gt; &amp;reduct_obj_inout) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>TOp_2_1_Base&lt; Scalar, TOpEleWiseConjProdEleWiseTransformation&lt; Scalar &gt; &gt;</name>
    <filename>classRTOpPack_1_1TOp__2__1__Base.html</filename>
    <base>RTOpPack::RTOpT</base>
    <member kind="function">
      <type></type>
      <name>TOp_2_1_Base</name>
      <anchorfile>classRTOpPack_1_1TOp__2__1__Base.html</anchorfile>
      <anchor>a5b993fcee3e81003b756faa9fea1e4ce</anchor>
      <arglist>(TOpEleWiseConjProdEleWiseTransformation&lt; Scalar &gt; eleWiseTransformation=TOpEleWiseConjProdEleWiseTransformation&lt; Scalar &gt;())</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>TOpEleWiseConjProdEleWiseTransformation&lt; Scalar &gt;</type>
      <name>eleWiseTransformation_</name>
      <anchorfile>classRTOpPack_1_1TOp__2__1__Base.html</anchorfile>
      <anchor>ad75a561442b131c15d12a9c302590ef4</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>apply_op_impl</name>
      <anchorfile>classRTOpPack_1_1TOp__2__1__Base.html</anchorfile>
      <anchor>aa3795b2a94ef8c4a2468d30913b2f111</anchor>
      <arglist>(const ArrayView&lt; const ConstSubVectorView&lt; Scalar &gt; &gt; &amp;sub_vecs, const ArrayView&lt; const SubVectorView&lt; Scalar &gt; &gt; &amp;targ_sub_vecs, const Ptr&lt; ReductTarget &gt; &amp;reduct_obj_inout) const</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>TOp_2_1_Base&lt; Scalar, TOpEleWiseDivideEleWiseTransformation&lt; Scalar &gt; &gt;</name>
    <filename>classRTOpPack_1_1TOp__2__1__Base.html</filename>
    <base>RTOpPack::RTOpT</base>
    <member kind="function">
      <type></type>
      <name>TOp_2_1_Base</name>
      <anchorfile>classRTOpPack_1_1TOp__2__1__Base.html</anchorfile>
      <anchor>a5b993fcee3e81003b756faa9fea1e4ce</anchor>
      <arglist>(TOpEleWiseDivideEleWiseTransformation&lt; Scalar &gt; eleWiseTransformation=TOpEleWiseDivideEleWiseTransformation&lt; Scalar &gt;())</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>TOpEleWiseDivideEleWiseTransformation&lt; Scalar &gt;</type>
      <name>eleWiseTransformation_</name>
      <anchorfile>classRTOpPack_1_1TOp__2__1__Base.html</anchorfile>
      <anchor>ad75a561442b131c15d12a9c302590ef4</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>apply_op_impl</name>
      <anchorfile>classRTOpPack_1_1TOp__2__1__Base.html</anchorfile>
      <anchor>aa3795b2a94ef8c4a2468d30913b2f111</anchor>
      <arglist>(const ArrayView&lt; const ConstSubVectorView&lt; Scalar &gt; &gt; &amp;sub_vecs, const ArrayView&lt; const SubVectorView&lt; Scalar &gt; &gt; &amp;targ_sub_vecs, const Ptr&lt; ReductTarget &gt; &amp;reduct_obj_inout) const</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>TOp_2_1_Base&lt; Scalar, TOpEleWiseProdEleWiseTransformation&lt; Scalar &gt; &gt;</name>
    <filename>classRTOpPack_1_1TOp__2__1__Base.html</filename>
    <base>RTOpPack::RTOpT</base>
    <member kind="function">
      <type></type>
      <name>TOp_2_1_Base</name>
      <anchorfile>classRTOpPack_1_1TOp__2__1__Base.html</anchorfile>
      <anchor>a5b993fcee3e81003b756faa9fea1e4ce</anchor>
      <arglist>(TOpEleWiseProdEleWiseTransformation&lt; Scalar &gt; eleWiseTransformation=TOpEleWiseProdEleWiseTransformation&lt; Scalar &gt;())</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>TOpEleWiseProdEleWiseTransformation&lt; Scalar &gt;</type>
      <name>eleWiseTransformation_</name>
      <anchorfile>classRTOpPack_1_1TOp__2__1__Base.html</anchorfile>
      <anchor>ad75a561442b131c15d12a9c302590ef4</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>apply_op_impl</name>
      <anchorfile>classRTOpPack_1_1TOp__2__1__Base.html</anchorfile>
      <anchor>aa3795b2a94ef8c4a2468d30913b2f111</anchor>
      <arglist>(const ArrayView&lt; const ConstSubVectorView&lt; Scalar &gt; &gt; &amp;sub_vecs, const ArrayView&lt; const SubVectorView&lt; Scalar &gt; &gt; &amp;targ_sub_vecs, const Ptr&lt; ReductTarget &gt; &amp;reduct_obj_inout) const</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>RTOpPack::TOp_3_1_Base</name>
    <filename>classRTOpPack_1_1TOp__3__1__Base.html</filename>
    <templarg></templarg>
    <templarg></templarg>
    <base>RTOpPack::RTOpT</base>
    <member kind="function">
      <type></type>
      <name>TOp_3_1_Base</name>
      <anchorfile>classRTOpPack_1_1TOp__3__1__Base.html</anchorfile>
      <anchor>adcb794941b816f67ff638c7400de62dc</anchor>
      <arglist>(EleWiseTransformation eleWiseTransformation=EleWiseTransformation())</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>EleWiseTransformation</type>
      <name>eleWiseTransformation_</name>
      <anchorfile>classRTOpPack_1_1TOp__3__1__Base.html</anchorfile>
      <anchor>a586d147d06857babec678d6d20a19df3</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>apply_op_impl</name>
      <anchorfile>classRTOpPack_1_1TOp__3__1__Base.html</anchorfile>
      <anchor>ab4882630a77c058d6ab112487893a48e</anchor>
      <arglist>(const ArrayView&lt; const ConstSubVectorView&lt; Scalar &gt; &gt; &amp;sub_vecs, const ArrayView&lt; const SubVectorView&lt; Scalar &gt; &gt; &amp;targ_sub_vecs, const Ptr&lt; ReductTarget &gt; &amp;reduct_obj_inout) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>RTOpPack::TOpAddScalar</name>
    <filename>classRTOpPack_1_1TOpAddScalar.html</filename>
    <templarg></templarg>
    <base>TOp_0_1_Base&lt; Scalar, TOpAddScalarEleWiseTransformation&lt; Scalar &gt; &gt;</base>
    <member kind="typedef">
      <type>TOp_0_1_Base&lt; Scalar, TOpAddScalarEleWiseTransformation&lt; Scalar &gt; &gt;</type>
      <name>base_t</name>
      <anchorfile>classRTOpPack_1_1TOpAddScalar.html</anchorfile>
      <anchor>a2f6ca22f7c6a167ecfec4d516bc553d0</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>TOpAddScalar</name>
      <anchorfile>classRTOpPack_1_1TOpAddScalar.html</anchorfile>
      <anchor>ada38754bf5f4e8559ceefce2dd90ddac</anchor>
      <arglist>(const Scalar &amp;alpha)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>RTOpPack::TOpAddScalarEleWiseTransformation</name>
    <filename>classRTOpPack_1_1TOpAddScalarEleWiseTransformation.html</filename>
    <templarg></templarg>
    <member kind="function">
      <type></type>
      <name>TOpAddScalarEleWiseTransformation</name>
      <anchorfile>classRTOpPack_1_1TOpAddScalarEleWiseTransformation.html</anchorfile>
      <anchor>ace868a08104354107ccb5a6501678dfc</anchor>
      <arglist>(const Scalar &amp;alpha)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>operator()</name>
      <anchorfile>classRTOpPack_1_1TOpAddScalarEleWiseTransformation.html</anchorfile>
      <anchor>a5bd56b0cb31035c38feef605c263fa74</anchor>
      <arglist>(Scalar &amp;z0) const </arglist>
    </member>
    <member kind="variable" protection="private">
      <type>Scalar</type>
      <name>alpha_</name>
      <anchorfile>classRTOpPack_1_1TOpAddScalarEleWiseTransformation.html</anchorfile>
      <anchor>a83e81faf9677a2364dfc8ca11efecc6b</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>RTOpPack::TOpAssignScalar</name>
    <filename>classRTOpPack_1_1TOpAssignScalar.html</filename>
    <templarg></templarg>
    <base>TOp_0_1_Base&lt; Scalar, TOpAssignScalarEleWiseTransformation&lt; Scalar &gt; &gt;</base>
    <member kind="typedef">
      <type>TOp_0_1_Base&lt; Scalar, TOpAssignScalarEleWiseTransformation&lt; Scalar &gt; &gt;</type>
      <name>base_t</name>
      <anchorfile>classRTOpPack_1_1TOpAssignScalar.html</anchorfile>
      <anchor>a0abbd2e992922a93a73babdca67dc00e</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>TOpAssignScalar</name>
      <anchorfile>classRTOpPack_1_1TOpAssignScalar.html</anchorfile>
      <anchor>afd2c60eb72b03a4f36aa9b09e76cf62e</anchor>
      <arglist>(const Scalar &amp;alpha)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>RTOpPack::TOpAssignScalarEleWiseTransformation</name>
    <filename>classRTOpPack_1_1TOpAssignScalarEleWiseTransformation.html</filename>
    <templarg></templarg>
    <member kind="function">
      <type></type>
      <name>TOpAssignScalarEleWiseTransformation</name>
      <anchorfile>classRTOpPack_1_1TOpAssignScalarEleWiseTransformation.html</anchorfile>
      <anchor>a10f08fd4cb9baee8843714087eed9d83</anchor>
      <arglist>(const Scalar &amp;alpha)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>operator()</name>
      <anchorfile>classRTOpPack_1_1TOpAssignScalarEleWiseTransformation.html</anchorfile>
      <anchor>ac8825ff651ff8f72a545cd26f7ed9fda</anchor>
      <arglist>(Scalar &amp;z0) const </arglist>
    </member>
    <member kind="function" protection="private">
      <type></type>
      <name>TOpAssignScalarEleWiseTransformation</name>
      <anchorfile>classRTOpPack_1_1TOpAssignScalarEleWiseTransformation.html</anchorfile>
      <anchor>a3ea1dfffd8d233faab91f1814b2ddbdf</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>Scalar</type>
      <name>alpha_</name>
      <anchorfile>classRTOpPack_1_1TOpAssignScalarEleWiseTransformation.html</anchorfile>
      <anchor>a9c48336636d5bd0de0cd6b756a0c4c46</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>RTOpPack::TOpAXPY</name>
    <filename>classRTOpPack_1_1TOpAXPY.html</filename>
    <templarg></templarg>
    <base>TOp_1_1_Base&lt; Scalar, TOpAXPYEleWiseTransformation&lt; Scalar &gt; &gt;</base>
    <member kind="typedef">
      <type>TOp_1_1_Base&lt; Scalar, TOpAXPYEleWiseTransformation&lt; Scalar &gt; &gt;</type>
      <name>base_t</name>
      <anchorfile>classRTOpPack_1_1TOpAXPY.html</anchorfile>
      <anchor>a712b1ae491330e87c78d887914a08653</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>TOpAXPY</name>
      <anchorfile>classRTOpPack_1_1TOpAXPY.html</anchorfile>
      <anchor>a78ebff956e8b99412278187fbbc98a32</anchor>
      <arglist>(const Scalar &amp;alpha)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>RTOpPack::TOpAXPYEleWiseTransformation</name>
    <filename>classRTOpPack_1_1TOpAXPYEleWiseTransformation.html</filename>
    <templarg></templarg>
    <member kind="function">
      <type></type>
      <name>TOpAXPYEleWiseTransformation</name>
      <anchorfile>classRTOpPack_1_1TOpAXPYEleWiseTransformation.html</anchorfile>
      <anchor>a1e064fb450b8eaf8da019665b118af74</anchor>
      <arglist>(const Scalar &amp;alpha)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>operator()</name>
      <anchorfile>classRTOpPack_1_1TOpAXPYEleWiseTransformation.html</anchorfile>
      <anchor>a98cad351edc0b00b9dfadd442922140c</anchor>
      <arglist>(const Scalar &amp;v0, Scalar &amp;z0) const </arglist>
    </member>
    <member kind="variable" protection="private">
      <type>Scalar</type>
      <name>alpha_</name>
      <anchorfile>classRTOpPack_1_1TOpAXPYEleWiseTransformation.html</anchorfile>
      <anchor>ae59ad94e1efff4142e447d7cd8e5c500</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>RTOpPack::TOpEleWiseConjProd</name>
    <filename>classRTOpPack_1_1TOpEleWiseConjProd.html</filename>
    <templarg></templarg>
    <base>TOp_2_1_Base&lt; Scalar, TOpEleWiseConjProdEleWiseTransformation&lt; Scalar &gt; &gt;</base>
    <member kind="typedef">
      <type>TOp_2_1_Base&lt; Scalar, TOpEleWiseConjProdEleWiseTransformation&lt; Scalar &gt; &gt;</type>
      <name>base_t</name>
      <anchorfile>classRTOpPack_1_1TOpEleWiseConjProd.html</anchorfile>
      <anchor>a90082f7fb25928f0aff8961b03f9c2f2</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>TOpEleWiseConjProd</name>
      <anchorfile>classRTOpPack_1_1TOpEleWiseConjProd.html</anchorfile>
      <anchor>aac088d5867e2760b7a2aa1e15093d30e</anchor>
      <arglist>(const Scalar &amp;alpha)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>RTOpPack::TOpEleWiseConjProdEleWiseTransformation</name>
    <filename>classRTOpPack_1_1TOpEleWiseConjProdEleWiseTransformation.html</filename>
    <templarg></templarg>
    <member kind="function">
      <type></type>
      <name>TOpEleWiseConjProdEleWiseTransformation</name>
      <anchorfile>classRTOpPack_1_1TOpEleWiseConjProdEleWiseTransformation.html</anchorfile>
      <anchor>a42707b5000729d7dc320d8831134e6ff</anchor>
      <arglist>(const Scalar &amp;alpha)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>operator()</name>
      <anchorfile>classRTOpPack_1_1TOpEleWiseConjProdEleWiseTransformation.html</anchorfile>
      <anchor>af1bd8dd59ee5587e7afc0f9539958c91</anchor>
      <arglist>(const Scalar &amp;v0, const Scalar &amp;v1, Scalar &amp;z0) const </arglist>
    </member>
    <member kind="variable" protection="private">
      <type>Scalar</type>
      <name>alpha_</name>
      <anchorfile>classRTOpPack_1_1TOpEleWiseConjProdEleWiseTransformation.html</anchorfile>
      <anchor>a93a79da44c5726b12371490ea5713803</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>RTOpPack::TOpEleWiseDivide</name>
    <filename>classRTOpPack_1_1TOpEleWiseDivide.html</filename>
    <templarg></templarg>
    <base>TOp_2_1_Base&lt; Scalar, TOpEleWiseDivideEleWiseTransformation&lt; Scalar &gt; &gt;</base>
    <member kind="typedef">
      <type>TOp_2_1_Base&lt; Scalar, TOpEleWiseDivideEleWiseTransformation&lt; Scalar &gt; &gt;</type>
      <name>base_t</name>
      <anchorfile>classRTOpPack_1_1TOpEleWiseDivide.html</anchorfile>
      <anchor>aafa7fb85c7d7685ef878472ab775a0d3</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>TOpEleWiseDivide</name>
      <anchorfile>classRTOpPack_1_1TOpEleWiseDivide.html</anchorfile>
      <anchor>a0ca0877a85f8eff3ee43cf431d931598</anchor>
      <arglist>(const Scalar &amp;alpha)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>RTOpPack::TOpEleWiseDivideEleWiseTransformation</name>
    <filename>classRTOpPack_1_1TOpEleWiseDivideEleWiseTransformation.html</filename>
    <templarg></templarg>
    <member kind="function">
      <type></type>
      <name>TOpEleWiseDivideEleWiseTransformation</name>
      <anchorfile>classRTOpPack_1_1TOpEleWiseDivideEleWiseTransformation.html</anchorfile>
      <anchor>ab556b8329fa71c041b68daeb78e353fb</anchor>
      <arglist>(const Scalar &amp;alpha)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>operator()</name>
      <anchorfile>classRTOpPack_1_1TOpEleWiseDivideEleWiseTransformation.html</anchorfile>
      <anchor>afbf47d7644a703dc368cdc4c1ae6ae16</anchor>
      <arglist>(const Scalar &amp;v0, const Scalar &amp;v1, Scalar &amp;z0) const </arglist>
    </member>
    <member kind="variable" protection="private">
      <type>Scalar</type>
      <name>alpha_</name>
      <anchorfile>classRTOpPack_1_1TOpEleWiseDivideEleWiseTransformation.html</anchorfile>
      <anchor>a81a73063c905bbf2a65b4bc2630d814d</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>RTOpPack::TOpEleWiseProd</name>
    <filename>classRTOpPack_1_1TOpEleWiseProd.html</filename>
    <templarg></templarg>
    <base>TOp_2_1_Base&lt; Scalar, TOpEleWiseProdEleWiseTransformation&lt; Scalar &gt; &gt;</base>
    <member kind="typedef">
      <type>TOp_2_1_Base&lt; Scalar, TOpEleWiseProdEleWiseTransformation&lt; Scalar &gt; &gt;</type>
      <name>base_t</name>
      <anchorfile>classRTOpPack_1_1TOpEleWiseProd.html</anchorfile>
      <anchor>a53d8df39a7f3aad5e7d85b0ba12f2533</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>TOpEleWiseProd</name>
      <anchorfile>classRTOpPack_1_1TOpEleWiseProd.html</anchorfile>
      <anchor>a667ebb70b8ff2cf11a86dc1177c7e96f</anchor>
      <arglist>(const Scalar &amp;alpha)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>RTOpPack::TOpEleWiseProdEleWiseTransformation</name>
    <filename>classRTOpPack_1_1TOpEleWiseProdEleWiseTransformation.html</filename>
    <templarg></templarg>
    <member kind="function">
      <type></type>
      <name>TOpEleWiseProdEleWiseTransformation</name>
      <anchorfile>classRTOpPack_1_1TOpEleWiseProdEleWiseTransformation.html</anchorfile>
      <anchor>a8bcb852fb77ab9529b56bc6d6c88b6a3</anchor>
      <arglist>(const Scalar &amp;alpha)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>operator()</name>
      <anchorfile>classRTOpPack_1_1TOpEleWiseProdEleWiseTransformation.html</anchorfile>
      <anchor>a98327a6ec5d505c9a3c6f1156f1df7cd</anchor>
      <arglist>(const Scalar &amp;v0, const Scalar &amp;v1, Scalar &amp;z0) const </arglist>
    </member>
    <member kind="variable" protection="private">
      <type>Scalar</type>
      <name>alpha_</name>
      <anchorfile>classRTOpPack_1_1TOpEleWiseProdEleWiseTransformation.html</anchorfile>
      <anchor>aad8f7f066d24f3b36aff8e75c311809e</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>RTOpPack::TOpEleWiseProdUpdate</name>
    <filename>classRTOpPack_1_1TOpEleWiseProdUpdate.html</filename>
    <templarg></templarg>
    <base>TOp_1_1_Base&lt; Scalar, TOpEleWiseProdUpdateEleWiseTransformation&lt; Scalar &gt; &gt;</base>
    <member kind="typedef">
      <type>TOp_1_1_Base&lt; Scalar, TOpEleWiseProdUpdateEleWiseTransformation&lt; Scalar &gt; &gt;</type>
      <name>base_t</name>
      <anchorfile>classRTOpPack_1_1TOpEleWiseProdUpdate.html</anchorfile>
      <anchor>acccf1978eb7d29045e8d020fd3e298a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>TOpEleWiseProdUpdate</name>
      <anchorfile>classRTOpPack_1_1TOpEleWiseProdUpdate.html</anchorfile>
      <anchor>a98bd6730e85bcceb3d94a88cde9b8504</anchor>
      <arglist>(const Scalar &amp;alpha)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>RTOpPack::TOpEleWiseProdUpdateEleWiseTransformation</name>
    <filename>classRTOpPack_1_1TOpEleWiseProdUpdateEleWiseTransformation.html</filename>
    <templarg></templarg>
    <member kind="function">
      <type></type>
      <name>TOpEleWiseProdUpdateEleWiseTransformation</name>
      <anchorfile>classRTOpPack_1_1TOpEleWiseProdUpdateEleWiseTransformation.html</anchorfile>
      <anchor>ab99225a82c0f9122263e7def4252fdad</anchor>
      <arglist>(const Scalar &amp;alpha)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>operator()</name>
      <anchorfile>classRTOpPack_1_1TOpEleWiseProdUpdateEleWiseTransformation.html</anchorfile>
      <anchor>a17b0551e288ab867e9bf6e13a8899361</anchor>
      <arglist>(const Scalar &amp;v0, Scalar &amp;z0) const </arglist>
    </member>
    <member kind="variable" protection="private">
      <type>Scalar</type>
      <name>alpha_</name>
      <anchorfile>classRTOpPack_1_1TOpEleWiseProdUpdateEleWiseTransformation.html</anchorfile>
      <anchor>a7e3df162e1154c994bd686a9568a2b66</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>RTOpPack::TOpEleWiseScale</name>
    <filename>classRTOpPack_1_1TOpEleWiseScale.html</filename>
    <templarg></templarg>
    <base>TOp_1_1_Base&lt; Scalar, TOpEleWiseScaleEleWiseTransformation&lt; Scalar &gt; &gt;</base>
    <member kind="function">
      <type></type>
      <name>TOpEleWiseScale</name>
      <anchorfile>classRTOpPack_1_1TOpEleWiseScale.html</anchorfile>
      <anchor>a365871290713036acf0bd3c099098bb3</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>RTOpPack::TOpEleWiseScaleEleWiseTransformation</name>
    <filename>classRTOpPack_1_1TOpEleWiseScaleEleWiseTransformation.html</filename>
    <templarg></templarg>
    <member kind="function">
      <type>void</type>
      <name>operator()</name>
      <anchorfile>classRTOpPack_1_1TOpEleWiseScaleEleWiseTransformation.html</anchorfile>
      <anchor>ad59f10e88a27f0f84c2520d440c9f186</anchor>
      <arglist>(const Scalar &amp;v0, Scalar &amp;z0) const </arglist>
    </member>
    <member kind="variable" protection="private">
      <type>Scalar</type>
      <name>alpha_</name>
      <anchorfile>classRTOpPack_1_1TOpEleWiseScaleEleWiseTransformation.html</anchorfile>
      <anchor>a8686c1da93464049b4843b93418bcd3f</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>RTOpPack::TOpLinearCombination</name>
    <filename>classRTOpPack_1_1TOpLinearCombination.html</filename>
    <templarg></templarg>
    <base>RTOpPack::RTOpT</base>
    <member kind="function">
      <type></type>
      <name>TOpLinearCombination</name>
      <anchorfile>classRTOpPack_1_1TOpLinearCombination.html</anchorfile>
      <anchor>a9c29a3e4d62024151370d9b4eaa939e1</anchor>
      <arglist>(const ArrayView&lt; const Scalar &gt; &amp;alpha_in=Teuchos::null, const Scalar &amp;beta=Teuchos::ScalarTraits&lt; Scalar &gt;::zero())</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>alpha</name>
      <anchorfile>classRTOpPack_1_1TOpLinearCombination.html</anchorfile>
      <anchor>aa3bb5b57bea71a49c6b422ec015bad14</anchor>
      <arglist>(const ArrayView&lt; const Scalar &gt; &amp;alpha_in)</arglist>
    </member>
    <member kind="function">
      <type>const ArrayView&lt; const Scalar &gt;</type>
      <name>alpha</name>
      <anchorfile>classRTOpPack_1_1TOpLinearCombination.html</anchorfile>
      <anchor>a4bf1fbe21fecf222967787fd18f85381</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>beta</name>
      <anchorfile>classRTOpPack_1_1TOpLinearCombination.html</anchorfile>
      <anchor>a73da4d62d8ac0dc1dca31d4691fd6606</anchor>
      <arglist>(const Scalar &amp;beta_in)</arglist>
    </member>
    <member kind="function">
      <type>Scalar</type>
      <name>beta</name>
      <anchorfile>classRTOpPack_1_1TOpLinearCombination.html</anchorfile>
      <anchor>aa0eaeba7eedde92d346d2eff7a5d8c03</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>num_vecs</name>
      <anchorfile>classRTOpPack_1_1TOpLinearCombination.html</anchorfile>
      <anchor>ac3e9d2d55295b93e87506aca74e07eb6</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="variable" protection="private">
      <type>Scalar</type>
      <name>beta_</name>
      <anchorfile>classRTOpPack_1_1TOpLinearCombination.html</anchorfile>
      <anchor>a84638c061783fd798be0d9df48222b81</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>Array&lt; Scalar &gt;</type>
      <name>alpha_</name>
      <anchorfile>classRTOpPack_1_1TOpLinearCombination.html</anchorfile>
      <anchor>afce33a37ddd57c5e6e2fdd7a422aa3ee</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>apply_op_impl</name>
      <anchorfile>classRTOpPack_1_1TOpLinearCombination.html</anchorfile>
      <anchor>a46e016c8a2dde5b248c93b3c9ad8d6f0</anchor>
      <arglist>(const ArrayView&lt; const ConstSubVectorView&lt; Scalar &gt; &gt; &amp;sub_vecs, const ArrayView&lt; const SubVectorView&lt; Scalar &gt; &gt; &amp;targ_sub_vecs, const Ptr&lt; ReductTarget &gt; &amp;reduct_obj_inout) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>RTOpPack::TOpRandomize</name>
    <filename>classRTOpPack_1_1TOpRandomize.html</filename>
    <templarg></templarg>
    <base>RTOpPack::RTOpT</base>
    <member kind="function">
      <type></type>
      <name>TOpRandomize</name>
      <anchorfile>classRTOpPack_1_1TOpRandomize.html</anchorfile>
      <anchor>a89d010fb5c03f3d06bfe13f6dd6f34fe</anchor>
      <arglist>(const Scalar &amp;l=-ScalarTraits&lt; Scalar &gt;::one(), const Scalar &amp;u=+ScalarTraits&lt; Scalar &gt;::one())</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_bounds</name>
      <anchorfile>classRTOpPack_1_1TOpRandomize.html</anchorfile>
      <anchor>a6f4e9c3b2b75309b787407d6f1766af1</anchor>
      <arglist>(const Scalar &amp;l, const Scalar &amp;u)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_seed</name>
      <anchorfile>classRTOpPack_1_1TOpRandomize.html</anchorfile>
      <anchor>a96f4025f22170b61545d94c0ed222a3b</anchor>
      <arglist>(const unsigned int seed)</arglist>
    </member>
    <member kind="function">
      <type>unsigned int</type>
      <name>get_seed</name>
      <anchorfile>classRTOpPack_1_1TOpRandomize.html</anchorfile>
      <anchor>a16814eb3e2e56027078a4dfa83e65cd6</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>set_static_seed</name>
      <anchorfile>classRTOpPack_1_1TOpRandomize.html</anchorfile>
      <anchor>aca817f4de04f91e7a5e29cfd59a83cf1</anchor>
      <arglist>(const unsigned int static_seed)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static unsigned int</type>
      <name>get_static_seed</name>
      <anchorfile>classRTOpPack_1_1TOpRandomize.html</anchorfile>
      <anchor>ae8140efa882784796fb93cace4db62d5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>unsigned int</type>
      <name>seed_</name>
      <anchorfile>classRTOpPack_1_1TOpRandomize.html</anchorfile>
      <anchor>aa9d42e105fce0d84fc92b6f98410fac9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>Scalar</type>
      <name>l_</name>
      <anchorfile>classRTOpPack_1_1TOpRandomize.html</anchorfile>
      <anchor>aa70c9131d62c875c556061c7649d5682</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>Scalar</type>
      <name>u_</name>
      <anchorfile>classRTOpPack_1_1TOpRandomize.html</anchorfile>
      <anchor>a6be2131f43b2c66d6d68ff042ea86b2c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private" static="yes">
      <type>static unsigned int</type>
      <name>static_seed_</name>
      <anchorfile>classRTOpPack_1_1TOpRandomize.html</anchorfile>
      <anchor>aa55cd2a9132350d6081adf23c272763c</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>apply_op_impl</name>
      <anchorfile>classRTOpPack_1_1TOpRandomize.html</anchorfile>
      <anchor>a4baa58f626396f9131e1616021a9fc33</anchor>
      <arglist>(const ArrayView&lt; const ConstSubVectorView&lt; Scalar &gt; &gt; &amp;sub_vecs, const ArrayView&lt; const SubVectorView&lt; Scalar &gt; &gt; &amp;targ_sub_vecs, const Ptr&lt; ReductTarget &gt; &amp;reduct_obj_inout) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>RTOpPack::TOpScaleVector</name>
    <filename>classRTOpPack_1_1TOpScaleVector.html</filename>
    <templarg></templarg>
    <base>TOp_0_1_Base&lt; Scalar, TOpScaleVectorEleWiseTransformation&lt; Scalar &gt; &gt;</base>
    <member kind="typedef">
      <type>TOp_0_1_Base&lt; Scalar, TOpScaleVectorEleWiseTransformation&lt; Scalar &gt; &gt;</type>
      <name>base_t</name>
      <anchorfile>classRTOpPack_1_1TOpScaleVector.html</anchorfile>
      <anchor>acd3205c144a76cea219d86d6c9a34323</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>TOpScaleVector</name>
      <anchorfile>classRTOpPack_1_1TOpScaleVector.html</anchorfile>
      <anchor>ac545dc0fb62182e2580c2fe63ed5f0a7</anchor>
      <arglist>(const Scalar &amp;alpha)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>RTOpPack::TOpScaleVectorEleWiseTransformation</name>
    <filename>classRTOpPack_1_1TOpScaleVectorEleWiseTransformation.html</filename>
    <templarg></templarg>
    <member kind="function">
      <type></type>
      <name>TOpScaleVectorEleWiseTransformation</name>
      <anchorfile>classRTOpPack_1_1TOpScaleVectorEleWiseTransformation.html</anchorfile>
      <anchor>ac51d1b71b536fa1e0d2437baeae4037a</anchor>
      <arglist>(const Scalar &amp;alpha)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>operator()</name>
      <anchorfile>classRTOpPack_1_1TOpScaleVectorEleWiseTransformation.html</anchorfile>
      <anchor>af0043d8722d8458d58e91188656bbb98</anchor>
      <arglist>(Scalar &amp;z0) const </arglist>
    </member>
    <member kind="variable" protection="private">
      <type>Scalar</type>
      <name>alpha_</name>
      <anchorfile>classRTOpPack_1_1TOpScaleVectorEleWiseTransformation.html</anchorfile>
      <anchor>a9c55df55db32726ad30a612470cb27ce</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>RTOpPack::TOpSetAssendingValues</name>
    <filename>classRTOpPack_1_1TOpSetAssendingValues.html</filename>
    <templarg></templarg>
    <base>TOp_0_1_CoordVariantBase&lt; Scalar, TOpSetAssendingValuesEleWiseTransformation&lt; Scalar &gt; &gt;</base>
    <member kind="typedef">
      <type>TOp_0_1_CoordVariantBase&lt; Scalar, TOpSetAssendingValuesEleWiseTransformation&lt; Scalar &gt; &gt;</type>
      <name>base_t</name>
      <anchorfile>classRTOpPack_1_1TOpSetAssendingValues.html</anchorfile>
      <anchor>a1412ce3eb9c1fa860b87706c59cd793f</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>TOpSetAssendingValues</name>
      <anchorfile>classRTOpPack_1_1TOpSetAssendingValues.html</anchorfile>
      <anchor>a43bea5615ea2dd689aa203cafd419136</anchor>
      <arglist>(const Scalar &amp;offset=static_cast&lt; Scalar &gt;(0.0))</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>RTOpPack::TOpSetAssendingValuesEleWiseTransformation</name>
    <filename>classRTOpPack_1_1TOpSetAssendingValuesEleWiseTransformation.html</filename>
    <templarg></templarg>
    <member kind="function">
      <type></type>
      <name>TOpSetAssendingValuesEleWiseTransformation</name>
      <anchorfile>classRTOpPack_1_1TOpSetAssendingValuesEleWiseTransformation.html</anchorfile>
      <anchor>a2caeff62e1e645d214a2906c7c8229d0</anchor>
      <arglist>(const Scalar &amp;offset)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>operator()</name>
      <anchorfile>classRTOpPack_1_1TOpSetAssendingValuesEleWiseTransformation.html</anchorfile>
      <anchor>a159eb227dbd5bcdb0ad437a9f7bb336e</anchor>
      <arglist>(const Ordinal global_i, Scalar &amp;z0) const </arglist>
    </member>
    <member kind="function" protection="private">
      <type></type>
      <name>TOpSetAssendingValuesEleWiseTransformation</name>
      <anchorfile>classRTOpPack_1_1TOpSetAssendingValuesEleWiseTransformation.html</anchorfile>
      <anchor>a3beab0f60ad3e197e05a760be1d2a296</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>Scalar</type>
      <name>offset_</name>
      <anchorfile>classRTOpPack_1_1TOpSetAssendingValuesEleWiseTransformation.html</anchorfile>
      <anchor>a8351d92ac1f8546951b7bb2ecb0cd12b</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>RTOpPack::TOpSetElement</name>
    <filename>classRTOpPack_1_1TOpSetElement.html</filename>
    <templarg></templarg>
    <base>TOp_0_1_CoordVariantBase&lt; Scalar, TOpSetElementEleWiseTransformation&lt; Scalar &gt; &gt;</base>
    <member kind="function">
      <type></type>
      <name>TOpSetElement</name>
      <anchorfile>classRTOpPack_1_1TOpSetElement.html</anchorfile>
      <anchor>a6e5491ab959839859b4eb4f7851c60d3</anchor>
      <arglist>(const Ordinal &amp;global_i_in=-1, const Scalar &amp;val_i_in=static_cast&lt; Scalar &gt;(0.0))</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initialize</name>
      <anchorfile>classRTOpPack_1_1TOpSetElement.html</anchorfile>
      <anchor>a6fcd4abad4ec97d72e01e3a657632d99</anchor>
      <arglist>(const Ordinal &amp;global_i_in, const Scalar &amp;val_i_in)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual Range1D</type>
      <name>range_impl</name>
      <anchorfile>classRTOpPack_1_1TOpSetElement.html</anchorfile>
      <anchor>a5085be62f1fa63ce94a153e2ea63c645</anchor>
      <arglist>() const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>RTOpPack::TOpSetElementEleWiseTransformation</name>
    <filename>classRTOpPack_1_1TOpSetElementEleWiseTransformation.html</filename>
    <templarg></templarg>
    <member kind="function">
      <type></type>
      <name>TOpSetElementEleWiseTransformation</name>
      <anchorfile>classRTOpPack_1_1TOpSetElementEleWiseTransformation.html</anchorfile>
      <anchor>ae0b660c64ef36fe9ac7a2a00a2973fee</anchor>
      <arglist>(const Ordinal &amp;global_i_in=-1, const Scalar &amp;val_i_in=static_cast&lt; Scalar &gt;(0.0))</arglist>
    </member>
    <member kind="function">
      <type>Ordinal</type>
      <name>global_i</name>
      <anchorfile>classRTOpPack_1_1TOpSetElementEleWiseTransformation.html</anchorfile>
      <anchor>a839cd04f50abb5c4f1f497c46c60e1a6</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>operator()</name>
      <anchorfile>classRTOpPack_1_1TOpSetElementEleWiseTransformation.html</anchorfile>
      <anchor>a31225e84a33fd259bd56015a47d73fe8</anchor>
      <arglist>(const Ordinal global_i_in, Scalar &amp;z0) const </arglist>
    </member>
    <member kind="variable" protection="private">
      <type>Ordinal</type>
      <name>global_i_</name>
      <anchorfile>classRTOpPack_1_1TOpSetElementEleWiseTransformation.html</anchorfile>
      <anchor>a58662f2d93f5027d07c7969eed751931</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>Scalar</type>
      <name>val_i_</name>
      <anchorfile>classRTOpPack_1_1TOpSetElementEleWiseTransformation.html</anchorfile>
      <anchor>a089aa7c79fe924bbc6236bdc1100bb48</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>RTOpPack::TOpSetSubVector</name>
    <filename>classRTOpPack_1_1TOpSetSubVector.html</filename>
    <templarg></templarg>
    <base>RTOpPack::RTOpT</base>
    <member kind="typedef">
      <type>RTOpT&lt; Scalar &gt;::primitive_value_type</type>
      <name>primitive_value_type</name>
      <anchorfile>classRTOpPack_1_1TOpSetSubVector.html</anchorfile>
      <anchor>a9b980dff92e43a5d82b5a95e4e41c2bd</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue" protection="private">
      <name>num_sub_vec_members</name>
      <anchorfile>classRTOpPack_1_1TOpSetSubVector.html</anchorfile>
      <anchor>a80958dfaa37098ddcfc8ef698cbfb30da78b973a6a5897ef5e1239787eca07289</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue" protection="private">
      <name>num_sub_vec_members</name>
      <anchorfile>classRTOpPack_1_1TOpSetSubVector.html</anchorfile>
      <anchor>a80958dfaa37098ddcfc8ef698cbfb30da78b973a6a5897ef5e1239787eca07289</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>SparseSubVectorT&lt; Scalar &gt;</type>
      <name>sub_vec_</name>
      <anchorfile>classRTOpPack_1_1TOpSetSubVector.html</anchorfile>
      <anchor>a11f5ca989e5030148b711c7014e4f7e4</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>TOpSetSubVector</name>
      <anchorfile>classRTOpPack_1_1TOpSetSubVector.html</anchorfile>
      <anchor>ab6311856deddb286d4e8448b2208d8a3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>TOpSetSubVector</name>
      <anchorfile>classRTOpPack_1_1TOpSetSubVector.html</anchorfile>
      <anchor>aa32948636d9f4a7a5e22ce506c31754f</anchor>
      <arglist>(const SparseSubVectorT&lt; Scalar &gt; &amp;sub_vec)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_sub_vec</name>
      <anchorfile>classRTOpPack_1_1TOpSetSubVector.html</anchorfile>
      <anchor>a9aae41a2efcbaf1d2efecf150c252749</anchor>
      <arglist>(const SparseSubVectorT&lt; Scalar &gt; &amp;sub_vec)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>bool</type>
      <name>coord_invariant_impl</name>
      <anchorfile>classRTOpPack_1_1TOpSetSubVector.html</anchorfile>
      <anchor>a3dc136ea2de28ff8fb509d824c6e0c1b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>apply_op_impl</name>
      <anchorfile>classRTOpPack_1_1TOpSetSubVector.html</anchorfile>
      <anchor>a02d5beb96ac3bb507561b6e788773183</anchor>
      <arglist>(const ArrayView&lt; const ConstSubVectorView&lt; Scalar &gt; &gt; &amp;sub_vecs, const ArrayView&lt; const SubVectorView&lt; Scalar &gt; &gt; &amp;targ_sub_vecs, const Ptr&lt; ReductTarget &gt; &amp;reduct_obj) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>RTOpPack::TOpUnaryFuncPtr</name>
    <filename>classRTOpPack_1_1TOpUnaryFuncPtr.html</filename>
    <templarg></templarg>
    <base>RTOpPack::RTOpT</base>
    <member kind="typedef">
      <type>void(*</type>
      <name>unary_func_ptr_t</name>
      <anchorfile>classRTOpPack_1_1TOpUnaryFuncPtr.html</anchorfile>
      <anchor>a1f54051e5fbd4011f7bfdb9bb5c72664</anchor>
      <arglist>)(const Scalar x[], int x_dim, Scalar out[])</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>TOpUnaryFuncPtr</name>
      <anchorfile>classRTOpPack_1_1TOpUnaryFuncPtr.html</anchorfile>
      <anchor>a0ac0276f68ecdac964c8bd07bc9f0eac</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>TOpUnaryFuncPtr</name>
      <anchorfile>classRTOpPack_1_1TOpUnaryFuncPtr.html</anchorfile>
      <anchor>aa03232ade6038acc8a2cb1bb28dd3db4</anchor>
      <arglist>(unary_func_ptr_t unary_func_ptr, const std::string &amp;op_name)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initialize</name>
      <anchorfile>classRTOpPack_1_1TOpUnaryFuncPtr.html</anchorfile>
      <anchor>a946cab2c5ac41c604d81ed7aa8d3a055</anchor>
      <arglist>(unary_func_ptr_t unary_func_ptr, const std::string &amp;op_name)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_initialized</name>
      <anchorfile>classRTOpPack_1_1TOpUnaryFuncPtr.html</anchorfile>
      <anchor>a5bcf40be82404dc07f8084d109930c96</anchor>
      <arglist>(unary_func_ptr_t *unary_func_ptr=NULL, std::string *op_name=NULL)</arglist>
    </member>
    <member kind="function" protection="private">
      <type></type>
      <name>TOpUnaryFuncPtr</name>
      <anchorfile>classRTOpPack_1_1TOpUnaryFuncPtr.html</anchorfile>
      <anchor>abc98187f189cb65bdfdf2abd79a87850</anchor>
      <arglist>(const TOpUnaryFuncPtr &amp;)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>TOpUnaryFuncPtr &amp;</type>
      <name>operator=</name>
      <anchorfile>classRTOpPack_1_1TOpUnaryFuncPtr.html</anchorfile>
      <anchor>ad2564028570a920f6a7c5ae6809f5f42</anchor>
      <arglist>(const TOpUnaryFuncPtr &amp;)</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>std::string</type>
      <name>op_name_</name>
      <anchorfile>classRTOpPack_1_1TOpUnaryFuncPtr.html</anchorfile>
      <anchor>a826a66de6cdc6f2807d94e89c45985d3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>unary_func_ptr_t</type>
      <name>unary_func_ptr_</name>
      <anchorfile>classRTOpPack_1_1TOpUnaryFuncPtr.html</anchorfile>
      <anchor>af9fbcb595f48f654821a66d248340fa5</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>const char *</type>
      <name>op_name</name>
      <anchorfile>classRTOpPack_1_1TOpUnaryFuncPtr.html</anchorfile>
      <anchor>a7d967bfcb2cab91e0022234078b2e72e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>apply_op</name>
      <anchorfile>classRTOpPack_1_1TOpUnaryFuncPtr.html</anchorfile>
      <anchor>a2d7b4de7124ffd95aac7f2a1ad08cf4c</anchor>
      <arglist>(const int num_vecs, const ConstSubVectorView&lt; Scalar &gt; sub_vecs[], const int num_targ_vecs, const SubVectorView&lt; Scalar &gt; targ_sub_vecs[], ReductTarget *reduct_obj) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>RTOpPack::UnknownError</name>
    <filename>classRTOpPack_1_1UnknownError.html</filename>
    <member kind="function">
      <type></type>
      <name>UnknownError</name>
      <anchorfile>classRTOpPack_1_1UnknownError.html</anchorfile>
      <anchor>a9cf63b506dafc4aad189aab4da21a640</anchor>
      <arglist>(const std::string &amp;what_arg)</arglist>
    </member>
  </compound>
  <compound kind="namespace">
    <name>RTOpPack</name>
    <filename>namespaceRTOpPack.html</filename>
    <class kind="class">RTOpPack::BasicReductObjReductionOp</class>
    <class kind="class">RTOpPack::BasicReductObjReductionOp&lt; ConcreteReductObj, REDUCT_TYPE_MAX &gt;</class>
    <class kind="class">RTOpPack::BasicReductObjReductionOp&lt; ConcreteReductObj, REDUCT_TYPE_MIN &gt;</class>
    <class kind="class">RTOpPack::BasicReductObjReductionOp&lt; ConcreteReductObj, REDUCT_TYPE_SUM &gt;</class>
    <class kind="class">RTOpPack::ConstSubMultiVectorView</class>
    <class kind="class">RTOpPack::ConstSubVectorView</class>
    <class kind="class">RTOpPack::DefaultReductTarget</class>
    <class kind="class">RTOpPack::IncompatibleReductObj</class>
    <class kind="class">RTOpPack::IncompatibleVecs</class>
    <class kind="class">RTOpPack::InvalidNumTargVecs</class>
    <class kind="class">RTOpPack::InvalidNumVecs</class>
    <class kind="class">RTOpPack::InvalidUsage</class>
    <class kind="class">RTOpPack::PrimitiveTypeTraits</class>
    <class kind="class">RTOpPack::PrimitiveTypeTraits&lt; Scalar, index_type &gt;</class>
    <class kind="class">RTOpPack::PrimitiveTypeTraits&lt; Scalar, Scalar &gt;</class>
    <class kind="class">RTOpPack::PrimitiveTypeTraits&lt; Scalar, ScalarIndex&lt; Scalar &gt; &gt;</class>
    <class kind="class">RTOpPack::ReductTarget</class>
    <class kind="class">RTOpPack::ReductTargetReductionOp</class>
    <class kind="class">RTOpPack::ReductTargetSerializer</class>
    <class kind="class">RTOpPack::ROp_1_CoordVariantScalarReduction</class>
    <class kind="class">RTOpPack::ROp_1_ScalarReduction</class>
    <class kind="class">RTOpPack::ROp_2_ScalarReduction</class>
    <class kind="class">RTOpPack::ROpGetElement</class>
    <class kind="class">RTOpPack::ROpGetElementEleWiseReductionOp</class>
    <class kind="class">RTOpPack::ROpGetSubVector</class>
    <class kind="class">RTOpPack::ROpMaxIndex</class>
    <class kind="class">RTOpPack::ROpMaxIndexEleWiseReductionOp</class>
    <class kind="class">RTOpPack::ROpMaxIndexLessThanBound</class>
    <class kind="class">RTOpPack::ROpMaxIndexLessThanBoundEleWiseReductionOp</class>
    <class kind="class">RTOpPack::ROpMaxIndexReductObjReductionOp</class>
    <class kind="class">RTOpPack::ROpMinIndex</class>
    <class kind="class">RTOpPack::ROpMinIndexEleWiseReductionOp</class>
    <class kind="class">RTOpPack::ROpMinIndexGreaterThanBound</class>
    <class kind="class">RTOpPack::ROpMinIndexGreaterThanBoundEleWiseReductionOp</class>
    <class kind="class">RTOpPack::ROpMinIndexReductObjReductionOp</class>
    <class kind="class">RTOpPack::ROpNorm2</class>
    <class kind="class">RTOpPack::ROpNorm2EleWiseReduction</class>
    <class kind="class">RTOpPack::ROpScalarReductionWithOpBase</class>
    <class kind="class">RTOpPack::ROpWeightedNorm2</class>
    <class kind="class">RTOpPack::ROpWeightedNorm2EleWiseReduction</class>
    <class kind="class">RTOpPack::RTOpServer</class>
    <class kind="class">RTOpPack::RTOpSubRangeDecorator</class>
    <class kind="class">RTOpPack::RTOpT</class>
    <class kind="struct">RTOpPack::ScalarIndex</class>
    <class kind="class">RTOpPack::SparseSubVectorT</class>
    <class kind="class">RTOpPack::SubMultiVectorView</class>
    <class kind="class">RTOpPack::SubVectorView</class>
    <class kind="class">RTOpPack::SumScalarReductObjReduction</class>
    <class kind="class">RTOpPack::TOp_0_1_Base</class>
    <class kind="class">RTOpPack::TOp_0_1_CoordVariantBase</class>
    <class kind="class">RTOpPack::TOp_1_1_Base</class>
    <class kind="class">RTOpPack::TOp_2_1_Base</class>
    <class kind="class">RTOpPack::TOp_3_1_Base</class>
    <class kind="class">RTOpPack::TOpAddScalar</class>
    <class kind="class">RTOpPack::TOpAddScalarEleWiseTransformation</class>
    <class kind="class">RTOpPack::TOpAssignScalar</class>
    <class kind="class">RTOpPack::TOpAssignScalarEleWiseTransformation</class>
    <class kind="class">RTOpPack::TOpAXPY</class>
    <class kind="class">RTOpPack::TOpAXPYEleWiseTransformation</class>
    <class kind="class">RTOpPack::TOpEleWiseConjProd</class>
    <class kind="class">RTOpPack::TOpEleWiseConjProdEleWiseTransformation</class>
    <class kind="class">RTOpPack::TOpEleWiseDivide</class>
    <class kind="class">RTOpPack::TOpEleWiseDivideEleWiseTransformation</class>
    <class kind="class">RTOpPack::TOpEleWiseProd</class>
    <class kind="class">RTOpPack::TOpEleWiseProdEleWiseTransformation</class>
    <class kind="class">RTOpPack::TOpEleWiseProdUpdate</class>
    <class kind="class">RTOpPack::TOpEleWiseProdUpdateEleWiseTransformation</class>
    <class kind="class">RTOpPack::TOpEleWiseScale</class>
    <class kind="class">RTOpPack::TOpEleWiseScaleEleWiseTransformation</class>
    <class kind="class">RTOpPack::TOpLinearCombination</class>
    <class kind="class">RTOpPack::TOpRandomize</class>
    <class kind="class">RTOpPack::TOpScaleVector</class>
    <class kind="class">RTOpPack::TOpScaleVectorEleWiseTransformation</class>
    <class kind="class">RTOpPack::TOpSetAssendingValues</class>
    <class kind="class">RTOpPack::TOpSetAssendingValuesEleWiseTransformation</class>
    <class kind="class">RTOpPack::TOpSetElement</class>
    <class kind="class">RTOpPack::TOpSetElementEleWiseTransformation</class>
    <class kind="class">RTOpPack::TOpSetSubVector</class>
    <class kind="class">RTOpPack::TOpUnaryFuncPtr</class>
    <class kind="class">RTOpPack::UnknownError</class>
    <member kind="typedef">
      <type>Teuchos_Ordinal</type>
      <name>Ordinal</name>
      <anchorfile>namespaceRTOpPack.html</anchorfile>
      <anchor>a2748f9607cdb199b78e4fb3b1a0675c3</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Teuchos_Ordinal</type>
      <name>index_type</name>
      <anchorfile>namespaceRTOpPack.html</anchorfile>
      <anchor>a1ca78b0d4ddf52dc7f710bcca904b701</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>char</type>
      <name>char_type</name>
      <anchorfile>namespaceRTOpPack.html</anchorfile>
      <anchor>a6233a6700d436c31330a2a6d03750c40</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>ETransp</name>
      <anchorfile>namespaceRTOpPack.html</anchorfile>
      <anchor>a6dd686f0856f7da469fb22d7306586c2</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>NOTRANS</name>
      <anchorfile>namespaceRTOpPack.html</anchorfile>
      <anchor>a6dd686f0856f7da469fb22d7306586c2a88e45d282c9b05b40d977c19a3c7701a</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>TRANS</name>
      <anchorfile>namespaceRTOpPack.html</anchorfile>
      <anchor>a6dd686f0856f7da469fb22d7306586c2a3be8d472081a6dbe69bc75e16821f523</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CONJTRANS</name>
      <anchorfile>namespaceRTOpPack.html</anchorfile>
      <anchor>a6dd686f0856f7da469fb22d7306586c2a7d555adbebdbb628e639f4b311b6a2a3</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>EBasicReductTypes</name>
      <anchorfile>namespaceRTOpPack.html</anchorfile>
      <anchor>a0583d57eddf0f3d901a56dc18b768655</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>REDUCT_TYPE_SUM</name>
      <anchorfile>namespaceRTOpPack.html</anchorfile>
      <anchor>a0583d57eddf0f3d901a56dc18b768655a86fc347b5848f48b253893eb42ccac87</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>REDUCT_TYPE_MAX</name>
      <anchorfile>namespaceRTOpPack.html</anchorfile>
      <anchor>a0583d57eddf0f3d901a56dc18b768655a4fa151ed466569eceb6a0712499c2c1d</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>REDUCT_TYPE_MIN</name>
      <anchorfile>namespaceRTOpPack.html</anchorfile>
      <anchor>a0583d57eddf0f3d901a56dc18b768655a47f78de745f137e44fc0f5f6ed7071f2</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>assign_entries</name>
      <anchorfile>namespaceRTOpPack.html</anchorfile>
      <anchor>aaa21a11cf366b2ba786bd5e52678b4a2</anchor>
      <arglist>(const Ptr&lt; const SubVectorView&lt; Scalar &gt; &gt; &amp;msv, const ConstSubVectorView&lt; Scalar &gt; &amp;sv)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>assign_entries</name>
      <anchorfile>namespaceRTOpPack.html</anchorfile>
      <anchor>af3cb072a2b8d5123d616ba4057dd72b9</anchor>
      <arglist>(const Ptr&lt; const SubMultiVectorView&lt; Scalar &gt; &gt; &amp;msmv, const ConstSubMultiVectorView&lt; Scalar &gt; &amp;smv)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>getrf</name>
      <anchorfile>namespaceRTOpPack.html</anchorfile>
      <anchor>a49a263c6e33256cbcac68e3ba12176ea</anchor>
      <arglist>(const SubMultiVectorView&lt; Scalar &gt; &amp;A, const ArrayView&lt; int &gt; &amp;ipiv, const Ptr&lt; int &gt; &amp;rank)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>getrs</name>
      <anchorfile>namespaceRTOpPack.html</anchorfile>
      <anchor>a14ef611932a8c143190e2298dd57486a</anchor>
      <arglist>(const ConstSubMultiVectorView&lt; Scalar &gt; &amp;A, const ArrayView&lt; const int &gt; &amp;ipiv, const ETransp transp, const Ptr&lt; const SubMultiVectorView&lt; Scalar &gt; &gt; &amp;BX)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>RTOP_ROP_1_REDUCT_SCALAR</name>
      <anchorfile>namespaceRTOpPack.html</anchorfile>
      <anchor>a5896c1aea0d2c2b1e9f491b301f9f7fe</anchor>
      <arglist>(ROpCountNanInf, index_type, REDUCT_TYPE_SUM)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>RTOP_ROP_2_REDUCT_SCALAR</name>
      <anchorfile>namespaceRTOpPack.html</anchorfile>
      <anchor>a588fefd89bf99744acc41ad10d12a3df</anchor>
      <arglist>(ROpDotProd, Scalar, REDUCT_TYPE_SUM)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>RTOP_ROP_1_REDUCT_SCALAR_CUSTOM_DEFAULT</name>
      <anchorfile>namespaceRTOpPack.html</anchorfile>
      <anchor>af53bd72a1de3e27ebb658aecd8e067f0</anchor>
      <arglist>(ROpMax, Scalar, REDUCT_TYPE_MAX, Teuchos::as&lt; Scalar &gt;(-std::numeric_limits&lt; Scalar &gt;::max()))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>RTOP_ROP_1_REDUCT_SCALAR_CUSTOM_DEFAULT</name>
      <anchorfile>namespaceRTOpPack.html</anchorfile>
      <anchor>a9ed27681a391209cd325e9ef849fac6f</anchor>
      <arglist>(ROpMin, Scalar, REDUCT_TYPE_MIN, std::numeric_limits&lt; Scalar &gt;::max())</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>RTOP_ROP_1_REDUCT_SCALAR</name>
      <anchorfile>namespaceRTOpPack.html</anchorfile>
      <anchor>afa7883b52ca3756eea4137592a583e76</anchor>
      <arglist>(ROpNorm1, typename ScalarTraits&lt; Scalar &gt;::magnitudeType, REDUCT_TYPE_SUM)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>RTOP_ROP_1_REDUCT_SCALAR</name>
      <anchorfile>namespaceRTOpPack.html</anchorfile>
      <anchor>a935d892d691cf26e285e5fdc202d6c1e</anchor>
      <arglist>(ROpNormInf, typename ScalarTraits&lt; Scalar &gt;::magnitudeType, REDUCT_TYPE_MAX)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>RTOP_ROP_1_REDUCT_SCALAR</name>
      <anchorfile>namespaceRTOpPack.html</anchorfile>
      <anchor>a46219fb6aa99cab595fed75e4d4c05d6</anchor>
      <arglist>(ROpSum, Scalar, REDUCT_TYPE_SUM)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>RTOP_TOP_1_1</name>
      <anchorfile>namespaceRTOpPack.html</anchorfile>
      <anchor>ac8f14f954cb91c8b7ccabfd14adedcee</anchor>
      <arglist>(TOpAbs)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>RTOP_TOP_1_1</name>
      <anchorfile>namespaceRTOpPack.html</anchorfile>
      <anchor>ac7eec09c3900fd08715afab7c7874916</anchor>
      <arglist>(TOpAssignVectors)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>RTOP_TOP_1_1</name>
      <anchorfile>namespaceRTOpPack.html</anchorfile>
      <anchor>ae94e5c3710a816d7606dfc1076837a6e</anchor>
      <arglist>(TOpReciprocal)</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>version</name>
      <anchorfile>namespaceRTOpPack.html</anchorfile>
      <anchor>a377a459e637d300395ab32f30c225284</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>validate_apply_op</name>
      <anchorfile>namespaceRTOpPack.html</anchorfile>
      <anchor>a2a35e8756c033d8b824e81be457e0e71</anchor>
      <arglist>(const RTOpT&lt; Scalar &gt; &amp;op, const int allowed_num_sub_vecs, const int allowed_num_targ_sub_vecs, const bool expect_reduct_obj, const ArrayView&lt; const ConstSubVectorView&lt; Scalar &gt; &gt; &amp;sub_vecs, const ArrayView&lt; const SubVectorView&lt; Scalar &gt; &gt; &amp;targ_sub_vecs, const Ptr&lt; const ReductTarget &gt; &amp;reduct_obj)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_SPMD_apply_op_dump_out</name>
      <anchorfile>namespaceRTOpPack.html</anchorfile>
      <anchor>a79aa1319c0b2c169083658709d72a5f3</anchor>
      <arglist>(const RCP&lt; FancyOStream &gt; &amp;dumpOut)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>serializedSize</name>
      <anchorfile>namespaceRTOpPack.html</anchorfile>
      <anchor>ab4bf0e860e3a4788782b7b452d84d7c3</anchor>
      <arglist>(int num_values, int num_indexes, int num_chars)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>serialize</name>
      <anchorfile>namespaceRTOpPack.html</anchorfile>
      <anchor>a4c4bb17b58ef8668015c2bb3fa00f18e</anchor>
      <arglist>(const RTOpT&lt; Scalar &gt; &amp;op, Ordinal num_values, Ordinal num_indexes, Ordinal num_chars, const ReductTarget &amp;reduct_obj, char reduct_obj_ext[])</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>deserialize</name>
      <anchorfile>namespaceRTOpPack.html</anchorfile>
      <anchor>a43c9194b7666e79077503930013a6a50</anchor>
      <arglist>(const RTOpT&lt; Scalar &gt; &amp;op, int num_values, int num_indexes, int num_chars, const char reduct_obj_ext[], ReductTarget *reduct_obj)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SPMD_all_reduce</name>
      <anchorfile>namespaceRTOpPack.html</anchorfile>
      <anchor>abab748acdfc57f0a0c07f023112d2c2f</anchor>
      <arglist>(const Teuchos::Comm&lt; index_type &gt; *comm, const RTOpT&lt; Scalar &gt; &amp;op, const int num_cols, const ReductTarget *const i_reduct_objs[], ReductTarget *const reduct_objs[])</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SPMD_apply_op</name>
      <anchorfile>namespaceRTOpPack.html</anchorfile>
      <anchor>ad0271ea1eccddfbf6f8b0736e619d77a</anchor>
      <arglist>(const Teuchos::Comm&lt; index_type &gt; *comm, const RTOpT&lt; Scalar &gt; &amp;op, const int num_vecs, const ConstSubVectorView&lt; Scalar &gt; sub_vecs[], const int num_targ_vecs, const SubVectorView&lt; Scalar &gt; targ_sub_vecs[], ReductTarget *reduct_obj)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SPMD_apply_op</name>
      <anchorfile>namespaceRTOpPack.html</anchorfile>
      <anchor>ae5f130891cf4ef23ff7da293367069e6</anchor>
      <arglist>(const Teuchos::Comm&lt; index_type &gt; *comm, const RTOpT&lt; Scalar &gt; &amp;op, const int num_cols, const int num_multi_vecs, const ConstSubMultiVectorView&lt; Scalar &gt; sub_multi_vecs[], const int num_targ_multi_vecs, const SubMultiVectorView&lt; Scalar &gt; targ_sub_multi_vecs[], ReductTarget *const reduct_objs[])</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SPMD_apply_op</name>
      <anchorfile>namespaceRTOpPack.html</anchorfile>
      <anchor>ac1c270f15e624e9f492f38dfb8f57cb2</anchor>
      <arglist>(const Teuchos::Comm&lt; index_type &gt; *comm, const RTOpT&lt; Scalar &gt; &amp;op, const int num_cols, const int num_vecs, const ConstSubVectorView&lt; Scalar &gt; sub_vecs[], const int num_targ_vecs, const SubVectorView&lt; Scalar &gt; sub_targ_vecs[], ReductTarget *const reduct_objs[])</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; FancyOStream &gt; &amp;</type>
      <name>spmdApplyOpDumpOut</name>
      <anchorfile>namespaceRTOpPack.html</anchorfile>
      <anchor>a3c8fbe70e5cd7aa5c0c38a0486748b68</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>print</name>
      <anchorfile>namespaceRTOpPack.html</anchorfile>
      <anchor>a7b263b8b71b8ac53e5756a4ef7e03cb6</anchor>
      <arglist>(const ConstSubVectorView&lt; Scalar &gt; &amp;v, Teuchos::FancyOStream &amp;out_arg)</arglist>
    </member>
    <member kind="variable">
      <type>const int</type>
      <name>NUM_ETRANS_ARGS</name>
      <anchorfile>namespaceRTOpPack.html</anchorfile>
      <anchor>aa476f279820b4f1054fcc8ff7f24dbd5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const Teuchos::Tuple&lt; char, NUM_ETRANS_ARGS &gt;</type>
      <name>transpMap</name>
      <anchorfile>namespaceRTOpPack.html</anchorfile>
      <anchor>a0a534f2b7606752456764aa1e38ed86c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>RTOP_DEPRECATED bool</type>
      <name>show_spmd_apply_op_dump</name>
      <anchorfile>namespaceRTOpPack.html</anchorfile>
      <anchor>aeed3bfa798acb008d1b1bf5a5a210898</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="namespace">
    <name>Teuchos</name>
    <filename>namespaceTeuchos.html</filename>
    <class kind="class">Teuchos::Comm</class>
  </compound>
  <compound kind="page">
    <name>index</name>
    <title>RTOp Package Browser (Single Doxygen Collection)</title>
    <filename>index</filename>
  </compound>
</tagfile>
