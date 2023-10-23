<?xml version='1.0' encoding='UTF-8' standalone='yes' ?>
<tagfile>
  <compound kind="file">
    <name>BelosThyraAdapter.hpp</name>
    <path>/Users/sscoll/dist/trilinos/packages/stratimikos/adapters/belos/src/</path>
    <filename>BelosThyraAdapter_8hpp</filename>
    <class kind="class">Belos::MultiVecTraits&lt; ScalarType, Thyra::MultiVectorBase&lt; ScalarType &gt; &gt;</class>
    <class kind="class">Belos::OperatorTraits&lt; ScalarType,                                                                                                                                                                           Thyra::MultiVectorBase&lt; ScalarType &gt;,                                                                                                                                                                           Thyra::LinearOpBase&lt; ScalarType &gt; &gt;</class>
  </compound>
  <compound kind="class">
    <name>Thyra::AmesosLinearOpWithSolve</name>
    <filename>classThyra_1_1AmesosLinearOpWithSolve.html</filename>
    <member kind="function">
      <type></type>
      <name>AmesosLinearOpWithSolve</name>
      <anchorfile>classThyra_1_1AmesosLinearOpWithSolve.html</anchorfile>
      <anchor>ae452dda1ae74a0dc7d468b2c5b6ec352</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>AmesosLinearOpWithSolve</name>
      <anchorfile>classThyra_1_1AmesosLinearOpWithSolve.html</anchorfile>
      <anchor>ab31712dd2a4d4852041cd8d18619317e</anchor>
      <arglist>(const Teuchos::RCP&lt; const LinearOpBase&lt; double &gt; &gt; &amp;fwdOp, const Teuchos::RCP&lt; const LinearOpSourceBase&lt; double &gt; &gt; &amp;fwdOpSrc, const Teuchos::RCP&lt; Epetra_LinearProblem &gt; &amp;epetraLP, const Teuchos::RCP&lt; Amesos_BaseSolver &gt; &amp;amesosSolver, const EOpTransp amesosSolverTransp, const double amesosSolverScalar)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initialize</name>
      <anchorfile>classThyra_1_1AmesosLinearOpWithSolve.html</anchorfile>
      <anchor>a94260297aa955c0ec04d47a0bc1f9a07</anchor>
      <arglist>(const Teuchos::RCP&lt; const LinearOpBase&lt; double &gt; &gt; &amp;fwdOp, const Teuchos::RCP&lt; const LinearOpSourceBase&lt; double &gt; &gt; &amp;fwdOpSrc, const Teuchos::RCP&lt; Epetra_LinearProblem &gt; &amp;epetraLP, const Teuchos::RCP&lt; Amesos_BaseSolver &gt; &amp;amesosSolver, const EOpTransp amesosSolverTransp, const double amesosSolverScalar)</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const LinearOpSourceBase&lt; double &gt; &gt;</type>
      <name>extract_fwdOpSrc</name>
      <anchorfile>classThyra_1_1AmesosLinearOpWithSolve.html</anchorfile>
      <anchor>ac42dbf10cfa115e97720362c43a1426c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const LinearOpBase&lt; double &gt; &gt;</type>
      <name>get_fwdOp</name>
      <anchorfile>classThyra_1_1AmesosLinearOpWithSolve.html</anchorfile>
      <anchor>ae669c403e4e7cc30e7b8ff1d4dd19449</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const LinearOpSourceBase&lt; double &gt; &gt;</type>
      <name>get_fwdOpSrc</name>
      <anchorfile>classThyra_1_1AmesosLinearOpWithSolve.html</anchorfile>
      <anchor>a8c289905428a318d00923f812ab55977</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; Epetra_LinearProblem &gt;</type>
      <name>get_epetraLP</name>
      <anchorfile>classThyra_1_1AmesosLinearOpWithSolve.html</anchorfile>
      <anchor>a1a182a032fbc70ea6ccff9f8e1b21267</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; Amesos_BaseSolver &gt;</type>
      <name>get_amesosSolver</name>
      <anchorfile>classThyra_1_1AmesosLinearOpWithSolve.html</anchorfile>
      <anchor>a7eec1bcda9967eafe489cfd5cec30242</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>EOpTransp</type>
      <name>get_amesosSolverTransp</name>
      <anchorfile>classThyra_1_1AmesosLinearOpWithSolve.html</anchorfile>
      <anchor>ae5581a986e9e2bb45b5c96a77486eba1</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>get_amesosSolverScalar</name>
      <anchorfile>classThyra_1_1AmesosLinearOpWithSolve.html</anchorfile>
      <anchor>a411c026f82006abb56ff33b4dd7a06a4</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>uninitialize</name>
      <anchorfile>classThyra_1_1AmesosLinearOpWithSolve.html</anchorfile>
      <anchor>a6987048bb88c011766086ab91389e4b0</anchor>
      <arglist>(Teuchos::RCP&lt; const LinearOpBase&lt; double &gt; &gt; *fwdOp=NULL, Teuchos::RCP&lt; const LinearOpSourceBase&lt; double &gt; &gt; *fwdOpSrc=NULL, Teuchos::RCP&lt; Epetra_LinearProblem &gt; *epetraLP=NULL, Teuchos::RCP&lt; Amesos_BaseSolver &gt; *amesosSolver=NULL, EOpTransp *amesosSolverTransp=NULL, double *amesosSolverScalar=NULL)</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const VectorSpaceBase&lt; double &gt; &gt;</type>
      <name>range</name>
      <anchorfile>classThyra_1_1AmesosLinearOpWithSolve.html</anchorfile>
      <anchor>ac39dac85ea47e04125e4391af7836024</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const VectorSpaceBase&lt; double &gt; &gt;</type>
      <name>domain</name>
      <anchorfile>classThyra_1_1AmesosLinearOpWithSolve.html</anchorfile>
      <anchor>a7e4d5261278dd2fe8f2d513cc91b4f1e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const LinearOpBase&lt; double &gt; &gt;</type>
      <name>clone</name>
      <anchorfile>classThyra_1_1AmesosLinearOpWithSolve.html</anchorfile>
      <anchor>af4549208a21f1a1bb1ec4b405215de34</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>description</name>
      <anchorfile>classThyra_1_1AmesosLinearOpWithSolve.html</anchorfile>
      <anchor>a121dcd5ff8f080ec5e3cdcd936881467</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>describe</name>
      <anchorfile>classThyra_1_1AmesosLinearOpWithSolve.html</anchorfile>
      <anchor>a0439958b804193aa817e45059b21e51f</anchor>
      <arglist>(Teuchos::FancyOStream &amp;out, const Teuchos::EVerbosityLevel verbLevel) const </arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual bool</type>
      <name>opSupportedImpl</name>
      <anchorfile>classThyra_1_1AmesosLinearOpWithSolve.html</anchorfile>
      <anchor>aa8583df9be618bbc7b27d1caefdd39c3</anchor>
      <arglist>(EOpTransp M_trans) const </arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual void</type>
      <name>applyImpl</name>
      <anchorfile>classThyra_1_1AmesosLinearOpWithSolve.html</anchorfile>
      <anchor>a97357b4ed0acb4b6236dee3ba387f237</anchor>
      <arglist>(const EOpTransp M_trans, const MultiVectorBase&lt; double &gt; &amp;X, const Ptr&lt; MultiVectorBase&lt; double &gt; &gt; &amp;Y, const double alpha, const double beta) const </arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual bool</type>
      <name>solveSupportsImpl</name>
      <anchorfile>classThyra_1_1AmesosLinearOpWithSolve.html</anchorfile>
      <anchor>a7f1a7eff8d7b8d3efdbdb108db54e66c</anchor>
      <arglist>(EOpTransp M_trans) const </arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual bool</type>
      <name>solveSupportsSolveMeasureTypeImpl</name>
      <anchorfile>classThyra_1_1AmesosLinearOpWithSolve.html</anchorfile>
      <anchor>a7ddc5b589764d5a8ed7d8e8fb82a2f33</anchor>
      <arglist>(EOpTransp M_trans, const SolveMeasureType &amp;solveMeasureType) const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>SolveStatus&lt; double &gt;</type>
      <name>solveImpl</name>
      <anchorfile>classThyra_1_1AmesosLinearOpWithSolve.html</anchorfile>
      <anchor>aec6ec6b44b38bae714bb854224d9fb83</anchor>
      <arglist>(const EOpTransp M_trans, const MultiVectorBase&lt; double &gt; &amp;B, const Ptr&lt; MultiVectorBase&lt; double &gt; &gt; &amp;X, const Ptr&lt; const SolveCriteria&lt; double &gt; &gt; solveCriteria) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::AmesosLinearOpWithSolveFactory</name>
    <filename>classThyra_1_1AmesosLinearOpWithSolveFactory.html</filename>
    <member kind="variable" static="yes">
      <type>static const std::string</type>
      <name>SolverType_name</name>
      <anchorfile>classThyra_1_1AmesosLinearOpWithSolveFactory.html</anchorfile>
      <anchor>a1960fe3f600a66f8ca63d283f7371ffc</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const std::string</type>
      <name>RefactorizationPolicy_name</name>
      <anchorfile>classThyra_1_1AmesosLinearOpWithSolveFactory.html</anchorfile>
      <anchor>a6c75b2dbeb0b11639489b1a7e53bb20b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const std::string</type>
      <name>ThrowOnPreconditionerInput_name</name>
      <anchorfile>classThyra_1_1AmesosLinearOpWithSolveFactory.html</anchorfile>
      <anchor>a90223741ec2bb1e77d6bf106bc6186f2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const std::string</type>
      <name>Amesos_Settings_name</name>
      <anchorfile>classThyra_1_1AmesosLinearOpWithSolveFactory.html</anchorfile>
      <anchor>ac897afd9468a17b68390ee0f3db0b4f3</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~AmesosLinearOpWithSolveFactory</name>
      <anchorfile>classThyra_1_1AmesosLinearOpWithSolveFactory.html</anchorfile>
      <anchor>a2be578136ad4ba454ec35d8b7c0cb010</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>AmesosLinearOpWithSolveFactory</name>
      <anchorfile>classThyra_1_1AmesosLinearOpWithSolveFactory.html</anchorfile>
      <anchor>a3eb55396bd810a12a84002511e0ec706</anchor>
      <arglist>(const Amesos::ESolverType solverType=Amesos::LAPACK, const Amesos::ERefactorizationPolicy refactorizationPolicy=Amesos::REPIVOT_ON_REFACTORIZATION, const bool throwOnPrecInput=true)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_COMPOSITION_MEMBERS</name>
      <anchorfile>classThyra_1_1AmesosLinearOpWithSolveFactory.html</anchorfile>
      <anchor>a2ed05f9b73c9bcf16468dc7bdc7423c6</anchor>
      <arglist>(EpetraOperatorViewExtractorBase, epetraFwdOpViewExtractor)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isCompatible</name>
      <anchorfile>classThyra_1_1AmesosLinearOpWithSolveFactory.html</anchorfile>
      <anchor>a51e6a3e70dc7e59d4f611fee42f6cc32</anchor>
      <arglist>(const LinearOpSourceBase&lt; double &gt; &amp;fwdOpSrc) const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; LinearOpWithSolveBase&lt; double &gt; &gt;</type>
      <name>createOp</name>
      <anchorfile>classThyra_1_1AmesosLinearOpWithSolveFactory.html</anchorfile>
      <anchor>afa25b690a68f1c3425d305e95c46ce5f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initializeOp</name>
      <anchorfile>classThyra_1_1AmesosLinearOpWithSolveFactory.html</anchorfile>
      <anchor>a352d6ad746ded101524f231c62d58483</anchor>
      <arglist>(const Teuchos::RCP&lt; const LinearOpSourceBase&lt; double &gt; &gt; &amp;fwdOpSrc, LinearOpWithSolveBase&lt; double &gt; *Op, const ESupportSolveUse supportSolveUse) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>supportsPreconditionerInputType</name>
      <anchorfile>classThyra_1_1AmesosLinearOpWithSolveFactory.html</anchorfile>
      <anchor>a1e62fd009f1765c22254f690aa4eb345</anchor>
      <arglist>(const EPreconditionerInputType precOpType) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initializePreconditionedOp</name>
      <anchorfile>classThyra_1_1AmesosLinearOpWithSolveFactory.html</anchorfile>
      <anchor>ab68341e76a270bdd5daa6ff2722b8cf2</anchor>
      <arglist>(const Teuchos::RCP&lt; const LinearOpSourceBase&lt; double &gt; &gt; &amp;fwdOpSrc, const Teuchos::RCP&lt; const PreconditionerBase&lt; double &gt; &gt; &amp;prec, LinearOpWithSolveBase&lt; double &gt; *Op, const ESupportSolveUse supportSolveUse) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initializePreconditionedOp</name>
      <anchorfile>classThyra_1_1AmesosLinearOpWithSolveFactory.html</anchorfile>
      <anchor>aba8e42e9c334aeae930508af18501377</anchor>
      <arglist>(const Teuchos::RCP&lt; const LinearOpSourceBase&lt; double &gt; &gt; &amp;fwdOpSrc, const Teuchos::RCP&lt; const LinearOpSourceBase&lt; double &gt; &gt; &amp;approxFwdOpSrc, LinearOpWithSolveBase&lt; double &gt; *Op, const ESupportSolveUse supportSolveUse) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>uninitializeOp</name>
      <anchorfile>classThyra_1_1AmesosLinearOpWithSolveFactory.html</anchorfile>
      <anchor>a2b410307cbb6ade186e5452a21c1bf5a</anchor>
      <arglist>(LinearOpWithSolveBase&lt; double &gt; *Op, Teuchos::RCP&lt; const LinearOpSourceBase&lt; double &gt; &gt; *fwdOpSrc, Teuchos::RCP&lt; const PreconditionerBase&lt; double &gt; &gt; *prec, Teuchos::RCP&lt; const LinearOpSourceBase&lt; double &gt; &gt; *approxFwdOpSrc, ESupportSolveUse *supportSolveUse) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setParameterList</name>
      <anchorfile>classThyra_1_1AmesosLinearOpWithSolveFactory.html</anchorfile>
      <anchor>aa5dd3d295a6867907d1b284fef649f8e</anchor>
      <arglist>(Teuchos::RCP&lt; Teuchos::ParameterList &gt; const &amp;paramList)</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; Teuchos::ParameterList &gt;</type>
      <name>getNonconstParameterList</name>
      <anchorfile>classThyra_1_1AmesosLinearOpWithSolveFactory.html</anchorfile>
      <anchor>ab4b5e32f8a4a54ed8dcab0652c73d869</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; Teuchos::ParameterList &gt;</type>
      <name>unsetParameterList</name>
      <anchorfile>classThyra_1_1AmesosLinearOpWithSolveFactory.html</anchorfile>
      <anchor>a83ae1a483de9aa40eb11286111694041</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Teuchos::ParameterList &gt;</type>
      <name>getParameterList</name>
      <anchorfile>classThyra_1_1AmesosLinearOpWithSolveFactory.html</anchorfile>
      <anchor>a221be9b121ffb6675c6d96e28ce7e78b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Teuchos::ParameterList &gt;</type>
      <name>getValidParameters</name>
      <anchorfile>classThyra_1_1AmesosLinearOpWithSolveFactory.html</anchorfile>
      <anchor>a4aebcc57384d4a2a1fde306d746dde59</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>description</name>
      <anchorfile>classThyra_1_1AmesosLinearOpWithSolveFactory.html</anchorfile>
      <anchor>afd929734bc04fc8a98eb8ca227a58d2b</anchor>
      <arglist>() const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::AztecOOLinearOpWithSolve</name>
    <filename>classThyra_1_1AztecOOLinearOpWithSolve.html</filename>
    <member kind="function">
      <type></type>
      <name>AztecOOLinearOpWithSolve</name>
      <anchorfile>classThyra_1_1AztecOOLinearOpWithSolve.html</anchorfile>
      <anchor>a3c43c76cb2e4208900e20c1a86db38f7</anchor>
      <arglist>(const int fwdDefaultMaxIterations=400, const double fwdDefaultTol=1e-6, const int adjDefaultMaxIterations=400, const double adjDefaultTol=1e-6, const bool outputEveryRhs=false)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classThyra_1_1AztecOOLinearOpWithSolve.html</anchorfile>
      <anchor>a406b6e017ad5ca4639179d2e034a3164</anchor>
      <arglist>(int, fwdDefaultMaxIterations)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classThyra_1_1AztecOOLinearOpWithSolve.html</anchorfile>
      <anchor>a0be9d8c34b8ad6d6aca85092de470fb7</anchor>
      <arglist>(double, fwdDefaultTol)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classThyra_1_1AztecOOLinearOpWithSolve.html</anchorfile>
      <anchor>afa04f3435f19fe464ec911d73132b7dc</anchor>
      <arglist>(int, adjDefaultMaxIterations)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classThyra_1_1AztecOOLinearOpWithSolve.html</anchorfile>
      <anchor>a9da70b51bc1e3131446b4fe72a4ac358</anchor>
      <arglist>(double, adjDefaultTol)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classThyra_1_1AztecOOLinearOpWithSolve.html</anchorfile>
      <anchor>a2c2f5a93ea2bb86bb298ee6f8336f782</anchor>
      <arglist>(bool, outputEveryRhs)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initialize</name>
      <anchorfile>classThyra_1_1AztecOOLinearOpWithSolve.html</anchorfile>
      <anchor>a0824d9c05409424caeba757c5e81b4c6</anchor>
      <arglist>(const RCP&lt; const LinearOpBase&lt; double &gt; &gt; &amp;fwdOp, const RCP&lt; const LinearOpSourceBase&lt; double &gt; &gt; &amp;fwdOpSrc, const RCP&lt; const PreconditionerBase&lt; double &gt; &gt; &amp;prec, const bool isExternalPrec, const RCP&lt; const LinearOpSourceBase&lt; double &gt; &gt; &amp;approxFwdOpSrc, const RCP&lt; AztecOO &gt; &amp;aztecFwdSolver, const bool allowInexactFwdSolve=false, const RCP&lt; AztecOO &gt; &amp;aztecAdjSolver=Teuchos::null, const bool allowInexactAdjSolve=false, const double aztecSolverScalar=1.0)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const LinearOpSourceBase&lt; double &gt; &gt;</type>
      <name>extract_fwdOpSrc</name>
      <anchorfile>classThyra_1_1AztecOOLinearOpWithSolve.html</anchorfile>
      <anchor>a3c5add7ae231846c59801c6acaf667e6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const PreconditionerBase&lt; double &gt; &gt;</type>
      <name>extract_prec</name>
      <anchorfile>classThyra_1_1AztecOOLinearOpWithSolve.html</anchorfile>
      <anchor>a017213281d0a3f8489e97166736a7f2c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isExternalPrec</name>
      <anchorfile>classThyra_1_1AztecOOLinearOpWithSolve.html</anchorfile>
      <anchor>addbfa7c59790de53863d0e0a6349a2cd</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const LinearOpSourceBase&lt; double &gt; &gt;</type>
      <name>extract_approxFwdOpSrc</name>
      <anchorfile>classThyra_1_1AztecOOLinearOpWithSolve.html</anchorfile>
      <anchor>a6cd46544c6c58e1d06d11f4656645744</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>uninitialize</name>
      <anchorfile>classThyra_1_1AztecOOLinearOpWithSolve.html</anchorfile>
      <anchor>ae66f2a93a0e6cbf17b5441415834eb63</anchor>
      <arglist>(RCP&lt; const LinearOpBase&lt; double &gt; &gt; *fwdOp=NULL, RCP&lt; const LinearOpSourceBase&lt; double &gt; &gt; *fwdOpSrc=NULL, RCP&lt; const PreconditionerBase&lt; double &gt; &gt; *prec=NULL, bool *isExternalPrec=NULL, RCP&lt; const LinearOpSourceBase&lt; double &gt; &gt; *approxFwdOpSrc=NULL, RCP&lt; AztecOO &gt; *aztecFwdSolver=NULL, bool *allowInexactFwdSolve=NULL, RCP&lt; AztecOO &gt; *aztecAdjSolver=NULL, bool *allowInexactAdjSolve=NULL, double *aztecSolverScalar=NULL)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const VectorSpaceBase&lt; double &gt; &gt;</type>
      <name>range</name>
      <anchorfile>classThyra_1_1AztecOOLinearOpWithSolve.html</anchorfile>
      <anchor>aeda7e393ea0e3e49bcd7cd9247b8ddfc</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const VectorSpaceBase&lt; double &gt; &gt;</type>
      <name>domain</name>
      <anchorfile>classThyra_1_1AztecOOLinearOpWithSolve.html</anchorfile>
      <anchor>a0c5ff2062385a4f9eac71a50ba16e0d8</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const LinearOpBase&lt; double &gt; &gt;</type>
      <name>clone</name>
      <anchorfile>classThyra_1_1AztecOOLinearOpWithSolve.html</anchorfile>
      <anchor>ac3c420eeeb2a7a759e46b4be4f2c365b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual bool</type>
      <name>opSupportedImpl</name>
      <anchorfile>classThyra_1_1AztecOOLinearOpWithSolve.html</anchorfile>
      <anchor>a64b1e4266aedf673d662a139030898a4</anchor>
      <arglist>(EOpTransp M_trans) const </arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual void</type>
      <name>applyImpl</name>
      <anchorfile>classThyra_1_1AztecOOLinearOpWithSolve.html</anchorfile>
      <anchor>a39c409a369a7e3214ee63efd7df9cb84</anchor>
      <arglist>(const EOpTransp M_trans, const MultiVectorBase&lt; double &gt; &amp;X, const Ptr&lt; MultiVectorBase&lt; double &gt; &gt; &amp;Y, const double alpha, const double beta) const </arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>description</name>
      <anchorfile>classThyra_1_1AztecOOLinearOpWithSolve.html</anchorfile>
      <anchor>aa4286811ed18154085dc38cbc860218d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>describe</name>
      <anchorfile>classThyra_1_1AztecOOLinearOpWithSolve.html</anchorfile>
      <anchor>a2fe83a1c0e4a171ab2d80de92449ca4a</anchor>
      <arglist>(Teuchos::FancyOStream &amp;out, const Teuchos::EVerbosityLevel verbLevel) const </arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual bool</type>
      <name>solveSupportsImpl</name>
      <anchorfile>classThyra_1_1AztecOOLinearOpWithSolve.html</anchorfile>
      <anchor>a0a405deaf3ade3b8bd15deb502f99afd</anchor>
      <arglist>(EOpTransp M_trans) const </arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual bool</type>
      <name>solveSupportsSolveMeasureTypeImpl</name>
      <anchorfile>classThyra_1_1AztecOOLinearOpWithSolve.html</anchorfile>
      <anchor>ac256c6cd0206ad4648066d735bf7562c</anchor>
      <arglist>(EOpTransp M_trans, const SolveMeasureType &amp;solveMeasureType) const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>SolveStatus&lt; double &gt;</type>
      <name>solveImpl</name>
      <anchorfile>classThyra_1_1AztecOOLinearOpWithSolve.html</anchorfile>
      <anchor>a2c230cf12b56362cfeef821b0ab4dba8</anchor>
      <arglist>(const EOpTransp M_trans, const MultiVectorBase&lt; double &gt; &amp;B, const Ptr&lt; MultiVectorBase&lt; double &gt; &gt; &amp;X, const Ptr&lt; const SolveCriteria&lt; double &gt; &gt; solveCriteria) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::AztecOOLinearOpWithSolveFactory</name>
    <filename>classThyra_1_1AztecOOLinearOpWithSolveFactory.html</filename>
    <member kind="function">
      <type></type>
      <name>AztecOOLinearOpWithSolveFactory</name>
      <anchorfile>classThyra_1_1AztecOOLinearOpWithSolveFactory.html</anchorfile>
      <anchor>a65002923a712a2c723d439316de374fb</anchor>
      <arglist>(Teuchos::RCP&lt; Teuchos::ParameterList &gt; const &amp;paramList=Teuchos::null)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_COMPOSITION_MEMBERS</name>
      <anchorfile>classThyra_1_1AztecOOLinearOpWithSolveFactory.html</anchorfile>
      <anchor>a5ebbf0df65f2de69885abb7d0b5f64c7</anchor>
      <arglist>(EpetraOperatorViewExtractorBase, epetraFwdOpViewExtractor)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>acceptsPreconditionerFactory</name>
      <anchorfile>classThyra_1_1AztecOOLinearOpWithSolveFactory.html</anchorfile>
      <anchor>a7b91815e4815b762011d757dd842f53d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setPreconditionerFactory</name>
      <anchorfile>classThyra_1_1AztecOOLinearOpWithSolveFactory.html</anchorfile>
      <anchor>a989fc992523f52fc7a7818f50d870ed2</anchor>
      <arglist>(const Teuchos::RCP&lt; PreconditionerFactoryBase&lt; double &gt; &gt; &amp;precFactory, const std::string &amp;precFactoryName)</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; PreconditionerFactoryBase&lt; double &gt; &gt;</type>
      <name>getPreconditionerFactory</name>
      <anchorfile>classThyra_1_1AztecOOLinearOpWithSolveFactory.html</anchorfile>
      <anchor>a27f69d9cde7274cf0586a530be81d42d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>unsetPreconditionerFactory</name>
      <anchorfile>classThyra_1_1AztecOOLinearOpWithSolveFactory.html</anchorfile>
      <anchor>a1bceb7b1f19c37c3921b204f93c10666</anchor>
      <arglist>(Teuchos::RCP&lt; PreconditionerFactoryBase&lt; double &gt; &gt; *precFactory, std::string *precFactoryName)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isCompatible</name>
      <anchorfile>classThyra_1_1AztecOOLinearOpWithSolveFactory.html</anchorfile>
      <anchor>ad630f7002ceed65dcab7886b9954eb6d</anchor>
      <arglist>(const LinearOpSourceBase&lt; double &gt; &amp;fwdOpSrc) const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; LinearOpWithSolveBase&lt; double &gt; &gt;</type>
      <name>createOp</name>
      <anchorfile>classThyra_1_1AztecOOLinearOpWithSolveFactory.html</anchorfile>
      <anchor>a7c57afbc76e53a018094170bf2fe0176</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initializeOp</name>
      <anchorfile>classThyra_1_1AztecOOLinearOpWithSolveFactory.html</anchorfile>
      <anchor>aaba1ff96a624980c863bbb53cccbf0ab</anchor>
      <arglist>(const Teuchos::RCP&lt; const LinearOpSourceBase&lt; double &gt; &gt; &amp;fwdOpSrc, LinearOpWithSolveBase&lt; double &gt; *Op, const ESupportSolveUse supportSolveUse) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initializeAndReuseOp</name>
      <anchorfile>classThyra_1_1AztecOOLinearOpWithSolveFactory.html</anchorfile>
      <anchor>a5574e55d1a09b988e3fb68f8f189b337</anchor>
      <arglist>(const Teuchos::RCP&lt; const LinearOpSourceBase&lt; double &gt; &gt; &amp;fwdOpSrc, LinearOpWithSolveBase&lt; double &gt; *Op) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>uninitializeOp</name>
      <anchorfile>classThyra_1_1AztecOOLinearOpWithSolveFactory.html</anchorfile>
      <anchor>a6e32575123e23ba4ae73fd3ac43865f2</anchor>
      <arglist>(LinearOpWithSolveBase&lt; double &gt; *Op, Teuchos::RCP&lt; const LinearOpSourceBase&lt; double &gt; &gt; *fwdOpSrc, Teuchos::RCP&lt; const PreconditionerBase&lt; double &gt; &gt; *prec, Teuchos::RCP&lt; const LinearOpSourceBase&lt; double &gt; &gt; *approxFwdOpSrc, ESupportSolveUse *supportSolveUse) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>supportsPreconditionerInputType</name>
      <anchorfile>classThyra_1_1AztecOOLinearOpWithSolveFactory.html</anchorfile>
      <anchor>a4397b2580e541cadc200f9772810b039</anchor>
      <arglist>(const EPreconditionerInputType precOpType) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initializePreconditionedOp</name>
      <anchorfile>classThyra_1_1AztecOOLinearOpWithSolveFactory.html</anchorfile>
      <anchor>a9e042e28d3efd59e6eea0523338c73e8</anchor>
      <arglist>(const Teuchos::RCP&lt; const LinearOpSourceBase&lt; double &gt; &gt; &amp;fwdOpSrc, const Teuchos::RCP&lt; const PreconditionerBase&lt; double &gt; &gt; &amp;prec, LinearOpWithSolveBase&lt; double &gt; *Op, const ESupportSolveUse supportSolveUse) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initializeApproxPreconditionedOp</name>
      <anchorfile>classThyra_1_1AztecOOLinearOpWithSolveFactory.html</anchorfile>
      <anchor>afe9df7b3457218619e79b3eecc84dcf6</anchor>
      <arglist>(const Teuchos::RCP&lt; const LinearOpSourceBase&lt; double &gt; &gt; &amp;fwdOpSrc, const Teuchos::RCP&lt; const LinearOpSourceBase&lt; double &gt; &gt; &amp;approxFwdOpSrc, LinearOpWithSolveBase&lt; double &gt; *Op, const ESupportSolveUse supportSolveUse) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setParameterList</name>
      <anchorfile>classThyra_1_1AztecOOLinearOpWithSolveFactory.html</anchorfile>
      <anchor>a42880bab9b8dc389f6e4b8b5781500e5</anchor>
      <arglist>(Teuchos::RCP&lt; Teuchos::ParameterList &gt; const &amp;paramList)</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; Teuchos::ParameterList &gt;</type>
      <name>getNonconstParameterList</name>
      <anchorfile>classThyra_1_1AztecOOLinearOpWithSolveFactory.html</anchorfile>
      <anchor>a9f289b5fed018191a8c5bd315b13109b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; Teuchos::ParameterList &gt;</type>
      <name>unsetParameterList</name>
      <anchorfile>classThyra_1_1AztecOOLinearOpWithSolveFactory.html</anchorfile>
      <anchor>aac85e5214e52586a12908ecb428e4bb2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Teuchos::ParameterList &gt;</type>
      <name>getParameterList</name>
      <anchorfile>classThyra_1_1AztecOOLinearOpWithSolveFactory.html</anchorfile>
      <anchor>a427a61476c20d13b69a156a485ae54c5</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Teuchos::ParameterList &gt;</type>
      <name>getValidParameters</name>
      <anchorfile>classThyra_1_1AztecOOLinearOpWithSolveFactory.html</anchorfile>
      <anchor>ac203bc2efe985d53e8452d5f84d2ee47</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>description</name>
      <anchorfile>classThyra_1_1AztecOOLinearOpWithSolveFactory.html</anchorfile>
      <anchor>a3039d2ec093f79c9d5b29d69bc84872e</anchor>
      <arglist>() const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::BelosLinearOpWithSolve</name>
    <filename>classThyra_1_1BelosLinearOpWithSolve.html</filename>
    <templarg>Scalar</templarg>
    <member kind="typedef">
      <type>MultiVectorBase&lt; Scalar &gt;</type>
      <name>MV_t</name>
      <anchorfile>classThyra_1_1BelosLinearOpWithSolve.html</anchorfile>
      <anchor>a59f425a86bdb442ca5c9a094cd41700b</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>LinearOpBase&lt; Scalar &gt;</type>
      <name>LO_t</name>
      <anchorfile>classThyra_1_1BelosLinearOpWithSolve.html</anchorfile>
      <anchor>a551fb9875ba257a5c29ab932b207dd02</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BelosLinearOpWithSolve</name>
      <anchorfile>classThyra_1_1BelosLinearOpWithSolve.html</anchorfile>
      <anchor>a31d6138c4a62f850e96e9e23552377e9</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initialize</name>
      <anchorfile>classThyra_1_1BelosLinearOpWithSolve.html</anchorfile>
      <anchor>afbf257b2dd376565db1b86504d5aab6e</anchor>
      <arglist>(const RCP&lt; Belos::LinearProblem&lt; Scalar, MV_t, LO_t &gt; &gt; &amp;lp, const RCP&lt; Teuchos::ParameterList &gt; &amp;solverPL, const RCP&lt; Belos::SolverManager&lt; Scalar, MV_t, LO_t &gt; &gt; &amp;iterativeSolver, const RCP&lt; const LinearOpSourceBase&lt; Scalar &gt; &gt; &amp;fwdOpSrc, const RCP&lt; const PreconditionerBase&lt; Scalar &gt; &gt; &amp;prec, const bool isExternalPrec, const RCP&lt; const LinearOpSourceBase&lt; Scalar &gt; &gt; &amp;approxFwdOpSrc, const ESupportSolveUse &amp;supportSolveUse, const int convergenceTestFrequency)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const LinearOpSourceBase&lt; Scalar &gt; &gt;</type>
      <name>extract_fwdOpSrc</name>
      <anchorfile>classThyra_1_1BelosLinearOpWithSolve.html</anchorfile>
      <anchor>af2330ccf5ffc9ad20c1c43f55224528f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const PreconditionerBase&lt; Scalar &gt; &gt;</type>
      <name>extract_prec</name>
      <anchorfile>classThyra_1_1BelosLinearOpWithSolve.html</anchorfile>
      <anchor>ac7d07a9979ab7a90950a6c1ac61d5c26</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isExternalPrec</name>
      <anchorfile>classThyra_1_1BelosLinearOpWithSolve.html</anchorfile>
      <anchor>a7b74ea1e2f4b360c8022f06ffab56cf4</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const LinearOpSourceBase&lt; Scalar &gt; &gt;</type>
      <name>extract_approxFwdOpSrc</name>
      <anchorfile>classThyra_1_1BelosLinearOpWithSolve.html</anchorfile>
      <anchor>aa48978b5d461c3376597a3355fbf944e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>ESupportSolveUse</type>
      <name>supportSolveUse</name>
      <anchorfile>classThyra_1_1BelosLinearOpWithSolve.html</anchorfile>
      <anchor>a3d2e8dc5d5f51111ad04da323131a8ad</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>uninitialize</name>
      <anchorfile>classThyra_1_1BelosLinearOpWithSolve.html</anchorfile>
      <anchor>a07e344253998b18c83d0168dda101b7e</anchor>
      <arglist>(RCP&lt; Belos::LinearProblem&lt; Scalar, MV_t, LO_t &gt; &gt; *lp=NULL, RCP&lt; Teuchos::ParameterList &gt; *solverPL=NULL, RCP&lt; Belos::SolverManager&lt; Scalar, MV_t, LO_t &gt; &gt; *iterativeSolver=NULL, RCP&lt; const LinearOpSourceBase&lt; Scalar &gt; &gt; *fwdOpSrc=NULL, RCP&lt; const PreconditionerBase&lt; Scalar &gt; &gt; *prec=NULL, bool *isExternalPrec=NULL, RCP&lt; const LinearOpSourceBase&lt; Scalar &gt; &gt; *approxFwdOpSrc=NULL, ESupportSolveUse *supportSolveUse=NULL)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const VectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>range</name>
      <anchorfile>classThyra_1_1BelosLinearOpWithSolve.html</anchorfile>
      <anchor>aa0f68c03877d45d8f10b2223d1450559</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const VectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>domain</name>
      <anchorfile>classThyra_1_1BelosLinearOpWithSolve.html</anchorfile>
      <anchor>aba7afa9eb9dd627eec4d45ef7c35376a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const LinearOpBase&lt; Scalar &gt; &gt;</type>
      <name>clone</name>
      <anchorfile>classThyra_1_1BelosLinearOpWithSolve.html</anchorfile>
      <anchor>a27eff803c6c72d9ee952d9e89963c273</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual bool</type>
      <name>opSupportedImpl</name>
      <anchorfile>classThyra_1_1BelosLinearOpWithSolve.html</anchorfile>
      <anchor>a02960decd38d3f4a1cc3e87094d2e24b</anchor>
      <arglist>(EOpTransp M_trans) const </arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual void</type>
      <name>applyImpl</name>
      <anchorfile>classThyra_1_1BelosLinearOpWithSolve.html</anchorfile>
      <anchor>a70e68e72a2127992ecfd2c95d8213875</anchor>
      <arglist>(const EOpTransp M_trans, const MultiVectorBase&lt; Scalar &gt; &amp;X, const Ptr&lt; MultiVectorBase&lt; Scalar &gt; &gt; &amp;Y, const Scalar alpha, const Scalar beta) const </arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>description</name>
      <anchorfile>classThyra_1_1BelosLinearOpWithSolve.html</anchorfile>
      <anchor>ab6a9f2f13c2efccab1873b15ead7b6b4</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>describe</name>
      <anchorfile>classThyra_1_1BelosLinearOpWithSolve.html</anchorfile>
      <anchor>ae4a093b0627a1e9f469ea91fd32a91ef</anchor>
      <arglist>(Teuchos::FancyOStream &amp;out, const Teuchos::EVerbosityLevel verbLevel) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setParameterList</name>
      <anchorfile>classThyra_1_1BelosLinearOpWithSolve.html</anchorfile>
      <anchor>a7528c03f7817d2c2e7cd8aee20ae2fa8</anchor>
      <arglist>(RCP&lt; Teuchos::ParameterList &gt; const &amp;paramList)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; Teuchos::ParameterList &gt;</type>
      <name>getNonconstParameterList</name>
      <anchorfile>classThyra_1_1BelosLinearOpWithSolve.html</anchorfile>
      <anchor>a241173d7cdf6f54cec9a320b0c119480</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; Teuchos::ParameterList &gt;</type>
      <name>unsetParameterList</name>
      <anchorfile>classThyra_1_1BelosLinearOpWithSolve.html</anchorfile>
      <anchor>a11a5f17dea200e21b6171be4f63cd1d7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const Teuchos::ParameterList &gt;</type>
      <name>getParameterList</name>
      <anchorfile>classThyra_1_1BelosLinearOpWithSolve.html</anchorfile>
      <anchor>ae6f2f3c8e3718b4c032e1bd966790d43</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const Teuchos::ParameterList &gt;</type>
      <name>getValidParameters</name>
      <anchorfile>classThyra_1_1BelosLinearOpWithSolve.html</anchorfile>
      <anchor>ab840d526e3ecf37c594faed9a85d8d9d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual bool</type>
      <name>solveSupportsImpl</name>
      <anchorfile>classThyra_1_1BelosLinearOpWithSolve.html</anchorfile>
      <anchor>a445035a5e2021a7552d310299b8ceedf</anchor>
      <arglist>(EOpTransp M_trans) const </arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual bool</type>
      <name>solveSupportsNewImpl</name>
      <anchorfile>classThyra_1_1BelosLinearOpWithSolve.html</anchorfile>
      <anchor>a0019f20cd88f0d71df7d342f504e709c</anchor>
      <arglist>(EOpTransp transp, const Ptr&lt; const SolveCriteria&lt; Scalar &gt; &gt; solveCriteria) const </arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual bool</type>
      <name>solveSupportsSolveMeasureTypeImpl</name>
      <anchorfile>classThyra_1_1BelosLinearOpWithSolve.html</anchorfile>
      <anchor>ab3ee6b2c7e4a68829bcf2a7d6487a372</anchor>
      <arglist>(EOpTransp M_trans, const SolveMeasureType &amp;solveMeasureType) const </arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual SolveStatus&lt; Scalar &gt;</type>
      <name>solveImpl</name>
      <anchorfile>classThyra_1_1BelosLinearOpWithSolve.html</anchorfile>
      <anchor>a72ec493db6fed2e8f4ad3794fc058c27</anchor>
      <arglist>(const EOpTransp transp, const MultiVectorBase&lt; Scalar &gt; &amp;B, const Ptr&lt; MultiVectorBase&lt; Scalar &gt; &gt; &amp;X, const Ptr&lt; const SolveCriteria&lt; Scalar &gt; &gt; solveCriteria) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::BelosLinearOpWithSolveFactory</name>
    <filename>classThyra_1_1BelosLinearOpWithSolveFactory.html</filename>
    <templarg></templarg>
    <member kind="typedef">
      <type>Teuchos::ScalarTraits&lt; Scalar &gt;::magnitudeType</type>
      <name>MagnitudeType</name>
      <anchorfile>classThyra_1_1BelosLinearOpWithSolveFactory.html</anchorfile>
      <anchor>a242df2fd8b061cc61994118a0ec6a026</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const std::string</type>
      <name>SolverType_name</name>
      <anchorfile>classThyra_1_1BelosLinearOpWithSolveFactory.html</anchorfile>
      <anchor>a347ed0cb7dfac3723734ca25765e4559</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const std::string</type>
      <name>SolverType_default</name>
      <anchorfile>classThyra_1_1BelosLinearOpWithSolveFactory.html</anchorfile>
      <anchor>a4cd28003e6b8339e6438cf7030756186</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const std::string</type>
      <name>SolverTypes_name</name>
      <anchorfile>classThyra_1_1BelosLinearOpWithSolveFactory.html</anchorfile>
      <anchor>a4810d8b6278ed64b77dfacf4114c7442</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const std::string</type>
      <name>BlockGMRES_name</name>
      <anchorfile>classThyra_1_1BelosLinearOpWithSolveFactory.html</anchorfile>
      <anchor>a3115c387bf3e2d1f84dbbcec0d9e20de</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const std::string</type>
      <name>PseudoBlockGMRES_name</name>
      <anchorfile>classThyra_1_1BelosLinearOpWithSolveFactory.html</anchorfile>
      <anchor>addeb7d8522c2f67ea2d3ba8d4a3d1257</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const std::string</type>
      <name>BlockCG_name</name>
      <anchorfile>classThyra_1_1BelosLinearOpWithSolveFactory.html</anchorfile>
      <anchor>a9392d52385eb06f2b25ed9c98746d339</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const std::string</type>
      <name>PseudoBlockCG_name</name>
      <anchorfile>classThyra_1_1BelosLinearOpWithSolveFactory.html</anchorfile>
      <anchor>a7ac51c8e39187cb2664ad8931ef61673</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const std::string</type>
      <name>PseudoBlockStochasticCG_name</name>
      <anchorfile>classThyra_1_1BelosLinearOpWithSolveFactory.html</anchorfile>
      <anchor>ae91187455de1302ead74dc61a89a1c00</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const std::string</type>
      <name>GCRODR_name</name>
      <anchorfile>classThyra_1_1BelosLinearOpWithSolveFactory.html</anchorfile>
      <anchor>a5c5e1f67489649c4e5f5155eda5f5fcf</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const std::string</type>
      <name>RCG_name</name>
      <anchorfile>classThyra_1_1BelosLinearOpWithSolveFactory.html</anchorfile>
      <anchor>a930ffe3eff33c97d672e41b092a1a534</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const std::string</type>
      <name>MINRES_name</name>
      <anchorfile>classThyra_1_1BelosLinearOpWithSolveFactory.html</anchorfile>
      <anchor>a4c3b4cf6601fd75822c538bae6b1cd37</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const std::string</type>
      <name>TFQMR_name</name>
      <anchorfile>classThyra_1_1BelosLinearOpWithSolveFactory.html</anchorfile>
      <anchor>a13d92d841a78088f3e270f09b196035c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const std::string</type>
      <name>ConvergenceTestFrequency_name</name>
      <anchorfile>classThyra_1_1BelosLinearOpWithSolveFactory.html</anchorfile>
      <anchor>a1607e9266d570ab5ee0743277371e2d7</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BelosLinearOpWithSolveFactory</name>
      <anchorfile>classThyra_1_1BelosLinearOpWithSolveFactory.html</anchorfile>
      <anchor>ac5d71b3a135d2318a70bfb0cf29d5822</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BelosLinearOpWithSolveFactory</name>
      <anchorfile>classThyra_1_1BelosLinearOpWithSolveFactory.html</anchorfile>
      <anchor>a8d791ce9d46650fa141d69421d7e9d12</anchor>
      <arglist>(const Teuchos::RCP&lt; PreconditionerFactoryBase&lt; Scalar &gt; &gt; &amp;precFactory)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>acceptsPreconditionerFactory</name>
      <anchorfile>classThyra_1_1BelosLinearOpWithSolveFactory.html</anchorfile>
      <anchor>a767e9d3298e706115fff0a84301038f6</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setPreconditionerFactory</name>
      <anchorfile>classThyra_1_1BelosLinearOpWithSolveFactory.html</anchorfile>
      <anchor>a5bb0e6e7db7657a233a020027982a17e</anchor>
      <arglist>(const Teuchos::RCP&lt; PreconditionerFactoryBase&lt; Scalar &gt; &gt; &amp;precFactory, const std::string &amp;precFactoryName)</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; PreconditionerFactoryBase&lt; Scalar &gt; &gt;</type>
      <name>getPreconditionerFactory</name>
      <anchorfile>classThyra_1_1BelosLinearOpWithSolveFactory.html</anchorfile>
      <anchor>a54ea63d4e47c32e52b1eb14e1de1a93c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>unsetPreconditionerFactory</name>
      <anchorfile>classThyra_1_1BelosLinearOpWithSolveFactory.html</anchorfile>
      <anchor>a09bb34b508dc94473d4a33ba716d940d</anchor>
      <arglist>(Teuchos::RCP&lt; PreconditionerFactoryBase&lt; Scalar &gt; &gt; *precFactory, std::string *precFactoryName)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isCompatible</name>
      <anchorfile>classThyra_1_1BelosLinearOpWithSolveFactory.html</anchorfile>
      <anchor>a317afbbc1e4280de1ad62824305ad0e8</anchor>
      <arglist>(const LinearOpSourceBase&lt; Scalar &gt; &amp;fwdOpSrc) const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; LinearOpWithSolveBase&lt; Scalar &gt; &gt;</type>
      <name>createOp</name>
      <anchorfile>classThyra_1_1BelosLinearOpWithSolveFactory.html</anchorfile>
      <anchor>a48d11109a23c1abc73ed6c3b1e7f655c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initializeOp</name>
      <anchorfile>classThyra_1_1BelosLinearOpWithSolveFactory.html</anchorfile>
      <anchor>acba21a2847eab4b9df1057cfbf360a67</anchor>
      <arglist>(const Teuchos::RCP&lt; const LinearOpSourceBase&lt; Scalar &gt; &gt; &amp;fwdOpSrc, LinearOpWithSolveBase&lt; Scalar &gt; *Op, const ESupportSolveUse supportSolveUse) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initializeAndReuseOp</name>
      <anchorfile>classThyra_1_1BelosLinearOpWithSolveFactory.html</anchorfile>
      <anchor>a19128c129b39244ec32400c7fee0a683</anchor>
      <arglist>(const Teuchos::RCP&lt; const LinearOpSourceBase&lt; Scalar &gt; &gt; &amp;fwdOpSrc, LinearOpWithSolveBase&lt; Scalar &gt; *Op) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>uninitializeOp</name>
      <anchorfile>classThyra_1_1BelosLinearOpWithSolveFactory.html</anchorfile>
      <anchor>a2bb4e9a34ec84e3897608b8349e37f4d</anchor>
      <arglist>(LinearOpWithSolveBase&lt; Scalar &gt; *Op, Teuchos::RCP&lt; const LinearOpSourceBase&lt; Scalar &gt; &gt; *fwdOpSrc, Teuchos::RCP&lt; const PreconditionerBase&lt; Scalar &gt; &gt; *prec, Teuchos::RCP&lt; const LinearOpSourceBase&lt; Scalar &gt; &gt; *approxFwdOpSrc, ESupportSolveUse *supportSolveUse) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>supportsPreconditionerInputType</name>
      <anchorfile>classThyra_1_1BelosLinearOpWithSolveFactory.html</anchorfile>
      <anchor>a21fbef6b596977963d8089df5bce3b4a</anchor>
      <arglist>(const EPreconditionerInputType precOpType) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initializePreconditionedOp</name>
      <anchorfile>classThyra_1_1BelosLinearOpWithSolveFactory.html</anchorfile>
      <anchor>a91a71abacceb27bc57b97fa0c2bb98d5</anchor>
      <arglist>(const Teuchos::RCP&lt; const LinearOpSourceBase&lt; Scalar &gt; &gt; &amp;fwdOpSrc, const Teuchos::RCP&lt; const PreconditionerBase&lt; Scalar &gt; &gt; &amp;prec, LinearOpWithSolveBase&lt; Scalar &gt; *Op, const ESupportSolveUse supportSolveUse) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initializeApproxPreconditionedOp</name>
      <anchorfile>classThyra_1_1BelosLinearOpWithSolveFactory.html</anchorfile>
      <anchor>a550356f9ff683e6f607578b419151f9f</anchor>
      <arglist>(const Teuchos::RCP&lt; const LinearOpSourceBase&lt; Scalar &gt; &gt; &amp;fwdOpSrc, const Teuchos::RCP&lt; const LinearOpSourceBase&lt; Scalar &gt; &gt; &amp;approxFwdOpSrc, LinearOpWithSolveBase&lt; Scalar &gt; *Op, const ESupportSolveUse supportSolveUse) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setParameterList</name>
      <anchorfile>classThyra_1_1BelosLinearOpWithSolveFactory.html</anchorfile>
      <anchor>a12f101ead8e321ebfdca33c77cf53fa3</anchor>
      <arglist>(Teuchos::RCP&lt; Teuchos::ParameterList &gt; const &amp;paramList)</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; Teuchos::ParameterList &gt;</type>
      <name>getNonconstParameterList</name>
      <anchorfile>classThyra_1_1BelosLinearOpWithSolveFactory.html</anchorfile>
      <anchor>aaba625c577fba0233277a4a37f1436e3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; Teuchos::ParameterList &gt;</type>
      <name>unsetParameterList</name>
      <anchorfile>classThyra_1_1BelosLinearOpWithSolveFactory.html</anchorfile>
      <anchor>ade9516cfd4bce93d2904ab1182b6a4c2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Teuchos::ParameterList &gt;</type>
      <name>getParameterList</name>
      <anchorfile>classThyra_1_1BelosLinearOpWithSolveFactory.html</anchorfile>
      <anchor>afe591c6d105115bc4c61f7f86e74b6ac</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Teuchos::ParameterList &gt;</type>
      <name>getValidParameters</name>
      <anchorfile>classThyra_1_1BelosLinearOpWithSolveFactory.html</anchorfile>
      <anchor>a36c3e79fdb156c1a2fa4e29a82e9a128</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>description</name>
      <anchorfile>classThyra_1_1BelosLinearOpWithSolveFactory.html</anchorfile>
      <anchor>ac2bb62cd7efea4ab8385b6ed81c64f0a</anchor>
      <arglist>() const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Stratimikos::DefaultLinearSolverBuilder</name>
    <filename>classStratimikos_1_1DefaultLinearSolverBuilder.html</filename>
    <member kind="function">
      <type></type>
      <name>DefaultLinearSolverBuilder</name>
      <anchorfile>classStratimikos_1_1DefaultLinearSolverBuilder.html</anchorfile>
      <anchor>a52b3facd6f91fb2d752a26c9dfe107ac</anchor>
      <arglist>(const std::string &amp;paramsXmlFileName=&quot;&quot;, const std::string &amp;extraParamsXmlString=&quot;&quot;, const std::string &amp;paramsUsedXmlOutFileName=&quot;&quot;, const std::string &amp;paramsXmlFileNameOption=&quot;linear-solver-params-file&quot;, const std::string &amp;extraParamsXmlStringOption=&quot;extra-linear-solver-params&quot;, const std::string &amp;paramsUsedXmlOutFileNameOption=&quot;linear-solver-params-used-file&quot;)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~DefaultLinearSolverBuilder</name>
      <anchorfile>classStratimikos_1_1DefaultLinearSolverBuilder.html</anchorfile>
      <anchor>a4fc335128c648e66272e0347132030fe</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classStratimikos_1_1DefaultLinearSolverBuilder.html</anchorfile>
      <anchor>a28023b9994a51e1848edfa7773e07757</anchor>
      <arglist>(std::string, paramsXmlFileName)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classStratimikos_1_1DefaultLinearSolverBuilder.html</anchorfile>
      <anchor>a4ec347c75b0883ef1bd7389a2bdea9a4</anchor>
      <arglist>(std::string, extraParamsXmlString)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classStratimikos_1_1DefaultLinearSolverBuilder.html</anchorfile>
      <anchor>a380a4c2ce77df840b04351fc33f65b50</anchor>
      <arglist>(std::string, paramsUsedXmlOutFileName)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classStratimikos_1_1DefaultLinearSolverBuilder.html</anchorfile>
      <anchor>ad987a02d9dc7793d3d3eaf7ddc208f63</anchor>
      <arglist>(std::string, paramsXmlFileNameOption)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classStratimikos_1_1DefaultLinearSolverBuilder.html</anchorfile>
      <anchor>aa5e0dfe7fee5ea113e41c88388749d88</anchor>
      <arglist>(std::string, extraParamsXmlStringOption)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classStratimikos_1_1DefaultLinearSolverBuilder.html</anchorfile>
      <anchor>a65aaf334beaea308c8f1c32858bb508d</anchor>
      <arglist>(std::string, paramsUsedXmlOutFileNameOption)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setLinearSolveStrategyFactory</name>
      <anchorfile>classStratimikos_1_1DefaultLinearSolverBuilder.html</anchorfile>
      <anchor>ae612daca49e31d13d0f3ee76658ae908</anchor>
      <arglist>(const RCP&lt; const AbstractFactory&lt; Thyra::LinearOpWithSolveFactoryBase&lt; double &gt; &gt; &gt; &amp;solveStrategyFactory, const std::string &amp;solveStrategyName, const bool makeDefault=false)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setDefaultLinearSolveStrategyFactoryName</name>
      <anchorfile>classStratimikos_1_1DefaultLinearSolverBuilder.html</anchorfile>
      <anchor>a82b94f01017241409bc0d9c3f1c5e4f9</anchor>
      <arglist>(const std::string &amp;solveStrategyName)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setPreconditioningStrategyFactory</name>
      <anchorfile>classStratimikos_1_1DefaultLinearSolverBuilder.html</anchorfile>
      <anchor>a2cdad6700b31a5745f7ddaa690bc4156</anchor>
      <arglist>(const RCP&lt; const AbstractFactory&lt; Thyra::PreconditionerFactoryBase&lt; double &gt; &gt; &gt; &amp;precStrategyFactory, const std::string &amp;precStrategyName, const bool makeDefault=false)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setDefaultPreconditioningStrategyFactoryName</name>
      <anchorfile>classStratimikos_1_1DefaultLinearSolverBuilder.html</anchorfile>
      <anchor>a37172c1409f474ebf44ef126c3e0e62e</anchor>
      <arglist>(const std::string &amp;precStrategyName)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setupCLP</name>
      <anchorfile>classStratimikos_1_1DefaultLinearSolverBuilder.html</anchorfile>
      <anchor>a063fd9a56030273baa9609d1b55ea46d</anchor>
      <arglist>(Teuchos::CommandLineProcessor *clp)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>readParameters</name>
      <anchorfile>classStratimikos_1_1DefaultLinearSolverBuilder.html</anchorfile>
      <anchor>a94487fd24913787ca304306ae87120c5</anchor>
      <arglist>(std::ostream *out)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>writeParamsFile</name>
      <anchorfile>classStratimikos_1_1DefaultLinearSolverBuilder.html</anchorfile>
      <anchor>ad7b231ca0c65134de91a04a9a6d3a3dc</anchor>
      <arglist>(const Thyra::LinearOpWithSolveFactoryBase&lt; double &gt; &amp;lowsFactory, const std::string &amp;outputXmlFileName=&quot;&quot;) const </arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>getLinearSolveStrategyName</name>
      <anchorfile>classStratimikos_1_1DefaultLinearSolverBuilder.html</anchorfile>
      <anchor>a0f07c594a6517590c7c85a1e4f054e64</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>getPreconditionerStrategyName</name>
      <anchorfile>classStratimikos_1_1DefaultLinearSolverBuilder.html</anchorfile>
      <anchor>ac22b4c742956ac2de05b7c6c6797076c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setParameterList</name>
      <anchorfile>classStratimikos_1_1DefaultLinearSolverBuilder.html</anchorfile>
      <anchor>aed0c3679e842c73340156659352edd41</anchor>
      <arglist>(RCP&lt; ParameterList &gt; const &amp;paramList)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; ParameterList &gt;</type>
      <name>getNonconstParameterList</name>
      <anchorfile>classStratimikos_1_1DefaultLinearSolverBuilder.html</anchorfile>
      <anchor>a43884951441ec7eaa065074c97dc4b0d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; ParameterList &gt;</type>
      <name>unsetParameterList</name>
      <anchorfile>classStratimikos_1_1DefaultLinearSolverBuilder.html</anchorfile>
      <anchor>a23464f38af637ed550db3591f2fbc107</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const ParameterList &gt;</type>
      <name>getParameterList</name>
      <anchorfile>classStratimikos_1_1DefaultLinearSolverBuilder.html</anchorfile>
      <anchor>a6632f5cbc0b225dec53e6f649e268525</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const ParameterList &gt;</type>
      <name>getValidParameters</name>
      <anchorfile>classStratimikos_1_1DefaultLinearSolverBuilder.html</anchorfile>
      <anchor>aa3b5392930037531ef6f118b3f42eede</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; Thyra::LinearOpWithSolveFactoryBase&lt; double &gt; &gt;</type>
      <name>createLinearSolveStrategy</name>
      <anchorfile>classStratimikos_1_1DefaultLinearSolverBuilder.html</anchorfile>
      <anchor>a8aadf71ce9fa68960f7066add303274a</anchor>
      <arglist>(const std::string &amp;linearSolveStrategyName) const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; Thyra::PreconditionerFactoryBase&lt; double &gt; &gt;</type>
      <name>createPreconditioningStrategy</name>
      <anchorfile>classStratimikos_1_1DefaultLinearSolverBuilder.html</anchorfile>
      <anchor>a8d880b686a14ffe5bae201d5fcd20f65</anchor>
      <arglist>(const std::string &amp;preconditioningStrategyName) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::GeneralSolveCriteriaBelosStatusTest</name>
    <filename>classThyra_1_1GeneralSolveCriteriaBelosStatusTest.html</filename>
    <templarg>Scalar</templarg>
    <base>StatusTest&lt; Scalar, MultiVectorBase&lt; Scalar &gt;, LinearOpBase&lt; Scalar &gt; &gt;</base>
    <member kind="function">
      <type>RCP&lt; GeneralSolveCriteriaBelosStatusTest&lt; Scalar &gt; &gt;</type>
      <name>createGeneralSolveCriteriaBelosStatusTest</name>
      <anchorfile>classThyra_1_1GeneralSolveCriteriaBelosStatusTest.html</anchorfile>
      <anchor>a339c860ac809c78704fe34b2a6cb6ea3</anchor>
      <arglist>(const SolveCriteria&lt; Scalar &gt; &amp;solveCriteria, const int convergenceTestFrequency)</arglist>
    </member>
    <member kind="typedef">
      <type>MultiVectorBase&lt; Scalar &gt;</type>
      <name>MV</name>
      <anchorfile>classThyra_1_1GeneralSolveCriteriaBelosStatusTest.html</anchorfile>
      <anchor>a38cfbd901a740a50ebff405ed85ceb1b</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>LinearOpBase&lt; Scalar &gt;</type>
      <name>OP</name>
      <anchorfile>classThyra_1_1GeneralSolveCriteriaBelosStatusTest.html</anchorfile>
      <anchor>a47046202f3c5d19e2363c10827566cf8</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>ScalarTraits&lt; Scalar &gt;::magnitudeType</type>
      <name>ScalarMag</name>
      <anchorfile>classThyra_1_1GeneralSolveCriteriaBelosStatusTest.html</anchorfile>
      <anchor>a6a7f72b3dfb10fd5955d0468a7b4f81e</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>GeneralSolveCriteriaBelosStatusTest</name>
      <anchorfile>classThyra_1_1GeneralSolveCriteriaBelosStatusTest.html</anchorfile>
      <anchor>a03e16c71dcc26236fb5a6bf6625c8433</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setSolveCriteria</name>
      <anchorfile>classThyra_1_1GeneralSolveCriteriaBelosStatusTest.html</anchorfile>
      <anchor>a05bcf8b49540a3c728b874a434fcde7e</anchor>
      <arglist>(const SolveCriteria&lt; Scalar &gt; &amp;solveCriteria, const int convergenceTestFrequency)</arglist>
    </member>
    <member kind="function">
      <type>ArrayView&lt; const ScalarMag &gt;</type>
      <name>achievedTol</name>
      <anchorfile>classThyra_1_1GeneralSolveCriteriaBelosStatusTest.html</anchorfile>
      <anchor>ac664c4c69289ff32c9e16bdf23ab10c8</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual Belos::StatusType</type>
      <name>checkStatus</name>
      <anchorfile>classThyra_1_1GeneralSolveCriteriaBelosStatusTest.html</anchorfile>
      <anchor>a43c483b3cf2d91ed3b8b9fdf731abd5b</anchor>
      <arglist>(Belos::Iteration&lt; Scalar, MV, OP &gt; *iSolver)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual Belos::StatusType</type>
      <name>getStatus</name>
      <anchorfile>classThyra_1_1GeneralSolveCriteriaBelosStatusTest.html</anchorfile>
      <anchor>a54b96e758685217591e5247e962e40c8</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>reset</name>
      <anchorfile>classThyra_1_1GeneralSolveCriteriaBelosStatusTest.html</anchorfile>
      <anchor>a296fb4ea7702ec0ead23d84dedd122b4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>print</name>
      <anchorfile>classThyra_1_1GeneralSolveCriteriaBelosStatusTest.html</anchorfile>
      <anchor>a7f09b2a0c6041ba724263c6a7b75b1aa</anchor>
      <arglist>(std::ostream &amp;os, int indent) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::IfpackPreconditionerFactory</name>
    <filename>classThyra_1_1IfpackPreconditionerFactory.html</filename>
    <member kind="function">
      <type></type>
      <name>IfpackPreconditionerFactory</name>
      <anchorfile>classThyra_1_1IfpackPreconditionerFactory.html</anchorfile>
      <anchor>ac11aa744f3beb4ec39f0b7d6e699228f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_COMPOSITION_MEMBERS</name>
      <anchorfile>classThyra_1_1IfpackPreconditionerFactory.html</anchorfile>
      <anchor>a15a2227db9a653a7e62d6cff7b1e4260</anchor>
      <arglist>(EpetraOperatorViewExtractorBase, epetraFwdOpViewExtractor)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isCompatible</name>
      <anchorfile>classThyra_1_1IfpackPreconditionerFactory.html</anchorfile>
      <anchor>abfd152bc160fc5eb48ecb0db0c41d7cf</anchor>
      <arglist>(const LinearOpSourceBase&lt; double &gt; &amp;fwdOpSrc) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>applySupportsConj</name>
      <anchorfile>classThyra_1_1IfpackPreconditionerFactory.html</anchorfile>
      <anchor>a84f12b23249d39235d4e0177d5a0c099</anchor>
      <arglist>(EConj conj) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>applyTransposeSupportsConj</name>
      <anchorfile>classThyra_1_1IfpackPreconditionerFactory.html</anchorfile>
      <anchor>ab3f5c3e785a3098f5040d633fa534160</anchor>
      <arglist>(EConj conj) const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; PreconditionerBase&lt; double &gt; &gt;</type>
      <name>createPrec</name>
      <anchorfile>classThyra_1_1IfpackPreconditionerFactory.html</anchorfile>
      <anchor>a6ad75060f7daa010098e12f859cf96ac</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initializePrec</name>
      <anchorfile>classThyra_1_1IfpackPreconditionerFactory.html</anchorfile>
      <anchor>a6b6eb30e00ff3d6bd3ac3ce454e6e3c3</anchor>
      <arglist>(const Teuchos::RCP&lt; const LinearOpSourceBase&lt; double &gt; &gt; &amp;fwdOpSrc, PreconditionerBase&lt; double &gt; *prec, const ESupportSolveUse supportSolveUse) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>uninitializePrec</name>
      <anchorfile>classThyra_1_1IfpackPreconditionerFactory.html</anchorfile>
      <anchor>ae263310fae5ddf1cfbd1784a233af1e5</anchor>
      <arglist>(PreconditionerBase&lt; double &gt; *prec, Teuchos::RCP&lt; const LinearOpSourceBase&lt; double &gt; &gt; *fwdOpSrc, ESupportSolveUse *supportSolveUse) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setParameterList</name>
      <anchorfile>classThyra_1_1IfpackPreconditionerFactory.html</anchorfile>
      <anchor>a509eab15f8770362b5b962a9edf12eca</anchor>
      <arglist>(Teuchos::RCP&lt; Teuchos::ParameterList &gt; const &amp;paramList)</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; Teuchos::ParameterList &gt;</type>
      <name>getNonconstParameterList</name>
      <anchorfile>classThyra_1_1IfpackPreconditionerFactory.html</anchorfile>
      <anchor>aa53517d474f98288682348cf46d05647</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; Teuchos::ParameterList &gt;</type>
      <name>unsetParameterList</name>
      <anchorfile>classThyra_1_1IfpackPreconditionerFactory.html</anchorfile>
      <anchor>aeae73777077174a5546293ff0c906a70</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Teuchos::ParameterList &gt;</type>
      <name>getParameterList</name>
      <anchorfile>classThyra_1_1IfpackPreconditionerFactory.html</anchorfile>
      <anchor>acd14bf1fe4dabf584a92fa46a9a60af9</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Teuchos::ParameterList &gt;</type>
      <name>getValidParameters</name>
      <anchorfile>classThyra_1_1IfpackPreconditionerFactory.html</anchorfile>
      <anchor>a5004b4d3d010faa2a91a5eb760c0262a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>description</name>
      <anchorfile>classThyra_1_1IfpackPreconditionerFactory.html</anchorfile>
      <anchor>a02602490c3890b8d854c5dfc28999a9a</anchor>
      <arglist>() const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::MLPreconditionerFactory</name>
    <filename>classThyra_1_1MLPreconditionerFactory.html</filename>
    <member kind="function">
      <type></type>
      <name>MLPreconditionerFactory</name>
      <anchorfile>classThyra_1_1MLPreconditionerFactory.html</anchorfile>
      <anchor>a10223f363c3d539820effd34e9b8d9b7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_COMPOSITION_MEMBERS</name>
      <anchorfile>classThyra_1_1MLPreconditionerFactory.html</anchorfile>
      <anchor>a2f71e48f9beaa2ee89f80ef7506a241d</anchor>
      <arglist>(EpetraOperatorViewExtractorBase, epetraFwdOpViewExtractor)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isCompatible</name>
      <anchorfile>classThyra_1_1MLPreconditionerFactory.html</anchorfile>
      <anchor>a8472c5e349315b5e17ade630af4ffc4c</anchor>
      <arglist>(const LinearOpSourceBase&lt; double &gt; &amp;fwdOp) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>applySupportsConj</name>
      <anchorfile>classThyra_1_1MLPreconditionerFactory.html</anchorfile>
      <anchor>ae22281c95d6fd3c150d35daf78d9efa3</anchor>
      <arglist>(EConj conj) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>applyTransposeSupportsConj</name>
      <anchorfile>classThyra_1_1MLPreconditionerFactory.html</anchorfile>
      <anchor>a99f2a1e54a9c96ac55655cc4054e892e</anchor>
      <arglist>(EConj conj) const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; PreconditionerBase&lt; double &gt; &gt;</type>
      <name>createPrec</name>
      <anchorfile>classThyra_1_1MLPreconditionerFactory.html</anchorfile>
      <anchor>a092cd7e23dd94ace3b7892e55ec0d7d5</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initializePrec</name>
      <anchorfile>classThyra_1_1MLPreconditionerFactory.html</anchorfile>
      <anchor>a361c82f5c5f7dee68a075fb77016e946</anchor>
      <arglist>(const Teuchos::RCP&lt; const LinearOpSourceBase&lt; double &gt; &gt; &amp;fwdOp, PreconditionerBase&lt; double &gt; *prec, const ESupportSolveUse supportSolveUse) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>uninitializePrec</name>
      <anchorfile>classThyra_1_1MLPreconditionerFactory.html</anchorfile>
      <anchor>a8babdf8b7ed8755f6bbef0ed448a0c91</anchor>
      <arglist>(PreconditionerBase&lt; double &gt; *prec, Teuchos::RCP&lt; const LinearOpSourceBase&lt; double &gt; &gt; *fwdOp, ESupportSolveUse *supportSolveUse) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setParameterList</name>
      <anchorfile>classThyra_1_1MLPreconditionerFactory.html</anchorfile>
      <anchor>aa070a9bcac66362a32fdc3cea6ea3a12</anchor>
      <arglist>(Teuchos::RCP&lt; Teuchos::ParameterList &gt; const &amp;paramList)</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; Teuchos::ParameterList &gt;</type>
      <name>getNonconstParameterList</name>
      <anchorfile>classThyra_1_1MLPreconditionerFactory.html</anchorfile>
      <anchor>a022a51be74ae773aeea16700d7cda39f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; Teuchos::ParameterList &gt;</type>
      <name>unsetParameterList</name>
      <anchorfile>classThyra_1_1MLPreconditionerFactory.html</anchorfile>
      <anchor>a51f4ca56aca0da8fbd9d3a3c1ff8f4f8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Teuchos::ParameterList &gt;</type>
      <name>getParameterList</name>
      <anchorfile>classThyra_1_1MLPreconditionerFactory.html</anchorfile>
      <anchor>a0101c3947bfd81ef31df880025189b22</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Teuchos::ParameterList &gt;</type>
      <name>getValidParameters</name>
      <anchorfile>classThyra_1_1MLPreconditionerFactory.html</anchorfile>
      <anchor>aa61f48838123d762a73520c438c6eab8</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>description</name>
      <anchorfile>classThyra_1_1MLPreconditionerFactory.html</anchorfile>
      <anchor>a38112d5ec3985b4593897f657b96e89f</anchor>
      <arglist>() const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Belos::MultiVecTraits&lt; ScalarType, Thyra::MultiVectorBase&lt; ScalarType &gt; &gt;</name>
    <filename>classBelos_1_1MultiVecTraits_3_01ScalarType_00_01Thyra_1_1MultiVectorBase_3_01ScalarType_01_4_01_4.html</filename>
    <templarg></templarg>
    <member kind="function" static="yes">
      <type>static Teuchos::RCP&lt; TMVB &gt;</type>
      <name>Clone</name>
      <anchorfile>classBelos_1_1MultiVecTraits_3_01ScalarType_00_01Thyra_1_1MultiVectorBase_3_01ScalarType_01_4_01_4.html</anchorfile>
      <anchor>a16e06cdd3b652128cc2fa2bad3187d69</anchor>
      <arglist>(const TMVB &amp;mv, const int numvecs)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static Teuchos::RCP&lt; TMVB &gt;</type>
      <name>CloneCopy</name>
      <anchorfile>classBelos_1_1MultiVecTraits_3_01ScalarType_00_01Thyra_1_1MultiVectorBase_3_01ScalarType_01_4_01_4.html</anchorfile>
      <anchor>aa6cb286773af0d55635e8231412257cb</anchor>
      <arglist>(const TMVB &amp;mv)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static Teuchos::RCP&lt; TMVB &gt;</type>
      <name>CloneCopy</name>
      <anchorfile>classBelos_1_1MultiVecTraits_3_01ScalarType_00_01Thyra_1_1MultiVectorBase_3_01ScalarType_01_4_01_4.html</anchorfile>
      <anchor>af0ea71f659bc4df40fb7354787e15cea</anchor>
      <arglist>(const TMVB &amp;mv, const std::vector&lt; int &gt; &amp;index)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static Teuchos::RCP&lt; TMVB &gt;</type>
      <name>CloneViewNonConst</name>
      <anchorfile>classBelos_1_1MultiVecTraits_3_01ScalarType_00_01Thyra_1_1MultiVectorBase_3_01ScalarType_01_4_01_4.html</anchorfile>
      <anchor>ab1abf0614fc955522068689582380653</anchor>
      <arglist>(TMVB &amp;mv, const std::vector&lt; int &gt; &amp;index)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static Teuchos::RCP&lt; const TMVB &gt;</type>
      <name>CloneView</name>
      <anchorfile>classBelos_1_1MultiVecTraits_3_01ScalarType_00_01Thyra_1_1MultiVectorBase_3_01ScalarType_01_4_01_4.html</anchorfile>
      <anchor>aeb5322c40e07bf9da0ef36ef44199e9a</anchor>
      <arglist>(const TMVB &amp;mv, const std::vector&lt; int &gt; &amp;index)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ptrdiff_t</type>
      <name>GetGlobalLength</name>
      <anchorfile>classBelos_1_1MultiVecTraits_3_01ScalarType_00_01Thyra_1_1MultiVectorBase_3_01ScalarType_01_4_01_4.html</anchorfile>
      <anchor>a9fddfda67326916c341be57502506366</anchor>
      <arglist>(const TMVB &amp;mv)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static int</type>
      <name>GetNumberVecs</name>
      <anchorfile>classBelos_1_1MultiVecTraits_3_01ScalarType_00_01Thyra_1_1MultiVectorBase_3_01ScalarType_01_4_01_4.html</anchorfile>
      <anchor>a475932d613bf7d9f6fc340c2db30de87</anchor>
      <arglist>(const TMVB &amp;mv)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>MvTimesMatAddMv</name>
      <anchorfile>classBelos_1_1MultiVecTraits_3_01ScalarType_00_01Thyra_1_1MultiVectorBase_3_01ScalarType_01_4_01_4.html</anchorfile>
      <anchor>ae56cd6b0bc48512e5d23b4edc3da724a</anchor>
      <arglist>(const ScalarType alpha, const TMVB &amp;A, const Teuchos::SerialDenseMatrix&lt; int, ScalarType &gt; &amp;B, const ScalarType beta, TMVB &amp;mv)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>MvAddMv</name>
      <anchorfile>classBelos_1_1MultiVecTraits_3_01ScalarType_00_01Thyra_1_1MultiVectorBase_3_01ScalarType_01_4_01_4.html</anchorfile>
      <anchor>a37897ebb058553ce39b8dcaf91772854</anchor>
      <arglist>(const ScalarType alpha, const TMVB &amp;A, const ScalarType beta, const TMVB &amp;B, TMVB &amp;mv)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>MvScale</name>
      <anchorfile>classBelos_1_1MultiVecTraits_3_01ScalarType_00_01Thyra_1_1MultiVectorBase_3_01ScalarType_01_4_01_4.html</anchorfile>
      <anchor>ac2ef9f52d0067f920b9ce98ccebbe969</anchor>
      <arglist>(TMVB &amp;mv, const ScalarType alpha)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>MvScale</name>
      <anchorfile>classBelos_1_1MultiVecTraits_3_01ScalarType_00_01Thyra_1_1MultiVectorBase_3_01ScalarType_01_4_01_4.html</anchorfile>
      <anchor>ad8bd6399ee3af6ee6d5aa019db7d242c</anchor>
      <arglist>(TMVB &amp;mv, const std::vector&lt; ScalarType &gt; &amp;alpha)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>MvTransMv</name>
      <anchorfile>classBelos_1_1MultiVecTraits_3_01ScalarType_00_01Thyra_1_1MultiVectorBase_3_01ScalarType_01_4_01_4.html</anchorfile>
      <anchor>ac754771ee5ff25d9602fc603832ab9f2</anchor>
      <arglist>(const ScalarType alpha, const TMVB &amp;A, const TMVB &amp;mv, Teuchos::SerialDenseMatrix&lt; int, ScalarType &gt; &amp;B)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>MvDot</name>
      <anchorfile>classBelos_1_1MultiVecTraits_3_01ScalarType_00_01Thyra_1_1MultiVectorBase_3_01ScalarType_01_4_01_4.html</anchorfile>
      <anchor>aa1be4c35db7b31f3e28d7f8b42225fed</anchor>
      <arglist>(const TMVB &amp;mv, const TMVB &amp;A, std::vector&lt; ScalarType &gt; &amp;b)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>MvNorm</name>
      <anchorfile>classBelos_1_1MultiVecTraits_3_01ScalarType_00_01Thyra_1_1MultiVectorBase_3_01ScalarType_01_4_01_4.html</anchorfile>
      <anchor>af3009aa9b35def1f1fc1e636544ca894</anchor>
      <arglist>(const TMVB &amp;mv, std::vector&lt; magType &gt; &amp;normvec, NormType type=TwoNorm)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>SetBlock</name>
      <anchorfile>classBelos_1_1MultiVecTraits_3_01ScalarType_00_01Thyra_1_1MultiVectorBase_3_01ScalarType_01_4_01_4.html</anchorfile>
      <anchor>a212fb538c6b43437c3f26605fa2ac4bc</anchor>
      <arglist>(const TMVB &amp;A, const std::vector&lt; int &gt; &amp;index, TMVB &amp;mv)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>MvRandom</name>
      <anchorfile>classBelos_1_1MultiVecTraits_3_01ScalarType_00_01Thyra_1_1MultiVectorBase_3_01ScalarType_01_4_01_4.html</anchorfile>
      <anchor>ae9079655a3f41f14c00e748778a49695</anchor>
      <arglist>(TMVB &amp;mv)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>MvInit</name>
      <anchorfile>classBelos_1_1MultiVecTraits_3_01ScalarType_00_01Thyra_1_1MultiVectorBase_3_01ScalarType_01_4_01_4.html</anchorfile>
      <anchor>afedcff6bfd7a23222aeb33e157dc313e</anchor>
      <arglist>(TMVB &amp;mv, ScalarType alpha=Teuchos::ScalarTraits&lt; ScalarType &gt;::zero())</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>MvPrint</name>
      <anchorfile>classBelos_1_1MultiVecTraits_3_01ScalarType_00_01Thyra_1_1MultiVectorBase_3_01ScalarType_01_4_01_4.html</anchorfile>
      <anchor>a006c036f27d902bf8a2c3213d3f6d4c3</anchor>
      <arglist>(const TMVB &amp;mv, std::ostream &amp;os)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Belos::OperatorTraits&lt; ScalarType,                                                                                                                                                                           Thyra::MultiVectorBase&lt; ScalarType &gt;,                                                                                                                                                                           Thyra::LinearOpBase&lt; ScalarType &gt; &gt;</name>
    <filename>classBelos_1_1OperatorTraits_3_01ScalarType_00_01_01_01_01_01_01_01_01_01_01_01_01_01_01_01_01_0549f141cedfd17f086626f3bf8704bcf.html</filename>
    <templarg></templarg>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>Apply</name>
      <anchorfile>classBelos_1_1OperatorTraits_3_01ScalarType_00_01_01_01_01_01_01_01_01_01_01_01_01_01_01_01_01_0549f141cedfd17f086626f3bf8704bcf.html</anchorfile>
      <anchor>ab2139b46930fec9ffa2ead39f9aed41b</anchor>
      <arglist>(const TLOB &amp;Op, const TMVB &amp;x, TMVB &amp;y, ETrans trans=NOTRANS)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static bool</type>
      <name>HasApplyTranspose</name>
      <anchorfile>classBelos_1_1OperatorTraits_3_01ScalarType_00_01_01_01_01_01_01_01_01_01_01_01_01_01_01_01_01_0549f141cedfd17f086626f3bf8704bcf.html</anchorfile>
      <anchor>a9126411c07f614a63f82417c703b2c60</anchor>
      <arglist>(const TLOB &amp;Op)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::TsqrAdaptor</name>
    <filename>classThyra_1_1TsqrAdaptor.html</filename>
    <templarg></templarg>
    <member kind="function">
      <type></type>
      <name>TsqrAdaptor</name>
      <anchorfile>classThyra_1_1TsqrAdaptor.html</anchorfile>
      <anchor>acff148d1108224c2c27538d66c6fac99</anchor>
      <arglist>(const Teuchos::RCP&lt; Teuchos::ParameterList &gt; &amp;)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>TsqrAdaptor</name>
      <anchorfile>classThyra_1_1TsqrAdaptor.html</anchorfile>
      <anchor>a8dd1aa7ce3ce5b9dfe59d70a3742cec8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>factorExplicit</name>
      <anchorfile>classThyra_1_1TsqrAdaptor.html</anchorfile>
      <anchor>ae8be14ef31c24e7da63b360545de4d36</anchor>
      <arglist>(MV &amp;, MV &amp;, dense_matrix_type &amp;, const bool=false)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>revealRank</name>
      <anchorfile>classThyra_1_1TsqrAdaptor.html</anchorfile>
      <anchor>a528f6288e4034efc0519a5b0b8e24ce8</anchor>
      <arglist>(MV &amp;, dense_matrix_type &amp;, const magnitude_type &amp;)</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>stratimikos_testing_grp</name>
    <title>Stratimikos testing code.</title>
    <filename>group__stratimikos__testing__grp.html</filename>
  </compound>
  <compound kind="page">
    <name>index</name>
    <title>Stratimikos: Thyra-based strategies for linear solvers</title>
    <filename>index</filename>
    <docanchor file="index" title="Linear solver adapters">stratimikos_lows_adapters_sec</docanchor>
    <docanchor file="index" title="Preconditioner adapters">stratimikos_pf_adapters_sec</docanchor>
    <docanchor file="index" title="Stratimikos examples">stratimikos_examples_sec</docanchor>
    <docanchor file="index" title="Stratimikos browser">stratimikos_browser_sec</docanchor>
    <docanchor file="index" title="Software">RTOp_interface_software_sec</docanchor>
    <docanchor file="index" title="Links">RTOp_interface_links_sec</docanchor>
    <docanchor file="index" title="Software">RTOp_support_software_sec</docanchor>
    <docanchor file="index" title="Links">RTOp_support_links_sec</docanchor>
    <docanchor file="index" title="Software">RTOp_ops_lib_software_sec</docanchor>
    <docanchor file="index" title="Links">RTOp_ops_lib_links_sec</docanchor>
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
    <docanchor file="index" title="Introduction">EpetraExt_intro</docanchor>
    <docanchor file="index" title="Overview of EpetraExt">EpetraExt_startup</docanchor>
    <docanchor file="index" title="EpetraExt Classes">EpetraExt_formulations</docanchor>
    <docanchor file="index" title="EpetraExt Functions">EpetraExt_functions</docanchor>
    <docanchor file="index" title="EpetraExt adapters">EpetraExt_adapters</docanchor>
    <docanchor file="index" title="Browse all of Epetraext as a single doxygen collection">EpetraExt_browser</docanchor>
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
    <docanchor file="index" title="Introduction">aztecoo_intro</docanchor>
    <docanchor file="index" title="Overview of AztecOO.">aztecoo_startup</docanchor>
    <docanchor file="index" title="AztecOO and Matrix Free usage.">aztecoo_matrixfree</docanchor>
    <docanchor file="index" title="Thyra support">aztecoo_thyra</docanchor>
    <docanchor file="index" title="Browse all of AztecOO as a single doxygen collection">AztecOO_browser</docanchor>
    <docanchor file="index" title="Table of Contents">ifp_table</docanchor>
    <docanchor file="index" title="Introduction">ifp_intro</docanchor>
    <docanchor file="index" title="Download IFPACK">ifp_download</docanchor>
    <docanchor file="index" title="Configuring IFPACK">ifp_configure</docanchor>
    <docanchor file="index" title="Examples of Usage">ifp_example</docanchor>
    <docanchor file="index" title="List of Supported Parameters">ifp_params</docanchor>
    <docanchor file="index" title="Brief Description IFPACK Classes">ifp_tools</docanchor>
    <docanchor file="index" title="Error Table">ifp_error</docanchor>
    <docanchor file="index" title="Known Bugs and Future Developments">ifp_bugs</docanchor>
    <docanchor file="index" title="Copyright">ifp_copyright</docanchor>
    <docanchor file="index" title="Browse all of Ifpack as a single doxygen collection">ifp_browser</docanchor>
  </compound>
</tagfile>
