<?xml version='1.0' encoding='UTF-8' standalone='yes' ?>
<tagfile>
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
  </compound>
  <compound kind="class">
    <name>RTOpPack::ROpGetSubVector</name>
    <filename>classRTOpPack_1_1ROpGetSubVector.html</filename>
    <templarg></templarg>
    <base>RTOpT&lt; Scalar &gt;</base>
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
  </compound>
  <compound kind="class">
    <name>RTOpPack::TOpAddScalar</name>
    <filename>classRTOpPack_1_1TOpAddScalar.html</filename>
    <templarg></templarg>
    <base>TOp_0_1_Base&lt; Scalar, TOpAddScalarEleWiseTransformation&lt; Scalar &gt; &gt;</base>
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
  </compound>
  <compound kind="class">
    <name>RTOpPack::TOpAssignScalar</name>
    <filename>classRTOpPack_1_1TOpAssignScalar.html</filename>
    <templarg></templarg>
    <base>TOp_0_1_Base&lt; Scalar, TOpAssignScalarEleWiseTransformation&lt; Scalar &gt; &gt;</base>
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
  </compound>
  <compound kind="class">
    <name>RTOpPack::TOpAXPY</name>
    <filename>classRTOpPack_1_1TOpAXPY.html</filename>
    <templarg></templarg>
    <base>TOp_1_1_Base&lt; Scalar, TOpAXPYEleWiseTransformation&lt; Scalar &gt; &gt;</base>
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
  </compound>
  <compound kind="class">
    <name>RTOpPack::TOpEleWiseConjProd</name>
    <filename>classRTOpPack_1_1TOpEleWiseConjProd.html</filename>
    <templarg></templarg>
    <base>TOp_2_1_Base&lt; Scalar, TOpEleWiseConjProdEleWiseTransformation&lt; Scalar &gt; &gt;</base>
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
  </compound>
  <compound kind="class">
    <name>RTOpPack::TOpEleWiseDivide</name>
    <filename>classRTOpPack_1_1TOpEleWiseDivide.html</filename>
    <templarg></templarg>
    <base>TOp_2_1_Base&lt; Scalar, TOpEleWiseDivideEleWiseTransformation&lt; Scalar &gt; &gt;</base>
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
  </compound>
  <compound kind="class">
    <name>RTOpPack::TOpEleWiseProd</name>
    <filename>classRTOpPack_1_1TOpEleWiseProd.html</filename>
    <templarg></templarg>
    <base>TOp_2_1_Base&lt; Scalar, TOpEleWiseProdEleWiseTransformation&lt; Scalar &gt; &gt;</base>
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
  </compound>
  <compound kind="class">
    <name>RTOpPack::TOpEleWiseProdUpdate</name>
    <filename>classRTOpPack_1_1TOpEleWiseProdUpdate.html</filename>
    <templarg></templarg>
    <base>TOp_1_1_Base&lt; Scalar, TOpEleWiseProdUpdateEleWiseTransformation&lt; Scalar &gt; &gt;</base>
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
  </compound>
  <compound kind="class">
    <name>RTOpPack::TOpLinearCombination</name>
    <filename>classRTOpPack_1_1TOpLinearCombination.html</filename>
    <templarg></templarg>
    <base>RTOpT&lt; Scalar &gt;</base>
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
    <base>RTOpT&lt; Scalar &gt;</base>
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
  </compound>
  <compound kind="class">
    <name>RTOpPack::TOpSetAssendingValues</name>
    <filename>classRTOpPack_1_1TOpSetAssendingValues.html</filename>
    <templarg></templarg>
    <base>TOp_0_1_CoordVariantBase&lt; Scalar, TOpSetAssendingValuesEleWiseTransformation&lt; Scalar &gt; &gt;</base>
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
  </compound>
  <compound kind="class">
    <name>RTOpPack::TOpSetSubVector</name>
    <filename>classRTOpPack_1_1TOpSetSubVector.html</filename>
    <templarg></templarg>
    <base>RTOpT&lt; Scalar &gt;</base>
    <member kind="typedef">
      <type>RTOpT&lt; Scalar &gt;::primitive_value_type</type>
      <name>primitive_value_type</name>
      <anchorfile>classRTOpPack_1_1TOpSetSubVector.html</anchorfile>
      <anchor>a9b980dff92e43a5d82b5a95e4e41c2bd</anchor>
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
  <compound kind="page">
    <name>index</name>
    <title>Collection of Concrete Vector Reduction/Transformation Operator Implementations</title>
    <filename>index</filename>
    <docanchor file="index" title="Software">RTOp_ops_lib_software_sec</docanchor>
    <docanchor file="index" title="Links">RTOp_ops_lib_links_sec</docanchor>
    <docanchor file="index" title="Software">RTOp_interface_software_sec</docanchor>
    <docanchor file="index" title="Links">RTOp_interface_links_sec</docanchor>
    <docanchor file="index" title="Software">RTOp_support_software_sec</docanchor>
    <docanchor file="index" title="Links">RTOp_support_links_sec</docanchor>
  </compound>
</tagfile>
