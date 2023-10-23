<?xml version='1.0' encoding='UTF-8' standalone='yes' ?>
<tagfile>
  <compound kind="class">
    <name>NLPInterfacePack::NLP</name>
    <filename>classNLPInterfacePack_1_1NLP.html</filename>
    <class kind="class">NLPInterfacePack::NLP::IncompatibleType</class>
    <class kind="class">NLPInterfacePack::NLP::InvalidInitialization</class>
    <class kind="class">NLPInterfacePack::NLP::NoBounds</class>
    <class kind="class">NLPInterfacePack::NLP::UnInitialized</class>
    <class kind="struct">NLPInterfacePack::NLP::ZeroOrderInfo</class>
    <member kind="typedef">
      <type>Teuchos::RCP&lt; const VectorSpace &gt;</type>
      <name>vec_space_ptr_t</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a3535d4780d6a4eba0c25dd88809a624f</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Teuchos::RCP&lt; const OptionsFromStreamPack::OptionsFromStream &gt;</type>
      <name>options_ptr_t</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a8d3cfdcce6ee1e3c84d11ccfb1494ccb</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>const ZeroOrderInfo</type>
      <name>zero_order_info</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a63e6b374a7c56bc74bcbf2b3baa655fa</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const ZeroOrderInfo</type>
      <name>zero_order_info_breve</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a4aea1f22eed001b847e7be0250e5311c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" static="yes">
      <type>static value_type</type>
      <name>infinite_bound</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a1dc9592c25b467398848fbc6344a90e6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>assert_ref_set</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a737c913d13ca4e41a1ec25b371720bbc</anchor>
      <arglist>(T *p, std::string info) const </arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>NLP</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a8f9b7801c9c426d0e166935e2b02a5dc</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~NLP</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>afdee0ffed4b98701793d2d39762cc7fc</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>force_xinit_in_bounds</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a8b656613e166e28308d544a6f08a4075</anchor>
      <arglist>(bool force_xinit_in_bounds)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>force_xinit_in_bounds</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a93274bb52989b37e274fa291a1748f17</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>set_options</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>ab49bf8f5f809c9e9a1218951fe34f8d6</anchor>
      <arglist>(const options_ptr_t &amp;options)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const options_ptr_t &amp;</type>
      <name>get_options</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a6777671ee1d71404cd73b57c2560f2af</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>initialize</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a09ea72e2fa22e9d6e7ee52049cc3dab0</anchor>
      <arglist>(bool test_setup=false)</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>is_initialized</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a10e99e8ef26428d2f7425effdb73d2b6</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual size_type</type>
      <name>n</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a7f262b0c225619698b650a57298c0769</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual size_type</type>
      <name>m</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a675c11df23f6d5effdb184140f0477d7</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual vec_space_ptr_t</type>
      <name>space_x</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a8fbb005110abb78153b24eb0182107a9</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual vec_space_ptr_t</type>
      <name>space_c</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>aacdd590b3266a728db1fd468762f7e81</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual size_type</type>
      <name>num_bounded_x</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>ade9988baa1efa189c7569623e36f7b6b</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual const Vector &amp;</type>
      <name>xl</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a3f40753a3ede6aa55ef9ad3a2fd9fc07</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual const Vector &amp;</type>
      <name>xu</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a8f283df9dc4df9809688dbe6abb317bf</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual value_type</type>
      <name>max_var_bounds_viol</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a8bafa89c9b8be0dcbe2c27d366997faa</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual const Vector &amp;</type>
      <name>xinit</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>ad3fc1146cc2714d100d5a43602acd17b</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>get_init_lagrange_mult</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a332a401edad57dc3c06c38c20270917f</anchor>
      <arglist>(VectorMutable *lambda, VectorMutable *nu) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>set_f</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a980e823e4c910953086873ed61e34130</anchor>
      <arglist>(value_type *f)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual value_type *</type>
      <name>get_f</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a950451eaca0ea90ef61c7b0422b31fda</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual value_type &amp;</type>
      <name>f</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a738dd301d37fa7b79b30b42f2ea97d16</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const value_type &amp;</type>
      <name>f</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a22aa288b69b1e7f5b4e3ba100051cb1f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>set_c</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>ae7fada2f10f4c10640c462009462a748</anchor>
      <arglist>(VectorMutable *c)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual VectorMutable *</type>
      <name>get_c</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a9a19b89571ab8e44c0bfda3f9530b0c3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual VectorMutable &amp;</type>
      <name>c</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a5da9a90b212ce508fa2b608c4e6a6f80</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const Vector &amp;</type>
      <name>c</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a6aae6fadac3de67155a654fc04a15b34</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>unset_quantities</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>ac4679031ab89b596f5872f93e70a0372</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>scale_f</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a8757ed6ec67dc3a8a637972788d6e8ba</anchor>
      <arglist>(value_type scale_f)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual value_type</type>
      <name>scale_f</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a71150db7a0cc5d6b1b265338f7ce347e</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>calc_f</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>af1c8df0e7d52d8d0a6159136b5f2415f</anchor>
      <arglist>(const Vector &amp;x, bool newx=true) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>calc_c</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a90ef9d68922f0bdbc46ff1f283494e11</anchor>
      <arglist>(const Vector &amp;x, bool newx=true) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>report_final_solution</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a640bd431dc821cd06e0a4a69c7516be0</anchor>
      <arglist>(const Vector &amp;x, const Vector *lambda, const Vector *nu, bool is_optimal)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual size_type</type>
      <name>num_f_evals</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a684c04f1cbc049d9d626fa7604ee036a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual size_type</type>
      <name>num_c_evals</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a9ba6eabb94807b34d227ff897b1d2ee5</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual size_type</type>
      <name>ns</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a16396fbd0c43455a63d41f481ff09870</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual vec_space_ptr_t</type>
      <name>space_c_breve</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a206f4e541f586e09e43484907333b46a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual vec_space_ptr_t</type>
      <name>space_h_breve</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a17d23d84ad7c31e7ddd41b64eb2ffb67</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const Vector &amp;</type>
      <name>hl_breve</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a11181b99d07f5b799e1ae20b5cc19c71</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const Vector &amp;</type>
      <name>hu_breve</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>ac403365ee5b3f0628c967e56b63fbe75</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>set_c_breve</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a2d07b59dd6f28551ced5a8ee136d3e4b</anchor>
      <arglist>(VectorMutable *c_breve)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual VectorMutable *</type>
      <name>get_c_breve</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a81d6461bcaad765712d6f1a95e7199c3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual VectorMutable &amp;</type>
      <name>c_breve</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a283f37b55d108f6b2c452696e944cf77</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const Vector &amp;</type>
      <name>c_breve</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a7e68ab062a6a057237fa135f17d0ba0e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>set_h_breve</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>aff16ae4eacdcbdcfedf4bb1cbd1bb633</anchor>
      <arglist>(VectorMutable *h_breve)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual VectorMutable *</type>
      <name>get_h_breve</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a596fb18f90a7e367eeb060ea2393879a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual VectorMutable &amp;</type>
      <name>h_breve</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a781936f02d0c72927f570635cc1cc0fb</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const Vector &amp;</type>
      <name>h_breve</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a0f32bff188894d3d868e0b4db9e22eaf</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const Permutation &amp;</type>
      <name>P_var</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a75da12f5236771ce1b82a5009d841284</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const Permutation &amp;</type>
      <name>P_equ</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a0c9249575c0fae4a343ef0611c142388</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>calc_c_breve</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>ad37e807d366cbd918b0115eceed942a2</anchor>
      <arglist>(const Vector &amp;x, bool newx=true) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>calc_h_breve</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a333edd6f0f9fa0e48059a683530b47e1</anchor>
      <arglist>(const Vector &amp;x, bool newx=true) const </arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual void</type>
      <name>imp_calc_f</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>ad523d2c27f85684f95b4115e384f8efb</anchor>
      <arglist>(const Vector &amp;x, bool newx, const ZeroOrderInfo &amp;zero_order_info) const =0</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual void</type>
      <name>imp_calc_c</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a8da8481d95868220fd6eb0952d65c114</anchor>
      <arglist>(const Vector &amp;x, bool newx, const ZeroOrderInfo &amp;zero_order_info) const =0</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual void</type>
      <name>imp_calc_c_breve</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a6c493037871f5a6c14c7218221f06b23</anchor>
      <arglist>(const Vector &amp;x, bool newx, const ZeroOrderInfo &amp;zero_order_info_breve) const </arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual void</type>
      <name>imp_calc_h_breve</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a24ba3f8d9b03d47501b73a8c51c6ec53</anchor>
      <arglist>(const Vector &amp;x, bool newx, const ZeroOrderInfo &amp;zero_order_info_breve) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>NLPInterfacePack::NLP::IncompatibleType</name>
    <filename>classNLPInterfacePack_1_1NLP_1_1IncompatibleType.html</filename>
  </compound>
  <compound kind="class">
    <name>NLPInterfacePack::NLP::InvalidInitialization</name>
    <filename>classNLPInterfacePack_1_1NLP_1_1InvalidInitialization.html</filename>
  </compound>
  <compound kind="class">
    <name>NLPInterfacePack::NLP::NoBounds</name>
    <filename>classNLPInterfacePack_1_1NLP_1_1NoBounds.html</filename>
  </compound>
  <compound kind="class">
    <name>NLPInterfacePack::NLP::UnInitialized</name>
    <filename>classNLPInterfacePack_1_1NLP_1_1UnInitialized.html</filename>
  </compound>
  <compound kind="struct">
    <name>NLPInterfacePack::NLP::ZeroOrderInfo</name>
    <filename>structNLPInterfacePack_1_1NLP_1_1ZeroOrderInfo.html</filename>
    <member kind="function">
      <type></type>
      <name>ZeroOrderInfo</name>
      <anchorfile>structNLPInterfacePack_1_1NLP_1_1ZeroOrderInfo.html</anchorfile>
      <anchor>a608d5df1080ae38eab8428091f86b72b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ZeroOrderInfo</name>
      <anchorfile>structNLPInterfacePack_1_1NLP_1_1ZeroOrderInfo.html</anchorfile>
      <anchor>ae52a35d194dc010ba4f2c645d3c1042b</anchor>
      <arglist>(value_type *f_in, VectorMutable *c_in, VectorMutable *h_in)</arglist>
    </member>
    <member kind="variable">
      <type>value_type *</type>
      <name>f</name>
      <anchorfile>structNLPInterfacePack_1_1NLP_1_1ZeroOrderInfo.html</anchorfile>
      <anchor>aee1202e0d0b2f05e4af43c86a288ea41</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>VectorMutable *</type>
      <name>c</name>
      <anchorfile>structNLPInterfacePack_1_1NLP_1_1ZeroOrderInfo.html</anchorfile>
      <anchor>ac7d81ec64efb5d83694fde3ed8d74d28</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>VectorMutable *</type>
      <name>h</name>
      <anchorfile>structNLPInterfacePack_1_1NLP_1_1ZeroOrderInfo.html</anchorfile>
      <anchor>a89161da33e477d7892884871298be72f</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>NLPInterfacePack::NLPDirect</name>
    <filename>classNLPInterfacePack_1_1NLPDirect.html</filename>
    <base virtualness="virtual">NLPInterfacePack::NLPObjGrad</base>
    <member kind="typedef">
      <type>Teuchos::RCP&lt; const Teuchos::AbstractFactory&lt; MatrixOp &gt; &gt;</type>
      <name>mat_fcty_ptr_t</name>
      <anchorfile>classNLPInterfacePack_1_1NLPDirect.html</anchorfile>
      <anchor>aa66066e015798d7ce0d10d736bf5db20</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Teuchos::RCP&lt; const Teuchos::AbstractFactory&lt; MatrixSymOp &gt; &gt;</type>
      <name>mat_sym_fcty_ptr_t</name>
      <anchorfile>classNLPInterfacePack_1_1NLPDirect.html</anchorfile>
      <anchor>a8c54338c32a9e9a7b6b0aa2ee09d1512</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Teuchos::RCP&lt; const Teuchos::AbstractFactory&lt; MatrixSymOpNonsing &gt; &gt;</type>
      <name>mat_sym_nonsing_fcty_ptr_t</name>
      <anchorfile>classNLPInterfacePack_1_1NLPDirect.html</anchorfile>
      <anchor>aedb4b443905fb070620f00364770e1e3</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_factories</name>
      <anchorfile>classNLPInterfacePack_1_1NLPDirect.html</anchorfile>
      <anchor>ac6ef677d72590b670c164ca73c5f52d3</anchor>
      <arglist>(const mat_sym_fcty_ptr_t &amp;factory_transDtD, const mat_sym_nonsing_fcty_ptr_t &amp;factory_S)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>NLPObjGrad</name>
      <anchorfile>classNLPInterfacePack_1_1NLPObjGrad.html</anchorfile>
      <anchor>afb95be53fd1fdbb2186d37a9b5c3d9fb</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initialize</name>
      <anchorfile>classNLPInterfacePack_1_1NLPObjGrad.html</anchorfile>
      <anchor>a952d1fa6e9f309e734686f7c2fdcbdef</anchor>
      <arglist>(bool test_setup)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>supports_Gf</name>
      <anchorfile>classNLPInterfacePack_1_1NLPObjGrad.html</anchorfile>
      <anchor>a00fac73b679fbb079883596b63c67548</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>supports_Gf_prod</name>
      <anchorfile>classNLPInterfacePack_1_1NLPObjGrad.html</anchorfile>
      <anchor>a36f0d690e23e2e64900ab9f9de9bfcc5</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>set_Gf</name>
      <anchorfile>classNLPInterfacePack_1_1NLPObjGrad.html</anchorfile>
      <anchor>a09d8aa18d9322bdc826961a79773e33c</anchor>
      <arglist>(VectorMutable *Gf)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual VectorMutable *</type>
      <name>get_Gf</name>
      <anchorfile>classNLPInterfacePack_1_1NLPObjGrad.html</anchorfile>
      <anchor>a005dc9e7d8ead6fd375c7e30ceb7c0ad</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual VectorMutable &amp;</type>
      <name>Gf</name>
      <anchorfile>classNLPInterfacePack_1_1NLPObjGrad.html</anchorfile>
      <anchor>a41a1c61f724ce5f0eefd6441e0d035be</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const Vector &amp;</type>
      <name>Gf</name>
      <anchorfile>classNLPInterfacePack_1_1NLPObjGrad.html</anchorfile>
      <anchor>ae62e281e6dcdb21ff58582e68bb16423</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>unset_quantities</name>
      <anchorfile>classNLPInterfacePack_1_1NLPObjGrad.html</anchorfile>
      <anchor>acaa369276df73f29fec14fb80971f919</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>calc_Gf</name>
      <anchorfile>classNLPInterfacePack_1_1NLPObjGrad.html</anchorfile>
      <anchor>aaa7e6bdc0ac3244bc2c32ce256c0fa78</anchor>
      <arglist>(const Vector &amp;x, bool newx=true) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual value_type</type>
      <name>calc_Gf_prod</name>
      <anchorfile>classNLPInterfacePack_1_1NLPObjGrad.html</anchorfile>
      <anchor>a273cac12a3785f982c86f719c70ecf50</anchor>
      <arglist>(const Vector &amp;x, const Vector &amp;d, bool newx=true) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual size_type</type>
      <name>num_Gf_evals</name>
      <anchorfile>classNLPInterfacePack_1_1NLPObjGrad.html</anchorfile>
      <anchor>af04320a39fe4a80c5c4cf8783483275a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual size_type</type>
      <name>r</name>
      <anchorfile>classNLPInterfacePack_1_1NLPDirect.html</anchorfile>
      <anchor>aba228a256e21531438f71262fbe29dfb</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual Range1D</type>
      <name>var_dep</name>
      <anchorfile>classNLPInterfacePack_1_1NLPDirect.html</anchorfile>
      <anchor>ad30655cfa7bd49f804d55f90fb00d6f3</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual Range1D</type>
      <name>var_indep</name>
      <anchorfile>classNLPInterfacePack_1_1NLPDirect.html</anchorfile>
      <anchor>adcfc4410aef4aac7e6480ed74a4f0898</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual Range1D</type>
      <name>con_decomp</name>
      <anchorfile>classNLPInterfacePack_1_1NLPDirect.html</anchorfile>
      <anchor>ad26f2315a3d49b0ed31e7e5c0bb0a4fb</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual Range1D</type>
      <name>con_undecomp</name>
      <anchorfile>classNLPInterfacePack_1_1NLPDirect.html</anchorfile>
      <anchor>a0f891efce20ce1b948692b43386b9675</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const mat_fcty_ptr_t</type>
      <name>factory_GcU</name>
      <anchorfile>classNLPInterfacePack_1_1NLPDirect.html</anchorfile>
      <anchor>ac95208a58a34321f8ea994e78db346b8</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual const mat_fcty_ptr_t</type>
      <name>factory_D</name>
      <anchorfile>classNLPInterfacePack_1_1NLPDirect.html</anchorfile>
      <anchor>a9576dad6cfbec9ce5359d397fe88eb0b</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const mat_fcty_ptr_t</type>
      <name>factory_Uz</name>
      <anchorfile>classNLPInterfacePack_1_1NLPDirect.html</anchorfile>
      <anchor>aee099220d3328ddc8f6240ebed3e58d1</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const mat_fcty_ptr_t</type>
      <name>factory_GcUD</name>
      <anchorfile>classNLPInterfacePack_1_1NLPDirect.html</anchorfile>
      <anchor>a3ae26eef12618560d7247c9c3c0475d2</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const mat_sym_fcty_ptr_t</type>
      <name>factory_transDtD</name>
      <anchorfile>classNLPInterfacePack_1_1NLPDirect.html</anchorfile>
      <anchor>a3c7e22c8e44a9a29844aba6ecb270a05</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const mat_sym_nonsing_fcty_ptr_t</type>
      <name>factory_S</name>
      <anchorfile>classNLPInterfacePack_1_1NLPDirect.html</anchorfile>
      <anchor>ad69c146ef98acd0b1c530066c01fe7f5</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>calc_point</name>
      <anchorfile>classNLPInterfacePack_1_1NLPDirect.html</anchorfile>
      <anchor>a0b5c2efc32f0ab3e4858e80964beab4d</anchor>
      <arglist>(const Vector &amp;x, value_type *f, VectorMutable *c, bool recalc_c, VectorMutable *Gf, VectorMutable *py, VectorMutable *rGf, MatrixOp *GcU, MatrixOp *D, MatrixOp *Uz) const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>calc_semi_newton_step</name>
      <anchorfile>classNLPInterfacePack_1_1NLPDirect.html</anchorfile>
      <anchor>a10b97d4dae670e43b6d4e64a3ded0df4</anchor>
      <arglist>(const Vector &amp;x, VectorMutable *c, bool recalc_c, VectorMutable *py) const =0</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initialize</name>
      <anchorfile>classNLPInterfacePack_1_1NLPDirect.html</anchorfile>
      <anchor>aff3f22f1f085ce878c503ac859c2f488</anchor>
      <arglist>(bool test_setup)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static value_type</type>
      <name>infinite_bound</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a1dc9592c25b467398848fbc6344a90e6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>const ObjGradInfo</type>
      <name>obj_grad_info</name>
      <anchorfile>classNLPInterfacePack_1_1NLPObjGrad.html</anchorfile>
      <anchor>acdab01aba51adc311c3e1b200121889c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual void</type>
      <name>imp_calc_Gf</name>
      <anchorfile>classNLPInterfacePack_1_1NLPObjGrad.html</anchorfile>
      <anchor>aed8d78a5daea70c1cb70f65282db12cc</anchor>
      <arglist>(const Vector &amp;x, bool newx, const ObjGradInfo &amp;obj_grad_info) const =0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>NLPInterfacePack::NLPFirstOrder</name>
    <filename>classNLPInterfacePack_1_1NLPFirstOrder.html</filename>
    <base virtualness="virtual">NLPInterfacePack::NLPObjGrad</base>
    <class kind="struct">NLPInterfacePack::NLPFirstOrder::FirstOrderInfo</class>
    <member kind="typedef">
      <type>Teuchos::RCP&lt; const Teuchos::AbstractFactory&lt; MatrixOp &gt; &gt;</type>
      <name>mat_fcty_ptr_t</name>
      <anchorfile>classNLPInterfacePack_1_1NLPFirstOrder.html</anchorfile>
      <anchor>a02fc7fa49e2c4854a42435a0d67befd9</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Teuchos::RCP&lt; BasisSystem &gt;</type>
      <name>basis_sys_ptr_t</name>
      <anchorfile>classNLPInterfacePack_1_1NLPFirstOrder.html</anchorfile>
      <anchor>a8cd358a54058f52849d76e5f45a500a5</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" protection="protected">
      <type>const FirstOrderInfo</type>
      <name>first_order_info</name>
      <anchorfile>classNLPInterfacePack_1_1NLPFirstOrder.html</anchorfile>
      <anchor>aed5b41c031d94f81306ba07ccabe23bb</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>const ObjGradInfo</type>
      <name>obj_grad_info</name>
      <anchorfile>classNLPInterfacePack_1_1NLPObjGrad.html</anchorfile>
      <anchor>acdab01aba51adc311c3e1b200121889c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual void</type>
      <name>imp_calc_Gf</name>
      <anchorfile>classNLPInterfacePack_1_1NLPObjGrad.html</anchorfile>
      <anchor>aed8d78a5daea70c1cb70f65282db12cc</anchor>
      <arglist>(const Vector &amp;x, bool newx, const ObjGradInfo &amp;obj_grad_info) const =0</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>assert_ref_set</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a737c913d13ca4e41a1ec25b371720bbc</anchor>
      <arglist>(T *p, std::string info) const </arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual void</type>
      <name>imp_calc_f</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>ad523d2c27f85684f95b4115e384f8efb</anchor>
      <arglist>(const Vector &amp;x, bool newx, const ZeroOrderInfo &amp;zero_order_info) const =0</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual void</type>
      <name>imp_calc_c</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a8da8481d95868220fd6eb0952d65c114</anchor>
      <arglist>(const Vector &amp;x, bool newx, const ZeroOrderInfo &amp;zero_order_info) const =0</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual void</type>
      <name>imp_calc_c_breve</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a6c493037871f5a6c14c7218221f06b23</anchor>
      <arglist>(const Vector &amp;x, bool newx, const ZeroOrderInfo &amp;zero_order_info_breve) const </arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual void</type>
      <name>imp_calc_h_breve</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a24ba3f8d9b03d47501b73a8c51c6ec53</anchor>
      <arglist>(const Vector &amp;x, bool newx, const ZeroOrderInfo &amp;zero_order_info_breve) const </arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>NLPFirstOrder</name>
      <anchorfile>classNLPInterfacePack_1_1NLPFirstOrder.html</anchorfile>
      <anchor>afed7a912a2155a48a337a88daf829e60</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initialize</name>
      <anchorfile>classNLPInterfacePack_1_1NLPFirstOrder.html</anchorfile>
      <anchor>aaf30d8e4cede5228693aee2db01bd8b1</anchor>
      <arglist>(bool test_setup)</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual const mat_fcty_ptr_t</type>
      <name>factory_Gc</name>
      <anchorfile>classNLPInterfacePack_1_1NLPFirstOrder.html</anchorfile>
      <anchor>ae904cf141d5190812f9995fd8e645c0b</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const basis_sys_ptr_t</type>
      <name>basis_sys</name>
      <anchorfile>classNLPInterfacePack_1_1NLPFirstOrder.html</anchorfile>
      <anchor>ae6624f7932f132d4813025861f731794</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>set_Gc</name>
      <anchorfile>classNLPInterfacePack_1_1NLPFirstOrder.html</anchorfile>
      <anchor>aa766f589e0161c2f5a944eff827249a0</anchor>
      <arglist>(MatrixOp *Gc)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual MatrixOp *</type>
      <name>get_Gc</name>
      <anchorfile>classNLPInterfacePack_1_1NLPFirstOrder.html</anchorfile>
      <anchor>a66c3fd41bacab73468e7a98816379152</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual MatrixOp &amp;</type>
      <name>Gc</name>
      <anchorfile>classNLPInterfacePack_1_1NLPFirstOrder.html</anchorfile>
      <anchor>a59909f2dc634431042ae5d6c368d1d33</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const MatrixOp &amp;</type>
      <name>Gc</name>
      <anchorfile>classNLPInterfacePack_1_1NLPFirstOrder.html</anchorfile>
      <anchor>a17c21c0c70c13ad9963a224d84d1dab7</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>unset_quantities</name>
      <anchorfile>classNLPInterfacePack_1_1NLPFirstOrder.html</anchorfile>
      <anchor>adcca065b45335f90bede49862c0c5440</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>calc_Gc</name>
      <anchorfile>classNLPInterfacePack_1_1NLPFirstOrder.html</anchorfile>
      <anchor>aaacfb01f36b86c239a3743cca5f1b01a</anchor>
      <arglist>(const Vector &amp;x, bool newx=true) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual size_type</type>
      <name>num_Gc_evals</name>
      <anchorfile>classNLPInterfacePack_1_1NLPFirstOrder.html</anchorfile>
      <anchor>a792e27c3d6a7b0db6bec63aa5772d32b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual void</type>
      <name>imp_calc_Gc</name>
      <anchorfile>classNLPInterfacePack_1_1NLPFirstOrder.html</anchorfile>
      <anchor>ada7c5b81723ab5ebfe142ebf5fa44b7d</anchor>
      <arglist>(const Vector &amp;x, bool newx, const FirstOrderInfo &amp;first_order_info) const =0</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>NLPObjGrad</name>
      <anchorfile>classNLPInterfacePack_1_1NLPObjGrad.html</anchorfile>
      <anchor>afb95be53fd1fdbb2186d37a9b5c3d9fb</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initialize</name>
      <anchorfile>classNLPInterfacePack_1_1NLPObjGrad.html</anchorfile>
      <anchor>a952d1fa6e9f309e734686f7c2fdcbdef</anchor>
      <arglist>(bool test_setup)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>supports_Gf</name>
      <anchorfile>classNLPInterfacePack_1_1NLPObjGrad.html</anchorfile>
      <anchor>a00fac73b679fbb079883596b63c67548</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>supports_Gf_prod</name>
      <anchorfile>classNLPInterfacePack_1_1NLPObjGrad.html</anchorfile>
      <anchor>a36f0d690e23e2e64900ab9f9de9bfcc5</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>set_Gf</name>
      <anchorfile>classNLPInterfacePack_1_1NLPObjGrad.html</anchorfile>
      <anchor>a09d8aa18d9322bdc826961a79773e33c</anchor>
      <arglist>(VectorMutable *Gf)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual VectorMutable *</type>
      <name>get_Gf</name>
      <anchorfile>classNLPInterfacePack_1_1NLPObjGrad.html</anchorfile>
      <anchor>a005dc9e7d8ead6fd375c7e30ceb7c0ad</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual VectorMutable &amp;</type>
      <name>Gf</name>
      <anchorfile>classNLPInterfacePack_1_1NLPObjGrad.html</anchorfile>
      <anchor>a41a1c61f724ce5f0eefd6441e0d035be</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const Vector &amp;</type>
      <name>Gf</name>
      <anchorfile>classNLPInterfacePack_1_1NLPObjGrad.html</anchorfile>
      <anchor>ae62e281e6dcdb21ff58582e68bb16423</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>unset_quantities</name>
      <anchorfile>classNLPInterfacePack_1_1NLPObjGrad.html</anchorfile>
      <anchor>acaa369276df73f29fec14fb80971f919</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>calc_Gf</name>
      <anchorfile>classNLPInterfacePack_1_1NLPObjGrad.html</anchorfile>
      <anchor>aaa7e6bdc0ac3244bc2c32ce256c0fa78</anchor>
      <arglist>(const Vector &amp;x, bool newx=true) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual value_type</type>
      <name>calc_Gf_prod</name>
      <anchorfile>classNLPInterfacePack_1_1NLPObjGrad.html</anchorfile>
      <anchor>a273cac12a3785f982c86f719c70ecf50</anchor>
      <arglist>(const Vector &amp;x, const Vector &amp;d, bool newx=true) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual size_type</type>
      <name>num_Gf_evals</name>
      <anchorfile>classNLPInterfacePack_1_1NLPObjGrad.html</anchorfile>
      <anchor>af04320a39fe4a80c5c4cf8783483275a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const ZeroOrderInfo</type>
      <name>zero_order_info</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a63e6b374a7c56bc74bcbf2b3baa655fa</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const ZeroOrderInfo</type>
      <name>zero_order_info_breve</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a4aea1f22eed001b847e7be0250e5311c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>NLP</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a8f9b7801c9c426d0e166935e2b02a5dc</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~NLP</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>afdee0ffed4b98701793d2d39762cc7fc</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>force_xinit_in_bounds</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a8b656613e166e28308d544a6f08a4075</anchor>
      <arglist>(bool force_xinit_in_bounds)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>force_xinit_in_bounds</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a93274bb52989b37e274fa291a1748f17</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>set_options</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>ab49bf8f5f809c9e9a1218951fe34f8d6</anchor>
      <arglist>(const options_ptr_t &amp;options)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const options_ptr_t &amp;</type>
      <name>get_options</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a6777671ee1d71404cd73b57c2560f2af</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>is_initialized</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a10e99e8ef26428d2f7425effdb73d2b6</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual size_type</type>
      <name>n</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a7f262b0c225619698b650a57298c0769</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual size_type</type>
      <name>m</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a675c11df23f6d5effdb184140f0477d7</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual vec_space_ptr_t</type>
      <name>space_x</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a8fbb005110abb78153b24eb0182107a9</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual vec_space_ptr_t</type>
      <name>space_c</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>aacdd590b3266a728db1fd468762f7e81</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual size_type</type>
      <name>num_bounded_x</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>ade9988baa1efa189c7569623e36f7b6b</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual const Vector &amp;</type>
      <name>xl</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a3f40753a3ede6aa55ef9ad3a2fd9fc07</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual const Vector &amp;</type>
      <name>xu</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a8f283df9dc4df9809688dbe6abb317bf</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual value_type</type>
      <name>max_var_bounds_viol</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a8bafa89c9b8be0dcbe2c27d366997faa</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual const Vector &amp;</type>
      <name>xinit</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>ad3fc1146cc2714d100d5a43602acd17b</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>get_init_lagrange_mult</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a332a401edad57dc3c06c38c20270917f</anchor>
      <arglist>(VectorMutable *lambda, VectorMutable *nu) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>set_f</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a980e823e4c910953086873ed61e34130</anchor>
      <arglist>(value_type *f)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual value_type *</type>
      <name>get_f</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a950451eaca0ea90ef61c7b0422b31fda</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual value_type &amp;</type>
      <name>f</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a738dd301d37fa7b79b30b42f2ea97d16</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const value_type &amp;</type>
      <name>f</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a22aa288b69b1e7f5b4e3ba100051cb1f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>set_c</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>ae7fada2f10f4c10640c462009462a748</anchor>
      <arglist>(VectorMutable *c)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual VectorMutable *</type>
      <name>get_c</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a9a19b89571ab8e44c0bfda3f9530b0c3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual VectorMutable &amp;</type>
      <name>c</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a5da9a90b212ce508fa2b608c4e6a6f80</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const Vector &amp;</type>
      <name>c</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a6aae6fadac3de67155a654fc04a15b34</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>scale_f</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a8757ed6ec67dc3a8a637972788d6e8ba</anchor>
      <arglist>(value_type scale_f)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual value_type</type>
      <name>scale_f</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a71150db7a0cc5d6b1b265338f7ce347e</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>calc_f</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>af1c8df0e7d52d8d0a6159136b5f2415f</anchor>
      <arglist>(const Vector &amp;x, bool newx=true) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>calc_c</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a90ef9d68922f0bdbc46ff1f283494e11</anchor>
      <arglist>(const Vector &amp;x, bool newx=true) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>report_final_solution</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a640bd431dc821cd06e0a4a69c7516be0</anchor>
      <arglist>(const Vector &amp;x, const Vector *lambda, const Vector *nu, bool is_optimal)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual size_type</type>
      <name>num_f_evals</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a684c04f1cbc049d9d626fa7604ee036a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual size_type</type>
      <name>num_c_evals</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a9ba6eabb94807b34d227ff897b1d2ee5</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual size_type</type>
      <name>ns</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a16396fbd0c43455a63d41f481ff09870</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual vec_space_ptr_t</type>
      <name>space_c_breve</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a206f4e541f586e09e43484907333b46a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual vec_space_ptr_t</type>
      <name>space_h_breve</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a17d23d84ad7c31e7ddd41b64eb2ffb67</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const Vector &amp;</type>
      <name>hl_breve</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a11181b99d07f5b799e1ae20b5cc19c71</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const Vector &amp;</type>
      <name>hu_breve</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>ac403365ee5b3f0628c967e56b63fbe75</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>set_c_breve</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a2d07b59dd6f28551ced5a8ee136d3e4b</anchor>
      <arglist>(VectorMutable *c_breve)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual VectorMutable *</type>
      <name>get_c_breve</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a81d6461bcaad765712d6f1a95e7199c3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual VectorMutable &amp;</type>
      <name>c_breve</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a283f37b55d108f6b2c452696e944cf77</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const Vector &amp;</type>
      <name>c_breve</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a7e68ab062a6a057237fa135f17d0ba0e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>set_h_breve</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>aff16ae4eacdcbdcfedf4bb1cbd1bb633</anchor>
      <arglist>(VectorMutable *h_breve)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual VectorMutable *</type>
      <name>get_h_breve</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a596fb18f90a7e367eeb060ea2393879a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual VectorMutable &amp;</type>
      <name>h_breve</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a781936f02d0c72927f570635cc1cc0fb</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const Vector &amp;</type>
      <name>h_breve</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a0f32bff188894d3d868e0b4db9e22eaf</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const Permutation &amp;</type>
      <name>P_var</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a75da12f5236771ce1b82a5009d841284</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const Permutation &amp;</type>
      <name>P_equ</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a0c9249575c0fae4a343ef0611c142388</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>calc_c_breve</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>ad37e807d366cbd918b0115eceed942a2</anchor>
      <arglist>(const Vector &amp;x, bool newx=true) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>calc_h_breve</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a333edd6f0f9fa0e48059a683530b47e1</anchor>
      <arglist>(const Vector &amp;x, bool newx=true) const </arglist>
    </member>
    <member kind="function" static="yes">
      <type>static value_type</type>
      <name>infinite_bound</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a1dc9592c25b467398848fbc6344a90e6</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>NLPInterfacePack::NLPFirstOrder::FirstOrderInfo</name>
    <filename>structNLPInterfacePack_1_1NLPFirstOrder_1_1FirstOrderInfo.html</filename>
    <member kind="function">
      <type></type>
      <name>FirstOrderInfo</name>
      <anchorfile>structNLPInterfacePack_1_1NLPFirstOrder_1_1FirstOrderInfo.html</anchorfile>
      <anchor>a21224af4cb6460f7df6aea15e42b7e73</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>FirstOrderInfo</name>
      <anchorfile>structNLPInterfacePack_1_1NLPFirstOrder_1_1FirstOrderInfo.html</anchorfile>
      <anchor>adb7b53d202bf1ad5ac0cfc0257fae902</anchor>
      <arglist>(MatrixOp *Gc_in, const ObjGradInfo &amp;obj_grad)</arglist>
    </member>
    <member kind="variable">
      <type>MatrixOp *</type>
      <name>Gc</name>
      <anchorfile>structNLPInterfacePack_1_1NLPFirstOrder_1_1FirstOrderInfo.html</anchorfile>
      <anchor>a6789edea5468346bc048ffa49ba7ca5d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>VectorMutable *</type>
      <name>Gf</name>
      <anchorfile>structNLPInterfacePack_1_1NLPFirstOrder_1_1FirstOrderInfo.html</anchorfile>
      <anchor>aa99224b5fed62d934c07398eecc9cde5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>value_type *</type>
      <name>f</name>
      <anchorfile>structNLPInterfacePack_1_1NLPFirstOrder_1_1FirstOrderInfo.html</anchorfile>
      <anchor>a8b9b139acfcc60b5bea0a6037ac6182c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>VectorMutable *</type>
      <name>c</name>
      <anchorfile>structNLPInterfacePack_1_1NLPFirstOrder_1_1FirstOrderInfo.html</anchorfile>
      <anchor>a2d53ade6337a0be9eb10413f3e77a36b</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>NLPInterfacePack::NLPObjGrad</name>
    <filename>classNLPInterfacePack_1_1NLPObjGrad.html</filename>
    <base virtualness="virtual">NLPInterfacePack::NLP</base>
    <class kind="struct">NLPInterfacePack::NLPObjGrad::ObjGradInfo</class>
    <member kind="function" protection="protected">
      <type>const ObjGradInfo</type>
      <name>obj_grad_info</name>
      <anchorfile>classNLPInterfacePack_1_1NLPObjGrad.html</anchorfile>
      <anchor>acdab01aba51adc311c3e1b200121889c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>assert_ref_set</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a737c913d13ca4e41a1ec25b371720bbc</anchor>
      <arglist>(T *p, std::string info) const </arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual void</type>
      <name>imp_calc_f</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>ad523d2c27f85684f95b4115e384f8efb</anchor>
      <arglist>(const Vector &amp;x, bool newx, const ZeroOrderInfo &amp;zero_order_info) const =0</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual void</type>
      <name>imp_calc_c</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a8da8481d95868220fd6eb0952d65c114</anchor>
      <arglist>(const Vector &amp;x, bool newx, const ZeroOrderInfo &amp;zero_order_info) const =0</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual void</type>
      <name>imp_calc_c_breve</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a6c493037871f5a6c14c7218221f06b23</anchor>
      <arglist>(const Vector &amp;x, bool newx, const ZeroOrderInfo &amp;zero_order_info_breve) const </arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual void</type>
      <name>imp_calc_h_breve</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a24ba3f8d9b03d47501b73a8c51c6ec53</anchor>
      <arglist>(const Vector &amp;x, bool newx, const ZeroOrderInfo &amp;zero_order_info_breve) const </arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>NLPObjGrad</name>
      <anchorfile>classNLPInterfacePack_1_1NLPObjGrad.html</anchorfile>
      <anchor>afb95be53fd1fdbb2186d37a9b5c3d9fb</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initialize</name>
      <anchorfile>classNLPInterfacePack_1_1NLPObjGrad.html</anchorfile>
      <anchor>a952d1fa6e9f309e734686f7c2fdcbdef</anchor>
      <arglist>(bool test_setup)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>supports_Gf</name>
      <anchorfile>classNLPInterfacePack_1_1NLPObjGrad.html</anchorfile>
      <anchor>a00fac73b679fbb079883596b63c67548</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>supports_Gf_prod</name>
      <anchorfile>classNLPInterfacePack_1_1NLPObjGrad.html</anchorfile>
      <anchor>a36f0d690e23e2e64900ab9f9de9bfcc5</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>set_Gf</name>
      <anchorfile>classNLPInterfacePack_1_1NLPObjGrad.html</anchorfile>
      <anchor>a09d8aa18d9322bdc826961a79773e33c</anchor>
      <arglist>(VectorMutable *Gf)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual VectorMutable *</type>
      <name>get_Gf</name>
      <anchorfile>classNLPInterfacePack_1_1NLPObjGrad.html</anchorfile>
      <anchor>a005dc9e7d8ead6fd375c7e30ceb7c0ad</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual VectorMutable &amp;</type>
      <name>Gf</name>
      <anchorfile>classNLPInterfacePack_1_1NLPObjGrad.html</anchorfile>
      <anchor>a41a1c61f724ce5f0eefd6441e0d035be</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const Vector &amp;</type>
      <name>Gf</name>
      <anchorfile>classNLPInterfacePack_1_1NLPObjGrad.html</anchorfile>
      <anchor>ae62e281e6dcdb21ff58582e68bb16423</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>unset_quantities</name>
      <anchorfile>classNLPInterfacePack_1_1NLPObjGrad.html</anchorfile>
      <anchor>acaa369276df73f29fec14fb80971f919</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>calc_Gf</name>
      <anchorfile>classNLPInterfacePack_1_1NLPObjGrad.html</anchorfile>
      <anchor>aaa7e6bdc0ac3244bc2c32ce256c0fa78</anchor>
      <arglist>(const Vector &amp;x, bool newx=true) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual value_type</type>
      <name>calc_Gf_prod</name>
      <anchorfile>classNLPInterfacePack_1_1NLPObjGrad.html</anchorfile>
      <anchor>a273cac12a3785f982c86f719c70ecf50</anchor>
      <arglist>(const Vector &amp;x, const Vector &amp;d, bool newx=true) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual size_type</type>
      <name>num_Gf_evals</name>
      <anchorfile>classNLPInterfacePack_1_1NLPObjGrad.html</anchorfile>
      <anchor>af04320a39fe4a80c5c4cf8783483275a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual void</type>
      <name>imp_calc_Gf</name>
      <anchorfile>classNLPInterfacePack_1_1NLPObjGrad.html</anchorfile>
      <anchor>aed8d78a5daea70c1cb70f65282db12cc</anchor>
      <arglist>(const Vector &amp;x, bool newx, const ObjGradInfo &amp;obj_grad_info) const =0</arglist>
    </member>
    <member kind="typedef">
      <type>Teuchos::RCP&lt; const VectorSpace &gt;</type>
      <name>vec_space_ptr_t</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a3535d4780d6a4eba0c25dd88809a624f</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Teuchos::RCP&lt; const OptionsFromStreamPack::OptionsFromStream &gt;</type>
      <name>options_ptr_t</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a8d3cfdcce6ee1e3c84d11ccfb1494ccb</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>const ZeroOrderInfo</type>
      <name>zero_order_info</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a63e6b374a7c56bc74bcbf2b3baa655fa</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const ZeroOrderInfo</type>
      <name>zero_order_info_breve</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a4aea1f22eed001b847e7be0250e5311c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>NLP</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a8f9b7801c9c426d0e166935e2b02a5dc</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~NLP</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>afdee0ffed4b98701793d2d39762cc7fc</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>force_xinit_in_bounds</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a8b656613e166e28308d544a6f08a4075</anchor>
      <arglist>(bool force_xinit_in_bounds)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>force_xinit_in_bounds</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a93274bb52989b37e274fa291a1748f17</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>set_options</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>ab49bf8f5f809c9e9a1218951fe34f8d6</anchor>
      <arglist>(const options_ptr_t &amp;options)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const options_ptr_t &amp;</type>
      <name>get_options</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a6777671ee1d71404cd73b57c2560f2af</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>is_initialized</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a10e99e8ef26428d2f7425effdb73d2b6</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual size_type</type>
      <name>n</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a7f262b0c225619698b650a57298c0769</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual size_type</type>
      <name>m</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a675c11df23f6d5effdb184140f0477d7</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual vec_space_ptr_t</type>
      <name>space_x</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a8fbb005110abb78153b24eb0182107a9</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual vec_space_ptr_t</type>
      <name>space_c</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>aacdd590b3266a728db1fd468762f7e81</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual size_type</type>
      <name>num_bounded_x</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>ade9988baa1efa189c7569623e36f7b6b</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual const Vector &amp;</type>
      <name>xl</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a3f40753a3ede6aa55ef9ad3a2fd9fc07</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual const Vector &amp;</type>
      <name>xu</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a8f283df9dc4df9809688dbe6abb317bf</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual value_type</type>
      <name>max_var_bounds_viol</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a8bafa89c9b8be0dcbe2c27d366997faa</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual const Vector &amp;</type>
      <name>xinit</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>ad3fc1146cc2714d100d5a43602acd17b</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>get_init_lagrange_mult</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a332a401edad57dc3c06c38c20270917f</anchor>
      <arglist>(VectorMutable *lambda, VectorMutable *nu) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>set_f</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a980e823e4c910953086873ed61e34130</anchor>
      <arglist>(value_type *f)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual value_type *</type>
      <name>get_f</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a950451eaca0ea90ef61c7b0422b31fda</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual value_type &amp;</type>
      <name>f</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a738dd301d37fa7b79b30b42f2ea97d16</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const value_type &amp;</type>
      <name>f</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a22aa288b69b1e7f5b4e3ba100051cb1f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>set_c</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>ae7fada2f10f4c10640c462009462a748</anchor>
      <arglist>(VectorMutable *c)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual VectorMutable *</type>
      <name>get_c</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a9a19b89571ab8e44c0bfda3f9530b0c3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual VectorMutable &amp;</type>
      <name>c</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a5da9a90b212ce508fa2b608c4e6a6f80</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const Vector &amp;</type>
      <name>c</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a6aae6fadac3de67155a654fc04a15b34</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>scale_f</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a8757ed6ec67dc3a8a637972788d6e8ba</anchor>
      <arglist>(value_type scale_f)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual value_type</type>
      <name>scale_f</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a71150db7a0cc5d6b1b265338f7ce347e</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>calc_f</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>af1c8df0e7d52d8d0a6159136b5f2415f</anchor>
      <arglist>(const Vector &amp;x, bool newx=true) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>calc_c</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a90ef9d68922f0bdbc46ff1f283494e11</anchor>
      <arglist>(const Vector &amp;x, bool newx=true) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>report_final_solution</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a640bd431dc821cd06e0a4a69c7516be0</anchor>
      <arglist>(const Vector &amp;x, const Vector *lambda, const Vector *nu, bool is_optimal)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual size_type</type>
      <name>num_f_evals</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a684c04f1cbc049d9d626fa7604ee036a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual size_type</type>
      <name>num_c_evals</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a9ba6eabb94807b34d227ff897b1d2ee5</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual size_type</type>
      <name>ns</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a16396fbd0c43455a63d41f481ff09870</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual vec_space_ptr_t</type>
      <name>space_c_breve</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a206f4e541f586e09e43484907333b46a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual vec_space_ptr_t</type>
      <name>space_h_breve</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a17d23d84ad7c31e7ddd41b64eb2ffb67</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const Vector &amp;</type>
      <name>hl_breve</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a11181b99d07f5b799e1ae20b5cc19c71</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const Vector &amp;</type>
      <name>hu_breve</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>ac403365ee5b3f0628c967e56b63fbe75</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>set_c_breve</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a2d07b59dd6f28551ced5a8ee136d3e4b</anchor>
      <arglist>(VectorMutable *c_breve)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual VectorMutable *</type>
      <name>get_c_breve</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a81d6461bcaad765712d6f1a95e7199c3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual VectorMutable &amp;</type>
      <name>c_breve</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a283f37b55d108f6b2c452696e944cf77</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const Vector &amp;</type>
      <name>c_breve</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a7e68ab062a6a057237fa135f17d0ba0e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>set_h_breve</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>aff16ae4eacdcbdcfedf4bb1cbd1bb633</anchor>
      <arglist>(VectorMutable *h_breve)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual VectorMutable *</type>
      <name>get_h_breve</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a596fb18f90a7e367eeb060ea2393879a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual VectorMutable &amp;</type>
      <name>h_breve</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a781936f02d0c72927f570635cc1cc0fb</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const Vector &amp;</type>
      <name>h_breve</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a0f32bff188894d3d868e0b4db9e22eaf</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const Permutation &amp;</type>
      <name>P_var</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a75da12f5236771ce1b82a5009d841284</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const Permutation &amp;</type>
      <name>P_equ</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a0c9249575c0fae4a343ef0611c142388</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>calc_c_breve</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>ad37e807d366cbd918b0115eceed942a2</anchor>
      <arglist>(const Vector &amp;x, bool newx=true) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>calc_h_breve</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a333edd6f0f9fa0e48059a683530b47e1</anchor>
      <arglist>(const Vector &amp;x, bool newx=true) const </arglist>
    </member>
    <member kind="function" static="yes">
      <type>static value_type</type>
      <name>infinite_bound</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a1dc9592c25b467398848fbc6344a90e6</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>NLPInterfacePack::NLPObjGrad::ObjGradInfo</name>
    <filename>structNLPInterfacePack_1_1NLPObjGrad_1_1ObjGradInfo.html</filename>
    <member kind="function">
      <type></type>
      <name>ObjGradInfo</name>
      <anchorfile>structNLPInterfacePack_1_1NLPObjGrad_1_1ObjGradInfo.html</anchorfile>
      <anchor>a7a0eea810ea6461e8c99ceb8bce9f226</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ObjGradInfo</name>
      <anchorfile>structNLPInterfacePack_1_1NLPObjGrad_1_1ObjGradInfo.html</anchorfile>
      <anchor>ae203d1befa29144acf0627f89afbef4b</anchor>
      <arglist>(VectorMutable *Gf_in, const ZeroOrderInfo &amp;first_order_info_in)</arglist>
    </member>
    <member kind="variable">
      <type>VectorMutable *</type>
      <name>Gf</name>
      <anchorfile>structNLPInterfacePack_1_1NLPObjGrad_1_1ObjGradInfo.html</anchorfile>
      <anchor>a59e4377f6e9f59ea32ffaacdf9d84a19</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>value_type *</type>
      <name>f</name>
      <anchorfile>structNLPInterfacePack_1_1NLPObjGrad_1_1ObjGradInfo.html</anchorfile>
      <anchor>aa4d6f19878f5f4c181b6356f67ad27a7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>VectorMutable *</type>
      <name>c</name>
      <anchorfile>structNLPInterfacePack_1_1NLPObjGrad_1_1ObjGradInfo.html</anchorfile>
      <anchor>a063e1c1c556a97ed06868b78569bff64</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>NLPInterfacePack::NLPSecondOrder</name>
    <filename>classNLPInterfacePack_1_1NLPSecondOrder.html</filename>
    <base virtualness="virtual">NLPInterfacePack::NLPFirstOrder</base>
    <class kind="struct">NLPInterfacePack::NLPSecondOrder::SecondOrderInfo</class>
    <member kind="typedef">
      <type>Teuchos::RCP&lt; const Teuchos::AbstractFactory&lt; MatrixSymOp &gt; &gt;</type>
      <name>mat_sym_fcty_ptr_t</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSecondOrder.html</anchorfile>
      <anchor>a3ded7d15ca8c5720b155cac4c1ad35b6</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Teuchos::RCP&lt; const Teuchos::AbstractFactory&lt; MatrixOp &gt; &gt;</type>
      <name>mat_fcty_ptr_t</name>
      <anchorfile>classNLPInterfacePack_1_1NLPFirstOrder.html</anchorfile>
      <anchor>a02fc7fa49e2c4854a42435a0d67befd9</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Teuchos::RCP&lt; BasisSystem &gt;</type>
      <name>basis_sys_ptr_t</name>
      <anchorfile>classNLPInterfacePack_1_1NLPFirstOrder.html</anchorfile>
      <anchor>a8cd358a54058f52849d76e5f45a500a5</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" protection="protected">
      <type>const SecondOrderInfo</type>
      <name>second_order_info</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSecondOrder.html</anchorfile>
      <anchor>a091f7016624691c43284f76780e25159</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>const FirstOrderInfo</type>
      <name>first_order_info</name>
      <anchorfile>classNLPInterfacePack_1_1NLPFirstOrder.html</anchorfile>
      <anchor>aed5b41c031d94f81306ba07ccabe23bb</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual void</type>
      <name>imp_calc_Gc</name>
      <anchorfile>classNLPInterfacePack_1_1NLPFirstOrder.html</anchorfile>
      <anchor>ada7c5b81723ab5ebfe142ebf5fa44b7d</anchor>
      <arglist>(const Vector &amp;x, bool newx, const FirstOrderInfo &amp;first_order_info) const =0</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>const ObjGradInfo</type>
      <name>obj_grad_info</name>
      <anchorfile>classNLPInterfacePack_1_1NLPObjGrad.html</anchorfile>
      <anchor>acdab01aba51adc311c3e1b200121889c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual void</type>
      <name>imp_calc_Gf</name>
      <anchorfile>classNLPInterfacePack_1_1NLPObjGrad.html</anchorfile>
      <anchor>aed8d78a5daea70c1cb70f65282db12cc</anchor>
      <arglist>(const Vector &amp;x, bool newx, const ObjGradInfo &amp;obj_grad_info) const =0</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>assert_ref_set</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a737c913d13ca4e41a1ec25b371720bbc</anchor>
      <arglist>(T *p, std::string info) const </arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual void</type>
      <name>imp_calc_f</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>ad523d2c27f85684f95b4115e384f8efb</anchor>
      <arglist>(const Vector &amp;x, bool newx, const ZeroOrderInfo &amp;zero_order_info) const =0</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual void</type>
      <name>imp_calc_c</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a8da8481d95868220fd6eb0952d65c114</anchor>
      <arglist>(const Vector &amp;x, bool newx, const ZeroOrderInfo &amp;zero_order_info) const =0</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual void</type>
      <name>imp_calc_c_breve</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a6c493037871f5a6c14c7218221f06b23</anchor>
      <arglist>(const Vector &amp;x, bool newx, const ZeroOrderInfo &amp;zero_order_info_breve) const </arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual void</type>
      <name>imp_calc_h_breve</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a24ba3f8d9b03d47501b73a8c51c6ec53</anchor>
      <arglist>(const Vector &amp;x, bool newx, const ZeroOrderInfo &amp;zero_order_info_breve) const </arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>NLPSecondOrder</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSecondOrder.html</anchorfile>
      <anchor>ae3aa59d595ec4c5064204791361925cc</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initialize</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSecondOrder.html</anchorfile>
      <anchor>a27cdc8765f871e69602799ce889672b6</anchor>
      <arglist>(bool test_setup)</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual const mat_sym_fcty_ptr_t</type>
      <name>factory_HL</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSecondOrder.html</anchorfile>
      <anchor>a5bc0aa2b0318dec967888334ceef1c4c</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>set_HL</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSecondOrder.html</anchorfile>
      <anchor>a9c22e5e31e234f42bcc545c75d5563ef</anchor>
      <arglist>(MatrixSymOp *HL)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual MatrixSymOp *</type>
      <name>get_HL</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSecondOrder.html</anchorfile>
      <anchor>a4dac18a42a1a2af3b1af2288cffff69d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual MatrixSymOp &amp;</type>
      <name>HL</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSecondOrder.html</anchorfile>
      <anchor>a3d893fa5fb752ca2a5f714036477ab77</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const MatrixSymOp &amp;</type>
      <name>HL</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSecondOrder.html</anchorfile>
      <anchor>a5df4a981aac69d4378280ec0b0e780a9</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>unset_quantities</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSecondOrder.html</anchorfile>
      <anchor>a3f78614c93b7f6e33f4bcbbe7a4caa91</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>calc_HL</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSecondOrder.html</anchorfile>
      <anchor>ab83f6deb59a4ef6be3ada550f254e84a</anchor>
      <arglist>(const Vector &amp;x, const Vector *lambda, bool newpoint=true) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual size_type</type>
      <name>num_HL_evals</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSecondOrder.html</anchorfile>
      <anchor>aa9389fbe8bf5327739533dde6f629391</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual void</type>
      <name>imp_calc_HL</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSecondOrder.html</anchorfile>
      <anchor>afb0fd266bae0318b32b2877d8bd318cf</anchor>
      <arglist>(const Vector &amp;x, const Vector *lambda, bool newpoint, const SecondOrderInfo &amp;second_order_info) const =0</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>NLPFirstOrder</name>
      <anchorfile>classNLPInterfacePack_1_1NLPFirstOrder.html</anchorfile>
      <anchor>afed7a912a2155a48a337a88daf829e60</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual const mat_fcty_ptr_t</type>
      <name>factory_Gc</name>
      <anchorfile>classNLPInterfacePack_1_1NLPFirstOrder.html</anchorfile>
      <anchor>ae904cf141d5190812f9995fd8e645c0b</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const basis_sys_ptr_t</type>
      <name>basis_sys</name>
      <anchorfile>classNLPInterfacePack_1_1NLPFirstOrder.html</anchorfile>
      <anchor>ae6624f7932f132d4813025861f731794</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>set_Gc</name>
      <anchorfile>classNLPInterfacePack_1_1NLPFirstOrder.html</anchorfile>
      <anchor>aa766f589e0161c2f5a944eff827249a0</anchor>
      <arglist>(MatrixOp *Gc)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual MatrixOp *</type>
      <name>get_Gc</name>
      <anchorfile>classNLPInterfacePack_1_1NLPFirstOrder.html</anchorfile>
      <anchor>a66c3fd41bacab73468e7a98816379152</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual MatrixOp &amp;</type>
      <name>Gc</name>
      <anchorfile>classNLPInterfacePack_1_1NLPFirstOrder.html</anchorfile>
      <anchor>a59909f2dc634431042ae5d6c368d1d33</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const MatrixOp &amp;</type>
      <name>Gc</name>
      <anchorfile>classNLPInterfacePack_1_1NLPFirstOrder.html</anchorfile>
      <anchor>a17c21c0c70c13ad9963a224d84d1dab7</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>calc_Gc</name>
      <anchorfile>classNLPInterfacePack_1_1NLPFirstOrder.html</anchorfile>
      <anchor>aaacfb01f36b86c239a3743cca5f1b01a</anchor>
      <arglist>(const Vector &amp;x, bool newx=true) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual size_type</type>
      <name>num_Gc_evals</name>
      <anchorfile>classNLPInterfacePack_1_1NLPFirstOrder.html</anchorfile>
      <anchor>a792e27c3d6a7b0db6bec63aa5772d32b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>NLPObjGrad</name>
      <anchorfile>classNLPInterfacePack_1_1NLPObjGrad.html</anchorfile>
      <anchor>afb95be53fd1fdbb2186d37a9b5c3d9fb</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>supports_Gf</name>
      <anchorfile>classNLPInterfacePack_1_1NLPObjGrad.html</anchorfile>
      <anchor>a00fac73b679fbb079883596b63c67548</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>supports_Gf_prod</name>
      <anchorfile>classNLPInterfacePack_1_1NLPObjGrad.html</anchorfile>
      <anchor>a36f0d690e23e2e64900ab9f9de9bfcc5</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>set_Gf</name>
      <anchorfile>classNLPInterfacePack_1_1NLPObjGrad.html</anchorfile>
      <anchor>a09d8aa18d9322bdc826961a79773e33c</anchor>
      <arglist>(VectorMutable *Gf)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual VectorMutable *</type>
      <name>get_Gf</name>
      <anchorfile>classNLPInterfacePack_1_1NLPObjGrad.html</anchorfile>
      <anchor>a005dc9e7d8ead6fd375c7e30ceb7c0ad</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual VectorMutable &amp;</type>
      <name>Gf</name>
      <anchorfile>classNLPInterfacePack_1_1NLPObjGrad.html</anchorfile>
      <anchor>a41a1c61f724ce5f0eefd6441e0d035be</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const Vector &amp;</type>
      <name>Gf</name>
      <anchorfile>classNLPInterfacePack_1_1NLPObjGrad.html</anchorfile>
      <anchor>ae62e281e6dcdb21ff58582e68bb16423</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>calc_Gf</name>
      <anchorfile>classNLPInterfacePack_1_1NLPObjGrad.html</anchorfile>
      <anchor>aaa7e6bdc0ac3244bc2c32ce256c0fa78</anchor>
      <arglist>(const Vector &amp;x, bool newx=true) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual value_type</type>
      <name>calc_Gf_prod</name>
      <anchorfile>classNLPInterfacePack_1_1NLPObjGrad.html</anchorfile>
      <anchor>a273cac12a3785f982c86f719c70ecf50</anchor>
      <arglist>(const Vector &amp;x, const Vector &amp;d, bool newx=true) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual size_type</type>
      <name>num_Gf_evals</name>
      <anchorfile>classNLPInterfacePack_1_1NLPObjGrad.html</anchorfile>
      <anchor>af04320a39fe4a80c5c4cf8783483275a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const ZeroOrderInfo</type>
      <name>zero_order_info</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a63e6b374a7c56bc74bcbf2b3baa655fa</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const ZeroOrderInfo</type>
      <name>zero_order_info_breve</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a4aea1f22eed001b847e7be0250e5311c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>NLP</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a8f9b7801c9c426d0e166935e2b02a5dc</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~NLP</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>afdee0ffed4b98701793d2d39762cc7fc</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>force_xinit_in_bounds</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a8b656613e166e28308d544a6f08a4075</anchor>
      <arglist>(bool force_xinit_in_bounds)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>force_xinit_in_bounds</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a93274bb52989b37e274fa291a1748f17</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>set_options</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>ab49bf8f5f809c9e9a1218951fe34f8d6</anchor>
      <arglist>(const options_ptr_t &amp;options)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const options_ptr_t &amp;</type>
      <name>get_options</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a6777671ee1d71404cd73b57c2560f2af</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>is_initialized</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a10e99e8ef26428d2f7425effdb73d2b6</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual size_type</type>
      <name>n</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a7f262b0c225619698b650a57298c0769</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual size_type</type>
      <name>m</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a675c11df23f6d5effdb184140f0477d7</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual vec_space_ptr_t</type>
      <name>space_x</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a8fbb005110abb78153b24eb0182107a9</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual vec_space_ptr_t</type>
      <name>space_c</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>aacdd590b3266a728db1fd468762f7e81</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual size_type</type>
      <name>num_bounded_x</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>ade9988baa1efa189c7569623e36f7b6b</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual const Vector &amp;</type>
      <name>xl</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a3f40753a3ede6aa55ef9ad3a2fd9fc07</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual const Vector &amp;</type>
      <name>xu</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a8f283df9dc4df9809688dbe6abb317bf</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual value_type</type>
      <name>max_var_bounds_viol</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a8bafa89c9b8be0dcbe2c27d366997faa</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual const Vector &amp;</type>
      <name>xinit</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>ad3fc1146cc2714d100d5a43602acd17b</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>get_init_lagrange_mult</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a332a401edad57dc3c06c38c20270917f</anchor>
      <arglist>(VectorMutable *lambda, VectorMutable *nu) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>set_f</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a980e823e4c910953086873ed61e34130</anchor>
      <arglist>(value_type *f)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual value_type *</type>
      <name>get_f</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a950451eaca0ea90ef61c7b0422b31fda</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual value_type &amp;</type>
      <name>f</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a738dd301d37fa7b79b30b42f2ea97d16</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const value_type &amp;</type>
      <name>f</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a22aa288b69b1e7f5b4e3ba100051cb1f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>set_c</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>ae7fada2f10f4c10640c462009462a748</anchor>
      <arglist>(VectorMutable *c)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual VectorMutable *</type>
      <name>get_c</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a9a19b89571ab8e44c0bfda3f9530b0c3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual VectorMutable &amp;</type>
      <name>c</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a5da9a90b212ce508fa2b608c4e6a6f80</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const Vector &amp;</type>
      <name>c</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a6aae6fadac3de67155a654fc04a15b34</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>scale_f</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a8757ed6ec67dc3a8a637972788d6e8ba</anchor>
      <arglist>(value_type scale_f)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual value_type</type>
      <name>scale_f</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a71150db7a0cc5d6b1b265338f7ce347e</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>calc_f</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>af1c8df0e7d52d8d0a6159136b5f2415f</anchor>
      <arglist>(const Vector &amp;x, bool newx=true) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>calc_c</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a90ef9d68922f0bdbc46ff1f283494e11</anchor>
      <arglist>(const Vector &amp;x, bool newx=true) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>report_final_solution</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a640bd431dc821cd06e0a4a69c7516be0</anchor>
      <arglist>(const Vector &amp;x, const Vector *lambda, const Vector *nu, bool is_optimal)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual size_type</type>
      <name>num_f_evals</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a684c04f1cbc049d9d626fa7604ee036a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual size_type</type>
      <name>num_c_evals</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a9ba6eabb94807b34d227ff897b1d2ee5</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual size_type</type>
      <name>ns</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a16396fbd0c43455a63d41f481ff09870</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual vec_space_ptr_t</type>
      <name>space_c_breve</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a206f4e541f586e09e43484907333b46a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual vec_space_ptr_t</type>
      <name>space_h_breve</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a17d23d84ad7c31e7ddd41b64eb2ffb67</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const Vector &amp;</type>
      <name>hl_breve</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a11181b99d07f5b799e1ae20b5cc19c71</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const Vector &amp;</type>
      <name>hu_breve</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>ac403365ee5b3f0628c967e56b63fbe75</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>set_c_breve</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a2d07b59dd6f28551ced5a8ee136d3e4b</anchor>
      <arglist>(VectorMutable *c_breve)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual VectorMutable *</type>
      <name>get_c_breve</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a81d6461bcaad765712d6f1a95e7199c3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual VectorMutable &amp;</type>
      <name>c_breve</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a283f37b55d108f6b2c452696e944cf77</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const Vector &amp;</type>
      <name>c_breve</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a7e68ab062a6a057237fa135f17d0ba0e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>set_h_breve</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>aff16ae4eacdcbdcfedf4bb1cbd1bb633</anchor>
      <arglist>(VectorMutable *h_breve)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual VectorMutable *</type>
      <name>get_h_breve</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a596fb18f90a7e367eeb060ea2393879a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual VectorMutable &amp;</type>
      <name>h_breve</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a781936f02d0c72927f570635cc1cc0fb</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const Vector &amp;</type>
      <name>h_breve</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a0f32bff188894d3d868e0b4db9e22eaf</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const Permutation &amp;</type>
      <name>P_var</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a75da12f5236771ce1b82a5009d841284</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const Permutation &amp;</type>
      <name>P_equ</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a0c9249575c0fae4a343ef0611c142388</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>calc_c_breve</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>ad37e807d366cbd918b0115eceed942a2</anchor>
      <arglist>(const Vector &amp;x, bool newx=true) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>calc_h_breve</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a333edd6f0f9fa0e48059a683530b47e1</anchor>
      <arglist>(const Vector &amp;x, bool newx=true) const </arglist>
    </member>
    <member kind="function" static="yes">
      <type>static value_type</type>
      <name>infinite_bound</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a1dc9592c25b467398848fbc6344a90e6</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>NLPInterfacePack::NLPSecondOrder::SecondOrderInfo</name>
    <filename>structNLPInterfacePack_1_1NLPSecondOrder_1_1SecondOrderInfo.html</filename>
    <member kind="function">
      <type></type>
      <name>SecondOrderInfo</name>
      <anchorfile>structNLPInterfacePack_1_1NLPSecondOrder_1_1SecondOrderInfo.html</anchorfile>
      <anchor>a3f80d0507e75231640dd3e59cd4dfa02</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SecondOrderInfo</name>
      <anchorfile>structNLPInterfacePack_1_1NLPSecondOrder_1_1SecondOrderInfo.html</anchorfile>
      <anchor>a663c2600b731718ded47dada58045a15</anchor>
      <arglist>(MatrixSymOp *HL_in, const FirstOrderInfo &amp;first_order_info)</arglist>
    </member>
    <member kind="variable">
      <type>MatrixSymOp *</type>
      <name>HL</name>
      <anchorfile>structNLPInterfacePack_1_1NLPSecondOrder_1_1SecondOrderInfo.html</anchorfile>
      <anchor>a7bfde6cc520a89a7d4db1644d803611c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>MatrixOp *</type>
      <name>Gc</name>
      <anchorfile>structNLPInterfacePack_1_1NLPSecondOrder_1_1SecondOrderInfo.html</anchorfile>
      <anchor>a2123e378ac5254bd1facae78d389f4ab</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>VectorMutable *</type>
      <name>Gf</name>
      <anchorfile>structNLPInterfacePack_1_1NLPSecondOrder_1_1SecondOrderInfo.html</anchorfile>
      <anchor>a94f0b49068817c227acf094ee3872b0c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>value_type *</type>
      <name>f</name>
      <anchorfile>structNLPInterfacePack_1_1NLPSecondOrder_1_1SecondOrderInfo.html</anchorfile>
      <anchor>ac7eb0f25e5bd87ea533061d7712c0792</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>VectorMutable *</type>
      <name>c</name>
      <anchorfile>structNLPInterfacePack_1_1NLPSecondOrder_1_1SecondOrderInfo.html</anchorfile>
      <anchor>ab7892c0e3ddb0cecf8add68f223936d7</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>NLPInterfacePack::NLPVarReductPerm</name>
    <filename>classNLPInterfacePack_1_1NLPVarReductPerm.html</filename>
    <base virtualness="virtual">NLPInterfacePack::NLP</base>
    <class kind="class">NLPInterfacePack::NLPVarReductPerm::InvalidBasis</class>
    <member kind="typedef">
      <type>Teuchos::RCP&lt; const Teuchos::AbstractFactory&lt; Permutation &gt; &gt;</type>
      <name>perm_fcty_ptr_t</name>
      <anchorfile>classNLPInterfacePack_1_1NLPVarReductPerm.html</anchorfile>
      <anchor>aaf51d526f581c00339c4e2bdc5f44aba</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual const perm_fcty_ptr_t</type>
      <name>factory_P_var</name>
      <anchorfile>classNLPInterfacePack_1_1NLPVarReductPerm.html</anchorfile>
      <anchor>a13520b37a43bce18b9e73f954bcd45bc</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual const perm_fcty_ptr_t</type>
      <name>factory_P_equ</name>
      <anchorfile>classNLPInterfacePack_1_1NLPVarReductPerm.html</anchorfile>
      <anchor>a76c3f75543d1e91e773849007b810cd4</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual Range1D</type>
      <name>var_dep</name>
      <anchorfile>classNLPInterfacePack_1_1NLPVarReductPerm.html</anchorfile>
      <anchor>a85418919fc6eb76ef0284c3094370f88</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual Range1D</type>
      <name>var_indep</name>
      <anchorfile>classNLPInterfacePack_1_1NLPVarReductPerm.html</anchorfile>
      <anchor>acb5c51bf708899e18d524453a345264c</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual Range1D</type>
      <name>equ_decomp</name>
      <anchorfile>classNLPInterfacePack_1_1NLPVarReductPerm.html</anchorfile>
      <anchor>ab2b167e99eb258725de6b6c825abe594</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual Range1D</type>
      <name>equ_undecomp</name>
      <anchorfile>classNLPInterfacePack_1_1NLPVarReductPerm.html</anchorfile>
      <anchor>a7f56c13918c214ed46cc9459c1bb88e1</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>nlp_selects_basis</name>
      <anchorfile>classNLPInterfacePack_1_1NLPVarReductPerm.html</anchorfile>
      <anchor>ac07ffa630e1364d564730188ec480ef6</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>get_next_basis</name>
      <anchorfile>classNLPInterfacePack_1_1NLPVarReductPerm.html</anchorfile>
      <anchor>ab2812444b0cb7e931a3441d4b233f9a9</anchor>
      <arglist>(Permutation *P_var, Range1D *var_dep, Permutation *P_equ, Range1D *equ_decomp)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>set_basis</name>
      <anchorfile>classNLPInterfacePack_1_1NLPVarReductPerm.html</anchorfile>
      <anchor>a470da8e2b6d8d8eeed942c01297cc12c</anchor>
      <arglist>(const Permutation &amp;P_var, const Range1D &amp;var_dep, const Permutation *P_equ, const Range1D *equ_decomp)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>get_basis</name>
      <anchorfile>classNLPInterfacePack_1_1NLPVarReductPerm.html</anchorfile>
      <anchor>a3f0ece06c0a4070b5e733bc3f02d91a7</anchor>
      <arglist>(Permutation *P_var, Range1D *var_dep, Permutation *P_equ, Range1D *equ_decomp) const =0</arglist>
    </member>
    <member kind="typedef">
      <type>Teuchos::RCP&lt; const VectorSpace &gt;</type>
      <name>vec_space_ptr_t</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a3535d4780d6a4eba0c25dd88809a624f</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Teuchos::RCP&lt; const OptionsFromStreamPack::OptionsFromStream &gt;</type>
      <name>options_ptr_t</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a8d3cfdcce6ee1e3c84d11ccfb1494ccb</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>const ZeroOrderInfo</type>
      <name>zero_order_info</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a63e6b374a7c56bc74bcbf2b3baa655fa</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const ZeroOrderInfo</type>
      <name>zero_order_info_breve</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a4aea1f22eed001b847e7be0250e5311c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>NLP</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a8f9b7801c9c426d0e166935e2b02a5dc</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~NLP</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>afdee0ffed4b98701793d2d39762cc7fc</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>force_xinit_in_bounds</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a8b656613e166e28308d544a6f08a4075</anchor>
      <arglist>(bool force_xinit_in_bounds)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>force_xinit_in_bounds</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a93274bb52989b37e274fa291a1748f17</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>set_options</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>ab49bf8f5f809c9e9a1218951fe34f8d6</anchor>
      <arglist>(const options_ptr_t &amp;options)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const options_ptr_t &amp;</type>
      <name>get_options</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a6777671ee1d71404cd73b57c2560f2af</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>initialize</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a09ea72e2fa22e9d6e7ee52049cc3dab0</anchor>
      <arglist>(bool test_setup=false)</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>is_initialized</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a10e99e8ef26428d2f7425effdb73d2b6</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual size_type</type>
      <name>n</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a7f262b0c225619698b650a57298c0769</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual size_type</type>
      <name>m</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a675c11df23f6d5effdb184140f0477d7</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual vec_space_ptr_t</type>
      <name>space_x</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a8fbb005110abb78153b24eb0182107a9</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual vec_space_ptr_t</type>
      <name>space_c</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>aacdd590b3266a728db1fd468762f7e81</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual size_type</type>
      <name>num_bounded_x</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>ade9988baa1efa189c7569623e36f7b6b</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual const Vector &amp;</type>
      <name>xl</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a3f40753a3ede6aa55ef9ad3a2fd9fc07</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual const Vector &amp;</type>
      <name>xu</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a8f283df9dc4df9809688dbe6abb317bf</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual value_type</type>
      <name>max_var_bounds_viol</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a8bafa89c9b8be0dcbe2c27d366997faa</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual const Vector &amp;</type>
      <name>xinit</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>ad3fc1146cc2714d100d5a43602acd17b</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>get_init_lagrange_mult</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a332a401edad57dc3c06c38c20270917f</anchor>
      <arglist>(VectorMutable *lambda, VectorMutable *nu) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>set_f</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a980e823e4c910953086873ed61e34130</anchor>
      <arglist>(value_type *f)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual value_type *</type>
      <name>get_f</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a950451eaca0ea90ef61c7b0422b31fda</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual value_type &amp;</type>
      <name>f</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a738dd301d37fa7b79b30b42f2ea97d16</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const value_type &amp;</type>
      <name>f</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a22aa288b69b1e7f5b4e3ba100051cb1f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>set_c</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>ae7fada2f10f4c10640c462009462a748</anchor>
      <arglist>(VectorMutable *c)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual VectorMutable *</type>
      <name>get_c</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a9a19b89571ab8e44c0bfda3f9530b0c3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual VectorMutable &amp;</type>
      <name>c</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a5da9a90b212ce508fa2b608c4e6a6f80</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const Vector &amp;</type>
      <name>c</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a6aae6fadac3de67155a654fc04a15b34</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>unset_quantities</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>ac4679031ab89b596f5872f93e70a0372</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>scale_f</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a8757ed6ec67dc3a8a637972788d6e8ba</anchor>
      <arglist>(value_type scale_f)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual value_type</type>
      <name>scale_f</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a71150db7a0cc5d6b1b265338f7ce347e</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>calc_f</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>af1c8df0e7d52d8d0a6159136b5f2415f</anchor>
      <arglist>(const Vector &amp;x, bool newx=true) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>calc_c</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a90ef9d68922f0bdbc46ff1f283494e11</anchor>
      <arglist>(const Vector &amp;x, bool newx=true) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>report_final_solution</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a640bd431dc821cd06e0a4a69c7516be0</anchor>
      <arglist>(const Vector &amp;x, const Vector *lambda, const Vector *nu, bool is_optimal)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual size_type</type>
      <name>num_f_evals</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a684c04f1cbc049d9d626fa7604ee036a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual size_type</type>
      <name>num_c_evals</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a9ba6eabb94807b34d227ff897b1d2ee5</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual size_type</type>
      <name>ns</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a16396fbd0c43455a63d41f481ff09870</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual vec_space_ptr_t</type>
      <name>space_c_breve</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a206f4e541f586e09e43484907333b46a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual vec_space_ptr_t</type>
      <name>space_h_breve</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a17d23d84ad7c31e7ddd41b64eb2ffb67</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const Vector &amp;</type>
      <name>hl_breve</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a11181b99d07f5b799e1ae20b5cc19c71</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const Vector &amp;</type>
      <name>hu_breve</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>ac403365ee5b3f0628c967e56b63fbe75</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>set_c_breve</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a2d07b59dd6f28551ced5a8ee136d3e4b</anchor>
      <arglist>(VectorMutable *c_breve)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual VectorMutable *</type>
      <name>get_c_breve</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a81d6461bcaad765712d6f1a95e7199c3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual VectorMutable &amp;</type>
      <name>c_breve</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a283f37b55d108f6b2c452696e944cf77</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const Vector &amp;</type>
      <name>c_breve</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a7e68ab062a6a057237fa135f17d0ba0e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>set_h_breve</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>aff16ae4eacdcbdcfedf4bb1cbd1bb633</anchor>
      <arglist>(VectorMutable *h_breve)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual VectorMutable *</type>
      <name>get_h_breve</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a596fb18f90a7e367eeb060ea2393879a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual VectorMutable &amp;</type>
      <name>h_breve</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a781936f02d0c72927f570635cc1cc0fb</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const Vector &amp;</type>
      <name>h_breve</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a0f32bff188894d3d868e0b4db9e22eaf</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const Permutation &amp;</type>
      <name>P_var</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a75da12f5236771ce1b82a5009d841284</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const Permutation &amp;</type>
      <name>P_equ</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a0c9249575c0fae4a343ef0611c142388</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>calc_c_breve</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>ad37e807d366cbd918b0115eceed942a2</anchor>
      <arglist>(const Vector &amp;x, bool newx=true) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>calc_h_breve</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a333edd6f0f9fa0e48059a683530b47e1</anchor>
      <arglist>(const Vector &amp;x, bool newx=true) const </arglist>
    </member>
    <member kind="function" static="yes">
      <type>static value_type</type>
      <name>infinite_bound</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a1dc9592c25b467398848fbc6344a90e6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>assert_ref_set</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a737c913d13ca4e41a1ec25b371720bbc</anchor>
      <arglist>(T *p, std::string info) const </arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual void</type>
      <name>imp_calc_f</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>ad523d2c27f85684f95b4115e384f8efb</anchor>
      <arglist>(const Vector &amp;x, bool newx, const ZeroOrderInfo &amp;zero_order_info) const =0</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual void</type>
      <name>imp_calc_c</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a8da8481d95868220fd6eb0952d65c114</anchor>
      <arglist>(const Vector &amp;x, bool newx, const ZeroOrderInfo &amp;zero_order_info) const =0</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual void</type>
      <name>imp_calc_c_breve</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a6c493037871f5a6c14c7218221f06b23</anchor>
      <arglist>(const Vector &amp;x, bool newx, const ZeroOrderInfo &amp;zero_order_info_breve) const </arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual void</type>
      <name>imp_calc_h_breve</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a24ba3f8d9b03d47501b73a8c51c6ec53</anchor>
      <arglist>(const Vector &amp;x, bool newx, const ZeroOrderInfo &amp;zero_order_info_breve) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>NLPInterfacePack::NLPVarReductPerm::InvalidBasis</name>
    <filename>classNLPInterfacePack_1_1NLPVarReductPerm_1_1InvalidBasis.html</filename>
  </compound>
  <compound kind="class">
    <name>NLPInterfacePack::NLPDirectTester</name>
    <filename>classNLPInterfacePack_1_1NLPDirectTester.html</filename>
    <member kind="enumeration">
      <name>ETestingMethod</name>
      <anchorfile>classNLPInterfacePack_1_1NLPDirectTester.html</anchorfile>
      <anchor>ac8099a0371546dbbb5e393468f75612a</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_COMPOSITION_MEMBERS</name>
      <anchorfile>classNLPInterfacePack_1_1NLPDirectTester.html</anchorfile>
      <anchor>a4d7a851c0295d65eb55f406c2c4c9672</anchor>
      <arglist>(CalcFiniteDiffProd, calc_fd_prod)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classNLPInterfacePack_1_1NLPDirectTester.html</anchorfile>
      <anchor>a0b26b6b7580818bda4b169a3ccc0b565</anchor>
      <arglist>(ETestingMethod, Gf_testing_method)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classNLPInterfacePack_1_1NLPDirectTester.html</anchorfile>
      <anchor>a79f88e5e62580a8703689f88fef31c6b</anchor>
      <arglist>(ETestingMethod, Gc_testing_method)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classNLPInterfacePack_1_1NLPDirectTester.html</anchorfile>
      <anchor>a2bef382474eba93cb6b44b1e8a0218a3</anchor>
      <arglist>(value_type, Gf_warning_tol)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classNLPInterfacePack_1_1NLPDirectTester.html</anchorfile>
      <anchor>a1015fad57bea9afefdd4d3b8dce41876</anchor>
      <arglist>(value_type, Gf_error_tol)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classNLPInterfacePack_1_1NLPDirectTester.html</anchorfile>
      <anchor>afd38cf593d801c312a7c3f8410761ae4</anchor>
      <arglist>(value_type, Gc_warning_tol)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classNLPInterfacePack_1_1NLPDirectTester.html</anchorfile>
      <anchor>a580801d1f1374610faf03f6954b7cc69</anchor>
      <arglist>(value_type, Gc_error_tol)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classNLPInterfacePack_1_1NLPDirectTester.html</anchorfile>
      <anchor>a104b1f2411d67f31ab08fc9b03b6e56f</anchor>
      <arglist>(size_type, num_fd_directions)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classNLPInterfacePack_1_1NLPDirectTester.html</anchorfile>
      <anchor>a6b95f7688628b3241a3d4b02a9f68c92</anchor>
      <arglist>(bool, dump_all)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>NLPDirectTester</name>
      <anchorfile>classNLPInterfacePack_1_1NLPDirectTester.html</anchorfile>
      <anchor>ac63609a9cccc3d0cfc3666e11f59a33a</anchor>
      <arglist>(const calc_fd_prod_ptr_t &amp;calc_fd_prod=Teuchos::null, ETestingMethod Gf_testing_method=FD_DIRECTIONAL, ETestingMethod Gc_testing_method=FD_DIRECTIONAL, value_type Gf_warning_tol=1e-6, value_type Gf_error_tol=1e-1, value_type Gc_warning_tol=1e-6, value_type Gc_error_tol=1e-1, size_type num_fd_directions=1, bool dump_all=false)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>finite_diff_check</name>
      <anchorfile>classNLPInterfacePack_1_1NLPDirectTester.html</anchorfile>
      <anchor>ab323827acdcece533d4823e9dc408b16</anchor>
      <arglist>(NLPDirect *nlp, const Vector &amp;xo, const Vector *xl, const Vector *xu, const Vector *c, const Vector *Gf, const Vector *py, const Vector *rGf, const MatrixOp *GcU, const MatrixOp *D, const MatrixOp *Uz, bool print_all_warnings, std::ostream *out) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>NLPInterfacePack::NLPDirectTesterSetOptions</name>
    <filename>classNLPInterfacePack_1_1NLPDirectTesterSetOptions.html</filename>
    <base>OptionsFromStreamPack::SetOptionsFromStreamNode</base>
    <base>SetOptionsToTargetBase&lt; NLPDirectTester &gt;</base>
    <member kind="function">
      <type></type>
      <name>NLPDirectTesterSetOptions</name>
      <anchorfile>classNLPInterfacePack_1_1NLPDirectTesterSetOptions.html</anchorfile>
      <anchor>a976d8f36494b78c0febf304dde062a1e</anchor>
      <arglist>(NLPDirectTester *target=0, const char opt_grp_name[]=&quot;NLPDirectTester&quot;)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>setOption</name>
      <anchorfile>classNLPInterfacePack_1_1NLPDirectTesterSetOptions.html</anchorfile>
      <anchor>a7482ed513b17643b1a1a6fe020c82d0a</anchor>
      <arglist>(int option_num, const std::string &amp;option_value)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>NLPInterfacePack::NLPFirstDerivTester</name>
    <filename>classNLPInterfacePack_1_1NLPFirstDerivTester.html</filename>
    <member kind="enumeration">
      <name>ETestingMethod</name>
      <anchorfile>classNLPInterfacePack_1_1NLPFirstDerivTester.html</anchorfile>
      <anchor>a724f4ac051dade3638ee4b22b244f6b1</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_COMPOSITION_MEMBERS</name>
      <anchorfile>classNLPInterfacePack_1_1NLPFirstDerivTester.html</anchorfile>
      <anchor>a083b9f70253bbf34e6081a53f48c96dc</anchor>
      <arglist>(CalcFiniteDiffProd, calc_fd_prod)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classNLPInterfacePack_1_1NLPFirstDerivTester.html</anchorfile>
      <anchor>a6e8d95e927ccbf6bcf5fb29a99b49e4b</anchor>
      <arglist>(ETestingMethod, fd_testing_method)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classNLPInterfacePack_1_1NLPFirstDerivTester.html</anchorfile>
      <anchor>af664f2544554ad7d388b35e3a063cfa6</anchor>
      <arglist>(size_type, num_fd_directions)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classNLPInterfacePack_1_1NLPFirstDerivTester.html</anchorfile>
      <anchor>adbd8258786456a0476cd508762bbf452</anchor>
      <arglist>(value_type, warning_tol)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classNLPInterfacePack_1_1NLPFirstDerivTester.html</anchorfile>
      <anchor>ae97746f0ade2194748c71a1b2e26c5f2</anchor>
      <arglist>(value_type, error_tol)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>NLPFirstDerivTester</name>
      <anchorfile>classNLPInterfacePack_1_1NLPFirstDerivTester.html</anchorfile>
      <anchor>ae5bb94cd4c90ab1b75e48d9061b128bf</anchor>
      <arglist>(const calc_fd_prod_ptr_t &amp;calc_fd_prod=Teuchos::rcp(new CalcFiniteDiffProd()), ETestingMethod fd_testing_method=FD_DIRECTIONAL, size_type num_fd_directions=1, value_type warning_tol=1e-8, value_type error_tol=1e-3)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>finite_diff_check</name>
      <anchorfile>classNLPInterfacePack_1_1NLPFirstDerivTester.html</anchorfile>
      <anchor>aac0240f2d60827672a274d78ed4598e3</anchor>
      <arglist>(NLP *nlp, const Vector &amp;xo, const Vector *xl, const Vector *xu, const MatrixOp *Gc, const Vector *Gf, bool print_all_warnings, std::ostream *out) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>NLPInterfacePack::NLPFirstDerivTesterSetOptions</name>
    <filename>classNLPInterfacePack_1_1NLPFirstDerivTesterSetOptions.html</filename>
    <base>OptionsFromStreamPack::SetOptionsFromStreamNode</base>
    <base>SetOptionsToTargetBase&lt; NLPFirstDerivTester &gt;</base>
    <member kind="function">
      <type></type>
      <name>NLPFirstDerivTesterSetOptions</name>
      <anchorfile>classNLPInterfacePack_1_1NLPFirstDerivTesterSetOptions.html</anchorfile>
      <anchor>a54cba8056a33a0cb80af8e7acd111ceb</anchor>
      <arglist>(NLPFirstDerivTester *target=0, const char opt_grp_name[]=&quot;NLPFirstDerivTester&quot;)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>setOption</name>
      <anchorfile>classNLPInterfacePack_1_1NLPFirstDerivTesterSetOptions.html</anchorfile>
      <anchor>aa10cc4d57047acddf9efae0800ad86c9</anchor>
      <arglist>(int option_num, const std::string &amp;option_value)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>NLPInterfacePack::NLPTester</name>
    <filename>classNLPInterfacePack_1_1NLPTester.html</filename>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classNLPInterfacePack_1_1NLPTester.html</anchorfile>
      <anchor>a2c09db93f2bb64d600c293fe5480d234</anchor>
      <arglist>(bool, print_all)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classNLPInterfacePack_1_1NLPTester.html</anchorfile>
      <anchor>ac3b2f5b5b772a6320e9d641e7541d261</anchor>
      <arglist>(bool, throw_exception)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>NLPTester</name>
      <anchorfile>classNLPInterfacePack_1_1NLPTester.html</anchorfile>
      <anchor>a4ddbf13fd3ef2f58f1602e7e9f11cf44</anchor>
      <arglist>(bool print_all=false, bool throw_exception=true)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>test_interface</name>
      <anchorfile>classNLPInterfacePack_1_1NLPTester.html</anchorfile>
      <anchor>adb5a88bb0089a8122e58eabe88c7de3c</anchor>
      <arglist>(NLP *nlp, const Vector &amp;xo, bool print_all_warnings, std::ostream *out)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>NLPInterfacePack::NLPTesterSetOptions</name>
    <filename>classNLPInterfacePack_1_1NLPTesterSetOptions.html</filename>
    <base>OptionsFromStreamPack::SetOptionsFromStreamNode</base>
    <base>SetOptionsToTargetBase&lt; NLPTester &gt;</base>
    <member kind="function">
      <type></type>
      <name>NLPTesterSetOptions</name>
      <anchorfile>classNLPInterfacePack_1_1NLPTesterSetOptions.html</anchorfile>
      <anchor>a0a8e1ac57e521fd0b714befedb158504</anchor>
      <arglist>(NLPTester *target=0, const char opt_grp_name[]=&quot;NLPTester&quot;)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>setOption</name>
      <anchorfile>classNLPInterfacePack_1_1NLPTesterSetOptions.html</anchorfile>
      <anchor>a3551a0ac178e0e1dcc8d1b1978c2b44c</anchor>
      <arglist>(int option_num, const std::string &amp;option_value)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>NLPInterfacePack::CalcFiniteDiffProd</name>
    <filename>classNLPInterfacePack_1_1CalcFiniteDiffProd.html</filename>
    <member kind="enumeration">
      <name>EFDMethodOrder</name>
      <anchorfile>classNLPInterfacePack_1_1CalcFiniteDiffProd.html</anchorfile>
      <anchor>a412057d5d844e97b7b86df709e7790b8</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>FD_ORDER_ONE</name>
      <anchorfile>classNLPInterfacePack_1_1CalcFiniteDiffProd.html</anchorfile>
      <anchor>a412057d5d844e97b7b86df709e7790b8a63aa916de963577c8610ec30753dc6a8</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>FD_ORDER_TWO</name>
      <anchorfile>classNLPInterfacePack_1_1CalcFiniteDiffProd.html</anchorfile>
      <anchor>a412057d5d844e97b7b86df709e7790b8aa1d12d77ffcabfeb49348cd6e337377c</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>FD_ORDER_TWO_CENTRAL</name>
      <anchorfile>classNLPInterfacePack_1_1CalcFiniteDiffProd.html</anchorfile>
      <anchor>a412057d5d844e97b7b86df709e7790b8a7fffc0b1ac87477107e68b228db1e69c</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>FD_ORDER_TWO_AUTO</name>
      <anchorfile>classNLPInterfacePack_1_1CalcFiniteDiffProd.html</anchorfile>
      <anchor>a412057d5d844e97b7b86df709e7790b8a84a1ee8d28fcc8ff70c746fe256eda6b</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>FD_ORDER_FOUR</name>
      <anchorfile>classNLPInterfacePack_1_1CalcFiniteDiffProd.html</anchorfile>
      <anchor>a412057d5d844e97b7b86df709e7790b8a5c9da7ce30a01dc42f6ff990fc56e92a</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>FD_ORDER_FOUR_CENTRAL</name>
      <anchorfile>classNLPInterfacePack_1_1CalcFiniteDiffProd.html</anchorfile>
      <anchor>a412057d5d844e97b7b86df709e7790b8acf10c70c2c34a2a146d0b8231c86e7ec</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>FD_ORDER_FOUR_AUTO</name>
      <anchorfile>classNLPInterfacePack_1_1CalcFiniteDiffProd.html</anchorfile>
      <anchor>a412057d5d844e97b7b86df709e7790b8ad9d0a540a86eedca03b1aca7a54d01a3</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>EFDStepSelect</name>
      <anchorfile>classNLPInterfacePack_1_1CalcFiniteDiffProd.html</anchorfile>
      <anchor>a612c770c405da7015a3799ef86744cea</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>FD_STEP_ABSOLUTE</name>
      <anchorfile>classNLPInterfacePack_1_1CalcFiniteDiffProd.html</anchorfile>
      <anchor>a612c770c405da7015a3799ef86744ceaa4c7bb07b510f6971831cc6f8b58a93ec</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>FD_STEP_RELATIVE</name>
      <anchorfile>classNLPInterfacePack_1_1CalcFiniteDiffProd.html</anchorfile>
      <anchor>a612c770c405da7015a3799ef86744ceaa3641b0ebbc36ae0eccf4206f167e5efd</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classNLPInterfacePack_1_1CalcFiniteDiffProd.html</anchorfile>
      <anchor>ad47fdd7b7dc972abb1e897d789deb171</anchor>
      <arglist>(EFDMethodOrder, fd_method_order)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classNLPInterfacePack_1_1CalcFiniteDiffProd.html</anchorfile>
      <anchor>a4cd342c63e9e68e49607f327c226cb3e</anchor>
      <arglist>(EFDStepSelect, fd_step_select)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classNLPInterfacePack_1_1CalcFiniteDiffProd.html</anchorfile>
      <anchor>a21649fe81e63cf8bb0db66e53e02c5af</anchor>
      <arglist>(value_type, fd_step_size)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classNLPInterfacePack_1_1CalcFiniteDiffProd.html</anchorfile>
      <anchor>a117b8ffc190e96d64164a5cdbf0b7c27</anchor>
      <arglist>(value_type, fd_step_size_min)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classNLPInterfacePack_1_1CalcFiniteDiffProd.html</anchorfile>
      <anchor>a4199782b52882ad7af2b1c85577819d4</anchor>
      <arglist>(value_type, fd_step_size_f)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classNLPInterfacePack_1_1CalcFiniteDiffProd.html</anchorfile>
      <anchor>a0ecd60bd088deee76e1065ff5691a0ee</anchor>
      <arglist>(value_type, fd_step_size_c)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>CalcFiniteDiffProd</name>
      <anchorfile>classNLPInterfacePack_1_1CalcFiniteDiffProd.html</anchorfile>
      <anchor>ae39aef9e2bab1642660fbf92d78e06c4</anchor>
      <arglist>(EFDMethodOrder fd_method_order=FD_ORDER_FOUR_AUTO, EFDStepSelect fd_step_select=FD_STEP_ABSOLUTE, value_type fd_step_size=-1.0, value_type fd_step_size_min=-1.0, value_type fd_step_size_f=-1.0, value_type fd_step_size_c=-1.0)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~CalcFiniteDiffProd</name>
      <anchorfile>classNLPInterfacePack_1_1CalcFiniteDiffProd.html</anchorfile>
      <anchor>a78e91f84ef319d54596114e9376de75b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>calc_deriv_product</name>
      <anchorfile>classNLPInterfacePack_1_1CalcFiniteDiffProd.html</anchorfile>
      <anchor>a57faee344756d490f791bb5f5999bbe2</anchor>
      <arglist>(const Vector &amp;xo, const Vector *xl, const Vector *xu, const Vector &amp;v, const value_type *fo, const Vector *co, bool check_nan_inf, NLP *nlp, value_type *Gf_prod, VectorMutable *Gc_prod, std::ostream *out, bool trace=false, bool dump_all=false) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>NLPInterfacePack::CalcFiniteDiffProdSetOptions</name>
    <filename>classNLPInterfacePack_1_1CalcFiniteDiffProdSetOptions.html</filename>
    <base>OptionsFromStreamPack::SetOptionsFromStreamNode</base>
    <base>SetOptionsToTargetBase&lt; CalcFiniteDiffProd &gt;</base>
    <member kind="function">
      <type></type>
      <name>CalcFiniteDiffProdSetOptions</name>
      <anchorfile>classNLPInterfacePack_1_1CalcFiniteDiffProdSetOptions.html</anchorfile>
      <anchor>a8598e01ee2c785d68fe7b0ec3784bb82</anchor>
      <arglist>(CalcFiniteDiffProd *target=0, const char opt_grp_name[]=&quot;CalcFiniteDiffProd&quot;)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>setOption</name>
      <anchorfile>classNLPInterfacePack_1_1CalcFiniteDiffProdSetOptions.html</anchorfile>
      <anchor>aa0a21ff4dacf048f02d370994fbc1117</anchor>
      <arglist>(int option_num, const std::string &amp;option_value)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>NLPInterfacePack::NLPBarrier</name>
    <filename>classNLPInterfacePack_1_1NLPBarrier.html</filename>
    <base>NLPInterfacePack::NLPObjGrad</base>
    <member kind="function">
      <type>void</type>
      <name>mu</name>
      <anchorfile>classNLPInterfacePack_1_1NLPBarrier.html</anchorfile>
      <anchor>aec1abe342c8d0957ed44f88befb856b8</anchor>
      <arglist>(const value_type mu)</arglist>
    </member>
    <member kind="function">
      <type>value_type</type>
      <name>barrier_term</name>
      <anchorfile>classNLPInterfacePack_1_1NLPBarrier.html</anchorfile>
      <anchor>a9a50589a470542094a7fb402d624a379</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>value_type</type>
      <name>objective_term</name>
      <anchorfile>classNLPInterfacePack_1_1NLPBarrier.html</anchorfile>
      <anchor>ab059d9acf630b3537af17e970271c07e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Teuchos::RCP&lt; Vector &gt;</type>
      <name>grad_barrier_term</name>
      <anchorfile>classNLPInterfacePack_1_1NLPBarrier.html</anchorfile>
      <anchor>a7d8f47e96fa3832cdae5c96b02b3bfca</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Teuchos::RCP&lt; Vector &gt;</type>
      <name>grad_objective_term</name>
      <anchorfile>classNLPInterfacePack_1_1NLPBarrier.html</anchorfile>
      <anchor>aa9f09366426f1f7802637b0154fc6f69</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>NLPBarrier</name>
      <anchorfile>classNLPInterfacePack_1_1NLPBarrier.html</anchorfile>
      <anchor>a34226a6385f8f125d4dd59f8c63bc161</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>InitializeFromNLP</name>
      <anchorfile>classNLPInterfacePack_1_1NLPBarrier.html</anchorfile>
      <anchor>aecf663c4d1ae5ee674c134cf7a541842</anchor>
      <arglist>(Teuchos::RCP&lt; NLP &gt; original_nlp)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initialize</name>
      <anchorfile>classNLPInterfacePack_1_1NLPBarrier.html</anchorfile>
      <anchor>a63d54f91732fdfd2fe425e590ea1debb</anchor>
      <arglist>(bool test_setup)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>is_initialized</name>
      <anchorfile>classNLPInterfacePack_1_1NLPBarrier.html</anchorfile>
      <anchor>af28980f1a3fe86a2068006b9cff5ac31</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_Gf</name>
      <anchorfile>classNLPInterfacePack_1_1NLPBarrier.html</anchorfile>
      <anchor>a87810cfd0e0d6d600bb8fafdfc237d45</anchor>
      <arglist>(VectorMutable *Gf)</arglist>
    </member>
    <member kind="function">
      <type>VectorMutable *</type>
      <name>get_Gf</name>
      <anchorfile>classNLPInterfacePack_1_1NLPBarrier.html</anchorfile>
      <anchor>a5adfa32d9ad1613ee836e71edd504396</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>VectorMutable &amp;</type>
      <name>Gf</name>
      <anchorfile>classNLPInterfacePack_1_1NLPBarrier.html</anchorfile>
      <anchor>aded1eb154168b89daa93da905422739e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const Vector &amp;</type>
      <name>Gf</name>
      <anchorfile>classNLPInterfacePack_1_1NLPBarrier.html</anchorfile>
      <anchor>a29d32a35c48296114ac97d038ff5b33a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>calc_Gf</name>
      <anchorfile>classNLPInterfacePack_1_1NLPBarrier.html</anchorfile>
      <anchor>a5a763b6e4661546cc05c57cb0f03671e</anchor>
      <arglist>(const Vector &amp;x, bool newx=true) const </arglist>
    </member>
    <member kind="function">
      <type>size_type</type>
      <name>num_Gf_evals</name>
      <anchorfile>classNLPInterfacePack_1_1NLPBarrier.html</anchorfile>
      <anchor>aaf8c45d7359348f3ca6b1c543fe65018</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>force_xinit_in_bounds</name>
      <anchorfile>classNLPInterfacePack_1_1NLPBarrier.html</anchorfile>
      <anchor>ac0844c56f58c2fe19c88f0fc9ed77c81</anchor>
      <arglist>(bool force_xinit_in_bounds)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>force_xinit_in_bounds</name>
      <anchorfile>classNLPInterfacePack_1_1NLPBarrier.html</anchorfile>
      <anchor>ab66cb4ea9bbe237c07be469834f2c93e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>size_type</type>
      <name>n</name>
      <anchorfile>classNLPInterfacePack_1_1NLPBarrier.html</anchorfile>
      <anchor>ab27b7dc2b0a1fefdbd82207a0d3e1a3a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>size_type</type>
      <name>m</name>
      <anchorfile>classNLPInterfacePack_1_1NLPBarrier.html</anchorfile>
      <anchor>ae1ab98cd504de64fe1b7e8f3be855017</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>vec_space_ptr_t</type>
      <name>space_x</name>
      <anchorfile>classNLPInterfacePack_1_1NLPBarrier.html</anchorfile>
      <anchor>a35460c24ba0c293196384d4912777d28</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>vec_space_ptr_t</type>
      <name>space_c</name>
      <anchorfile>classNLPInterfacePack_1_1NLPBarrier.html</anchorfile>
      <anchor>a281616d2a597d9d56f2e837da2948b6b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>size_type</type>
      <name>num_bounded_x</name>
      <anchorfile>classNLPInterfacePack_1_1NLPBarrier.html</anchorfile>
      <anchor>ad7b1ad0cce24a2f5b936d0f3209bd101</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Vector &amp;</type>
      <name>xl</name>
      <anchorfile>classNLPInterfacePack_1_1NLPBarrier.html</anchorfile>
      <anchor>a7723ce0ffd4074c1203a9489fb59334c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Vector &amp;</type>
      <name>xu</name>
      <anchorfile>classNLPInterfacePack_1_1NLPBarrier.html</anchorfile>
      <anchor>a9e534d32588dbeb1cdb608419b3c9420</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>value_type</type>
      <name>max_var_bounds_viol</name>
      <anchorfile>classNLPInterfacePack_1_1NLPBarrier.html</anchorfile>
      <anchor>a68dccdaa083a2389b7748488dab27e13</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Vector &amp;</type>
      <name>xinit</name>
      <anchorfile>classNLPInterfacePack_1_1NLPBarrier.html</anchorfile>
      <anchor>acf1180bb3fea2f14ae23713d07683cc7</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>get_init_lagrange_mult</name>
      <anchorfile>classNLPInterfacePack_1_1NLPBarrier.html</anchorfile>
      <anchor>a951620237a8ab8fab08ae242a97ba801</anchor>
      <arglist>(VectorMutable *lambda, VectorMutable *nu) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_f</name>
      <anchorfile>classNLPInterfacePack_1_1NLPBarrier.html</anchorfile>
      <anchor>a0764c13ab9933245aea1e7a562f703b3</anchor>
      <arglist>(value_type *f)</arglist>
    </member>
    <member kind="function">
      <type>value_type *</type>
      <name>get_f</name>
      <anchorfile>classNLPInterfacePack_1_1NLPBarrier.html</anchorfile>
      <anchor>a75d4a15b92b4eae22e15eaedc09d23b3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>value_type &amp;</type>
      <name>f</name>
      <anchorfile>classNLPInterfacePack_1_1NLPBarrier.html</anchorfile>
      <anchor>a88ddc89bd3584585b52f3b26ccd0e97e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const value_type &amp;</type>
      <name>f</name>
      <anchorfile>classNLPInterfacePack_1_1NLPBarrier.html</anchorfile>
      <anchor>a2981ebd6dd43f0c85665f8e1c887b191</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_c</name>
      <anchorfile>classNLPInterfacePack_1_1NLPBarrier.html</anchorfile>
      <anchor>aff01edfd9fc135b09a029a3a063268cc</anchor>
      <arglist>(VectorMutable *c)</arglist>
    </member>
    <member kind="function">
      <type>VectorMutable *</type>
      <name>get_c</name>
      <anchorfile>classNLPInterfacePack_1_1NLPBarrier.html</anchorfile>
      <anchor>aa279be0cb054c73e5e8cbb3c7d05181f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>VectorMutable &amp;</type>
      <name>c</name>
      <anchorfile>classNLPInterfacePack_1_1NLPBarrier.html</anchorfile>
      <anchor>a187f4032f143ceb7c04aded9c87bb1af</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const Vector &amp;</type>
      <name>c</name>
      <anchorfile>classNLPInterfacePack_1_1NLPBarrier.html</anchorfile>
      <anchor>a5d114218a66250ac3a31b4dd72280ed4</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>scale_f</name>
      <anchorfile>classNLPInterfacePack_1_1NLPBarrier.html</anchorfile>
      <anchor>acc9d5b27ce13a57df6fed989122851d8</anchor>
      <arglist>(value_type scale_f)</arglist>
    </member>
    <member kind="function">
      <type>value_type</type>
      <name>scale_f</name>
      <anchorfile>classNLPInterfacePack_1_1NLPBarrier.html</anchorfile>
      <anchor>a8e64e30c4d44796d351d027980c5bdfa</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>calc_f</name>
      <anchorfile>classNLPInterfacePack_1_1NLPBarrier.html</anchorfile>
      <anchor>a19201dbdec33a16b8b2575cf1f3b9473</anchor>
      <arglist>(const Vector &amp;x, bool newx=true) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>calc_c</name>
      <anchorfile>classNLPInterfacePack_1_1NLPBarrier.html</anchorfile>
      <anchor>a6c08bdf2e0b894d8d327666243e47ea8</anchor>
      <arglist>(const Vector &amp;x, bool newx=true) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>report_final_solution</name>
      <anchorfile>classNLPInterfacePack_1_1NLPBarrier.html</anchorfile>
      <anchor>a345d3f0a57b4e4e04e59d40fa277eb7b</anchor>
      <arglist>(const Vector &amp;x, const Vector *lambda, const Vector *nu, bool is_optimal)</arglist>
    </member>
    <member kind="function">
      <type>size_type</type>
      <name>num_f_evals</name>
      <anchorfile>classNLPInterfacePack_1_1NLPBarrier.html</anchorfile>
      <anchor>a35bedc8f91cafd413c43b203860662c9</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>size_type</type>
      <name>num_c_evals</name>
      <anchorfile>classNLPInterfacePack_1_1NLPBarrier.html</anchorfile>
      <anchor>a3f7fca3ac4bea5858db8ecdc4b1c8286</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>size_type</type>
      <name>ns</name>
      <anchorfile>classNLPInterfacePack_1_1NLPBarrier.html</anchorfile>
      <anchor>a2461c00befcbacf6dceeed00796b3abc</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>vec_space_ptr_t</type>
      <name>space_c_breve</name>
      <anchorfile>classNLPInterfacePack_1_1NLPBarrier.html</anchorfile>
      <anchor>a3d525863b8d99042dd89e51512470635</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>vec_space_ptr_t</type>
      <name>space_h_breve</name>
      <anchorfile>classNLPInterfacePack_1_1NLPBarrier.html</anchorfile>
      <anchor>a70d125bbd02f7ef71ebbd2a96559f1cd</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Vector &amp;</type>
      <name>hl_breve</name>
      <anchorfile>classNLPInterfacePack_1_1NLPBarrier.html</anchorfile>
      <anchor>a57e112339379c15bfb401bf34c71e645</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Vector &amp;</type>
      <name>hu_breve</name>
      <anchorfile>classNLPInterfacePack_1_1NLPBarrier.html</anchorfile>
      <anchor>aacb6beb1efaeedd45ae5113402ac4b4a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_c_breve</name>
      <anchorfile>classNLPInterfacePack_1_1NLPBarrier.html</anchorfile>
      <anchor>a7541aae06051512dcc9e161e40c29585</anchor>
      <arglist>(VectorMutable *c_breve)</arglist>
    </member>
    <member kind="function">
      <type>VectorMutable *</type>
      <name>get_c_breve</name>
      <anchorfile>classNLPInterfacePack_1_1NLPBarrier.html</anchorfile>
      <anchor>a7e347ba114dbaaa8a6939dbcfbfadff2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>VectorMutable &amp;</type>
      <name>c_breve</name>
      <anchorfile>classNLPInterfacePack_1_1NLPBarrier.html</anchorfile>
      <anchor>a1b6f0874a42f464901c678de6e8f92e3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const Vector &amp;</type>
      <name>c_breve</name>
      <anchorfile>classNLPInterfacePack_1_1NLPBarrier.html</anchorfile>
      <anchor>adf4f117787185ceae9b3d7c4c2fe662c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_h_breve</name>
      <anchorfile>classNLPInterfacePack_1_1NLPBarrier.html</anchorfile>
      <anchor>ae42fb77a9cc2188eb323a43421b319cc</anchor>
      <arglist>(VectorMutable *h_breve)</arglist>
    </member>
    <member kind="function">
      <type>VectorMutable *</type>
      <name>get_h_breve</name>
      <anchorfile>classNLPInterfacePack_1_1NLPBarrier.html</anchorfile>
      <anchor>ad66c6844daf87100e9faa75d4337bf2f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>VectorMutable &amp;</type>
      <name>h_breve</name>
      <anchorfile>classNLPInterfacePack_1_1NLPBarrier.html</anchorfile>
      <anchor>a12cb5c99da4df8b065a30240a615162f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const Vector &amp;</type>
      <name>h_breve</name>
      <anchorfile>classNLPInterfacePack_1_1NLPBarrier.html</anchorfile>
      <anchor>a6884b768614b2dd23df921cb5ffda615</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Permutation &amp;</type>
      <name>P_var</name>
      <anchorfile>classNLPInterfacePack_1_1NLPBarrier.html</anchorfile>
      <anchor>a887fd5de1c1eea3f39f0470e690dc969</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Permutation &amp;</type>
      <name>P_equ</name>
      <anchorfile>classNLPInterfacePack_1_1NLPBarrier.html</anchorfile>
      <anchor>ab115ff702d97d168241b54cde568dcc7</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>calc_c_breve</name>
      <anchorfile>classNLPInterfacePack_1_1NLPBarrier.html</anchorfile>
      <anchor>ac445cd18aa1033895f19d18c671e87bb</anchor>
      <arglist>(const Vector &amp;x, bool newx) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>calc_h_breve</name>
      <anchorfile>classNLPInterfacePack_1_1NLPBarrier.html</anchorfile>
      <anchor>a8dd26c483fa72338285f21526ed99f65</anchor>
      <arglist>(const Vector &amp;x, bool newx) const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>imp_calc_f</name>
      <anchorfile>classNLPInterfacePack_1_1NLPBarrier.html</anchorfile>
      <anchor>a186cc8d6aaf33febcef2d2472b6b56e5</anchor>
      <arglist>(const Vector &amp;x, bool newx, const ZeroOrderInfo &amp;zero_order_info) const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>imp_calc_c</name>
      <anchorfile>classNLPInterfacePack_1_1NLPBarrier.html</anchorfile>
      <anchor>a092f996d6876041da1de7bee64f2ec72</anchor>
      <arglist>(const Vector &amp;x, bool newx, const ZeroOrderInfo &amp;zero_order_info) const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>imp_calc_c_breve</name>
      <anchorfile>classNLPInterfacePack_1_1NLPBarrier.html</anchorfile>
      <anchor>a1a280ade8451f6c6248173d6c79c9da6</anchor>
      <arglist>(const Vector &amp;x, bool newx, const ZeroOrderInfo &amp;zero_order_info_breve) const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>imp_calc_h_breve</name>
      <anchorfile>classNLPInterfacePack_1_1NLPBarrier.html</anchorfile>
      <anchor>abef8952f28805035b518a0d995b989fb</anchor>
      <arglist>(const Vector &amp;x, bool newx, const ZeroOrderInfo &amp;zero_order_info_breve) const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>imp_calc_Gf</name>
      <anchorfile>classNLPInterfacePack_1_1NLPBarrier.html</anchorfile>
      <anchor>a29ab57bd13fade3f5803e3e7ecb41cee</anchor>
      <arglist>(const Vector &amp;x, bool newx, const ObjGradInfo &amp;obj_grad_info) const </arglist>
    </member>
    <member kind="typedef">
      <type>Teuchos::RCP&lt; const VectorSpace &gt;</type>
      <name>vec_space_ptr_t</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a3535d4780d6a4eba0c25dd88809a624f</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Teuchos::RCP&lt; const OptionsFromStreamPack::OptionsFromStream &gt;</type>
      <name>options_ptr_t</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a8d3cfdcce6ee1e3c84d11ccfb1494ccb</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>NLPObjGrad</name>
      <anchorfile>classNLPInterfacePack_1_1NLPObjGrad.html</anchorfile>
      <anchor>afb95be53fd1fdbb2186d37a9b5c3d9fb</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>supports_Gf</name>
      <anchorfile>classNLPInterfacePack_1_1NLPObjGrad.html</anchorfile>
      <anchor>a00fac73b679fbb079883596b63c67548</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>supports_Gf_prod</name>
      <anchorfile>classNLPInterfacePack_1_1NLPObjGrad.html</anchorfile>
      <anchor>a36f0d690e23e2e64900ab9f9de9bfcc5</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>unset_quantities</name>
      <anchorfile>classNLPInterfacePack_1_1NLPObjGrad.html</anchorfile>
      <anchor>acaa369276df73f29fec14fb80971f919</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual value_type</type>
      <name>calc_Gf_prod</name>
      <anchorfile>classNLPInterfacePack_1_1NLPObjGrad.html</anchorfile>
      <anchor>a273cac12a3785f982c86f719c70ecf50</anchor>
      <arglist>(const Vector &amp;x, const Vector &amp;d, bool newx=true) const </arglist>
    </member>
    <member kind="function">
      <type>const ZeroOrderInfo</type>
      <name>zero_order_info</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a63e6b374a7c56bc74bcbf2b3baa655fa</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const ZeroOrderInfo</type>
      <name>zero_order_info_breve</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a4aea1f22eed001b847e7be0250e5311c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>NLP</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a8f9b7801c9c426d0e166935e2b02a5dc</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~NLP</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>afdee0ffed4b98701793d2d39762cc7fc</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>set_options</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>ab49bf8f5f809c9e9a1218951fe34f8d6</anchor>
      <arglist>(const options_ptr_t &amp;options)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const options_ptr_t &amp;</type>
      <name>get_options</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a6777671ee1d71404cd73b57c2560f2af</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" static="yes">
      <type>static value_type</type>
      <name>infinite_bound</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a1dc9592c25b467398848fbc6344a90e6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>const ObjGradInfo</type>
      <name>obj_grad_info</name>
      <anchorfile>classNLPInterfacePack_1_1NLPObjGrad.html</anchorfile>
      <anchor>acdab01aba51adc311c3e1b200121889c</anchor>
      <arglist>() const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>NLPInterfacePack::NLPSerialPreprocess</name>
    <filename>classNLPInterfacePack_1_1NLPSerialPreprocess.html</filename>
    <base virtualness="virtual">NLPInterfacePack::NLPObjGrad</base>
    <base virtualness="virtual">NLPInterfacePack::NLPVarReductPerm</base>
    <class kind="class">NLPInterfacePack::NLPSerialPreprocess::InconsistantBounds</class>
    <class kind="struct">NLPInterfacePack::NLPSerialPreprocess::ObjGradInfoSerial</class>
    <class kind="struct">NLPInterfacePack::NLPSerialPreprocess::ZeroOrderInfoSerial</class>
    <member kind="function">
      <type></type>
      <name>NLPSerialPreprocess</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocess.html</anchorfile>
      <anchor>aa9f32e52a01d3d91b885259bac9be41d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>NLPObjGrad</name>
      <anchorfile>classNLPInterfacePack_1_1NLPObjGrad.html</anchorfile>
      <anchor>afb95be53fd1fdbb2186d37a9b5c3d9fb</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>supports_Gf</name>
      <anchorfile>classNLPInterfacePack_1_1NLPObjGrad.html</anchorfile>
      <anchor>a00fac73b679fbb079883596b63c67548</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>supports_Gf_prod</name>
      <anchorfile>classNLPInterfacePack_1_1NLPObjGrad.html</anchorfile>
      <anchor>a36f0d690e23e2e64900ab9f9de9bfcc5</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>set_Gf</name>
      <anchorfile>classNLPInterfacePack_1_1NLPObjGrad.html</anchorfile>
      <anchor>a09d8aa18d9322bdc826961a79773e33c</anchor>
      <arglist>(VectorMutable *Gf)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual VectorMutable *</type>
      <name>get_Gf</name>
      <anchorfile>classNLPInterfacePack_1_1NLPObjGrad.html</anchorfile>
      <anchor>a005dc9e7d8ead6fd375c7e30ceb7c0ad</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual VectorMutable &amp;</type>
      <name>Gf</name>
      <anchorfile>classNLPInterfacePack_1_1NLPObjGrad.html</anchorfile>
      <anchor>a41a1c61f724ce5f0eefd6441e0d035be</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const Vector &amp;</type>
      <name>Gf</name>
      <anchorfile>classNLPInterfacePack_1_1NLPObjGrad.html</anchorfile>
      <anchor>ae62e281e6dcdb21ff58582e68bb16423</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>unset_quantities</name>
      <anchorfile>classNLPInterfacePack_1_1NLPObjGrad.html</anchorfile>
      <anchor>acaa369276df73f29fec14fb80971f919</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>calc_Gf</name>
      <anchorfile>classNLPInterfacePack_1_1NLPObjGrad.html</anchorfile>
      <anchor>aaa7e6bdc0ac3244bc2c32ce256c0fa78</anchor>
      <arglist>(const Vector &amp;x, bool newx=true) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual value_type</type>
      <name>calc_Gf_prod</name>
      <anchorfile>classNLPInterfacePack_1_1NLPObjGrad.html</anchorfile>
      <anchor>a273cac12a3785f982c86f719c70ecf50</anchor>
      <arglist>(const Vector &amp;x, const Vector &amp;d, bool newx=true) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual size_type</type>
      <name>num_Gf_evals</name>
      <anchorfile>classNLPInterfacePack_1_1NLPObjGrad.html</anchorfile>
      <anchor>af04320a39fe4a80c5c4cf8783483275a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" static="yes">
      <type>static value_type</type>
      <name>fixed_var_mult</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocess.html</anchorfile>
      <anchor>a8565a3c75f1e540f29046ea7e7226993</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>force_xinit_in_bounds</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocess.html</anchorfile>
      <anchor>a9ceb771f10914187afdd660799d184df</anchor>
      <arglist>(bool force_xinit_in_bounds)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>force_xinit_in_bounds</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocess.html</anchorfile>
      <anchor>aa7e3e3aee859f846490f1e1d967e25a6</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initialize</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocess.html</anchorfile>
      <anchor>a72799fe47c0112a5cd4ff7e5b84181dd</anchor>
      <arglist>(bool test_setup)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>is_initialized</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocess.html</anchorfile>
      <anchor>abb499cc5ece73f72b363f770da43292c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>size_type</type>
      <name>n</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocess.html</anchorfile>
      <anchor>a55d0a020a61bdef7f59798bedbc0da09</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>size_type</type>
      <name>m</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocess.html</anchorfile>
      <anchor>a9d2974df36955a66e86a6d0c1bc7aab1</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>vec_space_ptr_t</type>
      <name>space_x</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocess.html</anchorfile>
      <anchor>aaa9beb255243025ce48bcda57e2d0864</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>vec_space_ptr_t</type>
      <name>space_c</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocess.html</anchorfile>
      <anchor>a53e626be2cc678d8e7b8f6b753f98260</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>size_type</type>
      <name>num_bounded_x</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocess.html</anchorfile>
      <anchor>ab616e968676e072d35e656b9e1b3a0a5</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Vector &amp;</type>
      <name>xl</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocess.html</anchorfile>
      <anchor>a20251d583d585fdf14ebd0f0c0351d17</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Vector &amp;</type>
      <name>xu</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocess.html</anchorfile>
      <anchor>aec2c3370cb8cf24cb95719c5411c4588</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Vector &amp;</type>
      <name>xinit</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocess.html</anchorfile>
      <anchor>a4387dbc36369091c08be6a17ac4c022b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>get_init_lagrange_mult</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocess.html</anchorfile>
      <anchor>a4459d77f5e4565e6dbbdd8b1f5bb8a43</anchor>
      <arglist>(VectorMutable *lambda, VectorMutable *nu) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>scale_f</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocess.html</anchorfile>
      <anchor>acd6f4f5643eee9e14917c1375e74c102</anchor>
      <arglist>(value_type scale_f)</arglist>
    </member>
    <member kind="function">
      <type>value_type</type>
      <name>scale_f</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocess.html</anchorfile>
      <anchor>ab34ca10954b14dcbc05e665061903468</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>report_final_solution</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocess.html</anchorfile>
      <anchor>ac309339aab575282edd8bfe5f86bc204</anchor>
      <arglist>(const Vector &amp;x, const Vector *lambda, const Vector *nu, bool is_optimal)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual size_type</type>
      <name>ns</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocess.html</anchorfile>
      <anchor>af6b15084b027fa1fad4e645551bf28f6</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>vec_space_ptr_t</type>
      <name>space_c_breve</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocess.html</anchorfile>
      <anchor>a5d227ccf334f7dc5e504264b3d960d31</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>vec_space_ptr_t</type>
      <name>space_h_breve</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocess.html</anchorfile>
      <anchor>ab1351e6071c95e09ed12d746ca0126b0</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Vector &amp;</type>
      <name>hl_breve</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocess.html</anchorfile>
      <anchor>a5d3cb0ff330534cfdbb80a3e3d68801c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Vector &amp;</type>
      <name>hu_breve</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocess.html</anchorfile>
      <anchor>a9d6eb90b67fe0a418e27b5e85504021f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Permutation &amp;</type>
      <name>P_var</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocess.html</anchorfile>
      <anchor>a20ba9c457369b19e7505bde1c1fd191f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Permutation &amp;</type>
      <name>P_equ</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocess.html</anchorfile>
      <anchor>a3e244bc4e9233e0e7020262dce50034e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const perm_fcty_ptr_t</type>
      <name>factory_P_var</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocess.html</anchorfile>
      <anchor>ab3fc849051f53d63b51cfb98d82461cd</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const perm_fcty_ptr_t</type>
      <name>factory_P_equ</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocess.html</anchorfile>
      <anchor>a88cb6481b9065b75147bd448231fadeb</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Range1D</type>
      <name>var_dep</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocess.html</anchorfile>
      <anchor>a1dccd917ca8ce83b09a5dab3501146e5</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Range1D</type>
      <name>var_indep</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocess.html</anchorfile>
      <anchor>a8938a738d4fb03a87c5484846579dc92</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Range1D</type>
      <name>equ_decomp</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocess.html</anchorfile>
      <anchor>a736d489d799b4c499816ee9bc5984f25</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Range1D</type>
      <name>equ_undecomp</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocess.html</anchorfile>
      <anchor>a6e78e5efccd7c794bd3983b9632ae7ce</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>nlp_selects_basis</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocess.html</anchorfile>
      <anchor>ab6d1db5713720a9b04ade70c6a79e67c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>get_next_basis</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocess.html</anchorfile>
      <anchor>a28043cbdf05b1edbd132670e771079ef</anchor>
      <arglist>(Permutation *P_var, Range1D *var_dep, Permutation *P_equ, Range1D *equ_decomp)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_basis</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocess.html</anchorfile>
      <anchor>a879e7c31efd7a4a2b1228fdfa4b965be</anchor>
      <arglist>(const Permutation &amp;P_var, const Range1D &amp;var_dep, const Permutation *P_equ, const Range1D *equ_decomp)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>get_basis</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocess.html</anchorfile>
      <anchor>ae325e692ef304bde2d0404ebff3a21aa</anchor>
      <arglist>(Permutation *P_var, Range1D *var_dep, Permutation *P_equ, Range1D *equ_decomp) const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>imp_calc_f</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocess.html</anchorfile>
      <anchor>a2879df90045b1f18f5d3a33a103893ae</anchor>
      <arglist>(const Vector &amp;x, bool newx, const ZeroOrderInfo &amp;zero_order_info) const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>imp_calc_c</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocess.html</anchorfile>
      <anchor>ad444ffbdf7c551bf0e1cb8e42441466e</anchor>
      <arglist>(const Vector &amp;x, bool newx, const ZeroOrderInfo &amp;zero_order_info) const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>imp_calc_c_breve</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocess.html</anchorfile>
      <anchor>a4c41bb0493ee1f8890da6ba64d51585d</anchor>
      <arglist>(const Vector &amp;x, bool newx, const ZeroOrderInfo &amp;zero_order_info_breve) const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>imp_calc_h_breve</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocess.html</anchorfile>
      <anchor>a1a3847558535aae166dc1eb9c451e1c2</anchor>
      <arglist>(const Vector &amp;x, bool newx, const ZeroOrderInfo &amp;zero_order_info_breve) const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>imp_calc_Gf</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocess.html</anchorfile>
      <anchor>a4782315227ffbb712a9688d0823dc152</anchor>
      <arglist>(const Vector &amp;x, bool newx, const ObjGradInfo &amp;obj_grad_info) const </arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual bool</type>
      <name>imp_nlp_has_changed</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocess.html</anchorfile>
      <anchor>a840cb5c9468e7afb4e2ee1a495240145</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual size_type</type>
      <name>imp_n_orig</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocess.html</anchorfile>
      <anchor>acde0fe0565b801355d9516da6f9c992e</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual size_type</type>
      <name>imp_m_orig</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocess.html</anchorfile>
      <anchor>ab44625d03954e4203dbacd476475d902</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual size_type</type>
      <name>imp_mI_orig</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocess.html</anchorfile>
      <anchor>afeac2bb6085c1fda7defc6ee502aaf84</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual const DVectorSlice</type>
      <name>imp_xinit_orig</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocess.html</anchorfile>
      <anchor>a4c1ae3a2de35425f1f24d0bc34f25c7f</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual bool</type>
      <name>imp_has_var_bounds</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocess.html</anchorfile>
      <anchor>a12f7bb495b10dbb76c94c5fba7158d5f</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual const DVectorSlice</type>
      <name>imp_xl_orig</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocess.html</anchorfile>
      <anchor>a9cd984501ef80c1bbc09b14bb823da54</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual const DVectorSlice</type>
      <name>imp_xu_orig</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocess.html</anchorfile>
      <anchor>a29bf016d0b6f0d01e9e74d4792a70340</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual const DVectorSlice</type>
      <name>imp_hl_orig</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocess.html</anchorfile>
      <anchor>ad9694a7862a31c344cc752570895d444</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual const DVectorSlice</type>
      <name>imp_hu_orig</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocess.html</anchorfile>
      <anchor>a8925e76cf3c58f4d39d5e8176b117c88</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual void</type>
      <name>imp_calc_f_orig</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocess.html</anchorfile>
      <anchor>a0eb152ab58109cfccc852e3525299c70</anchor>
      <arglist>(const DVectorSlice &amp;x_full, bool newx, const ZeroOrderInfoSerial &amp;zero_order_info) const =0</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual void</type>
      <name>imp_calc_c_orig</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocess.html</anchorfile>
      <anchor>a2ac8d4e76900e5c90b6f00b9f2e6f966</anchor>
      <arglist>(const DVectorSlice &amp;x_full, bool newx, const ZeroOrderInfoSerial &amp;zero_order_info) const =0</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual void</type>
      <name>imp_calc_h_orig</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocess.html</anchorfile>
      <anchor>a47080202e269d9518ab4df45fdf9d9ad</anchor>
      <arglist>(const DVectorSlice &amp;x_full, bool newx, const ZeroOrderInfoSerial &amp;zero_order_info) const =0</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual void</type>
      <name>imp_calc_Gf_orig</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocess.html</anchorfile>
      <anchor>acd0ae358e5853ad539de0a0afb95e4b5</anchor>
      <arglist>(const DVectorSlice &amp;x_full, bool newx, const ObjGradInfoSerial &amp;obj_grad_info) const =0</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual bool</type>
      <name>imp_get_next_basis</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocess.html</anchorfile>
      <anchor>af20094352d70231f813c6c369fea7704</anchor>
      <arglist>(IVector *var_perm_full, IVector *equ_perm_full, size_type *rank_full, size_type *rank)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual void</type>
      <name>imp_report_orig_final_solution</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocess.html</anchorfile>
      <anchor>aae2cff233f7e4aeb68180c812f2776ff</anchor>
      <arglist>(const DVectorSlice &amp;x_full, const DVectorSlice *lambda_orig, const DVectorSlice *lambdaI_orig, const DVectorSlice *nu_orig, bool optimal)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>set_not_initialized</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocess.html</anchorfile>
      <anchor>acd00c736902e1169c37b6b22c9dcf1e1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>assert_initialized</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocess.html</anchorfile>
      <anchor>a6f1070e99fb23487b9872020913a5a69</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>set_x_full</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocess.html</anchorfile>
      <anchor>a2443b241a4fb43bc7e2d984632974065</anchor>
      <arglist>(const DVectorSlice &amp;x, bool newx, DVectorSlice *x_full) const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>DVectorSlice</type>
      <name>x_full</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocess.html</anchorfile>
      <anchor>ae39d25531af9ac99d7e54f9c1b37438e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>const ZeroOrderInfoSerial</type>
      <name>zero_order_orig_info</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocess.html</anchorfile>
      <anchor>a228b4d6479ffa7d34d89c1f78b31f284</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>const ObjGradInfoSerial</type>
      <name>obj_grad_orig_info</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocess.html</anchorfile>
      <anchor>a4691397f4989236bcda9a898b93b9792</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>const IVector &amp;</type>
      <name>var_remove_fixed_to_full</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocess.html</anchorfile>
      <anchor>a823ad9e6e86167dc36adeea070a9626e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>const IVector &amp;</type>
      <name>var_full_to_remove_fixed</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocess.html</anchorfile>
      <anchor>a7c0597ad65618159e7cf25e97956bbee</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>const IVector &amp;</type>
      <name>var_perm</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocess.html</anchorfile>
      <anchor>a535184f67578dbdcccc593e4334fdcae</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>const IVector &amp;</type>
      <name>equ_perm</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocess.html</anchorfile>
      <anchor>a96e24e2cfe816099d530550d6dd27a01</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>const IVector &amp;</type>
      <name>inv_equ_perm</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocess.html</anchorfile>
      <anchor>a3c21c284a637ff87c6122ffb160ec957</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>var_from_full</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocess.html</anchorfile>
      <anchor>a1933fe81d371f3084fd712a0535395ca</anchor>
      <arglist>(DVectorSlice::const_iterator vec_full, DVectorSlice::iterator vec) const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>var_to_full</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocess.html</anchorfile>
      <anchor>a38cc831eec1768060917553f012103a4</anchor>
      <arglist>(DVectorSlice::const_iterator vec, DVectorSlice::iterator vec_full) const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>equ_from_full</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocess.html</anchorfile>
      <anchor>a18e6e3016d7135a021a0971f9b73bdf2</anchor>
      <arglist>(const DVectorSlice &amp;c_orig, const DVectorSlice &amp;h_orig, const DVectorSlice &amp;s_orig, DVectorSlice *c_full) const </arglist>
    </member>
    <member kind="typedef">
      <type>Teuchos::RCP&lt; const VectorSpace &gt;</type>
      <name>vec_space_ptr_t</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a3535d4780d6a4eba0c25dd88809a624f</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Teuchos::RCP&lt; const OptionsFromStreamPack::OptionsFromStream &gt;</type>
      <name>options_ptr_t</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a8d3cfdcce6ee1e3c84d11ccfb1494ccb</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Teuchos::RCP&lt; const Teuchos::AbstractFactory&lt; Permutation &gt; &gt;</type>
      <name>perm_fcty_ptr_t</name>
      <anchorfile>classNLPInterfacePack_1_1NLPVarReductPerm.html</anchorfile>
      <anchor>aaf51d526f581c00339c4e2bdc5f44aba</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" protection="protected">
      <type>const ObjGradInfo</type>
      <name>obj_grad_info</name>
      <anchorfile>classNLPInterfacePack_1_1NLPObjGrad.html</anchorfile>
      <anchor>acdab01aba51adc311c3e1b200121889c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>assert_ref_set</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a737c913d13ca4e41a1ec25b371720bbc</anchor>
      <arglist>(T *p, std::string info) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>NLPInterfacePack::NLPSerialPreprocess::InconsistantBounds</name>
    <filename>classNLPInterfacePack_1_1NLPSerialPreprocess_1_1InconsistantBounds.html</filename>
  </compound>
  <compound kind="struct">
    <name>NLPInterfacePack::NLPSerialPreprocess::ObjGradInfoSerial</name>
    <filename>structNLPInterfacePack_1_1NLPSerialPreprocess_1_1ObjGradInfoSerial.html</filename>
    <member kind="function">
      <type></type>
      <name>ObjGradInfoSerial</name>
      <anchorfile>structNLPInterfacePack_1_1NLPSerialPreprocess_1_1ObjGradInfoSerial.html</anchorfile>
      <anchor>a87d5b49c44c37b4e07baeaa1aea27caf</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ObjGradInfoSerial</name>
      <anchorfile>structNLPInterfacePack_1_1NLPSerialPreprocess_1_1ObjGradInfoSerial.html</anchorfile>
      <anchor>a90e7c93be7421fca2fcea5958ffc44a2</anchor>
      <arglist>(DVector *Gf_in, const ZeroOrderInfoSerial &amp;first_order_info_in)</arglist>
    </member>
    <member kind="variable">
      <type>DVector *</type>
      <name>Gf</name>
      <anchorfile>structNLPInterfacePack_1_1NLPSerialPreprocess_1_1ObjGradInfoSerial.html</anchorfile>
      <anchor>a065bc8220ca1ff4ad9b6ee7063af8837</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>value_type *</type>
      <name>f</name>
      <anchorfile>structNLPInterfacePack_1_1NLPSerialPreprocess_1_1ObjGradInfoSerial.html</anchorfile>
      <anchor>aa2c7dcd3d38f35f494e8dd7a5eaaba7b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>DVector *</type>
      <name>c</name>
      <anchorfile>structNLPInterfacePack_1_1NLPSerialPreprocess_1_1ObjGradInfoSerial.html</anchorfile>
      <anchor>a3264916216b5d2e736dcec0a94922ccb</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>DVector *</type>
      <name>h</name>
      <anchorfile>structNLPInterfacePack_1_1NLPSerialPreprocess_1_1ObjGradInfoSerial.html</anchorfile>
      <anchor>a123f94645173efefe63514e7c247b4cc</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>NLPInterfacePack::NLPSerialPreprocess::ZeroOrderInfoSerial</name>
    <filename>structNLPInterfacePack_1_1NLPSerialPreprocess_1_1ZeroOrderInfoSerial.html</filename>
    <member kind="function">
      <type></type>
      <name>ZeroOrderInfoSerial</name>
      <anchorfile>structNLPInterfacePack_1_1NLPSerialPreprocess_1_1ZeroOrderInfoSerial.html</anchorfile>
      <anchor>a70311ac3b682a919a9a1a3fb095dba42</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ZeroOrderInfoSerial</name>
      <anchorfile>structNLPInterfacePack_1_1NLPSerialPreprocess_1_1ZeroOrderInfoSerial.html</anchorfile>
      <anchor>a45b961d50a554a5f49788f2bcf4230a3</anchor>
      <arglist>(value_type *f_in, DVector *c_in, DVector *h_in)</arglist>
    </member>
    <member kind="variable">
      <type>value_type *</type>
      <name>f</name>
      <anchorfile>structNLPInterfacePack_1_1NLPSerialPreprocess_1_1ZeroOrderInfoSerial.html</anchorfile>
      <anchor>a2303c3844b28805cc0d6f6f062b4cd7e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>DVector *</type>
      <name>c</name>
      <anchorfile>structNLPInterfacePack_1_1NLPSerialPreprocess_1_1ZeroOrderInfoSerial.html</anchorfile>
      <anchor>a0936aaf83d267fe17d59a015855c0199</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>DVector *</type>
      <name>h</name>
      <anchorfile>structNLPInterfacePack_1_1NLPSerialPreprocess_1_1ZeroOrderInfoSerial.html</anchorfile>
      <anchor>a785eb5f591e7af3a81bed645bb5422a7</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>NLPInterfacePack::NLPSerialPreprocessExplJac</name>
    <filename>classNLPInterfacePack_1_1NLPSerialPreprocessExplJac.html</filename>
    <base virtualness="virtual">NLPInterfacePack::NLPSerialPreprocess</base>
    <base virtualness="virtual">NLPInterfacePack::NLPFirstOrder</base>
    <class kind="struct">NLPInterfacePack::NLPSerialPreprocessExplJac::FirstOrderExplInfo</class>
    <member kind="typedef">
      <type>Teuchos::RCP&lt; const Teuchos::AbstractFactory&lt; MatrixOp &gt; &gt;</type>
      <name>factory_mat_ptr_t</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocessExplJac.html</anchorfile>
      <anchor>aa16493bdb1163b8bbecb00b43d9d9237</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_COMPOSITION_MEMBERS</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocessExplJac.html</anchorfile>
      <anchor>aba0402f5b107a204ab6df58661e4f796</anchor>
      <arglist>(BasisSystemFactory, basis_sys_fcty)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>NLPSerialPreprocessExplJac</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocessExplJac.html</anchorfile>
      <anchor>a785785ea6e04a66ec749510c564b73a9</anchor>
      <arglist>(const basis_sys_fcty_ptr_t &amp;basis_sys_fcty=Teuchos::rcp(new BasisSystemFactoryStd()), const factory_mat_ptr_t &amp;factory_Gc_full=Teuchos::null)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_factory_Gc_full</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocessExplJac.html</anchorfile>
      <anchor>a63baa64930664fddcd3a483161545a2d</anchor>
      <arglist>(const factory_mat_ptr_t &amp;factory_Gc_full)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_options</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocessExplJac.html</anchorfile>
      <anchor>a88ae700c5bb221edf0fd82c17a7127af</anchor>
      <arglist>(const options_ptr_t &amp;options)</arglist>
    </member>
    <member kind="function">
      <type>const options_ptr_t &amp;</type>
      <name>get_options</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocessExplJac.html</anchorfile>
      <anchor>aec794a8e0e96706c8629e02082273570</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initialize</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocessExplJac.html</anchorfile>
      <anchor>abf3ef349f66a3e69bd848f68dcef8efb</anchor>
      <arglist>(bool test_setup)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>is_initialized</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocessExplJac.html</anchorfile>
      <anchor>a2d0e083911e0d70388c2509cfdbed6e5</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const mat_fcty_ptr_t</type>
      <name>factory_Gc</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocessExplJac.html</anchorfile>
      <anchor>a7ee59855b47a6b1acc59a6b66160d4fd</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const basis_sys_ptr_t</type>
      <name>basis_sys</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocessExplJac.html</anchorfile>
      <anchor>ac074bfcfde07ae8ab774528f1a04bb91</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_Gc</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocessExplJac.html</anchorfile>
      <anchor>a5f37611a1fc44bc5e0a372bb6e83313a</anchor>
      <arglist>(MatrixOp *Gc)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>get_next_basis</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocessExplJac.html</anchorfile>
      <anchor>a520b0d61ec223cd0ca7df41c3c79cbfa</anchor>
      <arglist>(Permutation *P_var, Range1D *var_dep, Permutation *P_equ, Range1D *equ_decomp)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_basis</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocessExplJac.html</anchorfile>
      <anchor>a217ab95625f2954c8f1df894051b70ce</anchor>
      <arglist>(const Permutation &amp;P_var, const Range1D &amp;var_dep, const Permutation *P_equ, const Range1D *equ_decomp)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>imp_calc_Gc</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocessExplJac.html</anchorfile>
      <anchor>a39006944211ef8c94c9c3eda1a6a13b0</anchor>
      <arglist>(const Vector &amp;x, bool newx, const FirstOrderInfo &amp;first_order_info) const </arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual size_type</type>
      <name>imp_Gc_nz_orig</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocessExplJac.html</anchorfile>
      <anchor>a8188d37c3d9d69b19882c8249c6afb7b</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual size_type</type>
      <name>imp_Gh_nz_orig</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocessExplJac.html</anchorfile>
      <anchor>a6b49bbc51e934e87ddf5e7052d929542</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual void</type>
      <name>imp_calc_Gc_orig</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocessExplJac.html</anchorfile>
      <anchor>a1896bf23529ffc0fb28bbe64665462be</anchor>
      <arglist>(const DVectorSlice &amp;x_full, bool newx, const FirstOrderExplInfo &amp;first_order_expl_info) const =0</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual void</type>
      <name>imp_calc_Gh_orig</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocessExplJac.html</anchorfile>
      <anchor>a1bb47180ec014c05d153df652b613810</anchor>
      <arglist>(const DVectorSlice &amp;x_full, bool newx, const FirstOrderExplInfo &amp;first_order_expl_info) const =0</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>assert_initialized</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocessExplJac.html</anchorfile>
      <anchor>abbb816d30898366efe128517592cc441</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>const FirstOrderExplInfo</type>
      <name>first_order_expl_info</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocessExplJac.html</anchorfile>
      <anchor>a0d39898e3d13661202e1431823e202af</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="typedef">
      <type>Teuchos::RCP&lt; const VectorSpace &gt;</type>
      <name>vec_space_ptr_t</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a3535d4780d6a4eba0c25dd88809a624f</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Teuchos::RCP&lt; const OptionsFromStreamPack::OptionsFromStream &gt;</type>
      <name>options_ptr_t</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a8d3cfdcce6ee1e3c84d11ccfb1494ccb</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Teuchos::RCP&lt; const Teuchos::AbstractFactory&lt; Permutation &gt; &gt;</type>
      <name>perm_fcty_ptr_t</name>
      <anchorfile>classNLPInterfacePack_1_1NLPVarReductPerm.html</anchorfile>
      <anchor>aaf51d526f581c00339c4e2bdc5f44aba</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Teuchos::RCP&lt; const Teuchos::AbstractFactory&lt; MatrixOp &gt; &gt;</type>
      <name>mat_fcty_ptr_t</name>
      <anchorfile>classNLPInterfacePack_1_1NLPFirstOrder.html</anchorfile>
      <anchor>a02fc7fa49e2c4854a42435a0d67befd9</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Teuchos::RCP&lt; BasisSystem &gt;</type>
      <name>basis_sys_ptr_t</name>
      <anchorfile>classNLPInterfacePack_1_1NLPFirstOrder.html</anchorfile>
      <anchor>a8cd358a54058f52849d76e5f45a500a5</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>NLPSerialPreprocess</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocess.html</anchorfile>
      <anchor>aa9f32e52a01d3d91b885259bac9be41d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>force_xinit_in_bounds</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocess.html</anchorfile>
      <anchor>a9ceb771f10914187afdd660799d184df</anchor>
      <arglist>(bool force_xinit_in_bounds)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>force_xinit_in_bounds</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocess.html</anchorfile>
      <anchor>aa7e3e3aee859f846490f1e1d967e25a6</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>size_type</type>
      <name>n</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocess.html</anchorfile>
      <anchor>a55d0a020a61bdef7f59798bedbc0da09</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>size_type</type>
      <name>m</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocess.html</anchorfile>
      <anchor>a9d2974df36955a66e86a6d0c1bc7aab1</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>vec_space_ptr_t</type>
      <name>space_x</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocess.html</anchorfile>
      <anchor>aaa9beb255243025ce48bcda57e2d0864</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>vec_space_ptr_t</type>
      <name>space_c</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocess.html</anchorfile>
      <anchor>a53e626be2cc678d8e7b8f6b753f98260</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>size_type</type>
      <name>num_bounded_x</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocess.html</anchorfile>
      <anchor>ab616e968676e072d35e656b9e1b3a0a5</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Vector &amp;</type>
      <name>xl</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocess.html</anchorfile>
      <anchor>a20251d583d585fdf14ebd0f0c0351d17</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Vector &amp;</type>
      <name>xu</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocess.html</anchorfile>
      <anchor>aec2c3370cb8cf24cb95719c5411c4588</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Vector &amp;</type>
      <name>xinit</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocess.html</anchorfile>
      <anchor>a4387dbc36369091c08be6a17ac4c022b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>get_init_lagrange_mult</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocess.html</anchorfile>
      <anchor>a4459d77f5e4565e6dbbdd8b1f5bb8a43</anchor>
      <arglist>(VectorMutable *lambda, VectorMutable *nu) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>scale_f</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocess.html</anchorfile>
      <anchor>acd6f4f5643eee9e14917c1375e74c102</anchor>
      <arglist>(value_type scale_f)</arglist>
    </member>
    <member kind="function">
      <type>value_type</type>
      <name>scale_f</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocess.html</anchorfile>
      <anchor>ab34ca10954b14dcbc05e665061903468</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>report_final_solution</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocess.html</anchorfile>
      <anchor>ac309339aab575282edd8bfe5f86bc204</anchor>
      <arglist>(const Vector &amp;x, const Vector *lambda, const Vector *nu, bool is_optimal)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual size_type</type>
      <name>ns</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocess.html</anchorfile>
      <anchor>af6b15084b027fa1fad4e645551bf28f6</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>vec_space_ptr_t</type>
      <name>space_c_breve</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocess.html</anchorfile>
      <anchor>a5d227ccf334f7dc5e504264b3d960d31</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>vec_space_ptr_t</type>
      <name>space_h_breve</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocess.html</anchorfile>
      <anchor>ab1351e6071c95e09ed12d746ca0126b0</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Vector &amp;</type>
      <name>hl_breve</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocess.html</anchorfile>
      <anchor>a5d3cb0ff330534cfdbb80a3e3d68801c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Vector &amp;</type>
      <name>hu_breve</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocess.html</anchorfile>
      <anchor>a9d6eb90b67fe0a418e27b5e85504021f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Permutation &amp;</type>
      <name>P_var</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocess.html</anchorfile>
      <anchor>a20ba9c457369b19e7505bde1c1fd191f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Permutation &amp;</type>
      <name>P_equ</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocess.html</anchorfile>
      <anchor>a3e244bc4e9233e0e7020262dce50034e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const perm_fcty_ptr_t</type>
      <name>factory_P_var</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocess.html</anchorfile>
      <anchor>ab3fc849051f53d63b51cfb98d82461cd</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const perm_fcty_ptr_t</type>
      <name>factory_P_equ</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocess.html</anchorfile>
      <anchor>a88cb6481b9065b75147bd448231fadeb</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Range1D</type>
      <name>var_dep</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocess.html</anchorfile>
      <anchor>a1dccd917ca8ce83b09a5dab3501146e5</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Range1D</type>
      <name>var_indep</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocess.html</anchorfile>
      <anchor>a8938a738d4fb03a87c5484846579dc92</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Range1D</type>
      <name>equ_decomp</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocess.html</anchorfile>
      <anchor>a736d489d799b4c499816ee9bc5984f25</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Range1D</type>
      <name>equ_undecomp</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocess.html</anchorfile>
      <anchor>a6e78e5efccd7c794bd3983b9632ae7ce</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>nlp_selects_basis</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocess.html</anchorfile>
      <anchor>ab6d1db5713720a9b04ade70c6a79e67c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>get_basis</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocess.html</anchorfile>
      <anchor>ae325e692ef304bde2d0404ebff3a21aa</anchor>
      <arglist>(Permutation *P_var, Range1D *var_dep, Permutation *P_equ, Range1D *equ_decomp) const </arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>NLPFirstOrder</name>
      <anchorfile>classNLPInterfacePack_1_1NLPFirstOrder.html</anchorfile>
      <anchor>afed7a912a2155a48a337a88daf829e60</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual MatrixOp *</type>
      <name>get_Gc</name>
      <anchorfile>classNLPInterfacePack_1_1NLPFirstOrder.html</anchorfile>
      <anchor>a66c3fd41bacab73468e7a98816379152</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual MatrixOp &amp;</type>
      <name>Gc</name>
      <anchorfile>classNLPInterfacePack_1_1NLPFirstOrder.html</anchorfile>
      <anchor>a59909f2dc634431042ae5d6c368d1d33</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const MatrixOp &amp;</type>
      <name>Gc</name>
      <anchorfile>classNLPInterfacePack_1_1NLPFirstOrder.html</anchorfile>
      <anchor>a17c21c0c70c13ad9963a224d84d1dab7</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>unset_quantities</name>
      <anchorfile>classNLPInterfacePack_1_1NLPFirstOrder.html</anchorfile>
      <anchor>adcca065b45335f90bede49862c0c5440</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>calc_Gc</name>
      <anchorfile>classNLPInterfacePack_1_1NLPFirstOrder.html</anchorfile>
      <anchor>aaacfb01f36b86c239a3743cca5f1b01a</anchor>
      <arglist>(const Vector &amp;x, bool newx=true) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual size_type</type>
      <name>num_Gc_evals</name>
      <anchorfile>classNLPInterfacePack_1_1NLPFirstOrder.html</anchorfile>
      <anchor>a792e27c3d6a7b0db6bec63aa5772d32b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>NLPObjGrad</name>
      <anchorfile>classNLPInterfacePack_1_1NLPObjGrad.html</anchorfile>
      <anchor>afb95be53fd1fdbb2186d37a9b5c3d9fb</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>supports_Gf</name>
      <anchorfile>classNLPInterfacePack_1_1NLPObjGrad.html</anchorfile>
      <anchor>a00fac73b679fbb079883596b63c67548</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>supports_Gf_prod</name>
      <anchorfile>classNLPInterfacePack_1_1NLPObjGrad.html</anchorfile>
      <anchor>a36f0d690e23e2e64900ab9f9de9bfcc5</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>set_Gf</name>
      <anchorfile>classNLPInterfacePack_1_1NLPObjGrad.html</anchorfile>
      <anchor>a09d8aa18d9322bdc826961a79773e33c</anchor>
      <arglist>(VectorMutable *Gf)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual VectorMutable *</type>
      <name>get_Gf</name>
      <anchorfile>classNLPInterfacePack_1_1NLPObjGrad.html</anchorfile>
      <anchor>a005dc9e7d8ead6fd375c7e30ceb7c0ad</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual VectorMutable &amp;</type>
      <name>Gf</name>
      <anchorfile>classNLPInterfacePack_1_1NLPObjGrad.html</anchorfile>
      <anchor>a41a1c61f724ce5f0eefd6441e0d035be</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const Vector &amp;</type>
      <name>Gf</name>
      <anchorfile>classNLPInterfacePack_1_1NLPObjGrad.html</anchorfile>
      <anchor>ae62e281e6dcdb21ff58582e68bb16423</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>unset_quantities</name>
      <anchorfile>classNLPInterfacePack_1_1NLPObjGrad.html</anchorfile>
      <anchor>acaa369276df73f29fec14fb80971f919</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>calc_Gf</name>
      <anchorfile>classNLPInterfacePack_1_1NLPObjGrad.html</anchorfile>
      <anchor>aaa7e6bdc0ac3244bc2c32ce256c0fa78</anchor>
      <arglist>(const Vector &amp;x, bool newx=true) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual value_type</type>
      <name>calc_Gf_prod</name>
      <anchorfile>classNLPInterfacePack_1_1NLPObjGrad.html</anchorfile>
      <anchor>a273cac12a3785f982c86f719c70ecf50</anchor>
      <arglist>(const Vector &amp;x, const Vector &amp;d, bool newx=true) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual size_type</type>
      <name>num_Gf_evals</name>
      <anchorfile>classNLPInterfacePack_1_1NLPObjGrad.html</anchorfile>
      <anchor>af04320a39fe4a80c5c4cf8783483275a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const ZeroOrderInfo</type>
      <name>zero_order_info</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a63e6b374a7c56bc74bcbf2b3baa655fa</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const ZeroOrderInfo</type>
      <name>zero_order_info_breve</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a4aea1f22eed001b847e7be0250e5311c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>NLP</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a8f9b7801c9c426d0e166935e2b02a5dc</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~NLP</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>afdee0ffed4b98701793d2d39762cc7fc</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual value_type</type>
      <name>max_var_bounds_viol</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a8bafa89c9b8be0dcbe2c27d366997faa</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>set_f</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a980e823e4c910953086873ed61e34130</anchor>
      <arglist>(value_type *f)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual value_type *</type>
      <name>get_f</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a950451eaca0ea90ef61c7b0422b31fda</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual value_type &amp;</type>
      <name>f</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a738dd301d37fa7b79b30b42f2ea97d16</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const value_type &amp;</type>
      <name>f</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a22aa288b69b1e7f5b4e3ba100051cb1f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>set_c</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>ae7fada2f10f4c10640c462009462a748</anchor>
      <arglist>(VectorMutable *c)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual VectorMutable *</type>
      <name>get_c</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a9a19b89571ab8e44c0bfda3f9530b0c3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual VectorMutable &amp;</type>
      <name>c</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a5da9a90b212ce508fa2b608c4e6a6f80</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const Vector &amp;</type>
      <name>c</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a6aae6fadac3de67155a654fc04a15b34</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>calc_f</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>af1c8df0e7d52d8d0a6159136b5f2415f</anchor>
      <arglist>(const Vector &amp;x, bool newx=true) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>calc_c</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a90ef9d68922f0bdbc46ff1f283494e11</anchor>
      <arglist>(const Vector &amp;x, bool newx=true) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual size_type</type>
      <name>num_f_evals</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a684c04f1cbc049d9d626fa7604ee036a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual size_type</type>
      <name>num_c_evals</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a9ba6eabb94807b34d227ff897b1d2ee5</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>set_c_breve</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a2d07b59dd6f28551ced5a8ee136d3e4b</anchor>
      <arglist>(VectorMutable *c_breve)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual VectorMutable *</type>
      <name>get_c_breve</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a81d6461bcaad765712d6f1a95e7199c3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual VectorMutable &amp;</type>
      <name>c_breve</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a283f37b55d108f6b2c452696e944cf77</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const Vector &amp;</type>
      <name>c_breve</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a7e68ab062a6a057237fa135f17d0ba0e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>set_h_breve</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>aff16ae4eacdcbdcfedf4bb1cbd1bb633</anchor>
      <arglist>(VectorMutable *h_breve)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual VectorMutable *</type>
      <name>get_h_breve</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a596fb18f90a7e367eeb060ea2393879a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual VectorMutable &amp;</type>
      <name>h_breve</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a781936f02d0c72927f570635cc1cc0fb</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const Vector &amp;</type>
      <name>h_breve</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a0f32bff188894d3d868e0b4db9e22eaf</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>calc_c_breve</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>ad37e807d366cbd918b0115eceed942a2</anchor>
      <arglist>(const Vector &amp;x, bool newx=true) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>calc_h_breve</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a333edd6f0f9fa0e48059a683530b47e1</anchor>
      <arglist>(const Vector &amp;x, bool newx=true) const </arglist>
    </member>
    <member kind="function" static="yes">
      <type>static value_type</type>
      <name>fixed_var_mult</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocess.html</anchorfile>
      <anchor>a8565a3c75f1e540f29046ea7e7226993</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static value_type</type>
      <name>infinite_bound</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a1dc9592c25b467398848fbc6344a90e6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>imp_calc_f</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocess.html</anchorfile>
      <anchor>a2879df90045b1f18f5d3a33a103893ae</anchor>
      <arglist>(const Vector &amp;x, bool newx, const ZeroOrderInfo &amp;zero_order_info) const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>imp_calc_c</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocess.html</anchorfile>
      <anchor>ad444ffbdf7c551bf0e1cb8e42441466e</anchor>
      <arglist>(const Vector &amp;x, bool newx, const ZeroOrderInfo &amp;zero_order_info) const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>imp_calc_c_breve</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocess.html</anchorfile>
      <anchor>a4c41bb0493ee1f8890da6ba64d51585d</anchor>
      <arglist>(const Vector &amp;x, bool newx, const ZeroOrderInfo &amp;zero_order_info_breve) const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>imp_calc_h_breve</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocess.html</anchorfile>
      <anchor>a1a3847558535aae166dc1eb9c451e1c2</anchor>
      <arglist>(const Vector &amp;x, bool newx, const ZeroOrderInfo &amp;zero_order_info_breve) const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>imp_calc_Gf</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocess.html</anchorfile>
      <anchor>a4782315227ffbb712a9688d0823dc152</anchor>
      <arglist>(const Vector &amp;x, bool newx, const ObjGradInfo &amp;obj_grad_info) const </arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual bool</type>
      <name>imp_nlp_has_changed</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocess.html</anchorfile>
      <anchor>a840cb5c9468e7afb4e2ee1a495240145</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual size_type</type>
      <name>imp_n_orig</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocess.html</anchorfile>
      <anchor>acde0fe0565b801355d9516da6f9c992e</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual size_type</type>
      <name>imp_m_orig</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocess.html</anchorfile>
      <anchor>ab44625d03954e4203dbacd476475d902</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual size_type</type>
      <name>imp_mI_orig</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocess.html</anchorfile>
      <anchor>afeac2bb6085c1fda7defc6ee502aaf84</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual const DVectorSlice</type>
      <name>imp_xinit_orig</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocess.html</anchorfile>
      <anchor>a4c1ae3a2de35425f1f24d0bc34f25c7f</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual bool</type>
      <name>imp_has_var_bounds</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocess.html</anchorfile>
      <anchor>a12f7bb495b10dbb76c94c5fba7158d5f</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual const DVectorSlice</type>
      <name>imp_xl_orig</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocess.html</anchorfile>
      <anchor>a9cd984501ef80c1bbc09b14bb823da54</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual const DVectorSlice</type>
      <name>imp_xu_orig</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocess.html</anchorfile>
      <anchor>a29bf016d0b6f0d01e9e74d4792a70340</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual const DVectorSlice</type>
      <name>imp_hl_orig</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocess.html</anchorfile>
      <anchor>ad9694a7862a31c344cc752570895d444</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual const DVectorSlice</type>
      <name>imp_hu_orig</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocess.html</anchorfile>
      <anchor>a8925e76cf3c58f4d39d5e8176b117c88</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual void</type>
      <name>imp_calc_f_orig</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocess.html</anchorfile>
      <anchor>a0eb152ab58109cfccc852e3525299c70</anchor>
      <arglist>(const DVectorSlice &amp;x_full, bool newx, const ZeroOrderInfoSerial &amp;zero_order_info) const =0</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual void</type>
      <name>imp_calc_c_orig</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocess.html</anchorfile>
      <anchor>a2ac8d4e76900e5c90b6f00b9f2e6f966</anchor>
      <arglist>(const DVectorSlice &amp;x_full, bool newx, const ZeroOrderInfoSerial &amp;zero_order_info) const =0</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual void</type>
      <name>imp_calc_h_orig</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocess.html</anchorfile>
      <anchor>a47080202e269d9518ab4df45fdf9d9ad</anchor>
      <arglist>(const DVectorSlice &amp;x_full, bool newx, const ZeroOrderInfoSerial &amp;zero_order_info) const =0</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual void</type>
      <name>imp_calc_Gf_orig</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocess.html</anchorfile>
      <anchor>acd0ae358e5853ad539de0a0afb95e4b5</anchor>
      <arglist>(const DVectorSlice &amp;x_full, bool newx, const ObjGradInfoSerial &amp;obj_grad_info) const =0</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual bool</type>
      <name>imp_get_next_basis</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocess.html</anchorfile>
      <anchor>af20094352d70231f813c6c369fea7704</anchor>
      <arglist>(IVector *var_perm_full, IVector *equ_perm_full, size_type *rank_full, size_type *rank)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual void</type>
      <name>imp_report_orig_final_solution</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocess.html</anchorfile>
      <anchor>aae2cff233f7e4aeb68180c812f2776ff</anchor>
      <arglist>(const DVectorSlice &amp;x_full, const DVectorSlice *lambda_orig, const DVectorSlice *lambdaI_orig, const DVectorSlice *nu_orig, bool optimal)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>set_not_initialized</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocess.html</anchorfile>
      <anchor>acd00c736902e1169c37b6b22c9dcf1e1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>assert_initialized</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocess.html</anchorfile>
      <anchor>a6f1070e99fb23487b9872020913a5a69</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>set_x_full</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocess.html</anchorfile>
      <anchor>a2443b241a4fb43bc7e2d984632974065</anchor>
      <arglist>(const DVectorSlice &amp;x, bool newx, DVectorSlice *x_full) const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>DVectorSlice</type>
      <name>x_full</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocess.html</anchorfile>
      <anchor>ae39d25531af9ac99d7e54f9c1b37438e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>const ZeroOrderInfoSerial</type>
      <name>zero_order_orig_info</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocess.html</anchorfile>
      <anchor>a228b4d6479ffa7d34d89c1f78b31f284</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>const ObjGradInfoSerial</type>
      <name>obj_grad_orig_info</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocess.html</anchorfile>
      <anchor>a4691397f4989236bcda9a898b93b9792</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>const IVector &amp;</type>
      <name>var_remove_fixed_to_full</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocess.html</anchorfile>
      <anchor>a823ad9e6e86167dc36adeea070a9626e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>const IVector &amp;</type>
      <name>var_full_to_remove_fixed</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocess.html</anchorfile>
      <anchor>a7c0597ad65618159e7cf25e97956bbee</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>const IVector &amp;</type>
      <name>var_perm</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocess.html</anchorfile>
      <anchor>a535184f67578dbdcccc593e4334fdcae</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>const IVector &amp;</type>
      <name>equ_perm</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocess.html</anchorfile>
      <anchor>a96e24e2cfe816099d530550d6dd27a01</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>const IVector &amp;</type>
      <name>inv_equ_perm</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocess.html</anchorfile>
      <anchor>a3c21c284a637ff87c6122ffb160ec957</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>var_from_full</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocess.html</anchorfile>
      <anchor>a1933fe81d371f3084fd712a0535395ca</anchor>
      <arglist>(DVectorSlice::const_iterator vec_full, DVectorSlice::iterator vec) const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>var_to_full</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocess.html</anchorfile>
      <anchor>a38cc831eec1768060917553f012103a4</anchor>
      <arglist>(DVectorSlice::const_iterator vec, DVectorSlice::iterator vec_full) const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>equ_from_full</name>
      <anchorfile>classNLPInterfacePack_1_1NLPSerialPreprocess.html</anchorfile>
      <anchor>a18e6e3016d7135a021a0971f9b73bdf2</anchor>
      <arglist>(const DVectorSlice &amp;c_orig, const DVectorSlice &amp;h_orig, const DVectorSlice &amp;s_orig, DVectorSlice *c_full) const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>const ObjGradInfo</type>
      <name>obj_grad_info</name>
      <anchorfile>classNLPInterfacePack_1_1NLPObjGrad.html</anchorfile>
      <anchor>acdab01aba51adc311c3e1b200121889c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>assert_ref_set</name>
      <anchorfile>classNLPInterfacePack_1_1NLP.html</anchorfile>
      <anchor>a737c913d13ca4e41a1ec25b371720bbc</anchor>
      <arglist>(T *p, std::string info) const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>const FirstOrderInfo</type>
      <name>first_order_info</name>
      <anchorfile>classNLPInterfacePack_1_1NLPFirstOrder.html</anchorfile>
      <anchor>aed5b41c031d94f81306ba07ccabe23bb</anchor>
      <arglist>() const </arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>NLPInterfacePack::NLPSerialPreprocessExplJac::FirstOrderExplInfo</name>
    <filename>structNLPInterfacePack_1_1NLPSerialPreprocessExplJac_1_1FirstOrderExplInfo.html</filename>
    <member kind="typedef">
      <type>std::valarray&lt; value_type &gt;</type>
      <name>val_t</name>
      <anchorfile>structNLPInterfacePack_1_1NLPSerialPreprocessExplJac_1_1FirstOrderExplInfo.html</anchorfile>
      <anchor>a06d0203e0555a21ee96ccc8fdd520ee1</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::valarray&lt; index_type &gt;</type>
      <name>ivect_t</name>
      <anchorfile>structNLPInterfacePack_1_1NLPSerialPreprocessExplJac_1_1FirstOrderExplInfo.html</anchorfile>
      <anchor>abd37324a311a419fb9b9787b8de0abe9</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>FirstOrderExplInfo</name>
      <anchorfile>structNLPInterfacePack_1_1NLPSerialPreprocessExplJac_1_1FirstOrderExplInfo.html</anchorfile>
      <anchor>a0eef89c016d4e238efe39b30a42c7d36</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>FirstOrderExplInfo</name>
      <anchorfile>structNLPInterfacePack_1_1NLPSerialPreprocessExplJac_1_1FirstOrderExplInfo.html</anchorfile>
      <anchor>a6bd46fc408dfa0f3985cb02f306d1b18</anchor>
      <arglist>(index_type *Gc_nz_in, val_t *Gc_val_in, ivect_t *Gc_ivect_in, jvect_t *Gc_jvect_in, index_type *Gh_nz_in, val_t *Gh_val_in, ivect_t *Gh_ivect_in, jvect_t *Gh_jvect_in, const ObjGradInfoSerial &amp;obj_grad)</arglist>
    </member>
    <member kind="variable">
      <type>size_type *</type>
      <name>Gc_nz</name>
      <anchorfile>structNLPInterfacePack_1_1NLPSerialPreprocessExplJac_1_1FirstOrderExplInfo.html</anchorfile>
      <anchor>aed079145a17e0a7138cdfb597a197f93</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>val_t *</type>
      <name>Gc_val</name>
      <anchorfile>structNLPInterfacePack_1_1NLPSerialPreprocessExplJac_1_1FirstOrderExplInfo.html</anchorfile>
      <anchor>acee9bda1c0cd1e20cf561721f61d584b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>ivect_t *</type>
      <name>Gc_ivect</name>
      <anchorfile>structNLPInterfacePack_1_1NLPSerialPreprocessExplJac_1_1FirstOrderExplInfo.html</anchorfile>
      <anchor>a059245319b7646b52bd490033ea94315</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>jvect_t *</type>
      <name>Gc_jvect</name>
      <anchorfile>structNLPInterfacePack_1_1NLPSerialPreprocessExplJac_1_1FirstOrderExplInfo.html</anchorfile>
      <anchor>a6feb91c35f3ce5a065933e73c64340f2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>size_type *</type>
      <name>Gh_nz</name>
      <anchorfile>structNLPInterfacePack_1_1NLPSerialPreprocessExplJac_1_1FirstOrderExplInfo.html</anchorfile>
      <anchor>a50f484cdc26132a56fce514559122c25</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>val_t *</type>
      <name>Gh_val</name>
      <anchorfile>structNLPInterfacePack_1_1NLPSerialPreprocessExplJac_1_1FirstOrderExplInfo.html</anchorfile>
      <anchor>ab23c327561f7ffe953bad8436b3d5a6a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>ivect_t *</type>
      <name>Gh_ivect</name>
      <anchorfile>structNLPInterfacePack_1_1NLPSerialPreprocessExplJac_1_1FirstOrderExplInfo.html</anchorfile>
      <anchor>a90a34dcae4cfec724dc2316a67d9874f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>jvect_t *</type>
      <name>Gh_jvect</name>
      <anchorfile>structNLPInterfacePack_1_1NLPSerialPreprocessExplJac_1_1FirstOrderExplInfo.html</anchorfile>
      <anchor>a8476ac7c6e22005fcb6700725390a9ac</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>DVector *</type>
      <name>Gf</name>
      <anchorfile>structNLPInterfacePack_1_1NLPSerialPreprocessExplJac_1_1FirstOrderExplInfo.html</anchorfile>
      <anchor>aa55d44f56e9fd40b78e0a2775a688598</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>value_type *</type>
      <name>f</name>
      <anchorfile>structNLPInterfacePack_1_1NLPSerialPreprocessExplJac_1_1FirstOrderExplInfo.html</anchorfile>
      <anchor>a50cb8a6cea2260c4b9e2baadcf3b430e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>DVector *</type>
      <name>c</name>
      <anchorfile>structNLPInterfacePack_1_1NLPSerialPreprocessExplJac_1_1FirstOrderExplInfo.html</anchorfile>
      <anchor>a90d98669a274d99bcb9fe82ea827da49</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>DVector *</type>
      <name>h</name>
      <anchorfile>structNLPInterfacePack_1_1NLPSerialPreprocessExplJac_1_1FirstOrderExplInfo.html</anchorfile>
      <anchor>a08743a2b202eb4c1c267fe144209fa89</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="dir">
    <name>abstract</name>
    <path>/Users/sscoll/Downloads/trilinos-11.0.3-Source/packages/moocho/src/NLPInterfacePack/src/abstract/</path>
    <filename>dir_388452fc903004c8dc8078fcbf0348f8.html</filename>
    <dir>interfaces</dir>
    <dir>test</dir>
    <dir>tools</dir>
  </compound>
  <compound kind="dir">
    <name>interfaces</name>
    <path>/Users/sscoll/Downloads/trilinos-11.0.3-Source/packages/moocho/src/NLPInterfacePack/src/abstract/interfaces/</path>
    <filename>dir_cee4da53758d08afc07d0baa4ecfdb74.html</filename>
    <file>NLPInterfacePack_NLP.cpp</file>
    <file>NLPInterfacePack_NLP.hpp</file>
    <file>NLPInterfacePack_NLPDirect.cpp</file>
    <file>NLPInterfacePack_NLPDirect.hpp</file>
    <file>NLPInterfacePack_NLPFirstOrder.cpp</file>
    <file>NLPInterfacePack_NLPFirstOrder.hpp</file>
    <file>NLPInterfacePack_NLPObjGrad.cpp</file>
    <file>NLPInterfacePack_NLPObjGrad.hpp</file>
    <file>NLPInterfacePack_NLPSecondOrder.cpp</file>
    <file>NLPInterfacePack_NLPSecondOrder.hpp</file>
    <file>NLPInterfacePack_NLPVarReductPerm.hpp</file>
  </compound>
  <compound kind="dir">
    <name>NLPInterfacePack</name>
    <path>/Users/sscoll/Downloads/trilinos-11.0.3-Source/packages/moocho/src/NLPInterfacePack/</path>
    <filename>dir_daa046f46d8059be5b441b1bc5f39e46.html</filename>
    <dir>src</dir>
  </compound>
  <compound kind="dir">
    <name>serial</name>
    <path>/Users/sscoll/Downloads/trilinos-11.0.3-Source/packages/moocho/src/NLPInterfacePack/src/serial/</path>
    <filename>dir_1e8fec8cf667f2d4108ba05b8cf45771.html</filename>
    <file>NLPInterfacePack_NLPSerialPreprocess.cpp</file>
    <file>NLPInterfacePack_NLPSerialPreprocess.hpp</file>
    <file>NLPInterfacePack_NLPSerialPreprocessExplJac.cpp</file>
    <file>NLPInterfacePack_NLPSerialPreprocessExplJac.hpp</file>
  </compound>
  <compound kind="dir">
    <name>src</name>
    <path>/Users/sscoll/Downloads/trilinos-11.0.3-Source/packages/moocho/src/NLPInterfacePack/src/</path>
    <filename>dir_d0aa41d3e37f2fa573c84c6df62ea992.html</filename>
    <dir>abstract</dir>
    <dir>serial</dir>
    <file>NLPInterfacePack_Types.hpp</file>
  </compound>
  <compound kind="dir">
    <name>src</name>
    <path>/Users/sscoll/Downloads/trilinos-11.0.3-Source/packages/moocho/src/</path>
    <filename>dir_7bfd6931b65fca56728ca4076fbf2548.html</filename>
    <dir>NLPInterfacePack</dir>
  </compound>
  <compound kind="dir">
    <name>test</name>
    <path>/Users/sscoll/Downloads/trilinos-11.0.3-Source/packages/moocho/src/NLPInterfacePack/src/abstract/test/</path>
    <filename>dir_5bd0793f799ed2a7cd72650319605c8c.html</filename>
    <file>NLPInterfacePack_NLPDirectTester.cpp</file>
    <file>NLPInterfacePack_NLPDirectTester.hpp</file>
    <file>NLPInterfacePack_NLPDirectTesterSetOptions.cpp</file>
    <file>NLPInterfacePack_NLPDirectTesterSetOptions.hpp</file>
    <file>NLPInterfacePack_NLPFirstDerivTester.cpp</file>
    <file>NLPInterfacePack_NLPFirstDerivTester.hpp</file>
    <file>NLPInterfacePack_NLPFirstDerivTesterSetOptions.cpp</file>
    <file>NLPInterfacePack_NLPFirstDerivTesterSetOptions.hpp</file>
    <file>NLPInterfacePack_NLPTester.cpp</file>
    <file>NLPInterfacePack_NLPTester.hpp</file>
    <file>NLPInterfacePack_NLPTesterSetOptions.cpp</file>
    <file>NLPInterfacePack_NLPTesterSetOptions.hpp</file>
    <file>NLPInterfacePack_test_basis_system.cpp</file>
    <file>NLPInterfacePack_test_basis_system.hpp</file>
    <file>NLPInterfacePack_test_nlp_direct.cpp</file>
    <file>NLPInterfacePack_test_nlp_direct.hpp</file>
    <file>NLPInterfacePack_test_nlp_first_order.cpp</file>
    <file>NLPInterfacePack_test_nlp_first_order.hpp</file>
  </compound>
  <compound kind="dir">
    <name>tools</name>
    <path>/Users/sscoll/Downloads/trilinos-11.0.3-Source/packages/moocho/src/NLPInterfacePack/src/abstract/tools/</path>
    <filename>dir_f9167d6ec684a4b3a3e25f8be51bd4af.html</filename>
    <file>NLPInterfacePack_CalcFiniteDiffProd.cpp</file>
    <file>NLPInterfacePack_CalcFiniteDiffProd.hpp</file>
    <file>NLPInterfacePack_CalcFiniteDiffProdSetOptions.cpp</file>
    <file>NLPInterfacePack_CalcFiniteDiffProdSetOptions.hpp</file>
    <file>NLPInterfacePack_NLPBarrier.cpp</file>
    <file>NLPInterfacePack_NLPBarrier.hpp</file>
  </compound>
  <compound kind="page">
    <name>index</name>
    <title>NLPInterfacePack: C++ Interfaces and Implementation for Non-Linear Programs</title>
    <filename>index</filename>
  </compound>
</tagfile>
