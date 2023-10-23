<?xml version='1.0' encoding='UTF-8' standalone='yes' ?>
<tagfile>
  <compound kind="file">
    <name>Ifpack_ShyLU.cpp</name>
    <path>/Users/sscoll/dist/trilinos/packages/shylu/core/src/epetra/</path>
    <filename>Ifpack__ShyLU_8cpp</filename>
    <includes id="Ifpack__ShyLU_8h" name="Ifpack_ShyLU.h" local="yes" imported="no">Ifpack_ShyLU.h</includes>
    <includes id="IQRSolver_8h" name="IQRSolver.h" local="no" imported="no">IQRSolver.h</includes>
  </compound>
  <compound kind="file">
    <name>Ifpack_ShyLU.h</name>
    <path>/Users/sscoll/dist/trilinos/packages/shylu/core/src/epetra/</path>
    <filename>Ifpack__ShyLU_8h</filename>
    <includes id="shylu_8h" name="shylu.h" local="yes" imported="no">shylu.h</includes>
    <includes id="shylu__util_8h" name="shylu_util.h" local="yes" imported="no">shylu_util.h</includes>
    <class kind="class">Ifpack_ShyLU</class>
  </compound>
  <compound kind="file">
    <name>IQRSolver.h</name>
    <path>/Users/sscoll/dist/trilinos/packages/shylu/core/src/epetra/</path>
    <filename>IQRSolver_8h</filename>
    <class kind="class">IQR::IQRSolver</class>
  </compound>
  <compound kind="file">
    <name>shylu.cpp</name>
    <path>/Users/sscoll/dist/trilinos/packages/shylu/core/src/epetra/</path>
    <filename>shylu_8cpp</filename>
    <includes id="shylu__util_8h" name="shylu_util.h" local="yes" imported="no">shylu_util.h</includes>
    <includes id="shylu_8h" name="shylu.h" local="yes" imported="no">shylu.h</includes>
  </compound>
  <compound kind="file">
    <name>shylu.h</name>
    <path>/Users/sscoll/dist/trilinos/packages/shylu/core/src/epetra/</path>
    <filename>shylu_8h</filename>
    <includes id="IQRSolver_8h" name="IQRSolver.h" local="no" imported="no">IQRSolver.h</includes>
    <class kind="struct">shylu_data</class>
    <member kind="function">
      <type>int</type>
      <name>shylu_factor</name>
      <anchorfile>shylu_8h.html</anchorfile>
      <anchor>ab199d6b1ee507383b520507134fda85c</anchor>
      <arglist>(Epetra_CrsMatrix *A, shylu_symbolic *ssym, shylu_data *data, shylu_config *config)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>shylu_symbolic_factor</name>
      <anchorfile>shylu_8h.html</anchorfile>
      <anchor>a83a0211e95ede20f0e493cd142372533</anchor>
      <arglist>(Epetra_CrsMatrix *A, shylu_symbolic *ssym, shylu_data *data, shylu_config *config)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>shylu_solve</name>
      <anchorfile>shylu_8h.html</anchorfile>
      <anchor>a299ce5d3b891e2bb8146fb1eee1d3e67</anchor>
      <arglist>(shylu_symbolic *ssym, shylu_data *data, shylu_config *config, const Epetra_MultiVector &amp;X, Epetra_MultiVector &amp;Y)</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; Epetra_CrsMatrix &gt;</type>
      <name>computeApproxSchur</name>
      <anchorfile>shylu_8h.html</anchorfile>
      <anchor>a231067db2486ce75fa901c70b1b54ab0</anchor>
      <arglist>(shylu_config *config, shylu_symbolic *ssym, Epetra_CrsMatrix *G, Epetra_CrsMatrix *R, Epetra_LinearProblem *LP, Amesos_BaseSolver *solver, Ifpack_Preconditioner *ifSolver, Epetra_CrsMatrix *C, Epetra_Map *localDRowMap)</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; Epetra_CrsMatrix &gt;</type>
      <name>computeApproxWideSchur</name>
      <anchorfile>shylu_8h.html</anchorfile>
      <anchor>a5e9b3d157aa792a04932dd654517de3a</anchor>
      <arglist>(shylu_config *config, shylu_symbolic *ssym, Epetra_CrsMatrix *G, Epetra_CrsMatrix *R, Epetra_LinearProblem *LP, Amesos_BaseSolver *solver, Ifpack_Preconditioner *ifSolver, Epetra_CrsMatrix *C, Epetra_Map *localDRowMap)</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; Epetra_CrsMatrix &gt;</type>
      <name>computeSchur_GuidedProbing</name>
      <anchorfile>shylu_8h.html</anchorfile>
      <anchor>aec801b2b6e1d872a60d8cbc37a15e648</anchor>
      <arglist>(shylu_config *config, shylu_symbolic *ssym, shylu_data *data, Epetra_Map *localDRowMap)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>shylu_debug_manager.hpp</name>
    <path>/Users/sscoll/dist/trilinos/packages/shylu/core/src/epetra/</path>
    <filename>shylu__debug__manager_8hpp</filename>
    <class kind="class">DebugManager</class>
  </compound>
  <compound kind="file">
    <name>shylu_directsolver_interface.cpp</name>
    <path>/Users/sscoll/dist/trilinos/packages/shylu/core/src/epetra/</path>
    <filename>shylu__directsolver__interface_8cpp</filename>
    <includes id="shylu__directsolver__interface__decl_8hpp" name="shylu_directsolver_interface_decl.hpp" local="yes" imported="no">shylu_directsolver_interface_decl.hpp</includes>
    <includes id="shylu__directsolver__interface__def_8hpp" name="shylu_directsolver_interface_def.hpp" local="yes" imported="no">shylu_directsolver_interface_def.hpp</includes>
  </compound>
  <compound kind="file">
    <name>shylu_directsolver_interface.hpp</name>
    <path>/Users/sscoll/dist/trilinos/packages/shylu/core/src/epetra/</path>
    <filename>shylu__directsolver__interface_8hpp</filename>
    <includes id="shylu__directsolver__interface__decl_8hpp" name="shylu_directsolver_interface_decl.hpp" local="yes" imported="no">shylu_directsolver_interface_decl.hpp</includes>
    <includes id="shylu__directsolver__interface__def_8hpp" name="shylu_directsolver_interface_def.hpp" local="yes" imported="no">shylu_directsolver_interface_def.hpp</includes>
  </compound>
  <compound kind="file">
    <name>shylu_directsolver_interface_decl.hpp</name>
    <path>/Users/sscoll/dist/trilinos/packages/shylu/core/src/epetra/</path>
    <filename>shylu__directsolver__interface__decl_8hpp</filename>
    <includes id="shylu_8h" name="shylu.h" local="no" imported="no">shylu.h</includes>
    <includes id="shylu__util_8h" name="shylu_util.h" local="no" imported="no">shylu_util.h</includes>
    <class kind="class">ShyLU::DirectSolverInterface</class>
  </compound>
  <compound kind="file">
    <name>shylu_directsolver_interface_def.hpp</name>
    <path>/Users/sscoll/dist/trilinos/packages/shylu/core/src/epetra/</path>
    <filename>shylu__directsolver__interface__def_8hpp</filename>
    <includes id="shylu__directsolver__interface__decl_8hpp" name="shylu_directsolver_interface_decl.hpp" local="yes" imported="no">shylu_directsolver_interface_decl.hpp</includes>
  </compound>
  <compound kind="file">
    <name>shylu_factor.cpp</name>
    <path>/Users/sscoll/dist/trilinos/packages/shylu/core/src/epetra/</path>
    <filename>shylu__factor_8cpp</filename>
    <includes id="shylu_8h" name="shylu.h" local="yes" imported="no">shylu.h</includes>
    <includes id="shylu__util_8h" name="shylu_util.h" local="yes" imported="no">shylu_util.h</includes>
    <member kind="function">
      <type>int</type>
      <name>shylu_symbolic_factor</name>
      <anchorfile>shylu__factor_8cpp.html</anchorfile>
      <anchor>a83a0211e95ede20f0e493cd142372533</anchor>
      <arglist>(Epetra_CrsMatrix *A, shylu_symbolic *ssym, shylu_data *data, shylu_config *config)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>shylu_factor</name>
      <anchorfile>shylu__factor_8cpp.html</anchorfile>
      <anchor>ab199d6b1ee507383b520507134fda85c</anchor>
      <arglist>(Epetra_CrsMatrix *A, shylu_symbolic *ssym, shylu_data *data, shylu_config *config)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>shylu_partition_interface.cpp</name>
    <path>/Users/sscoll/dist/trilinos/packages/shylu/core/src/epetra/</path>
    <filename>shylu__partition__interface_8cpp</filename>
    <includes id="shylu__partition__interface__decl_8hpp" name="shylu_partition_interface_decl.hpp" local="yes" imported="no">shylu_partition_interface_decl.hpp</includes>
    <includes id="shylu__partition__interface__def_8hpp" name="shylu_partition_interface_def.hpp" local="yes" imported="no">shylu_partition_interface_def.hpp</includes>
  </compound>
  <compound kind="file">
    <name>shylu_partition_interface_decl.hpp</name>
    <path>/Users/sscoll/dist/trilinos/packages/shylu/core/src/epetra/</path>
    <filename>shylu__partition__interface__decl_8hpp</filename>
    <includes id="shylu_8h" name="shylu.h" local="no" imported="no">shylu.h</includes>
    <includes id="shylu__util_8h" name="shylu_util.h" local="no" imported="no">shylu_util.h</includes>
    <class kind="class">ShyLU::PartitionInterface</class>
  </compound>
  <compound kind="file">
    <name>shylu_partition_interface_def.hpp</name>
    <path>/Users/sscoll/dist/trilinos/packages/shylu/core/src/epetra/</path>
    <filename>shylu__partition__interface__def_8hpp</filename>
    <includes id="shylu__partition__interface__decl_8hpp" name="shylu_partition_interface_decl.hpp" local="yes" imported="no">shylu_partition_interface_decl.hpp</includes>
  </compound>
  <compound kind="file">
    <name>shylu_solve.cpp</name>
    <path>/Users/sscoll/dist/trilinos/packages/shylu/core/src/epetra/</path>
    <filename>shylu__solve_8cpp</filename>
    <includes id="shylu__util_8h" name="shylu_util.h" local="yes" imported="no">shylu_util.h</includes>
    <includes id="shylu_8h" name="shylu.h" local="yes" imported="no">shylu.h</includes>
    <member kind="function">
      <type>int</type>
      <name>shylu_solve</name>
      <anchorfile>shylu__solve_8cpp.html</anchorfile>
      <anchor>a299ce5d3b891e2bb8146fb1eee1d3e67</anchor>
      <arglist>(shylu_symbolic *ssym, shylu_data *data, shylu_config *config, const Epetra_MultiVector &amp;X, Epetra_MultiVector &amp;Y)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>shylu_util.cpp</name>
    <path>/Users/sscoll/dist/trilinos/packages/shylu/core/src/epetra/</path>
    <filename>shylu__util_8cpp</filename>
    <includes id="shylu__util_8h" name="shylu_util.h" local="yes" imported="no">shylu_util.h</includes>
  </compound>
  <compound kind="file">
    <name>shylu_util.h</name>
    <path>/Users/sscoll/dist/trilinos/packages/shylu/core/src/epetra/</path>
    <filename>shylu__util_8h</filename>
  </compound>
  <compound kind="class">
    <name>AmesosSchurOperator</name>
    <filename>classAmesosSchurOperator.html</filename>
    <base>Epetra_Operator</base>
    <member kind="function">
      <type></type>
      <name>AmesosSchurOperator</name>
      <anchorfile>classAmesosSchurOperator.html</anchorfile>
      <anchor>a2c4dc013bf16eca2bfd6c785fa4d3116</anchor>
      <arglist>(Epetra_CrsMatrix *A)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~AmesosSchurOperator</name>
      <anchorfile>classAmesosSchurOperator.html</anchorfile>
      <anchor>a4f6455e9b8c17cce4bd88c35880def79</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Initialize</name>
      <anchorfile>classAmesosSchurOperator.html</anchorfile>
      <anchor>a60146b8db38aa4b79b2450d10620dde2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>IsInitialized</name>
      <anchorfile>classAmesosSchurOperator.html</anchorfile>
      <anchor>a9be677f60e33b2f493f64603dc08e700</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Compute</name>
      <anchorfile>classAmesosSchurOperator.html</anchorfile>
      <anchor>ad597ddd13ebf2c1fb0e97ba6ab8d6fe2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>IsComputed</name>
      <anchorfile>classAmesosSchurOperator.html</anchorfile>
      <anchor>a292e0fd9447f18638a347b0639d65918</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetParameters</name>
      <anchorfile>classAmesosSchurOperator.html</anchorfile>
      <anchor>a5176d72fbfc680f0df95100e847e66d6</anchor>
      <arglist>(Teuchos::ParameterList &amp;parameterlist)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>UseTranspose</name>
      <anchorfile>classAmesosSchurOperator.html</anchorfile>
      <anchor>a8de4973b0aefe13f5fbb5f4bab9de28d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ApplyInverse</name>
      <anchorfile>classAmesosSchurOperator.html</anchorfile>
      <anchor>a8d963b9df5276a681d7b376828b0d224</anchor>
      <arglist>(const Epetra_MultiVector &amp;X, Epetra_MultiVector &amp;Y) const </arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>Condest</name>
      <anchorfile>classAmesosSchurOperator.html</anchorfile>
      <anchor>a33ac0cf41469c115b87bd3c08e47d40a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const char *</type>
      <name>Label</name>
      <anchorfile>classAmesosSchurOperator.html</anchorfile>
      <anchor>aa6ae9f0917cf8e92bc5661aa3cfe9db7</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetLabel</name>
      <anchorfile>classAmesosSchurOperator.html</anchorfile>
      <anchor>ac26a405211e6534f1d8039a1096096e3</anchor>
      <arglist>(const char *Label_in)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>NormInf</name>
      <anchorfile>classAmesosSchurOperator.html</anchorfile>
      <anchor>a6922ece5a840ec2a3aa2888d6486775b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>HasNormInf</name>
      <anchorfile>classAmesosSchurOperator.html</anchorfile>
      <anchor>a74e1ade21712101f25c7cb4370167c4b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_Map &amp;</type>
      <name>OperatorDomainMap</name>
      <anchorfile>classAmesosSchurOperator.html</anchorfile>
      <anchor>a1799d722c695099e7ea57f03aebcfccc</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_Map &amp;</type>
      <name>OperatorRangeMap</name>
      <anchorfile>classAmesosSchurOperator.html</anchorfile>
      <anchor>abcb84fa63e0a68eeb3b8bc052b8e6993</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_Comm &amp;</type>
      <name>Comm</name>
      <anchorfile>classAmesosSchurOperator.html</anchorfile>
      <anchor>a72091d44d3e9381853fc9c378e7dedd1</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_RowMatrix &amp;</type>
      <name>Matrix</name>
      <anchorfile>classAmesosSchurOperator.html</anchorfile>
      <anchor>a3625b1007e1a0e610c7fa7be3f4259e0</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual ostream &amp;</type>
      <name>Print</name>
      <anchorfile>classAmesosSchurOperator.html</anchorfile>
      <anchor>a8b0922ff99b8e94cacc8ebdb4729f1a2</anchor>
      <arglist>(ostream &amp;os) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>NumInitialize</name>
      <anchorfile>classAmesosSchurOperator.html</anchorfile>
      <anchor>ab345a96c44d76f6f8e8f40625b391483</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>NumCompute</name>
      <anchorfile>classAmesosSchurOperator.html</anchorfile>
      <anchor>ad6d4dec226976adf998bb6425b864d68</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>NumApplyInverse</name>
      <anchorfile>classAmesosSchurOperator.html</anchorfile>
      <anchor>a75e4d61a8e82dedd5e681fe81f6077cc</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual double</type>
      <name>InitializeTime</name>
      <anchorfile>classAmesosSchurOperator.html</anchorfile>
      <anchor>a67802311ee32bb320e2632f457cbc225</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual double</type>
      <name>ComputeTime</name>
      <anchorfile>classAmesosSchurOperator.html</anchorfile>
      <anchor>a70fe5a3742bb91f9d5b7a5458fa10953</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual double</type>
      <name>ApplyInverseTime</name>
      <anchorfile>classAmesosSchurOperator.html</anchorfile>
      <anchor>a456a9edb0c1fc8fff744440b9e5efa75</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual double</type>
      <name>InitializeFlops</name>
      <anchorfile>classAmesosSchurOperator.html</anchorfile>
      <anchor>a3bce0596431d27fb49b8a76021787b38</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>AmesosSchurOperator</name>
      <anchorfile>classAmesosSchurOperator.html</anchorfile>
      <anchor>a2c4dc013bf16eca2bfd6c785fa4d3116</anchor>
      <arglist>(Epetra_CrsMatrix *A)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~AmesosSchurOperator</name>
      <anchorfile>classAmesosSchurOperator.html</anchorfile>
      <anchor>a4f6455e9b8c17cce4bd88c35880def79</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Initialize</name>
      <anchorfile>classAmesosSchurOperator.html</anchorfile>
      <anchor>a60146b8db38aa4b79b2450d10620dde2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>IsInitialized</name>
      <anchorfile>classAmesosSchurOperator.html</anchorfile>
      <anchor>a9be677f60e33b2f493f64603dc08e700</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Compute</name>
      <anchorfile>classAmesosSchurOperator.html</anchorfile>
      <anchor>ad597ddd13ebf2c1fb0e97ba6ab8d6fe2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>IsComputed</name>
      <anchorfile>classAmesosSchurOperator.html</anchorfile>
      <anchor>a292e0fd9447f18638a347b0639d65918</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetParameters</name>
      <anchorfile>classAmesosSchurOperator.html</anchorfile>
      <anchor>a5176d72fbfc680f0df95100e847e66d6</anchor>
      <arglist>(Teuchos::ParameterList &amp;parameterlist)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>UseTranspose</name>
      <anchorfile>classAmesosSchurOperator.html</anchorfile>
      <anchor>a8de4973b0aefe13f5fbb5f4bab9de28d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ApplyInverse</name>
      <anchorfile>classAmesosSchurOperator.html</anchorfile>
      <anchor>a8d963b9df5276a681d7b376828b0d224</anchor>
      <arglist>(const Epetra_MultiVector &amp;X, Epetra_MultiVector &amp;Y) const </arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>Condest</name>
      <anchorfile>classAmesosSchurOperator.html</anchorfile>
      <anchor>a33ac0cf41469c115b87bd3c08e47d40a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const char *</type>
      <name>Label</name>
      <anchorfile>classAmesosSchurOperator.html</anchorfile>
      <anchor>aa6ae9f0917cf8e92bc5661aa3cfe9db7</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetLabel</name>
      <anchorfile>classAmesosSchurOperator.html</anchorfile>
      <anchor>ac26a405211e6534f1d8039a1096096e3</anchor>
      <arglist>(const char *Label_in)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>NormInf</name>
      <anchorfile>classAmesosSchurOperator.html</anchorfile>
      <anchor>a6922ece5a840ec2a3aa2888d6486775b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>HasNormInf</name>
      <anchorfile>classAmesosSchurOperator.html</anchorfile>
      <anchor>a74e1ade21712101f25c7cb4370167c4b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_Map &amp;</type>
      <name>OperatorDomainMap</name>
      <anchorfile>classAmesosSchurOperator.html</anchorfile>
      <anchor>a1799d722c695099e7ea57f03aebcfccc</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_Map &amp;</type>
      <name>OperatorRangeMap</name>
      <anchorfile>classAmesosSchurOperator.html</anchorfile>
      <anchor>abcb84fa63e0a68eeb3b8bc052b8e6993</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_Comm &amp;</type>
      <name>Comm</name>
      <anchorfile>classAmesosSchurOperator.html</anchorfile>
      <anchor>a72091d44d3e9381853fc9c378e7dedd1</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_RowMatrix &amp;</type>
      <name>Matrix</name>
      <anchorfile>classAmesosSchurOperator.html</anchorfile>
      <anchor>a3625b1007e1a0e610c7fa7be3f4259e0</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual ostream &amp;</type>
      <name>Print</name>
      <anchorfile>classAmesosSchurOperator.html</anchorfile>
      <anchor>a8b0922ff99b8e94cacc8ebdb4729f1a2</anchor>
      <arglist>(ostream &amp;os) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>NumInitialize</name>
      <anchorfile>classAmesosSchurOperator.html</anchorfile>
      <anchor>ab345a96c44d76f6f8e8f40625b391483</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>NumCompute</name>
      <anchorfile>classAmesosSchurOperator.html</anchorfile>
      <anchor>ad6d4dec226976adf998bb6425b864d68</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>NumApplyInverse</name>
      <anchorfile>classAmesosSchurOperator.html</anchorfile>
      <anchor>a75e4d61a8e82dedd5e681fe81f6077cc</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual double</type>
      <name>InitializeTime</name>
      <anchorfile>classAmesosSchurOperator.html</anchorfile>
      <anchor>a67802311ee32bb320e2632f457cbc225</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual double</type>
      <name>ComputeTime</name>
      <anchorfile>classAmesosSchurOperator.html</anchorfile>
      <anchor>a70fe5a3742bb91f9d5b7a5458fa10953</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual double</type>
      <name>ApplyInverseTime</name>
      <anchorfile>classAmesosSchurOperator.html</anchorfile>
      <anchor>a456a9edb0c1fc8fff744440b9e5efa75</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual double</type>
      <name>InitializeFlops</name>
      <anchorfile>classAmesosSchurOperator.html</anchorfile>
      <anchor>a3bce0596431d27fb49b8a76021787b38</anchor>
      <arglist>() const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>DebugManager</name>
    <filename>classDebugManager.html</filename>
  </compound>
  <compound kind="class">
    <name>ShyLU::DirectSolverInterface</name>
    <filename>classShyLU_1_1DirectSolverInterface.html</filename>
    <templarg></templarg>
    <templarg></templarg>
    <member kind="function">
      <type></type>
      <name>DirectSolverInterface</name>
      <anchorfile>classShyLU_1_1DirectSolverInterface.html</anchorfile>
      <anchor>a3c7f6454afa09bbf40dd4bb5c0e995de</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>IQR::GMRESManager</name>
    <filename>classIQR_1_1GMRESManager.html</filename>
    <templarg></templarg>
    <templarg></templarg>
    <templarg></templarg>
    <templarg></templarg>
  </compound>
  <compound kind="struct">
    <name>IQR::IdPreconditioner</name>
    <filename>structIQR_1_1IdPreconditioner.html</filename>
  </compound>
  <compound kind="class">
    <name>Ifpack_ShyLU</name>
    <filename>classIfpack__ShyLU.html</filename>
    <member kind="function">
      <type></type>
      <name>Ifpack_ShyLU</name>
      <anchorfile>classIfpack__ShyLU.html</anchorfile>
      <anchor>a140ded6298dcd1d12c2e127a5ceb414e</anchor>
      <arglist>(Epetra_CrsMatrix *A)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~Ifpack_ShyLU</name>
      <anchorfile>classIfpack__ShyLU.html</anchorfile>
      <anchor>a0382964fb27a54a6afdba46d788e9448</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Initialize</name>
      <anchorfile>classIfpack__ShyLU.html</anchorfile>
      <anchor>ae32e352cb742d2e49ce3092d3534b552</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>IsInitialized</name>
      <anchorfile>classIfpack__ShyLU.html</anchorfile>
      <anchor>a458980dd9357ac7b6000edbded570c32</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Compute</name>
      <anchorfile>classIfpack__ShyLU.html</anchorfile>
      <anchor>ae451ef9cef49f0f507f32e3abdc9ebe7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>IsComputed</name>
      <anchorfile>classIfpack__ShyLU.html</anchorfile>
      <anchor>a50df686f97f97217931c44ac171239cb</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetParameters</name>
      <anchorfile>classIfpack__ShyLU.html</anchorfile>
      <anchor>aee7f12bccf04c966e3aa7825dc3ce6e7</anchor>
      <arglist>(Teuchos::ParameterList &amp;parameterlist)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>UseTranspose</name>
      <anchorfile>classIfpack__ShyLU.html</anchorfile>
      <anchor>a5daf911240b64480875e385ca54c34a0</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ApplyInverse</name>
      <anchorfile>classIfpack__ShyLU.html</anchorfile>
      <anchor>a7a22d81c081a1ea08964f3680a9dcca1</anchor>
      <arglist>(const Epetra_MultiVector &amp;X, Epetra_MultiVector &amp;Y) const </arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>Condest</name>
      <anchorfile>classIfpack__ShyLU.html</anchorfile>
      <anchor>a9c3e3a4ec09c2b0aee035bc55f41a95b</anchor>
      <arglist>(const Ifpack_CondestType CT=Ifpack_Cheap, const int MaxIters=1550, const double Tol=1e-9, Epetra_RowMatrix *Matrix_in=0)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>JustTryIt</name>
      <anchorfile>classIfpack__ShyLU.html</anchorfile>
      <anchor>a0deb651f41fbf6a2efd2f40360fa673e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const char *</type>
      <name>Label</name>
      <anchorfile>classIfpack__ShyLU.html</anchorfile>
      <anchor>a977f5722dd0bd7d50d9b02bac9c1e061</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetLabel</name>
      <anchorfile>classIfpack__ShyLU.html</anchorfile>
      <anchor>ae87b36701b8100d3de8a9735a48f88d4</anchor>
      <arglist>(std::string Label_in)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>NormInf</name>
      <anchorfile>classIfpack__ShyLU.html</anchorfile>
      <anchor>aaed56e4e2b3d4467c8f236e3f687016f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>HasNormInf</name>
      <anchorfile>classIfpack__ShyLU.html</anchorfile>
      <anchor>a608b6ad3a5dabc4939891a9306f4df6b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_Map &amp;</type>
      <name>OperatorDomainMap</name>
      <anchorfile>classIfpack__ShyLU.html</anchorfile>
      <anchor>af085eac695e7420da6b01b9bf963e6f2</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_Map &amp;</type>
      <name>OperatorRangeMap</name>
      <anchorfile>classIfpack__ShyLU.html</anchorfile>
      <anchor>a1d9729fa3f985dcf8a97672a431d45b8</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_Comm &amp;</type>
      <name>Comm</name>
      <anchorfile>classIfpack__ShyLU.html</anchorfile>
      <anchor>a9eac3062fab40c575622cc7851dd8068</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_RowMatrix &amp;</type>
      <name>Matrix</name>
      <anchorfile>classIfpack__ShyLU.html</anchorfile>
      <anchor>aded80e1024918d9b9555cb2c44df92ed</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual ostream &amp;</type>
      <name>Print</name>
      <anchorfile>classIfpack__ShyLU.html</anchorfile>
      <anchor>a9a1d78e3ec0a6d8e3a6e16c7d1e93e45</anchor>
      <arglist>(ostream &amp;os) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>NumInitialize</name>
      <anchorfile>classIfpack__ShyLU.html</anchorfile>
      <anchor>a8294c1c6e5af14162438a5bcdf029758</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>NumCompute</name>
      <anchorfile>classIfpack__ShyLU.html</anchorfile>
      <anchor>aefde81a795743d3259a7d249aff59e60</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>NumApplyInverse</name>
      <anchorfile>classIfpack__ShyLU.html</anchorfile>
      <anchor>a8f4ff4b9fe4f53b2f0755210b87db7a5</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual double</type>
      <name>InitializeTime</name>
      <anchorfile>classIfpack__ShyLU.html</anchorfile>
      <anchor>a354ae67cfcdae5b1912e3a832522b84e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual double</type>
      <name>ComputeTime</name>
      <anchorfile>classIfpack__ShyLU.html</anchorfile>
      <anchor>ad52692e1690011438e6887357bcfff85</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual double</type>
      <name>ApplyInverseTime</name>
      <anchorfile>classIfpack__ShyLU.html</anchorfile>
      <anchor>adf3b2e0895e391927f70fe662270f441</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual double</type>
      <name>InitializeFlops</name>
      <anchorfile>classIfpack__ShyLU.html</anchorfile>
      <anchor>a27158b58dd4903d5f41e2d6f55dead4e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Ifpack_ShyLU</name>
      <anchorfile>classIfpack__ShyLU.html</anchorfile>
      <anchor>a140ded6298dcd1d12c2e127a5ceb414e</anchor>
      <arglist>(Epetra_CrsMatrix *A)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~Ifpack_ShyLU</name>
      <anchorfile>classIfpack__ShyLU.html</anchorfile>
      <anchor>a0382964fb27a54a6afdba46d788e9448</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Initialize</name>
      <anchorfile>classIfpack__ShyLU.html</anchorfile>
      <anchor>ae32e352cb742d2e49ce3092d3534b552</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>IsInitialized</name>
      <anchorfile>classIfpack__ShyLU.html</anchorfile>
      <anchor>a458980dd9357ac7b6000edbded570c32</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Compute</name>
      <anchorfile>classIfpack__ShyLU.html</anchorfile>
      <anchor>ae451ef9cef49f0f507f32e3abdc9ebe7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>IsComputed</name>
      <anchorfile>classIfpack__ShyLU.html</anchorfile>
      <anchor>a50df686f97f97217931c44ac171239cb</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetParameters</name>
      <anchorfile>classIfpack__ShyLU.html</anchorfile>
      <anchor>aee7f12bccf04c966e3aa7825dc3ce6e7</anchor>
      <arglist>(Teuchos::ParameterList &amp;parameterlist)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>UseTranspose</name>
      <anchorfile>classIfpack__ShyLU.html</anchorfile>
      <anchor>a5daf911240b64480875e385ca54c34a0</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ApplyInverse</name>
      <anchorfile>classIfpack__ShyLU.html</anchorfile>
      <anchor>a7a22d81c081a1ea08964f3680a9dcca1</anchor>
      <arglist>(const Epetra_MultiVector &amp;X, Epetra_MultiVector &amp;Y) const </arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>Condest</name>
      <anchorfile>classIfpack__ShyLU.html</anchorfile>
      <anchor>a9c3e3a4ec09c2b0aee035bc55f41a95b</anchor>
      <arglist>(const Ifpack_CondestType CT=Ifpack_Cheap, const int MaxIters=1550, const double Tol=1e-9, Epetra_RowMatrix *Matrix_in=0)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>JustTryIt</name>
      <anchorfile>classIfpack__ShyLU.html</anchorfile>
      <anchor>a0deb651f41fbf6a2efd2f40360fa673e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const char *</type>
      <name>Label</name>
      <anchorfile>classIfpack__ShyLU.html</anchorfile>
      <anchor>a977f5722dd0bd7d50d9b02bac9c1e061</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetLabel</name>
      <anchorfile>classIfpack__ShyLU.html</anchorfile>
      <anchor>ae87b36701b8100d3de8a9735a48f88d4</anchor>
      <arglist>(std::string Label_in)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>NormInf</name>
      <anchorfile>classIfpack__ShyLU.html</anchorfile>
      <anchor>aaed56e4e2b3d4467c8f236e3f687016f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>HasNormInf</name>
      <anchorfile>classIfpack__ShyLU.html</anchorfile>
      <anchor>a608b6ad3a5dabc4939891a9306f4df6b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_Map &amp;</type>
      <name>OperatorDomainMap</name>
      <anchorfile>classIfpack__ShyLU.html</anchorfile>
      <anchor>af085eac695e7420da6b01b9bf963e6f2</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_Map &amp;</type>
      <name>OperatorRangeMap</name>
      <anchorfile>classIfpack__ShyLU.html</anchorfile>
      <anchor>a1d9729fa3f985dcf8a97672a431d45b8</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_Comm &amp;</type>
      <name>Comm</name>
      <anchorfile>classIfpack__ShyLU.html</anchorfile>
      <anchor>a9eac3062fab40c575622cc7851dd8068</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_RowMatrix &amp;</type>
      <name>Matrix</name>
      <anchorfile>classIfpack__ShyLU.html</anchorfile>
      <anchor>aded80e1024918d9b9555cb2c44df92ed</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual ostream &amp;</type>
      <name>Print</name>
      <anchorfile>classIfpack__ShyLU.html</anchorfile>
      <anchor>a9a1d78e3ec0a6d8e3a6e16c7d1e93e45</anchor>
      <arglist>(ostream &amp;os) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>NumInitialize</name>
      <anchorfile>classIfpack__ShyLU.html</anchorfile>
      <anchor>a8294c1c6e5af14162438a5bcdf029758</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>NumCompute</name>
      <anchorfile>classIfpack__ShyLU.html</anchorfile>
      <anchor>aefde81a795743d3259a7d249aff59e60</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>NumApplyInverse</name>
      <anchorfile>classIfpack__ShyLU.html</anchorfile>
      <anchor>a8f4ff4b9fe4f53b2f0755210b87db7a5</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual double</type>
      <name>InitializeTime</name>
      <anchorfile>classIfpack__ShyLU.html</anchorfile>
      <anchor>a354ae67cfcdae5b1912e3a832522b84e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual double</type>
      <name>ComputeTime</name>
      <anchorfile>classIfpack__ShyLU.html</anchorfile>
      <anchor>ad52692e1690011438e6887357bcfff85</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual double</type>
      <name>ApplyInverseTime</name>
      <anchorfile>classIfpack__ShyLU.html</anchorfile>
      <anchor>adf3b2e0895e391927f70fe662270f441</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual double</type>
      <name>InitializeFlops</name>
      <anchorfile>classIfpack__ShyLU.html</anchorfile>
      <anchor>a27158b58dd4903d5f41e2d6f55dead4e</anchor>
      <arglist>() const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>IQR::IQRSolver</name>
    <filename>classIQR_1_1IQRSolver.html</filename>
  </compound>
  <compound kind="class">
    <name>ShyLU::IterativeSolverInterface</name>
    <filename>classShyLU_1_1IterativeSolverInterface.html</filename>
    <templarg></templarg>
    <templarg></templarg>
  </compound>
  <compound kind="class">
    <name>ShyLU::PartitionInterface</name>
    <filename>classShyLU_1_1PartitionInterface.html</filename>
    <templarg></templarg>
    <templarg></templarg>
    <member kind="function">
      <type></type>
      <name>PartitionInterface</name>
      <anchorfile>classShyLU_1_1PartitionInterface.html</anchorfile>
      <anchor>ae2cbe12a5b4cf03bb3daaddf4614336d</anchor>
      <arglist>(Matrix *inA, Teuchos::ParameterList *pList)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>shylu_config</name>
    <filename>structshylu__config.html</filename>
  </compound>
  <compound kind="struct">
    <name>shylu_data</name>
    <filename>structshylu__data.html</filename>
  </compound>
  <compound kind="class">
    <name>ShyLU_Local_Schur_Operator</name>
    <filename>classShyLU__Local__Schur__Operator.html</filename>
    <base virtualness="virtual">Epetra_Operator</base>
  </compound>
  <compound kind="class">
    <name>ShyLU_Probing_Operator</name>
    <filename>classShyLU__Probing__Operator.html</filename>
    <base virtualness="virtual">Epetra_Operator</base>
  </compound>
  <compound kind="struct">
    <name>shylu_symbolic</name>
    <filename>structshylu__symbolic.html</filename>
  </compound>
  <compound kind="page">
    <name>index</name>
    <title>Trilinos/ShyLU:  Scalable/Sparse Hybrid LU</title>
    <filename>index</filename>
    <docanchor file="index" title="Information">Contact</docanchor>
    <docanchor file="index" title="Introduction">ShyLU</docanchor>
    <docanchor file="index" title="State">Current</docanchor>
    <docanchor file="index">Subpackages</docanchor>
    <docanchor file="index" title="Outline">Epetra_outline</docanchor>
    <docanchor file="index" title="Introduction">Epetra_intro</docanchor>
    <docanchor file="index" title="Overview of Epetra.">Epetra_startup</docanchor>
    <docanchor file="index" title="Epetra Classes">Epetra_formulations</docanchor>
    <docanchor file="index" title="Fortran and C Support">Epetra_wrappers</docanchor>
    <docanchor file="index" title="Trilinos and Epetra">Epetra_trilinos</docanchor>
    <docanchor file="index" title="Transition support for current Aztec users">Epetra_aztec2trilinos</docanchor>
    <docanchor file="index" title="Extending Epetra functionality">Epetra_extending</docanchor>
    <docanchor file="index" title="Why not abstract multivector and vector classes?">why_not_abstract_vector</docanchor>
    <docanchor file="index" title="Tutorial lessons">Epetra_example</docanchor>
    <docanchor file="index" title="Epetra adapters for Thyra and PyTrilinos">Epetra_adapters</docanchor>
    <docanchor file="index" title="Browse all of Epetra as a single doxygen collection">Epetra_browser</docanchor>
    <docanchor file="index" title="Introduction">Kokkos_Intro</docanchor>
    <docanchor file="index" title="The %Kokkos programming model">Kokkos_Kokkos</docanchor>
    <docanchor file="index" title="%Kokkos Classic">Kokkos_Classic</docanchor>
    <docanchor file="index" title="Current Linear Solvers">solvers</docanchor>
    <docanchor file="index" title="Belos Contributors">contributors</docanchor>
    <docanchor file="index" title="Where to start">starting_place</docanchor>
    <docanchor file="index" title="Browse all of Belos as a single doxygen collection">belos_browser</docanchor>
    <docanchor file="index" title="Thyra support">belos_thyra</docanchor>
    <docanchor file="index" title="Frequently Asked Questions">belos_faq</docanchor>
    <docanchor file="index" title="Introduction">intro</docanchor>
  </compound>
</tagfile>
