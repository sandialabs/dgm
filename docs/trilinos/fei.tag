<?xml version='1.0' encoding='UTF-8' standalone='yes' ?>
<tagfile>
  <compound kind="class">
    <name>fei_trilinos::Aztec_LSVector</name>
    <filename>classfei__trilinos_1_1Aztec__LSVector.html</filename>
  </compound>
  <compound kind="class">
    <name>snl_fei::BlkSizeMsgHandler</name>
    <filename>classsnl__fei_1_1BlkSizeMsgHandler.html</filename>
    <base>MessageHandler&lt; int &gt;</base>
    <member kind="function">
      <type></type>
      <name>BlkSizeMsgHandler</name>
      <anchorfile>classsnl__fei_1_1BlkSizeMsgHandler.html</anchorfile>
      <anchor>a7a82cb9bee133f44e67011a0e7200b87</anchor>
      <arglist>(fei::VectorSpace *vspace, fei::Graph *graph, MPI_Comm comm)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~BlkSizeMsgHandler</name>
      <anchorfile>classsnl__fei_1_1BlkSizeMsgHandler.html</anchorfile>
      <anchor>a52aeb95376390135ef9a3264e20295bc</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>do_the_exchange</name>
      <anchorfile>classsnl__fei_1_1BlkSizeMsgHandler.html</anchorfile>
      <anchor>ab5962265c7efd4734f7d2d87f93abd1e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>std::vector&lt; int &gt; &amp;</type>
      <name>getSendProcs</name>
      <anchorfile>classsnl__fei_1_1BlkSizeMsgHandler.html</anchorfile>
      <anchor>a768fd00aaa272dc12b462bfc7f67dfad</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>std::vector&lt; int &gt; &amp;</type>
      <name>getRecvProcs</name>
      <anchorfile>classsnl__fei_1_1BlkSizeMsgHandler.html</anchorfile>
      <anchor>a39d9bd79888b22ca252deb4d0819dc94</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getSendMessageLength</name>
      <anchorfile>classsnl__fei_1_1BlkSizeMsgHandler.html</anchorfile>
      <anchor>a9acf748967dfe47339f377decd636a13</anchor>
      <arglist>(int destProc, int &amp;messageLength)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getSendMessage</name>
      <anchorfile>classsnl__fei_1_1BlkSizeMsgHandler.html</anchorfile>
      <anchor>aab91266d8aee87934320fc33e17066a9</anchor>
      <arglist>(int destProc, std::vector&lt; int &gt; &amp;message)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>processRecvMessage</name>
      <anchorfile>classsnl__fei_1_1BlkSizeMsgHandler.html</anchorfile>
      <anchor>a463c80c099cab12f0941414c4d0c6e7e</anchor>
      <arglist>(int srcProc, std::vector&lt; int &gt; &amp;message)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>BlockDescriptor</name>
    <filename>classBlockDescriptor.html</filename>
    <member kind="function">
      <type>int</type>
      <name>setNumNodesPerElement</name>
      <anchorfile>classBlockDescriptor.html</anchorfile>
      <anchor>aab6d7a4ee820e8ab62370a51ea51e590</anchor>
      <arglist>(int numNodes)</arglist>
    </member>
    <member kind="function">
      <type>int **</type>
      <name>fieldIDsTablePtr</name>
      <anchorfile>classBlockDescriptor.html</anchorfile>
      <anchor>ab7d3787b3df60c5be92eadff908b36e9</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>fei::BlockLinearProblemManager</name>
    <filename>classfei_1_1BlockLinearProblemManager.html</filename>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~BlockLinearProblemManager</name>
      <anchorfile>classfei_1_1BlockLinearProblemManager.html</anchorfile>
      <anchor>a0aebdab932d3cb3b43a68dca3a054404</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>setRowDistribution</name>
      <anchorfile>classfei_1_1BlockLinearProblemManager.html</anchorfile>
      <anchor>ac531e44952a2ae90362d06f0c4462302</anchor>
      <arglist>(const std::vector&lt; int &gt; &amp;ownedIDs, const std::vector&lt; int &gt; &amp;dofPerOwnedID, const std::vector&lt; int &gt; &amp;ghostIDs, const std::vector&lt; int &gt; &amp;dofPerGhostID)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>setMatrixGraph</name>
      <anchorfile>classfei_1_1BlockLinearProblemManager.html</anchorfile>
      <anchor>ac936a181429aa6e54125f50f4a91d84a</anchor>
      <arglist>(fei::SharedPtr&lt; fei::SparseRowGraph &gt; matrixGraph)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>setMatrixValues</name>
      <anchorfile>classfei_1_1BlockLinearProblemManager.html</anchorfile>
      <anchor>a4a1714456118ea66ca70bbda5addd6c4</anchor>
      <arglist>(double scalar)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>getNumOwnedIDs</name>
      <anchorfile>classfei_1_1BlockLinearProblemManager.html</anchorfile>
      <anchor>a77d7e184d2f2a6f8fda0a747b6ab0cbc</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>getRowPointLength</name>
      <anchorfile>classfei_1_1BlockLinearProblemManager.html</anchorfile>
      <anchor>a98e2b8566f5a543d04df1acfe4b94edf</anchor>
      <arglist>(int ownedID)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>getRowBlockLength</name>
      <anchorfile>classfei_1_1BlockLinearProblemManager.html</anchorfile>
      <anchor>ae033460304807e28efc1a9d1ed7acd22</anchor>
      <arglist>(int ownedID)=0</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>copyOutMatrixRow</name>
      <anchorfile>classfei_1_1BlockLinearProblemManager.html</anchorfile>
      <anchor>ad9cd5b884f52ff017d69a1776e8d0ccb</anchor>
      <arglist>(int ownedID, int dofOffset, int numColIDs, int numCoefs, int *colIDs, int *dofPerColID, double *coefs)</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>insertMatrixValues</name>
      <anchorfile>classfei_1_1BlockLinearProblemManager.html</anchorfile>
      <anchor>a145512deb703764e66ceeab7d0b75749</anchor>
      <arglist>(int rowID, int numRowDof, int colID, int numColDof, const double *const *values, bool sum_into)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>insertMatrixValues</name>
      <anchorfile>classfei_1_1BlockLinearProblemManager.html</anchorfile>
      <anchor>a2e4664446eb8413100eb470f4bd104a4</anchor>
      <arglist>(int rowID, int rowDofOffset, int colID, int colDofOffset, double value, bool sum_into)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>setVectorValues</name>
      <anchorfile>classfei_1_1BlockLinearProblemManager.html</anchorfile>
      <anchor>ac41970849a3d208ce5ee18e190939a9f</anchor>
      <arglist>(double scalar, bool soln_vector)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>insertVectorValues</name>
      <anchorfile>classfei_1_1BlockLinearProblemManager.html</anchorfile>
      <anchor>addaa3c931d0314c54a9b3b96df4085a0</anchor>
      <arglist>(int ID, int numDof, const double *values, bool sum_into, bool soln_vector, int vectorIndex=0)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>copyOutVectorValues</name>
      <anchorfile>classfei_1_1BlockLinearProblemManager.html</anchorfile>
      <anchor>ab618b3bb4e8509e03f78b8dc4f754af1</anchor>
      <arglist>(int ID, int numDof, double *values, bool soln_vector, int vectorIndex=0)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual double *</type>
      <name>getLocalVectorValuesPtr</name>
      <anchorfile>classfei_1_1BlockLinearProblemManager.html</anchorfile>
      <anchor>abebdb9f270eac59c1b08485f06c0ca6a</anchor>
      <arglist>(bool soln_vector, int vectorIndex=0)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>globalAssemble</name>
      <anchorfile>classfei_1_1BlockLinearProblemManager.html</anchorfile>
      <anchor>aafcf283a853252a49eddf0fe9b80f123</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>solve</name>
      <anchorfile>classfei_1_1BlockLinearProblemManager.html</anchorfile>
      <anchor>ab208d7b5be601646270ccfc4eb8c4879</anchor>
      <arglist>(const fei::ParameterSet &amp;parameters)=0</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>snl_fei::BlockMatrixTraits</name>
    <filename>structsnl__fei_1_1BlockMatrixTraits.html</filename>
    <templarg></templarg>
    <member kind="function" static="yes">
      <type>static const char *</type>
      <name>typeName</name>
      <anchorfile>structsnl__fei_1_1BlockMatrixTraits.html</anchorfile>
      <anchor>adac853bfc70983dfbccd0a6c7b685da4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static int</type>
      <name>putScalar</name>
      <anchorfile>structsnl__fei_1_1BlockMatrixTraits.html</anchorfile>
      <anchor>aa11df878cdb518acad42d8e589f8045f</anchor>
      <arglist>(T *, double)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static int</type>
      <name>getRowLength</name>
      <anchorfile>structsnl__fei_1_1BlockMatrixTraits.html</anchorfile>
      <anchor>ab1979b3cd8e23a4b54e29c255519ef7f</anchor>
      <arglist>(T *, int, int &amp;)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static int</type>
      <name>getPointRowLength</name>
      <anchorfile>structsnl__fei_1_1BlockMatrixTraits.html</anchorfile>
      <anchor>a8b6137c68513e319c478e87914e402a6</anchor>
      <arglist>(T *, int, int &amp;)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static int</type>
      <name>copyOutRow</name>
      <anchorfile>structsnl__fei_1_1BlockMatrixTraits.html</anchorfile>
      <anchor>a5fa7352cc09a9818ba2bc76bdb06f84b</anchor>
      <arglist>(T *, int, int, int, int *, int *, double *, int, int &amp;)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static int</type>
      <name>copyOutPointRow</name>
      <anchorfile>structsnl__fei_1_1BlockMatrixTraits.html</anchorfile>
      <anchor>a3833f7f85be34373fb4db7ef8812c8eb</anchor>
      <arglist>(T *, int, int, int, double *, int *, int &amp;)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static int</type>
      <name>sumIn</name>
      <anchorfile>structsnl__fei_1_1BlockMatrixTraits.html</anchorfile>
      <anchor>a15d01b45ca1468a282021623e7b42e09</anchor>
      <arglist>(T *, int, int, int, const int *, const int *, int, const double *)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static int</type>
      <name>copyIn</name>
      <anchorfile>structsnl__fei_1_1BlockMatrixTraits.html</anchorfile>
      <anchor>af7fa8d12499ef2ba4d1642b86a925a23</anchor>
      <arglist>(T *, int, int, int, const int *, const int *, int, const double *)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static int</type>
      <name>sumIn</name>
      <anchorfile>structsnl__fei_1_1BlockMatrixTraits.html</anchorfile>
      <anchor>a603492fe1db606070d1a9dee3cd7388f</anchor>
      <arglist>(T *, int, int, int, const int *, const int *, const int *, const double *const *)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static int</type>
      <name>copyIn</name>
      <anchorfile>structsnl__fei_1_1BlockMatrixTraits.html</anchorfile>
      <anchor>a32bf52858d1b2060b91104075d0f458b</anchor>
      <arglist>(T *, int, int, int, const int *, const int *, const int *, const double *const *)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static int</type>
      <name>globalAssemble</name>
      <anchorfile>structsnl__fei_1_1BlockMatrixTraits.html</anchorfile>
      <anchor>a8741219fdc89b7a0496c845809d2c0fd</anchor>
      <arglist>(T *)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>snl_fei::Broker</name>
    <filename>classsnl__fei_1_1Broker.html</filename>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~Broker</name>
      <anchorfile>classsnl__fei_1_1Broker.html</anchorfile>
      <anchor>adf0ea1b5b7c92d66e858143d4df8d13b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual fei::SharedPtr&lt; fei::Vector &gt;</type>
      <name>createVector</name>
      <anchorfile>classsnl__fei_1_1Broker.html</anchorfile>
      <anchor>a3a3bffeca5be56d4be0da1a12f32be77</anchor>
      <arglist>(bool isSolutionVector=false)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual fei::SharedPtr&lt; fei::Matrix &gt;</type>
      <name>createMatrix</name>
      <anchorfile>classsnl__fei_1_1Broker.html</anchorfile>
      <anchor>a6b1363f8a9f69fde45bb47d2b428b7c8</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual fei::SharedPtr&lt; fei::LinearSystem &gt;</type>
      <name>createLinearSystem</name>
      <anchorfile>classsnl__fei_1_1Broker.html</anchorfile>
      <anchor>a158bd6969b0cc45439dafd50cdc97175</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>setMatrixGraph</name>
      <anchorfile>classsnl__fei_1_1Broker.html</anchorfile>
      <anchor>acc97d850633f3d7c2c1335c810e2b1f3</anchor>
      <arglist>(fei::SharedPtr&lt; fei::MatrixGraph &gt; matrixGraph)=0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>snl_fei::Broker_FEData</name>
    <filename>classsnl__fei_1_1Broker__FEData.html</filename>
    <base>snl_fei::Broker</base>
    <member kind="function">
      <type></type>
      <name>Broker_FEData</name>
      <anchorfile>classsnl__fei_1_1Broker__FEData.html</anchorfile>
      <anchor>a8a7a22b39fe9e1f532fe527e3fcc671c</anchor>
      <arglist>(fei::SharedPtr&lt; FiniteElementData &gt; feData, fei::SharedPtr&lt; fei::MatrixGraph &gt; matrixGraph, int nodeIDType)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~Broker_FEData</name>
      <anchorfile>classsnl__fei_1_1Broker__FEData.html</anchorfile>
      <anchor>af851fa47eab4be8a3767d9ed816b2308</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual fei::SharedPtr&lt; fei::Vector &gt;</type>
      <name>createVector</name>
      <anchorfile>classsnl__fei_1_1Broker__FEData.html</anchorfile>
      <anchor>a78b5c83ce2feb5f09ff96c5ee49bbc80</anchor>
      <arglist>(bool isSolutionVector=false)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual fei::SharedPtr&lt; fei::Matrix &gt;</type>
      <name>createMatrix</name>
      <anchorfile>classsnl__fei_1_1Broker__FEData.html</anchorfile>
      <anchor>a5336d20a1fa1022847aa870cb5f9cefe</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual fei::SharedPtr&lt; fei::LinearSystem &gt;</type>
      <name>createLinearSystem</name>
      <anchorfile>classsnl__fei_1_1Broker__FEData.html</anchorfile>
      <anchor>a3b65729bc15e94094a34cfbf75b81eea</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>setMatrixGraph</name>
      <anchorfile>classsnl__fei_1_1Broker__FEData.html</anchorfile>
      <anchor>a0193f879ecc112c8b0c90448add667a2</anchor>
      <arglist>(fei::SharedPtr&lt; fei::MatrixGraph &gt; matrixGraph)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>snl_fei::Broker_LinSysCore</name>
    <filename>classsnl__fei_1_1Broker__LinSysCore.html</filename>
    <base>snl_fei::Broker</base>
    <member kind="function">
      <type></type>
      <name>Broker_LinSysCore</name>
      <anchorfile>classsnl__fei_1_1Broker__LinSysCore.html</anchorfile>
      <anchor>ae9a3f7b779a238448ac4923e8c42f457</anchor>
      <arglist>(fei::SharedPtr&lt; LinearSystemCore &gt; lsc, fei::SharedPtr&lt; fei::MatrixGraph &gt; matrixGraph, fei::SharedPtr&lt; fei::Reducer &gt; reducer, bool blockMatrix)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~Broker_LinSysCore</name>
      <anchorfile>classsnl__fei_1_1Broker__LinSysCore.html</anchorfile>
      <anchor>ab474543d89f1e8bd947fa2466a3de91f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>fei::SharedPtr&lt; fei::Vector &gt;</type>
      <name>createVector</name>
      <anchorfile>classsnl__fei_1_1Broker__LinSysCore.html</anchorfile>
      <anchor>af5ecf4235514a31851ec918f8907ffdc</anchor>
      <arglist>(bool isSolutionVector=false)</arglist>
    </member>
    <member kind="function">
      <type>fei::SharedPtr&lt; fei::Matrix &gt;</type>
      <name>createMatrix</name>
      <anchorfile>classsnl__fei_1_1Broker__LinSysCore.html</anchorfile>
      <anchor>a0034b7109b97b6d48e153bda1c622587</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>fei::SharedPtr&lt; fei::LinearSystem &gt;</type>
      <name>createLinearSystem</name>
      <anchorfile>classsnl__fei_1_1Broker__LinSysCore.html</anchorfile>
      <anchor>ae0cd1a8d6b1a8d4d762ee870820bff3e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setMatrixGraph</name>
      <anchorfile>classsnl__fei_1_1Broker__LinSysCore.html</anchorfile>
      <anchor>ad2bc84c999d921b62cdf1837433b530b</anchor>
      <arglist>(fei::SharedPtr&lt; fei::MatrixGraph &gt; matrixGraph)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>fei::CommMap</name>
    <filename>structfei_1_1CommMap.html</filename>
    <templarg>T</templarg>
  </compound>
  <compound kind="class">
    <name>fei::ConnectivityBlock</name>
    <filename>classfei_1_1ConnectivityBlock.html</filename>
    <member kind="function">
      <type></type>
      <name>ConnectivityBlock</name>
      <anchorfile>classfei_1_1ConnectivityBlock.html</anchorfile>
      <anchor>a783173c9e034ab2b5d7ee1fe48b82e7f</anchor>
      <arglist>(int blockID, fei::Pattern *pattern, int numConnectivities)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ConnectivityBlock</name>
      <anchorfile>classfei_1_1ConnectivityBlock.html</anchorfile>
      <anchor>ae7bb5597bbdf0d10d7b0cba5b08f9a88</anchor>
      <arglist>(int blockID, fei::Pattern *rowpattern, fei::Pattern *colpattern, int numConnectivities)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ConnectivityBlock</name>
      <anchorfile>classfei_1_1ConnectivityBlock.html</anchorfile>
      <anchor>a53b18ff619793183ab4c65a51b10dd7a</anchor>
      <arglist>(int numRowIDs, const int *rowIDs, const int *rowOffsets, bool offsets_are_lengths=false)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ConnectivityBlock</name>
      <anchorfile>classfei_1_1ConnectivityBlock.html</anchorfile>
      <anchor>ab54bf1f0e69ea61f8ad2d0e65a29e694</anchor>
      <arglist>(int fieldID, int numRowIDs, const int *rowIDs, const int *rowOffsets, bool offsets_are_lengths=false)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~ConnectivityBlock</name>
      <anchorfile>classfei_1_1ConnectivityBlock.html</anchorfile>
      <anchor>aad3780f63ae64f526aa1ab69e3280047</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getBlockID</name>
      <anchorfile>classfei_1_1ConnectivityBlock.html</anchorfile>
      <anchor>a95a343bd2c27e2a98d3c8096486cb9b3</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const fei::Pattern *</type>
      <name>getRowPattern</name>
      <anchorfile>classfei_1_1ConnectivityBlock.html</anchorfile>
      <anchor>a03b95b2600a58754af202fe2db038810</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>fei::Pattern *</type>
      <name>getRowPattern</name>
      <anchorfile>classfei_1_1ConnectivityBlock.html</anchorfile>
      <anchor>a70436e7757f140f134d3c4088e8d4e17</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const fei::Pattern *</type>
      <name>getColPattern</name>
      <anchorfile>classfei_1_1ConnectivityBlock.html</anchorfile>
      <anchor>a5a8caffa34f8a665a9b4fc7b05d3dbc8</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>fei::Pattern *</type>
      <name>getColPattern</name>
      <anchorfile>classfei_1_1ConnectivityBlock.html</anchorfile>
      <anchor>a26d5a7b29bf759b646ce97a3d97bd43b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const std::map&lt; int, int &gt; &amp;</type>
      <name>getConnectivityIDs</name>
      <anchorfile>classfei_1_1ConnectivityBlock.html</anchorfile>
      <anchor>a3fdc7a06d3dfc0a0cd679dbf969bf59f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>std::map&lt; int, int &gt; &amp;</type>
      <name>getConnectivityIDs</name>
      <anchorfile>classfei_1_1ConnectivityBlock.html</anchorfile>
      <anchor>a8f955be4ed1ef41f2d8eff7153d8afdc</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>std::vector&lt; int &gt; &amp;</type>
      <name>getConnectivityOffsets</name>
      <anchorfile>classfei_1_1ConnectivityBlock.html</anchorfile>
      <anchor>a93c74c56eea30226cc913df09bd4e5b9</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>std::vector&lt; int &gt; &amp;</type>
      <name>getRowConnectivities</name>
      <anchorfile>classfei_1_1ConnectivityBlock.html</anchorfile>
      <anchor>abe3485feb706bbebbf8910e6c4a54246</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>std::vector&lt; int &gt; &amp;</type>
      <name>getColConnectivities</name>
      <anchorfile>classfei_1_1ConnectivityBlock.html</anchorfile>
      <anchor>ad254dbd8a39978a678c3821407b79118</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const int *</type>
      <name>getRowConnectivity</name>
      <anchorfile>classfei_1_1ConnectivityBlock.html</anchorfile>
      <anchor>a179f5decb799015509e4752b1ac0be54</anchor>
      <arglist>(int ID) const </arglist>
    </member>
    <member kind="function">
      <type>const int *</type>
      <name>getColConnectivity</name>
      <anchorfile>classfei_1_1ConnectivityBlock.html</anchorfile>
      <anchor>abf0747cef6749ec290d1c8f5af678604</anchor>
      <arglist>(int ID) const </arglist>
    </member>
    <member kind="function">
      <type>int *</type>
      <name>getRowConnectivity</name>
      <anchorfile>classfei_1_1ConnectivityBlock.html</anchorfile>
      <anchor>a0b66da0403e8c1f4b9ed7563cb23472f</anchor>
      <arglist>(int ID)</arglist>
    </member>
    <member kind="function">
      <type>int *</type>
      <name>getColConnectivity</name>
      <anchorfile>classfei_1_1ConnectivityBlock.html</anchorfile>
      <anchor>a3ab0d4f4a9f108746d5e3e1951726447</anchor>
      <arglist>(int ID)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isSymmetric</name>
      <anchorfile>classfei_1_1ConnectivityBlock.html</anchorfile>
      <anchor>a8cd0eb46a3ac5befbc89bfa4c45973ab</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setIsDiagonal</name>
      <anchorfile>classfei_1_1ConnectivityBlock.html</anchorfile>
      <anchor>a3a4be3153fb803ef7310dc33af01414a</anchor>
      <arglist>(bool flag)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isDiagonal</name>
      <anchorfile>classfei_1_1ConnectivityBlock.html</anchorfile>
      <anchor>a3b486c1a261b53e71841e823e7dc88d7</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>haveFieldID</name>
      <anchorfile>classfei_1_1ConnectivityBlock.html</anchorfile>
      <anchor>a079ffc1f7c9bbd31c5714aef0c7cc5bf</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>fieldID</name>
      <anchorfile>classfei_1_1ConnectivityBlock.html</anchorfile>
      <anchor>a76faad363eee0abeeb258bf3c26c9af5</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ConnectivityTable</name>
    <filename>classConnectivityTable.html</filename>
  </compound>
  <compound kind="class">
    <name>fei::ParameterSet::const_iterator</name>
    <filename>classfei_1_1ParameterSet_1_1const__iterator.html</filename>
    <member kind="function">
      <type></type>
      <name>const_iterator</name>
      <anchorfile>classfei_1_1ParameterSet_1_1const__iterator.html</anchorfile>
      <anchor>a281a44ca8a7a3424ced84afecb61246b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>const_iterator</name>
      <anchorfile>classfei_1_1ParameterSet_1_1const__iterator.html</anchorfile>
      <anchor>aafbf8967ffcbbeb3ea23a80ea4ecdbaf</anchor>
      <arglist>(int offset, std::vector&lt; const Param * &gt; *params)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~const_iterator</name>
      <anchorfile>classfei_1_1ParameterSet_1_1const__iterator.html</anchorfile>
      <anchor>ad39728c1b73c1563c55165b410d51644</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const Param &amp;</type>
      <name>operator*</name>
      <anchorfile>classfei_1_1ParameterSet_1_1const__iterator.html</anchorfile>
      <anchor>ab40e89da77fbf9838fa191e93968ad78</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const_iterator &amp;</type>
      <name>operator++</name>
      <anchorfile>classfei_1_1ParameterSet_1_1const__iterator.html</anchorfile>
      <anchor>af8cf3f82a94e2f8803a5ed0d5b514a61</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const_iterator &amp;</type>
      <name>operator=</name>
      <anchorfile>classfei_1_1ParameterSet_1_1const__iterator.html</anchorfile>
      <anchor>add87e84234dbee72275907c8637519bd</anchor>
      <arglist>(const const_iterator &amp;src)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator==</name>
      <anchorfile>classfei_1_1ParameterSet_1_1const__iterator.html</anchorfile>
      <anchor>a2d095709c7ef3f9a10cb30343e58a1b7</anchor>
      <arglist>(const const_iterator &amp;rhs)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator!=</name>
      <anchorfile>classfei_1_1ParameterSet_1_1const__iterator.html</anchorfile>
      <anchor>ac7961bae2324a16e7efcd69bdbb36d94</anchor>
      <arglist>(const const_iterator &amp;rhs)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>fei::ctg_set::const_iterator</name>
    <filename>classfei_1_1ctg__set_1_1const__iterator.html</filename>
    <member kind="function">
      <type></type>
      <name>const_iterator</name>
      <anchorfile>classfei_1_1ctg__set_1_1const__iterator.html</anchorfile>
      <anchor>a9f08d995d44c10da75bdbf075047628a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>const_iterator</name>
      <anchorfile>classfei_1_1ctg__set_1_1const__iterator.html</anchorfile>
      <anchor>a804dca4bb04c0d44449742ee5e448036</anchor>
      <arglist>(const ctg_set&lt; T &gt; *_set, const T &amp;val, int i)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>const_iterator</name>
      <anchorfile>classfei_1_1ctg__set_1_1const__iterator.html</anchorfile>
      <anchor>a58554585fae8596fec7d59af5385cf80</anchor>
      <arglist>(const const_iterator &amp;src)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~const_iterator</name>
      <anchorfile>classfei_1_1ctg__set_1_1const__iterator.html</anchorfile>
      <anchor>a08f024feeb16302c7065c9dff6ae9544</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const T &amp;</type>
      <name>operator*</name>
      <anchorfile>classfei_1_1ctg__set_1_1const__iterator.html</anchorfile>
      <anchor>a19e73d25ac66127e250d67dd6b05aeb7</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const_iterator &amp;</type>
      <name>operator++</name>
      <anchorfile>classfei_1_1ctg__set_1_1const__iterator.html</anchorfile>
      <anchor>ad2f047c5285bda293f838154bf7be612</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const_iterator &amp;</type>
      <name>operator=</name>
      <anchorfile>classfei_1_1ctg__set_1_1const__iterator.html</anchorfile>
      <anchor>abbe9c65f0fe261398875b3492ee110b5</anchor>
      <arglist>(const const_iterator &amp;src)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator==</name>
      <anchorfile>classfei_1_1ctg__set_1_1const__iterator.html</anchorfile>
      <anchor>a611a18eb132cc071f73c2c442b510169</anchor>
      <arglist>(const const_iterator &amp;rhs)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator!=</name>
      <anchorfile>classfei_1_1ctg__set_1_1const__iterator.html</anchorfile>
      <anchor>a87375ef1592f0e743fb761a7fe484ec1</anchor>
      <arglist>(const const_iterator &amp;rhs)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>snl_fei::Constraint</name>
    <filename>classsnl__fei_1_1Constraint.html</filename>
    <templarg>RecordType</templarg>
    <member kind="function">
      <type></type>
      <name>Constraint</name>
      <anchorfile>classsnl__fei_1_1Constraint.html</anchorfile>
      <anchor>a7df17aa5b2566eee4d239512a5116474</anchor>
      <arglist>(int id=0, bool isPenaltyConstr=false)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Constraint</name>
      <anchorfile>classsnl__fei_1_1Constraint.html</anchorfile>
      <anchor>ac4ba49952d227c48e7611911ebe81f26</anchor>
      <arglist>(int id, int constraintIDType, bool isSlave, bool isPenaltyConstr, int numIDs, const int *idTypes, const int *IDs, const int *fieldIDs, int offsetOfSlave, int offsetIntoSlaveField, const double *weights, double rhsValue, fei::VectorSpace *vspace)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~Constraint</name>
      <anchorfile>classsnl__fei_1_1Constraint.html</anchorfile>
      <anchor>a3681fc6db62f2082e1e5c45a9fc45ddd</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getConstraintID</name>
      <anchorfile>classsnl__fei_1_1Constraint.html</anchorfile>
      <anchor>a39bb8a1fec531c754dd5b9926240dafd</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setConstraintID</name>
      <anchorfile>classsnl__fei_1_1Constraint.html</anchorfile>
      <anchor>a462846793ab457798e296d380a272704</anchor>
      <arglist>(int id)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getIDType</name>
      <anchorfile>classsnl__fei_1_1Constraint.html</anchorfile>
      <anchor>a44d333de1fb83ed233372eb8d3918aa9</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setIDType</name>
      <anchorfile>classsnl__fei_1_1Constraint.html</anchorfile>
      <anchor>a328b79952b88acbf76430eed18481a2f</anchor>
      <arglist>(int idType)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isPenalty</name>
      <anchorfile>classsnl__fei_1_1Constraint.html</anchorfile>
      <anchor>a5c57e445912bbf725281cf9361ad007d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setIsPenalty</name>
      <anchorfile>classsnl__fei_1_1Constraint.html</anchorfile>
      <anchor>a9232eee85e15e0e862a160c152f5b54a</anchor>
      <arglist>(bool isPenaltyConstr)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getEqnNumber</name>
      <anchorfile>classsnl__fei_1_1Constraint.html</anchorfile>
      <anchor>ae2710b4c280815763bbb30864d5d43e0</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setEqnNumber</name>
      <anchorfile>classsnl__fei_1_1Constraint.html</anchorfile>
      <anchor>a04be55c972fe3684a9423d6f135c15cf</anchor>
      <arglist>(int eqn)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getBlkEqnNumber</name>
      <anchorfile>classsnl__fei_1_1Constraint.html</anchorfile>
      <anchor>adf8b520642a1afaf401b22a31f80c206</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setBlkEqnNumber</name>
      <anchorfile>classsnl__fei_1_1Constraint.html</anchorfile>
      <anchor>a658c6f75ccc0c6fd83e1cf4251e24897</anchor>
      <arglist>(int blkEqn)</arglist>
    </member>
    <member kind="function">
      <type>RecordType</type>
      <name>getSlave</name>
      <anchorfile>classsnl__fei_1_1Constraint.html</anchorfile>
      <anchor>a8614700c981eda559786e88420033f79</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setSlave</name>
      <anchorfile>classsnl__fei_1_1Constraint.html</anchorfile>
      <anchor>a78a6a1dc829464523dd4bd19778c563d</anchor>
      <arglist>(int slv)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getSlaveFieldID</name>
      <anchorfile>classsnl__fei_1_1Constraint.html</anchorfile>
      <anchor>a1203744d97749ebe790200003b549e21</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setSlaveFieldID</name>
      <anchorfile>classsnl__fei_1_1Constraint.html</anchorfile>
      <anchor>a97bb29627cf1c1970efad28016e3fd98</anchor>
      <arglist>(int f)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getOffsetIntoSlaveField</name>
      <anchorfile>classsnl__fei_1_1Constraint.html</anchorfile>
      <anchor>a5032e0d68e84f9b33f0e347d141a1818</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setOffsetIntoSlaveField</name>
      <anchorfile>classsnl__fei_1_1Constraint.html</anchorfile>
      <anchor>a6a02e3b444301d0c54981247960bcbc9</anchor>
      <arglist>(int offset)</arglist>
    </member>
    <member kind="function">
      <type>std::vector&lt; int &gt; &amp;</type>
      <name>getMasters</name>
      <anchorfile>classsnl__fei_1_1Constraint.html</anchorfile>
      <anchor>a143adf73f2f883f5d95b248e16eae441</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>std::vector&lt; int &gt; &amp;</type>
      <name>getMasterIDTypes</name>
      <anchorfile>classsnl__fei_1_1Constraint.html</anchorfile>
      <anchor>ac3fdaff7a97852276cd9b232adb6578a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>std::vector&lt; snl_fei::RecordCollection * &gt; &amp;</type>
      <name>getMasterRecordCollections</name>
      <anchorfile>classsnl__fei_1_1Constraint.html</anchorfile>
      <anchor>a921d58b76f82fb08fd327fd4eb856283</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>std::vector&lt; int &gt; &amp;</type>
      <name>getMasterFieldIDs</name>
      <anchorfile>classsnl__fei_1_1Constraint.html</anchorfile>
      <anchor>aa9fb4f0c78020244a8cd1143d5d60175</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>std::vector&lt; double &gt; &amp;</type>
      <name>getMasterWeights</name>
      <anchorfile>classsnl__fei_1_1Constraint.html</anchorfile>
      <anchor>ac2a155355e0acc20761ab8c79a1a0a13</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>getRHSValue</name>
      <anchorfile>classsnl__fei_1_1Constraint.html</anchorfile>
      <anchor>a84a7e9aa78ec1f1d51d3efed98879182</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setRHSValue</name>
      <anchorfile>classsnl__fei_1_1Constraint.html</anchorfile>
      <anchor>a8db8c7e254d672dcb6520878baa05575</anchor>
      <arglist>(double rhs)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator!=</name>
      <anchorfile>classsnl__fei_1_1Constraint.html</anchorfile>
      <anchor>a51e8706c07111dde2668f8d405190cea</anchor>
      <arglist>(const Constraint&lt; RecordType &gt; &amp;rhs)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>structurallySame</name>
      <anchorfile>classsnl__fei_1_1Constraint.html</anchorfile>
      <anchor>a34b5a7fbbbd1e8f60216b2b9c2acf2c9</anchor>
      <arglist>(const Constraint&lt; RecordType &gt; &amp;rhs)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>CRSet</name>
    <filename>classCRSet.html</filename>
    <member kind="function">
      <type></type>
      <name>CRSet</name>
      <anchorfile>classCRSet.html</anchorfile>
      <anchor>a5e8658c2e0739d9ae59678c3f414c802</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~CRSet</name>
      <anchorfile>classCRSet.html</anchorfile>
      <anchor>a2976dd55c67d6f3d80d176964f87273b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>crID_</name>
      <anchorfile>classCRSet.html</anchorfile>
      <anchor>a8101eb6d21cef70b4bc5c22b4eab58d8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>numNodes_</name>
      <anchorfile>classCRSet.html</anchorfile>
      <anchor>af74d8a9d3126f95e2030e0b5d550cdb8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>GlobalID</type>
      <name>slaveNodeID_</name>
      <anchorfile>classCRSet.html</anchorfile>
      <anchor>ab9bc374f932a9ce5c575f43ec033004f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>slaveFieldID_</name>
      <anchorfile>classCRSet.html</anchorfile>
      <anchor>a95211ac551bb41e5f21e8b61d4a79a01</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>slaveOffset_</name>
      <anchorfile>classCRSet.html</anchorfile>
      <anchor>a6b096ddb6a9ef204a849f967e92c3496</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>fei::CSRMat</name>
    <filename>classfei_1_1CSRMat.html</filename>
  </compound>
  <compound kind="class">
    <name>fei::CSVec</name>
    <filename>classfei_1_1CSVec.html</filename>
  </compound>
  <compound kind="class">
    <name>fei::ctg_set</name>
    <filename>classfei_1_1ctg__set.html</filename>
    <templarg>T</templarg>
    <class kind="class">fei::ctg_set::const_iterator</class>
    <member kind="typedef">
      <type>T</type>
      <name>key_type</name>
      <anchorfile>classfei_1_1ctg__set.html</anchorfile>
      <anchor>a0d1538025441498593e62614c7854460</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ctg_set</name>
      <anchorfile>classfei_1_1ctg__set.html</anchorfile>
      <anchor>a5287f1f7c69891c2d447e00010356a33</anchor>
      <arglist>(int alloc_incr=32)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ctg_set</name>
      <anchorfile>classfei_1_1ctg__set.html</anchorfile>
      <anchor>a17ba432217d2d9c75f54202e53a3b777</anchor>
      <arglist>(const ctg_set&lt; T &gt; &amp;src)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~ctg_set</name>
      <anchorfile>classfei_1_1ctg__set.html</anchorfile>
      <anchor>a8dd00fa02cc268accd698f6f3acfa549</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const_iterator</type>
      <name>begin</name>
      <anchorfile>classfei_1_1ctg__set.html</anchorfile>
      <anchor>a3482c7ce9b5ef92e9372a7d40815e10c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>ctg_set&lt; T &gt; &amp;</type>
      <name>operator=</name>
      <anchorfile>classfei_1_1ctg__set.html</anchorfile>
      <anchor>a94adec3110bcdad78450b25db79c86a5</anchor>
      <arglist>(const ctg_set&lt; T &gt; &amp;src)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator!=</name>
      <anchorfile>classfei_1_1ctg__set.html</anchorfile>
      <anchor>a12c1a2d6a77abe7d53bd931a4c5f50a1</anchor>
      <arglist>(const ctg_set&lt; T &gt; &amp;rhs)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>clear</name>
      <anchorfile>classfei_1_1ctg__set.html</anchorfile>
      <anchor>a3822c6f193b8d0565979fcb782efdf54</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>std::pair&lt; const_iterator, bool &gt;</type>
      <name>insert</name>
      <anchorfile>classfei_1_1ctg__set.html</anchorfile>
      <anchor>a876587d03d182da14abe54c819012979</anchor>
      <arglist>(const T &amp;item)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>insert2</name>
      <anchorfile>classfei_1_1ctg__set.html</anchorfile>
      <anchor>aca5afa2cbb20e1b3dc6bdd1ed74d4d2d</anchor>
      <arglist>(const T &amp;item)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>insert2_dense_group</name>
      <anchorfile>classfei_1_1ctg__set.html</anchorfile>
      <anchor>a1b370474d446accd612c3592250bd522</anchor>
      <arglist>(const T &amp;starting_index, int group_size)</arglist>
    </member>
    <member kind="function">
      <type>const_iterator</type>
      <name>find</name>
      <anchorfile>classfei_1_1ctg__set.html</anchorfile>
      <anchor>a7f48627b0552a6e1c0765f8302028d7a</anchor>
      <arglist>(const T &amp;item)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>copy_to_array</name>
      <anchorfile>classfei_1_1ctg__set.html</anchorfile>
      <anchor>a4788413435501841f9727688d623c500</anchor>
      <arglist>(int len, T *items) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>copy_to_vector</name>
      <anchorfile>classfei_1_1ctg__set.html</anchorfile>
      <anchor>a5e87405f00bf06280904d35d57bce986</anchor>
      <arglist>(std::vector&lt; T &gt; &amp;items) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>size</name>
      <anchorfile>classfei_1_1ctg__set.html</anchorfile>
      <anchor>a957f1db42adea9a8985e35055c048408</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" static="yes">
      <type>static const_iterator</type>
      <name>end</name>
      <anchorfile>classfei_1_1ctg__set.html</anchorfile>
      <anchor>a61bc3a895a2bbad451dfb286e8137de7</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ctg_set&lt; int &gt;</name>
    <filename>classfei_1_1ctg__set.html</filename>
    <member kind="typedef">
      <type>int</type>
      <name>key_type</name>
      <anchorfile>classfei_1_1ctg__set.html</anchorfile>
      <anchor>a0d1538025441498593e62614c7854460</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ctg_set</name>
      <anchorfile>classfei_1_1ctg__set.html</anchorfile>
      <anchor>a5287f1f7c69891c2d447e00010356a33</anchor>
      <arglist>(int alloc_incr=32)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ctg_set</name>
      <anchorfile>classfei_1_1ctg__set.html</anchorfile>
      <anchor>a17ba432217d2d9c75f54202e53a3b777</anchor>
      <arglist>(const ctg_set&lt; int &gt; &amp;src)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~ctg_set</name>
      <anchorfile>classfei_1_1ctg__set.html</anchorfile>
      <anchor>a8dd00fa02cc268accd698f6f3acfa549</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const_iterator</type>
      <name>begin</name>
      <anchorfile>classfei_1_1ctg__set.html</anchorfile>
      <anchor>a3482c7ce9b5ef92e9372a7d40815e10c</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>ctg_set&lt; int &gt; &amp;</type>
      <name>operator=</name>
      <anchorfile>classfei_1_1ctg__set.html</anchorfile>
      <anchor>a94adec3110bcdad78450b25db79c86a5</anchor>
      <arglist>(const ctg_set&lt; int &gt; &amp;src)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator!=</name>
      <anchorfile>classfei_1_1ctg__set.html</anchorfile>
      <anchor>a12c1a2d6a77abe7d53bd931a4c5f50a1</anchor>
      <arglist>(const ctg_set&lt; int &gt; &amp;rhs)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>clear</name>
      <anchorfile>classfei_1_1ctg__set.html</anchorfile>
      <anchor>a3822c6f193b8d0565979fcb782efdf54</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>std::pair&lt; const_iterator, bool &gt;</type>
      <name>insert</name>
      <anchorfile>classfei_1_1ctg__set.html</anchorfile>
      <anchor>a876587d03d182da14abe54c819012979</anchor>
      <arglist>(const int &amp;item)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>insert2</name>
      <anchorfile>classfei_1_1ctg__set.html</anchorfile>
      <anchor>aca5afa2cbb20e1b3dc6bdd1ed74d4d2d</anchor>
      <arglist>(const int &amp;item)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>insert2_dense_group</name>
      <anchorfile>classfei_1_1ctg__set.html</anchorfile>
      <anchor>a1b370474d446accd612c3592250bd522</anchor>
      <arglist>(const int &amp;starting_index, int group_size)</arglist>
    </member>
    <member kind="function">
      <type>const_iterator</type>
      <name>find</name>
      <anchorfile>classfei_1_1ctg__set.html</anchorfile>
      <anchor>a7f48627b0552a6e1c0765f8302028d7a</anchor>
      <arglist>(const int &amp;item)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>copy_to_array</name>
      <anchorfile>classfei_1_1ctg__set.html</anchorfile>
      <anchor>a4788413435501841f9727688d623c500</anchor>
      <arglist>(int len, int *items) const</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>copy_to_vector</name>
      <anchorfile>classfei_1_1ctg__set.html</anchorfile>
      <anchor>a5e87405f00bf06280904d35d57bce986</anchor>
      <arglist>(std::vector&lt; int &gt; &amp;items) const</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>size</name>
      <anchorfile>classfei_1_1ctg__set.html</anchorfile>
      <anchor>a957f1db42adea9a8985e35055c048408</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static const_iterator</type>
      <name>end</name>
      <anchorfile>classfei_1_1ctg__set.html</anchorfile>
      <anchor>a61bc3a895a2bbad451dfb286e8137de7</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Data</name>
    <filename>classData.html</filename>
    <member kind="function">
      <type></type>
      <name>Data</name>
      <anchorfile>classData.html</anchorfile>
      <anchor>af11f741cb7f587e2e495452a8905a22a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~Data</name>
      <anchorfile>classData.html</anchorfile>
      <anchor>a8c4dbe720325cd952ec9146114f22d35</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setTypeName</name>
      <anchorfile>classData.html</anchorfile>
      <anchor>a6007105a49b8a9c35e01f5c5fffcbcd1</anchor>
      <arglist>(const char *name)</arglist>
    </member>
    <member kind="function">
      <type>const char *</type>
      <name>getTypeName</name>
      <anchorfile>classData.html</anchorfile>
      <anchor>ae9faf9a743087db793dd67451562b60a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setDataPtr</name>
      <anchorfile>classData.html</anchorfile>
      <anchor>a045f799f00fc0ac4955dad39e45f8071</anchor>
      <arglist>(void *ptr)</arglist>
    </member>
    <member kind="function">
      <type>void *</type>
      <name>getDataPtr</name>
      <anchorfile>classData.html</anchorfile>
      <anchor>a729cfe6ed4ed219307153c9a7914115f</anchor>
      <arglist>() const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>fei::Dof</name>
    <filename>classfei_1_1Dof.html</filename>
    <templarg>LocalOrdinal</templarg>
    <templarg>GlobalOrdinal</templarg>
    <member kind="function">
      <type></type>
      <name>Dof</name>
      <anchorfile>classfei_1_1Dof.html</anchorfile>
      <anchor>ad60ac5db740264323cb26acc358dcd1a</anchor>
      <arglist>(LocalOrdinal rank, GlobalOrdinal id, LocalOrdinal field)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~Dof</name>
      <anchorfile>classfei_1_1Dof.html</anchorfile>
      <anchor>a855d743fa8d7156e674d982d81615c3a</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>fei::DofMapper</name>
    <filename>classfei_1_1DofMapper.html</filename>
    <templarg>LocalOrdinal</templarg>
    <templarg>GlobalOrdinal</templarg>
    <templarg>DofOrder</templarg>
    <member kind="function">
      <type></type>
      <name>DofMapper</name>
      <anchorfile>classfei_1_1DofMapper.html</anchorfile>
      <anchor>a44f66df4df371d656ae4e97605b9915c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~DofMapper</name>
      <anchorfile>classfei_1_1DofMapper.html</anchorfile>
      <anchor>a3123066d76dc19d526605272280eb994</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setFieldSize</name>
      <anchorfile>classfei_1_1DofMapper.html</anchorfile>
      <anchor>a5736e05590aa24c05264451306af97ca</anchor>
      <arglist>(LocalOrdinal field, LocalOrdinal field_size)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>EqnBuffer</name>
    <filename>classEqnBuffer.html</filename>
    <member kind="function">
      <type></type>
      <name>EqnBuffer</name>
      <anchorfile>classEqnBuffer.html</anchorfile>
      <anchor>ac1331f22094d895a1df6551f32e3b3e8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>EqnBuffer</name>
      <anchorfile>classEqnBuffer.html</anchorfile>
      <anchor>aa63e71b2c15a78312c65ecb43ed5badd</anchor>
      <arglist>(const EqnBuffer &amp;src)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~EqnBuffer</name>
      <anchorfile>classEqnBuffer.html</anchorfile>
      <anchor>a450ccb185137763247a78c6abec69802</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>EqnBuffer *</type>
      <name>deepCopy</name>
      <anchorfile>classEqnBuffer.html</anchorfile>
      <anchor>a122228eecaae5356f0345255a6a4c8dc</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>EqnBuffer &amp;</type>
      <name>operator=</name>
      <anchorfile>classEqnBuffer.html</anchorfile>
      <anchor>ac34f4ca3c1d2f021b30d22a6f9537b8b</anchor>
      <arglist>(const EqnBuffer &amp;src)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getNumEqns</name>
      <anchorfile>classEqnBuffer.html</anchorfile>
      <anchor>a07202084cecf51238a2ffb96fa114165</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>std::vector&lt; int &gt; &amp;</type>
      <name>eqnNumbers</name>
      <anchorfile>classEqnBuffer.html</anchorfile>
      <anchor>a4d3b648c76d6947ca4a56199eac1f66b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>std::vector&lt; fei::CSVec * &gt; &amp;</type>
      <name>eqns</name>
      <anchorfile>classEqnBuffer.html</anchorfile>
      <anchor>a00319869f17cb08a4d7af99a8c9f82cc</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getNumRHSs</name>
      <anchorfile>classEqnBuffer.html</anchorfile>
      <anchor>a4500c75820e40ebe57ec4fe60acbc49d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setNumRHSs</name>
      <anchorfile>classEqnBuffer.html</anchorfile>
      <anchor>a321abe0d669f6cf6559c7436a0092ab4</anchor>
      <arglist>(int n)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>addRHS</name>
      <anchorfile>classEqnBuffer.html</anchorfile>
      <anchor>aadfdf4ad54abe02dd8926a1049888e38</anchor>
      <arglist>(int eqnNumber, int rhsIndex, double value, bool accumulate=true)</arglist>
    </member>
    <member kind="function">
      <type>std::vector&lt; std::vector&lt; double &gt; * &gt; *</type>
      <name>rhsCoefsPtr</name>
      <anchorfile>classEqnBuffer.html</anchorfile>
      <anchor>a1e2c94768b36df6dea98092c93edb0c1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getEqnIndex</name>
      <anchorfile>classEqnBuffer.html</anchorfile>
      <anchor>ad00d06024037c948955291051cdee5ed</anchor>
      <arglist>(int eqn)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>isInIndices</name>
      <anchorfile>classEqnBuffer.html</anchorfile>
      <anchor>a309bed42afa8ab22ee708c175a43616b</anchor>
      <arglist>(int eqn)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>addEqn</name>
      <anchorfile>classEqnBuffer.html</anchorfile>
      <anchor>aaceb2d4269ff801fc3c2ad03e244d977</anchor>
      <arglist>(int eqnNumber, const double *coefs, const int *indices, int len, bool accumulate, bool create_indices_union=false)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>addEqns</name>
      <anchorfile>classEqnBuffer.html</anchorfile>
      <anchor>a83a2f16c46f706f4ac41e288a6b58cf4</anchor>
      <arglist>(EqnBuffer &amp;inputEqns, bool accumulate)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getCoef</name>
      <anchorfile>classEqnBuffer.html</anchorfile>
      <anchor>ac69d90b4b7c6c430fd507024cfc5f7a3</anchor>
      <arglist>(int eqnNumber, int colIndex, double &amp;coef)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>removeIndex</name>
      <anchorfile>classEqnBuffer.html</anchorfile>
      <anchor>a87e09dac7d0ec88194c2ff2d63da6c68</anchor>
      <arglist>(int eqnNumber, int colIndex)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getCoefAndRemoveIndex</name>
      <anchorfile>classEqnBuffer.html</anchorfile>
      <anchor>a3a00da8b418d4a11a558cc7b40ba7709</anchor>
      <arglist>(int eqnNumber, int colIndex, double &amp;coef)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>resetCoefs</name>
      <anchorfile>classEqnBuffer.html</anchorfile>
      <anchor>a16eb417a502dadd1a5c6d69051006d88</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>addIndices</name>
      <anchorfile>classEqnBuffer.html</anchorfile>
      <anchor>aeaa499d3ec0d888880077fc9c06096ee</anchor>
      <arglist>(int eqnNumber, const int *indices, int len)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>EqnCommMgr</name>
    <filename>classEqnCommMgr.html</filename>
    <member kind="function">
      <type></type>
      <name>EqnCommMgr</name>
      <anchorfile>classEqnCommMgr.html</anchorfile>
      <anchor>a0c78bd49a5f3b13694df31612b71dd8e</anchor>
      <arglist>(MPI_Comm comm, bool accumulate=true)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>EqnCommMgr</name>
      <anchorfile>classEqnCommMgr.html</anchorfile>
      <anchor>ab83bb84605df50bd7ad31ee5223f57f2</anchor>
      <arglist>(const EqnCommMgr &amp;src)</arglist>
    </member>
    <member kind="function">
      <type>EqnCommMgr &amp;</type>
      <name>operator=</name>
      <anchorfile>classEqnCommMgr.html</anchorfile>
      <anchor>aa7c408257468409e8f80dc5b8be8ad8e</anchor>
      <arglist>(const EqnCommMgr &amp;src)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~EqnCommMgr</name>
      <anchorfile>classEqnCommMgr.html</anchorfile>
      <anchor>acd9e5c5645787e096fc43f1f3f8dddf2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>EqnCommMgr *</type>
      <name>deepCopy</name>
      <anchorfile>classEqnCommMgr.html</anchorfile>
      <anchor>a777424257542964f11e03bbbd32f3ba5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>size_t</type>
      <name>getNumSharingProcs</name>
      <anchorfile>classEqnCommMgr.html</anchorfile>
      <anchor>ad98711dbef511095736e69b704b7cb98</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>size_t</type>
      <name>getNumOwnerProcs</name>
      <anchorfile>classEqnCommMgr.html</anchorfile>
      <anchor>a49de10884c5f7c118ac48a0dd932d2b2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>addLocalEqn</name>
      <anchorfile>classEqnCommMgr.html</anchorfile>
      <anchor>a5145319550c0a46f669a418791e32b32</anchor>
      <arglist>(int eqnNumber, int srcProc)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>mirrorProcEqns</name>
      <anchorfile>classEqnCommMgr.html</anchorfile>
      <anchor>a8d541ad93e43b2c9cfe907b9701b0e6f</anchor>
      <arglist>(ProcEqns &amp;inProcEqns, ProcEqns &amp;outProcEqns)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>mirrorProcEqnLengths</name>
      <anchorfile>classEqnCommMgr.html</anchorfile>
      <anchor>a8e57401e7c5b7c3cd88677dfbd0440b3</anchor>
      <arglist>(ProcEqns &amp;inProcEqns, ProcEqns &amp;outProcEqns)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>fei::EqnRecord</name>
    <filename>structfei_1_1EqnRecord.html</filename>
    <member kind="variable">
      <type>int</type>
      <name>global_eqn</name>
      <anchorfile>structfei_1_1EqnRecord.html</anchorfile>
      <anchor>a586bc2073cfc8908111f48fc293659a9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>IDType</name>
      <anchorfile>structfei_1_1EqnRecord.html</anchorfile>
      <anchor>a019f0bcf67c505d9034b2bfa8c8caa32</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>ID</name>
      <anchorfile>structfei_1_1EqnRecord.html</anchorfile>
      <anchor>a948d000453745dcaea11212e80dcb99c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>fieldID</name>
      <anchorfile>structfei_1_1EqnRecord.html</anchorfile>
      <anchor>ab99f89ae7887854c740b20ede71a36ee</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>offset</name>
      <anchorfile>structfei_1_1EqnRecord.html</anchorfile>
      <anchor>a02cddef8d0a8df299460078616ccb3d4</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>fei::Matrix::Factory</name>
    <filename>classfei_1_1Matrix_1_1Factory.html</filename>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~Factory</name>
      <anchorfile>classfei_1_1Matrix_1_1Factory.html</anchorfile>
      <anchor>a960b462907d53f5d118a90c8f3ce7d4e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual fei::SharedPtr&lt; fei::Matrix &gt;</type>
      <name>createMatrix</name>
      <anchorfile>classfei_1_1Matrix_1_1Factory.html</anchorfile>
      <anchor>a960d7afc2216a6fd7bad8d47c70613e5</anchor>
      <arglist>(fei::SharedPtr&lt; fei::MatrixGraph &gt; matrixGraph)=0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>fei::MatrixGraph::Factory</name>
    <filename>classfei_1_1MatrixGraph_1_1Factory.html</filename>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~Factory</name>
      <anchorfile>classfei_1_1MatrixGraph_1_1Factory.html</anchorfile>
      <anchor>ac4fb5422aa2866fbbba2994adaa57820</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual fei::SharedPtr&lt; fei::MatrixGraph &gt;</type>
      <name>createMatrixGraph</name>
      <anchorfile>classfei_1_1MatrixGraph_1_1Factory.html</anchorfile>
      <anchor>a89e13bd572bba38a58f794865abab4a6</anchor>
      <arglist>(fei::SharedPtr&lt; fei::VectorSpace &gt; rowSpace, fei::SharedPtr&lt; fei::VectorSpace &gt; columnSpace, const char *name)=0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>fei::MatrixGraph_Impl2::Factory</name>
    <filename>classfei_1_1MatrixGraph__Impl2_1_1Factory.html</filename>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~Factory</name>
      <anchorfile>classfei_1_1MatrixGraph__Impl2_1_1Factory.html</anchorfile>
      <anchor>a47dee022c30f2f015007b912ef6c4b4d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual fei::SharedPtr&lt; fei::MatrixGraph &gt;</type>
      <name>createMatrixGraph</name>
      <anchorfile>classfei_1_1MatrixGraph__Impl2_1_1Factory.html</anchorfile>
      <anchor>a0f39b3e2fbbf7c4bde521a1c01d17fff</anchor>
      <arglist>(fei::SharedPtr&lt; fei::VectorSpace &gt; rowSpace, fei::SharedPtr&lt; fei::VectorSpace &gt; columnSpace, const char *name)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>fei::Solver::Factory</name>
    <filename>classfei_1_1Solver_1_1Factory.html</filename>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~Factory</name>
      <anchorfile>classfei_1_1Solver_1_1Factory.html</anchorfile>
      <anchor>a1661bbca5e203110c231d31af2c1d01b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual fei::SharedPtr&lt; fei::Solver &gt;</type>
      <name>createSolver</name>
      <anchorfile>classfei_1_1Solver_1_1Factory.html</anchorfile>
      <anchor>aa917885a1b9b408168d80c9e23dbb6c5</anchor>
      <arglist>(const char *name=0)=0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>fei::Vector::Factory</name>
    <filename>classfei_1_1Vector_1_1Factory.html</filename>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~Factory</name>
      <anchorfile>classfei_1_1Vector_1_1Factory.html</anchorfile>
      <anchor>af9683a1585927e7442d6c7c4f56c5ced</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual fei::SharedPtr&lt; fei::Vector &gt;</type>
      <name>createVector</name>
      <anchorfile>classfei_1_1Vector_1_1Factory.html</anchorfile>
      <anchor>a0c7dc506c0054aae6517ba1e0bec038c</anchor>
      <arglist>(fei::SharedPtr&lt; fei::VectorSpace &gt; vecSpace, int numVectors=1)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual fei::SharedPtr&lt; fei::Vector &gt;</type>
      <name>createVector</name>
      <anchorfile>classfei_1_1Vector_1_1Factory.html</anchorfile>
      <anchor>ab7d49c2c972a7341331d46d278c4c044</anchor>
      <arglist>(fei::SharedPtr&lt; fei::VectorSpace &gt; vecSpace, bool isSolutionVector, int numVectors=1)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual fei::SharedPtr&lt; fei::Vector &gt;</type>
      <name>createVector</name>
      <anchorfile>classfei_1_1Vector_1_1Factory.html</anchorfile>
      <anchor>a51013d4e1a2bbbf99244149720fee92d</anchor>
      <arglist>(fei::SharedPtr&lt; fei::MatrixGraph &gt; matrixGraph, int numVectors=1)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual fei::SharedPtr&lt; fei::Vector &gt;</type>
      <name>createVector</name>
      <anchorfile>classfei_1_1Vector_1_1Factory.html</anchorfile>
      <anchor>a457ee50fc490cea9b1e7d90a095732ec</anchor>
      <arglist>(fei::SharedPtr&lt; fei::MatrixGraph &gt; matrixGraph, bool isSolutionVector, int numVectors=1)=0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>fei::VectorSpace::Factory</name>
    <filename>classfei_1_1VectorSpace_1_1Factory.html</filename>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~Factory</name>
      <anchorfile>classfei_1_1VectorSpace_1_1Factory.html</anchorfile>
      <anchor>a71147be7a05fc415d9c475079cf7a49e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual fei::SharedPtr&lt; VectorSpace &gt;</type>
      <name>createVectorSpace</name>
      <anchorfile>classfei_1_1VectorSpace_1_1Factory.html</anchorfile>
      <anchor>a188c45dbadac9727604c4bc22efc3f8c</anchor>
      <arglist>(MPI_Comm, const char *name)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>snl_fei::Factory</name>
    <filename>classsnl__fei_1_1Factory.html</filename>
    <base virtualness="virtual">fei::Factory</base>
    <member kind="function">
      <type></type>
      <name>Factory</name>
      <anchorfile>classsnl__fei_1_1Factory.html</anchorfile>
      <anchor>a636f874c4967aab68a123f63fd7a23de</anchor>
      <arglist>(MPI_Comm comm, fei::SharedPtr&lt; LibraryWrapper &gt; wrapper)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Factory</name>
      <anchorfile>classsnl__fei_1_1Factory.html</anchorfile>
      <anchor>a57369150a1c9ba2eeb49f8c9a9fbbb52</anchor>
      <arglist>(MPI_Comm comm, fei::SharedPtr&lt; LinearSystemCore &gt; lsc)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Factory</name>
      <anchorfile>classsnl__fei_1_1Factory.html</anchorfile>
      <anchor>a20308d5c4ed73d500ff8892975aa8fac</anchor>
      <arglist>(MPI_Comm comm, fei::SharedPtr&lt; FiniteElementData &gt; feData, int nodeIDType)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~Factory</name>
      <anchorfile>classsnl__fei_1_1Factory.html</anchorfile>
      <anchor>a7109de010426664c6d7284a5f598d8cc</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>fei::SharedPtr&lt; fei::Factory &gt;</type>
      <name>clone</name>
      <anchorfile>classsnl__fei_1_1Factory.html</anchorfile>
      <anchor>af531d974dd8962086c490a6b7914bc0b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>parameters</name>
      <anchorfile>classsnl__fei_1_1Factory.html</anchorfile>
      <anchor>afd83ca98fab6e8297d23a5dcc3dd9647</anchor>
      <arglist>(const fei::ParameterSet &amp;parameterset)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual fei::SharedPtr&lt; fei::MatrixGraph &gt;</type>
      <name>createMatrixGraph</name>
      <anchorfile>classsnl__fei_1_1Factory.html</anchorfile>
      <anchor>a7ffdc09e12f24152bca8b26c5f532b47</anchor>
      <arglist>(fei::SharedPtr&lt; fei::VectorSpace &gt; rowSpace, fei::SharedPtr&lt; fei::VectorSpace &gt; columnSpace, const char *name)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual fei::SharedPtr&lt; fei::Vector &gt;</type>
      <name>createVector</name>
      <anchorfile>classsnl__fei_1_1Factory.html</anchorfile>
      <anchor>a4d5528ed7e2e023a30a974dd71e35702</anchor>
      <arglist>(fei::SharedPtr&lt; fei::VectorSpace &gt; vecSpace, int numVectors=1)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual fei::SharedPtr&lt; fei::Vector &gt;</type>
      <name>createVector</name>
      <anchorfile>classsnl__fei_1_1Factory.html</anchorfile>
      <anchor>a8dde1d4eab1fd73d0eb3ee25ab714f9e</anchor>
      <arglist>(fei::SharedPtr&lt; fei::VectorSpace &gt; vecSpace, bool isSolutionVector, int numVectors=1)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual fei::SharedPtr&lt; fei::Vector &gt;</type>
      <name>createVector</name>
      <anchorfile>classsnl__fei_1_1Factory.html</anchorfile>
      <anchor>ac965eb61cb5a17d42683628e42daeb78</anchor>
      <arglist>(fei::SharedPtr&lt; fei::MatrixGraph &gt; matrixGraph, int numVectors=1)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual fei::SharedPtr&lt; fei::Vector &gt;</type>
      <name>createVector</name>
      <anchorfile>classsnl__fei_1_1Factory.html</anchorfile>
      <anchor>a138c89de8668d2f9f776927599ec449c</anchor>
      <arglist>(fei::SharedPtr&lt; fei::MatrixGraph &gt; matrixGraph, bool isSolutionVector, int numVectors=1)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual fei::SharedPtr&lt; fei::Matrix &gt;</type>
      <name>createMatrix</name>
      <anchorfile>classsnl__fei_1_1Factory.html</anchorfile>
      <anchor>aa883bc1b43683f0a1d7f3708c9d48ef3</anchor>
      <arglist>(fei::SharedPtr&lt; fei::MatrixGraph &gt; matrixGraph)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual fei::SharedPtr&lt; fei::LinearSystem &gt;</type>
      <name>createLinearSystem</name>
      <anchorfile>classsnl__fei_1_1Factory.html</anchorfile>
      <anchor>a8c0cb487541e995f85504fade136da98</anchor>
      <arglist>(fei::SharedPtr&lt; fei::MatrixGraph &gt; &amp;matrixGraph)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual fei::SharedPtr&lt; fei::Solver &gt;</type>
      <name>createSolver</name>
      <anchorfile>classsnl__fei_1_1Factory.html</anchorfile>
      <anchor>a2f0d2b8a4767092dca2a4a6a56c827e6</anchor>
      <arglist>(const char *name=0)</arglist>
    </member>
    <member kind="function">
      <type>fei::SharedPtr&lt; LibraryWrapper &gt;</type>
      <name>get_LibraryWrapper</name>
      <anchorfile>classsnl__fei_1_1Factory.html</anchorfile>
      <anchor>a684fdba896015502e1a6dd4a2a6cd7aa</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getOutputLevel</name>
      <anchorfile>classsnl__fei_1_1Factory.html</anchorfile>
      <anchor>a37cc64b1684cad98d3ea9aa66f3341c6</anchor>
      <arglist>() const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>fei::Factory</name>
    <filename>classfei_1_1Factory.html</filename>
    <base virtualness="virtual">fei::VectorSpace::Factory</base>
    <base virtualness="virtual">fei::MatrixGraph::Factory</base>
    <base virtualness="virtual">fei::Matrix::Factory</base>
    <base virtualness="virtual">fei::Vector::Factory</base>
    <base virtualness="virtual">fei::LinearSystem::Factory</base>
    <base virtualness="virtual">fei::Solver::Factory</base>
    <member kind="function">
      <type></type>
      <name>Factory</name>
      <anchorfile>classfei_1_1Factory.html</anchorfile>
      <anchor>ae4d4633ccdaec65c3308c2cf6bacf610</anchor>
      <arglist>(MPI_Comm comm)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~Factory</name>
      <anchorfile>classfei_1_1Factory.html</anchorfile>
      <anchor>ab86c7c8d311380c031652508be13ef2b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual fei::SharedPtr&lt; Factory &gt;</type>
      <name>clone</name>
      <anchorfile>classfei_1_1Factory.html</anchorfile>
      <anchor>a694d65ddf2d4da0aaa59af0889370548</anchor>
      <arglist>() const  =0</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>parameters</name>
      <anchorfile>classfei_1_1Factory.html</anchorfile>
      <anchor>ad05ee861b1688a602a61c9dfc4423dd3</anchor>
      <arglist>(const fei::ParameterSet &amp;paramset)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual fei::SharedPtr&lt; FEI &gt;</type>
      <name>createFEI</name>
      <anchorfile>classfei_1_1Factory.html</anchorfile>
      <anchor>a79b99471b6933af4170b44bce46c62a2</anchor>
      <arglist>(fei::SharedPtr&lt; LibraryWrapper &gt; wrapper, MPI_Comm comm)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual fei::SharedPtr&lt; FEI &gt;</type>
      <name>createFEI</name>
      <anchorfile>classfei_1_1Factory.html</anchorfile>
      <anchor>aec4b600064cde97c264340358940f6b1</anchor>
      <arglist>(MPI_Comm comm)</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>getOutputLevel</name>
      <anchorfile>classfei_1_1Factory.html</anchorfile>
      <anchor>a853be583a3544cfddb00c9c60a048d72</anchor>
      <arglist>() const  =0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>fei::LinearSystem::Factory</name>
    <filename>classfei_1_1LinearSystem_1_1Factory.html</filename>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~Factory</name>
      <anchorfile>classfei_1_1LinearSystem_1_1Factory.html</anchorfile>
      <anchor>a89684996d2ffbf4dc6f87006ddc846ae</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual fei::SharedPtr&lt; fei::LinearSystem &gt;</type>
      <name>createLinearSystem</name>
      <anchorfile>classfei_1_1LinearSystem_1_1Factory.html</anchorfile>
      <anchor>a65a070e76a85a617b78c008b00cc58dc</anchor>
      <arglist>(fei::SharedPtr&lt; fei::MatrixGraph &gt; &amp;matrixGraph)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>FEData</name>
    <filename>classFEData.html</filename>
    <base virtualness="virtual">FiniteElementData</base>
    <member kind="function">
      <type></type>
      <name>FEData</name>
      <anchorfile>classFEData.html</anchorfile>
      <anchor>aa4c15a2aa57434feb800c54e7f35732e</anchor>
      <arglist>(MPI_Comm comm)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>parameters</name>
      <anchorfile>classFEData.html</anchorfile>
      <anchor>ac29f80460e8bdcf0bbe92e2bfea50c7f</anchor>
      <arglist>(int numParams, char **params)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>setLookup</name>
      <anchorfile>classFEData.html</anchorfile>
      <anchor>a53035d3dab82c31c7bcec0464d7d7692</anchor>
      <arglist>(Lookup &amp;lookup)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>describeStructure</name>
      <anchorfile>classFEData.html</anchorfile>
      <anchor>a1e3d7d50cd0a60259c2bd7a10605a32b</anchor>
      <arglist>(int numElemBlocks, const int *numElemsPerBlock, const int *numNodesPerElem, const int *elemMatrixSizePerBlock, int totalNumNodes, int numSharedNodes, int numMultCRs)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>setConnectivity</name>
      <anchorfile>classFEData.html</anchorfile>
      <anchor>a43f68e55aee4912a72edb6abc9edec44</anchor>
      <arglist>(int elemBlockID, int elemID, int numNodes, const int *nodeNumbers, const int *numDofPerNode, const int *dof_ids)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>setElemMatrix</name>
      <anchorfile>classFEData.html</anchorfile>
      <anchor>a3a0bb3fc087db10c0fc3a3af33a2e52f</anchor>
      <arglist>(int elemBlockID, int elemID, int numNodes, const int *nodeNumbers, const int *dofPerNode, const int *dof_ids, const double *const *coefs)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>setElemVector</name>
      <anchorfile>classFEData.html</anchorfile>
      <anchor>a117324f635189b641373dd1388c24e8c</anchor>
      <arglist>(int elemBlockID, int elemID, int numNodes, const int *nodeNumbers, const int *dofPerNode, const int *dof_ids, const double *coefs)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>setDirichletBCs</name>
      <anchorfile>classFEData.html</anchorfile>
      <anchor>a82231e819943f4eddac7c1e1fb00a3a4</anchor>
      <arglist>(int numBCs, const int *nodeNumbers, const int *dofOffsets, const double *values)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>sumIntoMatrix</name>
      <anchorfile>classFEData.html</anchorfile>
      <anchor>a815495b445b7764764c14ba12f9f50e7</anchor>
      <arglist>(int numRowNodes, const int *rowNodeNumbers, const int *rowDofOffsets, const int *numColNodesPerRow, const int *colNodeNumbers, const int *colDofOffsets, const double *coefs)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>loadComplete</name>
      <anchorfile>classFEData.html</anchorfile>
      <anchor>ae5669cbaff42e561a78fa954c7d56c8e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>launchSolver</name>
      <anchorfile>classFEData.html</anchorfile>
      <anchor>aaa62d69af6c3f1ae256837914cee5e43</anchor>
      <arglist>(int &amp;solveStatus, int &amp;iterations)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>reset</name>
      <anchorfile>classFEData.html</anchorfile>
      <anchor>a7737a6343bdb61bc7f9529781d5d0b84</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>deleteConstraints</name>
      <anchorfile>classFEData.html</anchorfile>
      <anchor>a54a1d80accee4846e6f3161d67144173</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getSolnEntry</name>
      <anchorfile>classFEData.html</anchorfile>
      <anchor>a49821619e53d786ef16fbc0e5b85f137</anchor>
      <arglist>(int nodeNumber, int dofOffset, double &amp;value)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getMultiplierSoln</name>
      <anchorfile>classFEData.html</anchorfile>
      <anchor>a952cbbb6fd2f5983ab058461f93914bd</anchor>
      <arglist>(int CRID, double &amp;lagrangeMultiplier)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>putNodalFieldData</name>
      <anchorfile>classFEData.html</anchorfile>
      <anchor>a2ac2da6c46887ce28470e9bc02db9181</anchor>
      <arglist>(int fieldID, int fieldSize, int numNodes, const int *nodeNumbers, const double *coefs)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>setMultiplierCR</name>
      <anchorfile>classFEData.html</anchorfile>
      <anchor>ab04a6eb201cffdc9a98fe3e97318a645</anchor>
      <arglist>(int CRID, int numNodes, const int *nodeNumbers, const int *dofOffsets, const double *coefWeights, double rhsValue)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>setPenaltyCR</name>
      <anchorfile>classFEData.html</anchorfile>
      <anchor>ab64c39780d2062dc441494011a881f28</anchor>
      <arglist>(int CRID, int numNodes, const int *nodeNumbers, const int *dofOffsets, const double *coefWeights, double penaltyValue, double rhsValue)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>FEDataFilter</name>
    <filename>classFEDataFilter.html</filename>
    <base>Filter</base>
  </compound>
  <compound kind="class">
    <name>FEI</name>
    <filename>classFEI.html</filename>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~FEI</name>
      <anchorfile>classFEI.html</anchorfile>
      <anchor>a5aec1444c37a2e3ac676cbece510f340</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>parameters</name>
      <anchorfile>classFEI.html</anchorfile>
      <anchor>abc2c3ac55b356bce6b2de91628c7bbe2</anchor>
      <arglist>(int numParams, const char *const *paramStrings)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>setIDLists</name>
      <anchorfile>classFEI.html</anchorfile>
      <anchor>a8dacbabfcf596f77ddbdd93b21763b9b</anchor>
      <arglist>(int numMatrices, const int *matrixIDs, int numRHSs, const int *rhsIDs)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>setSolveType</name>
      <anchorfile>classFEI.html</anchorfile>
      <anchor>aed348235538a63b9a56498351655a35c</anchor>
      <arglist>(int solveType)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>initFields</name>
      <anchorfile>classFEI.html</anchorfile>
      <anchor>a86698a20ea68f1445487eb7dfcb07075</anchor>
      <arglist>(int numFields, const int *fieldSizes, const int *fieldIDs, const int *fieldTypes=NULL)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>initElemBlock</name>
      <anchorfile>classFEI.html</anchorfile>
      <anchor>a36dcd5bd20ae0b7dfcedcd775424764a</anchor>
      <arglist>(GlobalID elemBlockID, int numElements, int numNodesPerElement, const int *numFieldsPerNode, const int *const *nodalFieldIDs, int numElemDofFieldsPerElement, const int *elemDOFFieldIDs, int interleaveStrategy)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>initElem</name>
      <anchorfile>classFEI.html</anchorfile>
      <anchor>af363d2567eef6def01ec637b78f397cf</anchor>
      <arglist>(GlobalID elemBlockID, GlobalID elemID, const GlobalID *elemConn)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>initSharedNodes</name>
      <anchorfile>classFEI.html</anchorfile>
      <anchor>ac01ad9a98bc5994afe93d05ba3f86577</anchor>
      <arglist>(int numSharedNodes, const GlobalID *sharedNodeIDs, const int *numProcsPerNode, const int *const *sharingProcIDs)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>initCRMult</name>
      <anchorfile>classFEI.html</anchorfile>
      <anchor>a761cd245917a43482b514b2f3631fb7d</anchor>
      <arglist>(int numCRNodes, const GlobalID *CRNodeIDs, const int *CRFieldIDs, int &amp;CRID)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>initCRPen</name>
      <anchorfile>classFEI.html</anchorfile>
      <anchor>a5ab511e57af68e3d9a626bfc503150cc</anchor>
      <arglist>(int numCRNodes, const GlobalID *CRNodeIDs, const int *CRFieldIDs, int &amp;CRID)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>initSlaveVariable</name>
      <anchorfile>classFEI.html</anchorfile>
      <anchor>ac6ca34a2d4ada8cf854323d74041c370</anchor>
      <arglist>(GlobalID slaveNodeID, int slaveFieldID, int offsetIntoSlaveField, int numMasterNodes, const GlobalID *masterNodeIDs, const int *masterFieldIDs, const double *weights, double rhsValue)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>initComplete</name>
      <anchorfile>classFEI.html</anchorfile>
      <anchor>a04032507c1d7deeef03d6f3845e7ff1d</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>setCurrentMatrix</name>
      <anchorfile>classFEI.html</anchorfile>
      <anchor>a2cf38780f320ffb1af27c8ff4cca70fb</anchor>
      <arglist>(int matrixID)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>setCurrentRHS</name>
      <anchorfile>classFEI.html</anchorfile>
      <anchor>a8efa87aa7d9484ecb5a2236ace15381e</anchor>
      <arglist>(int rhsID)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>resetSystem</name>
      <anchorfile>classFEI.html</anchorfile>
      <anchor>ac8650954384b8491ad155f4ced740cf5</anchor>
      <arglist>(double s=0.0)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>resetMatrix</name>
      <anchorfile>classFEI.html</anchorfile>
      <anchor>a9834f090a22fd22adcdfadc11e696f47</anchor>
      <arglist>(double s=0.0)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>resetRHSVector</name>
      <anchorfile>classFEI.html</anchorfile>
      <anchor>abc6bcd613785fb4b7e3fdde4f89e9baf</anchor>
      <arglist>(double s=0.0)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>resetInitialGuess</name>
      <anchorfile>classFEI.html</anchorfile>
      <anchor>a61717bf641f73c6d1119062b3cd2a81a</anchor>
      <arglist>(double s)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>deleteMultCRs</name>
      <anchorfile>classFEI.html</anchorfile>
      <anchor>ac6e047f70047fab9027cf03152a419b8</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>loadNodeBCs</name>
      <anchorfile>classFEI.html</anchorfile>
      <anchor>af29a5b37ecdc04baebca01a7656f6d0a</anchor>
      <arglist>(int numNodes, const GlobalID *nodeIDs, int fieldID, const int *offsetsIntoField, const double *prescribedValues)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>loadElemBCs</name>
      <anchorfile>classFEI.html</anchorfile>
      <anchor>ac2131950199ec60fa60f5a8a0d0f18a6</anchor>
      <arglist>(int numElems, const GlobalID *elemIDs, int fieldID, const double *const *alpha, const double *const *beta, const double *const *gamma)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>sumInElem</name>
      <anchorfile>classFEI.html</anchorfile>
      <anchor>a3a4b809d233db25c13bf45e16d43555b</anchor>
      <arglist>(GlobalID elemBlockID, GlobalID elemID, const GlobalID *elemConn, const double *const *elemStiffness, const double *elemLoad, int elemFormat)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>sumInElemMatrix</name>
      <anchorfile>classFEI.html</anchorfile>
      <anchor>a39aae1178f941c357db743691d63e140</anchor>
      <arglist>(GlobalID elemBlockID, GlobalID elemID, const GlobalID *elemConn, const double *const *elemStiffness, int elemFormat)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>sumInElemRHS</name>
      <anchorfile>classFEI.html</anchorfile>
      <anchor>a8cedce6a58e9406b605892bc4b6faa9d</anchor>
      <arglist>(GlobalID elemBlockID, GlobalID elemID, const GlobalID *elemConn, const double *elemLoad)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>loadCRMult</name>
      <anchorfile>classFEI.html</anchorfile>
      <anchor>a7c1fd4143a1d52ac60a6a7f5e33c2e02</anchor>
      <arglist>(int CRMultID, int numCRNodes, const GlobalID *CRNodeIDs, const int *CRFieldIDs, const double *CRWeights, double CRValue)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>loadCRPen</name>
      <anchorfile>classFEI.html</anchorfile>
      <anchor>a595ef7f2af6ac11b8e5056901a397aba</anchor>
      <arglist>(int CRPenID, int numCRNodes, const GlobalID *CRNodeIDs, const int *CRFieldIDs, const double *CRWeights, double CRValue, double penValue)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>putIntoRHS</name>
      <anchorfile>classFEI.html</anchorfile>
      <anchor>a7c7ce14221c0a546c546b501c7338680</anchor>
      <arglist>(int IDType, int fieldID, int numIDs, const GlobalID *IDs, const double *coefficients)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>sumIntoRHS</name>
      <anchorfile>classFEI.html</anchorfile>
      <anchor>ad661613e3358438ccc14d479fb9941b3</anchor>
      <arglist>(int IDType, int fieldID, int numIDs, const GlobalID *IDs, const double *coefficients)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>setMatScalars</name>
      <anchorfile>classFEI.html</anchorfile>
      <anchor>a6a3a8a0d3c7d280fe88f1c29528244cb</anchor>
      <arglist>(int numScalars, const int *IDs, const double *scalars)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>setRHSScalars</name>
      <anchorfile>classFEI.html</anchorfile>
      <anchor>a9b8f3653277c29b34d8795d2c4cc8bfb</anchor>
      <arglist>(int numScalars, const int *IDs, const double *scalars)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>loadComplete</name>
      <anchorfile>classFEI.html</anchorfile>
      <anchor>a874ad10c236b79ffb27b5cb0374460ec</anchor>
      <arglist>(bool applyBCs=true, bool globalAssemble=true)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>residualNorm</name>
      <anchorfile>classFEI.html</anchorfile>
      <anchor>a2bc007651ddf64a15834f2072ce8ad19</anchor>
      <arglist>(int whichNorm, int numFields, int *fieldIDs, double *norms)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>solve</name>
      <anchorfile>classFEI.html</anchorfile>
      <anchor>aed8159ff0873f26578dab5c8f8b808cb</anchor>
      <arglist>(int &amp;status)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>iterations</name>
      <anchorfile>classFEI.html</anchorfile>
      <anchor>aab2221611e219db9933e8a0a76ade813</anchor>
      <arglist>(int &amp;itersTaken) const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>getFieldSize</name>
      <anchorfile>classFEI.html</anchorfile>
      <anchor>a19195e48026a8c746fb7ddc2d3a98a39</anchor>
      <arglist>(int fieldID, int &amp;numScalars)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>getEqnNumbers</name>
      <anchorfile>classFEI.html</anchorfile>
      <anchor>a94fd960cd36a9f999bc86339c9831f11</anchor>
      <arglist>(GlobalID ID, int idType, int fieldID, int &amp;numEqns, int *eqnNumbers)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>getNodalFieldSolution</name>
      <anchorfile>classFEI.html</anchorfile>
      <anchor>ae0fb771f3a7c61b47caaae2dcbd0584d</anchor>
      <arglist>(int fieldID, int numNodes, const GlobalID *nodeIDs, double *results)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>getNumLocalNodes</name>
      <anchorfile>classFEI.html</anchorfile>
      <anchor>a874d40c48f9ac2354e99bc681894da26</anchor>
      <arglist>(int &amp;numNodes)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>getLocalNodeIDList</name>
      <anchorfile>classFEI.html</anchorfile>
      <anchor>a1659b3b0fa6b58941788bec5caa6a80d</anchor>
      <arglist>(int &amp;numNodes, GlobalID *nodeIDs, int lenNodeIDs)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>putNodalFieldData</name>
      <anchorfile>classFEI.html</anchorfile>
      <anchor>a5f7c82682b1955f228577149febc7dfc</anchor>
      <arglist>(int fieldID, int numNodes, const GlobalID *nodeIDs, const double *data)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>getBlockNodeSolution</name>
      <anchorfile>classFEI.html</anchorfile>
      <anchor>af394fd59a64c167b32fa94416d1a510d</anchor>
      <arglist>(GlobalID elemBlockID, int numNodes, const GlobalID *nodeIDs, int *offsets, double *results)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>getNodalSolution</name>
      <anchorfile>classFEI.html</anchorfile>
      <anchor>a4fbdb0027dfc20928171dfd9175805a9</anchor>
      <arglist>(int numNodes, const GlobalID *nodeIDs, int *offsets, double *results)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>getBlockFieldNodeSolution</name>
      <anchorfile>classFEI.html</anchorfile>
      <anchor>ade5fc56993b08ae5fa14846e12c5b0fd</anchor>
      <arglist>(GlobalID elemBlockID, int fieldID, int numNodes, const GlobalID *nodeIDs, double *results)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>getBlockElemSolution</name>
      <anchorfile>classFEI.html</anchorfile>
      <anchor>adc4b171343801716140980ff0dd19f37</anchor>
      <arglist>(GlobalID elemBlockID, int numElems, const GlobalID *elemIDs, int &amp;numElemDOFPerElement, double *results)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>getNumCRMultipliers</name>
      <anchorfile>classFEI.html</anchorfile>
      <anchor>a412274f5ed9e9609fdfbd19adbc33bf6</anchor>
      <arglist>(int &amp;numMultCRs)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>getCRMultIDList</name>
      <anchorfile>classFEI.html</anchorfile>
      <anchor>a33dc0d99319a63236b6107448eb02f1c</anchor>
      <arglist>(int numMultCRs, int *multIDs)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>getCRMultipliers</name>
      <anchorfile>classFEI.html</anchorfile>
      <anchor>a65cc13634816781f9484b6e2cf703d38</anchor>
      <arglist>(int numCRs, const int *CRIDs, double *results)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>putBlockNodeSolution</name>
      <anchorfile>classFEI.html</anchorfile>
      <anchor>a8e993e390bbeb8f4b06ea3e22913fd42</anchor>
      <arglist>(GlobalID elemBlockID, int numNodes, const GlobalID *nodeIDs, const int *offsets, const double *estimates)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>putBlockFieldNodeSolution</name>
      <anchorfile>classFEI.html</anchorfile>
      <anchor>aacf9ec5473fe2202f1f7e422a99bbf6e</anchor>
      <arglist>(GlobalID elemBlockID, int fieldID, int numNodes, const GlobalID *nodeIDs, const double *estimates)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>putBlockElemSolution</name>
      <anchorfile>classFEI.html</anchorfile>
      <anchor>a272e4ec25d4fb09e259b027a5822f6a2</anchor>
      <arglist>(GlobalID elemBlockID, int numElems, const GlobalID *elemIDs, int dofPerElem, const double *estimates)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>putCRMultipliers</name>
      <anchorfile>classFEI.html</anchorfile>
      <anchor>ac7f0be86dae6af87f0423953b66442ea</anchor>
      <arglist>(int numMultCRs, const int *CRMultIDs, const double *multEstimates)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>getBlockNodeIDList</name>
      <anchorfile>classFEI.html</anchorfile>
      <anchor>a3b01c6e4498adf36d63ceae7c686629b</anchor>
      <arglist>(GlobalID elemBlockID, int numNodes, GlobalID *nodeIDs)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>getBlockElemIDList</name>
      <anchorfile>classFEI.html</anchorfile>
      <anchor>af2bac083e76f4eeff1f53bcbfb0654a6</anchor>
      <arglist>(GlobalID elemBlockID, int numElems, GlobalID *elemIDs)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>version</name>
      <anchorfile>classFEI.html</anchorfile>
      <anchor>a99c9490a986e0093b4cf565d3e347c51</anchor>
      <arglist>(const char *&amp;versionString)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>cumulative_cpu_times</name>
      <anchorfile>classFEI.html</anchorfile>
      <anchor>a854fe8099e376c951178d790d1a54fca</anchor>
      <arglist>(double &amp;initPhase, double &amp;loadPhase, double &amp;solve, double &amp;solnReturn)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>getNumSolnParams</name>
      <anchorfile>classFEI.html</anchorfile>
      <anchor>a95c4a1774e6046f7cddd6716b716681f</anchor>
      <arglist>(GlobalID globalNodeID, int &amp;numSolnParams) const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>getNumElemBlocks</name>
      <anchorfile>classFEI.html</anchorfile>
      <anchor>afe89640dfa34048f483531fb92c547f2</anchor>
      <arglist>(int &amp;numElemBlocks) const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>getNumBlockActNodes</name>
      <anchorfile>classFEI.html</anchorfile>
      <anchor>a7ace8a49c7989c19542df3184b59f4f3</anchor>
      <arglist>(GlobalID elemBlockID, int &amp;numNodes) const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>getNumBlockActEqns</name>
      <anchorfile>classFEI.html</anchorfile>
      <anchor>a842795b2e2600a92e19efce4028ce2e9</anchor>
      <arglist>(GlobalID elemBlockID, int &amp;numEqns) const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>getNumNodesPerElement</name>
      <anchorfile>classFEI.html</anchorfile>
      <anchor>abe3ff909070d010734b8873a96a992c4</anchor>
      <arglist>(GlobalID elemBlockID, int &amp;nodesPerElem) const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>getNumEqnsPerElement</name>
      <anchorfile>classFEI.html</anchorfile>
      <anchor>a6398e6b4fe236528451dcf6da82ec28f</anchor>
      <arglist>(GlobalID elemBlockID, int &amp;eqnsPerElem) const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>getNumBlockElements</name>
      <anchorfile>classFEI.html</anchorfile>
      <anchor>a4dc7adfdc0ed6b579697ba0387b18b40</anchor>
      <arglist>(GlobalID blockID, int &amp;numElems) const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>getNumBlockElemDOF</name>
      <anchorfile>classFEI.html</anchorfile>
      <anchor>a12b2053c32c970283b667301d0e17c56</anchor>
      <arglist>(GlobalID blockID, int &amp;DOFPerElem) const  =0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>fei::FEI_Impl</name>
    <filename>classfei_1_1FEI__Impl.html</filename>
    <base>FEI</base>
    <base protection="private">fei::Logger</base>
    <member kind="function">
      <type></type>
      <name>FEI_Impl</name>
      <anchorfile>classfei_1_1FEI__Impl.html</anchorfile>
      <anchor>af76223c38f003fc41e911039f9d382d8</anchor>
      <arglist>(fei::SharedPtr&lt; LibraryWrapper &gt; wrapper, MPI_Comm comm, int masterRank=0)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>FEI_Impl</name>
      <anchorfile>classfei_1_1FEI__Impl.html</anchorfile>
      <anchor>abab89fc24afd1723f0d65fa36ea4ebaa</anchor>
      <arglist>(const fei::Factory *factory, MPI_Comm comm, int masterRank=0)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~FEI_Impl</name>
      <anchorfile>classfei_1_1FEI__Impl.html</anchorfile>
      <anchor>a2370ece4b38dd90675f096bc1e1a3423</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>fei::SharedPtr&lt; fei::LinearSystem &gt;</type>
      <name>getLinearSystem</name>
      <anchorfile>classfei_1_1FEI__Impl.html</anchorfile>
      <anchor>a13dde276de107d8ab590b220451b6406</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>parameters</name>
      <anchorfile>classfei_1_1FEI__Impl.html</anchorfile>
      <anchor>abd457eee6b49fe78a0963a5eb15381a0</anchor>
      <arglist>(int numParams, const char *const *paramStrings)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>setIDLists</name>
      <anchorfile>classfei_1_1FEI__Impl.html</anchorfile>
      <anchor>affd06212765c33ddcfaaddc09fe58292</anchor>
      <arglist>(int numMatrices, const int *matrixIDs, int numRHSs, const int *rhsIDs)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>setSolveType</name>
      <anchorfile>classfei_1_1FEI__Impl.html</anchorfile>
      <anchor>af3c55cb260581bd2d2b4637b04e16d85</anchor>
      <arglist>(int solveType)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>initFields</name>
      <anchorfile>classfei_1_1FEI__Impl.html</anchorfile>
      <anchor>a33ad95752d7fdafa744bc269080a83ab</anchor>
      <arglist>(int numFields, const int *fieldSizes, const int *fieldIDs, const int *fieldTypes=NULL)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>initElemBlock</name>
      <anchorfile>classfei_1_1FEI__Impl.html</anchorfile>
      <anchor>a43bdc9b388f7a8ee4ab6213ff5f2a3d6</anchor>
      <arglist>(GlobalID elemBlockID, int numElements, int numNodesPerElement, const int *numFieldsPerNode, const int *const *nodalFieldIDs, int numElemDofFieldsPerElement, const int *elemDOFFieldIDs, int interleaveStrategy)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>initElem</name>
      <anchorfile>classfei_1_1FEI__Impl.html</anchorfile>
      <anchor>a1bad0a72be5ecef39474f37a4b59e825</anchor>
      <arglist>(GlobalID elemBlockID, GlobalID elemID, const GlobalID *elemConn)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>initSlaveVariable</name>
      <anchorfile>classfei_1_1FEI__Impl.html</anchorfile>
      <anchor>a14ad5272de1fdb881e4df7c905b7e62d</anchor>
      <arglist>(GlobalID slaveNodeID, int slaveFieldID, int offsetIntoSlaveField, int numMasterNodes, const GlobalID *masterNodeIDs, const int *masterFieldIDs, const double *weights, double rhsValue)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>deleteMultCRs</name>
      <anchorfile>classfei_1_1FEI__Impl.html</anchorfile>
      <anchor>a4b683541fbfece03cdd36cb7cc51f5ca</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>initSharedNodes</name>
      <anchorfile>classfei_1_1FEI__Impl.html</anchorfile>
      <anchor>ab3b4471818012cee6bacd9557bd0e895</anchor>
      <arglist>(int numSharedNodes, const GlobalID *sharedNodeIDs, const int *numProcsPerNode, const int *const *sharingProcIDs)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>initCRMult</name>
      <anchorfile>classfei_1_1FEI__Impl.html</anchorfile>
      <anchor>a6021c513785411551c216917754b8726</anchor>
      <arglist>(int numCRNodes, const GlobalID *CRNodeIDs, const int *CRFieldIDs, int &amp;CRID)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>initCRPen</name>
      <anchorfile>classfei_1_1FEI__Impl.html</anchorfile>
      <anchor>a1e3af09df7e5fc2caa095013531601fb</anchor>
      <arglist>(int numCRNodes, const GlobalID *CRNodeIDs, const int *CRFieldIDs, int &amp;CRID)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>initComplete</name>
      <anchorfile>classfei_1_1FEI__Impl.html</anchorfile>
      <anchor>a8a7904505aa2df0ebe1273f4fffbead8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>setCurrentMatrix</name>
      <anchorfile>classfei_1_1FEI__Impl.html</anchorfile>
      <anchor>ae2ba07518f169f51047870a46a2e283c</anchor>
      <arglist>(int matrixID)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>setCurrentRHS</name>
      <anchorfile>classfei_1_1FEI__Impl.html</anchorfile>
      <anchor>ab677364b75355a791e6f69f311d12423</anchor>
      <arglist>(int rhsID)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>resetSystem</name>
      <anchorfile>classfei_1_1FEI__Impl.html</anchorfile>
      <anchor>a537da9af8f7a04919215caa88310e20a</anchor>
      <arglist>(double s=0.0)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>resetMatrix</name>
      <anchorfile>classfei_1_1FEI__Impl.html</anchorfile>
      <anchor>a1b4d01ddbff83ace62a744c5f34e2f60</anchor>
      <arglist>(double s=0.0)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>resetRHSVector</name>
      <anchorfile>classfei_1_1FEI__Impl.html</anchorfile>
      <anchor>a11277d051960db6f4541f7d04184452a</anchor>
      <arglist>(double s=0.0)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>resetInitialGuess</name>
      <anchorfile>classfei_1_1FEI__Impl.html</anchorfile>
      <anchor>a5f5f6fe7dbeedd82cc685fe3e72e57c9</anchor>
      <arglist>(double s=0.0)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>loadNodeBCs</name>
      <anchorfile>classfei_1_1FEI__Impl.html</anchorfile>
      <anchor>a80da2c7441a057934160ec8ad52b7f8c</anchor>
      <arglist>(int numNodes, const GlobalID *nodeIDs, int fieldID, const int *offsetsIntoField, const double *prescribedValues)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>loadElemBCs</name>
      <anchorfile>classfei_1_1FEI__Impl.html</anchorfile>
      <anchor>a0ffc96851c46bed1c3093da6ade1ecba</anchor>
      <arglist>(int numElems, const GlobalID *elemIDs, int fieldID, const double *const *alpha, const double *const *beta, const double *const *gamma)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>sumInElem</name>
      <anchorfile>classfei_1_1FEI__Impl.html</anchorfile>
      <anchor>a9931d188b6ae6d8b97b143c943c8a732</anchor>
      <arglist>(GlobalID elemBlockID, GlobalID elemID, const GlobalID *elemConn, const double *const *elemStiffness, const double *elemLoad, int elemFormat)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>sumInElemMatrix</name>
      <anchorfile>classfei_1_1FEI__Impl.html</anchorfile>
      <anchor>a9d75112c7ff4a9210d62c1f35819d6d8</anchor>
      <arglist>(GlobalID elemBlockID, GlobalID elemID, const GlobalID *elemConn, const double *const *elemStiffness, int elemFormat)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>sumInElemRHS</name>
      <anchorfile>classfei_1_1FEI__Impl.html</anchorfile>
      <anchor>a9997a75792087a1c158c245fbb5e62c2</anchor>
      <arglist>(GlobalID elemBlockID, GlobalID elemID, const GlobalID *elemConn, const double *elemLoad)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>loadCRMult</name>
      <anchorfile>classfei_1_1FEI__Impl.html</anchorfile>
      <anchor>adcb1f52868b6a457600f00924cf9b82a</anchor>
      <arglist>(int CRMultID, int numCRNodes, const GlobalID *CRNodeIDs, const int *CRFieldIDs, const double *CRWeights, double CRValue)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>loadCRPen</name>
      <anchorfile>classfei_1_1FEI__Impl.html</anchorfile>
      <anchor>a170187981e9a25715c4079234699ca4b</anchor>
      <arglist>(int CRPenID, int numCRNodes, const GlobalID *CRNodeIDs, const int *CRFieldIDs, const double *CRWeights, double CRValue, double penValue)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>putIntoRHS</name>
      <anchorfile>classfei_1_1FEI__Impl.html</anchorfile>
      <anchor>a327fdf3c536a626edccdf6b2eca97c5d</anchor>
      <arglist>(int IDType, int fieldID, int numIDs, const GlobalID *IDs, const double *coefficients)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>sumIntoRHS</name>
      <anchorfile>classfei_1_1FEI__Impl.html</anchorfile>
      <anchor>ac116af550d73520b00885e632c736ece</anchor>
      <arglist>(int IDType, int fieldID, int numIDs, const GlobalID *IDs, const double *coefficients)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>setMatScalars</name>
      <anchorfile>classfei_1_1FEI__Impl.html</anchorfile>
      <anchor>a3b729436e1dd50468faba9af995b0d34</anchor>
      <arglist>(int numScalars, const int *IDs, const double *scalars)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>setRHSScalars</name>
      <anchorfile>classfei_1_1FEI__Impl.html</anchorfile>
      <anchor>a5fc8bf769e0dcd273364df47788b714b</anchor>
      <arglist>(int numScalars, const int *IDs, const double *scalars)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>loadComplete</name>
      <anchorfile>classfei_1_1FEI__Impl.html</anchorfile>
      <anchor>a3975a002d0dd02d13ada152f625bbe84</anchor>
      <arglist>(bool applyBCs=true, bool globalAssemble=true)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>residualNorm</name>
      <anchorfile>classfei_1_1FEI__Impl.html</anchorfile>
      <anchor>a6a35c17464bf2dbcaf8e4fb50cfb2f85</anchor>
      <arglist>(int whichNorm, int numFields, int *fieldIDs, double *norms)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>solve</name>
      <anchorfile>classfei_1_1FEI__Impl.html</anchorfile>
      <anchor>a3baf52eb279718828760e617b0c4fadb</anchor>
      <arglist>(int &amp;status)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>iterations</name>
      <anchorfile>classfei_1_1FEI__Impl.html</anchorfile>
      <anchor>a233faa5e164be5e98a54ba6e317105e0</anchor>
      <arglist>(int &amp;itersTaken) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>version</name>
      <anchorfile>classfei_1_1FEI__Impl.html</anchorfile>
      <anchor>ae02c61e55be0dd7b7f3f68edd7be04c6</anchor>
      <arglist>(const char *&amp;versionString)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>cumulative_cpu_times</name>
      <anchorfile>classfei_1_1FEI__Impl.html</anchorfile>
      <anchor>a5c96acddf5c3d718da985dbe75224bee</anchor>
      <arglist>(double &amp;initTime, double &amp;loadTime, double &amp;solveTime, double &amp;solnReturnTime)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getBlockNodeSolution</name>
      <anchorfile>classfei_1_1FEI__Impl.html</anchorfile>
      <anchor>aa4f0ec6af2fdb9d561b04ab22de3af5f</anchor>
      <arglist>(GlobalID elemBlockID, int numNodes, const GlobalID *nodeIDs, int *offsets, double *results)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getNodalSolution</name>
      <anchorfile>classfei_1_1FEI__Impl.html</anchorfile>
      <anchor>a9b226234cc39ede8361a13aa346c7031</anchor>
      <arglist>(int numNodes, const GlobalID *nodeIDs, int *offsets, double *results)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getBlockFieldNodeSolution</name>
      <anchorfile>classfei_1_1FEI__Impl.html</anchorfile>
      <anchor>a48f1a1842818d8247b8bae72a93dd6ce</anchor>
      <arglist>(GlobalID elemBlockID, int fieldID, int numNodes, const GlobalID *nodeIDs, double *results)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getBlockElemSolution</name>
      <anchorfile>classfei_1_1FEI__Impl.html</anchorfile>
      <anchor>aade1c1c8c1e09f6daabb4e32add5539d</anchor>
      <arglist>(GlobalID elemBlockID, int numElems, const GlobalID *elemIDs, int &amp;numElemDOFPerElement, double *results)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getNumCRMultipliers</name>
      <anchorfile>classfei_1_1FEI__Impl.html</anchorfile>
      <anchor>a89108a910726f8019b5c2e551b035170</anchor>
      <arglist>(int &amp;numMultCRs)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getCRMultIDList</name>
      <anchorfile>classfei_1_1FEI__Impl.html</anchorfile>
      <anchor>a210880f81d477c4082528fdd2d332790</anchor>
      <arglist>(int numMultCRs, int *multIDs)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getCRMultipliers</name>
      <anchorfile>classfei_1_1FEI__Impl.html</anchorfile>
      <anchor>af70769599471333d3b59d2fd4b0212d2</anchor>
      <arglist>(int numCRs, const int *CRIDs, double *multipliers)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>putBlockNodeSolution</name>
      <anchorfile>classfei_1_1FEI__Impl.html</anchorfile>
      <anchor>a49d81f531fb3ce52a4c2a34c9e05421d</anchor>
      <arglist>(GlobalID elemBlockID, int numNodes, const GlobalID *nodeIDs, const int *offsets, const double *estimates)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>putBlockFieldNodeSolution</name>
      <anchorfile>classfei_1_1FEI__Impl.html</anchorfile>
      <anchor>a60f3987625a3044f1e3019bcf29a0471</anchor>
      <arglist>(GlobalID elemBlockID, int fieldID, int numNodes, const GlobalID *nodeIDs, const double *estimates)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>putBlockElemSolution</name>
      <anchorfile>classfei_1_1FEI__Impl.html</anchorfile>
      <anchor>aaef194452a4d07cf23ab1f2d3be6a029</anchor>
      <arglist>(GlobalID elemBlockID, int numElems, const GlobalID *elemIDs, int dofPerElem, const double *estimates)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>putCRMultipliers</name>
      <anchorfile>classfei_1_1FEI__Impl.html</anchorfile>
      <anchor>a75bb905a42c488f1d2c54a1676e6916a</anchor>
      <arglist>(int numMultCRs, const int *CRIDs, const double *multEstimates)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getBlockNodeIDList</name>
      <anchorfile>classfei_1_1FEI__Impl.html</anchorfile>
      <anchor>aa4bfcb1b4c9b394ec647e4f455d076fe</anchor>
      <arglist>(GlobalID elemBlockID, int numNodes, GlobalID *nodeIDs)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getBlockElemIDList</name>
      <anchorfile>classfei_1_1FEI__Impl.html</anchorfile>
      <anchor>ae0ac02d672d0402ee7c91aa419944788</anchor>
      <arglist>(GlobalID elemBlockID, int numElems, GlobalID *elemIDs)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getNumSolnParams</name>
      <anchorfile>classfei_1_1FEI__Impl.html</anchorfile>
      <anchor>a2e76e192e940aa2407df74b09d699bf1</anchor>
      <arglist>(GlobalID nodeID, int &amp;numSolnParams) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getNumElemBlocks</name>
      <anchorfile>classfei_1_1FEI__Impl.html</anchorfile>
      <anchor>a80c9d07088bdf8681f776358ea308d7c</anchor>
      <arglist>(int &amp;numElemBlocks) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getNumBlockActNodes</name>
      <anchorfile>classfei_1_1FEI__Impl.html</anchorfile>
      <anchor>a76e4bbd64baea83d7a76baff1485270b</anchor>
      <arglist>(GlobalID blockID, int &amp;numNodes) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getNumBlockActEqns</name>
      <anchorfile>classfei_1_1FEI__Impl.html</anchorfile>
      <anchor>ab385f8d15cd5fea60f7486717f99143b</anchor>
      <arglist>(GlobalID blockID, int &amp;numEqns) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getNumNodesPerElement</name>
      <anchorfile>classfei_1_1FEI__Impl.html</anchorfile>
      <anchor>a843813b006a0a5f82acf94cd20322533</anchor>
      <arglist>(GlobalID blockID, int &amp;nodesPerElem) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getNumEqnsPerElement</name>
      <anchorfile>classfei_1_1FEI__Impl.html</anchorfile>
      <anchor>a4c7267b3dfaf7bed16114b69a910fdd6</anchor>
      <arglist>(GlobalID blockID, int &amp;numEqns) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getNumBlockElements</name>
      <anchorfile>classfei_1_1FEI__Impl.html</anchorfile>
      <anchor>a8c70702cc9e56ddbc1ff4afaaa252a45</anchor>
      <arglist>(GlobalID blockID, int &amp;numElems) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getNumBlockElemDOF</name>
      <anchorfile>classfei_1_1FEI__Impl.html</anchorfile>
      <anchor>acdf5b0a6794600c37adf5f15777fd39a</anchor>
      <arglist>(GlobalID blockID, int &amp;DOFPerElem) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getParameters</name>
      <anchorfile>classfei_1_1FEI__Impl.html</anchorfile>
      <anchor>acbb32f0b44f07f075b0382bc387e8341</anchor>
      <arglist>(int &amp;numParams, char **&amp;paramStrings)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getFieldSize</name>
      <anchorfile>classfei_1_1FEI__Impl.html</anchorfile>
      <anchor>aa1c5d45bd6b4766e7678ec0507a9ce79</anchor>
      <arglist>(int fieldID, int &amp;numScalars)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getEqnNumbers</name>
      <anchorfile>classfei_1_1FEI__Impl.html</anchorfile>
      <anchor>a3b09df5fc84b99575f54ed7ac2a36caf</anchor>
      <arglist>(GlobalID ID, int idType, int fieldID, int &amp;numEqns, int *eqnNumbers)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getNodalFieldSolution</name>
      <anchorfile>classfei_1_1FEI__Impl.html</anchorfile>
      <anchor>a77d2518df747f550281b27961e9568e6</anchor>
      <arglist>(int fieldID, int numNodes, const GlobalID *nodeIDs, double *results)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getNumLocalNodes</name>
      <anchorfile>classfei_1_1FEI__Impl.html</anchorfile>
      <anchor>a843f4ffe25789fbe5d199353d3ecab2c</anchor>
      <arglist>(int &amp;numNodes)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getLocalNodeIDList</name>
      <anchorfile>classfei_1_1FEI__Impl.html</anchorfile>
      <anchor>aa5184b5d3261073801bd9b4198fff80b</anchor>
      <arglist>(int &amp;numNodes, GlobalID *nodeIDs, int lenNodeIDs)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>putNodalFieldData</name>
      <anchorfile>classfei_1_1FEI__Impl.html</anchorfile>
      <anchor>ae40d90e55a1659dee1c02efba624315a</anchor>
      <arglist>(int fieldID, int numNodes, const GlobalID *nodeIDs, const double *nodeData)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>FEI_Implementation</name>
    <filename>classFEI__Implementation.html</filename>
    <base>FEI</base>
    <member kind="function">
      <type></type>
      <name>FEI_Implementation</name>
      <anchorfile>classFEI__Implementation.html</anchorfile>
      <anchor>ab508361ab1a4245d3d6de159d2b23818</anchor>
      <arglist>(fei::SharedPtr&lt; LibraryWrapper &gt; libWrapper, MPI_Comm comm, int masterRank=0)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~FEI_Implementation</name>
      <anchorfile>classFEI__Implementation.html</anchorfile>
      <anchor>a1bf8e0843f44f9373b7e451f69bb6f95</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>parameters</name>
      <anchorfile>classFEI__Implementation.html</anchorfile>
      <anchor>af49e5af1f8980035f63f196373667c64</anchor>
      <arglist>(int numParams, const char *const *paramStrings)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>setIDLists</name>
      <anchorfile>classFEI__Implementation.html</anchorfile>
      <anchor>a91ac9975203f9480b98ddcd32953fc9a</anchor>
      <arglist>(int numMatrices, const int *matrixIDs, int numRHSs, const int *rhsIDs)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>setSolveType</name>
      <anchorfile>classFEI__Implementation.html</anchorfile>
      <anchor>a485d4f4b2ed0938473d992fad738d576</anchor>
      <arglist>(int solveType)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>initFields</name>
      <anchorfile>classFEI__Implementation.html</anchorfile>
      <anchor>a614a4631752f73566254ee2c6a7d48ff</anchor>
      <arglist>(int numFields, const int *fieldSizes, const int *fieldIDs, const int *fieldTypes=NULL)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>initElemBlock</name>
      <anchorfile>classFEI__Implementation.html</anchorfile>
      <anchor>ac5cdefee134dfc78be2d16c6ee6d5260</anchor>
      <arglist>(GlobalID elemBlockID, int numElements, int numNodesPerElement, const int *numFieldsPerNode, const int *const *nodalFieldIDs, int numElemDofFieldsPerElement, const int *elemDOFFieldIDs, int interleaveStrategy)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>initElem</name>
      <anchorfile>classFEI__Implementation.html</anchorfile>
      <anchor>a2fabb142da9b74e7d575b3197007037a</anchor>
      <arglist>(GlobalID elemBlockID, GlobalID elemID, const GlobalID *elemConn)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>initSlaveVariable</name>
      <anchorfile>classFEI__Implementation.html</anchorfile>
      <anchor>a93f303cd8d5f5c4e35064dabefd9e720</anchor>
      <arglist>(GlobalID slaveNodeID, int slaveFieldID, int offsetIntoSlaveField, int numMasterNodes, const GlobalID *masterNodeIDs, const int *masterFieldIDs, const double *weights, double rhsValue)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>deleteMultCRs</name>
      <anchorfile>classFEI__Implementation.html</anchorfile>
      <anchor>afa50966c5491a20cc0d6601e6054aa76</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>initSharedNodes</name>
      <anchorfile>classFEI__Implementation.html</anchorfile>
      <anchor>a2514c0871f1a7e588a978673b8204c97</anchor>
      <arglist>(int numSharedNodes, const GlobalID *sharedNodeIDs, const int *numProcsPerNode, const int *const *sharingProcIDs)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>initCRMult</name>
      <anchorfile>classFEI__Implementation.html</anchorfile>
      <anchor>a45388a5002145835334794cf5779fac4</anchor>
      <arglist>(int numCRNodes, const GlobalID *CRNodes, const int *CRFields, int &amp;CRID)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>initCRPen</name>
      <anchorfile>classFEI__Implementation.html</anchorfile>
      <anchor>a1be258e8bc74caeb30d3466a2b67edfa</anchor>
      <arglist>(int numCRNodes, const GlobalID *CRNodes, const int *CRFields, int &amp;CRID)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>initComplete</name>
      <anchorfile>classFEI__Implementation.html</anchorfile>
      <anchor>a93a0a49f1c00e9af053dc65adb885675</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>setCurrentMatrix</name>
      <anchorfile>classFEI__Implementation.html</anchorfile>
      <anchor>a463c00c29b535df3744a763fa26a14b2</anchor>
      <arglist>(int matID)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>setCurrentRHS</name>
      <anchorfile>classFEI__Implementation.html</anchorfile>
      <anchor>a77f90b0aed7aad784865a0d53febd848</anchor>
      <arglist>(int rhsID)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>resetSystem</name>
      <anchorfile>classFEI__Implementation.html</anchorfile>
      <anchor>ad5e351d389a12e6d79002345f3855544</anchor>
      <arglist>(double s=0.0)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>resetMatrix</name>
      <anchorfile>classFEI__Implementation.html</anchorfile>
      <anchor>ab4de1b52adb5e5722ad786958d8f153e</anchor>
      <arglist>(double s=0.0)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>resetRHSVector</name>
      <anchorfile>classFEI__Implementation.html</anchorfile>
      <anchor>a6b3c0ae76d29bd121392f9ee200bb6ae</anchor>
      <arglist>(double s=0.0)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>resetInitialGuess</name>
      <anchorfile>classFEI__Implementation.html</anchorfile>
      <anchor>a534ccaf755db00271fe7e10a029e3388</anchor>
      <arglist>(double s=0.0)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>loadNodeBCs</name>
      <anchorfile>classFEI__Implementation.html</anchorfile>
      <anchor>a1ea7534371fe3af1ead4b296923b9d50</anchor>
      <arglist>(int numNodes, const GlobalID *nodeIDs, int fieldID, const int *offsetsIntoField, const double *prescribedValues)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>loadElemBCs</name>
      <anchorfile>classFEI__Implementation.html</anchorfile>
      <anchor>a4ba40ef40269f313f36c981a6050465f</anchor>
      <arglist>(int numElems, const GlobalID *elemIDs, int fieldID, const double *const *alpha, const double *const *beta, const double *const *gamma)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>sumInElem</name>
      <anchorfile>classFEI__Implementation.html</anchorfile>
      <anchor>a183b8b9067edaf8bb79a226b9e0e7075</anchor>
      <arglist>(GlobalID elemBlockID, GlobalID elemID, const GlobalID *elemConn, const double *const *elemStiffness, const double *elemLoad, int elemFormat)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>sumInElemMatrix</name>
      <anchorfile>classFEI__Implementation.html</anchorfile>
      <anchor>a1c5a33c6893025fc96327e2a65eb9fe8</anchor>
      <arglist>(GlobalID elemBlockID, GlobalID elemID, const GlobalID *elemConn, const double *const *elemStiffness, int elemFormat)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>sumInElemRHS</name>
      <anchorfile>classFEI__Implementation.html</anchorfile>
      <anchor>a04857086a5b46404d97f801420942e04</anchor>
      <arglist>(GlobalID elemBlockID, GlobalID elemID, const GlobalID *elemConn, const double *elemLoad)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>loadCRMult</name>
      <anchorfile>classFEI__Implementation.html</anchorfile>
      <anchor>ae4d21370ad0f1f97cde8dd7de1d711f5</anchor>
      <arglist>(int CRID, int numCRNodes, const GlobalID *CRNodes, const int *CRFields, const double *CRWeights, double CRValue)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>loadCRPen</name>
      <anchorfile>classFEI__Implementation.html</anchorfile>
      <anchor>a85df294911e627c0f29705f0f8e0c782</anchor>
      <arglist>(int CRID, int numCRNodes, const GlobalID *CRNodes, const int *CRFields, const double *CRWeights, double CRValue, double penValue)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>putIntoRHS</name>
      <anchorfile>classFEI__Implementation.html</anchorfile>
      <anchor>a3030f64590ae5b27e7f901922df60588</anchor>
      <arglist>(int IDType, int fieldID, int numIDs, const GlobalID *IDs, const double *rhsEntries)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>sumIntoRHS</name>
      <anchorfile>classFEI__Implementation.html</anchorfile>
      <anchor>aef201288c553da534e4ffd363ee3002d</anchor>
      <arglist>(int IDType, int fieldID, int numIDs, const GlobalID *IDs, const double *rhsEntries)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>setMatScalars</name>
      <anchorfile>classFEI__Implementation.html</anchorfile>
      <anchor>a7ebf9fbc6647e42c0113cbaf5b7dbc36</anchor>
      <arglist>(int numScalars, const int *IDs, const double *scalars)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>setRHSScalars</name>
      <anchorfile>classFEI__Implementation.html</anchorfile>
      <anchor>afa80c6753b90441f26f627fcaeb8c934</anchor>
      <arglist>(int numScalars, const int *IDs, const double *scalars)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>loadComplete</name>
      <anchorfile>classFEI__Implementation.html</anchorfile>
      <anchor>a6de7fe855b1de339c3aedda1f9cbdbb9</anchor>
      <arglist>(bool applyBCs=true, bool globalAssemble=true)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>residualNorm</name>
      <anchorfile>classFEI__Implementation.html</anchorfile>
      <anchor>ad5bd660342a2ee2e88f30969c2be6046</anchor>
      <arglist>(int whichNorm, int numFields, int *fieldIDs, double *norms)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>solve</name>
      <anchorfile>classFEI__Implementation.html</anchorfile>
      <anchor>a50d041697b9a2f6ec4fbb49aa48ddc11</anchor>
      <arglist>(int &amp;status)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>iterations</name>
      <anchorfile>classFEI__Implementation.html</anchorfile>
      <anchor>afc15d8f37e28fa977334f974eaef927a</anchor>
      <arglist>(int &amp;itersTaken) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>version</name>
      <anchorfile>classFEI__Implementation.html</anchorfile>
      <anchor>a2d6956b44082685029a555773569f437</anchor>
      <arglist>(const char *&amp;versionString)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>cumulative_cpu_times</name>
      <anchorfile>classFEI__Implementation.html</anchorfile>
      <anchor>a9bf8a237f9ca641c70d2af340c667e38</anchor>
      <arglist>(double &amp;initTime, double &amp;loadTime, double &amp;solveTime, double &amp;solnReturnTime)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getBlockNodeSolution</name>
      <anchorfile>classFEI__Implementation.html</anchorfile>
      <anchor>a349802bc2eea1e5ad474c639db9483df</anchor>
      <arglist>(GlobalID elemBlockID, int numNodes, const GlobalID *nodeIDs, int *offsets, double *results)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getNodalSolution</name>
      <anchorfile>classFEI__Implementation.html</anchorfile>
      <anchor>ac765297233e38f77fb5d05993c81d55b</anchor>
      <arglist>(int numNodes, const GlobalID *nodeIDs, int *offsets, double *results)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getBlockFieldNodeSolution</name>
      <anchorfile>classFEI__Implementation.html</anchorfile>
      <anchor>a4d48c7e29cfde24c7ad77bdfe6e4d4b5</anchor>
      <arglist>(GlobalID elemBlockID, int fieldID, int numNodes, const GlobalID *nodeIDs, double *results)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getBlockElemSolution</name>
      <anchorfile>classFEI__Implementation.html</anchorfile>
      <anchor>a356765e8163571c24630b154f3e75e86</anchor>
      <arglist>(GlobalID elemBlockID, int numElems, const GlobalID *elemIDs, int &amp;numElemDOFPerElement, double *results)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getNumCRMultipliers</name>
      <anchorfile>classFEI__Implementation.html</anchorfile>
      <anchor>ad43dd062a0bdc8e61cab11fd35ac1992</anchor>
      <arglist>(int &amp;numMultCRs)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getCRMultIDList</name>
      <anchorfile>classFEI__Implementation.html</anchorfile>
      <anchor>a4eaa4a206e31bc50b778f824a18b7bb1</anchor>
      <arglist>(int numMultCRs, int *multIDs)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getCRMultipliers</name>
      <anchorfile>classFEI__Implementation.html</anchorfile>
      <anchor>ab65fe78d992c572c01face87cae16ddd</anchor>
      <arglist>(int numCRs, const int *CRIDs, double *multipliers)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>putBlockNodeSolution</name>
      <anchorfile>classFEI__Implementation.html</anchorfile>
      <anchor>ae9e9b07a8637c8da4eef89aa1caea93d</anchor>
      <arglist>(GlobalID elemBlockID, int numNodes, const GlobalID *nodeIDs, const int *offsets, const double *estimates)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>putBlockFieldNodeSolution</name>
      <anchorfile>classFEI__Implementation.html</anchorfile>
      <anchor>ad0e31fe716d671ab5910c538df0cadf9</anchor>
      <arglist>(GlobalID elemBlockID, int fieldID, int numNodes, const GlobalID *nodeIDs, const double *estimates)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>putBlockElemSolution</name>
      <anchorfile>classFEI__Implementation.html</anchorfile>
      <anchor>af3e8321f59190a580d085085b8ddaac7</anchor>
      <arglist>(GlobalID elemBlockID, int numElems, const GlobalID *elemIDs, int dofPerElem, const double *estimates)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>putCRMultipliers</name>
      <anchorfile>classFEI__Implementation.html</anchorfile>
      <anchor>af867b9a7ae935776d5e194be4dd384c5</anchor>
      <arglist>(int numMultCRs, const int *CRIDs, const double *multEstimates)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getBlockNodeIDList</name>
      <anchorfile>classFEI__Implementation.html</anchorfile>
      <anchor>a70f14febf1ddbb03f65ff87b1a4569ba</anchor>
      <arglist>(GlobalID elemBlockID, int numNodes, GlobalID *nodeIDs)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getBlockElemIDList</name>
      <anchorfile>classFEI__Implementation.html</anchorfile>
      <anchor>a0d3f7a29520adc9ee99b453cb3ad74f4</anchor>
      <arglist>(GlobalID elemBlockID, int numElems, GlobalID *elemIDs)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getNumSolnParams</name>
      <anchorfile>classFEI__Implementation.html</anchorfile>
      <anchor>ae394fd13b65aafa22d67f516a67132d3</anchor>
      <arglist>(GlobalID nodeID, int &amp;numSolnParams) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getNumElemBlocks</name>
      <anchorfile>classFEI__Implementation.html</anchorfile>
      <anchor>a359926f524bbdd42f5890e4bde8ef338</anchor>
      <arglist>(int &amp;numElemBlocks) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getNumBlockActNodes</name>
      <anchorfile>classFEI__Implementation.html</anchorfile>
      <anchor>a6d88c55c2ff6da0d8f6924e8a13fce1e</anchor>
      <arglist>(GlobalID blockID, int &amp;numNodes) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getNumBlockActEqns</name>
      <anchorfile>classFEI__Implementation.html</anchorfile>
      <anchor>aa42892a7404c28f506a80bd93068101f</anchor>
      <arglist>(GlobalID blockID, int &amp;numEqns) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getNumNodesPerElement</name>
      <anchorfile>classFEI__Implementation.html</anchorfile>
      <anchor>ae89444301daae4895014c5cf6c0cb397</anchor>
      <arglist>(GlobalID blockID, int &amp;nodesPerElem) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getNumEqnsPerElement</name>
      <anchorfile>classFEI__Implementation.html</anchorfile>
      <anchor>a494495644341cc9e9f58856f9906b3e8</anchor>
      <arglist>(GlobalID blockID, int &amp;numEqns) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getNumBlockElements</name>
      <anchorfile>classFEI__Implementation.html</anchorfile>
      <anchor>a5c32667fd4cd70f2e9c6e7a508facc41</anchor>
      <arglist>(GlobalID blockID, int &amp;numElems) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getNumBlockElemDOF</name>
      <anchorfile>classFEI__Implementation.html</anchorfile>
      <anchor>a56d0841311277c0fb8c246dee5bf68dc</anchor>
      <arglist>(GlobalID blockID, int &amp;DOFPerElem) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getParameters</name>
      <anchorfile>classFEI__Implementation.html</anchorfile>
      <anchor>ad1bed3734f16f57a72c30e2f44db0c4d</anchor>
      <arglist>(int &amp;numParams, char **&amp;paramStrings)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getFieldSize</name>
      <anchorfile>classFEI__Implementation.html</anchorfile>
      <anchor>a98becfbf9b28829832220fcb60074906</anchor>
      <arglist>(int fieldID, int &amp;numScalars)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getEqnNumbers</name>
      <anchorfile>classFEI__Implementation.html</anchorfile>
      <anchor>a1ae930a317b51423186fd0931a07dc58</anchor>
      <arglist>(GlobalID ID, int idType, int fieldID, int &amp;numEqns, int *eqnNumbers)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getNodalFieldSolution</name>
      <anchorfile>classFEI__Implementation.html</anchorfile>
      <anchor>aa986c4b36201ffab755488a5ca974a21</anchor>
      <arglist>(int fieldID, int numNodes, const GlobalID *nodeIDs, double *results)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getNumLocalNodes</name>
      <anchorfile>classFEI__Implementation.html</anchorfile>
      <anchor>ac5d6fd179a2b3fbc3f4e84e448174693</anchor>
      <arglist>(int &amp;numNodes)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getLocalNodeIDList</name>
      <anchorfile>classFEI__Implementation.html</anchorfile>
      <anchor>abd0791fd26fd0e4dfe028fb1a43c144c</anchor>
      <arglist>(int &amp;numNodes, GlobalID *nodeIDs, int lenNodeIDs)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>putNodalFieldData</name>
      <anchorfile>classFEI__Implementation.html</anchorfile>
      <anchor>a11eece07062fda5cdf686a96abcea74c</anchor>
      <arglist>(int fieldID, int numNodes, const GlobalID *nodeIDs, const double *nodeData)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>fei_Pool_alloc</name>
    <filename>classfei__Pool__alloc.html</filename>
    <templarg>T</templarg>
  </compound>
  <compound kind="class">
    <name>fei_Pool_alloc&lt; ctg_set&lt; int &gt; &gt;</name>
    <filename>classfei__Pool__alloc.html</filename>
  </compound>
  <compound kind="class">
    <name>fei_Pool_alloc&lt; fei::CSVec &gt;</name>
    <filename>classfei__Pool__alloc.html</filename>
  </compound>
  <compound kind="class">
    <name>fei_Pool_alloc&lt; NodeDescriptor &gt;</name>
    <filename>classfei__Pool__alloc.html</filename>
  </compound>
  <compound kind="class">
    <name>fei_Pool_alloc&lt; SET_TYPE &gt;</name>
    <filename>classfei__Pool__alloc.html</filename>
  </compound>
  <compound kind="class">
    <name>feitester</name>
    <filename>classfeitester.html</filename>
    <member kind="function" virtualness="pure">
      <type>virtual const char *</type>
      <name>getName</name>
      <anchorfile>classfeitester.html</anchorfile>
      <anchor>ae1b545722a808799e142eb5cd05bd907</anchor>
      <arglist>()=0</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>snl_fei::FEMatrixTraits</name>
    <filename>structsnl__fei_1_1FEMatrixTraits.html</filename>
    <templarg></templarg>
    <member kind="function" static="yes">
      <type>static const char *</type>
      <name>typeName</name>
      <anchorfile>structsnl__fei_1_1FEMatrixTraits.html</anchorfile>
      <anchor>a16a957f55e261bfb381a7b333f80df62</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static int</type>
      <name>reset</name>
      <anchorfile>structsnl__fei_1_1FEMatrixTraits.html</anchorfile>
      <anchor>ac62937a77f71d81799794024501d8e1e</anchor>
      <arglist>(T *mat)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static int</type>
      <name>sumInElemMatrix</name>
      <anchorfile>structsnl__fei_1_1FEMatrixTraits.html</anchorfile>
      <anchor>a748c4afd5d913b7c9175b42ff5a03589</anchor>
      <arglist>(T *mat, int elemBlockID, int elemID, int numNodes, const int *nodeNumbers, const int *dofPerNode, const int *dof_ids, const double *const *coefs)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static int</type>
      <name>setDirichletBCs</name>
      <anchorfile>structsnl__fei_1_1FEMatrixTraits.html</anchorfile>
      <anchor>a7a01f1c0b0b7b913db79ac68cdfff2d6</anchor>
      <arglist>(T *mat, int numBCs, const int *nodeNumbers, const int *dof_ids, const double *values)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>snl_fei::FEMatrixTraits&lt; FiniteElementData &gt;</name>
    <filename>structsnl__fei_1_1FEMatrixTraits_3_01FiniteElementData_01_4.html</filename>
    <member kind="function" static="yes">
      <type>static const char *</type>
      <name>typeName</name>
      <anchorfile>structsnl__fei_1_1FEMatrixTraits_3_01FiniteElementData_01_4.html</anchorfile>
      <anchor>a0359a1fce47dfb7e746dfe64339f09b8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static int</type>
      <name>reset</name>
      <anchorfile>structsnl__fei_1_1FEMatrixTraits_3_01FiniteElementData_01_4.html</anchorfile>
      <anchor>a61c34d005dd7d54da73d2c2ec40dd086</anchor>
      <arglist>(FiniteElementData *mat)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static int</type>
      <name>sumInElemMatrix</name>
      <anchorfile>structsnl__fei_1_1FEMatrixTraits_3_01FiniteElementData_01_4.html</anchorfile>
      <anchor>a909a5074e7daf7939d3f4cba0d8caa11</anchor>
      <arglist>(FiniteElementData *mat, int elemBlockID, int elemID, int numNodes, const int *nodeNumbers, const int *dofPerNode, const int *dof_ids, const double *const *coefs)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static int</type>
      <name>setDirichletBCs</name>
      <anchorfile>structsnl__fei_1_1FEMatrixTraits_3_01FiniteElementData_01_4.html</anchorfile>
      <anchor>a0e15102967ab9826fd8932b0b740f4f7</anchor>
      <arglist>(FiniteElementData *mat, int numBCs, const int *nodeNumbers, const int *dof_ids, const double *values)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>snl_fei::FEVectorTraits</name>
    <filename>structsnl__fei_1_1FEVectorTraits.html</filename>
    <templarg></templarg>
    <member kind="function" static="yes">
      <type>static const char *</type>
      <name>typeName</name>
      <anchorfile>structsnl__fei_1_1FEVectorTraits.html</anchorfile>
      <anchor>aa01e8f519691abcb4f9a92c0665c6a56</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static int</type>
      <name>reset</name>
      <anchorfile>structsnl__fei_1_1FEVectorTraits.html</anchorfile>
      <anchor>a1af4c575dff2d7c7f9e9503137eacac8</anchor>
      <arglist>(T *)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static int</type>
      <name>sumInElemVector</name>
      <anchorfile>structsnl__fei_1_1FEVectorTraits.html</anchorfile>
      <anchor>ada938a89b4fb17c0875f358fa876de26</anchor>
      <arglist>(T *, int, int, int, const int *, const int *, const int *, const double *)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static int</type>
      <name>copyOut</name>
      <anchorfile>structsnl__fei_1_1FEVectorTraits.html</anchorfile>
      <anchor>a39099da8ce08e7e2f35b9d668669eaec</anchor>
      <arglist>(T *, int, int, double &amp;)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>snl_fei::FEVectorTraits&lt; FiniteElementData &gt;</name>
    <filename>structsnl__fei_1_1FEVectorTraits_3_01FiniteElementData_01_4.html</filename>
    <member kind="function" static="yes">
      <type>static const char *</type>
      <name>typeName</name>
      <anchorfile>structsnl__fei_1_1FEVectorTraits_3_01FiniteElementData_01_4.html</anchorfile>
      <anchor>a47924967ab4cdf7836a29fc8aaeaca3c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static int</type>
      <name>reset</name>
      <anchorfile>structsnl__fei_1_1FEVectorTraits_3_01FiniteElementData_01_4.html</anchorfile>
      <anchor>a2687d6ffea3af17c68a471ccc9862582</anchor>
      <arglist>(FiniteElementData *vec)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static int</type>
      <name>sumInElemVector</name>
      <anchorfile>structsnl__fei_1_1FEVectorTraits_3_01FiniteElementData_01_4.html</anchorfile>
      <anchor>aeeb67c14f57d73d8d6f3fbb40f96a067</anchor>
      <arglist>(FiniteElementData *vec, int elemBlockID, int elemID, int numNodes, const int *nodeNumbers, const int *dofPerNode, const int *dof_ids, const double *coefs)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static int</type>
      <name>copyOut</name>
      <anchorfile>structsnl__fei_1_1FEVectorTraits_3_01FiniteElementData_01_4.html</anchorfile>
      <anchor>af635279378d97d0bffc6cb9248813907</anchor>
      <arglist>(FiniteElementData *vec, int nodeNumber, int dofOffset, double &amp;value)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>fei::FieldDofMap</name>
    <filename>classfei_1_1FieldDofMap.html</filename>
    <templarg>LocalOrdinal</templarg>
  </compound>
  <compound kind="class">
    <name>FieldDofMap&lt; int &gt;</name>
    <filename>classfei_1_1FieldDofMap.html</filename>
  </compound>
  <compound kind="class">
    <name>fei::FieldMask</name>
    <filename>classfei_1_1FieldMask.html</filename>
    <member kind="function">
      <type></type>
      <name>FieldMask</name>
      <anchorfile>classfei_1_1FieldMask.html</anchorfile>
      <anchor>a407f33be9421fa086f4e5e8f012a5f2e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>FieldMask</name>
      <anchorfile>classfei_1_1FieldMask.html</anchorfile>
      <anchor>ac5c24a56aa2e65fe83faceb7ba0013af</anchor>
      <arglist>(const FieldMask &amp;fm)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>FieldMask</name>
      <anchorfile>classfei_1_1FieldMask.html</anchorfile>
      <anchor>a1f9746981305365ca2252cb7c5b59594</anchor>
      <arglist>(int numFields, const int *fieldIDs, const int *fieldSizes)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~FieldMask</name>
      <anchorfile>classfei_1_1FieldMask.html</anchorfile>
      <anchor>a8577c70e05d16841cb935cb8814413aa</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getMaskID</name>
      <anchorfile>classfei_1_1FieldMask.html</anchorfile>
      <anchor>ae37d55357afbd26619db1ea261e6f8a8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>addField</name>
      <anchorfile>classfei_1_1FieldMask.html</anchorfile>
      <anchor>acb9e668738d31e7b097df7c72b25c02c</anchor>
      <arglist>(int fieldID, int fieldSize)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>hasFieldID</name>
      <anchorfile>classfei_1_1FieldMask.html</anchorfile>
      <anchor>aba42f73f2b401c3920b1b523401c1768</anchor>
      <arglist>(int fieldID) const </arglist>
    </member>
    <member kind="function">
      <type>size_t</type>
      <name>getNumFields</name>
      <anchorfile>classfei_1_1FieldMask.html</anchorfile>
      <anchor>aebf525aab8ed5c6434f6b1b307e0f98d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getNumIndices</name>
      <anchorfile>classfei_1_1FieldMask.html</anchorfile>
      <anchor>aa8328061d7e4d7d1452756aeef488cdc</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setNumIndices</name>
      <anchorfile>classfei_1_1FieldMask.html</anchorfile>
      <anchor>aa4659bb35f67ec006ea2824c55f1e083</anchor>
      <arglist>(int numInd)</arglist>
    </member>
    <member kind="function">
      <type>std::vector&lt; int &gt; &amp;</type>
      <name>getFieldIDs</name>
      <anchorfile>classfei_1_1FieldMask.html</anchorfile>
      <anchor>a3b5b74797b913c75fcdcb9b4f4e01cac</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const std::vector&lt; int &gt; &amp;</type>
      <name>getFieldIDs</name>
      <anchorfile>classfei_1_1FieldMask.html</anchorfile>
      <anchor>aefc0c10d916736e72f36c7ae25ee2eec</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>std::vector&lt; int &gt; &amp;</type>
      <name>getFieldSizes</name>
      <anchorfile>classfei_1_1FieldMask.html</anchorfile>
      <anchor>a368842f120a01ad20a724af12fc8cf58</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const std::vector&lt; int &gt; &amp;</type>
      <name>getFieldSizes</name>
      <anchorfile>classfei_1_1FieldMask.html</anchorfile>
      <anchor>a812739092e046595662b83f8712cc0f9</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getFieldEqnOffset</name>
      <anchorfile>classfei_1_1FieldMask.html</anchorfile>
      <anchor>a2ccc8fd93bd2faec122d4b915199cb62</anchor>
      <arglist>(int fieldID, int &amp;offset) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator==</name>
      <anchorfile>classfei_1_1FieldMask.html</anchorfile>
      <anchor>aeef79ad3c182a0bd7a3fc5e882833e30</anchor>
      <arglist>(const FieldMask &amp;fm) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator!=</name>
      <anchorfile>classfei_1_1FieldMask.html</anchorfile>
      <anchor>a4d7069d25bc6af203688527895784620</anchor>
      <arglist>(const FieldMask &amp;fm) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isSubSetOf</name>
      <anchorfile>classfei_1_1FieldMask.html</anchorfile>
      <anchor>aa9b45cf74586ae634450e5dc280e8caf</anchor>
      <arglist>(const FieldMask &amp;fm) const </arglist>
    </member>
    <member kind="function" static="yes">
      <type>static int</type>
      <name>calculateMaskID</name>
      <anchorfile>classfei_1_1FieldMask.html</anchorfile>
      <anchor>a51aa220cc2bb8a96994816dd9458d6c2</anchor>
      <arglist>(int numFields, const int *fieldIDs)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static int</type>
      <name>calculateMaskID</name>
      <anchorfile>classfei_1_1FieldMask.html</anchorfile>
      <anchor>a7d893a2611436982ea98a890dd3e37f5</anchor>
      <arglist>(const FieldMask &amp;fm, int fieldID)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Filter</name>
    <filename>classFilter.html</filename>
    <member kind="function">
      <type></type>
      <name>Filter</name>
      <anchorfile>classFilter.html</anchorfile>
      <anchor>a2905f3297020a7f314a20130ab0eda00</anchor>
      <arglist>(SNL_FEI_Structure *probStruct)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~Filter</name>
      <anchorfile>classFilter.html</anchorfile>
      <anchor>a502ee334d42eac3edbaf32b599f9c35e</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>FiniteElementData</name>
    <filename>classFiniteElementData.html</filename>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>parameters</name>
      <anchorfile>classFiniteElementData.html</anchorfile>
      <anchor>aada4d7f3ffc0219caa91a76711d220c8</anchor>
      <arglist>(int numParams, char **params)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>setLookup</name>
      <anchorfile>classFiniteElementData.html</anchorfile>
      <anchor>a24f992f8b302e8b866ca1a3b9808c3d4</anchor>
      <arglist>(Lookup &amp;lookup)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>describeStructure</name>
      <anchorfile>classFiniteElementData.html</anchorfile>
      <anchor>a53afd726f364397eb6c90d80ab09368b</anchor>
      <arglist>(int numElemBlocks, const int *numElemsPerBlock, const int *numNodesPerElem, const int *elemMatrixSizePerBlock, int totalNumNodes, int numSharedNodes, int numMultCRs)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>setConnectivity</name>
      <anchorfile>classFiniteElementData.html</anchorfile>
      <anchor>a5d1d3227267acbfbef72f85cf3f8e41d</anchor>
      <arglist>(int elemBlockID, int elemID, int numNodes, const int *nodeNumbers, const int *numDofPerNode, const int *dof_ids)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>setElemMatrix</name>
      <anchorfile>classFiniteElementData.html</anchorfile>
      <anchor>a2dde1c7a04e77f15d9e31133b043d627</anchor>
      <arglist>(int elemBlockID, int elemID, int numNodes, const int *nodeNumbers, const int *numDofPerNode, const int *dof_ids, const double *const *coefs)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>setElemVector</name>
      <anchorfile>classFiniteElementData.html</anchorfile>
      <anchor>a6b0b28a4548d7096fae244c93d91b72b</anchor>
      <arglist>(int elemBlockID, int elemID, int numNodes, const int *nodeNumbers, const int *numDofPerNode, const int *dof_ids, const double *coefs)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>setDirichletBCs</name>
      <anchorfile>classFiniteElementData.html</anchorfile>
      <anchor>a0eef2ed58fee8da737e5b7c9e4a1386d</anchor>
      <arglist>(int numBCs, const int *nodeNumbers, const int *dof_ids, const double *values)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>sumIntoMatrix</name>
      <anchorfile>classFiniteElementData.html</anchorfile>
      <anchor>a4167eb43a1a0d8685343a1f39ca55cac</anchor>
      <arglist>(int numRowNodes, const int *rowNodeNumbers, const int *row_dof_ids, const int *numColNodesPerRow, const int *colNodeNumbers, const int *col_dof_ids, const double *coefs)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>loadComplete</name>
      <anchorfile>classFiniteElementData.html</anchorfile>
      <anchor>a8a7ed8f9503e233604b17f97ce9417b9</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>launchSolver</name>
      <anchorfile>classFiniteElementData.html</anchorfile>
      <anchor>aa3a9c5a9332d973f152797235ef556be</anchor>
      <arglist>(int &amp;solveStatus, int &amp;iterations)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>reset</name>
      <anchorfile>classFiniteElementData.html</anchorfile>
      <anchor>a602e32bb6a1147a7101aace065d371ad</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>deleteConstraints</name>
      <anchorfile>classFiniteElementData.html</anchorfile>
      <anchor>a6608e0106cedc23cda8be0423074a968</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>getSolnEntry</name>
      <anchorfile>classFiniteElementData.html</anchorfile>
      <anchor>acd36c3e8bba1b451f345b9554bbf1ea5</anchor>
      <arglist>(int nodeNumber, int dof_id, double &amp;value)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>getMultiplierSoln</name>
      <anchorfile>classFiniteElementData.html</anchorfile>
      <anchor>ad3221e0984a9b882a98c52a1ebd3779f</anchor>
      <arglist>(int CRID, double &amp;lagrangeMultiplier)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>putNodalFieldData</name>
      <anchorfile>classFiniteElementData.html</anchorfile>
      <anchor>aeff979c137246a2b82fcb6c753cf5fbe</anchor>
      <arglist>(int fieldID, int fieldSize, int numNodes, const int *nodeNumbers, const double *coefs)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>setMultiplierCR</name>
      <anchorfile>classFiniteElementData.html</anchorfile>
      <anchor>a147b2e5082ad0f09c5bea7c772976d33</anchor>
      <arglist>(int CRID, int numNodes, const int *nodeNumbers, const int *dof_ids, const double *coefWeights, double rhsValue)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>setPenaltyCR</name>
      <anchorfile>classFiniteElementData.html</anchorfile>
      <anchor>abb70546295f335c2dd3d735edc354e8e</anchor>
      <arglist>(int CRID, int numNodes, const int *nodeNumbers, const int *dof_ids, const double *coefWeights, double penaltyValue, double rhsValue)=0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>fei::Graph</name>
    <filename>classfei_1_1Graph.html</filename>
    <member kind="typedef">
      <type>snl_fei::RaggedTable&lt; snl_fei::MapContig&lt; fei::ctg_set&lt; int &gt; * &gt;, fei::ctg_set&lt; int &gt; &gt;</type>
      <name>table_type</name>
      <anchorfile>classfei_1_1Graph.html</anchorfile>
      <anchor>ab182699b5376be4f547b8e962de9c327</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>fei::ctg_set&lt; int &gt;</type>
      <name>table_row_type</name>
      <anchorfile>classfei_1_1Graph.html</anchorfile>
      <anchor>a64066d49b46b7ed51845078f943b0d89</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>snl_fei::RaggedTable&lt; std::map&lt; int, fei::ctg_set&lt; int &gt; * &gt;, fei::ctg_set&lt; int &gt; &gt;</type>
      <name>remote_table_type</name>
      <anchorfile>classfei_1_1Graph.html</anchorfile>
      <anchor>a1eccb9d5fd1500e57ae557651d72eb4a</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~Graph</name>
      <anchorfile>classfei_1_1Graph.html</anchorfile>
      <anchor>a25de1828569aa6e5a297c50acf15c2cc</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>addIndices</name>
      <anchorfile>classfei_1_1Graph.html</anchorfile>
      <anchor>a5b20a80fe993e8a38a08510fc88546db</anchor>
      <arglist>(int row, int len, const int *indices)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>addSymmetricIndices</name>
      <anchorfile>classfei_1_1Graph.html</anchorfile>
      <anchor>a8b20ef9b9e352770fd63159656085449</anchor>
      <arglist>(int numIndices, int *indices, bool diagonal=false)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>gatherFromOverlap</name>
      <anchorfile>classfei_1_1Graph.html</anchorfile>
      <anchor>a71412c211ba59c219b790b18d36cde36</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual table_type *</type>
      <name>getLocalGraph</name>
      <anchorfile>classfei_1_1Graph.html</anchorfile>
      <anchor>af119a7cc78e624b309b933e39f507b61</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual std::vector&lt; remote_table_type * &gt; &amp;</type>
      <name>getRemoteGraph</name>
      <anchorfile>classfei_1_1Graph.html</anchorfile>
      <anchor>a22e64cd35ab407b9c79a04c735fafbfe</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>writeLocalGraph</name>
      <anchorfile>classfei_1_1Graph.html</anchorfile>
      <anchor>a80690e5c6f94fda4c0da15405ea7a7aa</anchor>
      <arglist>(FEI_OSTREAM &amp;os, bool debug=false, bool prefixLinesWithPoundSign=true)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>writeRemoteGraph</name>
      <anchorfile>classfei_1_1Graph.html</anchorfile>
      <anchor>af6af3569f3ab5cb3a16f86ce3ca973b0</anchor>
      <arglist>(FEI_OSTREAM &amp;os)=0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>fei::Graph_Impl</name>
    <filename>classfei_1_1Graph__Impl.html</filename>
    <base>fei::Graph</base>
    <member kind="function">
      <type></type>
      <name>Graph_Impl</name>
      <anchorfile>classfei_1_1Graph__Impl.html</anchorfile>
      <anchor>a81e045b03a0001372955e35c93f65bc4</anchor>
      <arglist>(MPI_Comm comm, int firstLocalRow, int lastLocalRow)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~Graph_Impl</name>
      <anchorfile>classfei_1_1Graph__Impl.html</anchorfile>
      <anchor>a029943d7944f1a6bfad81c1f299905ee</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>addIndices</name>
      <anchorfile>classfei_1_1Graph__Impl.html</anchorfile>
      <anchor>a1758122555bb67308edf5ad36a1f5b87</anchor>
      <arglist>(int row, int len, const int *indices)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>addSymmetricIndices</name>
      <anchorfile>classfei_1_1Graph__Impl.html</anchorfile>
      <anchor>ada47e94d03a98ac2b6154a6f8187d855</anchor>
      <arglist>(int numIndices, int *indices, bool diagonal=false)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>gatherFromOverlap</name>
      <anchorfile>classfei_1_1Graph__Impl.html</anchorfile>
      <anchor>a9b3780731f9523af5a325d2ca97b84e8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>table_type *</type>
      <name>getLocalGraph</name>
      <anchorfile>classfei_1_1Graph__Impl.html</anchorfile>
      <anchor>a0b05f7e61b0d222f3f729de7c5752dba</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>std::vector&lt; remote_table_type * &gt; &amp;</type>
      <name>getRemoteGraph</name>
      <anchorfile>classfei_1_1Graph__Impl.html</anchorfile>
      <anchor>add90bdd7c4643d1904f416c1652160b6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>writeLocalGraph</name>
      <anchorfile>classfei_1_1Graph__Impl.html</anchorfile>
      <anchor>a83858d471c5248a0acaa7adc3ffdcbc8</anchor>
      <arglist>(FEI_OSTREAM &amp;os, bool debug=false, bool prefixLinesWithPoundSign=true)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>writeRemoteGraph</name>
      <anchorfile>classfei_1_1Graph__Impl.html</anchorfile>
      <anchor>a847af5e8863c16ae9a4c469c53574419</anchor>
      <arglist>(FEI_OSTREAM &amp;os)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getNumLocalRows</name>
      <anchorfile>classfei_1_1Graph__Impl.html</anchorfile>
      <anchor>a8b62d25b082abe8df721e7d7e1fb6901</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getNumLocalNonzeros</name>
      <anchorfile>classfei_1_1Graph__Impl.html</anchorfile>
      <anchor>aa3407759c8bc51aac8c8f1a7445f5996</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getLocalRowLength</name>
      <anchorfile>classfei_1_1Graph__Impl.html</anchorfile>
      <anchor>a12a06c622d5ab563d8fc7cf38e318f60</anchor>
      <arglist>(int row)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>fei::GraphReducer</name>
    <filename>classfei_1_1GraphReducer.html</filename>
    <base>fei::Graph</base>
    <member kind="function">
      <type></type>
      <name>GraphReducer</name>
      <anchorfile>classfei_1_1GraphReducer.html</anchorfile>
      <anchor>a40e88dba087699804cc7081518912370</anchor>
      <arglist>(fei::SharedPtr&lt; fei::Reducer &gt; reducer, fei::SharedPtr&lt; fei::Graph &gt; target)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~GraphReducer</name>
      <anchorfile>classfei_1_1GraphReducer.html</anchorfile>
      <anchor>a427eb38db400abbcfffe2f807099d2c1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>addIndices</name>
      <anchorfile>classfei_1_1GraphReducer.html</anchorfile>
      <anchor>a154bd01951561b822f7bcc9ad7c161f9</anchor>
      <arglist>(int row, int len, const int *indices)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>addSymmetricIndices</name>
      <anchorfile>classfei_1_1GraphReducer.html</anchorfile>
      <anchor>a2d64c3c024031777cb7b4834ffacf832</anchor>
      <arglist>(int numIndices, int *indices, bool diagonal=false)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>gatherFromOverlap</name>
      <anchorfile>classfei_1_1GraphReducer.html</anchorfile>
      <anchor>a8983c8e7eff1f2d58d8a9518e5ec4f4c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>table_type *</type>
      <name>getLocalGraph</name>
      <anchorfile>classfei_1_1GraphReducer.html</anchorfile>
      <anchor>aab32358d461190e954cf40ba76b84505</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>std::vector&lt; remote_table_type * &gt; &amp;</type>
      <name>getRemoteGraph</name>
      <anchorfile>classfei_1_1GraphReducer.html</anchorfile>
      <anchor>aafa9cc0df21648944665095b1ea82062</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>writeLocalGraph</name>
      <anchorfile>classfei_1_1GraphReducer.html</anchorfile>
      <anchor>a464b855447cd5248c7c7daa4e75fc04f</anchor>
      <arglist>(FEI_OSTREAM &amp;os, bool debug=false, bool prefixLinesWithPoundSign=true)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>writeRemoteGraph</name>
      <anchorfile>classfei_1_1GraphReducer.html</anchorfile>
      <anchor>a5e512346e02a6ebb96e8463cfc0ac03f</anchor>
      <arglist>(FEI_OSTREAM &amp;os)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>HexBeam</name>
    <filename>classHexBeam.html</filename>
  </compound>
  <compound kind="class">
    <name>HexBeamCR</name>
    <filename>classHexBeamCR.html</filename>
    <base>HexBeam</base>
  </compound>
  <compound kind="class">
    <name>fei::IndexTable</name>
    <filename>classfei_1_1IndexTable.html</filename>
    <member kind="function">
      <type></type>
      <name>IndexTable</name>
      <anchorfile>classfei_1_1IndexTable.html</anchorfile>
      <anchor>a47b8add70e3e6a28db784fa768207122</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~IndexTable</name>
      <anchorfile>classfei_1_1IndexTable.html</anchorfile>
      <anchor>a00953b5287b0bff736e295e7335e3c05</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>addDiagonals</name>
      <anchorfile>classfei_1_1IndexTable.html</anchorfile>
      <anchor>a94808cd37ba39f59267295fa76398d1c</anchor>
      <arglist>(int numIndices, const int *indices)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>addIndices</name>
      <anchorfile>classfei_1_1IndexTable.html</anchorfile>
      <anchor>a222116f2e80e826413c250a4b5fb05e6</anchor>
      <arglist>(int row, int numIndices, const int *indices)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>addIndices</name>
      <anchorfile>classfei_1_1IndexTable.html</anchorfile>
      <anchor>a39f467fb7f96507a65fbff20a46cadb8</anchor>
      <arglist>(int numRows, const int *rows, int numIndices, const int *indices)=0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>snl_fei::MapContig::iterator</name>
    <filename>classsnl__fei_1_1MapContig_1_1iterator.html</filename>
    <member kind="function">
      <type></type>
      <name>iterator</name>
      <anchorfile>classsnl__fei_1_1MapContig_1_1iterator.html</anchorfile>
      <anchor>acd292f3192ef0f0d5412086feae4f507</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>iterator</name>
      <anchorfile>classsnl__fei_1_1MapContig_1_1iterator.html</anchorfile>
      <anchor>a3d333f2f229106ac8fd77b88b2083eb6</anchor>
      <arglist>(int offset, MapContig&lt; VAL_TYPE &gt; *mapPtr)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~iterator</name>
      <anchorfile>classsnl__fei_1_1MapContig_1_1iterator.html</anchorfile>
      <anchor>aba943d09ce69e9c632f3523612364852</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>iterator &amp;</type>
      <name>operator++</name>
      <anchorfile>classsnl__fei_1_1MapContig_1_1iterator.html</anchorfile>
      <anchor>a8803504e3f4d443ddb7fd4f0860638d7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator==</name>
      <anchorfile>classsnl__fei_1_1MapContig_1_1iterator.html</anchorfile>
      <anchor>aeead17764ca86715eaa375ce341a8647</anchor>
      <arglist>(const iterator &amp;rhs)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator!=</name>
      <anchorfile>classsnl__fei_1_1MapContig_1_1iterator.html</anchorfile>
      <anchor>a2e17992151eaf2d8a17e2e63488a4e99</anchor>
      <arglist>(const iterator &amp;rhs)</arglist>
    </member>
    <member kind="function">
      <type>value_type</type>
      <name>operator*</name>
      <anchorfile>classsnl__fei_1_1MapContig_1_1iterator.html</anchorfile>
      <anchor>a9f6be298cde61961685313b584f4c779</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>iterator &amp;</type>
      <name>operator=</name>
      <anchorfile>classsnl__fei_1_1MapContig_1_1iterator.html</anchorfile>
      <anchor>aa188e39249f6d5487ded74f9ef174934</anchor>
      <arglist>(const iterator &amp;src)</arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>offset_</name>
      <anchorfile>classsnl__fei_1_1MapContig_1_1iterator.html</anchorfile>
      <anchor>a82ffe650e5ed927f7ce805a762a8ee8f</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>fei::less_field_rank_id</name>
    <filename>structfei_1_1less__field__rank__id.html</filename>
    <templarg></templarg>
    <templarg></templarg>
  </compound>
  <compound kind="struct">
    <name>fei::less_rank_id_field</name>
    <filename>structfei_1_1less__rank__id__field.html</filename>
    <templarg></templarg>
    <templarg></templarg>
  </compound>
  <compound kind="class">
    <name>fei::LinearProblemManager</name>
    <filename>classfei_1_1LinearProblemManager.html</filename>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~LinearProblemManager</name>
      <anchorfile>classfei_1_1LinearProblemManager.html</anchorfile>
      <anchor>a0085a20656aa19c7184753233467142c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>setRowDistribution</name>
      <anchorfile>classfei_1_1LinearProblemManager.html</anchorfile>
      <anchor>a68de29c19d2cfd12e73cdd5c2222c311</anchor>
      <arglist>(const std::vector&lt; int &gt; &amp;ownedGlobalRows)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>setMatrixGraph</name>
      <anchorfile>classfei_1_1LinearProblemManager.html</anchorfile>
      <anchor>a12412803327abb862303eb2d5f888abf</anchor>
      <arglist>(fei::SharedPtr&lt; fei::SparseRowGraph &gt; matrixGraph)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>setMatrixValues</name>
      <anchorfile>classfei_1_1LinearProblemManager.html</anchorfile>
      <anchor>a4c5996896c2e9da145b6b740c12dea20</anchor>
      <arglist>(double scalar)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>getLocalNumRows</name>
      <anchorfile>classfei_1_1LinearProblemManager.html</anchorfile>
      <anchor>ab01fccb9b80d6261857dd137671882ed</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>getRowLength</name>
      <anchorfile>classfei_1_1LinearProblemManager.html</anchorfile>
      <anchor>af735c076e4feac04a2557b0d3fcd9a05</anchor>
      <arglist>(int row)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>copyOutMatrixRow</name>
      <anchorfile>classfei_1_1LinearProblemManager.html</anchorfile>
      <anchor>a4bde84ca63ec593ec588ff05a7341889</anchor>
      <arglist>(int row, int len, double *coefs, int *indices)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>insertMatrixValues</name>
      <anchorfile>classfei_1_1LinearProblemManager.html</anchorfile>
      <anchor>a7eeba1ed6a7e49d7886e567db9383442</anchor>
      <arglist>(int numRows, const int *rows, int numCols, const int *cols, const double *const *values, bool sum_into)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>setVectorValues</name>
      <anchorfile>classfei_1_1LinearProblemManager.html</anchorfile>
      <anchor>ae1ddc8f666720d18b9ab88974859e1bf</anchor>
      <arglist>(double scalar, bool soln_vector)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>insertVectorValues</name>
      <anchorfile>classfei_1_1LinearProblemManager.html</anchorfile>
      <anchor>a9cd3fceda9591ebf12ec765d83ab4450</anchor>
      <arglist>(int numValues, const int *globalIndices, const double *values, bool sum_into, bool soln_vector, int vectorIndex=0)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>copyOutVectorValues</name>
      <anchorfile>classfei_1_1LinearProblemManager.html</anchorfile>
      <anchor>a79ddb5afd8162b57375d6b8ad78a1963</anchor>
      <arglist>(int numValues, const int *globalIndices, double *values, bool soln_vector, int vectorIndex=0)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual double *</type>
      <name>getLocalVectorValuesPtr</name>
      <anchorfile>classfei_1_1LinearProblemManager.html</anchorfile>
      <anchor>a7ce93968c2c0c9f7b36b437b49cd9e7e</anchor>
      <arglist>(bool soln_vector, int vectorIndex=0)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>globalAssemble</name>
      <anchorfile>classfei_1_1LinearProblemManager.html</anchorfile>
      <anchor>aaf7e813184b06d20b0d6bc72e3ec84ca</anchor>
      <arglist>()=0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>fei::LinearSystem</name>
    <filename>classfei_1_1LinearSystem.html</filename>
    <class kind="class">fei::LinearSystem::Factory</class>
    <member kind="function">
      <type></type>
      <name>LinearSystem</name>
      <anchorfile>classfei_1_1LinearSystem.html</anchorfile>
      <anchor>a5a11260d680a59917cf9025172a883a5</anchor>
      <arglist>(fei::SharedPtr&lt; fei::MatrixGraph &gt; &amp;matrixGraph)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~LinearSystem</name>
      <anchorfile>classfei_1_1LinearSystem.html</anchorfile>
      <anchor>a744bf4c7bd4cc6041acb2f5b003b3cf3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>parameters</name>
      <anchorfile>classfei_1_1LinearSystem.html</anchorfile>
      <anchor>a7ecdfabee8685e30225239cbbca371d8</anchor>
      <arglist>(int numParams, const char *const *paramStrings)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>parameters</name>
      <anchorfile>classfei_1_1LinearSystem.html</anchorfile>
      <anchor>a5583a85238a62ae726b4866dec4c7e3f</anchor>
      <arglist>(const fei::ParameterSet &amp;params)=0</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>setMatrix</name>
      <anchorfile>classfei_1_1LinearSystem.html</anchorfile>
      <anchor>ad549e2f901cad222f28448a0c622828c</anchor>
      <arglist>(fei::SharedPtr&lt; fei::Matrix &gt; &amp;matrix)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual fei::SharedPtr&lt; fei::Matrix &gt;</type>
      <name>getMatrix</name>
      <anchorfile>classfei_1_1LinearSystem.html</anchorfile>
      <anchor>a2ffde84094d31112f0e7142ae4a9d297</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual fei::SharedPtr&lt; const fei::Matrix &gt;</type>
      <name>getMatrix</name>
      <anchorfile>classfei_1_1LinearSystem.html</anchorfile>
      <anchor>aa098a2a78c798835ba013bf7531f0277</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>setRHS</name>
      <anchorfile>classfei_1_1LinearSystem.html</anchorfile>
      <anchor>a1a84be580a06119d78c6bd5ec4dc447f</anchor>
      <arglist>(fei::SharedPtr&lt; fei::Vector &gt; &amp;rhs)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual fei::SharedPtr&lt; fei::Vector &gt;</type>
      <name>getRHS</name>
      <anchorfile>classfei_1_1LinearSystem.html</anchorfile>
      <anchor>ae7dd8c5a83208c55b2b39167bb8fb3ab</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual fei::SharedPtr&lt; const fei::Vector &gt;</type>
      <name>getRHS</name>
      <anchorfile>classfei_1_1LinearSystem.html</anchorfile>
      <anchor>a20cd79ec7e2f780f8d41c35836b6f70b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>setSolutionVector</name>
      <anchorfile>classfei_1_1LinearSystem.html</anchorfile>
      <anchor>a2a2e305a896cfd56811c8e02360d3081</anchor>
      <arglist>(fei::SharedPtr&lt; fei::Vector &gt; &amp;soln)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual fei::SharedPtr&lt; fei::Vector &gt;</type>
      <name>getSolutionVector</name>
      <anchorfile>classfei_1_1LinearSystem.html</anchorfile>
      <anchor>a92e5ed18ab89676225a45e1d3665e91f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual fei::SharedPtr&lt; const fei::Vector &gt;</type>
      <name>getSolutionVector</name>
      <anchorfile>classfei_1_1LinearSystem.html</anchorfile>
      <anchor>a10a7ed3a027284ccb7f1f542aea65a4f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>putAttribute</name>
      <anchorfile>classfei_1_1LinearSystem.html</anchorfile>
      <anchor>a9876df1cdc1da635c1d937a1c22fb272</anchor>
      <arglist>(const char *name, void *attribute)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>getAttribute</name>
      <anchorfile>classfei_1_1LinearSystem.html</anchorfile>
      <anchor>aa593e7d2abe4bb9d44e7580565a39f30</anchor>
      <arglist>(const char *name, void *&amp;attribute)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>loadEssentialBCs</name>
      <anchorfile>classfei_1_1LinearSystem.html</anchorfile>
      <anchor>a1e6b5ce9623056f053115fdc96b45df7</anchor>
      <arglist>(int numIDs, const int *IDs, int idType, int fieldID, int offsetIntoField, const double *prescribedValues)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>loadEssentialBCs</name>
      <anchorfile>classfei_1_1LinearSystem.html</anchorfile>
      <anchor>aee6e4a0ec5ebd5b216197e099bf1e3ab</anchor>
      <arglist>(int numIDs, const int *IDs, int idType, int fieldID, const int *offsetsIntoField, const double *prescribedValues)</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>loadLagrangeConstraint</name>
      <anchorfile>classfei_1_1LinearSystem.html</anchorfile>
      <anchor>a7bee04c9a938948340531ac56df95992</anchor>
      <arglist>(int constraintID, const double *weights, double rhsValue)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>loadPenaltyConstraint</name>
      <anchorfile>classfei_1_1LinearSystem.html</anchorfile>
      <anchor>a5e5a4ae829db303feee932cc199c32b2</anchor>
      <arglist>(int constraintID, const double *weights, double penaltyValue, double rhsValue)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>loadComplete</name>
      <anchorfile>classfei_1_1LinearSystem.html</anchorfile>
      <anchor>afdfc95fe08e9da423c5add501a326cf6</anchor>
      <arglist>(bool applyBCs=true, bool globalAssemble=true)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>setBCValuesOnVector</name>
      <anchorfile>classfei_1_1LinearSystem.html</anchorfile>
      <anchor>a9cc4bab89b05ae047a16fb8007bee2cd</anchor>
      <arglist>(fei::Vector *vector)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>eqnIsEssentialBC</name>
      <anchorfile>classfei_1_1LinearSystem.html</anchorfile>
      <anchor>a08f944d866970af4302622f623bd2007</anchor>
      <arglist>(int globalEqnIndex) const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>getEssentialBCs</name>
      <anchorfile>classfei_1_1LinearSystem.html</anchorfile>
      <anchor>aca73ea1169aac60b47f62e46e50ee912</anchor>
      <arglist>(std::vector&lt; int &gt; &amp;bcEqns, std::vector&lt; double &gt; &amp;bcVals) const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>getConstrainedEqns</name>
      <anchorfile>classfei_1_1LinearSystem.html</anchorfile>
      <anchor>a1fdd9fd7ed683d1459e19cdb5e395de1</anchor>
      <arglist>(std::vector&lt; int &gt; &amp;crEqns) const  =0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>snl_fei::LinearSystem_FEData</name>
    <filename>classsnl__fei_1_1LinearSystem__FEData.html</filename>
    <base>fei::LinearSystem</base>
    <member kind="function">
      <type></type>
      <name>LinearSystem_FEData</name>
      <anchorfile>classsnl__fei_1_1LinearSystem__FEData.html</anchorfile>
      <anchor>a7cc66c1b913c7354b623e8a5fec12878</anchor>
      <arglist>(fei::SharedPtr&lt; FiniteElementData &gt; &amp;fedata, fei::SharedPtr&lt; fei::MatrixGraph &gt; &amp;matrixGraph)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~LinearSystem_FEData</name>
      <anchorfile>classsnl__fei_1_1LinearSystem__FEData.html</anchorfile>
      <anchor>a63389024d2abc1e480b41893e3ce194e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>loadLagrangeConstraint</name>
      <anchorfile>classsnl__fei_1_1LinearSystem__FEData.html</anchorfile>
      <anchor>a8c73cd7200f5ab8da6ac9a5bd7829f4b</anchor>
      <arglist>(int constraintID, const double *weights, double rhsValue)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>loadPenaltyConstraint</name>
      <anchorfile>classsnl__fei_1_1LinearSystem__FEData.html</anchorfile>
      <anchor>a3d94a32ed98b74d6649a1ace75baccfe</anchor>
      <arglist>(int constraintID, const double *weights, double penaltyValue, double rhsValue)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>loadComplete</name>
      <anchorfile>classsnl__fei_1_1LinearSystem__FEData.html</anchorfile>
      <anchor>a2744b458fb1d74fbaa82ebaef74ee1b4</anchor>
      <arglist>(bool applyBCs=true, bool globalAssemble=true)</arglist>
    </member>
    <member kind="function">
      <type>fei::SharedPtr&lt; FiniteElementData &gt;</type>
      <name>getFiniteElementData</name>
      <anchorfile>classsnl__fei_1_1LinearSystem__FEData.html</anchorfile>
      <anchor>a08a545d806cfa42ddde09a1f89e4135c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>parameters</name>
      <anchorfile>classsnl__fei_1_1LinearSystem__FEData.html</anchorfile>
      <anchor>a37b7f32dadc5cdfd881ee78b97d2c8b0</anchor>
      <arglist>(int numParams, const char *const *paramStrings)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>parameters</name>
      <anchorfile>classsnl__fei_1_1LinearSystem__FEData.html</anchorfile>
      <anchor>a93ffe7eccd3c2f5fa84a9939329ebb05</anchor>
      <arglist>(const fei::ParameterSet &amp;params)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>setBCValuesOnVector</name>
      <anchorfile>classsnl__fei_1_1LinearSystem__FEData.html</anchorfile>
      <anchor>a5f233a26c3dc89f7abf55bcc619e8103</anchor>
      <arglist>(fei::Vector *vector)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setLookup</name>
      <anchorfile>classsnl__fei_1_1LinearSystem__FEData.html</anchorfile>
      <anchor>a51c3ad63d9429998c04cf0f70fd3a1eb</anchor>
      <arglist>(Lookup *lookup)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>eqnIsEssentialBC</name>
      <anchorfile>classsnl__fei_1_1LinearSystem__FEData.html</anchorfile>
      <anchor>ab3a509e9a82ce3b408a624e91c7bd3d3</anchor>
      <arglist>(int globalEqnIndex) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>getEssentialBCs</name>
      <anchorfile>classsnl__fei_1_1LinearSystem__FEData.html</anchorfile>
      <anchor>a55b4b74151b19657455f8ab56545ec3c</anchor>
      <arglist>(std::vector&lt; int &gt; &amp;bcEqns, std::vector&lt; double &gt; &amp;bcVals) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>getConstrainedEqns</name>
      <anchorfile>classsnl__fei_1_1LinearSystem__FEData.html</anchorfile>
      <anchor>a444b5463cc32c03b250643e27bb8c5aa</anchor>
      <arglist>(std::vector&lt; int &gt; &amp;crEqns) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>snl_fei::LinearSystem_General</name>
    <filename>classsnl__fei_1_1LinearSystem__General.html</filename>
    <base>fei::LinearSystem</base>
    <base protection="private">fei::Logger</base>
    <member kind="function">
      <type></type>
      <name>LinearSystem_General</name>
      <anchorfile>classsnl__fei_1_1LinearSystem__General.html</anchorfile>
      <anchor>a304603ba80ccb17d25a81b78d57e8d63</anchor>
      <arglist>(fei::SharedPtr&lt; fei::MatrixGraph &gt; &amp;matrixGraph)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~LinearSystem_General</name>
      <anchorfile>classsnl__fei_1_1LinearSystem__General.html</anchorfile>
      <anchor>aff467263015f143d303fbb61a7ba66e7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>loadEssentialBCs</name>
      <anchorfile>classsnl__fei_1_1LinearSystem__General.html</anchorfile>
      <anchor>abc106e3047c2fb57cbf4ab8247c31d61</anchor>
      <arglist>(int numIDs, const int *IDs, int idType, int fieldID, int offsetIntoField, const double *prescribedValues)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>loadEssentialBCs</name>
      <anchorfile>classsnl__fei_1_1LinearSystem__General.html</anchorfile>
      <anchor>a6c0291f3d8fb5d3d8ef31f755a648659</anchor>
      <arglist>(int numIDs, const int *IDs, int idType, int fieldID, const int *offsetIntoField, const double *prescribedValues)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>loadLagrangeConstraint</name>
      <anchorfile>classsnl__fei_1_1LinearSystem__General.html</anchorfile>
      <anchor>a3a642be06f1707173944afcb152c5037</anchor>
      <arglist>(int constraintID, const double *weights, double rhsValue)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>loadPenaltyConstraint</name>
      <anchorfile>classsnl__fei_1_1LinearSystem__General.html</anchorfile>
      <anchor>aceb22016b9921359b2e51c4b78ea1bff</anchor>
      <arglist>(int constraintID, const double *weights, double penaltyValue, double rhsValue)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>loadComplete</name>
      <anchorfile>classsnl__fei_1_1LinearSystem__General.html</anchorfile>
      <anchor>a292a7047664a32fa6ace349d89192fe2</anchor>
      <arglist>(bool applyBCs=true, bool globalAssemble=true)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>parameters</name>
      <anchorfile>classsnl__fei_1_1LinearSystem__General.html</anchorfile>
      <anchor>aaffcfaed46b129599a2dbeff413e86f3</anchor>
      <arglist>(int numParams, const char *const *paramStrings)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>parameters</name>
      <anchorfile>classsnl__fei_1_1LinearSystem__General.html</anchorfile>
      <anchor>a77dfbf7daa3992c329e5f1f64f2176f9</anchor>
      <arglist>(const fei::ParameterSet &amp;params)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>setBCValuesOnVector</name>
      <anchorfile>classsnl__fei_1_1LinearSystem__General.html</anchorfile>
      <anchor>a5ada9e39887f41ce4d9844f2cc23d2fd</anchor>
      <arglist>(fei::Vector *vector)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>eqnIsEssentialBC</name>
      <anchorfile>classsnl__fei_1_1LinearSystem__General.html</anchorfile>
      <anchor>aa92d1157ffc88f0361e0aeda097c29cf</anchor>
      <arglist>(int globalEqnIndex) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>getEssentialBCs</name>
      <anchorfile>classsnl__fei_1_1LinearSystem__General.html</anchorfile>
      <anchor>a05868c562cfc7047c86ef8102ae1456b</anchor>
      <arglist>(std::vector&lt; int &gt; &amp;bcEqns, std::vector&lt; double &gt; &amp;bcVals) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>getConstrainedEqns</name>
      <anchorfile>classsnl__fei_1_1LinearSystem__General.html</anchorfile>
      <anchor>a9ed611455638fce900f0e5106ccd6654</anchor>
      <arglist>(std::vector&lt; int &gt; &amp;crEqns) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>LinearSystemCore</name>
    <filename>classLinearSystemCore.html</filename>
    <member kind="function">
      <type></type>
      <name>LinearSystemCore</name>
      <anchorfile>classLinearSystemCore.html</anchorfile>
      <anchor>a9ef0b9ff1f0e5966df08bd14fdfb5ede</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~LinearSystemCore</name>
      <anchorfile>classLinearSystemCore.html</anchorfile>
      <anchor>accab3892d7350d9c7e05c9e2d3a727ef</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual LinearSystemCore *</type>
      <name>clone</name>
      <anchorfile>classLinearSystemCore.html</anchorfile>
      <anchor>a55fe55e790445e329ee131ada2d157ba</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>parameters</name>
      <anchorfile>classLinearSystemCore.html</anchorfile>
      <anchor>a2e4723fb0f5aa0455d7431dee00c11c7</anchor>
      <arglist>(int numParams, const char *const *params)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>setLookup</name>
      <anchorfile>classLinearSystemCore.html</anchorfile>
      <anchor>a1f8471c595c7302de4fef9e209768a9b</anchor>
      <arglist>(Lookup &amp;lookup)=0</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>getProperty</name>
      <anchorfile>classLinearSystemCore.html</anchorfile>
      <anchor>a19ece4307b1fad22f915cbb9ce920c00</anchor>
      <arglist>(const char *, double &amp;)</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>setGlobalOffsets</name>
      <anchorfile>classLinearSystemCore.html</anchorfile>
      <anchor>adf48a26acea8af60d8510c4e79e58558</anchor>
      <arglist>(int len, int *nodeOffsets, int *eqnOffsets, int *blkEqnOffsets)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>setConnectivities</name>
      <anchorfile>classLinearSystemCore.html</anchorfile>
      <anchor>a57d90556afa201ee0b841e4c0f26918c</anchor>
      <arglist>(GlobalID elemBlock, int numElements, int numNodesPerElem, const GlobalID *elemIDs, const int *const *connNodes)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>setStiffnessMatrices</name>
      <anchorfile>classLinearSystemCore.html</anchorfile>
      <anchor>aa3add667614d7c9b24fd2996a9181b1e</anchor>
      <arglist>(GlobalID elemBlock, int numElems, const GlobalID *elemIDs, const double *const *const *stiff, int numEqnsPerElem, const int *const *eqnIndices)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>setLoadVectors</name>
      <anchorfile>classLinearSystemCore.html</anchorfile>
      <anchor>a49032423fb8d37f1f81bc804b5b8ec13</anchor>
      <arglist>(GlobalID elemBlock, int numElems, const GlobalID *elemIDs, const double *const *load, int numEqnsPerElem, const int *const *eqnIndices)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>setMatrixStructure</name>
      <anchorfile>classLinearSystemCore.html</anchorfile>
      <anchor>af2bea8785cefd57e6b52b4b6c4fdca9f</anchor>
      <arglist>(int **ptColIndices, int *ptRrowLengths, int **blkColIndices, int *blkRowLengths, int *ptRowsPerBlkRow)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>setMultCREqns</name>
      <anchorfile>classLinearSystemCore.html</anchorfile>
      <anchor>ab596df5bdc212a240a68715a7451f2d7</anchor>
      <arglist>(int multCRSetID, int numCRs, int numNodesPerCR, int **nodeNumbers, int **eqnNumbers, int *fieldIDs, int *multiplierEqnNumbers)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>setPenCREqns</name>
      <anchorfile>classLinearSystemCore.html</anchorfile>
      <anchor>a867ca428d7259bc7b93b6aa638059b33</anchor>
      <arglist>(int penCRSetID, int numCRs, int numNodesPerCR, int **nodeNumbers, int **eqnNumbers, int *fieldIDs)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>sumIntoSystemMatrix</name>
      <anchorfile>classLinearSystemCore.html</anchorfile>
      <anchor>a17a1050b6c7249911efd11c953cc21d0</anchor>
      <arglist>(int numPtRows, const int *ptRows, int numPtCols, const int *ptCols, int numBlkRows, const int *blkRows, int numBlkCols, const int *blkCols, const double *const *values)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>sumIntoSystemMatrix</name>
      <anchorfile>classLinearSystemCore.html</anchorfile>
      <anchor>a76aac7c0e7af43c8f29ed749c69f0dfc</anchor>
      <arglist>(int numPtRows, const int *ptRows, int numPtCols, const int *ptCols, const double *const *values)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>putIntoSystemMatrix</name>
      <anchorfile>classLinearSystemCore.html</anchorfile>
      <anchor>a1b892eb26a69fd4dc238239561f7d63b</anchor>
      <arglist>(int numPtRows, const int *ptRows, int numPtCols, const int *ptCols, const double *const *values)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>getMatrixRowLength</name>
      <anchorfile>classLinearSystemCore.html</anchorfile>
      <anchor>a508ae024c24ad7ddac14098edc863942</anchor>
      <arglist>(int row, int &amp;length)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>getMatrixRow</name>
      <anchorfile>classLinearSystemCore.html</anchorfile>
      <anchor>a13a1b3fdd8ee94ad059d2a288bc99eaf</anchor>
      <arglist>(int row, double *coefs, int *indices, int len, int &amp;rowLength)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>sumIntoRHSVector</name>
      <anchorfile>classLinearSystemCore.html</anchorfile>
      <anchor>a2bc570a8ac743d8403284fc4ad36243b</anchor>
      <arglist>(int num, const double *values, const int *indices)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>putIntoRHSVector</name>
      <anchorfile>classLinearSystemCore.html</anchorfile>
      <anchor>a8d785bd49fdec79fa859cbd126f98cb4</anchor>
      <arglist>(int num, const double *values, const int *indices)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>getFromRHSVector</name>
      <anchorfile>classLinearSystemCore.html</anchorfile>
      <anchor>a1d6687366d37e46f8744b66594a35a52</anchor>
      <arglist>(int num, double *values, const int *indices)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>matrixLoadComplete</name>
      <anchorfile>classLinearSystemCore.html</anchorfile>
      <anchor>a8d0884d1d216af462a6bf1e494ba17be</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>putNodalFieldData</name>
      <anchorfile>classLinearSystemCore.html</anchorfile>
      <anchor>afe02febc84c656cb81ee3c73404f0ba3</anchor>
      <arglist>(int fieldID, int fieldSize, int *nodeNumbers, int numNodes, const double *data)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>resetMatrixAndVector</name>
      <anchorfile>classLinearSystemCore.html</anchorfile>
      <anchor>a4d4e3707f49019b4ad5c983caae79843</anchor>
      <arglist>(double s)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>resetMatrix</name>
      <anchorfile>classLinearSystemCore.html</anchorfile>
      <anchor>a7bc028c014735393e3e6d0360d1f26b1</anchor>
      <arglist>(double s)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>resetRHSVector</name>
      <anchorfile>classLinearSystemCore.html</anchorfile>
      <anchor>a9fc04454615772616c0d737818276aff</anchor>
      <arglist>(double s)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>enforceEssentialBC</name>
      <anchorfile>classLinearSystemCore.html</anchorfile>
      <anchor>a3996d48023c18bca8d116e38639408c1</anchor>
      <arglist>(int *globalEqn, double *alpha, double *gamma, int len)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>enforceRemoteEssBCs</name>
      <anchorfile>classLinearSystemCore.html</anchorfile>
      <anchor>aff96d089f89fc241a2634c154912a734</anchor>
      <arglist>(int numEqns, int *globalEqns, int **colIndices, int *colIndLen, double **coefs)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>getMatrixPtr</name>
      <anchorfile>classLinearSystemCore.html</anchorfile>
      <anchor>ab6a123f512f5d63f5ca85178a8649366</anchor>
      <arglist>(Data &amp;data)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>copyInMatrix</name>
      <anchorfile>classLinearSystemCore.html</anchorfile>
      <anchor>a51d2491d874e8fba9e6f55b2832f4fba</anchor>
      <arglist>(double scalar, const Data &amp;data)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>copyOutMatrix</name>
      <anchorfile>classLinearSystemCore.html</anchorfile>
      <anchor>a8c21aaa3377f1b449f7b5e89d6e5a77f</anchor>
      <arglist>(double scalar, Data &amp;data)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>sumInMatrix</name>
      <anchorfile>classLinearSystemCore.html</anchorfile>
      <anchor>a224cc2a202b667e1f2795bfa93b157c9</anchor>
      <arglist>(double scalar, const Data &amp;data)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>getRHSVectorPtr</name>
      <anchorfile>classLinearSystemCore.html</anchorfile>
      <anchor>a7b9fba0b1fb9d1e9e0235477ed42a447</anchor>
      <arglist>(Data &amp;data)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>copyInRHSVector</name>
      <anchorfile>classLinearSystemCore.html</anchorfile>
      <anchor>a124a84a9b66d91f2c68ef3ae7c9f6d54</anchor>
      <arglist>(double scalar, const Data &amp;data)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>copyOutRHSVector</name>
      <anchorfile>classLinearSystemCore.html</anchorfile>
      <anchor>a612af8541297e0a692ee7c0c8e0e797f</anchor>
      <arglist>(double scalar, Data &amp;data)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>sumInRHSVector</name>
      <anchorfile>classLinearSystemCore.html</anchorfile>
      <anchor>adf1dec4fa2dcc233df18d58c75f84cc4</anchor>
      <arglist>(double scalar, const Data &amp;data)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>destroyMatrixData</name>
      <anchorfile>classLinearSystemCore.html</anchorfile>
      <anchor>a7ddaabe1b1913a3af9c5576b0135a022</anchor>
      <arglist>(Data &amp;data)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>destroyVectorData</name>
      <anchorfile>classLinearSystemCore.html</anchorfile>
      <anchor>a2ea60fe33c63c7371b310335855a7d4c</anchor>
      <arglist>(Data &amp;data)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>setNumRHSVectors</name>
      <anchorfile>classLinearSystemCore.html</anchorfile>
      <anchor>a16b0f112937850195ed14b8b68d8d328</anchor>
      <arglist>(int numRHSs, const int *rhsIDs)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>setRHSID</name>
      <anchorfile>classLinearSystemCore.html</anchorfile>
      <anchor>abf643e5d255cd2c38315ec66b8f4e32a</anchor>
      <arglist>(int rhsID)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>putInitialGuess</name>
      <anchorfile>classLinearSystemCore.html</anchorfile>
      <anchor>af1a4288cbff62c6929cbf3c955a77a9f</anchor>
      <arglist>(const int *eqnNumbers, const double *values, int len)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>getSolution</name>
      <anchorfile>classLinearSystemCore.html</anchorfile>
      <anchor>a8b80a874cacdbfedb297b729139e6554</anchor>
      <arglist>(double *answers, int len)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>getSolnEntry</name>
      <anchorfile>classLinearSystemCore.html</anchorfile>
      <anchor>ae5ed92e086e130c77636db717fe52205</anchor>
      <arglist>(int eqnNumber, double &amp;answer)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>formResidual</name>
      <anchorfile>classLinearSystemCore.html</anchorfile>
      <anchor>a2a93a2ecabb4780e58318e4a7b0b45d3</anchor>
      <arglist>(double *values, int len)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>launchSolver</name>
      <anchorfile>classLinearSystemCore.html</anchorfile>
      <anchor>aacab77eafa84515071b4f429f3b03ea0</anchor>
      <arglist>(int &amp;solveStatus, int &amp;iterations)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>writeSystem</name>
      <anchorfile>classLinearSystemCore.html</anchorfile>
      <anchor>a551bbc75e810ffdd3778b580ea0c1216</anchor>
      <arglist>(const char *name)=0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>LinSysCore_flexible</name>
    <filename>classLinSysCore__flexible.html</filename>
    <base virtualness="virtual">LinearSystemCore</base>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>resetConstraints</name>
      <anchorfile>classLinSysCore__flexible.html</anchorfile>
      <anchor>abbd546355f96d63c40d7bcb62def6092</anchor>
      <arglist>(double s)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>setMultCRComplete</name>
      <anchorfile>classLinSysCore__flexible.html</anchorfile>
      <anchor>a88b2d5bb54f9ae958959e8413dc0d7e5</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>constraintsLoadComplete</name>
      <anchorfile>classLinSysCore__flexible.html</anchorfile>
      <anchor>a4be9d61c211a04ef456ff7406e29aef5</anchor>
      <arglist>()=0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>LinSysCoreFilter</name>
    <filename>classLinSysCoreFilter.html</filename>
    <base>Filter</base>
  </compound>
  <compound kind="class">
    <name>fei::LogFile</name>
    <filename>classfei_1_1LogFile.html</filename>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~LogFile</name>
      <anchorfile>classfei_1_1LogFile.html</anchorfile>
      <anchor>a266ec4b8b64599f22f82e9d51760af2e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>openOutputStream</name>
      <anchorfile>classfei_1_1LogFile.html</anchorfile>
      <anchor>ab07527f7f02d9e4d26f5581ec34e9f33</anchor>
      <arglist>(const char *path=NULL, int nprocs=1, int localproc=0)</arglist>
    </member>
    <member kind="function">
      <type>FEI_OSTREAM *</type>
      <name>getOutputStream</name>
      <anchorfile>classfei_1_1LogFile.html</anchorfile>
      <anchor>a3c52bf613403eadc341527d8c260c19c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>closeOutputStream</name>
      <anchorfile>classfei_1_1LogFile.html</anchorfile>
      <anchor>a0c0dba1d102ddca409199a180252439a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static LogFile &amp;</type>
      <name>getLogFile</name>
      <anchorfile>classfei_1_1LogFile.html</anchorfile>
      <anchor>af913d424f29f6fb4f4cfdb9170a088fe</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>fei::Logger</name>
    <filename>classfei_1_1Logger.html</filename>
    <member kind="function">
      <type></type>
      <name>Logger</name>
      <anchorfile>classfei_1_1Logger.html</anchorfile>
      <anchor>aa2cc7e24b18c6b3aff7106cbbc3a3b9d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~Logger</name>
      <anchorfile>classfei_1_1Logger.html</anchorfile>
      <anchor>af76bf36bc419fc480b01ff2c0fbf4ea3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setOutputLevel</name>
      <anchorfile>classfei_1_1Logger.html</anchorfile>
      <anchor>af98da33275349f5536457df4d88e9686</anchor>
      <arglist>(OutputLevel olevel)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>OutputLevel</type>
      <name>output_level_</name>
      <anchorfile>classfei_1_1Logger.html</anchorfile>
      <anchor>ae0ea8f8f9a2dd1fcb4c06ad8d9201401</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>FEI_OSTREAM *</type>
      <name>output_stream_</name>
      <anchorfile>classfei_1_1Logger.html</anchorfile>
      <anchor>a39801b1625900c2944d1f1650b20e87b</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>fei::LogManager</name>
    <filename>classfei_1_1LogManager.html</filename>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~LogManager</name>
      <anchorfile>classfei_1_1LogManager.html</anchorfile>
      <anchor>ac057928f904cf6b6018582417fd6824b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>OutputLevel</type>
      <name>getOutputLevel</name>
      <anchorfile>classfei_1_1LogManager.html</anchorfile>
      <anchor>affc0ffed1a4df5904421916254f04314</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setOutputLevel</name>
      <anchorfile>classfei_1_1LogManager.html</anchorfile>
      <anchor>a4beb042571c43fcbac3e1e32709d110d</anchor>
      <arglist>(OutputLevel olevel)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setOutputLevel</name>
      <anchorfile>classfei_1_1LogManager.html</anchorfile>
      <anchor>acf0ef5e8970f4cd20a296f990f323e57</anchor>
      <arglist>(const char *olevel)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setOutputPath</name>
      <anchorfile>classfei_1_1LogManager.html</anchorfile>
      <anchor>ad8aefc6426335aa64cf08b7a95a56a75</anchor>
      <arglist>(const std::string &amp;opath)</arglist>
    </member>
    <member kind="function">
      <type>const std::string &amp;</type>
      <name>getOutputPath</name>
      <anchorfile>classfei_1_1LogManager.html</anchorfile>
      <anchor>a8dc65ef1ea4174ead0f26ceba7ad9c48</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setNumProcs</name>
      <anchorfile>classfei_1_1LogManager.html</anchorfile>
      <anchor>ae03409dab167f4717e36769a7852df3a</anchor>
      <arglist>(int nprocs, int localproc)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static LogManager &amp;</type>
      <name>getLogManager</name>
      <anchorfile>classfei_1_1LogManager.html</anchorfile>
      <anchor>a6a6ad2603cd29a38b6471bec83df59d3</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Lookup</name>
    <filename>classLookup.html</filename>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~Lookup</name>
      <anchorfile>classLookup.html</anchorfile>
      <anchor>a1ceeae3b4f9680502a7f987f6d57632d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>getNumFields</name>
      <anchorfile>classLookup.html</anchorfile>
      <anchor>aaa42a7c2b95938d3404caf0021e05f2a</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>getFieldSize</name>
      <anchorfile>classLookup.html</anchorfile>
      <anchor>a68cadfa0fbd7898df13f0b4d637e04f9</anchor>
      <arglist>(int fieldID)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual const int *</type>
      <name>getFieldIDsPtr</name>
      <anchorfile>classLookup.html</anchorfile>
      <anchor>af2893d4c6d9720f8afce8ed2494a6d3a</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual const int *</type>
      <name>getFieldSizesPtr</name>
      <anchorfile>classLookup.html</anchorfile>
      <anchor>a1d662d8516ea87b176b7db13b3b7713c</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>getNumElemBlocks</name>
      <anchorfile>classLookup.html</anchorfile>
      <anchor>addc137ad9027b88b45c2599bc5d5cbbd</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual const GlobalID *</type>
      <name>getElemBlockIDs</name>
      <anchorfile>classLookup.html</anchorfile>
      <anchor>a863e67be995d4c46062f4ea6fd1251a8</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>getElemBlockInfo</name>
      <anchorfile>classLookup.html</anchorfile>
      <anchor>a8ea30d911f735a846366910d8c21d207</anchor>
      <arglist>(GlobalID blockID, int &amp;interleaveStrategy, int &amp;lumpingStrategy, int &amp;numElemDOF, int &amp;numElements, int &amp;numNodesPerElem, int &amp;numEqnsPerElem)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual const int *</type>
      <name>getNumFieldsPerNode</name>
      <anchorfile>classLookup.html</anchorfile>
      <anchor>a5220498d0d1fb4e275bb4785297fccc8</anchor>
      <arglist>(GlobalID blockID)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual const int *const *</type>
      <name>getFieldIDsTable</name>
      <anchorfile>classLookup.html</anchorfile>
      <anchor>af864c6273e7b5ed4933a5c2f5b9398da</anchor>
      <arglist>(GlobalID blockID)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>getEqnNumber</name>
      <anchorfile>classLookup.html</anchorfile>
      <anchor>a10cdd7f4ac482c9fef05a9d0eb653371</anchor>
      <arglist>(int nodeNumber, int fieldID)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>getAssociatedNodeNumber</name>
      <anchorfile>classLookup.html</anchorfile>
      <anchor>a1585c5599db7897590db1237ab01c1b4</anchor>
      <arglist>(int eqnNumber)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>getAssociatedFieldID</name>
      <anchorfile>classLookup.html</anchorfile>
      <anchor>af7112c327052118238b393a4dcff9a88</anchor>
      <arglist>(int eqnNumber)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>isInLocalElement</name>
      <anchorfile>classLookup.html</anchorfile>
      <anchor>a93f4593fd53bf0350a7f6ad0a60757ac</anchor>
      <arglist>(int nodeNumber)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>getNumSubdomains</name>
      <anchorfile>classLookup.html</anchorfile>
      <anchor>aeffc67a5eb920a7653261f69701077a8</anchor>
      <arglist>(int nodeNumber)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int *</type>
      <name>getSubdomainList</name>
      <anchorfile>classLookup.html</anchorfile>
      <anchor>acd5322d79a9129bda409c669e0cfd767</anchor>
      <arglist>(int nodeNumber)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>getNumSharedNodes</name>
      <anchorfile>classLookup.html</anchorfile>
      <anchor>ad97d6cb92a4e411cb90a941fbde239c0</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual const int *</type>
      <name>getSharedNodeNumbers</name>
      <anchorfile>classLookup.html</anchorfile>
      <anchor>af32dadbb8633d1a7240127187025d465</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual const int *</type>
      <name>getSharedNodeProcs</name>
      <anchorfile>classLookup.html</anchorfile>
      <anchor>a3ad26c5bf13daa39274c8309f2386a35</anchor>
      <arglist>(int nodeNumber)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>getNumSharingProcs</name>
      <anchorfile>classLookup.html</anchorfile>
      <anchor>a0633f69b7a9db442811c27de4cd7b4da</anchor>
      <arglist>(int nodeNumber)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>isExactlyBlkEqn</name>
      <anchorfile>classLookup.html</anchorfile>
      <anchor>a5e60b29c868518bc6c7853ac7cf1f1e6</anchor>
      <arglist>(int ptEqn)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>ptEqnToBlkEqn</name>
      <anchorfile>classLookup.html</anchorfile>
      <anchor>a485173d7d3b06f37c2a5bc7d36c4d9bd</anchor>
      <arglist>(int ptEqn)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>getOffsetIntoBlkEqn</name>
      <anchorfile>classLookup.html</anchorfile>
      <anchor>a7673c448e46c3370bb31f3c0ec7c68d1</anchor>
      <arglist>(int blkEqn, int ptEqn)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>getBlkEqnSize</name>
      <anchorfile>classLookup.html</anchorfile>
      <anchor>a360042b747a9c1d9ef09ff13c2a0055a</anchor>
      <arglist>(int blkEqn)=0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>fei::Lookup_Impl</name>
    <filename>classfei_1_1Lookup__Impl.html</filename>
    <base virtualness="virtual">Lookup</base>
    <member kind="function">
      <type></type>
      <name>Lookup_Impl</name>
      <anchorfile>classfei_1_1Lookup__Impl.html</anchorfile>
      <anchor>a750d09b64db05260157ca20bbc4509cb</anchor>
      <arglist>(fei::SharedPtr&lt; fei::MatrixGraph &gt; matGraph, int nodeIDType)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~Lookup_Impl</name>
      <anchorfile>classfei_1_1Lookup__Impl.html</anchorfile>
      <anchor>a1e6930098f2467a06fc36e09656bf668</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getNumFields</name>
      <anchorfile>classfei_1_1Lookup__Impl.html</anchorfile>
      <anchor>a1eef9d5fca49a07b8ecb1b153d7a43e1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getFieldSize</name>
      <anchorfile>classfei_1_1Lookup__Impl.html</anchorfile>
      <anchor>a4016603044b095dde7a684b3b6039d1f</anchor>
      <arglist>(int fieldID)</arglist>
    </member>
    <member kind="function">
      <type>const int *</type>
      <name>getFieldIDsPtr</name>
      <anchorfile>classfei_1_1Lookup__Impl.html</anchorfile>
      <anchor>ad2bcca8ea17e7de84fc90e118d8609b5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const int *</type>
      <name>getFieldSizesPtr</name>
      <anchorfile>classfei_1_1Lookup__Impl.html</anchorfile>
      <anchor>abc5a0be9253236fa97d334243cbd903a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getNumElemBlocks</name>
      <anchorfile>classfei_1_1Lookup__Impl.html</anchorfile>
      <anchor>ad9cc89c1340fc6049830463fe3c36092</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const GlobalID *</type>
      <name>getElemBlockIDs</name>
      <anchorfile>classfei_1_1Lookup__Impl.html</anchorfile>
      <anchor>a798867a1a6a0f8cad59e11876e682940</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>getElemBlockInfo</name>
      <anchorfile>classfei_1_1Lookup__Impl.html</anchorfile>
      <anchor>ad1f671d72beed57bc2e59e85da0ad356</anchor>
      <arglist>(GlobalID blockID, int &amp;interleaveStrategy, int &amp;lumpingStrategy, int &amp;numElemDOF, int &amp;numElements, int &amp;numNodesPerElem, int &amp;numEqnsPerElem)</arglist>
    </member>
    <member kind="function">
      <type>const int *</type>
      <name>getNumFieldsPerNode</name>
      <anchorfile>classfei_1_1Lookup__Impl.html</anchorfile>
      <anchor>a2535edd8f35494468ff58a9195d844fb</anchor>
      <arglist>(GlobalID blockID)</arglist>
    </member>
    <member kind="function">
      <type>const int *const *</type>
      <name>getFieldIDsTable</name>
      <anchorfile>classfei_1_1Lookup__Impl.html</anchorfile>
      <anchor>a6c0fe6978ed5fad9a411f1cc81284c63</anchor>
      <arglist>(GlobalID blockID)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getEqnNumber</name>
      <anchorfile>classfei_1_1Lookup__Impl.html</anchorfile>
      <anchor>a2bd514750a9100726f4ba12ec0a5f298</anchor>
      <arglist>(int nodeNumber, int fieldID)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getAssociatedNodeNumber</name>
      <anchorfile>classfei_1_1Lookup__Impl.html</anchorfile>
      <anchor>a6dcce520894ce028c8b46f802583b551</anchor>
      <arglist>(int eqnNumber)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getAssociatedFieldID</name>
      <anchorfile>classfei_1_1Lookup__Impl.html</anchorfile>
      <anchor>a1dd646189a7979fa3db9b87ebbba1e23</anchor>
      <arglist>(int eqnNumber)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isInLocalElement</name>
      <anchorfile>classfei_1_1Lookup__Impl.html</anchorfile>
      <anchor>a1783b4787bd8f34a6d334cc94a93159a</anchor>
      <arglist>(int nodeNumber)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getNumSubdomains</name>
      <anchorfile>classfei_1_1Lookup__Impl.html</anchorfile>
      <anchor>a89c9e5afa3e495808e025341591d733f</anchor>
      <arglist>(int nodeNumber)</arglist>
    </member>
    <member kind="function">
      <type>int *</type>
      <name>getSubdomainList</name>
      <anchorfile>classfei_1_1Lookup__Impl.html</anchorfile>
      <anchor>adaf821013cb87fabb62a077735ec8223</anchor>
      <arglist>(int nodeNumber)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getNumSharedNodes</name>
      <anchorfile>classfei_1_1Lookup__Impl.html</anchorfile>
      <anchor>a054fd9bc3cacdf075ef4ff94d52c0e7c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const int *</type>
      <name>getSharedNodeNumbers</name>
      <anchorfile>classfei_1_1Lookup__Impl.html</anchorfile>
      <anchor>a043d57eaf7188f0fda1a986312b65406</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const int *</type>
      <name>getSharedNodeProcs</name>
      <anchorfile>classfei_1_1Lookup__Impl.html</anchorfile>
      <anchor>ac2435fe445b4c4b8cf0b1870c7a4eb7e</anchor>
      <arglist>(int nodeNumber)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getNumSharingProcs</name>
      <anchorfile>classfei_1_1Lookup__Impl.html</anchorfile>
      <anchor>a327beb347515ce3b4ddeb2382d27c41a</anchor>
      <arglist>(int nodeNumber)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isExactlyBlkEqn</name>
      <anchorfile>classfei_1_1Lookup__Impl.html</anchorfile>
      <anchor>ad1296fc52a8179e1949825352ca44e27</anchor>
      <arglist>(int ptEqn)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ptEqnToBlkEqn</name>
      <anchorfile>classfei_1_1Lookup__Impl.html</anchorfile>
      <anchor>a0324558fd9b041c5195661bf32c4654e</anchor>
      <arglist>(int ptEqn)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getOffsetIntoBlkEqn</name>
      <anchorfile>classfei_1_1Lookup__Impl.html</anchorfile>
      <anchor>a01aea76bc032379c200d02900bd867e4</anchor>
      <arglist>(int blkEqn, int ptEqn)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getBlkEqnSize</name>
      <anchorfile>classfei_1_1Lookup__Impl.html</anchorfile>
      <anchor>a2793fd35255ef5722f90809a9e07f2dc</anchor>
      <arglist>(int blkEqn)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>snl_fei::MapContig</name>
    <filename>classsnl__fei_1_1MapContig.html</filename>
    <templarg>VAL_TYPE</templarg>
    <class kind="class">snl_fei::MapContig::iterator</class>
    <member kind="typedef">
      <type>int</type>
      <name>key_type</name>
      <anchorfile>classsnl__fei_1_1MapContig.html</anchorfile>
      <anchor>a4f69913f0214cd1f99e01bc7a5fa222b</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>VAL_TYPE</type>
      <name>mapped_type</name>
      <anchorfile>classsnl__fei_1_1MapContig.html</anchorfile>
      <anchor>afd185323f98591263d526de8318bfcae</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::pair&lt; int, VAL_TYPE &gt;</type>
      <name>value_type</name>
      <anchorfile>classsnl__fei_1_1MapContig.html</anchorfile>
      <anchor>a92697585cfe2b18b49fb0b28f1421e3e</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>MapContig</name>
      <anchorfile>classsnl__fei_1_1MapContig.html</anchorfile>
      <anchor>a19349735ea3704393e0565cc40ef2f9d</anchor>
      <arglist>(int firstKey, int lastKey)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>MapContig</name>
      <anchorfile>classsnl__fei_1_1MapContig.html</anchorfile>
      <anchor>af8220082fa8f235bde2b68e913081e36</anchor>
      <arglist>(const MapContig&lt; VAL_TYPE &gt; &amp;src)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~MapContig</name>
      <anchorfile>classsnl__fei_1_1MapContig.html</anchorfile>
      <anchor>a1ceffffea3dfa7b7326efe9f5500d326</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>iterator</type>
      <name>begin</name>
      <anchorfile>classsnl__fei_1_1MapContig.html</anchorfile>
      <anchor>a404c0278a5b0d2c092838c6c682c5b71</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>iterator &amp;</type>
      <name>end</name>
      <anchorfile>classsnl__fei_1_1MapContig.html</anchorfile>
      <anchor>acc0e7d96a5e6545cb5ed1c230660ff8b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>std::pair&lt; iterator, bool &gt;</type>
      <name>insert</name>
      <anchorfile>classsnl__fei_1_1MapContig.html</anchorfile>
      <anchor>acbca8d095cfe36e5b92e97087366e785</anchor>
      <arglist>(value_type val)</arglist>
    </member>
    <member kind="function">
      <type>iterator</type>
      <name>insert</name>
      <anchorfile>classsnl__fei_1_1MapContig.html</anchorfile>
      <anchor>aeca27e997223ee92171bfec585ea24d4</anchor>
      <arglist>(iterator &amp;pos, value_type val)</arglist>
    </member>
    <member kind="function">
      <type>iterator</type>
      <name>find</name>
      <anchorfile>classsnl__fei_1_1MapContig.html</anchorfile>
      <anchor>a8b60436f0e943310c5cf95784f48403b</anchor>
      <arglist>(int key)</arglist>
    </member>
    <member kind="function">
      <type>iterator</type>
      <name>lower_bound</name>
      <anchorfile>classsnl__fei_1_1MapContig.html</anchorfile>
      <anchor>a8e29217ca97e31810bcedd358e516f32</anchor>
      <arglist>(int key)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>size</name>
      <anchorfile>classsnl__fei_1_1MapContig.html</anchorfile>
      <anchor>a31296f236f49f5888d4ca737266652a3</anchor>
      <arglist>() const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>MapContig&lt; fei::ctg_set&lt; int &gt; * &gt;</name>
    <filename>classsnl__fei_1_1MapContig.html</filename>
    <member kind="typedef">
      <type>int</type>
      <name>key_type</name>
      <anchorfile>classsnl__fei_1_1MapContig.html</anchorfile>
      <anchor>a4f69913f0214cd1f99e01bc7a5fa222b</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>fei::ctg_set&lt; int &gt; *</type>
      <name>mapped_type</name>
      <anchorfile>classsnl__fei_1_1MapContig.html</anchorfile>
      <anchor>afd185323f98591263d526de8318bfcae</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::pair&lt; int, fei::ctg_set&lt; int &gt; * &gt;</type>
      <name>value_type</name>
      <anchorfile>classsnl__fei_1_1MapContig.html</anchorfile>
      <anchor>a92697585cfe2b18b49fb0b28f1421e3e</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>MapContig</name>
      <anchorfile>classsnl__fei_1_1MapContig.html</anchorfile>
      <anchor>a19349735ea3704393e0565cc40ef2f9d</anchor>
      <arglist>(int firstKey, int lastKey)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>MapContig</name>
      <anchorfile>classsnl__fei_1_1MapContig.html</anchorfile>
      <anchor>af8220082fa8f235bde2b68e913081e36</anchor>
      <arglist>(const MapContig&lt; fei::ctg_set&lt; int &gt; * &gt; &amp;src)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~MapContig</name>
      <anchorfile>classsnl__fei_1_1MapContig.html</anchorfile>
      <anchor>a1ceffffea3dfa7b7326efe9f5500d326</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>iterator</type>
      <name>begin</name>
      <anchorfile>classsnl__fei_1_1MapContig.html</anchorfile>
      <anchor>a404c0278a5b0d2c092838c6c682c5b71</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>iterator &amp;</type>
      <name>end</name>
      <anchorfile>classsnl__fei_1_1MapContig.html</anchorfile>
      <anchor>acc0e7d96a5e6545cb5ed1c230660ff8b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>std::pair&lt; iterator, bool &gt;</type>
      <name>insert</name>
      <anchorfile>classsnl__fei_1_1MapContig.html</anchorfile>
      <anchor>acbca8d095cfe36e5b92e97087366e785</anchor>
      <arglist>(value_type val)</arglist>
    </member>
    <member kind="function">
      <type>iterator</type>
      <name>insert</name>
      <anchorfile>classsnl__fei_1_1MapContig.html</anchorfile>
      <anchor>aeca27e997223ee92171bfec585ea24d4</anchor>
      <arglist>(iterator &amp;pos, value_type val)</arglist>
    </member>
    <member kind="function">
      <type>iterator</type>
      <name>find</name>
      <anchorfile>classsnl__fei_1_1MapContig.html</anchorfile>
      <anchor>a8b60436f0e943310c5cf95784f48403b</anchor>
      <arglist>(int key)</arglist>
    </member>
    <member kind="function">
      <type>iterator</type>
      <name>lower_bound</name>
      <anchorfile>classsnl__fei_1_1MapContig.html</anchorfile>
      <anchor>a8e29217ca97e31810bcedd358e516f32</anchor>
      <arglist>(int key)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>size</name>
      <anchorfile>classsnl__fei_1_1MapContig.html</anchorfile>
      <anchor>a31296f236f49f5888d4ca737266652a3</anchor>
      <arglist>() const</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>snl_fei::MapTraits</name>
    <filename>structsnl__fei_1_1MapTraits.html</filename>
    <templarg></templarg>
    <member kind="function" static="yes">
      <type>static MAP_TYPE::iterator</type>
      <name>lower_bound</name>
      <anchorfile>structsnl__fei_1_1MapTraits.html</anchorfile>
      <anchor>af8a00e69337e6b491b928bcbb6904618</anchor>
      <arglist>(MAP_TYPE &amp;map_obj, typename MAP_TYPE::key_type item)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>insert</name>
      <anchorfile>structsnl__fei_1_1MapTraits.html</anchorfile>
      <anchor>a0ad35d71508c021a3becf267ad1491ab</anchor>
      <arglist>(MAP_TYPE &amp;map_obj, typename MAP_TYPE::iterator &amp;pos, typename MAP_TYPE::value_type &amp;val)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>fei::Matrix</name>
    <filename>classfei_1_1Matrix.html</filename>
    <class kind="class">fei::Matrix::Factory</class>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~Matrix</name>
      <anchorfile>classfei_1_1Matrix.html</anchorfile>
      <anchor>a796d5beef4f6195110b03bfb3bb28f87</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual const char *</type>
      <name>typeName</name>
      <anchorfile>classfei_1_1Matrix.html</anchorfile>
      <anchor>a3f8d4159470a80746421c1e9e7fde9b9</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>parameters</name>
      <anchorfile>classfei_1_1Matrix.html</anchorfile>
      <anchor>a8fd192a481c9119e57f39b9e98e7c4d0</anchor>
      <arglist>(const fei::ParameterSet &amp;paramset)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual fei::SharedPtr&lt; fei::MatrixGraph &gt;</type>
      <name>getMatrixGraph</name>
      <anchorfile>classfei_1_1Matrix.html</anchorfile>
      <anchor>aa3f31b446b898dd787870976418fd12c</anchor>
      <arglist>() const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>setMatrixGraph</name>
      <anchorfile>classfei_1_1Matrix.html</anchorfile>
      <anchor>aa6ad6cc2e179a725087cf90c20ff90d2</anchor>
      <arglist>(fei::SharedPtr&lt; fei::MatrixGraph &gt; matrixGraph)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>getGlobalNumRows</name>
      <anchorfile>classfei_1_1Matrix.html</anchorfile>
      <anchor>a891e980107b400a8d8cd83d39971ffe9</anchor>
      <arglist>() const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>getLocalNumRows</name>
      <anchorfile>classfei_1_1Matrix.html</anchorfile>
      <anchor>aefa5e8712bd2dc0cec0c70a1c057fe7a</anchor>
      <arglist>() const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>getRowLength</name>
      <anchorfile>classfei_1_1Matrix.html</anchorfile>
      <anchor>a8236017ef04aeee3089b424388cf1737</anchor>
      <arglist>(int row, int &amp;length) const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>putScalar</name>
      <anchorfile>classfei_1_1Matrix.html</anchorfile>
      <anchor>aa7024ea769c8c39052c8c34d08baad91</anchor>
      <arglist>(double scalar)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>copyOutRow</name>
      <anchorfile>classfei_1_1Matrix.html</anchorfile>
      <anchor>acf2e21adbbf7c3ecb7bf90464ff84b70</anchor>
      <arglist>(int row, int len, double *coefs, int *indices) const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>sumIn</name>
      <anchorfile>classfei_1_1Matrix.html</anchorfile>
      <anchor>a95ed3bb4b585bcb835262630aa5a16fe</anchor>
      <arglist>(int numRows, const int *rows, int numCols, const int *cols, const double *const *values, int format=0)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>copyIn</name>
      <anchorfile>classfei_1_1Matrix.html</anchorfile>
      <anchor>a348c2d305dcf6f10b1d435e46a4a5bfc</anchor>
      <arglist>(int numRows, const int *rows, int numCols, const int *cols, const double *const *values, int format=0)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>sumInFieldData</name>
      <anchorfile>classfei_1_1Matrix.html</anchorfile>
      <anchor>acf3367f183eecfcc8326815ee481c3ea</anchor>
      <arglist>(int fieldID, int idType, int rowID, int colID, const double *const *data, int format=0)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>sumInFieldData</name>
      <anchorfile>classfei_1_1Matrix.html</anchorfile>
      <anchor>a8eaeb049cbf56e1fc151b57177c7bbfd</anchor>
      <arglist>(int fieldID, int idType, int rowID, int colID, const double *data, int format=0)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>sumIn</name>
      <anchorfile>classfei_1_1Matrix.html</anchorfile>
      <anchor>ad88fa61d00f990afea7b8f48c728da6f</anchor>
      <arglist>(int blockID, int connectivityID, const double *const *values, int format=0)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>globalAssemble</name>
      <anchorfile>classfei_1_1Matrix.html</anchorfile>
      <anchor>abea36a52690fb2a56d79d530362017f7</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>multiply</name>
      <anchorfile>classfei_1_1Matrix.html</anchorfile>
      <anchor>ad34466a5c95be15ee9ed2aba21647d6f</anchor>
      <arglist>(fei::Vector *x, fei::Vector *y)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>setCommSizes</name>
      <anchorfile>classfei_1_1Matrix.html</anchorfile>
      <anchor>a4920bae1670e4e9eeb14851b2a837538</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>gatherFromOverlap</name>
      <anchorfile>classfei_1_1Matrix.html</anchorfile>
      <anchor>a66968d413efe68b68d080780c99b38d5</anchor>
      <arglist>(bool accumulate=true)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>writeToFile</name>
      <anchorfile>classfei_1_1Matrix.html</anchorfile>
      <anchor>a629e42e44d772b02ea5cc02770eeb49f</anchor>
      <arglist>(const char *filename, bool matrixMarketFormat=true)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>writeToStream</name>
      <anchorfile>classfei_1_1Matrix.html</anchorfile>
      <anchor>a1eba1cfd44158d98b02b7ca0fc3a6817</anchor>
      <arglist>(FEI_OSTREAM &amp;ostrm, bool matrixMarketFormat=true)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>usingBlockEntryStorage</name>
      <anchorfile>classfei_1_1Matrix.html</anchorfile>
      <anchor>a4e2f7d7569f4ebfcbb218115a5a832a6</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>markState</name>
      <anchorfile>classfei_1_1Matrix.html</anchorfile>
      <anchor>ae80e74f7c0d023042fc8718aa97d7613</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>changedSinceMark</name>
      <anchorfile>classfei_1_1Matrix.html</anchorfile>
      <anchor>a8f071d1519f373ee3534fdb972f16e37</anchor>
      <arglist>()=0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>fei::Matrix_Impl</name>
    <filename>classfei_1_1Matrix__Impl.html</filename>
    <templarg>T</templarg>
    <base>fei::Matrix</base>
    <member kind="function">
      <type></type>
      <name>Matrix_Impl</name>
      <anchorfile>classfei_1_1Matrix__Impl.html</anchorfile>
      <anchor>a3d1e79cd41efa2eb250eb737510074fb</anchor>
      <arglist>(fei::SharedPtr&lt; T &gt; matrix, fei::SharedPtr&lt; fei::MatrixGraph &gt; matrixGraph, int numLocalEqns, bool zeroSharedRows=true)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~Matrix_Impl</name>
      <anchorfile>classfei_1_1Matrix__Impl.html</anchorfile>
      <anchor>a2e219b71e1c78ef530ad37a262ba0538</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const char *</type>
      <name>typeName</name>
      <anchorfile>classfei_1_1Matrix__Impl.html</anchorfile>
      <anchor>aabe580fda669d40e8e0658e112ce3429</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>parameters</name>
      <anchorfile>classfei_1_1Matrix__Impl.html</anchorfile>
      <anchor>a8f848bf44829c16ff2d22cc573a47551</anchor>
      <arglist>(const fei::ParameterSet &amp;paramset)</arglist>
    </member>
    <member kind="function">
      <type>fei::SharedPtr&lt; T &gt;</type>
      <name>getMatrix</name>
      <anchorfile>classfei_1_1Matrix__Impl.html</anchorfile>
      <anchor>a1986db91998e64c16298c06e6540b6df</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>fei::SharedPtr&lt; fei::MatrixGraph &gt;</type>
      <name>getMatrixGraph</name>
      <anchorfile>classfei_1_1Matrix__Impl.html</anchorfile>
      <anchor>ae9cd11365477305c4e8bdb4e14230684</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setMatrixGraph</name>
      <anchorfile>classfei_1_1Matrix__Impl.html</anchorfile>
      <anchor>ac1ec1511d8edd875deafa2db2508e458</anchor>
      <arglist>(fei::SharedPtr&lt; fei::MatrixGraph &gt; matrixGraph)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getGlobalNumRows</name>
      <anchorfile>classfei_1_1Matrix__Impl.html</anchorfile>
      <anchor>adfb6d0a9d35a3d48b89738b74736be2c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getLocalNumRows</name>
      <anchorfile>classfei_1_1Matrix__Impl.html</anchorfile>
      <anchor>add63ef3551b44b472eec70fe35bfe5d3</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>putScalar</name>
      <anchorfile>classfei_1_1Matrix__Impl.html</anchorfile>
      <anchor>a64849c8298d7defe1e075f3ee29d2d83</anchor>
      <arglist>(double scalar)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getRowLength</name>
      <anchorfile>classfei_1_1Matrix__Impl.html</anchorfile>
      <anchor>a7cf863ac056c0854b5a911ab10e2ec17</anchor>
      <arglist>(int row, int &amp;length) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>copyOutRow</name>
      <anchorfile>classfei_1_1Matrix__Impl.html</anchorfile>
      <anchor>aea04ec3ddc8fa1a7240cbf0b28671113</anchor>
      <arglist>(int row, int len, double *coefs, int *indices) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>sumIn</name>
      <anchorfile>classfei_1_1Matrix__Impl.html</anchorfile>
      <anchor>ac6b9c5ea93516ea5b5c04a26f7133fb9</anchor>
      <arglist>(int numRows, const int *rows, int numCols, const int *cols, const double *const *values, int format=0)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>copyIn</name>
      <anchorfile>classfei_1_1Matrix__Impl.html</anchorfile>
      <anchor>ab93c87323d0dcbf69b03df9b09c21be3</anchor>
      <arglist>(int numRows, const int *rows, int numCols, const int *cols, const double *const *values, int format=0)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>sumInFieldData</name>
      <anchorfile>classfei_1_1Matrix__Impl.html</anchorfile>
      <anchor>a594f7c1cddd5f06627eca1b349f589df</anchor>
      <arglist>(int fieldID, int idType, int rowID, int colID, const double *const *data, int format=0)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>sumInFieldData</name>
      <anchorfile>classfei_1_1Matrix__Impl.html</anchorfile>
      <anchor>afa65898d971b6803ab33c13b7a027f4d</anchor>
      <arglist>(int fieldID, int idType, int rowID, int colID, const double *data, int format=0)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>sumIn</name>
      <anchorfile>classfei_1_1Matrix__Impl.html</anchorfile>
      <anchor>a7a2c1d444c40665b7dddf4e74cc5e602</anchor>
      <arglist>(int blockID, int connectivityID, const double *const *values, int format=0)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>globalAssemble</name>
      <anchorfile>classfei_1_1Matrix__Impl.html</anchorfile>
      <anchor>ab46d13d908ca53e7011228ef0bf55dd8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>multiply</name>
      <anchorfile>classfei_1_1Matrix__Impl.html</anchorfile>
      <anchor>a052ab72239ff7ecaacf27e350e9bac84</anchor>
      <arglist>(fei::Vector *x, fei::Vector *y)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setCommSizes</name>
      <anchorfile>classfei_1_1Matrix__Impl.html</anchorfile>
      <anchor>addaaef890828fcab19dcd8d23ee4f6c0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>gatherFromOverlap</name>
      <anchorfile>classfei_1_1Matrix__Impl.html</anchorfile>
      <anchor>a069a531de69ca7b2701642d12c371975</anchor>
      <arglist>(bool accumulate=true)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>writeToFile</name>
      <anchorfile>classfei_1_1Matrix__Impl.html</anchorfile>
      <anchor>ad8c6cafa1d68da8e24bb69340e133307</anchor>
      <arglist>(const char *filename, bool matrixMarketFormat=true)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>writeToStream</name>
      <anchorfile>classfei_1_1Matrix__Impl.html</anchorfile>
      <anchor>a0556366c9cfbdc512a7712964b8ef4ec</anchor>
      <arglist>(FEI_OSTREAM &amp;ostrm, bool matrixMarketFormat=true)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>usingBlockEntryStorage</name>
      <anchorfile>classfei_1_1Matrix__Impl.html</anchorfile>
      <anchor>a67e8ad46f9bfcb38ffef8aa66f2003e1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>giveToUnderlyingMatrix</name>
      <anchorfile>classfei_1_1Matrix__Impl.html</anchorfile>
      <anchor>a3a42b2ba618e908a8032f12831549f8e</anchor>
      <arglist>(int numRows, const int *rows, int numCols, const int *cols, const double *const *values, bool sumInto, int format)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>giveToUnderlyingBlockMatrix</name>
      <anchorfile>classfei_1_1Matrix__Impl.html</anchorfile>
      <anchor>aec6b94567fbe293fb943c04426955205</anchor>
      <arglist>(int row, int rowDim, int numCols, const int *cols, const int *LDAs, const int *colDims, const double *const *values, bool sumInto)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>markState</name>
      <anchorfile>classfei_1_1Matrix__Impl.html</anchorfile>
      <anchor>a28ab730c1d9d5d32f425a79e17695217</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>changedSinceMark</name>
      <anchorfile>classfei_1_1Matrix__Impl.html</anchorfile>
      <anchor>a6c8f542cca8913245c6c093d8c27e4f2</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>fei::MatrixGraph</name>
    <filename>classfei_1_1MatrixGraph.html</filename>
    <class kind="class">fei::MatrixGraph::Factory</class>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~MatrixGraph</name>
      <anchorfile>classfei_1_1MatrixGraph.html</anchorfile>
      <anchor>a97946927434bbf17853e74b1a96d1142</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>setParameters</name>
      <anchorfile>classfei_1_1MatrixGraph.html</anchorfile>
      <anchor>aefe7ef1dcaedc70e840e6469ca355cfd</anchor>
      <arglist>(const fei::ParameterSet &amp;params)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>setRowSpace</name>
      <anchorfile>classfei_1_1MatrixGraph.html</anchorfile>
      <anchor>af9a5214723d465812d4a1c3891221a09</anchor>
      <arglist>(fei::SharedPtr&lt; fei::VectorSpace &gt; rowSpace)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual fei::SharedPtr&lt; fei::VectorSpace &gt;</type>
      <name>getRowSpace</name>
      <anchorfile>classfei_1_1MatrixGraph.html</anchorfile>
      <anchor>ae59b58a72d6ba8a5708afa48b77802e7</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>setColumnSpace</name>
      <anchorfile>classfei_1_1MatrixGraph.html</anchorfile>
      <anchor>a0245032cf2c2fec688499328e28faa4e</anchor>
      <arglist>(fei::SharedPtr&lt; fei::VectorSpace &gt; columnSpace)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual fei::SharedPtr&lt; fei::VectorSpace &gt;</type>
      <name>getColSpace</name>
      <anchorfile>classfei_1_1MatrixGraph.html</anchorfile>
      <anchor>ac42d895989a0566457edf71b7cfac840</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>definePattern</name>
      <anchorfile>classfei_1_1MatrixGraph.html</anchorfile>
      <anchor>a17f2eaeeddd2ced7a3ae63a172029901</anchor>
      <arglist>(int numIDs, int idType)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>definePattern</name>
      <anchorfile>classfei_1_1MatrixGraph.html</anchorfile>
      <anchor>a5fc2aca28dd9410df24fa35c0d1e121c</anchor>
      <arglist>(int numIDs, int idType, int fieldID)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>definePattern</name>
      <anchorfile>classfei_1_1MatrixGraph.html</anchorfile>
      <anchor>abd94a38e337ad299cbfb3e9bb94acf24</anchor>
      <arglist>(int numIDs, int idType, const int *numFieldsPerID, const int *fieldIDs)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>definePattern</name>
      <anchorfile>classfei_1_1MatrixGraph.html</anchorfile>
      <anchor>abe5879aa66289ac49b11d0793db919ac</anchor>
      <arglist>(int numIDs, const int *idTypes, const int *numFieldsPerID, const int *fieldIDs)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>initConnectivityBlock</name>
      <anchorfile>classfei_1_1MatrixGraph.html</anchorfile>
      <anchor>af804b2ce89802ac0587c5ca9a502033d</anchor>
      <arglist>(int blockID, int numConnectivityLists, int patternID, bool diagonal=false)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>initConnectivityBlock</name>
      <anchorfile>classfei_1_1MatrixGraph.html</anchorfile>
      <anchor>acfc49e01d246a2678191aa7721bb08c1</anchor>
      <arglist>(int numConnectivityLists, int patternID, bool diagonal=false)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>initConnectivityBlock</name>
      <anchorfile>classfei_1_1MatrixGraph.html</anchorfile>
      <anchor>a828ed6ebd5db364483125ac494a175c0</anchor>
      <arglist>(int blockID, int numConnectivityLists, int rowPatternID, int colPatternID)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>initConnectivity</name>
      <anchorfile>classfei_1_1MatrixGraph.html</anchorfile>
      <anchor>aa45d1d239313c0f7bda2822159e5ee5e</anchor>
      <arglist>(int blockID, int connectivityID, const int *connectedIdentifiers)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>initConnectivity</name>
      <anchorfile>classfei_1_1MatrixGraph.html</anchorfile>
      <anchor>a68784152dfb2b09b9c4df01387d153ef</anchor>
      <arglist>(int blockID, int connectivityID, const int *rowConnectedIdentifiers, const int *colConnectedIdentifiers)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>initConnectivity</name>
      <anchorfile>classfei_1_1MatrixGraph.html</anchorfile>
      <anchor>a266c4e702acbe52b6e9edb64e025b091</anchor>
      <arglist>(int patternID, const int *connectedIdentifiers)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>initConnectivity</name>
      <anchorfile>classfei_1_1MatrixGraph.html</anchorfile>
      <anchor>ac6f68e3128440230ca1791f8a8e202ed</anchor>
      <arglist>(int rowPatternID, const int *rowConnectedIdentifiers, int colPatternID, const int *colConnectedIdentifiers)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>initConnectivity</name>
      <anchorfile>classfei_1_1MatrixGraph.html</anchorfile>
      <anchor>a0cb8c9b385750ae160acadb135f40b38</anchor>
      <arglist>(int idType, int numRows, const int *rowIDs, const int *rowOffsets, const int *packedColumnIDs)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>initConnectivity</name>
      <anchorfile>classfei_1_1MatrixGraph.html</anchorfile>
      <anchor>ad23a98df3107fbd600ebf6a270acf5ae</anchor>
      <arglist>(int idType, int fieldID, int numRows, const int *rowIDs, const int *rowOffsets, const int *packedColumnIDs)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>initConnectivity</name>
      <anchorfile>classfei_1_1MatrixGraph.html</anchorfile>
      <anchor>a2e16a910fef80cf191f3fe68e62f1cc1</anchor>
      <arglist>(int idType, int numRows, const int *rowIDs, const int *rowLengths, const int *const *columnIDs)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>initLagrangeConstraint</name>
      <anchorfile>classfei_1_1MatrixGraph.html</anchorfile>
      <anchor>ada89c4dc9ad465c27a1eef765d547529</anchor>
      <arglist>(int constraintID, int constraintIDType, int numIDs, const int *idTypes, const int *IDs, const int *fieldIDs)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>initPenaltyConstraint</name>
      <anchorfile>classfei_1_1MatrixGraph.html</anchorfile>
      <anchor>a2a5c883ff61bd7d8fc7a0bcbaaa85981</anchor>
      <arglist>(int constraintID, int constraintIDType, int numIDs, const int *idTypes, const int *IDs, const int *fieldIDs)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>initSlaveConstraint</name>
      <anchorfile>classfei_1_1MatrixGraph.html</anchorfile>
      <anchor>ac34b90dd5753d6b07bb3d608d109e071</anchor>
      <arglist>(int numIDs, const int *idTypes, const int *IDs, const int *fieldIDs, int offsetOfSlave, int offsetIntoSlaveField, const double *weights, double rhsValue)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>hasSlaveDof</name>
      <anchorfile>classfei_1_1MatrixGraph.html</anchorfile>
      <anchor>a9452b82239d7488fd8a0a770b3403b05</anchor>
      <arglist>(int ID, int idType)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>initComplete</name>
      <anchorfile>classfei_1_1MatrixGraph.html</anchorfile>
      <anchor>a31b6e7af7ba8794b4a8036e3bfcd17ea</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual fei::SharedPtr&lt; fei::SparseRowGraph &gt;</type>
      <name>createGraph</name>
      <anchorfile>classfei_1_1MatrixGraph.html</anchorfile>
      <anchor>ad8ed13730e50e6c4720fa611651c6e85</anchor>
      <arglist>(bool blockEntryGraph, bool localRowGraph_includeSharedRows=false)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>compareStructure</name>
      <anchorfile>classfei_1_1MatrixGraph.html</anchorfile>
      <anchor>a92fc4c4510020f492d4527a219faab71</anchor>
      <arglist>(const fei::MatrixGraph &amp;matrixGraph, bool &amp;equivalent) const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>getNumConnectivityBlocks</name>
      <anchorfile>classfei_1_1MatrixGraph.html</anchorfile>
      <anchor>a7d11df53c5aa0d0ad232ad9ae442f853</anchor>
      <arglist>() const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual std::map&lt; int, fei::ConnectivityBlock * &gt; &amp;</type>
      <name>getConnectivityBlocks</name>
      <anchorfile>classfei_1_1MatrixGraph.html</anchorfile>
      <anchor>a8375c0521df31e5d67244f41998ba867</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>getConnectivityBlockIDs</name>
      <anchorfile>classfei_1_1MatrixGraph.html</anchorfile>
      <anchor>a4a624cb614a1e9951f74f6037782efb9</anchor>
      <arglist>(std::vector&lt; int &gt; &amp;blockIDs) const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>getNumIDsPerConnectivityList</name>
      <anchorfile>classfei_1_1MatrixGraph.html</anchorfile>
      <anchor>a7466a2b3a3c349503ca5902b646d4c60</anchor>
      <arglist>(int blockID) const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>getConnectivityNumIndices</name>
      <anchorfile>classfei_1_1MatrixGraph.html</anchorfile>
      <anchor>ab7bf5abcc0151a8048ea743d3ea62598</anchor>
      <arglist>(int blockID) const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>getConnectivityNumIndices</name>
      <anchorfile>classfei_1_1MatrixGraph.html</anchorfile>
      <anchor>a0a1ece67e83451d21830502c533259bf</anchor>
      <arglist>(int blockID, int &amp;numRowIndices, int &amp;numColIndices)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>getConnectivityIndices</name>
      <anchorfile>classfei_1_1MatrixGraph.html</anchorfile>
      <anchor>ae4cc89a624e454de9a338964bb670e12</anchor>
      <arglist>(int blockID, int connectivityID, int indicesAllocLen, int *indices, int &amp;numIndices)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>getConnectivityIndices</name>
      <anchorfile>classfei_1_1MatrixGraph.html</anchorfile>
      <anchor>aca3f2651096128ca04ece1cede3c06b6</anchor>
      <arglist>(int blockID, int connectivityID, int rowIndicesAllocLen, int *rowIndices, int &amp;numRowIndices, int colIndicesAllocLen, int *colIndices, int &amp;numColIndices)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>getPatternNumIndices</name>
      <anchorfile>classfei_1_1MatrixGraph.html</anchorfile>
      <anchor>ace411484bfae5798bfd7c7d1e250e9be</anchor>
      <arglist>(int patternID, int &amp;numIndices)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>getPatternIndices</name>
      <anchorfile>classfei_1_1MatrixGraph.html</anchorfile>
      <anchor>ac79aeb51093fa204233e9d81688be361</anchor>
      <arglist>(int patternID, const int *IDs, std::vector&lt; int &gt; &amp;indices)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>getLocalNumLagrangeConstraints</name>
      <anchorfile>classfei_1_1MatrixGraph.html</anchorfile>
      <anchor>adc7c75b0b3df65ac98fa5470543796be</anchor>
      <arglist>() const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>getGlobalNumSlaveConstraints</name>
      <anchorfile>classfei_1_1MatrixGraph.html</anchorfile>
      <anchor>a1bdcb7af75976a3ab5c884adbca7f7fa</anchor>
      <arglist>() const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual ConstraintType *</type>
      <name>getLagrangeConstraint</name>
      <anchorfile>classfei_1_1MatrixGraph.html</anchorfile>
      <anchor>a8c109ae84ef7a100dc60ca0f15601e93</anchor>
      <arglist>(int constraintID)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual std::map&lt; int, ConstraintType * &gt; &amp;</type>
      <name>getLagrangeConstraints</name>
      <anchorfile>classfei_1_1MatrixGraph.html</anchorfile>
      <anchor>adf3fb99fc6965602f69331d4d593d240</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual ConstraintType *</type>
      <name>getPenaltyConstraint</name>
      <anchorfile>classfei_1_1MatrixGraph.html</anchorfile>
      <anchor>a9090c57d840c59e3a2a4e99449110671</anchor>
      <arglist>(int constraintID)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual ConstraintType *</type>
      <name>getSlaveConstraint</name>
      <anchorfile>classfei_1_1MatrixGraph.html</anchorfile>
      <anchor>abb1306ce3f9af0f73f25a8e0ea59d7c2</anchor>
      <arglist>(int constraintID)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>getConstraintConnectivityIndices</name>
      <anchorfile>classfei_1_1MatrixGraph.html</anchorfile>
      <anchor>a96d5a7b08467568b5fbde08bcf8ecd55</anchor>
      <arglist>(ConstraintType *cr, std::vector&lt; int &gt; &amp;globalIndices)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual const fei::ConnectivityBlock *</type>
      <name>getConnectivityBlock</name>
      <anchorfile>classfei_1_1MatrixGraph.html</anchorfile>
      <anchor>a71acdfe4458e71d51e392cb58c9ce492</anchor>
      <arglist>(int blockID) const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual fei::ConnectivityBlock *</type>
      <name>getConnectivityBlock</name>
      <anchorfile>classfei_1_1MatrixGraph.html</anchorfile>
      <anchor>a3429e7b0e057dbefda7ab1480e1eff83</anchor>
      <arglist>(int blockID)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>setIndicesMode</name>
      <anchorfile>classfei_1_1MatrixGraph.html</anchorfile>
      <anchor>a50518c4c17cc22b42f9611af2208ae7a</anchor>
      <arglist>(int mode)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual fei::SharedPtr&lt; fei::FillableMat &gt;</type>
      <name>getSlaveDependencyMatrix</name>
      <anchorfile>classfei_1_1MatrixGraph.html</anchorfile>
      <anchor>ade99133605917e88aaeb1d8ad3e86258</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual fei::Pattern *</type>
      <name>getPattern</name>
      <anchorfile>classfei_1_1MatrixGraph.html</anchorfile>
      <anchor>aa731433dafa27a61bdabd0094ad364a9</anchor>
      <arglist>(int patternID)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>createSlaveMatrices</name>
      <anchorfile>classfei_1_1MatrixGraph.html</anchorfile>
      <anchor>a8f99fc40203d67b85ea9ed5203a730b6</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual fei::SharedPtr&lt; fei::Reducer &gt;</type>
      <name>getReducer</name>
      <anchorfile>classfei_1_1MatrixGraph.html</anchorfile>
      <anchor>a9324d9d76346f13db5e877b841e33a4b</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual fei::SharedPtr&lt; fei::SparseRowGraph &gt;</type>
      <name>getRemotelyOwnedGraphRows</name>
      <anchorfile>classfei_1_1MatrixGraph.html</anchorfile>
      <anchor>a05b65f3d4089f8b6fd3b1e533b7ccc9a</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>getConstrainedIndices</name>
      <anchorfile>classfei_1_1MatrixGraph.html</anchorfile>
      <anchor>a6e78f50eaf7380da970934374c9983f6</anchor>
      <arglist>(std::vector&lt; int &gt; &amp;crindices) const  =0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>fei::MatrixGraph_Impl2</name>
    <filename>classfei_1_1MatrixGraph__Impl2.html</filename>
    <base>fei::MatrixGraph</base>
    <base protection="private">fei::Logger</base>
    <class kind="class">fei::MatrixGraph_Impl2::Factory</class>
    <member kind="function">
      <type></type>
      <name>MatrixGraph_Impl2</name>
      <anchorfile>classfei_1_1MatrixGraph__Impl2.html</anchorfile>
      <anchor>a11946111970e7d90a8ca7b3dcd0b314f</anchor>
      <arglist>(fei::SharedPtr&lt; fei::VectorSpace &gt; rowSpace, fei::SharedPtr&lt; fei::VectorSpace &gt; colSpace, const char *name=NULL)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~MatrixGraph_Impl2</name>
      <anchorfile>classfei_1_1MatrixGraph__Impl2.html</anchorfile>
      <anchor>a646925217a0dfcebc7b50992fb09af0c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setParameters</name>
      <anchorfile>classfei_1_1MatrixGraph__Impl2.html</anchorfile>
      <anchor>a03369ec20d70a22219b877f6180f51a4</anchor>
      <arglist>(const fei::ParameterSet &amp;params)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setRowSpace</name>
      <anchorfile>classfei_1_1MatrixGraph__Impl2.html</anchorfile>
      <anchor>a73d078e9d642e0bfc3e6fd0fe12641a2</anchor>
      <arglist>(fei::SharedPtr&lt; fei::VectorSpace &gt; rowSpace)</arglist>
    </member>
    <member kind="function">
      <type>fei::SharedPtr&lt; fei::VectorSpace &gt;</type>
      <name>getRowSpace</name>
      <anchorfile>classfei_1_1MatrixGraph__Impl2.html</anchorfile>
      <anchor>a0214e030feaa3cac70335abe249986cd</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setColumnSpace</name>
      <anchorfile>classfei_1_1MatrixGraph__Impl2.html</anchorfile>
      <anchor>a57730b75478453d8d0c6ceea7bb40337</anchor>
      <arglist>(fei::SharedPtr&lt; fei::VectorSpace &gt; columnSpace)</arglist>
    </member>
    <member kind="function">
      <type>fei::SharedPtr&lt; fei::VectorSpace &gt;</type>
      <name>getColSpace</name>
      <anchorfile>classfei_1_1MatrixGraph__Impl2.html</anchorfile>
      <anchor>a3da568fe4dcad18fee545d1d7a17a8ab</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>definePattern</name>
      <anchorfile>classfei_1_1MatrixGraph__Impl2.html</anchorfile>
      <anchor>a4d93fb4d9acacc474bed26f3f6166983</anchor>
      <arglist>(int numIDs, int idType)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>definePattern</name>
      <anchorfile>classfei_1_1MatrixGraph__Impl2.html</anchorfile>
      <anchor>a2e1d2ce3e8d827b8c544940c3270eae9</anchor>
      <arglist>(int numIDs, int idType, int fieldID)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>definePattern</name>
      <anchorfile>classfei_1_1MatrixGraph__Impl2.html</anchorfile>
      <anchor>a94abeaef26ffdf302e8c824011dbfff8</anchor>
      <arglist>(int numIDs, int idType, const int *numFieldsPerID, const int *fieldIDs)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>definePattern</name>
      <anchorfile>classfei_1_1MatrixGraph__Impl2.html</anchorfile>
      <anchor>a67d35f59fdad202909c977cf5503091c</anchor>
      <arglist>(int numIDs, const int *idTypes, const int *numFieldsPerID, const int *fieldIDs)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>initConnectivityBlock</name>
      <anchorfile>classfei_1_1MatrixGraph__Impl2.html</anchorfile>
      <anchor>a724cfdfb3cbf220d8b65233e17b7319b</anchor>
      <arglist>(int blockID, int numConnectivityLists, int patternID, bool diagonal=false)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>initConnectivityBlock</name>
      <anchorfile>classfei_1_1MatrixGraph__Impl2.html</anchorfile>
      <anchor>a12603184258e621fc7b27d2c5aba42c1</anchor>
      <arglist>(int numConnectivityLists, int patternID, bool diagonal=false)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>initConnectivityBlock</name>
      <anchorfile>classfei_1_1MatrixGraph__Impl2.html</anchorfile>
      <anchor>ad537feceee1a1cfa3bdee6c0f4259ac7</anchor>
      <arglist>(int blockID, int numConnectivityLists, int rowPatternID, int colPatternID)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>initConnectivity</name>
      <anchorfile>classfei_1_1MatrixGraph__Impl2.html</anchorfile>
      <anchor>ac08877fcd42cc8b40f07bde00b6a5d91</anchor>
      <arglist>(int blockID, int connectivityID, const int *connectedIdentifiers)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>initConnectivity</name>
      <anchorfile>classfei_1_1MatrixGraph__Impl2.html</anchorfile>
      <anchor>a4ee319d0657ed27035632d717dc21e3b</anchor>
      <arglist>(int blockID, int connectivityID, const int *rowConnectedIdentifiers, const int *colConnectedIdentifiers)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>initConnectivity</name>
      <anchorfile>classfei_1_1MatrixGraph__Impl2.html</anchorfile>
      <anchor>a7dc854d0bfc8343f0149c7b5028bc0bd</anchor>
      <arglist>(int patternID, const int *connectedIdentifiers)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>initConnectivity</name>
      <anchorfile>classfei_1_1MatrixGraph__Impl2.html</anchorfile>
      <anchor>a59b0f060453a4ef15ad09a77bca9446b</anchor>
      <arglist>(int rowPatternID, const int *rowConnectedIdentifiers, int colPatternID, const int *colConnectedIdentifiers)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>initConnectivity</name>
      <anchorfile>classfei_1_1MatrixGraph__Impl2.html</anchorfile>
      <anchor>a0e5c9576829554c05bdbd1fb0d3e464c</anchor>
      <arglist>(int idType, int numRows, const int *rowIDs, const int *rowOffsets, const int *packedColumnIDs)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>initConnectivity</name>
      <anchorfile>classfei_1_1MatrixGraph__Impl2.html</anchorfile>
      <anchor>af612aa890acbdec7a57d239136344735</anchor>
      <arglist>(int idType, int fieldID, int numRows, const int *rowIDs, const int *rowOffsets, const int *packedColumnIDs)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>initConnectivity</name>
      <anchorfile>classfei_1_1MatrixGraph__Impl2.html</anchorfile>
      <anchor>a391d0189d0baba3ac6e2ff3c6f647693</anchor>
      <arglist>(int idType, int numRows, const int *rowIDs, const int *rowLengths, const int *const *columnIDs)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>initLagrangeConstraint</name>
      <anchorfile>classfei_1_1MatrixGraph__Impl2.html</anchorfile>
      <anchor>a9a22da1a55945b27a4a55caeead58703</anchor>
      <arglist>(int constraintID, int constraintIDType, int numIDs, const int *idTypes, const int *IDs, const int *fieldIDs)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>initPenaltyConstraint</name>
      <anchorfile>classfei_1_1MatrixGraph__Impl2.html</anchorfile>
      <anchor>a63fa63fda1da5f7d22634704d16b2769</anchor>
      <arglist>(int constraintID, int constraintIDType, int numIDs, const int *idTypes, const int *IDs, const int *fieldIDs)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>initSlaveConstraint</name>
      <anchorfile>classfei_1_1MatrixGraph__Impl2.html</anchorfile>
      <anchor>a8baa27603726fdddce0e858b8dbc25ad</anchor>
      <arglist>(int numIDs, const int *idTypes, const int *IDs, const int *fieldIDs, int offsetOfSlave, int offsetIntoSlaveField, const double *weights, double rhsValue)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>hasSlaveDof</name>
      <anchorfile>classfei_1_1MatrixGraph__Impl2.html</anchorfile>
      <anchor>a77775d17f38d08b344efc4bfb7cf101f</anchor>
      <arglist>(int ID, int idType)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>initComplete</name>
      <anchorfile>classfei_1_1MatrixGraph__Impl2.html</anchorfile>
      <anchor>acbfc3f58f3f0f9747b5e6b603b208002</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>fei::SharedPtr&lt; fei::SparseRowGraph &gt;</type>
      <name>createGraph</name>
      <anchorfile>classfei_1_1MatrixGraph__Impl2.html</anchorfile>
      <anchor>ae13439aa5aa24186ce10dbae8caf753a</anchor>
      <arglist>(bool blockEntryGraph, bool localRowGraph_includeSharedRows=false)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>compareStructure</name>
      <anchorfile>classfei_1_1MatrixGraph__Impl2.html</anchorfile>
      <anchor>a502d981a4e01679375b61fe5aca48306</anchor>
      <arglist>(const fei::MatrixGraph &amp;matrixGraph, bool &amp;equivalent) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getNumConnectivityBlocks</name>
      <anchorfile>classfei_1_1MatrixGraph__Impl2.html</anchorfile>
      <anchor>afb578433fe1a00b864ffc0d1834a106c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>std::map&lt; int, fei::ConnectivityBlock * &gt; &amp;</type>
      <name>getConnectivityBlocks</name>
      <anchorfile>classfei_1_1MatrixGraph__Impl2.html</anchorfile>
      <anchor>a2b9ebe5d3143e32afeda891ee7c1cda4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getConnectivityBlockIDs</name>
      <anchorfile>classfei_1_1MatrixGraph__Impl2.html</anchorfile>
      <anchor>af7ddec3959f7c27002370c72f829c9d4</anchor>
      <arglist>(std::vector&lt; int &gt; &amp;blockIDs) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getNumIDsPerConnectivityList</name>
      <anchorfile>classfei_1_1MatrixGraph__Impl2.html</anchorfile>
      <anchor>a3bdda648040ec0bef65dc0f3b0eaf17a</anchor>
      <arglist>(int blockID) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getConnectivityNumIndices</name>
      <anchorfile>classfei_1_1MatrixGraph__Impl2.html</anchorfile>
      <anchor>a87dfebfc562bc5c6aa7191e05ce1973c</anchor>
      <arglist>(int blockID) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getConnectivityNumIndices</name>
      <anchorfile>classfei_1_1MatrixGraph__Impl2.html</anchorfile>
      <anchor>a55237ad74d921a042c49356c0458fdf9</anchor>
      <arglist>(int blockID, int &amp;numRowIndices, int &amp;numColIndices)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getConnectivityIndices</name>
      <anchorfile>classfei_1_1MatrixGraph__Impl2.html</anchorfile>
      <anchor>a26c79814d6c727c8d05b889a4cd676e0</anchor>
      <arglist>(int blockID, int connectivityID, int indicesAllocLen, int *indices, int &amp;numIndices)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getConnectivityIndices</name>
      <anchorfile>classfei_1_1MatrixGraph__Impl2.html</anchorfile>
      <anchor>a3be3e6b41d0d2e1b624886f492e7da2f</anchor>
      <arglist>(int blockID, int connectivityID, int rowIndicesAllocLen, int *rowIndices, int &amp;numRowIndices, int colIndicesAllocLen, int *colIndices, int &amp;numColIndices)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getPatternNumIndices</name>
      <anchorfile>classfei_1_1MatrixGraph__Impl2.html</anchorfile>
      <anchor>af3908d7450cb252248c6876f06907c96</anchor>
      <arglist>(int patternID, int &amp;numIndices)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getPatternIndices</name>
      <anchorfile>classfei_1_1MatrixGraph__Impl2.html</anchorfile>
      <anchor>a7ff9ae8f7d1b0caf6646e5eccd5948bc</anchor>
      <arglist>(int patternID, const int *IDs, std::vector&lt; int &gt; &amp;indices)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getLocalNumLagrangeConstraints</name>
      <anchorfile>classfei_1_1MatrixGraph__Impl2.html</anchorfile>
      <anchor>a1cdb7234915bef326e4162a06b3bdcd6</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getGlobalNumSlaveConstraints</name>
      <anchorfile>classfei_1_1MatrixGraph__Impl2.html</anchorfile>
      <anchor>a7e3c616aad2e1db9b85489061c6f7de1</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>ConstraintType *</type>
      <name>getLagrangeConstraint</name>
      <anchorfile>classfei_1_1MatrixGraph__Impl2.html</anchorfile>
      <anchor>a2394b5b8022fd50da0469495a4dbdb4e</anchor>
      <arglist>(int constraintID)</arglist>
    </member>
    <member kind="function">
      <type>std::map&lt; int, ConstraintType * &gt; &amp;</type>
      <name>getLagrangeConstraints</name>
      <anchorfile>classfei_1_1MatrixGraph__Impl2.html</anchorfile>
      <anchor>aa48dae08c1d595b9c63bc73c6ceec50f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>ConstraintType *</type>
      <name>getPenaltyConstraint</name>
      <anchorfile>classfei_1_1MatrixGraph__Impl2.html</anchorfile>
      <anchor>a621efbb1e017795b9dc6c47e2f7bc2b2</anchor>
      <arglist>(int constraintID)</arglist>
    </member>
    <member kind="function">
      <type>ConstraintType *</type>
      <name>getSlaveConstraint</name>
      <anchorfile>classfei_1_1MatrixGraph__Impl2.html</anchorfile>
      <anchor>a3cd34b1da19bee000ce37bcf4d722424</anchor>
      <arglist>(int constraintID)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getConstraintConnectivityIndices</name>
      <anchorfile>classfei_1_1MatrixGraph__Impl2.html</anchorfile>
      <anchor>abe3581006ecb8f8eaa3659a3b6fc6fc5</anchor>
      <arglist>(ConstraintType *cr, std::vector&lt; int &gt; &amp;globalIndices)</arglist>
    </member>
    <member kind="function">
      <type>const fei::ConnectivityBlock *</type>
      <name>getConnectivityBlock</name>
      <anchorfile>classfei_1_1MatrixGraph__Impl2.html</anchorfile>
      <anchor>a6fbd822f61b7ad4f631b8c52d6f82724</anchor>
      <arglist>(int blockID) const </arglist>
    </member>
    <member kind="function">
      <type>fei::ConnectivityBlock *</type>
      <name>getConnectivityBlock</name>
      <anchorfile>classfei_1_1MatrixGraph__Impl2.html</anchorfile>
      <anchor>a29a7d12ab166b3b4266581de2c13700d</anchor>
      <arglist>(int blockID)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setIndicesMode</name>
      <anchorfile>classfei_1_1MatrixGraph__Impl2.html</anchorfile>
      <anchor>a658d66e7e7406386878dd669a19901be</anchor>
      <arglist>(int mode)</arglist>
    </member>
    <member kind="function">
      <type>fei::SharedPtr&lt; FillableMat &gt;</type>
      <name>getSlaveDependencyMatrix</name>
      <anchorfile>classfei_1_1MatrixGraph__Impl2.html</anchorfile>
      <anchor>ab16753d398af34dd887ebcd9a4fe2e8f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>fei::Pattern *</type>
      <name>getPattern</name>
      <anchorfile>classfei_1_1MatrixGraph__Impl2.html</anchorfile>
      <anchor>aa06026306da479a52fe2d393185b4bc6</anchor>
      <arglist>(int patternID)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>createSlaveMatrices</name>
      <anchorfile>classfei_1_1MatrixGraph__Impl2.html</anchorfile>
      <anchor>a47d157ada8f8b1ebf89cfd3ab1b749c0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>fei::SharedPtr&lt; fei::Reducer &gt;</type>
      <name>getReducer</name>
      <anchorfile>classfei_1_1MatrixGraph__Impl2.html</anchorfile>
      <anchor>aaaca318f74d18b65a9ba61026eebbdab</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>fei::SharedPtr&lt; fei::SparseRowGraph &gt;</type>
      <name>getRemotelyOwnedGraphRows</name>
      <anchorfile>classfei_1_1MatrixGraph__Impl2.html</anchorfile>
      <anchor>adf5279a5541100b89cd343b0c9266c80</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>getConstrainedIndices</name>
      <anchorfile>classfei_1_1MatrixGraph__Impl2.html</anchorfile>
      <anchor>a95104b387e397912283571b17250684f</anchor>
      <arglist>(std::vector&lt; int &gt; &amp;crindices) const </arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>fei::MatrixTraits</name>
    <filename>structfei_1_1MatrixTraits.html</filename>
    <templarg></templarg>
    <member kind="function" static="yes">
      <type>static const char *</type>
      <name>typeName</name>
      <anchorfile>structfei_1_1MatrixTraits.html</anchorfile>
      <anchor>a74d55b9a26ba5cf5abffc4174edc264d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static int</type>
      <name>setValues</name>
      <anchorfile>structfei_1_1MatrixTraits.html</anchorfile>
      <anchor>adff053132a2b39c0b4b1ae83fa40f2a1</anchor>
      <arglist>(T *mat, double scalar)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static int</type>
      <name>getNumLocalRows</name>
      <anchorfile>structfei_1_1MatrixTraits.html</anchorfile>
      <anchor>a4d3cb040b5a319b7eacb69ce0425cd61</anchor>
      <arglist>(T *mat, int &amp;numRows)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static int</type>
      <name>getRowLength</name>
      <anchorfile>structfei_1_1MatrixTraits.html</anchorfile>
      <anchor>a41230410d57690c962d72dc5ef4f144b</anchor>
      <arglist>(T *mat, int row, int &amp;length)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static int</type>
      <name>copyOutRow</name>
      <anchorfile>structfei_1_1MatrixTraits.html</anchorfile>
      <anchor>acff01ea9636aaeb2e2a3ff06e02ff94c</anchor>
      <arglist>(T *mat, int row, int len, double *coefs, int *indices)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static int</type>
      <name>putValuesIn</name>
      <anchorfile>structfei_1_1MatrixTraits.html</anchorfile>
      <anchor>aa9b90bf9e8267d33e5c677d2deb25e63</anchor>
      <arglist>(T *mat, int numRows, const int *rows, int numCols, const int *cols, const double *const *values, bool sum_into)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static int</type>
      <name>globalAssemble</name>
      <anchorfile>structfei_1_1MatrixTraits.html</anchorfile>
      <anchor>a2d9bd6cd11bd280ccd5834bc98acd345</anchor>
      <arglist>(T *A)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static int</type>
      <name>matvec</name>
      <anchorfile>structfei_1_1MatrixTraits.html</anchorfile>
      <anchor>a1b066a4fab32364aee803da9357663de</anchor>
      <arglist>(T *A, fei::Vector *x, fei::Vector *y)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>fei::MatrixTraits&lt; fei::LinearProblemManager &gt;</name>
    <filename>structfei_1_1MatrixTraits_3_01fei_1_1LinearProblemManager_01_4.html</filename>
    <member kind="function" static="yes">
      <type>static const char *</type>
      <name>typeName</name>
      <anchorfile>structfei_1_1MatrixTraits_3_01fei_1_1LinearProblemManager_01_4.html</anchorfile>
      <anchor>a847edf93599e1069b79669000c721d26</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static int</type>
      <name>setValues</name>
      <anchorfile>structfei_1_1MatrixTraits_3_01fei_1_1LinearProblemManager_01_4.html</anchorfile>
      <anchor>a3a99d427a0b1bf9f189ec94cbabb273a</anchor>
      <arglist>(fei::LinearProblemManager *mat, double scalar)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static int</type>
      <name>getNumLocalRows</name>
      <anchorfile>structfei_1_1MatrixTraits_3_01fei_1_1LinearProblemManager_01_4.html</anchorfile>
      <anchor>aafd064e9c2cd002961d03fd9ff0a3573</anchor>
      <arglist>(fei::LinearProblemManager *mat, int &amp;numRows)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static int</type>
      <name>getRowLength</name>
      <anchorfile>structfei_1_1MatrixTraits_3_01fei_1_1LinearProblemManager_01_4.html</anchorfile>
      <anchor>a351cd72b09addb77b428f064187a2961</anchor>
      <arglist>(fei::LinearProblemManager *mat, int row, int &amp;length)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static int</type>
      <name>copyOutRow</name>
      <anchorfile>structfei_1_1MatrixTraits_3_01fei_1_1LinearProblemManager_01_4.html</anchorfile>
      <anchor>aca3bf5f11c311fae6032f12eea72c44d</anchor>
      <arglist>(fei::LinearProblemManager *mat, int row, int len, double *coefs, int *indices)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static int</type>
      <name>putValuesIn</name>
      <anchorfile>structfei_1_1MatrixTraits_3_01fei_1_1LinearProblemManager_01_4.html</anchorfile>
      <anchor>afcc39f46f104529fc6189c7279de47e4</anchor>
      <arglist>(fei::LinearProblemManager *mat, int numRows, const int *rows, int numCols, const int *cols, const double *const *values, bool sum_into)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static int</type>
      <name>globalAssemble</name>
      <anchorfile>structfei_1_1MatrixTraits_3_01fei_1_1LinearProblemManager_01_4.html</anchorfile>
      <anchor>a2855a42f8c87f3d67f0b1c427e14c390</anchor>
      <arglist>(fei::LinearProblemManager *mat)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static int</type>
      <name>matvec</name>
      <anchorfile>structfei_1_1MatrixTraits_3_01fei_1_1LinearProblemManager_01_4.html</anchorfile>
      <anchor>a1744b720965753f8a80797cec24a5134</anchor>
      <arglist>(fei::LinearProblemManager *mat, fei::Vector *x, fei::Vector *y)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>fei::MatrixTraits&lt; FillableMat &gt;</name>
    <filename>structfei_1_1MatrixTraits_3_01FillableMat_01_4.html</filename>
    <member kind="function" static="yes">
      <type>static const char *</type>
      <name>typeName</name>
      <anchorfile>structfei_1_1MatrixTraits_3_01FillableMat_01_4.html</anchorfile>
      <anchor>a1c4eff4945eecac03ae3aa80a8830cc7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static int</type>
      <name>setValues</name>
      <anchorfile>structfei_1_1MatrixTraits_3_01FillableMat_01_4.html</anchorfile>
      <anchor>a036c9de84e64cf9cadc476ec128906d2</anchor>
      <arglist>(FillableMat *mat, double scalar)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static int</type>
      <name>getNumLocalRows</name>
      <anchorfile>structfei_1_1MatrixTraits_3_01FillableMat_01_4.html</anchorfile>
      <anchor>a292ba4dc0ea7529bd4eea666696fe7a2</anchor>
      <arglist>(FillableMat *mat, int &amp;numRows)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static int</type>
      <name>getRowLength</name>
      <anchorfile>structfei_1_1MatrixTraits_3_01FillableMat_01_4.html</anchorfile>
      <anchor>a5768cd70d671619645ff6f071f9f2971</anchor>
      <arglist>(FillableMat *mat, int row, int &amp;length)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static int</type>
      <name>copyOutRow</name>
      <anchorfile>structfei_1_1MatrixTraits_3_01FillableMat_01_4.html</anchorfile>
      <anchor>a2f774163825531036d216c7660a50c56</anchor>
      <arglist>(FillableMat *mat, int row, int len, double *coefs, int *indices)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static int</type>
      <name>putValuesIn</name>
      <anchorfile>structfei_1_1MatrixTraits_3_01FillableMat_01_4.html</anchorfile>
      <anchor>a8801a6c73efc31a661235dca3cd35b5e</anchor>
      <arglist>(FillableMat *mat, int numRows, const int *rows, int numCols, const int *cols, const double *const *values, bool sum_into)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static int</type>
      <name>globalAssemble</name>
      <anchorfile>structfei_1_1MatrixTraits_3_01FillableMat_01_4.html</anchorfile>
      <anchor>aeefffad829090430c12f6660cf6c09fd</anchor>
      <arglist>(FillableMat *mat)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static int</type>
      <name>matvec</name>
      <anchorfile>structfei_1_1MatrixTraits_3_01FillableMat_01_4.html</anchorfile>
      <anchor>a0cfb3e5923fea275bdb0e24adb0ebd5b</anchor>
      <arglist>(FillableMat *mat, fei::Vector *x, fei::Vector *y)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>fei::MatrixTraits&lt; FiniteElementData &gt;</name>
    <filename>structfei_1_1MatrixTraits_3_01FiniteElementData_01_4.html</filename>
    <member kind="function" static="yes">
      <type>static const char *</type>
      <name>typeName</name>
      <anchorfile>structfei_1_1MatrixTraits_3_01FiniteElementData_01_4.html</anchorfile>
      <anchor>ad9854b9a8b5df5269549e1b5145f054a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static int</type>
      <name>setValues</name>
      <anchorfile>structfei_1_1MatrixTraits_3_01FiniteElementData_01_4.html</anchorfile>
      <anchor>a73504ed7e425c8948e93269741235d17</anchor>
      <arglist>(FiniteElementData *fed, double scalar)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static int</type>
      <name>getNumLocalRows</name>
      <anchorfile>structfei_1_1MatrixTraits_3_01FiniteElementData_01_4.html</anchorfile>
      <anchor>a3f707fb8f2613645cdea9a9135206222</anchor>
      <arglist>(FiniteElementData *fed, int &amp;numRows)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static int</type>
      <name>getRowLength</name>
      <anchorfile>structfei_1_1MatrixTraits_3_01FiniteElementData_01_4.html</anchorfile>
      <anchor>a644eede794b0dd0ccd1a3eb4ad965281</anchor>
      <arglist>(FiniteElementData *fed, int row, int &amp;length)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static int</type>
      <name>copyOutRow</name>
      <anchorfile>structfei_1_1MatrixTraits_3_01FiniteElementData_01_4.html</anchorfile>
      <anchor>ad8bc14eba0416ce3fe4d39ab4c51969e</anchor>
      <arglist>(FiniteElementData *fed, int row, int len, double *coefs, int *indices)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static int</type>
      <name>putValuesIn</name>
      <anchorfile>structfei_1_1MatrixTraits_3_01FiniteElementData_01_4.html</anchorfile>
      <anchor>a821b383b6ee617dd653e431e94dfc6f1</anchor>
      <arglist>(FiniteElementData *fed, int numRows, const int *rows, int numCols, const int *cols, const double *const *values, bool sum_into)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static int</type>
      <name>globalAssemble</name>
      <anchorfile>structfei_1_1MatrixTraits_3_01FiniteElementData_01_4.html</anchorfile>
      <anchor>aba9d9cc1cdaa36db75068974b14177b8</anchor>
      <arglist>(FiniteElementData *fed)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static int</type>
      <name>matvec</name>
      <anchorfile>structfei_1_1MatrixTraits_3_01FiniteElementData_01_4.html</anchorfile>
      <anchor>a352040e2ce0758752bd0b9bed650cdad</anchor>
      <arglist>(FiniteElementData *fed, fei::Vector *x, fei::Vector *y)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>fei::MatrixTraits&lt; LinearSystemCore &gt;</name>
    <filename>structfei_1_1MatrixTraits_3_01LinearSystemCore_01_4.html</filename>
    <member kind="function" static="yes">
      <type>static const char *</type>
      <name>typeName</name>
      <anchorfile>structfei_1_1MatrixTraits_3_01LinearSystemCore_01_4.html</anchorfile>
      <anchor>a68729c52c524c3f12c5e61c161fc0385</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static int</type>
      <name>setValues</name>
      <anchorfile>structfei_1_1MatrixTraits_3_01LinearSystemCore_01_4.html</anchorfile>
      <anchor>a1b7ab1b7bca3fa7748d5fe15cc38c02b</anchor>
      <arglist>(LinearSystemCore *lsc, double scalar)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static int</type>
      <name>getNumLocalRows</name>
      <anchorfile>structfei_1_1MatrixTraits_3_01LinearSystemCore_01_4.html</anchorfile>
      <anchor>ac0ae278cbc90e880ea0f54529b41dad0</anchor>
      <arglist>(LinearSystemCore *lsc, int &amp;numRows)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static int</type>
      <name>getRowLength</name>
      <anchorfile>structfei_1_1MatrixTraits_3_01LinearSystemCore_01_4.html</anchorfile>
      <anchor>a445c8c6e03dc5a1fa256a1d8a4a06f9d</anchor>
      <arglist>(LinearSystemCore *lsc, int row, int &amp;length)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static int</type>
      <name>copyOutRow</name>
      <anchorfile>structfei_1_1MatrixTraits_3_01LinearSystemCore_01_4.html</anchorfile>
      <anchor>a575347a2a1cf967d3350d44d1c4e4c30</anchor>
      <arglist>(LinearSystemCore *lsc, int row, int len, double *coefs, int *indices)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static int</type>
      <name>putValuesIn</name>
      <anchorfile>structfei_1_1MatrixTraits_3_01LinearSystemCore_01_4.html</anchorfile>
      <anchor>a5610369a5aa37cfb5dd63bd009d79e8f</anchor>
      <arglist>(LinearSystemCore *lsc, int numRows, const int *rows, int numCols, const int *cols, const double *const *values, bool sum_into)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static int</type>
      <name>globalAssemble</name>
      <anchorfile>structfei_1_1MatrixTraits_3_01LinearSystemCore_01_4.html</anchorfile>
      <anchor>a1671cbd7c9c8d6b3b66bd5496b6e05f0</anchor>
      <arglist>(LinearSystemCore *lsc)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static int</type>
      <name>matvec</name>
      <anchorfile>structfei_1_1MatrixTraits_3_01LinearSystemCore_01_4.html</anchorfile>
      <anchor>a45b1048b000776c98af7384a01ae08e3</anchor>
      <arglist>(LinearSystemCore *lsc, fei::Vector *x, fei::Vector *y)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>fei::MessageHandler</name>
    <filename>classfei_1_1MessageHandler.html</filename>
    <templarg>T</templarg>
    <member kind="function" virtualness="pure">
      <type>virtual std::vector&lt; int &gt; &amp;</type>
      <name>getSendProcs</name>
      <anchorfile>classfei_1_1MessageHandler.html</anchorfile>
      <anchor>a982a58dab2dd19fe45392a90dcb42c3d</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual std::vector&lt; int &gt; &amp;</type>
      <name>getRecvProcs</name>
      <anchorfile>classfei_1_1MessageHandler.html</anchorfile>
      <anchor>acc7cf53d05736078a39c2010476001de</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>getSendMessageLength</name>
      <anchorfile>classfei_1_1MessageHandler.html</anchorfile>
      <anchor>aed9423c59fe40d22f9223f4c2f27d08d</anchor>
      <arglist>(int destProc, int &amp;messageLength)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>getSendMessage</name>
      <anchorfile>classfei_1_1MessageHandler.html</anchorfile>
      <anchor>ac9a334ca95419c35ff0d9575a3407d7f</anchor>
      <arglist>(int destProc, std::vector&lt; T &gt; &amp;message)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>processRecvMessage</name>
      <anchorfile>classfei_1_1MessageHandler.html</anchorfile>
      <anchor>a2d4606ac52055e48a6b4e4051e04d4e1</anchor>
      <arglist>(int srcProc, std::vector&lt; T &gt; &amp;message)=0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>MessageHandler&lt; int &gt;</name>
    <filename>classfei_1_1MessageHandler.html</filename>
    <member kind="function" virtualness="pure">
      <type>virtual std::vector&lt; int &gt; &amp;</type>
      <name>getSendProcs</name>
      <anchorfile>classfei_1_1MessageHandler.html</anchorfile>
      <anchor>a982a58dab2dd19fe45392a90dcb42c3d</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual std::vector&lt; int &gt; &amp;</type>
      <name>getRecvProcs</name>
      <anchorfile>classfei_1_1MessageHandler.html</anchorfile>
      <anchor>acc7cf53d05736078a39c2010476001de</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>getSendMessageLength</name>
      <anchorfile>classfei_1_1MessageHandler.html</anchorfile>
      <anchor>aed9423c59fe40d22f9223f4c2f27d08d</anchor>
      <arglist>(int destProc, int &amp;messageLength)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>getSendMessage</name>
      <anchorfile>classfei_1_1MessageHandler.html</anchorfile>
      <anchor>ac9a334ca95419c35ff0d9575a3407d7f</anchor>
      <arglist>(int destProc, std::vector&lt; int &gt; &amp;message)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>processRecvMessage</name>
      <anchorfile>classfei_1_1MessageHandler.html</anchorfile>
      <anchor>a2d4606ac52055e48a6b4e4051e04d4e1</anchor>
      <arglist>(int srcProc, std::vector&lt; int &gt; &amp;message)=0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>NodeCommMgr</name>
    <filename>classNodeCommMgr.html</filename>
    <base>MessageHandler&lt; int &gt;</base>
    <member kind="function">
      <type>std::vector&lt; int &gt; &amp;</type>
      <name>getSendProcs</name>
      <anchorfile>classNodeCommMgr.html</anchorfile>
      <anchor>af6a925e7736701ae2c69bdeb3cc3191a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>std::vector&lt; int &gt; &amp;</type>
      <name>getRecvProcs</name>
      <anchorfile>classNodeCommMgr.html</anchorfile>
      <anchor>a586da58cc57303de4f005ef96ccf093e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getSendMessageLength</name>
      <anchorfile>classNodeCommMgr.html</anchorfile>
      <anchor>abda45b3bb9fec4c0e0acd652eca4a7ec</anchor>
      <arglist>(int destProc, int &amp;messageLength)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getSendMessage</name>
      <anchorfile>classNodeCommMgr.html</anchorfile>
      <anchor>aa348c5f6c96e23ffcb8a4d40e034533c</anchor>
      <arglist>(int destProc, std::vector&lt; int &gt; &amp;message)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>processRecvMessage</name>
      <anchorfile>classNodeCommMgr.html</anchorfile>
      <anchor>a44a9616d9f8a8db0db84123a7bb9c9a0</anchor>
      <arglist>(int srcProc, std::vector&lt; int &gt; &amp;message)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>NodeDatabase</name>
    <filename>classNodeDatabase.html</filename>
    <member kind="function">
      <type></type>
      <name>NodeDatabase</name>
      <anchorfile>classNodeDatabase.html</anchorfile>
      <anchor>ab791f7eb7d44ef10e520716969ccf270</anchor>
      <arglist>(std::map&lt; int, int &gt; *fieldDatabase, NodeCommMgr *nodeCommMgr)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~NodeDatabase</name>
      <anchorfile>classNodeDatabase.html</anchorfile>
      <anchor>a469913a747a35605f8a85f9dcb614290</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getNumNodeDescriptors</name>
      <anchorfile>classNodeDatabase.html</anchorfile>
      <anchor>a83ce19e440577be4c7d770c0c61feca9</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>std::map&lt; GlobalID, int &gt; &amp;</type>
      <name>getNodeIDs</name>
      <anchorfile>classNodeDatabase.html</anchorfile>
      <anchor>a31f566f1a59191110a4e79d1ca29c198</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getNodeWithID</name>
      <anchorfile>classNodeDatabase.html</anchorfile>
      <anchor>a44d7009370d1cd26eec324637b726d70</anchor>
      <arglist>(GlobalID nodeID, const NodeDescriptor *&amp;node) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getNodeWithNumber</name>
      <anchorfile>classNodeDatabase.html</anchorfile>
      <anchor>afe624e895fa9b2a0e2f1cd318de93d87</anchor>
      <arglist>(int nodeNumber, const NodeDescriptor *&amp;node) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getNodeWithEqn</name>
      <anchorfile>classNodeDatabase.html</anchorfile>
      <anchor>a7275a92c867058a36e5efa57ae5084ce</anchor>
      <arglist>(int eqnNumber, const NodeDescriptor *&amp;node) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>getNodeAtIndex</name>
      <anchorfile>classNodeDatabase.html</anchorfile>
      <anchor>a971366b791ebe64868e77dedff35ad5c</anchor>
      <arglist>(int i, const NodeDescriptor *&amp;node) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>countLocalNodalEqns</name>
      <anchorfile>classNodeDatabase.html</anchorfile>
      <anchor>abbe5edb536a198d6f4b43368b847cb5a</anchor>
      <arglist>(int localRank)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>countLocalNodeDescriptors</name>
      <anchorfile>classNodeDatabase.html</anchorfile>
      <anchor>adb36233899748a5697577176b5dff3c1</anchor>
      <arglist>(int localRank)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getIndexOfID</name>
      <anchorfile>classNodeDatabase.html</anchorfile>
      <anchor>af214a0c33d70dbd27f3088aa614c8935</anchor>
      <arglist>(GlobalID nodeID) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>initNodeID</name>
      <anchorfile>classNodeDatabase.html</anchorfile>
      <anchor>ada81e3badd7591b1bfb2e648274a3646</anchor>
      <arglist>(GlobalID nodeID)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>initNodeIDs</name>
      <anchorfile>classNodeDatabase.html</anchorfile>
      <anchor>aadb422b26a53b050dbae076ef1e51b66</anchor>
      <arglist>(GlobalID *nodeIDs, int numNodes)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>synchronize</name>
      <anchorfile>classNodeDatabase.html</anchorfile>
      <anchor>a3403a192a1f04847ac24fad86106cc78</anchor>
      <arglist>(int firstLocalNodeNumber, int firstLocalEqn, int localRank, MPI_Comm comm)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getAssociatedNodeNumber</name>
      <anchorfile>classNodeDatabase.html</anchorfile>
      <anchor>a7ff701f2916fc5fd9500dfa3ccebab45</anchor>
      <arglist>(int eqnNumber)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getAssociatedFieldID</name>
      <anchorfile>classNodeDatabase.html</anchorfile>
      <anchor>ac38d15fa72e103ef6bd706cf4983e2dc</anchor>
      <arglist>(int eqnNumber)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isSynchronized</name>
      <anchorfile>classNodeDatabase.html</anchorfile>
      <anchor>a5e05d2a248234d8d54601aacd799baa8</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>NodeDescriptor</name>
    <filename>classNodeDescriptor.html</filename>
    <member kind="function">
      <type>bool</type>
      <name>getFieldEqnNumber</name>
      <anchorfile>classNodeDescriptor.html</anchorfile>
      <anchor>a29de255fd29dfbecb46b4eaea9207aba</anchor>
      <arglist>(int fieldID, int &amp;eqnNumber) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>getFieldID</name>
      <anchorfile>classNodeDescriptor.html</anchorfile>
      <anchor>ad2cbce5b141c362246a88bc4dd31caec</anchor>
      <arglist>(int eqnNumber, int &amp;fieldID, int &amp;offset_into_field) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>fei::Param</name>
    <filename>classfei_1_1Param.html</filename>
    <member kind="enumeration">
      <type></type>
      <name>ParamType</name>
      <anchorfile>classfei_1_1Param.html</anchorfile>
      <anchor>a394ea882b2dcab42d9fe1c2fd7f88556</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Param</name>
      <anchorfile>classfei_1_1Param.html</anchorfile>
      <anchor>a413c87aa0ddf69790765b64e49f925f4</anchor>
      <arglist>(const char *name, const char *value)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Param</name>
      <anchorfile>classfei_1_1Param.html</anchorfile>
      <anchor>ada618c7c4c48981365b99bb38ad43f9d</anchor>
      <arglist>(const char *name, double value)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Param</name>
      <anchorfile>classfei_1_1Param.html</anchorfile>
      <anchor>a8c5004ea4b6e28f69cca0542d4df511b</anchor>
      <arglist>(const char *name, int value)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Param</name>
      <anchorfile>classfei_1_1Param.html</anchorfile>
      <anchor>a22537aec9fc5e1477b282f01c4e1fe2f</anchor>
      <arglist>(const char *name, const void *value)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Param</name>
      <anchorfile>classfei_1_1Param.html</anchorfile>
      <anchor>a2c4a01ff72e653a57caa1fe77542ecd7</anchor>
      <arglist>(const char *name, bool value)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Param</name>
      <anchorfile>classfei_1_1Param.html</anchorfile>
      <anchor>a0d979c69a1c0bed6b0aa39c75453f3f2</anchor>
      <arglist>(const Param &amp;src)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~Param</name>
      <anchorfile>classfei_1_1Param.html</anchorfile>
      <anchor>a4e2dc8a37aa8535ce69a15af199dcc65</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Param &amp;</type>
      <name>operator=</name>
      <anchorfile>classfei_1_1Param.html</anchorfile>
      <anchor>aa7180defbc18820a78f8c105db3357c5</anchor>
      <arglist>(const Param &amp;src)</arglist>
    </member>
    <member kind="function">
      <type>const std::string &amp;</type>
      <name>getName</name>
      <anchorfile>classfei_1_1Param.html</anchorfile>
      <anchor>a8eedad779b46983ad5ba8d2ed5d36e28</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>ParamType</type>
      <name>getType</name>
      <anchorfile>classfei_1_1Param.html</anchorfile>
      <anchor>a1183c25cc7eeecbaae7ede4ea5ee66d1</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const std::string &amp;</type>
      <name>getStringValue</name>
      <anchorfile>classfei_1_1Param.html</anchorfile>
      <anchor>a06554128b52a3e7b1ef429b3375f699e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>getDoubleValue</name>
      <anchorfile>classfei_1_1Param.html</anchorfile>
      <anchor>a910a5a4a9c8f67799d07678e0d698803</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getIntValue</name>
      <anchorfile>classfei_1_1Param.html</anchorfile>
      <anchor>ad63fb1bee92100b38d16d94f47ceb1f6</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>getBoolValue</name>
      <anchorfile>classfei_1_1Param.html</anchorfile>
      <anchor>a30050570c4397a35f359504abfc0f1d9</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const void *</type>
      <name>getVoidValue</name>
      <anchorfile>classfei_1_1Param.html</anchorfile>
      <anchor>a5d4850247407b2a232119c1ab71bf4c3</anchor>
      <arglist>() const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>fei::ParameterSet</name>
    <filename>classfei_1_1ParameterSet.html</filename>
    <class kind="class">fei::ParameterSet::const_iterator</class>
    <member kind="function">
      <type></type>
      <name>ParameterSet</name>
      <anchorfile>classfei_1_1ParameterSet.html</anchorfile>
      <anchor>a115bdfd6b531e5984102827448ab20bc</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~ParameterSet</name>
      <anchorfile>classfei_1_1ParameterSet.html</anchorfile>
      <anchor>a1415f067b86c9cd17e2a5bcd8baf4a7d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>add</name>
      <anchorfile>classfei_1_1ParameterSet.html</anchorfile>
      <anchor>a55be045455fa3b24ae326330a31f2e0e</anchor>
      <arglist>(const Param &amp;param, bool maintain_unique_keys=true)</arglist>
    </member>
    <member kind="function">
      <type>const Param *</type>
      <name>get</name>
      <anchorfile>classfei_1_1ParameterSet.html</anchorfile>
      <anchor>a73f76ca34eae7c472d471f591d884b71</anchor>
      <arglist>(const char *name) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>size</name>
      <anchorfile>classfei_1_1ParameterSet.html</anchorfile>
      <anchor>a3a5be628be2f3830a6528b55d9bf38f3</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const_iterator</type>
      <name>begin</name>
      <anchorfile>classfei_1_1ParameterSet.html</anchorfile>
      <anchor>ab3b7df5b8f7ad4554837679cb48f18de</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const_iterator</type>
      <name>end</name>
      <anchorfile>classfei_1_1ParameterSet.html</anchorfile>
      <anchor>a9e6609b762f64cf1bf46409975ce2acc</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getIntParamValue</name>
      <anchorfile>classfei_1_1ParameterSet.html</anchorfile>
      <anchor>a334c98811b50a9ace14924664c7e8502</anchor>
      <arglist>(const char *name, int &amp;paramValue) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getDoubleParamValue</name>
      <anchorfile>classfei_1_1ParameterSet.html</anchorfile>
      <anchor>ae66a15c1ed3539e2c01a081274775dbb</anchor>
      <arglist>(const char *name, double &amp;paramValue) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getStringParamValue</name>
      <anchorfile>classfei_1_1ParameterSet.html</anchorfile>
      <anchor>a5f190f6a8760d94ccf3251bd812f3728</anchor>
      <arglist>(const char *name, std::string &amp;paramValue) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getBoolParamValue</name>
      <anchorfile>classfei_1_1ParameterSet.html</anchorfile>
      <anchor>a5183f06b5ebc10e8c37715df217e413f</anchor>
      <arglist>(const char *name, bool &amp;paramValue) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getVoidParamValue</name>
      <anchorfile>classfei_1_1ParameterSet.html</anchorfile>
      <anchor>a420905b4b9e2d2d398243136bd8b4bfd</anchor>
      <arglist>(const char *name, const void *&amp;paramValue) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>fei::Pattern</name>
    <filename>classfei_1_1Pattern.html</filename>
    <member kind="enumeration">
      <type></type>
      <name>PatternType</name>
      <anchorfile>classfei_1_1Pattern.html</anchorfile>
      <anchor>a029e96e0a32f40147d49aacec768f09b</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Pattern</name>
      <anchorfile>classfei_1_1Pattern.html</anchorfile>
      <anchor>ae72e22222807c01e54d5b8fae81ccaaf</anchor>
      <arglist>(int numIDs, int idType, snl_fei::RecordCollection *records)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Pattern</name>
      <anchorfile>classfei_1_1Pattern.html</anchorfile>
      <anchor>a541879e113d40da9ed6a990dd952cead</anchor>
      <arglist>(int numIDs, int idType, snl_fei::RecordCollection *records, int fieldID, int fieldSize)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Pattern</name>
      <anchorfile>classfei_1_1Pattern.html</anchorfile>
      <anchor>a96e1ee736b75eabb340b6a85f8c9ab43</anchor>
      <arglist>(int numIDs, int idType, snl_fei::RecordCollection *records, const int *numFieldsPerID, const int *fieldIDs, const int *fieldSizes)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Pattern</name>
      <anchorfile>classfei_1_1Pattern.html</anchorfile>
      <anchor>a4dbd31f5965a5a31af422bd15b34d0b9</anchor>
      <arglist>(int numIDs, const int *idTypes, snl_fei::RecordCollection *const *records, const int *numFieldsPerID, const int *fieldIDs, const int *fieldSizes)</arglist>
    </member>
    <member kind="function">
      <type>PatternType</type>
      <name>getPatternType</name>
      <anchorfile>classfei_1_1Pattern.html</anchorfile>
      <anchor>a50975d287bcc10a9cc377936c598d55d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getNumIDs</name>
      <anchorfile>classfei_1_1Pattern.html</anchorfile>
      <anchor>a3e201f2dfdcec8a5fb21c6614350114b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const int *</type>
      <name>getIDTypes</name>
      <anchorfile>classfei_1_1Pattern.html</anchorfile>
      <anchor>a14801e6454fac3efe54527afb200c973</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>snl_fei::RecordCollection *const *</type>
      <name>getRecordCollections</name>
      <anchorfile>classfei_1_1Pattern.html</anchorfile>
      <anchor>a616c836c5a836c44963623ccd0d5e88a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const int *</type>
      <name>getNumFieldsPerID</name>
      <anchorfile>classfei_1_1Pattern.html</anchorfile>
      <anchor>a4e8271d3def336bb333c4748180154c9</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const int *</type>
      <name>getFieldIDs</name>
      <anchorfile>classfei_1_1Pattern.html</anchorfile>
      <anchor>a6cbb437fa33a78352c1c2dcd019e1d8c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const int *</type>
      <name>getNumIndicesPerID</name>
      <anchorfile>classfei_1_1Pattern.html</anchorfile>
      <anchor>a0c56bba47accdc4711e05c1fba9c5017</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getTotalNumFields</name>
      <anchorfile>classfei_1_1Pattern.html</anchorfile>
      <anchor>a27d05a156c232ac7e4995a78aa1acd1a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getNumIndices</name>
      <anchorfile>classfei_1_1Pattern.html</anchorfile>
      <anchor>a1c095e538f117844cbb869c1eb24570f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator==</name>
      <anchorfile>classfei_1_1Pattern.html</anchorfile>
      <anchor>a3ccd8dc09f5a8c7fd3142b40f981d448</anchor>
      <arglist>(const Pattern &amp;rhs) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator!=</name>
      <anchorfile>classfei_1_1Pattern.html</anchorfile>
      <anchor>ab4eac3f69318fa162983ff465529c918</anchor>
      <arglist>(const Pattern &amp;rhs) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>snl_fei::PointBlockMap</name>
    <filename>classsnl__fei_1_1PointBlockMap.html</filename>
    <member kind="function">
      <type></type>
      <name>PointBlockMap</name>
      <anchorfile>classsnl__fei_1_1PointBlockMap.html</anchorfile>
      <anchor>ad86320be9d8dfa2afeea13a9a753f476</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~PointBlockMap</name>
      <anchorfile>classsnl__fei_1_1PointBlockMap.html</anchorfile>
      <anchor>ad35ce675bf6b043b792471b985e784a2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setPtEqualBlk</name>
      <anchorfile>classsnl__fei_1_1PointBlockMap.html</anchorfile>
      <anchor>af487cda71190d90a446a57ffab1e0f51</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>ptEqualBlk</name>
      <anchorfile>classsnl__fei_1_1PointBlockMap.html</anchorfile>
      <anchor>a6de5678968c6be54a60d41ce724dfd07</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>setEqn</name>
      <anchorfile>classsnl__fei_1_1PointBlockMap.html</anchorfile>
      <anchor>a6d50981bc3b329ae85d1399291fc8892</anchor>
      <arglist>(int ptEqn, int blkEqn)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>setEqn</name>
      <anchorfile>classsnl__fei_1_1PointBlockMap.html</anchorfile>
      <anchor>abf3829b09547b2b64db29f51ba81ac3c</anchor>
      <arglist>(int ptEqn, int blkEqn, int blkSize)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>setBlkEqnSize</name>
      <anchorfile>classsnl__fei_1_1PointBlockMap.html</anchorfile>
      <anchor>aacec29bdfdf406b092e13b7be687ca98</anchor>
      <arglist>(int blkEqn, int size)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getBlkEqnSize</name>
      <anchorfile>classsnl__fei_1_1PointBlockMap.html</anchorfile>
      <anchor>a9ddec87e14f12811e606551fcd1448d4</anchor>
      <arglist>(int blkEqn)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getMaxBlkEqnSize</name>
      <anchorfile>classsnl__fei_1_1PointBlockMap.html</anchorfile>
      <anchor>a97224acc7f0d14f5e6fa139b6eccdf1c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setMaxBlkEqnSize</name>
      <anchorfile>classsnl__fei_1_1PointBlockMap.html</anchorfile>
      <anchor>ad84790e530ae3f9e520968f73daea9d2</anchor>
      <arglist>(int sz)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>eqnToBlkEqn</name>
      <anchorfile>classsnl__fei_1_1PointBlockMap.html</anchorfile>
      <anchor>af8bd9c871f8d88fb22e01043e78078fd</anchor>
      <arglist>(int eqn) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>blkEqnToPtEqn</name>
      <anchorfile>classsnl__fei_1_1PointBlockMap.html</anchorfile>
      <anchor>a8611074e4def832e5b5008d0c8dab2ca</anchor>
      <arglist>(int blkEqn) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getBlkEqnInfo</name>
      <anchorfile>classsnl__fei_1_1PointBlockMap.html</anchorfile>
      <anchor>a76c2c77eecd4eee743a3f0b776db3a8b</anchor>
      <arglist>(int blkEqn, int &amp;ptEqn, int &amp;blkSize)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getPtEqnInfo</name>
      <anchorfile>classsnl__fei_1_1PointBlockMap.html</anchorfile>
      <anchor>a82827ccf5a444367aeeccfd2a8e81854</anchor>
      <arglist>(int ptEqn, int &amp;blkEqn, int &amp;blkOffset)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getBlkEqnOffset</name>
      <anchorfile>classsnl__fei_1_1PointBlockMap.html</anchorfile>
      <anchor>ae17f2df89d68d3ad20df5ddb2aa62966</anchor>
      <arglist>(int blkEqn, int ptEqn)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isExactlyBlkEqn</name>
      <anchorfile>classsnl__fei_1_1PointBlockMap.html</anchorfile>
      <anchor>ac828381f7451ef1e6812e5ef93faf753</anchor>
      <arglist>(int ptEqn)</arglist>
    </member>
    <member kind="function">
      <type>std::map&lt; int, int &gt; *</type>
      <name>getPtEqns</name>
      <anchorfile>classsnl__fei_1_1PointBlockMap.html</anchorfile>
      <anchor>a8f65b27caa0b8a465d2b51f7379dc6f7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>std::map&lt; int, std::pair&lt; int, int &gt; &gt; *</type>
      <name>getBlkEqns</name>
      <anchorfile>classsnl__fei_1_1PointBlockMap.html</anchorfile>
      <anchor>a0f034baeef680bb44d757d5ed2abfb1c</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ProcEqns</name>
    <filename>classProcEqns.html</filename>
    <member kind="function">
      <type></type>
      <name>ProcEqns</name>
      <anchorfile>classProcEqns.html</anchorfile>
      <anchor>a2af29b33ffcfc31f6d2dbabbd3f3d026</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~ProcEqns</name>
      <anchorfile>classProcEqns.html</anchorfile>
      <anchor>a701ee29904c8fb4c111759ac0f2cb5fc</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>ProcEqns *</type>
      <name>deepCopy</name>
      <anchorfile>classProcEqns.html</anchorfile>
      <anchor>a4b4eb6963656863285f065af8fc1f2c6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>size_t</type>
      <name>getNumProcs</name>
      <anchorfile>classProcEqns.html</anchorfile>
      <anchor>a4d5ce97b8ec87c56484dc009609e7282</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>std::vector&lt; int &gt; &amp;</type>
      <name>procsPtr</name>
      <anchorfile>classProcEqns.html</anchorfile>
      <anchor>ab747ccb101a118c6007fbcfc8fa0c646</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>std::vector&lt; int &gt; &amp;</type>
      <name>eqnsPerProcPtr</name>
      <anchorfile>classProcEqns.html</anchorfile>
      <anchor>a1529e8f050a54fde710c53fcf03ece9e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>std::vector&lt; std::vector&lt; int &gt; * &gt; &amp;</type>
      <name>procEqnNumbersPtr</name>
      <anchorfile>classProcEqns.html</anchorfile>
      <anchor>a73f6488e3fa5009a1a39e9be14fbfddf</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>std::vector&lt; std::vector&lt; int &gt; * &gt; &amp;</type>
      <name>procEqnLengthsPtr</name>
      <anchorfile>classProcEqns.html</anchorfile>
      <anchor>ab7be39c397c86da2bd1660b1197642a8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>addEqn</name>
      <anchorfile>classProcEqns.html</anchorfile>
      <anchor>a998ef05cbc2079526703a4505f0ebed4</anchor>
      <arglist>(int eqnNumber, int proc)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>addEqn</name>
      <anchorfile>classProcEqns.html</anchorfile>
      <anchor>aa029778191d433952bd99f8f4a571dfb</anchor>
      <arglist>(int eqnNumber, int eqnLength, int proc)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setProcEqnLengths</name>
      <anchorfile>classProcEqns.html</anchorfile>
      <anchor>adec307d03ec42f1b51ef7d20c4aee2dc</anchor>
      <arglist>(int *eqnNumbers, int *eqnLengths, int len)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>snl_fei::RaggedTable</name>
    <filename>classsnl__fei_1_1RaggedTable.html</filename>
    <templarg>MAP_TYPE</templarg>
    <templarg>SET_TYPE</templarg>
    <base>fei::IndexTable</base>
    <member kind="typedef">
      <type>MAP_TYPE</type>
      <name>map_type</name>
      <anchorfile>classsnl__fei_1_1RaggedTable.html</anchorfile>
      <anchor>a4228710981456c7aec6cab67be485d81</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>SET_TYPE</type>
      <name>row_type</name>
      <anchorfile>classsnl__fei_1_1RaggedTable.html</anchorfile>
      <anchor>a45e95ca8b35adf4210ce55ac5711c478</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>MAP_TYPE::iterator</type>
      <name>iterator</name>
      <anchorfile>classsnl__fei_1_1RaggedTable.html</anchorfile>
      <anchor>a0b2a1931440decac17522c43207d0318</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>RaggedTable</name>
      <anchorfile>classsnl__fei_1_1RaggedTable.html</anchorfile>
      <anchor>a3d6fea75c98a4139d474abbc2aece22d</anchor>
      <arglist>(int firstKey, int lastKey)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>RaggedTable</name>
      <anchorfile>classsnl__fei_1_1RaggedTable.html</anchorfile>
      <anchor>ac754040553e61ec10a861b5ace3322c5</anchor>
      <arglist>(const RaggedTable&lt; MAP_TYPE, SET_TYPE &gt; &amp;src)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>addDiagonals</name>
      <anchorfile>classsnl__fei_1_1RaggedTable.html</anchorfile>
      <anchor>aeca77ce37787b2d5d2df0d3531f6f495</anchor>
      <arglist>(int numIndices, const int *indices)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>addIndices</name>
      <anchorfile>classsnl__fei_1_1RaggedTable.html</anchorfile>
      <anchor>a91daf6173422f1e15cc6a4ccf9a7d2b2</anchor>
      <arglist>(int row, int numIndices, const int *indices)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>addIndices</name>
      <anchorfile>classsnl__fei_1_1RaggedTable.html</anchorfile>
      <anchor>a76f7010d46f0b0aa017d8afad65dd010</anchor>
      <arglist>(int numRows, const int *rows, int numIndices, const int *indices)</arglist>
    </member>
    <member kind="function">
      <type>MAP_TYPE &amp;</type>
      <name>getMap</name>
      <anchorfile>classsnl__fei_1_1RaggedTable.html</anchorfile>
      <anchor>abe9648fc97d60757439662fffa8c9831</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const MAP_TYPE &amp;</type>
      <name>getMap</name>
      <anchorfile>classsnl__fei_1_1RaggedTable.html</anchorfile>
      <anchor>a73ff822850645bea82078ca46f169b83</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>SET_TYPE *</type>
      <name>getRow</name>
      <anchorfile>classsnl__fei_1_1RaggedTable.html</anchorfile>
      <anchor>a2043386de3ac47c759af73f93a4b3c8c</anchor>
      <arglist>(int row)</arglist>
    </member>
    <member kind="function">
      <type>iterator</type>
      <name>begin</name>
      <anchorfile>classsnl__fei_1_1RaggedTable.html</anchorfile>
      <anchor>a36ecb778fa5d51ba4382d7da02ffa60c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>iterator</type>
      <name>end</name>
      <anchorfile>classsnl__fei_1_1RaggedTable.html</anchorfile>
      <anchor>ae5b5034f767afafd459f902c8cb4d757</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>equal</name>
      <anchorfile>classsnl__fei_1_1RaggedTable.html</anchorfile>
      <anchor>a57052314effff2bbc2653fb223a409a9</anchor>
      <arglist>(const RaggedTable&lt; MAP_TYPE, SET_TYPE &gt; &amp;rhs, bool quiet=true) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>snl_fei::RaggedTable&lt; MapContig&lt; fei::ctg_set&lt; int &gt; * &gt;, fei::ctg_set&lt; int &gt; &gt;</name>
    <filename>classsnl__fei_1_1RaggedTable_3_01MapContig_3_01fei_1_1ctg__set_3_01int_01_4_01_5_01_4_00_01fei_1_1ctg__set_3_01int_01_4_01_4.html</filename>
    <base>fei::IndexTable</base>
    <member kind="function">
      <type></type>
      <name>RaggedTable</name>
      <anchorfile>classsnl__fei_1_1RaggedTable_3_01MapContig_3_01fei_1_1ctg__set_3_01int_01_4_01_5_01_4_00_01fei_1_1ctg__set_3_01int_01_4_01_4.html</anchorfile>
      <anchor>ad1ef5b4a92de7131fed92efb5c76adfb</anchor>
      <arglist>(int firstKey, int lastKey)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>addDiagonals</name>
      <anchorfile>classsnl__fei_1_1RaggedTable_3_01MapContig_3_01fei_1_1ctg__set_3_01int_01_4_01_5_01_4_00_01fei_1_1ctg__set_3_01int_01_4_01_4.html</anchorfile>
      <anchor>ac913e3427bddede9cd42362d56418747</anchor>
      <arglist>(int numIndices, const int *indices)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>addIndices</name>
      <anchorfile>classsnl__fei_1_1RaggedTable_3_01MapContig_3_01fei_1_1ctg__set_3_01int_01_4_01_5_01_4_00_01fei_1_1ctg__set_3_01int_01_4_01_4.html</anchorfile>
      <anchor>a98fc5fbbed24c7ff17f0bd190cda2bb4</anchor>
      <arglist>(int row, int numIndices, const int *indices)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>addIndices</name>
      <anchorfile>classsnl__fei_1_1RaggedTable_3_01MapContig_3_01fei_1_1ctg__set_3_01int_01_4_01_5_01_4_00_01fei_1_1ctg__set_3_01int_01_4_01_4.html</anchorfile>
      <anchor>ae8f967be8bd53894d0fd51046439aaca</anchor>
      <arglist>(int numRows, const int *rows, int numIndices, const int *indices)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>fei::Record</name>
    <filename>classfei_1_1Record.html</filename>
    <templarg>GlobalIDType</templarg>
    <member kind="function">
      <type></type>
      <name>Record</name>
      <anchorfile>classfei_1_1Record.html</anchorfile>
      <anchor>a5b7295a573bb0300b12c8d4eba1753cd</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Record</name>
      <anchorfile>classfei_1_1Record.html</anchorfile>
      <anchor>a8563411222bb5246f9ed6ff1bb27817d</anchor>
      <arglist>(const Record&lt; GlobalIDType &gt; &amp;src)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~Record</name>
      <anchorfile>classfei_1_1Record.html</anchorfile>
      <anchor>aa272e4fab597e87fdab24a38c8a04c6c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setID</name>
      <anchorfile>classfei_1_1Record.html</anchorfile>
      <anchor>a11de1e8859854a8d24abf6a2eb1cd918</anchor>
      <arglist>(const GlobalIDType &amp;ID)</arglist>
    </member>
    <member kind="function">
      <type>GlobalIDType</type>
      <name>getID</name>
      <anchorfile>classfei_1_1Record.html</anchorfile>
      <anchor>a5489189922015575cd699db8f9a21ffa</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setNumber</name>
      <anchorfile>classfei_1_1Record.html</anchorfile>
      <anchor>a64c85d9fd7688c75428f3b271eb39bd1</anchor>
      <arglist>(const GlobalIDType &amp;num)</arglist>
    </member>
    <member kind="function">
      <type>GlobalIDType</type>
      <name>getNumber</name>
      <anchorfile>classfei_1_1Record.html</anchorfile>
      <anchor>a142be47c684c05d3884d02663d3181c4</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator==</name>
      <anchorfile>classfei_1_1Record.html</anchorfile>
      <anchor>a2ba476340dcc10e0c60f0d876c8cb1ab</anchor>
      <arglist>(const Record&lt; GlobalIDType &gt; &amp;rcd) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator!=</name>
      <anchorfile>classfei_1_1Record.html</anchorfile>
      <anchor>ad17268211a3257b663c809f46ff65e11</anchor>
      <arglist>(const Record&lt; GlobalIDType &gt; &amp;rcd) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator&lt;</name>
      <anchorfile>classfei_1_1Record.html</anchorfile>
      <anchor>a7ad664168cd99386c47fde67b9a294c7</anchor>
      <arglist>(const Record&lt; GlobalIDType &gt; &amp;rcd) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator&gt;</name>
      <anchorfile>classfei_1_1Record.html</anchorfile>
      <anchor>a6f4e6c2f6b432483111e9ecc2016e9eb</anchor>
      <arglist>(const Record&lt; GlobalIDType &gt; &amp;rcd) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setOwnerProc</name>
      <anchorfile>classfei_1_1Record.html</anchorfile>
      <anchor>a915e71619ce1a6693b96e6f3625f7cea</anchor>
      <arglist>(int owner)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getOwnerProc</name>
      <anchorfile>classfei_1_1Record.html</anchorfile>
      <anchor>abd8b382dc431cf0a4ab886739ecd155c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setFieldMask</name>
      <anchorfile>classfei_1_1Record.html</anchorfile>
      <anchor>ab0594656dd2c0de90b975aa776dd5ba1</anchor>
      <arglist>(fei::FieldMask *fm)</arglist>
    </member>
    <member kind="function">
      <type>fei::FieldMask *</type>
      <name>getFieldMask</name>
      <anchorfile>classfei_1_1Record.html</anchorfile>
      <anchor>a6bab62e367fadeb8a7fad8baba990bf2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const fei::FieldMask *</type>
      <name>getFieldMask</name>
      <anchorfile>classfei_1_1Record.html</anchorfile>
      <anchor>aabe7ce9d788ead5d4124393d3f896b07</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setOffsetIntoEqnNumbers</name>
      <anchorfile>classfei_1_1Record.html</anchorfile>
      <anchor>a694346e48b780a7df46d83ade67780e9</anchor>
      <arglist>(int offset)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getOffsetIntoEqnNumbers</name>
      <anchorfile>classfei_1_1Record.html</anchorfile>
      <anchor>ac8efa22d6d082a4c9de74d82d5616db9</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>isInLocalSubdomain_</name>
      <anchorfile>classfei_1_1Record.html</anchorfile>
      <anchor>a603b718a2cb6b2868778160576901f84</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>fei::Record_Operator</name>
    <filename>classfei_1_1Record__Operator.html</filename>
    <templarg>GlobalIDType</templarg>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~Record_Operator</name>
      <anchorfile>classfei_1_1Record__Operator.html</anchorfile>
      <anchor>a8962a9218e20414464fb03cd466e6d65</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>operator()</name>
      <anchorfile>classfei_1_1Record__Operator.html</anchorfile>
      <anchor>a2e3dcc90246f2cf4c3d69685495ff23a</anchor>
      <arglist>(Record&lt; GlobalIDType &gt; &amp;record)=0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Record_Operator&lt; int &gt;</name>
    <filename>classfei_1_1Record__Operator.html</filename>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~Record_Operator</name>
      <anchorfile>classfei_1_1Record__Operator.html</anchorfile>
      <anchor>a8962a9218e20414464fb03cd466e6d65</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>operator()</name>
      <anchorfile>classfei_1_1Record__Operator.html</anchorfile>
      <anchor>a2e3dcc90246f2cf4c3d69685495ff23a</anchor>
      <arglist>(Record&lt; int &gt; &amp;record)=0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>snl_fei::RecordCollection</name>
    <filename>classsnl__fei_1_1RecordCollection.html</filename>
    <member kind="function">
      <type></type>
      <name>RecordCollection</name>
      <anchorfile>classsnl__fei_1_1RecordCollection.html</anchorfile>
      <anchor>ab9aa6f9b8a2a07fcb07e86972e281ee3</anchor>
      <arglist>(int localProc)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>RecordCollection</name>
      <anchorfile>classsnl__fei_1_1RecordCollection.html</anchorfile>
      <anchor>a3d0a7db711a4e41ab801fe07891b90ad</anchor>
      <arglist>(const RecordCollection &amp;src)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~RecordCollection</name>
      <anchorfile>classsnl__fei_1_1RecordCollection.html</anchorfile>
      <anchor>ab8c211acd05325498912bf9b36a3d3c4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initRecords</name>
      <anchorfile>classsnl__fei_1_1RecordCollection.html</anchorfile>
      <anchor>a4b47945bd3064e9a0b8b8967c503d64d</anchor>
      <arglist>(int numIDs, const int *IDs, std::vector&lt; fei::FieldMask * &gt; &amp;fieldMasks, int *recordLocalIDs=NULL)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initRecords</name>
      <anchorfile>classsnl__fei_1_1RecordCollection.html</anchorfile>
      <anchor>ab51f12bba646414d1d4a90d0e5d31f8c</anchor>
      <arglist>(int fieldID, int fieldSize, int numIDs, const int *IDs, std::vector&lt; fei::FieldMask * &gt; &amp;fieldMasks, int *recordLocalIDs=NULL)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setOwners_lowestSharing</name>
      <anchorfile>classsnl__fei_1_1RecordCollection.html</anchorfile>
      <anchor>a4bf736e3287829760405e993b4c5d0b9</anchor>
      <arglist>(fei::SharedIDs&lt; int &gt; &amp;sharedIDs)</arglist>
    </member>
    <member kind="function">
      <type>size_t</type>
      <name>getNumRecords</name>
      <anchorfile>classsnl__fei_1_1RecordCollection.html</anchorfile>
      <anchor>a89f94c7524ea55de0bd316f242bcd93f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>std::map&lt; int, int &gt; &amp;</type>
      <name>getGlobalToLocalMap</name>
      <anchorfile>classsnl__fei_1_1RecordCollection.html</anchorfile>
      <anchor>a4dd3b47bb508d97d5fee05b9cae1f302</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>std::vector&lt; fei::Record&lt; int &gt; &gt; &amp;</type>
      <name>getRecords</name>
      <anchorfile>classsnl__fei_1_1RecordCollection.html</anchorfile>
      <anchor>a58c862697fd6494384f99f905ad82817</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const std::vector&lt; fei::Record&lt; int &gt; &gt; &amp;</type>
      <name>getRecords</name>
      <anchorfile>classsnl__fei_1_1RecordCollection.html</anchorfile>
      <anchor>a9392c325d1188abd4d964ed5b8e3a8d4</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>fei::Record&lt; int &gt; *</type>
      <name>getRecordWithID</name>
      <anchorfile>classsnl__fei_1_1RecordCollection.html</anchorfile>
      <anchor>adc592afbf4bf846512aa357eda9a9ee2</anchor>
      <arglist>(int ID)</arglist>
    </member>
    <member kind="function">
      <type>const fei::Record&lt; int &gt; *</type>
      <name>getRecordWithID</name>
      <anchorfile>classsnl__fei_1_1RecordCollection.html</anchorfile>
      <anchor>a43a8e18a5dbf2d4ee061a47b896f6563</anchor>
      <arglist>(int ID) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getGlobalIndex</name>
      <anchorfile>classsnl__fei_1_1RecordCollection.html</anchorfile>
      <anchor>a155542e86b8a1e1631a879fabdd53209</anchor>
      <arglist>(int ID, int fieldID, int fieldSize, int fieldOffset, int whichComponentOfField, const int *eqnNumbers)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getGlobalIndexLocalID</name>
      <anchorfile>classsnl__fei_1_1RecordCollection.html</anchorfile>
      <anchor>a64104d92efd31c337e8e04331b3dfa7c</anchor>
      <arglist>(int localID, int fieldID, int fieldSize, int fieldOffset, int whichComponentOfField, const int *eqnNumbers)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getGlobalBlkIndex</name>
      <anchorfile>classsnl__fei_1_1RecordCollection.html</anchorfile>
      <anchor>acfa381deb599e1840511b00e4b4d3340</anchor>
      <arglist>(int ID, int &amp;globalBlkIndex)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setDebugOutput</name>
      <anchorfile>classsnl__fei_1_1RecordCollection.html</anchorfile>
      <anchor>af65e3ee2d3584fd8d681b3a730e11cd5</anchor>
      <arglist>(FEI_OSTREAM *dbgOut)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>snl_fei::RecordMsgHandler</name>
    <filename>classsnl__fei_1_1RecordMsgHandler.html</filename>
    <base>MessageHandler&lt; int &gt;</base>
    <member kind="function">
      <type></type>
      <name>RecordMsgHandler</name>
      <anchorfile>classsnl__fei_1_1RecordMsgHandler.html</anchorfile>
      <anchor>af63194cdbbaaf734e7adcd9287abcd1b</anchor>
      <arglist>(int localProc, RecordCollection *recordCollection, snl_fei::PointBlockMap &amp;ptBlkMap, std::vector&lt; fei::FieldMask * &gt; &amp;fieldMasks, std::vector&lt; int &gt; &amp;eqnNumbers)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~RecordMsgHandler</name>
      <anchorfile>classsnl__fei_1_1RecordMsgHandler.html</anchorfile>
      <anchor>ac29fd6f5dcf03b1b98a2396a6cba1fec</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>std::vector&lt; int &gt; &amp;</type>
      <name>getSendProcs</name>
      <anchorfile>classsnl__fei_1_1RecordMsgHandler.html</anchorfile>
      <anchor>af725ce60378277c655a7bd9f5641d88f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>std::vector&lt; int &gt; &amp;</type>
      <name>getRecvProcs</name>
      <anchorfile>classsnl__fei_1_1RecordMsgHandler.html</anchorfile>
      <anchor>a0f954e53012d1e9c0422d772fa3418ef</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getSendMessageLength</name>
      <anchorfile>classsnl__fei_1_1RecordMsgHandler.html</anchorfile>
      <anchor>a536a033e46ff0cf37c093a088c5f3a07</anchor>
      <arglist>(int destProc, int &amp;messageLength)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getSendMessage</name>
      <anchorfile>classsnl__fei_1_1RecordMsgHandler.html</anchorfile>
      <anchor>a77186508e24e442cc56f4acf386a17a9</anchor>
      <arglist>(int destProc, std::vector&lt; int &gt; &amp;message)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>processRecvMessage</name>
      <anchorfile>classsnl__fei_1_1RecordMsgHandler.html</anchorfile>
      <anchor>a90e463e9dd2b3d4e719cb47244676183</anchor>
      <arglist>(int srcProc, std::vector&lt; int &gt; &amp;message)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setTask</name>
      <anchorfile>classsnl__fei_1_1RecordMsgHandler.html</anchorfile>
      <anchor>a931dd8efcb7feb39002053e67a2bf2b0</anchor>
      <arglist>(int task)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setSendPattern</name>
      <anchorfile>classsnl__fei_1_1RecordMsgHandler.html</anchorfile>
      <anchor>a86efe203f5709a73dd0b0611e90ca7e0</anchor>
      <arglist>(fei::comm_map *pattern)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setRecvPattern</name>
      <anchorfile>classsnl__fei_1_1RecordMsgHandler.html</anchorfile>
      <anchor>ad7bf8e30216c98fc383d4f66b60bd234</anchor>
      <arglist>(fei::comm_map *pattern)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>fei::ReverseMapper</name>
    <filename>classfei_1_1ReverseMapper.html</filename>
    <member kind="function">
      <type></type>
      <name>ReverseMapper</name>
      <anchorfile>classfei_1_1ReverseMapper.html</anchorfile>
      <anchor>a064e862fa743adb6bc82c4a46e46d82c</anchor>
      <arglist>(const VectorSpace &amp;vspace)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~ReverseMapper</name>
      <anchorfile>classfei_1_1ReverseMapper.html</anchorfile>
      <anchor>a6aa619398558d50c0b8c5829e6254f95</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>snl_fei::SetTraits</name>
    <filename>structsnl__fei_1_1SetTraits.html</filename>
    <templarg></templarg>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>insert</name>
      <anchorfile>structsnl__fei_1_1SetTraits.html</anchorfile>
      <anchor>a736f1ca47a208eb45e598534fb8b1561</anchor>
      <arglist>(SET_TYPE *set_obj, typename SET_TYPE::key_type item)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>snl_fei::SetTraits&lt; fei::ctg_set&lt; int &gt; &gt;</name>
    <filename>structsnl__fei_1_1SetTraits_3_01fei_1_1ctg__set_3_01int_01_4_01_4.html</filename>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>insert</name>
      <anchorfile>structsnl__fei_1_1SetTraits_3_01fei_1_1ctg__set_3_01int_01_4_01_4.html</anchorfile>
      <anchor>aa5cfcb6239a05eb8f224a12671141ff0</anchor>
      <arglist>(fei::ctg_set&lt; int &gt; *set_obj, int item)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>fei::SharedIDs</name>
    <filename>classfei_1_1SharedIDs.html</filename>
    <templarg>T</templarg>
    <member kind="typedef">
      <type>std::map&lt; T, std::set&lt; int &gt; &gt;</type>
      <name>map_type</name>
      <anchorfile>classfei_1_1SharedIDs.html</anchorfile>
      <anchor>a6ea80ec5cb10af48881f9d32bc707430</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SharedIDs</name>
      <anchorfile>classfei_1_1SharedIDs.html</anchorfile>
      <anchor>a45d63c3a8aedfddd6235d333f6ba6c06</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SharedIDs</name>
      <anchorfile>classfei_1_1SharedIDs.html</anchorfile>
      <anchor>ab6b4aefac3d545b4637fd6df7691d4f3</anchor>
      <arglist>(const SharedIDs&lt; T &gt; &amp;src)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~SharedIDs</name>
      <anchorfile>classfei_1_1SharedIDs.html</anchorfile>
      <anchor>a95d73fa2531031553582977e2ab529c1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>addSharedID</name>
      <anchorfile>classfei_1_1SharedIDs.html</anchorfile>
      <anchor>a7898735fc7073efaf33e8d324d302102</anchor>
      <arglist>(const T &amp;ID, size_t numSharingProcs, const int *sharingProcs)</arglist>
    </member>
    <member kind="function">
      <type>map_type &amp;</type>
      <name>getSharedIDs</name>
      <anchorfile>classfei_1_1SharedIDs.html</anchorfile>
      <anchor>a87d5fa123bab9008861bca6ea1c32b65</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const map_type &amp;</type>
      <name>getSharedIDs</name>
      <anchorfile>classfei_1_1SharedIDs.html</anchorfile>
      <anchor>a9751100219b00ecec0edd1cbf755d73e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>std::vector&lt; int &gt; &amp;</type>
      <name>getOwningProcs</name>
      <anchorfile>classfei_1_1SharedIDs.html</anchorfile>
      <anchor>a598b4300717049d9c31966034d5bffeb</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const std::vector&lt; int &gt; &amp;</type>
      <name>getOwningProcs</name>
      <anchorfile>classfei_1_1SharedIDs.html</anchorfile>
      <anchor>aaa70a5db068e27e2a0624ded64aa6b9a</anchor>
      <arglist>() const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>SharedIDs&lt; int &gt;</name>
    <filename>classfei_1_1SharedIDs.html</filename>
    <member kind="typedef">
      <type>std::map&lt; int, std::set&lt; int &gt; &gt;</type>
      <name>map_type</name>
      <anchorfile>classfei_1_1SharedIDs.html</anchorfile>
      <anchor>a6ea80ec5cb10af48881f9d32bc707430</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SharedIDs</name>
      <anchorfile>classfei_1_1SharedIDs.html</anchorfile>
      <anchor>a45d63c3a8aedfddd6235d333f6ba6c06</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SharedIDs</name>
      <anchorfile>classfei_1_1SharedIDs.html</anchorfile>
      <anchor>ab6b4aefac3d545b4637fd6df7691d4f3</anchor>
      <arglist>(const SharedIDs&lt; int &gt; &amp;src)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~SharedIDs</name>
      <anchorfile>classfei_1_1SharedIDs.html</anchorfile>
      <anchor>a95d73fa2531031553582977e2ab529c1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>addSharedID</name>
      <anchorfile>classfei_1_1SharedIDs.html</anchorfile>
      <anchor>a7898735fc7073efaf33e8d324d302102</anchor>
      <arglist>(const int &amp;ID, size_t numSharingProcs, const int *sharingProcs)</arglist>
    </member>
    <member kind="function">
      <type>map_type &amp;</type>
      <name>getSharedIDs</name>
      <anchorfile>classfei_1_1SharedIDs.html</anchorfile>
      <anchor>a87d5fa123bab9008861bca6ea1c32b65</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const map_type &amp;</type>
      <name>getSharedIDs</name>
      <anchorfile>classfei_1_1SharedIDs.html</anchorfile>
      <anchor>a9751100219b00ecec0edd1cbf755d73e</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>std::vector&lt; int &gt; &amp;</type>
      <name>getOwningProcs</name>
      <anchorfile>classfei_1_1SharedIDs.html</anchorfile>
      <anchor>a598b4300717049d9c31966034d5bffeb</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const std::vector&lt; int &gt; &amp;</type>
      <name>getOwningProcs</name>
      <anchorfile>classfei_1_1SharedIDs.html</anchorfile>
      <anchor>aaa70a5db068e27e2a0624ded64aa6b9a</anchor>
      <arglist>() const</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>fei::SharedPtr</name>
    <filename>classfei_1_1SharedPtr.html</filename>
    <templarg>T</templarg>
    <member kind="typedef">
      <type>T</type>
      <name>element_type</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>ac4770c63a5fb9297d0d0414afe79117c</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SharedPtr</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>afad2a2441a6f7907dd4d249dfd813398</anchor>
      <arglist>(T *p)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~SharedPtr</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>ac6c248f87712f6afafa28fcbcdb53987</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SharedPtr</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>aa04f35878be5d09a9e7212992936a16b</anchor>
      <arglist>(const SharedPtr&lt; Y &gt; &amp;x)</arglist>
    </member>
    <member kind="function">
      <type>SharedPtr &amp;</type>
      <name>operator=</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a3345b70111b88d517dbfe6991d197a89</anchor>
      <arglist>(const SharedPtr&lt; Y &gt; &amp;x)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SharedPtr</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a9874d9dc7e02ff82a87a5ee45b2ea74d</anchor>
      <arglist>(const SharedPtr &amp;x)</arglist>
    </member>
    <member kind="function">
      <type>SharedPtr &amp;</type>
      <name>operator=</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a5370427758b9147ab6cc347b12b011bf</anchor>
      <arglist>(const SharedPtr &amp;x)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>reset</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a0cce56dc2d636ba354b63d30061fa072</anchor>
      <arglist>(T *p=0)</arglist>
    </member>
    <member kind="function">
      <type>T &amp;</type>
      <name>operator*</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>aa65e5c5fb01b8b3c6e820302b1ca5424</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>T *</type>
      <name>operator-&gt;</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a1d18d5e137d8a184d5f1bdc1913d10a8</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>T *</type>
      <name>get</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a0296a552885744dbf7c81e29be463e28</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>long</type>
      <name>use_count</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a26d79923e382b42cb2a8fab468cad7ea</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>unique</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a653b3e338f9a87623c875b51ff932cc8</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>share</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>ad27873719f16e17c9057355130079499</anchor>
      <arglist>(T *xpointer, long *xcount)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>dispose</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>ac25cf9cbd9843804de943be3bb2670df</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>SharedPtr&lt; Aztec_BlockMap &gt;</name>
    <filename>classfei_1_1SharedPtr.html</filename>
    <member kind="typedef">
      <type>Aztec_BlockMap</type>
      <name>element_type</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>ac4770c63a5fb9297d0d0414afe79117c</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SharedPtr</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>afad2a2441a6f7907dd4d249dfd813398</anchor>
      <arglist>(Aztec_BlockMap *p)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SharedPtr</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>aa04f35878be5d09a9e7212992936a16b</anchor>
      <arglist>(const SharedPtr&lt; Y &gt; &amp;x)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SharedPtr</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a9874d9dc7e02ff82a87a5ee45b2ea74d</anchor>
      <arglist>(const SharedPtr &amp;x)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~SharedPtr</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>ac6c248f87712f6afafa28fcbcdb53987</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>SharedPtr &amp;</type>
      <name>operator=</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a3345b70111b88d517dbfe6991d197a89</anchor>
      <arglist>(const SharedPtr&lt; Y &gt; &amp;x)</arglist>
    </member>
    <member kind="function">
      <type>SharedPtr &amp;</type>
      <name>operator=</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a5370427758b9147ab6cc347b12b011bf</anchor>
      <arglist>(const SharedPtr &amp;x)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>reset</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a0cce56dc2d636ba354b63d30061fa072</anchor>
      <arglist>(Aztec_BlockMap *p=0)</arglist>
    </member>
    <member kind="function">
      <type>Aztec_BlockMap &amp;</type>
      <name>operator*</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>aa65e5c5fb01b8b3c6e820302b1ca5424</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>Aztec_BlockMap *</type>
      <name>operator-&gt;</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a1d18d5e137d8a184d5f1bdc1913d10a8</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>Aztec_BlockMap *</type>
      <name>get</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a0296a552885744dbf7c81e29be463e28</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>long</type>
      <name>use_count</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a26d79923e382b42cb2a8fab468cad7ea</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>unique</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a653b3e338f9a87623c875b51ff932cc8</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>share</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>ad27873719f16e17c9057355130079499</anchor>
      <arglist>(Aztec_BlockMap *xpointer, long *xcount)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>dispose</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>ac25cf9cbd9843804de943be3bb2670df</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>SharedPtr&lt; Aztec_Map &gt;</name>
    <filename>classfei_1_1SharedPtr.html</filename>
    <member kind="typedef">
      <type>Aztec_Map</type>
      <name>element_type</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>ac4770c63a5fb9297d0d0414afe79117c</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SharedPtr</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>afad2a2441a6f7907dd4d249dfd813398</anchor>
      <arglist>(Aztec_Map *p)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SharedPtr</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>aa04f35878be5d09a9e7212992936a16b</anchor>
      <arglist>(const SharedPtr&lt; Y &gt; &amp;x)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SharedPtr</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a9874d9dc7e02ff82a87a5ee45b2ea74d</anchor>
      <arglist>(const SharedPtr &amp;x)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~SharedPtr</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>ac6c248f87712f6afafa28fcbcdb53987</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>SharedPtr &amp;</type>
      <name>operator=</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a3345b70111b88d517dbfe6991d197a89</anchor>
      <arglist>(const SharedPtr&lt; Y &gt; &amp;x)</arglist>
    </member>
    <member kind="function">
      <type>SharedPtr &amp;</type>
      <name>operator=</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a5370427758b9147ab6cc347b12b011bf</anchor>
      <arglist>(const SharedPtr &amp;x)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>reset</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a0cce56dc2d636ba354b63d30061fa072</anchor>
      <arglist>(Aztec_Map *p=0)</arglist>
    </member>
    <member kind="function">
      <type>Aztec_Map &amp;</type>
      <name>operator*</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>aa65e5c5fb01b8b3c6e820302b1ca5424</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>Aztec_Map *</type>
      <name>operator-&gt;</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a1d18d5e137d8a184d5f1bdc1913d10a8</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>Aztec_Map *</type>
      <name>get</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a0296a552885744dbf7c81e29be463e28</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>long</type>
      <name>use_count</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a26d79923e382b42cb2a8fab468cad7ea</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>unique</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a653b3e338f9a87623c875b51ff932cc8</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>share</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>ad27873719f16e17c9057355130079499</anchor>
      <arglist>(Aztec_Map *xpointer, long *xcount)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>dispose</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>ac25cf9cbd9843804de943be3bb2670df</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>SharedPtr&lt; DataReader &gt;</name>
    <filename>classfei_1_1SharedPtr.html</filename>
    <member kind="typedef">
      <type>DataReader</type>
      <name>element_type</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>ac4770c63a5fb9297d0d0414afe79117c</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SharedPtr</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>afad2a2441a6f7907dd4d249dfd813398</anchor>
      <arglist>(DataReader *p)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SharedPtr</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>aa04f35878be5d09a9e7212992936a16b</anchor>
      <arglist>(const SharedPtr&lt; Y &gt; &amp;x)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SharedPtr</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a9874d9dc7e02ff82a87a5ee45b2ea74d</anchor>
      <arglist>(const SharedPtr &amp;x)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~SharedPtr</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>ac6c248f87712f6afafa28fcbcdb53987</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>SharedPtr &amp;</type>
      <name>operator=</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a3345b70111b88d517dbfe6991d197a89</anchor>
      <arglist>(const SharedPtr&lt; Y &gt; &amp;x)</arglist>
    </member>
    <member kind="function">
      <type>SharedPtr &amp;</type>
      <name>operator=</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a5370427758b9147ab6cc347b12b011bf</anchor>
      <arglist>(const SharedPtr &amp;x)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>reset</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a0cce56dc2d636ba354b63d30061fa072</anchor>
      <arglist>(DataReader *p=0)</arglist>
    </member>
    <member kind="function">
      <type>DataReader &amp;</type>
      <name>operator*</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>aa65e5c5fb01b8b3c6e820302b1ca5424</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>DataReader *</type>
      <name>operator-&gt;</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a1d18d5e137d8a184d5f1bdc1913d10a8</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>DataReader *</type>
      <name>get</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a0296a552885744dbf7c81e29be463e28</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>long</type>
      <name>use_count</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a26d79923e382b42cb2a8fab468cad7ea</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>unique</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a653b3e338f9a87623c875b51ff932cc8</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>share</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>ad27873719f16e17c9057355130079499</anchor>
      <arglist>(DataReader *xpointer, long *xcount)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>dispose</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>ac25cf9cbd9843804de943be3bb2670df</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>SharedPtr&lt; Epetra_Comm &gt;</name>
    <filename>classfei_1_1SharedPtr.html</filename>
    <member kind="typedef">
      <type>Epetra_Comm</type>
      <name>element_type</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>ac4770c63a5fb9297d0d0414afe79117c</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SharedPtr</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>afad2a2441a6f7907dd4d249dfd813398</anchor>
      <arglist>(Epetra_Comm *p)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SharedPtr</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>aa04f35878be5d09a9e7212992936a16b</anchor>
      <arglist>(const SharedPtr&lt; Y &gt; &amp;x)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SharedPtr</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a9874d9dc7e02ff82a87a5ee45b2ea74d</anchor>
      <arglist>(const SharedPtr &amp;x)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~SharedPtr</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>ac6c248f87712f6afafa28fcbcdb53987</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>SharedPtr &amp;</type>
      <name>operator=</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a3345b70111b88d517dbfe6991d197a89</anchor>
      <arglist>(const SharedPtr&lt; Y &gt; &amp;x)</arglist>
    </member>
    <member kind="function">
      <type>SharedPtr &amp;</type>
      <name>operator=</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a5370427758b9147ab6cc347b12b011bf</anchor>
      <arglist>(const SharedPtr &amp;x)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>reset</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a0cce56dc2d636ba354b63d30061fa072</anchor>
      <arglist>(Epetra_Comm *p=0)</arglist>
    </member>
    <member kind="function">
      <type>Epetra_Comm &amp;</type>
      <name>operator*</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>aa65e5c5fb01b8b3c6e820302b1ca5424</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>Epetra_Comm *</type>
      <name>operator-&gt;</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a1d18d5e137d8a184d5f1bdc1913d10a8</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>Epetra_Comm *</type>
      <name>get</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a0296a552885744dbf7c81e29be463e28</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>long</type>
      <name>use_count</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a26d79923e382b42cb2a8fab468cad7ea</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>unique</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a653b3e338f9a87623c875b51ff932cc8</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>share</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>ad27873719f16e17c9057355130079499</anchor>
      <arglist>(Epetra_Comm *xpointer, long *xcount)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>dispose</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>ac25cf9cbd9843804de943be3bb2670df</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>SharedPtr&lt; Epetra_CrsGraph &gt;</name>
    <filename>classfei_1_1SharedPtr.html</filename>
    <member kind="typedef">
      <type>Epetra_CrsGraph</type>
      <name>element_type</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>ac4770c63a5fb9297d0d0414afe79117c</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SharedPtr</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>afad2a2441a6f7907dd4d249dfd813398</anchor>
      <arglist>(Epetra_CrsGraph *p)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SharedPtr</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>aa04f35878be5d09a9e7212992936a16b</anchor>
      <arglist>(const SharedPtr&lt; Y &gt; &amp;x)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SharedPtr</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a9874d9dc7e02ff82a87a5ee45b2ea74d</anchor>
      <arglist>(const SharedPtr &amp;x)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~SharedPtr</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>ac6c248f87712f6afafa28fcbcdb53987</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>SharedPtr &amp;</type>
      <name>operator=</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a3345b70111b88d517dbfe6991d197a89</anchor>
      <arglist>(const SharedPtr&lt; Y &gt; &amp;x)</arglist>
    </member>
    <member kind="function">
      <type>SharedPtr &amp;</type>
      <name>operator=</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a5370427758b9147ab6cc347b12b011bf</anchor>
      <arglist>(const SharedPtr &amp;x)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>reset</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a0cce56dc2d636ba354b63d30061fa072</anchor>
      <arglist>(Epetra_CrsGraph *p=0)</arglist>
    </member>
    <member kind="function">
      <type>Epetra_CrsGraph &amp;</type>
      <name>operator*</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>aa65e5c5fb01b8b3c6e820302b1ca5424</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>Epetra_CrsGraph *</type>
      <name>operator-&gt;</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a1d18d5e137d8a184d5f1bdc1913d10a8</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>Epetra_CrsGraph *</type>
      <name>get</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a0296a552885744dbf7c81e29be463e28</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>long</type>
      <name>use_count</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a26d79923e382b42cb2a8fab468cad7ea</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>unique</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a653b3e338f9a87623c875b51ff932cc8</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>share</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>ad27873719f16e17c9057355130079499</anchor>
      <arglist>(Epetra_CrsGraph *xpointer, long *xcount)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>dispose</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>ac25cf9cbd9843804de943be3bb2670df</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>SharedPtr&lt; Epetra_CrsMatrix &gt;</name>
    <filename>classfei_1_1SharedPtr.html</filename>
    <member kind="typedef">
      <type>Epetra_CrsMatrix</type>
      <name>element_type</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>ac4770c63a5fb9297d0d0414afe79117c</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SharedPtr</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>afad2a2441a6f7907dd4d249dfd813398</anchor>
      <arglist>(Epetra_CrsMatrix *p)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SharedPtr</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>aa04f35878be5d09a9e7212992936a16b</anchor>
      <arglist>(const SharedPtr&lt; Y &gt; &amp;x)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SharedPtr</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a9874d9dc7e02ff82a87a5ee45b2ea74d</anchor>
      <arglist>(const SharedPtr &amp;x)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~SharedPtr</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>ac6c248f87712f6afafa28fcbcdb53987</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>SharedPtr &amp;</type>
      <name>operator=</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a3345b70111b88d517dbfe6991d197a89</anchor>
      <arglist>(const SharedPtr&lt; Y &gt; &amp;x)</arglist>
    </member>
    <member kind="function">
      <type>SharedPtr &amp;</type>
      <name>operator=</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a5370427758b9147ab6cc347b12b011bf</anchor>
      <arglist>(const SharedPtr &amp;x)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>reset</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a0cce56dc2d636ba354b63d30061fa072</anchor>
      <arglist>(Epetra_CrsMatrix *p=0)</arglist>
    </member>
    <member kind="function">
      <type>Epetra_CrsMatrix &amp;</type>
      <name>operator*</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>aa65e5c5fb01b8b3c6e820302b1ca5424</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>Epetra_CrsMatrix *</type>
      <name>operator-&gt;</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a1d18d5e137d8a184d5f1bdc1913d10a8</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>Epetra_CrsMatrix *</type>
      <name>get</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a0296a552885744dbf7c81e29be463e28</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>long</type>
      <name>use_count</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a26d79923e382b42cb2a8fab468cad7ea</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>unique</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a653b3e338f9a87623c875b51ff932cc8</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>share</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>ad27873719f16e17c9057355130079499</anchor>
      <arglist>(Epetra_CrsMatrix *xpointer, long *xcount)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>dispose</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>ac25cf9cbd9843804de943be3bb2670df</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>SharedPtr&lt; Epetra_Map &gt;</name>
    <filename>classfei_1_1SharedPtr.html</filename>
    <member kind="typedef">
      <type>Epetra_Map</type>
      <name>element_type</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>ac4770c63a5fb9297d0d0414afe79117c</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SharedPtr</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>afad2a2441a6f7907dd4d249dfd813398</anchor>
      <arglist>(Epetra_Map *p)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SharedPtr</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>aa04f35878be5d09a9e7212992936a16b</anchor>
      <arglist>(const SharedPtr&lt; Y &gt; &amp;x)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SharedPtr</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a9874d9dc7e02ff82a87a5ee45b2ea74d</anchor>
      <arglist>(const SharedPtr &amp;x)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~SharedPtr</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>ac6c248f87712f6afafa28fcbcdb53987</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>SharedPtr &amp;</type>
      <name>operator=</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a3345b70111b88d517dbfe6991d197a89</anchor>
      <arglist>(const SharedPtr&lt; Y &gt; &amp;x)</arglist>
    </member>
    <member kind="function">
      <type>SharedPtr &amp;</type>
      <name>operator=</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a5370427758b9147ab6cc347b12b011bf</anchor>
      <arglist>(const SharedPtr &amp;x)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>reset</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a0cce56dc2d636ba354b63d30061fa072</anchor>
      <arglist>(Epetra_Map *p=0)</arglist>
    </member>
    <member kind="function">
      <type>Epetra_Map &amp;</type>
      <name>operator*</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>aa65e5c5fb01b8b3c6e820302b1ca5424</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>Epetra_Map *</type>
      <name>operator-&gt;</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a1d18d5e137d8a184d5f1bdc1913d10a8</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>Epetra_Map *</type>
      <name>get</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a0296a552885744dbf7c81e29be463e28</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>long</type>
      <name>use_count</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a26d79923e382b42cb2a8fab468cad7ea</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>unique</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a653b3e338f9a87623c875b51ff932cc8</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>share</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>ad27873719f16e17c9057355130079499</anchor>
      <arglist>(Epetra_Map *xpointer, long *xcount)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>dispose</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>ac25cf9cbd9843804de943be3bb2670df</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>SharedPtr&lt; Epetra_MultiVector &gt;</name>
    <filename>classfei_1_1SharedPtr.html</filename>
    <member kind="typedef">
      <type>Epetra_MultiVector</type>
      <name>element_type</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>ac4770c63a5fb9297d0d0414afe79117c</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SharedPtr</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>afad2a2441a6f7907dd4d249dfd813398</anchor>
      <arglist>(Epetra_MultiVector *p)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SharedPtr</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>aa04f35878be5d09a9e7212992936a16b</anchor>
      <arglist>(const SharedPtr&lt; Y &gt; &amp;x)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SharedPtr</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a9874d9dc7e02ff82a87a5ee45b2ea74d</anchor>
      <arglist>(const SharedPtr &amp;x)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~SharedPtr</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>ac6c248f87712f6afafa28fcbcdb53987</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>SharedPtr &amp;</type>
      <name>operator=</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a3345b70111b88d517dbfe6991d197a89</anchor>
      <arglist>(const SharedPtr&lt; Y &gt; &amp;x)</arglist>
    </member>
    <member kind="function">
      <type>SharedPtr &amp;</type>
      <name>operator=</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a5370427758b9147ab6cc347b12b011bf</anchor>
      <arglist>(const SharedPtr &amp;x)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>reset</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a0cce56dc2d636ba354b63d30061fa072</anchor>
      <arglist>(Epetra_MultiVector *p=0)</arglist>
    </member>
    <member kind="function">
      <type>Epetra_MultiVector &amp;</type>
      <name>operator*</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>aa65e5c5fb01b8b3c6e820302b1ca5424</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>Epetra_MultiVector *</type>
      <name>operator-&gt;</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a1d18d5e137d8a184d5f1bdc1913d10a8</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>Epetra_MultiVector *</type>
      <name>get</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a0296a552885744dbf7c81e29be463e28</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>long</type>
      <name>use_count</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a26d79923e382b42cb2a8fab468cad7ea</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>unique</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a653b3e338f9a87623c875b51ff932cc8</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>share</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>ad27873719f16e17c9057355130079499</anchor>
      <arglist>(Epetra_MultiVector *xpointer, long *xcount)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>dispose</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>ac25cf9cbd9843804de943be3bb2670df</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>SharedPtr&lt; FEI &gt;</name>
    <filename>classfei_1_1SharedPtr.html</filename>
    <member kind="typedef">
      <type>FEI</type>
      <name>element_type</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>ac4770c63a5fb9297d0d0414afe79117c</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SharedPtr</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>afad2a2441a6f7907dd4d249dfd813398</anchor>
      <arglist>(FEI *p)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SharedPtr</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>aa04f35878be5d09a9e7212992936a16b</anchor>
      <arglist>(const SharedPtr&lt; Y &gt; &amp;x)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SharedPtr</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a9874d9dc7e02ff82a87a5ee45b2ea74d</anchor>
      <arglist>(const SharedPtr &amp;x)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~SharedPtr</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>ac6c248f87712f6afafa28fcbcdb53987</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>SharedPtr &amp;</type>
      <name>operator=</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a3345b70111b88d517dbfe6991d197a89</anchor>
      <arglist>(const SharedPtr&lt; Y &gt; &amp;x)</arglist>
    </member>
    <member kind="function">
      <type>SharedPtr &amp;</type>
      <name>operator=</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a5370427758b9147ab6cc347b12b011bf</anchor>
      <arglist>(const SharedPtr &amp;x)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>reset</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a0cce56dc2d636ba354b63d30061fa072</anchor>
      <arglist>(FEI *p=0)</arglist>
    </member>
    <member kind="function">
      <type>FEI &amp;</type>
      <name>operator*</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>aa65e5c5fb01b8b3c6e820302b1ca5424</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>FEI *</type>
      <name>operator-&gt;</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a1d18d5e137d8a184d5f1bdc1913d10a8</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>FEI *</type>
      <name>get</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a0296a552885744dbf7c81e29be463e28</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>long</type>
      <name>use_count</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a26d79923e382b42cb2a8fab468cad7ea</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>unique</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a653b3e338f9a87623c875b51ff932cc8</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>share</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>ad27873719f16e17c9057355130079499</anchor>
      <arglist>(FEI *xpointer, long *xcount)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>dispose</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>ac25cf9cbd9843804de943be3bb2670df</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>SharedPtr&lt; fei::CSVec &gt;</name>
    <filename>classfei_1_1SharedPtr.html</filename>
    <member kind="typedef">
      <type>fei::CSVec</type>
      <name>element_type</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>ac4770c63a5fb9297d0d0414afe79117c</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SharedPtr</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>afad2a2441a6f7907dd4d249dfd813398</anchor>
      <arglist>(fei::CSVec *p)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SharedPtr</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>aa04f35878be5d09a9e7212992936a16b</anchor>
      <arglist>(const SharedPtr&lt; Y &gt; &amp;x)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SharedPtr</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a9874d9dc7e02ff82a87a5ee45b2ea74d</anchor>
      <arglist>(const SharedPtr &amp;x)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~SharedPtr</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>ac6c248f87712f6afafa28fcbcdb53987</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>SharedPtr &amp;</type>
      <name>operator=</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a3345b70111b88d517dbfe6991d197a89</anchor>
      <arglist>(const SharedPtr&lt; Y &gt; &amp;x)</arglist>
    </member>
    <member kind="function">
      <type>SharedPtr &amp;</type>
      <name>operator=</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a5370427758b9147ab6cc347b12b011bf</anchor>
      <arglist>(const SharedPtr &amp;x)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>reset</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a0cce56dc2d636ba354b63d30061fa072</anchor>
      <arglist>(fei::CSVec *p=0)</arglist>
    </member>
    <member kind="function">
      <type>fei::CSVec &amp;</type>
      <name>operator*</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>aa65e5c5fb01b8b3c6e820302b1ca5424</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>fei::CSVec *</type>
      <name>operator-&gt;</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a1d18d5e137d8a184d5f1bdc1913d10a8</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>fei::CSVec *</type>
      <name>get</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a0296a552885744dbf7c81e29be463e28</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>long</type>
      <name>use_count</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a26d79923e382b42cb2a8fab468cad7ea</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>unique</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a653b3e338f9a87623c875b51ff932cc8</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>share</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>ad27873719f16e17c9057355130079499</anchor>
      <arglist>(fei::CSVec *xpointer, long *xcount)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>dispose</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>ac25cf9cbd9843804de943be3bb2670df</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>SharedPtr&lt; fei::EqnComm &gt;</name>
    <filename>classfei_1_1SharedPtr.html</filename>
    <member kind="typedef">
      <type>fei::EqnComm</type>
      <name>element_type</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>ac4770c63a5fb9297d0d0414afe79117c</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SharedPtr</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>afad2a2441a6f7907dd4d249dfd813398</anchor>
      <arglist>(fei::EqnComm *p)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SharedPtr</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>aa04f35878be5d09a9e7212992936a16b</anchor>
      <arglist>(const SharedPtr&lt; Y &gt; &amp;x)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SharedPtr</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a9874d9dc7e02ff82a87a5ee45b2ea74d</anchor>
      <arglist>(const SharedPtr &amp;x)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~SharedPtr</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>ac6c248f87712f6afafa28fcbcdb53987</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>SharedPtr &amp;</type>
      <name>operator=</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a3345b70111b88d517dbfe6991d197a89</anchor>
      <arglist>(const SharedPtr&lt; Y &gt; &amp;x)</arglist>
    </member>
    <member kind="function">
      <type>SharedPtr &amp;</type>
      <name>operator=</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a5370427758b9147ab6cc347b12b011bf</anchor>
      <arglist>(const SharedPtr &amp;x)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>reset</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a0cce56dc2d636ba354b63d30061fa072</anchor>
      <arglist>(fei::EqnComm *p=0)</arglist>
    </member>
    <member kind="function">
      <type>fei::EqnComm &amp;</type>
      <name>operator*</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>aa65e5c5fb01b8b3c6e820302b1ca5424</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>fei::EqnComm *</type>
      <name>operator-&gt;</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a1d18d5e137d8a184d5f1bdc1913d10a8</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>fei::EqnComm *</type>
      <name>get</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a0296a552885744dbf7c81e29be463e28</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>long</type>
      <name>use_count</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a26d79923e382b42cb2a8fab468cad7ea</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>unique</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a653b3e338f9a87623c875b51ff932cc8</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>share</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>ad27873719f16e17c9057355130079499</anchor>
      <arglist>(fei::EqnComm *xpointer, long *xcount)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>dispose</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>ac25cf9cbd9843804de943be3bb2670df</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>SharedPtr&lt; fei::Factory &gt;</name>
    <filename>classfei_1_1SharedPtr.html</filename>
    <member kind="typedef">
      <type>fei::Factory</type>
      <name>element_type</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>ac4770c63a5fb9297d0d0414afe79117c</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SharedPtr</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>afad2a2441a6f7907dd4d249dfd813398</anchor>
      <arglist>(fei::Factory *p)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SharedPtr</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>aa04f35878be5d09a9e7212992936a16b</anchor>
      <arglist>(const SharedPtr&lt; Y &gt; &amp;x)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SharedPtr</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a9874d9dc7e02ff82a87a5ee45b2ea74d</anchor>
      <arglist>(const SharedPtr &amp;x)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~SharedPtr</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>ac6c248f87712f6afafa28fcbcdb53987</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>SharedPtr &amp;</type>
      <name>operator=</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a3345b70111b88d517dbfe6991d197a89</anchor>
      <arglist>(const SharedPtr&lt; Y &gt; &amp;x)</arglist>
    </member>
    <member kind="function">
      <type>SharedPtr &amp;</type>
      <name>operator=</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a5370427758b9147ab6cc347b12b011bf</anchor>
      <arglist>(const SharedPtr &amp;x)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>reset</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a0cce56dc2d636ba354b63d30061fa072</anchor>
      <arglist>(fei::Factory *p=0)</arglist>
    </member>
    <member kind="function">
      <type>fei::Factory &amp;</type>
      <name>operator*</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>aa65e5c5fb01b8b3c6e820302b1ca5424</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>fei::Factory *</type>
      <name>operator-&gt;</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a1d18d5e137d8a184d5f1bdc1913d10a8</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>fei::Factory *</type>
      <name>get</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a0296a552885744dbf7c81e29be463e28</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>long</type>
      <name>use_count</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a26d79923e382b42cb2a8fab468cad7ea</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>unique</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a653b3e338f9a87623c875b51ff932cc8</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>share</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>ad27873719f16e17c9057355130079499</anchor>
      <arglist>(fei::Factory *xpointer, long *xcount)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>dispose</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>ac25cf9cbd9843804de943be3bb2670df</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>SharedPtr&lt; fei::fei::Graph &gt;</name>
    <filename>classfei_1_1SharedPtr.html</filename>
    <member kind="typedef">
      <type>fei::fei::Graph</type>
      <name>element_type</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>ac4770c63a5fb9297d0d0414afe79117c</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SharedPtr</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>afad2a2441a6f7907dd4d249dfd813398</anchor>
      <arglist>(fei::fei::Graph *p)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SharedPtr</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>aa04f35878be5d09a9e7212992936a16b</anchor>
      <arglist>(const SharedPtr&lt; Y &gt; &amp;x)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SharedPtr</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a9874d9dc7e02ff82a87a5ee45b2ea74d</anchor>
      <arglist>(const SharedPtr &amp;x)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~SharedPtr</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>ac6c248f87712f6afafa28fcbcdb53987</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>SharedPtr &amp;</type>
      <name>operator=</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a3345b70111b88d517dbfe6991d197a89</anchor>
      <arglist>(const SharedPtr&lt; Y &gt; &amp;x)</arglist>
    </member>
    <member kind="function">
      <type>SharedPtr &amp;</type>
      <name>operator=</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a5370427758b9147ab6cc347b12b011bf</anchor>
      <arglist>(const SharedPtr &amp;x)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>reset</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a0cce56dc2d636ba354b63d30061fa072</anchor>
      <arglist>(fei::fei::Graph *p=0)</arglist>
    </member>
    <member kind="function">
      <type>fei::fei::Graph &amp;</type>
      <name>operator*</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>aa65e5c5fb01b8b3c6e820302b1ca5424</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>fei::fei::Graph *</type>
      <name>operator-&gt;</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a1d18d5e137d8a184d5f1bdc1913d10a8</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>fei::fei::Graph *</type>
      <name>get</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a0296a552885744dbf7c81e29be463e28</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>long</type>
      <name>use_count</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a26d79923e382b42cb2a8fab468cad7ea</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>unique</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a653b3e338f9a87623c875b51ff932cc8</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>share</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>ad27873719f16e17c9057355130079499</anchor>
      <arglist>(fei::fei::Graph *xpointer, long *xcount)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>dispose</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>ac25cf9cbd9843804de943be3bb2670df</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>SharedPtr&lt; fei::fei::LinearSystem &gt;</name>
    <filename>classfei_1_1SharedPtr.html</filename>
    <member kind="typedef">
      <type>fei::fei::LinearSystem</type>
      <name>element_type</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>ac4770c63a5fb9297d0d0414afe79117c</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SharedPtr</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>afad2a2441a6f7907dd4d249dfd813398</anchor>
      <arglist>(fei::fei::LinearSystem *p)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SharedPtr</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>aa04f35878be5d09a9e7212992936a16b</anchor>
      <arglist>(const SharedPtr&lt; Y &gt; &amp;x)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SharedPtr</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a9874d9dc7e02ff82a87a5ee45b2ea74d</anchor>
      <arglist>(const SharedPtr &amp;x)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~SharedPtr</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>ac6c248f87712f6afafa28fcbcdb53987</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>SharedPtr &amp;</type>
      <name>operator=</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a3345b70111b88d517dbfe6991d197a89</anchor>
      <arglist>(const SharedPtr&lt; Y &gt; &amp;x)</arglist>
    </member>
    <member kind="function">
      <type>SharedPtr &amp;</type>
      <name>operator=</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a5370427758b9147ab6cc347b12b011bf</anchor>
      <arglist>(const SharedPtr &amp;x)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>reset</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a0cce56dc2d636ba354b63d30061fa072</anchor>
      <arglist>(fei::fei::LinearSystem *p=0)</arglist>
    </member>
    <member kind="function">
      <type>fei::fei::LinearSystem &amp;</type>
      <name>operator*</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>aa65e5c5fb01b8b3c6e820302b1ca5424</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>fei::fei::LinearSystem *</type>
      <name>operator-&gt;</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a1d18d5e137d8a184d5f1bdc1913d10a8</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>fei::fei::LinearSystem *</type>
      <name>get</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a0296a552885744dbf7c81e29be463e28</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>long</type>
      <name>use_count</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a26d79923e382b42cb2a8fab468cad7ea</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>unique</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a653b3e338f9a87623c875b51ff932cc8</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>share</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>ad27873719f16e17c9057355130079499</anchor>
      <arglist>(fei::fei::LinearSystem *xpointer, long *xcount)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>dispose</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>ac25cf9cbd9843804de943be3bb2670df</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>SharedPtr&lt; fei::fei::Matrix &gt;</name>
    <filename>classfei_1_1SharedPtr.html</filename>
    <member kind="typedef">
      <type>fei::fei::Matrix</type>
      <name>element_type</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>ac4770c63a5fb9297d0d0414afe79117c</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SharedPtr</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>afad2a2441a6f7907dd4d249dfd813398</anchor>
      <arglist>(fei::fei::Matrix *p)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SharedPtr</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>aa04f35878be5d09a9e7212992936a16b</anchor>
      <arglist>(const SharedPtr&lt; Y &gt; &amp;x)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SharedPtr</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a9874d9dc7e02ff82a87a5ee45b2ea74d</anchor>
      <arglist>(const SharedPtr &amp;x)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~SharedPtr</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>ac6c248f87712f6afafa28fcbcdb53987</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>SharedPtr &amp;</type>
      <name>operator=</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a3345b70111b88d517dbfe6991d197a89</anchor>
      <arglist>(const SharedPtr&lt; Y &gt; &amp;x)</arglist>
    </member>
    <member kind="function">
      <type>SharedPtr &amp;</type>
      <name>operator=</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a5370427758b9147ab6cc347b12b011bf</anchor>
      <arglist>(const SharedPtr &amp;x)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>reset</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a0cce56dc2d636ba354b63d30061fa072</anchor>
      <arglist>(fei::fei::Matrix *p=0)</arglist>
    </member>
    <member kind="function">
      <type>fei::fei::Matrix &amp;</type>
      <name>operator*</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>aa65e5c5fb01b8b3c6e820302b1ca5424</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>fei::fei::Matrix *</type>
      <name>operator-&gt;</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a1d18d5e137d8a184d5f1bdc1913d10a8</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>fei::fei::Matrix *</type>
      <name>get</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a0296a552885744dbf7c81e29be463e28</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>long</type>
      <name>use_count</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a26d79923e382b42cb2a8fab468cad7ea</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>unique</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a653b3e338f9a87623c875b51ff932cc8</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>share</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>ad27873719f16e17c9057355130079499</anchor>
      <arglist>(fei::fei::Matrix *xpointer, long *xcount)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>dispose</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>ac25cf9cbd9843804de943be3bb2670df</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>SharedPtr&lt; fei::fei::MatrixGraph &gt;</name>
    <filename>classfei_1_1SharedPtr.html</filename>
    <member kind="typedef">
      <type>fei::fei::MatrixGraph</type>
      <name>element_type</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>ac4770c63a5fb9297d0d0414afe79117c</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SharedPtr</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>afad2a2441a6f7907dd4d249dfd813398</anchor>
      <arglist>(fei::fei::MatrixGraph *p)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SharedPtr</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>aa04f35878be5d09a9e7212992936a16b</anchor>
      <arglist>(const SharedPtr&lt; Y &gt; &amp;x)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SharedPtr</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a9874d9dc7e02ff82a87a5ee45b2ea74d</anchor>
      <arglist>(const SharedPtr &amp;x)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~SharedPtr</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>ac6c248f87712f6afafa28fcbcdb53987</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>SharedPtr &amp;</type>
      <name>operator=</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a3345b70111b88d517dbfe6991d197a89</anchor>
      <arglist>(const SharedPtr&lt; Y &gt; &amp;x)</arglist>
    </member>
    <member kind="function">
      <type>SharedPtr &amp;</type>
      <name>operator=</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a5370427758b9147ab6cc347b12b011bf</anchor>
      <arglist>(const SharedPtr &amp;x)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>reset</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a0cce56dc2d636ba354b63d30061fa072</anchor>
      <arglist>(fei::fei::MatrixGraph *p=0)</arglist>
    </member>
    <member kind="function">
      <type>fei::fei::MatrixGraph &amp;</type>
      <name>operator*</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>aa65e5c5fb01b8b3c6e820302b1ca5424</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>fei::fei::MatrixGraph *</type>
      <name>operator-&gt;</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a1d18d5e137d8a184d5f1bdc1913d10a8</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>fei::fei::MatrixGraph *</type>
      <name>get</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a0296a552885744dbf7c81e29be463e28</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>long</type>
      <name>use_count</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a26d79923e382b42cb2a8fab468cad7ea</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>unique</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a653b3e338f9a87623c875b51ff932cc8</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>share</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>ad27873719f16e17c9057355130079499</anchor>
      <arglist>(fei::fei::MatrixGraph *xpointer, long *xcount)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>dispose</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>ac25cf9cbd9843804de943be3bb2670df</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>SharedPtr&lt; fei::fei::SparseRowGraph &gt;</name>
    <filename>classfei_1_1SharedPtr.html</filename>
    <member kind="typedef">
      <type>fei::fei::SparseRowGraph</type>
      <name>element_type</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>ac4770c63a5fb9297d0d0414afe79117c</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SharedPtr</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>afad2a2441a6f7907dd4d249dfd813398</anchor>
      <arglist>(fei::fei::SparseRowGraph *p)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SharedPtr</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>aa04f35878be5d09a9e7212992936a16b</anchor>
      <arglist>(const SharedPtr&lt; Y &gt; &amp;x)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SharedPtr</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a9874d9dc7e02ff82a87a5ee45b2ea74d</anchor>
      <arglist>(const SharedPtr &amp;x)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~SharedPtr</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>ac6c248f87712f6afafa28fcbcdb53987</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>SharedPtr &amp;</type>
      <name>operator=</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a3345b70111b88d517dbfe6991d197a89</anchor>
      <arglist>(const SharedPtr&lt; Y &gt; &amp;x)</arglist>
    </member>
    <member kind="function">
      <type>SharedPtr &amp;</type>
      <name>operator=</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a5370427758b9147ab6cc347b12b011bf</anchor>
      <arglist>(const SharedPtr &amp;x)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>reset</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a0cce56dc2d636ba354b63d30061fa072</anchor>
      <arglist>(fei::fei::SparseRowGraph *p=0)</arglist>
    </member>
    <member kind="function">
      <type>fei::fei::SparseRowGraph &amp;</type>
      <name>operator*</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>aa65e5c5fb01b8b3c6e820302b1ca5424</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>fei::fei::SparseRowGraph *</type>
      <name>operator-&gt;</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a1d18d5e137d8a184d5f1bdc1913d10a8</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>fei::fei::SparseRowGraph *</type>
      <name>get</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a0296a552885744dbf7c81e29be463e28</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>long</type>
      <name>use_count</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a26d79923e382b42cb2a8fab468cad7ea</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>unique</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a653b3e338f9a87623c875b51ff932cc8</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>share</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>ad27873719f16e17c9057355130079499</anchor>
      <arglist>(fei::fei::SparseRowGraph *xpointer, long *xcount)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>dispose</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>ac25cf9cbd9843804de943be3bb2670df</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>SharedPtr&lt; fei::fei::Vector &gt;</name>
    <filename>classfei_1_1SharedPtr.html</filename>
    <member kind="typedef">
      <type>fei::fei::Vector</type>
      <name>element_type</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>ac4770c63a5fb9297d0d0414afe79117c</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SharedPtr</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>afad2a2441a6f7907dd4d249dfd813398</anchor>
      <arglist>(fei::fei::Vector *p)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SharedPtr</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>aa04f35878be5d09a9e7212992936a16b</anchor>
      <arglist>(const SharedPtr&lt; Y &gt; &amp;x)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SharedPtr</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a9874d9dc7e02ff82a87a5ee45b2ea74d</anchor>
      <arglist>(const SharedPtr &amp;x)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~SharedPtr</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>ac6c248f87712f6afafa28fcbcdb53987</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>SharedPtr &amp;</type>
      <name>operator=</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a3345b70111b88d517dbfe6991d197a89</anchor>
      <arglist>(const SharedPtr&lt; Y &gt; &amp;x)</arglist>
    </member>
    <member kind="function">
      <type>SharedPtr &amp;</type>
      <name>operator=</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a5370427758b9147ab6cc347b12b011bf</anchor>
      <arglist>(const SharedPtr &amp;x)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>reset</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a0cce56dc2d636ba354b63d30061fa072</anchor>
      <arglist>(fei::fei::Vector *p=0)</arglist>
    </member>
    <member kind="function">
      <type>fei::fei::Vector &amp;</type>
      <name>operator*</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>aa65e5c5fb01b8b3c6e820302b1ca5424</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>fei::fei::Vector *</type>
      <name>operator-&gt;</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a1d18d5e137d8a184d5f1bdc1913d10a8</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>fei::fei::Vector *</type>
      <name>get</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a0296a552885744dbf7c81e29be463e28</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>long</type>
      <name>use_count</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a26d79923e382b42cb2a8fab468cad7ea</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>unique</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a653b3e338f9a87623c875b51ff932cc8</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>share</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>ad27873719f16e17c9057355130079499</anchor>
      <arglist>(fei::fei::Vector *xpointer, long *xcount)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>dispose</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>ac25cf9cbd9843804de943be3bb2670df</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>SharedPtr&lt; fei::fei::VectorSpace &gt;</name>
    <filename>classfei_1_1SharedPtr.html</filename>
    <member kind="typedef">
      <type>fei::fei::VectorSpace</type>
      <name>element_type</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>ac4770c63a5fb9297d0d0414afe79117c</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SharedPtr</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>afad2a2441a6f7907dd4d249dfd813398</anchor>
      <arglist>(fei::fei::VectorSpace *p)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SharedPtr</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>aa04f35878be5d09a9e7212992936a16b</anchor>
      <arglist>(const SharedPtr&lt; Y &gt; &amp;x)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SharedPtr</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a9874d9dc7e02ff82a87a5ee45b2ea74d</anchor>
      <arglist>(const SharedPtr &amp;x)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~SharedPtr</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>ac6c248f87712f6afafa28fcbcdb53987</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>SharedPtr &amp;</type>
      <name>operator=</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a3345b70111b88d517dbfe6991d197a89</anchor>
      <arglist>(const SharedPtr&lt; Y &gt; &amp;x)</arglist>
    </member>
    <member kind="function">
      <type>SharedPtr &amp;</type>
      <name>operator=</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a5370427758b9147ab6cc347b12b011bf</anchor>
      <arglist>(const SharedPtr &amp;x)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>reset</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a0cce56dc2d636ba354b63d30061fa072</anchor>
      <arglist>(fei::fei::VectorSpace *p=0)</arglist>
    </member>
    <member kind="function">
      <type>fei::fei::VectorSpace &amp;</type>
      <name>operator*</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>aa65e5c5fb01b8b3c6e820302b1ca5424</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>fei::fei::VectorSpace *</type>
      <name>operator-&gt;</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a1d18d5e137d8a184d5f1bdc1913d10a8</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>fei::fei::VectorSpace *</type>
      <name>get</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a0296a552885744dbf7c81e29be463e28</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>long</type>
      <name>use_count</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a26d79923e382b42cb2a8fab468cad7ea</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>unique</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a653b3e338f9a87623c875b51ff932cc8</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>share</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>ad27873719f16e17c9057355130079499</anchor>
      <arglist>(fei::fei::VectorSpace *xpointer, long *xcount)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>dispose</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>ac25cf9cbd9843804de943be3bb2670df</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>SharedPtr&lt; fei::LinearProblemManager &gt;</name>
    <filename>classfei_1_1SharedPtr.html</filename>
    <member kind="typedef">
      <type>fei::LinearProblemManager</type>
      <name>element_type</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>ac4770c63a5fb9297d0d0414afe79117c</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SharedPtr</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>afad2a2441a6f7907dd4d249dfd813398</anchor>
      <arglist>(fei::LinearProblemManager *p)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SharedPtr</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>aa04f35878be5d09a9e7212992936a16b</anchor>
      <arglist>(const SharedPtr&lt; Y &gt; &amp;x)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SharedPtr</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a9874d9dc7e02ff82a87a5ee45b2ea74d</anchor>
      <arglist>(const SharedPtr &amp;x)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~SharedPtr</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>ac6c248f87712f6afafa28fcbcdb53987</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>SharedPtr &amp;</type>
      <name>operator=</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a3345b70111b88d517dbfe6991d197a89</anchor>
      <arglist>(const SharedPtr&lt; Y &gt; &amp;x)</arglist>
    </member>
    <member kind="function">
      <type>SharedPtr &amp;</type>
      <name>operator=</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a5370427758b9147ab6cc347b12b011bf</anchor>
      <arglist>(const SharedPtr &amp;x)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>reset</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a0cce56dc2d636ba354b63d30061fa072</anchor>
      <arglist>(fei::LinearProblemManager *p=0)</arglist>
    </member>
    <member kind="function">
      <type>fei::LinearProblemManager &amp;</type>
      <name>operator*</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>aa65e5c5fb01b8b3c6e820302b1ca5424</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>fei::LinearProblemManager *</type>
      <name>operator-&gt;</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a1d18d5e137d8a184d5f1bdc1913d10a8</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>fei::LinearProblemManager *</type>
      <name>get</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a0296a552885744dbf7c81e29be463e28</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>long</type>
      <name>use_count</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a26d79923e382b42cb2a8fab468cad7ea</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>unique</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a653b3e338f9a87623c875b51ff932cc8</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>share</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>ad27873719f16e17c9057355130079499</anchor>
      <arglist>(fei::LinearProblemManager *xpointer, long *xcount)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>dispose</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>ac25cf9cbd9843804de943be3bb2670df</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>SharedPtr&lt; fei::LinearSystem &gt;</name>
    <filename>classfei_1_1SharedPtr.html</filename>
    <member kind="typedef">
      <type>fei::LinearSystem</type>
      <name>element_type</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>ac4770c63a5fb9297d0d0414afe79117c</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SharedPtr</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>afad2a2441a6f7907dd4d249dfd813398</anchor>
      <arglist>(fei::LinearSystem *p)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SharedPtr</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>aa04f35878be5d09a9e7212992936a16b</anchor>
      <arglist>(const SharedPtr&lt; Y &gt; &amp;x)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SharedPtr</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a9874d9dc7e02ff82a87a5ee45b2ea74d</anchor>
      <arglist>(const SharedPtr &amp;x)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~SharedPtr</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>ac6c248f87712f6afafa28fcbcdb53987</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>SharedPtr &amp;</type>
      <name>operator=</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a3345b70111b88d517dbfe6991d197a89</anchor>
      <arglist>(const SharedPtr&lt; Y &gt; &amp;x)</arglist>
    </member>
    <member kind="function">
      <type>SharedPtr &amp;</type>
      <name>operator=</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a5370427758b9147ab6cc347b12b011bf</anchor>
      <arglist>(const SharedPtr &amp;x)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>reset</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a0cce56dc2d636ba354b63d30061fa072</anchor>
      <arglist>(fei::LinearSystem *p=0)</arglist>
    </member>
    <member kind="function">
      <type>fei::LinearSystem &amp;</type>
      <name>operator*</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>aa65e5c5fb01b8b3c6e820302b1ca5424</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>fei::LinearSystem *</type>
      <name>operator-&gt;</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a1d18d5e137d8a184d5f1bdc1913d10a8</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>fei::LinearSystem *</type>
      <name>get</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a0296a552885744dbf7c81e29be463e28</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>long</type>
      <name>use_count</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a26d79923e382b42cb2a8fab468cad7ea</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>unique</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a653b3e338f9a87623c875b51ff932cc8</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>share</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>ad27873719f16e17c9057355130079499</anchor>
      <arglist>(fei::LinearSystem *xpointer, long *xcount)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>dispose</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>ac25cf9cbd9843804de943be3bb2670df</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>SharedPtr&lt; fei::Matrix &gt;</name>
    <filename>classfei_1_1SharedPtr.html</filename>
    <member kind="typedef">
      <type>fei::Matrix</type>
      <name>element_type</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>ac4770c63a5fb9297d0d0414afe79117c</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SharedPtr</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>afad2a2441a6f7907dd4d249dfd813398</anchor>
      <arglist>(fei::Matrix *p)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SharedPtr</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>aa04f35878be5d09a9e7212992936a16b</anchor>
      <arglist>(const SharedPtr&lt; Y &gt; &amp;x)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SharedPtr</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a9874d9dc7e02ff82a87a5ee45b2ea74d</anchor>
      <arglist>(const SharedPtr &amp;x)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~SharedPtr</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>ac6c248f87712f6afafa28fcbcdb53987</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>SharedPtr &amp;</type>
      <name>operator=</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a3345b70111b88d517dbfe6991d197a89</anchor>
      <arglist>(const SharedPtr&lt; Y &gt; &amp;x)</arglist>
    </member>
    <member kind="function">
      <type>SharedPtr &amp;</type>
      <name>operator=</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a5370427758b9147ab6cc347b12b011bf</anchor>
      <arglist>(const SharedPtr &amp;x)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>reset</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a0cce56dc2d636ba354b63d30061fa072</anchor>
      <arglist>(fei::Matrix *p=0)</arglist>
    </member>
    <member kind="function">
      <type>fei::Matrix &amp;</type>
      <name>operator*</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>aa65e5c5fb01b8b3c6e820302b1ca5424</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>fei::Matrix *</type>
      <name>operator-&gt;</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a1d18d5e137d8a184d5f1bdc1913d10a8</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>fei::Matrix *</type>
      <name>get</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a0296a552885744dbf7c81e29be463e28</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>long</type>
      <name>use_count</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a26d79923e382b42cb2a8fab468cad7ea</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>unique</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a653b3e338f9a87623c875b51ff932cc8</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>share</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>ad27873719f16e17c9057355130079499</anchor>
      <arglist>(fei::Matrix *xpointer, long *xcount)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>dispose</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>ac25cf9cbd9843804de943be3bb2670df</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>SharedPtr&lt; fei::MatrixGraph &gt;</name>
    <filename>classfei_1_1SharedPtr.html</filename>
    <member kind="typedef">
      <type>fei::MatrixGraph</type>
      <name>element_type</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>ac4770c63a5fb9297d0d0414afe79117c</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SharedPtr</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>afad2a2441a6f7907dd4d249dfd813398</anchor>
      <arglist>(fei::MatrixGraph *p)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SharedPtr</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>aa04f35878be5d09a9e7212992936a16b</anchor>
      <arglist>(const SharedPtr&lt; Y &gt; &amp;x)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SharedPtr</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a9874d9dc7e02ff82a87a5ee45b2ea74d</anchor>
      <arglist>(const SharedPtr &amp;x)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~SharedPtr</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>ac6c248f87712f6afafa28fcbcdb53987</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>SharedPtr &amp;</type>
      <name>operator=</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a3345b70111b88d517dbfe6991d197a89</anchor>
      <arglist>(const SharedPtr&lt; Y &gt; &amp;x)</arglist>
    </member>
    <member kind="function">
      <type>SharedPtr &amp;</type>
      <name>operator=</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a5370427758b9147ab6cc347b12b011bf</anchor>
      <arglist>(const SharedPtr &amp;x)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>reset</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a0cce56dc2d636ba354b63d30061fa072</anchor>
      <arglist>(fei::MatrixGraph *p=0)</arglist>
    </member>
    <member kind="function">
      <type>fei::MatrixGraph &amp;</type>
      <name>operator*</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>aa65e5c5fb01b8b3c6e820302b1ca5424</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>fei::MatrixGraph *</type>
      <name>operator-&gt;</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a1d18d5e137d8a184d5f1bdc1913d10a8</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>fei::MatrixGraph *</type>
      <name>get</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a0296a552885744dbf7c81e29be463e28</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>long</type>
      <name>use_count</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a26d79923e382b42cb2a8fab468cad7ea</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>unique</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a653b3e338f9a87623c875b51ff932cc8</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>share</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>ad27873719f16e17c9057355130079499</anchor>
      <arglist>(fei::MatrixGraph *xpointer, long *xcount)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>dispose</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>ac25cf9cbd9843804de943be3bb2670df</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>SharedPtr&lt; fei::Reducer &gt;</name>
    <filename>classfei_1_1SharedPtr.html</filename>
    <member kind="typedef">
      <type>fei::Reducer</type>
      <name>element_type</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>ac4770c63a5fb9297d0d0414afe79117c</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SharedPtr</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>afad2a2441a6f7907dd4d249dfd813398</anchor>
      <arglist>(fei::Reducer *p)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SharedPtr</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>aa04f35878be5d09a9e7212992936a16b</anchor>
      <arglist>(const SharedPtr&lt; Y &gt; &amp;x)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SharedPtr</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a9874d9dc7e02ff82a87a5ee45b2ea74d</anchor>
      <arglist>(const SharedPtr &amp;x)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~SharedPtr</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>ac6c248f87712f6afafa28fcbcdb53987</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>SharedPtr &amp;</type>
      <name>operator=</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a3345b70111b88d517dbfe6991d197a89</anchor>
      <arglist>(const SharedPtr&lt; Y &gt; &amp;x)</arglist>
    </member>
    <member kind="function">
      <type>SharedPtr &amp;</type>
      <name>operator=</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a5370427758b9147ab6cc347b12b011bf</anchor>
      <arglist>(const SharedPtr &amp;x)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>reset</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a0cce56dc2d636ba354b63d30061fa072</anchor>
      <arglist>(fei::Reducer *p=0)</arglist>
    </member>
    <member kind="function">
      <type>fei::Reducer &amp;</type>
      <name>operator*</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>aa65e5c5fb01b8b3c6e820302b1ca5424</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>fei::Reducer *</type>
      <name>operator-&gt;</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a1d18d5e137d8a184d5f1bdc1913d10a8</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>fei::Reducer *</type>
      <name>get</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a0296a552885744dbf7c81e29be463e28</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>long</type>
      <name>use_count</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a26d79923e382b42cb2a8fab468cad7ea</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>unique</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a653b3e338f9a87623c875b51ff932cc8</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>share</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>ad27873719f16e17c9057355130079499</anchor>
      <arglist>(fei::Reducer *xpointer, long *xcount)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>dispose</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>ac25cf9cbd9843804de943be3bb2670df</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>SharedPtr&lt; fei::SparseRowGraph &gt;</name>
    <filename>classfei_1_1SharedPtr.html</filename>
    <member kind="typedef">
      <type>fei::SparseRowGraph</type>
      <name>element_type</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>ac4770c63a5fb9297d0d0414afe79117c</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SharedPtr</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>afad2a2441a6f7907dd4d249dfd813398</anchor>
      <arglist>(fei::SparseRowGraph *p)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SharedPtr</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>aa04f35878be5d09a9e7212992936a16b</anchor>
      <arglist>(const SharedPtr&lt; Y &gt; &amp;x)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SharedPtr</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a9874d9dc7e02ff82a87a5ee45b2ea74d</anchor>
      <arglist>(const SharedPtr &amp;x)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~SharedPtr</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>ac6c248f87712f6afafa28fcbcdb53987</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>SharedPtr &amp;</type>
      <name>operator=</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a3345b70111b88d517dbfe6991d197a89</anchor>
      <arglist>(const SharedPtr&lt; Y &gt; &amp;x)</arglist>
    </member>
    <member kind="function">
      <type>SharedPtr &amp;</type>
      <name>operator=</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a5370427758b9147ab6cc347b12b011bf</anchor>
      <arglist>(const SharedPtr &amp;x)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>reset</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a0cce56dc2d636ba354b63d30061fa072</anchor>
      <arglist>(fei::SparseRowGraph *p=0)</arglist>
    </member>
    <member kind="function">
      <type>fei::SparseRowGraph &amp;</type>
      <name>operator*</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>aa65e5c5fb01b8b3c6e820302b1ca5424</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>fei::SparseRowGraph *</type>
      <name>operator-&gt;</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a1d18d5e137d8a184d5f1bdc1913d10a8</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>fei::SparseRowGraph *</type>
      <name>get</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a0296a552885744dbf7c81e29be463e28</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>long</type>
      <name>use_count</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a26d79923e382b42cb2a8fab468cad7ea</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>unique</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a653b3e338f9a87623c875b51ff932cc8</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>share</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>ad27873719f16e17c9057355130079499</anchor>
      <arglist>(fei::SparseRowGraph *xpointer, long *xcount)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>dispose</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>ac25cf9cbd9843804de943be3bb2670df</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>SharedPtr&lt; fei::Vector &gt;</name>
    <filename>classfei_1_1SharedPtr.html</filename>
    <member kind="typedef">
      <type>fei::Vector</type>
      <name>element_type</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>ac4770c63a5fb9297d0d0414afe79117c</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SharedPtr</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>afad2a2441a6f7907dd4d249dfd813398</anchor>
      <arglist>(fei::Vector *p)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SharedPtr</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>aa04f35878be5d09a9e7212992936a16b</anchor>
      <arglist>(const SharedPtr&lt; Y &gt; &amp;x)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SharedPtr</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a9874d9dc7e02ff82a87a5ee45b2ea74d</anchor>
      <arglist>(const SharedPtr &amp;x)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~SharedPtr</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>ac6c248f87712f6afafa28fcbcdb53987</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>SharedPtr &amp;</type>
      <name>operator=</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a3345b70111b88d517dbfe6991d197a89</anchor>
      <arglist>(const SharedPtr&lt; Y &gt; &amp;x)</arglist>
    </member>
    <member kind="function">
      <type>SharedPtr &amp;</type>
      <name>operator=</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a5370427758b9147ab6cc347b12b011bf</anchor>
      <arglist>(const SharedPtr &amp;x)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>reset</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a0cce56dc2d636ba354b63d30061fa072</anchor>
      <arglist>(fei::Vector *p=0)</arglist>
    </member>
    <member kind="function">
      <type>fei::Vector &amp;</type>
      <name>operator*</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>aa65e5c5fb01b8b3c6e820302b1ca5424</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>fei::Vector *</type>
      <name>operator-&gt;</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a1d18d5e137d8a184d5f1bdc1913d10a8</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>fei::Vector *</type>
      <name>get</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a0296a552885744dbf7c81e29be463e28</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>long</type>
      <name>use_count</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a26d79923e382b42cb2a8fab468cad7ea</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>unique</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a653b3e338f9a87623c875b51ff932cc8</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>share</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>ad27873719f16e17c9057355130079499</anchor>
      <arglist>(fei::Vector *xpointer, long *xcount)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>dispose</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>ac25cf9cbd9843804de943be3bb2670df</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>SharedPtr&lt; fei::VectorSpace &gt;</name>
    <filename>classfei_1_1SharedPtr.html</filename>
    <member kind="typedef">
      <type>fei::VectorSpace</type>
      <name>element_type</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>ac4770c63a5fb9297d0d0414afe79117c</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SharedPtr</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>afad2a2441a6f7907dd4d249dfd813398</anchor>
      <arglist>(fei::VectorSpace *p)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SharedPtr</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>aa04f35878be5d09a9e7212992936a16b</anchor>
      <arglist>(const SharedPtr&lt; Y &gt; &amp;x)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SharedPtr</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a9874d9dc7e02ff82a87a5ee45b2ea74d</anchor>
      <arglist>(const SharedPtr &amp;x)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~SharedPtr</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>ac6c248f87712f6afafa28fcbcdb53987</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>SharedPtr &amp;</type>
      <name>operator=</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a3345b70111b88d517dbfe6991d197a89</anchor>
      <arglist>(const SharedPtr&lt; Y &gt; &amp;x)</arglist>
    </member>
    <member kind="function">
      <type>SharedPtr &amp;</type>
      <name>operator=</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a5370427758b9147ab6cc347b12b011bf</anchor>
      <arglist>(const SharedPtr &amp;x)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>reset</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a0cce56dc2d636ba354b63d30061fa072</anchor>
      <arglist>(fei::VectorSpace *p=0)</arglist>
    </member>
    <member kind="function">
      <type>fei::VectorSpace &amp;</type>
      <name>operator*</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>aa65e5c5fb01b8b3c6e820302b1ca5424</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>fei::VectorSpace *</type>
      <name>operator-&gt;</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a1d18d5e137d8a184d5f1bdc1913d10a8</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>fei::VectorSpace *</type>
      <name>get</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a0296a552885744dbf7c81e29be463e28</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>long</type>
      <name>use_count</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a26d79923e382b42cb2a8fab468cad7ea</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>unique</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a653b3e338f9a87623c875b51ff932cc8</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>share</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>ad27873719f16e17c9057355130079499</anchor>
      <arglist>(fei::VectorSpace *xpointer, long *xcount)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>dispose</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>ac25cf9cbd9843804de943be3bb2670df</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>SharedPtr&lt; FillableMat &gt;</name>
    <filename>classfei_1_1SharedPtr.html</filename>
    <member kind="typedef">
      <type>FillableMat</type>
      <name>element_type</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>ac4770c63a5fb9297d0d0414afe79117c</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SharedPtr</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>afad2a2441a6f7907dd4d249dfd813398</anchor>
      <arglist>(FillableMat *p)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SharedPtr</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>aa04f35878be5d09a9e7212992936a16b</anchor>
      <arglist>(const SharedPtr&lt; Y &gt; &amp;x)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SharedPtr</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a9874d9dc7e02ff82a87a5ee45b2ea74d</anchor>
      <arglist>(const SharedPtr &amp;x)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~SharedPtr</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>ac6c248f87712f6afafa28fcbcdb53987</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>SharedPtr &amp;</type>
      <name>operator=</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a3345b70111b88d517dbfe6991d197a89</anchor>
      <arglist>(const SharedPtr&lt; Y &gt; &amp;x)</arglist>
    </member>
    <member kind="function">
      <type>SharedPtr &amp;</type>
      <name>operator=</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a5370427758b9147ab6cc347b12b011bf</anchor>
      <arglist>(const SharedPtr &amp;x)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>reset</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a0cce56dc2d636ba354b63d30061fa072</anchor>
      <arglist>(FillableMat *p=0)</arglist>
    </member>
    <member kind="function">
      <type>FillableMat &amp;</type>
      <name>operator*</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>aa65e5c5fb01b8b3c6e820302b1ca5424</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>FillableMat *</type>
      <name>operator-&gt;</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a1d18d5e137d8a184d5f1bdc1913d10a8</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>FillableMat *</type>
      <name>get</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a0296a552885744dbf7c81e29be463e28</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>long</type>
      <name>use_count</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a26d79923e382b42cb2a8fab468cad7ea</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>unique</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a653b3e338f9a87623c875b51ff932cc8</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>share</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>ad27873719f16e17c9057355130079499</anchor>
      <arglist>(FillableMat *xpointer, long *xcount)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>dispose</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>ac25cf9cbd9843804de943be3bb2670df</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>SharedPtr&lt; FiniteElementData &gt;</name>
    <filename>classfei_1_1SharedPtr.html</filename>
    <member kind="typedef">
      <type>FiniteElementData</type>
      <name>element_type</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>ac4770c63a5fb9297d0d0414afe79117c</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SharedPtr</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>afad2a2441a6f7907dd4d249dfd813398</anchor>
      <arglist>(FiniteElementData *p)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SharedPtr</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>aa04f35878be5d09a9e7212992936a16b</anchor>
      <arglist>(const SharedPtr&lt; Y &gt; &amp;x)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SharedPtr</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a9874d9dc7e02ff82a87a5ee45b2ea74d</anchor>
      <arglist>(const SharedPtr &amp;x)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~SharedPtr</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>ac6c248f87712f6afafa28fcbcdb53987</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>SharedPtr &amp;</type>
      <name>operator=</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a3345b70111b88d517dbfe6991d197a89</anchor>
      <arglist>(const SharedPtr&lt; Y &gt; &amp;x)</arglist>
    </member>
    <member kind="function">
      <type>SharedPtr &amp;</type>
      <name>operator=</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a5370427758b9147ab6cc347b12b011bf</anchor>
      <arglist>(const SharedPtr &amp;x)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>reset</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a0cce56dc2d636ba354b63d30061fa072</anchor>
      <arglist>(FiniteElementData *p=0)</arglist>
    </member>
    <member kind="function">
      <type>FiniteElementData &amp;</type>
      <name>operator*</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>aa65e5c5fb01b8b3c6e820302b1ca5424</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>FiniteElementData *</type>
      <name>operator-&gt;</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a1d18d5e137d8a184d5f1bdc1913d10a8</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>FiniteElementData *</type>
      <name>get</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a0296a552885744dbf7c81e29be463e28</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>long</type>
      <name>use_count</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a26d79923e382b42cb2a8fab468cad7ea</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>unique</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a653b3e338f9a87623c875b51ff932cc8</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>share</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>ad27873719f16e17c9057355130079499</anchor>
      <arglist>(FiniteElementData *xpointer, long *xcount)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>dispose</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>ac25cf9cbd9843804de943be3bb2670df</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>SharedPtr&lt; LibraryWrapper &gt;</name>
    <filename>classfei_1_1SharedPtr.html</filename>
    <member kind="typedef">
      <type>LibraryWrapper</type>
      <name>element_type</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>ac4770c63a5fb9297d0d0414afe79117c</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SharedPtr</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>afad2a2441a6f7907dd4d249dfd813398</anchor>
      <arglist>(LibraryWrapper *p)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SharedPtr</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>aa04f35878be5d09a9e7212992936a16b</anchor>
      <arglist>(const SharedPtr&lt; Y &gt; &amp;x)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SharedPtr</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a9874d9dc7e02ff82a87a5ee45b2ea74d</anchor>
      <arglist>(const SharedPtr &amp;x)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~SharedPtr</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>ac6c248f87712f6afafa28fcbcdb53987</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>SharedPtr &amp;</type>
      <name>operator=</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a3345b70111b88d517dbfe6991d197a89</anchor>
      <arglist>(const SharedPtr&lt; Y &gt; &amp;x)</arglist>
    </member>
    <member kind="function">
      <type>SharedPtr &amp;</type>
      <name>operator=</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a5370427758b9147ab6cc347b12b011bf</anchor>
      <arglist>(const SharedPtr &amp;x)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>reset</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a0cce56dc2d636ba354b63d30061fa072</anchor>
      <arglist>(LibraryWrapper *p=0)</arglist>
    </member>
    <member kind="function">
      <type>LibraryWrapper &amp;</type>
      <name>operator*</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>aa65e5c5fb01b8b3c6e820302b1ca5424</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>LibraryWrapper *</type>
      <name>operator-&gt;</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a1d18d5e137d8a184d5f1bdc1913d10a8</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>LibraryWrapper *</type>
      <name>get</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a0296a552885744dbf7c81e29be463e28</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>long</type>
      <name>use_count</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a26d79923e382b42cb2a8fab468cad7ea</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>unique</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a653b3e338f9a87623c875b51ff932cc8</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>share</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>ad27873719f16e17c9057355130079499</anchor>
      <arglist>(LibraryWrapper *xpointer, long *xcount)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>dispose</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>ac25cf9cbd9843804de943be3bb2670df</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>SharedPtr&lt; LinearSystemCore &gt;</name>
    <filename>classfei_1_1SharedPtr.html</filename>
    <member kind="typedef">
      <type>LinearSystemCore</type>
      <name>element_type</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>ac4770c63a5fb9297d0d0414afe79117c</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SharedPtr</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>afad2a2441a6f7907dd4d249dfd813398</anchor>
      <arglist>(LinearSystemCore *p)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SharedPtr</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>aa04f35878be5d09a9e7212992936a16b</anchor>
      <arglist>(const SharedPtr&lt; Y &gt; &amp;x)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SharedPtr</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a9874d9dc7e02ff82a87a5ee45b2ea74d</anchor>
      <arglist>(const SharedPtr &amp;x)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~SharedPtr</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>ac6c248f87712f6afafa28fcbcdb53987</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>SharedPtr &amp;</type>
      <name>operator=</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a3345b70111b88d517dbfe6991d197a89</anchor>
      <arglist>(const SharedPtr&lt; Y &gt; &amp;x)</arglist>
    </member>
    <member kind="function">
      <type>SharedPtr &amp;</type>
      <name>operator=</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a5370427758b9147ab6cc347b12b011bf</anchor>
      <arglist>(const SharedPtr &amp;x)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>reset</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a0cce56dc2d636ba354b63d30061fa072</anchor>
      <arglist>(LinearSystemCore *p=0)</arglist>
    </member>
    <member kind="function">
      <type>LinearSystemCore &amp;</type>
      <name>operator*</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>aa65e5c5fb01b8b3c6e820302b1ca5424</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>LinearSystemCore *</type>
      <name>operator-&gt;</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a1d18d5e137d8a184d5f1bdc1913d10a8</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>LinearSystemCore *</type>
      <name>get</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a0296a552885744dbf7c81e29be463e28</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>long</type>
      <name>use_count</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a26d79923e382b42cb2a8fab468cad7ea</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>unique</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a653b3e338f9a87623c875b51ff932cc8</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>share</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>ad27873719f16e17c9057355130079499</anchor>
      <arglist>(LinearSystemCore *xpointer, long *xcount)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>dispose</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>ac25cf9cbd9843804de943be3bb2670df</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>SharedPtr&lt; snl_fei::snl_fei::Broker &gt;</name>
    <filename>classfei_1_1SharedPtr.html</filename>
    <member kind="typedef">
      <type>snl_fei::snl_fei::Broker</type>
      <name>element_type</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>ac4770c63a5fb9297d0d0414afe79117c</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SharedPtr</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>afad2a2441a6f7907dd4d249dfd813398</anchor>
      <arglist>(snl_fei::snl_fei::Broker *p)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SharedPtr</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>aa04f35878be5d09a9e7212992936a16b</anchor>
      <arglist>(const SharedPtr&lt; Y &gt; &amp;x)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SharedPtr</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a9874d9dc7e02ff82a87a5ee45b2ea74d</anchor>
      <arglist>(const SharedPtr &amp;x)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~SharedPtr</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>ac6c248f87712f6afafa28fcbcdb53987</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>SharedPtr &amp;</type>
      <name>operator=</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a3345b70111b88d517dbfe6991d197a89</anchor>
      <arglist>(const SharedPtr&lt; Y &gt; &amp;x)</arglist>
    </member>
    <member kind="function">
      <type>SharedPtr &amp;</type>
      <name>operator=</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a5370427758b9147ab6cc347b12b011bf</anchor>
      <arglist>(const SharedPtr &amp;x)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>reset</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a0cce56dc2d636ba354b63d30061fa072</anchor>
      <arglist>(snl_fei::snl_fei::Broker *p=0)</arglist>
    </member>
    <member kind="function">
      <type>snl_fei::snl_fei::Broker &amp;</type>
      <name>operator*</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>aa65e5c5fb01b8b3c6e820302b1ca5424</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>snl_fei::snl_fei::Broker *</type>
      <name>operator-&gt;</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a1d18d5e137d8a184d5f1bdc1913d10a8</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>snl_fei::snl_fei::Broker *</type>
      <name>get</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a0296a552885744dbf7c81e29be463e28</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>long</type>
      <name>use_count</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a26d79923e382b42cb2a8fab468cad7ea</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>unique</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>a653b3e338f9a87623c875b51ff932cc8</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>share</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>ad27873719f16e17c9057355130079499</anchor>
      <arglist>(snl_fei::snl_fei::Broker *xpointer, long *xcount)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>dispose</name>
      <anchorfile>classfei_1_1SharedPtr.html</anchorfile>
      <anchor>ac25cf9cbd9843804de943be3bb2670df</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>SlaveVariable</name>
    <filename>classSlaveVariable.html</filename>
    <member kind="function">
      <type></type>
      <name>SlaveVariable</name>
      <anchorfile>classSlaveVariable.html</anchorfile>
      <anchor>a0914bd048c4143ada71ffa6ffa9483d6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~SlaveVariable</name>
      <anchorfile>classSlaveVariable.html</anchorfile>
      <anchor>a757d6916b0eb247ffc7a7c7f57d82603</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>SNL_FEI_Structure</name>
    <filename>classSNL__FEI__Structure.html</filename>
    <base>Lookup</base>
    <member kind="function">
      <type></type>
      <name>SNL_FEI_Structure</name>
      <anchorfile>classSNL__FEI__Structure.html</anchorfile>
      <anchor>ab1504cd634df845871a606ded85298bd</anchor>
      <arglist>(MPI_Comm comm)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~SNL_FEI_Structure</name>
      <anchorfile>classSNL__FEI__Structure.html</anchorfile>
      <anchor>a33ae39d92ffdd18b3600d7352c8666d5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>parameters</name>
      <anchorfile>classSNL__FEI__Structure.html</anchorfile>
      <anchor>a20f2933eb5c4382f59edb6c1d145bfb3</anchor>
      <arglist>(int numParams, const char *const *paramStrings)</arglist>
    </member>
    <member kind="function">
      <type>const int *</type>
      <name>getFieldIDsPtr</name>
      <anchorfile>classSNL__FEI__Structure.html</anchorfile>
      <anchor>a83175187671f3097043c0629efc87709</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const int *</type>
      <name>getFieldSizesPtr</name>
      <anchorfile>classSNL__FEI__Structure.html</anchorfile>
      <anchor>a57c6b8867582f8ea03726fdff10f21ed</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getNumFields</name>
      <anchorfile>classSNL__FEI__Structure.html</anchorfile>
      <anchor>a645e6ab55c3aa5de5e955d7b268c0afe</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getFieldSize</name>
      <anchorfile>classSNL__FEI__Structure.html</anchorfile>
      <anchor>a36cec5c39de493776f7c4b407b319c23</anchor>
      <arglist>(int fieldID)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isInLocalElement</name>
      <anchorfile>classSNL__FEI__Structure.html</anchorfile>
      <anchor>ac5ba9c7c0b0de1080e3e2784029e9013</anchor>
      <arglist>(int nodeNumber)</arglist>
    </member>
    <member kind="function">
      <type>const int *</type>
      <name>getNumFieldsPerNode</name>
      <anchorfile>classSNL__FEI__Structure.html</anchorfile>
      <anchor>ac21b71e8856ca22c5219627a1577b210</anchor>
      <arglist>(GlobalID blockID)</arglist>
    </member>
    <member kind="function">
      <type>const int *const *</type>
      <name>getFieldIDsTable</name>
      <anchorfile>classSNL__FEI__Structure.html</anchorfile>
      <anchor>a8385280567c16ffdd232d86b3c12110a</anchor>
      <arglist>(GlobalID blockID)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getEqnNumber</name>
      <anchorfile>classSNL__FEI__Structure.html</anchorfile>
      <anchor>a9a52d909e3af7ad1bdca457a49afadac</anchor>
      <arglist>(int nodeNumber, int fieldID)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getOwnerProcForEqn</name>
      <anchorfile>classSNL__FEI__Structure.html</anchorfile>
      <anchor>aea327741b314343002786146f70f0c9f</anchor>
      <arglist>(int eqn)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getNumElemBlocks</name>
      <anchorfile>classSNL__FEI__Structure.html</anchorfile>
      <anchor>a2ec21504575dfdfcd9ed5d00b818e23b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const GlobalID *</type>
      <name>getElemBlockIDs</name>
      <anchorfile>classSNL__FEI__Structure.html</anchorfile>
      <anchor>a2202ba1d402b5e17f1c290e211dd21ed</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>getElemBlockInfo</name>
      <anchorfile>classSNL__FEI__Structure.html</anchorfile>
      <anchor>a7c5dcb05031b48e4a33bbe2356886ee8</anchor>
      <arglist>(GlobalID blockID, int &amp;interleaveStrategy, int &amp;lumpingStrategy, int &amp;numElemDOF, int &amp;numElements, int &amp;numNodesPerElem, int &amp;numEqnsPerElem)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getBlockDescriptor_index</name>
      <anchorfile>classSNL__FEI__Structure.html</anchorfile>
      <anchor>a4e3426941a60d83062c39faebe9dddfd</anchor>
      <arglist>(int index, BlockDescriptor *&amp;block)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getIndexOfBlock</name>
      <anchorfile>classSNL__FEI__Structure.html</anchorfile>
      <anchor>af91a99742149b9e2039dcbdae560e9cd</anchor>
      <arglist>(GlobalID blockID) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getBlockID</name>
      <anchorfile>classSNL__FEI__Structure.html</anchorfile>
      <anchor>a535375006fdbbabf21d71673bb9c19d6</anchor>
      <arglist>(unsigned index) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getNumSharedNodes</name>
      <anchorfile>classSNL__FEI__Structure.html</anchorfile>
      <anchor>a962a9dfdfb2f6b974302f9ba4dfb5b17</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const int *</type>
      <name>getSharedNodeNumbers</name>
      <anchorfile>classSNL__FEI__Structure.html</anchorfile>
      <anchor>a17419bb83d7f3bd5fad06f7764c56d12</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const int *</type>
      <name>getSharedNodeProcs</name>
      <anchorfile>classSNL__FEI__Structure.html</anchorfile>
      <anchor>a99b581049407040bb5f2c5d54789d7d9</anchor>
      <arglist>(int nodeNumber)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getNumSharingProcs</name>
      <anchorfile>classSNL__FEI__Structure.html</anchorfile>
      <anchor>a61de12edcb9f10308bb64a1f99dab183</anchor>
      <arglist>(int nodeNumber)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getNumSubdomains</name>
      <anchorfile>classSNL__FEI__Structure.html</anchorfile>
      <anchor>a629574305186b65d70099b99e53c2717</anchor>
      <arglist>(int nodeNumber)</arglist>
    </member>
    <member kind="function">
      <type>int *</type>
      <name>getSubdomainList</name>
      <anchorfile>classSNL__FEI__Structure.html</anchorfile>
      <anchor>abed7427ba5e0a5bf3e3b94c3546d39ca</anchor>
      <arglist>(int nodeNumber)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getAssociatedNodeNumber</name>
      <anchorfile>classSNL__FEI__Structure.html</anchorfile>
      <anchor>a2d4a1367a97a4d0c5e832904a795653a</anchor>
      <arglist>(int eqnNumber)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getAssociatedFieldID</name>
      <anchorfile>classSNL__FEI__Structure.html</anchorfile>
      <anchor>a73ba13486830e9c9b6bacd7ae26a6d5b</anchor>
      <arglist>(int eqnNumber)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isExactlyBlkEqn</name>
      <anchorfile>classSNL__FEI__Structure.html</anchorfile>
      <anchor>aab80b7eda371c93d4f456d5950ee274c</anchor>
      <arglist>(int ptEqn)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ptEqnToBlkEqn</name>
      <anchorfile>classSNL__FEI__Structure.html</anchorfile>
      <anchor>a900bb07f3d635e2e582772466a0230bc</anchor>
      <arglist>(int ptEqn)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getOffsetIntoBlkEqn</name>
      <anchorfile>classSNL__FEI__Structure.html</anchorfile>
      <anchor>a04e13604d0c2ea37fee18ec67b600a24</anchor>
      <arglist>(int blkEqn, int ptEqn)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getBlkEqnSize</name>
      <anchorfile>classSNL__FEI__Structure.html</anchorfile>
      <anchor>a6bf2d21aa9d48a61cb3eb32908a0a5ee</anchor>
      <arglist>(int blkEqn)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isSlaveEqn</name>
      <anchorfile>classSNL__FEI__Structure.html</anchorfile>
      <anchor>a20f01a1e8bd714435535d670c38c01cd</anchor>
      <arglist>(int eqn)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>translateToReducedEqn</name>
      <anchorfile>classSNL__FEI__Structure.html</anchorfile>
      <anchor>aebf44063741a0bc4fe4a52563f33e309</anchor>
      <arglist>(int eqn, int &amp;reducedEqn)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>translateToReducedEqns</name>
      <anchorfile>classSNL__FEI__Structure.html</anchorfile>
      <anchor>a2328b0e4ae8aed16fa725a91a4228612</anchor>
      <arglist>(EqnCommMgr &amp;eqnCommMgr)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>translateToReducedEqns</name>
      <anchorfile>classSNL__FEI__Structure.html</anchorfile>
      <anchor>abac74ca0246577248213a6be5fcbd07f</anchor>
      <arglist>(EqnBuffer &amp;eqnBuf)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>translateToReducedEqns</name>
      <anchorfile>classSNL__FEI__Structure.html</anchorfile>
      <anchor>a4dea70f1b95d94bf88ce9bd9fc6da890</anchor>
      <arglist>(ProcEqns &amp;procEqns)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>translateMatToReducedEqns</name>
      <anchorfile>classSNL__FEI__Structure.html</anchorfile>
      <anchor>a01274abfbda479e3dd65fbfd92ac4011</anchor>
      <arglist>(fei::CSRMat &amp;mat)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>translateFromReducedEqn</name>
      <anchorfile>classSNL__FEI__Structure.html</anchorfile>
      <anchor>a85629ec79ed54aed62ae4669e411ae81</anchor>
      <arglist>(int reducedEqn)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getMasterEqnNumbers</name>
      <anchorfile>classSNL__FEI__Structure.html</anchorfile>
      <anchor>abe85029b0e384afe96750695ff605f6c</anchor>
      <arglist>(int slaveEqn, std::vector&lt; int &gt; *&amp;masterEqns)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getMasterEqnCoefs</name>
      <anchorfile>classSNL__FEI__Structure.html</anchorfile>
      <anchor>a9b4c954ba0c952418d725e84bbcba1d6</anchor>
      <arglist>(int slaveEqn, std::vector&lt; double &gt; *&amp;masterCoefs)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getMasterEqnRHS</name>
      <anchorfile>classSNL__FEI__Structure.html</anchorfile>
      <anchor>a0eacbda36aab4d045913b2cad3b14b19</anchor>
      <arglist>(int slaveEqn, double &amp;rhsValue)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>fei::Solver</name>
    <filename>classfei_1_1Solver.html</filename>
    <class kind="class">fei::Solver::Factory</class>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~Solver</name>
      <anchorfile>classfei_1_1Solver.html</anchorfile>
      <anchor>a74fe41cb2d37ed02da2f3399445a8597</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>solve</name>
      <anchorfile>classfei_1_1Solver.html</anchorfile>
      <anchor>aa14bb748eb219c5def8bcf5fe01ad3c6</anchor>
      <arglist>(fei::LinearSystem *linearSystem, fei::Matrix *preconditioningMatrix, const fei::ParameterSet &amp;parameterSet, int &amp;iterationsTaken, int &amp;status)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>fei::SparseRowGraph</name>
    <filename>classfei_1_1SparseRowGraph.html</filename>
    <member kind="function">
      <type></type>
      <name>SparseRowGraph</name>
      <anchorfile>classfei_1_1SparseRowGraph.html</anchorfile>
      <anchor>a4f652c7ffdb6fa2d897680208c2e7607</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SparseRowGraph</name>
      <anchorfile>classfei_1_1SparseRowGraph.html</anchorfile>
      <anchor>a3819e771a499f3e923616df198136d40</anchor>
      <arglist>(const SparseRowGraph &amp;src)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~SparseRowGraph</name>
      <anchorfile>classfei_1_1SparseRowGraph.html</anchorfile>
      <anchor>adfaba11469b956c853364bfdb07ba07a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator==</name>
      <anchorfile>classfei_1_1SparseRowGraph.html</anchorfile>
      <anchor>a890ada4e4132cc2de0b44c7b98e97029</anchor>
      <arglist>(const fei::SparseRowGraph &amp;othergraph) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator!=</name>
      <anchorfile>classfei_1_1SparseRowGraph.html</anchorfile>
      <anchor>a604a5d28cde1ac758b99057ab3a68430</anchor>
      <arglist>(const fei::SparseRowGraph &amp;othergraph) const </arglist>
    </member>
    <member kind="variable">
      <type>std::vector&lt; int &gt;</type>
      <name>rowNumbers</name>
      <anchorfile>classfei_1_1SparseRowGraph.html</anchorfile>
      <anchor>a2a0db79f162f577178295f3e219cace7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::vector&lt; int &gt;</type>
      <name>rowOffsets</name>
      <anchorfile>classfei_1_1SparseRowGraph.html</anchorfile>
      <anchor>a689957ec963f5da2bfa5005bb851138b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::vector&lt; int &gt;</type>
      <name>packedColumnIndices</name>
      <anchorfile>classfei_1_1SparseRowGraph.html</anchorfile>
      <anchor>a2a9930c722cf23e72046a0357de05d5c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>blockEntries</name>
      <anchorfile>classfei_1_1SparseRowGraph.html</anchorfile>
      <anchor>a4c02a1b991ce71cc689c3e08819df7d5</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>snl_fei::SubdMsgHandler</name>
    <filename>classsnl__fei_1_1SubdMsgHandler.html</filename>
    <base>MessageHandler&lt; int &gt;</base>
    <member kind="function">
      <type></type>
      <name>SubdMsgHandler</name>
      <anchorfile>classsnl__fei_1_1SubdMsgHandler.html</anchorfile>
      <anchor>ad9a9d80f1769cf3460f74224d0e63bb3</anchor>
      <arglist>(RecordCollection *recordCollection, fei::SharedIDs&lt; int &gt; *sharedIDTable, fei::SharedIDs&lt; int &gt; *subdomainIDTable)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~SubdMsgHandler</name>
      <anchorfile>classsnl__fei_1_1SubdMsgHandler.html</anchorfile>
      <anchor>a4393a2444f44ea7c56dcec312cc9cab9</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>std::vector&lt; int &gt; &amp;</type>
      <name>getSendProcs</name>
      <anchorfile>classsnl__fei_1_1SubdMsgHandler.html</anchorfile>
      <anchor>a47b758dbd7fc6962a431c4a74f0bb405</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>std::vector&lt; int &gt; &amp;</type>
      <name>getRecvProcs</name>
      <anchorfile>classsnl__fei_1_1SubdMsgHandler.html</anchorfile>
      <anchor>a06bde02b77c7df040bde8672dff7614a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getSendMessageLength</name>
      <anchorfile>classsnl__fei_1_1SubdMsgHandler.html</anchorfile>
      <anchor>addf4047aaf7224e24268d262a935c406</anchor>
      <arglist>(int destProc, int &amp;messageLength)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getSendMessage</name>
      <anchorfile>classsnl__fei_1_1SubdMsgHandler.html</anchorfile>
      <anchor>a0838400ca9e7d5f2305298d321751ba4</anchor>
      <arglist>(int destProc, std::vector&lt; int &gt; &amp;message)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>processRecvMessage</name>
      <anchorfile>classsnl__fei_1_1SubdMsgHandler.html</anchorfile>
      <anchor>ae442d424eac7408a53c1de8238e6ed7f</anchor>
      <arglist>(int srcProc, std::vector&lt; int &gt; &amp;message)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setSendPattern</name>
      <anchorfile>classsnl__fei_1_1SubdMsgHandler.html</anchorfile>
      <anchor>af2fa8ea3bd10c5ce984f50f6d205342e</anchor>
      <arglist>(fei::comm_map *pattern)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setRecvPattern</name>
      <anchorfile>classsnl__fei_1_1SubdMsgHandler.html</anchorfile>
      <anchor>a83961e95a6f04007988187ce30e81beb</anchor>
      <arglist>(fei::comm_map *pattern)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>test_Algebraic</name>
    <filename>classtest__Algebraic.html</filename>
    <base>tester</base>
    <member kind="function">
      <type>const char *</type>
      <name>getName</name>
      <anchorfile>classtest__Algebraic.html</anchorfile>
      <anchor>a8123649e2ec558ae3a3e30ac5d20a82d</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>test_AztecWrappers</name>
    <filename>classtest__AztecWrappers.html</filename>
    <base>tester</base>
    <member kind="function">
      <type>const char *</type>
      <name>getName</name>
      <anchorfile>classtest__AztecWrappers.html</anchorfile>
      <anchor>a0bfe8aa09ef5e4f3911533191ae4b3b8</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>test_benchmarks</name>
    <filename>classtest__benchmarks.html</filename>
    <base>tester</base>
    <member kind="function">
      <type>const char *</type>
      <name>getName</name>
      <anchorfile>classtest__benchmarks.html</anchorfile>
      <anchor>a09aad7abc8e504d3a2828734c07b9932</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>test_Database</name>
    <filename>classtest__Database.html</filename>
    <base>tester</base>
    <member kind="function">
      <type>const char *</type>
      <name>getName</name>
      <anchorfile>classtest__Database.html</anchorfile>
      <anchor>ad2e24e985c823e61b6ac4955a747ad9d</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>test_EqnCommMgr</name>
    <filename>classtest__EqnCommMgr.html</filename>
    <base>tester</base>
    <member kind="function">
      <type>const char *</type>
      <name>getName</name>
      <anchorfile>classtest__EqnCommMgr.html</anchorfile>
      <anchor>a58e7ef7660b739b3536422347bb0acfc</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>test_Factory</name>
    <filename>classtest__Factory.html</filename>
    <base>tester</base>
    <member kind="function">
      <type>const char *</type>
      <name>getName</name>
      <anchorfile>classtest__Factory.html</anchorfile>
      <anchor>af66a9d12ba44eee65c8749bff7e32f53</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>test_FEI_Impl</name>
    <filename>classtest__FEI__Impl.html</filename>
    <base>tester</base>
    <member kind="function">
      <type>const char *</type>
      <name>getName</name>
      <anchorfile>classtest__FEI__Impl.html</anchorfile>
      <anchor>a04754fbb3e11ec243fcc4a386f053875</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>test_FEI_Implementation</name>
    <filename>classtest__FEI__Implementation.html</filename>
    <base>tester</base>
    <member kind="function">
      <type>const char *</type>
      <name>getName</name>
      <anchorfile>classtest__FEI__Implementation.html</anchorfile>
      <anchor>ab08cec68fc689d3376e2ffe17383bc0a</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>test_LinearSystem</name>
    <filename>classtest__LinearSystem.html</filename>
    <base>tester</base>
    <member kind="function">
      <type>const char *</type>
      <name>getName</name>
      <anchorfile>classtest__LinearSystem.html</anchorfile>
      <anchor>a94ca4f43a0122364407452e42cf39796</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>test_Matrix</name>
    <filename>classtest__Matrix.html</filename>
    <base>tester</base>
    <member kind="function">
      <type>const char *</type>
      <name>getName</name>
      <anchorfile>classtest__Matrix.html</anchorfile>
      <anchor>a4c908707475c71737b06e6c6da7b11b0</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>test_MatrixGraph</name>
    <filename>classtest__MatrixGraph.html</filename>
    <base>tester</base>
    <member kind="function">
      <type>const char *</type>
      <name>getName</name>
      <anchorfile>classtest__MatrixGraph.html</anchorfile>
      <anchor>ae8c2491c5e00acef4c72c52f35ee012c</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>test_misc</name>
    <filename>classtest__misc.html</filename>
    <base>tester</base>
    <member kind="function">
      <type>const char *</type>
      <name>getName</name>
      <anchorfile>classtest__misc.html</anchorfile>
      <anchor>a951197f188df5d3be401b9cc8823cdd0</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>test_PointBlockMap</name>
    <filename>classtest__PointBlockMap.html</filename>
    <base>tester</base>
    <member kind="function">
      <type>const char *</type>
      <name>getName</name>
      <anchorfile>classtest__PointBlockMap.html</anchorfile>
      <anchor>ab1d16f034ef222a9c483f16eef2927ff</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>test_Set</name>
    <filename>classtest__Set.html</filename>
    <base>tester</base>
    <member kind="function">
      <type>const char *</type>
      <name>getName</name>
      <anchorfile>classtest__Set.html</anchorfile>
      <anchor>aa08a142bad73385ca89e0d0f0cf0c009</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>test_SNL_FEI_Structure</name>
    <filename>classtest__SNL__FEI__Structure.html</filename>
    <base>tester</base>
    <member kind="function">
      <type>const char *</type>
      <name>getName</name>
      <anchorfile>classtest__SNL__FEI__Structure.html</anchorfile>
      <anchor>aabc17457624758c4caae789d7ce8c93c</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>test_Utils</name>
    <filename>classtest__Utils.html</filename>
    <base>tester</base>
    <member kind="function">
      <type>const char *</type>
      <name>getName</name>
      <anchorfile>classtest__Utils.html</anchorfile>
      <anchor>a217980fad82fa60424a1aa383c914ee1</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>test_Vector</name>
    <filename>classtest__Vector.html</filename>
    <base>tester</base>
    <member kind="function">
      <type>const char *</type>
      <name>getName</name>
      <anchorfile>classtest__Vector.html</anchorfile>
      <anchor>ad0c2cee2b6b9c28fc965060ff8380c50</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>test_VectorSpace</name>
    <filename>classtest__VectorSpace.html</filename>
    <base>tester</base>
    <member kind="function">
      <type>const char *</type>
      <name>getName</name>
      <anchorfile>classtest__VectorSpace.html</anchorfile>
      <anchor>af5c17656b4b55039695aa860e9e2e5f2</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>testData</name>
    <filename>classtestData.html</filename>
  </compound>
  <compound kind="class">
    <name>tester</name>
    <filename>classtester.html</filename>
    <member kind="function" virtualness="pure">
      <type>virtual const char *</type>
      <name>getName</name>
      <anchorfile>classtester.html</anchorfile>
      <anchor>a5856bf4f2c6edd3ca78195e0d94d9e21</anchor>
      <arglist>()=0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>fei::Vector</name>
    <filename>classfei_1_1Vector.html</filename>
    <class kind="class">fei::Vector::Factory</class>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~Vector</name>
      <anchorfile>classfei_1_1Vector.html</anchorfile>
      <anchor>ab5170c62a9ef27cd61ed1710ebdd468b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual const char *</type>
      <name>typeName</name>
      <anchorfile>classfei_1_1Vector.html</anchorfile>
      <anchor>a646d7d15a8985fde8a419a5affba4a25</anchor>
      <arglist>() const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>putScalar</name>
      <anchorfile>classfei_1_1Vector.html</anchorfile>
      <anchor>a26e398a85c1a43dc29f402b77ccfae4c</anchor>
      <arglist>(double scalar)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>sumIn</name>
      <anchorfile>classfei_1_1Vector.html</anchorfile>
      <anchor>a95fe5767de21b5e5d2177435b4a67bdf</anchor>
      <arglist>(int numValues, const int *indices, const double *values, int vectorIndex=0)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>copyIn</name>
      <anchorfile>classfei_1_1Vector.html</anchorfile>
      <anchor>ae5436675ddc7a729c19bbee787a54d3f</anchor>
      <arglist>(int numValues, const int *indices, const double *values, int vectorIndex=0)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>copyOut</name>
      <anchorfile>classfei_1_1Vector.html</anchorfile>
      <anchor>a2456ccb68c15cb2610ee17ee31d17238</anchor>
      <arglist>(int numValues, const int *indices, double *values, int vectorIndex=0) const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>update</name>
      <anchorfile>classfei_1_1Vector.html</anchorfile>
      <anchor>a4739b9e210b77f57acc2adb943005ca9</anchor>
      <arglist>(double a, const fei::Vector *x, double b)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>scatterToOverlap</name>
      <anchorfile>classfei_1_1Vector.html</anchorfile>
      <anchor>a4616c794d14579d41dc5dcd8171ebfc5</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>setCommSizes</name>
      <anchorfile>classfei_1_1Vector.html</anchorfile>
      <anchor>a8d9b01199cac870030ab831f7b2e9d95</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>gatherFromOverlap</name>
      <anchorfile>classfei_1_1Vector.html</anchorfile>
      <anchor>aa57af15909a09444343820f2418d70b2</anchor>
      <arglist>(bool accumulate=true)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual fei::SharedPtr&lt; fei::VectorSpace &gt;</type>
      <name>getVectorSpace</name>
      <anchorfile>classfei_1_1Vector.html</anchorfile>
      <anchor>a57233dbab9e1c03c6cbdd3294e4ab1c1</anchor>
      <arglist>() const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>setVectorSpace</name>
      <anchorfile>classfei_1_1Vector.html</anchorfile>
      <anchor>a8ebac51cb111c1faeba42a596b68541d</anchor>
      <arglist>(fei::SharedPtr&lt; fei::VectorSpace &gt; vecSpace)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>sumInFieldData</name>
      <anchorfile>classfei_1_1Vector.html</anchorfile>
      <anchor>a6d028a2d78d8ceeb1e39837848e1c31e</anchor>
      <arglist>(int fieldID, int idType, int numIDs, const int *IDs, const double *data, int vectorIndex=0)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>copyInFieldData</name>
      <anchorfile>classfei_1_1Vector.html</anchorfile>
      <anchor>af2d07fd2295ef673eccfb9b0ffc14bc9</anchor>
      <arglist>(int fieldID, int idType, int numIDs, const int *IDs, const double *data, int vectorIndex=0)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>copyOutFieldData</name>
      <anchorfile>classfei_1_1Vector.html</anchorfile>
      <anchor>ab5a4a82e3ac54236661f0684775c0f51</anchor>
      <arglist>(int fieldID, int idType, int numIDs, const int *IDs, double *data, int vectorIndex=0)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>writeToFile</name>
      <anchorfile>classfei_1_1Vector.html</anchorfile>
      <anchor>a9ef6cdc400b243b20aefc9d6ec43dab3</anchor>
      <arglist>(const char *filename, bool matrixMarketFormat=true)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>writeToStream</name>
      <anchorfile>classfei_1_1Vector.html</anchorfile>
      <anchor>a9a16f030561d4d28b06eded1096189d2</anchor>
      <arglist>(FEI_OSTREAM &amp;ostrm, bool matrixMarketFormat=true)=0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>fei::Vector_core</name>
    <filename>classfei_1_1Vector__core.html</filename>
    <base protection="protected">fei::Logger</base>
    <member kind="function">
      <type></type>
      <name>Vector_core</name>
      <anchorfile>classfei_1_1Vector__core.html</anchorfile>
      <anchor>a83be8c0a7e1801b53d18dd671976f7ae</anchor>
      <arglist>(fei::SharedPtr&lt; fei::VectorSpace &gt; vecSpace, int numLocalEqns)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~Vector_core</name>
      <anchorfile>classfei_1_1Vector__core.html</anchorfile>
      <anchor>a92673f18d5c651e4d17301c5c36b5426</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>copyOut</name>
      <anchorfile>classfei_1_1Vector__core.html</anchorfile>
      <anchor>a546ac1ce3c37cac81f9b23c55a02e04c</anchor>
      <arglist>(int numValues, const int *indices, double *values, int vectorIndex=0) const </arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>sumIntoFEVector</name>
      <anchorfile>classfei_1_1Vector__core.html</anchorfile>
      <anchor>a30a3edc7af572ad44b1351b4e6487013</anchor>
      <arglist>(int blockID, int connOffset, int numNodes, const int *nodeNumbers, const int *numIndicesPerNode, const int *dof_ids, const double *values)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>copyOut_FE</name>
      <anchorfile>classfei_1_1Vector__core.html</anchorfile>
      <anchor>a9785973a1fe61cb986864c95942af825</anchor>
      <arglist>(int nodeNumber, int dofOffset, double &amp;value)=0</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>giveToVector</name>
      <anchorfile>classfei_1_1Vector__core.html</anchorfile>
      <anchor>a65a06788bdc0b52c17e2e5134b663af6</anchor>
      <arglist>(int numValues, const int *indices, const double *values, bool sumInto=true, int vectorIndex=0)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>scatterToOverlap</name>
      <anchorfile>classfei_1_1Vector__core.html</anchorfile>
      <anchor>ac181a7db28274d03a78032da1498a324</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setOverlap</name>
      <anchorfile>classfei_1_1Vector__core.html</anchorfile>
      <anchor>aae29423e9f5e27c4bff41170a621d66f</anchor>
      <arglist>(int numRemoteEqns=0, const int *remoteEqns=NULL)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>int</type>
      <name>assembleFieldData</name>
      <anchorfile>classfei_1_1Vector__core.html</anchorfile>
      <anchor>ae52cd981bef9279a94a0f0dc4cd11e67</anchor>
      <arglist>(int fieldID, int idType, int numIDs, const int *IDs, const double *data, bool sumInto=true, int vectorIndex=0)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual int</type>
      <name>gatherFromOverlap</name>
      <anchorfile>classfei_1_1Vector__core.html</anchorfile>
      <anchor>a3e9673609640c6127599d95bbf2bef20</anchor>
      <arglist>(bool accumulate=true)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual int</type>
      <name>copyOutFieldData</name>
      <anchorfile>classfei_1_1Vector__core.html</anchorfile>
      <anchor>aca7bdac20e2ff5f51c8a8d6e62ce9a00</anchor>
      <arglist>(int fieldID, int idType, int numIDs, const int *IDs, double *data, int vectorIndex=0)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual int</type>
      <name>giveToUnderlyingVector</name>
      <anchorfile>classfei_1_1Vector__core.html</anchorfile>
      <anchor>a8c4169d6a9739d365f5fb83c1d668132</anchor>
      <arglist>(int numValues, const int *indices, const double *values, bool sumInto=true, int vectorIndex=0)=0</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual int</type>
      <name>copyOutOfUnderlyingVector</name>
      <anchorfile>classfei_1_1Vector__core.html</anchorfile>
      <anchor>aae32243e68fde8e03f95dc93558cc22e</anchor>
      <arglist>(int numValues, const int *indices, double *values, int vectorIndex=0) const  =0</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual int</type>
      <name>writeToFile</name>
      <anchorfile>classfei_1_1Vector__core.html</anchorfile>
      <anchor>a6760cbf62f70f4e1a1ea512063d1fc51</anchor>
      <arglist>(const char *filename, bool matrixMarketFormat=true)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual int</type>
      <name>writeToStream</name>
      <anchorfile>classfei_1_1Vector__core.html</anchorfile>
      <anchor>a9855b2af2dcbce2c80de16f5fc1690e9</anchor>
      <arglist>(FEI_OSTREAM &amp;ostrm, bool matrixMarketFormat=true)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>fei::SharedPtr&lt; fei::VectorSpace &gt;</type>
      <name>get_vector_space</name>
      <anchorfile>classfei_1_1Vector__core.html</anchorfile>
      <anchor>a75427f4fc3d90d89b8de0154354a5ba9</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>set_vector_space</name>
      <anchorfile>classfei_1_1Vector__core.html</anchorfile>
      <anchor>a96333b0e32525378038cfac355624740</anchor>
      <arglist>(fei::SharedPtr&lt; fei::VectorSpace &gt; vspace)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>int</type>
      <name>firstLocalOffset</name>
      <anchorfile>classfei_1_1Vector__core.html</anchorfile>
      <anchor>aa78d69b93471304c27470e9992e89884</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>int</type>
      <name>lastLocalOffset</name>
      <anchorfile>classfei_1_1Vector__core.html</anchorfile>
      <anchor>ae43d909ae763c9ef8210d0328e9d62fc</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>std::vector&lt; int &gt; &amp;</type>
      <name>work_indices</name>
      <anchorfile>classfei_1_1Vector__core.html</anchorfile>
      <anchor>a2ea32e5c7936aed9c24efa298333e836</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>std::vector&lt; int &gt; &amp;</type>
      <name>work_indices2</name>
      <anchorfile>classfei_1_1Vector__core.html</anchorfile>
      <anchor>a69d3cea54ccbcfcfe717c3baafeedf87</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>bool</type>
      <name>haveFEVector</name>
      <anchorfile>classfei_1_1Vector__core.html</anchorfile>
      <anchor>a95e49964c158cd8886d1a9ee59ef69ae</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>setFEVector</name>
      <anchorfile>classfei_1_1Vector__core.html</anchorfile>
      <anchor>aeff5bdd2d596886bf03434b7d811d77d</anchor>
      <arglist>(bool flag)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>std::vector&lt; CSVec * &gt; &amp;</type>
      <name>remotelyOwned</name>
      <anchorfile>classfei_1_1Vector__core.html</anchorfile>
      <anchor>a30719af4406b8d7a044c355517f93f26</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>fei::Vector_Impl</name>
    <filename>classfei_1_1Vector__Impl.html</filename>
    <templarg>T</templarg>
    <base>fei::Vector</base>
    <base>fei::Vector_core</base>
    <member kind="function">
      <type></type>
      <name>Vector_Impl</name>
      <anchorfile>classfei_1_1Vector__Impl.html</anchorfile>
      <anchor>a7d6f5e879a3652e0ecf0e086567b2ad7</anchor>
      <arglist>(fei::SharedPtr&lt; fei::VectorSpace &gt; vecSpace, T *vector, int numLocalEqns, bool isSolutionVector=false, bool deleteVector=false)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~Vector_Impl</name>
      <anchorfile>classfei_1_1Vector__Impl.html</anchorfile>
      <anchor>ae06d7071ec90da718bb504c17260d679</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const char *</type>
      <name>typeName</name>
      <anchorfile>classfei_1_1Vector__Impl.html</anchorfile>
      <anchor>a8a0cb837c05396a61ef861b21021ca93</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>update</name>
      <anchorfile>classfei_1_1Vector__Impl.html</anchorfile>
      <anchor>a575c4ced1b8d722ac09ebddfcaabc7fb</anchor>
      <arglist>(double a, const fei::Vector *x, double b)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>scatterToOverlap</name>
      <anchorfile>classfei_1_1Vector__Impl.html</anchorfile>
      <anchor>aab665d2e0f8dbad80377dd4cf0d901bf</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setCommSizes</name>
      <anchorfile>classfei_1_1Vector__Impl.html</anchorfile>
      <anchor>afd04e295f304b39f5c81a78daa235bb7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>gatherFromOverlap</name>
      <anchorfile>classfei_1_1Vector__Impl.html</anchorfile>
      <anchor>a3470a6f56fb07e28f935f7ecb7b205c1</anchor>
      <arglist>(bool accumulate=true)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>putScalar</name>
      <anchorfile>classfei_1_1Vector__Impl.html</anchorfile>
      <anchor>aaff591fd0fd8836d707220de9fc256c9</anchor>
      <arglist>(double scalar)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>sumIn</name>
      <anchorfile>classfei_1_1Vector__Impl.html</anchorfile>
      <anchor>aa1355f03c6a78a1b8561ae2b99aad8ca</anchor>
      <arglist>(int numValues, const int *indices, const double *values, int vectorIndex=0)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>copyIn</name>
      <anchorfile>classfei_1_1Vector__Impl.html</anchorfile>
      <anchor>a23dc927468e11ed3ef71e1fa5728870a</anchor>
      <arglist>(int numValues, const int *indices, const double *values, int vectorIndex=0)</arglist>
    </member>
    <member kind="function">
      <type>fei::SharedPtr&lt; fei::VectorSpace &gt;</type>
      <name>getVectorSpace</name>
      <anchorfile>classfei_1_1Vector__Impl.html</anchorfile>
      <anchor>a97aa9234c1138823584df53484eb398c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setVectorSpace</name>
      <anchorfile>classfei_1_1Vector__Impl.html</anchorfile>
      <anchor>a7ca68b5310706986260149391601db3c</anchor>
      <arglist>(fei::SharedPtr&lt; fei::VectorSpace &gt; vecSpace)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>sumInFieldData</name>
      <anchorfile>classfei_1_1Vector__Impl.html</anchorfile>
      <anchor>a3120fc669b79c7ae4a765783f6908f04</anchor>
      <arglist>(int fieldID, int idType, int numIDs, const int *IDs, const double *data, int vectorIndex=0)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>copyInFieldData</name>
      <anchorfile>classfei_1_1Vector__Impl.html</anchorfile>
      <anchor>a0d54a1ad4e9491f6dce27b1b21a5e0c0</anchor>
      <arglist>(int fieldID, int idType, int numIDs, const int *IDs, const double *data, int vectorIndex=0)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>copyOutFieldData</name>
      <anchorfile>classfei_1_1Vector__Impl.html</anchorfile>
      <anchor>a7553b4a144acc9ae71c273a484c03a74</anchor>
      <arglist>(int fieldID, int idType, int numIDs, const int *IDs, double *data, int vectorIndex=0)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>writeToFile</name>
      <anchorfile>classfei_1_1Vector__Impl.html</anchorfile>
      <anchor>ab5890e5aeacfec46cd5466b0061ee61b</anchor>
      <arglist>(const char *filename, bool matrixMarketFormat=true)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>writeToStream</name>
      <anchorfile>classfei_1_1Vector__Impl.html</anchorfile>
      <anchor>acbddebd4e6fb65acd4ae92fd66a9bba6</anchor>
      <arglist>(FEI_OSTREAM &amp;ostrm, bool matrixMarketFormat=true)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setUnderlyingVector</name>
      <anchorfile>classfei_1_1Vector__Impl.html</anchorfile>
      <anchor>ac46ac5aeb8cf4fe17625d8f5da483c01</anchor>
      <arglist>(T *vec)</arglist>
    </member>
    <member kind="function">
      <type>T *</type>
      <name>getUnderlyingVector</name>
      <anchorfile>classfei_1_1Vector__Impl.html</anchorfile>
      <anchor>a53fb44ff406368760dee8a2e5fe31d45</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>copyOut</name>
      <anchorfile>classfei_1_1Vector__Impl.html</anchorfile>
      <anchor>ac7b021a13c7da457a97f3e67081cc520</anchor>
      <arglist>(int numValues, const int *indices, double *values, int vectorIndex=0) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>copyOut_FE</name>
      <anchorfile>classfei_1_1Vector__Impl.html</anchorfile>
      <anchor>a3545362e8f5ce8b4e300321d8b932a8e</anchor>
      <arglist>(int nodeNumber, int dofOffset, double &amp;value)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>fei::VectorSpace</name>
    <filename>classfei_1_1VectorSpace.html</filename>
    <base protection="private">fei::Logger</base>
    <class kind="class">fei::VectorSpace::Factory</class>
    <member kind="function">
      <type></type>
      <name>VectorSpace</name>
      <anchorfile>classfei_1_1VectorSpace.html</anchorfile>
      <anchor>a1772c97a52073c31e6eb8c61c61ff492</anchor>
      <arglist>(MPI_Comm comm, const char *name=NULL)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~VectorSpace</name>
      <anchorfile>classfei_1_1VectorSpace.html</anchorfile>
      <anchor>aed9d5305ef5067300506ca6104af1340</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setParameters</name>
      <anchorfile>classfei_1_1VectorSpace.html</anchorfile>
      <anchor>a7d32400ceadd5c846a68f81e73d0fb83</anchor>
      <arglist>(const fei::ParameterSet &amp;paramset)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>defineFields</name>
      <anchorfile>classfei_1_1VectorSpace.html</anchorfile>
      <anchor>ad0dd169d7e54315ef09ec7eaae063336</anchor>
      <arglist>(int numFields, const int *fieldIDs, const int *fieldSizes, const int *fieldTypes=NULL)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>defineIDTypes</name>
      <anchorfile>classfei_1_1VectorSpace.html</anchorfile>
      <anchor>af9d1fa5384e8645cfddb92cd0cb4489a</anchor>
      <arglist>(int numIDTypes, const int *idTypes)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>addDOFs</name>
      <anchorfile>classfei_1_1VectorSpace.html</anchorfile>
      <anchor>ab54a6225de742127e079c37e7f79e4ce</anchor>
      <arglist>(int fieldID, int idType, int numIDs, const int *IDs)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>addDOFs</name>
      <anchorfile>classfei_1_1VectorSpace.html</anchorfile>
      <anchor>a9749a10828acc681d8afe296a11238cd</anchor>
      <arglist>(int idType, int numIDs, const int *IDs)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>initSharedIDs</name>
      <anchorfile>classfei_1_1VectorSpace.html</anchorfile>
      <anchor>a611c384edbab89621be195ac7e94e155</anchor>
      <arglist>(int numShared, int idType, const int *sharedIDs, const int *numSharingProcsPerID, const int *sharingProcs)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>initSharedIDs</name>
      <anchorfile>classfei_1_1VectorSpace.html</anchorfile>
      <anchor>a57aa3f6c2e774d13105128a90039f4cb</anchor>
      <arglist>(int numShared, int idType, const int *sharedIDs, const int *numSharingProcsPerID, const int *const *sharingProcs)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>addVectorSpace</name>
      <anchorfile>classfei_1_1VectorSpace.html</anchorfile>
      <anchor>ab121a72373f5aa216b942cc9c8de26e0</anchor>
      <arglist>(fei::VectorSpace *inputSpace)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>initComplete</name>
      <anchorfile>classfei_1_1VectorSpace.html</anchorfile>
      <anchor>a3c58bd78b11537200038d395f8a8653a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>initCompleteAlreadyCalled</name>
      <anchorfile>classfei_1_1VectorSpace.html</anchorfile>
      <anchor>a983b0ecb58e2a8e08a71c771151415b5</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>MPI_Comm</type>
      <name>getCommunicator</name>
      <anchorfile>classfei_1_1VectorSpace.html</anchorfile>
      <anchor>a2d5e3f053d42459937ca65ed2ba8c5e5</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getGlobalIndex</name>
      <anchorfile>classfei_1_1VectorSpace.html</anchorfile>
      <anchor>ad091d76dcdf0b5028fb7e7b0c43dbcae</anchor>
      <arglist>(int idType, int ID, int fieldID, int fieldOffset, int whichComponentOfField, int &amp;globalIndex)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getGlobalIndex</name>
      <anchorfile>classfei_1_1VectorSpace.html</anchorfile>
      <anchor>a45dcf28abae7d501dfc996ebca32bb20</anchor>
      <arglist>(int idType, int ID, int fieldID, int &amp;globalIndex)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getGlobalBlkIndex</name>
      <anchorfile>classfei_1_1VectorSpace.html</anchorfile>
      <anchor>aa172736a2c8bbce56b84e5c7ec9cfcc7</anchor>
      <arglist>(int idType, int ID, int &amp;globalBlkIndex)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getGlobalIndices</name>
      <anchorfile>classfei_1_1VectorSpace.html</anchorfile>
      <anchor>a3a30c31bd14c89deb82fe54c4cf62148</anchor>
      <arglist>(int numIDs, const int *IDs, int idType, int fieldID, int *globalIndices)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getGlobalIndicesLocalIDs</name>
      <anchorfile>classfei_1_1VectorSpace.html</anchorfile>
      <anchor>a78483d519ad6af8ab72916c45a2ee588</anchor>
      <arglist>(int numIDs, const int *localIDs, int idType, int fieldID, int *globalIndices)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getGlobalBlkIndices</name>
      <anchorfile>classfei_1_1VectorSpace.html</anchorfile>
      <anchor>af9d5337d256a1c5255a6815fadaad24d</anchor>
      <arglist>(int numIDs, const int *IDs, int idType, int *globalBlkIndices)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getGlobalIndices</name>
      <anchorfile>classfei_1_1VectorSpace.html</anchorfile>
      <anchor>a6302eb2c6187a038a807c8f62f337ac9</anchor>
      <arglist>(int numIDs, const int *IDs, const int *idTypes, const int *fieldIDs, int *globalIndices)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getGlobalIndex</name>
      <anchorfile>classfei_1_1VectorSpace.html</anchorfile>
      <anchor>a978abf48cd6d44b6de9dc587eae8d231</anchor>
      <arglist>(int idType, int ID, int &amp;globalIndex)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getNumDegreesOfFreedom</name>
      <anchorfile>classfei_1_1VectorSpace.html</anchorfile>
      <anchor>ab51e6e5ce49d1ba1e9f7da8acc1e6c66</anchor>
      <arglist>(int idType, int ID)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getNumFields</name>
      <anchorfile>classfei_1_1VectorSpace.html</anchorfile>
      <anchor>abec9b5f4c1be9b620ef40c306274aee4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>getFields</name>
      <anchorfile>classfei_1_1VectorSpace.html</anchorfile>
      <anchor>a834d808f97524d4360cd34b3e62ac740</anchor>
      <arglist>(std::vector&lt; int &gt; &amp;fieldIDs)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getNumFields</name>
      <anchorfile>classfei_1_1VectorSpace.html</anchorfile>
      <anchor>a19a4e805c3ad8e9e23132c5c74f3451c</anchor>
      <arglist>(int idType, int ID)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>getFields</name>
      <anchorfile>classfei_1_1VectorSpace.html</anchorfile>
      <anchor>a64e0fb9080a673fdb90826c9efe5e6f0</anchor>
      <arglist>(int idType, int ID, std::vector&lt; int &gt; &amp;fieldIDs)</arglist>
    </member>
    <member kind="function">
      <type>size_t</type>
      <name>getNumIDTypes</name>
      <anchorfile>classfei_1_1VectorSpace.html</anchorfile>
      <anchor>a939480e21047bf344169b7a228311df7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>getIDTypes</name>
      <anchorfile>classfei_1_1VectorSpace.html</anchorfile>
      <anchor>a506e21f5de1195e1f469bda1d8d9bf38</anchor>
      <arglist>(std::vector&lt; int &gt; &amp;idTypes) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>getGlobalIndexOffsets</name>
      <anchorfile>classfei_1_1VectorSpace.html</anchorfile>
      <anchor>ab91e703c264e05e3fdd1d072ae739c20</anchor>
      <arglist>(std::vector&lt; int &gt; &amp;globalOffsets) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>getGlobalBlkIndexOffsets</name>
      <anchorfile>classfei_1_1VectorSpace.html</anchorfile>
      <anchor>a901ace1c30fa193eadde3a9eed2a13ef</anchor>
      <arglist>(std::vector&lt; int &gt; &amp;globalBlkOffsets) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getOwnerProcPtIndex</name>
      <anchorfile>classfei_1_1VectorSpace.html</anchorfile>
      <anchor>a814c7469ed9d4e6e9f6201895e6ea327</anchor>
      <arglist>(int globalIndex)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getOwnerProcBlkIndex</name>
      <anchorfile>classfei_1_1VectorSpace.html</anchorfile>
      <anchor>a3fbb8c6fa45e84441113208760959151</anchor>
      <arglist>(int globalIndex)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isLocal</name>
      <anchorfile>classfei_1_1VectorSpace.html</anchorfile>
      <anchor>aaadbb5614e0f2d77a5df3b932fe09ef0</anchor>
      <arglist>(int idType, int ID)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isLocallyOwned</name>
      <anchorfile>classfei_1_1VectorSpace.html</anchorfile>
      <anchor>a620b6fcba9650fdf7cde61c5e38902ae</anchor>
      <arglist>(int idType, int ID)</arglist>
    </member>
    <member kind="function">
      <type>unsigned</type>
      <name>getFieldSize</name>
      <anchorfile>classfei_1_1VectorSpace.html</anchorfile>
      <anchor>a194eeeee945adce78a9b9f021db66df6</anchor>
      <arglist>(int fieldID)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getNumOwnedAndSharedIDs</name>
      <anchorfile>classfei_1_1VectorSpace.html</anchorfile>
      <anchor>a1af68df4a9916aa6bf284ba036b95a5b</anchor>
      <arglist>(int idType)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getNumOwnedIDs</name>
      <anchorfile>classfei_1_1VectorSpace.html</anchorfile>
      <anchor>a5f8f8b66719c4cdb8a724d915974c30d</anchor>
      <arglist>(int idType)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getOwnedAndSharedIDs</name>
      <anchorfile>classfei_1_1VectorSpace.html</anchorfile>
      <anchor>a87412b321d400359cf90403a321c303a</anchor>
      <arglist>(int idtype, int lenList, int *IDs, int &amp;numOwnedAndSharedIDs)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getOwnedIDs</name>
      <anchorfile>classfei_1_1VectorSpace.html</anchorfile>
      <anchor>ac0d6cf244d8a12b3d0f524b48581c58c</anchor>
      <arglist>(int idtype, int lenList, int *IDs, int &amp;numLocalIDs)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getNumIndices_SharedAndOwned</name>
      <anchorfile>classfei_1_1VectorSpace.html</anchorfile>
      <anchor>a5a64422cf06379af35f5fc20d7b14882</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getIndices_SharedAndOwned</name>
      <anchorfile>classfei_1_1VectorSpace.html</anchorfile>
      <anchor>a86e5dd7cc710f88ab2fc5a4479e85e32</anchor>
      <arglist>(std::vector&lt; int &gt; &amp;globalIndices) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getNumBlkIndices_SharedAndOwned</name>
      <anchorfile>classfei_1_1VectorSpace.html</anchorfile>
      <anchor>a1b322be2fdd62447eddedf6e2e1b3c09</anchor>
      <arglist>(int &amp;numBlkIndices) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getBlkIndices_SharedAndOwned</name>
      <anchorfile>classfei_1_1VectorSpace.html</anchorfile>
      <anchor>a45e6790ba136998db991f413bf0b06f3</anchor>
      <arglist>(int lenBlkIndices, int *globalBlkIndices, int *blkSizes, int &amp;numBlkIndices)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getNumIndices_Owned</name>
      <anchorfile>classfei_1_1VectorSpace.html</anchorfile>
      <anchor>a5167e21023e8dd09a7300faff70b8769</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getIndices_Owned</name>
      <anchorfile>classfei_1_1VectorSpace.html</anchorfile>
      <anchor>aa93584ef37f91b9d183a0bae160f9a7e</anchor>
      <arglist>(std::vector&lt; int &gt; &amp;globalIndices) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getNumBlkIndices_Owned</name>
      <anchorfile>classfei_1_1VectorSpace.html</anchorfile>
      <anchor>a4666a9287c055aebf10d10970106f9ff</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getBlkIndices_Owned</name>
      <anchorfile>classfei_1_1VectorSpace.html</anchorfile>
      <anchor>ada7014b2d628d2207f90cf05b8328f63</anchor>
      <arglist>(int lenBlkIndices, int *globalBlkIndices, int *blkSizes, int &amp;numBlkIndices)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getNumSharedIDs</name>
      <anchorfile>classfei_1_1VectorSpace.html</anchorfile>
      <anchor>a012a0559569cd5e5754a71f4cc81a712</anchor>
      <arglist>(int idType, int &amp;numShared)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getGlobalNumIndices</name>
      <anchorfile>classfei_1_1VectorSpace.html</anchorfile>
      <anchor>a1eb3a642440b33e90b858c5969a2c805</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getGlobalNumBlkIndices</name>
      <anchorfile>classfei_1_1VectorSpace.html</anchorfile>
      <anchor>a27787eb14c2c6ecea24ee07311042406</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getRecordCollection</name>
      <anchorfile>classfei_1_1VectorSpace.html</anchorfile>
      <anchor>ae4ce2cf544ab22a2715acd480b8be6bb</anchor>
      <arglist>(int idType, snl_fei::RecordCollection *&amp;records)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getRecordCollection</name>
      <anchorfile>classfei_1_1VectorSpace.html</anchorfile>
      <anchor>a25d76de7ce4d3b9729f0568b337d5ad6</anchor>
      <arglist>(int idType, const snl_fei::RecordCollection *&amp;records) const </arglist>
    </member>
    <member kind="function">
      <type>std::vector&lt; int &gt; &amp;</type>
      <name>getEqnNumbers</name>
      <anchorfile>classfei_1_1VectorSpace.html</anchorfile>
      <anchor>aebdb45d7e6ac8fadd1e124f730fe9f19</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const std::vector&lt; int &gt; &amp;</type>
      <name>getEqnNumbers</name>
      <anchorfile>classfei_1_1VectorSpace.html</anchorfile>
      <anchor>a2350af0a6311b251d11f407458d8fc3b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>snl_fei::PointBlockMap *</type>
      <name>getPointBlockMap</name>
      <anchorfile>classfei_1_1VectorSpace.html</anchorfile>
      <anchor>abf9c8a692546304d1b23833b98f9420b</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>fei::VectorTraits</name>
    <filename>structfei_1_1VectorTraits.html</filename>
    <templarg></templarg>
    <member kind="function" static="yes">
      <type>static const char *</type>
      <name>typeName</name>
      <anchorfile>structfei_1_1VectorTraits.html</anchorfile>
      <anchor>a5033064a56f565d0e0f4a1a2f95f7d55</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static int</type>
      <name>setValues</name>
      <anchorfile>structfei_1_1VectorTraits.html</anchorfile>
      <anchor>aafdb26f26d645f9440d5a6fbb136a9ee</anchor>
      <arglist>(T *vec, int firstLocalOffset, double scalar, bool isSolnVector=false)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static int</type>
      <name>putValuesIn</name>
      <anchorfile>structfei_1_1VectorTraits.html</anchorfile>
      <anchor>aa9205bdc654285122fad212ec774a422</anchor>
      <arglist>(T *vec, int firstLocalOffset, int numValues, const int *indices, const double *values, bool sum_into, bool isSolnVector=false, int vectorIndex=0)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static int</type>
      <name>copyOut</name>
      <anchorfile>structfei_1_1VectorTraits.html</anchorfile>
      <anchor>ac26f8ae2a4e61106b28fb869bc5923dd</anchor>
      <arglist>(T *vec, int firstLocalOffset, int numValues, const int *indices, double *values, bool isSolnVector=false, int vectorIndex=0)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static double *</type>
      <name>getLocalCoefsPtr</name>
      <anchorfile>structfei_1_1VectorTraits.html</anchorfile>
      <anchor>a739a898d04d4a162540542ec106d699d</anchor>
      <arglist>(T *vec, bool isSolnVector=false, int vectorIndex=0)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static int</type>
      <name>update</name>
      <anchorfile>structfei_1_1VectorTraits.html</anchorfile>
      <anchor>a7116c1d0555ea0d50f98d4500ce9880b</anchor>
      <arglist>(T *vec, double a, const T *x, double b)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static int</type>
      <name>globalAssemble</name>
      <anchorfile>structfei_1_1VectorTraits.html</anchorfile>
      <anchor>a9c3a637b1d388435ae19a5037bd8aeaa</anchor>
      <arglist>(T *vec)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>fei::VectorTraits&lt; fei::LinearProblemManager &gt;</name>
    <filename>structfei_1_1VectorTraits_3_01fei_1_1LinearProblemManager_01_4.html</filename>
    <member kind="function" static="yes">
      <type>static const char *</type>
      <name>typeName</name>
      <anchorfile>structfei_1_1VectorTraits_3_01fei_1_1LinearProblemManager_01_4.html</anchorfile>
      <anchor>a59269e25a35bbdbf79bae867769d2bc5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static int</type>
      <name>setValues</name>
      <anchorfile>structfei_1_1VectorTraits_3_01fei_1_1LinearProblemManager_01_4.html</anchorfile>
      <anchor>aff8eea47dfbc17d91f464fe2938d34e2</anchor>
      <arglist>(fei::LinearProblemManager *vec, int firstLocalOffset, double scalar, bool isSolnVector=false)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static int</type>
      <name>putValuesIn</name>
      <anchorfile>structfei_1_1VectorTraits_3_01fei_1_1LinearProblemManager_01_4.html</anchorfile>
      <anchor>a2920da14c7b695abbf10a1811e2278cd</anchor>
      <arglist>(fei::LinearProblemManager *vec, int firstLocalOffset, int numValues, const int *indices, const double *values, bool sum_into, bool isSolnVector=false, int vectorIndex=0)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static int</type>
      <name>copyOut</name>
      <anchorfile>structfei_1_1VectorTraits_3_01fei_1_1LinearProblemManager_01_4.html</anchorfile>
      <anchor>a81c18ce6fe149f1d8f970c30e54f1904</anchor>
      <arglist>(fei::LinearProblemManager *vec, int firstLocalOffset, int numValues, const int *indices, double *values, bool isSolnVector=false, int vectorIndex=0)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static int</type>
      <name>globalAssemble</name>
      <anchorfile>structfei_1_1VectorTraits_3_01fei_1_1LinearProblemManager_01_4.html</anchorfile>
      <anchor>a23d69f93308f9cff102b2990c0cc9676</anchor>
      <arglist>(fei::LinearProblemManager *vec)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static int</type>
      <name>update</name>
      <anchorfile>structfei_1_1VectorTraits_3_01fei_1_1LinearProblemManager_01_4.html</anchorfile>
      <anchor>a84adfe3754e12a555b187836af9680e6</anchor>
      <arglist>(fei::LinearProblemManager *vec, double a, const fei::LinearProblemManager *x, double b)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>fei::VectorTraits&lt; FiniteElementData &gt;</name>
    <filename>structfei_1_1VectorTraits_3_01FiniteElementData_01_4.html</filename>
    <member kind="function" static="yes">
      <type>static const char *</type>
      <name>typeName</name>
      <anchorfile>structfei_1_1VectorTraits_3_01FiniteElementData_01_4.html</anchorfile>
      <anchor>a1b47a5460e739661d5285d8f10d88b83</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static int</type>
      <name>setValues</name>
      <anchorfile>structfei_1_1VectorTraits_3_01FiniteElementData_01_4.html</anchorfile>
      <anchor>a03b9dfb4447db9111399b279d549d889</anchor>
      <arglist>(FiniteElementData *vec, int firstLocalOffset, double scalar, bool isSolnVector=false)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static int</type>
      <name>putValuesIn</name>
      <anchorfile>structfei_1_1VectorTraits_3_01FiniteElementData_01_4.html</anchorfile>
      <anchor>afb3c7edaf8fc92d8906e144345057fdb</anchor>
      <arglist>(FiniteElementData *vec, int firstLocalOffset, int numValues, const int *indices, const double *values, bool sum_into, bool isSolnVector=false, int vectorIndex=0)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static int</type>
      <name>copyOut</name>
      <anchorfile>structfei_1_1VectorTraits_3_01FiniteElementData_01_4.html</anchorfile>
      <anchor>af5f04c038543eb2049f7a193383f87ce</anchor>
      <arglist>(FiniteElementData *vec, int firstLocalOffset, int numValues, const int *indices, double *values, bool isSolnVector=false, int vectorIndex=0)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static int</type>
      <name>update</name>
      <anchorfile>structfei_1_1VectorTraits_3_01FiniteElementData_01_4.html</anchorfile>
      <anchor>a1c7f57d11c5753a57a90e7763e8d641b</anchor>
      <arglist>(FiniteElementData *vec, double a, const FiniteElementData *x, double b)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>fei::VectorTraits&lt; LinearSystemCore &gt;</name>
    <filename>structfei_1_1VectorTraits_3_01LinearSystemCore_01_4.html</filename>
    <member kind="function" static="yes">
      <type>static const char *</type>
      <name>typeName</name>
      <anchorfile>structfei_1_1VectorTraits_3_01LinearSystemCore_01_4.html</anchorfile>
      <anchor>adb94ab31c5a679812cdb29d68e3e894d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static int</type>
      <name>setValues</name>
      <anchorfile>structfei_1_1VectorTraits_3_01LinearSystemCore_01_4.html</anchorfile>
      <anchor>a63c689aeb503ea64e994fe7cadd91284</anchor>
      <arglist>(LinearSystemCore *vec, int firstLocalOffset, double scalar, bool isSolnVector=false)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static int</type>
      <name>putValuesIn</name>
      <anchorfile>structfei_1_1VectorTraits_3_01LinearSystemCore_01_4.html</anchorfile>
      <anchor>afb12663084b198e28d28c22771fa09bd</anchor>
      <arglist>(LinearSystemCore *vec, int firstLocalOffset, int numValues, const int *indices, const double *values, bool sum_into, bool isSolnVector=false, int vectorIndex=0)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static int</type>
      <name>copyOut</name>
      <anchorfile>structfei_1_1VectorTraits_3_01LinearSystemCore_01_4.html</anchorfile>
      <anchor>a634729f5fa3b9651a1da8c883a3e1dfa</anchor>
      <arglist>(LinearSystemCore *vec, int firstLocalOffset, int numValues, const int *indices, double *values, bool isSolnVector=false, int vectorIndex=0)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static int</type>
      <name>update</name>
      <anchorfile>structfei_1_1VectorTraits_3_01LinearSystemCore_01_4.html</anchorfile>
      <anchor>a3daa4497020a7775bcdb47373a3a742e</anchor>
      <arglist>(LinearSystemCore *vec, double a, const LinearSystemCore *x, double b)</arglist>
    </member>
  </compound>
  <compound kind="namespace">
    <name>fei</name>
    <filename>namespacefei.html</filename>
    <namespace>fei::impl_utils</namespace>
    <namespace>fei::utils</namespace>
    <class kind="class">fei::BlockLinearProblemManager</class>
    <class kind="struct">fei::CommMap</class>
    <class kind="class">fei::ConnectivityBlock</class>
    <class kind="class">fei::CSRMat</class>
    <class kind="class">fei::CSVec</class>
    <class kind="class">fei::ctg_set</class>
    <class kind="class">fei::Dof</class>
    <class kind="class">fei::DofMapper</class>
    <class kind="struct">fei::EqnRecord</class>
    <class kind="class">fei::Factory</class>
    <class kind="class">fei::FEI_Impl</class>
    <class kind="class">fei::FieldDofMap</class>
    <class kind="class">fei::FieldMask</class>
    <class kind="class">fei::Graph</class>
    <class kind="class">fei::Graph_Impl</class>
    <class kind="class">fei::GraphReducer</class>
    <class kind="class">fei::IndexTable</class>
    <class kind="struct">fei::less_field_rank_id</class>
    <class kind="struct">fei::less_rank_id_field</class>
    <class kind="class">fei::LinearProblemManager</class>
    <class kind="class">fei::LinearSystem</class>
    <class kind="class">fei::LogFile</class>
    <class kind="class">fei::Logger</class>
    <class kind="class">fei::LogManager</class>
    <class kind="class">fei::Lookup_Impl</class>
    <class kind="class">fei::Matrix</class>
    <class kind="class">fei::Matrix_Impl</class>
    <class kind="class">fei::MatrixGraph</class>
    <class kind="class">fei::MatrixGraph_Impl2</class>
    <class kind="struct">fei::MatrixTraits</class>
    <class kind="struct">fei::MatrixTraits&lt; fei::LinearProblemManager &gt;</class>
    <class kind="struct">fei::MatrixTraits&lt; FillableMat &gt;</class>
    <class kind="struct">fei::MatrixTraits&lt; FiniteElementData &gt;</class>
    <class kind="struct">fei::MatrixTraits&lt; LinearSystemCore &gt;</class>
    <class kind="class">fei::MessageHandler</class>
    <class kind="class">fei::Param</class>
    <class kind="class">fei::ParameterSet</class>
    <class kind="class">fei::Pattern</class>
    <class kind="class">fei::Record</class>
    <class kind="class">fei::Record_Operator</class>
    <class kind="class">fei::ReverseMapper</class>
    <class kind="class">fei::SharedIDs</class>
    <class kind="class">fei::SharedPtr</class>
    <class kind="class">fei::Solver</class>
    <class kind="class">fei::SparseRowGraph</class>
    <class kind="class">fei::Vector</class>
    <class kind="class">fei::Vector_core</class>
    <class kind="class">fei::Vector_Impl</class>
    <class kind="class">fei::VectorSpace</class>
    <class kind="struct">fei::VectorTraits</class>
    <class kind="struct">fei::VectorTraits&lt; fei::LinearProblemManager &gt;</class>
    <class kind="struct">fei::VectorTraits&lt; FiniteElementData &gt;</class>
    <class kind="struct">fei::VectorTraits&lt; LinearSystemCore &gt;</class>
    <member kind="typedef">
      <type>snl_fei::Constraint&lt; fei::Record&lt; int &gt; * &gt;</type>
      <name>ConstraintType</name>
      <anchorfile>namespacefei.html</anchorfile>
      <anchor>aef0d5bdbf26ccdc8ba1e0fb8214084e5</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>OutputLevel</name>
      <anchorfile>namespacefei.html</anchorfile>
      <anchor>aa3cf1e3b2acd02b2133db8b46f0a287f</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>lowerBound</name>
      <anchorfile>namespacefei.html</anchorfile>
      <anchor>a0efc4a8e242575239085dff260d5067e</anchor>
      <arglist>(const T &amp;item, const T *list, int len)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>binarySearch</name>
      <anchorfile>namespacefei.html</anchorfile>
      <anchor>abc8f01488b2d10e91c73453e3067fc07</anchor>
      <arglist>(const T &amp;item, const T *list, int len)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>insertion_sort_with_companions</name>
      <anchorfile>namespacefei.html</anchorfile>
      <anchor>afcc5443b9ed0c896b6d0dbfba8fa6eca</anchor>
      <arglist>(int len, int *array, T *companions)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>binarySearch</name>
      <anchorfile>namespacefei.html</anchorfile>
      <anchor>a29656e9f9d21e1cbb0659f5c7db2187c</anchor>
      <arglist>(const T &amp;item, const T *list, int len, int &amp;insertPoint)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>binarySearch</name>
      <anchorfile>namespacefei.html</anchorfile>
      <anchor>a89ab72509f596deeb7c844d088bd7dc8</anchor>
      <arglist>(const T &amp;item, const std::vector&lt; T &gt; &amp;list, int &amp;insertPoint)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>binarySearch</name>
      <anchorfile>namespacefei.html</anchorfile>
      <anchor>a70606676b37cc67b3432ed751deb13a7</anchor>
      <arglist>(const T &amp;item, const std::vector&lt; T &gt; &amp;list)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>binarySearch</name>
      <anchorfile>namespacefei.html</anchorfile>
      <anchor>ad0946cec4b73f857af5212104a46a8ad</anchor>
      <arglist>(const T &amp;item, const T *list, int, int start, int end, int &amp;insertPoint)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>binarySearch</name>
      <anchorfile>namespacefei.html</anchorfile>
      <anchor>ab4b6c849ff3cdffb0845769c8abdbb2b</anchor>
      <arglist>(int numItems, const T *items, int *offsets, const T *list, int listLength)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>sortedListInsert</name>
      <anchorfile>namespacefei.html</anchorfile>
      <anchor>acc28917fd0b26792db6d64ef5a52ce95</anchor>
      <arglist>(const T &amp;item, std::vector&lt; T &gt; &amp;list)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>sortedListInsert</name>
      <anchorfile>namespacefei.html</anchorfile>
      <anchor>a41d157b4a60fe59dabe579287f1eb3d5</anchor>
      <arglist>(const T &amp;item, T *&amp;list, int &amp;len, int &amp;allocLen)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>listInsert</name>
      <anchorfile>namespacefei.html</anchorfile>
      <anchor>aaed8c8a03cb7d092ebb73ddc32eaca25</anchor>
      <arglist>(const T &amp;item, int offset, T *&amp;list, int &amp;usedLength, int &amp;allocatedLength, int allocChunkSize=200)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>searchList</name>
      <anchorfile>namespacefei.html</anchorfile>
      <anchor>a4c5bd8920f581c1ad21bc00afb030439</anchor>
      <arglist>(const T &amp;item, const T *list, int len)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>addItemsToCommMap</name>
      <anchorfile>namespacefei.html</anchorfile>
      <anchor>ab140e04f0d8436d728c942b6c51fc060</anchor>
      <arglist>(int proc, size_t numItems, const T *items, typename CommMap&lt; T &gt;::Type &amp;comm_map, bool keep_sorted_and_unique=true)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>localProc</name>
      <anchorfile>namespacefei.html</anchorfile>
      <anchor>a0e3a06536098e9ff002247a35f1b6fa7</anchor>
      <arglist>(MPI_Comm comm)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>numProcs</name>
      <anchorfile>namespacefei.html</anchorfile>
      <anchor>ae4de8e0030da28cb961a03df9d424a00</anchor>
      <arglist>(MPI_Comm comm)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>mirrorProcs</name>
      <anchorfile>namespacefei.html</anchorfile>
      <anchor>a86d65d9b2a28cd11f1d72d2eb4844e11</anchor>
      <arglist>(MPI_Comm comm, std::vector&lt; int &gt; &amp;toProcs, std::vector&lt; int &gt; &amp;fromProcs)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>mirrorCommPattern</name>
      <anchorfile>namespacefei.html</anchorfile>
      <anchor>a71950510d0cccb162802f85f5cc40d04</anchor>
      <arglist>(MPI_Comm comm, comm_map *inPattern, comm_map *&amp;outPattern)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>exchangeIntData</name>
      <anchorfile>namespacefei.html</anchorfile>
      <anchor>aaf9956842e18172ec5d3b6e21f00bb0e</anchor>
      <arglist>(MPI_Comm comm, const std::vector&lt; int &gt; &amp;sendProcs, std::vector&lt; int &gt; &amp;sendData, const std::vector&lt; int &gt; &amp;recvProcs, std::vector&lt; int &gt; &amp;recvData)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Allreduce</name>
      <anchorfile>namespacefei.html</anchorfile>
      <anchor>ac8327d1a3aa9c95c430136bb33f9da71</anchor>
      <arglist>(MPI_Comm comm, bool localBool, bool &amp;globalBool)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GlobalMax</name>
      <anchorfile>namespacefei.html</anchorfile>
      <anchor>ad3dc3c245361504fc96e8f10773d5d39</anchor>
      <arglist>(MPI_Comm comm, std::vector&lt; T &gt; &amp;local, std::vector&lt; T &gt; &amp;global)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GlobalMax</name>
      <anchorfile>namespacefei.html</anchorfile>
      <anchor>a1557e3aa42e2023a206f54b87b32f59d</anchor>
      <arglist>(MPI_Comm comm, T local, T &amp;global)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GlobalMin</name>
      <anchorfile>namespacefei.html</anchorfile>
      <anchor>a51f8e9679eb87080cadd1dfafb18c597</anchor>
      <arglist>(MPI_Comm comm, std::vector&lt; T &gt; &amp;local, std::vector&lt; T &gt; &amp;global)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GlobalMin</name>
      <anchorfile>namespacefei.html</anchorfile>
      <anchor>a4cf910b47415678f7cad553409fbe54f</anchor>
      <arglist>(MPI_Comm comm, T local, T &amp;global)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GlobalSum</name>
      <anchorfile>namespacefei.html</anchorfile>
      <anchor>ae808d07911cdef542d4eaecdda341443</anchor>
      <arglist>(MPI_Comm comm, std::vector&lt; T &gt; &amp;local, std::vector&lt; T &gt; &amp;global)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GlobalSum</name>
      <anchorfile>namespacefei.html</anchorfile>
      <anchor>ae4018feca418c8a9a25584156eed1f2b</anchor>
      <arglist>(MPI_Comm comm, T local, T &amp;global)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Allgatherv</name>
      <anchorfile>namespacefei.html</anchorfile>
      <anchor>ab5abe7c1735b40ec8f7a3bcaca1a8c53</anchor>
      <arglist>(MPI_Comm comm, std::vector&lt; T &gt; &amp;sendbuf, std::vector&lt; int &gt; &amp;recvLengths, std::vector&lt; T &gt; &amp;recvbuf)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>exchangeCommMapData</name>
      <anchorfile>namespacefei.html</anchorfile>
      <anchor>aaebe97d8eb96b7081e54210ed61f82b7</anchor>
      <arglist>(MPI_Comm comm, const typename CommMap&lt; T &gt;::Type &amp;sendCommMap, typename CommMap&lt; T &gt;::Type &amp;recvCommMap, bool recvProcsKnownOnEntry=false, bool recvLengthsKnownOnEntry=false)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_console_ostream</name>
      <anchorfile>namespacefei.html</anchorfile>
      <anchor>aa1be28e3aae0dea3eb504f4913ea9a3f</anchor>
      <arglist>(std::ostream &amp;os)</arglist>
    </member>
    <member kind="function">
      <type>std::ostream &amp;</type>
      <name>console_out</name>
      <anchorfile>namespacefei.html</anchorfile>
      <anchor>abd0fcf9f34f05ec5d0ffbfed82ab1588</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>multiply_CSRMat_CSVec</name>
      <anchorfile>namespacefei.html</anchorfile>
      <anchor>ad58b7ad63318699e0141fd7d819053fd</anchor>
      <arglist>(const CSRMat &amp;A, const CSVec &amp;x, CSVec &amp;y)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>multiply_trans_CSRMat_CSVec</name>
      <anchorfile>namespacefei.html</anchorfile>
      <anchor>ab699a07c0dc1e4c2977fceaa97f79103</anchor>
      <arglist>(const CSRMat &amp;A, const CSVec &amp;x, CSVec &amp;y)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>multiply_CSRMat_CSRMat</name>
      <anchorfile>namespacefei.html</anchorfile>
      <anchor>a6b2c8c56cf90537d52fb2ab7e380c5c0</anchor>
      <arglist>(const CSRMat &amp;A, const CSRMat &amp;B, CSRMat &amp;C, bool storeResultZeros)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>multiply_trans_CSRMat_CSRMat</name>
      <anchorfile>namespacefei.html</anchorfile>
      <anchor>a6b46a568705048eb31cac3de84db86b9</anchor>
      <arglist>(const CSRMat &amp;A, const CSRMat &amp;B, CSRMat &amp;C, bool storeResultZeros)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>add_CSVec_CSVec</name>
      <anchorfile>namespacefei.html</anchorfile>
      <anchor>a392fd8e0be3d07d974f76fbbe95b45f7</anchor>
      <arglist>(const CSVec &amp;u, CSVec &amp;v)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>print</name>
      <anchorfile>namespacefei.html</anchorfile>
      <anchor>ac00483ad6d37e3844769bdfb284182b5</anchor>
      <arglist>(std::ostream &amp;os, const FillableMat &amp;mat)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>count_nnz</name>
      <anchorfile>namespacefei.html</anchorfile>
      <anchor>a08c3714f0c246baf7db5ddf6f156bc3e</anchor>
      <arglist>(const FillableMat &amp;mat)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>get_row_numbers</name>
      <anchorfile>namespacefei.html</anchorfile>
      <anchor>aee8cfd5729e1757e28030ea63d2833c1</anchor>
      <arglist>(const FillableMat &amp;mat, std::vector&lt; int &gt; &amp;rows)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_shared_ids</name>
      <anchorfile>namespacefei.html</anchorfile>
      <anchor>acfd9d7b740be49b74758060400bbc2d6</anchor>
      <arglist>(MPI_Comm comm, const snl_fei::RecordCollection &amp;records, fei::SharedIDs&lt; int &gt; &amp;sharedIDs, int lowest_global_id, int highest_global_id)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator==</name>
      <anchorfile>namespacefei.html</anchorfile>
      <anchor>ab28313070bead7c78e48ff62588ce894</anchor>
      <arglist>(const SharedPtr&lt; T &gt; &amp;a, const SharedPtr&lt; U &gt; &amp;b)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator!=</name>
      <anchorfile>namespacefei.html</anchorfile>
      <anchor>abb300085ed1f292befee5d78db48e93a</anchor>
      <arglist>(const SharedPtr&lt; T &gt; &amp;a, const SharedPtr&lt; U &gt; &amp;b)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>find_row_start</name>
      <anchorfile>namespacefei.html</anchorfile>
      <anchor>a107a404246ef50d354a45a963ef3ff1e</anchor>
      <arglist>(int row, const SparseRowGraph &amp;srg)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>copySetToArray</name>
      <anchorfile>namespacefei.html</anchorfile>
      <anchor>a2db91d5c836c18200eae1ccef4da9418</anchor>
      <arglist>(const SET_TYPE &amp;set_obj, int lenList, int *list)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>copySetToVector</name>
      <anchorfile>namespacefei.html</anchorfile>
      <anchor>a19002647ede8ef2bdfb6b87a34976315</anchor>
      <arglist>(const std::set&lt; T &gt; &amp;set_obj, std::vector&lt; T &gt; &amp;vec)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>copyKeysToArray</name>
      <anchorfile>namespacefei.html</anchorfile>
      <anchor>a945393d80f22fea79eee3f5ae398c411</anchor>
      <arglist>(const MAP_TYPE &amp;map_obj, unsigned lenList, int *list)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>copyKeysToVector</name>
      <anchorfile>namespacefei.html</anchorfile>
      <anchor>a5c2a3aecb10f35366836022195b1bb58</anchor>
      <arglist>(const MAP_TYPE &amp;map_obj, std::vector&lt; int &gt; &amp;keyvector)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>copyToArrays</name>
      <anchorfile>namespacefei.html</anchorfile>
      <anchor>a4dedffe9e70d7a84174914f2a4c6eea3</anchor>
      <arglist>(MAP_TYPE &amp;map_obj, int lenList, int *keylist, int *vallist)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>destroyValues</name>
      <anchorfile>namespacefei.html</anchorfile>
      <anchor>a1af46d3341fe4568aa0e4d4fb6b5f1d7</anchor>
      <arglist>(MAP_TYPE &amp;map_obj)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>writeToStream</name>
      <anchorfile>namespacefei.html</anchorfile>
      <anchor>aef0b2ab2927c884f26042856ac4d2efb</anchor>
      <arglist>(snl_fei::RaggedTable&lt; MAP_TYPE, SET_TYPE &gt; &amp;table, FEI_OSTREAM &amp;os, const char *lineprefix=NULL)</arglist>
    </member>
    <member kind="function">
      <type>fei::SharedPtr&lt; fei::SparseRowGraph &gt;</type>
      <name>createSparseRowGraph</name>
      <anchorfile>namespacefei.html</anchorfile>
      <anchor>a73c9175e24ed6599b247a49a366e7cd2</anchor>
      <arglist>(const std::vector&lt; snl_fei::RaggedTable&lt; MAP_TYPE, SET_TYPE &gt; * &gt; &amp;tables)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>copyToSparseRowGraph</name>
      <anchorfile>namespacefei.html</anchorfile>
      <anchor>af2aa95997091815bc7885f6af8fe703b</anchor>
      <arglist>(snl_fei::RaggedTable&lt; MAP_TYPE, SET_TYPE &gt; &amp;table, fei::SparseRowGraph &amp;srg)</arglist>
    </member>
    <member kind="function">
      <type>fei::SharedPtr&lt; fei::SparseRowGraph &gt;</type>
      <name>createSparseRowGraph</name>
      <anchorfile>namespacefei.html</anchorfile>
      <anchor>aacda491eedb68a90749b90e556879b57</anchor>
      <arglist>(snl_fei::RaggedTable&lt; MAP_TYPE, SET_TYPE &gt; &amp;table)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>countNonzeros</name>
      <anchorfile>namespacefei.html</anchorfile>
      <anchor>a357a61ba7a10e3d6915632e10a09b3e7</anchor>
      <arglist>(snl_fei::RaggedTable&lt; MAP_TYPE, SET_TYPE &gt; &amp;table)</arglist>
    </member>
    <member kind="function">
      <type>fei::SharedPtr&lt; LibraryWrapper &gt;</type>
      <name>create_LibraryWrapper</name>
      <anchorfile>namespacefei.html</anchorfile>
      <anchor>adac3dc13d80c7bb052495bb5bc93c45d</anchor>
      <arglist>(MPI_Comm comm, const char *libraryName)</arglist>
    </member>
    <member kind="function">
      <type>fei::SharedPtr&lt; fei::Factory &gt;</type>
      <name>create_fei_Factory</name>
      <anchorfile>namespacefei.html</anchorfile>
      <anchor>a90066727fac24dcfeef4085e0174caa7</anchor>
      <arglist>(MPI_Comm comm, const char *libraryName)</arglist>
    </member>
  </compound>
  <compound kind="namespace">
    <name>fei::impl_utils</name>
    <filename>namespacefei_1_1impl__utils.html</filename>
    <member kind="function">
      <type>void</type>
      <name>find_offsets</name>
      <anchorfile>namespacefei_1_1impl__utils.html</anchorfile>
      <anchor>a415e877d1b75600aa9c33cf57256cd1a</anchor>
      <arglist>(const std::vector&lt; int &gt; &amp;sources, const std::vector&lt; int &gt; &amp;targets, std::vector&lt; int &gt; &amp;offsets)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>unpack_FillableMat</name>
      <anchorfile>namespacefei_1_1impl__utils.html</anchorfile>
      <anchor>aab0290114cd406ebdcff311e33909f8d</anchor>
      <arglist>(const char *buffer_begin, const char *buffer_end, fei::FillableMat &amp;mat, bool clear_mat_on_entry, bool overwrite_entries)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>unpack_CSRMat</name>
      <anchorfile>namespacefei_1_1impl__utils.html</anchorfile>
      <anchor>a62121dda1e616232d47391d77e5b3eaa</anchor>
      <arglist>(const char *buffer_begin, const char *buffer_end, fei::CSRMat &amp;mat)</arglist>
    </member>
  </compound>
  <compound kind="namespace">
    <name>fei::utils</name>
    <filename>namespacefei_1_1utils.html</filename>
    <member kind="function">
      <type>const char *</type>
      <name>version</name>
      <anchorfile>namespacefei_1_1utils.html</anchorfile>
      <anchor>ace8702f5572dc849bb7c4b301cf2c367</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>cpu_time</name>
      <anchorfile>namespacefei_1_1utils.html</anchorfile>
      <anchor>ad42d9849bbc0ac7a38ea31e562005eef</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>fei::OutputLevel</type>
      <name>string_to_output_level</name>
      <anchorfile>namespacefei_1_1utils.html</anchorfile>
      <anchor>acfb2c2f71b1c3beb6bdf85c932c83aa7</anchor>
      <arglist>(const std::string &amp;str)</arglist>
    </member>
    <member kind="function">
      <type>LinearSystemCore *</type>
      <name>get_LinearSystemCore</name>
      <anchorfile>namespacefei_1_1utils.html</anchorfile>
      <anchor>a759d7563f164956bba6ea17d38ef6647</anchor>
      <arglist>(fei::Matrix *matrix)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>getConnectivityArrays</name>
      <anchorfile>namespacefei_1_1utils.html</anchorfile>
      <anchor>a3a9c942efcfacdbab37cd1e37b3bc030</anchor>
      <arglist>(fei::MatrixGraph &amp;matrixGraph, std::vector&lt; int &gt; &amp;nodes, std::vector&lt; int &gt; &amp;elem_offsets)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>char_ptrs_to_strings</name>
      <anchorfile>namespacefei_1_1utils.html</anchorfile>
      <anchor>a67b94945ba99c04edba4a0dfb3ba4eb8</anchor>
      <arglist>(int numStrings, const char *const *charstrings, std::vector&lt; std::string &gt; &amp;stdstrings)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>strings_to_char_ptrs</name>
      <anchorfile>namespacefei_1_1utils.html</anchorfile>
      <anchor>ad89751e19c5c7ce7fc8ce465def6af26</anchor>
      <arglist>(std::vector&lt; std::string &gt; &amp;stdstrings, int &amp;numStrings, const char **&amp;charPtrs)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>parse_strings</name>
      <anchorfile>namespacefei_1_1utils.html</anchorfile>
      <anchor>a0659cd5e66f4dd3e3eb533971e0d8af4</anchor>
      <arglist>(std::vector&lt; std::string &gt; &amp;stdstrings, const char *separator_string, fei::ParameterSet &amp;paramset)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>convert_ParameterSet_to_strings</name>
      <anchorfile>namespacefei_1_1utils.html</anchorfile>
      <anchor>a12904d2a23a2cf952736441d5d8a786f</anchor>
      <arglist>(const fei::ParameterSet *paramset, std::vector&lt; std::string &gt; &amp;paramStrings)</arglist>
    </member>
  </compound>
  <compound kind="namespace">
    <name>fei_test_utils</name>
    <filename>namespacefei__test__utils.html</filename>
    <member kind="function">
      <type>std::string</type>
      <name>construct_filename</name>
      <anchorfile>namespacefei__test__utils.html</anchorfile>
      <anchor>a60bf3aa8af2ca7ac02783a76fe096f87</anchor>
      <arglist>(int argc, char **argv)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>initialize_mpi</name>
      <anchorfile>namespacefei__test__utils.html</anchorfile>
      <anchor>a51faa95dd543b6b4d7de8d4f8be696b5</anchor>
      <arglist>(int argc, char **argv, int &amp;localProc, int &amp;numProcs)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>bool_arg</name>
      <anchorfile>namespacefei__test__utils.html</anchorfile>
      <anchor>aa2e0be9300ec4b2043debb850425e742</anchor>
      <arglist>(const char *flag, int argc, char **argv, bool default_result)</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>get_arg_value</name>
      <anchorfile>namespacefei__test__utils.html</anchorfile>
      <anchor>afa5e98fe19c58cc985c9ad9dc5967aa1</anchor>
      <arglist>(const char *flag, int argc, char **argv)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>broadcast_string</name>
      <anchorfile>namespacefei__test__utils.html</anchorfile>
      <anchor>ac09056191b19f63f8a5dfbe1ed499736</anchor>
      <arglist>(MPI_Comm comm, int root, std::string &amp;strg)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>read_file_lines_into_strings</name>
      <anchorfile>namespacefei__test__utils.html</anchorfile>
      <anchor>ae4ff60d62fd35369aea16ede19ddf5ed</anchor>
      <arglist>(const char *filename, std::vector&lt; std::string &gt; &amp;file_contents)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>get_filename_and_read_input</name>
      <anchorfile>namespacefei__test__utils.html</anchorfile>
      <anchor>a603040461e8ede9ebb995f20367d2580</anchor>
      <arglist>(int argc, char **argv, MPI_Comm comm, int localProc, std::vector&lt; std::string &gt; &amp;stdstrings)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>read_input_file</name>
      <anchorfile>namespacefei__test__utils.html</anchorfile>
      <anchor>ac919a3b67e6f777b095c54ae6ea5a5c0</anchor>
      <arglist>(const char *filename, MPI_Comm comm, std::vector&lt; std::string &gt; &amp;file_contents)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>get_file_benchmark</name>
      <anchorfile>namespacefei__test__utils.html</anchorfile>
      <anchor>ac8257ddf2c09eab1bbd2d26331cf3765</anchor>
      <arglist>(const char *filename, const char *testname)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>within_percentage_margin</name>
      <anchorfile>namespacefei__test__utils.html</anchorfile>
      <anchor>aade5423196a53cfa5474c5c73ca374b1</anchor>
      <arglist>(double value1, double value2, unsigned margin)</arglist>
    </member>
  </compound>
  <compound kind="page">
    <name>index</name>
    <title>FEI (Finite Element Interface)</title>
    <filename>index</filename>
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
  </compound>
</tagfile>
