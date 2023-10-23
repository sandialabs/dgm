<?xml version='1.0' encoding='ISO-8859-1' standalone='yes' ?>
<tagfile>
  <compound kind="page">
    <name>index</name>
    <title>MOOCHO: Multi-functional Object-Oriented arCHitecture for Optimization</title>
    <filename>index</filename>
    <docanchor file="index">moocho_quickstart_solver_output_sec</docanchor>
    <docanchor file="index">moocho_quickstart_solve_driver_sec</docanchor>
    <docanchor file="index">mooch_intro_sec</docanchor>
    <docanchor file="index">moocho_internal_links_sec</docanchor>
    <docanchor file="index">moocho_nlps_sec</docanchor>
    <docanchor file="index">moocho_console_output_sec</docanchor>
    <docanchor file="index">moocho_quickstart_algo_interrupt_sec</docanchor>
    <docanchor file="index">moocho_summary_output_sec</docanchor>
    <docanchor file="index">moocho_math_overview_sec</docanchor>
    <docanchor file="index">moocho_links_sec</docanchor>
    <docanchor file="index">moocho_explicit_nlps_sec</docanchor>
    <docanchor file="index">moocho_pdf_version_sec</docanchor>
    <docanchor file="index">moocho_quickstart_moocho_input_options_sec</docanchor>
    <docanchor file="index">moocho_quickstart_sec</docanchor>
    <docanchor file="index">moocho_outline_sec</docanchor>
    <docanchor file="index">moocho_browse_sec</docanchor>
    <docanchor file="index">moocho_quickstart_input_linear_solver_input_params_sec</docanchor>
    <docanchor file="index">moocho_quickstart_solving_sec</docanchor>
    <docanchor file="index">moocho_dependencies_sec</docanchor>
    <docanchor file="index">moocho_simulation_constrained_nlps_sec</docanchor>
    <docanchor file="index">moocho_journal_output_sec</docanchor>
    <docanchor file="index">moocho_algo_output_sec</docanchor>
  </compound>
  <compound kind="group">
    <name>moocho_sample_inout_output_files_grp</name>
    <title>Sample MOOCHO input and output.</title>
    <filename>group__moocho__sample__inout__output__files__grp.html</filename>
    <subgroup>moocho_option_sample_grp</subgroup>
    <subgroup>moocho_console_sample_out_grp</subgroup>
    <subgroup>moocho_algo_sample_out_grp</subgroup>
    <subgroup>moocho_summary_sample_out_grp</subgroup>
    <subgroup>moocho_journal_sample_out_grp</subgroup>
  </compound>
  <compound kind="group">
    <name>moocho_option_sample_grp</name>
    <title>Sample MOOCHO Options File</title>
    <filename>group__moocho__option__sample__grp.html</filename>
  </compound>
  <compound kind="group">
    <name>moocho_console_sample_out_grp</name>
    <title>Sample MOOCHO Console Output</title>
    <filename>group__moocho__console__sample__out__grp.html</filename>
  </compound>
  <compound kind="group">
    <name>moocho_algo_sample_out_grp</name>
    <title>Sample MOOCHO Algorithm Configuration Output (MoochoAlgo.out)</title>
    <filename>group__moocho__algo__sample__out__grp.html</filename>
  </compound>
  <compound kind="group">
    <name>moocho_summary_sample_out_grp</name>
    <title>Sample MOOCHO Algorithm Summary Output (MoochoSummary.out)</title>
    <filename>group__moocho__summary__sample__out__grp.html</filename>
  </compound>
  <compound kind="group">
    <name>moocho_journal_sample_out_grp</name>
    <title>Sample MOOCHO Algorithm Journal Output (MoochoJournal.out)</title>
    <filename>group__moocho__journal__sample__out__grp.html</filename>
  </compound>
  <compound kind="group">
    <name>explnlp2_ops_grp</name>
    <title>Reduction/Transformation operators for example NLP subclass.</title>
    <filename>group__explnlp2__ops__grp.html</filename>
    <subgroup>explnlp2_eval_grp</subgroup>
    <subgroup>explnlp2_calc_py_D_grp</subgroup>
  </compound>
  <compound kind="group">
    <name>explnlp2_eval_grp</name>
    <title>Evaluate the constraints for the example NLP.</title>
    <filename>group__explnlp2__eval__grp.html</filename>
    <member kind="function">
      <type>int</type>
      <name>RTOp_TOp_explnlp2_c_eval_construct</name>
      <anchorfile>group__explnlp2__eval__grp.html</anchorfile>
      <anchor>gaa1f071f654bea452ef4f04dae62e0cb2</anchor>
      <arglist>(struct RTOp_RTOp *op)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>RTOp_TOp_explnlp2_c_eval_destroy</name>
      <anchorfile>group__explnlp2__eval__grp.html</anchorfile>
      <anchor>ga7c35c0aff28f63a2e28f6a2cd92aa989</anchor>
      <arglist>(struct RTOp_RTOp *op)</arglist>
    </member>
    <member kind="variable">
      <type>struct RTOp_RTOp_vtbl_t</type>
      <name>RTOp_TOp_explnlp2_c_eval_vtbl</name>
      <anchorfile>group__explnlp2__eval__grp.html</anchorfile>
      <anchor>gaef06e312c4b427439c0ec5a6c898b57b</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>explnlp2_calc_py_D_grp</name>
    <title>Evaluate py = -inv(C)c and/or D = inv(C)N for the example %NLP.</title>
    <filename>group__explnlp2__calc__py__D__grp.html</filename>
    <member kind="function">
      <type>int</type>
      <name>RTOp_TOp_explnlp2_calc_py_D_construct</name>
      <anchorfile>group__explnlp2__calc__py__D__grp.html</anchorfile>
      <anchor>ga864065da9f4a35697324930f22662cf7</anchor>
      <arglist>(int task, struct RTOp_RTOp *op)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>RTOp_TOp_explnlp2_calc_py_D_set_task</name>
      <anchorfile>group__explnlp2__calc__py__D__grp.html</anchorfile>
      <anchor>ga3dc0e166ad6c200f14ef1360c0e86bdc</anchor>
      <arglist>(int task, struct RTOp_RTOp *op)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>RTOp_TOp_explnlp2_calc_py_D_destroy</name>
      <anchorfile>group__explnlp2__calc__py__D__grp.html</anchorfile>
      <anchor>ga2c32ad8d814d82b221ca430dc84e75ea</anchor>
      <arglist>(struct RTOp_RTOp *op)</arglist>
    </member>
    <member kind="variable">
      <type>struct RTOp_RTOp_vtbl_t</type>
      <name>RTOp_TOp_explnlp2_calc_py_D_vtbl</name>
      <anchorfile>group__explnlp2__calc__py__D__grp.html</anchorfile>
      <anchor>ga7e2ce3b668938d02108e44a32d5a6192</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>ExampleNLPDirectRun_grp</name>
    <title>Helper function for ExampleNLPDirect</title>
    <filename>group__ExampleNLPDirectRun__grp.html</filename>
    <member kind="function">
      <type>MoochoPack::MoochoSolver::ESolutionStatus</type>
      <name>ExampleNLPDirectRun</name>
      <anchorfile>group__ExampleNLPDirectRun__grp.html</anchorfile>
      <anchor>ga2ed6f28b87166e53940783dda704b107</anchor>
      <arglist>(const VectorSpace &amp;vec_space, value_type xo, bool has_bounds, bool dep_bounded, std::ostream *console_out, std::ostream *error_out, bool throw_solve_exception=false, std::ostream *algo_out=NULL, std::ostream *summary_out=NULL, std::ostream *journal_out=NULL)</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>ExampleNLPFirstOrderRun_grp</name>
    <title>Helper function for ExampleNLPFirstOrder</title>
    <filename>group__ExampleNLPFirstOrderRun__grp.html</filename>
    <member kind="function">
      <type>MoochoPack::MoochoSolver::ESolutionStatus</type>
      <name>ExampleNLPFirstOrderRun</name>
      <anchorfile>group__ExampleNLPFirstOrderRun__grp.html</anchorfile>
      <anchor>ga3e518e58342c0947ab43f422a6f41d55</anchor>
      <arglist>(const VectorSpace &amp;vec_space, value_type xo, bool has_bounds, bool dep_bounded, std::ostream *console_out, std::ostream *error_out, bool throw_solve_exception=false, std::ostream *algo_out=NULL, std::ostream *summary_out=NULL, std::ostream *journal_out=NULL)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>NLPInterfacePack::ExampleNLPBanded</name>
    <filename>classNLPInterfacePack_1_1ExampleNLPBanded.html</filename>
    <base>NLPInterfacePack::NLPSerialPreprocessExplJac</base>
    <member kind="function">
      <type></type>
      <name>ExampleNLPBanded</name>
      <anchorfile>classNLPInterfacePack_1_1ExampleNLPBanded.html</anchorfile>
      <anchor>a2ec88ca3bb9b80be6e4517e416e7a86f</anchor>
      <arglist>(size_type nD, size_type nI, size_type bw=1, size_type mU=0, size_type mI=0, value_type xo=0.1, value_type xDl=-NLP::infinite_bound(), value_type xDu=+NLP::infinite_bound(), value_type xIl=-NLP::infinite_bound(), value_type xIu=+NLP::infinite_bound(), value_type hl=-NLP::infinite_bound(), value_type hu=+NLP::infinite_bound(), bool nlp_selects_basis=false, value_type diag_scal=10.0, value_type diag_vary=1.0, bool sym_basis=false, value_type f_offset=0.0, value_type co=0.0, bool ignore_constraints=false)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initialize</name>
      <anchorfile>classNLPInterfacePack_1_1ExampleNLPBanded.html</anchorfile>
      <anchor>a34c782e09fdc63a79d93207bac3a1149</anchor>
      <arglist>(bool test_setup)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>is_initialized</name>
      <anchorfile>classNLPInterfacePack_1_1ExampleNLPBanded.html</anchorfile>
      <anchor>a3453444a756d7d99bc418d8d354a72b9</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>value_type</type>
      <name>max_var_bounds_viol</name>
      <anchorfile>classNLPInterfacePack_1_1ExampleNLPBanded.html</anchorfile>
      <anchor>ac3fc2e508e911c990333f2ccde82e1e4</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>nlp_selects_basis</name>
      <anchorfile>classNLPInterfacePack_1_1ExampleNLPBanded.html</anchorfile>
      <anchor>a850f3bf499b262f6e2d5d9ddc402ec00</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>bool</type>
      <name>imp_nlp_has_changed</name>
      <anchorfile>classNLPInterfacePack_1_1ExampleNLPBanded.html</anchorfile>
      <anchor>aa4effbd4018eb7f6b8a7c00ea933ab87</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>size_type</type>
      <name>imp_n_orig</name>
      <anchorfile>classNLPInterfacePack_1_1ExampleNLPBanded.html</anchorfile>
      <anchor>afa5a8002258d7a475e39550ef757c3a3</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>size_type</type>
      <name>imp_m_orig</name>
      <anchorfile>classNLPInterfacePack_1_1ExampleNLPBanded.html</anchorfile>
      <anchor>acc0e5d286688bb44c50af93b4bd64687</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>size_type</type>
      <name>imp_mI_orig</name>
      <anchorfile>classNLPInterfacePack_1_1ExampleNLPBanded.html</anchorfile>
      <anchor>a260dfb320308df50c1413dad7add7501</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>const DVectorSlice</type>
      <name>imp_xinit_orig</name>
      <anchorfile>classNLPInterfacePack_1_1ExampleNLPBanded.html</anchorfile>
      <anchor>a448610202a32b253e1ba4a79b0884211</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>bool</type>
      <name>imp_has_var_bounds</name>
      <anchorfile>classNLPInterfacePack_1_1ExampleNLPBanded.html</anchorfile>
      <anchor>a4642aeb62c69fab9c3442453b985598a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>const DVectorSlice</type>
      <name>imp_xl_orig</name>
      <anchorfile>classNLPInterfacePack_1_1ExampleNLPBanded.html</anchorfile>
      <anchor>a724f1ab7ac3c8ef59c0ab6f2aac9b05b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>const DVectorSlice</type>
      <name>imp_xu_orig</name>
      <anchorfile>classNLPInterfacePack_1_1ExampleNLPBanded.html</anchorfile>
      <anchor>aa60a6abdcab62f67bda3d58406c147ef</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>const DVectorSlice</type>
      <name>imp_hl_orig</name>
      <anchorfile>classNLPInterfacePack_1_1ExampleNLPBanded.html</anchorfile>
      <anchor>aa882736ee1fa32738b4b09f38487ca90</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>const DVectorSlice</type>
      <name>imp_hu_orig</name>
      <anchorfile>classNLPInterfacePack_1_1ExampleNLPBanded.html</anchorfile>
      <anchor>a42270b0130d1bcde5a2d4fb19beae633</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>imp_calc_f_orig</name>
      <anchorfile>classNLPInterfacePack_1_1ExampleNLPBanded.html</anchorfile>
      <anchor>a7f57793dbb1ce64e8d3b1b467df8e35e</anchor>
      <arglist>(const DVectorSlice &amp;x_full, bool newx, const ZeroOrderInfoSerial &amp;zero_order_info) const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>imp_calc_c_orig</name>
      <anchorfile>classNLPInterfacePack_1_1ExampleNLPBanded.html</anchorfile>
      <anchor>a66ee10831379e202ddc559ed15c17209</anchor>
      <arglist>(const DVectorSlice &amp;x_full, bool newx, const ZeroOrderInfoSerial &amp;zero_order_info) const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>imp_calc_h_orig</name>
      <anchorfile>classNLPInterfacePack_1_1ExampleNLPBanded.html</anchorfile>
      <anchor>a3e957fbe060712d9095557dac41f66db</anchor>
      <arglist>(const DVectorSlice &amp;x_full, bool newx, const ZeroOrderInfoSerial &amp;zero_order_info) const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>imp_calc_Gf_orig</name>
      <anchorfile>classNLPInterfacePack_1_1ExampleNLPBanded.html</anchorfile>
      <anchor>af6856ae47075a8d8ecd803a883acccf5</anchor>
      <arglist>(const DVectorSlice &amp;x_full, bool newx, const ObjGradInfoSerial &amp;obj_grad_info) const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>bool</type>
      <name>imp_get_next_basis</name>
      <anchorfile>classNLPInterfacePack_1_1ExampleNLPBanded.html</anchorfile>
      <anchor>a8bbe6cc70818934d124aaf6f1f38c74b</anchor>
      <arglist>(IVector *var_perm_full, IVector *equ_perm_full, size_type *rank_full, size_type *rank)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>imp_report_orig_final_solution</name>
      <anchorfile>classNLPInterfacePack_1_1ExampleNLPBanded.html</anchorfile>
      <anchor>a722caadd7ec42fc15c3e5f90c99c4907</anchor>
      <arglist>(const DVectorSlice &amp;x_orig, const DVectorSlice *lambda_orig, const DVectorSlice *lambdaI_orig, const DVectorSlice *nu_orig, bool is_optimal) const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>size_type</type>
      <name>imp_Gc_nz_orig</name>
      <anchorfile>classNLPInterfacePack_1_1ExampleNLPBanded.html</anchorfile>
      <anchor>a258f9fae401c4584fc047f40bde4a443</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>size_type</type>
      <name>imp_Gh_nz_orig</name>
      <anchorfile>classNLPInterfacePack_1_1ExampleNLPBanded.html</anchorfile>
      <anchor>aec0c7a9c1229a885e5d5e483a82c0d6d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>imp_calc_Gc_orig</name>
      <anchorfile>classNLPInterfacePack_1_1ExampleNLPBanded.html</anchorfile>
      <anchor>a62fd807d11f8cf79a388b5fac668d9a4</anchor>
      <arglist>(const DVectorSlice &amp;x_full, bool newx, const FirstOrderExplInfo &amp;first_order_expl_info) const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>imp_calc_Gh_orig</name>
      <anchorfile>classNLPInterfacePack_1_1ExampleNLPBanded.html</anchorfile>
      <anchor>aa95e3743e110183bf15122cf1d788423</anchor>
      <arglist>(const DVectorSlice &amp;x_full, bool newx, const FirstOrderExplInfo &amp;first_order_expl_info) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>NLPInterfacePack::ExampleNLPDirect</name>
    <filename>classNLPInterfacePack_1_1ExampleNLPDirect.html</filename>
    <base virtualness="virtual">NLPInterfacePack::NLPDirect</base>
    <base virtualness="virtual">NLPInterfacePack::ExampleNLPObjGrad</base>
    <member kind="function">
      <type></type>
      <name>ExampleNLPDirect</name>
      <anchorfile>classNLPInterfacePack_1_1ExampleNLPDirect.html</anchorfile>
      <anchor>a4109eeced9b3f2fba479d514fb0234e0</anchor>
      <arglist>(const VectorSpace::space_ptr_t &amp;vec_space, value_type xo, bool has_bounds, bool dep_bounded)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initialize</name>
      <anchorfile>classNLPInterfacePack_1_1ExampleNLPDirect.html</anchorfile>
      <anchor>a8f5df1e112f8532eae7edd3349d45b1d</anchor>
      <arglist>(bool test_setup)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>is_initialized</name>
      <anchorfile>classNLPInterfacePack_1_1ExampleNLPDirect.html</anchorfile>
      <anchor>a95932a44f796782fb5478afdfc756e89</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Range1D</type>
      <name>var_dep</name>
      <anchorfile>classNLPInterfacePack_1_1ExampleNLPDirect.html</anchorfile>
      <anchor>af7a0e8239417b0825da42026a2e161a1</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Range1D</type>
      <name>var_indep</name>
      <anchorfile>classNLPInterfacePack_1_1ExampleNLPDirect.html</anchorfile>
      <anchor>aae9412faa52c98f6d04f62cf152d51e8</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const mat_fcty_ptr_t</type>
      <name>factory_D</name>
      <anchorfile>classNLPInterfacePack_1_1ExampleNLPDirect.html</anchorfile>
      <anchor>aa17d462b57c3709931d12798cb8078e7</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>calc_point</name>
      <anchorfile>classNLPInterfacePack_1_1ExampleNLPDirect.html</anchorfile>
      <anchor>aa0f6691089bf7f881653f6b9d985b1d6</anchor>
      <arglist>(const Vector &amp;x, value_type *f, VectorMutable *c, bool recalc_c, VectorMutable *Gf, VectorMutable *py, VectorMutable *rGf, MatrixOp *GcU, MatrixOp *D, MatrixOp *Uz) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>calc_semi_newton_step</name>
      <anchorfile>classNLPInterfacePack_1_1ExampleNLPDirect.html</anchorfile>
      <anchor>ab84cc6a2876c8364587ebf2a0aeaaa45</anchor>
      <arglist>(const Vector &amp;x, VectorMutable *c, bool recalc_c, VectorMutable *py) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>NLPInterfacePack::ExampleNLPObjGrad</name>
    <filename>classNLPInterfacePack_1_1ExampleNLPObjGrad.html</filename>
    <base virtualness="virtual">NLPInterfacePack::NLPObjGrad</base>
    <member kind="function">
      <type></type>
      <name>ExampleNLPObjGrad</name>
      <anchorfile>classNLPInterfacePack_1_1ExampleNLPObjGrad.html</anchorfile>
      <anchor>a19d3045b2cd0e1eb82d9ba99e82aa404</anchor>
      <arglist>(const VectorSpace::space_ptr_t &amp;vec_space, value_type xo, bool has_bounds, bool dep_bounded)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual Range1D</type>
      <name>var_dep</name>
      <anchorfile>classNLPInterfacePack_1_1ExampleNLPObjGrad.html</anchorfile>
      <anchor>a99871334e99f9aed0cfad68bbcbbffec</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual Range1D</type>
      <name>var_indep</name>
      <anchorfile>classNLPInterfacePack_1_1ExampleNLPObjGrad.html</anchorfile>
      <anchor>a7ee8ff09b19353596ddd17721cc55dc7</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initialize</name>
      <anchorfile>classNLPInterfacePack_1_1ExampleNLPObjGrad.html</anchorfile>
      <anchor>a3e98d9df3bd5833c39d6e90196e75cf8</anchor>
      <arglist>(bool test_setup)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>is_initialized</name>
      <anchorfile>classNLPInterfacePack_1_1ExampleNLPObjGrad.html</anchorfile>
      <anchor>ac3b4c2a52cbd845d7250a30d6414abc4</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>size_type</type>
      <name>n</name>
      <anchorfile>classNLPInterfacePack_1_1ExampleNLPObjGrad.html</anchorfile>
      <anchor>a70aa7cb255f8e66689a53c4eae5321f4</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>size_type</type>
      <name>m</name>
      <anchorfile>classNLPInterfacePack_1_1ExampleNLPObjGrad.html</anchorfile>
      <anchor>a84b29c7bf2a5012e20a55a9acd513567</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>vec_space_ptr_t</type>
      <name>space_x</name>
      <anchorfile>classNLPInterfacePack_1_1ExampleNLPObjGrad.html</anchorfile>
      <anchor>abfcdc1f62e808f81967f678fbf4aeb4d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>vec_space_ptr_t</type>
      <name>space_c</name>
      <anchorfile>classNLPInterfacePack_1_1ExampleNLPObjGrad.html</anchorfile>
      <anchor>a2e57723340b79e86a70f4c400a9f9b90</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>size_type</type>
      <name>num_bounded_x</name>
      <anchorfile>classNLPInterfacePack_1_1ExampleNLPObjGrad.html</anchorfile>
      <anchor>a96e637bbeefdc5f23012f39fa8c0babe</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>force_xinit_in_bounds</name>
      <anchorfile>classNLPInterfacePack_1_1ExampleNLPObjGrad.html</anchorfile>
      <anchor>ae06753aa2c7340dc5ffd37379ea8fbcb</anchor>
      <arglist>(bool force_xinit_in_bounds)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>force_xinit_in_bounds</name>
      <anchorfile>classNLPInterfacePack_1_1ExampleNLPObjGrad.html</anchorfile>
      <anchor>aa11e2063ffc421ee2bf9f738fba00bfd</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Vector &amp;</type>
      <name>xinit</name>
      <anchorfile>classNLPInterfacePack_1_1ExampleNLPObjGrad.html</anchorfile>
      <anchor>a347eda7ad32be8158ff14e1135ea9367</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Vector &amp;</type>
      <name>xl</name>
      <anchorfile>classNLPInterfacePack_1_1ExampleNLPObjGrad.html</anchorfile>
      <anchor>a95c3f7c4841096e6c7776c0e570da7b7</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Vector &amp;</type>
      <name>xu</name>
      <anchorfile>classNLPInterfacePack_1_1ExampleNLPObjGrad.html</anchorfile>
      <anchor>a5e1661b65d6c93136574389a731c714b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>value_type</type>
      <name>max_var_bounds_viol</name>
      <anchorfile>classNLPInterfacePack_1_1ExampleNLPObjGrad.html</anchorfile>
      <anchor>a932a73afad91c9526f87ee31e2617858</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>scale_f</name>
      <anchorfile>classNLPInterfacePack_1_1ExampleNLPObjGrad.html</anchorfile>
      <anchor>a68fa4f226b715e08061fbaf2ab20b38a</anchor>
      <arglist>(value_type scale_f)</arglist>
    </member>
    <member kind="function">
      <type>value_type</type>
      <name>scale_f</name>
      <anchorfile>classNLPInterfacePack_1_1ExampleNLPObjGrad.html</anchorfile>
      <anchor>a99bec08c4cb73b446f390a2026e3077c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>report_final_solution</name>
      <anchorfile>classNLPInterfacePack_1_1ExampleNLPObjGrad.html</anchorfile>
      <anchor>a0c528abda00f80ad127d01d80b04bb8f</anchor>
      <arglist>(const Vector &amp;x, const Vector *lambda, const Vector *nu, bool optimal)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>imp_calc_f</name>
      <anchorfile>classNLPInterfacePack_1_1ExampleNLPObjGrad.html</anchorfile>
      <anchor>a45844fb2a6eefcae4a4a6c6f0d86b8ec</anchor>
      <arglist>(const Vector &amp;x, bool newx, const ZeroOrderInfo &amp;zero_order_info) const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>imp_calc_c</name>
      <anchorfile>classNLPInterfacePack_1_1ExampleNLPObjGrad.html</anchorfile>
      <anchor>a7e892cfbf6ea3091b2e6346154dc8739</anchor>
      <arglist>(const Vector &amp;x, bool newx, const ZeroOrderInfo &amp;zero_order_info) const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>imp_calc_h</name>
      <anchorfile>classNLPInterfacePack_1_1ExampleNLPObjGrad.html</anchorfile>
      <anchor>a4b9ec39ed039f9f38771851f3e106550</anchor>
      <arglist>(const Vector &amp;x, bool newx, const ZeroOrderInfo &amp;zero_order_info) const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>imp_calc_Gf</name>
      <anchorfile>classNLPInterfacePack_1_1ExampleNLPObjGrad.html</anchorfile>
      <anchor>a5bc591e9aebf25f3e2072ac33c06f187</anchor>
      <arglist>(const Vector &amp;x, bool newx, const ObjGradInfo &amp;obj_grad_info) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>NLPInterfacePack::ExampleBasisSystem</name>
    <filename>classNLPInterfacePack_1_1ExampleBasisSystem.html</filename>
    <base>AbstractLinAlgPack::BasisSystemComposite</base>
    <member kind="function">
      <type></type>
      <name>ExampleBasisSystem</name>
      <anchorfile>classNLPInterfacePack_1_1ExampleBasisSystem.html</anchorfile>
      <anchor>ad620d30b852b57faffe17a342aa07159</anchor>
      <arglist>(const VectorSpace::space_ptr_t &amp;space_x, const Range1D &amp;var_dep, const Range1D &amp;var_indep)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initialize</name>
      <anchorfile>classNLPInterfacePack_1_1ExampleBasisSystem.html</anchorfile>
      <anchor>a93e604614656ba560f7c3b6dd91c8d9e</anchor>
      <arglist>(const VectorSpace::space_ptr_t &amp;space_x, const Range1D &amp;var_dep, const Range1D &amp;var_indep)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>update_D</name>
      <anchorfile>classNLPInterfacePack_1_1ExampleBasisSystem.html</anchorfile>
      <anchor>ab6551e5109d6244c457f7b7b5f11ebc5</anchor>
      <arglist>(const MatrixOpNonsing &amp;C, const MatrixOp &amp;N, MatrixOp *D, EMatRelations mat_rel) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>NLPInterfacePack::ExampleNLPFirstOrder</name>
    <filename>classNLPInterfacePack_1_1ExampleNLPFirstOrder.html</filename>
    <base virtualness="virtual">NLPInterfacePack::NLPFirstOrder</base>
    <base virtualness="virtual">NLPInterfacePack::ExampleNLPObjGrad</base>
    <member kind="function">
      <type></type>
      <name>ExampleNLPFirstOrder</name>
      <anchorfile>classNLPInterfacePack_1_1ExampleNLPFirstOrder.html</anchorfile>
      <anchor>aba65e991d1dbd42f12c176e4f2b175bd</anchor>
      <arglist>(const VectorSpace::space_ptr_t &amp;vec_space, value_type xo, bool has_bounds, bool dep_bounded)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initialize</name>
      <anchorfile>classNLPInterfacePack_1_1ExampleNLPFirstOrder.html</anchorfile>
      <anchor>aabf2d0e835ad287be44e77376ff25ee1</anchor>
      <arglist>(bool test_setup)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>is_initialized</name>
      <anchorfile>classNLPInterfacePack_1_1ExampleNLPFirstOrder.html</anchorfile>
      <anchor>a497bf1eea83ab71f19f71a9553a46ba6</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_Gc</name>
      <anchorfile>classNLPInterfacePack_1_1ExampleNLPFirstOrder.html</anchorfile>
      <anchor>a86ec632e22dea34f1b23698c1af8a78c</anchor>
      <arglist>(MatrixOp *Gc)</arglist>
    </member>
    <member kind="function">
      <type>const NLPFirstOrder::mat_fcty_ptr_t</type>
      <name>factory_Gc</name>
      <anchorfile>classNLPInterfacePack_1_1ExampleNLPFirstOrder.html</anchorfile>
      <anchor>aaab0e2d583d1349bd7803b840a0512d7</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const basis_sys_ptr_t</type>
      <name>basis_sys</name>
      <anchorfile>classNLPInterfacePack_1_1ExampleNLPFirstOrder.html</anchorfile>
      <anchor>ae5dbc7ece804a0a091c3f45b56293668</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>imp_calc_Gc</name>
      <anchorfile>classNLPInterfacePack_1_1ExampleNLPFirstOrder.html</anchorfile>
      <anchor>ae4da9a582748dc46354a090a0dea8bb6</anchor>
      <arglist>(const Vector &amp;x, bool newx, const FirstOrderInfo &amp;first_order_info) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>NLPInterfacePack::NLPWBCounterExample</name>
    <filename>classNLPInterfacePack_1_1NLPWBCounterExample.html</filename>
    <base>NLPInterfacePack::NLPSerialPreprocessExplJac</base>
    <member kind="function">
      <type></type>
      <name>NLPWBCounterExample</name>
      <anchorfile>classNLPInterfacePack_1_1NLPWBCounterExample.html</anchorfile>
      <anchor>a050b540720fd63d250c6dd5a4c43945d</anchor>
      <arglist>(value_type xinit[3], value_type a=0.0, value_type b=1.0, bool nlp_selects_basis=true, bool linear_obj=true)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initialize</name>
      <anchorfile>classNLPInterfacePack_1_1NLPWBCounterExample.html</anchorfile>
      <anchor>a9e947fe408aea7c128aa6c9edd56dd45</anchor>
      <arglist>(bool test_setup)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>is_initialized</name>
      <anchorfile>classNLPInterfacePack_1_1NLPWBCounterExample.html</anchorfile>
      <anchor>a4e3e59338ab1fd2755c0bf1e28036d00</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>value_type</type>
      <name>max_var_bounds_viol</name>
      <anchorfile>classNLPInterfacePack_1_1NLPWBCounterExample.html</anchorfile>
      <anchor>a6a21e6700ed8028bcab6c4d91943daf7</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>nlp_selects_basis</name>
      <anchorfile>classNLPInterfacePack_1_1NLPWBCounterExample.html</anchorfile>
      <anchor>a2979264295c3e97e0bc3ae9d21da6de0</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>bool</type>
      <name>imp_nlp_has_changed</name>
      <anchorfile>classNLPInterfacePack_1_1NLPWBCounterExample.html</anchorfile>
      <anchor>ada8c7874675ce893ae4c5aa1b22d2530</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>size_type</type>
      <name>imp_n_orig</name>
      <anchorfile>classNLPInterfacePack_1_1NLPWBCounterExample.html</anchorfile>
      <anchor>a1ab112fc2cd5ec92d220cb2ca656d8a0</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>size_type</type>
      <name>imp_m_orig</name>
      <anchorfile>classNLPInterfacePack_1_1NLPWBCounterExample.html</anchorfile>
      <anchor>a5b2b51a9f863cb7b87a3d56b022e8b35</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>size_type</type>
      <name>imp_mI_orig</name>
      <anchorfile>classNLPInterfacePack_1_1NLPWBCounterExample.html</anchorfile>
      <anchor>a10ceaa5a8f0219614812258c26508ada</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>const DVectorSlice</type>
      <name>imp_xinit_orig</name>
      <anchorfile>classNLPInterfacePack_1_1NLPWBCounterExample.html</anchorfile>
      <anchor>a4ef50d072754a3055fca5ae8178b7c81</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>bool</type>
      <name>imp_has_var_bounds</name>
      <anchorfile>classNLPInterfacePack_1_1NLPWBCounterExample.html</anchorfile>
      <anchor>a496103c171cf55dc35bf4b4ff2b7a6a5</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>const DVectorSlice</type>
      <name>imp_xl_orig</name>
      <anchorfile>classNLPInterfacePack_1_1NLPWBCounterExample.html</anchorfile>
      <anchor>a0034731f250e98b7fa18196944107982</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>const DVectorSlice</type>
      <name>imp_xu_orig</name>
      <anchorfile>classNLPInterfacePack_1_1NLPWBCounterExample.html</anchorfile>
      <anchor>afd7d3366ca85424a3b7ac8caff4677fd</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>const DVectorSlice</type>
      <name>imp_hl_orig</name>
      <anchorfile>classNLPInterfacePack_1_1NLPWBCounterExample.html</anchorfile>
      <anchor>ad447e6e570296284345e95bbf93f8ae7</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>const DVectorSlice</type>
      <name>imp_hu_orig</name>
      <anchorfile>classNLPInterfacePack_1_1NLPWBCounterExample.html</anchorfile>
      <anchor>a940bc2c6a1f8b6da993c4ef14273af07</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>imp_calc_f_orig</name>
      <anchorfile>classNLPInterfacePack_1_1NLPWBCounterExample.html</anchorfile>
      <anchor>aa1df137a4fdef08a50e70559689a33a2</anchor>
      <arglist>(const DVectorSlice &amp;x_full, bool newx, const ZeroOrderInfoSerial &amp;zero_order_info) const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>imp_calc_c_orig</name>
      <anchorfile>classNLPInterfacePack_1_1NLPWBCounterExample.html</anchorfile>
      <anchor>aec696c9ab89252f2cdddf227ecb2404c</anchor>
      <arglist>(const DVectorSlice &amp;x_full, bool newx, const ZeroOrderInfoSerial &amp;zero_order_info) const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>imp_calc_h_orig</name>
      <anchorfile>classNLPInterfacePack_1_1NLPWBCounterExample.html</anchorfile>
      <anchor>a90fa5bbe3bb86a6146b3b4e86fa242f5</anchor>
      <arglist>(const DVectorSlice &amp;x_full, bool newx, const ZeroOrderInfoSerial &amp;zero_order_info) const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>imp_calc_Gf_orig</name>
      <anchorfile>classNLPInterfacePack_1_1NLPWBCounterExample.html</anchorfile>
      <anchor>ae3b3769d4389a065e4251e65f1d92355</anchor>
      <arglist>(const DVectorSlice &amp;x_full, bool newx, const ObjGradInfoSerial &amp;obj_grad_info) const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>bool</type>
      <name>imp_get_next_basis</name>
      <anchorfile>classNLPInterfacePack_1_1NLPWBCounterExample.html</anchorfile>
      <anchor>aa9a686871b1e35e4ea2fb644f3c7a95c</anchor>
      <arglist>(IVector *var_perm_full, IVector *equ_perm_full, size_type *rank_full, size_type *rank)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>imp_report_orig_final_solution</name>
      <anchorfile>classNLPInterfacePack_1_1NLPWBCounterExample.html</anchorfile>
      <anchor>ab5ac72695f97db1316c54d29a835dfca</anchor>
      <arglist>(const DVectorSlice &amp;x_orig, const DVectorSlice *lambda_orig, const DVectorSlice *lambdaI_orig, const DVectorSlice *nu_orig, bool is_optimal) const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>size_type</type>
      <name>imp_Gc_nz_orig</name>
      <anchorfile>classNLPInterfacePack_1_1NLPWBCounterExample.html</anchorfile>
      <anchor>afe731b7bf26aa1497f662e99b6766013</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>size_type</type>
      <name>imp_Gh_nz_orig</name>
      <anchorfile>classNLPInterfacePack_1_1NLPWBCounterExample.html</anchorfile>
      <anchor>a934b1af254ec0beae4d43f096d96cbd7</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>imp_calc_Gc_orig</name>
      <anchorfile>classNLPInterfacePack_1_1NLPWBCounterExample.html</anchorfile>
      <anchor>a103b06a0d0adb2cd8bdf9b306efe7c39</anchor>
      <arglist>(const DVectorSlice &amp;x_full, bool newx, const FirstOrderExplInfo &amp;first_order_expl_info) const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>imp_calc_Gh_orig</name>
      <anchorfile>classNLPInterfacePack_1_1NLPWBCounterExample.html</anchorfile>
      <anchor>a425b8cafcf18664fb56ee1a561f39f9d</anchor>
      <arglist>(const DVectorSlice &amp;x_full, bool newx, const FirstOrderExplInfo &amp;first_order_expl_info) const </arglist>
    </member>
  </compound>
  <compound kind="dir">
    <name>http://trilinos.sandia.gov/packages/docs/r10.6/packages/moocho/thyra/example/DiagonalQuadraticResponseOnlyOpt/</name>
    <path>http://trilinos.sandia.gov/packages/docs/r10.6/packages/moocho/thyra/example/DiagonalQuadraticResponseOnlyOpt/</path>
    <filename>dir_48fcb77385309b7a2398800a7ce15dd0.html</filename>
    <file>EpetraExtDiagonalQuadraticResponseOnlyOptMain.cpp</file>
    <file>ThyraDiagonalQuadraticResponseOnlyOptMain.cpp</file>
  </compound>
  <compound kind="dir">
    <name>http://trilinos.sandia.gov/packages/docs/r10.6/packages/moocho/thyra/example/DiagonalTransientInversion/</name>
    <path>http://trilinos.sandia.gov/packages/docs/r10.6/packages/moocho/thyra/example/DiagonalTransientInversion/</path>
    <filename>dir_8dbd5edda6d693ed24ef15e2f968cf52.html</filename>
    <file>DiagonalTransientInversionMain.cpp</file>
  </compound>
  <compound kind="dir">
    <name>http://trilinos.sandia.gov/packages/docs/r10.6/packages/moocho/thyra/example/</name>
    <path>http://trilinos.sandia.gov/packages/docs/r10.6/packages/moocho/thyra/example/</path>
    <filename>dir_ff185e0ce61fba1f1954545413d94bf0.html</filename>
    <dir>http://trilinos.sandia.gov/packages/docs/r10.6/packages/moocho/thyra/example/DiagonalQuadraticResponseOnlyOpt/</dir>
    <dir>http://trilinos.sandia.gov/packages/docs/r10.6/packages/moocho/thyra/example/DiagonalTransientInversion/</dir>
    <dir>http://trilinos.sandia.gov/packages/docs/r10.6/packages/moocho/thyra/example/NLPThyraEpetraAdvDiffReactOpt/</dir>
    <dir>http://trilinos.sandia.gov/packages/docs/r10.6/packages/moocho/thyra/example/NLPThyraEpetraModelEval4DOpt/</dir>
  </compound>
  <compound kind="dir">
    <name>http://trilinos.sandia.gov/packages/docs/r10.6/packages/moocho/example/</name>
    <path>http://trilinos.sandia.gov/packages/docs/r10.6/packages/moocho/example/</path>
    <filename>dir_76e8b15f8d255ba86ab9f8aa544d3827.html</filename>
    <dir>http://trilinos.sandia.gov/packages/docs/r10.6/packages/moocho/example/ExampleNLPBanded/</dir>
    <dir>http://trilinos.sandia.gov/packages/docs/r10.6/packages/moocho/example/ExampleNLPDirect/</dir>
    <dir>http://trilinos.sandia.gov/packages/docs/r10.6/packages/moocho/example/ExampleNLPFirstOrder/</dir>
    <dir>http://trilinos.sandia.gov/packages/docs/r10.6/packages/moocho/example/NLPWBCounterExample/</dir>
  </compound>
  <compound kind="dir">
    <name>http://trilinos.sandia.gov/packages/docs/r10.6/packages/moocho/example/ExampleNLPBanded/</name>
    <path>http://trilinos.sandia.gov/packages/docs/r10.6/packages/moocho/example/ExampleNLPBanded/</path>
    <filename>dir_798f2231ce51cdc0b5d9ab4ae5670de9.html</filename>
    <file>ExampleNLPBandedMain.cpp</file>
    <file>NLPInterfacePack_ExampleNLPBanded.cpp</file>
    <file>NLPInterfacePack_ExampleNLPBanded.hpp</file>
  </compound>
  <compound kind="dir">
    <name>http://trilinos.sandia.gov/packages/docs/r10.6/packages/moocho/example/ExampleNLPDirect/</name>
    <path>http://trilinos.sandia.gov/packages/docs/r10.6/packages/moocho/example/ExampleNLPDirect/</path>
    <filename>dir_d4f7be19105cceb1949fa848c2366439.html</filename>
    <file>AbstractLinAlgPack_exampleNLPDiagSetup.cpp</file>
    <file>AbstractLinAlgPack_exampleNLPDiagSetup.hpp</file>
    <file>ExampleNLPDirectMain.cpp</file>
    <file>ExampleNLPDirectRTOps.c</file>
    <file>ExampleNLPDirectRTOps.h</file>
    <file>NLPInterfacePack_ExampleNLPDirect.cpp</file>
    <file>NLPInterfacePack_ExampleNLPDirect.hpp</file>
    <file>NLPInterfacePack_ExampleNLPDirectRun.cpp</file>
    <file>NLPInterfacePack_ExampleNLPDirectRun.hpp</file>
    <file>NLPInterfacePack_ExampleNLPObjGrad.cpp</file>
    <file>NLPInterfacePack_ExampleNLPObjGrad.hpp</file>
  </compound>
  <compound kind="dir">
    <name>http://trilinos.sandia.gov/packages/docs/r10.6/packages/moocho/example/ExampleNLPFirstOrder/</name>
    <path>http://trilinos.sandia.gov/packages/docs/r10.6/packages/moocho/example/ExampleNLPFirstOrder/</path>
    <filename>dir_d9b263e613b5140c6a0878cb79ceb026.html</filename>
    <file>ExampleNLPFirstOrderMain.cpp</file>
    <file>NLPInterfacePack_ExampleBasisSystem.cpp</file>
    <file>NLPInterfacePack_ExampleBasisSystem.hpp</file>
    <file>NLPInterfacePack_ExampleNLPFirstOrder.cpp</file>
    <file>NLPInterfacePack_ExampleNLPFirstOrder.hpp</file>
    <file>NLPInterfacePack_ExampleNLPFirstOrderRun.cpp</file>
    <file>NLPInterfacePack_ExampleNLPFirstOrderRun.hpp</file>
  </compound>
  <compound kind="dir">
    <name>http://trilinos.sandia.gov/packages/docs/r10.6/packages/moocho/thyra/example/NLPThyraEpetraAdvDiffReactOpt/</name>
    <path>http://trilinos.sandia.gov/packages/docs/r10.6/packages/moocho/thyra/example/NLPThyraEpetraAdvDiffReactOpt/</path>
    <filename>dir_1b5f6666e902c89e6f9385d8eb9a66c4.html</filename>
    <file>MultiPeriodNLPThyraEpetraAdvDiffReactOptMain.cpp</file>
    <file>NLPThyraEpetraAdvDiffReactOptMain.cpp</file>
  </compound>
  <compound kind="dir">
    <name>http://trilinos.sandia.gov/packages/docs/r10.6/packages/moocho/thyra/example/NLPThyraEpetraModelEval4DOpt/</name>
    <path>http://trilinos.sandia.gov/packages/docs/r10.6/packages/moocho/thyra/example/NLPThyraEpetraModelEval4DOpt/</path>
    <filename>dir_3aac9df3e91f2c5ee3d2a5a7b25d1dd5.html</filename>
    <file>NLPThyraEpetraModelEval4DOptMain.cpp</file>
    <file>NLPThyraEpetraMultiPointModelEval4DOptMain.cpp</file>
  </compound>
  <compound kind="dir">
    <name>http://trilinos.sandia.gov/packages/docs/r10.6/packages/moocho/example/NLPWBCounterExample/</name>
    <path>http://trilinos.sandia.gov/packages/docs/r10.6/packages/moocho/example/NLPWBCounterExample/</path>
    <filename>dir_0192bbf30974ae60100c67fd67d2884f.html</filename>
    <file>NLPInterfacePack_NLPWBCounterExample.cpp</file>
    <file>NLPInterfacePack_NLPWBCounterExample.hpp</file>
    <file>NLPWBCounterExampleMain.cpp</file>
  </compound>
  <compound kind="dir">
    <name>http://trilinos.sandia.gov/packages/docs/r10.6/packages/moocho/thyra/</name>
    <path>http://trilinos.sandia.gov/packages/docs/r10.6/packages/moocho/thyra/</path>
    <filename>dir_adae6de920a6cf5c1e938de80824eb04.html</filename>
    <dir>http://trilinos.sandia.gov/packages/docs/r10.6/packages/moocho/thyra/example/</dir>
  </compound>
</tagfile>
