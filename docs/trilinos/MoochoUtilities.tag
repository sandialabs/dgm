<?xml version='1.0' encoding='UTF-8' standalone='yes' ?>
<tagfile>
  <compound kind="group">
    <name>BLAS_Cpp_grp</name>
    <title>Basic C++/Fortran BLAS declarations/utilities.</title>
    <filename>group__BLAS__Cpp__grp.html</filename>
    <subgroup>BLAS_Cpp_grp_enums</subgroup>
    <subgroup>BLAS_Cpp_grp_helper</subgroup>
    <member kind="typedef">
      <type>size_t</type>
      <name>size_type</name>
      <anchorfile>group__BLAS__Cpp__grp.html</anchorfile>
      <anchor>ga44fc680243ce4a9ded30f06aba64596f</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>BLAS_Cpp_grp_enums</name>
    <title>BLAS Enumerations</title>
    <filename>group__BLAS__Cpp__grp__enums.html</filename>
    <member kind="enumeration">
      <name>Side</name>
      <anchorfile>group__BLAS__Cpp__grp__enums.html</anchorfile>
      <anchor>gaa0d0f7ec2d0493dc6b25614b3dbc6dea</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>Transp</name>
      <anchorfile>group__BLAS__Cpp__grp__enums.html</anchorfile>
      <anchor>gae8e89b5749b1c3c3b12fef664609e8b5</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>no_trans</name>
      <anchorfile>group__BLAS__Cpp__grp__enums.html</anchorfile>
      <anchor>ggae8e89b5749b1c3c3b12fef664609e8b5ab3630c82ed783feaa30e0450c2e00ac2</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>trans</name>
      <anchorfile>group__BLAS__Cpp__grp__enums.html</anchorfile>
      <anchor>ggae8e89b5749b1c3c3b12fef664609e8b5a8d106be97f486609e990116452b96fbe</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>conj_trans</name>
      <anchorfile>group__BLAS__Cpp__grp__enums.html</anchorfile>
      <anchor>ggae8e89b5749b1c3c3b12fef664609e8b5a115de6232e3cf0b3c27a4055768bc74e</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>Uplo</name>
      <anchorfile>group__BLAS__Cpp__grp__enums.html</anchorfile>
      <anchor>ga767d668d03e8037536d8f70644fa98ac</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>Diag</name>
      <anchorfile>group__BLAS__Cpp__grp__enums.html</anchorfile>
      <anchor>ga1dd43ae184bcc787099fcfce6647b852</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>Uplo</type>
      <name>operator!</name>
      <anchorfile>group__BLAS__Cpp__grp__enums.html</anchorfile>
      <anchor>ga37b283b5dbed1cda35e04e56bb44a61f</anchor>
      <arglist>(Uplo uplo)</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>BLAS_Cpp_grp_helper</name>
    <title>Helper functions</title>
    <filename>group__BLAS__Cpp__grp__helper.html</filename>
    <member kind="function">
      <type>Transp</type>
      <name>bool_to_trans</name>
      <anchorfile>group__BLAS__Cpp__grp__helper.html</anchorfile>
      <anchor>ga278982a93b6f454688efe6595d789d42</anchor>
      <arglist>(bool return_trans)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>trans_to_bool</name>
      <anchorfile>group__BLAS__Cpp__grp__helper.html</anchorfile>
      <anchor>ga2c8850fa865c52f0fbca3d93a7e93c92</anchor>
      <arglist>(Transp _trans)</arglist>
    </member>
    <member kind="function">
      <type>Transp</type>
      <name>operator!</name>
      <anchorfile>group__BLAS__Cpp__grp__helper.html</anchorfile>
      <anchor>gabfb26cf76a4beb5f28ef8b7f680cd923</anchor>
      <arglist>(Transp _trans)</arglist>
    </member>
    <member kind="function">
      <type>Transp</type>
      <name>trans_not</name>
      <anchorfile>group__BLAS__Cpp__grp__helper.html</anchorfile>
      <anchor>ga1323fc9380580beaeb133e6768daf3a6</anchor>
      <arglist>(Transp _trans)</arglist>
    </member>
    <member kind="function">
      <type>Transp</type>
      <name>trans_trans</name>
      <anchorfile>group__BLAS__Cpp__grp__helper.html</anchorfile>
      <anchor>ga00c850ad6061e8a6ca1318da426b846e</anchor>
      <arglist>(Transp _trans1, Transp _trans2)</arglist>
    </member>
    <member kind="function">
      <type>const char *</type>
      <name>trans_to_string</name>
      <anchorfile>group__BLAS__Cpp__grp__helper.html</anchorfile>
      <anchor>ga16227afc891d67442cec88022e0eab62</anchor>
      <arglist>(Transp _trans)</arglist>
    </member>
    <member kind="function">
      <type>size_type</type>
      <name>rows</name>
      <anchorfile>group__BLAS__Cpp__grp__helper.html</anchorfile>
      <anchor>gad269ae964111d322c40509b07ee65cd0</anchor>
      <arglist>(size_type rows, size_type cols, BLAS_Cpp::Transp _trans)</arglist>
    </member>
    <member kind="function">
      <type>size_type</type>
      <name>cols</name>
      <anchorfile>group__BLAS__Cpp__grp__helper.html</anchorfile>
      <anchor>gae4d0a5ec8c7c7190871c48e529796c08</anchor>
      <arglist>(size_type rows, size_type cols, BLAS_Cpp::Transp _trans)</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>OptionsFromStreamExceptions</name>
    <title>Exception classes.</title>
    <filename>group__OptionsFromStreamExceptions.html</filename>
    <class kind="class">OptionsFromStreamPack::InputException</class>
    <class kind="class">OptionsFromStreamPack::AccessException</class>
  </compound>
  <compound kind="group">
    <name>ProfileHackPack_grp</name>
    <title>Poor-mans profiling helper tools.</title>
    <filename>group__ProfileHackPack__grp.html</filename>
    <class kind="class">ProfileHackPack::ProfileTiming</class>
    <member kind="function">
      <type>void</type>
      <name>set_time</name>
      <anchorfile>group__ProfileHackPack__grp.html</anchorfile>
      <anchor>gaec64ec4096515674203bde1dfbe41896</anchor>
      <arglist>(const char func_name[], double time_secs)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>print_timings</name>
      <anchorfile>group__ProfileHackPack__grp.html</anchorfile>
      <anchor>ga624d4654e7ae0084a1c0dfbdb3c8705a</anchor>
      <arglist>(std::ostream &amp;out)</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>StandardAggregationMacros_grp</name>
    <title>Macros that add &lt;&lt;std aggr&gt;&gt; members for an association.</title>
    <filename>group__StandardAggregationMacros__grp.html</filename>
    <member kind="define">
      <type>#define</type>
      <name>STANDARD_AGGREGATION_MEMBERS</name>
      <anchorfile>group__StandardAggregationMacros__grp.html</anchorfile>
      <anchor>gac32f81eecd6a7632d46c917bea84211a</anchor>
      <arglist>(TYPE, NAME)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>STANDARD_CONST_AGGREGATION_MEMBERS</name>
      <anchorfile>group__StandardAggregationMacros__grp.html</anchorfile>
      <anchor>ga634c490c814994582da0ffd765248c09</anchor>
      <arglist>(TYPE, NAME)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>FortranTypes::InvalidFileNameException</name>
    <filename>classFortranTypes_1_1InvalidFileNameException.html</filename>
  </compound>
  <compound kind="class">
    <name>FortranTypes::OpenException</name>
    <filename>classFortranTypes_1_1OpenException.html</filename>
  </compound>
  <compound kind="class">
    <name>MemMngPack::ReleaseResource</name>
    <filename>classMemMngPack_1_1ReleaseResource.html</filename>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~ReleaseResource</name>
      <anchorfile>classMemMngPack_1_1ReleaseResource.html</anchorfile>
      <anchor>aa5211a61b7c5f7012ec34546dfb2c925</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>resource_is_bound</name>
      <anchorfile>classMemMngPack_1_1ReleaseResource.html</anchorfile>
      <anchor>a82584935deb0d21819c96cc60798e1cd</anchor>
      <arglist>() const =0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>MemMngPack::ReleaseResource_ref_count_ptr</name>
    <filename>classMemMngPack_1_1ReleaseResource__ref__count__ptr.html</filename>
    <templarg></templarg>
    <base>MemMngPack::ReleaseResource</base>
    <member kind="typedef">
      <type>Teuchos::RCP&lt; T &gt;</type>
      <name>ptr_t</name>
      <anchorfile>classMemMngPack_1_1ReleaseResource__ref__count__ptr.html</anchorfile>
      <anchor>af680296397d9b42078ed31d61d0893d5</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ReleaseResource_ref_count_ptr</name>
      <anchorfile>classMemMngPack_1_1ReleaseResource__ref__count__ptr.html</anchorfile>
      <anchor>aa41e0c1a0cc27157b18b8b82acaeb645</anchor>
      <arglist>(const ptr_t &amp;ptr)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>resource_is_bound</name>
      <anchorfile>classMemMngPack_1_1ReleaseResource__ref__count__ptr.html</anchorfile>
      <anchor>a9ca0b6b600ba6146c3231a16ecc5dc2b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~ReleaseResource</name>
      <anchorfile>classMemMngPack_1_1ReleaseResource.html</anchorfile>
      <anchor>aa5211a61b7c5f7012ec34546dfb2c925</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable">
      <type>ptr_t</type>
      <name>ptr</name>
      <anchorfile>classMemMngPack_1_1ReleaseResource__ref__count__ptr.html</anchorfile>
      <anchor>af49c4628034ab523bde7b27afdcafc6b</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>OptionsFromStreamPack::CommandLineOptionsFromStreamProcessor</name>
    <filename>classOptionsFromStreamPack_1_1CommandLineOptionsFromStreamProcessor.html</filename>
    <member kind="function">
      <type></type>
      <name>CommandLineOptionsFromStreamProcessor</name>
      <anchorfile>classOptionsFromStreamPack_1_1CommandLineOptionsFromStreamProcessor.html</anchorfile>
      <anchor>affc2a2cb9bf21b33f9b1595235264f0e</anchor>
      <arglist>(const std::string &amp;options_file_name_opt_name=&quot;ofs-options-file&quot;, const std::string &amp;options_file_name_opt_doc=&quot;The name of the file containing input options for OptionsFromStream object.&quot;, const std::string &amp;options_file_name=&quot;&quot;, const std::string &amp;extra_options_str_opt_name=&quot;ofs-extra-options&quot;, const std::string &amp;extra_options_str_opt_doc=&quot;Extra options in format \&quot;OptGrp1{name1=val1,...,namen=valn}:OptGr2{name1=val1,...,namen=valn}:...\&quot;&quot;, const std::string &amp;extra_options_str=&quot;&quot;)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_options</name>
      <anchorfile>classOptionsFromStreamPack_1_1CommandLineOptionsFromStreamProcessor.html</anchorfile>
      <anchor>a07839b46a2f9fe739baac4c7c8acb61e</anchor>
      <arglist>(Teuchos::RCP&lt; OptionsFromStream &gt; const &amp;options)</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; OptionsFromStream &gt;</type>
      <name>get_options</name>
      <anchorfile>classOptionsFromStreamPack_1_1CommandLineOptionsFromStreamProcessor.html</anchorfile>
      <anchor>a7b78dd6ce6d8f901efb52c2e0558e5b1</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classOptionsFromStreamPack_1_1CommandLineOptionsFromStreamProcessor.html</anchorfile>
      <anchor>a8280f7cf2877a5bfdd9cbc651ce7acbd</anchor>
      <arglist>(std::string, options_file_name_opt_name)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classOptionsFromStreamPack_1_1CommandLineOptionsFromStreamProcessor.html</anchorfile>
      <anchor>acf2ba2cb998d50a099dfe5ad64aa9f4f</anchor>
      <arglist>(std::string, options_file_name_opt_doc)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classOptionsFromStreamPack_1_1CommandLineOptionsFromStreamProcessor.html</anchorfile>
      <anchor>ae9a79c7e1a6c699872db2c695b37839b</anchor>
      <arglist>(std::string, options_file_name)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classOptionsFromStreamPack_1_1CommandLineOptionsFromStreamProcessor.html</anchorfile>
      <anchor>a3412db8b19a62805257d1b791b8260aa</anchor>
      <arglist>(std::string, extra_options_str_opt_name)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classOptionsFromStreamPack_1_1CommandLineOptionsFromStreamProcessor.html</anchorfile>
      <anchor>a84d2954ccd1147f1ac813d2e6f4e0480</anchor>
      <arglist>(std::string, extra_options_str_opt_doc)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classOptionsFromStreamPack_1_1CommandLineOptionsFromStreamProcessor.html</anchorfile>
      <anchor>a4b83ff26263fb756346088fbee5e0766</anchor>
      <arglist>(std::string, extra_options_str)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setup_commandline_processor</name>
      <anchorfile>classOptionsFromStreamPack_1_1CommandLineOptionsFromStreamProcessor.html</anchorfile>
      <anchor>ac6018bfc8ca32fdab463f529811c8064</anchor>
      <arglist>(Teuchos::CommandLineProcessor *clp)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>process_options</name>
      <anchorfile>classOptionsFromStreamPack_1_1CommandLineOptionsFromStreamProcessor.html</anchorfile>
      <anchor>aa949637c57445b75fe23eb273965f507</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; OptionsFromStream &gt;</type>
      <name>process_and_get_options</name>
      <anchorfile>classOptionsFromStreamPack_1_1CommandLineOptionsFromStreamProcessor.html</anchorfile>
      <anchor>abd93c16d51b80bbacb0abb377d8cf4de</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>OptionsFromStreamPack::OptionsFromStream</name>
    <filename>classOptionsFromStreamPack_1_1OptionsFromStream.html</filename>
    <class kind="class">OptionsFromStreamPack::OptionsFromStream::InputStreamError</class>
    <member kind="function">
      <type>void</type>
      <name>print_options</name>
      <anchorfile>classOptionsFromStreamPack_1_1OptionsFromStream.html</anchorfile>
      <anchor>ab7aca84b40a1943c78bdc6da5725447c</anchor>
      <arglist>(std::ostream &amp;out) const </arglist>
    </member>
    <member kind="function" static="yes">
      <type>static bool</type>
      <name>options_group_exists</name>
      <anchorfile>classOptionsFromStreamPack_1_1OptionsFromStream.html</anchorfile>
      <anchor>adf6520f0a6b70022e1f0659f61103e8b</anchor>
      <arglist>(const options_group_t &amp;options_group)</arglist>
    </member>
    <member kind="typedef">
      <type>OptionsFromStreamUtilityPack::options_group_map_t::iterator</type>
      <name>iterator</name>
      <anchorfile>classOptionsFromStreamPack_1_1OptionsFromStream.html</anchorfile>
      <anchor>a3c4992518d116c15f7ff758892687183</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>OptionsFromStreamUtilityPack::options_group_map_t::const_iterator</type>
      <name>const_iterator</name>
      <anchorfile>classOptionsFromStreamPack_1_1OptionsFromStream.html</anchorfile>
      <anchor>a162a4d940cd595af6b136617b78ca692</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>OptionsFromStreamUtilityPack::OptionsGroup</type>
      <name>options_group_t</name>
      <anchorfile>classOptionsFromStreamPack_1_1OptionsFromStream.html</anchorfile>
      <anchor>a5c372e52a6b8705e14c0d4920688cf91</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>OptionsFromStream</name>
      <anchorfile>classOptionsFromStreamPack_1_1OptionsFromStream.html</anchorfile>
      <anchor>ad8fcf8e796e17c92ddb5c9122ebb5e56</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>OptionsFromStream</name>
      <anchorfile>classOptionsFromStreamPack_1_1OptionsFromStream.html</anchorfile>
      <anchor>afc1b85eb22992ad96dd657d9f1f8f7c8</anchor>
      <arglist>(std::istream &amp;in)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>clear_options</name>
      <anchorfile>classOptionsFromStreamPack_1_1OptionsFromStream.html</anchorfile>
      <anchor>a25a03723dd9647b677e93c2957f4ee3e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>read_options</name>
      <anchorfile>classOptionsFromStreamPack_1_1OptionsFromStream.html</anchorfile>
      <anchor>adc0a545495a2f13039d4130c84081b8d</anchor>
      <arglist>(std::istream &amp;in)</arglist>
    </member>
    <member kind="function">
      <type>options_group_t</type>
      <name>options_group</name>
      <anchorfile>classOptionsFromStreamPack_1_1OptionsFromStream.html</anchorfile>
      <anchor>aa1a8790d0692795f207114091606a56b</anchor>
      <arglist>(const std::string &amp;options_group_name)</arglist>
    </member>
    <member kind="function">
      <type>const options_group_t</type>
      <name>options_group</name>
      <anchorfile>classOptionsFromStreamPack_1_1OptionsFromStream.html</anchorfile>
      <anchor>acc76f33e5e642fe13fcff760415360e2</anchor>
      <arglist>(const std::string &amp;options_group_name) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>reset_unaccessed_options_groups</name>
      <anchorfile>classOptionsFromStreamPack_1_1OptionsFromStream.html</anchorfile>
      <anchor>a0f9f3317f664b566bcf1eb6c9354f4b0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>print_unaccessed_options_groups</name>
      <anchorfile>classOptionsFromStreamPack_1_1OptionsFromStream.html</anchorfile>
      <anchor>a0f5add9018999a421d83ffebcee587f2</anchor>
      <arglist>(std::ostream &amp;out) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>num_options_groups</name>
      <anchorfile>classOptionsFromStreamPack_1_1OptionsFromStream.html</anchorfile>
      <anchor>a4c5524577c9be4b53da2e9e60a6ee888</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>iterator</type>
      <name>begin</name>
      <anchorfile>classOptionsFromStreamPack_1_1OptionsFromStream.html</anchorfile>
      <anchor>a4e15557f4c330baca7029095ca59418a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>iterator</type>
      <name>end</name>
      <anchorfile>classOptionsFromStreamPack_1_1OptionsFromStream.html</anchorfile>
      <anchor>ab80d32490dacd294dc8530ebbfa5a19c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const_iterator</type>
      <name>begin</name>
      <anchorfile>classOptionsFromStreamPack_1_1OptionsFromStream.html</anchorfile>
      <anchor>aec73f0637c541a78db3f11bc4f28a15f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const_iterator</type>
      <name>end</name>
      <anchorfile>classOptionsFromStreamPack_1_1OptionsFromStream.html</anchorfile>
      <anchor>ae35c038f1a0466843aad3c38dd6d7461</anchor>
      <arglist>() const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>OptionsFromStreamPack::OptionsFromStream::InputStreamError</name>
    <filename>classOptionsFromStreamPack_1_1OptionsFromStream_1_1InputStreamError.html</filename>
  </compound>
  <compound kind="class">
    <name>OptionsFromStreamPack::InputException</name>
    <filename>classOptionsFromStreamPack_1_1InputException.html</filename>
  </compound>
  <compound kind="class">
    <name>OptionsFromStreamPack::AccessException</name>
    <filename>classOptionsFromStreamPack_1_1AccessException.html</filename>
  </compound>
  <compound kind="class">
    <name>OptionsFromStreamPack::SetOptionsFromStream</name>
    <filename>classOptionsFromStreamPack_1_1SetOptionsFromStream.html</filename>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~SetOptionsFromStream</name>
      <anchorfile>classOptionsFromStreamPack_1_1SetOptionsFromStream.html</anchorfile>
      <anchor>ab17d24f0392283758f90523c96683c0e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>set_options</name>
      <anchorfile>classOptionsFromStreamPack_1_1SetOptionsFromStream.html</anchorfile>
      <anchor>ada3b907aa528022c2446ffd0f713815b</anchor>
      <arglist>(const OptionsFromStream &amp;options)=0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>OptionsFromStreamPack::SetOptionsFromStreamNode</name>
    <filename>classOptionsFromStreamPack_1_1SetOptionsFromStreamNode.html</filename>
    <base>OptionsFromStreamPack::SetOptionsFromStream</base>
    <member kind="function">
      <type></type>
      <name>SetOptionsFromStreamNode</name>
      <anchorfile>classOptionsFromStreamPack_1_1SetOptionsFromStreamNode.html</anchorfile>
      <anchor>ab76afd498ed4b530a310d3dd8aea3cde</anchor>
      <arglist>(const std::string &amp;options_group, int num_options, const char *option_names[], bool exists_optional=true)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_options</name>
      <anchorfile>classOptionsFromStreamPack_1_1SetOptionsFromStreamNode.html</anchorfile>
      <anchor>aab309dbaaa9053245e58620a0627f303</anchor>
      <arglist>(const OptionsFromStream &amp;options)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~SetOptionsFromStream</name>
      <anchorfile>classOptionsFromStreamPack_1_1SetOptionsFromStream.html</anchorfile>
      <anchor>ab17d24f0392283758f90523c96683c0e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual void</type>
      <name>setOption</name>
      <anchorfile>classOptionsFromStreamPack_1_1SetOptionsFromStreamNode.html</anchorfile>
      <anchor>a35bde2e0f5a912d2b0430fbbeaabf6e6</anchor>
      <arglist>(int option_num, const std::string &amp;option_value)=0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>OptionsFromStreamPack::SetOptionsToTargetBase</name>
    <filename>classOptionsFromStreamPack_1_1SetOptionsToTargetBase.html</filename>
    <templarg></templarg>
    <member kind="function">
      <type>void</type>
      <name>set_target</name>
      <anchorfile>classOptionsFromStreamPack_1_1SetOptionsToTargetBase.html</anchorfile>
      <anchor>a296059ae482e9bdb4189cde3bc7ea3d7</anchor>
      <arglist>(T *target)</arglist>
    </member>
    <member kind="function">
      <type>T *</type>
      <name>get_target</name>
      <anchorfile>classOptionsFromStreamPack_1_1SetOptionsToTargetBase.html</anchorfile>
      <anchor>abef5c7e0387f6a568144e8d9e1a1e108</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const T *</type>
      <name>get_target</name>
      <anchorfile>classOptionsFromStreamPack_1_1SetOptionsToTargetBase.html</anchorfile>
      <anchor>abcf01aa34f9d71a85fc34f204ad045ba</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>T &amp;</type>
      <name>target</name>
      <anchorfile>classOptionsFromStreamPack_1_1SetOptionsToTargetBase.html</anchorfile>
      <anchor>af6c85e992cf34cb963879c27289d1a89</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const T &amp;</type>
      <name>target</name>
      <anchorfile>classOptionsFromStreamPack_1_1SetOptionsToTargetBase.html</anchorfile>
      <anchor>ada7f828c51779cf397ad08c8373485c1</anchor>
      <arglist>() const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>OptionsFromStreamPack::StringToIntMap</name>
    <filename>classOptionsFromStreamPack_1_1StringToIntMap.html</filename>
    <class kind="class">OptionsFromStreamPack::StringToIntMap::AlreadyExists</class>
    <class kind="class">OptionsFromStreamPack::StringToIntMap::DoesNotExist</class>
    <member kind="function">
      <type></type>
      <name>StringToIntMap</name>
      <anchorfile>classOptionsFromStreamPack_1_1StringToIntMap.html</anchorfile>
      <anchor>acb6ce3ca3df9fd005d275ce327049360</anchor>
      <arglist>(const std::string &amp;name, int n, const char *strings[])</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>operator()</name>
      <anchorfile>classOptionsFromStreamPack_1_1StringToIntMap.html</anchorfile>
      <anchor>a4d64f0e3706f7abe828c5c339d2178cf</anchor>
      <arglist>(const std::string &amp;str) const </arglist>
    </member>
    <member kind="function">
      <type>const std::string &amp;</type>
      <name>name</name>
      <anchorfile>classOptionsFromStreamPack_1_1StringToIntMap.html</anchorfile>
      <anchor>a3372b953676a69f07173d725d3327246</anchor>
      <arglist>() const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>OptionsFromStreamPack::StringToIntMap::AlreadyExists</name>
    <filename>classOptionsFromStreamPack_1_1StringToIntMap_1_1AlreadyExists.html</filename>
  </compound>
  <compound kind="class">
    <name>OptionsFromStreamPack::StringToIntMap::DoesNotExist</name>
    <filename>classOptionsFromStreamPack_1_1StringToIntMap_1_1DoesNotExist.html</filename>
    <base>OptionsFromStreamPack::AccessException</base>
  </compound>
  <compound kind="class">
    <name>OptionsFromStreamPack::OptionsFromStreamUtilityPack::OptionsGroup</name>
    <filename>classOptionsFromStreamPack_1_1OptionsFromStreamUtilityPack_1_1OptionsGroup.html</filename>
    <member kind="function">
      <type>bool</type>
      <name>options_group_exists</name>
      <anchorfile>classOptionsFromStreamPack_1_1OptionsFromStreamUtilityPack_1_1OptionsGroup.html</anchorfile>
      <anchor>afec0696e2a5838ecdcf454645efad366</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" static="yes">
      <type>static bool</type>
      <name>option_exists</name>
      <anchorfile>classOptionsFromStreamPack_1_1OptionsFromStreamUtilityPack_1_1OptionsGroup.html</anchorfile>
      <anchor>aa8fb7dcedba5f68cf9f2de446b170f33</anchor>
      <arglist>(const std::string &amp;option_value)</arglist>
    </member>
    <member kind="typedef">
      <type>option_to_value_map_t::iterator</type>
      <name>iterator</name>
      <anchorfile>classOptionsFromStreamPack_1_1OptionsFromStreamUtilityPack_1_1OptionsGroup.html</anchorfile>
      <anchor>a01a3f554523a33f7b62edb4f3e22dc96</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>option_to_value_map_t::const_iterator</type>
      <name>const_iterator</name>
      <anchorfile>classOptionsFromStreamPack_1_1OptionsFromStreamUtilityPack_1_1OptionsGroup.html</anchorfile>
      <anchor>aa5e0ab689c77fd194d42c8ec2a4f7bec</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>std::string &amp;</type>
      <name>option_value</name>
      <anchorfile>classOptionsFromStreamPack_1_1OptionsFromStreamUtilityPack_1_1OptionsGroup.html</anchorfile>
      <anchor>a4290a67d047e5cf689b9115467c53cd4</anchor>
      <arglist>(const std::string &amp;option_name)</arglist>
    </member>
    <member kind="function">
      <type>const std::string &amp;</type>
      <name>option_value</name>
      <anchorfile>classOptionsFromStreamPack_1_1OptionsFromStreamUtilityPack_1_1OptionsGroup.html</anchorfile>
      <anchor>af87650bfb982edebf6b9f0315e12c485</anchor>
      <arglist>(const std::string &amp;option_name) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>num_options</name>
      <anchorfile>classOptionsFromStreamPack_1_1OptionsFromStreamUtilityPack_1_1OptionsGroup.html</anchorfile>
      <anchor>a90be522a95c879f27c6617763d1e7e52</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>iterator</type>
      <name>begin</name>
      <anchorfile>classOptionsFromStreamPack_1_1OptionsFromStreamUtilityPack_1_1OptionsGroup.html</anchorfile>
      <anchor>abc9dfd15bcca55bda1f74793616bedce</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>iterator</type>
      <name>end</name>
      <anchorfile>classOptionsFromStreamPack_1_1OptionsFromStreamUtilityPack_1_1OptionsGroup.html</anchorfile>
      <anchor>a0a485e15ba41ca17e49241b14ba30dbd</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const_iterator</type>
      <name>begin</name>
      <anchorfile>classOptionsFromStreamPack_1_1OptionsFromStreamUtilityPack_1_1OptionsGroup.html</anchorfile>
      <anchor>a6f5eea1b0582c54ffbe253a990f9ee70</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const_iterator</type>
      <name>end</name>
      <anchorfile>classOptionsFromStreamPack_1_1OptionsFromStreamUtilityPack_1_1OptionsGroup.html</anchorfile>
      <anchor>af1a63fbbfadff49406e317a4bf99382e</anchor>
      <arglist>() const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ProfileHackPack::ProfileTiming</name>
    <filename>classProfileHackPack_1_1ProfileTiming.html</filename>
    <member kind="function">
      <type></type>
      <name>ProfileTiming</name>
      <anchorfile>classProfileHackPack_1_1ProfileTiming.html</anchorfile>
      <anchor>a46a7c62835c0896fa5a58dc38e83f233</anchor>
      <arglist>(const std::string &amp;func_name, std::ostream *out=NULL)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~ProfileTiming</name>
      <anchorfile>classProfileHackPack_1_1ProfileTiming.html</anchorfile>
      <anchor>a401c848c608be247e93f5e5d5e7e5cc4</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>RangePack::Range1D</name>
    <filename>classRangePack_1_1Range1D.html</filename>
    <member kind="enumeration">
      <name>EInvalidRange</name>
      <anchorfile>classRangePack_1_1Range1D.html</anchorfile>
      <anchor>ac252ae4af2b1bf0dd53c434d66aa8f8c</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>RTOpPack::Ordinal</type>
      <name>Index</name>
      <anchorfile>classRangePack_1_1Range1D.html</anchorfile>
      <anchor>ab18ba7b1907c81ca86215847dcd39e9e</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Range1D</name>
      <anchorfile>classRangePack_1_1Range1D.html</anchorfile>
      <anchor>a530c653cb2968955af66a4b18b4603c0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Range1D</name>
      <anchorfile>classRangePack_1_1Range1D.html</anchorfile>
      <anchor>a0fa1c01b9e4d5dbfb4155de3f13321a3</anchor>
      <arglist>(EInvalidRange)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Range1D</name>
      <anchorfile>classRangePack_1_1Range1D.html</anchorfile>
      <anchor>a049ad7dd3de7d2607e5deeca49ccdac0</anchor>
      <arglist>(Index lbound, Index ubound)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>full_range</name>
      <anchorfile>classRangePack_1_1Range1D.html</anchorfile>
      <anchor>abf9973d11fe4714d50990dea5561ffd6</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Index</type>
      <name>lbound</name>
      <anchorfile>classRangePack_1_1Range1D.html</anchorfile>
      <anchor>a8233da45c7cb8cd9bbd1dd8aaadefe1f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Index</type>
      <name>ubound</name>
      <anchorfile>classRangePack_1_1Range1D.html</anchorfile>
      <anchor>a95174b445dedf0d0dddab3199788e97c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Index</type>
      <name>size</name>
      <anchorfile>classRangePack_1_1Range1D.html</anchorfile>
      <anchor>af6588766994b74d7388457335d8a22ce</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>in_range</name>
      <anchorfile>classRangePack_1_1Range1D.html</anchorfile>
      <anchor>a9487de0998e098aeda12aa835ae6670a</anchor>
      <arglist>(Index i) const </arglist>
    </member>
    <member kind="function">
      <type>Range1D &amp;</type>
      <name>operator+=</name>
      <anchorfile>classRangePack_1_1Range1D.html</anchorfile>
      <anchor>abf71e1c251554693130195f666cb74c9</anchor>
      <arglist>(Index incr)</arglist>
    </member>
    <member kind="function">
      <type>Range1D &amp;</type>
      <name>operator-=</name>
      <anchorfile>classRangePack_1_1Range1D.html</anchorfile>
      <anchor>ab5043e047c032be816edba99b47a9cf8</anchor>
      <arglist>(Index incr)</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const Range1D</type>
      <name>Invalid</name>
      <anchorfile>classRangePack_1_1Range1D.html</anchorfile>
      <anchor>ad210e6b437f4f5420e2cfced662b1579</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator==</name>
      <anchorfile>classRangePack_1_1Range1D.html</anchorfile>
      <anchor>adf61b6230c029e12f3382b4cb8a8e65a</anchor>
      <arglist>(const Range1D &amp;rng1, const Range1D &amp;rng2)</arglist>
    </member>
    <member kind="function">
      <type>Range1D</type>
      <name>operator+</name>
      <anchorfile>classRangePack_1_1Range1D.html</anchorfile>
      <anchor>a63a095ab449fd2419ee75a0e4df3ffcd</anchor>
      <arglist>(const Range1D &amp;rng_rhs, Range1D::Index i)</arglist>
    </member>
    <member kind="function">
      <type>Range1D</type>
      <name>operator+</name>
      <anchorfile>classRangePack_1_1Range1D.html</anchorfile>
      <anchor>ac82047fd876716dbe88b263fc9b0a6be</anchor>
      <arglist>(Range1D::Index i, const Range1D &amp;rng_rhs)</arglist>
    </member>
    <member kind="function">
      <type>Range1D</type>
      <name>operator-</name>
      <anchorfile>classRangePack_1_1Range1D.html</anchorfile>
      <anchor>a8dd57f48c72100ab3c2f966a96ed4689</anchor>
      <arglist>(const Range1D &amp;rng_rhs, Range1D::Index i)</arglist>
    </member>
    <member kind="function">
      <type>Range1D</type>
      <name>full_range</name>
      <anchorfile>classRangePack_1_1Range1D.html</anchorfile>
      <anchor>a6e1d1f56f8f40f5a79b0a1cd33e4102d</anchor>
      <arglist>(const Range1D &amp;rng, Range1D::Index lbound, Range1D::Index ubound)</arglist>
    </member>
    <member kind="function">
      <type>Range1D</type>
      <name>convert</name>
      <anchorfile>classRangePack_1_1Range1D.html</anchorfile>
      <anchor>afa1422d5345d367d197e1e2622a15e29</anchor>
      <arglist>(const Teuchos::Range1D &amp;rng)</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::Range1D</type>
      <name>convert</name>
      <anchorfile>classRangePack_1_1Range1D.html</anchorfile>
      <anchor>a68cd1a407d249b2f18617af4da253820</anchor>
      <arglist>(const Range1D &amp;rng)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>SerializationPack::Serializable</name>
    <filename>classSerializationPack_1_1Serializable.html</filename>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~Serializable</name>
      <anchorfile>classSerializationPack_1_1Serializable.html</anchorfile>
      <anchor>a7842eb193c8c85a0d11950bed75a0e43</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>serialize</name>
      <anchorfile>classSerializationPack_1_1Serializable.html</anchorfile>
      <anchor>aeeeaabd8e70a7951f0ebd7b2aaadffa4</anchor>
      <arglist>(std::ostream &amp;out) const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>unserialize</name>
      <anchorfile>classSerializationPack_1_1Serializable.html</anchorfile>
      <anchor>ae493b058a6c8d38ada49de7608ac8b23</anchor>
      <arglist>(std::istream &amp;in)=0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>StandardCompositionRelationshipsPack::NoRefSet</name>
    <filename>classStandardCompositionRelationshipsPack_1_1NoRefSet.html</filename>
  </compound>
  <compound kind="class">
    <name>StopWatchPack::stopwatch</name>
    <filename>classStopWatchPack_1_1stopwatch.html</filename>
    <member kind="function">
      <type></type>
      <name>stopwatch</name>
      <anchorfile>classStopWatchPack_1_1stopwatch.html</anchorfile>
      <anchor>a7cf7807a14d3aca762a30d8d9db5ca84</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>is_running</name>
      <anchorfile>classStopWatchPack_1_1stopwatch.html</anchorfile>
      <anchor>a562ee03243acf7f0b74b758c7a267838</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>start</name>
      <anchorfile>classStopWatchPack_1_1stopwatch.html</anchorfile>
      <anchor>a6c4a759674898a6f21f5c4ac691a34fd</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>stop</name>
      <anchorfile>classStopWatchPack_1_1stopwatch.html</anchorfile>
      <anchor>a6b6eb7d4cbce31370f61b32a21d475ab</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>reset</name>
      <anchorfile>classStopWatchPack_1_1stopwatch.html</anchorfile>
      <anchor>ae2d15005fa6bddd704380b6ea8921f8f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>read</name>
      <anchorfile>classStopWatchPack_1_1stopwatch.html</anchorfile>
      <anchor>a38a9ce675c2507b306c0d0ca214e757a</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>StrideIterPack::stride_iter</name>
    <filename>classStrideIterPack_1_1stride__iter.html</filename>
    <templarg>T_iterator_type</templarg>
    <templarg>T_value_type</templarg>
    <templarg>T_reference_type</templarg>
    <templarg>T_pointer_type</templarg>
    <templarg>T_difference_type</templarg>
    <member kind="function">
      <type>difference_type</type>
      <name>operator-</name>
      <anchorfile>classStrideIterPack_1_1stride__iter.html</anchorfile>
      <anchor>aee5802e80c6ec24c2976dbb6d32414ce</anchor>
      <arglist>(const stride_iter &amp;itr) const </arglist>
    </member>
    <member kind="typedef">
      <type>std::random_access_iterator_tag</type>
      <name>iterator_category</name>
      <anchorfile>classStrideIterPack_1_1stride__iter.html</anchorfile>
      <anchor>a1dfb99089dd5b60c43451e9047723ad7</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>T_iterator_type</type>
      <name>iterator_type</name>
      <anchorfile>classStrideIterPack_1_1stride__iter.html</anchorfile>
      <anchor>a63d5dfba4d48dc9139a979ab743916ac</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>T_value_type</type>
      <name>value_type</name>
      <anchorfile>classStrideIterPack_1_1stride__iter.html</anchorfile>
      <anchor>a9088b61ec5559f2c1ecf4af1a600809d</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>T_reference_type</type>
      <name>reference</name>
      <anchorfile>classStrideIterPack_1_1stride__iter.html</anchorfile>
      <anchor>a5e0020742857bac83478b7cda6b56fa6</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>T_pointer_type</type>
      <name>pointer</name>
      <anchorfile>classStrideIterPack_1_1stride__iter.html</anchorfile>
      <anchor>a16da8f477bdda717e93ce13c4bb40edf</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>T_difference_type</type>
      <name>difference_type</name>
      <anchorfile>classStrideIterPack_1_1stride__iter.html</anchorfile>
      <anchor>a6ca4411dedac19a6ef01efed8ee15d6f</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>stride_iter</name>
      <anchorfile>classStrideIterPack_1_1stride__iter.html</anchorfile>
      <anchor>aec6e21704e5a325f779ada829e2e4851</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>stride_iter</name>
      <anchorfile>classStrideIterPack_1_1stride__iter.html</anchorfile>
      <anchor>a8cec92f252044aa4af82388c61f78580</anchor>
      <arglist>(iterator_type current)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>stride_iter</name>
      <anchorfile>classStrideIterPack_1_1stride__iter.html</anchorfile>
      <anchor>ab7ed07739a05a73eb5b50caaefb77a11</anchor>
      <arglist>(iterator_type current, difference_type stride)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>stride_iter</name>
      <anchorfile>classStrideIterPack_1_1stride__iter.html</anchorfile>
      <anchor>ad910be33692df33f56034162ab8ff23d</anchor>
      <arglist>(const stride_iter&lt; Iter, Val, Ref, Ptr, Diff &gt; &amp;rhs)</arglist>
    </member>
    <member kind="function">
      <type>stride_iter &amp;</type>
      <name>operator=</name>
      <anchorfile>classStrideIterPack_1_1stride__iter.html</anchorfile>
      <anchor>ae8ae75b61564377a4e53c5ba97d7ba45</anchor>
      <arglist>(const stride_iter&lt; Iter, Val, Ref, Ptr, Diff &gt; &amp;rhs)</arglist>
    </member>
    <member kind="function">
      <type>reference</type>
      <name>operator*</name>
      <anchorfile>classStrideIterPack_1_1stride__iter.html</anchorfile>
      <anchor>a5cb51b742f37fc35aacbc0c6ec3c6174</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>pointer</type>
      <name>operator-&gt;</name>
      <anchorfile>classStrideIterPack_1_1stride__iter.html</anchorfile>
      <anchor>a57db582641f7f046781a1f662d896966</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>reference</type>
      <name>operator[]</name>
      <anchorfile>classStrideIterPack_1_1stride__iter.html</anchorfile>
      <anchor>a40020cdc23a77ed87bccfd8ae16fe7d5</anchor>
      <arglist>(difference_type n) const </arglist>
    </member>
    <member kind="function">
      <type>stride_iter &amp;</type>
      <name>operator++</name>
      <anchorfile>classStrideIterPack_1_1stride__iter.html</anchorfile>
      <anchor>a177ebd5ca0fcf74cb4d08b69e06bc88a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const stride_iter</type>
      <name>operator++</name>
      <anchorfile>classStrideIterPack_1_1stride__iter.html</anchorfile>
      <anchor>a9c427805e2c216f581ee929b904bf589</anchor>
      <arglist>(int)</arglist>
    </member>
    <member kind="function">
      <type>stride_iter &amp;</type>
      <name>operator--</name>
      <anchorfile>classStrideIterPack_1_1stride__iter.html</anchorfile>
      <anchor>ad9ee9f9b7482d3ce3a1ac664d6e98040</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const stride_iter</type>
      <name>operator--</name>
      <anchorfile>classStrideIterPack_1_1stride__iter.html</anchorfile>
      <anchor>adf94697d71832d74c2618add64037feb</anchor>
      <arglist>(int)</arglist>
    </member>
    <member kind="function">
      <type>stride_iter</type>
      <name>operator+</name>
      <anchorfile>classStrideIterPack_1_1stride__iter.html</anchorfile>
      <anchor>a2665d4b4feb2c1ffb455d316a98155ec</anchor>
      <arglist>(difference_type n)</arglist>
    </member>
    <member kind="function">
      <type>const stride_iter</type>
      <name>operator+</name>
      <anchorfile>classStrideIterPack_1_1stride__iter.html</anchorfile>
      <anchor>a980053b1c1c859057758028bc3037b69</anchor>
      <arglist>(difference_type n) const </arglist>
    </member>
    <member kind="function">
      <type>stride_iter &amp;</type>
      <name>operator+=</name>
      <anchorfile>classStrideIterPack_1_1stride__iter.html</anchorfile>
      <anchor>ab99c936ab09ee7163465219c2fd098fb</anchor>
      <arglist>(difference_type n)</arglist>
    </member>
    <member kind="function">
      <type>stride_iter</type>
      <name>operator-</name>
      <anchorfile>classStrideIterPack_1_1stride__iter.html</anchorfile>
      <anchor>a72423598e83c29bf24d4f0d32e8f4a42</anchor>
      <arglist>(difference_type n)</arglist>
    </member>
    <member kind="function">
      <type>const stride_iter</type>
      <name>operator-</name>
      <anchorfile>classStrideIterPack_1_1stride__iter.html</anchorfile>
      <anchor>a00adaf90c1a6b43061314187b84ffa6d</anchor>
      <arglist>(difference_type n) const </arglist>
    </member>
    <member kind="function">
      <type>stride_iter &amp;</type>
      <name>operator-=</name>
      <anchorfile>classStrideIterPack_1_1stride__iter.html</anchorfile>
      <anchor>ab844a394584507339bd3b60bdc33872d</anchor>
      <arglist>(difference_type n)</arglist>
    </member>
    <member kind="function">
      <type>iterator_type</type>
      <name>current</name>
      <anchorfile>classStrideIterPack_1_1stride__iter.html</anchorfile>
      <anchor>ad3b9ec35513147c9caeb94cb405ccb72</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>difference_type</type>
      <name>stride</name>
      <anchorfile>classStrideIterPack_1_1stride__iter.html</anchorfile>
      <anchor>abce28e01a8bd3af0fbf10e366ce1da9c</anchor>
      <arglist>() const </arglist>
    </member>
  </compound>
  <compound kind="dir">
    <name>MoochoUtilities</name>
    <path>/Users/sscoll/Downloads/trilinos-11.0.3-Source/packages/moocho/src/MoochoUtilities/</path>
    <filename>dir_da0daebbebcdcf618a1a9e37bb799e34.html</filename>
    <dir>src</dir>
  </compound>
  <compound kind="dir">
    <name>src</name>
    <path>/Users/sscoll/Downloads/trilinos-11.0.3-Source/packages/moocho/src/MoochoUtilities/src/</path>
    <filename>dir_c718046de9551db48bae0c659a24e476.html</filename>
    <file>BLAS_Cpp_Types.hpp</file>
    <file>CrtDbgReport.cpp</file>
    <file>CrtSetDbgFlag.cpp</file>
    <file>FortranTypes_CppFortranStrings.cpp</file>
    <file>FortranTypes_CppFortranStrings.hpp</file>
    <file>FortranTypes_f_open_file.cpp</file>
    <file>FortranTypes_f_open_file.hpp</file>
    <file>InputStreamHelperPack_EatInputComment.cpp</file>
    <file>InputStreamHelperPack_EatInputComment.hpp</file>
    <file>OptionsFromStreamPack_CommandLineOptionsFromStreamProcessor.cpp</file>
    <file>OptionsFromStreamPack_CommandLineOptionsFromStreamProcessor.hpp</file>
    <file>OptionsFromStreamPack_OptionsFromStream.cpp</file>
    <file>OptionsFromStreamPack_OptionsFromStream.hpp</file>
    <file>OptionsFromStreamPack_OptionsFromStreamExceptions.hpp</file>
    <file>OptionsFromStreamPack_SetOptionsFromStream.hpp</file>
    <file>OptionsFromStreamPack_SetOptionsFromStreamNode.cpp</file>
    <file>OptionsFromStreamPack_SetOptionsFromStreamNode.hpp</file>
    <file>OptionsFromStreamPack_SetOptionsToTargetBase.hpp</file>
    <file>OptionsFromStreamPack_StringToBool.cpp</file>
    <file>OptionsFromStreamPack_StringToBool.hpp</file>
    <file>OptionsFromStreamPack_StringToIntMap.cpp</file>
    <file>OptionsFromStreamPack_StringToIntMap.hpp</file>
    <file>ProfileHackPack_profile_hack.cpp</file>
    <file>ProfileHackPack_profile_hack.hpp</file>
    <file>RangePack_Range1D.cpp</file>
    <file>RangePack_Range1D.hpp</file>
    <file>ReleaseResource.hpp</file>
    <file>ReleaseResource_ref_count_ptr.hpp</file>
    <file>SerializationPack_Serializable.hpp</file>
    <file>SpecialASCII.hpp</file>
    <file>StandardAggregationMacros.hpp</file>
    <file>StandardCompositionRelationshipsPack.hpp</file>
    <file>StopWatchPack_stopwatch.cpp</file>
    <file>StopWatchPack_stopwatch.hpp</file>
    <file>StrideIterPack_StrideIter.hpp</file>
    <file>TestingHelperPack_update_success.cpp</file>
    <file>TestingHelperPack_update_success.hpp</file>
  </compound>
  <compound kind="dir">
    <name>src</name>
    <path>/Users/sscoll/Downloads/trilinos-11.0.3-Source/packages/moocho/src/</path>
    <filename>dir_68267d1309a1af8e8297ef4c3efbcdba.html</filename>
    <dir>MoochoUtilities</dir>
  </compound>
  <compound kind="page">
    <name>index</name>
    <title>MoochoUtilities: Miscellaneous Utilities for MOOCHO</title>
    <filename>index</filename>
  </compound>
</tagfile>
