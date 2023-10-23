<?xml version='1.0' encoding='UTF-8' standalone='yes' ?>
<tagfile>
  <compound kind="class">
    <name>OptiPack::DefaultPolyLineSearchPointEvaluator</name>
    <filename>classOptiPack_1_1DefaultPolyLineSearchPointEvaluator.html</filename>
    <templarg></templarg>
    <base>OptiPack::LineSearchPointEvaluatorBase</base>
    <member kind="typedef">
      <type>ScalarTraits&lt; Scalar &gt;::magnitudeType</type>
      <name>ScalarMag</name>
      <anchorfile>classOptiPack_1_1DefaultPolyLineSearchPointEvaluator.html</anchorfile>
      <anchor>a598108cd8db7908ce5d4beff53070377</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>const RCP&lt; DefaultPolyLineSearchPointEvaluator&lt; Scalar &gt; &gt;</type>
      <name>defaultPolyLineSearchPointEvaluator</name>
      <anchorfile>classOptiPack_1_1DefaultPolyLineSearchPointEvaluator.html</anchorfile>
      <anchor>a2f9efb3521cbed3c6b0b219fb8fc0b4a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>DefaultPolyLineSearchPointEvaluator</name>
      <anchorfile>classOptiPack_1_1DefaultPolyLineSearchPointEvaluator.html</anchorfile>
      <anchor>a9fb781c16d98fd2f85f473f0a03ece01</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initialize</name>
      <anchorfile>classOptiPack_1_1DefaultPolyLineSearchPointEvaluator.html</anchorfile>
      <anchor>a5ea6585925189d15b0782b1f422c8951</anchor>
      <arglist>(const ArrayView&lt; const RCP&lt; const Thyra::VectorBase&lt; Scalar &gt; &gt; &gt; &amp;vecs)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>computePoint</name>
      <anchorfile>classOptiPack_1_1DefaultPolyLineSearchPointEvaluator.html</anchorfile>
      <anchor>ae76676eba1928527beb61d7a1e576b15</anchor>
      <arglist>(const ScalarMag &amp;alpha, const Ptr&lt; Thyra::VectorBase&lt; Scalar &gt; &gt; &amp;p) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>OptiPack::LineSearchPointEvaluatorBase</name>
    <filename>classOptiPack_1_1LineSearchPointEvaluatorBase.html</filename>
    <templarg></templarg>
    <member kind="typedef">
      <type>ScalarTraits&lt; Scalar &gt;::magnitudeType</type>
      <name>ScalarMag</name>
      <anchorfile>classOptiPack_1_1LineSearchPointEvaluatorBase.html</anchorfile>
      <anchor>a42ef32d671c1d179cce08d6a48a4d675</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>computePoint</name>
      <anchorfile>classOptiPack_1_1LineSearchPointEvaluatorBase.html</anchorfile>
      <anchor>abb2eda8a21f467010e9839e70b494673</anchor>
      <arglist>(const ScalarMag &amp;alpha, const Ptr&lt; Thyra::VectorBase&lt; Scalar &gt; &gt; &amp;p) const  =0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::ModelEvaluator</name>
    <filename>classThyra_1_1ModelEvaluator.html</filename>
    <templarg></templarg>
  </compound>
  <compound kind="class">
    <name>OptiPack::NonlinearCG</name>
    <filename>classOptiPack_1_1NonlinearCG.html</filename>
    <templarg>Scalar</templarg>
    <member kind="typedef">
      <type>ScalarTraits&lt; Scalar &gt;::magnitudeType</type>
      <name>ScalarMag</name>
      <anchorfile>classOptiPack_1_1NonlinearCG.html</anchorfile>
      <anchor>a15182386d2cbe3bec9bfbbf538659efc</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>const RCP&lt; NonlinearCG&lt; Scalar &gt; &gt;</type>
      <name>nonlinearCG</name>
      <anchorfile>classOptiPack_1_1NonlinearCG.html</anchorfile>
      <anchor>a796e0a38c96ea25edf1a33d00dc5dcb1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const RCP&lt; NonlinearCG&lt; Scalar &gt; &gt;</type>
      <name>nonlinearCG</name>
      <anchorfile>classOptiPack_1_1NonlinearCG.html</anchorfile>
      <anchor>a72eb3b5443ac7cdd98931955fb6699c2</anchor>
      <arglist>(const RCP&lt; const Thyra::ModelEvaluator&lt; Scalar &gt; &gt; &amp;model, const int paramIndex, const int responseIndex, const RCP&lt; GlobiPack::LineSearchBase&lt; Scalar &gt; &gt; &amp;linesearch)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>NonlinearCG</name>
      <anchorfile>classOptiPack_1_1NonlinearCG.html</anchorfile>
      <anchor>ab2b9f0a70cb78631478879f082167845</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initialize</name>
      <anchorfile>classOptiPack_1_1NonlinearCG.html</anchorfile>
      <anchor>a6471cac3b36042bb0a0d667fd4be4287</anchor>
      <arglist>(const RCP&lt; const Thyra::ModelEvaluator&lt; Scalar &gt; &gt; &amp;model, const int paramIndex, const int responseIndex, const RCP&lt; GlobiPack::LineSearchBase&lt; Scalar &gt; &gt; &amp;linesearch)</arglist>
    </member>
    <member kind="function">
      <type>NonlinearCGUtils::ESolverTypes</type>
      <name>get_solverType</name>
      <anchorfile>classOptiPack_1_1NonlinearCG.html</anchorfile>
      <anchor>adb7bfeeb05417b95bb5e8f5bdd7f043c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>ScalarMag</type>
      <name>get_alpha_init</name>
      <anchorfile>classOptiPack_1_1NonlinearCG.html</anchorfile>
      <anchor>a5131d38255cccea39d555bfec62264c7</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>get_alpha_reinit</name>
      <anchorfile>classOptiPack_1_1NonlinearCG.html</anchorfile>
      <anchor>ad56361c5e4ba4ee9c8e5dcea3189eeb4</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>get_and_conv_tests</name>
      <anchorfile>classOptiPack_1_1NonlinearCG.html</anchorfile>
      <anchor>af00c9f9267d8dd508b099d7c0bd7a9df</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>get_minIters</name>
      <anchorfile>classOptiPack_1_1NonlinearCG.html</anchorfile>
      <anchor>a73aebae99d6652b6bf9bc258fcf12d66</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>get_maxIters</name>
      <anchorfile>classOptiPack_1_1NonlinearCG.html</anchorfile>
      <anchor>aa1b05f8b8740d3436ed727abd8ad380c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>ScalarMag</type>
      <name>get_g_reduct_tol</name>
      <anchorfile>classOptiPack_1_1NonlinearCG.html</anchorfile>
      <anchor>ab493e0c90e6bff771b50652a97edf3e7</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>ScalarMag</type>
      <name>get_g_grad_tol</name>
      <anchorfile>classOptiPack_1_1NonlinearCG.html</anchorfile>
      <anchor>a1b70d3b8588ed08f1e7cc347a5a53752</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>ScalarMag</type>
      <name>get_g_mag</name>
      <anchorfile>classOptiPack_1_1NonlinearCG.html</anchorfile>
      <anchor>a9b1c3ea86f202e7f8b319ebc4b725416</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setParameterList</name>
      <anchorfile>classOptiPack_1_1NonlinearCG.html</anchorfile>
      <anchor>a747bf829c2df006bf3fa1743b7f4907c</anchor>
      <arglist>(RCP&lt; ParameterList &gt; const &amp;paramList)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const ParameterList &gt;</type>
      <name>getValidParameters</name>
      <anchorfile>classOptiPack_1_1NonlinearCG.html</anchorfile>
      <anchor>a9f447f5e1193c2cc1880da098aa335e1</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>NonlinearCGUtils::ESolveReturn</type>
      <name>doSolve</name>
      <anchorfile>classOptiPack_1_1NonlinearCG.html</anchorfile>
      <anchor>a65c62f9aab531d28fe6b1730f1be94cd</anchor>
      <arglist>(const Ptr&lt; Thyra::VectorBase&lt; Scalar &gt; &gt; &amp;p, const Ptr&lt; ScalarMag &gt; &amp;g_opt, const Ptr&lt; const ScalarMag &gt; &amp;g_reduct_tol=Teuchos::null, const Ptr&lt; const ScalarMag &gt; &amp;g_grad_tol=Teuchos::null, const Ptr&lt; const ScalarMag &gt; &amp;alpha_init=Teuchos::null, const Ptr&lt; int &gt; &amp;numIters=Teuchos::null)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>OptiPack::UnconstrainedOptMeritFunc1D</name>
    <filename>classOptiPack_1_1UnconstrainedOptMeritFunc1D.html</filename>
    <templarg></templarg>
    <base>MeritFunc1DBase&lt; ScalarTraits&lt; Scalar &gt;::magnitudeType &gt;</base>
    <member kind="typedef">
      <type>ScalarTraits&lt; Scalar &gt;::magnitudeType</type>
      <name>ScalarMag</name>
      <anchorfile>classOptiPack_1_1UnconstrainedOptMeritFunc1D.html</anchorfile>
      <anchor>a704b4b3caac2620b7e1c800b48947720</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>const RCP&lt; UnconstrainedOptMeritFunc1D&lt; Scalar &gt; &gt;</type>
      <name>unconstrainedOptMeritFunc1D</name>
      <anchorfile>classOptiPack_1_1UnconstrainedOptMeritFunc1D.html</anchorfile>
      <anchor>a917389d693b51f0529b8840b8cc5bf0f</anchor>
      <arglist>(const RCP&lt; const Thyra::ModelEvaluator&lt; Scalar &gt; &gt; &amp;model, const int paramIndex, const int responseIndex)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>UnconstrainedOptMeritFunc1D</name>
      <anchorfile>classOptiPack_1_1UnconstrainedOptMeritFunc1D.html</anchorfile>
      <anchor>aac5aa9fc29c1bc731b0fb2078d886009</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setModel</name>
      <anchorfile>classOptiPack_1_1UnconstrainedOptMeritFunc1D.html</anchorfile>
      <anchor>acfec9a5fb873dea6aa9a5412094d2b1a</anchor>
      <arglist>(const RCP&lt; const Thyra::ModelEvaluator&lt; Scalar &gt; &gt; &amp;model, const int paramIndex, const int responseIndex)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setEvaluationQuantities</name>
      <anchorfile>classOptiPack_1_1UnconstrainedOptMeritFunc1D.html</anchorfile>
      <anchor>a6a6385d244768a7b482ad5f295ef16b6</anchor>
      <arglist>(const RCP&lt; const LineSearchPointEvaluatorBase&lt; Scalar &gt; &gt; &amp;pointEvaluator, const RCP&lt; Thyra::VectorBase&lt; Scalar &gt; &gt; &amp;p, const RCP&lt; Thyra::VectorBase&lt; Scalar &gt; &gt; &amp;g_vec, const RCP&lt; Thyra::VectorBase&lt; Scalar &gt; &gt; &amp;g_grad_vec)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>supportsDerivEvals</name>
      <anchorfile>classOptiPack_1_1UnconstrainedOptMeritFunc1D.html</anchorfile>
      <anchor>a893bc53ea952a9910bd541de4ab10f4e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>eval</name>
      <anchorfile>classOptiPack_1_1UnconstrainedOptMeritFunc1D.html</anchorfile>
      <anchor>a332cd4ce7b48bd9a4b992fd441be7f16</anchor>
      <arglist>(const ScalarMag &amp;alpha, const Ptr&lt; ScalarMag &gt; &amp;phi, const Ptr&lt; ScalarMag &gt; &amp;Dphi) const </arglist>
    </member>
  </compound>
  <compound kind="page">
    <name>index</name>
    <title>OptiPack: Collection of simple Thyra-based Optimization ANAs</title>
    <filename>index</filename>
    <docanchor file="index" title="OptiPack browser">optipack_browser_sec</docanchor>
    <docanchor file="index" title="GlobiPack browser">globipack_browser_sec</docanchor>
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
