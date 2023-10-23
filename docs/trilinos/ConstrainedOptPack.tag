<?xml version='1.0' encoding='UTF-8' standalone='yes' ?>
<tagfile>
  <compound kind="class">
    <name>ConstrainedOptPack::DecompositionSystem</name>
    <filename>classConstrainedOptPack_1_1DecompositionSystem.html</filename>
    <class kind="class">ConstrainedOptPack::DecompositionSystem::InvalidMatrixType</class>
    <class kind="class">ConstrainedOptPack::DecompositionSystem::SingularDecomposition</class>
    <class kind="class">ConstrainedOptPack::DecompositionSystem::TestFailed</class>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~DecompositionSystem</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystem.html</anchorfile>
      <anchor>a1d7ad1d94cccf0fdbce543457a58345b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="enumeration">
      <name>EOutputLevel</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystem.html</anchorfile>
      <anchor>a27eee53062a62baa44228ad45010bf3f</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>ERunTests</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystem.html</anchorfile>
      <anchor>a514857badaabb41f2c0bdce3be5079cf</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>EMatRelations</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystem.html</anchorfile>
      <anchor>a7c1dc404e7dd2ff50e0108a16d681576</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Teuchos::RCP&lt; const Teuchos::AbstractFactory&lt; MatrixOpNonsing &gt; &gt;</type>
      <name>mat_nonsing_fcty_ptr_t</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystem.html</anchorfile>
      <anchor>a94f446e30c331437fe358591719f6179</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Teuchos::RCP&lt; const Teuchos::AbstractFactory&lt; MatrixOp &gt; &gt;</type>
      <name>mat_fcty_ptr_t</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystem.html</anchorfile>
      <anchor>a116b9df2f42652c9e5f402988a8ae52d</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual size_type</type>
      <name>n</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystem.html</anchorfile>
      <anchor>a80e201b98d7405c5f77413d3a2d04213</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual size_type</type>
      <name>m</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystem.html</anchorfile>
      <anchor>a63c4ba31b6b41b0c8f5740896197804c</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual size_type</type>
      <name>r</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystem.html</anchorfile>
      <anchor>aa7bf734e440c56d7463917dc1f8e5b59</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual Range1D</type>
      <name>equ_decomp</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystem.html</anchorfile>
      <anchor>a127fdf35fff39735ef6272350f54e3db</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual Range1D</type>
      <name>equ_undecomp</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystem.html</anchorfile>
      <anchor>a63ef97262e8cbc69deb61770ef1c1a77</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual const VectorSpace::space_ptr_t</type>
      <name>space_range</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystem.html</anchorfile>
      <anchor>a77cd74df5db3ac64f34d1b5e7e66e07b</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual const VectorSpace::space_ptr_t</type>
      <name>space_null</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystem.html</anchorfile>
      <anchor>ae0a3943c4814c02ce268dee674a8d123</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual const mat_fcty_ptr_t</type>
      <name>factory_Z</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystem.html</anchorfile>
      <anchor>a1059aa89ac8fe485f42b8554261b2c8d</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual const mat_fcty_ptr_t</type>
      <name>factory_Y</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystem.html</anchorfile>
      <anchor>a13bcf47f857195331434b6ef7926494c</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual const mat_nonsing_fcty_ptr_t</type>
      <name>factory_R</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystem.html</anchorfile>
      <anchor>a93bfbb959b6d1a3c7ef410e26a7aa101</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual const mat_fcty_ptr_t</type>
      <name>factory_Uz</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystem.html</anchorfile>
      <anchor>a447b1df0477107c0c590a126a34a21ea</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual const mat_fcty_ptr_t</type>
      <name>factory_Uy</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystem.html</anchorfile>
      <anchor>a53e82952b05418e69c1090dc1f73e204</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>update_decomp</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystem.html</anchorfile>
      <anchor>aaf5dcbb723043c6d37b15de212c7eaf6</anchor>
      <arglist>(std::ostream *out, EOutputLevel olevel, ERunTests test_what, const MatrixOp &amp;Gc, MatrixOp *Z, MatrixOp *Y, MatrixOpNonsing *R, MatrixOp *Uz, MatrixOp *Vy, EMatRelations mat_rel=MATRICES_INDEP_IMPS) const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>print_update_decomp</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystem.html</anchorfile>
      <anchor>ab670429eaa9b2e5bc0340bfe2af3a2b1</anchor>
      <arglist>(std::ostream &amp;out, const std::string &amp;leading_str) const =0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ConstrainedOptPack::DecompositionSystem::InvalidMatrixType</name>
    <filename>classConstrainedOptPack_1_1DecompositionSystem_1_1InvalidMatrixType.html</filename>
  </compound>
  <compound kind="class">
    <name>ConstrainedOptPack::DecompositionSystem::SingularDecomposition</name>
    <filename>classConstrainedOptPack_1_1DecompositionSystem_1_1SingularDecomposition.html</filename>
  </compound>
  <compound kind="class">
    <name>ConstrainedOptPack::DecompositionSystem::TestFailed</name>
    <filename>classConstrainedOptPack_1_1DecompositionSystem_1_1TestFailed.html</filename>
  </compound>
  <compound kind="class">
    <name>ConstrainedOptPack::DecompositionSystemCoordinate</name>
    <filename>classConstrainedOptPack_1_1DecompositionSystemCoordinate.html</filename>
    <base>ConstrainedOptPack::DecompositionSystemVarReductImp</base>
    <member kind="function">
      <type></type>
      <name>DecompositionSystemCoordinate</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemCoordinate.html</anchorfile>
      <anchor>ac19db0aaac8b6988e2ddf2d653d74426</anchor>
      <arglist>(const VectorSpace::space_ptr_t &amp;space_x=Teuchos::null, const VectorSpace::space_ptr_t &amp;space_c=Teuchos::null, const basis_sys_ptr_t &amp;basis_sys=Teuchos::null, const basis_sys_tester_ptr_t &amp;basis_sys_tester=Teuchos::null, EExplicitImplicit D_imp=MAT_IMP_AUTO, EExplicitImplicit Uz_imp=MAT_IMP_AUTO)</arglist>
    </member>
    <member kind="function">
      <type>const mat_fcty_ptr_t</type>
      <name>factory_Y</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemCoordinate.html</anchorfile>
      <anchor>ad88f9b3f3f3bd43085a032f91358cf0e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const mat_nonsing_fcty_ptr_t</type>
      <name>factory_R</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemCoordinate.html</anchorfile>
      <anchor>a8f90bc02b5d828810b2e4226a85052c6</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const mat_fcty_ptr_t</type>
      <name>factory_Uy</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemCoordinate.html</anchorfile>
      <anchor>a4827514d6f889bb1161a76a448e4e64b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>mat_nonsing_fcty_ptr_t::element_type::obj_ptr_t</type>
      <name>uninitialize_matrices</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemCoordinate.html</anchorfile>
      <anchor>afef165e5bdefcc17c20e434712277d28</anchor>
      <arglist>(std::ostream *out, EOutputLevel olevel, MatrixOp *Y, MatrixOpNonsing *R, MatrixOp *Uy) const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>initialize_matrices</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemCoordinate.html</anchorfile>
      <anchor>a2dfdf26cdf37376a066313541c8df91e</anchor>
      <arglist>(std::ostream *out, EOutputLevel olevel, const mat_nonsing_fcty_ptr_t::element_type::obj_ptr_t &amp;C, const mat_fcty_ptr_t::element_type::obj_ptr_t &amp;D, MatrixOp *Y, MatrixOpNonsing *R, MatrixOp *Uy, EMatRelations mat_rel) const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>print_update_matrices</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemCoordinate.html</anchorfile>
      <anchor>ad1824b582fc231f0fcf758587ae20d1d</anchor>
      <arglist>(std::ostream &amp;out, const std::string &amp;leading_str) const </arglist>
    </member>
    <member kind="typedef">
      <type>DecompositionSystem</type>
      <name>inherited</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemVarReductImp.html</anchorfile>
      <anchor>a20f6c2a81370aa8dd2c13eff2fdd112c</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Teuchos::RCP&lt; const BasisSystem &gt;</type>
      <name>basis_sys_ptr_t</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemVarReductImp.html</anchorfile>
      <anchor>abf35edef6303101e99223bff3cf5723a</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>EExplicitImplicit</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemVarReduct.html</anchorfile>
      <anchor>a21b5eb0cfd0b56b8b73e12174bad131e</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>EOutputLevel</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystem.html</anchorfile>
      <anchor>a27eee53062a62baa44228ad45010bf3f</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>ERunTests</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystem.html</anchorfile>
      <anchor>a514857badaabb41f2c0bdce3be5079cf</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>EMatRelations</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystem.html</anchorfile>
      <anchor>a7c1dc404e7dd2ff50e0108a16d681576</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Teuchos::RCP&lt; const Teuchos::AbstractFactory&lt; MatrixOpNonsing &gt; &gt;</type>
      <name>mat_nonsing_fcty_ptr_t</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystem.html</anchorfile>
      <anchor>a94f446e30c331437fe358591719f6179</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Teuchos::RCP&lt; const Teuchos::AbstractFactory&lt; MatrixOp &gt; &gt;</type>
      <name>mat_fcty_ptr_t</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystem.html</anchorfile>
      <anchor>a116b9df2f42652c9e5f402988a8ae52d</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initialize</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemVarReductImp.html</anchorfile>
      <anchor>a9f3be25151f08641a948bcf69c40baa1</anchor>
      <arglist>(const VectorSpace::space_ptr_t &amp;space_x, const VectorSpace::space_ptr_t &amp;space_c, const basis_sys_ptr_t &amp;basis_sys)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_COMPOSITION_MEMBERS</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemVarReductImp.html</anchorfile>
      <anchor>aadcf606e7a78dd519c94b3b0234eb0ba</anchor>
      <arglist>(BasisSystemTester, basis_sys_tester)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>DecompositionSystemVarReductImp</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemVarReductImp.html</anchorfile>
      <anchor>a0ee90f39d71f78732840d0cfabecd4cc</anchor>
      <arglist>(const VectorSpace::space_ptr_t &amp;space_x, const VectorSpace::space_ptr_t &amp;space_c, const basis_sys_ptr_t &amp;basis_sys, const basis_sys_tester_ptr_t &amp;basis_sys_tester, EExplicitImplicit D_imp, EExplicitImplicit Uz_imp)</arglist>
    </member>
    <member kind="function">
      <type>const VectorSpace::space_ptr_t &amp;</type>
      <name>space_x</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemVarReductImp.html</anchorfile>
      <anchor>a6da483ed23eb6be35f0d111d1804b1d8</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const VectorSpace::space_ptr_t &amp;</type>
      <name>space_c</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemVarReductImp.html</anchorfile>
      <anchor>ad8315cce58d684705423b471db217c93</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const basis_sys_ptr_t &amp;</type>
      <name>basis_sys</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemVarReductImp.html</anchorfile>
      <anchor>a7bcb20c615c2f10272a04d0ad206ab0a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>get_basis_matrices</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemVarReductImp.html</anchorfile>
      <anchor>a9cff11b92f6f3597405c21f0067e3979</anchor>
      <arglist>(std::ostream *out, EOutputLevel olevel, ERunTests test_what, MatrixOp *Z, MatrixOp *Y, MatrixOpNonsing *R, MatrixOp *Uz, MatrixOp *Uy, Teuchos::RCP&lt; MatrixOpNonsing &gt; *C_ptr, Teuchos::RCP&lt; MatrixOp &gt; *D_ptr)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_basis_matrices</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemVarReductImp.html</anchorfile>
      <anchor>af3adf84cb815f1fd66179b0325e7431e</anchor>
      <arglist>(std::ostream *out, EOutputLevel olevel, ERunTests test_what, const Teuchos::RCP&lt; MatrixOpNonsing &gt; &amp;C_ptr, const Teuchos::RCP&lt; MatrixOp &gt; &amp;D_ptr, MatrixOp *Uz, const basis_sys_ptr_t &amp;basis_sys=Teuchos::null)</arglist>
    </member>
    <member kind="function">
      <type>EExplicitImplicit</type>
      <name>D_imp_used</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemVarReductImp.html</anchorfile>
      <anchor>a3b179c77eafcd18622e6b551f774380f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>size_type</type>
      <name>n</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemVarReductImp.html</anchorfile>
      <anchor>afc28cacbbed825c816ac211ce4770a3d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>size_type</type>
      <name>m</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemVarReductImp.html</anchorfile>
      <anchor>a7839c237d61770e00b43b9cc33e28786</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>size_type</type>
      <name>r</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemVarReductImp.html</anchorfile>
      <anchor>aae99c5e05746f847b21e0aac9ec070ab</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const VectorSpace::space_ptr_t</type>
      <name>space_range</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemVarReductImp.html</anchorfile>
      <anchor>a56f7df51c0541a8bbe571585349c1ac7</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const VectorSpace::space_ptr_t</type>
      <name>space_null</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemVarReductImp.html</anchorfile>
      <anchor>af52bad7a706c0bcf93985b7ac646cb68</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const mat_fcty_ptr_t</type>
      <name>factory_Z</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemVarReductImp.html</anchorfile>
      <anchor>accbbc8e9c4b266169c15ac1191be3c07</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const mat_fcty_ptr_t</type>
      <name>factory_Uz</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemVarReductImp.html</anchorfile>
      <anchor>a5184652dbdcacfff9eaa5732c03e752e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>update_decomp</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemVarReductImp.html</anchorfile>
      <anchor>a7f6c2ccb7c1814f902d647baafc4a803</anchor>
      <arglist>(std::ostream *out, EOutputLevel olevel, ERunTests test_what, const MatrixOp &amp;Gc, MatrixOp *Z, MatrixOp *Y, MatrixOpNonsing *R, MatrixOp *Uz, MatrixOp *Uy, EMatRelations mat_rel) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>print_update_decomp</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemVarReductImp.html</anchorfile>
      <anchor>a069d9d872b3c1571b381f47f5c915a7e</anchor>
      <arglist>(std::ostream &amp;out, const std::string &amp;leading_str) const </arglist>
    </member>
    <member kind="function">
      <type>Range1D</type>
      <name>var_indep</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemVarReductImp.html</anchorfile>
      <anchor>a111d24087131c164e5c0a32442c64b5e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Range1D</type>
      <name>var_dep</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemVarReductImp.html</anchorfile>
      <anchor>a75b2331f9f60be762713035a5fd3136b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual void</type>
      <name>update_D_imp_used</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemVarReductImp.html</anchorfile>
      <anchor>a29e9827dfe874a44a3ee7334af90fd7a</anchor>
      <arglist>(EExplicitImplicit *D_imp_used) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ConstrainedOptPack::DecompositionSystemOrthogonal</name>
    <filename>classConstrainedOptPack_1_1DecompositionSystemOrthogonal.html</filename>
    <base>ConstrainedOptPack::DecompositionSystemVarReductImp</base>
    <member kind="function">
      <type></type>
      <name>DecompositionSystemOrthogonal</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemOrthogonal.html</anchorfile>
      <anchor>a7624bc8af5909d375c55b877d6e54c7a</anchor>
      <arglist>(const VectorSpace::space_ptr_t &amp;space_x=Teuchos::null, const VectorSpace::space_ptr_t &amp;space_c=Teuchos::null, const basis_sys_ptr_t &amp;basis_sys=Teuchos::null, const basis_sys_tester_ptr_t &amp;basis_sys_tester=Teuchos::null, EExplicitImplicit D_imp=MAT_IMP_EXPLICIT, EExplicitImplicit Uz_imp=MAT_IMP_EXPLICIT)</arglist>
    </member>
    <member kind="function">
      <type>const mat_fcty_ptr_t</type>
      <name>factory_Y</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemOrthogonal.html</anchorfile>
      <anchor>a194aa91e5187cf4e8b9907f0e1021d17</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const mat_nonsing_fcty_ptr_t</type>
      <name>factory_R</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemOrthogonal.html</anchorfile>
      <anchor>a55107532ec6cf646618273076f42dc63</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const mat_fcty_ptr_t</type>
      <name>factory_Uy</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemOrthogonal.html</anchorfile>
      <anchor>aff7a9e9cc6aa18ca9deed18921219e1e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>update_D_imp_used</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemOrthogonal.html</anchorfile>
      <anchor>a519b520f6cddc509884286a1519b0c22</anchor>
      <arglist>(EExplicitImplicit *D_imp_used) const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>mat_nonsing_fcty_ptr_t::element_type::obj_ptr_t</type>
      <name>uninitialize_matrices</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemOrthogonal.html</anchorfile>
      <anchor>a4a5cc55735e95d2734000cdbd2fc6dfe</anchor>
      <arglist>(std::ostream *out, EOutputLevel olevel, MatrixOp *Y, MatrixOpNonsing *R, MatrixOp *Uy) const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>initialize_matrices</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemOrthogonal.html</anchorfile>
      <anchor>a1d71dee431ec055d6cdf7ecccbd3a883</anchor>
      <arglist>(std::ostream *out, EOutputLevel olevel, const mat_nonsing_fcty_ptr_t::element_type::obj_ptr_t &amp;C, const mat_fcty_ptr_t::element_type::obj_ptr_t &amp;D, MatrixOp *Y, MatrixOpNonsing *R, MatrixOp *Uy, EMatRelations mat_rel) const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>print_update_matrices</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemOrthogonal.html</anchorfile>
      <anchor>a29b37c7652236ec676e320e65bbc0fae</anchor>
      <arglist>(std::ostream &amp;out, const std::string &amp;leading_str) const </arglist>
    </member>
    <member kind="typedef">
      <type>DecompositionSystem</type>
      <name>inherited</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemVarReductImp.html</anchorfile>
      <anchor>a20f6c2a81370aa8dd2c13eff2fdd112c</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Teuchos::RCP&lt; const BasisSystem &gt;</type>
      <name>basis_sys_ptr_t</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemVarReductImp.html</anchorfile>
      <anchor>abf35edef6303101e99223bff3cf5723a</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>EExplicitImplicit</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemVarReduct.html</anchorfile>
      <anchor>a21b5eb0cfd0b56b8b73e12174bad131e</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>EOutputLevel</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystem.html</anchorfile>
      <anchor>a27eee53062a62baa44228ad45010bf3f</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>ERunTests</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystem.html</anchorfile>
      <anchor>a514857badaabb41f2c0bdce3be5079cf</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>EMatRelations</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystem.html</anchorfile>
      <anchor>a7c1dc404e7dd2ff50e0108a16d681576</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Teuchos::RCP&lt; const Teuchos::AbstractFactory&lt; MatrixOpNonsing &gt; &gt;</type>
      <name>mat_nonsing_fcty_ptr_t</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystem.html</anchorfile>
      <anchor>a94f446e30c331437fe358591719f6179</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Teuchos::RCP&lt; const Teuchos::AbstractFactory&lt; MatrixOp &gt; &gt;</type>
      <name>mat_fcty_ptr_t</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystem.html</anchorfile>
      <anchor>a116b9df2f42652c9e5f402988a8ae52d</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initialize</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemVarReductImp.html</anchorfile>
      <anchor>a9f3be25151f08641a948bcf69c40baa1</anchor>
      <arglist>(const VectorSpace::space_ptr_t &amp;space_x, const VectorSpace::space_ptr_t &amp;space_c, const basis_sys_ptr_t &amp;basis_sys)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_COMPOSITION_MEMBERS</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemVarReductImp.html</anchorfile>
      <anchor>aadcf606e7a78dd519c94b3b0234eb0ba</anchor>
      <arglist>(BasisSystemTester, basis_sys_tester)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>DecompositionSystemVarReductImp</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemVarReductImp.html</anchorfile>
      <anchor>a0ee90f39d71f78732840d0cfabecd4cc</anchor>
      <arglist>(const VectorSpace::space_ptr_t &amp;space_x, const VectorSpace::space_ptr_t &amp;space_c, const basis_sys_ptr_t &amp;basis_sys, const basis_sys_tester_ptr_t &amp;basis_sys_tester, EExplicitImplicit D_imp, EExplicitImplicit Uz_imp)</arglist>
    </member>
    <member kind="function">
      <type>const VectorSpace::space_ptr_t &amp;</type>
      <name>space_x</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemVarReductImp.html</anchorfile>
      <anchor>a6da483ed23eb6be35f0d111d1804b1d8</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const VectorSpace::space_ptr_t &amp;</type>
      <name>space_c</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemVarReductImp.html</anchorfile>
      <anchor>ad8315cce58d684705423b471db217c93</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const basis_sys_ptr_t &amp;</type>
      <name>basis_sys</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemVarReductImp.html</anchorfile>
      <anchor>a7bcb20c615c2f10272a04d0ad206ab0a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>get_basis_matrices</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemVarReductImp.html</anchorfile>
      <anchor>a9cff11b92f6f3597405c21f0067e3979</anchor>
      <arglist>(std::ostream *out, EOutputLevel olevel, ERunTests test_what, MatrixOp *Z, MatrixOp *Y, MatrixOpNonsing *R, MatrixOp *Uz, MatrixOp *Uy, Teuchos::RCP&lt; MatrixOpNonsing &gt; *C_ptr, Teuchos::RCP&lt; MatrixOp &gt; *D_ptr)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_basis_matrices</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemVarReductImp.html</anchorfile>
      <anchor>af3adf84cb815f1fd66179b0325e7431e</anchor>
      <arglist>(std::ostream *out, EOutputLevel olevel, ERunTests test_what, const Teuchos::RCP&lt; MatrixOpNonsing &gt; &amp;C_ptr, const Teuchos::RCP&lt; MatrixOp &gt; &amp;D_ptr, MatrixOp *Uz, const basis_sys_ptr_t &amp;basis_sys=Teuchos::null)</arglist>
    </member>
    <member kind="function">
      <type>EExplicitImplicit</type>
      <name>D_imp_used</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemVarReductImp.html</anchorfile>
      <anchor>a3b179c77eafcd18622e6b551f774380f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>size_type</type>
      <name>n</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemVarReductImp.html</anchorfile>
      <anchor>afc28cacbbed825c816ac211ce4770a3d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>size_type</type>
      <name>m</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemVarReductImp.html</anchorfile>
      <anchor>a7839c237d61770e00b43b9cc33e28786</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>size_type</type>
      <name>r</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemVarReductImp.html</anchorfile>
      <anchor>aae99c5e05746f847b21e0aac9ec070ab</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const VectorSpace::space_ptr_t</type>
      <name>space_range</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemVarReductImp.html</anchorfile>
      <anchor>a56f7df51c0541a8bbe571585349c1ac7</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const VectorSpace::space_ptr_t</type>
      <name>space_null</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemVarReductImp.html</anchorfile>
      <anchor>af52bad7a706c0bcf93985b7ac646cb68</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const mat_fcty_ptr_t</type>
      <name>factory_Z</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemVarReductImp.html</anchorfile>
      <anchor>accbbc8e9c4b266169c15ac1191be3c07</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const mat_fcty_ptr_t</type>
      <name>factory_Uz</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemVarReductImp.html</anchorfile>
      <anchor>a5184652dbdcacfff9eaa5732c03e752e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>update_decomp</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemVarReductImp.html</anchorfile>
      <anchor>a7f6c2ccb7c1814f902d647baafc4a803</anchor>
      <arglist>(std::ostream *out, EOutputLevel olevel, ERunTests test_what, const MatrixOp &amp;Gc, MatrixOp *Z, MatrixOp *Y, MatrixOpNonsing *R, MatrixOp *Uz, MatrixOp *Uy, EMatRelations mat_rel) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>print_update_decomp</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemVarReductImp.html</anchorfile>
      <anchor>a069d9d872b3c1571b381f47f5c915a7e</anchor>
      <arglist>(std::ostream &amp;out, const std::string &amp;leading_str) const </arglist>
    </member>
    <member kind="function">
      <type>Range1D</type>
      <name>var_indep</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemVarReductImp.html</anchorfile>
      <anchor>a111d24087131c164e5c0a32442c64b5e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Range1D</type>
      <name>var_dep</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemVarReductImp.html</anchorfile>
      <anchor>a75b2331f9f60be762713035a5fd3136b</anchor>
      <arglist>() const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ConstrainedOptPack::DecompositionSystemTester</name>
    <filename>classConstrainedOptPack_1_1DecompositionSystemTester.html</filename>
    <member kind="function">
      <type></type>
      <name>DecompositionSystemTester</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemTester.html</anchorfile>
      <anchor>a97f986c964e44a51262b802f1f08c59c</anchor>
      <arglist>(EPrintTestLevel print_tests=PRINT_NOT_SELECTED, bool dump_all=false, bool throw_exception=true, size_type num_random_tests=1, value_type mult_warning_tol=1e-14, value_type mult_error_tol=1e-8, value_type solve_warning_tol=1e-14, value_type solve_error_tol=1e-8)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>test_decomp_system</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemTester.html</anchorfile>
      <anchor>a9b163eda84f3e5a080c0b001941043aa</anchor>
      <arglist>(const DecompositionSystem &amp;decomp_sys, const MatrixOp &amp;Gc, const MatrixOp *Z, const MatrixOp *Y, const MatrixOpNonsing *R, const MatrixOp *Uz, const MatrixOp *Uy, std::ostream *out)</arglist>
    </member>
    <member kind="enumeration">
      <name>EPrintTestLevel</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemTester.html</anchorfile>
      <anchor>a7033b43d727061071583af2a2eda70c6</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>PRINT_NOT_SELECTED</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemTester.html</anchorfile>
      <anchor>a7033b43d727061071583af2a2eda70c6a88f7538eff49eae3f0122d7ebb8e38b6</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>PRINT_NONE</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemTester.html</anchorfile>
      <anchor>a7033b43d727061071583af2a2eda70c6a53c441e896bfe1c49bb6c11f81fa1432</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>PRINT_BASIC</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemTester.html</anchorfile>
      <anchor>a7033b43d727061071583af2a2eda70c6afd4d31788bad9d3a01ed6873f702b753</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>PRINT_MORE</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemTester.html</anchorfile>
      <anchor>a7033b43d727061071583af2a2eda70c6afcbebe37db43d750f614268cc44e0f69</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>PRINT_ALL</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemTester.html</anchorfile>
      <anchor>a7033b43d727061071583af2a2eda70c6a7477ad3b900a4120fd3a5f707bf7788e</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemTester.html</anchorfile>
      <anchor>afbde95fb336e4b2a110c6cd39fe0f755</anchor>
      <arglist>(EPrintTestLevel, print_tests)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemTester.html</anchorfile>
      <anchor>a85260f35ccd01a44a0c76ac90b81f98a</anchor>
      <arglist>(bool, dump_all)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemTester.html</anchorfile>
      <anchor>a012e1f81a33aa2eb70f5586cd43a1232</anchor>
      <arglist>(bool, throw_exception)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemTester.html</anchorfile>
      <anchor>a022ea36bf2a159ee72ddc19ed6600176</anchor>
      <arglist>(size_type, num_random_tests)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemTester.html</anchorfile>
      <anchor>a888934b532c79418c15b4322665f1c7e</anchor>
      <arglist>(value_type, mult_warning_tol)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemTester.html</anchorfile>
      <anchor>a25900892cd375a08b0b61dfd85276a7c</anchor>
      <arglist>(value_type, mult_error_tol)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemTester.html</anchorfile>
      <anchor>af2d9bae0287f072acfdfbb4c01afe707</anchor>
      <arglist>(value_type, solve_warning_tol)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemTester.html</anchorfile>
      <anchor>a88060060a101e85f12e09bc221a99513</anchor>
      <arglist>(value_type, solve_error_tol)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ConstrainedOptPack::DecompositionSystemTesterSetOptions</name>
    <filename>classConstrainedOptPack_1_1DecompositionSystemTesterSetOptions.html</filename>
    <base>OptionsFromStreamPack::SetOptionsFromStreamNode</base>
    <base>OptionsFromStreamPack::SetOptionsToTargetBase</base>
    <member kind="function">
      <type></type>
      <name>DecompositionSystemTesterSetOptions</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemTesterSetOptions.html</anchorfile>
      <anchor>a7a0129ae9d6efd4926994ec76888cb74</anchor>
      <arglist>(DecompositionSystemTester *target=0, const char opt_grp_name[]=&quot;DecompositionSystemTester&quot;)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>setOption</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemTesterSetOptions.html</anchorfile>
      <anchor>a59abb97e3a2bf1e36634a1299f170231</anchor>
      <arglist>(int option_num, const std::string &amp;option_value)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ConstrainedOptPack::DecompositionSystemVarReduct</name>
    <filename>classConstrainedOptPack_1_1DecompositionSystemVarReduct.html</filename>
    <base>ConstrainedOptPack::DecompositionSystem</base>
    <member kind="enumeration">
      <name>EExplicitImplicit</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemVarReduct.html</anchorfile>
      <anchor>a21b5eb0cfd0b56b8b73e12174bad131e</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemVarReduct.html</anchorfile>
      <anchor>aef673f16173f2f3ee7fb5cfba223cc92</anchor>
      <arglist>(EExplicitImplicit, D_imp)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemVarReduct.html</anchorfile>
      <anchor>ae5111facb6d3109d230fcbf002166325</anchor>
      <arglist>(EExplicitImplicit, Uz_imp)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>DecompositionSystemVarReduct</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemVarReduct.html</anchorfile>
      <anchor>abab67372a6ea18d7676879dc96c401a9</anchor>
      <arglist>(EExplicitImplicit D_imp=MAT_IMP_AUTO, EExplicitImplicit Uz_imp=MAT_IMP_AUTO)</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual Range1D</type>
      <name>var_indep</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemVarReduct.html</anchorfile>
      <anchor>a68bdac8ccb21f77d5c2c377b1f226232</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual Range1D</type>
      <name>var_dep</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemVarReduct.html</anchorfile>
      <anchor>a74d930ac4c4269568fd00b1092c66706</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="enumeration">
      <name>EOutputLevel</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystem.html</anchorfile>
      <anchor>a27eee53062a62baa44228ad45010bf3f</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>ERunTests</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystem.html</anchorfile>
      <anchor>a514857badaabb41f2c0bdce3be5079cf</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>EMatRelations</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystem.html</anchorfile>
      <anchor>a7c1dc404e7dd2ff50e0108a16d681576</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Teuchos::RCP&lt; const Teuchos::AbstractFactory&lt; MatrixOpNonsing &gt; &gt;</type>
      <name>mat_nonsing_fcty_ptr_t</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystem.html</anchorfile>
      <anchor>a94f446e30c331437fe358591719f6179</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Teuchos::RCP&lt; const Teuchos::AbstractFactory&lt; MatrixOp &gt; &gt;</type>
      <name>mat_fcty_ptr_t</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystem.html</anchorfile>
      <anchor>a116b9df2f42652c9e5f402988a8ae52d</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~DecompositionSystem</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystem.html</anchorfile>
      <anchor>a1d7ad1d94cccf0fdbce543457a58345b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual size_type</type>
      <name>n</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystem.html</anchorfile>
      <anchor>a80e201b98d7405c5f77413d3a2d04213</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual size_type</type>
      <name>m</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystem.html</anchorfile>
      <anchor>a63c4ba31b6b41b0c8f5740896197804c</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual size_type</type>
      <name>r</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystem.html</anchorfile>
      <anchor>aa7bf734e440c56d7463917dc1f8e5b59</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual Range1D</type>
      <name>equ_decomp</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystem.html</anchorfile>
      <anchor>a127fdf35fff39735ef6272350f54e3db</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual Range1D</type>
      <name>equ_undecomp</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystem.html</anchorfile>
      <anchor>a63ef97262e8cbc69deb61770ef1c1a77</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual const VectorSpace::space_ptr_t</type>
      <name>space_range</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystem.html</anchorfile>
      <anchor>a77cd74df5db3ac64f34d1b5e7e66e07b</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual const VectorSpace::space_ptr_t</type>
      <name>space_null</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystem.html</anchorfile>
      <anchor>ae0a3943c4814c02ce268dee674a8d123</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual const mat_fcty_ptr_t</type>
      <name>factory_Z</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystem.html</anchorfile>
      <anchor>a1059aa89ac8fe485f42b8554261b2c8d</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual const mat_fcty_ptr_t</type>
      <name>factory_Y</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystem.html</anchorfile>
      <anchor>a13bcf47f857195331434b6ef7926494c</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual const mat_nonsing_fcty_ptr_t</type>
      <name>factory_R</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystem.html</anchorfile>
      <anchor>a93bfbb959b6d1a3c7ef410e26a7aa101</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual const mat_fcty_ptr_t</type>
      <name>factory_Uz</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystem.html</anchorfile>
      <anchor>a447b1df0477107c0c590a126a34a21ea</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual const mat_fcty_ptr_t</type>
      <name>factory_Uy</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystem.html</anchorfile>
      <anchor>a53e82952b05418e69c1090dc1f73e204</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>update_decomp</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystem.html</anchorfile>
      <anchor>aaf5dcbb723043c6d37b15de212c7eaf6</anchor>
      <arglist>(std::ostream *out, EOutputLevel olevel, ERunTests test_what, const MatrixOp &amp;Gc, MatrixOp *Z, MatrixOp *Y, MatrixOpNonsing *R, MatrixOp *Uz, MatrixOp *Vy, EMatRelations mat_rel=MATRICES_INDEP_IMPS) const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>print_update_decomp</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystem.html</anchorfile>
      <anchor>ab670429eaa9b2e5bc0340bfe2af3a2b1</anchor>
      <arglist>(std::ostream &amp;out, const std::string &amp;leading_str) const =0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ConstrainedOptPack::DecompositionSystemVarReductImp</name>
    <filename>classConstrainedOptPack_1_1DecompositionSystemVarReductImp.html</filename>
    <base>ConstrainedOptPack::DecompositionSystemVarReduct</base>
    <member kind="function">
      <type>void</type>
      <name>initialize</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemVarReductImp.html</anchorfile>
      <anchor>a9f3be25151f08641a948bcf69c40baa1</anchor>
      <arglist>(const VectorSpace::space_ptr_t &amp;space_x, const VectorSpace::space_ptr_t &amp;space_c, const basis_sys_ptr_t &amp;basis_sys)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemVarReduct.html</anchorfile>
      <anchor>aef673f16173f2f3ee7fb5cfba223cc92</anchor>
      <arglist>(EExplicitImplicit, D_imp)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemVarReduct.html</anchorfile>
      <anchor>ae5111facb6d3109d230fcbf002166325</anchor>
      <arglist>(EExplicitImplicit, Uz_imp)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>DecompositionSystemVarReduct</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemVarReduct.html</anchorfile>
      <anchor>abab67372a6ea18d7676879dc96c401a9</anchor>
      <arglist>(EExplicitImplicit D_imp=MAT_IMP_AUTO, EExplicitImplicit Uz_imp=MAT_IMP_AUTO)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual void</type>
      <name>update_D_imp_used</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemVarReductImp.html</anchorfile>
      <anchor>a29e9827dfe874a44a3ee7334af90fd7a</anchor>
      <arglist>(EExplicitImplicit *D_imp_used) const </arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual mat_nonsing_fcty_ptr_t::element_type::obj_ptr_t</type>
      <name>uninitialize_matrices</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemVarReductImp.html</anchorfile>
      <anchor>a901e5a35dd3b663640779a37d7d4b2fc</anchor>
      <arglist>(std::ostream *out, EOutputLevel olevel, MatrixOp *Y, MatrixOpNonsing *R, MatrixOp *Uy) const =0</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual void</type>
      <name>initialize_matrices</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemVarReductImp.html</anchorfile>
      <anchor>a50e782260323ee46fb3eb2d4404c59f7</anchor>
      <arglist>(std::ostream *out, EOutputLevel olevel, const mat_nonsing_fcty_ptr_t::element_type::obj_ptr_t &amp;C_ptr, const mat_fcty_ptr_t::element_type::obj_ptr_t &amp;D_ptr, MatrixOp *Y, MatrixOpNonsing *R, MatrixOp *Uy, EMatRelations mat_rel) const =0</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual void</type>
      <name>print_update_matrices</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemVarReductImp.html</anchorfile>
      <anchor>a7556ac21b771ab65e6b719c27b768e0c</anchor>
      <arglist>(std::ostream &amp;out, const std::string &amp;leading_str) const =0</arglist>
    </member>
    <member kind="typedef">
      <type>DecompositionSystem</type>
      <name>inherited</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemVarReductImp.html</anchorfile>
      <anchor>a20f6c2a81370aa8dd2c13eff2fdd112c</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Teuchos::RCP&lt; const BasisSystem &gt;</type>
      <name>basis_sys_ptr_t</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemVarReductImp.html</anchorfile>
      <anchor>abf35edef6303101e99223bff3cf5723a</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_COMPOSITION_MEMBERS</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemVarReductImp.html</anchorfile>
      <anchor>aadcf606e7a78dd519c94b3b0234eb0ba</anchor>
      <arglist>(BasisSystemTester, basis_sys_tester)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>DecompositionSystemVarReductImp</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemVarReductImp.html</anchorfile>
      <anchor>a0ee90f39d71f78732840d0cfabecd4cc</anchor>
      <arglist>(const VectorSpace::space_ptr_t &amp;space_x, const VectorSpace::space_ptr_t &amp;space_c, const basis_sys_ptr_t &amp;basis_sys, const basis_sys_tester_ptr_t &amp;basis_sys_tester, EExplicitImplicit D_imp, EExplicitImplicit Uz_imp)</arglist>
    </member>
    <member kind="function">
      <type>const VectorSpace::space_ptr_t &amp;</type>
      <name>space_x</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemVarReductImp.html</anchorfile>
      <anchor>a6da483ed23eb6be35f0d111d1804b1d8</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const VectorSpace::space_ptr_t &amp;</type>
      <name>space_c</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemVarReductImp.html</anchorfile>
      <anchor>ad8315cce58d684705423b471db217c93</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const basis_sys_ptr_t &amp;</type>
      <name>basis_sys</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemVarReductImp.html</anchorfile>
      <anchor>a7bcb20c615c2f10272a04d0ad206ab0a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>get_basis_matrices</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemVarReductImp.html</anchorfile>
      <anchor>a9cff11b92f6f3597405c21f0067e3979</anchor>
      <arglist>(std::ostream *out, EOutputLevel olevel, ERunTests test_what, MatrixOp *Z, MatrixOp *Y, MatrixOpNonsing *R, MatrixOp *Uz, MatrixOp *Uy, Teuchos::RCP&lt; MatrixOpNonsing &gt; *C_ptr, Teuchos::RCP&lt; MatrixOp &gt; *D_ptr)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_basis_matrices</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemVarReductImp.html</anchorfile>
      <anchor>af3adf84cb815f1fd66179b0325e7431e</anchor>
      <arglist>(std::ostream *out, EOutputLevel olevel, ERunTests test_what, const Teuchos::RCP&lt; MatrixOpNonsing &gt; &amp;C_ptr, const Teuchos::RCP&lt; MatrixOp &gt; &amp;D_ptr, MatrixOp *Uz, const basis_sys_ptr_t &amp;basis_sys=Teuchos::null)</arglist>
    </member>
    <member kind="function">
      <type>EExplicitImplicit</type>
      <name>D_imp_used</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemVarReductImp.html</anchorfile>
      <anchor>a3b179c77eafcd18622e6b551f774380f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>size_type</type>
      <name>n</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemVarReductImp.html</anchorfile>
      <anchor>afc28cacbbed825c816ac211ce4770a3d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>size_type</type>
      <name>m</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemVarReductImp.html</anchorfile>
      <anchor>a7839c237d61770e00b43b9cc33e28786</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>size_type</type>
      <name>r</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemVarReductImp.html</anchorfile>
      <anchor>aae99c5e05746f847b21e0aac9ec070ab</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const VectorSpace::space_ptr_t</type>
      <name>space_range</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemVarReductImp.html</anchorfile>
      <anchor>a56f7df51c0541a8bbe571585349c1ac7</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const VectorSpace::space_ptr_t</type>
      <name>space_null</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemVarReductImp.html</anchorfile>
      <anchor>af52bad7a706c0bcf93985b7ac646cb68</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const mat_fcty_ptr_t</type>
      <name>factory_Z</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemVarReductImp.html</anchorfile>
      <anchor>accbbc8e9c4b266169c15ac1191be3c07</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const mat_fcty_ptr_t</type>
      <name>factory_Uz</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemVarReductImp.html</anchorfile>
      <anchor>a5184652dbdcacfff9eaa5732c03e752e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>update_decomp</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemVarReductImp.html</anchorfile>
      <anchor>a7f6c2ccb7c1814f902d647baafc4a803</anchor>
      <arglist>(std::ostream *out, EOutputLevel olevel, ERunTests test_what, const MatrixOp &amp;Gc, MatrixOp *Z, MatrixOp *Y, MatrixOpNonsing *R, MatrixOp *Uz, MatrixOp *Uy, EMatRelations mat_rel) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>print_update_decomp</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemVarReductImp.html</anchorfile>
      <anchor>a069d9d872b3c1571b381f47f5c915a7e</anchor>
      <arglist>(std::ostream &amp;out, const std::string &amp;leading_str) const </arglist>
    </member>
    <member kind="function">
      <type>Range1D</type>
      <name>var_indep</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemVarReductImp.html</anchorfile>
      <anchor>a111d24087131c164e5c0a32442c64b5e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Range1D</type>
      <name>var_dep</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemVarReductImp.html</anchorfile>
      <anchor>a75b2331f9f60be762713035a5fd3136b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="enumeration">
      <name>EExplicitImplicit</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemVarReduct.html</anchorfile>
      <anchor>a21b5eb0cfd0b56b8b73e12174bad131e</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>EOutputLevel</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystem.html</anchorfile>
      <anchor>a27eee53062a62baa44228ad45010bf3f</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>ERunTests</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystem.html</anchorfile>
      <anchor>a514857badaabb41f2c0bdce3be5079cf</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>EMatRelations</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystem.html</anchorfile>
      <anchor>a7c1dc404e7dd2ff50e0108a16d681576</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Teuchos::RCP&lt; const Teuchos::AbstractFactory&lt; MatrixOpNonsing &gt; &gt;</type>
      <name>mat_nonsing_fcty_ptr_t</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystem.html</anchorfile>
      <anchor>a94f446e30c331437fe358591719f6179</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Teuchos::RCP&lt; const Teuchos::AbstractFactory&lt; MatrixOp &gt; &gt;</type>
      <name>mat_fcty_ptr_t</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystem.html</anchorfile>
      <anchor>a116b9df2f42652c9e5f402988a8ae52d</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ConstrainedOptPack::DecompositionSystemVarReductPerm</name>
    <filename>classConstrainedOptPack_1_1DecompositionSystemVarReductPerm.html</filename>
    <base>ConstrainedOptPack::DecompositionSystemVarReduct</base>
    <member kind="typedef">
      <type>Teuchos::RCP&lt; const Teuchos::AbstractFactory&lt; Permutation &gt; &gt;</type>
      <name>perm_fcty_ptr_t</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemVarReductPerm.html</anchorfile>
      <anchor>adbc76fe427dac9ab914dce77d0cb8328</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>DecompositionSystemVarReductPerm</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemVarReductPerm.html</anchorfile>
      <anchor>ad01fdbba7eef9ed6591624bba3c393b9</anchor>
      <arglist>(EExplicitImplicit D_imp=MAT_IMP_AUTO, EExplicitImplicit Uz_imp=MAT_IMP_AUTO)</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual const perm_fcty_ptr_t</type>
      <name>factory_P_var</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemVarReductPerm.html</anchorfile>
      <anchor>a0e396598fa1182f18bf99b7398df6674</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual const perm_fcty_ptr_t</type>
      <name>factory_P_equ</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemVarReductPerm.html</anchorfile>
      <anchor>a14a64e874296a0de406e4ffedc4cf0ce</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>has_basis</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemVarReductPerm.html</anchorfile>
      <anchor>ab658374cd7d2fedff886979cd62c13b7</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>set_decomp</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemVarReductPerm.html</anchorfile>
      <anchor>ab033b1fe782173e3613f5bb5740824ef</anchor>
      <arglist>(std::ostream *out, EOutputLevel olevel, ERunTests test_what, const Permutation &amp;P_var, const Range1D &amp;var_dep, const Permutation *P_equ, const Range1D *equ_decomp, const MatrixOp &amp;Gc, MatrixOp *Z, MatrixOp *Y, MatrixOpNonsing *R, MatrixOp *Uz, MatrixOp *Uy, EMatRelations mat_rel=MATRICES_INDEP_IMPS)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>select_decomp</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemVarReductPerm.html</anchorfile>
      <anchor>a42c4caae41cfab616d7b375ccd349ac9</anchor>
      <arglist>(std::ostream *out, EOutputLevel olevel, ERunTests test_what, const Vector *nu, MatrixOp *Gc, Permutation *P_var, Range1D *var_dep, Permutation *P_equ, Range1D *equ_decomp, MatrixOp *Z, MatrixOp *Y, MatrixOpNonsing *R, MatrixOp *Uz, MatrixOp *Uy, EMatRelations mat_rel=MATRICES_INDEP_IMPS)=0</arglist>
    </member>
    <member kind="enumeration">
      <name>EExplicitImplicit</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemVarReduct.html</anchorfile>
      <anchor>a21b5eb0cfd0b56b8b73e12174bad131e</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>EOutputLevel</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystem.html</anchorfile>
      <anchor>a27eee53062a62baa44228ad45010bf3f</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>ERunTests</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystem.html</anchorfile>
      <anchor>a514857badaabb41f2c0bdce3be5079cf</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>EMatRelations</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystem.html</anchorfile>
      <anchor>a7c1dc404e7dd2ff50e0108a16d681576</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Teuchos::RCP&lt; const Teuchos::AbstractFactory&lt; MatrixOpNonsing &gt; &gt;</type>
      <name>mat_nonsing_fcty_ptr_t</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystem.html</anchorfile>
      <anchor>a94f446e30c331437fe358591719f6179</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Teuchos::RCP&lt; const Teuchos::AbstractFactory&lt; MatrixOp &gt; &gt;</type>
      <name>mat_fcty_ptr_t</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystem.html</anchorfile>
      <anchor>a116b9df2f42652c9e5f402988a8ae52d</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemVarReduct.html</anchorfile>
      <anchor>aef673f16173f2f3ee7fb5cfba223cc92</anchor>
      <arglist>(EExplicitImplicit, D_imp)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemVarReduct.html</anchorfile>
      <anchor>ae5111facb6d3109d230fcbf002166325</anchor>
      <arglist>(EExplicitImplicit, Uz_imp)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>DecompositionSystemVarReduct</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemVarReduct.html</anchorfile>
      <anchor>abab67372a6ea18d7676879dc96c401a9</anchor>
      <arglist>(EExplicitImplicit D_imp=MAT_IMP_AUTO, EExplicitImplicit Uz_imp=MAT_IMP_AUTO)</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual Range1D</type>
      <name>var_indep</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemVarReduct.html</anchorfile>
      <anchor>a68bdac8ccb21f77d5c2c377b1f226232</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual Range1D</type>
      <name>var_dep</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemVarReduct.html</anchorfile>
      <anchor>a74d930ac4c4269568fd00b1092c66706</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~DecompositionSystem</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystem.html</anchorfile>
      <anchor>a1d7ad1d94cccf0fdbce543457a58345b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual size_type</type>
      <name>n</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystem.html</anchorfile>
      <anchor>a80e201b98d7405c5f77413d3a2d04213</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual size_type</type>
      <name>m</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystem.html</anchorfile>
      <anchor>a63c4ba31b6b41b0c8f5740896197804c</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual size_type</type>
      <name>r</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystem.html</anchorfile>
      <anchor>aa7bf734e440c56d7463917dc1f8e5b59</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual Range1D</type>
      <name>equ_decomp</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystem.html</anchorfile>
      <anchor>a127fdf35fff39735ef6272350f54e3db</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual Range1D</type>
      <name>equ_undecomp</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystem.html</anchorfile>
      <anchor>a63ef97262e8cbc69deb61770ef1c1a77</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual const VectorSpace::space_ptr_t</type>
      <name>space_range</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystem.html</anchorfile>
      <anchor>a77cd74df5db3ac64f34d1b5e7e66e07b</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual const VectorSpace::space_ptr_t</type>
      <name>space_null</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystem.html</anchorfile>
      <anchor>ae0a3943c4814c02ce268dee674a8d123</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual const mat_fcty_ptr_t</type>
      <name>factory_Z</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystem.html</anchorfile>
      <anchor>a1059aa89ac8fe485f42b8554261b2c8d</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual const mat_fcty_ptr_t</type>
      <name>factory_Y</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystem.html</anchorfile>
      <anchor>a13bcf47f857195331434b6ef7926494c</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual const mat_nonsing_fcty_ptr_t</type>
      <name>factory_R</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystem.html</anchorfile>
      <anchor>a93bfbb959b6d1a3c7ef410e26a7aa101</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual const mat_fcty_ptr_t</type>
      <name>factory_Uz</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystem.html</anchorfile>
      <anchor>a447b1df0477107c0c590a126a34a21ea</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual const mat_fcty_ptr_t</type>
      <name>factory_Uy</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystem.html</anchorfile>
      <anchor>a53e82952b05418e69c1090dc1f73e204</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>update_decomp</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystem.html</anchorfile>
      <anchor>aaf5dcbb723043c6d37b15de212c7eaf6</anchor>
      <arglist>(std::ostream *out, EOutputLevel olevel, ERunTests test_what, const MatrixOp &amp;Gc, MatrixOp *Z, MatrixOp *Y, MatrixOpNonsing *R, MatrixOp *Uz, MatrixOp *Vy, EMatRelations mat_rel=MATRICES_INDEP_IMPS) const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>print_update_decomp</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystem.html</anchorfile>
      <anchor>ab670429eaa9b2e5bc0340bfe2af3a2b1</anchor>
      <arglist>(std::ostream &amp;out, const std::string &amp;leading_str) const =0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ConstrainedOptPack::DecompositionSystemVarReductPermStd</name>
    <filename>classConstrainedOptPack_1_1DecompositionSystemVarReductPermStd.html</filename>
    <base>ConstrainedOptPack::DecompositionSystemVarReductPerm</base>
    <member kind="typedef">
      <type>Teuchos::RCP&lt; DecompositionSystemVarReductImp &gt;</type>
      <name>decomp_sys_imp_ptr_t</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemVarReductPermStd.html</anchorfile>
      <anchor>a254333590dede75d6e32648bd6a4f0e3</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Teuchos::RCP&lt; BasisSystemPerm &gt;</type>
      <name>basis_sys_ptr_t</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemVarReductPermStd.html</anchorfile>
      <anchor>a5d4b32fc7620a1bf6896ca2db9ac58ed</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>DecompositionSystemVarReductPermStd</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemVarReductPermStd.html</anchorfile>
      <anchor>a8f8e4e969e68f8318eeb473dfa9049a3</anchor>
      <arglist>(const decomp_sys_imp_ptr_t &amp;decomp_sys_imp=Teuchos::null, const basis_sys_ptr_t &amp;basis_sys=Teuchos::null, bool basis_selected=false, EExplicitImplicit D_imp=MAT_IMP_AUTO, EExplicitImplicit Uz_imp=MAT_IMP_AUTO)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initialize</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemVarReductPermStd.html</anchorfile>
      <anchor>ab100c94c3d0209cce68c749bc8fc7a25</anchor>
      <arglist>(const decomp_sys_imp_ptr_t &amp;decomp_sys_imp, const basis_sys_ptr_t &amp;basis_sys, bool basis_selected=false, EExplicitImplicit D_imp=MAT_IMP_AUTO, EExplicitImplicit Uz_imp=MAT_IMP_AUTO)</arglist>
    </member>
    <member kind="function">
      <type>const decomp_sys_imp_ptr_t &amp;</type>
      <name>decomp_sys_imp</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemVarReductPermStd.html</anchorfile>
      <anchor>a3fab8ea083b61e7a529e46bb16f38792</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const basis_sys_ptr_t &amp;</type>
      <name>basis_sys</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemVarReductPermStd.html</anchorfile>
      <anchor>aa297a694921e27bd26b9b76cc526dcc3</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>size_type</type>
      <name>n</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemVarReductPermStd.html</anchorfile>
      <anchor>a95848e655efda1a25f3252cf9f8abc1e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>size_type</type>
      <name>m</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemVarReductPermStd.html</anchorfile>
      <anchor>a1f30bbdb00f1c7d6373a79039160925a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>size_type</type>
      <name>r</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemVarReductPermStd.html</anchorfile>
      <anchor>a050fd188144dbfb4fe3f16628b0c558b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Range1D</type>
      <name>equ_decomp</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemVarReductPermStd.html</anchorfile>
      <anchor>a63bb2b0a63a740b16f27f9b602b52c65</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Range1D</type>
      <name>equ_undecomp</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemVarReductPermStd.html</anchorfile>
      <anchor>aa41752358016c1b97cd7016058b7050a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const VectorSpace::space_ptr_t</type>
      <name>space_range</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemVarReductPermStd.html</anchorfile>
      <anchor>a51770499344f66b2cdcd6ca425610cd3</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const VectorSpace::space_ptr_t</type>
      <name>space_null</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemVarReductPermStd.html</anchorfile>
      <anchor>ac860073dddc2c6dc059a0bf4613e099b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const mat_fcty_ptr_t</type>
      <name>factory_Z</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemVarReductPermStd.html</anchorfile>
      <anchor>a1fccec5ef56bbcff61096706c4ed1c60</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const mat_fcty_ptr_t</type>
      <name>factory_Y</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemVarReductPermStd.html</anchorfile>
      <anchor>aa8957934a13393e5b645e975edee8945</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const mat_nonsing_fcty_ptr_t</type>
      <name>factory_R</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemVarReductPermStd.html</anchorfile>
      <anchor>a7c4af0a8fc764e44cd65b3f9304028aa</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const mat_fcty_ptr_t</type>
      <name>factory_Uz</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemVarReductPermStd.html</anchorfile>
      <anchor>a686be435eb8f67c466a2ec758e4590d9</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const mat_fcty_ptr_t</type>
      <name>factory_Uy</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemVarReductPermStd.html</anchorfile>
      <anchor>ae848f7679cb7a95179717ae3c7f0d1a7</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>update_decomp</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemVarReductPermStd.html</anchorfile>
      <anchor>ac01f1d919464e8e8e5f43a899b9fb7b0</anchor>
      <arglist>(std::ostream *out, EOutputLevel olevel, ERunTests test_what, const MatrixOp &amp;Gc, MatrixOp *Z, MatrixOp *Y, MatrixOpNonsing *R, MatrixOp *Uz, MatrixOp *Uy, EMatRelations mat_rel) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>print_update_decomp</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemVarReductPermStd.html</anchorfile>
      <anchor>a18f812c9f1c088973ef029ec870e7de6</anchor>
      <arglist>(std::ostream &amp;out, const std::string &amp;leading_str) const </arglist>
    </member>
    <member kind="function">
      <type>Range1D</type>
      <name>var_indep</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemVarReductPermStd.html</anchorfile>
      <anchor>ab9086670c21bbedd085f4577a6928535</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Range1D</type>
      <name>var_dep</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemVarReductPermStd.html</anchorfile>
      <anchor>a3bf6104d465e4b1a5fe6e3c2e86fb715</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const perm_fcty_ptr_t</type>
      <name>factory_P_var</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemVarReductPermStd.html</anchorfile>
      <anchor>a835e76cd2d32502a88ef52bc926a7b32</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const perm_fcty_ptr_t</type>
      <name>factory_P_equ</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemVarReductPermStd.html</anchorfile>
      <anchor>a1dd5310a19c390b3812216c98c7c87f9</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>has_basis</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemVarReductPermStd.html</anchorfile>
      <anchor>ae889bf1d07b42068528b271af9ac6e00</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_decomp</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemVarReductPermStd.html</anchorfile>
      <anchor>a4d073f2a2361e108558fea03fca5ae8f</anchor>
      <arglist>(std::ostream *out, EOutputLevel olevel, ERunTests test_what, const Permutation &amp;P_var, const Range1D &amp;var_dep, const Permutation *P_equ, const Range1D *equ_decomp, const MatrixOp &amp;Gc, MatrixOp *Z, MatrixOp *Y, MatrixOpNonsing *R, MatrixOp *Uz, MatrixOp *Uy, EMatRelations mat_rel)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>select_decomp</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemVarReductPermStd.html</anchorfile>
      <anchor>a3e10a25287fc76d646f21f23da77083e</anchor>
      <arglist>(std::ostream *out, EOutputLevel olevel, ERunTests test_what, const Vector *nu, MatrixOp *Gc, Permutation *P_var, Range1D *var_dep, Permutation *P_equ, Range1D *equ_decomp, MatrixOp *Z, MatrixOp *Y, MatrixOpNonsing *R, MatrixOp *Uz, MatrixOp *Uy, EMatRelations mat_rel)</arglist>
    </member>
    <member kind="typedef">
      <type>Teuchos::RCP&lt; const Teuchos::AbstractFactory&lt; Permutation &gt; &gt;</type>
      <name>perm_fcty_ptr_t</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemVarReductPerm.html</anchorfile>
      <anchor>adbc76fe427dac9ab914dce77d0cb8328</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>EExplicitImplicit</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemVarReduct.html</anchorfile>
      <anchor>a21b5eb0cfd0b56b8b73e12174bad131e</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>EOutputLevel</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystem.html</anchorfile>
      <anchor>a27eee53062a62baa44228ad45010bf3f</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>ERunTests</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystem.html</anchorfile>
      <anchor>a514857badaabb41f2c0bdce3be5079cf</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>EMatRelations</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystem.html</anchorfile>
      <anchor>a7c1dc404e7dd2ff50e0108a16d681576</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Teuchos::RCP&lt; const Teuchos::AbstractFactory&lt; MatrixOpNonsing &gt; &gt;</type>
      <name>mat_nonsing_fcty_ptr_t</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystem.html</anchorfile>
      <anchor>a94f446e30c331437fe358591719f6179</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Teuchos::RCP&lt; const Teuchos::AbstractFactory&lt; MatrixOp &gt; &gt;</type>
      <name>mat_fcty_ptr_t</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystem.html</anchorfile>
      <anchor>a116b9df2f42652c9e5f402988a8ae52d</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>DecompositionSystemVarReductPerm</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemVarReductPerm.html</anchorfile>
      <anchor>ad01fdbba7eef9ed6591624bba3c393b9</anchor>
      <arglist>(EExplicitImplicit D_imp=MAT_IMP_AUTO, EExplicitImplicit Uz_imp=MAT_IMP_AUTO)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemVarReduct.html</anchorfile>
      <anchor>aef673f16173f2f3ee7fb5cfba223cc92</anchor>
      <arglist>(EExplicitImplicit, D_imp)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemVarReduct.html</anchorfile>
      <anchor>ae5111facb6d3109d230fcbf002166325</anchor>
      <arglist>(EExplicitImplicit, Uz_imp)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>DecompositionSystemVarReduct</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystemVarReduct.html</anchorfile>
      <anchor>abab67372a6ea18d7676879dc96c401a9</anchor>
      <arglist>(EExplicitImplicit D_imp=MAT_IMP_AUTO, EExplicitImplicit Uz_imp=MAT_IMP_AUTO)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~DecompositionSystem</name>
      <anchorfile>classConstrainedOptPack_1_1DecompositionSystem.html</anchorfile>
      <anchor>a1d7ad1d94cccf0fdbce543457a58345b</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ConstrainedOptPack::DirectLineSearch_Strategy</name>
    <filename>classConstrainedOptPack_1_1DirectLineSearch__Strategy.html</filename>
    <class kind="class">ConstrainedOptPack::DirectLineSearch_Strategy::NotDescentDirection</class>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~DirectLineSearch_Strategy</name>
      <anchorfile>classConstrainedOptPack_1_1DirectLineSearch__Strategy.html</anchorfile>
      <anchor>a3e71effe66c96a9e9cd235daba4ee74d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>set_max_iter</name>
      <anchorfile>classConstrainedOptPack_1_1DirectLineSearch__Strategy.html</anchorfile>
      <anchor>a7ded6cfcbb2caefd526272bb723f00a0</anchor>
      <arglist>(int max_iter)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>max_iter</name>
      <anchorfile>classConstrainedOptPack_1_1DirectLineSearch__Strategy.html</anchorfile>
      <anchor>a70cb9b700c69e5795e1344d83b914c91</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>num_iterations</name>
      <anchorfile>classConstrainedOptPack_1_1DirectLineSearch__Strategy.html</anchorfile>
      <anchor>adb152454d251fc93773348013260d30f</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>do_line_search</name>
      <anchorfile>classConstrainedOptPack_1_1DirectLineSearch__Strategy.html</anchorfile>
      <anchor>ae2faea1397360c05b13703b487aca3e8</anchor>
      <arglist>(const MeritFuncCalc1D &amp;phi, value_type phi_k, value_type *alpha_k, value_type *phi_kp1, std::ostream *out=0)=0</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>print_algorithm</name>
      <anchorfile>classConstrainedOptPack_1_1DirectLineSearch__Strategy.html</anchorfile>
      <anchor>af54cf8fba36f78785afe056b4656aa3d</anchor>
      <arglist>(std::ostream &amp;out, const std::string &amp;leading_str) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ConstrainedOptPack::DirectLineSearch_Strategy::NotDescentDirection</name>
    <filename>classConstrainedOptPack_1_1DirectLineSearch__Strategy_1_1NotDescentDirection.html</filename>
  </compound>
  <compound kind="class">
    <name>ConstrainedOptPack::DirectLineSearchArmQuad_Strategy</name>
    <filename>classConstrainedOptPack_1_1DirectLineSearchArmQuad__Strategy.html</filename>
    <base>ConstrainedOptPack::DirectLineSearch_Strategy</base>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classConstrainedOptPack_1_1DirectLineSearchArmQuad__Strategy.html</anchorfile>
      <anchor>a7f1b43274f9a5f425a5b941c9b44d63c</anchor>
      <arglist>(value_type, eta)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classConstrainedOptPack_1_1DirectLineSearchArmQuad__Strategy.html</anchorfile>
      <anchor>a1444417e547197c6ea0cd5f5499be349</anchor>
      <arglist>(value_type, min_frac)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classConstrainedOptPack_1_1DirectLineSearchArmQuad__Strategy.html</anchorfile>
      <anchor>add855cbe9ff1c30b9e67a8be0c59c6b6</anchor>
      <arglist>(value_type, max_frac)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classConstrainedOptPack_1_1DirectLineSearchArmQuad__Strategy.html</anchorfile>
      <anchor>ae1533d0ffd21d0af3e3b1a16288827bc</anchor>
      <arglist>(bool, max_out_iter)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>DirectLineSearchArmQuad_Strategy</name>
      <anchorfile>classConstrainedOptPack_1_1DirectLineSearchArmQuad__Strategy.html</anchorfile>
      <anchor>a540f05bce2cecd128785f4946b64c5f1</anchor>
      <arglist>(int max_iter=20, value_type eta=1.0e-4, value_type min_frac=0.1, value_type max_frac=0.5, bool max_out_iter=false)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~DirectLineSearch_Strategy</name>
      <anchorfile>classConstrainedOptPack_1_1DirectLineSearch__Strategy.html</anchorfile>
      <anchor>a3e71effe66c96a9e9cd235daba4ee74d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_max_iter</name>
      <anchorfile>classConstrainedOptPack_1_1DirectLineSearchArmQuad__Strategy.html</anchorfile>
      <anchor>a841ba6cfcd762333b499d951c742f681</anchor>
      <arglist>(int max_iter)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>max_iter</name>
      <anchorfile>classConstrainedOptPack_1_1DirectLineSearchArmQuad__Strategy.html</anchorfile>
      <anchor>af30084f5d11ef95fa86d4703fb0771c5</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>num_iterations</name>
      <anchorfile>classConstrainedOptPack_1_1DirectLineSearchArmQuad__Strategy.html</anchorfile>
      <anchor>a93a00eaa6beed9ecd2c910989371d98e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>do_line_search</name>
      <anchorfile>classConstrainedOptPack_1_1DirectLineSearchArmQuad__Strategy.html</anchorfile>
      <anchor>a649c53e458bba86ff4e9d9023b0d0d88</anchor>
      <arglist>(const MeritFuncCalc1D &amp;phi, value_type phi_k, value_type *alpha_k, value_type *phi_kp1, std::ostream *out)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>print_algorithm</name>
      <anchorfile>classConstrainedOptPack_1_1DirectLineSearchArmQuad__Strategy.html</anchorfile>
      <anchor>a535a099b0e1a25a2e871ba18e91164e0</anchor>
      <arglist>(std::ostream &amp;out, const std::string &amp;leading_str) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ConstrainedOptPack::DirectLineSearchArmQuad_StrategySetOptions</name>
    <filename>classConstrainedOptPack_1_1DirectLineSearchArmQuad__StrategySetOptions.html</filename>
    <base>OptionsFromStreamPack::SetOptionsFromStreamNode</base>
    <base>OptionsFromStreamPack::SetOptionsToTargetBase</base>
    <member kind="function">
      <type></type>
      <name>DirectLineSearchArmQuad_StrategySetOptions</name>
      <anchorfile>classConstrainedOptPack_1_1DirectLineSearchArmQuad__StrategySetOptions.html</anchorfile>
      <anchor>af1fac67ecfc623e3c4a4ab8068d32e17</anchor>
      <arglist>(DirectLineSearchArmQuad_Strategy *qp_solver=0, const char opt_grp_name[]=&quot;DirectLineSearchArmQuad&quot;)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>setOption</name>
      <anchorfile>classConstrainedOptPack_1_1DirectLineSearchArmQuad__StrategySetOptions.html</anchorfile>
      <anchor>ae988dbf010d326f07dd17522cb2beeb0</anchor>
      <arglist>(int option_num, const std::string &amp;option_value)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ConstrainedOptPack::MeritFuncCalc</name>
    <filename>classConstrainedOptPack_1_1MeritFuncCalc.html</filename>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~MeritFuncCalc</name>
      <anchorfile>classConstrainedOptPack_1_1MeritFuncCalc.html</anchorfile>
      <anchor>a45faba7296da61294c38644e6fd4b9b4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual value_type</type>
      <name>operator()</name>
      <anchorfile>classConstrainedOptPack_1_1MeritFuncCalc.html</anchorfile>
      <anchor>ae24ce4803708f31847a2091b0d6a4a84</anchor>
      <arglist>(const Vector &amp;x) const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual value_type</type>
      <name>deriv</name>
      <anchorfile>classConstrainedOptPack_1_1MeritFuncCalc.html</anchorfile>
      <anchor>a284807cf9ceff10b7923b58c086f47c4</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>print_merit_func</name>
      <anchorfile>classConstrainedOptPack_1_1MeritFuncCalc.html</anchorfile>
      <anchor>a1a975fcb6105ecaa4c60213739169133</anchor>
      <arglist>(std::ostream &amp;out, const std::string &amp;leading_str) const =0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ConstrainedOptPack::MeritFuncCalc1D</name>
    <filename>classConstrainedOptPack_1_1MeritFuncCalc1D.html</filename>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~MeritFuncCalc1D</name>
      <anchorfile>classConstrainedOptPack_1_1MeritFuncCalc1D.html</anchorfile>
      <anchor>a87805ce6cef6c72382bac61bea736ed0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual value_type</type>
      <name>operator()</name>
      <anchorfile>classConstrainedOptPack_1_1MeritFuncCalc1D.html</anchorfile>
      <anchor>ac49d9089e8f305222ee6167f5178e080</anchor>
      <arglist>(value_type alpha) const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual value_type</type>
      <name>deriv</name>
      <anchorfile>classConstrainedOptPack_1_1MeritFuncCalc1D.html</anchorfile>
      <anchor>ae49d2775f6a2437715d25a99ecdfdc53</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>print_merit_func</name>
      <anchorfile>classConstrainedOptPack_1_1MeritFuncCalc1D.html</anchorfile>
      <anchor>ab562d5e0d8f2edb2f3f708c0d49a0fd3</anchor>
      <arglist>(std::ostream &amp;out, const std::string &amp;leading_str) const =0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ConstrainedOptPack::MeritFuncCalc1DQuadratic</name>
    <filename>classConstrainedOptPack_1_1MeritFuncCalc1DQuadratic.html</filename>
    <base>ConstrainedOptPack::MeritFuncCalc1D</base>
    <member kind="typedef">
      <type>const Vector *</type>
      <name>const_VectorWithOp_ptr</name>
      <anchorfile>classConstrainedOptPack_1_1MeritFuncCalc1DQuadratic.html</anchorfile>
      <anchor>a9d11fa4b32572c27c1b02bc5452d4943</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>MeritFuncCalc1DQuadratic</name>
      <anchorfile>classConstrainedOptPack_1_1MeritFuncCalc1DQuadratic.html</anchorfile>
      <anchor>acf2b67ba7bff8448512d30ef947ec449</anchor>
      <arglist>(const MeritFuncCalc &amp;phi, size_type p, const_VectorWithOp_ptr d[], VectorMutable *x)</arglist>
    </member>
    <member kind="function">
      <type>value_type</type>
      <name>operator()</name>
      <anchorfile>classConstrainedOptPack_1_1MeritFuncCalc1DQuadratic.html</anchorfile>
      <anchor>a54f763d84e8b3bedfbcf03dee1855d16</anchor>
      <arglist>(value_type alpha) const </arglist>
    </member>
    <member kind="function">
      <type>value_type</type>
      <name>deriv</name>
      <anchorfile>classConstrainedOptPack_1_1MeritFuncCalc1DQuadratic.html</anchorfile>
      <anchor>a9876a9e44b71984be3ec6f851c91c358</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>print_merit_func</name>
      <anchorfile>classConstrainedOptPack_1_1MeritFuncCalc1DQuadratic.html</anchorfile>
      <anchor>a989c5787a8bbcda6d6dc8bdce5d4750e</anchor>
      <arglist>(std::ostream &amp;out, const std::string &amp;leading_str) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~MeritFuncCalc1D</name>
      <anchorfile>classConstrainedOptPack_1_1MeritFuncCalc1D.html</anchorfile>
      <anchor>a87805ce6cef6c72382bac61bea736ed0</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ConstrainedOptPack::MeritFuncCalcNLE</name>
    <filename>classConstrainedOptPack_1_1MeritFuncCalcNLE.html</filename>
    <base>ConstrainedOptPack::MeritFuncCalc</base>
    <member kind="function">
      <type></type>
      <name>MeritFuncCalcNLE</name>
      <anchorfile>classConstrainedOptPack_1_1MeritFuncCalcNLE.html</anchorfile>
      <anchor>a7566c208e40401f00dfd49b8c167f1de</anchor>
      <arglist>(const MeritFuncNLE *phi=0, const NLP *nlp=0)</arglist>
    </member>
    <member kind="function">
      <type>value_type</type>
      <name>operator()</name>
      <anchorfile>classConstrainedOptPack_1_1MeritFuncCalcNLE.html</anchorfile>
      <anchor>ac62c95d787ada267deb046e291af7b3e</anchor>
      <arglist>(const Vector &amp;x) const </arglist>
    </member>
    <member kind="function">
      <type>value_type</type>
      <name>deriv</name>
      <anchorfile>classConstrainedOptPack_1_1MeritFuncCalcNLE.html</anchorfile>
      <anchor>ab2f627f64f47f94cc86b0c2ce2e2beb6</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>print_merit_func</name>
      <anchorfile>classConstrainedOptPack_1_1MeritFuncCalcNLE.html</anchorfile>
      <anchor>afe72a0e0b4c56d9cbb025b74d42c83b3</anchor>
      <arglist>(std::ostream &amp;out, const std::string &amp;leading_str) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~MeritFuncCalc</name>
      <anchorfile>classConstrainedOptPack_1_1MeritFuncCalc.html</anchorfile>
      <anchor>a45faba7296da61294c38644e6fd4b9b4</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ConstrainedOptPack::MeritFuncCalcNLP</name>
    <filename>classConstrainedOptPack_1_1MeritFuncCalcNLP.html</filename>
    <base>ConstrainedOptPack::MeritFuncCalc</base>
    <member kind="function">
      <type></type>
      <name>MeritFuncCalcNLP</name>
      <anchorfile>classConstrainedOptPack_1_1MeritFuncCalcNLP.html</anchorfile>
      <anchor>a34c12d346a511a8980fc8201f1ddd0cd</anchor>
      <arglist>(const MeritFuncNLP *phi=0, const NLP *nlp=0)</arglist>
    </member>
    <member kind="function">
      <type>value_type</type>
      <name>operator()</name>
      <anchorfile>classConstrainedOptPack_1_1MeritFuncCalcNLP.html</anchorfile>
      <anchor>a2d60606fda78a76f02cb7169735fff0e</anchor>
      <arglist>(const Vector &amp;x) const </arglist>
    </member>
    <member kind="function">
      <type>value_type</type>
      <name>deriv</name>
      <anchorfile>classConstrainedOptPack_1_1MeritFuncCalcNLP.html</anchorfile>
      <anchor>a53f12ecaa89b55aa300fdc239d04a21e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>print_merit_func</name>
      <anchorfile>classConstrainedOptPack_1_1MeritFuncCalcNLP.html</anchorfile>
      <anchor>a6bfb9a9f1c1cb60e98be19eb5fe68935</anchor>
      <arglist>(std::ostream &amp;out, const std::string &amp;leading_str) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~MeritFuncCalc</name>
      <anchorfile>classConstrainedOptPack_1_1MeritFuncCalc.html</anchorfile>
      <anchor>a45faba7296da61294c38644e6fd4b9b4</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ConstrainedOptPack::MeritFuncNLE</name>
    <filename>classConstrainedOptPack_1_1MeritFuncNLE.html</filename>
    <class kind="class">ConstrainedOptPack::MeritFuncNLE::InvalidInitialization</class>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~MeritFuncNLE</name>
      <anchorfile>classConstrainedOptPack_1_1MeritFuncNLE.html</anchorfile>
      <anchor>a0549a8de6c68f6a1367b4011f1e4e778</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual value_type</type>
      <name>value</name>
      <anchorfile>classConstrainedOptPack_1_1MeritFuncNLE.html</anchorfile>
      <anchor>ae37ea2fe584f5707e7ff643c0b614375</anchor>
      <arglist>(const Vector &amp;c) const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual value_type</type>
      <name>deriv</name>
      <anchorfile>classConstrainedOptPack_1_1MeritFuncNLE.html</anchorfile>
      <anchor>ac9cf46ec03a420855f602811d6bf1bca</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>print_merit_func</name>
      <anchorfile>classConstrainedOptPack_1_1MeritFuncNLE.html</anchorfile>
      <anchor>a969913912411888ff9bdaefeeedc925c</anchor>
      <arglist>(std::ostream &amp;out, const std::string &amp;leading_str) const =0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ConstrainedOptPack::MeritFuncNLE::InvalidInitialization</name>
    <filename>classConstrainedOptPack_1_1MeritFuncNLE_1_1InvalidInitialization.html</filename>
  </compound>
  <compound kind="class">
    <name>ConstrainedOptPack::MeritFuncNLESqrResid</name>
    <filename>classConstrainedOptPack_1_1MeritFuncNLESqrResid.html</filename>
    <base>ConstrainedOptPack::MeritFuncNLE</base>
    <member kind="function">
      <type></type>
      <name>MeritFuncNLESqrResid</name>
      <anchorfile>classConstrainedOptPack_1_1MeritFuncNLESqrResid.html</anchorfile>
      <anchor>ab8698fb6274e389114381ed9528aedde</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>value_type</type>
      <name>calc_deriv</name>
      <anchorfile>classConstrainedOptPack_1_1MeritFuncNLESqrResid.html</anchorfile>
      <anchor>afcc42fec329f1329a758528418d90d78</anchor>
      <arglist>(const Vector &amp;c_k)</arglist>
    </member>
    <member kind="function">
      <type>value_type</type>
      <name>value</name>
      <anchorfile>classConstrainedOptPack_1_1MeritFuncNLESqrResid.html</anchorfile>
      <anchor>ad3d9aea3b7f0f11a7e5fdc7f3f3f13aa</anchor>
      <arglist>(const Vector &amp;c) const </arglist>
    </member>
    <member kind="function">
      <type>value_type</type>
      <name>deriv</name>
      <anchorfile>classConstrainedOptPack_1_1MeritFuncNLESqrResid.html</anchorfile>
      <anchor>ab7dc44ec2b877ca42ccb4a1477484c74</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>print_merit_func</name>
      <anchorfile>classConstrainedOptPack_1_1MeritFuncNLESqrResid.html</anchorfile>
      <anchor>a9809213bad391dd82543eeabde9cdecd</anchor>
      <arglist>(std::ostream &amp;out, const std::string &amp;leading_str) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~MeritFuncNLE</name>
      <anchorfile>classConstrainedOptPack_1_1MeritFuncNLE.html</anchorfile>
      <anchor>a0549a8de6c68f6a1367b4011f1e4e778</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ConstrainedOptPack::MeritFuncNLP</name>
    <filename>classConstrainedOptPack_1_1MeritFuncNLP.html</filename>
    <class kind="class">ConstrainedOptPack::MeritFuncNLP::InvalidInitialization</class>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~MeritFuncNLP</name>
      <anchorfile>classConstrainedOptPack_1_1MeritFuncNLP.html</anchorfile>
      <anchor>acbc3c6fb1a0911ae952b8dc8b3c56061</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual MeritFuncNLP &amp;</type>
      <name>operator=</name>
      <anchorfile>classConstrainedOptPack_1_1MeritFuncNLP.html</anchorfile>
      <anchor>afc7c7ee110a59201239d22d2af350aae</anchor>
      <arglist>(const MeritFuncNLP &amp;)</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual value_type</type>
      <name>value</name>
      <anchorfile>classConstrainedOptPack_1_1MeritFuncNLP.html</anchorfile>
      <anchor>aa76c14766bc7ffd94a8d9789b4527d2b</anchor>
      <arglist>(value_type f, const Vector *c, const Vector *h, const Vector *hl, const Vector *hu) const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual value_type</type>
      <name>deriv</name>
      <anchorfile>classConstrainedOptPack_1_1MeritFuncNLP.html</anchorfile>
      <anchor>acc0d148732d7be3aebc3ddeb73791fd7</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>print_merit_func</name>
      <anchorfile>classConstrainedOptPack_1_1MeritFuncNLP.html</anchorfile>
      <anchor>add1929d1f496ab6093ebcecf1f0f4e56</anchor>
      <arglist>(std::ostream &amp;out, const std::string &amp;leading_str) const =0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ConstrainedOptPack::MeritFuncNLP::InvalidInitialization</name>
    <filename>classConstrainedOptPack_1_1MeritFuncNLP_1_1InvalidInitialization.html</filename>
  </compound>
  <compound kind="class">
    <name>ConstrainedOptPack::MeritFuncNLPDirecDeriv</name>
    <filename>classConstrainedOptPack_1_1MeritFuncNLPDirecDeriv.html</filename>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~MeritFuncNLPDirecDeriv</name>
      <anchorfile>classConstrainedOptPack_1_1MeritFuncNLPDirecDeriv.html</anchorfile>
      <anchor>a3cec11782cbbca1a2405a6bc84eb923f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual value_type</type>
      <name>calc_deriv</name>
      <anchorfile>classConstrainedOptPack_1_1MeritFuncNLPDirecDeriv.html</anchorfile>
      <anchor>af66985f522359a6fcfbf2be40b65895a</anchor>
      <arglist>(const Vector &amp;Gf_k, const Vector *c_k, const Vector *h_k, const Vector *hl, const Vector *hu, const Vector &amp;d_k)=0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ConstrainedOptPack::MeritFuncNLPL1</name>
    <filename>classConstrainedOptPack_1_1MeritFuncNLPL1.html</filename>
    <base>ConstrainedOptPack::MeritFuncNLP</base>
    <base>ConstrainedOptPack::MeritFuncNLPDirecDeriv</base>
    <base>ConstrainedOptPack::MeritFuncPenaltyParam</base>
    <member kind="function">
      <type></type>
      <name>MeritFuncNLPL1</name>
      <anchorfile>classConstrainedOptPack_1_1MeritFuncNLPL1.html</anchorfile>
      <anchor>a0b21571ad66d0ae6e39c7096473e70fb</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~MeritFuncNLP</name>
      <anchorfile>classConstrainedOptPack_1_1MeritFuncNLP.html</anchorfile>
      <anchor>acbc3c6fb1a0911ae952b8dc8b3c56061</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~MeritFuncNLPDirecDeriv</name>
      <anchorfile>classConstrainedOptPack_1_1MeritFuncNLPDirecDeriv.html</anchorfile>
      <anchor>a3cec11782cbbca1a2405a6bc84eb923f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~MeritFuncPenaltyParam</name>
      <anchorfile>classConstrainedOptPack_1_1MeritFuncPenaltyParam.html</anchorfile>
      <anchor>a8220e6b7248b42bc992809073e629308</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>MeritFuncNLP &amp;</type>
      <name>operator=</name>
      <anchorfile>classConstrainedOptPack_1_1MeritFuncNLPL1.html</anchorfile>
      <anchor>afafa2ec3f18edeeff50858cc27603a7c</anchor>
      <arglist>(const MeritFuncNLP &amp;)</arglist>
    </member>
    <member kind="function">
      <type>value_type</type>
      <name>value</name>
      <anchorfile>classConstrainedOptPack_1_1MeritFuncNLPL1.html</anchorfile>
      <anchor>a656beea0654ca77b3b46aa09daeb3f33</anchor>
      <arglist>(value_type f, const Vector *c, const Vector *h, const Vector *hl, const Vector *hu) const </arglist>
    </member>
    <member kind="function">
      <type>value_type</type>
      <name>deriv</name>
      <anchorfile>classConstrainedOptPack_1_1MeritFuncNLPL1.html</anchorfile>
      <anchor>a56b86286d3e1d32af9cafe9ce64f63f2</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>print_merit_func</name>
      <anchorfile>classConstrainedOptPack_1_1MeritFuncNLPL1.html</anchorfile>
      <anchor>acfc05168e6909c446fb6da2573a77cbc</anchor>
      <arglist>(std::ostream &amp;out, const std::string &amp;leading_str) const </arglist>
    </member>
    <member kind="function">
      <type>value_type</type>
      <name>calc_deriv</name>
      <anchorfile>classConstrainedOptPack_1_1MeritFuncNLPL1.html</anchorfile>
      <anchor>a1c0f28753926ab91d042f363657876d8</anchor>
      <arglist>(const Vector &amp;Gf_k, const Vector *c_k, const Vector *h_k, const Vector *hl, const Vector *hu, const Vector &amp;d_k)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>mu</name>
      <anchorfile>classConstrainedOptPack_1_1MeritFuncNLPL1.html</anchorfile>
      <anchor>a7bb56b24d6d5b35646e3d781ebb4c1f6</anchor>
      <arglist>(value_type mu)</arglist>
    </member>
    <member kind="function">
      <type>value_type</type>
      <name>mu</name>
      <anchorfile>classConstrainedOptPack_1_1MeritFuncNLPL1.html</anchorfile>
      <anchor>a8ccbc4d8abe82a7bdf159fb5dc12806b</anchor>
      <arglist>() const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ConstrainedOptPack::MeritFuncNLPModL1</name>
    <filename>classConstrainedOptPack_1_1MeritFuncNLPModL1.html</filename>
    <base>ConstrainedOptPack::MeritFuncNLP</base>
    <base>ConstrainedOptPack::MeritFuncNLPDirecDeriv</base>
    <base>ConstrainedOptPack::MeritFuncPenaltyParams</base>
    <member kind="function">
      <type></type>
      <name>MeritFuncNLPModL1</name>
      <anchorfile>classConstrainedOptPack_1_1MeritFuncNLPModL1.html</anchorfile>
      <anchor>a76a07ce2a3e529966942108ad5ef0942</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~MeritFuncNLP</name>
      <anchorfile>classConstrainedOptPack_1_1MeritFuncNLP.html</anchorfile>
      <anchor>acbc3c6fb1a0911ae952b8dc8b3c56061</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual MeritFuncNLP &amp;</type>
      <name>operator=</name>
      <anchorfile>classConstrainedOptPack_1_1MeritFuncNLP.html</anchorfile>
      <anchor>afc7c7ee110a59201239d22d2af350aae</anchor>
      <arglist>(const MeritFuncNLP &amp;)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~MeritFuncNLPDirecDeriv</name>
      <anchorfile>classConstrainedOptPack_1_1MeritFuncNLPDirecDeriv.html</anchorfile>
      <anchor>a3cec11782cbbca1a2405a6bc84eb923f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~MeritFuncPenaltyParams</name>
      <anchorfile>classConstrainedOptPack_1_1MeritFuncPenaltyParams.html</anchorfile>
      <anchor>aad6e722e0105ae1b55d8aa829154ee91</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>value_type</type>
      <name>value</name>
      <anchorfile>classConstrainedOptPack_1_1MeritFuncNLPModL1.html</anchorfile>
      <anchor>a5fe3b7d862affa58da3c3df08f72d193</anchor>
      <arglist>(value_type f, const Vector *c, const Vector *h, const Vector *hl, const Vector *hu) const </arglist>
    </member>
    <member kind="function">
      <type>value_type</type>
      <name>deriv</name>
      <anchorfile>classConstrainedOptPack_1_1MeritFuncNLPModL1.html</anchorfile>
      <anchor>a89c8528d0df618e2545ad323c2be0b60</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>print_merit_func</name>
      <anchorfile>classConstrainedOptPack_1_1MeritFuncNLPModL1.html</anchorfile>
      <anchor>a18518d26fd4f6387d3c269906a827803</anchor>
      <arglist>(std::ostream &amp;out, const std::string &amp;leading_str) const </arglist>
    </member>
    <member kind="function">
      <type>value_type</type>
      <name>calc_deriv</name>
      <anchorfile>classConstrainedOptPack_1_1MeritFuncNLPModL1.html</anchorfile>
      <anchor>a1fa295e6bc477dd3a6a2cfea1172f558</anchor>
      <arglist>(const Vector &amp;Gf_k, const Vector *c_k, const Vector *h_k, const Vector *hl, const Vector *hu, const Vector &amp;d_k)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_space_c</name>
      <anchorfile>classConstrainedOptPack_1_1MeritFuncNLPModL1.html</anchorfile>
      <anchor>abfce15983f80a9d41a302778b3b9f2b7</anchor>
      <arglist>(const VectorSpace::space_ptr_t &amp;space_c)</arglist>
    </member>
    <member kind="function">
      <type>VectorMutable &amp;</type>
      <name>set_mu</name>
      <anchorfile>classConstrainedOptPack_1_1MeritFuncNLPModL1.html</anchorfile>
      <anchor>a917c2c98b0c47992a3b25e76511d524d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const Vector &amp;</type>
      <name>get_mu</name>
      <anchorfile>classConstrainedOptPack_1_1MeritFuncNLPModL1.html</anchorfile>
      <anchor>a366b3872d1e35de4bcd119fa56592bd3</anchor>
      <arglist>() const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ConstrainedOptPack::MeritFuncPenaltyParam</name>
    <filename>classConstrainedOptPack_1_1MeritFuncPenaltyParam.html</filename>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~MeritFuncPenaltyParam</name>
      <anchorfile>classConstrainedOptPack_1_1MeritFuncPenaltyParam.html</anchorfile>
      <anchor>a8220e6b7248b42bc992809073e629308</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>mu</name>
      <anchorfile>classConstrainedOptPack_1_1MeritFuncPenaltyParam.html</anchorfile>
      <anchor>aa52c614d51e5dfe1e7d4b454a7f8d03d</anchor>
      <arglist>(value_type mu)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual value_type</type>
      <name>mu</name>
      <anchorfile>classConstrainedOptPack_1_1MeritFuncPenaltyParam.html</anchorfile>
      <anchor>a1d967131cde4d301457eefe5a0e8d5fa</anchor>
      <arglist>() const =0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ConstrainedOptPack::MeritFuncPenaltyParams</name>
    <filename>classConstrainedOptPack_1_1MeritFuncPenaltyParams.html</filename>
    <class kind="class">ConstrainedOptPack::MeritFuncPenaltyParams::CanNotResize</class>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~MeritFuncPenaltyParams</name>
      <anchorfile>classConstrainedOptPack_1_1MeritFuncPenaltyParams.html</anchorfile>
      <anchor>aad6e722e0105ae1b55d8aa829154ee91</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>set_space_c</name>
      <anchorfile>classConstrainedOptPack_1_1MeritFuncPenaltyParams.html</anchorfile>
      <anchor>a03ff2f4cdf79b1a2f616d25d429b7609</anchor>
      <arglist>(const VectorSpace::space_ptr_t &amp;space_c)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual VectorMutable &amp;</type>
      <name>set_mu</name>
      <anchorfile>classConstrainedOptPack_1_1MeritFuncPenaltyParams.html</anchorfile>
      <anchor>a731dd4dd27720fa4d6faf60a046137d5</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual const Vector &amp;</type>
      <name>get_mu</name>
      <anchorfile>classConstrainedOptPack_1_1MeritFuncPenaltyParams.html</anchorfile>
      <anchor>acf06b77455e6609721463123b2849423</anchor>
      <arglist>() const =0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ConstrainedOptPack::MeritFuncPenaltyParams::CanNotResize</name>
    <filename>classConstrainedOptPack_1_1MeritFuncPenaltyParams_1_1CanNotResize.html</filename>
  </compound>
  <compound kind="class">
    <name>ConstrainedOptPack::MatrixDecompRangeOrthog</name>
    <filename>classConstrainedOptPack_1_1MatrixDecompRangeOrthog.html</filename>
    <base>AbstractLinAlgPack::MatrixOpNonsing</base>
    <member kind="function">
      <type></type>
      <name>MatrixDecompRangeOrthog</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixDecompRangeOrthog.html</anchorfile>
      <anchor>a07a7a5c42564a12f599cb8359457b2e5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>MatrixDecompRangeOrthog</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixDecompRangeOrthog.html</anchorfile>
      <anchor>ad746b7afea927f80354ec21ee75617a1</anchor>
      <arglist>(const C_ptr_t &amp;C_ptr, const D_ptr_t &amp;D_ptr, const S_ptr_t &amp;S_ptr)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initialize</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixDecompRangeOrthog.html</anchorfile>
      <anchor>a4c687cefecb33f0713e70db1bf2486ec</anchor>
      <arglist>(const C_ptr_t &amp;C_ptr, const D_ptr_t &amp;D_ptr, const S_ptr_t &amp;S_ptr)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_uninitialized</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixDecompRangeOrthog.html</anchorfile>
      <anchor>a8a3cc7e8086b8d50299e89eb2029d1d8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const C_ptr_t &amp;</type>
      <name>C_ptr</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixDecompRangeOrthog.html</anchorfile>
      <anchor>a60e3fcbd02423c1d53f0a2cd1bea5a49</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const D_ptr_t &amp;</type>
      <name>D_ptr</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixDecompRangeOrthog.html</anchorfile>
      <anchor>aee0ed315fd59875c6cd535096a9b1599</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const S_ptr_t &amp;</type>
      <name>S_ptr</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixDecompRangeOrthog.html</anchorfile>
      <anchor>ac952aca54e8edb0d4a20dedaeae7a6b5</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>size_type</type>
      <name>rows</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixDecompRangeOrthog.html</anchorfile>
      <anchor>a2a15424941f1fdfa6e05d66920ba2c44</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>size_type</type>
      <name>cols</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixDecompRangeOrthog.html</anchorfile>
      <anchor>a76a10283deb9c566cc41a88d12eb6512</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const VectorSpace &amp;</type>
      <name>space_cols</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixDecompRangeOrthog.html</anchorfile>
      <anchor>a0cdb98a052a9f9118f5df7398a3529b0</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const VectorSpace &amp;</type>
      <name>space_rows</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixDecompRangeOrthog.html</anchorfile>
      <anchor>a6aecbec0e34398e0c7bbac35d0be9ddd</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>std::ostream &amp;</type>
      <name>output</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixDecompRangeOrthog.html</anchorfile>
      <anchor>acd4bd268d7926c2a7e24c0fa6c52fdff</anchor>
      <arglist>(std::ostream &amp;out) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Vp_StMtV</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixDecompRangeOrthog.html</anchorfile>
      <anchor>a217d90c82cc947ca2130fc1ab30d038e</anchor>
      <arglist>(VectorMutable *v_lhs, value_type alpha, BLAS_Cpp::Transp trans_rhs1, const Vector &amp;v_rhs2, value_type beta) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>V_InvMtV</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixDecompRangeOrthog.html</anchorfile>
      <anchor>a9cb7f3ff52feef16360b8b929fdc5297</anchor>
      <arglist>(VectorMutable *v_lhs, BLAS_Cpp::Transp trans_rhs1, const Vector &amp;v_rhs2) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ConstrainedOptPack::MatrixGenBanded</name>
    <filename>classConstrainedOptPack_1_1MatrixGenBanded.html</filename>
    <member kind="typedef">
      <type>Teuchos::RCP&lt; MemMngPack::ReleaseResource &gt;</type>
      <name>release_resource_ptr_t</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixGenBanded.html</anchorfile>
      <anchor>abee2e0c3b16e58651bfea46280849134</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>MatrixGenBanded</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixGenBanded.html</anchorfile>
      <anchor>a44026fc6734fe50d212b864ca49849b5</anchor>
      <arglist>(size_type m=0, size_type n=0, size_type kl=0, size_type ku=0, DMatrixSlice *MB=NULL, const release_resource_ptr_t &amp;MB_release_resource_ptr=NULL)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initialize</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixGenBanded.html</anchorfile>
      <anchor>aaab6521337e5a44ef614c4b4f2d1de5d</anchor>
      <arglist>(size_type m=0, size_type n=0, size_type kl=0, size_type ku=0, DMatrixSlice *MB=NULL, const release_resource_ptr_t &amp;MB_release_resource_ptr=NULL)</arglist>
    </member>
    <member kind="function">
      <type>size_type</type>
      <name>kl</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixGenBanded.html</anchorfile>
      <anchor>a8cd65f658051beb13334ca68121dbbac</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>size_type</type>
      <name>ku</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixGenBanded.html</anchorfile>
      <anchor>a0be049c54dcfecfbab0f21836906c9b8</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>DMatrixSlice &amp;</type>
      <name>MB</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixGenBanded.html</anchorfile>
      <anchor>a800e2e096831c0e780575cfef99e9a9d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const DMatrixSlice &amp;</type>
      <name>MB</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixGenBanded.html</anchorfile>
      <anchor>afe1bf60c6470af4c5452b6472a081cba</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>size_type</type>
      <name>rows</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixGenBanded.html</anchorfile>
      <anchor>a331b7ec1a913c4fbe389131f609942c5</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>size_type</type>
      <name>cols</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixGenBanded.html</anchorfile>
      <anchor>a2270aad5003f29a4cc4647f8cb328149</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>size_type</type>
      <name>nz</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixGenBanded.html</anchorfile>
      <anchor>a4a11c2d3dc019974011b42061e88a783</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>std::ostream &amp;</type>
      <name>output</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixGenBanded.html</anchorfile>
      <anchor>a2acefd71ba46d6b6f87437bb81df3ebb</anchor>
      <arglist>(std::ostream &amp;out) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Vp_StMtV</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixGenBanded.html</anchorfile>
      <anchor>a7b4ac1ad2d1082afc1158bcbf59899cd</anchor>
      <arglist>(DVectorSlice *vs_lhs, value_type alpha, BLAS_Cpp::Transp trans_rhs1, const DVectorSlice &amp;vs_rhs2, value_type beta) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Vp_StMtV</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixGenBanded.html</anchorfile>
      <anchor>aeea4a63e7697e9a9ce5686bc3175c473</anchor>
      <arglist>(DVectorSlice *vs_lhs, value_type alpha, BLAS_Cpp::Transp trans_rhs1, const SpVectorSlice &amp;sv_rhs2, value_type beta) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Vp_StPtMtV</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixGenBanded.html</anchorfile>
      <anchor>a836c5b6b325b39e6e0ae026396bbcc06</anchor>
      <arglist>(DVectorSlice *vs_lhs, value_type alpha, const GenPermMatrixSlice &amp;P_rhs1, BLAS_Cpp::Transp P_rhs1_trans, BLAS_Cpp::Transp M_rhs2_trans, const DVectorSlice &amp;vs_rhs3, value_type beta) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Vp_StPtMtV</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixGenBanded.html</anchorfile>
      <anchor>af4179339a0c14c7299c9f2ebbb2fcb01</anchor>
      <arglist>(DVectorSlice *vs_lhs, value_type alpha, const GenPermMatrixSlice &amp;P_rhs1, BLAS_Cpp::Transp P_rhs1_trans, BLAS_Cpp::Transp M_rhs2_trans, const SpVectorSlice &amp;sv_rhs3, value_type beta) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ConstrainedOptPack::MatrixHessianRelaxed</name>
    <filename>classConstrainedOptPack_1_1MatrixHessianRelaxed.html</filename>
    <base>AbstractLinAlgPack::MatrixSymOp</base>
    <member kind="function">
      <type></type>
      <name>MatrixHessianRelaxed</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixHessianRelaxed.html</anchorfile>
      <anchor>aecec2c14117a49991dc8762f180c9ea0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initialize</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixHessianRelaxed.html</anchorfile>
      <anchor>a7ef754639afa6d223b50444da8194daa</anchor>
      <arglist>(const MatrixSymOp &amp;H, value_type bigM)</arglist>
    </member>
    <member kind="function">
      <type>size_type</type>
      <name>rows</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixHessianRelaxed.html</anchorfile>
      <anchor>a4fd15893d1440e8808067f7c1d34aed1</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Vp_StMtV</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixHessianRelaxed.html</anchorfile>
      <anchor>a962abb1f4562d82b030d796c27753b0c</anchor>
      <arglist>(DVectorSlice *vs_lhs, value_type alpha, BLAS_Cpp::Transp trans_rhs1, const DVectorSlice &amp;vs_rhs2, value_type beta) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Vp_StMtV</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixHessianRelaxed.html</anchorfile>
      <anchor>ab083818cff4658ade453d565c27e86c2</anchor>
      <arglist>(DVectorSlice *vs_lhs, value_type alpha, BLAS_Cpp::Transp trans_rhs1, const SpVectorSlice &amp;sv_rhs2, value_type beta) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Vp_StPtMtV</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixHessianRelaxed.html</anchorfile>
      <anchor>abdebf85e9b9e56ea8bcebda7a64284ce</anchor>
      <arglist>(DVectorSlice *vs_lhs, value_type alpha, const GenPermMatrixSlice &amp;P_rhs1, BLAS_Cpp::Transp P_rhs1_trans, BLAS_Cpp::Transp M_rhs2_trans, const DVectorSlice &amp;vs_rhs3, value_type beta) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Vp_StPtMtV</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixHessianRelaxed.html</anchorfile>
      <anchor>a94e18c85111cda9dd19d33fb331e8cb8</anchor>
      <arglist>(DVectorSlice *vs_lhs, value_type alpha, const GenPermMatrixSlice &amp;P_rhs1, BLAS_Cpp::Transp P_rhs1_trans, BLAS_Cpp::Transp M_rhs2_trans, const SpVectorSlice &amp;sv_rhs3, value_type beta) const </arglist>
    </member>
    <member kind="function">
      <type>value_type</type>
      <name>transVtMtV</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixHessianRelaxed.html</anchorfile>
      <anchor>a9ef5e28742a4c59efc86427a3260dbad</anchor>
      <arglist>(const SpVectorSlice &amp;sv_rhs1, BLAS_Cpp::Transp trans_rhs2, const SpVectorSlice &amp;sv_rhs3) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ConstrainedOptPack::MatrixHessianSuperBasic</name>
    <filename>classConstrainedOptPack_1_1MatrixHessianSuperBasic.html</filename>
    <base virtualness="virtual">AbstractLinAlgPack::MatrixSymOp</base>
    <member kind="typedef">
      <type>Teuchos::RCP&lt; const MatrixSymWithOpFactorized &gt;</type>
      <name>B_RR_ptr_t</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixHessianSuperBasic.html</anchorfile>
      <anchor>a02d3bf7dfadadf98b0fc509ef188b5c0</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Teuchos::RCP&lt; const MatrixOp &gt;</type>
      <name>B_RX_ptr_t</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixHessianSuperBasic.html</anchorfile>
      <anchor>a933880a7e3d176da6f386ab6f74ebc1c</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Teuchos::RCP&lt; const MatrixSymOp &gt;</type>
      <name>B_XX_ptr_t</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixHessianSuperBasic.html</anchorfile>
      <anchor>aa76078b8d8f12637a288f7d4694dd711</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::vector&lt; EBounds &gt;</type>
      <name>bnd_fixed_t</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixHessianSuperBasic.html</anchorfile>
      <anchor>aad79e189f6c05e4794d9becada72304c</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>MatrixHessianSuperBasic</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixHessianSuperBasic.html</anchorfile>
      <anchor>ab51037a2766a1d5c9a6de4b95ecb168f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>initialize</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixHessianSuperBasic.html</anchorfile>
      <anchor>a30a609214242b1cd4658f107733bbf3c</anchor>
      <arglist>(size_type n, size_type n_R, const size_type i_x_free[], const size_type i_x_fixed[], const EBounds bnd_fixed[], const B_RR_ptr_t &amp;B_RR_ptr, const B_RX_ptr_t &amp;B_RX_ptr, BLAS_Cpp::Transp B_RX_trans, const B_XX_ptr_t &amp;B_XX_ptr)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>assert_initialized</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixHessianSuperBasic.html</anchorfile>
      <anchor>a09646183ae562de9e36fbe805ca3d1d0</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const GenPermMatrixSlice &amp;</type>
      <name>Q_R</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixHessianSuperBasic.html</anchorfile>
      <anchor>aff1ac2f1798831cb98a46627c205925e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const GenPermMatrixSlice &amp;</type>
      <name>Q_X</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixHessianSuperBasic.html</anchorfile>
      <anchor>af19b3acdedd30fc5665bcedea2d07781</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const bnd_fixed_t &amp;</type>
      <name>bnd_fixed</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixHessianSuperBasic.html</anchorfile>
      <anchor>a87a7429e325a501b47f22fd84f1e265c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const B_RR_ptr_t &amp;</type>
      <name>B_RR_ptr</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixHessianSuperBasic.html</anchorfile>
      <anchor>a4192f6663c66e19058cbf960340026ee</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const B_RX_ptr_t &amp;</type>
      <name>B_RX_ptr</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixHessianSuperBasic.html</anchorfile>
      <anchor>a2bdcadb296062b6b1c888ee5c3a31c64</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>BLAS_Cpp::Transp</type>
      <name>B_RX_trans</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixHessianSuperBasic.html</anchorfile>
      <anchor>aa8a8c786324df793594c45f05ec823f3</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const B_XX_ptr_t &amp;</type>
      <name>B_XX_ptr</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixHessianSuperBasic.html</anchorfile>
      <anchor>ae43f52cd44744080c714168544687662</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>size_type</type>
      <name>rows</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixHessianSuperBasic.html</anchorfile>
      <anchor>ac75077153464ce8f4e444b9f54ce3274</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Vp_StMtV</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixHessianSuperBasic.html</anchorfile>
      <anchor>a46c96a8507334c0762e44f0e283c6438</anchor>
      <arglist>(DVectorSlice *vs_lhs, value_type alpha, BLAS_Cpp::Transp trans_rhs1, const DVectorSlice &amp;vs_rhs2, value_type beta) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Vp_StMtV</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixHessianSuperBasic.html</anchorfile>
      <anchor>a79cb70d661d8176e4fe0bd73da5aa6a0</anchor>
      <arglist>(DVectorSlice *vs_lhs, value_type alpha, BLAS_Cpp::Transp trans_rhs1, const SpVectorSlice &amp;sv_rhs2, value_type beta) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Vp_StPtMtV</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixHessianSuperBasic.html</anchorfile>
      <anchor>a399c62863a7f7abd3113c778b392b916</anchor>
      <arglist>(DVectorSlice *vs_lhs, value_type alpha, const GenPermMatrixSlice &amp;P_rhs1, BLAS_Cpp::Transp P_rhs1_trans, BLAS_Cpp::Transp M_rhs2_trans, const DVectorSlice &amp;sv_rhs3, value_type beta) const </arglist>
    </member>
    <member kind="function">
      <type>value_type</type>
      <name>transVtMtV</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixHessianSuperBasic.html</anchorfile>
      <anchor>a00c461391cde73301e3fd82a78599735</anchor>
      <arglist>(const SpVectorSlice &amp;sv_rhs1, BLAS_Cpp::Transp trans_rhs2, const SpVectorSlice &amp;sv_rhs3) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ConstrainedOptPack::MatrixHessianSuperBasicInitDiagonal</name>
    <filename>classConstrainedOptPack_1_1MatrixHessianSuperBasicInitDiagonal.html</filename>
    <base virtualness="virtual">ConstrainedOptPack::MatrixHessianSuperBasic</base>
    <base virtualness="virtual">AbstractLinAlgPack::MatrixSymInitDiag</base>
    <member kind="function">
      <type></type>
      <name>MatrixHessianSuperBasicInitDiagonal</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixHessianSuperBasicInitDiagonal.html</anchorfile>
      <anchor>aa9b41032de2d4d6131620e4b0f401739</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>MatrixHessianSuperBasic</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixHessianSuperBasic.html</anchorfile>
      <anchor>ab51037a2766a1d5c9a6de4b95ecb168f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const GenPermMatrixSlice &amp;</type>
      <name>Q_R</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixHessianSuperBasic.html</anchorfile>
      <anchor>aff1ac2f1798831cb98a46627c205925e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const GenPermMatrixSlice &amp;</type>
      <name>Q_X</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixHessianSuperBasic.html</anchorfile>
      <anchor>af19b3acdedd30fc5665bcedea2d07781</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const bnd_fixed_t &amp;</type>
      <name>bnd_fixed</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixHessianSuperBasic.html</anchorfile>
      <anchor>a87a7429e325a501b47f22fd84f1e265c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const B_RR_ptr_t &amp;</type>
      <name>B_RR_ptr</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixHessianSuperBasic.html</anchorfile>
      <anchor>a4192f6663c66e19058cbf960340026ee</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const B_RX_ptr_t &amp;</type>
      <name>B_RX_ptr</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixHessianSuperBasic.html</anchorfile>
      <anchor>a2bdcadb296062b6b1c888ee5c3a31c64</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>BLAS_Cpp::Transp</type>
      <name>B_RX_trans</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixHessianSuperBasic.html</anchorfile>
      <anchor>aa8a8c786324df793594c45f05ec823f3</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const B_XX_ptr_t &amp;</type>
      <name>B_XX_ptr</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixHessianSuperBasic.html</anchorfile>
      <anchor>ae43f52cd44744080c714168544687662</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>size_type</type>
      <name>rows</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixHessianSuperBasic.html</anchorfile>
      <anchor>ac75077153464ce8f4e444b9f54ce3274</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Vp_StMtV</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixHessianSuperBasic.html</anchorfile>
      <anchor>a46c96a8507334c0762e44f0e283c6438</anchor>
      <arglist>(DVectorSlice *vs_lhs, value_type alpha, BLAS_Cpp::Transp trans_rhs1, const DVectorSlice &amp;vs_rhs2, value_type beta) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Vp_StMtV</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixHessianSuperBasic.html</anchorfile>
      <anchor>a79cb70d661d8176e4fe0bd73da5aa6a0</anchor>
      <arglist>(DVectorSlice *vs_lhs, value_type alpha, BLAS_Cpp::Transp trans_rhs1, const SpVectorSlice &amp;sv_rhs2, value_type beta) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Vp_StPtMtV</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixHessianSuperBasic.html</anchorfile>
      <anchor>a399c62863a7f7abd3113c778b392b916</anchor>
      <arglist>(DVectorSlice *vs_lhs, value_type alpha, const GenPermMatrixSlice &amp;P_rhs1, BLAS_Cpp::Transp P_rhs1_trans, BLAS_Cpp::Transp M_rhs2_trans, const DVectorSlice &amp;sv_rhs3, value_type beta) const </arglist>
    </member>
    <member kind="function">
      <type>value_type</type>
      <name>transVtMtV</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixHessianSuperBasic.html</anchorfile>
      <anchor>a00c461391cde73301e3fd82a78599735</anchor>
      <arglist>(const SpVectorSlice &amp;sv_rhs1, BLAS_Cpp::Transp trans_rhs2, const SpVectorSlice &amp;sv_rhs3) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initialize</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixHessianSuperBasicInitDiagonal.html</anchorfile>
      <anchor>ab3a76264fb485573586cbdc8f32f1c25</anchor>
      <arglist>(size_type n, size_type n_R, const size_type i_x_free[], const size_type i_x_fixed[], const EBounds bnd_fixed[], const B_RR_ptr_t &amp;B_RR_ptr, const B_RX_ptr_t &amp;B_RX_ptr, BLAS_Cpp::Transp B_RX_trans, const B_XX_ptr_t &amp;B_XX_ptr)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>init_identity</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixHessianSuperBasicInitDiagonal.html</anchorfile>
      <anchor>a1da57e8ecc83bf58b066c643a001f2f3</anchor>
      <arglist>(size_type n, value_type alpha)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>init_diagonal</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixHessianSuperBasicInitDiagonal.html</anchorfile>
      <anchor>a55986614acee3ed65f9a95759e99038c</anchor>
      <arglist>(const DVectorSlice &amp;diag)</arglist>
    </member>
    <member kind="typedef">
      <type>Teuchos::RCP&lt; const MatrixSymWithOpFactorized &gt;</type>
      <name>B_RR_ptr_t</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixHessianSuperBasic.html</anchorfile>
      <anchor>a02d3bf7dfadadf98b0fc509ef188b5c0</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Teuchos::RCP&lt; const MatrixOp &gt;</type>
      <name>B_RX_ptr_t</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixHessianSuperBasic.html</anchorfile>
      <anchor>a933880a7e3d176da6f386ab6f74ebc1c</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Teuchos::RCP&lt; const MatrixSymOp &gt;</type>
      <name>B_XX_ptr_t</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixHessianSuperBasic.html</anchorfile>
      <anchor>aa76078b8d8f12637a288f7d4694dd711</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::vector&lt; EBounds &gt;</type>
      <name>bnd_fixed_t</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixHessianSuperBasic.html</anchorfile>
      <anchor>aad79e189f6c05e4794d9becada72304c</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>assert_initialized</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixHessianSuperBasic.html</anchorfile>
      <anchor>a09646183ae562de9e36fbe805ca3d1d0</anchor>
      <arglist>() const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ConstrainedOptPack::MatrixIdentConcat</name>
    <filename>classConstrainedOptPack_1_1MatrixIdentConcat.html</filename>
    <base virtualness="virtual">AbstractLinAlgPack::MatrixOp</base>
    <member kind="function" virtualness="pure">
      <type>virtual Range1D</type>
      <name>D_rng</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixIdentConcat.html</anchorfile>
      <anchor>a8e9b00edc6e7a2388d450664c8f17831</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual Range1D</type>
      <name>I_rng</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixIdentConcat.html</anchorfile>
      <anchor>aaf7ff5acf0cb4079a2dbe25e1d626f31</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual value_type</type>
      <name>alpha</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixIdentConcat.html</anchorfile>
      <anchor>a03d96ee744c49fa50ab2630daf16356f</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual const MatrixOp &amp;</type>
      <name>D</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixIdentConcat.html</anchorfile>
      <anchor>ad4de9e4622a495061d03d3484f07e3e3</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual BLAS_Cpp::Transp</type>
      <name>D_trans</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixIdentConcat.html</anchorfile>
      <anchor>ae31d97f04b9aeabb1197556cf4c401b7</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function">
      <type>size_type</type>
      <name>rows</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixIdentConcat.html</anchorfile>
      <anchor>a9aa1dc009ed34f084d0e9f4991ee6a09</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>size_type</type>
      <name>cols</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixIdentConcat.html</anchorfile>
      <anchor>a7ea842711cdfaec99b6d92947a5d5f5e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>size_type</type>
      <name>nz</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixIdentConcat.html</anchorfile>
      <anchor>ace220df9e3f2d45936e3ff32fb7f8529</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>std::ostream &amp;</type>
      <name>output</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixIdentConcat.html</anchorfile>
      <anchor>aaf430254d7b3e3801587f6601adacdab</anchor>
      <arglist>(std::ostream &amp;out) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Vp_StMtV</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixIdentConcat.html</anchorfile>
      <anchor>a13e9f97c256968c8cd5cf9470d82957e</anchor>
      <arglist>(VectorMutable *vs_lhs, value_type alpha, BLAS_Cpp::Transp trans_rhs1, const Vector &amp;vs_rhs2, value_type beta) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Vp_StMtV</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixIdentConcat.html</anchorfile>
      <anchor>ae50dafda038dca983a1fa9e5c7149859</anchor>
      <arglist>(VectorMutable *vs_lhs, value_type alpha, BLAS_Cpp::Transp trans_rhs1, const SpVectorSlice &amp;sv_rhs2, value_type beta) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ConstrainedOptPack::MatrixIdentConcatStd</name>
    <filename>classConstrainedOptPack_1_1MatrixIdentConcatStd.html</filename>
    <base>ConstrainedOptPack::MatrixIdentConcat</base>
    <member kind="enumeration">
      <name>ETopBottom</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixIdentConcatStd.html</anchorfile>
      <anchor>a28ade8799e6cd031378d3872899132dc</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Teuchos::RCP&lt; const MatrixOp &gt;</type>
      <name>D_ptr_t</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixIdentConcatStd.html</anchorfile>
      <anchor>aafe2ac8f98af9123e9061d58285f9a0c</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>MatrixIdentConcatStd</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixIdentConcatStd.html</anchorfile>
      <anchor>af4f1437ccd66fccd2ee50e94acf668b4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>initialize</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixIdentConcatStd.html</anchorfile>
      <anchor>aaa029d3c3a764dec15e0f21a4c703a8b</anchor>
      <arglist>(const VectorSpace::space_ptr_t &amp;space_cols, const VectorSpace::space_ptr_t &amp;space_rows, ETopBottom top_or_bottom, value_type alpha, const D_ptr_t &amp;D_ptr, BLAS_Cpp::Transp D_trans)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>set_uninitialized</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixIdentConcatStd.html</anchorfile>
      <anchor>ae612090c36b482fdae123d35b84e6de0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const D_ptr_t &amp;</type>
      <name>D_ptr</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixIdentConcatStd.html</anchorfile>
      <anchor>a8226e812ef3d1b014b85667ab9310d4e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Range1D</type>
      <name>D_rng</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixIdentConcatStd.html</anchorfile>
      <anchor>a55181e577827a917ca7ca10d3346ff8e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Range1D</type>
      <name>I_rng</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixIdentConcatStd.html</anchorfile>
      <anchor>a9deb0a7faf2c4a38004d5cfdcb5dc2ff</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>value_type</type>
      <name>alpha</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixIdentConcatStd.html</anchorfile>
      <anchor>a22c147ca680378fe66003125bb958f9c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const MatrixOp &amp;</type>
      <name>D</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixIdentConcatStd.html</anchorfile>
      <anchor>af70e0611ae985f445cf473a508581d2a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>BLAS_Cpp::Transp</type>
      <name>D_trans</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixIdentConcatStd.html</anchorfile>
      <anchor>af76b5fae50c21a8e058dd97be783587c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const VectorSpace &amp;</type>
      <name>space_cols</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixIdentConcatStd.html</anchorfile>
      <anchor>a579384ae834f2d73d75b07a85c69bfbb</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const VectorSpace &amp;</type>
      <name>space_rows</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixIdentConcatStd.html</anchorfile>
      <anchor>a43520b02a06b21bd4046ab5170541d35</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>MatrixOp &amp;</type>
      <name>operator=</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixIdentConcatStd.html</anchorfile>
      <anchor>ade6fa58cbadd327344d4fca7b0901382</anchor>
      <arglist>(const MatrixOp &amp;m)</arglist>
    </member>
    <member kind="function">
      <type>size_type</type>
      <name>rows</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixIdentConcat.html</anchorfile>
      <anchor>a9aa1dc009ed34f084d0e9f4991ee6a09</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>size_type</type>
      <name>cols</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixIdentConcat.html</anchorfile>
      <anchor>a7ea842711cdfaec99b6d92947a5d5f5e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>size_type</type>
      <name>nz</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixIdentConcat.html</anchorfile>
      <anchor>ace220df9e3f2d45936e3ff32fb7f8529</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>std::ostream &amp;</type>
      <name>output</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixIdentConcat.html</anchorfile>
      <anchor>aaf430254d7b3e3801587f6601adacdab</anchor>
      <arglist>(std::ostream &amp;out) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Vp_StMtV</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixIdentConcat.html</anchorfile>
      <anchor>a13e9f97c256968c8cd5cf9470d82957e</anchor>
      <arglist>(VectorMutable *vs_lhs, value_type alpha, BLAS_Cpp::Transp trans_rhs1, const Vector &amp;vs_rhs2, value_type beta) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Vp_StMtV</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixIdentConcat.html</anchorfile>
      <anchor>ae50dafda038dca983a1fa9e5c7149859</anchor>
      <arglist>(VectorMutable *vs_lhs, value_type alpha, BLAS_Cpp::Transp trans_rhs1, const SpVectorSlice &amp;sv_rhs2, value_type beta) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ConstrainedOptPack::MatrixKKTFullSpaceRelaxed</name>
    <filename>classConstrainedOptPack_1_1MatrixKKTFullSpaceRelaxed.html</filename>
    <class kind="class">ConstrainedOptPack::MatrixKKTFullSpaceRelaxed::InvalidMatrixType</class>
    <class kind="class">ConstrainedOptPack::MatrixKKTFullSpaceRelaxed::NotInitializedException</class>
    <class kind="class">ConstrainedOptPack::MatrixKKTFullSpaceRelaxed::SingularMatrixException</class>
    <member kind="enumeration">
      <name>ERunTests</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixKKTFullSpaceRelaxed.html</anchorfile>
      <anchor>a689b3b35fd9fda65048454b566a00f80</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>EPrintMoreOrLess</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixKKTFullSpaceRelaxed.html</anchorfile>
      <anchor>a2c76accf20c3f683309a0b94e045e0b2</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>AbstractLinAlgPack::DirectSparseFortranCompatibleSolver</type>
      <name>DirectSparseFortranCompatibleSolver</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixKKTFullSpaceRelaxed.html</anchorfile>
      <anchor>a152fe3d28eb4bc88ea35df09b2a4cd5d</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_COMPOSITION_MEMBERS</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixKKTFullSpaceRelaxed.html</anchorfile>
      <anchor>a5aa06e53b4c32eb4452402f9f393a1bc</anchor>
      <arglist>(DirectSparseFortranCompatibleSolver, direct_solver)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>MatrixKKTFullSpaceRelaxed</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixKKTFullSpaceRelaxed.html</anchorfile>
      <anchor>a940501d73b2157086822128bd13edfd2</anchor>
      <arglist>(const direct_solver_ptr_t &amp;direct_solver=0)</arglist>
    </member>
    <member kind="function">
      <type>size_type</type>
      <name>rows</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixKKTFullSpaceRelaxed.html</anchorfile>
      <anchor>a308d69059e855e1ae50403fdb3a4ad24</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>size_type</type>
      <name>cols</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixKKTFullSpaceRelaxed.html</anchorfile>
      <anchor>a23f60524a23e767368df11cd435a87a9</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>std::ostream &amp;</type>
      <name>output</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixKKTFullSpaceRelaxed.html</anchorfile>
      <anchor>afa93a570b4ecb58a96c48d872fdbbd5a</anchor>
      <arglist>(std::ostream &amp;out) const </arglist>
    </member>
    <member kind="function">
      <type>MatrixOp &amp;</type>
      <name>operator=</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixKKTFullSpaceRelaxed.html</anchorfile>
      <anchor>af2b479b53f961ccdb3ffedba9ae6620e</anchor>
      <arglist>(const MatrixOp &amp;m)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Vp_StMtV</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixKKTFullSpaceRelaxed.html</anchorfile>
      <anchor>a1159d3137f0ed42b506214f1041ee677</anchor>
      <arglist>(DVectorSlice *vs_lhs, value_type alpha, BLAS_Cpp::Transp trans_rhs1, const DVectorSlice &amp;vs_rhs2, value_type beta) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>V_InvMtV</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixKKTFullSpaceRelaxed.html</anchorfile>
      <anchor>a676fc43d09da3a7b381a74fdf86e14c7</anchor>
      <arglist>(DVectorSlice *v_lhs, BLAS_Cpp::Transp trans_rhs1, const DVectorSlice &amp;vs_rhs2) const </arglist>
    </member>
    <member kind="function">
      <type>FortranTypes::f_int</type>
      <name>num_nonzeros</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixKKTFullSpaceRelaxed.html</anchorfile>
      <anchor>afd2133630707ddcc077383aed7374e30</anchor>
      <arglist>(EExtractRegion extract_region) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>coor_extract_nonzeros</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixKKTFullSpaceRelaxed.html</anchorfile>
      <anchor>ab195156ebdaf3a734fa4f2efee475894</anchor>
      <arglist>(EExtractRegion extract_region, const FortranTypes::f_int len_Aval, FortranTypes::f_dbl_prec Aval[], const FortranTypes::f_int len_Aij, FortranTypes::f_int Arow[], FortranTypes::f_int Acol[], const FortranTypes::f_int row_offset, const FortranTypes::f_int col_offset) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initialize</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixKKTFullSpaceRelaxed.html</anchorfile>
      <anchor>a5eb1f2fe7f083bf6f422ddce54f53eab</anchor>
      <arglist>(const MatrixOp &amp;G, const MatrixOp &amp;A, std::ostream *out=0, EPrintMoreOrLess print_what=PRINT_LESS, ERunTests test_what=NO_TESTS)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initialize_relaxed</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixKKTFullSpaceRelaxed.html</anchorfile>
      <anchor>a5edd59914d2d7dc8310b573ec5528138</anchor>
      <arglist>(const MatrixOp &amp;G, const MatrixOp &amp;A, const DVectorSlice &amp;c, value_type bigM=1e+10, std::ostream *out=0, EPrintMoreOrLess print_what=PRINT_LESS, ERunTests test_what=NO_TESTS)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_uninitialized</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixKKTFullSpaceRelaxed.html</anchorfile>
      <anchor>a5bf5de97b4fd4241ffeeb3a71e284ec8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>release_memory</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixKKTFullSpaceRelaxed.html</anchorfile>
      <anchor>a3009066ac24785e3b2493d4b14688ece</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ConstrainedOptPack::MatrixKKTFullSpaceRelaxed::InvalidMatrixType</name>
    <filename>classConstrainedOptPack_1_1MatrixKKTFullSpaceRelaxed_1_1InvalidMatrixType.html</filename>
  </compound>
  <compound kind="class">
    <name>ConstrainedOptPack::MatrixKKTFullSpaceRelaxed::NotInitializedException</name>
    <filename>classConstrainedOptPack_1_1MatrixKKTFullSpaceRelaxed_1_1NotInitializedException.html</filename>
  </compound>
  <compound kind="class">
    <name>ConstrainedOptPack::MatrixKKTFullSpaceRelaxed::SingularMatrixException</name>
    <filename>classConstrainedOptPack_1_1MatrixKKTFullSpaceRelaxed_1_1SingularMatrixException.html</filename>
  </compound>
  <compound kind="class">
    <name>ConstrainedOptPack::MatrixSymAddDelBunchKaufman</name>
    <filename>classConstrainedOptPack_1_1MatrixSymAddDelBunchKaufman.html</filename>
    <base virtualness="virtual">AbstractLinAlgPack::MatrixSymOpNonsingSerial</base>
    <base virtualness="virtual">ConstrainedOptPack::MatrixSymAddDelUpdateableWithOpNonsingular</base>
    <member kind="function">
      <type></type>
      <name>MatrixSymAddDelBunchKaufman</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixSymAddDelBunchKaufman.html</anchorfile>
      <anchor>a1638ae1420dd1e82f29628b2806ced90</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>pivot_tols</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixSymAddDelBunchKaufman.html</anchorfile>
      <anchor>a445b96c3cfdfeb5574641a207240c336</anchor>
      <arglist>(PivotTolerances pivot_tols)</arglist>
    </member>
    <member kind="function">
      <type>PivotTolerances</type>
      <name>pivot_tols</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixSymAddDelBunchKaufman.html</anchorfile>
      <anchor>ab4d487945c840f223bb72d38bd09bcdd</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~MatrixSymAddDelUpdateableWithOpNonsingular</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixSymAddDelUpdateableWithOpNonsingular.html</anchorfile>
      <anchor>a4e10edbae85c03fe21d225f568d5deff</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const MatrixSymOpNonsing &amp;</type>
      <name>op_interface</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixSymAddDelBunchKaufman.html</anchorfile>
      <anchor>a1fe8c8cc6963a954918c7a0c284a7665</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>MatrixSymAddDelUpdateable &amp;</type>
      <name>update_interface</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixSymAddDelBunchKaufman.html</anchorfile>
      <anchor>a8a4a3eec2b5b5dcf6d31c994c98466fa</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const MatrixSymAddDelUpdateable &amp;</type>
      <name>update_interface</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixSymAddDelBunchKaufman.html</anchorfile>
      <anchor>a4ac62dd0b88ebbb3a955b9fe631038af</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initialize</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixSymAddDelBunchKaufman.html</anchorfile>
      <anchor>a63942c55caa93fb81c833d7e0828cc7b</anchor>
      <arglist>(value_type alpha, size_type max_size)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initialize</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixSymAddDelBunchKaufman.html</anchorfile>
      <anchor>a68209ed863e49d557d710b711b181fae</anchor>
      <arglist>(const DMatrixSliceSym &amp;A, size_type max_size, bool force_factorization, Inertia inertia, PivotTolerances pivot_tols)</arglist>
    </member>
    <member kind="function">
      <type>size_type</type>
      <name>max_size</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixSymAddDelBunchKaufman.html</anchorfile>
      <anchor>ada9702081168797973f9e35e9ac613a1</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Inertia</type>
      <name>inertia</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixSymAddDelBunchKaufman.html</anchorfile>
      <anchor>aa0f11555d307c58fe0ee244620c68b19</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_uninitialized</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixSymAddDelBunchKaufman.html</anchorfile>
      <anchor>a3d22cdca810947b2df3230b5cb2b1b44</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>augment_update</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixSymAddDelBunchKaufman.html</anchorfile>
      <anchor>af2d7d394b6d92644000663b3f2909a2a</anchor>
      <arglist>(const DVectorSlice *t, value_type alpha, bool force_refactorization, EEigenValType add_eigen_val, PivotTolerances pivot_tols)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>delete_update</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixSymAddDelBunchKaufman.html</anchorfile>
      <anchor>a80c97ca140f5b99d2c4554b489c5664b</anchor>
      <arglist>(size_type jd, bool force_refactorization, EEigenValType drop_eigen_val, PivotTolerances pivot_tols)</arglist>
    </member>
    <member kind="function">
      <type>size_type</type>
      <name>rows</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixSymAddDelBunchKaufman.html</anchorfile>
      <anchor>a46ed6824c4f039c5de3c1d1c04c1ec5d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>std::ostream &amp;</type>
      <name>output</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixSymAddDelBunchKaufman.html</anchorfile>
      <anchor>a4e49dfa08dd85ccc6e08e5aa5a343a16</anchor>
      <arglist>(std::ostream &amp;out) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Vp_StMtV</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixSymAddDelBunchKaufman.html</anchorfile>
      <anchor>ae12655533f59e19b10a26b5eca36fb89</anchor>
      <arglist>(DVectorSlice *vs_lhs, value_type alpha, BLAS_Cpp::Transp trans_rhs1, const DVectorSlice &amp;vs_rhs2, value_type beta) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>V_InvMtV</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixSymAddDelBunchKaufman.html</anchorfile>
      <anchor>ae81676182effbff3002141a34d435784</anchor>
      <arglist>(DVectorSlice *vs_lhs, BLAS_Cpp::Transp trans_rhs1, const DVectorSlice &amp;vs_rhs2) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ConstrainedOptPack::MatrixSymAddDelUpdateableWithOpNonsingular</name>
    <filename>classConstrainedOptPack_1_1MatrixSymAddDelUpdateableWithOpNonsingular.html</filename>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~MatrixSymAddDelUpdateableWithOpNonsingular</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixSymAddDelUpdateableWithOpNonsingular.html</anchorfile>
      <anchor>a4e10edbae85c03fe21d225f568d5deff</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual const MatrixSymOpNonsing &amp;</type>
      <name>op_interface</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixSymAddDelUpdateableWithOpNonsingular.html</anchorfile>
      <anchor>a7cec47cbc8dc10f449293607aaedb9bc</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual MatrixSymAddDelUpdateable &amp;</type>
      <name>update_interface</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixSymAddDelUpdateableWithOpNonsingular.html</anchorfile>
      <anchor>a360db44aacfdd88b19f7cd75dd723460</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual const MatrixSymAddDelUpdateable &amp;</type>
      <name>update_interface</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixSymAddDelUpdateableWithOpNonsingular.html</anchorfile>
      <anchor>a9b594549dda398a9077314aaeed7bfdf</anchor>
      <arglist>() const =0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ConstrainedOptPack::MatrixSymHessianRelaxNonSing</name>
    <filename>classConstrainedOptPack_1_1MatrixSymHessianRelaxNonSing.html</filename>
    <base>AbstractLinAlgPack::MatrixSymOpNonsing</base>
    <member kind="typedef">
      <type>Teuchos::RCP&lt; const MatrixSymOpNonsing &gt;</type>
      <name>G_ptr_t</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixSymHessianRelaxNonSing.html</anchorfile>
      <anchor>a6c9823459893e9e2c64255aaf8c21b11</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Teuchos::RCP&lt; VectorMutable &gt;</type>
      <name>vec_mut_ptr_t</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixSymHessianRelaxNonSing.html</anchorfile>
      <anchor>a6b51faf4101bbcf6298b3db1733252a3</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Teuchos::RCP&lt; const VectorSpace &gt;</type>
      <name>space_ptr_t</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixSymHessianRelaxNonSing.html</anchorfile>
      <anchor>ad39fa357d9a072fbf970d1194a644a9f</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>MatrixSymHessianRelaxNonSing</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixSymHessianRelaxNonSing.html</anchorfile>
      <anchor>a226b2030b4634426c68e6f5f2e77d19b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>MatrixSymHessianRelaxNonSing</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixSymHessianRelaxNonSing.html</anchorfile>
      <anchor>a494094e820cb419804f77bec1ce9ab7d</anchor>
      <arglist>(const G_ptr_t &amp;G_ptr, const vec_mut_ptr_t &amp;M_diag_ptr, const space_ptr_t &amp;space=Teuchos::null)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initialize</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixSymHessianRelaxNonSing.html</anchorfile>
      <anchor>aa5da326ed920986cbda903e0c4f228a2</anchor>
      <arglist>(const G_ptr_t &amp;G_ptr, const vec_mut_ptr_t &amp;M_diag_ptr, const space_ptr_t &amp;space=Teuchos::null)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_uninitialized</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixSymHessianRelaxNonSing.html</anchorfile>
      <anchor>a595af09af4e6f3398d0cbab64fcd01dc</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const G_ptr_t &amp;</type>
      <name>G_ptr</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixSymHessianRelaxNonSing.html</anchorfile>
      <anchor>a5e851de46169a82fd84a750f827d194c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const vec_mut_ptr_t &amp;</type>
      <name>M_diag_ptr</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixSymHessianRelaxNonSing.html</anchorfile>
      <anchor>a62877d77b0b8e9742ee7e6cb6a6180d9</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const MatrixSymOpNonsing &amp;</type>
      <name>G</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixSymHessianRelaxNonSing.html</anchorfile>
      <anchor>a9957247db0968d5a21669261ab61de07</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const AbstractLinAlgPack::MatrixSymDiagStd &amp;</type>
      <name>M</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixSymHessianRelaxNonSing.html</anchorfile>
      <anchor>a6548ef8e3190e7040db710f72b24e68a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const VectorSpace &amp;</type>
      <name>space_cols</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixSymHessianRelaxNonSing.html</anchorfile>
      <anchor>a054f6e7a9be4fd2999c67c0dce722634</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>Mp_StM</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixSymHessianRelaxNonSing.html</anchorfile>
      <anchor>a538444f4d4a5dd256739c85f725f7725</anchor>
      <arglist>(MatrixOp *mwo_lhs, value_type alpha, BLAS_Cpp::Transp trans_rhs) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Vp_StMtV</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixSymHessianRelaxNonSing.html</anchorfile>
      <anchor>ac71e345d591d5b773720a8a55a719fc1</anchor>
      <arglist>(VectorMutable *v_lhs, value_type alpha, BLAS_Cpp::Transp trans_rhs1, const Vector &amp;v_rhs2, value_type beta) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Vp_StMtV</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixSymHessianRelaxNonSing.html</anchorfile>
      <anchor>aa55e0205350e0a8b2f07417b13b11d63</anchor>
      <arglist>(VectorMutable *v_lhs, value_type alpha, BLAS_Cpp::Transp trans_rhs1, const SpVectorSlice &amp;sv_rhs2, value_type beta) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Vp_StPtMtV</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixSymHessianRelaxNonSing.html</anchorfile>
      <anchor>a30c2d44beab27f292c3deeaf67715ed7</anchor>
      <arglist>(VectorMutable *v_lhs, value_type alpha, const GenPermMatrixSlice &amp;P_rhs1, BLAS_Cpp::Transp P_rhs1_trans, BLAS_Cpp::Transp M_rhs2_trans, const Vector &amp;v_rhs3, value_type beta) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Vp_StPtMtV</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixSymHessianRelaxNonSing.html</anchorfile>
      <anchor>a37251d8069eab6f5a2742b23ce2b93f6</anchor>
      <arglist>(VectorMutable *v_lhs, value_type alpha, const GenPermMatrixSlice &amp;P_rhs1, BLAS_Cpp::Transp P_rhs1_trans, BLAS_Cpp::Transp M_rhs2_trans, const SpVectorSlice &amp;sv_rhs3, value_type beta) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Mp_StPtMtP</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixSymHessianRelaxNonSing.html</anchorfile>
      <anchor>a5144ea57dc0817758191e5ec539fe304</anchor>
      <arglist>(MatrixSymOp *sym_lhs, value_type alpha, EMatRhsPlaceHolder dummy_place_holder, const GenPermMatrixSlice &amp;gpms_rhs, BLAS_Cpp::Transp gpms_rhs_trans, value_type beta) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>V_InvMtV</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixSymHessianRelaxNonSing.html</anchorfile>
      <anchor>a2ef6193f6d596e46fa024daec109f290</anchor>
      <arglist>(VectorMutable *v_lhs, BLAS_Cpp::Transp trans_rhs1, const Vector &amp;v_rhs2) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>V_InvMtV</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixSymHessianRelaxNonSing.html</anchorfile>
      <anchor>a9b61c4194deca81f791ae40978657620</anchor>
      <arglist>(VectorMutable *v_lhs, BLAS_Cpp::Transp trans_rhs1, const SpVectorSlice &amp;sv_rhs2) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ConstrainedOptPack::MatrixSymIdentitySerial</name>
    <filename>classConstrainedOptPack_1_1MatrixSymIdentitySerial.html</filename>
    <base virtualness="virtual">AbstractLinAlgPack::MatrixSymOpNonsingSerial</base>
    <base virtualness="virtual">AbstractLinAlgPack::MatrixExtractInvCholFactor</base>
    <member kind="function">
      <type></type>
      <name>MatrixSymIdentitySerial</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixSymIdentitySerial.html</anchorfile>
      <anchor>ad114e2155a52a8fbb4c87670273f868e</anchor>
      <arglist>(size_type size=1, value_type scale=1.0)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initialize</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixSymIdentitySerial.html</anchorfile>
      <anchor>ad521bbe0eaf887507e6f55468a2b8c8b</anchor>
      <arglist>(size_type size, value_type scale)</arglist>
    </member>
    <member kind="function">
      <type>value_type</type>
      <name>scale</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixSymIdentitySerial.html</anchorfile>
      <anchor>aee95aab565d92eb101bdda72b26463d8</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>size_type</type>
      <name>rows</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixSymIdentitySerial.html</anchorfile>
      <anchor>ac4d72f48721f08ed40c5ddc86a6820c8</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>size_type</type>
      <name>nz</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixSymIdentitySerial.html</anchorfile>
      <anchor>a96ac271b80b2291b3c1eb5b93381359a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>std::ostream &amp;</type>
      <name>output</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixSymIdentitySerial.html</anchorfile>
      <anchor>aec2a9aa363ee25b016523c54ee2290fa</anchor>
      <arglist>(std::ostream &amp;out) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Vp_StMtV</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixSymIdentitySerial.html</anchorfile>
      <anchor>a479ec8c8c11ed00052e59736720ca086</anchor>
      <arglist>(DVectorSlice *vs_lhs, value_type alpha, BLAS_Cpp::Transp trans_rhs1, const DVectorSlice &amp;vs_rhs2, value_type beta) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>V_InvMtV</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixSymIdentitySerial.html</anchorfile>
      <anchor>a78e965c09d8e661605b0e66eac0e10a4</anchor>
      <arglist>(DVectorSlice *vs_lhs, BLAS_Cpp::Transp trans_rhs1, const DVectorSlice &amp;vs_rhs2) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>M_StMtInvMtM</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixSymIdentitySerial.html</anchorfile>
      <anchor>aba58f5ff25761695b595e1e94bfc862c</anchor>
      <arglist>(DMatrixSliceSym *sym_gms_lhs, value_type alpha, const MatrixOpSerial &amp;mwo, BLAS_Cpp::Transp mwo_trans, EMatrixDummyArg) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>extract_inv_chol</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixSymIdentitySerial.html</anchorfile>
      <anchor>afd1635919e15d4d24de4efa4e3426380</anchor>
      <arglist>(DMatrixSliceTriEle *InvChol) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ConstrainedOptPack::MatrixSymPosDefBandedChol</name>
    <filename>classConstrainedOptPack_1_1MatrixSymPosDefBandedChol.html</filename>
    <member kind="typedef">
      <type>Teuchos::RCP&lt; MemMngPack::ReleaseResource &gt;</type>
      <name>release_resource_ptr_t</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixSymPosDefBandedChol.html</anchorfile>
      <anchor>ac8cfe8e8f17a520285416eb764748da0</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>MatrixSymPosDefBandedChol</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixSymPosDefBandedChol.html</anchorfile>
      <anchor>a7aba786dd2433871da05372dcd070b0a</anchor>
      <arglist>(size_type n=0, size_type kd=0, DMatrixSlice *MB=NULL, const release_resource_ptr_t &amp;MB_release_resource_ptr=NULL, BLAS_Cpp::Uplo MB_uplo=BLAS_Cpp::lower, DMatrixSlice *UB=NULL, const release_resource_ptr_t &amp;UB_release_resource_ptr=NULL, BLAS_Cpp::Uplo UB_uplo=BLAS_Cpp::lower, bool update_factor=false, value_type scale=1.0)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initialize</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixSymPosDefBandedChol.html</anchorfile>
      <anchor>a3549915cec7b5d44f996723f8dbd14db</anchor>
      <arglist>(size_type n=0, size_type kd=0, DMatrixSlice *MB=NULL, const release_resource_ptr_t &amp;MB_release_resource_ptr=NULL, BLAS_Cpp::Uplo MB_uplo=BLAS_Cpp::lower, DMatrixSlice *UB=NULL, const release_resource_ptr_t &amp;UB_release_resource_ptr=NULL, BLAS_Cpp::Uplo UB_uplo=BLAS_Cpp::lower, bool update_factor=false, value_type scale=1.0)</arglist>
    </member>
    <member kind="function">
      <type>size_type</type>
      <name>kd</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixSymPosDefBandedChol.html</anchorfile>
      <anchor>ac63b9f317648a8de5e34c524c96d1431</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>DMatrixSlice &amp;</type>
      <name>MB</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixSymPosDefBandedChol.html</anchorfile>
      <anchor>ab7299155b714b0a8e96b9b9207290d1c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const DMatrixSlice &amp;</type>
      <name>MB</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixSymPosDefBandedChol.html</anchorfile>
      <anchor>af59231a26cef7f975e5e7a1b9f5259c1</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>BLAS_Cpp::Uplo</type>
      <name>MB_uplo</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixSymPosDefBandedChol.html</anchorfile>
      <anchor>aeab6ca5a1d6ade0b4c2f9576741041a4</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>DMatrixSlice &amp;</type>
      <name>UB</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixSymPosDefBandedChol.html</anchorfile>
      <anchor>a93d5f1c19a24d68819a9013e9b9957c9</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const DMatrixSlice &amp;</type>
      <name>UB</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixSymPosDefBandedChol.html</anchorfile>
      <anchor>a5f79010b9c80856123b1a3766ff156e8</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>BLAS_Cpp::Uplo</type>
      <name>UB_uplo</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixSymPosDefBandedChol.html</anchorfile>
      <anchor>a836721b900d2b43e510731974c725cf3</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>size_type</type>
      <name>rows</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixSymPosDefBandedChol.html</anchorfile>
      <anchor>a73240d772c37cbb7218006d672230feb</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>size_type</type>
      <name>nz</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixSymPosDefBandedChol.html</anchorfile>
      <anchor>a69ee04e9741c0234769987e2463c6aab</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>std::ostream &amp;</type>
      <name>output</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixSymPosDefBandedChol.html</anchorfile>
      <anchor>a7086f164cbf3adf9342a3f3266a63858</anchor>
      <arglist>(std::ostream &amp;out) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Vp_StMtV</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixSymPosDefBandedChol.html</anchorfile>
      <anchor>a8088adcaca2a60f0e792e93f795458eb</anchor>
      <arglist>(DVectorSlice *vs_lhs, value_type alpha, BLAS_Cpp::Transp trans_rhs1, const DVectorSlice &amp;vs_rhs2, value_type beta) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Vp_StMtV</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixSymPosDefBandedChol.html</anchorfile>
      <anchor>a28c7e1e0da6e789dab2d4bfdad93f779</anchor>
      <arglist>(DVectorSlice *vs_lhs, value_type alpha, BLAS_Cpp::Transp trans_rhs1, const SpVectorSlice &amp;sv_rhs2, value_type beta) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Vp_StPtMtV</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixSymPosDefBandedChol.html</anchorfile>
      <anchor>a4e17a564c28690b69306be90c787168e</anchor>
      <arglist>(DVectorSlice *vs_lhs, value_type alpha, const GenPermMatrixSlice &amp;P_rhs1, BLAS_Cpp::Transp P_rhs1_trans, BLAS_Cpp::Transp M_rhs2_trans, const DVectorSlice &amp;vs_rhs3, value_type beta) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Vp_StPtMtV</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixSymPosDefBandedChol.html</anchorfile>
      <anchor>afdb415f97215f4c318409dbb574672ff</anchor>
      <arglist>(DVectorSlice *vs_lhs, value_type alpha, const GenPermMatrixSlice &amp;P_rhs1, BLAS_Cpp::Transp P_rhs1_trans, BLAS_Cpp::Transp M_rhs2_trans, const SpVectorSlice &amp;sv_rhs3, value_type beta) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>V_InvMtV</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixSymPosDefBandedChol.html</anchorfile>
      <anchor>ab5c5bb1893fc99c4430c64a634a33878</anchor>
      <arglist>(DVectorSlice *vs_lhs, BLAS_Cpp::Transp trans_rhs1, const DVectorSlice &amp;vs_rhs2) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ConstrainedOptPack::MatrixSymPosDefInvCholFactor</name>
    <filename>classConstrainedOptPack_1_1MatrixSymPosDefInvCholFactor.html</filename>
    <base virtualness="virtual">MatrixWithOpConcreteEncap&lt; SymInvCholMatrix &gt;</base>
    <base>AbstractLinAlgPack::MatrixExtractInvCholFactor</base>
    <base virtualness="virtual">SerializationPack::Serializable</base>
    <member kind="function">
      <type></type>
      <name>MatrixSymPosDefInvCholFactor</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixSymPosDefInvCholFactor.html</anchorfile>
      <anchor>a5d22a64923864abc757edbd8fa751b2f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>MatrixSymPosDefInvCholFactor</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixSymPosDefInvCholFactor.html</anchorfile>
      <anchor>abf343abfd312cdf1580ef7e0f85cfff3</anchor>
      <arglist>(const SymInvCholMatrix &amp;m)</arglist>
    </member>
    <member kind="function">
      <type>size_type</type>
      <name>cols</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixSymPosDefInvCholFactor.html</anchorfile>
      <anchor>abbf4848d4c92c91e7d966800ba8c4e1e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>MatrixOp &amp;</type>
      <name>operator=</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixSymPosDefInvCholFactor.html</anchorfile>
      <anchor>a64822ce0c0cd190a9a08a78cdb5ccade</anchor>
      <arglist>(const MatrixOp &amp;m)</arglist>
    </member>
    <member kind="function">
      <type>std::ostream &amp;</type>
      <name>output</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixSymPosDefInvCholFactor.html</anchorfile>
      <anchor>a2e7d7484bea3da5ab70f62c063bfb917</anchor>
      <arglist>(std::ostream &amp;out) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Vp_StMtV</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixSymPosDefInvCholFactor.html</anchorfile>
      <anchor>a9cf08199e8327599488cd599eabf6a24</anchor>
      <arglist>(DVectorSlice *vs_lhs, value_type alpha, BLAS_Cpp::Transp trans_rhs1, const DVectorSlice &amp;vs_rhs2, value_type beta) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Vp_StMtV</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixSymPosDefInvCholFactor.html</anchorfile>
      <anchor>ac7b6d2e86c9b19d2023e1d49a441f8e7</anchor>
      <arglist>(DVectorSlice *vs_lhs, value_type alpha, BLAS_Cpp::Transp trans_rhs1, const SpVectorSlice &amp;sv_rhs2, value_type beta) const </arglist>
    </member>
    <member kind="function">
      <type>value_type</type>
      <name>transVtMtV</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixSymPosDefInvCholFactor.html</anchorfile>
      <anchor>ab21fa307b7fc5b69fd3206fd473e7ad7</anchor>
      <arglist>(const DVectorSlice &amp;vs_rhs1, BLAS_Cpp::Transp trans_rhs2, const DVectorSlice &amp;vs_rhs3) const </arglist>
    </member>
    <member kind="function">
      <type>value_type</type>
      <name>transVtMtV</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixSymPosDefInvCholFactor.html</anchorfile>
      <anchor>a7b09a888bbec13172361b4ca82e0211b</anchor>
      <arglist>(const SpVectorSlice &amp;sv_rhs1, BLAS_Cpp::Transp trans_rhs2, const SpVectorSlice &amp;sv_rhs3) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>V_InvMtV</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixSymPosDefInvCholFactor.html</anchorfile>
      <anchor>a1e4702eb966c61f7b65e75a9aa567f55</anchor>
      <arglist>(DVector *v_lhs, BLAS_Cpp::Transp trans_rhs1, const DVectorSlice &amp;vs_rhs2) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>V_InvMtV</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixSymPosDefInvCholFactor.html</anchorfile>
      <anchor>aab0bae6e3e25f5540155a851ec29f0bb</anchor>
      <arglist>(DVectorSlice *vs_lhs, BLAS_Cpp::Transp trans_rhs1, const DVectorSlice &amp;vs_rhs2) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>V_InvMtV</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixSymPosDefInvCholFactor.html</anchorfile>
      <anchor>ac7468e5ab48f19989e3690e1864817b6</anchor>
      <arglist>(DVector *v_lhs, BLAS_Cpp::Transp trans_rhs1, const SpVectorSlice &amp;sv_rhs2) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>V_InvMtV</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixSymPosDefInvCholFactor.html</anchorfile>
      <anchor>ae135d7a458987daf834637d089ecdbc1</anchor>
      <arglist>(DVectorSlice *vs_lhs, BLAS_Cpp::Transp trans_rhs1, const SpVectorSlice &amp;sv_rhs2) const </arglist>
    </member>
    <member kind="function">
      <type>value_type</type>
      <name>transVtInvMtV</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixSymPosDefInvCholFactor.html</anchorfile>
      <anchor>a08e1f992eed7d1042f0ae7c6ce53ae2c</anchor>
      <arglist>(const DVectorSlice &amp;vs_rhs1, BLAS_Cpp::Transp trans_rhs2, const DVectorSlice &amp;vs_rhs3) const </arglist>
    </member>
    <member kind="function">
      <type>value_type</type>
      <name>transVtInvMtV</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixSymPosDefInvCholFactor.html</anchorfile>
      <anchor>a22afd710c0bbc0b660223d1c7b1bec3a</anchor>
      <arglist>(const SpVectorSlice &amp;sv_rhs1, BLAS_Cpp::Transp trans_rhs2, const SpVectorSlice &amp;sv_rhs3) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>M_StMtInvMtM</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixSymPosDefInvCholFactor.html</anchorfile>
      <anchor>a2808e62b84005d1ff954fbb944c983c2</anchor>
      <arglist>(DMatrixSliceSym *sym_gms_lhs, value_type alpha, const MatrixOp &amp;mwo, BLAS_Cpp::Transp mwo_trans, EMatrixDummyArg) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>init_identity</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixSymPosDefInvCholFactor.html</anchorfile>
      <anchor>a7702f25f218ff7b00927f06d0e59787a</anchor>
      <arglist>(size_type n, value_type alpha)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>init_diagonal</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixSymPosDefInvCholFactor.html</anchorfile>
      <anchor>a78925fbb41e29bba39b0dc07a9ebb936</anchor>
      <arglist>(const DVectorSlice &amp;diag)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>secant_update</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixSymPosDefInvCholFactor.html</anchorfile>
      <anchor>a61a5b8e52c2daf665870e67cba2a3b5b</anchor>
      <arglist>(DVectorSlice *s, DVectorSlice *y, DVectorSlice *Bs)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>extract_inv_chol</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixSymPosDefInvCholFactor.html</anchorfile>
      <anchor>a1a6fdd52f051ff8896176aede135b66f</anchor>
      <arglist>(DMatrixSliceTriEle *InvChol) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>serialize</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixSymPosDefInvCholFactor.html</anchorfile>
      <anchor>a9eabb83b6e7fd3bb03cad95f2236d0d1</anchor>
      <arglist>(std::ostream &amp;out) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>unserialize</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixSymPosDefInvCholFactor.html</anchorfile>
      <anchor>a6f51c158ef343771da4e3ebd071dd104</anchor>
      <arglist>(std::istream &amp;in)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ConstrainedOptPack::MatrixSymPosDefLBFGS</name>
    <filename>classConstrainedOptPack_1_1MatrixSymPosDefLBFGS.html</filename>
    <base>AbstractLinAlgPack::MatrixSymOpNonsing</base>
    <class kind="class">ConstrainedOptPack::MatrixSymPosDefLBFGS::PostMod</class>
    <member kind="function">
      <type></type>
      <name>MatrixSymPosDefLBFGS</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixSymPosDefLBFGS.html</anchorfile>
      <anchor>a652f60aa667b5a40fa68f9551c6cfccc</anchor>
      <arglist>(size_type max_size=0, size_type m=10, bool maintain_original=true, bool maintain_inverse=true, bool auto_rescaling=false)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixSymPosDefLBFGS.html</anchorfile>
      <anchor>ac2c56519405fd877f72c97fecfbcf423</anchor>
      <arglist>(bool, auto_rescaling)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initial_setup</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixSymPosDefLBFGS.html</anchorfile>
      <anchor>a6087170ba5ad076d431d57e939744751</anchor>
      <arglist>(size_type max_size=0, size_type m=10, bool maintain_original=true, bool maintain_inverse=true, bool auto_rescaling=false)</arglist>
    </member>
    <member kind="function">
      <type>size_type</type>
      <name>m</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixSymPosDefLBFGS.html</anchorfile>
      <anchor>a2eb68e1a123d11a7d5bea8f1021492e8</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>size_type</type>
      <name>m_bar</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixSymPosDefLBFGS.html</anchorfile>
      <anchor>ab46930834d221e5130c4b1fb1cb4d7aa</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>size_type</type>
      <name>k_bar</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixSymPosDefLBFGS.html</anchorfile>
      <anchor>a5db1b603628fa402d66907f29f21a4d8</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>value_type</type>
      <name>gamma_k</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixSymPosDefLBFGS.html</anchorfile>
      <anchor>a3edd2cb25b838a4edf66045958379423</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const DMatrixSlice</type>
      <name>S</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixSymPosDefLBFGS.html</anchorfile>
      <anchor>a091d5bc95e25f12416bbcbdb70bf30cd</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const DMatrixSlice</type>
      <name>Y</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixSymPosDefLBFGS.html</anchorfile>
      <anchor>a567017dad8c4c20f17240e6a26f19d9e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>maintain_original</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixSymPosDefLBFGS.html</anchorfile>
      <anchor>acbdaf1d2b116dcb187b550497c88b05f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>maintain_inverse</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixSymPosDefLBFGS.html</anchorfile>
      <anchor>ad46782a49ab8b1fbe32b4211ac8c194d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>size_type</type>
      <name>num_secant_updates</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixSymPosDefLBFGS.html</anchorfile>
      <anchor>a1e13c52de00095869c31b7423721e5fb</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>size_type</type>
      <name>rows</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixSymPosDefLBFGS.html</anchorfile>
      <anchor>aed871b310a8adf43f0c7a2291dd4dcd8</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="typedef">
      <type>Teuchos::RCP&lt; const MultiVector &gt;</type>
      <name>multi_vec_ptr_t</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixSymPosDefLBFGS.html</anchorfile>
      <anchor>a9f9173bf6ae7fdf8a42cbf0a3a471baa</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>MatrixSymPosDefLBFGS</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixSymPosDefLBFGS.html</anchorfile>
      <anchor>aeea41ce0c4a46fa3c3a57856c5b9ee4f</anchor>
      <arglist>(size_type m=10, bool maintain_original=true, bool maintain_inverse=true, bool auto_rescaling=false)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixSymPosDefLBFGS.html</anchorfile>
      <anchor>ac2c56519405fd877f72c97fecfbcf423</anchor>
      <arglist>(bool, auto_rescaling)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initial_setup</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixSymPosDefLBFGS.html</anchorfile>
      <anchor>a1b11c9fd202b2ce261ef70351105ce73</anchor>
      <arglist>(size_type m=10, bool maintain_original=true, bool maintain_inverse=true, bool auto_rescaling=false)</arglist>
    </member>
    <member kind="function">
      <type>size_type</type>
      <name>m</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixSymPosDefLBFGS.html</anchorfile>
      <anchor>a2eb68e1a123d11a7d5bea8f1021492e8</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>size_type</type>
      <name>m_bar</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixSymPosDefLBFGS.html</anchorfile>
      <anchor>ab46930834d221e5130c4b1fb1cb4d7aa</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>value_type</type>
      <name>gamma_k</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixSymPosDefLBFGS.html</anchorfile>
      <anchor>a3edd2cb25b838a4edf66045958379423</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const multi_vec_ptr_t</type>
      <name>S</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixSymPosDefLBFGS.html</anchorfile>
      <anchor>a091d5bc95e25f12416bbcbdb70bf30cd</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const multi_vec_ptr_t</type>
      <name>Y</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixSymPosDefLBFGS.html</anchorfile>
      <anchor>a567017dad8c4c20f17240e6a26f19d9e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>maintain_original</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixSymPosDefLBFGS.html</anchorfile>
      <anchor>acbdaf1d2b116dcb187b550497c88b05f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>maintain_inverse</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixSymPosDefLBFGS.html</anchorfile>
      <anchor>ad46782a49ab8b1fbe32b4211ac8c194d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>size_type</type>
      <name>num_secant_updates</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixSymPosDefLBFGS.html</anchorfile>
      <anchor>a1e13c52de00095869c31b7423721e5fb</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const VectorSpace &amp;</type>
      <name>space_cols</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixSymPosDefLBFGS.html</anchorfile>
      <anchor>aef86202cd86e823273bf29d6250125a5</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>std::ostream &amp;</type>
      <name>output</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixSymPosDefLBFGS.html</anchorfile>
      <anchor>a7a3fc2fec5dafed6f0dea3af5bd36d01</anchor>
      <arglist>(std::ostream &amp;out) const </arglist>
    </member>
    <member kind="function">
      <type>MatrixOp &amp;</type>
      <name>operator=</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixSymPosDefLBFGS.html</anchorfile>
      <anchor>a6690089c8e338df3e31e4d1ce4b9d75d</anchor>
      <arglist>(const MatrixOp &amp;mwo)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Vp_StMtV</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixSymPosDefLBFGS.html</anchorfile>
      <anchor>a9e204e407eece003e7e8b625368da295</anchor>
      <arglist>(VectorMutable *v_lhs, value_type alpha, BLAS_Cpp::Transp trans_rhs1, const Vector &amp;v_rhs2, value_type beta) const </arglist>
    </member>
    <member kind="function">
      <type>std::ostream &amp;</type>
      <name>output</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixSymPosDefLBFGS.html</anchorfile>
      <anchor>a8c5b955f599f0d9c2949291a378e1226</anchor>
      <arglist>(std::ostream &amp;out) const </arglist>
    </member>
    <member kind="function">
      <type>MatrixOp &amp;</type>
      <name>operator=</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixSymPosDefLBFGS.html</anchorfile>
      <anchor>a78dbbd9a5444dcdb860298c1e01cdb53</anchor>
      <arglist>(const MatrixOp &amp;m)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Vp_StMtV</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixSymPosDefLBFGS.html</anchorfile>
      <anchor>aaead81924b1df527a119a64d29837264</anchor>
      <arglist>(DVectorSlice *vs_lhs, value_type alpha, BLAS_Cpp::Transp trans_rhs1, const DVectorSlice &amp;vs_rhs2, value_type beta) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>V_InvMtV</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixSymPosDefLBFGS.html</anchorfile>
      <anchor>a5220a940686fc508074944ffeffe87be</anchor>
      <arglist>(VectorMutable *v_lhs, BLAS_Cpp::Transp trans_rhs1, const Vector &amp;v_rhs2) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>init_identity</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixSymPosDefLBFGS.html</anchorfile>
      <anchor>ad31a5e4686c70e829ee554fa92a0f3c6</anchor>
      <arglist>(const VectorSpace &amp;space_diag, value_type alpha)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>init_diagonal</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixSymPosDefLBFGS.html</anchorfile>
      <anchor>a2fbe63316bd210c303b8d32e3ca1155c</anchor>
      <arglist>(const Vector &amp;diag)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>secant_update</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixSymPosDefLBFGS.html</anchorfile>
      <anchor>a51c2c1e4faada4acd3719d7027220fbb</anchor>
      <arglist>(VectorMutable *s, VectorMutable *y, VectorMutable *Bs)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>init_identity</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixSymPosDefLBFGS.html</anchorfile>
      <anchor>a7c52aca0820ccaed9f9eb74ea8f386c4</anchor>
      <arglist>(size_type n, value_type alpha)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>init_diagonal</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixSymPosDefLBFGS.html</anchorfile>
      <anchor>a8931c4c06574701a94c46c636477853c</anchor>
      <arglist>(const DVectorSlice &amp;diag)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>secant_update</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixSymPosDefLBFGS.html</anchorfile>
      <anchor>af6869ccf87e385be1b296f0d4813b159</anchor>
      <arglist>(DVectorSlice *s, DVectorSlice *y, DVectorSlice *Bs)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>V_InvMtV</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixSymPosDefLBFGS.html</anchorfile>
      <anchor>a4fbdcf6fc0137633bd7cb844d63eaa61</anchor>
      <arglist>(DVectorSlice *v_lhs, BLAS_Cpp::Transp trans_rhs1, const DVectorSlice &amp;vs_rhs2) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initialize</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixSymPosDefLBFGS.html</anchorfile>
      <anchor>a47f0412e940ac4f8f97cbbeb70f64628</anchor>
      <arglist>(value_type alpha, size_type max_size)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initialize</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixSymPosDefLBFGS.html</anchorfile>
      <anchor>adebc3ea0dd7bba86cad23f5cab484a06</anchor>
      <arglist>(const DMatrixSliceSym &amp;A, size_type max_size, bool force_factorization, Inertia inertia, PivotTolerances pivot_tols)</arglist>
    </member>
    <member kind="function">
      <type>size_type</type>
      <name>max_size</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixSymPosDefLBFGS.html</anchorfile>
      <anchor>ab896ab436623848b1c6e466fdd1a1b14</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Inertia</type>
      <name>inertia</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixSymPosDefLBFGS.html</anchorfile>
      <anchor>a6c30ef89004f9810d52dec013cdb838d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_uninitialized</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixSymPosDefLBFGS.html</anchorfile>
      <anchor>a409f8acde43608c825c42a39e114cffe</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>augment_update</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixSymPosDefLBFGS.html</anchorfile>
      <anchor>a62047d151e947fea6e0e110b866c720f</anchor>
      <arglist>(const DVectorSlice *t, value_type alpha, bool force_refactorization, EEigenValType add_eigen_val, PivotTolerances pivot_tols)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>delete_update</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixSymPosDefLBFGS.html</anchorfile>
      <anchor>ac42992b6f663c17540af4789692e4ac6</anchor>
      <arglist>(size_type jd, bool force_refactorization, EEigenValType drop_eigen_val, PivotTolerances pivot_tols)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ConstrainedOptPack::MatrixSymPosDefLBFGS::PostMod</name>
    <filename>classConstrainedOptPack_1_1MatrixSymPosDefLBFGS_1_1PostMod.html</filename>
    <member kind="function">
      <type></type>
      <name>PostMod</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixSymPosDefLBFGS_1_1PostMod.html</anchorfile>
      <anchor>a931da2f82e135359d9ca1f4e9b0bc2a9</anchor>
      <arglist>(size_type m=10, bool maintain_original=true, bool maintain_inverse=true, bool auto_rescaling=false)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initialize</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixSymPosDefLBFGS_1_1PostMod.html</anchorfile>
      <anchor>a740e700888dc39b473c4381e6f07f136</anchor>
      <arglist>(MatrixSymPosDefLBFGS *p) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ConstrainedOptPack::MatrixVarReductImplicit</name>
    <filename>classConstrainedOptPack_1_1MatrixVarReductImplicit.html</filename>
    <base>AbstractLinAlgPack::MatrixOp</base>
    <member kind="typedef">
      <type>Teuchos::RCP&lt; const MatrixOpNonsing &gt;</type>
      <name>mat_nonsing_ptr_t</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixVarReductImplicit.html</anchorfile>
      <anchor>a99e74d5e9e7b9faa8e8c741e7aa330f9</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Teuchos::RCP&lt; const MatrixOp &gt;</type>
      <name>mat_ptr_t</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixVarReductImplicit.html</anchorfile>
      <anchor>af5ec70a79a589b7a3667754e1d5db5bd</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>initialize</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixVarReductImplicit.html</anchorfile>
      <anchor>a7a4eee7b309a0a1d13cf75c2a9d7e241</anchor>
      <arglist>(const mat_nonsing_ptr_t &amp;C, const mat_ptr_t &amp;N, const mat_ptr_t &amp;D_direct)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>set_uninitialized</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixVarReductImplicit.html</anchorfile>
      <anchor>a5796fa21aa0fcae3eae338cc666c011a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const mat_nonsing_ptr_t &amp;</type>
      <name>C_ptr</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixVarReductImplicit.html</anchorfile>
      <anchor>a8d95a1bc8abb33faa853851ccd129721</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const mat_ptr_t &amp;</type>
      <name>N_ptr</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixVarReductImplicit.html</anchorfile>
      <anchor>a047e3111f2bfb1c37dc874cff2d81e87</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const mat_ptr_t &amp;</type>
      <name>D_direct_ptr</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixVarReductImplicit.html</anchorfile>
      <anchor>a9b66a1d5f003bb31ed498dfe05c17b1b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>size_type</type>
      <name>rows</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixVarReductImplicit.html</anchorfile>
      <anchor>aa76842b3ca0f1a9b6af549fa82954dc1</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>size_type</type>
      <name>cols</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixVarReductImplicit.html</anchorfile>
      <anchor>a50b6dfb07b34e825219ef8d1f23a8dbf</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const VectorSpace &amp;</type>
      <name>space_cols</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixVarReductImplicit.html</anchorfile>
      <anchor>a0688c432c4e73334b4630c503202f768</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const VectorSpace &amp;</type>
      <name>space_rows</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixVarReductImplicit.html</anchorfile>
      <anchor>acc2ec73649320149417149e7deb1167a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>MatrixOp &amp;</type>
      <name>operator=</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixVarReductImplicit.html</anchorfile>
      <anchor>ae59bd837403ec7c0318baa05e9d3308d</anchor>
      <arglist>(const MatrixOp &amp;M)</arglist>
    </member>
    <member kind="function">
      <type>std::ostream &amp;</type>
      <name>output</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixVarReductImplicit.html</anchorfile>
      <anchor>a7639536047b8aae713cb7c1fb9677b66</anchor>
      <arglist>(std::ostream &amp;) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Vp_StMtV</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixVarReductImplicit.html</anchorfile>
      <anchor>a669dc409c5e1d439eeb21cccbe9fcded</anchor>
      <arglist>(VectorMutable *v_lhs, value_type alpha, BLAS_Cpp::Transp trans_rhs1, const Vector &amp;v_rhs2, value_type beta) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Vp_StMtV</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixVarReductImplicit.html</anchorfile>
      <anchor>a009ee88ad89f5871fe70117277a68108</anchor>
      <arglist>(VectorMutable *v_lhs, value_type alpha, BLAS_Cpp::Transp trans_rhs1, const SpVectorSlice &amp;sv_rhs2, value_type beta) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Vp_StPtMtV</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixVarReductImplicit.html</anchorfile>
      <anchor>af3b8f9f64b9ea89a9883454b1d085d48</anchor>
      <arglist>(VectorMutable *v_lhs, value_type alpha, const GenPermMatrixSlice &amp;P_rhs1, BLAS_Cpp::Transp P_rhs1_trans, BLAS_Cpp::Transp M_rhs2_trans, const Vector &amp;v_rhs3, value_type beta) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Vp_StPtMtV</name>
      <anchorfile>classConstrainedOptPack_1_1MatrixVarReductImplicit.html</anchorfile>
      <anchor>a1509c8a88e4e8932435015a66b35abcf</anchor>
      <arglist>(VectorMutable *v_lhs, value_type alpha, const GenPermMatrixSlice &amp;P_rhs1, BLAS_Cpp::Transp P_rhs1_trans, BLAS_Cpp::Transp M_rhs2_trans, const SpVectorSlice &amp;sv_rhs3, value_type beta) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ConstrainedOptPack::VariableBoundsTester</name>
    <filename>classConstrainedOptPack_1_1VariableBoundsTester.html</filename>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classConstrainedOptPack_1_1VariableBoundsTester.html</anchorfile>
      <anchor>a094f162b5946d48beddfde27efa00b64</anchor>
      <arglist>(value_type, warning_tol)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classConstrainedOptPack_1_1VariableBoundsTester.html</anchorfile>
      <anchor>a88e371e45c6cf2297b160fb95f315718</anchor>
      <arglist>(value_type, error_tol)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>VariableBoundsTester</name>
      <anchorfile>classConstrainedOptPack_1_1VariableBoundsTester.html</anchorfile>
      <anchor>a2f3dae1bb894e35bea6cf1013f4950ec</anchor>
      <arglist>(value_type warning_tol=1e-10, value_type error_tol=1e-5)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~VariableBoundsTester</name>
      <anchorfile>classConstrainedOptPack_1_1VariableBoundsTester.html</anchorfile>
      <anchor>a1b4637623cc75dcb2dcbc3b55c01a354</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>check_in_bounds</name>
      <anchorfile>classConstrainedOptPack_1_1VariableBoundsTester.html</anchorfile>
      <anchor>a1db1ac5c2f3749f44c6730abe06bd02c</anchor>
      <arglist>(std::ostream *out, bool print_all_warnings, bool print_vectors, const Vector &amp;xL, const char xL_name[], const Vector &amp;xU, const char xU_name[], const Vector &amp;x, const char x_name[])</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ConstrainedOptPack::VariableBoundsTesterSetOptions</name>
    <filename>classConstrainedOptPack_1_1VariableBoundsTesterSetOptions.html</filename>
    <base>OptionsFromStreamPack::SetOptionsFromStreamNode</base>
    <base>OptionsFromStreamPack::SetOptionsToTargetBase</base>
    <member kind="function">
      <type></type>
      <name>VariableBoundsTesterSetOptions</name>
      <anchorfile>classConstrainedOptPack_1_1VariableBoundsTesterSetOptions.html</anchorfile>
      <anchor>a361530b9aee118550e990f0c66102cd8</anchor>
      <arglist>(VariableBoundsTester *target=0, const char opt_grp_name[]=&quot;VariableBoundsTester&quot;)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>setOption</name>
      <anchorfile>classConstrainedOptPack_1_1VariableBoundsTesterSetOptions.html</anchorfile>
      <anchor>a733431cfcde5edc7e12b6259fa978e97</anchor>
      <arglist>(int option_num, const std::string &amp;option_value)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ConstrainedOptPack::QPSchur</name>
    <filename>classConstrainedOptPack_1_1QPSchur.html</filename>
    <class kind="class">ConstrainedOptPack::QPSchur::ActiveSet</class>
    <class kind="class">ConstrainedOptPack::QPSchur::DualInfeasibleException</class>
    <class kind="class">ConstrainedOptPack::QPSchur::InconsistantConstraintsException</class>
    <class kind="class">ConstrainedOptPack::QPSchur::NumericalInstabilityException</class>
    <class kind="class">ConstrainedOptPack::QPSchur::TestFailed</class>
    <class kind="class">ConstrainedOptPack::QPSchur::U_hat_t</class>
    <member kind="function">
      <type>const ActiveSet &amp;</type>
      <name>act_set</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchur.html</anchorfile>
      <anchor>a98182578f839b2d01885cadbe8e7652c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>dump_act_set_quantities</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchur.html</anchorfile>
      <anchor>a7e6b1a7b3af515650603df91efbc34ed</anchor>
      <arglist>(const ActiveSet &amp;act_set, std::ostream &amp;out, bool print_S_hat=true)</arglist>
    </member>
    <member kind="enumeration">
      <name>EPDSteps</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchur.html</anchorfile>
      <anchor>a7715fd62f5b2bc3f5c707198f2ea569d</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>EIterRefineReturn</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchur.html</anchorfile>
      <anchor>acfe3211aff3216b383824dfddd7e02aa</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual ESolveReturn</type>
      <name>qp_algo</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchur.html</anchorfile>
      <anchor>aa6627a88656a9348982eb322793063b5</anchor>
      <arglist>(EPDSteps first_step, std::ostream *out, EOutputLevel output_level, ERunTests test_what, const DVectorSlice &amp;vo, ActiveSet *act_set, DVectorSlice *v, DVectorSlice *x, size_type *iter, size_type *num_adds, size_type *num_drops, size_type *iter_refine_num_resid, size_type *iter_refine_num_solves, StopWatchPack::stopwatch *timer)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual void</type>
      <name>set_x</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchur.html</anchorfile>
      <anchor>a2e9b8b20fc9ab0681937399d6364cab5</anchor>
      <arglist>(const ActiveSet &amp;act_set, const DVectorSlice &amp;v, DVectorSlice *x)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual void</type>
      <name>set_multipliers</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchur.html</anchorfile>
      <anchor>a0a58a42f0e791373a7a06af9ed2e0e13</anchor>
      <arglist>(const ActiveSet &amp;act_set, const DVectorSlice &amp;v, SpVector *mu, DVectorSlice *lambda, SpVector *lambda_breve)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>bool</type>
      <name>timeout_return</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchur.html</anchorfile>
      <anchor>a6134c73e47a9ce0bbb3dd4a7e9bb2729</anchor>
      <arglist>(StopWatchPack::stopwatch *timer, std::ostream *out, EOutputLevel output_level) const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>EIterRefineReturn</type>
      <name>iter_refine</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchur.html</anchorfile>
      <anchor>a558b3f174b515ba2f3bc83979f953396</anchor>
      <arglist>(const ActiveSet &amp;act_set, std::ostream *out, EOutputLevel output_level, const value_type ao, const DVectorSlice *bo, const value_type aa, const DVectorSlice *ba, DVectorSlice *v, DVectorSlice *z, size_type *iter_refine_num_resid, size_type *iter_refine_num_solves)</arglist>
    </member>
    <member kind="enumeration">
      <name>ERunTests</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchur.html</anchorfile>
      <anchor>a43e81f0e510935ec444fe8069acbe199</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>ESolveReturn</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchur.html</anchorfile>
      <anchor>af1115a9ebcc62e52afa0a04821261b5c</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>EOutputLevel</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchur.html</anchorfile>
      <anchor>a0903983bb6bd717ac7333d2fa55bd2b5</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>QPSchurPack::QP</type>
      <name>QP</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchur.html</anchorfile>
      <anchor>aef54b2422739a6d2519fffc430cde601</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>MatrixSymAddDelUpdateable</type>
      <name>MSADU</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchur.html</anchorfile>
      <anchor>a1fc2d6efa8239ba13715f02f3ba290a7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static value_type</type>
      <name>DEGENERATE_MULT</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchur.html</anchorfile>
      <anchor>af22751aeeca1f966beb68369e061d4ce</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_COMPOSITION_MEMBERS</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchur.html</anchorfile>
      <anchor>a97bcc6876402932c713224f9e0c5751f</anchor>
      <arglist>(MatrixSymAddDelUpdateableWithOpNonsingular, schur_comp)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchur.html</anchorfile>
      <anchor>a5eb37839dc5140ab4c363d9541b2eaf9</anchor>
      <arglist>(size_type, max_iter)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchur.html</anchorfile>
      <anchor>aa8f5a130ea4875589ddeda7bbc5ad495</anchor>
      <arglist>(value_type, max_real_runtime)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchur.html</anchorfile>
      <anchor>a6f6ef736c4e8f1649377361d5474e06d</anchor>
      <arglist>(value_type, feas_tol)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchur.html</anchorfile>
      <anchor>ac2d820b121b799efd21829dfeae348a5</anchor>
      <arglist>(value_type, loose_feas_tol)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchur.html</anchorfile>
      <anchor>a202b26267e4f53d4ed5c5a09109b827b</anchor>
      <arglist>(value_type, dual_infeas_tol)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchur.html</anchorfile>
      <anchor>a440ac8abf336ee0f64ec758e1ac762a7</anchor>
      <arglist>(value_type, huge_primal_step)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchur.html</anchorfile>
      <anchor>a994cbfc27602a7d65a3b1a2fac9324f4</anchor>
      <arglist>(value_type, huge_dual_step)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchur.html</anchorfile>
      <anchor>a5d3a933f542eca026960d100e608982a</anchor>
      <arglist>(value_type, warning_tol)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchur.html</anchorfile>
      <anchor>a69911450c045ddf1d6189912ac669026</anchor>
      <arglist>(value_type, error_tol)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchur.html</anchorfile>
      <anchor>a42406338cb08cbb13287f272d97ff66d</anchor>
      <arglist>(size_type, iter_refine_min_iter)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchur.html</anchorfile>
      <anchor>a0ab1bd9c617239f3fd1bc5ec40776dd3</anchor>
      <arglist>(size_type, iter_refine_max_iter)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchur.html</anchorfile>
      <anchor>a58de3955144d9bb76eae08aa9eba9749</anchor>
      <arglist>(value_type, iter_refine_opt_tol)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchur.html</anchorfile>
      <anchor>ae88c6f36c5e64ae3891e089f371d3ba1</anchor>
      <arglist>(value_type, iter_refine_feas_tol)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchur.html</anchorfile>
      <anchor>a39dd06860f67abc2b97acaadbd4514e7</anchor>
      <arglist>(bool, iter_refine_at_solution)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchur.html</anchorfile>
      <anchor>a47b9558efd9ba567e11db3a17a391416</anchor>
      <arglist>(bool, salvage_init_schur_comp)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>pivot_tols</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchur.html</anchorfile>
      <anchor>a976a848852e303ce22c2ef6c1b69dc3f</anchor>
      <arglist>(MSADU::PivotTolerances pivot_tols)</arglist>
    </member>
    <member kind="function">
      <type>MSADU::PivotTolerances</type>
      <name>pivot_tols</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchur.html</anchorfile>
      <anchor>a39056ecc80586f34419d3d8844578103</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~QPSchur</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchur.html</anchorfile>
      <anchor>adc84f488f286b4160da5dd149833fc27</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>QPSchur</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchur.html</anchorfile>
      <anchor>a586b420fa7ed698ff408bee3ae69a73f</anchor>
      <arglist>(const schur_comp_ptr_t &amp;schur_comp=Teuchos::null, size_type max_iter=100, value_type max_real_runtime=1e+20, value_type feas_tol=1e-8, value_type loose_feas_tol=1e-6, value_type dual_infeas_tol=1e-12, value_type huge_primal_step=1e+20, value_type huge_dual_step=1e+20, value_type warning_tol=1e-10, value_type error_tol=1e-5, size_type iter_refine_min_iter=1, size_type iter_refine_max_iter=3, value_type iter_refine_opt_tol=1e-12, value_type iter_refine_feas_tol=1e-12, bool iter_refine_at_solution=true, bool salvage_init_schur_comp=true, MSADU::PivotTolerances pivot_tols=MSADU::PivotTolerances(1e-8, 1e-11, 1e-11))</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual ESolveReturn</type>
      <name>solve_qp</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchur.html</anchorfile>
      <anchor>aed401870a2f45e415393558c44942627</anchor>
      <arglist>(QP &amp;qp, size_type num_act_change, const int ij_act_change[], const EBounds bnds[], std::ostream *out, EOutputLevel output_level, ERunTests test_what, DVectorSlice *x, SpVector *mu, DVectorSlice *lambda, SpVector *lambda_breve, size_type *iter, size_type *num_adds, size_type *num_drops)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ConstrainedOptPack::QPSchur::ActiveSet</name>
    <filename>classConstrainedOptPack_1_1QPSchur_1_1ActiveSet.html</filename>
    <member kind="typedef">
      <type>QPSchurPack::QP</type>
      <name>QP</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchur_1_1ActiveSet.html</anchorfile>
      <anchor>a79f7adcb95f13e9d3dbe6d1ecdb68070</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>MatrixSymAddDelUpdateable</type>
      <name>MSADU</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchur_1_1ActiveSet.html</anchorfile>
      <anchor>a79585701bf20df624e0d6cfbaca4a7aa</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_COMPOSITION_MEMBERS</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchur_1_1ActiveSet.html</anchorfile>
      <anchor>a28058bca514f4c816a0ca780db638a03</anchor>
      <arglist>(MatrixSymAddDelUpdateableWithOpNonsingular, schur_comp)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchur_1_1ActiveSet.html</anchorfile>
      <anchor>aa0413a9c7af8a8ac935ecb886388bb59</anchor>
      <arglist>(MSADU::PivotTolerances, pivot_tols)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ActiveSet</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchur_1_1ActiveSet.html</anchorfile>
      <anchor>a6451e1f07e5eec82809e1c0fc145f48c</anchor>
      <arglist>(const schur_comp_ptr_t &amp;schur_comp, MSADU::PivotTolerances pivot_tols=MSADU::PivotTolerances(1e-6, 1e-8, 1e-8))</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initialize</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchur_1_1ActiveSet.html</anchorfile>
      <anchor>a8ec18bd0d765206150ccc64af4ee80ab</anchor>
      <arglist>(QP &amp;qp, size_type num_act_change, const int ij_act_change[], const EBounds bnds[], bool test, bool salvage_init_schur_comp, std::ostream *out, EOutputLevel output_level)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>refactorize_schur_comp</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchur_1_1ActiveSet.html</anchorfile>
      <anchor>a064d7ccc6c5367b02711023a3dfb8ca4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>add_constraint</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchur_1_1ActiveSet.html</anchorfile>
      <anchor>a9d68024174324f62d6e2f15bd82676cd</anchor>
      <arglist>(size_type ja, EBounds bnd_ja, bool update_steps, std::ostream *out, EOutputLevel output_level, bool force_refactorization=true, bool allow_any_cond=false)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>drop_constraint</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchur_1_1ActiveSet.html</anchorfile>
      <anchor>ac72ec19a50f9b69bec963859708f454d</anchor>
      <arglist>(int jd, std::ostream *out, EOutputLevel output_level, bool force_refactorization=true, bool allow_any_cond=false)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>drop_add_constraints</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchur_1_1ActiveSet.html</anchorfile>
      <anchor>ae80bb38b0b614f67c0122d57e0fbb353</anchor>
      <arglist>(int jd, size_type ja, EBounds bnd_ja, bool update_steps, std::ostream *out, EOutputLevel output_level)</arglist>
    </member>
    <member kind="function">
      <type>QP &amp;</type>
      <name>qp</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchur_1_1ActiveSet.html</anchorfile>
      <anchor>a36936bb3c66799df0107d819f499a66d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const QP &amp;</type>
      <name>qp</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchur_1_1ActiveSet.html</anchorfile>
      <anchor>ad2c9e029ae21fec40dba031c07344598</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>size_type</type>
      <name>q_hat</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchur_1_1ActiveSet.html</anchorfile>
      <anchor>a484f3bfa26e99950bc2889efc0ddbd9a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>size_type</type>
      <name>q_plus_hat</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchur_1_1ActiveSet.html</anchorfile>
      <anchor>a61870cea25fd429b7df7251a37b53573</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>size_type</type>
      <name>q_F_hat</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchur_1_1ActiveSet.html</anchorfile>
      <anchor>ad444aa49ce5d8597be703fb0d957b4a8</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>size_type</type>
      <name>q_C_hat</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchur_1_1ActiveSet.html</anchorfile>
      <anchor>addd506bb2cbe7a7c5c45a800042c87ba</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>size_type</type>
      <name>q_D_hat</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchur_1_1ActiveSet.html</anchorfile>
      <anchor>a6b0991e65260ad444d188e748a8b7573</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ij_map</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchur_1_1ActiveSet.html</anchorfile>
      <anchor>a606044d10f876bc6a78edc0124777ddc</anchor>
      <arglist>(size_type s) const </arglist>
    </member>
    <member kind="function">
      <type>size_type</type>
      <name>s_map</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchur_1_1ActiveSet.html</anchorfile>
      <anchor>ab7a5df1f16e81e528667b78c2541c5e4</anchor>
      <arglist>(int ij) const </arglist>
    </member>
    <member kind="function">
      <type>value_type</type>
      <name>constr_norm</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchur_1_1ActiveSet.html</anchorfile>
      <anchor>ae2e07265d973d13037da22ddcc8f505e</anchor>
      <arglist>(size_type s) const </arglist>
    </member>
    <member kind="function">
      <type>EBounds</type>
      <name>bnd</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchur_1_1ActiveSet.html</anchorfile>
      <anchor>ab103b38d82a5b867fd07c7cd44c3f000</anchor>
      <arglist>(size_type s) const </arglist>
    </member>
    <member kind="function">
      <type>size_type</type>
      <name>l_fxfx</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchur_1_1ActiveSet.html</anchorfile>
      <anchor>a8bf929fccff29bc1f1275e8c616bfd30</anchor>
      <arglist>(size_type k) const </arglist>
    </member>
    <member kind="function">
      <type>const U_hat_t &amp;</type>
      <name>U_hat</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchur_1_1ActiveSet.html</anchorfile>
      <anchor>ae2747bdea42cad9f8481947d2a1aa653</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const MatrixSymOpNonsing &amp;</type>
      <name>S_hat</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchur_1_1ActiveSet.html</anchorfile>
      <anchor>abb9d10ed5e954dbdd8886f881e20e2e9</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const GenPermMatrixSlice &amp;</type>
      <name>P_XF_hat</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchur_1_1ActiveSet.html</anchorfile>
      <anchor>a131c12a5828c285efc38612a7a69468f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const GenPermMatrixSlice &amp;</type>
      <name>P_FC_hat</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchur_1_1ActiveSet.html</anchorfile>
      <anchor>a48f30c015faddcd5b0371a2d5c6db549</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const GenPermMatrixSlice &amp;</type>
      <name>P_plus_hat</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchur_1_1ActiveSet.html</anchorfile>
      <anchor>ad8ff21b1725203166e1f1db54ad1accc</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const GenPermMatrixSlice &amp;</type>
      <name>Q_XD_hat</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchur_1_1ActiveSet.html</anchorfile>
      <anchor>a2cd0c119cd32b780e9d02a2c1f70b8ee</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const DVectorSlice</type>
      <name>d_hat</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchur_1_1ActiveSet.html</anchorfile>
      <anchor>a80c0da1f00a9508ea9d994cb00be31d1</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>DVectorSlice</type>
      <name>z_hat</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchur_1_1ActiveSet.html</anchorfile>
      <anchor>acb56e2081272c1ab9db9df8c376fb2d1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const DVectorSlice</type>
      <name>z_hat</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchur_1_1ActiveSet.html</anchorfile>
      <anchor>a40759a36c6bc90f1722c3d359e9826ac</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>DVectorSlice</type>
      <name>p_z_hat</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchur_1_1ActiveSet.html</anchorfile>
      <anchor>ad3e93a874aea66e4baaa06bfa6d9e513</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const DVectorSlice</type>
      <name>p_z_hat</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchur_1_1ActiveSet.html</anchorfile>
      <anchor>ae02f37515009f772399f2e87058be3d7</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>DVectorSlice</type>
      <name>mu_D_hat</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchur_1_1ActiveSet.html</anchorfile>
      <anchor>a66affdeb6f484593f88e30b5e6e0c50e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const DVectorSlice</type>
      <name>mu_D_hat</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchur_1_1ActiveSet.html</anchorfile>
      <anchor>a3ef49a225e77e8900e2c2b25d99ca231</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>DVectorSlice</type>
      <name>p_mu_D_hat</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchur_1_1ActiveSet.html</anchorfile>
      <anchor>aeb84c89abe2b926ecf2c5dbcba8ab242</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const DVectorSlice</type>
      <name>p_mu_D_hat</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchur_1_1ActiveSet.html</anchorfile>
      <anchor>a70c15ac6f0a696fbbc9438a656732cb8</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>is_init_fixed</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchur_1_1ActiveSet.html</anchorfile>
      <anchor>a9424b99bdf545f751737a90e14682192</anchor>
      <arglist>(size_type j) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>all_dof_used_up</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchur_1_1ActiveSet.html</anchorfile>
      <anchor>ab182d66a2a00a15d213289f0e9ca0526</anchor>
      <arglist>() const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ConstrainedOptPack::QPSchur::DualInfeasibleException</name>
    <filename>classConstrainedOptPack_1_1QPSchur_1_1DualInfeasibleException.html</filename>
    <base>ConstrainedOptPack::QPSchur::NumericalInstabilityException</base>
  </compound>
  <compound kind="class">
    <name>ConstrainedOptPack::QPSchur::InconsistantConstraintsException</name>
    <filename>classConstrainedOptPack_1_1QPSchur_1_1InconsistantConstraintsException.html</filename>
  </compound>
  <compound kind="class">
    <name>ConstrainedOptPack::QPSchur::NumericalInstabilityException</name>
    <filename>classConstrainedOptPack_1_1QPSchur_1_1NumericalInstabilityException.html</filename>
  </compound>
  <compound kind="class">
    <name>ConstrainedOptPack::QPSchur::TestFailed</name>
    <filename>classConstrainedOptPack_1_1QPSchur_1_1TestFailed.html</filename>
  </compound>
  <compound kind="class">
    <name>ConstrainedOptPack::QPSchur::U_hat_t</name>
    <filename>classConstrainedOptPack_1_1QPSchur_1_1U__hat__t.html</filename>
    <base>AbstractLinAlgPack::MatrixOpSerial</base>
    <member kind="function">
      <type></type>
      <name>U_hat_t</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchur_1_1U__hat__t.html</anchorfile>
      <anchor>ad31cf4ce8bffa4165b4ab15761357e82</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initialize</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchur_1_1U__hat__t.html</anchorfile>
      <anchor>a5000e05d89cbd389b78ac0e44eb12fe7</anchor>
      <arglist>(const MatrixSymOp *G, const MatrixOp *A, const MatrixOp *A_bar, const GenPermMatrixSlice *Q_R, const GenPermMatrixSlice *P_XF_hat, const GenPermMatrixSlice *P_plus_hat)</arglist>
    </member>
    <member kind="function">
      <type>const MatrixSymOp &amp;</type>
      <name>G</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchur_1_1U__hat__t.html</anchorfile>
      <anchor>a142fd79db2659fb33e6f98c9992ee49d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const MatrixOp *</type>
      <name>A</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchur_1_1U__hat__t.html</anchorfile>
      <anchor>ae1d5c5ca7d128f0cfb0a176158674dde</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const MatrixOp &amp;</type>
      <name>A_bar</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchur_1_1U__hat__t.html</anchorfile>
      <anchor>ad539bd3893f800104abf4a6fc269e28b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const GenPermMatrixSlice &amp;</type>
      <name>Q_R</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchur_1_1U__hat__t.html</anchorfile>
      <anchor>ac927ce75e4be3886d0a166b304ef72a9</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const GenPermMatrixSlice &amp;</type>
      <name>P_XF_hat</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchur_1_1U__hat__t.html</anchorfile>
      <anchor>acee3bac4cf39a26d105ca5094e334d74</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const GenPermMatrixSlice &amp;</type>
      <name>P_plus_hat</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchur_1_1U__hat__t.html</anchorfile>
      <anchor>a70876199edfdf3f801e374ffa58f02c2</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>size_type</type>
      <name>rows</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchur_1_1U__hat__t.html</anchorfile>
      <anchor>a96f508b3a7b7b26bbeee057049e70bb6</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>size_type</type>
      <name>cols</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchur_1_1U__hat__t.html</anchorfile>
      <anchor>aa26bb7571a932da36d1a032739d68d35</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Vp_StMtV</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchur_1_1U__hat__t.html</anchorfile>
      <anchor>ab012ee4bba25349a67a11dfa91ab6360</anchor>
      <arglist>(DVectorSlice *vs_lhs, value_type alpha, BLAS_Cpp::Transp trans_rhs1, const DVectorSlice &amp;vs_rhs2, value_type beta) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Vp_StMtV</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchur_1_1U__hat__t.html</anchorfile>
      <anchor>a7bd9f7c7556b4e13c05bb2d9a58121e9</anchor>
      <arglist>(DVectorSlice *vs_lhs, value_type alpha, BLAS_Cpp::Transp trans_rhs1, const SpVectorSlice &amp;sv_rhs2, value_type beta) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ConstrainedOptPack::QPSchurInitKKTSystemHessianFixedFree</name>
    <filename>classConstrainedOptPack_1_1QPSchurInitKKTSystemHessianFixedFree.html</filename>
    <base>ConstrainedOptPack::QPSolverRelaxedQPSchur::InitKKTSystem</base>
    <member kind="function">
      <type>void</type>
      <name>initialize_kkt_system</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchurInitKKTSystemHessianFixedFree.html</anchorfile>
      <anchor>a1108a5dfb8ffbaefef6b909cdd70c478</anchor>
      <arglist>(const DVectorSlice &amp;g, const MatrixOp &amp;G, value_type etaL, const SpVectorSlice &amp;dL, const SpVectorSlice &amp;dU, const MatrixOp *F, BLAS_Cpp::Transp trans_F, const DVectorSlice *f, const DVectorSlice &amp;d, const SpVectorSlice &amp;nu, size_type *n_R, i_x_free_t *i_x_free, i_x_fixed_t *i_x_fixed, bnd_fixed_t *bnd_fixed, j_f_decomp_t *j_f_decomp, DVector *b_X, Ko_ptr_t *Ko, DVector *fo) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~InitKKTSystem</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxedQPSchur_1_1InitKKTSystem.html</anchorfile>
      <anchor>afe88b3e54b7c80d76897bcd29904ae23</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>initialize_kkt_system</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxedQPSchur_1_1InitKKTSystem.html</anchorfile>
      <anchor>a82bc214039b66397f28702da39cfdeec</anchor>
      <arglist>(const Vector &amp;g, const MatrixOp &amp;G, value_type etaL, const Vector *dL, const Vector *dU, const MatrixOp *F, BLAS_Cpp::Transp trans_F, const Vector *f, const Vector *d, const Vector *nu, size_type *n_R, i_x_free_t *i_x_free, i_x_fixed_t *i_x_fixed, bnd_fixed_t *bnd_fixed, j_f_decomp_t *j_f_decomp, DVector *b_X, Ko_ptr_t *Ko, DVector *fo) const =0</arglist>
    </member>
    <member kind="typedef">
      <type>std::vector&lt; size_type &gt;</type>
      <name>i_x_free_t</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxedQPSchur_1_1InitKKTSystem.html</anchorfile>
      <anchor>a5de1f93875d573da8e88ea953096ac53</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::vector&lt; size_type &gt;</type>
      <name>i_x_fixed_t</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxedQPSchur_1_1InitKKTSystem.html</anchorfile>
      <anchor>a0211d12edde7b739504bc5e725c0db5f</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::vector&lt; EBounds &gt;</type>
      <name>bnd_fixed_t</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxedQPSchur_1_1InitKKTSystem.html</anchorfile>
      <anchor>abfb8f44c2944af4c7a289f01a9d2bcd1</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::vector&lt; size_type &gt;</type>
      <name>j_f_decomp_t</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxedQPSchur_1_1InitKKTSystem.html</anchorfile>
      <anchor>af477000cad3adbb2dd82803ce5906baa</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Teuchos::RCP&lt; const MatrixSymOpNonsing &gt;</type>
      <name>Ko_ptr_t</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxedQPSchur_1_1InitKKTSystem.html</anchorfile>
      <anchor>ad60651e7c7c5e7d4d492290e1ed1a4cc</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ConstrainedOptPack::QPSchurInitKKTSystemHessianFull</name>
    <filename>classConstrainedOptPack_1_1QPSchurInitKKTSystemHessianFull.html</filename>
    <base>ConstrainedOptPack::QPSolverRelaxedQPSchur::InitKKTSystem</base>
    <member kind="function">
      <type>void</type>
      <name>initialize_kkt_system</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchurInitKKTSystemHessianFull.html</anchorfile>
      <anchor>a22bb8eed4f93a432c7319b0984319519</anchor>
      <arglist>(const Vector &amp;g, const MatrixOp &amp;G, value_type etaL, const Vector *dL, const Vector *dU, const MatrixOp *F, BLAS_Cpp::Transp trans_F, const Vector *f, const Vector *d, const Vector *nu, size_type *n_R, i_x_free_t *i_x_free, i_x_fixed_t *i_x_fixed, bnd_fixed_t *bnd_fixed, j_f_decomp_t *j_f_decomp, DVector *b_X, Ko_ptr_t *Ko, DVector *fo) const </arglist>
    </member>
    <member kind="typedef">
      <type>std::vector&lt; size_type &gt;</type>
      <name>i_x_free_t</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxedQPSchur_1_1InitKKTSystem.html</anchorfile>
      <anchor>a5de1f93875d573da8e88ea953096ac53</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::vector&lt; size_type &gt;</type>
      <name>i_x_fixed_t</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxedQPSchur_1_1InitKKTSystem.html</anchorfile>
      <anchor>a0211d12edde7b739504bc5e725c0db5f</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::vector&lt; EBounds &gt;</type>
      <name>bnd_fixed_t</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxedQPSchur_1_1InitKKTSystem.html</anchorfile>
      <anchor>abfb8f44c2944af4c7a289f01a9d2bcd1</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::vector&lt; size_type &gt;</type>
      <name>j_f_decomp_t</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxedQPSchur_1_1InitKKTSystem.html</anchorfile>
      <anchor>af477000cad3adbb2dd82803ce5906baa</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Teuchos::RCP&lt; const MatrixSymOpNonsing &gt;</type>
      <name>Ko_ptr_t</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxedQPSchur_1_1InitKKTSystem.html</anchorfile>
      <anchor>ad60651e7c7c5e7d4d492290e1ed1a4cc</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~InitKKTSystem</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxedQPSchur_1_1InitKKTSystem.html</anchorfile>
      <anchor>afe88b3e54b7c80d76897bcd29904ae23</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ConstrainedOptPack::QPSchurInitKKTSystemHessianRelaxed</name>
    <filename>classConstrainedOptPack_1_1QPSchurInitKKTSystemHessianRelaxed.html</filename>
    <base>ConstrainedOptPack::QPSchurInitKKTSystemHessianFull</base>
    <member kind="function">
      <type>void</type>
      <name>initialize_kkt_system</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchurInitKKTSystemHessianRelaxed.html</anchorfile>
      <anchor>a4c02b744c6bf96b91f246600bab1c6f0</anchor>
      <arglist>(const DVectorSlice &amp;g, const MatrixOp &amp;G, value_type etaL, const SpVectorSlice &amp;dL, const SpVectorSlice &amp;dU, const MatrixOp *F, BLAS_Cpp::Transp trans_F, const DVectorSlice *f, const DVectorSlice &amp;d, const SpVectorSlice &amp;nu, size_type *n_R, i_x_free_t *i_x_free, i_x_fixed_t *i_x_fixed, bnd_fixed_t *bnd_fixed, j_f_decomp_t *j_f_decomp, DVector *b_X, Ko_ptr_t *Ko, DVector *fo) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initialize_kkt_system</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchurInitKKTSystemHessianFull.html</anchorfile>
      <anchor>a22bb8eed4f93a432c7319b0984319519</anchor>
      <arglist>(const Vector &amp;g, const MatrixOp &amp;G, value_type etaL, const Vector *dL, const Vector *dU, const MatrixOp *F, BLAS_Cpp::Transp trans_F, const Vector *f, const Vector *d, const Vector *nu, size_type *n_R, i_x_free_t *i_x_free, i_x_fixed_t *i_x_fixed, bnd_fixed_t *bnd_fixed, j_f_decomp_t *j_f_decomp, DVector *b_X, Ko_ptr_t *Ko, DVector *fo) const </arglist>
    </member>
    <member kind="typedef">
      <type>std::vector&lt; size_type &gt;</type>
      <name>i_x_free_t</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxedQPSchur_1_1InitKKTSystem.html</anchorfile>
      <anchor>a5de1f93875d573da8e88ea953096ac53</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::vector&lt; size_type &gt;</type>
      <name>i_x_fixed_t</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxedQPSchur_1_1InitKKTSystem.html</anchorfile>
      <anchor>a0211d12edde7b739504bc5e725c0db5f</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::vector&lt; EBounds &gt;</type>
      <name>bnd_fixed_t</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxedQPSchur_1_1InitKKTSystem.html</anchorfile>
      <anchor>abfb8f44c2944af4c7a289f01a9d2bcd1</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::vector&lt; size_type &gt;</type>
      <name>j_f_decomp_t</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxedQPSchur_1_1InitKKTSystem.html</anchorfile>
      <anchor>af477000cad3adbb2dd82803ce5906baa</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Teuchos::RCP&lt; const MatrixSymOpNonsing &gt;</type>
      <name>Ko_ptr_t</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxedQPSchur_1_1InitKKTSystem.html</anchorfile>
      <anchor>ad60651e7c7c5e7d4d492290e1ed1a4cc</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ConstrainedOptPack::QPSchurInitKKTSystemHessianSuperBasic</name>
    <filename>classConstrainedOptPack_1_1QPSchurInitKKTSystemHessianSuperBasic.html</filename>
    <base>ConstrainedOptPack::QPSolverRelaxedQPSchur::InitKKTSystem</base>
    <member kind="function">
      <type>void</type>
      <name>initialize_kkt_system</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchurInitKKTSystemHessianSuperBasic.html</anchorfile>
      <anchor>acdbf565e5cd86a186e16f35401e3600f</anchor>
      <arglist>(const DVectorSlice &amp;g, const MatrixOp &amp;G, value_type etaL, const SpVectorSlice &amp;dL, const SpVectorSlice &amp;dU, const MatrixOp *F, BLAS_Cpp::Transp trans_F, const DVectorSlice *f, const DVectorSlice &amp;d, const SpVectorSlice &amp;nu, size_type *n_R, i_x_free_t *i_x_free, i_x_fixed_t *i_x_fixed, bnd_fixed_t *bnd_fixed, j_f_decomp_t *j_f_decomp, DVector *b_X, Ko_ptr_t *Ko, DVector *fo) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~InitKKTSystem</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxedQPSchur_1_1InitKKTSystem.html</anchorfile>
      <anchor>afe88b3e54b7c80d76897bcd29904ae23</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>initialize_kkt_system</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxedQPSchur_1_1InitKKTSystem.html</anchorfile>
      <anchor>a82bc214039b66397f28702da39cfdeec</anchor>
      <arglist>(const Vector &amp;g, const MatrixOp &amp;G, value_type etaL, const Vector *dL, const Vector *dU, const MatrixOp *F, BLAS_Cpp::Transp trans_F, const Vector *f, const Vector *d, const Vector *nu, size_type *n_R, i_x_free_t *i_x_free, i_x_fixed_t *i_x_fixed, bnd_fixed_t *bnd_fixed, j_f_decomp_t *j_f_decomp, DVector *b_X, Ko_ptr_t *Ko, DVector *fo) const =0</arglist>
    </member>
    <member kind="typedef">
      <type>std::vector&lt; size_type &gt;</type>
      <name>i_x_free_t</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxedQPSchur_1_1InitKKTSystem.html</anchorfile>
      <anchor>a5de1f93875d573da8e88ea953096ac53</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::vector&lt; size_type &gt;</type>
      <name>i_x_fixed_t</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxedQPSchur_1_1InitKKTSystem.html</anchorfile>
      <anchor>a0211d12edde7b739504bc5e725c0db5f</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::vector&lt; EBounds &gt;</type>
      <name>bnd_fixed_t</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxedQPSchur_1_1InitKKTSystem.html</anchorfile>
      <anchor>abfb8f44c2944af4c7a289f01a9d2bcd1</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::vector&lt; size_type &gt;</type>
      <name>j_f_decomp_t</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxedQPSchur_1_1InitKKTSystem.html</anchorfile>
      <anchor>af477000cad3adbb2dd82803ce5906baa</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Teuchos::RCP&lt; const MatrixSymOpNonsing &gt;</type>
      <name>Ko_ptr_t</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxedQPSchur_1_1InitKKTSystem.html</anchorfile>
      <anchor>ad60651e7c7c5e7d4d492290e1ed1a4cc</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ConstrainedOptPack::QPSolverRelaxed</name>
    <filename>classConstrainedOptPack_1_1QPSolverRelaxed.html</filename>
    <class kind="class">ConstrainedOptPack::QPSolverRelaxed::Infeasible</class>
    <class kind="class">ConstrainedOptPack::QPSolverRelaxed::InvalidInput</class>
    <class kind="class">ConstrainedOptPack::QPSolverRelaxed::TestFailed</class>
    <class kind="class">ConstrainedOptPack::QPSolverRelaxed::Unbounded</class>
    <member kind="enumeration">
      <name>EOutputLevel</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxed.html</anchorfile>
      <anchor>aa265cc3580531afcb84f0d4c0a3454dd</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>ERunTests</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxed.html</anchorfile>
      <anchor>ae488af6a9c9ff7a4b2c1d0cbcb3e2cdc</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxed.html</anchorfile>
      <anchor>aaea3eba54dd2f942a31e82c2ed5919cb</anchor>
      <arglist>(value_type, infinite_bound)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>QPSolverRelaxed</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxed.html</anchorfile>
      <anchor>a6e8f4a6d3d8dc95f26c200c458df0ff4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~QPSolverRelaxed</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxed.html</anchorfile>
      <anchor>a063976969662f8007234a1aaa858882f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual QPSolverStats::ESolutionType</type>
      <name>solve_qp</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxed.html</anchorfile>
      <anchor>a08ce2f5920a0c1ea4a48017cc8ee506a</anchor>
      <arglist>(std::ostream *out, EOutputLevel olevel, ERunTests test_what, const Vector &amp;g, const MatrixSymOp &amp;G, value_type etaL, const Vector &amp;dL, const Vector &amp;dU, const MatrixOp &amp;E, BLAS_Cpp::Transp trans_E, const Vector &amp;b, const Vector &amp;eL, const Vector &amp;eU, const MatrixOp &amp;F, BLAS_Cpp::Transp trans_F, const Vector &amp;f, value_type *obj_d, value_type *eta, VectorMutable *d, VectorMutable *nu, VectorMutable *mu, VectorMutable *Ed, VectorMutable *lambda, VectorMutable *Fd)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual QPSolverStats::ESolutionType</type>
      <name>solve_qp</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxed.html</anchorfile>
      <anchor>ae2145699eda93c4bff7112379aabf9ce</anchor>
      <arglist>(std::ostream *out, EOutputLevel olevel, ERunTests test_what, const Vector &amp;g, const MatrixSymOp &amp;G, value_type etaL, const Vector &amp;dL, const Vector &amp;dU, const MatrixOp &amp;E, BLAS_Cpp::Transp trans_E, const Vector &amp;b, const Vector &amp;eL, const Vector &amp;eU, value_type *obj_d, value_type *eta, VectorMutable *d, VectorMutable *nu, VectorMutable *mu, VectorMutable *Ed)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual QPSolverStats::ESolutionType</type>
      <name>solve_qp</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxed.html</anchorfile>
      <anchor>a76430e8a919ed1598b598ac661830f70</anchor>
      <arglist>(std::ostream *out, EOutputLevel olevel, ERunTests test_what, const Vector &amp;g, const MatrixSymOp &amp;G, value_type etaL, const Vector &amp;dL, const Vector &amp;dU, const MatrixOp &amp;F, BLAS_Cpp::Transp trans_F, const Vector &amp;f, value_type *obj_d, value_type *eta, VectorMutable *d, VectorMutable *nu, VectorMutable *lambda, VectorMutable *Fd)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual QPSolverStats::ESolutionType</type>
      <name>solve_qp</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxed.html</anchorfile>
      <anchor>ad825cdf563a01a81b5fcbcb6f5802f11</anchor>
      <arglist>(std::ostream *out, EOutputLevel olevel, ERunTests test_what, const Vector &amp;g, const MatrixSymOp &amp;G, const Vector &amp;dL, const Vector &amp;dU, value_type *obj_d, VectorMutable *d, VectorMutable *nu)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual QPSolverStats::ESolutionType</type>
      <name>solve_qp</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxed.html</anchorfile>
      <anchor>a60cb2d323a1beb29cc4c663ec1d509a3</anchor>
      <arglist>(std::ostream *out, EOutputLevel olevel, ERunTests test_what, const Vector &amp;g, const MatrixSymOp &amp;G, value_type etaL, const Vector *dL, const Vector *dU, const MatrixOp *E, BLAS_Cpp::Transp trans_E, const Vector *b, const Vector *eL, const Vector *eU, const MatrixOp *F, BLAS_Cpp::Transp trans_F, const Vector *f, value_type *obj_d, value_type *eta, VectorMutable *d, VectorMutable *nu, VectorMutable *mu, VectorMutable *Ed, VectorMutable *lambda, VectorMutable *Fd)</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual QPSolverStats</type>
      <name>get_qp_stats</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxed.html</anchorfile>
      <anchor>a39a648c02cae605054e6f1236f61d724</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>release_memory</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxed.html</anchorfile>
      <anchor>aea1a90a475debb12fdeda5cfde49db76</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>validate_input</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxed.html</anchorfile>
      <anchor>a9e35580a0ed98ae12106faaaff30dd9d</anchor>
      <arglist>(const value_type infinite_bound, const Vector &amp;g, const MatrixSymOp &amp;G, value_type etaL, const Vector *dL, const Vector *dU, const MatrixOp *E, BLAS_Cpp::Transp trans_E, const Vector *b, const Vector *eL, const Vector *eU, const MatrixOp *F, BLAS_Cpp::Transp trans_F, const Vector *f, const value_type *obj_d, const value_type *eta, const Vector *d, const Vector *nu, const Vector *mu, const Vector *Ed, const Vector *lambda, const Vector *Fd)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>print_qp_input</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxed.html</anchorfile>
      <anchor>a18546584b754bab31e187d48066d232d</anchor>
      <arglist>(const value_type infinite_bound, std::ostream *out, EOutputLevel olevel, const Vector &amp;g, const MatrixSymOp &amp;G, value_type etaL, const Vector *dL, const Vector *dU, const MatrixOp *E, BLAS_Cpp::Transp trans_E, const Vector *b, const Vector *eL, const Vector *eU, const MatrixOp *F, BLAS_Cpp::Transp trans_F, const Vector *f, value_type *eta, VectorMutable *d, VectorMutable *nu, VectorMutable *mu, VectorMutable *lambda)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>print_qp_output</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxed.html</anchorfile>
      <anchor>ac55dc26232542593275d61b0b17114ee</anchor>
      <arglist>(const value_type infinite_bound, std::ostream *out, EOutputLevel olevel, const value_type *obj_d, const value_type *eta, const Vector *d, const Vector *nu, const Vector *mu, const Vector *Ed, const Vector *lambda, const Vector *Fd)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual QPSolverStats::ESolutionType</type>
      <name>imp_solve_qp</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxed.html</anchorfile>
      <anchor>abbe3d99a7e36dd0e6b438b755d04f1a8</anchor>
      <arglist>(std::ostream *out, EOutputLevel olevel, ERunTests test_what, const Vector &amp;g, const MatrixSymOp &amp;G, value_type etaL, const Vector *dL, const Vector *dU, const MatrixOp *E, BLAS_Cpp::Transp trans_E, const Vector *b, const Vector *eL, const Vector *eU, const MatrixOp *F, BLAS_Cpp::Transp trans_F, const Vector *f, value_type *obj_d, value_type *eta, VectorMutable *d, VectorMutable *nu, VectorMutable *mu, VectorMutable *Ed, VectorMutable *lambda, VectorMutable *Fd)=0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ConstrainedOptPack::QPSolverRelaxed::Infeasible</name>
    <filename>classConstrainedOptPack_1_1QPSolverRelaxed_1_1Infeasible.html</filename>
  </compound>
  <compound kind="class">
    <name>ConstrainedOptPack::QPSolverRelaxed::InvalidInput</name>
    <filename>classConstrainedOptPack_1_1QPSolverRelaxed_1_1InvalidInput.html</filename>
  </compound>
  <compound kind="class">
    <name>ConstrainedOptPack::QPSolverRelaxed::TestFailed</name>
    <filename>classConstrainedOptPack_1_1QPSolverRelaxed_1_1TestFailed.html</filename>
  </compound>
  <compound kind="class">
    <name>ConstrainedOptPack::QPSolverRelaxed::Unbounded</name>
    <filename>classConstrainedOptPack_1_1QPSolverRelaxed_1_1Unbounded.html</filename>
  </compound>
  <compound kind="class">
    <name>ConstrainedOptPack::QPSolverRelaxedQPKWIK</name>
    <filename>classConstrainedOptPack_1_1QPSolverRelaxedQPKWIK.html</filename>
    <base>ConstrainedOptPack::QPSolverRelaxed</base>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxedQPKWIK.html</anchorfile>
      <anchor>a0889d84c0571f7e5b05a81a7724005ea</anchor>
      <arglist>(value_type, max_qp_iter_frac)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxedQPKWIK.html</anchorfile>
      <anchor>a48285f25d6cd58cc335929c5aa6ff439</anchor>
      <arglist>(value_type, infinite_bound)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>QPSolverRelaxedQPKWIK</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxedQPKWIK.html</anchorfile>
      <anchor>a989b194bd2238374f1c027ded2e61ddd</anchor>
      <arglist>(value_type max_qp_iter_frac=10.0, value_type infinite_bound=1e+20)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~QPSolverRelaxedQPKWIK</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxedQPKWIK.html</anchorfile>
      <anchor>a456c5b5340b93af80ddd6d10628ec427</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>QPSolverStats</type>
      <name>get_qp_stats</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxedQPKWIK.html</anchorfile>
      <anchor>a91c519b60d1741b3c8632c8f5532f0bb</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>release_memory</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxedQPKWIK.html</anchorfile>
      <anchor>a5c5632b6ec865752ef11eac58182e441</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>QPSolverStats::ESolutionType</type>
      <name>imp_solve_qp</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxedQPKWIK.html</anchorfile>
      <anchor>a34e9b6a8ff4486e6a4f647312a450477</anchor>
      <arglist>(std::ostream *out, EOutputLevel olevel, ERunTests test_what, const Vector &amp;g, const MatrixSymOp &amp;G, value_type etaL, const Vector *dL, const Vector *dU, const MatrixOp *E, BLAS_Cpp::Transp trans_E, const Vector *b, const Vector *eL, const Vector *eU, const MatrixOp *F, BLAS_Cpp::Transp trans_F, const Vector *f, value_type *obj_d, value_type *eta, VectorMutable *d, VectorMutable *nu, VectorMutable *mu, VectorMutable *Ed, VectorMutable *lambda, VectorMutable *Fd)</arglist>
    </member>
    <member kind="enumeration">
      <name>EOutputLevel</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxed.html</anchorfile>
      <anchor>aa265cc3580531afcb84f0d4c0a3454dd</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>ERunTests</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxed.html</anchorfile>
      <anchor>ae488af6a9c9ff7a4b2c1d0cbcb3e2cdc</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxed.html</anchorfile>
      <anchor>aaea3eba54dd2f942a31e82c2ed5919cb</anchor>
      <arglist>(value_type, infinite_bound)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>QPSolverRelaxed</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxed.html</anchorfile>
      <anchor>a6e8f4a6d3d8dc95f26c200c458df0ff4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~QPSolverRelaxed</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxed.html</anchorfile>
      <anchor>a063976969662f8007234a1aaa858882f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual QPSolverStats::ESolutionType</type>
      <name>solve_qp</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxed.html</anchorfile>
      <anchor>a08ce2f5920a0c1ea4a48017cc8ee506a</anchor>
      <arglist>(std::ostream *out, EOutputLevel olevel, ERunTests test_what, const Vector &amp;g, const MatrixSymOp &amp;G, value_type etaL, const Vector &amp;dL, const Vector &amp;dU, const MatrixOp &amp;E, BLAS_Cpp::Transp trans_E, const Vector &amp;b, const Vector &amp;eL, const Vector &amp;eU, const MatrixOp &amp;F, BLAS_Cpp::Transp trans_F, const Vector &amp;f, value_type *obj_d, value_type *eta, VectorMutable *d, VectorMutable *nu, VectorMutable *mu, VectorMutable *Ed, VectorMutable *lambda, VectorMutable *Fd)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual QPSolverStats::ESolutionType</type>
      <name>solve_qp</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxed.html</anchorfile>
      <anchor>ae2145699eda93c4bff7112379aabf9ce</anchor>
      <arglist>(std::ostream *out, EOutputLevel olevel, ERunTests test_what, const Vector &amp;g, const MatrixSymOp &amp;G, value_type etaL, const Vector &amp;dL, const Vector &amp;dU, const MatrixOp &amp;E, BLAS_Cpp::Transp trans_E, const Vector &amp;b, const Vector &amp;eL, const Vector &amp;eU, value_type *obj_d, value_type *eta, VectorMutable *d, VectorMutable *nu, VectorMutable *mu, VectorMutable *Ed)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual QPSolverStats::ESolutionType</type>
      <name>solve_qp</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxed.html</anchorfile>
      <anchor>a76430e8a919ed1598b598ac661830f70</anchor>
      <arglist>(std::ostream *out, EOutputLevel olevel, ERunTests test_what, const Vector &amp;g, const MatrixSymOp &amp;G, value_type etaL, const Vector &amp;dL, const Vector &amp;dU, const MatrixOp &amp;F, BLAS_Cpp::Transp trans_F, const Vector &amp;f, value_type *obj_d, value_type *eta, VectorMutable *d, VectorMutable *nu, VectorMutable *lambda, VectorMutable *Fd)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual QPSolverStats::ESolutionType</type>
      <name>solve_qp</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxed.html</anchorfile>
      <anchor>ad825cdf563a01a81b5fcbcb6f5802f11</anchor>
      <arglist>(std::ostream *out, EOutputLevel olevel, ERunTests test_what, const Vector &amp;g, const MatrixSymOp &amp;G, const Vector &amp;dL, const Vector &amp;dU, value_type *obj_d, VectorMutable *d, VectorMutable *nu)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual QPSolverStats::ESolutionType</type>
      <name>solve_qp</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxed.html</anchorfile>
      <anchor>a60cb2d323a1beb29cc4c663ec1d509a3</anchor>
      <arglist>(std::ostream *out, EOutputLevel olevel, ERunTests test_what, const Vector &amp;g, const MatrixSymOp &amp;G, value_type etaL, const Vector *dL, const Vector *dU, const MatrixOp *E, BLAS_Cpp::Transp trans_E, const Vector *b, const Vector *eL, const Vector *eU, const MatrixOp *F, BLAS_Cpp::Transp trans_F, const Vector *f, value_type *obj_d, value_type *eta, VectorMutable *d, VectorMutable *nu, VectorMutable *mu, VectorMutable *Ed, VectorMutable *lambda, VectorMutable *Fd)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>validate_input</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxed.html</anchorfile>
      <anchor>a9e35580a0ed98ae12106faaaff30dd9d</anchor>
      <arglist>(const value_type infinite_bound, const Vector &amp;g, const MatrixSymOp &amp;G, value_type etaL, const Vector *dL, const Vector *dU, const MatrixOp *E, BLAS_Cpp::Transp trans_E, const Vector *b, const Vector *eL, const Vector *eU, const MatrixOp *F, BLAS_Cpp::Transp trans_F, const Vector *f, const value_type *obj_d, const value_type *eta, const Vector *d, const Vector *nu, const Vector *mu, const Vector *Ed, const Vector *lambda, const Vector *Fd)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>print_qp_input</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxed.html</anchorfile>
      <anchor>a18546584b754bab31e187d48066d232d</anchor>
      <arglist>(const value_type infinite_bound, std::ostream *out, EOutputLevel olevel, const Vector &amp;g, const MatrixSymOp &amp;G, value_type etaL, const Vector *dL, const Vector *dU, const MatrixOp *E, BLAS_Cpp::Transp trans_E, const Vector *b, const Vector *eL, const Vector *eU, const MatrixOp *F, BLAS_Cpp::Transp trans_F, const Vector *f, value_type *eta, VectorMutable *d, VectorMutable *nu, VectorMutable *mu, VectorMutable *lambda)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>print_qp_output</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxed.html</anchorfile>
      <anchor>ac55dc26232542593275d61b0b17114ee</anchor>
      <arglist>(const value_type infinite_bound, std::ostream *out, EOutputLevel olevel, const value_type *obj_d, const value_type *eta, const Vector *d, const Vector *nu, const Vector *mu, const Vector *Ed, const Vector *lambda, const Vector *Fd)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ConstrainedOptPack::QPSolverRelaxedQPOPTSOL</name>
    <filename>classConstrainedOptPack_1_1QPSolverRelaxedQPOPTSOL.html</filename>
    <base>ConstrainedOptPack::QPSolverRelaxed</base>
    <member kind="enumeration">
      <name>EInform</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxedQPOPTSOL.html</anchorfile>
      <anchor>a3dc638c36e1e5b713072c75bc04b942b</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>EOutputLevel</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxed.html</anchorfile>
      <anchor>aa265cc3580531afcb84f0d4c0a3454dd</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>ERunTests</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxed.html</anchorfile>
      <anchor>ae488af6a9c9ff7a4b2c1d0cbcb3e2cdc</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>QPSolverRelaxedQPOPTSOL</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxedQPOPTSOL.html</anchorfile>
      <anchor>a3754f6963cd04a517c0d74fbb09ccffb</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~QPSolverRelaxedQPOPTSOL</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxedQPOPTSOL.html</anchorfile>
      <anchor>ae909f8a819bf55e04b5b0f7f85bca6df</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const MatrixOp *</type>
      <name>G</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxedQPOPTSOL.html</anchorfile>
      <anchor>ae428ec23bffe9f166d245877e7d500ce</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual value_type</type>
      <name>use_as_bigM</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxedQPOPTSOL.html</anchorfile>
      <anchor>a628799847290ef1d3095b9294ad2d2e7</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>QPSolverStats</type>
      <name>get_qp_stats</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxedQPOPTSOL.html</anchorfile>
      <anchor>a7e49eb883190a2f5c40cf522743cd184</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>release_memory</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxedQPOPTSOL.html</anchorfile>
      <anchor>a98e2881ec84c79abd68f5760e470ad02</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxed.html</anchorfile>
      <anchor>aaea3eba54dd2f942a31e82c2ed5919cb</anchor>
      <arglist>(value_type, infinite_bound)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>QPSolverRelaxed</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxed.html</anchorfile>
      <anchor>a6e8f4a6d3d8dc95f26c200c458df0ff4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~QPSolverRelaxed</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxed.html</anchorfile>
      <anchor>a063976969662f8007234a1aaa858882f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual QPSolverStats::ESolutionType</type>
      <name>solve_qp</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxed.html</anchorfile>
      <anchor>a08ce2f5920a0c1ea4a48017cc8ee506a</anchor>
      <arglist>(std::ostream *out, EOutputLevel olevel, ERunTests test_what, const Vector &amp;g, const MatrixSymOp &amp;G, value_type etaL, const Vector &amp;dL, const Vector &amp;dU, const MatrixOp &amp;E, BLAS_Cpp::Transp trans_E, const Vector &amp;b, const Vector &amp;eL, const Vector &amp;eU, const MatrixOp &amp;F, BLAS_Cpp::Transp trans_F, const Vector &amp;f, value_type *obj_d, value_type *eta, VectorMutable *d, VectorMutable *nu, VectorMutable *mu, VectorMutable *Ed, VectorMutable *lambda, VectorMutable *Fd)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual QPSolverStats::ESolutionType</type>
      <name>solve_qp</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxed.html</anchorfile>
      <anchor>ae2145699eda93c4bff7112379aabf9ce</anchor>
      <arglist>(std::ostream *out, EOutputLevel olevel, ERunTests test_what, const Vector &amp;g, const MatrixSymOp &amp;G, value_type etaL, const Vector &amp;dL, const Vector &amp;dU, const MatrixOp &amp;E, BLAS_Cpp::Transp trans_E, const Vector &amp;b, const Vector &amp;eL, const Vector &amp;eU, value_type *obj_d, value_type *eta, VectorMutable *d, VectorMutable *nu, VectorMutable *mu, VectorMutable *Ed)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual QPSolverStats::ESolutionType</type>
      <name>solve_qp</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxed.html</anchorfile>
      <anchor>a76430e8a919ed1598b598ac661830f70</anchor>
      <arglist>(std::ostream *out, EOutputLevel olevel, ERunTests test_what, const Vector &amp;g, const MatrixSymOp &amp;G, value_type etaL, const Vector &amp;dL, const Vector &amp;dU, const MatrixOp &amp;F, BLAS_Cpp::Transp trans_F, const Vector &amp;f, value_type *obj_d, value_type *eta, VectorMutable *d, VectorMutable *nu, VectorMutable *lambda, VectorMutable *Fd)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual QPSolverStats::ESolutionType</type>
      <name>solve_qp</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxed.html</anchorfile>
      <anchor>ad825cdf563a01a81b5fcbcb6f5802f11</anchor>
      <arglist>(std::ostream *out, EOutputLevel olevel, ERunTests test_what, const Vector &amp;g, const MatrixSymOp &amp;G, const Vector &amp;dL, const Vector &amp;dU, value_type *obj_d, VectorMutable *d, VectorMutable *nu)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual QPSolverStats::ESolutionType</type>
      <name>solve_qp</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxed.html</anchorfile>
      <anchor>a60cb2d323a1beb29cc4c663ec1d509a3</anchor>
      <arglist>(std::ostream *out, EOutputLevel olevel, ERunTests test_what, const Vector &amp;g, const MatrixSymOp &amp;G, value_type etaL, const Vector *dL, const Vector *dU, const MatrixOp *E, BLAS_Cpp::Transp trans_E, const Vector *b, const Vector *eL, const Vector *eU, const MatrixOp *F, BLAS_Cpp::Transp trans_F, const Vector *f, value_type *obj_d, value_type *eta, VectorMutable *d, VectorMutable *nu, VectorMutable *mu, VectorMutable *Ed, VectorMutable *lambda, VectorMutable *Fd)</arglist>
    </member>
    <member kind="typedef" protection="protected">
      <type>std::vector&lt; f_int &gt;</type>
      <name>ISTATE_t</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxedQPOPTSOL.html</anchorfile>
      <anchor>ad2a7c8b3253358dceab5f78fae918b90</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef" protection="protected">
      <type>std::vector&lt; f_int &gt;</type>
      <name>IWORK_t</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxedQPOPTSOL.html</anchorfile>
      <anchor>a0c416ac900b6cb2c6ae41a12c18d207f</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef" protection="protected">
      <type>std::vector&lt; f_dbl_prec &gt;</type>
      <name>WORK_t</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxedQPOPTSOL.html</anchorfile>
      <anchor>a2b647bdb55b5c77cab72ba6239efa98e</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" protection="protected">
      <type>QPSolverStats::ESolutionType</type>
      <name>imp_solve_qp</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxedQPOPTSOL.html</anchorfile>
      <anchor>a2e468be8ad26d046ee13c8bf8bf44600</anchor>
      <arglist>(std::ostream *out, EOutputLevel olevel, ERunTests test_what, const Vector &amp;g, const MatrixSymOp &amp;G, value_type etaL, const Vector *dL, const Vector *dU, const MatrixOp *E, BLAS_Cpp::Transp trans_E, const Vector *b, const Vector *eL, const Vector *eU, const MatrixOp *F, BLAS_Cpp::Transp trans_F, const Vector *f, value_type *obj_d, value_type *eta, VectorMutable *d, VectorMutable *nu, VectorMutable *mu, VectorMutable *Ed, VectorMutable *lambda, VectorMutable *Fd)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual f_int</type>
      <name>liwork</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxedQPOPTSOL.html</anchorfile>
      <anchor>ac6e8306d0567b9a9bbb33ca93073719e</anchor>
      <arglist>(f_int N, f_int NCLIN) const =0</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual f_int</type>
      <name>lrwork</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxedQPOPTSOL.html</anchorfile>
      <anchor>abdedb2c1b2b3d2fcd6693053260e97ee</anchor>
      <arglist>(f_int N, f_int NCLIN) const =0</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual EInform</type>
      <name>call_qp_solver</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxedQPOPTSOL.html</anchorfile>
      <anchor>a45216cd59d988708c5f0733a0ff27253</anchor>
      <arglist>(bool warm_start)=0</arglist>
    </member>
    <member kind="typedef">
      <type>FortranTypes::f_int</type>
      <name>f_int</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxedQPOPTSOL.html</anchorfile>
      <anchor>a6605c51b3773d82fb82b5af8163fe08f</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>FortranTypes::f_dbl_prec</type>
      <name>f_dbl_prec</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxedQPOPTSOL.html</anchorfile>
      <anchor>ac9b78ac40526a3861e6da4f0a108476c</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>FortranTypes::f_logical</type>
      <name>f_logical</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxedQPOPTSOL.html</anchorfile>
      <anchor>a0a1cc10813b19cab845698c3e0e6c618</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>f_int</type>
      <name>N_</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxedQPOPTSOL.html</anchorfile>
      <anchor>a8258a60cc0e557d03f2019cc910619d9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>f_int</type>
      <name>NCLIN_</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxedQPOPTSOL.html</anchorfile>
      <anchor>a417d1ad900553b385923246d0de15678</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>DMatrix</type>
      <name>A_</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxedQPOPTSOL.html</anchorfile>
      <anchor>a565ab7e8565a29ca0d60ac8aadc52771</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>DVector</type>
      <name>BL_</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxedQPOPTSOL.html</anchorfile>
      <anchor>ae6133f49e2d3f75453f560e843dc0ff3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>DVector</type>
      <name>BU_</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxedQPOPTSOL.html</anchorfile>
      <anchor>ad1ac9c4f73c46caccd9e153f195cdbe4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>DVector</type>
      <name>CVEC_</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxedQPOPTSOL.html</anchorfile>
      <anchor>a50e2109ca81e1a8a78353f1104412020</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>ISTATE_t</type>
      <name>ISTATE_</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxedQPOPTSOL.html</anchorfile>
      <anchor>a4e2037b6bc3ecc798e81f42fc3fda92c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>DVector</type>
      <name>X_</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxedQPOPTSOL.html</anchorfile>
      <anchor>a0cd6e90d33a1d74ef5c3bf4c12b7ec8d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>DVector</type>
      <name>AX_</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxedQPOPTSOL.html</anchorfile>
      <anchor>a039bcd9bb890234245aa26d770a4b76f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>DVector</type>
      <name>CLAMDA_</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxedQPOPTSOL.html</anchorfile>
      <anchor>a9cc7e1c295a28cd47d99ffa5f6ad9c28</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>f_int</type>
      <name>ITER_</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxedQPOPTSOL.html</anchorfile>
      <anchor>a6d2ac7bfd8a4ccd12002974e108d747c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>f_dbl_prec</type>
      <name>OBJ_</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxedQPOPTSOL.html</anchorfile>
      <anchor>a28e7e676ae1967422c82ca5e3e071363</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>f_int</type>
      <name>LIWORK_</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxedQPOPTSOL.html</anchorfile>
      <anchor>a3bc458fddc5085deda58f92304750ffb</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>IWORK_t</type>
      <name>IWORK_</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxedQPOPTSOL.html</anchorfile>
      <anchor>a65eeac5a6057de9d747f869ecc45e8b0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>f_int</type>
      <name>LWORK_</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxedQPOPTSOL.html</anchorfile>
      <anchor>a2efac8d46dff3b14baa953e8396a77a4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>WORK_t</type>
      <name>WORK_</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxedQPOPTSOL.html</anchorfile>
      <anchor>a55fcfdab1301f318c9a8adb65eb9255b</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>validate_input</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxed.html</anchorfile>
      <anchor>a9e35580a0ed98ae12106faaaff30dd9d</anchor>
      <arglist>(const value_type infinite_bound, const Vector &amp;g, const MatrixSymOp &amp;G, value_type etaL, const Vector *dL, const Vector *dU, const MatrixOp *E, BLAS_Cpp::Transp trans_E, const Vector *b, const Vector *eL, const Vector *eU, const MatrixOp *F, BLAS_Cpp::Transp trans_F, const Vector *f, const value_type *obj_d, const value_type *eta, const Vector *d, const Vector *nu, const Vector *mu, const Vector *Ed, const Vector *lambda, const Vector *Fd)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>print_qp_input</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxed.html</anchorfile>
      <anchor>a18546584b754bab31e187d48066d232d</anchor>
      <arglist>(const value_type infinite_bound, std::ostream *out, EOutputLevel olevel, const Vector &amp;g, const MatrixSymOp &amp;G, value_type etaL, const Vector *dL, const Vector *dU, const MatrixOp *E, BLAS_Cpp::Transp trans_E, const Vector *b, const Vector *eL, const Vector *eU, const MatrixOp *F, BLAS_Cpp::Transp trans_F, const Vector *f, value_type *eta, VectorMutable *d, VectorMutable *nu, VectorMutable *mu, VectorMutable *lambda)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>print_qp_output</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxed.html</anchorfile>
      <anchor>ac55dc26232542593275d61b0b17114ee</anchor>
      <arglist>(const value_type infinite_bound, std::ostream *out, EOutputLevel olevel, const value_type *obj_d, const value_type *eta, const Vector *d, const Vector *nu, const Vector *mu, const Vector *Ed, const Vector *lambda, const Vector *Fd)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ConstrainedOptPack::QPSolverRelaxedQPSchur</name>
    <filename>classConstrainedOptPack_1_1QPSolverRelaxedQPSchur.html</filename>
    <base>ConstrainedOptPack::QPSolverRelaxed</base>
    <class kind="class">ConstrainedOptPack::QPSolverRelaxedQPSchur::InitKKTSystem</class>
    <class kind="class">ConstrainedOptPack::QPSolverRelaxedQPSchur::ReinitKKTSystem</class>
    <member kind="enumeration">
      <name>ELocalOutputLevel</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxedQPSchur.html</anchorfile>
      <anchor>aef8bd2f7d72ec88d28b4ce1d5262ae87</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>EOutputLevel</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxed.html</anchorfile>
      <anchor>aa265cc3580531afcb84f0d4c0a3454dd</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>ERunTests</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxed.html</anchorfile>
      <anchor>ae488af6a9c9ff7a4b2c1d0cbcb3e2cdc</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_COMPOSITION_MEMBERS</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxedQPSchur.html</anchorfile>
      <anchor>a1f7869387810f49ad609ecaab44f3ee4</anchor>
      <arglist>(InitKKTSystem, init_kkt_sys)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_COMPOSITION_MEMBERS</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxedQPSchur.html</anchorfile>
      <anchor>a77fee43f3db75477b68ed9a569d73fdc</anchor>
      <arglist>(QPSchurPack::ConstraintsRelaxedStd, constraints)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxedQPSchur.html</anchorfile>
      <anchor>ab356b6ea7ef1f9b8a2f5d8f7909fe83b</anchor>
      <arglist>(value_type, max_qp_iter_frac)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxedQPSchur.html</anchorfile>
      <anchor>ad565de7ad63c3982358d782fe25fefec</anchor>
      <arglist>(value_type, max_real_runtime)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxedQPSchur.html</anchorfile>
      <anchor>abedccf7bad02e1fef587447c7a35e00b</anchor>
      <arglist>(QPSchurPack::ConstraintsRelaxedStd::EInequalityPickPolicy, inequality_pick_policy)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxedQPSchur.html</anchorfile>
      <anchor>afdb71f10f803877cd4df9832e515d387</anchor>
      <arglist>(ELocalOutputLevel, print_level)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxedQPSchur.html</anchorfile>
      <anchor>a316231e3fe5c2f759fd1c0ee3c8a50e1</anchor>
      <arglist>(value_type, bounds_tol)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxedQPSchur.html</anchorfile>
      <anchor>a1b05ddb5b0300b36a802964ba03f801d</anchor>
      <arglist>(value_type, inequality_tol)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxedQPSchur.html</anchorfile>
      <anchor>a6cb1aabb9e47a0366c4599fbf4e5e5ca</anchor>
      <arglist>(value_type, equality_tol)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxedQPSchur.html</anchorfile>
      <anchor>a74b6226f087f08fd06f3b236518eea8b</anchor>
      <arglist>(value_type, loose_feas_tol)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxedQPSchur.html</anchorfile>
      <anchor>aa9bac9d55ea998bb922e82932233e932</anchor>
      <arglist>(value_type, dual_infeas_tol)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxedQPSchur.html</anchorfile>
      <anchor>a9ec62f0cc853fd722bd7cf4f0119ad49</anchor>
      <arglist>(value_type, huge_primal_step)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxedQPSchur.html</anchorfile>
      <anchor>a22b36fa1c9d1084b734efbdd97051e8f</anchor>
      <arglist>(value_type, huge_dual_step)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxedQPSchur.html</anchorfile>
      <anchor>ada74bf6f6a8655a3e220030abe71aa12</anchor>
      <arglist>(value_type, bigM)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxedQPSchur.html</anchorfile>
      <anchor>a646ceada373455d4356958bbe8c7cb4f</anchor>
      <arglist>(value_type, warning_tol)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxedQPSchur.html</anchorfile>
      <anchor>a634dccd834d5a38e840be33dcad64c59</anchor>
      <arglist>(value_type, error_tol)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxedQPSchur.html</anchorfile>
      <anchor>a64f6ab0ae4dc9c3e36ca085ebdbff36e</anchor>
      <arglist>(size_type, iter_refine_min_iter)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxedQPSchur.html</anchorfile>
      <anchor>a3c5b373230d146d280c4e6bb5739eda6</anchor>
      <arglist>(size_type, iter_refine_max_iter)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxedQPSchur.html</anchorfile>
      <anchor>aaa19d3a7ae8a5dc46e7078165d5060f4</anchor>
      <arglist>(value_type, iter_refine_opt_tol)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxedQPSchur.html</anchorfile>
      <anchor>ae94ec44b625a24ead9fa4a22bd5c175f</anchor>
      <arglist>(value_type, iter_refine_feas_tol)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxedQPSchur.html</anchorfile>
      <anchor>a5939495b42c17b2105b7c74e852c5c43</anchor>
      <arglist>(bool, iter_refine_at_solution)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxedQPSchur.html</anchorfile>
      <anchor>a6bfa98fedac6d5dbc044df7427c978d8</anchor>
      <arglist>(value_type, pivot_warning_tol)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxedQPSchur.html</anchorfile>
      <anchor>a0714a6f61941abcc52e4c074f57cf663</anchor>
      <arglist>(value_type, pivot_singular_tol)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxedQPSchur.html</anchorfile>
      <anchor>aa7f03adb16fd7f4ac7062144e66602c8</anchor>
      <arglist>(value_type, pivot_wrong_inertia_tol)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxedQPSchur.html</anchorfile>
      <anchor>aa2130f0f6a0ce6074bf758166e13b51f</anchor>
      <arglist>(bool, add_equalities_initially)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>QPSolverRelaxedQPSchur</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxedQPSchur.html</anchorfile>
      <anchor>af38d1bf95b6af3ebf698068f349de914</anchor>
      <arglist>(const init_kkt_sys_ptr_t &amp;init_kkt_sys=Teuchos::null, const constraints_ptr_t &amp;constraints=Teuchos::rcp(new QPSchurPack::ConstraintsRelaxedStd), value_type max_qp_iter_frac=10.0, value_type max_real_runtime=1e+20, QPSchurPack::ConstraintsRelaxedStd::EInequalityPickPolicy inequality_pick_policy=QPSchurPack::ConstraintsRelaxedStd::ADD_BOUNDS_THEN_MOST_VIOLATED_INEQUALITY, ELocalOutputLevel print_level=USE_INPUT_ARG, value_type bounds_tol=-1.0, value_type inequality_tol=-1.0, value_type equality_tol=-1.0, value_type loose_feas_tol=-1.0, value_type dual_infeas_tol=-1.0, value_type huge_primal_step=-1.0, value_type huge_dual_step=-1.0, value_type bigM=1e+10, value_type warning_tol=1e-10, value_type error_tol=1e-5, size_type iter_refine_min_iter=1, size_type iter_refine_max_iter=3, value_type iter_refine_opt_tol=1e-12, value_type iter_refine_feas_tol=1e-12, bool iter_refine_at_solution=true, value_type pivot_warning_tol=1e-8, value_type pivot_singular_tol=1e-11, value_type pivot_wrong_inertia_tol=1e-11, bool add_equalities_initially=true)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~QPSolverRelaxedQPSchur</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxedQPSchur.html</anchorfile>
      <anchor>a15f79a4de7ea60d6b3072bf0505be572</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxed.html</anchorfile>
      <anchor>aaea3eba54dd2f942a31e82c2ed5919cb</anchor>
      <arglist>(value_type, infinite_bound)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>QPSolverRelaxed</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxed.html</anchorfile>
      <anchor>a6e8f4a6d3d8dc95f26c200c458df0ff4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~QPSolverRelaxed</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxed.html</anchorfile>
      <anchor>a063976969662f8007234a1aaa858882f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual QPSolverStats::ESolutionType</type>
      <name>solve_qp</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxed.html</anchorfile>
      <anchor>a08ce2f5920a0c1ea4a48017cc8ee506a</anchor>
      <arglist>(std::ostream *out, EOutputLevel olevel, ERunTests test_what, const Vector &amp;g, const MatrixSymOp &amp;G, value_type etaL, const Vector &amp;dL, const Vector &amp;dU, const MatrixOp &amp;E, BLAS_Cpp::Transp trans_E, const Vector &amp;b, const Vector &amp;eL, const Vector &amp;eU, const MatrixOp &amp;F, BLAS_Cpp::Transp trans_F, const Vector &amp;f, value_type *obj_d, value_type *eta, VectorMutable *d, VectorMutable *nu, VectorMutable *mu, VectorMutable *Ed, VectorMutable *lambda, VectorMutable *Fd)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual QPSolverStats::ESolutionType</type>
      <name>solve_qp</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxed.html</anchorfile>
      <anchor>ae2145699eda93c4bff7112379aabf9ce</anchor>
      <arglist>(std::ostream *out, EOutputLevel olevel, ERunTests test_what, const Vector &amp;g, const MatrixSymOp &amp;G, value_type etaL, const Vector &amp;dL, const Vector &amp;dU, const MatrixOp &amp;E, BLAS_Cpp::Transp trans_E, const Vector &amp;b, const Vector &amp;eL, const Vector &amp;eU, value_type *obj_d, value_type *eta, VectorMutable *d, VectorMutable *nu, VectorMutable *mu, VectorMutable *Ed)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual QPSolverStats::ESolutionType</type>
      <name>solve_qp</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxed.html</anchorfile>
      <anchor>a76430e8a919ed1598b598ac661830f70</anchor>
      <arglist>(std::ostream *out, EOutputLevel olevel, ERunTests test_what, const Vector &amp;g, const MatrixSymOp &amp;G, value_type etaL, const Vector &amp;dL, const Vector &amp;dU, const MatrixOp &amp;F, BLAS_Cpp::Transp trans_F, const Vector &amp;f, value_type *obj_d, value_type *eta, VectorMutable *d, VectorMutable *nu, VectorMutable *lambda, VectorMutable *Fd)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual QPSolverStats::ESolutionType</type>
      <name>solve_qp</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxed.html</anchorfile>
      <anchor>ad825cdf563a01a81b5fcbcb6f5802f11</anchor>
      <arglist>(std::ostream *out, EOutputLevel olevel, ERunTests test_what, const Vector &amp;g, const MatrixSymOp &amp;G, const Vector &amp;dL, const Vector &amp;dU, value_type *obj_d, VectorMutable *d, VectorMutable *nu)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual QPSolverStats::ESolutionType</type>
      <name>solve_qp</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxed.html</anchorfile>
      <anchor>a60cb2d323a1beb29cc4c663ec1d509a3</anchor>
      <arglist>(std::ostream *out, EOutputLevel olevel, ERunTests test_what, const Vector &amp;g, const MatrixSymOp &amp;G, value_type etaL, const Vector *dL, const Vector *dU, const MatrixOp *E, BLAS_Cpp::Transp trans_E, const Vector *b, const Vector *eL, const Vector *eU, const MatrixOp *F, BLAS_Cpp::Transp trans_F, const Vector *f, value_type *obj_d, value_type *eta, VectorMutable *d, VectorMutable *nu, VectorMutable *mu, VectorMutable *Ed, VectorMutable *lambda, VectorMutable *Fd)</arglist>
    </member>
    <member kind="function">
      <type>QPSolverStats</type>
      <name>get_qp_stats</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxedQPSchur.html</anchorfile>
      <anchor>a5498bfc180388287baa5325136a3619e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>release_memory</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxedQPSchur.html</anchorfile>
      <anchor>a1df842d54a006ed7977645bc89c2f1f3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>QPSolverStats::ESolutionType</type>
      <name>imp_solve_qp</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxedQPSchur.html</anchorfile>
      <anchor>a06f8aef91110a1543d647f6e38c1d157</anchor>
      <arglist>(std::ostream *out, EOutputLevel olevel, ERunTests test_what, const Vector &amp;g, const MatrixSymOp &amp;G, value_type etaL, const Vector *dL, const Vector *dU, const MatrixOp *E, BLAS_Cpp::Transp trans_E, const Vector *b, const Vector *eL, const Vector *eU, const MatrixOp *F, BLAS_Cpp::Transp trans_F, const Vector *f, value_type *obj_d, value_type *eta, VectorMutable *d, VectorMutable *nu, VectorMutable *mu, VectorMutable *Ed, VectorMutable *lambda, VectorMutable *Fd)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>validate_input</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxed.html</anchorfile>
      <anchor>a9e35580a0ed98ae12106faaaff30dd9d</anchor>
      <arglist>(const value_type infinite_bound, const Vector &amp;g, const MatrixSymOp &amp;G, value_type etaL, const Vector *dL, const Vector *dU, const MatrixOp *E, BLAS_Cpp::Transp trans_E, const Vector *b, const Vector *eL, const Vector *eU, const MatrixOp *F, BLAS_Cpp::Transp trans_F, const Vector *f, const value_type *obj_d, const value_type *eta, const Vector *d, const Vector *nu, const Vector *mu, const Vector *Ed, const Vector *lambda, const Vector *Fd)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>print_qp_input</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxed.html</anchorfile>
      <anchor>a18546584b754bab31e187d48066d232d</anchor>
      <arglist>(const value_type infinite_bound, std::ostream *out, EOutputLevel olevel, const Vector &amp;g, const MatrixSymOp &amp;G, value_type etaL, const Vector *dL, const Vector *dU, const MatrixOp *E, BLAS_Cpp::Transp trans_E, const Vector *b, const Vector *eL, const Vector *eU, const MatrixOp *F, BLAS_Cpp::Transp trans_F, const Vector *f, value_type *eta, VectorMutable *d, VectorMutable *nu, VectorMutable *mu, VectorMutable *lambda)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>print_qp_output</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxed.html</anchorfile>
      <anchor>ac55dc26232542593275d61b0b17114ee</anchor>
      <arglist>(const value_type infinite_bound, std::ostream *out, EOutputLevel olevel, const value_type *obj_d, const value_type *eta, const Vector *d, const Vector *nu, const Vector *mu, const Vector *Ed, const Vector *lambda, const Vector *Fd)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ConstrainedOptPack::QPSolverRelaxedQPSchur::InitKKTSystem</name>
    <filename>classConstrainedOptPack_1_1QPSolverRelaxedQPSchur_1_1InitKKTSystem.html</filename>
    <member kind="typedef">
      <type>std::vector&lt; size_type &gt;</type>
      <name>i_x_free_t</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxedQPSchur_1_1InitKKTSystem.html</anchorfile>
      <anchor>a5de1f93875d573da8e88ea953096ac53</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::vector&lt; size_type &gt;</type>
      <name>i_x_fixed_t</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxedQPSchur_1_1InitKKTSystem.html</anchorfile>
      <anchor>a0211d12edde7b739504bc5e725c0db5f</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::vector&lt; EBounds &gt;</type>
      <name>bnd_fixed_t</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxedQPSchur_1_1InitKKTSystem.html</anchorfile>
      <anchor>abfb8f44c2944af4c7a289f01a9d2bcd1</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::vector&lt; size_type &gt;</type>
      <name>j_f_decomp_t</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxedQPSchur_1_1InitKKTSystem.html</anchorfile>
      <anchor>af477000cad3adbb2dd82803ce5906baa</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Teuchos::RCP&lt; const MatrixSymOpNonsing &gt;</type>
      <name>Ko_ptr_t</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxedQPSchur_1_1InitKKTSystem.html</anchorfile>
      <anchor>ad60651e7c7c5e7d4d492290e1ed1a4cc</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~InitKKTSystem</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxedQPSchur_1_1InitKKTSystem.html</anchorfile>
      <anchor>afe88b3e54b7c80d76897bcd29904ae23</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>initialize_kkt_system</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxedQPSchur_1_1InitKKTSystem.html</anchorfile>
      <anchor>a82bc214039b66397f28702da39cfdeec</anchor>
      <arglist>(const Vector &amp;g, const MatrixOp &amp;G, value_type etaL, const Vector *dL, const Vector *dU, const MatrixOp *F, BLAS_Cpp::Transp trans_F, const Vector *f, const Vector *d, const Vector *nu, size_type *n_R, i_x_free_t *i_x_free, i_x_fixed_t *i_x_fixed, bnd_fixed_t *bnd_fixed, j_f_decomp_t *j_f_decomp, DVector *b_X, Ko_ptr_t *Ko, DVector *fo) const =0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ConstrainedOptPack::QPSolverRelaxedQPSchur::ReinitKKTSystem</name>
    <filename>classConstrainedOptPack_1_1QPSolverRelaxedQPSchur_1_1ReinitKKTSystem.html</filename>
    <base>ConstrainedOptPack::QPSolverRelaxedQPSchur::InitKKTSystem</base>
    <member kind="typedef">
      <type>std::vector&lt; size_type &gt;</type>
      <name>i_x_free_t</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxedQPSchur_1_1InitKKTSystem.html</anchorfile>
      <anchor>a5de1f93875d573da8e88ea953096ac53</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::vector&lt; size_type &gt;</type>
      <name>i_x_fixed_t</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxedQPSchur_1_1InitKKTSystem.html</anchorfile>
      <anchor>a0211d12edde7b739504bc5e725c0db5f</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::vector&lt; EBounds &gt;</type>
      <name>bnd_fixed_t</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxedQPSchur_1_1InitKKTSystem.html</anchorfile>
      <anchor>abfb8f44c2944af4c7a289f01a9d2bcd1</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::vector&lt; size_type &gt;</type>
      <name>j_f_decomp_t</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxedQPSchur_1_1InitKKTSystem.html</anchorfile>
      <anchor>af477000cad3adbb2dd82803ce5906baa</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Teuchos::RCP&lt; const MatrixSymOpNonsing &gt;</type>
      <name>Ko_ptr_t</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxedQPSchur_1_1InitKKTSystem.html</anchorfile>
      <anchor>ad60651e7c7c5e7d4d492290e1ed1a4cc</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~InitKKTSystem</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxedQPSchur_1_1InitKKTSystem.html</anchorfile>
      <anchor>afe88b3e54b7c80d76897bcd29904ae23</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>initialize_kkt_system</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxedQPSchur_1_1InitKKTSystem.html</anchorfile>
      <anchor>a82bc214039b66397f28702da39cfdeec</anchor>
      <arglist>(const Vector &amp;g, const MatrixOp &amp;G, value_type etaL, const Vector *dL, const Vector *dU, const MatrixOp *F, BLAS_Cpp::Transp trans_F, const Vector *f, const Vector *d, const Vector *nu, size_type *n_R, i_x_free_t *i_x_free, i_x_fixed_t *i_x_fixed, bnd_fixed_t *bnd_fixed, j_f_decomp_t *j_f_decomp, DVector *b_X, Ko_ptr_t *Ko, DVector *fo) const =0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ConstrainedOptPack::QPSolverRelaxedQPSchurSetOptions</name>
    <filename>classConstrainedOptPack_1_1QPSolverRelaxedQPSchurSetOptions.html</filename>
    <base>OptionsFromStreamPack::SetOptionsFromStreamNode</base>
    <base>OptionsFromStreamPack::SetOptionsToTargetBase</base>
    <member kind="function">
      <type></type>
      <name>QPSolverRelaxedQPSchurSetOptions</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxedQPSchurSetOptions.html</anchorfile>
      <anchor>a2d7e54093f00f3e4fa241bf727c900d0</anchor>
      <arglist>(QPSolverRelaxedQPSchur *target=0, const char opt_grp_name[]=&quot;QPSolverRelaxedQPSchur&quot;)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>setOption</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxedQPSchurSetOptions.html</anchorfile>
      <anchor>a029cb32aa11cbe67ceab3188c9fd3b36</anchor>
      <arglist>(int option_num, const std::string &amp;option_value)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ConstrainedOptPack::QPSolverRelaxedTester</name>
    <filename>classConstrainedOptPack_1_1QPSolverRelaxedTester.html</filename>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxedTester.html</anchorfile>
      <anchor>ac8a20e865eb4905330179b938fa8463a</anchor>
      <arglist>(value_type, opt_warning_tol)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxedTester.html</anchorfile>
      <anchor>a32f972c866c25236afa48dfcc1312e88</anchor>
      <arglist>(value_type, opt_error_tol)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxedTester.html</anchorfile>
      <anchor>a7686a9ffa55904236a947d574dd191c9</anchor>
      <arglist>(value_type, feas_warning_tol)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxedTester.html</anchorfile>
      <anchor>afd4ee7b47b6e3309782efcdbe36b4c9d</anchor>
      <arglist>(value_type, feas_error_tol)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxedTester.html</anchorfile>
      <anchor>add689d80d389c40431d390d61aa3dc6b</anchor>
      <arglist>(value_type, comp_warning_tol)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxedTester.html</anchorfile>
      <anchor>a513068374cc86ef81be1bb40be357faf</anchor>
      <arglist>(value_type, comp_error_tol)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>QPSolverRelaxedTester</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxedTester.html</anchorfile>
      <anchor>aa8df760e58c32b4f917b08b71b0b8360</anchor>
      <arglist>(value_type opt_warning_tol=1e-10, value_type opt_error_tol=1e-5, value_type feas_warning_tol=1e-10, value_type feas_error_tol=1e-5, value_type comp_warning_tol=1e-10, value_type comp_error_tol=1e-5)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~QPSolverRelaxedTester</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxedTester.html</anchorfile>
      <anchor>a9fa40c33ce7acae46ae70ed80f4b177a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>check_optimality_conditions</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxedTester.html</anchorfile>
      <anchor>a335ade8b03f9e5e16c8f65be7c7c323f</anchor>
      <arglist>(QPSolverStats::ESolutionType solution_type, const value_type infinite_bound, std::ostream *out, bool print_all_warnings, bool print_vectors, const Vector &amp;g, const MatrixSymOp &amp;G, value_type etaL, const Vector &amp;dL, const Vector &amp;dU, const MatrixOp &amp;E, BLAS_Cpp::Transp trans_E, const Vector &amp;b, const Vector &amp;eL, const Vector &amp;eU, const MatrixOp &amp;F, BLAS_Cpp::Transp trans_F, const Vector &amp;f, const value_type *obj_d, const value_type *eta, const Vector *d, const Vector *nu, const Vector *mu, const Vector *Ed, const Vector *lambda, const Vector *Fd)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>check_optimality_conditions</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxedTester.html</anchorfile>
      <anchor>afedf67cff086091d96250f19d7eb3839</anchor>
      <arglist>(QPSolverStats::ESolutionType solution_type, const value_type infinite_bound, std::ostream *out, bool print_all_warnings, bool print_vectors, const Vector &amp;g, const MatrixSymOp &amp;G, value_type etaL, const Vector &amp;dL, const Vector &amp;dU, const MatrixOp &amp;E, BLAS_Cpp::Transp trans_E, const Vector &amp;b, const Vector &amp;eL, const Vector &amp;eU, const value_type *obj_d, const value_type *eta, const Vector *d, const Vector *nu, const Vector *mu, const Vector *Ed)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>check_optimality_conditions</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxedTester.html</anchorfile>
      <anchor>a8a24a1ed7fac93a2b32f09e731451041</anchor>
      <arglist>(QPSolverStats::ESolutionType solution_type, const value_type infinite_bound, std::ostream *out, bool print_all_warnings, bool print_vectors, const Vector &amp;g, const MatrixSymOp &amp;G, value_type etaL, const Vector &amp;dL, const Vector &amp;dU, const MatrixOp &amp;F, BLAS_Cpp::Transp trans_F, const Vector &amp;f, const value_type *obj_d, const value_type *eta, const Vector *d, const Vector *nu, const Vector *lambda, const Vector *Fd)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>check_optimality_conditions</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxedTester.html</anchorfile>
      <anchor>a9293e45c55e3c68e54bdb4145062cbf2</anchor>
      <arglist>(QPSolverStats::ESolutionType solution_type, const value_type infinite_bound, std::ostream *out, bool print_all_warnings, bool print_vectors, const Vector &amp;g, const MatrixSymOp &amp;G, const Vector &amp;dL, const Vector &amp;dU, const value_type *obj_d, const Vector *d, const Vector *nu)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>check_optimality_conditions</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxedTester.html</anchorfile>
      <anchor>a211a59b2dcfbe2657b072c138e00583f</anchor>
      <arglist>(QPSolverStats::ESolutionType solution_type, const value_type infinite_bound, std::ostream *out, bool print_all_warnings, bool print_vectors, const Vector &amp;g, const MatrixSymOp &amp;G, value_type etaL, const Vector *dL, const Vector *dU, const MatrixOp *E, BLAS_Cpp::Transp trans_E, const Vector *b, const Vector *eL, const Vector *eU, const MatrixOp *F, BLAS_Cpp::Transp trans_F, const Vector *f, const value_type *obj_d, const value_type *eta, const Vector *d, const Vector *nu, const Vector *mu, const Vector *Ed, const Vector *lambda, const Vector *Fd)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual bool</type>
      <name>imp_check_optimality_conditions</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxedTester.html</anchorfile>
      <anchor>ade55130de7dcc944a26403f897d1b0d8</anchor>
      <arglist>(QPSolverStats::ESolutionType solution_type, const value_type infinite_bound, std::ostream *out, bool print_all_warnings, bool print_vectors, const Vector &amp;g, const MatrixSymOp &amp;G, value_type etaL, const Vector *dL, const Vector *dU, const MatrixOp *E, BLAS_Cpp::Transp trans_E, const Vector *b, const Vector *eL, const Vector *eU, const MatrixOp *F, BLAS_Cpp::Transp trans_F, const Vector *f, const value_type *obj_d, const value_type *eta, const Vector *d, const Vector *nu, const Vector *mu, const Vector *Ed, const Vector *lambda, const Vector *Fd)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ConstrainedOptPack::QPSolverRelaxedTesterSetOptions</name>
    <filename>classConstrainedOptPack_1_1QPSolverRelaxedTesterSetOptions.html</filename>
    <base>OptionsFromStreamPack::SetOptionsFromStreamNode</base>
    <base>OptionsFromStreamPack::SetOptionsToTargetBase</base>
    <member kind="function">
      <type></type>
      <name>QPSolverRelaxedTesterSetOptions</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxedTesterSetOptions.html</anchorfile>
      <anchor>a5b668139e5f9c08bc73941917d40a7e0</anchor>
      <arglist>(QPSolverRelaxedTester *target=0, const char opt_grp_name[]=&quot;QPSolverRelaxedTester&quot;)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>setOption</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverRelaxedTesterSetOptions.html</anchorfile>
      <anchor>ae8c2470e2ebcc988259c96a2974c1056</anchor>
      <arglist>(int option_num, const std::string &amp;option_value)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ConstrainedOptPack::QPSolverStats</name>
    <filename>classConstrainedOptPack_1_1QPSolverStats.html</filename>
    <member kind="enumeration">
      <name>ESolutionType</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverStats.html</anchorfile>
      <anchor>adac09b753845adbe065c63bc7bd01cf8</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>EConvexity</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverStats.html</anchorfile>
      <anchor>a06285e4ddd3ba022a32743542291cd90</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>QPSolverStats</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverStats.html</anchorfile>
      <anchor>ad67d71ccc1b06baa8e40c7ae551f36b8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_stats</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverStats.html</anchorfile>
      <anchor>a1244548418468010d0d15781e0438614</anchor>
      <arglist>(ESolutionType solution_type, EConvexity convexity, int num_qp_iter, int num_adds, int num_drops, bool warm_start, bool infeasible_qp)</arglist>
    </member>
    <member kind="function">
      <type>ESolutionType</type>
      <name>solution_type</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverStats.html</anchorfile>
      <anchor>a28c0819eb8e68fedd56bcf61713d6a31</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>EConvexity</type>
      <name>convexity</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverStats.html</anchorfile>
      <anchor>af9e3905d25cf411ae87f9ad9d2be3631</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>num_qp_iter</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverStats.html</anchorfile>
      <anchor>a079a792a2d2b78decb78585b55a9b93b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>num_adds</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverStats.html</anchorfile>
      <anchor>a0a957c85a2fb98a9602b6c290a23093a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>num_drop</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverStats.html</anchorfile>
      <anchor>ac74a9fef384ce33f148b2b7320e28de0</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>warm_start</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverStats.html</anchorfile>
      <anchor>aae06cd984502919ce21324140cab6657</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>infeasible_qp</name>
      <anchorfile>classConstrainedOptPack_1_1QPSolverStats.html</anchorfile>
      <anchor>ae731ff277cd13f2435e820671f40e632</anchor>
      <arglist>() const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ConstrainedOptPack::QPSchurPack::ConstraintsRelaxedStd</name>
    <filename>classConstrainedOptPack_1_1QPSchurPack_1_1ConstraintsRelaxedStd.html</filename>
    <base>ConstrainedOptPack::QPSchurPack::Constraints</base>
    <class kind="class">ConstrainedOptPack::QPSchurPack::ConstraintsRelaxedStd::MatrixConstraints</class>
    <member kind="enumeration">
      <name>EInequalityPickPolicy</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchurPack_1_1ConstraintsRelaxedStd.html</anchorfile>
      <anchor>a4119763153d6359d808449068004e00b</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>EPickPolicy</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchurPack_1_1Constraints.html</anchorfile>
      <anchor>a5b22642847ce6fd0bde39895abccc682</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchurPack_1_1ConstraintsRelaxedStd.html</anchorfile>
      <anchor>a5da98c00833ab560c36fa2bed22f302a</anchor>
      <arglist>(value_type, bounds_tol)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchurPack_1_1ConstraintsRelaxedStd.html</anchorfile>
      <anchor>aa05f178f81eb003438e469f6a67a8e34</anchor>
      <arglist>(value_type, inequality_tol)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchurPack_1_1ConstraintsRelaxedStd.html</anchorfile>
      <anchor>a58a3829fbef64c0c046d718340975eac</anchor>
      <arglist>(value_type, equality_tol)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchurPack_1_1ConstraintsRelaxedStd.html</anchorfile>
      <anchor>af618d5459d94c875db537df19f11d58f</anchor>
      <arglist>(EInequalityPickPolicy, inequality_pick_policy)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ConstraintsRelaxedStd</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchurPack_1_1ConstraintsRelaxedStd.html</anchorfile>
      <anchor>a9c1e3c57cb25d7aa105a1d873d0075fd</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initialize</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchurPack_1_1ConstraintsRelaxedStd.html</anchorfile>
      <anchor>a9c549efb28e5e46e9f546ecee3050a58</anchor>
      <arglist>(const VectorSpace::space_ptr_t &amp;space_d_eta, value_type etaL, const Vector *dL, const Vector *dU, const MatrixOp *E, BLAS_Cpp::Transp trans_E, const Vector *b, const Vector *eL, const Vector *eU, const MatrixOp *F, BLAS_Cpp::Transp trans_F, const Vector *f, size_type m_undecomp, const size_type j_f_undecomp[], VectorMutable *Ed, bool check_F=true, value_type bounds_tol=1e-10, value_type inequality_tol=1e-10, value_type equality_tol=1e-10)</arglist>
    </member>
    <member kind="function">
      <type>const MatrixConstraints &amp;</type>
      <name>A_bar_relaxed</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchurPack_1_1ConstraintsRelaxedStd.html</anchorfile>
      <anchor>aaa30a3f7a475d82bd958f82d6578fd35</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>size_type</type>
      <name>n</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchurPack_1_1ConstraintsRelaxedStd.html</anchorfile>
      <anchor>ae42130c439d60e5308663b667a13e6f2</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>size_type</type>
      <name>m_breve</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchurPack_1_1ConstraintsRelaxedStd.html</anchorfile>
      <anchor>a55a1ba7f20950e82ff391dd6d6de5bec</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const MatrixOp &amp;</type>
      <name>A_bar</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchurPack_1_1ConstraintsRelaxedStd.html</anchorfile>
      <anchor>acd74fcf4043bdce4f24c2971ac3f919f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>pick_violated_policy</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchurPack_1_1ConstraintsRelaxedStd.html</anchorfile>
      <anchor>acf40577b5820f30f20b5eda91be33858</anchor>
      <arglist>(EPickPolicy pick_policy)</arglist>
    </member>
    <member kind="function">
      <type>EPickPolicy</type>
      <name>pick_violated_policy</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchurPack_1_1ConstraintsRelaxedStd.html</anchorfile>
      <anchor>a4e3240392a4943894c9cfa6906b10bc1</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>pick_violated</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchurPack_1_1ConstraintsRelaxedStd.html</anchorfile>
      <anchor>a14cb55c70fa5a1f127b17c02ef22b10b</anchor>
      <arglist>(const DVectorSlice &amp;x, size_type *j_viol, value_type *constr_val, value_type *viol_bnd_val, value_type *norm_2_constr, EBounds *bnd, bool *can_ignore) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>ignore</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchurPack_1_1ConstraintsRelaxedStd.html</anchorfile>
      <anchor>af3017e94645bca1055823e047d74cf85</anchor>
      <arglist>(size_type j)</arglist>
    </member>
    <member kind="function">
      <type>value_type</type>
      <name>get_bnd</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchurPack_1_1ConstraintsRelaxedStd.html</anchorfile>
      <anchor>a1f268bf97164fa982722b7a86b80e56d</anchor>
      <arglist>(size_type j, EBounds bnd) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~Constraints</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchurPack_1_1Constraints.html</anchorfile>
      <anchor>a67b17418a14938da03b3eaaf0484e1ab</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ConstrainedOptPack::QPSchurPack::ConstraintsRelaxedStd::MatrixConstraints</name>
    <filename>classConstrainedOptPack_1_1QPSchurPack_1_1ConstraintsRelaxedStd_1_1MatrixConstraints.html</filename>
    <member kind="function">
      <type></type>
      <name>MatrixConstraints</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchurPack_1_1ConstraintsRelaxedStd_1_1MatrixConstraints.html</anchorfile>
      <anchor>a1c5ba16470c604fe6e2e3b6c9b9bd724</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initialize</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchurPack_1_1ConstraintsRelaxedStd_1_1MatrixConstraints.html</anchorfile>
      <anchor>a91492a526f880090802304d1549f9f74</anchor>
      <arglist>(const VectorSpace::space_ptr_t &amp;space_d_eta, const size_type m_in, const size_type m_eq, const MatrixOp *E, BLAS_Cpp::Transp trans_E, const Vector *b, const MatrixOp *F, BLAS_Cpp::Transp trans_F, const Vector *f, size_type m_undecomp, const size_type j_f_undecomp[])</arglist>
    </member>
    <member kind="function">
      <type>size_type</type>
      <name>nd</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchurPack_1_1ConstraintsRelaxedStd_1_1MatrixConstraints.html</anchorfile>
      <anchor>aa7b97baf1105f9576ba62658f852cd2e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>size_type</type>
      <name>m_in</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchurPack_1_1ConstraintsRelaxedStd_1_1MatrixConstraints.html</anchorfile>
      <anchor>a98b4b0d47ac6b980e8aca59d1fea96c2</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>size_type</type>
      <name>m_eq</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchurPack_1_1ConstraintsRelaxedStd_1_1MatrixConstraints.html</anchorfile>
      <anchor>a80311d25ee88d9cc03fd22849225206c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const MatrixOp *</type>
      <name>E</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchurPack_1_1ConstraintsRelaxedStd_1_1MatrixConstraints.html</anchorfile>
      <anchor>a3222c1f5ddbbac41e3845f9e8dc66ae3</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>BLAS_Cpp::Transp</type>
      <name>trans_E</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchurPack_1_1ConstraintsRelaxedStd_1_1MatrixConstraints.html</anchorfile>
      <anchor>a954b4b29fe56415ba18fa2fc26287588</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Vector *</type>
      <name>b</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchurPack_1_1ConstraintsRelaxedStd_1_1MatrixConstraints.html</anchorfile>
      <anchor>a7a8405dfcc71c3eb7bc71ad3ad5a9749</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const MatrixOp *</type>
      <name>F</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchurPack_1_1ConstraintsRelaxedStd_1_1MatrixConstraints.html</anchorfile>
      <anchor>a6d3ed009ed20580fa022b924c0da63cd</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>BLAS_Cpp::Transp</type>
      <name>trans_F</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchurPack_1_1ConstraintsRelaxedStd_1_1MatrixConstraints.html</anchorfile>
      <anchor>a34d0879836969f3a7e833571e8500391</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Vector *</type>
      <name>f</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchurPack_1_1ConstraintsRelaxedStd_1_1MatrixConstraints.html</anchorfile>
      <anchor>a33d306d928980db4811172036b2f6ac7</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const GenPermMatrixSlice &amp;</type>
      <name>P_u</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchurPack_1_1ConstraintsRelaxedStd_1_1MatrixConstraints.html</anchorfile>
      <anchor>adbd5e42698a437fae5ea12f27a7b1220</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const VectorSpace &amp;</type>
      <name>space_cols</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchurPack_1_1ConstraintsRelaxedStd_1_1MatrixConstraints.html</anchorfile>
      <anchor>a02f7cd8a2fc69ccf2b94fbf6ee79b6d2</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const VectorSpace &amp;</type>
      <name>space_rows</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchurPack_1_1ConstraintsRelaxedStd_1_1MatrixConstraints.html</anchorfile>
      <anchor>a339bbc81c07d66925d2c3aced84a956f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>MatrixOp &amp;</type>
      <name>operator=</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchurPack_1_1ConstraintsRelaxedStd_1_1MatrixConstraints.html</anchorfile>
      <anchor>a19a86fb1721a33a57fbe92c75efda7b2</anchor>
      <arglist>(const MatrixOp &amp;m)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Vp_StMtV</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchurPack_1_1ConstraintsRelaxedStd_1_1MatrixConstraints.html</anchorfile>
      <anchor>ab9139e5ab40fd1d7e23c118b918a6b78</anchor>
      <arglist>(VectorMutable *vs_lhs, value_type alpha, BLAS_Cpp::Transp trans_rhs1, const Vector &amp;vs_rhs2, value_type beta) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Vp_StPtMtV</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchurPack_1_1ConstraintsRelaxedStd_1_1MatrixConstraints.html</anchorfile>
      <anchor>afbf6f4032406bee565f8a9583d4dff8f</anchor>
      <arglist>(VectorMutable *vs_lhs, value_type alpha, const GenPermMatrixSlice &amp;P_rhs1, BLAS_Cpp::Transp P_rhs1_trans, BLAS_Cpp::Transp M_rhs2_trans, const SpVectorSlice &amp;sv_rhs3, value_type beta) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ConstrainedOptPack::QPSchurPack::QPInitFixedFreeStd</name>
    <filename>classConstrainedOptPack_1_1QPSchurPack_1_1QPInitFixedFreeStd.html</filename>
    <base>ConstrainedOptPack::QPSchurPack::QP</base>
    <member kind="function">
      <type></type>
      <name>QPInitFixedFreeStd</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchurPack_1_1QPInitFixedFreeStd.html</anchorfile>
      <anchor>a602ad786c5cce33d0e1af1863cf6e257</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initialize</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchurPack_1_1QPInitFixedFreeStd.html</anchorfile>
      <anchor>aebec805fd7eab3149a79d5ca19b0da37</anchor>
      <arglist>(const DVectorSlice &amp;g, const MatrixSymOp &amp;G, const MatrixOp *A, size_type n_R, const size_type i_x_free[], const size_type i_x_fixed[], const EBounds bnd_fixed[], const DVectorSlice &amp;b_X, const MatrixSymOpNonsing &amp;Ko, const DVectorSlice &amp;fo, Constraints *constraints, std::ostream *out=NULL, bool test_setup=false, value_type warning_tol=1e-10, value_type error_tol=1e-5, bool print_all_warnings=false)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~QP</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchurPack_1_1QP.html</anchorfile>
      <anchor>a462f130d28b9465c7cefa3bafa236793</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>dump_qp</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchurPack_1_1QP.html</anchorfile>
      <anchor>a0572da33364ec2d7ef1ef0566395215c</anchor>
      <arglist>(std::ostream &amp;out)</arglist>
    </member>
    <member kind="function">
      <type>size_type</type>
      <name>n</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchurPack_1_1QPInitFixedFreeStd.html</anchorfile>
      <anchor>a4dd665b86a2609d0643c2aa2c01a006a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>size_type</type>
      <name>m</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchurPack_1_1QPInitFixedFreeStd.html</anchorfile>
      <anchor>a94dbdda5b159d7dc141526432a1a7553</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const DVectorSlice</type>
      <name>g</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchurPack_1_1QPInitFixedFreeStd.html</anchorfile>
      <anchor>a9835d9505f57eafa7983e5b228f16552</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const MatrixSymOp &amp;</type>
      <name>G</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchurPack_1_1QPInitFixedFreeStd.html</anchorfile>
      <anchor>adb8844c8ea7644ca7117a32ec575143a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const MatrixOp &amp;</type>
      <name>A</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchurPack_1_1QPInitFixedFreeStd.html</anchorfile>
      <anchor>ae24580a977ade72d3fcabb56cfb324e8</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>size_type</type>
      <name>n_R</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchurPack_1_1QPInitFixedFreeStd.html</anchorfile>
      <anchor>aa418f52ecbc5a8001a5606edb347eff1</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const x_init_t &amp;</type>
      <name>x_init</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchurPack_1_1QPInitFixedFreeStd.html</anchorfile>
      <anchor>aef90b1a9b60f8ef5f9afc2f20e91ecac</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const l_x_X_map_t &amp;</type>
      <name>l_x_X_map</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchurPack_1_1QPInitFixedFreeStd.html</anchorfile>
      <anchor>a0ce2fcd4b56186c01e44ac73fdd895aa</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const i_x_X_map_t &amp;</type>
      <name>i_x_X_map</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchurPack_1_1QPInitFixedFreeStd.html</anchorfile>
      <anchor>ac9a16da52d1876360c4cea77f5e9700d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const DVectorSlice</type>
      <name>b_X</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchurPack_1_1QPInitFixedFreeStd.html</anchorfile>
      <anchor>a4aa12436f61e051cde88e991152329b2</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const GenPermMatrixSlice &amp;</type>
      <name>Q_R</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchurPack_1_1QPInitFixedFreeStd.html</anchorfile>
      <anchor>af51568f173af393459ecef7857960b46</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const GenPermMatrixSlice &amp;</type>
      <name>Q_X</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchurPack_1_1QPInitFixedFreeStd.html</anchorfile>
      <anchor>ac6f8000a1385cafbd90d6ac2ba4d9807</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const MatrixSymOpNonsing &amp;</type>
      <name>Ko</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchurPack_1_1QPInitFixedFreeStd.html</anchorfile>
      <anchor>a12e1da03fdd9ef3146569b67cea04e69</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const DVectorSlice</type>
      <name>fo</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchurPack_1_1QPInitFixedFreeStd.html</anchorfile>
      <anchor>a0aed4b71defefdd76e24b2bcc8e831cf</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Constraints &amp;</type>
      <name>constraints</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchurPack_1_1QPInitFixedFreeStd.html</anchorfile>
      <anchor>a4abcb86e8bc8511565f6f055b2acf113</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const Constraints &amp;</type>
      <name>constraints</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchurPack_1_1QPInitFixedFreeStd.html</anchorfile>
      <anchor>a19d7bbfab2ef8dc127aa80b120a5d7d4</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="typedef">
      <type>vector_one_based_checked&lt; EBounds &gt;</type>
      <name>x_init_t</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchurPack_1_1QP.html</anchorfile>
      <anchor>a9c6229e0966e0b6cb77b5a695ec17395</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>vector_one_based_checked&lt; size_type &gt;</type>
      <name>l_x_X_map_t</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchurPack_1_1QP.html</anchorfile>
      <anchor>af1cb94bcc9479a937f87afb26a23bcba</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>vector_one_based_checked&lt; size_type &gt;</type>
      <name>i_x_X_map_t</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchurPack_1_1QP.html</anchorfile>
      <anchor>a5567ea46a176e5476e5c40f06d52e75f</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>QPSchurPack::Constraints</type>
      <name>Constraints</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchurPack_1_1QP.html</anchorfile>
      <anchor>a5025ea6618c8e2b9d357ab596e68d70b</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ConstrainedOptPack::QPSchurPack::vector_one_based_checked</name>
    <filename>classConstrainedOptPack_1_1QPSchurPack_1_1vector__one__based__checked.html</filename>
    <templarg></templarg>
    <member kind="function">
      <type>T &amp;</type>
      <name>operator()</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchurPack_1_1vector__one__based__checked.html</anchorfile>
      <anchor>a5381b883f5441197870f7c0575517430</anchor>
      <arglist>(typename this_t::size_type i)</arglist>
    </member>
    <member kind="function">
      <type>T</type>
      <name>operator()</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchurPack_1_1vector__one__based__checked.html</anchorfile>
      <anchor>a8fbd0be283f11ebb44022bc40cbcc85b</anchor>
      <arglist>(typename this_t::size_type i) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ConstrainedOptPack::QPSchurPack::QP</name>
    <filename>classConstrainedOptPack_1_1QPSchurPack_1_1QP.html</filename>
    <member kind="typedef">
      <type>vector_one_based_checked&lt; EBounds &gt;</type>
      <name>x_init_t</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchurPack_1_1QP.html</anchorfile>
      <anchor>a9c6229e0966e0b6cb77b5a695ec17395</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>vector_one_based_checked&lt; size_type &gt;</type>
      <name>l_x_X_map_t</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchurPack_1_1QP.html</anchorfile>
      <anchor>af1cb94bcc9479a937f87afb26a23bcba</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>vector_one_based_checked&lt; size_type &gt;</type>
      <name>i_x_X_map_t</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchurPack_1_1QP.html</anchorfile>
      <anchor>a5567ea46a176e5476e5c40f06d52e75f</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>QPSchurPack::Constraints</type>
      <name>Constraints</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchurPack_1_1QP.html</anchorfile>
      <anchor>a5025ea6618c8e2b9d357ab596e68d70b</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~QP</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchurPack_1_1QP.html</anchorfile>
      <anchor>a462f130d28b9465c7cefa3bafa236793</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual size_type</type>
      <name>n</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchurPack_1_1QP.html</anchorfile>
      <anchor>a2ec6460384d10332c753be548dd76961</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual size_type</type>
      <name>m</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchurPack_1_1QP.html</anchorfile>
      <anchor>a5bdd046e1d4bc13173afdaf343011485</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual const DVectorSlice</type>
      <name>g</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchurPack_1_1QP.html</anchorfile>
      <anchor>aa1ff5b0ce5d10107318049dd222e9188</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual const MatrixSymOp &amp;</type>
      <name>G</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchurPack_1_1QP.html</anchorfile>
      <anchor>a24b512f0b98362a4b8bff5d9d2f728c2</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual const MatrixOp &amp;</type>
      <name>A</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchurPack_1_1QP.html</anchorfile>
      <anchor>a32d8b626ac250f3ad979b5d692691e9b</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual size_type</type>
      <name>n_R</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchurPack_1_1QP.html</anchorfile>
      <anchor>adeb4a7a92aac3d2f285512ac8caab1a9</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual const x_init_t &amp;</type>
      <name>x_init</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchurPack_1_1QP.html</anchorfile>
      <anchor>a52d328884f2f68d6cd5a7963f0cb5fae</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual const l_x_X_map_t &amp;</type>
      <name>l_x_X_map</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchurPack_1_1QP.html</anchorfile>
      <anchor>afd5b828232bd96320c547704e81d4b8b</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual const i_x_X_map_t &amp;</type>
      <name>i_x_X_map</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchurPack_1_1QP.html</anchorfile>
      <anchor>a3c9a86ca0cb2a5589334b19f0a40f49b</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual const DVectorSlice</type>
      <name>b_X</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchurPack_1_1QP.html</anchorfile>
      <anchor>affba5c15fc92b38f4ac8854e26503b0f</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual const GenPermMatrixSlice &amp;</type>
      <name>Q_R</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchurPack_1_1QP.html</anchorfile>
      <anchor>aa92aa531a5db0b4b1577f7e8b15d9349</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual const GenPermMatrixSlice &amp;</type>
      <name>Q_X</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchurPack_1_1QP.html</anchorfile>
      <anchor>af92cb2bdaf6ace5804425734249c383f</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual const MatrixSymOpNonsing &amp;</type>
      <name>Ko</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchurPack_1_1QP.html</anchorfile>
      <anchor>a30ae5a1328f7ac196191ddc0dd562c99</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual const DVectorSlice</type>
      <name>fo</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchurPack_1_1QP.html</anchorfile>
      <anchor>aa2e7c1ece593dad74854ba04add55340</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual Constraints &amp;</type>
      <name>constraints</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchurPack_1_1QP.html</anchorfile>
      <anchor>a3d78481c7f9bd3de412be0494b3882b2</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual const Constraints &amp;</type>
      <name>constraints</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchurPack_1_1QP.html</anchorfile>
      <anchor>a1d4b7ad0f8c2a40a940befa02a93af3a</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>dump_qp</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchurPack_1_1QP.html</anchorfile>
      <anchor>a0572da33364ec2d7ef1ef0566395215c</anchor>
      <arglist>(std::ostream &amp;out)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ConstrainedOptPack::QPSchurPack::Constraints</name>
    <filename>classConstrainedOptPack_1_1QPSchurPack_1_1Constraints.html</filename>
    <member kind="enumeration">
      <name>EPickPolicy</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchurPack_1_1Constraints.html</anchorfile>
      <anchor>a5b22642847ce6fd0bde39895abccc682</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~Constraints</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchurPack_1_1Constraints.html</anchorfile>
      <anchor>a67b17418a14938da03b3eaaf0484e1ab</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual size_type</type>
      <name>n</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchurPack_1_1Constraints.html</anchorfile>
      <anchor>abddf9563092af9b47fe08aa6c15c8f10</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual size_type</type>
      <name>m_breve</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchurPack_1_1Constraints.html</anchorfile>
      <anchor>af883f09c21bf80bd1281a2e7a39c2717</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual const MatrixOp &amp;</type>
      <name>A_bar</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchurPack_1_1Constraints.html</anchorfile>
      <anchor>ad758afc8c0acf47927e728a9474e2c63</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>pick_violated_policy</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchurPack_1_1Constraints.html</anchorfile>
      <anchor>a8634a32250df60670be53c581383ef96</anchor>
      <arglist>(EPickPolicy pick_policy)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual EPickPolicy</type>
      <name>pick_violated_policy</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchurPack_1_1Constraints.html</anchorfile>
      <anchor>a21068cb596c01dce93dc868b6e09a440</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>pick_violated</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchurPack_1_1Constraints.html</anchorfile>
      <anchor>aa7cb4dedcb15bb7553f4f8ea4ed69770</anchor>
      <arglist>(const DVectorSlice &amp;x, size_type *j_viol, value_type *constr_val, value_type *viol_bnd_val, value_type *norm_2_constr, EBounds *bnd, bool *can_ignore) const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>ignore</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchurPack_1_1Constraints.html</anchorfile>
      <anchor>af00208cd1996cc75fd6f45c9fa88215b</anchor>
      <arglist>(size_type j)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual value_type</type>
      <name>get_bnd</name>
      <anchorfile>classConstrainedOptPack_1_1QPSchurPack_1_1Constraints.html</anchorfile>
      <anchor>af2656bec8c2579850c94bac61fb80874</anchor>
      <arglist>(size_type j, EBounds bnd) const =0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>QPKWIK_Output::set_output</name>
    <filename>classQPKWIK__Output_1_1set__output.html</filename>
    <member kind="function">
      <type></type>
      <name>set_output</name>
      <anchorfile>classQPKWIK__Output_1_1set__output.html</anchorfile>
      <anchor>af7f9955329f69f482dacbc3a17fec11f</anchor>
      <arglist>(std::ostream *out)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~set_output</name>
      <anchorfile>classQPKWIK__Output_1_1set__output.html</anchorfile>
      <anchor>a853c8ea18dc0a2721a45e5d23830dfd1</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="dir">
    <name>ConstrainedOptPack</name>
    <path>/Users/sscoll/Downloads/trilinos-11.0.3-Source/packages/moocho/src/ConstrainedOptPack/</path>
    <filename>dir_74e2252e0908ae7b4996603afe281b51.html</filename>
    <dir>src</dir>
  </compound>
  <compound kind="dir">
    <name>decompositions</name>
    <path>/Users/sscoll/Downloads/trilinos-11.0.3-Source/packages/moocho/src/ConstrainedOptPack/src/decompositions/</path>
    <filename>dir_ffe628b3d28075e86094f778ea5b87d9.html</filename>
    <file>ConstrainedOptPack_DecompositionSystem.cpp</file>
    <file>ConstrainedOptPack_DecompositionSystem.hpp</file>
    <file>ConstrainedOptPack_DecompositionSystemCoordinate.cpp</file>
    <file>ConstrainedOptPack_DecompositionSystemCoordinate.hpp</file>
    <file>ConstrainedOptPack_DecompositionSystemOrthogonal.cpp</file>
    <file>ConstrainedOptPack_DecompositionSystemOrthogonal.hpp</file>
    <file>ConstrainedOptPack_DecompositionSystemTester.cpp</file>
    <file>ConstrainedOptPack_DecompositionSystemTester.hpp</file>
    <file>ConstrainedOptPack_DecompositionSystemTesterSetOptions.cpp</file>
    <file>ConstrainedOptPack_DecompositionSystemTesterSetOptions.hpp</file>
    <file>ConstrainedOptPack_DecompositionSystemVarReduct.hpp</file>
    <file>ConstrainedOptPack_DecompositionSystemVarReductImp.cpp</file>
    <file>ConstrainedOptPack_DecompositionSystemVarReductImp.hpp</file>
    <file>ConstrainedOptPack_DecompositionSystemVarReductPerm.hpp</file>
    <file>ConstrainedOptPack_DecompositionSystemVarReductPermStd.cpp</file>
    <file>ConstrainedOptPack_DecompositionSystemVarReductPermStd.hpp</file>
  </compound>
  <compound kind="dir">
    <name>globalization</name>
    <path>/Users/sscoll/Downloads/trilinos-11.0.3-Source/packages/moocho/src/ConstrainedOptPack/src/globalization/</path>
    <filename>dir_89ee4f8cf130f6f0c598361d0b6f6f07.html</filename>
    <file>ConstrainedOptPack_DirectLineSearch_Strategy.hpp</file>
    <file>ConstrainedOptPack_DirectLineSearchArmQuad_Strategy.cpp</file>
    <file>ConstrainedOptPack_DirectLineSearchArmQuad_Strategy.hpp</file>
    <file>ConstrainedOptPack_DirectLineSearchArmQuad_StrategySetOptions.cpp</file>
    <file>ConstrainedOptPack_DirectLineSearchArmQuad_StrategySetOptions.hpp</file>
    <file>ConstrainedOptPack_MeritFuncCalc.hpp</file>
    <file>ConstrainedOptPack_MeritFuncCalc1D.hpp</file>
    <file>ConstrainedOptPack_MeritFuncCalc1DQuadratic.cpp</file>
    <file>ConstrainedOptPack_MeritFuncCalc1DQuadratic.hpp</file>
    <file>ConstrainedOptPack_MeritFuncCalcNLE.cpp</file>
    <file>ConstrainedOptPack_MeritFuncCalcNLE.hpp</file>
    <file>ConstrainedOptPack_MeritFuncCalcNLP.cpp</file>
    <file>ConstrainedOptPack_MeritFuncCalcNLP.hpp</file>
    <file>ConstrainedOptPack_MeritFuncNLE.hpp</file>
    <file>ConstrainedOptPack_MeritFuncNLESqrResid.cpp</file>
    <file>ConstrainedOptPack_MeritFuncNLESqrResid.hpp</file>
    <file>ConstrainedOptPack_MeritFuncNLP.cpp</file>
    <file>ConstrainedOptPack_MeritFuncNLP.hpp</file>
    <file>ConstrainedOptPack_MeritFuncNLPDirecDeriv.hpp</file>
    <file>ConstrainedOptPack_MeritFuncNLPL1.cpp</file>
    <file>ConstrainedOptPack_MeritFuncNLPL1.hpp</file>
    <file>ConstrainedOptPack_MeritFuncNLPModL1.cpp</file>
    <file>ConstrainedOptPack_MeritFuncNLPModL1.hpp</file>
    <file>ConstrainedOptPack_MeritFuncPenaltyParam.hpp</file>
    <file>ConstrainedOptPack_MeritFuncPenaltyParams.hpp</file>
  </compound>
  <compound kind="dir">
    <name>matrices</name>
    <path>/Users/sscoll/Downloads/trilinos-11.0.3-Source/packages/moocho/src/ConstrainedOptPack/src/matrices/</path>
    <filename>dir_c2d3462e76b7f79822d5423628a5760f.html</filename>
    <file>ConstrainedOptPack_MatrixDecompRangeOrthog.cpp</file>
    <file>ConstrainedOptPack_MatrixDecompRangeOrthog.hpp</file>
    <file>ConstrainedOptPack_MatrixGenBanded.cpp</file>
    <file>ConstrainedOptPack_MatrixGenBanded.hpp</file>
    <file>ConstrainedOptPack_MatrixHessianRelaxed.cpp</file>
    <file>ConstrainedOptPack_MatrixHessianRelaxed.hpp</file>
    <file>ConstrainedOptPack_MatrixHessianSuperBasic.cpp</file>
    <file>ConstrainedOptPack_MatrixHessianSuperBasic.hpp</file>
    <file>ConstrainedOptPack_MatrixHessianSuperBasicInitDiagonal.cpp</file>
    <file>ConstrainedOptPack_MatrixHessianSuperBasicInitDiagonal.hpp</file>
    <file>ConstrainedOptPack_MatrixIdentConcat.cpp</file>
    <file>ConstrainedOptPack_MatrixIdentConcat.hpp</file>
    <file>ConstrainedOptPack_MatrixIdentConcatStd.cpp</file>
    <file>ConstrainedOptPack_MatrixIdentConcatStd.hpp</file>
    <file>ConstrainedOptPack_MatrixKKTFullSpaceRelaxed.cpp</file>
    <file>ConstrainedOptPack_MatrixKKTFullSpaceRelaxed.hpp</file>
    <file>ConstrainedOptPack_MatrixSymAddDelBunchKaufman.cpp</file>
    <file>ConstrainedOptPack_MatrixSymAddDelBunchKaufman.hpp</file>
    <file>ConstrainedOptPack_MatrixSymAddDelUpdateableWithOpNonsingular.hpp</file>
    <file>ConstrainedOptPack_MatrixSymHessianRelaxNonSing.cpp</file>
    <file>ConstrainedOptPack_MatrixSymHessianRelaxNonSing.hpp</file>
    <file>ConstrainedOptPack_MatrixSymIdentitySerial.cpp</file>
    <file>ConstrainedOptPack_MatrixSymIdentitySerial.hpp</file>
    <file>ConstrainedOptPack_MatrixSymPosDefBandedChol.cpp</file>
    <file>ConstrainedOptPack_MatrixSymPosDefBandedChol.hpp</file>
    <file>ConstrainedOptPack_MatrixSymPosDefInvCholFactor.cpp</file>
    <file>ConstrainedOptPack_MatrixSymPosDefInvCholFactor.hpp</file>
    <file>ConstrainedOptPack_MatrixSymPosDefLBFGS.cpp</file>
    <file>ConstrainedOptPack_MatrixSymPosDefLBFGS.hpp</file>
    <file>ConstrainedOptPack_MatrixSymPosDefLBFGSSerial.cpp</file>
    <file>ConstrainedOptPack_MatrixSymPosDefLBFGSSerial.hpp</file>
    <file>ConstrainedOptPack_MatrixVarReductImplicit.cpp</file>
    <file>ConstrainedOptPack_MatrixVarReductImplicit.hpp</file>
  </compound>
  <compound kind="dir">
    <name>misc</name>
    <path>/Users/sscoll/Downloads/trilinos-11.0.3-Source/packages/moocho/src/ConstrainedOptPack/src/misc/</path>
    <filename>dir_517f5ca792537e2fe70969c03890b69f.html</filename>
    <file>ConstrainedOptPack_ComputeMinMult.cpp</file>
    <file>ConstrainedOptPack_ComputeMinMult.hpp</file>
    <file>ConstrainedOptPack_initialize_Q_R_Q_X.cpp</file>
    <file>ConstrainedOptPack_initialize_Q_R_Q_X.hpp</file>
    <file>ConstrainedOptPack_print_vector_change_stats.cpp</file>
    <file>ConstrainedOptPack_print_vector_change_stats.hpp</file>
    <file>ConstrainedOptPack_VariableBoundsTester.cpp</file>
    <file>ConstrainedOptPack_VariableBoundsTester.hpp</file>
    <file>ConstrainedOptPack_VariableBoundsTesterSetOptions.cpp</file>
    <file>ConstrainedOptPack_VariableBoundsTesterSetOptions.hpp</file>
    <file>ConstrainedOptPack_vector_change_stats.cpp</file>
    <file>ConstrainedOptPack_vector_change_stats.hpp</file>
  </compound>
  <compound kind="dir">
    <name>qpsolvers</name>
    <path>/Users/sscoll/Downloads/trilinos-11.0.3-Source/packages/moocho/src/ConstrainedOptPack/src/qpsolvers/</path>
    <filename>dir_5e9e7ef8ab61c41cf3dea54a9923f1ed.html</filename>
    <file>ConstrainedOptPack_ConstraintsRelaxedStd.cpp</file>
    <file>ConstrainedOptPack_ConstraintsRelaxedStd.hpp</file>
    <file>ConstrainedOptPack_QPInitFixedFreeStd.cpp</file>
    <file>ConstrainedOptPack_QPInitFixedFreeStd.hpp</file>
    <file>ConstrainedOptPack_QPKWIK_Output.cpp</file>
    <file>ConstrainedOptPack_QPKWIK_Output.hpp</file>
    <file>ConstrainedOptPack_QPOPT_CppDecl.hpp</file>
    <file>ConstrainedOptPack_QPSchur.cpp</file>
    <file>ConstrainedOptPack_QPSchur.hpp</file>
    <file>ConstrainedOptPack_QPSchurInitKKTSystemHessianFixedFree.cpp</file>
    <file>ConstrainedOptPack_QPSchurInitKKTSystemHessianFixedFree.hpp</file>
    <file>ConstrainedOptPack_QPSchurInitKKTSystemHessianFull.cpp</file>
    <file>ConstrainedOptPack_QPSchurInitKKTSystemHessianFull.hpp</file>
    <file>ConstrainedOptPack_QPSchurInitKKTSystemHessianRelaxed.cpp</file>
    <file>ConstrainedOptPack_QPSchurInitKKTSystemHessianRelaxed.hpp</file>
    <file>ConstrainedOptPack_QPSchurInitKKTSystemHessianSuperBasic.cpp</file>
    <file>ConstrainedOptPack_QPSchurInitKKTSystemHessianSuperBasic.hpp</file>
    <file>ConstrainedOptPack_QPSolverRelaxed.cpp</file>
    <file>ConstrainedOptPack_QPSolverRelaxed.hpp</file>
    <file>ConstrainedOptPack_QPSolverRelaxedLOQO.cpp</file>
    <file>ConstrainedOptPack_QPSolverRelaxedLOQO.hpp</file>
    <file>ConstrainedOptPack_QPSolverRelaxedQPKWIK.cpp</file>
    <file>ConstrainedOptPack_QPSolverRelaxedQPKWIK.hpp</file>
    <file>ConstrainedOptPack_QPSolverRelaxedQPOPT.cpp</file>
    <file>ConstrainedOptPack_QPSolverRelaxedQPOPT.hpp</file>
    <file>ConstrainedOptPack_QPSolverRelaxedQPOPTSOL.cpp</file>
    <file>ConstrainedOptPack_QPSolverRelaxedQPOPTSOL.hpp</file>
    <file>ConstrainedOptPack_QPSolverRelaxedQPSchur.cpp</file>
    <file>ConstrainedOptPack_QPSolverRelaxedQPSchur.hpp</file>
    <file>ConstrainedOptPack_QPSolverRelaxedQPSchurSetOptions.cpp</file>
    <file>ConstrainedOptPack_QPSolverRelaxedQPSchurSetOptions.hpp</file>
    <file>ConstrainedOptPack_QPSolverRelaxedTester.cpp</file>
    <file>ConstrainedOptPack_QPSolverRelaxedTester.hpp</file>
    <file>ConstrainedOptPack_QPSolverRelaxedTesterSetOptions.cpp</file>
    <file>ConstrainedOptPack_QPSolverRelaxedTesterSetOptions.hpp</file>
    <file>ConstrainedOptPack_QPSolverStats.hpp</file>
  </compound>
  <compound kind="dir">
    <name>src</name>
    <path>/Users/sscoll/Downloads/trilinos-11.0.3-Source/packages/moocho/src/ConstrainedOptPack/src/</path>
    <filename>dir_ae18d17cad6254e7ebf0b2f203666ef2.html</filename>
    <dir>decompositions</dir>
    <dir>globalization</dir>
    <dir>matrices</dir>
    <dir>misc</dir>
    <dir>qpsolvers</dir>
    <file>ConstrainedOptPack_Types.hpp</file>
  </compound>
  <compound kind="dir">
    <name>src</name>
    <path>/Users/sscoll/Downloads/trilinos-11.0.3-Source/packages/moocho/src/</path>
    <filename>dir_68267d1309a1af8e8297ef4c3efbcdba.html</filename>
    <dir>ConstrainedOptPack</dir>
  </compound>
  <compound kind="page">
    <name>index</name>
    <title>ConstrainedOptPack: C++ Tools for Constrained (and Unconstrained) Optimization</title>
    <filename>index</filename>
  </compound>
</tagfile>
