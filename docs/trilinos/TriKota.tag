<?xml version='1.0' encoding='UTF-8' standalone='yes' ?>
<tagfile>
  <compound kind="class">
    <name>TriKota::DirectApplicInterface</name>
    <filename>classTriKota_1_1DirectApplicInterface.html</filename>
    <member kind="function">
      <type></type>
      <name>DirectApplicInterface</name>
      <anchorfile>classTriKota_1_1DirectApplicInterface.html</anchorfile>
      <anchor>afaeac7c0a176e385a2a15802c11167f9</anchor>
      <arglist>(Dakota::ProblemDescDB &amp;problem_db_, const Teuchos::RCP&lt; EpetraExt::ModelEvaluator &gt; App_, int p_index=0, int g_index=0)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>int</type>
      <name>derived_map_ac</name>
      <anchorfile>classTriKota_1_1DirectApplicInterface.html</anchorfile>
      <anchor>a72e6cd9ee6fafcb3c857cd63353f72d9</anchor>
      <arglist>(const Dakota::String &amp;ac_name)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>int</type>
      <name>derived_map_of</name>
      <anchorfile>classTriKota_1_1DirectApplicInterface.html</anchorfile>
      <anchor>a8de9d0cc63ea0af44e8664a37a47661d</anchor>
      <arglist>(const Dakota::String &amp;of_name)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>TriKota::Driver</name>
    <filename>classTriKota_1_1Driver.html</filename>
    <member kind="function">
      <type></type>
      <name>Driver</name>
      <anchorfile>classTriKota_1_1Driver.html</anchorfile>
      <anchor>a9b973c24708f2e052c396ca01db98f35</anchor>
      <arglist>(std::string dakota_in=&quot;dakota.in&quot;, std::string dakota_out=&quot;dakota.out&quot;, std::string dakota_err=&quot;dakota.err&quot;, std::string dakota_restart_out=&quot;dakota_restart.out&quot;, std::string dakota_restart_in=&quot;&quot;, const int stop_restart_evals=0)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getAnalysisComm</name>
      <anchorfile>classTriKota_1_1Driver.html</anchorfile>
      <anchor>a3a0205779a54e00cf96bb9f797f34ed4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Dakota::ProblemDescDB &amp;</type>
      <name>getProblemDescDB</name>
      <anchorfile>classTriKota_1_1Driver.html</anchorfile>
      <anchor>ac2f5805e7fca4c454e02321ef80613ed</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>run</name>
      <anchorfile>classTriKota_1_1Driver.html</anchorfile>
      <anchor>a2a63f6783215400b3ce21c41d81e63c5</anchor>
      <arglist>(Dakota::DirectApplicInterface *appInterface)</arglist>
    </member>
    <member kind="function">
      <type>const Dakota::Variables</type>
      <name>getFinalSolution</name>
      <anchorfile>classTriKota_1_1Driver.html</anchorfile>
      <anchor>a15921efea35ceefd4fdbd60e8966872f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>rankZero</name>
      <anchorfile>classTriKota_1_1Driver.html</anchorfile>
      <anchor>ae327298e64a4bf9406315e06667eea66</anchor>
      <arglist>() const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>TriKota::ThyraDirectApplicInterface</name>
    <filename>classTriKota_1_1ThyraDirectApplicInterface.html</filename>
    <member kind="function">
      <type></type>
      <name>ThyraDirectApplicInterface</name>
      <anchorfile>classTriKota_1_1ThyraDirectApplicInterface.html</anchorfile>
      <anchor>a9aea022fee07b3a0fe324e130b20295b</anchor>
      <arglist>(Dakota::ProblemDescDB &amp;problem_db_, const Teuchos::RCP&lt; Thyra::ModelEvaluatorDefaultBase&lt; double &gt; &gt; App_, int p_index=0, int g_index=0)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>int</type>
      <name>derived_map_ac</name>
      <anchorfile>classTriKota_1_1ThyraDirectApplicInterface.html</anchorfile>
      <anchor>a371f38e9f271f600379a9d1fc23cc1aa</anchor>
      <arglist>(const Dakota::String &amp;ac_name)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>int</type>
      <name>derived_map_of</name>
      <anchorfile>classTriKota_1_1ThyraDirectApplicInterface.html</anchorfile>
      <anchor>a9ab6644d1ea8021356c283a35fc39e5f</anchor>
      <arglist>(const Dakota::String &amp;of_name)</arglist>
    </member>
  </compound>
  <compound kind="namespace">
    <name>TriKota</name>
    <filename>namespaceTriKota.html</filename>
    <class kind="class">TriKota::DirectApplicInterface</class>
    <class kind="class">TriKota::Driver</class>
    <class kind="class">TriKota::ThyraDirectApplicInterface</class>
    <member kind="function">
      <type>std::string</type>
      <name>TriKota_Version</name>
      <anchorfile>namespaceTriKota.html</anchorfile>
      <anchor>aabe9c7f8541605e22e2aa7f408b25312</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="page">
    <name>index</name>
    <title>TriKota:  A Trilinos Wrapper for Dakota</title>
    <filename>index</filename>
    <docanchor file="index" title="Outline">trikota_outline</docanchor>
    <docanchor file="index" title="Introduction">trikota_intro</docanchor>
    <docanchor file="index" title="How to Build TriKota, including Dakota">trikota_build</docanchor>
    <docanchor file="index" title="Using TriKota">trikota_adapters</docanchor>
    <docanchor file="index" title="TriKota Contacts">trikota_help</docanchor>
  </compound>
</tagfile>
