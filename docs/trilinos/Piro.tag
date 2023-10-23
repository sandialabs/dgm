<?xml version='1.0' encoding='UTF-8' standalone='yes' ?>
<tagfile>
  <compound kind="class">
    <name>Piro::Epetra::AbstractNetworkModel</name>
    <filename>classPiro_1_1Epetra_1_1AbstractNetworkModel.html</filename>
    <member kind="function">
      <type></type>
      <name>AbstractNetworkModel</name>
      <anchorfile>classPiro_1_1Epetra_1_1AbstractNetworkModel.html</anchorfile>
      <anchor>addc24a437771140e6945b7404fc1c4c6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~AbstractNetworkModel</name>
      <anchorfile>classPiro_1_1Epetra_1_1AbstractNetworkModel.html</anchorfile>
      <anchor>a3a7df02ca0c7727a11e585f018fc49fd</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>evalModel</name>
      <anchorfile>classPiro_1_1Epetra_1_1AbstractNetworkModel.html</anchorfile>
      <anchor>a2952a0c96c458ee758c4e361e170050c</anchor>
      <arglist>(const Teuchos::Array&lt; EpetraExt::ModelEvaluator::InArgs &gt; &amp;model_inargs, const Teuchos::Array&lt; EpetraExt::ModelEvaluator::OutArgs &gt; &amp;model_outargs, const EpetraExt::ModelEvaluator::InArgs &amp;network_inargs, const EpetraExt::ModelEvaluator::OutArgs &amp;network_outargs, const Teuchos::Array&lt; int &gt; &amp;n_p, const Teuchos::Array&lt; int &gt; &amp;n_g, const Teuchos::Array&lt; Teuchos::RCP&lt; Epetra_Vector &gt; &gt; &amp;p, const Teuchos::Array&lt; Teuchos::RCP&lt; Epetra_Vector &gt; &gt; &amp;g, const Teuchos::Array&lt; Teuchos::RCP&lt; Epetra_MultiVector &gt; &gt; &amp;dgdp, const Teuchos::Array&lt; EpetraExt::ModelEvaluator::EDerivativeMultiVectorOrientation &gt; &amp;dgdp_layout, const Teuchos::Array&lt; EpetraExt::ModelEvaluator::OutArgs::sg_vector_t &gt; &amp;p_sg, const Teuchos::Array&lt; EpetraExt::ModelEvaluator::OutArgs::sg_vector_t &gt; &amp;g_sg, const Teuchos::Array&lt; Teuchos::RCP&lt; Stokhos::EpetraMultiVectorOrthogPoly &gt; &gt; &amp;dgdp_sg, const Teuchos::Array&lt; EpetraExt::ModelEvaluator::EDerivativeMultiVectorOrientation &gt; &amp;dgdp_sg_layout) const  =0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Piro::Epetra::AdaptiveSolutionManager</name>
    <filename>classPiro_1_1Epetra_1_1AdaptiveSolutionManager.html</filename>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>hasAdaptation</name>
      <anchorfile>classPiro_1_1Epetra_1_1AdaptiveSolutionManager.html</anchorfile>
      <anchor>aef5d3f796639edf262b7c9eb976ea33b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual Teuchos::RCP&lt; LOCA::Epetra::Group &gt;</type>
      <name>buildSolutionGroup</name>
      <anchorfile>classPiro_1_1Epetra_1_1AdaptiveSolutionManager.html</anchorfile>
      <anchor>a673dbc163356cd55e69395a2869edeed</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>destroySolutionGroup</name>
      <anchorfile>classPiro_1_1Epetra_1_1AdaptiveSolutionManager.html</anchorfile>
      <anchor>a45b17bbedceca11cd00d31e021c0ca80</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>Teuchos::RCP&lt; LOCA::Epetra::ModelEvaluatorInterface &gt;</type>
      <name>interface</name>
      <anchorfile>classPiro_1_1Epetra_1_1AdaptiveSolutionManager.html</anchorfile>
      <anchor>aaee784acb561f7406674255639f3d77b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>Teuchos::RCP&lt; LOCA::ParameterVector &gt;</type>
      <name>pVector</name>
      <anchorfile>classPiro_1_1Epetra_1_1AdaptiveSolutionManager.html</anchorfile>
      <anchor>a202a03f25b531b7ff45950c4e2ed0940</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>Teuchos::RCP&lt; LOCA::GlobalData &gt;</type>
      <name>globalData</name>
      <anchorfile>classPiro_1_1Epetra_1_1AdaptiveSolutionManager.html</anchorfile>
      <anchor>a476efe24910bb061c0b8e11fab6dce6a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>Teuchos::RCP&lt; EpetraExt::ModelEvaluator &gt;</type>
      <name>model</name>
      <anchorfile>classPiro_1_1Epetra_1_1AdaptiveSolutionManager.html</anchorfile>
      <anchor>a271258da6e0e52ed9ead8f34452d8ba3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>bool</type>
      <name>createPrec</name>
      <anchorfile>classPiro_1_1Epetra_1_1AdaptiveSolutionManager.html</anchorfile>
      <anchor>a40d9e5fea2aaba6173c42443b6278411</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>bool</type>
      <name>adaptiveMesh</name>
      <anchorfile>classPiro_1_1Epetra_1_1AdaptiveSolutionManager.html</anchorfile>
      <anchor>a3247c355ddd754fca40712ad6f62476e</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Piro::Epetra::InvertMassMatrixDecorator</name>
    <filename>classPiro_1_1Epetra_1_1InvertMassMatrixDecorator.html</filename>
    <member kind="function">
      <type></type>
      <name>InvertMassMatrixDecorator</name>
      <anchorfile>classPiro_1_1Epetra_1_1InvertMassMatrixDecorator.html</anchorfile>
      <anchor>a79811ac4069faee9369918f136e7506c</anchor>
      <arglist>(Teuchos::RCP&lt; Teuchos::ParameterList &gt; stratParams, Teuchos::RCP&lt; EpetraExt::ModelEvaluator &gt; &amp;model, bool massMatrixIsConstant=true, bool lumpMassMatrix=false, bool massMatrixIsCoeffOfSecondDeriv=false)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>InvertMassMatrixDecorator</name>
      <anchorfile>classPiro_1_1Epetra_1_1InvertMassMatrixDecorator.html</anchorfile>
      <anchor>a79811ac4069faee9369918f136e7506c</anchor>
      <arglist>(Teuchos::RCP&lt; Teuchos::ParameterList &gt; stratParams, Teuchos::RCP&lt; EpetraExt::ModelEvaluator &gt; &amp;model, bool massMatrixIsConstant=true, bool lumpMassMatrix=false, bool massMatrixIsCoeffOfSecondDeriv=false)</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Epetra_Vector &gt;</type>
      <name>get_p_init</name>
      <anchorfile>classPiro_1_1Epetra_1_1InvertMassMatrixDecorator.html</anchorfile>
      <anchor>a936640209a52ee9275945467488832ae</anchor>
      <arglist>(int l) const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; Epetra_Operator &gt;</type>
      <name>create_W</name>
      <anchorfile>classPiro_1_1Epetra_1_1InvertMassMatrixDecorator.html</anchorfile>
      <anchor>a88616db0bd892a20422e03ba9a68b4ee</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>EpetraExt::ModelEvaluator::InArgs</type>
      <name>createInArgs</name>
      <anchorfile>classPiro_1_1Epetra_1_1InvertMassMatrixDecorator.html</anchorfile>
      <anchor>aaf92076baaacd66909dbbe0f468e977a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>EpetraExt::ModelEvaluator::OutArgs</type>
      <name>createOutArgs</name>
      <anchorfile>classPiro_1_1Epetra_1_1InvertMassMatrixDecorator.html</anchorfile>
      <anchor>a41c0e17cb1369a2dd6a490081d072da6</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>evalModel</name>
      <anchorfile>classPiro_1_1Epetra_1_1InvertMassMatrixDecorator.html</anchorfile>
      <anchor>a9f16192b1d4c0ebd153cca5f9e3ac782</anchor>
      <arglist>(const InArgs &amp;inArgs, const OutArgs &amp;outArgs) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Piro::InvertMassMatrixDecorator</name>
    <filename>classPiro_1_1InvertMassMatrixDecorator.html</filename>
    <templarg></templarg>
    <member kind="function">
      <type></type>
      <name>InvertMassMatrixDecorator</name>
      <anchorfile>classPiro_1_1InvertMassMatrixDecorator.html</anchorfile>
      <anchor>ac3ecc2151762b431ae5287ebff3a878e</anchor>
      <arglist>(Teuchos::RCP&lt; Teuchos::ParameterList &gt; stratParams, Teuchos::RCP&lt; Thyra::ModelEvaluator&lt; Scalar &gt; &gt; &amp;model, bool massMatrixIsConstant=true, bool lumpMassMatrix=false, bool massMatrixIsCoeffOfSecondDeriv=false)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>InvertMassMatrixDecorator</name>
      <anchorfile>classPiro_1_1InvertMassMatrixDecorator.html</anchorfile>
      <anchor>ac3ecc2151762b431ae5287ebff3a878e</anchor>
      <arglist>(Teuchos::RCP&lt; Teuchos::ParameterList &gt; stratParams, Teuchos::RCP&lt; Thyra::ModelEvaluator&lt; Scalar &gt; &gt; &amp;model, bool massMatrixIsConstant=true, bool lumpMassMatrix=false, bool massMatrixIsCoeffOfSecondDeriv=false)</arglist>
    </member>
    <member kind="function">
      <type>Thyra::ModelEvaluatorBase::InArgs&lt; Scalar &gt;</type>
      <name>getNominalValues</name>
      <anchorfile>classPiro_1_1InvertMassMatrixDecorator.html</anchorfile>
      <anchor>abf8dbcb0535857d2df9538ce7729e43e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; Thyra::LinearOpBase&lt; Scalar &gt; &gt;</type>
      <name>create_W_op</name>
      <anchorfile>classPiro_1_1InvertMassMatrixDecorator.html</anchorfile>
      <anchor>ad639274a0898beefe7aa1a27e8cfbc6d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Thyra::LinearOpWithSolveFactoryBase&lt; Scalar &gt; &gt;</type>
      <name>get_W_factory</name>
      <anchorfile>classPiro_1_1InvertMassMatrixDecorator.html</anchorfile>
      <anchor>a72f9ff52dab4dcc93669a553fdc8985c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Thyra::ModelEvaluatorBase::OutArgs&lt; Scalar &gt;</type>
      <name>createOutArgsImpl</name>
      <anchorfile>classPiro_1_1InvertMassMatrixDecorator.html</anchorfile>
      <anchor>a091769cc748966b4a69837bed16d0a0b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>reportFinalPoint</name>
      <anchorfile>classPiro_1_1InvertMassMatrixDecorator.html</anchorfile>
      <anchor>a1a9f21e35354839baf4451a13ce3cd60</anchor>
      <arglist>(const Thyra::ModelEvaluatorBase::InArgs&lt; Scalar &gt; &amp;finalPoint, const bool wasSolved)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Piro::LOCAAdaptiveSolver</name>
    <filename>classPiro_1_1LOCAAdaptiveSolver.html</filename>
    <templarg></templarg>
    <base>Piro::SteadyStateSolver</base>
    <member kind="function">
      <type>void</type>
      <name>reportFinalPoint</name>
      <anchorfile>classPiro_1_1LOCAAdaptiveSolver.html</anchorfile>
      <anchor>a5d7d787537962497b2fd2a9453405d2a</anchor>
      <arglist>(const Thyra::ModelEvaluatorBase::InArgs&lt; Scalar &gt; &amp;finalPoint, const bool wasSolved)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>LOCAAdaptiveSolver</name>
      <anchorfile>classPiro_1_1LOCAAdaptiveSolver.html</anchorfile>
      <anchor>af7c9e24848782eacc95180e608474dd3</anchor>
      <arglist>(const Teuchos::RCP&lt; Teuchos::ParameterList &gt; &amp;piroParams, const Teuchos::RCP&lt; Thyra::ModelEvaluator&lt; Scalar &gt; &gt; &amp;model, const Teuchos::RCP&lt; Thyra::AdaptiveSolutionManager &gt; &amp;solMgr, const Teuchos::RCP&lt; LOCA::Thyra::SaveDataStrategy &gt; &amp;saveDataStrategy)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>LOCAAdaptiveSolver</name>
      <anchorfile>classPiro_1_1LOCAAdaptiveSolver.html</anchorfile>
      <anchor>af7c9e24848782eacc95180e608474dd3</anchor>
      <arglist>(const Teuchos::RCP&lt; Teuchos::ParameterList &gt; &amp;piroParams, const Teuchos::RCP&lt; Thyra::ModelEvaluator&lt; Scalar &gt; &gt; &amp;model, const Teuchos::RCP&lt; Thyra::AdaptiveSolutionManager &gt; &amp;solMgr, const Teuchos::RCP&lt; LOCA::Thyra::SaveDataStrategy &gt; &amp;saveDataStrategy)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Piro::Epetra::LOCAAdaptiveSolver</name>
    <filename>classPiro_1_1Epetra_1_1LOCAAdaptiveSolver.html</filename>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Epetra_Vector &gt;</type>
      <name>get_p_init</name>
      <anchorfile>classPiro_1_1Epetra_1_1LOCAAdaptiveSolver.html</anchorfile>
      <anchor>a23285b4c5eacc9c86d78bf7b19b046c3</anchor>
      <arglist>(int l) const </arglist>
    </member>
    <member kind="function">
      <type>EpetraExt::ModelEvaluator::InArgs</type>
      <name>createInArgs</name>
      <anchorfile>classPiro_1_1Epetra_1_1LOCAAdaptiveSolver.html</anchorfile>
      <anchor>afc8661f9df2df7ee21ab77087a67a565</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>EpetraExt::ModelEvaluator::OutArgs</type>
      <name>createOutArgs</name>
      <anchorfile>classPiro_1_1Epetra_1_1LOCAAdaptiveSolver.html</anchorfile>
      <anchor>a91e52b3e9735f48b259e17dca79f9822</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>evalModel</name>
      <anchorfile>classPiro_1_1Epetra_1_1LOCAAdaptiveSolver.html</anchorfile>
      <anchor>a2d9a0f633a8b550209a90fa121cd0504</anchor>
      <arglist>(const InArgs &amp;inArgs, const OutArgs &amp;outArgs) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Piro::Epetra::LOCASolver</name>
    <filename>classPiro_1_1Epetra_1_1LOCASolver.html</filename>
    <member kind="function">
      <type>Teuchos::RCP&lt; const LOCA::Stepper &gt;</type>
      <name>getLOCAStepper</name>
      <anchorfile>classPiro_1_1Epetra_1_1LOCASolver.html</anchorfile>
      <anchor>ab970ac6e6e485af24d10700e20520fe8</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; LOCA::Stepper &gt;</type>
      <name>getLOCAStepperNonConst</name>
      <anchorfile>classPiro_1_1Epetra_1_1LOCASolver.html</anchorfile>
      <anchor>aaa6631cf120e2d2f4dd03a0e2d5c11c2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const LOCA::GlobalData &gt;</type>
      <name>getGlobalData</name>
      <anchorfile>classPiro_1_1Epetra_1_1LOCASolver.html</anchorfile>
      <anchor>a4813a315abb0dac29b501dccbe936419</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; LOCA::GlobalData &gt;</type>
      <name>getGlobalDataNonConst</name>
      <anchorfile>classPiro_1_1Epetra_1_1LOCASolver.html</anchorfile>
      <anchor>aa7b7b3b26c9ca137b849c02269b59d74</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>LOCASolver</name>
      <anchorfile>classPiro_1_1Epetra_1_1LOCASolver.html</anchorfile>
      <anchor>a6fc4fe5e80551e49c04d6a5bcdcd6dcb</anchor>
      <arglist>(Teuchos::RCP&lt; Teuchos::ParameterList &gt; piroParams, Teuchos::RCP&lt; EpetraExt::ModelEvaluator &gt; model, Teuchos::RCP&lt; NOX::Epetra::Observer &gt; observer=Teuchos::null, Teuchos::RCP&lt; LOCA::SaveEigenData::AbstractStrategy &gt; saveEigData=Teuchos::null, Teuchos::RCP&lt; LOCA::StatusTest::Abstract &gt; locaStatusTest_=Teuchos::null)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>LOCASolver</name>
      <anchorfile>classPiro_1_1Epetra_1_1LOCASolver.html</anchorfile>
      <anchor>a6fc4fe5e80551e49c04d6a5bcdcd6dcb</anchor>
      <arglist>(Teuchos::RCP&lt; Teuchos::ParameterList &gt; piroParams, Teuchos::RCP&lt; EpetraExt::ModelEvaluator &gt; model, Teuchos::RCP&lt; NOX::Epetra::Observer &gt; observer=Teuchos::null, Teuchos::RCP&lt; LOCA::SaveEigenData::AbstractStrategy &gt; saveEigData=Teuchos::null, Teuchos::RCP&lt; LOCA::StatusTest::Abstract &gt; locaStatusTest_=Teuchos::null)</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Epetra_Vector &gt;</type>
      <name>get_p_init</name>
      <anchorfile>classPiro_1_1Epetra_1_1LOCASolver.html</anchorfile>
      <anchor>a674b844e1c86c6b231c46225f7916979</anchor>
      <arglist>(int l) const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Epetra_Vector &gt;</type>
      <name>get_p_lower_bounds</name>
      <anchorfile>classPiro_1_1Epetra_1_1LOCASolver.html</anchorfile>
      <anchor>a21a58bb1d9cb81903995c1d57f745af6</anchor>
      <arglist>(int l) const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Epetra_Vector &gt;</type>
      <name>get_p_upper_bounds</name>
      <anchorfile>classPiro_1_1Epetra_1_1LOCASolver.html</anchorfile>
      <anchor>a780b4cfb8f1c51450e8866795d22be23</anchor>
      <arglist>(int l) const </arglist>
    </member>
    <member kind="function">
      <type>EpetraExt::ModelEvaluator::InArgs</type>
      <name>createInArgs</name>
      <anchorfile>classPiro_1_1Epetra_1_1LOCASolver.html</anchorfile>
      <anchor>ade143ade2fb4e7226c367c46298758d9</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>EpetraExt::ModelEvaluator::OutArgs</type>
      <name>createOutArgs</name>
      <anchorfile>classPiro_1_1Epetra_1_1LOCASolver.html</anchorfile>
      <anchor>aa2ad2c711a0ac83a46431ab57e242e90</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>evalModel</name>
      <anchorfile>classPiro_1_1Epetra_1_1LOCASolver.html</anchorfile>
      <anchor>a821e239f1efccd5b57032e842f404527</anchor>
      <arglist>(const InArgs &amp;inArgs, const OutArgs &amp;outArgs) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Piro::LOCASolver</name>
    <filename>classPiro_1_1LOCASolver.html</filename>
    <templarg></templarg>
    <base>Piro::SteadyStateSolver</base>
    <member kind="function">
      <type></type>
      <name>LOCASolver</name>
      <anchorfile>classPiro_1_1LOCASolver.html</anchorfile>
      <anchor>a686c432aa5405a0a032121f680b93a62</anchor>
      <arglist>(const Teuchos::RCP&lt; Teuchos::ParameterList &gt; &amp;piroParams, const Teuchos::RCP&lt; Thyra::ModelEvaluator&lt; Scalar &gt; &gt; &amp;model, const Teuchos::RCP&lt; LOCA::Thyra::SaveDataStrategy &gt; &amp;saveDataStrategy)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>LOCASolver</name>
      <anchorfile>classPiro_1_1LOCASolver.html</anchorfile>
      <anchor>a686c432aa5405a0a032121f680b93a62</anchor>
      <arglist>(const Teuchos::RCP&lt; Teuchos::ParameterList &gt; &amp;piroParams, const Teuchos::RCP&lt; Thyra::ModelEvaluator&lt; Scalar &gt; &gt; &amp;model, const Teuchos::RCP&lt; LOCA::Thyra::SaveDataStrategy &gt; &amp;saveDataStrategy)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Piro::Epetra::MatrixFreeDecorator</name>
    <filename>classPiro_1_1Epetra_1_1MatrixFreeDecorator.html</filename>
    <member kind="function">
      <type></type>
      <name>MatrixFreeDecorator</name>
      <anchorfile>classPiro_1_1Epetra_1_1MatrixFreeDecorator.html</anchorfile>
      <anchor>aab83e860152af1ced4c6e1fa94a20cac</anchor>
      <arglist>(Teuchos::RCP&lt; EpetraExt::ModelEvaluator &gt; &amp;model, double lambda_=1.0e-6)</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Epetra_Vector &gt;</type>
      <name>get_p_init</name>
      <anchorfile>classPiro_1_1Epetra_1_1MatrixFreeDecorator.html</anchorfile>
      <anchor>a7c4d8c18539a550e51e7fd6fc765360b</anchor>
      <arglist>(int l) const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Epetra_Vector &gt;</type>
      <name>get_p_lower_bounds</name>
      <anchorfile>classPiro_1_1Epetra_1_1MatrixFreeDecorator.html</anchorfile>
      <anchor>a54f27b488d789ded7c3fb151b1c412f9</anchor>
      <arglist>(int l) const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Epetra_Vector &gt;</type>
      <name>get_p_upper_bounds</name>
      <anchorfile>classPiro_1_1Epetra_1_1MatrixFreeDecorator.html</anchorfile>
      <anchor>ab3e758496e21184423e1cc1416cc585e</anchor>
      <arglist>(int l) const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; Epetra_Operator &gt;</type>
      <name>create_W</name>
      <anchorfile>classPiro_1_1Epetra_1_1MatrixFreeDecorator.html</anchorfile>
      <anchor>a28cee7ba5d0d5b3fe85d5f152a649d54</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; EpetraExt::ModelEvaluator::Preconditioner &gt;</type>
      <name>create_WPrec</name>
      <anchorfile>classPiro_1_1Epetra_1_1MatrixFreeDecorator.html</anchorfile>
      <anchor>af17d3b00464826550c982a9699cf2aa8</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>EpetraExt::ModelEvaluator::InArgs</type>
      <name>createInArgs</name>
      <anchorfile>classPiro_1_1Epetra_1_1MatrixFreeDecorator.html</anchorfile>
      <anchor>ab079b203373e9993a92661a84888627b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>EpetraExt::ModelEvaluator::OutArgs</type>
      <name>createOutArgs</name>
      <anchorfile>classPiro_1_1Epetra_1_1MatrixFreeDecorator.html</anchorfile>
      <anchor>a2740355b2056d83a9eca043c7ab36494</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>evalModel</name>
      <anchorfile>classPiro_1_1Epetra_1_1MatrixFreeDecorator.html</anchorfile>
      <anchor>a0bfcdb2c6c9a53303094070dc17b6ef2</anchor>
      <arglist>(const InArgs &amp;inArgs, const OutArgs &amp;outArgs) const </arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>MatrixFreeDecorator</name>
      <anchorfile>classPiro_1_1Epetra_1_1MatrixFreeDecorator.html</anchorfile>
      <anchor>aab83e860152af1ced4c6e1fa94a20cac</anchor>
      <arglist>(Teuchos::RCP&lt; EpetraExt::ModelEvaluator &gt; &amp;model, double lambda_=1.0e-6)</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Epetra_Vector &gt;</type>
      <name>get_p_init</name>
      <anchorfile>classPiro_1_1Epetra_1_1MatrixFreeDecorator.html</anchorfile>
      <anchor>a7c4d8c18539a550e51e7fd6fc765360b</anchor>
      <arglist>(int l) const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Epetra_Vector &gt;</type>
      <name>get_p_lower_bounds</name>
      <anchorfile>classPiro_1_1Epetra_1_1MatrixFreeDecorator.html</anchorfile>
      <anchor>a54f27b488d789ded7c3fb151b1c412f9</anchor>
      <arglist>(int l) const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Epetra_Vector &gt;</type>
      <name>get_p_upper_bounds</name>
      <anchorfile>classPiro_1_1Epetra_1_1MatrixFreeDecorator.html</anchorfile>
      <anchor>ab3e758496e21184423e1cc1416cc585e</anchor>
      <arglist>(int l) const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; Epetra_Operator &gt;</type>
      <name>create_W</name>
      <anchorfile>classPiro_1_1Epetra_1_1MatrixFreeDecorator.html</anchorfile>
      <anchor>a28cee7ba5d0d5b3fe85d5f152a649d54</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; EpetraExt::ModelEvaluator::Preconditioner &gt;</type>
      <name>create_WPrec</name>
      <anchorfile>classPiro_1_1Epetra_1_1MatrixFreeDecorator.html</anchorfile>
      <anchor>af17d3b00464826550c982a9699cf2aa8</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>EpetraExt::ModelEvaluator::InArgs</type>
      <name>createInArgs</name>
      <anchorfile>classPiro_1_1Epetra_1_1MatrixFreeDecorator.html</anchorfile>
      <anchor>ab079b203373e9993a92661a84888627b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>EpetraExt::ModelEvaluator::OutArgs</type>
      <name>createOutArgs</name>
      <anchorfile>classPiro_1_1Epetra_1_1MatrixFreeDecorator.html</anchorfile>
      <anchor>a2740355b2056d83a9eca043c7ab36494</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>evalModel</name>
      <anchorfile>classPiro_1_1Epetra_1_1MatrixFreeDecorator.html</anchorfile>
      <anchor>a0bfcdb2c6c9a53303094070dc17b6ef2</anchor>
      <arglist>(const InArgs &amp;inArgs, const OutArgs &amp;outArgs) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Piro::MatrixFreeDecorator</name>
    <filename>classPiro_1_1MatrixFreeDecorator.html</filename>
    <templarg></templarg>
    <member kind="function">
      <type></type>
      <name>MatrixFreeDecorator</name>
      <anchorfile>classPiro_1_1MatrixFreeDecorator.html</anchorfile>
      <anchor>a66600eb4bf36bbb3294223fb9e9a6170</anchor>
      <arglist>(Teuchos::RCP&lt; Thyra::ModelEvaluator&lt; Scalar &gt; &gt; model)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>MatrixFreeDecorator</name>
      <anchorfile>classPiro_1_1MatrixFreeDecorator.html</anchorfile>
      <anchor>a66600eb4bf36bbb3294223fb9e9a6170</anchor>
      <arglist>(Teuchos::RCP&lt; Thyra::ModelEvaluator&lt; Scalar &gt; &gt; model)</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; Thyra::LinearOpBase&lt; Scalar &gt; &gt;</type>
      <name>create_W_op</name>
      <anchorfile>classPiro_1_1MatrixFreeDecorator.html</anchorfile>
      <anchor>a3ba7002dac0ff6216525b3452f52137e</anchor>
      <arglist>() const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Piro::MatrixFreeLinearOp</name>
    <filename>classPiro_1_1MatrixFreeLinearOp.html</filename>
    <templarg></templarg>
    <member kind="function">
      <type></type>
      <name>MatrixFreeLinearOp</name>
      <anchorfile>classPiro_1_1MatrixFreeLinearOp.html</anchorfile>
      <anchor>aec1ebd55c68f7c9db37b206a16f886b1</anchor>
      <arglist>(const Teuchos::RCP&lt; const Thyra::ModelEvaluator&lt; Scalar &gt; &gt; &amp;model)</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Thyra::ModelEvaluator&lt; Scalar &gt; &gt;</type>
      <name>model</name>
      <anchorfile>classPiro_1_1MatrixFreeLinearOp.html</anchorfile>
      <anchor>a3b24df1bfd837d35af56f35506539323</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Thyra::ModelEvaluatorBase::InArgs&lt; Scalar &gt;</type>
      <name>basePoint</name>
      <anchorfile>classPiro_1_1MatrixFreeLinearOp.html</anchorfile>
      <anchor>a17e30757d6e3ec45ddf3605eeefcf8e3</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Thyra::VectorBase&lt; Scalar &gt; &gt;</type>
      <name>f_base</name>
      <anchorfile>classPiro_1_1MatrixFreeLinearOp.html</anchorfile>
      <anchor>aa35747ac1fdf286ce1c76387c054bcac</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setBase</name>
      <anchorfile>classPiro_1_1MatrixFreeLinearOp.html</anchorfile>
      <anchor>aa2efd1ba78b1c0119591b3ed7859d18e</anchor>
      <arglist>(const Thyra::ModelEvaluatorBase::InArgs&lt; Scalar &gt; &amp;basePoint, const Teuchos::RCP&lt; const Thyra::VectorBase&lt; Scalar &gt; &gt; &amp;f_base)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>MatrixFreeLinearOp</name>
      <anchorfile>classPiro_1_1MatrixFreeLinearOp.html</anchorfile>
      <anchor>aec1ebd55c68f7c9db37b206a16f886b1</anchor>
      <arglist>(const Teuchos::RCP&lt; const Thyra::ModelEvaluator&lt; Scalar &gt; &gt; &amp;model)</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Thyra::VectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>range</name>
      <anchorfile>classPiro_1_1MatrixFreeLinearOp.html</anchorfile>
      <anchor>aaf2fa90b75cf6feeb75b54fdef9e3bea</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Thyra::VectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>domain</name>
      <anchorfile>classPiro_1_1MatrixFreeLinearOp.html</anchorfile>
      <anchor>a0819e050c8396ed8c3922e2af68f2d3a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>bool</type>
      <name>opSupportedImpl</name>
      <anchorfile>classPiro_1_1MatrixFreeLinearOp.html</anchorfile>
      <anchor>a7d0a6f1b2530204c2be06fa8e41cbd61</anchor>
      <arglist>(Thyra::EOpTransp M_trans) const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>applyImpl</name>
      <anchorfile>classPiro_1_1MatrixFreeLinearOp.html</anchorfile>
      <anchor>a7ad15e66440e914825e1b54b782ee41c</anchor>
      <arglist>(const Thyra::EOpTransp M_trans, const Thyra::MultiVectorBase&lt; Scalar &gt; &amp;X, const Teuchos::Ptr&lt; Thyra::MultiVectorBase&lt; Scalar &gt; &gt; &amp;Y, const Scalar alpha, const Scalar beta) const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Thyra::ModelEvaluator&lt; Scalar &gt; &gt;</type>
      <name>model</name>
      <anchorfile>classPiro_1_1MatrixFreeLinearOp.html</anchorfile>
      <anchor>a3b24df1bfd837d35af56f35506539323</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Thyra::ModelEvaluatorBase::InArgs&lt; Scalar &gt;</type>
      <name>basePoint</name>
      <anchorfile>classPiro_1_1MatrixFreeLinearOp.html</anchorfile>
      <anchor>a17e30757d6e3ec45ddf3605eeefcf8e3</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Thyra::VectorBase&lt; Scalar &gt; &gt;</type>
      <name>f_base</name>
      <anchorfile>classPiro_1_1MatrixFreeLinearOp.html</anchorfile>
      <anchor>aa35747ac1fdf286ce1c76387c054bcac</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setBase</name>
      <anchorfile>classPiro_1_1MatrixFreeLinearOp.html</anchorfile>
      <anchor>aa2efd1ba78b1c0119591b3ed7859d18e</anchor>
      <arglist>(const Thyra::ModelEvaluatorBase::InArgs&lt; Scalar &gt; &amp;basePoint, const Teuchos::RCP&lt; const Thyra::VectorBase&lt; Scalar &gt; &gt; &amp;f_base)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Piro::Epetra::MatrixFreeOperator</name>
    <filename>classPiro_1_1Epetra_1_1MatrixFreeOperator.html</filename>
    <member kind="function">
      <type>void</type>
      <name>setBase</name>
      <anchorfile>classPiro_1_1Epetra_1_1MatrixFreeOperator.html</anchorfile>
      <anchor>a2404c827875a0d5f5168185a376b4af7</anchor>
      <arglist>(const EpetraExt::ModelEvaluator::InArgs &amp;modelInArgs_, Teuchos::RCP&lt; Epetra_Vector &gt; fBase, const bool haveXdot_, const bool haveXdotdot_)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>TriKota::MPDirectApplicInterface</name>
    <filename>classTriKota_1_1MPDirectApplicInterface.html</filename>
    <member kind="function">
      <type></type>
      <name>MPDirectApplicInterface</name>
      <anchorfile>classTriKota_1_1MPDirectApplicInterface.html</anchorfile>
      <anchor>ab282118b4665b01a03d47be7c05cc1b0</anchor>
      <arglist>(Dakota::ProblemDescDB &amp;problem_db_, const Teuchos::RCP&lt; Piro::Epetra::StokhosMPSolver &gt; &amp;model_, int p_index=0, int g_index=0)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>int</type>
      <name>derived_map_ac</name>
      <anchorfile>classTriKota_1_1MPDirectApplicInterface.html</anchorfile>
      <anchor>ac608f3019fcb9ef07bc5e3981d14aa5e</anchor>
      <arglist>(const Dakota::String &amp;ac_name)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>derived_map_asynch</name>
      <anchorfile>classTriKota_1_1MPDirectApplicInterface.html</anchorfile>
      <anchor>ace13f4f8ca56f2a79ef9cb4624d8e5b2</anchor>
      <arglist>(const Dakota::ParamResponsePair &amp;pair)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>wait_local_evaluations</name>
      <anchorfile>classTriKota_1_1MPDirectApplicInterface.html</anchorfile>
      <anchor>ac06fb7dc18b142d3082518badbf57368</anchor>
      <arglist>(Dakota::PRPQueue &amp;prp_queue)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Piro::Epetra::NECoupledModelEvaluator</name>
    <filename>classPiro_1_1Epetra_1_1NECoupledModelEvaluator.html</filename>
    <member kind="function">
      <type></type>
      <name>NECoupledModelEvaluator</name>
      <anchorfile>classPiro_1_1Epetra_1_1NECoupledModelEvaluator.html</anchorfile>
      <anchor>aeb52e197a4689b940c81a3282a67a053</anchor>
      <arglist>(const Teuchos::Array&lt; Teuchos::RCP&lt; EpetraExt::ModelEvaluator &gt; &gt; &amp;models, const Teuchos::Array&lt; Teuchos::RCP&lt; Teuchos::ParameterList &gt; &gt; &amp;piroParams, const Teuchos::RCP&lt; AbstractNetworkModel &gt; &amp;network_model, const Teuchos::RCP&lt; Teuchos::ParameterList &gt; &amp;params, const Teuchos::RCP&lt; const Epetra_Comm &gt; &amp;comm, const Teuchos::Array&lt; Teuchos::RCP&lt; NOX::Epetra::Observer &gt; &gt; &amp;observers=Teuchos::Array&lt; Teuchos::RCP&lt; NOX::Epetra::Observer &gt; &gt;())</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Epetra_Map &gt;</type>
      <name>get_x_map</name>
      <anchorfile>classPiro_1_1Epetra_1_1NECoupledModelEvaluator.html</anchorfile>
      <anchor>afdc08dd5f7f2956121bd5011b32a7262</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Epetra_Map &gt;</type>
      <name>get_f_map</name>
      <anchorfile>classPiro_1_1Epetra_1_1NECoupledModelEvaluator.html</anchorfile>
      <anchor>a3ed0491e834c07af840129c7b7751ae8</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Epetra_Vector &gt;</type>
      <name>get_x_init</name>
      <anchorfile>classPiro_1_1Epetra_1_1NECoupledModelEvaluator.html</anchorfile>
      <anchor>adfc6d5cd10f5ecd5f5a51acc36cf6c94</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Epetra_Map &gt;</type>
      <name>get_p_map</name>
      <anchorfile>classPiro_1_1Epetra_1_1NECoupledModelEvaluator.html</anchorfile>
      <anchor>afc5bc5816888d31106126f4af78e229e</anchor>
      <arglist>(int l) const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Epetra_Map &gt;</type>
      <name>get_g_map</name>
      <anchorfile>classPiro_1_1Epetra_1_1NECoupledModelEvaluator.html</anchorfile>
      <anchor>a84e3521e3387229aefff3e6ee468871d</anchor>
      <arglist>(int j) const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Teuchos::Array&lt; std::string &gt; &gt;</type>
      <name>get_p_names</name>
      <anchorfile>classPiro_1_1Epetra_1_1NECoupledModelEvaluator.html</anchorfile>
      <anchor>a87c107c8a3acb8a109ef25d9e23369d1</anchor>
      <arglist>(int l) const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Epetra_Vector &gt;</type>
      <name>get_p_init</name>
      <anchorfile>classPiro_1_1Epetra_1_1NECoupledModelEvaluator.html</anchorfile>
      <anchor>a53308eda5e9387dd0c32392bcd7e78a3</anchor>
      <arglist>(int l) const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; Epetra_Operator &gt;</type>
      <name>create_W</name>
      <anchorfile>classPiro_1_1Epetra_1_1NECoupledModelEvaluator.html</anchorfile>
      <anchor>ae16fe5956681cb1d5f772ab39554179e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>InArgs</type>
      <name>createInArgs</name>
      <anchorfile>classPiro_1_1Epetra_1_1NECoupledModelEvaluator.html</anchorfile>
      <anchor>a92e4a0d8d83216e4852c5a3950a00be4</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>OutArgs</type>
      <name>createOutArgs</name>
      <anchorfile>classPiro_1_1Epetra_1_1NECoupledModelEvaluator.html</anchorfile>
      <anchor>a3efcf43feeeec87a5d1f9d53fb1c2813</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>evalModel</name>
      <anchorfile>classPiro_1_1Epetra_1_1NECoupledModelEvaluator.html</anchorfile>
      <anchor>a82c378f513ac790537bb1653e078bf51</anchor>
      <arglist>(const InArgs &amp;inArgs, const OutArgs &amp;outArgs) const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Epetra_Map &gt;</type>
      <name>get_x_map</name>
      <anchorfile>classPiro_1_1Epetra_1_1NECoupledModelEvaluator.html</anchorfile>
      <anchor>afdc08dd5f7f2956121bd5011b32a7262</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Epetra_Map &gt;</type>
      <name>get_f_map</name>
      <anchorfile>classPiro_1_1Epetra_1_1NECoupledModelEvaluator.html</anchorfile>
      <anchor>a3ed0491e834c07af840129c7b7751ae8</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Epetra_Vector &gt;</type>
      <name>get_x_init</name>
      <anchorfile>classPiro_1_1Epetra_1_1NECoupledModelEvaluator.html</anchorfile>
      <anchor>adfc6d5cd10f5ecd5f5a51acc36cf6c94</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Epetra_Map &gt;</type>
      <name>get_p_map</name>
      <anchorfile>classPiro_1_1Epetra_1_1NECoupledModelEvaluator.html</anchorfile>
      <anchor>afc5bc5816888d31106126f4af78e229e</anchor>
      <arglist>(int l) const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Epetra_Map &gt;</type>
      <name>get_g_map</name>
      <anchorfile>classPiro_1_1Epetra_1_1NECoupledModelEvaluator.html</anchorfile>
      <anchor>a84e3521e3387229aefff3e6ee468871d</anchor>
      <arglist>(int j) const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Teuchos::Array&lt; std::string &gt; &gt;</type>
      <name>get_p_names</name>
      <anchorfile>classPiro_1_1Epetra_1_1NECoupledModelEvaluator.html</anchorfile>
      <anchor>a87c107c8a3acb8a109ef25d9e23369d1</anchor>
      <arglist>(int l) const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Epetra_Vector &gt;</type>
      <name>get_p_init</name>
      <anchorfile>classPiro_1_1Epetra_1_1NECoupledModelEvaluator.html</anchorfile>
      <anchor>a53308eda5e9387dd0c32392bcd7e78a3</anchor>
      <arglist>(int l) const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; Epetra_Operator &gt;</type>
      <name>create_W</name>
      <anchorfile>classPiro_1_1Epetra_1_1NECoupledModelEvaluator.html</anchorfile>
      <anchor>ae16fe5956681cb1d5f772ab39554179e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>InArgs</type>
      <name>createInArgs</name>
      <anchorfile>classPiro_1_1Epetra_1_1NECoupledModelEvaluator.html</anchorfile>
      <anchor>a92e4a0d8d83216e4852c5a3950a00be4</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>OutArgs</type>
      <name>createOutArgs</name>
      <anchorfile>classPiro_1_1Epetra_1_1NECoupledModelEvaluator.html</anchorfile>
      <anchor>a3efcf43feeeec87a5d1f9d53fb1c2813</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>evalModel</name>
      <anchorfile>classPiro_1_1Epetra_1_1NECoupledModelEvaluator.html</anchorfile>
      <anchor>a82c378f513ac790537bb1653e078bf51</anchor>
      <arglist>(const InArgs &amp;inArgs, const OutArgs &amp;outArgs) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Piro::Epetra::NewmarkDecorator</name>
    <filename>classPiro_1_1Epetra_1_1NewmarkDecorator.html</filename>
    <member kind="function">
      <type></type>
      <name>NewmarkDecorator</name>
      <anchorfile>classPiro_1_1Epetra_1_1NewmarkDecorator.html</anchorfile>
      <anchor>a3619a581474e2095210b0207e055fa3c</anchor>
      <arglist>(Teuchos::RCP&lt; EpetraExt::ModelEvaluator &gt; &amp;model, double beta_, double gamma_)</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Epetra_Vector &gt;</type>
      <name>get_p_init</name>
      <anchorfile>classPiro_1_1Epetra_1_1NewmarkDecorator.html</anchorfile>
      <anchor>a39641fd122af1c7d40ff808f5c9c7fb2</anchor>
      <arglist>(int l) const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; Epetra_Operator &gt;</type>
      <name>create_W</name>
      <anchorfile>classPiro_1_1Epetra_1_1NewmarkDecorator.html</anchorfile>
      <anchor>aa1134b03688227362b99db01fa6b5fbe</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>EpetraExt::ModelEvaluator::InArgs</type>
      <name>createInArgs</name>
      <anchorfile>classPiro_1_1Epetra_1_1NewmarkDecorator.html</anchorfile>
      <anchor>ac6a889ac04a620418cfea19872c51c94</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>EpetraExt::ModelEvaluator::OutArgs</type>
      <name>createOutArgs</name>
      <anchorfile>classPiro_1_1Epetra_1_1NewmarkDecorator.html</anchorfile>
      <anchor>a7cee6993200cde9eb0b6171979d9e8dd</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>evalModel</name>
      <anchorfile>classPiro_1_1Epetra_1_1NewmarkDecorator.html</anchorfile>
      <anchor>aaedc3b50cfbd0fa52603f5b6d25f5e6d</anchor>
      <arglist>(const InArgs &amp;inArgs, const OutArgs &amp;outArgs) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>injectData</name>
      <anchorfile>classPiro_1_1Epetra_1_1NewmarkDecorator.html</anchorfile>
      <anchor>a182d45bcf70a38a878a41febc6ddb122</anchor>
      <arglist>(const Teuchos::RCP&lt; Epetra_Vector &gt; &amp;acceleration_, const Teuchos::RCP&lt; Epetra_Vector &gt; &amp;velocity_pred_, const Teuchos::RCP&lt; Epetra_Vector &gt; &amp;displacement_pred_, double delta_t_, double time_)</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Epetra_Map &gt;</type>
      <name>get_x_map</name>
      <anchorfile>classPiro_1_1Epetra_1_1NewmarkDecorator.html</anchorfile>
      <anchor>a5c6ac0bd520db7da751674e71ea64852</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Epetra_Map &gt;</type>
      <name>get_f_map</name>
      <anchorfile>classPiro_1_1Epetra_1_1NewmarkDecorator.html</anchorfile>
      <anchor>a19dff2d490d529570138469854b25dcb</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Epetra_Vector &gt;</type>
      <name>get_x_init</name>
      <anchorfile>classPiro_1_1Epetra_1_1NewmarkDecorator.html</anchorfile>
      <anchor>a07c73d87899593dea7a5d2771d887408</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Epetra_Vector &gt;</type>
      <name>get_x_dot_init</name>
      <anchorfile>classPiro_1_1Epetra_1_1NewmarkDecorator.html</anchorfile>
      <anchor>a48c27b54fd575ca0d4ca2bf2fc2173fe</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Epetra_Vector &gt;</type>
      <name>get_x_dotdot_init</name>
      <anchorfile>classPiro_1_1Epetra_1_1NewmarkDecorator.html</anchorfile>
      <anchor>ab89d684aab07b0b4e3a21e7472bb3f93</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Epetra_Map &gt;</type>
      <name>get_p_map</name>
      <anchorfile>classPiro_1_1Epetra_1_1NewmarkDecorator.html</anchorfile>
      <anchor>a8fbac4e351671445dbef1412ef637686</anchor>
      <arglist>(int l) const </arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>NewmarkDecorator</name>
      <anchorfile>classPiro_1_1Epetra_1_1NewmarkDecorator.html</anchorfile>
      <anchor>a3619a581474e2095210b0207e055fa3c</anchor>
      <arglist>(Teuchos::RCP&lt; EpetraExt::ModelEvaluator &gt; &amp;model, double beta_, double gamma_)</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Epetra_Vector &gt;</type>
      <name>get_p_init</name>
      <anchorfile>classPiro_1_1Epetra_1_1NewmarkDecorator.html</anchorfile>
      <anchor>a39641fd122af1c7d40ff808f5c9c7fb2</anchor>
      <arglist>(int l) const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; Epetra_Operator &gt;</type>
      <name>create_W</name>
      <anchorfile>classPiro_1_1Epetra_1_1NewmarkDecorator.html</anchorfile>
      <anchor>aa1134b03688227362b99db01fa6b5fbe</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>EpetraExt::ModelEvaluator::InArgs</type>
      <name>createInArgs</name>
      <anchorfile>classPiro_1_1Epetra_1_1NewmarkDecorator.html</anchorfile>
      <anchor>ac6a889ac04a620418cfea19872c51c94</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>EpetraExt::ModelEvaluator::OutArgs</type>
      <name>createOutArgs</name>
      <anchorfile>classPiro_1_1Epetra_1_1NewmarkDecorator.html</anchorfile>
      <anchor>a7cee6993200cde9eb0b6171979d9e8dd</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>evalModel</name>
      <anchorfile>classPiro_1_1Epetra_1_1NewmarkDecorator.html</anchorfile>
      <anchor>aaedc3b50cfbd0fa52603f5b6d25f5e6d</anchor>
      <arglist>(const InArgs &amp;inArgs, const OutArgs &amp;outArgs) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>injectData</name>
      <anchorfile>classPiro_1_1Epetra_1_1NewmarkDecorator.html</anchorfile>
      <anchor>a182d45bcf70a38a878a41febc6ddb122</anchor>
      <arglist>(const Teuchos::RCP&lt; Epetra_Vector &gt; &amp;acceleration_, const Teuchos::RCP&lt; Epetra_Vector &gt; &amp;velocity_pred_, const Teuchos::RCP&lt; Epetra_Vector &gt; &amp;displacement_pred_, double delta_t_, double time_)</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Epetra_Map &gt;</type>
      <name>get_x_map</name>
      <anchorfile>classPiro_1_1Epetra_1_1NewmarkDecorator.html</anchorfile>
      <anchor>a5c6ac0bd520db7da751674e71ea64852</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Epetra_Map &gt;</type>
      <name>get_f_map</name>
      <anchorfile>classPiro_1_1Epetra_1_1NewmarkDecorator.html</anchorfile>
      <anchor>a19dff2d490d529570138469854b25dcb</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Epetra_Vector &gt;</type>
      <name>get_x_init</name>
      <anchorfile>classPiro_1_1Epetra_1_1NewmarkDecorator.html</anchorfile>
      <anchor>a07c73d87899593dea7a5d2771d887408</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Epetra_Vector &gt;</type>
      <name>get_x_dot_init</name>
      <anchorfile>classPiro_1_1Epetra_1_1NewmarkDecorator.html</anchorfile>
      <anchor>a48c27b54fd575ca0d4ca2bf2fc2173fe</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Epetra_Vector &gt;</type>
      <name>get_x_dotdot_init</name>
      <anchorfile>classPiro_1_1Epetra_1_1NewmarkDecorator.html</anchorfile>
      <anchor>ab89d684aab07b0b4e3a21e7472bb3f93</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Epetra_Map &gt;</type>
      <name>get_p_map</name>
      <anchorfile>classPiro_1_1Epetra_1_1NewmarkDecorator.html</anchorfile>
      <anchor>a8fbac4e351671445dbef1412ef637686</anchor>
      <arglist>(int l) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Piro::Epetra::NewmarkSolver</name>
    <filename>classPiro_1_1Epetra_1_1NewmarkSolver.html</filename>
    <member kind="function">
      <type></type>
      <name>NewmarkSolver</name>
      <anchorfile>classPiro_1_1Epetra_1_1NewmarkSolver.html</anchorfile>
      <anchor>a60f5458812e72ca7584d6b57f84bd3c2</anchor>
      <arglist>(Teuchos::RCP&lt; Teuchos::ParameterList &gt; appParams, Teuchos::RCP&lt; EpetraExt::ModelEvaluator &gt; model, Teuchos::RCP&lt; NOX::Epetra::Observer &gt; observer=Teuchos::null)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>NewmarkSolver</name>
      <anchorfile>classPiro_1_1Epetra_1_1NewmarkSolver.html</anchorfile>
      <anchor>a60f5458812e72ca7584d6b57f84bd3c2</anchor>
      <arglist>(Teuchos::RCP&lt; Teuchos::ParameterList &gt; appParams, Teuchos::RCP&lt; EpetraExt::ModelEvaluator &gt; model, Teuchos::RCP&lt; NOX::Epetra::Observer &gt; observer=Teuchos::null)</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Epetra_Vector &gt;</type>
      <name>get_p_init</name>
      <anchorfile>classPiro_1_1Epetra_1_1NewmarkSolver.html</anchorfile>
      <anchor>aaadf4edaaccf596ad0a4c30451664c96</anchor>
      <arglist>(int l) const </arglist>
    </member>
    <member kind="function">
      <type>EpetraExt::ModelEvaluator::InArgs</type>
      <name>createInArgs</name>
      <anchorfile>classPiro_1_1Epetra_1_1NewmarkSolver.html</anchorfile>
      <anchor>a8553bb5de4021d1e004e785e17700a01</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>EpetraExt::ModelEvaluator::OutArgs</type>
      <name>createOutArgs</name>
      <anchorfile>classPiro_1_1Epetra_1_1NewmarkSolver.html</anchorfile>
      <anchor>aef59d1139389bb22c0c19d02652db4f2</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>evalModel</name>
      <anchorfile>classPiro_1_1Epetra_1_1NewmarkSolver.html</anchorfile>
      <anchor>ac1a295417e60f011b34851e5e460d4fa</anchor>
      <arglist>(const InArgs &amp;inArgs, const OutArgs &amp;outArgs) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Piro::Epetra::NOXSolver</name>
    <filename>classPiro_1_1Epetra_1_1NOXSolver.html</filename>
    <member kind="function">
      <type></type>
      <name>NOXSolver</name>
      <anchorfile>classPiro_1_1Epetra_1_1NOXSolver.html</anchorfile>
      <anchor>ac279a07f9993ccc4a96ad47bbed12e7d</anchor>
      <arglist>(Teuchos::RCP&lt; Teuchos::ParameterList &gt; piroParams, Teuchos::RCP&lt; EpetraExt::ModelEvaluator &gt; model, Teuchos::RCP&lt; NOX::Epetra::Observer &gt; observer=Teuchos::null, Teuchos::RCP&lt; NOX::Epetra::ModelEvaluatorInterface &gt; interface=Teuchos::null, Teuchos::RCP&lt; NOX::Epetra::LinearSystem &gt; linsys=Teuchos::null)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>NOXSolver</name>
      <anchorfile>classPiro_1_1Epetra_1_1NOXSolver.html</anchorfile>
      <anchor>ac279a07f9993ccc4a96ad47bbed12e7d</anchor>
      <arglist>(Teuchos::RCP&lt; Teuchos::ParameterList &gt; piroParams, Teuchos::RCP&lt; EpetraExt::ModelEvaluator &gt; model, Teuchos::RCP&lt; NOX::Epetra::Observer &gt; observer=Teuchos::null, Teuchos::RCP&lt; NOX::Epetra::ModelEvaluatorInterface &gt; interface=Teuchos::null, Teuchos::RCP&lt; NOX::Epetra::LinearSystem &gt; linsys=Teuchos::null)</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Epetra_Vector &gt;</type>
      <name>get_p_init</name>
      <anchorfile>classPiro_1_1Epetra_1_1NOXSolver.html</anchorfile>
      <anchor>ac7fc9ae0f6c724fe658b639750f8aaa6</anchor>
      <arglist>(int l) const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Epetra_Vector &gt;</type>
      <name>get_p_lower_bounds</name>
      <anchorfile>classPiro_1_1Epetra_1_1NOXSolver.html</anchorfile>
      <anchor>a7b00e4485fba5e6cb25ab658a32922c3</anchor>
      <arglist>(int l) const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Epetra_Vector &gt;</type>
      <name>get_p_upper_bounds</name>
      <anchorfile>classPiro_1_1Epetra_1_1NOXSolver.html</anchorfile>
      <anchor>abd665374f025c180060096b7c832a6e3</anchor>
      <arglist>(int l) const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; Epetra_Operator &gt;</type>
      <name>create_DgDp_op</name>
      <anchorfile>classPiro_1_1Epetra_1_1NOXSolver.html</anchorfile>
      <anchor>af387f72ae04ef9adb05b2f09a581ac4b</anchor>
      <arglist>(int j, int l) const </arglist>
    </member>
    <member kind="function">
      <type>EpetraExt::ModelEvaluator::InArgs</type>
      <name>createInArgs</name>
      <anchorfile>classPiro_1_1Epetra_1_1NOXSolver.html</anchorfile>
      <anchor>ac05de07278fa48543474ac309aad9618</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>EpetraExt::ModelEvaluator::OutArgs</type>
      <name>createOutArgs</name>
      <anchorfile>classPiro_1_1Epetra_1_1NOXSolver.html</anchorfile>
      <anchor>aa0d1339360c980d9b971e69b0639092f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>evalModel</name>
      <anchorfile>classPiro_1_1Epetra_1_1NOXSolver.html</anchorfile>
      <anchor>aa82eb8dbecf54742acf1be084be5d579</anchor>
      <arglist>(const InArgs &amp;inArgs, const OutArgs &amp;outArgs) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Piro::NOXSolver</name>
    <filename>classPiro_1_1NOXSolver.html</filename>
    <templarg></templarg>
    <base>Piro::SteadyStateSolver</base>
    <member kind="function">
      <type></type>
      <name>NOXSolver</name>
      <anchorfile>classPiro_1_1NOXSolver.html</anchorfile>
      <anchor>a156ebbd1b855f7c5d751ddadbe137f6c</anchor>
      <arglist>(const Teuchos::RCP&lt; Teuchos::ParameterList &gt; &amp;appParams, const Teuchos::RCP&lt; Thyra::ModelEvaluator&lt; Scalar &gt; &gt; &amp;model, const Teuchos::RCP&lt; ObserverBase&lt; Scalar &gt; &gt; &amp;observer=Teuchos::null)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>NOXSolver</name>
      <anchorfile>classPiro_1_1NOXSolver.html</anchorfile>
      <anchor>a156ebbd1b855f7c5d751ddadbe137f6c</anchor>
      <arglist>(const Teuchos::RCP&lt; Teuchos::ParameterList &gt; &amp;appParams, const Teuchos::RCP&lt; Thyra::ModelEvaluator&lt; Scalar &gt; &gt; &amp;model, const Teuchos::RCP&lt; ObserverBase&lt; Scalar &gt; &gt; &amp;observer=Teuchos::null)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Piro::ObserverBase</name>
    <filename>classPiro_1_1ObserverBase.html</filename>
    <templarg></templarg>
  </compound>
  <compound kind="class">
    <name>Piro::ObserverToLOCASaveDataStrategyAdapter</name>
    <filename>classPiro_1_1ObserverToLOCASaveDataStrategyAdapter.html</filename>
  </compound>
  <compound kind="class">
    <name>Piro::ObserverToRythmosIntegrationObserverAdapter</name>
    <filename>classPiro_1_1ObserverToRythmosIntegrationObserverAdapter.html</filename>
    <templarg></templarg>
  </compound>
  <compound kind="class">
    <name>Piro::Epetra::ParamToResponseNetworkModel</name>
    <filename>classPiro_1_1Epetra_1_1ParamToResponseNetworkModel.html</filename>
    <base>Piro::Epetra::AbstractNetworkModel</base>
    <member kind="function">
      <type></type>
      <name>ParamToResponseNetworkModel</name>
      <anchorfile>classPiro_1_1Epetra_1_1ParamToResponseNetworkModel.html</anchorfile>
      <anchor>ab7a4c67b915d3588b30c267b816a7f28</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~ParamToResponseNetworkModel</name>
      <anchorfile>classPiro_1_1Epetra_1_1ParamToResponseNetworkModel.html</anchorfile>
      <anchor>ab759c4f273c96a547435ed2c9ad795bb</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>evalModel</name>
      <anchorfile>classPiro_1_1Epetra_1_1ParamToResponseNetworkModel.html</anchorfile>
      <anchor>ad5cdb3410082f37b221d5e8c51718932</anchor>
      <arglist>(const Teuchos::Array&lt; EpetraExt::ModelEvaluator::InArgs &gt; &amp;model_inargs, const Teuchos::Array&lt; EpetraExt::ModelEvaluator::OutArgs &gt; &amp;model_outargs, const EpetraExt::ModelEvaluator::InArgs &amp;network_inargs, const EpetraExt::ModelEvaluator::OutArgs &amp;network_outargs, const Teuchos::Array&lt; int &gt; &amp;n_p, const Teuchos::Array&lt; int &gt; &amp;n_g, const Teuchos::Array&lt; Teuchos::RCP&lt; Epetra_Vector &gt; &gt; &amp;p, const Teuchos::Array&lt; Teuchos::RCP&lt; Epetra_Vector &gt; &gt; &amp;g, const Teuchos::Array&lt; Teuchos::RCP&lt; Epetra_MultiVector &gt; &gt; &amp;dgdp, const Teuchos::Array&lt; EpetraExt::ModelEvaluator::EDerivativeMultiVectorOrientation &gt; &amp;dgdp_layout, const Teuchos::Array&lt; EpetraExt::ModelEvaluator::OutArgs::sg_vector_t &gt; &amp;p_sg, const Teuchos::Array&lt; EpetraExt::ModelEvaluator::OutArgs::sg_vector_t &gt; &amp;g_sg, const Teuchos::Array&lt; Teuchos::RCP&lt; Stokhos::EpetraMultiVectorOrthogPoly &gt; &gt; &amp;dgdp_sg, const Teuchos::Array&lt; EpetraExt::ModelEvaluator::EDerivativeMultiVectorOrientation &gt; &amp;dgdp_sg_layout) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Piro::Provider</name>
    <filename>classPiro_1_1Provider.html</filename>
    <templarg>T</templarg>
    <member kind="function">
      <type></type>
      <name>Provider</name>
      <anchorfile>classPiro_1_1Provider.html</anchorfile>
      <anchor>a199a0db8239dace66c1e77c51f72f52e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Provider</name>
      <anchorfile>classPiro_1_1Provider.html</anchorfile>
      <anchor>acbe275083c3c1932d3facafac5016700</anchor>
      <arglist>(Teuchos::ENull)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Provider</name>
      <anchorfile>classPiro_1_1Provider.html</anchorfile>
      <anchor>a8fceaa5c8948f456986afe96071b743e</anchor>
      <arglist>(const Teuchos::RCP&lt; U &gt; &amp;instance)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Provider</name>
      <anchorfile>classPiro_1_1Provider.html</anchorfile>
      <anchor>aeef76f30f31762caf0e949b7f91e25b2</anchor>
      <arglist>(const P &amp;p)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Provider</name>
      <anchorfile>classPiro_1_1Provider.html</anchorfile>
      <anchor>a1f33c3f49793aa15e9843da77dbd5064</anchor>
      <arglist>(const Teuchos::RCP&lt; ProviderBase&lt; T &gt; &gt; &amp;ptr_in)</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; T &gt;</type>
      <name>operator()</name>
      <anchorfile>classPiro_1_1Provider.html</anchorfile>
      <anchor>a2d659991bc4b6bf807bb728bf0355916</anchor>
      <arglist>(const Teuchos::RCP&lt; Teuchos::ParameterList &gt; &amp;params)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>nonnull</name>
      <anchorfile>classPiro_1_1Provider.html</anchorfile>
      <anchor>a31815576fef1d4a47a3ed9798a40d29c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>is_null</name>
      <anchorfile>classPiro_1_1Provider.html</anchorfile>
      <anchor>ae6e0b713a6d3bf97bd8790c8bf194ab3</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const ProviderBase&lt; T &gt; &gt;</type>
      <name>ptr</name>
      <anchorfile>classPiro_1_1Provider.html</anchorfile>
      <anchor>ad1c9a22dd5adf5dc3379647d7a9e9109</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; ProviderBase&lt; T &gt; &gt;</type>
      <name>ptr</name>
      <anchorfile>classPiro_1_1Provider.html</anchorfile>
      <anchor>a18caa197bd709ce94bafd3477654bbdc</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>nonnull</name>
      <anchorfile>classPiro_1_1Provider.html</anchorfile>
      <anchor>a45dad972f027ba721a0ec7e97daa39b5</anchor>
      <arglist>(const Provider&lt; T &gt; &amp;handle)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>is_null</name>
      <anchorfile>classPiro_1_1Provider.html</anchorfile>
      <anchor>a9f79a2e2f080731f989a315a829f45c4</anchor>
      <arglist>(const Provider&lt; T &gt; &amp;handle)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>nonnull</name>
      <anchorfile>classPiro_1_1Provider.html</anchorfile>
      <anchor>a45dad972f027ba721a0ec7e97daa39b5</anchor>
      <arglist>(const Provider&lt; T &gt; &amp;handle)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>is_null</name>
      <anchorfile>classPiro_1_1Provider.html</anchorfile>
      <anchor>a9f79a2e2f080731f989a315a829f45c4</anchor>
      <arglist>(const Provider&lt; T &gt; &amp;handle)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Provider</name>
      <anchorfile>classPiro_1_1Provider.html</anchorfile>
      <anchor>a199a0db8239dace66c1e77c51f72f52e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Provider</name>
      <anchorfile>classPiro_1_1Provider.html</anchorfile>
      <anchor>acbe275083c3c1932d3facafac5016700</anchor>
      <arglist>(Teuchos::ENull)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Provider</name>
      <anchorfile>classPiro_1_1Provider.html</anchorfile>
      <anchor>a8fceaa5c8948f456986afe96071b743e</anchor>
      <arglist>(const Teuchos::RCP&lt; U &gt; &amp;instance)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Provider</name>
      <anchorfile>classPiro_1_1Provider.html</anchorfile>
      <anchor>aeef76f30f31762caf0e949b7f91e25b2</anchor>
      <arglist>(const P &amp;p)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Provider</name>
      <anchorfile>classPiro_1_1Provider.html</anchorfile>
      <anchor>a1f33c3f49793aa15e9843da77dbd5064</anchor>
      <arglist>(const Teuchos::RCP&lt; ProviderBase&lt; T &gt; &gt; &amp;ptr_in)</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; T &gt;</type>
      <name>operator()</name>
      <anchorfile>classPiro_1_1Provider.html</anchorfile>
      <anchor>a2d659991bc4b6bf807bb728bf0355916</anchor>
      <arglist>(const Teuchos::RCP&lt; Teuchos::ParameterList &gt; &amp;params)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>nonnull</name>
      <anchorfile>classPiro_1_1Provider.html</anchorfile>
      <anchor>a31815576fef1d4a47a3ed9798a40d29c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>is_null</name>
      <anchorfile>classPiro_1_1Provider.html</anchorfile>
      <anchor>ae6e0b713a6d3bf97bd8790c8bf194ab3</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const ProviderBase&lt; T &gt; &gt;</type>
      <name>ptr</name>
      <anchorfile>classPiro_1_1Provider.html</anchorfile>
      <anchor>ad1c9a22dd5adf5dc3379647d7a9e9109</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; ProviderBase&lt; T &gt; &gt;</type>
      <name>ptr</name>
      <anchorfile>classPiro_1_1Provider.html</anchorfile>
      <anchor>a18caa197bd709ce94bafd3477654bbdc</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Piro::ProviderBase</name>
    <filename>classPiro_1_1ProviderBase.html</filename>
    <templarg></templarg>
    <member kind="function" virtualness="pure">
      <type>virtual Teuchos::RCP&lt; T &gt;</type>
      <name>getInstance</name>
      <anchorfile>classPiro_1_1ProviderBase.html</anchorfile>
      <anchor>aaffc4318894425eb480ef394d9525e1d</anchor>
      <arglist>(const Teuchos::RCP&lt; Teuchos::ParameterList &gt; &amp;params)=0</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ProviderBase</name>
      <anchorfile>classPiro_1_1ProviderBase.html</anchorfile>
      <anchor>aa037165a04495a77d26517716c4ad73e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~ProviderBase</name>
      <anchorfile>classPiro_1_1ProviderBase.html</anchorfile>
      <anchor>a9b3c9e68ebdc9b21c52a0f3db216229a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ProviderBase</name>
      <anchorfile>classPiro_1_1ProviderBase.html</anchorfile>
      <anchor>aa037165a04495a77d26517716c4ad73e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~ProviderBase</name>
      <anchorfile>classPiro_1_1ProviderBase.html</anchorfile>
      <anchor>a9b3c9e68ebdc9b21c52a0f3db216229a</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Piro::RythmosNOXRowSumUpdaterObserver</name>
    <filename>classPiro_1_1RythmosNOXRowSumUpdaterObserver.html</filename>
    <templarg></templarg>
    <member kind="function">
      <type>Teuchos::RCP&lt; RythmosNOXRowSumUpdaterObserver&lt; Scalar &gt; &gt;</type>
      <name>createRythmosNOXRowSumUpdaterObserver</name>
      <anchorfile>classPiro_1_1RythmosNOXRowSumUpdaterObserver.html</anchorfile>
      <anchor>a7a45485fa517aafdbe88952c0ff515ef</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Piro::RythmosSolver</name>
    <filename>classPiro_1_1RythmosSolver.html</filename>
    <templarg></templarg>
    <member kind="function">
      <type></type>
      <name>RythmosSolver</name>
      <anchorfile>classPiro_1_1RythmosSolver.html</anchorfile>
      <anchor>a2f416b8462703e59704547724e4ef315</anchor>
      <arglist>(const Teuchos::RCP&lt; Rythmos::DefaultIntegrator&lt; Scalar &gt; &gt; &amp;stateIntegrator, const Teuchos::RCP&lt; Rythmos::StepperBase&lt; Scalar &gt; &gt; &amp;stateStepper, const Teuchos::RCP&lt; Thyra::NonlinearSolverBase&lt; Scalar &gt; &gt; &amp;timeStepSolver, const Teuchos::RCP&lt; Thyra::ModelEvaluator&lt; Scalar &gt; &gt; &amp;model, Scalar initialTime, Scalar finalTime, const Teuchos::RCP&lt; Thyra::ModelEvaluator&lt; Scalar &gt; &gt; &amp;initialConditionModel=Teuchos::null, Teuchos::EVerbosityLevel verbosityLevel=Teuchos::VERB_DEFAULT)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>RythmosSolver</name>
      <anchorfile>classPiro_1_1RythmosSolver.html</anchorfile>
      <anchor>a3cd364043a7359b395e7b64ffded6a11</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>RythmosSolver</name>
      <anchorfile>classPiro_1_1RythmosSolver.html</anchorfile>
      <anchor>a0b74ceaacf03657554f22d6b2dde322e</anchor>
      <arglist>(const Teuchos::RCP&lt; Teuchos::ParameterList &gt; &amp;appParams, const Teuchos::RCP&lt; Thyra::ModelEvaluator&lt; Scalar &gt; &gt; &amp;model, const Teuchos::RCP&lt; Rythmos::IntegrationObserverBase&lt; Scalar &gt; &gt; &amp;observer=Teuchos::null)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>RythmosSolver</name>
      <anchorfile>classPiro_1_1RythmosSolver.html</anchorfile>
      <anchor>a3727c665fe7a51b4183e8b0721954691</anchor>
      <arglist>(const Teuchos::RCP&lt; Rythmos::DefaultIntegrator&lt; Scalar &gt; &gt; &amp;stateIntegrator, const Teuchos::RCP&lt; Rythmos::StepperBase&lt; Scalar &gt; &gt; &amp;stateStepper, const Teuchos::RCP&lt; Thyra::NonlinearSolverBase&lt; Scalar &gt; &gt; &amp;timeStepSolver, const Teuchos::RCP&lt; Thyra::ModelEvaluator&lt; Scalar &gt; &gt; &amp;model, Scalar finalTime, const Teuchos::RCP&lt; Thyra::ModelEvaluator&lt; Scalar &gt; &gt; &amp;initialConditionModel=Teuchos::null, Teuchos::EVerbosityLevel verbosityLevel=Teuchos::VERB_DEFAULT)</arglist>
    </member>
    <member kind="function">
      <type>Thyra::ModelEvaluatorBase::InArgs&lt; Scalar &gt;</type>
      <name>getNominalValues</name>
      <anchorfile>classPiro_1_1RythmosSolver.html</anchorfile>
      <anchor>adbb2f9bcc9379d68aff63703a530a80a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Thyra::ModelEvaluatorBase::InArgs&lt; Scalar &gt;</type>
      <name>createInArgs</name>
      <anchorfile>classPiro_1_1RythmosSolver.html</anchorfile>
      <anchor>a20b00927f0f8c561581f82d86145656e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Thyra::VectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>get_p_space</name>
      <anchorfile>classPiro_1_1RythmosSolver.html</anchorfile>
      <anchor>a14d8e406fa373c95eaa23f44c6c867b1</anchor>
      <arglist>(int l) const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Thyra::VectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>get_g_space</name>
      <anchorfile>classPiro_1_1RythmosSolver.html</anchorfile>
      <anchor>a205fe7308bb8f3cb37fa23fa423a9d20</anchor>
      <arglist>(int j) const </arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>RythmosSolver</name>
      <anchorfile>classPiro_1_1RythmosSolver.html</anchorfile>
      <anchor>a3cd364043a7359b395e7b64ffded6a11</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>RythmosSolver</name>
      <anchorfile>classPiro_1_1RythmosSolver.html</anchorfile>
      <anchor>a0b74ceaacf03657554f22d6b2dde322e</anchor>
      <arglist>(const Teuchos::RCP&lt; Teuchos::ParameterList &gt; &amp;appParams, const Teuchos::RCP&lt; Thyra::ModelEvaluator&lt; Scalar &gt; &gt; &amp;model, const Teuchos::RCP&lt; Rythmos::IntegrationObserverBase&lt; Scalar &gt; &gt; &amp;observer=Teuchos::null)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>RythmosSolver</name>
      <anchorfile>classPiro_1_1RythmosSolver.html</anchorfile>
      <anchor>a3727c665fe7a51b4183e8b0721954691</anchor>
      <arglist>(const Teuchos::RCP&lt; Rythmos::DefaultIntegrator&lt; Scalar &gt; &gt; &amp;stateIntegrator, const Teuchos::RCP&lt; Rythmos::StepperBase&lt; Scalar &gt; &gt; &amp;stateStepper, const Teuchos::RCP&lt; Thyra::NonlinearSolverBase&lt; Scalar &gt; &gt; &amp;timeStepSolver, const Teuchos::RCP&lt; Thyra::ModelEvaluator&lt; Scalar &gt; &gt; &amp;model, Scalar finalTime, const Teuchos::RCP&lt; Thyra::ModelEvaluator&lt; Scalar &gt; &gt; &amp;initialConditionModel=Teuchos::null, Teuchos::EVerbosityLevel verbosityLevel=Teuchos::VERB_DEFAULT)</arglist>
    </member>
    <member kind="function">
      <type>Thyra::ModelEvaluatorBase::InArgs&lt; Scalar &gt;</type>
      <name>getNominalValues</name>
      <anchorfile>classPiro_1_1RythmosSolver.html</anchorfile>
      <anchor>adbb2f9bcc9379d68aff63703a530a80a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Thyra::ModelEvaluatorBase::InArgs&lt; Scalar &gt;</type>
      <name>createInArgs</name>
      <anchorfile>classPiro_1_1RythmosSolver.html</anchorfile>
      <anchor>a20b00927f0f8c561581f82d86145656e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Thyra::VectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>get_p_space</name>
      <anchorfile>classPiro_1_1RythmosSolver.html</anchorfile>
      <anchor>a14d8e406fa373c95eaa23f44c6c867b1</anchor>
      <arglist>(int l) const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Thyra::VectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>get_g_space</name>
      <anchorfile>classPiro_1_1RythmosSolver.html</anchorfile>
      <anchor>a205fe7308bb8f3cb37fa23fa423a9d20</anchor>
      <arglist>(int j) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Piro::Epetra::RythmosSolver</name>
    <filename>classPiro_1_1Epetra_1_1RythmosSolver.html</filename>
    <member kind="function">
      <type></type>
      <name>RythmosSolver</name>
      <anchorfile>classPiro_1_1Epetra_1_1RythmosSolver.html</anchorfile>
      <anchor>a9b477e58182399ff0e3ec2cd4182a5ac</anchor>
      <arglist>(const Teuchos::RCP&lt; Rythmos::DefaultIntegrator&lt; double &gt; &gt; &amp;stateIntegrator, const Teuchos::RCP&lt; Rythmos::StepperBase&lt; double &gt; &gt; &amp;stateStepper, const Teuchos::RCP&lt; Rythmos::TimeStepNonlinearSolver&lt; double &gt; &gt; &amp;timeStepSolver, const Teuchos::RCP&lt; EpetraExt::ModelEvaluator &gt; &amp;model, const Teuchos::RCP&lt; Thyra::LinearOpWithSolveFactoryBase&lt; double &gt; &gt; &amp;lowsFactory, double initialTime, double finalTime, Teuchos::EVerbosityLevel verbosityLevel=Teuchos::VERB_DEFAULT)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>RythmosSolver</name>
      <anchorfile>classPiro_1_1Epetra_1_1RythmosSolver.html</anchorfile>
      <anchor>aafebecdfd2f1f463291d36276b2e70dc</anchor>
      <arglist>(Teuchos::RCP&lt; Teuchos::ParameterList &gt; piroParams, Teuchos::RCP&lt; EpetraExt::ModelEvaluator &gt; model, Teuchos::RCP&lt; Rythmos::IntegrationObserverBase&lt; double &gt; &gt; observer=Teuchos::null)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>RythmosSolver</name>
      <anchorfile>classPiro_1_1Epetra_1_1RythmosSolver.html</anchorfile>
      <anchor>a3c13f7d5316f6f0b8485dd2a6200709c</anchor>
      <arglist>(const Teuchos::RCP&lt; Rythmos::DefaultIntegrator&lt; double &gt; &gt; &amp;stateIntegrator, const Teuchos::RCP&lt; Rythmos::StepperBase&lt; double &gt; &gt; &amp;stateStepper, const Teuchos::RCP&lt; Rythmos::TimeStepNonlinearSolver&lt; double &gt; &gt; &amp;timeStepSolver, const Teuchos::RCP&lt; EpetraExt::ModelEvaluator &gt; &amp;model, const Teuchos::RCP&lt; Thyra::LinearOpWithSolveFactoryBase&lt; double &gt; &gt; &amp;lowsFactory, double finalTime, Teuchos::EVerbosityLevel verbosityLevel=Teuchos::VERB_DEFAULT)</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Epetra_Map &gt;</type>
      <name>get_x_map</name>
      <anchorfile>classPiro_1_1Epetra_1_1RythmosSolver.html</anchorfile>
      <anchor>abd5fbca23f97d53f548a5176e107db57</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Epetra_Map &gt;</type>
      <name>get_f_map</name>
      <anchorfile>classPiro_1_1Epetra_1_1RythmosSolver.html</anchorfile>
      <anchor>a6235b2b8f1633d4fafdb0a024eca3370</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Epetra_Map &gt;</type>
      <name>get_p_map</name>
      <anchorfile>classPiro_1_1Epetra_1_1RythmosSolver.html</anchorfile>
      <anchor>aba800796ca71d989113d915388770019</anchor>
      <arglist>(int l) const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Epetra_Map &gt;</type>
      <name>get_g_map</name>
      <anchorfile>classPiro_1_1Epetra_1_1RythmosSolver.html</anchorfile>
      <anchor>a4cb48dfaa6a0d88cd0bd9f03398e316f</anchor>
      <arglist>(int j) const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Epetra_Vector &gt;</type>
      <name>get_x_init</name>
      <anchorfile>classPiro_1_1Epetra_1_1RythmosSolver.html</anchorfile>
      <anchor>a1a895b6683475733df42989163c2ab9d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Epetra_Vector &gt;</type>
      <name>get_p_init</name>
      <anchorfile>classPiro_1_1Epetra_1_1RythmosSolver.html</anchorfile>
      <anchor>a44f3e9852f711433abff756e385808ec</anchor>
      <arglist>(int l) const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; Epetra_Operator &gt;</type>
      <name>create_DgDp_op</name>
      <anchorfile>classPiro_1_1Epetra_1_1RythmosSolver.html</anchorfile>
      <anchor>a65eceb16803749403dde721d015bbbfe</anchor>
      <arglist>(int j, int l) const </arglist>
    </member>
    <member kind="function">
      <type>EpetraExt::ModelEvaluator::InArgs</type>
      <name>createInArgs</name>
      <anchorfile>classPiro_1_1Epetra_1_1RythmosSolver.html</anchorfile>
      <anchor>afe6df27ff27dc0753873dc9440deb581</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>EpetraExt::ModelEvaluator::OutArgs</type>
      <name>createOutArgs</name>
      <anchorfile>classPiro_1_1Epetra_1_1RythmosSolver.html</anchorfile>
      <anchor>a8a9e6b9d2d6d6f6fe98caf8a1aa3a473</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>evalModel</name>
      <anchorfile>classPiro_1_1Epetra_1_1RythmosSolver.html</anchorfile>
      <anchor>af933db710e644d634493a5e5e15673cd</anchor>
      <arglist>(const InArgs &amp;inArgs, const OutArgs &amp;outArgs) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Np</name>
      <anchorfile>classPiro_1_1Epetra_1_1RythmosSolver.html</anchorfile>
      <anchor>a8caae71adf201e58802a3ce80296f8df</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Ng</name>
      <anchorfile>classPiro_1_1Epetra_1_1RythmosSolver.html</anchorfile>
      <anchor>abbaeddc74a17f90a271c7a90890fdb3d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>RythmosSolver</name>
      <anchorfile>classPiro_1_1Epetra_1_1RythmosSolver.html</anchorfile>
      <anchor>aafebecdfd2f1f463291d36276b2e70dc</anchor>
      <arglist>(Teuchos::RCP&lt; Teuchos::ParameterList &gt; piroParams, Teuchos::RCP&lt; EpetraExt::ModelEvaluator &gt; model, Teuchos::RCP&lt; Rythmos::IntegrationObserverBase&lt; double &gt; &gt; observer=Teuchos::null)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>RythmosSolver</name>
      <anchorfile>classPiro_1_1Epetra_1_1RythmosSolver.html</anchorfile>
      <anchor>a3c13f7d5316f6f0b8485dd2a6200709c</anchor>
      <arglist>(const Teuchos::RCP&lt; Rythmos::DefaultIntegrator&lt; double &gt; &gt; &amp;stateIntegrator, const Teuchos::RCP&lt; Rythmos::StepperBase&lt; double &gt; &gt; &amp;stateStepper, const Teuchos::RCP&lt; Rythmos::TimeStepNonlinearSolver&lt; double &gt; &gt; &amp;timeStepSolver, const Teuchos::RCP&lt; EpetraExt::ModelEvaluator &gt; &amp;model, const Teuchos::RCP&lt; Thyra::LinearOpWithSolveFactoryBase&lt; double &gt; &gt; &amp;lowsFactory, double finalTime, Teuchos::EVerbosityLevel verbosityLevel=Teuchos::VERB_DEFAULT)</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Epetra_Map &gt;</type>
      <name>get_x_map</name>
      <anchorfile>classPiro_1_1Epetra_1_1RythmosSolver.html</anchorfile>
      <anchor>abd5fbca23f97d53f548a5176e107db57</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Epetra_Map &gt;</type>
      <name>get_f_map</name>
      <anchorfile>classPiro_1_1Epetra_1_1RythmosSolver.html</anchorfile>
      <anchor>a6235b2b8f1633d4fafdb0a024eca3370</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Epetra_Map &gt;</type>
      <name>get_p_map</name>
      <anchorfile>classPiro_1_1Epetra_1_1RythmosSolver.html</anchorfile>
      <anchor>aba800796ca71d989113d915388770019</anchor>
      <arglist>(int l) const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Epetra_Map &gt;</type>
      <name>get_g_map</name>
      <anchorfile>classPiro_1_1Epetra_1_1RythmosSolver.html</anchorfile>
      <anchor>a4cb48dfaa6a0d88cd0bd9f03398e316f</anchor>
      <arglist>(int j) const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Epetra_Vector &gt;</type>
      <name>get_x_init</name>
      <anchorfile>classPiro_1_1Epetra_1_1RythmosSolver.html</anchorfile>
      <anchor>a1a895b6683475733df42989163c2ab9d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Epetra_Vector &gt;</type>
      <name>get_p_init</name>
      <anchorfile>classPiro_1_1Epetra_1_1RythmosSolver.html</anchorfile>
      <anchor>a44f3e9852f711433abff756e385808ec</anchor>
      <arglist>(int l) const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; Epetra_Operator &gt;</type>
      <name>create_DgDp_op</name>
      <anchorfile>classPiro_1_1Epetra_1_1RythmosSolver.html</anchorfile>
      <anchor>a65eceb16803749403dde721d015bbbfe</anchor>
      <arglist>(int j, int l) const </arglist>
    </member>
    <member kind="function">
      <type>EpetraExt::ModelEvaluator::InArgs</type>
      <name>createInArgs</name>
      <anchorfile>classPiro_1_1Epetra_1_1RythmosSolver.html</anchorfile>
      <anchor>afe6df27ff27dc0753873dc9440deb581</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>EpetraExt::ModelEvaluator::OutArgs</type>
      <name>createOutArgs</name>
      <anchorfile>classPiro_1_1Epetra_1_1RythmosSolver.html</anchorfile>
      <anchor>a8a9e6b9d2d6d6f6fe98caf8a1aa3a473</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>evalModel</name>
      <anchorfile>classPiro_1_1Epetra_1_1RythmosSolver.html</anchorfile>
      <anchor>af933db710e644d634493a5e5e15673cd</anchor>
      <arglist>(const InArgs &amp;inArgs, const OutArgs &amp;outArgs) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Np</name>
      <anchorfile>classPiro_1_1Epetra_1_1RythmosSolver.html</anchorfile>
      <anchor>a8caae71adf201e58802a3ce80296f8df</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Ng</name>
      <anchorfile>classPiro_1_1Epetra_1_1RythmosSolver.html</anchorfile>
      <anchor>abbaeddc74a17f90a271c7a90890fdb3d</anchor>
      <arglist>() const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Piro::RythmosStepControlFactory</name>
    <filename>classPiro_1_1RythmosStepControlFactory.html</filename>
    <templarg></templarg>
  </compound>
  <compound kind="class">
    <name>Piro::RythmosStepperFactory</name>
    <filename>classPiro_1_1RythmosStepperFactory.html</filename>
    <templarg></templarg>
  </compound>
  <compound kind="class">
    <name>Piro::Epetra::SensitivityOperator</name>
    <filename>classPiro_1_1Epetra_1_1SensitivityOperator.html</filename>
    <member kind="function">
      <type></type>
      <name>SensitivityOperator</name>
      <anchorfile>classPiro_1_1Epetra_1_1SensitivityOperator.html</anchorfile>
      <anchor>a1d234a3688b009a71ee5a3d9bd50bee1</anchor>
      <arglist>(const Teuchos::RCP&lt; const Epetra_Map &gt; &amp;g_map, const Teuchos::RCP&lt; const Epetra_Map &gt; &amp;p_map)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>SetUseTranspose</name>
      <anchorfile>classPiro_1_1Epetra_1_1SensitivityOperator.html</anchorfile>
      <anchor>a1319b29446d886cd026f2288f7978c6e</anchor>
      <arglist>(bool UseTranspose)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>Apply</name>
      <anchorfile>classPiro_1_1Epetra_1_1SensitivityOperator.html</anchorfile>
      <anchor>a12b7de30cf5198c36206ddfec8ff793c</anchor>
      <arglist>(const Epetra_MultiVector &amp;Input, Epetra_MultiVector &amp;Result) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>ApplyInverse</name>
      <anchorfile>classPiro_1_1Epetra_1_1SensitivityOperator.html</anchorfile>
      <anchor>a1530f5032bcbbfc2a61de38b64e7aeab</anchor>
      <arglist>(const Epetra_MultiVector &amp;X, Epetra_MultiVector &amp;Y) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual double</type>
      <name>NormInf</name>
      <anchorfile>classPiro_1_1Epetra_1_1SensitivityOperator.html</anchorfile>
      <anchor>aaec39dec134bc63f4624e831556fc5f0</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const char *</type>
      <name>Label</name>
      <anchorfile>classPiro_1_1Epetra_1_1SensitivityOperator.html</anchorfile>
      <anchor>a21218ad2ebb5a31f7bcf96d1581a4b3d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>UseTranspose</name>
      <anchorfile>classPiro_1_1Epetra_1_1SensitivityOperator.html</anchorfile>
      <anchor>a1ba92b81c049fb6a13849c4dc005e827</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>HasNormInf</name>
      <anchorfile>classPiro_1_1Epetra_1_1SensitivityOperator.html</anchorfile>
      <anchor>a4f087621a77b080e9f9dbffad8ff4ce8</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const Epetra_Comm &amp;</type>
      <name>Comm</name>
      <anchorfile>classPiro_1_1Epetra_1_1SensitivityOperator.html</anchorfile>
      <anchor>af8319129e92bbce1e3491e5cd50a1155</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const Epetra_Map &amp;</type>
      <name>OperatorDomainMap</name>
      <anchorfile>classPiro_1_1Epetra_1_1SensitivityOperator.html</anchorfile>
      <anchor>a00055538dd9321915f811159968e0a8f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const Epetra_Map &amp;</type>
      <name>OperatorRangeMap</name>
      <anchorfile>classPiro_1_1Epetra_1_1SensitivityOperator.html</anchorfile>
      <anchor>a6fa35e44b2807c4971077abd7d12e3fa</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SensitivityOperator</name>
      <anchorfile>classPiro_1_1Epetra_1_1SensitivityOperator.html</anchorfile>
      <anchor>a1d234a3688b009a71ee5a3d9bd50bee1</anchor>
      <arglist>(const Teuchos::RCP&lt; const Epetra_Map &gt; &amp;g_map, const Teuchos::RCP&lt; const Epetra_Map &gt; &amp;p_map)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>SetUseTranspose</name>
      <anchorfile>classPiro_1_1Epetra_1_1SensitivityOperator.html</anchorfile>
      <anchor>a1319b29446d886cd026f2288f7978c6e</anchor>
      <arglist>(bool UseTranspose)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>Apply</name>
      <anchorfile>classPiro_1_1Epetra_1_1SensitivityOperator.html</anchorfile>
      <anchor>a12b7de30cf5198c36206ddfec8ff793c</anchor>
      <arglist>(const Epetra_MultiVector &amp;Input, Epetra_MultiVector &amp;Result) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>ApplyInverse</name>
      <anchorfile>classPiro_1_1Epetra_1_1SensitivityOperator.html</anchorfile>
      <anchor>a1530f5032bcbbfc2a61de38b64e7aeab</anchor>
      <arglist>(const Epetra_MultiVector &amp;X, Epetra_MultiVector &amp;Y) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual double</type>
      <name>NormInf</name>
      <anchorfile>classPiro_1_1Epetra_1_1SensitivityOperator.html</anchorfile>
      <anchor>aaec39dec134bc63f4624e831556fc5f0</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const char *</type>
      <name>Label</name>
      <anchorfile>classPiro_1_1Epetra_1_1SensitivityOperator.html</anchorfile>
      <anchor>a21218ad2ebb5a31f7bcf96d1581a4b3d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>UseTranspose</name>
      <anchorfile>classPiro_1_1Epetra_1_1SensitivityOperator.html</anchorfile>
      <anchor>a1ba92b81c049fb6a13849c4dc005e827</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>HasNormInf</name>
      <anchorfile>classPiro_1_1Epetra_1_1SensitivityOperator.html</anchorfile>
      <anchor>a4f087621a77b080e9f9dbffad8ff4ce8</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const Epetra_Comm &amp;</type>
      <name>Comm</name>
      <anchorfile>classPiro_1_1Epetra_1_1SensitivityOperator.html</anchorfile>
      <anchor>af8319129e92bbce1e3491e5cd50a1155</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const Epetra_Map &amp;</type>
      <name>OperatorDomainMap</name>
      <anchorfile>classPiro_1_1Epetra_1_1SensitivityOperator.html</anchorfile>
      <anchor>a00055538dd9321915f811159968e0a8f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const Epetra_Map &amp;</type>
      <name>OperatorRangeMap</name>
      <anchorfile>classPiro_1_1Epetra_1_1SensitivityOperator.html</anchorfile>
      <anchor>a6fa35e44b2807c4971077abd7d12e3fa</anchor>
      <arglist>() const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Piro::SolutionObserverBase</name>
    <filename>classPiro_1_1SolutionObserverBase.html</filename>
    <templarg></templarg>
    <templarg></templarg>
  </compound>
  <compound kind="class">
    <name>Piro::SolverFactory</name>
    <filename>classPiro_1_1SolverFactory.html</filename>
    <member kind="function">
      <type>Teuchos::RCP&lt; Thyra::ResponseOnlyModelEvaluatorBase&lt; Scalar &gt; &gt;</type>
      <name>createSolver</name>
      <anchorfile>classPiro_1_1SolverFactory.html</anchorfile>
      <anchor>a2eac6651427f83b35420d3c20fe18fe8</anchor>
      <arglist>(const Teuchos::RCP&lt; Teuchos::ParameterList &gt; &amp;piroParams, const Teuchos::RCP&lt; Thyra::ModelEvaluator&lt; Scalar &gt; &gt; &amp;model, const Teuchos::RCP&lt; Thyra::AdaptiveSolutionManager &gt; &amp;solMgr, const Teuchos::RCP&lt; Piro::ObserverBase&lt; Scalar &gt; &gt; &amp;observer=Teuchos::null)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Piro::Epetra::SolverFactory</name>
    <filename>classPiro_1_1Epetra_1_1SolverFactory.html</filename>
    <member kind="function">
      <type>Teuchos::RCP&lt; EpetraExt::ModelEvaluator &gt;</type>
      <name>createSolver</name>
      <anchorfile>classPiro_1_1Epetra_1_1SolverFactory.html</anchorfile>
      <anchor>a84981c0374407fbbbc355bef2fff159c</anchor>
      <arglist>(const Teuchos::RCP&lt; Teuchos::ParameterList &gt; &amp;piroParams, const Teuchos::RCP&lt; EpetraExt::ModelEvaluator &gt; &amp;model)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setSource</name>
      <anchorfile>classPiro_1_1Epetra_1_1SolverFactory.html</anchorfile>
      <anchor>a3ecc543bad688839a8820997e2563304</anchor>
      <arglist>(const Provider&lt; T &gt; &amp;p)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Piro::SteadyStateSolver</name>
    <filename>classPiro_1_1SteadyStateSolver.html</filename>
    <templarg></templarg>
    <member kind="function">
      <type></type>
      <name>SteadyStateSolver</name>
      <anchorfile>classPiro_1_1SteadyStateSolver.html</anchorfile>
      <anchor>a7b1481c9517ce150e3384b1dbeb517a2</anchor>
      <arglist>(const Teuchos::RCP&lt; const Thyra::ModelEvaluator&lt; Scalar &gt; &gt; &amp;model)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SteadyStateSolver</name>
      <anchorfile>classPiro_1_1SteadyStateSolver.html</anchorfile>
      <anchor>a1e55326f5ed88d21d3b6fed5b0ba2d2d</anchor>
      <arglist>(const Teuchos::RCP&lt; const Thyra::ModelEvaluator&lt; Scalar &gt; &gt; &amp;model, int numParameters)</arglist>
    </member>
    <member kind="function">
      <type>Thyra::ModelEvaluatorBase::InArgs&lt; Scalar &gt;</type>
      <name>createInArgs</name>
      <anchorfile>classPiro_1_1SteadyStateSolver.html</anchorfile>
      <anchor>acc50942872b694e0f9eee9f6b9753c80</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Thyra::VectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>get_p_space</name>
      <anchorfile>classPiro_1_1SteadyStateSolver.html</anchorfile>
      <anchor>aada71f879b04f8d050d7c9a2d9206c54</anchor>
      <arglist>(int l) const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Thyra::VectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>get_g_space</name>
      <anchorfile>classPiro_1_1SteadyStateSolver.html</anchorfile>
      <anchor>abba76620be5f92a1b5fd7e9745fafce9</anchor>
      <arglist>(int j) const </arglist>
    </member>
    <member kind="function">
      <type>Thyra::ModelEvaluatorBase::InArgs&lt; Scalar &gt;</type>
      <name>getNominalValues</name>
      <anchorfile>classPiro_1_1SteadyStateSolver.html</anchorfile>
      <anchor>afd8b67db6567222c07ae6c9ec8e396a3</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>const Thyra::ModelEvaluator&lt; Scalar &gt; &amp;</type>
      <name>getModel</name>
      <anchorfile>classPiro_1_1SteadyStateSolver.html</anchorfile>
      <anchor>a5f6748ddc5e7e7971d15f8303627364d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>int</type>
      <name>num_p</name>
      <anchorfile>classPiro_1_1SteadyStateSolver.html</anchorfile>
      <anchor>a2758ad5957cb9d4fa9bbec3cb87aa5d0</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>int</type>
      <name>num_g</name>
      <anchorfile>classPiro_1_1SteadyStateSolver.html</anchorfile>
      <anchor>a47e3bab313b1a62bb3252ca2db5555f7</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>evalConvergedModel</name>
      <anchorfile>classPiro_1_1SteadyStateSolver.html</anchorfile>
      <anchor>a4d45af53efee8e96b2d2aa7e9fbfd23b</anchor>
      <arglist>(const Thyra::ModelEvaluatorBase::InArgs&lt; Scalar &gt; &amp;modelInArgs, const Thyra::ModelEvaluatorBase::OutArgs&lt; Scalar &gt; &amp;outArgs) const </arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SteadyStateSolver</name>
      <anchorfile>classPiro_1_1SteadyStateSolver.html</anchorfile>
      <anchor>a7b1481c9517ce150e3384b1dbeb517a2</anchor>
      <arglist>(const Teuchos::RCP&lt; const Thyra::ModelEvaluator&lt; Scalar &gt; &gt; &amp;model)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SteadyStateSolver</name>
      <anchorfile>classPiro_1_1SteadyStateSolver.html</anchorfile>
      <anchor>a1e55326f5ed88d21d3b6fed5b0ba2d2d</anchor>
      <arglist>(const Teuchos::RCP&lt; const Thyra::ModelEvaluator&lt; Scalar &gt; &gt; &amp;model, int numParameters)</arglist>
    </member>
    <member kind="function">
      <type>Thyra::ModelEvaluatorBase::InArgs&lt; Scalar &gt;</type>
      <name>createInArgs</name>
      <anchorfile>classPiro_1_1SteadyStateSolver.html</anchorfile>
      <anchor>acc50942872b694e0f9eee9f6b9753c80</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Thyra::VectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>get_p_space</name>
      <anchorfile>classPiro_1_1SteadyStateSolver.html</anchorfile>
      <anchor>aada71f879b04f8d050d7c9a2d9206c54</anchor>
      <arglist>(int l) const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Thyra::VectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>get_g_space</name>
      <anchorfile>classPiro_1_1SteadyStateSolver.html</anchorfile>
      <anchor>abba76620be5f92a1b5fd7e9745fafce9</anchor>
      <arglist>(int j) const </arglist>
    </member>
    <member kind="function">
      <type>Thyra::ModelEvaluatorBase::InArgs&lt; Scalar &gt;</type>
      <name>getNominalValues</name>
      <anchorfile>classPiro_1_1SteadyStateSolver.html</anchorfile>
      <anchor>afd8b67db6567222c07ae6c9ec8e396a3</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>const Thyra::ModelEvaluator&lt; Scalar &gt; &amp;</type>
      <name>getModel</name>
      <anchorfile>classPiro_1_1SteadyStateSolver.html</anchorfile>
      <anchor>a5f6748ddc5e7e7971d15f8303627364d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>int</type>
      <name>num_p</name>
      <anchorfile>classPiro_1_1SteadyStateSolver.html</anchorfile>
      <anchor>a2758ad5957cb9d4fa9bbec3cb87aa5d0</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>int</type>
      <name>num_g</name>
      <anchorfile>classPiro_1_1SteadyStateSolver.html</anchorfile>
      <anchor>a47e3bab313b1a62bb3252ca2db5555f7</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>evalConvergedModel</name>
      <anchorfile>classPiro_1_1SteadyStateSolver.html</anchorfile>
      <anchor>a4d45af53efee8e96b2d2aa7e9fbfd23b</anchor>
      <arglist>(const Thyra::ModelEvaluatorBase::InArgs&lt; Scalar &gt; &amp;modelInArgs, const Thyra::ModelEvaluatorBase::OutArgs&lt; Scalar &gt; &amp;outArgs) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Piro::Epetra::StokhosMPSolver</name>
    <filename>classPiro_1_1Epetra_1_1StokhosMPSolver.html</filename>
    <member kind="function">
      <type></type>
      <name>StokhosMPSolver</name>
      <anchorfile>classPiro_1_1Epetra_1_1StokhosMPSolver.html</anchorfile>
      <anchor>a562b8fbb80dc36c3315e2eac1d137068</anchor>
      <arglist>(const Teuchos::RCP&lt; Teuchos::ParameterList &gt; &amp;piroParams, const Teuchos::RCP&lt; Teuchos::ParameterList &gt; &amp;mpParams, const Teuchos::RCP&lt; const Epetra_Comm &gt; &amp;globalComm, int block_size, int num_spatial_procs)</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Epetra_Comm &gt;</type>
      <name>getSpatialComm</name>
      <anchorfile>classPiro_1_1Epetra_1_1StokhosMPSolver.html</anchorfile>
      <anchor>ae699513629667a0ec4a20765134e82d3</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Epetra_Comm &gt;</type>
      <name>getStochasticComm</name>
      <anchorfile>classPiro_1_1Epetra_1_1StokhosMPSolver.html</anchorfile>
      <anchor>a21accbcac36744987e37cc435b3f9e16</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const EpetraExt::MultiComm &gt;</type>
      <name>getGlobalMultiComm</name>
      <anchorfile>classPiro_1_1Epetra_1_1StokhosMPSolver.html</anchorfile>
      <anchor>a8a86054eaf31cc58224c758227f638e1</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setup</name>
      <anchorfile>classPiro_1_1Epetra_1_1StokhosMPSolver.html</anchorfile>
      <anchor>abf61e09853745c7eafeb74aad0ba61d4</anchor>
      <arglist>(const Teuchos::RCP&lt; EpetraExt::ModelEvaluator &gt; &amp;model, const Teuchos::RCP&lt; NOX::Epetra::Observer &gt; &amp;noxObserver=Teuchos::null)</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Epetra_Map &gt;</type>
      <name>get_p_map</name>
      <anchorfile>classPiro_1_1Epetra_1_1StokhosMPSolver.html</anchorfile>
      <anchor>ad18bb4c4a2c412b26dc9d460486dcd07</anchor>
      <arglist>(int l) const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Epetra_Map &gt;</type>
      <name>get_g_map</name>
      <anchorfile>classPiro_1_1Epetra_1_1StokhosMPSolver.html</anchorfile>
      <anchor>a10e1a92c69dee3a81d59ae3c012f458c</anchor>
      <arglist>(int j) const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Epetra_Vector &gt;</type>
      <name>get_p_init</name>
      <anchorfile>classPiro_1_1Epetra_1_1StokhosMPSolver.html</anchorfile>
      <anchor>ae1771df694cd4c8533a434599642e916</anchor>
      <arglist>(int l) const </arglist>
    </member>
    <member kind="function">
      <type>EpetraExt::ModelEvaluator::InArgs</type>
      <name>createInArgs</name>
      <anchorfile>classPiro_1_1Epetra_1_1StokhosMPSolver.html</anchorfile>
      <anchor>a7550a71a1220dcc3af185596ab01f111</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>EpetraExt::ModelEvaluator::OutArgs</type>
      <name>createOutArgs</name>
      <anchorfile>classPiro_1_1Epetra_1_1StokhosMPSolver.html</anchorfile>
      <anchor>a6ed5ff4f2dba60e6575c95e7454b50ca</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>evalModel</name>
      <anchorfile>classPiro_1_1Epetra_1_1StokhosMPSolver.html</anchorfile>
      <anchor>abd7fd5e0cc974e48826466b5c77bbe0c</anchor>
      <arglist>(const InArgs &amp;inArgs, const OutArgs &amp;outArgs) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_x_mp_init</name>
      <anchorfile>classPiro_1_1Epetra_1_1StokhosMPSolver.html</anchorfile>
      <anchor>a3a2173abf246ea2bc72439effe6c1350</anchor>
      <arglist>(const Stokhos::ProductEpetraVector &amp;x_mp_in)</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Stokhos::ProductEpetraVector &gt;</type>
      <name>get_x_mp_init</name>
      <anchorfile>classPiro_1_1Epetra_1_1StokhosMPSolver.html</anchorfile>
      <anchor>af6d13b563ccaa8c0420e57bdf33e6c79</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_p_mp_init</name>
      <anchorfile>classPiro_1_1Epetra_1_1StokhosMPSolver.html</anchorfile>
      <anchor>ae15aa526f97b66c23677eaf12444e0ad</anchor>
      <arglist>(int i, const Stokhos::ProductEpetraVector &amp;p_mp_in)</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Stokhos::ProductEpetraVector &gt;</type>
      <name>get_p_mp_init</name>
      <anchorfile>classPiro_1_1Epetra_1_1StokhosMPSolver.html</anchorfile>
      <anchor>a5cfa6605b3bb9766170a8341fd535646</anchor>
      <arglist>(int l) const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; Stokhos::ProductEpetraVector &gt;</type>
      <name>create_x_mp</name>
      <anchorfile>classPiro_1_1Epetra_1_1StokhosMPSolver.html</anchorfile>
      <anchor>a36b4b4f0fa2e799f68098304296d5a60</anchor>
      <arglist>(Epetra_DataAccess CV=Copy, const Epetra_Vector *v=NULL) const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; Stokhos::ProductEpetraVector &gt;</type>
      <name>create_p_mp</name>
      <anchorfile>classPiro_1_1Epetra_1_1StokhosMPSolver.html</anchorfile>
      <anchor>a62fac6615c0b2ddb68ac3a49c033b7b4</anchor>
      <arglist>(int l, Epetra_DataAccess CV=Copy, const Epetra_Vector *v=NULL) const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; Stokhos::ProductEpetraMultiVector &gt;</type>
      <name>create_p_mv_mp</name>
      <anchorfile>classPiro_1_1Epetra_1_1StokhosMPSolver.html</anchorfile>
      <anchor>a30b84e33c0350a370908ca6fdf5dc623</anchor>
      <arglist>(int l, int num_vecs, Epetra_DataAccess CV=Copy, const Epetra_MultiVector *v=NULL) const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; Stokhos::ProductEpetraVector &gt;</type>
      <name>create_g_mp</name>
      <anchorfile>classPiro_1_1Epetra_1_1StokhosMPSolver.html</anchorfile>
      <anchor>a6a02da75ed9fec071a075c5890165216</anchor>
      <arglist>(int l, Epetra_DataAccess CV=Copy, const Epetra_Vector *v=NULL) const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; Stokhos::ProductEpetraMultiVector &gt;</type>
      <name>create_g_mv_mp</name>
      <anchorfile>classPiro_1_1Epetra_1_1StokhosMPSolver.html</anchorfile>
      <anchor>ac784c9f2e24e4c64806a7f1058391614</anchor>
      <arglist>(int l, int num_vecs, Epetra_DataAccess CV=Copy, const Epetra_MultiVector *v=NULL) const </arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>StokhosMPSolver</name>
      <anchorfile>classPiro_1_1Epetra_1_1StokhosMPSolver.html</anchorfile>
      <anchor>a562b8fbb80dc36c3315e2eac1d137068</anchor>
      <arglist>(const Teuchos::RCP&lt; Teuchos::ParameterList &gt; &amp;piroParams, const Teuchos::RCP&lt; Teuchos::ParameterList &gt; &amp;mpParams, const Teuchos::RCP&lt; const Epetra_Comm &gt; &amp;globalComm, int block_size, int num_spatial_procs)</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Epetra_Comm &gt;</type>
      <name>getSpatialComm</name>
      <anchorfile>classPiro_1_1Epetra_1_1StokhosMPSolver.html</anchorfile>
      <anchor>ae699513629667a0ec4a20765134e82d3</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Epetra_Comm &gt;</type>
      <name>getStochasticComm</name>
      <anchorfile>classPiro_1_1Epetra_1_1StokhosMPSolver.html</anchorfile>
      <anchor>a21accbcac36744987e37cc435b3f9e16</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const EpetraExt::MultiComm &gt;</type>
      <name>getGlobalMultiComm</name>
      <anchorfile>classPiro_1_1Epetra_1_1StokhosMPSolver.html</anchorfile>
      <anchor>a8a86054eaf31cc58224c758227f638e1</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setup</name>
      <anchorfile>classPiro_1_1Epetra_1_1StokhosMPSolver.html</anchorfile>
      <anchor>abf61e09853745c7eafeb74aad0ba61d4</anchor>
      <arglist>(const Teuchos::RCP&lt; EpetraExt::ModelEvaluator &gt; &amp;model, const Teuchos::RCP&lt; NOX::Epetra::Observer &gt; &amp;noxObserver=Teuchos::null)</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Epetra_Map &gt;</type>
      <name>get_p_map</name>
      <anchorfile>classPiro_1_1Epetra_1_1StokhosMPSolver.html</anchorfile>
      <anchor>ad18bb4c4a2c412b26dc9d460486dcd07</anchor>
      <arglist>(int l) const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Epetra_Map &gt;</type>
      <name>get_g_map</name>
      <anchorfile>classPiro_1_1Epetra_1_1StokhosMPSolver.html</anchorfile>
      <anchor>a10e1a92c69dee3a81d59ae3c012f458c</anchor>
      <arglist>(int j) const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Epetra_Vector &gt;</type>
      <name>get_p_init</name>
      <anchorfile>classPiro_1_1Epetra_1_1StokhosMPSolver.html</anchorfile>
      <anchor>ae1771df694cd4c8533a434599642e916</anchor>
      <arglist>(int l) const </arglist>
    </member>
    <member kind="function">
      <type>EpetraExt::ModelEvaluator::InArgs</type>
      <name>createInArgs</name>
      <anchorfile>classPiro_1_1Epetra_1_1StokhosMPSolver.html</anchorfile>
      <anchor>a7550a71a1220dcc3af185596ab01f111</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>EpetraExt::ModelEvaluator::OutArgs</type>
      <name>createOutArgs</name>
      <anchorfile>classPiro_1_1Epetra_1_1StokhosMPSolver.html</anchorfile>
      <anchor>a6ed5ff4f2dba60e6575c95e7454b50ca</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>evalModel</name>
      <anchorfile>classPiro_1_1Epetra_1_1StokhosMPSolver.html</anchorfile>
      <anchor>abd7fd5e0cc974e48826466b5c77bbe0c</anchor>
      <arglist>(const InArgs &amp;inArgs, const OutArgs &amp;outArgs) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_x_mp_init</name>
      <anchorfile>classPiro_1_1Epetra_1_1StokhosMPSolver.html</anchorfile>
      <anchor>a3a2173abf246ea2bc72439effe6c1350</anchor>
      <arglist>(const Stokhos::ProductEpetraVector &amp;x_mp_in)</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Stokhos::ProductEpetraVector &gt;</type>
      <name>get_x_mp_init</name>
      <anchorfile>classPiro_1_1Epetra_1_1StokhosMPSolver.html</anchorfile>
      <anchor>af6d13b563ccaa8c0420e57bdf33e6c79</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_p_mp_init</name>
      <anchorfile>classPiro_1_1Epetra_1_1StokhosMPSolver.html</anchorfile>
      <anchor>ae15aa526f97b66c23677eaf12444e0ad</anchor>
      <arglist>(int i, const Stokhos::ProductEpetraVector &amp;p_mp_in)</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Stokhos::ProductEpetraVector &gt;</type>
      <name>get_p_mp_init</name>
      <anchorfile>classPiro_1_1Epetra_1_1StokhosMPSolver.html</anchorfile>
      <anchor>a5cfa6605b3bb9766170a8341fd535646</anchor>
      <arglist>(int l) const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; Stokhos::ProductEpetraVector &gt;</type>
      <name>create_x_mp</name>
      <anchorfile>classPiro_1_1Epetra_1_1StokhosMPSolver.html</anchorfile>
      <anchor>a36b4b4f0fa2e799f68098304296d5a60</anchor>
      <arglist>(Epetra_DataAccess CV=Copy, const Epetra_Vector *v=NULL) const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; Stokhos::ProductEpetraVector &gt;</type>
      <name>create_p_mp</name>
      <anchorfile>classPiro_1_1Epetra_1_1StokhosMPSolver.html</anchorfile>
      <anchor>a62fac6615c0b2ddb68ac3a49c033b7b4</anchor>
      <arglist>(int l, Epetra_DataAccess CV=Copy, const Epetra_Vector *v=NULL) const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; Stokhos::ProductEpetraMultiVector &gt;</type>
      <name>create_p_mv_mp</name>
      <anchorfile>classPiro_1_1Epetra_1_1StokhosMPSolver.html</anchorfile>
      <anchor>a30b84e33c0350a370908ca6fdf5dc623</anchor>
      <arglist>(int l, int num_vecs, Epetra_DataAccess CV=Copy, const Epetra_MultiVector *v=NULL) const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; Stokhos::ProductEpetraVector &gt;</type>
      <name>create_g_mp</name>
      <anchorfile>classPiro_1_1Epetra_1_1StokhosMPSolver.html</anchorfile>
      <anchor>a6a02da75ed9fec071a075c5890165216</anchor>
      <arglist>(int l, Epetra_DataAccess CV=Copy, const Epetra_Vector *v=NULL) const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; Stokhos::ProductEpetraMultiVector &gt;</type>
      <name>create_g_mv_mp</name>
      <anchorfile>classPiro_1_1Epetra_1_1StokhosMPSolver.html</anchorfile>
      <anchor>ac784c9f2e24e4c64806a7f1058391614</anchor>
      <arglist>(int l, int num_vecs, Epetra_DataAccess CV=Copy, const Epetra_MultiVector *v=NULL) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Piro::Epetra::StokhosNOXObserver</name>
    <filename>classPiro_1_1Epetra_1_1StokhosNOXObserver.html</filename>
  </compound>
  <compound kind="class">
    <name>Piro::Epetra::StokhosSolver</name>
    <filename>classPiro_1_1Epetra_1_1StokhosSolver.html</filename>
    <member kind="function">
      <type></type>
      <name>StokhosSolver</name>
      <anchorfile>classPiro_1_1Epetra_1_1StokhosSolver.html</anchorfile>
      <anchor>a350c90d272a7bc986b4702c33fb91a72</anchor>
      <arglist>(const Teuchos::RCP&lt; Teuchos::ParameterList &gt; &amp;piroParams, const Teuchos::RCP&lt; const Epetra_Comm &gt; &amp;globalComm)</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Epetra_Comm &gt;</type>
      <name>getSpatialComm</name>
      <anchorfile>classPiro_1_1Epetra_1_1StokhosSolver.html</anchorfile>
      <anchor>a8e115a000091d45a20702a6cf781f399</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Epetra_Comm &gt;</type>
      <name>getStochasticComm</name>
      <anchorfile>classPiro_1_1Epetra_1_1StokhosSolver.html</anchorfile>
      <anchor>a37873e243da90175ddfb4df1a6b73d28</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const EpetraExt::MultiComm &gt;</type>
      <name>getGlobalMultiComm</name>
      <anchorfile>classPiro_1_1Epetra_1_1StokhosSolver.html</anchorfile>
      <anchor>ae09aa696284cbdf4458340d72042ebab</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setup</name>
      <anchorfile>classPiro_1_1Epetra_1_1StokhosSolver.html</anchorfile>
      <anchor>a1520b11999f1e61fbdf52363b72f6db7</anchor>
      <arglist>(const Teuchos::RCP&lt; EpetraExt::ModelEvaluator &gt; &amp;model, const Teuchos::RCP&lt; NOX::Epetra::Observer &gt; &amp;noxObserver=Teuchos::null)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>resetSolverParameters</name>
      <anchorfile>classPiro_1_1Epetra_1_1StokhosSolver.html</anchorfile>
      <anchor>a2bcbef8e40e917a701ebb74519b55258</anchor>
      <arglist>(const Teuchos::ParameterList &amp;new_solver_params)</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Epetra_Map &gt;</type>
      <name>get_p_map</name>
      <anchorfile>classPiro_1_1Epetra_1_1StokhosSolver.html</anchorfile>
      <anchor>af00c9a7d3f7d79f567792c4b7418e639</anchor>
      <arglist>(int l) const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Epetra_Map &gt;</type>
      <name>get_g_map</name>
      <anchorfile>classPiro_1_1Epetra_1_1StokhosSolver.html</anchorfile>
      <anchor>a78ee4b940c91d95276f32a012f06c55b</anchor>
      <arglist>(int j) const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Epetra_Vector &gt;</type>
      <name>get_p_init</name>
      <anchorfile>classPiro_1_1Epetra_1_1StokhosSolver.html</anchorfile>
      <anchor>a8dfdf4a181cb337e3aa979d3dac5821f</anchor>
      <arglist>(int l) const </arglist>
    </member>
    <member kind="function">
      <type>EpetraExt::ModelEvaluator::InArgs</type>
      <name>createInArgs</name>
      <anchorfile>classPiro_1_1Epetra_1_1StokhosSolver.html</anchorfile>
      <anchor>a0a283e0f7f73ad8fadd3b9566f8a31a5</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>EpetraExt::ModelEvaluator::OutArgs</type>
      <name>createOutArgs</name>
      <anchorfile>classPiro_1_1Epetra_1_1StokhosSolver.html</anchorfile>
      <anchor>a818a3220347bac2b5d1530f7c19538da</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>evalModel</name>
      <anchorfile>classPiro_1_1Epetra_1_1StokhosSolver.html</anchorfile>
      <anchor>a6e6d5ed5ef780195e3a605de4a3a8b37</anchor>
      <arglist>(const InArgs &amp;inArgs, const OutArgs &amp;outArgs) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_x_sg_init</name>
      <anchorfile>classPiro_1_1Epetra_1_1StokhosSolver.html</anchorfile>
      <anchor>ad493f2ae9bba524e8edcb0bf3594d434</anchor>
      <arglist>(const Stokhos::EpetraVectorOrthogPoly &amp;x_sg_in)</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Stokhos::EpetraVectorOrthogPoly &gt;</type>
      <name>get_x_sg_init</name>
      <anchorfile>classPiro_1_1Epetra_1_1StokhosSolver.html</anchorfile>
      <anchor>af1cb65667e9efce181c669a4c1fb10e7</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_p_sg_init</name>
      <anchorfile>classPiro_1_1Epetra_1_1StokhosSolver.html</anchorfile>
      <anchor>afa873c5285399e549d589dccbbc1d370</anchor>
      <arglist>(int i, const Stokhos::EpetraVectorOrthogPoly &amp;p_sg_in)</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Stokhos::EpetraVectorOrthogPoly &gt;</type>
      <name>get_p_sg_init</name>
      <anchorfile>classPiro_1_1Epetra_1_1StokhosSolver.html</anchorfile>
      <anchor>a546ca585c244eca3d2def54c1f550d3e</anchor>
      <arglist>(int l) const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; Stokhos::EpetraVectorOrthogPoly &gt;</type>
      <name>create_x_sg</name>
      <anchorfile>classPiro_1_1Epetra_1_1StokhosSolver.html</anchorfile>
      <anchor>a044c422b4cbd0aee0c617b49520b0247</anchor>
      <arglist>(Epetra_DataAccess CV=Copy, const Epetra_Vector *v=NULL) const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; Stokhos::EpetraVectorOrthogPoly &gt;</type>
      <name>create_p_sg</name>
      <anchorfile>classPiro_1_1Epetra_1_1StokhosSolver.html</anchorfile>
      <anchor>a4e5a577cad188719797b2b69fd0403b8</anchor>
      <arglist>(int l, Epetra_DataAccess CV=Copy, const Epetra_Vector *v=NULL) const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; Stokhos::EpetraVectorOrthogPoly &gt;</type>
      <name>create_g_sg</name>
      <anchorfile>classPiro_1_1Epetra_1_1StokhosSolver.html</anchorfile>
      <anchor>a5a0e652bd49fa7a6232fa0f96111619f</anchor>
      <arglist>(int l, Epetra_DataAccess CV=Copy, const Epetra_Vector *v=NULL) const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; Stokhos::EpetraMultiVectorOrthogPoly &gt;</type>
      <name>create_g_mv_sg</name>
      <anchorfile>classPiro_1_1Epetra_1_1StokhosSolver.html</anchorfile>
      <anchor>a84176ea19dc451d51f1c4772dcff02c3</anchor>
      <arglist>(int l, int num_vecs, Epetra_DataAccess CV=Copy, const Epetra_MultiVector *v=NULL) const </arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>StokhosSolver</name>
      <anchorfile>classPiro_1_1Epetra_1_1StokhosSolver.html</anchorfile>
      <anchor>a350c90d272a7bc986b4702c33fb91a72</anchor>
      <arglist>(const Teuchos::RCP&lt; Teuchos::ParameterList &gt; &amp;piroParams, const Teuchos::RCP&lt; const Epetra_Comm &gt; &amp;globalComm)</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Epetra_Comm &gt;</type>
      <name>getSpatialComm</name>
      <anchorfile>classPiro_1_1Epetra_1_1StokhosSolver.html</anchorfile>
      <anchor>a8e115a000091d45a20702a6cf781f399</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Epetra_Comm &gt;</type>
      <name>getStochasticComm</name>
      <anchorfile>classPiro_1_1Epetra_1_1StokhosSolver.html</anchorfile>
      <anchor>a37873e243da90175ddfb4df1a6b73d28</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const EpetraExt::MultiComm &gt;</type>
      <name>getGlobalMultiComm</name>
      <anchorfile>classPiro_1_1Epetra_1_1StokhosSolver.html</anchorfile>
      <anchor>ae09aa696284cbdf4458340d72042ebab</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setup</name>
      <anchorfile>classPiro_1_1Epetra_1_1StokhosSolver.html</anchorfile>
      <anchor>a1520b11999f1e61fbdf52363b72f6db7</anchor>
      <arglist>(const Teuchos::RCP&lt; EpetraExt::ModelEvaluator &gt; &amp;model, const Teuchos::RCP&lt; NOX::Epetra::Observer &gt; &amp;noxObserver=Teuchos::null)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>resetSolverParameters</name>
      <anchorfile>classPiro_1_1Epetra_1_1StokhosSolver.html</anchorfile>
      <anchor>a2bcbef8e40e917a701ebb74519b55258</anchor>
      <arglist>(const Teuchos::ParameterList &amp;new_solver_params)</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Epetra_Map &gt;</type>
      <name>get_p_map</name>
      <anchorfile>classPiro_1_1Epetra_1_1StokhosSolver.html</anchorfile>
      <anchor>af00c9a7d3f7d79f567792c4b7418e639</anchor>
      <arglist>(int l) const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Epetra_Map &gt;</type>
      <name>get_g_map</name>
      <anchorfile>classPiro_1_1Epetra_1_1StokhosSolver.html</anchorfile>
      <anchor>a78ee4b940c91d95276f32a012f06c55b</anchor>
      <arglist>(int j) const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Epetra_Vector &gt;</type>
      <name>get_p_init</name>
      <anchorfile>classPiro_1_1Epetra_1_1StokhosSolver.html</anchorfile>
      <anchor>a8dfdf4a181cb337e3aa979d3dac5821f</anchor>
      <arglist>(int l) const </arglist>
    </member>
    <member kind="function">
      <type>EpetraExt::ModelEvaluator::InArgs</type>
      <name>createInArgs</name>
      <anchorfile>classPiro_1_1Epetra_1_1StokhosSolver.html</anchorfile>
      <anchor>a0a283e0f7f73ad8fadd3b9566f8a31a5</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>EpetraExt::ModelEvaluator::OutArgs</type>
      <name>createOutArgs</name>
      <anchorfile>classPiro_1_1Epetra_1_1StokhosSolver.html</anchorfile>
      <anchor>a818a3220347bac2b5d1530f7c19538da</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>evalModel</name>
      <anchorfile>classPiro_1_1Epetra_1_1StokhosSolver.html</anchorfile>
      <anchor>a6e6d5ed5ef780195e3a605de4a3a8b37</anchor>
      <arglist>(const InArgs &amp;inArgs, const OutArgs &amp;outArgs) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_x_sg_init</name>
      <anchorfile>classPiro_1_1Epetra_1_1StokhosSolver.html</anchorfile>
      <anchor>ad493f2ae9bba524e8edcb0bf3594d434</anchor>
      <arglist>(const Stokhos::EpetraVectorOrthogPoly &amp;x_sg_in)</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Stokhos::EpetraVectorOrthogPoly &gt;</type>
      <name>get_x_sg_init</name>
      <anchorfile>classPiro_1_1Epetra_1_1StokhosSolver.html</anchorfile>
      <anchor>af1cb65667e9efce181c669a4c1fb10e7</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_p_sg_init</name>
      <anchorfile>classPiro_1_1Epetra_1_1StokhosSolver.html</anchorfile>
      <anchor>afa873c5285399e549d589dccbbc1d370</anchor>
      <arglist>(int i, const Stokhos::EpetraVectorOrthogPoly &amp;p_sg_in)</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Stokhos::EpetraVectorOrthogPoly &gt;</type>
      <name>get_p_sg_init</name>
      <anchorfile>classPiro_1_1Epetra_1_1StokhosSolver.html</anchorfile>
      <anchor>a546ca585c244eca3d2def54c1f550d3e</anchor>
      <arglist>(int l) const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; Stokhos::EpetraVectorOrthogPoly &gt;</type>
      <name>create_x_sg</name>
      <anchorfile>classPiro_1_1Epetra_1_1StokhosSolver.html</anchorfile>
      <anchor>a044c422b4cbd0aee0c617b49520b0247</anchor>
      <arglist>(Epetra_DataAccess CV=Copy, const Epetra_Vector *v=NULL) const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; Stokhos::EpetraVectorOrthogPoly &gt;</type>
      <name>create_p_sg</name>
      <anchorfile>classPiro_1_1Epetra_1_1StokhosSolver.html</anchorfile>
      <anchor>a4e5a577cad188719797b2b69fd0403b8</anchor>
      <arglist>(int l, Epetra_DataAccess CV=Copy, const Epetra_Vector *v=NULL) const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; Stokhos::EpetraVectorOrthogPoly &gt;</type>
      <name>create_g_sg</name>
      <anchorfile>classPiro_1_1Epetra_1_1StokhosSolver.html</anchorfile>
      <anchor>a5a0e652bd49fa7a6232fa0f96111619f</anchor>
      <arglist>(int l, Epetra_DataAccess CV=Copy, const Epetra_Vector *v=NULL) const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; Stokhos::EpetraMultiVectorOrthogPoly &gt;</type>
      <name>create_g_mv_sg</name>
      <anchorfile>classPiro_1_1Epetra_1_1StokhosSolver.html</anchorfile>
      <anchor>a84176ea19dc451d51f1c4772dcff02c3</anchor>
      <arglist>(int l, int num_vecs, Epetra_DataAccess CV=Copy, const Epetra_MultiVector *v=NULL) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Piro::Epetra::StokhosSolverFactory</name>
    <filename>classPiro_1_1Epetra_1_1StokhosSolverFactory.html</filename>
    <member kind="enumeration">
      <type></type>
      <name>SG_METHOD</name>
      <anchorfile>classPiro_1_1Epetra_1_1StokhosSolverFactory.html</anchorfile>
      <anchor>af96324c34111a81b8f79a9c22299fdcc</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>StokhosSolverFactory</name>
      <anchorfile>classPiro_1_1Epetra_1_1StokhosSolverFactory.html</anchorfile>
      <anchor>a860888adbe17a79d316804eb9ede170a</anchor>
      <arglist>(const Teuchos::RCP&lt; Teuchos::ParameterList &gt; &amp;piroParams, const Teuchos::RCP&lt; const Epetra_Comm &gt; &amp;globalComm)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>resetSolverParameters</name>
      <anchorfile>classPiro_1_1Epetra_1_1StokhosSolverFactory.html</anchorfile>
      <anchor>a1894ce9818556548c5fd9cdcad56e006</anchor>
      <arglist>(const Teuchos::ParameterList &amp;new_solver_params)</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; Stokhos::SGModelEvaluator &gt;</type>
      <name>createSGModel</name>
      <anchorfile>classPiro_1_1Epetra_1_1StokhosSolverFactory.html</anchorfile>
      <anchor>aa8af36ae88ca5873a4c0ee6abfbde923</anchor>
      <arglist>(const Teuchos::RCP&lt; EpetraExt::ModelEvaluator &gt; &amp;model)</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; NOX::Epetra::Observer &gt;</type>
      <name>createSGObserver</name>
      <anchorfile>classPiro_1_1Epetra_1_1StokhosSolverFactory.html</anchorfile>
      <anchor>a32d683c2579e89f56dcd9dc854af7212</anchor>
      <arglist>(const Teuchos::RCP&lt; NOX::Epetra::Observer &gt; &amp;noxObserver)</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; EpetraExt::ModelEvaluator &gt;</type>
      <name>createSGSolver</name>
      <anchorfile>classPiro_1_1Epetra_1_1StokhosSolverFactory.html</anchorfile>
      <anchor>a550bd471619a70f5679dd9d891c0e90c</anchor>
      <arglist>(const Teuchos::RCP&lt; EpetraExt::ModelEvaluator &gt; &amp;sg_model, const Teuchos::RCP&lt; NOX::Epetra::Observer &gt; &amp;sg_observer=Teuchos::null)</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; Stokhos::SGInverseModelEvaluator &gt;</type>
      <name>createSGSolverAdapter</name>
      <anchorfile>classPiro_1_1Epetra_1_1StokhosSolverFactory.html</anchorfile>
      <anchor>a980ceb1a24b4de748a8609183a7be865</anchor>
      <arglist>(const Teuchos::RCP&lt; EpetraExt::ModelEvaluator &gt; &amp;sg_solver)</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; EpetraExt::ModelEvaluator &gt;</type>
      <name>createRSModel</name>
      <anchorfile>classPiro_1_1Epetra_1_1StokhosSolverFactory.html</anchorfile>
      <anchor>a2550536ee0326b6b557082cbe47c867d</anchor>
      <arglist>(const Teuchos::RCP&lt; EpetraExt::ModelEvaluator &gt; &amp;sg_model)</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Epetra_Comm &gt;</type>
      <name>getSpatialComm</name>
      <anchorfile>classPiro_1_1Epetra_1_1StokhosSolverFactory.html</anchorfile>
      <anchor>a2577073e305fb211fa39ffce2d247068</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Epetra_Comm &gt;</type>
      <name>getStochasticComm</name>
      <anchorfile>classPiro_1_1Epetra_1_1StokhosSolverFactory.html</anchorfile>
      <anchor>a71540c5615ce594b2fbcb8a6df939d8d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const EpetraExt::MultiComm &gt;</type>
      <name>getGlobalMultiComm</name>
      <anchorfile>classPiro_1_1Epetra_1_1StokhosSolverFactory.html</anchorfile>
      <anchor>a3cdf6c48779896b34fca04775bffa4ab</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Stokhos::OrthogPolyBasis&lt; int, double &gt; &gt;</type>
      <name>getBasis</name>
      <anchorfile>classPiro_1_1Epetra_1_1StokhosSolverFactory.html</anchorfile>
      <anchor>a999fca9e543892ca717a665e9a70f780</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Stokhos::Quadrature&lt; int, double &gt; &gt;</type>
      <name>getQuad</name>
      <anchorfile>classPiro_1_1Epetra_1_1StokhosSolverFactory.html</anchorfile>
      <anchor>a8b145714f9a71bfee2a81462f05a6b5b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>SG_METHOD</type>
      <name>getSGMethod</name>
      <anchorfile>classPiro_1_1Epetra_1_1StokhosSolverFactory.html</anchorfile>
      <anchor>af3e87a3e40609ddf7a5c7fff449d00e6</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; Stokhos::SGModelEvaluator &gt;</type>
      <name>createSGModel</name>
      <anchorfile>classPiro_1_1Epetra_1_1StokhosSolverFactory.html</anchorfile>
      <anchor>aa8af36ae88ca5873a4c0ee6abfbde923</anchor>
      <arglist>(const Teuchos::RCP&lt; EpetraExt::ModelEvaluator &gt; &amp;model)</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; NOX::Epetra::Observer &gt;</type>
      <name>createSGObserver</name>
      <anchorfile>classPiro_1_1Epetra_1_1StokhosSolverFactory.html</anchorfile>
      <anchor>a32d683c2579e89f56dcd9dc854af7212</anchor>
      <arglist>(const Teuchos::RCP&lt; NOX::Epetra::Observer &gt; &amp;noxObserver)</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; EpetraExt::ModelEvaluator &gt;</type>
      <name>createSGSolver</name>
      <anchorfile>classPiro_1_1Epetra_1_1StokhosSolverFactory.html</anchorfile>
      <anchor>a550bd471619a70f5679dd9d891c0e90c</anchor>
      <arglist>(const Teuchos::RCP&lt; EpetraExt::ModelEvaluator &gt; &amp;sg_model, const Teuchos::RCP&lt; NOX::Epetra::Observer &gt; &amp;sg_observer=Teuchos::null)</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; Stokhos::SGInverseModelEvaluator &gt;</type>
      <name>createSGSolverAdapter</name>
      <anchorfile>classPiro_1_1Epetra_1_1StokhosSolverFactory.html</anchorfile>
      <anchor>a980ceb1a24b4de748a8609183a7be865</anchor>
      <arglist>(const Teuchos::RCP&lt; EpetraExt::ModelEvaluator &gt; &amp;sg_solver)</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; EpetraExt::ModelEvaluator &gt;</type>
      <name>createRSModel</name>
      <anchorfile>classPiro_1_1Epetra_1_1StokhosSolverFactory.html</anchorfile>
      <anchor>a2550536ee0326b6b557082cbe47c867d</anchor>
      <arglist>(const Teuchos::RCP&lt; EpetraExt::ModelEvaluator &gt; &amp;sg_model)</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Epetra_Comm &gt;</type>
      <name>getSpatialComm</name>
      <anchorfile>classPiro_1_1Epetra_1_1StokhosSolverFactory.html</anchorfile>
      <anchor>a2577073e305fb211fa39ffce2d247068</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Epetra_Comm &gt;</type>
      <name>getStochasticComm</name>
      <anchorfile>classPiro_1_1Epetra_1_1StokhosSolverFactory.html</anchorfile>
      <anchor>a71540c5615ce594b2fbcb8a6df939d8d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const EpetraExt::MultiComm &gt;</type>
      <name>getGlobalMultiComm</name>
      <anchorfile>classPiro_1_1Epetra_1_1StokhosSolverFactory.html</anchorfile>
      <anchor>a3cdf6c48779896b34fca04775bffa4ab</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Stokhos::OrthogPolyBasis&lt; int, double &gt; &gt;</type>
      <name>getBasis</name>
      <anchorfile>classPiro_1_1Epetra_1_1StokhosSolverFactory.html</anchorfile>
      <anchor>a999fca9e543892ca717a665e9a70f780</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Stokhos::Quadrature&lt; int, double &gt; &gt;</type>
      <name>getQuad</name>
      <anchorfile>classPiro_1_1Epetra_1_1StokhosSolverFactory.html</anchorfile>
      <anchor>a8b145714f9a71bfee2a81462f05a6b5b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>SG_METHOD</type>
      <name>getSGMethod</name>
      <anchorfile>classPiro_1_1Epetra_1_1StokhosSolverFactory.html</anchorfile>
      <anchor>af3e87a3e40609ddf7a5c7fff449d00e6</anchor>
      <arglist>() const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Piro::TransientDecorator</name>
    <filename>classPiro_1_1TransientDecorator.html</filename>
    <templarg></templarg>
    <templarg></templarg>
    <templarg></templarg>
    <templarg></templarg>
    <member kind="function">
      <type>void</type>
      <name>set_DgDx_dotdot</name>
      <anchorfile>classPiro_1_1TransientDecorator.html</anchorfile>
      <anchor>ac8f282764910070280b9a68ebbf3f35a</anchor>
      <arglist>(int j, const Thyra::ModelEvaluatorBase::Derivative&lt; Scalar &gt; &amp;DgDx_dotdot_j)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Piro::Epetra::TrapezoidDecorator</name>
    <filename>classPiro_1_1Epetra_1_1TrapezoidDecorator.html</filename>
    <member kind="function">
      <type></type>
      <name>TrapezoidDecorator</name>
      <anchorfile>classPiro_1_1Epetra_1_1TrapezoidDecorator.html</anchorfile>
      <anchor>a1abdb25041873a0318999dae1da4ddb2</anchor>
      <arglist>(Teuchos::RCP&lt; EpetraExt::ModelEvaluator &gt; &amp;model)</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Epetra_Vector &gt;</type>
      <name>get_p_init</name>
      <anchorfile>classPiro_1_1Epetra_1_1TrapezoidDecorator.html</anchorfile>
      <anchor>a73da7b81ed129e8826920045eff48ca0</anchor>
      <arglist>(int l) const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; Epetra_Operator &gt;</type>
      <name>create_W</name>
      <anchorfile>classPiro_1_1Epetra_1_1TrapezoidDecorator.html</anchorfile>
      <anchor>a8ce54ad564ff8ad68ee915afb0a3e09c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>EpetraExt::ModelEvaluator::InArgs</type>
      <name>createInArgs</name>
      <anchorfile>classPiro_1_1Epetra_1_1TrapezoidDecorator.html</anchorfile>
      <anchor>acb23473e8852538f2bcf255724c3ce9b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>EpetraExt::ModelEvaluator::OutArgs</type>
      <name>createOutArgs</name>
      <anchorfile>classPiro_1_1Epetra_1_1TrapezoidDecorator.html</anchorfile>
      <anchor>a7be0dde3f7a0595f6a4bdf3ae82f69bb</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>evalModel</name>
      <anchorfile>classPiro_1_1Epetra_1_1TrapezoidDecorator.html</anchorfile>
      <anchor>ad18463b22a48292a95d0848d154a494d</anchor>
      <arglist>(const InArgs &amp;inArgs, const OutArgs &amp;outArgs) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>injectData</name>
      <anchorfile>classPiro_1_1Epetra_1_1TrapezoidDecorator.html</anchorfile>
      <anchor>a4aae0cadd0937a15c329f842b5e40f73</anchor>
      <arglist>(const Teuchos::RCP&lt; Epetra_Vector &gt; &amp;x_, const Teuchos::RCP&lt; Epetra_Vector &gt; &amp;x_pred_a_, double fdt2_, const Teuchos::RCP&lt; Epetra_Vector &gt; &amp;x_pred_v_, double tdt_, double time_)</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Epetra_Map &gt;</type>
      <name>get_x_map</name>
      <anchorfile>classPiro_1_1Epetra_1_1TrapezoidDecorator.html</anchorfile>
      <anchor>a73ba98ce086214e558eb1b3837d4a462</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Epetra_Map &gt;</type>
      <name>get_f_map</name>
      <anchorfile>classPiro_1_1Epetra_1_1TrapezoidDecorator.html</anchorfile>
      <anchor>ae69f272b0f50ddfe05f089b5c9d2de79</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Epetra_Vector &gt;</type>
      <name>get_x_init</name>
      <anchorfile>classPiro_1_1Epetra_1_1TrapezoidDecorator.html</anchorfile>
      <anchor>a93d6ec555cbd629978c1aa294c146c01</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Epetra_Vector &gt;</type>
      <name>get_x_dot_init</name>
      <anchorfile>classPiro_1_1Epetra_1_1TrapezoidDecorator.html</anchorfile>
      <anchor>a5ece890061bde2e3ea7ff7401645abdf</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Epetra_Vector &gt;</type>
      <name>get_x_dotdot_init</name>
      <anchorfile>classPiro_1_1Epetra_1_1TrapezoidDecorator.html</anchorfile>
      <anchor>ae29d15642674d8d4635023f6d5ea3df3</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Epetra_Map &gt;</type>
      <name>get_p_map</name>
      <anchorfile>classPiro_1_1Epetra_1_1TrapezoidDecorator.html</anchorfile>
      <anchor>a301e76617e03278a79e4cc38b2009ecc</anchor>
      <arglist>(int l) const </arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>TrapezoidDecorator</name>
      <anchorfile>classPiro_1_1Epetra_1_1TrapezoidDecorator.html</anchorfile>
      <anchor>a1abdb25041873a0318999dae1da4ddb2</anchor>
      <arglist>(Teuchos::RCP&lt; EpetraExt::ModelEvaluator &gt; &amp;model)</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Epetra_Vector &gt;</type>
      <name>get_p_init</name>
      <anchorfile>classPiro_1_1Epetra_1_1TrapezoidDecorator.html</anchorfile>
      <anchor>a73da7b81ed129e8826920045eff48ca0</anchor>
      <arglist>(int l) const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; Epetra_Operator &gt;</type>
      <name>create_W</name>
      <anchorfile>classPiro_1_1Epetra_1_1TrapezoidDecorator.html</anchorfile>
      <anchor>a8ce54ad564ff8ad68ee915afb0a3e09c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>EpetraExt::ModelEvaluator::InArgs</type>
      <name>createInArgs</name>
      <anchorfile>classPiro_1_1Epetra_1_1TrapezoidDecorator.html</anchorfile>
      <anchor>acb23473e8852538f2bcf255724c3ce9b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>EpetraExt::ModelEvaluator::OutArgs</type>
      <name>createOutArgs</name>
      <anchorfile>classPiro_1_1Epetra_1_1TrapezoidDecorator.html</anchorfile>
      <anchor>a7be0dde3f7a0595f6a4bdf3ae82f69bb</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>evalModel</name>
      <anchorfile>classPiro_1_1Epetra_1_1TrapezoidDecorator.html</anchorfile>
      <anchor>ad18463b22a48292a95d0848d154a494d</anchor>
      <arglist>(const InArgs &amp;inArgs, const OutArgs &amp;outArgs) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>injectData</name>
      <anchorfile>classPiro_1_1Epetra_1_1TrapezoidDecorator.html</anchorfile>
      <anchor>a4aae0cadd0937a15c329f842b5e40f73</anchor>
      <arglist>(const Teuchos::RCP&lt; Epetra_Vector &gt; &amp;x_, const Teuchos::RCP&lt; Epetra_Vector &gt; &amp;x_pred_a_, double fdt2_, const Teuchos::RCP&lt; Epetra_Vector &gt; &amp;x_pred_v_, double tdt_, double time_)</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Epetra_Map &gt;</type>
      <name>get_x_map</name>
      <anchorfile>classPiro_1_1Epetra_1_1TrapezoidDecorator.html</anchorfile>
      <anchor>a73ba98ce086214e558eb1b3837d4a462</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Epetra_Map &gt;</type>
      <name>get_f_map</name>
      <anchorfile>classPiro_1_1Epetra_1_1TrapezoidDecorator.html</anchorfile>
      <anchor>ae69f272b0f50ddfe05f089b5c9d2de79</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Epetra_Vector &gt;</type>
      <name>get_x_init</name>
      <anchorfile>classPiro_1_1Epetra_1_1TrapezoidDecorator.html</anchorfile>
      <anchor>a93d6ec555cbd629978c1aa294c146c01</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Epetra_Vector &gt;</type>
      <name>get_x_dot_init</name>
      <anchorfile>classPiro_1_1Epetra_1_1TrapezoidDecorator.html</anchorfile>
      <anchor>a5ece890061bde2e3ea7ff7401645abdf</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Epetra_Vector &gt;</type>
      <name>get_x_dotdot_init</name>
      <anchorfile>classPiro_1_1Epetra_1_1TrapezoidDecorator.html</anchorfile>
      <anchor>ae29d15642674d8d4635023f6d5ea3df3</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Epetra_Map &gt;</type>
      <name>get_p_map</name>
      <anchorfile>classPiro_1_1Epetra_1_1TrapezoidDecorator.html</anchorfile>
      <anchor>a301e76617e03278a79e4cc38b2009ecc</anchor>
      <arglist>(int l) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Piro::TrapezoidDecorator</name>
    <filename>classPiro_1_1TrapezoidDecorator.html</filename>
    <templarg></templarg>
    <templarg></templarg>
    <templarg></templarg>
    <templarg></templarg>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Thyra::VectorBase&lt; Scalar &gt; &gt;</type>
      <name>get_x</name>
      <anchorfile>classPiro_1_1TrapezoidDecorator.html</anchorfile>
      <anchor>a0413721a661f6eb809878b8fc2a5b23f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Thyra::VectorBase&lt; Scalar &gt; &gt;</type>
      <name>get_x_dot</name>
      <anchorfile>classPiro_1_1TrapezoidDecorator.html</anchorfile>
      <anchor>a88e82235f3a4b0954499ed8ac4473107</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Thyra::VectorBase&lt; Scalar &gt; &gt;</type>
      <name>get_x_dotdot</name>
      <anchorfile>classPiro_1_1TrapezoidDecorator.html</anchorfile>
      <anchor>a7c94e3b6ddd3c89db8fe9c0543d837ea</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>injectData</name>
      <anchorfile>classPiro_1_1TrapezoidDecorator.html</anchorfile>
      <anchor>ab744aec4c55a1bcdc349af0cee592e6d</anchor>
      <arglist>(const Teuchos::RCP&lt; Thyra::VectorBase&lt; Scalar &gt; &gt; &amp;x_, const Teuchos::RCP&lt; Thyra::VectorBase&lt; Scalar &gt; &gt; &amp;x_pred_a_, Scalar fdt2_, const Teuchos::RCP&lt; Thyra::VectorBase&lt; Scalar &gt; &gt; &amp;x_pred_v_, Scalar tdt_, Scalar time_)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>evalModelImpl</name>
      <anchorfile>classPiro_1_1TrapezoidDecorator.html</anchorfile>
      <anchor>ae23ff3f7e59b782bf611c11ddd0cfdef</anchor>
      <arglist>(const Thyra::ModelEvaluatorBase::InArgs&lt; Scalar &gt; &amp;inArgs, const Thyra::ModelEvaluatorBase::OutArgs&lt; Scalar &gt; &amp;outArgs) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Piro::Epetra::TrapezoidRuleSolver</name>
    <filename>classPiro_1_1Epetra_1_1TrapezoidRuleSolver.html</filename>
    <member kind="function">
      <type></type>
      <name>TrapezoidRuleSolver</name>
      <anchorfile>classPiro_1_1Epetra_1_1TrapezoidRuleSolver.html</anchorfile>
      <anchor>a4bbe1360106e2b174576f033de58fef2</anchor>
      <arglist>(Teuchos::RCP&lt; Teuchos::ParameterList &gt; appParams, Teuchos::RCP&lt; EpetraExt::ModelEvaluator &gt; model, Teuchos::RCP&lt; NOX::Epetra::Observer &gt; observer=Teuchos::null)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>TrapezoidRuleSolver</name>
      <anchorfile>classPiro_1_1Epetra_1_1TrapezoidRuleSolver.html</anchorfile>
      <anchor>a4bbe1360106e2b174576f033de58fef2</anchor>
      <arglist>(Teuchos::RCP&lt; Teuchos::ParameterList &gt; appParams, Teuchos::RCP&lt; EpetraExt::ModelEvaluator &gt; model, Teuchos::RCP&lt; NOX::Epetra::Observer &gt; observer=Teuchos::null)</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Epetra_Vector &gt;</type>
      <name>get_p_init</name>
      <anchorfile>classPiro_1_1Epetra_1_1TrapezoidRuleSolver.html</anchorfile>
      <anchor>a49f342a7bd4414326f62ae8efcdd5f8a</anchor>
      <arglist>(int l) const </arglist>
    </member>
    <member kind="function">
      <type>EpetraExt::ModelEvaluator::InArgs</type>
      <name>createInArgs</name>
      <anchorfile>classPiro_1_1Epetra_1_1TrapezoidRuleSolver.html</anchorfile>
      <anchor>a32014b3b04d1485f75e73992d7a3f964</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>EpetraExt::ModelEvaluator::OutArgs</type>
      <name>createOutArgs</name>
      <anchorfile>classPiro_1_1Epetra_1_1TrapezoidRuleSolver.html</anchorfile>
      <anchor>a0e711bc3809b3f9a19789ba2f9823bac</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>evalModel</name>
      <anchorfile>classPiro_1_1Epetra_1_1TrapezoidRuleSolver.html</anchorfile>
      <anchor>a1e3ac6d3d95a82982146f47581d66ea8</anchor>
      <arglist>(const InArgs &amp;inArgs, const OutArgs &amp;outArgs) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Piro::TrapezoidRuleSolver</name>
    <filename>classPiro_1_1TrapezoidRuleSolver.html</filename>
    <templarg></templarg>
    <templarg></templarg>
    <templarg></templarg>
    <templarg></templarg>
    <member kind="function">
      <type></type>
      <name>TrapezoidRuleSolver</name>
      <anchorfile>classPiro_1_1TrapezoidRuleSolver.html</anchorfile>
      <anchor>a6c6ddbc4922560573e1489336334b988</anchor>
      <arglist>(const Teuchos::RCP&lt; Teuchos::ParameterList &gt; &amp;appParams, const Teuchos::RCP&lt; Thyra::ModelEvaluator&lt; Scalar &gt; &gt; &amp;model, const Teuchos::RCP&lt; Thyra::AdaptiveSolutionManager &gt; &amp;solMgr, const Teuchos::RCP&lt; Piro::ObserverBase&lt; Scalar &gt; &gt; &amp;observer=Teuchos::null)</arglist>
    </member>
    <member kind="function">
      <type>Thyra::ModelEvaluatorBase::InArgs&lt; Scalar &gt;</type>
      <name>getNominalValues</name>
      <anchorfile>classPiro_1_1TrapezoidRuleSolver.html</anchorfile>
      <anchor>a6b91af552fafbc51f7f02f2e9faad116</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Thyra::ModelEvaluatorBase::InArgs&lt; Scalar &gt;</type>
      <name>createInArgs</name>
      <anchorfile>classPiro_1_1TrapezoidRuleSolver.html</anchorfile>
      <anchor>ab99b28077719d5c9a96f78ae25aa2a2a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Thyra::VectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>get_p_space</name>
      <anchorfile>classPiro_1_1TrapezoidRuleSolver.html</anchorfile>
      <anchor>a732ba71a146a1a36a0ad0725d254b136</anchor>
      <arglist>(int l) const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Thyra::VectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>get_g_space</name>
      <anchorfile>classPiro_1_1TrapezoidRuleSolver.html</anchorfile>
      <anchor>a50eafa3cac93d313bccca77c239b56a9</anchor>
      <arglist>(int j) const </arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>TrapezoidRuleSolver</name>
      <anchorfile>classPiro_1_1TrapezoidRuleSolver.html</anchorfile>
      <anchor>a6c6ddbc4922560573e1489336334b988</anchor>
      <arglist>(const Teuchos::RCP&lt; Teuchos::ParameterList &gt; &amp;appParams, const Teuchos::RCP&lt; Thyra::ModelEvaluator&lt; Scalar &gt; &gt; &amp;model, const Teuchos::RCP&lt; Thyra::AdaptiveSolutionManager &gt; &amp;solMgr, const Teuchos::RCP&lt; Piro::ObserverBase&lt; Scalar &gt; &gt; &amp;observer=Teuchos::null)</arglist>
    </member>
    <member kind="function">
      <type>Thyra::ModelEvaluatorBase::InArgs&lt; Scalar &gt;</type>
      <name>getNominalValues</name>
      <anchorfile>classPiro_1_1TrapezoidRuleSolver.html</anchorfile>
      <anchor>a6b91af552fafbc51f7f02f2e9faad116</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Thyra::ModelEvaluatorBase::InArgs&lt; Scalar &gt;</type>
      <name>createInArgs</name>
      <anchorfile>classPiro_1_1TrapezoidRuleSolver.html</anchorfile>
      <anchor>ab99b28077719d5c9a96f78ae25aa2a2a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Thyra::VectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>get_p_space</name>
      <anchorfile>classPiro_1_1TrapezoidRuleSolver.html</anchorfile>
      <anchor>a732ba71a146a1a36a0ad0725d254b136</anchor>
      <arglist>(int l) const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Thyra::VectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>get_g_space</name>
      <anchorfile>classPiro_1_1TrapezoidRuleSolver.html</anchorfile>
      <anchor>a50eafa3cac93d313bccca77c239b56a9</anchor>
      <arglist>(int j) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Piro::Epetra::VelocityVerletSolver</name>
    <filename>classPiro_1_1Epetra_1_1VelocityVerletSolver.html</filename>
    <member kind="function">
      <type></type>
      <name>VelocityVerletSolver</name>
      <anchorfile>classPiro_1_1Epetra_1_1VelocityVerletSolver.html</anchorfile>
      <anchor>af9ced9e5f407714b4611b53cd4bdc1e1</anchor>
      <arglist>(Teuchos::RCP&lt; Teuchos::ParameterList &gt; appParams, Teuchos::RCP&lt; EpetraExt::ModelEvaluator &gt; model, Teuchos::RCP&lt; NOX::Epetra::Observer &gt; observer=Teuchos::null)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>VelocityVerletSolver</name>
      <anchorfile>classPiro_1_1Epetra_1_1VelocityVerletSolver.html</anchorfile>
      <anchor>af9ced9e5f407714b4611b53cd4bdc1e1</anchor>
      <arglist>(Teuchos::RCP&lt; Teuchos::ParameterList &gt; appParams, Teuchos::RCP&lt; EpetraExt::ModelEvaluator &gt; model, Teuchos::RCP&lt; NOX::Epetra::Observer &gt; observer=Teuchos::null)</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Epetra_Vector &gt;</type>
      <name>get_p_init</name>
      <anchorfile>classPiro_1_1Epetra_1_1VelocityVerletSolver.html</anchorfile>
      <anchor>a1470616f572923c684a8adb3e3d7dc94</anchor>
      <arglist>(int l) const </arglist>
    </member>
    <member kind="function">
      <type>EpetraExt::ModelEvaluator::InArgs</type>
      <name>createInArgs</name>
      <anchorfile>classPiro_1_1Epetra_1_1VelocityVerletSolver.html</anchorfile>
      <anchor>abaebd7c5418ba5f144c56e6644822757</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>EpetraExt::ModelEvaluator::OutArgs</type>
      <name>createOutArgs</name>
      <anchorfile>classPiro_1_1Epetra_1_1VelocityVerletSolver.html</anchorfile>
      <anchor>ac67883f2af4c84cb22c1dd3460f0217f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>evalModel</name>
      <anchorfile>classPiro_1_1Epetra_1_1VelocityVerletSolver.html</anchorfile>
      <anchor>a6e8c8fe1220934c8419cd88dd2dc42ce</anchor>
      <arglist>(const InArgs &amp;inArgs, const OutArgs &amp;outArgs) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Piro::VelocityVerletSolver</name>
    <filename>classPiro_1_1VelocityVerletSolver.html</filename>
    <templarg></templarg>
    <templarg></templarg>
    <templarg></templarg>
    <templarg></templarg>
    <member kind="function">
      <type></type>
      <name>VelocityVerletSolver</name>
      <anchorfile>classPiro_1_1VelocityVerletSolver.html</anchorfile>
      <anchor>a38997c7a6345e47ae1b4b77c64d033d9</anchor>
      <arglist>(const Teuchos::RCP&lt; Teuchos::ParameterList &gt; &amp;appParams, const Teuchos::RCP&lt; Thyra::ModelEvaluator&lt; Scalar &gt; &gt; &amp;model, const Teuchos::RCP&lt; Thyra::AdaptiveSolutionManager &gt; &amp;solMgr, const Teuchos::RCP&lt; Piro::ObserverBase&lt; Scalar &gt; &gt; &amp;observer=Teuchos::null)</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Thyra::VectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>get_x</name>
      <anchorfile>classPiro_1_1VelocityVerletSolver.html</anchorfile>
      <anchor>a0dbe0a4ec57571276e2e2befebbf373c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Thyra::VectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>get_x_dot</name>
      <anchorfile>classPiro_1_1VelocityVerletSolver.html</anchorfile>
      <anchor>ac3d8f33c3b12ddb57a59278d0a83ff2d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Thyra::ModelEvaluatorBase::InArgs&lt; Scalar &gt;</type>
      <name>getNominalValues</name>
      <anchorfile>classPiro_1_1VelocityVerletSolver.html</anchorfile>
      <anchor>ace037b104993131508096970813d3304</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Thyra::ModelEvaluatorBase::InArgs&lt; Scalar &gt;</type>
      <name>createInArgs</name>
      <anchorfile>classPiro_1_1VelocityVerletSolver.html</anchorfile>
      <anchor>a324eae363cc3cf9f42a3d0883d96ad8a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Thyra::VectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>get_p_space</name>
      <anchorfile>classPiro_1_1VelocityVerletSolver.html</anchorfile>
      <anchor>a979131cd437b2c20eba3e204f6751d68</anchor>
      <arglist>(int l) const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Thyra::VectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>get_g_space</name>
      <anchorfile>classPiro_1_1VelocityVerletSolver.html</anchorfile>
      <anchor>a4cc1f85bffaaf2368de2befd50a5eb97</anchor>
      <arglist>(int j) const </arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>VelocityVerletSolver</name>
      <anchorfile>classPiro_1_1VelocityVerletSolver.html</anchorfile>
      <anchor>a38997c7a6345e47ae1b4b77c64d033d9</anchor>
      <arglist>(const Teuchos::RCP&lt; Teuchos::ParameterList &gt; &amp;appParams, const Teuchos::RCP&lt; Thyra::ModelEvaluator&lt; Scalar &gt; &gt; &amp;model, const Teuchos::RCP&lt; Thyra::AdaptiveSolutionManager &gt; &amp;solMgr, const Teuchos::RCP&lt; Piro::ObserverBase&lt; Scalar &gt; &gt; &amp;observer=Teuchos::null)</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Thyra::VectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>get_x</name>
      <anchorfile>classPiro_1_1VelocityVerletSolver.html</anchorfile>
      <anchor>a0dbe0a4ec57571276e2e2befebbf373c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Thyra::VectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>get_x_dot</name>
      <anchorfile>classPiro_1_1VelocityVerletSolver.html</anchorfile>
      <anchor>ac3d8f33c3b12ddb57a59278d0a83ff2d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Thyra::ModelEvaluatorBase::InArgs&lt; Scalar &gt;</type>
      <name>getNominalValues</name>
      <anchorfile>classPiro_1_1VelocityVerletSolver.html</anchorfile>
      <anchor>ace037b104993131508096970813d3304</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Thyra::ModelEvaluatorBase::InArgs&lt; Scalar &gt;</type>
      <name>createInArgs</name>
      <anchorfile>classPiro_1_1VelocityVerletSolver.html</anchorfile>
      <anchor>a324eae363cc3cf9f42a3d0883d96ad8a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Thyra::VectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>get_p_space</name>
      <anchorfile>classPiro_1_1VelocityVerletSolver.html</anchorfile>
      <anchor>a979131cd437b2c20eba3e204f6751d68</anchor>
      <arglist>(int l) const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Thyra::VectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>get_g_space</name>
      <anchorfile>classPiro_1_1VelocityVerletSolver.html</anchorfile>
      <anchor>a4cc1f85bffaaf2368de2befd50a5eb97</anchor>
      <arglist>(int j) const </arglist>
    </member>
  </compound>
  <compound kind="namespace">
    <name>Piro</name>
    <filename>namespacePiro.html</filename>
    <namespace>Piro::Epetra</namespace>
    <class kind="class">Piro::InvertMassMatrixDecorator</class>
    <class kind="class">Piro::LOCAAdaptiveSolver</class>
    <class kind="class">Piro::LOCASolver</class>
    <class kind="class">Piro::MatrixFreeDecorator</class>
    <class kind="class">Piro::MatrixFreeLinearOp</class>
    <class kind="class">Piro::NOXSolver</class>
    <class kind="class">Piro::ObserverBase</class>
    <class kind="class">Piro::ObserverToLOCASaveDataStrategyAdapter</class>
    <class kind="class">Piro::ObserverToRythmosIntegrationObserverAdapter</class>
    <class kind="class">Piro::Provider</class>
    <class kind="class">Piro::ProviderBase</class>
    <class kind="class">Piro::RythmosNOXRowSumUpdaterObserver</class>
    <class kind="class">Piro::RythmosSolver</class>
    <class kind="class">Piro::RythmosStepControlFactory</class>
    <class kind="class">Piro::RythmosStepperFactory</class>
    <class kind="class">Piro::SolutionObserverBase</class>
    <class kind="class">Piro::SolverFactory</class>
    <class kind="class">Piro::SteadyStateSolver</class>
    <class kind="class">Piro::TransientDecorator</class>
    <class kind="class">Piro::TrapezoidDecorator</class>
    <class kind="class">Piro::TrapezoidRuleSolver</class>
    <class kind="class">Piro::VelocityVerletSolver</class>
    <member kind="function">
      <type>Teuchos::RCP&lt; RythmosSolver&lt; Scalar &gt; &gt;</type>
      <name>rythmosSolver</name>
      <anchorfile>namespacePiro.html</anchorfile>
      <anchor>a9d7c8ef0749cad7da5725af0006e9c80</anchor>
      <arglist>(const Teuchos::RCP&lt; Teuchos::ParameterList &gt; &amp;appParams, const Teuchos::RCP&lt; Thyra::ModelEvaluator&lt; Scalar &gt; &gt; &amp;model, const Teuchos::RCP&lt; ObserverBase&lt; Scalar &gt; &gt; &amp;piroObserver)</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; Teuchos::ParameterList &gt;</type>
      <name>extractStratimikosParams</name>
      <anchorfile>namespacePiro.html</anchorfile>
      <anchor>aa264b40b86403515b1537ce53289d2a6</anchor>
      <arglist>(const Teuchos::RCP&lt; Teuchos::ParameterList &gt; &amp;piroParams)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>renamePreconditionerParamList</name>
      <anchorfile>namespacePiro.html</anchorfile>
      <anchor>a2844c5c6339c17fa9a3737aacdcc5304</anchor>
      <arglist>(const Teuchos::RCP&lt; Teuchos::ParameterList &gt; &amp;stratParams, const std::string &amp;oldname, const std::string &amp;newname)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>PerformAnalysis</name>
      <anchorfile>group__Piro__Thyra__analysis__driver__grp.html</anchorfile>
      <anchor>ga11854fca36d1c0a26755a62218ec82fb</anchor>
      <arglist>(Thyra::ModelEvaluatorDefaultBase&lt; double &gt; &amp;piroModel, Teuchos::ParameterList &amp;analysisParams, Teuchos::RCP&lt; Thyra::VectorBase&lt; double &gt; &gt; &amp;result)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>PerformMoochoAnalysis</name>
      <anchorfile>group__Piro__Thyra__analysis__driver__grp.html</anchorfile>
      <anchor>gad7c0029424c85582d6f57fde003db979</anchor>
      <arglist>(Thyra::ModelEvaluatorDefaultBase&lt; double &gt; &amp;piroModel, Teuchos::ParameterList &amp;moochoParams, Teuchos::RCP&lt; Thyra::VectorBase&lt; double &gt; &gt; &amp;p)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>PerformDakotaAnalysis</name>
      <anchorfile>group__Piro__Thyra__analysis__driver__grp.html</anchorfile>
      <anchor>ga1edc944a03c278e5387f26cc8760c1f4</anchor>
      <arglist>(Thyra::ModelEvaluatorDefaultBase&lt; double &gt; &amp;piroModel, Teuchos::ParameterList &amp;dakotaParams, Teuchos::RCP&lt; Thyra::VectorBase&lt; double &gt; &gt; &amp;p)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>PerformOptiPackAnalysis</name>
      <anchorfile>group__Piro__Thyra__analysis__driver__grp.html</anchorfile>
      <anchor>gaa2a1e1cb19973485bc2520bfd9fe2806</anchor>
      <arglist>(Thyra::ModelEvaluatorDefaultBase&lt; double &gt; &amp;piroModel, Teuchos::ParameterList &amp;optipackParams, Teuchos::ParameterList &amp;globipackParams, Teuchos::RCP&lt; Thyra::VectorBase&lt; double &gt; &gt; &amp;p)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>PerformROLAnalysis</name>
      <anchorfile>group__Piro__Thyra__analysis__driver__grp.html</anchorfile>
      <anchor>gada9af6abf0021b3f9171ebbea0a2f3de</anchor>
      <arglist>(Thyra::ModelEvaluatorDefaultBase&lt; double &gt; &amp;piroModel, Teuchos::ParameterList &amp;rolParams, Teuchos::RCP&lt; Thyra::VectorBase&lt; double &gt; &gt; &amp;p)</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Teuchos::ParameterList &gt;</type>
      <name>getValidPiroAnalysisParameters</name>
      <anchorfile>group__Piro__analysis__driver__grp.html</anchorfile>
      <anchor>gaba4d9ce5a1f6e5fa5d61ed044ad10828</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Teuchos::ParameterList &gt;</type>
      <name>getValidPiroAnalysisDakotaParameters</name>
      <anchorfile>group__Piro__analysis__driver__grp.html</anchorfile>
      <anchor>ga1caa2a6d80140119808cf56b7eb3c9d9</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>PerformSolve</name>
      <anchorfile>group__Piro__Thyra__solve__driver__grp.html</anchorfile>
      <anchor>gad4507966c123f363324048ce48abda4b</anchor>
      <arglist>(const Thyra::ResponseOnlyModelEvaluatorBase&lt; Scalar &gt; &amp;piroModel, Teuchos::RCP&lt; Thyra::VectorBase&lt; Scalar &gt; &gt; &amp;response)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>PerformSolve</name>
      <anchorfile>group__Piro__Thyra__solve__driver__grp.html</anchorfile>
      <anchor>gacfd7256c27498d6e559f360bc9079449</anchor>
      <arglist>(const Thyra::ResponseOnlyModelEvaluatorBase&lt; Scalar &gt; &amp;piroModel, Teuchos::ParameterList &amp;solveParams, Teuchos::RCP&lt; Thyra::VectorBase&lt; Scalar &gt; &gt; &amp;response)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>PerformSolve</name>
      <anchorfile>group__Piro__Thyra__solve__driver__grp.html</anchorfile>
      <anchor>gacbe2c3f69f34745c3f46235fd9f0f5e6</anchor>
      <arglist>(const Thyra::ResponseOnlyModelEvaluatorBase&lt; Scalar &gt; &amp;piroModel, Teuchos::ParameterList &amp;solveParams, Teuchos::RCP&lt; Thyra::VectorBase&lt; Scalar &gt; &gt; &amp;response, Teuchos::RCP&lt; Thyra::MultiVectorBase&lt; Scalar &gt; &gt; &amp;sensitivity)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>PerformSolve</name>
      <anchorfile>group__Piro__Thyra__solve__driver__grp.html</anchorfile>
      <anchor>ga8bc4622f6114d42a8710864849cf5a39</anchor>
      <arglist>(const Thyra::ResponseOnlyModelEvaluatorBase&lt; Scalar &gt; &amp;piroModel, Teuchos::ParameterList &amp;solveParams, Teuchos::Array&lt; Teuchos::RCP&lt; Thyra::VectorBase&lt; Scalar &gt; &gt; &gt; &amp;responses, Teuchos::Array&lt; Teuchos::Array&lt; Teuchos::RCP&lt; Thyra::MultiVectorBase&lt; Scalar &gt; &gt; &gt; &gt; &amp;sensitivities)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>PerformSolve</name>
      <anchorfile>group__Piro__Thyra__solve__driver__grp.html</anchorfile>
      <anchor>ga11a701402f5a363748f914a4d2ad53bd</anchor>
      <arglist>(const Thyra::ResponseOnlyModelEvaluatorBase&lt; Scalar &gt; &amp;piroModel, Teuchos::ParameterList &amp;solveParams, Teuchos::Array&lt; Teuchos::RCP&lt; const Thyra::VectorBase&lt; Scalar &gt; &gt; &gt; &amp;responses, Teuchos::Array&lt; Teuchos::Array&lt; Teuchos::RCP&lt; const Thyra::MultiVectorBase&lt; Scalar &gt; &gt; &gt; &gt; &amp;sensitivities)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>PerformSolveBase</name>
      <anchorfile>group__Piro__Thyra__solve__driver__grp.html</anchorfile>
      <anchor>gab77bf33565113ddde2c79d29a74e1fa5</anchor>
      <arglist>(const Thyra::ModelEvaluator&lt; Scalar &gt; &amp;piroModel, Teuchos::RCP&lt; Thyra::VectorBase&lt; Scalar &gt; &gt; &amp;response)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>PerformSolveBase</name>
      <anchorfile>group__Piro__Thyra__solve__driver__grp.html</anchorfile>
      <anchor>ga561519af97904fe5cd5052bdf3f449ab</anchor>
      <arglist>(const Thyra::ModelEvaluator&lt; Scalar &gt; &amp;piroModel, Teuchos::ParameterList &amp;solveParams, Teuchos::RCP&lt; Thyra::VectorBase&lt; Scalar &gt; &gt; &amp;response)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>PerformSolveBase</name>
      <anchorfile>group__Piro__Thyra__solve__driver__grp.html</anchorfile>
      <anchor>ga0552abf3fe1a3ca768cc370f360de1f6</anchor>
      <arglist>(const Thyra::ModelEvaluator&lt; Scalar &gt; &amp;piroModel, Teuchos::ParameterList &amp;solveParams, Teuchos::RCP&lt; Thyra::VectorBase&lt; Scalar &gt; &gt; &amp;response, Teuchos::RCP&lt; Thyra::MultiVectorBase&lt; Scalar &gt; &gt; &amp;sensitivity)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>PerformSolveBase</name>
      <anchorfile>group__Piro__Thyra__solve__driver__grp.html</anchorfile>
      <anchor>ga40c957f6fbb22fd5fa5cdeed1d47a88d</anchor>
      <arglist>(const Thyra::ModelEvaluator&lt; Scalar &gt; &amp;piroModel, Teuchos::ParameterList &amp;solveParams, Teuchos::Array&lt; Teuchos::RCP&lt; Thyra::VectorBase&lt; Scalar &gt; &gt; &gt; &amp;responses, Teuchos::Array&lt; Teuchos::Array&lt; Teuchos::RCP&lt; Thyra::MultiVectorBase&lt; Scalar &gt; &gt; &gt; &gt; &amp;sensitivities)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>PerformSolveBase</name>
      <anchorfile>group__Piro__Thyra__solve__driver__grp.html</anchorfile>
      <anchor>ga057eb9d71f1e8f35a15035d530ea76af</anchor>
      <arglist>(const Thyra::ModelEvaluator&lt; Scalar &gt; &amp;piroModel, Teuchos::ParameterList &amp;solveParams, Teuchos::Array&lt; Teuchos::RCP&lt; const Thyra::VectorBase&lt; Scalar &gt; &gt; &gt; &amp;responses, Teuchos::Array&lt; Teuchos::Array&lt; Teuchos::RCP&lt; const Thyra::MultiVectorBase&lt; Scalar &gt; &gt; &gt; &gt; &amp;sensitivities)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>PerformSolveBase</name>
      <anchorfile>group__Piro__Thyra__solve__driver__grp.html</anchorfile>
      <anchor>ga530d41d550a71cfae9a99987b055bbdd</anchor>
      <arglist>(const Thyra::ModelEvaluator&lt; Scalar &gt; &amp;piroModel, Teuchos::ParameterList &amp;solveParams, Teuchos::Array&lt; Teuchos::RCP&lt; const Thyra::VectorBase&lt; Scalar &gt; &gt; &gt; &amp;responses, Teuchos::Array&lt; Teuchos::Array&lt; Teuchos::RCP&lt; const Thyra::MultiVectorBase&lt; Scalar &gt; &gt; &gt; &gt; &amp;sensitivities, Teuchos::RCP&lt; SolutionObserverBase&lt; Scalar, const Thyra::VectorBase&lt; Scalar &gt; &gt; &gt; observer)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>PerformAnalysis</name>
      <anchorfile>group__Piro__Thyra__analysis__driver__grp.html</anchorfile>
      <anchor>ga11854fca36d1c0a26755a62218ec82fb</anchor>
      <arglist>(Thyra::ModelEvaluatorDefaultBase&lt; double &gt; &amp;piroModel, Teuchos::ParameterList &amp;analysisParams, Teuchos::RCP&lt; Thyra::VectorBase&lt; double &gt; &gt; &amp;result)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>PerformMoochoAnalysis</name>
      <anchorfile>group__Piro__Thyra__analysis__driver__grp.html</anchorfile>
      <anchor>gad7c0029424c85582d6f57fde003db979</anchor>
      <arglist>(Thyra::ModelEvaluatorDefaultBase&lt; double &gt; &amp;piroModel, Teuchos::ParameterList &amp;moochoParams, Teuchos::RCP&lt; Thyra::VectorBase&lt; double &gt; &gt; &amp;p)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>PerformDakotaAnalysis</name>
      <anchorfile>group__Piro__Thyra__analysis__driver__grp.html</anchorfile>
      <anchor>ga1edc944a03c278e5387f26cc8760c1f4</anchor>
      <arglist>(Thyra::ModelEvaluatorDefaultBase&lt; double &gt; &amp;piroModel, Teuchos::ParameterList &amp;dakotaParams, Teuchos::RCP&lt; Thyra::VectorBase&lt; double &gt; &gt; &amp;p)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>PerformOptiPackAnalysis</name>
      <anchorfile>group__Piro__Thyra__analysis__driver__grp.html</anchorfile>
      <anchor>gaa2a1e1cb19973485bc2520bfd9fe2806</anchor>
      <arglist>(Thyra::ModelEvaluatorDefaultBase&lt; double &gt; &amp;piroModel, Teuchos::ParameterList &amp;optipackParams, Teuchos::ParameterList &amp;globipackParams, Teuchos::RCP&lt; Thyra::VectorBase&lt; double &gt; &gt; &amp;p)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>PerformROLAnalysis</name>
      <anchorfile>group__Piro__Thyra__analysis__driver__grp.html</anchorfile>
      <anchor>gada9af6abf0021b3f9171ebbea0a2f3de</anchor>
      <arglist>(Thyra::ModelEvaluatorDefaultBase&lt; double &gt; &amp;piroModel, Teuchos::ParameterList &amp;rolParams, Teuchos::RCP&lt; Thyra::VectorBase&lt; double &gt; &gt; &amp;p)</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Teuchos::ParameterList &gt;</type>
      <name>getValidPiroAnalysisParameters</name>
      <anchorfile>group__Piro__analysis__driver__grp.html</anchorfile>
      <anchor>gaba4d9ce5a1f6e5fa5d61ed044ad10828</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Teuchos::ParameterList &gt;</type>
      <name>getValidPiroAnalysisDakotaParameters</name>
      <anchorfile>group__Piro__analysis__driver__grp.html</anchorfile>
      <anchor>ga1caa2a6d80140119808cf56b7eb3c9d9</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>PerformSolve</name>
      <anchorfile>group__Piro__Thyra__solve__driver__grp.html</anchorfile>
      <anchor>gad4507966c123f363324048ce48abda4b</anchor>
      <arglist>(const Thyra::ResponseOnlyModelEvaluatorBase&lt; Scalar &gt; &amp;piroModel, Teuchos::RCP&lt; Thyra::VectorBase&lt; Scalar &gt; &gt; &amp;response)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>PerformSolve</name>
      <anchorfile>group__Piro__Thyra__solve__driver__grp.html</anchorfile>
      <anchor>gacfd7256c27498d6e559f360bc9079449</anchor>
      <arglist>(const Thyra::ResponseOnlyModelEvaluatorBase&lt; Scalar &gt; &amp;piroModel, Teuchos::ParameterList &amp;solveParams, Teuchos::RCP&lt; Thyra::VectorBase&lt; Scalar &gt; &gt; &amp;response)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>PerformSolve</name>
      <anchorfile>group__Piro__Thyra__solve__driver__grp.html</anchorfile>
      <anchor>gacbe2c3f69f34745c3f46235fd9f0f5e6</anchor>
      <arglist>(const Thyra::ResponseOnlyModelEvaluatorBase&lt; Scalar &gt; &amp;piroModel, Teuchos::ParameterList &amp;solveParams, Teuchos::RCP&lt; Thyra::VectorBase&lt; Scalar &gt; &gt; &amp;response, Teuchos::RCP&lt; Thyra::MultiVectorBase&lt; Scalar &gt; &gt; &amp;sensitivity)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>PerformSolve</name>
      <anchorfile>group__Piro__Thyra__solve__driver__grp.html</anchorfile>
      <anchor>ga8bc4622f6114d42a8710864849cf5a39</anchor>
      <arglist>(const Thyra::ResponseOnlyModelEvaluatorBase&lt; Scalar &gt; &amp;piroModel, Teuchos::ParameterList &amp;solveParams, Teuchos::Array&lt; Teuchos::RCP&lt; Thyra::VectorBase&lt; Scalar &gt; &gt; &gt; &amp;responses, Teuchos::Array&lt; Teuchos::Array&lt; Teuchos::RCP&lt; Thyra::MultiVectorBase&lt; Scalar &gt; &gt; &gt; &gt; &amp;sensitivities)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>PerformSolve</name>
      <anchorfile>group__Piro__Thyra__solve__driver__grp.html</anchorfile>
      <anchor>ga11a701402f5a363748f914a4d2ad53bd</anchor>
      <arglist>(const Thyra::ResponseOnlyModelEvaluatorBase&lt; Scalar &gt; &amp;piroModel, Teuchos::ParameterList &amp;solveParams, Teuchos::Array&lt; Teuchos::RCP&lt; const Thyra::VectorBase&lt; Scalar &gt; &gt; &gt; &amp;responses, Teuchos::Array&lt; Teuchos::Array&lt; Teuchos::RCP&lt; const Thyra::MultiVectorBase&lt; Scalar &gt; &gt; &gt; &gt; &amp;sensitivities)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>PerformSolveBase</name>
      <anchorfile>group__Piro__Thyra__solve__driver__grp.html</anchorfile>
      <anchor>gab77bf33565113ddde2c79d29a74e1fa5</anchor>
      <arglist>(const Thyra::ModelEvaluator&lt; Scalar &gt; &amp;piroModel, Teuchos::RCP&lt; Thyra::VectorBase&lt; Scalar &gt; &gt; &amp;response)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>PerformSolveBase</name>
      <anchorfile>group__Piro__Thyra__solve__driver__grp.html</anchorfile>
      <anchor>ga561519af97904fe5cd5052bdf3f449ab</anchor>
      <arglist>(const Thyra::ModelEvaluator&lt; Scalar &gt; &amp;piroModel, Teuchos::ParameterList &amp;solveParams, Teuchos::RCP&lt; Thyra::VectorBase&lt; Scalar &gt; &gt; &amp;response)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>PerformSolveBase</name>
      <anchorfile>group__Piro__Thyra__solve__driver__grp.html</anchorfile>
      <anchor>ga0552abf3fe1a3ca768cc370f360de1f6</anchor>
      <arglist>(const Thyra::ModelEvaluator&lt; Scalar &gt; &amp;piroModel, Teuchos::ParameterList &amp;solveParams, Teuchos::RCP&lt; Thyra::VectorBase&lt; Scalar &gt; &gt; &amp;response, Teuchos::RCP&lt; Thyra::MultiVectorBase&lt; Scalar &gt; &gt; &amp;sensitivity)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>PerformSolveBase</name>
      <anchorfile>group__Piro__Thyra__solve__driver__grp.html</anchorfile>
      <anchor>ga40c957f6fbb22fd5fa5cdeed1d47a88d</anchor>
      <arglist>(const Thyra::ModelEvaluator&lt; Scalar &gt; &amp;piroModel, Teuchos::ParameterList &amp;solveParams, Teuchos::Array&lt; Teuchos::RCP&lt; Thyra::VectorBase&lt; Scalar &gt; &gt; &gt; &amp;responses, Teuchos::Array&lt; Teuchos::Array&lt; Teuchos::RCP&lt; Thyra::MultiVectorBase&lt; Scalar &gt; &gt; &gt; &gt; &amp;sensitivities)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>PerformSolveBase</name>
      <anchorfile>group__Piro__Thyra__solve__driver__grp.html</anchorfile>
      <anchor>ga057eb9d71f1e8f35a15035d530ea76af</anchor>
      <arglist>(const Thyra::ModelEvaluator&lt; Scalar &gt; &amp;piroModel, Teuchos::ParameterList &amp;solveParams, Teuchos::Array&lt; Teuchos::RCP&lt; const Thyra::VectorBase&lt; Scalar &gt; &gt; &gt; &amp;responses, Teuchos::Array&lt; Teuchos::Array&lt; Teuchos::RCP&lt; const Thyra::MultiVectorBase&lt; Scalar &gt; &gt; &gt; &gt; &amp;sensitivities)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>PerformSolveBase</name>
      <anchorfile>group__Piro__Thyra__solve__driver__grp.html</anchorfile>
      <anchor>ga530d41d550a71cfae9a99987b055bbdd</anchor>
      <arglist>(const Thyra::ModelEvaluator&lt; Scalar &gt; &amp;piroModel, Teuchos::ParameterList &amp;solveParams, Teuchos::Array&lt; Teuchos::RCP&lt; const Thyra::VectorBase&lt; Scalar &gt; &gt; &gt; &amp;responses, Teuchos::Array&lt; Teuchos::Array&lt; Teuchos::RCP&lt; const Thyra::MultiVectorBase&lt; Scalar &gt; &gt; &gt; &gt; &amp;sensitivities, Teuchos::RCP&lt; SolutionObserverBase&lt; Scalar, const Thyra::VectorBase&lt; Scalar &gt; &gt; &gt; observer)</arglist>
    </member>
  </compound>
  <compound kind="namespace">
    <name>Piro::Epetra</name>
    <filename>namespacePiro_1_1Epetra.html</filename>
    <class kind="class">Piro::Epetra::AbstractNetworkModel</class>
    <class kind="class">Piro::Epetra::AdaptiveSolutionManager</class>
    <class kind="class">Piro::Epetra::InvertMassMatrixDecorator</class>
    <class kind="class">Piro::Epetra::LOCAAdaptiveSolver</class>
    <class kind="class">Piro::Epetra::LOCASolver</class>
    <class kind="class">Piro::Epetra::MatrixFreeDecorator</class>
    <class kind="class">Piro::Epetra::MatrixFreeOperator</class>
    <class kind="class">Piro::Epetra::NECoupledModelEvaluator</class>
    <class kind="class">Piro::Epetra::NewmarkDecorator</class>
    <class kind="class">Piro::Epetra::NewmarkSolver</class>
    <class kind="class">Piro::Epetra::NOXSolver</class>
    <class kind="class">Piro::Epetra::ParamToResponseNetworkModel</class>
    <class kind="class">Piro::Epetra::RythmosSolver</class>
    <class kind="class">Piro::Epetra::SensitivityOperator</class>
    <class kind="class">Piro::Epetra::SolverFactory</class>
    <class kind="class">Piro::Epetra::StokhosMPSolver</class>
    <class kind="class">Piro::Epetra::StokhosNOXObserver</class>
    <class kind="class">Piro::Epetra::StokhosSolver</class>
    <class kind="class">Piro::Epetra::StokhosSolverFactory</class>
    <class kind="class">Piro::Epetra::TrapezoidDecorator</class>
    <class kind="class">Piro::Epetra::TrapezoidRuleSolver</class>
    <class kind="class">Piro::Epetra::VelocityVerletSolver</class>
    <member kind="function">
      <type>int</type>
      <name>PerformAnalysis</name>
      <anchorfile>group__Piro__Epetra__analysis__driver__grp.html</anchorfile>
      <anchor>gaa3d8225d14ec83b461b709cedee8d791</anchor>
      <arglist>(EpetraExt::ModelEvaluator &amp;piroModel, Teuchos::ParameterList &amp;analysisParams, Teuchos::RCP&lt; Epetra_Vector &gt; &amp;p)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>PerformSolve</name>
      <anchorfile>group__Piro__Epetra__solve__driver__grp.html</anchorfile>
      <anchor>ga1ca846ebc019021cafa888ff919d4fce</anchor>
      <arglist>(const EpetraExt::ModelEvaluator &amp;piroSolver, Teuchos::ParameterList &amp;solveParams, Teuchos::Array&lt; Teuchos::RCP&lt; Epetra_Vector &gt; &gt; &amp;responses, Teuchos::Array&lt; Teuchos::Array&lt; Teuchos::RCP&lt; Epetra_MultiVector &gt; &gt; &gt; &amp;sensitivities)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>PerformSolve</name>
      <anchorfile>group__Piro__Epetra__solve__driver__grp.html</anchorfile>
      <anchor>ga7a3e2d9c085c951c9fbe274f33a17671</anchor>
      <arglist>(const EpetraExt::ModelEvaluator &amp;piroSolver, Teuchos::ParameterList &amp;solveParams, Teuchos::Array&lt; Teuchos::RCP&lt; const Epetra_Vector &gt; &gt; &amp;responses, Teuchos::Array&lt; Teuchos::Array&lt; Teuchos::RCP&lt; const Epetra_MultiVector &gt; &gt; &gt; &amp;sensitivities)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>PerformAnalysis</name>
      <anchorfile>group__Piro__Epetra__analysis__driver__grp.html</anchorfile>
      <anchor>gaa3d8225d14ec83b461b709cedee8d791</anchor>
      <arglist>(EpetraExt::ModelEvaluator &amp;piroModel, Teuchos::ParameterList &amp;analysisParams, Teuchos::RCP&lt; Epetra_Vector &gt; &amp;p)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>PerformSolve</name>
      <anchorfile>group__Piro__Epetra__solve__driver__grp.html</anchorfile>
      <anchor>ga1ca846ebc019021cafa888ff919d4fce</anchor>
      <arglist>(const EpetraExt::ModelEvaluator &amp;piroSolver, Teuchos::ParameterList &amp;solveParams, Teuchos::Array&lt; Teuchos::RCP&lt; Epetra_Vector &gt; &gt; &amp;responses, Teuchos::Array&lt; Teuchos::Array&lt; Teuchos::RCP&lt; Epetra_MultiVector &gt; &gt; &gt; &amp;sensitivities)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>PerformSolve</name>
      <anchorfile>group__Piro__Epetra__solve__driver__grp.html</anchorfile>
      <anchor>ga7a3e2d9c085c951c9fbe274f33a17671</anchor>
      <arglist>(const EpetraExt::ModelEvaluator &amp;piroSolver, Teuchos::ParameterList &amp;solveParams, Teuchos::Array&lt; Teuchos::RCP&lt; const Epetra_Vector &gt; &gt; &amp;responses, Teuchos::Array&lt; Teuchos::Array&lt; Teuchos::RCP&lt; const Epetra_MultiVector &gt; &gt; &gt; &amp;sensitivities)</arglist>
    </member>
  </compound>
  <compound kind="namespace">
    <name>TriKota</name>
    <filename>namespaceTriKota.html</filename>
    <class kind="class">TriKota::MPDirectApplicInterface</class>
  </compound>
  <compound kind="group">
    <name>Piro_solver_grp</name>
    <title>Piro solvers</title>
    <filename>group__Piro__solver__grp.html</filename>
    <subgroup>Piro_Thyra_solver_grp</subgroup>
    <subgroup>Piro_Epetra_solver_grp</subgroup>
  </compound>
  <compound kind="group">
    <name>Piro_Thyra_solver_grp</name>
    <title>Thyra-based Piro solvers</title>
    <filename>group__Piro__Thyra__solver__grp.html</filename>
    <class kind="class">Piro::LOCAAdaptiveSolver</class>
    <class kind="class">Piro::LOCASolver</class>
    <class kind="class">Piro::NOXSolver</class>
    <class kind="class">Piro::RythmosSolver</class>
    <class kind="class">Piro::SteadyStateSolver</class>
  </compound>
  <compound kind="group">
    <name>Piro_Epetra_solver_grp</name>
    <title>Epetra-based Piro solvers</title>
    <filename>group__Piro__Epetra__solver__grp.html</filename>
    <class kind="class">Piro::Epetra::LOCAAdaptiveSolver</class>
    <class kind="class">Piro::Epetra::LOCASolver</class>
    <class kind="class">Piro::Epetra::NewmarkDecorator</class>
    <class kind="class">Piro::Epetra::NOXSolver</class>
    <class kind="class">Piro::Epetra::RythmosSolver</class>
    <class kind="class">Piro::Epetra::TrapezoidDecorator</class>
    <class kind="class">Piro::Epetra::VelocityVerletSolver</class>
  </compound>
  <compound kind="group">
    <name>Piro_driver_grp</name>
    <title>Piro drivers</title>
    <filename>group__Piro__driver__grp.html</filename>
    <subgroup>Piro_solve_driver_grp</subgroup>
    <subgroup>Piro_analysis_driver_grp</subgroup>
  </compound>
  <compound kind="group">
    <name>Piro_solve_driver_grp</name>
    <title>Piro solve drivers</title>
    <filename>group__Piro__solve__driver__grp.html</filename>
    <subgroup>Piro_Thyra_solve_driver_grp</subgroup>
    <subgroup>Piro_Epetra_solve_driver_grp</subgroup>
  </compound>
  <compound kind="group">
    <name>Piro_Thyra_solve_driver_grp</name>
    <title>Thyra-based solve drivers</title>
    <filename>group__Piro__Thyra__solve__driver__grp.html</filename>
    <member kind="function">
      <type>void</type>
      <name>PerformSolve</name>
      <anchorfile>group__Piro__Thyra__solve__driver__grp.html</anchorfile>
      <anchor>gad4507966c123f363324048ce48abda4b</anchor>
      <arglist>(const Thyra::ResponseOnlyModelEvaluatorBase&lt; Scalar &gt; &amp;piroModel, Teuchos::RCP&lt; Thyra::VectorBase&lt; Scalar &gt; &gt; &amp;response)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>PerformSolve</name>
      <anchorfile>group__Piro__Thyra__solve__driver__grp.html</anchorfile>
      <anchor>gacfd7256c27498d6e559f360bc9079449</anchor>
      <arglist>(const Thyra::ResponseOnlyModelEvaluatorBase&lt; Scalar &gt; &amp;piroModel, Teuchos::ParameterList &amp;solveParams, Teuchos::RCP&lt; Thyra::VectorBase&lt; Scalar &gt; &gt; &amp;response)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>PerformSolve</name>
      <anchorfile>group__Piro__Thyra__solve__driver__grp.html</anchorfile>
      <anchor>gacbe2c3f69f34745c3f46235fd9f0f5e6</anchor>
      <arglist>(const Thyra::ResponseOnlyModelEvaluatorBase&lt; Scalar &gt; &amp;piroModel, Teuchos::ParameterList &amp;solveParams, Teuchos::RCP&lt; Thyra::VectorBase&lt; Scalar &gt; &gt; &amp;response, Teuchos::RCP&lt; Thyra::MultiVectorBase&lt; Scalar &gt; &gt; &amp;sensitivity)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>PerformSolve</name>
      <anchorfile>group__Piro__Thyra__solve__driver__grp.html</anchorfile>
      <anchor>ga8bc4622f6114d42a8710864849cf5a39</anchor>
      <arglist>(const Thyra::ResponseOnlyModelEvaluatorBase&lt; Scalar &gt; &amp;piroModel, Teuchos::ParameterList &amp;solveParams, Teuchos::Array&lt; Teuchos::RCP&lt; Thyra::VectorBase&lt; Scalar &gt; &gt; &gt; &amp;responses, Teuchos::Array&lt; Teuchos::Array&lt; Teuchos::RCP&lt; Thyra::MultiVectorBase&lt; Scalar &gt; &gt; &gt; &gt; &amp;sensitivities)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>PerformSolve</name>
      <anchorfile>group__Piro__Thyra__solve__driver__grp.html</anchorfile>
      <anchor>ga11a701402f5a363748f914a4d2ad53bd</anchor>
      <arglist>(const Thyra::ResponseOnlyModelEvaluatorBase&lt; Scalar &gt; &amp;piroModel, Teuchos::ParameterList &amp;solveParams, Teuchos::Array&lt; Teuchos::RCP&lt; const Thyra::VectorBase&lt; Scalar &gt; &gt; &gt; &amp;responses, Teuchos::Array&lt; Teuchos::Array&lt; Teuchos::RCP&lt; const Thyra::MultiVectorBase&lt; Scalar &gt; &gt; &gt; &gt; &amp;sensitivities)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>PerformSolveBase</name>
      <anchorfile>group__Piro__Thyra__solve__driver__grp.html</anchorfile>
      <anchor>gab77bf33565113ddde2c79d29a74e1fa5</anchor>
      <arglist>(const Thyra::ModelEvaluator&lt; Scalar &gt; &amp;piroModel, Teuchos::RCP&lt; Thyra::VectorBase&lt; Scalar &gt; &gt; &amp;response)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>PerformSolveBase</name>
      <anchorfile>group__Piro__Thyra__solve__driver__grp.html</anchorfile>
      <anchor>ga561519af97904fe5cd5052bdf3f449ab</anchor>
      <arglist>(const Thyra::ModelEvaluator&lt; Scalar &gt; &amp;piroModel, Teuchos::ParameterList &amp;solveParams, Teuchos::RCP&lt; Thyra::VectorBase&lt; Scalar &gt; &gt; &amp;response)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>PerformSolveBase</name>
      <anchorfile>group__Piro__Thyra__solve__driver__grp.html</anchorfile>
      <anchor>ga0552abf3fe1a3ca768cc370f360de1f6</anchor>
      <arglist>(const Thyra::ModelEvaluator&lt; Scalar &gt; &amp;piroModel, Teuchos::ParameterList &amp;solveParams, Teuchos::RCP&lt; Thyra::VectorBase&lt; Scalar &gt; &gt; &amp;response, Teuchos::RCP&lt; Thyra::MultiVectorBase&lt; Scalar &gt; &gt; &amp;sensitivity)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>PerformSolveBase</name>
      <anchorfile>group__Piro__Thyra__solve__driver__grp.html</anchorfile>
      <anchor>ga40c957f6fbb22fd5fa5cdeed1d47a88d</anchor>
      <arglist>(const Thyra::ModelEvaluator&lt; Scalar &gt; &amp;piroModel, Teuchos::ParameterList &amp;solveParams, Teuchos::Array&lt; Teuchos::RCP&lt; Thyra::VectorBase&lt; Scalar &gt; &gt; &gt; &amp;responses, Teuchos::Array&lt; Teuchos::Array&lt; Teuchos::RCP&lt; Thyra::MultiVectorBase&lt; Scalar &gt; &gt; &gt; &gt; &amp;sensitivities)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>PerformSolveBase</name>
      <anchorfile>group__Piro__Thyra__solve__driver__grp.html</anchorfile>
      <anchor>ga057eb9d71f1e8f35a15035d530ea76af</anchor>
      <arglist>(const Thyra::ModelEvaluator&lt; Scalar &gt; &amp;piroModel, Teuchos::ParameterList &amp;solveParams, Teuchos::Array&lt; Teuchos::RCP&lt; const Thyra::VectorBase&lt; Scalar &gt; &gt; &gt; &amp;responses, Teuchos::Array&lt; Teuchos::Array&lt; Teuchos::RCP&lt; const Thyra::MultiVectorBase&lt; Scalar &gt; &gt; &gt; &gt; &amp;sensitivities)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>PerformSolveBase</name>
      <anchorfile>group__Piro__Thyra__solve__driver__grp.html</anchorfile>
      <anchor>ga530d41d550a71cfae9a99987b055bbdd</anchor>
      <arglist>(const Thyra::ModelEvaluator&lt; Scalar &gt; &amp;piroModel, Teuchos::ParameterList &amp;solveParams, Teuchos::Array&lt; Teuchos::RCP&lt; const Thyra::VectorBase&lt; Scalar &gt; &gt; &gt; &amp;responses, Teuchos::Array&lt; Teuchos::Array&lt; Teuchos::RCP&lt; const Thyra::MultiVectorBase&lt; Scalar &gt; &gt; &gt; &gt; &amp;sensitivities, Teuchos::RCP&lt; SolutionObserverBase&lt; Scalar, const Thyra::VectorBase&lt; Scalar &gt; &gt; &gt; observer)</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>Piro_Epetra_solve_driver_grp</name>
    <title>Epetra-based solve drivers</title>
    <filename>group__Piro__Epetra__solve__driver__grp.html</filename>
    <member kind="function">
      <type>void</type>
      <name>PerformSolve</name>
      <anchorfile>group__Piro__Epetra__solve__driver__grp.html</anchorfile>
      <anchor>ga1ca846ebc019021cafa888ff919d4fce</anchor>
      <arglist>(const EpetraExt::ModelEvaluator &amp;piroSolver, Teuchos::ParameterList &amp;solveParams, Teuchos::Array&lt; Teuchos::RCP&lt; Epetra_Vector &gt; &gt; &amp;responses, Teuchos::Array&lt; Teuchos::Array&lt; Teuchos::RCP&lt; Epetra_MultiVector &gt; &gt; &gt; &amp;sensitivities)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>PerformSolve</name>
      <anchorfile>group__Piro__Epetra__solve__driver__grp.html</anchorfile>
      <anchor>ga7a3e2d9c085c951c9fbe274f33a17671</anchor>
      <arglist>(const EpetraExt::ModelEvaluator &amp;piroSolver, Teuchos::ParameterList &amp;solveParams, Teuchos::Array&lt; Teuchos::RCP&lt; const Epetra_Vector &gt; &gt; &amp;responses, Teuchos::Array&lt; Teuchos::Array&lt; Teuchos::RCP&lt; const Epetra_MultiVector &gt; &gt; &gt; &amp;sensitivities)</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>Piro_analysis_driver_grp</name>
    <title>Piro analysis drivers</title>
    <filename>group__Piro__analysis__driver__grp.html</filename>
    <subgroup>Piro_Thyra_analysis_driver_grp</subgroup>
    <subgroup>Piro_Epetra_analysis_driver_grp</subgroup>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Teuchos::ParameterList &gt;</type>
      <name>getValidPiroAnalysisParameters</name>
      <anchorfile>group__Piro__analysis__driver__grp.html</anchorfile>
      <anchor>gaba4d9ce5a1f6e5fa5d61ed044ad10828</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Teuchos::ParameterList &gt;</type>
      <name>getValidPiroAnalysisDakotaParameters</name>
      <anchorfile>group__Piro__analysis__driver__grp.html</anchorfile>
      <anchor>ga1caa2a6d80140119808cf56b7eb3c9d9</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>Piro_Thyra_analysis_driver_grp</name>
    <title>Thyra-based analysis drivers</title>
    <filename>group__Piro__Thyra__analysis__driver__grp.html</filename>
    <member kind="function">
      <type>int</type>
      <name>PerformAnalysis</name>
      <anchorfile>group__Piro__Thyra__analysis__driver__grp.html</anchorfile>
      <anchor>ga11854fca36d1c0a26755a62218ec82fb</anchor>
      <arglist>(Thyra::ModelEvaluatorDefaultBase&lt; double &gt; &amp;piroModel, Teuchos::ParameterList &amp;analysisParams, Teuchos::RCP&lt; Thyra::VectorBase&lt; double &gt; &gt; &amp;result)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>PerformMoochoAnalysis</name>
      <anchorfile>group__Piro__Thyra__analysis__driver__grp.html</anchorfile>
      <anchor>gad7c0029424c85582d6f57fde003db979</anchor>
      <arglist>(Thyra::ModelEvaluatorDefaultBase&lt; double &gt; &amp;piroModel, Teuchos::ParameterList &amp;moochoParams, Teuchos::RCP&lt; Thyra::VectorBase&lt; double &gt; &gt; &amp;p)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>PerformDakotaAnalysis</name>
      <anchorfile>group__Piro__Thyra__analysis__driver__grp.html</anchorfile>
      <anchor>ga1edc944a03c278e5387f26cc8760c1f4</anchor>
      <arglist>(Thyra::ModelEvaluatorDefaultBase&lt; double &gt; &amp;piroModel, Teuchos::ParameterList &amp;dakotaParams, Teuchos::RCP&lt; Thyra::VectorBase&lt; double &gt; &gt; &amp;p)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>PerformOptiPackAnalysis</name>
      <anchorfile>group__Piro__Thyra__analysis__driver__grp.html</anchorfile>
      <anchor>gaa2a1e1cb19973485bc2520bfd9fe2806</anchor>
      <arglist>(Thyra::ModelEvaluatorDefaultBase&lt; double &gt; &amp;piroModel, Teuchos::ParameterList &amp;optipackParams, Teuchos::ParameterList &amp;globipackParams, Teuchos::RCP&lt; Thyra::VectorBase&lt; double &gt; &gt; &amp;p)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>PerformROLAnalysis</name>
      <anchorfile>group__Piro__Thyra__analysis__driver__grp.html</anchorfile>
      <anchor>gada9af6abf0021b3f9171ebbea0a2f3de</anchor>
      <arglist>(Thyra::ModelEvaluatorDefaultBase&lt; double &gt; &amp;piroModel, Teuchos::ParameterList &amp;rolParams, Teuchos::RCP&lt; Thyra::VectorBase&lt; double &gt; &gt; &amp;p)</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>Piro_Epetra_analysis_driver_grp</name>
    <title>Epetra-based analysis drivers</title>
    <filename>group__Piro__Epetra__analysis__driver__grp.html</filename>
    <member kind="function">
      <type>int</type>
      <name>PerformAnalysis</name>
      <anchorfile>group__Piro__Epetra__analysis__driver__grp.html</anchorfile>
      <anchor>gaa3d8225d14ec83b461b709cedee8d791</anchor>
      <arglist>(EpetraExt::ModelEvaluator &amp;piroModel, Teuchos::ParameterList &amp;analysisParams, Teuchos::RCP&lt; Epetra_Vector &gt; &amp;p)</arglist>
    </member>
  </compound>
  <compound kind="page">
    <name>index</name>
    <title>%Piro: Strategy package for embedded analysis capabilitites</title>
    <filename>index</filename>
    <docanchor file="index" title="Outline">piro_outline</docanchor>
    <docanchor file="index" title="Disclaimer for Beta-Release in Trilinos 11.4">piro_disclaimer</docanchor>
    <docanchor file="index" title="Introduction">piro_intro</docanchor>
    <docanchor file="index" title="Piro Description">piro_overview</docanchor>
    <docanchor file="index" title="Piro Use Case">piro_use</docanchor>
    <docanchor file="index" title="Model Evaluator Confusion">piro_me</docanchor>
    <docanchor file="index" title="Piro Contacts">piro_help</docanchor>
  </compound>
</tagfile>
