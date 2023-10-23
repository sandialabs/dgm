<?xml version='1.0' encoding='UTF-8' standalone='yes' ?>
<tagfile>
  <compound kind="file">
    <name>example_CurlLSFEM.cpp</name>
    <path>/Users/sscoll/dist/trilinos/packages/trilinoscouplings/examples/scaling/</path>
    <filename>example__CurlLSFEM_8cpp</filename>
    <class kind="struct">fecomp</class>
    <member kind="function">
      <type>void</type>
      <name>TestMultiLevelPreconditioner_CurlLSFEM</name>
      <anchorfile>example__CurlLSFEM_8cpp.html</anchorfile>
      <anchor>a2b5a93b2e8196982046dea6bd12f98f5</anchor>
      <arglist>(char ProblemType[], Teuchos::ParameterList &amp;MLList, Epetra_CrsMatrix &amp;CurlCurl, Epetra_CrsMatrix &amp;D0clean, Epetra_CrsMatrix &amp;M0inv, Epetra_CrsMatrix &amp;M1, Epetra_MultiVector &amp;xh, Epetra_MultiVector &amp;b, double &amp;TotalErrorResidual, double &amp;TotalErrorExactSol)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>evalu</name>
      <anchorfile>example__CurlLSFEM_8cpp.html</anchorfile>
      <anchor>abc70c1d859ea706bab25b57f74d17b47</anchor>
      <arglist>(double &amp;uExact0, double &amp;uExact1, double &amp;uExact2, double &amp;x, double &amp;y, double &amp;z)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>evalDivu</name>
      <anchorfile>example__CurlLSFEM_8cpp.html</anchorfile>
      <anchor>a9c445afa9c0103c8e26a2f42d683ac39</anchor>
      <arglist>(double &amp;x, double &amp;y, double &amp;z, double &amp;mu)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>evalCurlu</name>
      <anchorfile>example__CurlLSFEM_8cpp.html</anchorfile>
      <anchor>a4f5912a0eef30279ea7dedf76e0589e7</anchor>
      <arglist>(double &amp;curlu0, double &amp;curlu1, double &amp;curlu2, double &amp;x, double &amp;y, double &amp;z, double &amp;mu)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>evalGradDivu</name>
      <anchorfile>example__CurlLSFEM_8cpp.html</anchorfile>
      <anchor>a161413d5e20418b5a4cd889ea9c73ed7</anchor>
      <arglist>(double &amp;gradDivu0, double &amp;gradDivu1, double &amp;gradDivu2, double &amp;x, double &amp;y, double &amp;z, double &amp;mu)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Multiply_Ones</name>
      <anchorfile>example__CurlLSFEM_8cpp.html</anchorfile>
      <anchor>ae3de3e0aaf131132d5826fd10a3d1941</anchor>
      <arglist>(const Epetra_CrsMatrix &amp;A, const Epetra_Vector &amp;x, Epetra_Vector &amp;y)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>solution_test</name>
      <anchorfile>example__CurlLSFEM_8cpp.html</anchorfile>
      <anchor>a0e6d87c364a8f93cf33d5c75c9876a5c</anchor>
      <arglist>(string msg, const Epetra_Operator &amp;A, const Epetra_MultiVector &amp;lhs, const Epetra_MultiVector &amp;rhs, const Epetra_MultiVector &amp;xexact, Epetra_Time &amp;Time, double &amp;TotalErrorExactSol, double &amp;TotalErrorResidual)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>example_CVFEM.cpp</name>
    <path>/Users/sscoll/dist/trilinos/packages/trilinoscouplings/examples/scaling/</path>
    <filename>example__CVFEM_8cpp</filename>
    <member kind="function">
      <type>const Scalar</type>
      <name>exactSolution</name>
      <anchorfile>example__CVFEM_8cpp.html</anchorfile>
      <anchor>a451a80b0b5add51ef44028dd0fe41c45</anchor>
      <arglist>(const Scalar &amp;x, const Scalar &amp;y)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>advectionVelocity</name>
      <anchorfile>example__CVFEM_8cpp.html</anchorfile>
      <anchor>a0989fda2e32dc35e7d4911a44b1399fc</anchor>
      <arglist>(Scalar advVel[2], const Scalar &amp;x, const Scalar &amp;y, const std::string problem)</arglist>
    </member>
    <member kind="function">
      <type>const Scalar1</type>
      <name>diffusivity</name>
      <anchorfile>example__CVFEM_8cpp.html</anchorfile>
      <anchor>a6761b16d69a046ea8f128379e9094be8</anchor>
      <arglist>(const Scalar1 &amp;x, const Scalar1 &amp;y, const Scalar2 &amp;epsilon, const bool variableEpsilon)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>exactSolutionGrad</name>
      <anchorfile>example__CVFEM_8cpp.html</anchorfile>
      <anchor>a39ad6b00a882135f38e06d1fe79d5b37</anchor>
      <arglist>(Scalar gradExact[2], const Scalar &amp;x, const Scalar &amp;y)</arglist>
    </member>
    <member kind="function">
      <type>const Scalar1</type>
      <name>sourceTerm</name>
      <anchorfile>example__CVFEM_8cpp.html</anchorfile>
      <anchor>a359f364128be76b2e00b4b309bae4f1f</anchor>
      <arglist>(Scalar1 &amp;x, Scalar1 &amp;y, Scalar2 &amp;epsilon, const bool variableEpsilon, const std::string problem)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>evaluateExactSolution</name>
      <anchorfile>example__CVFEM_8cpp.html</anchorfile>
      <anchor>af1618d152ee05bde4c0e26519eacf14e</anchor>
      <arglist>(ArrayOut &amp;exactSolutionValues, const ArrayIn &amp;evaluationPoints)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>evaluateExactSolutionGrad</name>
      <anchorfile>example__CVFEM_8cpp.html</anchorfile>
      <anchor>aaf5fe8202359578160eb300c38b0db0e</anchor>
      <arglist>(ArrayOut &amp;exactSolutionGradValues, const ArrayIn &amp;evaluationPoints)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>createMesh</name>
      <anchorfile>example__CVFEM_8cpp.html</anchorfile>
      <anchor>a8ea20da6c3ee648be291829d47fbf25c</anchor>
      <arglist>(ArrayOut1 &amp;elemToNode, ArrayOut2 &amp;nodeCoords, ArrayOut1 &amp;bcLeftId, ArrayOut1 &amp;bcRightId, ArrayOut1 &amp;bcTopId, ArrayOut1 &amp;bcBotId, const std::string &amp;meshType, const Scalar &amp;meshSize)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>example_DivLSFEM.cpp</name>
    <path>/Users/sscoll/dist/trilinos/packages/trilinoscouplings/examples/scaling/</path>
    <filename>example__DivLSFEM_8cpp</filename>
    <class kind="struct">fecomp</class>
    <member kind="function">
      <type>int</type>
      <name>Multiply_Abs</name>
      <anchorfile>example__DivLSFEM_8cpp.html</anchorfile>
      <anchor>ae653458a9a8f534b25d27231b421b49f</anchor>
      <arglist>(const Epetra_CrsMatrix &amp;A, const Epetra_Vector &amp;x, Epetra_Vector &amp;y)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>TestMultiLevelPreconditioner_DivLSFEM</name>
      <anchorfile>example__DivLSFEM_8cpp.html</anchorfile>
      <anchor>a0435815886acb653020589813d0e5d14</anchor>
      <arglist>(char ProblemType[], Teuchos::ParameterList &amp;MLList, Epetra_CrsMatrix &amp;GradDiv, Epetra_CrsMatrix &amp;D0clean, Epetra_CrsMatrix &amp;D1clean, Epetra_CrsMatrix &amp;FaceNode, Epetra_CrsMatrix &amp;M1, Epetra_CrsMatrix &amp;M1inv, Epetra_CrsMatrix &amp;M2, Epetra_MultiVector &amp;xh, Epetra_MultiVector &amp;b, double &amp;TotalErrorResidual, double &amp;TotalErrorExactSol)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>evalu</name>
      <anchorfile>example__DivLSFEM_8cpp.html</anchorfile>
      <anchor>abc70c1d859ea706bab25b57f74d17b47</anchor>
      <arglist>(double &amp;uExact0, double &amp;uExact1, double &amp;uExact2, double &amp;x, double &amp;y, double &amp;z)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>evalDivu</name>
      <anchorfile>example__DivLSFEM_8cpp.html</anchorfile>
      <anchor>a4b1e2d82b116aeada95393ff1a086335</anchor>
      <arglist>(double &amp;x, double &amp;y, double &amp;z)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>evalCurlu</name>
      <anchorfile>example__DivLSFEM_8cpp.html</anchorfile>
      <anchor>a4f5912a0eef30279ea7dedf76e0589e7</anchor>
      <arglist>(double &amp;curlu0, double &amp;curlu1, double &amp;curlu2, double &amp;x, double &amp;y, double &amp;z, double &amp;mu)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>evalCurlCurlu</name>
      <anchorfile>example__DivLSFEM_8cpp.html</anchorfile>
      <anchor>aff21915c0412adc1394e0c33ba9150fe</anchor>
      <arglist>(double &amp;curlCurlu0, double &amp;curlCurlu1, double &amp;curlCurlu2, double &amp;x, double &amp;y, double &amp;z, double &amp;mu)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Multiply_Ones</name>
      <anchorfile>example__DivLSFEM_8cpp.html</anchorfile>
      <anchor>ae3de3e0aaf131132d5826fd10a3d1941</anchor>
      <arglist>(const Epetra_CrsMatrix &amp;A, const Epetra_Vector &amp;x, Epetra_Vector &amp;y)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>solution_test</name>
      <anchorfile>example__DivLSFEM_8cpp.html</anchorfile>
      <anchor>a0e6d87c364a8f93cf33d5c75c9876a5c</anchor>
      <arglist>(string msg, const Epetra_Operator &amp;A, const Epetra_MultiVector &amp;lhs, const Epetra_MultiVector &amp;rhs, const Epetra_MultiVector &amp;xexact, Epetra_Time &amp;Time, double &amp;TotalErrorExactSol, double &amp;TotalErrorResidual)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>example_Maxwell.cpp</name>
    <path>/Users/sscoll/dist/trilinos/packages/trilinoscouplings/examples/scaling/</path>
    <filename>example__Maxwell_8cpp</filename>
    <class kind="struct">fecomp</class>
    <member kind="function">
      <type>void</type>
      <name>TestMultiLevelPreconditioner_Maxwell</name>
      <anchorfile>example__Maxwell_8cpp.html</anchorfile>
      <anchor>a78e899ebb5c32978429cd2e3a1de9529</anchor>
      <arglist>(char ProblemType[], Teuchos::ParameterList &amp;MLList, Epetra_CrsMatrix &amp;CurlCurl, Epetra_CrsMatrix &amp;D0clean, Epetra_CrsMatrix &amp;M0inv, Epetra_CrsMatrix &amp;M1, Epetra_MultiVector &amp;xh, Epetra_MultiVector &amp;b, double &amp;TotalErrorResidual, double &amp;TotalErrorExactSol)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>evalu</name>
      <anchorfile>example__Maxwell_8cpp.html</anchorfile>
      <anchor>abc70c1d859ea706bab25b57f74d17b47</anchor>
      <arglist>(double &amp;uExact0, double &amp;uExact1, double &amp;uExact2, double &amp;x, double &amp;y, double &amp;z)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>evalCurlu</name>
      <anchorfile>example__Maxwell_8cpp.html</anchorfile>
      <anchor>a4f5912a0eef30279ea7dedf76e0589e7</anchor>
      <arglist>(double &amp;curlu0, double &amp;curlu1, double &amp;curlu2, double &amp;x, double &amp;y, double &amp;z, double &amp;mu)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>evalCurlCurlu</name>
      <anchorfile>example__Maxwell_8cpp.html</anchorfile>
      <anchor>a05dd35be2c58e806c7723bd5269de173</anchor>
      <arglist>(double &amp;curlcurlu0, double &amp;curlcurlu1, double &amp;curlcurlu2, double &amp;x, double &amp;y, double &amp;z, double &amp;mu)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Multiply_Ones</name>
      <anchorfile>example__Maxwell_8cpp.html</anchorfile>
      <anchor>ae3de3e0aaf131132d5826fd10a3d1941</anchor>
      <arglist>(const Epetra_CrsMatrix &amp;A, const Epetra_Vector &amp;x, Epetra_Vector &amp;y)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>solution_test</name>
      <anchorfile>example__Maxwell_8cpp.html</anchorfile>
      <anchor>a0e6d87c364a8f93cf33d5c75c9876a5c</anchor>
      <arglist>(string msg, const Epetra_Operator &amp;A, const Epetra_MultiVector &amp;lhs, const Epetra_MultiVector &amp;rhs, const Epetra_MultiVector &amp;xexact, Epetra_Time &amp;Time, double &amp;TotalErrorExactSol, double &amp;TotalErrorResidual)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>example_Poisson.cpp</name>
    <path>/Users/sscoll/dist/trilinos/packages/trilinoscouplings/examples/scaling/</path>
    <filename>example__Poisson_8cpp</filename>
    <member kind="function">
      <type>int</type>
      <name>TestMultiLevelPreconditionerLaplace</name>
      <anchorfile>example__Poisson_8cpp.html</anchorfile>
      <anchor>a1a44741db70410027ee1cf256cd837e2</anchor>
      <arglist>(char ProblemType[], Teuchos::ParameterList &amp;MLList, Epetra_CrsMatrix &amp;A, const Epetra_MultiVector &amp;xexact, Epetra_MultiVector &amp;b, Epetra_MultiVector &amp;uh, double &amp;TotalErrorResidual, double &amp;TotalErrorExactSol)</arglist>
    </member>
    <member kind="function">
      <type>const Scalar</type>
      <name>exactSolution</name>
      <anchorfile>example__Poisson_8cpp.html</anchorfile>
      <anchor>ad771d072e4d6491a77d5304024cdc6b2</anchor>
      <arglist>(const Scalar &amp;x, const Scalar &amp;y, const Scalar &amp;z)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>materialTensor</name>
      <anchorfile>example__Poisson_8cpp.html</anchorfile>
      <anchor>a40bb49a1cabdf5e7c716c0d017614870</anchor>
      <arglist>(Scalar material[][3], const Scalar &amp;x, const Scalar &amp;y, const Scalar &amp;z)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>exactSolutionGrad</name>
      <anchorfile>example__Poisson_8cpp.html</anchorfile>
      <anchor>a6718d0dd54ef59594d95716d4f265994</anchor>
      <arglist>(Scalar gradExact[3], const Scalar &amp;x, const Scalar &amp;y, const Scalar &amp;z)</arglist>
    </member>
    <member kind="function">
      <type>const Scalar</type>
      <name>sourceTerm</name>
      <anchorfile>example__Poisson_8cpp.html</anchorfile>
      <anchor>a26af8a2eb9265dc0e30f03a39e56a320</anchor>
      <arglist>(Scalar &amp;x, Scalar &amp;y, Scalar &amp;z)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>evaluateMaterialTensor</name>
      <anchorfile>example__Poisson_8cpp.html</anchorfile>
      <anchor>a0225b4e280626d02bef9ab551001a12f</anchor>
      <arglist>(ArrayOut &amp;worksetMaterialValues, const ArrayIn &amp;evaluationPoints)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>evaluateSourceTerm</name>
      <anchorfile>example__Poisson_8cpp.html</anchorfile>
      <anchor>ab1ff876999b2ba7cf5db528be6a0ca72</anchor>
      <arglist>(ArrayOut &amp;sourceTermValues, const ArrayIn &amp;evaluationPoints)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>evaluateExactSolution</name>
      <anchorfile>example__Poisson_8cpp.html</anchorfile>
      <anchor>af1618d152ee05bde4c0e26519eacf14e</anchor>
      <arglist>(ArrayOut &amp;exactSolutionValues, const ArrayIn &amp;evaluationPoints)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>evaluateExactSolutionGrad</name>
      <anchorfile>example__Poisson_8cpp.html</anchorfile>
      <anchor>aaf5fe8202359578160eb300c38b0db0e</anchor>
      <arglist>(ArrayOut &amp;exactSolutionGradValues, const ArrayIn &amp;evaluationPoints)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>example_Poisson_NoFE_Tpetra.cpp</name>
    <path>/Users/sscoll/dist/trilinos/packages/trilinoscouplings/examples/scaling/</path>
    <filename>example__Poisson__NoFE__Tpetra_8cpp</filename>
    <member kind="function">
      <type>const Scalar</type>
      <name>exactSolution</name>
      <anchorfile>example__Poisson__NoFE__Tpetra_8cpp.html</anchorfile>
      <anchor>ad771d072e4d6491a77d5304024cdc6b2</anchor>
      <arglist>(const Scalar &amp;x, const Scalar &amp;y, const Scalar &amp;z)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>materialTensor</name>
      <anchorfile>example__Poisson__NoFE__Tpetra_8cpp.html</anchorfile>
      <anchor>a40bb49a1cabdf5e7c716c0d017614870</anchor>
      <arglist>(Scalar material[][3], const Scalar &amp;x, const Scalar &amp;y, const Scalar &amp;z)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>exactSolutionGrad</name>
      <anchorfile>example__Poisson__NoFE__Tpetra_8cpp.html</anchorfile>
      <anchor>a6718d0dd54ef59594d95716d4f265994</anchor>
      <arglist>(Scalar gradExact[3], const Scalar &amp;x, const Scalar &amp;y, const Scalar &amp;z)</arglist>
    </member>
    <member kind="function">
      <type>const Scalar</type>
      <name>sourceTerm</name>
      <anchorfile>example__Poisson__NoFE__Tpetra_8cpp.html</anchorfile>
      <anchor>a26af8a2eb9265dc0e30f03a39e56a320</anchor>
      <arglist>(Scalar &amp;x, Scalar &amp;y, Scalar &amp;z)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>evaluateMaterialTensor</name>
      <anchorfile>example__Poisson__NoFE__Tpetra_8cpp.html</anchorfile>
      <anchor>a0225b4e280626d02bef9ab551001a12f</anchor>
      <arglist>(ArrayOut &amp;worksetMaterialValues, const ArrayIn &amp;evaluationPoints)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>evaluateSourceTerm</name>
      <anchorfile>example__Poisson__NoFE__Tpetra_8cpp.html</anchorfile>
      <anchor>ab1ff876999b2ba7cf5db528be6a0ca72</anchor>
      <arglist>(ArrayOut &amp;sourceTermValues, const ArrayIn &amp;evaluationPoints)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>evaluateExactSolution</name>
      <anchorfile>example__Poisson__NoFE__Tpetra_8cpp.html</anchorfile>
      <anchor>af1618d152ee05bde4c0e26519eacf14e</anchor>
      <arglist>(ArrayOut &amp;exactSolutionValues, const ArrayIn &amp;evaluationPoints)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>evaluateExactSolutionGrad</name>
      <anchorfile>example__Poisson__NoFE__Tpetra_8cpp.html</anchorfile>
      <anchor>aaf5fe8202359578160eb300c38b0db0e</anchor>
      <arglist>(ArrayOut &amp;exactSolutionGradValues, const ArrayIn &amp;evaluationPoints)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>example_Poisson_stk.cpp</name>
    <path>/Users/sscoll/dist/trilinos/packages/trilinoscouplings/examples/scaling/</path>
    <filename>example__Poisson__stk_8cpp</filename>
    <member kind="function">
      <type>const Scalar</type>
      <name>exactSolution</name>
      <anchorfile>example__Poisson__stk_8cpp.html</anchorfile>
      <anchor>ad771d072e4d6491a77d5304024cdc6b2</anchor>
      <arglist>(const Scalar &amp;x, const Scalar &amp;y, const Scalar &amp;z)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>materialTensor</name>
      <anchorfile>example__Poisson__stk_8cpp.html</anchorfile>
      <anchor>a40bb49a1cabdf5e7c716c0d017614870</anchor>
      <arglist>(Scalar material[][3], const Scalar &amp;x, const Scalar &amp;y, const Scalar &amp;z)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>exactSolutionGrad</name>
      <anchorfile>example__Poisson__stk_8cpp.html</anchorfile>
      <anchor>a6718d0dd54ef59594d95716d4f265994</anchor>
      <arglist>(Scalar gradExact[3], const Scalar &amp;x, const Scalar &amp;y, const Scalar &amp;z)</arglist>
    </member>
    <member kind="function">
      <type>const Scalar</type>
      <name>sourceTerm</name>
      <anchorfile>example__Poisson__stk_8cpp.html</anchorfile>
      <anchor>a26af8a2eb9265dc0e30f03a39e56a320</anchor>
      <arglist>(Scalar &amp;x, Scalar &amp;y, Scalar &amp;z)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>evaluateMaterialTensor</name>
      <anchorfile>example__Poisson__stk_8cpp.html</anchorfile>
      <anchor>a0225b4e280626d02bef9ab551001a12f</anchor>
      <arglist>(ArrayOut &amp;worksetMaterialValues, const ArrayIn &amp;evaluationPoints)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>evaluateSourceTerm</name>
      <anchorfile>example__Poisson__stk_8cpp.html</anchorfile>
      <anchor>ab1ff876999b2ba7cf5db528be6a0ca72</anchor>
      <arglist>(ArrayOut &amp;sourceTermValues, const ArrayIn &amp;evaluationPoints)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>evaluateExactSolution</name>
      <anchorfile>example__Poisson__stk_8cpp.html</anchorfile>
      <anchor>af1618d152ee05bde4c0e26519eacf14e</anchor>
      <arglist>(ArrayOut &amp;exactSolutionValues, const ArrayIn &amp;evaluationPoints)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>evaluateExactSolutionGrad</name>
      <anchorfile>example__Poisson__stk_8cpp.html</anchorfile>
      <anchor>aaf5fe8202359578160eb300c38b0db0e</anchor>
      <arglist>(ArrayOut &amp;exactSolutionGradValues, const ArrayIn &amp;evaluationPoints)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>getBasis</name>
      <anchorfile>example__Poisson__stk_8cpp.html</anchorfile>
      <anchor>aa4843307c61aefa3e3db588189ebf83f</anchor>
      <arglist>(Teuchos::RCP&lt; Intrepid::Basis&lt; double, IntrepidFieldContainer &gt; &gt; &amp;basis, const shards::CellTopology &amp;cellTopology, int order)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>example_StabilizedADR.cpp</name>
    <path>/Users/sscoll/dist/trilinos/packages/trilinoscouplings/examples/scaling/</path>
    <filename>example__StabilizedADR_8cpp</filename>
    <member kind="function">
      <type>const Scalar</type>
      <name>exactSolution</name>
      <anchorfile>example__StabilizedADR_8cpp.html</anchorfile>
      <anchor>ad771d072e4d6491a77d5304024cdc6b2</anchor>
      <arglist>(const Scalar &amp;x, const Scalar &amp;y, const Scalar &amp;z)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>diffusionTensor</name>
      <anchorfile>example__StabilizedADR_8cpp.html</anchorfile>
      <anchor>a47e17b1c31ec9c6036f3dfbabbef3e8e</anchor>
      <arglist>(Scalar diffusion[][3], const Scalar &amp;x, const Scalar &amp;y, const Scalar &amp;z)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>advectiveVector</name>
      <anchorfile>example__StabilizedADR_8cpp.html</anchorfile>
      <anchor>a80c75755898f5fd87245694681854594</anchor>
      <arglist>(Scalar advection[3], const Scalar &amp;x, const Scalar &amp;y, const Scalar &amp;z)</arglist>
    </member>
    <member kind="function">
      <type>const Scalar</type>
      <name>reactionTerm</name>
      <anchorfile>example__StabilizedADR_8cpp.html</anchorfile>
      <anchor>a6b8d0108c051e85fed37cb215b786f47</anchor>
      <arglist>(const Scalar &amp;x, const Scalar &amp;y, const Scalar &amp;z)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>exactSolutionGrad</name>
      <anchorfile>example__StabilizedADR_8cpp.html</anchorfile>
      <anchor>a6718d0dd54ef59594d95716d4f265994</anchor>
      <arglist>(Scalar gradExact[3], const Scalar &amp;x, const Scalar &amp;y, const Scalar &amp;z)</arglist>
    </member>
    <member kind="function">
      <type>const Scalar</type>
      <name>sourceTerm</name>
      <anchorfile>example__StabilizedADR_8cpp.html</anchorfile>
      <anchor>a26af8a2eb9265dc0e30f03a39e56a320</anchor>
      <arglist>(Scalar &amp;x, Scalar &amp;y, Scalar &amp;z)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>evaluateDiffusionTensor</name>
      <anchorfile>example__StabilizedADR_8cpp.html</anchorfile>
      <anchor>a2d658201374273482eca233246929878</anchor>
      <arglist>(ArrayOut &amp;worksetDiffusionValues, const ArrayIn &amp;evaluationPoints)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>evaluateAdvectiveVector</name>
      <anchorfile>example__StabilizedADR_8cpp.html</anchorfile>
      <anchor>a1cf5f082742a41e8d1ffef0bd31229b8</anchor>
      <arglist>(ArrayOut &amp;worksetAdvectionValues, const ArrayIn &amp;evaluationPoints)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>evaluateReactionCoefficient</name>
      <anchorfile>example__StabilizedADR_8cpp.html</anchorfile>
      <anchor>a20d8e200c39aee14df0c5e596bc1fc0a</anchor>
      <arglist>(ArrayOut &amp;worksetReactionValues, const ArrayIn &amp;evaluationPoints)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>evaluateSourceTerm</name>
      <anchorfile>example__StabilizedADR_8cpp.html</anchorfile>
      <anchor>ab1ff876999b2ba7cf5db528be6a0ca72</anchor>
      <arglist>(ArrayOut &amp;sourceTermValues, const ArrayIn &amp;evaluationPoints)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>evaluateExactSolution</name>
      <anchorfile>example__StabilizedADR_8cpp.html</anchorfile>
      <anchor>af1618d152ee05bde4c0e26519eacf14e</anchor>
      <arglist>(ArrayOut &amp;exactSolutionValues, const ArrayIn &amp;evaluationPoints)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>evaluateExactSolutionGrad</name>
      <anchorfile>example__StabilizedADR_8cpp.html</anchorfile>
      <anchor>aaf5fe8202359578160eb300c38b0db0e</anchor>
      <arglist>(ArrayOut &amp;exactSolutionGradValues, const ArrayIn &amp;evaluationPoints)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>getPamgenMesh</name>
      <anchorfile>example__StabilizedADR_8cpp.html</anchorfile>
      <anchor>a104cc80b573c41d04d419dfc07c64d91</anchor>
      <arglist>(FieldContainer&lt; Scalar &gt; &amp;localNodeCoordsFC, FieldContainer&lt; long long &gt; &amp;localCellToNodeFC, FieldContainer&lt; int &gt; &amp;nodeOnBoundaryFC, FieldContainer&lt; bool &gt; &amp;nodeIsOwnedFC, FieldContainer&lt; long long &gt; &amp;globalNodeIdsFC, const std::string &amp;meshInput, const int &amp;procRank, const int &amp;numProcs, const Epetra_Comm &amp;Comm, Epetra_Time &amp;Time, const string &amp;message, const int verbose=0)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>IntrepidPoisson_Pamgen_Epetra_main.cpp</name>
    <path>/Users/sscoll/dist/trilinos/packages/trilinoscouplings/examples/scaling/</path>
    <filename>IntrepidPoisson__Pamgen__Epetra__main_8cpp</filename>
    <includes id="TrilinosCouplings__IntrepidPoissonExampleHelpers_8hpp" name="TrilinosCouplings_IntrepidPoissonExampleHelpers.hpp" local="yes" imported="no">TrilinosCouplings_IntrepidPoissonExampleHelpers.hpp</includes>
  </compound>
  <compound kind="file">
    <name>IntrepidPoisson_Pamgen_Tpetra_main.cpp</name>
    <path>/Users/sscoll/dist/trilinos/packages/trilinoscouplings/examples/scaling/</path>
    <filename>IntrepidPoisson__Pamgen__Tpetra__main_8cpp</filename>
    <includes id="TrilinosCouplings__IntrepidPoissonExampleHelpers_8hpp" name="TrilinosCouplings_IntrepidPoissonExampleHelpers.hpp" local="yes" imported="no">TrilinosCouplings_IntrepidPoissonExampleHelpers.hpp</includes>
  </compound>
  <compound kind="file">
    <name>ml_nox_preconditioner1.cpp</name>
    <path>/Users/sscoll/dist/trilinos/packages/trilinoscouplings/src/ml/NonlinML/</path>
    <filename>ml__nox__preconditioner1_8cpp</filename>
  </compound>
  <compound kind="file">
    <name>ml_nox_preconditioner2.cpp</name>
    <path>/Users/sscoll/dist/trilinos/packages/trilinoscouplings/src/ml/NonlinML/</path>
    <filename>ml__nox__preconditioner2_8cpp</filename>
  </compound>
  <compound kind="file">
    <name>ml_nox_preconditioner_utils.cpp</name>
    <path>/Users/sscoll/dist/trilinos/packages/trilinoscouplings/src/ml/NonlinML/</path>
    <filename>ml__nox__preconditioner__utils_8cpp</filename>
  </compound>
  <compound kind="file">
    <name>nlnml_preconditioner1.cpp</name>
    <path>/Users/sscoll/dist/trilinos/packages/trilinoscouplings/src/ml/NonlinML/</path>
    <filename>nlnml__preconditioner1_8cpp</filename>
  </compound>
  <compound kind="file">
    <name>nlnml_preconditioner_utils.cpp</name>
    <path>/Users/sscoll/dist/trilinos/packages/trilinoscouplings/src/ml/NonlinML/</path>
    <filename>nlnml__preconditioner__utils_8cpp</filename>
  </compound>
  <compound kind="file">
    <name>TrilinosCouplings_IntrepidPoissonExample_SolveWithBelos.hpp</name>
    <path>/Users/sscoll/dist/trilinos/packages/trilinoscouplings/examples/scaling/</path>
    <filename>TrilinosCouplings__IntrepidPoissonExample__SolveWithBelos_8hpp</filename>
    <member kind="function">
      <type>void</type>
      <name>solveWithBelos</name>
      <anchorfile>TrilinosCouplings__IntrepidPoissonExample__SolveWithBelos_8hpp.html</anchorfile>
      <anchor>adf17fe560e5b95e0dbcacacd61eee705</anchor>
      <arglist>(bool &amp;converged, int &amp;numItersPerformed, const std::string &amp;solverName, const typename Teuchos::ScalarTraits&lt; ST &gt;::magnitudeType &amp;tol, const int maxNumIters, const int num_steps, const Teuchos::RCP&lt; MV &gt; &amp;X, const Teuchos::RCP&lt; const OP &gt; &amp;A, const Teuchos::RCP&lt; const MV &gt; &amp;B, const Teuchos::RCP&lt; const OP &gt; &amp;M_left, const Teuchos::RCP&lt; const OP &gt; &amp;M_right)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>TrilinosCouplings_IntrepidPoissonExampleHelpers.hpp</name>
    <path>/Users/sscoll/dist/trilinos/packages/trilinoscouplings/examples/scaling/</path>
    <filename>TrilinosCouplings__IntrepidPoissonExampleHelpers_8hpp</filename>
    <namespace>IntrepidPoissonExample</namespace>
  </compound>
  <compound kind="class">
    <name>EpetraExt::AmesosAMDGlobal_CrsGraph</name>
    <filename>classEpetraExt_1_1AmesosAMDGlobal__CrsGraph.html</filename>
    <member kind="function">
      <type></type>
      <name>~AmesosAMDGlobal_CrsGraph</name>
      <anchorfile>classEpetraExt_1_1AmesosAMDGlobal__CrsGraph.html</anchorfile>
      <anchor>a667329c9d17ebd3402736ee8b953bff3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>AmesosAMDGlobal_CrsGraph</name>
      <anchorfile>classEpetraExt_1_1AmesosAMDGlobal__CrsGraph.html</anchorfile>
      <anchor>a6611ea0d9e07047de7d89549068f3724</anchor>
      <arglist>(bool verbose=false, bool debug=false)</arglist>
    </member>
    <member kind="function">
      <type>NewTypeRef</type>
      <name>operator()</name>
      <anchorfile>classEpetraExt_1_1AmesosAMDGlobal__CrsGraph.html</anchorfile>
      <anchor>a17e9c98fae04a86021b49a043ec50cbe</anchor>
      <arglist>(OriginalTypeRef orig)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>EpetraExt::AmesosBTF_CrsGraph</name>
    <filename>classEpetraExt_1_1AmesosBTF__CrsGraph.html</filename>
    <member kind="function">
      <type></type>
      <name>~AmesosBTF_CrsGraph</name>
      <anchorfile>classEpetraExt_1_1AmesosBTF__CrsGraph.html</anchorfile>
      <anchor>a62b16b81a80be47a0bd7342e93802e84</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>AmesosBTF_CrsGraph</name>
      <anchorfile>classEpetraExt_1_1AmesosBTF__CrsGraph.html</anchorfile>
      <anchor>a99a0521d54c171432a2cd5148c57faea</anchor>
      <arglist>(bool upperTri=false, bool verbose=false)</arglist>
    </member>
    <member kind="function">
      <type>NewTypeRef</type>
      <name>operator()</name>
      <anchorfile>classEpetraExt_1_1AmesosBTF__CrsGraph.html</anchorfile>
      <anchor>ae462e2e0cd3b8e1f5b398a70982a7ad1</anchor>
      <arglist>(OriginalTypeRef orig)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>EpetraExt::AmesosBTF_CrsMatrix</name>
    <filename>classEpetraExt_1_1AmesosBTF__CrsMatrix.html</filename>
  </compound>
  <compound kind="class">
    <name>EpetraExt::AmesosBTFGlobal_LinearProblem</name>
    <filename>classEpetraExt_1_1AmesosBTFGlobal__LinearProblem.html</filename>
  </compound>
  <compound kind="struct">
    <name>fecomp</name>
    <filename>structfecomp.html</filename>
  </compound>
  <compound kind="class">
    <name>EpetraExt::Isorropia_CrsGraph</name>
    <filename>classEpetraExt_1_1Isorropia__CrsGraph.html</filename>
  </compound>
  <compound kind="class">
    <name>TrilinosCouplings::TpetraIntrepidPoissonExample::MaterialTensor</name>
    <filename>classTrilinosCouplings_1_1TpetraIntrepidPoissonExample_1_1MaterialTensor.html</filename>
    <templarg>Scalar</templarg>
  </compound>
  <compound kind="class">
    <name>ML_Nox_Preconditioner</name>
    <filename>classML__Nox__Preconditioner.html</filename>
  </compound>
  <compound kind="class">
    <name>NLNML_NonlinearLevel</name>
    <filename>classNLNML__NonlinearLevel.html</filename>
  </compound>
  <compound kind="namespace">
    <name>EpetraIntrepidPoissonExample</name>
    <filename>namespaceEpetraIntrepidPoissonExample.html</filename>
  </compound>
  <compound kind="namespace">
    <name>IntrepidPoissonExample</name>
    <filename>namespaceIntrepidPoissonExample.html</filename>
  </compound>
  <compound kind="namespace">
    <name>TpetraIntrepidPoissonExample</name>
    <filename>namespaceTpetraIntrepidPoissonExample.html</filename>
  </compound>
  <compound kind="page">
    <name>index</name>
    <title>Trilinos/packages/trilinoscouplings</title>
    <filename>index</filename>
    <docanchor file="index" title="Outline">trilinoscouplings_outline</docanchor>
    <docanchor file="index" title="Introduction">trilinoscouplings_intro</docanchor>
    <docanchor file="index" title="Overview of TrilinosCouplings">trilinoscouplings_startup</docanchor>
    <docanchor file="index" title="Scaling Examples">trilinoscouplings_scaling_ex</docanchor>
    <docanchor file="index" title="Browse all of trilinoscouplings as a single doxygen collection">trilinoscouplings_browser</docanchor>
  </compound>
</tagfile>
