<?xml version='1.0' encoding='UTF-8' standalone='yes' ?>
<tagfile>
  <compound kind="file">
    <name>ml_amesos_wrap.h</name>
    <path>/Users/sscoll/dist/trilinos/packages/ml/src/Utils/</path>
    <filename>ml__amesos__wrap_8h</filename>
    <member kind="function">
      <type>int</type>
      <name>ML_Amesos_Gen</name>
      <anchorfile>ml__amesos__wrap_8h.html</anchorfile>
      <anchor>ace1da17e267aee098034a107c24d1683</anchor>
      <arglist>(ML *ml, int curr_level, int choice, int MaxProcs, double AddToDiag, Amesos_Handle_Type *Amesos_Handle)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ML_Amesos_Solve</name>
      <anchorfile>ml__amesos__wrap_8h.html</anchorfile>
      <anchor>a78c3df0cb437efe8c7903655815d1110</anchor>
      <arglist>(void *Amesos_Handle, double x[], double rhs[])</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>ML_Amesos_Destroy</name>
      <anchorfile>ml__amesos__wrap_8h.html</anchorfile>
      <anchor>a57b35c060fc213f150b909372f75e288</anchor>
      <arglist>(void *Amesos_Handle)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>ml_anasazi.h</name>
    <path>/Users/sscoll/dist/trilinos/packages/ml/src/Utils/</path>
    <filename>ml__anasazi_8h</filename>
    <namespace>ML_Anasazi</namespace>
    <member kind="function">
      <type>int</type>
      <name>Interface</name>
      <anchorfile>namespaceML__Anasazi.html</anchorfile>
      <anchor>a75ac5be2035e966946cfdca8c790a267</anchor>
      <arglist>(const Epetra_RowMatrix *RowMatrix, Epetra_MultiVector &amp;EigenVectors, double RealEigenvalues[], double ImagEigenvalues[], Teuchos::ParameterList &amp;List, double RealEigenvectors[]=0, double ImagEigenvectors[]=0, int *NumRealEigenvectors=0, int *NumImagEigenvectors=0, ML *ml=0)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetFieldOfValuesBox</name>
      <anchorfile>namespaceML__Anasazi.html</anchorfile>
      <anchor>a8ce97418ea46f9b7c5d46be0b3e3c7df</anchor>
      <arglist>(const Epetra_RowMatrix *RowMatrix, double &amp;MaxReal, double &amp;MaxImag, Teuchos::ParameterList &amp;AnasaziList)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ML_Anasazi_Get_FieldOfValuesBox_Interface</name>
      <anchorfile>ml__anasazi_8h.html</anchorfile>
      <anchor>a15d0a0b01e316fa8d509e96b07280045</anchor>
      <arglist>(ML_Operator *Amat, struct ML_Field_Of_Values *fov)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ML_Anasazi_Get_SpectralNorm_Anasazi</name>
      <anchorfile>ml__anasazi_8h.html</anchorfile>
      <anchor>a55b311e88a1e72925c0cbae6c08426f6</anchor>
      <arglist>(ML_Operator *Amat, ML_Smoother *smoother, int MaxIters, double Tolerance, int IsProblemSymmetric, int UseDiagonalScaling, double *LambdaMax)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>ml_EdgeMatrixFreePreconditioner.h</name>
    <path>/Users/sscoll/dist/trilinos/packages/ml/src/RefMaxwell/</path>
    <filename>ml__EdgeMatrixFreePreconditioner_8h</filename>
    <includes id="ml__MultiLevelPreconditioner_8h" name="ml_MultiLevelPreconditioner.h" local="yes" imported="no">ml_MultiLevelPreconditioner.h</includes>
    <class kind="class">ML_Epetra::EdgeMatrixFreePreconditioner</class>
    <namespace>ML_Epetra</namespace>
  </compound>
  <compound kind="file">
    <name>ml_epetra_utils.h</name>
    <path>/Users/sscoll/dist/trilinos/packages/ml/src/Utils/</path>
    <filename>ml__epetra__utils_8h</filename>
    <namespace>ML_Epetra</namespace>
    <member kind="function">
      <type>int</type>
      <name>ML_Epetra_matvec</name>
      <anchorfile>ml__epetra__utils_8h.html</anchorfile>
      <anchor>a6de70ce338301d6ae28f8857fd3c0cf8</anchor>
      <arglist>(ML_Operator *data, int in, double *p, int out, double *ap)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ML_Epetra_getrow</name>
      <anchorfile>ml__epetra__utils_8h.html</anchorfile>
      <anchor>a89650707c325d59be395edffdb526e6e</anchor>
      <arglist>(ML_Operator *data, int N_requested_rows, int requested_rows[], int allocated_space, int columns[], double values[], int row_lengths[])</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ML_Epetra_comm_wrapper</name>
      <anchorfile>ml__epetra__utils_8h.html</anchorfile>
      <anchor>a30b3b37502da93593be45f3b0470ca93</anchor>
      <arglist>(double vec[], void *data)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>EpetraMatrix2MLMatrix</name>
      <anchorfile>ml__epetra__utils_8h.html</anchorfile>
      <anchor>a861059544ba9c54a94efd26f8a268dc1</anchor>
      <arglist>(ML *ml_handle, int level, Epetra_RowMatrix *Amat)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ML_Operator_WrapEpetraMatrix</name>
      <anchorfile>ml__epetra__utils_8h.html</anchorfile>
      <anchor>a8ed6c6e293f53531a4043762f71c3cb4</anchor>
      <arglist>(Epetra_RowMatrix *A, ML_Operator *Result)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ML_Operator_WrapEpetraCrsMatrix</name>
      <anchorfile>ml__epetra__utils_8h.html</anchorfile>
      <anchor>a42e11380d3049f62ad426d52b18cd6ff</anchor>
      <arglist>(Epetra_CrsMatrix *A, ML_Operator *newMatrix, bool verbose=false)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Epetra_CrsMatrix_Wrap_ML_Operator</name>
      <anchorfile>ml__epetra__utils_8h.html</anchorfile>
      <anchor>a48e04716537eb7075375373fd8cf3697</anchor>
      <arglist>(ML_Operator *A, const Epetra_Comm &amp;Comm, const Epetra_Map &amp;RowMap, Epetra_CrsMatrix **Result, Epetra_DataAccess CV=::View, int base=0)</arglist>
    </member>
    <member kind="function">
      <type>Epetra_CrsMatrix *</type>
      <name>Epetra_MatrixMult</name>
      <anchorfile>ml__epetra__utils_8h.html</anchorfile>
      <anchor>a40405cf0cd895a15d8df723048a7f2cf</anchor>
      <arglist>(Epetra_RowMatrix *B, Epetra_RowMatrix *Bt)</arglist>
    </member>
    <member kind="function">
      <type>Epetra_CrsMatrix *</type>
      <name>Epetra_MatrixAdd</name>
      <anchorfile>ml__epetra__utils_8h.html</anchorfile>
      <anchor>a172fd82559a082f570e936867703d2db</anchor>
      <arglist>(Epetra_RowMatrix *B, Epetra_RowMatrix *Bt, double scalar)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ML_Operator2EpetraCrsMatrix</name>
      <anchorfile>ml__epetra__utils_8h.html</anchorfile>
      <anchor>aa30a25357de4493095c9b3fa7d4eea00</anchor>
      <arglist>(ML_Operator *Ke, Epetra_CrsMatrix *&amp;CrsMatrix, int &amp;MaxNumNonzeros, bool CheckNonzeroRow, double &amp;, int base=0, bool verbose=false)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ML_Epetra_PtAP</name>
      <anchorfile>namespaceML__Epetra.html</anchorfile>
      <anchor>a654449cb61cf14354bc6178bef4b511e</anchor>
      <arglist>(const Epetra_CrsMatrix &amp;A, const Epetra_CrsMatrix &amp;P, Epetra_CrsMatrix *&amp;Result, bool verbose=false)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ML_Epetra_RAP</name>
      <anchorfile>namespaceML__Epetra.html</anchorfile>
      <anchor>a8b67ded5d8822c69c174ca20199200d6</anchor>
      <arglist>(const Epetra_CrsMatrix &amp;A, const Epetra_CrsMatrix &amp;P, const Epetra_CrsMatrix &amp;R, Epetra_CrsMatrix *&amp;Result, bool verbose)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Epetra_PtAP</name>
      <anchorfile>namespaceML__Epetra.html</anchorfile>
      <anchor>a28806e45dd689c5e25ae0550e3cc55fa</anchor>
      <arglist>(const Epetra_CrsMatrix &amp;A, const Epetra_CrsMatrix &amp;P, Epetra_CrsMatrix *&amp;Result, bool keep_zero_rows=false, bool verbose=false)</arglist>
    </member>
    <member kind="function">
      <type>int *</type>
      <name>FindLocalDiricheltRowsFromOnesAndZeros</name>
      <anchorfile>namespaceML__Epetra.html</anchorfile>
      <anchor>a6036c23604aa2ae45754ac943c4bdd17</anchor>
      <arglist>(const Epetra_CrsMatrix &amp;Matrix, int &amp;numBCRows)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Apply_BCsToMatrixColumns</name>
      <anchorfile>namespaceML__Epetra.html</anchorfile>
      <anchor>ac5a14382c90516d405b8cfc91382d4ef</anchor>
      <arglist>(const int *dirichletRows, int numBCRows, const Epetra_CrsMatrix &amp;Matrix)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Apply_BCsToMatrixRows</name>
      <anchorfile>namespaceML__Epetra.html</anchorfile>
      <anchor>aa2017813fef318a1fcbd2477a237ef88</anchor>
      <arglist>(const int *dirichletRows, int numBCRows, const Epetra_CrsMatrix &amp;Matrix)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Apply_BCsToMatrixColumns</name>
      <anchorfile>namespaceML__Epetra.html</anchorfile>
      <anchor>adef8c4cb6e769016fc2358047285f5d2</anchor>
      <arglist>(const Epetra_RowMatrix &amp;iBoundaryMatrix, const Epetra_RowMatrix &amp;iMatrix)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Apply_BCsToGradient</name>
      <anchorfile>namespaceML__Epetra.html</anchorfile>
      <anchor>acacbd0af46df3fb65b3f6a917b0ff5cf</anchor>
      <arglist>(const Epetra_RowMatrix &amp;EdgeMatrix, const Epetra_RowMatrix &amp;T)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Apply_OAZToMatrix</name>
      <anchorfile>namespaceML__Epetra.html</anchorfile>
      <anchor>a62e88102bb26b9e8f3c13359ad852fb1</anchor>
      <arglist>(int *dirichletRows, int numBCRows, const Epetra_CrsMatrix &amp;Matrix)</arglist>
    </member>
    <member kind="function">
      <type>Epetra_IntVector *</type>
      <name>LocalRowstoColumns</name>
      <anchorfile>namespaceML__Epetra.html</anchorfile>
      <anchor>abf48f7683e25146522a6bc1fea4420f7</anchor>
      <arglist>(int *Rows, int numRows, const Epetra_CrsMatrix &amp;Matrix)</arglist>
    </member>
    <member kind="function">
      <type>Epetra_IntVector *</type>
      <name>FindLocalDirichletColumnsFromRows</name>
      <anchorfile>namespaceML__Epetra.html</anchorfile>
      <anchor>a252072c2e6f22063c5f16ee414889b7a</anchor>
      <arglist>(const int *dirichletRows, int numBCRows, const Epetra_CrsMatrix &amp;Matrix)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Remove_Zeroed_Rows</name>
      <anchorfile>namespaceML__Epetra.html</anchorfile>
      <anchor>a843e125059a029d759708ef91f15f1f3</anchor>
      <arglist>(const Epetra_CrsMatrix &amp;Matrix, double tol=0.0)</arglist>
    </member>
    <member kind="function">
      <type>Epetra_RowMatrix *</type>
      <name>ModifyEpetraMatrixColMap</name>
      <anchorfile>namespaceML__Epetra.html</anchorfile>
      <anchor>a24bc7bfd25ff2b787a56cb8d713dbad5</anchor>
      <arglist>(const Epetra_RowMatrix &amp;A, EpetraExt::CrsMatrix_SolverMap &amp;transform, const char *matrixName=0, bool verbose=false)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>ML_BreakForDebugger</name>
      <anchorfile>ml__epetra__utils_8h.html</anchorfile>
      <anchor>a95ce6bb2ede3c08998fd809337aeecfa</anchor>
      <arglist>(const Epetra_Comm &amp;comm)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>ml_Epetra_wrap_CrsGraph_as_RowMatrix.H</name>
    <path>/Users/sscoll/dist/trilinos/packages/ml/src/Utils/</path>
    <filename>ml__Epetra__wrap__CrsGraph__as__RowMatrix_8H</filename>
    <class kind="class">ML_Epetra::CrsGraphWrapper</class>
    <namespace>ML_Epetra</namespace>
  </compound>
  <compound kind="file">
    <name>ml_Ifpack_ML.h</name>
    <path>/Users/sscoll/dist/trilinos/packages/ml/src/Utils/</path>
    <filename>ml__Ifpack__ML_8h</filename>
    <includes id="ml__MultiLevelPreconditioner_8h" name="ml_MultiLevelPreconditioner.h" local="yes" imported="no">ml_MultiLevelPreconditioner.h</includes>
    <class kind="class">ML_Epetra::Ifpack_ML</class>
    <namespace>ML_Epetra</namespace>
  </compound>
  <compound kind="file">
    <name>ml_ifpack_wrap.h</name>
    <path>/Users/sscoll/dist/trilinos/packages/ml/src/Utils/</path>
    <filename>ml__ifpack__wrap_8h</filename>
    <member kind="function">
      <type>int</type>
      <name>ML_Smoother_Ifpack</name>
      <anchorfile>ml__ifpack__wrap_8h.html</anchorfile>
      <anchor>ac056a5093fc23952c0795354f423c53f</anchor>
      <arglist>(ML_Smoother *sm, int inlen, double x[], int outlen, double rhs[])</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>ML_Smoother_Clean_Ifpack</name>
      <anchorfile>ml__ifpack__wrap_8h.html</anchorfile>
      <anchor>a979379f25109070a75d63815f4b5ce26</anchor>
      <arglist>(void *Ifpack_Handle)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ML_Gen_Smoother_Ifpack</name>
      <anchorfile>ml__ifpack__wrap_8h.html</anchorfile>
      <anchor>a870abc97dba65159c90e491a74025cec</anchor>
      <arglist>(ML *ml, const char *Type, int Overlap, int nl, int pre_or_post, void *List, void *Comm)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>ml_MatrixFreePreconditioner.h</name>
    <path>/Users/sscoll/dist/trilinos/packages/ml/src/MatrixFree/</path>
    <filename>ml__MatrixFreePreconditioner_8h</filename>
    <includes id="ml__MultiLevelPreconditioner_8h" name="ml_MultiLevelPreconditioner.h" local="yes" imported="no">ml_MultiLevelPreconditioner.h</includes>
    <class kind="class">ML_Epetra::MatrixFreePreconditioner</class>
    <namespace>ML_Epetra</namespace>
  </compound>
  <compound kind="file">
    <name>ml_MultiLevelOperator.h</name>
    <path>/Users/sscoll/dist/trilinos/packages/ml/src/Utils/</path>
    <filename>ml__MultiLevelOperator_8h</filename>
    <class kind="class">ML_Epetra::MultiLevelOperator</class>
    <namespace>ML_Epetra</namespace>
  </compound>
  <compound kind="file">
    <name>ml_MultiLevelPreconditioner.cpp</name>
    <path>/Users/sscoll/dist/trilinos/packages/ml/src/Utils/</path>
    <filename>ml__MultiLevelPreconditioner_8cpp</filename>
    <includes id="ml__RowMatrix_8h" name="ml_RowMatrix.h" local="yes" imported="no">ml_RowMatrix.h</includes>
    <includes id="ml__amesos__wrap_8h" name="ml_amesos_wrap.h" local="yes" imported="no">ml_amesos_wrap.h</includes>
    <includes id="ml__epetra__utils_8h" name="ml_epetra_utils.h" local="yes" imported="no">ml_epetra_utils.h</includes>
    <includes id="ml__MultiLevelPreconditioner_8h" name="ml_MultiLevelPreconditioner.h" local="yes" imported="no">ml_MultiLevelPreconditioner.h</includes>
    <includes id="ml__anasazi_8h" name="ml_anasazi.h" local="yes" imported="no">ml_anasazi.h</includes>
    <includes id="ml__ifpack__wrap_8h" name="ml_ifpack_wrap.h" local="yes" imported="no">ml_ifpack_wrap.h</includes>
    <member kind="function">
      <type>int</type>
      <name>MLShove</name>
      <anchorfile>ml__MultiLevelPreconditioner_8cpp.html</anchorfile>
      <anchor>a836762a510f8cb162ba774058eb0d6aa</anchor>
      <arglist>(ML_Operator *Mat, MLVec&lt; int &gt; &amp;rowPtr, MLVec&lt; int &gt; &amp;cols, MLVec&lt; double &gt; &amp;vals, int invec_leng, int(*commfunc)(double *vec, void *data), struct wrappedCommStruct &amp;framework, int nGhost)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>MLunamalgP</name>
      <anchorfile>ml__MultiLevelPreconditioner_8cpp.html</anchorfile>
      <anchor>a8781fec714f89054aabeb624af67b3ff</anchor>
      <arglist>(const MLVec&lt; int &gt; &amp;amalgRowPtr, const MLVec&lt; int &gt; &amp;amalgCols, const MLVec&lt; double &gt; &amp;amalgVals, int maxDofPerNode, const MLVec&lt; char &gt; &amp;status, bool fineIsPadded, MLVec&lt; int &gt; &amp;rowPtr, MLVec&lt; int &gt; &amp;cols, MLVec&lt; double &gt; &amp;vals)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>ml_MultiLevelPreconditioner.h</name>
    <path>/Users/sscoll/dist/trilinos/packages/ml/src/Utils/</path>
    <filename>ml__MultiLevelPreconditioner_8h</filename>
    <includes id="ml__epetra__utils_8h" name="ml_epetra_utils.h" local="yes" imported="no">ml_epetra_utils.h</includes>
    <class kind="class">ML_Epetra::MultiLevelPreconditioner</class>
    <class kind="class">MLVec</class>
    <class kind="struct">wrappedCommStruct</class>
    <namespace>ML_Epetra</namespace>
    <member kind="enumeration">
      <type></type>
      <name>AMGType</name>
      <anchorfile>namespaceML__Epetra.html</anchorfile>
      <anchor>acdeabed2c09f4fa9cbfa2d330cbf3f2f</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetDefaults</name>
      <anchorfile>namespaceML__Epetra.html</anchorfile>
      <anchor>a56d4ce3baee9b349ed2333326e0ec2b6</anchor>
      <arglist>(std::string ProblemType, Teuchos::ParameterList &amp;List, int *options=0, double *params=0, const bool OverWrite=true)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetDefaultsDD</name>
      <anchorfile>namespaceML__Epetra.html</anchorfile>
      <anchor>afe8ac10c161ff035bfff3c7d933a682e</anchor>
      <arglist>(Teuchos::ParameterList &amp;List, Teuchos::RCP&lt; std::vector&lt; int &gt; &gt; &amp;options, Teuchos::RCP&lt; std::vector&lt; double &gt; &gt; &amp;params, bool Overwrite=true)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetDefaultsDD_LU</name>
      <anchorfile>namespaceML__Epetra.html</anchorfile>
      <anchor>a74f35b250c87034cd245d02a49853a46</anchor>
      <arglist>(Teuchos::ParameterList &amp;List, Teuchos::RCP&lt; std::vector&lt; int &gt; &gt; &amp;options, Teuchos::RCP&lt; std::vector&lt; double &gt; &gt; &amp;params, bool Overwrite=true)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetDefaultsDD_3Levels</name>
      <anchorfile>namespaceML__Epetra.html</anchorfile>
      <anchor>a1a7035c7ccc295e3b15d47a82150c504</anchor>
      <arglist>(Teuchos::ParameterList &amp;List, Teuchos::RCP&lt; std::vector&lt; int &gt; &gt; &amp;options, Teuchos::RCP&lt; std::vector&lt; double &gt; &gt; &amp;params, bool Overwrite=true)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetDefaultsDD_3Levels_LU</name>
      <anchorfile>namespaceML__Epetra.html</anchorfile>
      <anchor>a6eee28e412ed3ab46e7fed2e0ec63871</anchor>
      <arglist>(Teuchos::ParameterList &amp;List, Teuchos::RCP&lt; std::vector&lt; int &gt; &gt; &amp;options, Teuchos::RCP&lt; std::vector&lt; double &gt; &gt; &amp;params, bool Overwrite=true)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetDefaultsMaxwell</name>
      <anchorfile>namespaceML__Epetra.html</anchorfile>
      <anchor>a0707be28e45423af9662d399a21f8bd1</anchor>
      <arglist>(Teuchos::ParameterList &amp;List, Teuchos::RCP&lt; std::vector&lt; int &gt; &gt; &amp;options, Teuchos::RCP&lt; std::vector&lt; double &gt; &gt; &amp;params, bool Overwrite=true)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetDefaultsSA</name>
      <anchorfile>namespaceML__Epetra.html</anchorfile>
      <anchor>a46fd78bf3b6979a5bec018c93b4c23b4</anchor>
      <arglist>(Teuchos::ParameterList &amp;List, Teuchos::RCP&lt; std::vector&lt; int &gt; &gt; &amp;options, Teuchos::RCP&lt; std::vector&lt; double &gt; &gt; &amp;params, bool Overwrite=true)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetDefaultsNSSA</name>
      <anchorfile>namespaceML__Epetra.html</anchorfile>
      <anchor>a8371873a53298fee7d9bf8fd836b8091</anchor>
      <arglist>(Teuchos::ParameterList &amp;List, Teuchos::RCP&lt; std::vector&lt; int &gt; &gt; &amp;options, Teuchos::RCP&lt; std::vector&lt; double &gt; &gt; &amp;params, bool Overwrite=true)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ReadXML</name>
      <anchorfile>namespaceML__Epetra.html</anchorfile>
      <anchor>aa15a238c96fdcafd8f5625a49ed53d03</anchor>
      <arglist>(const std::string &amp;FileName, Teuchos::ParameterList &amp;List, const Epetra_Comm &amp;Comm)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>MLunamalgP</name>
      <anchorfile>ml__MultiLevelPreconditioner_8h.html</anchorfile>
      <anchor>a8781fec714f89054aabeb624af67b3ff</anchor>
      <arglist>(const MLVec&lt; int &gt; &amp;amalgRowPtr, const MLVec&lt; int &gt; &amp;amalgCols, const MLVec&lt; double &gt; &amp;amalgVals, int maxDofPerNode, const MLVec&lt; char &gt; &amp;status, bool fineIsPadded, MLVec&lt; int &gt; &amp;rowPtr, MLVec&lt; int &gt; &amp;cols, MLVec&lt; double &gt; &amp;vals)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>MLShove</name>
      <anchorfile>ml__MultiLevelPreconditioner_8h.html</anchorfile>
      <anchor>a836762a510f8cb162ba774058eb0d6aa</anchor>
      <arglist>(ML_Operator *Mat, MLVec&lt; int &gt; &amp;rowPtr, MLVec&lt; int &gt; &amp;cols, MLVec&lt; double &gt; &amp;vals, int invec_leng, int(*commfunc)(double *vec, void *data), struct wrappedCommStruct &amp;framework, int nGhost)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>ml_MultiLevelPreconditioner_Adapt.cpp</name>
    <path>/Users/sscoll/dist/trilinos/packages/ml/src/Utils/</path>
    <filename>ml__MultiLevelPreconditioner__Adapt_8cpp</filename>
    <includes id="ml__MultiLevelPreconditioner_8h" name="ml_MultiLevelPreconditioner.h" local="yes" imported="no">ml_MultiLevelPreconditioner.h</includes>
  </compound>
  <compound kind="file">
    <name>ml_MultiLevelPreconditioner_Analyze.cpp</name>
    <path>/Users/sscoll/dist/trilinos/packages/ml/src/Utils/</path>
    <filename>ml__MultiLevelPreconditioner__Analyze_8cpp</filename>
    <includes id="ml__RowMatrix_8h" name="ml_RowMatrix.h" local="yes" imported="no">ml_RowMatrix.h</includes>
    <includes id="ml__MultiLevelPreconditioner_8h" name="ml_MultiLevelPreconditioner.h" local="yes" imported="no">ml_MultiLevelPreconditioner.h</includes>
  </compound>
  <compound kind="file">
    <name>ml_MultiLevelPreconditioner_Defaults.cpp</name>
    <path>/Users/sscoll/dist/trilinos/packages/ml/src/Utils/</path>
    <filename>ml__MultiLevelPreconditioner__Defaults_8cpp</filename>
    <includes id="ml__MultiLevelPreconditioner_8h" name="ml_MultiLevelPreconditioner.h" local="yes" imported="no">ml_MultiLevelPreconditioner.h</includes>
  </compound>
  <compound kind="file">
    <name>ml_MultiLevelPreconditioner_Smoothers.cpp</name>
    <path>/Users/sscoll/dist/trilinos/packages/ml/src/Utils/</path>
    <filename>ml__MultiLevelPreconditioner__Smoothers_8cpp</filename>
    <includes id="ml__ifpack__wrap_8h" name="ml_ifpack_wrap.h" local="yes" imported="no">ml_ifpack_wrap.h</includes>
    <includes id="ml__epetra__utils_8h" name="ml_epetra_utils.h" local="yes" imported="no">ml_epetra_utils.h</includes>
    <includes id="ml__MultiLevelPreconditioner_8h" name="ml_MultiLevelPreconditioner.h" local="yes" imported="no">ml_MultiLevelPreconditioner.h</includes>
  </compound>
  <compound kind="file">
    <name>ml_MultiLevelPreconditioner_Viz.cpp</name>
    <path>/Users/sscoll/dist/trilinos/packages/ml/src/Utils/</path>
    <filename>ml__MultiLevelPreconditioner__Viz_8cpp</filename>
    <includes id="ml__MultiLevelPreconditioner_8h" name="ml_MultiLevelPreconditioner.h" local="yes" imported="no">ml_MultiLevelPreconditioner.h</includes>
  </compound>
  <compound kind="file">
    <name>ml_MultiLevelPreconditioner_XML.cpp</name>
    <path>/Users/sscoll/dist/trilinos/packages/ml/src/Utils/</path>
    <filename>ml__MultiLevelPreconditioner__XML_8cpp</filename>
    <includes id="ml__MultiLevelPreconditioner_8h" name="ml_MultiLevelPreconditioner.h" local="yes" imported="no">ml_MultiLevelPreconditioner.h</includes>
  </compound>
  <compound kind="file">
    <name>ml_RefMaxwell.h</name>
    <path>/Users/sscoll/dist/trilinos/packages/ml/src/RefMaxwell/</path>
    <filename>ml__RefMaxwell_8h</filename>
    <includes id="ml__RefMaxwell__11__Operator_8h" name="ml_RefMaxwell_11_Operator.h" local="yes" imported="no">ml_RefMaxwell_11_Operator.h</includes>
    <includes id="ml__MultiLevelPreconditioner_8h" name="ml_MultiLevelPreconditioner.h" local="yes" imported="no">ml_MultiLevelPreconditioner.h</includes>
    <class kind="class">ML_Epetra::ML_RMP</class>
    <namespace>ML_Epetra</namespace>
    <member kind="function">
      <type>int</type>
      <name>SetDefaultsRefMaxwell</name>
      <anchorfile>namespaceML__Epetra.html</anchorfile>
      <anchor>a2bed35bc292c07d1126004bbe7cd44fa</anchor>
      <arglist>(Teuchos::ParameterList &amp;inList, bool OverWrite=true)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>ml_RefMaxwell_11_Operator.h</name>
    <path>/Users/sscoll/dist/trilinos/packages/ml/src/RefMaxwell/</path>
    <filename>ml__RefMaxwell__11__Operator_8h</filename>
    <class kind="class">ML_Epetra::ML_RefMaxwell_11_Operator</class>
    <namespace>ML_Epetra</namespace>
  </compound>
  <compound kind="file">
    <name>ml_RowMatrix.h</name>
    <path>/Users/sscoll/dist/trilinos/packages/ml/src/Utils/</path>
    <filename>ml__RowMatrix_8h</filename>
    <class kind="class">ML_Epetra::RowMatrix</class>
    <namespace>ML_Epetra</namespace>
  </compound>
  <compound kind="file">
    <name>MLAPI_Aggregation.h</name>
    <path>/Users/sscoll/dist/trilinos/packages/ml/src/MLAPI/</path>
    <filename>MLAPI__Aggregation_8h</filename>
    <namespace>MLAPI</namespace>
    <member kind="function">
      <type>void</type>
      <name>GetPtent</name>
      <anchorfile>namespaceMLAPI.html</anchorfile>
      <anchor>a6609804c6d86c4708b7168cab10fe4ef</anchor>
      <arglist>(const Operator &amp;A, Teuchos::ParameterList &amp;List, const MultiVector &amp;ThisNS, Operator &amp;Ptent, MultiVector &amp;NextNS)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>GetPtent</name>
      <anchorfile>namespaceMLAPI.html</anchorfile>
      <anchor>a02dd2723ac5649b278cbe387b4184ad7</anchor>
      <arglist>(const Operator &amp;A, Teuchos::ParameterList &amp;List, Operator &amp;Ptent)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>GetPtent</name>
      <anchorfile>namespaceMLAPI.html</anchorfile>
      <anchor>a5ba8fd04b219e87086364582f6223418</anchor>
      <arglist>(const Epetra_RowMatrix &amp;A, Teuchos::ParameterList &amp;List, double *thisns, Teuchos::RCP&lt; Epetra_CrsMatrix &gt; &amp;Ptent, Teuchos::RCP&lt; Epetra_MultiVector &gt; &amp;NextNS, const int domainoffset=0)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>GetPtent</name>
      <anchorfile>namespaceMLAPI.html</anchorfile>
      <anchor>a3dabf6c0b2d4e9b5e09bc47c5867eb93</anchor>
      <arglist>(const Epetra_RowMatrix &amp;A, Teuchos::ParameterList &amp;List, double *thisns, Teuchos::RCP&lt; Epetra_CrsMatrix &gt; &amp;Ptent, const int domainoffset=0)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetAggregates</name>
      <anchorfile>namespaceMLAPI.html</anchorfile>
      <anchor>ac910b47c4ef0b9e28acf9cfe719ab3ae</anchor>
      <arglist>(Epetra_RowMatrix &amp;A, Teuchos::ParameterList &amp;List, double *thisns, Epetra_IntVector &amp;aggrinfo)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetGlobalAggregates</name>
      <anchorfile>namespaceMLAPI.html</anchorfile>
      <anchor>a0a75b74ee4a063a3ee5b6750a9afc0de</anchor>
      <arglist>(Epetra_RowMatrix &amp;A, Teuchos::ParameterList &amp;List, double *thisns, Epetra_IntVector &amp;aggrinfo)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>MLAPI_BaseLinearCombination.h</name>
    <path>/Users/sscoll/dist/trilinos/packages/ml/src/MLAPI/</path>
    <filename>MLAPI__BaseLinearCombination_8h</filename>
    <class kind="class">MLAPI::BaseLinearCombination</class>
    <namespace>MLAPI</namespace>
  </compound>
  <compound kind="file">
    <name>MLAPI_BaseObject.h</name>
    <path>/Users/sscoll/dist/trilinos/packages/ml/src/MLAPI/</path>
    <filename>MLAPI__BaseObject_8h</filename>
    <includes id="MLAPI__Workspace_8h" name="MLAPI_Workspace.h" local="yes" imported="no">MLAPI_Workspace.h</includes>
    <class kind="class">MLAPI::BaseObject</class>
    <namespace>MLAPI</namespace>
  </compound>
  <compound kind="file">
    <name>MLAPI_BaseOperator.h</name>
    <path>/Users/sscoll/dist/trilinos/packages/ml/src/MLAPI/</path>
    <filename>MLAPI__BaseOperator_8h</filename>
    <includes id="MLAPI__BaseObject_8h" name="MLAPI_BaseObject.h" local="yes" imported="no">MLAPI_BaseObject.h</includes>
    <class kind="class">MLAPI::BaseOperator</class>
    <namespace>MLAPI</namespace>
  </compound>
  <compound kind="file">
    <name>MLAPI_CompObject.h</name>
    <path>/Users/sscoll/dist/trilinos/packages/ml/src/MLAPI/</path>
    <filename>MLAPI__CompObject_8h</filename>
    <class kind="class">MLAPI::CompObject</class>
    <namespace>MLAPI</namespace>
  </compound>
  <compound kind="file">
    <name>MLAPI_Defaults.h</name>
    <path>/Users/sscoll/dist/trilinos/packages/ml/src/MLAPI/</path>
    <filename>MLAPI__Defaults_8h</filename>
    <namespace>MLAPI</namespace>
    <member kind="function">
      <type>void</type>
      <name>SetDefaults</name>
      <anchorfile>namespaceMLAPI.html</anchorfile>
      <anchor>a7b88442031e5a937bfd320862c864cb4</anchor>
      <arglist>(Teuchos::ParameterList &amp;List)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>MLAPI_DistributedMatrix.h</name>
    <path>/Users/sscoll/dist/trilinos/packages/ml/src/MLAPI/</path>
    <filename>MLAPI__DistributedMatrix_8h</filename>
    <includes id="MLAPI__Operator_8h" name="MLAPI_Operator.h" local="yes" imported="no">MLAPI_Operator.h</includes>
    <includes id="MLAPI__Space_8h" name="MLAPI_Space.h" local="yes" imported="no">MLAPI_Space.h</includes>
    <includes id="MLAPI__BaseLinearCombination_8h" name="MLAPI_BaseLinearCombination.h" local="yes" imported="no">MLAPI_BaseLinearCombination.h</includes>
    <class kind="class">MLAPI::DistributedMatrix</class>
    <namespace>MLAPI</namespace>
  </compound>
  <compound kind="file">
    <name>MLAPI_Eig.h</name>
    <path>/Users/sscoll/dist/trilinos/packages/ml/src/MLAPI/</path>
    <filename>MLAPI__Eig_8h</filename>
    <namespace>MLAPI</namespace>
    <member kind="function">
      <type>double</type>
      <name>MaxEigAnorm</name>
      <anchorfile>namespaceMLAPI.html</anchorfile>
      <anchor>a5bed05896791e61e29644bb78471c5be</anchor>
      <arglist>(const Operator &amp;Op, const bool DiagonalScaling=false)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>MaxEigCG</name>
      <anchorfile>namespaceMLAPI.html</anchorfile>
      <anchor>aadba5c6ee7b4ee7da2dc7680419018c8</anchor>
      <arglist>(const Operator &amp;Op, const bool DiagonalScaling=false)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>MaxEigPowerMethod</name>
      <anchorfile>namespaceMLAPI.html</anchorfile>
      <anchor>a13e4478ac0f2ffe04ac6420af3c4f2d3</anchor>
      <arglist>(const Operator &amp;Op, const bool DiagonalScaling=false)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>MaxEigAnasazi</name>
      <anchorfile>namespaceMLAPI.html</anchorfile>
      <anchor>a5aab66a75fddbfc405c86285c67f7aa9</anchor>
      <arglist>(const Operator &amp;Op, const bool DiagonalScaling=false)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Eig</name>
      <anchorfile>namespaceMLAPI.html</anchorfile>
      <anchor>a48592896b1ef49d15a8d02ba79dd3558</anchor>
      <arglist>(const Operator &amp;Op, MultiVector &amp;ER, MultiVector &amp;EI)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>MLAPI_EpetraBaseOperator.h</name>
    <path>/Users/sscoll/dist/trilinos/packages/ml/src/MLAPI/</path>
    <filename>MLAPI__EpetraBaseOperator_8h</filename>
    <includes id="MLAPI__BaseOperator_8h" name="MLAPI_BaseOperator.h" local="yes" imported="no">MLAPI_BaseOperator.h</includes>
    <includes id="MLAPI__Workspace_8h" name="MLAPI_Workspace.h" local="yes" imported="no">MLAPI_Workspace.h</includes>
    <class kind="class">MLAPI::EpetraBaseOperator</class>
    <namespace>MLAPI</namespace>
  </compound>
  <compound kind="file">
    <name>MLAPI_Expressions.h</name>
    <path>/Users/sscoll/dist/trilinos/packages/ml/src/MLAPI/</path>
    <filename>MLAPI__Expressions_8h</filename>
    <namespace>MLAPI</namespace>
    <member kind="function">
      <type>MultiVectorCombination</type>
      <name>operator+</name>
      <anchorfile>namespaceMLAPI.html</anchorfile>
      <anchor>a2b49b3900112df29828ebd137c881af7</anchor>
      <arglist>(const MultiVector &amp;x, const MultiVector &amp;y)</arglist>
    </member>
    <member kind="function">
      <type>MultiVectorCombination</type>
      <name>operator+</name>
      <anchorfile>namespaceMLAPI.html</anchorfile>
      <anchor>a67aae181510b908a4bc7241f201a09fd</anchor>
      <arglist>(const MultiVectorScaled &amp;left, const MultiVectorScaled &amp;right)</arglist>
    </member>
    <member kind="function">
      <type>Residual</type>
      <name>operator+</name>
      <anchorfile>namespaceMLAPI.html</anchorfile>
      <anchor>a417990acd4e8ed720ff15934ea3e0758</anchor>
      <arglist>(const MultiVectorScaled &amp;left, const BaseOperatorTimesMultiVector &amp;right)</arglist>
    </member>
    <member kind="function">
      <type>Residual</type>
      <name>operator+</name>
      <anchorfile>namespaceMLAPI.html</anchorfile>
      <anchor>a68626732ec8f15b925621e959ba0aedf</anchor>
      <arglist>(const MultiVector &amp;left, const BaseOperatorTimesMultiVector &amp;right)</arglist>
    </member>
    <member kind="function">
      <type>MultiVectorCombination</type>
      <name>operator-</name>
      <anchorfile>namespaceMLAPI.html</anchorfile>
      <anchor>a35b11ca410893124559bfd5f25165fa5</anchor>
      <arglist>(const MultiVector &amp;x, const MultiVector &amp;y)</arglist>
    </member>
    <member kind="function">
      <type>Residual</type>
      <name>operator-</name>
      <anchorfile>namespaceMLAPI.html</anchorfile>
      <anchor>a1d875f7b716eccdd6c8deac17999e4a2</anchor>
      <arglist>(const MultiVector &amp;left, const BaseOperatorTimesMultiVector &amp;right)</arglist>
    </member>
    <member kind="function">
      <type>MultiVector</type>
      <name>operator+</name>
      <anchorfile>namespaceMLAPI.html</anchorfile>
      <anchor>aa4bfbe16791ed9055976bac8642566f2</anchor>
      <arglist>(const MultiVector &amp;x, const double alpha)</arglist>
    </member>
    <member kind="function">
      <type>MultiVector</type>
      <name>operator+</name>
      <anchorfile>namespaceMLAPI.html</anchorfile>
      <anchor>a1a6ba2efe14bfccc918b6a2c9e34a173</anchor>
      <arglist>(const double alpha, const MultiVector &amp;x)</arglist>
    </member>
    <member kind="function">
      <type>MultiVector</type>
      <name>operator-</name>
      <anchorfile>namespaceMLAPI.html</anchorfile>
      <anchor>a1ab03f15a180c0a21125e67a603ce08a</anchor>
      <arglist>(const MultiVector &amp;x, const double alpha)</arglist>
    </member>
    <member kind="function">
      <type>MultiVector</type>
      <name>operator-</name>
      <anchorfile>namespaceMLAPI.html</anchorfile>
      <anchor>abad75ca3f02a5ae2bb3132e4150af9e6</anchor>
      <arglist>(const double alpha, const MultiVector &amp;x)</arglist>
    </member>
    <member kind="function">
      <type>Operator</type>
      <name>operator+</name>
      <anchorfile>namespaceMLAPI.html</anchorfile>
      <anchor>a379d76a03dad3df4838009340553df6c</anchor>
      <arglist>(const Operator &amp;A, const Operator &amp;B)</arglist>
    </member>
    <member kind="function">
      <type>Operator</type>
      <name>operator-</name>
      <anchorfile>namespaceMLAPI.html</anchorfile>
      <anchor>a3304c61897312556c1a8145a60f318c2</anchor>
      <arglist>(const Operator &amp;A, const Operator &amp;B)</arglist>
    </member>
    <member kind="function">
      <type>Operator</type>
      <name>operator*</name>
      <anchorfile>namespaceMLAPI.html</anchorfile>
      <anchor>abf7cb7e6d04eb612d3e13b93fa962723</anchor>
      <arglist>(const Operator &amp;A, const Operator &amp;B)</arglist>
    </member>
    <member kind="function">
      <type>Operator</type>
      <name>operator*</name>
      <anchorfile>namespaceMLAPI.html</anchorfile>
      <anchor>a78a3aeda702aaa0d5b4a71943127c58a</anchor>
      <arglist>(const Operator &amp;A, const double alpha)</arglist>
    </member>
    <member kind="function">
      <type>Operator</type>
      <name>operator*</name>
      <anchorfile>namespaceMLAPI.html</anchorfile>
      <anchor>a418ca6404aea1e6afcbbcad65754be19</anchor>
      <arglist>(const double alpha, const Operator &amp;A)</arglist>
    </member>
    <member kind="function">
      <type>Operator</type>
      <name>operator/</name>
      <anchorfile>namespaceMLAPI.html</anchorfile>
      <anchor>a4cb916db6b6d6f7082645d066b8f37ca</anchor>
      <arglist>(const Operator &amp;A, const double alpha)</arglist>
    </member>
    <member kind="function">
      <type>MultiVector</type>
      <name>operator*</name>
      <anchorfile>namespaceMLAPI.html</anchorfile>
      <anchor>a50c893b9be5041a6d4403d7c975501ff</anchor>
      <arglist>(const MultiVector &amp;x, const double alpha)</arglist>
    </member>
    <member kind="function">
      <type>MultiVector</type>
      <name>operator/</name>
      <anchorfile>namespaceMLAPI.html</anchorfile>
      <anchor>ae1ab8c560702377b5289b12edd20a2d1</anchor>
      <arglist>(const MultiVector &amp;x, const double alpha)</arglist>
    </member>
    <member kind="function">
      <type>BaseOperatorTimesMultiVector</type>
      <name>operator*</name>
      <anchorfile>namespaceMLAPI.html</anchorfile>
      <anchor>ab9308df6a665fbb2f9c85fd0a3229b6a</anchor>
      <arglist>(const BaseOperator &amp;A, const MultiVector &amp;x)</arglist>
    </member>
    <member kind="function">
      <type>BaseOperatorTimesMultiVector</type>
      <name>operator*</name>
      <anchorfile>namespaceMLAPI.html</anchorfile>
      <anchor>acc84e359c2ad5a9617d1380f75f5b297</anchor>
      <arglist>(const BaseOperator &amp;A, const BaseLinearCombination &amp;x)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>operator*</name>
      <anchorfile>namespaceMLAPI.html</anchorfile>
      <anchor>a9030720a1ebfc6ed9bfb5c8a21c6ab60</anchor>
      <arglist>(const MultiVector &amp;x, const MultiVector &amp;y)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>MLAPI_Gallery.h</name>
    <path>/Users/sscoll/dist/trilinos/packages/ml/src/MLAPI/</path>
    <filename>MLAPI__Gallery_8h</filename>
    <namespace>MLAPI</namespace>
    <member kind="function">
      <type>Operator</type>
      <name>Gallery</name>
      <anchorfile>namespaceMLAPI.html</anchorfile>
      <anchor>a71b4b0c3cc1abedfd6f791a00fa54c79</anchor>
      <arglist>(const std::string ProblemType, const Space &amp;MySpace)</arglist>
    </member>
    <member kind="function">
      <type>Operator</type>
      <name>GetShiftedLaplacian1D</name>
      <anchorfile>namespaceMLAPI.html</anchorfile>
      <anchor>a83c05734bb635e59c4387312d9cca9c7</anchor>
      <arglist>(const int NX, const double Factor=0.99)</arglist>
    </member>
    <member kind="function">
      <type>Operator</type>
      <name>GetShiftedLaplacian2D</name>
      <anchorfile>namespaceMLAPI.html</anchorfile>
      <anchor>a2b571c35b05b1ace0e9b79c9ff512172</anchor>
      <arglist>(const int NX, const int NY, const double Factor=0.99, const bool RandomScale=false)</arglist>
    </member>
    <member kind="function">
      <type>Operator</type>
      <name>ReadMatrix</name>
      <anchorfile>namespaceMLAPI.html</anchorfile>
      <anchor>a8cf394f66d009eef0ba2053334ec1418</anchor>
      <arglist>(const char *FileName)</arglist>
    </member>
    <member kind="function">
      <type>Operator</type>
      <name>GetRecirc2D</name>
      <anchorfile>namespaceMLAPI.html</anchorfile>
      <anchor>a242622ff52124e5d30c7f037663481ef</anchor>
      <arglist>(const int NX, const int NY, const double conv, const double diff)</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::ParameterList</type>
      <name>ReadParameterList</name>
      <anchorfile>namespaceMLAPI.html</anchorfile>
      <anchor>af187f70b1eb20c19fb1c7d3ab0ca4d87</anchor>
      <arglist>(const char *FileName)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>MLAPI_InverseOperator.h</name>
    <path>/Users/sscoll/dist/trilinos/packages/ml/src/MLAPI/</path>
    <filename>MLAPI__InverseOperator_8h</filename>
    <includes id="ml__MultiLevelPreconditioner_8h" name="ml_MultiLevelPreconditioner.h" local="yes" imported="no">ml_MultiLevelPreconditioner.h</includes>
    <includes id="MLAPI__BaseOperator_8h" name="MLAPI_BaseOperator.h" local="yes" imported="no">MLAPI_BaseOperator.h</includes>
    <includes id="MLAPI__CompObject_8h" name="MLAPI_CompObject.h" local="yes" imported="no">MLAPI_CompObject.h</includes>
    <includes id="MLAPI__Operator_8h" name="MLAPI_Operator.h" local="yes" imported="no">MLAPI_Operator.h</includes>
    <class kind="class">MLAPI::InverseOperator</class>
    <namespace>MLAPI</namespace>
  </compound>
  <compound kind="file">
    <name>MLAPI_Krylov.h</name>
    <path>/Users/sscoll/dist/trilinos/packages/ml/src/MLAPI/</path>
    <filename>MLAPI__Krylov_8h</filename>
    <namespace>MLAPI</namespace>
  </compound>
  <compound kind="file">
    <name>MLAPI_LoadBalanceInverseOperator.h</name>
    <path>/Users/sscoll/dist/trilinos/packages/ml/src/MLAPI/</path>
    <filename>MLAPI__LoadBalanceInverseOperator_8h</filename>
    <includes id="ml__MultiLevelPreconditioner_8h" name="ml_MultiLevelPreconditioner.h" local="yes" imported="no">ml_MultiLevelPreconditioner.h</includes>
    <includes id="MLAPI__BaseOperator_8h" name="MLAPI_BaseOperator.h" local="yes" imported="no">MLAPI_BaseOperator.h</includes>
    <includes id="MLAPI__CompObject_8h" name="MLAPI_CompObject.h" local="yes" imported="no">MLAPI_CompObject.h</includes>
    <includes id="MLAPI__InverseOperator_8h" name="MLAPI_InverseOperator.h" local="yes" imported="no">MLAPI_InverseOperator.h</includes>
    <includes id="MLAPI__LoadBalanceOperator_8h" name="MLAPI_LoadBalanceOperator.h" local="yes" imported="no">MLAPI_LoadBalanceOperator.h</includes>
    <class kind="class">MLAPI::LoadBalanceInverseOperator</class>
    <namespace>MLAPI</namespace>
  </compound>
  <compound kind="file">
    <name>MLAPI_LoadBalanceOperator.h</name>
    <path>/Users/sscoll/dist/trilinos/packages/ml/src/MLAPI/</path>
    <filename>MLAPI__LoadBalanceOperator_8h</filename>
    <includes id="MLAPI__Operator_8h" name="MLAPI_Operator.h" local="yes" imported="no">MLAPI_Operator.h</includes>
    <class kind="class">MLAPI::LoadBalanceOperator</class>
    <namespace>MLAPI</namespace>
  </compound>
  <compound kind="file">
    <name>MLAPI_MATLABStream.h</name>
    <path>/Users/sscoll/dist/trilinos/packages/ml/src/MLAPI/</path>
    <filename>MLAPI__MATLABStream_8h</filename>
    <includes id="MLAPI__Operator_8h" name="MLAPI_Operator.h" local="yes" imported="no">MLAPI_Operator.h</includes>
    <class kind="class">MLAPI::MATLABStream</class>
    <namespace>MLAPI</namespace>
  </compound>
  <compound kind="file">
    <name>MLAPI_MultiLevelAdaptiveSA.h</name>
    <path>/Users/sscoll/dist/trilinos/packages/ml/src/MLAPI/</path>
    <filename>MLAPI__MultiLevelAdaptiveSA_8h</filename>
    <includes id="MLAPI__CompObject_8h" name="MLAPI_CompObject.h" local="yes" imported="no">MLAPI_CompObject.h</includes>
    <includes id="MLAPI__Operator_8h" name="MLAPI_Operator.h" local="yes" imported="no">MLAPI_Operator.h</includes>
    <includes id="MLAPI__Operator__Utils_8h" name="MLAPI_Operator_Utils.h" local="yes" imported="no">MLAPI_Operator_Utils.h</includes>
    <includes id="MLAPI__MultiVector_8h" name="MLAPI_MultiVector.h" local="yes" imported="no">MLAPI_MultiVector.h</includes>
    <includes id="MLAPI__MultiVector__Utils_8h" name="MLAPI_MultiVector_Utils.h" local="yes" imported="no">MLAPI_MultiVector_Utils.h</includes>
    <includes id="MLAPI__InverseOperator_8h" name="MLAPI_InverseOperator.h" local="yes" imported="no">MLAPI_InverseOperator.h</includes>
    <includes id="MLAPI__Expressions_8h" name="MLAPI_Expressions.h" local="yes" imported="no">MLAPI_Expressions.h</includes>
    <includes id="MLAPI__BaseOperator_8h" name="MLAPI_BaseOperator.h" local="yes" imported="no">MLAPI_BaseOperator.h</includes>
    <includes id="MLAPI__Workspace_8h" name="MLAPI_Workspace.h" local="yes" imported="no">MLAPI_Workspace.h</includes>
    <includes id="MLAPI__Aggregation_8h" name="MLAPI_Aggregation.h" local="yes" imported="no">MLAPI_Aggregation.h</includes>
    <includes id="MLAPI__Eig_8h" name="MLAPI_Eig.h" local="yes" imported="no">MLAPI_Eig.h</includes>
    <class kind="class">MLAPI::MultiLevelAdaptiveSA</class>
    <namespace>MLAPI</namespace>
  </compound>
  <compound kind="file">
    <name>MLAPI_MultiLevelSA.h</name>
    <path>/Users/sscoll/dist/trilinos/packages/ml/src/MLAPI/</path>
    <filename>MLAPI__MultiLevelSA_8h</filename>
    <includes id="MLAPI__CompObject_8h" name="MLAPI_CompObject.h" local="yes" imported="no">MLAPI_CompObject.h</includes>
    <includes id="MLAPI__Operator_8h" name="MLAPI_Operator.h" local="yes" imported="no">MLAPI_Operator.h</includes>
    <includes id="MLAPI__Operator__Utils_8h" name="MLAPI_Operator_Utils.h" local="yes" imported="no">MLAPI_Operator_Utils.h</includes>
    <includes id="MLAPI__MultiVector_8h" name="MLAPI_MultiVector.h" local="yes" imported="no">MLAPI_MultiVector.h</includes>
    <includes id="MLAPI__InverseOperator_8h" name="MLAPI_InverseOperator.h" local="yes" imported="no">MLAPI_InverseOperator.h</includes>
    <includes id="MLAPI__Expressions_8h" name="MLAPI_Expressions.h" local="yes" imported="no">MLAPI_Expressions.h</includes>
    <includes id="MLAPI__BaseOperator_8h" name="MLAPI_BaseOperator.h" local="yes" imported="no">MLAPI_BaseOperator.h</includes>
    <includes id="MLAPI__Workspace_8h" name="MLAPI_Workspace.h" local="yes" imported="no">MLAPI_Workspace.h</includes>
    <includes id="MLAPI__Aggregation_8h" name="MLAPI_Aggregation.h" local="yes" imported="no">MLAPI_Aggregation.h</includes>
    <includes id="MLAPI__Eig_8h" name="MLAPI_Eig.h" local="yes" imported="no">MLAPI_Eig.h</includes>
    <class kind="class">MLAPI::MultiLevelSA</class>
    <namespace>MLAPI</namespace>
  </compound>
  <compound kind="file">
    <name>MLAPI_MultiVector.h</name>
    <path>/Users/sscoll/dist/trilinos/packages/ml/src/MLAPI/</path>
    <filename>MLAPI__MultiVector_8h</filename>
    <includes id="MLAPI__BaseObject_8h" name="MLAPI_BaseObject.h" local="yes" imported="no">MLAPI_BaseObject.h</includes>
    <includes id="MLAPI__Space_8h" name="MLAPI_Space.h" local="yes" imported="no">MLAPI_Space.h</includes>
    <includes id="MLAPI__CompObject_8h" name="MLAPI_CompObject.h" local="yes" imported="no">MLAPI_CompObject.h</includes>
    <includes id="MLAPI__BaseLinearCombination_8h" name="MLAPI_BaseLinearCombination.h" local="yes" imported="no">MLAPI_BaseLinearCombination.h</includes>
    <class kind="class">MLAPI::DoubleVector</class>
    <class kind="class">MLAPI::MultiVector</class>
    <namespace>MLAPI</namespace>
  </compound>
  <compound kind="file">
    <name>MLAPI_MultiVector_Utils.h</name>
    <path>/Users/sscoll/dist/trilinos/packages/ml/src/MLAPI/</path>
    <filename>MLAPI__MultiVector__Utils_8h</filename>
    <includes id="MLAPI__MultiVector_8h" name="MLAPI_MultiVector.h" local="yes" imported="no">MLAPI_MultiVector.h</includes>
    <namespace>MLAPI</namespace>
    <member kind="function">
      <type>MultiVector</type>
      <name>Duplicate</name>
      <anchorfile>namespaceMLAPI.html</anchorfile>
      <anchor>a915d25039bd3ffc80371095cec7f05eb</anchor>
      <arglist>(const MultiVector &amp;y)</arglist>
    </member>
    <member kind="function">
      <type>MultiVector</type>
      <name>Duplicate</name>
      <anchorfile>namespaceMLAPI.html</anchorfile>
      <anchor>a0bc85c1f4ed364fac977d1608c3be2e4</anchor>
      <arglist>(const MultiVector &amp;y, const int v)</arglist>
    </member>
    <member kind="function">
      <type>MultiVector</type>
      <name>Extract</name>
      <anchorfile>namespaceMLAPI.html</anchorfile>
      <anchor>a22a408a5afb903611c3b87f9dbb214b1</anchor>
      <arglist>(const MultiVector &amp;y, const int v)</arglist>
    </member>
    <member kind="function">
      <type>MultiVector</type>
      <name>Redistribute</name>
      <anchorfile>namespaceMLAPI.html</anchorfile>
      <anchor>ae89073713c2f0652695632215d7c7c48</anchor>
      <arglist>(const MultiVector &amp;y, const int NumEquations)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>MLAPI_Operator.h</name>
    <path>/Users/sscoll/dist/trilinos/packages/ml/src/MLAPI/</path>
    <filename>MLAPI__Operator_8h</filename>
    <includes id="ml__epetra__utils_8h" name="ml_epetra_utils.h" local="yes" imported="no">ml_epetra_utils.h</includes>
    <includes id="ml__RowMatrix_8h" name="ml_RowMatrix.h" local="yes" imported="no">ml_RowMatrix.h</includes>
    <includes id="MLAPI__Space_8h" name="MLAPI_Space.h" local="yes" imported="no">MLAPI_Space.h</includes>
    <includes id="MLAPI__MultiVector_8h" name="MLAPI_MultiVector.h" local="yes" imported="no">MLAPI_MultiVector.h</includes>
    <includes id="MLAPI__BaseOperator_8h" name="MLAPI_BaseOperator.h" local="yes" imported="no">MLAPI_BaseOperator.h</includes>
    <includes id="MLAPI__CompObject_8h" name="MLAPI_CompObject.h" local="yes" imported="no">MLAPI_CompObject.h</includes>
    <includes id="MLAPI__Workspace_8h" name="MLAPI_Workspace.h" local="yes" imported="no">MLAPI_Workspace.h</includes>
    <includes id="MLAPI__Operator__Box_8h" name="MLAPI_Operator_Box.h" local="yes" imported="no">MLAPI_Operator_Box.h</includes>
    <class kind="class">MLAPI::Operator</class>
    <namespace>MLAPI</namespace>
  </compound>
  <compound kind="file">
    <name>MLAPI_Operator_Box.h</name>
    <path>/Users/sscoll/dist/trilinos/packages/ml/src/MLAPI/</path>
    <filename>MLAPI__Operator__Box_8h</filename>
    <class kind="class">MLAPI::ML_Operator_Box</class>
    <namespace>MLAPI</namespace>
  </compound>
  <compound kind="file">
    <name>MLAPI_Operator_Utils.h</name>
    <path>/Users/sscoll/dist/trilinos/packages/ml/src/MLAPI/</path>
    <filename>MLAPI__Operator__Utils_8h</filename>
    <includes id="ml__epetra__utils_8h" name="ml_epetra_utils.h" local="yes" imported="no">ml_epetra_utils.h</includes>
    <includes id="ml__amesos__wrap_8h" name="ml_amesos_wrap.h" local="yes" imported="no">ml_amesos_wrap.h</includes>
    <includes id="ml__anasazi_8h" name="ml_anasazi.h" local="yes" imported="no">ml_anasazi.h</includes>
    <includes id="MLAPI__Space_8h" name="MLAPI_Space.h" local="yes" imported="no">MLAPI_Space.h</includes>
    <includes id="MLAPI__MultiVector_8h" name="MLAPI_MultiVector.h" local="yes" imported="no">MLAPI_MultiVector.h</includes>
    <includes id="MLAPI__Operator_8h" name="MLAPI_Operator.h" local="yes" imported="no">MLAPI_Operator.h</includes>
    <namespace>MLAPI</namespace>
    <member kind="function">
      <type>Operator</type>
      <name>GetRAP</name>
      <anchorfile>namespaceMLAPI.html</anchorfile>
      <anchor>a45dc3eaf084df2ed0baa2ec5e8466088</anchor>
      <arglist>(const Operator &amp;R, const Operator &amp;A, const Operator &amp;P)</arglist>
    </member>
    <member kind="function">
      <type>Operator</type>
      <name>GetTranspose</name>
      <anchorfile>namespaceMLAPI.html</anchorfile>
      <anchor>adc2f2f4e84b5e47bec27f06db43047cb</anchor>
      <arglist>(const Operator &amp;A, const bool byrow=true)</arglist>
    </member>
    <member kind="function">
      <type>Operator</type>
      <name>GetIdentity</name>
      <anchorfile>namespaceMLAPI.html</anchorfile>
      <anchor>a4eb030282f617cd49645de146b2579de</anchor>
      <arglist>(const Space &amp;DomainSpace, const Space &amp;RangeSpace)</arglist>
    </member>
    <member kind="function">
      <type>MultiVector</type>
      <name>GetDiagonal</name>
      <anchorfile>namespaceMLAPI.html</anchorfile>
      <anchor>ac10cde78ae263ce22e5c4208a7afac07</anchor>
      <arglist>(const Operator &amp;A)</arglist>
    </member>
    <member kind="function">
      <type>MultiVector</type>
      <name>GetDiagonal</name>
      <anchorfile>namespaceMLAPI.html</anchorfile>
      <anchor>a6b0c3607b5c0eaa96bab4e25f71a241c</anchor>
      <arglist>(const Operator &amp;A, const int offset)</arglist>
    </member>
    <member kind="function">
      <type>Operator</type>
      <name>GetDiagonal</name>
      <anchorfile>namespaceMLAPI.html</anchorfile>
      <anchor>a804e2b0509398ce872ce3745878fe488</anchor>
      <arglist>(const MultiVector &amp;D)</arglist>
    </member>
    <member kind="function">
      <type>Operator</type>
      <name>GetJacobiIterationOperator</name>
      <anchorfile>namespaceMLAPI.html</anchorfile>
      <anchor>a06460ec53f3dd3b2ef482581b15217f1</anchor>
      <arglist>(const Operator &amp;Amat, double Damping)</arglist>
    </member>
    <member kind="function">
      <type>Operator</type>
      <name>GetPtent1D</name>
      <anchorfile>namespaceMLAPI.html</anchorfile>
      <anchor>a6787be3f3c96d1d2f608004d2412c18e</anchor>
      <arglist>(const MultiVector &amp;D, const int offset=0)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>AnalyzeCheap</name>
      <anchorfile>namespaceMLAPI.html</anchorfile>
      <anchor>a0a2a385d7a18181c321cdde429a0e764</anchor>
      <arglist>(const Operator &amp;A)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>PrintSparsity</name>
      <anchorfile>namespaceMLAPI.html</anchorfile>
      <anchor>a306e5ad67267cd2c303f54262cfc7930</anchor>
      <arglist>(const Operator &amp;A, int NumPDEEquations=1)</arglist>
    </member>
    <member kind="function">
      <type>Operator</type>
      <name>GetScaledOperator</name>
      <anchorfile>namespaceMLAPI.html</anchorfile>
      <anchor>a89f0cce653d7c8e7002e7bc73c7c9dc3</anchor>
      <arglist>(const Operator &amp;A, const double alpha)</arglist>
    </member>
    <member kind="function">
      <type>Operator</type>
      <name>Duplicate</name>
      <anchorfile>namespaceMLAPI.html</anchorfile>
      <anchor>a580aefe59d91fce2b76a69d342e8b444</anchor>
      <arglist>(const Operator &amp;A)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>MLAPI_SerialMatrix.h</name>
    <path>/Users/sscoll/dist/trilinos/packages/ml/src/MLAPI/</path>
    <filename>MLAPI__SerialMatrix_8h</filename>
    <includes id="MLAPI__Space_8h" name="MLAPI_Space.h" local="yes" imported="no">MLAPI_Space.h</includes>
    <includes id="MLAPI__Operator_8h" name="MLAPI_Operator.h" local="yes" imported="no">MLAPI_Operator.h</includes>
    <class kind="class">MLAPI::Epetra_SerialMatrix</class>
    <class kind="class">MLAPI::SerialMatrix</class>
    <namespace>MLAPI</namespace>
  </compound>
  <compound kind="file">
    <name>MLAPI_Space.h</name>
    <path>/Users/sscoll/dist/trilinos/packages/ml/src/MLAPI/</path>
    <filename>MLAPI__Space_8h</filename>
    <includes id="MLAPI__Workspace_8h" name="MLAPI_Workspace.h" local="yes" imported="no">MLAPI_Workspace.h</includes>
    <includes id="MLAPI__BaseObject_8h" name="MLAPI_BaseObject.h" local="yes" imported="no">MLAPI_BaseObject.h</includes>
    <class kind="class">MLAPI::Space</class>
    <namespace>MLAPI</namespace>
  </compound>
  <compound kind="file">
    <name>MLAPI_Workspace.h</name>
    <path>/Users/sscoll/dist/trilinos/packages/ml/src/MLAPI/</path>
    <filename>MLAPI__Workspace_8h</filename>
    <namespace>MLAPI</namespace>
    <member kind="function">
      <type>ML_Comm *</type>
      <name>GetML_Comm</name>
      <anchorfile>namespaceMLAPI.html</anchorfile>
      <anchor>a2b92d9681a55c4d314249c244e676502</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Epetra_Comm &amp;</type>
      <name>GetEpetra_Comm</name>
      <anchorfile>namespaceMLAPI.html</anchorfile>
      <anchor>a639a90dc98e2418eca8be3d3865e2709</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Barrier</name>
      <anchorfile>namespaceMLAPI.html</anchorfile>
      <anchor>ac28167b38770ed2387cd07be88d06859</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetMyPID</name>
      <anchorfile>namespaceMLAPI.html</anchorfile>
      <anchor>a311e8c40d629be1e5ea38609c63f6f89</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetNumProcs</name>
      <anchorfile>namespaceMLAPI.html</anchorfile>
      <anchor>a0b1fd48ca2666c29d0ecc379353839f1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetPrintLevel</name>
      <anchorfile>namespaceMLAPI.html</anchorfile>
      <anchor>a7328d4c8b158abc1764d1db95790f1e8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetPrintLevel</name>
      <anchorfile>namespaceMLAPI.html</anchorfile>
      <anchor>a001fca7fbfcb719c164dd73ef3ce758d</anchor>
      <arglist>(int Level)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Init</name>
      <anchorfile>namespaceMLAPI.html</anchorfile>
      <anchor>af368e6d9fa55ccd00a482cf01dbb9828</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Finalize</name>
      <anchorfile>namespaceMLAPI.html</anchorfile>
      <anchor>aabd0be9dafbd3cca6df87930cd78e065</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>amalg_drop</name>
    <filename>structamalg__drop.html</filename>
    <member kind="variable">
      <type>void *</type>
      <name>vblock_data</name>
      <anchorfile>structamalg__drop.html</anchorfile>
      <anchor>a69c45ef092faec94d034d3601ff25a4b</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>MLAPI::BaseLinearCombination</name>
    <filename>classMLAPI_1_1BaseLinearCombination.html</filename>
    <member kind="function" virtualness="pure">
      <type>virtual const Space</type>
      <name>GetVectorSpace</name>
      <anchorfile>classMLAPI_1_1BaseLinearCombination.html</anchorfile>
      <anchor>af86fe0ec0d5a27759286bf47dcef34bc</anchor>
      <arglist>() const  =0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>MLAPI::BaseObject</name>
    <filename>classMLAPI_1_1BaseObject.html</filename>
    <member kind="function">
      <type></type>
      <name>BaseObject</name>
      <anchorfile>classMLAPI_1_1BaseObject.html</anchorfile>
      <anchor>aebdd2a5391832255644b029e17bce25c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BaseObject</name>
      <anchorfile>classMLAPI_1_1BaseObject.html</anchorfile>
      <anchor>a850a10969b831032193c7d8cbb6818f6</anchor>
      <arglist>(const std::string &amp;Label)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~BaseObject</name>
      <anchorfile>classMLAPI_1_1BaseObject.html</anchorfile>
      <anchor>a1fbb3f07e436334dced0a0aedaf9fced</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetLabel</name>
      <anchorfile>classMLAPI_1_1BaseObject.html</anchorfile>
      <anchor>a0152ffc288db66415d40a7d55cb59a8e</anchor>
      <arglist>(const std::string &amp;Label)</arglist>
    </member>
    <member kind="function">
      <type>const std::string &amp;</type>
      <name>GetLabel</name>
      <anchorfile>classMLAPI_1_1BaseObject.html</anchorfile>
      <anchor>a404c4b11fc9e27335425f2326a098e7c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual std::ostream &amp;</type>
      <name>Print</name>
      <anchorfile>classMLAPI_1_1BaseObject.html</anchorfile>
      <anchor>aa31b785aa8b8a49ac70b8f96c11bee38</anchor>
      <arglist>(std::ostream &amp;os, const bool Verbose=true) const  =0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>MLAPI::BaseOperator</name>
    <filename>classMLAPI_1_1BaseOperator.html</filename>
    <base>MLAPI::BaseObject</base>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~BaseOperator</name>
      <anchorfile>classMLAPI_1_1BaseOperator.html</anchorfile>
      <anchor>a795c9926bef5c235ec450e0274f8df62</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>Apply</name>
      <anchorfile>classMLAPI_1_1BaseOperator.html</anchorfile>
      <anchor>aa4a97078cd762ed3f5687f668835d62f</anchor>
      <arglist>(const MultiVector &amp;LHS, MultiVector &amp;RHS) const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual const Space</type>
      <name>GetOperatorDomainSpace</name>
      <anchorfile>classMLAPI_1_1BaseOperator.html</anchorfile>
      <anchor>ae37c92e62b4ca960a30b4180778f32d8</anchor>
      <arglist>() const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual const Space</type>
      <name>GetOperatorRangeSpace</name>
      <anchorfile>classMLAPI_1_1BaseOperator.html</anchorfile>
      <anchor>a4f0865f1c3bc01e7e317e48fe3bcc813</anchor>
      <arglist>() const  =0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>MLAPI::BaseOperatorTimesMultiVector</name>
    <filename>classMLAPI_1_1BaseOperatorTimesMultiVector.html</filename>
    <base>MLAPI::BaseLinearCombination</base>
    <member kind="function">
      <type>const Space</type>
      <name>GetVectorSpace</name>
      <anchorfile>classMLAPI_1_1BaseOperatorTimesMultiVector.html</anchorfile>
      <anchor>a835e9b2d4f1f48663abf86f733e8fded</anchor>
      <arglist>() const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>MLAPI::CompObject</name>
    <filename>classMLAPI_1_1CompObject.html</filename>
    <member kind="function">
      <type></type>
      <name>CompObject</name>
      <anchorfile>classMLAPI_1_1CompObject.html</anchorfile>
      <anchor>a3d251476189f11b77ce52dddca1b025a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~CompObject</name>
      <anchorfile>classMLAPI_1_1CompObject.html</anchorfile>
      <anchor>a50d94876ba7e093bba8820a5ad40abdc</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>GetFlops</name>
      <anchorfile>classMLAPI_1_1CompObject.html</anchorfile>
      <anchor>aca0706b4b38538788decf2fa4fd5f7b6</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetFlops</name>
      <anchorfile>classMLAPI_1_1CompObject.html</anchorfile>
      <anchor>ad15e283bef6527eeaa1501b7fb49a893</anchor>
      <arglist>(double Flops) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>UpdateFlops</name>
      <anchorfile>classMLAPI_1_1CompObject.html</anchorfile>
      <anchor>a69e33a031a1369a61cb906f6d764a858</anchor>
      <arglist>(double Flops) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ML_Epetra::CrsGraphWrapper</name>
    <filename>classML__Epetra_1_1CrsGraphWrapper.html</filename>
    <base virtualness="virtual">Epetra_RowMatrix</base>
    <member kind="function">
      <type></type>
      <name>CrsGraphWrapper</name>
      <anchorfile>classML__Epetra_1_1CrsGraphWrapper.html</anchorfile>
      <anchor>a24b7ea900610a06b5a783b81d79f7787</anchor>
      <arglist>(const Epetra_CrsGraph &amp;graph, const Epetra_Map &amp;dm, const Epetra_Map &amp;rm, const Epetra_Comm &amp;comm)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~CrsGraphWrapper</name>
      <anchorfile>classML__Epetra_1_1CrsGraphWrapper.html</anchorfile>
      <anchor>a59ab76f0baa1ee6c2c17a70efbb08b48</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumMyRowEntries</name>
      <anchorfile>classML__Epetra_1_1CrsGraphWrapper.html</anchorfile>
      <anchor>aad5129b057cb8893db5e311a3f43e6e0</anchor>
      <arglist>(int MyRow, int &amp;NumEntries) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>MaxNumEntries</name>
      <anchorfile>classML__Epetra_1_1CrsGraphWrapper.html</anchorfile>
      <anchor>a3a563f58916ae9a0746a1ac69646ab8e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ExtractMyRowCopy</name>
      <anchorfile>classML__Epetra_1_1CrsGraphWrapper.html</anchorfile>
      <anchor>aba1d7ba2e1f609d3d28bc8b6fb8be42d</anchor>
      <arglist>(int MyRow, int Length, int &amp;NumEntries, double *Values, int *Indices) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ExtractDiagonalCopy</name>
      <anchorfile>classML__Epetra_1_1CrsGraphWrapper.html</anchorfile>
      <anchor>ae0d013d04833061dfae239d4d41446b2</anchor>
      <arglist>(Epetra_Vector &amp;Diagonal) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Multiply</name>
      <anchorfile>classML__Epetra_1_1CrsGraphWrapper.html</anchorfile>
      <anchor>ac770d42315c1e1c48560d6ceba6970c7</anchor>
      <arglist>(bool TransA, const Epetra_MultiVector &amp;X, Epetra_MultiVector &amp;Y) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Solve</name>
      <anchorfile>classML__Epetra_1_1CrsGraphWrapper.html</anchorfile>
      <anchor>aef2735ee8a5222ddbd27b6e10322bd1e</anchor>
      <arglist>(bool Upper, bool Trans, bool UnitDiagonal, const Epetra_MultiVector &amp;X, Epetra_MultiVector &amp;Y) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>InvRowSums</name>
      <anchorfile>classML__Epetra_1_1CrsGraphWrapper.html</anchorfile>
      <anchor>ad8d30545eef1a6df5189cca813c69eb1</anchor>
      <arglist>(Epetra_Vector &amp;x) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>LeftScale</name>
      <anchorfile>classML__Epetra_1_1CrsGraphWrapper.html</anchorfile>
      <anchor>a98f6feedfb58e1048ef17cd895c23b93</anchor>
      <arglist>(const Epetra_Vector &amp;x)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>InvColSums</name>
      <anchorfile>classML__Epetra_1_1CrsGraphWrapper.html</anchorfile>
      <anchor>acc8169320716afa4fce093ee91aec1f3</anchor>
      <arglist>(Epetra_Vector &amp;x) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>RightScale</name>
      <anchorfile>classML__Epetra_1_1CrsGraphWrapper.html</anchorfile>
      <anchor>a326675e9502215f43415576f718cf5c2</anchor>
      <arglist>(const Epetra_Vector &amp;x)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>Filled</name>
      <anchorfile>classML__Epetra_1_1CrsGraphWrapper.html</anchorfile>
      <anchor>a4c6d44a677a3a0751848a36e70edd2fc</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>NormInf</name>
      <anchorfile>classML__Epetra_1_1CrsGraphWrapper.html</anchorfile>
      <anchor>ab9f597215889040d7e90a9306891c19b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>NormOne</name>
      <anchorfile>classML__Epetra_1_1CrsGraphWrapper.html</anchorfile>
      <anchor>a9e3a8a620c7c81a1c55bd0ce15c4c20c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>long long</type>
      <name>NumGlobalNonzeros</name>
      <anchorfile>classML__Epetra_1_1CrsGraphWrapper.html</anchorfile>
      <anchor>ad7af0ddfae581d3ae7d2af0d8367c1e4</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>long long</type>
      <name>NumGlobalRows</name>
      <anchorfile>classML__Epetra_1_1CrsGraphWrapper.html</anchorfile>
      <anchor>a862bc808656f4a6e6392872728ff1fd1</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>long long</type>
      <name>NumGlobalCols</name>
      <anchorfile>classML__Epetra_1_1CrsGraphWrapper.html</anchorfile>
      <anchor>a2855db5459354789176f3c11eecf2f05</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>long long</type>
      <name>NumGlobalDiagonals</name>
      <anchorfile>classML__Epetra_1_1CrsGraphWrapper.html</anchorfile>
      <anchor>a0ca02e1614dda09199ae249318876c18</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumMyNonzeros</name>
      <anchorfile>classML__Epetra_1_1CrsGraphWrapper.html</anchorfile>
      <anchor>a1bf11c465929f74f02b7a2630d7e8f42</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumMyRows</name>
      <anchorfile>classML__Epetra_1_1CrsGraphWrapper.html</anchorfile>
      <anchor>aa841e994a07c8838e608c178c5d05ff1</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumMyCols</name>
      <anchorfile>classML__Epetra_1_1CrsGraphWrapper.html</anchorfile>
      <anchor>af3d62ff24f60efb679287172c692c2b3</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumMyDiagonals</name>
      <anchorfile>classML__Epetra_1_1CrsGraphWrapper.html</anchorfile>
      <anchor>aaa144ae572f77d8c6fd48da33b8755b5</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>LowerTriangular</name>
      <anchorfile>classML__Epetra_1_1CrsGraphWrapper.html</anchorfile>
      <anchor>ad2d86daba9c2d5a95bb5c16671a257fa</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>UpperTriangular</name>
      <anchorfile>classML__Epetra_1_1CrsGraphWrapper.html</anchorfile>
      <anchor>ab796bfcfefd539fdf81a111b12e17c69</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_Map &amp;</type>
      <name>RowMatrixRowMap</name>
      <anchorfile>classML__Epetra_1_1CrsGraphWrapper.html</anchorfile>
      <anchor>a4c7495651cf9642a8b6d800e2963b354</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_Map &amp;</type>
      <name>RowMatrixColMap</name>
      <anchorfile>classML__Epetra_1_1CrsGraphWrapper.html</anchorfile>
      <anchor>a6ba394bde76f53b5e48190b1fa62d95f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_Import *</type>
      <name>RowMatrixImporter</name>
      <anchorfile>classML__Epetra_1_1CrsGraphWrapper.html</anchorfile>
      <anchor>ac6b30bd634e3ca115769d3c5b506d805</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_BlockMap &amp;</type>
      <name>Map</name>
      <anchorfile>classML__Epetra_1_1CrsGraphWrapper.html</anchorfile>
      <anchor>a2be059acb78f39cf3642c2e789254dfe</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetUseTranspose</name>
      <anchorfile>classML__Epetra_1_1CrsGraphWrapper.html</anchorfile>
      <anchor>a740bfb709374a6fc94420608a7ad27d5</anchor>
      <arglist>(bool UseTranspose)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Apply</name>
      <anchorfile>classML__Epetra_1_1CrsGraphWrapper.html</anchorfile>
      <anchor>a848d339a99dee9fbd5305486201114d8</anchor>
      <arglist>(const Epetra_MultiVector &amp;X, Epetra_MultiVector &amp;Y) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ApplyInverse</name>
      <anchorfile>classML__Epetra_1_1CrsGraphWrapper.html</anchorfile>
      <anchor>a206f799cd815925f58acabf2883510c4</anchor>
      <arglist>(const Epetra_MultiVector &amp;X, Epetra_MultiVector &amp;Y) const </arglist>
    </member>
    <member kind="function">
      <type>const char *</type>
      <name>Label</name>
      <anchorfile>classML__Epetra_1_1CrsGraphWrapper.html</anchorfile>
      <anchor>acb54b9096dfa0654cf32ef7487df1021</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>UseTranspose</name>
      <anchorfile>classML__Epetra_1_1CrsGraphWrapper.html</anchorfile>
      <anchor>acbfb79afcfd5a1651f45bdfcec25a659</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>HasNormInf</name>
      <anchorfile>classML__Epetra_1_1CrsGraphWrapper.html</anchorfile>
      <anchor>aa07f1f7de326d1126e00e293b04b4fad</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_Comm &amp;</type>
      <name>Comm</name>
      <anchorfile>classML__Epetra_1_1CrsGraphWrapper.html</anchorfile>
      <anchor>a973a1bdc7773383725a1c635e6f1e887</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_Map &amp;</type>
      <name>OperatorDomainMap</name>
      <anchorfile>classML__Epetra_1_1CrsGraphWrapper.html</anchorfile>
      <anchor>a77face507cc5283f4c403174b3f6f92f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_Map &amp;</type>
      <name>OperatorRangeMap</name>
      <anchorfile>classML__Epetra_1_1CrsGraphWrapper.html</anchorfile>
      <anchor>aae585eaa840fb78e0aad980b188d0d67</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>CrsGraphWrapper</name>
      <anchorfile>classML__Epetra_1_1CrsGraphWrapper.html</anchorfile>
      <anchor>a24b7ea900610a06b5a783b81d79f7787</anchor>
      <arglist>(const Epetra_CrsGraph &amp;graph, const Epetra_Map &amp;dm, const Epetra_Map &amp;rm, const Epetra_Comm &amp;comm)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~CrsGraphWrapper</name>
      <anchorfile>classML__Epetra_1_1CrsGraphWrapper.html</anchorfile>
      <anchor>a59ab76f0baa1ee6c2c17a70efbb08b48</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumMyRowEntries</name>
      <anchorfile>classML__Epetra_1_1CrsGraphWrapper.html</anchorfile>
      <anchor>aad5129b057cb8893db5e311a3f43e6e0</anchor>
      <arglist>(int MyRow, int &amp;NumEntries) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>MaxNumEntries</name>
      <anchorfile>classML__Epetra_1_1CrsGraphWrapper.html</anchorfile>
      <anchor>a3a563f58916ae9a0746a1ac69646ab8e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ExtractMyRowCopy</name>
      <anchorfile>classML__Epetra_1_1CrsGraphWrapper.html</anchorfile>
      <anchor>aba1d7ba2e1f609d3d28bc8b6fb8be42d</anchor>
      <arglist>(int MyRow, int Length, int &amp;NumEntries, double *Values, int *Indices) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ExtractDiagonalCopy</name>
      <anchorfile>classML__Epetra_1_1CrsGraphWrapper.html</anchorfile>
      <anchor>ae0d013d04833061dfae239d4d41446b2</anchor>
      <arglist>(Epetra_Vector &amp;Diagonal) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Multiply</name>
      <anchorfile>classML__Epetra_1_1CrsGraphWrapper.html</anchorfile>
      <anchor>ac770d42315c1e1c48560d6ceba6970c7</anchor>
      <arglist>(bool TransA, const Epetra_MultiVector &amp;X, Epetra_MultiVector &amp;Y) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Solve</name>
      <anchorfile>classML__Epetra_1_1CrsGraphWrapper.html</anchorfile>
      <anchor>aef2735ee8a5222ddbd27b6e10322bd1e</anchor>
      <arglist>(bool Upper, bool Trans, bool UnitDiagonal, const Epetra_MultiVector &amp;X, Epetra_MultiVector &amp;Y) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>InvRowSums</name>
      <anchorfile>classML__Epetra_1_1CrsGraphWrapper.html</anchorfile>
      <anchor>ad8d30545eef1a6df5189cca813c69eb1</anchor>
      <arglist>(Epetra_Vector &amp;x) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>LeftScale</name>
      <anchorfile>classML__Epetra_1_1CrsGraphWrapper.html</anchorfile>
      <anchor>a98f6feedfb58e1048ef17cd895c23b93</anchor>
      <arglist>(const Epetra_Vector &amp;x)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>InvColSums</name>
      <anchorfile>classML__Epetra_1_1CrsGraphWrapper.html</anchorfile>
      <anchor>acc8169320716afa4fce093ee91aec1f3</anchor>
      <arglist>(Epetra_Vector &amp;x) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>RightScale</name>
      <anchorfile>classML__Epetra_1_1CrsGraphWrapper.html</anchorfile>
      <anchor>a326675e9502215f43415576f718cf5c2</anchor>
      <arglist>(const Epetra_Vector &amp;x)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>Filled</name>
      <anchorfile>classML__Epetra_1_1CrsGraphWrapper.html</anchorfile>
      <anchor>a4c6d44a677a3a0751848a36e70edd2fc</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>NormInf</name>
      <anchorfile>classML__Epetra_1_1CrsGraphWrapper.html</anchorfile>
      <anchor>ab9f597215889040d7e90a9306891c19b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>NormOne</name>
      <anchorfile>classML__Epetra_1_1CrsGraphWrapper.html</anchorfile>
      <anchor>a9e3a8a620c7c81a1c55bd0ce15c4c20c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>long long</type>
      <name>NumGlobalNonzeros</name>
      <anchorfile>classML__Epetra_1_1CrsGraphWrapper.html</anchorfile>
      <anchor>ad7af0ddfae581d3ae7d2af0d8367c1e4</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>long long</type>
      <name>NumGlobalRows</name>
      <anchorfile>classML__Epetra_1_1CrsGraphWrapper.html</anchorfile>
      <anchor>a862bc808656f4a6e6392872728ff1fd1</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>long long</type>
      <name>NumGlobalCols</name>
      <anchorfile>classML__Epetra_1_1CrsGraphWrapper.html</anchorfile>
      <anchor>a2855db5459354789176f3c11eecf2f05</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>long long</type>
      <name>NumGlobalDiagonals</name>
      <anchorfile>classML__Epetra_1_1CrsGraphWrapper.html</anchorfile>
      <anchor>a0ca02e1614dda09199ae249318876c18</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumMyNonzeros</name>
      <anchorfile>classML__Epetra_1_1CrsGraphWrapper.html</anchorfile>
      <anchor>a1bf11c465929f74f02b7a2630d7e8f42</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumMyRows</name>
      <anchorfile>classML__Epetra_1_1CrsGraphWrapper.html</anchorfile>
      <anchor>aa841e994a07c8838e608c178c5d05ff1</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumMyCols</name>
      <anchorfile>classML__Epetra_1_1CrsGraphWrapper.html</anchorfile>
      <anchor>af3d62ff24f60efb679287172c692c2b3</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumMyDiagonals</name>
      <anchorfile>classML__Epetra_1_1CrsGraphWrapper.html</anchorfile>
      <anchor>aaa144ae572f77d8c6fd48da33b8755b5</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>LowerTriangular</name>
      <anchorfile>classML__Epetra_1_1CrsGraphWrapper.html</anchorfile>
      <anchor>ad2d86daba9c2d5a95bb5c16671a257fa</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>UpperTriangular</name>
      <anchorfile>classML__Epetra_1_1CrsGraphWrapper.html</anchorfile>
      <anchor>ab796bfcfefd539fdf81a111b12e17c69</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_Map &amp;</type>
      <name>RowMatrixRowMap</name>
      <anchorfile>classML__Epetra_1_1CrsGraphWrapper.html</anchorfile>
      <anchor>a4c7495651cf9642a8b6d800e2963b354</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_Map &amp;</type>
      <name>RowMatrixColMap</name>
      <anchorfile>classML__Epetra_1_1CrsGraphWrapper.html</anchorfile>
      <anchor>a6ba394bde76f53b5e48190b1fa62d95f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_Import *</type>
      <name>RowMatrixImporter</name>
      <anchorfile>classML__Epetra_1_1CrsGraphWrapper.html</anchorfile>
      <anchor>ac6b30bd634e3ca115769d3c5b506d805</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_BlockMap &amp;</type>
      <name>Map</name>
      <anchorfile>classML__Epetra_1_1CrsGraphWrapper.html</anchorfile>
      <anchor>a2be059acb78f39cf3642c2e789254dfe</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetUseTranspose</name>
      <anchorfile>classML__Epetra_1_1CrsGraphWrapper.html</anchorfile>
      <anchor>a740bfb709374a6fc94420608a7ad27d5</anchor>
      <arglist>(bool UseTranspose)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Apply</name>
      <anchorfile>classML__Epetra_1_1CrsGraphWrapper.html</anchorfile>
      <anchor>a848d339a99dee9fbd5305486201114d8</anchor>
      <arglist>(const Epetra_MultiVector &amp;X, Epetra_MultiVector &amp;Y) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ApplyInverse</name>
      <anchorfile>classML__Epetra_1_1CrsGraphWrapper.html</anchorfile>
      <anchor>a206f799cd815925f58acabf2883510c4</anchor>
      <arglist>(const Epetra_MultiVector &amp;X, Epetra_MultiVector &amp;Y) const </arglist>
    </member>
    <member kind="function">
      <type>const char *</type>
      <name>Label</name>
      <anchorfile>classML__Epetra_1_1CrsGraphWrapper.html</anchorfile>
      <anchor>acb54b9096dfa0654cf32ef7487df1021</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>UseTranspose</name>
      <anchorfile>classML__Epetra_1_1CrsGraphWrapper.html</anchorfile>
      <anchor>acbfb79afcfd5a1651f45bdfcec25a659</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>HasNormInf</name>
      <anchorfile>classML__Epetra_1_1CrsGraphWrapper.html</anchorfile>
      <anchor>aa07f1f7de326d1126e00e293b04b4fad</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_Comm &amp;</type>
      <name>Comm</name>
      <anchorfile>classML__Epetra_1_1CrsGraphWrapper.html</anchorfile>
      <anchor>a973a1bdc7773383725a1c635e6f1e887</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_Map &amp;</type>
      <name>OperatorDomainMap</name>
      <anchorfile>classML__Epetra_1_1CrsGraphWrapper.html</anchorfile>
      <anchor>a77face507cc5283f4c403174b3f6f92f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_Map &amp;</type>
      <name>OperatorRangeMap</name>
      <anchorfile>classML__Epetra_1_1CrsGraphWrapper.html</anchorfile>
      <anchor>aae585eaa840fb78e0aad980b188d0d67</anchor>
      <arglist>() const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>MLAPI::DistributedMatrix</name>
    <filename>classMLAPI_1_1DistributedMatrix.html</filename>
    <base>Epetra_RowMatrix</base>
    <base>MLAPI::Operator</base>
    <member kind="function">
      <type>int</type>
      <name>Apply</name>
      <anchorfile>classMLAPI_1_1DistributedMatrix.html</anchorfile>
      <anchor>ab714f29a935c0564c54a75d257b932da</anchor>
      <arglist>(const MultiVector &amp;X, MultiVector &amp;Y) const </arglist>
    </member>
    <member kind="function">
      <type>std::ostream &amp;</type>
      <name>Print</name>
      <anchorfile>classMLAPI_1_1DistributedMatrix.html</anchorfile>
      <anchor>a2022608c15088fc7736255b9f124a79c</anchor>
      <arglist>(std::ostream &amp;os, const bool verbose=true) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>MLAPI::DoubleVector</name>
    <filename>classMLAPI_1_1DoubleVector.html</filename>
  </compound>
  <compound kind="class">
    <name>ML_Epetra::EdgeMatrixFreePreconditioner</name>
    <filename>classML__Epetra_1_1EdgeMatrixFreePreconditioner.html</filename>
    <member kind="function">
      <type></type>
      <name>EdgeMatrixFreePreconditioner</name>
      <anchorfile>classML__Epetra_1_1EdgeMatrixFreePreconditioner.html</anchorfile>
      <anchor>a8a6dcb7efbc9bae9cd6c0a1329c449cd</anchor>
      <arglist>(Teuchos::RCP&lt; const Epetra_Operator &gt; Operator, Teuchos::RCP&lt; const Epetra_Vector &gt; Diagonal, Teuchos::RCP&lt; const Epetra_CrsMatrix &gt; D0_Matrix, Teuchos::RCP&lt; const Epetra_CrsMatrix &gt; D0_Clean_Matrix, Teuchos::RCP&lt; const Epetra_CrsMatrix &gt; TMT_Matrix, Teuchos::ArrayRCP&lt; int &gt; BCedges, const Teuchos::ParameterList &amp;List, const bool ComputePrec=true)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~EdgeMatrixFreePreconditioner</name>
      <anchorfile>classML__Epetra_1_1EdgeMatrixFreePreconditioner.html</anchorfile>
      <anchor>a5c67d0b83fa00ebc38a0f5d629b25d0b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ComputePreconditioner</name>
      <anchorfile>classML__Epetra_1_1EdgeMatrixFreePreconditioner.html</anchorfile>
      <anchor>acbe034dea1416be52cb4254d208ed37b</anchor>
      <arglist>(const bool CheckFiltering=false)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ReComputePreconditioner</name>
      <anchorfile>classML__Epetra_1_1EdgeMatrixFreePreconditioner.html</anchorfile>
      <anchor>a21b79fa36f64597a0d408914deaa0926</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Apply</name>
      <anchorfile>classML__Epetra_1_1EdgeMatrixFreePreconditioner.html</anchorfile>
      <anchor>ae3c96577c43ee69df8a0974ec3aa6aeb</anchor>
      <arglist>(const Epetra_MultiVector &amp;X, Epetra_MultiVector &amp;Y) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ApplyInverse</name>
      <anchorfile>classML__Epetra_1_1EdgeMatrixFreePreconditioner.html</anchorfile>
      <anchor>aa603d217e38f10503d24ad5633803c5c</anchor>
      <arglist>(const Epetra_MultiVector &amp;B, Epetra_MultiVector &amp;X) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Print</name>
      <anchorfile>classML__Epetra_1_1EdgeMatrixFreePreconditioner.html</anchorfile>
      <anchor>a340eeb1dc3b027f89116f967da0e88b8</anchor>
      <arglist>(int whichHierarchy=-2)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>DestroyPreconditioner</name>
      <anchorfile>classML__Epetra_1_1EdgeMatrixFreePreconditioner.html</anchorfile>
      <anchor>aa36814db94d10bcdf2089665f55fdb04</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetUseTranspose</name>
      <anchorfile>classML__Epetra_1_1EdgeMatrixFreePreconditioner.html</anchorfile>
      <anchor>ae03de95c9483f0f3c28b7e3d04edc44e</anchor>
      <arglist>(bool UseTranspose)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>NormInf</name>
      <anchorfile>classML__Epetra_1_1EdgeMatrixFreePreconditioner.html</anchorfile>
      <anchor>ac6667952ec01eff9ba94900d7d4fdd13</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>UseTranspose</name>
      <anchorfile>classML__Epetra_1_1EdgeMatrixFreePreconditioner.html</anchorfile>
      <anchor>a1c356e6cf7dd2498f5ef2458077adae4</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>HasNormInf</name>
      <anchorfile>classML__Epetra_1_1EdgeMatrixFreePreconditioner.html</anchorfile>
      <anchor>a8e8584d498aad93557605e04d7d94ba2</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_Comm &amp;</type>
      <name>Comm</name>
      <anchorfile>classML__Epetra_1_1EdgeMatrixFreePreconditioner.html</anchorfile>
      <anchor>ae39228ed73fb5abb682fab55c672e2cb</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_Map &amp;</type>
      <name>OperatorDomainMap</name>
      <anchorfile>classML__Epetra_1_1EdgeMatrixFreePreconditioner.html</anchorfile>
      <anchor>ad9d2ec0d85905227510ce2c0dbd2ae6a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_Map &amp;</type>
      <name>OperatorRangeMap</name>
      <anchorfile>classML__Epetra_1_1EdgeMatrixFreePreconditioner.html</anchorfile>
      <anchor>a666d326b9b0652e7c822096bd1da035f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Complexities</name>
      <anchorfile>classML__Epetra_1_1EdgeMatrixFreePreconditioner.html</anchorfile>
      <anchor>a14586470a693156c9b274efc486996ef</anchor>
      <arglist>(double &amp;complexity, double &amp;fineNnz)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>EdgeMatrixFreePreconditioner</name>
      <anchorfile>classML__Epetra_1_1EdgeMatrixFreePreconditioner.html</anchorfile>
      <anchor>a8a6dcb7efbc9bae9cd6c0a1329c449cd</anchor>
      <arglist>(Teuchos::RCP&lt; const Epetra_Operator &gt; Operator, Teuchos::RCP&lt; const Epetra_Vector &gt; Diagonal, Teuchos::RCP&lt; const Epetra_CrsMatrix &gt; D0_Matrix, Teuchos::RCP&lt; const Epetra_CrsMatrix &gt; D0_Clean_Matrix, Teuchos::RCP&lt; const Epetra_CrsMatrix &gt; TMT_Matrix, Teuchos::ArrayRCP&lt; int &gt; BCedges, const Teuchos::ParameterList &amp;List, const bool ComputePrec=true)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~EdgeMatrixFreePreconditioner</name>
      <anchorfile>classML__Epetra_1_1EdgeMatrixFreePreconditioner.html</anchorfile>
      <anchor>a5c67d0b83fa00ebc38a0f5d629b25d0b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ComputePreconditioner</name>
      <anchorfile>classML__Epetra_1_1EdgeMatrixFreePreconditioner.html</anchorfile>
      <anchor>acbe034dea1416be52cb4254d208ed37b</anchor>
      <arglist>(const bool CheckFiltering=false)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ReComputePreconditioner</name>
      <anchorfile>classML__Epetra_1_1EdgeMatrixFreePreconditioner.html</anchorfile>
      <anchor>a21b79fa36f64597a0d408914deaa0926</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Apply</name>
      <anchorfile>classML__Epetra_1_1EdgeMatrixFreePreconditioner.html</anchorfile>
      <anchor>ae3c96577c43ee69df8a0974ec3aa6aeb</anchor>
      <arglist>(const Epetra_MultiVector &amp;X, Epetra_MultiVector &amp;Y) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ApplyInverse</name>
      <anchorfile>classML__Epetra_1_1EdgeMatrixFreePreconditioner.html</anchorfile>
      <anchor>aa603d217e38f10503d24ad5633803c5c</anchor>
      <arglist>(const Epetra_MultiVector &amp;B, Epetra_MultiVector &amp;X) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Print</name>
      <anchorfile>classML__Epetra_1_1EdgeMatrixFreePreconditioner.html</anchorfile>
      <anchor>a340eeb1dc3b027f89116f967da0e88b8</anchor>
      <arglist>(int whichHierarchy=-2)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>DestroyPreconditioner</name>
      <anchorfile>classML__Epetra_1_1EdgeMatrixFreePreconditioner.html</anchorfile>
      <anchor>aa36814db94d10bcdf2089665f55fdb04</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetUseTranspose</name>
      <anchorfile>classML__Epetra_1_1EdgeMatrixFreePreconditioner.html</anchorfile>
      <anchor>ae03de95c9483f0f3c28b7e3d04edc44e</anchor>
      <arglist>(bool UseTranspose)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>NormInf</name>
      <anchorfile>classML__Epetra_1_1EdgeMatrixFreePreconditioner.html</anchorfile>
      <anchor>ac6667952ec01eff9ba94900d7d4fdd13</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>UseTranspose</name>
      <anchorfile>classML__Epetra_1_1EdgeMatrixFreePreconditioner.html</anchorfile>
      <anchor>a1c356e6cf7dd2498f5ef2458077adae4</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>HasNormInf</name>
      <anchorfile>classML__Epetra_1_1EdgeMatrixFreePreconditioner.html</anchorfile>
      <anchor>a8e8584d498aad93557605e04d7d94ba2</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_Comm &amp;</type>
      <name>Comm</name>
      <anchorfile>classML__Epetra_1_1EdgeMatrixFreePreconditioner.html</anchorfile>
      <anchor>ae39228ed73fb5abb682fab55c672e2cb</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_Map &amp;</type>
      <name>OperatorDomainMap</name>
      <anchorfile>classML__Epetra_1_1EdgeMatrixFreePreconditioner.html</anchorfile>
      <anchor>ad9d2ec0d85905227510ce2c0dbd2ae6a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_Map &amp;</type>
      <name>OperatorRangeMap</name>
      <anchorfile>classML__Epetra_1_1EdgeMatrixFreePreconditioner.html</anchorfile>
      <anchor>a666d326b9b0652e7c822096bd1da035f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Complexities</name>
      <anchorfile>classML__Epetra_1_1EdgeMatrixFreePreconditioner.html</anchorfile>
      <anchor>a14586470a693156c9b274efc486996ef</anchor>
      <arglist>(double &amp;complexity, double &amp;fineNnz)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>EdgeMatrixFreePreconditioner</name>
    <filename>classEdgeMatrixFreePreconditioner.html</filename>
  </compound>
  <compound kind="class">
    <name>MLAPI::Epetra_SerialMatrix</name>
    <filename>classMLAPI_1_1Epetra__SerialMatrix.html</filename>
    <base>Epetra_RowMatrix</base>
  </compound>
  <compound kind="class">
    <name>MLAPI::EpetraBaseOperator</name>
    <filename>classMLAPI_1_1EpetraBaseOperator.html</filename>
    <base>Epetra_Operator</base>
    <member kind="function">
      <type></type>
      <name>EpetraBaseOperator</name>
      <anchorfile>classMLAPI_1_1EpetraBaseOperator.html</anchorfile>
      <anchor>a303530db5ac57c236c4e5d4450983959</anchor>
      <arglist>(const Epetra_Map &amp;inMap, const BaseOperator &amp;Op)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~EpetraBaseOperator</name>
      <anchorfile>classMLAPI_1_1EpetraBaseOperator.html</anchorfile>
      <anchor>a6f4e8f27f38567e0248fe224d12d2ffd</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ApplyInverse</name>
      <anchorfile>classMLAPI_1_1EpetraBaseOperator.html</anchorfile>
      <anchor>a053ea74aa1bb4be09f294853a0330372</anchor>
      <arglist>(const Epetra_MultiVector &amp;X_Epetra, Epetra_MultiVector &amp;Y_Epetra) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>SetUseTranspose</name>
      <anchorfile>classMLAPI_1_1EpetraBaseOperator.html</anchorfile>
      <anchor>afd1d935df43f75c007ec60881062a73b</anchor>
      <arglist>(bool UseTransposeFlag)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>Apply</name>
      <anchorfile>classMLAPI_1_1EpetraBaseOperator.html</anchorfile>
      <anchor>a8335c2bb73b72ddc81d59591e266371d</anchor>
      <arglist>(const Epetra_MultiVector &amp;X_Epetra, Epetra_MultiVector &amp;Y_Epetra) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual double</type>
      <name>NormInf</name>
      <anchorfile>classMLAPI_1_1EpetraBaseOperator.html</anchorfile>
      <anchor>ac64815cce4317cc558eae9b11f8d73c9</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const char *</type>
      <name>Label</name>
      <anchorfile>classMLAPI_1_1EpetraBaseOperator.html</anchorfile>
      <anchor>a7ba5cd001bd38a62473bccd225346747</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>UseTranspose</name>
      <anchorfile>classMLAPI_1_1EpetraBaseOperator.html</anchorfile>
      <anchor>aa4ac849bc90755eb067a22a8978afe52</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>HasNormInf</name>
      <anchorfile>classMLAPI_1_1EpetraBaseOperator.html</anchorfile>
      <anchor>adf540b897af56fcb134150d31caeee44</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const Epetra_Comm &amp;</type>
      <name>Comm</name>
      <anchorfile>classMLAPI_1_1EpetraBaseOperator.html</anchorfile>
      <anchor>a2c86fd4bf0ebe38eb78bf3e61c757548</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const Epetra_Map &amp;</type>
      <name>OperatorDomainMap</name>
      <anchorfile>classMLAPI_1_1EpetraBaseOperator.html</anchorfile>
      <anchor>adae06a402f0a5b1f3270b2adc6f5bd17</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const Epetra_Map &amp;</type>
      <name>OperatorRangeMap</name>
      <anchorfile>classMLAPI_1_1EpetraBaseOperator.html</anchorfile>
      <anchor>acdd8dd699a694823c67c0f5f245a7cb2</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const Epetra_Map &amp;</type>
      <name>Map</name>
      <anchorfile>classMLAPI_1_1EpetraBaseOperator.html</anchorfile>
      <anchor>a35e1f0ef62bd9e291e97a673a7b95ed2</anchor>
      <arglist>() const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ML_Epetra::Ifpack_ML</name>
    <filename>classML__Epetra_1_1Ifpack__ML.html</filename>
    <member kind="function">
      <type></type>
      <name>Ifpack_ML</name>
      <anchorfile>classML__Epetra_1_1Ifpack__ML.html</anchorfile>
      <anchor>ae4c924fa682c24c239b11af22e085cec</anchor>
      <arglist>(Epetra_RowMatrix *A)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~Ifpack_ML</name>
      <anchorfile>classML__Epetra_1_1Ifpack__ML.html</anchorfile>
      <anchor>a8064abbe533d698f91a73337234c1e5b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>SetParameters</name>
      <anchorfile>classML__Epetra_1_1Ifpack__ML.html</anchorfile>
      <anchor>a9622a3040f8c9face427ee9dfb24d940</anchor>
      <arglist>(Teuchos::ParameterList &amp;List)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>Initialize</name>
      <anchorfile>classML__Epetra_1_1Ifpack__ML.html</anchorfile>
      <anchor>af71b1e752f99ee021ff32367c415b15b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>IsInitialized</name>
      <anchorfile>classML__Epetra_1_1Ifpack__ML.html</anchorfile>
      <anchor>ab6d201f1a8780ca129cc117fb47c0da9</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>Compute</name>
      <anchorfile>classML__Epetra_1_1Ifpack__ML.html</anchorfile>
      <anchor>a29311ede1056160bd63ac51de8f3bd28</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>IsComputed</name>
      <anchorfile>classML__Epetra_1_1Ifpack__ML.html</anchorfile>
      <anchor>a83504f73f4d607119046a1ea53682924</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual double</type>
      <name>Condest</name>
      <anchorfile>classML__Epetra_1_1Ifpack__ML.html</anchorfile>
      <anchor>a5aaf065e1d836da947b13d092cfc897c</anchor>
      <arglist>(const Ifpack_CondestType CT=Ifpack_Cheap, const int MaxIters=1550, const double Tol=1e-9, Epetra_RowMatrix *matrix=0)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual double</type>
      <name>Condest</name>
      <anchorfile>classML__Epetra_1_1Ifpack__ML.html</anchorfile>
      <anchor>a56bc25246ee11748e926f0508f3bea32</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>ApplyInverse</name>
      <anchorfile>classML__Epetra_1_1Ifpack__ML.html</anchorfile>
      <anchor>a2a1a59ab45caf3cca002ffa875ef1ecc</anchor>
      <arglist>(const Epetra_MultiVector &amp;X, Epetra_MultiVector &amp;Y) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const Epetra_RowMatrix &amp;</type>
      <name>Matrix</name>
      <anchorfile>classML__Epetra_1_1Ifpack__ML.html</anchorfile>
      <anchor>ab16f735600b665f858987b6168a7dca7</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>NumInitialize</name>
      <anchorfile>classML__Epetra_1_1Ifpack__ML.html</anchorfile>
      <anchor>aff374d623a060b5f4f22e30eb866e44a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>NumCompute</name>
      <anchorfile>classML__Epetra_1_1Ifpack__ML.html</anchorfile>
      <anchor>aa32f734178d5580cbf6f08e07bb8eaf0</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>NumApplyInverse</name>
      <anchorfile>classML__Epetra_1_1Ifpack__ML.html</anchorfile>
      <anchor>a9e52c1d27b0ba12ac41d30efa9b0a7cf</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual double</type>
      <name>InitializeTime</name>
      <anchorfile>classML__Epetra_1_1Ifpack__ML.html</anchorfile>
      <anchor>a9ec8dfb060e272809660c2b920b4af7b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual double</type>
      <name>ComputeTime</name>
      <anchorfile>classML__Epetra_1_1Ifpack__ML.html</anchorfile>
      <anchor>a834b417d3fdfb4115bea295d478aa184</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual double</type>
      <name>ApplyInverseTime</name>
      <anchorfile>classML__Epetra_1_1Ifpack__ML.html</anchorfile>
      <anchor>a34c48f7469995189be2a52f0c43ee973</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual double</type>
      <name>InitializeFlops</name>
      <anchorfile>classML__Epetra_1_1Ifpack__ML.html</anchorfile>
      <anchor>a1b70208b45cd1695702093d4171a2914</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual double</type>
      <name>ComputeFlops</name>
      <anchorfile>classML__Epetra_1_1Ifpack__ML.html</anchorfile>
      <anchor>a7b59f05a2a934860f11429eeb9ba5b4c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual double</type>
      <name>ApplyInverseFlops</name>
      <anchorfile>classML__Epetra_1_1Ifpack__ML.html</anchorfile>
      <anchor>ab555f8addf247ed2203e8233ef451da0</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual std::ostream &amp;</type>
      <name>Print</name>
      <anchorfile>classML__Epetra_1_1Ifpack__ML.html</anchorfile>
      <anchor>a2949b70dd65f43538ddd7b2f01abe3b1</anchor>
      <arglist>(std::ostream &amp;os) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetUseTranspose</name>
      <anchorfile>classML__Epetra_1_1Ifpack__ML.html</anchorfile>
      <anchor>aaae5eca44fc620ed85588dfc44ada2d0</anchor>
      <arglist>(bool useTranspose)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Apply</name>
      <anchorfile>classML__Epetra_1_1Ifpack__ML.html</anchorfile>
      <anchor>a2904f1290750bd3a1851629169c81449</anchor>
      <arglist>(const Epetra_MultiVector &amp;, Epetra_MultiVector &amp;) const </arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>NormInf</name>
      <anchorfile>classML__Epetra_1_1Ifpack__ML.html</anchorfile>
      <anchor>a5440e6333a42ae057e0481b2d0fc3d46</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const char *</type>
      <name>Label</name>
      <anchorfile>classML__Epetra_1_1Ifpack__ML.html</anchorfile>
      <anchor>abefe74858541d4ccfa2baa9c2cfc85aa</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>UseTranspose</name>
      <anchorfile>classML__Epetra_1_1Ifpack__ML.html</anchorfile>
      <anchor>aa0d5a0797d4389fe1606ba342c0f4f32</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>HasNormInf</name>
      <anchorfile>classML__Epetra_1_1Ifpack__ML.html</anchorfile>
      <anchor>a175144fffe0fe70dbc2658e4dc316fde</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_Comm &amp;</type>
      <name>Comm</name>
      <anchorfile>classML__Epetra_1_1Ifpack__ML.html</anchorfile>
      <anchor>a95a154b7d1768d4a83550bf5d1961ff9</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_Map &amp;</type>
      <name>OperatorDomainMap</name>
      <anchorfile>classML__Epetra_1_1Ifpack__ML.html</anchorfile>
      <anchor>a79c63a9923ab10bfe394b0a2624cf925</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_Map &amp;</type>
      <name>OperatorRangeMap</name>
      <anchorfile>classML__Epetra_1_1Ifpack__ML.html</anchorfile>
      <anchor>a690b7c4f13f5b58e527bbd4aa2f030b7</anchor>
      <arglist>() const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Ifpack_ML</name>
    <filename>classIfpack__ML.html</filename>
  </compound>
  <compound kind="class">
    <name>MLAPI::InverseOperator</name>
    <filename>classMLAPI_1_1InverseOperator.html</filename>
    <base>MLAPI::BaseOperator</base>
    <base>MLAPI::CompObject</base>
    <base>MLAPI::TimeObject</base>
    <member kind="function">
      <type></type>
      <name>InverseOperator</name>
      <anchorfile>classMLAPI_1_1InverseOperator.html</anchorfile>
      <anchor>a1da5d33519ce822923581590b3ab20c3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>InverseOperator</name>
      <anchorfile>classMLAPI_1_1InverseOperator.html</anchorfile>
      <anchor>af2e2214dd5ca1d38bb83b987c765f26d</anchor>
      <arglist>(const Operator &amp;Op, const std::string Type)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>InverseOperator</name>
      <anchorfile>classMLAPI_1_1InverseOperator.html</anchorfile>
      <anchor>acdc48de3599255bfb1961a6c2906a0f0</anchor>
      <arglist>(const Operator &amp;Op, const std::string Type, Teuchos::ParameterList &amp;List)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>InverseOperator</name>
      <anchorfile>classMLAPI_1_1InverseOperator.html</anchorfile>
      <anchor>a1971f46d3723242ef362ee38b77fd7df</anchor>
      <arglist>(const InverseOperator &amp;RHS)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~InverseOperator</name>
      <anchorfile>classMLAPI_1_1InverseOperator.html</anchorfile>
      <anchor>a796ddbbbcee78a17e5cca3b3f6ec9b47</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>InverseOperator &amp;</type>
      <name>operator=</name>
      <anchorfile>classMLAPI_1_1InverseOperator.html</anchorfile>
      <anchor>a08ece47e6aa30b3553fde7ae529a5653</anchor>
      <arglist>(const InverseOperator &amp;RHS)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Reshape</name>
      <anchorfile>classMLAPI_1_1InverseOperator.html</anchorfile>
      <anchor>a36422a033d75a4809af8563bccad9595</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Reshape</name>
      <anchorfile>classMLAPI_1_1InverseOperator.html</anchorfile>
      <anchor>a45da4959b73d0e5416a15de6c265433d</anchor>
      <arglist>(const Operator &amp;Op, const std::string Type)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Reshape</name>
      <anchorfile>classMLAPI_1_1InverseOperator.html</anchorfile>
      <anchor>a16c89d526165df98ea0de597ac486ab8</anchor>
      <arglist>(const Operator &amp;Op, const std::string Type, Teuchos::ParameterList &amp;List, Teuchos::ParameterList *pushlist=NULL)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Reshape</name>
      <anchorfile>classMLAPI_1_1InverseOperator.html</anchorfile>
      <anchor>a50ee5b320ec03873443da5151e7e617b</anchor>
      <arglist>(Ifpack_Preconditioner *prec, const Operator &amp;Op, const bool ownership)</arglist>
    </member>
    <member kind="function">
      <type>const Space</type>
      <name>GetOperatorRangeSpace</name>
      <anchorfile>classMLAPI_1_1InverseOperator.html</anchorfile>
      <anchor>a8e2cac342c8d210fae6b90d2a1f36b6c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Space</type>
      <name>GetOperatorDomainSpace</name>
      <anchorfile>classMLAPI_1_1InverseOperator.html</anchorfile>
      <anchor>a8219d99fe72c0aa713b6c8f1b5042c7d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Space</type>
      <name>GetRangeSpace</name>
      <anchorfile>classMLAPI_1_1InverseOperator.html</anchorfile>
      <anchor>ae179313eb16fcbbd2684660e0a2adff9</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Space</type>
      <name>GetDomainSpace</name>
      <anchorfile>classMLAPI_1_1InverseOperator.html</anchorfile>
      <anchor>ad744113609782d864f53b0b2c34329a9</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Teuchos::RefCountPtr&lt; Epetra_RowMatrix &gt;</type>
      <name>RCPRowMatrix</name>
      <anchorfile>classMLAPI_1_1InverseOperator.html</anchorfile>
      <anchor>a8f09f2b1cbfa38e861c3c6950618d151</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Epetra_RowMatrix *</type>
      <name>RowMatrix</name>
      <anchorfile>classMLAPI_1_1InverseOperator.html</anchorfile>
      <anchor>a163c57d973e95f407699a1d6328bf1c1</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Operator &amp;</type>
      <name>GetOperator</name>
      <anchorfile>classMLAPI_1_1InverseOperator.html</anchorfile>
      <anchor>ab7a4b95001bfb5e5f92cd1700cdddb1c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RefCountPtr&lt; Ifpack_Preconditioner &gt; &amp;</type>
      <name>GetRCPData</name>
      <anchorfile>classMLAPI_1_1InverseOperator.html</anchorfile>
      <anchor>abe1d99157ccd12272b6d06d821bc787b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RefCountPtr&lt; ML_Epetra::MultiLevelPreconditioner &gt; &amp;</type>
      <name>GetRCPMLPrec</name>
      <anchorfile>classMLAPI_1_1InverseOperator.html</anchorfile>
      <anchor>ae329b3c1b6d863b97ce5b70be1c856a4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const Teuchos::RefCountPtr&lt; Ifpack_Preconditioner &gt; &amp;</type>
      <name>GetRCPData</name>
      <anchorfile>classMLAPI_1_1InverseOperator.html</anchorfile>
      <anchor>a3001dfb6764d39b6998666ded1c23aec</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Teuchos::RefCountPtr&lt; ML_Epetra::MultiLevelPreconditioner &gt; &amp;</type>
      <name>GetRCPMLPrec</name>
      <anchorfile>classMLAPI_1_1InverseOperator.html</anchorfile>
      <anchor>ae4b0b196cf3333bbbde48a5ba93bcaf8</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Apply</name>
      <anchorfile>classMLAPI_1_1InverseOperator.html</anchorfile>
      <anchor>acb5f53543bdc84e0640ff59cc328fa21</anchor>
      <arglist>(const MultiVector &amp;x, MultiVector &amp;y) const </arglist>
    </member>
    <member kind="function">
      <type>MultiVector</type>
      <name>operator()</name>
      <anchorfile>classMLAPI_1_1InverseOperator.html</anchorfile>
      <anchor>a4ecf7ffdf0ad9256c7962fc4edaf7716</anchor>
      <arglist>(const MultiVector &amp;LHS)</arglist>
    </member>
    <member kind="function">
      <type>MultiVector</type>
      <name>operator()</name>
      <anchorfile>classMLAPI_1_1InverseOperator.html</anchorfile>
      <anchor>a63c28f2b0e7c2b27b3b2b09901ea2a88</anchor>
      <arglist>(const MultiVector &amp;LHS, const MultiVector &amp;RHS)</arglist>
    </member>
    <member kind="function">
      <type>std::ostream &amp;</type>
      <name>Print</name>
      <anchorfile>classMLAPI_1_1InverseOperator.html</anchorfile>
      <anchor>ae758d9df22e66b0e081cec021f9396d1</anchor>
      <arglist>(std::ostream &amp;os, const bool verbose=true) const </arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>InverseOperator</name>
      <anchorfile>classMLAPI_1_1InverseOperator.html</anchorfile>
      <anchor>a1da5d33519ce822923581590b3ab20c3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>InverseOperator</name>
      <anchorfile>classMLAPI_1_1InverseOperator.html</anchorfile>
      <anchor>af2e2214dd5ca1d38bb83b987c765f26d</anchor>
      <arglist>(const Operator &amp;Op, const std::string Type)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>InverseOperator</name>
      <anchorfile>classMLAPI_1_1InverseOperator.html</anchorfile>
      <anchor>acdc48de3599255bfb1961a6c2906a0f0</anchor>
      <arglist>(const Operator &amp;Op, const std::string Type, Teuchos::ParameterList &amp;List)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>InverseOperator</name>
      <anchorfile>classMLAPI_1_1InverseOperator.html</anchorfile>
      <anchor>a1971f46d3723242ef362ee38b77fd7df</anchor>
      <arglist>(const InverseOperator &amp;RHS)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~InverseOperator</name>
      <anchorfile>classMLAPI_1_1InverseOperator.html</anchorfile>
      <anchor>a796ddbbbcee78a17e5cca3b3f6ec9b47</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>InverseOperator &amp;</type>
      <name>operator=</name>
      <anchorfile>classMLAPI_1_1InverseOperator.html</anchorfile>
      <anchor>a08ece47e6aa30b3553fde7ae529a5653</anchor>
      <arglist>(const InverseOperator &amp;RHS)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Reshape</name>
      <anchorfile>classMLAPI_1_1InverseOperator.html</anchorfile>
      <anchor>a36422a033d75a4809af8563bccad9595</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Reshape</name>
      <anchorfile>classMLAPI_1_1InverseOperator.html</anchorfile>
      <anchor>a45da4959b73d0e5416a15de6c265433d</anchor>
      <arglist>(const Operator &amp;Op, const std::string Type)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Reshape</name>
      <anchorfile>classMLAPI_1_1InverseOperator.html</anchorfile>
      <anchor>a16c89d526165df98ea0de597ac486ab8</anchor>
      <arglist>(const Operator &amp;Op, const std::string Type, Teuchos::ParameterList &amp;List, Teuchos::ParameterList *pushlist=NULL)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Reshape</name>
      <anchorfile>classMLAPI_1_1InverseOperator.html</anchorfile>
      <anchor>a50ee5b320ec03873443da5151e7e617b</anchor>
      <arglist>(Ifpack_Preconditioner *prec, const Operator &amp;Op, const bool ownership)</arglist>
    </member>
    <member kind="function">
      <type>const Space</type>
      <name>GetOperatorRangeSpace</name>
      <anchorfile>classMLAPI_1_1InverseOperator.html</anchorfile>
      <anchor>a8e2cac342c8d210fae6b90d2a1f36b6c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Space</type>
      <name>GetOperatorDomainSpace</name>
      <anchorfile>classMLAPI_1_1InverseOperator.html</anchorfile>
      <anchor>a8219d99fe72c0aa713b6c8f1b5042c7d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Space</type>
      <name>GetRangeSpace</name>
      <anchorfile>classMLAPI_1_1InverseOperator.html</anchorfile>
      <anchor>ae179313eb16fcbbd2684660e0a2adff9</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Space</type>
      <name>GetDomainSpace</name>
      <anchorfile>classMLAPI_1_1InverseOperator.html</anchorfile>
      <anchor>ad744113609782d864f53b0b2c34329a9</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Teuchos::RefCountPtr&lt; Epetra_RowMatrix &gt;</type>
      <name>RCPRowMatrix</name>
      <anchorfile>classMLAPI_1_1InverseOperator.html</anchorfile>
      <anchor>a8f09f2b1cbfa38e861c3c6950618d151</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Epetra_RowMatrix *</type>
      <name>RowMatrix</name>
      <anchorfile>classMLAPI_1_1InverseOperator.html</anchorfile>
      <anchor>a163c57d973e95f407699a1d6328bf1c1</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Operator &amp;</type>
      <name>GetOperator</name>
      <anchorfile>classMLAPI_1_1InverseOperator.html</anchorfile>
      <anchor>ab7a4b95001bfb5e5f92cd1700cdddb1c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RefCountPtr&lt; Ifpack_Preconditioner &gt; &amp;</type>
      <name>GetRCPData</name>
      <anchorfile>classMLAPI_1_1InverseOperator.html</anchorfile>
      <anchor>abe1d99157ccd12272b6d06d821bc787b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RefCountPtr&lt; ML_Epetra::MultiLevelPreconditioner &gt; &amp;</type>
      <name>GetRCPMLPrec</name>
      <anchorfile>classMLAPI_1_1InverseOperator.html</anchorfile>
      <anchor>ae329b3c1b6d863b97ce5b70be1c856a4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const Teuchos::RefCountPtr&lt; Ifpack_Preconditioner &gt; &amp;</type>
      <name>GetRCPData</name>
      <anchorfile>classMLAPI_1_1InverseOperator.html</anchorfile>
      <anchor>a3001dfb6764d39b6998666ded1c23aec</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Teuchos::RefCountPtr&lt; ML_Epetra::MultiLevelPreconditioner &gt; &amp;</type>
      <name>GetRCPMLPrec</name>
      <anchorfile>classMLAPI_1_1InverseOperator.html</anchorfile>
      <anchor>ae4b0b196cf3333bbbde48a5ba93bcaf8</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Apply</name>
      <anchorfile>classMLAPI_1_1InverseOperator.html</anchorfile>
      <anchor>acb5f53543bdc84e0640ff59cc328fa21</anchor>
      <arglist>(const MultiVector &amp;x, MultiVector &amp;y) const </arglist>
    </member>
    <member kind="function">
      <type>MultiVector</type>
      <name>operator()</name>
      <anchorfile>classMLAPI_1_1InverseOperator.html</anchorfile>
      <anchor>a4ecf7ffdf0ad9256c7962fc4edaf7716</anchor>
      <arglist>(const MultiVector &amp;LHS)</arglist>
    </member>
    <member kind="function">
      <type>MultiVector</type>
      <name>operator()</name>
      <anchorfile>classMLAPI_1_1InverseOperator.html</anchorfile>
      <anchor>a63c28f2b0e7c2b27b3b2b09901ea2a88</anchor>
      <arglist>(const MultiVector &amp;LHS, const MultiVector &amp;RHS)</arglist>
    </member>
    <member kind="function">
      <type>std::ostream &amp;</type>
      <name>Print</name>
      <anchorfile>classMLAPI_1_1InverseOperator.html</anchorfile>
      <anchor>ae758d9df22e66b0e081cec021f9396d1</anchor>
      <arglist>(std::ostream &amp;os, const bool verbose=true) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>MLAPI::LinearCombinationAdd</name>
    <filename>classMLAPI_1_1LinearCombinationAdd.html</filename>
    <base>MLAPI::BaseLinearCombination</base>
    <member kind="function">
      <type>const Space</type>
      <name>GetVectorSpace</name>
      <anchorfile>classMLAPI_1_1LinearCombinationAdd.html</anchorfile>
      <anchor>adf0888e2a92a38cbe51dcc47125eb73b</anchor>
      <arglist>() const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>MLAPI::LinearCombinationMixed</name>
    <filename>classMLAPI_1_1LinearCombinationMixed.html</filename>
    <base>MLAPI::BaseLinearCombination</base>
    <member kind="function">
      <type>const Space</type>
      <name>GetVectorSpace</name>
      <anchorfile>classMLAPI_1_1LinearCombinationMixed.html</anchorfile>
      <anchor>ac1cb739818007e7128fe01359c3bc1d1</anchor>
      <arglist>() const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>MLAPI::LinearCombinationScaled</name>
    <filename>classMLAPI_1_1LinearCombinationScaled.html</filename>
    <base>MLAPI::BaseLinearCombination</base>
    <member kind="function">
      <type>const Space</type>
      <name>GetVectorSpace</name>
      <anchorfile>classMLAPI_1_1LinearCombinationScaled.html</anchorfile>
      <anchor>a4e9ae011e377229de8c31d019fc732fe</anchor>
      <arglist>() const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>MLAPI::LoadBalanceInverseOperator</name>
    <filename>classMLAPI_1_1LoadBalanceInverseOperator.html</filename>
    <base>MLAPI::InverseOperator</base>
    <member kind="function">
      <type></type>
      <name>LoadBalanceInverseOperator</name>
      <anchorfile>classMLAPI_1_1LoadBalanceInverseOperator.html</anchorfile>
      <anchor>ac6e7c4ea7558f3e4759e315771164300</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>LoadBalanceInverseOperator</name>
      <anchorfile>classMLAPI_1_1LoadBalanceInverseOperator.html</anchorfile>
      <anchor>ae290650974e2369d3eb7ce30c60c2afb</anchor>
      <arglist>(const LoadBalanceInverseOperator &amp;RHS)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~LoadBalanceInverseOperator</name>
      <anchorfile>classMLAPI_1_1LoadBalanceInverseOperator.html</anchorfile>
      <anchor>a81a56c6eb61da744de5bc536a0f81db3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>LoadBalanceInverseOperator &amp;</type>
      <name>operator=</name>
      <anchorfile>classMLAPI_1_1LoadBalanceInverseOperator.html</anchorfile>
      <anchor>a9a8c501a8c6a7f9819d4f299a1dac7a5</anchor>
      <arglist>(const LoadBalanceInverseOperator &amp;RHS)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Reshape</name>
      <anchorfile>classMLAPI_1_1LoadBalanceInverseOperator.html</anchorfile>
      <anchor>a52534f6aa12877979cb1df75be88e91a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Reshape</name>
      <anchorfile>classMLAPI_1_1LoadBalanceInverseOperator.html</anchorfile>
      <anchor>a50ca1f6b27ca7cd4e7329dcbbe7d2868</anchor>
      <arglist>(Ifpack_Preconditioner *prec, const LoadBalanceOperator &amp;Op, const bool ownership)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>GetParticipation</name>
      <anchorfile>classMLAPI_1_1LoadBalanceInverseOperator.html</anchorfile>
      <anchor>a7f3072cb1403a87bab8de2c79f4b4d0b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Space</type>
      <name>GetOperatorRangeSpace</name>
      <anchorfile>classMLAPI_1_1LoadBalanceInverseOperator.html</anchorfile>
      <anchor>aafa1dea07c2ead03b2d78748778f7df0</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Space</type>
      <name>GetOperatorDomainSpace</name>
      <anchorfile>classMLAPI_1_1LoadBalanceInverseOperator.html</anchorfile>
      <anchor>a607f6b32aafadb1ff5a29bce540f7b2c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Space</type>
      <name>GetRangeSpace</name>
      <anchorfile>classMLAPI_1_1LoadBalanceInverseOperator.html</anchorfile>
      <anchor>a8266f89bdd8d19a7c92540e7fce42504</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Space</type>
      <name>GetDomainSpace</name>
      <anchorfile>classMLAPI_1_1LoadBalanceInverseOperator.html</anchorfile>
      <anchor>a8f2c526f5f4b7f22f16068e80a1fca10</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Teuchos::RCP&lt; Epetra_RowMatrix &gt;</type>
      <name>RCPRowMatrix</name>
      <anchorfile>classMLAPI_1_1LoadBalanceInverseOperator.html</anchorfile>
      <anchor>a8136dc1713ef67513dc08d66f7cccaf9</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Epetra_RowMatrix *</type>
      <name>RowMatrix</name>
      <anchorfile>classMLAPI_1_1LoadBalanceInverseOperator.html</anchorfile>
      <anchor>ae53077bbb959a6f9180fe2d6218f15ba</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const LoadBalanceOperator &amp;</type>
      <name>GetOperator</name>
      <anchorfile>classMLAPI_1_1LoadBalanceInverseOperator.html</anchorfile>
      <anchor>a031b5c10dd4f18a351ffa8c7e788db02</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; Ifpack_Preconditioner &gt; &amp;</type>
      <name>GetRCPData</name>
      <anchorfile>classMLAPI_1_1LoadBalanceInverseOperator.html</anchorfile>
      <anchor>a2e7e5c6f189941537a978af76651b2d6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const Teuchos::RCP&lt; Ifpack_Preconditioner &gt; &amp;</type>
      <name>GetRCPData</name>
      <anchorfile>classMLAPI_1_1LoadBalanceInverseOperator.html</anchorfile>
      <anchor>a61afd9f2a106ed9d2785a90ffbfd6b9f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Apply</name>
      <anchorfile>classMLAPI_1_1LoadBalanceInverseOperator.html</anchorfile>
      <anchor>a109e6ec1a8e1cbecab4aa536b0cfdcd2</anchor>
      <arglist>(const MultiVector &amp;x, MultiVector &amp;y) const </arglist>
    </member>
    <member kind="function">
      <type>MultiVector</type>
      <name>operator()</name>
      <anchorfile>classMLAPI_1_1LoadBalanceInverseOperator.html</anchorfile>
      <anchor>acc9253a3598d93916dcae5eaed11c621</anchor>
      <arglist>(const MultiVector &amp;LHS)</arglist>
    </member>
    <member kind="function">
      <type>MultiVector</type>
      <name>operator()</name>
      <anchorfile>classMLAPI_1_1LoadBalanceInverseOperator.html</anchorfile>
      <anchor>ad49f77847afc13ffdcee8c04f5e7f2e1</anchor>
      <arglist>(const MultiVector &amp;LHS, const MultiVector &amp;RHS)</arglist>
    </member>
    <member kind="function">
      <type>std::ostream &amp;</type>
      <name>Print</name>
      <anchorfile>classMLAPI_1_1LoadBalanceInverseOperator.html</anchorfile>
      <anchor>a5fa59b7251559e484c28fe0f393b6faf</anchor>
      <arglist>(std::ostream &amp;os, const bool verbose=true) const </arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>LoadBalanceInverseOperator</name>
      <anchorfile>classMLAPI_1_1LoadBalanceInverseOperator.html</anchorfile>
      <anchor>ac6e7c4ea7558f3e4759e315771164300</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>LoadBalanceInverseOperator</name>
      <anchorfile>classMLAPI_1_1LoadBalanceInverseOperator.html</anchorfile>
      <anchor>ae290650974e2369d3eb7ce30c60c2afb</anchor>
      <arglist>(const LoadBalanceInverseOperator &amp;RHS)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~LoadBalanceInverseOperator</name>
      <anchorfile>classMLAPI_1_1LoadBalanceInverseOperator.html</anchorfile>
      <anchor>a81a56c6eb61da744de5bc536a0f81db3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>LoadBalanceInverseOperator &amp;</type>
      <name>operator=</name>
      <anchorfile>classMLAPI_1_1LoadBalanceInverseOperator.html</anchorfile>
      <anchor>a9a8c501a8c6a7f9819d4f299a1dac7a5</anchor>
      <arglist>(const LoadBalanceInverseOperator &amp;RHS)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Reshape</name>
      <anchorfile>classMLAPI_1_1LoadBalanceInverseOperator.html</anchorfile>
      <anchor>a52534f6aa12877979cb1df75be88e91a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Reshape</name>
      <anchorfile>classMLAPI_1_1LoadBalanceInverseOperator.html</anchorfile>
      <anchor>a50ca1f6b27ca7cd4e7329dcbbe7d2868</anchor>
      <arglist>(Ifpack_Preconditioner *prec, const LoadBalanceOperator &amp;Op, const bool ownership)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>GetParticipation</name>
      <anchorfile>classMLAPI_1_1LoadBalanceInverseOperator.html</anchorfile>
      <anchor>a7f3072cb1403a87bab8de2c79f4b4d0b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Space</type>
      <name>GetOperatorRangeSpace</name>
      <anchorfile>classMLAPI_1_1LoadBalanceInverseOperator.html</anchorfile>
      <anchor>aafa1dea07c2ead03b2d78748778f7df0</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Space</type>
      <name>GetOperatorDomainSpace</name>
      <anchorfile>classMLAPI_1_1LoadBalanceInverseOperator.html</anchorfile>
      <anchor>a607f6b32aafadb1ff5a29bce540f7b2c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Space</type>
      <name>GetRangeSpace</name>
      <anchorfile>classMLAPI_1_1LoadBalanceInverseOperator.html</anchorfile>
      <anchor>a8266f89bdd8d19a7c92540e7fce42504</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Space</type>
      <name>GetDomainSpace</name>
      <anchorfile>classMLAPI_1_1LoadBalanceInverseOperator.html</anchorfile>
      <anchor>a8f2c526f5f4b7f22f16068e80a1fca10</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Teuchos::RCP&lt; Epetra_RowMatrix &gt;</type>
      <name>RCPRowMatrix</name>
      <anchorfile>classMLAPI_1_1LoadBalanceInverseOperator.html</anchorfile>
      <anchor>a8136dc1713ef67513dc08d66f7cccaf9</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Epetra_RowMatrix *</type>
      <name>RowMatrix</name>
      <anchorfile>classMLAPI_1_1LoadBalanceInverseOperator.html</anchorfile>
      <anchor>ae53077bbb959a6f9180fe2d6218f15ba</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const LoadBalanceOperator &amp;</type>
      <name>GetOperator</name>
      <anchorfile>classMLAPI_1_1LoadBalanceInverseOperator.html</anchorfile>
      <anchor>a031b5c10dd4f18a351ffa8c7e788db02</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; Ifpack_Preconditioner &gt; &amp;</type>
      <name>GetRCPData</name>
      <anchorfile>classMLAPI_1_1LoadBalanceInverseOperator.html</anchorfile>
      <anchor>a2e7e5c6f189941537a978af76651b2d6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const Teuchos::RCP&lt; Ifpack_Preconditioner &gt; &amp;</type>
      <name>GetRCPData</name>
      <anchorfile>classMLAPI_1_1LoadBalanceInverseOperator.html</anchorfile>
      <anchor>a61afd9f2a106ed9d2785a90ffbfd6b9f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Apply</name>
      <anchorfile>classMLAPI_1_1LoadBalanceInverseOperator.html</anchorfile>
      <anchor>a109e6ec1a8e1cbecab4aa536b0cfdcd2</anchor>
      <arglist>(const MultiVector &amp;x, MultiVector &amp;y) const </arglist>
    </member>
    <member kind="function">
      <type>MultiVector</type>
      <name>operator()</name>
      <anchorfile>classMLAPI_1_1LoadBalanceInverseOperator.html</anchorfile>
      <anchor>acc9253a3598d93916dcae5eaed11c621</anchor>
      <arglist>(const MultiVector &amp;LHS)</arglist>
    </member>
    <member kind="function">
      <type>MultiVector</type>
      <name>operator()</name>
      <anchorfile>classMLAPI_1_1LoadBalanceInverseOperator.html</anchorfile>
      <anchor>ad49f77847afc13ffdcee8c04f5e7f2e1</anchor>
      <arglist>(const MultiVector &amp;LHS, const MultiVector &amp;RHS)</arglist>
    </member>
    <member kind="function">
      <type>std::ostream &amp;</type>
      <name>Print</name>
      <anchorfile>classMLAPI_1_1LoadBalanceInverseOperator.html</anchorfile>
      <anchor>a5fa59b7251559e484c28fe0f393b6faf</anchor>
      <arglist>(std::ostream &amp;os, const bool verbose=true) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>MLAPI::LoadBalanceOperator</name>
    <filename>classMLAPI_1_1LoadBalanceOperator.html</filename>
    <base>MLAPI::Operator</base>
    <member kind="function">
      <type></type>
      <name>LoadBalanceOperator</name>
      <anchorfile>classMLAPI_1_1LoadBalanceOperator.html</anchorfile>
      <anchor>a4994ce0ff27700277c7f20eeaa91074e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>LoadBalanceOperator</name>
      <anchorfile>classMLAPI_1_1LoadBalanceOperator.html</anchorfile>
      <anchor>a91232f688d955775784e8d125703af73</anchor>
      <arglist>(const Space &amp;DomainSpace, const Space &amp;RangeSpace, ML_Operator *Op, bool Ownership=true, Teuchos::RefCountPtr&lt; ML_Operator_Box &gt; AuxOp=Teuchos::null)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>LoadBalanceOperator</name>
      <anchorfile>classMLAPI_1_1LoadBalanceOperator.html</anchorfile>
      <anchor>a401b0675c7eb9b332e20d5c40de346a0</anchor>
      <arglist>(const Space &amp;DomainSpace, const Space &amp;RangeSpace, Epetra_RowMatrix *Matrix, bool Ownership=true, Teuchos::RefCountPtr&lt; ML_Operator_Box &gt; AuxOp=Teuchos::null)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>LoadBalanceOperator</name>
      <anchorfile>classMLAPI_1_1LoadBalanceOperator.html</anchorfile>
      <anchor>a924911698696796285f87b07ae84e6d4</anchor>
      <arglist>(const LoadBalanceOperator &amp;RHS)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~LoadBalanceOperator</name>
      <anchorfile>classMLAPI_1_1LoadBalanceOperator.html</anchorfile>
      <anchor>a6c84af958dcfba871ab1b58afc260d98</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Reshape</name>
      <anchorfile>classMLAPI_1_1LoadBalanceOperator.html</anchorfile>
      <anchor>aa5f6a952cbbcf05257ac02b1da44f0c2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Reshape</name>
      <anchorfile>classMLAPI_1_1LoadBalanceOperator.html</anchorfile>
      <anchor>a95b5eeb933e9ad6ab8e7bab898497398</anchor>
      <arglist>(const Space &amp;DomainSpace, const Space &amp;RangeSpace, ML_Operator *Op, bool Ownership=true, Teuchos::RefCountPtr&lt; ML_Operator_Box &gt; AuxOp=Teuchos::null)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Reshape</name>
      <anchorfile>classMLAPI_1_1LoadBalanceOperator.html</anchorfile>
      <anchor>a6aada11a4e2e432dd99e5fb2faa14e4b</anchor>
      <arglist>(const Space &amp;DomainSpace, const Space &amp;RangeSpace, Epetra_RowMatrix *Matrix, bool Ownership=true, Teuchos::RCP&lt; ML_Operator_Box &gt; AuxOp=Teuchos::null)</arglist>
    </member>
    <member kind="function">
      <type>LoadBalanceOperator &amp;</type>
      <name>operator=</name>
      <anchorfile>classMLAPI_1_1LoadBalanceOperator.html</anchorfile>
      <anchor>aab4c10fa2684b186537f13d33d97d5f3</anchor>
      <arglist>(const LoadBalanceOperator &amp;RHS)</arglist>
    </member>
    <member kind="function">
      <type>Operator &amp;</type>
      <name>operator=</name>
      <anchorfile>classMLAPI_1_1LoadBalanceOperator.html</anchorfile>
      <anchor>a15fbbd91b9259522b7cf4a6a280f088b</anchor>
      <arglist>(const std::string &amp;Label)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>GetParticipation</name>
      <anchorfile>classMLAPI_1_1LoadBalanceOperator.html</anchorfile>
      <anchor>a75974ae485dc73084216f8c0f08c968b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Space</type>
      <name>GetOperatorDomainSpace</name>
      <anchorfile>classMLAPI_1_1LoadBalanceOperator.html</anchorfile>
      <anchor>af3a9f6fca7be727e42667396dfe1cf33</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Space</type>
      <name>GetOperatorRangeSpace</name>
      <anchorfile>classMLAPI_1_1LoadBalanceOperator.html</anchorfile>
      <anchor>adbab9598d573da9f2d2dfe0cf5bfa769</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Space</type>
      <name>GetDomainSpace</name>
      <anchorfile>classMLAPI_1_1LoadBalanceOperator.html</anchorfile>
      <anchor>a1006b6cfc375dd770abce9d42b0dead8</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Space</type>
      <name>GetRangeSpace</name>
      <anchorfile>classMLAPI_1_1LoadBalanceOperator.html</anchorfile>
      <anchor>abba91899a30a269224ad7d28f677562d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Space</type>
      <name>GetColumnSpace</name>
      <anchorfile>classMLAPI_1_1LoadBalanceOperator.html</anchorfile>
      <anchor>acd9aba62c858eac03b04cef78871145a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetNumGlobalRows</name>
      <anchorfile>classMLAPI_1_1LoadBalanceOperator.html</anchorfile>
      <anchor>a8c4f4a0d316588d0f31c2e32681405cd</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetNumMyRows</name>
      <anchorfile>classMLAPI_1_1LoadBalanceOperator.html</anchorfile>
      <anchor>a427960a8870cb974ca6eb5cea6df95e5</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetNumGlobalCols</name>
      <anchorfile>classMLAPI_1_1LoadBalanceOperator.html</anchorfile>
      <anchor>abe4b9951eb1dbcc72a674d8d7e999e87</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetNumMyCols</name>
      <anchorfile>classMLAPI_1_1LoadBalanceOperator.html</anchorfile>
      <anchor>a1e796d8e1077f6d76105fa0cda4d293a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetNumGlobalNonzeros</name>
      <anchorfile>classMLAPI_1_1LoadBalanceOperator.html</anchorfile>
      <anchor>a979ad2dd6706b5d0be3e5c21817ab22a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetNumMyNonzeros</name>
      <anchorfile>classMLAPI_1_1LoadBalanceOperator.html</anchorfile>
      <anchor>a682f6eded3bc6733e90bdc7d7d1d67e4</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_RowMatrix *</type>
      <name>GetRowMatrix</name>
      <anchorfile>classMLAPI_1_1LoadBalanceOperator.html</anchorfile>
      <anchor>a184edc0d95a8b60d7e2a5e9374ccda67</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>ML_Operator *</type>
      <name>GetML_Operator</name>
      <anchorfile>classMLAPI_1_1LoadBalanceOperator.html</anchorfile>
      <anchor>a72c18ba98ac7d4950ed20f8bc575c1d8</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Teuchos::RCP&lt; ML_Operator_Box &gt; &amp;</type>
      <name>GetRCPOperatorBox</name>
      <anchorfile>classMLAPI_1_1LoadBalanceOperator.html</anchorfile>
      <anchor>ae4f63ec46e94eaec2008998690657d33</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Teuchos::RCP&lt; ML_Operator_Box &gt; &amp;</type>
      <name>GetRCPAuxOperatorBox</name>
      <anchorfile>classMLAPI_1_1LoadBalanceOperator.html</anchorfile>
      <anchor>a3b881cc2097ca5362ddaf60897eb18be</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Teuchos::RCP&lt; Epetra_RowMatrix &gt; &amp;</type>
      <name>GetRCPRowMatrix</name>
      <anchorfile>classMLAPI_1_1LoadBalanceOperator.html</anchorfile>
      <anchor>aabe2692af02ce4cd64af0c0e6396662a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetGRID</name>
      <anchorfile>classMLAPI_1_1LoadBalanceOperator.html</anchorfile>
      <anchor>a7cdaefe0882370d23c1b4da4b37bab88</anchor>
      <arglist>(const int LRID) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetGCID</name>
      <anchorfile>classMLAPI_1_1LoadBalanceOperator.html</anchorfile>
      <anchor>adc3af1a1af4b9c1adbe0d848bac93446</anchor>
      <arglist>(const int LCID) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Apply</name>
      <anchorfile>classMLAPI_1_1LoadBalanceOperator.html</anchorfile>
      <anchor>ad3b5ebe2f8cbe113761ecff191d9c757</anchor>
      <arglist>(const MultiVector &amp;X, MultiVector &amp;Y) const </arglist>
    </member>
    <member kind="function">
      <type>std::ostream &amp;</type>
      <name>Print</name>
      <anchorfile>classMLAPI_1_1LoadBalanceOperator.html</anchorfile>
      <anchor>a1b2b74db56a03473fc37b528db67252a</anchor>
      <arglist>(std::ostream &amp;os, const bool verbose=true) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>BuildColumnSpace</name>
      <anchorfile>classMLAPI_1_1LoadBalanceOperator.html</anchorfile>
      <anchor>abc05743cb8a47385abd90a9c0fa1db75</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>LoadBalanceOperator</name>
      <anchorfile>classMLAPI_1_1LoadBalanceOperator.html</anchorfile>
      <anchor>a4994ce0ff27700277c7f20eeaa91074e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>LoadBalanceOperator</name>
      <anchorfile>classMLAPI_1_1LoadBalanceOperator.html</anchorfile>
      <anchor>a91232f688d955775784e8d125703af73</anchor>
      <arglist>(const Space &amp;DomainSpace, const Space &amp;RangeSpace, ML_Operator *Op, bool Ownership=true, Teuchos::RefCountPtr&lt; ML_Operator_Box &gt; AuxOp=Teuchos::null)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>LoadBalanceOperator</name>
      <anchorfile>classMLAPI_1_1LoadBalanceOperator.html</anchorfile>
      <anchor>a401b0675c7eb9b332e20d5c40de346a0</anchor>
      <arglist>(const Space &amp;DomainSpace, const Space &amp;RangeSpace, Epetra_RowMatrix *Matrix, bool Ownership=true, Teuchos::RefCountPtr&lt; ML_Operator_Box &gt; AuxOp=Teuchos::null)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>LoadBalanceOperator</name>
      <anchorfile>classMLAPI_1_1LoadBalanceOperator.html</anchorfile>
      <anchor>a924911698696796285f87b07ae84e6d4</anchor>
      <arglist>(const LoadBalanceOperator &amp;RHS)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~LoadBalanceOperator</name>
      <anchorfile>classMLAPI_1_1LoadBalanceOperator.html</anchorfile>
      <anchor>a6c84af958dcfba871ab1b58afc260d98</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Reshape</name>
      <anchorfile>classMLAPI_1_1LoadBalanceOperator.html</anchorfile>
      <anchor>aa5f6a952cbbcf05257ac02b1da44f0c2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Reshape</name>
      <anchorfile>classMLAPI_1_1LoadBalanceOperator.html</anchorfile>
      <anchor>a95b5eeb933e9ad6ab8e7bab898497398</anchor>
      <arglist>(const Space &amp;DomainSpace, const Space &amp;RangeSpace, ML_Operator *Op, bool Ownership=true, Teuchos::RefCountPtr&lt; ML_Operator_Box &gt; AuxOp=Teuchos::null)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Reshape</name>
      <anchorfile>classMLAPI_1_1LoadBalanceOperator.html</anchorfile>
      <anchor>a6aada11a4e2e432dd99e5fb2faa14e4b</anchor>
      <arglist>(const Space &amp;DomainSpace, const Space &amp;RangeSpace, Epetra_RowMatrix *Matrix, bool Ownership=true, Teuchos::RCP&lt; ML_Operator_Box &gt; AuxOp=Teuchos::null)</arglist>
    </member>
    <member kind="function">
      <type>LoadBalanceOperator &amp;</type>
      <name>operator=</name>
      <anchorfile>classMLAPI_1_1LoadBalanceOperator.html</anchorfile>
      <anchor>aab4c10fa2684b186537f13d33d97d5f3</anchor>
      <arglist>(const LoadBalanceOperator &amp;RHS)</arglist>
    </member>
    <member kind="function">
      <type>Operator &amp;</type>
      <name>operator=</name>
      <anchorfile>classMLAPI_1_1LoadBalanceOperator.html</anchorfile>
      <anchor>a15fbbd91b9259522b7cf4a6a280f088b</anchor>
      <arglist>(const std::string &amp;Label)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>GetParticipation</name>
      <anchorfile>classMLAPI_1_1LoadBalanceOperator.html</anchorfile>
      <anchor>a75974ae485dc73084216f8c0f08c968b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Space</type>
      <name>GetOperatorDomainSpace</name>
      <anchorfile>classMLAPI_1_1LoadBalanceOperator.html</anchorfile>
      <anchor>af3a9f6fca7be727e42667396dfe1cf33</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Space</type>
      <name>GetOperatorRangeSpace</name>
      <anchorfile>classMLAPI_1_1LoadBalanceOperator.html</anchorfile>
      <anchor>adbab9598d573da9f2d2dfe0cf5bfa769</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Space</type>
      <name>GetDomainSpace</name>
      <anchorfile>classMLAPI_1_1LoadBalanceOperator.html</anchorfile>
      <anchor>a1006b6cfc375dd770abce9d42b0dead8</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Space</type>
      <name>GetRangeSpace</name>
      <anchorfile>classMLAPI_1_1LoadBalanceOperator.html</anchorfile>
      <anchor>abba91899a30a269224ad7d28f677562d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Space</type>
      <name>GetColumnSpace</name>
      <anchorfile>classMLAPI_1_1LoadBalanceOperator.html</anchorfile>
      <anchor>acd9aba62c858eac03b04cef78871145a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetNumGlobalRows</name>
      <anchorfile>classMLAPI_1_1LoadBalanceOperator.html</anchorfile>
      <anchor>a8c4f4a0d316588d0f31c2e32681405cd</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetNumMyRows</name>
      <anchorfile>classMLAPI_1_1LoadBalanceOperator.html</anchorfile>
      <anchor>a427960a8870cb974ca6eb5cea6df95e5</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetNumGlobalCols</name>
      <anchorfile>classMLAPI_1_1LoadBalanceOperator.html</anchorfile>
      <anchor>abe4b9951eb1dbcc72a674d8d7e999e87</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetNumMyCols</name>
      <anchorfile>classMLAPI_1_1LoadBalanceOperator.html</anchorfile>
      <anchor>a1e796d8e1077f6d76105fa0cda4d293a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetNumGlobalNonzeros</name>
      <anchorfile>classMLAPI_1_1LoadBalanceOperator.html</anchorfile>
      <anchor>a979ad2dd6706b5d0be3e5c21817ab22a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetNumMyNonzeros</name>
      <anchorfile>classMLAPI_1_1LoadBalanceOperator.html</anchorfile>
      <anchor>a682f6eded3bc6733e90bdc7d7d1d67e4</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_RowMatrix *</type>
      <name>GetRowMatrix</name>
      <anchorfile>classMLAPI_1_1LoadBalanceOperator.html</anchorfile>
      <anchor>a184edc0d95a8b60d7e2a5e9374ccda67</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>ML_Operator *</type>
      <name>GetML_Operator</name>
      <anchorfile>classMLAPI_1_1LoadBalanceOperator.html</anchorfile>
      <anchor>a72c18ba98ac7d4950ed20f8bc575c1d8</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Teuchos::RCP&lt; ML_Operator_Box &gt; &amp;</type>
      <name>GetRCPOperatorBox</name>
      <anchorfile>classMLAPI_1_1LoadBalanceOperator.html</anchorfile>
      <anchor>ae4f63ec46e94eaec2008998690657d33</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Teuchos::RCP&lt; ML_Operator_Box &gt; &amp;</type>
      <name>GetRCPAuxOperatorBox</name>
      <anchorfile>classMLAPI_1_1LoadBalanceOperator.html</anchorfile>
      <anchor>a3b881cc2097ca5362ddaf60897eb18be</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Teuchos::RCP&lt; Epetra_RowMatrix &gt; &amp;</type>
      <name>GetRCPRowMatrix</name>
      <anchorfile>classMLAPI_1_1LoadBalanceOperator.html</anchorfile>
      <anchor>aabe2692af02ce4cd64af0c0e6396662a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetGRID</name>
      <anchorfile>classMLAPI_1_1LoadBalanceOperator.html</anchorfile>
      <anchor>a7cdaefe0882370d23c1b4da4b37bab88</anchor>
      <arglist>(const int LRID) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetGCID</name>
      <anchorfile>classMLAPI_1_1LoadBalanceOperator.html</anchorfile>
      <anchor>adc3af1a1af4b9c1adbe0d848bac93446</anchor>
      <arglist>(const int LCID) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Apply</name>
      <anchorfile>classMLAPI_1_1LoadBalanceOperator.html</anchorfile>
      <anchor>ad3b5ebe2f8cbe113761ecff191d9c757</anchor>
      <arglist>(const MultiVector &amp;X, MultiVector &amp;Y) const </arglist>
    </member>
    <member kind="function">
      <type>std::ostream &amp;</type>
      <name>Print</name>
      <anchorfile>classMLAPI_1_1LoadBalanceOperator.html</anchorfile>
      <anchor>a1b2b74db56a03473fc37b528db67252a</anchor>
      <arglist>(std::ostream &amp;os, const bool verbose=true) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>BuildColumnSpace</name>
      <anchorfile>classMLAPI_1_1LoadBalanceOperator.html</anchorfile>
      <anchor>abc05743cb8a47385abd90a9c0fa1db75</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>MLAPI::MATLABStream</name>
    <filename>classMLAPI_1_1MATLABStream.html</filename>
    <member kind="function">
      <type></type>
      <name>MATLABStream</name>
      <anchorfile>classMLAPI_1_1MATLABStream.html</anchorfile>
      <anchor>a62dc290b5f400e9db919dba14ff6dd5b</anchor>
      <arglist>(const std::string &amp;FileName, bool UseSparse=true)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~MATLABStream</name>
      <anchorfile>classMLAPI_1_1MATLABStream.html</anchorfile>
      <anchor>af62b6f0645442d7377ce0216692eb07b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>MATLABStream &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>classMLAPI_1_1MATLABStream.html</anchorfile>
      <anchor>afd246d424e480dfdf1008ce4ea08fbc8</anchor>
      <arglist>(const int obj)</arglist>
    </member>
    <member kind="function">
      <type>MATLABStream &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>classMLAPI_1_1MATLABStream.html</anchorfile>
      <anchor>a4756c2731ac671f8b1405b1dca62b6ae</anchor>
      <arglist>(const double obj)</arglist>
    </member>
    <member kind="function">
      <type>MATLABStream &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>classMLAPI_1_1MATLABStream.html</anchorfile>
      <anchor>a86e91be6065341d147f63c9c0af04e85</anchor>
      <arglist>(const std::string obj)</arglist>
    </member>
    <member kind="function">
      <type>MATLABStream &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>classMLAPI_1_1MATLABStream.html</anchorfile>
      <anchor>ae47c207b66b16fcd87d88c01efc9609d</anchor>
      <arglist>(const Operator &amp;obj)</arglist>
    </member>
    <member kind="function">
      <type>MATLABStream &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>classMLAPI_1_1MATLABStream.html</anchorfile>
      <anchor>af50cd40e92f131a5061bdbd927df478e</anchor>
      <arglist>(const MultiVector &amp;obj)</arglist>
    </member>
    <member kind="function">
      <type>MATLABStream &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>classMLAPI_1_1MATLABStream.html</anchorfile>
      <anchor>a8c9a26d571ec034e68014b6310ad7601</anchor>
      <arglist>(const Space &amp;obj)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>GetUseSparse</name>
      <anchorfile>classMLAPI_1_1MATLABStream.html</anchorfile>
      <anchor>a10f9e9b2976d2585dd3f5792ccf378e6</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetUseSparse</name>
      <anchorfile>classMLAPI_1_1MATLABStream.html</anchorfile>
      <anchor>a646ad2c901274d16ea097845809a1109</anchor>
      <arglist>(const bool UseSparse)</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>GetFileName</name>
      <anchorfile>classMLAPI_1_1MATLABStream.html</anchorfile>
      <anchor>a2d46d25c812770a0581e7fbf0b036b2e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>MATLABStream</name>
      <anchorfile>classMLAPI_1_1MATLABStream.html</anchorfile>
      <anchor>a62dc290b5f400e9db919dba14ff6dd5b</anchor>
      <arglist>(const std::string &amp;FileName, bool UseSparse=true)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~MATLABStream</name>
      <anchorfile>classMLAPI_1_1MATLABStream.html</anchorfile>
      <anchor>af62b6f0645442d7377ce0216692eb07b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>MATLABStream &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>classMLAPI_1_1MATLABStream.html</anchorfile>
      <anchor>afd246d424e480dfdf1008ce4ea08fbc8</anchor>
      <arglist>(const int obj)</arglist>
    </member>
    <member kind="function">
      <type>MATLABStream &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>classMLAPI_1_1MATLABStream.html</anchorfile>
      <anchor>a4756c2731ac671f8b1405b1dca62b6ae</anchor>
      <arglist>(const double obj)</arglist>
    </member>
    <member kind="function">
      <type>MATLABStream &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>classMLAPI_1_1MATLABStream.html</anchorfile>
      <anchor>a86e91be6065341d147f63c9c0af04e85</anchor>
      <arglist>(const std::string obj)</arglist>
    </member>
    <member kind="function">
      <type>MATLABStream &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>classMLAPI_1_1MATLABStream.html</anchorfile>
      <anchor>ae47c207b66b16fcd87d88c01efc9609d</anchor>
      <arglist>(const Operator &amp;obj)</arglist>
    </member>
    <member kind="function">
      <type>MATLABStream &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>classMLAPI_1_1MATLABStream.html</anchorfile>
      <anchor>af50cd40e92f131a5061bdbd927df478e</anchor>
      <arglist>(const MultiVector &amp;obj)</arglist>
    </member>
    <member kind="function">
      <type>MATLABStream &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>classMLAPI_1_1MATLABStream.html</anchorfile>
      <anchor>a8c9a26d571ec034e68014b6310ad7601</anchor>
      <arglist>(const Space &amp;obj)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>GetUseSparse</name>
      <anchorfile>classMLAPI_1_1MATLABStream.html</anchorfile>
      <anchor>a10f9e9b2976d2585dd3f5792ccf378e6</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetUseSparse</name>
      <anchorfile>classMLAPI_1_1MATLABStream.html</anchorfile>
      <anchor>a646ad2c901274d16ea097845809a1109</anchor>
      <arglist>(const bool UseSparse)</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>GetFileName</name>
      <anchorfile>classMLAPI_1_1MATLABStream.html</anchorfile>
      <anchor>a2d46d25c812770a0581e7fbf0b036b2e</anchor>
      <arglist>() const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>MatrixFreePreconditioner</name>
    <filename>classMatrixFreePreconditioner.html</filename>
  </compound>
  <compound kind="class">
    <name>ML_Epetra::MatrixFreePreconditioner</name>
    <filename>classML__Epetra_1_1MatrixFreePreconditioner.html</filename>
    <base>Epetra_Operator</base>
    <member kind="function">
      <type></type>
      <name>MatrixFreePreconditioner</name>
      <anchorfile>classML__Epetra_1_1MatrixFreePreconditioner.html</anchorfile>
      <anchor>acf4dedf631cbc70820d81d1422849a1b</anchor>
      <arglist>(const Epetra_Operator &amp;Operator, const Epetra_CrsGraph &amp;Graph, Epetra_MultiVector &amp;NullSpace, const Epetra_Vector &amp;PointDiagonal, Teuchos::ParameterList &amp;List)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~MatrixFreePreconditioner</name>
      <anchorfile>classML__Epetra_1_1MatrixFreePreconditioner.html</anchorfile>
      <anchor>a8b5e802ba9df0dee119cb81c9f93f7c7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetUseTranspose</name>
      <anchorfile>classML__Epetra_1_1MatrixFreePreconditioner.html</anchorfile>
      <anchor>a345c5ded8f6e48172b38507b204c46dd</anchor>
      <arglist>(bool UseTranspose)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Apply</name>
      <anchorfile>classML__Epetra_1_1MatrixFreePreconditioner.html</anchorfile>
      <anchor>a0fbd834314681644ff503304b995644d</anchor>
      <arglist>(const Epetra_MultiVector &amp;X, Epetra_MultiVector &amp;Y) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ApplyInverse</name>
      <anchorfile>classML__Epetra_1_1MatrixFreePreconditioner.html</anchorfile>
      <anchor>a7b136f906ac662228e4fad926f212207</anchor>
      <arglist>(const Epetra_MultiVector &amp;X, Epetra_MultiVector &amp;Y) const </arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>NormInf</name>
      <anchorfile>classML__Epetra_1_1MatrixFreePreconditioner.html</anchorfile>
      <anchor>a973197e8eda5a2d8d07146b7ecf575eb</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const char *</type>
      <name>Label</name>
      <anchorfile>classML__Epetra_1_1MatrixFreePreconditioner.html</anchorfile>
      <anchor>a9b5b90b67fb0c9fce59cfdc6e251c8bc</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>UseTranspose</name>
      <anchorfile>classML__Epetra_1_1MatrixFreePreconditioner.html</anchorfile>
      <anchor>a5339042fe095d25112de6aba335275ab</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>HasNormInf</name>
      <anchorfile>classML__Epetra_1_1MatrixFreePreconditioner.html</anchorfile>
      <anchor>a8ceeff9b087c4db52a2a7445995b30b3</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_Comm &amp;</type>
      <name>Comm</name>
      <anchorfile>classML__Epetra_1_1MatrixFreePreconditioner.html</anchorfile>
      <anchor>afbf036fc1c8f41e974584d4f9e85da94</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_Map &amp;</type>
      <name>OperatorDomainMap</name>
      <anchorfile>classML__Epetra_1_1MatrixFreePreconditioner.html</anchorfile>
      <anchor>aabc20823ba9f86a9d2d08d3eddf38055</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_Map &amp;</type>
      <name>OperatorRangeMap</name>
      <anchorfile>classML__Epetra_1_1MatrixFreePreconditioner.html</anchorfile>
      <anchor>a4bd95452e397e409962b882439fe5c19</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_RowMatrix &amp;</type>
      <name>C</name>
      <anchorfile>classML__Epetra_1_1MatrixFreePreconditioner.html</anchorfile>
      <anchor>a83981bd4a76b38518fdab36d17bd1c7a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_CrsMatrix &amp;</type>
      <name>R</name>
      <anchorfile>classML__Epetra_1_1MatrixFreePreconditioner.html</anchorfile>
      <anchor>ac3cf0b983bb5e9531d1004b67549dba0</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>ML_Comm *</type>
      <name>Comm_ML</name>
      <anchorfile>classML__Epetra_1_1MatrixFreePreconditioner.html</anchorfile>
      <anchor>a089de4a06e2653e33aafe421a6e549f1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>MyPID</name>
      <anchorfile>classML__Epetra_1_1MatrixFreePreconditioner.html</anchorfile>
      <anchor>ab71746c98a60775971bdfdc043f19be7</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumProc</name>
      <anchorfile>classML__Epetra_1_1MatrixFreePreconditioner.html</anchorfile>
      <anchor>a04e84c4e03b223466c18d467125eb1f0</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>IsComputed</name>
      <anchorfile>classML__Epetra_1_1MatrixFreePreconditioner.html</anchorfile>
      <anchor>a3c7532abe7a11d2fba6ed67ee284232e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>TotalCPUTime</name>
      <anchorfile>classML__Epetra_1_1MatrixFreePreconditioner.html</anchorfile>
      <anchor>ad756892f437177a01ad0177fc4424d69</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>MatrixFreePreconditioner</name>
      <anchorfile>classML__Epetra_1_1MatrixFreePreconditioner.html</anchorfile>
      <anchor>acf4dedf631cbc70820d81d1422849a1b</anchor>
      <arglist>(const Epetra_Operator &amp;Operator, const Epetra_CrsGraph &amp;Graph, Epetra_MultiVector &amp;NullSpace, const Epetra_Vector &amp;PointDiagonal, Teuchos::ParameterList &amp;List)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~MatrixFreePreconditioner</name>
      <anchorfile>classML__Epetra_1_1MatrixFreePreconditioner.html</anchorfile>
      <anchor>a8b5e802ba9df0dee119cb81c9f93f7c7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetUseTranspose</name>
      <anchorfile>classML__Epetra_1_1MatrixFreePreconditioner.html</anchorfile>
      <anchor>a345c5ded8f6e48172b38507b204c46dd</anchor>
      <arglist>(bool UseTranspose)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Apply</name>
      <anchorfile>classML__Epetra_1_1MatrixFreePreconditioner.html</anchorfile>
      <anchor>a0fbd834314681644ff503304b995644d</anchor>
      <arglist>(const Epetra_MultiVector &amp;X, Epetra_MultiVector &amp;Y) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ApplyInverse</name>
      <anchorfile>classML__Epetra_1_1MatrixFreePreconditioner.html</anchorfile>
      <anchor>a7b136f906ac662228e4fad926f212207</anchor>
      <arglist>(const Epetra_MultiVector &amp;X, Epetra_MultiVector &amp;Y) const </arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>NormInf</name>
      <anchorfile>classML__Epetra_1_1MatrixFreePreconditioner.html</anchorfile>
      <anchor>a973197e8eda5a2d8d07146b7ecf575eb</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const char *</type>
      <name>Label</name>
      <anchorfile>classML__Epetra_1_1MatrixFreePreconditioner.html</anchorfile>
      <anchor>a9b5b90b67fb0c9fce59cfdc6e251c8bc</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>UseTranspose</name>
      <anchorfile>classML__Epetra_1_1MatrixFreePreconditioner.html</anchorfile>
      <anchor>a5339042fe095d25112de6aba335275ab</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>HasNormInf</name>
      <anchorfile>classML__Epetra_1_1MatrixFreePreconditioner.html</anchorfile>
      <anchor>a8ceeff9b087c4db52a2a7445995b30b3</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_Comm &amp;</type>
      <name>Comm</name>
      <anchorfile>classML__Epetra_1_1MatrixFreePreconditioner.html</anchorfile>
      <anchor>afbf036fc1c8f41e974584d4f9e85da94</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_Map &amp;</type>
      <name>OperatorDomainMap</name>
      <anchorfile>classML__Epetra_1_1MatrixFreePreconditioner.html</anchorfile>
      <anchor>aabc20823ba9f86a9d2d08d3eddf38055</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_Map &amp;</type>
      <name>OperatorRangeMap</name>
      <anchorfile>classML__Epetra_1_1MatrixFreePreconditioner.html</anchorfile>
      <anchor>a4bd95452e397e409962b882439fe5c19</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_RowMatrix &amp;</type>
      <name>C</name>
      <anchorfile>classML__Epetra_1_1MatrixFreePreconditioner.html</anchorfile>
      <anchor>a83981bd4a76b38518fdab36d17bd1c7a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_CrsMatrix &amp;</type>
      <name>R</name>
      <anchorfile>classML__Epetra_1_1MatrixFreePreconditioner.html</anchorfile>
      <anchor>ac3cf0b983bb5e9531d1004b67549dba0</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>ML_Comm *</type>
      <name>Comm_ML</name>
      <anchorfile>classML__Epetra_1_1MatrixFreePreconditioner.html</anchorfile>
      <anchor>a089de4a06e2653e33aafe421a6e549f1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>MyPID</name>
      <anchorfile>classML__Epetra_1_1MatrixFreePreconditioner.html</anchorfile>
      <anchor>ab71746c98a60775971bdfdc043f19be7</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumProc</name>
      <anchorfile>classML__Epetra_1_1MatrixFreePreconditioner.html</anchorfile>
      <anchor>a04e84c4e03b223466c18d467125eb1f0</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>IsComputed</name>
      <anchorfile>classML__Epetra_1_1MatrixFreePreconditioner.html</anchorfile>
      <anchor>a3c7532abe7a11d2fba6ed67ee284232e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>TotalCPUTime</name>
      <anchorfile>classML__Epetra_1_1MatrixFreePreconditioner.html</anchorfile>
      <anchor>ad756892f437177a01ad0177fc4424d69</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Coarsen</name>
      <anchorfile>classML__Epetra_1_1MatrixFreePreconditioner.html</anchorfile>
      <anchor>a694e8347d1dbd2c535adf72e82ce8107</anchor>
      <arglist>(ML_Operator *A, ML_Aggregate **aggr, ML_Operator **P, ML_Operator **R, ML_Operator **C, int NumPDEEqns=1, int NullSpaceDim=1, double *NullSpace=NULL)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetBlockDiagonal</name>
      <anchorfile>classML__Epetra_1_1MatrixFreePreconditioner.html</anchorfile>
      <anchor>a90e1624243f8135bdf6c69b515fec71e</anchor>
      <arglist>(const Epetra_CrsGraph &amp;Graph, std::string DiagonalColoringType)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>ML_agg_indx_comm_struct</name>
    <filename>structML__agg__indx__comm__struct.html</filename>
  </compound>
  <compound kind="struct">
    <name>ML_Aggregate_Comm_Struct</name>
    <filename>structML__Aggregate__Comm__Struct.html</filename>
  </compound>
  <compound kind="struct">
    <name>ML_Aggregate_Struct</name>
    <filename>structML__Aggregate__Struct.html</filename>
    <member kind="variable">
      <type>int</type>
      <name>max_coarse_size</name>
      <anchorfile>structML__Aggregate__Struct.html</anchorfile>
      <anchor>a898579011fad6a35d91219567b8fc950</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>ordering</name>
      <anchorfile>structML__Aggregate__Struct.html</anchorfile>
      <anchor>acab4bb13bc8fe03bafd7818833fe665c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>min_nodes_per_aggregate</name>
      <anchorfile>structML__Aggregate__Struct.html</anchorfile>
      <anchor>af45eb584fac2332111baec113268e90d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>max_neigh_already_selected</name>
      <anchorfile>structML__Aggregate__Struct.html</anchorfile>
      <anchor>aa95fa3e773c16e46b83d4a7e5f974d9f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>double</type>
      <name>threshold</name>
      <anchorfile>structML__Aggregate__Struct.html</anchorfile>
      <anchor>a7ce6ff78b17e33678b316c01b452f16a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>double</type>
      <name>curr_threshold</name>
      <anchorfile>structML__Aggregate__Struct.html</anchorfile>
      <anchor>a4fd7540f39f4e014187f97ac64392b08</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>double</type>
      <name>drop_tol_for_smoothing</name>
      <anchorfile>structML__Aggregate__Struct.html</anchorfile>
      <anchor>a5f3da70fd45edd292d1434bcb5c7ca22</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>attach_scheme</name>
      <anchorfile>structML__Aggregate__Struct.html</anchorfile>
      <anchor>a3382da6b885eac5b005a9601d41dca73</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>double</type>
      <name>smoothP_damping_factor</name>
      <anchorfile>structML__Aggregate__Struct.html</anchorfile>
      <anchor>a151bd6ddf7b886cdb829eb42b7c7a8ce</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int *</type>
      <name>smoothP_damping_sweeps</name>
      <anchorfile>structML__Aggregate__Struct.html</anchorfile>
      <anchor>abc08658b1fdfc267dad21ef44fc182af</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>smoothP_type</name>
      <anchorfile>structML__Aggregate__Struct.html</anchorfile>
      <anchor>a1b7873e30fd4f11c63a7338c73d606b1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>coarsen_scheme</name>
      <anchorfile>structML__Aggregate__Struct.html</anchorfile>
      <anchor>ad92df24e589b907c7a90de2dec4449c6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>num_PDE_eqns</name>
      <anchorfile>structML__Aggregate__Struct.html</anchorfile>
      <anchor>a2cf2441cfd3c79bff86d77d7342abe05</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>nullspace_dim</name>
      <anchorfile>structML__Aggregate__Struct.html</anchorfile>
      <anchor>a115ab97d46bc91d0a06ca511cd07f529</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>double *</type>
      <name>nullspace_vect</name>
      <anchorfile>structML__Aggregate__Struct.html</anchorfile>
      <anchor>aa3cc3f21258616491712a08de87e1ace</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>nullspace_corrupted</name>
      <anchorfile>structML__Aggregate__Struct.html</anchorfile>
      <anchor>ad488997cf728c2282be5841ff063b191</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int *</type>
      <name>aggr_count</name>
      <anchorfile>structML__Aggregate__Struct.html</anchorfile>
      <anchor>a3c0975321d9794932349cd3435b72ded</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>keep_agg_information</name>
      <anchorfile>structML__Aggregate__Struct.html</anchorfile>
      <anchor>af38df70e57cb6e94dea8b13ef346bb38</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int **</type>
      <name>aggr_info</name>
      <anchorfile>structML__Aggregate__Struct.html</anchorfile>
      <anchor>a2ef4f5afddcd8d4670349ff39ce756cd</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>max_levels</name>
      <anchorfile>structML__Aggregate__Struct.html</anchorfile>
      <anchor>a982819a388714072facd30db7650442f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>begin_level</name>
      <anchorfile>structML__Aggregate__Struct.html</anchorfile>
      <anchor>a1f086e1e85dcd19179afbc389cd307cc</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>cur_level</name>
      <anchorfile>structML__Aggregate__Struct.html</anchorfile>
      <anchor>a6222e31746e88a403d02e5d092a5f248</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>double</type>
      <name>operator_complexity</name>
      <anchorfile>structML__Aggregate__Struct.html</anchorfile>
      <anchor>af363cfb58b6eb61e8269825ab6a44dfa</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>double</type>
      <name>fine_complexity</name>
      <anchorfile>structML__Aggregate__Struct.html</anchorfile>
      <anchor>aeaebb816494b3de898b36570216ee326</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>nvblocks</name>
      <anchorfile>structML__Aggregate__Struct.html</anchorfile>
      <anchor>a2aba38a35c9569c4abe965a6965a0369</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int *</type>
      <name>vblock_info</name>
      <anchorfile>structML__Aggregate__Struct.html</anchorfile>
      <anchor>af80f08d7a71bd0029432300294e9b0a5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>keep_P_tentative</name>
      <anchorfile>structML__Aggregate__Struct.html</anchorfile>
      <anchor>aff8178c84feaac7a7afdcc7a0fe252c1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>struct ML_Operator_Struct **</type>
      <name>P_tentative</name>
      <anchorfile>structML__Aggregate__Struct.html</anchorfile>
      <anchor>ad5337a3ad6ebc65f75658e2559c9b9ce</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>smooth_existing_P_tentative</name>
      <anchorfile>structML__Aggregate__Struct.html</anchorfile>
      <anchor>af19f2f77dfdaf413dc84c9d073841306</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>use_transpose</name>
      <anchorfile>structML__Aggregate__Struct.html</anchorfile>
      <anchor>a17a6fdbafa195efd03691dbf158d7f8f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>Restriction_smoothagg_transpose</name>
      <anchorfile>structML__Aggregate__Struct.html</anchorfile>
      <anchor>aeae3e63261715b8a9e0f7534b0a5a15d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>void *</type>
      <name>aggr_options</name>
      <anchorfile>structML__Aggregate__Struct.html</anchorfile>
      <anchor>ac5bd04bb266f7996c28e19647de8237c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>void *</type>
      <name>aggr_viz_and_stats</name>
      <anchorfile>structML__Aggregate__Struct.html</anchorfile>
      <anchor>a509bea10b3c3f1d87e7749c030b673c8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>block_scaled_SA</name>
      <anchorfile>structML__Aggregate__Struct.html</anchorfile>
      <anchor>ac99f9c386544a689e516fa3251172c68</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>double</type>
      <name>phase3_agg_creation</name>
      <anchorfile>structML__Aggregate__Struct.html</anchorfile>
      <anchor>aecc66dd9103ff3b1368a14adf88be179</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>double **</type>
      <name>nodal_coord</name>
      <anchorfile>structML__Aggregate__Struct.html</anchorfile>
      <anchor>ad3391750ff66eaded9935adf624fc0a9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>void *</type>
      <name>vblock_data</name>
      <anchorfile>structML__Aggregate__Struct.html</anchorfile>
      <anchor>a19a5e6fe78c4c2050cd25759341b5703</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>ML_Aux_Data</name>
    <filename>structML__Aux__Data.html</filename>
  </compound>
  <compound kind="struct">
    <name>ML_Function_Struct</name>
    <filename>structML__Function__Struct.html</filename>
  </compound>
  <compound kind="struct">
    <name>ML_GetrowFunc_Struct</name>
    <filename>structML__GetrowFunc__Struct.html</filename>
  </compound>
  <compound kind="struct">
    <name>ml_matscale</name>
    <filename>structml__matscale.html</filename>
  </compound>
  <compound kind="struct">
    <name>ml_matvscale</name>
    <filename>structml__matvscale.html</filename>
  </compound>
  <compound kind="struct">
    <name>ML_Node_Struct</name>
    <filename>structML__Node__Struct.html</filename>
  </compound>
  <compound kind="class">
    <name>MLAPI::ML_Operator_Box</name>
    <filename>classMLAPI_1_1ML__Operator__Box.html</filename>
    <member kind="function">
      <type></type>
      <name>ML_Operator_Box</name>
      <anchorfile>classMLAPI_1_1ML__Operator__Box.html</anchorfile>
      <anchor>a04af1682f3b0a6339a8b8aca7b007ca4</anchor>
      <arglist>(ML_Operator *Op, bool Ownership=true)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~ML_Operator_Box</name>
      <anchorfile>classMLAPI_1_1ML__Operator__Box.html</anchorfile>
      <anchor>ab6ce05171082fbce924e8a54c0c291f8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>ML_Operator *</type>
      <name>GetData</name>
      <anchorfile>classMLAPI_1_1ML__Operator__Box.html</anchorfile>
      <anchor>a3420405ba17039474d6db0bcc12fdea4</anchor>
      <arglist>() const </arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>ML_Operator_Struct</name>
    <filename>structML__Operator__Struct.html</filename>
    <member kind="variable">
      <type>int</type>
      <name>N_nonzeros</name>
      <anchorfile>structML__Operator__Struct.html</anchorfile>
      <anchor>ad677c429387d105339faa17ce0257012</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>ML_Aux_Data *</type>
      <name>aux_data</name>
      <anchorfile>structML__Operator__Struct.html</anchorfile>
      <anchor>aabd7f7f711aa9294695b1dbccd3d40fc</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>ML_Operator_Subspace_Struct</name>
    <filename>structML__Operator__Subspace__Struct.html</filename>
    <member kind="variable">
      <type>int</type>
      <name>vecleng</name>
      <anchorfile>structML__Operator__Subspace__Struct.html</anchorfile>
      <anchor>a34838d1e95e01137bc814d08266e053f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>void(*</type>
      <name>data_destroy</name>
      <anchorfile>structML__Operator__Subspace__Struct.html</anchorfile>
      <anchor>a57cb7fa034d8d8eea5303b9889a190a3</anchor>
      <arglist>)(void *)</arglist>
    </member>
    <member kind="variable">
      <type>int *</type>
      <name>pivots</name>
      <anchorfile>structML__Operator__Subspace__Struct.html</anchorfile>
      <anchor>a4ef32dba2289a4ba84f65b5ad1e400d4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>VAVdone</name>
      <anchorfile>structML__Operator__Subspace__Struct.html</anchorfile>
      <anchor>a939cdf87ea3b1eb6f328e2e046eb888b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>double *</type>
      <name>res1</name>
      <anchorfile>structML__Operator__Subspace__Struct.html</anchorfile>
      <anchor>a0952cf6badaaf66d11f52a1f143ab86f</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>ML_PrintControl_Struct</name>
    <filename>structML__PrintControl__Struct.html</filename>
  </compound>
  <compound kind="class">
    <name>ML_Epetra::ML_RefMaxwell_11_Operator</name>
    <filename>classML__Epetra_1_1ML__RefMaxwell__11__Operator.html</filename>
    <member kind="function">
      <type></type>
      <name>ML_RefMaxwell_11_Operator</name>
      <anchorfile>classML__Epetra_1_1ML__RefMaxwell__11__Operator.html</anchorfile>
      <anchor>a31c8d8fca9e4de209545108db6ac223e</anchor>
      <arglist>(const Epetra_CrsMatrix &amp;SM_Matrix, const Epetra_CrsMatrix &amp;D0_Matrix, const Epetra_CrsMatrix &amp;M0inv_Matrix, const Epetra_CrsMatrix &amp;M1_Matrix)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~ML_RefMaxwell_11_Operator</name>
      <anchorfile>classML__Epetra_1_1ML__RefMaxwell__11__Operator.html</anchorfile>
      <anchor>a354a0440a127440b0bbf3820428f60cc</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>SetUseTranspose</name>
      <anchorfile>classML__Epetra_1_1ML__RefMaxwell__11__Operator.html</anchorfile>
      <anchor>adb9bd3d89d190ec8f77e5f82f22a53a7</anchor>
      <arglist>(bool UseTranspose)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>Apply</name>
      <anchorfile>classML__Epetra_1_1ML__RefMaxwell__11__Operator.html</anchorfile>
      <anchor>a2ce91d7389ccd25cdde3167ffbd8a1ed</anchor>
      <arglist>(const Epetra_MultiVector &amp;X, Epetra_MultiVector &amp;Y) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>ApplyInverse</name>
      <anchorfile>classML__Epetra_1_1ML__RefMaxwell__11__Operator.html</anchorfile>
      <anchor>a4d786f8858630649efb0007df31b2553</anchor>
      <arglist>(const Epetra_MultiVector &amp;X, Epetra_MultiVector &amp;Y) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>MatrixMatrix_Multiply</name>
      <anchorfile>classML__Epetra_1_1ML__RefMaxwell__11__Operator.html</anchorfile>
      <anchor>af79d096202e9483ba824e9bcf470d3bb</anchor>
      <arglist>(const Epetra_CrsMatrix &amp;A, Epetra_CrsMatrix **C) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>MatrixMatrix_Multiply</name>
      <anchorfile>classML__Epetra_1_1ML__RefMaxwell__11__Operator.html</anchorfile>
      <anchor>a4cfa6e5429600dfe5739bb4707a4919a</anchor>
      <arglist>(const Epetra_CrsMatrix &amp;A, ML_Comm *comm, ML_Operator **C) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>PtAP</name>
      <anchorfile>classML__Epetra_1_1ML__RefMaxwell__11__Operator.html</anchorfile>
      <anchor>a396eccc48d0045dfc297519e847de92e</anchor>
      <arglist>(const Epetra_CrsMatrix &amp;A, ML_Comm *comm, ML_Operator **C) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual double</type>
      <name>NormInf</name>
      <anchorfile>classML__Epetra_1_1ML__RefMaxwell__11__Operator.html</anchorfile>
      <anchor>a3575090e727f159cdb41cc39521200cb</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>UseTranspose</name>
      <anchorfile>classML__Epetra_1_1ML__RefMaxwell__11__Operator.html</anchorfile>
      <anchor>a9596072c596ef787a377f214b70e3d46</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>HasNormInf</name>
      <anchorfile>classML__Epetra_1_1ML__RefMaxwell__11__Operator.html</anchorfile>
      <anchor>a31714e5f30b32890d2ca3a13182e2fc3</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const char *</type>
      <name>Label</name>
      <anchorfile>classML__Epetra_1_1ML__RefMaxwell__11__Operator.html</anchorfile>
      <anchor>af4100cbf8e076a8d9b3ef5646fdd3a92</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const Epetra_Comm &amp;</type>
      <name>Comm</name>
      <anchorfile>classML__Epetra_1_1ML__RefMaxwell__11__Operator.html</anchorfile>
      <anchor>a255dca664b0c22a102820a48346d6fd0</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const Epetra_Map &amp;</type>
      <name>OperatorDomainMap</name>
      <anchorfile>classML__Epetra_1_1ML__RefMaxwell__11__Operator.html</anchorfile>
      <anchor>ab37933d32c5333f9a66ef16264d856e0</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const Epetra_Map &amp;</type>
      <name>OperatorRangeMap</name>
      <anchorfile>classML__Epetra_1_1ML__RefMaxwell__11__Operator.html</anchorfile>
      <anchor>afe2e5f2579d0bb4c9ba8876e2fcba6f0</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const Epetra_CrsMatrix &amp;</type>
      <name>SM_Matrix</name>
      <anchorfile>classML__Epetra_1_1ML__RefMaxwell__11__Operator.html</anchorfile>
      <anchor>a790ddd76944c89a9f31767e346305e49</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ML_RefMaxwell_11_Operator</name>
      <anchorfile>classML__Epetra_1_1ML__RefMaxwell__11__Operator.html</anchorfile>
      <anchor>a31c8d8fca9e4de209545108db6ac223e</anchor>
      <arglist>(const Epetra_CrsMatrix &amp;SM_Matrix, const Epetra_CrsMatrix &amp;D0_Matrix, const Epetra_CrsMatrix &amp;M0inv_Matrix, const Epetra_CrsMatrix &amp;M1_Matrix)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~ML_RefMaxwell_11_Operator</name>
      <anchorfile>classML__Epetra_1_1ML__RefMaxwell__11__Operator.html</anchorfile>
      <anchor>a354a0440a127440b0bbf3820428f60cc</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>SetUseTranspose</name>
      <anchorfile>classML__Epetra_1_1ML__RefMaxwell__11__Operator.html</anchorfile>
      <anchor>adb9bd3d89d190ec8f77e5f82f22a53a7</anchor>
      <arglist>(bool UseTranspose)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>Apply</name>
      <anchorfile>classML__Epetra_1_1ML__RefMaxwell__11__Operator.html</anchorfile>
      <anchor>a2ce91d7389ccd25cdde3167ffbd8a1ed</anchor>
      <arglist>(const Epetra_MultiVector &amp;X, Epetra_MultiVector &amp;Y) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>ApplyInverse</name>
      <anchorfile>classML__Epetra_1_1ML__RefMaxwell__11__Operator.html</anchorfile>
      <anchor>a4d786f8858630649efb0007df31b2553</anchor>
      <arglist>(const Epetra_MultiVector &amp;X, Epetra_MultiVector &amp;Y) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>MatrixMatrix_Multiply</name>
      <anchorfile>classML__Epetra_1_1ML__RefMaxwell__11__Operator.html</anchorfile>
      <anchor>af79d096202e9483ba824e9bcf470d3bb</anchor>
      <arglist>(const Epetra_CrsMatrix &amp;A, Epetra_CrsMatrix **C) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>MatrixMatrix_Multiply</name>
      <anchorfile>classML__Epetra_1_1ML__RefMaxwell__11__Operator.html</anchorfile>
      <anchor>a4cfa6e5429600dfe5739bb4707a4919a</anchor>
      <arglist>(const Epetra_CrsMatrix &amp;A, ML_Comm *comm, ML_Operator **C) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>PtAP</name>
      <anchorfile>classML__Epetra_1_1ML__RefMaxwell__11__Operator.html</anchorfile>
      <anchor>a396eccc48d0045dfc297519e847de92e</anchor>
      <arglist>(const Epetra_CrsMatrix &amp;A, ML_Comm *comm, ML_Operator **C) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual double</type>
      <name>NormInf</name>
      <anchorfile>classML__Epetra_1_1ML__RefMaxwell__11__Operator.html</anchorfile>
      <anchor>a3575090e727f159cdb41cc39521200cb</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>UseTranspose</name>
      <anchorfile>classML__Epetra_1_1ML__RefMaxwell__11__Operator.html</anchorfile>
      <anchor>a9596072c596ef787a377f214b70e3d46</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>HasNormInf</name>
      <anchorfile>classML__Epetra_1_1ML__RefMaxwell__11__Operator.html</anchorfile>
      <anchor>a31714e5f30b32890d2ca3a13182e2fc3</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const char *</type>
      <name>Label</name>
      <anchorfile>classML__Epetra_1_1ML__RefMaxwell__11__Operator.html</anchorfile>
      <anchor>af4100cbf8e076a8d9b3ef5646fdd3a92</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const Epetra_Comm &amp;</type>
      <name>Comm</name>
      <anchorfile>classML__Epetra_1_1ML__RefMaxwell__11__Operator.html</anchorfile>
      <anchor>a255dca664b0c22a102820a48346d6fd0</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const Epetra_Map &amp;</type>
      <name>OperatorDomainMap</name>
      <anchorfile>classML__Epetra_1_1ML__RefMaxwell__11__Operator.html</anchorfile>
      <anchor>ab37933d32c5333f9a66ef16264d856e0</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const Epetra_Map &amp;</type>
      <name>OperatorRangeMap</name>
      <anchorfile>classML__Epetra_1_1ML__RefMaxwell__11__Operator.html</anchorfile>
      <anchor>afe2e5f2579d0bb4c9ba8876e2fcba6f0</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const Epetra_CrsMatrix &amp;</type>
      <name>SM_Matrix</name>
      <anchorfile>classML__Epetra_1_1ML__RefMaxwell__11__Operator.html</anchorfile>
      <anchor>a790ddd76944c89a9f31767e346305e49</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ML_RefMaxwell_11_Operator</name>
    <filename>classML__RefMaxwell__11__Operator.html</filename>
  </compound>
  <compound kind="class">
    <name>ML_Epetra::ML_RMP</name>
    <filename>classML__Epetra_1_1ML__RMP.html</filename>
    <member kind="function">
      <type></type>
      <name>ML_RMP</name>
      <anchorfile>classML__Epetra_1_1ML__RMP.html</anchorfile>
      <anchor>a49ff53b0c7dc2f5a43cb496e52962eeb</anchor>
      <arglist>(const Epetra_CrsMatrix &amp;SM_Matrix, const Epetra_CrsMatrix &amp;D0_Clean_Matrix, const Epetra_CrsMatrix &amp;Ms_Matrix, const Epetra_CrsMatrix &amp;M0inv_Matrix, const Epetra_CrsMatrix &amp;M1_Matrix,   const Teuchos::ParameterList &amp;List, const bool ComputePrec=true)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~ML_RMP</name>
      <anchorfile>classML__Epetra_1_1ML__RMP.html</anchorfile>
      <anchor>a359c8fe4a203977af0e70db67c6482d2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Apply</name>
      <anchorfile>classML__Epetra_1_1ML__RMP.html</anchorfile>
      <anchor>a3349b452651d89862d28e49704f0d3e4</anchor>
      <arglist>(const Epetra_MultiVector &amp;X, Epetra_MultiVector &amp;Y) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ApplyInverse</name>
      <anchorfile>classML__Epetra_1_1ML__RMP.html</anchorfile>
      <anchor>a47ab9da5e9523e97fa91c98aaf459535</anchor>
      <arglist>(const Epetra_MultiVector &amp;B, Epetra_MultiVector &amp;X) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ComputePreconditioner</name>
      <anchorfile>classML__Epetra_1_1ML__RMP.html</anchorfile>
      <anchor>af58a9dc1187ee069fb321ee32043f438</anchor>
      <arglist>(const bool CheckFiltering=false)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ReComputePreconditioner</name>
      <anchorfile>classML__Epetra_1_1ML__RMP.html</anchorfile>
      <anchor>a36d957948895596dc93edbc8f23ceab5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Print</name>
      <anchorfile>classML__Epetra_1_1ML__RMP.html</anchorfile>
      <anchor>a59fd52c140699e715729fd80768d8ff6</anchor>
      <arglist>(int whichHierarchy=11)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>DestroyPreconditioner</name>
      <anchorfile>classML__Epetra_1_1ML__RMP.html</anchorfile>
      <anchor>af7d5afbd0185283a22d8651cb901e07c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetUseTranspose</name>
      <anchorfile>classML__Epetra_1_1ML__RMP.html</anchorfile>
      <anchor>a66bab70447e15e53d1bda04e6a05afb6</anchor>
      <arglist>(bool UseTranspose)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>NormInf</name>
      <anchorfile>classML__Epetra_1_1ML__RMP.html</anchorfile>
      <anchor>a56380e6993046be757e541b83a9467e3</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>UseTranspose</name>
      <anchorfile>classML__Epetra_1_1ML__RMP.html</anchorfile>
      <anchor>a76a888d16d8c18bc6edad1678fd1db85</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>HasNormInf</name>
      <anchorfile>classML__Epetra_1_1ML__RMP.html</anchorfile>
      <anchor>a956b0ba83e3892d9e16c30c42a97013c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_Comm &amp;</type>
      <name>Comm</name>
      <anchorfile>classML__Epetra_1_1ML__RMP.html</anchorfile>
      <anchor>ac2842a90bc316ffeb125cbea33532adf</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_Map &amp;</type>
      <name>OperatorDomainMap</name>
      <anchorfile>classML__Epetra_1_1ML__RMP.html</anchorfile>
      <anchor>ad017a92eb2c566e16d7fe059f68031fd</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_Map &amp;</type>
      <name>OperatorRangeMap</name>
      <anchorfile>classML__Epetra_1_1ML__RMP.html</anchorfile>
      <anchor>a810d32a6c5f830a5669274636273ec11</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Complexities</name>
      <anchorfile>classML__Epetra_1_1ML__RMP.html</anchorfile>
      <anchor>a7fb3c354ad297ae65f657561c5ac7be3</anchor>
      <arglist>(double &amp;complexity, double &amp;fineNnz)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ML_RMP</name>
      <anchorfile>classML__Epetra_1_1ML__RMP.html</anchorfile>
      <anchor>a49ff53b0c7dc2f5a43cb496e52962eeb</anchor>
      <arglist>(const Epetra_CrsMatrix &amp;SM_Matrix, const Epetra_CrsMatrix &amp;D0_Clean_Matrix, const Epetra_CrsMatrix &amp;Ms_Matrix, const Epetra_CrsMatrix &amp;M0inv_Matrix, const Epetra_CrsMatrix &amp;M1_Matrix,   const Teuchos::ParameterList &amp;List, const bool ComputePrec=true)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~ML_RMP</name>
      <anchorfile>classML__Epetra_1_1ML__RMP.html</anchorfile>
      <anchor>a359c8fe4a203977af0e70db67c6482d2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Apply</name>
      <anchorfile>classML__Epetra_1_1ML__RMP.html</anchorfile>
      <anchor>a3349b452651d89862d28e49704f0d3e4</anchor>
      <arglist>(const Epetra_MultiVector &amp;X, Epetra_MultiVector &amp;Y) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ApplyInverse</name>
      <anchorfile>classML__Epetra_1_1ML__RMP.html</anchorfile>
      <anchor>a47ab9da5e9523e97fa91c98aaf459535</anchor>
      <arglist>(const Epetra_MultiVector &amp;B, Epetra_MultiVector &amp;X) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ComputePreconditioner</name>
      <anchorfile>classML__Epetra_1_1ML__RMP.html</anchorfile>
      <anchor>af58a9dc1187ee069fb321ee32043f438</anchor>
      <arglist>(const bool CheckFiltering=false)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ReComputePreconditioner</name>
      <anchorfile>classML__Epetra_1_1ML__RMP.html</anchorfile>
      <anchor>a36d957948895596dc93edbc8f23ceab5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Print</name>
      <anchorfile>classML__Epetra_1_1ML__RMP.html</anchorfile>
      <anchor>a59fd52c140699e715729fd80768d8ff6</anchor>
      <arglist>(int whichHierarchy=11)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>DestroyPreconditioner</name>
      <anchorfile>classML__Epetra_1_1ML__RMP.html</anchorfile>
      <anchor>af7d5afbd0185283a22d8651cb901e07c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetUseTranspose</name>
      <anchorfile>classML__Epetra_1_1ML__RMP.html</anchorfile>
      <anchor>a66bab70447e15e53d1bda04e6a05afb6</anchor>
      <arglist>(bool UseTranspose)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>NormInf</name>
      <anchorfile>classML__Epetra_1_1ML__RMP.html</anchorfile>
      <anchor>a56380e6993046be757e541b83a9467e3</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>UseTranspose</name>
      <anchorfile>classML__Epetra_1_1ML__RMP.html</anchorfile>
      <anchor>a76a888d16d8c18bc6edad1678fd1db85</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>HasNormInf</name>
      <anchorfile>classML__Epetra_1_1ML__RMP.html</anchorfile>
      <anchor>a956b0ba83e3892d9e16c30c42a97013c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_Comm &amp;</type>
      <name>Comm</name>
      <anchorfile>classML__Epetra_1_1ML__RMP.html</anchorfile>
      <anchor>ac2842a90bc316ffeb125cbea33532adf</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_Map &amp;</type>
      <name>OperatorDomainMap</name>
      <anchorfile>classML__Epetra_1_1ML__RMP.html</anchorfile>
      <anchor>ad017a92eb2c566e16d7fe059f68031fd</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_Map &amp;</type>
      <name>OperatorRangeMap</name>
      <anchorfile>classML__Epetra_1_1ML__RMP.html</anchorfile>
      <anchor>a810d32a6c5f830a5669274636273ec11</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Complexities</name>
      <anchorfile>classML__Epetra_1_1ML__RMP.html</anchorfile>
      <anchor>a7fb3c354ad297ae65f657561c5ac7be3</anchor>
      <arglist>(double &amp;complexity, double &amp;fineNnz)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>ML_Struct</name>
    <filename>structML__Struct.html</filename>
    <member kind="variable">
      <type>char *</type>
      <name>label</name>
      <anchorfile>structML__Struct.html</anchorfile>
      <anchor>aef1c867bb46d9aa5d0462db5c18803e2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>ML_init_flag</name>
      <anchorfile>structML__Struct.html</anchorfile>
      <anchor>a58c9b9919d727a28381e8e2b5baeaabd</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>ML_scheme</name>
      <anchorfile>structML__Struct.html</anchorfile>
      <anchor>aaf9cb92ce65f3d87be26df675d12f8f3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>ML_num_levels</name>
      <anchorfile>structML__Struct.html</anchorfile>
      <anchor>a724004f663689a69f6fbb33fe310bc9f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>ML_num_actual_levels</name>
      <anchorfile>structML__Struct.html</anchorfile>
      <anchor>aff036cd1faf8335804804958fbf5b9ae</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>ML_num_transfers</name>
      <anchorfile>structML__Struct.html</anchorfile>
      <anchor>a3ec9c031d54d2a8b287aa0971d86c978</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>struct ML_Timing *</type>
      <name>timing</name>
      <anchorfile>structML__Struct.html</anchorfile>
      <anchor>a8517164b0356d6587367221ac32689c9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>ML_Comm *</type>
      <name>comm</name>
      <anchorfile>structML__Struct.html</anchorfile>
      <anchor>ae0f8f1ecdd98112ff6bc300b21f3a96d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int *</type>
      <name>int_options</name>
      <anchorfile>structML__Struct.html</anchorfile>
      <anchor>a2f166391faf83b81774dae50c1e5d06e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>double *</type>
      <name>dble_options</name>
      <anchorfile>structML__Struct.html</anchorfile>
      <anchor>a95612855315e516872c1e7bf9950effb</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>void *</type>
      <name>void_options</name>
      <anchorfile>structML__Struct.html</anchorfile>
      <anchor>a951db8ae96d601c1f5f4b0d2bf1abba8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int(*</type>
      <name>func</name>
      <anchorfile>structML__Struct.html</anchorfile>
      <anchor>a54324ffffa1c179021833ab8cf898524</anchor>
      <arglist>)(void)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>ML_SuperNode_Struct</name>
    <filename>structML__SuperNode__Struct.html</filename>
  </compound>
  <compound kind="struct">
    <name>ML_Timing</name>
    <filename>structML__Timing.html</filename>
  </compound>
  <compound kind="class">
    <name>MLVec</name>
    <filename>classMLVec.html</filename>
    <templarg>T</templarg>
  </compound>
  <compound kind="class">
    <name>MLAPI::MultiLevelAdaptiveSA</name>
    <filename>classMLAPI_1_1MultiLevelAdaptiveSA.html</filename>
    <base>MLAPI::BaseOperator</base>
    <base>MLAPI::CompObject</base>
    <base>MLAPI::TimeObject</base>
    <member kind="function">
      <type></type>
      <name>MultiLevelAdaptiveSA</name>
      <anchorfile>classMLAPI_1_1MultiLevelAdaptiveSA.html</anchorfile>
      <anchor>a3aca65b64a506d9e6a0b68bffbcc8d91</anchor>
      <arglist>(const Operator &amp;FineMatrix, Teuchos::ParameterList &amp;List, const int NumPDEEqns, const int MaxLevels=20)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~MultiLevelAdaptiveSA</name>
      <anchorfile>classMLAPI_1_1MultiLevelAdaptiveSA.html</anchorfile>
      <anchor>a6a01ccbf1300dd96f750c35ec10c3135</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const Space</type>
      <name>GetOperatorDomainSpace</name>
      <anchorfile>classMLAPI_1_1MultiLevelAdaptiveSA.html</anchorfile>
      <anchor>a9c1b2dcaaa0aa3d8728fa60e003ece51</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Space</type>
      <name>GetOperatorRangeSpace</name>
      <anchorfile>classMLAPI_1_1MultiLevelAdaptiveSA.html</anchorfile>
      <anchor>aa3f2d700199d0abff242adb878852c5f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Space</type>
      <name>GetDomainSpace</name>
      <anchorfile>classMLAPI_1_1MultiLevelAdaptiveSA.html</anchorfile>
      <anchor>a1b097fc4ae50497e3097f2683ecfa173</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Space</type>
      <name>GetRangeSpace</name>
      <anchorfile>classMLAPI_1_1MultiLevelAdaptiveSA.html</anchorfile>
      <anchor>ac45a31f5160778c37f15b522dc249139</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Operator &amp;</type>
      <name>R</name>
      <anchorfile>classMLAPI_1_1MultiLevelAdaptiveSA.html</anchorfile>
      <anchor>afd71ff72efa072bba9168dfc91af4243</anchor>
      <arglist>(const int i)</arglist>
    </member>
    <member kind="function">
      <type>const Operator &amp;</type>
      <name>R</name>
      <anchorfile>classMLAPI_1_1MultiLevelAdaptiveSA.html</anchorfile>
      <anchor>a896551b9540dcab1a84fd0211e913d05</anchor>
      <arglist>(const int i) const </arglist>
    </member>
    <member kind="function">
      <type>Operator &amp;</type>
      <name>A</name>
      <anchorfile>classMLAPI_1_1MultiLevelAdaptiveSA.html</anchorfile>
      <anchor>a43e4bf2e3c884fb1d405e6d153f4fc27</anchor>
      <arglist>(const int i)</arglist>
    </member>
    <member kind="function">
      <type>const Operator &amp;</type>
      <name>A</name>
      <anchorfile>classMLAPI_1_1MultiLevelAdaptiveSA.html</anchorfile>
      <anchor>aad45c7717d460fa63a455f540590a3d0</anchor>
      <arglist>(const int i) const </arglist>
    </member>
    <member kind="function">
      <type>Operator &amp;</type>
      <name>P</name>
      <anchorfile>classMLAPI_1_1MultiLevelAdaptiveSA.html</anchorfile>
      <anchor>a1e283c9821689033cb9a9f5542b38fa9</anchor>
      <arglist>(const int i)</arglist>
    </member>
    <member kind="function">
      <type>const Operator &amp;</type>
      <name>P</name>
      <anchorfile>classMLAPI_1_1MultiLevelAdaptiveSA.html</anchorfile>
      <anchor>a69bf67487f13efe4b60f0a4f05c0c874</anchor>
      <arglist>(const int i) const </arglist>
    </member>
    <member kind="function">
      <type>InverseOperator &amp;</type>
      <name>S</name>
      <anchorfile>classMLAPI_1_1MultiLevelAdaptiveSA.html</anchorfile>
      <anchor>a0c6fc45579e808eb37802b1176ea8d5d</anchor>
      <arglist>(const int i)</arglist>
    </member>
    <member kind="function">
      <type>const InverseOperator &amp;</type>
      <name>S</name>
      <anchorfile>classMLAPI_1_1MultiLevelAdaptiveSA.html</anchorfile>
      <anchor>ae0497d65429e5d6b42391d35c48d6624</anchor>
      <arglist>(const int i) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetMaxLevels</name>
      <anchorfile>classMLAPI_1_1MultiLevelAdaptiveSA.html</anchorfile>
      <anchor>ac51c4f49a39225a4c0f08177cee803a6</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetMaxLevels</name>
      <anchorfile>classMLAPI_1_1MultiLevelAdaptiveSA.html</anchorfile>
      <anchor>a3072c4ba992de3b93eee84109f391436</anchor>
      <arglist>(const int MaxLevels)</arglist>
    </member>
    <member kind="function">
      <type>const MultiVector</type>
      <name>GetNullSpace</name>
      <anchorfile>classMLAPI_1_1MultiLevelAdaptiveSA.html</anchorfile>
      <anchor>acb69e49a42170324898b30b43da85eb5</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetNullSpace</name>
      <anchorfile>classMLAPI_1_1MultiLevelAdaptiveSA.html</anchorfile>
      <anchor>a39ab369798ae68f1c90597a8de96e12e</anchor>
      <arglist>(MultiVector &amp;NullSpace)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>IsComputed</name>
      <anchorfile>classMLAPI_1_1MultiLevelAdaptiveSA.html</anchorfile>
      <anchor>a3ef022a9df777e018f89c93d29dacf14</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetList</name>
      <anchorfile>classMLAPI_1_1MultiLevelAdaptiveSA.html</anchorfile>
      <anchor>ab6c259fb8a3c5c523ec7d6984501c1e6</anchor>
      <arglist>(Teuchos::ParameterList &amp;List)</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>GetSmootherType</name>
      <anchorfile>classMLAPI_1_1MultiLevelAdaptiveSA.html</anchorfile>
      <anchor>a60c3d37967f6a66b3b8af5db1e08b40a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>GetCoarseType</name>
      <anchorfile>classMLAPI_1_1MultiLevelAdaptiveSA.html</anchorfile>
      <anchor>a375a6264ebc927e95867554d63e5c2ec</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetInputNumPDEEqns</name>
      <anchorfile>classMLAPI_1_1MultiLevelAdaptiveSA.html</anchorfile>
      <anchor>aaa0cfa0e011c306cd50825e178c400a7</anchor>
      <arglist>(const int n)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetInputNumPDEEqns</name>
      <anchorfile>classMLAPI_1_1MultiLevelAdaptiveSA.html</anchorfile>
      <anchor>aafbed74f88b645ec0bfc8e47c047a713</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetNumPDEEqns</name>
      <anchorfile>classMLAPI_1_1MultiLevelAdaptiveSA.html</anchorfile>
      <anchor>a9096b4cdfe877380b78160979dfe9bf7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetMaxCoarseSize</name>
      <anchorfile>classMLAPI_1_1MultiLevelAdaptiveSA.html</anchorfile>
      <anchor>ae01cfa548f3d03dbc6a37fda72df004e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>GetMaxReduction</name>
      <anchorfile>classMLAPI_1_1MultiLevelAdaptiveSA.html</anchorfile>
      <anchor>a16db4832152a4bfa1be6075e7c5d2ece</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetNumItersCoarse</name>
      <anchorfile>classMLAPI_1_1MultiLevelAdaptiveSA.html</anchorfile>
      <anchor>a6e6342b000d42ed2c51c858283d976b2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetNumItersFine</name>
      <anchorfile>classMLAPI_1_1MultiLevelAdaptiveSA.html</anchorfile>
      <anchor>ac17e59dcd0e8d690a78dcfd4cb3b9ac7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>GetComplexity</name>
      <anchorfile>classMLAPI_1_1MultiLevelAdaptiveSA.html</anchorfile>
      <anchor>abbed983bd488ee1ad06af5b39c413115</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Compute</name>
      <anchorfile>classMLAPI_1_1MultiLevelAdaptiveSA.html</anchorfile>
      <anchor>a8d2d6fad09c8673ff636fdbc4ade7fba</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>AdaptCompute</name>
      <anchorfile>classMLAPI_1_1MultiLevelAdaptiveSA.html</anchorfile>
      <anchor>aa844aada295b478d230e504fe88c810f</anchor>
      <arglist>(const bool UseDefaultOrSpecified, int AdditionalCandidates)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetupInitialNullSpace</name>
      <anchorfile>classMLAPI_1_1MultiLevelAdaptiveSA.html</anchorfile>
      <anchor>a097e53228a327b62eb250654ce1f8c17</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>IncrementNullSpace</name>
      <anchorfile>classMLAPI_1_1MultiLevelAdaptiveSA.html</anchorfile>
      <anchor>a54581d09676369030c9fb1ce186d4d0a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Apply</name>
      <anchorfile>classMLAPI_1_1MultiLevelAdaptiveSA.html</anchorfile>
      <anchor>a46ce5b613a39952b035dfba7163f07a3</anchor>
      <arglist>(const MultiVector &amp;b_f, MultiVector &amp;x_f) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SolveMultiLevelSA</name>
      <anchorfile>classMLAPI_1_1MultiLevelAdaptiveSA.html</anchorfile>
      <anchor>acaf53461f567c37a85d2715c7bfb9335</anchor>
      <arglist>(const MultiVector &amp;b_f, MultiVector &amp;x_f, int level) const </arglist>
    </member>
    <member kind="function">
      <type>std::ostream &amp;</type>
      <name>Print</name>
      <anchorfile>classMLAPI_1_1MultiLevelAdaptiveSA.html</anchorfile>
      <anchor>a38dd87522e70cc3b79d7a41453211f0b</anchor>
      <arglist>(std::ostream &amp;os, const bool verbose=true) const </arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>MultiLevelAdaptiveSA</name>
      <anchorfile>classMLAPI_1_1MultiLevelAdaptiveSA.html</anchorfile>
      <anchor>a3aca65b64a506d9e6a0b68bffbcc8d91</anchor>
      <arglist>(const Operator &amp;FineMatrix, Teuchos::ParameterList &amp;List, const int NumPDEEqns, const int MaxLevels=20)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~MultiLevelAdaptiveSA</name>
      <anchorfile>classMLAPI_1_1MultiLevelAdaptiveSA.html</anchorfile>
      <anchor>a6a01ccbf1300dd96f750c35ec10c3135</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const Space</type>
      <name>GetOperatorDomainSpace</name>
      <anchorfile>classMLAPI_1_1MultiLevelAdaptiveSA.html</anchorfile>
      <anchor>a9c1b2dcaaa0aa3d8728fa60e003ece51</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Space</type>
      <name>GetOperatorRangeSpace</name>
      <anchorfile>classMLAPI_1_1MultiLevelAdaptiveSA.html</anchorfile>
      <anchor>aa3f2d700199d0abff242adb878852c5f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Space</type>
      <name>GetDomainSpace</name>
      <anchorfile>classMLAPI_1_1MultiLevelAdaptiveSA.html</anchorfile>
      <anchor>a1b097fc4ae50497e3097f2683ecfa173</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Space</type>
      <name>GetRangeSpace</name>
      <anchorfile>classMLAPI_1_1MultiLevelAdaptiveSA.html</anchorfile>
      <anchor>ac45a31f5160778c37f15b522dc249139</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Operator &amp;</type>
      <name>R</name>
      <anchorfile>classMLAPI_1_1MultiLevelAdaptiveSA.html</anchorfile>
      <anchor>afd71ff72efa072bba9168dfc91af4243</anchor>
      <arglist>(const int i)</arglist>
    </member>
    <member kind="function">
      <type>const Operator &amp;</type>
      <name>R</name>
      <anchorfile>classMLAPI_1_1MultiLevelAdaptiveSA.html</anchorfile>
      <anchor>a896551b9540dcab1a84fd0211e913d05</anchor>
      <arglist>(const int i) const </arglist>
    </member>
    <member kind="function">
      <type>Operator &amp;</type>
      <name>A</name>
      <anchorfile>classMLAPI_1_1MultiLevelAdaptiveSA.html</anchorfile>
      <anchor>a43e4bf2e3c884fb1d405e6d153f4fc27</anchor>
      <arglist>(const int i)</arglist>
    </member>
    <member kind="function">
      <type>const Operator &amp;</type>
      <name>A</name>
      <anchorfile>classMLAPI_1_1MultiLevelAdaptiveSA.html</anchorfile>
      <anchor>aad45c7717d460fa63a455f540590a3d0</anchor>
      <arglist>(const int i) const </arglist>
    </member>
    <member kind="function">
      <type>Operator &amp;</type>
      <name>P</name>
      <anchorfile>classMLAPI_1_1MultiLevelAdaptiveSA.html</anchorfile>
      <anchor>a1e283c9821689033cb9a9f5542b38fa9</anchor>
      <arglist>(const int i)</arglist>
    </member>
    <member kind="function">
      <type>const Operator &amp;</type>
      <name>P</name>
      <anchorfile>classMLAPI_1_1MultiLevelAdaptiveSA.html</anchorfile>
      <anchor>a69bf67487f13efe4b60f0a4f05c0c874</anchor>
      <arglist>(const int i) const </arglist>
    </member>
    <member kind="function">
      <type>InverseOperator &amp;</type>
      <name>S</name>
      <anchorfile>classMLAPI_1_1MultiLevelAdaptiveSA.html</anchorfile>
      <anchor>a0c6fc45579e808eb37802b1176ea8d5d</anchor>
      <arglist>(const int i)</arglist>
    </member>
    <member kind="function">
      <type>const InverseOperator &amp;</type>
      <name>S</name>
      <anchorfile>classMLAPI_1_1MultiLevelAdaptiveSA.html</anchorfile>
      <anchor>ae0497d65429e5d6b42391d35c48d6624</anchor>
      <arglist>(const int i) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetMaxLevels</name>
      <anchorfile>classMLAPI_1_1MultiLevelAdaptiveSA.html</anchorfile>
      <anchor>ac51c4f49a39225a4c0f08177cee803a6</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetMaxLevels</name>
      <anchorfile>classMLAPI_1_1MultiLevelAdaptiveSA.html</anchorfile>
      <anchor>a3072c4ba992de3b93eee84109f391436</anchor>
      <arglist>(const int MaxLevels)</arglist>
    </member>
    <member kind="function">
      <type>const MultiVector</type>
      <name>GetNullSpace</name>
      <anchorfile>classMLAPI_1_1MultiLevelAdaptiveSA.html</anchorfile>
      <anchor>acb69e49a42170324898b30b43da85eb5</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetNullSpace</name>
      <anchorfile>classMLAPI_1_1MultiLevelAdaptiveSA.html</anchorfile>
      <anchor>a39ab369798ae68f1c90597a8de96e12e</anchor>
      <arglist>(MultiVector &amp;NullSpace)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>IsComputed</name>
      <anchorfile>classMLAPI_1_1MultiLevelAdaptiveSA.html</anchorfile>
      <anchor>a3ef022a9df777e018f89c93d29dacf14</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetList</name>
      <anchorfile>classMLAPI_1_1MultiLevelAdaptiveSA.html</anchorfile>
      <anchor>ab6c259fb8a3c5c523ec7d6984501c1e6</anchor>
      <arglist>(Teuchos::ParameterList &amp;List)</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>GetSmootherType</name>
      <anchorfile>classMLAPI_1_1MultiLevelAdaptiveSA.html</anchorfile>
      <anchor>a60c3d37967f6a66b3b8af5db1e08b40a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>GetCoarseType</name>
      <anchorfile>classMLAPI_1_1MultiLevelAdaptiveSA.html</anchorfile>
      <anchor>a375a6264ebc927e95867554d63e5c2ec</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetInputNumPDEEqns</name>
      <anchorfile>classMLAPI_1_1MultiLevelAdaptiveSA.html</anchorfile>
      <anchor>aaa0cfa0e011c306cd50825e178c400a7</anchor>
      <arglist>(const int n)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetInputNumPDEEqns</name>
      <anchorfile>classMLAPI_1_1MultiLevelAdaptiveSA.html</anchorfile>
      <anchor>aafbed74f88b645ec0bfc8e47c047a713</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetNumPDEEqns</name>
      <anchorfile>classMLAPI_1_1MultiLevelAdaptiveSA.html</anchorfile>
      <anchor>a9096b4cdfe877380b78160979dfe9bf7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetMaxCoarseSize</name>
      <anchorfile>classMLAPI_1_1MultiLevelAdaptiveSA.html</anchorfile>
      <anchor>ae01cfa548f3d03dbc6a37fda72df004e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>GetMaxReduction</name>
      <anchorfile>classMLAPI_1_1MultiLevelAdaptiveSA.html</anchorfile>
      <anchor>a16db4832152a4bfa1be6075e7c5d2ece</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetNumItersCoarse</name>
      <anchorfile>classMLAPI_1_1MultiLevelAdaptiveSA.html</anchorfile>
      <anchor>a6e6342b000d42ed2c51c858283d976b2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetNumItersFine</name>
      <anchorfile>classMLAPI_1_1MultiLevelAdaptiveSA.html</anchorfile>
      <anchor>ac17e59dcd0e8d690a78dcfd4cb3b9ac7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>GetComplexity</name>
      <anchorfile>classMLAPI_1_1MultiLevelAdaptiveSA.html</anchorfile>
      <anchor>abbed983bd488ee1ad06af5b39c413115</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Compute</name>
      <anchorfile>classMLAPI_1_1MultiLevelAdaptiveSA.html</anchorfile>
      <anchor>a8d2d6fad09c8673ff636fdbc4ade7fba</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>AdaptCompute</name>
      <anchorfile>classMLAPI_1_1MultiLevelAdaptiveSA.html</anchorfile>
      <anchor>aa844aada295b478d230e504fe88c810f</anchor>
      <arglist>(const bool UseDefaultOrSpecified, int AdditionalCandidates)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetupInitialNullSpace</name>
      <anchorfile>classMLAPI_1_1MultiLevelAdaptiveSA.html</anchorfile>
      <anchor>a097e53228a327b62eb250654ce1f8c17</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>IncrementNullSpace</name>
      <anchorfile>classMLAPI_1_1MultiLevelAdaptiveSA.html</anchorfile>
      <anchor>a54581d09676369030c9fb1ce186d4d0a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Apply</name>
      <anchorfile>classMLAPI_1_1MultiLevelAdaptiveSA.html</anchorfile>
      <anchor>a46ce5b613a39952b035dfba7163f07a3</anchor>
      <arglist>(const MultiVector &amp;b_f, MultiVector &amp;x_f) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SolveMultiLevelSA</name>
      <anchorfile>classMLAPI_1_1MultiLevelAdaptiveSA.html</anchorfile>
      <anchor>acaf53461f567c37a85d2715c7bfb9335</anchor>
      <arglist>(const MultiVector &amp;b_f, MultiVector &amp;x_f, int level) const </arglist>
    </member>
    <member kind="function">
      <type>std::ostream &amp;</type>
      <name>Print</name>
      <anchorfile>classMLAPI_1_1MultiLevelAdaptiveSA.html</anchorfile>
      <anchor>a38dd87522e70cc3b79d7a41453211f0b</anchor>
      <arglist>(std::ostream &amp;os, const bool verbose=true) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ML_Epetra::MultiLevelOperator</name>
    <filename>classML__Epetra_1_1MultiLevelOperator.html</filename>
    <base virtualness="virtual">Epetra_Operator</base>
    <member kind="function">
      <type></type>
      <name>MultiLevelOperator</name>
      <anchorfile>classML__Epetra_1_1MultiLevelOperator.html</anchorfile>
      <anchor>a325e6416ed1a7e7ac2ac27f298221d0c</anchor>
      <arglist>(ML *ml_handle, const Epetra_Comm &amp;myComm, const Epetra_Map &amp;DomainMap, const Epetra_Map &amp;RangeMap)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~MultiLevelOperator</name>
      <anchorfile>classML__Epetra_1_1MultiLevelOperator.html</anchorfile>
      <anchor>acd0d8e1f7d7dbdc5202be8eab8936f74</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetOwnership</name>
      <anchorfile>classML__Epetra_1_1MultiLevelOperator.html</anchorfile>
      <anchor>a0e1ebf1eddbff7b3f37556742bf99b5c</anchor>
      <arglist>(bool ownership)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetUseTranspose</name>
      <anchorfile>classML__Epetra_1_1MultiLevelOperator.html</anchorfile>
      <anchor>a516e0298ea657191e475fb36e60fcb42</anchor>
      <arglist>(bool UseTrans)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Apply</name>
      <anchorfile>classML__Epetra_1_1MultiLevelOperator.html</anchorfile>
      <anchor>a3544f0b73c189b345801336fd5f83263</anchor>
      <arglist>(const Epetra_MultiVector &amp;X, Epetra_MultiVector &amp;Y) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ApplyInverse</name>
      <anchorfile>classML__Epetra_1_1MultiLevelOperator.html</anchorfile>
      <anchor>a9005ccd380c347515d811399a1d2844b</anchor>
      <arglist>(const Epetra_MultiVector &amp;X, Epetra_MultiVector &amp;Y) const </arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>NormInf</name>
      <anchorfile>classML__Epetra_1_1MultiLevelOperator.html</anchorfile>
      <anchor>a53926445a0a8daa4596f5535731b399f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const char *</type>
      <name>Label</name>
      <anchorfile>classML__Epetra_1_1MultiLevelOperator.html</anchorfile>
      <anchor>a0d08cdd81bdf042002d58b51003f2187</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>UseTranspose</name>
      <anchorfile>classML__Epetra_1_1MultiLevelOperator.html</anchorfile>
      <anchor>a4e00420697ef47afba61fd437cdcd72d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>HasNormInf</name>
      <anchorfile>classML__Epetra_1_1MultiLevelOperator.html</anchorfile>
      <anchor>aa5c625f0ad319d6988174f8443975096</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_Comm &amp;</type>
      <name>Comm</name>
      <anchorfile>classML__Epetra_1_1MultiLevelOperator.html</anchorfile>
      <anchor>ab47c721670b61ffb8691d44d416f6e7d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_Map &amp;</type>
      <name>OperatorDomainMap</name>
      <anchorfile>classML__Epetra_1_1MultiLevelOperator.html</anchorfile>
      <anchor>a58caff554ebe3affb337cfde57ce3d2f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_Map &amp;</type>
      <name>OperatorRangeMap</name>
      <anchorfile>classML__Epetra_1_1MultiLevelOperator.html</anchorfile>
      <anchor>a49f75658df412d861318ab8a65ee4039</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>MultiLevelOperator</name>
      <anchorfile>classML__Epetra_1_1MultiLevelOperator.html</anchorfile>
      <anchor>a325e6416ed1a7e7ac2ac27f298221d0c</anchor>
      <arglist>(ML *ml_handle, const Epetra_Comm &amp;myComm, const Epetra_Map &amp;DomainMap, const Epetra_Map &amp;RangeMap)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~MultiLevelOperator</name>
      <anchorfile>classML__Epetra_1_1MultiLevelOperator.html</anchorfile>
      <anchor>acd0d8e1f7d7dbdc5202be8eab8936f74</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetOwnership</name>
      <anchorfile>classML__Epetra_1_1MultiLevelOperator.html</anchorfile>
      <anchor>a0e1ebf1eddbff7b3f37556742bf99b5c</anchor>
      <arglist>(bool ownership)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetUseTranspose</name>
      <anchorfile>classML__Epetra_1_1MultiLevelOperator.html</anchorfile>
      <anchor>a516e0298ea657191e475fb36e60fcb42</anchor>
      <arglist>(bool UseTrans)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Apply</name>
      <anchorfile>classML__Epetra_1_1MultiLevelOperator.html</anchorfile>
      <anchor>a3544f0b73c189b345801336fd5f83263</anchor>
      <arglist>(const Epetra_MultiVector &amp;X, Epetra_MultiVector &amp;Y) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ApplyInverse</name>
      <anchorfile>classML__Epetra_1_1MultiLevelOperator.html</anchorfile>
      <anchor>a9005ccd380c347515d811399a1d2844b</anchor>
      <arglist>(const Epetra_MultiVector &amp;X, Epetra_MultiVector &amp;Y) const </arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>NormInf</name>
      <anchorfile>classML__Epetra_1_1MultiLevelOperator.html</anchorfile>
      <anchor>a53926445a0a8daa4596f5535731b399f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const char *</type>
      <name>Label</name>
      <anchorfile>classML__Epetra_1_1MultiLevelOperator.html</anchorfile>
      <anchor>a0d08cdd81bdf042002d58b51003f2187</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>UseTranspose</name>
      <anchorfile>classML__Epetra_1_1MultiLevelOperator.html</anchorfile>
      <anchor>a4e00420697ef47afba61fd437cdcd72d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>HasNormInf</name>
      <anchorfile>classML__Epetra_1_1MultiLevelOperator.html</anchorfile>
      <anchor>aa5c625f0ad319d6988174f8443975096</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_Comm &amp;</type>
      <name>Comm</name>
      <anchorfile>classML__Epetra_1_1MultiLevelOperator.html</anchorfile>
      <anchor>ab47c721670b61ffb8691d44d416f6e7d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_Map &amp;</type>
      <name>OperatorDomainMap</name>
      <anchorfile>classML__Epetra_1_1MultiLevelOperator.html</anchorfile>
      <anchor>a58caff554ebe3affb337cfde57ce3d2f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_Map &amp;</type>
      <name>OperatorRangeMap</name>
      <anchorfile>classML__Epetra_1_1MultiLevelOperator.html</anchorfile>
      <anchor>a49f75658df412d861318ab8a65ee4039</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>ML *</type>
      <name>solver_</name>
      <anchorfile>classML__Epetra_1_1MultiLevelOperator.html</anchorfile>
      <anchor>acc33618c49c00f2e2d6b9db29907159d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>const char *</type>
      <name>Label_</name>
      <anchorfile>classML__Epetra_1_1MultiLevelOperator.html</anchorfile>
      <anchor>af6f28dfcdad83802ec8fae2a70a53504</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ML_Epetra::MultiLevelPreconditioner</name>
    <filename>classML__Epetra_1_1MultiLevelPreconditioner.html</filename>
    <base virtualness="virtual">Epetra_Operator</base>
    <member kind="function">
      <type>int</type>
      <name>DestroyPreconditioner</name>
      <anchorfile>classML__Epetra_1_1MultiLevelPreconditioner.html</anchorfile>
      <anchor>a5510672a594a1b136b57d1650f136d58</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const Epetra_RowMatrix &amp;</type>
      <name>RowMatrix</name>
      <anchorfile>classML__Epetra_1_1MultiLevelPreconditioner.html</anchorfile>
      <anchor>a2f9a38135e718dd3ad4fa3f011f01db7</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_BlockMap &amp;</type>
      <name>Map</name>
      <anchorfile>classML__Epetra_1_1MultiLevelPreconditioner.html</anchorfile>
      <anchor>a5009d29600ac67995b8eb9ffcc35f6a7</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumGlobalRows</name>
      <anchorfile>classML__Epetra_1_1MultiLevelPreconditioner.html</anchorfile>
      <anchor>ae92ee53806ff15a568034e622282acee</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumGlobalCols</name>
      <anchorfile>classML__Epetra_1_1MultiLevelPreconditioner.html</anchorfile>
      <anchor>a78c15a278a6e609789041e5cb91ebcb9</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumMyRows</name>
      <anchorfile>classML__Epetra_1_1MultiLevelPreconditioner.html</anchorfile>
      <anchor>a7074e36351ed66d585babeef2b5bda05</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumMyCols</name>
      <anchorfile>classML__Epetra_1_1MultiLevelPreconditioner.html</anchorfile>
      <anchor>a26635fe90e8273c31728a541ffa5c171</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>PrintStencil2D</name>
      <anchorfile>classML__Epetra_1_1MultiLevelPreconditioner.html</anchorfile>
      <anchor>a0250fca18c73c4675907bbae2b2fc58e</anchor>
      <arglist>(const int nx, const int ny, int NodeID=-1, const int EquationID=0)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>AnalyzeHierarchy</name>
      <anchorfile>classML__Epetra_1_1MultiLevelPreconditioner.html</anchorfile>
      <anchor>aad3f352613d2efe0524b0d608ab82aca</anchor>
      <arglist>(const bool AnalyzeMatrices, const int PreCycles, const int PostCycles, const int MLCycles)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>AnalyzeSmoothers</name>
      <anchorfile>classML__Epetra_1_1MultiLevelPreconditioner.html</anchorfile>
      <anchor>a7960fc2ac3906e24925454f977acb158</anchor>
      <arglist>(const int NumPreCycles=1, const int NumPostCycles=1)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>AnalyzeCoarse</name>
      <anchorfile>classML__Epetra_1_1MultiLevelPreconditioner.html</anchorfile>
      <anchor>ad90526df20598a4d1fbfa73ed62d64b2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>AnalyzeCycle</name>
      <anchorfile>classML__Epetra_1_1MultiLevelPreconditioner.html</anchorfile>
      <anchor>aebf72f32c5d51a4ea81804772c019db0</anchor>
      <arglist>(const int NumCycles=1)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>TestSmoothers</name>
      <anchorfile>classML__Epetra_1_1MultiLevelPreconditioner.html</anchorfile>
      <anchor>aee7c0666a162fac38cf6d67f734271bc</anchor>
      <arglist>(Teuchos::ParameterList &amp;InputList, const bool IsSymmetric=false)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>TestSmoothers</name>
      <anchorfile>classML__Epetra_1_1MultiLevelPreconditioner.html</anchorfile>
      <anchor>a2fa7eb152a06a7a01fe63632f5824304</anchor>
      <arglist>(const bool IsSymmetric=false)</arglist>
    </member>
    <member kind="function">
      <type>const ML *</type>
      <name>GetML</name>
      <anchorfile>classML__Epetra_1_1MultiLevelPreconditioner.html</anchorfile>
      <anchor>a78fd9b34fb1d05d5679611dc2384034a</anchor>
      <arglist>(const int WhichML=-1) const </arglist>
    </member>
    <member kind="function">
      <type>const ML_Aggregate *</type>
      <name>GetML_Aggregate</name>
      <anchorfile>classML__Epetra_1_1MultiLevelPreconditioner.html</anchorfile>
      <anchor>af5910ac9796be89a0e8f7a9aee8ba9f1</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Visualize</name>
      <anchorfile>classML__Epetra_1_1MultiLevelPreconditioner.html</anchorfile>
      <anchor>ad6fb3f860653a999349c47053c13a798</anchor>
      <arglist>(bool VizAggre, bool VizPreSmoother, bool VizPostSmoother, bool VizCycle, int NumApplPreSmoother, int NumApplPostSmoother, int NumCycleSmoother)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>VisualizeAggregates</name>
      <anchorfile>classML__Epetra_1_1MultiLevelPreconditioner.html</anchorfile>
      <anchor>ac9006beb44fcd09703759b96ec80b6ed</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>VisualizeSmoothers</name>
      <anchorfile>classML__Epetra_1_1MultiLevelPreconditioner.html</anchorfile>
      <anchor>a5ee16b64ffa2632ec49003d01075b9a4</anchor>
      <arglist>(int NumPrecCycles=1, int NumPostCycles=1)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>VisualizeCycle</name>
      <anchorfile>classML__Epetra_1_1MultiLevelPreconditioner.html</anchorfile>
      <anchor>a770b9637ed6b5f8b1affa48979ea0f57</anchor>
      <arglist>(int NumCycles=1)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>CreateLabel</name>
      <anchorfile>classML__Epetra_1_1MultiLevelPreconditioner.html</anchorfile>
      <anchor>a7299deaa41b375504533f87a6e76b1b5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Complexities</name>
      <anchorfile>classML__Epetra_1_1MultiLevelPreconditioner.html</anchorfile>
      <anchor>a444d355346756356c2ee4b29647ec53e</anchor>
      <arglist>(double &amp;complexity, double &amp;fineNnz)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>MultiLevelPreconditioner</name>
      <anchorfile>classML__Epetra_1_1MultiLevelPreconditioner.html</anchorfile>
      <anchor>a67347841c24bebda9e38ad628db145ba</anchor>
      <arglist>(const Epetra_RowMatrix &amp;RowMatrix, const bool ComputePrec=true)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>MultiLevelPreconditioner</name>
      <anchorfile>classML__Epetra_1_1MultiLevelPreconditioner.html</anchorfile>
      <anchor>a86ce4d3dd21908f8379fcf0ae41d2ffc</anchor>
      <arglist>(const Epetra_RowMatrix &amp;RowMatrix, const Teuchos::ParameterList &amp;List, const bool ComputePrec=true)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>MultiLevelPreconditioner</name>
      <anchorfile>classML__Epetra_1_1MultiLevelPreconditioner.html</anchorfile>
      <anchor>a809f3f842ef718ef97fc7b27a6ba21b5</anchor>
      <arglist>(ML_Operator *Operator, const Teuchos::ParameterList &amp;List, const bool ComputePrec=true)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>MultiLevelPreconditioner</name>
      <anchorfile>classML__Epetra_1_1MultiLevelPreconditioner.html</anchorfile>
      <anchor>a953ea2d18629c19c0b67e0a28338718a</anchor>
      <arglist>(ML_Operator *Operator, const Teuchos::ParameterList &amp;List, Epetra_RowMatrix **DiagOperators, Teuchos::ParameterList *DiagLists, int NBlocks=1, const bool ComputePrec=true)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>MultiLevelPreconditioner</name>
      <anchorfile>classML__Epetra_1_1MultiLevelPreconditioner.html</anchorfile>
      <anchor>a59203ed1c62ac76884e252f50e05a405</anchor>
      <arglist>(const Epetra_RowMatrix &amp;EdgeMatrix, const Epetra_RowMatrix &amp;GradMatrix, const Epetra_RowMatrix &amp;NodeMatrix, const Teuchos::ParameterList &amp;List, const bool ComputePrec=true, const bool UseNodeMatrixForSmoother=false)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>MultiLevelPreconditioner</name>
      <anchorfile>classML__Epetra_1_1MultiLevelPreconditioner.html</anchorfile>
      <anchor>a0ecdb34d13aaceb48767950ed50d1b24</anchor>
      <arglist>(const Epetra_RowMatrix &amp;CurlCurlMatrix, const Epetra_RowMatrix &amp;MassMatrix, const Epetra_RowMatrix &amp;TMatrix, const Epetra_RowMatrix &amp;NodeMatrix, const Teuchos::ParameterList &amp;List, const bool ComputePrec=true)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>MultiLevelPreconditioner</name>
      <anchorfile>classML__Epetra_1_1MultiLevelPreconditioner.html</anchorfile>
      <anchor>a0e3e3380ddad9bf64d3bf36bc3802f8f</anchor>
      <arglist>(Epetra_RowMatrix &amp;RowMatrix, const Teuchos::ParameterList &amp;List, const int &amp;nNodes, const int &amp;maxDofPerNode, bool *dofPresent, Epetra_Vector &amp;Lhs, Epetra_Vector &amp;Rhs, const bool rhsAndsolProvided, const bool ComputePrec=true)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>MultiLevelPreconditioner</name>
      <anchorfile>classML__Epetra_1_1MultiLevelPreconditioner.html</anchorfile>
      <anchor>a5100c460d7d4f8ad0ba4819266393247</anchor>
      <arglist>(Epetra_RowMatrix &amp;RowMatrix, const Teuchos::ParameterList &amp;List, const double distTol,   const double tol,   Epetra_Vector &amp;Lhs, Epetra_Vector &amp;Rhs, const bool rhsAndsolProvided, const bool ComputePrec=true)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>MultiLevelPreconditioner</name>
      <anchorfile>classML__Epetra_1_1MultiLevelPreconditioner.html</anchorfile>
      <anchor>a5dd2ea24704e439cc3e87df1923cc883</anchor>
      <arglist>(const Epetra_MsrMatrix &amp;EdgeMatrix, ML_Operator *GradMatrix, AZ_MATRIX *NodeMatrix, int *proc_config, const Teuchos::ParameterList &amp;List, const bool ComputePrec=true)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~MultiLevelPreconditioner</name>
      <anchorfile>classML__Epetra_1_1MultiLevelPreconditioner.html</anchorfile>
      <anchor>a8b15a8eb8beeaddc47e1eb96061e982d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const char *</type>
      <name>Label</name>
      <anchorfile>classML__Epetra_1_1MultiLevelPreconditioner.html</anchorfile>
      <anchor>a5ef687b3bdbffb21cead84252b1ee6af</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>PrintUnused</name>
      <anchorfile>classML__Epetra_1_1MultiLevelPreconditioner.html</anchorfile>
      <anchor>a7f740f61bd18078a9d96fd2fa9b0179c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>PrintUnused</name>
      <anchorfile>classML__Epetra_1_1MultiLevelPreconditioner.html</anchorfile>
      <anchor>a1d190e002859b685d68e7964bab5e1b6</anchor>
      <arglist>(std::ostream &amp;os) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>PrintUnused</name>
      <anchorfile>classML__Epetra_1_1MultiLevelPreconditioner.html</anchorfile>
      <anchor>a64d70645c93c60bdb8cfa598c223dda1</anchor>
      <arglist>(const int MyPID) const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::ParameterList &amp;</type>
      <name>GetList</name>
      <anchorfile>classML__Epetra_1_1MultiLevelPreconditioner.html</anchorfile>
      <anchor>aea04faceca753615b34eee8794f50698</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>PrintList</name>
      <anchorfile>classML__Epetra_1_1MultiLevelPreconditioner.html</anchorfile>
      <anchor>a2df61ccbf8cefd809ea6880c2ac0ed9c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetParameterList</name>
      <anchorfile>classML__Epetra_1_1MultiLevelPreconditioner.html</anchorfile>
      <anchor>a2c4c973625931d48f3393c8f09a033bf</anchor>
      <arglist>(const Teuchos::ParameterList &amp;List)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Apply</name>
      <anchorfile>classML__Epetra_1_1MultiLevelPreconditioner.html</anchorfile>
      <anchor>ace6c652e9d298d201ac312b34d523e06</anchor>
      <arglist>(const Epetra_MultiVector &amp;X, Epetra_MultiVector &amp;Y) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ApplyInverse</name>
      <anchorfile>classML__Epetra_1_1MultiLevelPreconditioner.html</anchorfile>
      <anchor>a599fc670f497b35621d2ce445149a4df</anchor>
      <arglist>(const Epetra_MultiVector &amp;X, Epetra_MultiVector &amp;Y) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ComputePreconditioner</name>
      <anchorfile>classML__Epetra_1_1MultiLevelPreconditioner.html</anchorfile>
      <anchor>a0a5c1d47c6938d2ec1cb9bb710723c1e</anchor>
      <arglist>(const bool CheckFiltering=false)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ReComputePreconditioner</name>
      <anchorfile>classML__Epetra_1_1MultiLevelPreconditioner.html</anchorfile>
      <anchor>a1ab166a38be6d3d6b9c3400f256af9a4</anchor>
      <arglist>(bool keepFineLevelSmoother=false)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Print</name>
      <anchorfile>classML__Epetra_1_1MultiLevelPreconditioner.html</anchorfile>
      <anchor>a9303867b4ffe267f3962ab66f36d21e1</anchor>
      <arglist>(int level=-2)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>IsPreconditionerComputed</name>
      <anchorfile>classML__Epetra_1_1MultiLevelPreconditioner.html</anchorfile>
      <anchor>a97708c39466af51074751d00c9031aae</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetOwnership</name>
      <anchorfile>classML__Epetra_1_1MultiLevelPreconditioner.html</anchorfile>
      <anchor>aad8d7791705f87deab0b4b2523f8ea53</anchor>
      <arglist>(bool ownership)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetUseTranspose</name>
      <anchorfile>classML__Epetra_1_1MultiLevelPreconditioner.html</anchorfile>
      <anchor>a5a77fd5fed144e13812e24353b37a9ef</anchor>
      <arglist>(bool useTranspose)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>NormInf</name>
      <anchorfile>classML__Epetra_1_1MultiLevelPreconditioner.html</anchorfile>
      <anchor>aa6f1db14e9b191f4083d416353ff319b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>UseTranspose</name>
      <anchorfile>classML__Epetra_1_1MultiLevelPreconditioner.html</anchorfile>
      <anchor>a2b899af6afdba06f6be787885eb7e40d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>HasNormInf</name>
      <anchorfile>classML__Epetra_1_1MultiLevelPreconditioner.html</anchorfile>
      <anchor>a6ba838acc35d6a4e8a81ce10fa223935</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_Comm &amp;</type>
      <name>Comm</name>
      <anchorfile>classML__Epetra_1_1MultiLevelPreconditioner.html</anchorfile>
      <anchor>aa644fcae68586400fdc8e7fd21fc0528</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_Map &amp;</type>
      <name>OperatorDomainMap</name>
      <anchorfile>classML__Epetra_1_1MultiLevelPreconditioner.html</anchorfile>
      <anchor>a4314da047c70fb2db4ac037c77bf4b9b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_Map &amp;</type>
      <name>OperatorRangeMap</name>
      <anchorfile>classML__Epetra_1_1MultiLevelPreconditioner.html</anchorfile>
      <anchor>aba73158e1130ee3cbd07685658c65553</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>MultiLevelPreconditioner</name>
      <anchorfile>classML__Epetra_1_1MultiLevelPreconditioner.html</anchorfile>
      <anchor>a67347841c24bebda9e38ad628db145ba</anchor>
      <arglist>(const Epetra_RowMatrix &amp;RowMatrix, const bool ComputePrec=true)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>MultiLevelPreconditioner</name>
      <anchorfile>classML__Epetra_1_1MultiLevelPreconditioner.html</anchorfile>
      <anchor>a86ce4d3dd21908f8379fcf0ae41d2ffc</anchor>
      <arglist>(const Epetra_RowMatrix &amp;RowMatrix, const Teuchos::ParameterList &amp;List, const bool ComputePrec=true)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>MultiLevelPreconditioner</name>
      <anchorfile>classML__Epetra_1_1MultiLevelPreconditioner.html</anchorfile>
      <anchor>a809f3f842ef718ef97fc7b27a6ba21b5</anchor>
      <arglist>(ML_Operator *Operator, const Teuchos::ParameterList &amp;List, const bool ComputePrec=true)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>MultiLevelPreconditioner</name>
      <anchorfile>classML__Epetra_1_1MultiLevelPreconditioner.html</anchorfile>
      <anchor>a953ea2d18629c19c0b67e0a28338718a</anchor>
      <arglist>(ML_Operator *Operator, const Teuchos::ParameterList &amp;List, Epetra_RowMatrix **DiagOperators, Teuchos::ParameterList *DiagLists, int NBlocks=1, const bool ComputePrec=true)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>MultiLevelPreconditioner</name>
      <anchorfile>classML__Epetra_1_1MultiLevelPreconditioner.html</anchorfile>
      <anchor>a59203ed1c62ac76884e252f50e05a405</anchor>
      <arglist>(const Epetra_RowMatrix &amp;EdgeMatrix, const Epetra_RowMatrix &amp;GradMatrix, const Epetra_RowMatrix &amp;NodeMatrix, const Teuchos::ParameterList &amp;List, const bool ComputePrec=true, const bool UseNodeMatrixForSmoother=false)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>MultiLevelPreconditioner</name>
      <anchorfile>classML__Epetra_1_1MultiLevelPreconditioner.html</anchorfile>
      <anchor>a0ecdb34d13aaceb48767950ed50d1b24</anchor>
      <arglist>(const Epetra_RowMatrix &amp;CurlCurlMatrix, const Epetra_RowMatrix &amp;MassMatrix, const Epetra_RowMatrix &amp;TMatrix, const Epetra_RowMatrix &amp;NodeMatrix, const Teuchos::ParameterList &amp;List, const bool ComputePrec=true)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>MultiLevelPreconditioner</name>
      <anchorfile>classML__Epetra_1_1MultiLevelPreconditioner.html</anchorfile>
      <anchor>a0e3e3380ddad9bf64d3bf36bc3802f8f</anchor>
      <arglist>(Epetra_RowMatrix &amp;RowMatrix, const Teuchos::ParameterList &amp;List, const int &amp;nNodes, const int &amp;maxDofPerNode, bool *dofPresent, Epetra_Vector &amp;Lhs, Epetra_Vector &amp;Rhs, const bool rhsAndsolProvided, const bool ComputePrec=true)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>MultiLevelPreconditioner</name>
      <anchorfile>classML__Epetra_1_1MultiLevelPreconditioner.html</anchorfile>
      <anchor>a5100c460d7d4f8ad0ba4819266393247</anchor>
      <arglist>(Epetra_RowMatrix &amp;RowMatrix, const Teuchos::ParameterList &amp;List, const double distTol,   const double tol,   Epetra_Vector &amp;Lhs, Epetra_Vector &amp;Rhs, const bool rhsAndsolProvided, const bool ComputePrec=true)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>MultiLevelPreconditioner</name>
      <anchorfile>classML__Epetra_1_1MultiLevelPreconditioner.html</anchorfile>
      <anchor>a5dd2ea24704e439cc3e87df1923cc883</anchor>
      <arglist>(const Epetra_MsrMatrix &amp;EdgeMatrix, ML_Operator *GradMatrix, AZ_MATRIX *NodeMatrix, int *proc_config, const Teuchos::ParameterList &amp;List, const bool ComputePrec=true)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~MultiLevelPreconditioner</name>
      <anchorfile>classML__Epetra_1_1MultiLevelPreconditioner.html</anchorfile>
      <anchor>a8b15a8eb8beeaddc47e1eb96061e982d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const char *</type>
      <name>Label</name>
      <anchorfile>classML__Epetra_1_1MultiLevelPreconditioner.html</anchorfile>
      <anchor>a5ef687b3bdbffb21cead84252b1ee6af</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>PrintUnused</name>
      <anchorfile>classML__Epetra_1_1MultiLevelPreconditioner.html</anchorfile>
      <anchor>a7f740f61bd18078a9d96fd2fa9b0179c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>PrintUnused</name>
      <anchorfile>classML__Epetra_1_1MultiLevelPreconditioner.html</anchorfile>
      <anchor>a1d190e002859b685d68e7964bab5e1b6</anchor>
      <arglist>(std::ostream &amp;os) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>PrintUnused</name>
      <anchorfile>classML__Epetra_1_1MultiLevelPreconditioner.html</anchorfile>
      <anchor>a64d70645c93c60bdb8cfa598c223dda1</anchor>
      <arglist>(const int MyPID) const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::ParameterList &amp;</type>
      <name>GetList</name>
      <anchorfile>classML__Epetra_1_1MultiLevelPreconditioner.html</anchorfile>
      <anchor>aea04faceca753615b34eee8794f50698</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>PrintList</name>
      <anchorfile>classML__Epetra_1_1MultiLevelPreconditioner.html</anchorfile>
      <anchor>a2df61ccbf8cefd809ea6880c2ac0ed9c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetParameterList</name>
      <anchorfile>classML__Epetra_1_1MultiLevelPreconditioner.html</anchorfile>
      <anchor>a2c4c973625931d48f3393c8f09a033bf</anchor>
      <arglist>(const Teuchos::ParameterList &amp;List)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Apply</name>
      <anchorfile>classML__Epetra_1_1MultiLevelPreconditioner.html</anchorfile>
      <anchor>ace6c652e9d298d201ac312b34d523e06</anchor>
      <arglist>(const Epetra_MultiVector &amp;X, Epetra_MultiVector &amp;Y) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ApplyInverse</name>
      <anchorfile>classML__Epetra_1_1MultiLevelPreconditioner.html</anchorfile>
      <anchor>a599fc670f497b35621d2ce445149a4df</anchor>
      <arglist>(const Epetra_MultiVector &amp;X, Epetra_MultiVector &amp;Y) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ComputePreconditioner</name>
      <anchorfile>classML__Epetra_1_1MultiLevelPreconditioner.html</anchorfile>
      <anchor>a0a5c1d47c6938d2ec1cb9bb710723c1e</anchor>
      <arglist>(const bool CheckFiltering=false)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ReComputePreconditioner</name>
      <anchorfile>classML__Epetra_1_1MultiLevelPreconditioner.html</anchorfile>
      <anchor>a1ab166a38be6d3d6b9c3400f256af9a4</anchor>
      <arglist>(bool keepFineLevelSmoother=false)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Print</name>
      <anchorfile>classML__Epetra_1_1MultiLevelPreconditioner.html</anchorfile>
      <anchor>a9303867b4ffe267f3962ab66f36d21e1</anchor>
      <arglist>(int level=-2)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>IsPreconditionerComputed</name>
      <anchorfile>classML__Epetra_1_1MultiLevelPreconditioner.html</anchorfile>
      <anchor>a97708c39466af51074751d00c9031aae</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetOwnership</name>
      <anchorfile>classML__Epetra_1_1MultiLevelPreconditioner.html</anchorfile>
      <anchor>aad8d7791705f87deab0b4b2523f8ea53</anchor>
      <arglist>(bool ownership)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetUseTranspose</name>
      <anchorfile>classML__Epetra_1_1MultiLevelPreconditioner.html</anchorfile>
      <anchor>a5a77fd5fed144e13812e24353b37a9ef</anchor>
      <arglist>(bool useTranspose)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>NormInf</name>
      <anchorfile>classML__Epetra_1_1MultiLevelPreconditioner.html</anchorfile>
      <anchor>aa6f1db14e9b191f4083d416353ff319b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>UseTranspose</name>
      <anchorfile>classML__Epetra_1_1MultiLevelPreconditioner.html</anchorfile>
      <anchor>a2b899af6afdba06f6be787885eb7e40d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>HasNormInf</name>
      <anchorfile>classML__Epetra_1_1MultiLevelPreconditioner.html</anchorfile>
      <anchor>a6ba838acc35d6a4e8a81ce10fa223935</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_Comm &amp;</type>
      <name>Comm</name>
      <anchorfile>classML__Epetra_1_1MultiLevelPreconditioner.html</anchorfile>
      <anchor>aa644fcae68586400fdc8e7fd21fc0528</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_Map &amp;</type>
      <name>OperatorDomainMap</name>
      <anchorfile>classML__Epetra_1_1MultiLevelPreconditioner.html</anchorfile>
      <anchor>a4314da047c70fb2db4ac037c77bf4b9b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_Map &amp;</type>
      <name>OperatorRangeMap</name>
      <anchorfile>classML__Epetra_1_1MultiLevelPreconditioner.html</anchorfile>
      <anchor>aba73158e1130ee3cbd07685658c65553</anchor>
      <arglist>() const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>MultiLevelPreconditioner</name>
    <filename>classMultiLevelPreconditioner.html</filename>
  </compound>
  <compound kind="class">
    <name>MLAPI::MultiLevelSA</name>
    <filename>classMLAPI_1_1MultiLevelSA.html</filename>
    <base>MLAPI::BaseOperator</base>
    <base>MLAPI::CompObject</base>
    <base>MLAPI::TimeObject</base>
    <member kind="function">
      <type></type>
      <name>MultiLevelSA</name>
      <anchorfile>classMLAPI_1_1MultiLevelSA.html</anchorfile>
      <anchor>ad7f66d20cfeabcd6dcbcb3e03c5b90b6</anchor>
      <arglist>(const Operator &amp;FineMatrix, Teuchos::ParameterList &amp;List, const bool ConstructNow=true)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~MultiLevelSA</name>
      <anchorfile>classMLAPI_1_1MultiLevelSA.html</anchorfile>
      <anchor>a7e5aa24eff43a7b2e95661218a54a715</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const Space</type>
      <name>GetOperatorDomainSpace</name>
      <anchorfile>classMLAPI_1_1MultiLevelSA.html</anchorfile>
      <anchor>a59bcbe1cd31fcf655a5121f674b8a936</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Space</type>
      <name>GetOperatorRangeSpace</name>
      <anchorfile>classMLAPI_1_1MultiLevelSA.html</anchorfile>
      <anchor>a7546e1c0305c72f00f796eb2cf066dc1</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Space</type>
      <name>GetDomainSpace</name>
      <anchorfile>classMLAPI_1_1MultiLevelSA.html</anchorfile>
      <anchor>a0239175527a820d2355599b499d0ba9a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Space</type>
      <name>GetRangeSpace</name>
      <anchorfile>classMLAPI_1_1MultiLevelSA.html</anchorfile>
      <anchor>a3067e1566e55f3f2b6fe0d71b8b37d0e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Operator &amp;</type>
      <name>R</name>
      <anchorfile>classMLAPI_1_1MultiLevelSA.html</anchorfile>
      <anchor>a6320304122928c45f5f9c4d3f4878ab0</anchor>
      <arglist>(const int i) const </arglist>
    </member>
    <member kind="function">
      <type>const Operator &amp;</type>
      <name>A</name>
      <anchorfile>classMLAPI_1_1MultiLevelSA.html</anchorfile>
      <anchor>a0c65eaa87baca9cc5fc7e04da69c1371</anchor>
      <arglist>(const int i) const </arglist>
    </member>
    <member kind="function">
      <type>const Operator &amp;</type>
      <name>P</name>
      <anchorfile>classMLAPI_1_1MultiLevelSA.html</anchorfile>
      <anchor>a512e1daf680a8953b2824ab5281e8f96</anchor>
      <arglist>(const int i) const </arglist>
    </member>
    <member kind="function">
      <type>const InverseOperator &amp;</type>
      <name>S</name>
      <anchorfile>classMLAPI_1_1MultiLevelSA.html</anchorfile>
      <anchor>a1fd5dd2176caaac683d909b60c5e0ea8</anchor>
      <arglist>(const int i) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetMaxLevels</name>
      <anchorfile>classMLAPI_1_1MultiLevelSA.html</anchorfile>
      <anchor>a5bdcd0fcf472e3e0d97fc0e38c1ef2ec</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>IsComputed</name>
      <anchorfile>classMLAPI_1_1MultiLevelSA.html</anchorfile>
      <anchor>aa61c6e11961d50ef2241e5128c5e7aa6</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Compute</name>
      <anchorfile>classMLAPI_1_1MultiLevelSA.html</anchorfile>
      <anchor>ac9935f186429f8bf5539c0ef2406148b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Apply</name>
      <anchorfile>classMLAPI_1_1MultiLevelSA.html</anchorfile>
      <anchor>a4108cf9545fab5d893964fa088d54175</anchor>
      <arglist>(const MultiVector &amp;b_f, MultiVector &amp;x_f) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SolveMultiLevelSA</name>
      <anchorfile>classMLAPI_1_1MultiLevelSA.html</anchorfile>
      <anchor>ae7c9bf54e9416eabc37bffa1955df004</anchor>
      <arglist>(const MultiVector &amp;b_f, MultiVector &amp;x_f, int level) const </arglist>
    </member>
    <member kind="function">
      <type>std::ostream &amp;</type>
      <name>Print</name>
      <anchorfile>classMLAPI_1_1MultiLevelSA.html</anchorfile>
      <anchor>ab31e59a7e91341a19626d4f6e43ddd91</anchor>
      <arglist>(std::ostream &amp;os, const bool verbose=true) const </arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>MultiLevelSA</name>
      <anchorfile>classMLAPI_1_1MultiLevelSA.html</anchorfile>
      <anchor>ad7f66d20cfeabcd6dcbcb3e03c5b90b6</anchor>
      <arglist>(const Operator &amp;FineMatrix, Teuchos::ParameterList &amp;List, const bool ConstructNow=true)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~MultiLevelSA</name>
      <anchorfile>classMLAPI_1_1MultiLevelSA.html</anchorfile>
      <anchor>a7e5aa24eff43a7b2e95661218a54a715</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const Space</type>
      <name>GetOperatorDomainSpace</name>
      <anchorfile>classMLAPI_1_1MultiLevelSA.html</anchorfile>
      <anchor>a59bcbe1cd31fcf655a5121f674b8a936</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Space</type>
      <name>GetOperatorRangeSpace</name>
      <anchorfile>classMLAPI_1_1MultiLevelSA.html</anchorfile>
      <anchor>a7546e1c0305c72f00f796eb2cf066dc1</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Space</type>
      <name>GetDomainSpace</name>
      <anchorfile>classMLAPI_1_1MultiLevelSA.html</anchorfile>
      <anchor>a0239175527a820d2355599b499d0ba9a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Space</type>
      <name>GetRangeSpace</name>
      <anchorfile>classMLAPI_1_1MultiLevelSA.html</anchorfile>
      <anchor>a3067e1566e55f3f2b6fe0d71b8b37d0e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Operator &amp;</type>
      <name>R</name>
      <anchorfile>classMLAPI_1_1MultiLevelSA.html</anchorfile>
      <anchor>a6320304122928c45f5f9c4d3f4878ab0</anchor>
      <arglist>(const int i) const </arglist>
    </member>
    <member kind="function">
      <type>const Operator &amp;</type>
      <name>A</name>
      <anchorfile>classMLAPI_1_1MultiLevelSA.html</anchorfile>
      <anchor>a0c65eaa87baca9cc5fc7e04da69c1371</anchor>
      <arglist>(const int i) const </arglist>
    </member>
    <member kind="function">
      <type>const Operator &amp;</type>
      <name>P</name>
      <anchorfile>classMLAPI_1_1MultiLevelSA.html</anchorfile>
      <anchor>a512e1daf680a8953b2824ab5281e8f96</anchor>
      <arglist>(const int i) const </arglist>
    </member>
    <member kind="function">
      <type>const InverseOperator &amp;</type>
      <name>S</name>
      <anchorfile>classMLAPI_1_1MultiLevelSA.html</anchorfile>
      <anchor>a1fd5dd2176caaac683d909b60c5e0ea8</anchor>
      <arglist>(const int i) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetMaxLevels</name>
      <anchorfile>classMLAPI_1_1MultiLevelSA.html</anchorfile>
      <anchor>a5bdcd0fcf472e3e0d97fc0e38c1ef2ec</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>IsComputed</name>
      <anchorfile>classMLAPI_1_1MultiLevelSA.html</anchorfile>
      <anchor>aa61c6e11961d50ef2241e5128c5e7aa6</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Compute</name>
      <anchorfile>classMLAPI_1_1MultiLevelSA.html</anchorfile>
      <anchor>ac9935f186429f8bf5539c0ef2406148b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Apply</name>
      <anchorfile>classMLAPI_1_1MultiLevelSA.html</anchorfile>
      <anchor>a4108cf9545fab5d893964fa088d54175</anchor>
      <arglist>(const MultiVector &amp;b_f, MultiVector &amp;x_f) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SolveMultiLevelSA</name>
      <anchorfile>classMLAPI_1_1MultiLevelSA.html</anchorfile>
      <anchor>ae7c9bf54e9416eabc37bffa1955df004</anchor>
      <arglist>(const MultiVector &amp;b_f, MultiVector &amp;x_f, int level) const </arglist>
    </member>
    <member kind="function">
      <type>std::ostream &amp;</type>
      <name>Print</name>
      <anchorfile>classMLAPI_1_1MultiLevelSA.html</anchorfile>
      <anchor>ab31e59a7e91341a19626d4f6e43ddd91</anchor>
      <arglist>(std::ostream &amp;os, const bool verbose=true) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>MLAPI::MultiVector</name>
    <filename>classMLAPI_1_1MultiVector.html</filename>
    <base>MLAPI::BaseObject</base>
    <base>MLAPI::CompObject</base>
    <base>MLAPI::TimeObject</base>
    <member kind="function">
      <type></type>
      <name>MultiVector</name>
      <anchorfile>classMLAPI_1_1MultiVector.html</anchorfile>
      <anchor>a05f7db2f62741c4935d52cbee4a62992</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>MultiVector</name>
      <anchorfile>classMLAPI_1_1MultiVector.html</anchorfile>
      <anchor>a648fa9dca7baf7ecbf0a2e88f8832de2</anchor>
      <arglist>(const Space &amp;VectorSpace, const int NumVectors=1, bool SetToZero=true)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>MultiVector</name>
      <anchorfile>classMLAPI_1_1MultiVector.html</anchorfile>
      <anchor>a460d0d4c4522f86d747764bbd3a5d326</anchor>
      <arglist>(const Space &amp;VectorSpace, double **Values, const int NumVectors=1)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>MultiVector</name>
      <anchorfile>classMLAPI_1_1MultiVector.html</anchorfile>
      <anchor>a808ee5633e98814ff85499052530d319</anchor>
      <arglist>(const Space &amp;VectorSpace, Teuchos::RefCountPtr&lt; DoubleVector &gt; RCPValues)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>MultiVector</name>
      <anchorfile>classMLAPI_1_1MultiVector.html</anchorfile>
      <anchor>ab3e15bf4720de1d22627da88ba0fe8bd</anchor>
      <arglist>(const Space &amp;VectorSpace, std::vector&lt; Teuchos::RefCountPtr&lt; DoubleVector &gt; &gt; RCPValues)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>MultiVector</name>
      <anchorfile>classMLAPI_1_1MultiVector.html</anchorfile>
      <anchor>aec2ae6d3d2177218c7370b7906e54844</anchor>
      <arglist>(const MultiVector &amp;rhs)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~MultiVector</name>
      <anchorfile>classMLAPI_1_1MultiVector.html</anchorfile>
      <anchor>a080f6e7d354dfc79d18982083b2ed20b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Reshape</name>
      <anchorfile>classMLAPI_1_1MultiVector.html</anchorfile>
      <anchor>aaafa91b53c6c25c7be05b6e184f6000a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Reshape</name>
      <anchorfile>classMLAPI_1_1MultiVector.html</anchorfile>
      <anchor>a6eb3b896c91677b99bf44c7b43842097</anchor>
      <arglist>(const Space &amp;S, const int NumVectors=1, const bool SetToZero=true)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Append</name>
      <anchorfile>classMLAPI_1_1MultiVector.html</anchorfile>
      <anchor>afbe83ecbab7f57c2cdde2102237c8ff7</anchor>
      <arglist>(const int NumVectors=1, const bool SetToZero=true)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Append</name>
      <anchorfile>classMLAPI_1_1MultiVector.html</anchorfile>
      <anchor>aeab7460b0cb07e3fa9849e9423c39276</anchor>
      <arglist>(const MultiVector &amp;rhs)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Delete</name>
      <anchorfile>classMLAPI_1_1MultiVector.html</anchorfile>
      <anchor>a1554e745a784592c28f75a453bb3988e</anchor>
      <arglist>(const int v)</arglist>
    </member>
    <member kind="function">
      <type>MultiVector &amp;</type>
      <name>operator=</name>
      <anchorfile>classMLAPI_1_1MultiVector.html</anchorfile>
      <anchor>adc37b805cf246418a0abcc7c3f3c2a64</anchor>
      <arglist>(double rhs)</arglist>
    </member>
    <member kind="function">
      <type>MultiVector &amp;</type>
      <name>operator=</name>
      <anchorfile>classMLAPI_1_1MultiVector.html</anchorfile>
      <anchor>afdd02275159fa8d464a441fe69f8f344</anchor>
      <arglist>(const MultiVector &amp;rhs)</arglist>
    </member>
    <member kind="function">
      <type>MultiVector &amp;</type>
      <name>operator=</name>
      <anchorfile>classMLAPI_1_1MultiVector.html</anchorfile>
      <anchor>ae817d9b849e3c0a3193e5cba51d11d74</anchor>
      <arglist>(const BaseLinearCombination &amp;rhs)</arglist>
    </member>
    <member kind="function">
      <type>MultiVector &amp;</type>
      <name>operator=</name>
      <anchorfile>classMLAPI_1_1MultiVector.html</anchorfile>
      <anchor>ad593903ed20aae07aeb0413160947e3f</anchor>
      <arglist>(const std::string &amp;Label)</arglist>
    </member>
    <member kind="function">
      <type>const double &amp;</type>
      <name>operator()</name>
      <anchorfile>classMLAPI_1_1MultiVector.html</anchorfile>
      <anchor>aec88368b220c886b64b7a7d890f4dd01</anchor>
      <arglist>(const int i) const </arglist>
    </member>
    <member kind="function">
      <type>double &amp;</type>
      <name>operator()</name>
      <anchorfile>classMLAPI_1_1MultiVector.html</anchorfile>
      <anchor>a97faa872a0e3b06a7b8e527055b4226a</anchor>
      <arglist>(const int i)</arglist>
    </member>
    <member kind="function">
      <type>const double &amp;</type>
      <name>operator()</name>
      <anchorfile>classMLAPI_1_1MultiVector.html</anchorfile>
      <anchor>a46785e818492e1586387eccc543b1905</anchor>
      <arglist>(const int i, const int v) const </arglist>
    </member>
    <member kind="function">
      <type>double &amp;</type>
      <name>operator()</name>
      <anchorfile>classMLAPI_1_1MultiVector.html</anchorfile>
      <anchor>a91f9eec0a0e372c71aca9a5c79351ee8</anchor>
      <arglist>(const int i, const int v)</arglist>
    </member>
    <member kind="function">
      <type>const Space &amp;</type>
      <name>GetVectorSpace</name>
      <anchorfile>classMLAPI_1_1MultiVector.html</anchorfile>
      <anchor>a6b85479121a305a379676642eb14284a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Space &amp;</type>
      <name>GetVectorSpace</name>
      <anchorfile>classMLAPI_1_1MultiVector.html</anchorfile>
      <anchor>aa77254fdf0c69c8f37a06deed30793e4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetNumVectors</name>
      <anchorfile>classMLAPI_1_1MultiVector.html</anchorfile>
      <anchor>a57210a53246da2d651a138628c278eb8</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetMyLength</name>
      <anchorfile>classMLAPI_1_1MultiVector.html</anchorfile>
      <anchor>ad2672ceb8b21dbd13e26d2b15419c061</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetGlobalLength</name>
      <anchorfile>classMLAPI_1_1MultiVector.html</anchorfile>
      <anchor>a27dd48d56c521ebad2e05a9498111c14</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>double *</type>
      <name>GetValues</name>
      <anchorfile>classMLAPI_1_1MultiVector.html</anchorfile>
      <anchor>a5697bc147c7c1764b70d8e09ec9efbbd</anchor>
      <arglist>(const int v)</arglist>
    </member>
    <member kind="function">
      <type>const double *</type>
      <name>GetValues</name>
      <anchorfile>classMLAPI_1_1MultiVector.html</anchorfile>
      <anchor>ad13e3217c1cc5ee2d1c25d5afd6f1385</anchor>
      <arglist>(const int v) const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RefCountPtr&lt; DoubleVector &gt; &amp;</type>
      <name>GetRCPValues</name>
      <anchorfile>classMLAPI_1_1MultiVector.html</anchorfile>
      <anchor>a555bab23f6c80669a7c7219a21dda910</anchor>
      <arglist>(const int v)</arglist>
    </member>
    <member kind="function">
      <type>const Teuchos::RefCountPtr&lt; DoubleVector &gt; &amp;</type>
      <name>GetRCPValues</name>
      <anchorfile>classMLAPI_1_1MultiVector.html</anchorfile>
      <anchor>ac14af25e42d0f815fff206a369561129</anchor>
      <arglist>(const int v) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetRCPValues</name>
      <anchorfile>classMLAPI_1_1MultiVector.html</anchorfile>
      <anchor>a176c3270f3e75510104ccaa24ed31cbf</anchor>
      <arglist>(const Teuchos::RefCountPtr&lt; DoubleVector &gt; &amp;RCPValues, const int v)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Update</name>
      <anchorfile>classMLAPI_1_1MultiVector.html</anchorfile>
      <anchor>a2e66ff9b6248497ee1388499d5b3061a</anchor>
      <arglist>(const double alpha, int v=-1)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Update</name>
      <anchorfile>classMLAPI_1_1MultiVector.html</anchorfile>
      <anchor>aea60486efbe029f319ac4ce1f75d7cbe</anchor>
      <arglist>(const MultiVector &amp;rhs)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Update</name>
      <anchorfile>classMLAPI_1_1MultiVector.html</anchorfile>
      <anchor>ab1bbba324e07a2ea0ff3661b78c8f498</anchor>
      <arglist>(double alpha, const MultiVector &amp;rhs)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Update</name>
      <anchorfile>classMLAPI_1_1MultiVector.html</anchorfile>
      <anchor>ab3458cfc63b1fe6b082ded831cf52320</anchor>
      <arglist>(double alpha, const MultiVector &amp;x, double beta, const MultiVector &amp;y)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Update</name>
      <anchorfile>classMLAPI_1_1MultiVector.html</anchorfile>
      <anchor>ac535fbc0f2df65e84ae4d012b008412c</anchor>
      <arglist>(double alpha, const MultiVector &amp;rhs, double beta)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>DotProduct</name>
      <anchorfile>classMLAPI_1_1MultiVector.html</anchorfile>
      <anchor>aad9f383573d3d10efdc841c4a5d342b8</anchor>
      <arglist>(const MultiVector &amp;rhs, int v=-1) const </arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>Norm2</name>
      <anchorfile>classMLAPI_1_1MultiVector.html</anchorfile>
      <anchor>af5101e2c6ff2f5de0de558802767d5d4</anchor>
      <arglist>(int v=-1) const </arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>NormInf</name>
      <anchorfile>classMLAPI_1_1MultiVector.html</anchorfile>
      <anchor>a0bce9b1ee212c85c7d3e1444a1fbc62b</anchor>
      <arglist>(int v=-1) const </arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>NormOne</name>
      <anchorfile>classMLAPI_1_1MultiVector.html</anchorfile>
      <anchor>a4b3bd2036bbf563c0fb7482df40b360c</anchor>
      <arglist>(int v=-1) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Reciprocal</name>
      <anchorfile>classMLAPI_1_1MultiVector.html</anchorfile>
      <anchor>afc1fa0bc30595c29f571d0988e0abaaf</anchor>
      <arglist>(int v=-1)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Scale</name>
      <anchorfile>classMLAPI_1_1MultiVector.html</anchorfile>
      <anchor>aafb02e3122406b20b026bfc40fdd5993</anchor>
      <arglist>(const double Factor, int v=-1)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Random</name>
      <anchorfile>classMLAPI_1_1MultiVector.html</anchorfile>
      <anchor>a4a25679c110217e951fdbcb84bd3d68c</anchor>
      <arglist>(int v=-1)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Sort</name>
      <anchorfile>classMLAPI_1_1MultiVector.html</anchorfile>
      <anchor>a7102ac4759b5f0444c04a34fb4dd3e49</anchor>
      <arglist>(int v=-1, const bool IsIncreasing=false)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual std::ostream &amp;</type>
      <name>Print</name>
      <anchorfile>classMLAPI_1_1MultiVector.html</anchorfile>
      <anchor>adbaecca7f6e0764008853fc1af46a80f</anchor>
      <arglist>(std::ostream &amp;os, const bool verbose=true) const </arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>MultiVector</name>
      <anchorfile>classMLAPI_1_1MultiVector.html</anchorfile>
      <anchor>a05f7db2f62741c4935d52cbee4a62992</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>MultiVector</name>
      <anchorfile>classMLAPI_1_1MultiVector.html</anchorfile>
      <anchor>a648fa9dca7baf7ecbf0a2e88f8832de2</anchor>
      <arglist>(const Space &amp;VectorSpace, const int NumVectors=1, bool SetToZero=true)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>MultiVector</name>
      <anchorfile>classMLAPI_1_1MultiVector.html</anchorfile>
      <anchor>a460d0d4c4522f86d747764bbd3a5d326</anchor>
      <arglist>(const Space &amp;VectorSpace, double **Values, const int NumVectors=1)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>MultiVector</name>
      <anchorfile>classMLAPI_1_1MultiVector.html</anchorfile>
      <anchor>a808ee5633e98814ff85499052530d319</anchor>
      <arglist>(const Space &amp;VectorSpace, Teuchos::RefCountPtr&lt; DoubleVector &gt; RCPValues)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>MultiVector</name>
      <anchorfile>classMLAPI_1_1MultiVector.html</anchorfile>
      <anchor>ab3e15bf4720de1d22627da88ba0fe8bd</anchor>
      <arglist>(const Space &amp;VectorSpace, std::vector&lt; Teuchos::RefCountPtr&lt; DoubleVector &gt; &gt; RCPValues)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>MultiVector</name>
      <anchorfile>classMLAPI_1_1MultiVector.html</anchorfile>
      <anchor>aec2ae6d3d2177218c7370b7906e54844</anchor>
      <arglist>(const MultiVector &amp;rhs)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~MultiVector</name>
      <anchorfile>classMLAPI_1_1MultiVector.html</anchorfile>
      <anchor>a080f6e7d354dfc79d18982083b2ed20b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Reshape</name>
      <anchorfile>classMLAPI_1_1MultiVector.html</anchorfile>
      <anchor>aaafa91b53c6c25c7be05b6e184f6000a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Reshape</name>
      <anchorfile>classMLAPI_1_1MultiVector.html</anchorfile>
      <anchor>a6eb3b896c91677b99bf44c7b43842097</anchor>
      <arglist>(const Space &amp;S, const int NumVectors=1, const bool SetToZero=true)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Append</name>
      <anchorfile>classMLAPI_1_1MultiVector.html</anchorfile>
      <anchor>afbe83ecbab7f57c2cdde2102237c8ff7</anchor>
      <arglist>(const int NumVectors=1, const bool SetToZero=true)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Append</name>
      <anchorfile>classMLAPI_1_1MultiVector.html</anchorfile>
      <anchor>aeab7460b0cb07e3fa9849e9423c39276</anchor>
      <arglist>(const MultiVector &amp;rhs)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Delete</name>
      <anchorfile>classMLAPI_1_1MultiVector.html</anchorfile>
      <anchor>a1554e745a784592c28f75a453bb3988e</anchor>
      <arglist>(const int v)</arglist>
    </member>
    <member kind="function">
      <type>MultiVector &amp;</type>
      <name>operator=</name>
      <anchorfile>classMLAPI_1_1MultiVector.html</anchorfile>
      <anchor>adc37b805cf246418a0abcc7c3f3c2a64</anchor>
      <arglist>(double rhs)</arglist>
    </member>
    <member kind="function">
      <type>MultiVector &amp;</type>
      <name>operator=</name>
      <anchorfile>classMLAPI_1_1MultiVector.html</anchorfile>
      <anchor>afdd02275159fa8d464a441fe69f8f344</anchor>
      <arglist>(const MultiVector &amp;rhs)</arglist>
    </member>
    <member kind="function">
      <type>MultiVector &amp;</type>
      <name>operator=</name>
      <anchorfile>classMLAPI_1_1MultiVector.html</anchorfile>
      <anchor>ae817d9b849e3c0a3193e5cba51d11d74</anchor>
      <arglist>(const BaseLinearCombination &amp;rhs)</arglist>
    </member>
    <member kind="function">
      <type>MultiVector &amp;</type>
      <name>operator=</name>
      <anchorfile>classMLAPI_1_1MultiVector.html</anchorfile>
      <anchor>ad593903ed20aae07aeb0413160947e3f</anchor>
      <arglist>(const std::string &amp;Label)</arglist>
    </member>
    <member kind="function">
      <type>const double &amp;</type>
      <name>operator()</name>
      <anchorfile>classMLAPI_1_1MultiVector.html</anchorfile>
      <anchor>aec88368b220c886b64b7a7d890f4dd01</anchor>
      <arglist>(const int i) const </arglist>
    </member>
    <member kind="function">
      <type>double &amp;</type>
      <name>operator()</name>
      <anchorfile>classMLAPI_1_1MultiVector.html</anchorfile>
      <anchor>a97faa872a0e3b06a7b8e527055b4226a</anchor>
      <arglist>(const int i)</arglist>
    </member>
    <member kind="function">
      <type>const double &amp;</type>
      <name>operator()</name>
      <anchorfile>classMLAPI_1_1MultiVector.html</anchorfile>
      <anchor>a46785e818492e1586387eccc543b1905</anchor>
      <arglist>(const int i, const int v) const </arglist>
    </member>
    <member kind="function">
      <type>double &amp;</type>
      <name>operator()</name>
      <anchorfile>classMLAPI_1_1MultiVector.html</anchorfile>
      <anchor>a91f9eec0a0e372c71aca9a5c79351ee8</anchor>
      <arglist>(const int i, const int v)</arglist>
    </member>
    <member kind="function">
      <type>const Space &amp;</type>
      <name>GetVectorSpace</name>
      <anchorfile>classMLAPI_1_1MultiVector.html</anchorfile>
      <anchor>a6b85479121a305a379676642eb14284a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Space &amp;</type>
      <name>GetVectorSpace</name>
      <anchorfile>classMLAPI_1_1MultiVector.html</anchorfile>
      <anchor>aa77254fdf0c69c8f37a06deed30793e4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetNumVectors</name>
      <anchorfile>classMLAPI_1_1MultiVector.html</anchorfile>
      <anchor>a57210a53246da2d651a138628c278eb8</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetMyLength</name>
      <anchorfile>classMLAPI_1_1MultiVector.html</anchorfile>
      <anchor>ad2672ceb8b21dbd13e26d2b15419c061</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetGlobalLength</name>
      <anchorfile>classMLAPI_1_1MultiVector.html</anchorfile>
      <anchor>a27dd48d56c521ebad2e05a9498111c14</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>double *</type>
      <name>GetValues</name>
      <anchorfile>classMLAPI_1_1MultiVector.html</anchorfile>
      <anchor>a5697bc147c7c1764b70d8e09ec9efbbd</anchor>
      <arglist>(const int v)</arglist>
    </member>
    <member kind="function">
      <type>const double *</type>
      <name>GetValues</name>
      <anchorfile>classMLAPI_1_1MultiVector.html</anchorfile>
      <anchor>ad13e3217c1cc5ee2d1c25d5afd6f1385</anchor>
      <arglist>(const int v) const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RefCountPtr&lt; DoubleVector &gt; &amp;</type>
      <name>GetRCPValues</name>
      <anchorfile>classMLAPI_1_1MultiVector.html</anchorfile>
      <anchor>a555bab23f6c80669a7c7219a21dda910</anchor>
      <arglist>(const int v)</arglist>
    </member>
    <member kind="function">
      <type>const Teuchos::RefCountPtr&lt; DoubleVector &gt; &amp;</type>
      <name>GetRCPValues</name>
      <anchorfile>classMLAPI_1_1MultiVector.html</anchorfile>
      <anchor>ac14af25e42d0f815fff206a369561129</anchor>
      <arglist>(const int v) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetRCPValues</name>
      <anchorfile>classMLAPI_1_1MultiVector.html</anchorfile>
      <anchor>a176c3270f3e75510104ccaa24ed31cbf</anchor>
      <arglist>(const Teuchos::RefCountPtr&lt; DoubleVector &gt; &amp;RCPValues, const int v)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Update</name>
      <anchorfile>classMLAPI_1_1MultiVector.html</anchorfile>
      <anchor>a2e66ff9b6248497ee1388499d5b3061a</anchor>
      <arglist>(const double alpha, int v=-1)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Update</name>
      <anchorfile>classMLAPI_1_1MultiVector.html</anchorfile>
      <anchor>aea60486efbe029f319ac4ce1f75d7cbe</anchor>
      <arglist>(const MultiVector &amp;rhs)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Update</name>
      <anchorfile>classMLAPI_1_1MultiVector.html</anchorfile>
      <anchor>ab1bbba324e07a2ea0ff3661b78c8f498</anchor>
      <arglist>(double alpha, const MultiVector &amp;rhs)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Update</name>
      <anchorfile>classMLAPI_1_1MultiVector.html</anchorfile>
      <anchor>ab3458cfc63b1fe6b082ded831cf52320</anchor>
      <arglist>(double alpha, const MultiVector &amp;x, double beta, const MultiVector &amp;y)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Update</name>
      <anchorfile>classMLAPI_1_1MultiVector.html</anchorfile>
      <anchor>ac535fbc0f2df65e84ae4d012b008412c</anchor>
      <arglist>(double alpha, const MultiVector &amp;rhs, double beta)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>DotProduct</name>
      <anchorfile>classMLAPI_1_1MultiVector.html</anchorfile>
      <anchor>aad9f383573d3d10efdc841c4a5d342b8</anchor>
      <arglist>(const MultiVector &amp;rhs, int v=-1) const </arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>Norm2</name>
      <anchorfile>classMLAPI_1_1MultiVector.html</anchorfile>
      <anchor>af5101e2c6ff2f5de0de558802767d5d4</anchor>
      <arglist>(int v=-1) const </arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>NormInf</name>
      <anchorfile>classMLAPI_1_1MultiVector.html</anchorfile>
      <anchor>a0bce9b1ee212c85c7d3e1444a1fbc62b</anchor>
      <arglist>(int v=-1) const </arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>NormOne</name>
      <anchorfile>classMLAPI_1_1MultiVector.html</anchorfile>
      <anchor>a4b3bd2036bbf563c0fb7482df40b360c</anchor>
      <arglist>(int v=-1) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Reciprocal</name>
      <anchorfile>classMLAPI_1_1MultiVector.html</anchorfile>
      <anchor>afc1fa0bc30595c29f571d0988e0abaaf</anchor>
      <arglist>(int v=-1)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Scale</name>
      <anchorfile>classMLAPI_1_1MultiVector.html</anchorfile>
      <anchor>aafb02e3122406b20b026bfc40fdd5993</anchor>
      <arglist>(const double Factor, int v=-1)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Random</name>
      <anchorfile>classMLAPI_1_1MultiVector.html</anchorfile>
      <anchor>a4a25679c110217e951fdbcb84bd3d68c</anchor>
      <arglist>(int v=-1)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Sort</name>
      <anchorfile>classMLAPI_1_1MultiVector.html</anchorfile>
      <anchor>a7102ac4759b5f0444c04a34fb4dd3e49</anchor>
      <arglist>(int v=-1, const bool IsIncreasing=false)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual std::ostream &amp;</type>
      <name>Print</name>
      <anchorfile>classMLAPI_1_1MultiVector.html</anchorfile>
      <anchor>adbaecca7f6e0764008853fc1af46a80f</anchor>
      <arglist>(std::ostream &amp;os, const bool verbose=true) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>MLAPI::MultiVectorCombination</name>
    <filename>classMLAPI_1_1MultiVectorCombination.html</filename>
    <base>MLAPI::BaseLinearCombination</base>
    <member kind="function">
      <type>const Space</type>
      <name>GetVectorSpace</name>
      <anchorfile>classMLAPI_1_1MultiVectorCombination.html</anchorfile>
      <anchor>a882e03122ef3b50f985aeb95ec6150e6</anchor>
      <arglist>() const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>MLAPI::MultiVectorScaled</name>
    <filename>classMLAPI_1_1MultiVectorScaled.html</filename>
    <base>MLAPI::BaseLinearCombination</base>
    <member kind="function">
      <type>const Space</type>
      <name>GetVectorSpace</name>
      <anchorfile>classMLAPI_1_1MultiVectorScaled.html</anchorfile>
      <anchor>af43083b253d4a7ad734d588acaa60007</anchor>
      <arglist>() const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>MLAPI::Operator</name>
    <filename>classMLAPI_1_1Operator.html</filename>
    <base>MLAPI::BaseOperator</base>
    <base>MLAPI::CompObject</base>
    <base>MLAPI::TimeObject</base>
    <member kind="function">
      <type></type>
      <name>Operator</name>
      <anchorfile>classMLAPI_1_1Operator.html</anchorfile>
      <anchor>a0801e9ac629755b5b7882a9b4271634c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Operator</name>
      <anchorfile>classMLAPI_1_1Operator.html</anchorfile>
      <anchor>a6086105fa8bf779e1cb526f9f771aa4f</anchor>
      <arglist>(const Space &amp;DomainSpace, const Space &amp;RangeSpace, ML_Operator *Op, bool Ownership=true, Teuchos::RefCountPtr&lt; ML_Operator_Box &gt; AuxOp=Teuchos::null)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Operator</name>
      <anchorfile>classMLAPI_1_1Operator.html</anchorfile>
      <anchor>aa42419ddee826a829d8bf36d8d080850</anchor>
      <arglist>(const Space &amp;DomainSpace, const Space &amp;RangeSpace, Epetra_RowMatrix *Matrix, bool Ownership=true, Teuchos::RefCountPtr&lt; ML_Operator_Box &gt; AuxOp=Teuchos::null)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Operator</name>
      <anchorfile>classMLAPI_1_1Operator.html</anchorfile>
      <anchor>abf90b5ead706b259c3ecb914a7aeed22</anchor>
      <arglist>(const Operator &amp;RHS)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~Operator</name>
      <anchorfile>classMLAPI_1_1Operator.html</anchorfile>
      <anchor>a1173e9da8b991ee242f980ab7daca3cf</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Reshape</name>
      <anchorfile>classMLAPI_1_1Operator.html</anchorfile>
      <anchor>ac1f37aefad0f9ed94b77595ad0244a39</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Reshape</name>
      <anchorfile>classMLAPI_1_1Operator.html</anchorfile>
      <anchor>aadbdbb7cbb82991a6457b1b3a79c2562</anchor>
      <arglist>(const Space &amp;DomainSpace, const Space &amp;RangeSpace, ML_Operator *Op, bool Ownership=true, Teuchos::RefCountPtr&lt; ML_Operator_Box &gt; AuxOp=Teuchos::null)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Reshape</name>
      <anchorfile>classMLAPI_1_1Operator.html</anchorfile>
      <anchor>a28830a11b649afcab5f8b98130b5d704</anchor>
      <arglist>(const Space &amp;DomainSpace, const Space &amp;RangeSpace, Epetra_RowMatrix *Matrix, bool Ownership=true, Teuchos::RefCountPtr&lt; ML_Operator_Box &gt; AuxOp=Teuchos::null)</arglist>
    </member>
    <member kind="function">
      <type>Operator &amp;</type>
      <name>operator=</name>
      <anchorfile>classMLAPI_1_1Operator.html</anchorfile>
      <anchor>a55f68334a30a91a013599bd4f57af7b1</anchor>
      <arglist>(const Operator &amp;RHS)</arglist>
    </member>
    <member kind="function">
      <type>Operator &amp;</type>
      <name>operator=</name>
      <anchorfile>classMLAPI_1_1Operator.html</anchorfile>
      <anchor>a10f20546e263ee36b681e5dc6ef68a61</anchor>
      <arglist>(const std::string &amp;Label)</arglist>
    </member>
    <member kind="function">
      <type>const Space</type>
      <name>GetOperatorDomainSpace</name>
      <anchorfile>classMLAPI_1_1Operator.html</anchorfile>
      <anchor>a4748041b5f1eef95d56433a22cfc3107</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Space</type>
      <name>GetOperatorRangeSpace</name>
      <anchorfile>classMLAPI_1_1Operator.html</anchorfile>
      <anchor>a6511bfde6d54c88c86a78e3ac506417f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Space</type>
      <name>GetDomainSpace</name>
      <anchorfile>classMLAPI_1_1Operator.html</anchorfile>
      <anchor>af6a5e272deb62d09bbcc706b166a6431</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Space</type>
      <name>GetRangeSpace</name>
      <anchorfile>classMLAPI_1_1Operator.html</anchorfile>
      <anchor>af4ed327cf369b3dd0247a9629b7ea854</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Space</type>
      <name>GetColumnSpace</name>
      <anchorfile>classMLAPI_1_1Operator.html</anchorfile>
      <anchor>a790531dda1f6079fcb27c45881ee24c1</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetNumGlobalRows</name>
      <anchorfile>classMLAPI_1_1Operator.html</anchorfile>
      <anchor>a83a6452bef25f426276a7c5fb1e68528</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetNumMyRows</name>
      <anchorfile>classMLAPI_1_1Operator.html</anchorfile>
      <anchor>ab6567b0d3496a14119f2a4583059e34f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetNumGlobalCols</name>
      <anchorfile>classMLAPI_1_1Operator.html</anchorfile>
      <anchor>a379f71d4b30d73019b3595f26876793e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetNumMyCols</name>
      <anchorfile>classMLAPI_1_1Operator.html</anchorfile>
      <anchor>a55d13a6571494f25409f855e4eca19dc</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetNumGlobalNonzeros</name>
      <anchorfile>classMLAPI_1_1Operator.html</anchorfile>
      <anchor>a35dad6dfc984f41e1b6da54c1359ddc3</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetNumMyNonzeros</name>
      <anchorfile>classMLAPI_1_1Operator.html</anchorfile>
      <anchor>ada148f9e900a296c41cea5844106f960</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_RowMatrix *</type>
      <name>GetRowMatrix</name>
      <anchorfile>classMLAPI_1_1Operator.html</anchorfile>
      <anchor>a68dc94a755d361a723c8c96d07e5ff6e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>ML_Operator *</type>
      <name>GetML_Operator</name>
      <anchorfile>classMLAPI_1_1Operator.html</anchorfile>
      <anchor>aa31643f0953883c2a7396868e1196cdc</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Teuchos::RefCountPtr&lt; ML_Operator_Box &gt; &amp;</type>
      <name>GetRCPOperatorBox</name>
      <anchorfile>classMLAPI_1_1Operator.html</anchorfile>
      <anchor>ada08eaaf1c6cdf5b6a03b198c9ee636b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Teuchos::RefCountPtr&lt; ML_Operator_Box &gt; &amp;</type>
      <name>GetRCPAuxOperatorBox</name>
      <anchorfile>classMLAPI_1_1Operator.html</anchorfile>
      <anchor>a3014ef5f706a941ddb3703a507e89239</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Teuchos::RefCountPtr&lt; Epetra_RowMatrix &gt; &amp;</type>
      <name>GetRCPRowMatrix</name>
      <anchorfile>classMLAPI_1_1Operator.html</anchorfile>
      <anchor>a6dccc4a05aca865a33f92b4cf24b7a29</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetGRID</name>
      <anchorfile>classMLAPI_1_1Operator.html</anchorfile>
      <anchor>ab2ed95be72ed49db8bca7959c12df6f2</anchor>
      <arglist>(const int LRID) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetGCID</name>
      <anchorfile>classMLAPI_1_1Operator.html</anchorfile>
      <anchor>a20fc2a74ec82b879bc6f2cb977f57f7e</anchor>
      <arglist>(const int LCID) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Apply</name>
      <anchorfile>classMLAPI_1_1Operator.html</anchorfile>
      <anchor>aceb9820540a59543955872f58083ef6b</anchor>
      <arglist>(const MultiVector &amp;X, MultiVector &amp;Y) const </arglist>
    </member>
    <member kind="function">
      <type>std::ostream &amp;</type>
      <name>Print</name>
      <anchorfile>classMLAPI_1_1Operator.html</anchorfile>
      <anchor>a89a1d8c61ed8af2a277940afd484fbce</anchor>
      <arglist>(std::ostream &amp;os, const bool verbose=true) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>BuildColumnSpace</name>
      <anchorfile>classMLAPI_1_1Operator.html</anchorfile>
      <anchor>ab2faf1db882b238858cc8495aac1820d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Operator</name>
      <anchorfile>classMLAPI_1_1Operator.html</anchorfile>
      <anchor>a0801e9ac629755b5b7882a9b4271634c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Operator</name>
      <anchorfile>classMLAPI_1_1Operator.html</anchorfile>
      <anchor>a6086105fa8bf779e1cb526f9f771aa4f</anchor>
      <arglist>(const Space &amp;DomainSpace, const Space &amp;RangeSpace, ML_Operator *Op, bool Ownership=true, Teuchos::RefCountPtr&lt; ML_Operator_Box &gt; AuxOp=Teuchos::null)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Operator</name>
      <anchorfile>classMLAPI_1_1Operator.html</anchorfile>
      <anchor>aa42419ddee826a829d8bf36d8d080850</anchor>
      <arglist>(const Space &amp;DomainSpace, const Space &amp;RangeSpace, Epetra_RowMatrix *Matrix, bool Ownership=true, Teuchos::RefCountPtr&lt; ML_Operator_Box &gt; AuxOp=Teuchos::null)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Operator</name>
      <anchorfile>classMLAPI_1_1Operator.html</anchorfile>
      <anchor>abf90b5ead706b259c3ecb914a7aeed22</anchor>
      <arglist>(const Operator &amp;RHS)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~Operator</name>
      <anchorfile>classMLAPI_1_1Operator.html</anchorfile>
      <anchor>a1173e9da8b991ee242f980ab7daca3cf</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Reshape</name>
      <anchorfile>classMLAPI_1_1Operator.html</anchorfile>
      <anchor>ac1f37aefad0f9ed94b77595ad0244a39</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Reshape</name>
      <anchorfile>classMLAPI_1_1Operator.html</anchorfile>
      <anchor>aadbdbb7cbb82991a6457b1b3a79c2562</anchor>
      <arglist>(const Space &amp;DomainSpace, const Space &amp;RangeSpace, ML_Operator *Op, bool Ownership=true, Teuchos::RefCountPtr&lt; ML_Operator_Box &gt; AuxOp=Teuchos::null)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Reshape</name>
      <anchorfile>classMLAPI_1_1Operator.html</anchorfile>
      <anchor>a28830a11b649afcab5f8b98130b5d704</anchor>
      <arglist>(const Space &amp;DomainSpace, const Space &amp;RangeSpace, Epetra_RowMatrix *Matrix, bool Ownership=true, Teuchos::RefCountPtr&lt; ML_Operator_Box &gt; AuxOp=Teuchos::null)</arglist>
    </member>
    <member kind="function">
      <type>Operator &amp;</type>
      <name>operator=</name>
      <anchorfile>classMLAPI_1_1Operator.html</anchorfile>
      <anchor>a55f68334a30a91a013599bd4f57af7b1</anchor>
      <arglist>(const Operator &amp;RHS)</arglist>
    </member>
    <member kind="function">
      <type>Operator &amp;</type>
      <name>operator=</name>
      <anchorfile>classMLAPI_1_1Operator.html</anchorfile>
      <anchor>a10f20546e263ee36b681e5dc6ef68a61</anchor>
      <arglist>(const std::string &amp;Label)</arglist>
    </member>
    <member kind="function">
      <type>const Space</type>
      <name>GetOperatorDomainSpace</name>
      <anchorfile>classMLAPI_1_1Operator.html</anchorfile>
      <anchor>a4748041b5f1eef95d56433a22cfc3107</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Space</type>
      <name>GetOperatorRangeSpace</name>
      <anchorfile>classMLAPI_1_1Operator.html</anchorfile>
      <anchor>a6511bfde6d54c88c86a78e3ac506417f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Space</type>
      <name>GetDomainSpace</name>
      <anchorfile>classMLAPI_1_1Operator.html</anchorfile>
      <anchor>af6a5e272deb62d09bbcc706b166a6431</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Space</type>
      <name>GetRangeSpace</name>
      <anchorfile>classMLAPI_1_1Operator.html</anchorfile>
      <anchor>af4ed327cf369b3dd0247a9629b7ea854</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Space</type>
      <name>GetColumnSpace</name>
      <anchorfile>classMLAPI_1_1Operator.html</anchorfile>
      <anchor>a790531dda1f6079fcb27c45881ee24c1</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetNumGlobalRows</name>
      <anchorfile>classMLAPI_1_1Operator.html</anchorfile>
      <anchor>a83a6452bef25f426276a7c5fb1e68528</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetNumMyRows</name>
      <anchorfile>classMLAPI_1_1Operator.html</anchorfile>
      <anchor>ab6567b0d3496a14119f2a4583059e34f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetNumGlobalCols</name>
      <anchorfile>classMLAPI_1_1Operator.html</anchorfile>
      <anchor>a379f71d4b30d73019b3595f26876793e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetNumMyCols</name>
      <anchorfile>classMLAPI_1_1Operator.html</anchorfile>
      <anchor>a55d13a6571494f25409f855e4eca19dc</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetNumGlobalNonzeros</name>
      <anchorfile>classMLAPI_1_1Operator.html</anchorfile>
      <anchor>a35dad6dfc984f41e1b6da54c1359ddc3</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetNumMyNonzeros</name>
      <anchorfile>classMLAPI_1_1Operator.html</anchorfile>
      <anchor>ada148f9e900a296c41cea5844106f960</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_RowMatrix *</type>
      <name>GetRowMatrix</name>
      <anchorfile>classMLAPI_1_1Operator.html</anchorfile>
      <anchor>a68dc94a755d361a723c8c96d07e5ff6e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>ML_Operator *</type>
      <name>GetML_Operator</name>
      <anchorfile>classMLAPI_1_1Operator.html</anchorfile>
      <anchor>aa31643f0953883c2a7396868e1196cdc</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Teuchos::RefCountPtr&lt; ML_Operator_Box &gt; &amp;</type>
      <name>GetRCPOperatorBox</name>
      <anchorfile>classMLAPI_1_1Operator.html</anchorfile>
      <anchor>ada08eaaf1c6cdf5b6a03b198c9ee636b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Teuchos::RefCountPtr&lt; ML_Operator_Box &gt; &amp;</type>
      <name>GetRCPAuxOperatorBox</name>
      <anchorfile>classMLAPI_1_1Operator.html</anchorfile>
      <anchor>a3014ef5f706a941ddb3703a507e89239</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Teuchos::RefCountPtr&lt; Epetra_RowMatrix &gt; &amp;</type>
      <name>GetRCPRowMatrix</name>
      <anchorfile>classMLAPI_1_1Operator.html</anchorfile>
      <anchor>a6dccc4a05aca865a33f92b4cf24b7a29</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetGRID</name>
      <anchorfile>classMLAPI_1_1Operator.html</anchorfile>
      <anchor>ab2ed95be72ed49db8bca7959c12df6f2</anchor>
      <arglist>(const int LRID) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetGCID</name>
      <anchorfile>classMLAPI_1_1Operator.html</anchorfile>
      <anchor>a20fc2a74ec82b879bc6f2cb977f57f7e</anchor>
      <arglist>(const int LCID) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Apply</name>
      <anchorfile>classMLAPI_1_1Operator.html</anchorfile>
      <anchor>aceb9820540a59543955872f58083ef6b</anchor>
      <arglist>(const MultiVector &amp;X, MultiVector &amp;Y) const </arglist>
    </member>
    <member kind="function">
      <type>std::ostream &amp;</type>
      <name>Print</name>
      <anchorfile>classMLAPI_1_1Operator.html</anchorfile>
      <anchor>a89a1d8c61ed8af2a277940afd484fbce</anchor>
      <arglist>(std::ostream &amp;os, const bool verbose=true) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>BuildColumnSpace</name>
      <anchorfile>classMLAPI_1_1Operator.html</anchorfile>
      <anchor>ab2faf1db882b238858cc8495aac1820d</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>RefMaxwellPreconditioner</name>
    <filename>classRefMaxwellPreconditioner.html</filename>
  </compound>
  <compound kind="class">
    <name>MLAPI::Residual</name>
    <filename>classMLAPI_1_1Residual.html</filename>
    <base>MLAPI::BaseLinearCombination</base>
    <member kind="function">
      <type>const Space</type>
      <name>GetVectorSpace</name>
      <anchorfile>classMLAPI_1_1Residual.html</anchorfile>
      <anchor>a876b3936a9cad1b41713daa26db21bbb</anchor>
      <arglist>() const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ML_Epetra::RowMatrix</name>
    <filename>classML__Epetra_1_1RowMatrix.html</filename>
    <base virtualness="virtual">Epetra_RowMatrix</base>
    <member kind="function">
      <type>int</type>
      <name>SetOwnership</name>
      <anchorfile>classML__Epetra_1_1RowMatrix.html</anchorfile>
      <anchor>ad9f24595eff7702a0e89a51cbd5a8bd1</anchor>
      <arglist>(bool ownership)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetUseTranspose</name>
      <anchorfile>classML__Epetra_1_1RowMatrix.html</anchorfile>
      <anchor>a789bcd90e7f12cf297f4874639b51ba2</anchor>
      <arglist>(bool UseTransposeFlag)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>UseTranspose</name>
      <anchorfile>classML__Epetra_1_1RowMatrix.html</anchorfile>
      <anchor>a0c680ab32c3c11b715f97192048d787a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>HasNormInf</name>
      <anchorfile>classML__Epetra_1_1RowMatrix.html</anchorfile>
      <anchor>a6d213b1f626ce4f82d31f7399ea26eab</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_Comm &amp;</type>
      <name>Comm</name>
      <anchorfile>classML__Epetra_1_1RowMatrix.html</anchorfile>
      <anchor>a89d2fa1d1710f1f8374a576727c9179a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_Map &amp;</type>
      <name>OperatorDomainMap</name>
      <anchorfile>classML__Epetra_1_1RowMatrix.html</anchorfile>
      <anchor>a0d45236849bc9b8e36a1e58960149b50</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_Map &amp;</type>
      <name>OperatorRangeMap</name>
      <anchorfile>classML__Epetra_1_1RowMatrix.html</anchorfile>
      <anchor>a8d08ff0e3f420eb8e8fcc4d8087c83ba</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_BlockMap &amp;</type>
      <name>Map</name>
      <anchorfile>classML__Epetra_1_1RowMatrix.html</anchorfile>
      <anchor>a997f6af75dce6e4bad45ca6b01610b64</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Print</name>
      <anchorfile>classML__Epetra_1_1RowMatrix.html</anchorfile>
      <anchor>aa8960bacec7aaf58a4b68be349818017</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>RowMatrix</name>
      <anchorfile>classML__Epetra_1_1RowMatrix.html</anchorfile>
      <anchor>a601269b79bb0abf87b0ef45eb9a46980</anchor>
      <arglist>(ML_Operator *Op, const Epetra_Comm *Comm=0, const bool cheap=false, const USR_COMM=MPI_COMM_WORLD)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~RowMatrix</name>
      <anchorfile>classML__Epetra_1_1RowMatrix.html</anchorfile>
      <anchor>affe59b97060bbe8505ba5e7484d26a8a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>NumMyRowEntries</name>
      <anchorfile>classML__Epetra_1_1RowMatrix.html</anchorfile>
      <anchor>aaafab2406d026b5b5ba8af27784f2685</anchor>
      <arglist>(int MyRow, int &amp;NumEntries) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>MaxNumEntries</name>
      <anchorfile>classML__Epetra_1_1RowMatrix.html</anchorfile>
      <anchor>ac7b0d9b19ced944302dcdde6380b3b3c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>ExtractMyRowCopy</name>
      <anchorfile>classML__Epetra_1_1RowMatrix.html</anchorfile>
      <anchor>a16b0d251476993e0bed4be182a5936f2</anchor>
      <arglist>(int MyRow, int Length, int &amp;NumEntries, double *Values, int *Indices) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>ExtractDiagonalCopy</name>
      <anchorfile>classML__Epetra_1_1RowMatrix.html</anchorfile>
      <anchor>a63516e47c47ea1bae2de808c3d753c80</anchor>
      <arglist>(Epetra_Vector &amp;Diagonal) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>Multiply</name>
      <anchorfile>classML__Epetra_1_1RowMatrix.html</anchorfile>
      <anchor>a013a05f3482065accf19d1f98f2cc4c4</anchor>
      <arglist>(bool TransA, const Epetra_MultiVector &amp;X, Epetra_MultiVector &amp;Y) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>Solve</name>
      <anchorfile>classML__Epetra_1_1RowMatrix.html</anchorfile>
      <anchor>a4bd52cafcdc6452b94f25e4a47440ffb</anchor>
      <arglist>(bool Upper, bool Trans, bool UnitDiagonal, const Epetra_MultiVector &amp;X, Epetra_MultiVector &amp;Y) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>InvRowSums</name>
      <anchorfile>classML__Epetra_1_1RowMatrix.html</anchorfile>
      <anchor>a1f8a4a9c3931b1543e3c78de615cdee4</anchor>
      <arglist>(Epetra_Vector &amp;x) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>LeftScale</name>
      <anchorfile>classML__Epetra_1_1RowMatrix.html</anchorfile>
      <anchor>a06185357d639bb11935228c74657374f</anchor>
      <arglist>(const Epetra_Vector &amp;x)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>InvColSums</name>
      <anchorfile>classML__Epetra_1_1RowMatrix.html</anchorfile>
      <anchor>a3cadec29c9182312a4baac1d58eb5529</anchor>
      <arglist>(Epetra_Vector &amp;x) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>RightScale</name>
      <anchorfile>classML__Epetra_1_1RowMatrix.html</anchorfile>
      <anchor>a78561b0c7505764ac0477e8cf4088908</anchor>
      <arglist>(const Epetra_Vector &amp;x)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>Filled</name>
      <anchorfile>classML__Epetra_1_1RowMatrix.html</anchorfile>
      <anchor>aa45a215cbfa5c68cbb528a9723a43a5c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual double</type>
      <name>NormInf</name>
      <anchorfile>classML__Epetra_1_1RowMatrix.html</anchorfile>
      <anchor>abc493c3d78ee837cff3d474b69f2fd7f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual double</type>
      <name>NormOne</name>
      <anchorfile>classML__Epetra_1_1RowMatrix.html</anchorfile>
      <anchor>aa6c9d459fcf533119d2d32f76f2e0403</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>NumGlobalNonzeros</name>
      <anchorfile>classML__Epetra_1_1RowMatrix.html</anchorfile>
      <anchor>aaa041f83dc5cebaea802aed5d30bc725</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>NumGlobalRows</name>
      <anchorfile>classML__Epetra_1_1RowMatrix.html</anchorfile>
      <anchor>a9d553e470c2f59e4c4cb0776aec0c4d6</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>NumGlobalCols</name>
      <anchorfile>classML__Epetra_1_1RowMatrix.html</anchorfile>
      <anchor>afaf5458806aeee9115f4c7a1a7f52599</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>NumGlobalDiagonals</name>
      <anchorfile>classML__Epetra_1_1RowMatrix.html</anchorfile>
      <anchor>ac4bcbc8f7e0dc5de9f3e50c988360d30</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual long long</type>
      <name>NumGlobalNonzeros64</name>
      <anchorfile>classML__Epetra_1_1RowMatrix.html</anchorfile>
      <anchor>abc0396ceeec62866bfb403cdd01be05a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual long long</type>
      <name>NumGlobalRows64</name>
      <anchorfile>classML__Epetra_1_1RowMatrix.html</anchorfile>
      <anchor>aa460ecd6426989fa20b251e1e128d575</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual long long</type>
      <name>NumGlobalCols64</name>
      <anchorfile>classML__Epetra_1_1RowMatrix.html</anchorfile>
      <anchor>a9a8ef0f9fa67b09f7799e5c8080b29bb</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual long long</type>
      <name>NumGlobalDiagonals64</name>
      <anchorfile>classML__Epetra_1_1RowMatrix.html</anchorfile>
      <anchor>a80215f0b17f87745495e9c85167449f0</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>NumMyNonzeros</name>
      <anchorfile>classML__Epetra_1_1RowMatrix.html</anchorfile>
      <anchor>a96e9d959ed0c89f76c8cf1fdcb9bfe6d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>NumMyRows</name>
      <anchorfile>classML__Epetra_1_1RowMatrix.html</anchorfile>
      <anchor>adac0b4c7c50bb5304f5d7a65703a900c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>NumMyCols</name>
      <anchorfile>classML__Epetra_1_1RowMatrix.html</anchorfile>
      <anchor>af5caea5fe8fcb1f08f4b383899553057</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>NumMyDiagonals</name>
      <anchorfile>classML__Epetra_1_1RowMatrix.html</anchorfile>
      <anchor>af2b8f4e51061117aceb59662695ab4eb</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>LowerTriangular</name>
      <anchorfile>classML__Epetra_1_1RowMatrix.html</anchorfile>
      <anchor>a171718a6cfe5afa11adfa73d0e4137ad</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>UpperTriangular</name>
      <anchorfile>classML__Epetra_1_1RowMatrix.html</anchorfile>
      <anchor>ae6bfbf5abc018fa0d4cee005be87df02</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const Epetra_Map &amp;</type>
      <name>RowMatrixRowMap</name>
      <anchorfile>classML__Epetra_1_1RowMatrix.html</anchorfile>
      <anchor>a3282dd69e3cc630696471c31ada42ee0</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const Epetra_Map &amp;</type>
      <name>RowMatrixColMap</name>
      <anchorfile>classML__Epetra_1_1RowMatrix.html</anchorfile>
      <anchor>aa892b56bee992a524b585cfd0570c12a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const Epetra_Import *</type>
      <name>RowMatrixImporter</name>
      <anchorfile>classML__Epetra_1_1RowMatrix.html</anchorfile>
      <anchor>ae01abf9a46b526dc06bc57ffce982407</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>RowMatrix</name>
      <anchorfile>classML__Epetra_1_1RowMatrix.html</anchorfile>
      <anchor>a601269b79bb0abf87b0ef45eb9a46980</anchor>
      <arglist>(ML_Operator *Op, const Epetra_Comm *Comm=0, const bool cheap=false, const USR_COMM=MPI_COMM_WORLD)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~RowMatrix</name>
      <anchorfile>classML__Epetra_1_1RowMatrix.html</anchorfile>
      <anchor>affe59b97060bbe8505ba5e7484d26a8a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>NumMyRowEntries</name>
      <anchorfile>classML__Epetra_1_1RowMatrix.html</anchorfile>
      <anchor>aaafab2406d026b5b5ba8af27784f2685</anchor>
      <arglist>(int MyRow, int &amp;NumEntries) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>MaxNumEntries</name>
      <anchorfile>classML__Epetra_1_1RowMatrix.html</anchorfile>
      <anchor>ac7b0d9b19ced944302dcdde6380b3b3c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>ExtractMyRowCopy</name>
      <anchorfile>classML__Epetra_1_1RowMatrix.html</anchorfile>
      <anchor>a16b0d251476993e0bed4be182a5936f2</anchor>
      <arglist>(int MyRow, int Length, int &amp;NumEntries, double *Values, int *Indices) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>ExtractDiagonalCopy</name>
      <anchorfile>classML__Epetra_1_1RowMatrix.html</anchorfile>
      <anchor>a63516e47c47ea1bae2de808c3d753c80</anchor>
      <arglist>(Epetra_Vector &amp;Diagonal) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>Multiply</name>
      <anchorfile>classML__Epetra_1_1RowMatrix.html</anchorfile>
      <anchor>a013a05f3482065accf19d1f98f2cc4c4</anchor>
      <arglist>(bool TransA, const Epetra_MultiVector &amp;X, Epetra_MultiVector &amp;Y) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>Solve</name>
      <anchorfile>classML__Epetra_1_1RowMatrix.html</anchorfile>
      <anchor>a4bd52cafcdc6452b94f25e4a47440ffb</anchor>
      <arglist>(bool Upper, bool Trans, bool UnitDiagonal, const Epetra_MultiVector &amp;X, Epetra_MultiVector &amp;Y) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>InvRowSums</name>
      <anchorfile>classML__Epetra_1_1RowMatrix.html</anchorfile>
      <anchor>a1f8a4a9c3931b1543e3c78de615cdee4</anchor>
      <arglist>(Epetra_Vector &amp;x) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>LeftScale</name>
      <anchorfile>classML__Epetra_1_1RowMatrix.html</anchorfile>
      <anchor>a06185357d639bb11935228c74657374f</anchor>
      <arglist>(const Epetra_Vector &amp;x)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>InvColSums</name>
      <anchorfile>classML__Epetra_1_1RowMatrix.html</anchorfile>
      <anchor>a3cadec29c9182312a4baac1d58eb5529</anchor>
      <arglist>(Epetra_Vector &amp;x) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>RightScale</name>
      <anchorfile>classML__Epetra_1_1RowMatrix.html</anchorfile>
      <anchor>a78561b0c7505764ac0477e8cf4088908</anchor>
      <arglist>(const Epetra_Vector &amp;x)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>Filled</name>
      <anchorfile>classML__Epetra_1_1RowMatrix.html</anchorfile>
      <anchor>aa45a215cbfa5c68cbb528a9723a43a5c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual double</type>
      <name>NormInf</name>
      <anchorfile>classML__Epetra_1_1RowMatrix.html</anchorfile>
      <anchor>abc493c3d78ee837cff3d474b69f2fd7f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual double</type>
      <name>NormOne</name>
      <anchorfile>classML__Epetra_1_1RowMatrix.html</anchorfile>
      <anchor>aa6c9d459fcf533119d2d32f76f2e0403</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>NumGlobalNonzeros</name>
      <anchorfile>classML__Epetra_1_1RowMatrix.html</anchorfile>
      <anchor>aaa041f83dc5cebaea802aed5d30bc725</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>NumGlobalRows</name>
      <anchorfile>classML__Epetra_1_1RowMatrix.html</anchorfile>
      <anchor>a9d553e470c2f59e4c4cb0776aec0c4d6</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>NumGlobalCols</name>
      <anchorfile>classML__Epetra_1_1RowMatrix.html</anchorfile>
      <anchor>afaf5458806aeee9115f4c7a1a7f52599</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>NumGlobalDiagonals</name>
      <anchorfile>classML__Epetra_1_1RowMatrix.html</anchorfile>
      <anchor>ac4bcbc8f7e0dc5de9f3e50c988360d30</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual long long</type>
      <name>NumGlobalNonzeros64</name>
      <anchorfile>classML__Epetra_1_1RowMatrix.html</anchorfile>
      <anchor>abc0396ceeec62866bfb403cdd01be05a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual long long</type>
      <name>NumGlobalRows64</name>
      <anchorfile>classML__Epetra_1_1RowMatrix.html</anchorfile>
      <anchor>aa460ecd6426989fa20b251e1e128d575</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual long long</type>
      <name>NumGlobalCols64</name>
      <anchorfile>classML__Epetra_1_1RowMatrix.html</anchorfile>
      <anchor>a9a8ef0f9fa67b09f7799e5c8080b29bb</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual long long</type>
      <name>NumGlobalDiagonals64</name>
      <anchorfile>classML__Epetra_1_1RowMatrix.html</anchorfile>
      <anchor>a80215f0b17f87745495e9c85167449f0</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>NumMyNonzeros</name>
      <anchorfile>classML__Epetra_1_1RowMatrix.html</anchorfile>
      <anchor>a96e9d959ed0c89f76c8cf1fdcb9bfe6d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>NumMyRows</name>
      <anchorfile>classML__Epetra_1_1RowMatrix.html</anchorfile>
      <anchor>adac0b4c7c50bb5304f5d7a65703a900c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>NumMyCols</name>
      <anchorfile>classML__Epetra_1_1RowMatrix.html</anchorfile>
      <anchor>af5caea5fe8fcb1f08f4b383899553057</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>NumMyDiagonals</name>
      <anchorfile>classML__Epetra_1_1RowMatrix.html</anchorfile>
      <anchor>af2b8f4e51061117aceb59662695ab4eb</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>LowerTriangular</name>
      <anchorfile>classML__Epetra_1_1RowMatrix.html</anchorfile>
      <anchor>a171718a6cfe5afa11adfa73d0e4137ad</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>UpperTriangular</name>
      <anchorfile>classML__Epetra_1_1RowMatrix.html</anchorfile>
      <anchor>ae6bfbf5abc018fa0d4cee005be87df02</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const Epetra_Map &amp;</type>
      <name>RowMatrixRowMap</name>
      <anchorfile>classML__Epetra_1_1RowMatrix.html</anchorfile>
      <anchor>a3282dd69e3cc630696471c31ada42ee0</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const Epetra_Map &amp;</type>
      <name>RowMatrixColMap</name>
      <anchorfile>classML__Epetra_1_1RowMatrix.html</anchorfile>
      <anchor>aa892b56bee992a524b585cfd0570c12a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const Epetra_Import *</type>
      <name>RowMatrixImporter</name>
      <anchorfile>classML__Epetra_1_1RowMatrix.html</anchorfile>
      <anchor>ae01abf9a46b526dc06bc57ffce982407</anchor>
      <arglist>() const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>MLAPI::SerialMatrix</name>
    <filename>classMLAPI_1_1SerialMatrix.html</filename>
    <base>MLAPI::Operator</base>
    <member kind="function">
      <type>std::ostream &amp;</type>
      <name>Print</name>
      <anchorfile>classMLAPI_1_1SerialMatrix.html</anchorfile>
      <anchor>a77cea366f4fed5ee60f6f035331c2181</anchor>
      <arglist>(std::ostream &amp;os, const bool verbose=true) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>MLAPI::Space</name>
    <filename>classMLAPI_1_1Space.html</filename>
    <base>MLAPI::BaseObject</base>
    <member kind="function">
      <type></type>
      <name>Space</name>
      <anchorfile>classMLAPI_1_1Space.html</anchorfile>
      <anchor>a52f753df591922a03881bd279ae78afc</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Space</name>
      <anchorfile>classMLAPI_1_1Space.html</anchorfile>
      <anchor>aad97062b9710b07f964e0cfb39b86ef3</anchor>
      <arglist>(const int NumGlobalElements, const int NumMyElements=-1)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Space</name>
      <anchorfile>classMLAPI_1_1Space.html</anchorfile>
      <anchor>a5edf17de299275679449f2d0563cfbd4</anchor>
      <arglist>(const Epetra_Map &amp;Map)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Space</name>
      <anchorfile>classMLAPI_1_1Space.html</anchorfile>
      <anchor>ab535f0c30389c9aa64fe2a687cdb6155</anchor>
      <arglist>(const int NumGlobalElements, const int NumMyElements, const int *MyGlobalElements)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Space</name>
      <anchorfile>classMLAPI_1_1Space.html</anchorfile>
      <anchor>a1572779dc3997aa4640162ede2ec742c</anchor>
      <arglist>(const Space &amp;RHS)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~Space</name>
      <anchorfile>classMLAPI_1_1Space.html</anchorfile>
      <anchor>a7ac32178d17c7e7fc7d945f7e7400a07</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Reshape</name>
      <anchorfile>classMLAPI_1_1Space.html</anchorfile>
      <anchor>add7b016a6e1beb942bbcdc75f56d36a2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Reshape</name>
      <anchorfile>classMLAPI_1_1Space.html</anchorfile>
      <anchor>aa9c1c76dfd25bcf384723159326acc1c</anchor>
      <arglist>(const int NumGlobalElements, const int NumMyElements=-1)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Reshape</name>
      <anchorfile>classMLAPI_1_1Space.html</anchorfile>
      <anchor>a1d973064e89393c0a658c82966e32250</anchor>
      <arglist>(const int NumGlobalElements, const int NumMyElements, const int *MyGlobalElements)</arglist>
    </member>
    <member kind="function">
      <type>Space &amp;</type>
      <name>operator=</name>
      <anchorfile>classMLAPI_1_1Space.html</anchorfile>
      <anchor>a4b3ee1c6c0d300602fb21d938ca3d647</anchor>
      <arglist>(const Space &amp;RHS)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator==</name>
      <anchorfile>classMLAPI_1_1Space.html</anchorfile>
      <anchor>a6a15c1b7f089fa9628a50d7ae76fa825</anchor>
      <arglist>(const Space &amp;RHS) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator!=</name>
      <anchorfile>classMLAPI_1_1Space.html</anchorfile>
      <anchor>ab367123430a5d18f70baf051e43a633b</anchor>
      <arglist>(const Space &amp;RHS) const </arglist>
    </member>
    <member kind="function">
      <type>Space &amp;</type>
      <name>operator=</name>
      <anchorfile>classMLAPI_1_1Space.html</anchorfile>
      <anchor>a12684325ebed72add79a599bda651b3f</anchor>
      <arglist>(const std::string &amp;Label)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>operator()</name>
      <anchorfile>classMLAPI_1_1Space.html</anchorfile>
      <anchor>a182327b9b07ac04a63d761e5ea251678</anchor>
      <arglist>(int i) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetNumMyElements</name>
      <anchorfile>classMLAPI_1_1Space.html</anchorfile>
      <anchor>a13beeee0d5bea298a67e91d3be7db6eb</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetNumGlobalElements</name>
      <anchorfile>classMLAPI_1_1Space.html</anchorfile>
      <anchor>a6875ebed55bb8e0c6d5bc3fc56882779</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetOffset</name>
      <anchorfile>classMLAPI_1_1Space.html</anchorfile>
      <anchor>a75891f81494cbf88a84d9591b33658c5</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>IsLinear</name>
      <anchorfile>classMLAPI_1_1Space.html</anchorfile>
      <anchor>a19105e2561f7624e2a1bc09d0065d4cf</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Teuchos::RefCountPtr&lt; Epetra_IntSerialDenseVector &gt;</type>
      <name>GetRCPMyGlobalElements</name>
      <anchorfile>classMLAPI_1_1Space.html</anchorfile>
      <anchor>aa160ee90b9dd0e99eca697a0767b46d7</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>std::ostream &amp;</type>
      <name>Print</name>
      <anchorfile>classMLAPI_1_1Space.html</anchorfile>
      <anchor>a7fb4b7ed542056385653a2cc9d370d5c</anchor>
      <arglist>(std::ostream &amp;os, const bool verbose=true) const </arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Space</name>
      <anchorfile>classMLAPI_1_1Space.html</anchorfile>
      <anchor>a52f753df591922a03881bd279ae78afc</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Space</name>
      <anchorfile>classMLAPI_1_1Space.html</anchorfile>
      <anchor>aad97062b9710b07f964e0cfb39b86ef3</anchor>
      <arglist>(const int NumGlobalElements, const int NumMyElements=-1)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Space</name>
      <anchorfile>classMLAPI_1_1Space.html</anchorfile>
      <anchor>a5edf17de299275679449f2d0563cfbd4</anchor>
      <arglist>(const Epetra_Map &amp;Map)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Space</name>
      <anchorfile>classMLAPI_1_1Space.html</anchorfile>
      <anchor>ab535f0c30389c9aa64fe2a687cdb6155</anchor>
      <arglist>(const int NumGlobalElements, const int NumMyElements, const int *MyGlobalElements)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Space</name>
      <anchorfile>classMLAPI_1_1Space.html</anchorfile>
      <anchor>a1572779dc3997aa4640162ede2ec742c</anchor>
      <arglist>(const Space &amp;RHS)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~Space</name>
      <anchorfile>classMLAPI_1_1Space.html</anchorfile>
      <anchor>a7ac32178d17c7e7fc7d945f7e7400a07</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Reshape</name>
      <anchorfile>classMLAPI_1_1Space.html</anchorfile>
      <anchor>add7b016a6e1beb942bbcdc75f56d36a2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Reshape</name>
      <anchorfile>classMLAPI_1_1Space.html</anchorfile>
      <anchor>aa9c1c76dfd25bcf384723159326acc1c</anchor>
      <arglist>(const int NumGlobalElements, const int NumMyElements=-1)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Reshape</name>
      <anchorfile>classMLAPI_1_1Space.html</anchorfile>
      <anchor>a1d973064e89393c0a658c82966e32250</anchor>
      <arglist>(const int NumGlobalElements, const int NumMyElements, const int *MyGlobalElements)</arglist>
    </member>
    <member kind="function">
      <type>Space &amp;</type>
      <name>operator=</name>
      <anchorfile>classMLAPI_1_1Space.html</anchorfile>
      <anchor>a4b3ee1c6c0d300602fb21d938ca3d647</anchor>
      <arglist>(const Space &amp;RHS)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator==</name>
      <anchorfile>classMLAPI_1_1Space.html</anchorfile>
      <anchor>a6a15c1b7f089fa9628a50d7ae76fa825</anchor>
      <arglist>(const Space &amp;RHS) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator!=</name>
      <anchorfile>classMLAPI_1_1Space.html</anchorfile>
      <anchor>ab367123430a5d18f70baf051e43a633b</anchor>
      <arglist>(const Space &amp;RHS) const </arglist>
    </member>
    <member kind="function">
      <type>Space &amp;</type>
      <name>operator=</name>
      <anchorfile>classMLAPI_1_1Space.html</anchorfile>
      <anchor>a12684325ebed72add79a599bda651b3f</anchor>
      <arglist>(const std::string &amp;Label)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>operator()</name>
      <anchorfile>classMLAPI_1_1Space.html</anchorfile>
      <anchor>a182327b9b07ac04a63d761e5ea251678</anchor>
      <arglist>(int i) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetNumMyElements</name>
      <anchorfile>classMLAPI_1_1Space.html</anchorfile>
      <anchor>a13beeee0d5bea298a67e91d3be7db6eb</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetNumGlobalElements</name>
      <anchorfile>classMLAPI_1_1Space.html</anchorfile>
      <anchor>a6875ebed55bb8e0c6d5bc3fc56882779</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetOffset</name>
      <anchorfile>classMLAPI_1_1Space.html</anchorfile>
      <anchor>a75891f81494cbf88a84d9591b33658c5</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>IsLinear</name>
      <anchorfile>classMLAPI_1_1Space.html</anchorfile>
      <anchor>a19105e2561f7624e2a1bc09d0065d4cf</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Teuchos::RefCountPtr&lt; Epetra_IntSerialDenseVector &gt;</type>
      <name>GetRCPMyGlobalElements</name>
      <anchorfile>classMLAPI_1_1Space.html</anchorfile>
      <anchor>aa160ee90b9dd0e99eca697a0767b46d7</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>std::ostream &amp;</type>
      <name>Print</name>
      <anchorfile>classMLAPI_1_1Space.html</anchorfile>
      <anchor>a7fb4b7ed542056385653a2cc9d370d5c</anchor>
      <arglist>(std::ostream &amp;os, const bool verbose=true) const </arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>MLAPI::StackEntry</name>
    <filename>structMLAPI_1_1StackEntry.html</filename>
  </compound>
  <compound kind="class">
    <name>MLAPI::TimeObject</name>
    <filename>classMLAPI_1_1TimeObject.html</filename>
    <member kind="function">
      <type></type>
      <name>TimeObject</name>
      <anchorfile>classMLAPI_1_1TimeObject.html</anchorfile>
      <anchor>a9b431ba9a790dc4177de6e40bc5adfae</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~TimeObject</name>
      <anchorfile>classMLAPI_1_1TimeObject.html</anchorfile>
      <anchor>a124546be67440e8551ceef68588fb182</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>ResetTimer</name>
      <anchorfile>classMLAPI_1_1TimeObject.html</anchorfile>
      <anchor>a0606d9f9f3e6817397efecd6d3966287</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>UpdateTime</name>
      <anchorfile>classMLAPI_1_1TimeObject.html</anchorfile>
      <anchor>aad0497f7f97883154bfc9ce7176803af</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>UpdateTime</name>
      <anchorfile>classMLAPI_1_1TimeObject.html</anchorfile>
      <anchor>a0243d588abbea6d1633d148c9737b938</anchor>
      <arglist>(double t) const </arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>GetTime</name>
      <anchorfile>classMLAPI_1_1TimeObject.html</anchorfile>
      <anchor>ae0beba2b5d9e11f00470454a4cd62317</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>Epetra_Time</type>
      <name>Time_</name>
      <anchorfile>classMLAPI_1_1TimeObject.html</anchorfile>
      <anchor>a6cb31209a918f1ccdc7a2ad60b724023</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>double</type>
      <name>TotalTime_</name>
      <anchorfile>classMLAPI_1_1TimeObject.html</anchorfile>
      <anchor>a2a2924a7090519600820b28bccb52699</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>wrappedCommStruct</name>
    <filename>structwrappedCommStruct.html</filename>
  </compound>
  <compound kind="namespace">
    <name>ML_Anasazi</name>
    <filename>namespaceML__Anasazi.html</filename>
    <member kind="function">
      <type>int</type>
      <name>Interface</name>
      <anchorfile>namespaceML__Anasazi.html</anchorfile>
      <anchor>a75ac5be2035e966946cfdca8c790a267</anchor>
      <arglist>(const Epetra_RowMatrix *RowMatrix, Epetra_MultiVector &amp;EigenVectors, double RealEigenvalues[], double ImagEigenvalues[], Teuchos::ParameterList &amp;List, double RealEigenvectors[]=0, double ImagEigenvectors[]=0, int *NumRealEigenvectors=0, int *NumImagEigenvectors=0, ML *ml=0)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetFieldOfValuesBox</name>
      <anchorfile>namespaceML__Anasazi.html</anchorfile>
      <anchor>a8ce97418ea46f9b7c5d46be0b3e3c7df</anchor>
      <arglist>(const Epetra_RowMatrix *RowMatrix, double &amp;MaxReal, double &amp;MaxImag, Teuchos::ParameterList &amp;AnasaziList)</arglist>
    </member>
  </compound>
  <compound kind="namespace">
    <name>ML_Epetra</name>
    <filename>namespaceML__Epetra.html</filename>
    <class kind="class">ML_Epetra::CrsGraphWrapper</class>
    <class kind="class">ML_Epetra::EdgeMatrixFreePreconditioner</class>
    <class kind="class">ML_Epetra::Ifpack_ML</class>
    <class kind="class">ML_Epetra::MatrixFreePreconditioner</class>
    <class kind="class">ML_Epetra::ML_RefMaxwell_11_Operator</class>
    <class kind="class">ML_Epetra::ML_RMP</class>
    <class kind="class">ML_Epetra::MultiLevelOperator</class>
    <class kind="class">ML_Epetra::MultiLevelPreconditioner</class>
    <class kind="class">ML_Epetra::RowMatrix</class>
    <member kind="enumeration">
      <type></type>
      <name>AMGType</name>
      <anchorfile>namespaceML__Epetra.html</anchorfile>
      <anchor>acdeabed2c09f4fa9cbfa2d330cbf3f2f</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ML_Epetra_PtAP</name>
      <anchorfile>namespaceML__Epetra.html</anchorfile>
      <anchor>a654449cb61cf14354bc6178bef4b511e</anchor>
      <arglist>(const Epetra_CrsMatrix &amp;A, const Epetra_CrsMatrix &amp;P, Epetra_CrsMatrix *&amp;Result, bool verbose=false)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ML_Epetra_RAP</name>
      <anchorfile>namespaceML__Epetra.html</anchorfile>
      <anchor>a8b67ded5d8822c69c174ca20199200d6</anchor>
      <arglist>(const Epetra_CrsMatrix &amp;A, const Epetra_CrsMatrix &amp;P, const Epetra_CrsMatrix &amp;R, Epetra_CrsMatrix *&amp;Result, bool verbose)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Epetra_PtAP</name>
      <anchorfile>namespaceML__Epetra.html</anchorfile>
      <anchor>a28806e45dd689c5e25ae0550e3cc55fa</anchor>
      <arglist>(const Epetra_CrsMatrix &amp;A, const Epetra_CrsMatrix &amp;P, Epetra_CrsMatrix *&amp;Result, bool keep_zero_rows=false, bool verbose=false)</arglist>
    </member>
    <member kind="function">
      <type>int *</type>
      <name>FindLocalDiricheltRowsFromOnesAndZeros</name>
      <anchorfile>namespaceML__Epetra.html</anchorfile>
      <anchor>a6036c23604aa2ae45754ac943c4bdd17</anchor>
      <arglist>(const Epetra_CrsMatrix &amp;Matrix, int &amp;numBCRows)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Apply_BCsToMatrixColumns</name>
      <anchorfile>namespaceML__Epetra.html</anchorfile>
      <anchor>ac5a14382c90516d405b8cfc91382d4ef</anchor>
      <arglist>(const int *dirichletRows, int numBCRows, const Epetra_CrsMatrix &amp;Matrix)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Apply_BCsToMatrixRows</name>
      <anchorfile>namespaceML__Epetra.html</anchorfile>
      <anchor>aa2017813fef318a1fcbd2477a237ef88</anchor>
      <arglist>(const int *dirichletRows, int numBCRows, const Epetra_CrsMatrix &amp;Matrix)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Apply_BCsToMatrixColumns</name>
      <anchorfile>namespaceML__Epetra.html</anchorfile>
      <anchor>adef8c4cb6e769016fc2358047285f5d2</anchor>
      <arglist>(const Epetra_RowMatrix &amp;iBoundaryMatrix, const Epetra_RowMatrix &amp;iMatrix)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Apply_BCsToGradient</name>
      <anchorfile>namespaceML__Epetra.html</anchorfile>
      <anchor>acacbd0af46df3fb65b3f6a917b0ff5cf</anchor>
      <arglist>(const Epetra_RowMatrix &amp;EdgeMatrix, const Epetra_RowMatrix &amp;T)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Apply_OAZToMatrix</name>
      <anchorfile>namespaceML__Epetra.html</anchorfile>
      <anchor>a62e88102bb26b9e8f3c13359ad852fb1</anchor>
      <arglist>(int *dirichletRows, int numBCRows, const Epetra_CrsMatrix &amp;Matrix)</arglist>
    </member>
    <member kind="function">
      <type>Epetra_IntVector *</type>
      <name>LocalRowstoColumns</name>
      <anchorfile>namespaceML__Epetra.html</anchorfile>
      <anchor>abf48f7683e25146522a6bc1fea4420f7</anchor>
      <arglist>(int *Rows, int numRows, const Epetra_CrsMatrix &amp;Matrix)</arglist>
    </member>
    <member kind="function">
      <type>Epetra_IntVector *</type>
      <name>FindLocalDirichletColumnsFromRows</name>
      <anchorfile>namespaceML__Epetra.html</anchorfile>
      <anchor>a252072c2e6f22063c5f16ee414889b7a</anchor>
      <arglist>(const int *dirichletRows, int numBCRows, const Epetra_CrsMatrix &amp;Matrix)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Remove_Zeroed_Rows</name>
      <anchorfile>namespaceML__Epetra.html</anchorfile>
      <anchor>a843e125059a029d759708ef91f15f1f3</anchor>
      <arglist>(const Epetra_CrsMatrix &amp;Matrix, double tol=0.0)</arglist>
    </member>
    <member kind="function">
      <type>Epetra_RowMatrix *</type>
      <name>ModifyEpetraMatrixColMap</name>
      <anchorfile>namespaceML__Epetra.html</anchorfile>
      <anchor>a24bc7bfd25ff2b787a56cb8d713dbad5</anchor>
      <arglist>(const Epetra_RowMatrix &amp;A, EpetraExt::CrsMatrix_SolverMap &amp;transform, const char *matrixName=0, bool verbose=false)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetDefaults</name>
      <anchorfile>namespaceML__Epetra.html</anchorfile>
      <anchor>a56d4ce3baee9b349ed2333326e0ec2b6</anchor>
      <arglist>(std::string ProblemType, Teuchos::ParameterList &amp;List, int *options=0, double *params=0, const bool OverWrite=true)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetDefaultsDD</name>
      <anchorfile>namespaceML__Epetra.html</anchorfile>
      <anchor>afe8ac10c161ff035bfff3c7d933a682e</anchor>
      <arglist>(Teuchos::ParameterList &amp;List, Teuchos::RCP&lt; std::vector&lt; int &gt; &gt; &amp;options, Teuchos::RCP&lt; std::vector&lt; double &gt; &gt; &amp;params, bool Overwrite=true)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetDefaultsDD_LU</name>
      <anchorfile>namespaceML__Epetra.html</anchorfile>
      <anchor>a74f35b250c87034cd245d02a49853a46</anchor>
      <arglist>(Teuchos::ParameterList &amp;List, Teuchos::RCP&lt; std::vector&lt; int &gt; &gt; &amp;options, Teuchos::RCP&lt; std::vector&lt; double &gt; &gt; &amp;params, bool Overwrite=true)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetDefaultsDD_3Levels</name>
      <anchorfile>namespaceML__Epetra.html</anchorfile>
      <anchor>a1a7035c7ccc295e3b15d47a82150c504</anchor>
      <arglist>(Teuchos::ParameterList &amp;List, Teuchos::RCP&lt; std::vector&lt; int &gt; &gt; &amp;options, Teuchos::RCP&lt; std::vector&lt; double &gt; &gt; &amp;params, bool Overwrite=true)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetDefaultsDD_3Levels_LU</name>
      <anchorfile>namespaceML__Epetra.html</anchorfile>
      <anchor>a6eee28e412ed3ab46e7fed2e0ec63871</anchor>
      <arglist>(Teuchos::ParameterList &amp;List, Teuchos::RCP&lt; std::vector&lt; int &gt; &gt; &amp;options, Teuchos::RCP&lt; std::vector&lt; double &gt; &gt; &amp;params, bool Overwrite=true)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetDefaultsMaxwell</name>
      <anchorfile>namespaceML__Epetra.html</anchorfile>
      <anchor>a0707be28e45423af9662d399a21f8bd1</anchor>
      <arglist>(Teuchos::ParameterList &amp;List, Teuchos::RCP&lt; std::vector&lt; int &gt; &gt; &amp;options, Teuchos::RCP&lt; std::vector&lt; double &gt; &gt; &amp;params, bool Overwrite=true)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetDefaultsSA</name>
      <anchorfile>namespaceML__Epetra.html</anchorfile>
      <anchor>a46fd78bf3b6979a5bec018c93b4c23b4</anchor>
      <arglist>(Teuchos::ParameterList &amp;List, Teuchos::RCP&lt; std::vector&lt; int &gt; &gt; &amp;options, Teuchos::RCP&lt; std::vector&lt; double &gt; &gt; &amp;params, bool Overwrite=true)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetDefaultsNSSA</name>
      <anchorfile>namespaceML__Epetra.html</anchorfile>
      <anchor>a8371873a53298fee7d9bf8fd836b8091</anchor>
      <arglist>(Teuchos::ParameterList &amp;List, Teuchos::RCP&lt; std::vector&lt; int &gt; &gt; &amp;options, Teuchos::RCP&lt; std::vector&lt; double &gt; &gt; &amp;params, bool Overwrite=true)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ReadXML</name>
      <anchorfile>namespaceML__Epetra.html</anchorfile>
      <anchor>aa15a238c96fdcafd8f5625a49ed53d03</anchor>
      <arglist>(const std::string &amp;FileName, Teuchos::ParameterList &amp;List, const Epetra_Comm &amp;Comm)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetDefaultsRefMaxwell</name>
      <anchorfile>namespaceML__Epetra.html</anchorfile>
      <anchor>a2bed35bc292c07d1126004bbe7cd44fa</anchor>
      <arglist>(Teuchos::ParameterList &amp;inList, bool OverWrite=true)</arglist>
    </member>
  </compound>
  <compound kind="namespace">
    <name>MLAPI</name>
    <filename>namespaceMLAPI.html</filename>
    <class kind="class">MLAPI::BaseLinearCombination</class>
    <class kind="class">MLAPI::BaseObject</class>
    <class kind="class">MLAPI::BaseOperator</class>
    <class kind="class">MLAPI::BaseOperatorTimesMultiVector</class>
    <class kind="class">MLAPI::CompObject</class>
    <class kind="class">MLAPI::DistributedMatrix</class>
    <class kind="class">MLAPI::DoubleVector</class>
    <class kind="class">MLAPI::Epetra_SerialMatrix</class>
    <class kind="class">MLAPI::EpetraBaseOperator</class>
    <class kind="class">MLAPI::InverseOperator</class>
    <class kind="class">MLAPI::LinearCombinationAdd</class>
    <class kind="class">MLAPI::LinearCombinationMixed</class>
    <class kind="class">MLAPI::LinearCombinationScaled</class>
    <class kind="class">MLAPI::LoadBalanceInverseOperator</class>
    <class kind="class">MLAPI::LoadBalanceOperator</class>
    <class kind="class">MLAPI::MATLABStream</class>
    <class kind="class">MLAPI::ML_Operator_Box</class>
    <class kind="class">MLAPI::MultiLevelAdaptiveSA</class>
    <class kind="class">MLAPI::MultiLevelSA</class>
    <class kind="class">MLAPI::MultiVector</class>
    <class kind="class">MLAPI::MultiVectorCombination</class>
    <class kind="class">MLAPI::MultiVectorScaled</class>
    <class kind="class">MLAPI::Operator</class>
    <class kind="class">MLAPI::Residual</class>
    <class kind="class">MLAPI::SerialMatrix</class>
    <class kind="class">MLAPI::Space</class>
    <class kind="struct">MLAPI::StackEntry</class>
    <class kind="class">MLAPI::TimeObject</class>
    <member kind="function">
      <type>void</type>
      <name>GetPtent</name>
      <anchorfile>namespaceMLAPI.html</anchorfile>
      <anchor>a6609804c6d86c4708b7168cab10fe4ef</anchor>
      <arglist>(const Operator &amp;A, Teuchos::ParameterList &amp;List, const MultiVector &amp;ThisNS, Operator &amp;Ptent, MultiVector &amp;NextNS)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>GetPtent</name>
      <anchorfile>namespaceMLAPI.html</anchorfile>
      <anchor>a02dd2723ac5649b278cbe387b4184ad7</anchor>
      <arglist>(const Operator &amp;A, Teuchos::ParameterList &amp;List, Operator &amp;Ptent)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>GetPtent</name>
      <anchorfile>namespaceMLAPI.html</anchorfile>
      <anchor>a5ba8fd04b219e87086364582f6223418</anchor>
      <arglist>(const Epetra_RowMatrix &amp;A, Teuchos::ParameterList &amp;List, double *thisns, Teuchos::RCP&lt; Epetra_CrsMatrix &gt; &amp;Ptent, Teuchos::RCP&lt; Epetra_MultiVector &gt; &amp;NextNS, const int domainoffset=0)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>GetPtent</name>
      <anchorfile>namespaceMLAPI.html</anchorfile>
      <anchor>a3dabf6c0b2d4e9b5e09bc47c5867eb93</anchor>
      <arglist>(const Epetra_RowMatrix &amp;A, Teuchos::ParameterList &amp;List, double *thisns, Teuchos::RCP&lt; Epetra_CrsMatrix &gt; &amp;Ptent, const int domainoffset=0)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetAggregates</name>
      <anchorfile>namespaceMLAPI.html</anchorfile>
      <anchor>ac910b47c4ef0b9e28acf9cfe719ab3ae</anchor>
      <arglist>(Epetra_RowMatrix &amp;A, Teuchos::ParameterList &amp;List, double *thisns, Epetra_IntVector &amp;aggrinfo)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetGlobalAggregates</name>
      <anchorfile>namespaceMLAPI.html</anchorfile>
      <anchor>a0a75b74ee4a063a3ee5b6750a9afc0de</anchor>
      <arglist>(Epetra_RowMatrix &amp;A, Teuchos::ParameterList &amp;List, double *thisns, Epetra_IntVector &amp;aggrinfo)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetDefaults</name>
      <anchorfile>namespaceMLAPI.html</anchorfile>
      <anchor>a7b88442031e5a937bfd320862c864cb4</anchor>
      <arglist>(Teuchos::ParameterList &amp;List)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>MaxEigAnorm</name>
      <anchorfile>namespaceMLAPI.html</anchorfile>
      <anchor>a5bed05896791e61e29644bb78471c5be</anchor>
      <arglist>(const Operator &amp;Op, const bool DiagonalScaling=false)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>MaxEigCG</name>
      <anchorfile>namespaceMLAPI.html</anchorfile>
      <anchor>aadba5c6ee7b4ee7da2dc7680419018c8</anchor>
      <arglist>(const Operator &amp;Op, const bool DiagonalScaling=false)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>MaxEigPowerMethod</name>
      <anchorfile>namespaceMLAPI.html</anchorfile>
      <anchor>a13e4478ac0f2ffe04ac6420af3c4f2d3</anchor>
      <arglist>(const Operator &amp;Op, const bool DiagonalScaling=false)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>MaxEigAnasazi</name>
      <anchorfile>namespaceMLAPI.html</anchorfile>
      <anchor>a5aab66a75fddbfc405c86285c67f7aa9</anchor>
      <arglist>(const Operator &amp;Op, const bool DiagonalScaling=false)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Eig</name>
      <anchorfile>namespaceMLAPI.html</anchorfile>
      <anchor>a48592896b1ef49d15a8d02ba79dd3558</anchor>
      <arglist>(const Operator &amp;Op, MultiVector &amp;ER, MultiVector &amp;EI)</arglist>
    </member>
    <member kind="function">
      <type>MultiVectorCombination</type>
      <name>operator+</name>
      <anchorfile>namespaceMLAPI.html</anchorfile>
      <anchor>a2b49b3900112df29828ebd137c881af7</anchor>
      <arglist>(const MultiVector &amp;x, const MultiVector &amp;y)</arglist>
    </member>
    <member kind="function">
      <type>MultiVectorCombination</type>
      <name>operator+</name>
      <anchorfile>namespaceMLAPI.html</anchorfile>
      <anchor>a67aae181510b908a4bc7241f201a09fd</anchor>
      <arglist>(const MultiVectorScaled &amp;left, const MultiVectorScaled &amp;right)</arglist>
    </member>
    <member kind="function">
      <type>Residual</type>
      <name>operator+</name>
      <anchorfile>namespaceMLAPI.html</anchorfile>
      <anchor>a417990acd4e8ed720ff15934ea3e0758</anchor>
      <arglist>(const MultiVectorScaled &amp;left, const BaseOperatorTimesMultiVector &amp;right)</arglist>
    </member>
    <member kind="function">
      <type>Residual</type>
      <name>operator+</name>
      <anchorfile>namespaceMLAPI.html</anchorfile>
      <anchor>a68626732ec8f15b925621e959ba0aedf</anchor>
      <arglist>(const MultiVector &amp;left, const BaseOperatorTimesMultiVector &amp;right)</arglist>
    </member>
    <member kind="function">
      <type>MultiVectorCombination</type>
      <name>operator-</name>
      <anchorfile>namespaceMLAPI.html</anchorfile>
      <anchor>a35b11ca410893124559bfd5f25165fa5</anchor>
      <arglist>(const MultiVector &amp;x, const MultiVector &amp;y)</arglist>
    </member>
    <member kind="function">
      <type>Residual</type>
      <name>operator-</name>
      <anchorfile>namespaceMLAPI.html</anchorfile>
      <anchor>a1d875f7b716eccdd6c8deac17999e4a2</anchor>
      <arglist>(const MultiVector &amp;left, const BaseOperatorTimesMultiVector &amp;right)</arglist>
    </member>
    <member kind="function">
      <type>MultiVector</type>
      <name>operator+</name>
      <anchorfile>namespaceMLAPI.html</anchorfile>
      <anchor>aa4bfbe16791ed9055976bac8642566f2</anchor>
      <arglist>(const MultiVector &amp;x, const double alpha)</arglist>
    </member>
    <member kind="function">
      <type>MultiVector</type>
      <name>operator+</name>
      <anchorfile>namespaceMLAPI.html</anchorfile>
      <anchor>a1a6ba2efe14bfccc918b6a2c9e34a173</anchor>
      <arglist>(const double alpha, const MultiVector &amp;x)</arglist>
    </member>
    <member kind="function">
      <type>MultiVector</type>
      <name>operator-</name>
      <anchorfile>namespaceMLAPI.html</anchorfile>
      <anchor>a1ab03f15a180c0a21125e67a603ce08a</anchor>
      <arglist>(const MultiVector &amp;x, const double alpha)</arglist>
    </member>
    <member kind="function">
      <type>MultiVector</type>
      <name>operator-</name>
      <anchorfile>namespaceMLAPI.html</anchorfile>
      <anchor>abad75ca3f02a5ae2bb3132e4150af9e6</anchor>
      <arglist>(const double alpha, const MultiVector &amp;x)</arglist>
    </member>
    <member kind="function">
      <type>Operator</type>
      <name>operator+</name>
      <anchorfile>namespaceMLAPI.html</anchorfile>
      <anchor>a379d76a03dad3df4838009340553df6c</anchor>
      <arglist>(const Operator &amp;A, const Operator &amp;B)</arglist>
    </member>
    <member kind="function">
      <type>Operator</type>
      <name>operator-</name>
      <anchorfile>namespaceMLAPI.html</anchorfile>
      <anchor>a3304c61897312556c1a8145a60f318c2</anchor>
      <arglist>(const Operator &amp;A, const Operator &amp;B)</arglist>
    </member>
    <member kind="function">
      <type>Operator</type>
      <name>operator*</name>
      <anchorfile>namespaceMLAPI.html</anchorfile>
      <anchor>abf7cb7e6d04eb612d3e13b93fa962723</anchor>
      <arglist>(const Operator &amp;A, const Operator &amp;B)</arglist>
    </member>
    <member kind="function">
      <type>Operator</type>
      <name>operator*</name>
      <anchorfile>namespaceMLAPI.html</anchorfile>
      <anchor>a78a3aeda702aaa0d5b4a71943127c58a</anchor>
      <arglist>(const Operator &amp;A, const double alpha)</arglist>
    </member>
    <member kind="function">
      <type>Operator</type>
      <name>operator*</name>
      <anchorfile>namespaceMLAPI.html</anchorfile>
      <anchor>a418ca6404aea1e6afcbbcad65754be19</anchor>
      <arglist>(const double alpha, const Operator &amp;A)</arglist>
    </member>
    <member kind="function">
      <type>Operator</type>
      <name>operator/</name>
      <anchorfile>namespaceMLAPI.html</anchorfile>
      <anchor>a4cb916db6b6d6f7082645d066b8f37ca</anchor>
      <arglist>(const Operator &amp;A, const double alpha)</arglist>
    </member>
    <member kind="function">
      <type>MultiVector</type>
      <name>operator*</name>
      <anchorfile>namespaceMLAPI.html</anchorfile>
      <anchor>a50c893b9be5041a6d4403d7c975501ff</anchor>
      <arglist>(const MultiVector &amp;x, const double alpha)</arglist>
    </member>
    <member kind="function">
      <type>MultiVector</type>
      <name>operator/</name>
      <anchorfile>namespaceMLAPI.html</anchorfile>
      <anchor>ae1ab8c560702377b5289b12edd20a2d1</anchor>
      <arglist>(const MultiVector &amp;x, const double alpha)</arglist>
    </member>
    <member kind="function">
      <type>BaseOperatorTimesMultiVector</type>
      <name>operator*</name>
      <anchorfile>namespaceMLAPI.html</anchorfile>
      <anchor>ab9308df6a665fbb2f9c85fd0a3229b6a</anchor>
      <arglist>(const BaseOperator &amp;A, const MultiVector &amp;x)</arglist>
    </member>
    <member kind="function">
      <type>BaseOperatorTimesMultiVector</type>
      <name>operator*</name>
      <anchorfile>namespaceMLAPI.html</anchorfile>
      <anchor>acc84e359c2ad5a9617d1380f75f5b297</anchor>
      <arglist>(const BaseOperator &amp;A, const BaseLinearCombination &amp;x)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>operator*</name>
      <anchorfile>namespaceMLAPI.html</anchorfile>
      <anchor>a9030720a1ebfc6ed9bfb5c8a21c6ab60</anchor>
      <arglist>(const MultiVector &amp;x, const MultiVector &amp;y)</arglist>
    </member>
    <member kind="function">
      <type>Operator</type>
      <name>Gallery</name>
      <anchorfile>namespaceMLAPI.html</anchorfile>
      <anchor>a71b4b0c3cc1abedfd6f791a00fa54c79</anchor>
      <arglist>(const std::string ProblemType, const Space &amp;MySpace)</arglist>
    </member>
    <member kind="function">
      <type>Operator</type>
      <name>GetShiftedLaplacian1D</name>
      <anchorfile>namespaceMLAPI.html</anchorfile>
      <anchor>a83c05734bb635e59c4387312d9cca9c7</anchor>
      <arglist>(const int NX, const double Factor=0.99)</arglist>
    </member>
    <member kind="function">
      <type>Operator</type>
      <name>GetShiftedLaplacian2D</name>
      <anchorfile>namespaceMLAPI.html</anchorfile>
      <anchor>a2b571c35b05b1ace0e9b79c9ff512172</anchor>
      <arglist>(const int NX, const int NY, const double Factor=0.99, const bool RandomScale=false)</arglist>
    </member>
    <member kind="function">
      <type>Operator</type>
      <name>ReadMatrix</name>
      <anchorfile>namespaceMLAPI.html</anchorfile>
      <anchor>a8cf394f66d009eef0ba2053334ec1418</anchor>
      <arglist>(const char *FileName)</arglist>
    </member>
    <member kind="function">
      <type>Operator</type>
      <name>GetRecirc2D</name>
      <anchorfile>namespaceMLAPI.html</anchorfile>
      <anchor>a242622ff52124e5d30c7f037663481ef</anchor>
      <arglist>(const int NX, const int NY, const double conv, const double diff)</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::ParameterList</type>
      <name>ReadParameterList</name>
      <anchorfile>namespaceMLAPI.html</anchorfile>
      <anchor>af187f70b1eb20c19fb1c7d3ab0ca4d87</anchor>
      <arglist>(const char *FileName)</arglist>
    </member>
    <member kind="function">
      <type>MultiVector</type>
      <name>Duplicate</name>
      <anchorfile>namespaceMLAPI.html</anchorfile>
      <anchor>a915d25039bd3ffc80371095cec7f05eb</anchor>
      <arglist>(const MultiVector &amp;y)</arglist>
    </member>
    <member kind="function">
      <type>MultiVector</type>
      <name>Duplicate</name>
      <anchorfile>namespaceMLAPI.html</anchorfile>
      <anchor>a0bc85c1f4ed364fac977d1608c3be2e4</anchor>
      <arglist>(const MultiVector &amp;y, const int v)</arglist>
    </member>
    <member kind="function">
      <type>MultiVector</type>
      <name>Extract</name>
      <anchorfile>namespaceMLAPI.html</anchorfile>
      <anchor>a22a408a5afb903611c3b87f9dbb214b1</anchor>
      <arglist>(const MultiVector &amp;y, const int v)</arglist>
    </member>
    <member kind="function">
      <type>MultiVector</type>
      <name>Redistribute</name>
      <anchorfile>namespaceMLAPI.html</anchorfile>
      <anchor>ae89073713c2f0652695632215d7c7c48</anchor>
      <arglist>(const MultiVector &amp;y, const int NumEquations)</arglist>
    </member>
    <member kind="function">
      <type>Operator</type>
      <name>GetRAP</name>
      <anchorfile>namespaceMLAPI.html</anchorfile>
      <anchor>a45dc3eaf084df2ed0baa2ec5e8466088</anchor>
      <arglist>(const Operator &amp;R, const Operator &amp;A, const Operator &amp;P)</arglist>
    </member>
    <member kind="function">
      <type>Operator</type>
      <name>GetTranspose</name>
      <anchorfile>namespaceMLAPI.html</anchorfile>
      <anchor>adc2f2f4e84b5e47bec27f06db43047cb</anchor>
      <arglist>(const Operator &amp;A, const bool byrow=true)</arglist>
    </member>
    <member kind="function">
      <type>Operator</type>
      <name>GetIdentity</name>
      <anchorfile>namespaceMLAPI.html</anchorfile>
      <anchor>a4eb030282f617cd49645de146b2579de</anchor>
      <arglist>(const Space &amp;DomainSpace, const Space &amp;RangeSpace)</arglist>
    </member>
    <member kind="function">
      <type>MultiVector</type>
      <name>GetDiagonal</name>
      <anchorfile>namespaceMLAPI.html</anchorfile>
      <anchor>ac10cde78ae263ce22e5c4208a7afac07</anchor>
      <arglist>(const Operator &amp;A)</arglist>
    </member>
    <member kind="function">
      <type>MultiVector</type>
      <name>GetDiagonal</name>
      <anchorfile>namespaceMLAPI.html</anchorfile>
      <anchor>a6b0c3607b5c0eaa96bab4e25f71a241c</anchor>
      <arglist>(const Operator &amp;A, const int offset)</arglist>
    </member>
    <member kind="function">
      <type>Operator</type>
      <name>GetDiagonal</name>
      <anchorfile>namespaceMLAPI.html</anchorfile>
      <anchor>a804e2b0509398ce872ce3745878fe488</anchor>
      <arglist>(const MultiVector &amp;D)</arglist>
    </member>
    <member kind="function">
      <type>Operator</type>
      <name>GetJacobiIterationOperator</name>
      <anchorfile>namespaceMLAPI.html</anchorfile>
      <anchor>a06460ec53f3dd3b2ef482581b15217f1</anchor>
      <arglist>(const Operator &amp;Amat, double Damping)</arglist>
    </member>
    <member kind="function">
      <type>Operator</type>
      <name>GetPtent1D</name>
      <anchorfile>namespaceMLAPI.html</anchorfile>
      <anchor>a6787be3f3c96d1d2f608004d2412c18e</anchor>
      <arglist>(const MultiVector &amp;D, const int offset=0)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>AnalyzeCheap</name>
      <anchorfile>namespaceMLAPI.html</anchorfile>
      <anchor>a0a2a385d7a18181c321cdde429a0e764</anchor>
      <arglist>(const Operator &amp;A)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>PrintSparsity</name>
      <anchorfile>namespaceMLAPI.html</anchorfile>
      <anchor>a306e5ad67267cd2c303f54262cfc7930</anchor>
      <arglist>(const Operator &amp;A, int NumPDEEquations=1)</arglist>
    </member>
    <member kind="function">
      <type>Operator</type>
      <name>GetScaledOperator</name>
      <anchorfile>namespaceMLAPI.html</anchorfile>
      <anchor>a89f0cce653d7c8e7002e7bc73c7c9dc3</anchor>
      <arglist>(const Operator &amp;A, const double alpha)</arglist>
    </member>
    <member kind="function">
      <type>Operator</type>
      <name>Duplicate</name>
      <anchorfile>namespaceMLAPI.html</anchorfile>
      <anchor>a580aefe59d91fce2b76a69d342e8b444</anchor>
      <arglist>(const Operator &amp;A)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>ReadSAMISMatrix</name>
      <anchorfile>namespaceMLAPI.html</anchorfile>
      <anchor>a81a7c9724c0c3ba52f7404ef49c9fe43</anchor>
      <arglist>(const char *filen, Operator &amp;A, int &amp;NumPDEEqns)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>ReadSAMISKernel</name>
      <anchorfile>namespaceMLAPI.html</anchorfile>
      <anchor>ad59578977b32ee701565d837a12baa5a</anchor>
      <arglist>(const char *myKerFileName, MultiVector &amp;A, const int limKer=-1)</arglist>
    </member>
    <member kind="function">
      <type>ML_Comm *</type>
      <name>GetML_Comm</name>
      <anchorfile>namespaceMLAPI.html</anchorfile>
      <anchor>a2b92d9681a55c4d314249c244e676502</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Epetra_Comm &amp;</type>
      <name>GetEpetra_Comm</name>
      <anchorfile>namespaceMLAPI.html</anchorfile>
      <anchor>a639a90dc98e2418eca8be3d3865e2709</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Barrier</name>
      <anchorfile>namespaceMLAPI.html</anchorfile>
      <anchor>ac28167b38770ed2387cd07be88d06859</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetMyPID</name>
      <anchorfile>namespaceMLAPI.html</anchorfile>
      <anchor>a311e8c40d629be1e5ea38609c63f6f89</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetNumProcs</name>
      <anchorfile>namespaceMLAPI.html</anchorfile>
      <anchor>a0b1fd48ca2666c29d0ecc379353839f1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetPrintLevel</name>
      <anchorfile>namespaceMLAPI.html</anchorfile>
      <anchor>a7328d4c8b158abc1764d1db95790f1e8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetPrintLevel</name>
      <anchorfile>namespaceMLAPI.html</anchorfile>
      <anchor>a001fca7fbfcb719c164dd73ef3ce758d</anchor>
      <arglist>(int Level)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Init</name>
      <anchorfile>namespaceMLAPI.html</anchorfile>
      <anchor>af368e6d9fa55ccd00a482cf01dbb9828</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Finalize</name>
      <anchorfile>namespaceMLAPI.html</anchorfile>
      <anchor>aabd0be9dafbd3cca6df87930cd78e065</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="page">
    <name>ml_multilevelpreconditioner</name>
    <title>Example of use ML_Epetra::MultiLevelPreconditioner</title>
    <filename>ml_multilevelpreconditioner</filename>
  </compound>
  <compound kind="page">
    <name>ml_multileveloperator</name>
    <title>Example of use of ML_Epetra::MultiLevelOperator</title>
    <filename>ml_multileveloperator</filename>
  </compound>
  <compound kind="page">
    <name>mlguide_c</name>
    <title>mlguide.c</title>
    <filename>mlguide_c</filename>
  </compound>
  <compound kind="page">
    <name>mlguide_par_c</name>
    <title>mlguide_par.c</title>
    <filename>mlguide_par_c</filename>
  </compound>
  <compound kind="page">
    <name>ml_aztec_simple_c</name>
    <title>ml_aztec_simple.c</title>
    <filename>ml_aztec_simple_c</filename>
  </compound>
  <compound kind="page">
    <name>ml_operator_cpp</name>
    <title>ml_operator.cpp</title>
    <filename>ml_operator_cpp</filename>
  </compound>
  <compound kind="page">
    <name>ml_preconditioner_cpp</name>
    <title>ml_preconditioner.cpp</title>
    <filename>ml_preconditioner_cpp</filename>
  </compound>
  <compound kind="page">
    <name>ml_2level_DD_cpp</name>
    <title>ml_2level_DD.cpp</title>
    <filename>ml_2level_DD_cpp</filename>
  </compound>
  <compound kind="page">
    <name>ml_viz_cpp</name>
    <title>ml_viz.cpp</title>
    <filename>ml_viz_cpp</filename>
  </compound>
  <compound kind="page">
    <name>ml_analyze_cpp</name>
    <title>ml_analyze.cpp</title>
    <filename>ml_analyze_cpp</filename>
  </compound>
  <compound kind="page">
    <name>ml_read_maxwell_cpp</name>
    <title>ml_read_maxwell.cpp</title>
    <filename>ml_read_maxwell_cpp</filename>
  </compound>
  <compound kind="page">
    <name>ml_changelog</name>
    <title>ChangeLog</title>
    <filename>ml_changelog</filename>
  </compound>
  <compound kind="page">
    <name>ml_readme</name>
    <title>README</title>
    <filename>ml_readme</filename>
  </compound>
  <compound kind="page">
    <name>ml_blackboard_cpp</name>
    <title>BlackBoard.cpp</title>
    <filename>ml_blackboard_cpp</filename>
  </compound>
  <compound kind="page">
    <name>ml_powermethod</name>
    <title>PowerMethod.cpp</title>
    <filename>ml_powermethod</filename>
  </compound>
  <compound kind="page">
    <name>ml_epetrainterface</name>
    <title>EpetraInterface.cpp</title>
    <filename>ml_epetrainterface</filename>
  </compound>
  <compound kind="page">
    <name>ml_multilevel</name>
    <title>MultiLevel.cpp</title>
    <filename>ml_multilevel</filename>
  </compound>
  <compound kind="page">
    <name>ml_richardson</name>
    <title>Richardson.cpp</title>
    <filename>ml_richardson</filename>
  </compound>
  <compound kind="page">
    <name>ml_adaptivesa</name>
    <title>AdaptiveSA.cpp</title>
    <filename>ml_adaptivesa</filename>
  </compound>
  <compound kind="page">
    <name>ml_twolevel</name>
    <title>TwoLevelDDAdditive.cpp</title>
    <filename>ml_twolevel</filename>
  </compound>
  <compound kind="page">
    <name>ml_mlapi</name>
    <title>Overview of MLAPI</title>
    <filename>ml_mlapi</filename>
    <docanchor file="ml_mlapi" title="Table of contents">mlapi_tab</docanchor>
    <docanchor file="ml_mlapi" title="Introduction to MLAPI">mlapi_intro</docanchor>
    <docanchor file="ml_mlapi" title="Use of MultiVector">mlapi_multivector</docanchor>
    <docanchor file="ml_mlapi" title="Memory Management">mlapi_memory</docanchor>
    <docanchor file="ml_mlapi" title="Available Preconditioners">mlapi_prec</docanchor>
    <docanchor file="ml_mlapi" title="Interface with Epetra Objects">mlapi_epetrainterface</docanchor>
  </compound>
  <compound kind="page">
    <name>index</name>
    <title>ML: Multi Level Preconditioning Package</title>
    <filename>index</filename>
    <docanchor file="index" title="Table of Contents">ml_table</docanchor>
    <docanchor file="index" title="Where to find documentation">ml_doc</docanchor>
    <docanchor file="index" title="Examples source code">ml_examples</docanchor>
    <docanchor file="index" title="Quick introduction to the ML/Epetra interface">ml_minitutorial</docanchor>
    <docanchor file="index" title="The ML_Epetra::MultiLevelPreconditioner class">ml_MLP</docanchor>
    <docanchor file="index" title="Main Structures of ML">ml_mainstruct</docanchor>
    <docanchor file="index" title="Conversion utilities from/to Epetra matrices.">ml_conversion</docanchor>
    <docanchor file="index" title="ML interface to Amesos">ml_amesos</docanchor>
    <docanchor file="index" title="ML interface to IFPACK">ml_ifpack</docanchor>
    <docanchor file="index" title="ML interface to Anasazi">ml_anasazi</docanchor>
    <docanchor file="index" title="Overview of MLAPI">ml_mlapi_intro</docanchor>
    <docanchor file="index" title="ML for Python Applications">ml_python</docanchor>
    <docanchor file="index" title="ML/Thyra adapters">ml_thyra</docanchor>
    <docanchor file="index" title="Debugging Utilities">ml_debug</docanchor>
    <docanchor file="index" title="(Incomplete) History of visible changes">ml_changes</docanchor>
    <docanchor file="index" title="Copyright">ml_copyright</docanchor>
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
