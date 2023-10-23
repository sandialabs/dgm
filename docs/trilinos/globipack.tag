<?xml version='1.0' encoding='UTF-8' standalone='yes' ?>
<tagfile>
  <compound kind="class">
    <name>GlobiPack::ArmijoPolyInterpLineSearch</name>
    <filename>classGlobiPack_1_1ArmijoPolyInterpLineSearch.html</filename>
    <templarg></templarg>
    <base>GlobiPack::LineSearchBase</base>
    <member kind="function">
      <type>const RCP&lt; ArmijoPolyInterpLineSearch&lt; Scalar &gt; &gt;</type>
      <name>armijoQuadraticLineSearch</name>
      <anchorfile>classGlobiPack_1_1ArmijoPolyInterpLineSearch.html</anchorfile>
      <anchor>a4f4c62406ff9127fa826384fb316e340</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ArmijoPolyInterpLineSearch</name>
      <anchorfile>classGlobiPack_1_1ArmijoPolyInterpLineSearch.html</anchorfile>
      <anchor>ad14547822891b5c7949a292785f05656</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Scalar</type>
      <name>eta</name>
      <anchorfile>classGlobiPack_1_1ArmijoPolyInterpLineSearch.html</anchorfile>
      <anchor>a6f04b9d32809710e7a530bdd53f51bc8</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Scalar</type>
      <name>minFrac</name>
      <anchorfile>classGlobiPack_1_1ArmijoPolyInterpLineSearch.html</anchorfile>
      <anchor>a44acce27facb8cee7a31e3dbffff8461</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Scalar</type>
      <name>maxFrac</name>
      <anchorfile>classGlobiPack_1_1ArmijoPolyInterpLineSearch.html</anchorfile>
      <anchor>ad448b434aacaaf982ab5620271d23f3d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>minIters</name>
      <anchorfile>classGlobiPack_1_1ArmijoPolyInterpLineSearch.html</anchorfile>
      <anchor>a86dd5917fc95155692730e8790b96d12</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>maxIters</name>
      <anchorfile>classGlobiPack_1_1ArmijoPolyInterpLineSearch.html</anchorfile>
      <anchor>a668e6521e672888121f966ba116553b2</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>doMaxIters</name>
      <anchorfile>classGlobiPack_1_1ArmijoPolyInterpLineSearch.html</anchorfile>
      <anchor>af52465de9cbcc9fe2cebb26463500090</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setParameterList</name>
      <anchorfile>classGlobiPack_1_1ArmijoPolyInterpLineSearch.html</anchorfile>
      <anchor>a6d6b1207873466fb23be33a9c9ee4f8f</anchor>
      <arglist>(RCP&lt; ParameterList &gt; const &amp;paramList)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const ParameterList &gt;</type>
      <name>getValidParameters</name>
      <anchorfile>classGlobiPack_1_1ArmijoPolyInterpLineSearch.html</anchorfile>
      <anchor>a4176175a298de9bcfdfa08a5833bb855</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>requiresBaseDeriv</name>
      <anchorfile>classGlobiPack_1_1ArmijoPolyInterpLineSearch.html</anchorfile>
      <anchor>a308f8320aa23b5c4ac618dfca0714a92</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>requiresDerivEvals</name>
      <anchorfile>classGlobiPack_1_1ArmijoPolyInterpLineSearch.html</anchorfile>
      <anchor>a8c1e5d2706fdbf265083f07e1b44a26e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>doLineSearch</name>
      <anchorfile>classGlobiPack_1_1ArmijoPolyInterpLineSearch.html</anchorfile>
      <anchor>abe9115d3188f709d51760c950c88173e</anchor>
      <arglist>(const MeritFunc1DBase&lt; Scalar &gt; &amp;phi, const PointEval1D&lt; Scalar &gt; &amp;point_k, const Ptr&lt; PointEval1D&lt; Scalar &gt; &gt; &amp;point_kp1, const Ptr&lt; int &gt; &amp;numIters) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>GlobiPack::Brents1DMinimization</name>
    <filename>classGlobiPack_1_1Brents1DMinimization.html</filename>
    <templarg>Scalar</templarg>
    <member kind="function">
      <type>const RCP&lt; Brents1DMinimization&lt; Scalar &gt; &gt;</type>
      <name>brents1DMinimization</name>
      <anchorfile>classGlobiPack_1_1Brents1DMinimization.html</anchorfile>
      <anchor>af034d214f06d45015347324994d834b7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Brents1DMinimization</name>
      <anchorfile>classGlobiPack_1_1Brents1DMinimization.html</anchorfile>
      <anchor>aa2df9fc7fdf254328a4604a267e0cb63</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setParameterList</name>
      <anchorfile>classGlobiPack_1_1Brents1DMinimization.html</anchorfile>
      <anchor>acd0ec9a8e598f864cd56e7510e35bbda</anchor>
      <arglist>(RCP&lt; ParameterList &gt; const &amp;paramList)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const ParameterList &gt;</type>
      <name>getValidParameters</name>
      <anchorfile>classGlobiPack_1_1Brents1DMinimization.html</anchorfile>
      <anchor>acbf82424ff5b9d00c8ee0ab790e78280</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>approxMinimize</name>
      <anchorfile>classGlobiPack_1_1Brents1DMinimization.html</anchorfile>
      <anchor>a4054f1bd003550ef950d08ea0f423560</anchor>
      <arglist>(const MeritFunc1DBase&lt; Scalar &gt; &amp;phi, const PointEval1D&lt; Scalar &gt; &amp;pointLower, const Ptr&lt; PointEval1D&lt; Scalar &gt; &gt; &amp;pointMiddle, const PointEval1D&lt; Scalar &gt; &amp;pointUpper, const Ptr&lt; int &gt; &amp;numIters=Teuchos::null) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>GlobiPack::BrentsLineSearch</name>
    <filename>classGlobiPack_1_1BrentsLineSearch.html</filename>
    <templarg></templarg>
    <base>GlobiPack::LineSearchBase</base>
    <member kind="function">
      <type>const RCP&lt; BrentsLineSearch&lt; Scalar &gt; &gt;</type>
      <name>brentsLineSearch</name>
      <anchorfile>classGlobiPack_1_1BrentsLineSearch.html</anchorfile>
      <anchor>af6e5a2676f45a44c8bde3817d35ea57c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BrentsLineSearch</name>
      <anchorfile>classGlobiPack_1_1BrentsLineSearch.html</anchorfile>
      <anchor>aae62cd6181c76d3f1b963d3201079bfd</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const GoldenQuadInterpBracket&lt; Scalar &gt; &amp;</type>
      <name>bracket</name>
      <anchorfile>classGlobiPack_1_1BrentsLineSearch.html</anchorfile>
      <anchor>a894e71a25a190543a8f2cc9a40d8609d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Brents1DMinimization&lt; Scalar &gt; &amp;</type>
      <name>brentsMin</name>
      <anchorfile>classGlobiPack_1_1BrentsLineSearch.html</anchorfile>
      <anchor>a796a44ef2d18d1f4ff51415fe22103d1</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setParameterList</name>
      <anchorfile>classGlobiPack_1_1BrentsLineSearch.html</anchorfile>
      <anchor>ac9cbfb395d6f2a51e83f02f336286864</anchor>
      <arglist>(RCP&lt; ParameterList &gt; const &amp;paramList)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const ParameterList &gt;</type>
      <name>getValidParameters</name>
      <anchorfile>classGlobiPack_1_1BrentsLineSearch.html</anchorfile>
      <anchor>af0ed0095065fe2aa25417c9aa9112dee</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>requiresBaseDeriv</name>
      <anchorfile>classGlobiPack_1_1BrentsLineSearch.html</anchorfile>
      <anchor>aa1c2433939cab295ea0b7370207cd4d0</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>requiresDerivEvals</name>
      <anchorfile>classGlobiPack_1_1BrentsLineSearch.html</anchorfile>
      <anchor>abb56440159bdcd5b24b5591504ad530c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>doLineSearch</name>
      <anchorfile>classGlobiPack_1_1BrentsLineSearch.html</anchorfile>
      <anchor>ad944ee32441f4b55ebc19c7aed3bfb34</anchor>
      <arglist>(const MeritFunc1DBase&lt; Scalar &gt; &amp;phi, const PointEval1D&lt; Scalar &gt; &amp;point_k, const Ptr&lt; PointEval1D&lt; Scalar &gt; &gt; &amp;point_kp1, const Ptr&lt; int &gt; &amp;numIters) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>GlobiPack::GoldenQuadInterpBracket</name>
    <filename>classGlobiPack_1_1GoldenQuadInterpBracket.html</filename>
    <templarg>Scalar</templarg>
    <member kind="function">
      <type>const RCP&lt; GoldenQuadInterpBracket&lt; Scalar &gt; &gt;</type>
      <name>goldenQuadInterpBracket</name>
      <anchorfile>classGlobiPack_1_1GoldenQuadInterpBracket.html</anchorfile>
      <anchor>a807d6811634fa5e1a4867dc1ae454d82</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>GoldenQuadInterpBracket</name>
      <anchorfile>classGlobiPack_1_1GoldenQuadInterpBracket.html</anchorfile>
      <anchor>a348c61fbc2741a1ff8b7f67e446a818c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setParameterList</name>
      <anchorfile>classGlobiPack_1_1GoldenQuadInterpBracket.html</anchorfile>
      <anchor>a3ce3c30117a023fde50f4acfcdd8e00a</anchor>
      <arglist>(RCP&lt; ParameterList &gt; const &amp;paramList)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const ParameterList &gt;</type>
      <name>getValidParameters</name>
      <anchorfile>classGlobiPack_1_1GoldenQuadInterpBracket.html</anchorfile>
      <anchor>aab0ce35a02202387a9fb7e7ec491c19d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>bracketMinimum</name>
      <anchorfile>classGlobiPack_1_1GoldenQuadInterpBracket.html</anchorfile>
      <anchor>a5c44a45b8e442de8a66b4e1ccbfa4dbc</anchor>
      <arglist>(const MeritFunc1DBase&lt; Scalar &gt; &amp;phi, const Ptr&lt; PointEval1D&lt; Scalar &gt; &gt; &amp;pointLower, const Ptr&lt; PointEval1D&lt; Scalar &gt; &gt; &amp;pointMiddle, const Ptr&lt; PointEval1D&lt; Scalar &gt; &gt; &amp;pointUpper, const Ptr&lt; int &gt; &amp;numIters=Teuchos::null) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>GlobiPack::LineSearchBase</name>
    <filename>classGlobiPack_1_1LineSearchBase.html</filename>
    <templarg></templarg>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>requiresBaseDeriv</name>
      <anchorfile>classGlobiPack_1_1LineSearchBase.html</anchorfile>
      <anchor>a63a10e596cc873e79097c916098e48f7</anchor>
      <arglist>() const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>requiresDerivEvals</name>
      <anchorfile>classGlobiPack_1_1LineSearchBase.html</anchorfile>
      <anchor>a43d7bd167bc61acc60ced488d728d349</anchor>
      <arglist>() const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>doLineSearch</name>
      <anchorfile>classGlobiPack_1_1LineSearchBase.html</anchorfile>
      <anchor>a84cedbae29a9eddb8be0b75c48489b96</anchor>
      <arglist>(const MeritFunc1DBase&lt; Scalar &gt; &amp;phi, const PointEval1D&lt; Scalar &gt; &amp;point_k, const Ptr&lt; PointEval1D&lt; Scalar &gt; &gt; &amp;point_kp1, const Ptr&lt; int &gt; &amp;numIters) const  =0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>GlobiPack::MeritFunc1DBase</name>
    <filename>classGlobiPack_1_1MeritFunc1DBase.html</filename>
    <templarg>Scalar</templarg>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>supportsDerivEvals</name>
      <anchorfile>classGlobiPack_1_1MeritFunc1DBase.html</anchorfile>
      <anchor>ab7a44ec8ec269091b3716b751cad7074</anchor>
      <arglist>() const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>eval</name>
      <anchorfile>classGlobiPack_1_1MeritFunc1DBase.html</anchorfile>
      <anchor>a191439841f4f59209b1d39012f732f36</anchor>
      <arglist>(const Scalar &amp;alpha, const Ptr&lt; Scalar &gt; &amp;phi, const Ptr&lt; Scalar &gt; &amp;Dphi) const  =0</arglist>
    </member>
    <member kind="function">
      <type>ScalarTraits&lt; Scalar &gt;::magnitudeType</type>
      <name>computeValue</name>
      <anchorfile>classGlobiPack_1_1MeritFunc1DBase.html</anchorfile>
      <anchor>ad0597c3fcad9dd236392042a9a226938</anchor>
      <arglist>(const MeritFunc1DBase&lt; Scalar &gt; &amp;phi, const Scalar &amp;alpha)</arglist>
    </member>
    <member kind="function">
      <type>PointEval1D&lt; Scalar &gt;</type>
      <name>computePoint</name>
      <anchorfile>classGlobiPack_1_1MeritFunc1DBase.html</anchorfile>
      <anchor>ac2d0e947e0c4763f54ea7878cc25f237</anchor>
      <arglist>(const MeritFunc1DBase&lt; Scalar &gt; &amp;phi, const Scalar &amp;alpha, const bool compute_phi=true, const bool compute_Dphi=false)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>GlobiPack::Exceptions::NotDescentDirection</name>
    <filename>classGlobiPack_1_1Exceptions_1_1NotDescentDirection.html</filename>
  </compound>
  <compound kind="struct">
    <name>GlobiPack::PointEval1D</name>
    <filename>structGlobiPack_1_1PointEval1D.html</filename>
    <templarg>Scalar</templarg>
    <member kind="function">
      <type></type>
      <name>PointEval1D</name>
      <anchorfile>structGlobiPack_1_1PointEval1D.html</anchorfile>
      <anchor>a84d2a4f1fce7d9e5385ed20129744853</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>PointEval1D</name>
      <anchorfile>structGlobiPack_1_1PointEval1D.html</anchorfile>
      <anchor>adcd37f42f3bd004ce4aa5c1fe922e799</anchor>
      <arglist>(const Scalar &amp;alpha_in, const Scalar &amp;phi_in, const Scalar &amp;Dphi_in=valNotGiven())</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static Scalar</type>
      <name>valNotGiven</name>
      <anchorfile>structGlobiPack_1_1PointEval1D.html</anchorfile>
      <anchor>a98daff902a437196839c4daa1db6d8c7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable">
      <type>Scalar</type>
      <name>alpha</name>
      <anchorfile>structGlobiPack_1_1PointEval1D.html</anchorfile>
      <anchor>a429c9f9d2e0dbab40b714225fa9a2178</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>Scalar</type>
      <name>phi</name>
      <anchorfile>structGlobiPack_1_1PointEval1D.html</anchorfile>
      <anchor>ace87d2ddf273bceec2a33a0820aada43</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>Scalar</type>
      <name>Dphi</name>
      <anchorfile>structGlobiPack_1_1PointEval1D.html</anchorfile>
      <anchor>a59771155f5e0c5268b292bfa4a4dbec8</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="page">
    <name>index</name>
    <title>GlobiPack: Collection of Scalar 1D globalizaton utilities</title>
    <filename>index</filename>
    <docanchor file="index" title="GlobiPack browser">globipack_browser_sec</docanchor>
  </compound>
</tagfile>
