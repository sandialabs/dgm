<?xml version='1.0' encoding='UTF-8' standalone='yes' ?>
<tagfile>
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
    <member kind="function">
      <type>std::ostream &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>classRTOpPack_1_1ConstSubVectorView.html</anchorfile>
      <anchor>ac281c7853e26759d783e288b68267f28</anchor>
      <arglist>(std::ostream &amp;out, const ConstSubVectorView&lt; Scalar &gt; &amp;sv)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>RTOpPack::IncompatibleReductObj</name>
    <filename>classRTOpPack_1_1IncompatibleReductObj.html</filename>
  </compound>
  <compound kind="class">
    <name>RTOpPack::IncompatibleVecs</name>
    <filename>classRTOpPack_1_1IncompatibleVecs.html</filename>
  </compound>
  <compound kind="class">
    <name>RTOpPack::InvalidNumTargVecs</name>
    <filename>classRTOpPack_1_1InvalidNumTargVecs.html</filename>
  </compound>
  <compound kind="class">
    <name>RTOpPack::InvalidNumVecs</name>
    <filename>classRTOpPack_1_1InvalidNumVecs.html</filename>
  </compound>
  <compound kind="class">
    <name>RTOpPack::InvalidUsage</name>
    <filename>classRTOpPack_1_1InvalidUsage.html</filename>
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
  </compound>
  <compound kind="class">
    <name>RTOpPack::ReductTarget</name>
    <filename>classRTOpPack_1_1ReductTarget.html</filename>
  </compound>
  <compound kind="class">
    <name>RTOpPack::RTOpT</name>
    <filename>classRTOpPack_1_1RTOpT.html</filename>
    <templarg></templarg>
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
    <name>RTOpPack::UnknownError</name>
    <filename>classRTOpPack_1_1UnknownError.html</filename>
  </compound>
  <compound kind="page">
    <name>index</name>
    <title>Fundamental Vector Reduction/Transformation Operator (RTOp) Interfaces</title>
    <filename>index</filename>
    <docanchor file="index" title="Software">RTOp_interface_software_sec</docanchor>
    <docanchor file="index" title="Links">RTOp_interface_links_sec</docanchor>
  </compound>
</tagfile>
