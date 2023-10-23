<?xml version='1.0' encoding='UTF-8' standalone='yes' ?>
<tagfile>
  <compound kind="file">
    <name>AZOO_iterate.h</name>
    <path>/Users/sscoll/dist/trilinos/packages/aztecoo/src/</path>
    <filename>AZOO__iterate_8h</filename>
    <includes id="Aztec2Petra_8h" name="Aztec2Petra.h" local="yes" imported="no">Aztec2Petra.h</includes>
    <member kind="function">
      <type>void</type>
      <name>AZOO_iterate</name>
      <anchorfile>AZOO__iterate_8h.html</anchorfile>
      <anchor>a4c89ab2872cb1076a2849e40105dcde8</anchor>
      <arglist>(double *xsolve, double *b, int *options, double *params, double *status, int *proc_config, AZ_MATRIX *Amat, AZ_PRECOND *precond, struct AZ_SCALING *scaling)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Aztec2Petra.h</name>
    <path>/Users/sscoll/dist/trilinos/packages/aztecoo/src/</path>
    <filename>Aztec2Petra_8h</filename>
    <member kind="function">
      <type>int</type>
      <name>Aztec2Petra</name>
      <anchorfile>Aztec2Petra_8h.html</anchorfile>
      <anchor>ab6b26e2e31113ec539904ad79d7706f2</anchor>
      <arglist>(int *proc_config, AZ_MATRIX *Amat, double *az_x, double *az_b, Epetra_Comm *&amp;comm, Epetra_BlockMap *&amp;map, Epetra_RowMatrix *&amp;A, Epetra_Vector *&amp;x, Epetra_Vector *&amp;b, int **global_indices)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>AztecOO_StatusType.h</name>
    <path>/Users/sscoll/dist/trilinos/packages/aztecoo/src/</path>
    <filename>AztecOO__StatusType_8h</filename>
    <member kind="enumeration">
      <type></type>
      <name>AztecOO_StatusType</name>
      <anchorfile>AztecOO__StatusType_8h.html</anchorfile>
      <anchor>a83d088aa694917fb31c40a66342b4dde</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>Unchecked</name>
      <anchorfile>AztecOO__StatusType_8h.html</anchorfile>
      <anchor>a83d088aa694917fb31c40a66342b4ddeadf8edafdc44e6862bee7a37abddd6b28</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>Unconverged</name>
      <anchorfile>AztecOO__StatusType_8h.html</anchorfile>
      <anchor>a83d088aa694917fb31c40a66342b4ddeab411d14c8fedeabaf0eb643489c82982</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>Converged</name>
      <anchorfile>AztecOO__StatusType_8h.html</anchorfile>
      <anchor>a83d088aa694917fb31c40a66342b4ddea6c43fa1cdd73fc3d5db67420a283590a</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>Failed</name>
      <anchorfile>AztecOO__StatusType_8h.html</anchorfile>
      <anchor>a83d088aa694917fb31c40a66342b4ddea1f506c828f4945d6b5a7bf71445f7d54</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>NaN</name>
      <anchorfile>AztecOO__StatusType_8h.html</anchorfile>
      <anchor>a83d088aa694917fb31c40a66342b4ddea4c2b7217d0a01a8d2d8e35742bb635b2</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>PartialFailed</name>
      <anchorfile>AztecOO__StatusType_8h.html</anchorfile>
      <anchor>a83d088aa694917fb31c40a66342b4ddeab0394b28ac1211ee42e1625142d2d88e</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>alist</name>
    <filename>structalist.html</filename>
  </compound>
  <compound kind="struct">
    <name>AZ_CONVERGE_STRUCT</name>
    <filename>structAZ__CONVERGE__STRUCT.html</filename>
  </compound>
  <compound kind="struct">
    <name>AZ_MATRIX_STRUCT</name>
    <filename>structAZ__MATRIX__STRUCT.html</filename>
  </compound>
  <compound kind="class">
    <name>az_ostream_err</name>
    <filename>classaz__ostream__err.html</filename>
  </compound>
  <compound kind="class">
    <name>az_ostream_out</name>
    <filename>classaz__ostream__out.html</filename>
  </compound>
  <compound kind="struct">
    <name>AZ_PREC_STRUCT</name>
    <filename>structAZ__PREC__STRUCT.html</filename>
  </compound>
  <compound kind="struct">
    <name>AZ_SCALING</name>
    <filename>structAZ__SCALING.html</filename>
  </compound>
  <compound kind="struct">
    <name>aztec_choices</name>
    <filename>structaztec__choices.html</filename>
  </compound>
  <compound kind="class">
    <name>AztecOO</name>
    <filename>classAztecOO.html</filename>
    <class kind="struct">AztecOO::MatrixData</class>
    <class kind="struct">AztecOO::OperatorData</class>
    <member kind="function">
      <type>int</type>
      <name>SetPreconditioner</name>
      <anchorfile>classAztecOO.html</anchorfile>
      <anchor>a6a8fd8ccb8530706d6936f249b20c7df</anchor>
      <arglist>(AZ_PRECOND *Prec)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetPreconditioner</name>
      <anchorfile>classAztecOO.html</anchorfile>
      <anchor>a65345952f1a2123fa2ed0fa90a11b2d6</anchor>
      <arglist>(AZ_PREC_FUN prec_function, void *prec_data)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetScaling</name>
      <anchorfile>classAztecOO.html</anchorfile>
      <anchor>a0246a2b3d5c3dc9378ce728754825994</anchor>
      <arglist>(struct AZ_SCALING *Scaling)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetMatrixName</name>
      <anchorfile>classAztecOO.html</anchorfile>
      <anchor>a95dd7993e6ea17ee1708f392e922b3ee</anchor>
      <arglist>(int label)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetLabel</name>
      <anchorfile>classAztecOO.html</anchorfile>
      <anchor>aec10bf780ab82e0713141648a6083bce</anchor>
      <arglist>(const char *const Label)</arglist>
    </member>
    <member kind="function">
      <type>const char *</type>
      <name>GetLabel</name>
      <anchorfile>classAztecOO.html</anchorfile>
      <anchor>a4e911b4fc39ad6426f9168a705e064e9</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>AztecOO</name>
      <anchorfile>classAztecOO.html</anchorfile>
      <anchor>a7dedfdcd1286857e5ebf2175000ff460</anchor>
      <arglist>(Epetra_Operator *A, Epetra_MultiVector *X, Epetra_MultiVector *B)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>AztecOO</name>
      <anchorfile>classAztecOO.html</anchorfile>
      <anchor>a39a9b47a0779aa06a869ae036accd8cc</anchor>
      <arglist>(Epetra_RowMatrix *A, Epetra_MultiVector *X, Epetra_MultiVector *B)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>AztecOO</name>
      <anchorfile>classAztecOO.html</anchorfile>
      <anchor>a122208af66b2599386bb169e09d63c7f</anchor>
      <arglist>(const Epetra_LinearProblem &amp;LinearProblem)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>AztecOO</name>
      <anchorfile>classAztecOO.html</anchorfile>
      <anchor>a0d4cf2c0a28ca16fb44720edb65d356f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>AztecOO</name>
      <anchorfile>classAztecOO.html</anchorfile>
      <anchor>a436d9844bf373b125d07214fc6259797</anchor>
      <arglist>(const AztecOO &amp;Solver)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~AztecOO</name>
      <anchorfile>classAztecOO.html</anchorfile>
      <anchor>a1286dcddf8b3c1998544ae422df25681</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetProblem</name>
      <anchorfile>classAztecOO.html</anchorfile>
      <anchor>a2024b672998df56814d3f385641867d0</anchor>
      <arglist>(const Epetra_LinearProblem &amp;prob, bool call_SetPrecMatrix=false)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetUserOperator</name>
      <anchorfile>classAztecOO.html</anchorfile>
      <anchor>aeea2604aaf8ab629bf9a2f261de2ead1</anchor>
      <arglist>(Epetra_Operator *UserOperator)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetUserMatrix</name>
      <anchorfile>classAztecOO.html</anchorfile>
      <anchor>a9fd49118f943227406641a5b7ee21a63</anchor>
      <arglist>(Epetra_RowMatrix *UserMatrix, bool call_SetPrecMatrix=false)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetLHS</name>
      <anchorfile>classAztecOO.html</anchorfile>
      <anchor>a4d187e2f2438eec2038cb945ffe1a315</anchor>
      <arglist>(Epetra_MultiVector *X)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetRHS</name>
      <anchorfile>classAztecOO.html</anchorfile>
      <anchor>aa63afd6a8cedf3920373afefc8b0313e</anchor>
      <arglist>(Epetra_MultiVector *B)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>UnsetLHSRHS</name>
      <anchorfile>classAztecOO.html</anchorfile>
      <anchor>a6e44b5fa07a5be29b06f26ede5589c00</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetPrecMatrix</name>
      <anchorfile>classAztecOO.html</anchorfile>
      <anchor>a43171222802b012967c9c47aa130b154</anchor>
      <arglist>(Epetra_RowMatrix *PrecMatrix)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetPrecOperator</name>
      <anchorfile>classAztecOO.html</anchorfile>
      <anchor>a6c8ca8871c0b1b563fd288a3c494b068</anchor>
      <arglist>(Epetra_Operator *PrecOperator)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetStatusTest</name>
      <anchorfile>classAztecOO.html</anchorfile>
      <anchor>a6b5ad4abc82f904605b74347516fb04f</anchor>
      <arglist>(AztecOO_StatusTest *StatusTest)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetOutputStream</name>
      <anchorfile>classAztecOO.html</anchorfile>
      <anchor>af0122ec73d7244049be30457f424ffe4</anchor>
      <arglist>(std::ostream &amp;ostrm)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetErrorStream</name>
      <anchorfile>classAztecOO.html</anchorfile>
      <anchor>aced8503f93dcbb70c0cd5ec4a812d795</anchor>
      <arglist>(std::ostream &amp;errstrm)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ConstructPreconditioner</name>
      <anchorfile>classAztecOO.html</anchorfile>
      <anchor>a5abbb09dc41cffe7f32b365e44184b08</anchor>
      <arglist>(double &amp;condest)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>DestroyPreconditioner</name>
      <anchorfile>classAztecOO.html</anchorfile>
      <anchor>a357ca9721aaf6ac2995aa6914bfddf29</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>Condest</name>
      <anchorfile>classAztecOO.html</anchorfile>
      <anchor>a278622d736db1e101c15d1e9caf6f89d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>CheckInput</name>
      <anchorfile>classAztecOO.html</anchorfile>
      <anchor>ad7669a5c8723e2691f1159722358c725</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Epetra_LinearProblem *</type>
      <name>GetProblem</name>
      <anchorfile>classAztecOO.html</anchorfile>
      <anchor>aa3115228f6ea201bfee15be6ae89047c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Epetra_Operator *</type>
      <name>GetUserOperator</name>
      <anchorfile>classAztecOO.html</anchorfile>
      <anchor>a776836fc5b9fd00d534a5be96dc4e2c7</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Epetra_RowMatrix *</type>
      <name>GetUserMatrix</name>
      <anchorfile>classAztecOO.html</anchorfile>
      <anchor>a8e1f2e8f8ed0f653677e1a89e629d55c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Epetra_Operator *</type>
      <name>GetPrecOperator</name>
      <anchorfile>classAztecOO.html</anchorfile>
      <anchor>accb9350227400b986b18f2abb0a3d544</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Epetra_RowMatrix *</type>
      <name>GetPrecMatrix</name>
      <anchorfile>classAztecOO.html</anchorfile>
      <anchor>acb5ce96b19b9fadde5d0b73c584f6cba</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Epetra_MultiVector *</type>
      <name>GetLHS</name>
      <anchorfile>classAztecOO.html</anchorfile>
      <anchor>aec7a89f6e9c18f00d4e7b5d2aae1a4e9</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Epetra_MultiVector *</type>
      <name>GetRHS</name>
      <anchorfile>classAztecOO.html</anchorfile>
      <anchor>a2b5c82f10d8f78835c4a023c00165099</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>PrintLinearSystem</name>
      <anchorfile>classAztecOO.html</anchorfile>
      <anchor>a84c7f75b851f6b64f3ecdf3f1abc6464</anchor>
      <arglist>(const char *name)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetParameters</name>
      <anchorfile>classAztecOO.html</anchorfile>
      <anchor>aecf2bbb7c2bdcf4a12a8ca9e0eb18d9c</anchor>
      <arglist>(Teuchos::ParameterList &amp;parameterlist, bool cerr_warning_if_unused=false)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetAztecDefaults</name>
      <anchorfile>classAztecOO.html</anchorfile>
      <anchor>ad1aee90d580383a95bfc6041d1265189</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetAztecOption</name>
      <anchorfile>classAztecOO.html</anchorfile>
      <anchor>aa0087190b02e3352d0183d9fff5093df</anchor>
      <arglist>(int option, int value)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetAztecOption</name>
      <anchorfile>classAztecOO.html</anchorfile>
      <anchor>ada10722e29b0bf6a8fb9582523f4710a</anchor>
      <arglist>(int option)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetAztecParam</name>
      <anchorfile>classAztecOO.html</anchorfile>
      <anchor>a3225ab0b46750b19cf5578b5dc4b4a0a</anchor>
      <arglist>(int param, double value)</arglist>
    </member>
    <member kind="function">
      <type>const int *</type>
      <name>GetAllAztecOptions</name>
      <anchorfile>classAztecOO.html</anchorfile>
      <anchor>a22c77e9085435b33f484c6d8d801f078</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const double *</type>
      <name>GetAllAztecParams</name>
      <anchorfile>classAztecOO.html</anchorfile>
      <anchor>aa36d8cca3e418e0797d4da6f6215a64e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetAllAztecOptions</name>
      <anchorfile>classAztecOO.html</anchorfile>
      <anchor>a03e033e3adaec8247426f83f939f9246</anchor>
      <arglist>(const int *options)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetAllAztecParams</name>
      <anchorfile>classAztecOO.html</anchorfile>
      <anchor>af55374e815c8b531126c6c04c4125b98</anchor>
      <arglist>(const double *params)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Iterate</name>
      <anchorfile>classAztecOO.html</anchorfile>
      <anchor>a52d7f8c5d48c4df7a7e23fc4c0acb684</anchor>
      <arglist>(long long MaxIters, double Tolerance)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Iterate</name>
      <anchorfile>classAztecOO.html</anchorfile>
      <anchor>af70cb372efa6dbea29e1986ea501870b</anchor>
      <arglist>(Epetra_RowMatrix *A, Epetra_MultiVector *X, Epetra_MultiVector *B, int MaxIters, double Tolerance)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>recursiveIterate</name>
      <anchorfile>classAztecOO.html</anchorfile>
      <anchor>ae12b65655fce0baa13413392cfdfddfa</anchor>
      <arglist>(int MaxIters, double Tolerance)</arglist>
    </member>
    <member kind="function">
      <type>const double *</type>
      <name>GetAztecStatus</name>
      <anchorfile>classAztecOO.html</anchorfile>
      <anchor>a1925a3c53ef09b6bfc02d9bf23d1aef0</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetUseAdaptiveDefaultsTrue</name>
      <anchorfile>classAztecOO.html</anchorfile>
      <anchor>ad85696da98583bca0aba9108bce8c13a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetAdaptiveParams</name>
      <anchorfile>classAztecOO.html</anchorfile>
      <anchor>a9daf66370e375258d21c959e28b20ce9</anchor>
      <arglist>(int NumTrials, double *athresholds, double *rthresholds, double condestThreshold, double maxFill, int maxKspace)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>AdaptiveIterate</name>
      <anchorfile>classAztecOO.html</anchorfile>
      <anchor>a45aa8eebb0d196eb8315ddc539893d2c</anchor>
      <arglist>(int MaxIters, int MaxSolveAttempts, double Tolerance)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumIters</name>
      <anchorfile>classAztecOO.html</anchorfile>
      <anchor>a2268cae918f54a6b9bdc3917d4ca42fe</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>TrueResidual</name>
      <anchorfile>classAztecOO.html</anchorfile>
      <anchor>ab065e09ded59c8173db59b6a6ee7117e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>ScaledResidual</name>
      <anchorfile>classAztecOO.html</anchorfile>
      <anchor>a1eaf17a249a2c3913ed5994d539d2310</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>RecursiveResidual</name>
      <anchorfile>classAztecOO.html</anchorfile>
      <anchor>a7a8f147e0143de2b73a848c9c2b8818b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>SolveTime</name>
      <anchorfile>classAztecOO.html</anchorfile>
      <anchor>ad58d84e5c64130c2e717017ef5793fc8</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetAllAztecStatus</name>
      <anchorfile>classAztecOO.html</anchorfile>
      <anchor>adee07fa9c570f08e083808fc588c73ec</anchor>
      <arglist>(double *status)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>AztecOO</name>
      <anchorfile>classAztecOO.html</anchorfile>
      <anchor>a7dedfdcd1286857e5ebf2175000ff460</anchor>
      <arglist>(Epetra_Operator *A, Epetra_MultiVector *X, Epetra_MultiVector *B)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>AztecOO</name>
      <anchorfile>classAztecOO.html</anchorfile>
      <anchor>a39a9b47a0779aa06a869ae036accd8cc</anchor>
      <arglist>(Epetra_RowMatrix *A, Epetra_MultiVector *X, Epetra_MultiVector *B)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>AztecOO</name>
      <anchorfile>classAztecOO.html</anchorfile>
      <anchor>a122208af66b2599386bb169e09d63c7f</anchor>
      <arglist>(const Epetra_LinearProblem &amp;LinearProblem)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>AztecOO</name>
      <anchorfile>classAztecOO.html</anchorfile>
      <anchor>a0d4cf2c0a28ca16fb44720edb65d356f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>AztecOO</name>
      <anchorfile>classAztecOO.html</anchorfile>
      <anchor>a436d9844bf373b125d07214fc6259797</anchor>
      <arglist>(const AztecOO &amp;Solver)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~AztecOO</name>
      <anchorfile>classAztecOO.html</anchorfile>
      <anchor>a1286dcddf8b3c1998544ae422df25681</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetProblem</name>
      <anchorfile>classAztecOO.html</anchorfile>
      <anchor>a2024b672998df56814d3f385641867d0</anchor>
      <arglist>(const Epetra_LinearProblem &amp;prob, bool call_SetPrecMatrix=false)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetUserOperator</name>
      <anchorfile>classAztecOO.html</anchorfile>
      <anchor>aeea2604aaf8ab629bf9a2f261de2ead1</anchor>
      <arglist>(Epetra_Operator *UserOperator)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetUserMatrix</name>
      <anchorfile>classAztecOO.html</anchorfile>
      <anchor>a9fd49118f943227406641a5b7ee21a63</anchor>
      <arglist>(Epetra_RowMatrix *UserMatrix, bool call_SetPrecMatrix=false)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetLHS</name>
      <anchorfile>classAztecOO.html</anchorfile>
      <anchor>a4d187e2f2438eec2038cb945ffe1a315</anchor>
      <arglist>(Epetra_MultiVector *X)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetRHS</name>
      <anchorfile>classAztecOO.html</anchorfile>
      <anchor>aa63afd6a8cedf3920373afefc8b0313e</anchor>
      <arglist>(Epetra_MultiVector *B)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>UnsetLHSRHS</name>
      <anchorfile>classAztecOO.html</anchorfile>
      <anchor>a6e44b5fa07a5be29b06f26ede5589c00</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetPrecMatrix</name>
      <anchorfile>classAztecOO.html</anchorfile>
      <anchor>a43171222802b012967c9c47aa130b154</anchor>
      <arglist>(Epetra_RowMatrix *PrecMatrix)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetPrecOperator</name>
      <anchorfile>classAztecOO.html</anchorfile>
      <anchor>a6c8ca8871c0b1b563fd288a3c494b068</anchor>
      <arglist>(Epetra_Operator *PrecOperator)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetStatusTest</name>
      <anchorfile>classAztecOO.html</anchorfile>
      <anchor>a6b5ad4abc82f904605b74347516fb04f</anchor>
      <arglist>(AztecOO_StatusTest *StatusTest)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetOutputStream</name>
      <anchorfile>classAztecOO.html</anchorfile>
      <anchor>af0122ec73d7244049be30457f424ffe4</anchor>
      <arglist>(std::ostream &amp;ostrm)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetErrorStream</name>
      <anchorfile>classAztecOO.html</anchorfile>
      <anchor>aced8503f93dcbb70c0cd5ec4a812d795</anchor>
      <arglist>(std::ostream &amp;errstrm)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ConstructPreconditioner</name>
      <anchorfile>classAztecOO.html</anchorfile>
      <anchor>a5abbb09dc41cffe7f32b365e44184b08</anchor>
      <arglist>(double &amp;condest)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>DestroyPreconditioner</name>
      <anchorfile>classAztecOO.html</anchorfile>
      <anchor>a357ca9721aaf6ac2995aa6914bfddf29</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>Condest</name>
      <anchorfile>classAztecOO.html</anchorfile>
      <anchor>a278622d736db1e101c15d1e9caf6f89d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>CheckInput</name>
      <anchorfile>classAztecOO.html</anchorfile>
      <anchor>ad7669a5c8723e2691f1159722358c725</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Epetra_LinearProblem *</type>
      <name>GetProblem</name>
      <anchorfile>classAztecOO.html</anchorfile>
      <anchor>aa3115228f6ea201bfee15be6ae89047c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Epetra_Operator *</type>
      <name>GetUserOperator</name>
      <anchorfile>classAztecOO.html</anchorfile>
      <anchor>a776836fc5b9fd00d534a5be96dc4e2c7</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Epetra_RowMatrix *</type>
      <name>GetUserMatrix</name>
      <anchorfile>classAztecOO.html</anchorfile>
      <anchor>a8e1f2e8f8ed0f653677e1a89e629d55c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Epetra_Operator *</type>
      <name>GetPrecOperator</name>
      <anchorfile>classAztecOO.html</anchorfile>
      <anchor>accb9350227400b986b18f2abb0a3d544</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Epetra_RowMatrix *</type>
      <name>GetPrecMatrix</name>
      <anchorfile>classAztecOO.html</anchorfile>
      <anchor>acb5ce96b19b9fadde5d0b73c584f6cba</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Epetra_MultiVector *</type>
      <name>GetLHS</name>
      <anchorfile>classAztecOO.html</anchorfile>
      <anchor>aec7a89f6e9c18f00d4e7b5d2aae1a4e9</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Epetra_MultiVector *</type>
      <name>GetRHS</name>
      <anchorfile>classAztecOO.html</anchorfile>
      <anchor>a2b5c82f10d8f78835c4a023c00165099</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>PrintLinearSystem</name>
      <anchorfile>classAztecOO.html</anchorfile>
      <anchor>a84c7f75b851f6b64f3ecdf3f1abc6464</anchor>
      <arglist>(const char *name)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetParameters</name>
      <anchorfile>classAztecOO.html</anchorfile>
      <anchor>aecf2bbb7c2bdcf4a12a8ca9e0eb18d9c</anchor>
      <arglist>(Teuchos::ParameterList &amp;parameterlist, bool cerr_warning_if_unused=false)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetAztecDefaults</name>
      <anchorfile>classAztecOO.html</anchorfile>
      <anchor>ad1aee90d580383a95bfc6041d1265189</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetAztecOption</name>
      <anchorfile>classAztecOO.html</anchorfile>
      <anchor>aa0087190b02e3352d0183d9fff5093df</anchor>
      <arglist>(int option, int value)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetAztecOption</name>
      <anchorfile>classAztecOO.html</anchorfile>
      <anchor>ada10722e29b0bf6a8fb9582523f4710a</anchor>
      <arglist>(int option)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetAztecParam</name>
      <anchorfile>classAztecOO.html</anchorfile>
      <anchor>a3225ab0b46750b19cf5578b5dc4b4a0a</anchor>
      <arglist>(int param, double value)</arglist>
    </member>
    <member kind="function">
      <type>const int *</type>
      <name>GetAllAztecOptions</name>
      <anchorfile>classAztecOO.html</anchorfile>
      <anchor>a22c77e9085435b33f484c6d8d801f078</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const double *</type>
      <name>GetAllAztecParams</name>
      <anchorfile>classAztecOO.html</anchorfile>
      <anchor>aa36d8cca3e418e0797d4da6f6215a64e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetAllAztecOptions</name>
      <anchorfile>classAztecOO.html</anchorfile>
      <anchor>a03e033e3adaec8247426f83f939f9246</anchor>
      <arglist>(const int *options)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetAllAztecParams</name>
      <anchorfile>classAztecOO.html</anchorfile>
      <anchor>af55374e815c8b531126c6c04c4125b98</anchor>
      <arglist>(const double *params)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Iterate</name>
      <anchorfile>classAztecOO.html</anchorfile>
      <anchor>a52d7f8c5d48c4df7a7e23fc4c0acb684</anchor>
      <arglist>(long long MaxIters, double Tolerance)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Iterate</name>
      <anchorfile>classAztecOO.html</anchorfile>
      <anchor>af70cb372efa6dbea29e1986ea501870b</anchor>
      <arglist>(Epetra_RowMatrix *A, Epetra_MultiVector *X, Epetra_MultiVector *B, int MaxIters, double Tolerance)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>recursiveIterate</name>
      <anchorfile>classAztecOO.html</anchorfile>
      <anchor>ae12b65655fce0baa13413392cfdfddfa</anchor>
      <arglist>(int MaxIters, double Tolerance)</arglist>
    </member>
    <member kind="function">
      <type>const double *</type>
      <name>GetAztecStatus</name>
      <anchorfile>classAztecOO.html</anchorfile>
      <anchor>a1925a3c53ef09b6bfc02d9bf23d1aef0</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetUseAdaptiveDefaultsTrue</name>
      <anchorfile>classAztecOO.html</anchorfile>
      <anchor>ad85696da98583bca0aba9108bce8c13a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetAdaptiveParams</name>
      <anchorfile>classAztecOO.html</anchorfile>
      <anchor>a9daf66370e375258d21c959e28b20ce9</anchor>
      <arglist>(int NumTrials, double *athresholds, double *rthresholds, double condestThreshold, double maxFill, int maxKspace)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>AdaptiveIterate</name>
      <anchorfile>classAztecOO.html</anchorfile>
      <anchor>a45aa8eebb0d196eb8315ddc539893d2c</anchor>
      <arglist>(int MaxIters, int MaxSolveAttempts, double Tolerance)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumIters</name>
      <anchorfile>classAztecOO.html</anchorfile>
      <anchor>a2268cae918f54a6b9bdc3917d4ca42fe</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>TrueResidual</name>
      <anchorfile>classAztecOO.html</anchorfile>
      <anchor>ab065e09ded59c8173db59b6a6ee7117e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>ScaledResidual</name>
      <anchorfile>classAztecOO.html</anchorfile>
      <anchor>a1eaf17a249a2c3913ed5994d539d2310</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>RecursiveResidual</name>
      <anchorfile>classAztecOO.html</anchorfile>
      <anchor>a7a8f147e0143de2b73a848c9c2b8818b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>SolveTime</name>
      <anchorfile>classAztecOO.html</anchorfile>
      <anchor>ad58d84e5c64130c2e717017ef5793fc8</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetAllAztecStatus</name>
      <anchorfile>classAztecOO.html</anchorfile>
      <anchor>adee07fa9c570f08e083808fc588c73ec</anchor>
      <arglist>(double *status)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>AztecOO_Operator</name>
    <filename>classAztecOO__Operator.html</filename>
    <member kind="function">
      <type></type>
      <name>AztecOO_Operator</name>
      <anchorfile>classAztecOO__Operator.html</anchorfile>
      <anchor>a7e4aaf92130506bbd2fdebfed67ccc54</anchor>
      <arglist>(AztecOO *solver, int NumIters, double Tol=0.0)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~AztecOO_Operator</name>
      <anchorfile>classAztecOO__Operator.html</anchorfile>
      <anchor>a5fe870ab0f43cbdbaffb237f0abf5846</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetUseTranspose</name>
      <anchorfile>classAztecOO__Operator.html</anchorfile>
      <anchor>a41823f0b22efd5429e0e9e7aa809e837</anchor>
      <arglist>(bool use_transpose)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Apply</name>
      <anchorfile>classAztecOO__Operator.html</anchorfile>
      <anchor>aa766c6226c8d0b3058013f66ac86ea87</anchor>
      <arglist>(const Epetra_MultiVector &amp;X, Epetra_MultiVector &amp;Y) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ApplyInverse</name>
      <anchorfile>classAztecOO__Operator.html</anchorfile>
      <anchor>a2d9540232654754a5e4b5c24c114da71</anchor>
      <arglist>(const Epetra_MultiVector &amp;X, Epetra_MultiVector &amp;Y) const </arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>NormInf</name>
      <anchorfile>classAztecOO__Operator.html</anchorfile>
      <anchor>a8c4a73039736a79a54748d609163fc69</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const char *</type>
      <name>Label</name>
      <anchorfile>classAztecOO__Operator.html</anchorfile>
      <anchor>a3b1240e68fc5ec5e1dbe672905018af1</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>AztecOO *</type>
      <name>Solver</name>
      <anchorfile>classAztecOO__Operator.html</anchorfile>
      <anchor>a3899d38cfe4bfb46d29f1feec149feb7</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumIters</name>
      <anchorfile>classAztecOO__Operator.html</anchorfile>
      <anchor>aed4d5a81a7c9229de434776297b7f9b9</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>Tol</name>
      <anchorfile>classAztecOO__Operator.html</anchorfile>
      <anchor>a7788cbe890bc4da283bd5692f44438b8</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>UseTranspose</name>
      <anchorfile>classAztecOO__Operator.html</anchorfile>
      <anchor>a7d77c8136b4e8829b6331f6352f48890</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>HasNormInf</name>
      <anchorfile>classAztecOO__Operator.html</anchorfile>
      <anchor>a233e8186cfabdece5f171ea3308f156b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_Comm &amp;</type>
      <name>Comm</name>
      <anchorfile>classAztecOO__Operator.html</anchorfile>
      <anchor>a7cc75a53975d8e6161d67a5dad17fe05</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_Map &amp;</type>
      <name>OperatorDomainMap</name>
      <anchorfile>classAztecOO__Operator.html</anchorfile>
      <anchor>aa9c2557bd0fa2a4dce1ff872816afc5f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_Map &amp;</type>
      <name>OperatorRangeMap</name>
      <anchorfile>classAztecOO__Operator.html</anchorfile>
      <anchor>a560fad68a551ddc8589a63b21946c8ff</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>AztecOO_Operator</name>
      <anchorfile>classAztecOO__Operator.html</anchorfile>
      <anchor>a7e4aaf92130506bbd2fdebfed67ccc54</anchor>
      <arglist>(AztecOO *solver, int NumIters, double Tol=0.0)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~AztecOO_Operator</name>
      <anchorfile>classAztecOO__Operator.html</anchorfile>
      <anchor>a5fe870ab0f43cbdbaffb237f0abf5846</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetUseTranspose</name>
      <anchorfile>classAztecOO__Operator.html</anchorfile>
      <anchor>a41823f0b22efd5429e0e9e7aa809e837</anchor>
      <arglist>(bool use_transpose)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Apply</name>
      <anchorfile>classAztecOO__Operator.html</anchorfile>
      <anchor>aa766c6226c8d0b3058013f66ac86ea87</anchor>
      <arglist>(const Epetra_MultiVector &amp;X, Epetra_MultiVector &amp;Y) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ApplyInverse</name>
      <anchorfile>classAztecOO__Operator.html</anchorfile>
      <anchor>a2d9540232654754a5e4b5c24c114da71</anchor>
      <arglist>(const Epetra_MultiVector &amp;X, Epetra_MultiVector &amp;Y) const </arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>NormInf</name>
      <anchorfile>classAztecOO__Operator.html</anchorfile>
      <anchor>a8c4a73039736a79a54748d609163fc69</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const char *</type>
      <name>Label</name>
      <anchorfile>classAztecOO__Operator.html</anchorfile>
      <anchor>a3b1240e68fc5ec5e1dbe672905018af1</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>AztecOO *</type>
      <name>Solver</name>
      <anchorfile>classAztecOO__Operator.html</anchorfile>
      <anchor>a3899d38cfe4bfb46d29f1feec149feb7</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumIters</name>
      <anchorfile>classAztecOO__Operator.html</anchorfile>
      <anchor>aed4d5a81a7c9229de434776297b7f9b9</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>Tol</name>
      <anchorfile>classAztecOO__Operator.html</anchorfile>
      <anchor>a7788cbe890bc4da283bd5692f44438b8</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>UseTranspose</name>
      <anchorfile>classAztecOO__Operator.html</anchorfile>
      <anchor>a7d77c8136b4e8829b6331f6352f48890</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>HasNormInf</name>
      <anchorfile>classAztecOO__Operator.html</anchorfile>
      <anchor>a233e8186cfabdece5f171ea3308f156b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_Comm &amp;</type>
      <name>Comm</name>
      <anchorfile>classAztecOO__Operator.html</anchorfile>
      <anchor>a7cc75a53975d8e6161d67a5dad17fe05</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_Map &amp;</type>
      <name>OperatorDomainMap</name>
      <anchorfile>classAztecOO__Operator.html</anchorfile>
      <anchor>aa9c2557bd0fa2a4dce1ff872816afc5f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_Map &amp;</type>
      <name>OperatorRangeMap</name>
      <anchorfile>classAztecOO__Operator.html</anchorfile>
      <anchor>a560fad68a551ddc8589a63b21946c8ff</anchor>
      <arglist>() const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>AztecOO_StatusTest</name>
    <filename>classAztecOO__StatusTest.html</filename>
    <member kind="function">
      <type></type>
      <name>AztecOO_StatusTest</name>
      <anchorfile>classAztecOO__StatusTest.html</anchorfile>
      <anchor>a6c891228735bc81e8fb08e6f643da7a6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~AztecOO_StatusTest</name>
      <anchorfile>classAztecOO__StatusTest.html</anchorfile>
      <anchor>a8a6d140047f8c7611c93a502d23bbd85</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>ResidualVectorRequired</name>
      <anchorfile>classAztecOO__StatusTest.html</anchorfile>
      <anchor>a3e03557dfd75df304adedacd25c016c1</anchor>
      <arglist>() const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual AztecOO_StatusType</type>
      <name>CheckStatus</name>
      <anchorfile>classAztecOO__StatusTest.html</anchorfile>
      <anchor>adca483f9c14b8461635084f764a4e894</anchor>
      <arglist>(int CurrentIter, Epetra_MultiVector *CurrentResVector, double CurrentResNormEst, bool SolutionUpdated)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual AztecOO_StatusType</type>
      <name>GetStatus</name>
      <anchorfile>classAztecOO__StatusTest.html</anchorfile>
      <anchor>a4dd0fe54330dd3c123eb998440309437</anchor>
      <arglist>() const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual std::ostream &amp;</type>
      <name>Print</name>
      <anchorfile>classAztecOO__StatusTest.html</anchorfile>
      <anchor>abba6b46b7d5addc4a64da22b8aa0fb5a</anchor>
      <arglist>(std::ostream &amp;stream, int indent=0) const  =0</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>AztecOO_StatusTest</name>
      <anchorfile>classAztecOO__StatusTest.html</anchorfile>
      <anchor>a6c891228735bc81e8fb08e6f643da7a6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~AztecOO_StatusTest</name>
      <anchorfile>classAztecOO__StatusTest.html</anchorfile>
      <anchor>a8a6d140047f8c7611c93a502d23bbd85</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>ResidualVectorRequired</name>
      <anchorfile>classAztecOO__StatusTest.html</anchorfile>
      <anchor>a3e03557dfd75df304adedacd25c016c1</anchor>
      <arglist>() const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual AztecOO_StatusType</type>
      <name>CheckStatus</name>
      <anchorfile>classAztecOO__StatusTest.html</anchorfile>
      <anchor>adca483f9c14b8461635084f764a4e894</anchor>
      <arglist>(int CurrentIter, Epetra_MultiVector *CurrentResVector, double CurrentResNormEst, bool SolutionUpdated)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual AztecOO_StatusType</type>
      <name>GetStatus</name>
      <anchorfile>classAztecOO__StatusTest.html</anchorfile>
      <anchor>a4dd0fe54330dd3c123eb998440309437</anchor>
      <arglist>() const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual std::ostream &amp;</type>
      <name>Print</name>
      <anchorfile>classAztecOO__StatusTest.html</anchorfile>
      <anchor>abba6b46b7d5addc4a64da22b8aa0fb5a</anchor>
      <arglist>(std::ostream &amp;stream, int indent=0) const  =0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>AztecOO_StatusTestCombo</name>
    <filename>classAztecOO__StatusTestCombo.html</filename>
    <base>AztecOO_StatusTest</base>
    <member kind="enumvalue">
      <name>AND</name>
      <anchorfile>classAztecOO__StatusTestCombo.html</anchorfile>
      <anchor>a2d37fb53673826c2a98be1c4c5417c96ae80587ab98930cec171b597cf84ffa85</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>OR</name>
      <anchorfile>classAztecOO__StatusTestCombo.html</anchorfile>
      <anchor>a2d37fb53673826c2a98be1c4c5417c96a986ab28cfacee508f7b74db786bed7e2</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SEQ</name>
      <anchorfile>classAztecOO__StatusTestCombo.html</anchorfile>
      <anchor>a2d37fb53673826c2a98be1c4c5417c96aadc323bb366cfadaf4aef068db52999d</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>ComboType</name>
      <anchorfile>classAztecOO__StatusTestCombo.html</anchorfile>
      <anchor>a2d37fb53673826c2a98be1c4c5417c96</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>AND</name>
      <anchorfile>classAztecOO__StatusTestCombo.html</anchorfile>
      <anchor>a2d37fb53673826c2a98be1c4c5417c96ae80587ab98930cec171b597cf84ffa85</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>OR</name>
      <anchorfile>classAztecOO__StatusTestCombo.html</anchorfile>
      <anchor>a2d37fb53673826c2a98be1c4c5417c96a986ab28cfacee508f7b74db786bed7e2</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SEQ</name>
      <anchorfile>classAztecOO__StatusTestCombo.html</anchorfile>
      <anchor>a2d37fb53673826c2a98be1c4c5417c96aadc323bb366cfadaf4aef068db52999d</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>AztecOO_StatusTestCombo</name>
      <anchorfile>classAztecOO__StatusTestCombo.html</anchorfile>
      <anchor>af2a03b36d9a4eb4fca2911895469815e</anchor>
      <arglist>(ComboType t)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>AztecOO_StatusTestCombo</name>
      <anchorfile>classAztecOO__StatusTestCombo.html</anchorfile>
      <anchor>a2093ac1b3ae4211750534b1a1f03aaf5</anchor>
      <arglist>(ComboType t, AztecOO_StatusTest &amp;a)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>AztecOO_StatusTestCombo</name>
      <anchorfile>classAztecOO__StatusTestCombo.html</anchorfile>
      <anchor>aa26bed29e6fceac40eee858d08a7421b</anchor>
      <arglist>(ComboType t, AztecOO_StatusTest &amp;a, AztecOO_StatusTest &amp;b)</arglist>
    </member>
    <member kind="function">
      <type>AztecOO_StatusTestCombo &amp;</type>
      <name>AddStatusTest</name>
      <anchorfile>classAztecOO__StatusTestCombo.html</anchorfile>
      <anchor>aff1de1c485609c4041faeef9b7ed2b50</anchor>
      <arglist>(AztecOO_StatusTest &amp;a)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~AztecOO_StatusTestCombo</name>
      <anchorfile>classAztecOO__StatusTestCombo.html</anchorfile>
      <anchor>a336ca3fd88128ccef80921c7a7043a7d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>ResidualVectorRequired</name>
      <anchorfile>classAztecOO__StatusTestCombo.html</anchorfile>
      <anchor>aa0e685110023f80bbdd888492d57d047</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>AztecOO_StatusType</type>
      <name>CheckStatus</name>
      <anchorfile>classAztecOO__StatusTestCombo.html</anchorfile>
      <anchor>a73df8ac868d3776256bd3a159cec7e98</anchor>
      <arglist>(int CurrentIter, Epetra_MultiVector *CurrentResVector, double CurrentResNormEst, bool SolutionUpdated)</arglist>
    </member>
    <member kind="function">
      <type>AztecOO_StatusType</type>
      <name>GetStatus</name>
      <anchorfile>classAztecOO__StatusTestCombo.html</anchorfile>
      <anchor>a714a6d1d1a5fe9cddadb95ec8554c1c8</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>std::ostream &amp;</type>
      <name>Print</name>
      <anchorfile>classAztecOO__StatusTestCombo.html</anchorfile>
      <anchor>aa49128fe57bff2ec04e82dccfc2099c5</anchor>
      <arglist>(std::ostream &amp;stream, int indent=0) const </arglist>
    </member>
    <member kind="function">
      <type>ComboType</type>
      <name>GetComboType</name>
      <anchorfile>classAztecOO__StatusTestCombo.html</anchorfile>
      <anchor>aa67e02b4b0e939761589c7a7bcc05c5b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>OrOp</name>
      <anchorfile>classAztecOO__StatusTestCombo.html</anchorfile>
      <anchor>a5adbe0f3a9352c339c7930b32f077b6d</anchor>
      <arglist>(int CurrentIter, Epetra_MultiVector *CurrentResVector, double CurrentResNormEst, bool SolutionUpdated)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>AndOp</name>
      <anchorfile>classAztecOO__StatusTestCombo.html</anchorfile>
      <anchor>af4b2fbd43805444507c6587752c79637</anchor>
      <arglist>(int CurrentIter, Epetra_MultiVector *CurrentResVector, double CurrentResNormEst, bool SolutionUpdated)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>SeqOp</name>
      <anchorfile>classAztecOO__StatusTestCombo.html</anchorfile>
      <anchor>a7842ccd5097fc868a77fa7fe6ee32a62</anchor>
      <arglist>(int CurrentIter, Epetra_MultiVector *CurrentResVector, double CurrentResNormEst, bool SolutionUpdated)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>bool</type>
      <name>IsSafe</name>
      <anchorfile>classAztecOO__StatusTestCombo.html</anchorfile>
      <anchor>a726755d53df71008424f1b7e6b3c5729</anchor>
      <arglist>(AztecOO_StatusTest &amp;a)</arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>ComboType</name>
      <anchorfile>classAztecOO__StatusTestCombo.html</anchorfile>
      <anchor>a2d37fb53673826c2a98be1c4c5417c96</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>AND</name>
      <anchorfile>classAztecOO__StatusTestCombo.html</anchorfile>
      <anchor>a2d37fb53673826c2a98be1c4c5417c96ae80587ab98930cec171b597cf84ffa85</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>OR</name>
      <anchorfile>classAztecOO__StatusTestCombo.html</anchorfile>
      <anchor>a2d37fb53673826c2a98be1c4c5417c96a986ab28cfacee508f7b74db786bed7e2</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SEQ</name>
      <anchorfile>classAztecOO__StatusTestCombo.html</anchorfile>
      <anchor>a2d37fb53673826c2a98be1c4c5417c96aadc323bb366cfadaf4aef068db52999d</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>AztecOO_StatusTestCombo</name>
      <anchorfile>classAztecOO__StatusTestCombo.html</anchorfile>
      <anchor>af2a03b36d9a4eb4fca2911895469815e</anchor>
      <arglist>(ComboType t)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>AztecOO_StatusTestCombo</name>
      <anchorfile>classAztecOO__StatusTestCombo.html</anchorfile>
      <anchor>a2093ac1b3ae4211750534b1a1f03aaf5</anchor>
      <arglist>(ComboType t, AztecOO_StatusTest &amp;a)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>AztecOO_StatusTestCombo</name>
      <anchorfile>classAztecOO__StatusTestCombo.html</anchorfile>
      <anchor>aa26bed29e6fceac40eee858d08a7421b</anchor>
      <arglist>(ComboType t, AztecOO_StatusTest &amp;a, AztecOO_StatusTest &amp;b)</arglist>
    </member>
    <member kind="function">
      <type>AztecOO_StatusTestCombo &amp;</type>
      <name>AddStatusTest</name>
      <anchorfile>classAztecOO__StatusTestCombo.html</anchorfile>
      <anchor>aff1de1c485609c4041faeef9b7ed2b50</anchor>
      <arglist>(AztecOO_StatusTest &amp;a)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~AztecOO_StatusTestCombo</name>
      <anchorfile>classAztecOO__StatusTestCombo.html</anchorfile>
      <anchor>a336ca3fd88128ccef80921c7a7043a7d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>ResidualVectorRequired</name>
      <anchorfile>classAztecOO__StatusTestCombo.html</anchorfile>
      <anchor>aa0e685110023f80bbdd888492d57d047</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>AztecOO_StatusType</type>
      <name>CheckStatus</name>
      <anchorfile>classAztecOO__StatusTestCombo.html</anchorfile>
      <anchor>a73df8ac868d3776256bd3a159cec7e98</anchor>
      <arglist>(int CurrentIter, Epetra_MultiVector *CurrentResVector, double CurrentResNormEst, bool SolutionUpdated)</arglist>
    </member>
    <member kind="function">
      <type>AztecOO_StatusType</type>
      <name>GetStatus</name>
      <anchorfile>classAztecOO__StatusTestCombo.html</anchorfile>
      <anchor>a714a6d1d1a5fe9cddadb95ec8554c1c8</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>std::ostream &amp;</type>
      <name>Print</name>
      <anchorfile>classAztecOO__StatusTestCombo.html</anchorfile>
      <anchor>aa49128fe57bff2ec04e82dccfc2099c5</anchor>
      <arglist>(std::ostream &amp;stream, int indent=0) const </arglist>
    </member>
    <member kind="function">
      <type>ComboType</type>
      <name>GetComboType</name>
      <anchorfile>classAztecOO__StatusTestCombo.html</anchorfile>
      <anchor>aa67e02b4b0e939761589c7a7bcc05c5b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>OrOp</name>
      <anchorfile>classAztecOO__StatusTestCombo.html</anchorfile>
      <anchor>a5adbe0f3a9352c339c7930b32f077b6d</anchor>
      <arglist>(int CurrentIter, Epetra_MultiVector *CurrentResVector, double CurrentResNormEst, bool SolutionUpdated)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>AndOp</name>
      <anchorfile>classAztecOO__StatusTestCombo.html</anchorfile>
      <anchor>af4b2fbd43805444507c6587752c79637</anchor>
      <arglist>(int CurrentIter, Epetra_MultiVector *CurrentResVector, double CurrentResNormEst, bool SolutionUpdated)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>SeqOp</name>
      <anchorfile>classAztecOO__StatusTestCombo.html</anchorfile>
      <anchor>a7842ccd5097fc868a77fa7fe6ee32a62</anchor>
      <arglist>(int CurrentIter, Epetra_MultiVector *CurrentResVector, double CurrentResNormEst, bool SolutionUpdated)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>bool</type>
      <name>IsSafe</name>
      <anchorfile>classAztecOO__StatusTestCombo.html</anchorfile>
      <anchor>a726755d53df71008424f1b7e6b3c5729</anchor>
      <arglist>(AztecOO_StatusTest &amp;a)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>AztecOO_StatusTestMaxIters</name>
    <filename>classAztecOO__StatusTestMaxIters.html</filename>
    <base>AztecOO_StatusTest</base>
    <member kind="function">
      <type></type>
      <name>AztecOO_StatusTestMaxIters</name>
      <anchorfile>classAztecOO__StatusTestMaxIters.html</anchorfile>
      <anchor>a6919050c1801751ee5fc2a732fc79640</anchor>
      <arglist>(int MaxIters)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~AztecOO_StatusTestMaxIters</name>
      <anchorfile>classAztecOO__StatusTestMaxIters.html</anchorfile>
      <anchor>a18ad112184047bf555edc814ed48d708</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>ResidualVectorRequired</name>
      <anchorfile>classAztecOO__StatusTestMaxIters.html</anchorfile>
      <anchor>a085a6fb05c61d971322d3d83c21e15d8</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>AztecOO_StatusType</type>
      <name>CheckStatus</name>
      <anchorfile>classAztecOO__StatusTestMaxIters.html</anchorfile>
      <anchor>aa2e88cad0c20da501abf586f809b4bc8</anchor>
      <arglist>(int CurrentIter, Epetra_MultiVector *CurrentResVector, double CurrentResNormEst, bool SolutionUpdated)</arglist>
    </member>
    <member kind="function">
      <type>AztecOO_StatusType</type>
      <name>GetStatus</name>
      <anchorfile>classAztecOO__StatusTestMaxIters.html</anchorfile>
      <anchor>a0a8c2f810b604c7da65e2798d6138566</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>std::ostream &amp;</type>
      <name>Print</name>
      <anchorfile>classAztecOO__StatusTestMaxIters.html</anchorfile>
      <anchor>a1dcc04bd366535ce0f9e8cbb4ad9ffd9</anchor>
      <arglist>(std::ostream &amp;stream, int indent=0) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetMaxIters</name>
      <anchorfile>classAztecOO__StatusTestMaxIters.html</anchorfile>
      <anchor>a2980ed58657bc92aa8e45d0eeb689225</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetNumIters</name>
      <anchorfile>classAztecOO__StatusTestMaxIters.html</anchorfile>
      <anchor>adad5fc3d4e42c5a52fda70143500152a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>AztecOO_StatusTestMaxIters</name>
      <anchorfile>classAztecOO__StatusTestMaxIters.html</anchorfile>
      <anchor>a6919050c1801751ee5fc2a732fc79640</anchor>
      <arglist>(int MaxIters)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~AztecOO_StatusTestMaxIters</name>
      <anchorfile>classAztecOO__StatusTestMaxIters.html</anchorfile>
      <anchor>a18ad112184047bf555edc814ed48d708</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>ResidualVectorRequired</name>
      <anchorfile>classAztecOO__StatusTestMaxIters.html</anchorfile>
      <anchor>a085a6fb05c61d971322d3d83c21e15d8</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>AztecOO_StatusType</type>
      <name>CheckStatus</name>
      <anchorfile>classAztecOO__StatusTestMaxIters.html</anchorfile>
      <anchor>aa2e88cad0c20da501abf586f809b4bc8</anchor>
      <arglist>(int CurrentIter, Epetra_MultiVector *CurrentResVector, double CurrentResNormEst, bool SolutionUpdated)</arglist>
    </member>
    <member kind="function">
      <type>AztecOO_StatusType</type>
      <name>GetStatus</name>
      <anchorfile>classAztecOO__StatusTestMaxIters.html</anchorfile>
      <anchor>a0a8c2f810b604c7da65e2798d6138566</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>std::ostream &amp;</type>
      <name>Print</name>
      <anchorfile>classAztecOO__StatusTestMaxIters.html</anchorfile>
      <anchor>a1dcc04bd366535ce0f9e8cbb4ad9ffd9</anchor>
      <arglist>(std::ostream &amp;stream, int indent=0) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetMaxIters</name>
      <anchorfile>classAztecOO__StatusTestMaxIters.html</anchorfile>
      <anchor>a2980ed58657bc92aa8e45d0eeb689225</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetNumIters</name>
      <anchorfile>classAztecOO__StatusTestMaxIters.html</anchorfile>
      <anchor>adad5fc3d4e42c5a52fda70143500152a</anchor>
      <arglist>() const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>AztecOO_StatusTestResNorm</name>
    <filename>classAztecOO__StatusTestResNorm.html</filename>
    <base>AztecOO_StatusTest</base>
    <member kind="enumvalue">
      <name>Implicit</name>
      <anchorfile>classAztecOO__StatusTestResNorm.html</anchorfile>
      <anchor>ad1dc6cab3b18a9806ae25cd282eefed0a0ad9cb7365c3c3f27e65518eb652d10b</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>Explicit</name>
      <anchorfile>classAztecOO__StatusTestResNorm.html</anchorfile>
      <anchor>ad1dc6cab3b18a9806ae25cd282eefed0a3f813b7adb59bd93150b46faf93d6803</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>OneNorm</name>
      <anchorfile>classAztecOO__StatusTestResNorm.html</anchorfile>
      <anchor>a34110b05165d61286337f02f1150bd3da94cca3097a9b1cc3756cf048f8a5d21d</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>TwoNorm</name>
      <anchorfile>classAztecOO__StatusTestResNorm.html</anchorfile>
      <anchor>a34110b05165d61286337f02f1150bd3dacbb5fb9676f15defb1007d87889c46f7</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>InfNorm</name>
      <anchorfile>classAztecOO__StatusTestResNorm.html</anchorfile>
      <anchor>a34110b05165d61286337f02f1150bd3da4a6272e5afa69bdcdcb4c011e3292e34</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>NormOfRHS</name>
      <anchorfile>classAztecOO__StatusTestResNorm.html</anchorfile>
      <anchor>a49884bd281af874e277c7e14cf4f52feaf2437ffc9b9e89fa9bc08e54f81e62bd</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>NormOfInitRes</name>
      <anchorfile>classAztecOO__StatusTestResNorm.html</anchorfile>
      <anchor>a49884bd281af874e277c7e14cf4f52feafc2446aa89ec34f52f7448690a4479af</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>None</name>
      <anchorfile>classAztecOO__StatusTestResNorm.html</anchorfile>
      <anchor>a49884bd281af874e277c7e14cf4f52feaa4c4a16ea29d027e11dfedc42226d7f9</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>UserProvided</name>
      <anchorfile>classAztecOO__StatusTestResNorm.html</anchorfile>
      <anchor>a49884bd281af874e277c7e14cf4f52fea89ef4e799e63b7051b31c8241f6a789c</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>ResType</name>
      <anchorfile>classAztecOO__StatusTestResNorm.html</anchorfile>
      <anchor>ad1dc6cab3b18a9806ae25cd282eefed0</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>Implicit</name>
      <anchorfile>classAztecOO__StatusTestResNorm.html</anchorfile>
      <anchor>ad1dc6cab3b18a9806ae25cd282eefed0a0ad9cb7365c3c3f27e65518eb652d10b</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>Explicit</name>
      <anchorfile>classAztecOO__StatusTestResNorm.html</anchorfile>
      <anchor>ad1dc6cab3b18a9806ae25cd282eefed0a3f813b7adb59bd93150b46faf93d6803</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>NormType</name>
      <anchorfile>classAztecOO__StatusTestResNorm.html</anchorfile>
      <anchor>a34110b05165d61286337f02f1150bd3d</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>OneNorm</name>
      <anchorfile>classAztecOO__StatusTestResNorm.html</anchorfile>
      <anchor>a34110b05165d61286337f02f1150bd3da94cca3097a9b1cc3756cf048f8a5d21d</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>TwoNorm</name>
      <anchorfile>classAztecOO__StatusTestResNorm.html</anchorfile>
      <anchor>a34110b05165d61286337f02f1150bd3dacbb5fb9676f15defb1007d87889c46f7</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>InfNorm</name>
      <anchorfile>classAztecOO__StatusTestResNorm.html</anchorfile>
      <anchor>a34110b05165d61286337f02f1150bd3da4a6272e5afa69bdcdcb4c011e3292e34</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>ScaleType</name>
      <anchorfile>classAztecOO__StatusTestResNorm.html</anchorfile>
      <anchor>a49884bd281af874e277c7e14cf4f52fe</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>NormOfRHS</name>
      <anchorfile>classAztecOO__StatusTestResNorm.html</anchorfile>
      <anchor>a49884bd281af874e277c7e14cf4f52feaf2437ffc9b9e89fa9bc08e54f81e62bd</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>NormOfInitRes</name>
      <anchorfile>classAztecOO__StatusTestResNorm.html</anchorfile>
      <anchor>a49884bd281af874e277c7e14cf4f52feafc2446aa89ec34f52f7448690a4479af</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>None</name>
      <anchorfile>classAztecOO__StatusTestResNorm.html</anchorfile>
      <anchor>a49884bd281af874e277c7e14cf4f52feaa4c4a16ea29d027e11dfedc42226d7f9</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>UserProvided</name>
      <anchorfile>classAztecOO__StatusTestResNorm.html</anchorfile>
      <anchor>a49884bd281af874e277c7e14cf4f52fea89ef4e799e63b7051b31c8241f6a789c</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>AztecOO_StatusTestResNorm</name>
      <anchorfile>classAztecOO__StatusTestResNorm.html</anchorfile>
      <anchor>a483ff878e82232aa4c1503eb56b93c4d</anchor>
      <arglist>(const Epetra_Operator &amp;Operator, const Epetra_Vector &amp;LHS, const Epetra_Vector &amp;RHS, double Tolerance)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~AztecOO_StatusTestResNorm</name>
      <anchorfile>classAztecOO__StatusTestResNorm.html</anchorfile>
      <anchor>ae96a0bc4c3b10ada03a14e324f49181c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>DefineResForm</name>
      <anchorfile>classAztecOO__StatusTestResNorm.html</anchorfile>
      <anchor>a08ebf787679e83e4d8fcbc42f9272a8c</anchor>
      <arglist>(ResType TypeOfResidual, NormType TypeOfNorm, Epetra_Vector *Weights=0)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>DefineScaleForm</name>
      <anchorfile>classAztecOO__StatusTestResNorm.html</anchorfile>
      <anchor>a3c41e06c493d0a13b854be31fa0a7e75</anchor>
      <arglist>(ScaleType TypeOfScaling, NormType TypeOfNorm, Epetra_Vector *Weights=0, double ScaleValue=1.0)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ResetTolerance</name>
      <anchorfile>classAztecOO__StatusTestResNorm.html</anchorfile>
      <anchor>a15173268000a9be2fe3fa58809fa61d4</anchor>
      <arglist>(double Tolerance)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetMaxNumExtraIterations</name>
      <anchorfile>classAztecOO__StatusTestResNorm.html</anchorfile>
      <anchor>a90b457436e927c883567ddbd2d114137</anchor>
      <arglist>(int maxNumExtraIterations)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetMaxNumExtraIterations</name>
      <anchorfile>classAztecOO__StatusTestResNorm.html</anchorfile>
      <anchor>acff00ff388a9d8351e92b506c4491810</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>ResidualVectorRequired</name>
      <anchorfile>classAztecOO__StatusTestResNorm.html</anchorfile>
      <anchor>a9592eeb9ebbb2ace7e94da31757a9844</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>AztecOO_StatusType</type>
      <name>CheckStatus</name>
      <anchorfile>classAztecOO__StatusTestResNorm.html</anchorfile>
      <anchor>a6167a3f648d5e629ca8db05d727ca247</anchor>
      <arglist>(int CurrentIter, Epetra_MultiVector *CurrentResVector, double CurrentResNormEst, bool SolutionUpdated)</arglist>
    </member>
    <member kind="function">
      <type>AztecOO_StatusType</type>
      <name>GetStatus</name>
      <anchorfile>classAztecOO__StatusTestResNorm.html</anchorfile>
      <anchor>ab8a3971be9acccd19139bcd9afd48eb0</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>std::ostream &amp;</type>
      <name>Print</name>
      <anchorfile>classAztecOO__StatusTestResNorm.html</anchorfile>
      <anchor>a1d7f564f7db96e84545ac86f6e2119ad</anchor>
      <arglist>(std::ostream &amp;stream, int indent=0) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>ResetStatus</name>
      <anchorfile>classAztecOO__StatusTestResNorm.html</anchorfile>
      <anchor>aa52f7b38333c9aa86b101e7c00bb59dc</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>GetTolerance</name>
      <anchorfile>classAztecOO__StatusTestResNorm.html</anchorfile>
      <anchor>abcfe60cb889b114c05fbe7ff9216b418</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>GetTestValue</name>
      <anchorfile>classAztecOO__StatusTestResNorm.html</anchorfile>
      <anchor>a38e5a29a084f70ef72bbfcb201d362d8</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>GetResNormValue</name>
      <anchorfile>classAztecOO__StatusTestResNorm.html</anchorfile>
      <anchor>ad1bd8d54da615166c88d5ab7f061e800</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>GetScaledNormValue</name>
      <anchorfile>classAztecOO__StatusTestResNorm.html</anchorfile>
      <anchor>a1d61daa3d6b060cb3f1f3e912526ea2d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>ResType</name>
      <anchorfile>classAztecOO__StatusTestResNorm.html</anchorfile>
      <anchor>ad1dc6cab3b18a9806ae25cd282eefed0</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>Implicit</name>
      <anchorfile>classAztecOO__StatusTestResNorm.html</anchorfile>
      <anchor>ad1dc6cab3b18a9806ae25cd282eefed0a0ad9cb7365c3c3f27e65518eb652d10b</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>Explicit</name>
      <anchorfile>classAztecOO__StatusTestResNorm.html</anchorfile>
      <anchor>ad1dc6cab3b18a9806ae25cd282eefed0a3f813b7adb59bd93150b46faf93d6803</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>NormType</name>
      <anchorfile>classAztecOO__StatusTestResNorm.html</anchorfile>
      <anchor>a34110b05165d61286337f02f1150bd3d</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>OneNorm</name>
      <anchorfile>classAztecOO__StatusTestResNorm.html</anchorfile>
      <anchor>a34110b05165d61286337f02f1150bd3da94cca3097a9b1cc3756cf048f8a5d21d</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>TwoNorm</name>
      <anchorfile>classAztecOO__StatusTestResNorm.html</anchorfile>
      <anchor>a34110b05165d61286337f02f1150bd3dacbb5fb9676f15defb1007d87889c46f7</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>InfNorm</name>
      <anchorfile>classAztecOO__StatusTestResNorm.html</anchorfile>
      <anchor>a34110b05165d61286337f02f1150bd3da4a6272e5afa69bdcdcb4c011e3292e34</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>ScaleType</name>
      <anchorfile>classAztecOO__StatusTestResNorm.html</anchorfile>
      <anchor>a49884bd281af874e277c7e14cf4f52fe</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>NormOfRHS</name>
      <anchorfile>classAztecOO__StatusTestResNorm.html</anchorfile>
      <anchor>a49884bd281af874e277c7e14cf4f52feaf2437ffc9b9e89fa9bc08e54f81e62bd</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>NormOfInitRes</name>
      <anchorfile>classAztecOO__StatusTestResNorm.html</anchorfile>
      <anchor>a49884bd281af874e277c7e14cf4f52feafc2446aa89ec34f52f7448690a4479af</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>None</name>
      <anchorfile>classAztecOO__StatusTestResNorm.html</anchorfile>
      <anchor>a49884bd281af874e277c7e14cf4f52feaa4c4a16ea29d027e11dfedc42226d7f9</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>UserProvided</name>
      <anchorfile>classAztecOO__StatusTestResNorm.html</anchorfile>
      <anchor>a49884bd281af874e277c7e14cf4f52fea89ef4e799e63b7051b31c8241f6a789c</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>AztecOO_StatusTestResNorm</name>
      <anchorfile>classAztecOO__StatusTestResNorm.html</anchorfile>
      <anchor>a483ff878e82232aa4c1503eb56b93c4d</anchor>
      <arglist>(const Epetra_Operator &amp;Operator, const Epetra_Vector &amp;LHS, const Epetra_Vector &amp;RHS, double Tolerance)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~AztecOO_StatusTestResNorm</name>
      <anchorfile>classAztecOO__StatusTestResNorm.html</anchorfile>
      <anchor>ae96a0bc4c3b10ada03a14e324f49181c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>DefineResForm</name>
      <anchorfile>classAztecOO__StatusTestResNorm.html</anchorfile>
      <anchor>a08ebf787679e83e4d8fcbc42f9272a8c</anchor>
      <arglist>(ResType TypeOfResidual, NormType TypeOfNorm, Epetra_Vector *Weights=0)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>DefineScaleForm</name>
      <anchorfile>classAztecOO__StatusTestResNorm.html</anchorfile>
      <anchor>a3c41e06c493d0a13b854be31fa0a7e75</anchor>
      <arglist>(ScaleType TypeOfScaling, NormType TypeOfNorm, Epetra_Vector *Weights=0, double ScaleValue=1.0)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ResetTolerance</name>
      <anchorfile>classAztecOO__StatusTestResNorm.html</anchorfile>
      <anchor>a15173268000a9be2fe3fa58809fa61d4</anchor>
      <arglist>(double Tolerance)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetMaxNumExtraIterations</name>
      <anchorfile>classAztecOO__StatusTestResNorm.html</anchorfile>
      <anchor>a90b457436e927c883567ddbd2d114137</anchor>
      <arglist>(int maxNumExtraIterations)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetMaxNumExtraIterations</name>
      <anchorfile>classAztecOO__StatusTestResNorm.html</anchorfile>
      <anchor>acff00ff388a9d8351e92b506c4491810</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>ResidualVectorRequired</name>
      <anchorfile>classAztecOO__StatusTestResNorm.html</anchorfile>
      <anchor>a9592eeb9ebbb2ace7e94da31757a9844</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>AztecOO_StatusType</type>
      <name>CheckStatus</name>
      <anchorfile>classAztecOO__StatusTestResNorm.html</anchorfile>
      <anchor>a6167a3f648d5e629ca8db05d727ca247</anchor>
      <arglist>(int CurrentIter, Epetra_MultiVector *CurrentResVector, double CurrentResNormEst, bool SolutionUpdated)</arglist>
    </member>
    <member kind="function">
      <type>AztecOO_StatusType</type>
      <name>GetStatus</name>
      <anchorfile>classAztecOO__StatusTestResNorm.html</anchorfile>
      <anchor>ab8a3971be9acccd19139bcd9afd48eb0</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>std::ostream &amp;</type>
      <name>Print</name>
      <anchorfile>classAztecOO__StatusTestResNorm.html</anchorfile>
      <anchor>a1d7f564f7db96e84545ac86f6e2119ad</anchor>
      <arglist>(std::ostream &amp;stream, int indent=0) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>ResetStatus</name>
      <anchorfile>classAztecOO__StatusTestResNorm.html</anchorfile>
      <anchor>aa52f7b38333c9aa86b101e7c00bb59dc</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>GetTolerance</name>
      <anchorfile>classAztecOO__StatusTestResNorm.html</anchorfile>
      <anchor>abcfe60cb889b114c05fbe7ff9216b418</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>GetTestValue</name>
      <anchorfile>classAztecOO__StatusTestResNorm.html</anchorfile>
      <anchor>a38e5a29a084f70ef72bbfcb201d362d8</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>GetResNormValue</name>
      <anchorfile>classAztecOO__StatusTestResNorm.html</anchorfile>
      <anchor>ad1bd8d54da615166c88d5ab7f061e800</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>GetScaledNormValue</name>
      <anchorfile>classAztecOO__StatusTestResNorm.html</anchorfile>
      <anchor>a1d61daa3d6b060cb3f1f3e912526ea2d</anchor>
      <arglist>() const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>AztecOOConditionNumber</name>
    <filename>classAztecOOConditionNumber.html</filename>
    <member kind="enumeration">
      <type></type>
      <name>SolverType</name>
      <anchorfile>classAztecOOConditionNumber.html</anchorfile>
      <anchor>a78191643e02acb922487b1cd69d6ed76</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CG_</name>
      <anchorfile>classAztecOOConditionNumber.html</anchorfile>
      <anchor>a78191643e02acb922487b1cd69d6ed76a5848921ca7e0e6a4bcd9a82a04dffa20</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>GMRES_</name>
      <anchorfile>classAztecOOConditionNumber.html</anchorfile>
      <anchor>a78191643e02acb922487b1cd69d6ed76aa1753422112e034ab101c52c2cb271c4</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CG_</name>
      <anchorfile>classAztecOOConditionNumber.html</anchorfile>
      <anchor>a78191643e02acb922487b1cd69d6ed76a5848921ca7e0e6a4bcd9a82a04dffa20</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>GMRES_</name>
      <anchorfile>classAztecOOConditionNumber.html</anchorfile>
      <anchor>a78191643e02acb922487b1cd69d6ed76aa1753422112e034ab101c52c2cb271c4</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>AztecOOConditionNumber</name>
      <anchorfile>classAztecOOConditionNumber.html</anchorfile>
      <anchor>a1a5319145db50bbacc22691d89ff1443</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~AztecOOConditionNumber</name>
      <anchorfile>classAztecOOConditionNumber.html</anchorfile>
      <anchor>aa44a90e4064b2a24c25bf1eaa673bcc6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initialize</name>
      <anchorfile>classAztecOOConditionNumber.html</anchorfile>
      <anchor>a881486abc19942daa57469a9e4fa523c</anchor>
      <arglist>(const Epetra_Operator &amp;op, SolverType solverType=GMRES_, int krylovSubspaceSize=100, bool printSolve=false)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>computeConditionNumber</name>
      <anchorfile>classAztecOOConditionNumber.html</anchorfile>
      <anchor>a474841f1e1e1417c5536e2e115d4c911</anchor>
      <arglist>(int maxIters, double tol)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>getConditionNumber</name>
      <anchorfile>classAztecOOConditionNumber.html</anchorfile>
      <anchor>aa7d36104d3debd82c7c053c409f077e2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>freeMemory</name>
      <anchorfile>classAztecOOConditionNumber.html</anchorfile>
      <anchor>a8bb23f60485109fbc4ea76cd271208d1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>double</type>
      <name>conditionNumber_</name>
      <anchorfile>classAztecOOConditionNumber.html</anchorfile>
      <anchor>ab335509c79debfc833a184efa0ea0bce</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>Epetra_Map *</type>
      <name>domainMap_</name>
      <anchorfile>classAztecOOConditionNumber.html</anchorfile>
      <anchor>aa3664715b594c3ebbd96f2e7dc726dbf</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>Epetra_Map *</type>
      <name>rangeMap_</name>
      <anchorfile>classAztecOOConditionNumber.html</anchorfile>
      <anchor>ab9c8d98d8b64ea336d7623d7338aa737</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>Epetra_Operator *</type>
      <name>operator_</name>
      <anchorfile>classAztecOOConditionNumber.html</anchorfile>
      <anchor>a9aeda69f4a92d266a5ded075c0099e70</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>Epetra_Vector *</type>
      <name>rhs_</name>
      <anchorfile>classAztecOOConditionNumber.html</anchorfile>
      <anchor>a0ff5eb0999ff16819a8161a8ae5b4309</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>Epetra_Vector *</type>
      <name>dummy_</name>
      <anchorfile>classAztecOOConditionNumber.html</anchorfile>
      <anchor>a8f3b2736c52f6217986ed992c26cc498</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>AztecOO *</type>
      <name>solver_</name>
      <anchorfile>classAztecOOConditionNumber.html</anchorfile>
      <anchor>ae4a17147e4ef963cfacc0f914174688a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>bool</type>
      <name>printSolve_</name>
      <anchorfile>classAztecOOConditionNumber.html</anchorfile>
      <anchor>ac772ebc35e9d643b3c0a00fc6af79f1e</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>blockmat_struct</name>
    <filename>structblockmat__struct.html</filename>
  </compound>
  <compound kind="struct">
    <name>cilist</name>
    <filename>structcilist.html</filename>
  </compound>
  <compound kind="struct">
    <name>cllist</name>
    <filename>structcllist.html</filename>
  </compound>
  <compound kind="struct">
    <name>complex</name>
    <filename>structcomplex.html</filename>
  </compound>
  <compound kind="struct">
    <name>context</name>
    <filename>structcontext.html</filename>
  </compound>
  <compound kind="struct">
    <name>doublecomplex</name>
    <filename>structdoublecomplex.html</filename>
  </compound>
  <compound kind="class">
    <name>Epetra_MsrMatrix</name>
    <filename>classEpetra__MsrMatrix.html</filename>
    <member kind="function">
      <type></type>
      <name>Epetra_MsrMatrix</name>
      <anchorfile>classEpetra__MsrMatrix.html</anchorfile>
      <anchor>a530cfc41591be06061956cf624c6e647</anchor>
      <arglist>(int *proc_config, AZ_MATRIX *Amat)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~Epetra_MsrMatrix</name>
      <anchorfile>classEpetra__MsrMatrix.html</anchorfile>
      <anchor>a686ba442daa7b9550ba86383b3809e0a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ExtractMyRowCopy</name>
      <anchorfile>classEpetra__MsrMatrix.html</anchorfile>
      <anchor>a8318ce3220ded344ec9ad9d650501133</anchor>
      <arglist>(int MyRow, int Length, int &amp;NumEntries, double *Values, int *Indices) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ExtractDiagonalCopy</name>
      <anchorfile>classEpetra__MsrMatrix.html</anchorfile>
      <anchor>a81fefecd4656ef472de8e2f561b97103</anchor>
      <arglist>(Epetra_Vector &amp;Diagonal) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Multiply</name>
      <anchorfile>classEpetra__MsrMatrix.html</anchorfile>
      <anchor>acf3f75560841ea7e717da8854b1924c3</anchor>
      <arglist>(bool TransA, const Epetra_MultiVector &amp;X, Epetra_MultiVector &amp;Y) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Solve</name>
      <anchorfile>classEpetra__MsrMatrix.html</anchorfile>
      <anchor>abaa76ef6a28eb20acb4e97d9e0643280</anchor>
      <arglist>(bool Upper, bool Trans, bool UnitDiagonal, const Epetra_MultiVector &amp;X, Epetra_MultiVector &amp;Y) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>InvRowSums</name>
      <anchorfile>classEpetra__MsrMatrix.html</anchorfile>
      <anchor>af1de588bb773c57537194b94a81d4fdd</anchor>
      <arglist>(Epetra_Vector &amp;x) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>LeftScale</name>
      <anchorfile>classEpetra__MsrMatrix.html</anchorfile>
      <anchor>a3ef13deac62103255f93a82b266dfb09</anchor>
      <arglist>(const Epetra_Vector &amp;x)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>InvColSums</name>
      <anchorfile>classEpetra__MsrMatrix.html</anchorfile>
      <anchor>aa1820f3c97fd8bf814b794ce7be7a5f1</anchor>
      <arglist>(Epetra_Vector &amp;x) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>RightScale</name>
      <anchorfile>classEpetra__MsrMatrix.html</anchorfile>
      <anchor>a0e3daf60a0bacbc3c245bced554bcb31</anchor>
      <arglist>(const Epetra_Vector &amp;x)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>Filled</name>
      <anchorfile>classEpetra__MsrMatrix.html</anchorfile>
      <anchor>ae9f6108b81ed063f39a3da4366d7ba1c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>LowerTriangular</name>
      <anchorfile>classEpetra__MsrMatrix.html</anchorfile>
      <anchor>a565ea6354622de582de873afa3fa0629</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>UpperTriangular</name>
      <anchorfile>classEpetra__MsrMatrix.html</anchorfile>
      <anchor>afe1d44ab2bbc5588f84b5295cafb0593</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>AZ_MATRIX *</type>
      <name>Amat</name>
      <anchorfile>classEpetra__MsrMatrix.html</anchorfile>
      <anchor>add558b0aeac1feeef7cec0ae356302a6</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>NormInf</name>
      <anchorfile>classEpetra__MsrMatrix.html</anchorfile>
      <anchor>a8275237eaf5c1ebb01106a8fd7cb766d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>NormOne</name>
      <anchorfile>classEpetra__MsrMatrix.html</anchorfile>
      <anchor>a9652b28456fd7aa09230e07a60d4a075</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumGlobalNonzeros</name>
      <anchorfile>classEpetra__MsrMatrix.html</anchorfile>
      <anchor>aeb080e823cdf795ca16c9989a8c0d962</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumGlobalRows</name>
      <anchorfile>classEpetra__MsrMatrix.html</anchorfile>
      <anchor>a7e421d0866a3bbe921d7d382fe25d2ef</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumGlobalCols</name>
      <anchorfile>classEpetra__MsrMatrix.html</anchorfile>
      <anchor>a4d2e5bc0875454f2bd52fe9585a7b136</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumGlobalDiagonals</name>
      <anchorfile>classEpetra__MsrMatrix.html</anchorfile>
      <anchor>a34e3549c5301aac0a8a0fbda639019b2</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>long long</type>
      <name>NumGlobalNonzeros64</name>
      <anchorfile>classEpetra__MsrMatrix.html</anchorfile>
      <anchor>ac9bb2ec326d8b1f68952d01815ff904f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>long long</type>
      <name>NumGlobalRows64</name>
      <anchorfile>classEpetra__MsrMatrix.html</anchorfile>
      <anchor>a84c7775f55e07523e95b4ba89208825a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>long long</type>
      <name>NumGlobalCols64</name>
      <anchorfile>classEpetra__MsrMatrix.html</anchorfile>
      <anchor>aff09a2d1deccfc8369e756a9cfcdc2e8</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>long long</type>
      <name>NumGlobalDiagonals64</name>
      <anchorfile>classEpetra__MsrMatrix.html</anchorfile>
      <anchor>a6a9772da6ecfbede9d9b6665c3bb202b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumMyNonzeros</name>
      <anchorfile>classEpetra__MsrMatrix.html</anchorfile>
      <anchor>aec6f973dc3252f82404dc46951d8db3b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumMyRows</name>
      <anchorfile>classEpetra__MsrMatrix.html</anchorfile>
      <anchor>a4d94b6f0897f0b8ad2d497fa40283bd6</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumMyCols</name>
      <anchorfile>classEpetra__MsrMatrix.html</anchorfile>
      <anchor>aaae156cdafb30994ec8431482ad267a0</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumMyDiagonals</name>
      <anchorfile>classEpetra__MsrMatrix.html</anchorfile>
      <anchor>ae8d034052d4c4cfecb915cef8b3ecf92</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_Map &amp;</type>
      <name>OperatorDomainMap</name>
      <anchorfile>classEpetra__MsrMatrix.html</anchorfile>
      <anchor>a551591d3d5d3eff7c6178e73290e449a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_Map &amp;</type>
      <name>OperatorRangeMap</name>
      <anchorfile>classEpetra__MsrMatrix.html</anchorfile>
      <anchor>a5674d54e3e82e2ee87bf6459a7e17144</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_BlockMap &amp;</type>
      <name>Map</name>
      <anchorfile>classEpetra__MsrMatrix.html</anchorfile>
      <anchor>a75e4efc4487a1b55920cacad0591fed8</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_Map &amp;</type>
      <name>RowMatrixRowMap</name>
      <anchorfile>classEpetra__MsrMatrix.html</anchorfile>
      <anchor>a0fa542cc4b16f14d487a332bb5d47845</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_Map &amp;</type>
      <name>RowMatrixColMap</name>
      <anchorfile>classEpetra__MsrMatrix.html</anchorfile>
      <anchor>abef2cc105aa6316b3f2f29e76cd4e054</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const Epetra_Import *</type>
      <name>RowMatrixImporter</name>
      <anchorfile>classEpetra__MsrMatrix.html</anchorfile>
      <anchor>adb04521fc9e0cf8c909dcaf6fdaec485</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_Comm &amp;</type>
      <name>Comm</name>
      <anchorfile>classEpetra__MsrMatrix.html</anchorfile>
      <anchor>af76de187f88b534a270d55b2a75a129b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>Print</name>
      <anchorfile>classEpetra__MsrMatrix.html</anchorfile>
      <anchor>afe8af8468190979eeb81625cfbb2a1c3</anchor>
      <arglist>(std::ostream &amp;os) const </arglist>
    </member>
    <member kind="function">
      <type>const char *</type>
      <name>Label</name>
      <anchorfile>classEpetra__MsrMatrix.html</anchorfile>
      <anchor>a214dfbf5468e2cf861cd342c12440fa5</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetUseTranspose</name>
      <anchorfile>classEpetra__MsrMatrix.html</anchorfile>
      <anchor>a8d748b27c0aadd35bb70e81ba42b218b</anchor>
      <arglist>(bool use_transpose)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Apply</name>
      <anchorfile>classEpetra__MsrMatrix.html</anchorfile>
      <anchor>a8458f671c08b9ca51ee93d05afa65ae1</anchor>
      <arglist>(const Epetra_MultiVector &amp;X, Epetra_MultiVector &amp;Y) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ApplyInverse</name>
      <anchorfile>classEpetra__MsrMatrix.html</anchorfile>
      <anchor>aed296a49d34a62a5e524fcc754925715</anchor>
      <arglist>(const Epetra_MultiVector &amp;X, Epetra_MultiVector &amp;Y) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>HasNormInf</name>
      <anchorfile>classEpetra__MsrMatrix.html</anchorfile>
      <anchor>a8a1f6974be71979cbba6f1dabd9b1263</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>UseTranspose</name>
      <anchorfile>classEpetra__MsrMatrix.html</anchorfile>
      <anchor>a138be0032f8fd04e7eb514d7421ce625</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumMyRowEntries</name>
      <anchorfile>classEpetra__MsrMatrix.html</anchorfile>
      <anchor>aff7e428b10db86577d2c7952f998b031</anchor>
      <arglist>(int MyRow, int &amp;NumEntries) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>MaxNumEntries</name>
      <anchorfile>classEpetra__MsrMatrix.html</anchorfile>
      <anchor>aa0e81636107406aeff9484113aeddab0</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Epetra_MsrMatrix</name>
      <anchorfile>classEpetra__MsrMatrix.html</anchorfile>
      <anchor>a530cfc41591be06061956cf624c6e647</anchor>
      <arglist>(int *proc_config, AZ_MATRIX *Amat)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~Epetra_MsrMatrix</name>
      <anchorfile>classEpetra__MsrMatrix.html</anchorfile>
      <anchor>a686ba442daa7b9550ba86383b3809e0a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ExtractMyRowCopy</name>
      <anchorfile>classEpetra__MsrMatrix.html</anchorfile>
      <anchor>a8318ce3220ded344ec9ad9d650501133</anchor>
      <arglist>(int MyRow, int Length, int &amp;NumEntries, double *Values, int *Indices) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ExtractDiagonalCopy</name>
      <anchorfile>classEpetra__MsrMatrix.html</anchorfile>
      <anchor>a81fefecd4656ef472de8e2f561b97103</anchor>
      <arglist>(Epetra_Vector &amp;Diagonal) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Multiply</name>
      <anchorfile>classEpetra__MsrMatrix.html</anchorfile>
      <anchor>acf3f75560841ea7e717da8854b1924c3</anchor>
      <arglist>(bool TransA, const Epetra_MultiVector &amp;X, Epetra_MultiVector &amp;Y) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Solve</name>
      <anchorfile>classEpetra__MsrMatrix.html</anchorfile>
      <anchor>abaa76ef6a28eb20acb4e97d9e0643280</anchor>
      <arglist>(bool Upper, bool Trans, bool UnitDiagonal, const Epetra_MultiVector &amp;X, Epetra_MultiVector &amp;Y) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>InvRowSums</name>
      <anchorfile>classEpetra__MsrMatrix.html</anchorfile>
      <anchor>af1de588bb773c57537194b94a81d4fdd</anchor>
      <arglist>(Epetra_Vector &amp;x) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>LeftScale</name>
      <anchorfile>classEpetra__MsrMatrix.html</anchorfile>
      <anchor>a3ef13deac62103255f93a82b266dfb09</anchor>
      <arglist>(const Epetra_Vector &amp;x)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>InvColSums</name>
      <anchorfile>classEpetra__MsrMatrix.html</anchorfile>
      <anchor>aa1820f3c97fd8bf814b794ce7be7a5f1</anchor>
      <arglist>(Epetra_Vector &amp;x) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>RightScale</name>
      <anchorfile>classEpetra__MsrMatrix.html</anchorfile>
      <anchor>a0e3daf60a0bacbc3c245bced554bcb31</anchor>
      <arglist>(const Epetra_Vector &amp;x)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>Filled</name>
      <anchorfile>classEpetra__MsrMatrix.html</anchorfile>
      <anchor>ae9f6108b81ed063f39a3da4366d7ba1c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>LowerTriangular</name>
      <anchorfile>classEpetra__MsrMatrix.html</anchorfile>
      <anchor>a565ea6354622de582de873afa3fa0629</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>UpperTriangular</name>
      <anchorfile>classEpetra__MsrMatrix.html</anchorfile>
      <anchor>afe1d44ab2bbc5588f84b5295cafb0593</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>AZ_MATRIX *</type>
      <name>Amat</name>
      <anchorfile>classEpetra__MsrMatrix.html</anchorfile>
      <anchor>add558b0aeac1feeef7cec0ae356302a6</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>NormInf</name>
      <anchorfile>classEpetra__MsrMatrix.html</anchorfile>
      <anchor>a8275237eaf5c1ebb01106a8fd7cb766d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>NormOne</name>
      <anchorfile>classEpetra__MsrMatrix.html</anchorfile>
      <anchor>a9652b28456fd7aa09230e07a60d4a075</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumGlobalNonzeros</name>
      <anchorfile>classEpetra__MsrMatrix.html</anchorfile>
      <anchor>aeb080e823cdf795ca16c9989a8c0d962</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumGlobalRows</name>
      <anchorfile>classEpetra__MsrMatrix.html</anchorfile>
      <anchor>a7e421d0866a3bbe921d7d382fe25d2ef</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumGlobalCols</name>
      <anchorfile>classEpetra__MsrMatrix.html</anchorfile>
      <anchor>a4d2e5bc0875454f2bd52fe9585a7b136</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumGlobalDiagonals</name>
      <anchorfile>classEpetra__MsrMatrix.html</anchorfile>
      <anchor>a34e3549c5301aac0a8a0fbda639019b2</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>long long</type>
      <name>NumGlobalNonzeros64</name>
      <anchorfile>classEpetra__MsrMatrix.html</anchorfile>
      <anchor>ac9bb2ec326d8b1f68952d01815ff904f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>long long</type>
      <name>NumGlobalRows64</name>
      <anchorfile>classEpetra__MsrMatrix.html</anchorfile>
      <anchor>a84c7775f55e07523e95b4ba89208825a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>long long</type>
      <name>NumGlobalCols64</name>
      <anchorfile>classEpetra__MsrMatrix.html</anchorfile>
      <anchor>aff09a2d1deccfc8369e756a9cfcdc2e8</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>long long</type>
      <name>NumGlobalDiagonals64</name>
      <anchorfile>classEpetra__MsrMatrix.html</anchorfile>
      <anchor>a6a9772da6ecfbede9d9b6665c3bb202b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumMyNonzeros</name>
      <anchorfile>classEpetra__MsrMatrix.html</anchorfile>
      <anchor>aec6f973dc3252f82404dc46951d8db3b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumMyRows</name>
      <anchorfile>classEpetra__MsrMatrix.html</anchorfile>
      <anchor>a4d94b6f0897f0b8ad2d497fa40283bd6</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumMyCols</name>
      <anchorfile>classEpetra__MsrMatrix.html</anchorfile>
      <anchor>aaae156cdafb30994ec8431482ad267a0</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumMyDiagonals</name>
      <anchorfile>classEpetra__MsrMatrix.html</anchorfile>
      <anchor>ae8d034052d4c4cfecb915cef8b3ecf92</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_Map &amp;</type>
      <name>OperatorDomainMap</name>
      <anchorfile>classEpetra__MsrMatrix.html</anchorfile>
      <anchor>a551591d3d5d3eff7c6178e73290e449a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_Map &amp;</type>
      <name>OperatorRangeMap</name>
      <anchorfile>classEpetra__MsrMatrix.html</anchorfile>
      <anchor>a5674d54e3e82e2ee87bf6459a7e17144</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_BlockMap &amp;</type>
      <name>Map</name>
      <anchorfile>classEpetra__MsrMatrix.html</anchorfile>
      <anchor>a75e4efc4487a1b55920cacad0591fed8</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_Map &amp;</type>
      <name>RowMatrixRowMap</name>
      <anchorfile>classEpetra__MsrMatrix.html</anchorfile>
      <anchor>a0fa542cc4b16f14d487a332bb5d47845</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_Map &amp;</type>
      <name>RowMatrixColMap</name>
      <anchorfile>classEpetra__MsrMatrix.html</anchorfile>
      <anchor>abef2cc105aa6316b3f2f29e76cd4e054</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const Epetra_Import *</type>
      <name>RowMatrixImporter</name>
      <anchorfile>classEpetra__MsrMatrix.html</anchorfile>
      <anchor>adb04521fc9e0cf8c909dcaf6fdaec485</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_Comm &amp;</type>
      <name>Comm</name>
      <anchorfile>classEpetra__MsrMatrix.html</anchorfile>
      <anchor>af76de187f88b534a270d55b2a75a129b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>Print</name>
      <anchorfile>classEpetra__MsrMatrix.html</anchorfile>
      <anchor>afe8af8468190979eeb81625cfbb2a1c3</anchor>
      <arglist>(std::ostream &amp;os) const </arglist>
    </member>
    <member kind="function">
      <type>const char *</type>
      <name>Label</name>
      <anchorfile>classEpetra__MsrMatrix.html</anchorfile>
      <anchor>a214dfbf5468e2cf861cd342c12440fa5</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetUseTranspose</name>
      <anchorfile>classEpetra__MsrMatrix.html</anchorfile>
      <anchor>a8d748b27c0aadd35bb70e81ba42b218b</anchor>
      <arglist>(bool use_transpose)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Apply</name>
      <anchorfile>classEpetra__MsrMatrix.html</anchorfile>
      <anchor>a8458f671c08b9ca51ee93d05afa65ae1</anchor>
      <arglist>(const Epetra_MultiVector &amp;X, Epetra_MultiVector &amp;Y) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ApplyInverse</name>
      <anchorfile>classEpetra__MsrMatrix.html</anchorfile>
      <anchor>aed296a49d34a62a5e524fcc754925715</anchor>
      <arglist>(const Epetra_MultiVector &amp;X, Epetra_MultiVector &amp;Y) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>HasNormInf</name>
      <anchorfile>classEpetra__MsrMatrix.html</anchorfile>
      <anchor>a8a1f6974be71979cbba6f1dabd9b1263</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>UseTranspose</name>
      <anchorfile>classEpetra__MsrMatrix.html</anchorfile>
      <anchor>a138be0032f8fd04e7eb514d7421ce625</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumMyRowEntries</name>
      <anchorfile>classEpetra__MsrMatrix.html</anchorfile>
      <anchor>aff7e428b10db86577d2c7952f998b031</anchor>
      <arglist>(int MyRow, int &amp;NumEntries) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>MaxNumEntries</name>
      <anchorfile>classEpetra__MsrMatrix.html</anchorfile>
      <anchor>aa0e81636107406aeff9484113aeddab0</anchor>
      <arglist>() const </arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>grid</name>
    <filename>structgrid.html</filename>
  </compound>
  <compound kind="struct">
    <name>grid_level</name>
    <filename>structgrid__level.html</filename>
  </compound>
  <compound kind="struct">
    <name>icilist</name>
    <filename>structicilist.html</filename>
  </compound>
  <compound kind="struct">
    <name>inlist</name>
    <filename>structinlist.html</filename>
  </compound>
  <compound kind="struct">
    <name>AztecOO::MatrixData</name>
    <filename>structAztecOO_1_1MatrixData.html</filename>
  </compound>
  <compound kind="union">
    <name>Multitype</name>
    <filename>unionMultitype.html</filename>
  </compound>
  <compound kind="struct">
    <name>Namelist</name>
    <filename>structNamelist.html</filename>
  </compound>
  <compound kind="struct">
    <name>olist</name>
    <filename>structolist.html</filename>
  </compound>
  <compound kind="struct">
    <name>AztecOO::OperatorData</name>
    <filename>structAztecOO_1_1OperatorData.html</filename>
  </compound>
  <compound kind="struct">
    <name>submat_struct</name>
    <filename>structsubmat__struct.html</filename>
  </compound>
  <compound kind="struct">
    <name>Vardesc</name>
    <filename>structVardesc.html</filename>
  </compound>
  <compound kind="page">
    <name>index</name>
    <title>Trilinos/AztecOO: Object-Oriented Aztec Linear Solver Package.</title>
    <filename>index</filename>
    <docanchor file="index" title="Introduction">aztecoo_intro</docanchor>
    <docanchor file="index" title="Overview of AztecOO.">aztecoo_startup</docanchor>
    <docanchor file="index" title="AztecOO and Matrix Free usage.">aztecoo_matrixfree</docanchor>
    <docanchor file="index" title="Thyra support">aztecoo_thyra</docanchor>
    <docanchor file="index" title="Browse all of AztecOO as a single doxygen collection">AztecOO_browser</docanchor>
  </compound>
</tagfile>
