<?xml version='1.0' encoding='UTF-8' standalone='yes' ?>
<tagfile>
  <compound kind="class">
    <name>Rythmos::AdjointModelEvaluator</name>
    <filename>classRythmos_1_1AdjointModelEvaluator.html</filename>
    <templarg></templarg>
    <member kind="function">
      <type>RCP&lt; AdjointModelEvaluator&lt; Scalar &gt; &gt;</type>
      <name>adjointModelEvaluator</name>
      <anchorfile>classRythmos_1_1AdjointModelEvaluator.html</anchorfile>
      <anchor>ae3c3ad0dd3b9a67252f51100802d76f5</anchor>
      <arglist>(const RCP&lt; const Thyra::ModelEvaluator&lt; Scalar &gt; &gt; &amp;fwdStateModel, const TimeRange&lt; Scalar &gt; &amp;fwdTimeRange)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>AdjointModelEvaluator</name>
      <anchorfile>classRythmos_1_1AdjointModelEvaluator.html</anchorfile>
      <anchor>a27c2725cabe158e25b328ecf6a33a1c2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setFwdStateModel</name>
      <anchorfile>classRythmos_1_1AdjointModelEvaluator.html</anchorfile>
      <anchor>af3c3ef968ceab6178176a188b5fbc4c9</anchor>
      <arglist>(const RCP&lt; const Thyra::ModelEvaluator&lt; Scalar &gt; &gt; &amp;fwdStateModel, const Thyra::ModelEvaluatorBase::InArgs&lt; Scalar &gt; &amp;basePoint)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setFwdTimeRange</name>
      <anchorfile>classRythmos_1_1AdjointModelEvaluator.html</anchorfile>
      <anchor>a61f51509e35108b6ab3ea52274d2e2d0</anchor>
      <arglist>(const TimeRange&lt; Scalar &gt; &amp;fwdTimeRange)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setFwdStateSolutionBuffer</name>
      <anchorfile>classRythmos_1_1AdjointModelEvaluator.html</anchorfile>
      <anchor>ac8818130814e7450aabb9914229f207e</anchor>
      <arglist>(const RCP&lt; const InterpolationBufferBase&lt; Scalar &gt; &gt; &amp;fwdStateSolutionBuffer)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const Thyra::VectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>get_x_space</name>
      <anchorfile>classRythmos_1_1AdjointModelEvaluator.html</anchorfile>
      <anchor>ae89a71826906206c2c7ab5315f958347</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const Thyra::VectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>get_f_space</name>
      <anchorfile>classRythmos_1_1AdjointModelEvaluator.html</anchorfile>
      <anchor>a6b14b00d77be78d2f72554fb9649766e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Thyra::ModelEvaluatorBase::InArgs&lt; Scalar &gt;</type>
      <name>getNominalValues</name>
      <anchorfile>classRythmos_1_1AdjointModelEvaluator.html</anchorfile>
      <anchor>a2f4585a0654eb6f500eb987e28fab9c0</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; Thyra::LinearOpWithSolveBase&lt; Scalar &gt; &gt;</type>
      <name>create_W</name>
      <anchorfile>classRythmos_1_1AdjointModelEvaluator.html</anchorfile>
      <anchor>a6dbd2ef26fbf185f9bcb2da0528979e8</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; Thyra::LinearOpBase&lt; Scalar &gt; &gt;</type>
      <name>create_W_op</name>
      <anchorfile>classRythmos_1_1AdjointModelEvaluator.html</anchorfile>
      <anchor>a7fd65e6b351772fddf38b5afeb045f4a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Thyra::ModelEvaluatorBase::InArgs&lt; Scalar &gt;</type>
      <name>createInArgs</name>
      <anchorfile>classRythmos_1_1AdjointModelEvaluator.html</anchorfile>
      <anchor>a148952a96aba8b6d93855e462f0be13d</anchor>
      <arglist>() const </arglist>
    </member>
    <docanchor file="classRythmos_1_1AdjointModelEvaluator" title="Overview">Rythmos_AdjointModelEvaluator_Overview_sec</docanchor>
    <docanchor file="classRythmos_1_1AdjointModelEvaluator" title="Implementation Notes">Rythmos_AdjointModelEvaluator_ImplementationNotes_sec</docanchor>
  </compound>
  <compound kind="class">
    <name>Rythmos::BackwardEulerStepper</name>
    <filename>classRythmos_1_1BackwardEulerStepper.html</filename>
    <templarg></templarg>
    <base virtualness="virtual">Rythmos::SolverAcceptingStepperBase</base>
    <base virtualness="virtual">Rythmos::StepControlStrategyAcceptingStepperBase</base>
    <base virtualness="virtual">Rythmos::InterpolatorAcceptingObjectBase</base>
    <member kind="typedef">
      <type>Teuchos::ScalarTraits&lt; Scalar &gt;::magnitudeType</type>
      <name>ScalarMag</name>
      <anchorfile>classRythmos_1_1BackwardEulerStepper.html</anchorfile>
      <anchor>a400a841a7b94c3f110de2de971414876</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; BackwardEulerStepper&lt; Scalar &gt; &gt;</type>
      <name>backwardEulerStepper</name>
      <anchorfile>classRythmos_1_1BackwardEulerStepper.html</anchorfile>
      <anchor>a719c6c8134b9757c63ba52d4cbe76094</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; BackwardEulerStepper&lt; Scalar &gt; &gt;</type>
      <name>backwardEulerStepper</name>
      <anchorfile>classRythmos_1_1BackwardEulerStepper.html</anchorfile>
      <anchor>a50d4ae70764b81218059f0ce917070a2</anchor>
      <arglist>(const RCP&lt; Thyra::ModelEvaluator&lt; Scalar &gt; &gt; &amp;model, const RCP&lt; Thyra::NonlinearSolverBase&lt; Scalar &gt; &gt; &amp;solver)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BackwardEulerStepper</name>
      <anchorfile>classRythmos_1_1BackwardEulerStepper.html</anchorfile>
      <anchor>ac7ecc8e7f3e33b9fe4218bbf7d7ce424</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BackwardEulerStepper</name>
      <anchorfile>classRythmos_1_1BackwardEulerStepper.html</anchorfile>
      <anchor>a582d7484c69c6868f40470b7ba0bbb86</anchor>
      <arglist>(const RCP&lt; Thyra::ModelEvaluator&lt; Scalar &gt; &gt; &amp;model, const RCP&lt; Thyra::NonlinearSolverBase&lt; Scalar &gt; &gt; &amp;solver)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setInterpolator</name>
      <anchorfile>classRythmos_1_1BackwardEulerStepper.html</anchorfile>
      <anchor>a295c4223d054e74912d3bb19a8ba5042</anchor>
      <arglist>(const RCP&lt; InterpolatorBase&lt; Scalar &gt; &gt; &amp;interpolator)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; InterpolatorBase&lt; Scalar &gt; &gt;</type>
      <name>getNonconstInterpolator</name>
      <anchorfile>classRythmos_1_1BackwardEulerStepper.html</anchorfile>
      <anchor>a463fc1d6aeb3b5170aeaf737f986ae27</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const InterpolatorBase&lt; Scalar &gt; &gt;</type>
      <name>getInterpolator</name>
      <anchorfile>classRythmos_1_1BackwardEulerStepper.html</anchorfile>
      <anchor>a934e7def7339b506c82eaa2a591ef256</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; InterpolatorBase&lt; Scalar &gt; &gt;</type>
      <name>unSetInterpolator</name>
      <anchorfile>classRythmos_1_1BackwardEulerStepper.html</anchorfile>
      <anchor>a889e1b0753c702731cd189e482b8aa31</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setStepControlStrategy</name>
      <anchorfile>classRythmos_1_1BackwardEulerStepper.html</anchorfile>
      <anchor>ab025cfbe94466662a978b1870a36d059</anchor>
      <arglist>(const RCP&lt; StepControlStrategyBase&lt; Scalar &gt; &gt; &amp;stepControlStrategy)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; StepControlStrategyBase&lt; Scalar &gt; &gt;</type>
      <name>getNonconstStepControlStrategy</name>
      <anchorfile>classRythmos_1_1BackwardEulerStepper.html</anchorfile>
      <anchor>a6e8d03edd8bd58dc36b2e2336d692865</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const StepControlStrategyBase&lt; Scalar &gt; &gt;</type>
      <name>getStepControlStrategy</name>
      <anchorfile>classRythmos_1_1BackwardEulerStepper.html</anchorfile>
      <anchor>a2e794b787ed6805380ecf71a89bb01d9</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setSolver</name>
      <anchorfile>classRythmos_1_1BackwardEulerStepper.html</anchorfile>
      <anchor>a05293b32b7279b2c70d2b97b184dbfc3</anchor>
      <arglist>(const RCP&lt; Thyra::NonlinearSolverBase&lt; Scalar &gt; &gt; &amp;solver)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; Thyra::NonlinearSolverBase&lt; Scalar &gt; &gt;</type>
      <name>getNonconstSolver</name>
      <anchorfile>classRythmos_1_1BackwardEulerStepper.html</anchorfile>
      <anchor>a9d27b42a2b79f20dfcfd06e7e6eae7af</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const Thyra::NonlinearSolverBase&lt; Scalar &gt; &gt;</type>
      <name>getSolver</name>
      <anchorfile>classRythmos_1_1BackwardEulerStepper.html</anchorfile>
      <anchor>a85ae863a502c02e96a2bc89f824b08f8</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>supportsCloning</name>
      <anchorfile>classRythmos_1_1BackwardEulerStepper.html</anchorfile>
      <anchor>a670b3707ec068930dafe557d904408cf</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; StepperBase&lt; Scalar &gt; &gt;</type>
      <name>cloneStepperAlgorithm</name>
      <anchorfile>classRythmos_1_1BackwardEulerStepper.html</anchorfile>
      <anchor>aa62eee6c89f4e91d6d019da655f2215e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isImplicit</name>
      <anchorfile>classRythmos_1_1BackwardEulerStepper.html</anchorfile>
      <anchor>a95efa8a58b87c768ce0035db9789960f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setModel</name>
      <anchorfile>classRythmos_1_1BackwardEulerStepper.html</anchorfile>
      <anchor>a6cb49342acc663c7018513a0c879ec55</anchor>
      <arglist>(const RCP&lt; const Thyra::ModelEvaluator&lt; Scalar &gt; &gt; &amp;model)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setNonconstModel</name>
      <anchorfile>classRythmos_1_1BackwardEulerStepper.html</anchorfile>
      <anchor>a51b3841bcbcd1d6d510baa819aca7659</anchor>
      <arglist>(const RCP&lt; Thyra::ModelEvaluator&lt; Scalar &gt; &gt; &amp;model)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const Thyra::ModelEvaluator&lt; Scalar &gt; &gt;</type>
      <name>getModel</name>
      <anchorfile>classRythmos_1_1BackwardEulerStepper.html</anchorfile>
      <anchor>ae77adf3c20e2236ebc5021fd1e976a53</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; Thyra::ModelEvaluator&lt; Scalar &gt; &gt;</type>
      <name>getNonconstModel</name>
      <anchorfile>classRythmos_1_1BackwardEulerStepper.html</anchorfile>
      <anchor>ab2d5ca0e46da19259eccabdf11f4dfec</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setInitialCondition</name>
      <anchorfile>classRythmos_1_1BackwardEulerStepper.html</anchorfile>
      <anchor>aa397c49e95e3d7a2cbc132dea728d447</anchor>
      <arglist>(const Thyra::ModelEvaluatorBase::InArgs&lt; Scalar &gt; &amp;initialCondition)</arglist>
    </member>
    <member kind="function">
      <type>Thyra::ModelEvaluatorBase::InArgs&lt; Scalar &gt;</type>
      <name>getInitialCondition</name>
      <anchorfile>classRythmos_1_1BackwardEulerStepper.html</anchorfile>
      <anchor>a8dad2fbce26e167406ecac8bca0ccbf4</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Scalar</type>
      <name>takeStep</name>
      <anchorfile>classRythmos_1_1BackwardEulerStepper.html</anchorfile>
      <anchor>a86eba53381e15c235d194264c758ac4e</anchor>
      <arglist>(Scalar dt, StepSizeType flag)</arglist>
    </member>
    <member kind="function">
      <type>const StepStatus&lt; Scalar &gt;</type>
      <name>getStepStatus</name>
      <anchorfile>classRythmos_1_1BackwardEulerStepper.html</anchorfile>
      <anchor>a52e9d6591ee1a2e62ad8a94efd589bd0</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const Thyra::VectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>get_x_space</name>
      <anchorfile>classRythmos_1_1BackwardEulerStepper.html</anchorfile>
      <anchor>a38a75d9cb0ba19655546e8d36a6e135e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>addPoints</name>
      <anchorfile>classRythmos_1_1BackwardEulerStepper.html</anchorfile>
      <anchor>af099acdfd90a18eec079b4ecb0180b7a</anchor>
      <arglist>(const Array&lt; Scalar &gt; &amp;time_vec, const Array&lt; RCP&lt; const Thyra::VectorBase&lt; Scalar &gt; &gt; &gt; &amp;x_vec, const Array&lt; RCP&lt; const Thyra::VectorBase&lt; Scalar &gt; &gt; &gt; &amp;xdot_vec)</arglist>
    </member>
    <member kind="function">
      <type>TimeRange&lt; Scalar &gt;</type>
      <name>getTimeRange</name>
      <anchorfile>classRythmos_1_1BackwardEulerStepper.html</anchorfile>
      <anchor>a4cf967e41f3dbf19a62bbed6ca61b1b2</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>getPoints</name>
      <anchorfile>classRythmos_1_1BackwardEulerStepper.html</anchorfile>
      <anchor>a04dc6f7ab0ee731099638e685db7bf7c</anchor>
      <arglist>(const Array&lt; Scalar &gt; &amp;time_vec, Array&lt; RCP&lt; const Thyra::VectorBase&lt; Scalar &gt; &gt; &gt; *x_vec, Array&lt; RCP&lt; const Thyra::VectorBase&lt; Scalar &gt; &gt; &gt; *xdot_vec, Array&lt; ScalarMag &gt; *accuracy_vec) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>getNodes</name>
      <anchorfile>classRythmos_1_1BackwardEulerStepper.html</anchorfile>
      <anchor>a086678b847ed4e6be3906db1c60cf06e</anchor>
      <arglist>(Array&lt; Scalar &gt; *time_vec) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>removeNodes</name>
      <anchorfile>classRythmos_1_1BackwardEulerStepper.html</anchorfile>
      <anchor>a58d7876fa6dff7fcdb84472aa4b6bd7f</anchor>
      <arglist>(Array&lt; Scalar &gt; &amp;time_vec)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getOrder</name>
      <anchorfile>classRythmos_1_1BackwardEulerStepper.html</anchorfile>
      <anchor>ae2a31e9365fec6d7ce951036fdbd8f4f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setParameterList</name>
      <anchorfile>classRythmos_1_1BackwardEulerStepper.html</anchorfile>
      <anchor>ae46535998f9711d56043aba62d0c1f8a</anchor>
      <arglist>(RCP&lt; Teuchos::ParameterList &gt; const &amp;paramList)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; Teuchos::ParameterList &gt;</type>
      <name>getNonconstParameterList</name>
      <anchorfile>classRythmos_1_1BackwardEulerStepper.html</anchorfile>
      <anchor>a3204a6475e975cbe27e4aed03ef76cd9</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; Teuchos::ParameterList &gt;</type>
      <name>unsetParameterList</name>
      <anchorfile>classRythmos_1_1BackwardEulerStepper.html</anchorfile>
      <anchor>a9fc979e0b8b1f5ce3d8ffca96542d201</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const Teuchos::ParameterList &gt;</type>
      <name>getValidParameters</name>
      <anchorfile>classRythmos_1_1BackwardEulerStepper.html</anchorfile>
      <anchor>ad1afaff0c91deb68dd88efae425ebd4c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>describe</name>
      <anchorfile>classRythmos_1_1BackwardEulerStepper.html</anchorfile>
      <anchor>afd09a7b46188d4b8660ce8773d40d5ff</anchor>
      <arglist>(Teuchos::FancyOStream &amp;out, const Teuchos::EVerbosityLevel verbLevel) const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const MomentoBase&lt; Scalar &gt; &gt;</type>
      <name>getMomento</name>
      <anchorfile>classRythmos_1_1BackwardEulerStepper.html</anchorfile>
      <anchor>a07ed7908c9fd41d042b1b3d3b7cf0458</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setMomento</name>
      <anchorfile>classRythmos_1_1BackwardEulerStepper.html</anchorfile>
      <anchor>ac2a84268281b159ead2277f70a60a312</anchor>
      <arglist>(const Ptr&lt; const MomentoBase&lt; Scalar &gt; &gt; &amp;momentoPtr, const RCP&lt; Thyra::ModelEvaluator&lt; Scalar &gt; &gt; &amp;model, const RCP&lt; Thyra::NonlinearSolverBase&lt; Scalar &gt; &gt; &amp;solver)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Rythmos::BackwardEulerStepperMomento</name>
    <filename>classRythmos_1_1BackwardEulerStepperMomento.html</filename>
    <templarg></templarg>
    <base virtualness="virtual">Rythmos::MomentoBase</base>
  </compound>
  <compound kind="class">
    <name>Rythmos::BasicDiscreteAdjointStepperTester</name>
    <filename>classRythmos_1_1BasicDiscreteAdjointStepperTester.html</filename>
    <templarg></templarg>
    <member kind="function">
      <type>RCP&lt; BasicDiscreteAdjointStepperTester&lt; Scalar &gt; &gt;</type>
      <name>basicDiscreteAdjointStepperTester</name>
      <anchorfile>classRythmos_1_1BasicDiscreteAdjointStepperTester.html</anchorfile>
      <anchor>a98ed23c14af654b177532e589a4e5d89</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; BasicDiscreteAdjointStepperTester&lt; Scalar &gt; &gt;</type>
      <name>basicDiscreteAdjointStepperTester</name>
      <anchorfile>classRythmos_1_1BasicDiscreteAdjointStepperTester.html</anchorfile>
      <anchor>a8056dd162fe25e57c4d9bde9b19c4449</anchor>
      <arglist>(const RCP&lt; ParameterList &gt; &amp;paramList)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setParameterList</name>
      <anchorfile>classRythmos_1_1BasicDiscreteAdjointStepperTester.html</anchorfile>
      <anchor>a5c3e3d4c5dbe0e5be8eba8e38bf8a53a</anchor>
      <arglist>(RCP&lt; ParameterList &gt; const &amp;paramList)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const ParameterList &gt;</type>
      <name>getValidParameters</name>
      <anchorfile>classRythmos_1_1BasicDiscreteAdjointStepperTester.html</anchorfile>
      <anchor>a2c04c206aead0714a7abd72675e4a37d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>testAdjointStepper</name>
      <anchorfile>classRythmos_1_1BasicDiscreteAdjointStepperTester.html</anchorfile>
      <anchor>a4755d7c990e179c92d00efa7119d7ae4</anchor>
      <arglist>(Thyra::ModelEvaluator&lt; Scalar &gt; &amp;adjointModel, const Ptr&lt; IntegratorBase&lt; Scalar &gt; &gt; &amp;forwardIntegrator)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Rythmos::BreakPointInformerBase</name>
    <filename>classRythmos_1_1BreakPointInformerBase.html</filename>
    <templarg></templarg>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>testForBreakPoint</name>
      <anchorfile>classRythmos_1_1BreakPointInformerBase.html</anchorfile>
      <anchor>a74a4274a5148b01fcce1c493d4d99da9</anchor>
      <arglist>(Scalar &amp;time0, Scalar &amp;dt) const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual Scalar</type>
      <name>getNextBreakPoint</name>
      <anchorfile>classRythmos_1_1BreakPointInformerBase.html</anchorfile>
      <anchor>ab64ce530ef2e5e12f3c11d021436f192</anchor>
      <arglist>(Scalar &amp;time0) const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>removeNextBreakPoint</name>
      <anchorfile>classRythmos_1_1BreakPointInformerBase.html</anchorfile>
      <anchor>a12457d53eda91fc3396f8d529bfe51bf</anchor>
      <arglist>(Scalar &amp;time0)=0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Rythmos::CompositeIntegrationObserver</name>
    <filename>classRythmos_1_1CompositeIntegrationObserver.html</filename>
    <templarg></templarg>
    <base>Rythmos::IntegrationObserverBase</base>
    <member kind="function">
      <type>RCP&lt; CompositeIntegrationObserver&lt; Scalar &gt; &gt;</type>
      <name>createCompositeIntegrationObserver</name>
      <anchorfile>classRythmos_1_1CompositeIntegrationObserver.html</anchorfile>
      <anchor>a4799583431725becbdef94108997448c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>CompositeIntegrationObserver</name>
      <anchorfile>classRythmos_1_1CompositeIntegrationObserver.html</anchorfile>
      <anchor>a3bf32943976f303653dc8c4c4430b63e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>addObserver</name>
      <anchorfile>classRythmos_1_1CompositeIntegrationObserver.html</anchorfile>
      <anchor>ad8c37aefcfeed4c60448418ad2e70884</anchor>
      <arglist>(const RCP&lt; IntegrationObserverBase&lt; Scalar &gt; &gt; &amp;observer)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual RCP&lt; IntegrationObserverBase&lt; Scalar &gt; &gt;</type>
      <name>cloneIntegrationObserver</name>
      <anchorfile>classRythmos_1_1CompositeIntegrationObserver.html</anchorfile>
      <anchor>a7fa0d3fa5def3679e9511a582a4e02d0</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>resetIntegrationObserver</name>
      <anchorfile>classRythmos_1_1CompositeIntegrationObserver.html</anchorfile>
      <anchor>a4a5b9206942dc118fca18e11d8f64168</anchor>
      <arglist>(const TimeRange&lt; Scalar &gt; &amp;integrationTimeDomain)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>observeStartTimeIntegration</name>
      <anchorfile>classRythmos_1_1CompositeIntegrationObserver.html</anchorfile>
      <anchor>a9ef89807cbbd067793ad6a68c810be52</anchor>
      <arglist>(const StepperBase&lt; Scalar &gt; &amp;stepper)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>observeEndTimeIntegration</name>
      <anchorfile>classRythmos_1_1CompositeIntegrationObserver.html</anchorfile>
      <anchor>a8928cc5465edd1f590eee0437c191e6b</anchor>
      <arglist>(const StepperBase&lt; Scalar &gt; &amp;stepper)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>observeStartTimeStep</name>
      <anchorfile>classRythmos_1_1CompositeIntegrationObserver.html</anchorfile>
      <anchor>a636ec249d917668674d33fd5e903e189</anchor>
      <arglist>(const StepperBase&lt; Scalar &gt; &amp;stepper, const StepControlInfo&lt; Scalar &gt; &amp;stepCtrlInfo, const int timeStepIter)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>observeCompletedTimeStep</name>
      <anchorfile>classRythmos_1_1CompositeIntegrationObserver.html</anchorfile>
      <anchor>a0b231e39811947928445f79fa4b4dd98</anchor>
      <arglist>(const StepperBase&lt; Scalar &gt; &amp;stepper, const StepControlInfo&lt; Scalar &gt; &amp;stepCtrlInfo, const int timeStepIter)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>observeFailedTimeStep</name>
      <anchorfile>classRythmos_1_1CompositeIntegrationObserver.html</anchorfile>
      <anchor>aa629aa3b1fac01944d6744289a5db524</anchor>
      <arglist>(const StepperBase&lt; Scalar &gt; &amp;stepper, const StepControlInfo&lt; Scalar &gt; &amp;stepCtrlInfo, const int timeStepIter)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Rythmos::CubicSplineInterpolator</name>
    <filename>classRythmos_1_1CubicSplineInterpolator.html</filename>
    <templarg></templarg>
    <base virtualness="virtual">Rythmos::InterpolatorBase</base>
    <member kind="function">
      <type></type>
      <name>~CubicSplineInterpolator</name>
      <anchorfile>classRythmos_1_1CubicSplineInterpolator.html</anchorfile>
      <anchor>a519c0c52e9d1db36a58121647ad739d4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>CubicSplineInterpolator</name>
      <anchorfile>classRythmos_1_1CubicSplineInterpolator.html</anchorfile>
      <anchor>ad1221757c5d4789c50d924b84bc1fb9c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>supportsCloning</name>
      <anchorfile>classRythmos_1_1CubicSplineInterpolator.html</anchorfile>
      <anchor>afa227bb2b0cc327c9fe136f3f15d5885</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; InterpolatorBase&lt; Scalar &gt; &gt;</type>
      <name>cloneInterpolator</name>
      <anchorfile>classRythmos_1_1CubicSplineInterpolator.html</anchorfile>
      <anchor>a0c88bc3d364d2a9d60c0fa68e68a3d86</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setNodes</name>
      <anchorfile>classRythmos_1_1CubicSplineInterpolator.html</anchorfile>
      <anchor>aac8efe247112e1a78c9bc037ff889f38</anchor>
      <arglist>(const RCP&lt; const typename DataStore&lt; Scalar &gt;::DataStoreVector_t &gt; &amp;nodes)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>interpolate</name>
      <anchorfile>classRythmos_1_1CubicSplineInterpolator.html</anchorfile>
      <anchor>aaf21e3d9147e5b7c973d68d3269c6013</anchor>
      <arglist>(const Array&lt; Scalar &gt; &amp;t_values, typename DataStore&lt; Scalar &gt;::DataStoreVector_t *data_out) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>order</name>
      <anchorfile>classRythmos_1_1CubicSplineInterpolator.html</anchorfile>
      <anchor>acdff96d51306452e3575f891558f04ef</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>description</name>
      <anchorfile>classRythmos_1_1CubicSplineInterpolator.html</anchorfile>
      <anchor>a41d17f85195031c7e225367b12fd8036</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>describe</name>
      <anchorfile>classRythmos_1_1CubicSplineInterpolator.html</anchorfile>
      <anchor>ad2ff07c9a9896ac652c554bd1fc5434d</anchor>
      <arglist>(FancyOStream &amp;out, const Teuchos::EVerbosityLevel verbLevel) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setParameterList</name>
      <anchorfile>classRythmos_1_1CubicSplineInterpolator.html</anchorfile>
      <anchor>a2d68aaa4fd619046c0aa39b31d5a42f6</anchor>
      <arglist>(RCP&lt; ParameterList &gt; const &amp;paramList)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; ParameterList &gt;</type>
      <name>getNonconstParameterList</name>
      <anchorfile>classRythmos_1_1CubicSplineInterpolator.html</anchorfile>
      <anchor>ace65b3618d0ed403e561313498291ea8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; ParameterList &gt;</type>
      <name>unsetParameterList</name>
      <anchorfile>classRythmos_1_1CubicSplineInterpolator.html</anchorfile>
      <anchor>af21465b257c90fd878b0ec6ac765a9b4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const Teuchos::ParameterList &gt;</type>
      <name>getValidParameters</name>
      <anchorfile>classRythmos_1_1CubicSplineInterpolator.html</anchorfile>
      <anchor>a2364439bc43dc11449078e7764fb38c2</anchor>
      <arglist>() const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Rythmos::DefaultIntegrator</name>
    <filename>classRythmos_1_1DefaultIntegrator.html</filename>
    <templarg></templarg>
    <base virtualness="virtual">Rythmos::IntegrationControlStrategyAcceptingIntegratorBase</base>
    <base virtualness="virtual">Rythmos::InterpolationBufferAppenderAcceptingIntegratorBase</base>
    <base virtualness="virtual">Rythmos::TrailingInterpolationBufferAcceptingIntegratorBase</base>
    <member kind="typedef">
      <type>ScalarTraits&lt; Scalar &gt;::magnitudeType</type>
      <name>ScalarMag</name>
      <anchorfile>classRythmos_1_1DefaultIntegrator.html</anchorfile>
      <anchor>af9bd8be00b5bb8349811d806998d9a6d</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>getFwdPoints</name>
      <anchorfile>classRythmos_1_1DefaultIntegrator.html</anchorfile>
      <anchor>ab090d33dc3f4fca896c49231a5a417f1</anchor>
      <arglist>(const Array&lt; Scalar &gt; &amp;time_vec, Array&lt; RCP&lt; const Thyra::VectorBase&lt; Scalar &gt; &gt; &gt; *x_vec, Array&lt; RCP&lt; const Thyra::VectorBase&lt; Scalar &gt; &gt; &gt; *xdot_vec, Array&lt; ScalarMag &gt; *accuracy_vec)</arglist>
    </member>
    <member kind="function">
      <type>TimeRange&lt; Scalar &gt;</type>
      <name>getFwdTimeRange</name>
      <anchorfile>classRythmos_1_1DefaultIntegrator.html</anchorfile>
      <anchor>a6036929a15dc30727f7e175f41f95a60</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; DefaultIntegrator&lt; Scalar &gt; &gt;</type>
      <name>defaultIntegrator</name>
      <anchorfile>classRythmos_1_1DefaultIntegrator.html</anchorfile>
      <anchor>a8190f17d816bcf5e8b01a67836ef4c8b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; DefaultIntegrator&lt; Scalar &gt; &gt;</type>
      <name>defaultIntegrator</name>
      <anchorfile>classRythmos_1_1DefaultIntegrator.html</anchorfile>
      <anchor>a0851e4f7ecfa770550cc057972ad920f</anchor>
      <arglist>(const RCP&lt; IntegrationControlStrategyBase&lt; Scalar &gt; &gt; &amp;integrationControlStrategy, const RCP&lt; IntegrationObserverBase&lt; Scalar &gt; &gt; &amp;integrationObserver)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; DefaultIntegrator&lt; Scalar &gt; &gt;</type>
      <name>controlledDefaultIntegrator</name>
      <anchorfile>classRythmos_1_1DefaultIntegrator.html</anchorfile>
      <anchor>af2c850f073e1f7ad67cd275b4bd3b7a0</anchor>
      <arglist>(const RCP&lt; IntegrationControlStrategyBase&lt; Scalar &gt; &gt; &amp;integrationControlStrategy)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; DefaultIntegrator&lt; Scalar &gt; &gt;</type>
      <name>observedDefaultIntegrator</name>
      <anchorfile>classRythmos_1_1DefaultIntegrator.html</anchorfile>
      <anchor>ab13aa7d0e71ec80ec126344282d74b3d</anchor>
      <arglist>(const RCP&lt; IntegrationObserverBase&lt; Scalar &gt; &gt; &amp;integrationObserver)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; DefaultIntegrator&lt; Scalar &gt; &gt;</type>
      <name>defaultIntegrator</name>
      <anchorfile>classRythmos_1_1DefaultIntegrator.html</anchorfile>
      <anchor>a8190f17d816bcf5e8b01a67836ef4c8b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; DefaultIntegrator&lt; Scalar &gt; &gt;</type>
      <name>defaultIntegrator</name>
      <anchorfile>classRythmos_1_1DefaultIntegrator.html</anchorfile>
      <anchor>a0851e4f7ecfa770550cc057972ad920f</anchor>
      <arglist>(const RCP&lt; IntegrationControlStrategyBase&lt; Scalar &gt; &gt; &amp;integrationControlStrategy, const RCP&lt; IntegrationObserverBase&lt; Scalar &gt; &gt; &amp;integrationObserver)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; DefaultIntegrator&lt; Scalar &gt; &gt;</type>
      <name>controlledDefaultIntegrator</name>
      <anchorfile>classRythmos_1_1DefaultIntegrator.html</anchorfile>
      <anchor>af2c850f073e1f7ad67cd275b4bd3b7a0</anchor>
      <arglist>(const RCP&lt; IntegrationControlStrategyBase&lt; Scalar &gt; &gt; &amp;integrationControlStrategy)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; DefaultIntegrator&lt; Scalar &gt; &gt;</type>
      <name>observedDefaultIntegrator</name>
      <anchorfile>classRythmos_1_1DefaultIntegrator.html</anchorfile>
      <anchor>ab13aa7d0e71ec80ec126344282d74b3d</anchor>
      <arglist>(const RCP&lt; IntegrationObserverBase&lt; Scalar &gt; &gt; &amp;integrationObserver)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>DefaultIntegrator</name>
      <anchorfile>classRythmos_1_1DefaultIntegrator.html</anchorfile>
      <anchor>a7aba937624e7c5102d1498eccd361c89</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setIntegrationObserver</name>
      <anchorfile>classRythmos_1_1DefaultIntegrator.html</anchorfile>
      <anchor>ab34fe705bfbbbcd1826782ac91afc9ae</anchor>
      <arglist>(const RCP&lt; IntegrationObserverBase&lt; Scalar &gt; &gt; &amp;integrationObserver)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setInterpolationBufferAppender</name>
      <anchorfile>classRythmos_1_1DefaultIntegrator.html</anchorfile>
      <anchor>ab98bb461ca09b6b0845af60f400819d6</anchor>
      <arglist>(const RCP&lt; InterpolationBufferAppenderBase&lt; Scalar &gt; &gt; &amp;interpBufferAppender)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const InterpolationBufferAppenderBase&lt; Scalar &gt; &gt;</type>
      <name>getInterpolationBufferAppender</name>
      <anchorfile>classRythmos_1_1DefaultIntegrator.html</anchorfile>
      <anchor>ac9f2ba7012e938ccb6c79a3b90a4cb75</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; InterpolationBufferAppenderBase&lt; Scalar &gt; &gt;</type>
      <name>getNonconstInterpolationBufferAppender</name>
      <anchorfile>classRythmos_1_1DefaultIntegrator.html</anchorfile>
      <anchor>a4aad6bf8932e9e20cf6cdef2ad695013</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; InterpolationBufferAppenderBase&lt; Scalar &gt; &gt;</type>
      <name>unSetInterpolationBufferAppender</name>
      <anchorfile>classRythmos_1_1DefaultIntegrator.html</anchorfile>
      <anchor>aefc92c8551196ba62ba26a6451f5ea6f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setIntegrationControlStrategy</name>
      <anchorfile>classRythmos_1_1DefaultIntegrator.html</anchorfile>
      <anchor>ad31937c2f996b594ff59a6ae97f293d1</anchor>
      <arglist>(const RCP&lt; IntegrationControlStrategyBase&lt; Scalar &gt; &gt; &amp;integrationControlStrategy)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; IntegrationControlStrategyBase&lt; Scalar &gt; &gt;</type>
      <name>getNonconstIntegrationControlStrategy</name>
      <anchorfile>classRythmos_1_1DefaultIntegrator.html</anchorfile>
      <anchor>adf16ac1b5dc31b6ecedcfa486b156f42</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const IntegrationControlStrategyBase&lt; Scalar &gt; &gt;</type>
      <name>getIntegrationControlStrategy</name>
      <anchorfile>classRythmos_1_1DefaultIntegrator.html</anchorfile>
      <anchor>aea62a25264be9f68cb7c5eb85c371b07</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setParameterList</name>
      <anchorfile>classRythmos_1_1DefaultIntegrator.html</anchorfile>
      <anchor>ad8bf5c62f1dffe806a516fb87d001471</anchor>
      <arglist>(RCP&lt; ParameterList &gt; const &amp;paramList)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const ParameterList &gt;</type>
      <name>getValidParameters</name>
      <anchorfile>classRythmos_1_1DefaultIntegrator.html</anchorfile>
      <anchor>ab9236cd938589d4e54e58f049140e26b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; IntegratorBase&lt; Scalar &gt; &gt;</type>
      <name>cloneIntegrator</name>
      <anchorfile>classRythmos_1_1DefaultIntegrator.html</anchorfile>
      <anchor>aab94e0d0b9f63f750ad36d147e24c753</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setStepper</name>
      <anchorfile>classRythmos_1_1DefaultIntegrator.html</anchorfile>
      <anchor>a26d0d0077cd92781c71403361f90b7a1</anchor>
      <arglist>(const RCP&lt; StepperBase&lt; Scalar &gt; &gt; &amp;stepper, const Scalar &amp;finalTime, const bool landOnFinalTime=true)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; StepperBase&lt; Scalar &gt; &gt;</type>
      <name>unSetStepper</name>
      <anchorfile>classRythmos_1_1DefaultIntegrator.html</anchorfile>
      <anchor>a98a8082ed5721c348746b85c130e97fe</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const StepperBase&lt; Scalar &gt; &gt;</type>
      <name>getStepper</name>
      <anchorfile>classRythmos_1_1DefaultIntegrator.html</anchorfile>
      <anchor>a745fa6b336d7d9a04571177b258d66f9</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; StepperBase&lt; Scalar &gt; &gt;</type>
      <name>getNonconstStepper</name>
      <anchorfile>classRythmos_1_1DefaultIntegrator.html</anchorfile>
      <anchor>a73b6944e0984c0e5ea487df84c613a37</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setTrailingInterpolationBuffer</name>
      <anchorfile>classRythmos_1_1DefaultIntegrator.html</anchorfile>
      <anchor>a66a3da5b258b168f193f542aaebf27a0</anchor>
      <arglist>(const RCP&lt; InterpolationBufferBase&lt; Scalar &gt; &gt; &amp;trailingInterpBuffer)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; InterpolationBufferBase&lt; Scalar &gt; &gt;</type>
      <name>getNonconstTrailingInterpolationBuffer</name>
      <anchorfile>classRythmos_1_1DefaultIntegrator.html</anchorfile>
      <anchor>a3013c229c7bc23c7e75f473dd6add026</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const InterpolationBufferBase&lt; Scalar &gt; &gt;</type>
      <name>getTrailingInterpolationBuffer</name>
      <anchorfile>classRythmos_1_1DefaultIntegrator.html</anchorfile>
      <anchor>a998aaa68e3f8f6002747036a11d11554</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; InterpolationBufferBase&lt; Scalar &gt; &gt;</type>
      <name>unSetTrailingInterpolationBuffer</name>
      <anchorfile>classRythmos_1_1DefaultIntegrator.html</anchorfile>
      <anchor>addc339048bb47414903c23587fb0ba6c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const Thyra::VectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>get_x_space</name>
      <anchorfile>classRythmos_1_1DefaultIntegrator.html</anchorfile>
      <anchor>a521951ae61c6909f45df6921aaa4d85c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>addPoints</name>
      <anchorfile>classRythmos_1_1DefaultIntegrator.html</anchorfile>
      <anchor>a985b0f9bd6626053f797b7dc62121561</anchor>
      <arglist>(const Array&lt; Scalar &gt; &amp;time_vec, const Array&lt; RCP&lt; const Thyra::VectorBase&lt; Scalar &gt; &gt; &gt; &amp;x_vec, const Array&lt; RCP&lt; const Thyra::VectorBase&lt; Scalar &gt; &gt; &gt; &amp;xdot_vec)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>getPoints</name>
      <anchorfile>classRythmos_1_1DefaultIntegrator.html</anchorfile>
      <anchor>ae63cce197386f8fa1a007d5e79e64121</anchor>
      <arglist>(const Array&lt; Scalar &gt; &amp;time_vec, Array&lt; RCP&lt; const Thyra::VectorBase&lt; Scalar &gt; &gt; &gt; *x_vec, Array&lt; RCP&lt; const Thyra::VectorBase&lt; Scalar &gt; &gt; &gt; *xdot_vec, Array&lt; ScalarMag &gt; *accuracy_vec) const </arglist>
    </member>
    <member kind="function">
      <type>TimeRange&lt; Scalar &gt;</type>
      <name>getTimeRange</name>
      <anchorfile>classRythmos_1_1DefaultIntegrator.html</anchorfile>
      <anchor>aef0f9fdc1220070d9bc2e9d689b9c6a1</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>getNodes</name>
      <anchorfile>classRythmos_1_1DefaultIntegrator.html</anchorfile>
      <anchor>a70f9f6e2fc1d20d4c11e86524db8875c</anchor>
      <arglist>(Array&lt; Scalar &gt; *time_vec) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>removeNodes</name>
      <anchorfile>classRythmos_1_1DefaultIntegrator.html</anchorfile>
      <anchor>a5d59acf45175d77753836a4558f09c41</anchor>
      <arglist>(Array&lt; Scalar &gt; &amp;time_vec)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getOrder</name>
      <anchorfile>classRythmos_1_1DefaultIntegrator.html</anchorfile>
      <anchor>a7bdb850aa4a7df790430e96d002817a8</anchor>
      <arglist>() const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Rythmos::DiagonalImplicitRKModelEvaluator</name>
    <filename>classRythmos_1_1DiagonalImplicitRKModelEvaluator.html</filename>
    <templarg></templarg>
    <member kind="function">
      <type>RCP&lt; DiagonalImplicitRKModelEvaluator&lt; Scalar &gt; &gt;</type>
      <name>diagonalImplicitRKModelEvaluator</name>
      <anchorfile>classRythmos_1_1DiagonalImplicitRKModelEvaluator.html</anchorfile>
      <anchor>a0925867e3c387a820178300b1ce23f1e</anchor>
      <arglist>(const RCP&lt; const Thyra::ModelEvaluator&lt; Scalar &gt; &gt; &amp;daeModel, const Thyra::ModelEvaluatorBase::InArgs&lt; Scalar &gt; &amp;basePoint, const RCP&lt; Thyra::LinearOpWithSolveFactoryBase&lt; Scalar &gt; &gt; &amp;dirk_W_factory, const RCP&lt; const RKButcherTableauBase&lt; Scalar &gt; &gt; &amp;irkButcherTableau)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>DiagonalImplicitRKModelEvaluator</name>
      <anchorfile>classRythmos_1_1DiagonalImplicitRKModelEvaluator.html</anchorfile>
      <anchor>a316e366f4cf36601466f2049ae3b9299</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initializeDIRKModel</name>
      <anchorfile>classRythmos_1_1DiagonalImplicitRKModelEvaluator.html</anchorfile>
      <anchor>aec175cdce6decd92e2fa4978082e1377</anchor>
      <arglist>(const RCP&lt; const Thyra::ModelEvaluator&lt; Scalar &gt; &gt; &amp;daeModel, const Thyra::ModelEvaluatorBase::InArgs&lt; Scalar &gt; &amp;basePoint, const RCP&lt; Thyra::LinearOpWithSolveFactoryBase&lt; Scalar &gt; &gt; &amp;dirk_W_factory, const RCP&lt; const RKButcherTableauBase&lt; Scalar &gt; &gt; &amp;irkButcherTableau)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setTimeStepPoint</name>
      <anchorfile>classRythmos_1_1DiagonalImplicitRKModelEvaluator.html</anchorfile>
      <anchor>a4539a934464c4928824b87cd6a4456fc</anchor>
      <arglist>(const RCP&lt; const Thyra::VectorBase&lt; Scalar &gt; &gt; &amp;x_old, const Scalar &amp;t_old, const Scalar &amp;delta_t)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setStageSolution</name>
      <anchorfile>classRythmos_1_1DiagonalImplicitRKModelEvaluator.html</anchorfile>
      <anchor>a88c58485ffdee32e71817a3d3f649551</anchor>
      <arglist>(int stageNumber, const Thyra::VectorBase&lt; Scalar &gt; &amp;stage_solution)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setCurrentStage</name>
      <anchorfile>classRythmos_1_1DiagonalImplicitRKModelEvaluator.html</anchorfile>
      <anchor>aa1a575a3ef0fba826504b79f9a8e5ad7</anchor>
      <arglist>(int currentStage)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const Thyra::VectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>get_x_space</name>
      <anchorfile>classRythmos_1_1DiagonalImplicitRKModelEvaluator.html</anchorfile>
      <anchor>ad990a871b35d5bc24a3cf42aa2ced0ae</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const Thyra::VectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>get_f_space</name>
      <anchorfile>classRythmos_1_1DiagonalImplicitRKModelEvaluator.html</anchorfile>
      <anchor>a169a0f8398a154c1beb52b86de57e7b6</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; Thyra::LinearOpBase&lt; Scalar &gt; &gt;</type>
      <name>create_W_op</name>
      <anchorfile>classRythmos_1_1DiagonalImplicitRKModelEvaluator.html</anchorfile>
      <anchor>abf0519f39af5f0f49fc3e87e728e0740</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const Thyra::LinearOpWithSolveFactoryBase&lt; Scalar &gt; &gt;</type>
      <name>get_W_factory</name>
      <anchorfile>classRythmos_1_1DiagonalImplicitRKModelEvaluator.html</anchorfile>
      <anchor>a168348126a46fb2a8e2e49d655232ad3</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Thyra::ModelEvaluatorBase::InArgs&lt; Scalar &gt;</type>
      <name>getNominalValues</name>
      <anchorfile>classRythmos_1_1DiagonalImplicitRKModelEvaluator.html</anchorfile>
      <anchor>a8b93dcd934aa33d34ed04d8acd5697e3</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Thyra::ModelEvaluatorBase::InArgs&lt; Scalar &gt;</type>
      <name>createInArgs</name>
      <anchorfile>classRythmos_1_1DiagonalImplicitRKModelEvaluator.html</anchorfile>
      <anchor>ac7ba0e2f91617fb462c58ae7cf4ec640</anchor>
      <arglist>() const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>EpetraExt::DiagonalTransientModel</name>
    <filename>classEpetraExt_1_1DiagonalTransientModel.html</filename>
    <member kind="function">
      <type>Teuchos::RCP&lt; DiagonalTransientModel &gt;</type>
      <name>diagonalTransientModel</name>
      <anchorfile>classEpetraExt_1_1DiagonalTransientModel.html</anchorfile>
      <anchor>a207146564548c043b318df5f0f49a624</anchor>
      <arglist>(Teuchos::RCP&lt; Epetra_Comm &gt; const &amp;epetra_comm, Teuchos::RCP&lt; Teuchos::ParameterList &gt; const &amp;paramList=Teuchos::null)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>DiagonalTransientModel</name>
      <anchorfile>classEpetraExt_1_1DiagonalTransientModel.html</anchorfile>
      <anchor>adc06cd6db5e412aa21a488da24a397b6</anchor>
      <arglist>(Teuchos::RCP&lt; Epetra_Comm &gt; const &amp;epetra_comm)</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Epetra_Vector &gt;</type>
      <name>get_gamma</name>
      <anchorfile>classEpetraExt_1_1DiagonalTransientModel.html</anchorfile>
      <anchor>a0233f648f7da041945ccf4abea72fcc7</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Epetra_Vector &gt;</type>
      <name>getExactSolution</name>
      <anchorfile>classEpetraExt_1_1DiagonalTransientModel.html</anchorfile>
      <anchor>ad3e52df15b45e5b2cf90be5c465e6220</anchor>
      <arglist>(const double t, const Epetra_Vector *coeff_s_p=0) const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Epetra_MultiVector &gt;</type>
      <name>getExactSensSolution</name>
      <anchorfile>classEpetraExt_1_1DiagonalTransientModel.html</anchorfile>
      <anchor>a825638f602a851c16b80874f95c34fba</anchor>
      <arglist>(const double t, const Epetra_Vector *coeff_s_p=0) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setParameterList</name>
      <anchorfile>classEpetraExt_1_1DiagonalTransientModel.html</anchorfile>
      <anchor>a7c76ddcaf74895c09db19dab71a0e616</anchor>
      <arglist>(Teuchos::RCP&lt; Teuchos::ParameterList &gt; const &amp;paramList)</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; Teuchos::ParameterList &gt;</type>
      <name>getNonconstParameterList</name>
      <anchorfile>classEpetraExt_1_1DiagonalTransientModel.html</anchorfile>
      <anchor>a45038079bbb09dffd772e3d21ec6d4d0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; Teuchos::ParameterList &gt;</type>
      <name>unsetParameterList</name>
      <anchorfile>classEpetraExt_1_1DiagonalTransientModel.html</anchorfile>
      <anchor>a719f5ccbeb14ea40a2421be76982e642</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Teuchos::ParameterList &gt;</type>
      <name>getParameterList</name>
      <anchorfile>classEpetraExt_1_1DiagonalTransientModel.html</anchorfile>
      <anchor>aa33fdc2694cbe5d673dfe47094330ad5</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Teuchos::ParameterList &gt;</type>
      <name>getValidParameters</name>
      <anchorfile>classEpetraExt_1_1DiagonalTransientModel.html</anchorfile>
      <anchor>a35d87d8ac8e896011ffcc7d4fe0c58ea</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Epetra_Map &gt;</type>
      <name>get_x_map</name>
      <anchorfile>classEpetraExt_1_1DiagonalTransientModel.html</anchorfile>
      <anchor>ab8c284ba4d6113e3455be237fbc491b9</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Epetra_Map &gt;</type>
      <name>get_f_map</name>
      <anchorfile>classEpetraExt_1_1DiagonalTransientModel.html</anchorfile>
      <anchor>aa67ea10e28c4d45085eb7d74d0fe404b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Epetra_Map &gt;</type>
      <name>get_p_map</name>
      <anchorfile>classEpetraExt_1_1DiagonalTransientModel.html</anchorfile>
      <anchor>af87a6c4e25612098a392d978b09f9ab8</anchor>
      <arglist>(int l) const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Teuchos::Array&lt; std::string &gt; &gt;</type>
      <name>get_p_names</name>
      <anchorfile>classEpetraExt_1_1DiagonalTransientModel.html</anchorfile>
      <anchor>a711b087f3b8b457d563289a66dd636f2</anchor>
      <arglist>(int l) const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Epetra_Map &gt;</type>
      <name>get_g_map</name>
      <anchorfile>classEpetraExt_1_1DiagonalTransientModel.html</anchorfile>
      <anchor>a4798672f5b3867a87100bcbe7a838c56</anchor>
      <arglist>(int j) const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Epetra_Vector &gt;</type>
      <name>get_x_init</name>
      <anchorfile>classEpetraExt_1_1DiagonalTransientModel.html</anchorfile>
      <anchor>a7c99093001e62dc632d096c22c3284fd</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Epetra_Vector &gt;</type>
      <name>get_x_dot_init</name>
      <anchorfile>classEpetraExt_1_1DiagonalTransientModel.html</anchorfile>
      <anchor>a509957b58edddfb88e3ef76ff27ee518</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Epetra_Vector &gt;</type>
      <name>get_p_init</name>
      <anchorfile>classEpetraExt_1_1DiagonalTransientModel.html</anchorfile>
      <anchor>aeca5677b036d5175291401ab808dd710</anchor>
      <arglist>(int l) const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; Epetra_Operator &gt;</type>
      <name>create_W</name>
      <anchorfile>classEpetraExt_1_1DiagonalTransientModel.html</anchorfile>
      <anchor>a5c93f5a94d82758548536a4dd2cef346</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>InArgs</type>
      <name>createInArgs</name>
      <anchorfile>classEpetraExt_1_1DiagonalTransientModel.html</anchorfile>
      <anchor>a07409b477405c5ae33eca5b0da372393</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>OutArgs</type>
      <name>createOutArgs</name>
      <anchorfile>classEpetraExt_1_1DiagonalTransientModel.html</anchorfile>
      <anchor>aa5228e22b4ee7f3cfa22d8a5b1a41b16</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>evalModel</name>
      <anchorfile>classEpetraExt_1_1DiagonalTransientModel.html</anchorfile>
      <anchor>ada6e6a152027b29489c97efae978954d</anchor>
      <arglist>(const InArgs &amp;inArgs, const OutArgs &amp;outArgs) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Rythmos::ErrWtVecCalcAcceptingStepControlStrategyBase</name>
    <filename>classRythmos_1_1ErrWtVecCalcAcceptingStepControlStrategyBase.html</filename>
    <templarg></templarg>
    <base virtualness="virtual">Rythmos::StepControlStrategyBase</base>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>setErrWtVecCalc</name>
      <anchorfile>classRythmos_1_1ErrWtVecCalcAcceptingStepControlStrategyBase.html</anchorfile>
      <anchor>a684d90a3c1c5922db9df5fa82607c452</anchor>
      <arglist>(const RCP&lt; ErrWtVecCalcBase&lt; Scalar &gt; &gt; &amp;errWtVecCalc)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual RCP&lt; const ErrWtVecCalcBase&lt; Scalar &gt; &gt;</type>
      <name>getErrWtVecCalc</name>
      <anchorfile>classRythmos_1_1ErrWtVecCalcAcceptingStepControlStrategyBase.html</anchorfile>
      <anchor>ac983890059b968316315abf9303693a9</anchor>
      <arglist>() const  =0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Rythmos::Exceptions::ExceptionBase</name>
    <filename>classRythmos_1_1Exceptions_1_1ExceptionBase.html</filename>
  </compound>
  <compound kind="class">
    <name>Rythmos::ExplicitRKStepper</name>
    <filename>classRythmos_1_1ExplicitRKStepper.html</filename>
    <templarg></templarg>
    <base virtualness="virtual">Rythmos::RKButcherTableauAcceptingStepperBase</base>
    <base virtualness="virtual">Rythmos::StepControlStrategyAcceptingStepperBase</base>
    <member kind="function">
      <type></type>
      <name>ExplicitRKStepper</name>
      <anchorfile>classRythmos_1_1ExplicitRKStepper.html</anchorfile>
      <anchor>a94ab5f1c8e5814b9e6c26a88e227f405</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Thyra::VectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>get_x_space</name>
      <anchorfile>classRythmos_1_1ExplicitRKStepper.html</anchorfile>
      <anchor>af7ff21831f8d5562958962ef73e8d765</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setModel</name>
      <anchorfile>classRythmos_1_1ExplicitRKStepper.html</anchorfile>
      <anchor>a14f7716bffb2025d81df3a96c9448141</anchor>
      <arglist>(const Teuchos::RCP&lt; const Thyra::ModelEvaluator&lt; Scalar &gt; &gt; &amp;model)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setNonconstModel</name>
      <anchorfile>classRythmos_1_1ExplicitRKStepper.html</anchorfile>
      <anchor>a0820de23d05c46b17f383a259b73ebf8</anchor>
      <arglist>(const Teuchos::RCP&lt; Thyra::ModelEvaluator&lt; Scalar &gt; &gt; &amp;model)</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Thyra::ModelEvaluator&lt; Scalar &gt; &gt;</type>
      <name>getModel</name>
      <anchorfile>classRythmos_1_1ExplicitRKStepper.html</anchorfile>
      <anchor>a20d140a3326b2d785c4ca1b1d040c178</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; Thyra::ModelEvaluator&lt; Scalar &gt; &gt;</type>
      <name>getNonconstModel</name>
      <anchorfile>classRythmos_1_1ExplicitRKStepper.html</anchorfile>
      <anchor>aad539a3e9385ca8ebf1ae1090aacc03c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~ExplicitRKStepper</name>
      <anchorfile>classRythmos_1_1ExplicitRKStepper.html</anchorfile>
      <anchor>a1dea57b5c6f763e350f624d536fc9906</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setInitialCondition</name>
      <anchorfile>classRythmos_1_1ExplicitRKStepper.html</anchorfile>
      <anchor>adebb4e366ca93790e6b18b4c61d16b90</anchor>
      <arglist>(const Thyra::ModelEvaluatorBase::InArgs&lt; Scalar &gt; &amp;initialCondition)</arglist>
    </member>
    <member kind="function">
      <type>Thyra::ModelEvaluatorBase::InArgs&lt; Scalar &gt;</type>
      <name>getInitialCondition</name>
      <anchorfile>classRythmos_1_1ExplicitRKStepper.html</anchorfile>
      <anchor>a383ffcaffd3931e9ddddba17f0c27e50</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Scalar</type>
      <name>takeStep</name>
      <anchorfile>classRythmos_1_1ExplicitRKStepper.html</anchorfile>
      <anchor>ab6d00f45001bf9a7614190a9fc2f4065</anchor>
      <arglist>(Scalar dt, StepSizeType flag)</arglist>
    </member>
    <member kind="function">
      <type>const StepStatus&lt; Scalar &gt;</type>
      <name>getStepStatus</name>
      <anchorfile>classRythmos_1_1ExplicitRKStepper.html</anchorfile>
      <anchor>adca5fc3a43f4e5a15a9878ee469cc66e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>describe</name>
      <anchorfile>classRythmos_1_1ExplicitRKStepper.html</anchorfile>
      <anchor>a8012c2e7a9078b69dda14e2554a9e4e5</anchor>
      <arglist>(Teuchos::FancyOStream &amp;out, const Teuchos::EVerbosityLevel verbLevel) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>addPoints</name>
      <anchorfile>classRythmos_1_1ExplicitRKStepper.html</anchorfile>
      <anchor>ae1bfa5b12bd9b77eedebfccb1924598d</anchor>
      <arglist>(const Array&lt; Scalar &gt; &amp;time_vec, const Array&lt; Teuchos::RCP&lt; const Thyra::VectorBase&lt; Scalar &gt; &gt; &gt; &amp;x_vec, const Array&lt; Teuchos::RCP&lt; const Thyra::VectorBase&lt; Scalar &gt; &gt; &gt; &amp;xdot_vec)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>getPoints</name>
      <anchorfile>classRythmos_1_1ExplicitRKStepper.html</anchorfile>
      <anchor>ace2821a9c44059718ddb60b5c78aceed</anchor>
      <arglist>(const Array&lt; Scalar &gt; &amp;time_vec, Array&lt; RCP&lt; const VectorBase&lt; Scalar &gt; &gt; &gt; *x_vec, Array&lt; RCP&lt; const VectorBase&lt; Scalar &gt; &gt; &gt; *xdot_vec, Array&lt; ScalarMag &gt; *accuracy_vec) const </arglist>
    </member>
    <member kind="function">
      <type>TimeRange&lt; Scalar &gt;</type>
      <name>getTimeRange</name>
      <anchorfile>classRythmos_1_1ExplicitRKStepper.html</anchorfile>
      <anchor>a56f3527c6a48a94934cfa1f1c8b75223</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>getNodes</name>
      <anchorfile>classRythmos_1_1ExplicitRKStepper.html</anchorfile>
      <anchor>acdd24e96b1f623d1ada1b7e3d13c2633</anchor>
      <arglist>(Array&lt; Scalar &gt; *time_vec) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>removeNodes</name>
      <anchorfile>classRythmos_1_1ExplicitRKStepper.html</anchorfile>
      <anchor>a743703b91dcc2d1ee8530c5146b62769</anchor>
      <arglist>(Array&lt; Scalar &gt; &amp;time_vec)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getOrder</name>
      <anchorfile>classRythmos_1_1ExplicitRKStepper.html</anchorfile>
      <anchor>a3ef0636a011a29ed575e727e1e3ae047</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setParameterList</name>
      <anchorfile>classRythmos_1_1ExplicitRKStepper.html</anchorfile>
      <anchor>ae2d4602c7e89c4ef7585916ed2170abc</anchor>
      <arglist>(Teuchos::RCP&lt; Teuchos::ParameterList &gt; const &amp;paramList)</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; Teuchos::ParameterList &gt;</type>
      <name>getNonconstParameterList</name>
      <anchorfile>classRythmos_1_1ExplicitRKStepper.html</anchorfile>
      <anchor>abec799c600542b290721837c5c6215e5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; Teuchos::ParameterList &gt;</type>
      <name>unsetParameterList</name>
      <anchorfile>classRythmos_1_1ExplicitRKStepper.html</anchorfile>
      <anchor>a442a1976d308539feba138a45fb609ec</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const Teuchos::ParameterList &gt;</type>
      <name>getValidParameters</name>
      <anchorfile>classRythmos_1_1ExplicitRKStepper.html</anchorfile>
      <anchor>a713f2cf0c141b78f4cfdc1ff95602a2e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>supportsCloning</name>
      <anchorfile>classRythmos_1_1ExplicitRKStepper.html</anchorfile>
      <anchor>ada8ad422e31e70baa8095e3e4f2da5a3</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; StepperBase&lt; Scalar &gt; &gt;</type>
      <name>cloneStepperAlgorithm</name>
      <anchorfile>classRythmos_1_1ExplicitRKStepper.html</anchorfile>
      <anchor>ae3f5780ba8d970f6a6329bd5f0bb352f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setRKButcherTableau</name>
      <anchorfile>classRythmos_1_1ExplicitRKStepper.html</anchorfile>
      <anchor>aa05681ff55caa981805a197b2579ee2c</anchor>
      <arglist>(const RCP&lt; const RKButcherTableauBase&lt; Scalar &gt; &gt; &amp;rkbt)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const RKButcherTableauBase&lt; Scalar &gt; &gt;</type>
      <name>getRKButcherTableau</name>
      <anchorfile>classRythmos_1_1ExplicitRKStepper.html</anchorfile>
      <anchor>a0e9d15d371413ff9e0967cc1520e43a9</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setStepControlStrategy</name>
      <anchorfile>classRythmos_1_1ExplicitRKStepper.html</anchorfile>
      <anchor>a089bb4cd07adc613fee390138428345f</anchor>
      <arglist>(const RCP&lt; StepControlStrategyBase&lt; Scalar &gt; &gt; &amp;stepControlStrategy)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; StepControlStrategyBase&lt; Scalar &gt; &gt;</type>
      <name>getNonconstStepControlStrategy</name>
      <anchorfile>classRythmos_1_1ExplicitRKStepper.html</anchorfile>
      <anchor>aea60c1440da64c7a7fac91767848d4d4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const StepControlStrategyBase&lt; Scalar &gt; &gt;</type>
      <name>getStepControlStrategy</name>
      <anchorfile>classRythmos_1_1ExplicitRKStepper.html</anchorfile>
      <anchor>a211cb111bc918e9e340bf479af8a0352</anchor>
      <arglist>() const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Rythmos::ExplicitTaylorPolynomialStepper</name>
    <filename>classRythmos_1_1ExplicitTaylorPolynomialStepper.html</filename>
    <templarg>Scalar</templarg>
    <base virtualness="virtual">Rythmos::StepperBase</base>
    <member kind="typedef">
      <type>Teuchos::ScalarTraits&lt; Scalar &gt;::magnitudeType</type>
      <name>ScalarMag</name>
      <anchorfile>classRythmos_1_1ExplicitTaylorPolynomialStepper.html</anchorfile>
      <anchor>a3d26cc93daac2fb3de11dd232fb48b01</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ExplicitTaylorPolynomialStepper</name>
      <anchorfile>classRythmos_1_1ExplicitTaylorPolynomialStepper.html</anchorfile>
      <anchor>a78343ba4f21fd8355b3de708f818a44f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~ExplicitTaylorPolynomialStepper</name>
      <anchorfile>classRythmos_1_1ExplicitTaylorPolynomialStepper.html</anchorfile>
      <anchor>a74c20392f42b32db540b02837a51dc10</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const Thyra::VectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>get_x_space</name>
      <anchorfile>classRythmos_1_1ExplicitTaylorPolynomialStepper.html</anchorfile>
      <anchor>a7fd46eb87e8c9854bfe75d90ead0201d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setModel</name>
      <anchorfile>classRythmos_1_1ExplicitTaylorPolynomialStepper.html</anchorfile>
      <anchor>a10abf1b0826be89ca5a003c57416718b</anchor>
      <arglist>(const RCP&lt; const Thyra::ModelEvaluator&lt; Scalar &gt; &gt; &amp;model)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setNonconstModel</name>
      <anchorfile>classRythmos_1_1ExplicitTaylorPolynomialStepper.html</anchorfile>
      <anchor>ac65fe5aaaf9c2cd5f7554fa9f00be87c</anchor>
      <arglist>(const RCP&lt; Thyra::ModelEvaluator&lt; Scalar &gt; &gt; &amp;model)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const Thyra::ModelEvaluator&lt; Scalar &gt; &gt;</type>
      <name>getModel</name>
      <anchorfile>classRythmos_1_1ExplicitTaylorPolynomialStepper.html</anchorfile>
      <anchor>a42c6eb257d82bf642bfb97e8a750c81a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; Thyra::ModelEvaluator&lt; Scalar &gt; &gt;</type>
      <name>getNonconstModel</name>
      <anchorfile>classRythmos_1_1ExplicitTaylorPolynomialStepper.html</anchorfile>
      <anchor>a93c70855cd6bddde790d7da829e44a3d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setInitialCondition</name>
      <anchorfile>classRythmos_1_1ExplicitTaylorPolynomialStepper.html</anchorfile>
      <anchor>acb093981cf763d4bae05563b174255a2</anchor>
      <arglist>(const Thyra::ModelEvaluatorBase::InArgs&lt; Scalar &gt; &amp;initialCondition)</arglist>
    </member>
    <member kind="function">
      <type>Thyra::ModelEvaluatorBase::InArgs&lt; Scalar &gt;</type>
      <name>getInitialCondition</name>
      <anchorfile>classRythmos_1_1ExplicitTaylorPolynomialStepper.html</anchorfile>
      <anchor>a7cbb3aac47aa4c5a291ac0e2828d8570</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Scalar</type>
      <name>takeStep</name>
      <anchorfile>classRythmos_1_1ExplicitTaylorPolynomialStepper.html</anchorfile>
      <anchor>a228ecf4237eee7059fad74cdb4a7e258</anchor>
      <arglist>(Scalar dt, StepSizeType flag)</arglist>
    </member>
    <member kind="function">
      <type>const StepStatus&lt; Scalar &gt;</type>
      <name>getStepStatus</name>
      <anchorfile>classRythmos_1_1ExplicitTaylorPolynomialStepper.html</anchorfile>
      <anchor>a8eaecacf1654e38ed38cc8df059b416f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setParameterList</name>
      <anchorfile>classRythmos_1_1ExplicitTaylorPolynomialStepper.html</anchorfile>
      <anchor>a2e73981609a6e392c89a53f50579b45f</anchor>
      <arglist>(RCP&lt; Teuchos::ParameterList &gt; const &amp;paramList)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; Teuchos::ParameterList &gt;</type>
      <name>getNonconstParameterList</name>
      <anchorfile>classRythmos_1_1ExplicitTaylorPolynomialStepper.html</anchorfile>
      <anchor>a880fe70e951aa76da8f1bfdb5da26ef8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; Teuchos::ParameterList &gt;</type>
      <name>unsetParameterList</name>
      <anchorfile>classRythmos_1_1ExplicitTaylorPolynomialStepper.html</anchorfile>
      <anchor>add5f0fe268dc9387604522a14a162e81</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const Teuchos::ParameterList &gt;</type>
      <name>getValidParameters</name>
      <anchorfile>classRythmos_1_1ExplicitTaylorPolynomialStepper.html</anchorfile>
      <anchor>a9cdd705cf852ae6d6dfb69488f0253e6</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>description</name>
      <anchorfile>classRythmos_1_1ExplicitTaylorPolynomialStepper.html</anchorfile>
      <anchor>a21839fc1affcef79e7b422a455a8483b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>describe</name>
      <anchorfile>classRythmos_1_1ExplicitTaylorPolynomialStepper.html</anchorfile>
      <anchor>a02acd9d511b8d1c155da737ec72a7df6</anchor>
      <arglist>(Teuchos::FancyOStream &amp;out, const Teuchos::EVerbosityLevel verbLevel=Teuchos::Describable::verbLevel_default) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>addPoints</name>
      <anchorfile>classRythmos_1_1ExplicitTaylorPolynomialStepper.html</anchorfile>
      <anchor>aed56a1f04677e6038796fd466f3a826b</anchor>
      <arglist>(const Array&lt; Scalar &gt; &amp;time_vec, const Array&lt; RCP&lt; const Thyra::VectorBase&lt; Scalar &gt; &gt; &gt; &amp;x_vec, const Array&lt; RCP&lt; const Thyra::VectorBase&lt; Scalar &gt; &gt; &gt; &amp;xdot_vec)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>getPoints</name>
      <anchorfile>classRythmos_1_1ExplicitTaylorPolynomialStepper.html</anchorfile>
      <anchor>aa7a59c77e148a3d5662e063f82ad7e48</anchor>
      <arglist>(const Array&lt; Scalar &gt; &amp;time_vec, Array&lt; RCP&lt; const Thyra::VectorBase&lt; Scalar &gt; &gt; &gt; *x_vec, Array&lt; RCP&lt; const Thyra::VectorBase&lt; Scalar &gt; &gt; &gt; *xdot_vec, Array&lt; ScalarMag &gt; *accuracy_vec) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setRange</name>
      <anchorfile>classRythmos_1_1ExplicitTaylorPolynomialStepper.html</anchorfile>
      <anchor>aecbdb967dcd51faaafbcb101ebaca7c7</anchor>
      <arglist>(const TimeRange&lt; Scalar &gt; &amp;range, const InterpolationBufferBase&lt; Scalar &gt; &amp;IB)</arglist>
    </member>
    <member kind="function">
      <type>TimeRange&lt; Scalar &gt;</type>
      <name>getTimeRange</name>
      <anchorfile>classRythmos_1_1ExplicitTaylorPolynomialStepper.html</anchorfile>
      <anchor>acadd96d49f596f729cc41fdc4fd7fbc9</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>getNodes</name>
      <anchorfile>classRythmos_1_1ExplicitTaylorPolynomialStepper.html</anchorfile>
      <anchor>aa530971df25c72d6377e9a6c2ff13bab</anchor>
      <arglist>(Array&lt; Scalar &gt; *time_vec) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>removeNodes</name>
      <anchorfile>classRythmos_1_1ExplicitTaylorPolynomialStepper.html</anchorfile>
      <anchor>a9e8cbd164e9c72a1d9a7ad44fbb0ec08</anchor>
      <arglist>(Array&lt; Scalar &gt; &amp;time_vec)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getOrder</name>
      <anchorfile>classRythmos_1_1ExplicitTaylorPolynomialStepper.html</anchorfile>
      <anchor>ad8d05d6cc49720ce4a783350c935a6da</anchor>
      <arglist>() const </arglist>
    </member>
    <docanchor file="classRythmos_1_1ExplicitTaylorPolynomialStepper" title="Computing the Taylor Polynomial">Rythmos_ETI_local_TS</docanchor>
    <docanchor file="classRythmos_1_1ExplicitTaylorPolynomialStepper" title="Computing a Step Size">Rythmos_ETI_stepsize</docanchor>
    <docanchor file="classRythmos_1_1ExplicitTaylorPolynomialStepper" title="Summing the Polynomial">Rythmos_ETI_sum</docanchor>
    <docanchor file="classRythmos_1_1ExplicitTaylorPolynomialStepper" title="Parameters">Rythmos_ETI_params</docanchor>
  </compound>
  <compound kind="class">
    <name>Rythmos::FirstOrderErrorStepControlStrategy</name>
    <filename>classRythmos_1_1FirstOrderErrorStepControlStrategy.html</filename>
    <templarg></templarg>
    <base virtualness="virtual">Rythmos::StepControlStrategyBase</base>
    <member kind="function">
      <type>void</type>
      <name>initialize</name>
      <anchorfile>classRythmos_1_1FirstOrderErrorStepControlStrategy.html</anchorfile>
      <anchor>a3b80f45c4bc2bf20b3a045d0681cf4d1</anchor>
      <arglist>(const StepperBase&lt; Scalar &gt; &amp;stepper)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setRequestedStepSize</name>
      <anchorfile>classRythmos_1_1FirstOrderErrorStepControlStrategy.html</anchorfile>
      <anchor>aefd5a2855258646bec16c241aeb96ca1</anchor>
      <arglist>(const StepperBase&lt; Scalar &gt; &amp;stepper, const Scalar &amp;stepSize, const StepSizeType &amp;stepSizeType)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>nextStepSize</name>
      <anchorfile>classRythmos_1_1FirstOrderErrorStepControlStrategy.html</anchorfile>
      <anchor>afc280a54308ed9870a78ad50c1a7b925</anchor>
      <arglist>(const StepperBase&lt; Scalar &gt; &amp;stepper, Scalar *stepSize, StepSizeType *stepSizeType, int *order)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setCorrection</name>
      <anchorfile>classRythmos_1_1FirstOrderErrorStepControlStrategy.html</anchorfile>
      <anchor>af6bf9b0fd8fc249035dd9488b0b697a1</anchor>
      <arglist>(const StepperBase&lt; Scalar &gt; &amp;stepper, const RCP&lt; const Thyra::VectorBase&lt; Scalar &gt; &gt; &amp;soln, const RCP&lt; const Thyra::VectorBase&lt; Scalar &gt; &gt; &amp;ee, int solveStatus)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>acceptStep</name>
      <anchorfile>classRythmos_1_1FirstOrderErrorStepControlStrategy.html</anchorfile>
      <anchor>a8b3321e52a673fdf75c9d8cecb01815e</anchor>
      <arglist>(const StepperBase&lt; Scalar &gt; &amp;stepper, Scalar *LETValue)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>completeStep</name>
      <anchorfile>classRythmos_1_1FirstOrderErrorStepControlStrategy.html</anchorfile>
      <anchor>aae74b3a759ba51a7561ab5d7344acb0e</anchor>
      <arglist>(const StepperBase&lt; Scalar &gt; &amp;stepper)</arglist>
    </member>
    <member kind="function">
      <type>AttemptedStepStatusFlag</type>
      <name>rejectStep</name>
      <anchorfile>classRythmos_1_1FirstOrderErrorStepControlStrategy.html</anchorfile>
      <anchor>a12fbdab172924afc08fb7ffa8c8e38f0</anchor>
      <arglist>(const StepperBase&lt; Scalar &gt; &amp;stepper)</arglist>
    </member>
    <member kind="function">
      <type>StepControlStrategyState</type>
      <name>getCurrentState</name>
      <anchorfile>classRythmos_1_1FirstOrderErrorStepControlStrategy.html</anchorfile>
      <anchor>a330567dd4d8a7440c742475fef7de9d0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getMaxOrder</name>
      <anchorfile>classRythmos_1_1FirstOrderErrorStepControlStrategy.html</anchorfile>
      <anchor>a11c84d29b241e8b1f4c25ce0ad1bde8e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setStepControlData</name>
      <anchorfile>classRythmos_1_1FirstOrderErrorStepControlStrategy.html</anchorfile>
      <anchor>a2871cdb416b4f53d87c05f56450bab06</anchor>
      <arglist>(const StepperBase&lt; Scalar &gt; &amp;stepper)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>supportsCloning</name>
      <anchorfile>classRythmos_1_1FirstOrderErrorStepControlStrategy.html</anchorfile>
      <anchor>a989c9849c746ff9c8f8b06a6f8004a31</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; StepControlStrategyBase&lt; Scalar &gt; &gt;</type>
      <name>cloneStepControlStrategyAlgorithm</name>
      <anchorfile>classRythmos_1_1FirstOrderErrorStepControlStrategy.html</anchorfile>
      <anchor>a20232ee866bf868745be5e3fb0a5c023</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>describe</name>
      <anchorfile>classRythmos_1_1FirstOrderErrorStepControlStrategy.html</anchorfile>
      <anchor>a91e6cfb4b61abaac169a427d8b3bf663</anchor>
      <arglist>(Teuchos::FancyOStream &amp;out, const Teuchos::EVerbosityLevel verbLevel) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setParameterList</name>
      <anchorfile>classRythmos_1_1FirstOrderErrorStepControlStrategy.html</anchorfile>
      <anchor>af220ce62d1d4c4ca1da18481b62738d9</anchor>
      <arglist>(RCP&lt; Teuchos::ParameterList &gt; const &amp;paramList)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; Teuchos::ParameterList &gt;</type>
      <name>getNonconstParameterList</name>
      <anchorfile>classRythmos_1_1FirstOrderErrorStepControlStrategy.html</anchorfile>
      <anchor>a006ec0c4cb9834735ea584faf916facc</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; Teuchos::ParameterList &gt;</type>
      <name>unsetParameterList</name>
      <anchorfile>classRythmos_1_1FirstOrderErrorStepControlStrategy.html</anchorfile>
      <anchor>a2c0533325bba78606d2d76d0818b81ae</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const Teuchos::ParameterList &gt;</type>
      <name>getValidParameters</name>
      <anchorfile>classRythmos_1_1FirstOrderErrorStepControlStrategy.html</anchorfile>
      <anchor>a1f6bfb291dbb101a23cdb0297cd75b47</anchor>
      <arglist>() const </arglist>
    </member>
    <docanchor file="classRythmos_1_1FirstOrderErrorStepControlStrategy" title="Theory">Rythmos_FirstOrderErrorStepControlStrategy_Theory_sec</docanchor>
  </compound>
  <compound kind="class">
    <name>Rythmos::ForwardEulerStepper</name>
    <filename>classRythmos_1_1ForwardEulerStepper.html</filename>
    <templarg></templarg>
    <base virtualness="virtual">Rythmos::StepperBase</base>
    <member kind="function">
      <type></type>
      <name>ForwardEulerStepper</name>
      <anchorfile>classRythmos_1_1ForwardEulerStepper.html</anchorfile>
      <anchor>ad78fa2e60978e9fcae3af411a81f9335</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>supportsCloning</name>
      <anchorfile>classRythmos_1_1ForwardEulerStepper.html</anchorfile>
      <anchor>a636a456d1c07c37d0d9ffc28f34b6e69</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; StepperBase&lt; Scalar &gt; &gt;</type>
      <name>cloneStepperAlgorithm</name>
      <anchorfile>classRythmos_1_1ForwardEulerStepper.html</anchorfile>
      <anchor>a083d01e0f81cec59e042afba3ab6ccfc</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setModel</name>
      <anchorfile>classRythmos_1_1ForwardEulerStepper.html</anchorfile>
      <anchor>addfd524c13964b94a8e3f739078b4852</anchor>
      <arglist>(const RCP&lt; const Thyra::ModelEvaluator&lt; Scalar &gt; &gt; &amp;model)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setNonconstModel</name>
      <anchorfile>classRythmos_1_1ForwardEulerStepper.html</anchorfile>
      <anchor>a2a91eb5889750d4dd4a64aaa855f3f38</anchor>
      <arglist>(const RCP&lt; Thyra::ModelEvaluator&lt; Scalar &gt; &gt; &amp;model)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const Thyra::ModelEvaluator&lt; Scalar &gt; &gt;</type>
      <name>getModel</name>
      <anchorfile>classRythmos_1_1ForwardEulerStepper.html</anchorfile>
      <anchor>a7bc3935b92d8efa6d01362b9a40daf11</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; Thyra::ModelEvaluator&lt; Scalar &gt; &gt;</type>
      <name>getNonconstModel</name>
      <anchorfile>classRythmos_1_1ForwardEulerStepper.html</anchorfile>
      <anchor>aaa037b24288540a297ed4ede12d8dd08</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setInitialCondition</name>
      <anchorfile>classRythmos_1_1ForwardEulerStepper.html</anchorfile>
      <anchor>a5543ec2d61cd7cb78f3e1211c0e5b8b0</anchor>
      <arglist>(const Thyra::ModelEvaluatorBase::InArgs&lt; Scalar &gt; &amp;initialCondition)</arglist>
    </member>
    <member kind="function">
      <type>Thyra::ModelEvaluatorBase::InArgs&lt; Scalar &gt;</type>
      <name>getInitialCondition</name>
      <anchorfile>classRythmos_1_1ForwardEulerStepper.html</anchorfile>
      <anchor>a1364e11f339cccb5747a223e414ae6a5</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const Thyra::VectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>get_x_space</name>
      <anchorfile>classRythmos_1_1ForwardEulerStepper.html</anchorfile>
      <anchor>ace5888243c06074106f4b1774b2f4dac</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~ForwardEulerStepper</name>
      <anchorfile>classRythmos_1_1ForwardEulerStepper.html</anchorfile>
      <anchor>af8e8d1aa4ea54e8d49c949a9de828a55</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Scalar</type>
      <name>takeStep</name>
      <anchorfile>classRythmos_1_1ForwardEulerStepper.html</anchorfile>
      <anchor>ae9be86ef9ad64a62b2badc3ea3d46a81</anchor>
      <arglist>(Scalar dt, StepSizeType flag)</arglist>
    </member>
    <member kind="function">
      <type>const StepStatus&lt; Scalar &gt;</type>
      <name>getStepStatus</name>
      <anchorfile>classRythmos_1_1ForwardEulerStepper.html</anchorfile>
      <anchor>ad623beec7094a5fe03bf89531be2d37b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>description</name>
      <anchorfile>classRythmos_1_1ForwardEulerStepper.html</anchorfile>
      <anchor>aad0c0465ecb0fbc24ca354134b1f8235</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>describe</name>
      <anchorfile>classRythmos_1_1ForwardEulerStepper.html</anchorfile>
      <anchor>af16633ceb9ff8154889a72da245d7609</anchor>
      <arglist>(Teuchos::FancyOStream &amp;out, const Teuchos::EVerbosityLevel verbLevel) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>addPoints</name>
      <anchorfile>classRythmos_1_1ForwardEulerStepper.html</anchorfile>
      <anchor>a16aea705c68bbcceb4629e1ba0894659</anchor>
      <arglist>(const Array&lt; Scalar &gt; &amp;time_vec, const Array&lt; RCP&lt; const Thyra::VectorBase&lt; Scalar &gt; &gt; &gt; &amp;x_vec, const Array&lt; RCP&lt; const Thyra::VectorBase&lt; Scalar &gt; &gt; &gt; &amp;xdot_vec)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>getPoints</name>
      <anchorfile>classRythmos_1_1ForwardEulerStepper.html</anchorfile>
      <anchor>a53afbc405cae923f91bea0849ed49cbb</anchor>
      <arglist>(const Array&lt; Scalar &gt; &amp;time_vec, Array&lt; RCP&lt; const Thyra::VectorBase&lt; Scalar &gt; &gt; &gt; *x_vec, Array&lt; RCP&lt; const Thyra::VectorBase&lt; Scalar &gt; &gt; &gt; *xdot_vec, Array&lt; ScalarMag &gt; *accuracy_vec) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setRange</name>
      <anchorfile>classRythmos_1_1ForwardEulerStepper.html</anchorfile>
      <anchor>ae902a0afd8a6242475b124e4bd3f297d</anchor>
      <arglist>(const TimeRange&lt; Scalar &gt; &amp;range, const InterpolationBufferBase&lt; Scalar &gt; &amp;IB)</arglist>
    </member>
    <member kind="function">
      <type>TimeRange&lt; Scalar &gt;</type>
      <name>getTimeRange</name>
      <anchorfile>classRythmos_1_1ForwardEulerStepper.html</anchorfile>
      <anchor>a16fb507a1e2adc5f2ff39a9036c785c0</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>getNodes</name>
      <anchorfile>classRythmos_1_1ForwardEulerStepper.html</anchorfile>
      <anchor>aec873ac62d380f460e150b88e0875d4f</anchor>
      <arglist>(Array&lt; Scalar &gt; *time_vec) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>removeNodes</name>
      <anchorfile>classRythmos_1_1ForwardEulerStepper.html</anchorfile>
      <anchor>ab41365bf8646a0b0ff106950383a4828</anchor>
      <arglist>(Array&lt; Scalar &gt; &amp;time_vec)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getOrder</name>
      <anchorfile>classRythmos_1_1ForwardEulerStepper.html</anchorfile>
      <anchor>a7ad30c17a3fb5d754c403a168397c1a5</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setParameterList</name>
      <anchorfile>classRythmos_1_1ForwardEulerStepper.html</anchorfile>
      <anchor>ab641f6f3e203dd663b1c383079caf176</anchor>
      <arglist>(RCP&lt; Teuchos::ParameterList &gt; const &amp;paramList)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; Teuchos::ParameterList &gt;</type>
      <name>getNonconstParameterList</name>
      <anchorfile>classRythmos_1_1ForwardEulerStepper.html</anchorfile>
      <anchor>a7a6f47f0ce355242a4a4c16d4d19729c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; Teuchos::ParameterList &gt;</type>
      <name>unsetParameterList</name>
      <anchorfile>classRythmos_1_1ForwardEulerStepper.html</anchorfile>
      <anchor>a5773a56363810be8f3305cc99fe9d861</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const Teuchos::ParameterList &gt;</type>
      <name>getValidParameters</name>
      <anchorfile>classRythmos_1_1ForwardEulerStepper.html</anchorfile>
      <anchor>ae8bf311a1f76ab48f337fe608fcb9185</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const MomentoBase&lt; Scalar &gt; &gt;</type>
      <name>getMomento</name>
      <anchorfile>classRythmos_1_1ForwardEulerStepper.html</anchorfile>
      <anchor>ad40816ad1849331f232d7a86a3c876e2</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setMomento</name>
      <anchorfile>classRythmos_1_1ForwardEulerStepper.html</anchorfile>
      <anchor>a7227718db057070b4423ecc12c18d9c4</anchor>
      <arglist>(const Ptr&lt; const MomentoBase&lt; Scalar &gt; &gt; &amp;momentoPtr)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Rythmos::ForwardEulerStepperMomento</name>
    <filename>classRythmos_1_1ForwardEulerStepperMomento.html</filename>
    <templarg>Scalar</templarg>
    <base virtualness="virtual">Rythmos::MomentoBase</base>
  </compound>
  <compound kind="class">
    <name>Rythmos::ForwardResponseSensitivityComputer</name>
    <filename>classRythmos_1_1ForwardResponseSensitivityComputer.html</filename>
    <templarg>Scalar</templarg>
    <member kind="function">
      <type></type>
      <name>ForwardResponseSensitivityComputer</name>
      <anchorfile>classRythmos_1_1ForwardResponseSensitivityComputer.html</anchorfile>
      <anchor>af7d132ad698d467ef69d3240187392c7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classRythmos_1_1ForwardResponseSensitivityComputer.html</anchorfile>
      <anchor>a97298286f1662671e6b1754997120b86</anchor>
      <arglist>(bool, dumpSensitivities)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setResponseFunction</name>
      <anchorfile>classRythmos_1_1ForwardResponseSensitivityComputer.html</anchorfile>
      <anchor>a4434e86efeaa25669d98410f05edc7fb</anchor>
      <arglist>(const RCP&lt; const Thyra::ModelEvaluator&lt; Scalar &gt; &gt; &amp;responseFunc, const Thyra::ModelEvaluatorBase::InArgs&lt; Scalar &gt; &amp;basePoint, const int p_index, const int g_index)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>resetResponseFunction</name>
      <anchorfile>classRythmos_1_1ForwardResponseSensitivityComputer.html</anchorfile>
      <anchor>aeb7b5b4cd46d9b9c38404667680582f3</anchor>
      <arglist>(const RCP&lt; const Thyra::ModelEvaluator&lt; Scalar &gt; &gt; &amp;responseFunc, const Thyra::ModelEvaluatorBase::InArgs&lt; Scalar &gt; &amp;basePoint)</arglist>
    </member>
    <member kind="function">
      <type>const RCP&lt; Thyra::VectorBase&lt; Scalar &gt; &gt;</type>
      <name>create_g_hat</name>
      <anchorfile>classRythmos_1_1ForwardResponseSensitivityComputer.html</anchorfile>
      <anchor>ac25a1688d6db7ef2d39593f59d57f853</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const RCP&lt; Thyra::MultiVectorBase&lt; Scalar &gt; &gt;</type>
      <name>create_D_g_hat_D_p</name>
      <anchorfile>classRythmos_1_1ForwardResponseSensitivityComputer.html</anchorfile>
      <anchor>a043b1cdb029413e7dd055283192dc7b2</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>computeResponse</name>
      <anchorfile>classRythmos_1_1ForwardResponseSensitivityComputer.html</anchorfile>
      <anchor>af36521e54dca6ffb1083e2ef5f66ddde</anchor>
      <arglist>(const Thyra::VectorBase&lt; Scalar &gt; *x_dot, const Thyra::VectorBase&lt; Scalar &gt; &amp;x, const Scalar t, Thyra::VectorBase&lt; Scalar &gt; *g_hat) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>computeResponseAndSensitivity</name>
      <anchorfile>classRythmos_1_1ForwardResponseSensitivityComputer.html</anchorfile>
      <anchor>ac660cc446e70f6603d7ce07a58188bec</anchor>
      <arglist>(const Thyra::VectorBase&lt; Scalar &gt; *x_dot, const Thyra::MultiVectorBase&lt; Scalar &gt; *S_dot, const Thyra::VectorBase&lt; Scalar &gt; &amp;x, const Thyra::MultiVectorBase&lt; Scalar &gt; &amp;S, const Scalar t, Thyra::VectorBase&lt; Scalar &gt; *g_hat, Thyra::MultiVectorBase&lt; Scalar &gt; *D_g_hat_D_p) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Rythmos::ForwardResponseSensitivityComputerObserver</name>
    <filename>classRythmos_1_1ForwardResponseSensitivityComputerObserver.html</filename>
    <templarg></templarg>
    <base>Rythmos::IntegrationObserverBase</base>
    <member kind="function">
      <type>RCP&lt; ForwardResponseSensitivityComputerObserver&lt; Scalar &gt; &gt;</type>
      <name>forwardResponseSensitivityComputerObserver</name>
      <anchorfile>classRythmos_1_1ForwardResponseSensitivityComputerObserver.html</anchorfile>
      <anchor>a9731c9cbeb9c1ce65d9dadd8d52d4f82</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; ForwardResponseSensitivityComputerObserver&lt; Scalar &gt; &gt;</type>
      <name>forwardResponseSensitivityComputerObserver</name>
      <anchorfile>classRythmos_1_1ForwardResponseSensitivityComputerObserver.html</anchorfile>
      <anchor>a0402d2208a676ee61918a4d61b717677</anchor>
      <arglist>(const RCP&lt; const Thyra::ModelEvaluator&lt; Scalar &gt; &gt; &amp;responseFunc, const Thyra::ModelEvaluatorBase::InArgs&lt; Scalar &gt; &amp;basePoint, const int p_index, const int g_index)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ForwardResponseSensitivityComputerObserver</name>
      <anchorfile>classRythmos_1_1ForwardResponseSensitivityComputerObserver.html</anchorfile>
      <anchor>ab83e40a5fa80765f17ca1ce537069edb</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initialize</name>
      <anchorfile>classRythmos_1_1ForwardResponseSensitivityComputerObserver.html</anchorfile>
      <anchor>ad0841d55794fa6d30acd2132ceba7426</anchor>
      <arglist>(const RCP&lt; const Thyra::ModelEvaluator&lt; Scalar &gt; &gt; &amp;responseFunc, const Thyra::ModelEvaluatorBase::InArgs&lt; Scalar &gt; &amp;basePoint, const int p_index, const int g_index)</arglist>
    </member>
    <member kind="function">
      <type>const Array&lt; ResponseAndFwdSensPoint&lt; Scalar &gt; &gt; &amp;</type>
      <name>responseAndFwdSensPoints</name>
      <anchorfile>classRythmos_1_1ForwardResponseSensitivityComputerObserver.html</anchorfile>
      <anchor>a86a06bb09011c04b373253ef06087309</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual RCP&lt; IntegrationObserverBase&lt; Scalar &gt; &gt;</type>
      <name>cloneIntegrationObserver</name>
      <anchorfile>classRythmos_1_1ForwardResponseSensitivityComputerObserver.html</anchorfile>
      <anchor>a5272e44ffef4462b550eff59571bbc56</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>resetIntegrationObserver</name>
      <anchorfile>classRythmos_1_1ForwardResponseSensitivityComputerObserver.html</anchorfile>
      <anchor>aae3d576c09de82d5925b505c4144d825</anchor>
      <arglist>(const TimeRange&lt; Scalar &gt; &amp;integrationTimeDomain)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>observeCompletedTimeStep</name>
      <anchorfile>classRythmos_1_1ForwardResponseSensitivityComputerObserver.html</anchorfile>
      <anchor>a1de5f1762469869d725ec9155e68aea2</anchor>
      <arglist>(const StepperBase&lt; Scalar &gt; &amp;stepper, const StepControlInfo&lt; Scalar &gt; &amp;stepCtrlInfo, const int timeStepIter)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Rythmos::ForwardSensitivityExplicitModelEvaluator</name>
    <filename>classRythmos_1_1ForwardSensitivityExplicitModelEvaluator.html</filename>
    <templarg></templarg>
    <base virtualness="virtual">Rythmos::ForwardSensitivityModelEvaluatorBase</base>
    <member kind="function">
      <type></type>
      <name>ForwardSensitivityExplicitModelEvaluator</name>
      <anchorfile>classRythmos_1_1ForwardSensitivityExplicitModelEvaluator.html</anchorfile>
      <anchor>ab7095ededbed4d96bda77f11a31e89b8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initializeStructure</name>
      <anchorfile>classRythmos_1_1ForwardSensitivityExplicitModelEvaluator.html</anchorfile>
      <anchor>ac1103aa812fb43a02514a424feac3dcd</anchor>
      <arglist>(const RCP&lt; const Thyra::ModelEvaluator&lt; Scalar &gt; &gt; &amp;stateModel, const int p_index)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initializeStructureInitCondOnly</name>
      <anchorfile>classRythmos_1_1ForwardSensitivityExplicitModelEvaluator.html</anchorfile>
      <anchor>ac05e1f14d459f932c6870b0f325933fb</anchor>
      <arglist>(const RCP&lt; const Thyra::ModelEvaluator&lt; Scalar &gt; &gt; &amp;stateModel, const RCP&lt; const Thyra::VectorSpaceBase&lt; Scalar &gt; &gt; &amp;p_space)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const Thyra::ModelEvaluator&lt; Scalar &gt; &gt;</type>
      <name>getStateModel</name>
      <anchorfile>classRythmos_1_1ForwardSensitivityExplicitModelEvaluator.html</anchorfile>
      <anchor>a91e39527d687e78c5c9cf91b8cc904aa</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; Thyra::ModelEvaluator&lt; Scalar &gt; &gt;</type>
      <name>getNonconstStateModel</name>
      <anchorfile>classRythmos_1_1ForwardSensitivityExplicitModelEvaluator.html</anchorfile>
      <anchor>a3fa203d8ef14dbc486cc7e01492bd3b0</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>get_p_index</name>
      <anchorfile>classRythmos_1_1ForwardSensitivityExplicitModelEvaluator.html</anchorfile>
      <anchor>a48607020bf47bd5b36ff808ee22a50b6</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const Thyra::DefaultMultiVectorProductVectorSpace&lt; Scalar &gt; &gt;</type>
      <name>get_s_bar_space</name>
      <anchorfile>classRythmos_1_1ForwardSensitivityExplicitModelEvaluator.html</anchorfile>
      <anchor>a077c398a49850a2f1428ce6d40b584b5</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const Thyra::VectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>get_p_sens_space</name>
      <anchorfile>classRythmos_1_1ForwardSensitivityExplicitModelEvaluator.html</anchorfile>
      <anchor>a5d9c8d997959eaabd9bc7287852cfb49</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initializePointState</name>
      <anchorfile>classRythmos_1_1ForwardSensitivityExplicitModelEvaluator.html</anchorfile>
      <anchor>aeebf326fdabae166ba49c34779c342b4</anchor>
      <arglist>(Ptr&lt; StepperBase&lt; Scalar &gt; &gt; stateStepper, bool forceUpToDateW)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const Thyra::VectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>get_x_space</name>
      <anchorfile>classRythmos_1_1ForwardSensitivityExplicitModelEvaluator.html</anchorfile>
      <anchor>a94d3d54ccc63c330062f009a5db8cb0e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const Thyra::VectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>get_f_space</name>
      <anchorfile>classRythmos_1_1ForwardSensitivityExplicitModelEvaluator.html</anchorfile>
      <anchor>a5ef01ab9f75e699096a44823cf83fcaa</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Thyra::ModelEvaluatorBase::InArgs&lt; Scalar &gt;</type>
      <name>getNominalValues</name>
      <anchorfile>classRythmos_1_1ForwardSensitivityExplicitModelEvaluator.html</anchorfile>
      <anchor>af53df2cfb7fdced5db8a57976b367793</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; Thyra::LinearOpWithSolveBase&lt; Scalar &gt; &gt;</type>
      <name>create_W</name>
      <anchorfile>classRythmos_1_1ForwardSensitivityExplicitModelEvaluator.html</anchorfile>
      <anchor>a44a154c1e15ae3bf94d25fc9507184c2</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Thyra::ModelEvaluatorBase::InArgs&lt; Scalar &gt;</type>
      <name>createInArgs</name>
      <anchorfile>classRythmos_1_1ForwardSensitivityExplicitModelEvaluator.html</anchorfile>
      <anchor>a987cda67f9627929e39ccd918c5269cb</anchor>
      <arglist>() const </arglist>
    </member>
    <docanchor file="classRythmos_1_1ForwardSensitivityExplicitModelEvaluator" title="Introduction">Rythmos_ForwardSensitivityExplicitModelEvaluator_intro_sec</docanchor>
  </compound>
  <compound kind="class">
    <name>Rythmos::ForwardSensitivityImplicitModelEvaluator</name>
    <filename>classRythmos_1_1ForwardSensitivityImplicitModelEvaluator.html</filename>
    <templarg></templarg>
    <base virtualness="virtual">Rythmos::ForwardSensitivityModelEvaluatorBase</base>
    <member kind="function">
      <type></type>
      <name>ForwardSensitivityImplicitModelEvaluator</name>
      <anchorfile>classRythmos_1_1ForwardSensitivityImplicitModelEvaluator.html</anchorfile>
      <anchor>aee0b1beac8a569792b8a1debda6bb270</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initializeStructure</name>
      <anchorfile>classRythmos_1_1ForwardSensitivityImplicitModelEvaluator.html</anchorfile>
      <anchor>a5e1417912e8609eebf8efb1bbb22259e</anchor>
      <arglist>(const RCP&lt; const Thyra::ModelEvaluator&lt; Scalar &gt; &gt; &amp;stateModel, const int p_index)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const Thyra::ModelEvaluator&lt; Scalar &gt; &gt;</type>
      <name>getStateModel</name>
      <anchorfile>classRythmos_1_1ForwardSensitivityImplicitModelEvaluator.html</anchorfile>
      <anchor>ad9e99d1e9ea8c60e77712599aa1cba08</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; Thyra::ModelEvaluator&lt; Scalar &gt; &gt;</type>
      <name>getNonconstStateModel</name>
      <anchorfile>classRythmos_1_1ForwardSensitivityImplicitModelEvaluator.html</anchorfile>
      <anchor>af2110c8c9ed5b9bf36e084ddf0762cfd</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>get_p_index</name>
      <anchorfile>classRythmos_1_1ForwardSensitivityImplicitModelEvaluator.html</anchorfile>
      <anchor>a719d9398d6245d08f6a815c9e7a41e08</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setStateIntegrator</name>
      <anchorfile>classRythmos_1_1ForwardSensitivityImplicitModelEvaluator.html</anchorfile>
      <anchor>a7f934a61c2fcfe3ae75e982036178df6</anchor>
      <arglist>(const RCP&lt; IntegratorBase&lt; Scalar &gt; &gt; &amp;stateIntegrator, const Thyra::ModelEvaluatorBase::InArgs&lt; Scalar &gt; &amp;stateBasePoint)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initializePointState</name>
      <anchorfile>classRythmos_1_1ForwardSensitivityImplicitModelEvaluator.html</anchorfile>
      <anchor>ae59518fbc4a0495aadc6fef3d3d0a700</anchor>
      <arglist>(Ptr&lt; StepperBase&lt; Scalar &gt; &gt; stateStepper, bool forceUpToDateW)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initializeStructureInitCondOnly</name>
      <anchorfile>classRythmos_1_1ForwardSensitivityImplicitModelEvaluator.html</anchorfile>
      <anchor>af18b50fc8df6457d59869780cc7018f4</anchor>
      <arglist>(const RCP&lt; const Thyra::ModelEvaluator&lt; Scalar &gt; &gt; &amp;stateModel, const RCP&lt; const Thyra::VectorSpaceBase&lt; Scalar &gt; &gt; &amp;p_space)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const Thyra::DefaultMultiVectorProductVectorSpace&lt; Scalar &gt; &gt;</type>
      <name>get_s_bar_space</name>
      <anchorfile>classRythmos_1_1ForwardSensitivityImplicitModelEvaluator.html</anchorfile>
      <anchor>ad121da03d5319c259f86ebd5f0a51a92</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const Thyra::VectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>get_p_sens_space</name>
      <anchorfile>classRythmos_1_1ForwardSensitivityImplicitModelEvaluator.html</anchorfile>
      <anchor>ac029296bab68381d81ad73d43d428ecd</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const Thyra::VectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>get_x_space</name>
      <anchorfile>classRythmos_1_1ForwardSensitivityImplicitModelEvaluator.html</anchorfile>
      <anchor>aa54ec22399e35cb99ee0aec76a05f731</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const Thyra::VectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>get_f_space</name>
      <anchorfile>classRythmos_1_1ForwardSensitivityImplicitModelEvaluator.html</anchorfile>
      <anchor>a43f589a2c796976f72c4c835e4e2bf6e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Thyra::ModelEvaluatorBase::InArgs&lt; Scalar &gt;</type>
      <name>getNominalValues</name>
      <anchorfile>classRythmos_1_1ForwardSensitivityImplicitModelEvaluator.html</anchorfile>
      <anchor>a43443e61bd5f0b656b448ee79f4354d0</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; Thyra::LinearOpWithSolveBase&lt; Scalar &gt; &gt;</type>
      <name>create_W</name>
      <anchorfile>classRythmos_1_1ForwardSensitivityImplicitModelEvaluator.html</anchorfile>
      <anchor>a4c068eccead3c57c2fe84192fc8fa11e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Thyra::ModelEvaluatorBase::InArgs&lt; Scalar &gt;</type>
      <name>createInArgs</name>
      <anchorfile>classRythmos_1_1ForwardSensitivityImplicitModelEvaluator.html</anchorfile>
      <anchor>afe6780a0b3a1478e73ce8f5d5b92500f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initializeState</name>
      <anchorfile>classRythmos_1_1ForwardSensitivityImplicitModelEvaluator.html</anchorfile>
      <anchor>a4be283cea9fb09502ac21769ad08df88</anchor>
      <arglist>(const Thyra::ModelEvaluatorBase::InArgs&lt; Scalar &gt; &amp;stateBasePoint, const RCP&lt; const Thyra::LinearOpWithSolveBase&lt; Scalar &gt; &gt; &amp;W_tilde, const Scalar &amp;coeff_x_dot, const Scalar &amp;coeff_x, const RCP&lt; const Thyra::LinearOpBase&lt; Scalar &gt; &gt; &amp;DfDx_dot=Teuchos::null, const RCP&lt; const Thyra::MultiVectorBase&lt; Scalar &gt; &gt; &amp;DfDp=Teuchos::null)</arglist>
    </member>
    <docanchor file="classRythmos_1_1ForwardSensitivityImplicitModelEvaluator" title="Introduction">Rythmos_ForwardSensitivityModelEvaluatorBase_intro_sec</docanchor>
    <docanchor file="classRythmos_1_1ForwardSensitivityImplicitModelEvaluator" title="Implementation Details">Rythmos_ForwardSensitivityModelEvaluatorBase_details_sec</docanchor>
  </compound>
  <compound kind="class">
    <name>Rythmos::ForwardSensitivityIntegratorAsModelEvaluator</name>
    <filename>classRythmos_1_1ForwardSensitivityIntegratorAsModelEvaluator.html</filename>
    <templarg></templarg>
    <member kind="function">
      <type></type>
      <name>ForwardSensitivityIntegratorAsModelEvaluator</name>
      <anchorfile>classRythmos_1_1ForwardSensitivityIntegratorAsModelEvaluator.html</anchorfile>
      <anchor>ac42e8a0eb4be6fce88976978f3825b3b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initialize</name>
      <anchorfile>classRythmos_1_1ForwardSensitivityIntegratorAsModelEvaluator.html</anchorfile>
      <anchor>a0e9f87a6423d2ef9be0f7b8a5c189652</anchor>
      <arglist>(const RCP&lt; StepperBase&lt; Scalar &gt; &gt; &amp;stateStepper, const RCP&lt; IntegratorBase&lt; Scalar &gt; &gt; &amp;stateIntegrator, const RCP&lt; ForwardSensitivityStepper&lt; Scalar &gt; &gt; &amp;stateAndSensStepper, const RCP&lt; IntegratorBase&lt; Scalar &gt; &gt; &amp;stateAndSensIntegrator, const Thyra::ModelEvaluatorBase::InArgs&lt; Scalar &gt; &amp;stateAndSensInitCond, const Array&lt; Scalar &gt; &amp;responseTimes, const Array&lt; RCP&lt; const Thyra::ModelEvaluator&lt; Scalar &gt; &gt; &gt; &amp;responseFuncs, const Array&lt; Thyra::ModelEvaluatorBase::InArgs&lt; Scalar &gt; &gt; &amp;responseFuncBasePoints, const ForwardSensitivityIntegratorAsModelEvaluatorTypes::EResponseType responseType)</arglist>
    </member>
    <member kind="function">
      <type>const Array&lt; Scalar &gt; &amp;</type>
      <name>getResponseTimes</name>
      <anchorfile>classRythmos_1_1ForwardSensitivityIntegratorAsModelEvaluator.html</anchorfile>
      <anchor>a09ea5f2cb9a83e3bc1690478c1cfd794</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setParameterList</name>
      <anchorfile>classRythmos_1_1ForwardSensitivityIntegratorAsModelEvaluator.html</anchorfile>
      <anchor>adef4222e9d1d96160b9d29eb514f9a8d</anchor>
      <arglist>(RCP&lt; Teuchos::ParameterList &gt; const &amp;paramList)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; Teuchos::ParameterList &gt;</type>
      <name>getNonconstParameterList</name>
      <anchorfile>classRythmos_1_1ForwardSensitivityIntegratorAsModelEvaluator.html</anchorfile>
      <anchor>a57ab19002ae9aaddb1662a2e4a231dbd</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; Teuchos::ParameterList &gt;</type>
      <name>unsetParameterList</name>
      <anchorfile>classRythmos_1_1ForwardSensitivityIntegratorAsModelEvaluator.html</anchorfile>
      <anchor>a2331bf0602a597b855901091714a0e78</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const Teuchos::ParameterList &gt;</type>
      <name>getParameterList</name>
      <anchorfile>classRythmos_1_1ForwardSensitivityIntegratorAsModelEvaluator.html</anchorfile>
      <anchor>a5f0b0284357007519f0eb47d1ba9c975</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const Teuchos::ParameterList &gt;</type>
      <name>getValidParameters</name>
      <anchorfile>classRythmos_1_1ForwardSensitivityIntegratorAsModelEvaluator.html</anchorfile>
      <anchor>a513a4c3a7d536e48db6547c8489c1f02</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Np</name>
      <anchorfile>classRythmos_1_1ForwardSensitivityIntegratorAsModelEvaluator.html</anchorfile>
      <anchor>a0ce364b3b8e4284f7547f59f2d144236</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Ng</name>
      <anchorfile>classRythmos_1_1ForwardSensitivityIntegratorAsModelEvaluator.html</anchorfile>
      <anchor>aea4094c6ba55e83f6781018b3d23f27f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const Thyra::VectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>get_p_space</name>
      <anchorfile>classRythmos_1_1ForwardSensitivityIntegratorAsModelEvaluator.html</anchorfile>
      <anchor>a5c7688019d7ea46fe7671fe8ece158b1</anchor>
      <arglist>(int l) const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const Thyra::VectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>get_g_space</name>
      <anchorfile>classRythmos_1_1ForwardSensitivityIntegratorAsModelEvaluator.html</anchorfile>
      <anchor>ae013db8550a0b4e50dbcdd30101a8deb</anchor>
      <arglist>(int j) const </arglist>
    </member>
    <member kind="function">
      <type>Thyra::ModelEvaluatorBase::InArgs&lt; Scalar &gt;</type>
      <name>createInArgs</name>
      <anchorfile>classRythmos_1_1ForwardSensitivityIntegratorAsModelEvaluator.html</anchorfile>
      <anchor>aed1c7496d5c69abbaf19c99733fb89f0</anchor>
      <arglist>() const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Rythmos::ForwardSensitivityModelEvaluatorBase</name>
    <filename>classRythmos_1_1ForwardSensitivityModelEvaluatorBase.html</filename>
    <templarg>Scalar</templarg>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>initializeStructure</name>
      <anchorfile>classRythmos_1_1ForwardSensitivityModelEvaluatorBase.html</anchorfile>
      <anchor>af0e2bb6549fefba804c042eb6d1e3dad</anchor>
      <arglist>(const RCP&lt; const Thyra::ModelEvaluator&lt; Scalar &gt; &gt; &amp;stateModel, const int p_index)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>initializeStructureInitCondOnly</name>
      <anchorfile>classRythmos_1_1ForwardSensitivityModelEvaluatorBase.html</anchorfile>
      <anchor>ae60c1a7c79e17e20189ba412be926fd5</anchor>
      <arglist>(const RCP&lt; const Thyra::ModelEvaluator&lt; Scalar &gt; &gt; &amp;stateModel, const RCP&lt; const Thyra::VectorSpaceBase&lt; Scalar &gt; &gt; &amp;p_space)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual RCP&lt; const Thyra::ModelEvaluator&lt; Scalar &gt; &gt;</type>
      <name>getStateModel</name>
      <anchorfile>classRythmos_1_1ForwardSensitivityModelEvaluatorBase.html</anchorfile>
      <anchor>a64e08726c7914d57691dfb6063d90bef</anchor>
      <arglist>() const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual RCP&lt; Thyra::ModelEvaluator&lt; Scalar &gt; &gt;</type>
      <name>getNonconstStateModel</name>
      <anchorfile>classRythmos_1_1ForwardSensitivityModelEvaluatorBase.html</anchorfile>
      <anchor>a5c1b736e4176aaee6134a7768339ff0a</anchor>
      <arglist>() const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>get_p_index</name>
      <anchorfile>classRythmos_1_1ForwardSensitivityModelEvaluatorBase.html</anchorfile>
      <anchor>aa6395380547789d0d9374394aad48040</anchor>
      <arglist>() const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual RCP&lt; const Thyra::DefaultMultiVectorProductVectorSpace&lt; Scalar &gt; &gt;</type>
      <name>get_s_bar_space</name>
      <anchorfile>classRythmos_1_1ForwardSensitivityModelEvaluatorBase.html</anchorfile>
      <anchor>a708576a574f75997c2fd686ac80f0d69</anchor>
      <arglist>() const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual RCP&lt; const Thyra::VectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>get_p_sens_space</name>
      <anchorfile>classRythmos_1_1ForwardSensitivityModelEvaluatorBase.html</anchorfile>
      <anchor>a82b94561827fc234fa0151199643ff32</anchor>
      <arglist>() const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>initializePointState</name>
      <anchorfile>classRythmos_1_1ForwardSensitivityModelEvaluatorBase.html</anchorfile>
      <anchor>ab7f4d2441858ca226b6a02dd6b2fd8be</anchor>
      <arglist>(Ptr&lt; StepperBase&lt; Scalar &gt; &gt; stateStepper, bool forceUpToDateW)=0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Rythmos::ForwardSensitivityStepper</name>
    <filename>classRythmos_1_1ForwardSensitivityStepper.html</filename>
    <templarg>Scalar</templarg>
    <base virtualness="virtual">Rythmos::StepperBase</base>
    <member kind="typedef">
      <type>Teuchos::ScalarTraits&lt; Scalar &gt;::magnitudeType</type>
      <name>ScalarMag</name>
      <anchorfile>classRythmos_1_1ForwardSensitivityStepper.html</anchorfile>
      <anchor>a388b58f7ae15bf5f4be7bc6c86971a9f</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; ForwardSensitivityStepper&lt; Scalar &gt; &gt;</type>
      <name>forwardSensitivityStepper</name>
      <anchorfile>classRythmos_1_1ForwardSensitivityStepper.html</anchorfile>
      <anchor>a4d24b85f62ed17a6c527e3cd26c3532a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; ForwardSensitivityStepper&lt; Scalar &gt; &gt;</type>
      <name>forwardSensitivityStepper</name>
      <anchorfile>classRythmos_1_1ForwardSensitivityStepper.html</anchorfile>
      <anchor>a7b551d5a30ea403447869e64e834954e</anchor>
      <arglist>(const RCP&lt; const Thyra::ModelEvaluator&lt; Scalar &gt; &gt; &amp;stateModel, const int p_index, const Thyra::ModelEvaluatorBase::InArgs&lt; Scalar &gt; &amp;stateBasePoint, const RCP&lt; StepperBase&lt; Scalar &gt; &gt; &amp;stateStepper, const RCP&lt; Thyra::NonlinearSolverBase&lt; Scalar &gt; &gt; &amp;stateTimeStepSolver, const RCP&lt; StepperBase&lt; Scalar &gt; &gt; &amp;sensStepper=Teuchos::null, const RCP&lt; Thyra::NonlinearSolverBase&lt; Scalar &gt; &gt; &amp;sensTimeStepSolver=Teuchos::null)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getParameterIndex</name>
      <anchorfile>classRythmos_1_1ForwardSensitivityStepper.html</anchorfile>
      <anchor>ae7fe16f59b688c4a9edd700896b939ba</anchor>
      <arglist>(const ForwardSensitivityStepper&lt; Scalar &gt; &amp;fwdSensStepper)</arglist>
    </member>
    <member kind="function">
      <type>Thyra::ModelEvaluatorBase::InArgs&lt; Scalar &gt;</type>
      <name>createStateAndSensInitialCondition</name>
      <anchorfile>classRythmos_1_1ForwardSensitivityStepper.html</anchorfile>
      <anchor>a4fb136a44faaf9ec2a6e788a62dfb0be</anchor>
      <arglist>(const ForwardSensitivityStepper&lt; Scalar &gt; &amp;fwdSensStepper, const Thyra::ModelEvaluatorBase::InArgs&lt; Scalar &gt; &amp;state_ic, const RCP&lt; const Thyra::MultiVectorBase&lt; Scalar &gt; &gt; S_init=Teuchos::null, const RCP&lt; const Thyra::MultiVectorBase&lt; Scalar &gt; &gt; S_dot_init=Teuchos::null)</arglist>
    </member>
    <member kind="function">
      <type>Thyra::ModelEvaluatorBase::InArgs&lt; Scalar &gt;</type>
      <name>extractStateInitialCondition</name>
      <anchorfile>classRythmos_1_1ForwardSensitivityStepper.html</anchorfile>
      <anchor>a6ea3f3ab1fe65ec41268b106444e6dbf</anchor>
      <arglist>(const ForwardSensitivityStepper&lt; Scalar &gt; &amp;fwdSensStepper, const Thyra::ModelEvaluatorBase::InArgs&lt; Scalar &gt; &amp;state_and_sens_ic)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ForwardSensitivityStepper</name>
      <anchorfile>classRythmos_1_1ForwardSensitivityStepper.html</anchorfile>
      <anchor>aa1ab602845ad996a7d54f216d97b2dbb</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initializeSyncedSteppers</name>
      <anchorfile>classRythmos_1_1ForwardSensitivityStepper.html</anchorfile>
      <anchor>a1a394814cbdc26b4d8cf2fe6780be321</anchor>
      <arglist>(const RCP&lt; const Thyra::ModelEvaluator&lt; Scalar &gt; &gt; &amp;stateModel, const int p_index, const Thyra::ModelEvaluatorBase::InArgs&lt; Scalar &gt; &amp;stateBasePoint, const RCP&lt; StepperBase&lt; Scalar &gt; &gt; &amp;stateStepper, const RCP&lt; Thyra::NonlinearSolverBase&lt; Scalar &gt; &gt; &amp;stateTimeStepSolver, const RCP&lt; StepperBase&lt; Scalar &gt; &gt; &amp;sensStepper=Teuchos::null, const RCP&lt; Thyra::NonlinearSolverBase&lt; Scalar &gt; &gt; &amp;sensTimeStepSolver=Teuchos::null)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initializeSyncedSteppersInitCondOnly</name>
      <anchorfile>classRythmos_1_1ForwardSensitivityStepper.html</anchorfile>
      <anchor>a54eddd3b31f51f46df6d0e00de4bfc57</anchor>
      <arglist>(const RCP&lt; const Thyra::ModelEvaluator&lt; Scalar &gt; &gt; &amp;stateModel, const RCP&lt; const Thyra::VectorSpaceBase&lt; Scalar &gt; &gt; &amp;p_space, const Thyra::ModelEvaluatorBase::InArgs&lt; Scalar &gt; &amp;stateBasePoint, const RCP&lt; StepperBase&lt; Scalar &gt; &gt; &amp;stateStepper, const RCP&lt; Thyra::NonlinearSolverBase&lt; Scalar &gt; &gt; &amp;stateTimeStepSolver, const RCP&lt; StepperBase&lt; Scalar &gt; &gt; &amp;sensStepper=Teuchos::null, const RCP&lt; Thyra::NonlinearSolverBase&lt; Scalar &gt; &gt; &amp;sensTimeStepSolver=Teuchos::null)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initializeDecoupledSteppers</name>
      <anchorfile>classRythmos_1_1ForwardSensitivityStepper.html</anchorfile>
      <anchor>a59dbbd3635e8c61ad0855aa1dcfe07d5</anchor>
      <arglist>(const RCP&lt; const Thyra::ModelEvaluator&lt; Scalar &gt; &gt; &amp;stateModel, const int p_index, const Thyra::ModelEvaluatorBase::InArgs&lt; Scalar &gt; &amp;stateBasePoint, const RCP&lt; StepperBase&lt; Scalar &gt; &gt; &amp;stateStepper, const RCP&lt; Thyra::NonlinearSolverBase&lt; Scalar &gt; &gt; &amp;stateTimeStepSolver, const RCP&lt; IntegratorBase&lt; Scalar &gt; &gt; &amp;stateIntegrator, const Scalar &amp;finalTime, const RCP&lt; StepperBase&lt; Scalar &gt; &gt; &amp;sensStepper=Teuchos::null, const RCP&lt; Thyra::NonlinearSolverBase&lt; Scalar &gt; &gt; &amp;sensTimeStepSolver=Teuchos::null)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>stateModelIsConst</name>
      <anchorfile>classRythmos_1_1ForwardSensitivityStepper.html</anchorfile>
      <anchor>ae7ca3ea1d3304c4cf7d79273dc8af2c1</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const Thyra::ModelEvaluator&lt; Scalar &gt; &gt;</type>
      <name>getStateModel</name>
      <anchorfile>classRythmos_1_1ForwardSensitivityStepper.html</anchorfile>
      <anchor>a7574976b9466c33d93538ea69105e36b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; StepperBase&lt; Scalar &gt; &gt;</type>
      <name>getNonconstStateStepper</name>
      <anchorfile>classRythmos_1_1ForwardSensitivityStepper.html</anchorfile>
      <anchor>addc249817ab69611eb2986731c5b9544</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const ForwardSensitivityModelEvaluatorBase&lt; Scalar &gt; &gt;</type>
      <name>getFwdSensModel</name>
      <anchorfile>classRythmos_1_1ForwardSensitivityStepper.html</anchorfile>
      <anchor>a6c2cb05c3c9053fe68a1b9b51d74fd1e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const StateAndForwardSensitivityModelEvaluator&lt; Scalar &gt; &gt;</type>
      <name>getStateAndFwdSensModel</name>
      <anchorfile>classRythmos_1_1ForwardSensitivityStepper.html</anchorfile>
      <anchor>a741a9c1f19fb1f901ba1e39b95810f26</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setParameterList</name>
      <anchorfile>classRythmos_1_1ForwardSensitivityStepper.html</anchorfile>
      <anchor>af6fa254aa50ae817d7f51ee87840f413</anchor>
      <arglist>(RCP&lt; Teuchos::ParameterList &gt; const &amp;paramList)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const Teuchos::ParameterList &gt;</type>
      <name>getValidParameters</name>
      <anchorfile>classRythmos_1_1ForwardSensitivityStepper.html</anchorfile>
      <anchor>a80f863cb918f1a380786e2cd67392220</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>acceptsModel</name>
      <anchorfile>classRythmos_1_1ForwardSensitivityStepper.html</anchorfile>
      <anchor>a5322a57592719284a6afbcb2b85f9033</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setModel</name>
      <anchorfile>classRythmos_1_1ForwardSensitivityStepper.html</anchorfile>
      <anchor>a4b6a1331f29b253589d6c02ec4326814</anchor>
      <arglist>(const RCP&lt; const Thyra::ModelEvaluator&lt; Scalar &gt; &gt; &amp;model)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setNonconstModel</name>
      <anchorfile>classRythmos_1_1ForwardSensitivityStepper.html</anchorfile>
      <anchor>a8770ea24b5c1ad38ca847d5363e9e218</anchor>
      <arglist>(const RCP&lt; Thyra::ModelEvaluator&lt; Scalar &gt; &gt; &amp;model)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const Thyra::ModelEvaluator&lt; Scalar &gt; &gt;</type>
      <name>getModel</name>
      <anchorfile>classRythmos_1_1ForwardSensitivityStepper.html</anchorfile>
      <anchor>ad45d808d4c6e5150abc984eff8ec4416</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; Thyra::ModelEvaluator&lt; Scalar &gt; &gt;</type>
      <name>getNonconstModel</name>
      <anchorfile>classRythmos_1_1ForwardSensitivityStepper.html</anchorfile>
      <anchor>a25a569b5d5e66088543a3f0561b850b9</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setInitialCondition</name>
      <anchorfile>classRythmos_1_1ForwardSensitivityStepper.html</anchorfile>
      <anchor>ac412ad182b191bd7d648d7a5a0dcada3</anchor>
      <arglist>(const Thyra::ModelEvaluatorBase::InArgs&lt; Scalar &gt; &amp;state_and_sens_ic)</arglist>
    </member>
    <member kind="function">
      <type>Thyra::ModelEvaluatorBase::InArgs&lt; Scalar &gt;</type>
      <name>getInitialCondition</name>
      <anchorfile>classRythmos_1_1ForwardSensitivityStepper.html</anchorfile>
      <anchor>a542004009b6e36f218441f240ad50c05</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Scalar</type>
      <name>takeStep</name>
      <anchorfile>classRythmos_1_1ForwardSensitivityStepper.html</anchorfile>
      <anchor>a8c9621ed52c3c82adb132153a3b30832</anchor>
      <arglist>(Scalar dt, StepSizeType stepType)</arglist>
    </member>
    <member kind="function">
      <type>const StepStatus&lt; Scalar &gt;</type>
      <name>getStepStatus</name>
      <anchorfile>classRythmos_1_1ForwardSensitivityStepper.html</anchorfile>
      <anchor>aca71ea45f5456d2508dcbfa2f48528fb</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const Thyra::VectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>get_x_space</name>
      <anchorfile>classRythmos_1_1ForwardSensitivityStepper.html</anchorfile>
      <anchor>ab1484e02567566a49a95def7e1efeb1b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>addPoints</name>
      <anchorfile>classRythmos_1_1ForwardSensitivityStepper.html</anchorfile>
      <anchor>a922216a0164ea91ed60fa0f73d003b94</anchor>
      <arglist>(const Array&lt; Scalar &gt; &amp;time_vec, const Array&lt; Teuchos::RCP&lt; const Thyra::VectorBase&lt; Scalar &gt; &gt; &gt; &amp;x_vec, const Array&lt; Teuchos::RCP&lt; const Thyra::VectorBase&lt; Scalar &gt; &gt; &gt; &amp;xdot_vec)</arglist>
    </member>
    <member kind="function">
      <type>TimeRange&lt; Scalar &gt;</type>
      <name>getTimeRange</name>
      <anchorfile>classRythmos_1_1ForwardSensitivityStepper.html</anchorfile>
      <anchor>a3a7ffadd64afd44c31921c77602fb67b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>getPoints</name>
      <anchorfile>classRythmos_1_1ForwardSensitivityStepper.html</anchorfile>
      <anchor>a6a2f6f5a245cdcb0ed813e757e109877</anchor>
      <arglist>(const Array&lt; Scalar &gt; &amp;time_vec, Array&lt; RCP&lt; const Thyra::VectorBase&lt; Scalar &gt; &gt; &gt; *x_vec, Array&lt; RCP&lt; const Thyra::VectorBase&lt; Scalar &gt; &gt; &gt; *xdot_vec, Array&lt; ScalarMag &gt; *accuracy_vec) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>getNodes</name>
      <anchorfile>classRythmos_1_1ForwardSensitivityStepper.html</anchorfile>
      <anchor>a01c30963ec5211e9acd03861dffc87e3</anchor>
      <arglist>(Array&lt; Scalar &gt; *time_vec) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>removeNodes</name>
      <anchorfile>classRythmos_1_1ForwardSensitivityStepper.html</anchorfile>
      <anchor>aa753fbbf4670f806ba643984c97a78f3</anchor>
      <arglist>(Array&lt; Scalar &gt; &amp;time_vec)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getOrder</name>
      <anchorfile>classRythmos_1_1ForwardSensitivityStepper.html</anchorfile>
      <anchor>a5c31ac3f0bca16b45f085b9d71e419dc</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initialize</name>
      <anchorfile>classRythmos_1_1ForwardSensitivityStepper.html</anchorfile>
      <anchor>a9b51226e2b0e5e954306e2cce3f9f163</anchor>
      <arglist>(const RCP&lt; const Thyra::ModelEvaluator&lt; Scalar &gt; &gt; &amp;stateModel, const int p_index, const Thyra::ModelEvaluatorBase::InArgs&lt; Scalar &gt; &amp;stateBasePoint, const RCP&lt; StepperBase&lt; Scalar &gt; &gt; &amp;stateStepper, const RCP&lt; Thyra::NonlinearSolverBase&lt; Scalar &gt; &gt; &amp;stateTimeStepSolver, const RCP&lt; StepperBase&lt; Scalar &gt; &gt; &amp;sensStepper=Teuchos::null, const RCP&lt; Thyra::NonlinearSolverBase&lt; Scalar &gt; &gt; &amp;sensTimeStepSolver=Teuchos::null)</arglist>
    </member>
    <docanchor file="classRythmos_1_1ForwardSensitivityStepper" title="Introduction">Rythmos_ForwardSensitivityStepper_intro_sec</docanchor>
    <docanchor file="classRythmos_1_1ForwardSensitivityStepper" title="Implementation Details">Rythmos_ForwardSensitivityStepper_details_sec</docanchor>
  </compound>
  <compound kind="class">
    <name>Rythmos::ForwardSensitivityStepperTester</name>
    <filename>classRythmos_1_1ForwardSensitivityStepperTester.html</filename>
    <templarg></templarg>
    <member kind="function">
      <type>RCP&lt; ForwardSensitivityStepperTester&lt; Scalar &gt; &gt;</type>
      <name>forwardSensitivityStepperTester</name>
      <anchorfile>classRythmos_1_1ForwardSensitivityStepperTester.html</anchorfile>
      <anchor>a9302fc8c06291a79632983409bca96fd</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; ForwardSensitivityStepperTester&lt; Scalar &gt; &gt;</type>
      <name>forwardSensitivityStepperTester</name>
      <anchorfile>classRythmos_1_1ForwardSensitivityStepperTester.html</anchorfile>
      <anchor>abdb1f4237bacc5989802948b9bbefcd7</anchor>
      <arglist>(const RCP&lt; ParameterList &gt; &amp;paramList)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setParameterList</name>
      <anchorfile>classRythmos_1_1ForwardSensitivityStepperTester.html</anchorfile>
      <anchor>a7790085cd01448d4f1413390971c0eaa</anchor>
      <arglist>(RCP&lt; ParameterList &gt; const &amp;paramList)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const ParameterList &gt;</type>
      <name>getValidParameters</name>
      <anchorfile>classRythmos_1_1ForwardSensitivityStepperTester.html</anchorfile>
      <anchor>ab689300ff38360a8085a77832592602b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>testForwardSens</name>
      <anchorfile>classRythmos_1_1ForwardSensitivityStepperTester.html</anchorfile>
      <anchor>af56b73254478a827afdb68dad9282ba4</anchor>
      <arglist>(const Ptr&lt; IntegratorBase&lt; Scalar &gt; &gt; &amp;fwdSensIntegrator)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Rythmos::GaussQuadrature1D</name>
    <filename>classRythmos_1_1GaussQuadrature1D.html</filename>
    <templarg>Scalar</templarg>
  </compound>
  <compound kind="class">
    <name>Rythmos::Exceptions::GetFwdPointsFailed</name>
    <filename>classRythmos_1_1Exceptions_1_1GetFwdPointsFailed.html</filename>
    <base>Rythmos::Exceptions::ExceptionBase</base>
  </compound>
  <compound kind="class">
    <name>Rythmos::HermiteInterpolator</name>
    <filename>classRythmos_1_1HermiteInterpolator.html</filename>
    <templarg></templarg>
    <base virtualness="virtual">Rythmos::InterpolatorBase</base>
    <member kind="function">
      <type></type>
      <name>~HermiteInterpolator</name>
      <anchorfile>classRythmos_1_1HermiteInterpolator.html</anchorfile>
      <anchor>a6cf1ce732766fcaf778918481064d0b3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>HermiteInterpolator</name>
      <anchorfile>classRythmos_1_1HermiteInterpolator.html</anchorfile>
      <anchor>a4a2121f82b6ad184792ae9cc008402aa</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setNodes</name>
      <anchorfile>classRythmos_1_1HermiteInterpolator.html</anchorfile>
      <anchor>a5adc1bb9fcedfa271b89035abfca2598</anchor>
      <arglist>(const RCP&lt; const typename DataStore&lt; Scalar &gt;::DataStoreVector_t &gt; &amp;nodes)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>interpolate</name>
      <anchorfile>classRythmos_1_1HermiteInterpolator.html</anchorfile>
      <anchor>ac594c356dc46eef1710237102aef87e7</anchor>
      <arglist>(const Array&lt; Scalar &gt; &amp;t_values, typename DataStore&lt; Scalar &gt;::DataStoreVector_t *data_out) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>order</name>
      <anchorfile>classRythmos_1_1HermiteInterpolator.html</anchorfile>
      <anchor>acceb31c9363112fdec028919b75ba708</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>description</name>
      <anchorfile>classRythmos_1_1HermiteInterpolator.html</anchorfile>
      <anchor>ad18be51069805cfc6fb2c30a494abe2e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>describe</name>
      <anchorfile>classRythmos_1_1HermiteInterpolator.html</anchorfile>
      <anchor>ab9f8fdf9d69a198a1851cc975cc2b876</anchor>
      <arglist>(Teuchos::FancyOStream &amp;out, const Teuchos::EVerbosityLevel verbLevel) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setParameterList</name>
      <anchorfile>classRythmos_1_1HermiteInterpolator.html</anchorfile>
      <anchor>a5a012cc0702119060c198e1ba18786d4</anchor>
      <arglist>(RCP&lt; ParameterList &gt; const &amp;paramList)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; ParameterList &gt;</type>
      <name>getNonconstParameterList</name>
      <anchorfile>classRythmos_1_1HermiteInterpolator.html</anchorfile>
      <anchor>a75de4decad367be4ab3a30863ff471af</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; ParameterList &gt;</type>
      <name>unsetParameterList</name>
      <anchorfile>classRythmos_1_1HermiteInterpolator.html</anchorfile>
      <anchor>a38cf6589c956752cd7f715c4767a1aeb</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const Teuchos::ParameterList &gt;</type>
      <name>getValidParameters</name>
      <anchorfile>classRythmos_1_1HermiteInterpolator.html</anchorfile>
      <anchor>a22f1f6902c309350ee450ba1dc841775</anchor>
      <arglist>() const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Rythmos::ImplicitBDFStepper</name>
    <filename>classRythmos_1_1ImplicitBDFStepper.html</filename>
    <templarg>Scalar</templarg>
    <base virtualness="virtual">Rythmos::SolverAcceptingStepperBase</base>
    <base virtualness="virtual">Rythmos::StepControlStrategyAcceptingStepperBase</base>
    <member kind="typedef">
      <type>Teuchos::ScalarTraits&lt; Scalar &gt;::magnitudeType</type>
      <name>ScalarMag</name>
      <anchorfile>classRythmos_1_1ImplicitBDFStepper.html</anchorfile>
      <anchor>a960374a70a55ce5faefd65f515c14f7c</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>const Thyra::SolveStatus&lt; Scalar &gt; &amp;</type>
      <name>getNonlinearSolveStatus</name>
      <anchorfile>classRythmos_1_1ImplicitBDFStepper.html</anchorfile>
      <anchor>a57a39ba9c863b964858e00bbb119bd8d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ImplicitBDFStepper</name>
      <anchorfile>classRythmos_1_1ImplicitBDFStepper.html</anchorfile>
      <anchor>a44b60905e08e47aa0821502ae6d4e44c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ImplicitBDFStepper</name>
      <anchorfile>classRythmos_1_1ImplicitBDFStepper.html</anchorfile>
      <anchor>a658322828f2848bae811acecd3b139b0</anchor>
      <arglist>(const RCP&lt; Thyra::ModelEvaluator&lt; Scalar &gt; &gt; &amp;model, const RCP&lt; Thyra::NonlinearSolverBase&lt; Scalar &gt; &gt; &amp;solver)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ImplicitBDFStepper</name>
      <anchorfile>classRythmos_1_1ImplicitBDFStepper.html</anchorfile>
      <anchor>a23b3385415bc7a463d415f94db4d4862</anchor>
      <arglist>(const RCP&lt; Thyra::ModelEvaluator&lt; Scalar &gt; &gt; &amp;model, const RCP&lt; Thyra::NonlinearSolverBase&lt; Scalar &gt; &gt; &amp;solver, const RCP&lt; Teuchos::ParameterList &gt; &amp;parameterList)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const Thyra::VectorBase&lt; Scalar &gt; &gt;</type>
      <name>get_solution</name>
      <anchorfile>classRythmos_1_1ImplicitBDFStepper.html</anchorfile>
      <anchor>a4ab5a3a8f35f58e00ac43841b0e40a11</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const Thyra::VectorBase&lt; Scalar &gt; &gt;</type>
      <name>get_residual</name>
      <anchorfile>classRythmos_1_1ImplicitBDFStepper.html</anchorfile>
      <anchor>a9ca145d18f312b77ef8f0b8e8787dade</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Thyra::VectorBase&lt; Scalar &gt; &amp;</type>
      <name>getxHistory</name>
      <anchorfile>classRythmos_1_1ImplicitBDFStepper.html</anchorfile>
      <anchor>adfac0fbc724e8df29fcbe8944f54a78a</anchor>
      <arglist>(int index) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setStepControlData</name>
      <anchorfile>classRythmos_1_1ImplicitBDFStepper.html</anchorfile>
      <anchor>aed13088fc2b1cb7449ddca0be951bd92</anchor>
      <arglist>(const StepperBase&lt; Scalar &gt; &amp;stepper)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setStepControlStrategy</name>
      <anchorfile>classRythmos_1_1ImplicitBDFStepper.html</anchorfile>
      <anchor>a7469e7fcca2e8805f66078e36844ebb4</anchor>
      <arglist>(const RCP&lt; StepControlStrategyBase&lt; Scalar &gt; &gt; &amp;stepControlStrategy)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; StepControlStrategyBase&lt; Scalar &gt; &gt;</type>
      <name>getNonconstStepControlStrategy</name>
      <anchorfile>classRythmos_1_1ImplicitBDFStepper.html</anchorfile>
      <anchor>a8e6603e6abdb57af3fe3caae34b2ec4c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const StepControlStrategyBase&lt; Scalar &gt; &gt;</type>
      <name>getStepControlStrategy</name>
      <anchorfile>classRythmos_1_1ImplicitBDFStepper.html</anchorfile>
      <anchor>a1a561c6d09ee71d989f9fc67fae8b407</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setSolver</name>
      <anchorfile>classRythmos_1_1ImplicitBDFStepper.html</anchorfile>
      <anchor>afb9c9e30bc12466567daf2dcb62ae260</anchor>
      <arglist>(const RCP&lt; Thyra::NonlinearSolverBase&lt; Scalar &gt; &gt; &amp;solver)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; Thyra::NonlinearSolverBase&lt; Scalar &gt; &gt;</type>
      <name>getNonconstSolver</name>
      <anchorfile>classRythmos_1_1ImplicitBDFStepper.html</anchorfile>
      <anchor>a8f59badd0b26171c0fe85f418643b31b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const Thyra::NonlinearSolverBase&lt; Scalar &gt; &gt;</type>
      <name>getSolver</name>
      <anchorfile>classRythmos_1_1ImplicitBDFStepper.html</anchorfile>
      <anchor>a1f9bfa543eee7350b9f5be6955dfbe91</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isImplicit</name>
      <anchorfile>classRythmos_1_1ImplicitBDFStepper.html</anchorfile>
      <anchor>a61e4b91511a184a4d8a9fa4b9e741721</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>supportsCloning</name>
      <anchorfile>classRythmos_1_1ImplicitBDFStepper.html</anchorfile>
      <anchor>a3accb46f1a8814d2492e91d536baa12d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; StepperBase&lt; Scalar &gt; &gt;</type>
      <name>cloneStepperAlgorithm</name>
      <anchorfile>classRythmos_1_1ImplicitBDFStepper.html</anchorfile>
      <anchor>a084747fa547092f468bf9e7ecea8e0d4</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setModel</name>
      <anchorfile>classRythmos_1_1ImplicitBDFStepper.html</anchorfile>
      <anchor>a25c30ac72c058356b9373873a98e658a</anchor>
      <arglist>(const RCP&lt; const Thyra::ModelEvaluator&lt; Scalar &gt; &gt; &amp;model)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setNonconstModel</name>
      <anchorfile>classRythmos_1_1ImplicitBDFStepper.html</anchorfile>
      <anchor>a71761d9792145440aae5a39408708c60</anchor>
      <arglist>(const RCP&lt; Thyra::ModelEvaluator&lt; Scalar &gt; &gt; &amp;model)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const Thyra::ModelEvaluator&lt; Scalar &gt; &gt;</type>
      <name>getModel</name>
      <anchorfile>classRythmos_1_1ImplicitBDFStepper.html</anchorfile>
      <anchor>aa4735d58ef735a79cf39cb24b6e5ba29</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; Thyra::ModelEvaluator&lt; Scalar &gt; &gt;</type>
      <name>getNonconstModel</name>
      <anchorfile>classRythmos_1_1ImplicitBDFStepper.html</anchorfile>
      <anchor>a01bd9476fd4b0255753334371ecd049f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setInitialCondition</name>
      <anchorfile>classRythmos_1_1ImplicitBDFStepper.html</anchorfile>
      <anchor>aa98eb2ff6de944cb1a9d2420aac29037</anchor>
      <arglist>(const Thyra::ModelEvaluatorBase::InArgs&lt; Scalar &gt; &amp;initialCondition)</arglist>
    </member>
    <member kind="function">
      <type>Thyra::ModelEvaluatorBase::InArgs&lt; Scalar &gt;</type>
      <name>getInitialCondition</name>
      <anchorfile>classRythmos_1_1ImplicitBDFStepper.html</anchorfile>
      <anchor>a05693c59b80acf290ab21f06c51f69df</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Scalar</type>
      <name>takeStep</name>
      <anchorfile>classRythmos_1_1ImplicitBDFStepper.html</anchorfile>
      <anchor>a9da3bec9ec9d4d858d86c336502bec4e</anchor>
      <arglist>(Scalar dt, StepSizeType flag)</arglist>
    </member>
    <member kind="function">
      <type>const StepStatus&lt; Scalar &gt;</type>
      <name>getStepStatus</name>
      <anchorfile>classRythmos_1_1ImplicitBDFStepper.html</anchorfile>
      <anchor>abd1098fa47e0f47d279dc77bff3b6775</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const Thyra::VectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>get_x_space</name>
      <anchorfile>classRythmos_1_1ImplicitBDFStepper.html</anchorfile>
      <anchor>a98cea434bc5f4382408c905214d329a1</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>addPoints</name>
      <anchorfile>classRythmos_1_1ImplicitBDFStepper.html</anchorfile>
      <anchor>a04eb92f1b0f940e572f320460e883873</anchor>
      <arglist>(const Array&lt; Scalar &gt; &amp;time_vec, const Array&lt; RCP&lt; const Thyra::VectorBase&lt; Scalar &gt; &gt; &gt; &amp;x_vec, const Array&lt; RCP&lt; const Thyra::VectorBase&lt; Scalar &gt; &gt; &gt; &amp;xdot_vec)</arglist>
    </member>
    <member kind="function">
      <type>TimeRange&lt; Scalar &gt;</type>
      <name>getTimeRange</name>
      <anchorfile>classRythmos_1_1ImplicitBDFStepper.html</anchorfile>
      <anchor>a516a0803bf89928102eee5c91b798a75</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>getPoints</name>
      <anchorfile>classRythmos_1_1ImplicitBDFStepper.html</anchorfile>
      <anchor>a573012294b2daa1f4abe7e417ffcb018</anchor>
      <arglist>(const Array&lt; Scalar &gt; &amp;time_vec, Array&lt; RCP&lt; const Thyra::VectorBase&lt; Scalar &gt; &gt; &gt; *x_vec, Array&lt; RCP&lt; const Thyra::VectorBase&lt; Scalar &gt; &gt; &gt; *xdot_vec, Array&lt; ScalarMag &gt; *accuracy_vec) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>getNodes</name>
      <anchorfile>classRythmos_1_1ImplicitBDFStepper.html</anchorfile>
      <anchor>a707b1b881650792467f6a19fdd49d9b2</anchor>
      <arglist>(Array&lt; Scalar &gt; *time_vec) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>removeNodes</name>
      <anchorfile>classRythmos_1_1ImplicitBDFStepper.html</anchorfile>
      <anchor>ad73138377357cfddb9c5d69053c88945</anchor>
      <arglist>(Array&lt; Scalar &gt; &amp;time_vec)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getOrder</name>
      <anchorfile>classRythmos_1_1ImplicitBDFStepper.html</anchorfile>
      <anchor>acf3bb8464e1d8111c9e371a83c6ed001</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setParameterList</name>
      <anchorfile>classRythmos_1_1ImplicitBDFStepper.html</anchorfile>
      <anchor>a60946b0fd1ff03d2b856aa0a08cd94c5</anchor>
      <arglist>(RCP&lt; Teuchos::ParameterList &gt; const &amp;paramList)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; Teuchos::ParameterList &gt;</type>
      <name>getNonconstParameterList</name>
      <anchorfile>classRythmos_1_1ImplicitBDFStepper.html</anchorfile>
      <anchor>a40fefdaffc8cde628e93cc18cf276e4f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; Teuchos::ParameterList &gt;</type>
      <name>unsetParameterList</name>
      <anchorfile>classRythmos_1_1ImplicitBDFStepper.html</anchorfile>
      <anchor>aa88f23d4561cb2efd86704fdeee5dee8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const Teuchos::ParameterList &gt;</type>
      <name>getValidParameters</name>
      <anchorfile>classRythmos_1_1ImplicitBDFStepper.html</anchorfile>
      <anchor>aac89030ebecb5e48644d330c6aaa9a34</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>description</name>
      <anchorfile>classRythmos_1_1ImplicitBDFStepper.html</anchorfile>
      <anchor>a17e7f3c8d622e8b4a518428f4221d0f7</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>describe</name>
      <anchorfile>classRythmos_1_1ImplicitBDFStepper.html</anchorfile>
      <anchor>a60917ab0f87f5dacc59a06c7bc4c80bf</anchor>
      <arglist>(Teuchos::FancyOStream &amp;out, const Teuchos::EVerbosityLevel verbLevel) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Rythmos::ImplicitBDFStepperRampingStepControl</name>
    <filename>classRythmos_1_1ImplicitBDFStepperRampingStepControl.html</filename>
    <templarg></templarg>
    <base virtualness="virtual">Rythmos::ErrWtVecCalcAcceptingStepControlStrategyBase</base>
    <member kind="function">
      <type>void</type>
      <name>initialize</name>
      <anchorfile>classRythmos_1_1ImplicitBDFStepperRampingStepControl.html</anchorfile>
      <anchor>aa79f54eec88887c6bf7462d7cfd03c7d</anchor>
      <arglist>(const StepperBase&lt; Scalar &gt; &amp;stepper)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setRequestedStepSize</name>
      <anchorfile>classRythmos_1_1ImplicitBDFStepperRampingStepControl.html</anchorfile>
      <anchor>a9a50826eb54438f3b41d4f9dc1963d98</anchor>
      <arglist>(const StepperBase&lt; Scalar &gt; &amp;stepper, const Scalar &amp;stepSize, const StepSizeType &amp;stepSizeType)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>nextStepSize</name>
      <anchorfile>classRythmos_1_1ImplicitBDFStepperRampingStepControl.html</anchorfile>
      <anchor>a316d1c7142d03b2867eb24fa76eb9fe9</anchor>
      <arglist>(const StepperBase&lt; Scalar &gt; &amp;stepper, Scalar *stepSize, StepSizeType *stepSizeType, int *order)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setCorrection</name>
      <anchorfile>classRythmos_1_1ImplicitBDFStepperRampingStepControl.html</anchorfile>
      <anchor>aa0a15473207a788d1f74a4fee0445ce7</anchor>
      <arglist>(const StepperBase&lt; Scalar &gt; &amp;stepper, const RCP&lt; const Thyra::VectorBase&lt; Scalar &gt; &gt; &amp;soln, const RCP&lt; const Thyra::VectorBase&lt; Scalar &gt; &gt; &amp;ee, int solveStatus)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>acceptStep</name>
      <anchorfile>classRythmos_1_1ImplicitBDFStepperRampingStepControl.html</anchorfile>
      <anchor>a10351f9e4c3a225e48b2fb83b5533d32</anchor>
      <arglist>(const StepperBase&lt; Scalar &gt; &amp;stepper, Scalar *LETValue)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>completeStep</name>
      <anchorfile>classRythmos_1_1ImplicitBDFStepperRampingStepControl.html</anchorfile>
      <anchor>a58f2cdb51b8474d5fbab5571505be345</anchor>
      <arglist>(const StepperBase&lt; Scalar &gt; &amp;stepper)</arglist>
    </member>
    <member kind="function">
      <type>AttemptedStepStatusFlag</type>
      <name>rejectStep</name>
      <anchorfile>classRythmos_1_1ImplicitBDFStepperRampingStepControl.html</anchorfile>
      <anchor>ae08f175e31f68325b44d2daa56993445</anchor>
      <arglist>(const StepperBase&lt; Scalar &gt; &amp;stepper)</arglist>
    </member>
    <member kind="function">
      <type>StepControlStrategyState</type>
      <name>getCurrentState</name>
      <anchorfile>classRythmos_1_1ImplicitBDFStepperRampingStepControl.html</anchorfile>
      <anchor>a697d541ffcf187fef7aa8b7d915b559e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getMinOrder</name>
      <anchorfile>classRythmos_1_1ImplicitBDFStepperRampingStepControl.html</anchorfile>
      <anchor>ab5a930b8cbd3c3988660148d74bc8344</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getMaxOrder</name>
      <anchorfile>classRythmos_1_1ImplicitBDFStepperRampingStepControl.html</anchorfile>
      <anchor>a6b6c5ee9e4ba5ec7b53c5cf4b71f5087</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setStepControlData</name>
      <anchorfile>classRythmos_1_1ImplicitBDFStepperRampingStepControl.html</anchorfile>
      <anchor>a395ec0865291dd131123d8c7377f1518</anchor>
      <arglist>(const StepperBase&lt; Scalar &gt; &amp;stepper)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>supportsCloning</name>
      <anchorfile>classRythmos_1_1ImplicitBDFStepperRampingStepControl.html</anchorfile>
      <anchor>a3e90e46029cf9fedbb8d7120c836d1fa</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; StepControlStrategyBase&lt; Scalar &gt; &gt;</type>
      <name>cloneStepControlStrategyAlgorithm</name>
      <anchorfile>classRythmos_1_1ImplicitBDFStepperRampingStepControl.html</anchorfile>
      <anchor>a7db42c49f00009c3195d9122ae2086e8</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setErrWtVecCalc</name>
      <anchorfile>classRythmos_1_1ImplicitBDFStepperRampingStepControl.html</anchorfile>
      <anchor>a8a379a3e4e520e185579022d71572933</anchor>
      <arglist>(const RCP&lt; ErrWtVecCalcBase&lt; Scalar &gt; &gt; &amp;errWtVecCalc)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const ErrWtVecCalcBase&lt; Scalar &gt; &gt;</type>
      <name>getErrWtVecCalc</name>
      <anchorfile>classRythmos_1_1ImplicitBDFStepperRampingStepControl.html</anchorfile>
      <anchor>a278f2e1dd0b52cefc2f4b5650fc205b1</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>describe</name>
      <anchorfile>classRythmos_1_1ImplicitBDFStepperRampingStepControl.html</anchorfile>
      <anchor>a685570f41ce17e65f31d81e1eb0e31d8</anchor>
      <arglist>(Teuchos::FancyOStream &amp;out, const Teuchos::EVerbosityLevel verbLevel) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setParameterList</name>
      <anchorfile>classRythmos_1_1ImplicitBDFStepperRampingStepControl.html</anchorfile>
      <anchor>ab0ffa47c76a26186ef5f07c9813ebbc8</anchor>
      <arglist>(RCP&lt; Teuchos::ParameterList &gt; const &amp;paramList)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; Teuchos::ParameterList &gt;</type>
      <name>getNonconstParameterList</name>
      <anchorfile>classRythmos_1_1ImplicitBDFStepperRampingStepControl.html</anchorfile>
      <anchor>aff25756005084bfb845ead6562463398</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; Teuchos::ParameterList &gt;</type>
      <name>unsetParameterList</name>
      <anchorfile>classRythmos_1_1ImplicitBDFStepperRampingStepControl.html</anchorfile>
      <anchor>a4e61e7c7225f7046d3118d0478bcc5e9</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const Teuchos::ParameterList &gt;</type>
      <name>getValidParameters</name>
      <anchorfile>classRythmos_1_1ImplicitBDFStepperRampingStepControl.html</anchorfile>
      <anchor>abcdf02ee76a60543cfeeedd5c479b4ae</anchor>
      <arglist>() const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Rythmos::ImplicitRKModelEvaluator</name>
    <filename>classRythmos_1_1ImplicitRKModelEvaluator.html</filename>
    <templarg></templarg>
    <member kind="function">
      <type>RCP&lt; ImplicitRKModelEvaluator&lt; Scalar &gt; &gt;</type>
      <name>implicitRKModelEvaluator</name>
      <anchorfile>classRythmos_1_1ImplicitRKModelEvaluator.html</anchorfile>
      <anchor>af0e23261847d34d207d1c15e0bc38afa</anchor>
      <arglist>(const RCP&lt; const Thyra::ModelEvaluator&lt; Scalar &gt; &gt; &amp;daeModel, const Thyra::ModelEvaluatorBase::InArgs&lt; Scalar &gt; &amp;basePoint, const RCP&lt; Thyra::LinearOpWithSolveFactoryBase&lt; Scalar &gt; &gt; &amp;irk_W_factory, const RCP&lt; const RKButcherTableauBase&lt; Scalar &gt; &gt; &amp;irkButcherTableau)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ImplicitRKModelEvaluator</name>
      <anchorfile>classRythmos_1_1ImplicitRKModelEvaluator.html</anchorfile>
      <anchor>a5cb160a8806d3482271080d224e5a085</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initializeIRKModel</name>
      <anchorfile>classRythmos_1_1ImplicitRKModelEvaluator.html</anchorfile>
      <anchor>ab07e4c039a495bb0a089d18603424769</anchor>
      <arglist>(const RCP&lt; const Thyra::ModelEvaluator&lt; Scalar &gt; &gt; &amp;daeModel, const Thyra::ModelEvaluatorBase::InArgs&lt; Scalar &gt; &amp;basePoint, const RCP&lt; Thyra::LinearOpWithSolveFactoryBase&lt; Scalar &gt; &gt; &amp;irk_W_factory, const RCP&lt; const RKButcherTableauBase&lt; Scalar &gt; &gt; &amp;irkButcherTableau)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setTimeStepPoint</name>
      <anchorfile>classRythmos_1_1ImplicitRKModelEvaluator.html</anchorfile>
      <anchor>aff268c4bdb0e6626910e029d513fee90</anchor>
      <arglist>(const RCP&lt; const Thyra::VectorBase&lt; Scalar &gt; &gt; &amp;x_old, const Scalar &amp;t_old, const Scalar &amp;delta_t)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const Thyra::VectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>get_x_space</name>
      <anchorfile>classRythmos_1_1ImplicitRKModelEvaluator.html</anchorfile>
      <anchor>a0b2e67efa384835f122066638f2605d4</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const Thyra::VectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>get_f_space</name>
      <anchorfile>classRythmos_1_1ImplicitRKModelEvaluator.html</anchorfile>
      <anchor>a17b95cd566b7ab677ecdd0b023bc6a44</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; Thyra::LinearOpBase&lt; Scalar &gt; &gt;</type>
      <name>create_W_op</name>
      <anchorfile>classRythmos_1_1ImplicitRKModelEvaluator.html</anchorfile>
      <anchor>a2f6264cbe541ef75d6a27d0ac6fb7633</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const Thyra::LinearOpWithSolveFactoryBase&lt; Scalar &gt; &gt;</type>
      <name>get_W_factory</name>
      <anchorfile>classRythmos_1_1ImplicitRKModelEvaluator.html</anchorfile>
      <anchor>a5938de64ec0358d88cd4d2b07d7554f7</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Thyra::ModelEvaluatorBase::InArgs&lt; Scalar &gt;</type>
      <name>getNominalValues</name>
      <anchorfile>classRythmos_1_1ImplicitRKModelEvaluator.html</anchorfile>
      <anchor>a6b909e43b470dea3e8d28616982b8bc2</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Thyra::ModelEvaluatorBase::InArgs&lt; Scalar &gt;</type>
      <name>createInArgs</name>
      <anchorfile>classRythmos_1_1ImplicitRKModelEvaluator.html</anchorfile>
      <anchor>a51799fcb4372d2ddae2bd685d55b1263</anchor>
      <arglist>() const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Rythmos::ImplicitRKStepper</name>
    <filename>classRythmos_1_1ImplicitRKStepper.html</filename>
    <templarg></templarg>
    <base virtualness="virtual">Rythmos::SolverAcceptingStepperBase</base>
    <base virtualness="virtual">Rythmos::RKButcherTableauAcceptingStepperBase</base>
    <base virtualness="virtual">Rythmos::StepControlStrategyAcceptingStepperBase</base>
    <member kind="typedef">
      <type>ScalarTraits&lt; Scalar &gt;::magnitudeType</type>
      <name>ScalarMag</name>
      <anchorfile>classRythmos_1_1ImplicitRKStepper.html</anchorfile>
      <anchor>abd475f483e5f3aaf86706604f7f9ad57</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setDirk</name>
      <anchorfile>classRythmos_1_1ImplicitRKStepper.html</anchorfile>
      <anchor>af84bbb53edc109f21cfefd2cd1a81235</anchor>
      <arglist>(bool isDirk)</arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>isEmbeddedRK_</name>
      <anchorfile>classRythmos_1_1ImplicitRKStepper.html</anchorfile>
      <anchor>a99652f723e3563f739312a7bdf71f1d6</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; ImplicitRKStepper&lt; Scalar &gt; &gt;</type>
      <name>implicitRKStepper</name>
      <anchorfile>classRythmos_1_1ImplicitRKStepper.html</anchorfile>
      <anchor>af0b7e2669f89abf624fae3f8dc3e660c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; ImplicitRKStepper&lt; Scalar &gt; &gt;</type>
      <name>implicitRKStepper</name>
      <anchorfile>classRythmos_1_1ImplicitRKStepper.html</anchorfile>
      <anchor>af0b7e2669f89abf624fae3f8dc3e660c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ImplicitRKStepper</name>
      <anchorfile>classRythmos_1_1ImplicitRKStepper.html</anchorfile>
      <anchor>af30737a542fc4f5dad568854159dba4f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const Thyra::LinearOpWithSolveFactoryBase&lt; Scalar &gt; &gt;</type>
      <name>get_W_factory</name>
      <anchorfile>classRythmos_1_1ImplicitRKStepper.html</anchorfile>
      <anchor>ae7fe0516d3a29b491c31294db4992cad</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setRKButcherTableau</name>
      <anchorfile>classRythmos_1_1ImplicitRKStepper.html</anchorfile>
      <anchor>a86bb958f55fe4e56d07a15660dcd819a</anchor>
      <arglist>(const RCP&lt; const RKButcherTableauBase&lt; Scalar &gt; &gt; &amp;rkButcherTableau)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const RKButcherTableauBase&lt; Scalar &gt; &gt;</type>
      <name>getRKButcherTableau</name>
      <anchorfile>classRythmos_1_1ImplicitRKStepper.html</anchorfile>
      <anchor>ad72b8c24907324f78d582dffe58fd611</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setSolver</name>
      <anchorfile>classRythmos_1_1ImplicitRKStepper.html</anchorfile>
      <anchor>a57b1b4932d8ff6e76596ef7f498f5c32</anchor>
      <arglist>(const RCP&lt; Thyra::NonlinearSolverBase&lt; Scalar &gt; &gt; &amp;solver)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; Thyra::NonlinearSolverBase&lt; Scalar &gt; &gt;</type>
      <name>getNonconstSolver</name>
      <anchorfile>classRythmos_1_1ImplicitRKStepper.html</anchorfile>
      <anchor>a9b9d7fbec0f9f446d4e5fe47dcb7e6ac</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const Thyra::NonlinearSolverBase&lt; Scalar &gt; &gt;</type>
      <name>getSolver</name>
      <anchorfile>classRythmos_1_1ImplicitRKStepper.html</anchorfile>
      <anchor>afb1eaabd032f2ad4fa47d4d7b522375e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isImplicit</name>
      <anchorfile>classRythmos_1_1ImplicitRKStepper.html</anchorfile>
      <anchor>a7198a50dd72a10b644df0ba9559304ab</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>supportsCloning</name>
      <anchorfile>classRythmos_1_1ImplicitRKStepper.html</anchorfile>
      <anchor>ad53e77d42f08efd824e377f823d342e1</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; StepperBase&lt; Scalar &gt; &gt;</type>
      <name>cloneStepperAlgorithm</name>
      <anchorfile>classRythmos_1_1ImplicitRKStepper.html</anchorfile>
      <anchor>ae71aae913c82a724ef58967154eacf94</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setModel</name>
      <anchorfile>classRythmos_1_1ImplicitRKStepper.html</anchorfile>
      <anchor>a9ce8b2e37ad05af79eab549d87a9ea18</anchor>
      <arglist>(const RCP&lt; const Thyra::ModelEvaluator&lt; Scalar &gt; &gt; &amp;model)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setNonconstModel</name>
      <anchorfile>classRythmos_1_1ImplicitRKStepper.html</anchorfile>
      <anchor>a4a5807a3f3747abc832f3dff43d5bf97</anchor>
      <arglist>(const RCP&lt; Thyra::ModelEvaluator&lt; Scalar &gt; &gt; &amp;model)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const Thyra::ModelEvaluator&lt; Scalar &gt; &gt;</type>
      <name>getModel</name>
      <anchorfile>classRythmos_1_1ImplicitRKStepper.html</anchorfile>
      <anchor>af995fea6c2f70dab545519d3d5cd72ae</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; Thyra::ModelEvaluator&lt; Scalar &gt; &gt;</type>
      <name>getNonconstModel</name>
      <anchorfile>classRythmos_1_1ImplicitRKStepper.html</anchorfile>
      <anchor>a30ee6078b0822e3be6a9a51d7c9fab93</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setInitialCondition</name>
      <anchorfile>classRythmos_1_1ImplicitRKStepper.html</anchorfile>
      <anchor>aa753b022acb0b929e1b2de6390995bd5</anchor>
      <arglist>(const Thyra::ModelEvaluatorBase::InArgs&lt; Scalar &gt; &amp;initialCondition)</arglist>
    </member>
    <member kind="function">
      <type>Thyra::ModelEvaluatorBase::InArgs&lt; Scalar &gt;</type>
      <name>getInitialCondition</name>
      <anchorfile>classRythmos_1_1ImplicitRKStepper.html</anchorfile>
      <anchor>a743e542a1e1b66b182e46d81b2156887</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Scalar</type>
      <name>takeStep</name>
      <anchorfile>classRythmos_1_1ImplicitRKStepper.html</anchorfile>
      <anchor>ac9395857841d0ce0f2835eccca19c7dc</anchor>
      <arglist>(Scalar dt, StepSizeType flag)</arglist>
    </member>
    <member kind="function">
      <type>const StepStatus&lt; Scalar &gt;</type>
      <name>getStepStatus</name>
      <anchorfile>classRythmos_1_1ImplicitRKStepper.html</anchorfile>
      <anchor>adb37ee0f2965ecd945d57662f0aefb86</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setStepControlStrategy</name>
      <anchorfile>classRythmos_1_1ImplicitRKStepper.html</anchorfile>
      <anchor>ac1aa166a3df03db3f0bfd93e443d5f4a</anchor>
      <arglist>(const RCP&lt; StepControlStrategyBase&lt; Scalar &gt; &gt; &amp;stepControlStrategy)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; StepControlStrategyBase&lt; Scalar &gt; &gt;</type>
      <name>getNonconstStepControlStrategy</name>
      <anchorfile>classRythmos_1_1ImplicitRKStepper.html</anchorfile>
      <anchor>aeff562185572cf1b61ab7087e19fbee4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const StepControlStrategyBase&lt; Scalar &gt; &gt;</type>
      <name>getStepControlStrategy</name>
      <anchorfile>classRythmos_1_1ImplicitRKStepper.html</anchorfile>
      <anchor>a2c6c4ae41b758e5a7d0e56730a126f3c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const Thyra::VectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>get_x_space</name>
      <anchorfile>classRythmos_1_1ImplicitRKStepper.html</anchorfile>
      <anchor>a01e9bf01985b02878e4c8ab1661c0760</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>addPoints</name>
      <anchorfile>classRythmos_1_1ImplicitRKStepper.html</anchorfile>
      <anchor>ab46d6c893a158697826c7f809507b15b</anchor>
      <arglist>(const Array&lt; Scalar &gt; &amp;time_vec, const Array&lt; RCP&lt; const Thyra::VectorBase&lt; Scalar &gt; &gt; &gt; &amp;x_vec, const Array&lt; RCP&lt; const Thyra::VectorBase&lt; Scalar &gt; &gt; &gt; &amp;xdot_vec)</arglist>
    </member>
    <member kind="function">
      <type>TimeRange&lt; Scalar &gt;</type>
      <name>getTimeRange</name>
      <anchorfile>classRythmos_1_1ImplicitRKStepper.html</anchorfile>
      <anchor>a9a9c4d8560a7e9d3ef1467b98318b4ab</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>getPoints</name>
      <anchorfile>classRythmos_1_1ImplicitRKStepper.html</anchorfile>
      <anchor>af797908589fa3b8fca51bb853234ac7b</anchor>
      <arglist>(const Array&lt; Scalar &gt; &amp;time_vec, Array&lt; RCP&lt; const Thyra::VectorBase&lt; Scalar &gt; &gt; &gt; *x_vec, Array&lt; RCP&lt; const Thyra::VectorBase&lt; Scalar &gt; &gt; &gt; *xdot_vec, Array&lt; ScalarMag &gt; *accuracy_vec) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>getNodes</name>
      <anchorfile>classRythmos_1_1ImplicitRKStepper.html</anchorfile>
      <anchor>ab0ec592888406f0a56ac8d4b2f2a8769</anchor>
      <arglist>(Array&lt; Scalar &gt; *time_vec) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>removeNodes</name>
      <anchorfile>classRythmos_1_1ImplicitRKStepper.html</anchorfile>
      <anchor>a428dc9e5927298122fe398cd8c482b81</anchor>
      <arglist>(Array&lt; Scalar &gt; &amp;time_vec)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getOrder</name>
      <anchorfile>classRythmos_1_1ImplicitRKStepper.html</anchorfile>
      <anchor>a7bdec57f64d8afc95c7c14e0e053685b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setParameterList</name>
      <anchorfile>classRythmos_1_1ImplicitRKStepper.html</anchorfile>
      <anchor>a6145263f5f213a4c85778064d3a928c1</anchor>
      <arglist>(RCP&lt; ParameterList &gt; const &amp;paramList)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; ParameterList &gt;</type>
      <name>getNonconstParameterList</name>
      <anchorfile>classRythmos_1_1ImplicitRKStepper.html</anchorfile>
      <anchor>a288c880275c64460bef078d72b9dea2f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; ParameterList &gt;</type>
      <name>unsetParameterList</name>
      <anchorfile>classRythmos_1_1ImplicitRKStepper.html</anchorfile>
      <anchor>a0651e0e3b09242368eab178c5cea172a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const ParameterList &gt;</type>
      <name>getValidParameters</name>
      <anchorfile>classRythmos_1_1ImplicitRKStepper.html</anchorfile>
      <anchor>ae073035c437589002c484beba1ef2008</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>describe</name>
      <anchorfile>classRythmos_1_1ImplicitRKStepper.html</anchorfile>
      <anchor>a33826eef43f207eda2128894b2b39d5a</anchor>
      <arglist>(FancyOStream &amp;out, const Teuchos::EVerbosityLevel verbLevel) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Rythmos::IntegrationControlStrategyAcceptingIntegratorBase</name>
    <filename>classRythmos_1_1IntegrationControlStrategyAcceptingIntegratorBase.html</filename>
    <templarg></templarg>
    <base virtualness="virtual">Rythmos::IntegratorBase</base>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>setIntegrationControlStrategy</name>
      <anchorfile>classRythmos_1_1IntegrationControlStrategyAcceptingIntegratorBase.html</anchorfile>
      <anchor>a401d6d6751294641386c9f6655fee345</anchor>
      <arglist>(const RCP&lt; IntegrationControlStrategyBase&lt; Scalar &gt; &gt; &amp;integrationControlStrategy)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual RCP&lt; IntegrationControlStrategyBase&lt; Scalar &gt; &gt;</type>
      <name>getNonconstIntegrationControlStrategy</name>
      <anchorfile>classRythmos_1_1IntegrationControlStrategyAcceptingIntegratorBase.html</anchorfile>
      <anchor>ae8cf8b271b6f7de4dcf13816f179b732</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual RCP&lt; const IntegrationControlStrategyBase&lt; Scalar &gt; &gt;</type>
      <name>getIntegrationControlStrategy</name>
      <anchorfile>classRythmos_1_1IntegrationControlStrategyAcceptingIntegratorBase.html</anchorfile>
      <anchor>aa5ccf7840ef5db1af2edc8df2ad195fc</anchor>
      <arglist>() const  =0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Rythmos::IntegrationControlStrategyBase</name>
    <filename>classRythmos_1_1IntegrationControlStrategyBase.html</filename>
    <templarg></templarg>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>handlesFailedTimeSteps</name>
      <anchorfile>classRythmos_1_1IntegrationControlStrategyBase.html</anchorfile>
      <anchor>a1fe093376df73d2c505453d9cc589314</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual RCP&lt; IntegrationControlStrategyBase&lt; Scalar &gt; &gt;</type>
      <name>cloneIntegrationControlStrategy</name>
      <anchorfile>classRythmos_1_1IntegrationControlStrategyBase.html</anchorfile>
      <anchor>a727b4795619f655951ac865ee795aa32</anchor>
      <arglist>() const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>resetIntegrationControlStrategy</name>
      <anchorfile>classRythmos_1_1IntegrationControlStrategyBase.html</anchorfile>
      <anchor>ac2641dcbe64561870d6ae322033b40e5</anchor>
      <arglist>(const TimeRange&lt; Scalar &gt; &amp;integrationTimeDomain)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual StepControlInfo&lt; Scalar &gt;</type>
      <name>getNextStepControlInfo</name>
      <anchorfile>classRythmos_1_1IntegrationControlStrategyBase.html</anchorfile>
      <anchor>a943e6224eb3f2b0884d2984530f3b408</anchor>
      <arglist>(const StepperBase&lt; Scalar &gt; &amp;stepper, const StepControlInfo&lt; Scalar &gt; &amp;stepCtrlInfoLast, const int timeStepIter)=0</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>resetForFailedTimeStep</name>
      <anchorfile>classRythmos_1_1IntegrationControlStrategyBase.html</anchorfile>
      <anchor>aa6d082feb61107dde02f34fd3a08e41f</anchor>
      <arglist>(const StepperBase&lt; Scalar &gt; &amp;stepper, const StepControlInfo&lt; Scalar &gt; &amp;stepCtrlInfoLast, const int timeStepIter, const StepControlInfo&lt; Scalar &gt; &amp;stepCtrlInfo)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Rythmos::IntegrationObserverBase</name>
    <filename>classRythmos_1_1IntegrationObserverBase.html</filename>
    <templarg></templarg>
    <member kind="function" virtualness="pure">
      <type>virtual RCP&lt; IntegrationObserverBase&lt; Scalar &gt; &gt;</type>
      <name>cloneIntegrationObserver</name>
      <anchorfile>classRythmos_1_1IntegrationObserverBase.html</anchorfile>
      <anchor>a5d5e7717378b762e65088c37cb81855c</anchor>
      <arglist>() const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>resetIntegrationObserver</name>
      <anchorfile>classRythmos_1_1IntegrationObserverBase.html</anchorfile>
      <anchor>a82654072e33f21fbe247ab64cdc95c3c</anchor>
      <arglist>(const TimeRange&lt; Scalar &gt; &amp;integrationTimeDomain)=0</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>observeStartTimeIntegration</name>
      <anchorfile>classRythmos_1_1IntegrationObserverBase.html</anchorfile>
      <anchor>a5f177ddcb8438b05f4f73df402e0151d</anchor>
      <arglist>(const StepperBase&lt; Scalar &gt; &amp;stepper)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>observeEndTimeIntegration</name>
      <anchorfile>classRythmos_1_1IntegrationObserverBase.html</anchorfile>
      <anchor>a80a42dff6c428bac1ad22aa1dc87e448</anchor>
      <arglist>(const StepperBase&lt; Scalar &gt; &amp;stepper)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>observeStartTimeStep</name>
      <anchorfile>classRythmos_1_1IntegrationObserverBase.html</anchorfile>
      <anchor>aaacc0b6283d04458b4c6b9cb40b3036b</anchor>
      <arglist>(const StepperBase&lt; Scalar &gt; &amp;stepper, const StepControlInfo&lt; Scalar &gt; &amp;stepCtrlInfo, const int timeStepIter)</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>observeCompletedTimeStep</name>
      <anchorfile>classRythmos_1_1IntegrationObserverBase.html</anchorfile>
      <anchor>a37b2c1c20551ec560e45e705025d772b</anchor>
      <arglist>(const StepperBase&lt; Scalar &gt; &amp;stepper, const StepControlInfo&lt; Scalar &gt; &amp;stepCtrlInfo, const int timeStepIter)=0</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>observeFailedTimeStep</name>
      <anchorfile>classRythmos_1_1IntegrationObserverBase.html</anchorfile>
      <anchor>aac29b8cce74817dff860ab8114fdd2d2</anchor>
      <arglist>(const StepperBase&lt; Scalar &gt; &amp;stepper, const StepControlInfo&lt; Scalar &gt; &amp;stepCtrlInfo, const int timeStepIter)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Rythmos::IntegratorBase</name>
    <filename>classRythmos_1_1IntegratorBase.html</filename>
    <templarg>Scalar</templarg>
    <base virtualness="virtual">Rythmos::InterpolationBufferBase</base>
    <member kind="typedef">
      <type>Teuchos::ScalarTraits&lt; Scalar &gt;::magnitudeType</type>
      <name>ScalarMag</name>
      <anchorfile>classRythmos_1_1IntegratorBase.html</anchorfile>
      <anchor>a142eac51f7ebd1df2be3830bb6be7e40</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual RCP&lt; IntegratorBase&lt; Scalar &gt; &gt;</type>
      <name>cloneIntegrator</name>
      <anchorfile>classRythmos_1_1IntegratorBase.html</anchorfile>
      <anchor>affc0f451d7e2a35f922b7867a986db32</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>setStepper</name>
      <anchorfile>classRythmos_1_1IntegratorBase.html</anchorfile>
      <anchor>a1c0e2092ed850b199b178b42e2aaf28e</anchor>
      <arglist>(const RCP&lt; StepperBase&lt; Scalar &gt; &gt; &amp;stepper, const Scalar &amp;finalTime, const bool landOnFinalTime=true)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual Teuchos::RCP&lt; const StepperBase&lt; Scalar &gt; &gt;</type>
      <name>getStepper</name>
      <anchorfile>classRythmos_1_1IntegratorBase.html</anchorfile>
      <anchor>aeb82d63b1caa5b294f9134d7541acb07</anchor>
      <arglist>() const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual Teuchos::RCP&lt; StepperBase&lt; Scalar &gt; &gt;</type>
      <name>getNonconstStepper</name>
      <anchorfile>classRythmos_1_1IntegratorBase.html</anchorfile>
      <anchor>aefbcd1cf02eb22be5c0ce3d627b95316</anchor>
      <arglist>() const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual RCP&lt; StepperBase&lt; Scalar &gt; &gt;</type>
      <name>unSetStepper</name>
      <anchorfile>classRythmos_1_1IntegratorBase.html</anchorfile>
      <anchor>ab41c3c68bb158ab39f90a32a06608c1e</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>getFwdPoints</name>
      <anchorfile>classRythmos_1_1IntegratorBase.html</anchorfile>
      <anchor>a5126b362ed513b5bae631e9cbd5b5594</anchor>
      <arglist>(const Array&lt; Scalar &gt; &amp;time_vec, Array&lt; RCP&lt; const Thyra::VectorBase&lt; Scalar &gt; &gt; &gt; *x_vec, Array&lt; RCP&lt; const Thyra::VectorBase&lt; Scalar &gt; &gt; &gt; *xdot_vec, Array&lt; ScalarMag &gt; *accuracy_vec)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual TimeRange&lt; Scalar &gt;</type>
      <name>getFwdTimeRange</name>
      <anchorfile>classRythmos_1_1IntegratorBase.html</anchorfile>
      <anchor>a356422bc66bfd08967a33bffb7bfed8d</anchor>
      <arglist>() const  =0</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const Thyra::VectorBase&lt; Scalar &gt; &gt;</type>
      <name>get_fwd_x</name>
      <anchorfile>classRythmos_1_1IntegratorBase.html</anchorfile>
      <anchor>ab9e68114f1423d21aabec093a887954f</anchor>
      <arglist>(IntegratorBase&lt; Scalar &gt; &amp;integrator, const Scalar t)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>get_fwd_x_and_x_dot</name>
      <anchorfile>classRythmos_1_1IntegratorBase.html</anchorfile>
      <anchor>a8b0ae636c3be37ed65de3fae33b44e77</anchor>
      <arglist>(IntegratorBase&lt; Scalar &gt; &amp;integrator, const Scalar t, const Ptr&lt; RCP&lt; const Thyra::VectorBase&lt; Scalar &gt; &gt; &gt; &amp;x, const Ptr&lt; RCP&lt; const Thyra::VectorBase&lt; Scalar &gt; &gt; &gt; &amp;x_dot)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Rythmos::IntegratorBuilder</name>
    <filename>classRythmos_1_1IntegratorBuilder.html</filename>
    <templarg></templarg>
    <member kind="function">
      <type></type>
      <name>IntegratorBuilder</name>
      <anchorfile>classRythmos_1_1IntegratorBuilder.html</anchorfile>
      <anchor>a2da63473ea9716c6518a3fd652cf50ee</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~IntegratorBuilder</name>
      <anchorfile>classRythmos_1_1IntegratorBuilder.html</anchorfile>
      <anchor>a12e12411f6961b907135a17d860528ff</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setIntegratorFactory</name>
      <anchorfile>classRythmos_1_1IntegratorBuilder.html</anchorfile>
      <anchor>a3370d2870b3ee51ccc2411fb6c412021</anchor>
      <arglist>(const RCP&lt; const AbstractFactory&lt; IntegratorBase&lt; Scalar &gt; &gt; &gt; &amp;integratorFactory, const std::string &amp;integratorFactoryName)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setIntegrationControlFactory</name>
      <anchorfile>classRythmos_1_1IntegratorBuilder.html</anchorfile>
      <anchor>ab846a4b3afddc8469e2fd31175e93c63</anchor>
      <arglist>(const RCP&lt; const AbstractFactory&lt; IntegrationControlStrategyBase&lt; Scalar &gt; &gt; &gt; &amp;integrationControlFactory, const std::string &amp;integrationControlName)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setStepperBuilder</name>
      <anchorfile>classRythmos_1_1IntegratorBuilder.html</anchorfile>
      <anchor>a5a536db27684a222c99287e2db034f24</anchor>
      <arglist>(const RCP&lt; StepperBuilder&lt; Scalar &gt; &gt; &amp;stepperBuilder)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; StepperBuilder&lt; Scalar &gt; &gt;</type>
      <name>getStepperBuilder</name>
      <anchorfile>classRythmos_1_1IntegratorBuilder.html</anchorfile>
      <anchor>a54f9f7f831caf65e63c1a192fe73ac30</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setRKButcherTableauBuilder</name>
      <anchorfile>classRythmos_1_1IntegratorBuilder.html</anchorfile>
      <anchor>af500c39c27772321d366c7cf6a7d50b4</anchor>
      <arglist>(const RCP&lt; RKButcherTableauBuilder&lt; Scalar &gt; &gt; &amp;rkbtBuilder)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setStepControlFactory</name>
      <anchorfile>classRythmos_1_1IntegratorBuilder.html</anchorfile>
      <anchor>abefa6f6f2c10180ea7ab7e33182d8e28</anchor>
      <arglist>(const RCP&lt; const AbstractFactory&lt; StepControlStrategyBase&lt; Scalar &gt; &gt; &gt; &amp;stepControlStrategyFactory, const std::string &amp;stepControlName)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setInterpolationBufferFactory</name>
      <anchorfile>classRythmos_1_1IntegratorBuilder.html</anchorfile>
      <anchor>a724c83700dbdfcc378274a8d1e3d055c</anchor>
      <arglist>(const RCP&lt; const AbstractFactory&lt; InterpolationBufferBase&lt; Scalar &gt; &gt; &gt; &amp;interpolationBufferFactory, const std::string &amp;interpolationBufferName)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setInterpolationBufferAppenderFactory</name>
      <anchorfile>classRythmos_1_1IntegratorBuilder.html</anchorfile>
      <anchor>a49c3afd519198d9e728ad87082503417</anchor>
      <arglist>(const RCP&lt; const AbstractFactory&lt; InterpolationBufferAppenderBase&lt; Scalar &gt; &gt; &gt; &amp;interpolationBufferAppenderFactory, const std::string &amp;interpolationBufferAppenderName)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setErrWtVecCalcFactory</name>
      <anchorfile>classRythmos_1_1IntegratorBuilder.html</anchorfile>
      <anchor>a528c78d2f8651458abc8280dd0d45eb6</anchor>
      <arglist>(const RCP&lt; const AbstractFactory&lt; ErrWtVecCalcBase&lt; Scalar &gt; &gt; &gt; &amp;errWtVecCalcFactory, const std::string &amp;errWtVecCalcFactoryName)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setInterpolatorFactory</name>
      <anchorfile>classRythmos_1_1IntegratorBuilder.html</anchorfile>
      <anchor>a49093bfb49439a41344cf906ecc3d1e1</anchor>
      <arglist>(const RCP&lt; const AbstractFactory&lt; InterpolatorBase&lt; Scalar &gt; &gt; &gt; &amp;interpolatorFactory, const std::string &amp;interpolatorFactoryName)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setWFactoryObject</name>
      <anchorfile>classRythmos_1_1IntegratorBuilder.html</anchorfile>
      <anchor>a1a58db2eab8624d567c8fc211a5c3445</anchor>
      <arglist>(const RCP&lt; Thyra::LinearOpWithSolveFactoryBase&lt; Scalar &gt; &gt; &amp;wFactoryObject)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; IntegratorBase&lt; Scalar &gt; &gt;</type>
      <name>create</name>
      <anchorfile>classRythmos_1_1IntegratorBuilder.html</anchorfile>
      <anchor>a0bcbf376630041a23b54069990ee4056</anchor>
      <arglist>(const RCP&lt; const Thyra::ModelEvaluator&lt; Scalar &gt; &gt; &amp;model, const Thyra::ModelEvaluatorBase::InArgs&lt; Scalar &gt; &amp;initialCondition, const RCP&lt; Thyra::NonlinearSolverBase&lt; Scalar &gt; &gt; &amp;nlSolver) const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; IntegratorBuilder&lt; Scalar &gt; &gt;</type>
      <name>integratorBuilder</name>
      <anchorfile>classRythmos_1_1IntegratorBuilder.html</anchorfile>
      <anchor>aeec683a065da088de479ec2070aae97e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; IntegratorBuilder&lt; Scalar &gt; &gt;</type>
      <name>integratorBuilder</name>
      <anchorfile>classRythmos_1_1IntegratorBuilder.html</anchorfile>
      <anchor>a7ac64e24a36a4f3188a41cbbc514f8b0</anchor>
      <arglist>(const RCP&lt; ParameterList &gt; &amp;paramList)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; IntegratorBase&lt; Scalar &gt; &gt;</type>
      <name>createForwardSensitivityIntegrator</name>
      <anchorfile>classRythmos_1_1IntegratorBuilder.html</anchorfile>
      <anchor>a5b6461ad8d3a3cb6dd11a76b89f9bbb9</anchor>
      <arglist>(const RCP&lt; const Thyra::ModelEvaluator&lt; Scalar &gt; &gt; &amp;model, const int &amp;p_index, const Thyra::ModelEvaluatorBase::InArgs&lt; Scalar &gt; &amp;model_ic, const RCP&lt; Thyra::NonlinearSolverBase&lt; Scalar &gt; &gt; &amp;nlSolver, const RCP&lt; ParameterList &gt; &amp;integratorBuilderPL)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setParameterList</name>
      <anchorfile>classRythmos_1_1IntegratorBuilder.html</anchorfile>
      <anchor>a6a1a8aac22b572468f0492554a222624</anchor>
      <arglist>(const RCP&lt; Teuchos::ParameterList &gt; &amp;paramList)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const Teuchos::ParameterList &gt;</type>
      <name>getValidParameters</name>
      <anchorfile>classRythmos_1_1IntegratorBuilder.html</anchorfile>
      <anchor>aa399dabc6a799398314ecd6234da4f6e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; ParameterList &gt;</type>
      <name>getNonconstParameterList</name>
      <anchorfile>classRythmos_1_1IntegratorBuilder.html</anchorfile>
      <anchor>af921d05bcc9a4455375269b2baa2c2fa</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; ParameterList &gt;</type>
      <name>unsetParameterList</name>
      <anchorfile>classRythmos_1_1IntegratorBuilder.html</anchorfile>
      <anchor>afeb1b36bc2d2ead6b2e392e0d2eed1a3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const ParameterList &gt;</type>
      <name>getParameterList</name>
      <anchorfile>classRythmos_1_1IntegratorBuilder.html</anchorfile>
      <anchor>a2d3a2c7bacb5570c977c5a92e257b398</anchor>
      <arglist>() const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Rythmos::InterpolationBuffer</name>
    <filename>classRythmos_1_1InterpolationBuffer.html</filename>
    <templarg></templarg>
    <base virtualness="virtual">Rythmos::InterpolationBufferBase</base>
    <base virtualness="virtual">Rythmos::InterpolatorAcceptingObjectBase</base>
    <member kind="function">
      <type>RCP&lt; const Thyra::VectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>get_x_space</name>
      <anchorfile>classRythmos_1_1InterpolationBuffer.html</anchorfile>
      <anchor>a43c833a3fd0539c245d5e2becdabf17c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>InterpolationBuffer</name>
      <anchorfile>classRythmos_1_1InterpolationBuffer.html</anchorfile>
      <anchor>a061ae9245e38f796417106660ffcbafa</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initialize</name>
      <anchorfile>classRythmos_1_1InterpolationBuffer.html</anchorfile>
      <anchor>a5a74f1ffcecf1f2b0a59f12bb887b75a</anchor>
      <arglist>(const RCP&lt; InterpolatorBase&lt; Scalar &gt; &gt; &amp;interpolator, int storage)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setStorage</name>
      <anchorfile>classRythmos_1_1InterpolationBuffer.html</anchorfile>
      <anchor>a847cfc1fd132946968e2891ac91b6ce0</anchor>
      <arglist>(int storage)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getStorage</name>
      <anchorfile>classRythmos_1_1InterpolationBuffer.html</anchorfile>
      <anchor>a82004d4c68ea27831ce1f78c9e7d6516</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>IBPolicy</type>
      <name>getIBPolicy</name>
      <anchorfile>classRythmos_1_1InterpolationBuffer.html</anchorfile>
      <anchor>a48eee62103191b3d83276bd03008771f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~InterpolationBuffer</name>
      <anchorfile>classRythmos_1_1InterpolationBuffer.html</anchorfile>
      <anchor>a68cb049429f6e3b024c67b3f14e909fb</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>addPoints</name>
      <anchorfile>classRythmos_1_1InterpolationBuffer.html</anchorfile>
      <anchor>a1cd0b1fdf8330fb5f6669cfc8eb28e22</anchor>
      <arglist>(const Array&lt; Scalar &gt; &amp;time_vec, const Array&lt; RCP&lt; const Thyra::VectorBase&lt; Scalar &gt; &gt; &gt; &amp;x_vec, const Array&lt; RCP&lt; const Thyra::VectorBase&lt; Scalar &gt; &gt; &gt; &amp;xdot_vec)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>getPoints</name>
      <anchorfile>classRythmos_1_1InterpolationBuffer.html</anchorfile>
      <anchor>a11e69c1976579cf01540048d82c450e2</anchor>
      <arglist>(const Array&lt; Scalar &gt; &amp;time_vec, Array&lt; RCP&lt; const Thyra::VectorBase&lt; Scalar &gt; &gt; &gt; *x_vec, Array&lt; RCP&lt; const Thyra::VectorBase&lt; Scalar &gt; &gt; &gt; *xdot_vec, Array&lt; ScalarMag &gt; *accuracy_vec) const </arglist>
    </member>
    <member kind="function">
      <type>TimeRange&lt; Scalar &gt;</type>
      <name>getTimeRange</name>
      <anchorfile>classRythmos_1_1InterpolationBuffer.html</anchorfile>
      <anchor>a4777a5590f2528864a9da04a2daa39f4</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>getNodes</name>
      <anchorfile>classRythmos_1_1InterpolationBuffer.html</anchorfile>
      <anchor>a05ed8a162073ff8781363081515ee8c5</anchor>
      <arglist>(Array&lt; Scalar &gt; *time_vec) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getOrder</name>
      <anchorfile>classRythmos_1_1InterpolationBuffer.html</anchorfile>
      <anchor>a55d0b10a6e70995844292ad9a3453e49</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>removeNodes</name>
      <anchorfile>classRythmos_1_1InterpolationBuffer.html</anchorfile>
      <anchor>a4cb2635db610e96edea558f2c26c74df</anchor>
      <arglist>(Array&lt; Scalar &gt; &amp;time_vec)</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>description</name>
      <anchorfile>classRythmos_1_1InterpolationBuffer.html</anchorfile>
      <anchor>a866511ca39e6eb13db9297d7e47c73db</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>describe</name>
      <anchorfile>classRythmos_1_1InterpolationBuffer.html</anchorfile>
      <anchor>abf28a1e6accefaf9bfa7392424677745</anchor>
      <arglist>(Teuchos::FancyOStream &amp;out, const Teuchos::EVerbosityLevel verbLevel) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setParameterList</name>
      <anchorfile>classRythmos_1_1InterpolationBuffer.html</anchorfile>
      <anchor>ab2c702765e93cef81e8ffcf07123dc49</anchor>
      <arglist>(RCP&lt; Teuchos::ParameterList &gt; const &amp;paramList)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; Teuchos::ParameterList &gt;</type>
      <name>getNonconstParameterList</name>
      <anchorfile>classRythmos_1_1InterpolationBuffer.html</anchorfile>
      <anchor>a12077816a138a16ec4cc79a5770b5bdd</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; Teuchos::ParameterList &gt;</type>
      <name>unsetParameterList</name>
      <anchorfile>classRythmos_1_1InterpolationBuffer.html</anchorfile>
      <anchor>aebf77f6d83077c3d762b94a99723e3f0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; InterpolationBuffer&lt; Scalar &gt; &gt;</type>
      <name>interpolationBuffer</name>
      <anchorfile>classRythmos_1_1InterpolationBuffer.html</anchorfile>
      <anchor>a71bfcca22f56f0e67a3aee7ee20f9248</anchor>
      <arglist>(const RCP&lt; InterpolatorBase&lt; Scalar &gt; &gt; &amp;interpolator=Teuchos::null, int storage=0)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setInterpolator</name>
      <anchorfile>classRythmos_1_1InterpolationBuffer.html</anchorfile>
      <anchor>a993565d8f0cbc8999d3bae38e8551ce0</anchor>
      <arglist>(const RCP&lt; InterpolatorBase&lt; Scalar &gt; &gt; &amp;interpolator)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; InterpolatorBase&lt; Scalar &gt; &gt;</type>
      <name>getNonconstInterpolator</name>
      <anchorfile>classRythmos_1_1InterpolationBuffer.html</anchorfile>
      <anchor>a78d6ec1f3168ed6e99987d9857ae6fef</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const InterpolatorBase&lt; Scalar &gt; &gt;</type>
      <name>getInterpolator</name>
      <anchorfile>classRythmos_1_1InterpolationBuffer.html</anchorfile>
      <anchor>ae018dadeb8c00efd1ebe51a21209adc7</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; InterpolatorBase&lt; Scalar &gt; &gt;</type>
      <name>unSetInterpolator</name>
      <anchorfile>classRythmos_1_1InterpolationBuffer.html</anchorfile>
      <anchor>a7c77ddeb81d9c355d90eddfbdda02f47</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Rythmos::InterpolationBufferAppenderAcceptingIntegratorBase</name>
    <filename>classRythmos_1_1InterpolationBufferAppenderAcceptingIntegratorBase.html</filename>
    <templarg></templarg>
    <base virtualness="virtual">Rythmos::IntegratorBase</base>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>setInterpolationBufferAppender</name>
      <anchorfile>classRythmos_1_1InterpolationBufferAppenderAcceptingIntegratorBase.html</anchorfile>
      <anchor>a879c41d52cc58e93745ba289f9998333</anchor>
      <arglist>(const RCP&lt; InterpolationBufferAppenderBase&lt; Scalar &gt; &gt; &amp;interpBufferAppender)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual RCP&lt; const InterpolationBufferAppenderBase&lt; Scalar &gt; &gt;</type>
      <name>getInterpolationBufferAppender</name>
      <anchorfile>classRythmos_1_1InterpolationBufferAppenderAcceptingIntegratorBase.html</anchorfile>
      <anchor>abacc9db68f21ea8474f1588d749308cd</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual RCP&lt; InterpolationBufferAppenderBase&lt; Scalar &gt; &gt;</type>
      <name>getNonconstInterpolationBufferAppender</name>
      <anchorfile>classRythmos_1_1InterpolationBufferAppenderAcceptingIntegratorBase.html</anchorfile>
      <anchor>ae16b16584ce564edc9c2fc628cbc2ad5</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual RCP&lt; InterpolationBufferAppenderBase&lt; Scalar &gt; &gt;</type>
      <name>unSetInterpolationBufferAppender</name>
      <anchorfile>classRythmos_1_1InterpolationBufferAppenderAcceptingIntegratorBase.html</anchorfile>
      <anchor>a15400b61ab15af0ceb30dde769ce3d90</anchor>
      <arglist>()=0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Rythmos::InterpolationBufferAppenderBase</name>
    <filename>classRythmos_1_1InterpolationBufferAppenderBase.html</filename>
    <templarg></templarg>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>append</name>
      <anchorfile>classRythmos_1_1InterpolationBufferAppenderBase.html</anchorfile>
      <anchor>af986dc62e024e6d7902fd7e938e6f01e</anchor>
      <arglist>(const InterpolationBufferBase&lt; Scalar &gt; &amp;interpBuffSource, const TimeRange&lt; Scalar &gt; &amp;range, const Ptr&lt; InterpolationBufferBase&lt; Scalar &gt; &gt; &amp;interpBuffSink)=0</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>assertAppendPreconditions</name>
      <anchorfile>classRythmos_1_1InterpolationBufferAppenderBase.html</anchorfile>
      <anchor>a6ffab4427f207eb005b23789494a1687</anchor>
      <arglist>(const InterpolationBufferBase&lt; Scalar &gt; &amp;interpBuffSource, const TimeRange&lt; Scalar &gt; &amp;range, const InterpolationBufferBase&lt; Scalar &gt; &amp;interpBuffSink) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Rythmos::InterpolationBufferBase</name>
    <filename>classRythmos_1_1InterpolationBufferBase.html</filename>
    <templarg>Scalar</templarg>
    <member kind="typedef">
      <type>Teuchos::ScalarTraits&lt; Scalar &gt;::magnitudeType</type>
      <name>ScalarMag</name>
      <anchorfile>classRythmos_1_1InterpolationBufferBase.html</anchorfile>
      <anchor>a004ef49b7c4bf83cdeb6d9f9814f1b1b</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual RCP&lt; const Thyra::VectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>get_x_space</name>
      <anchorfile>classRythmos_1_1InterpolationBufferBase.html</anchorfile>
      <anchor>abb2e776579e20c04dde7cbfabca88cd5</anchor>
      <arglist>() const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>addPoints</name>
      <anchorfile>classRythmos_1_1InterpolationBufferBase.html</anchorfile>
      <anchor>a093975c7e98841ea5ac0f2c9ce534f52</anchor>
      <arglist>(const Array&lt; Scalar &gt; &amp;time_vec, const Array&lt; RCP&lt; const Thyra::VectorBase&lt; Scalar &gt; &gt; &gt; &amp;x_vec, const Array&lt; RCP&lt; const Thyra::VectorBase&lt; Scalar &gt; &gt; &gt; &amp;xdot_vec)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual TimeRange&lt; Scalar &gt;</type>
      <name>getTimeRange</name>
      <anchorfile>classRythmos_1_1InterpolationBufferBase.html</anchorfile>
      <anchor>a25357a7fa719f66da02786cfe727f20c</anchor>
      <arglist>() const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>getPoints</name>
      <anchorfile>classRythmos_1_1InterpolationBufferBase.html</anchorfile>
      <anchor>aed0316ccee758f7dea48162042e70310</anchor>
      <arglist>(const Array&lt; Scalar &gt; &amp;time_vec, Array&lt; RCP&lt; const Thyra::VectorBase&lt; Scalar &gt; &gt; &gt; *x_vec, Array&lt; RCP&lt; const Thyra::VectorBase&lt; Scalar &gt; &gt; &gt; *xdot_vec, Array&lt; ScalarMag &gt; *accuracy_vec) const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>getNodes</name>
      <anchorfile>classRythmos_1_1InterpolationBufferBase.html</anchorfile>
      <anchor>aa55cf0cdd37296bbea07e8ec6c9399fc</anchor>
      <arglist>(Array&lt; Scalar &gt; *time_vec) const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>removeNodes</name>
      <anchorfile>classRythmos_1_1InterpolationBufferBase.html</anchorfile>
      <anchor>abc436d422696405d2e01a8ae9bfe22c8</anchor>
      <arglist>(Array&lt; Scalar &gt; &amp;time_vec)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>getOrder</name>
      <anchorfile>classRythmos_1_1InterpolationBufferBase.html</anchorfile>
      <anchor>ad17413a9e37f7bb8dcc204a38fb16b7f</anchor>
      <arglist>() const  =0</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const Thyra::VectorBase&lt; Scalar &gt; &gt;</type>
      <name>get_x</name>
      <anchorfile>classRythmos_1_1InterpolationBufferBase.html</anchorfile>
      <anchor>a1e685a98c327512c86d20a82f68d9be4</anchor>
      <arglist>(const InterpolationBufferBase&lt; Scalar &gt; &amp;interpBuffer, const Scalar &amp;t)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const Thyra::VectorBase&lt; Scalar &gt; &gt;</type>
      <name>get_xdot</name>
      <anchorfile>classRythmos_1_1InterpolationBufferBase.html</anchorfile>
      <anchor>a2da2a63f63871cbc867f4306edd672fc</anchor>
      <arglist>(const InterpolationBufferBase&lt; Scalar &gt; &amp;interpBuffer, const Scalar &amp;t)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>get_x_and_x_dot</name>
      <anchorfile>classRythmos_1_1InterpolationBufferBase.html</anchorfile>
      <anchor>a06e8da1c69f41ee5f016e602afd043c2</anchor>
      <arglist>(const InterpolationBufferBase&lt; Scalar &gt; &amp;interpBuffer, const Scalar t, const Ptr&lt; RCP&lt; const Thyra::VectorBase&lt; Scalar &gt; &gt; &gt; &amp;x, const Ptr&lt; RCP&lt; const Thyra::VectorBase&lt; Scalar &gt; &gt; &gt; &amp;x_dot)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>assertTimePointsAreSorted</name>
      <anchorfile>classRythmos_1_1InterpolationBufferBase.html</anchorfile>
      <anchor>a7f409db13908044f81fdc6e91a257046</anchor>
      <arglist>(const Array&lt; Scalar &gt; &amp;time_vec)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>assertNoTimePointsBeforeCurrentTimeRange</name>
      <anchorfile>classRythmos_1_1InterpolationBufferBase.html</anchorfile>
      <anchor>ab202546b15a48500c5ea7d88bb4c6254</anchor>
      <arglist>(const InterpolationBufferBase&lt; Scalar &gt; &amp;interpBuffer, const Array&lt; Scalar &gt; &amp;time_vec, const int &amp;startingTimePointIndex=0)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>assertNoTimePointsInsideCurrentTimeRange</name>
      <anchorfile>classRythmos_1_1InterpolationBufferBase.html</anchorfile>
      <anchor>a7157a36e3a1a9490fb4b29a7d6584577</anchor>
      <arglist>(const InterpolationBufferBase&lt; Scalar &gt; &amp;interpBuffer, const Array&lt; Scalar &gt; &amp;time_vec)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>selectPointsInTimeRange</name>
      <anchorfile>classRythmos_1_1InterpolationBufferBase.html</anchorfile>
      <anchor>a3fe04d2a6c9b12a5bc95a80b1bbf75f9</anchor>
      <arglist>(const Array&lt; TimeType &gt; &amp;points_in, const TimeRange&lt; TimeType &gt; &amp;range, const Ptr&lt; Array&lt; TimeType &gt; &gt; &amp;points_out)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>removePointsInTimeRange</name>
      <anchorfile>classRythmos_1_1InterpolationBufferBase.html</anchorfile>
      <anchor>ae0ab43f4035226186869760f77706c52</anchor>
      <arglist>(Array&lt; TimeType &gt; *points_in, const TimeRange&lt; TimeType &gt; &amp;range)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>getCurrentPoints</name>
      <anchorfile>classRythmos_1_1InterpolationBufferBase.html</anchorfile>
      <anchor>a9d8f76e3172484e249a021bd933b3a05</anchor>
      <arglist>(const InterpolationBufferBase&lt; Scalar &gt; &amp;interpBuffer, const Array&lt; Scalar &gt; &amp;time_vec, Array&lt; RCP&lt; const Thyra::VectorBase&lt; Scalar &gt; &gt; &gt; *x_vec, Array&lt; RCP&lt; const Thyra::VectorBase&lt; Scalar &gt; &gt; &gt; *xdot_vec, int *nextTimePointIndex)</arglist>
    </member>
    <docanchor file="classRythmos_1_1InterpolationBufferBase" title="Definitions">Rythmos_InterpolationBufferBase_Definitions_sec</docanchor>
  </compound>
  <compound kind="class">
    <name>Rythmos::InterpolatorAcceptingObjectBase</name>
    <filename>classRythmos_1_1InterpolatorAcceptingObjectBase.html</filename>
    <templarg></templarg>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~InterpolatorAcceptingObjectBase</name>
      <anchorfile>classRythmos_1_1InterpolatorAcceptingObjectBase.html</anchorfile>
      <anchor>aced4c52225d28c6a7ee9427763041829</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>setInterpolator</name>
      <anchorfile>classRythmos_1_1InterpolatorAcceptingObjectBase.html</anchorfile>
      <anchor>a55fb905e1ebcf4d20885607dc0740d3a</anchor>
      <arglist>(const RCP&lt; InterpolatorBase&lt; Scalar &gt; &gt; &amp;interpolator)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual RCP&lt; InterpolatorBase&lt; Scalar &gt; &gt;</type>
      <name>getNonconstInterpolator</name>
      <anchorfile>classRythmos_1_1InterpolatorAcceptingObjectBase.html</anchorfile>
      <anchor>aa7bd7b21f245666b3932207fbf7222f4</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual RCP&lt; const InterpolatorBase&lt; Scalar &gt; &gt;</type>
      <name>getInterpolator</name>
      <anchorfile>classRythmos_1_1InterpolatorAcceptingObjectBase.html</anchorfile>
      <anchor>aba88e9e24122593e5f23c376a2f64d15</anchor>
      <arglist>() const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual RCP&lt; InterpolatorBase&lt; Scalar &gt; &gt;</type>
      <name>unSetInterpolator</name>
      <anchorfile>classRythmos_1_1InterpolatorAcceptingObjectBase.html</anchorfile>
      <anchor>a5f924b23b0e554d92cd341df721cc981</anchor>
      <arglist>()=0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Rythmos::InterpolatorBase</name>
    <filename>classRythmos_1_1InterpolatorBase.html</filename>
    <templarg></templarg>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>supportsCloning</name>
      <anchorfile>classRythmos_1_1InterpolatorBase.html</anchorfile>
      <anchor>a33d96600ba27a2f87ec1f20995ef0788</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual Teuchos::RCP&lt; InterpolatorBase&lt; Scalar &gt; &gt;</type>
      <name>cloneInterpolator</name>
      <anchorfile>classRythmos_1_1InterpolatorBase.html</anchorfile>
      <anchor>a389508127494f14aa2942366d1f0d6bf</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>setNodes</name>
      <anchorfile>classRythmos_1_1InterpolatorBase.html</anchorfile>
      <anchor>acfb024c7b01036a2e9bdca9dca291a51</anchor>
      <arglist>(const RCP&lt; const typename DataStore&lt; Scalar &gt;::DataStoreVector_t &gt; &amp;nodes)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>interpolate</name>
      <anchorfile>classRythmos_1_1InterpolatorBase.html</anchorfile>
      <anchor>a09574b29a593746df2793ad58cf422bb</anchor>
      <arglist>(const Array&lt; Scalar &gt; &amp;t_values, typename DataStore&lt; Scalar &gt;::DataStoreVector_t *data_out) const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>order</name>
      <anchorfile>classRythmos_1_1InterpolatorBase.html</anchorfile>
      <anchor>a93ed563ee7fbabcb7d7797fff7e831b7</anchor>
      <arglist>() const  =0</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>assertBaseInterpolatePreconditions</name>
      <anchorfile>classRythmos_1_1InterpolatorBase.html</anchorfile>
      <anchor>a7b149b4137cff473317198d046c29b4c</anchor>
      <arglist>(const typename DataStore&lt; Scalar &gt;::DataStoreVector_t &amp;data_in, const Array&lt; Scalar &gt; &amp;t_values, typename DataStore&lt; Scalar &gt;::DataStoreVector_t *data_out)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Rythmos::LinearInterpolator</name>
    <filename>classRythmos_1_1LinearInterpolator.html</filename>
    <templarg></templarg>
    <base virtualness="virtual">Rythmos::InterpolatorBase</base>
    <member kind="function">
      <type></type>
      <name>~LinearInterpolator</name>
      <anchorfile>classRythmos_1_1LinearInterpolator.html</anchorfile>
      <anchor>aaf584c0bb731baf4df1f74d686c50696</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>LinearInterpolator</name>
      <anchorfile>classRythmos_1_1LinearInterpolator.html</anchorfile>
      <anchor>a0a7f7ccb7a9815fda32826284009f07c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>supportsCloning</name>
      <anchorfile>classRythmos_1_1LinearInterpolator.html</anchorfile>
      <anchor>a60f06295905ca1641bc72421eec2d597</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; InterpolatorBase&lt; Scalar &gt; &gt;</type>
      <name>cloneInterpolator</name>
      <anchorfile>classRythmos_1_1LinearInterpolator.html</anchorfile>
      <anchor>a4b617b01ac804c12320261378829ce9f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setNodes</name>
      <anchorfile>classRythmos_1_1LinearInterpolator.html</anchorfile>
      <anchor>ab58442ab4524c36ef1468f68d92ad05c</anchor>
      <arglist>(const RCP&lt; const typename DataStore&lt; Scalar &gt;::DataStoreVector_t &gt; &amp;nodes)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>interpolate</name>
      <anchorfile>classRythmos_1_1LinearInterpolator.html</anchorfile>
      <anchor>aee6ed5315b03f461d672e295a5932482</anchor>
      <arglist>(const Array&lt; Scalar &gt; &amp;t_values, typename DataStore&lt; Scalar &gt;::DataStoreVector_t *data_out) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>order</name>
      <anchorfile>classRythmos_1_1LinearInterpolator.html</anchorfile>
      <anchor>aa0b1d9ed49369812601740fb8c665df0</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>description</name>
      <anchorfile>classRythmos_1_1LinearInterpolator.html</anchorfile>
      <anchor>a57cb98cde8d551db5c47df7524f1b587</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>describe</name>
      <anchorfile>classRythmos_1_1LinearInterpolator.html</anchorfile>
      <anchor>a8168f618c4e2c15c82baa3fcb042474f</anchor>
      <arglist>(FancyOStream &amp;out, const Teuchos::EVerbosityLevel verbLevel) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setParameterList</name>
      <anchorfile>classRythmos_1_1LinearInterpolator.html</anchorfile>
      <anchor>a393afbfaf7d2a46c4483fa0644c9c13e</anchor>
      <arglist>(RCP&lt; ParameterList &gt; const &amp;paramList)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; ParameterList &gt;</type>
      <name>getNonconstParameterList</name>
      <anchorfile>classRythmos_1_1LinearInterpolator.html</anchorfile>
      <anchor>a255a38d7860076642eb2a63eb1dd8cac</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; ParameterList &gt;</type>
      <name>unsetParameterList</name>
      <anchorfile>classRythmos_1_1LinearInterpolator.html</anchorfile>
      <anchor>a4d980525c3e9c6a8ac4a75572394c1da</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const Teuchos::ParameterList &gt;</type>
      <name>getValidParameters</name>
      <anchorfile>classRythmos_1_1LinearInterpolator.html</anchorfile>
      <anchor>a9969de90429ab8368d1a4d5c344fb0f0</anchor>
      <arglist>() const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Rythmos::LoggingIntegrationObserver</name>
    <filename>classRythmos_1_1LoggingIntegrationObserver.html</filename>
    <templarg></templarg>
    <base virtualness="virtual">Rythmos::IntegrationObserverBase</base>
    <member kind="function">
      <type>Teuchos::RCP&lt; LoggingIntegrationObserver&lt; Scalar &gt; &gt;</type>
      <name>createLoggingIntegrationObserver</name>
      <anchorfile>classRythmos_1_1LoggingIntegrationObserver.html</anchorfile>
      <anchor>a1ae5b90b4bf1bbbde4694dd8c2d627ea</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; IntegrationObserverBase&lt; Scalar &gt; &gt;</type>
      <name>cloneIntegrationObserver</name>
      <anchorfile>classRythmos_1_1LoggingIntegrationObserver.html</anchorfile>
      <anchor>aecdebc7d85c0df178da84c1e07df2880</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>resetIntegrationObserver</name>
      <anchorfile>classRythmos_1_1LoggingIntegrationObserver.html</anchorfile>
      <anchor>a816561af43aa19190a5b394dc5d2a0d4</anchor>
      <arglist>(const TimeRange&lt; Scalar &gt; &amp;integrationTimeDomain)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>observeStartTimeIntegration</name>
      <anchorfile>classRythmos_1_1LoggingIntegrationObserver.html</anchorfile>
      <anchor>a5776b708b6bbc563e16d8ff14f978e5e</anchor>
      <arglist>(const StepperBase&lt; Scalar &gt; &amp;stepper)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>observeEndTimeIntegration</name>
      <anchorfile>classRythmos_1_1LoggingIntegrationObserver.html</anchorfile>
      <anchor>a1c002751923971a2c60e6a5b79a77cdf</anchor>
      <arglist>(const StepperBase&lt; Scalar &gt; &amp;stepper)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>observeStartTimeStep</name>
      <anchorfile>classRythmos_1_1LoggingIntegrationObserver.html</anchorfile>
      <anchor>af24add27ba7994311fd1f12d23d68155</anchor>
      <arglist>(const StepperBase&lt; Scalar &gt; &amp;stepper, const StepControlInfo&lt; Scalar &gt; &amp;stepCtrlInfo, const int timeStepIter)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>observeCompletedTimeStep</name>
      <anchorfile>classRythmos_1_1LoggingIntegrationObserver.html</anchorfile>
      <anchor>a32a231e2c2103ac61820a7e6000e9503</anchor>
      <arglist>(const StepperBase&lt; Scalar &gt; &amp;stepper, const StepControlInfo&lt; Scalar &gt; &amp;stepCtrlInfo, const int timeStepIter)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>observeFailedTimeStep</name>
      <anchorfile>classRythmos_1_1LoggingIntegrationObserver.html</anchorfile>
      <anchor>a3fd97c63e4e9f09b416ea6cee38ca56d</anchor>
      <arglist>(const StepperBase&lt; Scalar &gt; &amp;stepper, const StepControlInfo&lt; Scalar &gt; &amp;stepCtrlInfo, const int timeStepIter)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Rythmos::MomentoBase</name>
    <filename>classRythmos_1_1MomentoBase.html</filename>
    <templarg></templarg>
  </compound>
  <compound kind="class">
    <name>Rythmos::PointwiseInterpolationBufferAppender</name>
    <filename>classRythmos_1_1PointwiseInterpolationBufferAppender.html</filename>
    <templarg>Scalar</templarg>
    <base virtualness="virtual">Rythmos::InterpolationBufferAppenderBase</base>
    <member kind="typedef">
      <type>Teuchos::ScalarTraits&lt; Scalar &gt;::magnitudeType</type>
      <name>ScalarMag</name>
      <anchorfile>classRythmos_1_1PointwiseInterpolationBufferAppender.html</anchorfile>
      <anchor>ab07ada99b607246b43294fee3f98e273</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>append</name>
      <anchorfile>classRythmos_1_1PointwiseInterpolationBufferAppender.html</anchorfile>
      <anchor>aabf118ff47cc80550c88d1fe92f5d0ff</anchor>
      <arglist>(const InterpolationBufferBase&lt; Scalar &gt; &amp;interpBuffSource, const TimeRange&lt; Scalar &gt; &amp;range, const Ptr&lt; InterpolationBufferBase&lt; Scalar &gt; &gt; &amp;interpBuffSink)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; PointwiseInterpolationBufferAppender&lt; Scalar &gt; &gt;</type>
      <name>pointwiseInterpolationBufferAppender</name>
      <anchorfile>classRythmos_1_1PointwiseInterpolationBufferAppender.html</anchorfile>
      <anchor>a799bb1136cf621c331f6cb90d75daf71</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>describe</name>
      <anchorfile>classRythmos_1_1PointwiseInterpolationBufferAppender.html</anchorfile>
      <anchor>a669c1cd07805def806851041afa559fb</anchor>
      <arglist>(Teuchos::FancyOStream &amp;out, const Teuchos::EVerbosityLevel verbLevel) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setParameterList</name>
      <anchorfile>classRythmos_1_1PointwiseInterpolationBufferAppender.html</anchorfile>
      <anchor>a128e03e4f8f54b4866dcf27ed3284f7e</anchor>
      <arglist>(const RCP&lt; ParameterList &gt; &amp;paramList)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const ParameterList &gt;</type>
      <name>getValidParameters</name>
      <anchorfile>classRythmos_1_1PointwiseInterpolationBufferAppender.html</anchorfile>
      <anchor>a5d466131bc636bfc3a935160f268a0de</anchor>
      <arglist>() const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Rythmos::RampingIntegrationControlStrategy</name>
    <filename>classRythmos_1_1RampingIntegrationControlStrategy.html</filename>
    <templarg></templarg>
    <base virtualness="virtual">Rythmos::IntegrationControlStrategyBase</base>
    <member kind="function">
      <type>RCP&lt; RampingIntegrationControlStrategy&lt; Scalar &gt; &gt;</type>
      <name>rampingIntegrationControlStrategy</name>
      <anchorfile>classRythmos_1_1RampingIntegrationControlStrategy.html</anchorfile>
      <anchor>a050722783990854d56b50fe0d2042af7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; RampingIntegrationControlStrategy&lt; Scalar &gt; &gt;</type>
      <name>rampingIntegrationControlStrategy</name>
      <anchorfile>classRythmos_1_1RampingIntegrationControlStrategy.html</anchorfile>
      <anchor>a4accc6bae18455c0b224f853bbc857ed</anchor>
      <arglist>(const RCP&lt; ParameterList &gt; &amp;paramList)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>RampingIntegrationControlStrategy</name>
      <anchorfile>classRythmos_1_1RampingIntegrationControlStrategy.html</anchorfile>
      <anchor>aef834ec6f32a40d21a63bf464b217147</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setParameterList</name>
      <anchorfile>classRythmos_1_1RampingIntegrationControlStrategy.html</anchorfile>
      <anchor>a5905534cc7dbca762344699c1679e1fa</anchor>
      <arglist>(RCP&lt; ParameterList &gt; const &amp;paramList)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const ParameterList &gt;</type>
      <name>getValidParameters</name>
      <anchorfile>classRythmos_1_1RampingIntegrationControlStrategy.html</anchorfile>
      <anchor>addb43c752718d0ae05e79ec5533254b9</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>handlesFailedTimeSteps</name>
      <anchorfile>classRythmos_1_1RampingIntegrationControlStrategy.html</anchorfile>
      <anchor>ab1c24acfe424477e7a6fe1340a0aea45</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; IntegrationControlStrategyBase&lt; Scalar &gt; &gt;</type>
      <name>cloneIntegrationControlStrategy</name>
      <anchorfile>classRythmos_1_1RampingIntegrationControlStrategy.html</anchorfile>
      <anchor>aead29fc9cff0ba414ff78ee37f845253</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>resetIntegrationControlStrategy</name>
      <anchorfile>classRythmos_1_1RampingIntegrationControlStrategy.html</anchorfile>
      <anchor>a2ede862396c6c70020879314b68a1155</anchor>
      <arglist>(const TimeRange&lt; Scalar &gt; &amp;integrationTimeDomain)</arglist>
    </member>
    <member kind="function">
      <type>StepControlInfo&lt; Scalar &gt;</type>
      <name>getNextStepControlInfo</name>
      <anchorfile>classRythmos_1_1RampingIntegrationControlStrategy.html</anchorfile>
      <anchor>a0569a5c9fc4dd3a1ea84f2a50e2d82e9</anchor>
      <arglist>(const StepperBase&lt; Scalar &gt; &amp;stepper, const StepControlInfo&lt; Scalar &gt; &amp;stepCtrlInfoLast, const int timeStepIter)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>resetForFailedTimeStep</name>
      <anchorfile>classRythmos_1_1RampingIntegrationControlStrategy.html</anchorfile>
      <anchor>ac7aa6bd1e5a91c10906050deaabc913c</anchor>
      <arglist>(const StepperBase&lt; Scalar &gt; &amp;stepper, const StepControlInfo&lt; Scalar &gt; &amp;stepCtrlInfoLast, const int timeStepIter, const StepControlInfo&lt; Scalar &gt; &amp;stepCtrlInfo)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Rythmos::ResponseAndFwdSensPoint</name>
    <filename>classRythmos_1_1ResponseAndFwdSensPoint.html</filename>
    <templarg></templarg>
    <member kind="function">
      <type></type>
      <name>ResponseAndFwdSensPoint</name>
      <anchorfile>classRythmos_1_1ResponseAndFwdSensPoint.html</anchorfile>
      <anchor>a81c5a27776883a28c3966c58ede59ce9</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ResponseAndFwdSensPoint</name>
      <anchorfile>classRythmos_1_1ResponseAndFwdSensPoint.html</anchorfile>
      <anchor>ad7be8c1415491e66019b1c8e2971cfe9</anchor>
      <arglist>(const Scalar &amp;t, const RCP&lt; const Thyra::VectorBase&lt; Scalar &gt; &gt; &amp;g, const RCP&lt; const Thyra::MultiVectorBase&lt; Scalar &gt; &gt; &amp;DgDp)</arglist>
    </member>
    <member kind="function">
      <type>Scalar</type>
      <name>t</name>
      <anchorfile>classRythmos_1_1ResponseAndFwdSensPoint.html</anchorfile>
      <anchor>aad8e49ab44fdd0959afc353e331503e6</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const RCP&lt; const Thyra::VectorBase&lt; Scalar &gt; &gt;</type>
      <name>g</name>
      <anchorfile>classRythmos_1_1ResponseAndFwdSensPoint.html</anchorfile>
      <anchor>aa9e89ee8f7829d99590c29f9f1260038</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const RCP&lt; const Thyra::MultiVectorBase&lt; Scalar &gt; &gt;</type>
      <name>DgDp</name>
      <anchorfile>classRythmos_1_1ResponseAndFwdSensPoint.html</anchorfile>
      <anchor>af316ae317947cb261fb09eedd9ce2d9b</anchor>
      <arglist>() const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Rythmos::RKButcherTableauAcceptingStepperBase</name>
    <filename>classRythmos_1_1RKButcherTableauAcceptingStepperBase.html</filename>
    <templarg></templarg>
    <base virtualness="virtual">Rythmos::StepperBase</base>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>setRKButcherTableau</name>
      <anchorfile>classRythmos_1_1RKButcherTableauAcceptingStepperBase.html</anchorfile>
      <anchor>a4079d010c8beb6765f4194178ecc7f8d</anchor>
      <arglist>(const Teuchos::RCP&lt; const RKButcherTableauBase&lt; Scalar &gt; &gt; &amp;rkbt)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual RCP&lt; const RKButcherTableauBase&lt; Scalar &gt; &gt;</type>
      <name>getRKButcherTableau</name>
      <anchorfile>classRythmos_1_1RKButcherTableauAcceptingStepperBase.html</anchorfile>
      <anchor>a56c3f0755aec54aa7a05795e0b140c58</anchor>
      <arglist>() const  =0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Rythmos::SimpleIntegrationControlStrategy</name>
    <filename>classRythmos_1_1SimpleIntegrationControlStrategy.html</filename>
    <templarg></templarg>
    <base virtualness="virtual">Rythmos::IntegrationControlStrategyBase</base>
    <member kind="function">
      <type>RCP&lt; SimpleIntegrationControlStrategy&lt; Scalar &gt; &gt;</type>
      <name>simpleIntegrationControlStrategy</name>
      <anchorfile>classRythmos_1_1SimpleIntegrationControlStrategy.html</anchorfile>
      <anchor>a2dc132233e857be658f1e6b045b96cae</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; SimpleIntegrationControlStrategy&lt; Scalar &gt; &gt;</type>
      <name>simpleIntegrationControlStrategy</name>
      <anchorfile>classRythmos_1_1SimpleIntegrationControlStrategy.html</anchorfile>
      <anchor>a4c6f346981763841aa0e7662eb689dfd</anchor>
      <arglist>(const RCP&lt; ParameterList &gt; &amp;paramList)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SimpleIntegrationControlStrategy</name>
      <anchorfile>classRythmos_1_1SimpleIntegrationControlStrategy.html</anchorfile>
      <anchor>a83e18433db6ee2de80375b21252e613a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setParameterList</name>
      <anchorfile>classRythmos_1_1SimpleIntegrationControlStrategy.html</anchorfile>
      <anchor>a38b72c772c9d17b3014da18a920fc8f8</anchor>
      <arglist>(RCP&lt; ParameterList &gt; const &amp;paramList)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const ParameterList &gt;</type>
      <name>getValidParameters</name>
      <anchorfile>classRythmos_1_1SimpleIntegrationControlStrategy.html</anchorfile>
      <anchor>a8cbed21e0621f4d259405e250070b991</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; IntegrationControlStrategyBase&lt; Scalar &gt; &gt;</type>
      <name>cloneIntegrationControlStrategy</name>
      <anchorfile>classRythmos_1_1SimpleIntegrationControlStrategy.html</anchorfile>
      <anchor>a107951469937c6366a043db212053115</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>resetIntegrationControlStrategy</name>
      <anchorfile>classRythmos_1_1SimpleIntegrationControlStrategy.html</anchorfile>
      <anchor>acb9a7f6a95abe5fd832b8d11fc023f1b</anchor>
      <arglist>(const TimeRange&lt; Scalar &gt; &amp;integrationTimeDomain)</arglist>
    </member>
    <member kind="function">
      <type>StepControlInfo&lt; Scalar &gt;</type>
      <name>getNextStepControlInfo</name>
      <anchorfile>classRythmos_1_1SimpleIntegrationControlStrategy.html</anchorfile>
      <anchor>a0d77b174978f2b708206b95e408eff20</anchor>
      <arglist>(const StepperBase&lt; Scalar &gt; &amp;stepper, const StepControlInfo&lt; Scalar &gt; &amp;stepCtrlInfoLast, const int timeStepIter)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Rythmos::SingleResidualModelEvaluator</name>
    <filename>classRythmos_1_1SingleResidualModelEvaluator.html</filename>
    <templarg>Scalar</templarg>
    <base virtualness="virtual">Rythmos::SingleResidualModelEvaluatorBase</base>
    <member kind="function">
      <type></type>
      <name>SingleResidualModelEvaluator</name>
      <anchorfile>classRythmos_1_1SingleResidualModelEvaluator.html</anchorfile>
      <anchor>af269896956d947137df817c548e2a02c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initializeSingleResidualModel</name>
      <anchorfile>classRythmos_1_1SingleResidualModelEvaluator.html</anchorfile>
      <anchor>a13d851701698f58a1044bd8f642be740</anchor>
      <arglist>(const RCP&lt; const Thyra::ModelEvaluator&lt; Scalar &gt; &gt; &amp;daeModel, const Thyra::ModelEvaluatorBase::InArgs&lt; Scalar &gt; &amp;basePoint, const Scalar &amp;coeff_x_dot, const RCP&lt; const Thyra::VectorBase&lt; Scalar &gt; &gt; &amp;x_dot_base, const Scalar &amp;coeff_x, const RCP&lt; const Thyra::VectorBase&lt; Scalar &gt; &gt; &amp;x_base, const Scalar &amp;t_base, const RCP&lt; const Thyra::VectorBase&lt; Scalar &gt; &gt; &amp;x_bar_init)</arglist>
    </member>
    <member kind="function">
      <type>Scalar</type>
      <name>get_coeff_x_dot</name>
      <anchorfile>classRythmos_1_1SingleResidualModelEvaluator.html</anchorfile>
      <anchor>ac865f536f58c3a3a1e0b8ac4483bfe00</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const Thyra::VectorBase&lt; Scalar &gt; &gt;</type>
      <name>get_x_dot_base</name>
      <anchorfile>classRythmos_1_1SingleResidualModelEvaluator.html</anchorfile>
      <anchor>abc897d711d3eec98a449fea12968016d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Scalar</type>
      <name>get_coeff_x</name>
      <anchorfile>classRythmos_1_1SingleResidualModelEvaluator.html</anchorfile>
      <anchor>a8c6e7ae285c1f46e00ab5388445c7aa4</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const Thyra::VectorBase&lt; Scalar &gt; &gt;</type>
      <name>get_x_base</name>
      <anchorfile>classRythmos_1_1SingleResidualModelEvaluator.html</anchorfile>
      <anchor>ad6a64192a4380809cfb94d035ada93f0</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Scalar</type>
      <name>get_t_base</name>
      <anchorfile>classRythmos_1_1SingleResidualModelEvaluator.html</anchorfile>
      <anchor>a6d52dfda987cde9e0a76effd3782f774</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Thyra::ModelEvaluatorBase::InArgs&lt; Scalar &gt;</type>
      <name>getNominalValues</name>
      <anchorfile>classRythmos_1_1SingleResidualModelEvaluator.html</anchorfile>
      <anchor>aecccd73a9500653551f64a14f9960dae</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Thyra::ModelEvaluatorBase::InArgs&lt; Scalar &gt;</type>
      <name>createInArgs</name>
      <anchorfile>classRythmos_1_1SingleResidualModelEvaluator.html</anchorfile>
      <anchor>a419894fa8bf5bee9f49a66eb67e538f2</anchor>
      <arglist>() const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Rythmos::SingleResidualModelEvaluatorBase</name>
    <filename>classRythmos_1_1SingleResidualModelEvaluatorBase.html</filename>
    <templarg></templarg>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>initializeSingleResidualModel</name>
      <anchorfile>classRythmos_1_1SingleResidualModelEvaluatorBase.html</anchorfile>
      <anchor>afc07456d0e49dd7847f005827569f288</anchor>
      <arglist>(const RCP&lt; const Thyra::ModelEvaluator&lt; Scalar &gt; &gt; &amp;daeModel, const Thyra::ModelEvaluatorBase::InArgs&lt; Scalar &gt; &amp;basePoint, const Scalar &amp;coeff_x_dot, const RCP&lt; const Thyra::VectorBase&lt; Scalar &gt; &gt; &amp;x_dot_base, const Scalar &amp;coeff_x, const RCP&lt; const Thyra::VectorBase&lt; Scalar &gt; &gt; &amp;x_base, const Scalar &amp;t_base, const RCP&lt; const Thyra::VectorBase&lt; Scalar &gt; &gt; &amp;x_bar_init)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual Scalar</type>
      <name>get_coeff_x_dot</name>
      <anchorfile>classRythmos_1_1SingleResidualModelEvaluatorBase.html</anchorfile>
      <anchor>ab07888b3812db8139fbd3640ab097fea</anchor>
      <arglist>() const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual RCP&lt; const Thyra::VectorBase&lt; Scalar &gt; &gt;</type>
      <name>get_x_dot_base</name>
      <anchorfile>classRythmos_1_1SingleResidualModelEvaluatorBase.html</anchorfile>
      <anchor>ada24a3ef7fb34f4ebcedb459a61336fd</anchor>
      <arglist>() const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual Scalar</type>
      <name>get_coeff_x</name>
      <anchorfile>classRythmos_1_1SingleResidualModelEvaluatorBase.html</anchorfile>
      <anchor>a09b575ebec25e2e9d80a5b7a3b3ce70c</anchor>
      <arglist>() const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual RCP&lt; const Thyra::VectorBase&lt; Scalar &gt; &gt;</type>
      <name>get_x_base</name>
      <anchorfile>classRythmos_1_1SingleResidualModelEvaluatorBase.html</anchorfile>
      <anchor>aec456cc1ad34edcef4831bb6794a9916</anchor>
      <arglist>() const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual Scalar</type>
      <name>get_t_base</name>
      <anchorfile>classRythmos_1_1SingleResidualModelEvaluatorBase.html</anchorfile>
      <anchor>a6d04343ac452a7286405be0f515f51cc</anchor>
      <arglist>() const  =0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Rythmos::SmartInterpolationBufferAppender</name>
    <filename>classRythmos_1_1SmartInterpolationBufferAppender.html</filename>
    <templarg></templarg>
    <base virtualness="virtual">Rythmos::InterpolationBufferAppenderBase</base>
    <member kind="function">
      <type>void</type>
      <name>append</name>
      <anchorfile>classRythmos_1_1SmartInterpolationBufferAppender.html</anchorfile>
      <anchor>acc33c4a7943151ec22013402f01bc149</anchor>
      <arglist>(const InterpolationBufferBase&lt; Scalar &gt; &amp;interpBuffSource, const TimeRange&lt; Scalar &gt; &amp;range, const Ptr&lt; InterpolationBufferBase&lt; Scalar &gt; &gt; &amp;interpBuffSink)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setParameterList</name>
      <anchorfile>classRythmos_1_1SmartInterpolationBufferAppender.html</anchorfile>
      <anchor>a0c656cea0b8e03b752cce900f02e1465</anchor>
      <arglist>(RCP&lt; Teuchos::ParameterList &gt; const &amp;paramList)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const Teuchos::ParameterList &gt;</type>
      <name>getValidParameters</name>
      <anchorfile>classRythmos_1_1SmartInterpolationBufferAppender.html</anchorfile>
      <anchor>aa48a0cc067b0f810d4fbd12ee9da4082</anchor>
      <arglist>() const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Rythmos::SolverAcceptingStepperBase</name>
    <filename>classRythmos_1_1SolverAcceptingStepperBase.html</filename>
    <templarg></templarg>
    <base virtualness="virtual">Rythmos::StepperBase</base>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>setSolver</name>
      <anchorfile>classRythmos_1_1SolverAcceptingStepperBase.html</anchorfile>
      <anchor>a71ac2801080302d5a8a3279174268c09</anchor>
      <arglist>(const Teuchos::RCP&lt; Thyra::NonlinearSolverBase&lt; Scalar &gt; &gt; &amp;solver)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual Teuchos::RCP&lt; Thyra::NonlinearSolverBase&lt; Scalar &gt; &gt;</type>
      <name>getNonconstSolver</name>
      <anchorfile>classRythmos_1_1SolverAcceptingStepperBase.html</anchorfile>
      <anchor>a5585a5fa00ee13de545392f1cefd67ad</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual Teuchos::RCP&lt; const Thyra::NonlinearSolverBase&lt; Scalar &gt; &gt;</type>
      <name>getSolver</name>
      <anchorfile>classRythmos_1_1SolverAcceptingStepperBase.html</anchorfile>
      <anchor>a930bb38623539ce0a8b4ad2d59669976</anchor>
      <arglist>() const  =0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Rythmos::StateAndForwardSensitivityModelEvaluator</name>
    <filename>classRythmos_1_1StateAndForwardSensitivityModelEvaluator.html</filename>
    <templarg></templarg>
    <member kind="function">
      <type></type>
      <name>StateAndForwardSensitivityModelEvaluator</name>
      <anchorfile>classRythmos_1_1StateAndForwardSensitivityModelEvaluator.html</anchorfile>
      <anchor>a4a2941adde48906c19f94328a7f71b37</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initializeStructure</name>
      <anchorfile>classRythmos_1_1StateAndForwardSensitivityModelEvaluator.html</anchorfile>
      <anchor>abab5e9f37103ebb12edb6f93f30ae5b4</anchor>
      <arglist>(const Teuchos::RCP&lt; const ForwardSensitivityModelEvaluatorBase&lt; Scalar &gt; &gt; &amp;sensModel)</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Thyra::DefaultProductVector&lt; Scalar &gt; &gt;</type>
      <name>create_x_bar_vec</name>
      <anchorfile>classRythmos_1_1StateAndForwardSensitivityModelEvaluator.html</anchorfile>
      <anchor>a4c119044d4f74412074cb3596858f660</anchor>
      <arglist>(const Teuchos::RCP&lt; const Thyra::VectorBase&lt; Scalar &gt; &gt; &amp;x_vec, const Teuchos::RCP&lt; const Thyra::VectorBase&lt; Scalar &gt; &gt; &amp;s_bar_vec) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Np</name>
      <anchorfile>classRythmos_1_1StateAndForwardSensitivityModelEvaluator.html</anchorfile>
      <anchor>a0a96718fa10d1a15916f66a7b6b26fd3</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Thyra::VectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>get_p_space</name>
      <anchorfile>classRythmos_1_1StateAndForwardSensitivityModelEvaluator.html</anchorfile>
      <anchor>a3ce30fc1c3b3894daa4fb61475cfcbe8</anchor>
      <arglist>(int l) const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Teuchos::Array&lt; std::string &gt; &gt;</type>
      <name>get_p_names</name>
      <anchorfile>classRythmos_1_1StateAndForwardSensitivityModelEvaluator.html</anchorfile>
      <anchor>a7314ca72396b035458ba66ba7e57dd9a</anchor>
      <arglist>(int l) const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Thyra::VectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>get_x_space</name>
      <anchorfile>classRythmos_1_1StateAndForwardSensitivityModelEvaluator.html</anchorfile>
      <anchor>a3b293a40901ca0889c9f044248c52146</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Thyra::VectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>get_f_space</name>
      <anchorfile>classRythmos_1_1StateAndForwardSensitivityModelEvaluator.html</anchorfile>
      <anchor>aae4ff436034e38d90faecd81790ed229</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Thyra::ModelEvaluatorBase::InArgs&lt; Scalar &gt;</type>
      <name>getNominalValues</name>
      <anchorfile>classRythmos_1_1StateAndForwardSensitivityModelEvaluator.html</anchorfile>
      <anchor>aa38e7a29e366398864c4192804a67edd</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; Thyra::LinearOpWithSolveBase&lt; Scalar &gt; &gt;</type>
      <name>create_W</name>
      <anchorfile>classRythmos_1_1StateAndForwardSensitivityModelEvaluator.html</anchorfile>
      <anchor>a9211ad2e0763fbef254d150858f7688e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Thyra::ModelEvaluatorBase::InArgs&lt; Scalar &gt;</type>
      <name>createInArgs</name>
      <anchorfile>classRythmos_1_1StateAndForwardSensitivityModelEvaluator.html</anchorfile>
      <anchor>a5a4939a26e3d345ad10beadebdabfee0</anchor>
      <arglist>() const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Rythmos::StateSerializerStrategy</name>
    <filename>classRythmos_1_1StateSerializerStrategy.html</filename>
    <templarg>Scalar</templarg>
  </compound>
  <compound kind="struct">
    <name>Rythmos::StepControlInfo</name>
    <filename>classRythmos_1_1StepControlInfo.html</filename>
    <templarg>Scalar</templarg>
    <member kind="function">
      <type></type>
      <name>StepControlInfo</name>
      <anchorfile>classRythmos_1_1StepControlInfo.html</anchorfile>
      <anchor>a65dd516f6de41656a89ba0d5d1ff3fd4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable">
      <type>Scalar</type>
      <name>stepSize</name>
      <anchorfile>classRythmos_1_1StepControlInfo.html</anchorfile>
      <anchor>a2c3e3dff8c83d47c5ac38da180572ff2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>StepSizeType</type>
      <name>stepType</name>
      <anchorfile>classRythmos_1_1StepControlInfo.html</anchorfile>
      <anchor>af6dccda59ba30331e0d4d402652924fe</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>limitedByBreakPoint</name>
      <anchorfile>classRythmos_1_1StepControlInfo.html</anchorfile>
      <anchor>a24ebeb2d7e0f38a2a82bf33757b00c51</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>EBreakPointType</type>
      <name>breakPointType</name>
      <anchorfile>classRythmos_1_1StepControlInfo.html</anchorfile>
      <anchor>a42a9e4da033bbe64fc374bd4b7d2fdcb</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>StepControlInfo&lt; Scalar &gt;</type>
      <name>stepCtrlInfoTaken</name>
      <anchorfile>classRythmos_1_1StepControlInfo.html</anchorfile>
      <anchor>ad0c6a10ece9dab570ff317a542366826</anchor>
      <arglist>(const StepControlInfo&lt; Scalar &gt; &amp;trialStepCtrlInfo, const Scalar &amp;stepSizeTaken)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Rythmos::StepControlStrategyAcceptingStepperBase</name>
    <filename>classRythmos_1_1StepControlStrategyAcceptingStepperBase.html</filename>
    <templarg></templarg>
    <base virtualness="virtual">Rythmos::StepperBase</base>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>setStepControlStrategy</name>
      <anchorfile>classRythmos_1_1StepControlStrategyAcceptingStepperBase.html</anchorfile>
      <anchor>ae7d0c7b17d114ccf9c70178c53e5ffcf</anchor>
      <arglist>(const Teuchos::RCP&lt; StepControlStrategyBase&lt; Scalar &gt; &gt; &amp;stepControlStrategy)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual Teuchos::RCP&lt; StepControlStrategyBase&lt; Scalar &gt; &gt;</type>
      <name>getNonconstStepControlStrategy</name>
      <anchorfile>classRythmos_1_1StepControlStrategyAcceptingStepperBase.html</anchorfile>
      <anchor>ac9b7532b206a267d473bf1ee622a96cf</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual Teuchos::RCP&lt; const StepControlStrategyBase&lt; Scalar &gt; &gt;</type>
      <name>getStepControlStrategy</name>
      <anchorfile>classRythmos_1_1StepControlStrategyAcceptingStepperBase.html</anchorfile>
      <anchor>a2efa56b6a51164c32b1900e843467c0e</anchor>
      <arglist>() const  =0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Rythmos::StepControlStrategyBase</name>
    <filename>classRythmos_1_1StepControlStrategyBase.html</filename>
    <templarg></templarg>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>initialize</name>
      <anchorfile>classRythmos_1_1StepControlStrategyBase.html</anchorfile>
      <anchor>ac618248872dddcd594ce2e4651353a2e</anchor>
      <arglist>(const StepperBase&lt; Scalar &gt; &amp;stepper)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>setRequestedStepSize</name>
      <anchorfile>classRythmos_1_1StepControlStrategyBase.html</anchorfile>
      <anchor>a3777eece027452725dd6bf5775bd490c</anchor>
      <arglist>(const StepperBase&lt; Scalar &gt; &amp;stepper, const Scalar &amp;stepSize, const StepSizeType &amp;stepSizeType)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>nextStepSize</name>
      <anchorfile>classRythmos_1_1StepControlStrategyBase.html</anchorfile>
      <anchor>a8a100ca90e8d0d07b85dd35bb9b1308a</anchor>
      <arglist>(const StepperBase&lt; Scalar &gt; &amp;stepper, Scalar *stepSize, StepSizeType *stepSizeType, int *order)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>setCorrection</name>
      <anchorfile>classRythmos_1_1StepControlStrategyBase.html</anchorfile>
      <anchor>a0630d2831c664fa9e3ab4ab9f830f78a</anchor>
      <arglist>(const StepperBase&lt; Scalar &gt; &amp;stepper, const RCP&lt; const Thyra::VectorBase&lt; Scalar &gt; &gt; &amp;soln, const RCP&lt; const Thyra::VectorBase&lt; Scalar &gt; &gt; &amp;ee, int solveStatus)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>acceptStep</name>
      <anchorfile>classRythmos_1_1StepControlStrategyBase.html</anchorfile>
      <anchor>ae37c4c5481e03ae898b16a409cb30dd6</anchor>
      <arglist>(const StepperBase&lt; Scalar &gt; &amp;stepper, Scalar *LETValue)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>completeStep</name>
      <anchorfile>classRythmos_1_1StepControlStrategyBase.html</anchorfile>
      <anchor>a164b621e3b472fdac1f3af67d4c24577</anchor>
      <arglist>(const StepperBase&lt; Scalar &gt; &amp;stepper)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual AttemptedStepStatusFlag</type>
      <name>rejectStep</name>
      <anchorfile>classRythmos_1_1StepControlStrategyBase.html</anchorfile>
      <anchor>aa0468a1df6753b6ecdb3880d40cba80c</anchor>
      <arglist>(const StepperBase&lt; Scalar &gt; &amp;stepper)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual StepControlStrategyState</type>
      <name>getCurrentState</name>
      <anchorfile>classRythmos_1_1StepControlStrategyBase.html</anchorfile>
      <anchor>afb1a0deebc55b9c2e934538124d1b3e8</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>getMaxOrder</name>
      <anchorfile>classRythmos_1_1StepControlStrategyBase.html</anchorfile>
      <anchor>ab25dfb77a2f747e4c56a47f2980a5d8a</anchor>
      <arglist>() const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>setStepControlData</name>
      <anchorfile>classRythmos_1_1StepControlStrategyBase.html</anchorfile>
      <anchor>a81a1d14bb8b8cb8a2666d5d064b5f446</anchor>
      <arglist>(const StepperBase&lt; Scalar &gt; &amp;stepper)=0</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>supportsCloning</name>
      <anchorfile>classRythmos_1_1StepControlStrategyBase.html</anchorfile>
      <anchor>ad59a710fcb298ef19e252a8f8ab93fc5</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual RCP&lt; StepControlStrategyBase&lt; Scalar &gt; &gt;</type>
      <name>cloneStepControlStrategyAlgorithm</name>
      <anchorfile>classRythmos_1_1StepControlStrategyBase.html</anchorfile>
      <anchor>a017dc8635fa73afa9b563eb4f285d960</anchor>
      <arglist>() const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Rythmos::StepperAsModelEvaluator</name>
    <filename>classRythmos_1_1StepperAsModelEvaluator.html</filename>
    <templarg></templarg>
    <member kind="function">
      <type></type>
      <name>StepperAsModelEvaluator</name>
      <anchorfile>classRythmos_1_1StepperAsModelEvaluator.html</anchorfile>
      <anchor>ad392785a5d13690eae28e4f6f307545c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initialize</name>
      <anchorfile>classRythmos_1_1StepperAsModelEvaluator.html</anchorfile>
      <anchor>aff21d8eb6e95c3d79c6fa51a6d005e31</anchor>
      <arglist>(const RCP&lt; StepperBase&lt; Scalar &gt; &gt; &amp;stepper, const RCP&lt; IntegratorBase&lt; Scalar &gt; &gt; &amp;integrator, const Thyra::ModelEvaluatorBase::InArgs&lt; Scalar &gt; &amp;initialCondition)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Np</name>
      <anchorfile>classRythmos_1_1StepperAsModelEvaluator.html</anchorfile>
      <anchor>a5ae43dd25e90b9bfb686a0dc7ffb421c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Ng</name>
      <anchorfile>classRythmos_1_1StepperAsModelEvaluator.html</anchorfile>
      <anchor>a46056237f0243b402ae2915476da0373</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const Thyra::VectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>get_p_space</name>
      <anchorfile>classRythmos_1_1StepperAsModelEvaluator.html</anchorfile>
      <anchor>a6b12bf9477a00750b92a93b5d2e87502</anchor>
      <arglist>(int l) const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const Thyra::VectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>get_g_space</name>
      <anchorfile>classRythmos_1_1StepperAsModelEvaluator.html</anchorfile>
      <anchor>ae2b539905c031d1843cac71b7951a3c7</anchor>
      <arglist>(int j) const </arglist>
    </member>
    <member kind="function">
      <type>Thyra::ModelEvaluatorBase::InArgs&lt; Scalar &gt;</type>
      <name>createInArgs</name>
      <anchorfile>classRythmos_1_1StepperAsModelEvaluator.html</anchorfile>
      <anchor>a1266d647ee7f3d0c84cce57ff1ff62ac</anchor>
      <arglist>() const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Rythmos::StepperBase</name>
    <filename>classRythmos_1_1StepperBase.html</filename>
    <templarg>Scalar</templarg>
    <base virtualness="virtual">Rythmos::InterpolationBufferBase</base>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>supportsCloning</name>
      <anchorfile>classRythmos_1_1StepperBase.html</anchorfile>
      <anchor>a4f71c4f04c88745e7e78c68f49a4f68b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual RCP&lt; StepperBase&lt; Scalar &gt; &gt;</type>
      <name>cloneStepperAlgorithm</name>
      <anchorfile>classRythmos_1_1StepperBase.html</anchorfile>
      <anchor>a82256479f52e9284f6ec7e5db509ec01</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>isImplicit</name>
      <anchorfile>classRythmos_1_1StepperBase.html</anchorfile>
      <anchor>a3585dd74abecfc5c243c36b635312ddf</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>acceptsModel</name>
      <anchorfile>classRythmos_1_1StepperBase.html</anchorfile>
      <anchor>ab8ef2e6e520210fb731eedb731277d92</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>setModel</name>
      <anchorfile>classRythmos_1_1StepperBase.html</anchorfile>
      <anchor>a69b74034084ed775e90797571750518a</anchor>
      <arglist>(const RCP&lt; const Thyra::ModelEvaluator&lt; Scalar &gt; &gt; &amp;model)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>setNonconstModel</name>
      <anchorfile>classRythmos_1_1StepperBase.html</anchorfile>
      <anchor>a7c7f8fc6af17c64aeffa9dc8f4fe9eee</anchor>
      <arglist>(const RCP&lt; Thyra::ModelEvaluator&lt; Scalar &gt; &gt; &amp;model)=0</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>modelIsConst</name>
      <anchorfile>classRythmos_1_1StepperBase.html</anchorfile>
      <anchor>a92ad3060feb6e73213d49fc5f654295c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual RCP&lt; const Thyra::ModelEvaluator&lt; Scalar &gt; &gt;</type>
      <name>getModel</name>
      <anchorfile>classRythmos_1_1StepperBase.html</anchorfile>
      <anchor>ab2bb8236d59bfebe5cef9a169d7be083</anchor>
      <arglist>() const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual RCP&lt; Thyra::ModelEvaluator&lt; Scalar &gt; &gt;</type>
      <name>getNonconstModel</name>
      <anchorfile>classRythmos_1_1StepperBase.html</anchorfile>
      <anchor>a760c2f8eadf3e2bda242b7ca204a7739</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>setInitialCondition</name>
      <anchorfile>classRythmos_1_1StepperBase.html</anchorfile>
      <anchor>ae3a20220aa0a565e763b1399a1257976</anchor>
      <arglist>(const Thyra::ModelEvaluatorBase::InArgs&lt; Scalar &gt; &amp;initialCondition)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual Thyra::ModelEvaluatorBase::InArgs&lt; Scalar &gt;</type>
      <name>getInitialCondition</name>
      <anchorfile>classRythmos_1_1StepperBase.html</anchorfile>
      <anchor>a0b37e02d12d30e713cc53fed0f844a44</anchor>
      <arglist>() const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual Scalar</type>
      <name>takeStep</name>
      <anchorfile>classRythmos_1_1StepperBase.html</anchorfile>
      <anchor>a48aac5b1c6e50945d927ffbd12512146</anchor>
      <arglist>(Scalar dt, StepSizeType stepType)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual const StepStatus&lt; Scalar &gt;</type>
      <name>getStepStatus</name>
      <anchorfile>classRythmos_1_1StepperBase.html</anchorfile>
      <anchor>ae26724f241dea9c5d460ab12b1955551</anchor>
      <arglist>() const  =0</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>setStepControlData</name>
      <anchorfile>classRythmos_1_1StepperBase.html</anchorfile>
      <anchor>a4b683541ee064a9b21ea2edf87c6a6b0</anchor>
      <arglist>(const StepperBase &amp;stepper)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isInitialized</name>
      <anchorfile>classRythmos_1_1StepperBase.html</anchorfile>
      <anchor>ac6d8ad200624199b40970d3628da7e06</anchor>
      <arglist>(const StepperBase&lt; Scalar &gt; &amp;stepper)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isInitialized</name>
      <anchorfile>classRythmos_1_1StepperBase.html</anchorfile>
      <anchor>ac6d8ad200624199b40970d3628da7e06</anchor>
      <arglist>(const StepperBase&lt; Scalar &gt; &amp;stepper)</arglist>
    </member>
    <docanchor file="classRythmos_1_1StepperBase" title="states">Initialization</docanchor>
  </compound>
  <compound kind="class">
    <name>Rythmos::StepperValidator</name>
    <filename>classRythmos_1_1StepperValidator.html</filename>
    <templarg></templarg>
    <member kind="function">
      <type>void</type>
      <name>setIntegratorBuilder</name>
      <anchorfile>classRythmos_1_1StepperValidator.html</anchorfile>
      <anchor>ae887be2e938fe163c153523196181ac7</anchor>
      <arglist>(const RCP&lt; IntegratorBuilder&lt; Scalar &gt; &gt; &amp;integratorBuilder)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>validateStepper</name>
      <anchorfile>classRythmos_1_1StepperValidator.html</anchorfile>
      <anchor>a47ee620676943b73824de2ed7a6e3da2</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setParameterList</name>
      <anchorfile>classRythmos_1_1StepperValidator.html</anchorfile>
      <anchor>a51f3e2668cffb09b5d967d9b8bd20409</anchor>
      <arglist>(RCP&lt; Teuchos::ParameterList &gt; const &amp;paramList)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; Teuchos::ParameterList &gt;</type>
      <name>getNonconstParameterList</name>
      <anchorfile>classRythmos_1_1StepperValidator.html</anchorfile>
      <anchor>af9cec81dd2731cc8b217da89b629c544</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; Teuchos::ParameterList &gt;</type>
      <name>unsetParameterList</name>
      <anchorfile>classRythmos_1_1StepperValidator.html</anchorfile>
      <anchor>aa1d4d6db202f12e8db4fbe4a1ce51f35</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const Teuchos::ParameterList &gt;</type>
      <name>getValidParameters</name>
      <anchorfile>classRythmos_1_1StepperValidator.html</anchorfile>
      <anchor>af54f9c62c295328db8c70d3ef93726fd</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>description</name>
      <anchorfile>classRythmos_1_1StepperValidator.html</anchorfile>
      <anchor>ab736aee5db2e7168aca37b0f7bbf2af4</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>describe</name>
      <anchorfile>classRythmos_1_1StepperValidator.html</anchorfile>
      <anchor>ada194b11a7c4c64b538c101634a0f724</anchor>
      <arglist>(Teuchos::FancyOStream &amp;out, const Teuchos::EVerbosityLevel verbLevel) const </arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>Rythmos::StepStatus</name>
    <filename>structRythmos_1_1StepStatus.html</filename>
    <templarg>Scalar</templarg>
    <member kind="function">
      <type></type>
      <name>StepStatus</name>
      <anchorfile>structRythmos_1_1StepStatus.html</anchorfile>
      <anchor>a46f3d9a94bad2476eee300039b888c58</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable">
      <type>std::string</type>
      <name>message</name>
      <anchorfile>structRythmos_1_1StepStatus.html</anchorfile>
      <anchor>a921cbaadd579bff7bc4cb36d6159b996</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>EStepStatus</type>
      <name>stepStatus</name>
      <anchorfile>structRythmos_1_1StepStatus.html</anchorfile>
      <anchor>aa62b58c458d3f0c9c12dd784ea610ed5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>EStepLETStatus</type>
      <name>stepLETStatus</name>
      <anchorfile>structRythmos_1_1StepStatus.html</anchorfile>
      <anchor>a586a67829671778a11635273ec2b9721</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>Scalar</type>
      <name>stepSize</name>
      <anchorfile>structRythmos_1_1StepStatus.html</anchorfile>
      <anchor>a25acacb8d40125f84666bc033dadd9e0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>order</name>
      <anchorfile>structRythmos_1_1StepStatus.html</anchorfile>
      <anchor>af1ac2ab45a777c30ac026faa011e90e0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>Scalar</type>
      <name>time</name>
      <anchorfile>structRythmos_1_1StepStatus.html</anchorfile>
      <anchor>ad6c3e76c6319c9cab2872d0e253bdec2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>Scalar</type>
      <name>stepLETValue</name>
      <anchorfile>structRythmos_1_1StepStatus.html</anchorfile>
      <anchor>a1d34e1669d3df12d843732f62cb91ef6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>RCP&lt; const Thyra::VectorBase&lt; Scalar &gt; &gt;</type>
      <name>solution</name>
      <anchorfile>structRythmos_1_1StepStatus.html</anchorfile>
      <anchor>a659f644dd1b8f4d663b6bfc6577d6506</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>RCP&lt; const Thyra::VectorBase&lt; Scalar &gt; &gt;</type>
      <name>solutionDot</name>
      <anchorfile>structRythmos_1_1StepStatus.html</anchorfile>
      <anchor>af8ca5371f551edbce3014d8c46c96688</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>RCP&lt; const Thyra::VectorBase&lt; Scalar &gt; &gt;</type>
      <name>residual</name>
      <anchorfile>structRythmos_1_1StepStatus.html</anchorfile>
      <anchor>ab39a8c9cdfce62fa0bc8471876270b84</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>RCP&lt; const Teuchos::ParameterList &gt;</type>
      <name>extraParameters</name>
      <anchorfile>structRythmos_1_1StepStatus.html</anchorfile>
      <anchor>acd273fa8e80575394f53742e1a51f87e</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Rythmos::ThetaStepper</name>
    <filename>classRythmos_1_1ThetaStepper.html</filename>
    <templarg></templarg>
    <base virtualness="virtual">Rythmos::SolverAcceptingStepperBase</base>
    <base virtualness="virtual">Rythmos::InterpolatorAcceptingObjectBase</base>
    <member kind="typedef">
      <type>Teuchos::ScalarTraits&lt; Scalar &gt;::magnitudeType</type>
      <name>ScalarMag</name>
      <anchorfile>classRythmos_1_1ThetaStepper.html</anchorfile>
      <anchor>a084b667e801b0866b6d6a854753f2d1e</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; ThetaStepper&lt; Scalar &gt; &gt;</type>
      <name>thetaStepper</name>
      <anchorfile>classRythmos_1_1ThetaStepper.html</anchorfile>
      <anchor>af22333cd83717ca49c49b08fbca6f588</anchor>
      <arglist>(const RCP&lt; Thyra::ModelEvaluator&lt; Scalar &gt; &gt; &amp;model, const RCP&lt; Thyra::NonlinearSolverBase&lt; Scalar &gt; &gt; &amp;solver, RCP&lt; Teuchos::ParameterList &gt; &amp;parameterList)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ThetaStepper</name>
      <anchorfile>classRythmos_1_1ThetaStepper.html</anchorfile>
      <anchor>ad2af4cee97b46f3c709c414e93d2f658</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isImplicit</name>
      <anchorfile>classRythmos_1_1ThetaStepper.html</anchorfile>
      <anchor>a88c8fe7b39940ad80b679146bd29d0d0</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setInterpolator</name>
      <anchorfile>classRythmos_1_1ThetaStepper.html</anchorfile>
      <anchor>a2f23f126885977a0a3c859954e0eb49c</anchor>
      <arglist>(const RCP&lt; InterpolatorBase&lt; Scalar &gt; &gt; &amp;interpolator)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; InterpolatorBase&lt; Scalar &gt; &gt;</type>
      <name>getNonconstInterpolator</name>
      <anchorfile>classRythmos_1_1ThetaStepper.html</anchorfile>
      <anchor>a854abb91ae9071a03500852c16cd3408</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const InterpolatorBase&lt; Scalar &gt; &gt;</type>
      <name>getInterpolator</name>
      <anchorfile>classRythmos_1_1ThetaStepper.html</anchorfile>
      <anchor>a83628b61feccc474ebe549fb506e5f2e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; InterpolatorBase&lt; Scalar &gt; &gt;</type>
      <name>unSetInterpolator</name>
      <anchorfile>classRythmos_1_1ThetaStepper.html</anchorfile>
      <anchor>a283677a4b4a836ed19d01eb20c21e846</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setSolver</name>
      <anchorfile>classRythmos_1_1ThetaStepper.html</anchorfile>
      <anchor>aef578850560354cc702255d988826828</anchor>
      <arglist>(const RCP&lt; Thyra::NonlinearSolverBase&lt; Scalar &gt; &gt; &amp;solver)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; Thyra::NonlinearSolverBase&lt; Scalar &gt; &gt;</type>
      <name>getNonconstSolver</name>
      <anchorfile>classRythmos_1_1ThetaStepper.html</anchorfile>
      <anchor>aba9fb73c9befb0a9e5d5c819e571c95b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const Thyra::NonlinearSolverBase&lt; Scalar &gt; &gt;</type>
      <name>getSolver</name>
      <anchorfile>classRythmos_1_1ThetaStepper.html</anchorfile>
      <anchor>af87f6e1829e0f5b4ade493c4b69ea9e0</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>supportsCloning</name>
      <anchorfile>classRythmos_1_1ThetaStepper.html</anchorfile>
      <anchor>aabf46a805220c69a2a88650ca5ed6de5</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; StepperBase&lt; Scalar &gt; &gt;</type>
      <name>cloneStepperAlgorithm</name>
      <anchorfile>classRythmos_1_1ThetaStepper.html</anchorfile>
      <anchor>a9c4530c7fc7ecb27d352b265ba9b20c7</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setModel</name>
      <anchorfile>classRythmos_1_1ThetaStepper.html</anchorfile>
      <anchor>a95a61fc15a9c1058edaa2c3fbfab90d3</anchor>
      <arglist>(const RCP&lt; const Thyra::ModelEvaluator&lt; Scalar &gt; &gt; &amp;model)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setNonconstModel</name>
      <anchorfile>classRythmos_1_1ThetaStepper.html</anchorfile>
      <anchor>a97916f87ca54841beb8b972801b07314</anchor>
      <arglist>(const RCP&lt; Thyra::ModelEvaluator&lt; Scalar &gt; &gt; &amp;model)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const Thyra::ModelEvaluator&lt; Scalar &gt; &gt;</type>
      <name>getModel</name>
      <anchorfile>classRythmos_1_1ThetaStepper.html</anchorfile>
      <anchor>aebf89d212f813797f9b2f84b47764cf3</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; Thyra::ModelEvaluator&lt; Scalar &gt; &gt;</type>
      <name>getNonconstModel</name>
      <anchorfile>classRythmos_1_1ThetaStepper.html</anchorfile>
      <anchor>a2f32e273bb01f78a6aee155afa7cd89a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setInitialCondition</name>
      <anchorfile>classRythmos_1_1ThetaStepper.html</anchorfile>
      <anchor>ace21fe029403cf60e4cd9ae5d5ba482b</anchor>
      <arglist>(const Thyra::ModelEvaluatorBase::InArgs&lt; Scalar &gt; &amp;initialCondition)</arglist>
    </member>
    <member kind="function">
      <type>Thyra::ModelEvaluatorBase::InArgs&lt; Scalar &gt;</type>
      <name>getInitialCondition</name>
      <anchorfile>classRythmos_1_1ThetaStepper.html</anchorfile>
      <anchor>ad9e89213679997f922468292ee888ea6</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Scalar</type>
      <name>takeStep</name>
      <anchorfile>classRythmos_1_1ThetaStepper.html</anchorfile>
      <anchor>a5ba0a7525ee4a96ed744b5243526b91f</anchor>
      <arglist>(Scalar dt, StepSizeType flag)</arglist>
    </member>
    <member kind="function">
      <type>const StepStatus&lt; Scalar &gt;</type>
      <name>getStepStatus</name>
      <anchorfile>classRythmos_1_1ThetaStepper.html</anchorfile>
      <anchor>aeebd113cca74423594ff09b772bd5276</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const Thyra::VectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>get_x_space</name>
      <anchorfile>classRythmos_1_1ThetaStepper.html</anchorfile>
      <anchor>a036652b814547efd6faca0e079948dcc</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>addPoints</name>
      <anchorfile>classRythmos_1_1ThetaStepper.html</anchorfile>
      <anchor>aaa551441b8ea8cf2657243e3afab5542</anchor>
      <arglist>(const Array&lt; Scalar &gt; &amp;time_vec, const Array&lt; RCP&lt; const Thyra::VectorBase&lt; Scalar &gt; &gt; &gt; &amp;x_vec, const Array&lt; RCP&lt; const Thyra::VectorBase&lt; Scalar &gt; &gt; &gt; &amp;xdot_vec)</arglist>
    </member>
    <member kind="function">
      <type>TimeRange&lt; Scalar &gt;</type>
      <name>getTimeRange</name>
      <anchorfile>classRythmos_1_1ThetaStepper.html</anchorfile>
      <anchor>a8b5d6d2cad01f821ac8388252c7d5b39</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>getPoints</name>
      <anchorfile>classRythmos_1_1ThetaStepper.html</anchorfile>
      <anchor>a2da6aed156c8367421a33061dfa6d08f</anchor>
      <arglist>(const Array&lt; Scalar &gt; &amp;time_vec, Array&lt; RCP&lt; const Thyra::VectorBase&lt; Scalar &gt; &gt; &gt; *x_vec, Array&lt; RCP&lt; const Thyra::VectorBase&lt; Scalar &gt; &gt; &gt; *xdot_vec, Array&lt; ScalarMag &gt; *accuracy_vec) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>getNodes</name>
      <anchorfile>classRythmos_1_1ThetaStepper.html</anchorfile>
      <anchor>a42e798b4bb8d3cbaaa18c04152789707</anchor>
      <arglist>(Array&lt; Scalar &gt; *time_vec) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>removeNodes</name>
      <anchorfile>classRythmos_1_1ThetaStepper.html</anchorfile>
      <anchor>a054db20207f83cf60e1f03f976b5e26e</anchor>
      <arglist>(Array&lt; Scalar &gt; &amp;time_vec)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getOrder</name>
      <anchorfile>classRythmos_1_1ThetaStepper.html</anchorfile>
      <anchor>a48b76e9025f467ec341a8c728f1abd48</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setParameterList</name>
      <anchorfile>classRythmos_1_1ThetaStepper.html</anchorfile>
      <anchor>a814b7b7a25e4dc07a5df5b967e7d4c25</anchor>
      <arglist>(RCP&lt; Teuchos::ParameterList &gt; const &amp;paramList)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; Teuchos::ParameterList &gt;</type>
      <name>getNonconstParameterList</name>
      <anchorfile>classRythmos_1_1ThetaStepper.html</anchorfile>
      <anchor>a5352be90242af744b89a719f81bd9c56</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; Teuchos::ParameterList &gt;</type>
      <name>unsetParameterList</name>
      <anchorfile>classRythmos_1_1ThetaStepper.html</anchorfile>
      <anchor>af3d974b0a32a4294f0205fc52223f7aa</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const Teuchos::ParameterList &gt;</type>
      <name>getValidParameters</name>
      <anchorfile>classRythmos_1_1ThetaStepper.html</anchorfile>
      <anchor>a5894e1f51ba16672cadd8aa7d2aa9738</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>describe</name>
      <anchorfile>classRythmos_1_1ThetaStepper.html</anchorfile>
      <anchor>a569bcde0abd4a5781d2fd21b607d11d6</anchor>
      <arglist>(Teuchos::FancyOStream &amp;out, const Teuchos::EVerbosityLevel verbLevel) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Rythmos::TimeDiscretizedBackwardEulerModelEvaluator</name>
    <filename>classRythmos_1_1TimeDiscretizedBackwardEulerModelEvaluator.html</filename>
    <templarg></templarg>
    <member kind="function">
      <type>RCP&lt; TimeDiscretizedBackwardEulerModelEvaluator&lt; Scalar &gt; &gt;</type>
      <name>timeDiscretizedBackwardEulerModelEvaluator</name>
      <anchorfile>classRythmos_1_1TimeDiscretizedBackwardEulerModelEvaluator.html</anchorfile>
      <anchor>a27360e5f056cc3f266df75e201e64e9a</anchor>
      <arglist>(const RCP&lt; const Thyra::ModelEvaluator&lt; Scalar &gt; &gt; &amp;daeModel, const Thyra::ModelEvaluatorBase::InArgs&lt; Scalar &gt; &amp;initCond, const Scalar finalTime, const int numTimeSteps, const RCP&lt; Thyra::LinearOpWithSolveFactoryBase&lt; Scalar &gt; &gt; &amp;W_bar_factory)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>TimeDiscretizedBackwardEulerModelEvaluator</name>
      <anchorfile>classRythmos_1_1TimeDiscretizedBackwardEulerModelEvaluator.html</anchorfile>
      <anchor>ae10e421030af8829db7aa9e6f7947839</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initialize</name>
      <anchorfile>classRythmos_1_1TimeDiscretizedBackwardEulerModelEvaluator.html</anchorfile>
      <anchor>a44c65334d00d636c5abd019d04d5b3d8</anchor>
      <arglist>(const RCP&lt; const Thyra::ModelEvaluator&lt; Scalar &gt; &gt; &amp;daeModel, const Thyra::ModelEvaluatorBase::InArgs&lt; Scalar &gt; &amp;initCond, const Scalar finalTime, const int numTimeSteps, const RCP&lt; Thyra::LinearOpWithSolveFactoryBase&lt; Scalar &gt; &gt; &amp;W_bar_factory=Teuchos::null)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const Thyra::VectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>get_x_space</name>
      <anchorfile>classRythmos_1_1TimeDiscretizedBackwardEulerModelEvaluator.html</anchorfile>
      <anchor>a3a4e7e0ef54a9d966acf09f6708e9e93</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const Thyra::VectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>get_f_space</name>
      <anchorfile>classRythmos_1_1TimeDiscretizedBackwardEulerModelEvaluator.html</anchorfile>
      <anchor>a29f07ab7e13e000e8ee75178cc09b6c8</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; Thyra::LinearOpBase&lt; Scalar &gt; &gt;</type>
      <name>create_W_op</name>
      <anchorfile>classRythmos_1_1TimeDiscretizedBackwardEulerModelEvaluator.html</anchorfile>
      <anchor>a2cf24940e52d516b92d4d27d71890d99</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const Thyra::LinearOpWithSolveFactoryBase&lt; Scalar &gt; &gt;</type>
      <name>get_W_factory</name>
      <anchorfile>classRythmos_1_1TimeDiscretizedBackwardEulerModelEvaluator.html</anchorfile>
      <anchor>a20aa6ccec941d2ad35ebbd4c31576ccf</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Thyra::ModelEvaluatorBase::InArgs&lt; Scalar &gt;</type>
      <name>getNominalValues</name>
      <anchorfile>classRythmos_1_1TimeDiscretizedBackwardEulerModelEvaluator.html</anchorfile>
      <anchor>acf7d173c1d063822b4d13d32b20b9589</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Thyra::ModelEvaluatorBase::InArgs&lt; Scalar &gt;</type>
      <name>createInArgs</name>
      <anchorfile>classRythmos_1_1TimeDiscretizedBackwardEulerModelEvaluator.html</anchorfile>
      <anchor>a61e8cdf7926242621ee955bd8465bf09</anchor>
      <arglist>() const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Rythmos::TimeRange</name>
    <filename>classRythmos_1_1TimeRange.html</filename>
    <templarg>TimeType</templarg>
    <member kind="function">
      <type></type>
      <name>TimeRange</name>
      <anchorfile>classRythmos_1_1TimeRange.html</anchorfile>
      <anchor>ae659826e7c16360e8edf4c9019c46a74</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>TimeRange</name>
      <anchorfile>classRythmos_1_1TimeRange.html</anchorfile>
      <anchor>a7c6b1228192fce3ed4c1ba89eb9458f5</anchor>
      <arglist>(const TimeType &amp;my_lower, const TimeType &amp;my_upper)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>TimeRange</name>
      <anchorfile>classRythmos_1_1TimeRange.html</anchorfile>
      <anchor>a044ad8dcfaa0d28c38dab2ce196ac870</anchor>
      <arglist>(const TimeRange&lt; TimeType &gt; &amp;tr)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~TimeRange</name>
      <anchorfile>classRythmos_1_1TimeRange.html</anchorfile>
      <anchor>a3177f06e8c08f0342c849e8b8af1d260</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isValid</name>
      <anchorfile>classRythmos_1_1TimeRange.html</anchorfile>
      <anchor>ac766d3550a395270ec9f17dbdec8e799</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>TimeType</type>
      <name>lower</name>
      <anchorfile>classRythmos_1_1TimeRange.html</anchorfile>
      <anchor>a8409e3b17e6cc8ae396bc47ddb8a15b0</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>TimeType</type>
      <name>upper</name>
      <anchorfile>classRythmos_1_1TimeRange.html</anchorfile>
      <anchor>aeb7c0cf688e9e68b6e17da63a790db9e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>TimeType</type>
      <name>length</name>
      <anchorfile>classRythmos_1_1TimeRange.html</anchorfile>
      <anchor>a31fee9dca24e5be07828e70878b6d18d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>isInRange</name>
      <anchorfile>classRythmos_1_1TimeRange.html</anchorfile>
      <anchor>abb1596efc1d82a60d0a598a14cd35f05</anchor>
      <arglist>(const TimeType &amp;t) const </arglist>
    </member>
    <member kind="function">
      <type>TimeRange&lt; TimeType &gt;</type>
      <name>copyAndScale</name>
      <anchorfile>classRythmos_1_1TimeRange.html</anchorfile>
      <anchor>aaeea531b1ae14ba529b244ea5c93b877</anchor>
      <arglist>(const TimeType &amp;scale) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>compareTimeValues</name>
      <anchorfile>classRythmos_1_1TimeRange.html</anchorfile>
      <anchor>a35d8d0fd9365159c5da6399d87ed4adf</anchor>
      <arglist>(const TimeType &amp;t1, const TimeType &amp;t2)</arglist>
    </member>
    <member kind="function">
      <type>TimeRange&lt; TimeType &gt;</type>
      <name>timeRange</name>
      <anchorfile>classRythmos_1_1TimeRange.html</anchorfile>
      <anchor>ae835e58c68a64c433e725ff8eb8c95ae</anchor>
      <arglist>(const TimeType my_lower, const TimeType my_upper)</arglist>
    </member>
    <member kind="function">
      <type>TimeRange&lt; TimeType &gt;</type>
      <name>invalidTimeRange</name>
      <anchorfile>classRythmos_1_1TimeRange.html</anchorfile>
      <anchor>a4703bca48e619d24bd10a1444339b467</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>std::ostream &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>classRythmos_1_1TimeRange.html</anchorfile>
      <anchor>a0c9a3818c829e7b44564e8eb04d81787</anchor>
      <arglist>(std::ostream &amp;out, const TimeRange&lt; TimeType &gt; &amp;range)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isInRange_cc</name>
      <anchorfile>classRythmos_1_1TimeRange.html</anchorfile>
      <anchor>acb5a6994c1f48ffe52d8b93c4e437858</anchor>
      <arglist>(const TimeRange&lt; TimeType &gt; &amp;tr, const TimeType &amp;p)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isInRange_oc</name>
      <anchorfile>classRythmos_1_1TimeRange.html</anchorfile>
      <anchor>ad4c26a1f3e836925d596e1f867504a29</anchor>
      <arglist>(const TimeRange&lt; TimeType &gt; &amp;tr, const TimeType &amp;p)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isInRange_co</name>
      <anchorfile>classRythmos_1_1TimeRange.html</anchorfile>
      <anchor>a4f911d48c50fcf862fa3bcd0a4ec9d02</anchor>
      <arglist>(const TimeRange&lt; TimeType &gt; &amp;tr, const TimeType &amp;p)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isInRange_oo</name>
      <anchorfile>classRythmos_1_1TimeRange.html</anchorfile>
      <anchor>a473f0c9160578f33294b4658b0c933b0</anchor>
      <arglist>(const TimeRange&lt; TimeType &gt; &amp;tr, const TimeType &amp;p)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>TimeRange&lt; Scalar &gt;</name>
    <filename>classRythmos_1_1TimeRange.html</filename>
    <member kind="function">
      <type></type>
      <name>TimeRange</name>
      <anchorfile>classRythmos_1_1TimeRange.html</anchorfile>
      <anchor>ae659826e7c16360e8edf4c9019c46a74</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>TimeRange</name>
      <anchorfile>classRythmos_1_1TimeRange.html</anchorfile>
      <anchor>a7c6b1228192fce3ed4c1ba89eb9458f5</anchor>
      <arglist>(const Scalar &amp;my_lower, const Scalar &amp;my_upper)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>TimeRange</name>
      <anchorfile>classRythmos_1_1TimeRange.html</anchorfile>
      <anchor>a044ad8dcfaa0d28c38dab2ce196ac870</anchor>
      <arglist>(const TimeRange&lt; Scalar &gt; &amp;tr)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~TimeRange</name>
      <anchorfile>classRythmos_1_1TimeRange.html</anchorfile>
      <anchor>a3177f06e8c08f0342c849e8b8af1d260</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isValid</name>
      <anchorfile>classRythmos_1_1TimeRange.html</anchorfile>
      <anchor>ac766d3550a395270ec9f17dbdec8e799</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>Scalar</type>
      <name>lower</name>
      <anchorfile>classRythmos_1_1TimeRange.html</anchorfile>
      <anchor>a8409e3b17e6cc8ae396bc47ddb8a15b0</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>Scalar</type>
      <name>upper</name>
      <anchorfile>classRythmos_1_1TimeRange.html</anchorfile>
      <anchor>aeb7c0cf688e9e68b6e17da63a790db9e</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>Scalar</type>
      <name>length</name>
      <anchorfile>classRythmos_1_1TimeRange.html</anchorfile>
      <anchor>a31fee9dca24e5be07828e70878b6d18d</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>isInRange</name>
      <anchorfile>classRythmos_1_1TimeRange.html</anchorfile>
      <anchor>abb1596efc1d82a60d0a598a14cd35f05</anchor>
      <arglist>(const Scalar &amp;t) const</arglist>
    </member>
    <member kind="function">
      <type>TimeRange&lt; Scalar &gt;</type>
      <name>copyAndScale</name>
      <anchorfile>classRythmos_1_1TimeRange.html</anchorfile>
      <anchor>aaeea531b1ae14ba529b244ea5c93b877</anchor>
      <arglist>(const Scalar &amp;scale) const</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Rythmos::TimeStepNonlinearSolver</name>
    <filename>classRythmos_1_1TimeStepNonlinearSolver.html</filename>
    <templarg></templarg>
    <member kind="typedef">
      <type>Teuchos::ScalarTraits&lt; Scalar &gt;</type>
      <name>ST</name>
      <anchorfile>classRythmos_1_1TimeStepNonlinearSolver.html</anchorfile>
      <anchor>a7d3b94a26bba2231531bcce1944830a7</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>ST::magnitudeType</type>
      <name>ScalarMag</name>
      <anchorfile>classRythmos_1_1TimeStepNonlinearSolver.html</anchorfile>
      <anchor>ae867ece767813b7804514bc00d2ebd74</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Teuchos::ScalarTraits&lt; ScalarMag &gt;</type>
      <name>SMT</name>
      <anchorfile>classRythmos_1_1TimeStepNonlinearSolver.html</anchorfile>
      <anchor>a75191c5a6fba964582aeb057cb7a53f5</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; TimeStepNonlinearSolver&lt; Scalar &gt; &gt;</type>
      <name>timeStepNonlinearSolver</name>
      <anchorfile>classRythmos_1_1TimeStepNonlinearSolver.html</anchorfile>
      <anchor>a6291e0a0996e3bc1aab2a2ce82663951</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; TimeStepNonlinearSolver&lt; Scalar &gt; &gt;</type>
      <name>timeStepNonlinearSolver</name>
      <anchorfile>classRythmos_1_1TimeStepNonlinearSolver.html</anchorfile>
      <anchor>a22932d78a5e7fa60696637ea4e66e935</anchor>
      <arglist>(const RCP&lt; ParameterList &gt; &amp;pl)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>TimeStepNonlinearSolver</name>
      <anchorfile>classRythmos_1_1TimeStepNonlinearSolver.html</anchorfile>
      <anchor>ae661fed8aa7c0abce6583601d56bf42a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setParameterList</name>
      <anchorfile>classRythmos_1_1TimeStepNonlinearSolver.html</anchorfile>
      <anchor>aacd24d426a43404a0e5174f1ddea9929</anchor>
      <arglist>(RCP&lt; ParameterList &gt; const &amp;paramList)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; ParameterList &gt;</type>
      <name>getNonconstParameterList</name>
      <anchorfile>classRythmos_1_1TimeStepNonlinearSolver.html</anchorfile>
      <anchor>ac20e52e230c14f163858ddefa6ed72ca</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; ParameterList &gt;</type>
      <name>unsetParameterList</name>
      <anchorfile>classRythmos_1_1TimeStepNonlinearSolver.html</anchorfile>
      <anchor>ae807db6cfa6dff662c693925684ca6df</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const ParameterList &gt;</type>
      <name>getParameterList</name>
      <anchorfile>classRythmos_1_1TimeStepNonlinearSolver.html</anchorfile>
      <anchor>a3c1eabd1122105519607ea556a38cf2b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const ParameterList &gt;</type>
      <name>getValidParameters</name>
      <anchorfile>classRythmos_1_1TimeStepNonlinearSolver.html</anchorfile>
      <anchor>a70afc4b5f8fc335cf2019492b8fbf735</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setModel</name>
      <anchorfile>classRythmos_1_1TimeStepNonlinearSolver.html</anchorfile>
      <anchor>ac7803e4e8897228d4709e4b9d232edab</anchor>
      <arglist>(const RCP&lt; const Thyra::ModelEvaluator&lt; Scalar &gt; &gt; &amp;model)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const Thyra::ModelEvaluator&lt; Scalar &gt; &gt;</type>
      <name>getModel</name>
      <anchorfile>classRythmos_1_1TimeStepNonlinearSolver.html</anchorfile>
      <anchor>a157c557c49da2d546aff6a3f7f6f178d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Thyra::SolveStatus&lt; Scalar &gt;</type>
      <name>solve</name>
      <anchorfile>classRythmos_1_1TimeStepNonlinearSolver.html</anchorfile>
      <anchor>a5a112966177282d846ef32006b3c2112</anchor>
      <arglist>(Thyra::VectorBase&lt; Scalar &gt; *x, const Thyra::SolveCriteria&lt; Scalar &gt; *solveCriteria, Thyra::VectorBase&lt; Scalar &gt; *delta=NULL)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>supportsCloning</name>
      <anchorfile>classRythmos_1_1TimeStepNonlinearSolver.html</anchorfile>
      <anchor>a081c5f90e3c4e976b5118e0afa9d1040</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; Thyra::NonlinearSolverBase&lt; Scalar &gt; &gt;</type>
      <name>cloneNonlinearSolver</name>
      <anchorfile>classRythmos_1_1TimeStepNonlinearSolver.html</anchorfile>
      <anchor>a627de2999c4596f32edfc27d7059e806</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const Thyra::VectorBase&lt; Scalar &gt; &gt;</type>
      <name>get_current_x</name>
      <anchorfile>classRythmos_1_1TimeStepNonlinearSolver.html</anchorfile>
      <anchor>a47b96cf7bf5d8ee74dfac052af7a029b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>is_W_current</name>
      <anchorfile>classRythmos_1_1TimeStepNonlinearSolver.html</anchorfile>
      <anchor>ab94c4c6dc3a79a79b61bf851b878cbf7</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; Thyra::LinearOpWithSolveBase&lt; Scalar &gt; &gt;</type>
      <name>get_nonconst_W</name>
      <anchorfile>classRythmos_1_1TimeStepNonlinearSolver.html</anchorfile>
      <anchor>aa1bdf585849c33e7a3b80796ed0928e9</anchor>
      <arglist>(const bool forceUpToDate)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const Thyra::LinearOpWithSolveBase&lt; Scalar &gt; &gt;</type>
      <name>get_W</name>
      <anchorfile>classRythmos_1_1TimeStepNonlinearSolver.html</anchorfile>
      <anchor>a03fa6fb5a05a0f5c003e1fc439c505d4</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_W_is_current</name>
      <anchorfile>classRythmos_1_1TimeStepNonlinearSolver.html</anchorfile>
      <anchor>a6cc89f5e73477297f242c6fa890172a5</anchor>
      <arglist>(bool W_is_current)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Rythmos::TrailingInterpolationBufferAcceptingIntegratorBase</name>
    <filename>classRythmos_1_1TrailingInterpolationBufferAcceptingIntegratorBase.html</filename>
    <templarg></templarg>
    <base virtualness="virtual">Rythmos::IntegratorBase</base>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>setTrailingInterpolationBuffer</name>
      <anchorfile>classRythmos_1_1TrailingInterpolationBufferAcceptingIntegratorBase.html</anchorfile>
      <anchor>a4dacb2d33931babb24cc5ffc05ba52b0</anchor>
      <arglist>(const RCP&lt; InterpolationBufferBase&lt; Scalar &gt; &gt; &amp;trailingInterpBuffer)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual RCP&lt; InterpolationBufferBase&lt; Scalar &gt; &gt;</type>
      <name>getNonconstTrailingInterpolationBuffer</name>
      <anchorfile>classRythmos_1_1TrailingInterpolationBufferAcceptingIntegratorBase.html</anchorfile>
      <anchor>a3a0aad6420623e1946a35446bd8ae7c8</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual RCP&lt; const InterpolationBufferBase&lt; Scalar &gt; &gt;</type>
      <name>getTrailingInterpolationBuffer</name>
      <anchorfile>classRythmos_1_1TrailingInterpolationBufferAcceptingIntegratorBase.html</anchorfile>
      <anchor>a37881fdc3aaf29ea882d70508f4deac2</anchor>
      <arglist>() const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual RCP&lt; InterpolationBufferBase&lt; Scalar &gt; &gt;</type>
      <name>unSetTrailingInterpolationBuffer</name>
      <anchorfile>classRythmos_1_1TrailingInterpolationBufferAcceptingIntegratorBase.html</anchorfile>
      <anchor>a125c05441685100379222900822c0b99</anchor>
      <arglist>()=0</arglist>
    </member>
  </compound>
  <compound kind="page">
    <name>index</name>
    <title>Rythmos : Transient Integration of Differential Equations</title>
    <filename>index</filename>
    <docanchor file="index" title="Time integration software">rythmos_software</docanchor>
    <docanchor file="index" title="Rythmos Examples">rythmos_examples_sec</docanchor>
    <docanchor file="index" title="Other Trilinos packages that Rythmos depends on">rythmos_dependencies_sec</docanchor>
    <docanchor file="index" title="Configuration of Rythmos">rythmos_configuration_sec</docanchor>
    <docanchor file="index" title="Contributors to the Rythmos Package">rythmos_contributors_sec</docanchor>
  </compound>
</tagfile>
