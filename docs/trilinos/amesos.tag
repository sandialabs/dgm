<?xml version='1.0' encoding='UTF-8' standalone='yes' ?>
<tagfile>
  <compound kind="file">
    <name>Amesos_BaseSolver.h</name>
    <path>/Users/sscoll/dist/trilinos/packages/amesos/src/</path>
    <filename>Amesos__BaseSolver_8h</filename>
    <class kind="class">Amesos_BaseSolver</class>
  </compound>
  <compound kind="file">
    <name>Amesos_Klu.h</name>
    <path>/Users/sscoll/dist/trilinos/packages/amesos/src/</path>
    <filename>Amesos__Klu_8h</filename>
    <includes id="Amesos__BaseSolver_8h" name="Amesos_BaseSolver.h" local="yes" imported="no">Amesos_BaseSolver.h</includes>
    <class kind="class">Amesos_Klu</class>
  </compound>
  <compound kind="file">
    <name>Amesos_MC64.h</name>
    <path>/Users/sscoll/dist/trilinos/packages/amesos/src/</path>
    <filename>Amesos__MC64_8h</filename>
  </compound>
  <compound kind="file">
    <name>Amesos_Paraklete.h</name>
    <path>/Users/sscoll/dist/trilinos/packages/amesos/src/</path>
    <filename>Amesos__Paraklete_8h</filename>
    <includes id="Amesos__BaseSolver_8h" name="Amesos_BaseSolver.h" local="yes" imported="no">Amesos_BaseSolver.h</includes>
    <class kind="class">Amesos_Paraklete</class>
  </compound>
  <compound kind="file">
    <name>Amesos_Reordering.h</name>
    <path>/Users/sscoll/dist/trilinos/packages/amesos/src/</path>
    <filename>Amesos__Reordering_8h</filename>
    <class kind="class">Amesos_Reordering</class>
  </compound>
  <compound kind="file">
    <name>Amesos_Scaling.h</name>
    <path>/Users/sscoll/dist/trilinos/packages/amesos/src/</path>
    <filename>Amesos__Scaling_8h</filename>
    <class kind="class">Amesos_Scaling</class>
  </compound>
  <compound kind="file">
    <name>Amesos_Taucs.h</name>
    <path>/Users/sscoll/dist/trilinos/packages/amesos/src/</path>
    <filename>Amesos__Taucs_8h</filename>
    <includes id="Amesos__BaseSolver_8h" name="Amesos_BaseSolver.h" local="yes" imported="no">Amesos_BaseSolver.h</includes>
    <class kind="class">Amesos_Taucs</class>
  </compound>
  <compound kind="file">
    <name>Amesos_Umfpack.h</name>
    <path>/Users/sscoll/dist/trilinos/packages/amesos/src/</path>
    <filename>Amesos__Umfpack_8h</filename>
    <includes id="Amesos__BaseSolver_8h" name="Amesos_BaseSolver.h" local="yes" imported="no">Amesos_BaseSolver.h</includes>
    <class kind="class">Amesos_Umfpack</class>
  </compound>
  <compound kind="class">
    <name>Amesos</name>
    <filename>classAmesos.html</filename>
    <member kind="function">
      <type>Amesos_BaseSolver *</type>
      <name>Create</name>
      <anchorfile>classAmesos.html</anchorfile>
      <anchor>a57272d41cf59138dd51b530eb9fd90c9</anchor>
      <arglist>(const char *ClassType, const Epetra_LinearProblem &amp;LinearProblem)</arglist>
    </member>
    <member kind="function">
      <type>Amesos_BaseSolver *</type>
      <name>Create</name>
      <anchorfile>classAmesos.html</anchorfile>
      <anchor>a09c86096a4bc0b03ae0661b287956468</anchor>
      <arglist>(const std::string CT, const Epetra_LinearProblem &amp;LinearProblem)</arglist>
    </member>
    <member kind="function">
      <type>Amesos_BaseSolver *</type>
      <name>Create</name>
      <anchorfile>classAmesos.html</anchorfile>
      <anchor>a57272d41cf59138dd51b530eb9fd90c9</anchor>
      <arglist>(const char *ClassType, const Epetra_LinearProblem &amp;LinearProblem)</arglist>
    </member>
    <member kind="function">
      <type>Amesos_BaseSolver *</type>
      <name>Create</name>
      <anchorfile>classAmesos.html</anchorfile>
      <anchor>a09c86096a4bc0b03ae0661b287956468</anchor>
      <arglist>(const std::string CT, const Epetra_LinearProblem &amp;LinearProblem)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>Query</name>
      <anchorfile>classAmesos.html</anchorfile>
      <anchor>a9929aa33f9b760a4a3a04dba8f9a75b1</anchor>
      <arglist>(const char *ClassType)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>Query</name>
      <anchorfile>classAmesos.html</anchorfile>
      <anchor>a3f735ee973b11c6623f86d421c24388b</anchor>
      <arglist>(const std::string CT)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static Teuchos::ParameterList</type>
      <name>GetValidParameters</name>
      <anchorfile>classAmesos.html</anchorfile>
      <anchor>a5c5193d68c0440f85de2ec7c7b582d55</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Amesos_BaseSolver</name>
    <filename>classAmesos__BaseSolver.html</filename>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~Amesos_BaseSolver</name>
      <anchorfile>classAmesos__BaseSolver.html</anchorfile>
      <anchor>a28fb5c8d3f24e0bc1c146a79e0fd1c6e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>SymbolicFactorization</name>
      <anchorfile>classAmesos__BaseSolver.html</anchorfile>
      <anchor>a8c7d37f010f456e73fecff141362cd6f</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>NumericFactorization</name>
      <anchorfile>classAmesos__BaseSolver.html</anchorfile>
      <anchor>a889d3a41a25a09d5ab22bcdcaf188bd4</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>Solve</name>
      <anchorfile>classAmesos__BaseSolver.html</anchorfile>
      <anchor>a26d1a31bac2d1a734d00ba239c259c39</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>SetUseTranspose</name>
      <anchorfile>classAmesos__BaseSolver.html</anchorfile>
      <anchor>a8d15300a27598a698d2d489a785babf3</anchor>
      <arglist>(bool UseTranspose)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>UseTranspose</name>
      <anchorfile>classAmesos__BaseSolver.html</anchorfile>
      <anchor>a0d91ad73d813c38374063d07ef2416d3</anchor>
      <arglist>() const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>SetParameters</name>
      <anchorfile>classAmesos__BaseSolver.html</anchorfile>
      <anchor>ace346398dfa98755ccefc1e42ed8c5e3</anchor>
      <arglist>(Teuchos::ParameterList &amp;ParameterList)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual const Epetra_LinearProblem *</type>
      <name>GetProblem</name>
      <anchorfile>classAmesos__BaseSolver.html</anchorfile>
      <anchor>a13dec34cc1c47ad03d7b39630e9e31cb</anchor>
      <arglist>() const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>MatrixShapeOK</name>
      <anchorfile>classAmesos__BaseSolver.html</anchorfile>
      <anchor>aaac5fe525b166a0bee29ba285fd3d355</anchor>
      <arglist>() const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual const Epetra_Comm &amp;</type>
      <name>Comm</name>
      <anchorfile>classAmesos__BaseSolver.html</anchorfile>
      <anchor>a57a45640dc90232d4667558a3ae54033</anchor>
      <arglist>() const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>NumSymbolicFact</name>
      <anchorfile>classAmesos__BaseSolver.html</anchorfile>
      <anchor>a1c73813b26b15b5d053ce52161cc3d98</anchor>
      <arglist>() const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>NumNumericFact</name>
      <anchorfile>classAmesos__BaseSolver.html</anchorfile>
      <anchor>a23712bae409ebf0306f52ae8ab8b1382</anchor>
      <arglist>() const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>NumSolve</name>
      <anchorfile>classAmesos__BaseSolver.html</anchorfile>
      <anchor>ac788753a8661a704ac0e2c6314f90b6c</anchor>
      <arglist>() const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>PrintStatus</name>
      <anchorfile>classAmesos__BaseSolver.html</anchorfile>
      <anchor>a6e4d04e6cd36b84912402e3e0f0e8684</anchor>
      <arglist>() const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>PrintTiming</name>
      <anchorfile>classAmesos__BaseSolver.html</anchorfile>
      <anchor>a247d675b16a7dd069edb21ad4faad952</anchor>
      <arglist>() const  =0</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>setParameterList</name>
      <anchorfile>classAmesos__BaseSolver.html</anchorfile>
      <anchor>a76452eda6f69d3d4e60dba30bf539d16</anchor>
      <arglist>(Teuchos::RCP&lt; Teuchos::ParameterList &gt; const &amp;paramList)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual Teuchos::RCP&lt; Teuchos::ParameterList &gt;</type>
      <name>getNonconstParameterList</name>
      <anchorfile>classAmesos__BaseSolver.html</anchorfile>
      <anchor>ab80b5d19fa26904497e2d6c7e53c8d37</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual Teuchos::RCP&lt; Teuchos::ParameterList &gt;</type>
      <name>unsetParameterList</name>
      <anchorfile>classAmesos__BaseSolver.html</anchorfile>
      <anchor>a824fa1c114b4f945af0345c0ab37f5fa</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>GetTiming</name>
      <anchorfile>classAmesos__BaseSolver.html</anchorfile>
      <anchor>ae849c3d447e9f022df3bfd141322488e</anchor>
      <arglist>(Teuchos::ParameterList &amp;TimingParameterList) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~Amesos_BaseSolver</name>
      <anchorfile>classAmesos__BaseSolver.html</anchorfile>
      <anchor>a28fb5c8d3f24e0bc1c146a79e0fd1c6e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>SymbolicFactorization</name>
      <anchorfile>classAmesos__BaseSolver.html</anchorfile>
      <anchor>a8c7d37f010f456e73fecff141362cd6f</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>NumericFactorization</name>
      <anchorfile>classAmesos__BaseSolver.html</anchorfile>
      <anchor>a889d3a41a25a09d5ab22bcdcaf188bd4</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>Solve</name>
      <anchorfile>classAmesos__BaseSolver.html</anchorfile>
      <anchor>a26d1a31bac2d1a734d00ba239c259c39</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>SetUseTranspose</name>
      <anchorfile>classAmesos__BaseSolver.html</anchorfile>
      <anchor>a8d15300a27598a698d2d489a785babf3</anchor>
      <arglist>(bool UseTranspose)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>UseTranspose</name>
      <anchorfile>classAmesos__BaseSolver.html</anchorfile>
      <anchor>a0d91ad73d813c38374063d07ef2416d3</anchor>
      <arglist>() const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>SetParameters</name>
      <anchorfile>classAmesos__BaseSolver.html</anchorfile>
      <anchor>ace346398dfa98755ccefc1e42ed8c5e3</anchor>
      <arglist>(Teuchos::ParameterList &amp;ParameterList)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual const Epetra_LinearProblem *</type>
      <name>GetProblem</name>
      <anchorfile>classAmesos__BaseSolver.html</anchorfile>
      <anchor>a13dec34cc1c47ad03d7b39630e9e31cb</anchor>
      <arglist>() const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>MatrixShapeOK</name>
      <anchorfile>classAmesos__BaseSolver.html</anchorfile>
      <anchor>aaac5fe525b166a0bee29ba285fd3d355</anchor>
      <arglist>() const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual const Epetra_Comm &amp;</type>
      <name>Comm</name>
      <anchorfile>classAmesos__BaseSolver.html</anchorfile>
      <anchor>a57a45640dc90232d4667558a3ae54033</anchor>
      <arglist>() const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>NumSymbolicFact</name>
      <anchorfile>classAmesos__BaseSolver.html</anchorfile>
      <anchor>a1c73813b26b15b5d053ce52161cc3d98</anchor>
      <arglist>() const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>NumNumericFact</name>
      <anchorfile>classAmesos__BaseSolver.html</anchorfile>
      <anchor>a23712bae409ebf0306f52ae8ab8b1382</anchor>
      <arglist>() const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>NumSolve</name>
      <anchorfile>classAmesos__BaseSolver.html</anchorfile>
      <anchor>ac788753a8661a704ac0e2c6314f90b6c</anchor>
      <arglist>() const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>PrintStatus</name>
      <anchorfile>classAmesos__BaseSolver.html</anchorfile>
      <anchor>a6e4d04e6cd36b84912402e3e0f0e8684</anchor>
      <arglist>() const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>PrintTiming</name>
      <anchorfile>classAmesos__BaseSolver.html</anchorfile>
      <anchor>a247d675b16a7dd069edb21ad4faad952</anchor>
      <arglist>() const  =0</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>setParameterList</name>
      <anchorfile>classAmesos__BaseSolver.html</anchorfile>
      <anchor>a76452eda6f69d3d4e60dba30bf539d16</anchor>
      <arglist>(Teuchos::RCP&lt; Teuchos::ParameterList &gt; const &amp;paramList)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual Teuchos::RCP&lt; Teuchos::ParameterList &gt;</type>
      <name>getNonconstParameterList</name>
      <anchorfile>classAmesos__BaseSolver.html</anchorfile>
      <anchor>ab80b5d19fa26904497e2d6c7e53c8d37</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual Teuchos::RCP&lt; Teuchos::ParameterList &gt;</type>
      <name>unsetParameterList</name>
      <anchorfile>classAmesos__BaseSolver.html</anchorfile>
      <anchor>a824fa1c114b4f945af0345c0ab37f5fa</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>GetTiming</name>
      <anchorfile>classAmesos__BaseSolver.html</anchorfile>
      <anchor>ae849c3d447e9f022df3bfd141322488e</anchor>
      <arglist>(Teuchos::ParameterList &amp;TimingParameterList) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Amesos_Btf</name>
    <filename>classAmesos__Btf.html</filename>
    <base>Amesos_BaseSolver</base>
    <member kind="function">
      <type></type>
      <name>Amesos_Btf</name>
      <anchorfile>classAmesos__Btf.html</anchorfile>
      <anchor>a0d813d090ef24d60601960b53516d42f</anchor>
      <arglist>(const Epetra_LinearProblem &amp;LinearProblem)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~Amesos_Btf</name>
      <anchorfile>classAmesos__Btf.html</anchorfile>
      <anchor>a6b2b74b922f44aefce1912bbe0459d74</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SymbolicFactorization</name>
      <anchorfile>classAmesos__Btf.html</anchorfile>
      <anchor>a2e369288b4df8a85173a37c25ebc73fa</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumericFactorization</name>
      <anchorfile>classAmesos__Btf.html</anchorfile>
      <anchor>a4904b3332b0f20249bf5f07af9490720</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Solve</name>
      <anchorfile>classAmesos__Btf.html</anchorfile>
      <anchor>ac19a1d24398481a27dfe3975b6ccb1fa</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const Epetra_LinearProblem *</type>
      <name>GetProblem</name>
      <anchorfile>classAmesos__Btf.html</anchorfile>
      <anchor>ac410770c03a54d7268ae718251cddfae</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>MatrixShapeOK</name>
      <anchorfile>classAmesos__Btf.html</anchorfile>
      <anchor>af5743c88a7c562827e0518603394b244</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetUseTranspose</name>
      <anchorfile>classAmesos__Btf.html</anchorfile>
      <anchor>af9396e015a3ee9acb5fc83dff9ebd941</anchor>
      <arglist>(bool UseTranspose)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>UseTranspose</name>
      <anchorfile>classAmesos__Btf.html</anchorfile>
      <anchor>a5622c4d9f209b797fb82fdb7875f7326</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_Comm &amp;</type>
      <name>Comm</name>
      <anchorfile>classAmesos__Btf.html</anchorfile>
      <anchor>aa9c41b3472168a1b075dbfd121a8210e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetParameters</name>
      <anchorfile>classAmesos__Btf.html</anchorfile>
      <anchor>ac7f2488a209e2548985c04efc06f550d</anchor>
      <arglist>(Teuchos::ParameterList &amp;ParameterList)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumSymbolicFact</name>
      <anchorfile>classAmesos__Btf.html</anchorfile>
      <anchor>a24e09bc3b92ab87c89711ded6e3cf9b6</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumNumericFact</name>
      <anchorfile>classAmesos__Btf.html</anchorfile>
      <anchor>a898efbae89818fa45870e5a419c0070d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumSolve</name>
      <anchorfile>classAmesos__Btf.html</anchorfile>
      <anchor>a8c4cc5ff801debb11dfadcbf5db3137f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>PrintTiming</name>
      <anchorfile>classAmesos__Btf.html</anchorfile>
      <anchor>a247b3a06c547b80bc90bcefb485d1fd7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>PrintStatus</name>
      <anchorfile>classAmesos__Btf.html</anchorfile>
      <anchor>af3c15813d422167152a3a912ba9b1eff</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Amesos_Btf</name>
      <anchorfile>classAmesos__Btf.html</anchorfile>
      <anchor>a0d813d090ef24d60601960b53516d42f</anchor>
      <arglist>(const Epetra_LinearProblem &amp;LinearProblem)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~Amesos_Btf</name>
      <anchorfile>classAmesos__Btf.html</anchorfile>
      <anchor>a6b2b74b922f44aefce1912bbe0459d74</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SymbolicFactorization</name>
      <anchorfile>classAmesos__Btf.html</anchorfile>
      <anchor>a2e369288b4df8a85173a37c25ebc73fa</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumericFactorization</name>
      <anchorfile>classAmesos__Btf.html</anchorfile>
      <anchor>a4904b3332b0f20249bf5f07af9490720</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Solve</name>
      <anchorfile>classAmesos__Btf.html</anchorfile>
      <anchor>ac19a1d24398481a27dfe3975b6ccb1fa</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const Epetra_LinearProblem *</type>
      <name>GetProblem</name>
      <anchorfile>classAmesos__Btf.html</anchorfile>
      <anchor>ac410770c03a54d7268ae718251cddfae</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>MatrixShapeOK</name>
      <anchorfile>classAmesos__Btf.html</anchorfile>
      <anchor>af5743c88a7c562827e0518603394b244</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetUseTranspose</name>
      <anchorfile>classAmesos__Btf.html</anchorfile>
      <anchor>af9396e015a3ee9acb5fc83dff9ebd941</anchor>
      <arglist>(bool UseTranspose)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>UseTranspose</name>
      <anchorfile>classAmesos__Btf.html</anchorfile>
      <anchor>a5622c4d9f209b797fb82fdb7875f7326</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_Comm &amp;</type>
      <name>Comm</name>
      <anchorfile>classAmesos__Btf.html</anchorfile>
      <anchor>aa9c41b3472168a1b075dbfd121a8210e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetParameters</name>
      <anchorfile>classAmesos__Btf.html</anchorfile>
      <anchor>ac7f2488a209e2548985c04efc06f550d</anchor>
      <arglist>(Teuchos::ParameterList &amp;ParameterList)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumSymbolicFact</name>
      <anchorfile>classAmesos__Btf.html</anchorfile>
      <anchor>a24e09bc3b92ab87c89711ded6e3cf9b6</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumNumericFact</name>
      <anchorfile>classAmesos__Btf.html</anchorfile>
      <anchor>a898efbae89818fa45870e5a419c0070d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumSolve</name>
      <anchorfile>classAmesos__Btf.html</anchorfile>
      <anchor>a8c4cc5ff801debb11dfadcbf5db3137f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>PrintTiming</name>
      <anchorfile>classAmesos__Btf.html</anchorfile>
      <anchor>a247b3a06c547b80bc90bcefb485d1fd7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>PrintStatus</name>
      <anchorfile>classAmesos__Btf.html</anchorfile>
      <anchor>af3c15813d422167152a3a912ba9b1eff</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Amesos_Component</name>
    <filename>classAmesos__Component.html</filename>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~Amesos_Component</name>
      <anchorfile>classAmesos__Component.html</anchorfile>
      <anchor>afcc59a1fb5ed61cb5fef8d5caec8e8ec</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>PartialFactorization</name>
      <anchorfile>classAmesos__Component.html</anchorfile>
      <anchor>af2db4f09f4f5e5cdc186cacea212ca14</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>Lsolve</name>
      <anchorfile>classAmesos__Component.html</anchorfile>
      <anchor>aef51b3b00376491465aeedc0f4d636e4</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>Usolve</name>
      <anchorfile>classAmesos__Component.html</anchorfile>
      <anchor>af7b20690648b56b6b9e146529a98a07b</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>SetRowPermutation</name>
      <anchorfile>classAmesos__Component.html</anchorfile>
      <anchor>a4e68f8f8df4c6fe3b2c57f8c570b0ac8</anchor>
      <arglist>(int *RowPermutation)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>SetColumnPermutation</name>
      <anchorfile>classAmesos__Component.html</anchorfile>
      <anchor>a37866661c1666d2feac2014245af4f98</anchor>
      <arglist>(int *ColumnPermutation)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>SetSubMatrixSize</name>
      <anchorfile>classAmesos__Component.html</anchorfile>
      <anchor>a20eec28bf6c6be8fddd9d91f279a5231</anchor>
      <arglist>(int SubMatrixSize)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>GetRowPermutation</name>
      <anchorfile>classAmesos__Component.html</anchorfile>
      <anchor>a295351bc5d2e81a87a476c97fe7b3b9f</anchor>
      <arglist>(int **RowPermutation)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>GetColumnPermutation</name>
      <anchorfile>classAmesos__Component.html</anchorfile>
      <anchor>afe731225a7a58740969f21b017e74369</anchor>
      <arglist>(int **ColumnPermutation)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>GetSubMatrixSize</name>
      <anchorfile>classAmesos__Component.html</anchorfile>
      <anchor>abfc5bf0034e8aed969dd47768395f63e</anchor>
      <arglist>(int *SubMatrixSize)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>GetSchurComplement</name>
      <anchorfile>classAmesos__Component.html</anchorfile>
      <anchor>ad1979d6a5379e985dfd9e08806f3e02a</anchor>
      <arglist>(Epetra_CrsMatrix *SchurComplement)=0</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~Amesos_Component</name>
      <anchorfile>classAmesos__Component.html</anchorfile>
      <anchor>afcc59a1fb5ed61cb5fef8d5caec8e8ec</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>PartialFactorization</name>
      <anchorfile>classAmesos__Component.html</anchorfile>
      <anchor>af2db4f09f4f5e5cdc186cacea212ca14</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>Lsolve</name>
      <anchorfile>classAmesos__Component.html</anchorfile>
      <anchor>aef51b3b00376491465aeedc0f4d636e4</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>Usolve</name>
      <anchorfile>classAmesos__Component.html</anchorfile>
      <anchor>af7b20690648b56b6b9e146529a98a07b</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>SetRowPermutation</name>
      <anchorfile>classAmesos__Component.html</anchorfile>
      <anchor>a4e68f8f8df4c6fe3b2c57f8c570b0ac8</anchor>
      <arglist>(int *RowPermutation)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>SetColumnPermutation</name>
      <anchorfile>classAmesos__Component.html</anchorfile>
      <anchor>a37866661c1666d2feac2014245af4f98</anchor>
      <arglist>(int *ColumnPermutation)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>SetSubMatrixSize</name>
      <anchorfile>classAmesos__Component.html</anchorfile>
      <anchor>a20eec28bf6c6be8fddd9d91f279a5231</anchor>
      <arglist>(int SubMatrixSize)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>GetRowPermutation</name>
      <anchorfile>classAmesos__Component.html</anchorfile>
      <anchor>a295351bc5d2e81a87a476c97fe7b3b9f</anchor>
      <arglist>(int **RowPermutation)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>GetColumnPermutation</name>
      <anchorfile>classAmesos__Component.html</anchorfile>
      <anchor>afe731225a7a58740969f21b017e74369</anchor>
      <arglist>(int **ColumnPermutation)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>GetSubMatrixSize</name>
      <anchorfile>classAmesos__Component.html</anchorfile>
      <anchor>abfc5bf0034e8aed969dd47768395f63e</anchor>
      <arglist>(int *SubMatrixSize)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>GetSchurComplement</name>
      <anchorfile>classAmesos__Component.html</anchorfile>
      <anchor>ad1979d6a5379e985dfd9e08806f3e02a</anchor>
      <arglist>(Epetra_CrsMatrix *SchurComplement)=0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Amesos_ComponentBaseSolver</name>
    <filename>classAmesos__ComponentBaseSolver.html</filename>
    <base virtualness="virtual">Amesos_BaseSolver</base>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~Amesos_ComponentBaseSolver</name>
      <anchorfile>classAmesos__ComponentBaseSolver.html</anchorfile>
      <anchor>afe2b2fe6572dafcbe4ca4f6b9dc79cfb</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>PartialFactorization</name>
      <anchorfile>classAmesos__ComponentBaseSolver.html</anchorfile>
      <anchor>a2a31b7ac7c52f5e0007c3b2a71a06df4</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>Lsolve</name>
      <anchorfile>classAmesos__ComponentBaseSolver.html</anchorfile>
      <anchor>a3d49de77d6a8a90da6489d1865e052a4</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>*virtual int</type>
      <name>LsolveStart</name>
      <anchorfile>classAmesos__ComponentBaseSolver.html</anchorfile>
      <anchor>a2ac4d57062440165f973b263a17e9e34</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>LsolvePart</name>
      <anchorfile>classAmesos__ComponentBaseSolver.html</anchorfile>
      <anchor>aaebe0289c9c8225ff713b80c3440da57</anchor>
      <arglist>(int begin, int end)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>Usolve</name>
      <anchorfile>classAmesos__ComponentBaseSolver.html</anchorfile>
      <anchor>ae9b52ba27594bbbf84b62e6d8d065d1c</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>*virtual int</type>
      <name>UsolveStart</name>
      <anchorfile>classAmesos__ComponentBaseSolver.html</anchorfile>
      <anchor>a69cd6f2c3207d7b8c866a996524554a9</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>UsolvePart</name>
      <anchorfile>classAmesos__ComponentBaseSolver.html</anchorfile>
      <anchor>af85a29ad5f881baee42182bd244924d9</anchor>
      <arglist>(int begin, int end)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>SetRowPermutation</name>
      <anchorfile>classAmesos__ComponentBaseSolver.html</anchorfile>
      <anchor>af394d18564218754c4b7664fcb6c3602</anchor>
      <arglist>(int *RowPermutation)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>SetColumnPermutation</name>
      <anchorfile>classAmesos__ComponentBaseSolver.html</anchorfile>
      <anchor>aff1fbbe3f49f7a7067619fd04104b89a</anchor>
      <arglist>(int *ColumnPermutation)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>SetSubMatrixSize</name>
      <anchorfile>classAmesos__ComponentBaseSolver.html</anchorfile>
      <anchor>a3df3ac2fd14501e4181ad4ae8e618cd0</anchor>
      <arglist>(int SubMatrixSize)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>GetRowPermutation</name>
      <anchorfile>classAmesos__ComponentBaseSolver.html</anchorfile>
      <anchor>a7a3adf0f80f0b3f551de9ef443dcb3bd</anchor>
      <arglist>(int **RowPermutation)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>GetColumnPermutation</name>
      <anchorfile>classAmesos__ComponentBaseSolver.html</anchorfile>
      <anchor>a2eebb5bd630b53db94a1b5583302ef9a</anchor>
      <arglist>(int **ColumnPermutation)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>GetSubMatrixSize</name>
      <anchorfile>classAmesos__ComponentBaseSolver.html</anchorfile>
      <anchor>ade687c4845c4046c20d4043058b4b555</anchor>
      <arglist>(int *SubMatrixSize)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>GetSchurComplement</name>
      <anchorfile>classAmesos__ComponentBaseSolver.html</anchorfile>
      <anchor>a2dcb1c73ed004873e03e3e03f0553e0f</anchor>
      <arglist>(Epetra_CrsMatrix *SchurComplement)=0</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~Amesos_ComponentBaseSolver</name>
      <anchorfile>classAmesos__ComponentBaseSolver.html</anchorfile>
      <anchor>afe2b2fe6572dafcbe4ca4f6b9dc79cfb</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>PartialFactorization</name>
      <anchorfile>classAmesos__ComponentBaseSolver.html</anchorfile>
      <anchor>a2a31b7ac7c52f5e0007c3b2a71a06df4</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>Lsolve</name>
      <anchorfile>classAmesos__ComponentBaseSolver.html</anchorfile>
      <anchor>a3d49de77d6a8a90da6489d1865e052a4</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>*virtual int</type>
      <name>LsolveStart</name>
      <anchorfile>classAmesos__ComponentBaseSolver.html</anchorfile>
      <anchor>a2ac4d57062440165f973b263a17e9e34</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>LsolvePart</name>
      <anchorfile>classAmesos__ComponentBaseSolver.html</anchorfile>
      <anchor>aaebe0289c9c8225ff713b80c3440da57</anchor>
      <arglist>(int begin, int end)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>Usolve</name>
      <anchorfile>classAmesos__ComponentBaseSolver.html</anchorfile>
      <anchor>ae9b52ba27594bbbf84b62e6d8d065d1c</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>*virtual int</type>
      <name>UsolveStart</name>
      <anchorfile>classAmesos__ComponentBaseSolver.html</anchorfile>
      <anchor>a69cd6f2c3207d7b8c866a996524554a9</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>UsolvePart</name>
      <anchorfile>classAmesos__ComponentBaseSolver.html</anchorfile>
      <anchor>af85a29ad5f881baee42182bd244924d9</anchor>
      <arglist>(int begin, int end)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>SetRowPermutation</name>
      <anchorfile>classAmesos__ComponentBaseSolver.html</anchorfile>
      <anchor>af394d18564218754c4b7664fcb6c3602</anchor>
      <arglist>(int *RowPermutation)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>SetColumnPermutation</name>
      <anchorfile>classAmesos__ComponentBaseSolver.html</anchorfile>
      <anchor>aff1fbbe3f49f7a7067619fd04104b89a</anchor>
      <arglist>(int *ColumnPermutation)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>SetSubMatrixSize</name>
      <anchorfile>classAmesos__ComponentBaseSolver.html</anchorfile>
      <anchor>a3df3ac2fd14501e4181ad4ae8e618cd0</anchor>
      <arglist>(int SubMatrixSize)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>GetRowPermutation</name>
      <anchorfile>classAmesos__ComponentBaseSolver.html</anchorfile>
      <anchor>a7a3adf0f80f0b3f551de9ef443dcb3bd</anchor>
      <arglist>(int **RowPermutation)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>GetColumnPermutation</name>
      <anchorfile>classAmesos__ComponentBaseSolver.html</anchorfile>
      <anchor>a2eebb5bd630b53db94a1b5583302ef9a</anchor>
      <arglist>(int **ColumnPermutation)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>GetSubMatrixSize</name>
      <anchorfile>classAmesos__ComponentBaseSolver.html</anchorfile>
      <anchor>ade687c4845c4046c20d4043058b4b555</anchor>
      <arglist>(int *SubMatrixSize)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>GetSchurComplement</name>
      <anchorfile>classAmesos__ComponentBaseSolver.html</anchorfile>
      <anchor>a2dcb1c73ed004873e03e3e03f0553e0f</anchor>
      <arglist>(Epetra_CrsMatrix *SchurComplement)=0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Amesos_Control</name>
    <filename>classAmesos__Control.html</filename>
    <member kind="function">
      <type></type>
      <name>Amesos_Control</name>
      <anchorfile>classAmesos__Control.html</anchorfile>
      <anchor>a6b8fa70ce5cdeb6200c916c0b2fcb33e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~Amesos_Control</name>
      <anchorfile>classAmesos__Control.html</anchorfile>
      <anchor>a23508029154696284096c066dff8ad94</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable">
      <type>double</type>
      <name>AddToDiag_</name>
      <anchorfile>classAmesos__Control.html</anchorfile>
      <anchor>ae19396011118fc145acf7b3110205773</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>double</type>
      <name>rcond_threshold_</name>
      <anchorfile>classAmesos__Control.html</anchorfile>
      <anchor>a89fc12d53f04e61a3f469c794d4a196f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>AddZeroToDiag_</name>
      <anchorfile>classAmesos__Control.html</anchorfile>
      <anchor>aa075826db8db6ed51c3d85947f0c52ff</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>MatrixProperty_</name>
      <anchorfile>classAmesos__Control.html</anchorfile>
      <anchor>af6404ec63d44e3f2b09e6fb2f524d322</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>Reindex_</name>
      <anchorfile>classAmesos__Control.html</anchorfile>
      <anchor>a9c7aa0ec15f72bcd8c54842f47fe23d4</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Amesos_Dscpack</name>
    <filename>classAmesos__Dscpack.html</filename>
    <base>Amesos_BaseSolver</base>
    <base protection="private">Amesos_Time</base>
    <base protection="private">Amesos_NoCopiable</base>
    <base protection="private">Amesos_Utils</base>
    <base protection="private">Amesos_Control</base>
    <base protection="private">Amesos_Status</base>
    <member kind="function">
      <type></type>
      <name>Amesos_Dscpack</name>
      <anchorfile>classAmesos__Dscpack.html</anchorfile>
      <anchor>aab5e89521cf47c479c2546655c1d9a0a</anchor>
      <arglist>(const Epetra_LinearProblem &amp;LinearProblem)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~Amesos_Dscpack</name>
      <anchorfile>classAmesos__Dscpack.html</anchorfile>
      <anchor>aeb4dd45f293e02b530fe90e0d851f4de</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SymbolicFactorization</name>
      <anchorfile>classAmesos__Dscpack.html</anchorfile>
      <anchor>aeb63b1e829dec6a7087e06fddc2a752a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumericFactorization</name>
      <anchorfile>classAmesos__Dscpack.html</anchorfile>
      <anchor>a0839eb92e791ef69f7b1fe35e0174c2d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Solve</name>
      <anchorfile>classAmesos__Dscpack.html</anchorfile>
      <anchor>a9807b05f9e1157172cfa31b8743d01d0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const Epetra_LinearProblem *</type>
      <name>GetProblem</name>
      <anchorfile>classAmesos__Dscpack.html</anchorfile>
      <anchor>ae13c44d1f2a36d2b48d2fd5d3e3c753b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>MatrixShapeOK</name>
      <anchorfile>classAmesos__Dscpack.html</anchorfile>
      <anchor>ab776cd050f03a1bce06a85873bc2d59d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetUseTranspose</name>
      <anchorfile>classAmesos__Dscpack.html</anchorfile>
      <anchor>af3ae209124e98c47f8a7e31af00dda47</anchor>
      <arglist>(bool UseTranspose)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>UseTranspose</name>
      <anchorfile>classAmesos__Dscpack.html</anchorfile>
      <anchor>ad16217b971217833fe9cc169db33212a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_Comm &amp;</type>
      <name>Comm</name>
      <anchorfile>classAmesos__Dscpack.html</anchorfile>
      <anchor>a394738dff13196143e3a00115d0e97be</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetParameters</name>
      <anchorfile>classAmesos__Dscpack.html</anchorfile>
      <anchor>a9fb3915d4acbbc06453dd46068970a48</anchor>
      <arglist>(Teuchos::ParameterList &amp;ParameterList)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumSymbolicFact</name>
      <anchorfile>classAmesos__Dscpack.html</anchorfile>
      <anchor>afc3296339d8f8b6a642667645d8d03bf</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumNumericFact</name>
      <anchorfile>classAmesos__Dscpack.html</anchorfile>
      <anchor>a498351bce33ff10f814b6e8086f9f5c7</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumSolve</name>
      <anchorfile>classAmesos__Dscpack.html</anchorfile>
      <anchor>afa89dbaa360378aacd2802e6de2c6f33</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>PrintTiming</name>
      <anchorfile>classAmesos__Dscpack.html</anchorfile>
      <anchor>ac877f18537618f3ed65471914c7257e3</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>PrintStatus</name>
      <anchorfile>classAmesos__Dscpack.html</anchorfile>
      <anchor>a982a8e6da5e4844d69af6dee5816209e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>GetTiming</name>
      <anchorfile>classAmesos__Dscpack.html</anchorfile>
      <anchor>a394a59c9d5cafd4b4b72fcadfd2defc5</anchor>
      <arglist>(Teuchos::ParameterList &amp;TimingParameterList) const </arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Amesos_Dscpack</name>
      <anchorfile>classAmesos__Dscpack.html</anchorfile>
      <anchor>aab5e89521cf47c479c2546655c1d9a0a</anchor>
      <arglist>(const Epetra_LinearProblem &amp;LinearProblem)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~Amesos_Dscpack</name>
      <anchorfile>classAmesos__Dscpack.html</anchorfile>
      <anchor>aeb4dd45f293e02b530fe90e0d851f4de</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SymbolicFactorization</name>
      <anchorfile>classAmesos__Dscpack.html</anchorfile>
      <anchor>aeb63b1e829dec6a7087e06fddc2a752a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumericFactorization</name>
      <anchorfile>classAmesos__Dscpack.html</anchorfile>
      <anchor>a0839eb92e791ef69f7b1fe35e0174c2d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Solve</name>
      <anchorfile>classAmesos__Dscpack.html</anchorfile>
      <anchor>a9807b05f9e1157172cfa31b8743d01d0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const Epetra_LinearProblem *</type>
      <name>GetProblem</name>
      <anchorfile>classAmesos__Dscpack.html</anchorfile>
      <anchor>ae13c44d1f2a36d2b48d2fd5d3e3c753b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>MatrixShapeOK</name>
      <anchorfile>classAmesos__Dscpack.html</anchorfile>
      <anchor>ab776cd050f03a1bce06a85873bc2d59d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetUseTranspose</name>
      <anchorfile>classAmesos__Dscpack.html</anchorfile>
      <anchor>af3ae209124e98c47f8a7e31af00dda47</anchor>
      <arglist>(bool UseTranspose)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>UseTranspose</name>
      <anchorfile>classAmesos__Dscpack.html</anchorfile>
      <anchor>ad16217b971217833fe9cc169db33212a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_Comm &amp;</type>
      <name>Comm</name>
      <anchorfile>classAmesos__Dscpack.html</anchorfile>
      <anchor>a394738dff13196143e3a00115d0e97be</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetParameters</name>
      <anchorfile>classAmesos__Dscpack.html</anchorfile>
      <anchor>a9fb3915d4acbbc06453dd46068970a48</anchor>
      <arglist>(Teuchos::ParameterList &amp;ParameterList)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumSymbolicFact</name>
      <anchorfile>classAmesos__Dscpack.html</anchorfile>
      <anchor>afc3296339d8f8b6a642667645d8d03bf</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumNumericFact</name>
      <anchorfile>classAmesos__Dscpack.html</anchorfile>
      <anchor>a498351bce33ff10f814b6e8086f9f5c7</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumSolve</name>
      <anchorfile>classAmesos__Dscpack.html</anchorfile>
      <anchor>afa89dbaa360378aacd2802e6de2c6f33</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>PrintTiming</name>
      <anchorfile>classAmesos__Dscpack.html</anchorfile>
      <anchor>ac877f18537618f3ed65471914c7257e3</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>PrintStatus</name>
      <anchorfile>classAmesos__Dscpack.html</anchorfile>
      <anchor>a982a8e6da5e4844d69af6dee5816209e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>GetTiming</name>
      <anchorfile>classAmesos__Dscpack.html</anchorfile>
      <anchor>a394a59c9d5cafd4b4b72fcadfd2defc5</anchor>
      <arglist>(Teuchos::ParameterList &amp;TimingParameterList) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Amesos_Dscpack_Pimpl</name>
    <filename>classAmesos__Dscpack__Pimpl.html</filename>
  </compound>
  <compound kind="class">
    <name>Amesos_Klu</name>
    <filename>classAmesos__Klu.html</filename>
    <base>Amesos_BaseSolver</base>
    <base protection="private">Amesos_Time</base>
    <base protection="private">Amesos_NoCopiable</base>
    <base protection="private">Amesos_Utils</base>
    <base protection="private">Amesos_Control</base>
    <base protection="private">Amesos_Status</base>
    <member kind="function">
      <type></type>
      <name>Amesos_Klu</name>
      <anchorfile>classAmesos__Klu.html</anchorfile>
      <anchor>a94316e86d8e1a85ab6befa5e7fd4f636</anchor>
      <arglist>(const Epetra_LinearProblem &amp;LinearProblem)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~Amesos_Klu</name>
      <anchorfile>classAmesos__Klu.html</anchorfile>
      <anchor>a5aa1c144c1ad55669438af6973be85ed</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SymbolicFactorization</name>
      <anchorfile>classAmesos__Klu.html</anchorfile>
      <anchor>a0244a35a6746c73a4be7298c2306119c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumericFactorization</name>
      <anchorfile>classAmesos__Klu.html</anchorfile>
      <anchor>aaffbe6406ff28dda2725107ee868a95e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Solve</name>
      <anchorfile>classAmesos__Klu.html</anchorfile>
      <anchor>acc011a3e6760b3faef8031a2eb469552</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const Epetra_LinearProblem *</type>
      <name>GetProblem</name>
      <anchorfile>classAmesos__Klu.html</anchorfile>
      <anchor>aeddac5fafc76ba8565e813bde1a25f47</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>MatrixShapeOK</name>
      <anchorfile>classAmesos__Klu.html</anchorfile>
      <anchor>ad62e4dcc1dd838df6e223b01b84f337f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetUseTranspose</name>
      <anchorfile>classAmesos__Klu.html</anchorfile>
      <anchor>a4bdac02fb58a06b48ae3975b95e64632</anchor>
      <arglist>(bool UseTranspose_in)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>UseTranspose</name>
      <anchorfile>classAmesos__Klu.html</anchorfile>
      <anchor>a216762fce26247aed8785aea81a32832</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_Comm &amp;</type>
      <name>Comm</name>
      <anchorfile>classAmesos__Klu.html</anchorfile>
      <anchor>ac806261d9268f8eaa257e63f15bef688</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetParameters</name>
      <anchorfile>classAmesos__Klu.html</anchorfile>
      <anchor>a30b38ba9b6046df6e97480457314f8de</anchor>
      <arglist>(Teuchos::ParameterList &amp;ParameterList)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumSymbolicFact</name>
      <anchorfile>classAmesos__Klu.html</anchorfile>
      <anchor>a66da8ac92754a36f87c56644cb7aae32</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumNumericFact</name>
      <anchorfile>classAmesos__Klu.html</anchorfile>
      <anchor>a4da6d85a26a3f64377c52c77fa6b9431</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumSolve</name>
      <anchorfile>classAmesos__Klu.html</anchorfile>
      <anchor>a5905ae5576027b1b057f9bbf45d320ac</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>PrintTiming</name>
      <anchorfile>classAmesos__Klu.html</anchorfile>
      <anchor>a67cf883bff992817980d49734f785b58</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>PrintStatus</name>
      <anchorfile>classAmesos__Klu.html</anchorfile>
      <anchor>a0899dfb36f9a9cbf45b334b27655dba6</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>GetTiming</name>
      <anchorfile>classAmesos__Klu.html</anchorfile>
      <anchor>a8b7bfc56d2124ae11e507a320348778b</anchor>
      <arglist>(Teuchos::ParameterList &amp;TimingParameterList) const </arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Amesos_Klu</name>
      <anchorfile>classAmesos__Klu.html</anchorfile>
      <anchor>a94316e86d8e1a85ab6befa5e7fd4f636</anchor>
      <arglist>(const Epetra_LinearProblem &amp;LinearProblem)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~Amesos_Klu</name>
      <anchorfile>classAmesos__Klu.html</anchorfile>
      <anchor>a5aa1c144c1ad55669438af6973be85ed</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SymbolicFactorization</name>
      <anchorfile>classAmesos__Klu.html</anchorfile>
      <anchor>a0244a35a6746c73a4be7298c2306119c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumericFactorization</name>
      <anchorfile>classAmesos__Klu.html</anchorfile>
      <anchor>aaffbe6406ff28dda2725107ee868a95e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Solve</name>
      <anchorfile>classAmesos__Klu.html</anchorfile>
      <anchor>acc011a3e6760b3faef8031a2eb469552</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const Epetra_LinearProblem *</type>
      <name>GetProblem</name>
      <anchorfile>classAmesos__Klu.html</anchorfile>
      <anchor>aeddac5fafc76ba8565e813bde1a25f47</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>MatrixShapeOK</name>
      <anchorfile>classAmesos__Klu.html</anchorfile>
      <anchor>ad62e4dcc1dd838df6e223b01b84f337f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetUseTranspose</name>
      <anchorfile>classAmesos__Klu.html</anchorfile>
      <anchor>a4bdac02fb58a06b48ae3975b95e64632</anchor>
      <arglist>(bool UseTranspose_in)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>UseTranspose</name>
      <anchorfile>classAmesos__Klu.html</anchorfile>
      <anchor>a216762fce26247aed8785aea81a32832</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_Comm &amp;</type>
      <name>Comm</name>
      <anchorfile>classAmesos__Klu.html</anchorfile>
      <anchor>ac806261d9268f8eaa257e63f15bef688</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetParameters</name>
      <anchorfile>classAmesos__Klu.html</anchorfile>
      <anchor>a30b38ba9b6046df6e97480457314f8de</anchor>
      <arglist>(Teuchos::ParameterList &amp;ParameterList)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumSymbolicFact</name>
      <anchorfile>classAmesos__Klu.html</anchorfile>
      <anchor>a66da8ac92754a36f87c56644cb7aae32</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumNumericFact</name>
      <anchorfile>classAmesos__Klu.html</anchorfile>
      <anchor>a4da6d85a26a3f64377c52c77fa6b9431</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumSolve</name>
      <anchorfile>classAmesos__Klu.html</anchorfile>
      <anchor>a5905ae5576027b1b057f9bbf45d320ac</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>PrintTiming</name>
      <anchorfile>classAmesos__Klu.html</anchorfile>
      <anchor>a67cf883bff992817980d49734f785b58</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>PrintStatus</name>
      <anchorfile>classAmesos__Klu.html</anchorfile>
      <anchor>a0899dfb36f9a9cbf45b334b27655dba6</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>GetTiming</name>
      <anchorfile>classAmesos__Klu.html</anchorfile>
      <anchor>a8b7bfc56d2124ae11e507a320348778b</anchor>
      <arglist>(Teuchos::ParameterList &amp;TimingParameterList) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Amesos_Klu_Pimpl</name>
    <filename>classAmesos__Klu__Pimpl.html</filename>
  </compound>
  <compound kind="class">
    <name>Amesos_Lapack</name>
    <filename>classAmesos__Lapack.html</filename>
    <base>Amesos_BaseSolver</base>
    <base protection="private">Amesos_Time</base>
    <base protection="private">Amesos_NoCopiable</base>
    <base protection="private">Amesos_Utils</base>
    <base protection="private">Amesos_Control</base>
    <base protection="private">Amesos_Status</base>
    <member kind="function">
      <type></type>
      <name>Amesos_Lapack</name>
      <anchorfile>classAmesos__Lapack.html</anchorfile>
      <anchor>ae48f6d9ffdb12c40738b4c90a6783bd6</anchor>
      <arglist>(const Epetra_LinearProblem &amp;LinearProblem)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~Amesos_Lapack</name>
      <anchorfile>classAmesos__Lapack.html</anchorfile>
      <anchor>a18149fbb4eb1b7771f77760182e0c0d2</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SymbolicFactorization</name>
      <anchorfile>classAmesos__Lapack.html</anchorfile>
      <anchor>af7ad7c6af5e8fde18998c36472a57d6e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumericFactorization</name>
      <anchorfile>classAmesos__Lapack.html</anchorfile>
      <anchor>ac56c7d1fdefa8ca177904264fae70d38</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Solve</name>
      <anchorfile>classAmesos__Lapack.html</anchorfile>
      <anchor>a39dcdfed9f7c03e23f6cb73df9fdafac</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const Epetra_LinearProblem *</type>
      <name>GetProblem</name>
      <anchorfile>classAmesos__Lapack.html</anchorfile>
      <anchor>a9d68deb4f8d4004c9977321ef4e1c6a7</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>MatrixShapeOK</name>
      <anchorfile>classAmesos__Lapack.html</anchorfile>
      <anchor>a007ae3765047453a3d33b08304434e47</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetUseTranspose</name>
      <anchorfile>classAmesos__Lapack.html</anchorfile>
      <anchor>a010e2075567e0137ae4c4d553b40a542</anchor>
      <arglist>(bool UseTranspose_in)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>UseTranspose</name>
      <anchorfile>classAmesos__Lapack.html</anchorfile>
      <anchor>a274c142a40dd054ea814bc3235bb90fe</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_Comm &amp;</type>
      <name>Comm</name>
      <anchorfile>classAmesos__Lapack.html</anchorfile>
      <anchor>a8bac780f6f8cc8a391a9c159c37c3cf2</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setParameterList</name>
      <anchorfile>classAmesos__Lapack.html</anchorfile>
      <anchor>adc3c943d897bea31d772371c600a7b64</anchor>
      <arglist>(Teuchos::RCP&lt; Teuchos::ParameterList &gt; const &amp;paramList)</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; Teuchos::ParameterList &gt;</type>
      <name>unsetParameterList</name>
      <anchorfile>classAmesos__Lapack.html</anchorfile>
      <anchor>ac1bcfedde272793a75229cc68862e48a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetParameters</name>
      <anchorfile>classAmesos__Lapack.html</anchorfile>
      <anchor>ad9b94ce5bb8959fc4bf968b18f3e7698</anchor>
      <arglist>(Teuchos::ParameterList &amp;ParameterList)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GEEV</name>
      <anchorfile>classAmesos__Lapack.html</anchorfile>
      <anchor>ab43c0bab4c86a073ed3ae0b205e8dea7</anchor>
      <arglist>(Epetra_Vector &amp;Er, Epetra_Vector &amp;Ei)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumSymbolicFact</name>
      <anchorfile>classAmesos__Lapack.html</anchorfile>
      <anchor>a292feffe0d3383d0f16e4026a761f63e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumNumericFact</name>
      <anchorfile>classAmesos__Lapack.html</anchorfile>
      <anchor>acd2a3cec4f6a8214228227a4a69e06ec</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumSolve</name>
      <anchorfile>classAmesos__Lapack.html</anchorfile>
      <anchor>ab0d27845217663edb3be23ce09f02273</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>PrintTiming</name>
      <anchorfile>classAmesos__Lapack.html</anchorfile>
      <anchor>a7e4c4a77a9332e2db723e770d424c53d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>PrintStatus</name>
      <anchorfile>classAmesos__Lapack.html</anchorfile>
      <anchor>ab8e16115c0141851a357cdd5f269d054</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>GetTiming</name>
      <anchorfile>classAmesos__Lapack.html</anchorfile>
      <anchor>a6384ce2d99538d82bcb97c855df09817</anchor>
      <arglist>(Teuchos::ParameterList &amp;TimingParameterList) const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>const Epetra_RowMatrix *</type>
      <name>Matrix</name>
      <anchorfile>classAmesos__Lapack.html</anchorfile>
      <anchor>a69025a848b146b8500615633edab8497</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>int</type>
      <name>NumGlobalRows</name>
      <anchorfile>classAmesos__Lapack.html</anchorfile>
      <anchor>a9058c80b420ace28fd649e20de3fcd5f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>int</type>
      <name>NumMyRows</name>
      <anchorfile>classAmesos__Lapack.html</anchorfile>
      <anchor>a727448c001dca55c4834344f75331ef5</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>const Epetra_Map &amp;</type>
      <name>SerialMap</name>
      <anchorfile>classAmesos__Lapack.html</anchorfile>
      <anchor>abfa98be114ed2eadf2edb35e94b75eb4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>Epetra_RowMatrix &amp;</type>
      <name>SerialMatrix</name>
      <anchorfile>classAmesos__Lapack.html</anchorfile>
      <anchor>a8931527f7fd8249a4529e0a6470e3db5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>const Epetra_Import &amp;</type>
      <name>MatrixImporter</name>
      <anchorfile>classAmesos__Lapack.html</anchorfile>
      <anchor>ae55803a3491c5e11541d7a518acfc58e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>const Epetra_Export &amp;</type>
      <name>RhsExporter</name>
      <anchorfile>classAmesos__Lapack.html</anchorfile>
      <anchor>ab3603a66e23201bdbe056b9218259ae0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>const Epetra_Import &amp;</type>
      <name>SolutionImporter</name>
      <anchorfile>classAmesos__Lapack.html</anchorfile>
      <anchor>a25740e5da4ee6ef5db4b35425c16590d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>int</type>
      <name>SolveSerial</name>
      <anchorfile>classAmesos__Lapack.html</anchorfile>
      <anchor>a669d2b76b99da23151eee9904dff1d60</anchor>
      <arglist>(Epetra_MultiVector &amp;X, const Epetra_MultiVector &amp;B)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>int</type>
      <name>SolveDistributed</name>
      <anchorfile>classAmesos__Lapack.html</anchorfile>
      <anchor>aff5d3a6d9027e13c36f4cbc348f37209</anchor>
      <arglist>(Epetra_MultiVector &amp;X, const Epetra_MultiVector &amp;B)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>int</type>
      <name>DistributedToSerial</name>
      <anchorfile>classAmesos__Lapack.html</anchorfile>
      <anchor>a777f22488db6b592a2f9184e8bcfc396</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>int</type>
      <name>SerialToDense</name>
      <anchorfile>classAmesos__Lapack.html</anchorfile>
      <anchor>ae12af80431314ba970c98c1087940f8e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>int</type>
      <name>DenseToFactored</name>
      <anchorfile>classAmesos__Lapack.html</anchorfile>
      <anchor>a2925100ec2949c4e1bc1f682ecb1ca0c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>Epetra_SerialDenseMatrix</type>
      <name>DenseMatrix_</name>
      <anchorfile>classAmesos__Lapack.html</anchorfile>
      <anchor>a5d8771ec85e297235e37f7c516695110</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>Epetra_SerialDenseMatrix</type>
      <name>DenseLHS_</name>
      <anchorfile>classAmesos__Lapack.html</anchorfile>
      <anchor>a7bd54bb0936f70655a37d15bdafc03f8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>Epetra_SerialDenseMatrix</type>
      <name>DenseRHS_</name>
      <anchorfile>classAmesos__Lapack.html</anchorfile>
      <anchor>aa8a17948ac5497cdc0a5d0f0f1f64284</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>Epetra_SerialDenseSolver</type>
      <name>DenseSolver_</name>
      <anchorfile>classAmesos__Lapack.html</anchorfile>
      <anchor>aa6c41b37aaff05daaf21d75a448815fc</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>bool</type>
      <name>UseTranspose_</name>
      <anchorfile>classAmesos__Lapack.html</anchorfile>
      <anchor>aada86a486ba3094ab48b2798434849a9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>const Epetra_LinearProblem *</type>
      <name>Problem_</name>
      <anchorfile>classAmesos__Lapack.html</anchorfile>
      <anchor>ad6a3c5cfacb93a9a662b854bf945b194</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>MtxRedistTime_</name>
      <anchorfile>classAmesos__Lapack.html</anchorfile>
      <anchor>ad7cf0bbbd8f773afafca76427c08f703</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Amesos_Lapack</name>
      <anchorfile>classAmesos__Lapack.html</anchorfile>
      <anchor>ae48f6d9ffdb12c40738b4c90a6783bd6</anchor>
      <arglist>(const Epetra_LinearProblem &amp;LinearProblem)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~Amesos_Lapack</name>
      <anchorfile>classAmesos__Lapack.html</anchorfile>
      <anchor>a18149fbb4eb1b7771f77760182e0c0d2</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SymbolicFactorization</name>
      <anchorfile>classAmesos__Lapack.html</anchorfile>
      <anchor>af7ad7c6af5e8fde18998c36472a57d6e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumericFactorization</name>
      <anchorfile>classAmesos__Lapack.html</anchorfile>
      <anchor>ac56c7d1fdefa8ca177904264fae70d38</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Solve</name>
      <anchorfile>classAmesos__Lapack.html</anchorfile>
      <anchor>a39dcdfed9f7c03e23f6cb73df9fdafac</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const Epetra_LinearProblem *</type>
      <name>GetProblem</name>
      <anchorfile>classAmesos__Lapack.html</anchorfile>
      <anchor>a9d68deb4f8d4004c9977321ef4e1c6a7</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>MatrixShapeOK</name>
      <anchorfile>classAmesos__Lapack.html</anchorfile>
      <anchor>a007ae3765047453a3d33b08304434e47</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetUseTranspose</name>
      <anchorfile>classAmesos__Lapack.html</anchorfile>
      <anchor>a010e2075567e0137ae4c4d553b40a542</anchor>
      <arglist>(bool UseTranspose_in)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>UseTranspose</name>
      <anchorfile>classAmesos__Lapack.html</anchorfile>
      <anchor>a274c142a40dd054ea814bc3235bb90fe</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_Comm &amp;</type>
      <name>Comm</name>
      <anchorfile>classAmesos__Lapack.html</anchorfile>
      <anchor>a8bac780f6f8cc8a391a9c159c37c3cf2</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setParameterList</name>
      <anchorfile>classAmesos__Lapack.html</anchorfile>
      <anchor>adc3c943d897bea31d772371c600a7b64</anchor>
      <arglist>(Teuchos::RCP&lt; Teuchos::ParameterList &gt; const &amp;paramList)</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; Teuchos::ParameterList &gt;</type>
      <name>unsetParameterList</name>
      <anchorfile>classAmesos__Lapack.html</anchorfile>
      <anchor>ac1bcfedde272793a75229cc68862e48a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetParameters</name>
      <anchorfile>classAmesos__Lapack.html</anchorfile>
      <anchor>ad9b94ce5bb8959fc4bf968b18f3e7698</anchor>
      <arglist>(Teuchos::ParameterList &amp;ParameterList)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GEEV</name>
      <anchorfile>classAmesos__Lapack.html</anchorfile>
      <anchor>ab43c0bab4c86a073ed3ae0b205e8dea7</anchor>
      <arglist>(Epetra_Vector &amp;Er, Epetra_Vector &amp;Ei)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumSymbolicFact</name>
      <anchorfile>classAmesos__Lapack.html</anchorfile>
      <anchor>a292feffe0d3383d0f16e4026a761f63e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumNumericFact</name>
      <anchorfile>classAmesos__Lapack.html</anchorfile>
      <anchor>acd2a3cec4f6a8214228227a4a69e06ec</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumSolve</name>
      <anchorfile>classAmesos__Lapack.html</anchorfile>
      <anchor>ab0d27845217663edb3be23ce09f02273</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>PrintTiming</name>
      <anchorfile>classAmesos__Lapack.html</anchorfile>
      <anchor>a7e4c4a77a9332e2db723e770d424c53d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>PrintStatus</name>
      <anchorfile>classAmesos__Lapack.html</anchorfile>
      <anchor>ab8e16115c0141851a357cdd5f269d054</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>GetTiming</name>
      <anchorfile>classAmesos__Lapack.html</anchorfile>
      <anchor>a6384ce2d99538d82bcb97c855df09817</anchor>
      <arglist>(Teuchos::ParameterList &amp;TimingParameterList) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Amesos_MC64</name>
    <filename>classAmesos__MC64.html</filename>
  </compound>
  <compound kind="class">
    <name>Amesos_Merikos</name>
    <filename>classAmesos__Merikos.html</filename>
    <base>Amesos_BaseSolver</base>
    <member kind="function">
      <type></type>
      <name>Amesos_Merikos</name>
      <anchorfile>classAmesos__Merikos.html</anchorfile>
      <anchor>a03333b8b35c7bacd7d5e71fe521c3725</anchor>
      <arglist>(const Epetra_LinearProblem &amp;LinearProblem)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~Amesos_Merikos</name>
      <anchorfile>classAmesos__Merikos.html</anchorfile>
      <anchor>ac4d626f1d0e0ce8ab78e3975a0ec4071</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>RedistributeA</name>
      <anchorfile>classAmesos__Merikos.html</anchorfile>
      <anchor>ab83b784ff0430370eb92b7bf9a97ebb3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SymbolicFactorization</name>
      <anchorfile>classAmesos__Merikos.html</anchorfile>
      <anchor>a868fd1594799cda1f31213c5017925b7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumericFactorization</name>
      <anchorfile>classAmesos__Merikos.html</anchorfile>
      <anchor>a4e5ded5f9a3d175494c5146ebcaf1683</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>LSolve</name>
      <anchorfile>classAmesos__Merikos.html</anchorfile>
      <anchor>ac8a0bb33300c812813e5c460b8e74049</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>USolve</name>
      <anchorfile>classAmesos__Merikos.html</anchorfile>
      <anchor>accad9fdcad5d97a9c3441fba9c14cb03</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Solve</name>
      <anchorfile>classAmesos__Merikos.html</anchorfile>
      <anchor>a3c69c02ad2bc269f48cabfef6c9a1242</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const Epetra_LinearProblem *</type>
      <name>GetProblem</name>
      <anchorfile>classAmesos__Merikos.html</anchorfile>
      <anchor>a16dfd8aa43385b0b96f452ad6fd1405a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>MatrixShapeOK</name>
      <anchorfile>classAmesos__Merikos.html</anchorfile>
      <anchor>a7a7a184562e1589f8521d7b899e98bba</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetUseTranspose</name>
      <anchorfile>classAmesos__Merikos.html</anchorfile>
      <anchor>a2d8f5e91e0902e2111d4af375189fc52</anchor>
      <arglist>(bool UseTranspose)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>UseTranspose</name>
      <anchorfile>classAmesos__Merikos.html</anchorfile>
      <anchor>a43d203e0f11c65d9708014789ec34909</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_Comm &amp;</type>
      <name>Comm</name>
      <anchorfile>classAmesos__Merikos.html</anchorfile>
      <anchor>a54afa3eb7d6f0356d2db6a345e5f9b53</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetParameters</name>
      <anchorfile>classAmesos__Merikos.html</anchorfile>
      <anchor>a001965c36f9cf2adf9440608a6afe696</anchor>
      <arglist>(Teuchos::ParameterList &amp;ParameterList)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumSymbolicFact</name>
      <anchorfile>classAmesos__Merikos.html</anchorfile>
      <anchor>a3a100bc313c3a43b130690d9835ff9e2</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumNumericFact</name>
      <anchorfile>classAmesos__Merikos.html</anchorfile>
      <anchor>ad75d375d7bd6656b1ee3e9d60e1544c8</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumSolve</name>
      <anchorfile>classAmesos__Merikos.html</anchorfile>
      <anchor>aabf9d09cdedefadf894e43ffaef73bbc</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>PrintTiming</name>
      <anchorfile>classAmesos__Merikos.html</anchorfile>
      <anchor>ad175cbecb5481c177f4f1a30ec11cb05</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>PrintStatus</name>
      <anchorfile>classAmesos__Merikos.html</anchorfile>
      <anchor>adbb9ca0f7445833ee54bf63c4ca54c34</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Amesos_Merikos</name>
      <anchorfile>classAmesos__Merikos.html</anchorfile>
      <anchor>a03333b8b35c7bacd7d5e71fe521c3725</anchor>
      <arglist>(const Epetra_LinearProblem &amp;LinearProblem)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~Amesos_Merikos</name>
      <anchorfile>classAmesos__Merikos.html</anchorfile>
      <anchor>ac4d626f1d0e0ce8ab78e3975a0ec4071</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>RedistributeA</name>
      <anchorfile>classAmesos__Merikos.html</anchorfile>
      <anchor>ab83b784ff0430370eb92b7bf9a97ebb3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SymbolicFactorization</name>
      <anchorfile>classAmesos__Merikos.html</anchorfile>
      <anchor>a868fd1594799cda1f31213c5017925b7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumericFactorization</name>
      <anchorfile>classAmesos__Merikos.html</anchorfile>
      <anchor>a4e5ded5f9a3d175494c5146ebcaf1683</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>LSolve</name>
      <anchorfile>classAmesos__Merikos.html</anchorfile>
      <anchor>ac8a0bb33300c812813e5c460b8e74049</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>USolve</name>
      <anchorfile>classAmesos__Merikos.html</anchorfile>
      <anchor>accad9fdcad5d97a9c3441fba9c14cb03</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Solve</name>
      <anchorfile>classAmesos__Merikos.html</anchorfile>
      <anchor>a3c69c02ad2bc269f48cabfef6c9a1242</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const Epetra_LinearProblem *</type>
      <name>GetProblem</name>
      <anchorfile>classAmesos__Merikos.html</anchorfile>
      <anchor>a16dfd8aa43385b0b96f452ad6fd1405a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>MatrixShapeOK</name>
      <anchorfile>classAmesos__Merikos.html</anchorfile>
      <anchor>a7a7a184562e1589f8521d7b899e98bba</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetUseTranspose</name>
      <anchorfile>classAmesos__Merikos.html</anchorfile>
      <anchor>a2d8f5e91e0902e2111d4af375189fc52</anchor>
      <arglist>(bool UseTranspose)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>UseTranspose</name>
      <anchorfile>classAmesos__Merikos.html</anchorfile>
      <anchor>a43d203e0f11c65d9708014789ec34909</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_Comm &amp;</type>
      <name>Comm</name>
      <anchorfile>classAmesos__Merikos.html</anchorfile>
      <anchor>a54afa3eb7d6f0356d2db6a345e5f9b53</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetParameters</name>
      <anchorfile>classAmesos__Merikos.html</anchorfile>
      <anchor>a001965c36f9cf2adf9440608a6afe696</anchor>
      <arglist>(Teuchos::ParameterList &amp;ParameterList)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumSymbolicFact</name>
      <anchorfile>classAmesos__Merikos.html</anchorfile>
      <anchor>a3a100bc313c3a43b130690d9835ff9e2</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumNumericFact</name>
      <anchorfile>classAmesos__Merikos.html</anchorfile>
      <anchor>ad75d375d7bd6656b1ee3e9d60e1544c8</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumSolve</name>
      <anchorfile>classAmesos__Merikos.html</anchorfile>
      <anchor>aabf9d09cdedefadf894e43ffaef73bbc</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>PrintTiming</name>
      <anchorfile>classAmesos__Merikos.html</anchorfile>
      <anchor>ad175cbecb5481c177f4f1a30ec11cb05</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>PrintStatus</name>
      <anchorfile>classAmesos__Merikos.html</anchorfile>
      <anchor>adbb9ca0f7445833ee54bf63c4ca54c34</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Amesos_Mumps</name>
    <filename>classAmesos__Mumps.html</filename>
    <base>Amesos_BaseSolver</base>
    <base protection="private">Amesos_Time</base>
    <base protection="private">Amesos_NoCopiable</base>
    <base protection="private">Amesos_Utils</base>
    <base protection="private">Amesos_Control</base>
    <base protection="private">Amesos_Status</base>
    <member kind="function">
      <type>bool</type>
      <name>MatrixShapeOK</name>
      <anchorfile>classAmesos__Mumps.html</anchorfile>
      <anchor>a545e5c606323718284f50410ef657f82</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_Comm &amp;</type>
      <name>Comm</name>
      <anchorfile>classAmesos__Mumps.html</anchorfile>
      <anchor>a2e0a790b89570716ebb48d280b521911</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_LinearProblem *</type>
      <name>GetProblem</name>
      <anchorfile>classAmesos__Mumps.html</anchorfile>
      <anchor>a57537f5e18e2896e53bff42db0bcf2e2</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Amesos_Mumps</name>
      <anchorfile>classAmesos__Mumps.html</anchorfile>
      <anchor>a6dc80d820de40053bd3082bcec959947</anchor>
      <arglist>(const Epetra_LinearProblem &amp;LinearProblem)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~Amesos_Mumps</name>
      <anchorfile>classAmesos__Mumps.html</anchorfile>
      <anchor>af7b2677ad9aad001ac7b67374140c56b</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SymbolicFactorization</name>
      <anchorfile>classAmesos__Mumps.html</anchorfile>
      <anchor>a033a56745c87232c14a4883a410172b1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumericFactorization</name>
      <anchorfile>classAmesos__Mumps.html</anchorfile>
      <anchor>a4701d3348e92cf4ae6dca2428de04f38</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Solve</name>
      <anchorfile>classAmesos__Mumps.html</anchorfile>
      <anchor>a055fb1772ed4b679808d7bde2f35312b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Destroy</name>
      <anchorfile>classAmesos__Mumps.html</anchorfile>
      <anchor>affeb2ae1e96c1bd6fdc3a6ec6a0d8d61</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetUseTranspose</name>
      <anchorfile>classAmesos__Mumps.html</anchorfile>
      <anchor>a037a5381515501ea4c10544fc0e16bd9</anchor>
      <arglist>(bool UseTranspose_in)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>UseTranspose</name>
      <anchorfile>classAmesos__Mumps.html</anchorfile>
      <anchor>ac3367385069b5725dc1a8f0424ea3373</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetParameters</name>
      <anchorfile>classAmesos__Mumps.html</anchorfile>
      <anchor>ac01bb45787653f31328964da6cd45b3d</anchor>
      <arglist>(Teuchos::ParameterList &amp;ParameterList)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumSymbolicFact</name>
      <anchorfile>classAmesos__Mumps.html</anchorfile>
      <anchor>af74c57becd9e720dcde09dac04c832cc</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumNumericFact</name>
      <anchorfile>classAmesos__Mumps.html</anchorfile>
      <anchor>a81617844869ac749c714df8ae9998837</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumSolve</name>
      <anchorfile>classAmesos__Mumps.html</anchorfile>
      <anchor>acf492a9273625c98dc5fbb43de1833dc</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>PrintTiming</name>
      <anchorfile>classAmesos__Mumps.html</anchorfile>
      <anchor>a28f5f6b44f13cba764e05e1a104f9552</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>PrintStatus</name>
      <anchorfile>classAmesos__Mumps.html</anchorfile>
      <anchor>ab366743bfe2dd31d5811034cdfe511ae</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>GetTiming</name>
      <anchorfile>classAmesos__Mumps.html</anchorfile>
      <anchor>adc6c00ebe7a051f9ec3d167e50f380aa</anchor>
      <arglist>(Teuchos::ParameterList &amp;TimingParameterList) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetPrecscaling</name>
      <anchorfile>classAmesos__Mumps.html</anchorfile>
      <anchor>ac62c6bdbeb9d41c6b66a4101057fb2da</anchor>
      <arglist>(double *ColSca, double *RowSca)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetRowScaling</name>
      <anchorfile>classAmesos__Mumps.html</anchorfile>
      <anchor>ae6180949d737d1aba35298f46e086bbe</anchor>
      <arglist>(double *RowSca)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetColScaling</name>
      <anchorfile>classAmesos__Mumps.html</anchorfile>
      <anchor>a67fef2af588ae7c316c304030bfd5f46</anchor>
      <arglist>(double *ColSca)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetOrdering</name>
      <anchorfile>classAmesos__Mumps.html</anchorfile>
      <anchor>a6c69f7673fd5db15bb32ae50f3cf32ce</anchor>
      <arglist>(int *PermIn)</arglist>
    </member>
    <member kind="function">
      <type>double *</type>
      <name>GetRINFO</name>
      <anchorfile>classAmesos__Mumps.html</anchorfile>
      <anchor>a0ff9afd6b06eded319ecf5c3a8607edf</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int *</type>
      <name>GetINFO</name>
      <anchorfile>classAmesos__Mumps.html</anchorfile>
      <anchor>a54bd7bcd359b7ca9ffa37278fe18841c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>double *</type>
      <name>GetRINFOG</name>
      <anchorfile>classAmesos__Mumps.html</anchorfile>
      <anchor>a778d79ae004d567d390f8b351d20023d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int *</type>
      <name>GetINFOG</name>
      <anchorfile>classAmesos__Mumps.html</anchorfile>
      <anchor>a91f26e0442f4bae049a100f90913a6cf</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetICNTL</name>
      <anchorfile>classAmesos__Mumps.html</anchorfile>
      <anchor>a2c979498c4cd03ce7f55f88d21379ced</anchor>
      <arglist>(int pos, int value)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetCNTL</name>
      <anchorfile>classAmesos__Mumps.html</anchorfile>
      <anchor>a1a00e951220f1c2546199827b38afe0c</anchor>
      <arglist>(int pos, double value)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>Epetra_RowMatrix &amp;</type>
      <name>Matrix</name>
      <anchorfile>classAmesos__Mumps.html</anchorfile>
      <anchor>a1057ad6ee060f825c9ed49c870c1a098</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>Epetra_Map &amp;</type>
      <name>RedistrMap</name>
      <anchorfile>classAmesos__Mumps.html</anchorfile>
      <anchor>a2f71a1f847b05db9158d9f9604bb1dcf</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>Epetra_Import &amp;</type>
      <name>RedistrImporter</name>
      <anchorfile>classAmesos__Mumps.html</anchorfile>
      <anchor>a433e0b3c7aed91e9d0570620372da63f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>Epetra_RowMatrix &amp;</type>
      <name>RedistrMatrix</name>
      <anchorfile>classAmesos__Mumps.html</anchorfile>
      <anchor>a4824656cc3dd88cdf13f29b80fa30d36</anchor>
      <arglist>(const bool ImportMatrix=false)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>Epetra_Map &amp;</type>
      <name>SerialMap</name>
      <anchorfile>classAmesos__Mumps.html</anchorfile>
      <anchor>aed06e63804f7d6b2cb8a45af6c991cb9</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>Epetra_Import &amp;</type>
      <name>SerialImporter</name>
      <anchorfile>classAmesos__Mumps.html</anchorfile>
      <anchor>acb29288ebf24c79499e73e5a9dc553cb</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>int</type>
      <name>ConvertToTriplet</name>
      <anchorfile>classAmesos__Mumps.html</anchorfile>
      <anchor>ad41963cd6aa62c149118d613d41f183e</anchor>
      <arglist>(const bool OnlyValues)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>int</type>
      <name>CheckError</name>
      <anchorfile>classAmesos__Mumps.html</anchorfile>
      <anchor>acb37883b7ad9287cebd96e66d4a65dd6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>CheckParameters</name>
      <anchorfile>classAmesos__Mumps.html</anchorfile>
      <anchor>adfef4d96a4ba47cbf27162f917705444</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>bool</type>
      <name>IsConvertToTripletOK_</name>
      <anchorfile>classAmesos__Mumps.html</anchorfile>
      <anchor>a5bae32c352bbd6b6dc2d405f6ccb69f7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>bool</type>
      <name>IsComputeSchurComplementOK_</name>
      <anchorfile>classAmesos__Mumps.html</anchorfile>
      <anchor>a644e3411b43b15f154cc8ceb9ad6bc14</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>std::vector&lt; int &gt;</type>
      <name>Row</name>
      <anchorfile>classAmesos__Mumps.html</anchorfile>
      <anchor>a993e80dca2136795d06db1beca027ffb</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>std::vector&lt; int &gt;</type>
      <name>Col</name>
      <anchorfile>classAmesos__Mumps.html</anchorfile>
      <anchor>a91da9ccad9532a981a9c886b7a09994f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>std::vector&lt; double &gt;</type>
      <name>Val</name>
      <anchorfile>classAmesos__Mumps.html</anchorfile>
      <anchor>a6a7925a976d2a3541198660e5f27efb4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>MaxProcs_</name>
      <anchorfile>classAmesos__Mumps.html</anchorfile>
      <anchor>a6e91c5bc441b4dd3d5caeca6361ffb03</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>bool</type>
      <name>UseTranspose_</name>
      <anchorfile>classAmesos__Mumps.html</anchorfile>
      <anchor>a104bba95569e8405877c09909e5d9c25</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>MtxConvTime_</name>
      <anchorfile>classAmesos__Mumps.html</anchorfile>
      <anchor>a34abd7d056b2392f2df8810f3d6b1af7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>double *</type>
      <name>RowSca_</name>
      <anchorfile>classAmesos__Mumps.html</anchorfile>
      <anchor>a34161923dbaab774f289e5e35f6f3ef3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int *</type>
      <name>PermIn_</name>
      <anchorfile>classAmesos__Mumps.html</anchorfile>
      <anchor>ac9bd0bbd3058fcdc2d9cfe8dce35f058</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>NumSchurComplementRows_</name>
      <anchorfile>classAmesos__Mumps.html</anchorfile>
      <anchor>a694e2550a8b6c299678c35f7ae8f6452</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int *</type>
      <name>SchurComplementRows_</name>
      <anchorfile>classAmesos__Mumps.html</anchorfile>
      <anchor>a5bde546f874867d4efedc7200e84bbdb</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>RCP&lt; Epetra_CrsMatrix &gt;</type>
      <name>CrsSchurComplement_</name>
      <anchorfile>classAmesos__Mumps.html</anchorfile>
      <anchor>a67682da3f91508bb5ace72d99d5aadae</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>RCP&lt; Epetra_SerialDenseMatrix &gt;</type>
      <name>DenseSchurComplement_</name>
      <anchorfile>classAmesos__Mumps.html</anchorfile>
      <anchor>ae4b71e6a889fa37a6b8af1c8511c3a22</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>const Epetra_LinearProblem *</type>
      <name>Problem_</name>
      <anchorfile>classAmesos__Mumps.html</anchorfile>
      <anchor>adfab1dfe9f5361462c83c3809801fd98</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>RCP&lt; Epetra_Map &gt;</type>
      <name>RedistrMap_</name>
      <anchorfile>classAmesos__Mumps.html</anchorfile>
      <anchor>a7cfa26cc5889ad2a51ce9849c6cafcc2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>RCP&lt; Epetra_Import &gt;</type>
      <name>RedistrImporter_</name>
      <anchorfile>classAmesos__Mumps.html</anchorfile>
      <anchor>a8d37e9815b0ad09a9da46295bcfbe49d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>RCP&lt; Epetra_CrsMatrix &gt;</type>
      <name>RedistrMatrix_</name>
      <anchorfile>classAmesos__Mumps.html</anchorfile>
      <anchor>a7de1e6ca4f030c60fd93d9ee4485fff5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>RCP&lt; Epetra_Map &gt;</type>
      <name>SerialMap_</name>
      <anchorfile>classAmesos__Mumps.html</anchorfile>
      <anchor>a0f6dbb942e0b2a9d386a03509e4ae821</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>RCP&lt; Epetra_Import &gt;</type>
      <name>SerialImporter_</name>
      <anchorfile>classAmesos__Mumps.html</anchorfile>
      <anchor>ae278d552ce15e83e3f63b02ebe371e79</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Amesos_Mumps</name>
      <anchorfile>classAmesos__Mumps.html</anchorfile>
      <anchor>a6dc80d820de40053bd3082bcec959947</anchor>
      <arglist>(const Epetra_LinearProblem &amp;LinearProblem)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~Amesos_Mumps</name>
      <anchorfile>classAmesos__Mumps.html</anchorfile>
      <anchor>af7b2677ad9aad001ac7b67374140c56b</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SymbolicFactorization</name>
      <anchorfile>classAmesos__Mumps.html</anchorfile>
      <anchor>a033a56745c87232c14a4883a410172b1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumericFactorization</name>
      <anchorfile>classAmesos__Mumps.html</anchorfile>
      <anchor>a4701d3348e92cf4ae6dca2428de04f38</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Solve</name>
      <anchorfile>classAmesos__Mumps.html</anchorfile>
      <anchor>a055fb1772ed4b679808d7bde2f35312b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Destroy</name>
      <anchorfile>classAmesos__Mumps.html</anchorfile>
      <anchor>affeb2ae1e96c1bd6fdc3a6ec6a0d8d61</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetUseTranspose</name>
      <anchorfile>classAmesos__Mumps.html</anchorfile>
      <anchor>a037a5381515501ea4c10544fc0e16bd9</anchor>
      <arglist>(bool UseTranspose_in)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>UseTranspose</name>
      <anchorfile>classAmesos__Mumps.html</anchorfile>
      <anchor>ac3367385069b5725dc1a8f0424ea3373</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetParameters</name>
      <anchorfile>classAmesos__Mumps.html</anchorfile>
      <anchor>ac01bb45787653f31328964da6cd45b3d</anchor>
      <arglist>(Teuchos::ParameterList &amp;ParameterList)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumSymbolicFact</name>
      <anchorfile>classAmesos__Mumps.html</anchorfile>
      <anchor>af74c57becd9e720dcde09dac04c832cc</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumNumericFact</name>
      <anchorfile>classAmesos__Mumps.html</anchorfile>
      <anchor>a81617844869ac749c714df8ae9998837</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumSolve</name>
      <anchorfile>classAmesos__Mumps.html</anchorfile>
      <anchor>acf492a9273625c98dc5fbb43de1833dc</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>PrintTiming</name>
      <anchorfile>classAmesos__Mumps.html</anchorfile>
      <anchor>a28f5f6b44f13cba764e05e1a104f9552</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>PrintStatus</name>
      <anchorfile>classAmesos__Mumps.html</anchorfile>
      <anchor>ab366743bfe2dd31d5811034cdfe511ae</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>GetTiming</name>
      <anchorfile>classAmesos__Mumps.html</anchorfile>
      <anchor>adc6c00ebe7a051f9ec3d167e50f380aa</anchor>
      <arglist>(Teuchos::ParameterList &amp;TimingParameterList) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetPrecscaling</name>
      <anchorfile>classAmesos__Mumps.html</anchorfile>
      <anchor>ac62c6bdbeb9d41c6b66a4101057fb2da</anchor>
      <arglist>(double *ColSca, double *RowSca)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetRowScaling</name>
      <anchorfile>classAmesos__Mumps.html</anchorfile>
      <anchor>ae6180949d737d1aba35298f46e086bbe</anchor>
      <arglist>(double *RowSca)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetColScaling</name>
      <anchorfile>classAmesos__Mumps.html</anchorfile>
      <anchor>a67fef2af588ae7c316c304030bfd5f46</anchor>
      <arglist>(double *ColSca)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetOrdering</name>
      <anchorfile>classAmesos__Mumps.html</anchorfile>
      <anchor>a6c69f7673fd5db15bb32ae50f3cf32ce</anchor>
      <arglist>(int *PermIn)</arglist>
    </member>
    <member kind="function">
      <type>double *</type>
      <name>GetRINFO</name>
      <anchorfile>classAmesos__Mumps.html</anchorfile>
      <anchor>a0ff9afd6b06eded319ecf5c3a8607edf</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int *</type>
      <name>GetINFO</name>
      <anchorfile>classAmesos__Mumps.html</anchorfile>
      <anchor>a54bd7bcd359b7ca9ffa37278fe18841c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>double *</type>
      <name>GetRINFOG</name>
      <anchorfile>classAmesos__Mumps.html</anchorfile>
      <anchor>a778d79ae004d567d390f8b351d20023d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int *</type>
      <name>GetINFOG</name>
      <anchorfile>classAmesos__Mumps.html</anchorfile>
      <anchor>a91f26e0442f4bae049a100f90913a6cf</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetICNTL</name>
      <anchorfile>classAmesos__Mumps.html</anchorfile>
      <anchor>a2c979498c4cd03ce7f55f88d21379ced</anchor>
      <arglist>(int pos, int value)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetCNTL</name>
      <anchorfile>classAmesos__Mumps.html</anchorfile>
      <anchor>a1a00e951220f1c2546199827b38afe0c</anchor>
      <arglist>(int pos, double value)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Amesos_NoCopiable</name>
    <filename>classAmesos__NoCopiable.html</filename>
    <member kind="function">
      <type></type>
      <name>Amesos_NoCopiable</name>
      <anchorfile>classAmesos__NoCopiable.html</anchorfile>
      <anchor>a0acdc5b0d260d0ce338578fe12daeb6e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~Amesos_NoCopiable</name>
      <anchorfile>classAmesos__NoCopiable.html</anchorfile>
      <anchor>a0d5249ec17a2424d31869db9e0ba62d4</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Amesos_Paraklete</name>
    <filename>classAmesos__Paraklete.html</filename>
    <base>Amesos_BaseSolver</base>
    <base protection="private">Amesos_Time</base>
    <base protection="private">Amesos_NoCopiable</base>
    <base protection="private">Amesos_Utils</base>
    <base protection="private">Amesos_Control</base>
    <base protection="private">Amesos_Status</base>
    <member kind="function">
      <type></type>
      <name>Amesos_Paraklete</name>
      <anchorfile>classAmesos__Paraklete.html</anchorfile>
      <anchor>ad5d24b4ecccad919b13bda1c7ceff66c</anchor>
      <arglist>(const Epetra_LinearProblem &amp;LinearProblem)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~Amesos_Paraklete</name>
      <anchorfile>classAmesos__Paraklete.html</anchorfile>
      <anchor>abfcbb2630fc281973a39a90f5c35fb2d</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SymbolicFactorization</name>
      <anchorfile>classAmesos__Paraklete.html</anchorfile>
      <anchor>acaec23d60f4af50d6cd8940f32d695ae</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumericFactorization</name>
      <anchorfile>classAmesos__Paraklete.html</anchorfile>
      <anchor>a7ae5ca4c8f78d5f5c30cf63240420af2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Solve</name>
      <anchorfile>classAmesos__Paraklete.html</anchorfile>
      <anchor>aadae099e7833d517a978d912454cacf9</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const Epetra_LinearProblem *</type>
      <name>GetProblem</name>
      <anchorfile>classAmesos__Paraklete.html</anchorfile>
      <anchor>a814d430ea2e7051344f04675b274fdc0</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>MatrixShapeOK</name>
      <anchorfile>classAmesos__Paraklete.html</anchorfile>
      <anchor>ae152d1ff30143f9dc020b340caa05e56</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetUseTranspose</name>
      <anchorfile>classAmesos__Paraklete.html</anchorfile>
      <anchor>aa74ea83de7ca2ab46b539b50f1377677</anchor>
      <arglist>(bool UseTranspose_in)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>UseTranspose</name>
      <anchorfile>classAmesos__Paraklete.html</anchorfile>
      <anchor>a91755f382eebd4dd633698a02137e5ee</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_Comm &amp;</type>
      <name>Comm</name>
      <anchorfile>classAmesos__Paraklete.html</anchorfile>
      <anchor>a7a3ded25627bfbd6c1b45895ea54fa64</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetParameters</name>
      <anchorfile>classAmesos__Paraklete.html</anchorfile>
      <anchor>af16bfbe15e55be02a4f018173f6ccdea</anchor>
      <arglist>(Teuchos::ParameterList &amp;ParameterList)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumSymbolicFact</name>
      <anchorfile>classAmesos__Paraklete.html</anchorfile>
      <anchor>a4686db09719a8eb666b92c0dbb88d0a1</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumNumericFact</name>
      <anchorfile>classAmesos__Paraklete.html</anchorfile>
      <anchor>abce2d07dfcc549f96381dc6dc8a66a61</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumSolve</name>
      <anchorfile>classAmesos__Paraklete.html</anchorfile>
      <anchor>a3a35f3dd21885cf3b67423888d8a4049</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>PrintTiming</name>
      <anchorfile>classAmesos__Paraklete.html</anchorfile>
      <anchor>a1c89aa5e7e09e042563f29b46219e283</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>PrintStatus</name>
      <anchorfile>classAmesos__Paraklete.html</anchorfile>
      <anchor>a579d851a4f48430ac09d355bdc4e6124</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>GetTiming</name>
      <anchorfile>classAmesos__Paraklete.html</anchorfile>
      <anchor>a1e52c03952d6a25f94d88cf77a4695af</anchor>
      <arglist>(Teuchos::ParameterList &amp;TimingParameterList) const </arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Amesos_Paraklete</name>
      <anchorfile>classAmesos__Paraklete.html</anchorfile>
      <anchor>ad5d24b4ecccad919b13bda1c7ceff66c</anchor>
      <arglist>(const Epetra_LinearProblem &amp;LinearProblem)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~Amesos_Paraklete</name>
      <anchorfile>classAmesos__Paraklete.html</anchorfile>
      <anchor>abfcbb2630fc281973a39a90f5c35fb2d</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SymbolicFactorization</name>
      <anchorfile>classAmesos__Paraklete.html</anchorfile>
      <anchor>acaec23d60f4af50d6cd8940f32d695ae</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumericFactorization</name>
      <anchorfile>classAmesos__Paraklete.html</anchorfile>
      <anchor>a7ae5ca4c8f78d5f5c30cf63240420af2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Solve</name>
      <anchorfile>classAmesos__Paraklete.html</anchorfile>
      <anchor>aadae099e7833d517a978d912454cacf9</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const Epetra_LinearProblem *</type>
      <name>GetProblem</name>
      <anchorfile>classAmesos__Paraklete.html</anchorfile>
      <anchor>a814d430ea2e7051344f04675b274fdc0</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>MatrixShapeOK</name>
      <anchorfile>classAmesos__Paraklete.html</anchorfile>
      <anchor>ae152d1ff30143f9dc020b340caa05e56</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetUseTranspose</name>
      <anchorfile>classAmesos__Paraklete.html</anchorfile>
      <anchor>aa74ea83de7ca2ab46b539b50f1377677</anchor>
      <arglist>(bool UseTranspose_in)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>UseTranspose</name>
      <anchorfile>classAmesos__Paraklete.html</anchorfile>
      <anchor>a91755f382eebd4dd633698a02137e5ee</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_Comm &amp;</type>
      <name>Comm</name>
      <anchorfile>classAmesos__Paraklete.html</anchorfile>
      <anchor>a7a3ded25627bfbd6c1b45895ea54fa64</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetParameters</name>
      <anchorfile>classAmesos__Paraklete.html</anchorfile>
      <anchor>af16bfbe15e55be02a4f018173f6ccdea</anchor>
      <arglist>(Teuchos::ParameterList &amp;ParameterList)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumSymbolicFact</name>
      <anchorfile>classAmesos__Paraklete.html</anchorfile>
      <anchor>a4686db09719a8eb666b92c0dbb88d0a1</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumNumericFact</name>
      <anchorfile>classAmesos__Paraklete.html</anchorfile>
      <anchor>abce2d07dfcc549f96381dc6dc8a66a61</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumSolve</name>
      <anchorfile>classAmesos__Paraklete.html</anchorfile>
      <anchor>a3a35f3dd21885cf3b67423888d8a4049</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>PrintTiming</name>
      <anchorfile>classAmesos__Paraklete.html</anchorfile>
      <anchor>a1c89aa5e7e09e042563f29b46219e283</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>PrintStatus</name>
      <anchorfile>classAmesos__Paraklete.html</anchorfile>
      <anchor>a579d851a4f48430ac09d355bdc4e6124</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>GetTiming</name>
      <anchorfile>classAmesos__Paraklete.html</anchorfile>
      <anchor>a1e52c03952d6a25f94d88cf77a4695af</anchor>
      <arglist>(Teuchos::ParameterList &amp;TimingParameterList) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Amesos_Paraklete_Pimpl</name>
    <filename>classAmesos__Paraklete__Pimpl.html</filename>
  </compound>
  <compound kind="class">
    <name>Amesos_Pardiso</name>
    <filename>classAmesos__Pardiso.html</filename>
    <base>Amesos_BaseSolver</base>
    <base protection="private">Amesos_Time</base>
    <base protection="private">Amesos_NoCopiable</base>
    <base protection="private">Amesos_Utils</base>
    <base protection="private">Amesos_Control</base>
    <base protection="private">Amesos_Status</base>
    <member kind="function">
      <type></type>
      <name>Amesos_Pardiso</name>
      <anchorfile>classAmesos__Pardiso.html</anchorfile>
      <anchor>a2149a124f7a861ad4aff6dde2d4ca85b</anchor>
      <arglist>(const Epetra_LinearProblem &amp;LinearProblem)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~Amesos_Pardiso</name>
      <anchorfile>classAmesos__Pardiso.html</anchorfile>
      <anchor>a0d193d835e286af7b49f2e939f8b7d3a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SymbolicFactorization</name>
      <anchorfile>classAmesos__Pardiso.html</anchorfile>
      <anchor>acc531a3cfb0832195dcaa3ebf155d687</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumericFactorization</name>
      <anchorfile>classAmesos__Pardiso.html</anchorfile>
      <anchor>a6b282f9463b5ea4a9ec227b6d194c5b1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Solve</name>
      <anchorfile>classAmesos__Pardiso.html</anchorfile>
      <anchor>abec40527e71e475b178508f0dcbbe51c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const Epetra_LinearProblem *</type>
      <name>GetProblem</name>
      <anchorfile>classAmesos__Pardiso.html</anchorfile>
      <anchor>ac15347ebf9f343ca5024b8f34373e103</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>MatrixShapeOK</name>
      <anchorfile>classAmesos__Pardiso.html</anchorfile>
      <anchor>ac9ab6bd6d7071bd7e15ac07068384aca</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetUseTranspose</name>
      <anchorfile>classAmesos__Pardiso.html</anchorfile>
      <anchor>af35e4024bf35ec0c436cd9004de0f70e</anchor>
      <arglist>(bool UseTranspose)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>UseTranspose</name>
      <anchorfile>classAmesos__Pardiso.html</anchorfile>
      <anchor>a2f15e43abaa2dfc25c937fb09e90ea52</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_Comm &amp;</type>
      <name>Comm</name>
      <anchorfile>classAmesos__Pardiso.html</anchorfile>
      <anchor>af56588116b7cccce7ecb187f65b93688</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetParameters</name>
      <anchorfile>classAmesos__Pardiso.html</anchorfile>
      <anchor>a2ebba406f29fa2b53a71f2887b36eb25</anchor>
      <arglist>(Teuchos::ParameterList &amp;ParameterList)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumSymbolicFact</name>
      <anchorfile>classAmesos__Pardiso.html</anchorfile>
      <anchor>afefbf197f4eb8d1ce99f4eba5652edd3</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumNumericFact</name>
      <anchorfile>classAmesos__Pardiso.html</anchorfile>
      <anchor>a830be3418aef03853724b2127fcc472e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumSolve</name>
      <anchorfile>classAmesos__Pardiso.html</anchorfile>
      <anchor>a6ddab6419117bbe3bdd62f3f8186f11f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>PrintTiming</name>
      <anchorfile>classAmesos__Pardiso.html</anchorfile>
      <anchor>a52b607908a5b69f595bfd6fc83f937b1</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>PrintStatus</name>
      <anchorfile>classAmesos__Pardiso.html</anchorfile>
      <anchor>af94653ec0f9aad2b62aca4dadce48f90</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>GetTiming</name>
      <anchorfile>classAmesos__Pardiso.html</anchorfile>
      <anchor>a89da6b0a11045f0d03be3c5a03a861f3</anchor>
      <arglist>(Teuchos::ParameterList &amp;TimingParameterList) const </arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Amesos_Pardiso</name>
      <anchorfile>classAmesos__Pardiso.html</anchorfile>
      <anchor>a2149a124f7a861ad4aff6dde2d4ca85b</anchor>
      <arglist>(const Epetra_LinearProblem &amp;LinearProblem)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~Amesos_Pardiso</name>
      <anchorfile>classAmesos__Pardiso.html</anchorfile>
      <anchor>a0d193d835e286af7b49f2e939f8b7d3a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SymbolicFactorization</name>
      <anchorfile>classAmesos__Pardiso.html</anchorfile>
      <anchor>acc531a3cfb0832195dcaa3ebf155d687</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumericFactorization</name>
      <anchorfile>classAmesos__Pardiso.html</anchorfile>
      <anchor>a6b282f9463b5ea4a9ec227b6d194c5b1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Solve</name>
      <anchorfile>classAmesos__Pardiso.html</anchorfile>
      <anchor>abec40527e71e475b178508f0dcbbe51c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const Epetra_LinearProblem *</type>
      <name>GetProblem</name>
      <anchorfile>classAmesos__Pardiso.html</anchorfile>
      <anchor>ac15347ebf9f343ca5024b8f34373e103</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>MatrixShapeOK</name>
      <anchorfile>classAmesos__Pardiso.html</anchorfile>
      <anchor>ac9ab6bd6d7071bd7e15ac07068384aca</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetUseTranspose</name>
      <anchorfile>classAmesos__Pardiso.html</anchorfile>
      <anchor>af35e4024bf35ec0c436cd9004de0f70e</anchor>
      <arglist>(bool UseTranspose)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>UseTranspose</name>
      <anchorfile>classAmesos__Pardiso.html</anchorfile>
      <anchor>a2f15e43abaa2dfc25c937fb09e90ea52</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_Comm &amp;</type>
      <name>Comm</name>
      <anchorfile>classAmesos__Pardiso.html</anchorfile>
      <anchor>af56588116b7cccce7ecb187f65b93688</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetParameters</name>
      <anchorfile>classAmesos__Pardiso.html</anchorfile>
      <anchor>a2ebba406f29fa2b53a71f2887b36eb25</anchor>
      <arglist>(Teuchos::ParameterList &amp;ParameterList)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumSymbolicFact</name>
      <anchorfile>classAmesos__Pardiso.html</anchorfile>
      <anchor>afefbf197f4eb8d1ce99f4eba5652edd3</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumNumericFact</name>
      <anchorfile>classAmesos__Pardiso.html</anchorfile>
      <anchor>a830be3418aef03853724b2127fcc472e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumSolve</name>
      <anchorfile>classAmesos__Pardiso.html</anchorfile>
      <anchor>a6ddab6419117bbe3bdd62f3f8186f11f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>PrintTiming</name>
      <anchorfile>classAmesos__Pardiso.html</anchorfile>
      <anchor>a52b607908a5b69f595bfd6fc83f937b1</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>PrintStatus</name>
      <anchorfile>classAmesos__Pardiso.html</anchorfile>
      <anchor>af94653ec0f9aad2b62aca4dadce48f90</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>GetTiming</name>
      <anchorfile>classAmesos__Pardiso.html</anchorfile>
      <anchor>a89da6b0a11045f0d03be3c5a03a861f3</anchor>
      <arglist>(Teuchos::ParameterList &amp;TimingParameterList) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Amesos_Reordering</name>
    <filename>classAmesos__Reordering.html</filename>
    <member kind="function" virtualness="pure">
      <type>virtual int *</type>
      <name>GetRowPerm</name>
      <anchorfile>classAmesos__Reordering.html</anchorfile>
      <anchor>ae14365cfcdcff422fbc26a902428a8a7</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int *</type>
      <name>GetColPerm</name>
      <anchorfile>classAmesos__Reordering.html</anchorfile>
      <anchor>a1efb36fbbdd591bd795702fa33642c16</anchor>
      <arglist>()=0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Amesos_Scalapack</name>
    <filename>classAmesos__Scalapack.html</filename>
    <base>Amesos_BaseSolver</base>
    <base protection="private">Amesos_Time</base>
    <base protection="private">Amesos_NoCopiable</base>
    <base protection="private">Amesos_Utils</base>
    <base protection="private">Amesos_Control</base>
    <base protection="private">Amesos_Status</base>
    <member kind="function">
      <type></type>
      <name>Amesos_Scalapack</name>
      <anchorfile>classAmesos__Scalapack.html</anchorfile>
      <anchor>aad7abca49f51b5ecf67d3b3dd8b08f5d</anchor>
      <arglist>(const Epetra_LinearProblem &amp;LinearProblem)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~Amesos_Scalapack</name>
      <anchorfile>classAmesos__Scalapack.html</anchorfile>
      <anchor>a173728ff4feff0ea142762227d8ad622</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SymbolicFactorization</name>
      <anchorfile>classAmesos__Scalapack.html</anchorfile>
      <anchor>acf7acc3f350ed5f6b64d1738df932a2a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumericFactorization</name>
      <anchorfile>classAmesos__Scalapack.html</anchorfile>
      <anchor>a99d836f24af7f263f18bfac5e051aa92</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Solve</name>
      <anchorfile>classAmesos__Scalapack.html</anchorfile>
      <anchor>a52dd144a19ffa88c8610196255aa42b3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const Epetra_LinearProblem *</type>
      <name>GetProblem</name>
      <anchorfile>classAmesos__Scalapack.html</anchorfile>
      <anchor>a867e560d49706d4948d90a712aca38ea</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>MatrixShapeOK</name>
      <anchorfile>classAmesos__Scalapack.html</anchorfile>
      <anchor>a06bb67d0acf1095f8a7e6832e3353dfd</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetUseTranspose</name>
      <anchorfile>classAmesos__Scalapack.html</anchorfile>
      <anchor>a4cb9429bda1b9faba93c643e57fb812b</anchor>
      <arglist>(bool UseTranspose)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>UseTranspose</name>
      <anchorfile>classAmesos__Scalapack.html</anchorfile>
      <anchor>aa3fc710fff74c92c0524c8341c547f72</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_Comm &amp;</type>
      <name>Comm</name>
      <anchorfile>classAmesos__Scalapack.html</anchorfile>
      <anchor>a99c07e1b15f5ceebe31ee80879a70ca6</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetParameters</name>
      <anchorfile>classAmesos__Scalapack.html</anchorfile>
      <anchor>acb153276bca1257e1d9a9fb3b051e7ef</anchor>
      <arglist>(Teuchos::ParameterList &amp;ParameterList)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumSymbolicFact</name>
      <anchorfile>classAmesos__Scalapack.html</anchorfile>
      <anchor>a3ac132c38e14a26de12307cc57dc04d8</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumNumericFact</name>
      <anchorfile>classAmesos__Scalapack.html</anchorfile>
      <anchor>a2bc69d3e27ca85a40933f6410fb730cb</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumSolve</name>
      <anchorfile>classAmesos__Scalapack.html</anchorfile>
      <anchor>abdc5b37eae9f75762b8527b448ddb743</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>PrintTiming</name>
      <anchorfile>classAmesos__Scalapack.html</anchorfile>
      <anchor>a12f6f64e1470305a2960876f3882ab62</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>PrintStatus</name>
      <anchorfile>classAmesos__Scalapack.html</anchorfile>
      <anchor>a527bab554d42be0a40717938e44cfd5a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>GetTiming</name>
      <anchorfile>classAmesos__Scalapack.html</anchorfile>
      <anchor>ad4b92f0b003ff183e3dbfa9e0d7a09a7</anchor>
      <arglist>(Teuchos::ParameterList &amp;TimingParameterList) const </arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Amesos_Scalapack</name>
      <anchorfile>classAmesos__Scalapack.html</anchorfile>
      <anchor>aad7abca49f51b5ecf67d3b3dd8b08f5d</anchor>
      <arglist>(const Epetra_LinearProblem &amp;LinearProblem)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~Amesos_Scalapack</name>
      <anchorfile>classAmesos__Scalapack.html</anchorfile>
      <anchor>a173728ff4feff0ea142762227d8ad622</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SymbolicFactorization</name>
      <anchorfile>classAmesos__Scalapack.html</anchorfile>
      <anchor>acf7acc3f350ed5f6b64d1738df932a2a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumericFactorization</name>
      <anchorfile>classAmesos__Scalapack.html</anchorfile>
      <anchor>a99d836f24af7f263f18bfac5e051aa92</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Solve</name>
      <anchorfile>classAmesos__Scalapack.html</anchorfile>
      <anchor>a52dd144a19ffa88c8610196255aa42b3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const Epetra_LinearProblem *</type>
      <name>GetProblem</name>
      <anchorfile>classAmesos__Scalapack.html</anchorfile>
      <anchor>a867e560d49706d4948d90a712aca38ea</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>MatrixShapeOK</name>
      <anchorfile>classAmesos__Scalapack.html</anchorfile>
      <anchor>a06bb67d0acf1095f8a7e6832e3353dfd</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetUseTranspose</name>
      <anchorfile>classAmesos__Scalapack.html</anchorfile>
      <anchor>a4cb9429bda1b9faba93c643e57fb812b</anchor>
      <arglist>(bool UseTranspose)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>UseTranspose</name>
      <anchorfile>classAmesos__Scalapack.html</anchorfile>
      <anchor>aa3fc710fff74c92c0524c8341c547f72</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_Comm &amp;</type>
      <name>Comm</name>
      <anchorfile>classAmesos__Scalapack.html</anchorfile>
      <anchor>a99c07e1b15f5ceebe31ee80879a70ca6</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetParameters</name>
      <anchorfile>classAmesos__Scalapack.html</anchorfile>
      <anchor>acb153276bca1257e1d9a9fb3b051e7ef</anchor>
      <arglist>(Teuchos::ParameterList &amp;ParameterList)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumSymbolicFact</name>
      <anchorfile>classAmesos__Scalapack.html</anchorfile>
      <anchor>a3ac132c38e14a26de12307cc57dc04d8</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumNumericFact</name>
      <anchorfile>classAmesos__Scalapack.html</anchorfile>
      <anchor>a2bc69d3e27ca85a40933f6410fb730cb</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumSolve</name>
      <anchorfile>classAmesos__Scalapack.html</anchorfile>
      <anchor>abdc5b37eae9f75762b8527b448ddb743</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>PrintTiming</name>
      <anchorfile>classAmesos__Scalapack.html</anchorfile>
      <anchor>a12f6f64e1470305a2960876f3882ab62</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>PrintStatus</name>
      <anchorfile>classAmesos__Scalapack.html</anchorfile>
      <anchor>a527bab554d42be0a40717938e44cfd5a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>GetTiming</name>
      <anchorfile>classAmesos__Scalapack.html</anchorfile>
      <anchor>ad4b92f0b003ff183e3dbfa9e0d7a09a7</anchor>
      <arglist>(Teuchos::ParameterList &amp;TimingParameterList) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Amesos_Scaling</name>
    <filename>classAmesos__Scaling.html</filename>
    <member kind="function" virtualness="pure">
      <type>virtual double *</type>
      <name>GetRowScaling</name>
      <anchorfile>classAmesos__Scaling.html</anchorfile>
      <anchor>aad1a085a0729244d6216598cac843709</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual double *</type>
      <name>GetColScaling</name>
      <anchorfile>classAmesos__Scaling.html</anchorfile>
      <anchor>a20bc67457d3c3ab6af926b25cfc8530d</anchor>
      <arglist>()=0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Amesos_StandardIndex</name>
    <filename>classAmesos__StandardIndex.html</filename>
    <member kind="function">
      <type></type>
      <name>Amesos_StandardIndex</name>
      <anchorfile>classAmesos__StandardIndex.html</anchorfile>
      <anchor>a470a7a03b66ab06eba2910279ddb93da</anchor>
      <arglist>(const Epetra_Map &amp;OriginalMap)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~Amesos_StandardIndex</name>
      <anchorfile>classAmesos__StandardIndex.html</anchorfile>
      <anchor>a6e60fc72ccb62986ba8c42112e4fdd83</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Amesos_Status</name>
    <filename>classAmesos__Status.html</filename>
    <member kind="function">
      <type></type>
      <name>Amesos_Status</name>
      <anchorfile>classAmesos__Status.html</anchorfile>
      <anchor>afccc5e49a7c06f60fdd606953c82ad5e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~Amesos_Status</name>
      <anchorfile>classAmesos__Status.html</anchorfile>
      <anchor>aa1ae581d181155a33eca638f0f8cf9e6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>IsSymbolicFactorizationOK_</name>
      <anchorfile>classAmesos__Status.html</anchorfile>
      <anchor>ad67230c759fd63f996201ccefa1a728a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>IsNumericFactorizationOK_</name>
      <anchorfile>classAmesos__Status.html</anchorfile>
      <anchor>a5c8119948180a5476d8d0592c0b89291</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>PrintTiming_</name>
      <anchorfile>classAmesos__Status.html</anchorfile>
      <anchor>a35bbdb53f2e19575d54e3aadab96749c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>PrintStatus_</name>
      <anchorfile>classAmesos__Status.html</anchorfile>
      <anchor>abcee1de12cb5f078c198ca8866ef1bb3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>ComputeVectorNorms_</name>
      <anchorfile>classAmesos__Status.html</anchorfile>
      <anchor>a3c2881ee30a0a324b78291790c34fbcc</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>ComputeTrueResidual_</name>
      <anchorfile>classAmesos__Status.html</anchorfile>
      <anchor>a9b101c7557162026251eb614b1dc34d1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>verbose_</name>
      <anchorfile>classAmesos__Status.html</anchorfile>
      <anchor>a4195856d9c3f6ec86cfc8f4decccde3b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>debug_</name>
      <anchorfile>classAmesos__Status.html</anchorfile>
      <anchor>a28768a27e3533e5a424a6980d1801318</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>NumSymbolicFact_</name>
      <anchorfile>classAmesos__Status.html</anchorfile>
      <anchor>a4316fb4b1e2e4c636a4e6ebc4399b876</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>NumNumericFact_</name>
      <anchorfile>classAmesos__Status.html</anchorfile>
      <anchor>afc9ebe197300b6a965366aa6749c61c4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>NumSolve_</name>
      <anchorfile>classAmesos__Status.html</anchorfile>
      <anchor>a7f0e20befdec1b3efbc7838b06003b00</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Amesos_Superlu</name>
    <filename>classAmesos__Superlu.html</filename>
    <base>Amesos_BaseSolver</base>
    <base protection="private">Amesos_Time</base>
    <base protection="private">Amesos_NoCopiable</base>
    <base protection="private">Amesos_Utils</base>
    <base protection="private">Amesos_Control</base>
    <base protection="private">Amesos_Status</base>
    <member kind="function">
      <type></type>
      <name>Amesos_Superlu</name>
      <anchorfile>classAmesos__Superlu.html</anchorfile>
      <anchor>a799d5c7652dfecbfca413a4cd82a1e32</anchor>
      <arglist>(const Epetra_LinearProblem &amp;LinearProblem)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~Amesos_Superlu</name>
      <anchorfile>classAmesos__Superlu.html</anchorfile>
      <anchor>a550ab859f07118a5a40f96f433e1d00b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SymbolicFactorization</name>
      <anchorfile>classAmesos__Superlu.html</anchorfile>
      <anchor>addf3b744aec396d34d6084564c6d5ed4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumericFactorization</name>
      <anchorfile>classAmesos__Superlu.html</anchorfile>
      <anchor>ae44fcae13a58830ef0f130cbf39962c3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Solve</name>
      <anchorfile>classAmesos__Superlu.html</anchorfile>
      <anchor>af4bdb2517aa9716c171e41bea17e6c1d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const Epetra_LinearProblem *</type>
      <name>GetProblem</name>
      <anchorfile>classAmesos__Superlu.html</anchorfile>
      <anchor>a2c50cbccf5d8fad054b0166d31ab4d17</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>MatrixShapeOK</name>
      <anchorfile>classAmesos__Superlu.html</anchorfile>
      <anchor>a6079963d10bfaf4b48cc26b402a79f56</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetUseTranspose</name>
      <anchorfile>classAmesos__Superlu.html</anchorfile>
      <anchor>aee27563073165ae953d53968b9d9b7db</anchor>
      <arglist>(bool useTheTranspose)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>UseTranspose</name>
      <anchorfile>classAmesos__Superlu.html</anchorfile>
      <anchor>a1dd146cc41c361a7f2dfef6119aee40e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_Comm &amp;</type>
      <name>Comm</name>
      <anchorfile>classAmesos__Superlu.html</anchorfile>
      <anchor>a07e121b9cff635d3ef42a508f45c0b3e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetParameters</name>
      <anchorfile>classAmesos__Superlu.html</anchorfile>
      <anchor>a4c4969fbae9edfb8d7a3cdac6047e8a3</anchor>
      <arglist>(Teuchos::ParameterList &amp;ParameterList)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumSymbolicFact</name>
      <anchorfile>classAmesos__Superlu.html</anchorfile>
      <anchor>ab777e0172a679dfca3dafb19886d58ff</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumNumericFact</name>
      <anchorfile>classAmesos__Superlu.html</anchorfile>
      <anchor>a33a18398b6e9bda7447766f865f46f28</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumSolve</name>
      <anchorfile>classAmesos__Superlu.html</anchorfile>
      <anchor>ae936c6e4adb5e9a3593edc33763ce1fb</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>PrintTiming</name>
      <anchorfile>classAmesos__Superlu.html</anchorfile>
      <anchor>ad29c6d35eb7789b85fea308cdf565692</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>PrintStatus</name>
      <anchorfile>classAmesos__Superlu.html</anchorfile>
      <anchor>a1eef3eb7ef69493a94abf079748c1c42</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>GetTiming</name>
      <anchorfile>classAmesos__Superlu.html</anchorfile>
      <anchor>a94a3db8098e8ae41e1ac81975403fb0d</anchor>
      <arglist>(Teuchos::ParameterList &amp;TimingParameterList) const </arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Amesos_Superlu</name>
      <anchorfile>classAmesos__Superlu.html</anchorfile>
      <anchor>a799d5c7652dfecbfca413a4cd82a1e32</anchor>
      <arglist>(const Epetra_LinearProblem &amp;LinearProblem)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~Amesos_Superlu</name>
      <anchorfile>classAmesos__Superlu.html</anchorfile>
      <anchor>a550ab859f07118a5a40f96f433e1d00b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SymbolicFactorization</name>
      <anchorfile>classAmesos__Superlu.html</anchorfile>
      <anchor>addf3b744aec396d34d6084564c6d5ed4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumericFactorization</name>
      <anchorfile>classAmesos__Superlu.html</anchorfile>
      <anchor>ae44fcae13a58830ef0f130cbf39962c3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Solve</name>
      <anchorfile>classAmesos__Superlu.html</anchorfile>
      <anchor>af4bdb2517aa9716c171e41bea17e6c1d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const Epetra_LinearProblem *</type>
      <name>GetProblem</name>
      <anchorfile>classAmesos__Superlu.html</anchorfile>
      <anchor>a2c50cbccf5d8fad054b0166d31ab4d17</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>MatrixShapeOK</name>
      <anchorfile>classAmesos__Superlu.html</anchorfile>
      <anchor>a6079963d10bfaf4b48cc26b402a79f56</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetUseTranspose</name>
      <anchorfile>classAmesos__Superlu.html</anchorfile>
      <anchor>aee27563073165ae953d53968b9d9b7db</anchor>
      <arglist>(bool useTheTranspose)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>UseTranspose</name>
      <anchorfile>classAmesos__Superlu.html</anchorfile>
      <anchor>a1dd146cc41c361a7f2dfef6119aee40e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_Comm &amp;</type>
      <name>Comm</name>
      <anchorfile>classAmesos__Superlu.html</anchorfile>
      <anchor>a07e121b9cff635d3ef42a508f45c0b3e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetParameters</name>
      <anchorfile>classAmesos__Superlu.html</anchorfile>
      <anchor>a4c4969fbae9edfb8d7a3cdac6047e8a3</anchor>
      <arglist>(Teuchos::ParameterList &amp;ParameterList)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumSymbolicFact</name>
      <anchorfile>classAmesos__Superlu.html</anchorfile>
      <anchor>ab777e0172a679dfca3dafb19886d58ff</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumNumericFact</name>
      <anchorfile>classAmesos__Superlu.html</anchorfile>
      <anchor>a33a18398b6e9bda7447766f865f46f28</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumSolve</name>
      <anchorfile>classAmesos__Superlu.html</anchorfile>
      <anchor>ae936c6e4adb5e9a3593edc33763ce1fb</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>PrintTiming</name>
      <anchorfile>classAmesos__Superlu.html</anchorfile>
      <anchor>ad29c6d35eb7789b85fea308cdf565692</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>PrintStatus</name>
      <anchorfile>classAmesos__Superlu.html</anchorfile>
      <anchor>a1eef3eb7ef69493a94abf079748c1c42</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>GetTiming</name>
      <anchorfile>classAmesos__Superlu.html</anchorfile>
      <anchor>a94a3db8098e8ae41e1ac81975403fb0d</anchor>
      <arglist>(Teuchos::ParameterList &amp;TimingParameterList) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Amesos_Superlu_Pimpl</name>
    <filename>classAmesos__Superlu__Pimpl.html</filename>
    <member kind="variable">
      <type>gridinfo_t</type>
      <name>grid_</name>
      <anchorfile>classAmesos__Superlu__Pimpl.html</anchorfile>
      <anchor>a703ecd995210726f06e9b824e6b719c6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>superlu_options_t</type>
      <name>options_</name>
      <anchorfile>classAmesos__Superlu__Pimpl.html</anchorfile>
      <anchor>a4dfadb10e60a7348cd2a9db82235e910</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Amesos_Superludist</name>
    <filename>classAmesos__Superludist.html</filename>
    <base>Amesos_BaseSolver</base>
    <base protection="private">Amesos_Time</base>
    <base protection="private">Amesos_NoCopiable</base>
    <base protection="private">Amesos_Utils</base>
    <base protection="private">Amesos_Control</base>
    <base protection="private">Amesos_Status</base>
    <member kind="function">
      <type>int</type>
      <name>SetParameters</name>
      <anchorfile>classAmesos__Superludist.html</anchorfile>
      <anchor>a020b30e93fb7f7e741d34aeacabe71bb</anchor>
      <arglist>(Teuchos::ParameterList &amp;ParameterList)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumSymbolicFact</name>
      <anchorfile>classAmesos__Superludist.html</anchorfile>
      <anchor>a4472253493b50d138791b17e6a1d9032</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumNumericFact</name>
      <anchorfile>classAmesos__Superludist.html</anchorfile>
      <anchor>a5def550a9704e0899e96d3ab699f737e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumSolve</name>
      <anchorfile>classAmesos__Superludist.html</anchorfile>
      <anchor>a52940bc886821f0ea079c184e80267c9</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>PrintTiming</name>
      <anchorfile>classAmesos__Superludist.html</anchorfile>
      <anchor>a393aaa2b6f3cb04269742a638193610d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>PrintStatus</name>
      <anchorfile>classAmesos__Superludist.html</anchorfile>
      <anchor>a17ad45419ccdd36ee763adf4a3d1fadc</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>GetTiming</name>
      <anchorfile>classAmesos__Superludist.html</anchorfile>
      <anchor>a909d8b4297b88e464bfe5533ac043393</anchor>
      <arglist>(Teuchos::ParameterList &amp;TimingParameterList) const </arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Amesos_Superludist</name>
      <anchorfile>classAmesos__Superludist.html</anchorfile>
      <anchor>a67186dcbb8b28d9cbcb801c4dd08a9dc</anchor>
      <arglist>(const Epetra_LinearProblem &amp;LinearProblem)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~Amesos_Superludist</name>
      <anchorfile>classAmesos__Superludist.html</anchorfile>
      <anchor>aa28511b38f5906d0dfcb7adfc35fcff0</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SymbolicFactorization</name>
      <anchorfile>classAmesos__Superludist.html</anchorfile>
      <anchor>a22b613968086b04fa6a1d5b09008b652</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumericFactorization</name>
      <anchorfile>classAmesos__Superludist.html</anchorfile>
      <anchor>ac2299bec535ac0dd5b9711a39d92013d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Solve</name>
      <anchorfile>classAmesos__Superludist.html</anchorfile>
      <anchor>a32c2b2f6690aa0b6911a3d413fe64104</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetUseTranspose</name>
      <anchorfile>classAmesos__Superludist.html</anchorfile>
      <anchor>adfb2349669f0da169036d3752045df34</anchor>
      <arglist>(bool UseTranspose)</arglist>
    </member>
    <member kind="function">
      <type>const Epetra_LinearProblem *</type>
      <name>GetProblem</name>
      <anchorfile>classAmesos__Superludist.html</anchorfile>
      <anchor>a4432c265654db0a7b3732cca005cf48e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>MatrixShapeOK</name>
      <anchorfile>classAmesos__Superludist.html</anchorfile>
      <anchor>acafd503767d8104acddba1d86c732664</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>UseTranspose</name>
      <anchorfile>classAmesos__Superludist.html</anchorfile>
      <anchor>ab76406b9b9533a662f338c28abe38fff</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Amesos_Superludist</name>
      <anchorfile>classAmesos__Superludist.html</anchorfile>
      <anchor>a67186dcbb8b28d9cbcb801c4dd08a9dc</anchor>
      <arglist>(const Epetra_LinearProblem &amp;LinearProblem)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~Amesos_Superludist</name>
      <anchorfile>classAmesos__Superludist.html</anchorfile>
      <anchor>aa28511b38f5906d0dfcb7adfc35fcff0</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SymbolicFactorization</name>
      <anchorfile>classAmesos__Superludist.html</anchorfile>
      <anchor>a22b613968086b04fa6a1d5b09008b652</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumericFactorization</name>
      <anchorfile>classAmesos__Superludist.html</anchorfile>
      <anchor>ac2299bec535ac0dd5b9711a39d92013d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Solve</name>
      <anchorfile>classAmesos__Superludist.html</anchorfile>
      <anchor>a32c2b2f6690aa0b6911a3d413fe64104</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetUseTranspose</name>
      <anchorfile>classAmesos__Superludist.html</anchorfile>
      <anchor>adfb2349669f0da169036d3752045df34</anchor>
      <arglist>(bool UseTranspose)</arglist>
    </member>
    <member kind="function">
      <type>const Epetra_LinearProblem *</type>
      <name>GetProblem</name>
      <anchorfile>classAmesos__Superludist.html</anchorfile>
      <anchor>a4432c265654db0a7b3732cca005cf48e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>MatrixShapeOK</name>
      <anchorfile>classAmesos__Superludist.html</anchorfile>
      <anchor>acafd503767d8104acddba1d86c732664</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>UseTranspose</name>
      <anchorfile>classAmesos__Superludist.html</anchorfile>
      <anchor>ab76406b9b9533a662f338c28abe38fff</anchor>
      <arglist>() const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Amesos_Support</name>
    <filename>classAmesos__Support.html</filename>
  </compound>
  <compound kind="class">
    <name>Amesos_Taucs</name>
    <filename>classAmesos__Taucs.html</filename>
    <base>Amesos_BaseSolver</base>
    <base protection="private">Amesos_Time</base>
    <base protection="private">Amesos_NoCopiable</base>
    <base protection="private">Amesos_Utils</base>
    <base protection="private">Amesos_Control</base>
    <base protection="private">Amesos_Status</base>
    <member kind="function">
      <type></type>
      <name>Amesos_Taucs</name>
      <anchorfile>classAmesos__Taucs.html</anchorfile>
      <anchor>a4df2291c586794b1f8297a01a0d878e1</anchor>
      <arglist>(const Epetra_LinearProblem &amp;LinearProblem)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~Amesos_Taucs</name>
      <anchorfile>classAmesos__Taucs.html</anchorfile>
      <anchor>ade3a9b9d0e870b9e06e983b58ffdba1b</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SymbolicFactorization</name>
      <anchorfile>classAmesos__Taucs.html</anchorfile>
      <anchor>a2313af775dd08f061327a9e42fd51160</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumericFactorization</name>
      <anchorfile>classAmesos__Taucs.html</anchorfile>
      <anchor>a3658b9a5ea28aba867169b560f085bba</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Solve</name>
      <anchorfile>classAmesos__Taucs.html</anchorfile>
      <anchor>af17c37ece3c1e743ac95f4dbd1c7ec54</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const Epetra_LinearProblem *</type>
      <name>GetProblem</name>
      <anchorfile>classAmesos__Taucs.html</anchorfile>
      <anchor>a0e38dc7cbe2d59c17fb13d7b5a682be6</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>MatrixShapeOK</name>
      <anchorfile>classAmesos__Taucs.html</anchorfile>
      <anchor>a7b23a7a4de1ce6292c8f7d68851f8e8c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetUseTranspose</name>
      <anchorfile>classAmesos__Taucs.html</anchorfile>
      <anchor>a3e4e1418042d6e0a9139c457470bde04</anchor>
      <arglist>(bool UseTranspose)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>UseTranspose</name>
      <anchorfile>classAmesos__Taucs.html</anchorfile>
      <anchor>a07a5050c8343cb188dc04b5ca246ec59</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_Comm &amp;</type>
      <name>Comm</name>
      <anchorfile>classAmesos__Taucs.html</anchorfile>
      <anchor>a4686dc7cb807c9f23e5b21494d4a5361</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetParameters</name>
      <anchorfile>classAmesos__Taucs.html</anchorfile>
      <anchor>aa744c391602e0d6cbe8cf90799225bab</anchor>
      <arglist>(Teuchos::ParameterList &amp;ParameterList)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumSymbolicFact</name>
      <anchorfile>classAmesos__Taucs.html</anchorfile>
      <anchor>ac564eddc7ffdb77ee29cf8179db086a1</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumNumericFact</name>
      <anchorfile>classAmesos__Taucs.html</anchorfile>
      <anchor>a73cbaa223bac8611d64050875a0ae880</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumSolve</name>
      <anchorfile>classAmesos__Taucs.html</anchorfile>
      <anchor>a3b0d526bc503c7aa168a71d161762fbf</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>PrintTiming</name>
      <anchorfile>classAmesos__Taucs.html</anchorfile>
      <anchor>aa081b6939fa7938a6201ab1f7d56bc16</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>PrintStatus</name>
      <anchorfile>classAmesos__Taucs.html</anchorfile>
      <anchor>af60b9880e6fea75a0d0dc38f5de2f670</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>GetTiming</name>
      <anchorfile>classAmesos__Taucs.html</anchorfile>
      <anchor>a8de1260521fc95e6203014a0fd3105f7</anchor>
      <arglist>(Teuchos::ParameterList &amp;TimingParameterList) const </arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Amesos_Taucs</name>
      <anchorfile>classAmesos__Taucs.html</anchorfile>
      <anchor>a4df2291c586794b1f8297a01a0d878e1</anchor>
      <arglist>(const Epetra_LinearProblem &amp;LinearProblem)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~Amesos_Taucs</name>
      <anchorfile>classAmesos__Taucs.html</anchorfile>
      <anchor>ade3a9b9d0e870b9e06e983b58ffdba1b</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SymbolicFactorization</name>
      <anchorfile>classAmesos__Taucs.html</anchorfile>
      <anchor>a2313af775dd08f061327a9e42fd51160</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumericFactorization</name>
      <anchorfile>classAmesos__Taucs.html</anchorfile>
      <anchor>a3658b9a5ea28aba867169b560f085bba</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Solve</name>
      <anchorfile>classAmesos__Taucs.html</anchorfile>
      <anchor>af17c37ece3c1e743ac95f4dbd1c7ec54</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const Epetra_LinearProblem *</type>
      <name>GetProblem</name>
      <anchorfile>classAmesos__Taucs.html</anchorfile>
      <anchor>a0e38dc7cbe2d59c17fb13d7b5a682be6</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>MatrixShapeOK</name>
      <anchorfile>classAmesos__Taucs.html</anchorfile>
      <anchor>a7b23a7a4de1ce6292c8f7d68851f8e8c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetUseTranspose</name>
      <anchorfile>classAmesos__Taucs.html</anchorfile>
      <anchor>a3e4e1418042d6e0a9139c457470bde04</anchor>
      <arglist>(bool UseTranspose)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>UseTranspose</name>
      <anchorfile>classAmesos__Taucs.html</anchorfile>
      <anchor>a07a5050c8343cb188dc04b5ca246ec59</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_Comm &amp;</type>
      <name>Comm</name>
      <anchorfile>classAmesos__Taucs.html</anchorfile>
      <anchor>a4686dc7cb807c9f23e5b21494d4a5361</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetParameters</name>
      <anchorfile>classAmesos__Taucs.html</anchorfile>
      <anchor>aa744c391602e0d6cbe8cf90799225bab</anchor>
      <arglist>(Teuchos::ParameterList &amp;ParameterList)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumSymbolicFact</name>
      <anchorfile>classAmesos__Taucs.html</anchorfile>
      <anchor>ac564eddc7ffdb77ee29cf8179db086a1</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumNumericFact</name>
      <anchorfile>classAmesos__Taucs.html</anchorfile>
      <anchor>a73cbaa223bac8611d64050875a0ae880</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumSolve</name>
      <anchorfile>classAmesos__Taucs.html</anchorfile>
      <anchor>a3b0d526bc503c7aa168a71d161762fbf</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>PrintTiming</name>
      <anchorfile>classAmesos__Taucs.html</anchorfile>
      <anchor>aa081b6939fa7938a6201ab1f7d56bc16</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>PrintStatus</name>
      <anchorfile>classAmesos__Taucs.html</anchorfile>
      <anchor>af60b9880e6fea75a0d0dc38f5de2f670</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>GetTiming</name>
      <anchorfile>classAmesos__Taucs.html</anchorfile>
      <anchor>a8de1260521fc95e6203014a0fd3105f7</anchor>
      <arglist>(Teuchos::ParameterList &amp;TimingParameterList) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Amesos_Taucs_Pimpl</name>
    <filename>classAmesos__Taucs__Pimpl.html</filename>
  </compound>
  <compound kind="class">
    <name>Amesos_TestRowMatrix</name>
    <filename>classAmesos__TestRowMatrix.html</filename>
    <member kind="function">
      <type>int</type>
      <name>SetUseTranspose</name>
      <anchorfile>classAmesos__TestRowMatrix.html</anchorfile>
      <anchor>aa0dd8ad2a0e0d20f697edfd059316ba9</anchor>
      <arglist>(bool UseTranspose_in)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>UseTranspose</name>
      <anchorfile>classAmesos__TestRowMatrix.html</anchorfile>
      <anchor>aff576f00719816fafdff6c61e4d9a307</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>HasNormInf</name>
      <anchorfile>classAmesos__TestRowMatrix.html</anchorfile>
      <anchor>a6a3267a1a006b6b4987c4d076c4bd082</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_Comm &amp;</type>
      <name>Comm</name>
      <anchorfile>classAmesos__TestRowMatrix.html</anchorfile>
      <anchor>aa0fdd6bf0a0df6b7b956210bbd6ba90f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_Map &amp;</type>
      <name>OperatorDomainMap</name>
      <anchorfile>classAmesos__TestRowMatrix.html</anchorfile>
      <anchor>af04068608d26b90b9e3e50c5569dd54c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_Map &amp;</type>
      <name>OperatorRangeMap</name>
      <anchorfile>classAmesos__TestRowMatrix.html</anchorfile>
      <anchor>aaaace8b0ac5c189fcbd5e551262eeb99</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Amesos_TestRowMatrix</name>
      <anchorfile>classAmesos__TestRowMatrix.html</anchorfile>
      <anchor>a5cce6ccf96732d98334b29daa4d7fd64</anchor>
      <arglist>(Epetra_RowMatrix *Matrix_in)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~Amesos_TestRowMatrix</name>
      <anchorfile>classAmesos__TestRowMatrix.html</anchorfile>
      <anchor>ac5fd3efd983c9a5a87dad7e4b324f3c9</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>NumMyRowEntries</name>
      <anchorfile>classAmesos__TestRowMatrix.html</anchorfile>
      <anchor>a4e84073943532d912136623a7e117469</anchor>
      <arglist>(int MyRow, int &amp;NumEntries) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>MaxNumEntries</name>
      <anchorfile>classAmesos__TestRowMatrix.html</anchorfile>
      <anchor>ab40397b5a74adeec78e2437a98bdf396</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>ExtractMyRowCopy</name>
      <anchorfile>classAmesos__TestRowMatrix.html</anchorfile>
      <anchor>ac12b2d24c3262be5cc3eb2547ab654e3</anchor>
      <arglist>(int MyRow, int Length, int &amp;NumEntries, double *Values, int *Indices) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>ExtractDiagonalCopy</name>
      <anchorfile>classAmesos__TestRowMatrix.html</anchorfile>
      <anchor>a225bd4851631dd0c0e57045a6d8cfd79</anchor>
      <arglist>(Epetra_Vector &amp;Diagonal) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>Multiply</name>
      <anchorfile>classAmesos__TestRowMatrix.html</anchorfile>
      <anchor>aca446694095076399923d7a059473468</anchor>
      <arglist>(bool TransA, const Epetra_MultiVector &amp;X, Epetra_MultiVector &amp;Y) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>Solve</name>
      <anchorfile>classAmesos__TestRowMatrix.html</anchorfile>
      <anchor>ad1dc06a97897e50c54755e5244ea88d4</anchor>
      <arglist>(bool Upper, bool Trans, bool UnitDiagonal, const Epetra_MultiVector &amp;X, Epetra_MultiVector &amp;Y) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>InvRowSums</name>
      <anchorfile>classAmesos__TestRowMatrix.html</anchorfile>
      <anchor>a41bb560844dee65e4a5f6342c29ae01f</anchor>
      <arglist>(Epetra_Vector &amp;x) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>LeftScale</name>
      <anchorfile>classAmesos__TestRowMatrix.html</anchorfile>
      <anchor>afcec18e75f2955f2601b1b70056bf236</anchor>
      <arglist>(const Epetra_Vector &amp;x)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>InvColSums</name>
      <anchorfile>classAmesos__TestRowMatrix.html</anchorfile>
      <anchor>affca080faea344e27f47f17bc1da86c7</anchor>
      <arglist>(Epetra_Vector &amp;x) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>RightScale</name>
      <anchorfile>classAmesos__TestRowMatrix.html</anchorfile>
      <anchor>a89f67314852b788590375374aaa62cf1</anchor>
      <arglist>(const Epetra_Vector &amp;x)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>Filled</name>
      <anchorfile>classAmesos__TestRowMatrix.html</anchorfile>
      <anchor>a018d7c5fd5a04dffc1370365b7ff09bb</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual double</type>
      <name>NormInf</name>
      <anchorfile>classAmesos__TestRowMatrix.html</anchorfile>
      <anchor>a71eb64d65b7721350cbe2be18c5acc43</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual double</type>
      <name>NormOne</name>
      <anchorfile>classAmesos__TestRowMatrix.html</anchorfile>
      <anchor>a3f430ce8717bf3d22a9e0b90401fe0c5</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>NumGlobalNonzeros</name>
      <anchorfile>classAmesos__TestRowMatrix.html</anchorfile>
      <anchor>a0797f80484438348ed5c52c7c5e024e5</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>NumGlobalRows</name>
      <anchorfile>classAmesos__TestRowMatrix.html</anchorfile>
      <anchor>abb5797df8ea371c574f10435d6f39dff</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>NumGlobalCols</name>
      <anchorfile>classAmesos__TestRowMatrix.html</anchorfile>
      <anchor>a211985381e10c45a23ed1ad1164b2ea4</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>NumGlobalDiagonals</name>
      <anchorfile>classAmesos__TestRowMatrix.html</anchorfile>
      <anchor>a944a834ddec498245a3648955530181a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual long long</type>
      <name>NumGlobalNonzeros64</name>
      <anchorfile>classAmesos__TestRowMatrix.html</anchorfile>
      <anchor>a31b47847cbe8cbd05ef43dc947ed38d1</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual long long</type>
      <name>NumGlobalRows64</name>
      <anchorfile>classAmesos__TestRowMatrix.html</anchorfile>
      <anchor>a0df26068d8f551567e048cc01ca06d7f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual long long</type>
      <name>NumGlobalCols64</name>
      <anchorfile>classAmesos__TestRowMatrix.html</anchorfile>
      <anchor>abcee4fdf19c60e603de8d76f36930793</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual long long</type>
      <name>NumGlobalDiagonals64</name>
      <anchorfile>classAmesos__TestRowMatrix.html</anchorfile>
      <anchor>a4278922ebb59c6b8ed503419620db32f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>NumMyNonzeros</name>
      <anchorfile>classAmesos__TestRowMatrix.html</anchorfile>
      <anchor>a665fa6a0f9d58387c707fd24de13d71d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>NumMyRows</name>
      <anchorfile>classAmesos__TestRowMatrix.html</anchorfile>
      <anchor>ad0b82991e35bad8a6db0b73fdebd3a27</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>NumMyCols</name>
      <anchorfile>classAmesos__TestRowMatrix.html</anchorfile>
      <anchor>a862d9979d20891495769ca3b099427a7</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>NumMyDiagonals</name>
      <anchorfile>classAmesos__TestRowMatrix.html</anchorfile>
      <anchor>a2722bd883e839878b2bbee3d2e72db79</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>LowerTriangular</name>
      <anchorfile>classAmesos__TestRowMatrix.html</anchorfile>
      <anchor>a7d09ae4538f0d0482135142f16431cfd</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>UpperTriangular</name>
      <anchorfile>classAmesos__TestRowMatrix.html</anchorfile>
      <anchor>a91bba87da112b1e4082e2d31c35a4ee8</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const Epetra_Map &amp;</type>
      <name>RowMatrixRowMap</name>
      <anchorfile>classAmesos__TestRowMatrix.html</anchorfile>
      <anchor>a331ae3193a2e1c501ecf176c61cca417</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const Epetra_Map &amp;</type>
      <name>RowMatrixColMap</name>
      <anchorfile>classAmesos__TestRowMatrix.html</anchorfile>
      <anchor>aedfa5045e53cbcf34b5ff2c5916696ff</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const Epetra_Import *</type>
      <name>RowMatrixImporter</name>
      <anchorfile>classAmesos__TestRowMatrix.html</anchorfile>
      <anchor>a85af6fcc231678c3f6bb836eb4dc271f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Amesos_TestRowMatrix</name>
      <anchorfile>classAmesos__TestRowMatrix.html</anchorfile>
      <anchor>a5cce6ccf96732d98334b29daa4d7fd64</anchor>
      <arglist>(Epetra_RowMatrix *Matrix_in)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~Amesos_TestRowMatrix</name>
      <anchorfile>classAmesos__TestRowMatrix.html</anchorfile>
      <anchor>ac5fd3efd983c9a5a87dad7e4b324f3c9</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>NumMyRowEntries</name>
      <anchorfile>classAmesos__TestRowMatrix.html</anchorfile>
      <anchor>a4e84073943532d912136623a7e117469</anchor>
      <arglist>(int MyRow, int &amp;NumEntries) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>MaxNumEntries</name>
      <anchorfile>classAmesos__TestRowMatrix.html</anchorfile>
      <anchor>ab40397b5a74adeec78e2437a98bdf396</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>ExtractMyRowCopy</name>
      <anchorfile>classAmesos__TestRowMatrix.html</anchorfile>
      <anchor>ac12b2d24c3262be5cc3eb2547ab654e3</anchor>
      <arglist>(int MyRow, int Length, int &amp;NumEntries, double *Values, int *Indices) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>ExtractDiagonalCopy</name>
      <anchorfile>classAmesos__TestRowMatrix.html</anchorfile>
      <anchor>a225bd4851631dd0c0e57045a6d8cfd79</anchor>
      <arglist>(Epetra_Vector &amp;Diagonal) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>Multiply</name>
      <anchorfile>classAmesos__TestRowMatrix.html</anchorfile>
      <anchor>aca446694095076399923d7a059473468</anchor>
      <arglist>(bool TransA, const Epetra_MultiVector &amp;X, Epetra_MultiVector &amp;Y) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>Solve</name>
      <anchorfile>classAmesos__TestRowMatrix.html</anchorfile>
      <anchor>ad1dc06a97897e50c54755e5244ea88d4</anchor>
      <arglist>(bool Upper, bool Trans, bool UnitDiagonal, const Epetra_MultiVector &amp;X, Epetra_MultiVector &amp;Y) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>InvRowSums</name>
      <anchorfile>classAmesos__TestRowMatrix.html</anchorfile>
      <anchor>a41bb560844dee65e4a5f6342c29ae01f</anchor>
      <arglist>(Epetra_Vector &amp;x) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>LeftScale</name>
      <anchorfile>classAmesos__TestRowMatrix.html</anchorfile>
      <anchor>afcec18e75f2955f2601b1b70056bf236</anchor>
      <arglist>(const Epetra_Vector &amp;x)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>InvColSums</name>
      <anchorfile>classAmesos__TestRowMatrix.html</anchorfile>
      <anchor>affca080faea344e27f47f17bc1da86c7</anchor>
      <arglist>(Epetra_Vector &amp;x) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>RightScale</name>
      <anchorfile>classAmesos__TestRowMatrix.html</anchorfile>
      <anchor>a89f67314852b788590375374aaa62cf1</anchor>
      <arglist>(const Epetra_Vector &amp;x)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>Filled</name>
      <anchorfile>classAmesos__TestRowMatrix.html</anchorfile>
      <anchor>a018d7c5fd5a04dffc1370365b7ff09bb</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual double</type>
      <name>NormInf</name>
      <anchorfile>classAmesos__TestRowMatrix.html</anchorfile>
      <anchor>a71eb64d65b7721350cbe2be18c5acc43</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual double</type>
      <name>NormOne</name>
      <anchorfile>classAmesos__TestRowMatrix.html</anchorfile>
      <anchor>a3f430ce8717bf3d22a9e0b90401fe0c5</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>NumGlobalNonzeros</name>
      <anchorfile>classAmesos__TestRowMatrix.html</anchorfile>
      <anchor>a0797f80484438348ed5c52c7c5e024e5</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>NumGlobalRows</name>
      <anchorfile>classAmesos__TestRowMatrix.html</anchorfile>
      <anchor>abb5797df8ea371c574f10435d6f39dff</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>NumGlobalCols</name>
      <anchorfile>classAmesos__TestRowMatrix.html</anchorfile>
      <anchor>a211985381e10c45a23ed1ad1164b2ea4</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>NumGlobalDiagonals</name>
      <anchorfile>classAmesos__TestRowMatrix.html</anchorfile>
      <anchor>a944a834ddec498245a3648955530181a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual long long</type>
      <name>NumGlobalNonzeros64</name>
      <anchorfile>classAmesos__TestRowMatrix.html</anchorfile>
      <anchor>a31b47847cbe8cbd05ef43dc947ed38d1</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual long long</type>
      <name>NumGlobalRows64</name>
      <anchorfile>classAmesos__TestRowMatrix.html</anchorfile>
      <anchor>a0df26068d8f551567e048cc01ca06d7f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual long long</type>
      <name>NumGlobalCols64</name>
      <anchorfile>classAmesos__TestRowMatrix.html</anchorfile>
      <anchor>abcee4fdf19c60e603de8d76f36930793</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual long long</type>
      <name>NumGlobalDiagonals64</name>
      <anchorfile>classAmesos__TestRowMatrix.html</anchorfile>
      <anchor>a4278922ebb59c6b8ed503419620db32f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>NumMyNonzeros</name>
      <anchorfile>classAmesos__TestRowMatrix.html</anchorfile>
      <anchor>a665fa6a0f9d58387c707fd24de13d71d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>NumMyRows</name>
      <anchorfile>classAmesos__TestRowMatrix.html</anchorfile>
      <anchor>ad0b82991e35bad8a6db0b73fdebd3a27</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>NumMyCols</name>
      <anchorfile>classAmesos__TestRowMatrix.html</anchorfile>
      <anchor>a862d9979d20891495769ca3b099427a7</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>NumMyDiagonals</name>
      <anchorfile>classAmesos__TestRowMatrix.html</anchorfile>
      <anchor>a2722bd883e839878b2bbee3d2e72db79</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>LowerTriangular</name>
      <anchorfile>classAmesos__TestRowMatrix.html</anchorfile>
      <anchor>a7d09ae4538f0d0482135142f16431cfd</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>UpperTriangular</name>
      <anchorfile>classAmesos__TestRowMatrix.html</anchorfile>
      <anchor>a91bba87da112b1e4082e2d31c35a4ee8</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const Epetra_Map &amp;</type>
      <name>RowMatrixRowMap</name>
      <anchorfile>classAmesos__TestRowMatrix.html</anchorfile>
      <anchor>a331ae3193a2e1c501ecf176c61cca417</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const Epetra_Map &amp;</type>
      <name>RowMatrixColMap</name>
      <anchorfile>classAmesos__TestRowMatrix.html</anchorfile>
      <anchor>aedfa5045e53cbcf34b5ff2c5916696ff</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const Epetra_Import *</type>
      <name>RowMatrixImporter</name>
      <anchorfile>classAmesos__TestRowMatrix.html</anchorfile>
      <anchor>a85af6fcc231678c3f6bb836eb4dc271f</anchor>
      <arglist>() const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Amesos_Time</name>
    <filename>classAmesos__Time.html</filename>
    <member kind="function">
      <type></type>
      <name>Amesos_Time</name>
      <anchorfile>classAmesos__Time.html</anchorfile>
      <anchor>a774ab6ffc874eec2851d3ab355c843d1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~Amesos_Time</name>
      <anchorfile>classAmesos__Time.html</anchorfile>
      <anchor>a83b59632ec354270fc86870328d816c2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>CreateTimer</name>
      <anchorfile>classAmesos__Time.html</anchorfile>
      <anchor>a60540db2c28263c6ca79de910b197c1f</anchor>
      <arglist>(const Epetra_Comm &amp;Comm, int size=1)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>ResetTimer</name>
      <anchorfile>classAmesos__Time.html</anchorfile>
      <anchor>a0ed8b88774c22c39f51ff45e329bcf99</anchor>
      <arglist>(const int timerID=0)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>AddTime</name>
      <anchorfile>classAmesos__Time.html</anchorfile>
      <anchor>a29ebce74f1f3db51895491fd0c7847bc</anchor>
      <arglist>(const std::string what, int dataID, const int timerID=0)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>GetTime</name>
      <anchorfile>classAmesos__Time.html</anchorfile>
      <anchor>a8088d5ae3f97b9a3ef9b8d5dc94aec90</anchor>
      <arglist>(const std::string what) const </arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>GetTime</name>
      <anchorfile>classAmesos__Time.html</anchorfile>
      <anchor>a50e00a473705672114b7f30123be3e79</anchor>
      <arglist>(const int dataID) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>GetTiming</name>
      <anchorfile>classAmesos__Time.html</anchorfile>
      <anchor>accfd3ad389596f13fb11a1d2f01145ec</anchor>
      <arglist>(Teuchos::ParameterList &amp;list) const </arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>Amesos_Time_Data</name>
    <filename>structAmesos__Time__Data.html</filename>
    <member kind="function">
      <type></type>
      <name>Amesos_Time_Data</name>
      <anchorfile>structAmesos__Time__Data.html</anchorfile>
      <anchor>a2c7098c925930efb75979bec1ea92805</anchor>
      <arglist>(std::string timeName, double timeVal)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~Amesos_Time_Data</name>
      <anchorfile>structAmesos__Time__Data.html</anchorfile>
      <anchor>ad4be98a32da56fd9a25674799acc155c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable">
      <type>std::string</type>
      <name>timeName_</name>
      <anchorfile>structAmesos__Time__Data.html</anchorfile>
      <anchor>afb0bc0eab7d7840f829eb862366a2039</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>double</type>
      <name>timeVal_</name>
      <anchorfile>structAmesos__Time__Data.html</anchorfile>
      <anchor>a884146c3225b0a7cc2b02414a7c2f656</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Amesos_Umfpack</name>
    <filename>classAmesos__Umfpack.html</filename>
    <base>Amesos_BaseSolver</base>
    <base protection="private">Amesos_Time</base>
    <base protection="private">Amesos_NoCopiable</base>
    <base protection="private">Amesos_Utils</base>
    <base protection="private">Amesos_Control</base>
    <base protection="private">Amesos_Status</base>
    <member kind="function">
      <type></type>
      <name>Amesos_Umfpack</name>
      <anchorfile>classAmesos__Umfpack.html</anchorfile>
      <anchor>a39555edb03bd32f952b7afba4af2cf6c</anchor>
      <arglist>(const Epetra_LinearProblem &amp;LinearProblem)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~Amesos_Umfpack</name>
      <anchorfile>classAmesos__Umfpack.html</anchorfile>
      <anchor>a8d83b2b254bba054066fa74913f6214a</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SymbolicFactorization</name>
      <anchorfile>classAmesos__Umfpack.html</anchorfile>
      <anchor>aa4f1e153d6fc7ae94f1e4938c5a86aff</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumericFactorization</name>
      <anchorfile>classAmesos__Umfpack.html</anchorfile>
      <anchor>a256ad7bb6173b484931cbe1aeab6fba6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Solve</name>
      <anchorfile>classAmesos__Umfpack.html</anchorfile>
      <anchor>ab8b0db971be2572e8367dc9e0883b185</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const Epetra_LinearProblem *</type>
      <name>GetProblem</name>
      <anchorfile>classAmesos__Umfpack.html</anchorfile>
      <anchor>aa2cc5ce0046170ddbac9e0cb6f9a0d74</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>MatrixShapeOK</name>
      <anchorfile>classAmesos__Umfpack.html</anchorfile>
      <anchor>ac59c7b560b965b60e440ba5a74838ff0</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetUseTranspose</name>
      <anchorfile>classAmesos__Umfpack.html</anchorfile>
      <anchor>a688f612aa1d6ef2b309aa4b2b09a287f</anchor>
      <arglist>(bool UseTranspose_in)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>UseTranspose</name>
      <anchorfile>classAmesos__Umfpack.html</anchorfile>
      <anchor>a27a91f318b0a90950dcfc88c9ebebb54</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_Comm &amp;</type>
      <name>Comm</name>
      <anchorfile>classAmesos__Umfpack.html</anchorfile>
      <anchor>aef10952e772b5549493c3fbcd704c2bc</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>GetRcond</name>
      <anchorfile>classAmesos__Umfpack.html</anchorfile>
      <anchor>ab3350f7f4fdc0f2128b977deec5e430c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetParameters</name>
      <anchorfile>classAmesos__Umfpack.html</anchorfile>
      <anchor>ae5e69beaa8355bf17bc1d9eb7c05a971</anchor>
      <arglist>(Teuchos::ParameterList &amp;ParameterList)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumSymbolicFact</name>
      <anchorfile>classAmesos__Umfpack.html</anchorfile>
      <anchor>a9e574843090413e798d22c93348d947e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumNumericFact</name>
      <anchorfile>classAmesos__Umfpack.html</anchorfile>
      <anchor>a2199cd5ca05f1c9ffc87ed2f815a7530</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumSolve</name>
      <anchorfile>classAmesos__Umfpack.html</anchorfile>
      <anchor>a66722d7670cadfa67c9d0066905cdebe</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>PrintTiming</name>
      <anchorfile>classAmesos__Umfpack.html</anchorfile>
      <anchor>a75691e89ab16a6902c6dd3eb6e817128</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>PrintStatus</name>
      <anchorfile>classAmesos__Umfpack.html</anchorfile>
      <anchor>adbfffe5f2f075a1710d4bd0d89fc06eb</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>GetTiming</name>
      <anchorfile>classAmesos__Umfpack.html</anchorfile>
      <anchor>ae0dc105487e12953737f42c0933ebfdc</anchor>
      <arglist>(Teuchos::ParameterList &amp;TimingParameterList) const </arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Amesos_Umfpack</name>
      <anchorfile>classAmesos__Umfpack.html</anchorfile>
      <anchor>a39555edb03bd32f952b7afba4af2cf6c</anchor>
      <arglist>(const Epetra_LinearProblem &amp;LinearProblem)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~Amesos_Umfpack</name>
      <anchorfile>classAmesos__Umfpack.html</anchorfile>
      <anchor>a8d83b2b254bba054066fa74913f6214a</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SymbolicFactorization</name>
      <anchorfile>classAmesos__Umfpack.html</anchorfile>
      <anchor>aa4f1e153d6fc7ae94f1e4938c5a86aff</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumericFactorization</name>
      <anchorfile>classAmesos__Umfpack.html</anchorfile>
      <anchor>a256ad7bb6173b484931cbe1aeab6fba6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Solve</name>
      <anchorfile>classAmesos__Umfpack.html</anchorfile>
      <anchor>ab8b0db971be2572e8367dc9e0883b185</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const Epetra_LinearProblem *</type>
      <name>GetProblem</name>
      <anchorfile>classAmesos__Umfpack.html</anchorfile>
      <anchor>aa2cc5ce0046170ddbac9e0cb6f9a0d74</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>MatrixShapeOK</name>
      <anchorfile>classAmesos__Umfpack.html</anchorfile>
      <anchor>ac59c7b560b965b60e440ba5a74838ff0</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetUseTranspose</name>
      <anchorfile>classAmesos__Umfpack.html</anchorfile>
      <anchor>a688f612aa1d6ef2b309aa4b2b09a287f</anchor>
      <arglist>(bool UseTranspose_in)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>UseTranspose</name>
      <anchorfile>classAmesos__Umfpack.html</anchorfile>
      <anchor>a27a91f318b0a90950dcfc88c9ebebb54</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_Comm &amp;</type>
      <name>Comm</name>
      <anchorfile>classAmesos__Umfpack.html</anchorfile>
      <anchor>aef10952e772b5549493c3fbcd704c2bc</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>GetRcond</name>
      <anchorfile>classAmesos__Umfpack.html</anchorfile>
      <anchor>ab3350f7f4fdc0f2128b977deec5e430c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetParameters</name>
      <anchorfile>classAmesos__Umfpack.html</anchorfile>
      <anchor>ae5e69beaa8355bf17bc1d9eb7c05a971</anchor>
      <arglist>(Teuchos::ParameterList &amp;ParameterList)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumSymbolicFact</name>
      <anchorfile>classAmesos__Umfpack.html</anchorfile>
      <anchor>a9e574843090413e798d22c93348d947e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumNumericFact</name>
      <anchorfile>classAmesos__Umfpack.html</anchorfile>
      <anchor>a2199cd5ca05f1c9ffc87ed2f815a7530</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumSolve</name>
      <anchorfile>classAmesos__Umfpack.html</anchorfile>
      <anchor>a66722d7670cadfa67c9d0066905cdebe</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>PrintTiming</name>
      <anchorfile>classAmesos__Umfpack.html</anchorfile>
      <anchor>a75691e89ab16a6902c6dd3eb6e817128</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>PrintStatus</name>
      <anchorfile>classAmesos__Umfpack.html</anchorfile>
      <anchor>adbfffe5f2f075a1710d4bd0d89fc06eb</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>GetTiming</name>
      <anchorfile>classAmesos__Umfpack.html</anchorfile>
      <anchor>ae0dc105487e12953737f42c0933ebfdc</anchor>
      <arglist>(Teuchos::ParameterList &amp;TimingParameterList) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Amesos_Utils</name>
    <filename>classAmesos__Utils.html</filename>
    <member kind="function">
      <type></type>
      <name>Amesos_Utils</name>
      <anchorfile>classAmesos__Utils.html</anchorfile>
      <anchor>af7dd078fe17d3531f1a1f77353c473f7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~Amesos_Utils</name>
      <anchorfile>classAmesos__Utils.html</anchorfile>
      <anchor>a285bf0d01534d1e1ddfc530da644b6a8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>ComputeTrueResidual</name>
      <anchorfile>classAmesos__Utils.html</anchorfile>
      <anchor>a6c378ca8290deff2b59c159b8ca8acf6</anchor>
      <arglist>(const Epetra_RowMatrix &amp;Matrix, const Epetra_MultiVector &amp;X, const Epetra_MultiVector &amp;B, const bool UseTranspose, const std::string prefix) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>ComputeVectorNorms</name>
      <anchorfile>classAmesos__Utils.html</anchorfile>
      <anchor>ade3b802b5480a587e4bdc512b7c3bba8</anchor>
      <arglist>(const Epetra_MultiVector &amp;X, const Epetra_MultiVector &amp;B, const std::string prefix) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>PrintLine</name>
      <anchorfile>classAmesos__Utils.html</anchorfile>
      <anchor>a6196b77387c6376a78469afac5eb57ec</anchor>
      <arglist>() const </arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>CColamd_Col_struct</name>
    <filename>structCColamd__Col__struct.html</filename>
  </compound>
  <compound kind="struct">
    <name>CColamd_Row_struct</name>
    <filename>structCColamd__Row__struct.html</filename>
  </compound>
  <compound kind="struct">
    <name>cholmod_common_struct</name>
    <filename>structcholmod__common__struct.html</filename>
    <class kind="struct">cholmod_common_struct::cholmod_method_struct</class>
  </compound>
  <compound kind="struct">
    <name>cholmod_dense_struct</name>
    <filename>structcholmod__dense__struct.html</filename>
  </compound>
  <compound kind="struct">
    <name>cholmod_factor_struct</name>
    <filename>structcholmod__factor__struct.html</filename>
  </compound>
  <compound kind="struct">
    <name>cholmod_common_struct::cholmod_method_struct</name>
    <filename>structcholmod__common__struct_1_1cholmod__method__struct.html</filename>
  </compound>
  <compound kind="struct">
    <name>cholmod_sparse_struct</name>
    <filename>structcholmod__sparse__struct.html</filename>
  </compound>
  <compound kind="struct">
    <name>cholmod_triplet_struct</name>
    <filename>structcholmod__triplet__struct.html</filename>
  </compound>
  <compound kind="struct">
    <name>Colamd_Col_struct</name>
    <filename>structColamd__Col__struct.html</filename>
  </compound>
  <compound kind="struct">
    <name>Colamd_Row_struct</name>
    <filename>structColamd__Row__struct.html</filename>
  </compound>
  <compound kind="class">
    <name>Epetra_SLU</name>
    <filename>classEpetra__SLU.html</filename>
    <member kind="function">
      <type></type>
      <name>Epetra_SLU</name>
      <anchorfile>classEpetra__SLU.html</anchorfile>
      <anchor>aa214e182d8809d4cab80f4152e58bcd8</anchor>
      <arglist>(Epetra_LinearProblem *Problem, int fill_fac=-1, int panel_size=-1, int relax=-1)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~Epetra_SLU</name>
      <anchorfile>classEpetra__SLU.html</anchorfile>
      <anchor>ab16b505bc5d7108cae8e40780088cbbe</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Solve</name>
      <anchorfile>classEpetra__SLU.html</anchorfile>
      <anchor>a9e9ab903fd0623cb47b09fdfcc7438b0</anchor>
      <arglist>(bool Verbose=false, bool Equil=true, bool Factor=true, int perm_type=2, double pivot_thresh=-1, bool Refact=true, bool Trans=false)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Epetra_SLU</name>
      <anchorfile>classEpetra__SLU.html</anchorfile>
      <anchor>aa214e182d8809d4cab80f4152e58bcd8</anchor>
      <arglist>(Epetra_LinearProblem *Problem, int fill_fac=-1, int panel_size=-1, int relax=-1)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~Epetra_SLU</name>
      <anchorfile>classEpetra__SLU.html</anchorfile>
      <anchor>ab16b505bc5d7108cae8e40780088cbbe</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Solve</name>
      <anchorfile>classEpetra__SLU.html</anchorfile>
      <anchor>a9e9ab903fd0623cb47b09fdfcc7438b0</anchor>
      <arglist>(bool Verbose=false, bool Equil=true, bool Factor=true, int perm_type=2, double pivot_thresh=-1, bool Refact=true, bool Trans=false)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>klu_common_struct</name>
    <filename>structklu__common__struct.html</filename>
  </compound>
  <compound kind="struct">
    <name>klu_l_common_struct</name>
    <filename>structklu__l__common__struct.html</filename>
  </compound>
  <compound kind="struct">
    <name>klu_l_numeric</name>
    <filename>structklu__l__numeric.html</filename>
  </compound>
  <compound kind="struct">
    <name>klu_l_symbolic</name>
    <filename>structklu__l__symbolic.html</filename>
  </compound>
  <compound kind="struct">
    <name>klu_numeric</name>
    <filename>structklu__numeric.html</filename>
  </compound>
  <compound kind="struct">
    <name>klu_symbolic</name>
    <filename>structklu__symbolic.html</filename>
  </compound>
  <compound kind="struct">
    <name>paraklete_btf_numeric_struct</name>
    <filename>structparaklete__btf__numeric__struct.html</filename>
  </compound>
  <compound kind="struct">
    <name>paraklete_btf_symbolic_struct</name>
    <filename>structparaklete__btf__symbolic__struct.html</filename>
  </compound>
  <compound kind="struct">
    <name>paraklete_common_struct</name>
    <filename>structparaklete__common__struct.html</filename>
  </compound>
  <compound kind="struct">
    <name>paraklete_node_struct</name>
    <filename>structparaklete__node__struct.html</filename>
  </compound>
  <compound kind="struct">
    <name>paraklete_numeric_struct</name>
    <filename>structparaklete__numeric__struct.html</filename>
  </compound>
  <compound kind="struct">
    <name>paraklete_symbolic_struct</name>
    <filename>structparaklete__symbolic__struct.html</filename>
  </compound>
  <compound kind="struct">
    <name>SLUData</name>
    <filename>classSLUData.html</filename>
  </compound>
  <compound kind="class">
    <name>SpoolesOO</name>
    <filename>classSpoolesOO.html</filename>
  </compound>
  <compound kind="class">
    <name>Superludist2_OO</name>
    <filename>classSuperludist2__OO.html</filename>
    <member kind="function">
      <type></type>
      <name>Superludist2_OO</name>
      <anchorfile>classSuperludist2__OO.html</anchorfile>
      <anchor>a86cac61912f1af8d08ca99da8fa3e496</anchor>
      <arglist>(const Epetra_LinearProblem &amp;LinearProblem)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~Superludist2_OO</name>
      <anchorfile>classSuperludist2__OO.html</anchorfile>
      <anchor>ad0ecc3fef1f97c48e472c085aad017a4</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetTrans</name>
      <anchorfile>classSuperludist2__OO.html</anchorfile>
      <anchor>af03d9d3b7dff4407b8f429b7cc0265f4</anchor>
      <arglist>(bool trans)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>GetTrans</name>
      <anchorfile>classSuperludist2__OO.html</anchorfile>
      <anchor>a32c5681ab7a834a4d85493163d2b2b79</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>CheckInput</name>
      <anchorfile>classSuperludist2__OO.html</anchorfile>
      <anchor>a1db33d164a070fd9967146b6c778eec2</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>Condest</name>
      <anchorfile>classSuperludist2__OO.html</anchorfile>
      <anchor>a6eed1c60679ac8c2484ea20eee00e098</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Solve</name>
      <anchorfile>classSuperludist2__OO.html</anchorfile>
      <anchor>a932195ca8793ce6ec332ca5ee04b4450</anchor>
      <arglist>(bool Factor)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Superludist2_OO</name>
      <anchorfile>classSuperludist2__OO.html</anchorfile>
      <anchor>a86cac61912f1af8d08ca99da8fa3e496</anchor>
      <arglist>(const Epetra_LinearProblem &amp;LinearProblem)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~Superludist2_OO</name>
      <anchorfile>classSuperludist2__OO.html</anchorfile>
      <anchor>ad0ecc3fef1f97c48e472c085aad017a4</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetTrans</name>
      <anchorfile>classSuperludist2__OO.html</anchorfile>
      <anchor>af03d9d3b7dff4407b8f429b7cc0265f4</anchor>
      <arglist>(bool trans)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>GetTrans</name>
      <anchorfile>classSuperludist2__OO.html</anchorfile>
      <anchor>a32c5681ab7a834a4d85493163d2b2b79</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>CheckInput</name>
      <anchorfile>classSuperludist2__OO.html</anchorfile>
      <anchor>a1db33d164a070fd9967146b6c778eec2</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>Condest</name>
      <anchorfile>classSuperludist2__OO.html</anchorfile>
      <anchor>a6eed1c60679ac8c2484ea20eee00e098</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Solve</name>
      <anchorfile>classSuperludist2__OO.html</anchorfile>
      <anchor>a932195ca8793ce6ec332ca5ee04b4450</anchor>
      <arglist>(bool Factor)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>SuperludistOO</name>
    <filename>classSuperludistOO.html</filename>
    <member kind="function">
      <type></type>
      <name>SuperludistOO</name>
      <anchorfile>classSuperludistOO.html</anchorfile>
      <anchor>a28a3ca42130f24df774883b48ff65775</anchor>
      <arglist>(const Epetra_LinearProblem &amp;LinearProblem)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~SuperludistOO</name>
      <anchorfile>classSuperludistOO.html</anchorfile>
      <anchor>a3e287c64830c7ab93a7dd4e93f446443</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetTrans</name>
      <anchorfile>classSuperludistOO.html</anchorfile>
      <anchor>a3de65cdc730f778fc1c3677ea58b97cb</anchor>
      <arglist>(bool trans)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>GetTrans</name>
      <anchorfile>classSuperludistOO.html</anchorfile>
      <anchor>a28055e9d8ddfe18a13331276e16d90f8</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>CheckInput</name>
      <anchorfile>classSuperludistOO.html</anchorfile>
      <anchor>a54a66b1ed740fb19b9a386f0c26b5ae3</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>Condest</name>
      <anchorfile>classSuperludistOO.html</anchorfile>
      <anchor>a5a7b16fb7ac17d1356e93a34c2768750</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Solve</name>
      <anchorfile>classSuperludistOO.html</anchorfile>
      <anchor>a4184368d8d85875e1f1071617ed7273e</anchor>
      <arglist>(bool Factor)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SuperludistOO</name>
      <anchorfile>classSuperludistOO.html</anchorfile>
      <anchor>a28a3ca42130f24df774883b48ff65775</anchor>
      <arglist>(const Epetra_LinearProblem &amp;LinearProblem)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~SuperludistOO</name>
      <anchorfile>classSuperludistOO.html</anchorfile>
      <anchor>a3e287c64830c7ab93a7dd4e93f446443</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetTrans</name>
      <anchorfile>classSuperludistOO.html</anchorfile>
      <anchor>a3de65cdc730f778fc1c3677ea58b97cb</anchor>
      <arglist>(bool trans)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>GetTrans</name>
      <anchorfile>classSuperludistOO.html</anchorfile>
      <anchor>a28055e9d8ddfe18a13331276e16d90f8</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>CheckInput</name>
      <anchorfile>classSuperludistOO.html</anchorfile>
      <anchor>a54a66b1ed740fb19b9a386f0c26b5ae3</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>Condest</name>
      <anchorfile>classSuperludistOO.html</anchorfile>
      <anchor>a5a7b16fb7ac17d1356e93a34c2768750</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Solve</name>
      <anchorfile>classSuperludistOO.html</anchorfile>
      <anchor>a4184368d8d85875e1f1071617ed7273e</anchor>
      <arglist>(bool Factor)</arglist>
    </member>
  </compound>
  <compound kind="page">
    <name>am_factory</name>
    <title></title>
    <filename>am_factory</filename>
  </compound>
  <compound kind="page">
    <name>am_compare</name>
    <title></title>
    <filename>am_compare</filename>
  </compound>
  <compound kind="page">
    <name>am_hb</name>
    <title></title>
    <filename>am_hb</filename>
  </compound>
  <compound kind="page">
    <name>am_readme</name>
    <title>README</title>
    <filename>am_readme</filename>
  </compound>
  <compound kind="page">
    <name>am_manual_testing</name>
    <title>MANUAL TESTING</title>
    <filename>am_manual_testing</filename>
  </compound>
  <compound kind="page">
    <name>am_change_log</name>
    <title>ChangeLog</title>
    <filename>am_change_log</filename>
  </compound>
  <compound kind="page">
    <name>index</name>
    <title>Amesos: An Interface to Serial and Parallel Direct Sparse Solver Packages.</title>
    <filename>index</filename>
    <docanchor file="index" title="Table of Contents">am_toc</docanchor>
    <docanchor file="index" title="Introduction">am_intro</docanchor>
    <docanchor file="index" title="Copyright and licensing of the third party codes">am_copyright</docanchor>
    <docanchor file="index" title="Quick comparison of the Amesos classes">am_comparison</docanchor>
    <docanchor file="index" title="Supported Matrix Formats.">am_matrix</docanchor>
    <docanchor file="index" title="Installing Amesos">am_install</docanchor>
    <docanchor file="index" title="Example of Use of Amesos Classes">am_example</docanchor>
    <docanchor file="index" title="Browse all of Amesos as a single doxygen collection">am_browser</docanchor>
    <docanchor file="index" title="Python support">am_python</docanchor>
    <docanchor file="index" title="Thyra support">am_thyra</docanchor>
    <docanchor file="index" title="Known bugs and future developments">am_future</docanchor>
    <docanchor file="index" title="Incompatibility between old versions of SuperLU">old_incompatibilities</docanchor>
    <docanchor file="index" title="bugs">known_bugs</docanchor>
    <docanchor file="index" title="Final Remarks">am_final</docanchor>
  </compound>
</tagfile>
