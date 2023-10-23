<?xml version='1.0' encoding='UTF-8' standalone='yes' ?>
<tagfile>
  <compound kind="file">
    <name>Ifpack2_ScalingType.hpp</name>
    <path>/Users/sscoll/Downloads/trilinos-11.0.3-Source/packages/ifpack2/src/</path>
    <filename>Ifpack2__ScalingType_8hpp</filename>
    <namespace>Ifpack2</namespace>
    <member kind="enumeration">
      <name>ScalingType</name>
      <anchorfile>namespaceIfpack2.html</anchorfile>
      <anchor>afef39739e18c7b7537c9428f2c60f719</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="namespace">
    <name>Ifpack2</name>
    <filename>namespaceIfpack2.html</filename>
    <class kind="class">Ifpack2::BlockRelaxation</class>
    <class kind="class">Ifpack2::BorderedOperator</class>
    <class kind="class">Ifpack2::Chebyshev</class>
    <class kind="class">Ifpack2::Diagonal</class>
    <class kind="class">Ifpack2::DiagonalFilter</class>
    <class kind="class">Ifpack2::DropFilter</class>
    <class kind="class">Ifpack2::Factory</class>
    <class kind="class">Ifpack2::IlukGraph</class>
    <class kind="class">Ifpack2::ILUT</class>
    <class kind="class">Ifpack2::LinearPartitioner</class>
    <class kind="class">Ifpack2::LocalFilter</class>
    <class kind="class">Ifpack2::OverlapGraph</class>
    <class kind="class">Ifpack2::Partitioner</class>
    <class kind="class">Ifpack2::Preconditioner</class>
    <class kind="class">Ifpack2::Relaxation</class>
    <class kind="class">Ifpack2::RILUK</class>
    <class kind="class">Ifpack2::SingletonFilter</class>
    <class kind="class">Ifpack2::SparsityFilter</class>
    <member kind="enumeration">
      <name>CondestType</name>
      <anchorfile>namespaceIfpack2.html</anchorfile>
      <anchor>a9ee8b3289963ca9a2d38d0310d7e8709</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>Cheap</name>
      <anchorfile>namespaceIfpack2.html</anchorfile>
      <anchor>a9ee8b3289963ca9a2d38d0310d7e8709a5bd2ee5d42497350ae960bd11f5e8e80</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CG</name>
      <anchorfile>namespaceIfpack2.html</anchorfile>
      <anchor>a9ee8b3289963ca9a2d38d0310d7e8709a1880dbdff3c9b492295449b1a2bdb7f2</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>GMRES</name>
      <anchorfile>namespaceIfpack2.html</anchorfile>
      <anchor>a9ee8b3289963ca9a2d38d0310d7e8709aa2b8987e4eda37cbcb2392b195da884b</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>ScalingType</name>
      <anchorfile>namespaceIfpack2.html</anchorfile>
      <anchor>afef39739e18c7b7537c9428f2c60f719</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>ConstructLevelFillGraph</name>
      <anchorfile>namespaceIfpack2.html</anchorfile>
      <anchor>a7bc14a627463441534acbb16d2f7afc6</anchor>
      <arglist>(const RowGraph&lt; LocalOrdinal, GlobalOrdinal &gt; &amp;userGraph, Teuchos::RCP&lt; CrsGraph&lt; LocalOrdinal, GlobalOrdinal &gt;&gt; graphL, Teuchos::RCP&lt; CrsGraph&lt; LocalOrdinal, GlobalOrdinal &gt;&gt; graphU)</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Tpetra::CrsGraph&lt; LocalOrdinal, GlobalOrdinal, Node &gt; &gt;</type>
      <name>CreateOverlapGraph</name>
      <anchorfile>namespaceIfpack2.html</anchorfile>
      <anchor>a1b067a1ec84e81ab5feb3bebbcdb2729</anchor>
      <arglist>(const Teuchos::RCP&lt; const Tpetra::CrsGraph&lt; LocalOrdinal, GlobalOrdinal, Node &gt; &gt; &amp;input_graph, int OverlapLevel)</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; Ifpack2::Diagonal&lt; MatrixType &gt; &gt;</type>
      <name>createDiagonalPreconditioner</name>
      <anchorfile>namespaceIfpack2.html</anchorfile>
      <anchor>ad77717c8e142617ca1dd4e9e9927d521</anchor>
      <arglist>(const Teuchos::RCP&lt; const VectorType &gt; &amp;invdiag)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>supportsUnsymmetric</name>
      <anchorfile>namespaceIfpack2.html</anchorfile>
      <anchor>abc9d9b4283f877a6d9a75116b88f7427</anchor>
      <arglist>(const std::string &amp;prec_type)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>add_to_heap</name>
      <anchorfile>namespaceIfpack2.html</anchorfile>
      <anchor>a0b3b7f1cf778af57a9165f2ec0d8d975</anchor>
      <arglist>(const Ordinal &amp;idx, Teuchos::Array&lt; Ordinal &gt; &amp;heap, SizeType &amp;heap_len)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>add_to_heap</name>
      <anchorfile>namespaceIfpack2.html</anchorfile>
      <anchor>a4db69343d5c9e6b2d4c8dfe4a1c6966f</anchor>
      <arglist>(const Ordinal &amp;idx, Teuchos::Array&lt; Ordinal &gt; &amp;heap, SizeType &amp;heap_len, Compare comp)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>rm_heap_root</name>
      <anchorfile>namespaceIfpack2.html</anchorfile>
      <anchor>a412ea41f8c9cb0dd1458e3991ad75059</anchor>
      <arglist>(Teuchos::Array&lt; Ordinal &gt; &amp;heap, SizeType &amp;heap_len)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>rm_heap_root</name>
      <anchorfile>namespaceIfpack2.html</anchorfile>
      <anchor>aadb1d35fc7e203bd1087164c90a9687e</anchor>
      <arglist>(Teuchos::Array&lt; Ordinal &gt; &amp;heap, SizeType &amp;heap_len, Compare comp)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>getValidParameters</name>
      <anchorfile>namespaceIfpack2.html</anchorfile>
      <anchor>a276389350db268dae6ca585d9ad992ad</anchor>
      <arglist>(Teuchos::ParameterList &amp;params)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>getParameter</name>
      <anchorfile>namespaceIfpack2.html</anchorfile>
      <anchor>a86d6da4094c130d7a867d70758cfdb2e</anchor>
      <arglist>(const Teuchos::ParameterList &amp;params, const std::string &amp;name, T &amp;value)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Ifpack2::BlockRelaxation</name>
    <filename>classIfpack2_1_1BlockRelaxation.html</filename>
    <templarg>MatrixType</templarg>
    <templarg>ContainerType</templarg>
    <base virtualness="virtual">Preconditioner&lt; MatrixType::scalar_type, MatrixType::local_ordinal_type, MatrixType::global_ordinal_type, MatrixType::node_type &gt;</base>
    <member kind="function">
      <type></type>
      <name>BlockRelaxation</name>
      <anchorfile>classIfpack2_1_1BlockRelaxation.html</anchorfile>
      <anchor>a7abde222e0464223db15b67285797bdb</anchor>
      <arglist>(const Teuchos::RCP&lt; const Tpetra::RowMatrix&lt; Scalar, LocalOrdinal, GlobalOrdinal, Node &gt; &gt; &amp;Matrix)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~BlockRelaxation</name>
      <anchorfile>classIfpack2_1_1BlockRelaxation.html</anchorfile>
      <anchor>a5bda6ca61381dbbd342cc1cc7f982681</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setParameters</name>
      <anchorfile>classIfpack2_1_1BlockRelaxation.html</anchorfile>
      <anchor>acd7474302b7704d23c36a9dce7fa1df6</anchor>
      <arglist>(const Teuchos::ParameterList &amp;params)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initialize</name>
      <anchorfile>classIfpack2_1_1BlockRelaxation.html</anchorfile>
      <anchor>a8fd5ea471f5479cc112eabe964125237</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isInitialized</name>
      <anchorfile>classIfpack2_1_1BlockRelaxation.html</anchorfile>
      <anchor>aa7b86e280c6e4d27ab2cc064e5f04b2e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>compute</name>
      <anchorfile>classIfpack2_1_1BlockRelaxation.html</anchorfile>
      <anchor>a336120266faa8b02287e9894977b9e93</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isComputed</name>
      <anchorfile>classIfpack2_1_1BlockRelaxation.html</anchorfile>
      <anchor>a01c9083dd04dbef7e66d2e901f57f14e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>apply</name>
      <anchorfile>classIfpack2_1_1BlockRelaxation.html</anchorfile>
      <anchor>a0056df47519737b4c063fb4627ca1709</anchor>
      <arglist>(const Tpetra::MultiVector&lt; Scalar, LocalOrdinal, GlobalOrdinal, Node &gt; &amp;X, Tpetra::MultiVector&lt; Scalar, LocalOrdinal, GlobalOrdinal, Node &gt; &amp;Y, Teuchos::ETransp mode=Teuchos::NO_TRANS, Scalar alpha=Teuchos::ScalarTraits&lt; Scalar &gt;::one(), Scalar beta=Teuchos::ScalarTraits&lt; Scalar &gt;::zero()) const </arglist>
    </member>
    <member kind="function">
      <type>const Teuchos::RCP&lt; const Tpetra::Map&lt; LocalOrdinal, GlobalOrdinal, Node &gt; &gt; &amp;</type>
      <name>getDomainMap</name>
      <anchorfile>classIfpack2_1_1BlockRelaxation.html</anchorfile>
      <anchor>af443aa5ade945219cb7104bfd447186d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Teuchos::RCP&lt; const Tpetra::Map&lt; LocalOrdinal, GlobalOrdinal, Node &gt; &gt; &amp;</type>
      <name>getRangeMap</name>
      <anchorfile>classIfpack2_1_1BlockRelaxation.html</anchorfile>
      <anchor>a406a6f7947a3b5fca8bbb8fcd181a06b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>hasTransposeApply</name>
      <anchorfile>classIfpack2_1_1BlockRelaxation.html</anchorfile>
      <anchor>af5b82318355753f1d4f6489b5912c025</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>applyMat</name>
      <anchorfile>classIfpack2_1_1BlockRelaxation.html</anchorfile>
      <anchor>ad5ea583ef52163de820d2716963c4fa3</anchor>
      <arglist>(const Tpetra::MultiVector&lt; Scalar, LocalOrdinal, GlobalOrdinal, Node &gt; &amp;X, Tpetra::MultiVector&lt; Scalar, LocalOrdinal, GlobalOrdinal, Node &gt; &amp;Y, Teuchos::ETransp mode=Teuchos::NO_TRANS) const </arglist>
    </member>
    <member kind="function">
      <type>magnitudeType</type>
      <name>computeCondEst</name>
      <anchorfile>classIfpack2_1_1BlockRelaxation.html</anchorfile>
      <anchor>aed3f8109037cd126b62c1d442c6385a8</anchor>
      <arglist>(CondestType CT=Cheap, LocalOrdinal MaxIters=1550, magnitudeType Tol=1e-9, const Teuchos::Ptr&lt; const Tpetra::RowMatrix&lt; Scalar, LocalOrdinal, GlobalOrdinal, Node &gt; &gt; &amp;matrix=Teuchos::null)</arglist>
    </member>
    <member kind="function">
      <type>magnitudeType</type>
      <name>getCondEst</name>
      <anchorfile>classIfpack2_1_1BlockRelaxation.html</anchorfile>
      <anchor>a9889d3ebb6d4cb4872f46d48d9f20c1d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Teuchos::RCP&lt; const Teuchos::Comm&lt; int &gt; &gt; &amp;</type>
      <name>getComm</name>
      <anchorfile>classIfpack2_1_1BlockRelaxation.html</anchorfile>
      <anchor>a3342a9d679e540c0cb4f17dc70163e73</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Tpetra::RowMatrix&lt; Scalar, LocalOrdinal, GlobalOrdinal, Node &gt; &gt;</type>
      <name>getMatrix</name>
      <anchorfile>classIfpack2_1_1BlockRelaxation.html</anchorfile>
      <anchor>ac5572b5cd162b46063affd822993312a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>getComputeFlops</name>
      <anchorfile>classIfpack2_1_1BlockRelaxation.html</anchorfile>
      <anchor>ac41b1e2b1d756639af4c20ec3b52adcd</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>getApplyFlops</name>
      <anchorfile>classIfpack2_1_1BlockRelaxation.html</anchorfile>
      <anchor>a216b225466d58e95637f8ea6f605bfb0</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getNumInitialize</name>
      <anchorfile>classIfpack2_1_1BlockRelaxation.html</anchorfile>
      <anchor>aedb3471b2ddee9e040bca40832006444</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getNumCompute</name>
      <anchorfile>classIfpack2_1_1BlockRelaxation.html</anchorfile>
      <anchor>a8be4f3e487f8b0ed5968df2e635c007e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getNumApply</name>
      <anchorfile>classIfpack2_1_1BlockRelaxation.html</anchorfile>
      <anchor>a21e0f39245bfbd8af206532e25beff95</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>getInitializeTime</name>
      <anchorfile>classIfpack2_1_1BlockRelaxation.html</anchorfile>
      <anchor>a24b8692ee6b37622c4e889900f6e8db6</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>getComputeTime</name>
      <anchorfile>classIfpack2_1_1BlockRelaxation.html</anchorfile>
      <anchor>a7811a61a3c69ad021fdcc915f06ebde3</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>getApplyTime</name>
      <anchorfile>classIfpack2_1_1BlockRelaxation.html</anchorfile>
      <anchor>aa50228173863d4ede2dcd2c87f8ce2d7</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>description</name>
      <anchorfile>classIfpack2_1_1BlockRelaxation.html</anchorfile>
      <anchor>aa1d73312aa48aca2a83c43b78a564c3d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>describe</name>
      <anchorfile>classIfpack2_1_1BlockRelaxation.html</anchorfile>
      <anchor>ab0116dce6472684d65e708ac9a73012b</anchor>
      <arglist>(Teuchos::FancyOStream &amp;out, const Teuchos::EVerbosityLevel verbLevel=Teuchos::Describable::verbLevel_default) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~Preconditioner</name>
      <anchorfile>classIfpack2_1_1Preconditioner.html</anchorfile>
      <anchor>a637973211128e0c09db53772df0f345d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual magnitudeType</type>
      <name>computeCondEst</name>
      <anchorfile>classIfpack2_1_1Preconditioner.html</anchorfile>
      <anchor>ab5b0a817cf6be83123192d38b5172131</anchor>
      <arglist>(CondestType CT=Ifpack2::Cheap, MatrixType::local_ordinal_typeMaxIters=1550, magnitudeType Tol=1e-9, const Teuchos::Ptr&lt; const Tpetra::RowMatrix&lt; MatrixType::scalar_type, MatrixType::local_ordinal_type, MatrixType::global_ordinal_type, MatrixType::node_type &gt; &gt; &amp;Matrix=Teuchos::null)=0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Ifpack2::BorderedOperator</name>
    <filename>classIfpack2_1_1BorderedOperator.html</filename>
    <templarg></templarg>
    <templarg></templarg>
    <templarg></templarg>
    <templarg></templarg>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~BorderedOperator</name>
      <anchorfile>classIfpack2_1_1BorderedOperator.html</anchorfile>
      <anchor>a56201f4fb42bc83327a1f4790ee3507d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BorderedOperator</name>
      <anchorfile>classIfpack2_1_1BorderedOperator.html</anchorfile>
      <anchor>a45e970590e3f775ee9026277e9452b03</anchor>
      <arglist>(const Teuchos::RCP&lt; const Tpetra::Operator&lt; Scalar, LocalOrdinal, GlobalOrdinal, Node &gt; &gt; &amp;A)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const Teuchos::RCP&lt; const Tpetra::Map&lt; LocalOrdinal, GlobalOrdinal, Node &gt; &gt; &amp;</type>
      <name>getDomainMap</name>
      <anchorfile>classIfpack2_1_1BorderedOperator.html</anchorfile>
      <anchor>a7f70f8f65a85f7747323e35d64b8cf0f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const Teuchos::RCP&lt; const Tpetra::Map&lt; LocalOrdinal, GlobalOrdinal, Node &gt; &gt; &amp;</type>
      <name>getRangeMap</name>
      <anchorfile>classIfpack2_1_1BorderedOperator.html</anchorfile>
      <anchor>a4242c1f08758a9b8192ccdb832e68e33</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>hasTransposeApply</name>
      <anchorfile>classIfpack2_1_1BorderedOperator.html</anchorfile>
      <anchor>a7ced79dde6519a68ef070b92c79f1a3e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>apply</name>
      <anchorfile>classIfpack2_1_1BorderedOperator.html</anchorfile>
      <anchor>a56678c83845b31e3ca85f9d66d9b34a4</anchor>
      <arglist>(const Tpetra::MultiVector&lt; Scalar, LocalOrdinal, GlobalOrdinal, Node &gt; &amp;X, Tpetra::MultiVector&lt; Scalar, LocalOrdinal, GlobalOrdinal, Node &gt; &amp;Y, Teuchos::ETransp mode=Teuchos::NO_TRANS, Scalar alpha=Teuchos::ScalarTraits&lt; Scalar &gt;::one(), Scalar beta=Teuchos::ScalarTraits&lt; Scalar &gt;::zero()) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Ifpack2::Chebyshev</name>
    <filename>classIfpack2_1_1Chebyshev.html</filename>
    <templarg>MatrixType</templarg>
    <base virtualness="virtual">Preconditioner&lt; MatrixType::scalar_type, MatrixType::local_ordinal_type, MatrixType::global_ordinal_type, MatrixType::node_type &gt;</base>
    <member kind="function">
      <type></type>
      <name>Chebyshev</name>
      <anchorfile>classIfpack2_1_1Chebyshev.html</anchorfile>
      <anchor>a718d877fa28a14e32da83e6be4199256</anchor>
      <arglist>(const Teuchos::RCP&lt; const Tpetra::RowMatrix&lt; Scalar, LocalOrdinal, GlobalOrdinal, Node &gt; &gt; &amp;A)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~Chebyshev</name>
      <anchorfile>classIfpack2_1_1Chebyshev.html</anchorfile>
      <anchor>ad4e41b18f36837c00587356b65cb9cc8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setParameters</name>
      <anchorfile>classIfpack2_1_1Chebyshev.html</anchorfile>
      <anchor>ab0c464ffa718435c0dd10966647beda0</anchor>
      <arglist>(const Teuchos::ParameterList &amp;params)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initialize</name>
      <anchorfile>classIfpack2_1_1Chebyshev.html</anchorfile>
      <anchor>a58de3ab7b5dc7fefd2f3f51e1dcef561</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isInitialized</name>
      <anchorfile>classIfpack2_1_1Chebyshev.html</anchorfile>
      <anchor>adf6be7d63bea77bb7680eb0ad8915dd6</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>compute</name>
      <anchorfile>classIfpack2_1_1Chebyshev.html</anchorfile>
      <anchor>a231f970f4a6176a460ae39f57a2b3f90</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isComputed</name>
      <anchorfile>classIfpack2_1_1Chebyshev.html</anchorfile>
      <anchor>a260bed4e7d2a3b210e30443d86a8e0c3</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>apply</name>
      <anchorfile>classIfpack2_1_1Chebyshev.html</anchorfile>
      <anchor>aa9bcf445eb072d7ce5ee1406143e0f2f</anchor>
      <arglist>(const Tpetra::MultiVector&lt; Scalar, LocalOrdinal, GlobalOrdinal, Node &gt; &amp;X, Tpetra::MultiVector&lt; Scalar, LocalOrdinal, GlobalOrdinal, Node &gt; &amp;Y, Teuchos::ETransp mode=Teuchos::NO_TRANS, Scalar alpha=Teuchos::ScalarTraits&lt; Scalar &gt;::one(), Scalar beta=Teuchos::ScalarTraits&lt; Scalar &gt;::zero()) const </arglist>
    </member>
    <member kind="function">
      <type>const Teuchos::RCP&lt; const Tpetra::Map&lt; LocalOrdinal, GlobalOrdinal, Node &gt; &gt; &amp;</type>
      <name>getDomainMap</name>
      <anchorfile>classIfpack2_1_1Chebyshev.html</anchorfile>
      <anchor>a3195ac5aa8dfcf3349f23451b17ce0c3</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Teuchos::RCP&lt; const Tpetra::Map&lt; LocalOrdinal, GlobalOrdinal, Node &gt; &gt; &amp;</type>
      <name>getRangeMap</name>
      <anchorfile>classIfpack2_1_1Chebyshev.html</anchorfile>
      <anchor>af16fd375b5022508d51f3d6fbd1a748d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>hasTransposeApply</name>
      <anchorfile>classIfpack2_1_1Chebyshev.html</anchorfile>
      <anchor>a8a2df1e00ba3cf141353193c65eaed98</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>applyMat</name>
      <anchorfile>classIfpack2_1_1Chebyshev.html</anchorfile>
      <anchor>ae340ab1b00a23c7bfe0d0ebce9931aad</anchor>
      <arglist>(const Tpetra::MultiVector&lt; Scalar, LocalOrdinal, GlobalOrdinal, Node &gt; &amp;X, Tpetra::MultiVector&lt; Scalar, LocalOrdinal, GlobalOrdinal, Node &gt; &amp;Y, Teuchos::ETransp mode=Teuchos::NO_TRANS) const </arglist>
    </member>
    <member kind="function">
      <type>magnitudeType</type>
      <name>computeCondEst</name>
      <anchorfile>classIfpack2_1_1Chebyshev.html</anchorfile>
      <anchor>a8d9fb11257a837f1fe175606fb7c2b7d</anchor>
      <arglist>(CondestType CT=Cheap, LocalOrdinal MaxIters=1550, magnitudeType Tol=1e-9, const Teuchos::Ptr&lt; const Tpetra::RowMatrix&lt; Scalar, LocalOrdinal, GlobalOrdinal, Node &gt; &gt; &amp;matrix=Teuchos::null)</arglist>
    </member>
    <member kind="function">
      <type>magnitudeType</type>
      <name>getCondEst</name>
      <anchorfile>classIfpack2_1_1Chebyshev.html</anchorfile>
      <anchor>ab6f241f2cfc938b0de6faed4f077b07b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Teuchos::RCP&lt; const Teuchos::Comm&lt; int &gt; &gt; &amp;</type>
      <name>getComm</name>
      <anchorfile>classIfpack2_1_1Chebyshev.html</anchorfile>
      <anchor>a7f9eaa808b6a6632ab321218d83d6fe9</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Tpetra::RowMatrix&lt; Scalar, LocalOrdinal, GlobalOrdinal, Node &gt; &gt;</type>
      <name>getMatrix</name>
      <anchorfile>classIfpack2_1_1Chebyshev.html</anchorfile>
      <anchor>a2e9b4b46f52dea9d24fb195987b6b10b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>getComputeFlops</name>
      <anchorfile>classIfpack2_1_1Chebyshev.html</anchorfile>
      <anchor>a7e51e594222f473f8946af892c040e74</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>getApplyFlops</name>
      <anchorfile>classIfpack2_1_1Chebyshev.html</anchorfile>
      <anchor>ad02d151faa8d2c074227e47c7dc8cb80</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getNumInitialize</name>
      <anchorfile>classIfpack2_1_1Chebyshev.html</anchorfile>
      <anchor>a337dc471bf9355c410867c00d2f3ef6d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getNumCompute</name>
      <anchorfile>classIfpack2_1_1Chebyshev.html</anchorfile>
      <anchor>aa53085bb1f34553b5ac0ba400b0c067f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getNumApply</name>
      <anchorfile>classIfpack2_1_1Chebyshev.html</anchorfile>
      <anchor>aab7c28f599cdfe771ebbfe22e2afbea2</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>getInitializeTime</name>
      <anchorfile>classIfpack2_1_1Chebyshev.html</anchorfile>
      <anchor>a2be1f08b2d5c4b772988dbcfde95eeb6</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>getComputeTime</name>
      <anchorfile>classIfpack2_1_1Chebyshev.html</anchorfile>
      <anchor>a9022ca03f7d9caf99a8fb46762fa311e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>getApplyTime</name>
      <anchorfile>classIfpack2_1_1Chebyshev.html</anchorfile>
      <anchor>a5c4c84e6eab5bf2e29fa9c96a5e3b9b3</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>description</name>
      <anchorfile>classIfpack2_1_1Chebyshev.html</anchorfile>
      <anchor>a9010050d306ac7503d9d9c3c60d6b71e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>describe</name>
      <anchorfile>classIfpack2_1_1Chebyshev.html</anchorfile>
      <anchor>a94f376e041d8c17e96073ad51c32696c</anchor>
      <arglist>(Teuchos::FancyOStream &amp;out, const Teuchos::EVerbosityLevel verbLevel=Teuchos::Describable::verbLevel_default) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~Preconditioner</name>
      <anchorfile>classIfpack2_1_1Preconditioner.html</anchorfile>
      <anchor>a637973211128e0c09db53772df0f345d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual magnitudeType</type>
      <name>computeCondEst</name>
      <anchorfile>classIfpack2_1_1Preconditioner.html</anchorfile>
      <anchor>ab5b0a817cf6be83123192d38b5172131</anchor>
      <arglist>(CondestType CT=Ifpack2::Cheap, MatrixType::local_ordinal_typeMaxIters=1550, magnitudeType Tol=1e-9, const Teuchos::Ptr&lt; const Tpetra::RowMatrix&lt; MatrixType::scalar_type, MatrixType::local_ordinal_type, MatrixType::global_ordinal_type, MatrixType::node_type &gt; &gt; &amp;Matrix=Teuchos::null)=0</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>PowerMethod</name>
      <anchorfile>classIfpack2_1_1Chebyshev.html</anchorfile>
      <anchor>aab11166176bb9ddeb8358d56dbae1de9</anchor>
      <arglist>(const Tpetra::Operator&lt; Scalar, LocalOrdinal, GlobalOrdinal, Node &gt; &amp;Operator, const Tpetra::Vector&lt; Scalar, LocalOrdinal, GlobalOrdinal, Node &gt; &amp;InvPointDiagonal, const int MaximumIterations, Scalar &amp;LambdaMax)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>CG</name>
      <anchorfile>classIfpack2_1_1Chebyshev.html</anchorfile>
      <anchor>a1fe7ae129362c3eb4c3ab86662bf0b71</anchor>
      <arglist>(const Tpetra::Operator&lt; Scalar, LocalOrdinal, GlobalOrdinal, Node &gt; &amp;Operator, const Tpetra::Vector&lt; Scalar, LocalOrdinal, GlobalOrdinal, Node &gt; &amp;InvPointDiagonal, const int MaximumIterations, Scalar &amp;lambda_min, Scalar &amp;lambda_max)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Ifpack2::Diagonal</name>
    <filename>classIfpack2_1_1Diagonal.html</filename>
    <templarg></templarg>
    <base virtualness="virtual">Preconditioner&lt; MatrixType::scalar_type, MatrixType::local_ordinal_type, MatrixType::global_ordinal_type, MatrixType::node_type &gt;</base>
    <member kind="function">
      <type></type>
      <name>Diagonal</name>
      <anchorfile>classIfpack2_1_1Diagonal.html</anchorfile>
      <anchor>ab70b1d5d469659b305a99e36bf3bd704</anchor>
      <arglist>(const Teuchos::RCP&lt; const MatrixType &gt; &amp;A)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Diagonal</name>
      <anchorfile>classIfpack2_1_1Diagonal.html</anchorfile>
      <anchor>a87076bda9f10a8e91d16938cd15b85ce</anchor>
      <arglist>(const Teuchos::RCP&lt; const Tpetra::Vector&lt; Scalar, LocalOrdinal, GlobalOrdinal, Node &gt; &gt; &amp;diag)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~Diagonal</name>
      <anchorfile>classIfpack2_1_1Diagonal.html</anchorfile>
      <anchor>a0973b0961903713826557bbf6919ca25</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setParameters</name>
      <anchorfile>classIfpack2_1_1Diagonal.html</anchorfile>
      <anchor>a5dfbda84fa50949aa5c047a32be5b23f</anchor>
      <arglist>(const Teuchos::ParameterList &amp;params)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initialize</name>
      <anchorfile>classIfpack2_1_1Diagonal.html</anchorfile>
      <anchor>ab95fcf39161463695b2562b284cef0a4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isInitialized</name>
      <anchorfile>classIfpack2_1_1Diagonal.html</anchorfile>
      <anchor>a32b853e779dec9f98a425674f3d9645e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>compute</name>
      <anchorfile>classIfpack2_1_1Diagonal.html</anchorfile>
      <anchor>abac9b4c2e753dbe9af22c1a4e7ab8ea1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isComputed</name>
      <anchorfile>classIfpack2_1_1Diagonal.html</anchorfile>
      <anchor>ae8530d49aad3834529ba1844d75c08a0</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>apply</name>
      <anchorfile>classIfpack2_1_1Diagonal.html</anchorfile>
      <anchor>ae19ae839741ba1233a3f77d34a6e6b86</anchor>
      <arglist>(const Tpetra::MultiVector&lt; Scalar, LocalOrdinal, GlobalOrdinal, Node &gt; &amp;X, Tpetra::MultiVector&lt; Scalar, LocalOrdinal, GlobalOrdinal, Node &gt; &amp;Y, Teuchos::ETransp mode=Teuchos::NO_TRANS, Scalar alpha=Teuchos::ScalarTraits&lt; Scalar &gt;::one(), Scalar beta=Teuchos::ScalarTraits&lt; Scalar &gt;::zero()) const </arglist>
    </member>
    <member kind="function">
      <type>const Teuchos::RCP&lt; const Tpetra::Map&lt; LocalOrdinal, GlobalOrdinal, Node &gt; &gt; &amp;</type>
      <name>getDomainMap</name>
      <anchorfile>classIfpack2_1_1Diagonal.html</anchorfile>
      <anchor>a2b15188da5023f059850591f4f7cf00d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Teuchos::RCP&lt; const Tpetra::Map&lt; LocalOrdinal, GlobalOrdinal, Node &gt; &gt; &amp;</type>
      <name>getRangeMap</name>
      <anchorfile>classIfpack2_1_1Diagonal.html</anchorfile>
      <anchor>a112d6d84fa131aaf9ee466c104d95f15</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>applyMat</name>
      <anchorfile>classIfpack2_1_1Diagonal.html</anchorfile>
      <anchor>a53da8a45a24eb79b6c6882fd5ec773af</anchor>
      <arglist>(const Tpetra::MultiVector&lt; Scalar, LocalOrdinal, GlobalOrdinal, Node &gt; &amp;X, Tpetra::MultiVector&lt; Scalar, LocalOrdinal, GlobalOrdinal, Node &gt; &amp;Y, Teuchos::ETransp mode=Teuchos::NO_TRANS) const </arglist>
    </member>
    <member kind="function">
      <type>magnitudeType</type>
      <name>computeCondEst</name>
      <anchorfile>classIfpack2_1_1Diagonal.html</anchorfile>
      <anchor>aee8e7f1be74d606c3bc3e40dfcb64aec</anchor>
      <arglist>(CondestType CT=Cheap, LocalOrdinal MaxIters=1550, magnitudeType Tol=1e-9, const Teuchos::Ptr&lt; const Tpetra::RowMatrix&lt; Scalar, LocalOrdinal, GlobalOrdinal, Node &gt; &gt; &amp;matrix=Teuchos::null)</arglist>
    </member>
    <member kind="function">
      <type>magnitudeType</type>
      <name>getCondEst</name>
      <anchorfile>classIfpack2_1_1Diagonal.html</anchorfile>
      <anchor>a93455520dd51f6d289fbb79ffafbde19</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Teuchos::RCP&lt; const Teuchos::Comm&lt; int &gt; &gt; &amp;</type>
      <name>getComm</name>
      <anchorfile>classIfpack2_1_1Diagonal.html</anchorfile>
      <anchor>a861cbd8c73af934e1d5776a9d6e753df</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Tpetra::RowMatrix&lt; Scalar, LocalOrdinal, GlobalOrdinal, Node &gt; &gt;</type>
      <name>getMatrix</name>
      <anchorfile>classIfpack2_1_1Diagonal.html</anchorfile>
      <anchor>ad38a44a840b1485e94db9ad77af358b0</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>getComputeFlops</name>
      <anchorfile>classIfpack2_1_1Diagonal.html</anchorfile>
      <anchor>a21358e237fc6e453ebd8328ca3aa7c6a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>getApplyFlops</name>
      <anchorfile>classIfpack2_1_1Diagonal.html</anchorfile>
      <anchor>a3f792f03d7854c8f5595e9a9616a3ea1</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getNumInitialize</name>
      <anchorfile>classIfpack2_1_1Diagonal.html</anchorfile>
      <anchor>a4ed8d47460383713936b920446d833b6</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getNumCompute</name>
      <anchorfile>classIfpack2_1_1Diagonal.html</anchorfile>
      <anchor>a887d0f4bed955805824f052163cad457</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getNumApply</name>
      <anchorfile>classIfpack2_1_1Diagonal.html</anchorfile>
      <anchor>a5137a68476d5642fff2dd973dea94037</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>getInitializeTime</name>
      <anchorfile>classIfpack2_1_1Diagonal.html</anchorfile>
      <anchor>af315d947a107e0c78eb78c2ce42b4d84</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>getComputeTime</name>
      <anchorfile>classIfpack2_1_1Diagonal.html</anchorfile>
      <anchor>a03e5673d7f061825a34ed97feb2417c4</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>getApplyTime</name>
      <anchorfile>classIfpack2_1_1Diagonal.html</anchorfile>
      <anchor>adfb4a1207d46a835f272c0101905e7af</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>description</name>
      <anchorfile>classIfpack2_1_1Diagonal.html</anchorfile>
      <anchor>ae9155ee23aa16db703805fd8e1a9afbd</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>describe</name>
      <anchorfile>classIfpack2_1_1Diagonal.html</anchorfile>
      <anchor>ad601d5c3bd6dba43160a54fc31571527</anchor>
      <arglist>(Teuchos::FancyOStream &amp;out, const Teuchos::EVerbosityLevel verbLevel=Teuchos::Describable::verbLevel_default) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~Preconditioner</name>
      <anchorfile>classIfpack2_1_1Preconditioner.html</anchorfile>
      <anchor>a637973211128e0c09db53772df0f345d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual magnitudeType</type>
      <name>computeCondEst</name>
      <anchorfile>classIfpack2_1_1Preconditioner.html</anchorfile>
      <anchor>ab5b0a817cf6be83123192d38b5172131</anchor>
      <arglist>(CondestType CT=Ifpack2::Cheap, MatrixType::local_ordinal_typeMaxIters=1550, magnitudeType Tol=1e-9, const Teuchos::Ptr&lt; const Tpetra::RowMatrix&lt; MatrixType::scalar_type, MatrixType::local_ordinal_type, MatrixType::global_ordinal_type, MatrixType::node_type &gt; &gt; &amp;Matrix=Teuchos::null)=0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Ifpack2::DiagonalFilter</name>
    <filename>classIfpack2_1_1DiagonalFilter.html</filename>
    <templarg></templarg>
    <member kind="function">
      <type></type>
      <name>DiagonalFilter</name>
      <anchorfile>classIfpack2_1_1DiagonalFilter.html</anchorfile>
      <anchor>a43b767d75b0ebeeabf62fe65870fb7f2</anchor>
      <arglist>(const Teuchos::RCP&lt; const Tpetra::RowMatrix&lt; Scalar, LocalOrdinal, GlobalOrdinal, Node &gt; &gt; &amp;Matrix, magnitudeType AbsoluteThreshold, magnitudeType RelativeThreshold)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~DiagonalFilter</name>
      <anchorfile>classIfpack2_1_1DiagonalFilter.html</anchorfile>
      <anchor>a0e29490b79b0c74af4d67386dbcaa2ab</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const Teuchos::RCP&lt; const Teuchos::Comm&lt; int &gt; &gt; &amp;</type>
      <name>getComm</name>
      <anchorfile>classIfpack2_1_1DiagonalFilter.html</anchorfile>
      <anchor>a21a65df15d5c15f4b9700e399d327d02</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual Teuchos::RCP&lt; Node &gt;</type>
      <name>getNode</name>
      <anchorfile>classIfpack2_1_1DiagonalFilter.html</anchorfile>
      <anchor>a6d7b2ca04220a3e29a31ab2b76fad237</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const Teuchos::RCP&lt; const Tpetra::Map&lt; LocalOrdinal, GlobalOrdinal, Node &gt; &gt; &amp;</type>
      <name>getRowMap</name>
      <anchorfile>classIfpack2_1_1DiagonalFilter.html</anchorfile>
      <anchor>a8623c5e98ab1d555d5501f2f092e30e9</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const Teuchos::RCP&lt; const Tpetra::Map&lt; LocalOrdinal, GlobalOrdinal, Node &gt; &gt; &amp;</type>
      <name>getColMap</name>
      <anchorfile>classIfpack2_1_1DiagonalFilter.html</anchorfile>
      <anchor>af3a82fa989df143afa2ea2b2fd5171af</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const Teuchos::RCP&lt; const Tpetra::Map&lt; LocalOrdinal, GlobalOrdinal, Node &gt; &gt; &amp;</type>
      <name>getDomainMap</name>
      <anchorfile>classIfpack2_1_1DiagonalFilter.html</anchorfile>
      <anchor>a6fc4e02d3474d80b89f838780bc37678</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const Teuchos::RCP&lt; const Tpetra::Map&lt; LocalOrdinal, GlobalOrdinal, Node &gt; &gt; &amp;</type>
      <name>getRangeMap</name>
      <anchorfile>classIfpack2_1_1DiagonalFilter.html</anchorfile>
      <anchor>a32cac0f3f7f7e39bd48b9be355acbdad</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual Teuchos::RCP&lt; const Tpetra::RowGraph&lt; LocalOrdinal, GlobalOrdinal, Node &gt; &gt;</type>
      <name>getGraph</name>
      <anchorfile>classIfpack2_1_1DiagonalFilter.html</anchorfile>
      <anchor>a28181e18fb23ba9854957865c24f068b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual global_size_t</type>
      <name>getGlobalNumRows</name>
      <anchorfile>classIfpack2_1_1DiagonalFilter.html</anchorfile>
      <anchor>ab03ca9df1964107db43b3fb500d977ff</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual global_size_t</type>
      <name>getGlobalNumCols</name>
      <anchorfile>classIfpack2_1_1DiagonalFilter.html</anchorfile>
      <anchor>a2f29c4a39677515f399eb775edbd24ef</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual size_t</type>
      <name>getNodeNumRows</name>
      <anchorfile>classIfpack2_1_1DiagonalFilter.html</anchorfile>
      <anchor>a34e3902319f6d2e226150312258ab2ca</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual size_t</type>
      <name>getNodeNumCols</name>
      <anchorfile>classIfpack2_1_1DiagonalFilter.html</anchorfile>
      <anchor>a4f14cd4d590fb0d8b3876555d28cf051</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual GlobalOrdinal</type>
      <name>getIndexBase</name>
      <anchorfile>classIfpack2_1_1DiagonalFilter.html</anchorfile>
      <anchor>a036b0b89eb8cd8e4e091ca010b26a5fc</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual global_size_t</type>
      <name>getGlobalNumEntries</name>
      <anchorfile>classIfpack2_1_1DiagonalFilter.html</anchorfile>
      <anchor>a3bb5d1a03b92992b4c8d8b18d26a8910</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual size_t</type>
      <name>getNodeNumEntries</name>
      <anchorfile>classIfpack2_1_1DiagonalFilter.html</anchorfile>
      <anchor>a38be825ff0094d85984ff028de823894</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual size_t</type>
      <name>getNumEntriesInGlobalRow</name>
      <anchorfile>classIfpack2_1_1DiagonalFilter.html</anchorfile>
      <anchor>a61f63a1a7291124212a45d5b507db8b0</anchor>
      <arglist>(GlobalOrdinal globalRow) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual size_t</type>
      <name>getNumEntriesInLocalRow</name>
      <anchorfile>classIfpack2_1_1DiagonalFilter.html</anchorfile>
      <anchor>af696d21287d6b2a7b046d5653afdef94</anchor>
      <arglist>(LocalOrdinal localRow) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual global_size_t</type>
      <name>getGlobalNumDiags</name>
      <anchorfile>classIfpack2_1_1DiagonalFilter.html</anchorfile>
      <anchor>abf73fc425243b59c3760fb8fedc873b3</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual size_t</type>
      <name>getNodeNumDiags</name>
      <anchorfile>classIfpack2_1_1DiagonalFilter.html</anchorfile>
      <anchor>aabe30e80d2a4296eb0fd346cf8184910</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual size_t</type>
      <name>getGlobalMaxNumRowEntries</name>
      <anchorfile>classIfpack2_1_1DiagonalFilter.html</anchorfile>
      <anchor>a5e4313341c30ad5944542f9cfe8adaa0</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual size_t</type>
      <name>getNodeMaxNumRowEntries</name>
      <anchorfile>classIfpack2_1_1DiagonalFilter.html</anchorfile>
      <anchor>a5f33c99278c6b476903b25160dc92a34</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>hasColMap</name>
      <anchorfile>classIfpack2_1_1DiagonalFilter.html</anchorfile>
      <anchor>aeaec7f15e45e19c16339d7bfa5a9e418</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>isLowerTriangular</name>
      <anchorfile>classIfpack2_1_1DiagonalFilter.html</anchorfile>
      <anchor>a0570650c115f51eaae680c899331e97f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>isUpperTriangular</name>
      <anchorfile>classIfpack2_1_1DiagonalFilter.html</anchorfile>
      <anchor>a73553b306ebcce8356d93fc8e1149552</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>isLocallyIndexed</name>
      <anchorfile>classIfpack2_1_1DiagonalFilter.html</anchorfile>
      <anchor>a900d2a4053064cd3a4bbcac5e3e66c29</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>isGloballyIndexed</name>
      <anchorfile>classIfpack2_1_1DiagonalFilter.html</anchorfile>
      <anchor>a0c049a804d5df3d4eff7173c82fa418d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>isFillComplete</name>
      <anchorfile>classIfpack2_1_1DiagonalFilter.html</anchorfile>
      <anchor>a54e8c7cdd92900b2415cf920f762f0fa</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>getGlobalRowCopy</name>
      <anchorfile>classIfpack2_1_1DiagonalFilter.html</anchorfile>
      <anchor>a0c563b178b4b200d37250a11312f1629</anchor>
      <arglist>(GlobalOrdinal GlobalRow, const Teuchos::ArrayView&lt; GlobalOrdinal &gt; &amp;Indices, const Teuchos::ArrayView&lt; Scalar &gt; &amp;Values, size_t &amp;NumEntries) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>getLocalRowCopy</name>
      <anchorfile>classIfpack2_1_1DiagonalFilter.html</anchorfile>
      <anchor>a0d5915db7043c2d8497a3d0397adc754</anchor>
      <arglist>(LocalOrdinal LocalRow, const Teuchos::ArrayView&lt; LocalOrdinal &gt; &amp;Indices, const Teuchos::ArrayView&lt; Scalar &gt; &amp;Values, size_t &amp;NumEntries) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>getGlobalRowView</name>
      <anchorfile>classIfpack2_1_1DiagonalFilter.html</anchorfile>
      <anchor>a41c2c69ea61ee05df80e9febbaa55b18</anchor>
      <arglist>(GlobalOrdinal GlobalRow, Teuchos::ArrayView&lt; const GlobalOrdinal &gt; &amp;indices, Teuchos::ArrayView&lt; const Scalar &gt; &amp;values) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>getLocalRowView</name>
      <anchorfile>classIfpack2_1_1DiagonalFilter.html</anchorfile>
      <anchor>af892d604a77bc7b690898eba678e545c</anchor>
      <arglist>(LocalOrdinal LocalRow, Teuchos::ArrayView&lt; const LocalOrdinal &gt; &amp;indices, Teuchos::ArrayView&lt; const Scalar &gt; &amp;values) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>getLocalDiagCopy</name>
      <anchorfile>classIfpack2_1_1DiagonalFilter.html</anchorfile>
      <anchor>a96ca6d0fb96b0b9bc31e40c5cbc0c02f</anchor>
      <arglist>(Tpetra::Vector&lt; Scalar, LocalOrdinal, GlobalOrdinal, Node &gt; &amp;diag) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>leftScale</name>
      <anchorfile>classIfpack2_1_1DiagonalFilter.html</anchorfile>
      <anchor>a6837eb9e8e65317160c90962971b5971</anchor>
      <arglist>(const Tpetra::Vector&lt; Scalar, LocalOrdinal, GlobalOrdinal, Node &gt; &amp;x)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>rightScale</name>
      <anchorfile>classIfpack2_1_1DiagonalFilter.html</anchorfile>
      <anchor>ad87309b48d253fafba48d163e1ef19c2</anchor>
      <arglist>(const Tpetra::Vector&lt; Scalar, LocalOrdinal, GlobalOrdinal, Node &gt; &amp;x)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual Teuchos::ScalarTraits&lt; Scalar &gt;::magnitudeType</type>
      <name>getFrobeniusNorm</name>
      <anchorfile>classIfpack2_1_1DiagonalFilter.html</anchorfile>
      <anchor>ac916bb103436a4d8329abd13997c8344</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>apply</name>
      <anchorfile>classIfpack2_1_1DiagonalFilter.html</anchorfile>
      <anchor>a7b0892d9b441ad4735c53e5fc5889801</anchor>
      <arglist>(const Tpetra::MultiVector&lt; Scalar, LocalOrdinal, GlobalOrdinal, Node &gt; &amp;X, Tpetra::MultiVector&lt; Scalar, LocalOrdinal, GlobalOrdinal, Node &gt; &amp;Y, Teuchos::ETransp mode=Teuchos::NO_TRANS, Scalar alpha=Teuchos::ScalarTraits&lt; Scalar &gt;::one(), Scalar beta=Teuchos::ScalarTraits&lt; Scalar &gt;::zero()) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>hasTransposeApply</name>
      <anchorfile>classIfpack2_1_1DiagonalFilter.html</anchorfile>
      <anchor>a33b603348dd3ba8fe5168c4c28b399e8</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual TPETRA_DEPRECATED void</type>
      <name>getGlobalRowView</name>
      <anchorfile>classIfpack2_1_1DiagonalFilter.html</anchorfile>
      <anchor>a8d5cd44d203f5459d446efb0ea2cb231</anchor>
      <arglist>(GlobalOrdinal GlobalRow, Teuchos::ArrayRCP&lt; const GlobalOrdinal &gt; &amp;indices, Teuchos::ArrayRCP&lt; const Scalar &gt; &amp;values) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual TPETRA_DEPRECATED void</type>
      <name>getLocalRowView</name>
      <anchorfile>classIfpack2_1_1DiagonalFilter.html</anchorfile>
      <anchor>a6ab950a176f3449f2936995bc4b42934</anchor>
      <arglist>(LocalOrdinal LocalRow, Teuchos::ArrayRCP&lt; const LocalOrdinal &gt; &amp;indices, Teuchos::ArrayRCP&lt; const Scalar &gt; &amp;values) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Ifpack2::DropFilter</name>
    <filename>classIfpack2_1_1DropFilter.html</filename>
    <templarg></templarg>
    <member kind="function">
      <type></type>
      <name>DropFilter</name>
      <anchorfile>classIfpack2_1_1DropFilter.html</anchorfile>
      <anchor>a689da80907e1b675dcb0c243b1155eeb</anchor>
      <arglist>(const Teuchos::RCP&lt; const Tpetra::RowMatrix&lt; Scalar, LocalOrdinal, GlobalOrdinal, Node &gt; &gt; &amp;Matrix, magnitudeType DropTol)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~DropFilter</name>
      <anchorfile>classIfpack2_1_1DropFilter.html</anchorfile>
      <anchor>aa69553ad618f27a19ba79025cdecd827</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const Teuchos::RCP&lt; const Teuchos::Comm&lt; int &gt; &gt; &amp;</type>
      <name>getComm</name>
      <anchorfile>classIfpack2_1_1DropFilter.html</anchorfile>
      <anchor>ada20fa28ca8633407ae000f85b78ab8f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual Teuchos::RCP&lt; Node &gt;</type>
      <name>getNode</name>
      <anchorfile>classIfpack2_1_1DropFilter.html</anchorfile>
      <anchor>ae082912ff994edecf3ad5681b1e35367</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const Teuchos::RCP&lt; const Tpetra::Map&lt; LocalOrdinal, GlobalOrdinal, Node &gt; &gt; &amp;</type>
      <name>getRowMap</name>
      <anchorfile>classIfpack2_1_1DropFilter.html</anchorfile>
      <anchor>a27a594766963e89f90b110035d121f96</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const Teuchos::RCP&lt; const Tpetra::Map&lt; LocalOrdinal, GlobalOrdinal, Node &gt; &gt; &amp;</type>
      <name>getColMap</name>
      <anchorfile>classIfpack2_1_1DropFilter.html</anchorfile>
      <anchor>a9cca8d6469c8f10e7bda6b5990e85683</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const Teuchos::RCP&lt; const Tpetra::Map&lt; LocalOrdinal, GlobalOrdinal, Node &gt; &gt; &amp;</type>
      <name>getDomainMap</name>
      <anchorfile>classIfpack2_1_1DropFilter.html</anchorfile>
      <anchor>aa49861a9d1b776bb311155c1be5136c8</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const Teuchos::RCP&lt; const Tpetra::Map&lt; LocalOrdinal, GlobalOrdinal, Node &gt; &gt; &amp;</type>
      <name>getRangeMap</name>
      <anchorfile>classIfpack2_1_1DropFilter.html</anchorfile>
      <anchor>a2fc479ff10806525e9a5d5f005f4dbf3</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual Teuchos::RCP&lt; const Tpetra::RowGraph&lt; LocalOrdinal, GlobalOrdinal, Node &gt; &gt;</type>
      <name>getGraph</name>
      <anchorfile>classIfpack2_1_1DropFilter.html</anchorfile>
      <anchor>ac2189eafc6b82d3cee14549df12db2f5</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual global_size_t</type>
      <name>getGlobalNumRows</name>
      <anchorfile>classIfpack2_1_1DropFilter.html</anchorfile>
      <anchor>ab3e97e5750212133bde118780947ba53</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual global_size_t</type>
      <name>getGlobalNumCols</name>
      <anchorfile>classIfpack2_1_1DropFilter.html</anchorfile>
      <anchor>a3b111f25bf835f01fe7753f245fb7bbe</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual size_t</type>
      <name>getNodeNumRows</name>
      <anchorfile>classIfpack2_1_1DropFilter.html</anchorfile>
      <anchor>ad6d95c45d09cfb0a0fccd2a4d9a66594</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual size_t</type>
      <name>getNodeNumCols</name>
      <anchorfile>classIfpack2_1_1DropFilter.html</anchorfile>
      <anchor>a4d4367ca12f144ed73d9677d29c73417</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual GlobalOrdinal</type>
      <name>getIndexBase</name>
      <anchorfile>classIfpack2_1_1DropFilter.html</anchorfile>
      <anchor>a70f719e6a1c1f7b32438c3d65caca8c0</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual global_size_t</type>
      <name>getGlobalNumEntries</name>
      <anchorfile>classIfpack2_1_1DropFilter.html</anchorfile>
      <anchor>a8caf9efa9a7f99439780c76d9a17e504</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual size_t</type>
      <name>getNodeNumEntries</name>
      <anchorfile>classIfpack2_1_1DropFilter.html</anchorfile>
      <anchor>a039dae1be4353bb1a9269c17a1b6a6cf</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual size_t</type>
      <name>getNumEntriesInGlobalRow</name>
      <anchorfile>classIfpack2_1_1DropFilter.html</anchorfile>
      <anchor>ad755ea4a7fa95fde00258c4b2f528dc3</anchor>
      <arglist>(GlobalOrdinal globalRow) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual size_t</type>
      <name>getNumEntriesInLocalRow</name>
      <anchorfile>classIfpack2_1_1DropFilter.html</anchorfile>
      <anchor>aa959924b5ec818ea175d01a3b6e89f78</anchor>
      <arglist>(LocalOrdinal localRow) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual global_size_t</type>
      <name>getGlobalNumDiags</name>
      <anchorfile>classIfpack2_1_1DropFilter.html</anchorfile>
      <anchor>ad817c46fdd70dbecad73a6c3b1bcdc31</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual size_t</type>
      <name>getNodeNumDiags</name>
      <anchorfile>classIfpack2_1_1DropFilter.html</anchorfile>
      <anchor>afc4bd367d1b0a5bfeb6080b506ec844a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual size_t</type>
      <name>getGlobalMaxNumRowEntries</name>
      <anchorfile>classIfpack2_1_1DropFilter.html</anchorfile>
      <anchor>ad105fa4ec7caa1560d1a4e2911f798bf</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual size_t</type>
      <name>getNodeMaxNumRowEntries</name>
      <anchorfile>classIfpack2_1_1DropFilter.html</anchorfile>
      <anchor>a8461827127cdbdfc1f7b5aca24405baf</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>hasColMap</name>
      <anchorfile>classIfpack2_1_1DropFilter.html</anchorfile>
      <anchor>a3568aa5cbf42cb743bc15b219efd91c3</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>isLowerTriangular</name>
      <anchorfile>classIfpack2_1_1DropFilter.html</anchorfile>
      <anchor>ab129b22d4e35b875a53165c55426a4af</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>isUpperTriangular</name>
      <anchorfile>classIfpack2_1_1DropFilter.html</anchorfile>
      <anchor>a79ced63e1f8ab5de9b2e0da0333f18b6</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>isLocallyIndexed</name>
      <anchorfile>classIfpack2_1_1DropFilter.html</anchorfile>
      <anchor>a6eb0d6df3ffdd6c9bbc0a20d8f25ace9</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>isGloballyIndexed</name>
      <anchorfile>classIfpack2_1_1DropFilter.html</anchorfile>
      <anchor>a1f19adde262d042c2d5428223a128c89</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>isFillComplete</name>
      <anchorfile>classIfpack2_1_1DropFilter.html</anchorfile>
      <anchor>adb9ea1acd4efc09cb81daa7daf92a7f3</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>getGlobalRowCopy</name>
      <anchorfile>classIfpack2_1_1DropFilter.html</anchorfile>
      <anchor>ac83b37e0091dde54bc9b8e15e9d0f8ea</anchor>
      <arglist>(GlobalOrdinal GlobalRow, const Teuchos::ArrayView&lt; GlobalOrdinal &gt; &amp;Indices, const Teuchos::ArrayView&lt; Scalar &gt; &amp;Values, size_t &amp;NumEntries) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>getLocalRowCopy</name>
      <anchorfile>classIfpack2_1_1DropFilter.html</anchorfile>
      <anchor>ac926fe80e4e6dc3e48c81d126a5b84f8</anchor>
      <arglist>(LocalOrdinal DropRow, const Teuchos::ArrayView&lt; LocalOrdinal &gt; &amp;Indices, const Teuchos::ArrayView&lt; Scalar &gt; &amp;Values, size_t &amp;NumEntries) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>getGlobalRowView</name>
      <anchorfile>classIfpack2_1_1DropFilter.html</anchorfile>
      <anchor>a257524bccb445d5a02679a0fc87655e6</anchor>
      <arglist>(GlobalOrdinal GlobalRow, Teuchos::ArrayView&lt; const GlobalOrdinal &gt; &amp;indices, Teuchos::ArrayView&lt; const Scalar &gt; &amp;values) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>getLocalRowView</name>
      <anchorfile>classIfpack2_1_1DropFilter.html</anchorfile>
      <anchor>a370af71e9af6b4a99ef4dfff573058ac</anchor>
      <arglist>(LocalOrdinal DropRow, Teuchos::ArrayView&lt; const LocalOrdinal &gt; &amp;indices, Teuchos::ArrayView&lt; const Scalar &gt; &amp;values) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>getLocalDiagCopy</name>
      <anchorfile>classIfpack2_1_1DropFilter.html</anchorfile>
      <anchor>a0a3729b1c446372547031384638e9fae</anchor>
      <arglist>(Tpetra::Vector&lt; Scalar, LocalOrdinal, GlobalOrdinal, Node &gt; &amp;diag) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>leftScale</name>
      <anchorfile>classIfpack2_1_1DropFilter.html</anchorfile>
      <anchor>a3598a8b6719f6a885f62fb5dc875a867</anchor>
      <arglist>(const Tpetra::Vector&lt; Scalar, LocalOrdinal, GlobalOrdinal, Node &gt; &amp;x)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>rightScale</name>
      <anchorfile>classIfpack2_1_1DropFilter.html</anchorfile>
      <anchor>a11cd2bf32a10d4d83aaff5208ca9af99</anchor>
      <arglist>(const Tpetra::Vector&lt; Scalar, LocalOrdinal, GlobalOrdinal, Node &gt; &amp;x)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual Teuchos::ScalarTraits&lt; Scalar &gt;::magnitudeType</type>
      <name>getFrobeniusNorm</name>
      <anchorfile>classIfpack2_1_1DropFilter.html</anchorfile>
      <anchor>a61c83fa557f47e6e72d3227f64aefc4a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>apply</name>
      <anchorfile>classIfpack2_1_1DropFilter.html</anchorfile>
      <anchor>a645327d95ae7b1f8be6626be555794d4</anchor>
      <arglist>(const Tpetra::MultiVector&lt; Scalar, LocalOrdinal, GlobalOrdinal, Node &gt; &amp;X, Tpetra::MultiVector&lt; Scalar, LocalOrdinal, GlobalOrdinal, Node &gt; &amp;Y, Teuchos::ETransp mode=Teuchos::NO_TRANS, Scalar alpha=Teuchos::ScalarTraits&lt; Scalar &gt;::one(), Scalar beta=Teuchos::ScalarTraits&lt; Scalar &gt;::zero()) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>hasTransposeApply</name>
      <anchorfile>classIfpack2_1_1DropFilter.html</anchorfile>
      <anchor>a6cfee5f93e1afb9052409aee6e346f3c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual TPETRA_DEPRECATED void</type>
      <name>getGlobalRowView</name>
      <anchorfile>classIfpack2_1_1DropFilter.html</anchorfile>
      <anchor>af0b8088da77a961ec40403c38f33b30f</anchor>
      <arglist>(GlobalOrdinal GlobalRow, Teuchos::ArrayRCP&lt; const GlobalOrdinal &gt; &amp;indices, Teuchos::ArrayRCP&lt; const Scalar &gt; &amp;values) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual TPETRA_DEPRECATED void</type>
      <name>getLocalRowView</name>
      <anchorfile>classIfpack2_1_1DropFilter.html</anchorfile>
      <anchor>ac772b382de74b1a8de39142c27598902</anchor>
      <arglist>(LocalOrdinal DropRow, Teuchos::ArrayRCP&lt; const LocalOrdinal &gt; &amp;indices, Teuchos::ArrayRCP&lt; const Scalar &gt; &amp;values) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Ifpack2::Factory</name>
    <filename>classIfpack2_1_1Factory.html</filename>
    <member kind="function" static="yes">
      <type>static Teuchos::RCP&lt; Ifpack2::Preconditioner&lt; typename MatrixType::scalar_type, typename MatrixType::local_ordinal_type, typename MatrixType::global_ordinal_type, typename MatrixType::node_type &gt; &gt;</type>
      <name>create</name>
      <anchorfile>classIfpack2_1_1Factory.html</anchorfile>
      <anchor>aafa496bc7d5e71788de0f1be96a3bcf7</anchor>
      <arglist>(const std::string &amp;prec_type, const Teuchos::RCP&lt; const MatrixType &gt; &amp;matrix, const int overlap=0)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Ifpack2::IlukGraph</name>
    <filename>classIfpack2_1_1IlukGraph.html</filename>
    <templarg>LocalOrdinal</templarg>
    <templarg>GlobalOrdinal</templarg>
    <templarg>Node</templarg>
    <member kind="function">
      <type></type>
      <name>IlukGraph</name>
      <anchorfile>classIfpack2_1_1IlukGraph.html</anchorfile>
      <anchor>a251432f1ee9cc9696960633e052bd974</anchor>
      <arglist>(const Teuchos::RCP&lt; const Tpetra::CrsGraph&lt; LocalOrdinal, GlobalOrdinal, Node &gt; &gt; &amp;Graph_in, int LevelFill_in, int LevelOverlap_in)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>IlukGraph</name>
      <anchorfile>classIfpack2_1_1IlukGraph.html</anchorfile>
      <anchor>ac46ee2526cea1679c3180b3fa7511c33</anchor>
      <arglist>(const IlukGraph&lt; LocalOrdinal, GlobalOrdinal, Node &gt; &amp;Graph_in)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~IlukGraph</name>
      <anchorfile>classIfpack2_1_1IlukGraph.html</anchorfile>
      <anchor>a2f00def4e721e74c21f84ed84adefc09</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setParameters</name>
      <anchorfile>classIfpack2_1_1IlukGraph.html</anchorfile>
      <anchor>a6cb6bde7e601b247eda336623cc0202d</anchor>
      <arglist>(const Teuchos::ParameterList &amp;parameterlist)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>constructFilledGraph</name>
      <anchorfile>classIfpack2_1_1IlukGraph.html</anchorfile>
      <anchor>a50b6a0b291d49896824c3fa88e21f1e7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>constructOverlapGraph</name>
      <anchorfile>classIfpack2_1_1IlukGraph.html</anchorfile>
      <anchor>ad617099824618b758fe9f5ad35da932c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getLevelFill</name>
      <anchorfile>classIfpack2_1_1IlukGraph.html</anchorfile>
      <anchor>af944a3d521e33a98a73af9594b2d6658</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getLevelOverlap</name>
      <anchorfile>classIfpack2_1_1IlukGraph.html</anchorfile>
      <anchor>aeb39509308fff31e510f417772d15d90</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Teuchos::RCP&lt; Tpetra::CrsGraph&lt; LocalOrdinal, GlobalOrdinal, Node &gt; &gt; &amp;</type>
      <name>getL_Graph</name>
      <anchorfile>classIfpack2_1_1IlukGraph.html</anchorfile>
      <anchor>a17ba82db7e6910757cbc805a1f9225b8</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Teuchos::RCP&lt; Tpetra::CrsGraph&lt; LocalOrdinal, GlobalOrdinal, Node &gt; &gt; &amp;</type>
      <name>getU_Graph</name>
      <anchorfile>classIfpack2_1_1IlukGraph.html</anchorfile>
      <anchor>a92c660308e243ff79f309b7867284cbd</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Teuchos::RCP&lt; Tpetra::CrsGraph&lt; LocalOrdinal, GlobalOrdinal, Node &gt; &gt; &amp;</type>
      <name>getOverlapGraph</name>
      <anchorfile>classIfpack2_1_1IlukGraph.html</anchorfile>
      <anchor>ac8bf00ba92959768a9108b37c4f9795b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>size_t</type>
      <name>getNumGlobalDiagonals</name>
      <anchorfile>classIfpack2_1_1IlukGraph.html</anchorfile>
      <anchor>a71e94361a7d3b55a304f2290a61a89f5</anchor>
      <arglist>() const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Ifpack2::ILUT</name>
    <filename>classIfpack2_1_1ILUT.html</filename>
    <templarg>MatrixType</templarg>
    <base virtualness="virtual">Preconditioner&lt; MatrixType::scalar_type, MatrixType::local_ordinal_type, MatrixType::global_ordinal_type, MatrixType::node_type &gt;</base>
    <member kind="function">
      <type></type>
      <name>ILUT</name>
      <anchorfile>classIfpack2_1_1ILUT.html</anchorfile>
      <anchor>ab624b74fe7ea2d25186b797b80c82c35</anchor>
      <arglist>(const Teuchos::RCP&lt; const Tpetra::RowMatrix&lt; Scalar, LocalOrdinal, GlobalOrdinal, Node &gt; &gt; &amp;A)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~ILUT</name>
      <anchorfile>classIfpack2_1_1ILUT.html</anchorfile>
      <anchor>a79e54d460c2aafb095840335c8a12f70</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setParameters</name>
      <anchorfile>classIfpack2_1_1ILUT.html</anchorfile>
      <anchor>aee2011b313e3070ee43b2cfc2d183634</anchor>
      <arglist>(const Teuchos::ParameterList &amp;params)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initialize</name>
      <anchorfile>classIfpack2_1_1ILUT.html</anchorfile>
      <anchor>ad1213bdd746d0570905d9fe1b0728ba7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isInitialized</name>
      <anchorfile>classIfpack2_1_1ILUT.html</anchorfile>
      <anchor>af05a748e28df5d33e8a3a59747c0943a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>compute</name>
      <anchorfile>classIfpack2_1_1ILUT.html</anchorfile>
      <anchor>a2dcabf60eecf315f70448ebc4140a7f9</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isComputed</name>
      <anchorfile>classIfpack2_1_1ILUT.html</anchorfile>
      <anchor>a2b7045d16e6cff4a3e1c869e11ab6f7d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>apply</name>
      <anchorfile>classIfpack2_1_1ILUT.html</anchorfile>
      <anchor>a29104c391a11fc56c6d64b240eccdf03</anchor>
      <arglist>(const Tpetra::MultiVector&lt; Scalar, LocalOrdinal, GlobalOrdinal, Node &gt; &amp;X, Tpetra::MultiVector&lt; Scalar, LocalOrdinal, GlobalOrdinal, Node &gt; &amp;Y, Teuchos::ETransp mode=Teuchos::NO_TRANS, Scalar alpha=Teuchos::ScalarTraits&lt; Scalar &gt;::one(), Scalar beta=Teuchos::ScalarTraits&lt; Scalar &gt;::zero()) const </arglist>
    </member>
    <member kind="function">
      <type>const Teuchos::RCP&lt; const Tpetra::Map&lt; LocalOrdinal, GlobalOrdinal, Node &gt; &gt; &amp;</type>
      <name>getDomainMap</name>
      <anchorfile>classIfpack2_1_1ILUT.html</anchorfile>
      <anchor>a057aa4a30d1cf6c3ab7d7a6e11383f8e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Teuchos::RCP&lt; const Tpetra::Map&lt; LocalOrdinal, GlobalOrdinal, Node &gt; &gt; &amp;</type>
      <name>getRangeMap</name>
      <anchorfile>classIfpack2_1_1ILUT.html</anchorfile>
      <anchor>a07a5c5cc06cc82acc5ae76de7b2317ba</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>hasTransposeApply</name>
      <anchorfile>classIfpack2_1_1ILUT.html</anchorfile>
      <anchor>a2c2743f26da403d68bcaa93a88020ee7</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>magnitudeType</type>
      <name>computeCondEst</name>
      <anchorfile>classIfpack2_1_1ILUT.html</anchorfile>
      <anchor>afea391934d2137dc2d1072dec1ee5477</anchor>
      <arglist>(CondestType CT=Cheap, LocalOrdinal MaxIters=1550, magnitudeType Tol=1e-9, const Teuchos::Ptr&lt; const Tpetra::RowMatrix&lt; Scalar, LocalOrdinal, GlobalOrdinal, Node &gt; &gt; &amp;Matrix_in=Teuchos::null)</arglist>
    </member>
    <member kind="function">
      <type>magnitudeType</type>
      <name>getCondEst</name>
      <anchorfile>classIfpack2_1_1ILUT.html</anchorfile>
      <anchor>a5e0b911eff12e52e54031d8098d86e29</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Teuchos::RCP&lt; const Teuchos::Comm&lt; int &gt; &gt; &amp;</type>
      <name>getComm</name>
      <anchorfile>classIfpack2_1_1ILUT.html</anchorfile>
      <anchor>a8c2b3debf2a62482a84b25c3987d3168</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Tpetra::RowMatrix&lt; Scalar, LocalOrdinal, GlobalOrdinal, Node &gt; &gt;</type>
      <name>getMatrix</name>
      <anchorfile>classIfpack2_1_1ILUT.html</anchorfile>
      <anchor>ad6269fb7e81189451867c15a47e564a6</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Teuchos::RCP&lt; const MatrixType &gt;</type>
      <name>getL</name>
      <anchorfile>classIfpack2_1_1ILUT.html</anchorfile>
      <anchor>ae53b5b757e08dddbd47d2029c416f43e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Teuchos::RCP&lt; const MatrixType &gt;</type>
      <name>getU</name>
      <anchorfile>classIfpack2_1_1ILUT.html</anchorfile>
      <anchor>a910eebda6eb9323dc6bbc577f653f857</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getNumInitialize</name>
      <anchorfile>classIfpack2_1_1ILUT.html</anchorfile>
      <anchor>a16c5ed37c9502afc7d92b30c22e288cf</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getNumCompute</name>
      <anchorfile>classIfpack2_1_1ILUT.html</anchorfile>
      <anchor>a14d826e90c9aaf3354ac0403aaac9f78</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getNumApply</name>
      <anchorfile>classIfpack2_1_1ILUT.html</anchorfile>
      <anchor>a1882cc155e53240cf14011d1228569a7</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>getInitializeTime</name>
      <anchorfile>classIfpack2_1_1ILUT.html</anchorfile>
      <anchor>a3e5f7563b218a68949e696a48ba9a1a3</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>getComputeTime</name>
      <anchorfile>classIfpack2_1_1ILUT.html</anchorfile>
      <anchor>ad60cc5241bd3f3ca39667cee9f14e313</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>getApplyTime</name>
      <anchorfile>classIfpack2_1_1ILUT.html</anchorfile>
      <anchor>aebbe7dff25e0a1b330e1326dd58dcc76</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>getLevelOfFill</name>
      <anchorfile>classIfpack2_1_1ILUT.html</anchorfile>
      <anchor>af09110103ed51d5eb1562f9c53230b9b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>getAbsoluteThreshold</name>
      <anchorfile>classIfpack2_1_1ILUT.html</anchorfile>
      <anchor>ae076c37766fa03fef62ccb1fe89c905f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>getRelativeThreshold</name>
      <anchorfile>classIfpack2_1_1ILUT.html</anchorfile>
      <anchor>a42a94ff86573578a9358a5f0412565df</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>magnitudeType</type>
      <name>getRelaxValue</name>
      <anchorfile>classIfpack2_1_1ILUT.html</anchorfile>
      <anchor>acc8c9ae2af5c7e65a18682ab8d73fe24</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>magnitudeType</type>
      <name>getDropTolerance</name>
      <anchorfile>classIfpack2_1_1ILUT.html</anchorfile>
      <anchor>ae59883b5b28640b0e75a220be3dbf689</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>global_size_t</type>
      <name>getGlobalNumEntries</name>
      <anchorfile>classIfpack2_1_1ILUT.html</anchorfile>
      <anchor>a0b2efa2d0d16fd281f558e319ea36d04</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>size_t</type>
      <name>getNodeNumEntries</name>
      <anchorfile>classIfpack2_1_1ILUT.html</anchorfile>
      <anchor>a9fd0a021425d85f1fa968f4b95dff2d2</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>description</name>
      <anchorfile>classIfpack2_1_1ILUT.html</anchorfile>
      <anchor>a7395afb18e5fbcaeff05bbd1cb18a18a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>describe</name>
      <anchorfile>classIfpack2_1_1ILUT.html</anchorfile>
      <anchor>aab9259c0394736a50bce98a2e2dcf5e3</anchor>
      <arglist>(Teuchos::FancyOStream &amp;out, const Teuchos::EVerbosityLevel verbLevel=Teuchos::Describable::verbLevel_default) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~Preconditioner</name>
      <anchorfile>classIfpack2_1_1Preconditioner.html</anchorfile>
      <anchor>a637973211128e0c09db53772df0f345d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual magnitudeType</type>
      <name>computeCondEst</name>
      <anchorfile>classIfpack2_1_1Preconditioner.html</anchorfile>
      <anchor>ab5b0a817cf6be83123192d38b5172131</anchor>
      <arglist>(CondestType CT=Ifpack2::Cheap, MatrixType::local_ordinal_typeMaxIters=1550, magnitudeType Tol=1e-9, const Teuchos::Ptr&lt; const Tpetra::RowMatrix&lt; MatrixType::scalar_type, MatrixType::local_ordinal_type, MatrixType::global_ordinal_type, MatrixType::node_type &gt; &gt; &amp;Matrix=Teuchos::null)=0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Ifpack2::LinearPartitioner</name>
    <filename>classIfpack2_1_1LinearPartitioner.html</filename>
    <templarg></templarg>
    <member kind="function">
      <type></type>
      <name>LinearPartitioner</name>
      <anchorfile>classIfpack2_1_1LinearPartitioner.html</anchorfile>
      <anchor>ac3b553a2858dfe1553b2889cf527405b</anchor>
      <arglist>(const Teuchos::RCP&lt; const Tpetra::RowGraph&lt; LocalOrdinal, GlobalOrdinal, Node &gt; &gt; &amp;Graph)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~LinearPartitioner</name>
      <anchorfile>classIfpack2_1_1LinearPartitioner.html</anchorfile>
      <anchor>a19c2f289c3cea31c10c248420f1dce6b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setPartitionParameters</name>
      <anchorfile>classIfpack2_1_1LinearPartitioner.html</anchorfile>
      <anchor>ab5fae2e5553f7e459a074483bc421782</anchor>
      <arglist>(Teuchos::ParameterList &amp;List)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>computePartitions</name>
      <anchorfile>classIfpack2_1_1LinearPartitioner.html</anchorfile>
      <anchor>af7bcf5c390a1327bb37dd7fcff17a8fa</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>OverlappingPartitioner</name>
      <anchorfile>classIfpack2_1_1OverlappingPartitioner.html</anchorfile>
      <anchor>a334836a2671e1be3cafc1e9683052ffd</anchor>
      <arglist>(const Teuchos::RCP&lt; const Tpetra::RowGraph&lt; LocalOrdinal, GlobalOrdinal, Node &gt; &gt; &amp;Graph)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~OverlappingPartitioner</name>
      <anchorfile>classIfpack2_1_1OverlappingPartitioner.html</anchorfile>
      <anchor>ac5e0da18722eecb1d9fa505539fb3842</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>size_t</type>
      <name>numLocalParts</name>
      <anchorfile>classIfpack2_1_1OverlappingPartitioner.html</anchorfile>
      <anchor>a60840695755260f421162b20b9af9aab</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>size_t</type>
      <name>overlappingLevel</name>
      <anchorfile>classIfpack2_1_1OverlappingPartitioner.html</anchorfile>
      <anchor>a3d0648eca1952d8dd40c3e188ae0e891</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>LocalOrdinal</type>
      <name>operator()</name>
      <anchorfile>classIfpack2_1_1OverlappingPartitioner.html</anchorfile>
      <anchor>acda4f221c24f34d4e9e67f0ede42eb43</anchor>
      <arglist>(LocalOrdinal MyRow) const </arglist>
    </member>
    <member kind="function">
      <type>LocalOrdinal</type>
      <name>operator()</name>
      <anchorfile>classIfpack2_1_1OverlappingPartitioner.html</anchorfile>
      <anchor>a4d2dee503c138838a0fabd1ad159631a</anchor>
      <arglist>(LocalOrdinal i, LocalOrdinal j) const </arglist>
    </member>
    <member kind="function">
      <type>size_t</type>
      <name>numRowsInPart</name>
      <anchorfile>classIfpack2_1_1OverlappingPartitioner.html</anchorfile>
      <anchor>ae57057080c396657954d10a572a79979</anchor>
      <arglist>(const LocalOrdinal Part) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>rowsInPart</name>
      <anchorfile>classIfpack2_1_1OverlappingPartitioner.html</anchorfile>
      <anchor>a8d4cc9c77a6a6adf9142cd141a0f68fd</anchor>
      <arglist>(const LocalOrdinal Part, Teuchos::ArrayRCP&lt; LocalOrdinal &gt; &amp;List) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual Teuchos::ArrayView&lt; const LocalOrdinal &gt;</type>
      <name>nonOverlappingPartition</name>
      <anchorfile>classIfpack2_1_1OverlappingPartitioner.html</anchorfile>
      <anchor>a542299b1afb0a59c494a0babeb0adc1b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>setParameters</name>
      <anchorfile>classIfpack2_1_1OverlappingPartitioner.html</anchorfile>
      <anchor>a32c5e4b2e53f51a2c358a6e0d9269339</anchor>
      <arglist>(Teuchos::ParameterList &amp;List)</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>setPartitionParameters</name>
      <anchorfile>classIfpack2_1_1OverlappingPartitioner.html</anchorfile>
      <anchor>a7643e330db263cfe8165ef3255b97906</anchor>
      <arglist>(Teuchos::ParameterList &amp;List)=0</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>compute</name>
      <anchorfile>classIfpack2_1_1OverlappingPartitioner.html</anchorfile>
      <anchor>a292e2c714b9a9c2c8ee2da4053f4e474</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>computePartitions</name>
      <anchorfile>classIfpack2_1_1OverlappingPartitioner.html</anchorfile>
      <anchor>aaf6d92acda727873712fadd93cf26cf7</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>computeOverlappingPartitions</name>
      <anchorfile>classIfpack2_1_1OverlappingPartitioner.html</anchorfile>
      <anchor>a6ea01595fc67a9a1c2644e8d3c864671</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>isComputed</name>
      <anchorfile>classIfpack2_1_1OverlappingPartitioner.html</anchorfile>
      <anchor>ac7464161ccd9ad3890bddf658a6e4443</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual std::ostream &amp;</type>
      <name>print</name>
      <anchorfile>classIfpack2_1_1OverlappingPartitioner.html</anchorfile>
      <anchor>a3e81290cff9ffeb1029a8fbc516a674b</anchor>
      <arglist>(std::ostream &amp;os) const </arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>description</name>
      <anchorfile>classIfpack2_1_1OverlappingPartitioner.html</anchorfile>
      <anchor>a29723a4a3296d0c93b3fe7be49201c37</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>describe</name>
      <anchorfile>classIfpack2_1_1OverlappingPartitioner.html</anchorfile>
      <anchor>aedcda4e2cea23b079ce3316faf7e239e</anchor>
      <arglist>(Teuchos::FancyOStream &amp;out, const Teuchos::EVerbosityLevel verbLevel=Teuchos::Describable::verbLevel_default) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~Partitioner</name>
      <anchorfile>classIfpack2_1_1Partitioner.html</anchorfile>
      <anchor>a614c5e31d061528be0473068af4bf1e8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual size_t</type>
      <name>numLocalParts</name>
      <anchorfile>classIfpack2_1_1Partitioner.html</anchorfile>
      <anchor>aceff8978dac976340b5bd5bb08f1755f</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual size_t</type>
      <name>overlappingLevel</name>
      <anchorfile>classIfpack2_1_1Partitioner.html</anchorfile>
      <anchor>aebc1582aae51285758aa99eeb18b76f2</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual LocalOrdinal</type>
      <name>operator()</name>
      <anchorfile>classIfpack2_1_1Partitioner.html</anchorfile>
      <anchor>a1af11e4a1e3bbe6f8fdca988d61d34e6</anchor>
      <arglist>(LocalOrdinal MyRow) const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual LocalOrdinal</type>
      <name>operator()</name>
      <anchorfile>classIfpack2_1_1Partitioner.html</anchorfile>
      <anchor>ae32a500ba8f9601cc0bd634b1202a8e3</anchor>
      <arglist>(LocalOrdinal i, LocalOrdinal j) const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual size_t</type>
      <name>numRowsInPart</name>
      <anchorfile>classIfpack2_1_1Partitioner.html</anchorfile>
      <anchor>af509c8da0bd9cd5a72ff70bebc118a5e</anchor>
      <arglist>(const LocalOrdinal Part) const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>rowsInPart</name>
      <anchorfile>classIfpack2_1_1Partitioner.html</anchorfile>
      <anchor>aa62d3e8370bfc6dbfc961016f9d5e3d4</anchor>
      <arglist>(const LocalOrdinal Part, Teuchos::ArrayRCP&lt; LocalOrdinal &gt; &amp;List) const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual Teuchos::ArrayView&lt; const LocalOrdinal &gt;</type>
      <name>nonOverlappingPartition</name>
      <anchorfile>classIfpack2_1_1Partitioner.html</anchorfile>
      <anchor>aa0bad87dbb1b8bc71a8281910c902cf2</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>setParameters</name>
      <anchorfile>classIfpack2_1_1Partitioner.html</anchorfile>
      <anchor>ab5bb772863b39fe101525e9b9052718b</anchor>
      <arglist>(Teuchos::ParameterList &amp;List)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>compute</name>
      <anchorfile>classIfpack2_1_1Partitioner.html</anchorfile>
      <anchor>a752d3b0bfdd6c86f9991c9c2a4d0d36e</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>isComputed</name>
      <anchorfile>classIfpack2_1_1Partitioner.html</anchorfile>
      <anchor>a6c06584d0426d4f955c194ab123c8d22</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual std::ostream &amp;</type>
      <name>print</name>
      <anchorfile>classIfpack2_1_1Partitioner.html</anchorfile>
      <anchor>a190ead9e48a9cae8b0b8bc900784a00a</anchor>
      <arglist>(std::ostream &amp;os) const =0</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>NumLocalParts_</name>
      <anchorfile>classIfpack2_1_1OverlappingPartitioner.html</anchorfile>
      <anchor>abeee580257d7fb2a502f41260d4cd142</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>Teuchos::Array&lt; LocalOrdinal &gt;</type>
      <name>Partition_</name>
      <anchorfile>classIfpack2_1_1OverlappingPartitioner.html</anchorfile>
      <anchor>a87b33943c9a4157ef1af5df57a1bc38e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>Teuchos::Array&lt; Teuchos::ArrayRCP&lt; LocalOrdinal &gt; &gt;</type>
      <name>Parts_</name>
      <anchorfile>classIfpack2_1_1OverlappingPartitioner.html</anchorfile>
      <anchor>afa7853fd03f58dd8786520783f020a25</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>Teuchos::RCP&lt; const Tpetra::RowGraph&lt; LocalOrdinal, GlobalOrdinal, Node &gt; &gt;</type>
      <name>Graph_</name>
      <anchorfile>classIfpack2_1_1OverlappingPartitioner.html</anchorfile>
      <anchor>ab39e1a33b0f4f33dacfcb6ae89dd8d39</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>size_t</type>
      <name>OverlappingLevel_</name>
      <anchorfile>classIfpack2_1_1OverlappingPartitioner.html</anchorfile>
      <anchor>a209c8a8b9b7f781a0498573678e951e9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>bool</type>
      <name>IsComputed_</name>
      <anchorfile>classIfpack2_1_1OverlappingPartitioner.html</anchorfile>
      <anchor>a8356dbdfed24bec196c046351b051d1f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>bool</type>
      <name>verbose_</name>
      <anchorfile>classIfpack2_1_1OverlappingPartitioner.html</anchorfile>
      <anchor>a1b0a2e41727176f8b34d60ecd63e2877</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Ifpack2::LocalFilter</name>
    <filename>classIfpack2_1_1LocalFilter.html</filename>
    <templarg>MatrixType</templarg>
    <member kind="function">
      <type></type>
      <name>LocalFilter</name>
      <anchorfile>classIfpack2_1_1LocalFilter.html</anchorfile>
      <anchor>a97c646e53f3cec496e32a72ae5424930</anchor>
      <arglist>(const Teuchos::RCP&lt; const Tpetra::RowMatrix&lt; Scalar, LocalOrdinal, GlobalOrdinal, Node &gt; &gt; &amp;Matrix)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~LocalFilter</name>
      <anchorfile>classIfpack2_1_1LocalFilter.html</anchorfile>
      <anchor>ab8727e06dc8002160390c88d94e0f811</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const Teuchos::RCP&lt; const Teuchos::Comm&lt; int &gt; &gt; &amp;</type>
      <name>getComm</name>
      <anchorfile>classIfpack2_1_1LocalFilter.html</anchorfile>
      <anchor>a6c1367f9d8e404f8cd2d8ed7314444d8</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual Teuchos::RCP&lt; Node &gt;</type>
      <name>getNode</name>
      <anchorfile>classIfpack2_1_1LocalFilter.html</anchorfile>
      <anchor>a720cf45c17de980027bbaaa0c89610c6</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const Teuchos::RCP&lt; const Tpetra::Map&lt; LocalOrdinal, GlobalOrdinal, Node &gt; &gt; &amp;</type>
      <name>getRowMap</name>
      <anchorfile>classIfpack2_1_1LocalFilter.html</anchorfile>
      <anchor>a2ddc7faaa191eb4352831ceeafc912a4</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const Teuchos::RCP&lt; const Tpetra::Map&lt; LocalOrdinal, GlobalOrdinal, Node &gt; &gt; &amp;</type>
      <name>getColMap</name>
      <anchorfile>classIfpack2_1_1LocalFilter.html</anchorfile>
      <anchor>a278283dd72ad146af57c15f100bde8f0</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const Teuchos::RCP&lt; const Tpetra::Map&lt; LocalOrdinal, GlobalOrdinal, Node &gt; &gt; &amp;</type>
      <name>getDomainMap</name>
      <anchorfile>classIfpack2_1_1LocalFilter.html</anchorfile>
      <anchor>ad7e1fdc61e4af956d412ce98bc16322a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const Teuchos::RCP&lt; const Tpetra::Map&lt; LocalOrdinal, GlobalOrdinal, Node &gt; &gt; &amp;</type>
      <name>getRangeMap</name>
      <anchorfile>classIfpack2_1_1LocalFilter.html</anchorfile>
      <anchor>a8413157d0147d408438e85baefb58e2f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual Teuchos::RCP&lt; const Tpetra::RowGraph&lt; LocalOrdinal, GlobalOrdinal, Node &gt; &gt;</type>
      <name>getGraph</name>
      <anchorfile>classIfpack2_1_1LocalFilter.html</anchorfile>
      <anchor>aa25b2cdc8b0a99f3a553b729ba38a99a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual global_size_t</type>
      <name>getGlobalNumRows</name>
      <anchorfile>classIfpack2_1_1LocalFilter.html</anchorfile>
      <anchor>a5796a699b07656d56850088833e5ca3d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual global_size_t</type>
      <name>getGlobalNumCols</name>
      <anchorfile>classIfpack2_1_1LocalFilter.html</anchorfile>
      <anchor>a198dbf7044020594206f6d07fbf067c2</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual size_t</type>
      <name>getNodeNumRows</name>
      <anchorfile>classIfpack2_1_1LocalFilter.html</anchorfile>
      <anchor>a0cc208b7f78749ad9add6c080498bb7f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual size_t</type>
      <name>getNodeNumCols</name>
      <anchorfile>classIfpack2_1_1LocalFilter.html</anchorfile>
      <anchor>ab38047b1c6e9d8369f5c76c5df60347b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual GlobalOrdinal</type>
      <name>getIndexBase</name>
      <anchorfile>classIfpack2_1_1LocalFilter.html</anchorfile>
      <anchor>abed5ebb2f0684953c0c3cc4837747424</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual global_size_t</type>
      <name>getGlobalNumEntries</name>
      <anchorfile>classIfpack2_1_1LocalFilter.html</anchorfile>
      <anchor>a7be180cff3ffe761c7bf5f6c39cd5099</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual size_t</type>
      <name>getNodeNumEntries</name>
      <anchorfile>classIfpack2_1_1LocalFilter.html</anchorfile>
      <anchor>a56a33de6da47ead261394b4cf2cd74bf</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual size_t</type>
      <name>getNumEntriesInGlobalRow</name>
      <anchorfile>classIfpack2_1_1LocalFilter.html</anchorfile>
      <anchor>aae4ed5011fe1380920306ee4c05f7ae9</anchor>
      <arglist>(GlobalOrdinal globalRow) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual size_t</type>
      <name>getNumEntriesInLocalRow</name>
      <anchorfile>classIfpack2_1_1LocalFilter.html</anchorfile>
      <anchor>ad11d451b883c12b7665111fe0a5b3fd3</anchor>
      <arglist>(LocalOrdinal localRow) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual global_size_t</type>
      <name>getGlobalNumDiags</name>
      <anchorfile>classIfpack2_1_1LocalFilter.html</anchorfile>
      <anchor>a78ce5b313d6fc0ce16906c5b092bba53</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual size_t</type>
      <name>getNodeNumDiags</name>
      <anchorfile>classIfpack2_1_1LocalFilter.html</anchorfile>
      <anchor>a8e354de5fcd183cbaf07b42357a1a966</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual size_t</type>
      <name>getGlobalMaxNumRowEntries</name>
      <anchorfile>classIfpack2_1_1LocalFilter.html</anchorfile>
      <anchor>aae5fcda257c6f4257bc11d7faa1b4d7e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual size_t</type>
      <name>getNodeMaxNumRowEntries</name>
      <anchorfile>classIfpack2_1_1LocalFilter.html</anchorfile>
      <anchor>af27d90c5c3716f7e0fce9685f9752118</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>hasColMap</name>
      <anchorfile>classIfpack2_1_1LocalFilter.html</anchorfile>
      <anchor>af8dec0fc4f66e15d8f4a7702dfc77b19</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>isLowerTriangular</name>
      <anchorfile>classIfpack2_1_1LocalFilter.html</anchorfile>
      <anchor>adf9c340c2a8139a693894a42254930c2</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>isUpperTriangular</name>
      <anchorfile>classIfpack2_1_1LocalFilter.html</anchorfile>
      <anchor>af53b8c8c57d8c789a65dc4c8454f343f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>isLocallyIndexed</name>
      <anchorfile>classIfpack2_1_1LocalFilter.html</anchorfile>
      <anchor>a0728cb0bac2ea2c440ad8b549959ab2d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>isGloballyIndexed</name>
      <anchorfile>classIfpack2_1_1LocalFilter.html</anchorfile>
      <anchor>aefa9d245737c633e4117a472289ff500</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>isFillComplete</name>
      <anchorfile>classIfpack2_1_1LocalFilter.html</anchorfile>
      <anchor>a08175fd2b3083933366e64fef74b967c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>getGlobalRowCopy</name>
      <anchorfile>classIfpack2_1_1LocalFilter.html</anchorfile>
      <anchor>a242abb403198898ad0eda2991dfa9a6d</anchor>
      <arglist>(GlobalOrdinal GlobalRow, const Teuchos::ArrayView&lt; GlobalOrdinal &gt; &amp;Indices, const Teuchos::ArrayView&lt; Scalar &gt; &amp;Values, size_t &amp;NumEntries) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>getLocalRowCopy</name>
      <anchorfile>classIfpack2_1_1LocalFilter.html</anchorfile>
      <anchor>a2035026c2ec257c0793fb52aa28c58d6</anchor>
      <arglist>(LocalOrdinal LocalRow, const Teuchos::ArrayView&lt; LocalOrdinal &gt; &amp;Indices, const Teuchos::ArrayView&lt; Scalar &gt; &amp;Values, size_t &amp;NumEntries) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>getGlobalRowView</name>
      <anchorfile>classIfpack2_1_1LocalFilter.html</anchorfile>
      <anchor>aa76b81ffef80cb5ffef2b0aae80dcbbf</anchor>
      <arglist>(GlobalOrdinal GlobalRow, Teuchos::ArrayView&lt; const GlobalOrdinal &gt; &amp;indices, Teuchos::ArrayView&lt; const Scalar &gt; &amp;values) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>getLocalRowView</name>
      <anchorfile>classIfpack2_1_1LocalFilter.html</anchorfile>
      <anchor>a8b195ec4529083a8e45dc6228fda51ee</anchor>
      <arglist>(LocalOrdinal LocalRow, Teuchos::ArrayView&lt; const LocalOrdinal &gt; &amp;indices, Teuchos::ArrayView&lt; const Scalar &gt; &amp;values) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>getLocalDiagCopy</name>
      <anchorfile>classIfpack2_1_1LocalFilter.html</anchorfile>
      <anchor>a4a8f1cfbc06644d9783529e8b8ac4f8d</anchor>
      <arglist>(Tpetra::Vector&lt; Scalar, LocalOrdinal, GlobalOrdinal, Node &gt; &amp;diag) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>leftScale</name>
      <anchorfile>classIfpack2_1_1LocalFilter.html</anchorfile>
      <anchor>afae08d5907ad45c47350d3ada28025a4</anchor>
      <arglist>(const Tpetra::Vector&lt; Scalar, LocalOrdinal, GlobalOrdinal, Node &gt; &amp;x)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>rightScale</name>
      <anchorfile>classIfpack2_1_1LocalFilter.html</anchorfile>
      <anchor>a78bdfb5cad39c1adcb36fbe2fd1cca88</anchor>
      <arglist>(const Tpetra::Vector&lt; Scalar, LocalOrdinal, GlobalOrdinal, Node &gt; &amp;x)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual Teuchos::ScalarTraits&lt; Scalar &gt;::magnitudeType</type>
      <name>getFrobeniusNorm</name>
      <anchorfile>classIfpack2_1_1LocalFilter.html</anchorfile>
      <anchor>a9fe0df730f2af3a5a0d205767497040f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>apply</name>
      <anchorfile>classIfpack2_1_1LocalFilter.html</anchorfile>
      <anchor>a1c0514f2016734575823b952d12f95a5</anchor>
      <arglist>(const Tpetra::MultiVector&lt; Scalar, LocalOrdinal, GlobalOrdinal, Node &gt; &amp;X, Tpetra::MultiVector&lt; Scalar, LocalOrdinal, GlobalOrdinal, Node &gt; &amp;Y, Teuchos::ETransp mode=Teuchos::NO_TRANS, Scalar alpha=Teuchos::ScalarTraits&lt; Scalar &gt;::one(), Scalar beta=Teuchos::ScalarTraits&lt; Scalar &gt;::zero()) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>hasTransposeApply</name>
      <anchorfile>classIfpack2_1_1LocalFilter.html</anchorfile>
      <anchor>ab1e6297ae388fbff99126966bcb516d9</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual TPETRA_DEPRECATED void</type>
      <name>getGlobalRowView</name>
      <anchorfile>classIfpack2_1_1LocalFilter.html</anchorfile>
      <anchor>a83175f8ccf8660e9f8f7eeec5daf42f5</anchor>
      <arglist>(GlobalOrdinal GlobalRow, Teuchos::ArrayRCP&lt; const GlobalOrdinal &gt; &amp;indices, Teuchos::ArrayRCP&lt; const Scalar &gt; &amp;values) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual TPETRA_DEPRECATED void</type>
      <name>getLocalRowView</name>
      <anchorfile>classIfpack2_1_1LocalFilter.html</anchorfile>
      <anchor>a713d2ffe49730a98b765577fd1496388</anchor>
      <arglist>(LocalOrdinal LocalRow, Teuchos::ArrayRCP&lt; const LocalOrdinal &gt; &amp;indices, Teuchos::ArrayRCP&lt; const Scalar &gt; &amp;values) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Ifpack2::OverlapGraph</name>
    <filename>classIfpack2_1_1OverlapGraph.html</filename>
    <templarg>LocalOrdinal</templarg>
    <templarg>GlobalOrdinal</templarg>
    <templarg>Node</templarg>
    <member kind="function">
      <type></type>
      <name>OverlapGraph</name>
      <anchorfile>classIfpack2_1_1OverlapGraph.html</anchorfile>
      <anchor>ad0f3119aa0c4048caf41c73c27b3a8d7</anchor>
      <arglist>(const Teuchos::RCP&lt; const Tpetra::CrsGraph&lt; LocalOrdinal, GlobalOrdinal, Node &gt; &gt; &amp;UserMatrixGraph_in, int OverlapLevel_in)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>OverlapGraph</name>
      <anchorfile>classIfpack2_1_1OverlapGraph.html</anchorfile>
      <anchor>a0712ee59b818a1e0dab0e957a736c9cf</anchor>
      <arglist>(const OverlapGraph&lt; LocalOrdinal, GlobalOrdinal, Node &gt; &amp;Source)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~OverlapGraph</name>
      <anchorfile>classIfpack2_1_1OverlapGraph.html</anchorfile>
      <anchor>a6836d8b4db66a0acf3aea93e49b8bfa5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetParameters</name>
      <anchorfile>classIfpack2_1_1OverlapGraph.html</anchorfile>
      <anchor>aa5dd35794d2e6029e9d51fd747b14a93</anchor>
      <arglist>(const Teuchos::ParameterList &amp;parameterlist, bool cerr_warning_if_unused=false)</arglist>
    </member>
    <member kind="function">
      <type>const Tpetra::CrsGraph&lt; LocalOrdinal, GlobalOrdinal, Node &gt; &amp;</type>
      <name>getOverlapGraph</name>
      <anchorfile>classIfpack2_1_1OverlapGraph.html</anchorfile>
      <anchor>af34a6dcba88c88deefa8b26a3074af10</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Tpetra::Map&lt; LocalOrdinal, GlobalOrdinal, Node &gt; &amp;</type>
      <name>getOverlapRowMap</name>
      <anchorfile>classIfpack2_1_1OverlapGraph.html</anchorfile>
      <anchor>a0f5381ddc46aef0a662e5e634add8d9e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Tpetra::Import&lt; LocalOrdinal, GlobalOrdinal, Node &gt; &amp;</type>
      <name>getOverlapImporter</name>
      <anchorfile>classIfpack2_1_1OverlapGraph.html</anchorfile>
      <anchor>a88d0fcbd5c340d252072100bc75406cc</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>OverlapLevel</name>
      <anchorfile>classIfpack2_1_1OverlapGraph.html</anchorfile>
      <anchor>af6a572fd0b3c541df6adf3a918c62456</anchor>
      <arglist>() const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Ifpack2::Partitioner</name>
    <filename>classIfpack2_1_1Partitioner.html</filename>
    <templarg></templarg>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~Partitioner</name>
      <anchorfile>classIfpack2_1_1Partitioner.html</anchorfile>
      <anchor>a614c5e31d061528be0473068af4bf1e8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual size_t</type>
      <name>numLocalParts</name>
      <anchorfile>classIfpack2_1_1Partitioner.html</anchorfile>
      <anchor>aceff8978dac976340b5bd5bb08f1755f</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual size_t</type>
      <name>overlappingLevel</name>
      <anchorfile>classIfpack2_1_1Partitioner.html</anchorfile>
      <anchor>aebc1582aae51285758aa99eeb18b76f2</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual LocalOrdinal</type>
      <name>operator()</name>
      <anchorfile>classIfpack2_1_1Partitioner.html</anchorfile>
      <anchor>a1af11e4a1e3bbe6f8fdca988d61d34e6</anchor>
      <arglist>(LocalOrdinal MyRow) const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual LocalOrdinal</type>
      <name>operator()</name>
      <anchorfile>classIfpack2_1_1Partitioner.html</anchorfile>
      <anchor>ae32a500ba8f9601cc0bd634b1202a8e3</anchor>
      <arglist>(LocalOrdinal i, LocalOrdinal j) const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual size_t</type>
      <name>numRowsInPart</name>
      <anchorfile>classIfpack2_1_1Partitioner.html</anchorfile>
      <anchor>af509c8da0bd9cd5a72ff70bebc118a5e</anchor>
      <arglist>(const LocalOrdinal Part) const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>rowsInPart</name>
      <anchorfile>classIfpack2_1_1Partitioner.html</anchorfile>
      <anchor>aa62d3e8370bfc6dbfc961016f9d5e3d4</anchor>
      <arglist>(const LocalOrdinal Part, Teuchos::ArrayRCP&lt; LocalOrdinal &gt; &amp;List) const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual Teuchos::ArrayView&lt; const LocalOrdinal &gt;</type>
      <name>nonOverlappingPartition</name>
      <anchorfile>classIfpack2_1_1Partitioner.html</anchorfile>
      <anchor>aa0bad87dbb1b8bc71a8281910c902cf2</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>setParameters</name>
      <anchorfile>classIfpack2_1_1Partitioner.html</anchorfile>
      <anchor>ab5bb772863b39fe101525e9b9052718b</anchor>
      <arglist>(Teuchos::ParameterList &amp;List)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>compute</name>
      <anchorfile>classIfpack2_1_1Partitioner.html</anchorfile>
      <anchor>a752d3b0bfdd6c86f9991c9c2a4d0d36e</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>isComputed</name>
      <anchorfile>classIfpack2_1_1Partitioner.html</anchorfile>
      <anchor>a6c06584d0426d4f955c194ab123c8d22</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual std::ostream &amp;</type>
      <name>print</name>
      <anchorfile>classIfpack2_1_1Partitioner.html</anchorfile>
      <anchor>a190ead9e48a9cae8b0b8bc900784a00a</anchor>
      <arglist>(std::ostream &amp;os) const =0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Ifpack2::Preconditioner</name>
    <filename>classIfpack2_1_1Preconditioner.html</filename>
    <templarg>Scalar</templarg>
    <templarg>LocalOrdinal</templarg>
    <templarg>GlobalOrdinal</templarg>
    <templarg>Node</templarg>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~Preconditioner</name>
      <anchorfile>classIfpack2_1_1Preconditioner.html</anchorfile>
      <anchor>a637973211128e0c09db53772df0f345d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>setParameters</name>
      <anchorfile>classIfpack2_1_1Preconditioner.html</anchorfile>
      <anchor>a60340992fc1b9eac82ef35333bee6efd</anchor>
      <arglist>(const Teuchos::ParameterList &amp;List)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>initialize</name>
      <anchorfile>classIfpack2_1_1Preconditioner.html</anchorfile>
      <anchor>ad3aefd6f16e8ef4cddb696cd23f160b0</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>isInitialized</name>
      <anchorfile>classIfpack2_1_1Preconditioner.html</anchorfile>
      <anchor>a180c876ccf7af87f10a1c1d08ba2dc01</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>compute</name>
      <anchorfile>classIfpack2_1_1Preconditioner.html</anchorfile>
      <anchor>a23954dd69f62b56455a9c0988bbe9e67</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>isComputed</name>
      <anchorfile>classIfpack2_1_1Preconditioner.html</anchorfile>
      <anchor>abb5af77756a7488ab636dbd97483ca66</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual magnitudeType</type>
      <name>computeCondEst</name>
      <anchorfile>classIfpack2_1_1Preconditioner.html</anchorfile>
      <anchor>ab5b0a817cf6be83123192d38b5172131</anchor>
      <arglist>(CondestType CT=Ifpack2::Cheap, LocalOrdinal MaxIters=1550, magnitudeType Tol=1e-9, const Teuchos::Ptr&lt; const Tpetra::RowMatrix&lt; Scalar, LocalOrdinal, GlobalOrdinal, Node &gt; &gt; &amp;Matrix=Teuchos::null)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual magnitudeType</type>
      <name>getCondEst</name>
      <anchorfile>classIfpack2_1_1Preconditioner.html</anchorfile>
      <anchor>a0d7fee88d22a0542cb9a6a6bbd96ce2d</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual Teuchos::RCP&lt; const Tpetra::RowMatrix&lt; Scalar, LocalOrdinal, GlobalOrdinal, Node &gt; &gt;</type>
      <name>getMatrix</name>
      <anchorfile>classIfpack2_1_1Preconditioner.html</anchorfile>
      <anchor>a6958e5d60d7783f96edfbf8f3d06bbc2</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>getNumInitialize</name>
      <anchorfile>classIfpack2_1_1Preconditioner.html</anchorfile>
      <anchor>afe6c77c5ab6da065f8dbade353e8535a</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>getNumCompute</name>
      <anchorfile>classIfpack2_1_1Preconditioner.html</anchorfile>
      <anchor>a286b18ee0769ecc8bf992dffdc442791</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>getNumApply</name>
      <anchorfile>classIfpack2_1_1Preconditioner.html</anchorfile>
      <anchor>a565e6c00bf14873ae7b23187c9978078</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual double</type>
      <name>getInitializeTime</name>
      <anchorfile>classIfpack2_1_1Preconditioner.html</anchorfile>
      <anchor>aeb91a16f5544ad4efaf756b1d2a8b39d</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual double</type>
      <name>getComputeTime</name>
      <anchorfile>classIfpack2_1_1Preconditioner.html</anchorfile>
      <anchor>a111d9bd4e28c0633696f271955ddcb4c</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual double</type>
      <name>getApplyTime</name>
      <anchorfile>classIfpack2_1_1Preconditioner.html</anchorfile>
      <anchor>a57c2d00799de050cd2a5a75ce80f48b9</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual const Teuchos::RCP&lt; const Tpetra::Map&lt; LocalOrdinal, GlobalOrdinal, Node &gt; &gt; &amp;</type>
      <name>getDomainMap</name>
      <anchorfile>classIfpack2_1_1Preconditioner.html</anchorfile>
      <anchor>abfdee2ca1515635cd8000e3a97756ac9</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual const Teuchos::RCP&lt; const Tpetra::Map&lt; LocalOrdinal, GlobalOrdinal, Node &gt; &gt; &amp;</type>
      <name>getRangeMap</name>
      <anchorfile>classIfpack2_1_1Preconditioner.html</anchorfile>
      <anchor>af576e27ef1049c43eb8192cd27a45939</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>apply</name>
      <anchorfile>classIfpack2_1_1Preconditioner.html</anchorfile>
      <anchor>a606c3f8155f67f2867fac3a7c44bd5df</anchor>
      <arglist>(const Tpetra::MultiVector&lt; Scalar, LocalOrdinal, GlobalOrdinal, Node &gt; &amp;X, Tpetra::MultiVector&lt; Scalar, LocalOrdinal, GlobalOrdinal, Node &gt; &amp;Y, Teuchos::ETransp mode=Teuchos::NO_TRANS, Scalar alpha=Teuchos::ScalarTraits&lt; Scalar &gt;::one(), Scalar beta=Teuchos::ScalarTraits&lt; Scalar &gt;::zero()) const =0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Ifpack2::Relaxation</name>
    <filename>classIfpack2_1_1Relaxation.html</filename>
    <templarg>MatrixType</templarg>
    <base virtualness="virtual">Preconditioner&lt; MatrixType::scalar_type, MatrixType::local_ordinal_type, MatrixType::global_ordinal_type, MatrixType::node_type &gt;</base>
    <member kind="function">
      <type></type>
      <name>Relaxation</name>
      <anchorfile>classIfpack2_1_1Relaxation.html</anchorfile>
      <anchor>a1121305a7281f86367680abeb3e5cf81</anchor>
      <arglist>(const Teuchos::RCP&lt; const Tpetra::RowMatrix&lt; Scalar, LocalOrdinal, GlobalOrdinal, Node &gt; &gt; &amp;Matrix)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~Relaxation</name>
      <anchorfile>classIfpack2_1_1Relaxation.html</anchorfile>
      <anchor>a09f3674028b47a5540c3f0bc872c82e1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setParameters</name>
      <anchorfile>classIfpack2_1_1Relaxation.html</anchorfile>
      <anchor>a08f8bb5eda400d0912efa33c552b5ce4</anchor>
      <arglist>(const Teuchos::ParameterList &amp;params)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initialize</name>
      <anchorfile>classIfpack2_1_1Relaxation.html</anchorfile>
      <anchor>a53fd53a77642276aecfaa51f12f3191b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isInitialized</name>
      <anchorfile>classIfpack2_1_1Relaxation.html</anchorfile>
      <anchor>a23b69067f66decd021e61c0129f91185</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>compute</name>
      <anchorfile>classIfpack2_1_1Relaxation.html</anchorfile>
      <anchor>a512bc4a35a2933356c27833b5498303c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isComputed</name>
      <anchorfile>classIfpack2_1_1Relaxation.html</anchorfile>
      <anchor>a72ba54c7cadfd510bf35a9562b5b5ee4</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>apply</name>
      <anchorfile>classIfpack2_1_1Relaxation.html</anchorfile>
      <anchor>a34c531ed30e5d7dbe5196be927c910d2</anchor>
      <arglist>(const Tpetra::MultiVector&lt; Scalar, LocalOrdinal, GlobalOrdinal, Node &gt; &amp;X, Tpetra::MultiVector&lt; Scalar, LocalOrdinal, GlobalOrdinal, Node &gt; &amp;Y, Teuchos::ETransp mode=Teuchos::NO_TRANS, Scalar alpha=Teuchos::ScalarTraits&lt; Scalar &gt;::one(), Scalar beta=Teuchos::ScalarTraits&lt; Scalar &gt;::zero()) const </arglist>
    </member>
    <member kind="function">
      <type>const Teuchos::RCP&lt; const Tpetra::Map&lt; LocalOrdinal, GlobalOrdinal, Node &gt; &gt; &amp;</type>
      <name>getDomainMap</name>
      <anchorfile>classIfpack2_1_1Relaxation.html</anchorfile>
      <anchor>a9762a172e36e7fe9716265a3d5ec59b2</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Teuchos::RCP&lt; const Tpetra::Map&lt; LocalOrdinal, GlobalOrdinal, Node &gt; &gt; &amp;</type>
      <name>getRangeMap</name>
      <anchorfile>classIfpack2_1_1Relaxation.html</anchorfile>
      <anchor>a35b7e15d250a0f2c9de8867b2584a3af</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>hasTransposeApply</name>
      <anchorfile>classIfpack2_1_1Relaxation.html</anchorfile>
      <anchor>ae7246407f66582f460e08f945b2bea62</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>applyMat</name>
      <anchorfile>classIfpack2_1_1Relaxation.html</anchorfile>
      <anchor>ada9606410257997189209dba7b416e62</anchor>
      <arglist>(const Tpetra::MultiVector&lt; Scalar, LocalOrdinal, GlobalOrdinal, Node &gt; &amp;X, Tpetra::MultiVector&lt; Scalar, LocalOrdinal, GlobalOrdinal, Node &gt; &amp;Y, Teuchos::ETransp mode=Teuchos::NO_TRANS) const </arglist>
    </member>
    <member kind="function">
      <type>magnitudeType</type>
      <name>computeCondEst</name>
      <anchorfile>classIfpack2_1_1Relaxation.html</anchorfile>
      <anchor>a07ca86a6afbf3ae51c1db61d8e42fd07</anchor>
      <arglist>(CondestType CT=Cheap, LocalOrdinal MaxIters=1550, magnitudeType Tol=1e-9, const Teuchos::Ptr&lt; const Tpetra::RowMatrix&lt; Scalar, LocalOrdinal, GlobalOrdinal, Node &gt; &gt; &amp;matrix=Teuchos::null)</arglist>
    </member>
    <member kind="function">
      <type>magnitudeType</type>
      <name>getCondEst</name>
      <anchorfile>classIfpack2_1_1Relaxation.html</anchorfile>
      <anchor>af67af8ecf467bcd9841bcbdc85078adf</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Teuchos::RCP&lt; const Teuchos::Comm&lt; int &gt; &gt; &amp;</type>
      <name>getComm</name>
      <anchorfile>classIfpack2_1_1Relaxation.html</anchorfile>
      <anchor>a4d2f82bc7b3a40726aa92f37702bbbc0</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Tpetra::RowMatrix&lt; Scalar, LocalOrdinal, GlobalOrdinal, Node &gt; &gt;</type>
      <name>getMatrix</name>
      <anchorfile>classIfpack2_1_1Relaxation.html</anchorfile>
      <anchor>a2fb590442526619340026843f5449024</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>getComputeFlops</name>
      <anchorfile>classIfpack2_1_1Relaxation.html</anchorfile>
      <anchor>a7102e3c575f1ec6a284c966aa9d705f3</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>getApplyFlops</name>
      <anchorfile>classIfpack2_1_1Relaxation.html</anchorfile>
      <anchor>a09c8106bcf6b4c74deeaf93289198a93</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getNumInitialize</name>
      <anchorfile>classIfpack2_1_1Relaxation.html</anchorfile>
      <anchor>ae36737f2eff9d5a69ef78346c3b89069</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getNumCompute</name>
      <anchorfile>classIfpack2_1_1Relaxation.html</anchorfile>
      <anchor>a1d8db3e7ac074dcb25ec3fda8379abee</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getNumApply</name>
      <anchorfile>classIfpack2_1_1Relaxation.html</anchorfile>
      <anchor>aa88266c35f22ddaefa8be9e5eb15b704</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>getInitializeTime</name>
      <anchorfile>classIfpack2_1_1Relaxation.html</anchorfile>
      <anchor>aaba0a09a43b7d5d756810797f04e97dd</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>getComputeTime</name>
      <anchorfile>classIfpack2_1_1Relaxation.html</anchorfile>
      <anchor>a4c759a30a9fde1b023301b058204a7bb</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>getApplyTime</name>
      <anchorfile>classIfpack2_1_1Relaxation.html</anchorfile>
      <anchor>a1114647ebfdf669fc742f240b996fc9f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>description</name>
      <anchorfile>classIfpack2_1_1Relaxation.html</anchorfile>
      <anchor>af7af751fe400b69667d296af2004af98</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>describe</name>
      <anchorfile>classIfpack2_1_1Relaxation.html</anchorfile>
      <anchor>af99b59165832348bc054461da235f551</anchor>
      <arglist>(Teuchos::FancyOStream &amp;out, const Teuchos::EVerbosityLevel verbLevel=Teuchos::Describable::verbLevel_default) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~Preconditioner</name>
      <anchorfile>classIfpack2_1_1Preconditioner.html</anchorfile>
      <anchor>a637973211128e0c09db53772df0f345d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual magnitudeType</type>
      <name>computeCondEst</name>
      <anchorfile>classIfpack2_1_1Preconditioner.html</anchorfile>
      <anchor>ab5b0a817cf6be83123192d38b5172131</anchor>
      <arglist>(CondestType CT=Ifpack2::Cheap, MatrixType::local_ordinal_typeMaxIters=1550, magnitudeType Tol=1e-9, const Teuchos::Ptr&lt; const Tpetra::RowMatrix&lt; MatrixType::scalar_type, MatrixType::local_ordinal_type, MatrixType::global_ordinal_type, MatrixType::node_type &gt; &gt; &amp;Matrix=Teuchos::null)=0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Ifpack2::RILUK</name>
    <filename>classIfpack2_1_1RILUK.html</filename>
    <templarg>MatrixType</templarg>
    <base virtualness="virtual">Preconditioner&lt; MatrixType::scalar_type, MatrixType::local_ordinal_type, MatrixType::global_ordinal_type, MatrixType::node_type &gt;</base>
    <member kind="function">
      <type></type>
      <name>RILUK</name>
      <anchorfile>classIfpack2_1_1RILUK.html</anchorfile>
      <anchor>a52dfbe4ee58d1744410d6b3b03fac82e</anchor>
      <arglist>(const Teuchos::RCP&lt; const MatrixType &gt; &amp;A_in)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~RILUK</name>
      <anchorfile>classIfpack2_1_1RILUK.html</anchorfile>
      <anchor>a14bf0fe45360dd7ffad930f7e9ff7e81</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetRelaxValue</name>
      <anchorfile>classIfpack2_1_1RILUK.html</anchorfile>
      <anchor>aeb76a1f5b2430d2a1f6b98eabd51ac22</anchor>
      <arglist>(magnitudeType RelaxValue)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetAbsoluteThreshold</name>
      <anchorfile>classIfpack2_1_1RILUK.html</anchorfile>
      <anchor>a60db391843de4b75382e4e1144ddc5f6</anchor>
      <arglist>(magnitudeType Athresh)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetRelativeThreshold</name>
      <anchorfile>classIfpack2_1_1RILUK.html</anchorfile>
      <anchor>a059befd92e5fe2782260e21560c292ac</anchor>
      <arglist>(magnitudeType Rthresh)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetOverlapMode</name>
      <anchorfile>classIfpack2_1_1RILUK.html</anchorfile>
      <anchor>a26957d61e8d96ffdc8b3421881eaf9fc</anchor>
      <arglist>(Tpetra::CombineMode OverlapMode)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setParameters</name>
      <anchorfile>classIfpack2_1_1RILUK.html</anchorfile>
      <anchor>a434b3c90b3166c98795c8130d68fc5a0</anchor>
      <arglist>(const Teuchos::ParameterList &amp;parameterlist)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initialize</name>
      <anchorfile>classIfpack2_1_1RILUK.html</anchorfile>
      <anchor>a06f4f95081fcbf5eb8f5a5d18d0c717b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isInitialized</name>
      <anchorfile>classIfpack2_1_1RILUK.html</anchorfile>
      <anchor>ad653905d6baa236d1f7571fae5235e63</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getNumInitialize</name>
      <anchorfile>classIfpack2_1_1RILUK.html</anchorfile>
      <anchor>a9fab90c9ad775e074adf65ef5cc43c50</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>compute</name>
      <anchorfile>classIfpack2_1_1RILUK.html</anchorfile>
      <anchor>ad6975338fab389e7c2a9bede6162b85a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isComputed</name>
      <anchorfile>classIfpack2_1_1RILUK.html</anchorfile>
      <anchor>a4d71681491614d7fbb2509b63821f649</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getNumCompute</name>
      <anchorfile>classIfpack2_1_1RILUK.html</anchorfile>
      <anchor>a325c0a42b3187406fce2cdf01cd2646d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getNumApply</name>
      <anchorfile>classIfpack2_1_1RILUK.html</anchorfile>
      <anchor>ac4f84e62c16a7c72c89c8eb8aefe8bb3</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>getInitializeTime</name>
      <anchorfile>classIfpack2_1_1RILUK.html</anchorfile>
      <anchor>a12d7077c2ecca844edb9638fe4f98903</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>getComputeTime</name>
      <anchorfile>classIfpack2_1_1RILUK.html</anchorfile>
      <anchor>ad1c9a60a8e63d1a03b6eda1c408c5aed</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>getApplyTime</name>
      <anchorfile>classIfpack2_1_1RILUK.html</anchorfile>
      <anchor>a576e6f24020cfdd8d446113528f2b1e2</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>apply</name>
      <anchorfile>classIfpack2_1_1RILUK.html</anchorfile>
      <anchor>abf07f1b14c3aaae3e301545bc1fca2e0</anchor>
      <arglist>(const Tpetra::MultiVector&lt; Scalar, LocalOrdinal, GlobalOrdinal, Node &gt; &amp;X, Tpetra::MultiVector&lt; Scalar, LocalOrdinal, GlobalOrdinal, Node &gt; &amp;Y, Teuchos::ETransp mode=Teuchos::NO_TRANS, Scalar alpha=Teuchos::ScalarTraits&lt; Scalar &gt;::one(), Scalar beta=Teuchos::ScalarTraits&lt; Scalar &gt;::zero()) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Multiply</name>
      <anchorfile>classIfpack2_1_1RILUK.html</anchorfile>
      <anchor>af0a77f4bb8662c1cddf0b2077b72bb3b</anchor>
      <arglist>(const Tpetra::MultiVector&lt; Scalar, LocalOrdinal, GlobalOrdinal, Node &gt; &amp;X, Tpetra::MultiVector&lt; Scalar, LocalOrdinal, GlobalOrdinal, Node &gt; &amp;Y, Teuchos::ETransp mode=Teuchos::NO_TRANS) const </arglist>
    </member>
    <member kind="function">
      <type>magnitudeType</type>
      <name>computeCondEst</name>
      <anchorfile>classIfpack2_1_1RILUK.html</anchorfile>
      <anchor>a68b3a89795523f968a012eef82b1f519</anchor>
      <arglist>(Teuchos::ETransp mode) const </arglist>
    </member>
    <member kind="function">
      <type>magnitudeType</type>
      <name>getCondEst</name>
      <anchorfile>classIfpack2_1_1RILUK.html</anchorfile>
      <anchor>a6268e4d7f11bb44289cc28b7cae5ea85</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Tpetra::RowMatrix&lt; Scalar, LocalOrdinal, GlobalOrdinal, Node &gt; &gt;</type>
      <name>getMatrix</name>
      <anchorfile>classIfpack2_1_1RILUK.html</anchorfile>
      <anchor>a20af4b37c0e67fe57228b26ffe8b0612</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>magnitudeType</type>
      <name>GetRelaxValue</name>
      <anchorfile>classIfpack2_1_1RILUK.html</anchorfile>
      <anchor>ac95ab818e223278932e76b21fa6d44af</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>magnitudeType</type>
      <name>getAbsoluteThreshold</name>
      <anchorfile>classIfpack2_1_1RILUK.html</anchorfile>
      <anchor>ad54edb1dc5c8ac5602d7a523bb1cdf1a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>magnitudeType</type>
      <name>getRelativeThreshold</name>
      <anchorfile>classIfpack2_1_1RILUK.html</anchorfile>
      <anchor>a1410b32d54dcb4d3e25812305c9d4f90</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Tpetra::CombineMode</type>
      <name>getOverlapMode</name>
      <anchorfile>classIfpack2_1_1RILUK.html</anchorfile>
      <anchor>a44ca1a51f7aade5b91c06165332b65a8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getGlobalNumEntries</name>
      <anchorfile>classIfpack2_1_1RILUK.html</anchorfile>
      <anchor>ad3098ec67e8219f5d69d02dae01a35ce</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Teuchos::RCP&lt; Ifpack2::IlukGraph&lt; LocalOrdinal, GlobalOrdinal, Node &gt; &gt; &amp;</type>
      <name>getGraph</name>
      <anchorfile>classIfpack2_1_1RILUK.html</anchorfile>
      <anchor>a7c327d8ba7e486d4771c648bb755a032</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const MatrixType &amp;</type>
      <name>getL</name>
      <anchorfile>classIfpack2_1_1RILUK.html</anchorfile>
      <anchor>a14454e10bd31847190603c7d94317fd2</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Tpetra::Vector&lt; Scalar, LocalOrdinal, GlobalOrdinal, Node &gt; &amp;</type>
      <name>getD</name>
      <anchorfile>classIfpack2_1_1RILUK.html</anchorfile>
      <anchor>a223214706ae32faa7f4e861f79d3d095</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const MatrixType &amp;</type>
      <name>getU</name>
      <anchorfile>classIfpack2_1_1RILUK.html</anchorfile>
      <anchor>a981a6c565fd255c5a1c6743505b34047</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Teuchos::RCP&lt; const Tpetra::Map&lt; LocalOrdinal, GlobalOrdinal, Node &gt; &gt; &amp;</type>
      <name>getDomainMap</name>
      <anchorfile>classIfpack2_1_1RILUK.html</anchorfile>
      <anchor>af4bbc76e820d4c6d68be17231ae32bee</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Teuchos::RCP&lt; const Tpetra::Map&lt; LocalOrdinal, GlobalOrdinal, Node &gt; &gt; &amp;</type>
      <name>getRangeMap</name>
      <anchorfile>classIfpack2_1_1RILUK.html</anchorfile>
      <anchor>a620038853f28c32f4f5c46d9b21e3fc6</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~Preconditioner</name>
      <anchorfile>classIfpack2_1_1Preconditioner.html</anchorfile>
      <anchor>a637973211128e0c09db53772df0f345d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual magnitudeType</type>
      <name>computeCondEst</name>
      <anchorfile>classIfpack2_1_1Preconditioner.html</anchorfile>
      <anchor>ab5b0a817cf6be83123192d38b5172131</anchor>
      <arglist>(CondestType CT=Ifpack2::Cheap, MatrixType::local_ordinal_typeMaxIters=1550, magnitudeType Tol=1e-9, const Teuchos::Ptr&lt; const Tpetra::RowMatrix&lt; MatrixType::scalar_type, MatrixType::local_ordinal_type, MatrixType::global_ordinal_type, MatrixType::node_type &gt; &gt; &amp;Matrix=Teuchos::null)=0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Ifpack2::SingletonFilter</name>
    <filename>classIfpack2_1_1SingletonFilter.html</filename>
    <templarg></templarg>
    <member kind="function">
      <type></type>
      <name>SingletonFilter</name>
      <anchorfile>classIfpack2_1_1SingletonFilter.html</anchorfile>
      <anchor>a0148f32207c7aa2c05901c0c37d871bc</anchor>
      <arglist>(const Teuchos::RCP&lt; const Tpetra::RowMatrix&lt; Scalar, LocalOrdinal, GlobalOrdinal, Node &gt; &gt; &amp;Matrix)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~SingletonFilter</name>
      <anchorfile>classIfpack2_1_1SingletonFilter.html</anchorfile>
      <anchor>ac8c1106bda179e753597bb07c4ad77b1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const Teuchos::RCP&lt; const Teuchos::Comm&lt; int &gt; &gt; &amp;</type>
      <name>getComm</name>
      <anchorfile>classIfpack2_1_1SingletonFilter.html</anchorfile>
      <anchor>a938e01efad1ab1fc017eb9b89762e68e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual Teuchos::RCP&lt; Node &gt;</type>
      <name>getNode</name>
      <anchorfile>classIfpack2_1_1SingletonFilter.html</anchorfile>
      <anchor>a2b60cd1f39d2dc84f4102ddc827bb118</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const Teuchos::RCP&lt; const Tpetra::Map&lt; LocalOrdinal, GlobalOrdinal, Node &gt; &gt; &amp;</type>
      <name>getRowMap</name>
      <anchorfile>classIfpack2_1_1SingletonFilter.html</anchorfile>
      <anchor>a60649fda8177ae4e78b9eae2b10d9b47</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const Teuchos::RCP&lt; const Tpetra::Map&lt; LocalOrdinal, GlobalOrdinal, Node &gt; &gt; &amp;</type>
      <name>getColMap</name>
      <anchorfile>classIfpack2_1_1SingletonFilter.html</anchorfile>
      <anchor>ac9c06d35ad1d0037767ec6a1dc901e58</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const Teuchos::RCP&lt; const Tpetra::Map&lt; LocalOrdinal, GlobalOrdinal, Node &gt; &gt; &amp;</type>
      <name>getDomainMap</name>
      <anchorfile>classIfpack2_1_1SingletonFilter.html</anchorfile>
      <anchor>af237ef1f9f9dcf04cd8b4f77b00f270b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const Teuchos::RCP&lt; const Tpetra::Map&lt; LocalOrdinal, GlobalOrdinal, Node &gt; &gt; &amp;</type>
      <name>getRangeMap</name>
      <anchorfile>classIfpack2_1_1SingletonFilter.html</anchorfile>
      <anchor>a429790dec1283cb47487e5ae2be5f87e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual Teuchos::RCP&lt; const Tpetra::RowGraph&lt; LocalOrdinal, GlobalOrdinal, Node &gt; &gt;</type>
      <name>getGraph</name>
      <anchorfile>classIfpack2_1_1SingletonFilter.html</anchorfile>
      <anchor>ae49b950e0dcc026b95114b2965719101</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual global_size_t</type>
      <name>getGlobalNumRows</name>
      <anchorfile>classIfpack2_1_1SingletonFilter.html</anchorfile>
      <anchor>a680addb7d23a93d96c54a000f7831ef7</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual global_size_t</type>
      <name>getGlobalNumCols</name>
      <anchorfile>classIfpack2_1_1SingletonFilter.html</anchorfile>
      <anchor>aa3a4a66433bf5dd975169d89ceb32fbd</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual size_t</type>
      <name>getNodeNumRows</name>
      <anchorfile>classIfpack2_1_1SingletonFilter.html</anchorfile>
      <anchor>ab6b4e37598d5557379f46664c646de02</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual size_t</type>
      <name>getNodeNumCols</name>
      <anchorfile>classIfpack2_1_1SingletonFilter.html</anchorfile>
      <anchor>a86ea42af743b598e5350b88561ec148a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual GlobalOrdinal</type>
      <name>getIndexBase</name>
      <anchorfile>classIfpack2_1_1SingletonFilter.html</anchorfile>
      <anchor>af5e60115fa950a34d36e6b00db3a5041</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual global_size_t</type>
      <name>getGlobalNumEntries</name>
      <anchorfile>classIfpack2_1_1SingletonFilter.html</anchorfile>
      <anchor>abd8068296a3b91de1f9cba638d256384</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual size_t</type>
      <name>getNodeNumEntries</name>
      <anchorfile>classIfpack2_1_1SingletonFilter.html</anchorfile>
      <anchor>ac3fd4a5b504667f6b501e52c07e77253</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual size_t</type>
      <name>getNumEntriesInGlobalRow</name>
      <anchorfile>classIfpack2_1_1SingletonFilter.html</anchorfile>
      <anchor>aa0b869f0de109673d54dd86760e23f6a</anchor>
      <arglist>(GlobalOrdinal globalRow) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual size_t</type>
      <name>getNumEntriesInLocalRow</name>
      <anchorfile>classIfpack2_1_1SingletonFilter.html</anchorfile>
      <anchor>a0e6879bf896d6d6d2bfa978cafe17169</anchor>
      <arglist>(LocalOrdinal localRow) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual global_size_t</type>
      <name>getGlobalNumDiags</name>
      <anchorfile>classIfpack2_1_1SingletonFilter.html</anchorfile>
      <anchor>a409a0b5b7bcfcb98e1cf559dfd0b1090</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual size_t</type>
      <name>getNodeNumDiags</name>
      <anchorfile>classIfpack2_1_1SingletonFilter.html</anchorfile>
      <anchor>a92ac65f120b623514065042dc76d811e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual size_t</type>
      <name>getGlobalMaxNumRowEntries</name>
      <anchorfile>classIfpack2_1_1SingletonFilter.html</anchorfile>
      <anchor>a658b085e1bd6d5c6de11d1850d91274d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual size_t</type>
      <name>getNodeMaxNumRowEntries</name>
      <anchorfile>classIfpack2_1_1SingletonFilter.html</anchorfile>
      <anchor>aec1413f0a099a29d2c9d8ffb6e938b9f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>hasColMap</name>
      <anchorfile>classIfpack2_1_1SingletonFilter.html</anchorfile>
      <anchor>a5ecf8273d349946bcc674f8bc4f5ce44</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>isLowerTriangular</name>
      <anchorfile>classIfpack2_1_1SingletonFilter.html</anchorfile>
      <anchor>ac403a3d05d86106c101b9fa8ab9fa7de</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>isUpperTriangular</name>
      <anchorfile>classIfpack2_1_1SingletonFilter.html</anchorfile>
      <anchor>addb91173a1b43cf8c8f7298c99c57431</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>isLocallyIndexed</name>
      <anchorfile>classIfpack2_1_1SingletonFilter.html</anchorfile>
      <anchor>a51cf6d0b2b9da70bba29622c66e577c3</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>isGloballyIndexed</name>
      <anchorfile>classIfpack2_1_1SingletonFilter.html</anchorfile>
      <anchor>afb44b6533fa443bc27bb8d7fb23f691c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>isFillComplete</name>
      <anchorfile>classIfpack2_1_1SingletonFilter.html</anchorfile>
      <anchor>ae2c974fd89c44fbf476aaf75e98a9c6b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>getGlobalRowCopy</name>
      <anchorfile>classIfpack2_1_1SingletonFilter.html</anchorfile>
      <anchor>a01b09b558ec2164b9da8bd5c903f0e4d</anchor>
      <arglist>(GlobalOrdinal GlobalRow, const Teuchos::ArrayView&lt; GlobalOrdinal &gt; &amp;Indices, const Teuchos::ArrayView&lt; Scalar &gt; &amp;Values, size_t &amp;NumEntries) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>getLocalRowCopy</name>
      <anchorfile>classIfpack2_1_1SingletonFilter.html</anchorfile>
      <anchor>a5f68d0df434f27c78ca342519caa1f1c</anchor>
      <arglist>(LocalOrdinal LocalRow, const Teuchos::ArrayView&lt; LocalOrdinal &gt; &amp;Indices, const Teuchos::ArrayView&lt; Scalar &gt; &amp;Values, size_t &amp;NumEntries) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>getGlobalRowView</name>
      <anchorfile>classIfpack2_1_1SingletonFilter.html</anchorfile>
      <anchor>a52a79580309fb3657004096fcfa6589f</anchor>
      <arglist>(GlobalOrdinal GlobalRow, Teuchos::ArrayView&lt; const GlobalOrdinal &gt; &amp;indices, Teuchos::ArrayView&lt; const Scalar &gt; &amp;values) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>getLocalRowView</name>
      <anchorfile>classIfpack2_1_1SingletonFilter.html</anchorfile>
      <anchor>addadf0a80ab35f12b100ca017853344c</anchor>
      <arglist>(LocalOrdinal LocalRow, Teuchos::ArrayView&lt; const LocalOrdinal &gt; &amp;indices, Teuchos::ArrayView&lt; const Scalar &gt; &amp;values) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>getLocalDiagCopy</name>
      <anchorfile>classIfpack2_1_1SingletonFilter.html</anchorfile>
      <anchor>a787c2b5c25edcadbd54ab40c9ac7cfde</anchor>
      <arglist>(Tpetra::Vector&lt; Scalar, LocalOrdinal, GlobalOrdinal, Node &gt; &amp;diag) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>leftScale</name>
      <anchorfile>classIfpack2_1_1SingletonFilter.html</anchorfile>
      <anchor>a01fa2de0f46d26733e3ae3a0c002b50f</anchor>
      <arglist>(const Tpetra::Vector&lt; Scalar, LocalOrdinal, GlobalOrdinal, Node &gt; &amp;x)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>rightScale</name>
      <anchorfile>classIfpack2_1_1SingletonFilter.html</anchorfile>
      <anchor>a534facca673ec3d4fff39a7cfd74738c</anchor>
      <arglist>(const Tpetra::Vector&lt; Scalar, LocalOrdinal, GlobalOrdinal, Node &gt; &amp;x)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual Teuchos::ScalarTraits&lt; Scalar &gt;::magnitudeType</type>
      <name>getFrobeniusNorm</name>
      <anchorfile>classIfpack2_1_1SingletonFilter.html</anchorfile>
      <anchor>a64f21637ba827ec12480917f88ae74e9</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>apply</name>
      <anchorfile>classIfpack2_1_1SingletonFilter.html</anchorfile>
      <anchor>ac5923c380cdc55b2a76108966df88274</anchor>
      <arglist>(const Tpetra::MultiVector&lt; Scalar, LocalOrdinal, GlobalOrdinal, Node &gt; &amp;X, Tpetra::MultiVector&lt; Scalar, LocalOrdinal, GlobalOrdinal, Node &gt; &amp;Y, Teuchos::ETransp mode=Teuchos::NO_TRANS, Scalar alpha=Teuchos::ScalarTraits&lt; Scalar &gt;::one(), Scalar beta=Teuchos::ScalarTraits&lt; Scalar &gt;::zero()) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>hasTransposeApply</name>
      <anchorfile>classIfpack2_1_1SingletonFilter.html</anchorfile>
      <anchor>a7042a17ba2115dc7633123d5577d1323</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>SolveSingletons</name>
      <anchorfile>classIfpack2_1_1SingletonFilter.html</anchorfile>
      <anchor>a119fe1b40e7649abb3417b7fd7c04dc3</anchor>
      <arglist>(const Tpetra::MultiVector&lt; Scalar, LocalOrdinal, GlobalOrdinal, Node &gt; &amp;RHS, Tpetra::MultiVector&lt; Scalar, LocalOrdinal, GlobalOrdinal, Node &gt; &amp;LHS)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>CreateReducedRHS</name>
      <anchorfile>classIfpack2_1_1SingletonFilter.html</anchorfile>
      <anchor>a8fb9d988fa846616e5435d4b588df08c</anchor>
      <arglist>(const Tpetra::MultiVector&lt; Scalar, LocalOrdinal, GlobalOrdinal, Node &gt; &amp;LHS, const Tpetra::MultiVector&lt; Scalar, LocalOrdinal, GlobalOrdinal, Node &gt; &amp;RHS, Tpetra::MultiVector&lt; Scalar, LocalOrdinal, GlobalOrdinal, Node &gt; &amp;ReducedRHS)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>UpdateLHS</name>
      <anchorfile>classIfpack2_1_1SingletonFilter.html</anchorfile>
      <anchor>a89cbd4443453390d4751370bf195a5cf</anchor>
      <arglist>(const Tpetra::MultiVector&lt; Scalar, LocalOrdinal, GlobalOrdinal, Node &gt; &amp;ReducedLHS, Tpetra::MultiVector&lt; Scalar, LocalOrdinal, GlobalOrdinal, Node &gt; &amp;LHS)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual TPETRA_DEPRECATED void</type>
      <name>getGlobalRowView</name>
      <anchorfile>classIfpack2_1_1SingletonFilter.html</anchorfile>
      <anchor>a25d2780d1b6400d9d7b093560fcd433a</anchor>
      <arglist>(GlobalOrdinal GlobalRow, Teuchos::ArrayRCP&lt; const GlobalOrdinal &gt; &amp;indices, Teuchos::ArrayRCP&lt; const Scalar &gt; &amp;values) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual TPETRA_DEPRECATED void</type>
      <name>getLocalRowView</name>
      <anchorfile>classIfpack2_1_1SingletonFilter.html</anchorfile>
      <anchor>ac9ae9164b4c024abbeea888eaa388aa7</anchor>
      <arglist>(LocalOrdinal LocalRow, Teuchos::ArrayRCP&lt; const LocalOrdinal &gt; &amp;indices, Teuchos::ArrayRCP&lt; const Scalar &gt; &amp;values) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Ifpack2::SparsityFilter</name>
    <filename>classIfpack2_1_1SparsityFilter.html</filename>
    <templarg></templarg>
    <member kind="function">
      <type></type>
      <name>SparsityFilter</name>
      <anchorfile>classIfpack2_1_1SparsityFilter.html</anchorfile>
      <anchor>a71456eab7357064b097fe5650f96ec44</anchor>
      <arglist>(const Teuchos::RCP&lt; const Tpetra::RowMatrix&lt; Scalar, LocalOrdinal, GlobalOrdinal, Node &gt; &gt; &amp;Matrix, size_t AllowedNumEntries, LocalOrdinal AllowedBandwidth=-Teuchos::ScalarTraits&lt; LocalOrdinal &gt;::one())</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~SparsityFilter</name>
      <anchorfile>classIfpack2_1_1SparsityFilter.html</anchorfile>
      <anchor>a64fb5c60b5ecec7f9870ad45b258bb5e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const Teuchos::RCP&lt; const Teuchos::Comm&lt; int &gt; &gt; &amp;</type>
      <name>getComm</name>
      <anchorfile>classIfpack2_1_1SparsityFilter.html</anchorfile>
      <anchor>afd0bb21b257fa9ee0e9d6869c88de6c5</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual Teuchos::RCP&lt; Node &gt;</type>
      <name>getNode</name>
      <anchorfile>classIfpack2_1_1SparsityFilter.html</anchorfile>
      <anchor>a222d3053d96bed7b012fefbed13f8f84</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const Teuchos::RCP&lt; const Tpetra::Map&lt; LocalOrdinal, GlobalOrdinal, Node &gt; &gt; &amp;</type>
      <name>getRowMap</name>
      <anchorfile>classIfpack2_1_1SparsityFilter.html</anchorfile>
      <anchor>a875201e74628c49acd9a073a4b8a27c4</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const Teuchos::RCP&lt; const Tpetra::Map&lt; LocalOrdinal, GlobalOrdinal, Node &gt; &gt; &amp;</type>
      <name>getColMap</name>
      <anchorfile>classIfpack2_1_1SparsityFilter.html</anchorfile>
      <anchor>acbc16deed1fc33176e854e796b0c2761</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const Teuchos::RCP&lt; const Tpetra::Map&lt; LocalOrdinal, GlobalOrdinal, Node &gt; &gt; &amp;</type>
      <name>getDomainMap</name>
      <anchorfile>classIfpack2_1_1SparsityFilter.html</anchorfile>
      <anchor>adc5958b7b0a447abacbd1802ccbd6d0e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const Teuchos::RCP&lt; const Tpetra::Map&lt; LocalOrdinal, GlobalOrdinal, Node &gt; &gt; &amp;</type>
      <name>getRangeMap</name>
      <anchorfile>classIfpack2_1_1SparsityFilter.html</anchorfile>
      <anchor>a4126a232276c2bd9b48be41ba8ec099b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual Teuchos::RCP&lt; const Tpetra::RowGraph&lt; LocalOrdinal, GlobalOrdinal, Node &gt; &gt;</type>
      <name>getGraph</name>
      <anchorfile>classIfpack2_1_1SparsityFilter.html</anchorfile>
      <anchor>ad47e016b612005ac891de031a2726760</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual global_size_t</type>
      <name>getGlobalNumRows</name>
      <anchorfile>classIfpack2_1_1SparsityFilter.html</anchorfile>
      <anchor>ae49aab45c1196e99642e3d3cb0a88072</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual global_size_t</type>
      <name>getGlobalNumCols</name>
      <anchorfile>classIfpack2_1_1SparsityFilter.html</anchorfile>
      <anchor>aa90d3d2db9c898d29a37010d9d60b901</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual size_t</type>
      <name>getNodeNumRows</name>
      <anchorfile>classIfpack2_1_1SparsityFilter.html</anchorfile>
      <anchor>ae1bf873e7cf5bb9b33d10a7c80414c7e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual size_t</type>
      <name>getNodeNumCols</name>
      <anchorfile>classIfpack2_1_1SparsityFilter.html</anchorfile>
      <anchor>a8dcc5088632b6fc67376ad2f22a319f5</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual GlobalOrdinal</type>
      <name>getIndexBase</name>
      <anchorfile>classIfpack2_1_1SparsityFilter.html</anchorfile>
      <anchor>a8e67e1a70635865d0e5e4e5755358611</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual global_size_t</type>
      <name>getGlobalNumEntries</name>
      <anchorfile>classIfpack2_1_1SparsityFilter.html</anchorfile>
      <anchor>aa27121ca235f4337bf76aa9b9ad6d87e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual size_t</type>
      <name>getNodeNumEntries</name>
      <anchorfile>classIfpack2_1_1SparsityFilter.html</anchorfile>
      <anchor>a2518f123a6729b3ae8e013800cc6af17</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual size_t</type>
      <name>getNumEntriesInGlobalRow</name>
      <anchorfile>classIfpack2_1_1SparsityFilter.html</anchorfile>
      <anchor>afe581d90adc415091199317e88ad6ea8</anchor>
      <arglist>(GlobalOrdinal globalRow) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual size_t</type>
      <name>getNumEntriesInLocalRow</name>
      <anchorfile>classIfpack2_1_1SparsityFilter.html</anchorfile>
      <anchor>a7ec5600dfe51c8a0bb617fd6b31a63d8</anchor>
      <arglist>(LocalOrdinal localRow) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual global_size_t</type>
      <name>getGlobalNumDiags</name>
      <anchorfile>classIfpack2_1_1SparsityFilter.html</anchorfile>
      <anchor>a12a9cbbbf30252bce05be3b1c2cfe193</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual size_t</type>
      <name>getNodeNumDiags</name>
      <anchorfile>classIfpack2_1_1SparsityFilter.html</anchorfile>
      <anchor>a2a4e8d2d498dd9f86b94484b8708f59e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual size_t</type>
      <name>getGlobalMaxNumRowEntries</name>
      <anchorfile>classIfpack2_1_1SparsityFilter.html</anchorfile>
      <anchor>a35868495ce2d34bc22294d0fd23e3ac4</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual size_t</type>
      <name>getNodeMaxNumRowEntries</name>
      <anchorfile>classIfpack2_1_1SparsityFilter.html</anchorfile>
      <anchor>a9ad3f6a43ee07c2eb03be9a505e1584b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>hasColMap</name>
      <anchorfile>classIfpack2_1_1SparsityFilter.html</anchorfile>
      <anchor>a1766e1b6dc17a4665801e982dbe4d80a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>isLowerTriangular</name>
      <anchorfile>classIfpack2_1_1SparsityFilter.html</anchorfile>
      <anchor>a14ae3a25c8cd18f9d6b01df7740140cd</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>isUpperTriangular</name>
      <anchorfile>classIfpack2_1_1SparsityFilter.html</anchorfile>
      <anchor>a3553b46d9ef6a9fc7228790b20feabd3</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>isLocallyIndexed</name>
      <anchorfile>classIfpack2_1_1SparsityFilter.html</anchorfile>
      <anchor>a86def893e36c09c53b97832582deb7ef</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>isGloballyIndexed</name>
      <anchorfile>classIfpack2_1_1SparsityFilter.html</anchorfile>
      <anchor>a6418ec00fe805d373e11cccf5aa719f7</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>isFillComplete</name>
      <anchorfile>classIfpack2_1_1SparsityFilter.html</anchorfile>
      <anchor>afd8795d040cb7e838a22e123931e4340</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>getGlobalRowCopy</name>
      <anchorfile>classIfpack2_1_1SparsityFilter.html</anchorfile>
      <anchor>a39047cd28d238a42b26c2bea8436abb0</anchor>
      <arglist>(GlobalOrdinal GlobalRow, const Teuchos::ArrayView&lt; GlobalOrdinal &gt; &amp;Indices, const Teuchos::ArrayView&lt; Scalar &gt; &amp;Values, size_t &amp;NumEntries) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>getLocalRowCopy</name>
      <anchorfile>classIfpack2_1_1SparsityFilter.html</anchorfile>
      <anchor>a50809f3ddd4f7a0634bfc97b0ee92972</anchor>
      <arglist>(LocalOrdinal DropRow, const Teuchos::ArrayView&lt; LocalOrdinal &gt; &amp;Indices, const Teuchos::ArrayView&lt; Scalar &gt; &amp;Values, size_t &amp;NumEntries) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>getGlobalRowView</name>
      <anchorfile>classIfpack2_1_1SparsityFilter.html</anchorfile>
      <anchor>a6b71feabe42adf22940f10b327a80860</anchor>
      <arglist>(GlobalOrdinal GlobalRow, Teuchos::ArrayView&lt; const GlobalOrdinal &gt; &amp;indices, Teuchos::ArrayView&lt; const Scalar &gt; &amp;values) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>getLocalRowView</name>
      <anchorfile>classIfpack2_1_1SparsityFilter.html</anchorfile>
      <anchor>a86daa6762e012d67bf145ed8ba1450cf</anchor>
      <arglist>(LocalOrdinal DropRow, Teuchos::ArrayView&lt; const LocalOrdinal &gt; &amp;indices, Teuchos::ArrayView&lt; const Scalar &gt; &amp;values) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>getLocalDiagCopy</name>
      <anchorfile>classIfpack2_1_1SparsityFilter.html</anchorfile>
      <anchor>a6ccb150a04ec5a5609920e2f0d1d5de5</anchor>
      <arglist>(Tpetra::Vector&lt; Scalar, LocalOrdinal, GlobalOrdinal, Node &gt; &amp;diag) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>leftScale</name>
      <anchorfile>classIfpack2_1_1SparsityFilter.html</anchorfile>
      <anchor>aba978ffc734eb79981ea3c706e011e76</anchor>
      <arglist>(const Tpetra::Vector&lt; Scalar, LocalOrdinal, GlobalOrdinal, Node &gt; &amp;x)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>rightScale</name>
      <anchorfile>classIfpack2_1_1SparsityFilter.html</anchorfile>
      <anchor>a98d27525c6ae25d4371cb3682737da4f</anchor>
      <arglist>(const Tpetra::Vector&lt; Scalar, LocalOrdinal, GlobalOrdinal, Node &gt; &amp;x)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual Teuchos::ScalarTraits&lt; Scalar &gt;::magnitudeType</type>
      <name>getFrobeniusNorm</name>
      <anchorfile>classIfpack2_1_1SparsityFilter.html</anchorfile>
      <anchor>a325c0d1bd29fe207fe174de3876321c3</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>apply</name>
      <anchorfile>classIfpack2_1_1SparsityFilter.html</anchorfile>
      <anchor>addb5897de836e2049766b552d1023224</anchor>
      <arglist>(const Tpetra::MultiVector&lt; Scalar, LocalOrdinal, GlobalOrdinal, Node &gt; &amp;X, Tpetra::MultiVector&lt; Scalar, LocalOrdinal, GlobalOrdinal, Node &gt; &amp;Y, Teuchos::ETransp mode=Teuchos::NO_TRANS, Scalar alpha=Teuchos::ScalarTraits&lt; Scalar &gt;::one(), Scalar beta=Teuchos::ScalarTraits&lt; Scalar &gt;::zero()) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>hasTransposeApply</name>
      <anchorfile>classIfpack2_1_1SparsityFilter.html</anchorfile>
      <anchor>a3979670e40469124cf082dbdfa947f39</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual TPETRA_DEPRECATED void</type>
      <name>getGlobalRowView</name>
      <anchorfile>classIfpack2_1_1SparsityFilter.html</anchorfile>
      <anchor>af0ac0f14335b90afa3b61c435458699c</anchor>
      <arglist>(GlobalOrdinal GlobalRow, Teuchos::ArrayRCP&lt; const GlobalOrdinal &gt; &amp;indices, Teuchos::ArrayRCP&lt; const Scalar &gt; &amp;values) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual TPETRA_DEPRECATED void</type>
      <name>getLocalRowView</name>
      <anchorfile>classIfpack2_1_1SparsityFilter.html</anchorfile>
      <anchor>a876fe99aeb06ccd505f9b1767e98ff78</anchor>
      <arglist>(LocalOrdinal DropRow, Teuchos::ArrayRCP&lt; const LocalOrdinal &gt; &amp;indices, Teuchos::ArrayRCP&lt; const Scalar &gt; &amp;values) const </arglist>
    </member>
  </compound>
  <compound kind="dir">
    <name>src</name>
    <path>/Users/sscoll/Downloads/trilinos-11.0.3-Source/packages/ifpack2/src/</path>
    <filename>dir_68267d1309a1af8e8297ef4c3efbcdba.html</filename>
    <file>Ifpack2_BlockRelaxation.cpp</file>
    <file>Ifpack2_BlockRelaxation_decl.hpp</file>
    <file>Ifpack2_BlockRelaxation_def.hpp</file>
    <file>Ifpack2_BorderedOperator.cpp</file>
    <file>Ifpack2_BorderedOperator_decl.hpp</file>
    <file>Ifpack2_BorderedOperator_def.hpp</file>
    <file>Ifpack2_Chebyshev.cpp</file>
    <file>Ifpack2_Chebyshev_decl.hpp</file>
    <file>Ifpack2_Chebyshev_def.hpp</file>
    <file>Ifpack2_Condest.hpp</file>
    <file>Ifpack2_CondestType.hpp</file>
    <file>Ifpack2_ConfigDefs.hpp</file>
    <file>Ifpack2_ConstructLevelFillGraph.hpp</file>
    <file>Ifpack2_Container.hpp</file>
    <file>Ifpack2_CreateOverlapGraph.hpp</file>
    <file>Ifpack2_Diagonal.cpp</file>
    <file>Ifpack2_Diagonal_decl.hpp</file>
    <file>Ifpack2_Diagonal_def.hpp</file>
    <file>Ifpack2_DiagonalFilter.cpp</file>
    <file>Ifpack2_DiagonalFilter_decl.hpp</file>
    <file>Ifpack2_DiagonalFilter_def.hpp</file>
    <file>Ifpack2_DropFilter.cpp</file>
    <file>Ifpack2_DropFilter_decl.hpp</file>
    <file>Ifpack2_DropFilter_def.hpp</file>
    <file>Ifpack2_ExplicitInstantiationHelpers.hpp</file>
    <file>Ifpack2_Factory.cpp</file>
    <file>Ifpack2_Factory.hpp</file>
    <file>Ifpack2_Heap.hpp</file>
    <file>Ifpack2_IlukGraph.hpp</file>
    <file>Ifpack2_ILUT.cpp</file>
    <file>Ifpack2_ILUT_decl.hpp</file>
    <file>Ifpack2_ILUT_def.hpp</file>
    <file>Ifpack2_LinearPartitioner.cpp</file>
    <file>Ifpack2_LinearPartitioner_decl.hpp</file>
    <file>Ifpack2_LinearPartitioner_def.hpp</file>
    <file>Ifpack2_LocalFilter.cpp</file>
    <file>Ifpack2_LocalFilter_decl.hpp</file>
    <file>Ifpack2_LocalFilter_def.hpp</file>
    <file>Ifpack2_OverlapGraph.hpp</file>
    <file>Ifpack2_OverlappingPartitioner_decl.hpp</file>
    <file>Ifpack2_OverlappingPartitioner_def.hpp</file>
    <file>Ifpack2_Parameters.cpp</file>
    <file>Ifpack2_Parameters.hpp</file>
    <file>Ifpack2_Partitioner.hpp</file>
    <file>Ifpack2_Preconditioner.hpp</file>
    <file>Ifpack2_Relaxation.cpp</file>
    <file>Ifpack2_Relaxation_decl.hpp</file>
    <file>Ifpack2_Relaxation_def.hpp</file>
    <file>Ifpack2_RILUK.cpp</file>
    <file>Ifpack2_RILUK_decl.hpp</file>
    <file>Ifpack2_RILUK_def.hpp</file>
    <file>Ifpack2_ScalingType.hpp</file>
    <file>Ifpack2_SingletonFilter.cpp</file>
    <file>Ifpack2_SingletonFilter_decl.hpp</file>
    <file>Ifpack2_SingletonFilter_def.hpp</file>
    <file>Ifpack2_SparseContainer.cpp</file>
    <file>Ifpack2_SparseContainer_decl.hpp</file>
    <file>Ifpack2_SparseContainer_def.hpp</file>
    <file>Ifpack2_SparsityFilter.cpp</file>
    <file>Ifpack2_SparsityFilter_decl.hpp</file>
    <file>Ifpack2_SparsityFilter_def.hpp</file>
    <file>Ifpack2_Version.hpp</file>
  </compound>
  <compound kind="page">
    <name>index</name>
    <title>Trilinos/Ifpack2: Templated Preconditioning Package</title>
    <filename>index</filename>
    <docanchor file="index">tifpack_intro</docanchor>
    <docanchor file="index">startup</docanchor>
    <docanchor file="index">types</docanchor>
    <docanchor file="index">precs</docanchor>
    <docanchor file="index">trilinos</docanchor>
    <docanchor file="index">Examples</docanchor>
  </compound>
</tagfile>
