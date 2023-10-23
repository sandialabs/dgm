<?xml version='1.0' encoding='UTF-8' standalone='yes' ?>
<tagfile>
  <compound kind="file">
    <name>Teko_DiagnosticLinearOp.hpp</name>
    <path>/Users/sscoll/dist/trilinos/packages/teko/src/</path>
    <filename>Teko__DiagnosticLinearOp_8hpp</filename>
    <includes id="Teko__Utilities_8hpp" name="Teko_Utilities.hpp" local="yes" imported="no">Teko_Utilities.hpp</includes>
    <class kind="class">Teko::DiagnosticLinearOp</class>
  </compound>
  <compound kind="file">
    <name>Teko_LU2x2InverseOp.hpp</name>
    <path>/Users/sscoll/dist/trilinos/packages/teko/src/</path>
    <filename>Teko__LU2x2InverseOp_8hpp</filename>
    <includes id="Teko__Utilities_8hpp" name="Teko_Utilities.hpp" local="yes" imported="no">Teko_Utilities.hpp</includes>
    <class kind="class">Teko::LU2x2InverseOp</class>
  </compound>
  <compound kind="file">
    <name>Teko_Utilities.hpp</name>
    <path>/Users/sscoll/dist/trilinos/packages/teko/src/</path>
    <filename>Teko__Utilities_8hpp</filename>
    <member kind="enumeration">
      <type></type>
      <name>DiagonalType</name>
      <anchorfile>Teko__Utilities_8hpp.html</anchorfile>
      <anchor>a4b6c5456ff86db747c9c0b836648b4d2</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>Diagonal</name>
      <anchorfile>Teko__Utilities_8hpp.html</anchorfile>
      <anchor>a4b6c5456ff86db747c9c0b836648b4d2abab4feb993ec9033f351968b7b1a5ae0</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>Lumped</name>
      <anchorfile>Teko__Utilities_8hpp.html</anchorfile>
      <anchor>a4b6c5456ff86db747c9c0b836648b4d2af4ee9b16239367cca6e4ec31a0615d89</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>AbsRowSum</name>
      <anchorfile>Teko__Utilities_8hpp.html</anchorfile>
      <anchor>a4b6c5456ff86db747c9c0b836648b4d2a9c4fb6f601a380fe75256994cba726cd</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>BlkDiag</name>
      <anchorfile>Teko__Utilities_8hpp.html</anchorfile>
      <anchor>a4b6c5456ff86db747c9c0b836648b4d2a517cdcac6b4b63afe2089bd7981dafdd</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>NotDiag</name>
      <anchorfile>Teko__Utilities_8hpp.html</anchorfile>
      <anchor>a4b6c5456ff86db747c9c0b836648b4d2a5afc99f563e06bd442f06603a86d122b</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>computeSpectralRad</name>
      <anchorfile>Teko__Utilities_8hpp.html</anchorfile>
      <anchor>ab64b501a286a5e8870816c4804c5b40a</anchor>
      <arglist>(const Teuchos::RCP&lt; const Thyra::LinearOpBase&lt; double &gt; &gt; &amp;A, double tol, bool isHermitian=false, int numBlocks=5, int restart=0, int verbosity=0)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>computeSmallestMagEig</name>
      <anchorfile>Teko__Utilities_8hpp.html</anchorfile>
      <anchor>a7e23a5c5c6e76920c1b608d642c852dd</anchor>
      <arglist>(const Teuchos::RCP&lt; const Thyra::LinearOpBase&lt; double &gt; &gt; &amp;A, double tol, bool isHermitian=false, int numBlocks=5, int restart=0, int verbosity=0)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>applyOp</name>
      <anchorfile>Teko__Utilities_8hpp.html</anchorfile>
      <anchor>a1516c0134d1cbe835293976b839ab44d</anchor>
      <arglist>(const LinearOp &amp;A, const BlockedMultiVector &amp;x, BlockedMultiVector &amp;y, double alpha=1.0, double beta=0.0)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>applyTransposeOp</name>
      <anchorfile>Teko__Utilities_8hpp.html</anchorfile>
      <anchor>a46bc53106c387498061691ddeb1a8988</anchor>
      <arglist>(const LinearOp &amp;A, const BlockedMultiVector &amp;x, BlockedMultiVector &amp;y, double alpha=1.0, double beta=0.0)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>update</name>
      <anchorfile>Teko__Utilities_8hpp.html</anchorfile>
      <anchor>a016e093cab400546660a55810d74d025</anchor>
      <arglist>(double alpha, const BlockedMultiVector &amp;x, double beta, BlockedMultiVector &amp;y)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>scale</name>
      <anchorfile>Teko__Utilities_8hpp.html</anchorfile>
      <anchor>a000f562785e7b78735c13fc35da81469</anchor>
      <arglist>(const double alpha, MultiVector &amp;x)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>scale</name>
      <anchorfile>Teko__Utilities_8hpp.html</anchorfile>
      <anchor>a6c70cb7c60523de6ca481351159a46d5</anchor>
      <arglist>(const double alpha, BlockedMultiVector &amp;x)</arglist>
    </member>
    <member kind="function">
      <type>LinearOp</type>
      <name>scale</name>
      <anchorfile>Teko__Utilities_8hpp.html</anchorfile>
      <anchor>a2ac61ed239c244c692bfd215fc151d8b</anchor>
      <arglist>(const double alpha, ModifiableLinearOp &amp;a)</arglist>
    </member>
    <member kind="function">
      <type>LinearOp</type>
      <name>adjoint</name>
      <anchorfile>Teko__Utilities_8hpp.html</anchorfile>
      <anchor>acf72b76bc9169ba7aaa3bc403e91f4e4</anchor>
      <arglist>(ModifiableLinearOp &amp;a)</arglist>
    </member>
    <member kind="function">
      <type>MultiVector</type>
      <name>toMultiVector</name>
      <anchorfile>Teko__Utilities_8hpp.html</anchorfile>
      <anchor>a804c34fbe7e04bb37c8ce14299414395</anchor>
      <arglist>(BlockedMultiVector &amp;bmv)</arglist>
    </member>
    <member kind="function">
      <type>const MultiVector</type>
      <name>toMultiVector</name>
      <anchorfile>Teko__Utilities_8hpp.html</anchorfile>
      <anchor>a44fe468a1e30d79b60ff825c565a1ae5</anchor>
      <arglist>(const BlockedMultiVector &amp;bmv)</arglist>
    </member>
    <member kind="function">
      <type>const BlockedMultiVector</type>
      <name>toBlockedMultiVector</name>
      <anchorfile>Teko__Utilities_8hpp.html</anchorfile>
      <anchor>a4f718e602652a86797abe972b1373294</anchor>
      <arglist>(const MultiVector &amp;bmv)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>blockCount</name>
      <anchorfile>Teko__Utilities_8hpp.html</anchorfile>
      <anchor>a8c24d7aca32e561c6659d72fab18bf22</anchor>
      <arglist>(const BlockedMultiVector &amp;bmv)</arglist>
    </member>
    <member kind="function">
      <type>MultiVector</type>
      <name>getBlock</name>
      <anchorfile>Teko__Utilities_8hpp.html</anchorfile>
      <anchor>a9f49b5676e2c01fe275ed5739ede0f4d</anchor>
      <arglist>(int i, const BlockedMultiVector &amp;bmv)</arglist>
    </member>
    <member kind="function">
      <type>MultiVector</type>
      <name>deepcopy</name>
      <anchorfile>Teko__Utilities_8hpp.html</anchorfile>
      <anchor>ac099aa1e458f47c42b98486f89e701bd</anchor>
      <arglist>(const MultiVector &amp;v)</arglist>
    </member>
    <member kind="function">
      <type>MultiVector</type>
      <name>copyAndInit</name>
      <anchorfile>Teko__Utilities_8hpp.html</anchorfile>
      <anchor>aaef0b66da40ac8a1e5948f358699e76a</anchor>
      <arglist>(const MultiVector &amp;v, double scalar)</arglist>
    </member>
    <member kind="function">
      <type>BlockedMultiVector</type>
      <name>deepcopy</name>
      <anchorfile>Teko__Utilities_8hpp.html</anchorfile>
      <anchor>a24d25753ade5b4eb148b954f2d995ba0</anchor>
      <arglist>(const BlockedMultiVector &amp;v)</arglist>
    </member>
    <member kind="function">
      <type>MultiVector</type>
      <name>datacopy</name>
      <anchorfile>Teko__Utilities_8hpp.html</anchorfile>
      <anchor>a3bd0de1e61b9e92053b7cefdcd276451</anchor>
      <arglist>(const MultiVector &amp;src, MultiVector &amp;dst)</arglist>
    </member>
    <member kind="function">
      <type>BlockedMultiVector</type>
      <name>datacopy</name>
      <anchorfile>Teko__Utilities_8hpp.html</anchorfile>
      <anchor>a4b15b80089fcb4418704730b5567b0db</anchor>
      <arglist>(const BlockedMultiVector &amp;src, BlockedMultiVector &amp;dst)</arglist>
    </member>
    <member kind="function">
      <type>LinearOp</type>
      <name>zero</name>
      <anchorfile>Teko__Utilities_8hpp.html</anchorfile>
      <anchor>ab52d336833ffb9d1dc987dceb8d8ba45</anchor>
      <arglist>(const VectorSpace &amp;vs)</arglist>
    </member>
    <member kind="function">
      <type>VectorSpace</type>
      <name>rangeSpace</name>
      <anchorfile>Teko__Utilities_8hpp.html</anchorfile>
      <anchor>aaceefddb7f2464bd57c3ca9b4b361ef8</anchor>
      <arglist>(const LinearOp &amp;lo)</arglist>
    </member>
    <member kind="function">
      <type>VectorSpace</type>
      <name>domainSpace</name>
      <anchorfile>Teko__Utilities_8hpp.html</anchorfile>
      <anchor>af49c3d7c4005602b1f4b06d8ebfe3efc</anchor>
      <arglist>(const LinearOp &amp;lo)</arglist>
    </member>
    <member kind="function">
      <type>BlockedLinearOp</type>
      <name>toBlockedLinearOp</name>
      <anchorfile>Teko__Utilities_8hpp.html</anchorfile>
      <anchor>ae0c3ed26b561d1918173f8fe0cb0ff66</anchor>
      <arglist>(LinearOp &amp;clo)</arglist>
    </member>
    <member kind="function">
      <type>const BlockedLinearOp</type>
      <name>toBlockedLinearOp</name>
      <anchorfile>Teko__Utilities_8hpp.html</anchorfile>
      <anchor>a96774860e12bf0cb214df5ea9b8d2b06</anchor>
      <arglist>(const LinearOp &amp;clo)</arglist>
    </member>
    <member kind="function">
      <type>LinearOp</type>
      <name>toLinearOp</name>
      <anchorfile>Teko__Utilities_8hpp.html</anchorfile>
      <anchor>a51a7c1e7564a13b7d043624c69c200d7</anchor>
      <arglist>(BlockedLinearOp &amp;blo)</arglist>
    </member>
    <member kind="function">
      <type>const LinearOp</type>
      <name>toLinearOp</name>
      <anchorfile>Teko__Utilities_8hpp.html</anchorfile>
      <anchor>a4f6b0a2b48c5f161f8d5d9b989fd41c1</anchor>
      <arglist>(const BlockedLinearOp &amp;blo)</arglist>
    </member>
    <member kind="function">
      <type>LinearOp</type>
      <name>toLinearOp</name>
      <anchorfile>Teko__Utilities_8hpp.html</anchorfile>
      <anchor>a788ec7473d30ffd6f687e6ca6d1de663</anchor>
      <arglist>(ModifiableLinearOp &amp;blo)</arglist>
    </member>
    <member kind="function">
      <type>const LinearOp</type>
      <name>toLinearOp</name>
      <anchorfile>Teko__Utilities_8hpp.html</anchorfile>
      <anchor>a2ce6268ff5c01f0b9863d42212d23211</anchor>
      <arglist>(const ModifiableLinearOp &amp;blo)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>blockRowCount</name>
      <anchorfile>Teko__Utilities_8hpp.html</anchorfile>
      <anchor>a7c2e17a856db30644ba802956adbd31e</anchor>
      <arglist>(const BlockedLinearOp &amp;blo)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>blockColCount</name>
      <anchorfile>Teko__Utilities_8hpp.html</anchorfile>
      <anchor>ac61bfa5cd2536919d0840b98ee77b428</anchor>
      <arglist>(const BlockedLinearOp &amp;blo)</arglist>
    </member>
    <member kind="function">
      <type>LinearOp</type>
      <name>getBlock</name>
      <anchorfile>Teko__Utilities_8hpp.html</anchorfile>
      <anchor>a4e68ba55b6ceddffc01c3fa14e2b6c6d</anchor>
      <arglist>(int i, int j, const BlockedLinearOp &amp;blo)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setBlock</name>
      <anchorfile>Teko__Utilities_8hpp.html</anchorfile>
      <anchor>aa3b6dda38f161bf87f0912b1db71f308</anchor>
      <arglist>(int i, int j, BlockedLinearOp &amp;blo, const LinearOp &amp;lo)</arglist>
    </member>
    <member kind="function">
      <type>BlockedLinearOp</type>
      <name>createBlockedOp</name>
      <anchorfile>Teko__Utilities_8hpp.html</anchorfile>
      <anchor>acc90e100292df978a58e220e06ad9ac2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>beginBlockFill</name>
      <anchorfile>Teko__Utilities_8hpp.html</anchorfile>
      <anchor>a4956b6edc887041df9545198d9727585</anchor>
      <arglist>(BlockedLinearOp &amp;blo, int rowCnt, int colCnt)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>beginBlockFill</name>
      <anchorfile>Teko__Utilities_8hpp.html</anchorfile>
      <anchor>a7d5092f08c049c1902eb40f9cfe9681b</anchor>
      <arglist>(BlockedLinearOp &amp;blo)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>endBlockFill</name>
      <anchorfile>Teko__Utilities_8hpp.html</anchorfile>
      <anchor>ae17b365cbf9d05b4e38e9c056c77a6f0</anchor>
      <arglist>(BlockedLinearOp &amp;blo)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>applyOp</name>
      <anchorfile>Teko__Utilities_8hpp.html</anchorfile>
      <anchor>a1516c0134d1cbe835293976b839ab44d</anchor>
      <arglist>(const LinearOp &amp;A, const BlockedMultiVector &amp;x, BlockedMultiVector &amp;y, double alpha=1.0, double beta=0.0)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>applyTransposeOp</name>
      <anchorfile>Teko__Utilities_8hpp.html</anchorfile>
      <anchor>a46bc53106c387498061691ddeb1a8988</anchor>
      <arglist>(const LinearOp &amp;A, const BlockedMultiVector &amp;x, BlockedMultiVector &amp;y, double alpha=1.0, double beta=0.0)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>update</name>
      <anchorfile>Teko__Utilities_8hpp.html</anchorfile>
      <anchor>a016e093cab400546660a55810d74d025</anchor>
      <arglist>(double alpha, const BlockedMultiVector &amp;x, double beta, BlockedMultiVector &amp;y)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>scale</name>
      <anchorfile>Teko__Utilities_8hpp.html</anchorfile>
      <anchor>a000f562785e7b78735c13fc35da81469</anchor>
      <arglist>(const double alpha, MultiVector &amp;x)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>scale</name>
      <anchorfile>Teko__Utilities_8hpp.html</anchorfile>
      <anchor>a6c70cb7c60523de6ca481351159a46d5</anchor>
      <arglist>(const double alpha, BlockedMultiVector &amp;x)</arglist>
    </member>
    <member kind="function">
      <type>LinearOp</type>
      <name>scale</name>
      <anchorfile>Teko__Utilities_8hpp.html</anchorfile>
      <anchor>a2ac61ed239c244c692bfd215fc151d8b</anchor>
      <arglist>(const double alpha, ModifiableLinearOp &amp;a)</arglist>
    </member>
    <member kind="function">
      <type>LinearOp</type>
      <name>adjoint</name>
      <anchorfile>Teko__Utilities_8hpp.html</anchorfile>
      <anchor>acf72b76bc9169ba7aaa3bc403e91f4e4</anchor>
      <arglist>(ModifiableLinearOp &amp;a)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Teko::AddPreconditionerFactory</name>
    <filename>classTeko_1_1AddPreconditionerFactory.html</filename>
    <base>Teko::BlockPreconditionerFactory</base>
    <member kind="function">
      <type></type>
      <name>AddPreconditionerFactory</name>
      <anchorfile>classTeko_1_1AddPreconditionerFactory.html</anchorfile>
      <anchor>aa19bd3c5a38d9664a4f9472a6a4c7a00</anchor>
      <arglist>(const Teuchos::RCP&lt; const Teko::BlockPreconditionerFactory &gt; &amp;FirstFactory, const Teuchos::RCP&lt; const Teko::BlockPreconditionerFactory &gt; &amp;SecondFactory)</arglist>
    </member>
    <member kind="function">
      <type>Teko::LinearOp</type>
      <name>buildPreconditionerOperator</name>
      <anchorfile>classTeko_1_1AddPreconditionerFactory.html</anchorfile>
      <anchor>a1dffa51831c3bfa991605c5b33ce1398</anchor>
      <arglist>(Teko::BlockedLinearOp &amp;blo, Teko::BlockPreconditionerState &amp;state) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual Teuchos::RCP&lt; Teko::PreconditionerState &gt;</type>
      <name>buildPreconditionerState</name>
      <anchorfile>classTeko_1_1AddPreconditionerFactory.html</anchorfile>
      <anchor>a842bdb826a1c886ba6c699af6cb4a795</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual void</type>
      <name>initializeFromParameterList</name>
      <anchorfile>classTeko_1_1AddPreconditionerFactory.html</anchorfile>
      <anchor>ae3cfdc62cafb54fa75ca6f9940d81883</anchor>
      <arglist>(const Teuchos::ParameterList &amp;pl)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Teko::AddPrecondState</name>
    <filename>classTeko_1_1AddPrecondState.html</filename>
    <base>Teko::BlockPreconditionerState</base>
  </compound>
  <compound kind="class">
    <name>Teko::NS::ALOperator</name>
    <filename>classTeko_1_1NS_1_1ALOperator.html</filename>
    <base>Teko::Epetra::BlockedEpetraOperator</base>
    <member kind="function">
      <type></type>
      <name>ALOperator</name>
      <anchorfile>classTeko_1_1NS_1_1ALOperator.html</anchorfile>
      <anchor>af2b540f7272833a9302f22afb1d9e748</anchor>
      <arglist>(const std::vector&lt; std::vector&lt; int &gt; &gt; &amp;vars, const Teuchos::RCP&lt; Epetra_Operator &gt; &amp;content, LinearOp pressureMassMatrix, double gamma=0.05, const std::string &amp;label=&quot;&lt;ANYM&gt;&quot;)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ALOperator</name>
      <anchorfile>classTeko_1_1NS_1_1ALOperator.html</anchorfile>
      <anchor>a2db3ddb615329e40bfcee3d46b659f24</anchor>
      <arglist>(const std::vector&lt; std::vector&lt; int &gt; &gt; &amp;vars, const Teuchos::RCP&lt; Epetra_Operator &gt; &amp;content, double gamma=0.05, const std::string &amp;label=&quot;&lt;ANYM&gt;&quot;)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setPressureMassMatrix</name>
      <anchorfile>classTeko_1_1NS_1_1ALOperator.html</anchorfile>
      <anchor>a12f49896f9b76c2add045c4c25fb8fa5</anchor>
      <arglist>(LinearOp pressureMassMatrix)</arglist>
    </member>
    <member kind="function">
      <type>const LinearOp &amp;</type>
      <name>getPressureMassMatrix</name>
      <anchorfile>classTeko_1_1NS_1_1ALOperator.html</anchorfile>
      <anchor>a6d38381914be851f2584c49de58fedb5</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setGamma</name>
      <anchorfile>classTeko_1_1NS_1_1ALOperator.html</anchorfile>
      <anchor>acbf6ad0b881fc24da7df1470fecfdad5</anchor>
      <arglist>(double gamma)</arglist>
    </member>
    <member kind="function">
      <type>const double &amp;</type>
      <name>getGamma</name>
      <anchorfile>classTeko_1_1NS_1_1ALOperator.html</anchorfile>
      <anchor>ad6dda0a8b749add103debc39b87b6b29</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>augmentRHS</name>
      <anchorfile>classTeko_1_1NS_1_1ALOperator.html</anchorfile>
      <anchor>ae5a60df584e13b11fe89baca87b5bd57</anchor>
      <arglist>(const Epetra_MultiVector &amp;b, Epetra_MultiVector &amp;bAugmented)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getNumberOfBlockRows</name>
      <anchorfile>classTeko_1_1NS_1_1ALOperator.html</anchorfile>
      <anchor>af9061725596c5db54e7dddc9dfeb30fe</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>RebuildOps</name>
      <anchorfile>classTeko_1_1NS_1_1ALOperator.html</anchorfile>
      <anchor>a88f372d4391b26b5442aa2fed5430c33</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const Teuchos::RCP&lt; const Epetra_Operator &gt;</type>
      <name>GetBlock</name>
      <anchorfile>classTeko_1_1NS_1_1ALOperator.html</anchorfile>
      <anchor>a0df9101cb3740294a743ce6e94d5f61d</anchor>
      <arglist>(int i, int j) const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>checkDim</name>
      <anchorfile>classTeko_1_1NS_1_1ALOperator.html</anchorfile>
      <anchor>addc95f6b9b7a218afe974da573962e24</anchor>
      <arglist>(const std::vector&lt; std::vector&lt; int &gt; &gt; &amp;vars)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>BuildALOperator</name>
      <anchorfile>classTeko_1_1NS_1_1ALOperator.html</anchorfile>
      <anchor>a7d4620203e98800d8768ebeea18f8fdf</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>Teuchos::RCP&lt; Thyra::LinearOpBase&lt; double &gt; &gt;</type>
      <name>alOperator_</name>
      <anchorfile>classTeko_1_1NS_1_1ALOperator.html</anchorfile>
      <anchor>a8790607631eab6bf1e9879686592bcc5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>Teuchos::RCP&lt; Thyra::LinearOpBase&lt; double &gt; &gt;</type>
      <name>alOperatorRhs_</name>
      <anchorfile>classTeko_1_1NS_1_1ALOperator.html</anchorfile>
      <anchor>a33169194b470f433b57141eee6021cc7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>LinearOp</type>
      <name>pressureMassMatrix_</name>
      <anchorfile>classTeko_1_1NS_1_1ALOperator.html</anchorfile>
      <anchor>a5add7d9490a2060022c54b0902f7e4fd</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>LinearOp</type>
      <name>invPressureMassMatrix_</name>
      <anchorfile>classTeko_1_1NS_1_1ALOperator.html</anchorfile>
      <anchor>a5e9f2dc383288bf9764854a8c0fe3fe3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>double</type>
      <name>gamma_</name>
      <anchorfile>classTeko_1_1NS_1_1ALOperator.html</anchorfile>
      <anchor>afb47511130815b7df5f79fb32843b408</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>dim_</name>
      <anchorfile>classTeko_1_1NS_1_1ALOperator.html</anchorfile>
      <anchor>aa28f89563d6ff2973fa8245d8da454fb</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>numBlockRows_</name>
      <anchorfile>classTeko_1_1NS_1_1ALOperator.html</anchorfile>
      <anchor>abefa80eec002bccfb05d45d5825becb3</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Teko::AutoClone</name>
    <filename>classTeko_1_1AutoClone.html</filename>
    <templarg></templarg>
    <templarg></templarg>
    <base>Teko::Cloneable</base>
    <member kind="function">
      <type></type>
      <name>AutoClone</name>
      <anchorfile>classTeko_1_1AutoClone.html</anchorfile>
      <anchor>a5064935333fd6f23b786236baf58ae1a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual Teuchos::RCP&lt; Cloneable &gt;</type>
      <name>clone</name>
      <anchorfile>classTeko_1_1AutoClone.html</anchorfile>
      <anchor>ad89ec5a4f6bb1e78a38e4dedad757fb3</anchor>
      <arglist>() const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Teko::AutoCloneDummy</name>
    <filename>classTeko_1_1AutoCloneDummy.html</filename>
  </compound>
  <compound kind="class">
    <name>Teko::Epetra::BlockedEpetraOperator</name>
    <filename>classTeko_1_1Epetra_1_1BlockedEpetraOperator.html</filename>
    <base>Teko::Epetra::EpetraOperatorWrapper</base>
    <member kind="function">
      <type></type>
      <name>BlockedEpetraOperator</name>
      <anchorfile>classTeko_1_1Epetra_1_1BlockedEpetraOperator.html</anchorfile>
      <anchor>a936eca4037439e12a552c231df1ba7c6</anchor>
      <arglist>(const std::vector&lt; std::vector&lt; int &gt; &gt; &amp;vars, const Teuchos::RCP&lt; const Epetra_Operator &gt; &amp;content, const std::string &amp;label=&quot;&lt;ANYM&gt;&quot;)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>SetContent</name>
      <anchorfile>classTeko_1_1Epetra_1_1BlockedEpetraOperator.html</anchorfile>
      <anchor>a60000173ddc83ac627c67c098bceaf47</anchor>
      <arglist>(const std::vector&lt; std::vector&lt; int &gt; &gt; &amp;vars, const Teuchos::RCP&lt; const Epetra_Operator &gt; &amp;content)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>RebuildOps</name>
      <anchorfile>classTeko_1_1Epetra_1_1BlockedEpetraOperator.html</anchorfile>
      <anchor>a576aef6b5e5fde4ee5f919e7b23f8871</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Reorder</name>
      <anchorfile>classTeko_1_1Epetra_1_1BlockedEpetraOperator.html</anchorfile>
      <anchor>a86896e28bfc129644c4216fd1d14c101</anchor>
      <arglist>(const BlockReorderManager &amp;brm)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>RemoveReording</name>
      <anchorfile>classTeko_1_1Epetra_1_1BlockedEpetraOperator.html</anchorfile>
      <anchor>ac6fb870f61488430395dd5c33c513a08</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>WriteBlocks</name>
      <anchorfile>classTeko_1_1Epetra_1_1BlockedEpetraOperator.html</anchorfile>
      <anchor>ad3d62881ee85b2ea74e8936581672d1f</anchor>
      <arglist>(const std::string &amp;prefix) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>testAgainstFullOperator</name>
      <anchorfile>classTeko_1_1Epetra_1_1BlockedEpetraOperator.html</anchorfile>
      <anchor>a5f288b18c829602d606c0c96ca076e02</anchor>
      <arglist>(int count, double tol) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Teko::TpetraHelpers::BlockedTpetraOperator</name>
    <filename>classTeko_1_1TpetraHelpers_1_1BlockedTpetraOperator.html</filename>
    <base>Teko::TpetraHelpers::TpetraOperatorWrapper</base>
    <member kind="function">
      <type></type>
      <name>BlockedTpetraOperator</name>
      <anchorfile>classTeko_1_1TpetraHelpers_1_1BlockedTpetraOperator.html</anchorfile>
      <anchor>a87eb069ae0e572ef5af32301a68da390</anchor>
      <arglist>(const std::vector&lt; std::vector&lt; GO &gt; &gt; &amp;vars, const Teuchos::RCP&lt; const Tpetra::Operator&lt; ST, LO, GO, NT &gt; &gt; &amp;content, const std::string &amp;label=&quot;&lt;ANYM&gt;&quot;)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>SetContent</name>
      <anchorfile>classTeko_1_1TpetraHelpers_1_1BlockedTpetraOperator.html</anchorfile>
      <anchor>a35f8127f3b907b6f0f5b931284c766b5</anchor>
      <arglist>(const std::vector&lt; std::vector&lt; GO &gt; &gt; &amp;vars, const Teuchos::RCP&lt; const Tpetra::Operator&lt; ST, LO, GO, NT &gt; &gt; &amp;content)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>RebuildOps</name>
      <anchorfile>classTeko_1_1TpetraHelpers_1_1BlockedTpetraOperator.html</anchorfile>
      <anchor>a455f47fec2717e7c61908f644ff622e6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Reorder</name>
      <anchorfile>classTeko_1_1TpetraHelpers_1_1BlockedTpetraOperator.html</anchorfile>
      <anchor>a7a88e461d12f85df0fda7d8db742dae0</anchor>
      <arglist>(const BlockReorderManager &amp;brm)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>RemoveReording</name>
      <anchorfile>classTeko_1_1TpetraHelpers_1_1BlockedTpetraOperator.html</anchorfile>
      <anchor>aecfe3d64c1b0f07a2f4a556a7a45a728</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>WriteBlocks</name>
      <anchorfile>classTeko_1_1TpetraHelpers_1_1BlockedTpetraOperator.html</anchorfile>
      <anchor>acf7aadea1322cb8a94da5b33440d7835</anchor>
      <arglist>(const std::string &amp;prefix) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>testAgainstFullOperator</name>
      <anchorfile>classTeko_1_1TpetraHelpers_1_1BlockedTpetraOperator.html</anchorfile>
      <anchor>a9b50a6c0fc9c101de31520bab9854789</anchor>
      <arglist>(int count, ST tol) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Teko::BlockImplicitLinearOp</name>
    <filename>classTeko_1_1BlockImplicitLinearOp.html</filename>
    <member kind="function" virtualness="pure">
      <type>virtual VectorSpace</type>
      <name>range</name>
      <anchorfile>classTeko_1_1BlockImplicitLinearOp.html</anchorfile>
      <anchor>a3a29e1be58c77472c9fb8916bf99011f</anchor>
      <arglist>() const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual VectorSpace</type>
      <name>domain</name>
      <anchorfile>classTeko_1_1BlockImplicitLinearOp.html</anchorfile>
      <anchor>a958904a001b00d637c4ada8d831e0c0a</anchor>
      <arglist>() const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>implicitApply</name>
      <anchorfile>classTeko_1_1BlockImplicitLinearOp.html</anchorfile>
      <anchor>a7c1b18f117f05659572920cba1c9d4f2</anchor>
      <arglist>(const BlockedMultiVector &amp;x, BlockedMultiVector &amp;y, const double alpha=1.0, const double beta=0.0) const  =0</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>implicitApply</name>
      <anchorfile>classTeko_1_1BlockImplicitLinearOp.html</anchorfile>
      <anchor>a911e3527eb5b5215f3c0f8921c1e9aaa</anchor>
      <arglist>(const Thyra::EOpTransp M_trans, const BlockedMultiVector &amp;x, BlockedMultiVector &amp;y, const double alpha=1.0, const double beta=0.0) const </arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual bool</type>
      <name>opSupportedImpl</name>
      <anchorfile>classTeko_1_1BlockImplicitLinearOp.html</anchorfile>
      <anchor>a38efc06b885cd2fb8c95bb548768063c</anchor>
      <arglist>(const Thyra::EOpTransp M_trans) const </arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual bool</type>
      <name>opSupportedImpl</name>
      <anchorfile>classTeko_1_1BlockImplicitLinearOp.html</anchorfile>
      <anchor>a38efc06b885cd2fb8c95bb548768063c</anchor>
      <arglist>(const Thyra::EOpTransp M_trans) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Teko::BlockInvDiagonalStrategy</name>
    <filename>classTeko_1_1BlockInvDiagonalStrategy.html</filename>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>getInvD</name>
      <anchorfile>classTeko_1_1BlockInvDiagonalStrategy.html</anchorfile>
      <anchor>ab03abbe4a696cb5d324a5dfedf42d95a</anchor>
      <arglist>(const BlockedLinearOp &amp;A, BlockPreconditionerState &amp;state, std::vector&lt; LinearOp &gt; &amp;invDiag) const  =0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Teko::BlockLowerTriInverseOp</name>
    <filename>classTeko_1_1BlockLowerTriInverseOp.html</filename>
    <base>Teko::BlockImplicitLinearOp</base>
    <member kind="function">
      <type></type>
      <name>BlockLowerTriInverseOp</name>
      <anchorfile>classTeko_1_1BlockLowerTriInverseOp.html</anchorfile>
      <anchor>a76700b19cefcdd01cdd5afb63d5b45c8</anchor>
      <arglist>(BlockedLinearOp &amp;L, const std::vector&lt; LinearOp &gt; &amp;invDiag)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual VectorSpace</type>
      <name>range</name>
      <anchorfile>classTeko_1_1BlockLowerTriInverseOp.html</anchorfile>
      <anchor>a39706cd2e83f096f6ad82380dfda0476</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual VectorSpace</type>
      <name>domain</name>
      <anchorfile>classTeko_1_1BlockLowerTriInverseOp.html</anchorfile>
      <anchor>a3dae1ec0fb9c3789d3f0bfd1b22c5dfb</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>implicitApply</name>
      <anchorfile>classTeko_1_1BlockLowerTriInverseOp.html</anchorfile>
      <anchor>a1e05d843b6383797be3bc49cf1841d3f</anchor>
      <arglist>(const BlockedMultiVector &amp;x, BlockedMultiVector &amp;y, const double alpha=1.0, const double beta=0.0) const </arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>const BlockedLinearOp</type>
      <name>L_</name>
      <anchorfile>classTeko_1_1BlockLowerTriInverseOp.html</anchorfile>
      <anchor>a562f4bab3c79c28bace6e9f3d9619fd7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>std::vector&lt; LinearOp &gt;</type>
      <name>invDiag_</name>
      <anchorfile>classTeko_1_1BlockLowerTriInverseOp.html</anchorfile>
      <anchor>a76b449b7c8def353475a597dc5196249</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>Teuchos::RCP&lt; const Thyra::ProductVectorSpaceBase&lt; double &gt; &gt;</type>
      <name>productRange_</name>
      <anchorfile>classTeko_1_1BlockLowerTriInverseOp.html</anchorfile>
      <anchor>a5380c7e7064956541fb10478049d0b70</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>Teuchos::RCP&lt; const Thyra::ProductVectorSpaceBase&lt; double &gt; &gt;</type>
      <name>productDomain_</name>
      <anchorfile>classTeko_1_1BlockLowerTriInverseOp.html</anchorfile>
      <anchor>a96422f6ffd783714b4ce493e0d679251</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual VectorSpace</type>
      <name>range</name>
      <anchorfile>classTeko_1_1BlockLowerTriInverseOp.html</anchorfile>
      <anchor>a39706cd2e83f096f6ad82380dfda0476</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual VectorSpace</type>
      <name>domain</name>
      <anchorfile>classTeko_1_1BlockLowerTriInverseOp.html</anchorfile>
      <anchor>a3dae1ec0fb9c3789d3f0bfd1b22c5dfb</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>implicitApply</name>
      <anchorfile>classTeko_1_1BlockLowerTriInverseOp.html</anchorfile>
      <anchor>a1e05d843b6383797be3bc49cf1841d3f</anchor>
      <arglist>(const BlockedMultiVector &amp;x, BlockedMultiVector &amp;y, const double alpha=1.0, const double beta=0.0) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Teko::BlockPreconditionerFactory</name>
    <filename>classTeko_1_1BlockPreconditionerFactory.html</filename>
    <base>Teko::PreconditionerFactory</base>
    <member kind="function" virtualness="pure">
      <type>virtual LinearOp</type>
      <name>buildPreconditionerOperator</name>
      <anchorfile>classTeko_1_1BlockPreconditionerFactory.html</anchorfile>
      <anchor>a4c0d6ab6d23de0d08bd35ad8ddcd3cfa</anchor>
      <arglist>(BlockedLinearOp &amp;blo, BlockPreconditionerState &amp;state) const  =0</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual RCP&lt; PreconditionerState &gt;</type>
      <name>buildPreconditionerState</name>
      <anchorfile>classTeko_1_1BlockPreconditionerFactory.html</anchorfile>
      <anchor>ae7be96fa199f1bccabfec38cd816d9aa</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; BlockPreconditionerState &gt;</type>
      <name>buildBlockPreconditionerState</name>
      <anchorfile>classTeko_1_1BlockPreconditionerFactory.html</anchorfile>
      <anchor>a822cece0776e838f6c683fdf45b73d26</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual LinearOp</type>
      <name>buildPreconditionerOperator</name>
      <anchorfile>classTeko_1_1BlockPreconditionerFactory.html</anchorfile>
      <anchor>a10b8fd7c2ffc9d4b38f27a952292bc4b</anchor>
      <arglist>(LinearOp &amp;blo, PreconditionerState &amp;state) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isCompatible</name>
      <anchorfile>classTeko_1_1BlockPreconditionerFactory.html</anchorfile>
      <anchor>a179baa989b4ddc0c4791326b4b247e4e</anchor>
      <arglist>(const Thyra::LinearOpSourceBase&lt; double &gt; &amp;fwdOpSrc) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Teko::BlockPreconditionerState</name>
    <filename>classTeko_1_1BlockPreconditionerState.html</filename>
    <base>Teko::PreconditionerState</base>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>setBlockSourceVector</name>
      <anchorfile>classTeko_1_1BlockPreconditionerState.html</anchorfile>
      <anchor>aa88ea02e9c0d04fa9515c1e4160cbc98</anchor>
      <arglist>(const Teko::BlockedMultiVector &amp;srcVec)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const Teko::BlockedMultiVector</type>
      <name>getBlockedSourceVector</name>
      <anchorfile>classTeko_1_1BlockPreconditionerState.html</anchorfile>
      <anchor>a279bc50215d1c0b0c7bf3dd1afc3f2df</anchor>
      <arglist>() const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Teko::BlockReorderLeaf</name>
    <filename>classTeko_1_1BlockReorderLeaf.html</filename>
    <base>Teko::BlockReorderManager</base>
    <member kind="function" virtualness="virtual">
      <type>virtual Teuchos::RCP&lt; BlockReorderManager &gt;</type>
      <name>Copy</name>
      <anchorfile>classTeko_1_1BlockReorderLeaf.html</anchorfile>
      <anchor>a9287cb81c4d8e4d81af0917c6db63c9b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>GetNumBlocks</name>
      <anchorfile>classTeko_1_1BlockReorderLeaf.html</anchorfile>
      <anchor>a53549eeebf8c9594682f480d9b15508d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>SetNumBlocks</name>
      <anchorfile>classTeko_1_1BlockReorderLeaf.html</anchorfile>
      <anchor>a136f71c95d2584d01c51a1db5c593a7f</anchor>
      <arglist>(int sz)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>SetBlock</name>
      <anchorfile>classTeko_1_1BlockReorderLeaf.html</anchorfile>
      <anchor>a560d3f4827b06c704e563412cb705a3f</anchor>
      <arglist>(int blockIndex, int reorder)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const Teuchos::RCP&lt; BlockReorderManager &gt;</type>
      <name>GetBlock</name>
      <anchorfile>classTeko_1_1BlockReorderLeaf.html</anchorfile>
      <anchor>afa4713d1c3f0749c8993237c5e7e00c4</anchor>
      <arglist>(int blockIndex)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const Teuchos::RCP&lt; const BlockReorderManager &gt;</type>
      <name>GetBlock</name>
      <anchorfile>classTeko_1_1BlockReorderLeaf.html</anchorfile>
      <anchor>a19431c497492b9f03f0c946aad41a37b</anchor>
      <arglist>(int blockIndex) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetIndex</name>
      <anchorfile>classTeko_1_1BlockReorderLeaf.html</anchorfile>
      <anchor>ac4bed348b1e30889459590019cdf5ebe</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual std::string</type>
      <name>toString</name>
      <anchorfile>classTeko_1_1BlockReorderLeaf.html</anchorfile>
      <anchor>ac4da9132a7f14701f58d479afb55c21c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>LargestIndex</name>
      <anchorfile>classTeko_1_1BlockReorderLeaf.html</anchorfile>
      <anchor>a18ecc8f4c90f13084c422434a5bc02a7</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BlockReorderLeaf</name>
      <anchorfile>classTeko_1_1BlockReorderLeaf.html</anchorfile>
      <anchor>aefbfe3fd80d5903fe728bf7987107985</anchor>
      <arglist>(int ind)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BlockReorderLeaf</name>
      <anchorfile>classTeko_1_1BlockReorderLeaf.html</anchorfile>
      <anchor>a99c94552e6f6e2cd53b04b3619ccab8c</anchor>
      <arglist>(const BlockReorderLeaf &amp;brl)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>value_</name>
      <anchorfile>classTeko_1_1BlockReorderLeaf.html</anchorfile>
      <anchor>ae4966cc6d89c60a6fb9537993ec38b38</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BlockReorderLeaf</name>
      <anchorfile>classTeko_1_1BlockReorderLeaf.html</anchorfile>
      <anchor>aefbfe3fd80d5903fe728bf7987107985</anchor>
      <arglist>(int ind)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BlockReorderLeaf</name>
      <anchorfile>classTeko_1_1BlockReorderLeaf.html</anchorfile>
      <anchor>a99c94552e6f6e2cd53b04b3619ccab8c</anchor>
      <arglist>(const BlockReorderLeaf &amp;brl)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Teko::BlockReorderManager</name>
    <filename>classTeko_1_1BlockReorderManager.html</filename>
    <member kind="function" virtualness="virtual">
      <type>virtual Teuchos::RCP&lt; BlockReorderManager &gt;</type>
      <name>Copy</name>
      <anchorfile>classTeko_1_1BlockReorderManager.html</anchorfile>
      <anchor>a05d2cf49d1c96215a27f64c314dbebca</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>SetNumBlocks</name>
      <anchorfile>classTeko_1_1BlockReorderManager.html</anchorfile>
      <anchor>a3f7dc2e2e2190db1eb5526b5a8822628</anchor>
      <arglist>(int sz)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>GetNumBlocks</name>
      <anchorfile>classTeko_1_1BlockReorderManager.html</anchorfile>
      <anchor>a207f1592861c8e0deafef33cf6ace709</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>SetBlock</name>
      <anchorfile>classTeko_1_1BlockReorderManager.html</anchorfile>
      <anchor>a4ade7d4dbc24dffb1ffb33660d90b9d9</anchor>
      <arglist>(int blockIndex, int reorder)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>SetBlock</name>
      <anchorfile>classTeko_1_1BlockReorderManager.html</anchorfile>
      <anchor>a3b08b5e221a678dd3de2e139342dfbf4</anchor>
      <arglist>(int blockIndex, const Teuchos::RCP&lt; BlockReorderManager &gt; &amp;reorder)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const Teuchos::RCP&lt; BlockReorderManager &gt;</type>
      <name>GetBlock</name>
      <anchorfile>classTeko_1_1BlockReorderManager.html</anchorfile>
      <anchor>a8ce2563e37f7507d39dc1251a8711691</anchor>
      <arglist>(int blockIndex)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const Teuchos::RCP&lt; const BlockReorderManager &gt;</type>
      <name>GetBlock</name>
      <anchorfile>classTeko_1_1BlockReorderManager.html</anchorfile>
      <anchor>abb12bb6843ce372c389f29e9c3a535ea</anchor>
      <arglist>(int blockIndex) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual std::string</type>
      <name>toString</name>
      <anchorfile>classTeko_1_1BlockReorderManager.html</anchorfile>
      <anchor>a5b8795d9ccfbf246ddea0a9a16906d75</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>LargestIndex</name>
      <anchorfile>classTeko_1_1BlockReorderManager.html</anchorfile>
      <anchor>acf0439bfb0d6ed4ade02b7f3a882f238</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BlockReorderManager</name>
      <anchorfile>classTeko_1_1BlockReorderManager.html</anchorfile>
      <anchor>ad054fbdf8c316306f54af129d8def24b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BlockReorderManager</name>
      <anchorfile>classTeko_1_1BlockReorderManager.html</anchorfile>
      <anchor>a5428f7443ac8236f86c1d3c8f1090f38</anchor>
      <arglist>(int sz)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BlockReorderManager</name>
      <anchorfile>classTeko_1_1BlockReorderManager.html</anchorfile>
      <anchor>abaeae0e06f3afc98654f92eba8283eb9</anchor>
      <arglist>(const BlockReorderManager &amp;bmm)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~BlockReorderManager</name>
      <anchorfile>classTeko_1_1BlockReorderManager.html</anchorfile>
      <anchor>a171168d9a1090842c6b5d289fd6c8c26</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>std::vector&lt; Teuchos::RCP&lt; BlockReorderManager &gt; &gt;</type>
      <name>children_</name>
      <anchorfile>classTeko_1_1BlockReorderManager.html</anchorfile>
      <anchor>ad797121df690560eeb8365209da73097</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Thyra::VectorSpaceBase&lt; double &gt; &gt;</type>
      <name>buildReorderedVectorSpace</name>
      <anchorfile>classTeko_1_1BlockReorderManager.html</anchorfile>
      <anchor>ad8f8bf4e2fba0271b19a355a5338b02c</anchor>
      <arglist>(const BlockReorderManager &amp;mgr, const Teuchos::RCP&lt; const Thyra::ProductVectorSpaceBase&lt; double &gt; &gt; &amp;blkSpc)</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Thyra::LinearOpBase&lt; double &gt; &gt;</type>
      <name>buildReorderedLinearOp</name>
      <anchorfile>classTeko_1_1BlockReorderManager.html</anchorfile>
      <anchor>a90e0f6ca42369567d4409ba7afa81aed</anchor>
      <arglist>(const BlockReorderManager &amp;bmm, const Teuchos::RCP&lt; const Thyra::BlockedLinearOpBase&lt; double &gt; &gt; &amp;blkOp)</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Thyra::LinearOpBase&lt; double &gt; &gt;</type>
      <name>buildReorderedLinearOp</name>
      <anchorfile>classTeko_1_1BlockReorderManager.html</anchorfile>
      <anchor>a1f7638b91a0a79f2958d8ddf4c7078af</anchor>
      <arglist>(const BlockReorderManager &amp;rowMgr, const BlockReorderManager &amp;colMgr, const Teuchos::RCP&lt; const Thyra::BlockedLinearOpBase&lt; double &gt; &gt; &amp;blkOp)</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Thyra::VectorSpaceBase&lt; double &gt; &gt;</type>
      <name>buildReorderedVectorSpace</name>
      <anchorfile>classTeko_1_1BlockReorderManager.html</anchorfile>
      <anchor>ad8f8bf4e2fba0271b19a355a5338b02c</anchor>
      <arglist>(const BlockReorderManager &amp;mgr, const Teuchos::RCP&lt; const Thyra::ProductVectorSpaceBase&lt; double &gt; &gt; &amp;blkSpc)</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; Thyra::MultiVectorBase&lt; double &gt; &gt;</type>
      <name>buildReorderedMultiVector</name>
      <anchorfile>classTeko_1_1BlockReorderManager.html</anchorfile>
      <anchor>a27bba56c7d57f7a2374c8613b8f46f16</anchor>
      <arglist>(const BlockReorderManager &amp;mgr, const Teuchos::RCP&lt; Thyra::ProductMultiVectorBase&lt; double &gt; &gt; &amp;blkVec)</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Thyra::MultiVectorBase&lt; double &gt; &gt;</type>
      <name>buildReorderedMultiVector</name>
      <anchorfile>classTeko_1_1BlockReorderManager.html</anchorfile>
      <anchor>ad2d1c5b793befa81f4385d1e75b5b092</anchor>
      <arglist>(const BlockReorderManager &amp;mgr, const Teuchos::RCP&lt; const Thyra::ProductMultiVectorBase&lt; double &gt; &gt; &amp;blkVec)</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; Thyra::MultiVectorBase&lt; double &gt; &gt;</type>
      <name>buildFlatMultiVector</name>
      <anchorfile>classTeko_1_1BlockReorderManager.html</anchorfile>
      <anchor>af0985f352aa90b11c2b5f1c6c827cdcc</anchor>
      <arglist>(const BlockReorderManager &amp;mgr, const Teuchos::RCP&lt; Thyra::ProductMultiVectorBase&lt; double &gt; &gt; &amp;blkVec)</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Thyra::MultiVectorBase&lt; double &gt; &gt;</type>
      <name>buildFlatMultiVector</name>
      <anchorfile>classTeko_1_1BlockReorderManager.html</anchorfile>
      <anchor>a7ad7cb6893e9d3e946eccc51b50b9ca5</anchor>
      <arglist>(const BlockReorderManager &amp;mgr, const Teuchos::RCP&lt; const Thyra::ProductMultiVectorBase&lt; double &gt; &gt; &amp;blkVec)</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const BlockReorderManager &gt;</type>
      <name>blockedReorderFromString</name>
      <anchorfile>classTeko_1_1BlockReorderManager.html</anchorfile>
      <anchor>a55e3c396e8ee2f7b21bcfc44be69445f</anchor>
      <arglist>(std::string &amp;reorder)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BlockReorderManager</name>
      <anchorfile>classTeko_1_1BlockReorderManager.html</anchorfile>
      <anchor>ad054fbdf8c316306f54af129d8def24b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BlockReorderManager</name>
      <anchorfile>classTeko_1_1BlockReorderManager.html</anchorfile>
      <anchor>a5428f7443ac8236f86c1d3c8f1090f38</anchor>
      <arglist>(int sz)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BlockReorderManager</name>
      <anchorfile>classTeko_1_1BlockReorderManager.html</anchorfile>
      <anchor>abaeae0e06f3afc98654f92eba8283eb9</anchor>
      <arglist>(const BlockReorderManager &amp;bmm)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~BlockReorderManager</name>
      <anchorfile>classTeko_1_1BlockReorderManager.html</anchorfile>
      <anchor>a171168d9a1090842c6b5d289fd6c8c26</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Teko::BlockUpperTriInverseOp</name>
    <filename>classTeko_1_1BlockUpperTriInverseOp.html</filename>
    <base>Teko::BlockImplicitLinearOp</base>
    <member kind="function">
      <type></type>
      <name>BlockUpperTriInverseOp</name>
      <anchorfile>classTeko_1_1BlockUpperTriInverseOp.html</anchorfile>
      <anchor>a48de84c91d15add523ba1f043a2d88c7</anchor>
      <arglist>(BlockedLinearOp &amp;U, const std::vector&lt; LinearOp &gt; &amp;invDiag)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual VectorSpace</type>
      <name>range</name>
      <anchorfile>classTeko_1_1BlockUpperTriInverseOp.html</anchorfile>
      <anchor>afb40233193fa459a2e496d3426e4b2cb</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual VectorSpace</type>
      <name>domain</name>
      <anchorfile>classTeko_1_1BlockUpperTriInverseOp.html</anchorfile>
      <anchor>ab9da14d80a90afdc4f4bda63fec4e66b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>implicitApply</name>
      <anchorfile>classTeko_1_1BlockUpperTriInverseOp.html</anchorfile>
      <anchor>a037b5f18cb590d1f6fa2d6dbe0913925</anchor>
      <arglist>(const BlockedMultiVector &amp;x, BlockedMultiVector &amp;y, const double alpha=1.0, const double beta=0.0) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>implicitApply</name>
      <anchorfile>classTeko_1_1BlockUpperTriInverseOp.html</anchorfile>
      <anchor>a74ec755c5bf5050efd7776f10cea9b79</anchor>
      <arglist>(const Thyra::EOpTransp M_trans, const BlockedMultiVector &amp;x, BlockedMultiVector &amp;y, const double alpha=1.0, const double beta=0.0) const </arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>const BlockedLinearOp</type>
      <name>U_</name>
      <anchorfile>classTeko_1_1BlockUpperTriInverseOp.html</anchorfile>
      <anchor>a14833f37c089711a48f5faa9b869973a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>std::vector&lt; LinearOp &gt;</type>
      <name>invDiag_</name>
      <anchorfile>classTeko_1_1BlockUpperTriInverseOp.html</anchorfile>
      <anchor>ab00c6fec1bd440205e061c4fcd6db22f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>Teuchos::RCP&lt; const Thyra::ProductVectorSpaceBase&lt; double &gt; &gt;</type>
      <name>productRange_</name>
      <anchorfile>classTeko_1_1BlockUpperTriInverseOp.html</anchorfile>
      <anchor>a51dd08d7a48cb4e6af0ca18069de2a77</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>Teuchos::RCP&lt; const Thyra::ProductVectorSpaceBase&lt; double &gt; &gt;</type>
      <name>productDomain_</name>
      <anchorfile>classTeko_1_1BlockUpperTriInverseOp.html</anchorfile>
      <anchor>a161552e2c89545fb21fbadeeab99453e</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual VectorSpace</type>
      <name>range</name>
      <anchorfile>classTeko_1_1BlockUpperTriInverseOp.html</anchorfile>
      <anchor>afb40233193fa459a2e496d3426e4b2cb</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual VectorSpace</type>
      <name>domain</name>
      <anchorfile>classTeko_1_1BlockUpperTriInverseOp.html</anchorfile>
      <anchor>ab9da14d80a90afdc4f4bda63fec4e66b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>implicitApply</name>
      <anchorfile>classTeko_1_1BlockUpperTriInverseOp.html</anchorfile>
      <anchor>a037b5f18cb590d1f6fa2d6dbe0913925</anchor>
      <arglist>(const BlockedMultiVector &amp;x, BlockedMultiVector &amp;y, const double alpha=1.0, const double beta=0.0) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>implicitApply</name>
      <anchorfile>classTeko_1_1BlockUpperTriInverseOp.html</anchorfile>
      <anchor>a74ec755c5bf5050efd7776f10cea9b79</anchor>
      <arglist>(const Thyra::EOpTransp M_trans, const BlockedMultiVector &amp;x, BlockedMultiVector &amp;y, const double alpha=1.0, const double beta=0.0) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Teko::Cloneable</name>
    <filename>classTeko_1_1Cloneable.html</filename>
    <member kind="function" virtualness="pure">
      <type>virtual Teuchos::RCP&lt; Cloneable &gt;</type>
      <name>clone</name>
      <anchorfile>classTeko_1_1Cloneable.html</anchorfile>
      <anchor>ad3db801e50d5041cac8d317108ce7d91</anchor>
      <arglist>() const  =0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Teko::CloneFactory</name>
    <filename>classTeko_1_1CloneFactory.html</filename>
    <templarg>CloneBaseType</templarg>
    <member kind="function">
      <type></type>
      <name>CloneFactory</name>
      <anchorfile>classTeko_1_1CloneFactory.html</anchorfile>
      <anchor>a349930237d498364534e5ac4a90c660f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>CloneFactory</name>
      <anchorfile>classTeko_1_1CloneFactory.html</anchorfile>
      <anchor>ad2098c7447d66836f1ddbc4513548bbd</anchor>
      <arglist>(const CloneFactory&lt; CloneBaseType &gt; &amp;cf)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual Teuchos::RCP&lt; CloneBaseType &gt;</type>
      <name>build</name>
      <anchorfile>classTeko_1_1CloneFactory.html</anchorfile>
      <anchor>a86728570033997085a22ac13ad167ae0</anchor>
      <arglist>(const std::string &amp;str) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>addClone</name>
      <anchorfile>classTeko_1_1CloneFactory.html</anchorfile>
      <anchor>a45bd4fc544b583974dee99cc810c54d2</anchor>
      <arglist>(const std::string &amp;str, const Teuchos::RCP&lt; Cloneable &gt; &amp;clone)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>cloneCount</name>
      <anchorfile>classTeko_1_1CloneFactory.html</anchorfile>
      <anchor>a9752d76bb5d6f0fce1b51348231347f0</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>getCloneNames</name>
      <anchorfile>classTeko_1_1CloneFactory.html</anchorfile>
      <anchor>a46978738444cc2bd2c040897448c833c</anchor>
      <arglist>(std::vector&lt; std::string &gt; &amp;names) const </arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>std::map&lt; std::string, Teuchos::RCP&lt; const Cloneable &gt; &gt;</type>
      <name>parentClones_</name>
      <anchorfile>classTeko_1_1CloneFactory.html</anchorfile>
      <anchor>a220c653fbfd275e390e06c3fcfc5a156</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>CloneFactory&lt; Teko::LU2x2Strategy &gt;</name>
    <filename>classTeko_1_1CloneFactory.html</filename>
    <member kind="function">
      <type></type>
      <name>CloneFactory</name>
      <anchorfile>classTeko_1_1CloneFactory.html</anchorfile>
      <anchor>a349930237d498364534e5ac4a90c660f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>CloneFactory</name>
      <anchorfile>classTeko_1_1CloneFactory.html</anchorfile>
      <anchor>ad2098c7447d66836f1ddbc4513548bbd</anchor>
      <arglist>(const CloneFactory&lt; Teko::LU2x2Strategy &gt; &amp;cf)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual Teuchos::RCP&lt; Teko::LU2x2Strategy &gt;</type>
      <name>build</name>
      <anchorfile>classTeko_1_1CloneFactory.html</anchorfile>
      <anchor>a86728570033997085a22ac13ad167ae0</anchor>
      <arglist>(const std::string &amp;str) const</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>addClone</name>
      <anchorfile>classTeko_1_1CloneFactory.html</anchorfile>
      <anchor>a45bd4fc544b583974dee99cc810c54d2</anchor>
      <arglist>(const std::string &amp;str, const Teuchos::RCP&lt; Cloneable &gt; &amp;clone)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>cloneCount</name>
      <anchorfile>classTeko_1_1CloneFactory.html</anchorfile>
      <anchor>a9752d76bb5d6f0fce1b51348231347f0</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>getCloneNames</name>
      <anchorfile>classTeko_1_1CloneFactory.html</anchorfile>
      <anchor>a46978738444cc2bd2c040897448c833c</anchor>
      <arglist>(std::vector&lt; std::string &gt; &amp;names) const</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>std::map&lt; std::string, Teuchos::RCP&lt; const Cloneable &gt; &gt;</type>
      <name>parentClones_</name>
      <anchorfile>classTeko_1_1CloneFactory.html</anchorfile>
      <anchor>a220c653fbfd275e390e06c3fcfc5a156</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>CloneFactory&lt; Teko::NS::LSCStrategy &gt;</name>
    <filename>classTeko_1_1CloneFactory.html</filename>
    <member kind="function">
      <type></type>
      <name>CloneFactory</name>
      <anchorfile>classTeko_1_1CloneFactory.html</anchorfile>
      <anchor>a349930237d498364534e5ac4a90c660f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>CloneFactory</name>
      <anchorfile>classTeko_1_1CloneFactory.html</anchorfile>
      <anchor>ad2098c7447d66836f1ddbc4513548bbd</anchor>
      <arglist>(const CloneFactory&lt; Teko::NS::LSCStrategy &gt; &amp;cf)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual Teuchos::RCP&lt; Teko::NS::LSCStrategy &gt;</type>
      <name>build</name>
      <anchorfile>classTeko_1_1CloneFactory.html</anchorfile>
      <anchor>a86728570033997085a22ac13ad167ae0</anchor>
      <arglist>(const std::string &amp;str) const</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>addClone</name>
      <anchorfile>classTeko_1_1CloneFactory.html</anchorfile>
      <anchor>a45bd4fc544b583974dee99cc810c54d2</anchor>
      <arglist>(const std::string &amp;str, const Teuchos::RCP&lt; Cloneable &gt; &amp;clone)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>cloneCount</name>
      <anchorfile>classTeko_1_1CloneFactory.html</anchorfile>
      <anchor>a9752d76bb5d6f0fce1b51348231347f0</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>getCloneNames</name>
      <anchorfile>classTeko_1_1CloneFactory.html</anchorfile>
      <anchor>a46978738444cc2bd2c040897448c833c</anchor>
      <arglist>(std::vector&lt; std::string &gt; &amp;names) const</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>std::map&lt; std::string, Teuchos::RCP&lt; const Cloneable &gt; &gt;</type>
      <name>parentClones_</name>
      <anchorfile>classTeko_1_1CloneFactory.html</anchorfile>
      <anchor>a220c653fbfd275e390e06c3fcfc5a156</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>CloneFactory&lt; Teko::PreconditionerFactory &gt;</name>
    <filename>classTeko_1_1CloneFactory.html</filename>
    <member kind="function">
      <type></type>
      <name>CloneFactory</name>
      <anchorfile>classTeko_1_1CloneFactory.html</anchorfile>
      <anchor>a349930237d498364534e5ac4a90c660f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>CloneFactory</name>
      <anchorfile>classTeko_1_1CloneFactory.html</anchorfile>
      <anchor>ad2098c7447d66836f1ddbc4513548bbd</anchor>
      <arglist>(const CloneFactory&lt; Teko::PreconditionerFactory &gt; &amp;cf)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual Teuchos::RCP&lt; Teko::PreconditionerFactory &gt;</type>
      <name>build</name>
      <anchorfile>classTeko_1_1CloneFactory.html</anchorfile>
      <anchor>a86728570033997085a22ac13ad167ae0</anchor>
      <arglist>(const std::string &amp;str) const</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>addClone</name>
      <anchorfile>classTeko_1_1CloneFactory.html</anchorfile>
      <anchor>a45bd4fc544b583974dee99cc810c54d2</anchor>
      <arglist>(const std::string &amp;str, const Teuchos::RCP&lt; Cloneable &gt; &amp;clone)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>cloneCount</name>
      <anchorfile>classTeko_1_1CloneFactory.html</anchorfile>
      <anchor>a9752d76bb5d6f0fce1b51348231347f0</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>getCloneNames</name>
      <anchorfile>classTeko_1_1CloneFactory.html</anchorfile>
      <anchor>a46978738444cc2bd2c040897448c833c</anchor>
      <arglist>(std::vector&lt; std::string &gt; &amp;names) const</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>std::map&lt; std::string, Teuchos::RCP&lt; const Cloneable &gt; &gt;</type>
      <name>parentClones_</name>
      <anchorfile>classTeko_1_1CloneFactory.html</anchorfile>
      <anchor>a220c653fbfd275e390e06c3fcfc5a156</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Teko::Epetra::DefaultMappingStrategy</name>
    <filename>classTeko_1_1Epetra_1_1DefaultMappingStrategy.html</filename>
    <base>Teko::Epetra::MappingStrategy</base>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>copyEpetraIntoThyra</name>
      <anchorfile>classTeko_1_1Epetra_1_1DefaultMappingStrategy.html</anchorfile>
      <anchor>a8104c834db444f62e340ad07d1be009e</anchor>
      <arglist>(const Epetra_MultiVector &amp;epetraX, const Teuchos::Ptr&lt; Thyra::MultiVectorBase&lt; double &gt; &gt; &amp;thyraX) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>copyThyraIntoEpetra</name>
      <anchorfile>classTeko_1_1Epetra_1_1DefaultMappingStrategy.html</anchorfile>
      <anchor>ae6d5f89e4eca8f923ace7dcacc2e7c94</anchor>
      <arglist>(const RCP&lt; const Thyra::MultiVectorBase&lt; double &gt; &gt; &amp;thyraX, Epetra_MultiVector &amp;epetraX) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const RCP&lt; const Epetra_Map &gt;</type>
      <name>domainMap</name>
      <anchorfile>classTeko_1_1Epetra_1_1DefaultMappingStrategy.html</anchorfile>
      <anchor>a72667198f055edc4d271ea6456832548</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const RCP&lt; const Epetra_Map &gt;</type>
      <name>rangeMap</name>
      <anchorfile>classTeko_1_1Epetra_1_1DefaultMappingStrategy.html</anchorfile>
      <anchor>a8c74be6a689b85b1045f1a8e2d701eed</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual std::string</type>
      <name>toString</name>
      <anchorfile>classTeko_1_1Epetra_1_1DefaultMappingStrategy.html</anchorfile>
      <anchor>a0ef0c7d6ccf56989b0551437254dc810</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>RCP&lt; const Thyra::VectorSpaceBase&lt; double &gt; &gt;</type>
      <name>domainSpace_</name>
      <anchorfile>classTeko_1_1Epetra_1_1DefaultMappingStrategy.html</anchorfile>
      <anchor>a5dee9e101da60be5f2843be74ef0ddbf</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>RCP&lt; const Thyra::VectorSpaceBase&lt; double &gt; &gt;</type>
      <name>rangeSpace_</name>
      <anchorfile>classTeko_1_1Epetra_1_1DefaultMappingStrategy.html</anchorfile>
      <anchor>a2b13de5e71f1dbaae915655dc41cf414</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>RCP&lt; const Epetra_Map &gt;</type>
      <name>domainMap_</name>
      <anchorfile>classTeko_1_1Epetra_1_1DefaultMappingStrategy.html</anchorfile>
      <anchor>a59dbd85bbd0b7d675e211fc02a7a3ebd</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>RCP&lt; const Epetra_Map &gt;</type>
      <name>rangeMap_</name>
      <anchorfile>classTeko_1_1Epetra_1_1DefaultMappingStrategy.html</anchorfile>
      <anchor>a95555af62474d37b42af2df6eb6f3a90</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Teko::TpetraHelpers::DefaultMappingStrategy</name>
    <filename>classTeko_1_1TpetraHelpers_1_1DefaultMappingStrategy.html</filename>
    <base>Teko::TpetraHelpers::MappingStrategy</base>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>copyTpetraIntoThyra</name>
      <anchorfile>classTeko_1_1TpetraHelpers_1_1DefaultMappingStrategy.html</anchorfile>
      <anchor>ada8996b6d2587ce3f10efc9d06fefcf5</anchor>
      <arglist>(const Tpetra::MultiVector&lt; ST, LO, GO, NT &gt; &amp;tpetraX, const Teuchos::Ptr&lt; Thyra::MultiVectorBase&lt; ST &gt; &gt; &amp;thyraX) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>copyThyraIntoTpetra</name>
      <anchorfile>classTeko_1_1TpetraHelpers_1_1DefaultMappingStrategy.html</anchorfile>
      <anchor>a2f5a2a17225890c41ec005573f042424</anchor>
      <arglist>(const RCP&lt; const Thyra::MultiVectorBase&lt; ST &gt; &gt; &amp;thyraX, Tpetra::MultiVector&lt; ST, LO, GO, NT &gt; &amp;tpetraX) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const RCP&lt; const Tpetra::Map&lt; LO, GO, NT &gt; &gt;</type>
      <name>domainMap</name>
      <anchorfile>classTeko_1_1TpetraHelpers_1_1DefaultMappingStrategy.html</anchorfile>
      <anchor>ad177d478bd47ec75a0add96f9e9157e1</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const RCP&lt; const Tpetra::Map&lt; LO, GO, NT &gt; &gt;</type>
      <name>rangeMap</name>
      <anchorfile>classTeko_1_1TpetraHelpers_1_1DefaultMappingStrategy.html</anchorfile>
      <anchor>ae6e5a01b3ef1eefcd19746e0a4c3a460</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual std::string</type>
      <name>toString</name>
      <anchorfile>classTeko_1_1TpetraHelpers_1_1DefaultMappingStrategy.html</anchorfile>
      <anchor>abbe33655ac8b829fbe6305c3ac0d5b52</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>RCP&lt; const Thyra::VectorSpaceBase&lt; ST &gt; &gt;</type>
      <name>domainSpace_</name>
      <anchorfile>classTeko_1_1TpetraHelpers_1_1DefaultMappingStrategy.html</anchorfile>
      <anchor>a630dc6d71315bd40d620b4a9289d1d70</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>RCP&lt; const Thyra::VectorSpaceBase&lt; ST &gt; &gt;</type>
      <name>rangeSpace_</name>
      <anchorfile>classTeko_1_1TpetraHelpers_1_1DefaultMappingStrategy.html</anchorfile>
      <anchor>a539cd56cf19ac5ee13025cedb95d6114</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>RCP&lt; const Tpetra::Map&lt; LO, GO, NT &gt; &gt;</type>
      <name>domainMap_</name>
      <anchorfile>classTeko_1_1TpetraHelpers_1_1DefaultMappingStrategy.html</anchorfile>
      <anchor>a58f88db513b9cf4e99184160000d8d76</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>RCP&lt; const Tpetra::Map&lt; LO, GO, NT &gt; &gt;</type>
      <name>rangeMap_</name>
      <anchorfile>classTeko_1_1TpetraHelpers_1_1DefaultMappingStrategy.html</anchorfile>
      <anchor>ae90adf330e278a4c9012ef0b763c4174</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Teko::DiagnosticLinearOp</name>
    <filename>classTeko_1_1DiagnosticLinearOp.html</filename>
    <base>Teko::ImplicitLinearOp</base>
    <member kind="function">
      <type></type>
      <name>DiagnosticLinearOp</name>
      <anchorfile>classTeko_1_1DiagnosticLinearOp.html</anchorfile>
      <anchor>ac49ebdc3538f669401c040456735200a</anchor>
      <arglist>(const Teuchos::RCP&lt; std::ostream &gt; &amp;ostrm, const ModifiableLinearOp &amp;A, const std::string &amp;diagnosticString)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>DiagnosticLinearOp</name>
      <anchorfile>classTeko_1_1DiagnosticLinearOp.html</anchorfile>
      <anchor>a8999e7c0e78ba0ea00efb5a0b769d5ac</anchor>
      <arglist>(const Teuchos::RCP&lt; std::ostream &gt; &amp;ostrm, const LinearOp &amp;A, const std::string &amp;diagnosticString)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>DiagnosticLinearOp</name>
      <anchorfile>classTeko_1_1DiagnosticLinearOp.html</anchorfile>
      <anchor>a4fb6600f52ba9ade0329987c066c9d03</anchor>
      <arglist>(const Teuchos::RCP&lt; std::ostream &gt; &amp;ostrm, const LinearOp &amp;fwdOp, const ModifiableLinearOp &amp;A, const std::string &amp;diagnosticString)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~DiagnosticLinearOp</name>
      <anchorfile>classTeko_1_1DiagnosticLinearOp.html</anchorfile>
      <anchor>a3371ca4d5c50e5a0857a65414d046485</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual VectorSpace</type>
      <name>range</name>
      <anchorfile>classTeko_1_1DiagnosticLinearOp.html</anchorfile>
      <anchor>a3140c2762b90fda11192caaa67cb7ad4</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual VectorSpace</type>
      <name>domain</name>
      <anchorfile>classTeko_1_1DiagnosticLinearOp.html</anchorfile>
      <anchor>abdb404540e521b63888005af09f3450f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>implicitApply</name>
      <anchorfile>classTeko_1_1DiagnosticLinearOp.html</anchorfile>
      <anchor>a1a752219f51a1a4e9c37c3af87176e06</anchor>
      <arglist>(const MultiVector &amp;x, MultiVector &amp;y, const double alpha=1.0, const double beta=0.0) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual VectorSpace</type>
      <name>range</name>
      <anchorfile>classTeko_1_1DiagnosticLinearOp.html</anchorfile>
      <anchor>a3140c2762b90fda11192caaa67cb7ad4</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual VectorSpace</type>
      <name>domain</name>
      <anchorfile>classTeko_1_1DiagnosticLinearOp.html</anchorfile>
      <anchor>abdb404540e521b63888005af09f3450f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>implicitApply</name>
      <anchorfile>classTeko_1_1DiagnosticLinearOp.html</anchorfile>
      <anchor>a1a752219f51a1a4e9c37c3af87176e06</anchor>
      <arglist>(const MultiVector &amp;x, MultiVector &amp;y, const double alpha=1.0, const double beta=0.0) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Teko::DiagnosticPreconditionerFactory</name>
    <filename>classTeko_1_1DiagnosticPreconditionerFactory.html</filename>
    <base virtualness="virtual">Teko::PreconditionerFactory</base>
    <member kind="function">
      <type></type>
      <name>DiagnosticPreconditionerFactory</name>
      <anchorfile>classTeko_1_1DiagnosticPreconditionerFactory.html</anchorfile>
      <anchor>a2ede58756c107982d2b6766a97fc8611</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>DiagnosticPreconditionerFactory</name>
      <anchorfile>classTeko_1_1DiagnosticPreconditionerFactory.html</anchorfile>
      <anchor>a2b099a8d2b1a919a02c96457a0a2809e</anchor>
      <arglist>(const Teuchos::RCP&lt; Teko::InverseFactory &gt; &amp;invFactory, const std::string &amp;label, const Teuchos::RCP&lt; std::ostream &gt; &amp;os=Teuchos::null, bool printResidual=false)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~DiagnosticPreconditionerFactory</name>
      <anchorfile>classTeko_1_1DiagnosticPreconditionerFactory.html</anchorfile>
      <anchor>a0cc63b02ed06ab29fca8fda71fb0387b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual LinearOp</type>
      <name>buildPreconditionerOperator</name>
      <anchorfile>classTeko_1_1DiagnosticPreconditionerFactory.html</anchorfile>
      <anchor>a92b659685d659b44771dd2ae1ba9ae88</anchor>
      <arglist>(LinearOp &amp;lo, PreconditionerState &amp;state) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>initializeFromParameterList</name>
      <anchorfile>classTeko_1_1DiagnosticPreconditionerFactory.html</anchorfile>
      <anchor>a25b8737e62bf40c5f52a09686174fddb</anchor>
      <arglist>(const Teuchos::ParameterList &amp;settings)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual Teuchos::RCP&lt; Teuchos::ParameterList &gt;</type>
      <name>getRequestedParameters</name>
      <anchorfile>classTeko_1_1DiagnosticPreconditionerFactory.html</anchorfile>
      <anchor>a35fdb7eeb21c6b66fb02836b4ed9f1c6</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>updateRequestedParameters</name>
      <anchorfile>classTeko_1_1DiagnosticPreconditionerFactory.html</anchorfile>
      <anchor>a224f3f2cd9ef0641a49735fe5981331b</anchor>
      <arglist>(const Teuchos::ParameterList &amp;pl)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>initializeFromParameterList</name>
      <anchorfile>classTeko_1_1DiagnosticPreconditionerFactory.html</anchorfile>
      <anchor>a25b8737e62bf40c5f52a09686174fddb</anchor>
      <arglist>(const Teuchos::ParameterList &amp;settings)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual Teuchos::RCP&lt; Teuchos::ParameterList &gt;</type>
      <name>getRequestedParameters</name>
      <anchorfile>classTeko_1_1DiagnosticPreconditionerFactory.html</anchorfile>
      <anchor>a35fdb7eeb21c6b66fb02836b4ed9f1c6</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>updateRequestedParameters</name>
      <anchorfile>classTeko_1_1DiagnosticPreconditionerFactory.html</anchorfile>
      <anchor>a224f3f2cd9ef0641a49735fe5981331b</anchor>
      <arglist>(const Teuchos::ParameterList &amp;pl)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Teko::DiagonallyScaledPreconditionerFactory</name>
    <filename>classTeko_1_1DiagonallyScaledPreconditionerFactory.html</filename>
    <base virtualness="virtual">Teko::PreconditionerFactory</base>
    <member kind="function">
      <type></type>
      <name>DiagonallyScaledPreconditionerFactory</name>
      <anchorfile>classTeko_1_1DiagonallyScaledPreconditionerFactory.html</anchorfile>
      <anchor>a17921beed9697cc1492c30d08859cc28</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>DiagonallyScaledPreconditionerFactory</name>
      <anchorfile>classTeko_1_1DiagonallyScaledPreconditionerFactory.html</anchorfile>
      <anchor>ab376d04894e166643fbb05368f001a35</anchor>
      <arglist>(const Teuchos::RCP&lt; Teko::InverseFactory &gt; &amp;invFactory, ScalingType columnScaling=COLUMN_SCALING, DiagonalType diagonalType=AbsRowSum)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~DiagonallyScaledPreconditionerFactory</name>
      <anchorfile>classTeko_1_1DiagonallyScaledPreconditionerFactory.html</anchorfile>
      <anchor>abff25df44cb6c3ca31779d2202645ae2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual LinearOp</type>
      <name>buildPreconditionerOperator</name>
      <anchorfile>classTeko_1_1DiagonallyScaledPreconditionerFactory.html</anchorfile>
      <anchor>aeef48b6faf066e9fb8e899c40b7e9767</anchor>
      <arglist>(LinearOp &amp;lo, PreconditionerState &amp;state) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>initializeFromParameterList</name>
      <anchorfile>classTeko_1_1DiagonallyScaledPreconditionerFactory.html</anchorfile>
      <anchor>acb3713da098a139723248884eb2c6a80</anchor>
      <arglist>(const Teuchos::ParameterList &amp;settings)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>initializeFromParameterList</name>
      <anchorfile>classTeko_1_1DiagonallyScaledPreconditionerFactory.html</anchorfile>
      <anchor>acb3713da098a139723248884eb2c6a80</anchor>
      <arglist>(const Teuchos::ParameterList &amp;settings)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Teko::DiagonalPreconditionerFactory</name>
    <filename>classTeko_1_1DiagonalPreconditionerFactory.html</filename>
    <base virtualness="virtual">Teko::PreconditionerFactory</base>
    <member kind="function">
      <type>Teuchos::RCP&lt; PreconditionerState &gt;</type>
      <name>buildPreconditionerState</name>
      <anchorfile>classTeko_1_1DiagonalPreconditionerFactory.html</anchorfile>
      <anchor>a304dc3cc835992d64671c9504c2217a5</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>LinearOp</type>
      <name>buildPreconditionerOperator</name>
      <anchorfile>classTeko_1_1DiagonalPreconditionerFactory.html</anchorfile>
      <anchor>a96cf0c2749c5fadbb827cbf8cac70b6f</anchor>
      <arglist>(LinearOp &amp;lo, PreconditionerState &amp;state) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>initializeFromParameterList</name>
      <anchorfile>classTeko_1_1DiagonalPreconditionerFactory.html</anchorfile>
      <anchor>a487d59be6f8e6d9551122d53b1d7670b</anchor>
      <arglist>(const Teuchos::ParameterList &amp;pl)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>Teuchos::ParameterList</type>
      <name>List_</name>
      <anchorfile>classTeko_1_1DiagonalPreconditionerFactory.html</anchorfile>
      <anchor>aaa1fc2444bb0550b07a203bf51cd7fff</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Teko::DiagonalPrecondState</name>
    <filename>classTeko_1_1DiagonalPrecondState.html</filename>
    <base>Teko::PreconditionerState</base>
  </compound>
  <compound kind="class">
    <name>Teko::Epetra::EpetraBlockPreconditioner</name>
    <filename>classTeko_1_1Epetra_1_1EpetraBlockPreconditioner.html</filename>
    <member kind="function">
      <type></type>
      <name>EpetraBlockPreconditioner</name>
      <anchorfile>classTeko_1_1Epetra_1_1EpetraBlockPreconditioner.html</anchorfile>
      <anchor>a4f61135a1cd4c176c9f740779f536c1a</anchor>
      <arglist>(const Teuchos::RCP&lt; const PreconditionerFactory &gt; &amp;bfp)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>initPreconditioner</name>
      <anchorfile>classTeko_1_1Epetra_1_1EpetraBlockPreconditioner.html</anchorfile>
      <anchor>ab04d585a1a5ad21d58d40f26e2c7c714</anchor>
      <arglist>(bool clearOld=false)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>buildPreconditioner</name>
      <anchorfile>classTeko_1_1Epetra_1_1EpetraBlockPreconditioner.html</anchorfile>
      <anchor>ae42f70808dd94d3cdcee0eb4962d2f0f</anchor>
      <arglist>(const Teuchos::RCP&lt; const Epetra_Operator &gt; &amp;A, bool clear=true)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>buildPreconditioner</name>
      <anchorfile>classTeko_1_1Epetra_1_1EpetraBlockPreconditioner.html</anchorfile>
      <anchor>a0265f66cfad4ccdb89165407bad13244</anchor>
      <arglist>(const Teuchos::RCP&lt; const Epetra_Operator &gt; &amp;A, const Epetra_MultiVector &amp;mv, bool clear=true)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>rebuildPreconditioner</name>
      <anchorfile>classTeko_1_1Epetra_1_1EpetraBlockPreconditioner.html</anchorfile>
      <anchor>af9e95731b6c91e69df8d35eb353c1f45</anchor>
      <arglist>(const Teuchos::RCP&lt; const Epetra_Operator &gt; &amp;A)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>rebuildPreconditioner</name>
      <anchorfile>classTeko_1_1Epetra_1_1EpetraBlockPreconditioner.html</anchorfile>
      <anchor>a0d3df26f238d52955c7321baeafde6a3</anchor>
      <arglist>(const Teuchos::RCP&lt; const Epetra_Operator &gt; &amp;A, const Epetra_MultiVector &amp;mv)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual Teuchos::RCP&lt; PreconditionerState &gt;</type>
      <name>getPreconditionerState</name>
      <anchorfile>classTeko_1_1Epetra_1_1EpetraBlockPreconditioner.html</anchorfile>
      <anchor>aa706ceccc5ec83e00a027e8d63c9a817</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual Teuchos::RCP&lt; const PreconditionerState &gt;</type>
      <name>getPreconditionerState</name>
      <anchorfile>classTeko_1_1Epetra_1_1EpetraBlockPreconditioner.html</anchorfile>
      <anchor>ab722fb04258f2c3dd81f844114d83e87</anchor>
      <arglist>() const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Teko::Epetra::EpetraOperatorWrapper</name>
    <filename>classTeko_1_1Epetra_1_1EpetraOperatorWrapper.html</filename>
    <member kind="function">
      <type>const RCP&lt; const Thyra::LinearOpBase&lt; double &gt; &gt;</type>
      <name>getThyraOp</name>
      <anchorfile>classTeko_1_1Epetra_1_1EpetraOperatorWrapper.html</anchorfile>
      <anchor>acf1eace048b9372d382d70529125bdd2</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const RCP&lt; const MappingStrategy &gt;</type>
      <name>getMapStrategy</name>
      <anchorfile>classTeko_1_1Epetra_1_1EpetraOperatorWrapper.html</anchorfile>
      <anchor>ae186f6e1d99807c37e7f2e74b52e2346</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>GetBlockRowCount</name>
      <anchorfile>classTeko_1_1Epetra_1_1EpetraOperatorWrapper.html</anchorfile>
      <anchor>a2f60c247e3f24edd2827cb85cbe3a100</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>GetBlockColCount</name>
      <anchorfile>classTeko_1_1Epetra_1_1EpetraOperatorWrapper.html</anchorfile>
      <anchor>a55a141a8930652b3717c5cb913f30469</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Epetra_Operator &gt;</type>
      <name>GetBlock</name>
      <anchorfile>classTeko_1_1Epetra_1_1EpetraOperatorWrapper.html</anchorfile>
      <anchor>a5a7cbf2d008a895c39fe6dba226fa2a1</anchor>
      <arglist>(int i, int j) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Teko::GaussSeidelPreconditionerFactory</name>
    <filename>classTeko_1_1GaussSeidelPreconditionerFactory.html</filename>
    <base>Teko::BlockPreconditionerFactory</base>
    <member kind="function">
      <type>LinearOp</type>
      <name>buildPreconditionerOperator</name>
      <anchorfile>classTeko_1_1GaussSeidelPreconditionerFactory.html</anchorfile>
      <anchor>a0436a86cd2d02db335a277c451305cdb</anchor>
      <arglist>(BlockedLinearOp &amp;blo, BlockPreconditionerState &amp;state) const </arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>GaussSeidelPreconditionerFactory</name>
      <anchorfile>classTeko_1_1GaussSeidelPreconditionerFactory.html</anchorfile>
      <anchor>ab774a91fd5d7956df335de3a1e7c7961</anchor>
      <arglist>(TriSolveType solveType, const LinearOp &amp;invD0, const LinearOp &amp;invD1)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>GaussSeidelPreconditionerFactory</name>
      <anchorfile>classTeko_1_1GaussSeidelPreconditionerFactory.html</anchorfile>
      <anchor>ae5581c50bc3ca536e2a83eb11cc1ae33</anchor>
      <arglist>(TriSolveType solveType, const RCP&lt; const BlockInvDiagonalStrategy &gt; &amp;strategy)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>GaussSeidelPreconditionerFactory</name>
      <anchorfile>classTeko_1_1GaussSeidelPreconditionerFactory.html</anchorfile>
      <anchor>a8664b1c00f9dd76d68073563ed4f74b3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual void</type>
      <name>initializeFromParameterList</name>
      <anchorfile>classTeko_1_1GaussSeidelPreconditionerFactory.html</anchorfile>
      <anchor>ab9cb4216fdf877d8128f497b8e430db5</anchor>
      <arglist>(const Teuchos::ParameterList &amp;pl)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>Teuchos::RCP&lt; const BlockInvDiagonalStrategy &gt;</type>
      <name>invOpsStrategy_</name>
      <anchorfile>classTeko_1_1GaussSeidelPreconditionerFactory.html</anchorfile>
      <anchor>aac268ef7b4aa975da269f82eee791386</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>GaussSeidelPreconditionerFactory</name>
      <anchorfile>classTeko_1_1GaussSeidelPreconditionerFactory.html</anchorfile>
      <anchor>ab774a91fd5d7956df335de3a1e7c7961</anchor>
      <arglist>(TriSolveType solveType, const LinearOp &amp;invD0, const LinearOp &amp;invD1)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>GaussSeidelPreconditionerFactory</name>
      <anchorfile>classTeko_1_1GaussSeidelPreconditionerFactory.html</anchorfile>
      <anchor>ae5581c50bc3ca536e2a83eb11cc1ae33</anchor>
      <arglist>(TriSolveType solveType, const RCP&lt; const BlockInvDiagonalStrategy &gt; &amp;strategy)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>GaussSeidelPreconditionerFactory</name>
      <anchorfile>classTeko_1_1GaussSeidelPreconditionerFactory.html</anchorfile>
      <anchor>a8664b1c00f9dd76d68073563ed4f74b3</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Teko::IdentityPreconditionerFactory</name>
    <filename>classTeko_1_1IdentityPreconditionerFactory.html</filename>
    <base>Teko::PreconditionerFactory</base>
    <member kind="function">
      <type>LinearOp</type>
      <name>buildPreconditionerOperator</name>
      <anchorfile>classTeko_1_1IdentityPreconditionerFactory.html</anchorfile>
      <anchor>aeedd37add8ffe9fcf70cc8b86c85bada</anchor>
      <arglist>(LinearOp &amp;lo, PreconditionerState &amp;state) const </arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>IdentityPreconditionerFactory</name>
      <anchorfile>classTeko_1_1IdentityPreconditionerFactory.html</anchorfile>
      <anchor>a9fe24c5ae794517cc1969db6d2bd71e6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual void</type>
      <name>initializeFromParameterList</name>
      <anchorfile>classTeko_1_1IdentityPreconditionerFactory.html</anchorfile>
      <anchor>a59fdf02f8ef7fcb4158bf6e7ad7fcd83</anchor>
      <arglist>(const Teuchos::ParameterList &amp;pl)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>double</type>
      <name>scaling_</name>
      <anchorfile>classTeko_1_1IdentityPreconditionerFactory.html</anchorfile>
      <anchor>aca410a3e95772c511cb9642c4c45dfb3</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>IdentityPreconditionerFactory</name>
      <anchorfile>classTeko_1_1IdentityPreconditionerFactory.html</anchorfile>
      <anchor>a9fe24c5ae794517cc1969db6d2bd71e6</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Teko::ImplicitLinearOp</name>
    <filename>classTeko_1_1ImplicitLinearOp.html</filename>
    <member kind="function" virtualness="pure">
      <type>virtual VectorSpace</type>
      <name>range</name>
      <anchorfile>classTeko_1_1ImplicitLinearOp.html</anchorfile>
      <anchor>ae61a490341aa4589fdd78c897480d489</anchor>
      <arglist>() const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual VectorSpace</type>
      <name>domain</name>
      <anchorfile>classTeko_1_1ImplicitLinearOp.html</anchorfile>
      <anchor>a7642dee230a45eb1d9255846949dec50</anchor>
      <arglist>() const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>implicitApply</name>
      <anchorfile>classTeko_1_1ImplicitLinearOp.html</anchorfile>
      <anchor>a8e44d0b04a968308afff7f48793937b1</anchor>
      <arglist>(const MultiVector &amp;x, MultiVector &amp;y, const double alpha=1.0, const double beta=0.0) const  =0</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual bool</type>
      <name>opSupportedImpl</name>
      <anchorfile>classTeko_1_1ImplicitLinearOp.html</anchorfile>
      <anchor>a793596e92acada3cbc969cb27cc29020</anchor>
      <arglist>(const Thyra::EOpTransp M_trans) const </arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual bool</type>
      <name>opSupportedImpl</name>
      <anchorfile>classTeko_1_1ImplicitLinearOp.html</anchorfile>
      <anchor>a793596e92acada3cbc969cb27cc29020</anchor>
      <arglist>(const Thyra::EOpTransp M_trans) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Teko::InverseFactory</name>
    <filename>classTeko_1_1InverseFactory.html</filename>
    <base>Teko::RequestHandlerContainer</base>
    <member kind="function" virtualness="pure">
      <type>virtual InverseLinearOp</type>
      <name>buildInverse</name>
      <anchorfile>classTeko_1_1InverseFactory.html</anchorfile>
      <anchor>ac4b5e7288f96c83180f86c2e04eccd55</anchor>
      <arglist>(const LinearOp &amp;linearOp) const  =0</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual InverseLinearOp</type>
      <name>buildInverse</name>
      <anchorfile>classTeko_1_1InverseFactory.html</anchorfile>
      <anchor>a75366f53d6700307fe1c2bc5eb17d6fd</anchor>
      <arglist>(const LinearOp &amp;linearOp, const LinearOp &amp;precOp) const </arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>rebuildInverse</name>
      <anchorfile>classTeko_1_1InverseFactory.html</anchorfile>
      <anchor>a0e393fb8f75f9f33c1050b21296fd17c</anchor>
      <arglist>(const LinearOp &amp;source, InverseLinearOp &amp;dest) const  =0</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>rebuildInverse</name>
      <anchorfile>classTeko_1_1InverseFactory.html</anchorfile>
      <anchor>a840a3d88afeb9090264d581fc41cfa84</anchor>
      <arglist>(const LinearOp &amp;source, const LinearOp &amp;precOp, InverseLinearOp &amp;dest) const </arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual Teuchos::RCP&lt; const Teuchos::ParameterList &gt;</type>
      <name>getParameterList</name>
      <anchorfile>classTeko_1_1InverseFactory.html</anchorfile>
      <anchor>a05d492c47275aebb067e3caaea11c67e</anchor>
      <arglist>() const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual std::string</type>
      <name>toString</name>
      <anchorfile>classTeko_1_1InverseFactory.html</anchorfile>
      <anchor>a3079d5e6f70d0b30fe62e92f195115d2</anchor>
      <arglist>() const  =0</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual Teuchos::RCP&lt; Teuchos::ParameterList &gt;</type>
      <name>getRequestedParameters</name>
      <anchorfile>classTeko_1_1InverseFactory.html</anchorfile>
      <anchor>a32ebfee4ffdd10fe62f13423a098b146</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>updateRequestedParameters</name>
      <anchorfile>classTeko_1_1InverseFactory.html</anchorfile>
      <anchor>a3bc2fd0254681b4092d910dd2ba7db96</anchor>
      <arglist>(const Teuchos::ParameterList &amp;pl)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setRequestHandler</name>
      <anchorfile>classTeko_1_1InverseFactory.html</anchorfile>
      <anchor>a1cfd94c10b9fa05e7aa32807d6258450</anchor>
      <arglist>(const Teuchos::RCP&lt; RequestHandler &gt; &amp;rh)</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; RequestHandler &gt;</type>
      <name>getRequestHandler</name>
      <anchorfile>classTeko_1_1InverseFactory.html</anchorfile>
      <anchor>a5cf7ac515350dbab763c747e87e803a3</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>Teuchos::RCP&lt; RequestHandler &gt;</type>
      <name>callbackHandler_</name>
      <anchorfile>classTeko_1_1InverseFactory.html</anchorfile>
      <anchor>af501ddd62b668a9de3dedcc9e55c2c52</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>InverseLinearOp</type>
      <name>buildInverse</name>
      <anchorfile>classTeko_1_1InverseFactory.html</anchorfile>
      <anchor>a9f04aba1c3754f725507ae355352bb22</anchor>
      <arglist>(const InverseFactory &amp;factory, const LinearOp &amp;A, const LinearOp &amp;precOp)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>rebuildInverse</name>
      <anchorfile>classTeko_1_1InverseFactory.html</anchorfile>
      <anchor>a986d5b512c8f5a195c9e365616a9fa8d</anchor>
      <arglist>(const InverseFactory &amp;factory, const LinearOp &amp;A, const LinearOp &amp;precOp, InverseLinearOp &amp;invA)</arglist>
    </member>
    <member kind="function">
      <type>InverseLinearOp</type>
      <name>buildInverse</name>
      <anchorfile>classTeko_1_1InverseFactory.html</anchorfile>
      <anchor>af2c1187cec72755642ac093b1e1b0c62</anchor>
      <arglist>(const InverseFactory &amp;factory, const LinearOp &amp;A)</arglist>
    </member>
    <member kind="function">
      <type>InverseLinearOp</type>
      <name>buildInverse</name>
      <anchorfile>classTeko_1_1InverseFactory.html</anchorfile>
      <anchor>a9f04aba1c3754f725507ae355352bb22</anchor>
      <arglist>(const InverseFactory &amp;factory, const LinearOp &amp;A, const LinearOp &amp;precOp)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>rebuildInverse</name>
      <anchorfile>classTeko_1_1InverseFactory.html</anchorfile>
      <anchor>a38dbd59742785c3fbcb240eb101733ea</anchor>
      <arglist>(const InverseFactory &amp;factory, const LinearOp &amp;A, InverseLinearOp &amp;invA)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>rebuildInverse</name>
      <anchorfile>classTeko_1_1InverseFactory.html</anchorfile>
      <anchor>a986d5b512c8f5a195c9e365616a9fa8d</anchor>
      <arglist>(const InverseFactory &amp;factory, const LinearOp &amp;A, const LinearOp &amp;precOp, InverseLinearOp &amp;invA)</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; InverseFactory &gt;</type>
      <name>invFactoryFromParamList</name>
      <anchorfile>classTeko_1_1InverseFactory.html</anchorfile>
      <anchor>aaf54f451a81de60ae7fb26c37e4c9349</anchor>
      <arglist>(const Teuchos::ParameterList &amp;list, const std::string &amp;type)</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Teuchos::ParameterList &gt;</type>
      <name>invFactoryValidParameters</name>
      <anchorfile>classTeko_1_1InverseFactory.html</anchorfile>
      <anchor>a2870ecba9d6dd60d92f0d3b2fc4a23b2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>InverseLinearOp</type>
      <name>buildInverse</name>
      <anchorfile>classTeko_1_1InverseFactory.html</anchorfile>
      <anchor>af2c1187cec72755642ac093b1e1b0c62</anchor>
      <arglist>(const InverseFactory &amp;factory, const LinearOp &amp;A)</arglist>
    </member>
    <member kind="function">
      <type>InverseLinearOp</type>
      <name>buildInverse</name>
      <anchorfile>classTeko_1_1InverseFactory.html</anchorfile>
      <anchor>a9f04aba1c3754f725507ae355352bb22</anchor>
      <arglist>(const InverseFactory &amp;factory, const LinearOp &amp;A, const LinearOp &amp;precOp)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>rebuildInverse</name>
      <anchorfile>classTeko_1_1InverseFactory.html</anchorfile>
      <anchor>a38dbd59742785c3fbcb240eb101733ea</anchor>
      <arglist>(const InverseFactory &amp;factory, const LinearOp &amp;A, InverseLinearOp &amp;invA)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>rebuildInverse</name>
      <anchorfile>classTeko_1_1InverseFactory.html</anchorfile>
      <anchor>a986d5b512c8f5a195c9e365616a9fa8d</anchor>
      <arglist>(const InverseFactory &amp;factory, const LinearOp &amp;A, const LinearOp &amp;precOp, InverseLinearOp &amp;invA)</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; InverseFactory &gt;</type>
      <name>invFactoryFromParamList</name>
      <anchorfile>classTeko_1_1InverseFactory.html</anchorfile>
      <anchor>aaf54f451a81de60ae7fb26c37e4c9349</anchor>
      <arglist>(const Teuchos::ParameterList &amp;list, const std::string &amp;type)</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Teuchos::ParameterList &gt;</type>
      <name>invFactoryValidParameters</name>
      <anchorfile>classTeko_1_1InverseFactory.html</anchorfile>
      <anchor>a2870ecba9d6dd60d92f0d3b2fc4a23b2</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Teko::Epetra::InverseFactoryOperator</name>
    <filename>classTeko_1_1Epetra_1_1InverseFactoryOperator.html</filename>
    <member kind="function">
      <type></type>
      <name>InverseFactoryOperator</name>
      <anchorfile>classTeko_1_1Epetra_1_1InverseFactoryOperator.html</anchorfile>
      <anchor>a13c04848226b2a67cbedcfe1ba8db30e</anchor>
      <arglist>(const Teuchos::RCP&lt; const InverseFactory &gt; &amp;bfp)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>initInverse</name>
      <anchorfile>classTeko_1_1Epetra_1_1InverseFactoryOperator.html</anchorfile>
      <anchor>a75a33c558b233916fd327623de27492d</anchor>
      <arglist>(bool clearOld=false)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>buildInverseOperator</name>
      <anchorfile>classTeko_1_1Epetra_1_1InverseFactoryOperator.html</anchorfile>
      <anchor>a111fbe12b0315ca13c9bc868d35ef4b4</anchor>
      <arglist>(const Teuchos::RCP&lt; const Epetra_Operator &gt; &amp;A, bool clear=true)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>buildInverseOperator</name>
      <anchorfile>classTeko_1_1Epetra_1_1InverseFactoryOperator.html</anchorfile>
      <anchor>a278125ef038d59e66635072e8c73110d</anchor>
      <arglist>(const Teuchos::RCP&lt; Epetra_Operator &gt; &amp;A, bool clear=true)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>rebuildInverseOperator</name>
      <anchorfile>classTeko_1_1Epetra_1_1InverseFactoryOperator.html</anchorfile>
      <anchor>aad69a420a079d299026d1a46c387fac7</anchor>
      <arglist>(const Teuchos::RCP&lt; const Epetra_Operator &gt; &amp;A)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>rebuildInverseOperator</name>
      <anchorfile>classTeko_1_1Epetra_1_1InverseFactoryOperator.html</anchorfile>
      <anchor>a377cd4e978eaae79a61d012c1edcef0d</anchor>
      <arglist>(const Teuchos::RCP&lt; Epetra_Operator &gt; &amp;A)</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Epetra_Operator &gt;</type>
      <name>getForwardOp</name>
      <anchorfile>classTeko_1_1Epetra_1_1InverseFactoryOperator.html</anchorfile>
      <anchor>a47ea9d07413cfcfa48ed2298eb01e968</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; Epetra_Operator &gt;</type>
      <name>getNonconstForwardOp</name>
      <anchorfile>classTeko_1_1Epetra_1_1InverseFactoryOperator.html</anchorfile>
      <anchor>a82f3f7c9dbbf7ec56cd9de3c014d8ed5</anchor>
      <arglist>() const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Teko::TpetraHelpers::InverseFactoryOperator</name>
    <filename>classTeko_1_1TpetraHelpers_1_1InverseFactoryOperator.html</filename>
    <member kind="function">
      <type></type>
      <name>InverseFactoryOperator</name>
      <anchorfile>classTeko_1_1TpetraHelpers_1_1InverseFactoryOperator.html</anchorfile>
      <anchor>a570edb941a0780c1074565ab005a2c9a</anchor>
      <arglist>(const Teuchos::RCP&lt; const InverseFactory &gt; &amp;bfp)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>initInverse</name>
      <anchorfile>classTeko_1_1TpetraHelpers_1_1InverseFactoryOperator.html</anchorfile>
      <anchor>ac43af663e48a78181c2859a34f8b0118</anchor>
      <arglist>(bool clearOld=false)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>buildInverseOperator</name>
      <anchorfile>classTeko_1_1TpetraHelpers_1_1InverseFactoryOperator.html</anchorfile>
      <anchor>a2a032a0645de1f6195f8016f9a13632a</anchor>
      <arglist>(const Teuchos::RCP&lt; const Tpetra::Operator&lt; ST, LO, GO, NT &gt; &gt; &amp;A, bool clear=true)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>buildInverseOperator</name>
      <anchorfile>classTeko_1_1TpetraHelpers_1_1InverseFactoryOperator.html</anchorfile>
      <anchor>aa31086e47aa50dd2e34f6b013a471d42</anchor>
      <arglist>(const Teuchos::RCP&lt; Tpetra::Operator&lt; ST, LO, GO, NT &gt; &gt; &amp;A, bool clear=true)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>rebuildInverseOperator</name>
      <anchorfile>classTeko_1_1TpetraHelpers_1_1InverseFactoryOperator.html</anchorfile>
      <anchor>a7c16db8f6af46a81d8d35920a96da85d</anchor>
      <arglist>(const Teuchos::RCP&lt; const Tpetra::Operator&lt; ST, LO, GO, NT &gt; &gt; &amp;A)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>rebuildInverseOperator</name>
      <anchorfile>classTeko_1_1TpetraHelpers_1_1InverseFactoryOperator.html</anchorfile>
      <anchor>a127d671b44af4bfa4ebc5b6fb7869a86</anchor>
      <arglist>(const Teuchos::RCP&lt; Tpetra::Operator&lt; ST, LO, GO, NT &gt; &gt; &amp;A)</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Tpetra::Operator&lt; ST, LO, GO, NT &gt; &gt;</type>
      <name>getForwardOp</name>
      <anchorfile>classTeko_1_1TpetraHelpers_1_1InverseFactoryOperator.html</anchorfile>
      <anchor>a0231d47dae3786c8e2a5d26c1b023a80</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; Tpetra::Operator&lt; ST, LO, GO, NT &gt; &gt;</type>
      <name>getNonconstForwardOp</name>
      <anchorfile>classTeko_1_1TpetraHelpers_1_1InverseFactoryOperator.html</anchorfile>
      <anchor>a23d2cef002dc649ef96ed6fac1c6c102</anchor>
      <arglist>() const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Teko::Epetra::InverseMappingStrategy</name>
    <filename>classTeko_1_1Epetra_1_1InverseMappingStrategy.html</filename>
    <base>Teko::Epetra::MappingStrategy</base>
    <member kind="function">
      <type></type>
      <name>InverseMappingStrategy</name>
      <anchorfile>classTeko_1_1Epetra_1_1InverseMappingStrategy.html</anchorfile>
      <anchor>a0214ea02d914ca63dd13554597a84704</anchor>
      <arglist>(const RCP&lt; const MappingStrategy &gt; &amp;forward)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>copyEpetraIntoThyra</name>
      <anchorfile>classTeko_1_1Epetra_1_1InverseMappingStrategy.html</anchorfile>
      <anchor>ae0b242602cbb7bd00f123e9a3ac3d631</anchor>
      <arglist>(const Epetra_MultiVector &amp;epetraX, const Teuchos::Ptr&lt; Thyra::MultiVectorBase&lt; double &gt; &gt; &amp;thyraX) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>copyThyraIntoEpetra</name>
      <anchorfile>classTeko_1_1Epetra_1_1InverseMappingStrategy.html</anchorfile>
      <anchor>a77e53d8b1bb80461b109893d5c63034d</anchor>
      <arglist>(const RCP&lt; const Thyra::MultiVectorBase&lt; double &gt; &gt; &amp;thyraX, Epetra_MultiVector &amp;epetraX) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const RCP&lt; const Epetra_Map &gt;</type>
      <name>domainMap</name>
      <anchorfile>classTeko_1_1Epetra_1_1InverseMappingStrategy.html</anchorfile>
      <anchor>a08cb59cacab0ad55fa8a3ba6c658e79b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const RCP&lt; const Epetra_Map &gt;</type>
      <name>rangeMap</name>
      <anchorfile>classTeko_1_1Epetra_1_1InverseMappingStrategy.html</anchorfile>
      <anchor>a0750d98d33e14a1492cc6474e4344e61</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual std::string</type>
      <name>toString</name>
      <anchorfile>classTeko_1_1Epetra_1_1InverseMappingStrategy.html</anchorfile>
      <anchor>a532424278e397abdb9bc9477ea82c2f1</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>const RCP&lt; const MappingStrategy &gt;</type>
      <name>forwardStrategy_</name>
      <anchorfile>classTeko_1_1Epetra_1_1InverseMappingStrategy.html</anchorfile>
      <anchor>a178f7acfc0d5855de840d313a8d3dd98</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Teko::TpetraHelpers::InverseMappingStrategy</name>
    <filename>classTeko_1_1TpetraHelpers_1_1InverseMappingStrategy.html</filename>
    <base>Teko::TpetraHelpers::MappingStrategy</base>
    <member kind="function">
      <type></type>
      <name>InverseMappingStrategy</name>
      <anchorfile>classTeko_1_1TpetraHelpers_1_1InverseMappingStrategy.html</anchorfile>
      <anchor>ab46c8ebe242e6079291ffc04233cb7ed</anchor>
      <arglist>(const RCP&lt; const MappingStrategy &gt; &amp;forward)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>copyTpetraIntoThyra</name>
      <anchorfile>classTeko_1_1TpetraHelpers_1_1InverseMappingStrategy.html</anchorfile>
      <anchor>a2b2b46964b17e9f11d0e82bf61f08994</anchor>
      <arglist>(const Tpetra::MultiVector&lt; ST, LO, GO, NT &gt; &amp;tpetraX, const Teuchos::Ptr&lt; Thyra::MultiVectorBase&lt; ST &gt; &gt; &amp;thyraX) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>copyThyraIntoTpetra</name>
      <anchorfile>classTeko_1_1TpetraHelpers_1_1InverseMappingStrategy.html</anchorfile>
      <anchor>ab3e4a58d4da6f3fa36434603306fca0a</anchor>
      <arglist>(const RCP&lt; const Thyra::MultiVectorBase&lt; ST &gt; &gt; &amp;thyraX, Tpetra::MultiVector&lt; ST, LO, GO, NT &gt; &amp;tpetraX) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const RCP&lt; const Tpetra::Map&lt; LO, GO, NT &gt; &gt;</type>
      <name>domainMap</name>
      <anchorfile>classTeko_1_1TpetraHelpers_1_1InverseMappingStrategy.html</anchorfile>
      <anchor>a77adda5b328cb72029fa1db90b5c8a87</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const RCP&lt; const Tpetra::Map&lt; LO, GO, NT &gt; &gt;</type>
      <name>rangeMap</name>
      <anchorfile>classTeko_1_1TpetraHelpers_1_1InverseMappingStrategy.html</anchorfile>
      <anchor>a8f5eb2b39049b3eff494cf5a795263f1</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual std::string</type>
      <name>toString</name>
      <anchorfile>classTeko_1_1TpetraHelpers_1_1InverseMappingStrategy.html</anchorfile>
      <anchor>acc730d6ddd1acca7758338fe9932b331</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>const RCP&lt; const MappingStrategy &gt;</type>
      <name>forwardStrategy_</name>
      <anchorfile>classTeko_1_1TpetraHelpers_1_1InverseMappingStrategy.html</anchorfile>
      <anchor>aa15e62075ebd65e614dc0255cd7524ed</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Teko::InvFactoryDiagStrategy</name>
    <filename>classTeko_1_1InvFactoryDiagStrategy.html</filename>
    <base>Teko::BlockInvDiagonalStrategy</base>
    <member kind="function">
      <type></type>
      <name>InvFactoryDiagStrategy</name>
      <anchorfile>classTeko_1_1InvFactoryDiagStrategy.html</anchorfile>
      <anchor>a4677ad4a6629d03d0a67aa770f2a751f</anchor>
      <arglist>(const Teuchos::RCP&lt; InverseFactory &gt; &amp;factory)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>InvFactoryDiagStrategy</name>
      <anchorfile>classTeko_1_1InvFactoryDiagStrategy.html</anchorfile>
      <anchor>aae9c2450e926906c15f7b477ae5a4acc</anchor>
      <arglist>(const std::vector&lt; Teuchos::RCP&lt; InverseFactory &gt; &gt; &amp;factories, const Teuchos::RCP&lt; InverseFactory &gt; &amp;defaultFact=Teuchos::null)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>getInvD</name>
      <anchorfile>classTeko_1_1InvFactoryDiagStrategy.html</anchorfile>
      <anchor>a8894ae410b562390fde01d1a54521350</anchor>
      <arglist>(const BlockedLinearOp &amp;A, BlockPreconditionerState &amp;state, std::vector&lt; LinearOp &gt; &amp;invDiag) const </arglist>
    </member>
    <member kind="function">
      <type>const std::vector&lt; Teuchos::RCP&lt; InverseFactory &gt; &gt; &amp;</type>
      <name>getFactories</name>
      <anchorfile>classTeko_1_1InvFactoryDiagStrategy.html</anchorfile>
      <anchor>a2236e0e191bc124867677e414ef40faf</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>LinearOp</type>
      <name>buildInverse</name>
      <anchorfile>classTeko_1_1InvFactoryDiagStrategy.html</anchorfile>
      <anchor>aff7a5dba91136225fd8fbb2ce68b74b2</anchor>
      <arglist>(const InverseFactory &amp;invFact, const LinearOp &amp;matrix, BlockPreconditionerState &amp;state, const std::string &amp;opPrefix, int i) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Teko::NS::InvLSCStrategy</name>
    <filename>classTeko_1_1NS_1_1InvLSCStrategy.html</filename>
    <base>Teko::NS::LSCStrategy</base>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>setPressureStabMatrix</name>
      <anchorfile>classTeko_1_1NS_1_1InvLSCStrategy.html</anchorfile>
      <anchor>ae96a95c4d55faa5982275046fa8fc280</anchor>
      <arglist>(const Teko::LinearOp &amp;psm)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>initializeState</name>
      <anchorfile>classTeko_1_1NS_1_1InvLSCStrategy.html</anchorfile>
      <anchor>a3ab058bec4e28fd4bf68f1d520e5d7ef</anchor>
      <arglist>(const BlockedLinearOp &amp;A, LSCPrecondState *state) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>computeInverses</name>
      <anchorfile>classTeko_1_1NS_1_1InvLSCStrategy.html</anchorfile>
      <anchor>a400731f77c2c76d6c2e954ef3682d6fa</anchor>
      <arglist>(const BlockedLinearOp &amp;A, LSCPrecondState *state) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>setEigSolveParam</name>
      <anchorfile>classTeko_1_1NS_1_1InvLSCStrategy.html</anchorfile>
      <anchor>a9369f322ab4d7acc1995a64e84d387bd</anchor>
      <arglist>(int sz)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>getEigSolveParam</name>
      <anchorfile>classTeko_1_1NS_1_1InvLSCStrategy.html</anchorfile>
      <anchor>aa5150a157d5a917ad7b9da7cf2a275ef</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>setUseFullLDU</name>
      <anchorfile>classTeko_1_1NS_1_1InvLSCStrategy.html</anchorfile>
      <anchor>a8881c84016e0a85a916dbd83a8c6acc3</anchor>
      <arglist>(bool val)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>setRowZeroing</name>
      <anchorfile>classTeko_1_1NS_1_1InvLSCStrategy.html</anchorfile>
      <anchor>acd02a09724f0aa83facf9f072994baf1</anchor>
      <arglist>(bool val)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>setMassMatrix</name>
      <anchorfile>classTeko_1_1NS_1_1InvLSCStrategy.html</anchorfile>
      <anchor>a7297042e8fc1643b3eadc21ec13544ad</anchor>
      <arglist>(const LinearOp &amp;mass)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>setHScaling</name>
      <anchorfile>classTeko_1_1NS_1_1InvLSCStrategy.html</anchorfile>
      <anchor>ad3cb6c7eecd3060a34284738729839e4</anchor>
      <arglist>(const LinearOp &amp;hScaling)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>setHScaling</name>
      <anchorfile>classTeko_1_1NS_1_1InvLSCStrategy.html</anchorfile>
      <anchor>a32196f52ec08a0b9e74fda7433c0057b</anchor>
      <arglist>(const MultiVector &amp;hScaling)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>setWScaling</name>
      <anchorfile>classTeko_1_1NS_1_1InvLSCStrategy.html</anchorfile>
      <anchor>a8db387811be1d688d89448534ca5f72e</anchor>
      <arglist>(const MultiVector &amp;wScaling)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>buildState</name>
      <anchorfile>classTeko_1_1NS_1_1InvLSCStrategy.html</anchorfile>
      <anchor>a0a819dfc7c09a8b10ba8397250b6d1be</anchor>
      <arglist>(BlockedLinearOp &amp;A, BlockPreconditionerState &amp;state) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual LinearOp</type>
      <name>getInvBQBt</name>
      <anchorfile>classTeko_1_1NS_1_1InvLSCStrategy.html</anchorfile>
      <anchor>a4ec92e1186229da667aff7400c9d364d</anchor>
      <arglist>(const BlockedLinearOp &amp;A, BlockPreconditionerState &amp;state) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual LinearOp</type>
      <name>getInvBHBt</name>
      <anchorfile>classTeko_1_1NS_1_1InvLSCStrategy.html</anchorfile>
      <anchor>aceba8d765d65064a39e996ef04bd0c4f</anchor>
      <arglist>(const BlockedLinearOp &amp;A, BlockPreconditionerState &amp;state) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual LinearOp</type>
      <name>getInvF</name>
      <anchorfile>classTeko_1_1NS_1_1InvLSCStrategy.html</anchorfile>
      <anchor>a74b9e9e2173381a0fee2111c249015c8</anchor>
      <arglist>(const BlockedLinearOp &amp;A, BlockPreconditionerState &amp;state) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual LinearOp</type>
      <name>getOuterStabilization</name>
      <anchorfile>classTeko_1_1NS_1_1InvLSCStrategy.html</anchorfile>
      <anchor>a029b4dc918a16e20048ab5a13f0e1a8c</anchor>
      <arglist>(const BlockedLinearOp &amp;A, BlockPreconditionerState &amp;state) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual LinearOp</type>
      <name>getInnerStabilization</name>
      <anchorfile>classTeko_1_1NS_1_1InvLSCStrategy.html</anchorfile>
      <anchor>ac6480fb6d1ad154e335ffb1c4be06e90</anchor>
      <arglist>(const BlockedLinearOp &amp;A, BlockPreconditionerState &amp;state) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual LinearOp</type>
      <name>getInvMass</name>
      <anchorfile>classTeko_1_1NS_1_1InvLSCStrategy.html</anchorfile>
      <anchor>ac75757d2adeb999dda726db3bbc7cd92</anchor>
      <arglist>(const BlockedLinearOp &amp;A, BlockPreconditionerState &amp;state) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual LinearOp</type>
      <name>getHScaling</name>
      <anchorfile>classTeko_1_1NS_1_1InvLSCStrategy.html</anchorfile>
      <anchor>ab355b94f91bc28a3e84e7e7463aec913</anchor>
      <arglist>(const BlockedLinearOp &amp;A, BlockPreconditionerState &amp;state) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>useFullLDU</name>
      <anchorfile>classTeko_1_1NS_1_1InvLSCStrategy.html</anchorfile>
      <anchor>a54dcad9631f6e3230dfe53eafe329e5e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>setSymmetric</name>
      <anchorfile>classTeko_1_1NS_1_1InvLSCStrategy.html</anchorfile>
      <anchor>a6f18a31726ebc0fdd61177a1bd033ce5</anchor>
      <arglist>(bool isSymmetric)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>initializeFromParameterList</name>
      <anchorfile>classTeko_1_1NS_1_1InvLSCStrategy.html</anchorfile>
      <anchor>a460029fecdc78d90097d4861de16b346</anchor>
      <arglist>(const Teuchos::ParameterList &amp;pl, const InverseLibrary &amp;invLib)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual Teuchos::RCP&lt; Teuchos::ParameterList &gt;</type>
      <name>getRequestedParameters</name>
      <anchorfile>classTeko_1_1NS_1_1InvLSCStrategy.html</anchorfile>
      <anchor>a25c272bfbe2ac7ca49ac42503cc4be29</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>updateRequestedParameters</name>
      <anchorfile>classTeko_1_1NS_1_1InvLSCStrategy.html</anchorfile>
      <anchor>aa9fd07a79f7a6890720fb80823f2ae84</anchor>
      <arglist>(const Teuchos::ParameterList &amp;pl)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>buildState</name>
      <anchorfile>classTeko_1_1NS_1_1InvLSCStrategy.html</anchorfile>
      <anchor>a0a819dfc7c09a8b10ba8397250b6d1be</anchor>
      <arglist>(BlockedLinearOp &amp;A, BlockPreconditionerState &amp;state) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual LinearOp</type>
      <name>getInvBQBt</name>
      <anchorfile>classTeko_1_1NS_1_1InvLSCStrategy.html</anchorfile>
      <anchor>a4ec92e1186229da667aff7400c9d364d</anchor>
      <arglist>(const BlockedLinearOp &amp;A, BlockPreconditionerState &amp;state) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual LinearOp</type>
      <name>getInvBHBt</name>
      <anchorfile>classTeko_1_1NS_1_1InvLSCStrategy.html</anchorfile>
      <anchor>aceba8d765d65064a39e996ef04bd0c4f</anchor>
      <arglist>(const BlockedLinearOp &amp;A, BlockPreconditionerState &amp;state) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual LinearOp</type>
      <name>getInvF</name>
      <anchorfile>classTeko_1_1NS_1_1InvLSCStrategy.html</anchorfile>
      <anchor>a74b9e9e2173381a0fee2111c249015c8</anchor>
      <arglist>(const BlockedLinearOp &amp;A, BlockPreconditionerState &amp;state) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual LinearOp</type>
      <name>getOuterStabilization</name>
      <anchorfile>classTeko_1_1NS_1_1InvLSCStrategy.html</anchorfile>
      <anchor>a029b4dc918a16e20048ab5a13f0e1a8c</anchor>
      <arglist>(const BlockedLinearOp &amp;A, BlockPreconditionerState &amp;state) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual LinearOp</type>
      <name>getInnerStabilization</name>
      <anchorfile>classTeko_1_1NS_1_1InvLSCStrategy.html</anchorfile>
      <anchor>ac6480fb6d1ad154e335ffb1c4be06e90</anchor>
      <arglist>(const BlockedLinearOp &amp;A, BlockPreconditionerState &amp;state) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual LinearOp</type>
      <name>getInvMass</name>
      <anchorfile>classTeko_1_1NS_1_1InvLSCStrategy.html</anchorfile>
      <anchor>ac75757d2adeb999dda726db3bbc7cd92</anchor>
      <arglist>(const BlockedLinearOp &amp;A, BlockPreconditionerState &amp;state) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual LinearOp</type>
      <name>getHScaling</name>
      <anchorfile>classTeko_1_1NS_1_1InvLSCStrategy.html</anchorfile>
      <anchor>ab355b94f91bc28a3e84e7e7463aec913</anchor>
      <arglist>(const BlockedLinearOp &amp;A, BlockPreconditionerState &amp;state) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>useFullLDU</name>
      <anchorfile>classTeko_1_1NS_1_1InvLSCStrategy.html</anchorfile>
      <anchor>a54dcad9631f6e3230dfe53eafe329e5e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>setSymmetric</name>
      <anchorfile>classTeko_1_1NS_1_1InvLSCStrategy.html</anchorfile>
      <anchor>a6f18a31726ebc0fdd61177a1bd033ce5</anchor>
      <arglist>(bool isSymmetric)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>initializeFromParameterList</name>
      <anchorfile>classTeko_1_1NS_1_1InvLSCStrategy.html</anchorfile>
      <anchor>a460029fecdc78d90097d4861de16b346</anchor>
      <arglist>(const Teuchos::ParameterList &amp;pl, const InverseLibrary &amp;invLib)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual Teuchos::RCP&lt; Teuchos::ParameterList &gt;</type>
      <name>getRequestedParameters</name>
      <anchorfile>classTeko_1_1NS_1_1InvLSCStrategy.html</anchorfile>
      <anchor>a25c272bfbe2ac7ca49ac42503cc4be29</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>updateRequestedParameters</name>
      <anchorfile>classTeko_1_1NS_1_1InvLSCStrategy.html</anchorfile>
      <anchor>aa9fd07a79f7a6890720fb80823f2ae84</anchor>
      <arglist>(const Teuchos::ParameterList &amp;pl)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Teko::IterativePreconditionerFactory</name>
    <filename>classTeko_1_1IterativePreconditionerFactory.html</filename>
    <base virtualness="virtual">Teko::PreconditionerFactory</base>
    <member kind="function">
      <type></type>
      <name>IterativePreconditionerFactory</name>
      <anchorfile>classTeko_1_1IterativePreconditionerFactory.html</anchorfile>
      <anchor>adf7feb5a9a0240d9cc5f39e64797a0d6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>IterativePreconditionerFactory</name>
      <anchorfile>classTeko_1_1IterativePreconditionerFactory.html</anchorfile>
      <anchor>ac261a3641b2499565eadbba6a5378f08</anchor>
      <arglist>(unsigned int correctionNum, const Teuchos::RCP&lt; Teko::InverseFactory &gt; &amp;precFactory)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>IterativePreconditionerFactory</name>
      <anchorfile>classTeko_1_1IterativePreconditionerFactory.html</anchorfile>
      <anchor>ac270891e975730562687265c583ba4a2</anchor>
      <arglist>(unsigned int correctionNum, const Teuchos::RCP&lt; Teko::PreconditionerFactory &gt; &amp;precFactory)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual LinearOp</type>
      <name>buildPreconditionerOperator</name>
      <anchorfile>classTeko_1_1IterativePreconditionerFactory.html</anchorfile>
      <anchor>af2c97ef6b27be9a405ec498f98f651db</anchor>
      <arglist>(LinearOp &amp;lo, PreconditionerState &amp;state) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>initializeFromParameterList</name>
      <anchorfile>classTeko_1_1IterativePreconditionerFactory.html</anchorfile>
      <anchor>a886124edef9256707fd8a8e316a5cfba</anchor>
      <arglist>(const Teuchos::ParameterList &amp;settings)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual Teuchos::RCP&lt; Teuchos::ParameterList &gt;</type>
      <name>getRequestedParameters</name>
      <anchorfile>classTeko_1_1IterativePreconditionerFactory.html</anchorfile>
      <anchor>a428847855fc07bcc6b27dfe691a6b748</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>updateRequestedParameters</name>
      <anchorfile>classTeko_1_1IterativePreconditionerFactory.html</anchorfile>
      <anchor>a0e60a69c80c0c759e325f3cc69249cb0</anchor>
      <arglist>(const Teuchos::ParameterList &amp;pl)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>initializeFromParameterList</name>
      <anchorfile>classTeko_1_1IterativePreconditionerFactory.html</anchorfile>
      <anchor>a886124edef9256707fd8a8e316a5cfba</anchor>
      <arglist>(const Teuchos::ParameterList &amp;settings)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual Teuchos::RCP&lt; Teuchos::ParameterList &gt;</type>
      <name>getRequestedParameters</name>
      <anchorfile>classTeko_1_1IterativePreconditionerFactory.html</anchorfile>
      <anchor>a428847855fc07bcc6b27dfe691a6b748</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>updateRequestedParameters</name>
      <anchorfile>classTeko_1_1IterativePreconditionerFactory.html</anchorfile>
      <anchor>a0e60a69c80c0c759e325f3cc69249cb0</anchor>
      <arglist>(const Teuchos::ParameterList &amp;pl)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Teko::JacobiPreconditionerFactory</name>
    <filename>classTeko_1_1JacobiPreconditionerFactory.html</filename>
    <base>Teko::BlockPreconditionerFactory</base>
    <member kind="function">
      <type>LinearOp</type>
      <name>buildPreconditionerOperator</name>
      <anchorfile>classTeko_1_1JacobiPreconditionerFactory.html</anchorfile>
      <anchor>ac83c297c98007b0ebe9407ae07816104</anchor>
      <arglist>(BlockedLinearOp &amp;blo, BlockPreconditionerState &amp;state) const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const BlockInvDiagonalStrategy &gt;</type>
      <name>getInvDiagStrategy</name>
      <anchorfile>classTeko_1_1JacobiPreconditionerFactory.html</anchorfile>
      <anchor>afd6c372073709b85af83be21c9de6321</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>JacobiPreconditionerFactory</name>
      <anchorfile>classTeko_1_1JacobiPreconditionerFactory.html</anchorfile>
      <anchor>ab4dd075bd44c07d4a725498f30711f44</anchor>
      <arglist>(const LinearOp &amp;invD0, const LinearOp &amp;invD1)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>JacobiPreconditionerFactory</name>
      <anchorfile>classTeko_1_1JacobiPreconditionerFactory.html</anchorfile>
      <anchor>af99a296f8170205f65adc2a52f75f408</anchor>
      <arglist>(const RCP&lt; const BlockInvDiagonalStrategy &gt; &amp;strategy)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>JacobiPreconditionerFactory</name>
      <anchorfile>classTeko_1_1JacobiPreconditionerFactory.html</anchorfile>
      <anchor>a73e98c3ad317c780888df64781f27f5b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual void</type>
      <name>initializeFromParameterList</name>
      <anchorfile>classTeko_1_1JacobiPreconditionerFactory.html</anchorfile>
      <anchor>a089ea8139722c4df01b00642c4117e4b</anchor>
      <arglist>(const Teuchos::ParameterList &amp;pl)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>Teuchos::RCP&lt; const BlockInvDiagonalStrategy &gt;</type>
      <name>invOpsStrategy_</name>
      <anchorfile>classTeko_1_1JacobiPreconditionerFactory.html</anchorfile>
      <anchor>abc2610bc2eb189153085617d03b147b0</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>JacobiPreconditionerFactory</name>
      <anchorfile>classTeko_1_1JacobiPreconditionerFactory.html</anchorfile>
      <anchor>ab4dd075bd44c07d4a725498f30711f44</anchor>
      <arglist>(const LinearOp &amp;invD0, const LinearOp &amp;invD1)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>JacobiPreconditionerFactory</name>
      <anchorfile>classTeko_1_1JacobiPreconditionerFactory.html</anchorfile>
      <anchor>af99a296f8170205f65adc2a52f75f408</anchor>
      <arglist>(const RCP&lt; const BlockInvDiagonalStrategy &gt; &amp;strategy)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>JacobiPreconditionerFactory</name>
      <anchorfile>classTeko_1_1JacobiPreconditionerFactory.html</anchorfile>
      <anchor>a73e98c3ad317c780888df64781f27f5b</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Teko::NS::LSCPrecondState</name>
    <filename>classTeko_1_1NS_1_1LSCPrecondState.html</filename>
    <base>Teko::BlockPreconditionerState</base>
    <member kind="variable">
      <type>LinearOp</type>
      <name>invMass_</name>
      <anchorfile>classTeko_1_1NS_1_1LSCPrecondState.html</anchorfile>
      <anchor>a935851bd9c2896d529877d6490fcd495</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>ModifiableLinearOp</type>
      <name>BQBt_</name>
      <anchorfile>classTeko_1_1NS_1_1LSCPrecondState.html</anchorfile>
      <anchor>a88a5f200fa3bfa036e0e679d85895b53</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>ModifiableLinearOp</type>
      <name>BHBt_</name>
      <anchorfile>classTeko_1_1NS_1_1LSCPrecondState.html</anchorfile>
      <anchor>aef72c1359ddb88c1cab043e4836d82b5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>LinearOp</type>
      <name>BQBtmC_</name>
      <anchorfile>classTeko_1_1NS_1_1LSCPrecondState.html</anchorfile>
      <anchor>add755c1ce5daed62e18c95365f73a643</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>LinearOp</type>
      <name>BHBtmC_</name>
      <anchorfile>classTeko_1_1NS_1_1LSCPrecondState.html</anchorfile>
      <anchor>a6bfc2856914af084825eea4b9a3a3e3a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>LinearOp</type>
      <name>aiD_</name>
      <anchorfile>classTeko_1_1NS_1_1LSCPrecondState.html</anchorfile>
      <anchor>a9c862104efe73c628ee163df4fe28c80</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>double</type>
      <name>gamma_</name>
      <anchorfile>classTeko_1_1NS_1_1LSCPrecondState.html</anchorfile>
      <anchor>aeb81a0d69d21c779b74fa816e25fc45d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>double</type>
      <name>alpha_</name>
      <anchorfile>classTeko_1_1NS_1_1LSCPrecondState.html</anchorfile>
      <anchor>ab1f48dfb52ccbeb404b889b7ac8e8184</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Teko::NS::LSCSIMPLECStrategy</name>
    <filename>classTeko_1_1NS_1_1LSCSIMPLECStrategy.html</filename>
    <base>Teko::NS::LSCStrategy</base>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>buildState</name>
      <anchorfile>classTeko_1_1NS_1_1LSCSIMPLECStrategy.html</anchorfile>
      <anchor>a0c07b52ce3229c1b7805aef63a6f346d</anchor>
      <arglist>(BlockedLinearOp &amp;A, BlockPreconditionerState &amp;state) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual LinearOp</type>
      <name>getInvBQBt</name>
      <anchorfile>classTeko_1_1NS_1_1LSCSIMPLECStrategy.html</anchorfile>
      <anchor>a80f784d9823164109a7f3c4f2f454788</anchor>
      <arglist>(const BlockedLinearOp &amp;A, BlockPreconditionerState &amp;state) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual LinearOp</type>
      <name>getInvBHBt</name>
      <anchorfile>classTeko_1_1NS_1_1LSCSIMPLECStrategy.html</anchorfile>
      <anchor>a08a874de36555a1740164d1092981606</anchor>
      <arglist>(const BlockedLinearOp &amp;A, BlockPreconditionerState &amp;state) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual LinearOp</type>
      <name>getInvF</name>
      <anchorfile>classTeko_1_1NS_1_1LSCSIMPLECStrategy.html</anchorfile>
      <anchor>ae1271ad6897feabd9f16d856ab95dd34</anchor>
      <arglist>(const BlockedLinearOp &amp;A, BlockPreconditionerState &amp;state) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual LinearOp</type>
      <name>getOuterStabilization</name>
      <anchorfile>classTeko_1_1NS_1_1LSCSIMPLECStrategy.html</anchorfile>
      <anchor>a8df1f48af33d8dd63e487c062b07a695</anchor>
      <arglist>(const BlockedLinearOp &amp;A, BlockPreconditionerState &amp;state) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual LinearOp</type>
      <name>getInnerStabilization</name>
      <anchorfile>classTeko_1_1NS_1_1LSCSIMPLECStrategy.html</anchorfile>
      <anchor>a3a8ea96f5b1248b8938cddd59f49311f</anchor>
      <arglist>(const BlockedLinearOp &amp;A, BlockPreconditionerState &amp;state) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual LinearOp</type>
      <name>getInvMass</name>
      <anchorfile>classTeko_1_1NS_1_1LSCSIMPLECStrategy.html</anchorfile>
      <anchor>ad9429035531dcd9617b5aa9f0b82fc5d</anchor>
      <arglist>(const BlockedLinearOp &amp;A, BlockPreconditionerState &amp;state) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual LinearOp</type>
      <name>getHScaling</name>
      <anchorfile>classTeko_1_1NS_1_1LSCSIMPLECStrategy.html</anchorfile>
      <anchor>a46e9b943efa0ba9277c7cfdebb2d8c62</anchor>
      <arglist>(const BlockedLinearOp &amp;A, BlockPreconditionerState &amp;state) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>useFullLDU</name>
      <anchorfile>classTeko_1_1NS_1_1LSCSIMPLECStrategy.html</anchorfile>
      <anchor>a9c8d5310b70983ef3805e23ee866f6a5</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>initializeFromParameterList</name>
      <anchorfile>classTeko_1_1NS_1_1LSCSIMPLECStrategy.html</anchorfile>
      <anchor>a65dca38594a9788c7bcb7769c9c78461</anchor>
      <arglist>(const Teuchos::ParameterList &amp;pl, const InverseLibrary &amp;invLib)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>initializeState</name>
      <anchorfile>classTeko_1_1NS_1_1LSCSIMPLECStrategy.html</anchorfile>
      <anchor>a8c3c3ff6d0a2f7c04bf2482d20c2fdfe</anchor>
      <arglist>(const BlockedLinearOp &amp;A, LSCPrecondState *state) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>computeInverses</name>
      <anchorfile>classTeko_1_1NS_1_1LSCSIMPLECStrategy.html</anchorfile>
      <anchor>ada7bc78df7494f77181d1e399b269744</anchor>
      <arglist>(const BlockedLinearOp &amp;A, LSCPrecondState *state) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>setUseFullLDU</name>
      <anchorfile>classTeko_1_1NS_1_1LSCSIMPLECStrategy.html</anchorfile>
      <anchor>ac2e67a071f8a09eb86eb1c47d853b85b</anchor>
      <arglist>(bool val)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>setSymmetric</name>
      <anchorfile>classTeko_1_1NS_1_1LSCSIMPLECStrategy.html</anchorfile>
      <anchor>ab3d64779823740900251f5ec729c5527</anchor>
      <arglist>(bool isSymmetric)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Teko::NS::LSCStrategy</name>
    <filename>classTeko_1_1NS_1_1LSCStrategy.html</filename>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>buildState</name>
      <anchorfile>classTeko_1_1NS_1_1LSCStrategy.html</anchorfile>
      <anchor>ab213146eeb05b9658531d43ad8158a17</anchor>
      <arglist>(BlockedLinearOp &amp;A, BlockPreconditionerState &amp;state) const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual LinearOp</type>
      <name>getInvBQBt</name>
      <anchorfile>classTeko_1_1NS_1_1LSCStrategy.html</anchorfile>
      <anchor>a67dd36063cb09a602f8941b2a769dbd8</anchor>
      <arglist>(const BlockedLinearOp &amp;A, BlockPreconditionerState &amp;state) const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual LinearOp</type>
      <name>getInvBHBt</name>
      <anchorfile>classTeko_1_1NS_1_1LSCStrategy.html</anchorfile>
      <anchor>af9aafc51e9c69c2daeaee25b8899f28f</anchor>
      <arglist>(const BlockedLinearOp &amp;A, BlockPreconditionerState &amp;state) const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual LinearOp</type>
      <name>getInvF</name>
      <anchorfile>classTeko_1_1NS_1_1LSCStrategy.html</anchorfile>
      <anchor>acd7217fc66ec5c0978310ddbe8356ba6</anchor>
      <arglist>(const BlockedLinearOp &amp;A, BlockPreconditionerState &amp;state) const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual LinearOp</type>
      <name>getOuterStabilization</name>
      <anchorfile>classTeko_1_1NS_1_1LSCStrategy.html</anchorfile>
      <anchor>a54277aae1608fe618c99c254b4ea1c07</anchor>
      <arglist>(const BlockedLinearOp &amp;A, BlockPreconditionerState &amp;state) const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual LinearOp</type>
      <name>getInnerStabilization</name>
      <anchorfile>classTeko_1_1NS_1_1LSCStrategy.html</anchorfile>
      <anchor>ac79d9e775c76e703f0e48363ca710864</anchor>
      <arglist>(const BlockedLinearOp &amp;A, BlockPreconditionerState &amp;state) const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual LinearOp</type>
      <name>getInvMass</name>
      <anchorfile>classTeko_1_1NS_1_1LSCStrategy.html</anchorfile>
      <anchor>accedc87db913cb124a319ac7362b9c46</anchor>
      <arglist>(const BlockedLinearOp &amp;A, BlockPreconditionerState &amp;state) const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual LinearOp</type>
      <name>getHScaling</name>
      <anchorfile>classTeko_1_1NS_1_1LSCStrategy.html</anchorfile>
      <anchor>a269dd30a732d4be80ad96d950ec31c1a</anchor>
      <arglist>(const BlockedLinearOp &amp;A, BlockPreconditionerState &amp;state) const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>useFullLDU</name>
      <anchorfile>classTeko_1_1NS_1_1LSCStrategy.html</anchorfile>
      <anchor>a874753f73a777a3a5f1b642672f476d7</anchor>
      <arglist>() const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>setSymmetric</name>
      <anchorfile>classTeko_1_1NS_1_1LSCStrategy.html</anchorfile>
      <anchor>ae7c0051dfdf64b555d773715ff9d9201</anchor>
      <arglist>(bool isSymmetric)=0</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>initializeFromParameterList</name>
      <anchorfile>classTeko_1_1NS_1_1LSCStrategy.html</anchorfile>
      <anchor>a8bd1fa15b71d8ddf2722f905de50d4d0</anchor>
      <arglist>(const Teuchos::ParameterList &amp;pl, const InverseLibrary &amp;invLib)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual Teuchos::RCP&lt; Teuchos::ParameterList &gt;</type>
      <name>getRequestedParameters</name>
      <anchorfile>classTeko_1_1NS_1_1LSCStrategy.html</anchorfile>
      <anchor>a6ccbb56a31805f5134f7a58755b60c04</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>updateRequestedParameters</name>
      <anchorfile>classTeko_1_1NS_1_1LSCStrategy.html</anchorfile>
      <anchor>a2049f41c57dbc17a703593714f8c1ceb</anchor>
      <arglist>(const Teuchos::ParameterList &amp;pl)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setRequestHandler</name>
      <anchorfile>classTeko_1_1NS_1_1LSCStrategy.html</anchorfile>
      <anchor>a6519624982b3e49bf2217d836b262c40</anchor>
      <arglist>(const Teuchos::RCP&lt; RequestHandler &gt; &amp;rh)</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; RequestHandler &gt;</type>
      <name>getRequestHandler</name>
      <anchorfile>classTeko_1_1NS_1_1LSCStrategy.html</anchorfile>
      <anchor>a25fcf4e28270c296a7ec7ed98e19770a</anchor>
      <arglist>() const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Teko::LU2x2DiagonalStrategy</name>
    <filename>classTeko_1_1LU2x2DiagonalStrategy.html</filename>
    <base>Teko::LU2x2Strategy</base>
    <member kind="function">
      <type></type>
      <name>LU2x2DiagonalStrategy</name>
      <anchorfile>classTeko_1_1LU2x2DiagonalStrategy.html</anchorfile>
      <anchor>acb4aaa1ee21e152983544fa62c88960d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>LU2x2DiagonalStrategy</name>
      <anchorfile>classTeko_1_1LU2x2DiagonalStrategy.html</anchorfile>
      <anchor>a71c8400de814565808bdf16180f9a8e8</anchor>
      <arglist>(const Teuchos::RCP&lt; InverseFactory &gt; &amp;invFA, const Teuchos::RCP&lt; InverseFactory &gt; &amp;invS)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~LU2x2DiagonalStrategy</name>
      <anchorfile>classTeko_1_1LU2x2DiagonalStrategy.html</anchorfile>
      <anchor>a6067c4c6f3bd7c3307f76d17a1a02c5a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const Teko::LinearOp</type>
      <name>getHatInvA00</name>
      <anchorfile>classTeko_1_1LU2x2DiagonalStrategy.html</anchorfile>
      <anchor>a096dcd8fb1737048c2395675f315e491</anchor>
      <arglist>(const Teko::BlockedLinearOp &amp;A, BlockPreconditionerState &amp;state) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const Teko::LinearOp</type>
      <name>getTildeInvA00</name>
      <anchorfile>classTeko_1_1LU2x2DiagonalStrategy.html</anchorfile>
      <anchor>ac5e8b2c0f631d2179696fb314af85f7d</anchor>
      <arglist>(const Teko::BlockedLinearOp &amp;A, BlockPreconditionerState &amp;state) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const Teko::LinearOp</type>
      <name>getInvS</name>
      <anchorfile>classTeko_1_1LU2x2DiagonalStrategy.html</anchorfile>
      <anchor>a3fc5825b029da2c3555566c1b04bd851</anchor>
      <arglist>(const Teko::BlockedLinearOp &amp;A, BlockPreconditionerState &amp;state) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>initializeFromParameterList</name>
      <anchorfile>classTeko_1_1LU2x2DiagonalStrategy.html</anchorfile>
      <anchor>afa632c8988b92c810aaf6a5e1df15753</anchor>
      <arglist>(const Teuchos::ParameterList &amp;settings, const InverseLibrary &amp;invLib)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>initializeState</name>
      <anchorfile>classTeko_1_1LU2x2DiagonalStrategy.html</anchorfile>
      <anchor>a5a5aecfa2dc6dd10e7f50f1338ddb220</anchor>
      <arglist>(const Teko::BlockedLinearOp &amp;A, BlockPreconditionerState &amp;state) const </arglist>
    </member>
    <member kind="function" protection="protected" static="yes">
      <type>static void</type>
      <name>buildTimers</name>
      <anchorfile>classTeko_1_1LU2x2DiagonalStrategy.html</anchorfile>
      <anchor>a56735f8229afe4b9919578092d3b5fba</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Teko::LU2x2InverseOp</name>
    <filename>classTeko_1_1LU2x2InverseOp.html</filename>
    <base>Teko::BlockImplicitLinearOp</base>
    <member kind="function">
      <type></type>
      <name>LU2x2InverseOp</name>
      <anchorfile>classTeko_1_1LU2x2InverseOp.html</anchorfile>
      <anchor>acfb296028971f7c7c6ef31a58eab4a46</anchor>
      <arglist>(const BlockedLinearOp &amp;A, const LinearOp &amp;invA00, const LinearOp &amp;invS)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>LU2x2InverseOp</name>
      <anchorfile>classTeko_1_1LU2x2InverseOp.html</anchorfile>
      <anchor>a8e9c780e0bf433050674a253ff4e1108</anchor>
      <arglist>(const BlockedLinearOp &amp;A, const LinearOp &amp;hatInvA00, const LinearOp &amp;tildeInvA00, const LinearOp &amp;invS)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual VectorSpace</type>
      <name>range</name>
      <anchorfile>classTeko_1_1LU2x2InverseOp.html</anchorfile>
      <anchor>aea29fc6a59144f72e104debbb9a67ef6</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual VectorSpace</type>
      <name>domain</name>
      <anchorfile>classTeko_1_1LU2x2InverseOp.html</anchorfile>
      <anchor>a66d267a48a3d306757e3f72ddba9b6df</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>implicitApply</name>
      <anchorfile>classTeko_1_1LU2x2InverseOp.html</anchorfile>
      <anchor>a5b5febfe347e17177f9a4e1a218acad3</anchor>
      <arglist>(const BlockedMultiVector &amp;x, BlockedMultiVector &amp;y, const double alpha=1.0, const double beta=0.0) const </arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>const BlockedLinearOp</type>
      <name>A_</name>
      <anchorfile>classTeko_1_1LU2x2InverseOp.html</anchorfile>
      <anchor>af37e19db961f5e9a2295650de6183cc3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>const LinearOp</type>
      <name>hatInvA00_</name>
      <anchorfile>classTeko_1_1LU2x2InverseOp.html</anchorfile>
      <anchor>a25ca14325f8d0d4e2c8c366078d63e1f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>const LinearOp</type>
      <name>tildeInvA00_</name>
      <anchorfile>classTeko_1_1LU2x2InverseOp.html</anchorfile>
      <anchor>a5e2720d0392c8e4713b68478c715f8fe</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>const LinearOp</type>
      <name>invS_</name>
      <anchorfile>classTeko_1_1LU2x2InverseOp.html</anchorfile>
      <anchor>a8d739a1408b42a462cbfd5070e31bddc</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>const LinearOp</type>
      <name>A10_</name>
      <anchorfile>classTeko_1_1LU2x2InverseOp.html</anchorfile>
      <anchor>ac03a5296edb779fd919e22e5ae04d456</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>const LinearOp</type>
      <name>A01_</name>
      <anchorfile>classTeko_1_1LU2x2InverseOp.html</anchorfile>
      <anchor>ac02e807b9fecb9a550f7f199c92128fb</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>Teuchos::RCP&lt; const Thyra::ProductVectorSpaceBase&lt; double &gt; &gt;</type>
      <name>productRange_</name>
      <anchorfile>classTeko_1_1LU2x2InverseOp.html</anchorfile>
      <anchor>a73f4684bbac1638124fdb5c539161ad3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>Teuchos::RCP&lt; const Thyra::ProductVectorSpaceBase&lt; double &gt; &gt;</type>
      <name>productDomain_</name>
      <anchorfile>classTeko_1_1LU2x2InverseOp.html</anchorfile>
      <anchor>a6cd5da1ec14f415627f95c6ab8589699</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>ModifiableLinearOp</type>
      <name>createDiagnosticLinearOp</name>
      <anchorfile>classTeko_1_1LU2x2InverseOp.html</anchorfile>
      <anchor>a3e6f49a2f3fbb080f73ec7cf21748cc6</anchor>
      <arglist>(const Teuchos::RCP&lt; std::ostream &gt; &amp;os, const ModifiableLinearOp &amp;A, const std::string &amp;label)</arglist>
    </member>
    <member kind="function">
      <type>ModifiableLinearOp</type>
      <name>createDiagnosticLinearOp</name>
      <anchorfile>classTeko_1_1LU2x2InverseOp.html</anchorfile>
      <anchor>aa83cf37e87635d6de34db8e007dada78</anchor>
      <arglist>(const Teuchos::RCP&lt; std::ostream &gt; &amp;os, const LinearOp &amp;A, const std::string &amp;label)</arglist>
    </member>
    <member kind="function">
      <type>ModifiableLinearOp</type>
      <name>createDiagnosticLinearOp</name>
      <anchorfile>classTeko_1_1LU2x2InverseOp.html</anchorfile>
      <anchor>a7e01fe7148da4c50f51e60aaef0b12e6</anchor>
      <arglist>(const Teuchos::RCP&lt; std::ostream &gt; &amp;os, const Teko::LinearOp &amp;fwdOp, const ModifiableLinearOp &amp;A, const std::string &amp;label)</arglist>
    </member>
    <member kind="function">
      <type>LinearOp</type>
      <name>createLU2x2InverseOp</name>
      <anchorfile>classTeko_1_1LU2x2InverseOp.html</anchorfile>
      <anchor>a87c7c5979af37f1335c4c370cd76e43b</anchor>
      <arglist>(BlockedLinearOp &amp;A, LinearOp &amp;invA00, LinearOp &amp;invS)</arglist>
    </member>
    <member kind="function">
      <type>LinearOp</type>
      <name>createLU2x2InverseOp</name>
      <anchorfile>classTeko_1_1LU2x2InverseOp.html</anchorfile>
      <anchor>a2df26f6a73c9c7269fcd93d37b511908</anchor>
      <arglist>(BlockedLinearOp &amp;A, LinearOp &amp;invA00, LinearOp &amp;invS, const std::string &amp;str)</arglist>
    </member>
    <member kind="function">
      <type>LinearOp</type>
      <name>createLU2x2InverseOp</name>
      <anchorfile>classTeko_1_1LU2x2InverseOp.html</anchorfile>
      <anchor>a16efc0342197a63c831c52633979d4ba</anchor>
      <arglist>(BlockedLinearOp &amp;A, LinearOp &amp;hatInvA00, LinearOp &amp;tildeInvA00, LinearOp &amp;invS)</arglist>
    </member>
    <member kind="function">
      <type>LinearOp</type>
      <name>createLU2x2InverseOp</name>
      <anchorfile>classTeko_1_1LU2x2InverseOp.html</anchorfile>
      <anchor>a7f33d8d90de9fd869a9a43975790c042</anchor>
      <arglist>(BlockedLinearOp &amp;A, LinearOp &amp;hatInvA00, LinearOp &amp;tildeInvA00, LinearOp &amp;invS, const std::string &amp;str)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual VectorSpace</type>
      <name>range</name>
      <anchorfile>classTeko_1_1LU2x2InverseOp.html</anchorfile>
      <anchor>aea29fc6a59144f72e104debbb9a67ef6</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual VectorSpace</type>
      <name>domain</name>
      <anchorfile>classTeko_1_1LU2x2InverseOp.html</anchorfile>
      <anchor>a66d267a48a3d306757e3f72ddba9b6df</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>implicitApply</name>
      <anchorfile>classTeko_1_1LU2x2InverseOp.html</anchorfile>
      <anchor>a5b5febfe347e17177f9a4e1a218acad3</anchor>
      <arglist>(const BlockedMultiVector &amp;x, BlockedMultiVector &amp;y, const double alpha=1.0, const double beta=0.0) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Teko::LU2x2PreconditionerFactory</name>
    <filename>classTeko_1_1LU2x2PreconditionerFactory.html</filename>
    <base>Teko::BlockPreconditionerFactory</base>
    <member kind="function">
      <type>LinearOp</type>
      <name>buildPreconditionerOperator</name>
      <anchorfile>classTeko_1_1LU2x2PreconditionerFactory.html</anchorfile>
      <anchor>a8fb3327a2263d816020e4836c5b97bf7</anchor>
      <arglist>(BlockedLinearOp &amp;blo, BlockPreconditionerState &amp;state) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>initializeFromParameterList</name>
      <anchorfile>classTeko_1_1LU2x2PreconditionerFactory.html</anchorfile>
      <anchor>a0b22f6c741a810d0fedc895ef9fb7822</anchor>
      <arglist>(const Teuchos::ParameterList &amp;settings)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual Teuchos::RCP&lt; Teuchos::ParameterList &gt;</type>
      <name>getRequestedParameters</name>
      <anchorfile>classTeko_1_1LU2x2PreconditionerFactory.html</anchorfile>
      <anchor>a5ffa28e7f80f82b968f2e1f2c82d7077</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>updateRequestedParameters</name>
      <anchorfile>classTeko_1_1LU2x2PreconditionerFactory.html</anchorfile>
      <anchor>a7f17ad5b038fcc4171aa1fb26afd4163</anchor>
      <arglist>(const Teuchos::ParameterList &amp;pl)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>useFullLDU</name>
      <anchorfile>classTeko_1_1LU2x2PreconditionerFactory.html</anchorfile>
      <anchor>a93ca626ae2ebb768f918f8263064b58f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>setFullLDU</name>
      <anchorfile>classTeko_1_1LU2x2PreconditionerFactory.html</anchorfile>
      <anchor>a136734fdec61d5624ce3f61be71f3659</anchor>
      <arglist>(bool value)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>LU2x2PreconditionerFactory</name>
      <anchorfile>classTeko_1_1LU2x2PreconditionerFactory.html</anchorfile>
      <anchor>a95259e22bfdb573906ad86055914af89</anchor>
      <arglist>(LinearOp &amp;invA00, LinearOp &amp;invS)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>LU2x2PreconditionerFactory</name>
      <anchorfile>classTeko_1_1LU2x2PreconditionerFactory.html</anchorfile>
      <anchor>a4562d7d0691e0a678f38fffc4bd204fb</anchor>
      <arglist>(LinearOp &amp;hatInvA00, LinearOp &amp;tildeInvA00, LinearOp &amp;invS)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>LU2x2PreconditionerFactory</name>
      <anchorfile>classTeko_1_1LU2x2PreconditionerFactory.html</anchorfile>
      <anchor>a3e95b08681c46a21b807cfcfab17c912</anchor>
      <arglist>(const Teuchos::RCP&lt; LU2x2Strategy &gt; &amp;strategy)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>LU2x2PreconditionerFactory</name>
      <anchorfile>classTeko_1_1LU2x2PreconditionerFactory.html</anchorfile>
      <anchor>a03881e4a321048d411c68d3cc87dfa8f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static RCP&lt; LU2x2Strategy &gt;</type>
      <name>buildStrategy</name>
      <anchorfile>classTeko_1_1LU2x2PreconditionerFactory.html</anchorfile>
      <anchor>a8a231ef47ba4121d388a580b399cbcef</anchor>
      <arglist>(const std::string &amp;name, const Teuchos::ParameterList &amp;settings, const RCP&lt; const InverseLibrary &gt; &amp;invLib, const RCP&lt; RequestHandler &gt; &amp;rh)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>addStrategy</name>
      <anchorfile>classTeko_1_1LU2x2PreconditionerFactory.html</anchorfile>
      <anchor>ac5322ae5829ce7eb7ce883fdd93e1942</anchor>
      <arglist>(const std::string &amp;name, const RCP&lt; Cloneable &gt; &amp;clone)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>Teuchos::RCP&lt; LU2x2Strategy &gt;</type>
      <name>invOpsStrategy_</name>
      <anchorfile>classTeko_1_1LU2x2PreconditionerFactory.html</anchorfile>
      <anchor>a665dd0d1c5baa60239307c3d77f23c5d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>bool</type>
      <name>useFullLDU_</name>
      <anchorfile>classTeko_1_1LU2x2PreconditionerFactory.html</anchorfile>
      <anchor>a13d92265eef60c2aab8fa66197a99b85</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>LU2x2PreconditionerFactory</name>
      <anchorfile>classTeko_1_1LU2x2PreconditionerFactory.html</anchorfile>
      <anchor>a95259e22bfdb573906ad86055914af89</anchor>
      <arglist>(LinearOp &amp;invA00, LinearOp &amp;invS)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>LU2x2PreconditionerFactory</name>
      <anchorfile>classTeko_1_1LU2x2PreconditionerFactory.html</anchorfile>
      <anchor>a4562d7d0691e0a678f38fffc4bd204fb</anchor>
      <arglist>(LinearOp &amp;hatInvA00, LinearOp &amp;tildeInvA00, LinearOp &amp;invS)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>LU2x2PreconditionerFactory</name>
      <anchorfile>classTeko_1_1LU2x2PreconditionerFactory.html</anchorfile>
      <anchor>a3e95b08681c46a21b807cfcfab17c912</anchor>
      <arglist>(const Teuchos::RCP&lt; LU2x2Strategy &gt; &amp;strategy)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>LU2x2PreconditionerFactory</name>
      <anchorfile>classTeko_1_1LU2x2PreconditionerFactory.html</anchorfile>
      <anchor>a03881e4a321048d411c68d3cc87dfa8f</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Teko::LU2x2Strategy</name>
    <filename>classTeko_1_1LU2x2Strategy.html</filename>
    <member kind="function" virtualness="pure">
      <type>virtual const Teko::LinearOp</type>
      <name>getHatInvA00</name>
      <anchorfile>classTeko_1_1LU2x2Strategy.html</anchorfile>
      <anchor>a3066e6c5acb3dfb376d912ad619c13c1</anchor>
      <arglist>(const Teko::BlockedLinearOp &amp;A, BlockPreconditionerState &amp;state) const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual const Teko::LinearOp</type>
      <name>getTildeInvA00</name>
      <anchorfile>classTeko_1_1LU2x2Strategy.html</anchorfile>
      <anchor>ab5c1ff57100df65d35a5b3d7856e150b</anchor>
      <arglist>(const Teko::BlockedLinearOp &amp;A, BlockPreconditionerState &amp;state) const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual const Teko::LinearOp</type>
      <name>getInvS</name>
      <anchorfile>classTeko_1_1LU2x2Strategy.html</anchorfile>
      <anchor>ae79e3fd59ac8b7450d3740defa58101e</anchor>
      <arglist>(const Teko::BlockedLinearOp &amp;A, BlockPreconditionerState &amp;state) const  =0</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>initializeFromParameterList</name>
      <anchorfile>classTeko_1_1LU2x2Strategy.html</anchorfile>
      <anchor>a0248ee0a89f037a7023c738bc7aed3f6</anchor>
      <arglist>(const Teuchos::ParameterList &amp;settings, const InverseLibrary &amp;invLib)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual Teuchos::RCP&lt; Teuchos::ParameterList &gt;</type>
      <name>getRequestedParameters</name>
      <anchorfile>classTeko_1_1LU2x2Strategy.html</anchorfile>
      <anchor>ae6090a93d759b9242d6381cfc59bb01a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>updateRequestedParameters</name>
      <anchorfile>classTeko_1_1LU2x2Strategy.html</anchorfile>
      <anchor>ab93c86eb6bb32668487620eb613ef26c</anchor>
      <arglist>(const Teuchos::ParameterList &amp;pl)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setRequestHandler</name>
      <anchorfile>classTeko_1_1LU2x2Strategy.html</anchorfile>
      <anchor>a498d54de4d3d1633c484b3c2daa9d616</anchor>
      <arglist>(const Teuchos::RCP&lt; RequestHandler &gt; &amp;rh)</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; RequestHandler &gt;</type>
      <name>getRequestHandler</name>
      <anchorfile>classTeko_1_1LU2x2Strategy.html</anchorfile>
      <anchor>a73a2a2bd19638fd188d96ee56ad26ca1</anchor>
      <arglist>() const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Teko::Epetra::MappingStrategy</name>
    <filename>classTeko_1_1Epetra_1_1MappingStrategy.html</filename>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>copyEpetraIntoThyra</name>
      <anchorfile>classTeko_1_1Epetra_1_1MappingStrategy.html</anchorfile>
      <anchor>a379445a8e0f247b419b92672bbdca4e2</anchor>
      <arglist>(const Epetra_MultiVector &amp;epetraX, const Teuchos::Ptr&lt; Thyra::MultiVectorBase&lt; double &gt; &gt; &amp;thyraX) const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>copyThyraIntoEpetra</name>
      <anchorfile>classTeko_1_1Epetra_1_1MappingStrategy.html</anchorfile>
      <anchor>afa3ebc69fa9d507a05bec067b5d53348</anchor>
      <arglist>(const RCP&lt; const Thyra::MultiVectorBase&lt; double &gt; &gt; &amp;thyraX, Epetra_MultiVector &amp;epetraX) const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual const RCP&lt; const Epetra_Map &gt;</type>
      <name>domainMap</name>
      <anchorfile>classTeko_1_1Epetra_1_1MappingStrategy.html</anchorfile>
      <anchor>a5f42f1418b0e12109db7d57bc542faeb</anchor>
      <arglist>() const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual const RCP&lt; const Epetra_Map &gt;</type>
      <name>rangeMap</name>
      <anchorfile>classTeko_1_1Epetra_1_1MappingStrategy.html</anchorfile>
      <anchor>a4550669081b6fbdf153702add6a5530b</anchor>
      <arglist>() const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual std::string</type>
      <name>toString</name>
      <anchorfile>classTeko_1_1Epetra_1_1MappingStrategy.html</anchorfile>
      <anchor>a725ca0744ee25dfafdfec9969960db99</anchor>
      <arglist>() const  =0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Teko::TpetraHelpers::MappingStrategy</name>
    <filename>classTeko_1_1TpetraHelpers_1_1MappingStrategy.html</filename>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>copyTpetraIntoThyra</name>
      <anchorfile>classTeko_1_1TpetraHelpers_1_1MappingStrategy.html</anchorfile>
      <anchor>a6f6cdb63a53d463484527216a06d1876</anchor>
      <arglist>(const Tpetra::MultiVector&lt; ST, LO, GO, NT &gt; &amp;tpetraX, const Teuchos::Ptr&lt; Thyra::MultiVectorBase&lt; ST &gt; &gt; &amp;thyraX) const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>copyThyraIntoTpetra</name>
      <anchorfile>classTeko_1_1TpetraHelpers_1_1MappingStrategy.html</anchorfile>
      <anchor>af3b76216ef5a1bcf0f50701ff1f8ff31</anchor>
      <arglist>(const RCP&lt; const Thyra::MultiVectorBase&lt; ST &gt; &gt; &amp;thyraX, Tpetra::MultiVector&lt; ST, LO, GO, NT &gt; &amp;tpetraX) const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual const RCP&lt; const Tpetra::Map&lt; LO, GO, NT &gt; &gt;</type>
      <name>domainMap</name>
      <anchorfile>classTeko_1_1TpetraHelpers_1_1MappingStrategy.html</anchorfile>
      <anchor>a91e0faacb297598c429c1930f34e7651</anchor>
      <arglist>() const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual const RCP&lt; const Tpetra::Map&lt; LO, GO, NT &gt; &gt;</type>
      <name>rangeMap</name>
      <anchorfile>classTeko_1_1TpetraHelpers_1_1MappingStrategy.html</anchorfile>
      <anchor>aa2594ca253f77b564cd6aaa3a7184392</anchor>
      <arglist>() const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual std::string</type>
      <name>toString</name>
      <anchorfile>classTeko_1_1TpetraHelpers_1_1MappingStrategy.html</anchorfile>
      <anchor>a36ac922ff48d564a0cdedd9d05b266df</anchor>
      <arglist>() const  =0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Teko::MLPreconditionerFactory</name>
    <filename>classTeko_1_1MLPreconditionerFactory.html</filename>
    <base>Teko::BlockPreconditionerFactory</base>
    <member kind="function" virtualness="virtual">
      <type>virtual LinearOp</type>
      <name>buildPreconditionerOperator</name>
      <anchorfile>classTeko_1_1MLPreconditionerFactory.html</anchorfile>
      <anchor>a89fd664fce9ea6ede9c6062885f90b73</anchor>
      <arglist>(BlockedLinearOp &amp;blo, BlockPreconditionerState &amp;state) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual Teuchos::RCP&lt; PreconditionerState &gt;</type>
      <name>buildPreconditionerState</name>
      <anchorfile>classTeko_1_1MLPreconditionerFactory.html</anchorfile>
      <anchor>a02c30e561f051be7476d8a4f57356154</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initializeFromParameterList</name>
      <anchorfile>classTeko_1_1MLPreconditionerFactory.html</anchorfile>
      <anchor>a284f8b1c4fdc1b046187b8f1a61d77af</anchor>
      <arglist>(const Teuchos::ParameterList &amp;settings)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>fillMLPreconditionerState</name>
      <anchorfile>classTeko_1_1MLPreconditionerFactory.html</anchorfile>
      <anchor>a30fd2501db7a14819e08c7c244b9cf98</anchor>
      <arglist>(const BlockedLinearOp &amp;blo, MLPreconditionerState &amp;mlState) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Teko::MLPreconditionerState</name>
    <filename>classTeko_1_1MLPreconditionerState.html</filename>
    <base>Teko::BlockPreconditionerState</base>
    <member kind="function">
      <type>Teuchos::RCP&lt; ML_Epetra::MultiLevelPreconditioner &gt;</type>
      <name>constructMLPreconditioner</name>
      <anchorfile>classTeko_1_1MLPreconditionerState.html</anchorfile>
      <anchor>aefb2bd219053ae8ba5e94b7e22cf37d5</anchor>
      <arglist>(const Teuchos::ParameterList &amp;mainList, const std::vector&lt; Teuchos::RCP&lt; const Teuchos::ParameterList &gt; &gt; &amp;coarseningParams)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setMLComm</name>
      <anchorfile>classTeko_1_1MLPreconditionerState.html</anchorfile>
      <anchor>aeb2c249923921cd59bc263d1118b611f</anchor>
      <arglist>(ML_Comm *comm)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setMLOperator</name>
      <anchorfile>classTeko_1_1MLPreconditionerState.html</anchorfile>
      <anchor>acdbf05edba84a1269c42232c82f55b76</anchor>
      <arglist>(ML_Operator *op)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setIsFilled</name>
      <anchorfile>classTeko_1_1MLPreconditionerState.html</anchorfile>
      <anchor>ac772a3cb4c63531612b4d8bbfa7c1171</anchor>
      <arglist>(bool value)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setAggregationMatrices</name>
      <anchorfile>classTeko_1_1MLPreconditionerState.html</anchorfile>
      <anchor>abb72489c7fc2b156a6b84619df9eb987</anchor>
      <arglist>(const std::vector&lt; Epetra_RowMatrix * &gt; &amp;diags)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isFilled</name>
      <anchorfile>classTeko_1_1MLPreconditionerState.html</anchorfile>
      <anchor>a083ff3d3f5f4be648cde7f6212e5b87a</anchor>
      <arglist>() const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Teko::NS::ModALPreconditionerFactory</name>
    <filename>classTeko_1_1NS_1_1ModALPreconditionerFactory.html</filename>
    <base>Teko::BlockPreconditionerFactory</base>
    <member kind="function">
      <type>void</type>
      <name>setPressureMassMatrix</name>
      <anchorfile>classTeko_1_1NS_1_1ModALPreconditionerFactory.html</anchorfile>
      <anchor>a0605efe1ec4eb81afbee2571026626b6</anchor>
      <arglist>(const LinearOp &amp;pressureMassMatrix)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setGamma</name>
      <anchorfile>classTeko_1_1NS_1_1ModALPreconditionerFactory.html</anchorfile>
      <anchor>a80c4318b97adfb1882560d0f8d893ae4</anchor>
      <arglist>(double gamma)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual LinearOp</type>
      <name>buildPreconditionerOperator</name>
      <anchorfile>classTeko_1_1NS_1_1ModALPreconditionerFactory.html</anchorfile>
      <anchor>a0dccceb587fb422aed46d8874dbd419b</anchor>
      <arglist>(BlockedLinearOp &amp;alOp, BlockPreconditionerState &amp;state) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual Teuchos::RCP&lt; PreconditionerState &gt;</type>
      <name>buildPreconditionerState</name>
      <anchorfile>classTeko_1_1NS_1_1ModALPreconditionerFactory.html</anchorfile>
      <anchor>a5b672fb91747f31e2b5363e3ff4a31e8</anchor>
      <arglist>() const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Teko::NS::ModALPrecondState</name>
    <filename>classTeko_1_1NS_1_1ModALPrecondState.html</filename>
    <base>Teko::BlockPreconditionerState</base>
  </compound>
  <compound kind="class">
    <name>Teko::MultPreconditionerFactory</name>
    <filename>classTeko_1_1MultPreconditionerFactory.html</filename>
    <base>Teko::BlockPreconditionerFactory</base>
    <member kind="function">
      <type></type>
      <name>MultPreconditionerFactory</name>
      <anchorfile>classTeko_1_1MultPreconditionerFactory.html</anchorfile>
      <anchor>ad133daa312f52c6a93540df8057e2ec8</anchor>
      <arglist>(const Teuchos::RCP&lt; const Teko::BlockPreconditionerFactory &gt; &amp;FirstFactory, const Teuchos::RCP&lt; const Teko::BlockPreconditionerFactory &gt; &amp;SecondFactory)</arglist>
    </member>
    <member kind="function">
      <type>Teko::LinearOp</type>
      <name>buildPreconditionerOperator</name>
      <anchorfile>classTeko_1_1MultPreconditionerFactory.html</anchorfile>
      <anchor>a1f31965178c6de9f1abf4230c23420bb</anchor>
      <arglist>(Teko::BlockedLinearOp &amp;blo, Teko::BlockPreconditionerState &amp;state) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual Teuchos::RCP&lt; Teko::PreconditionerState &gt;</type>
      <name>buildPreconditionerState</name>
      <anchorfile>classTeko_1_1MultPreconditionerFactory.html</anchorfile>
      <anchor>abeb0db0e99f00b1cbc83ca0ed434271e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual void</type>
      <name>initializeFromParameterList</name>
      <anchorfile>classTeko_1_1MultPreconditionerFactory.html</anchorfile>
      <anchor>af6a60ddd03e713fcd3b6b2b596eaaaed</anchor>
      <arglist>(const Teuchos::ParameterList &amp;pl)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Teko::MultPrecondState</name>
    <filename>classTeko_1_1MultPrecondState.html</filename>
    <base>Teko::BlockPreconditionerState</base>
  </compound>
  <compound kind="class">
    <name>Teko::MultPrecsLinearOp</name>
    <filename>classTeko_1_1MultPrecsLinearOp.html</filename>
    <base>Teko::BlockImplicitLinearOp</base>
    <member kind="function">
      <type></type>
      <name>MultPrecsLinearOp</name>
      <anchorfile>classTeko_1_1MultPrecsLinearOp.html</anchorfile>
      <anchor>ae030bd42dd42873fea5ab44dd6951467</anchor>
      <arglist>(const Teko::LinearOp &amp;A, const Teko::LinearOp &amp;M1, const Teko::LinearOp &amp;M2)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual Teko::VectorSpace</type>
      <name>range</name>
      <anchorfile>classTeko_1_1MultPrecsLinearOp.html</anchorfile>
      <anchor>ab6d15fed93bbb697cbb924490be41000</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual Teko::VectorSpace</type>
      <name>domain</name>
      <anchorfile>classTeko_1_1MultPrecsLinearOp.html</anchorfile>
      <anchor>a664a55c588276ca21d7eca80671694ac</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>implicitApply</name>
      <anchorfile>classTeko_1_1MultPrecsLinearOp.html</anchorfile>
      <anchor>a54cc6aa377b95c43ccc52de9980d465d</anchor>
      <arglist>(const Teko::BlockedMultiVector &amp;r, Teko::BlockedMultiVector &amp;y, const double alpha=1.0, const double beta=0.0) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Teko::NS::PCDStrategy</name>
    <filename>classTeko_1_1NS_1_1PCDStrategy.html</filename>
    <base>Teko::LU2x2Strategy</base>
    <member kind="function">
      <type></type>
      <name>PCDStrategy</name>
      <anchorfile>classTeko_1_1NS_1_1PCDStrategy.html</anchorfile>
      <anchor>af7bc2a0637f11adcdaf65f004b57b803</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>PCDStrategy</name>
      <anchorfile>classTeko_1_1NS_1_1PCDStrategy.html</anchorfile>
      <anchor>ab5544e2abf6a4c71667d16b71a438fa8</anchor>
      <arglist>(const Teuchos::RCP&lt; InverseFactory &gt; &amp;invFA, const Teuchos::RCP&lt; InverseFactory &gt; &amp;invS)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~PCDStrategy</name>
      <anchorfile>classTeko_1_1NS_1_1PCDStrategy.html</anchorfile>
      <anchor>a700f21e91b00d5cc735a06edec06381c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const Teko::LinearOp</type>
      <name>getHatInvA00</name>
      <anchorfile>classTeko_1_1NS_1_1PCDStrategy.html</anchorfile>
      <anchor>a4641148452095631170e25e65bac8ce5</anchor>
      <arglist>(const Teko::BlockedLinearOp &amp;A, BlockPreconditionerState &amp;state) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const Teko::LinearOp</type>
      <name>getTildeInvA00</name>
      <anchorfile>classTeko_1_1NS_1_1PCDStrategy.html</anchorfile>
      <anchor>a7b1ec17932aacfd0cf53acf89d80a245</anchor>
      <arglist>(const Teko::BlockedLinearOp &amp;A, BlockPreconditionerState &amp;state) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const Teko::LinearOp</type>
      <name>getInvS</name>
      <anchorfile>classTeko_1_1NS_1_1PCDStrategy.html</anchorfile>
      <anchor>a8f39ff158d4a423e8f2278b63b5e114c</anchor>
      <arglist>(const Teko::BlockedLinearOp &amp;A, BlockPreconditionerState &amp;state) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>initializeFromParameterList</name>
      <anchorfile>classTeko_1_1NS_1_1PCDStrategy.html</anchorfile>
      <anchor>a2be28b32c9b82d3d664d170fcd593106</anchor>
      <arglist>(const Teuchos::ParameterList &amp;settings, const InverseLibrary &amp;invLib)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual Teuchos::RCP&lt; Teuchos::ParameterList &gt;</type>
      <name>getRequestedParameters</name>
      <anchorfile>classTeko_1_1NS_1_1PCDStrategy.html</anchorfile>
      <anchor>a52548f29f2cc09773662df04ea2815a1</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>updateRequestedParameters</name>
      <anchorfile>classTeko_1_1NS_1_1PCDStrategy.html</anchorfile>
      <anchor>acdf8812a289d5ec1b73f2c65f7141dde</anchor>
      <arglist>(const Teuchos::ParameterList &amp;pl)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>initializeState</name>
      <anchorfile>classTeko_1_1NS_1_1PCDStrategy.html</anchorfile>
      <anchor>a8c8a608c17395d77300c1842d93e5c8d</anchor>
      <arglist>(const Teko::BlockedLinearOp &amp;A, BlockPreconditionerState &amp;state) const </arglist>
    </member>
    <member kind="function" protection="protected" static="yes">
      <type>static void</type>
      <name>buildTimers</name>
      <anchorfile>classTeko_1_1NS_1_1PCDStrategy.html</anchorfile>
      <anchor>a81adb7ae668cc4f5ba29909abd65185c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>Teuchos::RCP&lt; Teuchos::ParameterList &gt;</type>
      <name>lapParams_</name>
      <anchorfile>classTeko_1_1NS_1_1PCDStrategy.html</anchorfile>
      <anchor>a0afe42699b250dcda962ce2b27ceb28d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>Teuchos::RCP&lt; Teuchos::ParameterList &gt;</type>
      <name>pcdParams_</name>
      <anchorfile>classTeko_1_1NS_1_1PCDStrategy.html</anchorfile>
      <anchor>a48bf6ac474582c996032e36f04a9993b</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Teko::Preconditioner</name>
    <filename>classTeko_1_1Preconditioner.html</filename>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>setSourceVector</name>
      <anchorfile>classTeko_1_1Preconditioner.html</anchorfile>
      <anchor>a0a50be99931d276840581526e616ff7e</anchor>
      <arglist>(const RCP&lt; Thyra::MultiVectorBase&lt; double &gt; &gt; &amp;srcVec)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>setStateObject</name>
      <anchorfile>classTeko_1_1Preconditioner.html</anchorfile>
      <anchor>a951333402d306394ca4c1d8cc4e3458a</anchor>
      <arglist>(const RCP&lt; PreconditionerState &gt; &amp;state)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const RCP&lt; PreconditionerState &gt;</type>
      <name>getStateObject</name>
      <anchorfile>classTeko_1_1Preconditioner.html</anchorfile>
      <anchor>ac15a9e77d5f111272b21c7608f75651b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const RCP&lt; const PreconditionerState &gt;</type>
      <name>getStateObject</name>
      <anchorfile>classTeko_1_1Preconditioner.html</anchorfile>
      <anchor>a1e6f4cb8435343c43b6684b7421d6d22</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>mergeStateObject</name>
      <anchorfile>classTeko_1_1Preconditioner.html</anchorfile>
      <anchor>a224efa17dc1af93f1024d7c21d86b182</anchor>
      <arglist>(const PreconditionerState &amp;state)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>RCP&lt; PreconditionerState &gt;</type>
      <name>state_</name>
      <anchorfile>classTeko_1_1Preconditioner.html</anchorfile>
      <anchor>a609f8b7f00060cf293faa0aaf2a0ef53</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Teko::PreconditionerFactory</name>
    <filename>classTeko_1_1PreconditionerFactory.html</filename>
    <base>Teko::RequestHandlerContainer</base>
    <member kind="function" virtualness="pure">
      <type>virtual LinearOp</type>
      <name>buildPreconditionerOperator</name>
      <anchorfile>classTeko_1_1PreconditionerFactory.html</anchorfile>
      <anchor>a6ea45cb71834512e4ec6f764c84c7466</anchor>
      <arglist>(LinearOp &amp;lo, PreconditionerState &amp;state) const  =0</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual Teuchos::RCP&lt; PreconditionerState &gt;</type>
      <name>buildPreconditionerState</name>
      <anchorfile>classTeko_1_1PreconditionerFactory.html</anchorfile>
      <anchor>abb37c5a190840949c0c9917b480a35ad</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setInverseLibrary</name>
      <anchorfile>classTeko_1_1PreconditionerFactory.html</anchorfile>
      <anchor>a43d6f8e45b562d8fc1554abd9deae31b</anchor>
      <arglist>(const Teuchos::RCP&lt; const InverseLibrary &gt; &amp;il)</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const InverseLibrary &gt;</type>
      <name>getInverseLibrary</name>
      <anchorfile>classTeko_1_1PreconditionerFactory.html</anchorfile>
      <anchor>aa5584b1216e75e49679ac781b3955cee</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setRequestHandler</name>
      <anchorfile>classTeko_1_1PreconditionerFactory.html</anchorfile>
      <anchor>a6645be4a6d9cf413b06e02e91d750c1c</anchor>
      <arglist>(const Teuchos::RCP&lt; RequestHandler &gt; &amp;rh)</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; RequestHandler &gt;</type>
      <name>getRequestHandler</name>
      <anchorfile>classTeko_1_1PreconditionerFactory.html</anchorfile>
      <anchor>aac2fcde90ec7a94d9c87d30818ed462c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>initializeFromParameterList</name>
      <anchorfile>classTeko_1_1PreconditionerFactory.html</anchorfile>
      <anchor>af572a75619897db5dcb1781be51c2bb4</anchor>
      <arglist>(const Teuchos::ParameterList &amp;settings)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual Teuchos::RCP&lt; Teuchos::ParameterList &gt;</type>
      <name>getRequestedParameters</name>
      <anchorfile>classTeko_1_1PreconditionerFactory.html</anchorfile>
      <anchor>a369b96722a05c8bdcf914376ec5d116c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>updateRequestedParameters</name>
      <anchorfile>classTeko_1_1PreconditionerFactory.html</anchorfile>
      <anchor>a235db56ba59fdb73b692b5ffa945bb5b</anchor>
      <arglist>(const Teuchos::ParameterList &amp;pl)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isCompatible</name>
      <anchorfile>classTeko_1_1PreconditionerFactory.html</anchorfile>
      <anchor>af4550e79e10d3c3a3d6d028b10def7b0</anchor>
      <arglist>(const Thyra::LinearOpSourceBase&lt; double &gt; &amp;fwdOpSrc) const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; Thyra::PreconditionerBase&lt; double &gt; &gt;</type>
      <name>createPrec</name>
      <anchorfile>classTeko_1_1PreconditionerFactory.html</anchorfile>
      <anchor>a2ac39ed64e13d50d9d7a849780576127</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initializePrec</name>
      <anchorfile>classTeko_1_1PreconditionerFactory.html</anchorfile>
      <anchor>a1d599380f61731fb66fb56d1f35b9235</anchor>
      <arglist>(const Teuchos::RCP&lt; const Thyra::LinearOpSourceBase&lt; double &gt; &gt; &amp;fwdOpSrc, const Teuchos::RCP&lt; const Thyra::MultiVectorBase&lt; double &gt; &gt; &amp;solnVec, Thyra::PreconditionerBase&lt; double &gt; *precOp, const Thyra::ESupportSolveUse supportSolveUse) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initializePrec</name>
      <anchorfile>classTeko_1_1PreconditionerFactory.html</anchorfile>
      <anchor>a8dde5553cff56f6263beb6bbc874e8f7</anchor>
      <arglist>(const Teuchos::RCP&lt; const Thyra::LinearOpSourceBase&lt; double &gt; &gt; &amp;fwdOpSrc, Thyra::PreconditionerBase&lt; double &gt; *precOp, const Thyra::ESupportSolveUse supportSolveUse) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>uninitializePrec</name>
      <anchorfile>classTeko_1_1PreconditionerFactory.html</anchorfile>
      <anchor>a61a890f0a3cda766e0be8128c0ccfc02</anchor>
      <arglist>(Thyra::PreconditionerBase&lt; double &gt; *prec, Teuchos::RCP&lt; const Thyra::LinearOpSourceBase&lt; double &gt; &gt; *fwdOpSrc, Thyra::ESupportSolveUse *supportSolveUse) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setParameterList</name>
      <anchorfile>classTeko_1_1PreconditionerFactory.html</anchorfile>
      <anchor>a7eee51199a2c0ea36f1c526f24e66c5c</anchor>
      <arglist>(const Teuchos::RCP&lt; Teuchos::ParameterList &gt; &amp;paramList)</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; Teuchos::ParameterList &gt;</type>
      <name>getNonconstParameterList</name>
      <anchorfile>classTeko_1_1PreconditionerFactory.html</anchorfile>
      <anchor>a2e5b0a3d366c45ecad10e9adaab718ec</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; Teuchos::ParameterList &gt;</type>
      <name>unsetParameterList</name>
      <anchorfile>classTeko_1_1PreconditionerFactory.html</anchorfile>
      <anchor>afdb7cb2d38ecc54a5d3dbadf03b572c1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static Teuchos::RCP&lt; PreconditionerFactory &gt;</type>
      <name>buildPreconditionerFactory</name>
      <anchorfile>classTeko_1_1PreconditionerFactory.html</anchorfile>
      <anchor>a5b116ad6f273e5c8ea61ff650a195365</anchor>
      <arglist>(const std::string &amp;name, const Teuchos::ParameterList &amp;settings, const Teuchos::RCP&lt; const InverseLibrary &gt; &amp;invLib=Teuchos::null)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>addPreconditionerFactory</name>
      <anchorfile>classTeko_1_1PreconditionerFactory.html</anchorfile>
      <anchor>a916dab55bfa2115efc0acd2e0e52df11</anchor>
      <arglist>(const std::string &amp;name, const Teuchos::RCP&lt; Cloneable &gt; &amp;clone)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>getPreconditionerFactoryNames</name>
      <anchorfile>classTeko_1_1PreconditionerFactory.html</anchorfile>
      <anchor>ac0f22206fa1c3d60c0e74772d2a6e9c2</anchor>
      <arglist>(std::vector&lt; std::string &gt; &amp;names)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>Teuchos::RCP&lt; Teuchos::ParameterList &gt;</type>
      <name>paramList_</name>
      <anchorfile>classTeko_1_1PreconditionerFactory.html</anchorfile>
      <anchor>a7efd4d70fa6b7fa787f4a3045d9398f3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>Teuchos::RCP&lt; RequestHandler &gt;</type>
      <name>callbackHandler_</name>
      <anchorfile>classTeko_1_1PreconditionerFactory.html</anchorfile>
      <anchor>a9c61d2e0284534caaa95e48d00aae49e</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>initializeFromParameterList</name>
      <anchorfile>classTeko_1_1PreconditionerFactory.html</anchorfile>
      <anchor>af572a75619897db5dcb1781be51c2bb4</anchor>
      <arglist>(const Teuchos::ParameterList &amp;settings)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual Teuchos::RCP&lt; Teuchos::ParameterList &gt;</type>
      <name>getRequestedParameters</name>
      <anchorfile>classTeko_1_1PreconditionerFactory.html</anchorfile>
      <anchor>a369b96722a05c8bdcf914376ec5d116c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>updateRequestedParameters</name>
      <anchorfile>classTeko_1_1PreconditionerFactory.html</anchorfile>
      <anchor>a235db56ba59fdb73b692b5ffa945bb5b</anchor>
      <arglist>(const Teuchos::ParameterList &amp;pl)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isCompatible</name>
      <anchorfile>classTeko_1_1PreconditionerFactory.html</anchorfile>
      <anchor>af4550e79e10d3c3a3d6d028b10def7b0</anchor>
      <arglist>(const Thyra::LinearOpSourceBase&lt; double &gt; &amp;fwdOpSrc) const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; Thyra::PreconditionerBase&lt; double &gt; &gt;</type>
      <name>createPrec</name>
      <anchorfile>classTeko_1_1PreconditionerFactory.html</anchorfile>
      <anchor>a2ac39ed64e13d50d9d7a849780576127</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initializePrec</name>
      <anchorfile>classTeko_1_1PreconditionerFactory.html</anchorfile>
      <anchor>a1d599380f61731fb66fb56d1f35b9235</anchor>
      <arglist>(const Teuchos::RCP&lt; const Thyra::LinearOpSourceBase&lt; double &gt; &gt; &amp;fwdOpSrc, const Teuchos::RCP&lt; const Thyra::MultiVectorBase&lt; double &gt; &gt; &amp;solnVec, Thyra::PreconditionerBase&lt; double &gt; *precOp, const Thyra::ESupportSolveUse supportSolveUse) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initializePrec</name>
      <anchorfile>classTeko_1_1PreconditionerFactory.html</anchorfile>
      <anchor>a8dde5553cff56f6263beb6bbc874e8f7</anchor>
      <arglist>(const Teuchos::RCP&lt; const Thyra::LinearOpSourceBase&lt; double &gt; &gt; &amp;fwdOpSrc, Thyra::PreconditionerBase&lt; double &gt; *precOp, const Thyra::ESupportSolveUse supportSolveUse) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>uninitializePrec</name>
      <anchorfile>classTeko_1_1PreconditionerFactory.html</anchorfile>
      <anchor>a61a890f0a3cda766e0be8128c0ccfc02</anchor>
      <arglist>(Thyra::PreconditionerBase&lt; double &gt; *prec, Teuchos::RCP&lt; const Thyra::LinearOpSourceBase&lt; double &gt; &gt; *fwdOpSrc, Thyra::ESupportSolveUse *supportSolveUse) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setParameterList</name>
      <anchorfile>classTeko_1_1PreconditionerFactory.html</anchorfile>
      <anchor>a7eee51199a2c0ea36f1c526f24e66c5c</anchor>
      <arglist>(const Teuchos::RCP&lt; Teuchos::ParameterList &gt; &amp;paramList)</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; Teuchos::ParameterList &gt;</type>
      <name>getNonconstParameterList</name>
      <anchorfile>classTeko_1_1PreconditionerFactory.html</anchorfile>
      <anchor>a2e5b0a3d366c45ecad10e9adaab718ec</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; Teuchos::ParameterList &gt;</type>
      <name>unsetParameterList</name>
      <anchorfile>classTeko_1_1PreconditionerFactory.html</anchorfile>
      <anchor>afdb7cb2d38ecc54a5d3dbadf03b572c1</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Teko::PreconditionerLinearOp</name>
    <filename>classTeko_1_1PreconditionerLinearOp.html</filename>
    <templarg></templarg>
    <member kind="function">
      <type>void</type>
      <name>initialize</name>
      <anchorfile>classTeko_1_1PreconditionerLinearOp.html</anchorfile>
      <anchor>a444df1249225f5729df9fba314a68046</anchor>
      <arglist>(const Teuchos::RCP&lt; Thyra::PreconditionerBase&lt; ScalarT &gt; &gt; &amp;prec)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initialize</name>
      <anchorfile>classTeko_1_1PreconditionerLinearOp.html</anchorfile>
      <anchor>aa29dc7056be28fbbf3fac06c2822e8a0</anchor>
      <arglist>(const Teuchos::RCP&lt; const Thyra::PreconditionerBase&lt; ScalarT &gt; &gt; &amp;prec)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>uninitialize</name>
      <anchorfile>classTeko_1_1PreconditionerLinearOp.html</anchorfile>
      <anchor>aead3b7eee76bb1ec6ef02cd7ed24b763</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual Teuchos::RCP&lt; const Thyra::VectorSpaceBase&lt; ScalarT &gt; &gt;</type>
      <name>range</name>
      <anchorfile>classTeko_1_1PreconditionerLinearOp.html</anchorfile>
      <anchor>a18294c5165f9fa08fade6c5d4749fdd3</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual Teuchos::RCP&lt; const Thyra::VectorSpaceBase&lt; ScalarT &gt; &gt;</type>
      <name>domain</name>
      <anchorfile>classTeko_1_1PreconditionerLinearOp.html</anchorfile>
      <anchor>aebbd97e14c650e5a793c1ebb30806165</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>applyImpl</name>
      <anchorfile>classTeko_1_1PreconditionerLinearOp.html</anchorfile>
      <anchor>a66e5f87dd025e1c0cab38f95bacff47c</anchor>
      <arglist>(const Thyra::EOpTransp M_trans, const Thyra::MultiVectorBase&lt; ScalarT &gt; &amp;x, const Teuchos::Ptr&lt; Thyra::MultiVectorBase&lt; ScalarT &gt; &gt; &amp;y, const ScalarT alpha, const ScalarT beta) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual Teuchos::RCP&lt; Thyra::PreconditionerBase&lt; ScalarT &gt; &gt;</type>
      <name>getNonconstPreconditioner</name>
      <anchorfile>classTeko_1_1PreconditionerLinearOp.html</anchorfile>
      <anchor>a024d06e63de35c29cf0e23ce9398b494</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual Teuchos::RCP&lt; const Thyra::PreconditionerBase&lt; ScalarT &gt; &gt;</type>
      <name>getPreconditioner</name>
      <anchorfile>classTeko_1_1PreconditionerLinearOp.html</anchorfile>
      <anchor>afb53c290ee0e0ccd4319e19501cddbe0</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Teko::LinearOp</type>
      <name>getOperator</name>
      <anchorfile>classTeko_1_1PreconditionerLinearOp.html</anchorfile>
      <anchor>ae50f208ddb471e696a4c73e5ac27ef7a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>Teuchos::ConstNonconstObjectContainer&lt; Thyra::LinearOpBase&lt; ScalarT &gt; &gt;</type>
      <name>getOperator_cnoc</name>
      <anchorfile>classTeko_1_1PreconditionerLinearOp.html</anchorfile>
      <anchor>a1ed9ffd890d41846cd48fd89554b53a7</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>Teuchos::ConstNonconstObjectContainer&lt; Thyra::LinearOpBase&lt; ScalarT &gt; &gt;</type>
      <name>getOperator_cnoc</name>
      <anchorfile>classTeko_1_1PreconditionerLinearOp.html</anchorfile>
      <anchor>a53ec789f5d36cc83f2101681589b0d8d</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Teko::PreconditionerState</name>
    <filename>classTeko_1_1PreconditionerState.html</filename>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>isInitialized</name>
      <anchorfile>classTeko_1_1PreconditionerState.html</anchorfile>
      <anchor>adf1e6841c15281fc537408e7a389c742</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>setInitialized</name>
      <anchorfile>classTeko_1_1PreconditionerState.html</anchorfile>
      <anchor>ab4a684832966d11c041bdbf93b696f6b</anchor>
      <arglist>(bool init=true)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>setSourceVector</name>
      <anchorfile>classTeko_1_1PreconditionerState.html</anchorfile>
      <anchor>a8176cbefa4ce91649a760a8b2c35f9b3</anchor>
      <arglist>(const Teko::MultiVector &amp;srcVec)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const Teko::MultiVector</type>
      <name>getSourceVector</name>
      <anchorfile>classTeko_1_1PreconditionerState.html</anchorfile>
      <anchor>acf7beeaca813e5c022f27ee3c744f085</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>addInverse</name>
      <anchorfile>classTeko_1_1PreconditionerState.html</anchorfile>
      <anchor>a5a10be394e2073688afea43d4ff9f779</anchor>
      <arglist>(const std::string &amp;name, const Teko::InverseLinearOp &amp;ilo)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual Teko::InverseLinearOp</type>
      <name>getInverse</name>
      <anchorfile>classTeko_1_1PreconditionerState.html</anchorfile>
      <anchor>ad673e550f12a9d616348561b4bf01f88</anchor>
      <arglist>(const std::string &amp;name) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>addLinearOp</name>
      <anchorfile>classTeko_1_1PreconditionerState.html</anchorfile>
      <anchor>a2b8ff97e529743e0630b7a7220e3fad5</anchor>
      <arglist>(const std::string &amp;name, const Teko::LinearOp &amp;lo)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual Teko::LinearOp</type>
      <name>getLinearOp</name>
      <anchorfile>classTeko_1_1PreconditionerState.html</anchorfile>
      <anchor>aaa94213bd6522e74043e39d34e91e333</anchor>
      <arglist>(const std::string &amp;name)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>addModifiableOp</name>
      <anchorfile>classTeko_1_1PreconditionerState.html</anchorfile>
      <anchor>a36aa80665a0de1fb970c073b6e3f90e8</anchor>
      <arglist>(const std::string &amp;name, const Teko::ModifiableLinearOp &amp;mlo)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual Teko::ModifiableLinearOp &amp;</type>
      <name>getModifiableOp</name>
      <anchorfile>classTeko_1_1PreconditionerState.html</anchorfile>
      <anchor>ad53e5d1fd678024d6eccb9c174aeb469</anchor>
      <arglist>(const std::string &amp;name)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>merge</name>
      <anchorfile>classTeko_1_1PreconditionerState.html</anchorfile>
      <anchor>a9915ba149130db95b333339e65d73e81</anchor>
      <arglist>(const PreconditionerState &amp;ps, int position=-1)</arglist>
    </member>
    <member kind="function">
      <type>unsigned int</type>
      <name>getTag</name>
      <anchorfile>classTeko_1_1PreconditionerState.html</anchorfile>
      <anchor>a19bd3677b02700207b7aca94583ebcd6</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setTag</name>
      <anchorfile>classTeko_1_1PreconditionerState.html</anchorfile>
      <anchor>a8376de8c45535bb79ba29729aa80e714</anchor>
      <arglist>(unsigned int tag)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setParameterList</name>
      <anchorfile>classTeko_1_1PreconditionerState.html</anchorfile>
      <anchor>a483808eb268aea58d4ff2ea2831bee19</anchor>
      <arglist>(const Teuchos::RCP&lt; Teuchos::ParameterList &gt; &amp;paramList)</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; Teuchos::ParameterList &gt;</type>
      <name>getNonconstParameterList</name>
      <anchorfile>classTeko_1_1PreconditionerState.html</anchorfile>
      <anchor>a95ff9ab205e186e7d0bf3aa87fbe09df</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; Teuchos::ParameterList &gt;</type>
      <name>unsetParameterList</name>
      <anchorfile>classTeko_1_1PreconditionerState.html</anchorfile>
      <anchor>a1fcdacb3a5d23873d63faf2bc695939e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>Teuchos::RCP&lt; Teuchos::ParameterList &gt;</type>
      <name>paramList_</name>
      <anchorfile>classTeko_1_1PreconditionerState.html</anchorfile>
      <anchor>ae3395c9ad947848e17e3e4817351424d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>Teko::MultiVector</type>
      <name>srcVector_</name>
      <anchorfile>classTeko_1_1PreconditionerState.html</anchorfile>
      <anchor>a1c40d83e43226717695433d56d7d6254</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>std::map&lt; std::string, Teko::InverseLinearOp &gt;</type>
      <name>inverses_</name>
      <anchorfile>classTeko_1_1PreconditionerState.html</anchorfile>
      <anchor>ad0be7d4f65592921f3e72708e793a926</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>bool</type>
      <name>isInitialized_</name>
      <anchorfile>classTeko_1_1PreconditionerState.html</anchorfile>
      <anchor>ab55ff28f501a1b1e6370a5b81612e8ce</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setParameterList</name>
      <anchorfile>classTeko_1_1PreconditionerState.html</anchorfile>
      <anchor>a483808eb268aea58d4ff2ea2831bee19</anchor>
      <arglist>(const Teuchos::RCP&lt; Teuchos::ParameterList &gt; &amp;paramList)</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; Teuchos::ParameterList &gt;</type>
      <name>getNonconstParameterList</name>
      <anchorfile>classTeko_1_1PreconditionerState.html</anchorfile>
      <anchor>a95ff9ab205e186e7d0bf3aa87fbe09df</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; Teuchos::ParameterList &gt;</type>
      <name>unsetParameterList</name>
      <anchorfile>classTeko_1_1PreconditionerState.html</anchorfile>
      <anchor>a1fcdacb3a5d23873d63faf2bc695939e</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Teko::NS::PresLaplaceLSCStrategy</name>
    <filename>classTeko_1_1NS_1_1PresLaplaceLSCStrategy.html</filename>
    <base>Teko::NS::LSCStrategy</base>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>initializeState</name>
      <anchorfile>classTeko_1_1NS_1_1PresLaplaceLSCStrategy.html</anchorfile>
      <anchor>aa416cab0b560e0d0b9c3665c698c1140</anchor>
      <arglist>(const BlockedLinearOp &amp;A, LSCPrecondState *state) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>computeInverses</name>
      <anchorfile>classTeko_1_1NS_1_1PresLaplaceLSCStrategy.html</anchorfile>
      <anchor>a234649ae60416544e7265d2d5224c3fe</anchor>
      <arglist>(const BlockedLinearOp &amp;A, LSCPrecondState *state) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>setEigSolveParam</name>
      <anchorfile>classTeko_1_1NS_1_1PresLaplaceLSCStrategy.html</anchorfile>
      <anchor>ab4d11ad4f0eb0b6f64c43ad9b506d8a3</anchor>
      <arglist>(int sz)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>getEigSolveParam</name>
      <anchorfile>classTeko_1_1NS_1_1PresLaplaceLSCStrategy.html</anchorfile>
      <anchor>a0c46b7539f7f27dee8c91dd15215346c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>setUseFullLDU</name>
      <anchorfile>classTeko_1_1NS_1_1PresLaplaceLSCStrategy.html</anchorfile>
      <anchor>ab44e00bd95f275611408476bb6096c9a</anchor>
      <arglist>(bool val)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>buildState</name>
      <anchorfile>classTeko_1_1NS_1_1PresLaplaceLSCStrategy.html</anchorfile>
      <anchor>a24fc50d2ce30a5304b1482c023449774</anchor>
      <arglist>(BlockedLinearOp &amp;A, BlockPreconditionerState &amp;state) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual LinearOp</type>
      <name>getInvBQBt</name>
      <anchorfile>classTeko_1_1NS_1_1PresLaplaceLSCStrategy.html</anchorfile>
      <anchor>a5eed51d2442ef0f302ad04eecc5286cc</anchor>
      <arglist>(const BlockedLinearOp &amp;A, BlockPreconditionerState &amp;state) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual LinearOp</type>
      <name>getInvBHBt</name>
      <anchorfile>classTeko_1_1NS_1_1PresLaplaceLSCStrategy.html</anchorfile>
      <anchor>a97119cb39de7d7902ac05b94722dea9b</anchor>
      <arglist>(const BlockedLinearOp &amp;A, BlockPreconditionerState &amp;state) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual LinearOp</type>
      <name>getInvF</name>
      <anchorfile>classTeko_1_1NS_1_1PresLaplaceLSCStrategy.html</anchorfile>
      <anchor>ad2f117e77550497563944eac00d013d6</anchor>
      <arglist>(const BlockedLinearOp &amp;A, BlockPreconditionerState &amp;state) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual LinearOp</type>
      <name>getOuterStabilization</name>
      <anchorfile>classTeko_1_1NS_1_1PresLaplaceLSCStrategy.html</anchorfile>
      <anchor>aaf71af23b092470335d1eec47a1d9cc3</anchor>
      <arglist>(const BlockedLinearOp &amp;A, BlockPreconditionerState &amp;state) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual LinearOp</type>
      <name>getInnerStabilization</name>
      <anchorfile>classTeko_1_1NS_1_1PresLaplaceLSCStrategy.html</anchorfile>
      <anchor>ae49da8da1ef932921544983ba767ae4f</anchor>
      <arglist>(const BlockedLinearOp &amp;A, BlockPreconditionerState &amp;state) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual LinearOp</type>
      <name>getInvMass</name>
      <anchorfile>classTeko_1_1NS_1_1PresLaplaceLSCStrategy.html</anchorfile>
      <anchor>ac5598e6ff07994a11ef2512ed7eaa9ac</anchor>
      <arglist>(const BlockedLinearOp &amp;A, BlockPreconditionerState &amp;state) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual LinearOp</type>
      <name>getHScaling</name>
      <anchorfile>classTeko_1_1NS_1_1PresLaplaceLSCStrategy.html</anchorfile>
      <anchor>a55db194a2bd5d6dac2a772dabf3a296b</anchor>
      <arglist>(const BlockedLinearOp &amp;A, BlockPreconditionerState &amp;state) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>useFullLDU</name>
      <anchorfile>classTeko_1_1NS_1_1PresLaplaceLSCStrategy.html</anchorfile>
      <anchor>a757d8d9b9754176ca995a837a9d8b93d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>setSymmetric</name>
      <anchorfile>classTeko_1_1NS_1_1PresLaplaceLSCStrategy.html</anchorfile>
      <anchor>a33958b51c09cd42f0d5aaef37aaff44a</anchor>
      <arglist>(bool isSymmetric)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>initializeFromParameterList</name>
      <anchorfile>classTeko_1_1NS_1_1PresLaplaceLSCStrategy.html</anchorfile>
      <anchor>a04b805e5729d92764b0c306d7ed5c8be</anchor>
      <arglist>(const Teuchos::ParameterList &amp;pl, const InverseLibrary &amp;invLib)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual Teuchos::RCP&lt; Teuchos::ParameterList &gt;</type>
      <name>getRequestedParameters</name>
      <anchorfile>classTeko_1_1NS_1_1PresLaplaceLSCStrategy.html</anchorfile>
      <anchor>a5fdca07e279082357d3773dedecd5a0d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>updateRequestedParameters</name>
      <anchorfile>classTeko_1_1NS_1_1PresLaplaceLSCStrategy.html</anchorfile>
      <anchor>a5410687b232609b0ec14cd482eb35ffc</anchor>
      <arglist>(const Teuchos::ParameterList &amp;pl)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>buildState</name>
      <anchorfile>classTeko_1_1NS_1_1PresLaplaceLSCStrategy.html</anchorfile>
      <anchor>a24fc50d2ce30a5304b1482c023449774</anchor>
      <arglist>(BlockedLinearOp &amp;A, BlockPreconditionerState &amp;state) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual LinearOp</type>
      <name>getInvBQBt</name>
      <anchorfile>classTeko_1_1NS_1_1PresLaplaceLSCStrategy.html</anchorfile>
      <anchor>a5eed51d2442ef0f302ad04eecc5286cc</anchor>
      <arglist>(const BlockedLinearOp &amp;A, BlockPreconditionerState &amp;state) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual LinearOp</type>
      <name>getInvBHBt</name>
      <anchorfile>classTeko_1_1NS_1_1PresLaplaceLSCStrategy.html</anchorfile>
      <anchor>a97119cb39de7d7902ac05b94722dea9b</anchor>
      <arglist>(const BlockedLinearOp &amp;A, BlockPreconditionerState &amp;state) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual LinearOp</type>
      <name>getInvF</name>
      <anchorfile>classTeko_1_1NS_1_1PresLaplaceLSCStrategy.html</anchorfile>
      <anchor>ad2f117e77550497563944eac00d013d6</anchor>
      <arglist>(const BlockedLinearOp &amp;A, BlockPreconditionerState &amp;state) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual LinearOp</type>
      <name>getOuterStabilization</name>
      <anchorfile>classTeko_1_1NS_1_1PresLaplaceLSCStrategy.html</anchorfile>
      <anchor>aaf71af23b092470335d1eec47a1d9cc3</anchor>
      <arglist>(const BlockedLinearOp &amp;A, BlockPreconditionerState &amp;state) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual LinearOp</type>
      <name>getInnerStabilization</name>
      <anchorfile>classTeko_1_1NS_1_1PresLaplaceLSCStrategy.html</anchorfile>
      <anchor>ae49da8da1ef932921544983ba767ae4f</anchor>
      <arglist>(const BlockedLinearOp &amp;A, BlockPreconditionerState &amp;state) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual LinearOp</type>
      <name>getInvMass</name>
      <anchorfile>classTeko_1_1NS_1_1PresLaplaceLSCStrategy.html</anchorfile>
      <anchor>ac5598e6ff07994a11ef2512ed7eaa9ac</anchor>
      <arglist>(const BlockedLinearOp &amp;A, BlockPreconditionerState &amp;state) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual LinearOp</type>
      <name>getHScaling</name>
      <anchorfile>classTeko_1_1NS_1_1PresLaplaceLSCStrategy.html</anchorfile>
      <anchor>a55db194a2bd5d6dac2a772dabf3a296b</anchor>
      <arglist>(const BlockedLinearOp &amp;A, BlockPreconditionerState &amp;state) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>useFullLDU</name>
      <anchorfile>classTeko_1_1NS_1_1PresLaplaceLSCStrategy.html</anchorfile>
      <anchor>a757d8d9b9754176ca995a837a9d8b93d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>setSymmetric</name>
      <anchorfile>classTeko_1_1NS_1_1PresLaplaceLSCStrategy.html</anchorfile>
      <anchor>a33958b51c09cd42f0d5aaef37aaff44a</anchor>
      <arglist>(bool isSymmetric)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>initializeFromParameterList</name>
      <anchorfile>classTeko_1_1NS_1_1PresLaplaceLSCStrategy.html</anchorfile>
      <anchor>a04b805e5729d92764b0c306d7ed5c8be</anchor>
      <arglist>(const Teuchos::ParameterList &amp;pl, const InverseLibrary &amp;invLib)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual Teuchos::RCP&lt; Teuchos::ParameterList &gt;</type>
      <name>getRequestedParameters</name>
      <anchorfile>classTeko_1_1NS_1_1PresLaplaceLSCStrategy.html</anchorfile>
      <anchor>a5fdca07e279082357d3773dedecd5a0d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>updateRequestedParameters</name>
      <anchorfile>classTeko_1_1NS_1_1PresLaplaceLSCStrategy.html</anchorfile>
      <anchor>a5410687b232609b0ec14cd482eb35ffc</anchor>
      <arglist>(const Teuchos::ParameterList &amp;pl)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Teko::ReorderedLinearOp</name>
    <filename>classTeko_1_1ReorderedLinearOp.html</filename>
    <base>Teko::ImplicitLinearOp</base>
    <member kind="function">
      <type>Teuchos::RCP&lt; const BlockReorderManager &gt;</type>
      <name>getReorderManager</name>
      <anchorfile>classTeko_1_1ReorderedLinearOp.html</anchorfile>
      <anchor>ac9398c07f1b7268b7a7134a7252e206c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Teko::ModifiableLinearOp</type>
      <name>getBlockedOp</name>
      <anchorfile>classTeko_1_1ReorderedLinearOp.html</anchorfile>
      <anchor>a72c913fec1ad2bacaa8712a61731161a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual VectorSpace</type>
      <name>range</name>
      <anchorfile>classTeko_1_1ReorderedLinearOp.html</anchorfile>
      <anchor>a81ba51d74b65e214e6ddc744aff06026</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual VectorSpace</type>
      <name>domain</name>
      <anchorfile>classTeko_1_1ReorderedLinearOp.html</anchorfile>
      <anchor>a9ac07d12d57fd3b859f344a8eaf1a295</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>implicitApply</name>
      <anchorfile>classTeko_1_1ReorderedLinearOp.html</anchorfile>
      <anchor>a3060b5f58ddcf3f536633ff4db423e95</anchor>
      <arglist>(const MultiVector &amp;x, MultiVector &amp;y, const double alpha=1.0, const double beta=0.0) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Teko::RequestCallback</name>
    <filename>classTeko_1_1RequestCallback.html</filename>
    <templarg></templarg>
    <base>Teko::RequestCallbackBase</base>
    <member kind="function" virtualness="pure">
      <type>virtual DataT</type>
      <name>request</name>
      <anchorfile>classTeko_1_1RequestCallback.html</anchorfile>
      <anchor>a936e24e300eb7720586ba5079fd8c4fb</anchor>
      <arglist>(const RequestMesg &amp;)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>handlesRequest</name>
      <anchorfile>classTeko_1_1RequestCallback.html</anchorfile>
      <anchor>a82211ec04dc3a9f06913769e4af4bda2</anchor>
      <arglist>(const RequestMesg &amp;)=0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Teko::RequestCallbackBase</name>
    <filename>classTeko_1_1RequestCallbackBase.html</filename>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>handlesRequest</name>
      <anchorfile>classTeko_1_1RequestCallbackBase.html</anchorfile>
      <anchor>ae599a7f3181e4614d90de864a4353664</anchor>
      <arglist>(const RequestMesg &amp;)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>preRequest</name>
      <anchorfile>classTeko_1_1RequestCallbackBase.html</anchorfile>
      <anchor>a1bd82cca9dd4d9ed93935605cade33cd</anchor>
      <arglist>(const RequestMesg &amp;)=0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Teko::RequestHandler</name>
    <filename>classTeko_1_1RequestHandler.html</filename>
    <member kind="function">
      <type>void</type>
      <name>addRequestCallback</name>
      <anchorfile>classTeko_1_1RequestHandler.html</anchorfile>
      <anchor>a7367e3be7108d5b1851d48641c869b67</anchor>
      <arglist>(const Teuchos::RCP&lt; RequestCallbackBase &gt; &amp;callback)</arglist>
    </member>
    <member kind="function">
      <type>DataT</type>
      <name>request</name>
      <anchorfile>classTeko_1_1RequestHandler.html</anchorfile>
      <anchor>ae855b1e64d9981615bd0a1ba7bd3c022</anchor>
      <arglist>(const RequestMesg &amp;rm) const </arglist>
    </member>
    <member kind="function">
      <type>DataT</type>
      <name>request</name>
      <anchorfile>classTeko_1_1RequestHandler.html</anchorfile>
      <anchor>a2661ae8f00d01956a64d1a6f584eb27a</anchor>
      <arglist>(const std::string &amp;rm) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>preRequest</name>
      <anchorfile>classTeko_1_1RequestHandler.html</anchorfile>
      <anchor>a358a5cdff1daf49c04c166935ca87f77</anchor>
      <arglist>(const RequestMesg &amp;rm) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>preRequest</name>
      <anchorfile>classTeko_1_1RequestHandler.html</anchorfile>
      <anchor>a0863ca11aa244a784ad230a811653034</anchor>
      <arglist>(const std::string &amp;rm) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Teko::RequestHandlerContainer</name>
    <filename>classTeko_1_1RequestHandlerContainer.html</filename>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>setRequestHandler</name>
      <anchorfile>classTeko_1_1RequestHandlerContainer.html</anchorfile>
      <anchor>ae42e7000c796da555d3a3779d6fd0535</anchor>
      <arglist>(const Teuchos::RCP&lt; RequestHandler &gt; &amp;rh)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual Teuchos::RCP&lt; RequestHandler &gt;</type>
      <name>getRequestHandler</name>
      <anchorfile>classTeko_1_1RequestHandlerContainer.html</anchorfile>
      <anchor>a02278862b5ff75f5fd313d0b0503a772</anchor>
      <arglist>() const  =0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Teko::NS::SIMPLEPreconditionerFactory</name>
    <filename>classTeko_1_1NS_1_1SIMPLEPreconditionerFactory.html</filename>
    <base>Teko::BlockPreconditionerFactory</base>
    <member kind="function">
      <type></type>
      <name>SIMPLEPreconditionerFactory</name>
      <anchorfile>classTeko_1_1NS_1_1SIMPLEPreconditionerFactory.html</anchorfile>
      <anchor>a2e533bc0592aca0f69a5cec2f8340753</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>LinearOp</type>
      <name>buildPreconditionerOperator</name>
      <anchorfile>classTeko_1_1NS_1_1SIMPLEPreconditionerFactory.html</anchorfile>
      <anchor>abf3910e907f13553bf282de44c1ae33d</anchor>
      <arglist>(BlockedLinearOp &amp;blo, BlockPreconditionerState &amp;state) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>setMassMatrix</name>
      <anchorfile>classTeko_1_1NS_1_1SIMPLEPreconditionerFactory.html</anchorfile>
      <anchor>ab2d9eb25a2b34a15e28899536d539399</anchor>
      <arglist>(Teko::LinearOp &amp;mass)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual Teuchos::RCP&lt; Teuchos::ParameterList &gt;</type>
      <name>getRequestedParameters</name>
      <anchorfile>classTeko_1_1NS_1_1SIMPLEPreconditionerFactory.html</anchorfile>
      <anchor>a9e4d9104e0c4bff9d7b45e427dd4b551</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>updateRequestedParameters</name>
      <anchorfile>classTeko_1_1NS_1_1SIMPLEPreconditionerFactory.html</anchorfile>
      <anchor>a5fd6675995c7ffcb8ec7074455b9906e</anchor>
      <arglist>(const Teuchos::ParameterList &amp;pl)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>initializeFromParameterList</name>
      <anchorfile>classTeko_1_1NS_1_1SIMPLEPreconditionerFactory.html</anchorfile>
      <anchor>a7ca1386a5567a88b03e500398e65f71d</anchor>
      <arglist>(const Teuchos::ParameterList &amp;pl)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>Teko::mlutils::SmootherData</name>
    <filename>structTeko_1_1mlutils_1_1SmootherData.html</filename>
  </compound>
  <compound kind="class">
    <name>Teko::SmootherLinearOp</name>
    <filename>classTeko_1_1SmootherLinearOp.html</filename>
    <base>Teko::ImplicitLinearOp</base>
    <base>Teko::RequestHandlerContainer</base>
    <member kind="function" virtualness="virtual">
      <type>virtual VectorSpace</type>
      <name>range</name>
      <anchorfile>classTeko_1_1SmootherLinearOp.html</anchorfile>
      <anchor>acd1911dcb1cf054f3db7609384592136</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual VectorSpace</type>
      <name>domain</name>
      <anchorfile>classTeko_1_1SmootherLinearOp.html</anchorfile>
      <anchor>a3b3ab6f73c81ae8f7b4cef4eb229178a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>implicitApply</name>
      <anchorfile>classTeko_1_1SmootherLinearOp.html</anchorfile>
      <anchor>a055111d66b1a493c863db6d63f9aa123</anchor>
      <arglist>(const MultiVector &amp;x, MultiVector &amp;y, const double alpha=1.0, const double beta=0.0) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>setRequestHandler</name>
      <anchorfile>classTeko_1_1SmootherLinearOp.html</anchorfile>
      <anchor>a55e918b5302becbc451fbbaea8d2a2ce</anchor>
      <arglist>(const Teuchos::RCP&lt; RequestHandler &gt; &amp;rh)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual Teuchos::RCP&lt; RequestHandler &gt;</type>
      <name>getRequestHandler</name>
      <anchorfile>classTeko_1_1SmootherLinearOp.html</anchorfile>
      <anchor>a426b7fa334a152b5e2bdcc2979769317</anchor>
      <arglist>() const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Teko::StaticInvDiagStrategy</name>
    <filename>classTeko_1_1StaticInvDiagStrategy.html</filename>
    <base>Teko::BlockInvDiagonalStrategy</base>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>getInvD</name>
      <anchorfile>classTeko_1_1StaticInvDiagStrategy.html</anchorfile>
      <anchor>a389574df296c60459e496a9f1600c67a</anchor>
      <arglist>(const BlockedLinearOp &amp;A, BlockPreconditionerState &amp;state, std::vector&lt; LinearOp &gt; &amp;invDiag) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Teko::StaticLU2x2Strategy</name>
    <filename>classTeko_1_1StaticLU2x2Strategy.html</filename>
    <base>Teko::LU2x2Strategy</base>
    <member kind="function">
      <type></type>
      <name>StaticLU2x2Strategy</name>
      <anchorfile>classTeko_1_1StaticLU2x2Strategy.html</anchorfile>
      <anchor>a9220ad0f57a9c5e714d668766547af06</anchor>
      <arglist>(const Teko::LinearOp &amp;hInvA00, const Teko::LinearOp &amp;tInvA00, const Teko::LinearOp &amp;invS)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const Teko::LinearOp</type>
      <name>getHatInvA00</name>
      <anchorfile>classTeko_1_1StaticLU2x2Strategy.html</anchorfile>
      <anchor>a8083aa9e405dcfe02f297c34ebacbdf7</anchor>
      <arglist>(const Teko::BlockedLinearOp &amp;A, BlockPreconditionerState &amp;state) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const Teko::LinearOp</type>
      <name>getTildeInvA00</name>
      <anchorfile>classTeko_1_1StaticLU2x2Strategy.html</anchorfile>
      <anchor>a002209f0f281d050f973ebb1d06a00d2</anchor>
      <arglist>(const Teko::BlockedLinearOp &amp;A, BlockPreconditionerState &amp;state) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const Teko::LinearOp</type>
      <name>getInvS</name>
      <anchorfile>classTeko_1_1StaticLU2x2Strategy.html</anchorfile>
      <anchor>af88ca2f14eb61965b10925f8308c2890</anchor>
      <arglist>(const Teko::BlockedLinearOp &amp;A, BlockPreconditionerState &amp;state) const </arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>const Teko::LinearOp</type>
      <name>hatInvA00_</name>
      <anchorfile>classTeko_1_1StaticLU2x2Strategy.html</anchorfile>
      <anchor>a338806ac5a77b17db846aa81d4433961</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>const Teko::LinearOp</type>
      <name>tildeInvA00_</name>
      <anchorfile>classTeko_1_1StaticLU2x2Strategy.html</anchorfile>
      <anchor>a7b9c673fe468cd9fb777077efdaa6bbe</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>const Teko::LinearOp</type>
      <name>invS_</name>
      <anchorfile>classTeko_1_1StaticLU2x2Strategy.html</anchorfile>
      <anchor>adfca88789f4cee5eaf430262a7aa8bd7</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const Teko::LinearOp</type>
      <name>getHatInvA00</name>
      <anchorfile>classTeko_1_1StaticLU2x2Strategy.html</anchorfile>
      <anchor>a8083aa9e405dcfe02f297c34ebacbdf7</anchor>
      <arglist>(const Teko::BlockedLinearOp &amp;A, BlockPreconditionerState &amp;state) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const Teko::LinearOp</type>
      <name>getTildeInvA00</name>
      <anchorfile>classTeko_1_1StaticLU2x2Strategy.html</anchorfile>
      <anchor>a002209f0f281d050f973ebb1d06a00d2</anchor>
      <arglist>(const Teko::BlockedLinearOp &amp;A, BlockPreconditionerState &amp;state) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const Teko::LinearOp</type>
      <name>getInvS</name>
      <anchorfile>classTeko_1_1StaticLU2x2Strategy.html</anchorfile>
      <anchor>af88ca2f14eb61965b10925f8308c2890</anchor>
      <arglist>(const Teko::BlockedLinearOp &amp;A, BlockPreconditionerState &amp;state) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Teko::StaticRequestCallback</name>
    <filename>classTeko_1_1StaticRequestCallback.html</filename>
    <templarg></templarg>
    <base>Teko::RequestCallback</base>
    <member kind="function">
      <type>DataT</type>
      <name>request</name>
      <anchorfile>classTeko_1_1StaticRequestCallback.html</anchorfile>
      <anchor>ac16d3b92c53e28fcf6c76c09d2cd25f6</anchor>
      <arglist>(const RequestMesg &amp;rm)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>preRequest</name>
      <anchorfile>classTeko_1_1StaticRequestCallback.html</anchorfile>
      <anchor>ac10ad6c09b10bc41931e089f1f158ba1</anchor>
      <arglist>(const RequestMesg &amp;rm)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>handlesRequest</name>
      <anchorfile>classTeko_1_1StaticRequestCallback.html</anchorfile>
      <anchor>a2f421bf3d0c7b8395a5f6d9551d0bd9b</anchor>
      <arglist>(const RequestMesg &amp;rm)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Teko::StratimikosFactory</name>
    <filename>classTeko_1_1StratimikosFactory.html</filename>
    <member kind="function">
      <type>void</type>
      <name>initializePrec_Thyra</name>
      <anchorfile>classTeko_1_1StratimikosFactory.html</anchorfile>
      <anchor>aee783e6cd26ca74d589f8cc49b80d67c</anchor>
      <arglist>(const Teuchos::RCP&lt; const Thyra::LinearOpSourceBase&lt; double &gt; &gt; &amp;fwdOp, Thyra::PreconditionerBase&lt; double &gt; *prec, const Thyra::ESupportSolveUse supportSolveUse) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initializePrec_Epetra</name>
      <anchorfile>classTeko_1_1StratimikosFactory.html</anchorfile>
      <anchor>a6b17c888ad35d0c210047ae39e0891d4</anchor>
      <arglist>(const Teuchos::RCP&lt; const Thyra::LinearOpSourceBase&lt; double &gt; &gt; &amp;fwdOp, Thyra::PreconditionerBase&lt; double &gt; *prec, const Thyra::ESupportSolveUse supportSolveUse) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setRequestHandler</name>
      <anchorfile>classTeko_1_1StratimikosFactory.html</anchorfile>
      <anchor>ab4d20a6a9f9ae0a2b8f5988a69916d17</anchor>
      <arglist>(const Teuchos::RCP&lt; Teko::RequestHandler &gt; &amp;rh)</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; Teko::RequestHandler &gt;</type>
      <name>getRequestHandler</name>
      <anchorfile>classTeko_1_1StratimikosFactory.html</anchorfile>
      <anchor>afc6ecbc19ec25c55d5eec7c5fb425c91</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const std::vector&lt; int &gt; &amp;</type>
      <name>getDecomposition</name>
      <anchorfile>classTeko_1_1StratimikosFactory.html</anchorfile>
      <anchor>a2c0b100d949701c7910e1bc82fcb284b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>StratimikosFactory</name>
      <anchorfile>classTeko_1_1StratimikosFactory.html</anchorfile>
      <anchor>accd1cf70be3f54ffa0c7bd7083fc70d6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_COMPOSITION_MEMBERS</name>
      <anchorfile>classTeko_1_1StratimikosFactory.html</anchorfile>
      <anchor>aaf898f3b03f25f2f96784c4d94ddb73a</anchor>
      <arglist>(Thyra::EpetraOperatorViewExtractorBase, epetraFwdOpViewExtractor)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isCompatible</name>
      <anchorfile>classTeko_1_1StratimikosFactory.html</anchorfile>
      <anchor>aeec201ab86296a6695880c47647c0faf</anchor>
      <arglist>(const Thyra::LinearOpSourceBase&lt; double &gt; &amp;fwdOp) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>applySupportsConj</name>
      <anchorfile>classTeko_1_1StratimikosFactory.html</anchorfile>
      <anchor>a827181cafce06846f000d84631095009</anchor>
      <arglist>(Thyra::EConj conj) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>applyTransposeSupportsConj</name>
      <anchorfile>classTeko_1_1StratimikosFactory.html</anchorfile>
      <anchor>af0dc076d9952cb7fc5c607a85f76d687</anchor>
      <arglist>(Thyra::EConj conj) const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; Thyra::PreconditionerBase&lt; double &gt; &gt;</type>
      <name>createPrec</name>
      <anchorfile>classTeko_1_1StratimikosFactory.html</anchorfile>
      <anchor>a89123081bdb34c20ceed64b76404057d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initializePrec</name>
      <anchorfile>classTeko_1_1StratimikosFactory.html</anchorfile>
      <anchor>a2024d260e8471ad79cdc587fbb6acfcf</anchor>
      <arglist>(const Teuchos::RCP&lt; const Thyra::LinearOpSourceBase&lt; double &gt; &gt; &amp;fwdOp, Thyra::PreconditionerBase&lt; double &gt; *prec, const Thyra::ESupportSolveUse supportSolveUse) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>uninitializePrec</name>
      <anchorfile>classTeko_1_1StratimikosFactory.html</anchorfile>
      <anchor>a2664688e1bc3f43794beca28cb4010ec</anchor>
      <arglist>(Thyra::PreconditionerBase&lt; double &gt; *prec, Teuchos::RCP&lt; const Thyra::LinearOpSourceBase&lt; double &gt; &gt; *fwdOp, Thyra::ESupportSolveUse *supportSolveUse) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setParameterList</name>
      <anchorfile>classTeko_1_1StratimikosFactory.html</anchorfile>
      <anchor>a63fa1207dd9f4e1232583373f544c1cf</anchor>
      <arglist>(Teuchos::RCP&lt; Teuchos::ParameterList &gt; const &amp;paramList)</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; Teuchos::ParameterList &gt;</type>
      <name>getNonconstParameterList</name>
      <anchorfile>classTeko_1_1StratimikosFactory.html</anchorfile>
      <anchor>aaa618b27692cee444af571d4f34c14a2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; Teuchos::ParameterList &gt;</type>
      <name>unsetParameterList</name>
      <anchorfile>classTeko_1_1StratimikosFactory.html</anchorfile>
      <anchor>ac98d2e98307f8a3ca098baa643b59ce2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Teuchos::ParameterList &gt;</type>
      <name>getParameterList</name>
      <anchorfile>classTeko_1_1StratimikosFactory.html</anchorfile>
      <anchor>aec07120c6a684bd1a374fcc8474e1f5b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Teuchos::ParameterList &gt;</type>
      <name>getValidParameters</name>
      <anchorfile>classTeko_1_1StratimikosFactory.html</anchorfile>
      <anchor>a46df7c2db0af907f6e166716dc4a7890</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>description</name>
      <anchorfile>classTeko_1_1StratimikosFactory.html</anchorfile>
      <anchor>a56c001ae0c73cf30e352281ce6da049e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>StratimikosFactory</name>
      <anchorfile>classTeko_1_1StratimikosFactory.html</anchorfile>
      <anchor>accd1cf70be3f54ffa0c7bd7083fc70d6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_COMPOSITION_MEMBERS</name>
      <anchorfile>classTeko_1_1StratimikosFactory.html</anchorfile>
      <anchor>aaf898f3b03f25f2f96784c4d94ddb73a</anchor>
      <arglist>(Thyra::EpetraOperatorViewExtractorBase, epetraFwdOpViewExtractor)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isCompatible</name>
      <anchorfile>classTeko_1_1StratimikosFactory.html</anchorfile>
      <anchor>aeec201ab86296a6695880c47647c0faf</anchor>
      <arglist>(const Thyra::LinearOpSourceBase&lt; double &gt; &amp;fwdOp) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>applySupportsConj</name>
      <anchorfile>classTeko_1_1StratimikosFactory.html</anchorfile>
      <anchor>a827181cafce06846f000d84631095009</anchor>
      <arglist>(Thyra::EConj conj) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>applyTransposeSupportsConj</name>
      <anchorfile>classTeko_1_1StratimikosFactory.html</anchorfile>
      <anchor>af0dc076d9952cb7fc5c607a85f76d687</anchor>
      <arglist>(Thyra::EConj conj) const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; Thyra::PreconditionerBase&lt; double &gt; &gt;</type>
      <name>createPrec</name>
      <anchorfile>classTeko_1_1StratimikosFactory.html</anchorfile>
      <anchor>a89123081bdb34c20ceed64b76404057d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initializePrec</name>
      <anchorfile>classTeko_1_1StratimikosFactory.html</anchorfile>
      <anchor>a2024d260e8471ad79cdc587fbb6acfcf</anchor>
      <arglist>(const Teuchos::RCP&lt; const Thyra::LinearOpSourceBase&lt; double &gt; &gt; &amp;fwdOp, Thyra::PreconditionerBase&lt; double &gt; *prec, const Thyra::ESupportSolveUse supportSolveUse) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>uninitializePrec</name>
      <anchorfile>classTeko_1_1StratimikosFactory.html</anchorfile>
      <anchor>a2664688e1bc3f43794beca28cb4010ec</anchor>
      <arglist>(Thyra::PreconditionerBase&lt; double &gt; *prec, Teuchos::RCP&lt; const Thyra::LinearOpSourceBase&lt; double &gt; &gt; *fwdOp, Thyra::ESupportSolveUse *supportSolveUse) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setParameterList</name>
      <anchorfile>classTeko_1_1StratimikosFactory.html</anchorfile>
      <anchor>a63fa1207dd9f4e1232583373f544c1cf</anchor>
      <arglist>(Teuchos::RCP&lt; Teuchos::ParameterList &gt; const &amp;paramList)</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; Teuchos::ParameterList &gt;</type>
      <name>getNonconstParameterList</name>
      <anchorfile>classTeko_1_1StratimikosFactory.html</anchorfile>
      <anchor>aaa618b27692cee444af571d4f34c14a2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; Teuchos::ParameterList &gt;</type>
      <name>unsetParameterList</name>
      <anchorfile>classTeko_1_1StratimikosFactory.html</anchorfile>
      <anchor>ac98d2e98307f8a3ca098baa643b59ce2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Teuchos::ParameterList &gt;</type>
      <name>getParameterList</name>
      <anchorfile>classTeko_1_1StratimikosFactory.html</anchorfile>
      <anchor>aec07120c6a684bd1a374fcc8474e1f5b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Teuchos::ParameterList &gt;</type>
      <name>getValidParameters</name>
      <anchorfile>classTeko_1_1StratimikosFactory.html</anchorfile>
      <anchor>a46df7c2db0af907f6e166716dc4a7890</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>description</name>
      <anchorfile>classTeko_1_1StratimikosFactory.html</anchorfile>
      <anchor>a56c001ae0c73cf30e352281ce6da049e</anchor>
      <arglist>() const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Teko::NS::TimingsSIMPLEPreconditionerFactory</name>
    <filename>classTeko_1_1NS_1_1TimingsSIMPLEPreconditionerFactory.html</filename>
    <base>Teko::BlockPreconditionerFactory</base>
    <member kind="function">
      <type></type>
      <name>TimingsSIMPLEPreconditionerFactory</name>
      <anchorfile>classTeko_1_1NS_1_1TimingsSIMPLEPreconditionerFactory.html</anchorfile>
      <anchor>ac25e6fea4ce7204af9c3d20a1e0c1d19</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~TimingsSIMPLEPreconditionerFactory</name>
      <anchorfile>classTeko_1_1NS_1_1TimingsSIMPLEPreconditionerFactory.html</anchorfile>
      <anchor>ad0420354a746f0d4605f7b20578bcc6e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>LinearOp</type>
      <name>buildPreconditionerOperator</name>
      <anchorfile>classTeko_1_1NS_1_1TimingsSIMPLEPreconditionerFactory.html</anchorfile>
      <anchor>af1886b295f6f95687af55e164207876a</anchor>
      <arglist>(BlockedLinearOp &amp;blo, BlockPreconditionerState &amp;state) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>setMassMatrix</name>
      <anchorfile>classTeko_1_1NS_1_1TimingsSIMPLEPreconditionerFactory.html</anchorfile>
      <anchor>acea4e4ef0941c696e4068bb29d009069</anchor>
      <arglist>(Teko::LinearOp &amp;mass)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual Teuchos::RCP&lt; Teuchos::ParameterList &gt;</type>
      <name>getRequestedParameters</name>
      <anchorfile>classTeko_1_1NS_1_1TimingsSIMPLEPreconditionerFactory.html</anchorfile>
      <anchor>a6eba4206dd6890c10efec0de29899bd9</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>updateRequestedParameters</name>
      <anchorfile>classTeko_1_1NS_1_1TimingsSIMPLEPreconditionerFactory.html</anchorfile>
      <anchor>a1667c478e6374161cecd00424597e9bf</anchor>
      <arglist>(const Teuchos::ParameterList &amp;pl)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>initializeFromParameterList</name>
      <anchorfile>classTeko_1_1NS_1_1TimingsSIMPLEPreconditionerFactory.html</anchorfile>
      <anchor>a6b69c4a636b544bcba0f99f95976b182</anchor>
      <arglist>(const Teuchos::ParameterList &amp;pl)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Teko::TpetraHelpers::TpetraBlockPreconditioner</name>
    <filename>classTeko_1_1TpetraHelpers_1_1TpetraBlockPreconditioner.html</filename>
    <member kind="function">
      <type></type>
      <name>TpetraBlockPreconditioner</name>
      <anchorfile>classTeko_1_1TpetraHelpers_1_1TpetraBlockPreconditioner.html</anchorfile>
      <anchor>a00b58c208648eb2205e5434ce76dd8d6</anchor>
      <arglist>(const Teuchos::RCP&lt; const PreconditionerFactory &gt; &amp;bfp)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>initPreconditioner</name>
      <anchorfile>classTeko_1_1TpetraHelpers_1_1TpetraBlockPreconditioner.html</anchorfile>
      <anchor>a36e3429c156c37afb16d126957a762e9</anchor>
      <arglist>(bool clearOld=false)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>buildPreconditioner</name>
      <anchorfile>classTeko_1_1TpetraHelpers_1_1TpetraBlockPreconditioner.html</anchorfile>
      <anchor>a5984541c40d6d45c3b3abcb7a2c055ac</anchor>
      <arglist>(const Teuchos::RCP&lt; const Tpetra::Operator&lt; ST, LO, GO, NT &gt; &gt; &amp;A, bool clear=true)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>buildPreconditioner</name>
      <anchorfile>classTeko_1_1TpetraHelpers_1_1TpetraBlockPreconditioner.html</anchorfile>
      <anchor>a584b93b9f66c87bdd266e570a7aa6769</anchor>
      <arglist>(const Teuchos::RCP&lt; const Tpetra::Operator&lt; ST, LO, GO, NT &gt; &gt; &amp;A, const Tpetra::MultiVector&lt; ST, LO, GO, NT &gt; &amp;mv, bool clear=true)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>rebuildPreconditioner</name>
      <anchorfile>classTeko_1_1TpetraHelpers_1_1TpetraBlockPreconditioner.html</anchorfile>
      <anchor>a6d2520da18da3dfd5b690a43f51c81f4</anchor>
      <arglist>(const Teuchos::RCP&lt; const Tpetra::Operator&lt; ST, LO, GO, NT &gt; &gt; &amp;A)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>rebuildPreconditioner</name>
      <anchorfile>classTeko_1_1TpetraHelpers_1_1TpetraBlockPreconditioner.html</anchorfile>
      <anchor>a91aac3f5ce12559345e7c23cf4ed9c69</anchor>
      <arglist>(const Teuchos::RCP&lt; const Tpetra::Operator&lt; ST, LO, GO, NT &gt; &gt; &amp;A, const Tpetra::MultiVector&lt; ST, LO, GO, NT &gt; &amp;mv)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual Teuchos::RCP&lt; PreconditionerState &gt;</type>
      <name>getPreconditionerState</name>
      <anchorfile>classTeko_1_1TpetraHelpers_1_1TpetraBlockPreconditioner.html</anchorfile>
      <anchor>a00dd2ac2fe229574482bc5f2f00df505</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual Teuchos::RCP&lt; const PreconditionerState &gt;</type>
      <name>getPreconditionerState</name>
      <anchorfile>classTeko_1_1TpetraHelpers_1_1TpetraBlockPreconditioner.html</anchorfile>
      <anchor>a6316a82633b67e7e00217893a199510d</anchor>
      <arglist>() const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Teko::TpetraHelpers::TpetraOperatorWrapper</name>
    <filename>classTeko_1_1TpetraHelpers_1_1TpetraOperatorWrapper.html</filename>
    <member kind="function">
      <type>const RCP&lt; const Thyra::LinearOpBase&lt; ST &gt; &gt;</type>
      <name>getThyraOp</name>
      <anchorfile>classTeko_1_1TpetraHelpers_1_1TpetraOperatorWrapper.html</anchorfile>
      <anchor>a7ab5b7b67bfa38ae0eafdfc602000ee1</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const RCP&lt; const MappingStrategy &gt;</type>
      <name>getMapStrategy</name>
      <anchorfile>classTeko_1_1TpetraHelpers_1_1TpetraOperatorWrapper.html</anchorfile>
      <anchor>afe701b2651d39b461d7db6ee9a271585</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>GetBlockRowCount</name>
      <anchorfile>classTeko_1_1TpetraHelpers_1_1TpetraOperatorWrapper.html</anchorfile>
      <anchor>aa001c1437c40fb705d4e383b3d035035</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>GetBlockColCount</name>
      <anchorfile>classTeko_1_1TpetraHelpers_1_1TpetraOperatorWrapper.html</anchorfile>
      <anchor>ad82a3ee60332fcd53ae45759db1545cd</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Tpetra::Operator&lt; ST, LO, GO, NT &gt; &gt;</type>
      <name>GetBlock</name>
      <anchorfile>classTeko_1_1TpetraHelpers_1_1TpetraOperatorWrapper.html</anchorfile>
      <anchor>a2e3cc6574067acebb6479caf5d26219c</anchor>
      <arglist>(int i, int j) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Teko::Epetra::ZeroedOperator</name>
    <filename>classTeko_1_1Epetra_1_1ZeroedOperator.html</filename>
    <member kind="function">
      <type></type>
      <name>ZeroedOperator</name>
      <anchorfile>classTeko_1_1Epetra_1_1ZeroedOperator.html</anchorfile>
      <anchor>a3c36b743ebe4f05c55d296cc72999a60</anchor>
      <arglist>(const std::vector&lt; int &gt; &amp;zeroIndices, const Teuchos::RCP&lt; const Epetra_Operator &gt; &amp;op)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~ZeroedOperator</name>
      <anchorfile>classTeko_1_1Epetra_1_1ZeroedOperator.html</anchorfile>
      <anchor>a6ee39f4b255658bbce702c35d38f443e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetUseTranspose</name>
      <anchorfile>classTeko_1_1Epetra_1_1ZeroedOperator.html</anchorfile>
      <anchor>a8db0f8d0d0ff1154ec64ce1d698edea6</anchor>
      <arglist>(bool)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Apply</name>
      <anchorfile>classTeko_1_1Epetra_1_1ZeroedOperator.html</anchorfile>
      <anchor>a774ffeafaaab63beb456bab7c73c3966</anchor>
      <arglist>(const Epetra_MultiVector &amp;X, Epetra_MultiVector &amp;Y) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ApplyInverse</name>
      <anchorfile>classTeko_1_1Epetra_1_1ZeroedOperator.html</anchorfile>
      <anchor>a147dbfe7e447d478c50ddc7ced850355</anchor>
      <arglist>(const Epetra_MultiVector &amp;X, Epetra_MultiVector &amp;Y) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~ZeroedOperator</name>
      <anchorfile>classTeko_1_1Epetra_1_1ZeroedOperator.html</anchorfile>
      <anchor>a6ee39f4b255658bbce702c35d38f443e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetUseTranspose</name>
      <anchorfile>classTeko_1_1Epetra_1_1ZeroedOperator.html</anchorfile>
      <anchor>a8db0f8d0d0ff1154ec64ce1d698edea6</anchor>
      <arglist>(bool)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Apply</name>
      <anchorfile>classTeko_1_1Epetra_1_1ZeroedOperator.html</anchorfile>
      <anchor>a774ffeafaaab63beb456bab7c73c3966</anchor>
      <arglist>(const Epetra_MultiVector &amp;X, Epetra_MultiVector &amp;Y) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ApplyInverse</name>
      <anchorfile>classTeko_1_1Epetra_1_1ZeroedOperator.html</anchorfile>
      <anchor>a147dbfe7e447d478c50ddc7ced850355</anchor>
      <arglist>(const Epetra_MultiVector &amp;X, Epetra_MultiVector &amp;Y) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Teko::TpetraHelpers::ZeroedOperator</name>
    <filename>classTeko_1_1TpetraHelpers_1_1ZeroedOperator.html</filename>
    <member kind="function">
      <type></type>
      <name>ZeroedOperator</name>
      <anchorfile>classTeko_1_1TpetraHelpers_1_1ZeroedOperator.html</anchorfile>
      <anchor>ad28bdd9eaeac4a98eea028ef71c59ddb</anchor>
      <arglist>(const std::vector&lt; GO &gt; &amp;zeroIndices, const Teuchos::RCP&lt; const Tpetra::Operator&lt; ST, LO, GO, NT &gt; &gt; &amp;op)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~ZeroedOperator</name>
      <anchorfile>classTeko_1_1TpetraHelpers_1_1ZeroedOperator.html</anchorfile>
      <anchor>a07ff2d08d81ca030aad861ee85173abc</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetUseTranspose</name>
      <anchorfile>classTeko_1_1TpetraHelpers_1_1ZeroedOperator.html</anchorfile>
      <anchor>a01344822a42fc756891f991eca1ca14a</anchor>
      <arglist>(bool)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>apply</name>
      <anchorfile>classTeko_1_1TpetraHelpers_1_1ZeroedOperator.html</anchorfile>
      <anchor>a7d9393cf978737f6f956cc9ccb88ddf5</anchor>
      <arglist>(const Tpetra::MultiVector&lt; ST, LO, GO, NT &gt; &amp;X, Tpetra::MultiVector&lt; ST, LO, GO, NT &gt; &amp;Y, Teuchos::ETransp mode=Teuchos::NO_TRANS, ST alpha=Teuchos::ScalarTraits&lt; ST &gt;::one(), ST beta=Teuchos::ScalarTraits&lt; ST &gt;::zero()) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>applyInverse</name>
      <anchorfile>classTeko_1_1TpetraHelpers_1_1ZeroedOperator.html</anchorfile>
      <anchor>a983740a28ba90556f3a28b7d3b96102f</anchor>
      <arglist>(const Tpetra::MultiVector&lt; ST, LO, GO, NT &gt; &amp;X, Tpetra::MultiVector&lt; ST, LO, GO, NT &gt; &amp;Y, Teuchos::ETransp mode=Teuchos::NO_TRANS, ST alpha=Teuchos::ScalarTraits&lt; ST &gt;::one(), ST beta=Teuchos::ScalarTraits&lt; ST &gt;::zero()) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~ZeroedOperator</name>
      <anchorfile>classTeko_1_1TpetraHelpers_1_1ZeroedOperator.html</anchorfile>
      <anchor>a07ff2d08d81ca030aad861ee85173abc</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetUseTranspose</name>
      <anchorfile>classTeko_1_1TpetraHelpers_1_1ZeroedOperator.html</anchorfile>
      <anchor>a01344822a42fc756891f991eca1ca14a</anchor>
      <arglist>(bool)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>apply</name>
      <anchorfile>classTeko_1_1TpetraHelpers_1_1ZeroedOperator.html</anchorfile>
      <anchor>a7d9393cf978737f6f956cc9ccb88ddf5</anchor>
      <arglist>(const Tpetra::MultiVector&lt; ST, LO, GO, NT &gt; &amp;X, Tpetra::MultiVector&lt; ST, LO, GO, NT &gt; &amp;Y, Teuchos::ETransp mode=Teuchos::NO_TRANS, ST alpha=Teuchos::ScalarTraits&lt; ST &gt;::one(), ST beta=Teuchos::ScalarTraits&lt; ST &gt;::zero()) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>applyInverse</name>
      <anchorfile>classTeko_1_1TpetraHelpers_1_1ZeroedOperator.html</anchorfile>
      <anchor>a983740a28ba90556f3a28b7d3b96102f</anchor>
      <arglist>(const Tpetra::MultiVector&lt; ST, LO, GO, NT &gt; &amp;X, Tpetra::MultiVector&lt; ST, LO, GO, NT &gt; &amp;Y, Teuchos::ETransp mode=Teuchos::NO_TRANS, ST alpha=Teuchos::ScalarTraits&lt; ST &gt;::one(), ST beta=Teuchos::ScalarTraits&lt; ST &gt;::zero()) const </arglist>
    </member>
  </compound>
  <compound kind="page">
    <name>index</name>
    <title>Teko: For block and physics-based preconditioners</title>
    <filename>index</filename>
  </compound>
</tagfile>
