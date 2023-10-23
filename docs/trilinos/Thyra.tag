<?xml version='1.0' encoding='UTF-8' standalone='yes' ?>
<tagfile>
  <compound kind="file">
    <name>Thyra_EpetraThyraWrappers.hpp</name>
    <path>/Users/sscoll/dist/trilinos/packages/thyra/adapters/epetra/src/</path>
    <filename>Thyra__EpetraThyraWrappers_8hpp</filename>
    <member kind="function">
      <type>RCP&lt; const Teuchos::Comm&lt; Ordinal &gt; &gt;</type>
      <name>create_Comm</name>
      <anchorfile>group__Epetra__Thyra__Op__Vec__adapters__grp.html</anchorfile>
      <anchor>ga68f1d41c29d1251b5e171dfb8d876435</anchor>
      <arglist>(const RCP&lt; const Epetra_Comm &gt; &amp;epetraComm)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const VectorSpaceBase&lt; double &gt; &gt;</type>
      <name>create_VectorSpace</name>
      <anchorfile>group__Epetra__Thyra__Op__Vec__adapters__grp.html</anchorfile>
      <anchor>ga6f31a91efce616677a66d162c9b03805</anchor>
      <arglist>(const RCP&lt; const Epetra_Map &gt; &amp;epetra_map)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const VectorSpaceBase&lt; double &gt; &gt;</type>
      <name>create_LocallyReplicatedVectorSpace</name>
      <anchorfile>group__Epetra__Thyra__Op__Vec__adapters__grp.html</anchorfile>
      <anchor>gad20c20b3c0c8c14c5236ea7b7e34fdc1</anchor>
      <arglist>(const RCP&lt; const VectorSpaceBase&lt; double &gt; &gt; &amp;parentSpace, const int dim)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; VectorBase&lt; double &gt; &gt;</type>
      <name>create_Vector</name>
      <anchorfile>group__Epetra__Thyra__Op__Vec__adapters__grp.html</anchorfile>
      <anchor>ga1f3b0bf703c3b35237bac513b3ff5e21</anchor>
      <arglist>(const RCP&lt; Epetra_Vector &gt; &amp;epetra_v, const RCP&lt; const VectorSpaceBase&lt; double &gt; &gt; &amp;space)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const VectorBase&lt; double &gt; &gt;</type>
      <name>create_Vector</name>
      <anchorfile>group__Epetra__Thyra__Op__Vec__adapters__grp.html</anchorfile>
      <anchor>ga84d2b4aec5f2c5980b9b8cc207ca5a08</anchor>
      <arglist>(const RCP&lt; const Epetra_Vector &gt; &amp;epetra_v, const RCP&lt; const VectorSpaceBase&lt; double &gt; &gt; &amp;space)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; MultiVectorBase&lt; double &gt; &gt;</type>
      <name>create_MultiVector</name>
      <anchorfile>group__Epetra__Thyra__Op__Vec__adapters__grp.html</anchorfile>
      <anchor>ga35817c2b80660344e4c3e609653805a2</anchor>
      <arglist>(const RCP&lt; Epetra_MultiVector &gt; &amp;epetra_mv, const RCP&lt; const VectorSpaceBase&lt; double &gt; &gt; &amp;range, const RCP&lt; const VectorSpaceBase&lt; double &gt; &gt; &amp;domain=Teuchos::null)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const MultiVectorBase&lt; double &gt; &gt;</type>
      <name>create_MultiVector</name>
      <anchorfile>group__Epetra__Thyra__Op__Vec__adapters__grp.html</anchorfile>
      <anchor>ga231b01e7764cb7f780cc173e2c8a6cb5</anchor>
      <arglist>(const RCP&lt; const Epetra_MultiVector &gt; &amp;epetra_mv, const RCP&lt; const VectorSpaceBase&lt; double &gt; &gt; &amp;range, const RCP&lt; const VectorSpaceBase&lt; double &gt; &gt; &amp;domain=Teuchos::null)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const Epetra_Comm &gt;</type>
      <name>get_Epetra_Comm</name>
      <anchorfile>group__Epetra__Thyra__Op__Vec__adapters__grp.html</anchorfile>
      <anchor>ga3a1a44a4e90cc4eaf7192f46d66c47b0</anchor>
      <arglist>(const Teuchos::Comm&lt; Ordinal &gt; &amp;comm)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const Epetra_Map &gt;</type>
      <name>get_Epetra_Map</name>
      <anchorfile>group__Epetra__Thyra__Op__Vec__adapters__grp.html</anchorfile>
      <anchor>gaa63557fbffcf1b7190761b47deabd04b</anchor>
      <arglist>(const VectorSpaceBase&lt; double &gt; &amp;vs, const RCP&lt; const Epetra_Comm &gt; &amp;comm)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; Epetra_Vector &gt;</type>
      <name>get_Epetra_Vector</name>
      <anchorfile>group__Epetra__Thyra__Op__Vec__adapters__grp.html</anchorfile>
      <anchor>gaa2c3bd82b0b6ea7e646aa08831aa0252</anchor>
      <arglist>(const Epetra_Map &amp;map, const RCP&lt; VectorBase&lt; double &gt; &gt; &amp;v)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const Epetra_Vector &gt;</type>
      <name>get_Epetra_Vector</name>
      <anchorfile>group__Epetra__Thyra__Op__Vec__adapters__grp.html</anchorfile>
      <anchor>gac98405c4e1407b2967e684d1393955c0</anchor>
      <arglist>(const Epetra_Map &amp;map, const RCP&lt; const VectorBase&lt; double &gt; &gt; &amp;v)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; Epetra_MultiVector &gt;</type>
      <name>get_Epetra_MultiVector</name>
      <anchorfile>group__Epetra__Thyra__Op__Vec__adapters__grp.html</anchorfile>
      <anchor>gabe4a8cd77325734357b49733f9f751b0</anchor>
      <arglist>(const Epetra_Map &amp;map, const RCP&lt; MultiVectorBase&lt; double &gt; &gt; &amp;mv)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const Epetra_MultiVector &gt;</type>
      <name>get_Epetra_MultiVector</name>
      <anchorfile>group__Epetra__Thyra__Op__Vec__adapters__grp.html</anchorfile>
      <anchor>ga97677e36ca83f50043c0e3db0ff75022</anchor>
      <arglist>(const Epetra_Map &amp;map, const RCP&lt; const MultiVectorBase&lt; double &gt; &gt; &amp;mv)</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; Epetra_MultiVector &gt;</type>
      <name>get_Epetra_MultiVector</name>
      <anchorfile>group__Epetra__Thyra__Op__Vec__adapters__grp.html</anchorfile>
      <anchor>ga50422b34dc6ead91529aa213478632ec</anchor>
      <arglist>(const Epetra_Map &amp;map, MultiVectorBase&lt; double &gt; &amp;mv)</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Epetra_MultiVector &gt;</type>
      <name>get_Epetra_MultiVector</name>
      <anchorfile>group__Epetra__Thyra__Op__Vec__adapters__grp.html</anchorfile>
      <anchor>gab800f5abe4ff1e7cbd2c9230805cae8c</anchor>
      <arglist>(const Epetra_Map &amp;map, const MultiVectorBase&lt; double &gt; &amp;mv)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Thyra_UnitTestHelpers.hpp</name>
    <path>/Users/sscoll/dist/trilinos/packages/thyra/core/src/support/operator_vector/client_support/</path>
    <filename>Thyra__UnitTestHelpers_8hpp</filename>
    <member kind="define">
      <type>#define</type>
      <name>THYRA_UNIT_TEST_TEMPLATE_1_INSTANT_REAL_SCALAR_TYPES</name>
      <anchorfile>Thyra__UnitTestHelpers_8hpp.html</anchorfile>
      <anchor>ac3bceef79d8bdc3e1a149fbaf5c26148</anchor>
      <arglist>(TEST_GROUP, TEST_NAME)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>THYRA_UNIT_TEST_TEMPLATE_1_INSTANT_SCALAR_TYPES</name>
      <anchorfile>Thyra__UnitTestHelpers_8hpp.html</anchorfile>
      <anchor>ae36c01aec18243083e67f58684f4f0e1</anchor>
      <arglist>(TEST_GROUP, TEST_NAME)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::AddedLinearOpBase</name>
    <filename>classThyra_1_1AddedLinearOpBase.html</filename>
    <templarg>Scalar</templarg>
    <base virtualness="virtual">Thyra::LinearOpBase</base>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>numOps</name>
      <anchorfile>classThyra_1_1AddedLinearOpBase.html</anchorfile>
      <anchor>a65e4b2e89b9a24797e9782469db88e5e</anchor>
      <arglist>() const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>opIsConst</name>
      <anchorfile>classThyra_1_1AddedLinearOpBase.html</anchorfile>
      <anchor>a25415d6ab5816cbcf98fa1f38ecd42c0</anchor>
      <arglist>(const int k) const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual Teuchos::RCP&lt; LinearOpBase&lt; Scalar &gt; &gt;</type>
      <name>getNonconstOp</name>
      <anchorfile>classThyra_1_1AddedLinearOpBase.html</anchorfile>
      <anchor>aa783fbaa56c97c480f7536defee81495</anchor>
      <arglist>(const int k)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual Teuchos::RCP&lt; const LinearOpBase&lt; Scalar &gt; &gt;</type>
      <name>getOp</name>
      <anchorfile>classThyra_1_1AddedLinearOpBase.html</anchorfile>
      <anchor>a7f3af1874a8de4709050a4e64d00dfdb</anchor>
      <arglist>(const int k) const  =0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::BlockedLinearOpBase</name>
    <filename>classThyra_1_1BlockedLinearOpBase.html</filename>
    <templarg></templarg>
    <base virtualness="virtual">Thyra::LinearOpBase</base>
    <member kind="function" virtualness="pure">
      <type>virtual Teuchos::RCP&lt; const ProductVectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>productRange</name>
      <anchorfile>classThyra_1_1BlockedLinearOpBase.html</anchorfile>
      <anchor>a3e2a6e1202ed23a30c6a7bd085032ea4</anchor>
      <arglist>() const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual Teuchos::RCP&lt; const ProductVectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>productDomain</name>
      <anchorfile>classThyra_1_1BlockedLinearOpBase.html</anchorfile>
      <anchor>ac5670061dddb9c08aee967130366469f</anchor>
      <arglist>() const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>blockExists</name>
      <anchorfile>classThyra_1_1BlockedLinearOpBase.html</anchorfile>
      <anchor>a14bdcc03f4e31244972e054f8326ebdd</anchor>
      <arglist>(const int i, const int j) const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>blockIsConst</name>
      <anchorfile>classThyra_1_1BlockedLinearOpBase.html</anchorfile>
      <anchor>aa76196c9b25b2e6f0a870c06a82e4c5f</anchor>
      <arglist>(const int i, const int j) const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual Teuchos::RCP&lt; LinearOpBase&lt; Scalar &gt; &gt;</type>
      <name>getNonconstBlock</name>
      <anchorfile>classThyra_1_1BlockedLinearOpBase.html</anchorfile>
      <anchor>a9062ba5c68e06dbad1997714fe429ebd</anchor>
      <arglist>(const int i, const int j)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual Teuchos::RCP&lt; const LinearOpBase&lt; Scalar &gt; &gt;</type>
      <name>getBlock</name>
      <anchorfile>classThyra_1_1BlockedLinearOpBase.html</anchorfile>
      <anchor>a402e35fc2af501d1ed26bcc1e74db433</anchor>
      <arglist>(const int i, const int j) const  =0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::BlockedLinearOpWithSolveBase</name>
    <filename>classThyra_1_1BlockedLinearOpWithSolveBase.html</filename>
    <templarg>Scalar</templarg>
    <base virtualness="virtual">Thyra::LinearOpWithSolveBase</base>
    <base virtualness="virtual">Thyra::BlockedLinearOpBase</base>
    <member kind="function" virtualness="pure">
      <type>virtual Teuchos::RCP&lt; LinearOpWithSolveBase&lt; Scalar &gt; &gt;</type>
      <name>getNonconstLOWSBlock</name>
      <anchorfile>classThyra_1_1BlockedLinearOpWithSolveBase.html</anchorfile>
      <anchor>a204f277bcbe83ac812018e845b043ab4</anchor>
      <arglist>(const int i, const int j)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual Teuchos::RCP&lt; const LinearOpWithSolveBase&lt; Scalar &gt; &gt;</type>
      <name>getLOWSBlock</name>
      <anchorfile>classThyra_1_1BlockedLinearOpWithSolveBase.html</anchorfile>
      <anchor>afad566f66f7bad64ad62d3fc3d2d1dc5</anchor>
      <arglist>(const int i, const int j) const  =0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::CatastrophicSolveFailure</name>
    <filename>classThyra_1_1CatastrophicSolveFailure.html</filename>
  </compound>
  <compound kind="class">
    <name>Thyra::ConstDetachedMultiVectorView</name>
    <filename>classThyra_1_1ConstDetachedMultiVectorView.html</filename>
    <templarg>Scalar</templarg>
    <member kind="function">
      <type></type>
      <name>ConstDetachedMultiVectorView</name>
      <anchorfile>classThyra_1_1ConstDetachedMultiVectorView.html</anchorfile>
      <anchor>aa89b7de124dc994f4e8e9d643f2a8953</anchor>
      <arglist>(const RCP&lt; const MultiVectorBase&lt; Scalar &gt; &gt; &amp;mv, const Range1D &amp;rowRng=Range1D(), const Range1D &amp;colRng=Range1D())</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ConstDetachedMultiVectorView</name>
      <anchorfile>classThyra_1_1ConstDetachedMultiVectorView.html</anchorfile>
      <anchor>aeb30f600713d199c7610eeab806ff8df</anchor>
      <arglist>(const MultiVectorBase&lt; Scalar &gt; &amp;mv, const Range1D &amp;rowRng=Range1D(), const Range1D &amp;colRng=Range1D())</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~ConstDetachedMultiVectorView</name>
      <anchorfile>classThyra_1_1ConstDetachedMultiVectorView.html</anchorfile>
      <anchor>ac5a08093d8a1b19377d8489394f4fadb</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const RTOpPack::ConstSubMultiVectorView&lt; Scalar &gt; &amp;</type>
      <name>smv</name>
      <anchorfile>classThyra_1_1ConstDetachedMultiVectorView.html</anchorfile>
      <anchor>a69bc8be91424bb20dfde234fd1ceecee</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Ordinal</type>
      <name>globalOffset</name>
      <anchorfile>classThyra_1_1ConstDetachedMultiVectorView.html</anchorfile>
      <anchor>a452f1010c76097bc15f56a2e6eecfa41</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Ordinal</type>
      <name>subDim</name>
      <anchorfile>classThyra_1_1ConstDetachedMultiVectorView.html</anchorfile>
      <anchor>acd912d478cf74211fb5a7cd4f178f83d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Ordinal</type>
      <name>colOffset</name>
      <anchorfile>classThyra_1_1ConstDetachedMultiVectorView.html</anchorfile>
      <anchor>a9d3df6b18f146e490f5903881f672a4f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Ordinal</type>
      <name>numSubCols</name>
      <anchorfile>classThyra_1_1ConstDetachedMultiVectorView.html</anchorfile>
      <anchor>ab4c366197094acf2cda33df01ab75121</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Scalar *</type>
      <name>values</name>
      <anchorfile>classThyra_1_1ConstDetachedMultiVectorView.html</anchorfile>
      <anchor>aa91588dc7a0f9ef09fd798ac9371d19f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Ordinal</type>
      <name>leadingDim</name>
      <anchorfile>classThyra_1_1ConstDetachedMultiVectorView.html</anchorfile>
      <anchor>a091acc306be3e4d9f8f1fb2ae086cc71</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Scalar &amp;</type>
      <name>operator()</name>
      <anchorfile>classThyra_1_1ConstDetachedMultiVectorView.html</anchorfile>
      <anchor>a574ebdee5d31efe208eb32dd8674ba7b</anchor>
      <arglist>(Ordinal i, Ordinal j) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::ConstDetachedSpmdVectorView</name>
    <filename>classThyra_1_1ConstDetachedSpmdVectorView.html</filename>
    <templarg>Scalar</templarg>
    <member kind="function">
      <type></type>
      <name>ConstDetachedSpmdVectorView</name>
      <anchorfile>classThyra_1_1ConstDetachedSpmdVectorView.html</anchorfile>
      <anchor>ad75a9922dde2f0d30671b30b6b8192b0</anchor>
      <arglist>(const Teuchos::RCP&lt; const VectorBase&lt; Scalar &gt; &gt; &amp;v)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~ConstDetachedSpmdVectorView</name>
      <anchorfile>classThyra_1_1ConstDetachedSpmdVectorView.html</anchorfile>
      <anchor>a2360b7112e21844098c688017034185f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const RCP&lt; const SpmdVectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>spmdSpace</name>
      <anchorfile>classThyra_1_1ConstDetachedSpmdVectorView.html</anchorfile>
      <anchor>ae4511d20c58059d91793f3465b9880e2</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const RTOpPack::ConstSubVectorView&lt; Scalar &gt; &amp;</type>
      <name>sv</name>
      <anchorfile>classThyra_1_1ConstDetachedSpmdVectorView.html</anchorfile>
      <anchor>a43774fe167770f4535fe29ce9a87d11a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos_Ordinal</type>
      <name>globalOffset</name>
      <anchorfile>classThyra_1_1ConstDetachedSpmdVectorView.html</anchorfile>
      <anchor>a63671c1dc0516d5db9ed8cf5540c058e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos_Ordinal</type>
      <name>subDim</name>
      <anchorfile>classThyra_1_1ConstDetachedSpmdVectorView.html</anchorfile>
      <anchor>ae3c0dae2604647773b1343ac3c89b6b8</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const ArrayRCP&lt; const Scalar &gt;</type>
      <name>values</name>
      <anchorfile>classThyra_1_1ConstDetachedSpmdVectorView.html</anchorfile>
      <anchor>ac174ba82f4cbb104f0ba6dded1dd3aa3</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>ptrdiff_t</type>
      <name>stride</name>
      <anchorfile>classThyra_1_1ConstDetachedSpmdVectorView.html</anchorfile>
      <anchor>adf748d14e4abee6bbc28dd01dea08a3b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Scalar &amp;</type>
      <name>operator[]</name>
      <anchorfile>classThyra_1_1ConstDetachedSpmdVectorView.html</anchorfile>
      <anchor>a8f29f36a6a4697167120c54972d82725</anchor>
      <arglist>(Teuchos_Ordinal i) const </arglist>
    </member>
    <member kind="function">
      <type>const Scalar &amp;</type>
      <name>operator()</name>
      <anchorfile>classThyra_1_1ConstDetachedSpmdVectorView.html</anchorfile>
      <anchor>ac156eae0534ac49641bf8ae34c499eb7</anchor>
      <arglist>(Teuchos_Ordinal i) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::ConstDetachedVectorView</name>
    <filename>classThyra_1_1ConstDetachedVectorView.html</filename>
    <templarg>Scalar</templarg>
    <member kind="function">
      <type></type>
      <name>ConstDetachedVectorView</name>
      <anchorfile>classThyra_1_1ConstDetachedVectorView.html</anchorfile>
      <anchor>a4ba1d57c36076f1d26ed9beb90f7626f</anchor>
      <arglist>(const Teuchos::RCP&lt; const VectorBase&lt; Scalar &gt; &gt; &amp;v, const Range1D &amp;rng=Range1D(), const bool forceUnitStride=false)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ConstDetachedVectorView</name>
      <anchorfile>classThyra_1_1ConstDetachedVectorView.html</anchorfile>
      <anchor>af433244f920d5d90482faf176933786e</anchor>
      <arglist>(const VectorBase&lt; Scalar &gt; &amp;v, const Range1D &amp;rng=Range1D(), const bool forceUnitStride=false)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~ConstDetachedVectorView</name>
      <anchorfile>classThyra_1_1ConstDetachedVectorView.html</anchorfile>
      <anchor>a91d04d991cb29a92ccb6dacca7ca2a7d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const RTOpPack::ConstSubVectorView&lt; Scalar &gt; &amp;</type>
      <name>sv</name>
      <anchorfile>classThyra_1_1ConstDetachedVectorView.html</anchorfile>
      <anchor>a977ce9e0fc992733baaa97bfde4a9d8b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos_Ordinal</type>
      <name>globalOffset</name>
      <anchorfile>classThyra_1_1ConstDetachedVectorView.html</anchorfile>
      <anchor>aaeb14c5571342b621e809e22d58ae6e6</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos_Ordinal</type>
      <name>subDim</name>
      <anchorfile>classThyra_1_1ConstDetachedVectorView.html</anchorfile>
      <anchor>abea38a7848821c1ab91bb479a7eaaf38</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Scalar *</type>
      <name>values</name>
      <anchorfile>classThyra_1_1ConstDetachedVectorView.html</anchorfile>
      <anchor>a71ec0e5ee08673789990c006d4b8aa69</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>ptrdiff_t</type>
      <name>stride</name>
      <anchorfile>classThyra_1_1ConstDetachedVectorView.html</anchorfile>
      <anchor>aadc78e919b976d9c2cb8f28fc3f11de4</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Scalar &amp;</type>
      <name>operator[]</name>
      <anchorfile>classThyra_1_1ConstDetachedVectorView.html</anchorfile>
      <anchor>ab9de776288357f8943ce6e743e142dcc</anchor>
      <arglist>(Teuchos_Ordinal i) const </arglist>
    </member>
    <member kind="function">
      <type>const Scalar &amp;</type>
      <name>operator()</name>
      <anchorfile>classThyra_1_1ConstDetachedVectorView.html</anchorfile>
      <anchor>a5f58f4d337ebbff140c49dde0ff0ffa8</anchor>
      <arglist>(Teuchos_Ordinal i) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::DampenedNewtonNonlinearSolver</name>
    <filename>classThyra_1_1DampenedNewtonNonlinearSolver.html</filename>
    <templarg></templarg>
    <base>Thyra::NonlinearSolverBase</base>
    <member kind="typedef">
      <type>Teuchos::ScalarTraits&lt; Scalar &gt;</type>
      <name>ST</name>
      <anchorfile>classThyra_1_1DampenedNewtonNonlinearSolver.html</anchorfile>
      <anchor>a3366db041c6f6d3e478cd1157644ca61</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>ST::magnitudeType</type>
      <name>ScalarMag</name>
      <anchorfile>classThyra_1_1DampenedNewtonNonlinearSolver.html</anchorfile>
      <anchor>adcda7017af02c87041e378d9c70ec3fc</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Teuchos::ScalarTraits&lt; ScalarMag &gt;</type>
      <name>SMT</name>
      <anchorfile>classThyra_1_1DampenedNewtonNonlinearSolver.html</anchorfile>
      <anchor>a1c59e6791aa0c6248bdc995d49da1b81</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classThyra_1_1DampenedNewtonNonlinearSolver.html</anchorfile>
      <anchor>ab2a81637a848004770146cae46ecb882</anchor>
      <arglist>(ScalarMag, defaultTol)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classThyra_1_1DampenedNewtonNonlinearSolver.html</anchorfile>
      <anchor>a9e7e12e2a1d2bd2194c8f421081e4c73</anchor>
      <arglist>(int, defaultMaxNewtonIterations)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classThyra_1_1DampenedNewtonNonlinearSolver.html</anchorfile>
      <anchor>a2ae2293d4c356c412f043ea7e468acde</anchor>
      <arglist>(bool, useDampenedLineSearch)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classThyra_1_1DampenedNewtonNonlinearSolver.html</anchorfile>
      <anchor>a6bde233e208409729a951036795a09a9</anchor>
      <arglist>(Scalar, armijoConstant)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classThyra_1_1DampenedNewtonNonlinearSolver.html</anchorfile>
      <anchor>a160582e355b963ddb5afe587529a6555</anchor>
      <arglist>(int, maxLineSearchIterations)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>DampenedNewtonNonlinearSolver</name>
      <anchorfile>classThyra_1_1DampenedNewtonNonlinearSolver.html</anchorfile>
      <anchor>a206a21701d3ea36139db4416cf74ad04</anchor>
      <arglist>(const ScalarMag defaultTol=1e-2, const int defaultMaxNewtonIterations=1000, const bool useDampenedLineSearch=true, const Scalar armijoConstant=1e-4, const int maxLineSearchIterations=20)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static RCP&lt; const Teuchos::ParameterList &gt;</type>
      <name>getValidSolveCriteriaExtraParameters</name>
      <anchorfile>classThyra_1_1DampenedNewtonNonlinearSolver.html</anchorfile>
      <anchor>a8748dbcce15273c32f3f0b6aa98a3ef2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setParameterList</name>
      <anchorfile>classThyra_1_1DampenedNewtonNonlinearSolver.html</anchorfile>
      <anchor>a0b9afc4b6863801bc905613bc3297e58</anchor>
      <arglist>(RCP&lt; Teuchos::ParameterList &gt; const &amp;paramList)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; Teuchos::ParameterList &gt;</type>
      <name>getNonconstParameterList</name>
      <anchorfile>classThyra_1_1DampenedNewtonNonlinearSolver.html</anchorfile>
      <anchor>ae8d44d9af60d49fcb1edd584b6411ac3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; Teuchos::ParameterList &gt;</type>
      <name>unsetParameterList</name>
      <anchorfile>classThyra_1_1DampenedNewtonNonlinearSolver.html</anchorfile>
      <anchor>a0cba8d22c10f4f6ad415d1c27a89828e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const Teuchos::ParameterList &gt;</type>
      <name>getParameterList</name>
      <anchorfile>classThyra_1_1DampenedNewtonNonlinearSolver.html</anchorfile>
      <anchor>a56a5b4cc7c174eeb2be2a40887f7e0c1</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const Teuchos::ParameterList &gt;</type>
      <name>getValidParameters</name>
      <anchorfile>classThyra_1_1DampenedNewtonNonlinearSolver.html</anchorfile>
      <anchor>a7ace0168ee46710e10d3b71382ff43ea</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setModel</name>
      <anchorfile>classThyra_1_1DampenedNewtonNonlinearSolver.html</anchorfile>
      <anchor>a4cb528349c524b8b99fce52f4bda7e0a</anchor>
      <arglist>(const RCP&lt; const ModelEvaluator&lt; Scalar &gt; &gt; &amp;model)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const ModelEvaluator&lt; Scalar &gt; &gt;</type>
      <name>getModel</name>
      <anchorfile>classThyra_1_1DampenedNewtonNonlinearSolver.html</anchorfile>
      <anchor>ae60953e12f0eb425d186c5d4ed62d8ee</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>SolveStatus&lt; Scalar &gt;</type>
      <name>solve</name>
      <anchorfile>classThyra_1_1DampenedNewtonNonlinearSolver.html</anchorfile>
      <anchor>a59698165ff577c2229bc208752cfe1ec</anchor>
      <arglist>(VectorBase&lt; Scalar &gt; *x, const SolveCriteria&lt; Scalar &gt; *solveCriteria, VectorBase&lt; Scalar &gt; *delta)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const VectorBase&lt; Scalar &gt; &gt;</type>
      <name>get_current_x</name>
      <anchorfile>classThyra_1_1DampenedNewtonNonlinearSolver.html</anchorfile>
      <anchor>a6414a6b55f0c2e93f7b686f156050222</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>is_W_current</name>
      <anchorfile>classThyra_1_1DampenedNewtonNonlinearSolver.html</anchorfile>
      <anchor>a611621f4f2e91a5339df704c589d8c67</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; LinearOpWithSolveBase&lt; Scalar &gt; &gt;</type>
      <name>get_nonconst_W</name>
      <anchorfile>classThyra_1_1DampenedNewtonNonlinearSolver.html</anchorfile>
      <anchor>a6956c097da28bb684e11e3e295221fc7</anchor>
      <arglist>(const bool forceUpToDate)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const LinearOpWithSolveBase&lt; Scalar &gt; &gt;</type>
      <name>get_W</name>
      <anchorfile>classThyra_1_1DampenedNewtonNonlinearSolver.html</anchorfile>
      <anchor>a61235724660217f6f67bff8223ac4283</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_W_is_current</name>
      <anchorfile>classThyra_1_1DampenedNewtonNonlinearSolver.html</anchorfile>
      <anchor>a04a03b1f5599af762fad8621d25b0cdb</anchor>
      <arglist>(bool W_is_current)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::DefaultAddedLinearOp</name>
    <filename>classThyra_1_1DefaultAddedLinearOp.html</filename>
    <templarg></templarg>
    <base virtualness="virtual">Thyra::AddedLinearOpBase</base>
    <member kind="function">
      <type>RCP&lt; LinearOpBase&lt; Scalar &gt; &gt;</type>
      <name>nonconstAdd</name>
      <anchorfile>classThyra_1_1DefaultAddedLinearOp.html</anchorfile>
      <anchor>a867f3b8aaaf3fe6b7949bdaf60261f53</anchor>
      <arglist>(const RCP&lt; LinearOpBase&lt; Scalar &gt; &gt; &amp;A, const RCP&lt; LinearOpBase&lt; Scalar &gt; &gt; &amp;B, const std::string &amp;label=&quot;&quot;)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const LinearOpBase&lt; Scalar &gt; &gt;</type>
      <name>add</name>
      <anchorfile>classThyra_1_1DefaultAddedLinearOp.html</anchorfile>
      <anchor>ad980c348e6391aeae0d34b0252c31626</anchor>
      <arglist>(const RCP&lt; const LinearOpBase&lt; Scalar &gt; &gt; &amp;A, const RCP&lt; const LinearOpBase&lt; Scalar &gt; &gt; &amp;B, const std::string &amp;label=&quot;&quot;)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; LinearOpBase&lt; Scalar &gt; &gt;</type>
      <name>nonconstSubtract</name>
      <anchorfile>classThyra_1_1DefaultAddedLinearOp.html</anchorfile>
      <anchor>a1e82af2b1c217a93f7be74ceef46f882</anchor>
      <arglist>(const RCP&lt; LinearOpBase&lt; Scalar &gt; &gt; &amp;A, const RCP&lt; LinearOpBase&lt; Scalar &gt; &gt; &amp;B, const std::string &amp;label=&quot;&quot;)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const LinearOpBase&lt; Scalar &gt; &gt;</type>
      <name>subtract</name>
      <anchorfile>classThyra_1_1DefaultAddedLinearOp.html</anchorfile>
      <anchor>aec400072237506b078c7a750b97b76bc</anchor>
      <arglist>(const RCP&lt; const LinearOpBase&lt; Scalar &gt; &gt; &amp;A, const RCP&lt; const LinearOpBase&lt; Scalar &gt; &gt; &amp;B, const std::string &amp;label=&quot;&quot;)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>DefaultAddedLinearOp</name>
      <anchorfile>classThyra_1_1DefaultAddedLinearOp.html</anchorfile>
      <anchor>ab9cbbf0f18f960c665d2a0fcfd13da61</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>DefaultAddedLinearOp</name>
      <anchorfile>classThyra_1_1DefaultAddedLinearOp.html</anchorfile>
      <anchor>a605943d9c54d78fd2b4b81f26064b714</anchor>
      <arglist>(const ArrayView&lt; const RCP&lt; LinearOpBase&lt; Scalar &gt; &gt; &gt; &amp;Ops)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>DefaultAddedLinearOp</name>
      <anchorfile>classThyra_1_1DefaultAddedLinearOp.html</anchorfile>
      <anchor>ae8c9e1c8e0da579cfd62b136819ac2a7</anchor>
      <arglist>(const ArrayView&lt; const RCP&lt; const LinearOpBase&lt; Scalar &gt; &gt; &gt; &amp;Ops)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initialize</name>
      <anchorfile>classThyra_1_1DefaultAddedLinearOp.html</anchorfile>
      <anchor>abb73527c8ca7e4b18f31bb134eb93141</anchor>
      <arglist>(const ArrayView&lt; const RCP&lt; LinearOpBase&lt; Scalar &gt; &gt; &gt; &amp;Ops)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initialize</name>
      <anchorfile>classThyra_1_1DefaultAddedLinearOp.html</anchorfile>
      <anchor>a56a1de35c5945ef1eb52c2c9762c69fd</anchor>
      <arglist>(const ArrayView&lt; const RCP&lt; const LinearOpBase&lt; Scalar &gt; &gt; &gt; &amp;Ops)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>uninitialize</name>
      <anchorfile>classThyra_1_1DefaultAddedLinearOp.html</anchorfile>
      <anchor>a527f82ae9e69bed8837034fbe7325282</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>numOps</name>
      <anchorfile>classThyra_1_1DefaultAddedLinearOp.html</anchorfile>
      <anchor>a4f08973153a3588972fcdddf90955d26</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>opIsConst</name>
      <anchorfile>classThyra_1_1DefaultAddedLinearOp.html</anchorfile>
      <anchor>a6b3a2efbafd651006e17ce5cca653d60</anchor>
      <arglist>(const int k) const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; LinearOpBase&lt; Scalar &gt; &gt;</type>
      <name>getNonconstOp</name>
      <anchorfile>classThyra_1_1DefaultAddedLinearOp.html</anchorfile>
      <anchor>a2144e144387e9e8a332ff1cf74a8503b</anchor>
      <arglist>(const int k)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const LinearOpBase&lt; Scalar &gt; &gt;</type>
      <name>getOp</name>
      <anchorfile>classThyra_1_1DefaultAddedLinearOp.html</anchorfile>
      <anchor>a15fd7c840c48fa7ac0bb098a5f3a6f8b</anchor>
      <arglist>(const int k) const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const VectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>range</name>
      <anchorfile>classThyra_1_1DefaultAddedLinearOp.html</anchorfile>
      <anchor>a20ecfb0696327282acf98c51b21b021e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const VectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>domain</name>
      <anchorfile>classThyra_1_1DefaultAddedLinearOp.html</anchorfile>
      <anchor>a715f1212288e54845562f3258f465219</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const LinearOpBase&lt; Scalar &gt; &gt;</type>
      <name>clone</name>
      <anchorfile>classThyra_1_1DefaultAddedLinearOp.html</anchorfile>
      <anchor>a7cd88949527709e97fad8918b1bbe134</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>bool</type>
      <name>opSupportedImpl</name>
      <anchorfile>classThyra_1_1DefaultAddedLinearOp.html</anchorfile>
      <anchor>a9ac17f00dbeb0edddaabb3287d0ab477</anchor>
      <arglist>(EOpTransp M_trans) const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>applyImpl</name>
      <anchorfile>classThyra_1_1DefaultAddedLinearOp.html</anchorfile>
      <anchor>a63802b97d3c17c4143c46ac9211aab9f</anchor>
      <arglist>(const EOpTransp M_trans, const MultiVectorBase&lt; Scalar &gt; &amp;X, const Ptr&lt; MultiVectorBase&lt; Scalar &gt; &gt; &amp;Y, const Scalar alpha, const Scalar beta) const </arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>description</name>
      <anchorfile>classThyra_1_1DefaultAddedLinearOp.html</anchorfile>
      <anchor>a497a7b1b156b80c23d819daa94433404</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>describe</name>
      <anchorfile>classThyra_1_1DefaultAddedLinearOp.html</anchorfile>
      <anchor>addcc44e3cec1fa4261c4dec8945c2524</anchor>
      <arglist>(Teuchos::FancyOStream &amp;out, const Teuchos::EVerbosityLevel verbLevel) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::DefaultAdjointLinearOpWithSolve</name>
    <filename>classThyra_1_1DefaultAdjointLinearOpWithSolve.html</filename>
    <templarg></templarg>
    <base virtualness="virtual">Thyra::LinearOpWithSolveBase</base>
    <member kind="function">
      <type></type>
      <name>DefaultAdjointLinearOpWithSolve</name>
      <anchorfile>classThyra_1_1DefaultAdjointLinearOpWithSolve.html</anchorfile>
      <anchor>a665516f0d72512cecd4c205759ce1fec</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initialize</name>
      <anchorfile>classThyra_1_1DefaultAdjointLinearOpWithSolve.html</anchorfile>
      <anchor>a23db7a891c07732323b9adafb9063850</anchor>
      <arglist>(const RCP&lt; LinearOpWithSolveBase&lt; Scalar &gt; &gt; &amp;lows, const EOpTransp transp)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initialize</name>
      <anchorfile>classThyra_1_1DefaultAdjointLinearOpWithSolve.html</anchorfile>
      <anchor>aa19e18d585048f99664fb1d325c6c321</anchor>
      <arglist>(const RCP&lt; const LinearOpWithSolveBase&lt; Scalar &gt; &gt; &amp;lows, const EOpTransp transp)</arglist>
    </member>
    <member kind="function">
      <type>const RCP&lt; LinearOpWithSolveBase&lt; Scalar &gt; &gt;</type>
      <name>getNonconstOp</name>
      <anchorfile>classThyra_1_1DefaultAdjointLinearOpWithSolve.html</anchorfile>
      <anchor>abf645707bef55b64b8b5b4e37b357ea7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const RCP&lt; const LinearOpWithSolveBase&lt; Scalar &gt; &gt;</type>
      <name>getOp</name>
      <anchorfile>classThyra_1_1DefaultAdjointLinearOpWithSolve.html</anchorfile>
      <anchor>a39452cfeec7e737c51f27addc3597384</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const VectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>range</name>
      <anchorfile>classThyra_1_1DefaultAdjointLinearOpWithSolve.html</anchorfile>
      <anchor>adb72ad3fd4e41ee3a01280eda6d73512</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const VectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>domain</name>
      <anchorfile>classThyra_1_1DefaultAdjointLinearOpWithSolve.html</anchorfile>
      <anchor>a28affbbdbe1fc6d2943b20f6dc962b49</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>bool</type>
      <name>opSupportedImpl</name>
      <anchorfile>classThyra_1_1DefaultAdjointLinearOpWithSolve.html</anchorfile>
      <anchor>a979f98adc6586a089b1a31bda6b08750</anchor>
      <arglist>(EOpTransp M_trans) const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>applyImpl</name>
      <anchorfile>classThyra_1_1DefaultAdjointLinearOpWithSolve.html</anchorfile>
      <anchor>a8ef1c3110056265949b4a9fe72589ca2</anchor>
      <arglist>(const EOpTransp M_trans, const MultiVectorBase&lt; Scalar &gt; &amp;X, const Ptr&lt; MultiVectorBase&lt; Scalar &gt; &gt; &amp;Y, const Scalar alpha, const Scalar beta) const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>bool</type>
      <name>solveSupportsImpl</name>
      <anchorfile>classThyra_1_1DefaultAdjointLinearOpWithSolve.html</anchorfile>
      <anchor>aa837161ad2973b4339e0b35d0cb4a1b5</anchor>
      <arglist>(EOpTransp M_trans) const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>bool</type>
      <name>solveSupportsSolveMeasureTypeImpl</name>
      <anchorfile>classThyra_1_1DefaultAdjointLinearOpWithSolve.html</anchorfile>
      <anchor>aa4425b504ee8690c8ea583ed4b53648a</anchor>
      <arglist>(EOpTransp M_trans, const SolveMeasureType &amp;solveMeasureType) const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>SolveStatus&lt; Scalar &gt;</type>
      <name>solveImpl</name>
      <anchorfile>classThyra_1_1DefaultAdjointLinearOpWithSolve.html</anchorfile>
      <anchor>a4bd78de10629659e07dae299867b9854</anchor>
      <arglist>(const EOpTransp transp, const MultiVectorBase&lt; Scalar &gt; &amp;B, const Ptr&lt; MultiVectorBase&lt; Scalar &gt; &gt; &amp;X, const Ptr&lt; const SolveCriteria&lt; Scalar &gt; &gt; solveCriteria) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::DefaultBlockedLinearOp</name>
    <filename>classThyra_1_1DefaultBlockedLinearOp.html</filename>
    <templarg></templarg>
    <base virtualness="virtual">Thyra::PhysicallyBlockedLinearOpBase</base>
    <base virtualness="virtual">Thyra::RowStatLinearOpBase</base>
    <base virtualness="virtual">Thyra::ScaledLinearOpBase</base>
    <member kind="function">
      <type>RCP&lt; DefaultBlockedLinearOp&lt; Scalar &gt; &gt;</type>
      <name>defaultBlockedLinearOp</name>
      <anchorfile>classThyra_1_1DefaultBlockedLinearOp.html</anchorfile>
      <anchor>aaa0570d085c6f1ddf552e53957c6c457</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const LinearOpBase&lt; Scalar &gt; &gt;</type>
      <name>block1x1</name>
      <anchorfile>classThyra_1_1DefaultBlockedLinearOp.html</anchorfile>
      <anchor>aeb4588f114997d5aa5aaeabb7e548938</anchor>
      <arglist>(const Teuchos::RCP&lt; const LinearOpBase&lt; Scalar &gt; &gt; &amp;A00, const std::string &amp;label=&quot;&quot;)</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const LinearOpBase&lt; Scalar &gt; &gt;</type>
      <name>block1x2</name>
      <anchorfile>classThyra_1_1DefaultBlockedLinearOp.html</anchorfile>
      <anchor>abcd721aa40f2dae3924beaf27be94c5a</anchor>
      <arglist>(const Teuchos::RCP&lt; const LinearOpBase&lt; Scalar &gt; &gt; &amp;A00, const Teuchos::RCP&lt; const LinearOpBase&lt; Scalar &gt; &gt; &amp;A01, const std::string &amp;label=&quot;&quot;)</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const LinearOpBase&lt; Scalar &gt; &gt;</type>
      <name>block2x1</name>
      <anchorfile>classThyra_1_1DefaultBlockedLinearOp.html</anchorfile>
      <anchor>a7654a245ed8aaa7bb705d91293067726</anchor>
      <arglist>(const Teuchos::RCP&lt; const LinearOpBase&lt; Scalar &gt; &gt; &amp;A00, const Teuchos::RCP&lt; const LinearOpBase&lt; Scalar &gt; &gt; &amp;A10, const std::string &amp;label=&quot;&quot;)</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const LinearOpBase&lt; Scalar &gt; &gt;</type>
      <name>block2x2</name>
      <anchorfile>classThyra_1_1DefaultBlockedLinearOp.html</anchorfile>
      <anchor>acbe96629ed7bd52b43895ffab58a4cde</anchor>
      <arglist>(const Teuchos::RCP&lt; const LinearOpBase&lt; Scalar &gt; &gt; &amp;A00, const Teuchos::RCP&lt; const LinearOpBase&lt; Scalar &gt; &gt; &amp;A01, const Teuchos::RCP&lt; const LinearOpBase&lt; Scalar &gt; &gt; &amp;A10, const Teuchos::RCP&lt; const LinearOpBase&lt; Scalar &gt; &gt; &amp;A11, const std::string &amp;label=&quot;&quot;)</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; LinearOpBase&lt; Scalar &gt; &gt;</type>
      <name>nonconstBlock1x1</name>
      <anchorfile>classThyra_1_1DefaultBlockedLinearOp.html</anchorfile>
      <anchor>aeecb4d531f0dac152340db3e8d4a7ab5</anchor>
      <arglist>(const Teuchos::RCP&lt; LinearOpBase&lt; Scalar &gt; &gt; &amp;A00, const std::string &amp;label=&quot;&quot;)</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; LinearOpBase&lt; Scalar &gt; &gt;</type>
      <name>nonconstBlock1x2</name>
      <anchorfile>classThyra_1_1DefaultBlockedLinearOp.html</anchorfile>
      <anchor>a9a2bcf75906665eeccf0bf5f04094319</anchor>
      <arglist>(const Teuchos::RCP&lt; LinearOpBase&lt; Scalar &gt; &gt; &amp;A00, const Teuchos::RCP&lt; LinearOpBase&lt; Scalar &gt; &gt; &amp;A01, const std::string &amp;label=&quot;&quot;)</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; LinearOpBase&lt; Scalar &gt; &gt;</type>
      <name>nonconstBlock2x1</name>
      <anchorfile>classThyra_1_1DefaultBlockedLinearOp.html</anchorfile>
      <anchor>abd5cd8cf1e0c6c1b3fa313b5d998b0d9</anchor>
      <arglist>(const Teuchos::RCP&lt; LinearOpBase&lt; Scalar &gt; &gt; &amp;A00, const Teuchos::RCP&lt; LinearOpBase&lt; Scalar &gt; &gt; &amp;A10, const std::string &amp;label=&quot;&quot;)</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; LinearOpBase&lt; Scalar &gt; &gt;</type>
      <name>nonconstBlock2x2</name>
      <anchorfile>classThyra_1_1DefaultBlockedLinearOp.html</anchorfile>
      <anchor>a4675e8894d09362cf80025412ba6f8f5</anchor>
      <arglist>(const Teuchos::RCP&lt; LinearOpBase&lt; Scalar &gt; &gt; &amp;A00, const Teuchos::RCP&lt; LinearOpBase&lt; Scalar &gt; &gt; &amp;A01, const Teuchos::RCP&lt; LinearOpBase&lt; Scalar &gt; &gt; &amp;A10, const Teuchos::RCP&lt; LinearOpBase&lt; Scalar &gt; &gt; &amp;A11, const std::string &amp;label=&quot;&quot;)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>DefaultBlockedLinearOp</name>
      <anchorfile>classThyra_1_1DefaultBlockedLinearOp.html</anchorfile>
      <anchor>a5818cb1feedb5efaed8c290d6f05b3a2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>beginBlockFill</name>
      <anchorfile>classThyra_1_1DefaultBlockedLinearOp.html</anchorfile>
      <anchor>a54e98da9e467b17330d954b2a66c2df5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>beginBlockFill</name>
      <anchorfile>classThyra_1_1DefaultBlockedLinearOp.html</anchorfile>
      <anchor>acac51b9bde1bf64acad406eb44cead4d</anchor>
      <arglist>(const int numRowBlocks, const int numColBlocks)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>beginBlockFill</name>
      <anchorfile>classThyra_1_1DefaultBlockedLinearOp.html</anchorfile>
      <anchor>a3d0b38529fb06cfb5c877c3ddf355d79</anchor>
      <arglist>(const Teuchos::RCP&lt; const ProductVectorSpaceBase&lt; Scalar &gt; &gt; &amp;productRange, const Teuchos::RCP&lt; const ProductVectorSpaceBase&lt; Scalar &gt; &gt; &amp;productDomain)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>blockFillIsActive</name>
      <anchorfile>classThyra_1_1DefaultBlockedLinearOp.html</anchorfile>
      <anchor>a6ebb8fa950a1bfb5a6e1e088dcc11f73</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>acceptsBlock</name>
      <anchorfile>classThyra_1_1DefaultBlockedLinearOp.html</anchorfile>
      <anchor>a8dec70e4597aa125cde6624b7abc9632</anchor>
      <arglist>(const int i, const int j) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setNonconstBlock</name>
      <anchorfile>classThyra_1_1DefaultBlockedLinearOp.html</anchorfile>
      <anchor>a8be0fae1173b70cfb36ced770e6b094a</anchor>
      <arglist>(const int i, const int j, const Teuchos::RCP&lt; LinearOpBase&lt; Scalar &gt; &gt; &amp;block)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setBlock</name>
      <anchorfile>classThyra_1_1DefaultBlockedLinearOp.html</anchorfile>
      <anchor>ab63b7d4c05ebba80ac5a98fa8df7293c</anchor>
      <arglist>(const int i, const int j, const Teuchos::RCP&lt; const LinearOpBase&lt; Scalar &gt; &gt; &amp;block)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>endBlockFill</name>
      <anchorfile>classThyra_1_1DefaultBlockedLinearOp.html</anchorfile>
      <anchor>aba681c8d12ebb8942b806e1d2087d432</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>uninitialize</name>
      <anchorfile>classThyra_1_1DefaultBlockedLinearOp.html</anchorfile>
      <anchor>a52a5f43e121607c2978f6bae25803caa</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const ProductVectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>productRange</name>
      <anchorfile>classThyra_1_1DefaultBlockedLinearOp.html</anchorfile>
      <anchor>a561f674d02e1ce6e9b36bb3830bfd29d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const ProductVectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>productDomain</name>
      <anchorfile>classThyra_1_1DefaultBlockedLinearOp.html</anchorfile>
      <anchor>aed1ea0902a4fa11a3a5adba9b6cfe442</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>blockExists</name>
      <anchorfile>classThyra_1_1DefaultBlockedLinearOp.html</anchorfile>
      <anchor>a27c55847a51d86567a9722d08422b32d</anchor>
      <arglist>(const int i, const int j) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>blockIsConst</name>
      <anchorfile>classThyra_1_1DefaultBlockedLinearOp.html</anchorfile>
      <anchor>ac08d50f8403b7d12d67b9b7e4c3b5233</anchor>
      <arglist>(const int i, const int j) const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; LinearOpBase&lt; Scalar &gt; &gt;</type>
      <name>getNonconstBlock</name>
      <anchorfile>classThyra_1_1DefaultBlockedLinearOp.html</anchorfile>
      <anchor>a6886206b41d447ed8bc77cde2a7e2063</anchor>
      <arglist>(const int i, const int j)</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const LinearOpBase&lt; Scalar &gt; &gt;</type>
      <name>getBlock</name>
      <anchorfile>classThyra_1_1DefaultBlockedLinearOp.html</anchorfile>
      <anchor>a830cdde1286c8aa9e47b97d20d7379dc</anchor>
      <arglist>(const int i, const int j) const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const VectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>range</name>
      <anchorfile>classThyra_1_1DefaultBlockedLinearOp.html</anchorfile>
      <anchor>a3430747fee36df9273be0ea7b35f2039</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const VectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>domain</name>
      <anchorfile>classThyra_1_1DefaultBlockedLinearOp.html</anchorfile>
      <anchor>acb2fe70b4581d971fd28910958e4f1b9</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const LinearOpBase&lt; Scalar &gt; &gt;</type>
      <name>clone</name>
      <anchorfile>classThyra_1_1DefaultBlockedLinearOp.html</anchorfile>
      <anchor>acdda45f60162b02d05df72944ca88996</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>bool</type>
      <name>opSupportedImpl</name>
      <anchorfile>classThyra_1_1DefaultBlockedLinearOp.html</anchorfile>
      <anchor>a7950ccb19dd7f37b5740a8721634a671</anchor>
      <arglist>(EOpTransp M_trans) const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>applyImpl</name>
      <anchorfile>classThyra_1_1DefaultBlockedLinearOp.html</anchorfile>
      <anchor>a1820feec4ea21318bd36199e8102d2dd</anchor>
      <arglist>(const EOpTransp M_trans, const MultiVectorBase&lt; Scalar &gt; &amp;X, const Ptr&lt; MultiVectorBase&lt; Scalar &gt; &gt; &amp;Y, const Scalar alpha, const Scalar beta) const </arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>description</name>
      <anchorfile>classThyra_1_1DefaultBlockedLinearOp.html</anchorfile>
      <anchor>a87766e1724fc0589eb2116473c8b796c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>describe</name>
      <anchorfile>classThyra_1_1DefaultBlockedLinearOp.html</anchorfile>
      <anchor>a548785e3c69c6ef24fd63e7f31a44c97</anchor>
      <arglist>(Teuchos::FancyOStream &amp;out, const Teuchos::EVerbosityLevel verbLevel) const </arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual bool</type>
      <name>rowStatIsSupportedImpl</name>
      <anchorfile>classThyra_1_1DefaultBlockedLinearOp.html</anchorfile>
      <anchor>a00fdb949f459d0a343fc454820cf8a9f</anchor>
      <arglist>(const RowStatLinearOpBaseUtils::ERowStat rowStat) const </arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual void</type>
      <name>getRowStatImpl</name>
      <anchorfile>classThyra_1_1DefaultBlockedLinearOp.html</anchorfile>
      <anchor>a5eee9fae643ddbbfa702d9b5f3d4e47a</anchor>
      <arglist>(const RowStatLinearOpBaseUtils::ERowStat rowStat, const Teuchos::Ptr&lt; VectorBase&lt; Scalar &gt; &gt; &amp;rowStatVec) const </arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual bool</type>
      <name>supportsScaleLeftImpl</name>
      <anchorfile>classThyra_1_1DefaultBlockedLinearOp.html</anchorfile>
      <anchor>acf9bfaace1eb587853f308a0dad26662</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual bool</type>
      <name>supportsScaleRightImpl</name>
      <anchorfile>classThyra_1_1DefaultBlockedLinearOp.html</anchorfile>
      <anchor>afd5393599f6d696dde1c7985d1b4b378</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual void</type>
      <name>scaleLeftImpl</name>
      <anchorfile>classThyra_1_1DefaultBlockedLinearOp.html</anchorfile>
      <anchor>a841b43da9cdc9cfa58a64bf26c899f4e</anchor>
      <arglist>(const VectorBase&lt; Scalar &gt; &amp;row_scaling)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual void</type>
      <name>scaleRightImpl</name>
      <anchorfile>classThyra_1_1DefaultBlockedLinearOp.html</anchorfile>
      <anchor>a1a41d60f68a9bb039856836588cf77b8</anchor>
      <arglist>(const VectorBase&lt; Scalar &gt; &amp;col_scaling)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::DefaultBlockedTriangularLinearOpWithSolve</name>
    <filename>classThyra_1_1DefaultBlockedTriangularLinearOpWithSolve.html</filename>
    <templarg></templarg>
    <base virtualness="virtual">Thyra::PhysicallyBlockedLinearOpWithSolveBase</base>
    <member kind="function">
      <type>RCP&lt; DefaultBlockedTriangularLinearOpWithSolve&lt; Scalar &gt; &gt;</type>
      <name>defaultBlockedTriangularLinearOpWithSolve</name>
      <anchorfile>classThyra_1_1DefaultBlockedTriangularLinearOpWithSolve.html</anchorfile>
      <anchor>a413bc81b46910dd4a15321d741c53ca8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>DefaultBlockedTriangularLinearOpWithSolve</name>
      <anchorfile>classThyra_1_1DefaultBlockedTriangularLinearOpWithSolve.html</anchorfile>
      <anchor>a9803213c06a6ec07c4c7a75500a71995</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setNonconstBlocks</name>
      <anchorfile>classThyra_1_1DefaultBlockedTriangularLinearOpWithSolve.html</anchorfile>
      <anchor>a2230ec2c2f2b7c94214929f5f2d70115</anchor>
      <arglist>(const RCP&lt; PhysicallyBlockedLinearOpBase&lt; Scalar &gt; &gt; &amp;blocks)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setBlocks</name>
      <anchorfile>classThyra_1_1DefaultBlockedTriangularLinearOpWithSolve.html</anchorfile>
      <anchor>a605a004cf2542d36b4e2bd51a40fb571</anchor>
      <arglist>(const RCP&lt; const PhysicallyBlockedLinearOpBase&lt; Scalar &gt; &gt; &amp;blocks)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; PhysicallyBlockedLinearOpBase&lt; Scalar &gt; &gt;</type>
      <name>getNonconstBlocks</name>
      <anchorfile>classThyra_1_1DefaultBlockedTriangularLinearOpWithSolve.html</anchorfile>
      <anchor>a6c6eb31d7619468fa3b337084779f8b4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const PhysicallyBlockedLinearOpBase&lt; Scalar &gt; &gt;</type>
      <name>getBlocks</name>
      <anchorfile>classThyra_1_1DefaultBlockedTriangularLinearOpWithSolve.html</anchorfile>
      <anchor>a04768b5498374f8b2083b46729c59962</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>acceptsLOWSBlock</name>
      <anchorfile>classThyra_1_1DefaultBlockedTriangularLinearOpWithSolve.html</anchorfile>
      <anchor>a94b61b1f05c8352b66a4777e79124fd8</anchor>
      <arglist>(const int i, const int j) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setNonconstLOWSBlock</name>
      <anchorfile>classThyra_1_1DefaultBlockedTriangularLinearOpWithSolve.html</anchorfile>
      <anchor>a88159ca4d3f2e2a9b7db6b54a385dc01</anchor>
      <arglist>(const int i, const int j, const RCP&lt; LinearOpWithSolveBase&lt; Scalar &gt; &gt; &amp;block)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setLOWSBlock</name>
      <anchorfile>classThyra_1_1DefaultBlockedTriangularLinearOpWithSolve.html</anchorfile>
      <anchor>a3be69463a5d28511b30cec901a155c0e</anchor>
      <arglist>(const int i, const int j, const RCP&lt; const LinearOpWithSolveBase&lt; Scalar &gt; &gt; &amp;block)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>beginBlockFill</name>
      <anchorfile>classThyra_1_1DefaultBlockedTriangularLinearOpWithSolve.html</anchorfile>
      <anchor>ac72583a54d1a2277fa934a62dafc7c61</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>beginBlockFill</name>
      <anchorfile>classThyra_1_1DefaultBlockedTriangularLinearOpWithSolve.html</anchorfile>
      <anchor>a14d1f71fd4268b56f8c1b24cd40e8d01</anchor>
      <arglist>(const int numRowBlocks, const int numColBlocks)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>beginBlockFill</name>
      <anchorfile>classThyra_1_1DefaultBlockedTriangularLinearOpWithSolve.html</anchorfile>
      <anchor>afe7ac8e733c38bd8d88ba78362df8069</anchor>
      <arglist>(const RCP&lt; const ProductVectorSpaceBase&lt; Scalar &gt; &gt; &amp;productRange, const RCP&lt; const ProductVectorSpaceBase&lt; Scalar &gt; &gt; &amp;productDomain)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>blockFillIsActive</name>
      <anchorfile>classThyra_1_1DefaultBlockedTriangularLinearOpWithSolve.html</anchorfile>
      <anchor>a562714e1c0941ae8393f9efc996e733f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>acceptsBlock</name>
      <anchorfile>classThyra_1_1DefaultBlockedTriangularLinearOpWithSolve.html</anchorfile>
      <anchor>a69fff92daca4367284e237d71f783545</anchor>
      <arglist>(const int i, const int j) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setNonconstBlock</name>
      <anchorfile>classThyra_1_1DefaultBlockedTriangularLinearOpWithSolve.html</anchorfile>
      <anchor>a5ac1c2736823c1f0cc7dabfe9c9dd98e</anchor>
      <arglist>(const int i, const int j, const RCP&lt; LinearOpBase&lt; Scalar &gt; &gt; &amp;block)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setBlock</name>
      <anchorfile>classThyra_1_1DefaultBlockedTriangularLinearOpWithSolve.html</anchorfile>
      <anchor>a931bfe8aaf4faf668c398d1d8ad48eae</anchor>
      <arglist>(const int i, const int j, const RCP&lt; const LinearOpBase&lt; Scalar &gt; &gt; &amp;block)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>endBlockFill</name>
      <anchorfile>classThyra_1_1DefaultBlockedTriangularLinearOpWithSolve.html</anchorfile>
      <anchor>a4541a229d5b672335dbfacec2d5f28e7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>uninitialize</name>
      <anchorfile>classThyra_1_1DefaultBlockedTriangularLinearOpWithSolve.html</anchorfile>
      <anchor>ab378496082eeb541ab11c2af49030706</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; LinearOpWithSolveBase&lt; Scalar &gt; &gt;</type>
      <name>getNonconstLOWSBlock</name>
      <anchorfile>classThyra_1_1DefaultBlockedTriangularLinearOpWithSolve.html</anchorfile>
      <anchor>ac0dbb74d0fb154284ddab327b9d5e0ba</anchor>
      <arglist>(const int i, const int j)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const LinearOpWithSolveBase&lt; Scalar &gt; &gt;</type>
      <name>getLOWSBlock</name>
      <anchorfile>classThyra_1_1DefaultBlockedTriangularLinearOpWithSolve.html</anchorfile>
      <anchor>a3e414794367c7aba6d0996ae3002a780</anchor>
      <arglist>(const int i, const int j) const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const ProductVectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>productRange</name>
      <anchorfile>classThyra_1_1DefaultBlockedTriangularLinearOpWithSolve.html</anchorfile>
      <anchor>ad47b35bb4489414e0e6fb219e24137ee</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const ProductVectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>productDomain</name>
      <anchorfile>classThyra_1_1DefaultBlockedTriangularLinearOpWithSolve.html</anchorfile>
      <anchor>a24144f9129d3cead19009f6d24fdb67b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>blockExists</name>
      <anchorfile>classThyra_1_1DefaultBlockedTriangularLinearOpWithSolve.html</anchorfile>
      <anchor>a9445ab05ac5a3793b5b43c1f34a0e813</anchor>
      <arglist>(const int i, const int j) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>blockIsConst</name>
      <anchorfile>classThyra_1_1DefaultBlockedTriangularLinearOpWithSolve.html</anchorfile>
      <anchor>a6ca3504513e72fc0fbd4ca5b8f04cd2f</anchor>
      <arglist>(const int i, const int j) const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; LinearOpBase&lt; Scalar &gt; &gt;</type>
      <name>getNonconstBlock</name>
      <anchorfile>classThyra_1_1DefaultBlockedTriangularLinearOpWithSolve.html</anchorfile>
      <anchor>ae89610970039002620afd437684da662</anchor>
      <arglist>(const int i, const int j)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const LinearOpBase&lt; Scalar &gt; &gt;</type>
      <name>getBlock</name>
      <anchorfile>classThyra_1_1DefaultBlockedTriangularLinearOpWithSolve.html</anchorfile>
      <anchor>a0c64ae9a2aa2323cb25bd883a7bca891</anchor>
      <arglist>(const int i, const int j) const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const VectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>range</name>
      <anchorfile>classThyra_1_1DefaultBlockedTriangularLinearOpWithSolve.html</anchorfile>
      <anchor>a26124be7ef5c76a011b27283d4601ff8</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const VectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>domain</name>
      <anchorfile>classThyra_1_1DefaultBlockedTriangularLinearOpWithSolve.html</anchorfile>
      <anchor>a171437d9e9588e3542a12a2a7d2ef2dc</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const LinearOpBase&lt; Scalar &gt; &gt;</type>
      <name>clone</name>
      <anchorfile>classThyra_1_1DefaultBlockedTriangularLinearOpWithSolve.html</anchorfile>
      <anchor>a38fd78d7764661ded999e14715ce120a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>bool</type>
      <name>opSupportedImpl</name>
      <anchorfile>classThyra_1_1DefaultBlockedTriangularLinearOpWithSolve.html</anchorfile>
      <anchor>ace46ae3e1f769a54b7870c7827770359</anchor>
      <arglist>(EOpTransp M_trans) const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>applyImpl</name>
      <anchorfile>classThyra_1_1DefaultBlockedTriangularLinearOpWithSolve.html</anchorfile>
      <anchor>a08bfad2968bf16e9ce3e2ae02eac2ccc</anchor>
      <arglist>(const EOpTransp M_trans, const MultiVectorBase&lt; Scalar &gt; &amp;X, const Ptr&lt; MultiVectorBase&lt; Scalar &gt; &gt; &amp;Y, const Scalar alpha, const Scalar beta) const </arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>description</name>
      <anchorfile>classThyra_1_1DefaultBlockedTriangularLinearOpWithSolve.html</anchorfile>
      <anchor>aabdf83298e66df13237d98642015a969</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>describe</name>
      <anchorfile>classThyra_1_1DefaultBlockedTriangularLinearOpWithSolve.html</anchorfile>
      <anchor>af5bdad47c933645d8d016045b2c75397</anchor>
      <arglist>(Teuchos::FancyOStream &amp;out, const Teuchos::EVerbosityLevel verbLevel) const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>bool</type>
      <name>solveSupportsImpl</name>
      <anchorfile>classThyra_1_1DefaultBlockedTriangularLinearOpWithSolve.html</anchorfile>
      <anchor>a7a5039d73352574dd0b3c08c679a8ede</anchor>
      <arglist>(EOpTransp M_trans) const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>bool</type>
      <name>solveSupportsSolveMeasureTypeImpl</name>
      <anchorfile>classThyra_1_1DefaultBlockedTriangularLinearOpWithSolve.html</anchorfile>
      <anchor>aeb27deaf2cdaffd2b1430d3b387e78ae</anchor>
      <arglist>(EOpTransp M_trans, const SolveMeasureType &amp;solveMeasureType) const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>SolveStatus&lt; Scalar &gt;</type>
      <name>solveImpl</name>
      <anchorfile>classThyra_1_1DefaultBlockedTriangularLinearOpWithSolve.html</anchorfile>
      <anchor>a455ab4163bbf450ce05a01b9ef9434f3</anchor>
      <arglist>(const EOpTransp transp, const MultiVectorBase&lt; Scalar &gt; &amp;B, const Ptr&lt; MultiVectorBase&lt; Scalar &gt; &gt; &amp;X, const Ptr&lt; const SolveCriteria&lt; Scalar &gt; &gt; solveCriteria) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::DefaultBlockedTriangularLinearOpWithSolveFactory</name>
    <filename>classThyra_1_1DefaultBlockedTriangularLinearOpWithSolveFactory.html</filename>
    <templarg></templarg>
    <base virtualness="virtual">Thyra::LinearOpWithSolveFactoryBase</base>
    <member kind="function">
      <type></type>
      <name>DefaultBlockedTriangularLinearOpWithSolveFactory</name>
      <anchorfile>classThyra_1_1DefaultBlockedTriangularLinearOpWithSolveFactory.html</anchorfile>
      <anchor>a4fe0099b4990d0080543a3677dbfbd55</anchor>
      <arglist>(const RCP&lt; LinearOpWithSolveFactoryBase&lt; Scalar &gt; &gt; &amp;lowsf)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>DefaultBlockedTriangularLinearOpWithSolveFactory</name>
      <anchorfile>classThyra_1_1DefaultBlockedTriangularLinearOpWithSolveFactory.html</anchorfile>
      <anchor>a6444aadb46ab99e3c1cdcafcfcd4a597</anchor>
      <arglist>(const RCP&lt; const LinearOpWithSolveFactoryBase&lt; Scalar &gt; &gt; &amp;lowsf)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; LinearOpWithSolveFactoryBase&lt; Scalar &gt; &gt;</type>
      <name>getUnderlyingLOWSF</name>
      <anchorfile>classThyra_1_1DefaultBlockedTriangularLinearOpWithSolveFactory.html</anchorfile>
      <anchor>a05971265212a36aa1bb2af32798273df</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const LinearOpWithSolveFactoryBase&lt; Scalar &gt; &gt;</type>
      <name>getUnderlyingLOWSF</name>
      <anchorfile>classThyra_1_1DefaultBlockedTriangularLinearOpWithSolveFactory.html</anchorfile>
      <anchor>a9aa40d4a7fcbe56203606dbaf71c14c7</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>description</name>
      <anchorfile>classThyra_1_1DefaultBlockedTriangularLinearOpWithSolveFactory.html</anchorfile>
      <anchor>a9e4614ce0b9418c21c0128b83e43feda</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setParameterList</name>
      <anchorfile>classThyra_1_1DefaultBlockedTriangularLinearOpWithSolveFactory.html</anchorfile>
      <anchor>a59733ae08fa59a05ee974a03930a248d</anchor>
      <arglist>(RCP&lt; ParameterList &gt; const &amp;paramList)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; ParameterList &gt;</type>
      <name>getNonconstParameterList</name>
      <anchorfile>classThyra_1_1DefaultBlockedTriangularLinearOpWithSolveFactory.html</anchorfile>
      <anchor>a44a05ce997160dbe5d859cc93c00609d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; ParameterList &gt;</type>
      <name>unsetParameterList</name>
      <anchorfile>classThyra_1_1DefaultBlockedTriangularLinearOpWithSolveFactory.html</anchorfile>
      <anchor>a0942ccb4e26821aa1dbae67a33278171</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const ParameterList &gt;</type>
      <name>getParameterList</name>
      <anchorfile>classThyra_1_1DefaultBlockedTriangularLinearOpWithSolveFactory.html</anchorfile>
      <anchor>a65cfc9dbab4077e4de7cc423a19e8cc8</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const ParameterList &gt;</type>
      <name>getValidParameters</name>
      <anchorfile>classThyra_1_1DefaultBlockedTriangularLinearOpWithSolveFactory.html</anchorfile>
      <anchor>a75b0cedc8e5354265f182c14a6ecd3e8</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>acceptsPreconditionerFactory</name>
      <anchorfile>classThyra_1_1DefaultBlockedTriangularLinearOpWithSolveFactory.html</anchorfile>
      <anchor>a520b66172ebd947fcdaf90a5d23c3fae</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>setPreconditionerFactory</name>
      <anchorfile>classThyra_1_1DefaultBlockedTriangularLinearOpWithSolveFactory.html</anchorfile>
      <anchor>a054409d4ca3132c4521a520a5592bbda</anchor>
      <arglist>(const RCP&lt; PreconditionerFactoryBase&lt; Scalar &gt; &gt; &amp;precFactory, const std::string &amp;precFactoryName)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual RCP&lt; PreconditionerFactoryBase&lt; Scalar &gt; &gt;</type>
      <name>getPreconditionerFactory</name>
      <anchorfile>classThyra_1_1DefaultBlockedTriangularLinearOpWithSolveFactory.html</anchorfile>
      <anchor>a6fc8f910aab51f3a38322d2f178ef55f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>unsetPreconditionerFactory</name>
      <anchorfile>classThyra_1_1DefaultBlockedTriangularLinearOpWithSolveFactory.html</anchorfile>
      <anchor>a6899950202bed887ff8e8532b8ddbba3</anchor>
      <arglist>(RCP&lt; PreconditionerFactoryBase&lt; Scalar &gt; &gt; *precFactory, std::string *precFactoryName)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>isCompatible</name>
      <anchorfile>classThyra_1_1DefaultBlockedTriangularLinearOpWithSolveFactory.html</anchorfile>
      <anchor>af48b32ce0f1b86ddf1ff28355671a356</anchor>
      <arglist>(const LinearOpSourceBase&lt; Scalar &gt; &amp;fwdOpSrc) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual RCP&lt; LinearOpWithSolveBase&lt; Scalar &gt; &gt;</type>
      <name>createOp</name>
      <anchorfile>classThyra_1_1DefaultBlockedTriangularLinearOpWithSolveFactory.html</anchorfile>
      <anchor>a740127ba654be8f129ce58eabc2027c4</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>initializeOp</name>
      <anchorfile>classThyra_1_1DefaultBlockedTriangularLinearOpWithSolveFactory.html</anchorfile>
      <anchor>acd348ee77a6bc9293237a8b42dea0697</anchor>
      <arglist>(const RCP&lt; const LinearOpSourceBase&lt; Scalar &gt; &gt; &amp;fwdOpSrc, LinearOpWithSolveBase&lt; Scalar &gt; *Op, const ESupportSolveUse supportSolveUse) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>initializeAndReuseOp</name>
      <anchorfile>classThyra_1_1DefaultBlockedTriangularLinearOpWithSolveFactory.html</anchorfile>
      <anchor>ab6b3e746fe8c93ad8f77cae47430d9ff</anchor>
      <arglist>(const RCP&lt; const LinearOpSourceBase&lt; Scalar &gt; &gt; &amp;fwdOpSrc, LinearOpWithSolveBase&lt; Scalar &gt; *Op) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>uninitializeOp</name>
      <anchorfile>classThyra_1_1DefaultBlockedTriangularLinearOpWithSolveFactory.html</anchorfile>
      <anchor>aabc42f17d1471e5dfb4ab85786fc2e81</anchor>
      <arglist>(LinearOpWithSolveBase&lt; Scalar &gt; *Op, RCP&lt; const LinearOpSourceBase&lt; Scalar &gt; &gt; *fwdOpSrc, RCP&lt; const PreconditionerBase&lt; Scalar &gt; &gt; *prec, RCP&lt; const LinearOpSourceBase&lt; Scalar &gt; &gt; *approxFwdOpSrc, ESupportSolveUse *supportSolveUse) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>supportsPreconditionerInputType</name>
      <anchorfile>classThyra_1_1DefaultBlockedTriangularLinearOpWithSolveFactory.html</anchorfile>
      <anchor>a5ad94972b89bf47cabdf0738d3ee9adc</anchor>
      <arglist>(const EPreconditionerInputType precOpType) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>initializePreconditionedOp</name>
      <anchorfile>classThyra_1_1DefaultBlockedTriangularLinearOpWithSolveFactory.html</anchorfile>
      <anchor>a9f1298c4b72324a91a7d277bca833e3c</anchor>
      <arglist>(const RCP&lt; const LinearOpSourceBase&lt; Scalar &gt; &gt; &amp;fwdOpSrc, const RCP&lt; const PreconditionerBase&lt; Scalar &gt; &gt; &amp;prec, LinearOpWithSolveBase&lt; Scalar &gt; *Op, const ESupportSolveUse supportSolveUse) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>initializeApproxPreconditionedOp</name>
      <anchorfile>classThyra_1_1DefaultBlockedTriangularLinearOpWithSolveFactory.html</anchorfile>
      <anchor>ab714bb6ab21012ed9e092ad4aeddde08</anchor>
      <arglist>(const RCP&lt; const LinearOpSourceBase&lt; Scalar &gt; &gt; &amp;fwdOpSrc, const RCP&lt; const LinearOpSourceBase&lt; Scalar &gt; &gt; &amp;approxFwdOpSrc, LinearOpWithSolveBase&lt; Scalar &gt; *Op, const ESupportSolveUse supportSolveUse) const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>informUpdatedVerbosityState</name>
      <anchorfile>classThyra_1_1DefaultBlockedTriangularLinearOpWithSolveFactory.html</anchorfile>
      <anchor>a3ae393f75b9060e0d1f1d88f8d1eea62</anchor>
      <arglist>() const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::DefaultClusteredSpmdProductVector</name>
    <filename>classThyra_1_1DefaultClusteredSpmdProductVector.html</filename>
    <templarg></templarg>
    <base virtualness="virtual">Thyra::ProductVectorBase</base>
    <base protection="protected" virtualness="virtual">Thyra::VectorDefaultBase</base>
    <member kind="function">
      <type></type>
      <name>DefaultClusteredSpmdProductVector</name>
      <anchorfile>classThyra_1_1DefaultClusteredSpmdProductVector.html</anchorfile>
      <anchor>aec34a0cdf6b8e2b66814e6d6d92fbf0d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>DefaultClusteredSpmdProductVector</name>
      <anchorfile>classThyra_1_1DefaultClusteredSpmdProductVector.html</anchorfile>
      <anchor>ab6abc18eaf283795a81ce2355b286b70</anchor>
      <arglist>(const Teuchos::RCP&lt; const DefaultClusteredSpmdProductVectorSpace&lt; Scalar &gt; &gt; &amp;productSpace, const Teuchos::RCP&lt; VectorBase&lt; Scalar &gt; &gt; vecs[])</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initialize</name>
      <anchorfile>classThyra_1_1DefaultClusteredSpmdProductVector.html</anchorfile>
      <anchor>a70871790360ba3141d76f9bb74d021b4</anchor>
      <arglist>(const Teuchos::RCP&lt; const DefaultClusteredSpmdProductVectorSpace&lt; Scalar &gt; &gt; &amp;productSpace, const Teuchos::RCP&lt; VectorBase&lt; Scalar &gt; &gt; vecs[])</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>uninitialize</name>
      <anchorfile>classThyra_1_1DefaultClusteredSpmdProductVector.html</anchorfile>
      <anchor>a1fa1c2b2be8a03888c7f32d7a0d4532b</anchor>
      <arglist>(Teuchos::RCP&lt; const DefaultClusteredSpmdProductVectorSpace&lt; Scalar &gt; &gt; *productSpace=NULL, Teuchos::RCP&lt; VectorBase&lt; Scalar &gt; &gt; vecs[]=NULL)</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; VectorBase&lt; Scalar &gt; &gt;</type>
      <name>getNonconstVectorBlock</name>
      <anchorfile>classThyra_1_1DefaultClusteredSpmdProductVector.html</anchorfile>
      <anchor>ad54a9edb2e521a6d4e1f8fb8d93f781e</anchor>
      <arglist>(const int k)</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const VectorBase&lt; Scalar &gt; &gt;</type>
      <name>getVectorBlock</name>
      <anchorfile>classThyra_1_1DefaultClusteredSpmdProductVector.html</anchorfile>
      <anchor>ac403479c7fdbcddb26761ddabccc04b4</anchor>
      <arglist>(const int k) const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const ProductVectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>productSpace</name>
      <anchorfile>classThyra_1_1DefaultClusteredSpmdProductVector.html</anchorfile>
      <anchor>a8f9cf469cf9a4d950d23888bc4f9f718</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>blockIsConst</name>
      <anchorfile>classThyra_1_1DefaultClusteredSpmdProductVector.html</anchorfile>
      <anchor>ae52335fbe70f15898a4236921ae9a369</anchor>
      <arglist>(const int k) const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; MultiVectorBase&lt; Scalar &gt; &gt;</type>
      <name>getNonconstMultiVectorBlock</name>
      <anchorfile>classThyra_1_1DefaultClusteredSpmdProductVector.html</anchorfile>
      <anchor>aaca8e1f574763bc7af411e6382bfe84e</anchor>
      <arglist>(const int k)</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const MultiVectorBase&lt; Scalar &gt; &gt;</type>
      <name>getMultiVectorBlock</name>
      <anchorfile>classThyra_1_1DefaultClusteredSpmdProductVector.html</anchorfile>
      <anchor>a0e3850a754fa40a7e8405e8f0f1ea2b5</anchor>
      <arglist>(const int k) const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const VectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>space</name>
      <anchorfile>classThyra_1_1DefaultClusteredSpmdProductVector.html</anchorfile>
      <anchor>a436e02a3e11ba598e95e65ea53944ef8</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>applyOpImpl</name>
      <anchorfile>classThyra_1_1DefaultClusteredSpmdProductVector.html</anchorfile>
      <anchor>a47c462db830f4dc8eeba8a99c075ac85</anchor>
      <arglist>(const RTOpPack::RTOpT&lt; Scalar &gt; &amp;op, const ArrayView&lt; const Ptr&lt; const VectorBase&lt; Scalar &gt; &gt; &gt; &amp;vecs, const ArrayView&lt; const Ptr&lt; VectorBase&lt; Scalar &gt; &gt; &gt; &amp;targ_vecs, const Ptr&lt; RTOpPack::ReductTarget &gt; &amp;reduct_obj, const Ordinal global_offset) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::DefaultClusteredSpmdProductVectorSpace</name>
    <filename>classThyra_1_1DefaultClusteredSpmdProductVectorSpace.html</filename>
    <templarg></templarg>
    <base>Thyra::ProductVectorSpaceBase</base>
    <base protection="protected">Thyra::VectorSpaceDefaultBase</base>
    <member kind="function">
      <type></type>
      <name>DefaultClusteredSpmdProductVectorSpace</name>
      <anchorfile>classThyra_1_1DefaultClusteredSpmdProductVectorSpace.html</anchorfile>
      <anchor>a62519f836450463daee2e1545cbb200a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>DefaultClusteredSpmdProductVectorSpace</name>
      <anchorfile>classThyra_1_1DefaultClusteredSpmdProductVectorSpace.html</anchorfile>
      <anchor>a730b6aea952894600d1bd5c64cbabea8</anchor>
      <arglist>(const RCP&lt; const Teuchos::Comm&lt; Ordinal &gt; &gt; &amp;intraClusterComm, const int clusterRootRank, const RCP&lt; const Teuchos::Comm&lt; Ordinal &gt; &gt; &amp;interClusterComm, const int numBlocks, const RCP&lt; const VectorSpaceBase&lt; Scalar &gt; &gt; vecSpaces[])</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initialize</name>
      <anchorfile>classThyra_1_1DefaultClusteredSpmdProductVectorSpace.html</anchorfile>
      <anchor>aa4cd634d956a0c0da2f9dd5ef38e5e31</anchor>
      <arglist>(const RCP&lt; const Teuchos::Comm&lt; Ordinal &gt; &gt; &amp;intraClusterComm, const int clusterRootRank, const RCP&lt; const Teuchos::Comm&lt; Ordinal &gt; &gt; &amp;interClusterComm, const int numBlocks, const RCP&lt; const VectorSpaceBase&lt; Scalar &gt; &gt; vecSpaces[])</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const Teuchos::Comm&lt; Ordinal &gt; &gt;</type>
      <name>intraClusterComm</name>
      <anchorfile>classThyra_1_1DefaultClusteredSpmdProductVectorSpace.html</anchorfile>
      <anchor>a7e1bbffd6a7ad7b5a85c3bd7681d7994</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>clusterRootRank</name>
      <anchorfile>classThyra_1_1DefaultClusteredSpmdProductVectorSpace.html</anchorfile>
      <anchor>a6c36fedb61b5ee2ae760d8b9f1caa7a2</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const Teuchos::Comm&lt; Ordinal &gt; &gt;</type>
      <name>interClusterComm</name>
      <anchorfile>classThyra_1_1DefaultClusteredSpmdProductVectorSpace.html</anchorfile>
      <anchor>adfdf58ab6d72a861e8665863046ce8d0</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>clusterSubDim</name>
      <anchorfile>classThyra_1_1DefaultClusteredSpmdProductVectorSpace.html</anchorfile>
      <anchor>a14fde88f0ee4cdf0f37c71a148748641</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>clusterOffset</name>
      <anchorfile>classThyra_1_1DefaultClusteredSpmdProductVectorSpace.html</anchorfile>
      <anchor>a620f6fa98edb7680d27fe2c26f0f7125</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>description</name>
      <anchorfile>classThyra_1_1DefaultClusteredSpmdProductVectorSpace.html</anchorfile>
      <anchor>a3d8a3b0ed0a38004e343087f77b67bdd</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Ordinal</type>
      <name>dim</name>
      <anchorfile>classThyra_1_1DefaultClusteredSpmdProductVectorSpace.html</anchorfile>
      <anchor>aae6bd8561be4745d4a7cc416e722f9cb</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isCompatible</name>
      <anchorfile>classThyra_1_1DefaultClusteredSpmdProductVectorSpace.html</anchorfile>
      <anchor>ae2a2e5cb73249cf629157597ff1d1d90</anchor>
      <arglist>(const VectorSpaceBase&lt; Scalar &gt; &amp;vecSpc) const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const VectorSpaceFactoryBase&lt; Scalar &gt; &gt;</type>
      <name>smallVecSpcFcty</name>
      <anchorfile>classThyra_1_1DefaultClusteredSpmdProductVectorSpace.html</anchorfile>
      <anchor>a1e08dda7468a4ef6c34dcecfdc4a5699</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Scalar</type>
      <name>scalarProd</name>
      <anchorfile>classThyra_1_1DefaultClusteredSpmdProductVectorSpace.html</anchorfile>
      <anchor>ad09a8d248d4b3f4daa42066b8c02b93a</anchor>
      <arglist>(const VectorBase&lt; Scalar &gt; &amp;x, const VectorBase&lt; Scalar &gt; &amp;y) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>scalarProdsImpl</name>
      <anchorfile>classThyra_1_1DefaultClusteredSpmdProductVectorSpace.html</anchorfile>
      <anchor>a077e3cb13d3466bd1391ad2b82102b8b</anchor>
      <arglist>(const MultiVectorBase&lt; Scalar &gt; &amp;X, const MultiVectorBase&lt; Scalar &gt; &amp;Y, const ArrayView&lt; Scalar &gt; &amp;scalarProds) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isEuclidean</name>
      <anchorfile>classThyra_1_1DefaultClusteredSpmdProductVectorSpace.html</anchorfile>
      <anchor>a18ebc1e1282e3745dae92a2b0a6afe4b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>hasInCoreView</name>
      <anchorfile>classThyra_1_1DefaultClusteredSpmdProductVectorSpace.html</anchorfile>
      <anchor>a6ba8e95fd90a687f967abf7594a7b398</anchor>
      <arglist>(const Range1D &amp;rng, const EViewType viewType, const EStrideType strideType) const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const VectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>clone</name>
      <anchorfile>classThyra_1_1DefaultClusteredSpmdProductVectorSpace.html</anchorfile>
      <anchor>ae1d636ef150fd704f846abedeefdf255</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>numBlocks</name>
      <anchorfile>classThyra_1_1DefaultClusteredSpmdProductVectorSpace.html</anchorfile>
      <anchor>a0f77c35ac4c6b38f111f92486802552b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const VectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>getBlock</name>
      <anchorfile>classThyra_1_1DefaultClusteredSpmdProductVectorSpace.html</anchorfile>
      <anchor>adc5afaeacb9a9a297a9b1cc1ea421a65</anchor>
      <arglist>(const int k) const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>RCP&lt; VectorBase&lt; Scalar &gt; &gt;</type>
      <name>createMember</name>
      <anchorfile>classThyra_1_1DefaultClusteredSpmdProductVectorSpace.html</anchorfile>
      <anchor>a375e19e3f5a788143f5def5f663406ef</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>RCP&lt; MultiVectorBase&lt; Scalar &gt; &gt;</type>
      <name>createMembers</name>
      <anchorfile>classThyra_1_1DefaultClusteredSpmdProductVectorSpace.html</anchorfile>
      <anchor>a49f6c50cfd6aa119dccd7b02ba45b75e</anchor>
      <arglist>(int numMembers) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::DefaultColumnwiseMultiVector</name>
    <filename>classThyra_1_1DefaultColumnwiseMultiVector.html</filename>
    <templarg></templarg>
    <base virtualness="virtual">Thyra::MultiVectorDefaultBase</base>
    <member kind="function">
      <type></type>
      <name>DefaultColumnwiseMultiVector</name>
      <anchorfile>classThyra_1_1DefaultColumnwiseMultiVector.html</anchorfile>
      <anchor>acd88963ab7d50aef9b75bf69c0ca5139</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>DefaultColumnwiseMultiVector</name>
      <anchorfile>classThyra_1_1DefaultColumnwiseMultiVector.html</anchorfile>
      <anchor>ad35ae61a9342d33ecd3579ddc5d53194</anchor>
      <arglist>(const RCP&lt; VectorBase&lt; Scalar &gt; &gt; &amp;col_vec)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>DefaultColumnwiseMultiVector</name>
      <anchorfile>classThyra_1_1DefaultColumnwiseMultiVector.html</anchorfile>
      <anchor>ad3631d2b8e8d08d02e103b99ded378d5</anchor>
      <arglist>(const RCP&lt; const VectorSpaceBase&lt; Scalar &gt; &gt; &amp;range, const RCP&lt; const VectorSpaceBase&lt; Scalar &gt; &gt; &amp;domain, const ArrayView&lt; const RCP&lt; VectorBase&lt; Scalar &gt; &gt; &gt; &amp;col_vecs=Teuchos::null)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initialize</name>
      <anchorfile>classThyra_1_1DefaultColumnwiseMultiVector.html</anchorfile>
      <anchor>a98418e9b7de4d048c1f259274b4ab7b5</anchor>
      <arglist>(const RCP&lt; VectorBase&lt; Scalar &gt; &gt; &amp;col_vec)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initialize</name>
      <anchorfile>classThyra_1_1DefaultColumnwiseMultiVector.html</anchorfile>
      <anchor>afb0c77e6eaf7ca5261696f8bb26d9030</anchor>
      <arglist>(const RCP&lt; const VectorSpaceBase&lt; Scalar &gt; &gt; &amp;range, const RCP&lt; const VectorSpaceBase&lt; Scalar &gt; &gt; &amp;domain, const ArrayView&lt; const RCP&lt; VectorBase&lt; Scalar &gt; &gt; &gt; &amp;col_vecs=Teuchos::null)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>uninitialize</name>
      <anchorfile>classThyra_1_1DefaultColumnwiseMultiVector.html</anchorfile>
      <anchor>a61409fff20fc669e4563a2991a9206d1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const VectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>range</name>
      <anchorfile>classThyra_1_1DefaultColumnwiseMultiVector.html</anchorfile>
      <anchor>ad55b91f0bca40f2493b82cc071181925</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const VectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>domain</name>
      <anchorfile>classThyra_1_1DefaultColumnwiseMultiVector.html</anchorfile>
      <anchor>a9cf52ec96efe641ca226a3026bdce953</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; VectorBase&lt; Scalar &gt; &gt;</type>
      <name>nonconstColImpl</name>
      <anchorfile>classThyra_1_1DefaultColumnwiseMultiVector.html</anchorfile>
      <anchor>ad076ff39bf5acfa5b0d52e24980ca4d5</anchor>
      <arglist>(Ordinal j)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; MultiVectorBase&lt; Scalar &gt; &gt;</type>
      <name>nonconstContigSubViewImpl</name>
      <anchorfile>classThyra_1_1DefaultColumnwiseMultiVector.html</anchorfile>
      <anchor>a2afbf390c454675608557becf5a1540c</anchor>
      <arglist>(const Range1D &amp;col_rng)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>assignImpl</name>
      <anchorfile>classThyra_1_1DefaultColumnwiseMultiVector.html</anchorfile>
      <anchor>a9d3dec35936f1fc7b995db116cba50f2</anchor>
      <arglist>(Scalar alpha)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>bool</type>
      <name>opSupportedImpl</name>
      <anchorfile>classThyra_1_1DefaultColumnwiseMultiVector.html</anchorfile>
      <anchor>a27b1441f2b2134103fd91b8482813917</anchor>
      <arglist>(EOpTransp M_trans) const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>applyImpl</name>
      <anchorfile>classThyra_1_1DefaultColumnwiseMultiVector.html</anchorfile>
      <anchor>a7c4250ade3620366a02a45d9e4160483</anchor>
      <arglist>(const EOpTransp M_trans, const MultiVectorBase&lt; Scalar &gt; &amp;X, const Ptr&lt; MultiVectorBase&lt; Scalar &gt; &gt; &amp;Y, const Scalar alpha, const Scalar beta) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::DefaultDiagonalLinearOp</name>
    <filename>classThyra_1_1DefaultDiagonalLinearOp.html</filename>
    <templarg></templarg>
    <base virtualness="virtual">Thyra::DiagonalLinearOpBase</base>
    <member kind="function">
      <type>RCP&lt; const LinearOpBase&lt; Scalar &gt; &gt;</type>
      <name>diagonal</name>
      <anchorfile>classThyra_1_1DefaultDiagonalLinearOp.html</anchorfile>
      <anchor>aaeb5e28ed4c6f9141717fee37b494c0c</anchor>
      <arglist>(const RCP&lt; VectorBase&lt; Scalar &gt; &gt; &amp;diag, const std::string &amp;label=&quot;&quot;)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>DefaultDiagonalLinearOp</name>
      <anchorfile>classThyra_1_1DefaultDiagonalLinearOp.html</anchorfile>
      <anchor>a8a43d211b755a14b599ff85939b7ec48</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>DefaultDiagonalLinearOp</name>
      <anchorfile>classThyra_1_1DefaultDiagonalLinearOp.html</anchorfile>
      <anchor>aa90d043b6e02d17fa5712f669e716425</anchor>
      <arglist>(const RCP&lt; const VectorSpaceBase&lt; Scalar &gt; &gt; &amp;space)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>DefaultDiagonalLinearOp</name>
      <anchorfile>classThyra_1_1DefaultDiagonalLinearOp.html</anchorfile>
      <anchor>a99dabe8c0dba4b91bc614694c1269f5d</anchor>
      <arglist>(const RCP&lt; VectorBase&lt; Scalar &gt; &gt; &amp;diag)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>DefaultDiagonalLinearOp</name>
      <anchorfile>classThyra_1_1DefaultDiagonalLinearOp.html</anchorfile>
      <anchor>a10ed0978371a610be5fe0b2f7ed69abb</anchor>
      <arglist>(const RCP&lt; const VectorBase&lt; Scalar &gt; &gt; &amp;diag)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initialize</name>
      <anchorfile>classThyra_1_1DefaultDiagonalLinearOp.html</anchorfile>
      <anchor>a28c0d5e602d3285c3cce80157d535d53</anchor>
      <arglist>(const RCP&lt; const VectorSpaceBase&lt; Scalar &gt; &gt; &amp;space)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initialize</name>
      <anchorfile>classThyra_1_1DefaultDiagonalLinearOp.html</anchorfile>
      <anchor>a6cc93df9afc8a8e02d3e8f7a467df41d</anchor>
      <arglist>(const RCP&lt; VectorBase&lt; Scalar &gt; &gt; &amp;diag)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initialize</name>
      <anchorfile>classThyra_1_1DefaultDiagonalLinearOp.html</anchorfile>
      <anchor>a72d5c1f14b5a1d5a89a10f1fb0c10ab2</anchor>
      <arglist>(const RCP&lt; const VectorBase&lt; Scalar &gt; &gt; &amp;diag)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>uninitialize</name>
      <anchorfile>classThyra_1_1DefaultDiagonalLinearOp.html</anchorfile>
      <anchor>a04cea4b6b862be07f2b8e73b3325749b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isDiagConst</name>
      <anchorfile>classThyra_1_1DefaultDiagonalLinearOp.html</anchorfile>
      <anchor>a8a4346e96fbc9a1766c8293014c946ff</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; VectorBase&lt; Scalar &gt; &gt;</type>
      <name>getNonconstDiag</name>
      <anchorfile>classThyra_1_1DefaultDiagonalLinearOp.html</anchorfile>
      <anchor>a4f40eb8b9cb601b525feece4c00b6f5c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const VectorBase&lt; Scalar &gt; &gt;</type>
      <name>getDiag</name>
      <anchorfile>classThyra_1_1DefaultDiagonalLinearOp.html</anchorfile>
      <anchor>a227d376cc3eeafad7807bd95ec82ad81</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const VectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>range</name>
      <anchorfile>classThyra_1_1DefaultDiagonalLinearOp.html</anchorfile>
      <anchor>a3823baaaff578828cb23c2559137fb24</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const VectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>domain</name>
      <anchorfile>classThyra_1_1DefaultDiagonalLinearOp.html</anchorfile>
      <anchor>a309f352d7698b2da1214b1b6c076d5fd</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const LinearOpBase&lt; Scalar &gt; &gt;</type>
      <name>clone</name>
      <anchorfile>classThyra_1_1DefaultDiagonalLinearOp.html</anchorfile>
      <anchor>ad21e73e70a1c5892d5d17ce75a35c677</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>bool</type>
      <name>opSupportedImpl</name>
      <anchorfile>classThyra_1_1DefaultDiagonalLinearOp.html</anchorfile>
      <anchor>a5784593064b1c3aed8d5d2977b5d4474</anchor>
      <arglist>(EOpTransp M_trans) const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>applyImpl</name>
      <anchorfile>classThyra_1_1DefaultDiagonalLinearOp.html</anchorfile>
      <anchor>a49a9a27b17222974bf7e498a9ca97456</anchor>
      <arglist>(const EOpTransp M_trans, const MultiVectorBase&lt; Scalar &gt; &amp;X, const Ptr&lt; MultiVectorBase&lt; Scalar &gt; &gt; &amp;Y, const Scalar alpha, const Scalar beta) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::DefaultDiagonalLinearOpWithSolve</name>
    <filename>classThyra_1_1DefaultDiagonalLinearOpWithSolve.html</filename>
    <templarg>Scalar</templarg>
    <base virtualness="virtual">Thyra::DefaultDiagonalLinearOp</base>
    <base virtualness="virtual">Thyra::LinearOpWithSolveBase</base>
    <member kind="function">
      <type>RCP&lt; DefaultDiagonalLinearOpWithSolve&lt; Scalar &gt; &gt;</type>
      <name>defaultDiagonalLinearOpWithSolve</name>
      <anchorfile>classThyra_1_1DefaultDiagonalLinearOpWithSolve.html</anchorfile>
      <anchor>a999606b22074a3a7d79714e0573eac18</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; DefaultDiagonalLinearOpWithSolve&lt; Scalar &gt; &gt;</type>
      <name>defaultDiagonalLinearOpWithSolve</name>
      <anchorfile>classThyra_1_1DefaultDiagonalLinearOpWithSolve.html</anchorfile>
      <anchor>a4ff106dada3c72f80b9cf3c593fc6440</anchor>
      <arglist>(const RCP&lt; const VectorBase&lt; Scalar &gt; &gt; &amp;diag)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>DefaultDiagonalLinearOpWithSolve</name>
      <anchorfile>classThyra_1_1DefaultDiagonalLinearOpWithSolve.html</anchorfile>
      <anchor>ad00b53673967126d5e4cb7d5e93d790e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>DefaultDiagonalLinearOpWithSolve</name>
      <anchorfile>classThyra_1_1DefaultDiagonalLinearOpWithSolve.html</anchorfile>
      <anchor>ac4260752af0e3057ddf310b718d01386</anchor>
      <arglist>(const RCP&lt; const VectorBase&lt; Scalar &gt; &gt; &amp;diag)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>bool</type>
      <name>solveSupportsImpl</name>
      <anchorfile>classThyra_1_1DefaultDiagonalLinearOpWithSolve.html</anchorfile>
      <anchor>a0b20a2e8060118faa2bb6eb070e3b1d6</anchor>
      <arglist>(EOpTransp M_trans) const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>bool</type>
      <name>solveSupportsSolveMeasureTypeImpl</name>
      <anchorfile>classThyra_1_1DefaultDiagonalLinearOpWithSolve.html</anchorfile>
      <anchor>a132d5898a3b499070d2aa78e44b42747</anchor>
      <arglist>(EOpTransp M_trans, const SolveMeasureType &amp;solveMeasureType) const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>SolveStatus&lt; Scalar &gt;</type>
      <name>solveImpl</name>
      <anchorfile>classThyra_1_1DefaultDiagonalLinearOpWithSolve.html</anchorfile>
      <anchor>a3bee0154e32dc1dc34fdc78a7f7325fe</anchor>
      <arglist>(const EOpTransp transp, const MultiVectorBase&lt; Scalar &gt; &amp;B, const Ptr&lt; MultiVectorBase&lt; Scalar &gt; &gt; &amp;X, const Ptr&lt; const SolveCriteria&lt; Scalar &gt; &gt; solveCriteria) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::DefaultEvaluationLoggerModelEvaluator</name>
    <filename>classThyra_1_1DefaultEvaluationLoggerModelEvaluator.html</filename>
    <templarg></templarg>
    <base virtualness="virtual">Thyra::ModelEvaluatorDelegatorBase</base>
    <member kind="function">
      <type></type>
      <name>DefaultEvaluationLoggerModelEvaluator</name>
      <anchorfile>classThyra_1_1DefaultEvaluationLoggerModelEvaluator.html</anchorfile>
      <anchor>a4bd08390d755777b2e523de23e8704ba</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>DefaultEvaluationLoggerModelEvaluator</name>
      <anchorfile>classThyra_1_1DefaultEvaluationLoggerModelEvaluator.html</anchorfile>
      <anchor>aed82794a729e9e63c4e9ccd8e599543a</anchor>
      <arglist>(const RCP&lt; ModelEvaluator&lt; Scalar &gt; &gt; &amp;thyraModel, const RCP&lt; std::ostream &gt; &amp;tableOut)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initialize</name>
      <anchorfile>classThyra_1_1DefaultEvaluationLoggerModelEvaluator.html</anchorfile>
      <anchor>ad61a2d47286c6e871c82a3f827fb8aa5</anchor>
      <arglist>(const RCP&lt; ModelEvaluator&lt; Scalar &gt; &gt; &amp;thyraModel, const RCP&lt; std::ostream &gt; &amp;tableOut)</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>description</name>
      <anchorfile>classThyra_1_1DefaultEvaluationLoggerModelEvaluator.html</anchorfile>
      <anchor>a0ac217d907db6bde201fdf59786985fa</anchor>
      <arglist>() const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::DefaultFinalPointCaptureModelEvaluator</name>
    <filename>classThyra_1_1DefaultFinalPointCaptureModelEvaluator.html</filename>
    <templarg></templarg>
    <base virtualness="virtual">Thyra::ModelEvaluatorDelegatorBase</base>
    <member kind="typedef">
      <type>Teuchos::ScalarTraits&lt; Scalar &gt;::magnitudeType</type>
      <name>ScalarMag</name>
      <anchorfile>classThyra_1_1DefaultFinalPointCaptureModelEvaluator.html</anchorfile>
      <anchor>acaeb930950705a2b1368fc88fbb82ec4</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>DefaultFinalPointCaptureModelEvaluator</name>
      <anchorfile>classThyra_1_1DefaultFinalPointCaptureModelEvaluator.html</anchorfile>
      <anchor>a67ffd37da409a633ce1b0a5e82da65b3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>DefaultFinalPointCaptureModelEvaluator</name>
      <anchorfile>classThyra_1_1DefaultFinalPointCaptureModelEvaluator.html</anchorfile>
      <anchor>a145e9e95f47fe1eefa1bb36cdf23fc44</anchor>
      <arglist>(const Teuchos::RCP&lt; ModelEvaluator&lt; Scalar &gt; &gt; &amp;thyraModel)</arglist>
    </member>
    <member kind="function">
      <type>const ModelEvaluatorBase::InArgs&lt; Scalar &gt; &amp;</type>
      <name>getFinalPoint</name>
      <anchorfile>classThyra_1_1DefaultFinalPointCaptureModelEvaluator.html</anchorfile>
      <anchor>a9d69bc061ec61e49b680ac9452cb4cb9</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>finalPointWasSolved</name>
      <anchorfile>classThyra_1_1DefaultFinalPointCaptureModelEvaluator.html</anchorfile>
      <anchor>a05905023a25f397b18677dcfc53a74bf</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>description</name>
      <anchorfile>classThyra_1_1DefaultFinalPointCaptureModelEvaluator.html</anchorfile>
      <anchor>a10c2cda99528b66828d65acda855e9ea</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>reportFinalPoint</name>
      <anchorfile>classThyra_1_1DefaultFinalPointCaptureModelEvaluator.html</anchorfile>
      <anchor>aa0beb400f774d75fccc4c66882d20075</anchor>
      <arglist>(const ModelEvaluatorBase::InArgs&lt; Scalar &gt; &amp;finalPoint, const bool wasSolved)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::DefaultFiniteDifferenceModelEvaluator</name>
    <filename>classThyra_1_1DefaultFiniteDifferenceModelEvaluator.html</filename>
    <templarg></templarg>
    <base virtualness="virtual">Thyra::ModelEvaluatorDelegatorBase</base>
    <member kind="function">
      <type>RCP&lt; DefaultFiniteDifferenceModelEvaluator&lt; Scalar &gt; &gt;</type>
      <name>defaultFiniteDifferenceModelEvaluator</name>
      <anchorfile>classThyra_1_1DefaultFiniteDifferenceModelEvaluator.html</anchorfile>
      <anchor>a77354ad0e6684c28187b12a3d558cd18</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; DefaultFiniteDifferenceModelEvaluator&lt; Scalar &gt; &gt;</type>
      <name>defaultFiniteDifferenceModelEvaluator</name>
      <anchorfile>classThyra_1_1DefaultFiniteDifferenceModelEvaluator.html</anchorfile>
      <anchor>a153cfed65ec3d542eb88bc75d3753c58</anchor>
      <arglist>(const RCP&lt; ModelEvaluator&lt; Scalar &gt; &gt; &amp;thyraModel, const RCP&lt; DirectionalFiniteDiffCalculator&lt; Scalar &gt; &gt; &amp;direcFiniteDiffCalculator)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_COMPOSITION_MEMBERS</name>
      <anchorfile>classThyra_1_1DefaultFiniteDifferenceModelEvaluator.html</anchorfile>
      <anchor>a0de089f25c2b3f0cee98f7118ec7764b</anchor>
      <arglist>(DirectionalFiniteDiffCalculator&lt; Scalar &gt;, direcFiniteDiffCalculator)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>DefaultFiniteDifferenceModelEvaluator</name>
      <anchorfile>classThyra_1_1DefaultFiniteDifferenceModelEvaluator.html</anchorfile>
      <anchor>ace20436d1c5fd492b64fee6b381baa39</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initialize</name>
      <anchorfile>classThyra_1_1DefaultFiniteDifferenceModelEvaluator.html</anchorfile>
      <anchor>a358d244b411544769bab3d5ac28b7379</anchor>
      <arglist>(const RCP&lt; ModelEvaluator&lt; Scalar &gt; &gt; &amp;thyraModel, const RCP&lt; DirectionalFiniteDiffCalculator&lt; Scalar &gt; &gt; &amp;direcFiniteDiffCalculator)</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>description</name>
      <anchorfile>classThyra_1_1DefaultFiniteDifferenceModelEvaluator.html</anchorfile>
      <anchor>af91f258e59414d3609a36dd9c2f08352</anchor>
      <arglist>() const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::DefaultIdentityLinearOp</name>
    <filename>classThyra_1_1DefaultIdentityLinearOp.html</filename>
    <templarg></templarg>
    <base virtualness="virtual">Thyra::IdentityLinearOpBase</base>
    <member kind="function">
      <type>RCP&lt; const LinearOpBase&lt; Scalar &gt; &gt;</type>
      <name>identity</name>
      <anchorfile>classThyra_1_1DefaultIdentityLinearOp.html</anchorfile>
      <anchor>a24bc5c4d6de27d6c841d5f7811c134ad</anchor>
      <arglist>(const RCP&lt; const VectorSpaceBase&lt; Scalar &gt; &gt; &amp;space, const std::string &amp;label=&quot;&quot;)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>DefaultIdentityLinearOp</name>
      <anchorfile>classThyra_1_1DefaultIdentityLinearOp.html</anchorfile>
      <anchor>a0be8421f39f7d025e5697a716bdf2aa9</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>DefaultIdentityLinearOp</name>
      <anchorfile>classThyra_1_1DefaultIdentityLinearOp.html</anchorfile>
      <anchor>ab2c1af53cabd04d6c78ee9e5f7b63600</anchor>
      <arglist>(const RCP&lt; const VectorSpaceBase&lt; Scalar &gt; &gt; &amp;space)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initialize</name>
      <anchorfile>classThyra_1_1DefaultIdentityLinearOp.html</anchorfile>
      <anchor>ac5fae91854cec5a429ad1e0d0edcd819</anchor>
      <arglist>(const RCP&lt; const VectorSpaceBase&lt; Scalar &gt; &gt; &amp;space)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>uninitialize</name>
      <anchorfile>classThyra_1_1DefaultIdentityLinearOp.html</anchorfile>
      <anchor>acc77d0eaeedfdbc676cb704e2c7723f3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const VectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>range</name>
      <anchorfile>classThyra_1_1DefaultIdentityLinearOp.html</anchorfile>
      <anchor>a7247773b551797e3fa3d287884e2b073</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const VectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>domain</name>
      <anchorfile>classThyra_1_1DefaultIdentityLinearOp.html</anchorfile>
      <anchor>a66e79cc42554c7bceeae9b25c79b190a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const LinearOpBase&lt; Scalar &gt; &gt;</type>
      <name>clone</name>
      <anchorfile>classThyra_1_1DefaultIdentityLinearOp.html</anchorfile>
      <anchor>ae727e00d7d44d1adc8ecc9c8918fdb79</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>bool</type>
      <name>opSupportedImpl</name>
      <anchorfile>classThyra_1_1DefaultIdentityLinearOp.html</anchorfile>
      <anchor>aa1c7300fcd0d5798ce0c368fa6199b53</anchor>
      <arglist>(EOpTransp M_trans) const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>applyImpl</name>
      <anchorfile>classThyra_1_1DefaultIdentityLinearOp.html</anchorfile>
      <anchor>abc5bb959db9c2edf33d05c394f550d13</anchor>
      <arglist>(const EOpTransp M_trans, const MultiVectorBase&lt; Scalar &gt; &amp;X, const Ptr&lt; MultiVectorBase&lt; Scalar &gt; &gt; &amp;Y, const Scalar alpha, const Scalar beta) const </arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>description</name>
      <anchorfile>classThyra_1_1DefaultIdentityLinearOp.html</anchorfile>
      <anchor>acfb9863c01d9fcee3197b990a81904e6</anchor>
      <arglist>() const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::DefaultInverseLinearOp</name>
    <filename>classThyra_1_1DefaultInverseLinearOp.html</filename>
    <templarg></templarg>
    <base virtualness="virtual">Thyra::InverseLinearOpBase</base>
    <member kind="function">
      <type>RCP&lt; LinearOpBase&lt; Scalar &gt; &gt;</type>
      <name>nonconstInverse</name>
      <anchorfile>classThyra_1_1DefaultInverseLinearOp.html</anchorfile>
      <anchor>a07634101f85817e4e4c68d9b4de753a3</anchor>
      <arglist>(const RCP&lt; LinearOpWithSolveBase&lt; Scalar &gt; &gt; &amp;A, const Ptr&lt; const SolveCriteria&lt; Scalar &gt; &gt; &amp;fwdSolveCriteria=Teuchos::null, const EThrowOnSolveFailure throwOnFwdSolveFailure=THROW_ON_SOLVE_FAILURE, const Ptr&lt; const SolveCriteria&lt; Scalar &gt; &gt; &amp;adjSolveCriteria=Teuchos::null, const EThrowOnSolveFailure throwOnAdjSolveFailure=THROW_ON_SOLVE_FAILURE)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; LinearOpBase&lt; Scalar &gt; &gt;</type>
      <name>inverse</name>
      <anchorfile>classThyra_1_1DefaultInverseLinearOp.html</anchorfile>
      <anchor>ac5c90a354839ad43e08aa79084cee7eb</anchor>
      <arglist>(const RCP&lt; const LinearOpWithSolveBase&lt; Scalar &gt; &gt; &amp;A, const Ptr&lt; const SolveCriteria&lt; Scalar &gt; &gt; &amp;fwdSolveCriteria=Teuchos::null, const EThrowOnSolveFailure throwOnFwdSolveFailure=THROW_ON_SOLVE_FAILURE, const Ptr&lt; const SolveCriteria&lt; Scalar &gt; &gt; &amp;adjSolveCriteria=Teuchos::null, const EThrowOnSolveFailure throwOnAdjSolveFailure=THROW_ON_SOLVE_FAILURE)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>DefaultInverseLinearOp</name>
      <anchorfile>classThyra_1_1DefaultInverseLinearOp.html</anchorfile>
      <anchor>a47d7e6d0ac2e0872b242617233197b18</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>DefaultInverseLinearOp</name>
      <anchorfile>classThyra_1_1DefaultInverseLinearOp.html</anchorfile>
      <anchor>af87eb23a8142fa97361ae4809006e538</anchor>
      <arglist>(const RCP&lt; LinearOpWithSolveBase&lt; Scalar &gt; &gt; &amp;lows, const SolveCriteria&lt; Scalar &gt; *fwdSolveCriteria=NULL, const EThrowOnSolveFailure throwOnFwdSolveFailure=THROW_ON_SOLVE_FAILURE, const SolveCriteria&lt; Scalar &gt; *adjSolveCriteria=NULL, const EThrowOnSolveFailure throwOnAdjSolveFailure=THROW_ON_SOLVE_FAILURE)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>DefaultInverseLinearOp</name>
      <anchorfile>classThyra_1_1DefaultInverseLinearOp.html</anchorfile>
      <anchor>aad08287545d405d14d712d4bde3f9e79</anchor>
      <arglist>(const RCP&lt; const LinearOpWithSolveBase&lt; Scalar &gt; &gt; &amp;lows, const SolveCriteria&lt; Scalar &gt; *fwdSolveCriteria=NULL, const EThrowOnSolveFailure throwOnFwdSolveFailure=THROW_ON_SOLVE_FAILURE, const SolveCriteria&lt; Scalar &gt; *adjSolveCriteria=NULL, const EThrowOnSolveFailure throwOnAdjSolveFailure=THROW_ON_SOLVE_FAILURE)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initialize</name>
      <anchorfile>classThyra_1_1DefaultInverseLinearOp.html</anchorfile>
      <anchor>a2b4853732e24f4f0914b9c92184c7054</anchor>
      <arglist>(const RCP&lt; LinearOpWithSolveBase&lt; Scalar &gt; &gt; &amp;lows, const SolveCriteria&lt; Scalar &gt; *fwdSolveCriteria=NULL, const EThrowOnSolveFailure throwOnFwdSolveFailure=THROW_ON_SOLVE_FAILURE, const SolveCriteria&lt; Scalar &gt; *adjSolveCriteria=NULL, const EThrowOnSolveFailure throwOnAdjSolveFailure=THROW_ON_SOLVE_FAILURE)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initialize</name>
      <anchorfile>classThyra_1_1DefaultInverseLinearOp.html</anchorfile>
      <anchor>a60582dcb49caeb4211c30806335b1bea</anchor>
      <arglist>(const RCP&lt; const LinearOpWithSolveBase&lt; Scalar &gt; &gt; &amp;lows, const SolveCriteria&lt; Scalar &gt; *fwdSolveCriteria=NULL, const EThrowOnSolveFailure throwOnFwdSolveFailure=THROW_ON_SOLVE_FAILURE, const SolveCriteria&lt; Scalar &gt; *adjSolveCriteria=NULL, const EThrowOnSolveFailure throwOnAdjSolveFailure=THROW_ON_SOLVE_FAILURE)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>uninitialize</name>
      <anchorfile>classThyra_1_1DefaultInverseLinearOp.html</anchorfile>
      <anchor>a4a841e97c6a0eaa103c83b277a8ca199</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isLowsConst</name>
      <anchorfile>classThyra_1_1DefaultInverseLinearOp.html</anchorfile>
      <anchor>af195910e1a9208b921c34b4e3ebd8eab</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; LinearOpWithSolveBase&lt; Scalar &gt; &gt;</type>
      <name>getNonconstLows</name>
      <anchorfile>classThyra_1_1DefaultInverseLinearOp.html</anchorfile>
      <anchor>acdcf1d1dd2349c88569c3c4eee1bb616</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const LinearOpWithSolveBase&lt; Scalar &gt; &gt;</type>
      <name>getLows</name>
      <anchorfile>classThyra_1_1DefaultInverseLinearOp.html</anchorfile>
      <anchor>a273b0b4530b18c5bce5b830476a63b6c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const VectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>range</name>
      <anchorfile>classThyra_1_1DefaultInverseLinearOp.html</anchorfile>
      <anchor>aa66a88bd384a00a5cac7af3fc4cec30d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const VectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>domain</name>
      <anchorfile>classThyra_1_1DefaultInverseLinearOp.html</anchorfile>
      <anchor>ae239a43a792dac173407175a6dbf6b64</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const LinearOpBase&lt; Scalar &gt; &gt;</type>
      <name>clone</name>
      <anchorfile>classThyra_1_1DefaultInverseLinearOp.html</anchorfile>
      <anchor>aa2b49fcdac0a19f2f6e4ae2b20435c7a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>bool</type>
      <name>opSupportedImpl</name>
      <anchorfile>classThyra_1_1DefaultInverseLinearOp.html</anchorfile>
      <anchor>a95b821b32db5610397155029982319b7</anchor>
      <arglist>(EOpTransp M_trans) const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>applyImpl</name>
      <anchorfile>classThyra_1_1DefaultInverseLinearOp.html</anchorfile>
      <anchor>a49cabe372c79117696815edad04776aa</anchor>
      <arglist>(const EOpTransp M_trans, const MultiVectorBase&lt; Scalar &gt; &amp;X, const Ptr&lt; MultiVectorBase&lt; Scalar &gt; &gt; &amp;Y, const Scalar alpha, const Scalar beta) const </arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>description</name>
      <anchorfile>classThyra_1_1DefaultInverseLinearOp.html</anchorfile>
      <anchor>a8c99b05c929195ad60a30ebf13e25b97</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>describe</name>
      <anchorfile>classThyra_1_1DefaultInverseLinearOp.html</anchorfile>
      <anchor>a537c3b062a0032645db10e1fc5b07e85</anchor>
      <arglist>(FancyOStream &amp;out, const Teuchos::EVerbosityLevel verbLevel) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::DefaultInverseModelEvaluator</name>
    <filename>classThyra_1_1DefaultInverseModelEvaluator.html</filename>
    <templarg></templarg>
    <base virtualness="virtual">Thyra::ModelEvaluatorDelegatorBase</base>
    <base virtualness="virtual">Teuchos::ParameterListAcceptor</base>
    <member kind="function">
      <type></type>
      <name>STANDARD_CONST_COMPOSITION_MEMBERS</name>
      <anchorfile>classThyra_1_1DefaultInverseModelEvaluator.html</anchorfile>
      <anchor>a14e72cafc6bfc6ff6eeaf51f0c9f6f38</anchor>
      <arglist>(VectorBase&lt; Scalar &gt;, observationTarget)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_CONST_COMPOSITION_MEMBERS</name>
      <anchorfile>classThyra_1_1DefaultInverseModelEvaluator.html</anchorfile>
      <anchor>aed636e3c084bf30c25c95edee2244866</anchor>
      <arglist>(VectorBase&lt; Scalar &gt;, parameterBase)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_CONST_COMPOSITION_MEMBERS</name>
      <anchorfile>classThyra_1_1DefaultInverseModelEvaluator.html</anchorfile>
      <anchor>a161bd24212fd82f06c5c9a37d09ff11e</anchor>
      <arglist>(LinearOpBase&lt; Scalar &gt;, observationMatchWeightingOp)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_CONST_COMPOSITION_MEMBERS</name>
      <anchorfile>classThyra_1_1DefaultInverseModelEvaluator.html</anchorfile>
      <anchor>a6ad56c24e27bafb1848708ed17c34e5f</anchor>
      <arglist>(LinearOpBase&lt; Scalar &gt;, parameterRegularizationWeightingOp)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_NONCONST_COMPOSITION_MEMBERS</name>
      <anchorfile>classThyra_1_1DefaultInverseModelEvaluator.html</anchorfile>
      <anchor>a2b010befce1df3f5b6f606a8f0b4b566</anchor>
      <arglist>(MultiVectorFileIOBase&lt; Scalar &gt;, observationTargetIO)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_NONCONST_COMPOSITION_MEMBERS</name>
      <anchorfile>classThyra_1_1DefaultInverseModelEvaluator.html</anchorfile>
      <anchor>ad35071b5851da098cf1aed7da45d2c93</anchor>
      <arglist>(MultiVectorFileIOBase&lt; Scalar &gt;, parameterBaseIO)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; DefaultInverseModelEvaluator&lt; Scalar &gt; &gt;</type>
      <name>defaultInverseModelEvaluator</name>
      <anchorfile>classThyra_1_1DefaultInverseModelEvaluator.html</anchorfile>
      <anchor>ad5a93960c8b42ea751fd3b3a92cf9cc5</anchor>
      <arglist>(const RCP&lt; ModelEvaluator&lt; Scalar &gt; &gt; &amp;thyraModel)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>DefaultInverseModelEvaluator</name>
      <anchorfile>classThyra_1_1DefaultInverseModelEvaluator.html</anchorfile>
      <anchor>afc18e5a9ea07921a12205a7cf767e9e7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initialize</name>
      <anchorfile>classThyra_1_1DefaultInverseModelEvaluator.html</anchorfile>
      <anchor>a35098948fa9945f76cf5625731591657</anchor>
      <arglist>(const RCP&lt; ModelEvaluator&lt; Scalar &gt; &gt; &amp;thyraModel)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>uninitialize</name>
      <anchorfile>classThyra_1_1DefaultInverseModelEvaluator.html</anchorfile>
      <anchor>a4f5b1386c156928e1f09caa4ed3cc4e2</anchor>
      <arglist>(RCP&lt; ModelEvaluator&lt; Scalar &gt; &gt; *thyraModel)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setParameterList</name>
      <anchorfile>classThyra_1_1DefaultInverseModelEvaluator.html</anchorfile>
      <anchor>adb124cf1625132c7c72e5f49a6b9864a</anchor>
      <arglist>(RCP&lt; Teuchos::ParameterList &gt; const &amp;paramList)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; Teuchos::ParameterList &gt;</type>
      <name>getNonconstParameterList</name>
      <anchorfile>classThyra_1_1DefaultInverseModelEvaluator.html</anchorfile>
      <anchor>af4d2d888269433c727a1cd9ca17bc21b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; Teuchos::ParameterList &gt;</type>
      <name>unsetParameterList</name>
      <anchorfile>classThyra_1_1DefaultInverseModelEvaluator.html</anchorfile>
      <anchor>a8e372ff1207f8afe3997d18ab9a9718b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const Teuchos::ParameterList &gt;</type>
      <name>getParameterList</name>
      <anchorfile>classThyra_1_1DefaultInverseModelEvaluator.html</anchorfile>
      <anchor>a532b70b3b3b3c4f4c2c3a3622af570f5</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const Teuchos::ParameterList &gt;</type>
      <name>getValidParameters</name>
      <anchorfile>classThyra_1_1DefaultInverseModelEvaluator.html</anchorfile>
      <anchor>aa06f1211deec2dd6239e80b5563fb134</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>description</name>
      <anchorfile>classThyra_1_1DefaultInverseModelEvaluator.html</anchorfile>
      <anchor>adb02a46c220a7396347b115d38f9e9e3</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const VectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>get_p_space</name>
      <anchorfile>classThyra_1_1DefaultInverseModelEvaluator.html</anchorfile>
      <anchor>ab131cc6b8fa14a01f6309a8c78c6b352</anchor>
      <arglist>(int l) const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const VectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>get_g_space</name>
      <anchorfile>classThyra_1_1DefaultInverseModelEvaluator.html</anchorfile>
      <anchor>aa09f09be0c4a1c021a64c49bbd5476e2</anchor>
      <arglist>(int j) const </arglist>
    </member>
    <member kind="function">
      <type>ModelEvaluatorBase::InArgs&lt; Scalar &gt;</type>
      <name>createInArgs</name>
      <anchorfile>classThyra_1_1DefaultInverseModelEvaluator.html</anchorfile>
      <anchor>ae91ab6bdde0d26e283784e87641767b1</anchor>
      <arglist>() const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::DefaultLinearOpSource</name>
    <filename>classThyra_1_1DefaultLinearOpSource.html</filename>
    <templarg></templarg>
    <base virtualness="virtual">Thyra::LinearOpSourceBase</base>
    <member kind="function">
      <type>Teuchos::RCP&lt; const DefaultLinearOpSource&lt; Scalar &gt; &gt;</type>
      <name>defaultLinearOpSource</name>
      <anchorfile>classThyra_1_1DefaultLinearOpSource.html</anchorfile>
      <anchor>a81e31551ec39eb2878b3ebc32d635268</anchor>
      <arglist>(const Teuchos::RCP&lt; const LinearOpBase&lt; Scalar &gt; &gt; &amp;op)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>DefaultLinearOpSource</name>
      <anchorfile>classThyra_1_1DefaultLinearOpSource.html</anchorfile>
      <anchor>a7a355e709a583a5b753748c4b7514578</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>DefaultLinearOpSource</name>
      <anchorfile>classThyra_1_1DefaultLinearOpSource.html</anchorfile>
      <anchor>a40a4a3f3c8dada41546b1e361756b9d3</anchor>
      <arglist>(const Teuchos::RCP&lt; LinearOpBase&lt; Scalar &gt; &gt; &amp;op)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>DefaultLinearOpSource</name>
      <anchorfile>classThyra_1_1DefaultLinearOpSource.html</anchorfile>
      <anchor>a2b0b808204b5d7833fa1f630afb6d4bb</anchor>
      <arglist>(const Teuchos::RCP&lt; const LinearOpBase&lt; Scalar &gt; &gt; &amp;op)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initialize</name>
      <anchorfile>classThyra_1_1DefaultLinearOpSource.html</anchorfile>
      <anchor>a2974fe032f6a7f239b782956318fca88</anchor>
      <arglist>(const Teuchos::RCP&lt; LinearOpBase&lt; Scalar &gt; &gt; &amp;op)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initialize</name>
      <anchorfile>classThyra_1_1DefaultLinearOpSource.html</anchorfile>
      <anchor>ac290bae4c285453cb0a442bbffd94b22</anchor>
      <arglist>(const Teuchos::RCP&lt; const LinearOpBase&lt; Scalar &gt; &gt; &amp;op)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>uninitialize</name>
      <anchorfile>classThyra_1_1DefaultLinearOpSource.html</anchorfile>
      <anchor>abc51c7511f7ac25f31b9c1b7f2b74140</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isOpConst</name>
      <anchorfile>classThyra_1_1DefaultLinearOpSource.html</anchorfile>
      <anchor>af59f8361474d74d230a796e7e992cf51</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; LinearOpBase&lt; Scalar &gt; &gt;</type>
      <name>getNonconstOp</name>
      <anchorfile>classThyra_1_1DefaultLinearOpSource.html</anchorfile>
      <anchor>a9f990220bbf02938c7a09c8871ff7f81</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const LinearOpBase&lt; Scalar &gt; &gt;</type>
      <name>getOp</name>
      <anchorfile>classThyra_1_1DefaultLinearOpSource.html</anchorfile>
      <anchor>abb6e4f7d9d145abd66cfc539a7b75023</anchor>
      <arglist>() const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::DefaultLumpedParameterModelEvaluator</name>
    <filename>classThyra_1_1DefaultLumpedParameterModelEvaluator.html</filename>
    <templarg></templarg>
    <base virtualness="virtual">Thyra::ModelEvaluatorDelegatorBase</base>
    <base virtualness="virtual">Teuchos::ParameterListAcceptor</base>
    <member kind="function">
      <type>RCP&lt; DefaultLumpedParameterModelEvaluator&lt; Scalar &gt; &gt;</type>
      <name>defaultLumpedParameterModelEvaluator</name>
      <anchorfile>classThyra_1_1DefaultLumpedParameterModelEvaluator.html</anchorfile>
      <anchor>a5f4e9aa77f6de7fb195290158097497c</anchor>
      <arglist>(const RCP&lt; ModelEvaluator&lt; Scalar &gt; &gt; &amp;thyraModel)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>DefaultLumpedParameterModelEvaluator</name>
      <anchorfile>classThyra_1_1DefaultLumpedParameterModelEvaluator.html</anchorfile>
      <anchor>aa7ce95fdba39b82bf9d6a46c83915b3c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initialize</name>
      <anchorfile>classThyra_1_1DefaultLumpedParameterModelEvaluator.html</anchorfile>
      <anchor>ae791b04d9e7b54ffd3cbf519771de457</anchor>
      <arglist>(const RCP&lt; ModelEvaluator&lt; Scalar &gt; &gt; &amp;thyraModel)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>uninitialize</name>
      <anchorfile>classThyra_1_1DefaultLumpedParameterModelEvaluator.html</anchorfile>
      <anchor>a2b01885f55d25e873a363b57c3eac7bb</anchor>
      <arglist>(RCP&lt; ModelEvaluator&lt; Scalar &gt; &gt; *thyraModel)</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>description</name>
      <anchorfile>classThyra_1_1DefaultLumpedParameterModelEvaluator.html</anchorfile>
      <anchor>a411a9f4c770a0cdec9f16208ee9cb3d1</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setParameterList</name>
      <anchorfile>classThyra_1_1DefaultLumpedParameterModelEvaluator.html</anchorfile>
      <anchor>a4eb4dd444932c0431f5ebce78a05ee27</anchor>
      <arglist>(RCP&lt; Teuchos::ParameterList &gt; const &amp;paramList)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; Teuchos::ParameterList &gt;</type>
      <name>getNonconstParameterList</name>
      <anchorfile>classThyra_1_1DefaultLumpedParameterModelEvaluator.html</anchorfile>
      <anchor>a3ea54647146d9edd75b2ba9a204ae7e7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; Teuchos::ParameterList &gt;</type>
      <name>unsetParameterList</name>
      <anchorfile>classThyra_1_1DefaultLumpedParameterModelEvaluator.html</anchorfile>
      <anchor>aa59f39cd380230f3804c8aec15dd894b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const Teuchos::ParameterList &gt;</type>
      <name>getParameterList</name>
      <anchorfile>classThyra_1_1DefaultLumpedParameterModelEvaluator.html</anchorfile>
      <anchor>a205fccfcb9e86917d91b97a3c7c1d90b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const Teuchos::ParameterList &gt;</type>
      <name>getValidParameters</name>
      <anchorfile>classThyra_1_1DefaultLumpedParameterModelEvaluator.html</anchorfile>
      <anchor>a9517bf2263a728c1e165810dbf6245f6</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const VectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>get_p_space</name>
      <anchorfile>classThyra_1_1DefaultLumpedParameterModelEvaluator.html</anchorfile>
      <anchor>a4dc7d8559acf3e080321f2de563e3d2c</anchor>
      <arglist>(int l) const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const Array&lt; std::string &gt; &gt;</type>
      <name>get_p_names</name>
      <anchorfile>classThyra_1_1DefaultLumpedParameterModelEvaluator.html</anchorfile>
      <anchor>a0d726de45d54749b3a918811aab456a4</anchor>
      <arglist>(int l) const </arglist>
    </member>
    <member kind="function">
      <type>ModelEvaluatorBase::InArgs&lt; Scalar &gt;</type>
      <name>getNominalValues</name>
      <anchorfile>classThyra_1_1DefaultLumpedParameterModelEvaluator.html</anchorfile>
      <anchor>a1f67690d781a11a2a591c142a6b9e4ea</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>ModelEvaluatorBase::InArgs&lt; Scalar &gt;</type>
      <name>getLowerBounds</name>
      <anchorfile>classThyra_1_1DefaultLumpedParameterModelEvaluator.html</anchorfile>
      <anchor>a989ce8162d79867de7977bb79867d2fe</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>ModelEvaluatorBase::InArgs&lt; Scalar &gt;</type>
      <name>getUpperBounds</name>
      <anchorfile>classThyra_1_1DefaultLumpedParameterModelEvaluator.html</anchorfile>
      <anchor>a1d702cba4f379244d5fa5cd71f7f2183</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>reportFinalPoint</name>
      <anchorfile>classThyra_1_1DefaultLumpedParameterModelEvaluator.html</anchorfile>
      <anchor>af0f3050f14c3a1f58dc08c1bc80a158e</anchor>
      <arglist>(const ModelEvaluatorBase::InArgs&lt; Scalar &gt; &amp;finalPoint, const bool wasSolved)</arglist>
    </member>
    <docanchor file="classThyra_1_1DefaultLumpedParameterModelEvaluator" title="Introduction">Thyra_DefaultLumpedParameterModelEvaluator_intro_sec</docanchor>
    <docanchor file="classThyra_1_1DefaultLumpedParameterModelEvaluator" title="Derivatives">Thyra_DefaultLumpedParameterModelEvaluator_derivs_sec</docanchor>
    <docanchor file="classThyra_1_1DefaultLumpedParameterModelEvaluator" title="Mapping between fully and reduced parameters">Thyra_DefaultLumpedParameterModelEvaluator_mapping_sec</docanchor>
    <docanchor file="classThyra_1_1DefaultLumpedParameterModelEvaluator" title="Parameter bounds">Thyra_DefaultLumpedParameterModelEvaluator_bounds_sec</docanchor>
  </compound>
  <compound kind="class">
    <name>Thyra::DefaultModelEvaluatorWithSolveFactory</name>
    <filename>classThyra_1_1DefaultModelEvaluatorWithSolveFactory.html</filename>
    <templarg></templarg>
    <base virtualness="virtual">Thyra::ModelEvaluatorDelegatorBase</base>
    <member kind="function">
      <type></type>
      <name>DefaultModelEvaluatorWithSolveFactory</name>
      <anchorfile>classThyra_1_1DefaultModelEvaluatorWithSolveFactory.html</anchorfile>
      <anchor>ab411bff68d1afca8aa8f3a88ca07c8e0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>DefaultModelEvaluatorWithSolveFactory</name>
      <anchorfile>classThyra_1_1DefaultModelEvaluatorWithSolveFactory.html</anchorfile>
      <anchor>ae1162bebc31f810f29c9f04adee69987</anchor>
      <arglist>(const RCP&lt; ModelEvaluator&lt; Scalar &gt; &gt; &amp;thyraModel, const RCP&lt; LinearOpWithSolveFactoryBase&lt; Scalar &gt; &gt; &amp;W_factory)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initialize</name>
      <anchorfile>classThyra_1_1DefaultModelEvaluatorWithSolveFactory.html</anchorfile>
      <anchor>a502aa4da5fa3699ee3f6ca9477545b88</anchor>
      <arglist>(const RCP&lt; ModelEvaluator&lt; Scalar &gt; &gt; &amp;thyraModel, const RCP&lt; LinearOpWithSolveFactoryBase&lt; Scalar &gt; &gt; &amp;W_factory)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>uninitialize</name>
      <anchorfile>classThyra_1_1DefaultModelEvaluatorWithSolveFactory.html</anchorfile>
      <anchor>a368df38b03159b7ac88bd2e6e6ff3cf3</anchor>
      <arglist>(RCP&lt; ModelEvaluator&lt; Scalar &gt; &gt; *thyraModel=NULL, RCP&lt; LinearOpWithSolveFactoryBase&lt; Scalar &gt; &gt; *W_factory=NULL)</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>description</name>
      <anchorfile>classThyra_1_1DefaultModelEvaluatorWithSolveFactory.html</anchorfile>
      <anchor>a64cfe0524e6fb040d2317bb30364624d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; LinearOpWithSolveBase&lt; Scalar &gt; &gt;</type>
      <name>create_W</name>
      <anchorfile>classThyra_1_1DefaultModelEvaluatorWithSolveFactory.html</anchorfile>
      <anchor>a482c08f67b33ad5fc587e62f46a2346c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const LinearOpWithSolveFactoryBase&lt; Scalar &gt; &gt;</type>
      <name>get_W_factory</name>
      <anchorfile>classThyra_1_1DefaultModelEvaluatorWithSolveFactory.html</anchorfile>
      <anchor>a409046900aea62aaf3f6ec0df79e9d13</anchor>
      <arglist>() const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::DefaultMultiPeriodModelEvaluator</name>
    <filename>classThyra_1_1DefaultMultiPeriodModelEvaluator.html</filename>
    <templarg></templarg>
    <base virtualness="virtual">Thyra::ModelEvaluatorDefaultBase</base>
    <member kind="function">
      <type></type>
      <name>DefaultMultiPeriodModelEvaluator</name>
      <anchorfile>classThyra_1_1DefaultMultiPeriodModelEvaluator.html</anchorfile>
      <anchor>a3cba2585edf8554f98a80cbb4f0cd31c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>DefaultMultiPeriodModelEvaluator</name>
      <anchorfile>classThyra_1_1DefaultMultiPeriodModelEvaluator.html</anchorfile>
      <anchor>a9364ece68970e7c780eef10a00ec9ac1</anchor>
      <arglist>(const int N, const Array&lt; RCP&lt; ModelEvaluator&lt; Scalar &gt; &gt; &gt; &amp;periodModels, const Array&lt; int &gt; &amp;z_indexes, const Array&lt; Array&lt; RCP&lt; const VectorBase&lt; Scalar &gt; &gt; &gt; &gt; &amp;z, const int g_index, const Array&lt; Scalar &gt; g_weights, const RCP&lt; const ProductVectorSpaceBase&lt; Scalar &gt; &gt; &amp;x_bar_space=Teuchos::null, const RCP&lt; const ProductVectorSpaceBase&lt; Scalar &gt; &gt; &amp;f_bar_space=Teuchos::null, const RCP&lt; LinearOpWithSolveFactoryBase&lt; Scalar &gt; &gt; &amp;W_bar_factory=Teuchos::null)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initialize</name>
      <anchorfile>classThyra_1_1DefaultMultiPeriodModelEvaluator.html</anchorfile>
      <anchor>ad8c6c8d168b113b3400d0a945762fe61</anchor>
      <arglist>(const int N, const Array&lt; RCP&lt; ModelEvaluator&lt; Scalar &gt; &gt; &gt; &amp;periodModels, const Array&lt; int &gt; &amp;z_indexes, const Array&lt; Array&lt; RCP&lt; const VectorBase&lt; Scalar &gt; &gt; &gt; &gt; &amp;z, const int g_index, const Array&lt; Scalar &gt; g_weights, const RCP&lt; const ProductVectorSpaceBase&lt; Scalar &gt; &gt; &amp;x_bar_space=Teuchos::null, const RCP&lt; const ProductVectorSpaceBase&lt; Scalar &gt; &gt; &amp;f_bar_space=Teuchos::null, const RCP&lt; LinearOpWithSolveFactoryBase&lt; Scalar &gt; &gt; &amp;W_bar_factory=Teuchos::null)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>reset_z</name>
      <anchorfile>classThyra_1_1DefaultMultiPeriodModelEvaluator.html</anchorfile>
      <anchor>aae4890977fc2978fc05e45051e8610e7</anchor>
      <arglist>(const Array&lt; Array&lt; RCP&lt; const VectorBase&lt; Scalar &gt; &gt; &gt; &gt; &amp;z)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Np</name>
      <anchorfile>classThyra_1_1DefaultMultiPeriodModelEvaluator.html</anchorfile>
      <anchor>aa2636c9c77166f09108bb7b6e7dcec52</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Ng</name>
      <anchorfile>classThyra_1_1DefaultMultiPeriodModelEvaluator.html</anchorfile>
      <anchor>ad1600327131d64dfa9a46a5bee1328ab</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const VectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>get_x_space</name>
      <anchorfile>classThyra_1_1DefaultMultiPeriodModelEvaluator.html</anchorfile>
      <anchor>ac521180e8a60c4e5de8c3aa67e20bdbf</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const VectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>get_f_space</name>
      <anchorfile>classThyra_1_1DefaultMultiPeriodModelEvaluator.html</anchorfile>
      <anchor>af81c458f885513b1252339ebdb80a617</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const VectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>get_p_space</name>
      <anchorfile>classThyra_1_1DefaultMultiPeriodModelEvaluator.html</anchorfile>
      <anchor>af649a5d4e2b3b9cf00ada3b711ce590e</anchor>
      <arglist>(int l) const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const Array&lt; std::string &gt; &gt;</type>
      <name>get_p_names</name>
      <anchorfile>classThyra_1_1DefaultMultiPeriodModelEvaluator.html</anchorfile>
      <anchor>a246b6c8e11b285108aaf8e6b474f8f2e</anchor>
      <arglist>(int l) const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const VectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>get_g_space</name>
      <anchorfile>classThyra_1_1DefaultMultiPeriodModelEvaluator.html</anchorfile>
      <anchor>ab90e2e5dcabb12748d621bc2a2b49459</anchor>
      <arglist>(int j) const </arglist>
    </member>
    <member kind="function">
      <type>ArrayView&lt; const std::string &gt;</type>
      <name>get_g_names</name>
      <anchorfile>classThyra_1_1DefaultMultiPeriodModelEvaluator.html</anchorfile>
      <anchor>aea262ac5dcf6a961ccc19b5f8115617f</anchor>
      <arglist>(int j) const </arglist>
    </member>
    <member kind="function">
      <type>ModelEvaluatorBase::InArgs&lt; Scalar &gt;</type>
      <name>getNominalValues</name>
      <anchorfile>classThyra_1_1DefaultMultiPeriodModelEvaluator.html</anchorfile>
      <anchor>a2ee1376c92838c631222de4369008965</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>ModelEvaluatorBase::InArgs&lt; Scalar &gt;</type>
      <name>getLowerBounds</name>
      <anchorfile>classThyra_1_1DefaultMultiPeriodModelEvaluator.html</anchorfile>
      <anchor>a3ae9df377f47fa966033b62eb01d5212</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>ModelEvaluatorBase::InArgs&lt; Scalar &gt;</type>
      <name>getUpperBounds</name>
      <anchorfile>classThyra_1_1DefaultMultiPeriodModelEvaluator.html</anchorfile>
      <anchor>a87da72690f8a22a62bb66b032c2e0f23</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; LinearOpBase&lt; Scalar &gt; &gt;</type>
      <name>create_W_op</name>
      <anchorfile>classThyra_1_1DefaultMultiPeriodModelEvaluator.html</anchorfile>
      <anchor>aa1badbe6b7d15282cfafbd6b727c112b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; PreconditionerBase&lt; Scalar &gt; &gt;</type>
      <name>create_W_prec</name>
      <anchorfile>classThyra_1_1DefaultMultiPeriodModelEvaluator.html</anchorfile>
      <anchor>a9de5304a2f94798ed97d3ba05af44f50</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const LinearOpWithSolveFactoryBase&lt; Scalar &gt; &gt;</type>
      <name>get_W_factory</name>
      <anchorfile>classThyra_1_1DefaultMultiPeriodModelEvaluator.html</anchorfile>
      <anchor>a39c494bf3d63a49b15bb06a8531c1514</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>ModelEvaluatorBase::InArgs&lt; Scalar &gt;</type>
      <name>createInArgs</name>
      <anchorfile>classThyra_1_1DefaultMultiPeriodModelEvaluator.html</anchorfile>
      <anchor>a61f94fb4d8428fd828799f8b552372ac</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>reportFinalPoint</name>
      <anchorfile>classThyra_1_1DefaultMultiPeriodModelEvaluator.html</anchorfile>
      <anchor>ad40856b3c82f490c5634b54325e95922</anchor>
      <arglist>(const ModelEvaluatorBase::InArgs&lt; Scalar &gt; &amp;finalPoint, const bool wasSolved)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::DefaultMultipliedLinearOp</name>
    <filename>classThyra_1_1DefaultMultipliedLinearOp.html</filename>
    <templarg></templarg>
    <base virtualness="virtual">Thyra::MultipliedLinearOpBase</base>
    <member kind="function">
      <type>RCP&lt; DefaultMultipliedLinearOp&lt; Scalar &gt; &gt;</type>
      <name>defaultMultipliedLinearOp</name>
      <anchorfile>classThyra_1_1DefaultMultipliedLinearOp.html</anchorfile>
      <anchor>a7d90c5768979d81e2259e9150f1449bf</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; DefaultMultipliedLinearOp&lt; Scalar &gt; &gt;</type>
      <name>defaultMultipliedLinearOp</name>
      <anchorfile>classThyra_1_1DefaultMultipliedLinearOp.html</anchorfile>
      <anchor>ac822af0f582facb8a6567ec9973d28d8</anchor>
      <arglist>(const ArrayView&lt; const RCP&lt; LinearOpBase&lt; Scalar &gt; &gt; &gt; &amp;Ops)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; DefaultMultipliedLinearOp&lt; Scalar &gt; &gt;</type>
      <name>defaultMultipliedLinearOp</name>
      <anchorfile>classThyra_1_1DefaultMultipliedLinearOp.html</anchorfile>
      <anchor>a2ac2ecec57e3345e9279782f426a0ef8</anchor>
      <arglist>(const ArrayView&lt; const RCP&lt; const LinearOpBase&lt; Scalar &gt; &gt; &gt; &amp;Ops)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; LinearOpBase&lt; Scalar &gt; &gt;</type>
      <name>nonconstMultiply</name>
      <anchorfile>classThyra_1_1DefaultMultipliedLinearOp.html</anchorfile>
      <anchor>a03b30121a8bec77055c3dab36fa3dae4</anchor>
      <arglist>(const RCP&lt; LinearOpBase&lt; Scalar &gt; &gt; &amp;A, const RCP&lt; LinearOpBase&lt; Scalar &gt; &gt; &amp;B, const std::string &amp;M_label=&quot;&quot;)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const LinearOpBase&lt; Scalar &gt; &gt;</type>
      <name>multiply</name>
      <anchorfile>classThyra_1_1DefaultMultipliedLinearOp.html</anchorfile>
      <anchor>aa5870f5a39464ed2009a9a27f9c9a33f</anchor>
      <arglist>(const RCP&lt; const LinearOpBase&lt; Scalar &gt; &gt; &amp;A, const RCP&lt; const LinearOpBase&lt; Scalar &gt; &gt; &amp;B, const std::string &amp;M_label=&quot;&quot;)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const LinearOpBase&lt; Scalar &gt; &gt;</type>
      <name>multiply</name>
      <anchorfile>classThyra_1_1DefaultMultipliedLinearOp.html</anchorfile>
      <anchor>a914dcddaaa945ed1a1fc12894391a50f</anchor>
      <arglist>(const RCP&lt; const LinearOpBase&lt; Scalar &gt; &gt; &amp;A, const RCP&lt; const LinearOpBase&lt; Scalar &gt; &gt; &amp;B, const RCP&lt; const LinearOpBase&lt; Scalar &gt; &gt; &amp;C, const std::string &amp;M_label=&quot;&quot;)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>DefaultMultipliedLinearOp</name>
      <anchorfile>classThyra_1_1DefaultMultipliedLinearOp.html</anchorfile>
      <anchor>a5a189d01e820a8340ee618789cf3c5cb</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initialize</name>
      <anchorfile>classThyra_1_1DefaultMultipliedLinearOp.html</anchorfile>
      <anchor>a58a3b7215ac10cf7292d3395a662e4c2</anchor>
      <arglist>(const ArrayView&lt; const RCP&lt; LinearOpBase&lt; Scalar &gt; &gt; &gt; &amp;Ops)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initialize</name>
      <anchorfile>classThyra_1_1DefaultMultipliedLinearOp.html</anchorfile>
      <anchor>a1af3ddd60323a0cb1e8ec0977031e50c</anchor>
      <arglist>(const ArrayView&lt; const RCP&lt; const LinearOpBase&lt; Scalar &gt; &gt; &gt; &amp;Ops)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>uninitialize</name>
      <anchorfile>classThyra_1_1DefaultMultipliedLinearOp.html</anchorfile>
      <anchor>a103e3d6f0f9a01b86f705de4bc9f48db</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>numOps</name>
      <anchorfile>classThyra_1_1DefaultMultipliedLinearOp.html</anchorfile>
      <anchor>a0af79400b2729041cf73a92d79a278ab</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>opIsConst</name>
      <anchorfile>classThyra_1_1DefaultMultipliedLinearOp.html</anchorfile>
      <anchor>a6e4541e3d266416501776cedcb00a414</anchor>
      <arglist>(const int k) const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; LinearOpBase&lt; Scalar &gt; &gt;</type>
      <name>getNonconstOp</name>
      <anchorfile>classThyra_1_1DefaultMultipliedLinearOp.html</anchorfile>
      <anchor>a8f1b5566397dfbc10b413317c755a09a</anchor>
      <arglist>(const int k)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const LinearOpBase&lt; Scalar &gt; &gt;</type>
      <name>getOp</name>
      <anchorfile>classThyra_1_1DefaultMultipliedLinearOp.html</anchorfile>
      <anchor>a903a4972bd17cddb14bbc8d52bc42ec0</anchor>
      <arglist>(const int k) const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const VectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>range</name>
      <anchorfile>classThyra_1_1DefaultMultipliedLinearOp.html</anchorfile>
      <anchor>a44d48146f71dd84aefa7f0d4271eb886</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const VectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>domain</name>
      <anchorfile>classThyra_1_1DefaultMultipliedLinearOp.html</anchorfile>
      <anchor>a95e7438d5538c528d064609c0260442b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const LinearOpBase&lt; Scalar &gt; &gt;</type>
      <name>clone</name>
      <anchorfile>classThyra_1_1DefaultMultipliedLinearOp.html</anchorfile>
      <anchor>addf0dcbae48fcfe7ea41659381e26f7e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>bool</type>
      <name>opSupportedImpl</name>
      <anchorfile>classThyra_1_1DefaultMultipliedLinearOp.html</anchorfile>
      <anchor>a8f6f383ceed374a74034576cb5955986</anchor>
      <arglist>(EOpTransp M_trans) const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>applyImpl</name>
      <anchorfile>classThyra_1_1DefaultMultipliedLinearOp.html</anchorfile>
      <anchor>a64684ffc3843764d484c21c24b6b84a2</anchor>
      <arglist>(const EOpTransp M_trans, const MultiVectorBase&lt; Scalar &gt; &amp;X, const Ptr&lt; MultiVectorBase&lt; Scalar &gt; &gt; &amp;Y, const Scalar alpha, const Scalar beta) const </arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>description</name>
      <anchorfile>classThyra_1_1DefaultMultipliedLinearOp.html</anchorfile>
      <anchor>a079e173a70df4ae9965391748dbd0d6b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>describe</name>
      <anchorfile>classThyra_1_1DefaultMultipliedLinearOp.html</anchorfile>
      <anchor>aff671cba66999bda3834abe0207f6169</anchor>
      <arglist>(Teuchos::FancyOStream &amp;out, const Teuchos::EVerbosityLevel verbLevel) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::DefaultMultiVectorLinearOpWithSolve</name>
    <filename>classThyra_1_1DefaultMultiVectorLinearOpWithSolve.html</filename>
    <templarg></templarg>
    <base virtualness="virtual">Thyra::LinearOpWithSolveBase</base>
    <member kind="function">
      <type>RCP&lt; DefaultMultiVectorLinearOpWithSolve&lt; Scalar &gt; &gt;</type>
      <name>multiVectorLinearOpWithSolve</name>
      <anchorfile>classThyra_1_1DefaultMultiVectorLinearOpWithSolve.html</anchorfile>
      <anchor>ababc13928cb8597fc7ecfb8a52b82f6f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; DefaultMultiVectorLinearOpWithSolve&lt; Scalar &gt; &gt;</type>
      <name>nonconstMultiVectorLinearOpWithSolve</name>
      <anchorfile>classThyra_1_1DefaultMultiVectorLinearOpWithSolve.html</anchorfile>
      <anchor>a1be531fb89244482ded9a624c6d371af</anchor>
      <arglist>(const RCP&lt; LinearOpWithSolveBase&lt; Scalar &gt; &gt; &amp;lows, const RCP&lt; const DefaultMultiVectorProductVectorSpace&lt; Scalar &gt; &gt; &amp;multiVecRange, const RCP&lt; const DefaultMultiVectorProductVectorSpace&lt; Scalar &gt; &gt; &amp;multiVecDomain)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; DefaultMultiVectorLinearOpWithSolve&lt; Scalar &gt; &gt;</type>
      <name>multiVectorLinearOpWithSolve</name>
      <anchorfile>classThyra_1_1DefaultMultiVectorLinearOpWithSolve.html</anchorfile>
      <anchor>a27f1e272e9c060d4376f57429dc0687b</anchor>
      <arglist>(const RCP&lt; const LinearOpWithSolveBase&lt; Scalar &gt; &gt; &amp;lows, const RCP&lt; const DefaultMultiVectorProductVectorSpace&lt; Scalar &gt; &gt; &amp;multiVecRange, const RCP&lt; const DefaultMultiVectorProductVectorSpace&lt; Scalar &gt; &gt; &amp;multiVecDomain)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>DefaultMultiVectorLinearOpWithSolve</name>
      <anchorfile>classThyra_1_1DefaultMultiVectorLinearOpWithSolve.html</anchorfile>
      <anchor>a361289d9285a54d2ed7eee5fbe45e25d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>nonconstInitialize</name>
      <anchorfile>classThyra_1_1DefaultMultiVectorLinearOpWithSolve.html</anchorfile>
      <anchor>ac0c9284ca5424fa7fc62728e80ffff39</anchor>
      <arglist>(const RCP&lt; LinearOpWithSolveBase&lt; Scalar &gt; &gt; &amp;lows, const RCP&lt; const DefaultMultiVectorProductVectorSpace&lt; Scalar &gt; &gt; &amp;multiVecRange, const RCP&lt; const DefaultMultiVectorProductVectorSpace&lt; Scalar &gt; &gt; &amp;multiVecDomain)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initialize</name>
      <anchorfile>classThyra_1_1DefaultMultiVectorLinearOpWithSolve.html</anchorfile>
      <anchor>aedd21d559873f6ae62451298d6ad0667</anchor>
      <arglist>(const RCP&lt; const LinearOpWithSolveBase&lt; Scalar &gt; &gt; &amp;lows, const RCP&lt; const DefaultMultiVectorProductVectorSpace&lt; Scalar &gt; &gt; &amp;multiVecRange, const RCP&lt; const DefaultMultiVectorProductVectorSpace&lt; Scalar &gt; &gt; &amp;multiVecDomain)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; LinearOpWithSolveBase&lt; Scalar &gt; &gt;</type>
      <name>getNonconstLinearOpWithSolve</name>
      <anchorfile>classThyra_1_1DefaultMultiVectorLinearOpWithSolve.html</anchorfile>
      <anchor>a034c1e04e1abdaed9aebe5b8c70d488a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const LinearOpWithSolveBase&lt; Scalar &gt; &gt;</type>
      <name>getLinearOpWithSolve</name>
      <anchorfile>classThyra_1_1DefaultMultiVectorLinearOpWithSolve.html</anchorfile>
      <anchor>a10f5f0b8dcf4a3f1e39049f26db3cf44</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>uninitialize</name>
      <anchorfile>classThyra_1_1DefaultMultiVectorLinearOpWithSolve.html</anchorfile>
      <anchor>aff26d1370af634535c629b3201344e5a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const VectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>range</name>
      <anchorfile>classThyra_1_1DefaultMultiVectorLinearOpWithSolve.html</anchorfile>
      <anchor>a86e8cb3eee3b5574fc63ff2936cfadd7</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const VectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>domain</name>
      <anchorfile>classThyra_1_1DefaultMultiVectorLinearOpWithSolve.html</anchorfile>
      <anchor>a7c32c0f5864f645d3a0be5017e61c00c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const LinearOpBase&lt; Scalar &gt; &gt;</type>
      <name>clone</name>
      <anchorfile>classThyra_1_1DefaultMultiVectorLinearOpWithSolve.html</anchorfile>
      <anchor>a438899a4fbb10bec606cb880ddf510b8</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>bool</type>
      <name>opSupportedImpl</name>
      <anchorfile>classThyra_1_1DefaultMultiVectorLinearOpWithSolve.html</anchorfile>
      <anchor>a7439a39c44294770ab25204de98cb36a</anchor>
      <arglist>(EOpTransp M_trans) const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>applyImpl</name>
      <anchorfile>classThyra_1_1DefaultMultiVectorLinearOpWithSolve.html</anchorfile>
      <anchor>a6aa41255acc4c6b666aa19b14e0eca81</anchor>
      <arglist>(const EOpTransp M_trans, const MultiVectorBase&lt; Scalar &gt; &amp;X, const Ptr&lt; MultiVectorBase&lt; Scalar &gt; &gt; &amp;Y, const Scalar alpha, const Scalar beta) const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>bool</type>
      <name>solveSupportsImpl</name>
      <anchorfile>classThyra_1_1DefaultMultiVectorLinearOpWithSolve.html</anchorfile>
      <anchor>a37bc97601fe7e64ff0683983c6c47686</anchor>
      <arglist>(EOpTransp M_trans) const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>bool</type>
      <name>solveSupportsSolveMeasureTypeImpl</name>
      <anchorfile>classThyra_1_1DefaultMultiVectorLinearOpWithSolve.html</anchorfile>
      <anchor>afa47d9bc134bc985bde3c54993a03319</anchor>
      <arglist>(EOpTransp M_trans, const SolveMeasureType &amp;solveMeasureType) const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>SolveStatus&lt; Scalar &gt;</type>
      <name>solveImpl</name>
      <anchorfile>classThyra_1_1DefaultMultiVectorLinearOpWithSolve.html</anchorfile>
      <anchor>a440ac1973e628d92ca79388b9e8d7ea5</anchor>
      <arglist>(const EOpTransp transp, const MultiVectorBase&lt; Scalar &gt; &amp;B, const Ptr&lt; MultiVectorBase&lt; Scalar &gt; &gt; &amp;X, const Ptr&lt; const SolveCriteria&lt; Scalar &gt; &gt; solveCriteria) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::DefaultMultiVectorProductVector</name>
    <filename>classThyra_1_1DefaultMultiVectorProductVector.html</filename>
    <templarg></templarg>
    <base virtualness="virtual">Thyra::ProductVectorBase</base>
    <base protection="protected" virtualness="virtual">Thyra::VectorDefaultBase</base>
    <member kind="function">
      <type>RCP&lt; DefaultMultiVectorProductVector&lt; Scalar &gt; &gt;</type>
      <name>multiVectorProductVector</name>
      <anchorfile>classThyra_1_1DefaultMultiVectorProductVector.html</anchorfile>
      <anchor>a06089be6e4bf60191a63b15bf473e2ae</anchor>
      <arglist>(const RCP&lt; const DefaultMultiVectorProductVectorSpace&lt; Scalar &gt; &gt; &amp;productSpace, const RCP&lt; MultiVectorBase&lt; Scalar &gt; &gt; &amp;multiVec)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const DefaultMultiVectorProductVector&lt; Scalar &gt; &gt;</type>
      <name>multiVectorProductVector</name>
      <anchorfile>classThyra_1_1DefaultMultiVectorProductVector.html</anchorfile>
      <anchor>a6e12dfc389deb81ccb72a373affa1e06</anchor>
      <arglist>(const RCP&lt; const DefaultMultiVectorProductVectorSpace&lt; Scalar &gt; &gt; &amp;productSpace, const RCP&lt; const MultiVectorBase&lt; Scalar &gt; &gt; &amp;multiVec)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; DefaultMultiVectorProductVector&lt; Scalar &gt; &gt;</type>
      <name>multiVectorProductVector</name>
      <anchorfile>classThyra_1_1DefaultMultiVectorProductVector.html</anchorfile>
      <anchor>a7a96a177186253ff35222670c7da98b8</anchor>
      <arglist>(const RCP&lt; const DefaultMultiVectorProductVectorSpace&lt; Scalar &gt; &gt; &amp;productSpace)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>DefaultMultiVectorProductVector</name>
      <anchorfile>classThyra_1_1DefaultMultiVectorProductVector.html</anchorfile>
      <anchor>a666f923ac8b6873948c756862587bd33</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initialize</name>
      <anchorfile>classThyra_1_1DefaultMultiVectorProductVector.html</anchorfile>
      <anchor>a24836344371b5b48473f4f793fdf0688</anchor>
      <arglist>(const RCP&lt; const DefaultMultiVectorProductVectorSpace&lt; Scalar &gt; &gt; &amp;productSpace, const RCP&lt; MultiVectorBase&lt; Scalar &gt; &gt; &amp;multiVec)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initialize</name>
      <anchorfile>classThyra_1_1DefaultMultiVectorProductVector.html</anchorfile>
      <anchor>aaad7d866c86d670f7e4c1035c49666cd</anchor>
      <arglist>(const RCP&lt; const DefaultMultiVectorProductVectorSpace&lt; Scalar &gt; &gt; &amp;productSpace, const RCP&lt; const MultiVectorBase&lt; Scalar &gt; &gt; &amp;multiVec)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; MultiVectorBase&lt; Scalar &gt; &gt;</type>
      <name>getNonconstMultiVector</name>
      <anchorfile>classThyra_1_1DefaultMultiVectorProductVector.html</anchorfile>
      <anchor>af088c5a0c9b3b09fa1028dee886a49fd</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const MultiVectorBase&lt; Scalar &gt; &gt;</type>
      <name>getMultiVector</name>
      <anchorfile>classThyra_1_1DefaultMultiVectorProductVector.html</anchorfile>
      <anchor>a0d3379b64c96b8c489cfb53b971b2b7b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>uninitialize</name>
      <anchorfile>classThyra_1_1DefaultMultiVectorProductVector.html</anchorfile>
      <anchor>a03b2fcf39bb7977dea56aa78c3be64af</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>description</name>
      <anchorfile>classThyra_1_1DefaultMultiVectorProductVector.html</anchorfile>
      <anchor>a8c809047c51ce04055ac17a8e5d83a89</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>describe</name>
      <anchorfile>classThyra_1_1DefaultMultiVectorProductVector.html</anchorfile>
      <anchor>afbad982174c25d1d6a789f47d58c6076</anchor>
      <arglist>(Teuchos::FancyOStream &amp;out, const Teuchos::EVerbosityLevel verbLevel) const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; VectorBase&lt; Scalar &gt; &gt;</type>
      <name>getNonconstVectorBlock</name>
      <anchorfile>classThyra_1_1DefaultMultiVectorProductVector.html</anchorfile>
      <anchor>ae1d94c910ec0ba91b8eed795455082f4</anchor>
      <arglist>(const int k)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const VectorBase&lt; Scalar &gt; &gt;</type>
      <name>getVectorBlock</name>
      <anchorfile>classThyra_1_1DefaultMultiVectorProductVector.html</anchorfile>
      <anchor>af0148edb9c9eb292f8c5de2bc8c7860b</anchor>
      <arglist>(const int k) const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const ProductVectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>productSpace</name>
      <anchorfile>classThyra_1_1DefaultMultiVectorProductVector.html</anchorfile>
      <anchor>af4895a3b887b1d20e6944c66f0d9bb28</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>blockIsConst</name>
      <anchorfile>classThyra_1_1DefaultMultiVectorProductVector.html</anchorfile>
      <anchor>a6a6f76b297d06dcf32fd650634f53931</anchor>
      <arglist>(const int k) const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; MultiVectorBase&lt; Scalar &gt; &gt;</type>
      <name>getNonconstMultiVectorBlock</name>
      <anchorfile>classThyra_1_1DefaultMultiVectorProductVector.html</anchorfile>
      <anchor>aa71cfd0b5fd79ecbbd75b09904e8de1e</anchor>
      <arglist>(const int k)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const MultiVectorBase&lt; Scalar &gt; &gt;</type>
      <name>getMultiVectorBlock</name>
      <anchorfile>classThyra_1_1DefaultMultiVectorProductVector.html</anchorfile>
      <anchor>ab6c2de16b98466201b710734a1677e04</anchor>
      <arglist>(const int k) const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const VectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>space</name>
      <anchorfile>classThyra_1_1DefaultMultiVectorProductVector.html</anchorfile>
      <anchor>a7eed5e91c8e2cc695d14de1b127c2159</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>applyOpImpl</name>
      <anchorfile>classThyra_1_1DefaultMultiVectorProductVector.html</anchorfile>
      <anchor>a1882ca255f37d32bf2747f832db39ca7</anchor>
      <arglist>(const RTOpPack::RTOpT&lt; Scalar &gt; &amp;op, const ArrayView&lt; const Ptr&lt; const VectorBase&lt; Scalar &gt; &gt; &gt; &amp;vecs, const ArrayView&lt; const Ptr&lt; VectorBase&lt; Scalar &gt; &gt; &gt; &amp;targ_vecs, const Ptr&lt; RTOpPack::ReductTarget &gt; &amp;reduct_obj, const Ordinal global_offset) const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>acquireDetachedVectorViewImpl</name>
      <anchorfile>classThyra_1_1DefaultMultiVectorProductVector.html</anchorfile>
      <anchor>a33850d24c86ebdd6e16711219bf0fc56</anchor>
      <arglist>(const Range1D &amp;rng, RTOpPack::ConstSubVectorView&lt; Scalar &gt; *sub_vec) const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>releaseDetachedVectorViewImpl</name>
      <anchorfile>classThyra_1_1DefaultMultiVectorProductVector.html</anchorfile>
      <anchor>a73ba2b6abbaa17035305435063df7c1c</anchor>
      <arglist>(RTOpPack::ConstSubVectorView&lt; Scalar &gt; *sub_vec) const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>acquireNonconstDetachedVectorViewImpl</name>
      <anchorfile>classThyra_1_1DefaultMultiVectorProductVector.html</anchorfile>
      <anchor>aed231af8acd2fcc3cd092c6009c56ae2</anchor>
      <arglist>(const Range1D &amp;rng, RTOpPack::SubVectorView&lt; Scalar &gt; *sub_vec)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>commitNonconstDetachedVectorViewImpl</name>
      <anchorfile>classThyra_1_1DefaultMultiVectorProductVector.html</anchorfile>
      <anchor>a4f7fb15f2d96766cf5bb3d5191e091be</anchor>
      <arglist>(RTOpPack::SubVectorView&lt; Scalar &gt; *sub_vec)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>setSubVectorImpl</name>
      <anchorfile>classThyra_1_1DefaultMultiVectorProductVector.html</anchorfile>
      <anchor>acc045d78240725cd8600343302cb8dd3</anchor>
      <arglist>(const RTOpPack::SparseSubVectorT&lt; Scalar &gt; &amp;sub_vec)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>assignImpl</name>
      <anchorfile>classThyra_1_1DefaultMultiVectorProductVector.html</anchorfile>
      <anchor>a232ef77e470fa549e37360a81749bda1</anchor>
      <arglist>(Scalar alpha)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::DefaultMultiVectorProductVectorSpace</name>
    <filename>classThyra_1_1DefaultMultiVectorProductVectorSpace.html</filename>
    <templarg>Scalar</templarg>
    <base virtualness="virtual">Thyra::ProductVectorSpaceBase</base>
    <base protection="protected" virtualness="virtual">Thyra::VectorSpaceDefaultBase</base>
    <member kind="function">
      <type>RCP&lt; DefaultMultiVectorProductVectorSpace&lt; Scalar &gt; &gt;</type>
      <name>multiVectorProductVectorSpace</name>
      <anchorfile>classThyra_1_1DefaultMultiVectorProductVectorSpace.html</anchorfile>
      <anchor>aef7422cbda43dfa536495a5cd35903c0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; DefaultMultiVectorProductVectorSpace&lt; Scalar &gt; &gt;</type>
      <name>multiVectorProductVectorSpace</name>
      <anchorfile>classThyra_1_1DefaultMultiVectorProductVectorSpace.html</anchorfile>
      <anchor>af67095f7d4be8113a12d35cb31d732b8</anchor>
      <arglist>(const RCP&lt; const VectorSpaceBase&lt; Scalar &gt; &gt; &amp;space, const int numColumns)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>DefaultMultiVectorProductVectorSpace</name>
      <anchorfile>classThyra_1_1DefaultMultiVectorProductVectorSpace.html</anchorfile>
      <anchor>a37d09e1f2fdb0fef20efdb6ad59e2b08</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initialize</name>
      <anchorfile>classThyra_1_1DefaultMultiVectorProductVectorSpace.html</anchorfile>
      <anchor>a759fb3f3474083cab737ca6c359130be</anchor>
      <arglist>(const RCP&lt; const VectorSpaceBase&lt; Scalar &gt; &gt; &amp;space, const int numColumns)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const DefaultProductVectorSpace&lt; Scalar &gt; &gt;</type>
      <name>getDefaultProductVectorSpace</name>
      <anchorfile>classThyra_1_1DefaultMultiVectorProductVectorSpace.html</anchorfile>
      <anchor>a695fc46aa5686a34560cec759d3566c0</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>uninitialize</name>
      <anchorfile>classThyra_1_1DefaultMultiVectorProductVectorSpace.html</anchorfile>
      <anchor>aaa03b05d53f12245fc759a0cf6cb66a6</anchor>
      <arglist>(RCP&lt; const VectorSpaceBase&lt; Scalar &gt; &gt; *space=0, int *numColumns=0)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>numBlocks</name>
      <anchorfile>classThyra_1_1DefaultMultiVectorProductVectorSpace.html</anchorfile>
      <anchor>acd96b9fa576ea5ccbd43580a3c995010</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const VectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>getBlock</name>
      <anchorfile>classThyra_1_1DefaultMultiVectorProductVectorSpace.html</anchorfile>
      <anchor>a54204599021d5883827fac9d8542e32f</anchor>
      <arglist>(const int k) const </arglist>
    </member>
    <member kind="function">
      <type>Ordinal</type>
      <name>dim</name>
      <anchorfile>classThyra_1_1DefaultMultiVectorProductVectorSpace.html</anchorfile>
      <anchor>af35f98c8b65feeeb2bba1a495a320811</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isCompatible</name>
      <anchorfile>classThyra_1_1DefaultMultiVectorProductVectorSpace.html</anchorfile>
      <anchor>a0967f0915b10e07b88ca34449798f7c9</anchor>
      <arglist>(const VectorSpaceBase&lt; Scalar &gt; &amp;vecSpc) const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; VectorBase&lt; Scalar &gt; &gt;</type>
      <name>createMember</name>
      <anchorfile>classThyra_1_1DefaultMultiVectorProductVectorSpace.html</anchorfile>
      <anchor>af9446cb35242c40e89776f03c115bd41</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Scalar</type>
      <name>scalarProd</name>
      <anchorfile>classThyra_1_1DefaultMultiVectorProductVectorSpace.html</anchorfile>
      <anchor>ad2f9645e1f5f7afd5f314839299adcad</anchor>
      <arglist>(const VectorBase&lt; Scalar &gt; &amp;x, const VectorBase&lt; Scalar &gt; &amp;y) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>scalarProdsImpl</name>
      <anchorfile>classThyra_1_1DefaultMultiVectorProductVectorSpace.html</anchorfile>
      <anchor>abeb3611d981d86d98ca81bee797e210f</anchor>
      <arglist>(const MultiVectorBase&lt; Scalar &gt; &amp;X, const MultiVectorBase&lt; Scalar &gt; &amp;Y, const ArrayView&lt; Scalar &gt; &amp;scalarProds) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>hasInCoreView</name>
      <anchorfile>classThyra_1_1DefaultMultiVectorProductVectorSpace.html</anchorfile>
      <anchor>a1fac90fe746b1b9637d7099d0ae6c4e2</anchor>
      <arglist>(const Range1D &amp;rng, const EViewType viewType, const EStrideType strideType) const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const VectorSpaceFactoryBase&lt; Scalar &gt; &gt;</type>
      <name>smallVecSpcFcty</name>
      <anchorfile>classThyra_1_1DefaultMultiVectorProductVectorSpace.html</anchorfile>
      <anchor>aee28c822d674f26103c1c5831999c9d3</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; MultiVectorBase&lt; Scalar &gt; &gt;</type>
      <name>createMembers</name>
      <anchorfile>classThyra_1_1DefaultMultiVectorProductVectorSpace.html</anchorfile>
      <anchor>aaab618097f311603debc9d0be6010a7f</anchor>
      <arglist>(int numMembers) const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const VectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>clone</name>
      <anchorfile>classThyra_1_1DefaultMultiVectorProductVectorSpace.html</anchorfile>
      <anchor>a2414f0229ef4b2699801167896b10600</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>description</name>
      <anchorfile>classThyra_1_1DefaultMultiVectorProductVectorSpace.html</anchorfile>
      <anchor>ad91316dfb62b643bf60bf1d704650767</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>describe</name>
      <anchorfile>classThyra_1_1DefaultMultiVectorProductVectorSpace.html</anchorfile>
      <anchor>a1ba9893c1dc123d74acdd36e288dd4ae</anchor>
      <arglist>(Teuchos::FancyOStream &amp;out, const Teuchos::EVerbosityLevel verbLevel) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::DefaultNominalBoundsOverrideModelEvaluator</name>
    <filename>classThyra_1_1DefaultNominalBoundsOverrideModelEvaluator.html</filename>
    <templarg></templarg>
    <base virtualness="virtual">Thyra::ModelEvaluatorDelegatorBase</base>
    <member kind="typedef">
      <type>Teuchos::ScalarTraits&lt; Scalar &gt;::magnitudeType</type>
      <name>ScalarMag</name>
      <anchorfile>classThyra_1_1DefaultNominalBoundsOverrideModelEvaluator.html</anchorfile>
      <anchor>af9860e2e9c87983c361f6d48e3796578</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>DefaultNominalBoundsOverrideModelEvaluator</name>
      <anchorfile>classThyra_1_1DefaultNominalBoundsOverrideModelEvaluator.html</anchorfile>
      <anchor>a9236ec9cc6e70fd2e5b8d4f341b19f04</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>DefaultNominalBoundsOverrideModelEvaluator</name>
      <anchorfile>classThyra_1_1DefaultNominalBoundsOverrideModelEvaluator.html</anchorfile>
      <anchor>ad2aa0dfa144c12c20a90c2913919e708</anchor>
      <arglist>(const RCP&lt; ModelEvaluator&lt; Scalar &gt; &gt; &amp;thyraModel, const RCP&lt; const ModelEvaluatorBase::InArgs&lt; Scalar &gt; &gt; &amp;nominalValues, const RCP&lt; const ModelEvaluatorBase::InArgs&lt; Scalar &gt; &gt; &amp;lowerBounds=Teuchos::null, const RCP&lt; const ModelEvaluatorBase::InArgs&lt; Scalar &gt; &gt; &amp;upperBounds=Teuchos::null)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initialize</name>
      <anchorfile>classThyra_1_1DefaultNominalBoundsOverrideModelEvaluator.html</anchorfile>
      <anchor>a4be6afeb965ffecce70e36a28875064b</anchor>
      <arglist>(const RCP&lt; ModelEvaluator&lt; Scalar &gt; &gt; &amp;thyraModel, const RCP&lt; const ModelEvaluatorBase::InArgs&lt; Scalar &gt; &gt; &amp;nominalValues, const RCP&lt; const ModelEvaluatorBase::InArgs&lt; Scalar &gt; &gt; &amp;lowerBounds=Teuchos::null, const RCP&lt; const ModelEvaluatorBase::InArgs&lt; Scalar &gt; &gt; &amp;upperBounds=Teuchos::null)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setNominalValues</name>
      <anchorfile>classThyra_1_1DefaultNominalBoundsOverrideModelEvaluator.html</anchorfile>
      <anchor>abbbe4925efce8fc0c0a5349b33b66e68</anchor>
      <arglist>(const RCP&lt; const ModelEvaluatorBase::InArgs&lt; Scalar &gt; &gt; &amp;nominalValues)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setLowerBounds</name>
      <anchorfile>classThyra_1_1DefaultNominalBoundsOverrideModelEvaluator.html</anchorfile>
      <anchor>aa61ba76b121ad07f56c32804d0340aef</anchor>
      <arglist>(const RCP&lt; const ModelEvaluatorBase::InArgs&lt; Scalar &gt; &gt; &amp;lowerBounds)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setUpperBounds</name>
      <anchorfile>classThyra_1_1DefaultNominalBoundsOverrideModelEvaluator.html</anchorfile>
      <anchor>aaa5f3e02475750d4dcba710a788b14d8</anchor>
      <arglist>(const RCP&lt; const ModelEvaluatorBase::InArgs&lt; Scalar &gt; &gt; &amp;upperBounds)</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>description</name>
      <anchorfile>classThyra_1_1DefaultNominalBoundsOverrideModelEvaluator.html</anchorfile>
      <anchor>a3b4c7c8d7596372edba80174ef060a4f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>ModelEvaluatorBase::InArgs&lt; Scalar &gt;</type>
      <name>getNominalValues</name>
      <anchorfile>classThyra_1_1DefaultNominalBoundsOverrideModelEvaluator.html</anchorfile>
      <anchor>a2c90d6155420764613fd94b15f0f8a6b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>ModelEvaluatorBase::InArgs&lt; Scalar &gt;</type>
      <name>getLowerBounds</name>
      <anchorfile>classThyra_1_1DefaultNominalBoundsOverrideModelEvaluator.html</anchorfile>
      <anchor>ab66ebf6841c5ef9836793a4c514389f8</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>ModelEvaluatorBase::InArgs&lt; Scalar &gt;</type>
      <name>getUpperBounds</name>
      <anchorfile>classThyra_1_1DefaultNominalBoundsOverrideModelEvaluator.html</anchorfile>
      <anchor>a7959c80e8447c6ef693faf76865d81a0</anchor>
      <arglist>() const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::DefaultNonlinearSolverBuilder</name>
    <filename>classThyra_1_1DefaultNonlinearSolverBuilder.html</filename>
    <member kind="function">
      <type></type>
      <name>DefaultNonlinearSolverBuilder</name>
      <anchorfile>classThyra_1_1DefaultNonlinearSolverBuilder.html</anchorfile>
      <anchor>a4021f9393519e5200eeaf2229551a399</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~DefaultNonlinearSolverBuilder</name>
      <anchorfile>classThyra_1_1DefaultNonlinearSolverBuilder.html</anchorfile>
      <anchor>a7178ffe3f96ac8a9dae1f43328cd7d53</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setNonlinearSolverFactory</name>
      <anchorfile>classThyra_1_1DefaultNonlinearSolverBuilder.html</anchorfile>
      <anchor>a3a6d0668beeb27859f925dc0bfa3f19c</anchor>
      <arglist>(const RCP&lt; const AbstractFactory&lt; Thyra::NonlinearSolverBase&lt; double &gt; &gt; &gt; &amp;nonlinearSolverFactory, const std::string &amp;nonlinearSolverTypeName)</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>getNonlinearSolverName</name>
      <anchorfile>classThyra_1_1DefaultNonlinearSolverBuilder.html</anchorfile>
      <anchor>ac5f35ba1512ccbe41fb37b119770cf5a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setParameterList</name>
      <anchorfile>classThyra_1_1DefaultNonlinearSolverBuilder.html</anchorfile>
      <anchor>acbcc0cd4a2f02c94a5e0e0657283c4da</anchor>
      <arglist>(RCP&lt; ParameterList &gt; const &amp;paramList)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; ParameterList &gt;</type>
      <name>getNonconstParameterList</name>
      <anchorfile>classThyra_1_1DefaultNonlinearSolverBuilder.html</anchorfile>
      <anchor>a501206c0bde22e2a3414ff1326cdcb5a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; ParameterList &gt;</type>
      <name>unsetParameterList</name>
      <anchorfile>classThyra_1_1DefaultNonlinearSolverBuilder.html</anchorfile>
      <anchor>a628e17cda99c3fb3c42e3296041bcee4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const ParameterList &gt;</type>
      <name>getParameterList</name>
      <anchorfile>classThyra_1_1DefaultNonlinearSolverBuilder.html</anchorfile>
      <anchor>a6e5160f4fd9871f9eaa09f8fc31b666b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const ParameterList &gt;</type>
      <name>getValidParameters</name>
      <anchorfile>classThyra_1_1DefaultNonlinearSolverBuilder.html</anchorfile>
      <anchor>adea6521587cb7ec33195475bbb9ce8b5</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual Teuchos::RCP&lt; NonlinearSolverBase&lt; Scalar &gt; &gt;</type>
      <name>createNonlinearSolver</name>
      <anchorfile>classThyra_1_1DefaultNonlinearSolverBuilder.html</anchorfile>
      <anchor>ad3f043d46c8793d61a469f40aa01f373</anchor>
      <arglist>(const std::string &amp;nonlinearSolverTypeName) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::DefaultPreconditioner</name>
    <filename>classThyra_1_1DefaultPreconditioner.html</filename>
    <templarg></templarg>
    <base virtualness="virtual">Thyra::PreconditionerBase</base>
    <member kind="function">
      <type>Teuchos::RCP&lt; const DefaultPreconditioner&lt; Scalar &gt; &gt;</type>
      <name>unspecifiedPrec</name>
      <anchorfile>classThyra_1_1DefaultPreconditioner.html</anchorfile>
      <anchor>a5c4354d9fea07a8a077036402d4b1a9c</anchor>
      <arglist>(const Teuchos::RCP&lt; const LinearOpBase&lt; Scalar &gt; &gt; &amp;unspecifiedPrecOp)</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; DefaultPreconditioner&lt; Scalar &gt; &gt;</type>
      <name>nonconstUnspecifiedPrec</name>
      <anchorfile>classThyra_1_1DefaultPreconditioner.html</anchorfile>
      <anchor>a125c66389be7d2612c2b2c7006546845</anchor>
      <arglist>(const Teuchos::RCP&lt; LinearOpBase&lt; Scalar &gt; &gt; &amp;unspecifiedPrecOp)</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const DefaultPreconditioner&lt; Scalar &gt; &gt;</type>
      <name>leftPrec</name>
      <anchorfile>classThyra_1_1DefaultPreconditioner.html</anchorfile>
      <anchor>a23f7d6fc6dbd93574e1066a3bfdaa004</anchor>
      <arglist>(const Teuchos::RCP&lt; const LinearOpBase&lt; Scalar &gt; &gt; &amp;leftPrecOp)</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const DefaultPreconditioner&lt; Scalar &gt; &gt;</type>
      <name>rightPrec</name>
      <anchorfile>classThyra_1_1DefaultPreconditioner.html</anchorfile>
      <anchor>a007a1fd62554976d2ef4cfa0e3c16a74</anchor>
      <arglist>(const Teuchos::RCP&lt; const LinearOpBase&lt; Scalar &gt; &gt; &amp;rightPrecOp)</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const DefaultPreconditioner&lt; Scalar &gt; &gt;</type>
      <name>splitPrec</name>
      <anchorfile>classThyra_1_1DefaultPreconditioner.html</anchorfile>
      <anchor>a6a28a66da207c9f678d6f15b12a8b788</anchor>
      <arglist>(const Teuchos::RCP&lt; const LinearOpBase&lt; Scalar &gt; &gt; &amp;leftPrecOp, const Teuchos::RCP&lt; const LinearOpBase&lt; Scalar &gt; &gt; &amp;rightPrecOp)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>DefaultPreconditioner</name>
      <anchorfile>classThyra_1_1DefaultPreconditioner.html</anchorfile>
      <anchor>a7e23ac1b9c90b1227163f7ccf208bb15</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>DefaultPreconditioner</name>
      <anchorfile>classThyra_1_1DefaultPreconditioner.html</anchorfile>
      <anchor>a4c32969f5617c3a18ef9ee78c362581a</anchor>
      <arglist>(const Teuchos::RCP&lt; LinearOpBase&lt; Scalar &gt; &gt; &amp;leftPrecOp, const Teuchos::RCP&lt; LinearOpBase&lt; Scalar &gt; &gt; &amp;rightPrecOp)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>DefaultPreconditioner</name>
      <anchorfile>classThyra_1_1DefaultPreconditioner.html</anchorfile>
      <anchor>ab7f24e1e25682aae80bce021358be918</anchor>
      <arglist>(const Teuchos::RCP&lt; const LinearOpBase&lt; Scalar &gt; &gt; &amp;leftPrecOp, const Teuchos::RCP&lt; const LinearOpBase&lt; Scalar &gt; &gt; &amp;rightPrecOp)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>DefaultPreconditioner</name>
      <anchorfile>classThyra_1_1DefaultPreconditioner.html</anchorfile>
      <anchor>a92a7725faab4087d11afbbd983ebf54a</anchor>
      <arglist>(const Teuchos::RCP&lt; LinearOpBase&lt; Scalar &gt; &gt; &amp;unspecifiedPrecOp)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>DefaultPreconditioner</name>
      <anchorfile>classThyra_1_1DefaultPreconditioner.html</anchorfile>
      <anchor>a6d1f1d0321750364a997bab2074f8baf</anchor>
      <arglist>(const Teuchos::RCP&lt; const LinearOpBase&lt; Scalar &gt; &gt; &amp;unspecifiedPrecOp)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initializeLeft</name>
      <anchorfile>classThyra_1_1DefaultPreconditioner.html</anchorfile>
      <anchor>a646528b6f7a43611a9775c0b485dc523</anchor>
      <arglist>(const Teuchos::RCP&lt; LinearOpBase&lt; Scalar &gt; &gt; &amp;leftPrecOp)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initializeLeft</name>
      <anchorfile>classThyra_1_1DefaultPreconditioner.html</anchorfile>
      <anchor>a7a383274cc18ce6faef9d2223eac8410</anchor>
      <arglist>(const Teuchos::RCP&lt; const LinearOpBase&lt; Scalar &gt; &gt; &amp;leftPrecOp)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initializeRight</name>
      <anchorfile>classThyra_1_1DefaultPreconditioner.html</anchorfile>
      <anchor>ab1f1d0f3bf7287c46d87bed5423cbe05</anchor>
      <arglist>(const Teuchos::RCP&lt; LinearOpBase&lt; Scalar &gt; &gt; &amp;rightPrecOp)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initializeRight</name>
      <anchorfile>classThyra_1_1DefaultPreconditioner.html</anchorfile>
      <anchor>a8276f8fd563641994cabe22a6698ac1f</anchor>
      <arglist>(const Teuchos::RCP&lt; const LinearOpBase&lt; Scalar &gt; &gt; &amp;rightPrecOp)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initializeLeftRight</name>
      <anchorfile>classThyra_1_1DefaultPreconditioner.html</anchorfile>
      <anchor>afbe57b6e51e22ab9ca1feeac370e3513</anchor>
      <arglist>(const Teuchos::RCP&lt; LinearOpBase&lt; Scalar &gt; &gt; &amp;leftPrecOp, const Teuchos::RCP&lt; LinearOpBase&lt; Scalar &gt; &gt; &amp;rightPrecOp)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initializeLeftRight</name>
      <anchorfile>classThyra_1_1DefaultPreconditioner.html</anchorfile>
      <anchor>a4608b66be3ed43f61086b4ed426da1f8</anchor>
      <arglist>(const Teuchos::RCP&lt; const LinearOpBase&lt; Scalar &gt; &gt; &amp;leftPrecOp, const Teuchos::RCP&lt; const LinearOpBase&lt; Scalar &gt; &gt; &amp;rightPrecOp)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initializeUnspecified</name>
      <anchorfile>classThyra_1_1DefaultPreconditioner.html</anchorfile>
      <anchor>a02f9b1f545d50e970b9a8fd35a0ea97a</anchor>
      <arglist>(const Teuchos::RCP&lt; LinearOpBase&lt; Scalar &gt; &gt; &amp;unspecifiedPrecOp)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initializeUnspecified</name>
      <anchorfile>classThyra_1_1DefaultPreconditioner.html</anchorfile>
      <anchor>a3ca73842a68e3871c4320d6d6517d96d</anchor>
      <arglist>(const Teuchos::RCP&lt; const LinearOpBase&lt; Scalar &gt; &gt; &amp;unspecifiedPrecOp)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>uninitialize</name>
      <anchorfile>classThyra_1_1DefaultPreconditioner.html</anchorfile>
      <anchor>abf058725173e2ff481ba4762e5f88e02</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>description</name>
      <anchorfile>classThyra_1_1DefaultPreconditioner.html</anchorfile>
      <anchor>ad991a0f489e81f99b1bd7a5d8470bf5a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>describe</name>
      <anchorfile>classThyra_1_1DefaultPreconditioner.html</anchorfile>
      <anchor>aebb3cdd4ea747a7a4e18ad1aed529d12</anchor>
      <arglist>(Teuchos::FancyOStream &amp;out, const Teuchos::EVerbosityLevel verbLevel) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isLeftPrecOpConst</name>
      <anchorfile>classThyra_1_1DefaultPreconditioner.html</anchorfile>
      <anchor>a3cd747838b2ee5e20468281c51db3764</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; LinearOpBase&lt; Scalar &gt; &gt;</type>
      <name>getNonconstLeftPrecOp</name>
      <anchorfile>classThyra_1_1DefaultPreconditioner.html</anchorfile>
      <anchor>a338d1e3e87fc7ee844f14c135ee260b1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const LinearOpBase&lt; Scalar &gt; &gt;</type>
      <name>getLeftPrecOp</name>
      <anchorfile>classThyra_1_1DefaultPreconditioner.html</anchorfile>
      <anchor>a9de3042c00b08f22cb2b6105369d9a47</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isRightPrecOpConst</name>
      <anchorfile>classThyra_1_1DefaultPreconditioner.html</anchorfile>
      <anchor>a5ce0fff100b82c9364175a0ac76b8f48</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; LinearOpBase&lt; Scalar &gt; &gt;</type>
      <name>getNonconstRightPrecOp</name>
      <anchorfile>classThyra_1_1DefaultPreconditioner.html</anchorfile>
      <anchor>a03b731b9ca3787581c3133376c9fcfde</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const LinearOpBase&lt; Scalar &gt; &gt;</type>
      <name>getRightPrecOp</name>
      <anchorfile>classThyra_1_1DefaultPreconditioner.html</anchorfile>
      <anchor>a5b22c23b9d91c95fab3876bae0541cce</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isUnspecifiedPrecOpConst</name>
      <anchorfile>classThyra_1_1DefaultPreconditioner.html</anchorfile>
      <anchor>abd6da8a81903901f049bde27009a8a2b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; LinearOpBase&lt; Scalar &gt; &gt;</type>
      <name>getNonconstUnspecifiedPrecOp</name>
      <anchorfile>classThyra_1_1DefaultPreconditioner.html</anchorfile>
      <anchor>ab4f880ab074fd462a357d21e745d0191</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const LinearOpBase&lt; Scalar &gt; &gt;</type>
      <name>getUnspecifiedPrecOp</name>
      <anchorfile>classThyra_1_1DefaultPreconditioner.html</anchorfile>
      <anchor>a4a7d512a4bca930c52186bf8a4f3b5b1</anchor>
      <arglist>() const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::DefaultProductMultiVector</name>
    <filename>classThyra_1_1DefaultProductMultiVector.html</filename>
    <templarg></templarg>
    <base virtualness="virtual">Thyra::ProductMultiVectorBase</base>
    <base protection="protected" virtualness="virtual">Thyra::MultiVectorDefaultBase</base>
    <member kind="function">
      <type>RCP&lt; DefaultProductMultiVector&lt; Scalar &gt; &gt;</type>
      <name>defaultProductMultiVector</name>
      <anchorfile>classThyra_1_1DefaultProductMultiVector.html</anchorfile>
      <anchor>aa1a459758f699bc95757b04bbd9d2adc</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; DefaultProductMultiVector&lt; Scalar &gt; &gt;</type>
      <name>defaultProductMultiVector</name>
      <anchorfile>classThyra_1_1DefaultProductMultiVector.html</anchorfile>
      <anchor>ac572b5977a223f0dc181f32ecf42c51d</anchor>
      <arglist>(const RCP&lt; const DefaultProductVectorSpace&lt; Scalar &gt; &gt; &amp;productSpace, const int numMembers)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; DefaultProductMultiVector&lt; Scalar &gt; &gt;</type>
      <name>defaultProductMultiVector</name>
      <anchorfile>classThyra_1_1DefaultProductMultiVector.html</anchorfile>
      <anchor>a78b615308d92dbff271d5d670350f9ad</anchor>
      <arglist>(const RCP&lt; const DefaultProductVectorSpace&lt; Scalar &gt; &gt; &amp;productSpace, const ArrayView&lt; const RCP&lt; MultiVectorBase&lt; Scalar &gt; &gt; &gt; &amp;multiVecs)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; DefaultProductMultiVector&lt; Scalar &gt; &gt;</type>
      <name>defaultProductMultiVector</name>
      <anchorfile>classThyra_1_1DefaultProductMultiVector.html</anchorfile>
      <anchor>a28712e5f9fe9e52278938c1094dff7c7</anchor>
      <arglist>(const RCP&lt; const DefaultProductVectorSpace&lt; Scalar &gt; &gt; &amp;productSpace, const ArrayView&lt; const RCP&lt; const MultiVectorBase&lt; Scalar &gt; &gt; &gt; &amp;multiVecs)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const ProductMultiVectorBase&lt; Scalar &gt; &gt;</type>
      <name>castOrCreateSingleBlockProductMultiVector</name>
      <anchorfile>classThyra_1_1DefaultProductMultiVector.html</anchorfile>
      <anchor>a41aa32ffd69b7462947f97fe9394584a</anchor>
      <arglist>(const RCP&lt; const DefaultProductVectorSpace&lt; Scalar &gt; &gt; &amp;productSpace, const RCP&lt; const MultiVectorBase&lt; Scalar &gt; &gt; &amp;mv)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; ProductMultiVectorBase&lt; Scalar &gt; &gt;</type>
      <name>nonconstCastOrCreateSingleBlockProductMultiVector</name>
      <anchorfile>classThyra_1_1DefaultProductMultiVector.html</anchorfile>
      <anchor>a5740ce2ee0db7d63db5f7673753153bc</anchor>
      <arglist>(const RCP&lt; const DefaultProductVectorSpace&lt; Scalar &gt; &gt; &amp;productSpace, const RCP&lt; MultiVectorBase&lt; Scalar &gt; &gt; &amp;mv)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>DefaultProductMultiVector</name>
      <anchorfile>classThyra_1_1DefaultProductMultiVector.html</anchorfile>
      <anchor>a09ecb44e246b0928d9c20e494277a809</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initialize</name>
      <anchorfile>classThyra_1_1DefaultProductMultiVector.html</anchorfile>
      <anchor>a03fda576e006e75327ef208e952cb47e</anchor>
      <arglist>(const RCP&lt; const DefaultProductVectorSpace&lt; Scalar &gt; &gt; &amp;productSpace, const int numMembers)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initialize</name>
      <anchorfile>classThyra_1_1DefaultProductMultiVector.html</anchorfile>
      <anchor>a86d90650c1cd91d0fec56975e3664eef</anchor>
      <arglist>(const RCP&lt; const DefaultProductVectorSpace&lt; Scalar &gt; &gt; &amp;productSpace, const ArrayView&lt; const RCP&lt; MultiVectorBase&lt; Scalar &gt; &gt; &gt; &amp;multiVecs)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initialize</name>
      <anchorfile>classThyra_1_1DefaultProductMultiVector.html</anchorfile>
      <anchor>aaa06301949cdf84127a2dd796142a218</anchor>
      <arglist>(const RCP&lt; const DefaultProductVectorSpace&lt; Scalar &gt; &gt; &amp;productSpace, const ArrayView&lt; const RCP&lt; const MultiVectorBase&lt; Scalar &gt; &gt; &gt; &amp;multiVecs)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>uninitialize</name>
      <anchorfile>classThyra_1_1DefaultProductMultiVector.html</anchorfile>
      <anchor>a140caefb5312210390b2f639e8bff28c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>description</name>
      <anchorfile>classThyra_1_1DefaultProductMultiVector.html</anchorfile>
      <anchor>ab569b75cac5ac363069a165bbbf022e8</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>describe</name>
      <anchorfile>classThyra_1_1DefaultProductMultiVector.html</anchorfile>
      <anchor>afb27753756ed288d17d55f9bffeac074</anchor>
      <arglist>(Teuchos::FancyOStream &amp;out, const Teuchos::EVerbosityLevel verbLevel) const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const ProductVectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>productSpace</name>
      <anchorfile>classThyra_1_1DefaultProductMultiVector.html</anchorfile>
      <anchor>a1ad7bd7244c86c6da607736963151a18</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>blockIsConst</name>
      <anchorfile>classThyra_1_1DefaultProductMultiVector.html</anchorfile>
      <anchor>a482b646147fca8214a9239730969775e</anchor>
      <arglist>(const int k) const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; MultiVectorBase&lt; Scalar &gt; &gt;</type>
      <name>getNonconstMultiVectorBlock</name>
      <anchorfile>classThyra_1_1DefaultProductMultiVector.html</anchorfile>
      <anchor>a677a2e3e9944f3434f41289231290267</anchor>
      <arglist>(const int k)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const MultiVectorBase&lt; Scalar &gt; &gt;</type>
      <name>getMultiVectorBlock</name>
      <anchorfile>classThyra_1_1DefaultProductMultiVector.html</anchorfile>
      <anchor>a1aaa9768395abf9babcce7da4820bea9</anchor>
      <arglist>(const int k) const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; MultiVectorBase&lt; Scalar &gt; &gt;</type>
      <name>clone_mv</name>
      <anchorfile>classThyra_1_1DefaultProductMultiVector.html</anchorfile>
      <anchor>a06e7943da1d8ef59d10874d4f87e6685</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const VectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>range</name>
      <anchorfile>classThyra_1_1DefaultProductMultiVector.html</anchorfile>
      <anchor>af6fc1da884cd7ead471696db4f6790b8</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const VectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>domain</name>
      <anchorfile>classThyra_1_1DefaultProductMultiVector.html</anchorfile>
      <anchor>a3499d5dc996fcf4dcb2be5d1f78c6477</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>assignImpl</name>
      <anchorfile>classThyra_1_1DefaultProductMultiVector.html</anchorfile>
      <anchor>a6a6aa37f09f03815a69c5b7b9d1c7056</anchor>
      <arglist>(Scalar alpha)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>RCP&lt; const VectorBase&lt; Scalar &gt; &gt;</type>
      <name>colImpl</name>
      <anchorfile>classThyra_1_1DefaultProductMultiVector.html</anchorfile>
      <anchor>a33ad304e0672a6291bc8325f507e8fb4</anchor>
      <arglist>(Ordinal j) const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>RCP&lt; VectorBase&lt; Scalar &gt; &gt;</type>
      <name>nonconstColImpl</name>
      <anchorfile>classThyra_1_1DefaultProductMultiVector.html</anchorfile>
      <anchor>ae1961cfe77f55dd1cd2cdf8a62530653</anchor>
      <arglist>(Ordinal j)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>RCP&lt; const MultiVectorBase&lt; Scalar &gt; &gt;</type>
      <name>contigSubViewImpl</name>
      <anchorfile>classThyra_1_1DefaultProductMultiVector.html</anchorfile>
      <anchor>ace04389d772b5c72aa9b44533d3da9ab</anchor>
      <arglist>(const Range1D &amp;colRng) const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>RCP&lt; MultiVectorBase&lt; Scalar &gt; &gt;</type>
      <name>nonconstContigSubViewImpl</name>
      <anchorfile>classThyra_1_1DefaultProductMultiVector.html</anchorfile>
      <anchor>a184f9bd71f8b7e571c353e2f9f37a2cf</anchor>
      <arglist>(const Range1D &amp;colRng)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>RCP&lt; const MultiVectorBase&lt; Scalar &gt; &gt;</type>
      <name>nonContigSubViewImpl</name>
      <anchorfile>classThyra_1_1DefaultProductMultiVector.html</anchorfile>
      <anchor>a121fbb61ea5d6baa88f874b9ea7e26a9</anchor>
      <arglist>(const ArrayView&lt; const int &gt; &amp;cols) const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>RCP&lt; MultiVectorBase&lt; Scalar &gt; &gt;</type>
      <name>nonconstNonContigSubViewImpl</name>
      <anchorfile>classThyra_1_1DefaultProductMultiVector.html</anchorfile>
      <anchor>a102d47fe2cba77a91925360abd80ef26</anchor>
      <arglist>(const ArrayView&lt; const int &gt; &amp;cols)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>mvMultiReductApplyOpImpl</name>
      <anchorfile>classThyra_1_1DefaultProductMultiVector.html</anchorfile>
      <anchor>a11c559392e74880da845b6314604819a</anchor>
      <arglist>(const RTOpPack::RTOpT&lt; Scalar &gt; &amp;primary_op, const ArrayView&lt; const Ptr&lt; const MultiVectorBase&lt; Scalar &gt; &gt; &gt; &amp;multi_vecs, const ArrayView&lt; const Ptr&lt; MultiVectorBase&lt; Scalar &gt; &gt; &gt; &amp;targ_multi_vecs, const ArrayView&lt; const Ptr&lt; RTOpPack::ReductTarget &gt; &gt; &amp;reduct_objs, const Ordinal primary_global_offset) const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>acquireDetachedMultiVectorViewImpl</name>
      <anchorfile>classThyra_1_1DefaultProductMultiVector.html</anchorfile>
      <anchor>a1bf2b1ac14df1f69329b247054bb5068</anchor>
      <arglist>(const Range1D &amp;rowRng, const Range1D &amp;colRng, RTOpPack::ConstSubMultiVectorView&lt; Scalar &gt; *sub_mv) const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>releaseDetachedMultiVectorViewImpl</name>
      <anchorfile>classThyra_1_1DefaultProductMultiVector.html</anchorfile>
      <anchor>acb00ade5c4dfefeaa495ec98ca000b59</anchor>
      <arglist>(RTOpPack::ConstSubMultiVectorView&lt; Scalar &gt; *sub_mv) const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>acquireNonconstDetachedMultiVectorViewImpl</name>
      <anchorfile>classThyra_1_1DefaultProductMultiVector.html</anchorfile>
      <anchor>ac9499437f179eaa804fad5c284a99dd8</anchor>
      <arglist>(const Range1D &amp;rowRng, const Range1D &amp;colRng, RTOpPack::SubMultiVectorView&lt; Scalar &gt; *sub_mv)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>commitNonconstDetachedMultiVectorViewImpl</name>
      <anchorfile>classThyra_1_1DefaultProductMultiVector.html</anchorfile>
      <anchor>a470f9ef97bf4dc5a88460d5db50ce779</anchor>
      <arglist>(RTOpPack::SubMultiVectorView&lt; Scalar &gt; *sub_mv)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>bool</type>
      <name>opSupportedImpl</name>
      <anchorfile>classThyra_1_1DefaultProductMultiVector.html</anchorfile>
      <anchor>a1af526667affdc06ae48f040d542a997</anchor>
      <arglist>(EOpTransp M_trans) const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>applyImpl</name>
      <anchorfile>classThyra_1_1DefaultProductMultiVector.html</anchorfile>
      <anchor>a50af076179874a136f7a6af076369a6a</anchor>
      <arglist>(const EOpTransp M_trans, const MultiVectorBase&lt; Scalar &gt; &amp;X, const Ptr&lt; MultiVectorBase&lt; Scalar &gt; &gt; &amp;Y, const Scalar alpha, const Scalar beta) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::DefaultProductVector</name>
    <filename>classThyra_1_1DefaultProductVector.html</filename>
    <templarg></templarg>
    <base virtualness="virtual">Thyra::ProductVectorBase</base>
    <base protection="protected" virtualness="virtual">Thyra::VectorDefaultBase</base>
    <member kind="function">
      <type>RCP&lt; DefaultProductVector&lt; Scalar &gt; &gt;</type>
      <name>defaultProductVector</name>
      <anchorfile>classThyra_1_1DefaultProductVector.html</anchorfile>
      <anchor>a9f97075f127ea2d85053cdc36ea9372e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; DefaultProductVector&lt; Scalar &gt; &gt;</type>
      <name>defaultProductVector</name>
      <anchorfile>classThyra_1_1DefaultProductVector.html</anchorfile>
      <anchor>a68a20c768247dd748d6c44f9ebf1b386</anchor>
      <arglist>(const RCP&lt; const DefaultProductVectorSpace&lt; Scalar &gt; &gt; &amp;productSpace)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; DefaultProductVector&lt; Scalar &gt; &gt;</type>
      <name>defaultProductVector</name>
      <anchorfile>classThyra_1_1DefaultProductVector.html</anchorfile>
      <anchor>a8b1298337d773da15861c611625db792</anchor>
      <arglist>(const RCP&lt; const DefaultProductVectorSpace&lt; Scalar &gt; &gt; &amp;productSpace, const ArrayView&lt; const RCP&lt; VectorBase&lt; Scalar &gt; &gt; &gt; &amp;vecs)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; DefaultProductVector&lt; Scalar &gt; &gt;</type>
      <name>defaultProductVector</name>
      <anchorfile>classThyra_1_1DefaultProductVector.html</anchorfile>
      <anchor>ab8bb26f7bf232d32e36b911bb323125e</anchor>
      <arglist>(const RCP&lt; const DefaultProductVectorSpace&lt; Scalar &gt; &gt; &amp;productSpace, const ArrayView&lt; const RCP&lt; const VectorBase&lt; Scalar &gt; &gt; &gt; &amp;vecs)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; ProductVectorBase&lt; Scalar &gt; &gt;</type>
      <name>castOrCreateNonconstProductVectorBase</name>
      <anchorfile>classThyra_1_1DefaultProductVector.html</anchorfile>
      <anchor>afc124fd0cac4369f2c2d4a1151eca6b5</anchor>
      <arglist>(const RCP&lt; VectorBase&lt; Scalar &gt; &gt; v)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const ProductVectorBase&lt; Scalar &gt; &gt;</type>
      <name>castOrCreateProductVectorBase</name>
      <anchorfile>classThyra_1_1DefaultProductVector.html</anchorfile>
      <anchor>a1c999eb3909da0a86836ff1d4448fd0f</anchor>
      <arglist>(const RCP&lt; const VectorBase&lt; Scalar &gt; &gt; v)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>DefaultProductVector</name>
      <anchorfile>classThyra_1_1DefaultProductVector.html</anchorfile>
      <anchor>a239a0e8072e4c251fea8e7fa73cb67b0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>DefaultProductVector</name>
      <anchorfile>classThyra_1_1DefaultProductVector.html</anchorfile>
      <anchor>a776fde53dbbb8b316aad261e2179ad97</anchor>
      <arglist>(const RCP&lt; const DefaultProductVectorSpace&lt; Scalar &gt; &gt; &amp;productSpace)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initialize</name>
      <anchorfile>classThyra_1_1DefaultProductVector.html</anchorfile>
      <anchor>a1e6dc0577ca5e0dbf8e6d088d5421d92</anchor>
      <arglist>(const RCP&lt; const DefaultProductVectorSpace&lt; Scalar &gt; &gt; &amp;productSpace)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initialize</name>
      <anchorfile>classThyra_1_1DefaultProductVector.html</anchorfile>
      <anchor>adf36b47f37b14fff0e9a7aa7059f3764</anchor>
      <arglist>(const RCP&lt; const DefaultProductVectorSpace&lt; Scalar &gt; &gt; &amp;productSpace, const ArrayView&lt; const RCP&lt; VectorBase&lt; Scalar &gt; &gt; &gt; &amp;vecs)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initialize</name>
      <anchorfile>classThyra_1_1DefaultProductVector.html</anchorfile>
      <anchor>a76a4c736329f5abe912315eaae2dd5b3</anchor>
      <arglist>(const RCP&lt; const DefaultProductVectorSpace&lt; Scalar &gt; &gt; &amp;productSpace, const ArrayView&lt; const RCP&lt; const VectorBase&lt; Scalar &gt; &gt; &gt; &amp;vecs)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>uninitialize</name>
      <anchorfile>classThyra_1_1DefaultProductVector.html</anchorfile>
      <anchor>a3925963101899b94b2d04bf5b3b2d76c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>description</name>
      <anchorfile>classThyra_1_1DefaultProductVector.html</anchorfile>
      <anchor>a4ecb691b941019cd767d6f0c47cd6d98</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>describe</name>
      <anchorfile>classThyra_1_1DefaultProductVector.html</anchorfile>
      <anchor>a4fe5687727987aec13722ee3ae96ed20</anchor>
      <arglist>(Teuchos::FancyOStream &amp;out, const Teuchos::EVerbosityLevel verbLevel) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setBlock</name>
      <anchorfile>classThyra_1_1DefaultProductVector.html</anchorfile>
      <anchor>a6fc547c188a7b13bfbaf91f9a7f398fb</anchor>
      <arglist>(int i, const RCP&lt; const VectorBase&lt; Scalar &gt; &gt; &amp;b)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setNonconstBlock</name>
      <anchorfile>classThyra_1_1DefaultProductVector.html</anchorfile>
      <anchor>a6f1f4bb9638d14c8d8f9b311662af05c</anchor>
      <arglist>(int i, const RCP&lt; VectorBase&lt; Scalar &gt; &gt; &amp;b)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; VectorBase&lt; Scalar &gt; &gt;</type>
      <name>getNonconstVectorBlock</name>
      <anchorfile>classThyra_1_1DefaultProductVector.html</anchorfile>
      <anchor>aaaf2558e714ce3a634f8ae7f76cd83c9</anchor>
      <arglist>(const int k)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const VectorBase&lt; Scalar &gt; &gt;</type>
      <name>getVectorBlock</name>
      <anchorfile>classThyra_1_1DefaultProductVector.html</anchorfile>
      <anchor>a72a870bff0194cd32ef1baff0d3d4ddd</anchor>
      <arglist>(const int k) const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const ProductVectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>productSpace</name>
      <anchorfile>classThyra_1_1DefaultProductVector.html</anchorfile>
      <anchor>acdbf768d426a8af88d4554df93721de8</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>blockIsConst</name>
      <anchorfile>classThyra_1_1DefaultProductVector.html</anchorfile>
      <anchor>a409fc5d7db7e0de42081383ff44eb9d0</anchor>
      <arglist>(const int k) const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; MultiVectorBase&lt; Scalar &gt; &gt;</type>
      <name>getNonconstMultiVectorBlock</name>
      <anchorfile>classThyra_1_1DefaultProductVector.html</anchorfile>
      <anchor>a5ff6cb1899813552471cbce8f722abde</anchor>
      <arglist>(const int k)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const MultiVectorBase&lt; Scalar &gt; &gt;</type>
      <name>getMultiVectorBlock</name>
      <anchorfile>classThyra_1_1DefaultProductVector.html</anchorfile>
      <anchor>a2d412eea71f3ea14e70f130f3526d905</anchor>
      <arglist>(const int k) const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const VectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>space</name>
      <anchorfile>classThyra_1_1DefaultProductVector.html</anchorfile>
      <anchor>a1719b61c1e1edcee443a0cdaba921cea</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>applyOpImpl</name>
      <anchorfile>classThyra_1_1DefaultProductVector.html</anchorfile>
      <anchor>a1e1a93fa920d39021c74ffb470cd7177</anchor>
      <arglist>(const RTOpPack::RTOpT&lt; Scalar &gt; &amp;op, const ArrayView&lt; const Ptr&lt; const VectorBase&lt; Scalar &gt; &gt; &gt; &amp;vecs, const ArrayView&lt; const Ptr&lt; VectorBase&lt; Scalar &gt; &gt; &gt; &amp;targ_vecs, const Ptr&lt; RTOpPack::ReductTarget &gt; &amp;reduct_obj, const Ordinal global_offset) const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>acquireDetachedVectorViewImpl</name>
      <anchorfile>classThyra_1_1DefaultProductVector.html</anchorfile>
      <anchor>a14bffdba9e56bb429070534ea1fb37d2</anchor>
      <arglist>(const Range1D &amp;rng, RTOpPack::ConstSubVectorView&lt; Scalar &gt; *sub_vec) const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>releaseDetachedVectorViewImpl</name>
      <anchorfile>classThyra_1_1DefaultProductVector.html</anchorfile>
      <anchor>a3d302897e86f2c05601a642923cda7bf</anchor>
      <arglist>(RTOpPack::ConstSubVectorView&lt; Scalar &gt; *sub_vec) const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>acquireNonconstDetachedVectorViewImpl</name>
      <anchorfile>classThyra_1_1DefaultProductVector.html</anchorfile>
      <anchor>a24b8c8e53141b63a3ef36af97465aefe</anchor>
      <arglist>(const Range1D &amp;rng, RTOpPack::SubVectorView&lt; Scalar &gt; *sub_vec)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>commitNonconstDetachedVectorViewImpl</name>
      <anchorfile>classThyra_1_1DefaultProductVector.html</anchorfile>
      <anchor>aee6a907e7b2d92a8e741ccb1dea470a3</anchor>
      <arglist>(RTOpPack::SubVectorView&lt; Scalar &gt; *sub_vec)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>setSubVectorImpl</name>
      <anchorfile>classThyra_1_1DefaultProductVector.html</anchorfile>
      <anchor>a134b019167d75f958d054277db5caeaf</anchor>
      <arglist>(const RTOpPack::SparseSubVectorT&lt; Scalar &gt; &amp;sub_vec)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>assignImpl</name>
      <anchorfile>classThyra_1_1DefaultProductVector.html</anchorfile>
      <anchor>a31bb559517a2e8be08e0ba4c8bf0008a</anchor>
      <arglist>(Scalar alpha)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::DefaultProductVectorSpace</name>
    <filename>classThyra_1_1DefaultProductVectorSpace.html</filename>
    <templarg></templarg>
    <base virtualness="virtual">Thyra::ProductVectorSpaceBase</base>
    <base protection="protected" virtualness="virtual">Thyra::VectorSpaceDefaultBase</base>
    <member kind="function">
      <type>RCP&lt; DefaultProductVectorSpace&lt; Scalar &gt; &gt;</type>
      <name>productVectorSpace</name>
      <anchorfile>classThyra_1_1DefaultProductVectorSpace.html</anchorfile>
      <anchor>aa147f919f41244fcb42f4bff3e999f3d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; DefaultProductVectorSpace&lt; Scalar &gt; &gt;</type>
      <name>productVectorSpace</name>
      <anchorfile>classThyra_1_1DefaultProductVectorSpace.html</anchorfile>
      <anchor>aa5210db39f4f1e775941065110508c11</anchor>
      <arglist>(const ArrayView&lt; RCP&lt; const VectorSpaceBase&lt; Scalar &gt; &gt; &gt; &amp;vecSpaces)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; DefaultProductVectorSpace&lt; Scalar &gt; &gt;</type>
      <name>productVectorSpace</name>
      <anchorfile>classThyra_1_1DefaultProductVectorSpace.html</anchorfile>
      <anchor>a7ffd4936b7df00bde13c0880f5d15166</anchor>
      <arglist>(const RCP&lt; const VectorSpaceBase&lt; Scalar &gt; &gt; &amp;vecSpace, const int numBlocks)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>DefaultProductVectorSpace</name>
      <anchorfile>classThyra_1_1DefaultProductVectorSpace.html</anchorfile>
      <anchor>a0e801e91fcb1bb3d6f057700284581f6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>DefaultProductVectorSpace</name>
      <anchorfile>classThyra_1_1DefaultProductVectorSpace.html</anchorfile>
      <anchor>aca888d093c46b949ea0a682514360dc1</anchor>
      <arglist>(const ArrayView&lt; const RCP&lt; const VectorSpaceBase&lt; Scalar &gt; &gt; &gt; &amp;vecSpaces)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>initialize</name>
      <anchorfile>classThyra_1_1DefaultProductVectorSpace.html</anchorfile>
      <anchor>a3eeed2f21bf6a86907081a1d06eaa22a</anchor>
      <arglist>(const ArrayView&lt; const RCP&lt; const VectorSpaceBase&lt; Scalar &gt; &gt; &gt; &amp;vecSpaces)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>hasBeenCloned</name>
      <anchorfile>classThyra_1_1DefaultProductVectorSpace.html</anchorfile>
      <anchor>a72a7c4db02b5736d5493ce4bde462c7b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>uninitialize</name>
      <anchorfile>classThyra_1_1DefaultProductVectorSpace.html</anchorfile>
      <anchor>a70e84cbf7481281560d838e1143a7e46</anchor>
      <arglist>(const ArrayView&lt; RCP&lt; const VectorSpaceBase&lt; Scalar &gt; &gt; &gt; &amp;vecSpaces=Teuchos::null)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const RCP&lt; const VectorSpaceBase&lt; Scalar &gt; &gt; *</type>
      <name>vecSpaces</name>
      <anchorfile>classThyra_1_1DefaultProductVectorSpace.html</anchorfile>
      <anchor>a580e7111210c1fd9bdc801c81acf16e5</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const Ordinal *</type>
      <name>vecSpacesOffsets</name>
      <anchorfile>classThyra_1_1DefaultProductVectorSpace.html</anchorfile>
      <anchor>a3a7cffcfa7d168a3d457dfc13d6035a5</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>getVecSpcPoss</name>
      <anchorfile>classThyra_1_1DefaultProductVectorSpace.html</anchorfile>
      <anchor>a2a4becf944f78521fc7ce97639c5ca6d</anchor>
      <arglist>(Ordinal i, int *kth_vector_space, Ordinal *kth_global_offset) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>numBlocks</name>
      <anchorfile>classThyra_1_1DefaultProductVectorSpace.html</anchorfile>
      <anchor>abd122fb422ca52c62cf3c6d33c495a5d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const VectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>getBlock</name>
      <anchorfile>classThyra_1_1DefaultProductVectorSpace.html</anchorfile>
      <anchor>ad1017e7d9a678d24ecf055df4dcaaaf4</anchor>
      <arglist>(const int k) const </arglist>
    </member>
    <member kind="function">
      <type>Ordinal</type>
      <name>dim</name>
      <anchorfile>classThyra_1_1DefaultProductVectorSpace.html</anchorfile>
      <anchor>a4ea0f1043a5e15c99a89e61c6ca2810f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isCompatible</name>
      <anchorfile>classThyra_1_1DefaultProductVectorSpace.html</anchorfile>
      <anchor>ac005189f5f555b55bb4b99e2f9d2b740</anchor>
      <arglist>(const VectorSpaceBase&lt; Scalar &gt; &amp;vecSpc) const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; VectorBase&lt; Scalar &gt; &gt;</type>
      <name>createMember</name>
      <anchorfile>classThyra_1_1DefaultProductVectorSpace.html</anchorfile>
      <anchor>ad9a114876f976b4694a4ab2e67f1c2fe</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Scalar</type>
      <name>scalarProd</name>
      <anchorfile>classThyra_1_1DefaultProductVectorSpace.html</anchorfile>
      <anchor>a3277551e4ca18b177e53c06731c95c81</anchor>
      <arglist>(const VectorBase&lt; Scalar &gt; &amp;x, const VectorBase&lt; Scalar &gt; &amp;y) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>scalarProdsImpl</name>
      <anchorfile>classThyra_1_1DefaultProductVectorSpace.html</anchorfile>
      <anchor>a7ef3b249e3333f77d8e5520ce7d96eb2</anchor>
      <arglist>(const MultiVectorBase&lt; Scalar &gt; &amp;X, const MultiVectorBase&lt; Scalar &gt; &amp;Y, const ArrayView&lt; Scalar &gt; &amp;scalarProds) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>hasInCoreView</name>
      <anchorfile>classThyra_1_1DefaultProductVectorSpace.html</anchorfile>
      <anchor>a9b6305c52024dc23fd08be1dc95c447d</anchor>
      <arglist>(const Range1D &amp;rng, const EViewType viewType, const EStrideType strideType) const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const VectorSpaceFactoryBase&lt; Scalar &gt; &gt;</type>
      <name>smallVecSpcFcty</name>
      <anchorfile>classThyra_1_1DefaultProductVectorSpace.html</anchorfile>
      <anchor>a0452e1957d3d2509f08f091932a57235</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; MultiVectorBase&lt; Scalar &gt; &gt;</type>
      <name>createMembers</name>
      <anchorfile>classThyra_1_1DefaultProductVectorSpace.html</anchorfile>
      <anchor>a8274ea1ad5ba34137a33c60d5d76e145</anchor>
      <arglist>(int numMembers) const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const VectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>clone</name>
      <anchorfile>classThyra_1_1DefaultProductVectorSpace.html</anchorfile>
      <anchor>aeaea050e2a03078b6c431f6d3f05dc22</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>description</name>
      <anchorfile>classThyra_1_1DefaultProductVectorSpace.html</anchorfile>
      <anchor>a90e56effc559940482bf69c024408210</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>describe</name>
      <anchorfile>classThyra_1_1DefaultProductVectorSpace.html</anchorfile>
      <anchor>a398a5081388218b07df34370b7aeca58</anchor>
      <arglist>(Teuchos::FancyOStream &amp;out, const Teuchos::EVerbosityLevel verbLevel) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::DefaultScaledAdjointLinearOp</name>
    <filename>classThyra_1_1DefaultScaledAdjointLinearOp.html</filename>
    <templarg>Scalar</templarg>
    <base virtualness="virtual">Thyra::ScaledAdjointLinearOpBase</base>
    <member kind="function">
      <type>RCP&lt; LinearOpBase&lt; Scalar &gt; &gt;</type>
      <name>nonconstScale</name>
      <anchorfile>classThyra_1_1DefaultScaledAdjointLinearOp.html</anchorfile>
      <anchor>abf3b05a39734d7806dd0bb035341d1b6</anchor>
      <arglist>(const Scalar &amp;scalar, const RCP&lt; LinearOpBase&lt; Scalar &gt; &gt; &amp;Op, const std::string &amp;label=&quot;&quot;)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const LinearOpBase&lt; Scalar &gt; &gt;</type>
      <name>scale</name>
      <anchorfile>classThyra_1_1DefaultScaledAdjointLinearOp.html</anchorfile>
      <anchor>a729b33aff6c491322f4607cb9c7d57fc</anchor>
      <arglist>(const Scalar &amp;scalar, const RCP&lt; const LinearOpBase&lt; Scalar &gt; &gt; &amp;Op, const std::string &amp;label=&quot;&quot;)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; LinearOpBase&lt; Scalar &gt; &gt;</type>
      <name>nonconstAdjoint</name>
      <anchorfile>classThyra_1_1DefaultScaledAdjointLinearOp.html</anchorfile>
      <anchor>ab04644b9af873603ce55955ceaf4a847</anchor>
      <arglist>(const RCP&lt; LinearOpBase&lt; Scalar &gt; &gt; &amp;Op, const std::string &amp;label=&quot;&quot;)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const LinearOpBase&lt; Scalar &gt; &gt;</type>
      <name>adjoint</name>
      <anchorfile>classThyra_1_1DefaultScaledAdjointLinearOp.html</anchorfile>
      <anchor>aee9f8e8b00e998919ebf7fef83acb064</anchor>
      <arglist>(const RCP&lt; const LinearOpBase&lt; Scalar &gt; &gt; &amp;Op, const std::string &amp;label=&quot;&quot;)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; LinearOpBase&lt; Scalar &gt; &gt;</type>
      <name>nonconstTranspose</name>
      <anchorfile>classThyra_1_1DefaultScaledAdjointLinearOp.html</anchorfile>
      <anchor>ae686eb8000896f6f352521e93a30ecd3</anchor>
      <arglist>(const RCP&lt; LinearOpBase&lt; Scalar &gt; &gt; &amp;Op, const std::string &amp;label=&quot;&quot;)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const LinearOpBase&lt; Scalar &gt; &gt;</type>
      <name>transpose</name>
      <anchorfile>classThyra_1_1DefaultScaledAdjointLinearOp.html</anchorfile>
      <anchor>aad23ea7e2c02390532e0f803529ce228</anchor>
      <arglist>(const RCP&lt; const LinearOpBase&lt; Scalar &gt; &gt; &amp;Op, const std::string &amp;label=&quot;&quot;)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; LinearOpBase&lt; Scalar &gt; &gt;</type>
      <name>nonconstScaleAndAdjoint</name>
      <anchorfile>classThyra_1_1DefaultScaledAdjointLinearOp.html</anchorfile>
      <anchor>af71c9bb67ac2d80cec9363bc71d34b06</anchor>
      <arglist>(const Scalar &amp;scalar, const EOpTransp &amp;transp, const RCP&lt; LinearOpBase&lt; Scalar &gt; &gt; &amp;Op, const std::string &amp;label=&quot;&quot;)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const LinearOpBase&lt; Scalar &gt; &gt;</type>
      <name>scaleAndAdjoint</name>
      <anchorfile>classThyra_1_1DefaultScaledAdjointLinearOp.html</anchorfile>
      <anchor>ae86eb42da9cb80243152da90753a8cfc</anchor>
      <arglist>(const Scalar &amp;scalar, const EOpTransp &amp;transp, const RCP&lt; const LinearOpBase&lt; Scalar &gt; &gt; &amp;Op, const std::string &amp;label=&quot;&quot;)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>DefaultScaledAdjointLinearOp</name>
      <anchorfile>classThyra_1_1DefaultScaledAdjointLinearOp.html</anchorfile>
      <anchor>ade14fc0ff644fe696c3e9e943f9e40b5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>DefaultScaledAdjointLinearOp</name>
      <anchorfile>classThyra_1_1DefaultScaledAdjointLinearOp.html</anchorfile>
      <anchor>aa0ba0ba4385deaa153f93e33b8df14ef</anchor>
      <arglist>(const Scalar &amp;scalar, const EOpTransp &amp;transp, const RCP&lt; LinearOpBase&lt; Scalar &gt; &gt; &amp;Op)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>DefaultScaledAdjointLinearOp</name>
      <anchorfile>classThyra_1_1DefaultScaledAdjointLinearOp.html</anchorfile>
      <anchor>a794288d2862ed3b8c28307ea483b6fea</anchor>
      <arglist>(const Scalar &amp;scalar, const EOpTransp &amp;transp, const RCP&lt; const LinearOpBase&lt; Scalar &gt; &gt; &amp;Op)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initialize</name>
      <anchorfile>classThyra_1_1DefaultScaledAdjointLinearOp.html</anchorfile>
      <anchor>adb1d2539996b91b7a6f0a944afed1d0c</anchor>
      <arglist>(const Scalar &amp;scalar, const EOpTransp &amp;transp, const RCP&lt; LinearOpBase&lt; Scalar &gt; &gt; &amp;Op)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initialize</name>
      <anchorfile>classThyra_1_1DefaultScaledAdjointLinearOp.html</anchorfile>
      <anchor>a9f41dd420b3b0d8f7759ec655633d2b6</anchor>
      <arglist>(const Scalar &amp;scalar, const EOpTransp &amp;transp, const RCP&lt; const LinearOpBase&lt; Scalar &gt; &gt; &amp;Op)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; LinearOpBase&lt; Scalar &gt; &gt;</type>
      <name>getNonconstOp</name>
      <anchorfile>classThyra_1_1DefaultScaledAdjointLinearOp.html</anchorfile>
      <anchor>a0811531c27630ba6daea40949625ad2b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const LinearOpBase&lt; Scalar &gt; &gt;</type>
      <name>getOp</name>
      <anchorfile>classThyra_1_1DefaultScaledAdjointLinearOp.html</anchorfile>
      <anchor>ad0fc666cfc13757364f11d703a930ee4</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>uninitialize</name>
      <anchorfile>classThyra_1_1DefaultScaledAdjointLinearOp.html</anchorfile>
      <anchor>a83a74ebf6ffa2c11217be73fde153fa1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>description</name>
      <anchorfile>classThyra_1_1DefaultScaledAdjointLinearOp.html</anchorfile>
      <anchor>ab4bd56577369d5c77913a3649133174b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>describe</name>
      <anchorfile>classThyra_1_1DefaultScaledAdjointLinearOp.html</anchorfile>
      <anchor>ae20b450ed7433917f3e14b706249a37e</anchor>
      <arglist>(Teuchos::FancyOStream &amp;out, const Teuchos::EVerbosityLevel verbLevel) const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const VectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>range</name>
      <anchorfile>classThyra_1_1DefaultScaledAdjointLinearOp.html</anchorfile>
      <anchor>a596d730d2ff52c9e27a2f9be2e5e5f4d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const VectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>domain</name>
      <anchorfile>classThyra_1_1DefaultScaledAdjointLinearOp.html</anchorfile>
      <anchor>af1099cc635c4299e463becad5c889c3c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const LinearOpBase&lt; Scalar &gt; &gt;</type>
      <name>clone</name>
      <anchorfile>classThyra_1_1DefaultScaledAdjointLinearOp.html</anchorfile>
      <anchor>ab481391955445a36b3e7a314997690b2</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>bool</type>
      <name>opSupportedImpl</name>
      <anchorfile>classThyra_1_1DefaultScaledAdjointLinearOp.html</anchorfile>
      <anchor>a509fd0094c87ae94f3c3905bee1a0c0d</anchor>
      <arglist>(EOpTransp M_trans) const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>applyImpl</name>
      <anchorfile>classThyra_1_1DefaultScaledAdjointLinearOp.html</anchorfile>
      <anchor>ad7ac9e1e0d4801f80cb16d5470ccdb71</anchor>
      <arglist>(const EOpTransp M_trans, const MultiVectorBase&lt; Scalar &gt; &amp;X, const Ptr&lt; MultiVectorBase&lt; Scalar &gt; &gt; &amp;Y, const Scalar alpha, const Scalar beta) const </arglist>
    </member>
    <member kind="function">
      <type>Scalar</type>
      <name>overallScalar</name>
      <anchorfile>classThyra_1_1DefaultScaledAdjointLinearOp.html</anchorfile>
      <anchor>a991b9e9914e5a4023f65b09fa8ea8bd2</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>EOpTransp</type>
      <name>overallTransp</name>
      <anchorfile>classThyra_1_1DefaultScaledAdjointLinearOp.html</anchorfile>
      <anchor>ac766be064b23dcfcdcddbdf21a71ce8e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; LinearOpBase&lt; Scalar &gt; &gt;</type>
      <name>getNonconstOrigOp</name>
      <anchorfile>classThyra_1_1DefaultScaledAdjointLinearOp.html</anchorfile>
      <anchor>a322b8afb5bcced2bc0d6be4417e77bc6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const LinearOpBase&lt; Scalar &gt; &gt;</type>
      <name>getOrigOp</name>
      <anchorfile>classThyra_1_1DefaultScaledAdjointLinearOp.html</anchorfile>
      <anchor>a37b564c37e05bd874e0d30ef9c3513e4</anchor>
      <arglist>() const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::DefaultSerialDenseLinearOpWithSolve</name>
    <filename>classThyra_1_1DefaultSerialDenseLinearOpWithSolve.html</filename>
    <templarg></templarg>
    <base virtualness="virtual">Thyra::LinearOpWithSolveBase</base>
    <member kind="function">
      <type>RCP&lt; DefaultSerialDenseLinearOpWithSolve&lt; Scalar &gt; &gt;</type>
      <name>defaultSerialDenseLinearOpWithSolve</name>
      <anchorfile>classThyra_1_1DefaultSerialDenseLinearOpWithSolve.html</anchorfile>
      <anchor>ad4f1a9930b211a5a63b68506de8f9f74</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; DefaultSerialDenseLinearOpWithSolve&lt; Scalar &gt; &gt;</type>
      <name>defaultSerialDenseLinearOpWithSolve</name>
      <anchorfile>classThyra_1_1DefaultSerialDenseLinearOpWithSolve.html</anchorfile>
      <anchor>aeab01750e5fcf1a1fb982259010c64e1</anchor>
      <arglist>(const RCP&lt; const MultiVectorBase&lt; Scalar &gt; &gt; &amp;M)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>DefaultSerialDenseLinearOpWithSolve</name>
      <anchorfile>classThyra_1_1DefaultSerialDenseLinearOpWithSolve.html</anchorfile>
      <anchor>adc70648ab73299be3ef8f18a441d0ec4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initialize</name>
      <anchorfile>classThyra_1_1DefaultSerialDenseLinearOpWithSolve.html</anchorfile>
      <anchor>a62d586bc5e233e43a30ae27ec5f38108</anchor>
      <arglist>(const RCP&lt; const MultiVectorBase&lt; Scalar &gt; &gt; &amp;M)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const LinearOpBase&lt; Scalar &gt; &gt;</type>
      <name>getFwdOp</name>
      <anchorfile>classThyra_1_1DefaultSerialDenseLinearOpWithSolve.html</anchorfile>
      <anchor>a470be90976df5fbc4ed4124eb94842b6</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const VectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>range</name>
      <anchorfile>classThyra_1_1DefaultSerialDenseLinearOpWithSolve.html</anchorfile>
      <anchor>a7b2547c616f592aecd40516439f93948</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const VectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>domain</name>
      <anchorfile>classThyra_1_1DefaultSerialDenseLinearOpWithSolve.html</anchorfile>
      <anchor>a9c617a23f5646b1a34646a6fc29ec5f9</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>bool</type>
      <name>opSupportedImpl</name>
      <anchorfile>classThyra_1_1DefaultSerialDenseLinearOpWithSolve.html</anchorfile>
      <anchor>a22c910bdfbe5f428e5fec5e7f6ca39b8</anchor>
      <arglist>(EOpTransp M_trans) const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>applyImpl</name>
      <anchorfile>classThyra_1_1DefaultSerialDenseLinearOpWithSolve.html</anchorfile>
      <anchor>a15cbf4864d732880f42e338617a6f7d9</anchor>
      <arglist>(const EOpTransp M_trans, const MultiVectorBase&lt; Scalar &gt; &amp;X, const Ptr&lt; MultiVectorBase&lt; Scalar &gt; &gt; &amp;Y, const Scalar alpha, const Scalar beta) const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>bool</type>
      <name>solveSupportsImpl</name>
      <anchorfile>classThyra_1_1DefaultSerialDenseLinearOpWithSolve.html</anchorfile>
      <anchor>a183e5a499d188fd7166b951ed9f8a4b4</anchor>
      <arglist>(EOpTransp M_trans) const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>bool</type>
      <name>solveSupportsSolveMeasureTypeImpl</name>
      <anchorfile>classThyra_1_1DefaultSerialDenseLinearOpWithSolve.html</anchorfile>
      <anchor>a38906b500a967cf3dadcc2c786a82d8c</anchor>
      <arglist>(EOpTransp M_trans, const SolveMeasureType &amp;solveMeasureType) const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>SolveStatus&lt; Scalar &gt;</type>
      <name>solveImpl</name>
      <anchorfile>classThyra_1_1DefaultSerialDenseLinearOpWithSolve.html</anchorfile>
      <anchor>ae966cf58de8e91601f84e846049c98b9</anchor>
      <arglist>(const EOpTransp transp, const MultiVectorBase&lt; Scalar &gt; &amp;B, const Ptr&lt; MultiVectorBase&lt; Scalar &gt; &gt; &amp;X, const Ptr&lt; const SolveCriteria&lt; Scalar &gt; &gt; solveCriteria) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::DefaultSerialDenseLinearOpWithSolveFactory</name>
    <filename>classThyra_1_1DefaultSerialDenseLinearOpWithSolveFactory.html</filename>
    <templarg></templarg>
    <base virtualness="virtual">Thyra::LinearOpWithSolveFactoryBase</base>
    <base protection="protected" virtualness="virtual">Teuchos::ParameterListAcceptorDefaultBase</base>
    <member kind="function">
      <type>void</type>
      <name>setParameterList</name>
      <anchorfile>classThyra_1_1DefaultSerialDenseLinearOpWithSolveFactory.html</anchorfile>
      <anchor>a862e68a9ba760f68d4753c4617709613</anchor>
      <arglist>(RCP&lt; ParameterList &gt; const &amp;paramList)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const ParameterList &gt;</type>
      <name>getValidParameters</name>
      <anchorfile>classThyra_1_1DefaultSerialDenseLinearOpWithSolveFactory.html</anchorfile>
      <anchor>a8b936a241b5d89a425f4ec9114493042</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>acceptsPreconditionerFactory</name>
      <anchorfile>classThyra_1_1DefaultSerialDenseLinearOpWithSolveFactory.html</anchorfile>
      <anchor>a86a659212f46cd04c6bd0e1eb95990a8</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>setPreconditionerFactory</name>
      <anchorfile>classThyra_1_1DefaultSerialDenseLinearOpWithSolveFactory.html</anchorfile>
      <anchor>a26a84b4d902fdb12c344f17340985d3f</anchor>
      <arglist>(const RCP&lt; PreconditionerFactoryBase&lt; Scalar &gt; &gt; &amp;precFactory, const std::string &amp;precFactoryName)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual RCP&lt; PreconditionerFactoryBase&lt; Scalar &gt; &gt;</type>
      <name>getPreconditionerFactory</name>
      <anchorfile>classThyra_1_1DefaultSerialDenseLinearOpWithSolveFactory.html</anchorfile>
      <anchor>a0a8500322cd0ef75db0db9061dacc016</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>unsetPreconditionerFactory</name>
      <anchorfile>classThyra_1_1DefaultSerialDenseLinearOpWithSolveFactory.html</anchorfile>
      <anchor>ab589337a519c6fedaea8b3b4a92c08b7</anchor>
      <arglist>(RCP&lt; PreconditionerFactoryBase&lt; Scalar &gt; &gt; *precFactory, std::string *precFactoryName)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>isCompatible</name>
      <anchorfile>classThyra_1_1DefaultSerialDenseLinearOpWithSolveFactory.html</anchorfile>
      <anchor>aceb98d2c97192b875725162898f0017c</anchor>
      <arglist>(const LinearOpSourceBase&lt; Scalar &gt; &amp;fwdOpSrc) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual RCP&lt; LinearOpWithSolveBase&lt; Scalar &gt; &gt;</type>
      <name>createOp</name>
      <anchorfile>classThyra_1_1DefaultSerialDenseLinearOpWithSolveFactory.html</anchorfile>
      <anchor>a54d723d307cd72e67ebf8d17f50e8faa</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>initializeOp</name>
      <anchorfile>classThyra_1_1DefaultSerialDenseLinearOpWithSolveFactory.html</anchorfile>
      <anchor>a774d9910c64ae456042c514df0022c32</anchor>
      <arglist>(const RCP&lt; const LinearOpSourceBase&lt; Scalar &gt; &gt; &amp;fwdOpSrc, LinearOpWithSolveBase&lt; Scalar &gt; *Op, const ESupportSolveUse supportSolveUse) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>initializeAndReuseOp</name>
      <anchorfile>classThyra_1_1DefaultSerialDenseLinearOpWithSolveFactory.html</anchorfile>
      <anchor>a7a54033c37b2c219d59607bffdfa9301</anchor>
      <arglist>(const RCP&lt; const LinearOpSourceBase&lt; Scalar &gt; &gt; &amp;fwdOpSrc, LinearOpWithSolveBase&lt; Scalar &gt; *Op) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>uninitializeOp</name>
      <anchorfile>classThyra_1_1DefaultSerialDenseLinearOpWithSolveFactory.html</anchorfile>
      <anchor>aca2cc4b72d4c098c157769bf7c20af78</anchor>
      <arglist>(LinearOpWithSolveBase&lt; Scalar &gt; *Op, RCP&lt; const LinearOpSourceBase&lt; Scalar &gt; &gt; *fwdOpSrc, RCP&lt; const PreconditionerBase&lt; Scalar &gt; &gt; *prec, RCP&lt; const LinearOpSourceBase&lt; Scalar &gt; &gt; *approxFwdOpSrc, ESupportSolveUse *supportSolveUse) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>supportsPreconditionerInputType</name>
      <anchorfile>classThyra_1_1DefaultSerialDenseLinearOpWithSolveFactory.html</anchorfile>
      <anchor>ae5c10f9b9a1698c3b0bf60cce98114ec</anchor>
      <arglist>(const EPreconditionerInputType precOpType) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>initializePreconditionedOp</name>
      <anchorfile>classThyra_1_1DefaultSerialDenseLinearOpWithSolveFactory.html</anchorfile>
      <anchor>af1671b7e50ee8c9dffeaa563605a5574</anchor>
      <arglist>(const RCP&lt; const LinearOpSourceBase&lt; Scalar &gt; &gt; &amp;fwdOpSrc, const RCP&lt; const PreconditionerBase&lt; Scalar &gt; &gt; &amp;prec, LinearOpWithSolveBase&lt; Scalar &gt; *Op, const ESupportSolveUse supportSolveUse) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>initializeApproxPreconditionedOp</name>
      <anchorfile>classThyra_1_1DefaultSerialDenseLinearOpWithSolveFactory.html</anchorfile>
      <anchor>ae13feb0c8cc738471fcb8a848a0e6db7</anchor>
      <arglist>(const RCP&lt; const LinearOpSourceBase&lt; Scalar &gt; &gt; &amp;fwdOpSrc, const RCP&lt; const LinearOpSourceBase&lt; Scalar &gt; &gt; &amp;approxFwdOpSrc, LinearOpWithSolveBase&lt; Scalar &gt; *Op, const ESupportSolveUse supportSolveUse) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::DefaultSerialVectorSpaceConverter</name>
    <filename>classThyra_1_1DefaultSerialVectorSpaceConverter.html</filename>
    <templarg></templarg>
    <templarg></templarg>
    <base virtualness="virtual">Thyra::SerialVectorSpaceConverterBase</base>
    <member kind="function" virtualness="virtual">
      <type>virtual Teuchos::RCP&lt; const VectorSpaceBase&lt; ScalarTo &gt; &gt;</type>
      <name>createVectorSpaceTo</name>
      <anchorfile>classThyra_1_1DefaultSerialVectorSpaceConverter.html</anchorfile>
      <anchor>a154b787999fc22da3f7f2b63cbe533d5</anchor>
      <arglist>(const VectorSpaceBase&lt; ScalarFrom &gt; &amp;vecSpc) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual Teuchos::RCP&lt; const VectorSpaceBase&lt; ScalarFrom &gt; &gt;</type>
      <name>createVectorSpaceFrom</name>
      <anchorfile>classThyra_1_1DefaultSerialVectorSpaceConverter.html</anchorfile>
      <anchor>ac00cbe82ff1ee383b3f5aa77564a169e</anchor>
      <arglist>(const VectorSpaceBase&lt; ScalarTo &gt; &amp;vecSpc) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::DefaultSpmdMultiVector</name>
    <filename>classThyra_1_1DefaultSpmdMultiVector.html</filename>
    <templarg></templarg>
    <base virtualness="virtual">Thyra::SpmdMultiVectorDefaultBase</base>
    <member kind="function">
      <type></type>
      <name>DefaultSpmdMultiVector</name>
      <anchorfile>classThyra_1_1DefaultSpmdMultiVector.html</anchorfile>
      <anchor>a172468e777bfab40aecdece3a45c0007</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>DefaultSpmdMultiVector</name>
      <anchorfile>classThyra_1_1DefaultSpmdMultiVector.html</anchorfile>
      <anchor>ad881633f3c43de2d42142a031741247a</anchor>
      <arglist>(const RCP&lt; const SpmdVectorSpaceBase&lt; Scalar &gt; &gt; &amp;spmdRangeSpace, const RCP&lt; const ScalarProdVectorSpaceBase&lt; Scalar &gt; &gt; &amp;domainSpace)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>DefaultSpmdMultiVector</name>
      <anchorfile>classThyra_1_1DefaultSpmdMultiVector.html</anchorfile>
      <anchor>ae2a9de4b790ac2314538c17694ff4532</anchor>
      <arglist>(const RCP&lt; const SpmdVectorSpaceBase&lt; Scalar &gt; &gt; &amp;spmdRangeSpace, const RCP&lt; const ScalarProdVectorSpaceBase&lt; Scalar &gt; &gt; &amp;domainSpace, const ArrayRCP&lt; Scalar &gt; &amp;localValues, const Ordinal leadingDim=-1)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initialize</name>
      <anchorfile>classThyra_1_1DefaultSpmdMultiVector.html</anchorfile>
      <anchor>abc131f2951963301c7d44890a9a1ee7b</anchor>
      <arglist>(const RCP&lt; const SpmdVectorSpaceBase&lt; Scalar &gt; &gt; &amp;spmdRangeSpace, const RCP&lt; const ScalarProdVectorSpaceBase&lt; Scalar &gt; &gt; &amp;domainSpace)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initialize</name>
      <anchorfile>classThyra_1_1DefaultSpmdMultiVector.html</anchorfile>
      <anchor>a44a4dd07f1b7db46618b83f47799389b</anchor>
      <arglist>(const RCP&lt; const SpmdVectorSpaceBase&lt; Scalar &gt; &gt; &amp;spmdRangeSpace, const RCP&lt; const ScalarProdVectorSpaceBase&lt; Scalar &gt; &gt; &amp;domainSpace, const ArrayRCP&lt; Scalar &gt; &amp;localValues, const Ordinal leadingDim=-1)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>uninitialize</name>
      <anchorfile>classThyra_1_1DefaultSpmdMultiVector.html</anchorfile>
      <anchor>a20bd95d82d4bbe3bf99d35591f087b31</anchor>
      <arglist>(RCP&lt; const SpmdVectorSpaceBase&lt; Scalar &gt; &gt; *spmdRangeSpace=NULL, RCP&lt; const ScalarProdVectorSpaceBase&lt; Scalar &gt; &gt; *domainSpace=NULL, ArrayRCP&lt; Scalar &gt; *localValues=NULL, Ordinal *leadingDim=NULL)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const ScalarProdVectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>domainScalarProdVecSpc</name>
      <anchorfile>classThyra_1_1DefaultSpmdMultiVector.html</anchorfile>
      <anchor>a2edbb291af21f38fe7193603ac83c0c3</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>RCP&lt; VectorBase&lt; Scalar &gt; &gt;</type>
      <name>nonconstColImpl</name>
      <anchorfile>classThyra_1_1DefaultSpmdMultiVector.html</anchorfile>
      <anchor>a34d31305a455b39022e6d7e41f6ea4ae</anchor>
      <arglist>(Ordinal j)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>RCP&lt; const MultiVectorBase&lt; Scalar &gt; &gt;</type>
      <name>contigSubViewImpl</name>
      <anchorfile>classThyra_1_1DefaultSpmdMultiVector.html</anchorfile>
      <anchor>a260384429609168c0153808e3a2308c1</anchor>
      <arglist>(const Range1D &amp;colRng) const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>RCP&lt; MultiVectorBase&lt; Scalar &gt; &gt;</type>
      <name>nonconstContigSubViewImpl</name>
      <anchorfile>classThyra_1_1DefaultSpmdMultiVector.html</anchorfile>
      <anchor>aa8de7c997ab7b69d9593de501749f4d9</anchor>
      <arglist>(const Range1D &amp;colRng)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>RCP&lt; const MultiVectorBase&lt; Scalar &gt; &gt;</type>
      <name>nonContigSubViewImpl</name>
      <anchorfile>classThyra_1_1DefaultSpmdMultiVector.html</anchorfile>
      <anchor>a719bf7bd98f6e239a9d2574082a2ea3c</anchor>
      <arglist>(const ArrayView&lt; const int &gt; &amp;cols) const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>RCP&lt; MultiVectorBase&lt; Scalar &gt; &gt;</type>
      <name>nonconstNonContigSubViewImpl</name>
      <anchorfile>classThyra_1_1DefaultSpmdMultiVector.html</anchorfile>
      <anchor>a33d0f3f45093da65dff382f73e0a7455</anchor>
      <arglist>(const ArrayView&lt; const int &gt; &amp;cols)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>RCP&lt; const SpmdVectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>spmdSpaceImpl</name>
      <anchorfile>classThyra_1_1DefaultSpmdMultiVector.html</anchorfile>
      <anchor>abe60e2feca303654e7a6ecea5c621ef5</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>getNonconstLocalMultiVectorDataImpl</name>
      <anchorfile>classThyra_1_1DefaultSpmdMultiVector.html</anchorfile>
      <anchor>a825877c715befda9933c64f18df0f4c0</anchor>
      <arglist>(const Ptr&lt; ArrayRCP&lt; Scalar &gt; &gt; &amp;localValues, const Ptr&lt; Ordinal &gt; &amp;leadingDim)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>getLocalMultiVectorDataImpl</name>
      <anchorfile>classThyra_1_1DefaultSpmdMultiVector.html</anchorfile>
      <anchor>abca79e62939008f6d06fc845ffa65acd</anchor>
      <arglist>(const Ptr&lt; ArrayRCP&lt; const Scalar &gt; &gt; &amp;localValues, const Ptr&lt; Ordinal &gt; &amp;leadingDim) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::DefaultSpmdMultiVectorFileIO</name>
    <filename>classThyra_1_1DefaultSpmdMultiVectorFileIO.html</filename>
    <templarg></templarg>
    <base>Thyra::MultiVectorFileIOBase</base>
    <member kind="function">
      <type></type>
      <name>DefaultSpmdMultiVectorFileIO</name>
      <anchorfile>classThyra_1_1DefaultSpmdMultiVectorFileIO.html</anchorfile>
      <anchor>a721f5cf9d97944f4f854cc462b03bdf8</anchor>
      <arglist>(const std::string &amp;extensionTagName=&quot;&quot;, const int numProcs=-1, const int procRank=-1)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setFileNameExtension</name>
      <anchorfile>classThyra_1_1DefaultSpmdMultiVectorFileIO.html</anchorfile>
      <anchor>ab221be1eae394395d508fd27551d7dd6</anchor>
      <arglist>(const std::string &amp;extensionTagName=&quot;&quot;, const int numProcs=-1, const int procRank=-1)</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>getLocalFileName</name>
      <anchorfile>classThyra_1_1DefaultSpmdMultiVectorFileIO.html</anchorfile>
      <anchor>a9969d6493da0975ff314e6c1f5092280</anchor>
      <arglist>(const std::string &amp;fileNameBase) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isCompatible</name>
      <anchorfile>classThyra_1_1DefaultSpmdMultiVectorFileIO.html</anchorfile>
      <anchor>a9a52c6c4972c0b20ae1a46a108960059</anchor>
      <arglist>(const MultiVectorBase&lt; Scalar &gt; &amp;mv) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>readMultiVectorFromFile</name>
      <anchorfile>classThyra_1_1DefaultSpmdMultiVectorFileIO.html</anchorfile>
      <anchor>a467c5f7a94cc067fc71ca6b4c80f16f6</anchor>
      <arglist>(const std::string &amp;fileNameBase, Thyra::MultiVectorBase&lt; Scalar &gt; *mv) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>writeMultiVectorToFile</name>
      <anchorfile>classThyra_1_1DefaultSpmdMultiVectorFileIO.html</anchorfile>
      <anchor>a5dff903bd1107bd21df3abf175b3b92d</anchor>
      <arglist>(const Thyra::MultiVectorBase&lt; Scalar &gt; &amp;mv, const std::string &amp;fileNameBase) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::DefaultSpmdVector</name>
    <filename>classThyra_1_1DefaultSpmdVector.html</filename>
    <templarg></templarg>
    <base virtualness="virtual">Thyra::SpmdVectorDefaultBase</base>
    <member kind="function">
      <type></type>
      <name>DefaultSpmdVector</name>
      <anchorfile>classThyra_1_1DefaultSpmdVector.html</anchorfile>
      <anchor>a9a2d986433717b2f0f58c40e4ae25b8b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>DefaultSpmdVector</name>
      <anchorfile>classThyra_1_1DefaultSpmdVector.html</anchorfile>
      <anchor>a3ac366766963a5c634e5badc38951cb0</anchor>
      <arglist>(const RCP&lt; const SpmdVectorSpaceBase&lt; Scalar &gt; &gt; &amp;spmdSpace, const ArrayRCP&lt; Scalar &gt; &amp;localValues, const Ordinal stride)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initialize</name>
      <anchorfile>classThyra_1_1DefaultSpmdVector.html</anchorfile>
      <anchor>a7699100520c3a2c72ad508873bc63bac</anchor>
      <arglist>(const RCP&lt; const SpmdVectorSpaceBase&lt; Scalar &gt; &gt; &amp;spmdSpace, const ArrayRCP&lt; Scalar &gt; &amp;localValues, const Ordinal stride)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>uninitialize</name>
      <anchorfile>classThyra_1_1DefaultSpmdVector.html</anchorfile>
      <anchor>aa5c68b891e70236c55eac30377e90f72</anchor>
      <arglist>(RCP&lt; const SpmdVectorSpaceBase&lt; Scalar &gt; &gt; *spmdSpace=NULL, ArrayRCP&lt; Scalar &gt; *localValues=NULL, Ordinal *stride=NULL)</arglist>
    </member>
    <member kind="function">
      <type>ArrayRCP&lt; Scalar &gt;</type>
      <name>getRCPtr</name>
      <anchorfile>classThyra_1_1DefaultSpmdVector.html</anchorfile>
      <anchor>a6be1c1fc3b36b52f9342d8c09f92fee3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>ArrayRCP&lt; const Scalar &gt;</type>
      <name>getRCPtr</name>
      <anchorfile>classThyra_1_1DefaultSpmdVector.html</anchorfile>
      <anchor>a10598c97db280b0cb2e10aa7738b8579</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Scalar *</type>
      <name>getPtr</name>
      <anchorfile>classThyra_1_1DefaultSpmdVector.html</anchorfile>
      <anchor>ac4b2dd136d9ae6c6ddc6991c645be422</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const Scalar *</type>
      <name>getPtr</name>
      <anchorfile>classThyra_1_1DefaultSpmdVector.html</anchorfile>
      <anchor>a8a8a2b69816171b23df591154b54188b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Ordinal</type>
      <name>getStride</name>
      <anchorfile>classThyra_1_1DefaultSpmdVector.html</anchorfile>
      <anchor>aa77f180aa67f6a0d06f90f2173e8f080</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const SpmdVectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>spmdSpaceImpl</name>
      <anchorfile>classThyra_1_1DefaultSpmdVector.html</anchorfile>
      <anchor>a0cc5856befdd2d23d86d30159965fa70</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>getNonconstLocalVectorDataImpl</name>
      <anchorfile>classThyra_1_1DefaultSpmdVector.html</anchorfile>
      <anchor>a1d80bce014be080868776c0be8380c53</anchor>
      <arglist>(const Ptr&lt; ArrayRCP&lt; Scalar &gt; &gt; &amp;localValues)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>getLocalVectorDataImpl</name>
      <anchorfile>classThyra_1_1DefaultSpmdVector.html</anchorfile>
      <anchor>a1ce073b1f9a36dd5b931472ce1c1b545</anchor>
      <arglist>(const Ptr&lt; ArrayRCP&lt; const Scalar &gt; &gt; &amp;localValues) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::DefaultSpmdVectorSpace</name>
    <filename>classThyra_1_1DefaultSpmdVectorSpace.html</filename>
    <templarg></templarg>
    <base>Thyra::SpmdVectorSpaceDefaultBase</base>
    <member kind="function">
      <type>RCP&lt; DefaultSpmdVectorSpace&lt; Scalar &gt; &gt;</type>
      <name>defaultSpmdVectorSpace</name>
      <anchorfile>classThyra_1_1DefaultSpmdVectorSpace.html</anchorfile>
      <anchor>a19c9ee5e1023ead38f98c9e5904f667d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; DefaultSpmdVectorSpace&lt; Scalar &gt; &gt;</type>
      <name>defaultSpmdVectorSpace</name>
      <anchorfile>classThyra_1_1DefaultSpmdVectorSpace.html</anchorfile>
      <anchor>a20a68190d01803b5a3e4f98f23471a80</anchor>
      <arglist>(const Ordinal dim)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; DefaultSpmdVectorSpace&lt; Scalar &gt; &gt;</type>
      <name>defaultSpmdVectorSpace</name>
      <anchorfile>classThyra_1_1DefaultSpmdVectorSpace.html</anchorfile>
      <anchor>a3e50c9762ac77aa7b54176dd7acd13fa</anchor>
      <arglist>(const RCP&lt; const Teuchos::Comm&lt; Ordinal &gt; &gt; &amp;comm, const Ordinal localSubDim, const Ordinal globalDim, const int isLocallyReplicated=false)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; DefaultSpmdVectorSpace&lt; Scalar &gt; &gt;</type>
      <name>locallyReplicatedDefaultSpmdVectorSpace</name>
      <anchorfile>classThyra_1_1DefaultSpmdVectorSpace.html</anchorfile>
      <anchor>a4b5115eff84879188cd8af654cad9eb4</anchor>
      <arglist>(const RCP&lt; const Teuchos::Comm&lt; Ordinal &gt; &gt; &amp;comm, const Ordinal globalDim)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static RCP&lt; DefaultSpmdVectorSpace&lt; Scalar &gt; &gt;</type>
      <name>create</name>
      <anchorfile>classThyra_1_1DefaultSpmdVectorSpace.html</anchorfile>
      <anchor>a6d6c4bac2e8e8d11caa2420c61ec43ed</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initialize</name>
      <anchorfile>classThyra_1_1DefaultSpmdVectorSpace.html</anchorfile>
      <anchor>ab2d5271f66cc00ebe5c288a9b91776f8</anchor>
      <arglist>(const Ordinal dim)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initialize</name>
      <anchorfile>classThyra_1_1DefaultSpmdVectorSpace.html</anchorfile>
      <anchor>aadeff5ae3a0a92c19f3ab242fc0bab97</anchor>
      <arglist>(const RCP&lt; const Teuchos::Comm&lt; Ordinal &gt; &gt; &amp;comm, const Ordinal localSubDim, const Ordinal globalDim, const bool isLocallyReplicated=false)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>uninitialize</name>
      <anchorfile>classThyra_1_1DefaultSpmdVectorSpace.html</anchorfile>
      <anchor>aed8c1b519a86dd8b78868888d5ba780e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>hasInCoreView</name>
      <anchorfile>classThyra_1_1DefaultSpmdVectorSpace.html</anchorfile>
      <anchor>a54b1a7833757a8d775114c13ddca5e25</anchor>
      <arglist>(const Range1D &amp;rng, const EViewType viewType, const EStrideType strideType) const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const VectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>clone</name>
      <anchorfile>classThyra_1_1DefaultSpmdVectorSpace.html</anchorfile>
      <anchor>ad7e747815902fdcf6dd9f837b072975d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>RCP&lt; VectorBase&lt; Scalar &gt; &gt;</type>
      <name>createMember</name>
      <anchorfile>classThyra_1_1DefaultSpmdVectorSpace.html</anchorfile>
      <anchor>aa681f996eebed8b1bac013911279c3af</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>RCP&lt; MultiVectorBase&lt; Scalar &gt; &gt;</type>
      <name>createMembers</name>
      <anchorfile>classThyra_1_1DefaultSpmdVectorSpace.html</anchorfile>
      <anchor>aad9144ecf2012cef769a18b3b8cd208b</anchor>
      <arglist>(int numMembers) const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>RCP&lt; VectorBase&lt; Scalar &gt; &gt;</type>
      <name>createMemberView</name>
      <anchorfile>classThyra_1_1DefaultSpmdVectorSpace.html</anchorfile>
      <anchor>a5c6b0f3fce6ac2201b2aaddd3dc8d94a</anchor>
      <arglist>(const RTOpPack::SubVectorView&lt; Scalar &gt; &amp;raw_v) const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>RCP&lt; const VectorBase&lt; Scalar &gt; &gt;</type>
      <name>createMemberView</name>
      <anchorfile>classThyra_1_1DefaultSpmdVectorSpace.html</anchorfile>
      <anchor>a76c5db0cb65704d9f27c856364db8a1b</anchor>
      <arglist>(const RTOpPack::ConstSubVectorView&lt; Scalar &gt; &amp;raw_v) const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>RCP&lt; MultiVectorBase&lt; Scalar &gt; &gt;</type>
      <name>createMembersView</name>
      <anchorfile>classThyra_1_1DefaultSpmdVectorSpace.html</anchorfile>
      <anchor>adb07c36310ec8c944ac00c37b9590223</anchor>
      <arglist>(const RTOpPack::SubMultiVectorView&lt; Scalar &gt; &amp;raw_mv) const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>RCP&lt; const MultiVectorBase&lt; Scalar &gt; &gt;</type>
      <name>createMembersView</name>
      <anchorfile>classThyra_1_1DefaultSpmdVectorSpace.html</anchorfile>
      <anchor>a4c7b06652a4884c3686bebb6b714e759</anchor>
      <arglist>(const RTOpPack::ConstSubMultiVectorView&lt; Scalar &gt; &amp;raw_mv) const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const Teuchos::Comm&lt; Ordinal &gt; &gt;</type>
      <name>getComm</name>
      <anchorfile>classThyra_1_1DefaultSpmdVectorSpace.html</anchorfile>
      <anchor>a874556bc9127d11d7e4940c462b289f1</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Ordinal</type>
      <name>localSubDim</name>
      <anchorfile>classThyra_1_1DefaultSpmdVectorSpace.html</anchorfile>
      <anchor>ad22a7165b8bedef7db79035b0c3bbe10</anchor>
      <arglist>() const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::DefaultSpmdVectorSpaceFactory</name>
    <filename>classThyra_1_1DefaultSpmdVectorSpaceFactory.html</filename>
    <templarg></templarg>
    <base>Thyra::VectorSpaceFactoryBase</base>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Teuchos::Comm&lt; Ordinal &gt; &gt;</type>
      <name>getComm</name>
      <anchorfile>classThyra_1_1DefaultSpmdVectorSpaceFactory.html</anchorfile>
      <anchor>acf7ee7b30598c03b58e232fd1084313f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>DefaultSpmdVectorSpaceFactory</name>
      <anchorfile>classThyra_1_1DefaultSpmdVectorSpaceFactory.html</anchorfile>
      <anchor>adf69efb274ab53b132e6edd77de6fbbb</anchor>
      <arglist>(const Teuchos::RCP&lt; const Teuchos::Comm&lt; Ordinal &gt; &gt; &amp;comm=Teuchos::null)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; DefaultSpmdVectorSpaceFactory&lt; Scalar &gt; &gt;</type>
      <name>defaultSpmdVectorSpaceFactory</name>
      <anchorfile>classThyra_1_1DefaultSpmdVectorSpaceFactory.html</anchorfile>
      <anchor>ad0fb95d999ac1e14ac8d0f299496c8f9</anchor>
      <arglist>(const Teuchos::RCP&lt; const Teuchos::Comm&lt; Ordinal &gt; &gt; &amp;comm=Teuchos::null)</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const VectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>createVecSpc</name>
      <anchorfile>classThyra_1_1DefaultSpmdVectorSpaceFactory.html</anchorfile>
      <anchor>a7cb637e11015324d65d3a02ac2fe16d1</anchor>
      <arglist>(int dim) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::DefaultStateEliminationModelEvaluator</name>
    <filename>classThyra_1_1DefaultStateEliminationModelEvaluator.html</filename>
    <templarg></templarg>
    <base virtualness="virtual">Thyra::ModelEvaluatorDelegatorBase</base>
    <member kind="function">
      <type></type>
      <name>DefaultStateEliminationModelEvaluator</name>
      <anchorfile>classThyra_1_1DefaultStateEliminationModelEvaluator.html</anchorfile>
      <anchor>a543775c1a014762c7535e544627002d1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>DefaultStateEliminationModelEvaluator</name>
      <anchorfile>classThyra_1_1DefaultStateEliminationModelEvaluator.html</anchorfile>
      <anchor>a75c4dfbe3c759e453d943e94594f560a</anchor>
      <arglist>(const Teuchos::RCP&lt; ModelEvaluator&lt; Scalar &gt; &gt; &amp;thyraModel, const Teuchos::RCP&lt; NonlinearSolverBase&lt; Scalar &gt; &gt; &amp;stateSolver)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initialize</name>
      <anchorfile>classThyra_1_1DefaultStateEliminationModelEvaluator.html</anchorfile>
      <anchor>a45ad3796a6c0fb31241863003ae999ed</anchor>
      <arglist>(const Teuchos::RCP&lt; ModelEvaluator&lt; Scalar &gt; &gt; &amp;thyraModel, const Teuchos::RCP&lt; NonlinearSolverBase&lt; Scalar &gt; &gt; &amp;stateSolver)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>uninitialize</name>
      <anchorfile>classThyra_1_1DefaultStateEliminationModelEvaluator.html</anchorfile>
      <anchor>adaf41121b696608e01ff845c91bb9715</anchor>
      <arglist>(Teuchos::RCP&lt; ModelEvaluator&lt; Scalar &gt; &gt; *thyraModel=NULL, Teuchos::RCP&lt; NonlinearSolverBase&lt; Scalar &gt; &gt; *stateSolver=NULL)</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>description</name>
      <anchorfile>classThyra_1_1DefaultStateEliminationModelEvaluator.html</anchorfile>
      <anchor>a2da840fe55fc025c7a93483da141db5f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const VectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>get_x_space</name>
      <anchorfile>classThyra_1_1DefaultStateEliminationModelEvaluator.html</anchorfile>
      <anchor>aedda6b91ea1e0216f0b5ca6c1f77e8d8</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const VectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>get_f_space</name>
      <anchorfile>classThyra_1_1DefaultStateEliminationModelEvaluator.html</anchorfile>
      <anchor>a02c3544666d730c6f6676fa8fe6cc92e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>ModelEvaluatorBase::InArgs&lt; Scalar &gt;</type>
      <name>getNominalValues</name>
      <anchorfile>classThyra_1_1DefaultStateEliminationModelEvaluator.html</anchorfile>
      <anchor>a93ca7a6d7e473f48634b1695ad0bf1ac</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>ModelEvaluatorBase::InArgs&lt; Scalar &gt;</type>
      <name>getLowerBounds</name>
      <anchorfile>classThyra_1_1DefaultStateEliminationModelEvaluator.html</anchorfile>
      <anchor>a7ae7e96dfb6ee803518645bbad0177f7</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>ModelEvaluatorBase::InArgs&lt; Scalar &gt;</type>
      <name>getUpperBounds</name>
      <anchorfile>classThyra_1_1DefaultStateEliminationModelEvaluator.html</anchorfile>
      <anchor>a708d463fa2bde770b7e55277be95e6df</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; LinearOpWithSolveBase&lt; Scalar &gt; &gt;</type>
      <name>create_W</name>
      <anchorfile>classThyra_1_1DefaultStateEliminationModelEvaluator.html</anchorfile>
      <anchor>aba9680a3ac4183964d628a2efbbe6549</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; LinearOpBase&lt; Scalar &gt; &gt;</type>
      <name>create_W_op</name>
      <anchorfile>classThyra_1_1DefaultStateEliminationModelEvaluator.html</anchorfile>
      <anchor>a30cbb18d742995c8a601851b5c9c670d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>ModelEvaluatorBase::InArgs&lt; Scalar &gt;</type>
      <name>createInArgs</name>
      <anchorfile>classThyra_1_1DefaultStateEliminationModelEvaluator.html</anchorfile>
      <anchor>a9a888a52b3b47ddba7cec2a9a7f1a71c</anchor>
      <arglist>() const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::DefaultZeroLinearOp</name>
    <filename>classThyra_1_1DefaultZeroLinearOp.html</filename>
    <templarg></templarg>
    <base virtualness="virtual">Thyra::ZeroLinearOpBase</base>
    <base virtualness="virtual">Thyra::RowStatLinearOpBase</base>
    <base virtualness="virtual">Thyra::ScaledLinearOpBase</base>
    <member kind="function">
      <type>RCP&lt; const LinearOpBase&lt; Scalar &gt; &gt;</type>
      <name>zero</name>
      <anchorfile>classThyra_1_1DefaultZeroLinearOp.html</anchorfile>
      <anchor>aca667f95e92a1b3bccee85bc7e7c4058</anchor>
      <arglist>(const RCP&lt; const VectorSpaceBase&lt; Scalar &gt; &gt; &amp;range, const RCP&lt; const VectorSpaceBase&lt; Scalar &gt; &gt; &amp;domain)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; LinearOpBase&lt; Scalar &gt; &gt;</type>
      <name>nonconstZero</name>
      <anchorfile>classThyra_1_1DefaultZeroLinearOp.html</anchorfile>
      <anchor>aa43a56efa209a9abbdc09bec9c9d8041</anchor>
      <arglist>(const RCP&lt; const VectorSpaceBase&lt; Scalar &gt; &gt; &amp;range, const RCP&lt; const VectorSpaceBase&lt; Scalar &gt; &gt; &amp;domain)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>DefaultZeroLinearOp</name>
      <anchorfile>classThyra_1_1DefaultZeroLinearOp.html</anchorfile>
      <anchor>ab07420dead4f52c763f5aa26c31c3ef0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>DefaultZeroLinearOp</name>
      <anchorfile>classThyra_1_1DefaultZeroLinearOp.html</anchorfile>
      <anchor>a182fa81f269c2afbc8ccd2d7b21e2787</anchor>
      <arglist>(const RCP&lt; const VectorSpaceBase&lt; Scalar &gt; &gt; &amp;range, const RCP&lt; const VectorSpaceBase&lt; Scalar &gt; &gt; &amp;domain)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initialize</name>
      <anchorfile>classThyra_1_1DefaultZeroLinearOp.html</anchorfile>
      <anchor>a453d9a38e15efa360da2559f8e3bc2e9</anchor>
      <arglist>(const RCP&lt; const VectorSpaceBase&lt; Scalar &gt; &gt; &amp;range, const RCP&lt; const VectorSpaceBase&lt; Scalar &gt; &gt; &amp;domain)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>uninitialize</name>
      <anchorfile>classThyra_1_1DefaultZeroLinearOp.html</anchorfile>
      <anchor>a6b0a10b2c10d1d1a9cc65a18894b2707</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const VectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>range</name>
      <anchorfile>classThyra_1_1DefaultZeroLinearOp.html</anchorfile>
      <anchor>ad7384731cffc151c5dbc06ffa73a869a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const VectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>domain</name>
      <anchorfile>classThyra_1_1DefaultZeroLinearOp.html</anchorfile>
      <anchor>aa2bd3d2842d395f6bd2641e16cef0d8c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const LinearOpBase&lt; Scalar &gt; &gt;</type>
      <name>clone</name>
      <anchorfile>classThyra_1_1DefaultZeroLinearOp.html</anchorfile>
      <anchor>a0c8a3912c261d5fefff0c104485f360b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>bool</type>
      <name>opSupportedImpl</name>
      <anchorfile>classThyra_1_1DefaultZeroLinearOp.html</anchorfile>
      <anchor>a9d51ed17cf8c2c654762a455e8b1df7e</anchor>
      <arglist>(EOpTransp M_trans) const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>applyImpl</name>
      <anchorfile>classThyra_1_1DefaultZeroLinearOp.html</anchorfile>
      <anchor>ac29c267fb4fa7bebe371acd65d206a00</anchor>
      <arglist>(const EOpTransp M_trans, const MultiVectorBase&lt; Scalar &gt; &amp;X, const Ptr&lt; MultiVectorBase&lt; Scalar &gt; &gt; &amp;Y, const Scalar alpha, const Scalar beta) const </arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>description</name>
      <anchorfile>classThyra_1_1DefaultZeroLinearOp.html</anchorfile>
      <anchor>ab95b886fdda3bf745a26cbc3a7cf91ab</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual bool</type>
      <name>rowStatIsSupportedImpl</name>
      <anchorfile>classThyra_1_1DefaultZeroLinearOp.html</anchorfile>
      <anchor>ae01034c1ac04bfe1f080831d65ffa892</anchor>
      <arglist>(const RowStatLinearOpBaseUtils::ERowStat rowStat) const </arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual void</type>
      <name>getRowStatImpl</name>
      <anchorfile>classThyra_1_1DefaultZeroLinearOp.html</anchorfile>
      <anchor>a1b70535a1b8db17b5e0b8826160e0b21</anchor>
      <arglist>(const RowStatLinearOpBaseUtils::ERowStat rowStat, const Teuchos::Ptr&lt; VectorBase&lt; Scalar &gt; &gt; &amp;rowStatVec) const </arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual bool</type>
      <name>supportsScaleLeftImpl</name>
      <anchorfile>classThyra_1_1DefaultZeroLinearOp.html</anchorfile>
      <anchor>a72a84662671f3820f5321f24931e46ea</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual bool</type>
      <name>supportsScaleRightImpl</name>
      <anchorfile>classThyra_1_1DefaultZeroLinearOp.html</anchorfile>
      <anchor>a112d3173ce07b5f4db3e0f13da95bb8c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual void</type>
      <name>scaleLeftImpl</name>
      <anchorfile>classThyra_1_1DefaultZeroLinearOp.html</anchorfile>
      <anchor>a7ec66cc806f82592029ddc367424dbc0</anchor>
      <arglist>(const VectorBase&lt; Scalar &gt; &amp;row_scaling)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual void</type>
      <name>scaleRightImpl</name>
      <anchorfile>classThyra_1_1DefaultZeroLinearOp.html</anchorfile>
      <anchor>ad85ce0ca8cf9fda51783f20b0f00e848</anchor>
      <arglist>(const VectorBase&lt; Scalar &gt; &amp;col_scaling)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::DelayedLinearOpWithSolve</name>
    <filename>classThyra_1_1DelayedLinearOpWithSolve.html</filename>
    <templarg>Scalar</templarg>
    <base virtualness="virtual">Thyra::LinearOpWithSolveBase</base>
    <member kind="function">
      <type>RCP&lt; DelayedLinearOpWithSolve&lt; Scalar &gt; &gt;</type>
      <name>delayedLinearOpWithSolve</name>
      <anchorfile>classThyra_1_1DelayedLinearOpWithSolve.html</anchorfile>
      <anchor>ae1449c9cc53c0b7bd990af7ad949af4c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; DelayedLinearOpWithSolve&lt; Scalar &gt; &gt;</type>
      <name>delayedLinearOpWithSolve</name>
      <anchorfile>classThyra_1_1DelayedLinearOpWithSolve.html</anchorfile>
      <anchor>aaf9862b1f5372a1851e63996b798b034</anchor>
      <arglist>(const RCP&lt; const LinearOpSourceBase&lt; Scalar &gt; &gt; &amp;fwdOpSrc, const RCP&lt; LinearOpWithSolveFactoryBase&lt; Scalar &gt; &gt; &amp;lowsf)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>DelayedLinearOpWithSolve</name>
      <anchorfile>classThyra_1_1DelayedLinearOpWithSolve.html</anchorfile>
      <anchor>af467c321e5340f64ba5c2a2bbc956866</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initialize</name>
      <anchorfile>classThyra_1_1DelayedLinearOpWithSolve.html</anchorfile>
      <anchor>a1340e6cee14ee52fd6fb38d937e01585</anchor>
      <arglist>(const RCP&lt; const LinearOpSourceBase&lt; Scalar &gt; &gt; &amp;fwdOpSrc, const RCP&lt; const PreconditionerBase&lt; Scalar &gt; &gt; &amp;prec, const RCP&lt; const LinearOpSourceBase&lt; Scalar &gt; &gt; &amp;approxFwdOpSrc, const ESupportSolveUse supportSolveUse, const RCP&lt; LinearOpWithSolveFactoryBase&lt; Scalar &gt; &gt; &amp;lowsf)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const LinearOpSourceBase&lt; Scalar &gt; &gt;</type>
      <name>getFwdOpSrc</name>
      <anchorfile>classThyra_1_1DelayedLinearOpWithSolve.html</anchorfile>
      <anchor>a3706fdb8d9cb79cec5ab475bb5879c86</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const PreconditionerBase&lt; Scalar &gt; &gt;</type>
      <name>getPrec</name>
      <anchorfile>classThyra_1_1DelayedLinearOpWithSolve.html</anchorfile>
      <anchor>a8e220e8113515a3f7316b4c4f332b639</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const LinearOpSourceBase&lt; Scalar &gt; &gt;</type>
      <name>getApproxFwdOpSrc</name>
      <anchorfile>classThyra_1_1DelayedLinearOpWithSolve.html</anchorfile>
      <anchor>ae3b7899c416795f2204cb761efac1c79</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>ESupportSolveUse</type>
      <name>getSupportSolveUse</name>
      <anchorfile>classThyra_1_1DelayedLinearOpWithSolve.html</anchorfile>
      <anchor>ac2fefa35d6d784aa4c109574dd688779</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>description</name>
      <anchorfile>classThyra_1_1DelayedLinearOpWithSolve.html</anchorfile>
      <anchor>a3e50469edcf248ae36320b500ed2d7f8</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const VectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>range</name>
      <anchorfile>classThyra_1_1DelayedLinearOpWithSolve.html</anchorfile>
      <anchor>a553c1d0a668463c725ecc479df2a8c7d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const VectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>domain</name>
      <anchorfile>classThyra_1_1DelayedLinearOpWithSolve.html</anchorfile>
      <anchor>a355f146b6679c0f858d86b17f8678f2e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const LinearOpBase&lt; Scalar &gt; &gt;</type>
      <name>clone</name>
      <anchorfile>classThyra_1_1DelayedLinearOpWithSolve.html</anchorfile>
      <anchor>a4286c65cf3cbb5851424fba2bf135de3</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual bool</type>
      <name>opSupportedImpl</name>
      <anchorfile>classThyra_1_1DelayedLinearOpWithSolve.html</anchorfile>
      <anchor>a65f9ce0515402507fbebdc401e49e133</anchor>
      <arglist>(EOpTransp M_trans) const </arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual void</type>
      <name>applyImpl</name>
      <anchorfile>classThyra_1_1DelayedLinearOpWithSolve.html</anchorfile>
      <anchor>af5aa37243bc11e33c13f78f6d6d0412b</anchor>
      <arglist>(const EOpTransp M_trans, const MultiVectorBase&lt; Scalar &gt; &amp;X, const Ptr&lt; MultiVectorBase&lt; Scalar &gt; &gt; &amp;Y, const Scalar alpha, const Scalar beta) const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>informUpdatedVerbosityState</name>
      <anchorfile>classThyra_1_1DelayedLinearOpWithSolve.html</anchorfile>
      <anchor>a86500cd2ae24edd5f4ef5ffc604fcb74</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual bool</type>
      <name>solveSupportsImpl</name>
      <anchorfile>classThyra_1_1DelayedLinearOpWithSolve.html</anchorfile>
      <anchor>a9be360ad433df05e6dc88fc092f0cc2f</anchor>
      <arglist>(EOpTransp M_trans) const </arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual bool</type>
      <name>solveSupportsSolveMeasureTypeImpl</name>
      <anchorfile>classThyra_1_1DelayedLinearOpWithSolve.html</anchorfile>
      <anchor>adcf4dc53439e1be21d21ed4424e6deb5</anchor>
      <arglist>(EOpTransp M_trans, const SolveMeasureType &amp;solveMeasureType) const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>SolveStatus&lt; Scalar &gt;</type>
      <name>solveImpl</name>
      <anchorfile>classThyra_1_1DelayedLinearOpWithSolve.html</anchorfile>
      <anchor>a1ebd5a7d1ab31da0e3a299708882e8d5</anchor>
      <arglist>(const EOpTransp transp, const MultiVectorBase&lt; Scalar &gt; &amp;B, const Ptr&lt; MultiVectorBase&lt; Scalar &gt; &gt; &amp;X, const Ptr&lt; const SolveCriteria&lt; Scalar &gt; &gt; solveCriteria) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::DelayedLinearOpWithSolveFactory</name>
    <filename>classThyra_1_1DelayedLinearOpWithSolveFactory.html</filename>
    <templarg></templarg>
    <base virtualness="virtual">Thyra::LinearOpWithSolveFactoryBase</base>
    <member kind="function">
      <type></type>
      <name>DelayedLinearOpWithSolveFactory</name>
      <anchorfile>classThyra_1_1DelayedLinearOpWithSolveFactory.html</anchorfile>
      <anchor>ac72359a6966f896012c4d81bd7a3f535</anchor>
      <arglist>(const RCP&lt; LinearOpWithSolveFactoryBase&lt; Scalar &gt; &gt; &amp;lowsf)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; LinearOpWithSolveFactoryBase&lt; Scalar &gt; &gt;</type>
      <name>getUnderlyingLOWSF</name>
      <anchorfile>classThyra_1_1DelayedLinearOpWithSolveFactory.html</anchorfile>
      <anchor>ace17291065103c051448434519de5e5f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const LinearOpWithSolveFactoryBase&lt; Scalar &gt; &gt;</type>
      <name>getUnderlyingLOWSF</name>
      <anchorfile>classThyra_1_1DelayedLinearOpWithSolveFactory.html</anchorfile>
      <anchor>a0e0c16c4e4bbf4c019c73388e4148f62</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>description</name>
      <anchorfile>classThyra_1_1DelayedLinearOpWithSolveFactory.html</anchorfile>
      <anchor>ac0ad59a4f424cc0674eaaeebe65e84d5</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setParameterList</name>
      <anchorfile>classThyra_1_1DelayedLinearOpWithSolveFactory.html</anchorfile>
      <anchor>a1724bc12e9f10bc4e82f90127dcd5128</anchor>
      <arglist>(RCP&lt; ParameterList &gt; const &amp;paramList)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; ParameterList &gt;</type>
      <name>getNonconstParameterList</name>
      <anchorfile>classThyra_1_1DelayedLinearOpWithSolveFactory.html</anchorfile>
      <anchor>ad30aee34bc52a691181bbb71bde4770e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; ParameterList &gt;</type>
      <name>unsetParameterList</name>
      <anchorfile>classThyra_1_1DelayedLinearOpWithSolveFactory.html</anchorfile>
      <anchor>a7189bdb4095fd0892266695c338a3caf</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const ParameterList &gt;</type>
      <name>getParameterList</name>
      <anchorfile>classThyra_1_1DelayedLinearOpWithSolveFactory.html</anchorfile>
      <anchor>afac37913acd5cfd6824cb679d52163a3</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const ParameterList &gt;</type>
      <name>getValidParameters</name>
      <anchorfile>classThyra_1_1DelayedLinearOpWithSolveFactory.html</anchorfile>
      <anchor>ac65e0090eb9d3e138f9f0792dddf4d5a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>acceptsPreconditionerFactory</name>
      <anchorfile>classThyra_1_1DelayedLinearOpWithSolveFactory.html</anchorfile>
      <anchor>af0e9e6dc9648b387a0367d3c7ebf8352</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>setPreconditionerFactory</name>
      <anchorfile>classThyra_1_1DelayedLinearOpWithSolveFactory.html</anchorfile>
      <anchor>ae38bdfe17dda592635fab90151be0857</anchor>
      <arglist>(const RCP&lt; PreconditionerFactoryBase&lt; Scalar &gt; &gt; &amp;precFactory, const std::string &amp;precFactoryName)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual RCP&lt; PreconditionerFactoryBase&lt; Scalar &gt; &gt;</type>
      <name>getPreconditionerFactory</name>
      <anchorfile>classThyra_1_1DelayedLinearOpWithSolveFactory.html</anchorfile>
      <anchor>a31d197e1da7b6a16b48d359eeed3b99d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>unsetPreconditionerFactory</name>
      <anchorfile>classThyra_1_1DelayedLinearOpWithSolveFactory.html</anchorfile>
      <anchor>aba7a8e5c6872c74fa90cf4cd0de4503d</anchor>
      <arglist>(RCP&lt; PreconditionerFactoryBase&lt; Scalar &gt; &gt; *precFactory, std::string *precFactoryName)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>isCompatible</name>
      <anchorfile>classThyra_1_1DelayedLinearOpWithSolveFactory.html</anchorfile>
      <anchor>a8bc1713bdd362e4a14b82452f69d0c88</anchor>
      <arglist>(const LinearOpSourceBase&lt; Scalar &gt; &amp;fwdOpSrc) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual RCP&lt; LinearOpWithSolveBase&lt; Scalar &gt; &gt;</type>
      <name>createOp</name>
      <anchorfile>classThyra_1_1DelayedLinearOpWithSolveFactory.html</anchorfile>
      <anchor>a6a55e6f659f86daa3fc9ba57d7e25545</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>initializeOp</name>
      <anchorfile>classThyra_1_1DelayedLinearOpWithSolveFactory.html</anchorfile>
      <anchor>ab70cc9c9c58362db9e547ab671ea48b9</anchor>
      <arglist>(const RCP&lt; const LinearOpSourceBase&lt; Scalar &gt; &gt; &amp;fwdOpSrc, LinearOpWithSolveBase&lt; Scalar &gt; *Op, const ESupportSolveUse supportSolveUse) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>initializeAndReuseOp</name>
      <anchorfile>classThyra_1_1DelayedLinearOpWithSolveFactory.html</anchorfile>
      <anchor>a447b8dc59b13ae006f48bd43a2a61bd9</anchor>
      <arglist>(const RCP&lt; const LinearOpSourceBase&lt; Scalar &gt; &gt; &amp;fwdOpSrc, LinearOpWithSolveBase&lt; Scalar &gt; *Op) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>uninitializeOp</name>
      <anchorfile>classThyra_1_1DelayedLinearOpWithSolveFactory.html</anchorfile>
      <anchor>a95440db4c6e033846389ce066b6f5b64</anchor>
      <arglist>(LinearOpWithSolveBase&lt; Scalar &gt; *Op, RCP&lt; const LinearOpSourceBase&lt; Scalar &gt; &gt; *fwdOpSrc, RCP&lt; const PreconditionerBase&lt; Scalar &gt; &gt; *prec, RCP&lt; const LinearOpSourceBase&lt; Scalar &gt; &gt; *approxFwdOpSrc, ESupportSolveUse *supportSolveUse) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>supportsPreconditionerInputType</name>
      <anchorfile>classThyra_1_1DelayedLinearOpWithSolveFactory.html</anchorfile>
      <anchor>a23d2b4809526d13fab9eb9c1319b0085</anchor>
      <arglist>(const EPreconditionerInputType precOpType) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>initializePreconditionedOp</name>
      <anchorfile>classThyra_1_1DelayedLinearOpWithSolveFactory.html</anchorfile>
      <anchor>ace3efc6b16aa3c40a86f2f12eca5e941</anchor>
      <arglist>(const RCP&lt; const LinearOpSourceBase&lt; Scalar &gt; &gt; &amp;fwdOpSrc, const RCP&lt; const PreconditionerBase&lt; Scalar &gt; &gt; &amp;prec, LinearOpWithSolveBase&lt; Scalar &gt; *Op, const ESupportSolveUse supportSolveUse) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>initializeApproxPreconditionedOp</name>
      <anchorfile>classThyra_1_1DelayedLinearOpWithSolveFactory.html</anchorfile>
      <anchor>a9b1579d1eefeed8806ddfcc70523b22a</anchor>
      <arglist>(const RCP&lt; const LinearOpSourceBase&lt; Scalar &gt; &gt; &amp;fwdOpSrc, const RCP&lt; const LinearOpSourceBase&lt; Scalar &gt; &gt; &amp;approxFwdOpSrc, LinearOpWithSolveBase&lt; Scalar &gt; *Op, const ESupportSolveUse supportSolveUse) const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>informUpdatedVerbosityState</name>
      <anchorfile>classThyra_1_1DelayedLinearOpWithSolveFactory.html</anchorfile>
      <anchor>a69bc36345f178109f486ecf80b10a7d1</anchor>
      <arglist>() const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::ModelEvaluatorBase::Derivative</name>
    <filename>classThyra_1_1ModelEvaluatorBase_1_1Derivative.html</filename>
    <templarg>Scalar</templarg>
    <member kind="function">
      <type></type>
      <name>Derivative</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1Derivative.html</anchorfile>
      <anchor>a31b4198924e87967a23c0b10221c0b61</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Derivative</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1Derivative.html</anchorfile>
      <anchor>ac0c403895bf2cf66b5a1f57b862b7717</anchor>
      <arglist>(const RCP&lt; LinearOpBase&lt; Scalar &gt; &gt; &amp;lo)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Derivative</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1Derivative.html</anchorfile>
      <anchor>a85b2e37443fe0712ad35e0e0213a8e6e</anchor>
      <arglist>(const RCP&lt; MultiVectorBase&lt; Scalar &gt; &gt; &amp;mv, const EDerivativeMultiVectorOrientation orientation=DERIV_MV_BY_COL)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Derivative</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1Derivative.html</anchorfile>
      <anchor>a29d83ce4291f1858504fbe5aae585dc4</anchor>
      <arglist>(const DerivativeMultiVector&lt; Scalar &gt; &amp;dmv)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isEmpty</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1Derivative.html</anchorfile>
      <anchor>afe79b6147f6dda4c32d226b7fd3d7846</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Derivative&lt; Scalar &gt; &amp;</type>
      <name>assert_not_null</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1Derivative.html</anchorfile>
      <anchor>acb42d9e885fd46e39a838413303114be</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; LinearOpBase&lt; Scalar &gt; &gt;</type>
      <name>getLinearOp</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1Derivative.html</anchorfile>
      <anchor>ae625827190949b6636eb070d17718dfa</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; MultiVectorBase&lt; Scalar &gt; &gt;</type>
      <name>getMultiVector</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1Derivative.html</anchorfile>
      <anchor>a13bf14e950c175aa66bf0d58d7a98451</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>EDerivativeMultiVectorOrientation</type>
      <name>getMultiVectorOrientation</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1Derivative.html</anchorfile>
      <anchor>a60be33130ed631db5ece01bfde8109ca</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>DerivativeMultiVector&lt; Scalar &gt;</type>
      <name>getDerivativeMultiVector</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1Derivative.html</anchorfile>
      <anchor>a568e1469f9d5446da95ffda9972814b0</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isSupportedBy</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1Derivative.html</anchorfile>
      <anchor>ac8f1e5d341ea574be6f38820f252f03f</anchor>
      <arglist>(const DerivativeSupport &amp;derivSupport) const </arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>description</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1Derivative.html</anchorfile>
      <anchor>aa67a6ff862ce5312cc3617b978a14fe3</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>describe</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1Derivative.html</anchorfile>
      <anchor>af4cd709c72da7063b345b912c89f8a15</anchor>
      <arglist>(Teuchos::FancyOStream &amp;out, const Teuchos::EVerbosityLevel verbLevel) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::ModelEvaluatorBase::DerivativeMultiVector</name>
    <filename>classThyra_1_1ModelEvaluatorBase_1_1DerivativeMultiVector.html</filename>
    <templarg>Scalar</templarg>
    <member kind="function">
      <type></type>
      <name>DerivativeMultiVector</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1DerivativeMultiVector.html</anchorfile>
      <anchor>a9cb90b04d766c04717ac36c4742f2c41</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>DerivativeMultiVector</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1DerivativeMultiVector.html</anchorfile>
      <anchor>a26060a0df235e5f1c5bc22c1dbcf917d</anchor>
      <arglist>(const RCP&lt; MultiVectorBase&lt; Scalar &gt; &gt; &amp;mv, const EDerivativeMultiVectorOrientation orientation=DERIV_MV_BY_COL)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>changeOrientation</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1DerivativeMultiVector.html</anchorfile>
      <anchor>a36c40e4c8fb6653b113ce34674c05c56</anchor>
      <arglist>(const EDerivativeMultiVectorOrientation orientation)</arglist>
    </member>
    <member kind="function">
      <type>const DerivativeMultiVector&lt; Scalar &gt; &amp;</type>
      <name>assert_not_null</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1DerivativeMultiVector.html</anchorfile>
      <anchor>af8c4bb345b78bd777e0c3e129e9183a2</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; MultiVectorBase&lt; Scalar &gt; &gt;</type>
      <name>getMultiVector</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1DerivativeMultiVector.html</anchorfile>
      <anchor>af63b40699d787bd7a81c605ca3f3a708</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>EDerivativeMultiVectorOrientation</type>
      <name>getOrientation</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1DerivativeMultiVector.html</anchorfile>
      <anchor>a12ebdc6ff4ed76d035d1aed1dea54279</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>description</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1DerivativeMultiVector.html</anchorfile>
      <anchor>a6b739a6825fec14047888899d2c08892</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>describe</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1DerivativeMultiVector.html</anchorfile>
      <anchor>a4455b9d57a8fbb160232ff5632b390de</anchor>
      <arglist>(Teuchos::FancyOStream &amp;out, const Teuchos::EVerbosityLevel verbLevel) const </arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>Thyra::ModelEvaluatorBase::DerivativeProperties</name>
    <filename>structThyra_1_1ModelEvaluatorBase_1_1DerivativeProperties.html</filename>
    <member kind="function">
      <type></type>
      <name>DerivativeProperties</name>
      <anchorfile>structThyra_1_1ModelEvaluatorBase_1_1DerivativeProperties.html</anchorfile>
      <anchor>a1701e9add928015e855fad94ce57ea76</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>DerivativeProperties</name>
      <anchorfile>structThyra_1_1ModelEvaluatorBase_1_1DerivativeProperties.html</anchorfile>
      <anchor>abb961e41930f0735f3c33b5200025925</anchor>
      <arglist>(EDerivativeLinearity in_linearity, ERankStatus in_rank, bool in_supportsAdjoint)</arglist>
    </member>
    <member kind="variable">
      <type>EDerivativeLinearity</type>
      <name>linearity</name>
      <anchorfile>structThyra_1_1ModelEvaluatorBase_1_1DerivativeProperties.html</anchorfile>
      <anchor>a29a7905ffc3de9ce0351b306decdb1f5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>ERankStatus</type>
      <name>rank</name>
      <anchorfile>structThyra_1_1ModelEvaluatorBase_1_1DerivativeProperties.html</anchorfile>
      <anchor>ac1daea93fb7fb3c4ac9a4f2534de7fba</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>supportsAdjoint</name>
      <anchorfile>structThyra_1_1ModelEvaluatorBase_1_1DerivativeProperties.html</anchorfile>
      <anchor>a77c35a68b92dc6a943de619ece231133</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::ModelEvaluatorBase::DerivativeSupport</name>
    <filename>classThyra_1_1ModelEvaluatorBase_1_1DerivativeSupport.html</filename>
    <member kind="function">
      <type></type>
      <name>DerivativeSupport</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1DerivativeSupport.html</anchorfile>
      <anchor>acdd6b43ff97b3281b84013b8c5f2c713</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>DerivativeSupport</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1DerivativeSupport.html</anchorfile>
      <anchor>a00abd6232ae479e38a7edac5681fb488</anchor>
      <arglist>(EDerivativeLinearOp)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>DerivativeSupport</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1DerivativeSupport.html</anchorfile>
      <anchor>a944786c8f3c402f3350fba3a04cc9e62</anchor>
      <arglist>(EDerivativeMultiVectorOrientation mvOrientation)</arglist>
    </member>
    <member kind="function">
      <type>DerivativeSupport &amp;</type>
      <name>plus</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1DerivativeSupport.html</anchorfile>
      <anchor>a3c95d247b118e04c9e66338b4449d172</anchor>
      <arglist>(EDerivativeLinearOp)</arglist>
    </member>
    <member kind="function">
      <type>DerivativeSupport &amp;</type>
      <name>plus</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1DerivativeSupport.html</anchorfile>
      <anchor>a18952db25fae08b083d0e5fd7a7ffbca</anchor>
      <arglist>(EDerivativeMultiVectorOrientation mvOrientation)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>none</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1DerivativeSupport.html</anchorfile>
      <anchor>a4f2a929bb644a722650b07e60e12d73d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>supports</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1DerivativeSupport.html</anchorfile>
      <anchor>a3b43e3f64a4c8da45572178246259899</anchor>
      <arglist>(EDerivativeLinearOp) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>supports</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1DerivativeSupport.html</anchorfile>
      <anchor>afcd863357e0bb00271261f2660706da7</anchor>
      <arglist>(EDerivativeMultiVectorOrientation mvOrientation) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isSameSupport</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1DerivativeSupport.html</anchorfile>
      <anchor>a97c0d02013086240c8284d3ca43560a6</anchor>
      <arglist>(const DerivativeSupport &amp;derivSupport) const </arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>description</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1DerivativeSupport.html</anchorfile>
      <anchor>af5b46f60161efbfa532279a99f60921b</anchor>
      <arglist>() const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::DetachedMultiVectorView</name>
    <filename>classThyra_1_1DetachedMultiVectorView.html</filename>
    <templarg>Scalar</templarg>
    <member kind="function">
      <type></type>
      <name>DetachedMultiVectorView</name>
      <anchorfile>classThyra_1_1DetachedMultiVectorView.html</anchorfile>
      <anchor>ae9b1024d7b9b8f78c978d019c81c16d4</anchor>
      <arglist>(const RCP&lt; MultiVectorBase&lt; Scalar &gt; &gt; &amp;mv, const Range1D &amp;rowRng=Range1D(), const Range1D &amp;colRng=Range1D())</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>DetachedMultiVectorView</name>
      <anchorfile>classThyra_1_1DetachedMultiVectorView.html</anchorfile>
      <anchor>a1d9c87715d19535ec927a01842b32610</anchor>
      <arglist>(MultiVectorBase&lt; Scalar &gt; &amp;mv, const Range1D &amp;rowRng=Range1D(), const Range1D &amp;colRng=Range1D())</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~DetachedMultiVectorView</name>
      <anchorfile>classThyra_1_1DetachedMultiVectorView.html</anchorfile>
      <anchor>a5e6c8ad3bdf1662d8edc75f45e6ad79f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const RTOpPack::SubMultiVectorView&lt; Scalar &gt; &amp;</type>
      <name>smv</name>
      <anchorfile>classThyra_1_1DetachedMultiVectorView.html</anchorfile>
      <anchor>af2ab247809ccfe844658b6ad357e0538</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Ordinal</type>
      <name>globalOffset</name>
      <anchorfile>classThyra_1_1DetachedMultiVectorView.html</anchorfile>
      <anchor>af3043fd08b52190e431dde01b588a41e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Ordinal</type>
      <name>subDim</name>
      <anchorfile>classThyra_1_1DetachedMultiVectorView.html</anchorfile>
      <anchor>a6b756724d4704a77d4fd89439f42a5ea</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Ordinal</type>
      <name>colOffset</name>
      <anchorfile>classThyra_1_1DetachedMultiVectorView.html</anchorfile>
      <anchor>ab456d0a28fc38a7ae8c28a7cafc24d7d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Ordinal</type>
      <name>numSubCols</name>
      <anchorfile>classThyra_1_1DetachedMultiVectorView.html</anchorfile>
      <anchor>a0fc15e6f83592fa4bf392017a05ff685</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Scalar *</type>
      <name>values</name>
      <anchorfile>classThyra_1_1DetachedMultiVectorView.html</anchorfile>
      <anchor>ab3372663c6d22f269461648a96a7304e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Ordinal</type>
      <name>leadingDim</name>
      <anchorfile>classThyra_1_1DetachedMultiVectorView.html</anchorfile>
      <anchor>a8874460cc255fb230af210bb43548453</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Scalar &amp;</type>
      <name>operator()</name>
      <anchorfile>classThyra_1_1DetachedMultiVectorView.html</anchorfile>
      <anchor>a06d45165658d03bf0afabda075391ed2</anchor>
      <arglist>(Ordinal i, Ordinal j)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>doExplicitMultiVectorAdjoint</name>
      <anchorfile>classThyra_1_1DetachedMultiVectorView.html</anchorfile>
      <anchor>aef7d1f7044f8f68fe7ae2b7efddbd2f9</anchor>
      <arglist>(const MultiVectorBase&lt; Scalar &gt; &amp;mvIn, MultiVectorBase&lt; Scalar &gt; *mvTransOut)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::DetachedSpmdVectorView</name>
    <filename>classThyra_1_1DetachedSpmdVectorView.html</filename>
    <templarg>Scalar</templarg>
    <member kind="function">
      <type></type>
      <name>DetachedSpmdVectorView</name>
      <anchorfile>classThyra_1_1DetachedSpmdVectorView.html</anchorfile>
      <anchor>a1155f788297dd291a89f19ccb5d8db76</anchor>
      <arglist>(const Teuchos::RCP&lt; VectorBase&lt; Scalar &gt; &gt; &amp;v)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~DetachedSpmdVectorView</name>
      <anchorfile>classThyra_1_1DetachedSpmdVectorView.html</anchorfile>
      <anchor>ad7ecbb91ce2cfc76ea05e6a52343e2c8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const RCP&lt; const SpmdVectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>spmdSpace</name>
      <anchorfile>classThyra_1_1DetachedSpmdVectorView.html</anchorfile>
      <anchor>ae96c21cb85d2455ede2c480959cebd90</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const RTOpPack::SubVectorView&lt; Scalar &gt; &amp;</type>
      <name>sv</name>
      <anchorfile>classThyra_1_1DetachedSpmdVectorView.html</anchorfile>
      <anchor>a5b4a7d880361402fffd4a7c82cf7996f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos_Ordinal</type>
      <name>globalOffset</name>
      <anchorfile>classThyra_1_1DetachedSpmdVectorView.html</anchorfile>
      <anchor>aac5cf183e31be61538c75753510dcfed</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos_Ordinal</type>
      <name>subDim</name>
      <anchorfile>classThyra_1_1DetachedSpmdVectorView.html</anchorfile>
      <anchor>a54064e380dea18f2f2f2570c56411c57</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const ArrayRCP&lt; const Scalar &gt;</type>
      <name>values</name>
      <anchorfile>classThyra_1_1DetachedSpmdVectorView.html</anchorfile>
      <anchor>a42f56417ff0ba26c3d5d28af922d78d4</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>ptrdiff_t</type>
      <name>stride</name>
      <anchorfile>classThyra_1_1DetachedSpmdVectorView.html</anchorfile>
      <anchor>aade6624be77e35866e87570f456fb2dd</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Scalar &amp;</type>
      <name>operator[]</name>
      <anchorfile>classThyra_1_1DetachedSpmdVectorView.html</anchorfile>
      <anchor>a64a5c256392a411d8195aa711ee3d2ca</anchor>
      <arglist>(Teuchos_Ordinal i) const </arglist>
    </member>
    <member kind="function">
      <type>Scalar &amp;</type>
      <name>operator()</name>
      <anchorfile>classThyra_1_1DetachedSpmdVectorView.html</anchorfile>
      <anchor>a01ebb0e82e796357f255cfa5d8bf62e8</anchor>
      <arglist>(Teuchos_Ordinal i) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::DetachedVectorView</name>
    <filename>classThyra_1_1DetachedVectorView.html</filename>
    <templarg>Scalar</templarg>
    <member kind="function">
      <type></type>
      <name>DetachedVectorView</name>
      <anchorfile>classThyra_1_1DetachedVectorView.html</anchorfile>
      <anchor>aae34a9ea5ddef02cc1e5c00378db7e0c</anchor>
      <arglist>(const Teuchos::RCP&lt; VectorBase&lt; Scalar &gt; &gt; &amp;v, const Range1D &amp;rng=Range1D(), const bool forceUnitStride=false)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>DetachedVectorView</name>
      <anchorfile>classThyra_1_1DetachedVectorView.html</anchorfile>
      <anchor>a88fc8a8c3e4812bd51d1b67dca5592d3</anchor>
      <arglist>(VectorBase&lt; Scalar &gt; &amp;v, const Range1D &amp;rng=Range1D(), const bool forceUnitStride=false)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~DetachedVectorView</name>
      <anchorfile>classThyra_1_1DetachedVectorView.html</anchorfile>
      <anchor>a92dd2440ed36a5f56f959fccf584c4dd</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const RTOpPack::SubVectorView&lt; Scalar &gt; &amp;</type>
      <name>sv</name>
      <anchorfile>classThyra_1_1DetachedVectorView.html</anchorfile>
      <anchor>aad6fa90e97a87ceb3b9311aa9e0e3e47</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos_Ordinal</type>
      <name>globalOffset</name>
      <anchorfile>classThyra_1_1DetachedVectorView.html</anchorfile>
      <anchor>acce7c88263c63b30c2bea0d975e16854</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos_Ordinal</type>
      <name>subDim</name>
      <anchorfile>classThyra_1_1DetachedVectorView.html</anchorfile>
      <anchor>a342ab2afac5659e5e6c945c940d5afff</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Scalar *</type>
      <name>values</name>
      <anchorfile>classThyra_1_1DetachedVectorView.html</anchorfile>
      <anchor>a1bec08a6fc8bb745d8d266368ea43a74</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>ptrdiff_t</type>
      <name>stride</name>
      <anchorfile>classThyra_1_1DetachedVectorView.html</anchorfile>
      <anchor>a11ffe4e8222377fcec4f87f2b0a0a2a0</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Scalar &amp;</type>
      <name>operator[]</name>
      <anchorfile>classThyra_1_1DetachedVectorView.html</anchorfile>
      <anchor>a2f95a0ef2a3bb1a017fef4aca55ab4cc</anchor>
      <arglist>(Teuchos_Ordinal i) const </arglist>
    </member>
    <member kind="function">
      <type>Scalar &amp;</type>
      <name>operator()</name>
      <anchorfile>classThyra_1_1DetachedVectorView.html</anchorfile>
      <anchor>a2945acebee9aed22d491bde6ce7bcd61</anchor>
      <arglist>(Teuchos_Ordinal i) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::DiagonalEpetraLinearOpWithSolveFactory</name>
    <filename>classThyra_1_1DiagonalEpetraLinearOpWithSolveFactory.html</filename>
    <base>LinearOpWithSolveFactoryBase&lt; double &gt;</base>
    <member kind="function">
      <type>bool</type>
      <name>isCompatible</name>
      <anchorfile>classThyra_1_1DiagonalEpetraLinearOpWithSolveFactory.html</anchorfile>
      <anchor>a0f8abdfaeb82abe78574f21a3c28d25f</anchor>
      <arglist>(const LinearOpSourceBase&lt; double &gt; &amp;fwdOpSrc) const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; LinearOpWithSolveBase&lt; double &gt; &gt;</type>
      <name>createOp</name>
      <anchorfile>classThyra_1_1DiagonalEpetraLinearOpWithSolveFactory.html</anchorfile>
      <anchor>a2559d16980bc72c44404c9280a7a9a16</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initializeOp</name>
      <anchorfile>classThyra_1_1DiagonalEpetraLinearOpWithSolveFactory.html</anchorfile>
      <anchor>a1b90a7f96edf75f2578085b9d9e9c2bc</anchor>
      <arglist>(const Teuchos::RCP&lt; const LinearOpSourceBase&lt; double &gt; &gt; &amp;fwdOpSrc, LinearOpWithSolveBase&lt; double &gt; *Op, const ESupportSolveUse supportSolveUse) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>uninitializeOp</name>
      <anchorfile>classThyra_1_1DiagonalEpetraLinearOpWithSolveFactory.html</anchorfile>
      <anchor>ab43d9ab71eeb0ea5109b65304d599190</anchor>
      <arglist>(LinearOpWithSolveBase&lt; double &gt; *Op, Teuchos::RCP&lt; const LinearOpSourceBase&lt; double &gt; &gt; *fwdOpSrc, Teuchos::RCP&lt; const PreconditionerBase&lt; double &gt; &gt; *prec, Teuchos::RCP&lt; const LinearOpSourceBase&lt; double &gt; &gt; *approxFwdOpSrc, ESupportSolveUse *supportSolveUse) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setParameterList</name>
      <anchorfile>classThyra_1_1DiagonalEpetraLinearOpWithSolveFactory.html</anchorfile>
      <anchor>a3a9d6a0477789a42546005dc3252a711</anchor>
      <arglist>(Teuchos::RCP&lt; Teuchos::ParameterList &gt; const &amp;paramList)</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; Teuchos::ParameterList &gt;</type>
      <name>getNonconstParameterList</name>
      <anchorfile>classThyra_1_1DiagonalEpetraLinearOpWithSolveFactory.html</anchorfile>
      <anchor>a1f4a75fe9c2a1adbe826a7b9efd7d6e4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; Teuchos::ParameterList &gt;</type>
      <name>unsetParameterList</name>
      <anchorfile>classThyra_1_1DiagonalEpetraLinearOpWithSolveFactory.html</anchorfile>
      <anchor>afcb553a7051105d9839ba957bf72b250</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Teuchos::ParameterList &gt;</type>
      <name>getParameterList</name>
      <anchorfile>classThyra_1_1DiagonalEpetraLinearOpWithSolveFactory.html</anchorfile>
      <anchor>a09bde1b7cc4581433dfbca20eeeceb38</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Teuchos::ParameterList &gt;</type>
      <name>getValidParameters</name>
      <anchorfile>classThyra_1_1DiagonalEpetraLinearOpWithSolveFactory.html</anchorfile>
      <anchor>a4a7b0241c30d7e7475d870904d68cb2c</anchor>
      <arglist>() const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::DiagonalLinearOpBase</name>
    <filename>classThyra_1_1DiagonalLinearOpBase.html</filename>
    <templarg></templarg>
    <base virtualness="virtual">Thyra::LinearOpBase</base>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>isDiagConst</name>
      <anchorfile>classThyra_1_1DiagonalLinearOpBase.html</anchorfile>
      <anchor>a37d5811330164fe707514640a2e61f33</anchor>
      <arglist>() const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual Teuchos::RCP&lt; VectorBase&lt; Scalar &gt; &gt;</type>
      <name>getNonconstDiag</name>
      <anchorfile>classThyra_1_1DiagonalLinearOpBase.html</anchorfile>
      <anchor>a3514b37a7b21cdbc49e18988594790eb</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual Teuchos::RCP&lt; const VectorBase&lt; Scalar &gt; &gt;</type>
      <name>getDiag</name>
      <anchorfile>classThyra_1_1DiagonalLinearOpBase.html</anchorfile>
      <anchor>a98d9557b3ea4a70c58f642333ba9bc33</anchor>
      <arglist>() const  =0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::DiagonalQuadraticResponseOnlyModelEvaluator</name>
    <filename>classThyra_1_1DiagonalQuadraticResponseOnlyModelEvaluator.html</filename>
    <templarg></templarg>
    <base>Thyra::ResponseOnlyModelEvaluatorBase</base>
    <member kind="function">
      <type></type>
      <name>DiagonalQuadraticResponseOnlyModelEvaluator</name>
      <anchorfile>classThyra_1_1DiagonalQuadraticResponseOnlyModelEvaluator.html</anchorfile>
      <anchor>a7679ed791285fbc840beb3c2bd6a7eb1</anchor>
      <arglist>(const int localDim, const RCP&lt; const Teuchos::Comm&lt; Ordinal &gt; &gt; &amp;comm=Teuchos::null)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setSolutionVector</name>
      <anchorfile>classThyra_1_1DiagonalQuadraticResponseOnlyModelEvaluator.html</anchorfile>
      <anchor>a258f8e470de200dcdcd17ad73f321519</anchor>
      <arglist>(const RCP&lt; const VectorBase&lt; Scalar &gt; &gt; &amp;ps)</arglist>
    </member>
    <member kind="function">
      <type>const RCP&lt; const VectorBase&lt; Scalar &gt; &gt;</type>
      <name>getSolutionVector</name>
      <anchorfile>classThyra_1_1DiagonalQuadraticResponseOnlyModelEvaluator.html</anchorfile>
      <anchor>a579b18b4863e6c433ab586deaed495c2</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setDiagonalVector</name>
      <anchorfile>classThyra_1_1DiagonalQuadraticResponseOnlyModelEvaluator.html</anchorfile>
      <anchor>a143db46e8d3d975f65c20e6eeb0d474d</anchor>
      <arglist>(const RCP&lt; const VectorBase&lt; Scalar &gt; &gt; &amp;diag)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setDiagonalBarVector</name>
      <anchorfile>classThyra_1_1DiagonalQuadraticResponseOnlyModelEvaluator.html</anchorfile>
      <anchor>ad0c823174ed82e972f7a7163fa80c807</anchor>
      <arglist>(const RCP&lt; const VectorBase&lt; Scalar &gt; &gt; &amp;diag_bar)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setNonlinearTermFactor</name>
      <anchorfile>classThyra_1_1DiagonalQuadraticResponseOnlyModelEvaluator.html</anchorfile>
      <anchor>a6fb7f619520ede492e7c07269f25b0be</anchor>
      <arglist>(const Scalar &amp;nonlinearTermFactor)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setScalarOffset</name>
      <anchorfile>classThyra_1_1DiagonalQuadraticResponseOnlyModelEvaluator.html</anchorfile>
      <anchor>a5d25e3733febb8dfbc7ada8f04517bab</anchor>
      <arglist>(const Scalar &amp;g_offset)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Np</name>
      <anchorfile>classThyra_1_1DiagonalQuadraticResponseOnlyModelEvaluator.html</anchorfile>
      <anchor>aed8f029606aa6b44e64d16b2f524ff2d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Ng</name>
      <anchorfile>classThyra_1_1DiagonalQuadraticResponseOnlyModelEvaluator.html</anchorfile>
      <anchor>af37b3422f1d93a418c19e7a675dc9a39</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const VectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>get_p_space</name>
      <anchorfile>classThyra_1_1DiagonalQuadraticResponseOnlyModelEvaluator.html</anchorfile>
      <anchor>a7bcbba736704372f6d61dd535535a7b6</anchor>
      <arglist>(int l) const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const VectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>get_g_space</name>
      <anchorfile>classThyra_1_1DiagonalQuadraticResponseOnlyModelEvaluator.html</anchorfile>
      <anchor>a15a61a049fcdab969ac55e446781cac3</anchor>
      <arglist>(int j) const </arglist>
    </member>
    <member kind="function">
      <type>ModelEvaluatorBase::InArgs&lt; Scalar &gt;</type>
      <name>createInArgs</name>
      <anchorfile>classThyra_1_1DiagonalQuadraticResponseOnlyModelEvaluator.html</anchorfile>
      <anchor>a4e95fb681a5034f282eb952b31d20158</anchor>
      <arglist>() const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::DiagonalScalarProd</name>
    <filename>classThyra_1_1DiagonalScalarProd.html</filename>
    <templarg></templarg>
    <base>Thyra::ScalarProdBase</base>
    <member kind="function">
      <type>RCP&lt; DiagonalScalarProd&lt; Scalar &gt; &gt;</type>
      <name>diagonalScalarProd</name>
      <anchorfile>classThyra_1_1DiagonalScalarProd.html</anchorfile>
      <anchor>a5380f6dbe2505ac7612d3006314bcc28</anchor>
      <arglist>(const RCP&lt; const VectorBase&lt; Scalar &gt; &gt; &amp;s_diag)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>DiagonalScalarProd</name>
      <anchorfile>classThyra_1_1DiagonalScalarProd.html</anchorfile>
      <anchor>a73d4240672c5cf4111005da3d8a3bf55</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initialize</name>
      <anchorfile>classThyra_1_1DiagonalScalarProd.html</anchorfile>
      <anchor>a842a6460efb498568659af3482fe5cc4</anchor>
      <arglist>(const RCP&lt; const VectorBase&lt; Scalar &gt; &gt; &amp;s_diag)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual bool</type>
      <name>isEuclideanImpl</name>
      <anchorfile>classThyra_1_1DiagonalScalarProd.html</anchorfile>
      <anchor>a18cbae50196a7a3d207312f31debd4e9</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual void</type>
      <name>scalarProdsImpl</name>
      <anchorfile>classThyra_1_1DiagonalScalarProd.html</anchorfile>
      <anchor>af2c8088c18d31bf0dfa0a1d9f9c71f2e</anchor>
      <arglist>(const MultiVectorBase&lt; Scalar &gt; &amp;X, const MultiVectorBase&lt; Scalar &gt; &amp;Y, const ArrayView&lt; Scalar &gt; &amp;scalarProds_out) const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>RCP&lt; const LinearOpBase&lt; Scalar &gt; &gt;</type>
      <name>getLinearOpImpl</name>
      <anchorfile>classThyra_1_1DiagonalScalarProd.html</anchorfile>
      <anchor>a7e1180d97e31b85da1fd9b3768cea7a0</anchor>
      <arglist>() const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::DirectionalFiniteDiffCalculator</name>
    <filename>classThyra_1_1DirectionalFiniteDiffCalculator.html</filename>
    <templarg></templarg>
    <base>VerboseObject&lt; DirectionalFiniteDiffCalculator&lt; Scalar &gt; &gt;</base>
    <base>Teuchos::ParameterListAcceptor</base>
    <member kind="function">
      <type>RCP&lt; DirectionalFiniteDiffCalculator&lt; Scalar &gt; &gt;</type>
      <name>directionalFiniteDiffCalculator</name>
      <anchorfile>classThyra_1_1DirectionalFiniteDiffCalculator.html</anchorfile>
      <anchor>a88183bb11b0dac3d0491f1ffb6384648</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; DirectionalFiniteDiffCalculator&lt; Scalar &gt; &gt;</type>
      <name>directionalFiniteDiffCalculator</name>
      <anchorfile>classThyra_1_1DirectionalFiniteDiffCalculator.html</anchorfile>
      <anchor>ae10329d82db6863095fcb26c468369d5</anchor>
      <arglist>(const RCP&lt; ParameterList &gt; &amp;paramList)</arglist>
    </member>
    <member kind="typedef">
      <type>ScalarTraits&lt; Scalar &gt;</type>
      <name>ST</name>
      <anchorfile>classThyra_1_1DirectionalFiniteDiffCalculator.html</anchorfile>
      <anchor>a1a2427d94bb5ac70f136a920d6731b2e</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>ST::magnitudeType</type>
      <name>ScalarMag</name>
      <anchorfile>classThyra_1_1DirectionalFiniteDiffCalculator.html</anchorfile>
      <anchor>a77027983054ea56e1e43449b259fc1ab</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>ScalarTraits&lt; ScalarMag &gt;</type>
      <name>SMT</name>
      <anchorfile>classThyra_1_1DirectionalFiniteDiffCalculator.html</anchorfile>
      <anchor>aaa1a2833776cb8397c0175cfead20ba5</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>DirectionalFiniteDiffCalculatorTypes::EFDMethodType</type>
      <name>EFDMethodType</name>
      <anchorfile>classThyra_1_1DirectionalFiniteDiffCalculator.html</anchorfile>
      <anchor>af9951f9cb5003ab66b0fea2e92c9b23b</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>DirectionalFiniteDiffCalculatorTypes::EFDStepSelectType</type>
      <name>EFDStepSelectType</name>
      <anchorfile>classThyra_1_1DirectionalFiniteDiffCalculator.html</anchorfile>
      <anchor>a39224ec15f3d93d9735fd72e559f5e79</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>DirectionalFiniteDiffCalculatorTypes::SelectedDerivatives</type>
      <name>SelectedDerivatives</name>
      <anchorfile>classThyra_1_1DirectionalFiniteDiffCalculator.html</anchorfile>
      <anchor>a8ff2c5b7d7a4c9062c6772fcb7e6baad</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classThyra_1_1DirectionalFiniteDiffCalculator.html</anchorfile>
      <anchor>a7514b1164d4bffd7fef4ed61ffad113e</anchor>
      <arglist>(EFDMethodType, fd_method_type)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classThyra_1_1DirectionalFiniteDiffCalculator.html</anchorfile>
      <anchor>a6f966b2c98d28fedbe8f1cdf9b03092d</anchor>
      <arglist>(EFDStepSelectType, fd_step_select_type)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classThyra_1_1DirectionalFiniteDiffCalculator.html</anchorfile>
      <anchor>a007e99f33e3c3dcefcef81f1f8b7c35a</anchor>
      <arglist>(ScalarMag, fd_step_size)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classThyra_1_1DirectionalFiniteDiffCalculator.html</anchorfile>
      <anchor>ace4488d5d739513b4505073ebf1cfefc</anchor>
      <arglist>(ScalarMag, fd_step_size_min)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>DirectionalFiniteDiffCalculator</name>
      <anchorfile>classThyra_1_1DirectionalFiniteDiffCalculator.html</anchorfile>
      <anchor>a8dfbb4616512526492bd885b17a39344</anchor>
      <arglist>(EFDMethodType fd_method_type=DirectionalFiniteDiffCalculatorTypes::FD_ORDER_FOUR_AUTO, EFDStepSelectType fd_step_select_type=DirectionalFiniteDiffCalculatorTypes::FD_STEP_ABSOLUTE, ScalarMag fd_step_size=-1.0, ScalarMag fd_step_size_min=-1.0)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setParameterList</name>
      <anchorfile>classThyra_1_1DirectionalFiniteDiffCalculator.html</anchorfile>
      <anchor>a1e67dfbb9ac7dab98c68200f38de00a9</anchor>
      <arglist>(RCP&lt; ParameterList &gt; const &amp;paramList)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; ParameterList &gt;</type>
      <name>getNonconstParameterList</name>
      <anchorfile>classThyra_1_1DirectionalFiniteDiffCalculator.html</anchorfile>
      <anchor>a4a549869d35d4f47222e8e2e3087cbbb</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; ParameterList &gt;</type>
      <name>unsetParameterList</name>
      <anchorfile>classThyra_1_1DirectionalFiniteDiffCalculator.html</anchorfile>
      <anchor>a52d4a37e349d2be847b7795dd9b7d39a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const ParameterList &gt;</type>
      <name>getParameterList</name>
      <anchorfile>classThyra_1_1DirectionalFiniteDiffCalculator.html</anchorfile>
      <anchor>a3c21bb07f6f45ce575716ce20bde1387</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const ParameterList &gt;</type>
      <name>getValidParameters</name>
      <anchorfile>classThyra_1_1DirectionalFiniteDiffCalculator.html</anchorfile>
      <anchor>ac4015cc4ebf1b4b4db550345c67c996c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>ModelEvaluatorBase::OutArgs&lt; Scalar &gt;</type>
      <name>createOutArgs</name>
      <anchorfile>classThyra_1_1DirectionalFiniteDiffCalculator.html</anchorfile>
      <anchor>a2af6601fb6569ec0e2085005e063f524</anchor>
      <arglist>(const ModelEvaluator&lt; Scalar &gt; &amp;model, const SelectedDerivatives &amp;fdDerivatives)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>calcVariations</name>
      <anchorfile>classThyra_1_1DirectionalFiniteDiffCalculator.html</anchorfile>
      <anchor>af83071e010e8e8b26a92de8caa91b6d9</anchor>
      <arglist>(const ModelEvaluator&lt; Scalar &gt; &amp;model, const ModelEvaluatorBase::InArgs&lt; Scalar &gt; &amp;basePoint, const ModelEvaluatorBase::InArgs&lt; Scalar &gt; &amp;directions, const ModelEvaluatorBase::OutArgs&lt; Scalar &gt; &amp;baseFunctionValues, const ModelEvaluatorBase::OutArgs&lt; Scalar &gt; &amp;variations) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>calcDerivatives</name>
      <anchorfile>classThyra_1_1DirectionalFiniteDiffCalculator.html</anchorfile>
      <anchor>a73af2d71e43cc30ed95e5ef9fbf72916</anchor>
      <arglist>(const ModelEvaluator&lt; Scalar &gt; &amp;model, const ModelEvaluatorBase::InArgs&lt; Scalar &gt; &amp;basePoint, const ModelEvaluatorBase::OutArgs&lt; Scalar &gt; &amp;baseFunctionValues, const ModelEvaluatorBase::OutArgs&lt; Scalar &gt; &amp;derivatives) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::DummyTestModelEvaluator</name>
    <filename>classThyra_1_1DummyTestModelEvaluator.html</filename>
    <templarg></templarg>
    <base>Thyra::ModelEvaluatorDefaultBase</base>
    <member kind="function">
      <type>RCP&lt; DummyTestModelEvaluator&lt; Scalar &gt; &gt;</type>
      <name>dummyTestModelEvaluator</name>
      <anchorfile>classThyra_1_1DummyTestModelEvaluator.html</anchorfile>
      <anchor>a3c57e34ca02cd2cb5615d89196712a5f</anchor>
      <arglist>(const Ordinal x_size=2, const ArrayView&lt; const Ordinal &gt; &amp;p_sizes=Teuchos::null, const ArrayView&lt; const Ordinal &gt; &amp;g_sizes=Teuchos::null)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>DummyTestModelEvaluator</name>
      <anchorfile>classThyra_1_1DummyTestModelEvaluator.html</anchorfile>
      <anchor>aac761c792331b43c48e8baf97d511b21</anchor>
      <arglist>(const Ordinal x_size, const ArrayView&lt; const Ordinal &gt; &amp;p_sizes, const ArrayView&lt; const Ordinal &gt; &amp;g_sizes)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const VectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>get_x_space</name>
      <anchorfile>classThyra_1_1DummyTestModelEvaluator.html</anchorfile>
      <anchor>a06d54075e447fa84113ebef9222a8aad</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const VectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>get_p_space</name>
      <anchorfile>classThyra_1_1DummyTestModelEvaluator.html</anchorfile>
      <anchor>a96cc7f05618fb4eecdb018800e78afc3</anchor>
      <arglist>(int l) const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const Teuchos::Array&lt; std::string &gt; &gt;</type>
      <name>get_p_names</name>
      <anchorfile>classThyra_1_1DummyTestModelEvaluator.html</anchorfile>
      <anchor>aa16204919da7b9b93185ab86a581b93b</anchor>
      <arglist>(int l) const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const VectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>get_f_space</name>
      <anchorfile>classThyra_1_1DummyTestModelEvaluator.html</anchorfile>
      <anchor>ada9aad47d44c01cc8ff9c9b854f327bd</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const VectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>get_g_space</name>
      <anchorfile>classThyra_1_1DummyTestModelEvaluator.html</anchorfile>
      <anchor>ab374d0673c6052311030a7f7421e5fe5</anchor>
      <arglist>(int j) const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::ArrayView&lt; const std::string &gt;</type>
      <name>get_g_names</name>
      <anchorfile>classThyra_1_1DummyTestModelEvaluator.html</anchorfile>
      <anchor>a2b090271439e2d2e2bc4824981957692</anchor>
      <arglist>(int j) const </arglist>
    </member>
    <member kind="function">
      <type>ModelEvaluatorBase::InArgs&lt; Scalar &gt;</type>
      <name>getNominalValues</name>
      <anchorfile>classThyra_1_1DummyTestModelEvaluator.html</anchorfile>
      <anchor>a35a25db0b73e007d3fca3c717f6c10d4</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>ModelEvaluatorBase::InArgs&lt; Scalar &gt;</type>
      <name>getLowerBounds</name>
      <anchorfile>classThyra_1_1DummyTestModelEvaluator.html</anchorfile>
      <anchor>a25c39470b52006467b3a2b7cbd6aa425</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>ModelEvaluatorBase::InArgs&lt; Scalar &gt;</type>
      <name>getUpperBounds</name>
      <anchorfile>classThyra_1_1DummyTestModelEvaluator.html</anchorfile>
      <anchor>a17515dd7c86329b1449848fef2ac10d3</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; LinearOpBase&lt; Scalar &gt; &gt;</type>
      <name>create_W_op</name>
      <anchorfile>classThyra_1_1DummyTestModelEvaluator.html</anchorfile>
      <anchor>a0f8dd86cf9053d5f20b86599ce6564b8</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; PreconditionerBase&lt; Scalar &gt; &gt;</type>
      <name>create_W_prec</name>
      <anchorfile>classThyra_1_1DummyTestModelEvaluator.html</anchorfile>
      <anchor>a1f4f0ec19f9ed96abd31aefedd76acdf</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const LinearOpWithSolveFactoryBase&lt; Scalar &gt; &gt;</type>
      <name>get_W_factory</name>
      <anchorfile>classThyra_1_1DummyTestModelEvaluator.html</anchorfile>
      <anchor>a9c04d222e43f38a9b95672fe8ee9dc00</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>ModelEvaluatorBase::InArgs&lt; Scalar &gt;</type>
      <name>createInArgs</name>
      <anchorfile>classThyra_1_1DummyTestModelEvaluator.html</anchorfile>
      <anchor>aaf71221b0e5ac33eb64bdd6053cabf8c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>reportFinalPoint</name>
      <anchorfile>classThyra_1_1DummyTestModelEvaluator.html</anchorfile>
      <anchor>ad9fc4ac22e07a1bf1c08bef53b5ca024</anchor>
      <arglist>(const ModelEvaluatorBase::InArgs&lt; Scalar &gt; &amp;finalPoint, const bool wasSolved)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::EpetraExtAddTransformer</name>
    <filename>classThyra_1_1EpetraExtAddTransformer.html</filename>
    <base>LinearOpTransformerBase&lt; double &gt;</base>
    <member kind="function">
      <type>RCP&lt; EpetraExtAddTransformer &gt;</type>
      <name>epetraExtAddTransformer</name>
      <anchorfile>classThyra_1_1EpetraExtAddTransformer.html</anchorfile>
      <anchor>a80962fb6df1e519baa11044487c6d53f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>isCompatible</name>
      <anchorfile>classThyra_1_1EpetraExtAddTransformer.html</anchorfile>
      <anchor>a5fbe6904549c0d1d1d835a1072f8c477</anchor>
      <arglist>(const LinearOpBase&lt; double &gt; &amp;op_in) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual RCP&lt; LinearOpBase&lt; double &gt; &gt;</type>
      <name>createOutputOp</name>
      <anchorfile>classThyra_1_1EpetraExtAddTransformer.html</anchorfile>
      <anchor>ac5ac0d132d273a15b0ead2e90823d86e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>transform</name>
      <anchorfile>classThyra_1_1EpetraExtAddTransformer.html</anchorfile>
      <anchor>a5284157407a4050fc6f1f4eb96d52c99</anchor>
      <arglist>(const LinearOpBase&lt; double &gt; &amp;op_in, const Ptr&lt; LinearOpBase&lt; double &gt; &gt; &amp;op_inout) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::EpetraExtDiagScaledMatProdTransformer</name>
    <filename>classThyra_1_1EpetraExtDiagScaledMatProdTransformer.html</filename>
    <base>LinearOpTransformerBase&lt; double &gt;</base>
    <member kind="function">
      <type>RCP&lt; EpetraExtDiagScaledMatProdTransformer &gt;</type>
      <name>epetraExtDiagScaledMatProdTransformer</name>
      <anchorfile>classThyra_1_1EpetraExtDiagScaledMatProdTransformer.html</anchorfile>
      <anchor>a65dd3e03e5b15543924f50c2d1c46cdd</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>isCompatible</name>
      <anchorfile>classThyra_1_1EpetraExtDiagScaledMatProdTransformer.html</anchorfile>
      <anchor>a69e2b792abde7cae7eeb0dba8fc9d639</anchor>
      <arglist>(const LinearOpBase&lt; double &gt; &amp;op_in) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual RCP&lt; LinearOpBase&lt; double &gt; &gt;</type>
      <name>createOutputOp</name>
      <anchorfile>classThyra_1_1EpetraExtDiagScaledMatProdTransformer.html</anchorfile>
      <anchor>ab4ba95d2ae954429adda14bb9e67a2ac</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>transform</name>
      <anchorfile>classThyra_1_1EpetraExtDiagScaledMatProdTransformer.html</anchorfile>
      <anchor>a80801bd7603b3350b354677feb929142</anchor>
      <arglist>(const LinearOpBase&lt; double &gt; &amp;op_in, const Ptr&lt; LinearOpBase&lt; double &gt; &gt; &amp;op_inout) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::EpetraExtDiagScalingTransformer</name>
    <filename>classThyra_1_1EpetraExtDiagScalingTransformer.html</filename>
    <base>LinearOpTransformerBase&lt; double &gt;</base>
    <member kind="function">
      <type>RCP&lt; EpetraExtDiagScalingTransformer &gt;</type>
      <name>epetraExtDiagScalingTransformer</name>
      <anchorfile>classThyra_1_1EpetraExtDiagScalingTransformer.html</anchorfile>
      <anchor>a7881dfd32f3f6fd58ad4786b18f9abcf</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>isCompatible</name>
      <anchorfile>classThyra_1_1EpetraExtDiagScalingTransformer.html</anchorfile>
      <anchor>a27fa41a13fbfe55feb550a8aaec48597</anchor>
      <arglist>(const LinearOpBase&lt; double &gt; &amp;op_in) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual RCP&lt; LinearOpBase&lt; double &gt; &gt;</type>
      <name>createOutputOp</name>
      <anchorfile>classThyra_1_1EpetraExtDiagScalingTransformer.html</anchorfile>
      <anchor>a15422839b7283b0bfa8e620898e0d760</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>transform</name>
      <anchorfile>classThyra_1_1EpetraExtDiagScalingTransformer.html</anchorfile>
      <anchor>aee109219260fb4d12d46c1352b3c2c7d</anchor>
      <arglist>(const LinearOpBase&lt; double &gt; &amp;op_in, const Ptr&lt; LinearOpBase&lt; double &gt; &gt; &amp;op_inout) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::EpetraLinearOp</name>
    <filename>classThyra_1_1EpetraLinearOp.html</filename>
    <base virtualness="virtual">LinearOpBase&lt; double &gt;</base>
    <base virtualness="virtual">ScaledLinearOpBase&lt; double &gt;</base>
    <base virtualness="virtual">RowStatLinearOpBase&lt; double &gt;</base>
    <base virtualness="virtual">Thyra::EpetraLinearOpBase</base>
    <member kind="function">
      <type>RCP&lt; EpetraLinearOp &gt;</type>
      <name>nonconstEpetraLinearOp</name>
      <anchorfile>classThyra_1_1EpetraLinearOp.html</anchorfile>
      <anchor>a1cc2351f854146bb26d3aaf521445add</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; EpetraLinearOp &gt;</type>
      <name>partialNonconstEpetraLinearOp</name>
      <anchorfile>classThyra_1_1EpetraLinearOp.html</anchorfile>
      <anchor>a1be31cc5b9b681f74273d27d0f4d0041</anchor>
      <arglist>(const RCP&lt; const VectorSpaceBase&lt; double &gt; &gt; &amp;range, const RCP&lt; const VectorSpaceBase&lt; double &gt; &gt; &amp;domain, const RCP&lt; Epetra_Operator &gt; &amp;op, EOpTransp opTrans=NOTRANS, EApplyEpetraOpAs applyAs=EPETRA_OP_APPLY_APPLY, EAdjointEpetraOp adjointSupport=EPETRA_OP_ADJOINT_SUPPORTED)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; EpetraLinearOp &gt;</type>
      <name>nonconstEpetraLinearOp</name>
      <anchorfile>classThyra_1_1EpetraLinearOp.html</anchorfile>
      <anchor>ac0cd940bbdfdf6c8f17305f21b0647ec</anchor>
      <arglist>(const RCP&lt; Epetra_Operator &gt; &amp;op, EOpTransp opTrans=NOTRANS, EApplyEpetraOpAs applyAs=EPETRA_OP_APPLY_APPLY, EAdjointEpetraOp adjointSupport=EPETRA_OP_ADJOINT_SUPPORTED, const RCP&lt; const VectorSpaceBase&lt; double &gt; &gt; &amp;range=Teuchos::null, const RCP&lt; const VectorSpaceBase&lt; double &gt; &gt; &amp;domain=Teuchos::null)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const EpetraLinearOp &gt;</type>
      <name>epetraLinearOp</name>
      <anchorfile>classThyra_1_1EpetraLinearOp.html</anchorfile>
      <anchor>a92e973af4751c968e07d525f1efb54e6</anchor>
      <arglist>(const RCP&lt; const Epetra_Operator &gt; &amp;op, EOpTransp opTrans=NOTRANS, EApplyEpetraOpAs applyAs=EPETRA_OP_APPLY_APPLY, EAdjointEpetraOp adjointSupport=EPETRA_OP_ADJOINT_SUPPORTED, const RCP&lt; const VectorSpaceBase&lt; double &gt; &gt; &amp;range=Teuchos::null, const RCP&lt; const VectorSpaceBase&lt; double &gt; &gt; &amp;domain=Teuchos::null)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; EpetraLinearOp &gt;</type>
      <name>nonconstEpetraLinearOp</name>
      <anchorfile>classThyra_1_1EpetraLinearOp.html</anchorfile>
      <anchor>a94583c212fc909519e9d6c70defc3a2f</anchor>
      <arglist>(const RCP&lt; Epetra_Operator &gt; &amp;op, const std::string &amp;label, EOpTransp opTrans=NOTRANS, EApplyEpetraOpAs applyAs=EPETRA_OP_APPLY_APPLY, EAdjointEpetraOp adjointSupport=EPETRA_OP_ADJOINT_SUPPORTED, const RCP&lt; const VectorSpaceBase&lt; double &gt; &gt; &amp;range=Teuchos::null, const RCP&lt; const VectorSpaceBase&lt; double &gt; &gt; &amp;domain=Teuchos::null)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const EpetraLinearOp &gt;</type>
      <name>epetraLinearOp</name>
      <anchorfile>classThyra_1_1EpetraLinearOp.html</anchorfile>
      <anchor>ae1d047fffe8e482b659604b4baa8ea9b</anchor>
      <arglist>(const RCP&lt; const Epetra_Operator &gt; &amp;op, const std::string &amp;label, EOpTransp opTrans=NOTRANS, EApplyEpetraOpAs applyAs=EPETRA_OP_APPLY_APPLY, EAdjointEpetraOp adjointSupport=EPETRA_OP_ADJOINT_SUPPORTED, const RCP&lt; const SpmdVectorSpaceBase&lt; double &gt; &gt; &amp;range=Teuchos::null, const RCP&lt; const SpmdVectorSpaceBase&lt; double &gt; &gt; &amp;domain=Teuchos::null)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>EpetraLinearOp</name>
      <anchorfile>classThyra_1_1EpetraLinearOp.html</anchorfile>
      <anchor>a679cc6b69cb4b67697a056e70ef9cc91</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initialize</name>
      <anchorfile>classThyra_1_1EpetraLinearOp.html</anchorfile>
      <anchor>ac1f14477f23b9be8dd3149a14869f2ae</anchor>
      <arglist>(const RCP&lt; Epetra_Operator &gt; &amp;op, EOpTransp opTrans=NOTRANS, EApplyEpetraOpAs applyAs=EPETRA_OP_APPLY_APPLY, EAdjointEpetraOp adjointSupport=EPETRA_OP_ADJOINT_SUPPORTED, const RCP&lt; const VectorSpaceBase&lt; double &gt; &gt; &amp;range=Teuchos::null, const RCP&lt; const VectorSpaceBase&lt; double &gt; &gt; &amp;domain=Teuchos::null)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>partiallyInitialize</name>
      <anchorfile>classThyra_1_1EpetraLinearOp.html</anchorfile>
      <anchor>acacaf9131d41dc4a07e82d68a5d5b440</anchor>
      <arglist>(const RCP&lt; const VectorSpaceBase&lt; double &gt; &gt; &amp;range, const RCP&lt; const VectorSpaceBase&lt; double &gt; &gt; &amp;domain, const RCP&lt; Epetra_Operator &gt; &amp;op, EOpTransp opTrans=NOTRANS, EApplyEpetraOpAs applyAs=EPETRA_OP_APPLY_APPLY, EAdjointEpetraOp adjointSupport=EPETRA_OP_ADJOINT_SUPPORTED)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setFullyInitialized</name>
      <anchorfile>classThyra_1_1EpetraLinearOp.html</anchorfile>
      <anchor>a8e33c8e7f0713bf4fc031e3ca171664b</anchor>
      <arglist>(bool isFullyInitialized=true)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>uninitialize</name>
      <anchorfile>classThyra_1_1EpetraLinearOp.html</anchorfile>
      <anchor>a668b6296b2c279b3462158825ba9eebb</anchor>
      <arglist>(RCP&lt; Epetra_Operator &gt; *op=NULL, EOpTransp *opTrans=NULL, EApplyEpetraOpAs *applyAs=NULL, EAdjointEpetraOp *adjointSupport=NULL, RCP&lt; const VectorSpaceBase&lt; double &gt; &gt; *range=NULL, RCP&lt; const VectorSpaceBase&lt; double &gt; &gt; *domain=NULL)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const SpmdVectorSpaceBase&lt; double &gt; &gt;</type>
      <name>spmdRange</name>
      <anchorfile>classThyra_1_1EpetraLinearOp.html</anchorfile>
      <anchor>a6bbffd537b2a827997f4bf0c0fe80944</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const SpmdVectorSpaceBase&lt; double &gt; &gt;</type>
      <name>spmdDomain</name>
      <anchorfile>classThyra_1_1EpetraLinearOp.html</anchorfile>
      <anchor>aa0a23904758100106d290ee640004f64</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; Epetra_Operator &gt;</type>
      <name>epetra_op</name>
      <anchorfile>classThyra_1_1EpetraLinearOp.html</anchorfile>
      <anchor>ae55e9bedc28d1c620cf257ee7d846adb</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const Epetra_Operator &gt;</type>
      <name>epetra_op</name>
      <anchorfile>classThyra_1_1EpetraLinearOp.html</anchorfile>
      <anchor>a09bf8fa71fbd5ed57879c52f07e43874</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>getNonconstEpetraOpView</name>
      <anchorfile>classThyra_1_1EpetraLinearOp.html</anchorfile>
      <anchor>a501b44a929477f09709ec3381f4b5cff</anchor>
      <arglist>(const Ptr&lt; RCP&lt; Epetra_Operator &gt; &gt; &amp;epetraOp, const Ptr&lt; EOpTransp &gt; &amp;epetraOpTransp, const Ptr&lt; EApplyEpetraOpAs &gt; &amp;epetraOpApplyAs, const Ptr&lt; EAdjointEpetraOp &gt; &amp;epetraOpAdjointSupport)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>getEpetraOpView</name>
      <anchorfile>classThyra_1_1EpetraLinearOp.html</anchorfile>
      <anchor>a0bc7322353846778461f41b13204733a</anchor>
      <arglist>(const Ptr&lt; RCP&lt; const Epetra_Operator &gt; &gt; &amp;epetraOp, const Ptr&lt; EOpTransp &gt; &amp;epetraOpTransp, const Ptr&lt; EApplyEpetraOpAs &gt; &amp;epetraOpApplyAs, const Ptr&lt; EAdjointEpetraOp &gt; &amp;epetraOpAdjointSupport) const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const VectorSpaceBase&lt; double &gt; &gt;</type>
      <name>range</name>
      <anchorfile>classThyra_1_1EpetraLinearOp.html</anchorfile>
      <anchor>aebd75166f2648e1f178befb9209411c3</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const VectorSpaceBase&lt; double &gt; &gt;</type>
      <name>domain</name>
      <anchorfile>classThyra_1_1EpetraLinearOp.html</anchorfile>
      <anchor>ad627a248eb90364a75b96efb03261aec</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const LinearOpBase&lt; double &gt; &gt;</type>
      <name>clone</name>
      <anchorfile>classThyra_1_1EpetraLinearOp.html</anchorfile>
      <anchor>a732ba21aff53e3009d5400de3f5c2c9e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>description</name>
      <anchorfile>classThyra_1_1EpetraLinearOp.html</anchorfile>
      <anchor>ab1002cdd669d80562b82254422af5b10</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>describe</name>
      <anchorfile>classThyra_1_1EpetraLinearOp.html</anchorfile>
      <anchor>a53b1e45ef99018ae744b10303b189864</anchor>
      <arglist>(FancyOStream &amp;out, const Teuchos::EVerbosityLevel verbLevel) const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>bool</type>
      <name>opSupportedImpl</name>
      <anchorfile>classThyra_1_1EpetraLinearOp.html</anchorfile>
      <anchor>aa1c25d957125de918ff01a3b88dd4c00</anchor>
      <arglist>(EOpTransp M_trans) const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>applyImpl</name>
      <anchorfile>classThyra_1_1EpetraLinearOp.html</anchorfile>
      <anchor>a599e7551d2ed057cf04c9d1cae659e8d</anchor>
      <arglist>(const EOpTransp M_trans, const MultiVectorBase&lt; double &gt; &amp;X, const Ptr&lt; MultiVectorBase&lt; double &gt; &gt; &amp;Y, const double alpha, const double beta) const </arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual bool</type>
      <name>supportsScaleLeftImpl</name>
      <anchorfile>classThyra_1_1EpetraLinearOp.html</anchorfile>
      <anchor>aa5c9e3d0e3347826fcae4f125653c231</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual bool</type>
      <name>supportsScaleRightImpl</name>
      <anchorfile>classThyra_1_1EpetraLinearOp.html</anchorfile>
      <anchor>af46ea22785d7f15186574f8a4ce82b47</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual void</type>
      <name>scaleLeftImpl</name>
      <anchorfile>classThyra_1_1EpetraLinearOp.html</anchorfile>
      <anchor>a1a3986ee61427959d37567d467e211d8</anchor>
      <arglist>(const VectorBase&lt; double &gt; &amp;row_scaling)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual void</type>
      <name>scaleRightImpl</name>
      <anchorfile>classThyra_1_1EpetraLinearOp.html</anchorfile>
      <anchor>a3e3fa9e9a57e21438e509893ec438be3</anchor>
      <arglist>(const VectorBase&lt; double &gt; &amp;col_scaling)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual bool</type>
      <name>rowStatIsSupportedImpl</name>
      <anchorfile>classThyra_1_1EpetraLinearOp.html</anchorfile>
      <anchor>a208674cf6376ef4e5f6e2102233cc0b5</anchor>
      <arglist>(const RowStatLinearOpBaseUtils::ERowStat rowStat) const </arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual void</type>
      <name>getRowStatImpl</name>
      <anchorfile>classThyra_1_1EpetraLinearOp.html</anchorfile>
      <anchor>afe2d46ab729b3eda8941cf779fd7223f</anchor>
      <arglist>(const RowStatLinearOpBaseUtils::ERowStat rowStat, const Ptr&lt; VectorBase&lt; double &gt; &gt; &amp;rowStatVec) const </arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual RCP&lt; const SpmdVectorSpaceBase&lt; double &gt; &gt;</type>
      <name>allocateDomain</name>
      <anchorfile>classThyra_1_1EpetraLinearOp.html</anchorfile>
      <anchor>a695b90f2e241b08fb15fd955b3c0db85</anchor>
      <arglist>(const RCP&lt; Epetra_Operator &gt; &amp;op, EOpTransp op_trans) const </arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual RCP&lt; const SpmdVectorSpaceBase&lt; double &gt; &gt;</type>
      <name>allocateRange</name>
      <anchorfile>classThyra_1_1EpetraLinearOp.html</anchorfile>
      <anchor>a7a658130fbd4990010dddb1323bf20d7</anchor>
      <arglist>(const RCP&lt; Epetra_Operator &gt; &amp;op, EOpTransp op_trans) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::EpetraLinearOpBase</name>
    <filename>classThyra_1_1EpetraLinearOpBase.html</filename>
    <base virtualness="virtual">Teuchos::Describable</base>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>getNonconstEpetraOpView</name>
      <anchorfile>classThyra_1_1EpetraLinearOpBase.html</anchorfile>
      <anchor>a912b7cfa5c8e56712bcf015f743f5051</anchor>
      <arglist>(const Ptr&lt; RCP&lt; Epetra_Operator &gt; &gt; &amp;epetraOp, const Ptr&lt; EOpTransp &gt; &amp;epetraOpTransp, const Ptr&lt; EApplyEpetraOpAs &gt; &amp;epetraOpApplyAs, const Ptr&lt; EAdjointEpetraOp &gt; &amp;epetraOpAdjointSupport)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>getEpetraOpView</name>
      <anchorfile>classThyra_1_1EpetraLinearOpBase.html</anchorfile>
      <anchor>a5a8309c267a657bef7ec5732fd3e99d2</anchor>
      <arglist>(const Ptr&lt; RCP&lt; const Epetra_Operator &gt; &gt; &amp;epetraOp, const Ptr&lt; EOpTransp &gt; &amp;epetraOpTransp, const Ptr&lt; EApplyEpetraOpAs &gt; &amp;epetraOpApplyAs, const Ptr&lt; EAdjointEpetraOp &gt; &amp;epetraOpAdjointSupport) const  =0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::EpetraModelEvaluator</name>
    <filename>classThyra_1_1EpetraModelEvaluator.html</filename>
    <base>ModelEvaluatorDefaultBase&lt; double &gt;</base>
    <base virtualness="virtual">Teuchos::ParameterListAcceptor</base>
    <member kind="function">
      <type>RCP&lt; EpetraModelEvaluator &gt;</type>
      <name>epetraModelEvaluator</name>
      <anchorfile>classThyra_1_1EpetraModelEvaluator.html</anchorfile>
      <anchor>a1c94f52374a66a77466fc878452902aa</anchor>
      <arglist>(const RCP&lt; const EpetraExt::ModelEvaluator &gt; &amp;epetraModel, const RCP&lt; LinearOpWithSolveFactoryBase&lt; double &gt; &gt; &amp;W_factory)</arglist>
    </member>
    <member kind="function">
      <type>ModelEvaluatorBase::EDerivativeMultiVectorOrientation</type>
      <name>convert</name>
      <anchorfile>classThyra_1_1EpetraModelEvaluator.html</anchorfile>
      <anchor>af83da30a7d0903ba86925c4d82508284</anchor>
      <arglist>(const EpetraExt::ModelEvaluator::EDerivativeMultiVectorOrientation &amp;mvOrientation)</arglist>
    </member>
    <member kind="function">
      <type>EpetraExt::ModelEvaluator::EDerivativeMultiVectorOrientation</type>
      <name>convert</name>
      <anchorfile>classThyra_1_1EpetraModelEvaluator.html</anchorfile>
      <anchor>a9b41168f2c961bd3171ca1ab637dd50c</anchor>
      <arglist>(const ModelEvaluatorBase::EDerivativeMultiVectorOrientation &amp;mvOrientation)</arglist>
    </member>
    <member kind="function">
      <type>ModelEvaluatorBase::DerivativeProperties</type>
      <name>convert</name>
      <anchorfile>classThyra_1_1EpetraModelEvaluator.html</anchorfile>
      <anchor>aece6307db7696b3562eb205508e84d5a</anchor>
      <arglist>(const EpetraExt::ModelEvaluator::DerivativeProperties &amp;derivativeProperties)</arglist>
    </member>
    <member kind="function">
      <type>ModelEvaluatorBase::DerivativeSupport</type>
      <name>convert</name>
      <anchorfile>classThyra_1_1EpetraModelEvaluator.html</anchorfile>
      <anchor>a53d105778f58ff0295bb81b5d85efa88</anchor>
      <arglist>(const EpetraExt::ModelEvaluator::DerivativeSupport &amp;derivativeSupport)</arglist>
    </member>
    <member kind="function">
      <type>EpetraExt::ModelEvaluator::Derivative</type>
      <name>convert</name>
      <anchorfile>classThyra_1_1EpetraModelEvaluator.html</anchorfile>
      <anchor>abc30fb66bb1bef3737b9f68c8d18c92e</anchor>
      <arglist>(const ModelEvaluatorBase::Derivative&lt; double &gt; &amp;derivative, const RCP&lt; const Epetra_Map &gt; &amp;fnc_map, const RCP&lt; const Epetra_Map &gt; &amp;var_map)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>EpetraModelEvaluator</name>
      <anchorfile>classThyra_1_1EpetraModelEvaluator.html</anchorfile>
      <anchor>a659e747f11fe5403ba2966d446b4bdad</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>EpetraModelEvaluator</name>
      <anchorfile>classThyra_1_1EpetraModelEvaluator.html</anchorfile>
      <anchor>ae873caaecf0e5be0815735a8ea896fe5</anchor>
      <arglist>(const RCP&lt; const EpetraExt::ModelEvaluator &gt; &amp;epetraModel, const RCP&lt; LinearOpWithSolveFactoryBase&lt; double &gt; &gt; &amp;W_factory)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initialize</name>
      <anchorfile>classThyra_1_1EpetraModelEvaluator.html</anchorfile>
      <anchor>a22e9cd3808df6e1e2d9899e7c9b3038c</anchor>
      <arglist>(const RCP&lt; const EpetraExt::ModelEvaluator &gt; &amp;epetraModel, const RCP&lt; LinearOpWithSolveFactoryBase&lt; double &gt; &gt; &amp;W_factory)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const EpetraExt::ModelEvaluator &gt;</type>
      <name>getEpetraModel</name>
      <anchorfile>classThyra_1_1EpetraModelEvaluator.html</anchorfile>
      <anchor>aaff2691158dbe3e19f5560553bb51251</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setNominalValues</name>
      <anchorfile>classThyra_1_1EpetraModelEvaluator.html</anchorfile>
      <anchor>a3924fd60032878ee6b52fe0e2041a8df</anchor>
      <arglist>(const ModelEvaluatorBase::InArgs&lt; double &gt; &amp;nominalValues)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setStateVariableScalingVec</name>
      <anchorfile>classThyra_1_1EpetraModelEvaluator.html</anchorfile>
      <anchor>a2db9e2e7dbd804bec715c2765451e1b5</anchor>
      <arglist>(const RCP&lt; const Epetra_Vector &gt; &amp;stateVariableScalingVec)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const Epetra_Vector &gt;</type>
      <name>getStateVariableInvScalingVec</name>
      <anchorfile>classThyra_1_1EpetraModelEvaluator.html</anchorfile>
      <anchor>a9355a02dc1a6afc9374cd6a7ce53551e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const Epetra_Vector &gt;</type>
      <name>getStateVariableScalingVec</name>
      <anchorfile>classThyra_1_1EpetraModelEvaluator.html</anchorfile>
      <anchor>ab8d188f4af7f51b22f39164bc3fa3123</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setStateFunctionScalingVec</name>
      <anchorfile>classThyra_1_1EpetraModelEvaluator.html</anchorfile>
      <anchor>a0484f049d1f03808cfb9c99803bd2d73</anchor>
      <arglist>(const RCP&lt; const Epetra_Vector &gt; &amp;stateFunctionScalingVec)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const Epetra_Vector &gt;</type>
      <name>getStateFunctionScalingVec</name>
      <anchorfile>classThyra_1_1EpetraModelEvaluator.html</anchorfile>
      <anchor>ab73dcde7477782b3f187c33357ea7b18</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>uninitialize</name>
      <anchorfile>classThyra_1_1EpetraModelEvaluator.html</anchorfile>
      <anchor>aa38d2bb28c96dbf2aba905eb3fc43540</anchor>
      <arglist>(RCP&lt; const EpetraExt::ModelEvaluator &gt; *epetraModel=NULL, RCP&lt; LinearOpWithSolveFactoryBase&lt; double &gt; &gt; *W_factory=NULL)</arglist>
    </member>
    <member kind="function">
      <type>const ModelEvaluatorBase::InArgs&lt; double &gt; &amp;</type>
      <name>getFinalPoint</name>
      <anchorfile>classThyra_1_1EpetraModelEvaluator.html</anchorfile>
      <anchor>a67734e4aa3253190f0c6dec9b5334560</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>finalPointWasSolved</name>
      <anchorfile>classThyra_1_1EpetraModelEvaluator.html</anchorfile>
      <anchor>a470cfe236dab9a5bbd8974e6332808b2</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>description</name>
      <anchorfile>classThyra_1_1EpetraModelEvaluator.html</anchorfile>
      <anchor>a0c906640507890fa20d0770eb76cb9eb</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setParameterList</name>
      <anchorfile>classThyra_1_1EpetraModelEvaluator.html</anchorfile>
      <anchor>a8d45a2e57e8cd149f4698a6e4c5bec0b</anchor>
      <arglist>(RCP&lt; Teuchos::ParameterList &gt; const &amp;paramList)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; Teuchos::ParameterList &gt;</type>
      <name>getNonconstParameterList</name>
      <anchorfile>classThyra_1_1EpetraModelEvaluator.html</anchorfile>
      <anchor>a01c8ea87ba890ad52c6963af09aa84a6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; Teuchos::ParameterList &gt;</type>
      <name>unsetParameterList</name>
      <anchorfile>classThyra_1_1EpetraModelEvaluator.html</anchorfile>
      <anchor>a013a42489f443528101608b9d7bf70ae</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const Teuchos::ParameterList &gt;</type>
      <name>getParameterList</name>
      <anchorfile>classThyra_1_1EpetraModelEvaluator.html</anchorfile>
      <anchor>a546533ece985a486f4d0dd224c8b7ddd</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const Teuchos::ParameterList &gt;</type>
      <name>getValidParameters</name>
      <anchorfile>classThyra_1_1EpetraModelEvaluator.html</anchorfile>
      <anchor>abc281195725a1c122236cfdf47198c6f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Np</name>
      <anchorfile>classThyra_1_1EpetraModelEvaluator.html</anchorfile>
      <anchor>aa12682e9a5b12fcc53e448860f731a1f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Ng</name>
      <anchorfile>classThyra_1_1EpetraModelEvaluator.html</anchorfile>
      <anchor>a20e47792391a0878bdae2fd65b269245</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const VectorSpaceBase&lt; double &gt; &gt;</type>
      <name>get_x_space</name>
      <anchorfile>classThyra_1_1EpetraModelEvaluator.html</anchorfile>
      <anchor>a891d6d7c19dbfa5a696d20f22e501166</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const VectorSpaceBase&lt; double &gt; &gt;</type>
      <name>get_f_space</name>
      <anchorfile>classThyra_1_1EpetraModelEvaluator.html</anchorfile>
      <anchor>ab1688dfb8d7592d5d46a51e57f0ca8f7</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const VectorSpaceBase&lt; double &gt; &gt;</type>
      <name>get_p_space</name>
      <anchorfile>classThyra_1_1EpetraModelEvaluator.html</anchorfile>
      <anchor>a2eb843f82100e1eb6bf55ef025b6e52e</anchor>
      <arglist>(int l) const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const Teuchos::Array&lt; std::string &gt; &gt;</type>
      <name>get_p_names</name>
      <anchorfile>classThyra_1_1EpetraModelEvaluator.html</anchorfile>
      <anchor>af7f0709906c534421374d7628ef0815c</anchor>
      <arglist>(int l) const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const VectorSpaceBase&lt; double &gt; &gt;</type>
      <name>get_g_space</name>
      <anchorfile>classThyra_1_1EpetraModelEvaluator.html</anchorfile>
      <anchor>a046d69a879590791a5fe6b62b2a16d32</anchor>
      <arglist>(int j) const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::ArrayView&lt; const std::string &gt;</type>
      <name>get_g_names</name>
      <anchorfile>classThyra_1_1EpetraModelEvaluator.html</anchorfile>
      <anchor>a777b155aae042f39c7674bf3cdb1ecbe</anchor>
      <arglist>(int j) const </arglist>
    </member>
    <member kind="function">
      <type>ModelEvaluatorBase::InArgs&lt; double &gt;</type>
      <name>getNominalValues</name>
      <anchorfile>classThyra_1_1EpetraModelEvaluator.html</anchorfile>
      <anchor>a9b0ee5ad84ed71b251c6a7e32fe4d8ff</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>ModelEvaluatorBase::InArgs&lt; double &gt;</type>
      <name>getLowerBounds</name>
      <anchorfile>classThyra_1_1EpetraModelEvaluator.html</anchorfile>
      <anchor>ad869b756f71beef9ad5cde80032eadb1</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>ModelEvaluatorBase::InArgs&lt; double &gt;</type>
      <name>getUpperBounds</name>
      <anchorfile>classThyra_1_1EpetraModelEvaluator.html</anchorfile>
      <anchor>a1ad1d44eea26476ac2f1063af2d3ca4b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; LinearOpBase&lt; double &gt; &gt;</type>
      <name>create_W_op</name>
      <anchorfile>classThyra_1_1EpetraModelEvaluator.html</anchorfile>
      <anchor>a9bdd36892490f1a5a5505430600843d7</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; PreconditionerBase&lt; double &gt; &gt;</type>
      <name>create_W_prec</name>
      <anchorfile>classThyra_1_1EpetraModelEvaluator.html</anchorfile>
      <anchor>a05b628bbb0770609ac1393fc3b051e46</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const LinearOpWithSolveFactoryBase&lt; double &gt; &gt;</type>
      <name>get_W_factory</name>
      <anchorfile>classThyra_1_1EpetraModelEvaluator.html</anchorfile>
      <anchor>a3ec1b1fcab0d4451a4931e2c8d452a33</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>ModelEvaluatorBase::InArgs&lt; double &gt;</type>
      <name>createInArgs</name>
      <anchorfile>classThyra_1_1EpetraModelEvaluator.html</anchorfile>
      <anchor>a77559b4ae7597defd2204c3a47ce7fc5</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>reportFinalPoint</name>
      <anchorfile>classThyra_1_1EpetraModelEvaluator.html</anchorfile>
      <anchor>a81629840772af6c1411c99314f44582b</anchor>
      <arglist>(const ModelEvaluatorBase::InArgs&lt; double &gt; &amp;finalPoint, const bool wasSolved)</arglist>
    </member>
    <docanchor file="classThyra_1_1EpetraModelEvaluator" title="Scaling">Thyra_EpetraModelEvaluator_Scaling_sec</docanchor>
  </compound>
  <compound kind="class">
    <name>Thyra::EpetraOperatorViewExtractorBase</name>
    <filename>classThyra_1_1EpetraOperatorViewExtractorBase.html</filename>
    <base virtualness="virtual">Teuchos::Describable</base>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>isCompatible</name>
      <anchorfile>classThyra_1_1EpetraOperatorViewExtractorBase.html</anchorfile>
      <anchor>aad42f30fc950e581b591f6067e594d38</anchor>
      <arglist>(const LinearOpBase&lt; double &gt; &amp;fwdOp) const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>getNonconstEpetraOpView</name>
      <anchorfile>classThyra_1_1EpetraOperatorViewExtractorBase.html</anchorfile>
      <anchor>a14ceb2b2271314d7264f84a973477ac7</anchor>
      <arglist>(const RCP&lt; LinearOpBase&lt; double &gt; &gt; &amp;fwdOp, const Ptr&lt; RCP&lt; Epetra_Operator &gt; &gt; &amp;epetraOp, const Ptr&lt; EOpTransp &gt; &amp;epetraOpTransp, const Ptr&lt; EApplyEpetraOpAs &gt; &amp;epetraOpApplyAs, const Ptr&lt; EAdjointEpetraOp &gt; &amp;epetraOpAdjointSupport, const Ptr&lt; double &gt; &amp;epetraOpScalar) const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>getEpetraOpView</name>
      <anchorfile>classThyra_1_1EpetraOperatorViewExtractorBase.html</anchorfile>
      <anchor>a7d9977081ecc155ed75fde412e173cbd</anchor>
      <arglist>(const RCP&lt; const LinearOpBase&lt; double &gt; &gt; &amp;fwdOp, const Ptr&lt; RCP&lt; const Epetra_Operator &gt; &gt; &amp;epetraOp, const Ptr&lt; EOpTransp &gt; &amp;epetraOpTransp, const Ptr&lt; EApplyEpetraOpAs &gt; &amp;epetraOpApplyAs, const Ptr&lt; EAdjointEpetraOp &gt; &amp;epetraOpAdjointSupport, const Ptr&lt; double &gt; &amp;epetraOpScalar) const  =0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::EpetraOperatorViewExtractorStd</name>
    <filename>classThyra_1_1EpetraOperatorViewExtractorStd.html</filename>
    <base virtualness="virtual">Thyra::EpetraOperatorViewExtractorBase</base>
    <member kind="function">
      <type>bool</type>
      <name>isCompatible</name>
      <anchorfile>classThyra_1_1EpetraOperatorViewExtractorStd.html</anchorfile>
      <anchor>a5476396a9e13ff98e633e56d958c96d5</anchor>
      <arglist>(const LinearOpBase&lt; double &gt; &amp;fwdOp) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>getNonconstEpetraOpView</name>
      <anchorfile>classThyra_1_1EpetraOperatorViewExtractorStd.html</anchorfile>
      <anchor>a84b113c50e6400fe7871a83f323b85c9</anchor>
      <arglist>(const RCP&lt; LinearOpBase&lt; double &gt; &gt; &amp;fwdOp, const Ptr&lt; RCP&lt; Epetra_Operator &gt; &gt; &amp;epetraOp, const Ptr&lt; EOpTransp &gt; &amp;epetraOpTransp, const Ptr&lt; EApplyEpetraOpAs &gt; &amp;epetraOpApplyAs, const Ptr&lt; EAdjointEpetraOp &gt; &amp;epetraOpAdjointSupport, const Ptr&lt; double &gt; &amp;epetraOpScalar) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>getEpetraOpView</name>
      <anchorfile>classThyra_1_1EpetraOperatorViewExtractorStd.html</anchorfile>
      <anchor>a8edd26b897d6efe1556067ced36a758c</anchor>
      <arglist>(const RCP&lt; const LinearOpBase&lt; double &gt; &gt; &amp;fwdOp, const Ptr&lt; RCP&lt; const Epetra_Operator &gt; &gt; &amp;epetraOp, const Ptr&lt; EOpTransp &gt; &amp;epetraOpTransp, const Ptr&lt; EApplyEpetraOpAs &gt; &amp;epetraOpApplyAs, const Ptr&lt; EAdjointEpetraOp &gt; &amp;epetraOpAdjointSupport, const Ptr&lt; double &gt; &amp;epetraOpScalar) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::EpetraOperatorWrapper</name>
    <filename>classThyra_1_1EpetraOperatorWrapper.html</filename>
    <base>Epetra_Operator</base>
    <member kind="function">
      <type>RCP&lt; const LinearOpBase&lt; double &gt; &gt;</type>
      <name>makeEpetraWrapper</name>
      <anchorfile>classThyra_1_1EpetraOperatorWrapper.html</anchorfile>
      <anchor>a46c6dbb310473052a8d9e68cdcef10d0</anchor>
      <arglist>(const RCP&lt; const LinearOpBase&lt; double &gt; &gt; &amp;thyraOp)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>EpetraOperatorWrapper</name>
      <anchorfile>classThyra_1_1EpetraOperatorWrapper.html</anchorfile>
      <anchor>a55b79ba0b3a086afc72d9f5f56ae30fa</anchor>
      <arglist>(const RCP&lt; const LinearOpBase&lt; double &gt; &gt; &amp;thyraOp)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const LinearOpBase&lt; double &gt; &gt;</type>
      <name>getThyraOp</name>
      <anchorfile>classThyra_1_1EpetraOperatorWrapper.html</anchorfile>
      <anchor>a632d499790b5a5a597267bdd5a07b8b0</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>copyEpetraIntoThyra</name>
      <anchorfile>classThyra_1_1EpetraOperatorWrapper.html</anchorfile>
      <anchor>a4805ce7af27b131e0a6cd6edb3c0de8e</anchor>
      <arglist>(const Epetra_MultiVector &amp;x, const Ptr&lt; VectorBase&lt; double &gt; &gt; &amp;thyraVec) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>copyThyraIntoEpetra</name>
      <anchorfile>classThyra_1_1EpetraOperatorWrapper.html</anchorfile>
      <anchor>a9d00a527bcd999ba145b41ded01b95fe</anchor>
      <arglist>(const VectorBase&lt; double &gt; &amp;thyraVec, Epetra_MultiVector &amp;x) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetUseTranspose</name>
      <anchorfile>classThyra_1_1EpetraOperatorWrapper.html</anchorfile>
      <anchor>a19ada2ad9db9a7da7a2a1399518e7362</anchor>
      <arglist>(bool UseTranspose_in)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Apply</name>
      <anchorfile>classThyra_1_1EpetraOperatorWrapper.html</anchorfile>
      <anchor>a514e79045a45fdc199a6ab35ae1744f4</anchor>
      <arglist>(const Epetra_MultiVector &amp;X, Epetra_MultiVector &amp;Y) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ApplyInverse</name>
      <anchorfile>classThyra_1_1EpetraOperatorWrapper.html</anchorfile>
      <anchor>aaa93f607296834b6f8535dc709b32a9c</anchor>
      <arglist>(const Epetra_MultiVector &amp;X, Epetra_MultiVector &amp;Y) const </arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>NormInf</name>
      <anchorfile>classThyra_1_1EpetraOperatorWrapper.html</anchorfile>
      <anchor>a4bc980a0f08c8e08047d385783be677e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const char *</type>
      <name>Label</name>
      <anchorfile>classThyra_1_1EpetraOperatorWrapper.html</anchorfile>
      <anchor>a41559c4ab4548d8bddd16effcaf1f2fa</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>UseTranspose</name>
      <anchorfile>classThyra_1_1EpetraOperatorWrapper.html</anchorfile>
      <anchor>a9a282b993cb3c33a9b5b8b6025792c9e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>HasNormInf</name>
      <anchorfile>classThyra_1_1EpetraOperatorWrapper.html</anchorfile>
      <anchor>a137fc3ae132133e02449d5f1540cc4eb</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_Comm &amp;</type>
      <name>Comm</name>
      <anchorfile>classThyra_1_1EpetraOperatorWrapper.html</anchorfile>
      <anchor>a02485ea804993e8290b630f876c9f89f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_Map &amp;</type>
      <name>OperatorDomainMap</name>
      <anchorfile>classThyra_1_1EpetraOperatorWrapper.html</anchorfile>
      <anchor>ac9029dd29afbe2112886f5145895ce22</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_Map &amp;</type>
      <name>OperatorRangeMap</name>
      <anchorfile>classThyra_1_1EpetraOperatorWrapper.html</anchorfile>
      <anchor>af112baeb2d271e138a5d4d230c0361ba</anchor>
      <arglist>() const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::EuclideanScalarProd</name>
    <filename>classThyra_1_1EuclideanScalarProd.html</filename>
    <templarg></templarg>
    <base>Thyra::ScalarProdBase</base>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual bool</type>
      <name>isEuclideanImpl</name>
      <anchorfile>classThyra_1_1EuclideanScalarProd.html</anchorfile>
      <anchor>a48f98d46fe9d2e61f27ecbd042d03694</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual void</type>
      <name>scalarProdsImpl</name>
      <anchorfile>classThyra_1_1EuclideanScalarProd.html</anchorfile>
      <anchor>ac5f294cd26c19cc1f9a1d94d0e04de53</anchor>
      <arglist>(const MultiVectorBase&lt; Scalar &gt; &amp;X, const MultiVectorBase&lt; Scalar &gt; &amp;Y, const ArrayView&lt; Scalar &gt; &amp;scalarProds) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::ModelEvaluatorBase::Evaluation</name>
    <filename>classThyra_1_1ModelEvaluatorBase_1_1Evaluation.html</filename>
    <templarg>ObjType</templarg>
    <base>Teuchos::RCP</base>
    <member kind="function">
      <type></type>
      <name>Evaluation</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1Evaluation.html</anchorfile>
      <anchor>aa796cd38b07634a05d54edda05338991</anchor>
      <arglist>(Teuchos::ENull)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Evaluation</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1Evaluation.html</anchorfile>
      <anchor>af659f143f74cf534d9e72764c217edc8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Evaluation</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1Evaluation.html</anchorfile>
      <anchor>a799ad02fa4852238a01107d49f1d6941</anchor>
      <arglist>(const RCP&lt; ObjType &gt; &amp;obj)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Evaluation</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1Evaluation.html</anchorfile>
      <anchor>a49ec91887ec884f54b02b89073a6e787</anchor>
      <arglist>(const RCP&lt; ObjType &gt; &amp;obj, EEvalType evalType)</arglist>
    </member>
    <member kind="function">
      <type>EEvalType</type>
      <name>getType</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1Evaluation.html</anchorfile>
      <anchor>acb3a179ce70aa67019504ed6ebde26e6</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>reset</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1Evaluation.html</anchorfile>
      <anchor>a44951338593a297d7882e2a3cf571e09</anchor>
      <arglist>(const RCP&lt; ObjType &gt; &amp;obj, EEvalType evalType)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Evaluation&lt; Thyra::VectorBase&lt; double &gt; &gt;</name>
    <filename>classThyra_1_1ModelEvaluatorBase_1_1Evaluation.html</filename>
    <base>Teuchos::RCP</base>
    <member kind="function">
      <type></type>
      <name>Evaluation</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1Evaluation.html</anchorfile>
      <anchor>aa796cd38b07634a05d54edda05338991</anchor>
      <arglist>(Teuchos::ENull)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Evaluation</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1Evaluation.html</anchorfile>
      <anchor>af659f143f74cf534d9e72764c217edc8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Evaluation</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1Evaluation.html</anchorfile>
      <anchor>a799ad02fa4852238a01107d49f1d6941</anchor>
      <arglist>(const RCP&lt; Thyra::VectorBase&lt; double &gt; &gt; &amp;obj)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Evaluation</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1Evaluation.html</anchorfile>
      <anchor>a49ec91887ec884f54b02b89073a6e787</anchor>
      <arglist>(const RCP&lt; Thyra::VectorBase&lt; double &gt; &gt; &amp;obj, EEvalType evalType)</arglist>
    </member>
    <member kind="function">
      <type>EEvalType</type>
      <name>getType</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1Evaluation.html</anchorfile>
      <anchor>acb3a179ce70aa67019504ed6ebde26e6</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>reset</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1Evaluation.html</anchorfile>
      <anchor>a44951338593a297d7882e2a3cf571e09</anchor>
      <arglist>(const RCP&lt; Thyra::VectorBase&lt; double &gt; &gt; &amp;obj, EEvalType evalType)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Evaluation&lt; Thyra::VectorBase&lt; Scalar &gt; &gt;</name>
    <filename>classThyra_1_1ModelEvaluatorBase_1_1Evaluation.html</filename>
    <base>Teuchos::RCP</base>
    <member kind="function">
      <type></type>
      <name>Evaluation</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1Evaluation.html</anchorfile>
      <anchor>aa796cd38b07634a05d54edda05338991</anchor>
      <arglist>(Teuchos::ENull)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Evaluation</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1Evaluation.html</anchorfile>
      <anchor>af659f143f74cf534d9e72764c217edc8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Evaluation</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1Evaluation.html</anchorfile>
      <anchor>a799ad02fa4852238a01107d49f1d6941</anchor>
      <arglist>(const RCP&lt; Thyra::VectorBase&lt; Scalar &gt; &gt; &amp;obj)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Evaluation</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1Evaluation.html</anchorfile>
      <anchor>a49ec91887ec884f54b02b89073a6e787</anchor>
      <arglist>(const RCP&lt; Thyra::VectorBase&lt; Scalar &gt; &gt; &amp;obj, EEvalType evalType)</arglist>
    </member>
    <member kind="function">
      <type>EEvalType</type>
      <name>getType</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1Evaluation.html</anchorfile>
      <anchor>acb3a179ce70aa67019504ed6ebde26e6</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>reset</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1Evaluation.html</anchorfile>
      <anchor>a44951338593a297d7882e2a3cf571e09</anchor>
      <arglist>(const RCP&lt; Thyra::VectorBase&lt; Scalar &gt; &gt; &amp;obj, EEvalType evalType)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ExampleTridiagSerialLinearOp</name>
    <filename>classExampleTridiagSerialLinearOp.html</filename>
    <templarg></templarg>
    <base>Thyra::LinearOpDefaultBase</base>
    <member kind="function">
      <type></type>
      <name>ExampleTridiagSerialLinearOp</name>
      <anchorfile>classExampleTridiagSerialLinearOp.html</anchorfile>
      <anchor>a6c00e5c4aec9041ff3162a2e2394faf2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ExampleTridiagSerialLinearOp</name>
      <anchorfile>classExampleTridiagSerialLinearOp.html</anchorfile>
      <anchor>abf5da4a91cc9416b516c817883d26cdf</anchor>
      <arglist>(const Thyra::Ordinal dim, const Teuchos::ArrayView&lt; const Scalar &gt; &amp;lower, const Teuchos::ArrayView&lt; const Scalar &gt; &amp;diag, const Teuchos::ArrayView&lt; const Scalar &gt; &amp;upper)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initialize</name>
      <anchorfile>classExampleTridiagSerialLinearOp.html</anchorfile>
      <anchor>a93cf3b6f1a2aa346d3ec864694fdc186</anchor>
      <arglist>(const Thyra::Ordinal dim, const Teuchos::ArrayView&lt; const Scalar &gt; &amp;lower, const Teuchos::ArrayView&lt; const Scalar &gt; &amp;diag, const Teuchos::ArrayView&lt; const Scalar &gt; &amp;upper)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>Teuchos::RCP&lt; const Thyra::VectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>range</name>
      <anchorfile>classExampleTridiagSerialLinearOp.html</anchorfile>
      <anchor>a5d3b427dcfe768e112ce6243a6278404</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>Teuchos::RCP&lt; const Thyra::VectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>domain</name>
      <anchorfile>classExampleTridiagSerialLinearOp.html</anchorfile>
      <anchor>adc863d32524e8eca515b0f5512ff491e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>bool</type>
      <name>opSupportedImpl</name>
      <anchorfile>classExampleTridiagSerialLinearOp.html</anchorfile>
      <anchor>a6be76f6bd7ceca261767893591143553</anchor>
      <arglist>(Thyra::EOpTransp M_trans) const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>applyImpl</name>
      <anchorfile>classExampleTridiagSerialLinearOp.html</anchorfile>
      <anchor>aa2cae8a3feb3a9153defa217b0790570</anchor>
      <arglist>(const Thyra::EOpTransp M_trans, const Thyra::MultiVectorBase&lt; Scalar &gt; &amp;X_in, const Teuchos::Ptr&lt; Thyra::MultiVectorBase&lt; Scalar &gt; &gt; &amp;Y_inout, const Scalar alpha, const Scalar beta) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ExampleTridiagSpmdLinearOp</name>
    <filename>classExampleTridiagSpmdLinearOp.html</filename>
    <templarg></templarg>
    <base>Thyra::LinearOpDefaultBase</base>
    <member kind="function">
      <type></type>
      <name>ExampleTridiagSpmdLinearOp</name>
      <anchorfile>classExampleTridiagSpmdLinearOp.html</anchorfile>
      <anchor>a59abf41bcbe36b8fa8b48bf883320a75</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ExampleTridiagSpmdLinearOp</name>
      <anchorfile>classExampleTridiagSpmdLinearOp.html</anchorfile>
      <anchor>afa1ab792f64ea6d00f4a92efe45d1377</anchor>
      <arglist>(const Teuchos::RCP&lt; const Teuchos::Comm&lt; Thyra::Ordinal &gt; &gt; &amp;comm, const Thyra::Ordinal localDim, const Teuchos::ArrayView&lt; const Scalar &gt; &amp;lower, const Teuchos::ArrayView&lt; const Scalar &gt; &amp;diag, const Teuchos::ArrayView&lt; const Scalar &gt; &amp;upper)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initialize</name>
      <anchorfile>classExampleTridiagSpmdLinearOp.html</anchorfile>
      <anchor>a0cee7c040de8cc234661420d5002c953</anchor>
      <arglist>(const Teuchos::RCP&lt; const Teuchos::Comm&lt; Thyra::Ordinal &gt; &gt; &amp;comm, const Thyra::Ordinal localDim, const Teuchos::ArrayView&lt; const Scalar &gt; &amp;lower, const Teuchos::ArrayView&lt; const Scalar &gt; &amp;diag, const Teuchos::ArrayView&lt; const Scalar &gt; &amp;upper)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>Teuchos::RCP&lt; const Thyra::VectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>range</name>
      <anchorfile>classExampleTridiagSpmdLinearOp.html</anchorfile>
      <anchor>af559e31ed279514700c249895c89e518</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>Teuchos::RCP&lt; const Thyra::VectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>domain</name>
      <anchorfile>classExampleTridiagSpmdLinearOp.html</anchorfile>
      <anchor>a79bdc9f7297ec384526c5d0d0cc838bf</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>bool</type>
      <name>opSupportedImpl</name>
      <anchorfile>classExampleTridiagSpmdLinearOp.html</anchorfile>
      <anchor>ac85ae6ba66beda7a32dad9cc97cb738e</anchor>
      <arglist>(Thyra::EOpTransp M_trans) const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>applyImpl</name>
      <anchorfile>classExampleTridiagSpmdLinearOp.html</anchorfile>
      <anchor>a172435ffc5b1f9ada99bd3d4f3d8f84b</anchor>
      <arglist>(const Thyra::EOpTransp M_trans, const Thyra::MultiVectorBase&lt; Scalar &gt; &amp;X_in, const Teuchos::Ptr&lt; Thyra::MultiVectorBase&lt; Scalar &gt; &gt; &amp;Y_inout, const Scalar alpha, const Scalar beta) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::IdentityLinearOpBase</name>
    <filename>classThyra_1_1IdentityLinearOpBase.html</filename>
    <templarg></templarg>
    <base virtualness="virtual">Thyra::LinearOpBase</base>
  </compound>
  <compound kind="class">
    <name>Thyra::ModelEvaluatorBase::InArgs</name>
    <filename>classThyra_1_1ModelEvaluatorBase_1_1InArgs.html</filename>
    <templarg>Scalar</templarg>
    <base>Teuchos::Describable</base>
    <member kind="typedef">
      <type>Teuchos::ScalarTraits&lt; Scalar &gt;::magnitudeType</type>
      <name>ScalarMag</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1InArgs.html</anchorfile>
      <anchor>aa56a363c3b1a3239eaeff962c7933c9b</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>InArgs</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1InArgs.html</anchorfile>
      <anchor>a919a2c187f8ece9bc4df1b0612e88775</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Np</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1InArgs.html</anchorfile>
      <anchor>a0448e87846c26a62c28603a32e5e9b12</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>supports</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1InArgs.html</anchorfile>
      <anchor>ae2950a1835617ac10be7a6ba95066b8a</anchor>
      <arglist>(EInArgsMembers arg) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_x_dot</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1InArgs.html</anchorfile>
      <anchor>abea3d4c8e895c2233a795bafde2b8dd4</anchor>
      <arglist>(const RCP&lt; const VectorBase&lt; Scalar &gt; &gt; &amp;x_dot)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const VectorBase&lt; Scalar &gt; &gt;</type>
      <name>get_x_dot</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1InArgs.html</anchorfile>
      <anchor>af4c5507cc7788fa30f4b511db22be8d0</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_x</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1InArgs.html</anchorfile>
      <anchor>a7a7c6d048d099d3f8714ba3e075e4a9d</anchor>
      <arglist>(const RCP&lt; const VectorBase&lt; Scalar &gt; &gt; &amp;x)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const VectorBase&lt; Scalar &gt; &gt;</type>
      <name>get_x</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1InArgs.html</anchorfile>
      <anchor>a505709727238d161c9d7823caa78ccf1</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_p</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1InArgs.html</anchorfile>
      <anchor>a1b24462d861877fdfbf3a3536294e247</anchor>
      <arglist>(int l, const RCP&lt; const VectorBase&lt; Scalar &gt; &gt; &amp;p_l)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const VectorBase&lt; Scalar &gt; &gt;</type>
      <name>get_p</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1InArgs.html</anchorfile>
      <anchor>a8062c06dcf39fd4c312785f90feefcca</anchor>
      <arglist>(int l) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_x_dot_mp</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1InArgs.html</anchorfile>
      <anchor>a6720b457d386552f0d3ce6a846b66e5f</anchor>
      <arglist>(const RCP&lt; const Stokhos::ProductEpetraVector &gt; &amp;x_dot_mp)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const Stokhos::ProductEpetraVector &gt;</type>
      <name>get_x_dot_mp</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1InArgs.html</anchorfile>
      <anchor>a91aa0e980e4e74abf7f1f1639116269e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_x_mp</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1InArgs.html</anchorfile>
      <anchor>a5a833b86bbb6f0468518b7fd50431b61</anchor>
      <arglist>(const RCP&lt; const Stokhos::ProductEpetraVector &gt; &amp;x_mp)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const Stokhos::ProductEpetraVector &gt;</type>
      <name>get_x_mp</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1InArgs.html</anchorfile>
      <anchor>a71c86785ddc558628b908eb10eecda1b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>supports</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1InArgs.html</anchorfile>
      <anchor>a135e7d72113ff03dba9deb2bf39f5473</anchor>
      <arglist>(EInArgs_p_mp arg, int l) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_t</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1InArgs.html</anchorfile>
      <anchor>acc3ef922c7b06012809214d8c85baa94</anchor>
      <arglist>(ScalarMag t)</arglist>
    </member>
    <member kind="function">
      <type>ScalarMag</type>
      <name>get_t</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1InArgs.html</anchorfile>
      <anchor>a68869ca08ebdd8a781e848611918e27c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_alpha</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1InArgs.html</anchorfile>
      <anchor>ac67ddab96eaaaab08076d0c3aa152ced</anchor>
      <arglist>(Scalar alpha)</arglist>
    </member>
    <member kind="function">
      <type>Scalar</type>
      <name>get_alpha</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1InArgs.html</anchorfile>
      <anchor>a1e5a4a0c6bb196f964e27463c9d920cd</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_beta</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1InArgs.html</anchorfile>
      <anchor>a80044e33b2426c96cea0939f943c92bb</anchor>
      <arglist>(Scalar beta)</arglist>
    </member>
    <member kind="function">
      <type>Scalar</type>
      <name>get_beta</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1InArgs.html</anchorfile>
      <anchor>aff7a9a5377ffff438bc82f292ced23cc</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setArgs</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1InArgs.html</anchorfile>
      <anchor>a47ef9fef98bb3f93d7bcc28a1bf18203</anchor>
      <arglist>(const InArgs&lt; Scalar &gt; &amp;inArgs, bool ignoreUnsupported=false, bool cloneObjects=false)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>assertSameSupport</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1InArgs.html</anchorfile>
      <anchor>a663cf4d1b3444fa684f9453448276462</anchor>
      <arglist>(const InArgs&lt; Scalar &gt; &amp;inArgs) const </arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>modelEvalDescription</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1InArgs.html</anchorfile>
      <anchor>a0b58c6c2b71ad98f6d3fa39594b78dd0</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>description</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1InArgs.html</anchorfile>
      <anchor>ae5d88c5c324015f2db45a0daf866f871</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>describe</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1InArgs.html</anchorfile>
      <anchor>aa4029b645f7dd0cd69c1ef399920c810</anchor>
      <arglist>(Teuchos::FancyOStream &amp;out, const Teuchos::EVerbosityLevel verbLevel) const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>_setModelEvalDescription</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1InArgs.html</anchorfile>
      <anchor>af6c1c713f49e8b7f12002a9cd3940692</anchor>
      <arglist>(const std::string &amp;modelEvalDescription)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>_set_Np</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1InArgs.html</anchorfile>
      <anchor>aa4b4b3cebfa2c2d6c720239a82ad2fb0</anchor>
      <arglist>(int Np)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>_setSupports</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1InArgs.html</anchorfile>
      <anchor>af268545dd6bf9c722eda098135b8be72</anchor>
      <arglist>(EInArgsMembers arg, bool supports)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>_setSupports</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1InArgs.html</anchorfile>
      <anchor>a6cb78484aed09fb128873132a967f54b</anchor>
      <arglist>(EInArgs_p_mp arg, int l, bool supports)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>_setSupports</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1InArgs.html</anchorfile>
      <anchor>ab8d802a8af8db03416d9045015bd1741</anchor>
      <arglist>(const InArgs&lt; Scalar &gt; &amp;inputInArgs, const int Np)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>_setUnsupportsAndRelated</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1InArgs.html</anchorfile>
      <anchor>a49a405c558e929d6323e787c60a65439</anchor>
      <arglist>(EInArgsMembers arg)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>InArgs&lt; double &gt;</name>
    <filename>classThyra_1_1ModelEvaluatorBase_1_1InArgs.html</filename>
    <base>Teuchos::Describable</base>
    <member kind="typedef">
      <type>Teuchos::ScalarTraits&lt; double &gt;::magnitudeType</type>
      <name>ScalarMag</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1InArgs.html</anchorfile>
      <anchor>aa56a363c3b1a3239eaeff962c7933c9b</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>InArgs</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1InArgs.html</anchorfile>
      <anchor>a919a2c187f8ece9bc4df1b0612e88775</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Np</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1InArgs.html</anchorfile>
      <anchor>a0448e87846c26a62c28603a32e5e9b12</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>supports</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1InArgs.html</anchorfile>
      <anchor>ae2950a1835617ac10be7a6ba95066b8a</anchor>
      <arglist>(EInArgsMembers arg) const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>supports</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1InArgs.html</anchorfile>
      <anchor>a135e7d72113ff03dba9deb2bf39f5473</anchor>
      <arglist>(EInArgs_p_mp arg, int l) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_x_dot</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1InArgs.html</anchorfile>
      <anchor>abea3d4c8e895c2233a795bafde2b8dd4</anchor>
      <arglist>(const RCP&lt; const VectorBase&lt; double &gt; &gt; &amp;x_dot)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const VectorBase&lt; double &gt; &gt;</type>
      <name>get_x_dot</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1InArgs.html</anchorfile>
      <anchor>af4c5507cc7788fa30f4b511db22be8d0</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_x</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1InArgs.html</anchorfile>
      <anchor>a7a7c6d048d099d3f8714ba3e075e4a9d</anchor>
      <arglist>(const RCP&lt; const VectorBase&lt; double &gt; &gt; &amp;x)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const VectorBase&lt; double &gt; &gt;</type>
      <name>get_x</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1InArgs.html</anchorfile>
      <anchor>a505709727238d161c9d7823caa78ccf1</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_p</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1InArgs.html</anchorfile>
      <anchor>a1b24462d861877fdfbf3a3536294e247</anchor>
      <arglist>(int l, const RCP&lt; const VectorBase&lt; double &gt; &gt; &amp;p_l)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const VectorBase&lt; double &gt; &gt;</type>
      <name>get_p</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1InArgs.html</anchorfile>
      <anchor>a8062c06dcf39fd4c312785f90feefcca</anchor>
      <arglist>(int l) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_x_dot_mp</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1InArgs.html</anchorfile>
      <anchor>a6720b457d386552f0d3ce6a846b66e5f</anchor>
      <arglist>(const RCP&lt; const Stokhos::ProductEpetraVector &gt; &amp;x_dot_mp)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const Stokhos::ProductEpetraVector &gt;</type>
      <name>get_x_dot_mp</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1InArgs.html</anchorfile>
      <anchor>a91aa0e980e4e74abf7f1f1639116269e</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_x_mp</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1InArgs.html</anchorfile>
      <anchor>a5a833b86bbb6f0468518b7fd50431b61</anchor>
      <arglist>(const RCP&lt; const Stokhos::ProductEpetraVector &gt; &amp;x_mp)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const Stokhos::ProductEpetraVector &gt;</type>
      <name>get_x_mp</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1InArgs.html</anchorfile>
      <anchor>a71c86785ddc558628b908eb10eecda1b</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_t</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1InArgs.html</anchorfile>
      <anchor>acc3ef922c7b06012809214d8c85baa94</anchor>
      <arglist>(ScalarMag t)</arglist>
    </member>
    <member kind="function">
      <type>ScalarMag</type>
      <name>get_t</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1InArgs.html</anchorfile>
      <anchor>a68869ca08ebdd8a781e848611918e27c</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_alpha</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1InArgs.html</anchorfile>
      <anchor>ac67ddab96eaaaab08076d0c3aa152ced</anchor>
      <arglist>(double alpha)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>get_alpha</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1InArgs.html</anchorfile>
      <anchor>a1e5a4a0c6bb196f964e27463c9d920cd</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_beta</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1InArgs.html</anchorfile>
      <anchor>a80044e33b2426c96cea0939f943c92bb</anchor>
      <arglist>(double beta)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>get_beta</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1InArgs.html</anchorfile>
      <anchor>aff7a9a5377ffff438bc82f292ced23cc</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setArgs</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1InArgs.html</anchorfile>
      <anchor>a47ef9fef98bb3f93d7bcc28a1bf18203</anchor>
      <arglist>(const InArgs&lt; double &gt; &amp;inArgs, bool ignoreUnsupported=false, bool cloneObjects=false)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>assertSameSupport</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1InArgs.html</anchorfile>
      <anchor>a663cf4d1b3444fa684f9453448276462</anchor>
      <arglist>(const InArgs&lt; double &gt; &amp;inArgs) const</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>modelEvalDescription</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1InArgs.html</anchorfile>
      <anchor>a0b58c6c2b71ad98f6d3fa39594b78dd0</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>description</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1InArgs.html</anchorfile>
      <anchor>ae5d88c5c324015f2db45a0daf866f871</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>describe</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1InArgs.html</anchorfile>
      <anchor>aa4029b645f7dd0cd69c1ef399920c810</anchor>
      <arglist>(Teuchos::FancyOStream &amp;out, const Teuchos::EVerbosityLevel verbLevel) const</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>_setModelEvalDescription</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1InArgs.html</anchorfile>
      <anchor>af6c1c713f49e8b7f12002a9cd3940692</anchor>
      <arglist>(const std::string &amp;modelEvalDescription)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>_set_Np</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1InArgs.html</anchorfile>
      <anchor>aa4b4b3cebfa2c2d6c720239a82ad2fb0</anchor>
      <arglist>(int Np)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>_setSupports</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1InArgs.html</anchorfile>
      <anchor>af268545dd6bf9c722eda098135b8be72</anchor>
      <arglist>(EInArgsMembers arg, bool supports)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>_setSupports</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1InArgs.html</anchorfile>
      <anchor>a6cb78484aed09fb128873132a967f54b</anchor>
      <arglist>(EInArgs_p_mp arg, int l, bool supports)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>_setSupports</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1InArgs.html</anchorfile>
      <anchor>ab8d802a8af8db03416d9045015bd1741</anchor>
      <arglist>(const InArgs&lt; double &gt; &amp;inputInArgs, const int Np)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>_setUnsupportsAndRelated</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1InArgs.html</anchorfile>
      <anchor>a49a405c558e929d6323e787c60a65439</anchor>
      <arglist>(EInArgsMembers arg)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::ModelEvaluatorBase::InArgsSetup</name>
    <filename>classThyra_1_1ModelEvaluatorBase_1_1InArgsSetup.html</filename>
    <templarg>Scalar</templarg>
    <base>Thyra::ModelEvaluatorBase::InArgs</base>
    <member kind="function">
      <type></type>
      <name>InArgsSetup</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1InArgsSetup.html</anchorfile>
      <anchor>a2ccd41d116ef3fedbae9aa9b81c877ac</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>InArgsSetup</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1InArgsSetup.html</anchorfile>
      <anchor>aaac01220088721d721ca314e3d3fefb3</anchor>
      <arglist>(const InArgs&lt; Scalar &gt; &amp;)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setModelEvalDescription</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1InArgsSetup.html</anchorfile>
      <anchor>a04ea93dc57e980f21013678d0a16c84d</anchor>
      <arglist>(const std::string &amp;modelEvalDescription)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_Np</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1InArgsSetup.html</anchorfile>
      <anchor>af4f6b24a2d80a228729e21fa84a0d2cf</anchor>
      <arglist>(int Np)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setSupports</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1InArgsSetup.html</anchorfile>
      <anchor>aa69c7e01db73a03f9a9a1d04310f1661</anchor>
      <arglist>(EInArgsMembers arg, bool supports=true)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setSupports</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1InArgsSetup.html</anchorfile>
      <anchor>ac356d226916722588698a1b8156bde83</anchor>
      <arglist>(const InArgs&lt; Scalar &gt; &amp;inputInArgs, const int Np=-1)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setUnsupportsAndRelated</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1InArgsSetup.html</anchorfile>
      <anchor>a9c54b54a27366ae6f0dadff94c22b2e1</anchor>
      <arglist>(EInArgsMembers arg)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::Exceptions::IncompatibleVectorSpaces</name>
    <filename>classThyra_1_1Exceptions_1_1IncompatibleVectorSpaces.html</filename>
  </compound>
  <compound kind="class">
    <name>Thyra::InverseLinearOpBase</name>
    <filename>classThyra_1_1InverseLinearOpBase.html</filename>
    <templarg></templarg>
    <base virtualness="virtual">Thyra::LinearOpBase</base>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>isLowsConst</name>
      <anchorfile>classThyra_1_1InverseLinearOpBase.html</anchorfile>
      <anchor>acb0c1ef58feb545a081e8143fc5fe002</anchor>
      <arglist>() const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual Teuchos::RCP&lt; LinearOpWithSolveBase&lt; Scalar &gt; &gt;</type>
      <name>getNonconstLows</name>
      <anchorfile>classThyra_1_1InverseLinearOpBase.html</anchorfile>
      <anchor>a8a687f86e7378adde95c2ba689337a9e</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual Teuchos::RCP&lt; const LinearOpWithSolveBase&lt; Scalar &gt; &gt;</type>
      <name>getLows</name>
      <anchorfile>classThyra_1_1InverseLinearOpBase.html</anchorfile>
      <anchor>a08fb0ed8b353abf3379d8cd3eeac6472</anchor>
      <arglist>() const  =0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::LinearNonlinearSolver</name>
    <filename>classThyra_1_1LinearNonlinearSolver.html</filename>
    <templarg></templarg>
    <base>Thyra::NonlinearSolverBase</base>
    <member kind="function">
      <type>RCP&lt; LinearNonlinearSolver&lt; Scalar &gt; &gt;</type>
      <name>linearNonlinearSolver</name>
      <anchorfile>classThyra_1_1LinearNonlinearSolver.html</anchorfile>
      <anchor>ad32ea39a4ea049962f9067f6431841a0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setParameterList</name>
      <anchorfile>classThyra_1_1LinearNonlinearSolver.html</anchorfile>
      <anchor>a5948dc3c5d13c36c52994f86ba1b3da5</anchor>
      <arglist>(RCP&lt; Teuchos::ParameterList &gt; const &amp;paramList)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; Teuchos::ParameterList &gt;</type>
      <name>getNonconstParameterList</name>
      <anchorfile>classThyra_1_1LinearNonlinearSolver.html</anchorfile>
      <anchor>a8a6fb75261a4c6ac5612ff66112db894</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; Teuchos::ParameterList &gt;</type>
      <name>unsetParameterList</name>
      <anchorfile>classThyra_1_1LinearNonlinearSolver.html</anchorfile>
      <anchor>ab16ad7166dc45bb1e38af898d664d6ed</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const Teuchos::ParameterList &gt;</type>
      <name>getParameterList</name>
      <anchorfile>classThyra_1_1LinearNonlinearSolver.html</anchorfile>
      <anchor>a888570b1a43918443ffd32213abbff32</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const Teuchos::ParameterList &gt;</type>
      <name>getValidParameters</name>
      <anchorfile>classThyra_1_1LinearNonlinearSolver.html</anchorfile>
      <anchor>a8604bada062649ce5bd84fc7c5902c8c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setModel</name>
      <anchorfile>classThyra_1_1LinearNonlinearSolver.html</anchorfile>
      <anchor>a894572283590d6213aab96ad30615e77</anchor>
      <arglist>(const RCP&lt; const ModelEvaluator&lt; Scalar &gt; &gt; &amp;model)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const ModelEvaluator&lt; Scalar &gt; &gt;</type>
      <name>getModel</name>
      <anchorfile>classThyra_1_1LinearNonlinearSolver.html</anchorfile>
      <anchor>aa6f24b44e825b5f5df9a7e24ab3d3b97</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>SolveStatus&lt; Scalar &gt;</type>
      <name>solve</name>
      <anchorfile>classThyra_1_1LinearNonlinearSolver.html</anchorfile>
      <anchor>af9b3bfb99b95a230bb51073dbcbfd2f1</anchor>
      <arglist>(VectorBase&lt; Scalar &gt; *x, const SolveCriteria&lt; Scalar &gt; *solveCriteria, VectorBase&lt; Scalar &gt; *delta)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; LinearOpWithSolveBase&lt; Scalar &gt; &gt;</type>
      <name>get_nonconst_W</name>
      <anchorfile>classThyra_1_1LinearNonlinearSolver.html</anchorfile>
      <anchor>a12145a27de8a8c27fdfb89b0f1c7b473</anchor>
      <arglist>(const bool forceUpToDate)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const LinearOpWithSolveBase&lt; Scalar &gt; &gt;</type>
      <name>get_W</name>
      <anchorfile>classThyra_1_1LinearNonlinearSolver.html</anchorfile>
      <anchor>a263774d2bdf0c79833c48f65dda8da4b</anchor>
      <arglist>() const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::LinearOpBase</name>
    <filename>classThyra_1_1LinearOpBase.html</filename>
    <templarg>Scalar</templarg>
    <base virtualness="virtual">Teuchos::Describable</base>
    <member kind="function">
      <type>bool</type>
      <name>isFullyUninitialized</name>
      <anchorfile>classThyra_1_1LinearOpBase.html</anchorfile>
      <anchor>a8c90c875e27e48718aaa018e2090fa54</anchor>
      <arglist>(const LinearOpBase&lt; Scalar &gt; &amp;M)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isPartiallyInitialized</name>
      <anchorfile>classThyra_1_1LinearOpBase.html</anchorfile>
      <anchor>a21309edacdc04c7b6536ba95b65907ac</anchor>
      <arglist>(const LinearOpBase&lt; Scalar &gt; &amp;M)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isFullyInitialized</name>
      <anchorfile>classThyra_1_1LinearOpBase.html</anchorfile>
      <anchor>ad55d2aa42d688511157d1f3de49abcf8</anchor>
      <arglist>(const LinearOpBase&lt; Scalar &gt; &amp;M)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>opSupported</name>
      <anchorfile>classThyra_1_1LinearOpBase.html</anchorfile>
      <anchor>aecec644cadfef02ab02e8a9d00383ed0</anchor>
      <arglist>(const LinearOpBase&lt; Scalar &gt; &amp;M, EOpTransp M_trans)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>apply</name>
      <anchorfile>classThyra_1_1LinearOpBase.html</anchorfile>
      <anchor>a9ea459fec3e168d35dd994a240e0172c</anchor>
      <arglist>(const LinearOpBase&lt; Scalar &gt; &amp;M, const EOpTransp M_trans, const MultiVectorBase&lt; Scalar &gt; &amp;X, const Ptr&lt; MultiVectorBase&lt; Scalar &gt; &gt; &amp;Y, const Scalar alpha=static_cast&lt; Scalar &gt;(1.0), const Scalar beta=static_cast&lt; Scalar &gt;(0.0))</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>apply</name>
      <anchorfile>classThyra_1_1LinearOpBase.html</anchorfile>
      <anchor>adb1c5877f1454ea8c31347329018d522</anchor>
      <arglist>(const LinearOpBase&lt; double &gt; &amp;M, const EOpTransp M_trans, const MultiVectorBase&lt; double &gt; &amp;X, const Ptr&lt; MultiVectorBase&lt; double &gt; &gt; &amp;Y, const double alpha=1.0, const double beta=0.0)</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual RCP&lt; const VectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>range</name>
      <anchorfile>classThyra_1_1LinearOpBase.html</anchorfile>
      <anchor>ae5b3f51f2870d4aee80050b97e2aac05</anchor>
      <arglist>() const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual RCP&lt; const VectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>domain</name>
      <anchorfile>classThyra_1_1LinearOpBase.html</anchorfile>
      <anchor>a15dbb9dbf6662c2f01306b8a3669fb29</anchor>
      <arglist>() const  =0</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>opSupported</name>
      <anchorfile>classThyra_1_1LinearOpBase.html</anchorfile>
      <anchor>a2a7f314b861aec4b0615677bac8eb3ce</anchor>
      <arglist>(EOpTransp M_trans) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>apply</name>
      <anchorfile>classThyra_1_1LinearOpBase.html</anchorfile>
      <anchor>af0b01856896efa1963506fb2c004e813</anchor>
      <arglist>(const EOpTransp M_trans, const MultiVectorBase&lt; Scalar &gt; &amp;X, const Ptr&lt; MultiVectorBase&lt; Scalar &gt; &gt; &amp;Y, const Scalar alpha, const Scalar beta) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual RCP&lt; const LinearOpBase&lt; Scalar &gt; &gt;</type>
      <name>clone</name>
      <anchorfile>classThyra_1_1LinearOpBase.html</anchorfile>
      <anchor>a2e5e7c31077ba272b1e79d5696690a1b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual bool</type>
      <name>opSupportedImpl</name>
      <anchorfile>classThyra_1_1LinearOpBase.html</anchorfile>
      <anchor>ab29694443c63601323166fcf879d8666</anchor>
      <arglist>(EOpTransp M_trans) const  =0</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual void</type>
      <name>applyImpl</name>
      <anchorfile>classThyra_1_1LinearOpBase.html</anchorfile>
      <anchor>a0f2df1d7f6981bf0367fa0b847636b48</anchor>
      <arglist>(const EOpTransp M_trans, const MultiVectorBase&lt; Scalar &gt; &amp;X, const Ptr&lt; MultiVectorBase&lt; Scalar &gt; &gt; &amp;Y, const Scalar alpha, const Scalar beta) const  =0</arglist>
    </member>
    <docanchor file="classThyra_1_1LinearOpBase" title="Outline">Thyra_LO_outline_sec</docanchor>
    <docanchor file="classThyra_1_1LinearOpBase" title="Introduction">Thyra_LO_intro_sec</docanchor>
    <docanchor file="classThyra_1_1LinearOpBase" title="Range and domain spaces">Thyra_LO_spaces_sec</docanchor>
    <docanchor file="classThyra_1_1LinearOpBase" title="Scalar products and the adjoint relation">Thyra_LO_adjoint_relation_sec</docanchor>
    <docanchor file="classThyra_1_1LinearOpBase" title="Aliasing policy">Thyra_LO_aliasing_sec</docanchor>
    <docanchor file="classThyra_1_1LinearOpBase" title="Optional support for specific types of operator applications">Thyra_LO_optional_adjoints_sec</docanchor>
    <docanchor file="classThyra_1_1LinearOpBase" title="Testing LinearOpBase objects">Thyra_LO_testing_sec</docanchor>
    <docanchor file="classThyra_1_1LinearOpBase" title="Initialization states">Thyra_LO_initialization_sec</docanchor>
    <docanchor file="classThyra_1_1LinearOpBase" title="Notes for subclass developers">Thyra_LO_dev_notes_sec</docanchor>
  </compound>
  <compound kind="class">
    <name>LinearOpBase&lt; double &gt;</name>
    <filename>classThyra_1_1LinearOpBase.html</filename>
    <base virtualness="virtual">Teuchos::Describable</base>
    <member kind="function" virtualness="pure">
      <type>virtual RCP&lt; const VectorSpaceBase&lt; double &gt; &gt;</type>
      <name>range</name>
      <anchorfile>classThyra_1_1LinearOpBase.html</anchorfile>
      <anchor>ae5b3f51f2870d4aee80050b97e2aac05</anchor>
      <arglist>() const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual RCP&lt; const VectorSpaceBase&lt; double &gt; &gt;</type>
      <name>domain</name>
      <anchorfile>classThyra_1_1LinearOpBase.html</anchorfile>
      <anchor>a15dbb9dbf6662c2f01306b8a3669fb29</anchor>
      <arglist>() const  =0</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>opSupported</name>
      <anchorfile>classThyra_1_1LinearOpBase.html</anchorfile>
      <anchor>a2a7f314b861aec4b0615677bac8eb3ce</anchor>
      <arglist>(EOpTransp M_trans) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>apply</name>
      <anchorfile>classThyra_1_1LinearOpBase.html</anchorfile>
      <anchor>af0b01856896efa1963506fb2c004e813</anchor>
      <arglist>(const EOpTransp M_trans, const MultiVectorBase&lt; double &gt; &amp;X, const Ptr&lt; MultiVectorBase&lt; double &gt; &gt; &amp;Y, const double alpha, const double beta) const</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual RCP&lt; const LinearOpBase&lt; double &gt; &gt;</type>
      <name>clone</name>
      <anchorfile>classThyra_1_1LinearOpBase.html</anchorfile>
      <anchor>a2e5e7c31077ba272b1e79d5696690a1b</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual bool</type>
      <name>opSupportedImpl</name>
      <anchorfile>classThyra_1_1LinearOpBase.html</anchorfile>
      <anchor>ab29694443c63601323166fcf879d8666</anchor>
      <arglist>(EOpTransp M_trans) const  =0</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual void</type>
      <name>applyImpl</name>
      <anchorfile>classThyra_1_1LinearOpBase.html</anchorfile>
      <anchor>a0f2df1d7f6981bf0367fa0b847636b48</anchor>
      <arglist>(const EOpTransp M_trans, const MultiVectorBase&lt; double &gt; &amp;X, const Ptr&lt; MultiVectorBase&lt; double &gt; &gt; &amp;Y, const double alpha, const double beta) const  =0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::LinearOpChanger</name>
    <filename>classThyra_1_1LinearOpChanger.html</filename>
    <templarg>Scalar</templarg>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~LinearOpChanger</name>
      <anchorfile>classThyra_1_1LinearOpChanger.html</anchorfile>
      <anchor>a37fcbd6ea3231c2bec1b542beda691e3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>changeOp</name>
      <anchorfile>classThyra_1_1LinearOpChanger.html</anchorfile>
      <anchor>a32cd85c0f23e11c50bdad4157dcfdc8a</anchor>
      <arglist>(const Teuchos::Ptr&lt; LinearOpBase&lt; Scalar &gt; &gt; &amp;op) const  =0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::LinearOpDefaultBase</name>
    <filename>classThyra_1_1LinearOpDefaultBase.html</filename>
    <templarg></templarg>
    <base virtualness="virtual">Thyra::LinearOpBase</base>
    <member kind="function">
      <type>std::string</type>
      <name>description</name>
      <anchorfile>classThyra_1_1LinearOpDefaultBase.html</anchorfile>
      <anchor>ad9b758f8e26315369b29b784939dbe7e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>describe</name>
      <anchorfile>classThyra_1_1LinearOpDefaultBase.html</anchorfile>
      <anchor>a08d2f096bdb18d9cfdc196ce09a53650</anchor>
      <arglist>(Teuchos::FancyOStream &amp;out, const Teuchos::EVerbosityLevel verbLevel) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::LinearOpScalarProd</name>
    <filename>classThyra_1_1LinearOpScalarProd.html</filename>
    <templarg></templarg>
    <base>Thyra::ScalarProdBase</base>
    <member kind="function">
      <type></type>
      <name>LinearOpScalarProd</name>
      <anchorfile>classThyra_1_1LinearOpScalarProd.html</anchorfile>
      <anchor>a75e671ddd215d9a5a7e3c8a842b2d9b1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>LinearOpScalarProd</name>
      <anchorfile>classThyra_1_1LinearOpScalarProd.html</anchorfile>
      <anchor>a767326e7afef87b2dec7bc0a822b0de0</anchor>
      <arglist>(const RCP&lt; const LinearOpBase&lt; Scalar &gt; &gt; &amp;op)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initialize</name>
      <anchorfile>classThyra_1_1LinearOpScalarProd.html</anchorfile>
      <anchor>a9894cf0576894c048ad6b503d1f84010</anchor>
      <arglist>(const RCP&lt; const LinearOpBase&lt; Scalar &gt; &gt; &amp;op)</arglist>
    </member>
    <member kind="function">
      <type>const RCP&lt; const LinearOpBase&lt; Scalar &gt; &gt; &amp;</type>
      <name>op</name>
      <anchorfile>classThyra_1_1LinearOpScalarProd.html</anchorfile>
      <anchor>ae3b754d41dc11f9079ae0430bbdeb559</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>uninitialize</name>
      <anchorfile>classThyra_1_1LinearOpScalarProd.html</anchorfile>
      <anchor>a65c5d6045b3b7ea6c09941c4ddbe3bcb</anchor>
      <arglist>(const Ptr&lt; RCP&lt; const LinearOpBase&lt; Scalar &gt; &gt; &gt; &amp;op=Teuchos::null)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual bool</type>
      <name>isEuclideanImpl</name>
      <anchorfile>classThyra_1_1LinearOpScalarProd.html</anchorfile>
      <anchor>a246f79c9d5ee05d1971e4efb19f3b5da</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>scalarProdsImpl</name>
      <anchorfile>classThyra_1_1LinearOpScalarProd.html</anchorfile>
      <anchor>a2075dac7ed08c2cafc96d989ae2ea024</anchor>
      <arglist>(const MultiVectorBase&lt; Scalar &gt; &amp;X, const MultiVectorBase&lt; Scalar &gt; &amp;Y, const ArrayView&lt; Scalar &gt; &amp;scalarProds_out) const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>RCP&lt; const LinearOpBase&lt; Scalar &gt; &gt;</type>
      <name>getLinearOpImpl</name>
      <anchorfile>classThyra_1_1LinearOpScalarProd.html</anchorfile>
      <anchor>ae06a10e0f9857deea3d481cb906cd310</anchor>
      <arglist>() const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::LinearOpSourceBase</name>
    <filename>classThyra_1_1LinearOpSourceBase.html</filename>
    <templarg>Scalar</templarg>
    <base virtualness="virtual">Teuchos::Describable</base>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>isOpConst</name>
      <anchorfile>classThyra_1_1LinearOpSourceBase.html</anchorfile>
      <anchor>ad324f505af56472f1caca9a11f8c1979</anchor>
      <arglist>() const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual Teuchos::RCP&lt; LinearOpBase&lt; Scalar &gt; &gt;</type>
      <name>getNonconstOp</name>
      <anchorfile>classThyra_1_1LinearOpSourceBase.html</anchorfile>
      <anchor>ab650563eb5237f788cb5fce1df0872b3</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual Teuchos::RCP&lt; const LinearOpBase&lt; Scalar &gt; &gt;</type>
      <name>getOp</name>
      <anchorfile>classThyra_1_1LinearOpSourceBase.html</anchorfile>
      <anchor>a9bcaa0c70d6622a40f32a55388b33933</anchor>
      <arglist>() const  =0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::LinearOpTester</name>
    <filename>classThyra_1_1LinearOpTester.html</filename>
    <templarg>Scalar</templarg>
    <member kind="typedef">
      <type>Teuchos::ScalarTraits&lt; Scalar &gt;::magnitudeType</type>
      <name>ScalarMag</name>
      <anchorfile>classThyra_1_1LinearOpTester.html</anchorfile>
      <anchor>ac35ff437c42ce0cd9a4b677edf99c21d</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>LinearOpTester</name>
      <anchorfile>classThyra_1_1LinearOpTester.html</anchorfile>
      <anchor>a46f324ffe4238b5454a83ff0e0921d2a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classThyra_1_1LinearOpTester.html</anchorfile>
      <anchor>a115bde7c79c9e4ace52ea8614b3e9855</anchor>
      <arglist>(bool, check_linear_properties)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classThyra_1_1LinearOpTester.html</anchorfile>
      <anchor>acf11bcbffc3efe7e1b53de101620788e</anchor>
      <arglist>(ScalarMag, linear_properties_warning_tol)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classThyra_1_1LinearOpTester.html</anchorfile>
      <anchor>ad11096d51b99ffa4ca5ed19f130e22f9</anchor>
      <arglist>(ScalarMag, linear_properties_error_tol)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classThyra_1_1LinearOpTester.html</anchorfile>
      <anchor>a2baed1b448859e1975fb70b6b06f716b</anchor>
      <arglist>(bool, check_adjoint)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classThyra_1_1LinearOpTester.html</anchorfile>
      <anchor>a15e7d06136665a1cfac81c256df756ef</anchor>
      <arglist>(ScalarMag, adjoint_warning_tol)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classThyra_1_1LinearOpTester.html</anchorfile>
      <anchor>a491e5534e443c0ee95a6309c4a026751</anchor>
      <arglist>(ScalarMag, adjoint_error_tol)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classThyra_1_1LinearOpTester.html</anchorfile>
      <anchor>a76a084d59cda012796d69178020ebaf4</anchor>
      <arglist>(bool, check_for_symmetry)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classThyra_1_1LinearOpTester.html</anchorfile>
      <anchor>a6d1f029130f574966b614fc5ea668c7e</anchor>
      <arglist>(ScalarMag, symmetry_warning_tol)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classThyra_1_1LinearOpTester.html</anchorfile>
      <anchor>a3ceb7ab3b0b6368e16a37e106c568e34</anchor>
      <arglist>(ScalarMag, symmetry_error_tol)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classThyra_1_1LinearOpTester.html</anchorfile>
      <anchor>a628690256c15edbd6ffebb8892a014ce</anchor>
      <arglist>(int, num_random_vectors)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classThyra_1_1LinearOpTester.html</anchorfile>
      <anchor>a7a910d86f09e4035d42cbae0e1e2c6fe</anchor>
      <arglist>(bool, show_all_tests)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classThyra_1_1LinearOpTester.html</anchorfile>
      <anchor>afe06ac15741ac632e399c556e0f72f2f</anchor>
      <arglist>(bool, dump_all)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classThyra_1_1LinearOpTester.html</anchorfile>
      <anchor>a832bcb72df40738b91a3a3adfb70c2dc</anchor>
      <arglist>(int, num_rhs)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>enable_all_tests</name>
      <anchorfile>classThyra_1_1LinearOpTester.html</anchorfile>
      <anchor>a6e18acbcd6ad555aa3c530c204848ff2</anchor>
      <arglist>(const bool enable_all_tests)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_all_warning_tol</name>
      <anchorfile>classThyra_1_1LinearOpTester.html</anchorfile>
      <anchor>a6539021fb8c93d755401efb0d50cbebd</anchor>
      <arglist>(const ScalarMag warning_tol)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_all_error_tol</name>
      <anchorfile>classThyra_1_1LinearOpTester.html</anchorfile>
      <anchor>a7fca53f6fef0db1329ed4e8f5b763771</anchor>
      <arglist>(const ScalarMag error_tol)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>check</name>
      <anchorfile>classThyra_1_1LinearOpTester.html</anchorfile>
      <anchor>a7ae51f6efd59bb4b00001ec1bd63ab06</anchor>
      <arglist>(const LinearOpBase&lt; Scalar &gt; &amp;op, const Ptr&lt; MultiVectorRandomizerBase&lt; Scalar &gt; &gt; &amp;rangeRandomizer, const Ptr&lt; MultiVectorRandomizerBase&lt; Scalar &gt; &gt; &amp;domainRandomizer, const Ptr&lt; FancyOStream &gt; &amp;out) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>check</name>
      <anchorfile>classThyra_1_1LinearOpTester.html</anchorfile>
      <anchor>aa7bc1fb2304fbf84ee8134a2d970a405</anchor>
      <arglist>(const LinearOpBase&lt; Scalar &gt; &amp;op, const Ptr&lt; FancyOStream &gt; &amp;out) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>compare</name>
      <anchorfile>classThyra_1_1LinearOpTester.html</anchorfile>
      <anchor>aa13eef8777cb3f29eb8cd9417b70084a</anchor>
      <arglist>(const LinearOpBase&lt; Scalar &gt; &amp;op1, const LinearOpBase&lt; Scalar &gt; &amp;op2, const Ptr&lt; MultiVectorRandomizerBase&lt; Scalar &gt; &gt; &amp;domainRandomizer, const Ptr&lt; FancyOStream &gt; &amp;out_arg) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>compare</name>
      <anchorfile>classThyra_1_1LinearOpTester.html</anchorfile>
      <anchor>aeeece46b60e913c47678a623e463a432</anchor>
      <arglist>(const LinearOpBase&lt; Scalar &gt; &amp;op1, const LinearOpBase&lt; Scalar &gt; &amp;op2, const Ptr&lt; FancyOStream &gt; &amp;out_arg) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::LinearOpTransformerBase</name>
    <filename>classThyra_1_1LinearOpTransformerBase.html</filename>
    <templarg>Scalar</templarg>
    <base virtualness="virtual">Teuchos::Describable</base>
    <base virtualness="virtual">VerboseObject&lt; LinearOpTransformerBase&lt; Scalar &gt; &gt;</base>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>isCompatible</name>
      <anchorfile>classThyra_1_1LinearOpTransformerBase.html</anchorfile>
      <anchor>a441b2130818d7269e913c21cf704dda1</anchor>
      <arglist>(const LinearOpBase&lt; Scalar &gt; &amp;op_in) const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual RCP&lt; LinearOpBase&lt; Scalar &gt; &gt;</type>
      <name>createOutputOp</name>
      <anchorfile>classThyra_1_1LinearOpTransformerBase.html</anchorfile>
      <anchor>a9161eddbb8c6c474165aef398aa834ad</anchor>
      <arglist>() const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>transform</name>
      <anchorfile>classThyra_1_1LinearOpTransformerBase.html</anchorfile>
      <anchor>acfc12c9a60ad8154f97e3c794e6539b2</anchor>
      <arglist>(const LinearOpBase&lt; Scalar &gt; &amp;op_in, const Ptr&lt; LinearOpBase&lt; Scalar &gt; &gt; &amp;op_inout) const  =0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>LinearOpTransformerBase&lt; double &gt;</name>
    <filename>classThyra_1_1LinearOpTransformerBase.html</filename>
    <base virtualness="virtual">Teuchos::Describable</base>
    <base virtualness="virtual">VerboseObject&lt; LinearOpTransformerBase&lt; double &gt; &gt;</base>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>isCompatible</name>
      <anchorfile>classThyra_1_1LinearOpTransformerBase.html</anchorfile>
      <anchor>a441b2130818d7269e913c21cf704dda1</anchor>
      <arglist>(const LinearOpBase&lt; double &gt; &amp;op_in) const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual RCP&lt; LinearOpBase&lt; double &gt; &gt;</type>
      <name>createOutputOp</name>
      <anchorfile>classThyra_1_1LinearOpTransformerBase.html</anchorfile>
      <anchor>a9161eddbb8c6c474165aef398aa834ad</anchor>
      <arglist>() const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>transform</name>
      <anchorfile>classThyra_1_1LinearOpTransformerBase.html</anchorfile>
      <anchor>acfc12c9a60ad8154f97e3c794e6539b2</anchor>
      <arglist>(const LinearOpBase&lt; double &gt; &amp;op_in, const Ptr&lt; LinearOpBase&lt; double &gt; &gt; &amp;op_inout) const  =0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::LinearOpWithSolveBase</name>
    <filename>classThyra_1_1LinearOpWithSolveBase.html</filename>
    <templarg>Scalar</templarg>
    <base virtualness="virtual">Thyra::LinearOpBase</base>
    <base virtualness="virtual">VerboseObject&lt; LinearOpWithSolveBase&lt; Scalar &gt; &gt;</base>
    <member kind="function">
      <type>bool</type>
      <name>solveSupports</name>
      <anchorfile>classThyra_1_1LinearOpWithSolveBase.html</anchorfile>
      <anchor>a88adfc8e2fc32181864483b255308158</anchor>
      <arglist>(const LinearOpWithSolveBase&lt; Scalar &gt; &amp;A, const EOpTransp transp)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>solveSupports</name>
      <anchorfile>classThyra_1_1LinearOpWithSolveBase.html</anchorfile>
      <anchor>a52b5c5232054350210f1b8db8e4d8290</anchor>
      <arglist>(const LinearOpWithSolveBase&lt; Scalar &gt; &amp;A, const EOpTransp transp, const Ptr&lt; const SolveCriteria&lt; Scalar &gt; &gt; solveCriteria)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>solveSupportsSolveMeasureType</name>
      <anchorfile>classThyra_1_1LinearOpWithSolveBase.html</anchorfile>
      <anchor>a22ac7153bf1694e81a640e6959ae8358</anchor>
      <arglist>(const LinearOpWithSolveBase&lt; Scalar &gt; &amp;A, const EOpTransp transp, const SolveMeasureType &amp;solveMeasureType)</arglist>
    </member>
    <member kind="function">
      <type>SolveStatus&lt; Scalar &gt;</type>
      <name>solve</name>
      <anchorfile>classThyra_1_1LinearOpWithSolveBase.html</anchorfile>
      <anchor>a284237bd162e713dd732aab3f199f3b1</anchor>
      <arglist>(const LinearOpWithSolveBase&lt; Scalar &gt; &amp;A, const EOpTransp A_trans, const MultiVectorBase&lt; Scalar &gt; &amp;B, const Ptr&lt; MultiVectorBase&lt; Scalar &gt; &gt; &amp;X, const Ptr&lt; const SolveCriteria&lt; Scalar &gt; &gt; solveCriteria=Teuchos::null)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>assertSolveSupports</name>
      <anchorfile>classThyra_1_1LinearOpWithSolveBase.html</anchorfile>
      <anchor>abfb929e83913b64289fb3aeae4429ee3</anchor>
      <arglist>(const LinearOpWithSolveBase&lt; Scalar &gt; &amp;lows, const EOpTransp M_trans, const Ptr&lt; const SolveCriteria&lt; Scalar &gt; &gt; solveCriteria=Teuchos::null)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>solveSupports</name>
      <anchorfile>classThyra_1_1LinearOpWithSolveBase.html</anchorfile>
      <anchor>aadf3d5aca6a375303891b4240e6e4b79</anchor>
      <arglist>(EOpTransp transp) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>solveSupports</name>
      <anchorfile>classThyra_1_1LinearOpWithSolveBase.html</anchorfile>
      <anchor>ace7e2ef4ef5c75b7a29628dbcfc57482</anchor>
      <arglist>(EOpTransp transp, const Ptr&lt; const SolveCriteria&lt; Scalar &gt; &gt; solveCriteria) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>solveSupportsSolveMeasureType</name>
      <anchorfile>classThyra_1_1LinearOpWithSolveBase.html</anchorfile>
      <anchor>a584e314473929e996d7fcdb5e14d46a7</anchor>
      <arglist>(EOpTransp transp, const SolveMeasureType &amp;solveMeasureType) const </arglist>
    </member>
    <member kind="function">
      <type>SolveStatus&lt; Scalar &gt;</type>
      <name>solve</name>
      <anchorfile>classThyra_1_1LinearOpWithSolveBase.html</anchorfile>
      <anchor>ac7c5b4c8553833778e88e3fb627c4009</anchor>
      <arglist>(const EOpTransp A_trans, const MultiVectorBase&lt; Scalar &gt; &amp;B, const Ptr&lt; MultiVectorBase&lt; Scalar &gt; &gt; &amp;X, const Ptr&lt; const SolveCriteria&lt; Scalar &gt; &gt; solveCriteria=Teuchos::null) const </arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual bool</type>
      <name>solveSupportsImpl</name>
      <anchorfile>classThyra_1_1LinearOpWithSolveBase.html</anchorfile>
      <anchor>abad71735f5c2032de0d28a1b3921641f</anchor>
      <arglist>(EOpTransp transp) const </arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual bool</type>
      <name>solveSupportsNewImpl</name>
      <anchorfile>classThyra_1_1LinearOpWithSolveBase.html</anchorfile>
      <anchor>a2f72a7f9be5e695e38cf3670c0355127</anchor>
      <arglist>(EOpTransp transp, const Ptr&lt; const SolveCriteria&lt; Scalar &gt; &gt; solveCriteria) const </arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual bool</type>
      <name>solveSupportsSolveMeasureTypeImpl</name>
      <anchorfile>classThyra_1_1LinearOpWithSolveBase.html</anchorfile>
      <anchor>a6453c9128666205803235e8cdc5e1b71</anchor>
      <arglist>(EOpTransp transp, const SolveMeasureType &amp;solveMeasureType) const </arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual SolveStatus&lt; Scalar &gt;</type>
      <name>solveImpl</name>
      <anchorfile>classThyra_1_1LinearOpWithSolveBase.html</anchorfile>
      <anchor>a69e648493ece8982045b89bcd65c27c8</anchor>
      <arglist>(const EOpTransp transp, const MultiVectorBase&lt; Scalar &gt; &amp;B, const Ptr&lt; MultiVectorBase&lt; Scalar &gt; &gt; &amp;X, const Ptr&lt; const SolveCriteria&lt; Scalar &gt; &gt; solveCriteria) const  =0</arglist>
    </member>
    <docanchor file="classThyra_1_1LinearOpWithSolveBase" title="Outline">LOWSB_outline_sec</docanchor>
    <docanchor file="classThyra_1_1LinearOpWithSolveBase" title="Introduction">LOWSB_intro_sec</docanchor>
    <docanchor file="classThyra_1_1LinearOpWithSolveBase" title="Solve Criteria">LOWSB_solve_criteria_sec</docanchor>
    <docanchor file="classThyra_1_1LinearOpWithSolveBase" title="Solve Status">LOWSB_solve_status_sec</docanchor>
    <docanchor file="classThyra_1_1LinearOpWithSolveBase" title="Use cases">LOWSB_use_cases_sec</docanchor>
    <docanchor file="classThyra_1_1LinearOpWithSolveBase" title="Notes to subclass developers">LOWSB_developer_notes_sec</docanchor>
  </compound>
  <compound kind="class">
    <name>Thyra::LinearOpWithSolveFactoryBase</name>
    <filename>classThyra_1_1LinearOpWithSolveFactoryBase.html</filename>
    <templarg>Scalar</templarg>
    <base virtualness="virtual">Teuchos::Describable</base>
    <base virtualness="virtual">VerboseObject&lt; LinearOpWithSolveFactoryBase&lt; Scalar &gt; &gt;</base>
    <base virtualness="virtual">Teuchos::ParameterListAcceptor</base>
    <member kind="function">
      <type>bool</type>
      <name>isCompatible</name>
      <anchorfile>classThyra_1_1LinearOpWithSolveFactoryBase.html</anchorfile>
      <anchor>a022ee9efbe1c5ddda55ed0a6fb49265f</anchor>
      <arglist>(const LinearOpWithSolveFactoryBase&lt; Scalar &gt; &amp;lowsFactory, const LinearOpBase&lt; Scalar &gt; &amp;fwdOp)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setDefaultObjectLabel</name>
      <anchorfile>classThyra_1_1LinearOpWithSolveFactoryBase.html</anchorfile>
      <anchor>a20c68dfe3f9683e214eab8bb28569a16</anchor>
      <arglist>(const LinearOpBase&lt; Scalar &gt; &amp;fwdOp, const Ptr&lt; LinearOpWithSolveBase&lt; Scalar &gt; &gt; &amp;Op)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initializeOp</name>
      <anchorfile>classThyra_1_1LinearOpWithSolveFactoryBase.html</anchorfile>
      <anchor>a4a1ad3a5c97e09d7a48ca1d49c93c121</anchor>
      <arglist>(const LinearOpWithSolveFactoryBase&lt; Scalar &gt; &amp;lowsFactory, const RCP&lt; const LinearOpBase&lt; Scalar &gt; &gt; &amp;fwdOp, const Ptr&lt; LinearOpWithSolveBase&lt; Scalar &gt; &gt; &amp;Op, const ESupportSolveUse supportSolveUse=SUPPORT_SOLVE_UNSPECIFIED)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initializeAndReuseOp</name>
      <anchorfile>classThyra_1_1LinearOpWithSolveFactoryBase.html</anchorfile>
      <anchor>aa7415c12e220769165f8f1c8af83f7a0</anchor>
      <arglist>(const LinearOpWithSolveFactoryBase&lt; Scalar &gt; &amp;lowsFactory, const RCP&lt; const LinearOpBase&lt; Scalar &gt; &gt; &amp;fwdOp, const Ptr&lt; LinearOpWithSolveBase&lt; Scalar &gt; &gt; &amp;Op)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initializePreconditionedOp</name>
      <anchorfile>classThyra_1_1LinearOpWithSolveFactoryBase.html</anchorfile>
      <anchor>a72f4abc79f473e0b41c0c6971d64a795</anchor>
      <arglist>(const LinearOpWithSolveFactoryBase&lt; Scalar &gt; &amp;lowsFactory, const RCP&lt; const LinearOpBase&lt; Scalar &gt; &gt; &amp;fwdOp, const RCP&lt; const PreconditionerBase&lt; Scalar &gt; &gt; &amp;prec, const Ptr&lt; LinearOpWithSolveBase&lt; Scalar &gt; &gt; &amp;Op, const ESupportSolveUse supportSolveUse=SUPPORT_SOLVE_UNSPECIFIED)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initializeApproxPreconditionedOp</name>
      <anchorfile>classThyra_1_1LinearOpWithSolveFactoryBase.html</anchorfile>
      <anchor>a20f277c3f77c526094737c490d34b2d1</anchor>
      <arglist>(const LinearOpWithSolveFactoryBase&lt; Scalar &gt; &amp;lowsFactory, const RCP&lt; const LinearOpBase&lt; Scalar &gt; &gt; &amp;fwdOp, const RCP&lt; const LinearOpBase&lt; Scalar &gt; &gt; &amp;approxFwdOp, const Ptr&lt; LinearOpWithSolveBase&lt; Scalar &gt; &gt; &amp;Op, const ESupportSolveUse supportSolveUse=SUPPORT_SOLVE_UNSPECIFIED)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; LinearOpWithSolveBase&lt; Scalar &gt; &gt;</type>
      <name>linearOpWithSolve</name>
      <anchorfile>classThyra_1_1LinearOpWithSolveFactoryBase.html</anchorfile>
      <anchor>a3c7a64e9b91eaecea5025fec5a494573</anchor>
      <arglist>(const LinearOpWithSolveFactoryBase&lt; Scalar &gt; &amp;lowsFactory, const RCP&lt; const LinearOpBase&lt; Scalar &gt; &gt; &amp;fwdOp, const ESupportSolveUse supportSolveUse=SUPPORT_SOLVE_UNSPECIFIED)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; LinearOpBase&lt; Scalar &gt; &gt;</type>
      <name>inverse</name>
      <anchorfile>classThyra_1_1LinearOpWithSolveFactoryBase.html</anchorfile>
      <anchor>a0b7bef491ec0b97361e05572ffef1742</anchor>
      <arglist>(const LinearOpWithSolveFactoryBase&lt; Scalar &gt; &amp;LOWSF, const RCP&lt; const LinearOpBase&lt; Scalar &gt; &gt; &amp;fwdOp, const ESupportSolveUse supportSolveUse=SUPPORT_SOLVE_UNSPECIFIED, const Ptr&lt; const SolveCriteria&lt; Scalar &gt; &gt; &amp;fwdSolveCriteria=Teuchos::null, const EThrowOnSolveFailure throwOnFwdSolveFailure=THROW_ON_SOLVE_FAILURE, const Ptr&lt; const SolveCriteria&lt; Scalar &gt; &gt; &amp;adjSolveCriteria=Teuchos::null, const EThrowOnSolveFailure throwOnAdjSolveFailure=THROW_ON_SOLVE_FAILURE)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>uninitializeOp</name>
      <anchorfile>classThyra_1_1LinearOpWithSolveFactoryBase.html</anchorfile>
      <anchor>a72498e40f941e8db69cebd1008e5a02c</anchor>
      <arglist>(const LinearOpWithSolveFactoryBase&lt; Scalar &gt; &amp;lowsFactory, const Ptr&lt; LinearOpWithSolveBase&lt; Scalar &gt; &gt; &amp;Op, const Ptr&lt; RCP&lt; const LinearOpBase&lt; Scalar &gt; &gt; &gt; &amp;fwdOp=Teuchos::null, const Ptr&lt; RCP&lt; const PreconditionerBase&lt; Scalar &gt; &gt; &gt; &amp;prec=Teuchos::null, const Ptr&lt; RCP&lt; const LinearOpBase&lt; Scalar &gt; &gt; &gt; &amp;approxFwdOp=Teuchos::null, const Ptr&lt; ESupportSolveUse &gt; &amp;supportSolveUse=Teuchos::null)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>acceptsPreconditionerFactory</name>
      <anchorfile>classThyra_1_1LinearOpWithSolveFactoryBase.html</anchorfile>
      <anchor>aa5b07398430e6196901c9c611e4f0f01</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>setPreconditionerFactory</name>
      <anchorfile>classThyra_1_1LinearOpWithSolveFactoryBase.html</anchorfile>
      <anchor>a969c2fcfb097f00a5adbdb228d8989ae</anchor>
      <arglist>(const RCP&lt; PreconditionerFactoryBase&lt; Scalar &gt; &gt; &amp;precFactory, const std::string &amp;precFactoryName)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual RCP&lt; PreconditionerFactoryBase&lt; Scalar &gt; &gt;</type>
      <name>getPreconditionerFactory</name>
      <anchorfile>classThyra_1_1LinearOpWithSolveFactoryBase.html</anchorfile>
      <anchor>a5c83edfc61e686a5ba5288d6c6f1d160</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>unsetPreconditionerFactory</name>
      <anchorfile>classThyra_1_1LinearOpWithSolveFactoryBase.html</anchorfile>
      <anchor>a69545c5aaa56a53bebfeea054f2e8478</anchor>
      <arglist>(RCP&lt; PreconditionerFactoryBase&lt; Scalar &gt; &gt; *precFactory=NULL, std::string *precFactoryName=NULL)</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>isCompatible</name>
      <anchorfile>classThyra_1_1LinearOpWithSolveFactoryBase.html</anchorfile>
      <anchor>ae942f15b60b9fcbde269d15f2f13ed29</anchor>
      <arglist>(const LinearOpSourceBase&lt; Scalar &gt; &amp;fwdOpSrc) const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual RCP&lt; LinearOpWithSolveBase&lt; Scalar &gt; &gt;</type>
      <name>createOp</name>
      <anchorfile>classThyra_1_1LinearOpWithSolveFactoryBase.html</anchorfile>
      <anchor>a2a14f63b9cf56f2c4143511011c3f536</anchor>
      <arglist>() const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>initializeOp</name>
      <anchorfile>classThyra_1_1LinearOpWithSolveFactoryBase.html</anchorfile>
      <anchor>aea6cede1d96495f859551e9bd65c966e</anchor>
      <arglist>(const RCP&lt; const LinearOpSourceBase&lt; Scalar &gt; &gt; &amp;fwdOpSrc, LinearOpWithSolveBase&lt; Scalar &gt; *Op, const ESupportSolveUse supportSolveUse=SUPPORT_SOLVE_UNSPECIFIED) const  =0</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>initializeAndReuseOp</name>
      <anchorfile>classThyra_1_1LinearOpWithSolveFactoryBase.html</anchorfile>
      <anchor>a6bc710780b861d77a55495685044d973</anchor>
      <arglist>(const RCP&lt; const LinearOpSourceBase&lt; Scalar &gt; &gt; &amp;fwdOpSrc, LinearOpWithSolveBase&lt; Scalar &gt; *Op) const </arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>uninitializeOp</name>
      <anchorfile>classThyra_1_1LinearOpWithSolveFactoryBase.html</anchorfile>
      <anchor>abd242af9079f21055723ff271b0e473b</anchor>
      <arglist>(LinearOpWithSolveBase&lt; Scalar &gt; *Op, RCP&lt; const LinearOpSourceBase&lt; Scalar &gt; &gt; *fwdOpSrc=NULL, RCP&lt; const PreconditionerBase&lt; Scalar &gt; &gt; *prec=NULL, RCP&lt; const LinearOpSourceBase&lt; Scalar &gt; &gt; *approxFwdOpSrc=NULL, ESupportSolveUse *supportSolveUse=NULL) const  =0</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>supportsPreconditionerInputType</name>
      <anchorfile>classThyra_1_1LinearOpWithSolveFactoryBase.html</anchorfile>
      <anchor>a6f3e25e6ab51892c837c34271a08258b</anchor>
      <arglist>(const EPreconditionerInputType precOpType) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>initializePreconditionedOp</name>
      <anchorfile>classThyra_1_1LinearOpWithSolveFactoryBase.html</anchorfile>
      <anchor>ae9701e171d18977857f346249a8b93b5</anchor>
      <arglist>(const RCP&lt; const LinearOpSourceBase&lt; Scalar &gt; &gt; &amp;fwdOpSrc, const RCP&lt; const PreconditionerBase&lt; Scalar &gt; &gt; &amp;prec, LinearOpWithSolveBase&lt; Scalar &gt; *Op, const ESupportSolveUse supportSolveUse=SUPPORT_SOLVE_UNSPECIFIED) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>initializeApproxPreconditionedOp</name>
      <anchorfile>classThyra_1_1LinearOpWithSolveFactoryBase.html</anchorfile>
      <anchor>a7722c4c18343a4d019d56c085607fe50</anchor>
      <arglist>(const RCP&lt; const LinearOpSourceBase&lt; Scalar &gt; &gt; &amp;fwdOpSrc, const RCP&lt; const LinearOpSourceBase&lt; Scalar &gt; &gt; &amp;approxFwdOpSrc, LinearOpWithSolveBase&lt; Scalar &gt; *Op, const ESupportSolveUse supportSolveUse=SUPPORT_SOLVE_UNSPECIFIED) const </arglist>
    </member>
    <docanchor file="classThyra_1_1LinearOpWithSolveFactoryBase" title="Outline">LOWSFB_outline_sec</docanchor>
    <docanchor file="classThyra_1_1LinearOpWithSolveFactoryBase" title="Introduction">LOWSFB_intro_sec</docanchor>
    <docanchor file="classThyra_1_1LinearOpWithSolveFactoryBase" title="Use cases">LOWSFB_use_cases_sec</docanchor>
    <docanchor file="classThyra_1_1LinearOpWithSolveFactoryBase" title="Performing a single linear solve given a forward operator">LOWSFB_single_linear_solve_sec</docanchor>
    <docanchor file="classThyra_1_1LinearOpWithSolveFactoryBase" title="Creating invertible operators for scaled and/or adjoint forward operators">LOWSFB_scaled_adjoint_sec</docanchor>
    <docanchor file="classThyra_1_1LinearOpWithSolveFactoryBase" title="Updates of linear operator between linear solves">LOWSFB_updated_of_linear_op_sec</docanchor>
    <docanchor file="classThyra_1_1LinearOpWithSolveFactoryBase" title="Reuse of factorizations for small changes in the forward operator">LOWSFB_reuse_of_factorization_sec</docanchor>
    <docanchor file="classThyra_1_1LinearOpWithSolveFactoryBase" title="Updating the linear solver for major changes in the structure of the forward operator">LOWSFB_major_changes_in_op_sec</docanchor>
    <docanchor file="classThyra_1_1LinearOpWithSolveFactoryBase" title="Externally defined preconditioners">LOWSFB_external_prec_sec</docanchor>
    <docanchor file="classThyra_1_1LinearOpWithSolveFactoryBase" title="Use of externally defined preconditioner operators">LOWSFB_external_prec_op_sec</docanchor>
    <docanchor file="classThyra_1_1LinearOpWithSolveFactoryBase" title="The use of externally defined preconditioner matrices">LOWSFB_external_prec_mat_sec</docanchor>
    <docanchor file="classThyra_1_1LinearOpWithSolveFactoryBase" title="Reuse of externally defined preconditioner operators">LOWSFB_external_prec_op_reuse_sec</docanchor>
    <docanchor file="classThyra_1_1LinearOpWithSolveFactoryBase" title="Reuse of externally defined preconditioner matrices">LOWSFB_external_prec_mat_reuse_sec</docanchor>
    <docanchor file="classThyra_1_1LinearOpWithSolveFactoryBase" title="Output and verbosity">LOWSFB_verbosity_level_sec</docanchor>
    <docanchor file="classThyra_1_1LinearOpWithSolveFactoryBase" title="Notes to subclass developers">LOWSFB_developer_notes_sec</docanchor>
  </compound>
  <compound kind="class">
    <name>LinearOpWithSolveFactoryBase&lt; double &gt;</name>
    <filename>classThyra_1_1LinearOpWithSolveFactoryBase.html</filename>
    <base virtualness="virtual">Teuchos::Describable</base>
    <base virtualness="virtual">Teuchos::VerboseObject</base>
    <base virtualness="virtual">Teuchos::ParameterListAcceptor</base>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>acceptsPreconditionerFactory</name>
      <anchorfile>classThyra_1_1LinearOpWithSolveFactoryBase.html</anchorfile>
      <anchor>aa5b07398430e6196901c9c611e4f0f01</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>setPreconditionerFactory</name>
      <anchorfile>classThyra_1_1LinearOpWithSolveFactoryBase.html</anchorfile>
      <anchor>a969c2fcfb097f00a5adbdb228d8989ae</anchor>
      <arglist>(const RCP&lt; PreconditionerFactoryBase&lt; double &gt; &gt; &amp;precFactory, const std::string &amp;precFactoryName)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual RCP&lt; PreconditionerFactoryBase&lt; double &gt; &gt;</type>
      <name>getPreconditionerFactory</name>
      <anchorfile>classThyra_1_1LinearOpWithSolveFactoryBase.html</anchorfile>
      <anchor>a5c83edfc61e686a5ba5288d6c6f1d160</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>unsetPreconditionerFactory</name>
      <anchorfile>classThyra_1_1LinearOpWithSolveFactoryBase.html</anchorfile>
      <anchor>a69545c5aaa56a53bebfeea054f2e8478</anchor>
      <arglist>(RCP&lt; PreconditionerFactoryBase&lt; double &gt; &gt; *precFactory=NULL, std::string *precFactoryName=NULL)</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>isCompatible</name>
      <anchorfile>classThyra_1_1LinearOpWithSolveFactoryBase.html</anchorfile>
      <anchor>ae942f15b60b9fcbde269d15f2f13ed29</anchor>
      <arglist>(const LinearOpSourceBase&lt; double &gt; &amp;fwdOpSrc) const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual RCP&lt; LinearOpWithSolveBase&lt; double &gt; &gt;</type>
      <name>createOp</name>
      <anchorfile>classThyra_1_1LinearOpWithSolveFactoryBase.html</anchorfile>
      <anchor>a2a14f63b9cf56f2c4143511011c3f536</anchor>
      <arglist>() const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>initializeOp</name>
      <anchorfile>classThyra_1_1LinearOpWithSolveFactoryBase.html</anchorfile>
      <anchor>aea6cede1d96495f859551e9bd65c966e</anchor>
      <arglist>(const RCP&lt; const LinearOpSourceBase&lt; double &gt; &gt; &amp;fwdOpSrc, LinearOpWithSolveBase&lt; double &gt; *Op, const ESupportSolveUse supportSolveUse=SUPPORT_SOLVE_UNSPECIFIED) const  =0</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>initializeAndReuseOp</name>
      <anchorfile>classThyra_1_1LinearOpWithSolveFactoryBase.html</anchorfile>
      <anchor>a6bc710780b861d77a55495685044d973</anchor>
      <arglist>(const RCP&lt; const LinearOpSourceBase&lt; double &gt; &gt; &amp;fwdOpSrc, LinearOpWithSolveBase&lt; double &gt; *Op) const</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>uninitializeOp</name>
      <anchorfile>classThyra_1_1LinearOpWithSolveFactoryBase.html</anchorfile>
      <anchor>abd242af9079f21055723ff271b0e473b</anchor>
      <arglist>(LinearOpWithSolveBase&lt; double &gt; *Op, RCP&lt; const LinearOpSourceBase&lt; double &gt; &gt; *fwdOpSrc=NULL, RCP&lt; const PreconditionerBase&lt; double &gt; &gt; *prec=NULL, RCP&lt; const LinearOpSourceBase&lt; double &gt; &gt; *approxFwdOpSrc=NULL, ESupportSolveUse *supportSolveUse=NULL) const  =0</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>supportsPreconditionerInputType</name>
      <anchorfile>classThyra_1_1LinearOpWithSolveFactoryBase.html</anchorfile>
      <anchor>a6f3e25e6ab51892c837c34271a08258b</anchor>
      <arglist>(const EPreconditionerInputType precOpType) const</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>initializePreconditionedOp</name>
      <anchorfile>classThyra_1_1LinearOpWithSolveFactoryBase.html</anchorfile>
      <anchor>ae9701e171d18977857f346249a8b93b5</anchor>
      <arglist>(const RCP&lt; const LinearOpSourceBase&lt; double &gt; &gt; &amp;fwdOpSrc, const RCP&lt; const PreconditionerBase&lt; double &gt; &gt; &amp;prec, LinearOpWithSolveBase&lt; double &gt; *Op, const ESupportSolveUse supportSolveUse=SUPPORT_SOLVE_UNSPECIFIED) const</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>initializeApproxPreconditionedOp</name>
      <anchorfile>classThyra_1_1LinearOpWithSolveFactoryBase.html</anchorfile>
      <anchor>a7722c4c18343a4d019d56c085607fe50</anchor>
      <arglist>(const RCP&lt; const LinearOpSourceBase&lt; double &gt; &gt; &amp;fwdOpSrc, const RCP&lt; const LinearOpSourceBase&lt; double &gt; &gt; &amp;approxFwdOpSrc, LinearOpWithSolveBase&lt; double &gt; *Op, const ESupportSolveUse supportSolveUse=SUPPORT_SOLVE_UNSPECIFIED) const</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::LinearOpWithSolveTester</name>
    <filename>classThyra_1_1LinearOpWithSolveTester.html</filename>
    <templarg></templarg>
    <base virtualness="virtual">Teuchos::ParameterListAcceptorDefaultBase</base>
    <member kind="typedef">
      <type>Teuchos::ScalarTraits&lt; Scalar &gt;::magnitudeType</type>
      <name>ScalarMag</name>
      <anchorfile>classThyra_1_1LinearOpWithSolveTester.html</anchorfile>
      <anchor>a9e87da49679e01eeca806ead34fe6bbd</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>LinearOpWithSolveTester</name>
      <anchorfile>classThyra_1_1LinearOpWithSolveTester.html</anchorfile>
      <anchor>a76ec048ba33c343dcd4a1f72be4f55f7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classThyra_1_1LinearOpWithSolveTester.html</anchorfile>
      <anchor>adbadff514620bda2027f9aab186e846f</anchor>
      <arglist>(bool, check_forward_default)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classThyra_1_1LinearOpWithSolveTester.html</anchorfile>
      <anchor>aff2cdcbb9f5ee65ed94931d35a07bc98</anchor>
      <arglist>(ScalarMag, forward_default_residual_warning_tol)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classThyra_1_1LinearOpWithSolveTester.html</anchorfile>
      <anchor>a099fe8f8bb218eaa18bbd2f693665cce</anchor>
      <arglist>(ScalarMag, forward_default_residual_error_tol)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classThyra_1_1LinearOpWithSolveTester.html</anchorfile>
      <anchor>aa040cfd930945376510cbc1d60e8e11d</anchor>
      <arglist>(ScalarMag, forward_default_solution_error_warning_tol)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classThyra_1_1LinearOpWithSolveTester.html</anchorfile>
      <anchor>acf218d332e38d588575d0cb5a66cedc0</anchor>
      <arglist>(ScalarMag, forward_default_solution_error_error_tol)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classThyra_1_1LinearOpWithSolveTester.html</anchorfile>
      <anchor>ad59dc6cb9bc9ec0fcafb3801e97268f1</anchor>
      <arglist>(bool, check_forward_residual)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classThyra_1_1LinearOpWithSolveTester.html</anchorfile>
      <anchor>af15de593fcfcbea6532254d4a7cee7e6</anchor>
      <arglist>(ScalarMag, forward_residual_solve_tol)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classThyra_1_1LinearOpWithSolveTester.html</anchorfile>
      <anchor>a6fd35da7c0e86f5b65706d056196696c</anchor>
      <arglist>(ScalarMag, forward_residual_slack_warning_tol)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classThyra_1_1LinearOpWithSolveTester.html</anchorfile>
      <anchor>a0758e550acef1e8f8359ec5b92dc52dc</anchor>
      <arglist>(ScalarMag, forward_residual_slack_error_tol)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classThyra_1_1LinearOpWithSolveTester.html</anchorfile>
      <anchor>a235cb4cc5d581a13a9d96267a5c8b98f</anchor>
      <arglist>(bool, check_adjoint_default)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classThyra_1_1LinearOpWithSolveTester.html</anchorfile>
      <anchor>ae4201989101de6d74140820edcdf7cf0</anchor>
      <arglist>(ScalarMag, adjoint_default_residual_warning_tol)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classThyra_1_1LinearOpWithSolveTester.html</anchorfile>
      <anchor>acc0a519108b81cea8c3956a62d31d468</anchor>
      <arglist>(ScalarMag, adjoint_default_residual_error_tol)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classThyra_1_1LinearOpWithSolveTester.html</anchorfile>
      <anchor>a4872b02642fce845b976dd06c1517fe5</anchor>
      <arglist>(ScalarMag, adjoint_default_solution_error_warning_tol)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classThyra_1_1LinearOpWithSolveTester.html</anchorfile>
      <anchor>a5a0b7c502a855d4b1552e5d700c6cac5</anchor>
      <arglist>(ScalarMag, adjoint_default_solution_error_error_tol)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classThyra_1_1LinearOpWithSolveTester.html</anchorfile>
      <anchor>afc23b452cfe02c99d1581d8deffde31f</anchor>
      <arglist>(bool, check_adjoint_residual)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classThyra_1_1LinearOpWithSolveTester.html</anchorfile>
      <anchor>aa7b811a966d8cd8e7c06d141dfb7de99</anchor>
      <arglist>(ScalarMag, adjoint_residual_solve_tol)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classThyra_1_1LinearOpWithSolveTester.html</anchorfile>
      <anchor>a456b96bebde37d7f63ad9f35de1e14a0</anchor>
      <arglist>(ScalarMag, adjoint_residual_slack_warning_tol)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classThyra_1_1LinearOpWithSolveTester.html</anchorfile>
      <anchor>a1a9d61682341313de96a9e444edfe477</anchor>
      <arglist>(ScalarMag, adjoint_residual_slack_error_tol)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classThyra_1_1LinearOpWithSolveTester.html</anchorfile>
      <anchor>a9696ffcaa280c0f6a38cee9b61c927fe</anchor>
      <arglist>(int, num_random_vectors)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classThyra_1_1LinearOpWithSolveTester.html</anchorfile>
      <anchor>a2e9982995a33d1409f863ae5a55acf3c</anchor>
      <arglist>(bool, show_all_tests)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classThyra_1_1LinearOpWithSolveTester.html</anchorfile>
      <anchor>ad87807c2e7b0c77be687e0376b308d1d</anchor>
      <arglist>(bool, dump_all)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classThyra_1_1LinearOpWithSolveTester.html</anchorfile>
      <anchor>a5b44444ea48ee1308ad376b86333e4ae</anchor>
      <arglist>(int, num_rhs)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>turn_off_all_tests</name>
      <anchorfile>classThyra_1_1LinearOpWithSolveTester.html</anchorfile>
      <anchor>ad35a19ddc6bec5c5ee154cabd6cea20a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_all_solve_tol</name>
      <anchorfile>classThyra_1_1LinearOpWithSolveTester.html</anchorfile>
      <anchor>a758a468474d9e02e715acacb25af36a5</anchor>
      <arglist>(const ScalarMag solve_tol)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_all_slack_warning_tol</name>
      <anchorfile>classThyra_1_1LinearOpWithSolveTester.html</anchorfile>
      <anchor>a4e67e4df555ceb5ee670d5f25c0d8516</anchor>
      <arglist>(const ScalarMag slack_warning_tol)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_all_slack_error_tol</name>
      <anchorfile>classThyra_1_1LinearOpWithSolveTester.html</anchorfile>
      <anchor>ae68a998d7ba2375b33902684df44263d</anchor>
      <arglist>(const ScalarMag slack_error_tol)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setParameterList</name>
      <anchorfile>classThyra_1_1LinearOpWithSolveTester.html</anchorfile>
      <anchor>a098bc4836f9ed664b284b448498098c8</anchor>
      <arglist>(const RCP&lt; ParameterList &gt; &amp;paramList)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const ParameterList &gt;</type>
      <name>getValidParameters</name>
      <anchorfile>classThyra_1_1LinearOpWithSolveTester.html</anchorfile>
      <anchor>a2124d669b7603a6329603cc5e4c392d4</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>check</name>
      <anchorfile>classThyra_1_1LinearOpWithSolveTester.html</anchorfile>
      <anchor>acfadd43bffcc010ceb21773155006264</anchor>
      <arglist>(const LinearOpWithSolveBase&lt; Scalar &gt; &amp;op, Teuchos::FancyOStream *out) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::LinearSolverBuilderBase</name>
    <filename>classThyra_1_1LinearSolverBuilderBase.html</filename>
    <templarg>Scalar</templarg>
    <base virtualness="virtual">Teuchos::ParameterListAcceptor</base>
    <member kind="function" virtualness="pure">
      <type>virtual Teuchos::RCP&lt; LinearOpWithSolveFactoryBase&lt; Scalar &gt; &gt;</type>
      <name>createLinearSolveStrategy</name>
      <anchorfile>classThyra_1_1LinearSolverBuilderBase.html</anchorfile>
      <anchor>ad331321d1b5912af18b599fc00807c13</anchor>
      <arglist>(const std::string &amp;linearSolveStrategyName) const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual Teuchos::RCP&lt; PreconditionerFactoryBase&lt; Scalar &gt; &gt;</type>
      <name>createPreconditioningStrategy</name>
      <anchorfile>classThyra_1_1LinearSolverBuilderBase.html</anchorfile>
      <anchor>a13d17a3b6d9a48bfbd82bdc2271b95e0</anchor>
      <arglist>(const std::string &amp;preconditioningStrategyName) const  =0</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; LinearOpWithSolveFactoryBase&lt; Scalar &gt; &gt;</type>
      <name>createLinearSolveStrategy</name>
      <anchorfile>classThyra_1_1LinearSolverBuilderBase.html</anchorfile>
      <anchor>a6f7dd266f2730bd32621b381ddbe2ba8</anchor>
      <arglist>(const LinearSolverBuilderBase&lt; Scalar &gt; &amp;linearSolverBuilder, const std::string &amp;linearSolveStrategyName=&quot;&quot;)</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; PreconditionerFactoryBase&lt; Scalar &gt; &gt;</type>
      <name>createPreconditioningStrategy</name>
      <anchorfile>classThyra_1_1LinearSolverBuilderBase.html</anchorfile>
      <anchor>ab31b2dda4854690ae44b9449407c45c1</anchor>
      <arglist>(const LinearSolverBuilderBase&lt; Scalar &gt; &amp;linearSolverBuilder, const std::string &amp;preconditioningStrategyName=&quot;&quot;)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::ListedMultiVectorRandomizer</name>
    <filename>classThyra_1_1ListedMultiVectorRandomizer.html</filename>
    <templarg></templarg>
    <base>Thyra::MultiVectorRandomizerBase</base>
    <member kind="function">
      <type></type>
      <name>ListedMultiVectorRandomizer</name>
      <anchorfile>classThyra_1_1ListedMultiVectorRandomizer.html</anchorfile>
      <anchor>a5942cc562e96b1ce0a0d15c6d0333898</anchor>
      <arglist>(const Teuchos::RCP&lt; const MultiVectorBase&lt; Scalar &gt; &gt; multiVecs[], const int numMultiVecs)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initialize</name>
      <anchorfile>classThyra_1_1ListedMultiVectorRandomizer.html</anchorfile>
      <anchor>abd70663798fcc6805a4f32b77827c1a4</anchor>
      <arglist>(const Teuchos::RCP&lt; const MultiVectorBase&lt; Scalar &gt; &gt; multiVecs[], const int numMultiVecs)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isCompatible</name>
      <anchorfile>classThyra_1_1ListedMultiVectorRandomizer.html</anchorfile>
      <anchor>aa5b260e3830958571fe2d95d63041534</anchor>
      <arglist>(const VectorSpaceBase&lt; Scalar &gt; &amp;space) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::ModelEvaluator</name>
    <filename>classThyra_1_1ModelEvaluator.html</filename>
    <templarg>Scalar</templarg>
    <base>Thyra::ModelEvaluatorBase</base>
    <member kind="typedef">
      <type>Teuchos::ScalarTraits&lt; Scalar &gt;::magnitudeType</type>
      <name>ScalarMag</name>
      <anchorfile>classThyra_1_1ModelEvaluator.html</anchorfile>
      <anchor>a5d6a2998ef4219eea372e146f117ad37</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>Np</name>
      <anchorfile>classThyra_1_1ModelEvaluator.html</anchorfile>
      <anchor>a847c31b419f735de07168aeaa057adb7</anchor>
      <arglist>() const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>Ng</name>
      <anchorfile>classThyra_1_1ModelEvaluator.html</anchorfile>
      <anchor>a7940c3af499b74d7a0454e1aa5b172fb</anchor>
      <arglist>() const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual RCP&lt; const VectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>get_x_space</name>
      <anchorfile>classThyra_1_1ModelEvaluator.html</anchorfile>
      <anchor>a0f2bfae4ca8ca6786a8a2e390ccbc43e</anchor>
      <arglist>() const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual RCP&lt; const VectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>get_f_space</name>
      <anchorfile>classThyra_1_1ModelEvaluator.html</anchorfile>
      <anchor>a9788a602de6151190a71462b893ead3b</anchor>
      <arglist>() const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual RCP&lt; const VectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>get_p_space</name>
      <anchorfile>classThyra_1_1ModelEvaluator.html</anchorfile>
      <anchor>a7432fc1957d483e9fd8c418cd4cb3d10</anchor>
      <arglist>(int l) const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual RCP&lt; const Teuchos::Array&lt; std::string &gt; &gt;</type>
      <name>get_p_names</name>
      <anchorfile>classThyra_1_1ModelEvaluator.html</anchorfile>
      <anchor>a9dba8cf65458470729af1549c3f7b696</anchor>
      <arglist>(int l) const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual RCP&lt; const VectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>get_g_space</name>
      <anchorfile>classThyra_1_1ModelEvaluator.html</anchorfile>
      <anchor>aa54d04e8ee29f871b7376c8c5ebeb2a8</anchor>
      <arglist>(int j) const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual Teuchos::ArrayView&lt; const std::string &gt;</type>
      <name>get_g_names</name>
      <anchorfile>classThyra_1_1ModelEvaluator.html</anchorfile>
      <anchor>ad2cfbcb0021d8104a908b3e92b902572</anchor>
      <arglist>(int j) const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual ModelEvaluatorBase::InArgs&lt; Scalar &gt;</type>
      <name>getNominalValues</name>
      <anchorfile>classThyra_1_1ModelEvaluator.html</anchorfile>
      <anchor>a7bcb9359eaf7599fddf7756324f6ec72</anchor>
      <arglist>() const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual ModelEvaluatorBase::InArgs&lt; Scalar &gt;</type>
      <name>getLowerBounds</name>
      <anchorfile>classThyra_1_1ModelEvaluator.html</anchorfile>
      <anchor>acdded3b90f03710803264f3564408930</anchor>
      <arglist>() const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual ModelEvaluatorBase::InArgs&lt; Scalar &gt;</type>
      <name>getUpperBounds</name>
      <anchorfile>classThyra_1_1ModelEvaluator.html</anchorfile>
      <anchor>a205ef6a577b82df2809e9b4f3efa8b78</anchor>
      <arglist>() const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual RCP&lt; LinearOpWithSolveBase&lt; Scalar &gt; &gt;</type>
      <name>create_W</name>
      <anchorfile>classThyra_1_1ModelEvaluator.html</anchorfile>
      <anchor>a896e793c1f303a470092cbc053071fdf</anchor>
      <arglist>() const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual RCP&lt; LinearOpBase&lt; Scalar &gt; &gt;</type>
      <name>create_W_op</name>
      <anchorfile>classThyra_1_1ModelEvaluator.html</anchorfile>
      <anchor>a5276a69ab274477ed44a03823d7e39a5</anchor>
      <arglist>() const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual RCP&lt; PreconditionerBase&lt; Scalar &gt; &gt;</type>
      <name>create_W_prec</name>
      <anchorfile>classThyra_1_1ModelEvaluator.html</anchorfile>
      <anchor>ad3db9f740cf08536b550ab5ec807d621</anchor>
      <arglist>() const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual RCP&lt; LinearOpBase&lt; Scalar &gt; &gt;</type>
      <name>create_DfDp_op</name>
      <anchorfile>classThyra_1_1ModelEvaluator.html</anchorfile>
      <anchor>ae400d6a5a6bc6a715f9e8acb24967232</anchor>
      <arglist>(int l) const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual RCP&lt; LinearOpBase&lt; Scalar &gt; &gt;</type>
      <name>create_DgDx_dot_op</name>
      <anchorfile>classThyra_1_1ModelEvaluator.html</anchorfile>
      <anchor>ac8fc35f5436e5738663155779490c8ea</anchor>
      <arglist>(int j) const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual RCP&lt; LinearOpBase&lt; Scalar &gt; &gt;</type>
      <name>create_DgDx_op</name>
      <anchorfile>classThyra_1_1ModelEvaluator.html</anchorfile>
      <anchor>a80fe7020ac4b376dc174eaa2e6dd0a63</anchor>
      <arglist>(int j) const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual RCP&lt; LinearOpBase&lt; Scalar &gt; &gt;</type>
      <name>create_DgDp_op</name>
      <anchorfile>classThyra_1_1ModelEvaluator.html</anchorfile>
      <anchor>a4615710b88dedcb919b457e509723c07</anchor>
      <arglist>(int j, int l) const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual RCP&lt; const LinearOpWithSolveFactoryBase&lt; Scalar &gt; &gt;</type>
      <name>get_W_factory</name>
      <anchorfile>classThyra_1_1ModelEvaluator.html</anchorfile>
      <anchor>a9de740d771af40ff0bfb6e94276652fc</anchor>
      <arglist>() const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual ModelEvaluatorBase::InArgs&lt; Scalar &gt;</type>
      <name>createInArgs</name>
      <anchorfile>classThyra_1_1ModelEvaluator.html</anchorfile>
      <anchor>ab74862547d8693bd9d6434519cef80e2</anchor>
      <arglist>() const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual ModelEvaluatorBase::OutArgs&lt; Scalar &gt;</type>
      <name>createOutArgs</name>
      <anchorfile>classThyra_1_1ModelEvaluator.html</anchorfile>
      <anchor>a9c9facdaf928d0fbc133664654c5040d</anchor>
      <arglist>() const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>evalModel</name>
      <anchorfile>classThyra_1_1ModelEvaluator.html</anchorfile>
      <anchor>a422281e7837f29704d03eede4b152bee</anchor>
      <arglist>(const ModelEvaluatorBase::InArgs&lt; Scalar &gt; &amp;inArgs, const ModelEvaluatorBase::OutArgs&lt; Scalar &gt; &amp;outArgs) const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>reportFinalPoint</name>
      <anchorfile>classThyra_1_1ModelEvaluator.html</anchorfile>
      <anchor>a33f08cc44f9f44dee1c10a73e46918d0</anchor>
      <arglist>(const ModelEvaluatorBase::InArgs&lt; Scalar &gt; &amp;finalPoint, const bool wasSolved)=0</arglist>
    </member>
    <docanchor file="classThyra_1_1ModelEvaluator" title="Outline">Thyra_ME_outline_sec</docanchor>
    <docanchor file="classThyra_1_1ModelEvaluator" title="Introduction">Thyra_ME_intro_sec</docanchor>
    <docanchor file="classThyra_1_1ModelEvaluator" title="Examples of Abstract Problem Types">Thyra_ME_problem_types_sec</docanchor>
    <docanchor file="classThyra_1_1ModelEvaluator" title="Nonlinear Equations">Thyra_ME_nonlinear_equations_sec</docanchor>
    <docanchor file="classThyra_1_1ModelEvaluator" title="Explicit ODEs">Thyra_ME_explicit_ode_sec</docanchor>
    <docanchor file="classThyra_1_1ModelEvaluator" title="Implicit ODEs or DAEs">Thyra_ME_implicit_dae_sec</docanchor>
    <docanchor file="classThyra_1_1ModelEvaluator" title="Unconstrained optimization">Thyra_ME_unconstrained_optimization_sec</docanchor>
    <docanchor file="classThyra_1_1ModelEvaluator" title="Equality constrained optimization">Thyra_ME_equality_constrained_optimization_sec</docanchor>
    <docanchor file="classThyra_1_1ModelEvaluator" title="General constrained optimization">Thyra_ME_general_constrained_optimization_sec</docanchor>
    <docanchor file="classThyra_1_1ModelEvaluator" title="Function derivatives and sensitivities">Thyra_ME_derivatives_sec</docanchor>
    <docanchor file="classThyra_1_1ModelEvaluator" title="Nominal values">Thyra_ME_nominal_values_sec</docanchor>
    <docanchor file="classThyra_1_1ModelEvaluator" title="Variable and Function Bounds">Thyra_ME_bounds_sec</docanchor>
    <docanchor file="classThyra_1_1ModelEvaluator" title="Significance of Parameter Subvectors">Thyra_ME_param_subvectors_sec</docanchor>
    <docanchor file="classThyra_1_1ModelEvaluator" title="Failed evaluations">Thyra_ME_failed_evals_sec</docanchor>
    <docanchor file="classThyra_1_1ModelEvaluator" title="Inexact function evaluations">Thyra_ME_inexact_evals_sec</docanchor>
    <docanchor file="classThyra_1_1ModelEvaluator" title="Compile-Time and Run-Time Safety and Checking">Thyra_ME_checking_sec</docanchor>
    <docanchor file="classThyra_1_1ModelEvaluator" title="Notes to subclass developers">Thyra_ME_dev_notes_sec</docanchor>
  </compound>
  <compound kind="class">
    <name>ModelEvaluator&lt; double &gt;</name>
    <filename>classThyra_1_1ModelEvaluator.html</filename>
    <base>Thyra::ModelEvaluatorBase</base>
    <member kind="typedef">
      <type>Teuchos::ScalarTraits&lt; double &gt;::magnitudeType</type>
      <name>ScalarMag</name>
      <anchorfile>classThyra_1_1ModelEvaluator.html</anchorfile>
      <anchor>a5d6a2998ef4219eea372e146f117ad37</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>Np</name>
      <anchorfile>classThyra_1_1ModelEvaluator.html</anchorfile>
      <anchor>a847c31b419f735de07168aeaa057adb7</anchor>
      <arglist>() const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>Ng</name>
      <anchorfile>classThyra_1_1ModelEvaluator.html</anchorfile>
      <anchor>a7940c3af499b74d7a0454e1aa5b172fb</anchor>
      <arglist>() const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual RCP&lt; const VectorSpaceBase&lt; double &gt; &gt;</type>
      <name>get_x_space</name>
      <anchorfile>classThyra_1_1ModelEvaluator.html</anchorfile>
      <anchor>a0f2bfae4ca8ca6786a8a2e390ccbc43e</anchor>
      <arglist>() const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual RCP&lt; const VectorSpaceBase&lt; double &gt; &gt;</type>
      <name>get_f_space</name>
      <anchorfile>classThyra_1_1ModelEvaluator.html</anchorfile>
      <anchor>a9788a602de6151190a71462b893ead3b</anchor>
      <arglist>() const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual RCP&lt; const VectorSpaceBase&lt; double &gt; &gt;</type>
      <name>get_p_space</name>
      <anchorfile>classThyra_1_1ModelEvaluator.html</anchorfile>
      <anchor>a7432fc1957d483e9fd8c418cd4cb3d10</anchor>
      <arglist>(int l) const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual RCP&lt; const Teuchos::Array&lt; std::string &gt; &gt;</type>
      <name>get_p_names</name>
      <anchorfile>classThyra_1_1ModelEvaluator.html</anchorfile>
      <anchor>a9dba8cf65458470729af1549c3f7b696</anchor>
      <arglist>(int l) const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual RCP&lt; const VectorSpaceBase&lt; double &gt; &gt;</type>
      <name>get_g_space</name>
      <anchorfile>classThyra_1_1ModelEvaluator.html</anchorfile>
      <anchor>aa54d04e8ee29f871b7376c8c5ebeb2a8</anchor>
      <arglist>(int j) const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual Teuchos::ArrayView&lt; const std::string &gt;</type>
      <name>get_g_names</name>
      <anchorfile>classThyra_1_1ModelEvaluator.html</anchorfile>
      <anchor>ad2cfbcb0021d8104a908b3e92b902572</anchor>
      <arglist>(int j) const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual ModelEvaluatorBase::InArgs&lt; double &gt;</type>
      <name>getNominalValues</name>
      <anchorfile>classThyra_1_1ModelEvaluator.html</anchorfile>
      <anchor>a7bcb9359eaf7599fddf7756324f6ec72</anchor>
      <arglist>() const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual ModelEvaluatorBase::InArgs&lt; double &gt;</type>
      <name>getLowerBounds</name>
      <anchorfile>classThyra_1_1ModelEvaluator.html</anchorfile>
      <anchor>acdded3b90f03710803264f3564408930</anchor>
      <arglist>() const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual ModelEvaluatorBase::InArgs&lt; double &gt;</type>
      <name>getUpperBounds</name>
      <anchorfile>classThyra_1_1ModelEvaluator.html</anchorfile>
      <anchor>a205ef6a577b82df2809e9b4f3efa8b78</anchor>
      <arglist>() const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual RCP&lt; LinearOpWithSolveBase&lt; double &gt; &gt;</type>
      <name>create_W</name>
      <anchorfile>classThyra_1_1ModelEvaluator.html</anchorfile>
      <anchor>a896e793c1f303a470092cbc053071fdf</anchor>
      <arglist>() const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual RCP&lt; LinearOpBase&lt; double &gt; &gt;</type>
      <name>create_W_op</name>
      <anchorfile>classThyra_1_1ModelEvaluator.html</anchorfile>
      <anchor>a5276a69ab274477ed44a03823d7e39a5</anchor>
      <arglist>() const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual RCP&lt; PreconditionerBase&lt; double &gt; &gt;</type>
      <name>create_W_prec</name>
      <anchorfile>classThyra_1_1ModelEvaluator.html</anchorfile>
      <anchor>ad3db9f740cf08536b550ab5ec807d621</anchor>
      <arglist>() const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual RCP&lt; LinearOpBase&lt; double &gt; &gt;</type>
      <name>create_DfDp_op</name>
      <anchorfile>classThyra_1_1ModelEvaluator.html</anchorfile>
      <anchor>ae400d6a5a6bc6a715f9e8acb24967232</anchor>
      <arglist>(int l) const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual RCP&lt; LinearOpBase&lt; double &gt; &gt;</type>
      <name>create_DgDx_dot_op</name>
      <anchorfile>classThyra_1_1ModelEvaluator.html</anchorfile>
      <anchor>ac8fc35f5436e5738663155779490c8ea</anchor>
      <arglist>(int j) const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual RCP&lt; LinearOpBase&lt; double &gt; &gt;</type>
      <name>create_DgDx_op</name>
      <anchorfile>classThyra_1_1ModelEvaluator.html</anchorfile>
      <anchor>a80fe7020ac4b376dc174eaa2e6dd0a63</anchor>
      <arglist>(int j) const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual RCP&lt; LinearOpBase&lt; double &gt; &gt;</type>
      <name>create_DgDp_op</name>
      <anchorfile>classThyra_1_1ModelEvaluator.html</anchorfile>
      <anchor>a4615710b88dedcb919b457e509723c07</anchor>
      <arglist>(int j, int l) const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual RCP&lt; const LinearOpWithSolveFactoryBase&lt; double &gt; &gt;</type>
      <name>get_W_factory</name>
      <anchorfile>classThyra_1_1ModelEvaluator.html</anchorfile>
      <anchor>a9de740d771af40ff0bfb6e94276652fc</anchor>
      <arglist>() const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual ModelEvaluatorBase::InArgs&lt; double &gt;</type>
      <name>createInArgs</name>
      <anchorfile>classThyra_1_1ModelEvaluator.html</anchorfile>
      <anchor>ab74862547d8693bd9d6434519cef80e2</anchor>
      <arglist>() const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual ModelEvaluatorBase::OutArgs&lt; double &gt;</type>
      <name>createOutArgs</name>
      <anchorfile>classThyra_1_1ModelEvaluator.html</anchorfile>
      <anchor>a9c9facdaf928d0fbc133664654c5040d</anchor>
      <arglist>() const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>evalModel</name>
      <anchorfile>classThyra_1_1ModelEvaluator.html</anchorfile>
      <anchor>a422281e7837f29704d03eede4b152bee</anchor>
      <arglist>(const ModelEvaluatorBase::InArgs&lt; double &gt; &amp;inArgs, const ModelEvaluatorBase::OutArgs&lt; double &gt; &amp;outArgs) const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>reportFinalPoint</name>
      <anchorfile>classThyra_1_1ModelEvaluator.html</anchorfile>
      <anchor>a33f08cc44f9f44dee1c10a73e46918d0</anchor>
      <arglist>(const ModelEvaluatorBase::InArgs&lt; double &gt; &amp;finalPoint, const bool wasSolved)=0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::ModelEvaluatorBase</name>
    <filename>classThyra_1_1ModelEvaluatorBase.html</filename>
    <base virtualness="virtual">Teuchos::Describable</base>
    <base virtualness="virtual">VerboseObject&lt; ModelEvaluatorBase &gt;</base>
    <class kind="class">Thyra::ModelEvaluatorBase::Derivative</class>
    <class kind="class">Thyra::ModelEvaluatorBase::DerivativeMultiVector</class>
    <class kind="struct">Thyra::ModelEvaluatorBase::DerivativeProperties</class>
    <class kind="class">Thyra::ModelEvaluatorBase::DerivativeSupport</class>
    <class kind="class">Thyra::ModelEvaluatorBase::Evaluation</class>
    <class kind="class">Thyra::ModelEvaluatorBase::InArgs</class>
    <class kind="class">Thyra::ModelEvaluatorBase::InArgsSetup</class>
    <class kind="class">Thyra::ModelEvaluatorBase::MPDerivative</class>
    <class kind="class">Thyra::ModelEvaluatorBase::MPDerivativeMultiVector</class>
    <class kind="class">Thyra::ModelEvaluatorBase::OutArgs</class>
    <class kind="class">Thyra::ModelEvaluatorBase::OutArgsSetup</class>
    <member kind="enumvalue">
      <name>IN_ARG_x_dot</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase.html</anchorfile>
      <anchor>a156d30e081cbe668b0e82d6c2be4bb6ea743dcd606dce26c3e1897f76892c1e70</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IN_ARG_x</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase.html</anchorfile>
      <anchor>a156d30e081cbe668b0e82d6c2be4bb6eaa8aaf0eeaabcc8276bfb53b4121aa1da</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IN_ARG_x_dot_poly</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase.html</anchorfile>
      <anchor>a156d30e081cbe668b0e82d6c2be4bb6ea9082f998f53b1df84fbac00cdbddf587</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IN_ARG_x_poly</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase.html</anchorfile>
      <anchor>a156d30e081cbe668b0e82d6c2be4bb6ea68d8d960cfffb80c235932303ef503f9</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IN_ARG_x_dot_mp</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase.html</anchorfile>
      <anchor>a156d30e081cbe668b0e82d6c2be4bb6ea46e5227f1b7cc2796f7a0fbfac4810d1</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IN_ARG_x_mp</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase.html</anchorfile>
      <anchor>a156d30e081cbe668b0e82d6c2be4bb6ea294d29a5d2cca5a5fbde53263aae4934</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IN_ARG_t</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase.html</anchorfile>
      <anchor>a156d30e081cbe668b0e82d6c2be4bb6ea9f9dcd1618f60b9e0659347825edae9a</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IN_ARG_alpha</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase.html</anchorfile>
      <anchor>a156d30e081cbe668b0e82d6c2be4bb6ea3327f53a0d017a44d0959271b52a1f2e</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IN_ARG_beta</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase.html</anchorfile>
      <anchor>a156d30e081cbe668b0e82d6c2be4bb6eada948f2ed5809dd2959224ff98f4c5bd</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IN_ARG_p_mp</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase.html</anchorfile>
      <anchor>a45f33828e914f8c4ddfcb1f1f0b0e3e3a39f5c0f5bb7055efce9164db0069b3a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>EVAL_TYPE_APPROX_DERIV</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase.html</anchorfile>
      <anchor>afb87d28d5824c98a7fa2301771725f6bab7eede7038320032d8e4fbbcee5bc7ad</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>EVAL_TYPE_VERY_APPROX_DERIV</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase.html</anchorfile>
      <anchor>afb87d28d5824c98a7fa2301771725f6bad647595ec19279d20849c24234b547e5</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>DERIV_MV_JACOBIAN_FORM</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase.html</anchorfile>
      <anchor>a92f977c9a4aba128536bfd79d76b60c6aba698ff5788e87e2ef6fe1dffbf8d6e5</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>DERIV_MV_GRADIENT_FORM</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase.html</anchorfile>
      <anchor>a92f977c9a4aba128536bfd79d76b60c6a9286bac99d7b796c9208a1e6436570b3</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>DERIV_MV_BY_COL</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase.html</anchorfile>
      <anchor>a92f977c9a4aba128536bfd79d76b60c6a335c65d259566cba21a03058de527274</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>DERIV_TRANS_MV_BY_ROW</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase.html</anchorfile>
      <anchor>a92f977c9a4aba128536bfd79d76b60c6ae8fd5a234fda2322f38d61b2e4221571</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>DERIV_LINEAR_OP</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase.html</anchorfile>
      <anchor>adfd603025401490b224e994e2cce5abea2832a60aaac3aa4e546386e1dfe6d594</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>DERIV_LINEARITY_UNKNOWN</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase.html</anchorfile>
      <anchor>a21f9486b9ef44229939ffd9743bd49b6af102507a53f2a0485e32d4234f691683</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>DERIV_LINEARITY_CONST</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase.html</anchorfile>
      <anchor>a21f9486b9ef44229939ffd9743bd49b6a632b83e86d94b497e65eb5e29251d594</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>DERIV_LINEARITY_NONCONST</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase.html</anchorfile>
      <anchor>a21f9486b9ef44229939ffd9743bd49b6abd778cd64d0dded92acc5e506cccaffb</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>DERIV_RANK_UNKNOWN</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase.html</anchorfile>
      <anchor>ab6e7d271b38f0a1035c41ecc2682d914a3cee8701b46689107e68807a2e189b62</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>DERIV_RANK_FULL</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase.html</anchorfile>
      <anchor>ab6e7d271b38f0a1035c41ecc2682d914a618f1399ff8b4ef896bb52ed2a6eee74</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>DERIV_RANK_DEFICIENT</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase.html</anchorfile>
      <anchor>ab6e7d271b38f0a1035c41ecc2682d914ab4bd239ad445f7132c5503ef4ab6074b</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>OUT_ARG_f</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase.html</anchorfile>
      <anchor>a0dcb168274ca26954a0b3ff74bc185b2a739cd09c2f8914c78ba9b954bd0402e8</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>OUT_ARG_W</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase.html</anchorfile>
      <anchor>a0dcb168274ca26954a0b3ff74bc185b2a7edd7ee918e069e79f7048fcfb078d71</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>OUT_ARG_f_mp</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase.html</anchorfile>
      <anchor>a0dcb168274ca26954a0b3ff74bc185b2a6f26cf9e69d1fad3b8518c7b34596178</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>OUT_ARG_W_mp</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase.html</anchorfile>
      <anchor>a0dcb168274ca26954a0b3ff74bc185b2a84855f135253f69da52b11b72e17841f</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>OUT_ARG_W_op</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase.html</anchorfile>
      <anchor>a0dcb168274ca26954a0b3ff74bc185b2a47fd06e2e5e1c849d6a4b13ecdb70734</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>OUT_ARG_W_prec</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase.html</anchorfile>
      <anchor>a0dcb168274ca26954a0b3ff74bc185b2a741e58dcd8fe23f7c9d032e97d5a69a5</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>OUT_ARG_f_poly</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase.html</anchorfile>
      <anchor>a0dcb168274ca26954a0b3ff74bc185b2a34a9714884b030000695dbc43dc2bc12</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>OUT_ARG_DfDp</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase.html</anchorfile>
      <anchor>a951e2b8929bd0bb3cf0e9490ab1fee38ab3cd7737279ab11bd3f013b886cd5136</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>OUT_ARG_DgDx_dot</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase.html</anchorfile>
      <anchor>a6c25884d96f08af141a0f1b85aac0098a3d0410d00d4ee4bd6799bac9ed6a0296</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>OUT_ARG_DgDx</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase.html</anchorfile>
      <anchor>a121758676313420c50c9d8a418e3b1bca73ff2ddae6b4e7eab87640124fcba56c</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>OUT_ARG_DgDp</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase.html</anchorfile>
      <anchor>a9ab460861d43621a1a39e6096827d94aadff6a21a0fcb880192e3ccba98ab1949</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>OUT_ARG_DfDp_mp</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase.html</anchorfile>
      <anchor>a5522d788df5430fa4d426a0bec89f913a685506aab9241a852f388564ba560056</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>OUT_ARG_g_mp</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase.html</anchorfile>
      <anchor>a3e6117306931033b175b0015fc0c945baafbe9fcf811a0731f7f4ad25557b19a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>OUT_ARG_DgDx_dot_mp</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase.html</anchorfile>
      <anchor>ae7c674aeebf278ed23d0cc6f4923bbeeadc00bd142ab2c02d63bc03a1ba50a879</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>OUT_ARG_DgDx_mp</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase.html</anchorfile>
      <anchor>a556df16951a2f4b1d6a7d7181f89e12aaabafb1cd6d8dd101f1b7ef2caf02a2fc</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>OUT_ARG_DgDp_mp</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase.html</anchorfile>
      <anchor>aa173a79d547ccfa58ec3de9d05a6bc9ea641c550f1103e4a6cbebca8f54e5e4e5</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>toString</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase.html</anchorfile>
      <anchor>af0ae07441eb48fbc6cad9c62c3af35c4</anchor>
      <arglist>(ModelEvaluatorBase::EInArgsMembers)</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>toString</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase.html</anchorfile>
      <anchor>a68ff88bb8efc5decb26d6a2b3101ab37</anchor>
      <arglist>(ModelEvaluatorBase::EOutArgsMembers)</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>toString</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase.html</anchorfile>
      <anchor>a5880f816b92ef33d12b4031ac35baea8</anchor>
      <arglist>(ModelEvaluatorBase::EDerivativeMultiVectorOrientation orientation)</arglist>
    </member>
    <member kind="function">
      <type>ModelEvaluatorBase::EDerivativeMultiVectorOrientation</type>
      <name>getOtherDerivativeMultiVectorOrientation</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase.html</anchorfile>
      <anchor>a28355e8e8acd60fabb29b771e4deab73</anchor>
      <arglist>(ModelEvaluatorBase::EDerivativeMultiVectorOrientation orientation)</arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>EInArgsMembers</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase.html</anchorfile>
      <anchor>a156d30e081cbe668b0e82d6c2be4bb6e</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IN_ARG_x_dot</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase.html</anchorfile>
      <anchor>a156d30e081cbe668b0e82d6c2be4bb6ea743dcd606dce26c3e1897f76892c1e70</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IN_ARG_x</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase.html</anchorfile>
      <anchor>a156d30e081cbe668b0e82d6c2be4bb6eaa8aaf0eeaabcc8276bfb53b4121aa1da</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IN_ARG_x_dot_poly</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase.html</anchorfile>
      <anchor>a156d30e081cbe668b0e82d6c2be4bb6ea9082f998f53b1df84fbac00cdbddf587</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IN_ARG_x_poly</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase.html</anchorfile>
      <anchor>a156d30e081cbe668b0e82d6c2be4bb6ea68d8d960cfffb80c235932303ef503f9</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IN_ARG_x_dot_mp</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase.html</anchorfile>
      <anchor>a156d30e081cbe668b0e82d6c2be4bb6ea46e5227f1b7cc2796f7a0fbfac4810d1</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IN_ARG_x_mp</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase.html</anchorfile>
      <anchor>a156d30e081cbe668b0e82d6c2be4bb6ea294d29a5d2cca5a5fbde53263aae4934</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IN_ARG_t</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase.html</anchorfile>
      <anchor>a156d30e081cbe668b0e82d6c2be4bb6ea9f9dcd1618f60b9e0659347825edae9a</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IN_ARG_alpha</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase.html</anchorfile>
      <anchor>a156d30e081cbe668b0e82d6c2be4bb6ea3327f53a0d017a44d0959271b52a1f2e</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IN_ARG_beta</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase.html</anchorfile>
      <anchor>a156d30e081cbe668b0e82d6c2be4bb6eada948f2ed5809dd2959224ff98f4c5bd</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>EInArgs_p_mp</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase.html</anchorfile>
      <anchor>a45f33828e914f8c4ddfcb1f1f0b0e3e3</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IN_ARG_p_mp</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase.html</anchorfile>
      <anchor>a45f33828e914f8c4ddfcb1f1f0b0e3e3a39f5c0f5bb7055efce9164db0069b3a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>EEvalType</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase.html</anchorfile>
      <anchor>afb87d28d5824c98a7fa2301771725f6b</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>EVAL_TYPE_APPROX_DERIV</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase.html</anchorfile>
      <anchor>afb87d28d5824c98a7fa2301771725f6bab7eede7038320032d8e4fbbcee5bc7ad</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>EVAL_TYPE_VERY_APPROX_DERIV</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase.html</anchorfile>
      <anchor>afb87d28d5824c98a7fa2301771725f6bad647595ec19279d20849c24234b547e5</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>EDerivativeMultiVectorOrientation</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase.html</anchorfile>
      <anchor>a92f977c9a4aba128536bfd79d76b60c6</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>DERIV_MV_JACOBIAN_FORM</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase.html</anchorfile>
      <anchor>a92f977c9a4aba128536bfd79d76b60c6aba698ff5788e87e2ef6fe1dffbf8d6e5</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>DERIV_MV_GRADIENT_FORM</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase.html</anchorfile>
      <anchor>a92f977c9a4aba128536bfd79d76b60c6a9286bac99d7b796c9208a1e6436570b3</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>DERIV_MV_BY_COL</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase.html</anchorfile>
      <anchor>a92f977c9a4aba128536bfd79d76b60c6a335c65d259566cba21a03058de527274</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>DERIV_TRANS_MV_BY_ROW</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase.html</anchorfile>
      <anchor>a92f977c9a4aba128536bfd79d76b60c6ae8fd5a234fda2322f38d61b2e4221571</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>EDerivativeLinearOp</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase.html</anchorfile>
      <anchor>adfd603025401490b224e994e2cce5abe</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>DERIV_LINEAR_OP</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase.html</anchorfile>
      <anchor>adfd603025401490b224e994e2cce5abea2832a60aaac3aa4e546386e1dfe6d594</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>EDerivativeLinearity</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase.html</anchorfile>
      <anchor>a21f9486b9ef44229939ffd9743bd49b6</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>DERIV_LINEARITY_UNKNOWN</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase.html</anchorfile>
      <anchor>a21f9486b9ef44229939ffd9743bd49b6af102507a53f2a0485e32d4234f691683</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>DERIV_LINEARITY_CONST</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase.html</anchorfile>
      <anchor>a21f9486b9ef44229939ffd9743bd49b6a632b83e86d94b497e65eb5e29251d594</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>DERIV_LINEARITY_NONCONST</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase.html</anchorfile>
      <anchor>a21f9486b9ef44229939ffd9743bd49b6abd778cd64d0dded92acc5e506cccaffb</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>ERankStatus</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase.html</anchorfile>
      <anchor>ab6e7d271b38f0a1035c41ecc2682d914</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>DERIV_RANK_UNKNOWN</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase.html</anchorfile>
      <anchor>ab6e7d271b38f0a1035c41ecc2682d914a3cee8701b46689107e68807a2e189b62</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>DERIV_RANK_FULL</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase.html</anchorfile>
      <anchor>ab6e7d271b38f0a1035c41ecc2682d914a618f1399ff8b4ef896bb52ed2a6eee74</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>DERIV_RANK_DEFICIENT</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase.html</anchorfile>
      <anchor>ab6e7d271b38f0a1035c41ecc2682d914ab4bd239ad445f7132c5503ef4ab6074b</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>EOutArgsMembers</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase.html</anchorfile>
      <anchor>a0dcb168274ca26954a0b3ff74bc185b2</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>OUT_ARG_f</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase.html</anchorfile>
      <anchor>a0dcb168274ca26954a0b3ff74bc185b2a739cd09c2f8914c78ba9b954bd0402e8</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>OUT_ARG_W</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase.html</anchorfile>
      <anchor>a0dcb168274ca26954a0b3ff74bc185b2a7edd7ee918e069e79f7048fcfb078d71</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>OUT_ARG_f_mp</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase.html</anchorfile>
      <anchor>a0dcb168274ca26954a0b3ff74bc185b2a6f26cf9e69d1fad3b8518c7b34596178</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>OUT_ARG_W_mp</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase.html</anchorfile>
      <anchor>a0dcb168274ca26954a0b3ff74bc185b2a84855f135253f69da52b11b72e17841f</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>OUT_ARG_W_op</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase.html</anchorfile>
      <anchor>a0dcb168274ca26954a0b3ff74bc185b2a47fd06e2e5e1c849d6a4b13ecdb70734</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>OUT_ARG_W_prec</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase.html</anchorfile>
      <anchor>a0dcb168274ca26954a0b3ff74bc185b2a741e58dcd8fe23f7c9d032e97d5a69a5</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>OUT_ARG_f_poly</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase.html</anchorfile>
      <anchor>a0dcb168274ca26954a0b3ff74bc185b2a34a9714884b030000695dbc43dc2bc12</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>EOutArgsDfDp</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase.html</anchorfile>
      <anchor>a951e2b8929bd0bb3cf0e9490ab1fee38</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>OUT_ARG_DfDp</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase.html</anchorfile>
      <anchor>a951e2b8929bd0bb3cf0e9490ab1fee38ab3cd7737279ab11bd3f013b886cd5136</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>EOutArgsDgDx_dot</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase.html</anchorfile>
      <anchor>a6c25884d96f08af141a0f1b85aac0098</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>OUT_ARG_DgDx_dot</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase.html</anchorfile>
      <anchor>a6c25884d96f08af141a0f1b85aac0098a3d0410d00d4ee4bd6799bac9ed6a0296</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>EOutArgsDgDx</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase.html</anchorfile>
      <anchor>a121758676313420c50c9d8a418e3b1bc</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>OUT_ARG_DgDx</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase.html</anchorfile>
      <anchor>a121758676313420c50c9d8a418e3b1bca73ff2ddae6b4e7eab87640124fcba56c</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>EOutArgsDgDp</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase.html</anchorfile>
      <anchor>a9ab460861d43621a1a39e6096827d94a</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>OUT_ARG_DgDp</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase.html</anchorfile>
      <anchor>a9ab460861d43621a1a39e6096827d94aadff6a21a0fcb880192e3ccba98ab1949</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>EOutArgsDfDp_mp</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase.html</anchorfile>
      <anchor>a5522d788df5430fa4d426a0bec89f913</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>OUT_ARG_DfDp_mp</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase.html</anchorfile>
      <anchor>a5522d788df5430fa4d426a0bec89f913a685506aab9241a852f388564ba560056</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>EOutArgs_g_mp</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase.html</anchorfile>
      <anchor>a3e6117306931033b175b0015fc0c945b</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>OUT_ARG_g_mp</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase.html</anchorfile>
      <anchor>a3e6117306931033b175b0015fc0c945baafbe9fcf811a0731f7f4ad25557b19a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>EOutArgsDgDx_dot_mp</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase.html</anchorfile>
      <anchor>ae7c674aeebf278ed23d0cc6f4923bbee</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>OUT_ARG_DgDx_dot_mp</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase.html</anchorfile>
      <anchor>ae7c674aeebf278ed23d0cc6f4923bbeeadc00bd142ab2c02d63bc03a1ba50a879</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>EOutArgsDgDx_mp</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase.html</anchorfile>
      <anchor>a556df16951a2f4b1d6a7d7181f89e12a</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>OUT_ARG_DgDx_mp</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase.html</anchorfile>
      <anchor>a556df16951a2f4b1d6a7d7181f89e12aaabafb1cd6d8dd101f1b7ef2caf02a2fc</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>EOutArgsDgDp_mp</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase.html</anchorfile>
      <anchor>aa173a79d547ccfa58ec3de9d05a6bc9e</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>OUT_ARG_DgDp_mp</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase.html</anchorfile>
      <anchor>aa173a79d547ccfa58ec3de9d05a6bc9ea641c550f1103e4a6cbebca8f54e5e4e5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const int</type>
      <name>NUM_E_IN_ARGS_MEMBERS</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase.html</anchorfile>
      <anchor>a90cb6e83d919c7b6a085b7761276c5bd</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const int</type>
      <name>NUM_E_OUT_ARGS_MEMBERS</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase.html</anchorfile>
      <anchor>a582706e0f7f6cc142c86d289ff3e7358</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ModelEvaluatorBase</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase.html</anchorfile>
      <anchor>a61b391652270652e8021c1b1bb35b308</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::ModelEvaluatorDefaultBase</name>
    <filename>classThyra_1_1ModelEvaluatorDefaultBase.html</filename>
    <templarg>Scalar</templarg>
    <base virtualness="virtual">Thyra::ModelEvaluator</base>
    <member kind="function" protection="protected">
      <type></type>
      <name>ModelEvaluatorDefaultBase</name>
      <anchorfile>classThyra_1_1ModelEvaluatorDefaultBase.html</anchorfile>
      <anchor>a3aadfe8b55e548a49df06a7c0b9aa824</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; ModelEvaluatorBase::InArgs&lt; Scalar &gt; &gt;</type>
      <name>clone</name>
      <anchorfile>classThyra_1_1ModelEvaluatorDefaultBase.html</anchorfile>
      <anchor>a8fd2d7e92b01b9f306c279d7086d9030</anchor>
      <arglist>(const ModelEvaluatorBase::InArgs&lt; Scalar &gt; &amp;inArgs)</arglist>
    </member>
    <member kind="function">
      <type>ModelEvaluatorBase::Derivative&lt; Scalar &gt;</type>
      <name>derivativeGradient</name>
      <anchorfile>classThyra_1_1ModelEvaluatorDefaultBase.html</anchorfile>
      <anchor>acfe72b96d4f1a6ccdfc7633d42c42095</anchor>
      <arglist>(const RCP&lt; MultiVectorBase&lt; Scalar &gt; &gt; &amp;grad)</arglist>
    </member>
    <member kind="function">
      <type>ModelEvaluatorBase::DerivativeMultiVector&lt; Scalar &gt;</type>
      <name>create_DfDp_mv</name>
      <anchorfile>classThyra_1_1ModelEvaluatorDefaultBase.html</anchorfile>
      <anchor>a12e8b4e6174a810937e67c483a6fddb9</anchor>
      <arglist>(const ModelEvaluator&lt; Scalar &gt; &amp;model, int l, ModelEvaluatorBase::EDerivativeMultiVectorOrientation orientation)</arglist>
    </member>
    <member kind="function">
      <type>ModelEvaluatorBase::DerivativeMultiVector&lt; Scalar &gt;</type>
      <name>create_DgDx_dot_mv</name>
      <anchorfile>classThyra_1_1ModelEvaluatorDefaultBase.html</anchorfile>
      <anchor>a858c54bed46a42c83380c73e59e9396c</anchor>
      <arglist>(const ModelEvaluator&lt; Scalar &gt; &amp;model, int j, ModelEvaluatorBase::EDerivativeMultiVectorOrientation orientation)</arglist>
    </member>
    <member kind="function">
      <type>ModelEvaluatorBase::DerivativeMultiVector&lt; Scalar &gt;</type>
      <name>create_DgDx_mv</name>
      <anchorfile>classThyra_1_1ModelEvaluatorDefaultBase.html</anchorfile>
      <anchor>a6d2d1dec79bc0ff4a1e0610f30cf3051</anchor>
      <arglist>(const ModelEvaluator&lt; Scalar &gt; &amp;model, int j, ModelEvaluatorBase::EDerivativeMultiVectorOrientation orientation)</arglist>
    </member>
    <member kind="function">
      <type>ModelEvaluatorBase::DerivativeMultiVector&lt; Scalar &gt;</type>
      <name>create_DgDp_mv</name>
      <anchorfile>classThyra_1_1ModelEvaluatorDefaultBase.html</anchorfile>
      <anchor>ab7d953c5c9c43d63bc2ccab0ed2f0735</anchor>
      <arglist>(const ModelEvaluator&lt; Scalar &gt; &amp;model, int j, int l, ModelEvaluatorBase::EDerivativeMultiVectorOrientation orientation)</arglist>
    </member>
    <member kind="function">
      <type>ModelEvaluatorBase::DerivativeMultiVector&lt; Scalar &gt;</type>
      <name>get_dmv</name>
      <anchorfile>classThyra_1_1ModelEvaluatorDefaultBase.html</anchorfile>
      <anchor>a09fb370850bd72f691a11a672439fb19</anchor>
      <arglist>(const ModelEvaluatorBase::Derivative&lt; Scalar &gt; &amp;deriv, const std::string &amp;derivName)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; MultiVectorBase&lt; Scalar &gt; &gt;</type>
      <name>get_mv</name>
      <anchorfile>classThyra_1_1ModelEvaluatorDefaultBase.html</anchorfile>
      <anchor>aec28c2b1370346eff53d2c57be83c875</anchor>
      <arglist>(const ModelEvaluatorBase::Derivative&lt; Scalar &gt; &amp;deriv, const std::string &amp;derivName, ModelEvaluatorBase::EDerivativeMultiVectorOrientation orientation)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>assertDerivSpaces</name>
      <anchorfile>classThyra_1_1ModelEvaluatorDefaultBase.html</anchorfile>
      <anchor>af13c0c008e8a212856f602c97b0444da</anchor>
      <arglist>(const std::string &amp;modelEvalDescription, const ModelEvaluatorBase::Derivative&lt; Scalar &gt; &amp;deriv, const std::string &amp;deriv_name, const VectorSpaceBase&lt; Scalar &gt; &amp;fnc_space, const std::string &amp;fnc_space_name, const VectorSpaceBase&lt; Scalar &gt; &amp;var_space, const std::string &amp;var_space_name)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>assertInArgsOutArgsSetup</name>
      <anchorfile>classThyra_1_1ModelEvaluatorDefaultBase.html</anchorfile>
      <anchor>a987113550f8eee5ce2bbac6210062206</anchor>
      <arglist>(const std::string &amp;modelEvalDescription, const ModelEvaluatorBase::InArgs&lt; Scalar &gt; &amp;inArgs, const ModelEvaluatorBase::OutArgs&lt; Scalar &gt; &amp;outArgs)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>assertInArgsEvalObjects</name>
      <anchorfile>classThyra_1_1ModelEvaluatorDefaultBase.html</anchorfile>
      <anchor>ac8f888df04e077da63152bfa81433447</anchor>
      <arglist>(const ModelEvaluator&lt; Scalar &gt; &amp;model, const ModelEvaluatorBase::InArgs&lt; Scalar &gt; &amp;inArgs)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>assertOutArgsEvalObjects</name>
      <anchorfile>classThyra_1_1ModelEvaluatorDefaultBase.html</anchorfile>
      <anchor>a51a1cb257e8a8a74e7f2a03b28a78060</anchor>
      <arglist>(const ModelEvaluator&lt; Scalar &gt; &amp;model, const ModelEvaluatorBase::OutArgs&lt; Scalar &gt; &amp;outArgs, const ModelEvaluatorBase::InArgs&lt; Scalar &gt; *inArgs=0)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Np</name>
      <anchorfile>classThyra_1_1ModelEvaluatorDefaultBase.html</anchorfile>
      <anchor>a75b7947713dc002c452305634fc6484a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Ng</name>
      <anchorfile>classThyra_1_1ModelEvaluatorDefaultBase.html</anchorfile>
      <anchor>a0dfd18fb7b959072bc260e672cadff55</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; LinearOpBase&lt; Scalar &gt; &gt;</type>
      <name>create_DfDp_op</name>
      <anchorfile>classThyra_1_1ModelEvaluatorDefaultBase.html</anchorfile>
      <anchor>a714261c47f2f1267af246d498974d25c</anchor>
      <arglist>(int l) const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; LinearOpBase&lt; Scalar &gt; &gt;</type>
      <name>create_DgDx_dot_op</name>
      <anchorfile>classThyra_1_1ModelEvaluatorDefaultBase.html</anchorfile>
      <anchor>ac7cc25a31bdd4644ee243ec20dc7491b</anchor>
      <arglist>(int j) const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; LinearOpBase&lt; Scalar &gt; &gt;</type>
      <name>create_DgDx_op</name>
      <anchorfile>classThyra_1_1ModelEvaluatorDefaultBase.html</anchorfile>
      <anchor>a8c77272766c0b7825d726bfcf231affc</anchor>
      <arglist>(int j) const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; LinearOpBase&lt; Scalar &gt; &gt;</type>
      <name>create_DgDp_op</name>
      <anchorfile>classThyra_1_1ModelEvaluatorDefaultBase.html</anchorfile>
      <anchor>a4ca40f2f97949bbbf237f29e1ddf8c8f</anchor>
      <arglist>(int j, int l) const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; LinearOpWithSolveBase&lt; Scalar &gt; &gt;</type>
      <name>create_W</name>
      <anchorfile>classThyra_1_1ModelEvaluatorDefaultBase.html</anchorfile>
      <anchor>abb296e9367b1e0032834bd1d14bc39b0</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>ModelEvaluatorBase::OutArgs&lt; Scalar &gt;</type>
      <name>createOutArgs</name>
      <anchorfile>classThyra_1_1ModelEvaluatorDefaultBase.html</anchorfile>
      <anchor>a761cc805e9782891fdf32c95a9b4de90</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>evalModel</name>
      <anchorfile>classThyra_1_1ModelEvaluatorDefaultBase.html</anchorfile>
      <anchor>a8bf2864906c61d57eb522b7d1bcdda0f</anchor>
      <arglist>(const ModelEvaluatorBase::InArgs&lt; Scalar &gt; &amp;inArgs, const ModelEvaluatorBase::OutArgs&lt; Scalar &gt; &amp;outArgs) const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>initializeDefaultBase</name>
      <anchorfile>classThyra_1_1ModelEvaluatorDefaultBase.html</anchorfile>
      <anchor>aeb009cb9e74783447c6c1dd66db78a09</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ModelEvaluatorDefaultBase&lt; double &gt;</name>
    <filename>classThyra_1_1ModelEvaluatorDefaultBase.html</filename>
    <base virtualness="virtual">ModelEvaluator&lt; double &gt;</base>
    <member kind="function" protection="protected">
      <type></type>
      <name>ModelEvaluatorDefaultBase</name>
      <anchorfile>classThyra_1_1ModelEvaluatorDefaultBase.html</anchorfile>
      <anchor>a3aadfe8b55e548a49df06a7c0b9aa824</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Np</name>
      <anchorfile>classThyra_1_1ModelEvaluatorDefaultBase.html</anchorfile>
      <anchor>a75b7947713dc002c452305634fc6484a</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Ng</name>
      <anchorfile>classThyra_1_1ModelEvaluatorDefaultBase.html</anchorfile>
      <anchor>a0dfd18fb7b959072bc260e672cadff55</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; LinearOpBase&lt; double &gt; &gt;</type>
      <name>create_DfDp_op</name>
      <anchorfile>classThyra_1_1ModelEvaluatorDefaultBase.html</anchorfile>
      <anchor>a714261c47f2f1267af246d498974d25c</anchor>
      <arglist>(int l) const</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; LinearOpBase&lt; double &gt; &gt;</type>
      <name>create_DgDx_dot_op</name>
      <anchorfile>classThyra_1_1ModelEvaluatorDefaultBase.html</anchorfile>
      <anchor>ac7cc25a31bdd4644ee243ec20dc7491b</anchor>
      <arglist>(int j) const</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; LinearOpBase&lt; double &gt; &gt;</type>
      <name>create_DgDx_op</name>
      <anchorfile>classThyra_1_1ModelEvaluatorDefaultBase.html</anchorfile>
      <anchor>a8c77272766c0b7825d726bfcf231affc</anchor>
      <arglist>(int j) const</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; LinearOpBase&lt; double &gt; &gt;</type>
      <name>create_DgDp_op</name>
      <anchorfile>classThyra_1_1ModelEvaluatorDefaultBase.html</anchorfile>
      <anchor>a4ca40f2f97949bbbf237f29e1ddf8c8f</anchor>
      <arglist>(int j, int l) const</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; LinearOpWithSolveBase&lt; double &gt; &gt;</type>
      <name>create_W</name>
      <anchorfile>classThyra_1_1ModelEvaluatorDefaultBase.html</anchorfile>
      <anchor>abb296e9367b1e0032834bd1d14bc39b0</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>ModelEvaluatorBase::OutArgs&lt; double &gt;</type>
      <name>createOutArgs</name>
      <anchorfile>classThyra_1_1ModelEvaluatorDefaultBase.html</anchorfile>
      <anchor>a761cc805e9782891fdf32c95a9b4de90</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>evalModel</name>
      <anchorfile>classThyra_1_1ModelEvaluatorDefaultBase.html</anchorfile>
      <anchor>a8bf2864906c61d57eb522b7d1bcdda0f</anchor>
      <arglist>(const ModelEvaluatorBase::InArgs&lt; double &gt; &amp;inArgs, const ModelEvaluatorBase::OutArgs&lt; double &gt; &amp;outArgs) const</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>initializeDefaultBase</name>
      <anchorfile>classThyra_1_1ModelEvaluatorDefaultBase.html</anchorfile>
      <anchor>aeb009cb9e74783447c6c1dd66db78a09</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::ModelEvaluatorDelegatorBase</name>
    <filename>classThyra_1_1ModelEvaluatorDelegatorBase.html</filename>
    <templarg></templarg>
    <base virtualness="virtual">Thyra::ModelEvaluatorDefaultBase</base>
    <member kind="function">
      <type></type>
      <name>ModelEvaluatorDelegatorBase</name>
      <anchorfile>classThyra_1_1ModelEvaluatorDelegatorBase.html</anchorfile>
      <anchor>a220ae1ad85e5a706bb11756850dfc276</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ModelEvaluatorDelegatorBase</name>
      <anchorfile>classThyra_1_1ModelEvaluatorDelegatorBase.html</anchorfile>
      <anchor>a38758e7a567ac909056e39ae10e1a6b0</anchor>
      <arglist>(const RCP&lt; ModelEvaluator&lt; Scalar &gt; &gt; &amp;model)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ModelEvaluatorDelegatorBase</name>
      <anchorfile>classThyra_1_1ModelEvaluatorDelegatorBase.html</anchorfile>
      <anchor>a3772fe363e6f5d6578e287ee4c50f174</anchor>
      <arglist>(const RCP&lt; const ModelEvaluator&lt; Scalar &gt; &gt; &amp;model)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initialize</name>
      <anchorfile>classThyra_1_1ModelEvaluatorDelegatorBase.html</anchorfile>
      <anchor>aaff4e56a21995a949ebe3c97ab5825f2</anchor>
      <arglist>(const RCP&lt; ModelEvaluator&lt; Scalar &gt; &gt; &amp;model)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initialize</name>
      <anchorfile>classThyra_1_1ModelEvaluatorDelegatorBase.html</anchorfile>
      <anchor>a5544c6bc480cdf3246279c9f87917ce0</anchor>
      <arglist>(const RCP&lt; const ModelEvaluator&lt; Scalar &gt; &gt; &amp;model)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>uninitialize</name>
      <anchorfile>classThyra_1_1ModelEvaluatorDelegatorBase.html</anchorfile>
      <anchor>aac7bf3bfc04c5f2c59ca55cf11bb1687</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>isUnderlyingModelConst</name>
      <anchorfile>classThyra_1_1ModelEvaluatorDelegatorBase.html</anchorfile>
      <anchor>a0dc0a7f18d3877302d3fe3ebb6ccf73c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual RCP&lt; ModelEvaluator&lt; Scalar &gt; &gt;</type>
      <name>getNonconstUnderlyingModel</name>
      <anchorfile>classThyra_1_1ModelEvaluatorDelegatorBase.html</anchorfile>
      <anchor>ac3a1060e4a08f90854f9f5e359779dd3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual RCP&lt; const ModelEvaluator&lt; Scalar &gt; &gt;</type>
      <name>getUnderlyingModel</name>
      <anchorfile>classThyra_1_1ModelEvaluatorDelegatorBase.html</anchorfile>
      <anchor>a720ef4231f5e71571c91a8630232eaf5</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const VectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>get_x_space</name>
      <anchorfile>classThyra_1_1ModelEvaluatorDelegatorBase.html</anchorfile>
      <anchor>ac172bebdcd6201e3d5e22a0c4f916c98</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const VectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>get_f_space</name>
      <anchorfile>classThyra_1_1ModelEvaluatorDelegatorBase.html</anchorfile>
      <anchor>ac56543a36022cb620491f0fa49574013</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const VectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>get_p_space</name>
      <anchorfile>classThyra_1_1ModelEvaluatorDelegatorBase.html</anchorfile>
      <anchor>ad8cca048e30d104152c440b9bdb1b62d</anchor>
      <arglist>(int l) const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const Teuchos::Array&lt; std::string &gt; &gt;</type>
      <name>get_p_names</name>
      <anchorfile>classThyra_1_1ModelEvaluatorDelegatorBase.html</anchorfile>
      <anchor>ad395e7c11afa86196a1d46f56e73be49</anchor>
      <arglist>(int l) const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const VectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>get_g_space</name>
      <anchorfile>classThyra_1_1ModelEvaluatorDelegatorBase.html</anchorfile>
      <anchor>a06a7f169c201c72cb866cf57712fcdf2</anchor>
      <arglist>(int j) const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::ArrayView&lt; const std::string &gt;</type>
      <name>get_g_names</name>
      <anchorfile>classThyra_1_1ModelEvaluatorDelegatorBase.html</anchorfile>
      <anchor>a1dc63b9e674fce4d631c96bd84e84e28</anchor>
      <arglist>(int j) const </arglist>
    </member>
    <member kind="function">
      <type>ModelEvaluatorBase::InArgs&lt; Scalar &gt;</type>
      <name>getNominalValues</name>
      <anchorfile>classThyra_1_1ModelEvaluatorDelegatorBase.html</anchorfile>
      <anchor>a1a0a263d62fd2c238909e2020da57d81</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>ModelEvaluatorBase::InArgs&lt; Scalar &gt;</type>
      <name>getLowerBounds</name>
      <anchorfile>classThyra_1_1ModelEvaluatorDelegatorBase.html</anchorfile>
      <anchor>aef80af5cb7db0be9b0cdcfaeff070690</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>ModelEvaluatorBase::InArgs&lt; Scalar &gt;</type>
      <name>getUpperBounds</name>
      <anchorfile>classThyra_1_1ModelEvaluatorDelegatorBase.html</anchorfile>
      <anchor>a703063a9b94dd3d9252bd67aa3b92a70</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; LinearOpWithSolveBase&lt; Scalar &gt; &gt;</type>
      <name>create_W</name>
      <anchorfile>classThyra_1_1ModelEvaluatorDelegatorBase.html</anchorfile>
      <anchor>ad2fc21980ea8074685157ab9295f6624</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; LinearOpBase&lt; Scalar &gt; &gt;</type>
      <name>create_W_op</name>
      <anchorfile>classThyra_1_1ModelEvaluatorDelegatorBase.html</anchorfile>
      <anchor>ab4c4656ca74db5c4eb9e95a59e098147</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; PreconditionerBase&lt; Scalar &gt; &gt;</type>
      <name>create_W_prec</name>
      <anchorfile>classThyra_1_1ModelEvaluatorDelegatorBase.html</anchorfile>
      <anchor>af26602291a9d9dccc0fc8dafe6a0c02e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const LinearOpWithSolveFactoryBase&lt; Scalar &gt; &gt;</type>
      <name>get_W_factory</name>
      <anchorfile>classThyra_1_1ModelEvaluatorDelegatorBase.html</anchorfile>
      <anchor>a72bdd98b7687ae5d4d47ad4e22c9543c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>ModelEvaluatorBase::InArgs&lt; Scalar &gt;</type>
      <name>createInArgs</name>
      <anchorfile>classThyra_1_1ModelEvaluatorDelegatorBase.html</anchorfile>
      <anchor>a98a21b435f1152717e94041dc7609b9c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>reportFinalPoint</name>
      <anchorfile>classThyra_1_1ModelEvaluatorDelegatorBase.html</anchorfile>
      <anchor>a910b54bb6f7db4eb769d76443af1cda6</anchor>
      <arglist>(const ModelEvaluatorBase::InArgs&lt; Scalar &gt; &amp;finalPoint, const bool wasSolved)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>setLocalVerbosityLevelValidatedParameter</name>
      <anchorfile>classThyra_1_1ModelEvaluatorDelegatorBase.html</anchorfile>
      <anchor>a6757449f212af13c9c675e8199e0f8f0</anchor>
      <arglist>(ParameterList *paramList) const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>Teuchos::EVerbosityLevel</type>
      <name>readLocalVerbosityLevelValidatedParameter</name>
      <anchorfile>classThyra_1_1ModelEvaluatorDelegatorBase.html</anchorfile>
      <anchor>ad2c70806125c464ad32261e4f13799f2</anchor>
      <arglist>(ParameterList &amp;paramList) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::ModelEvaluatorBase::MPDerivative</name>
    <filename>classThyra_1_1ModelEvaluatorBase_1_1MPDerivative.html</filename>
    <member kind="function">
      <type></type>
      <name>MPDerivative</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1MPDerivative.html</anchorfile>
      <anchor>aa2649c19316ff862c71c5f81e8a83d43</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>MPDerivative</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1MPDerivative.html</anchorfile>
      <anchor>aa1992ff5b7844633f895f04c2e9061e8</anchor>
      <arglist>(const RCP&lt; Stokhos::ProductEpetraOperator &gt; &amp;lo)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>MPDerivative</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1MPDerivative.html</anchorfile>
      <anchor>a529d2f9a2b8d1bfba0a57dd2b3a99b85</anchor>
      <arglist>(const RCP&lt; Stokhos::ProductEpetraMultiVector &gt; &amp;mv, const EDerivativeMultiVectorOrientation orientation=DERIV_MV_BY_COL)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>MPDerivative</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1MPDerivative.html</anchorfile>
      <anchor>acdcfe6bdfff01cb3068b46b9314e157c</anchor>
      <arglist>(const MPDerivativeMultiVector &amp;dmv)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isEmpty</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1MPDerivative.html</anchorfile>
      <anchor>abbb7b365fbb80435a0c415f9d0347054</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const MPDerivative &amp;</type>
      <name>assert_not_null</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1MPDerivative.html</anchorfile>
      <anchor>a9f6b7071b74d0faa076d33c6af31d980</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; Stokhos::ProductEpetraOperator &gt;</type>
      <name>getLinearOp</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1MPDerivative.html</anchorfile>
      <anchor>ab1e0453002ac381042e82e8f9a2ff663</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; Stokhos::ProductEpetraMultiVector &gt;</type>
      <name>getMultiVector</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1MPDerivative.html</anchorfile>
      <anchor>a7078a3551dfe2a4f0c8ad8e984cc8411</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>EDerivativeMultiVectorOrientation</type>
      <name>getMultiVectorOrientation</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1MPDerivative.html</anchorfile>
      <anchor>a0ba2d34a62e9be8132a32781a5366369</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>MPDerivativeMultiVector</type>
      <name>getDerivativeMultiVector</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1MPDerivative.html</anchorfile>
      <anchor>a4b4007a50b26df779c6f791d259c1d73</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isSupportedBy</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1MPDerivative.html</anchorfile>
      <anchor>a0222dc58ae16809c457a2aec0c2e642f</anchor>
      <arglist>(const DerivativeSupport &amp;derivSupport) const </arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>description</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1MPDerivative.html</anchorfile>
      <anchor>a2f4c7d5b11235143200baa8e71e7b62f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>describe</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1MPDerivative.html</anchorfile>
      <anchor>a538e44cee8fe7397df6bf995fd26138b</anchor>
      <arglist>(Teuchos::FancyOStream &amp;out, const Teuchos::EVerbosityLevel verbLevel) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::ModelEvaluatorBase::MPDerivativeMultiVector</name>
    <filename>classThyra_1_1ModelEvaluatorBase_1_1MPDerivativeMultiVector.html</filename>
    <member kind="function">
      <type></type>
      <name>MPDerivativeMultiVector</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1MPDerivativeMultiVector.html</anchorfile>
      <anchor>adc9858247bbf422f0895b1405ed3a7c7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>MPDerivativeMultiVector</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1MPDerivativeMultiVector.html</anchorfile>
      <anchor>adff70cd29d928332f3d42eb754be5acd</anchor>
      <arglist>(const RCP&lt; Stokhos::ProductEpetraMultiVector &gt; &amp;mv, const EDerivativeMultiVectorOrientation orientation=DERIV_MV_BY_COL, const Teuchos::Array&lt; int &gt; &amp;paramIndexes=Teuchos::Array&lt; int &gt;())</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>changeOrientation</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1MPDerivativeMultiVector.html</anchorfile>
      <anchor>a6c38e8c11fec2a65e6e1e3faeaf671c2</anchor>
      <arglist>(const EDerivativeMultiVectorOrientation orientation)</arglist>
    </member>
    <member kind="function">
      <type>const MPDerivativeMultiVector &amp;</type>
      <name>assert_not_null</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1MPDerivativeMultiVector.html</anchorfile>
      <anchor>abbe38271b8fcbd5608c24ef04f647796</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; Stokhos::ProductEpetraMultiVector &gt;</type>
      <name>getMultiVector</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1MPDerivativeMultiVector.html</anchorfile>
      <anchor>a9e896aa8ceb04015f8301a6cad94df72</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>EDerivativeMultiVectorOrientation</type>
      <name>getOrientation</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1MPDerivativeMultiVector.html</anchorfile>
      <anchor>a6559d3fb5af1a7d26e764c9c070448b9</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Teuchos::Array&lt; int &gt; &amp;</type>
      <name>getParamIndexes</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1MPDerivativeMultiVector.html</anchorfile>
      <anchor>a588030a258ffc181f3446bd4dcdaf137</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>description</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1MPDerivativeMultiVector.html</anchorfile>
      <anchor>a184936c74a179927221538aa5c4a9e1a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>describe</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1MPDerivativeMultiVector.html</anchorfile>
      <anchor>abf1731a2a3c00576303e19c24e4ce14b</anchor>
      <arglist>(Teuchos::FancyOStream &amp;out, const Teuchos::EVerbosityLevel verbLevel) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::MultipliedLinearOpBase</name>
    <filename>classThyra_1_1MultipliedLinearOpBase.html</filename>
    <templarg>Scalar</templarg>
    <base virtualness="virtual">Thyra::LinearOpBase</base>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>numOps</name>
      <anchorfile>classThyra_1_1MultipliedLinearOpBase.html</anchorfile>
      <anchor>a8002d3eaa990395c51393a1bb937e1f6</anchor>
      <arglist>() const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>opIsConst</name>
      <anchorfile>classThyra_1_1MultipliedLinearOpBase.html</anchorfile>
      <anchor>ac31dce3b143f46595c15443efb786b03</anchor>
      <arglist>(const int k) const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual Teuchos::RCP&lt; LinearOpBase&lt; Scalar &gt; &gt;</type>
      <name>getNonconstOp</name>
      <anchorfile>classThyra_1_1MultipliedLinearOpBase.html</anchorfile>
      <anchor>a2a38388f4e6c769fddde2565f0150590</anchor>
      <arglist>(const int k)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual Teuchos::RCP&lt; const LinearOpBase&lt; Scalar &gt; &gt;</type>
      <name>getOp</name>
      <anchorfile>classThyra_1_1MultipliedLinearOpBase.html</anchorfile>
      <anchor>a6ced1ef50558ae1c9fcc66ea09828664</anchor>
      <arglist>(const int k) const  =0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::MultiVectorAdapterBase</name>
    <filename>classThyra_1_1MultiVectorAdapterBase.html</filename>
    <templarg></templarg>
    <base virtualness="virtual">Thyra::MultiVectorDefaultBase</base>
    <member kind="function" virtualness="pure">
      <type>virtual RCP&lt; const ScalarProdVectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>rangeScalarProdVecSpc</name>
      <anchorfile>classThyra_1_1MultiVectorAdapterBase.html</anchorfile>
      <anchor>a3f3f9415ecb5928f864ac6bc4109c6d6</anchor>
      <arglist>() const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual RCP&lt; const ScalarProdVectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>domainScalarProdVecSpc</name>
      <anchorfile>classThyra_1_1MultiVectorAdapterBase.html</anchorfile>
      <anchor>a7cebe2adfc05aaa78cd751d91083abff</anchor>
      <arglist>() const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>euclideanApply</name>
      <anchorfile>classThyra_1_1MultiVectorAdapterBase.html</anchorfile>
      <anchor>a17f8cbd316ad14b5ea83accb79301b96</anchor>
      <arglist>(const EOpTransp M_trans, const MultiVectorBase&lt; Scalar &gt; &amp;X, const Ptr&lt; MultiVectorBase&lt; Scalar &gt; &gt; &amp;Y, const Scalar alpha, const Scalar beta) const  =0</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const VectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>range</name>
      <anchorfile>classThyra_1_1MultiVectorAdapterBase.html</anchorfile>
      <anchor>ac1634f0058ed64f61950a9875acd52ce</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const VectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>domain</name>
      <anchorfile>classThyra_1_1MultiVectorAdapterBase.html</anchorfile>
      <anchor>ae90b01ad62782a4839dbbbb4b5fed1a0</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>bool</type>
      <name>opSupportedImpl</name>
      <anchorfile>classThyra_1_1MultiVectorAdapterBase.html</anchorfile>
      <anchor>a92fa52dcad7ccdf447cbe83c67c68e20</anchor>
      <arglist>(EOpTransp M_trans) const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>applyImpl</name>
      <anchorfile>classThyra_1_1MultiVectorAdapterBase.html</anchorfile>
      <anchor>a52eef89559a3ad050fce3b70aeeff292</anchor>
      <arglist>(const EOpTransp M_trans, const MultiVectorBase&lt; Scalar &gt; &amp;X, const Ptr&lt; MultiVectorBase&lt; Scalar &gt; &gt; &amp;Y, const Scalar alpha, const Scalar beta) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::MultiVectorAllocator</name>
    <filename>classThyra_1_1MultiVectorAllocator.html</filename>
    <templarg></templarg>
    <member kind="typedef">
      <type>Teuchos::RCP&lt; MultiVectorBase&lt; Scalar &gt; &gt;</type>
      <name>ptr_t</name>
      <anchorfile>classThyra_1_1MultiVectorAllocator.html</anchorfile>
      <anchor>a4bfa1cb0bd6686982255f25f59c03081</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>MultiVectorAllocator</name>
      <anchorfile>classThyra_1_1MultiVectorAllocator.html</anchorfile>
      <anchor>a6fb1f465fced0d2f46fdc965d957113d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>MultiVectorAllocator</name>
      <anchorfile>classThyra_1_1MultiVectorAllocator.html</anchorfile>
      <anchor>af61209fe80669b52f7a696d4baf021d4</anchor>
      <arglist>(const Teuchos::RCP&lt; const VectorSpaceBase&lt; Scalar &gt; &gt; &amp;vs, int numMembers)</arglist>
    </member>
    <member kind="function">
      <type>const ptr_t</type>
      <name>allocate</name>
      <anchorfile>classThyra_1_1MultiVectorAllocator.html</anchorfile>
      <anchor>aca82eab870c73d4e25b9a97d268b2446</anchor>
      <arglist>() const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::MultiVectorBase</name>
    <filename>classThyra_1_1MultiVectorBase.html</filename>
    <templarg>Scalar</templarg>
    <base virtualness="virtual">Thyra::LinearOpBase</base>
    <base virtualness="virtual">Thyra::RowStatLinearOpBase</base>
    <base virtualness="virtual">Thyra::ScaledLinearOpBase</base>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>absRowSum</name>
      <anchorfile>classThyra_1_1MultiVectorBase.html</anchorfile>
      <anchor>a57268d8eaf6002ee1eb52ae0966aa700</anchor>
      <arglist>(const Teuchos::Ptr&lt; Thyra::VectorBase&lt; Scalar &gt; &gt; &amp;output) const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>absColSum</name>
      <anchorfile>classThyra_1_1MultiVectorBase.html</anchorfile>
      <anchor>acf5d99c48508e02d244fd1f047b81dd2</anchor>
      <arglist>(const Teuchos::Ptr&lt; Thyra::VectorBase&lt; Scalar &gt; &gt; &amp;output) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>applyOp</name>
      <anchorfile>classThyra_1_1MultiVectorBase.html</anchorfile>
      <anchor>a7971bbd3e16aed843b67eceea50321cb</anchor>
      <arglist>(const RTOpPack::RTOpT&lt; Scalar &gt; &amp;primary_op, const ArrayView&lt; const Ptr&lt; const MultiVectorBase&lt; Scalar &gt; &gt; &gt; &amp;multi_vecs, const ArrayView&lt; const Ptr&lt; MultiVectorBase&lt; Scalar &gt; &gt; &gt; &amp;targ_multi_vecs, const ArrayView&lt; const Ptr&lt; RTOpPack::ReductTarget &gt; &gt; &amp;reduct_objs, const Ordinal primary_global_offset=0)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>applyOp</name>
      <anchorfile>classThyra_1_1MultiVectorBase.html</anchorfile>
      <anchor>aa600378449248c5123dbd327720abd62</anchor>
      <arglist>(const RTOpPack::RTOpT&lt; Scalar &gt; &amp;primary_op, const RTOpPack::RTOpT&lt; Scalar &gt; &amp;secondary_op, const ArrayView&lt; const Ptr&lt; const MultiVectorBase&lt; Scalar &gt; &gt; &gt; &amp;multi_vecs, const ArrayView&lt; const Ptr&lt; MultiVectorBase&lt; Scalar &gt; &gt; &gt; &amp;targ_multi_vecs, const Ptr&lt; RTOpPack::ReductTarget &gt; &amp;reduct_obj, const Ordinal primary_global_offset=0)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>norms</name>
      <anchorfile>classThyra_1_1MultiVectorBase.html</anchorfile>
      <anchor>a95c66c407e523a2f0831356c8804eb87</anchor>
      <arglist>(const MultiVectorBase&lt; Scalar &gt; &amp;V, const ArrayView&lt; typename ScalarTraits&lt; Scalar &gt;::magnitudeType &gt; &amp;norms)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>reductions</name>
      <anchorfile>classThyra_1_1MultiVectorBase.html</anchorfile>
      <anchor>ac6faef43a23572179448d72e33e75a53</anchor>
      <arglist>(const MultiVectorBase&lt; Scalar &gt; &amp;V, const NormOp &amp;op, const ArrayView&lt; typename ScalarTraits&lt; Scalar &gt;::magnitudeType &gt; &amp;norms)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>norms_1</name>
      <anchorfile>classThyra_1_1MultiVectorBase.html</anchorfile>
      <anchor>a2b550071af2e2de64de6629646c91539</anchor>
      <arglist>(const MultiVectorBase&lt; Scalar &gt; &amp;V, const ArrayView&lt; typename ScalarTraits&lt; Scalar &gt;::magnitudeType &gt; &amp;norms)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>norms_2</name>
      <anchorfile>classThyra_1_1MultiVectorBase.html</anchorfile>
      <anchor>a990e5daddf9317e80134cb83ae9ae90e</anchor>
      <arglist>(const MultiVectorBase&lt; Scalar &gt; &amp;V, const ArrayView&lt; typename ScalarTraits&lt; Scalar &gt;::magnitudeType &gt; &amp;norms)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>norms_inf</name>
      <anchorfile>classThyra_1_1MultiVectorBase.html</anchorfile>
      <anchor>ad2c439504b2cdf2b8c0805d1f66dcdad</anchor>
      <arglist>(const MultiVectorBase&lt; Scalar &gt; &amp;V, const ArrayView&lt; typename ScalarTraits&lt; Scalar &gt;::magnitudeType &gt; &amp;norms)</arglist>
    </member>
    <member kind="function">
      <type>Array&lt; typename ScalarTraits&lt; Scalar &gt;::magnitudeType &gt;</type>
      <name>norms_inf</name>
      <anchorfile>classThyra_1_1MultiVectorBase.html</anchorfile>
      <anchor>a7225577f52115651d3f1d28b9633fda0</anchor>
      <arglist>(const MultiVectorBase&lt; Scalar &gt; &amp;V)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>dots</name>
      <anchorfile>classThyra_1_1MultiVectorBase.html</anchorfile>
      <anchor>aa2f4c26b11278d79d8b4af26ce6fc97c</anchor>
      <arglist>(const MultiVectorBase&lt; Scalar &gt; &amp;V1, const MultiVectorBase&lt; Scalar &gt; &amp;V2, const ArrayView&lt; Scalar &gt; &amp;dots)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>sums</name>
      <anchorfile>classThyra_1_1MultiVectorBase.html</anchorfile>
      <anchor>a6a91e1134cab4b6b85d59ff380943908</anchor>
      <arglist>(const MultiVectorBase&lt; Scalar &gt; &amp;V, const ArrayView&lt; Scalar &gt; &amp;sums)</arglist>
    </member>
    <member kind="function">
      <type>ScalarTraits&lt; Scalar &gt;::magnitudeType</type>
      <name>norm_1</name>
      <anchorfile>classThyra_1_1MultiVectorBase.html</anchorfile>
      <anchor>a8ba2a058bfffa7bbec4081b4e1c49a60</anchor>
      <arglist>(const MultiVectorBase&lt; Scalar &gt; &amp;V)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>scale</name>
      <anchorfile>classThyra_1_1MultiVectorBase.html</anchorfile>
      <anchor>a5c1e37ca56e501babf7d92215e92df7b</anchor>
      <arglist>(Scalar alpha, const Ptr&lt; MultiVectorBase&lt; Scalar &gt; &gt; &amp;V)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>scaleUpdate</name>
      <anchorfile>classThyra_1_1MultiVectorBase.html</anchorfile>
      <anchor>ae4bcf97ac0a85e9000030bc921a4de4a</anchor>
      <arglist>(const VectorBase&lt; Scalar &gt; &amp;a, const MultiVectorBase&lt; Scalar &gt; &amp;U, const Ptr&lt; MultiVectorBase&lt; Scalar &gt; &gt; &amp;V)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>assign</name>
      <anchorfile>classThyra_1_1MultiVectorBase.html</anchorfile>
      <anchor>a3b25da556eb33cf258b78dd7d62a0462</anchor>
      <arglist>(const Ptr&lt; MultiVectorBase&lt; Scalar &gt; &gt; &amp;V, Scalar alpha)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>assign</name>
      <anchorfile>classThyra_1_1MultiVectorBase.html</anchorfile>
      <anchor>ada807300fa864fb1a888a98510f2f33e</anchor>
      <arglist>(const Ptr&lt; MultiVectorBase&lt; Scalar &gt; &gt; &amp;V, const MultiVectorBase&lt; Scalar &gt; &amp;U)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>update</name>
      <anchorfile>classThyra_1_1MultiVectorBase.html</anchorfile>
      <anchor>ae027cdeb2ca913cc2859f519f8ff0274</anchor>
      <arglist>(Scalar alpha, const MultiVectorBase&lt; Scalar &gt; &amp;U, const Ptr&lt; MultiVectorBase&lt; Scalar &gt; &gt; &amp;V)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>update</name>
      <anchorfile>classThyra_1_1MultiVectorBase.html</anchorfile>
      <anchor>a0a841a570950c16fb201659427a1a7d7</anchor>
      <arglist>(const ArrayView&lt; const Scalar &gt; &amp;alpha, Scalar beta, const MultiVectorBase&lt; Scalar &gt; &amp;U, const Ptr&lt; MultiVectorBase&lt; Scalar &gt; &gt; &amp;V)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>update</name>
      <anchorfile>classThyra_1_1MultiVectorBase.html</anchorfile>
      <anchor>a4b70b740998cad2e2203838961ac2d19</anchor>
      <arglist>(const MultiVectorBase&lt; Scalar &gt; &amp;U, const ArrayView&lt; const Scalar &gt; &amp;alpha, Scalar beta, const Ptr&lt; MultiVectorBase&lt; Scalar &gt; &gt; &amp;V)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>linear_combination</name>
      <anchorfile>classThyra_1_1MultiVectorBase.html</anchorfile>
      <anchor>a155b29842c0f0a329279356ab0824815</anchor>
      <arglist>(const ArrayView&lt; const Scalar &gt; &amp;alpha, const ArrayView&lt; const Ptr&lt; const MultiVectorBase&lt; Scalar &gt; &gt; &gt; &amp;X, const Scalar &amp;beta, const Ptr&lt; MultiVectorBase&lt; Scalar &gt; &gt; &amp;Y)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>randomize</name>
      <anchorfile>classThyra_1_1MultiVectorBase.html</anchorfile>
      <anchor>aca2feb6b201124512d4f0cf61ddf58b3</anchor>
      <arglist>(Scalar l, Scalar u, const Ptr&lt; MultiVectorBase&lt; Scalar &gt; &gt; &amp;V)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Vt_S</name>
      <anchorfile>classThyra_1_1MultiVectorBase.html</anchorfile>
      <anchor>ae86bb4ce5100dec83429b6bdcfe5d00a</anchor>
      <arglist>(const Ptr&lt; MultiVectorBase&lt; Scalar &gt; &gt; &amp;Z, const Scalar &amp;alpha)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Vp_S</name>
      <anchorfile>classThyra_1_1MultiVectorBase.html</anchorfile>
      <anchor>aea225c605bf1f422050f664e61b60acb</anchor>
      <arglist>(const Ptr&lt; MultiVectorBase&lt; Scalar &gt; &gt; &amp;Z, const Scalar &amp;alpha)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Vp_V</name>
      <anchorfile>classThyra_1_1MultiVectorBase.html</anchorfile>
      <anchor>abb6d2162953bdfa56ea211b52db9e70a</anchor>
      <arglist>(const Ptr&lt; MultiVectorBase&lt; Scalar &gt; &gt; &amp;Z, const MultiVectorBase&lt; Scalar &gt; &amp;X)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>V_VpV</name>
      <anchorfile>classThyra_1_1MultiVectorBase.html</anchorfile>
      <anchor>adb3733913ac4e105c354a7d055dde044</anchor>
      <arglist>(const Ptr&lt; MultiVectorBase&lt; Scalar &gt; &gt; &amp;Z, const MultiVectorBase&lt; Scalar &gt; &amp;X, const MultiVectorBase&lt; Scalar &gt; &amp;Y)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>V_VmV</name>
      <anchorfile>classThyra_1_1MultiVectorBase.html</anchorfile>
      <anchor>aadb4cbbef5d314630588e44c28366734</anchor>
      <arglist>(const Ptr&lt; MultiVectorBase&lt; Scalar &gt; &gt; &amp;Z, const MultiVectorBase&lt; Scalar &gt; &amp;X, const MultiVectorBase&lt; Scalar &gt; &amp;Y)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>V_StVpV</name>
      <anchorfile>classThyra_1_1MultiVectorBase.html</anchorfile>
      <anchor>a7e14bb410c36a9da22522acbef51ce26</anchor>
      <arglist>(const Ptr&lt; MultiVectorBase&lt; Scalar &gt; &gt; &amp;Z, const Scalar &amp;alpha, const MultiVectorBase&lt; Scalar &gt; &amp;X, const MultiVectorBase&lt; Scalar &gt; &amp;Y)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>assign</name>
      <anchorfile>classThyra_1_1MultiVectorBase.html</anchorfile>
      <anchor>aeafb734ee47eb5c21b3a53118a2478af</anchor>
      <arglist>(Scalar alpha)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const VectorBase&lt; Scalar &gt; &gt;</type>
      <name>col</name>
      <anchorfile>classThyra_1_1MultiVectorBase.html</anchorfile>
      <anchor>a992e991ed7bca2ad9881764057ed6a11</anchor>
      <arglist>(Ordinal j) const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; VectorBase&lt; Scalar &gt; &gt;</type>
      <name>col</name>
      <anchorfile>classThyra_1_1MultiVectorBase.html</anchorfile>
      <anchor>a0fa84a47cc77a902681834eb07194cf4</anchor>
      <arglist>(Ordinal j)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const MultiVectorBase&lt; Scalar &gt; &gt;</type>
      <name>subView</name>
      <anchorfile>classThyra_1_1MultiVectorBase.html</anchorfile>
      <anchor>a0a992bed28e109b7ad633168d749a83d</anchor>
      <arglist>(const Range1D &amp;colRng) const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; MultiVectorBase&lt; Scalar &gt; &gt;</type>
      <name>subView</name>
      <anchorfile>classThyra_1_1MultiVectorBase.html</anchorfile>
      <anchor>abebe127030bb8dd6c1d6b19b55a5578d</anchor>
      <arglist>(const Range1D &amp;colRng)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const MultiVectorBase&lt; Scalar &gt; &gt;</type>
      <name>subView</name>
      <anchorfile>classThyra_1_1MultiVectorBase.html</anchorfile>
      <anchor>a9a8f252df17370eafda20a48fa23f238</anchor>
      <arglist>(const ArrayView&lt; const int &gt; &amp;cols) const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; MultiVectorBase&lt; Scalar &gt; &gt;</type>
      <name>subView</name>
      <anchorfile>classThyra_1_1MultiVectorBase.html</anchorfile>
      <anchor>af1c0ca76077da41a05a5174543d0588b</anchor>
      <arglist>(const ArrayView&lt; const int &gt; &amp;cols)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>applyOp</name>
      <anchorfile>classThyra_1_1MultiVectorBase.html</anchorfile>
      <anchor>afe9e6940b9af6be9315830610ff2d19e</anchor>
      <arglist>(const RTOpPack::RTOpT&lt; Scalar &gt; &amp;primary_op, const ArrayView&lt; const Ptr&lt; const MultiVectorBase&lt; Scalar &gt; &gt; &gt; &amp;multi_vecs, const ArrayView&lt; const Ptr&lt; MultiVectorBase&lt; Scalar &gt; &gt; &gt; &amp;targ_multi_vecs, const ArrayView&lt; const Ptr&lt; RTOpPack::ReductTarget &gt; &gt; &amp;reduct_objs, const Ordinal primary_global_offset) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>applyOp</name>
      <anchorfile>classThyra_1_1MultiVectorBase.html</anchorfile>
      <anchor>af1d3ebb8dba89e861ed22cd6850e9621</anchor>
      <arglist>(const RTOpPack::RTOpT&lt; Scalar &gt; &amp;primary_op, const RTOpPack::RTOpT&lt; Scalar &gt; &amp;secondary_op, const ArrayView&lt; const Ptr&lt; const MultiVectorBase&lt; Scalar &gt; &gt; &gt; &amp;multi_vecs, const ArrayView&lt; const Ptr&lt; MultiVectorBase&lt; Scalar &gt; &gt; &gt; &amp;targ_multi_vecs, const Ptr&lt; RTOpPack::ReductTarget &gt; &amp;reduct_obj, const Ordinal primary_global_offset) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>acquireDetachedView</name>
      <anchorfile>classThyra_1_1MultiVectorBase.html</anchorfile>
      <anchor>a391b132b12dfb0b1f20ab8ecdf9ab83e</anchor>
      <arglist>(const Range1D &amp;rowRng, const Range1D &amp;colRng, RTOpPack::ConstSubMultiVectorView&lt; Scalar &gt; *sub_mv) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>releaseDetachedView</name>
      <anchorfile>classThyra_1_1MultiVectorBase.html</anchorfile>
      <anchor>ad4ffd5e4dfd3aa727f49ab52860b8d27</anchor>
      <arglist>(RTOpPack::ConstSubMultiVectorView&lt; Scalar &gt; *sub_mv) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>acquireDetachedView</name>
      <anchorfile>classThyra_1_1MultiVectorBase.html</anchorfile>
      <anchor>ac2fced0156a834fd479a865686389aac</anchor>
      <arglist>(const Range1D &amp;rowRng, const Range1D &amp;colRng, RTOpPack::SubMultiVectorView&lt; Scalar &gt; *sub_mv)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>commitDetachedView</name>
      <anchorfile>classThyra_1_1MultiVectorBase.html</anchorfile>
      <anchor>a938e6f89dd523b955954fa4ac82093d6</anchor>
      <arglist>(RTOpPack::SubMultiVectorView&lt; Scalar &gt; *sub_mv)</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual RCP&lt; MultiVectorBase&lt; Scalar &gt; &gt;</type>
      <name>clone_mv</name>
      <anchorfile>classThyra_1_1MultiVectorBase.html</anchorfile>
      <anchor>af7016169960423c0cd47b501e687fdd8</anchor>
      <arglist>() const  =0</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const LinearOpBase&lt; Scalar &gt; &gt;</type>
      <name>clone</name>
      <anchorfile>classThyra_1_1MultiVectorBase.html</anchorfile>
      <anchor>a63495b8946bc98c03d72602a7ceaa44d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual void</type>
      <name>assignImpl</name>
      <anchorfile>classThyra_1_1MultiVectorBase.html</anchorfile>
      <anchor>a96e417ac1fdbc30e53ea2daf4006644a</anchor>
      <arglist>(Scalar alpha)=0</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual RCP&lt; const VectorBase&lt; Scalar &gt; &gt;</type>
      <name>colImpl</name>
      <anchorfile>classThyra_1_1MultiVectorBase.html</anchorfile>
      <anchor>aedb0790bc5f0a4cabe4b55595f3da2a0</anchor>
      <arglist>(Ordinal j) const </arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual RCP&lt; VectorBase&lt; Scalar &gt; &gt;</type>
      <name>nonconstColImpl</name>
      <anchorfile>classThyra_1_1MultiVectorBase.html</anchorfile>
      <anchor>a001cf9476153f5e953e350c62660e87b</anchor>
      <arglist>(Ordinal j)=0</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual RCP&lt; const MultiVectorBase&lt; Scalar &gt; &gt;</type>
      <name>contigSubViewImpl</name>
      <anchorfile>classThyra_1_1MultiVectorBase.html</anchorfile>
      <anchor>a39d41d4f8caa190b8c16930af8d433b4</anchor>
      <arglist>(const Range1D &amp;colRng) const  =0</arglist>
      <docanchor file="classThyra_1_1MultiVectorBase">Thyra_MVB_subView_contiguous_const</docanchor>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual RCP&lt; MultiVectorBase&lt; Scalar &gt; &gt;</type>
      <name>nonconstContigSubViewImpl</name>
      <anchorfile>classThyra_1_1MultiVectorBase.html</anchorfile>
      <anchor>a8454d71dfa634137ac869ba7295fa388</anchor>
      <arglist>(const Range1D &amp;colRng)=0</arglist>
      <docanchor file="classThyra_1_1MultiVectorBase">Thyra_MVB_subView_contiguous_nonconst</docanchor>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual RCP&lt; const MultiVectorBase&lt; Scalar &gt; &gt;</type>
      <name>nonContigSubViewImpl</name>
      <anchorfile>classThyra_1_1MultiVectorBase.html</anchorfile>
      <anchor>a7ce43567fbd65682042fac4ac89ffe4c</anchor>
      <arglist>(const ArrayView&lt; const int &gt; &amp;cols) const  =0</arglist>
      <docanchor file="classThyra_1_1MultiVectorBase">Thyra_MVB_subView_noncontiguous_const</docanchor>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual RCP&lt; MultiVectorBase&lt; Scalar &gt; &gt;</type>
      <name>nonconstNonContigSubViewImpl</name>
      <anchorfile>classThyra_1_1MultiVectorBase.html</anchorfile>
      <anchor>a25689564da72e8ab023d7b91fab77bfa</anchor>
      <arglist>(const ArrayView&lt; const int &gt; &amp;cols)=0</arglist>
      <docanchor file="classThyra_1_1MultiVectorBase">Thyra_MVB_subView_noncontiguous_nonconst</docanchor>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual void</type>
      <name>mvMultiReductApplyOpImpl</name>
      <anchorfile>classThyra_1_1MultiVectorBase.html</anchorfile>
      <anchor>a40aca03b250b581babe7a5479bdae7ee</anchor>
      <arglist>(const RTOpPack::RTOpT&lt; Scalar &gt; &amp;primary_op, const ArrayView&lt; const Ptr&lt; const MultiVectorBase&lt; Scalar &gt; &gt; &gt; &amp;multi_vecs, const ArrayView&lt; const Ptr&lt; MultiVectorBase&lt; Scalar &gt; &gt; &gt; &amp;targ_multi_vecs, const ArrayView&lt; const Ptr&lt; RTOpPack::ReductTarget &gt; &gt; &amp;reduct_objs, const Ordinal primary_global_offset) const  =0</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual void</type>
      <name>mvSingleReductApplyOpImpl</name>
      <anchorfile>classThyra_1_1MultiVectorBase.html</anchorfile>
      <anchor>a36f956a368c4f99070b4ef2fd3e5081e</anchor>
      <arglist>(const RTOpPack::RTOpT&lt; Scalar &gt; &amp;primary_op, const RTOpPack::RTOpT&lt; Scalar &gt; &amp;secondary_op, const ArrayView&lt; const Ptr&lt; const MultiVectorBase&lt; Scalar &gt; &gt; &gt; &amp;multi_vecs, const ArrayView&lt; const Ptr&lt; MultiVectorBase&lt; Scalar &gt; &gt; &gt; &amp;targ_multi_vecs, const Ptr&lt; RTOpPack::ReductTarget &gt; &amp;reduct_obj, const Ordinal primary_global_offset) const  =0</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual void</type>
      <name>acquireDetachedMultiVectorViewImpl</name>
      <anchorfile>classThyra_1_1MultiVectorBase.html</anchorfile>
      <anchor>a9628a6064a8f97a84f8a70a441ebb574</anchor>
      <arglist>(const Range1D &amp;rowRng, const Range1D &amp;colRng, RTOpPack::ConstSubMultiVectorView&lt; Scalar &gt; *sub_mv) const  =0</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual void</type>
      <name>releaseDetachedMultiVectorViewImpl</name>
      <anchorfile>classThyra_1_1MultiVectorBase.html</anchorfile>
      <anchor>aed61552530ddc0ef20171f4ca2fdeadd</anchor>
      <arglist>(RTOpPack::ConstSubMultiVectorView&lt; Scalar &gt; *sub_mv) const  =0</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual void</type>
      <name>acquireNonconstDetachedMultiVectorViewImpl</name>
      <anchorfile>classThyra_1_1MultiVectorBase.html</anchorfile>
      <anchor>ac75f9dec20901fd9493590bd0265e5ea</anchor>
      <arglist>(const Range1D &amp;rowRng, const Range1D &amp;colRng, RTOpPack::SubMultiVectorView&lt; Scalar &gt; *sub_mv)=0</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual void</type>
      <name>commitNonconstDetachedMultiVectorViewImpl</name>
      <anchorfile>classThyra_1_1MultiVectorBase.html</anchorfile>
      <anchor>ac8e506bc0fd182c29f991d4593dc47f0</anchor>
      <arglist>(RTOpPack::SubMultiVectorView&lt; Scalar &gt; *sub_mv)=0</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual bool</type>
      <name>rowStatIsSupportedImpl</name>
      <anchorfile>classThyra_1_1MultiVectorBase.html</anchorfile>
      <anchor>a401b18b7c78ebc8217ebd46f17ae2f41</anchor>
      <arglist>(const RowStatLinearOpBaseUtils::ERowStat rowStat) const </arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual void</type>
      <name>getRowStatImpl</name>
      <anchorfile>classThyra_1_1MultiVectorBase.html</anchorfile>
      <anchor>a0e7e4bd749ed258c69fec358f594c9f0</anchor>
      <arglist>(const RowStatLinearOpBaseUtils::ERowStat rowStat, const Ptr&lt; VectorBase&lt; Scalar &gt; &gt; &amp;rowStatVec) const </arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual bool</type>
      <name>supportsScaleLeftImpl</name>
      <anchorfile>classThyra_1_1MultiVectorBase.html</anchorfile>
      <anchor>a2d3aff32f6fcfcd2112ab9adff58eaae</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual bool</type>
      <name>supportsScaleRightImpl</name>
      <anchorfile>classThyra_1_1MultiVectorBase.html</anchorfile>
      <anchor>aaa5f067a4057245a93f0a95d4b60e54e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual void</type>
      <name>scaleLeftImpl</name>
      <anchorfile>classThyra_1_1MultiVectorBase.html</anchorfile>
      <anchor>a0bb386d8709872e27abf1485973a4dab</anchor>
      <arglist>(const VectorBase&lt; Scalar &gt; &amp;row_scaling)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual void</type>
      <name>scaleRightImpl</name>
      <anchorfile>classThyra_1_1MultiVectorBase.html</anchorfile>
      <anchor>a54fecd0cb45162fa632dd9581b0f6936</anchor>
      <arglist>(const VectorBase&lt; Scalar &gt; &amp;col_scaling)</arglist>
    </member>
    <docanchor file="classThyra_1_1MultiVectorBase" title="Outline">Thyra_MVB_outline_sec</docanchor>
    <docanchor file="classThyra_1_1MultiVectorBase" title="Introduction">Thyra_MVB_intro_sec</docanchor>
    <docanchor file="classThyra_1_1MultiVectorBase" title="Changeable and non-changeable views">Thyra_MVB_views_sec</docanchor>
    <docanchor file="classThyra_1_1MultiVectorBase" title="Accessing the individual columns as vector views">Thyra_MVB_col_access_sec</docanchor>
    <docanchor file="classThyra_1_1MultiVectorBase" title="Accessing collections of columns as multi-vector views">Thyra_MVB_subviews_sec</docanchor>
    <docanchor file="classThyra_1_1MultiVectorBase" title="Common behavior of vector and multi-vector views">Thyra_MVB_view_behavior_sec</docanchor>
    <docanchor file="classThyra_1_1MultiVectorBase" title="MultiVectorBase as a linear operator">Thyra_MVB_as_LO_sec</docanchor>
    <docanchor file="classThyra_1_1MultiVectorBase" title="Multi-vector block updates">Thyra_MVB_block_update_sec</docanchor>
    <docanchor file="classThyra_1_1MultiVectorBase" title="Multi-vector block inner products">Thyra_MVB_block_inner_prod_sec</docanchor>
    <docanchor file="classThyra_1_1MultiVectorBase" title="Support for reduction/transformation operations">Thyra_MVB_RTOp_sec</docanchor>
    <docanchor file="classThyra_1_1MultiVectorBase" title="Collection of pre-written RTOps and wrapper functions">Thyra_MVB_rtop_collection_sec</docanchor>
    <docanchor file="classThyra_1_1MultiVectorBase" title="Explicit multi-vector coefficient access">Thyra_MVB_expl_access_sec</docanchor>
    <docanchor file="classThyra_1_1MultiVectorBase" title="Explicit multi-vector coefficient access utilities">Thyra_MVB_expl_access_utils_sec</docanchor>
    <docanchor file="classThyra_1_1MultiVectorBase" title="Notes for subclass developers">Thyra_MVB_dev_notes_sec</docanchor>
  </compound>
  <compound kind="class">
    <name>Thyra::MultiVectorDefaultBase</name>
    <filename>classThyra_1_1MultiVectorDefaultBase.html</filename>
    <templarg></templarg>
    <base virtualness="virtual">Thyra::MultiVectorBase</base>
    <base protection="protected" virtualness="virtual">Thyra::LinearOpDefaultBase</base>
    <member kind="function" virtualness="virtual">
      <type>virtual RCP&lt; MultiVectorBase&lt; Scalar &gt; &gt;</type>
      <name>clone_mv</name>
      <anchorfile>classThyra_1_1MultiVectorDefaultBase.html</anchorfile>
      <anchor>abed8f882feda50f278f6bc22aaff1628</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>assignImpl</name>
      <anchorfile>classThyra_1_1MultiVectorDefaultBase.html</anchorfile>
      <anchor>ad1fafd5c4e6bf0bc2c804e2781ae2470</anchor>
      <arglist>(Scalar alpha)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>RCP&lt; const MultiVectorBase&lt; Scalar &gt; &gt;</type>
      <name>contigSubViewImpl</name>
      <anchorfile>classThyra_1_1MultiVectorDefaultBase.html</anchorfile>
      <anchor>a2fc69a36fe2af9a926b4aff039e4eed2</anchor>
      <arglist>(const Range1D &amp;colRng) const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>RCP&lt; MultiVectorBase&lt; Scalar &gt; &gt;</type>
      <name>nonconstContigSubViewImpl</name>
      <anchorfile>classThyra_1_1MultiVectorDefaultBase.html</anchorfile>
      <anchor>ae4cddc057b49344861407ecfc93ed6c2</anchor>
      <arglist>(const Range1D &amp;colRng)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>RCP&lt; const MultiVectorBase&lt; Scalar &gt; &gt;</type>
      <name>nonContigSubViewImpl</name>
      <anchorfile>classThyra_1_1MultiVectorDefaultBase.html</anchorfile>
      <anchor>a329e943245ebf6f0cbc3c1bb0f945691</anchor>
      <arglist>(const ArrayView&lt; const int &gt; &amp;cols) const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>RCP&lt; MultiVectorBase&lt; Scalar &gt; &gt;</type>
      <name>nonconstNonContigSubViewImpl</name>
      <anchorfile>classThyra_1_1MultiVectorDefaultBase.html</anchorfile>
      <anchor>af1728b38b64109cd66117138483470f6</anchor>
      <arglist>(const ArrayView&lt; const int &gt; &amp;cols)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual void</type>
      <name>mvMultiReductApplyOpImpl</name>
      <anchorfile>classThyra_1_1MultiVectorDefaultBase.html</anchorfile>
      <anchor>a29dd5b11efa1d1ad56b68c99432bba9f</anchor>
      <arglist>(const RTOpPack::RTOpT&lt; Scalar &gt; &amp;primary_op, const ArrayView&lt; const Ptr&lt; const MultiVectorBase&lt; Scalar &gt; &gt; &gt; &amp;multi_vecs, const ArrayView&lt; const Ptr&lt; MultiVectorBase&lt; Scalar &gt; &gt; &gt; &amp;targ_multi_vecs, const ArrayView&lt; const Ptr&lt; RTOpPack::ReductTarget &gt; &gt; &amp;reduct_objs, const Ordinal primary_global_offset) const </arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual void</type>
      <name>mvSingleReductApplyOpImpl</name>
      <anchorfile>classThyra_1_1MultiVectorDefaultBase.html</anchorfile>
      <anchor>ad5e05aac53d3c6ac8ff46ef0832f86f9</anchor>
      <arglist>(const RTOpPack::RTOpT&lt; Scalar &gt; &amp;primary_op, const RTOpPack::RTOpT&lt; Scalar &gt; &amp;secondary_op, const ArrayView&lt; const Ptr&lt; const MultiVectorBase&lt; Scalar &gt; &gt; &gt; &amp;multi_vecs, const ArrayView&lt; const Ptr&lt; MultiVectorBase&lt; Scalar &gt; &gt; &gt; &amp;targ_multi_vecs, const Ptr&lt; RTOpPack::ReductTarget &gt; &amp;reduct_obj, const Ordinal primary_global_offset) const </arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual void</type>
      <name>acquireDetachedMultiVectorViewImpl</name>
      <anchorfile>classThyra_1_1MultiVectorDefaultBase.html</anchorfile>
      <anchor>a1e61eb98fe217165f3fa0fd1845cb50f</anchor>
      <arglist>(const Range1D &amp;rowRng, const Range1D &amp;colRng, RTOpPack::ConstSubMultiVectorView&lt; Scalar &gt; *sub_mv) const </arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual void</type>
      <name>releaseDetachedMultiVectorViewImpl</name>
      <anchorfile>classThyra_1_1MultiVectorDefaultBase.html</anchorfile>
      <anchor>ae8fb02cafde36f18c61631954f61f920</anchor>
      <arglist>(RTOpPack::ConstSubMultiVectorView&lt; Scalar &gt; *sub_mv) const </arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual void</type>
      <name>acquireNonconstDetachedMultiVectorViewImpl</name>
      <anchorfile>classThyra_1_1MultiVectorDefaultBase.html</anchorfile>
      <anchor>a339ee9011f96b5ce2605a205ac04fbc1</anchor>
      <arglist>(const Range1D &amp;rowRng, const Range1D &amp;colRng, RTOpPack::SubMultiVectorView&lt; Scalar &gt; *sub_mv)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual void</type>
      <name>commitNonconstDetachedMultiVectorViewImpl</name>
      <anchorfile>classThyra_1_1MultiVectorDefaultBase.html</anchorfile>
      <anchor>acfea48244f6d29ed3d5d379f9cdfb297</anchor>
      <arglist>(RTOpPack::SubMultiVectorView&lt; Scalar &gt; *sub_mv)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::MultiVectorFileIOBase</name>
    <filename>classThyra_1_1MultiVectorFileIOBase.html</filename>
    <templarg>Scalar</templarg>
    <base virtualness="virtual">VerboseObject&lt; MultiVectorFileIOBase&lt; Scalar &gt; &gt;</base>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>isCompatible</name>
      <anchorfile>classThyra_1_1MultiVectorFileIOBase.html</anchorfile>
      <anchor>adc07fc361014569d4b55b098356d5adc</anchor>
      <arglist>(const MultiVectorBase&lt; Scalar &gt; &amp;mv) const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>readMultiVectorFromFile</name>
      <anchorfile>classThyra_1_1MultiVectorFileIOBase.html</anchorfile>
      <anchor>a3c64564c6ebfb79099c9fe0bc90b7f6d</anchor>
      <arglist>(const std::string &amp;fileNameBase, Thyra::MultiVectorBase&lt; Scalar &gt; *mv) const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>writeMultiVectorToFile</name>
      <anchorfile>classThyra_1_1MultiVectorFileIOBase.html</anchorfile>
      <anchor>acc42144e60488fe7320e42d76f47d7df</anchor>
      <arglist>(const Thyra::MultiVectorBase&lt; Scalar &gt; &amp;mv, const std::string &amp;fileNameBase) const  =0</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; VectorBase&lt; Scalar &gt; &gt;</type>
      <name>readVectorFromFile</name>
      <anchorfile>classThyra_1_1MultiVectorFileIOBase.html</anchorfile>
      <anchor>ab7b2f741bd1a793f8041fb6797ce46ff</anchor>
      <arglist>(const MultiVectorFileIOBase&lt; Scalar &gt; &amp;fileIO, const std::string &amp;fileNameBase, const VectorSpaceBase&lt; Scalar &gt; &amp;vecSpc)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::MultiVectorRandomizerBase</name>
    <filename>classThyra_1_1MultiVectorRandomizerBase.html</filename>
    <templarg></templarg>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~MultiVectorRandomizerBase</name>
      <anchorfile>classThyra_1_1MultiVectorRandomizerBase.html</anchorfile>
      <anchor>a2549a3baf4abba90e67c0bfcd451e0fc</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>isCompatible</name>
      <anchorfile>classThyra_1_1MultiVectorRandomizerBase.html</anchorfile>
      <anchor>ae00b84abf4b82856b8cd185fb1438dea</anchor>
      <arglist>(const VectorSpaceBase&lt; Scalar &gt; &amp;space) const  =0</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>randomize</name>
      <anchorfile>classThyra_1_1MultiVectorRandomizerBase.html</anchorfile>
      <anchor>a911db5d1ede62aabfe03e0128fb26d49</anchor>
      <arglist>(const Ptr&lt; MultiVectorBase&lt; Scalar &gt; &gt; &amp;mv)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::MultiVectorStdOpsTester</name>
    <filename>classThyra_1_1MultiVectorStdOpsTester.html</filename>
    <templarg></templarg>
    <member kind="typedef">
      <type>Teuchos::ScalarTraits&lt; Scalar &gt;::magnitudeType</type>
      <name>ScalarMag</name>
      <anchorfile>classThyra_1_1MultiVectorStdOpsTester.html</anchorfile>
      <anchor>af975892f2066f2ccaf0b509e11777b8d</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classThyra_1_1MultiVectorStdOpsTester.html</anchorfile>
      <anchor>afbb39cc45e2b2cb455b2b855aa5e83be</anchor>
      <arglist>(ScalarMag, warning_tol)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classThyra_1_1MultiVectorStdOpsTester.html</anchorfile>
      <anchor>a17913d877b4ff6079d7b1516eee8dc5c</anchor>
      <arglist>(ScalarMag, error_tol)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classThyra_1_1MultiVectorStdOpsTester.html</anchorfile>
      <anchor>acbcc530a77f18ef99938d4547b76652e</anchor>
      <arglist>(int, num_mv_cols)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>MultiVectorStdOpsTester</name>
      <anchorfile>classThyra_1_1MultiVectorStdOpsTester.html</anchorfile>
      <anchor>a6c7ceb4427256fd548f8f3e95970cb94</anchor>
      <arglist>(const ScalarMag &amp;warning_tol=0, const ScalarMag &amp;error_tol=0, const int num_mv_cols=4)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>checkStdOps</name>
      <anchorfile>classThyra_1_1MultiVectorStdOpsTester.html</anchorfile>
      <anchor>a05edc08adb77a71e26a46a00c98d5f0c</anchor>
      <arglist>(const VectorSpaceBase&lt; Scalar &gt; &amp;vecSpc, std::ostream *out=0, const bool &amp;dumpAll=false)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::MultiVectorTester</name>
    <filename>classThyra_1_1MultiVectorTester.html</filename>
    <templarg>Scalar</templarg>
    <base>Teuchos::Describable</base>
    <member kind="typedef">
      <type>Teuchos::ScalarTraits&lt; Scalar &gt;::magnitudeType</type>
      <name>ScalarMag</name>
      <anchorfile>classThyra_1_1MultiVectorTester.html</anchorfile>
      <anchor>a694ab47c12a48c81699a89cf755bd5d9</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>LinearOpTester&lt; Scalar &gt; &amp;</type>
      <name>linearOpTester</name>
      <anchorfile>classThyra_1_1MultiVectorTester.html</anchorfile>
      <anchor>a53b559e7dfa520cb2500e723d0ca29be</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const LinearOpTester&lt; Scalar &gt; &amp;</type>
      <name>linearOpTester</name>
      <anchorfile>classThyra_1_1MultiVectorTester.html</anchorfile>
      <anchor>afaf9b9f60a928daee95102b42343249d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>warning_tol</name>
      <anchorfile>classThyra_1_1MultiVectorTester.html</anchorfile>
      <anchor>ae719537d9b99447af1cbeee62398de12</anchor>
      <arglist>(const ScalarMag &amp;warning_tol)</arglist>
    </member>
    <member kind="function">
      <type>ScalarMag</type>
      <name>warning_tol</name>
      <anchorfile>classThyra_1_1MultiVectorTester.html</anchorfile>
      <anchor>a4f929d561cdce321dbe0fd5100f00145</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>error_tol</name>
      <anchorfile>classThyra_1_1MultiVectorTester.html</anchorfile>
      <anchor>a12cbb591b8c7a947f222a55c2f384a5c</anchor>
      <arglist>(const ScalarMag &amp;error_tol)</arglist>
    </member>
    <member kind="function">
      <type>ScalarMag</type>
      <name>error_tol</name>
      <anchorfile>classThyra_1_1MultiVectorTester.html</anchorfile>
      <anchor>a1579616d7d6a22aa3ebdd920cf3c6fa7</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>num_random_vectors</name>
      <anchorfile>classThyra_1_1MultiVectorTester.html</anchorfile>
      <anchor>a46eb3221260e8e43f78283e48abe4167</anchor>
      <arglist>(const int num_random_vectors)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>num_random_vectors</name>
      <anchorfile>classThyra_1_1MultiVectorTester.html</anchorfile>
      <anchor>a314157cb33f316e5a9f459ca5e448a5e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>show_all_tests</name>
      <anchorfile>classThyra_1_1MultiVectorTester.html</anchorfile>
      <anchor>a4da92feb41b4f4a01f3b8603e32ac266</anchor>
      <arglist>(const bool show_all_tests)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>show_all_tests</name>
      <anchorfile>classThyra_1_1MultiVectorTester.html</anchorfile>
      <anchor>a2e34ed53efe8508d1d81258715d6dd45</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>dump_all</name>
      <anchorfile>classThyra_1_1MultiVectorTester.html</anchorfile>
      <anchor>ae6dd3a03c96c3b24959d9a08c2728e35</anchor>
      <arglist>(const bool dump_all)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>dump_all</name>
      <anchorfile>classThyra_1_1MultiVectorTester.html</anchorfile>
      <anchor>a66400a1c172136113dfd089d91b2954c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>MultiVectorTester</name>
      <anchorfile>classThyra_1_1MultiVectorTester.html</anchorfile>
      <anchor>ab7dfd20ba6bbda24bff8362bee37d11a</anchor>
      <arglist>(const ScalarMag warning_tol=1e-13, const ScalarMag error_tol=1e-10, const int num_random_vectors=1, const bool show_all_tests=false, const bool dump_all=false)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>checkMultiVector</name>
      <anchorfile>classThyra_1_1MultiVectorTester.html</anchorfile>
      <anchor>a00043c90d20c13b9e25ff0a1ca974e70</anchor>
      <arglist>(const VectorSpaceBase&lt; Scalar &gt; &amp;vs, const Ptr&lt; Teuchos::FancyOStream &gt; &amp;out) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>check</name>
      <anchorfile>classThyra_1_1MultiVectorTester.html</anchorfile>
      <anchor>acd6245530be69fdf86bf5ff94595066f</anchor>
      <arglist>(const MultiVectorBase&lt; Scalar &gt; &amp;mv, const Ptr&lt; Teuchos::FancyOStream &gt; &amp;out) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::NonlinearSolverBase</name>
    <filename>classThyra_1_1NonlinearSolverBase.html</filename>
    <templarg>Scalar</templarg>
    <base virtualness="virtual">Teuchos::Describable</base>
    <base virtualness="virtual">VerboseObject&lt; NonlinearSolverBase&lt; Scalar &gt; &gt;</base>
    <base virtualness="virtual">Teuchos::ParameterListAcceptor</base>
    <member kind="function">
      <type>const SolveStatus&lt; Scalar &gt;</type>
      <name>solve</name>
      <anchorfile>classThyra_1_1NonlinearSolverBase.html</anchorfile>
      <anchor>a4be4fc595b731b6d0689f91c89f9fbc0</anchor>
      <arglist>(NonlinearSolverBase&lt; Scalar &gt; &amp;nonlinearSolver, VectorBase&lt; Scalar &gt; *x, const SolveCriteria&lt; Scalar &gt; *solveCriteria=NULL, VectorBase&lt; Scalar &gt; *delta=NULL)</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>setModel</name>
      <anchorfile>classThyra_1_1NonlinearSolverBase.html</anchorfile>
      <anchor>aa1a9a5858256b648301c081fbf0c45ae</anchor>
      <arglist>(const RCP&lt; const ModelEvaluator&lt; Scalar &gt; &gt; &amp;model)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual RCP&lt; const ModelEvaluator&lt; Scalar &gt; &gt;</type>
      <name>getModel</name>
      <anchorfile>classThyra_1_1NonlinearSolverBase.html</anchorfile>
      <anchor>afe67c894729bdb546f2c57ee7bb7c352</anchor>
      <arglist>() const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual SolveStatus&lt; Scalar &gt;</type>
      <name>solve</name>
      <anchorfile>classThyra_1_1NonlinearSolverBase.html</anchorfile>
      <anchor>a63d57f0f196cc3e87dd025bcea276f9b</anchor>
      <arglist>(VectorBase&lt; Scalar &gt; *x, const SolveCriteria&lt; Scalar &gt; *solveCriteria=NULL, VectorBase&lt; Scalar &gt; *delta=NULL)=0</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>supportsCloning</name>
      <anchorfile>classThyra_1_1NonlinearSolverBase.html</anchorfile>
      <anchor>a11e776fa8f1bff31cc8fec4b4e0c092b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual RCP&lt; NonlinearSolverBase&lt; Scalar &gt; &gt;</type>
      <name>cloneNonlinearSolver</name>
      <anchorfile>classThyra_1_1NonlinearSolverBase.html</anchorfile>
      <anchor>a29b8d0292a16acc9f1fa25631821f74f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual RCP&lt; const VectorBase&lt; Scalar &gt; &gt;</type>
      <name>get_current_x</name>
      <anchorfile>classThyra_1_1NonlinearSolverBase.html</anchorfile>
      <anchor>ae59243cc34166a2c760c399403d389d9</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>is_W_current</name>
      <anchorfile>classThyra_1_1NonlinearSolverBase.html</anchorfile>
      <anchor>a57a49a439c9a3c1726d6eda12601c187</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual RCP&lt; LinearOpWithSolveBase&lt; Scalar &gt; &gt;</type>
      <name>get_nonconst_W</name>
      <anchorfile>classThyra_1_1NonlinearSolverBase.html</anchorfile>
      <anchor>a5b0065920defe32a5fca2b772651569e</anchor>
      <arglist>(const bool forceUpToDate=false)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual RCP&lt; const LinearOpWithSolveBase&lt; Scalar &gt; &gt;</type>
      <name>get_W</name>
      <anchorfile>classThyra_1_1NonlinearSolverBase.html</anchorfile>
      <anchor>ab98a2f40abcf71c28f2d8750a1638d42</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>set_W_is_current</name>
      <anchorfile>classThyra_1_1NonlinearSolverBase.html</anchorfile>
      <anchor>a015b99b18caa28727539440ab99ecd90</anchor>
      <arglist>(bool W_is_current)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::NullLinearOpChanger</name>
    <filename>classThyra_1_1NullLinearOpChanger.html</filename>
    <templarg></templarg>
    <base>Thyra::LinearOpChanger</base>
    <member kind="function">
      <type>void</type>
      <name>changeOp</name>
      <anchorfile>classThyra_1_1NullLinearOpChanger.html</anchorfile>
      <anchor>af4496ff07ab84b82f52692453fbaab41</anchor>
      <arglist>(const Teuchos::Ptr&lt; LinearOpBase&lt; Scalar &gt; &gt; &amp;op) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::Exceptions::OpNotSupported</name>
    <filename>classThyra_1_1Exceptions_1_1OpNotSupported.html</filename>
  </compound>
  <compound kind="class">
    <name>Thyra::ModelEvaluatorBase::OutArgs</name>
    <filename>classThyra_1_1ModelEvaluatorBase_1_1OutArgs.html</filename>
    <templarg>Scalar</templarg>
    <base>Teuchos::Describable</base>
    <member kind="function">
      <type></type>
      <name>OutArgs</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1OutArgs.html</anchorfile>
      <anchor>a9f293a2fa6db9955430f6507d5f8fd30</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Np</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1OutArgs.html</anchorfile>
      <anchor>aa31bb9aa24583daeecb0e19ba5fd290a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Ng</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1OutArgs.html</anchorfile>
      <anchor>a5800e69a7c746df4f95f852aa5d35ddc</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>supports</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1OutArgs.html</anchorfile>
      <anchor>acc98f78a921f27b6b3cbb110f0a52981</anchor>
      <arglist>(EOutArgsMembers arg) const </arglist>
    </member>
    <member kind="function">
      <type>const DerivativeSupport &amp;</type>
      <name>supports</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1OutArgs.html</anchorfile>
      <anchor>ae11f560751fe184847d823c879e3a6bc</anchor>
      <arglist>(EOutArgsDfDp arg, int l) const </arglist>
    </member>
    <member kind="function">
      <type>const DerivativeSupport &amp;</type>
      <name>supports</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1OutArgs.html</anchorfile>
      <anchor>ac4b9535a8e5e0cb5abbf52efcb042ee5</anchor>
      <arglist>(EOutArgsDgDx_dot arg, int j) const </arglist>
    </member>
    <member kind="function">
      <type>const DerivativeSupport &amp;</type>
      <name>supports</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1OutArgs.html</anchorfile>
      <anchor>a81f8f16d3967b32c5fac54129a3e2ddb</anchor>
      <arglist>(EOutArgsDgDx arg, int j) const </arglist>
    </member>
    <member kind="function">
      <type>const DerivativeSupport &amp;</type>
      <name>supports</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1OutArgs.html</anchorfile>
      <anchor>ae3b4d11221dfce6e3bc99b0142f86561</anchor>
      <arglist>(EOutArgsDgDp arg, int j, int l) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_f</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1OutArgs.html</anchorfile>
      <anchor>a49401b1b3d2af1a2ee2bdb10c78a7830</anchor>
      <arglist>(const Evaluation&lt; VectorBase&lt; Scalar &gt; &gt; &amp;f)</arglist>
    </member>
    <member kind="function">
      <type>Evaluation&lt; VectorBase&lt; Scalar &gt; &gt;</type>
      <name>get_f</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1OutArgs.html</anchorfile>
      <anchor>a7c8885dab35667c857ac3c5b9242fee8</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_g</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1OutArgs.html</anchorfile>
      <anchor>af26b648579eb585d84e63570f080d485</anchor>
      <arglist>(int j, const Evaluation&lt; VectorBase&lt; Scalar &gt; &gt; &amp;g_j)</arglist>
    </member>
    <member kind="function">
      <type>Evaluation&lt; VectorBase&lt; Scalar &gt; &gt;</type>
      <name>get_g</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1OutArgs.html</anchorfile>
      <anchor>a83d186d16d9f8f221ea287027c20371f</anchor>
      <arglist>(int j) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_W</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1OutArgs.html</anchorfile>
      <anchor>a636ec5ac52ed874137da252b4d681a2b</anchor>
      <arglist>(const RCP&lt; LinearOpWithSolveBase&lt; Scalar &gt; &gt; &amp;W)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; LinearOpWithSolveBase&lt; Scalar &gt; &gt;</type>
      <name>get_W</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1OutArgs.html</anchorfile>
      <anchor>a9bc25b0b2a5f024bed795e3935e14812</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_f_mp</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1OutArgs.html</anchorfile>
      <anchor>a3e98bda916dda5fb81ec8bedc63ba970</anchor>
      <arglist>(const RCP&lt; Stokhos::ProductEpetraVector &gt; &amp;f_mp)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; Stokhos::ProductEpetraVector &gt;</type>
      <name>get_f_mp</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1OutArgs.html</anchorfile>
      <anchor>a871f6107e9756b8f9f927f3ea4935cfa</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_g_mp</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1OutArgs.html</anchorfile>
      <anchor>af5636a38b4e8eac0774c5bfc4b9b4a1b</anchor>
      <arglist>(int j, const RCP&lt; Stokhos::ProductEpetraVector &gt; &amp;g_mp_j)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; Stokhos::ProductEpetraVector &gt;</type>
      <name>get_g_mp</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1OutArgs.html</anchorfile>
      <anchor>abe06fc7b3edffb066706ac9e56e4b411</anchor>
      <arglist>(int j) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_W_mp</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1OutArgs.html</anchorfile>
      <anchor>a828a529269716eaa848e2747add5090c</anchor>
      <arglist>(const RCP&lt; Stokhos::ProductEpetraOperator &gt; &amp;W_mp)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; Stokhos::ProductEpetraOperator &gt;</type>
      <name>get_W_mp</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1OutArgs.html</anchorfile>
      <anchor>abf82f6447caec9c1869a082cdbc21406</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_W_op</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1OutArgs.html</anchorfile>
      <anchor>aaf5ca0f719068ae24719dbb0a97a5522</anchor>
      <arglist>(const RCP&lt; LinearOpBase&lt; Scalar &gt; &gt; &amp;W_op)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; LinearOpBase&lt; Scalar &gt; &gt;</type>
      <name>get_W_op</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1OutArgs.html</anchorfile>
      <anchor>a57e1d874082fa684d6bc84825407a356</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_W_prec</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1OutArgs.html</anchorfile>
      <anchor>a77f0698f618678ecc98809bab5b6a785</anchor>
      <arglist>(const RCP&lt; PreconditionerBase&lt; Scalar &gt; &gt; &amp;W_prec)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; PreconditionerBase&lt; Scalar &gt; &gt;</type>
      <name>get_W_prec</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1OutArgs.html</anchorfile>
      <anchor>a938d85faef3efcf8e36b5fcd38bbe90f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>DerivativeProperties</type>
      <name>get_W_properties</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1OutArgs.html</anchorfile>
      <anchor>ae8cbf475f2c9320c6e546a8ec20ed299</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_DfDp</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1OutArgs.html</anchorfile>
      <anchor>a6aac2d38c1975f03b1af577ae0afd9d6</anchor>
      <arglist>(int l, const Derivative&lt; Scalar &gt; &amp;DfDp_l)</arglist>
    </member>
    <member kind="function">
      <type>Derivative&lt; Scalar &gt;</type>
      <name>get_DfDp</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1OutArgs.html</anchorfile>
      <anchor>a879376b6aefd607bc3455b1844503277</anchor>
      <arglist>(int l) const </arglist>
    </member>
    <member kind="function">
      <type>DerivativeProperties</type>
      <name>get_DfDp_properties</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1OutArgs.html</anchorfile>
      <anchor>a9ec9de441b7b97507cd87b2c8edeec79</anchor>
      <arglist>(int l) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_DgDx_dot</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1OutArgs.html</anchorfile>
      <anchor>a9e02654424dac33256e052ab74960855</anchor>
      <arglist>(int j, const Derivative&lt; Scalar &gt; &amp;DgDx_dot_j)</arglist>
    </member>
    <member kind="function">
      <type>Derivative&lt; Scalar &gt;</type>
      <name>get_DgDx_dot</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1OutArgs.html</anchorfile>
      <anchor>ad84b91fb4acfb1744304d99befa79458</anchor>
      <arglist>(int j) const </arglist>
    </member>
    <member kind="function">
      <type>DerivativeProperties</type>
      <name>get_DgDx_dot_properties</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1OutArgs.html</anchorfile>
      <anchor>a3efbf6839d08c1d5eb8362ba632d7248</anchor>
      <arglist>(int j) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_DgDx</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1OutArgs.html</anchorfile>
      <anchor>a8a4b84dee5df43a4364dbe8c0d4a8ec6</anchor>
      <arglist>(int j, const Derivative&lt; Scalar &gt; &amp;DgDx_j)</arglist>
    </member>
    <member kind="function">
      <type>Derivative&lt; Scalar &gt;</type>
      <name>get_DgDx</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1OutArgs.html</anchorfile>
      <anchor>a5ac317e97c5fd6bd0ccd5439d2083795</anchor>
      <arglist>(int j) const </arglist>
    </member>
    <member kind="function">
      <type>DerivativeProperties</type>
      <name>get_DgDx_properties</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1OutArgs.html</anchorfile>
      <anchor>a81f331a43bbaa66cb1d298a0cf0f48bd</anchor>
      <arglist>(int j) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_DgDp</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1OutArgs.html</anchorfile>
      <anchor>ad0c598dffa3e1635ddaba88d4174db1f</anchor>
      <arglist>(int j, int l, const Derivative&lt; Scalar &gt; &amp;DgDp_j_l)</arglist>
    </member>
    <member kind="function">
      <type>Derivative&lt; Scalar &gt;</type>
      <name>get_DgDp</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1OutArgs.html</anchorfile>
      <anchor>ac7b423c7ce83779bad099b04850dbef6</anchor>
      <arglist>(int j, int l) const </arglist>
    </member>
    <member kind="function">
      <type>DerivativeProperties</type>
      <name>get_DgDp_properties</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1OutArgs.html</anchorfile>
      <anchor>aec675c3c8e88468faee20cfe5446e40a</anchor>
      <arglist>(int j, int l) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setArgs</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1OutArgs.html</anchorfile>
      <anchor>a34e0ce3ad62038e8d1db0bd3e3a3fb90</anchor>
      <arglist>(const OutArgs&lt; Scalar &gt; &amp;outArgs, bool ignoreUnsupported=false)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setFailed</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1OutArgs.html</anchorfile>
      <anchor>ad6531ba6985dd5d7042cdcef1d743a59</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isFailed</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1OutArgs.html</anchorfile>
      <anchor>a6e4b214a4b6e5f59a5945f5bb05353c4</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isEmpty</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1OutArgs.html</anchorfile>
      <anchor>ac3865e02a82770f953fa533895234d50</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>assertSameSupport</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1OutArgs.html</anchorfile>
      <anchor>a95501452836bfb77888c03e938f336cf</anchor>
      <arglist>(const OutArgs&lt; Scalar &gt; &amp;outArgs) const </arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>modelEvalDescription</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1OutArgs.html</anchorfile>
      <anchor>a2a0386bdb399f83fc7af058fb314c222</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>description</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1OutArgs.html</anchorfile>
      <anchor>ae3052c89cb7b6605cbfa6f628ec6afcc</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>describe</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1OutArgs.html</anchorfile>
      <anchor>a5d59e0efe6fb81a27b424f160f713294</anchor>
      <arglist>(Teuchos::FancyOStream &amp;out, const Teuchos::EVerbosityLevel verbLevel) const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>_setModelEvalDescription</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1OutArgs.html</anchorfile>
      <anchor>ae9210ccb94d04aa45840d52e3081c6fd</anchor>
      <arglist>(const std::string &amp;modelEvalDescription)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>_set_Np_Ng</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1OutArgs.html</anchorfile>
      <anchor>a79a9acfddf2cda2f18b15cd9dada603e</anchor>
      <arglist>(int Np, int Ng)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>_setSupports</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1OutArgs.html</anchorfile>
      <anchor>a0c2ff536ebcdc50d2ca658401db413d0</anchor>
      <arglist>(EOutArgsMembers arg, bool supports)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>_setSupports</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1OutArgs.html</anchorfile>
      <anchor>aee40d4c9c5507bc8b6f313452108a774</anchor>
      <arglist>(EOutArgsDfDp arg, int l, const DerivativeSupport &amp;)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>_setSupports</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1OutArgs.html</anchorfile>
      <anchor>a4b655c863b7054af8ad37eae769d5eb7</anchor>
      <arglist>(EOutArgsDgDx_dot arg, int j, const DerivativeSupport &amp;)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>_setSupports</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1OutArgs.html</anchorfile>
      <anchor>a0fc7b13e2f8f51e06bd852c927b33490</anchor>
      <arglist>(EOutArgsDgDx arg, int j, const DerivativeSupport &amp;)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>_setSupports</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1OutArgs.html</anchorfile>
      <anchor>a7bc3ddf839c51fcac7758824b1869d0c</anchor>
      <arglist>(EOutArgsDgDp arg, int j, int l, const DerivativeSupport &amp;)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>_set_W_properties</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1OutArgs.html</anchorfile>
      <anchor>aec340a1b24429da7ea885ec239471f1b</anchor>
      <arglist>(const DerivativeProperties &amp;properties)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>_set_DfDp_properties</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1OutArgs.html</anchorfile>
      <anchor>a004d062b0ee14742ffe961aa6931a093</anchor>
      <arglist>(int l, const DerivativeProperties &amp;properties)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>_set_DgDx_dot_properties</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1OutArgs.html</anchorfile>
      <anchor>a0d75ff3b026b08909588b21cfc856ac4</anchor>
      <arglist>(int j, const DerivativeProperties &amp;properties)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>_set_DgDx_properties</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1OutArgs.html</anchorfile>
      <anchor>a4f0f5c5d6d2c5f674725ddcee5680ace</anchor>
      <arglist>(int j, const DerivativeProperties &amp;properties)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>_set_DgDp_properties</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1OutArgs.html</anchorfile>
      <anchor>a82a0f02e39978651161663ef692d2b6d</anchor>
      <arglist>(int j, int l, const DerivativeProperties &amp;properties)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>_setSupports</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1OutArgs.html</anchorfile>
      <anchor>a2083d8e4933f28926a06403840edda81</anchor>
      <arglist>(const OutArgs&lt; Scalar &gt; &amp;inputOutArgs)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>_setUnsupportsAndRelated</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1OutArgs.html</anchorfile>
      <anchor>afe22c4e6e922447f9605640b696ceaa8</anchor>
      <arglist>(EInArgsMembers arg)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>_setUnsupportsAndRelated</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1OutArgs.html</anchorfile>
      <anchor>a4f1e3b10d43c7585483f341e529d9ad1</anchor>
      <arglist>(EOutArgsMembers arg)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>OutArgs&lt; double &gt;</name>
    <filename>classThyra_1_1ModelEvaluatorBase_1_1OutArgs.html</filename>
    <base>Teuchos::Describable</base>
    <member kind="function">
      <type></type>
      <name>OutArgs</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1OutArgs.html</anchorfile>
      <anchor>a9f293a2fa6db9955430f6507d5f8fd30</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Np</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1OutArgs.html</anchorfile>
      <anchor>aa31bb9aa24583daeecb0e19ba5fd290a</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Ng</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1OutArgs.html</anchorfile>
      <anchor>a5800e69a7c746df4f95f852aa5d35ddc</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>supports</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1OutArgs.html</anchorfile>
      <anchor>acc98f78a921f27b6b3cbb110f0a52981</anchor>
      <arglist>(EOutArgsMembers arg) const</arglist>
    </member>
    <member kind="function">
      <type>const DerivativeSupport &amp;</type>
      <name>supports</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1OutArgs.html</anchorfile>
      <anchor>ae11f560751fe184847d823c879e3a6bc</anchor>
      <arglist>(EOutArgsDfDp arg, int l) const</arglist>
    </member>
    <member kind="function">
      <type>const DerivativeSupport &amp;</type>
      <name>supports</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1OutArgs.html</anchorfile>
      <anchor>ac4b9535a8e5e0cb5abbf52efcb042ee5</anchor>
      <arglist>(EOutArgsDgDx_dot arg, int j) const</arglist>
    </member>
    <member kind="function">
      <type>const DerivativeSupport &amp;</type>
      <name>supports</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1OutArgs.html</anchorfile>
      <anchor>a81f8f16d3967b32c5fac54129a3e2ddb</anchor>
      <arglist>(EOutArgsDgDx arg, int j) const</arglist>
    </member>
    <member kind="function">
      <type>const DerivativeSupport &amp;</type>
      <name>supports</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1OutArgs.html</anchorfile>
      <anchor>ae3b4d11221dfce6e3bc99b0142f86561</anchor>
      <arglist>(EOutArgsDgDp arg, int j, int l) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_f</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1OutArgs.html</anchorfile>
      <anchor>a49401b1b3d2af1a2ee2bdb10c78a7830</anchor>
      <arglist>(const Evaluation&lt; VectorBase&lt; double &gt; &gt; &amp;f)</arglist>
    </member>
    <member kind="function">
      <type>Evaluation&lt; VectorBase&lt; double &gt; &gt;</type>
      <name>get_f</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1OutArgs.html</anchorfile>
      <anchor>a7c8885dab35667c857ac3c5b9242fee8</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_g</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1OutArgs.html</anchorfile>
      <anchor>af26b648579eb585d84e63570f080d485</anchor>
      <arglist>(int j, const Evaluation&lt; VectorBase&lt; double &gt; &gt; &amp;g_j)</arglist>
    </member>
    <member kind="function">
      <type>Evaluation&lt; VectorBase&lt; double &gt; &gt;</type>
      <name>get_g</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1OutArgs.html</anchorfile>
      <anchor>a83d186d16d9f8f221ea287027c20371f</anchor>
      <arglist>(int j) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_W</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1OutArgs.html</anchorfile>
      <anchor>a636ec5ac52ed874137da252b4d681a2b</anchor>
      <arglist>(const RCP&lt; LinearOpWithSolveBase&lt; double &gt; &gt; &amp;W)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; LinearOpWithSolveBase&lt; double &gt; &gt;</type>
      <name>get_W</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1OutArgs.html</anchorfile>
      <anchor>a9bc25b0b2a5f024bed795e3935e14812</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_f_mp</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1OutArgs.html</anchorfile>
      <anchor>a3e98bda916dda5fb81ec8bedc63ba970</anchor>
      <arglist>(const RCP&lt; Stokhos::ProductEpetraVector &gt; &amp;f_mp)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; Stokhos::ProductEpetraVector &gt;</type>
      <name>get_f_mp</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1OutArgs.html</anchorfile>
      <anchor>a871f6107e9756b8f9f927f3ea4935cfa</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_g_mp</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1OutArgs.html</anchorfile>
      <anchor>af5636a38b4e8eac0774c5bfc4b9b4a1b</anchor>
      <arglist>(int j, const RCP&lt; Stokhos::ProductEpetraVector &gt; &amp;g_mp_j)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; Stokhos::ProductEpetraVector &gt;</type>
      <name>get_g_mp</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1OutArgs.html</anchorfile>
      <anchor>abe06fc7b3edffb066706ac9e56e4b411</anchor>
      <arglist>(int j) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_W_mp</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1OutArgs.html</anchorfile>
      <anchor>a828a529269716eaa848e2747add5090c</anchor>
      <arglist>(const RCP&lt; Stokhos::ProductEpetraOperator &gt; &amp;W_mp)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; Stokhos::ProductEpetraOperator &gt;</type>
      <name>get_W_mp</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1OutArgs.html</anchorfile>
      <anchor>abf82f6447caec9c1869a082cdbc21406</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_W_op</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1OutArgs.html</anchorfile>
      <anchor>aaf5ca0f719068ae24719dbb0a97a5522</anchor>
      <arglist>(const RCP&lt; LinearOpBase&lt; double &gt; &gt; &amp;W_op)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; LinearOpBase&lt; double &gt; &gt;</type>
      <name>get_W_op</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1OutArgs.html</anchorfile>
      <anchor>a57e1d874082fa684d6bc84825407a356</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_W_prec</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1OutArgs.html</anchorfile>
      <anchor>a77f0698f618678ecc98809bab5b6a785</anchor>
      <arglist>(const RCP&lt; PreconditionerBase&lt; double &gt; &gt; &amp;W_prec)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; PreconditionerBase&lt; double &gt; &gt;</type>
      <name>get_W_prec</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1OutArgs.html</anchorfile>
      <anchor>a938d85faef3efcf8e36b5fcd38bbe90f</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>DerivativeProperties</type>
      <name>get_W_properties</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1OutArgs.html</anchorfile>
      <anchor>ae8cbf475f2c9320c6e546a8ec20ed299</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_DfDp</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1OutArgs.html</anchorfile>
      <anchor>a6aac2d38c1975f03b1af577ae0afd9d6</anchor>
      <arglist>(int l, const Derivative&lt; double &gt; &amp;DfDp_l)</arglist>
    </member>
    <member kind="function">
      <type>Derivative&lt; double &gt;</type>
      <name>get_DfDp</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1OutArgs.html</anchorfile>
      <anchor>a879376b6aefd607bc3455b1844503277</anchor>
      <arglist>(int l) const</arglist>
    </member>
    <member kind="function">
      <type>DerivativeProperties</type>
      <name>get_DfDp_properties</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1OutArgs.html</anchorfile>
      <anchor>a9ec9de441b7b97507cd87b2c8edeec79</anchor>
      <arglist>(int l) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_DgDx_dot</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1OutArgs.html</anchorfile>
      <anchor>a9e02654424dac33256e052ab74960855</anchor>
      <arglist>(int j, const Derivative&lt; double &gt; &amp;DgDx_dot_j)</arglist>
    </member>
    <member kind="function">
      <type>Derivative&lt; double &gt;</type>
      <name>get_DgDx_dot</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1OutArgs.html</anchorfile>
      <anchor>ad84b91fb4acfb1744304d99befa79458</anchor>
      <arglist>(int j) const</arglist>
    </member>
    <member kind="function">
      <type>DerivativeProperties</type>
      <name>get_DgDx_dot_properties</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1OutArgs.html</anchorfile>
      <anchor>a3efbf6839d08c1d5eb8362ba632d7248</anchor>
      <arglist>(int j) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_DgDx</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1OutArgs.html</anchorfile>
      <anchor>a8a4b84dee5df43a4364dbe8c0d4a8ec6</anchor>
      <arglist>(int j, const Derivative&lt; double &gt; &amp;DgDx_j)</arglist>
    </member>
    <member kind="function">
      <type>Derivative&lt; double &gt;</type>
      <name>get_DgDx</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1OutArgs.html</anchorfile>
      <anchor>a5ac317e97c5fd6bd0ccd5439d2083795</anchor>
      <arglist>(int j) const</arglist>
    </member>
    <member kind="function">
      <type>DerivativeProperties</type>
      <name>get_DgDx_properties</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1OutArgs.html</anchorfile>
      <anchor>a81f331a43bbaa66cb1d298a0cf0f48bd</anchor>
      <arglist>(int j) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_DgDp</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1OutArgs.html</anchorfile>
      <anchor>ad0c598dffa3e1635ddaba88d4174db1f</anchor>
      <arglist>(int j, int l, const Derivative&lt; double &gt; &amp;DgDp_j_l)</arglist>
    </member>
    <member kind="function">
      <type>Derivative&lt; double &gt;</type>
      <name>get_DgDp</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1OutArgs.html</anchorfile>
      <anchor>ac7b423c7ce83779bad099b04850dbef6</anchor>
      <arglist>(int j, int l) const</arglist>
    </member>
    <member kind="function">
      <type>DerivativeProperties</type>
      <name>get_DgDp_properties</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1OutArgs.html</anchorfile>
      <anchor>aec675c3c8e88468faee20cfe5446e40a</anchor>
      <arglist>(int j, int l) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setArgs</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1OutArgs.html</anchorfile>
      <anchor>a34e0ce3ad62038e8d1db0bd3e3a3fb90</anchor>
      <arglist>(const OutArgs&lt; double &gt; &amp;outArgs, bool ignoreUnsupported=false)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setFailed</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1OutArgs.html</anchorfile>
      <anchor>ad6531ba6985dd5d7042cdcef1d743a59</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isFailed</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1OutArgs.html</anchorfile>
      <anchor>a6e4b214a4b6e5f59a5945f5bb05353c4</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isEmpty</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1OutArgs.html</anchorfile>
      <anchor>ac3865e02a82770f953fa533895234d50</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>assertSameSupport</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1OutArgs.html</anchorfile>
      <anchor>a95501452836bfb77888c03e938f336cf</anchor>
      <arglist>(const OutArgs&lt; double &gt; &amp;outArgs) const</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>modelEvalDescription</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1OutArgs.html</anchorfile>
      <anchor>a2a0386bdb399f83fc7af058fb314c222</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>description</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1OutArgs.html</anchorfile>
      <anchor>ae3052c89cb7b6605cbfa6f628ec6afcc</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>describe</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1OutArgs.html</anchorfile>
      <anchor>a5d59e0efe6fb81a27b424f160f713294</anchor>
      <arglist>(Teuchos::FancyOStream &amp;out, const Teuchos::EVerbosityLevel verbLevel) const</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>_setModelEvalDescription</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1OutArgs.html</anchorfile>
      <anchor>ae9210ccb94d04aa45840d52e3081c6fd</anchor>
      <arglist>(const std::string &amp;modelEvalDescription)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>_set_Np_Ng</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1OutArgs.html</anchorfile>
      <anchor>a79a9acfddf2cda2f18b15cd9dada603e</anchor>
      <arglist>(int Np, int Ng)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>_setSupports</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1OutArgs.html</anchorfile>
      <anchor>a0c2ff536ebcdc50d2ca658401db413d0</anchor>
      <arglist>(EOutArgsMembers arg, bool supports)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>_setSupports</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1OutArgs.html</anchorfile>
      <anchor>aee40d4c9c5507bc8b6f313452108a774</anchor>
      <arglist>(EOutArgsDfDp arg, int l, const DerivativeSupport &amp;)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>_setSupports</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1OutArgs.html</anchorfile>
      <anchor>a4b655c863b7054af8ad37eae769d5eb7</anchor>
      <arglist>(EOutArgsDgDx_dot arg, int j, const DerivativeSupport &amp;)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>_setSupports</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1OutArgs.html</anchorfile>
      <anchor>a0fc7b13e2f8f51e06bd852c927b33490</anchor>
      <arglist>(EOutArgsDgDx arg, int j, const DerivativeSupport &amp;)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>_setSupports</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1OutArgs.html</anchorfile>
      <anchor>a7bc3ddf839c51fcac7758824b1869d0c</anchor>
      <arglist>(EOutArgsDgDp arg, int j, int l, const DerivativeSupport &amp;)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>_setSupports</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1OutArgs.html</anchorfile>
      <anchor>a2083d8e4933f28926a06403840edda81</anchor>
      <arglist>(const OutArgs&lt; double &gt; &amp;inputOutArgs)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>_set_W_properties</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1OutArgs.html</anchorfile>
      <anchor>aec340a1b24429da7ea885ec239471f1b</anchor>
      <arglist>(const DerivativeProperties &amp;properties)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>_set_DfDp_properties</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1OutArgs.html</anchorfile>
      <anchor>a004d062b0ee14742ffe961aa6931a093</anchor>
      <arglist>(int l, const DerivativeProperties &amp;properties)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>_set_DgDx_dot_properties</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1OutArgs.html</anchorfile>
      <anchor>a0d75ff3b026b08909588b21cfc856ac4</anchor>
      <arglist>(int j, const DerivativeProperties &amp;properties)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>_set_DgDx_properties</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1OutArgs.html</anchorfile>
      <anchor>a4f0f5c5d6d2c5f674725ddcee5680ace</anchor>
      <arglist>(int j, const DerivativeProperties &amp;properties)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>_set_DgDp_properties</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1OutArgs.html</anchorfile>
      <anchor>a82a0f02e39978651161663ef692d2b6d</anchor>
      <arglist>(int j, int l, const DerivativeProperties &amp;properties)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>_setUnsupportsAndRelated</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1OutArgs.html</anchorfile>
      <anchor>afe22c4e6e922447f9605640b696ceaa8</anchor>
      <arglist>(EInArgsMembers arg)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>_setUnsupportsAndRelated</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1OutArgs.html</anchorfile>
      <anchor>a4f1e3b10d43c7585483f341e529d9ad1</anchor>
      <arglist>(EOutArgsMembers arg)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::ModelEvaluatorBase::OutArgsSetup</name>
    <filename>classThyra_1_1ModelEvaluatorBase_1_1OutArgsSetup.html</filename>
    <templarg>Scalar</templarg>
    <base>Thyra::ModelEvaluatorBase::OutArgs</base>
    <member kind="function">
      <type></type>
      <name>OutArgsSetup</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1OutArgsSetup.html</anchorfile>
      <anchor>a50b1e02b2621777ca5f912d52be57eb6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>OutArgsSetup</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1OutArgsSetup.html</anchorfile>
      <anchor>a298d6a8752ac5aa5ea79df8c9ee7afdb</anchor>
      <arglist>(const OutArgs&lt; Scalar &gt; &amp;)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setModelEvalDescription</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1OutArgsSetup.html</anchorfile>
      <anchor>ae4125c76a07b84e8240cb87b5413b3b4</anchor>
      <arglist>(const std::string &amp;modelEvalDescription)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_Np_Ng</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1OutArgsSetup.html</anchorfile>
      <anchor>af43ce2fa4faebfa460bf3032212987b3</anchor>
      <arglist>(int Np, int Ng)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setSupports</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1OutArgsSetup.html</anchorfile>
      <anchor>a0a6da7000c6e677c2a62f20ddf25007c</anchor>
      <arglist>(EOutArgsMembers arg, bool supports=true)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setSupports</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1OutArgsSetup.html</anchorfile>
      <anchor>a2a84d2e572edd35a31961b693ff5674d</anchor>
      <arglist>(EOutArgsDfDp arg, int l, const DerivativeSupport &amp;)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setSupports</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1OutArgsSetup.html</anchorfile>
      <anchor>a9d354431dc69bc24f3ffe0df16bc0576</anchor>
      <arglist>(EOutArgsDgDx_dot arg, int j, const DerivativeSupport &amp;)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setSupports</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1OutArgsSetup.html</anchorfile>
      <anchor>ad7de498f77aff409d8c3cc7eb14a3f77</anchor>
      <arglist>(EOutArgsDgDx arg, int j, const DerivativeSupport &amp;)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setSupports</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1OutArgsSetup.html</anchorfile>
      <anchor>a6e36884d278c7552f94a76a16995c819</anchor>
      <arglist>(EOutArgsDgDp arg, int j, int l, const DerivativeSupport &amp;)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_W_properties</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1OutArgsSetup.html</anchorfile>
      <anchor>a9363c283572c4262a6326829be65b551</anchor>
      <arglist>(const DerivativeProperties &amp;properties)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_DfDp_properties</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1OutArgsSetup.html</anchorfile>
      <anchor>a7d3450116629ea77c24a3f9c42397db1</anchor>
      <arglist>(int l, const DerivativeProperties &amp;properties)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_DgDx_dot_properties</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1OutArgsSetup.html</anchorfile>
      <anchor>a744d95567ed8faae06dcf912f46b868b</anchor>
      <arglist>(int j, const DerivativeProperties &amp;properties)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_DgDx_properties</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1OutArgsSetup.html</anchorfile>
      <anchor>aabf9e3400c62e82ecffeb499ce1d1415</anchor>
      <arglist>(int j, const DerivativeProperties &amp;properties)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_DgDp_properties</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1OutArgsSetup.html</anchorfile>
      <anchor>abb8e0844bd4d0e9b1ffdee3e5b12bc61</anchor>
      <arglist>(int j, int l, const DerivativeProperties &amp;properties)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setSupports</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1OutArgsSetup.html</anchorfile>
      <anchor>af66c61999573e3e55c19e67087ea9897</anchor>
      <arglist>(const OutArgs&lt; Scalar &gt; &amp;inputOutArgs)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setUnsupportsAndRelated</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1OutArgsSetup.html</anchorfile>
      <anchor>ac4f3d4db47730a8e56bb0f4b5f8f9aa7</anchor>
      <arglist>(EInArgsMembers arg)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setUnsupportsAndRelated</name>
      <anchorfile>classThyra_1_1ModelEvaluatorBase_1_1OutArgsSetup.html</anchorfile>
      <anchor>ab66b328a66d346aa718d5f48d714614c</anchor>
      <arglist>(EOutArgsMembers arg)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::ParameterDrivenMultiVectorInput</name>
    <filename>classThyra_1_1ParameterDrivenMultiVectorInput.html</filename>
    <templarg>Scalar</templarg>
    <base>Teuchos::ParameterListAcceptor</base>
    <base>VerboseObject&lt; ParameterDrivenMultiVectorInput&lt; Scalar &gt; &gt;</base>
    <member kind="function">
      <type>RCP&lt; const VectorBase&lt; Scalar &gt; &gt;</type>
      <name>readVectorOverride</name>
      <anchorfile>classThyra_1_1ParameterDrivenMultiVectorInput.html</anchorfile>
      <anchor>a7c14a986680f1d9eee8d7746b9c8639f</anchor>
      <arglist>(const ParameterDrivenMultiVectorInput&lt; Scalar &gt; &amp;pdmvi, const std::string &amp;vName, const RCP&lt; const VectorBase&lt; Scalar &gt; &gt; &amp;defaultVector)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ParameterDrivenMultiVectorInput</name>
      <anchorfile>classThyra_1_1ParameterDrivenMultiVectorInput.html</anchorfile>
      <anchor>a75678673a6f9dab4e6d64ffa36405126</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_CONST_COMPOSITION_MEMBERS</name>
      <anchorfile>classThyra_1_1ParameterDrivenMultiVectorInput.html</anchorfile>
      <anchor>a6ca3ac76a05f97141c01e59483f7a873</anchor>
      <arglist>(VectorSpaceBase&lt; Scalar &gt;, vecSpc)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_COMPOSITION_MEMBERS</name>
      <anchorfile>classThyra_1_1ParameterDrivenMultiVectorInput.html</anchorfile>
      <anchor>a79ff2966ece1d09067337782c3916fdb</anchor>
      <arglist>(MultiVectorFileIOBase&lt; Scalar &gt;, fileIO)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setParameterList</name>
      <anchorfile>classThyra_1_1ParameterDrivenMultiVectorInput.html</anchorfile>
      <anchor>a9bbf0dd82eaae6ba33c79fee64d6da61</anchor>
      <arglist>(Teuchos::RCP&lt; Teuchos::ParameterList &gt; const &amp;paramList)</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; Teuchos::ParameterList &gt;</type>
      <name>getNonconstParameterList</name>
      <anchorfile>classThyra_1_1ParameterDrivenMultiVectorInput.html</anchorfile>
      <anchor>a570915c8c81389a0e8509e9df4190361</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; Teuchos::ParameterList &gt;</type>
      <name>unsetParameterList</name>
      <anchorfile>classThyra_1_1ParameterDrivenMultiVectorInput.html</anchorfile>
      <anchor>ac29a1b0609afd4001e5896b8e4eb97d6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Teuchos::ParameterList &gt;</type>
      <name>getParameterList</name>
      <anchorfile>classThyra_1_1ParameterDrivenMultiVectorInput.html</anchorfile>
      <anchor>a606a4e3defd84ce75626559248432a83</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Teuchos::ParameterList &gt;</type>
      <name>getValidParameters</name>
      <anchorfile>classThyra_1_1ParameterDrivenMultiVectorInput.html</anchorfile>
      <anchor>ae0bdcd7ddfbb54fe2e756e20bf0976cb</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const std::string &amp;</type>
      <name>readinFileNameBase</name>
      <anchorfile>classThyra_1_1ParameterDrivenMultiVectorInput.html</anchorfile>
      <anchor>a8d03a4caefae1f4e56b630bbef107f1a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Teuchos::Array&lt; Scalar &gt; &amp;</type>
      <name>readinExplicitArray</name>
      <anchorfile>classThyra_1_1ParameterDrivenMultiVectorInput.html</anchorfile>
      <anchor>a8397bea9bf2a71b292c51214d3607a9a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Scalar</type>
      <name>readinScaleBy</name>
      <anchorfile>classThyra_1_1ParameterDrivenMultiVectorInput.html</anchorfile>
      <anchor>a643bc5cfd5faad8a0cb5e96036eccaa1</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>readMultiVector</name>
      <anchorfile>classThyra_1_1ParameterDrivenMultiVectorInput.html</anchorfile>
      <anchor>a0b99c87ab1c7c8ad4767e33fd9685da3</anchor>
      <arglist>(const std::string &amp;mvName, Thyra::MultiVectorBase&lt; Scalar &gt; *mv) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>readVector</name>
      <anchorfile>classThyra_1_1ParameterDrivenMultiVectorInput.html</anchorfile>
      <anchor>a01737c1a0c8964284547e1d2bb26bc12</anchor>
      <arglist>(const std::string &amp;vName, Teuchos::RCP&lt; Thyra::VectorBase&lt; Scalar &gt; &gt; *v) const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; Thyra::VectorBase&lt; Scalar &gt; &gt;</type>
      <name>readVector</name>
      <anchorfile>classThyra_1_1ParameterDrivenMultiVectorInput.html</anchorfile>
      <anchor>a6cf4193717f46e16ce12360ed38f4cf5</anchor>
      <arglist>(const std::string &amp;vName) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::PhysicallyBlockedLinearOpBase</name>
    <filename>classThyra_1_1PhysicallyBlockedLinearOpBase.html</filename>
    <templarg>Scalar</templarg>
    <base virtualness="virtual">Thyra::BlockedLinearOpBase</base>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>beginBlockFill</name>
      <anchorfile>classThyra_1_1PhysicallyBlockedLinearOpBase.html</anchorfile>
      <anchor>a5d3e54492310b41e6faeb5dbb9c78198</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>beginBlockFill</name>
      <anchorfile>classThyra_1_1PhysicallyBlockedLinearOpBase.html</anchorfile>
      <anchor>a50da8be8612452e6b095c86d59a64f4c</anchor>
      <arglist>(const int numRowBlocks, const int numColBlocks)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>beginBlockFill</name>
      <anchorfile>classThyra_1_1PhysicallyBlockedLinearOpBase.html</anchorfile>
      <anchor>ab0687e997e0732b80d7919a312bf4ea8</anchor>
      <arglist>(const Teuchos::RCP&lt; const ProductVectorSpaceBase&lt; Scalar &gt; &gt; &amp;productRange, const Teuchos::RCP&lt; const ProductVectorSpaceBase&lt; Scalar &gt; &gt; &amp;productDomain)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>blockFillIsActive</name>
      <anchorfile>classThyra_1_1PhysicallyBlockedLinearOpBase.html</anchorfile>
      <anchor>a469365b823ad87d3f59a788234e81899</anchor>
      <arglist>() const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>acceptsBlock</name>
      <anchorfile>classThyra_1_1PhysicallyBlockedLinearOpBase.html</anchorfile>
      <anchor>a2e34706e919ffdfc7e8a9205253e4655</anchor>
      <arglist>(const int i, const int j) const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>setNonconstBlock</name>
      <anchorfile>classThyra_1_1PhysicallyBlockedLinearOpBase.html</anchorfile>
      <anchor>a7db7164aa4c5a75db5fdbe0217bd9002</anchor>
      <arglist>(const int i, const int j, const Teuchos::RCP&lt; LinearOpBase&lt; Scalar &gt; &gt; &amp;block)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>setBlock</name>
      <anchorfile>classThyra_1_1PhysicallyBlockedLinearOpBase.html</anchorfile>
      <anchor>a9c083f83265f1bf7cbdd7d71f11f4013</anchor>
      <arglist>(const int i, const int j, const Teuchos::RCP&lt; const LinearOpBase&lt; Scalar &gt; &gt; &amp;block)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>endBlockFill</name>
      <anchorfile>classThyra_1_1PhysicallyBlockedLinearOpBase.html</anchorfile>
      <anchor>aaa9058847589158ba02d17c65e33a456</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>uninitialize</name>
      <anchorfile>classThyra_1_1PhysicallyBlockedLinearOpBase.html</anchorfile>
      <anchor>a3e7f1220d3a95739b9f7f6752121889d</anchor>
      <arglist>()=0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::PhysicallyBlockedLinearOpWithSolveBase</name>
    <filename>classThyra_1_1PhysicallyBlockedLinearOpWithSolveBase.html</filename>
    <templarg>Scalar</templarg>
    <base virtualness="virtual">Thyra::BlockedLinearOpWithSolveBase</base>
    <base virtualness="virtual">Thyra::PhysicallyBlockedLinearOpBase</base>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>acceptsLOWSBlock</name>
      <anchorfile>classThyra_1_1PhysicallyBlockedLinearOpWithSolveBase.html</anchorfile>
      <anchor>ac850f9ae12ebcff69834d6cae1c7814e</anchor>
      <arglist>(const int i, const int j) const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>setNonconstLOWSBlock</name>
      <anchorfile>classThyra_1_1PhysicallyBlockedLinearOpWithSolveBase.html</anchorfile>
      <anchor>a26c3d130110fde65e815785f3f9000f8</anchor>
      <arglist>(const int i, const int j, const Teuchos::RCP&lt; LinearOpWithSolveBase&lt; Scalar &gt; &gt; &amp;block)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>setLOWSBlock</name>
      <anchorfile>classThyra_1_1PhysicallyBlockedLinearOpWithSolveBase.html</anchorfile>
      <anchor>a6b181ddd3664c72194a46b2504946517</anchor>
      <arglist>(const int i, const int j, const Teuchos::RCP&lt; const LinearOpWithSolveBase&lt; Scalar &gt; &gt; &amp;block)=0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Teuchos::PolynomialTraits&lt; Thyra::VectorBase&lt; Scalar &gt; &gt;</name>
    <filename>classTeuchos_1_1PolynomialTraits_3_01Thyra_1_1VectorBase_3_01Scalar_01_4_01_4.html</filename>
    <templarg></templarg>
    <member kind="typedef">
      <type>Thyra::VectorBase&lt; Scalar &gt;</type>
      <name>coeff_type</name>
      <anchorfile>classTeuchos_1_1PolynomialTraits_3_01Thyra_1_1VectorBase_3_01Scalar_01_4_01_4.html</anchorfile>
      <anchor>a4a694a02ed4c1fb3cc47db4e6efc77e1</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Scalar</type>
      <name>scalar_type</name>
      <anchorfile>classTeuchos_1_1PolynomialTraits_3_01Thyra_1_1VectorBase_3_01Scalar_01_4_01_4.html</anchorfile>
      <anchor>a94690f56034d573df2d77a9885a06e9d</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" static="yes">
      <type>static Teuchos::RCP&lt; coeff_type &gt;</type>
      <name>clone</name>
      <anchorfile>classTeuchos_1_1PolynomialTraits_3_01Thyra_1_1VectorBase_3_01Scalar_01_4_01_4.html</anchorfile>
      <anchor>ac295c7dba0edb3f79344ceba56b7b0f7</anchor>
      <arglist>(const coeff_type &amp;c)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>copy</name>
      <anchorfile>classTeuchos_1_1PolynomialTraits_3_01Thyra_1_1VectorBase_3_01Scalar_01_4_01_4.html</anchorfile>
      <anchor>a05dfd18787031726d5ce766207964b9b</anchor>
      <arglist>(const coeff_type &amp;x, coeff_type *y)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>assign</name>
      <anchorfile>classTeuchos_1_1PolynomialTraits_3_01Thyra_1_1VectorBase_3_01Scalar_01_4_01_4.html</anchorfile>
      <anchor>aedcdc0ec7418287c970d1e093fadf215</anchor>
      <arglist>(coeff_type *y, const scalar_type &amp;alpha)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>update</name>
      <anchorfile>classTeuchos_1_1PolynomialTraits_3_01Thyra_1_1VectorBase_3_01Scalar_01_4_01_4.html</anchorfile>
      <anchor>ab16d758cfd0420750581a817777d14b1</anchor>
      <arglist>(coeff_type *y, const coeff_type &amp;x, const scalar_type &amp;beta)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::PreconditionerBase</name>
    <filename>classThyra_1_1PreconditionerBase.html</filename>
    <templarg></templarg>
    <base virtualness="virtual">Teuchos::Describable</base>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>isLeftPrecOpConst</name>
      <anchorfile>classThyra_1_1PreconditionerBase.html</anchorfile>
      <anchor>ac36c0603fc68831c0999ba86b38d2eca</anchor>
      <arglist>() const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual Teuchos::RCP&lt; LinearOpBase&lt; Scalar &gt; &gt;</type>
      <name>getNonconstLeftPrecOp</name>
      <anchorfile>classThyra_1_1PreconditionerBase.html</anchorfile>
      <anchor>ab2b296e80ac4f16b4023a1872452f839</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual Teuchos::RCP&lt; const LinearOpBase&lt; Scalar &gt; &gt;</type>
      <name>getLeftPrecOp</name>
      <anchorfile>classThyra_1_1PreconditionerBase.html</anchorfile>
      <anchor>a3e6340dbbac8cdfd8286c9a2b6c9789a</anchor>
      <arglist>() const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>isRightPrecOpConst</name>
      <anchorfile>classThyra_1_1PreconditionerBase.html</anchorfile>
      <anchor>ac8704c17f1a3a67b51dc125f7b0d91ff</anchor>
      <arglist>() const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual Teuchos::RCP&lt; LinearOpBase&lt; Scalar &gt; &gt;</type>
      <name>getNonconstRightPrecOp</name>
      <anchorfile>classThyra_1_1PreconditionerBase.html</anchorfile>
      <anchor>ac21c2c70bbc003efd183fc61167af7b6</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual Teuchos::RCP&lt; const LinearOpBase&lt; Scalar &gt; &gt;</type>
      <name>getRightPrecOp</name>
      <anchorfile>classThyra_1_1PreconditionerBase.html</anchorfile>
      <anchor>a59381e8d2360b074246907dd703140a1</anchor>
      <arglist>() const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>isUnspecifiedPrecOpConst</name>
      <anchorfile>classThyra_1_1PreconditionerBase.html</anchorfile>
      <anchor>a8783c6ec193f9809deb9da9287981ece</anchor>
      <arglist>() const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual Teuchos::RCP&lt; LinearOpBase&lt; Scalar &gt; &gt;</type>
      <name>getNonconstUnspecifiedPrecOp</name>
      <anchorfile>classThyra_1_1PreconditionerBase.html</anchorfile>
      <anchor>a6e6ac3a39e97cb252fd1ca5c9c0ad910</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual Teuchos::RCP&lt; const LinearOpBase&lt; Scalar &gt; &gt;</type>
      <name>getUnspecifiedPrecOp</name>
      <anchorfile>classThyra_1_1PreconditionerBase.html</anchorfile>
      <anchor>aac4b8530b6c675a2bf8cb094d6b8559a</anchor>
      <arglist>() const  =0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::PreconditionerFactoryBase</name>
    <filename>classThyra_1_1PreconditionerFactoryBase.html</filename>
    <templarg>Scalar</templarg>
    <base virtualness="virtual">Teuchos::Describable</base>
    <base virtualness="virtual">Teuchos::ParameterListAcceptor</base>
    <base virtualness="virtual">VerboseObject&lt; PreconditionerFactoryBase&lt; Scalar &gt; &gt;</base>
    <member kind="function">
      <type>void</type>
      <name>initializePrec</name>
      <anchorfile>classThyra_1_1PreconditionerFactoryBase.html</anchorfile>
      <anchor>a97e6203adfbb81da6ac47b32748d5ec8</anchor>
      <arglist>(const PreconditionerFactoryBase&lt; Scalar &gt; &amp;precFactory, const Teuchos::RCP&lt; const LinearOpBase&lt; Scalar &gt; &gt; &amp;fwdOp, const Teuchos::Ptr&lt; PreconditionerBase&lt; Scalar &gt; &gt; &amp;prec, const ESupportSolveUse supportSolveUse=SUPPORT_SOLVE_UNSPECIFIED)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>uninitializePrec</name>
      <anchorfile>classThyra_1_1PreconditionerFactoryBase.html</anchorfile>
      <anchor>a56e0e1d5c5ef175afa3d893485faa195</anchor>
      <arglist>(const PreconditionerFactoryBase&lt; Scalar &gt; &amp;precFactory, const Teuchos::Ptr&lt; PreconditionerBase&lt; Scalar &gt; &gt; &amp;prec, const Teuchos::Ptr&lt; Teuchos::RCP&lt; const LinearOpBase&lt; Scalar &gt; &gt; &gt; &amp;fwdOp=Teuchos::null, const Teuchos::Ptr&lt; ESupportSolveUse &gt; &amp;supportSolveUse=Teuchos::null)</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; PreconditionerBase&lt; Scalar &gt; &gt;</type>
      <name>prec</name>
      <anchorfile>classThyra_1_1PreconditionerFactoryBase.html</anchorfile>
      <anchor>a5a7633fc1c1164ff6828e397d1f8f73d</anchor>
      <arglist>(const PreconditionerFactoryBase&lt; Scalar &gt; &amp;precFactory, const Teuchos::RCP&lt; const LinearOpBase&lt; Scalar &gt; &gt; &amp;fwdOp, const ESupportSolveUse supportSolveUse=SUPPORT_SOLVE_UNSPECIFIED)</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>isCompatible</name>
      <anchorfile>classThyra_1_1PreconditionerFactoryBase.html</anchorfile>
      <anchor>ad938e6fadc2c8545f5751159886ec224</anchor>
      <arglist>(const LinearOpSourceBase&lt; Scalar &gt; &amp;fwdOpSrc) const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual RCP&lt; PreconditionerBase&lt; Scalar &gt; &gt;</type>
      <name>createPrec</name>
      <anchorfile>classThyra_1_1PreconditionerFactoryBase.html</anchorfile>
      <anchor>a356b85f9d364b9df1d449d8c2bb41350</anchor>
      <arglist>() const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>initializePrec</name>
      <anchorfile>classThyra_1_1PreconditionerFactoryBase.html</anchorfile>
      <anchor>a4787cf11327ecf493a5577b600d635be</anchor>
      <arglist>(const RCP&lt; const LinearOpSourceBase&lt; Scalar &gt; &gt; &amp;fwdOpSrc, PreconditionerBase&lt; Scalar &gt; *precOp, const ESupportSolveUse supportSolveUse=SUPPORT_SOLVE_UNSPECIFIED) const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>uninitializePrec</name>
      <anchorfile>classThyra_1_1PreconditionerFactoryBase.html</anchorfile>
      <anchor>ada490ba73a668a0eee41c13fca400f93</anchor>
      <arglist>(PreconditionerBase&lt; Scalar &gt; *prec, RCP&lt; const LinearOpSourceBase&lt; Scalar &gt; &gt; *fwdOpSrc=NULL, ESupportSolveUse *supportSolveUse=NULL) const  =0</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>applySupportsConj</name>
      <anchorfile>classThyra_1_1PreconditionerFactoryBase.html</anchorfile>
      <anchor>a4672cb1cc7aaf6d511d82a0a60777866</anchor>
      <arglist>(EConj conj) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>applyTransposeSupportsConj</name>
      <anchorfile>classThyra_1_1PreconditionerFactoryBase.html</anchorfile>
      <anchor>acb0746f26f7ccec6b34612707c516f29</anchor>
      <arglist>(EConj conj) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::ProductMultiVectorBase</name>
    <filename>classThyra_1_1ProductMultiVectorBase.html</filename>
    <templarg>Scalar</templarg>
    <base virtualness="virtual">Thyra::MultiVectorBase</base>
    <member kind="function" virtualness="pure">
      <type>virtual Teuchos::RCP&lt; const ProductVectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>productSpace</name>
      <anchorfile>classThyra_1_1ProductMultiVectorBase.html</anchorfile>
      <anchor>a6cca75f3efc5978d2fbc3b248c4c8289</anchor>
      <arglist>() const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>blockIsConst</name>
      <anchorfile>classThyra_1_1ProductMultiVectorBase.html</anchorfile>
      <anchor>a7896a3a4870e4f15b80eb2e6a79b24e9</anchor>
      <arglist>(const int k) const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual Teuchos::RCP&lt; MultiVectorBase&lt; Scalar &gt; &gt;</type>
      <name>getNonconstMultiVectorBlock</name>
      <anchorfile>classThyra_1_1ProductMultiVectorBase.html</anchorfile>
      <anchor>a69f241b523fafb590f6107d268d4953d</anchor>
      <arglist>(const int k)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual Teuchos::RCP&lt; const MultiVectorBase&lt; Scalar &gt; &gt;</type>
      <name>getMultiVectorBlock</name>
      <anchorfile>classThyra_1_1ProductMultiVectorBase.html</anchorfile>
      <anchor>ac6e2d71bf03459667c3138232888d2a6</anchor>
      <arglist>(const int k) const  =0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::ProductVectorBase</name>
    <filename>classThyra_1_1ProductVectorBase.html</filename>
    <templarg>Scalar</templarg>
    <base virtualness="virtual">Thyra::VectorBase</base>
    <base virtualness="virtual">Thyra::ProductMultiVectorBase</base>
    <member kind="function" virtualness="pure">
      <type>virtual RCP&lt; VectorBase&lt; Scalar &gt; &gt;</type>
      <name>getNonconstVectorBlock</name>
      <anchorfile>classThyra_1_1ProductVectorBase.html</anchorfile>
      <anchor>a803fb43934bfcef4ea477857d7ff132a</anchor>
      <arglist>(const int k)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual RCP&lt; const VectorBase&lt; Scalar &gt; &gt;</type>
      <name>getVectorBlock</name>
      <anchorfile>classThyra_1_1ProductVectorBase.html</anchorfile>
      <anchor>a328d60fb2b179178309ff549f9b19502</anchor>
      <arglist>(const int k) const  =0</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; Thyra::ProductVectorBase&lt; Scalar &gt; &gt;</type>
      <name>nonconstProductVectorBase</name>
      <anchorfile>classThyra_1_1ProductVectorBase.html</anchorfile>
      <anchor>a43222558abbc8c13ecf3747ce8eb1bca</anchor>
      <arglist>(const RCP&lt; Thyra::VectorBase&lt; Scalar &gt; &gt; &amp;v)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const Thyra::ProductVectorBase&lt; Scalar &gt; &gt;</type>
      <name>productVectorBase</name>
      <anchorfile>classThyra_1_1ProductVectorBase.html</anchorfile>
      <anchor>a33d77fb8d065d7e180ec0170894c41eb</anchor>
      <arglist>(const RCP&lt; const Thyra::VectorBase&lt; Scalar &gt; &gt; &amp;v)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::ProductVectorSpaceBase</name>
    <filename>classThyra_1_1ProductVectorSpaceBase.html</filename>
    <templarg></templarg>
    <base virtualness="virtual">Thyra::VectorSpaceBase</base>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>numBlocks</name>
      <anchorfile>classThyra_1_1ProductVectorSpaceBase.html</anchorfile>
      <anchor>a1c944d05b406395dca86d6c4ed1241d1</anchor>
      <arglist>() const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual Teuchos::RCP&lt; const VectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>getBlock</name>
      <anchorfile>classThyra_1_1ProductVectorSpaceBase.html</anchorfile>
      <anchor>a10b4f01d8036d48ae52f3d3588d41630</anchor>
      <arglist>(const int k) const  =0</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; ProductVectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>nonconstProductVectorSpaceBase</name>
      <anchorfile>classThyra_1_1ProductVectorSpaceBase.html</anchorfile>
      <anchor>aa5bbbd016b5c8007d2736e834eb31a7c</anchor>
      <arglist>(const RCP&lt; VectorSpaceBase&lt; Scalar &gt; &gt; &amp;v, const bool forceSuccess=true)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const ProductVectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>productVectorSpaceBase</name>
      <anchorfile>classThyra_1_1ProductVectorSpaceBase.html</anchorfile>
      <anchor>a16922e1072530e4c76a8ac4f3f09e940</anchor>
      <arglist>(const RCP&lt; const VectorSpaceBase&lt; Scalar &gt; &gt; &amp;v, const bool forceSuccess=true)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; ProductVectorSpaceBase&lt; double &gt; &gt;</type>
      <name>nonconstProductVectorSpaceBase</name>
      <anchorfile>classThyra_1_1ProductVectorSpaceBase.html</anchorfile>
      <anchor>a24541d85d913890e1b965f702a07b0fe</anchor>
      <arglist>(const RCP&lt; VectorSpaceBase&lt; double &gt; &gt; &amp;vs, const bool forceSuccess=true)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const ProductVectorSpaceBase&lt; double &gt; &gt;</type>
      <name>productVectorSpaceBase</name>
      <anchorfile>classThyra_1_1ProductVectorSpaceBase.html</anchorfile>
      <anchor>ab9d754094f7f709bac4887773bb1f404</anchor>
      <arglist>(const RCP&lt; const VectorSpaceBase&lt; double &gt; &gt; &amp;vs, const bool forceSuccess=true)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::ReductionFunctional</name>
    <filename>classThyra_1_1ReductionFunctional.html</filename>
    <templarg></templarg>
    <base>Teuchos::Describable</base>
    <member kind="function">
      <type>ScalarTraits&lt; Scalar &gt;::magnitudeType</type>
      <name>reduce</name>
      <anchorfile>classThyra_1_1ReductionFunctional.html</anchorfile>
      <anchor>affa2c7953bb4e3488ed462992825465c</anchor>
      <arglist>(const VectorBase&lt; Scalar &gt; &amp;v) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isCompatible</name>
      <anchorfile>classThyra_1_1ReductionFunctional.html</anchorfile>
      <anchor>a16522c0d2d5ec3deb6ac9dc5839370ee</anchor>
      <arglist>(const VectorBase&lt; Scalar &gt; &amp;v) const </arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual ScalarTraits&lt; Scalar &gt;::magnitudeType</type>
      <name>reduceImpl</name>
      <anchorfile>classThyra_1_1ReductionFunctional.html</anchorfile>
      <anchor>a9bef66541aad555cd8a9a7c100f9ee8d</anchor>
      <arglist>(const VectorBase&lt; Scalar &gt; &amp;v) const  =0</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual bool</type>
      <name>isCompatibleImpl</name>
      <anchorfile>classThyra_1_1ReductionFunctional.html</anchorfile>
      <anchor>a03aa717c00457bbf181302f4cf2fbb00</anchor>
      <arglist>(const VectorBase&lt; Scalar &gt; &amp;v) const  =0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::ResponseOnlyModelEvaluatorBase</name>
    <filename>classThyra_1_1ResponseOnlyModelEvaluatorBase.html</filename>
    <templarg></templarg>
    <base virtualness="virtual">Thyra::ModelEvaluatorDefaultBase</base>
    <member kind="function">
      <type>RCP&lt; const VectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>get_x_space</name>
      <anchorfile>classThyra_1_1ResponseOnlyModelEvaluatorBase.html</anchorfile>
      <anchor>a1ddf0cd15ee6db1de8bfda4dda624edc</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const Teuchos::Array&lt; std::string &gt; &gt;</type>
      <name>get_p_names</name>
      <anchorfile>classThyra_1_1ResponseOnlyModelEvaluatorBase.html</anchorfile>
      <anchor>a298594ad040749d25db9fd8c58008f6e</anchor>
      <arglist>(int l) const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::ArrayView&lt; const std::string &gt;</type>
      <name>get_g_names</name>
      <anchorfile>classThyra_1_1ResponseOnlyModelEvaluatorBase.html</anchorfile>
      <anchor>ae987f230a57dfde91c5eed0885914de7</anchor>
      <arglist>(int j) const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const VectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>get_f_space</name>
      <anchorfile>classThyra_1_1ResponseOnlyModelEvaluatorBase.html</anchorfile>
      <anchor>a5079b6cb9592da039656cc571d3fd726</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>ModelEvaluatorBase::InArgs&lt; Scalar &gt;</type>
      <name>getNominalValues</name>
      <anchorfile>classThyra_1_1ResponseOnlyModelEvaluatorBase.html</anchorfile>
      <anchor>a46a904f4186328dc7e78ed93b7c56c79</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>ModelEvaluatorBase::InArgs&lt; Scalar &gt;</type>
      <name>getLowerBounds</name>
      <anchorfile>classThyra_1_1ResponseOnlyModelEvaluatorBase.html</anchorfile>
      <anchor>a19afd98682792c4eab706b40da91fb5e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>ModelEvaluatorBase::InArgs&lt; Scalar &gt;</type>
      <name>getUpperBounds</name>
      <anchorfile>classThyra_1_1ResponseOnlyModelEvaluatorBase.html</anchorfile>
      <anchor>ad4f324aebc9c1329914c342131f57ff7</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; LinearOpWithSolveBase&lt; Scalar &gt; &gt;</type>
      <name>create_W</name>
      <anchorfile>classThyra_1_1ResponseOnlyModelEvaluatorBase.html</anchorfile>
      <anchor>a8fc4de6cbe84fe1c82ceeb3b39aa6c56</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; LinearOpBase&lt; Scalar &gt; &gt;</type>
      <name>create_W_op</name>
      <anchorfile>classThyra_1_1ResponseOnlyModelEvaluatorBase.html</anchorfile>
      <anchor>aa2007b8d6d86eb4ce86f6fc5a43ff6e5</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; PreconditionerBase&lt; Scalar &gt; &gt;</type>
      <name>create_W_prec</name>
      <anchorfile>classThyra_1_1ResponseOnlyModelEvaluatorBase.html</anchorfile>
      <anchor>ac5856b9081429c10d4ed922b5e8af63f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const LinearOpWithSolveFactoryBase&lt; Scalar &gt; &gt;</type>
      <name>get_W_factory</name>
      <anchorfile>classThyra_1_1ResponseOnlyModelEvaluatorBase.html</anchorfile>
      <anchor>a127464fde5be218fc43042eb42a4f993</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>reportFinalPoint</name>
      <anchorfile>classThyra_1_1ResponseOnlyModelEvaluatorBase.html</anchorfile>
      <anchor>a3f8e74fa856ab35e1e14c12540f2aff3</anchor>
      <arglist>(const ModelEvaluatorBase::InArgs&lt; Scalar &gt; &amp;finalPoint, const bool wasSolved)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::RowStatLinearOpBase</name>
    <filename>classThyra_1_1RowStatLinearOpBase.html</filename>
    <templarg>Scalar</templarg>
    <base virtualness="virtual">Thyra::LinearOpBase</base>
    <member kind="function">
      <type>bool</type>
      <name>rowStatIsSupported</name>
      <anchorfile>classThyra_1_1RowStatLinearOpBase.html</anchorfile>
      <anchor>a883dadcf63e50da3f3f7a0cdbef95e06</anchor>
      <arglist>(const RowStatLinearOpBaseUtils::ERowStat rowStat) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>getRowStat</name>
      <anchorfile>classThyra_1_1RowStatLinearOpBase.html</anchorfile>
      <anchor>a4d3a0e35beb6720f776c2537fb022fef</anchor>
      <arglist>(const RowStatLinearOpBaseUtils::ERowStat rowStat, const Ptr&lt; VectorBase&lt; Scalar &gt; &gt; &amp;rowStatVec) const </arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual bool</type>
      <name>rowStatIsSupportedImpl</name>
      <anchorfile>classThyra_1_1RowStatLinearOpBase.html</anchorfile>
      <anchor>a546bc2b3059307ce3b65a08925c2a159</anchor>
      <arglist>(const RowStatLinearOpBaseUtils::ERowStat rowStat) const  =0</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual void</type>
      <name>getRowStatImpl</name>
      <anchorfile>classThyra_1_1RowStatLinearOpBase.html</anchorfile>
      <anchor>a3ac1306a0e7d55cc5b33cbc9305e1a45</anchor>
      <arglist>(const RowStatLinearOpBaseUtils::ERowStat rowStat, const Ptr&lt; VectorBase&lt; Scalar &gt; &gt; &amp;rowStatVec) const  =0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>RowStatLinearOpBase&lt; double &gt;</name>
    <filename>classThyra_1_1RowStatLinearOpBase.html</filename>
    <base virtualness="virtual">LinearOpBase&lt; double &gt;</base>
    <member kind="function">
      <type>bool</type>
      <name>rowStatIsSupported</name>
      <anchorfile>classThyra_1_1RowStatLinearOpBase.html</anchorfile>
      <anchor>a883dadcf63e50da3f3f7a0cdbef95e06</anchor>
      <arglist>(const RowStatLinearOpBaseUtils::ERowStat rowStat) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>getRowStat</name>
      <anchorfile>classThyra_1_1RowStatLinearOpBase.html</anchorfile>
      <anchor>a4d3a0e35beb6720f776c2537fb022fef</anchor>
      <arglist>(const RowStatLinearOpBaseUtils::ERowStat rowStat, const Ptr&lt; VectorBase&lt; double &gt; &gt; &amp;rowStatVec) const</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual bool</type>
      <name>rowStatIsSupportedImpl</name>
      <anchorfile>classThyra_1_1RowStatLinearOpBase.html</anchorfile>
      <anchor>a546bc2b3059307ce3b65a08925c2a159</anchor>
      <arglist>(const RowStatLinearOpBaseUtils::ERowStat rowStat) const  =0</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual void</type>
      <name>getRowStatImpl</name>
      <anchorfile>classThyra_1_1RowStatLinearOpBase.html</anchorfile>
      <anchor>a3ac1306a0e7d55cc5b33cbc9305e1a45</anchor>
      <arglist>(const RowStatLinearOpBaseUtils::ERowStat rowStat, const Ptr&lt; VectorBase&lt; double &gt; &gt; &amp;rowStatVec) const  =0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::ScalarProdBase</name>
    <filename>classThyra_1_1ScalarProdBase.html</filename>
    <templarg></templarg>
    <base virtualness="virtual">Teuchos::Describable</base>
    <member kind="function">
      <type>bool</type>
      <name>isEuclidean</name>
      <anchorfile>classThyra_1_1ScalarProdBase.html</anchorfile>
      <anchor>ae05fc86059a49b4da654e4e1956ff300</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Scalar</type>
      <name>scalarProd</name>
      <anchorfile>classThyra_1_1ScalarProdBase.html</anchorfile>
      <anchor>a27527875e6127b27a02d1aa4c8491030</anchor>
      <arglist>(const VectorBase&lt; Scalar &gt; &amp;x, const VectorBase&lt; Scalar &gt; &amp;y) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>scalarProds</name>
      <anchorfile>classThyra_1_1ScalarProdBase.html</anchorfile>
      <anchor>ac48c1f6c43ea0d94aa56cc832f5407a6</anchor>
      <arglist>(const MultiVectorBase&lt; Scalar &gt; &amp;X, const MultiVectorBase&lt; Scalar &gt; &amp;Y, const ArrayView&lt; Scalar &gt; &amp;scalarProds_out) const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const LinearOpBase&lt; Scalar &gt; &gt;</type>
      <name>getLinearOp</name>
      <anchorfile>classThyra_1_1ScalarProdBase.html</anchorfile>
      <anchor>a2569bafdfdee1a94154c5429fa441dc4</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual bool</type>
      <name>isEuclideanImpl</name>
      <anchorfile>classThyra_1_1ScalarProdBase.html</anchorfile>
      <anchor>ad18722a1d3de22cf6683ad9a9c6e9de7</anchor>
      <arglist>() const  =0</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual Scalar</type>
      <name>scalarProdImpl</name>
      <anchorfile>classThyra_1_1ScalarProdBase.html</anchorfile>
      <anchor>adaa85d88c071d960eed606df194c703e</anchor>
      <arglist>(const VectorBase&lt; Scalar &gt; &amp;x, const VectorBase&lt; Scalar &gt; &amp;y) const </arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual void</type>
      <name>scalarProdsImpl</name>
      <anchorfile>classThyra_1_1ScalarProdBase.html</anchorfile>
      <anchor>a50a7a189567c8eb38c2d1bf4da06ff57</anchor>
      <arglist>(const MultiVectorBase&lt; Scalar &gt; &amp;X, const MultiVectorBase&lt; Scalar &gt; &amp;Y, const ArrayView&lt; Scalar &gt; &amp;scalarProds_out) const  =0</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual RCP&lt; const LinearOpBase&lt; Scalar &gt; &gt;</type>
      <name>getLinearOpImpl</name>
      <anchorfile>classThyra_1_1ScalarProdBase.html</anchorfile>
      <anchor>abe728994a373ac2ecd53f8e8d75361de</anchor>
      <arglist>() const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::ScalarProdVectorSpaceBase</name>
    <filename>classThyra_1_1ScalarProdVectorSpaceBase.html</filename>
    <templarg></templarg>
    <base virtualness="virtual">Thyra::VectorSpaceDefaultBase</base>
    <member kind="function">
      <type>RCP&lt; const ScalarProdVectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>createSmallScalarProdVectorSpaceBase</name>
      <anchorfile>classThyra_1_1ScalarProdVectorSpaceBase.html</anchorfile>
      <anchor>a24a22856754084f4d6fbf37ebf6bf8e0</anchor>
      <arglist>(const RCP&lt; const VectorSpaceBase&lt; Scalar &gt; &gt; &amp;vs, const Ordinal dim)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ScalarProdVectorSpaceBase</name>
      <anchorfile>classThyra_1_1ScalarProdVectorSpaceBase.html</anchorfile>
      <anchor>a5c743959e98463ed4146321f72ee56ff</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ScalarProdVectorSpaceBase</name>
      <anchorfile>classThyra_1_1ScalarProdVectorSpaceBase.html</anchorfile>
      <anchor>ab44115cb02cd8b952c65e3ba3457146c</anchor>
      <arglist>(const RCP&lt; const ScalarProdBase&lt; Scalar &gt; &gt; &amp;scalarProd)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>setScalarProd</name>
      <anchorfile>classThyra_1_1ScalarProdVectorSpaceBase.html</anchorfile>
      <anchor>ad2755ba6fafab53803987edbe657b40e</anchor>
      <arglist>(const RCP&lt; const ScalarProdBase&lt; Scalar &gt; &gt; &amp;scalarProd)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const ScalarProdBase&lt; Scalar &gt; &gt;</type>
      <name>getScalarProd</name>
      <anchorfile>classThyra_1_1ScalarProdVectorSpaceBase.html</anchorfile>
      <anchor>a971a4911ac2d5051379df23da8814acc</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isEuclidean</name>
      <anchorfile>classThyra_1_1ScalarProdVectorSpaceBase.html</anchorfile>
      <anchor>a698bea10573c2de61c186a16da55bc8f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Scalar</type>
      <name>scalarProd</name>
      <anchorfile>classThyra_1_1ScalarProdVectorSpaceBase.html</anchorfile>
      <anchor>ac9b801c63899f927a1566e4539807ba5</anchor>
      <arglist>(const VectorBase&lt; Scalar &gt; &amp;x, const VectorBase&lt; Scalar &gt; &amp;y) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>scalarProdsImpl</name>
      <anchorfile>classThyra_1_1ScalarProdVectorSpaceBase.html</anchorfile>
      <anchor>a33022c875dfb3aeceac06ece1a47411e</anchor>
      <arglist>(const MultiVectorBase&lt; Scalar &gt; &amp;X, const MultiVectorBase&lt; Scalar &gt; &amp;Y, const ArrayView&lt; Scalar &gt; &amp;scalarProds_out) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::ScaledAdjointLinearOpBase</name>
    <filename>classThyra_1_1ScaledAdjointLinearOpBase.html</filename>
    <templarg>Scalar</templarg>
    <base virtualness="virtual">Thyra::LinearOpBase</base>
    <member kind="function" virtualness="pure">
      <type>virtual Scalar</type>
      <name>overallScalar</name>
      <anchorfile>classThyra_1_1ScaledAdjointLinearOpBase.html</anchorfile>
      <anchor>a7dfb65085409ecbcbc355c4da522bb92</anchor>
      <arglist>() const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual EOpTransp</type>
      <name>overallTransp</name>
      <anchorfile>classThyra_1_1ScaledAdjointLinearOpBase.html</anchorfile>
      <anchor>af39eaf1d981b80cf579f28e714d7b721</anchor>
      <arglist>() const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual RCP&lt; LinearOpBase&lt; Scalar &gt; &gt;</type>
      <name>getNonconstOrigOp</name>
      <anchorfile>classThyra_1_1ScaledAdjointLinearOpBase.html</anchorfile>
      <anchor>ad26f51ef0e845557b2edab27c80d30dd</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual RCP&lt; const LinearOpBase&lt; Scalar &gt; &gt;</type>
      <name>getOrigOp</name>
      <anchorfile>classThyra_1_1ScaledAdjointLinearOpBase.html</anchorfile>
      <anchor>a2c1f7dfc90e731cd57496c22e3ae382c</anchor>
      <arglist>() const  =0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::ScaledLinearOpBase</name>
    <filename>classThyra_1_1ScaledLinearOpBase.html</filename>
    <templarg>Scalar</templarg>
    <base virtualness="virtual">Thyra::LinearOpBase</base>
    <member kind="function">
      <type>bool</type>
      <name>supportsScaleLeft</name>
      <anchorfile>classThyra_1_1ScaledLinearOpBase.html</anchorfile>
      <anchor>ae6be35152312907551f0db1b48eea67e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>supportsScaleRight</name>
      <anchorfile>classThyra_1_1ScaledLinearOpBase.html</anchorfile>
      <anchor>ac33ab8ac99fb6fbe351955af493dd1d2</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>scaleLeft</name>
      <anchorfile>classThyra_1_1ScaledLinearOpBase.html</anchorfile>
      <anchor>a305ccf775cf8db8d9c9ec285c3ab828d</anchor>
      <arglist>(const VectorBase&lt; Scalar &gt; &amp;row_scaling)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>scaleRight</name>
      <anchorfile>classThyra_1_1ScaledLinearOpBase.html</anchorfile>
      <anchor>af71e8ca359d0939328d2bea4a1ccc7d6</anchor>
      <arglist>(const VectorBase&lt; Scalar &gt; &amp;col_scaling)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual bool</type>
      <name>supportsScaleLeftImpl</name>
      <anchorfile>classThyra_1_1ScaledLinearOpBase.html</anchorfile>
      <anchor>a0c9dfa5f5edb6bb9e98e17fdbe683fce</anchor>
      <arglist>() const  =0</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual bool</type>
      <name>supportsScaleRightImpl</name>
      <anchorfile>classThyra_1_1ScaledLinearOpBase.html</anchorfile>
      <anchor>a8036a2dfe38524fd01264a06e1fa3ef7</anchor>
      <arglist>() const  =0</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual void</type>
      <name>scaleLeftImpl</name>
      <anchorfile>classThyra_1_1ScaledLinearOpBase.html</anchorfile>
      <anchor>a2c21c5e08dff133c0471a75af26e0b18</anchor>
      <arglist>(const VectorBase&lt; Scalar &gt; &amp;row_scaling)=0</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual void</type>
      <name>scaleRightImpl</name>
      <anchorfile>classThyra_1_1ScaledLinearOpBase.html</anchorfile>
      <anchor>a9e08a5037e8f4b4164661c2455878909</anchor>
      <arglist>(const VectorBase&lt; Scalar &gt; &amp;col_scaling)=0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ScaledLinearOpBase&lt; double &gt;</name>
    <filename>classThyra_1_1ScaledLinearOpBase.html</filename>
    <base virtualness="virtual">LinearOpBase&lt; double &gt;</base>
    <member kind="function">
      <type>bool</type>
      <name>supportsScaleLeft</name>
      <anchorfile>classThyra_1_1ScaledLinearOpBase.html</anchorfile>
      <anchor>ae6be35152312907551f0db1b48eea67e</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>supportsScaleRight</name>
      <anchorfile>classThyra_1_1ScaledLinearOpBase.html</anchorfile>
      <anchor>ac33ab8ac99fb6fbe351955af493dd1d2</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>scaleLeft</name>
      <anchorfile>classThyra_1_1ScaledLinearOpBase.html</anchorfile>
      <anchor>a305ccf775cf8db8d9c9ec285c3ab828d</anchor>
      <arglist>(const VectorBase&lt; double &gt; &amp;row_scaling)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>scaleRight</name>
      <anchorfile>classThyra_1_1ScaledLinearOpBase.html</anchorfile>
      <anchor>af71e8ca359d0939328d2bea4a1ccc7d6</anchor>
      <arglist>(const VectorBase&lt; double &gt; &amp;col_scaling)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual bool</type>
      <name>supportsScaleLeftImpl</name>
      <anchorfile>classThyra_1_1ScaledLinearOpBase.html</anchorfile>
      <anchor>a0c9dfa5f5edb6bb9e98e17fdbe683fce</anchor>
      <arglist>() const  =0</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual bool</type>
      <name>supportsScaleRightImpl</name>
      <anchorfile>classThyra_1_1ScaledLinearOpBase.html</anchorfile>
      <anchor>a8036a2dfe38524fd01264a06e1fa3ef7</anchor>
      <arglist>() const  =0</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual void</type>
      <name>scaleLeftImpl</name>
      <anchorfile>classThyra_1_1ScaledLinearOpBase.html</anchorfile>
      <anchor>a2c21c5e08dff133c0471a75af26e0b18</anchor>
      <arglist>(const VectorBase&lt; double &gt; &amp;row_scaling)=0</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual void</type>
      <name>scaleRightImpl</name>
      <anchorfile>classThyra_1_1ScaledLinearOpBase.html</anchorfile>
      <anchor>a9e08a5037e8f4b4164661c2455878909</anchor>
      <arglist>(const VectorBase&lt; double &gt; &amp;col_scaling)=0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::ScaledModelEvaluator</name>
    <filename>classThyra_1_1ScaledModelEvaluator.html</filename>
    <templarg></templarg>
    <base virtualness="virtual">Thyra::ModelEvaluatorDelegatorBase</base>
    <member kind="function">
      <type></type>
      <name>ScaledModelEvaluator</name>
      <anchorfile>classThyra_1_1ScaledModelEvaluator.html</anchorfile>
      <anchor>ac21941223314a97bc941a6cf68bef316</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>description</name>
      <anchorfile>classThyra_1_1ScaledModelEvaluator.html</anchorfile>
      <anchor>a5f23751c66aa5d3d7a3b701f2eb8bb43</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_f_scaling</name>
      <anchorfile>classThyra_1_1ScaledModelEvaluator.html</anchorfile>
      <anchor>a38f75022ae5a20ebdd226af92c167d3a</anchor>
      <arglist>(const RCP&lt; const Thyra::VectorBase&lt; Scalar &gt; &gt; &amp;f_scaling)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::DirectionalFiniteDiffCalculatorTypes::SelectedDerivatives</name>
    <filename>classThyra_1_1DirectionalFiniteDiffCalculatorTypes_1_1SelectedDerivatives.html</filename>
    <member kind="function">
      <type></type>
      <name>SelectedDerivatives</name>
      <anchorfile>classThyra_1_1DirectionalFiniteDiffCalculatorTypes_1_1SelectedDerivatives.html</anchorfile>
      <anchor>a8c826c698154ede667a936afb8f892e7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>SelectedDerivatives &amp;</type>
      <name>supports</name>
      <anchorfile>classThyra_1_1DirectionalFiniteDiffCalculatorTypes_1_1SelectedDerivatives.html</anchorfile>
      <anchor>a1d62df9e8998ffe779efecb4fff63249</anchor>
      <arglist>(ModelEvaluatorBase::EOutArgsDfDp arg, int l)</arglist>
    </member>
    <member kind="function">
      <type>SelectedDerivatives &amp;</type>
      <name>supports</name>
      <anchorfile>classThyra_1_1DirectionalFiniteDiffCalculatorTypes_1_1SelectedDerivatives.html</anchorfile>
      <anchor>accec7ba30c36d1f8f1722beeb43458d5</anchor>
      <arglist>(ModelEvaluatorBase::EOutArgsDgDp arg, int j, int l)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::SerialVectorSpaceConverterBase</name>
    <filename>classThyra_1_1SerialVectorSpaceConverterBase.html</filename>
    <templarg></templarg>
    <templarg></templarg>
    <base virtualness="virtual">Thyra::VectorSpaceConverterBase</base>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>convert</name>
      <anchorfile>classThyra_1_1SerialVectorSpaceConverterBase.html</anchorfile>
      <anchor>ab098f4db703b5f2e647dca70235230bf</anchor>
      <arglist>(const MultiVectorBase&lt; ScalarFrom &gt; &amp;mv_from, MultiVectorBase&lt; ScalarTo &gt; *mv_to) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::Simple2DModelEvaluator</name>
    <filename>classThyra_1_1Simple2DModelEvaluator.html</filename>
    <templarg></templarg>
    <base>Thyra::StateFuncModelEvaluatorBase</base>
    <member kind="function">
      <type>Teuchos::RCP&lt; Simple2DModelEvaluator&lt; Scalar &gt; &gt;</type>
      <name>simple2DModelEvaluator</name>
      <anchorfile>classThyra_1_1Simple2DModelEvaluator.html</anchorfile>
      <anchor>a3cc28486bb068d1f0de453ce99b0dd37</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_d</name>
      <anchorfile>classThyra_1_1Simple2DModelEvaluator.html</anchorfile>
      <anchor>a48841011c72108c3e8338c93e739e48c</anchor>
      <arglist>(const Scalar &amp;d)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_p</name>
      <anchorfile>classThyra_1_1Simple2DModelEvaluator.html</anchorfile>
      <anchor>a43de65802458ee90ea5e5618abd24853</anchor>
      <arglist>(const Teuchos::ArrayView&lt; const Scalar &gt; &amp;p)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_x0</name>
      <anchorfile>classThyra_1_1Simple2DModelEvaluator.html</anchorfile>
      <anchor>ae09316669edc12eeef6669ae05703ada</anchor>
      <arglist>(const Teuchos::ArrayView&lt; const Scalar &gt; &amp;x0)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setShowGetInvalidArgs</name>
      <anchorfile>classThyra_1_1Simple2DModelEvaluator.html</anchorfile>
      <anchor>af19f505d4ac8c9d847c78421292e519d</anchor>
      <arglist>(bool showGetInvalidArg)</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Thyra::VectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>get_x_space</name>
      <anchorfile>classThyra_1_1Simple2DModelEvaluator.html</anchorfile>
      <anchor>a4369a522279216858a3a390c3d022646</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Thyra::VectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>get_f_space</name>
      <anchorfile>classThyra_1_1Simple2DModelEvaluator.html</anchorfile>
      <anchor>ad345d317cf4b883421d8a728580a216a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Thyra::ModelEvaluatorBase::InArgs&lt; Scalar &gt;</type>
      <name>getNominalValues</name>
      <anchorfile>classThyra_1_1Simple2DModelEvaluator.html</anchorfile>
      <anchor>a763e59278d409f62c36a7c3c70aebb3a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; Thyra::LinearOpBase&lt; Scalar &gt; &gt;</type>
      <name>create_W_op</name>
      <anchorfile>classThyra_1_1Simple2DModelEvaluator.html</anchorfile>
      <anchor>a8299106270a1322bd7f4032f2058b4d8</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; Thyra::PreconditionerBase&lt; Scalar &gt; &gt;</type>
      <name>create_W_prec</name>
      <anchorfile>classThyra_1_1Simple2DModelEvaluator.html</anchorfile>
      <anchor>ac83710837904148ec7a7b2a30851380d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Thyra::LinearOpWithSolveFactoryBase&lt; Scalar &gt; &gt;</type>
      <name>get_W_factory</name>
      <anchorfile>classThyra_1_1Simple2DModelEvaluator.html</anchorfile>
      <anchor>ae0b30543f16b7ea6db411906e5d2cdc8</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Thyra::ModelEvaluatorBase::InArgs&lt; Scalar &gt;</type>
      <name>createInArgs</name>
      <anchorfile>classThyra_1_1Simple2DModelEvaluator.html</anchorfile>
      <anchor>a2956f0cb9c1eed2ded31f0d94e8b61e9</anchor>
      <arglist>() const </arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>Thyra::SolveCriteria</name>
    <filename>structThyra_1_1SolveCriteria.html</filename>
    <templarg>Scalar</templarg>
    <member kind="typedef">
      <type>Teuchos::ScalarTraits&lt; Scalar &gt;::magnitudeType</type>
      <name>ScalarMag</name>
      <anchorfile>structThyra_1_1SolveCriteria.html</anchorfile>
      <anchor>a8b3103a4fe93bb5baebee5666c4f6a84</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SolveCriteria</name>
      <anchorfile>structThyra_1_1SolveCriteria.html</anchorfile>
      <anchor>a6994d679c2f1e2f9ea00e255c63c1c0e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SolveCriteria</name>
      <anchorfile>structThyra_1_1SolveCriteria.html</anchorfile>
      <anchor>a591f1256fb4d54adee1550a6fc1b3d85</anchor>
      <arglist>(SolveMeasureType solveMeasureType_in, ScalarMag requestedTol_in, const RCP&lt; ParameterList &gt; &amp;extraParameters_in=Teuchos::null, const RCP&lt; ReductionFunctional&lt; Scalar &gt; &gt; &amp;numeratorReductionFunc_in=Teuchos::null, const RCP&lt; ReductionFunctional&lt; Scalar &gt; &gt; &amp;denominatorReductionFunc_in=Teuchos::null)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ScalarMag</type>
      <name>unspecifiedTolerance</name>
      <anchorfile>structThyra_1_1SolveCriteria.html</anchorfile>
      <anchor>a399f7bab843d05469ee12a7b5ea06192</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable">
      <type>SolveMeasureType</type>
      <name>solveMeasureType</name>
      <anchorfile>structThyra_1_1SolveCriteria.html</anchorfile>
      <anchor>abd5008a345e97645cc721267c681e7c1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>ScalarMag</type>
      <name>requestedTol</name>
      <anchorfile>structThyra_1_1SolveCriteria.html</anchorfile>
      <anchor>a008eb3e86e325237d09076a8717579dc</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>RCP&lt; ParameterList &gt;</type>
      <name>extraParameters</name>
      <anchorfile>structThyra_1_1SolveCriteria.html</anchorfile>
      <anchor>aa41ea6188c329614f27a01a7d4ca494e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>RCP&lt; const ReductionFunctional&lt; Scalar &gt; &gt;</type>
      <name>numeratorReductionFunc</name>
      <anchorfile>structThyra_1_1SolveCriteria.html</anchorfile>
      <anchor>a99f10616096a71841559b6c9e1649bf0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>RCP&lt; const ReductionFunctional&lt; Scalar &gt; &gt;</type>
      <name>denominatorReductionFunc</name>
      <anchorfile>structThyra_1_1SolveCriteria.html</anchorfile>
      <anchor>a161df996b2215fa3c731b21d34a06616</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>std::ostream &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>structThyra_1_1SolveCriteria.html</anchorfile>
      <anchor>af2c9d58acea5eacb674cec441e57d4be</anchor>
      <arglist>(std::ostream &amp;out, const SolveCriteria&lt; Scalar &gt; &amp;solveCriteria)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>Thyra::SolveMeasureType</name>
    <filename>structThyra_1_1SolveMeasureType.html</filename>
    <member kind="function">
      <type></type>
      <name>SolveMeasureType</name>
      <anchorfile>structThyra_1_1SolveMeasureType.html</anchorfile>
      <anchor>aa6f3dc36773a5447cd8fb9abbb091bfd</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SolveMeasureType</name>
      <anchorfile>structThyra_1_1SolveMeasureType.html</anchorfile>
      <anchor>ade8147e35a284a0d847fe8be9f61fb19</anchor>
      <arglist>(ESolveMeasureNormType _numerator, ESolveMeasureNormType _denominator)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set</name>
      <anchorfile>structThyra_1_1SolveMeasureType.html</anchorfile>
      <anchor>a5d2b37df46b74cfca0e505cf4427d64c</anchor>
      <arglist>(ESolveMeasureNormType _numerator, ESolveMeasureNormType _denominator)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>useDefault</name>
      <anchorfile>structThyra_1_1SolveMeasureType.html</anchorfile>
      <anchor>abede57740caf365831e25bc810463556</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator()</name>
      <anchorfile>structThyra_1_1SolveMeasureType.html</anchorfile>
      <anchor>a1375f9b4089891efbde7c4bb555148a7</anchor>
      <arglist>(ESolveMeasureNormType numerator_in, ESolveMeasureNormType denominator_in) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>contains</name>
      <anchorfile>structThyra_1_1SolveMeasureType.html</anchorfile>
      <anchor>a78a1b675b805ced227347f1e22ba882d</anchor>
      <arglist>(ESolveMeasureNormType measure) const </arglist>
    </member>
    <member kind="variable">
      <type>ESolveMeasureNormType</type>
      <name>numerator</name>
      <anchorfile>structThyra_1_1SolveMeasureType.html</anchorfile>
      <anchor>a00b5bced5b83c3f48174f1b175cd585f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>ESolveMeasureNormType</type>
      <name>denominator</name>
      <anchorfile>structThyra_1_1SolveMeasureType.html</anchorfile>
      <anchor>ae680020df4de7fa2caf87b4fd8ca868f</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>std::ostream &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>structThyra_1_1SolveMeasureType.html</anchorfile>
      <anchor>ad2e4617f91d6c1f273cb6162d553e1b4</anchor>
      <arglist>(std::ostream &amp;out, const SolveMeasureType &amp;solveMeasureType)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>Thyra::SolveStatus</name>
    <filename>structThyra_1_1SolveStatus.html</filename>
    <templarg>Scalar</templarg>
    <member kind="typedef">
      <type>Teuchos::ScalarTraits&lt; Scalar &gt;::magnitudeType</type>
      <name>ScalarMag</name>
      <anchorfile>structThyra_1_1SolveStatus.html</anchorfile>
      <anchor>a2289bb58d5b0b757443641f2089ef369</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SolveStatus</name>
      <anchorfile>structThyra_1_1SolveStatus.html</anchorfile>
      <anchor>a1131d146346368dc065594c1705b0896</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ScalarMag</type>
      <name>unknownTolerance</name>
      <anchorfile>structThyra_1_1SolveStatus.html</anchorfile>
      <anchor>a0a96cad9f0f9b00a11b6c6c20ab4e739</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static std::string</type>
      <name>achievedTolToString</name>
      <anchorfile>structThyra_1_1SolveStatus.html</anchorfile>
      <anchor>a61e741eefac48167af945e519cfd23b5</anchor>
      <arglist>(const ScalarMag &amp;achievedTol)</arglist>
    </member>
    <member kind="variable">
      <type>ESolveStatus</type>
      <name>solveStatus</name>
      <anchorfile>structThyra_1_1SolveStatus.html</anchorfile>
      <anchor>a68e6ed25ae89f3db0e24984df38df945</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>ScalarMag</type>
      <name>achievedTol</name>
      <anchorfile>structThyra_1_1SolveStatus.html</anchorfile>
      <anchor>a9a1950383aacc10d7a09be839e633dd2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::string</type>
      <name>message</name>
      <anchorfile>structThyra_1_1SolveStatus.html</anchorfile>
      <anchor>a5e0a6a08d4d9a1733869c78f91b735c1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>RCP&lt; ParameterList &gt;</type>
      <name>extraParameters</name>
      <anchorfile>structThyra_1_1SolveStatus.html</anchorfile>
      <anchor>a9e62bdd038453e61cca2e5d7e0e2e272</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>std::ostream &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>structThyra_1_1SolveStatus.html</anchorfile>
      <anchor>a3598b3ae7a4316bb098f9e9220216b19</anchor>
      <arglist>(std::ostream &amp;out_arg, const SolveStatus&lt; Scalar &gt; &amp;solveStatus)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>accumulateSolveStatusInit</name>
      <anchorfile>structThyra_1_1SolveStatus.html</anchorfile>
      <anchor>ab0ed482367e53ed438e2a6dbd3917848</anchor>
      <arglist>(const Ptr&lt; SolveStatus&lt; Scalar &gt; &gt; &amp;overallSolveStatus)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>accumulateSolveStatus</name>
      <anchorfile>structThyra_1_1SolveStatus.html</anchorfile>
      <anchor>aca3dea7982de16447ca8c521ef659d3f</anchor>
      <arglist>(const SolveCriteria&lt; Scalar &gt;, const SolveStatus&lt; Scalar &gt; &amp;solveStatus, const Ptr&lt; SolveStatus&lt; Scalar &gt; &gt; &amp;overallSolveStatus)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::SpmdMultiVectorBase</name>
    <filename>classThyra_1_1SpmdMultiVectorBase.html</filename>
    <templarg></templarg>
    <base virtualness="virtual">Thyra::MultiVectorBase</base>
    <member kind="function">
      <type>RCP&lt; const SpmdVectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>spmdSpace</name>
      <anchorfile>classThyra_1_1SpmdMultiVectorBase.html</anchorfile>
      <anchor>ab209eb58d059d6be44dfeca1562bb907</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RTOpPack::SubMultiVectorView&lt; Scalar &gt;</type>
      <name>getNonconstLocalSubMultiVector</name>
      <anchorfile>classThyra_1_1SpmdMultiVectorBase.html</anchorfile>
      <anchor>a17fcc87b1373f237ae291e1cecf1036c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>RTOpPack::ConstSubMultiVectorView&lt; Scalar &gt;</type>
      <name>getLocalSubMultiVector</name>
      <anchorfile>classThyra_1_1SpmdMultiVectorBase.html</anchorfile>
      <anchor>a5944dd611c6fed1ec8bb887789de5727</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>getNonconstLocalData</name>
      <anchorfile>classThyra_1_1SpmdMultiVectorBase.html</anchorfile>
      <anchor>aeaf740fbcaa61011fdbd79099c5dc3e9</anchor>
      <arglist>(const Ptr&lt; ArrayRCP&lt; Scalar &gt; &gt; &amp;localValues, const Ptr&lt; Ordinal &gt; &amp;leadingDim)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>getLocalData</name>
      <anchorfile>classThyra_1_1SpmdMultiVectorBase.html</anchorfile>
      <anchor>a188f9281a84881d9816f3bf8444cc91b</anchor>
      <arglist>(const Ptr&lt; ArrayRCP&lt; const Scalar &gt; &gt; &amp;localValues, const Ptr&lt; Ordinal &gt; &amp;leadingDim) const </arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual RCP&lt; const SpmdVectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>spmdSpaceImpl</name>
      <anchorfile>classThyra_1_1SpmdMultiVectorBase.html</anchorfile>
      <anchor>aacc08a9306626ce0d833df7fea458a23</anchor>
      <arglist>() const  =0</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual RTOpPack::SubMultiVectorView&lt; Scalar &gt;</type>
      <name>getNonconstLocalSubMultiVectorImpl</name>
      <anchorfile>classThyra_1_1SpmdMultiVectorBase.html</anchorfile>
      <anchor>a5c519cd766c67fe959112b9179aa9073</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual RTOpPack::ConstSubMultiVectorView&lt; Scalar &gt;</type>
      <name>getLocalSubMultiVectorImpl</name>
      <anchorfile>classThyra_1_1SpmdMultiVectorBase.html</anchorfile>
      <anchor>a332c8d58a5b05365fd9d74d3574b9505</anchor>
      <arglist>() const  =0</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual void</type>
      <name>getNonconstLocalMultiVectorDataImpl</name>
      <anchorfile>classThyra_1_1SpmdMultiVectorBase.html</anchorfile>
      <anchor>a556a2351fa8088d3932164b302f839d9</anchor>
      <arglist>(const Ptr&lt; ArrayRCP&lt; Scalar &gt; &gt; &amp;localValues, const Ptr&lt; Ordinal &gt; &amp;leadingDim)=0</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual void</type>
      <name>getLocalMultiVectorDataImpl</name>
      <anchorfile>classThyra_1_1SpmdMultiVectorBase.html</anchorfile>
      <anchor>a0066eba90fcc86008ed8161f830bb882</anchor>
      <arglist>(const Ptr&lt; ArrayRCP&lt; const Scalar &gt; &gt; &amp;localValues, const Ptr&lt; Ordinal &gt; &amp;leadingDim) const  =0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::SpmdMultiVectorDefaultBase</name>
    <filename>classThyra_1_1SpmdMultiVectorDefaultBase.html</filename>
    <templarg></templarg>
    <base virtualness="virtual">Thyra::SpmdMultiVectorBase</base>
    <base virtualness="virtual">Thyra::MultiVectorAdapterBase</base>
    <member kind="function">
      <type></type>
      <name>SpmdMultiVectorDefaultBase</name>
      <anchorfile>classThyra_1_1SpmdMultiVectorDefaultBase.html</anchorfile>
      <anchor>a3b24a839581c57f90505354f99b36d6d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const ScalarProdVectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>rangeScalarProdVecSpc</name>
      <anchorfile>classThyra_1_1SpmdMultiVectorDefaultBase.html</anchorfile>
      <anchor>a37f1519f723a3934d97e35ef7bfb70b2</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>RTOpPack::SubMultiVectorView&lt; Scalar &gt;</type>
      <name>getNonconstLocalSubMultiVectorImpl</name>
      <anchorfile>classThyra_1_1SpmdMultiVectorDefaultBase.html</anchorfile>
      <anchor>aaea6b873ce2ca30a5ed3e5c8cd62ad09</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>RTOpPack::ConstSubMultiVectorView&lt; Scalar &gt;</type>
      <name>getLocalSubMultiVectorImpl</name>
      <anchorfile>classThyra_1_1SpmdMultiVectorDefaultBase.html</anchorfile>
      <anchor>aabb3a0b20c9f09dc090421a9ca35e7a7</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>mvMultiReductApplyOpImpl</name>
      <anchorfile>classThyra_1_1SpmdMultiVectorDefaultBase.html</anchorfile>
      <anchor>a5556146365d40b7d18a824b0dee4d421</anchor>
      <arglist>(const RTOpPack::RTOpT&lt; Scalar &gt; &amp;primary_op, const ArrayView&lt; const Ptr&lt; const MultiVectorBase&lt; Scalar &gt; &gt; &gt; &amp;multi_vecs, const ArrayView&lt; const Ptr&lt; MultiVectorBase&lt; Scalar &gt; &gt; &gt; &amp;targ_multi_vecs, const ArrayView&lt; const Ptr&lt; RTOpPack::ReductTarget &gt; &gt; &amp;reduct_objs, const Ordinal primary_global_offset) const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>acquireDetachedMultiVectorViewImpl</name>
      <anchorfile>classThyra_1_1SpmdMultiVectorDefaultBase.html</anchorfile>
      <anchor>a278f4d0f818abb9427f9251d4a80b923</anchor>
      <arglist>(const Range1D &amp;rowRng, const Range1D &amp;colRng, RTOpPack::ConstSubMultiVectorView&lt; Scalar &gt; *sub_mv) const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>releaseDetachedMultiVectorViewImpl</name>
      <anchorfile>classThyra_1_1SpmdMultiVectorDefaultBase.html</anchorfile>
      <anchor>ae083e53d90945201c9387c5715853550</anchor>
      <arglist>(RTOpPack::ConstSubMultiVectorView&lt; Scalar &gt; *sub_mv) const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>acquireNonconstDetachedMultiVectorViewImpl</name>
      <anchorfile>classThyra_1_1SpmdMultiVectorDefaultBase.html</anchorfile>
      <anchor>ab8425331bd55c07b124f317546b52077</anchor>
      <arglist>(const Range1D &amp;rowRng, const Range1D &amp;colRng, RTOpPack::SubMultiVectorView&lt; Scalar &gt; *sub_mv)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>commitNonconstDetachedMultiVectorViewImpl</name>
      <anchorfile>classThyra_1_1SpmdMultiVectorDefaultBase.html</anchorfile>
      <anchor>affff7909bc831eae9a32ce21afc6a7f5</anchor>
      <arglist>(RTOpPack::SubMultiVectorView&lt; Scalar &gt; *sub_mv)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>euclideanApply</name>
      <anchorfile>classThyra_1_1SpmdMultiVectorDefaultBase.html</anchorfile>
      <anchor>a1fcdb1086ef1a9311b61dc61d55ee9f1</anchor>
      <arglist>(const EOpTransp M_trans, const MultiVectorBase&lt; Scalar &gt; &amp;X, const Ptr&lt; MultiVectorBase&lt; Scalar &gt; &gt; &amp;Y, const Scalar alpha, const Scalar beta) const </arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual void</type>
      <name>updateSpmdSpace</name>
      <anchorfile>classThyra_1_1SpmdMultiVectorDefaultBase.html</anchorfile>
      <anchor>ab91f48e0bf078c78aac91e297ab6e973</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>Range1D</type>
      <name>validateRowRange</name>
      <anchorfile>classThyra_1_1SpmdMultiVectorDefaultBase.html</anchorfile>
      <anchor>adea97e3133f2b7ccc6e6c060303c51b4</anchor>
      <arglist>(const Range1D &amp;rowRng) const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>Range1D</type>
      <name>validateColRange</name>
      <anchorfile>classThyra_1_1SpmdMultiVectorDefaultBase.html</anchorfile>
      <anchor>abf28fdad262ca276bd4e6360f035e81c</anchor>
      <arglist>(const Range1D &amp;rowCol) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::SpmdMultiVectorSerializer</name>
    <filename>classThyra_1_1SpmdMultiVectorSerializer.html</filename>
    <templarg>Scalar</templarg>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classThyra_1_1SpmdMultiVectorSerializer.html</anchorfile>
      <anchor>a1b91cf59d2b5c8a6cb789809a86e87c4</anchor>
      <arglist>(bool, binaryMode)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SpmdMultiVectorSerializer</name>
      <anchorfile>classThyra_1_1SpmdMultiVectorSerializer.html</anchorfile>
      <anchor>ad8e91d6b78919582f0812921b9f10da7</anchor>
      <arglist>(const bool binaryMode=false)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isCompatible</name>
      <anchorfile>classThyra_1_1SpmdMultiVectorSerializer.html</anchorfile>
      <anchor>a67b3c69b2ca8d6fdb0ffaa8674bed835</anchor>
      <arglist>(const MultiVectorBase&lt; Scalar &gt; &amp;mv) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>serialize</name>
      <anchorfile>classThyra_1_1SpmdMultiVectorSerializer.html</anchorfile>
      <anchor>addfcb10e33176cfff171ad113e313cf2</anchor>
      <arglist>(const MultiVectorBase&lt; Scalar &gt; &amp;mv, std::ostream &amp;out) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>deserialize</name>
      <anchorfile>classThyra_1_1SpmdMultiVectorSerializer.html</anchorfile>
      <anchor>a00023d33f8fa3650ded46b57e89cd805</anchor>
      <arglist>(std::istream &amp;in, MultiVectorBase&lt; Scalar &gt; *mv) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::SpmdVectorBase</name>
    <filename>classThyra_1_1SpmdVectorBase.html</filename>
    <templarg></templarg>
    <base virtualness="virtual">Thyra::VectorBase</base>
    <base virtualness="virtual">Thyra::SpmdMultiVectorBase</base>
    <member kind="function">
      <type>RTOpPack::SubVectorView&lt; Scalar &gt;</type>
      <name>getNonconstLocalSubVector</name>
      <anchorfile>classThyra_1_1SpmdVectorBase.html</anchorfile>
      <anchor>a57946a9c4ef717cd91ae841a5935a333</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>RTOpPack::ConstSubVectorView&lt; Scalar &gt;</type>
      <name>getLocalSubVector</name>
      <anchorfile>classThyra_1_1SpmdVectorBase.html</anchorfile>
      <anchor>a6a855af14363ad0e2d65f1bf2a00eca4</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>getNonconstLocalData</name>
      <anchorfile>classThyra_1_1SpmdVectorBase.html</anchorfile>
      <anchor>a5d978b06671650fb01f495b1273b22a6</anchor>
      <arglist>(const Ptr&lt; ArrayRCP&lt; Scalar &gt; &gt; &amp;localValues)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>getLocalData</name>
      <anchorfile>classThyra_1_1SpmdVectorBase.html</anchorfile>
      <anchor>a71c7ab5adf29fdcb8c37569cd8121535</anchor>
      <arglist>(const Ptr&lt; ArrayRCP&lt; const Scalar &gt; &gt; &amp;localValues) const </arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual RTOpPack::SubVectorView&lt; Scalar &gt;</type>
      <name>getNonconstLocalSubVectorImpl</name>
      <anchorfile>classThyra_1_1SpmdVectorBase.html</anchorfile>
      <anchor>a6d056f99cb85abda69e50a0ad8ae6541</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual RTOpPack::ConstSubVectorView&lt; Scalar &gt;</type>
      <name>getLocalSubVectorImpl</name>
      <anchorfile>classThyra_1_1SpmdVectorBase.html</anchorfile>
      <anchor>a66c72b2fbb6c5f1db262a08e6d8afc1f</anchor>
      <arglist>() const  =0</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual void</type>
      <name>getNonconstLocalVectorDataImpl</name>
      <anchorfile>classThyra_1_1SpmdVectorBase.html</anchorfile>
      <anchor>a9bee973e85aebc495c94c4013a82af81</anchor>
      <arglist>(const Ptr&lt; ArrayRCP&lt; Scalar &gt; &gt; &amp;localValues)=0</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual void</type>
      <name>getLocalVectorDataImpl</name>
      <anchorfile>classThyra_1_1SpmdVectorBase.html</anchorfile>
      <anchor>ad2c3f74ac63499909425b73580f719f6</anchor>
      <arglist>(const Ptr&lt; ArrayRCP&lt; const Scalar &gt; &gt; &amp;localValues) const  =0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::SpmdVectorDefaultBase</name>
    <filename>classThyra_1_1SpmdVectorDefaultBase.html</filename>
    <templarg></templarg>
    <base virtualness="virtual">Thyra::SpmdVectorBase</base>
    <base virtualness="virtual">Thyra::VectorDefaultBase</base>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>applyOpImplWithComm</name>
      <anchorfile>classThyra_1_1SpmdVectorDefaultBase.html</anchorfile>
      <anchor>a5d4d3b5b7dfffeb02395be1237fe9f42</anchor>
      <arglist>(const Ptr&lt; const Teuchos::Comm&lt; Ordinal &gt; &gt; &amp;comm, const RTOpPack::RTOpT&lt; Scalar &gt; &amp;op, const ArrayView&lt; const Ptr&lt; const VectorBase&lt; Scalar &gt; &gt; &gt; &amp;vecs, const ArrayView&lt; const Ptr&lt; VectorBase&lt; Scalar &gt; &gt; &gt; &amp;targ_vecs, const Ptr&lt; RTOpPack::ReductTarget &gt; &amp;reduct_obj, const Ordinal global_offset) const </arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SpmdVectorDefaultBase</name>
      <anchorfile>classThyra_1_1SpmdVectorDefaultBase.html</anchorfile>
      <anchor>a4471a265638bd483a9c41c228d265714</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>description</name>
      <anchorfile>classThyra_1_1SpmdVectorDefaultBase.html</anchorfile>
      <anchor>a378437debe6c62be23220f4e6ec97383</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const VectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>space</name>
      <anchorfile>classThyra_1_1SpmdVectorDefaultBase.html</anchorfile>
      <anchor>a461c1575ecd428bd9fa9aeb6c3019cdc</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>applyOpImpl</name>
      <anchorfile>classThyra_1_1SpmdVectorDefaultBase.html</anchorfile>
      <anchor>afa012d2ccb7a1e48f4b6de7825966fa7</anchor>
      <arglist>(const RTOpPack::RTOpT&lt; Scalar &gt; &amp;op, const ArrayView&lt; const Ptr&lt; const VectorBase&lt; Scalar &gt; &gt; &gt; &amp;vecs, const ArrayView&lt; const Ptr&lt; VectorBase&lt; Scalar &gt; &gt; &gt; &amp;targ_vecs, const Ptr&lt; RTOpPack::ReductTarget &gt; &amp;reduct_obj, const Ordinal global_offset) const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>acquireDetachedVectorViewImpl</name>
      <anchorfile>classThyra_1_1SpmdVectorDefaultBase.html</anchorfile>
      <anchor>a4a9f68e5e3bed7ec63cdbb0bbe57d56b</anchor>
      <arglist>(const Range1D &amp;rng, RTOpPack::ConstSubVectorView&lt; Scalar &gt; *sub_vec) const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>releaseDetachedVectorViewImpl</name>
      <anchorfile>classThyra_1_1SpmdVectorDefaultBase.html</anchorfile>
      <anchor>ad0caf28a4e7943f7526cb2755f5ca616</anchor>
      <arglist>(RTOpPack::ConstSubVectorView&lt; Scalar &gt; *sub_vec) const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>acquireNonconstDetachedVectorViewImpl</name>
      <anchorfile>classThyra_1_1SpmdVectorDefaultBase.html</anchorfile>
      <anchor>a33fd49f0ac7b433355c2e8522594e33b</anchor>
      <arglist>(const Range1D &amp;rng, RTOpPack::SubVectorView&lt; Scalar &gt; *sub_vec)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>commitNonconstDetachedVectorViewImpl</name>
      <anchorfile>classThyra_1_1SpmdVectorDefaultBase.html</anchorfile>
      <anchor>a97ac49980c1cc81688c0a1259e0fdb37</anchor>
      <arglist>(RTOpPack::SubVectorView&lt; Scalar &gt; *sub_vec)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>RTOpPack::SubMultiVectorView&lt; Scalar &gt;</type>
      <name>getNonconstLocalSubMultiVectorImpl</name>
      <anchorfile>classThyra_1_1SpmdVectorDefaultBase.html</anchorfile>
      <anchor>a021472232fbf79f0ece68cbd68719d66</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>RTOpPack::ConstSubMultiVectorView&lt; Scalar &gt;</type>
      <name>getLocalSubMultiVectorImpl</name>
      <anchorfile>classThyra_1_1SpmdVectorDefaultBase.html</anchorfile>
      <anchor>a6b03f15dac59c0a781bbf54d8bb98fc2</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>getNonconstLocalMultiVectorDataImpl</name>
      <anchorfile>classThyra_1_1SpmdVectorDefaultBase.html</anchorfile>
      <anchor>ad924590a5e16d7d245aff505abbe5573</anchor>
      <arglist>(const Ptr&lt; ArrayRCP&lt; Scalar &gt; &gt; &amp;localValues, const Ptr&lt; Ordinal &gt; &amp;leadingDim)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>getLocalMultiVectorDataImpl</name>
      <anchorfile>classThyra_1_1SpmdVectorDefaultBase.html</anchorfile>
      <anchor>a8daed6f226d284e09e1629a0b62b3d34</anchor>
      <arglist>(const Ptr&lt; ArrayRCP&lt; const Scalar &gt; &gt; &amp;localValues, const Ptr&lt; Ordinal &gt; &amp;leadingDim) const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>RTOpPack::SubVectorView&lt; Scalar &gt;</type>
      <name>getNonconstLocalSubVectorImpl</name>
      <anchorfile>classThyra_1_1SpmdVectorDefaultBase.html</anchorfile>
      <anchor>aef7dfd3cb05117ea92fce4e75541913c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>RTOpPack::ConstSubVectorView&lt; Scalar &gt;</type>
      <name>getLocalSubVectorImpl</name>
      <anchorfile>classThyra_1_1SpmdVectorDefaultBase.html</anchorfile>
      <anchor>a2f50cd7e7bb05d318ef83bb51d7722db</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual void</type>
      <name>updateSpmdSpace</name>
      <anchorfile>classThyra_1_1SpmdVectorDefaultBase.html</anchorfile>
      <anchor>aa3f292d56b71f5b2e75cf91bdc4d7fd7</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::SpmdVectorSpaceBase</name>
    <filename>classThyra_1_1SpmdVectorSpaceBase.html</filename>
    <templarg>Scalar</templarg>
    <base virtualness="virtual">Thyra::VectorSpaceBase</base>
    <member kind="function" virtualness="pure">
      <type>virtual Teuchos::RCP&lt; const Teuchos::Comm&lt; Ordinal &gt; &gt;</type>
      <name>getComm</name>
      <anchorfile>classThyra_1_1SpmdVectorSpaceBase.html</anchorfile>
      <anchor>a42450d2dc4db2e7c85b2e3f678168fda</anchor>
      <arglist>() const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual Ordinal</type>
      <name>localSubDim</name>
      <anchorfile>classThyra_1_1SpmdVectorSpaceBase.html</anchorfile>
      <anchor>abf46c990c39ef235d5d71b2e40e27bf8</anchor>
      <arglist>() const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual Ordinal</type>
      <name>localOffset</name>
      <anchorfile>classThyra_1_1SpmdVectorSpaceBase.html</anchorfile>
      <anchor>aca1195c46972c94ba9be6ad7cb104755</anchor>
      <arglist>() const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual Ordinal</type>
      <name>mapCode</name>
      <anchorfile>classThyra_1_1SpmdVectorSpaceBase.html</anchorfile>
      <anchor>af8d7f7d7d573bcd5f153be587517e1c8</anchor>
      <arglist>() const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>isLocallyReplicated</name>
      <anchorfile>classThyra_1_1SpmdVectorSpaceBase.html</anchorfile>
      <anchor>a9038db806a14217085c17128ca03c507</anchor>
      <arglist>() const  =0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::SpmdVectorSpaceDefaultBase</name>
    <filename>classThyra_1_1SpmdVectorSpaceDefaultBase.html</filename>
    <templarg></templarg>
    <base virtualness="virtual">Thyra::SpmdVectorSpaceBase</base>
    <base virtualness="virtual">Thyra::ScalarProdVectorSpaceBase</base>
    <member kind="function">
      <type></type>
      <name>SpmdVectorSpaceDefaultBase</name>
      <anchorfile>classThyra_1_1SpmdVectorSpaceDefaultBase.html</anchorfile>
      <anchor>a8c16e9f84b7b3fc73fac0976767df2fb</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual void</type>
      <name>updateState</name>
      <anchorfile>classThyra_1_1SpmdVectorSpaceDefaultBase.html</anchorfile>
      <anchor>a06e2ff2288a78f6101a955b29d4e611c</anchor>
      <arglist>(const Ordinal globalDim, const bool isLocallyReplicated=false)</arglist>
    </member>
    <member kind="function">
      <type>Ordinal</type>
      <name>localOffset</name>
      <anchorfile>classThyra_1_1SpmdVectorSpaceDefaultBase.html</anchorfile>
      <anchor>a5454ecb9249d62e62db0b121dbb3198d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Ordinal</type>
      <name>mapCode</name>
      <anchorfile>classThyra_1_1SpmdVectorSpaceDefaultBase.html</anchorfile>
      <anchor>a19a35b0855a50767c31c26baaa78e10b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isLocallyReplicated</name>
      <anchorfile>classThyra_1_1SpmdVectorSpaceDefaultBase.html</anchorfile>
      <anchor>aaaf0b34f3b9402744654728212cdb251</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>description</name>
      <anchorfile>classThyra_1_1SpmdVectorSpaceDefaultBase.html</anchorfile>
      <anchor>a651fb55b7995a4133a4c4f3a1b5242f7</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Ordinal</type>
      <name>dim</name>
      <anchorfile>classThyra_1_1SpmdVectorSpaceDefaultBase.html</anchorfile>
      <anchor>a93b80b4a5103dd5f9aac6ac1ef35cda5</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const VectorSpaceFactoryBase&lt; Scalar &gt; &gt;</type>
      <name>smallVecSpcFcty</name>
      <anchorfile>classThyra_1_1SpmdVectorSpaceDefaultBase.html</anchorfile>
      <anchor>ad31a9a34089d0827859535f925798b73</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isCompatible</name>
      <anchorfile>classThyra_1_1SpmdVectorSpaceDefaultBase.html</anchorfile>
      <anchor>a2f7653bcfb69c95b7f93bbf2752e87d2</anchor>
      <arglist>(const VectorSpaceBase&lt; Scalar &gt; &amp;vecSpc) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::StateFuncModelEvaluatorBase</name>
    <filename>classThyra_1_1StateFuncModelEvaluatorBase.html</filename>
    <templarg></templarg>
    <base virtualness="virtual">Thyra::ModelEvaluatorDefaultBase</base>
    <member kind="function">
      <type>RCP&lt; const VectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>get_p_space</name>
      <anchorfile>classThyra_1_1StateFuncModelEvaluatorBase.html</anchorfile>
      <anchor>a07d2f11acd6c9b187b55aab174e8770d</anchor>
      <arglist>(int l) const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const Teuchos::Array&lt; std::string &gt; &gt;</type>
      <name>get_p_names</name>
      <anchorfile>classThyra_1_1StateFuncModelEvaluatorBase.html</anchorfile>
      <anchor>a1fe876b5363efa2d57ec6ce317ceaf4b</anchor>
      <arglist>(int l) const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const VectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>get_g_space</name>
      <anchorfile>classThyra_1_1StateFuncModelEvaluatorBase.html</anchorfile>
      <anchor>a7e0ab2b8a75d8840be31e136c06427a8</anchor>
      <arglist>(int j) const </arglist>
    </member>
    <member kind="function">
      <type>Teuchos::ArrayView&lt; const std::string &gt;</type>
      <name>get_g_names</name>
      <anchorfile>classThyra_1_1StateFuncModelEvaluatorBase.html</anchorfile>
      <anchor>abcbfc1359cd35104c0a241c0d19fa388</anchor>
      <arglist>(int j) const </arglist>
    </member>
    <member kind="function">
      <type>ModelEvaluatorBase::InArgs&lt; Scalar &gt;</type>
      <name>getNominalValues</name>
      <anchorfile>classThyra_1_1StateFuncModelEvaluatorBase.html</anchorfile>
      <anchor>a51b38ce14d1d06a4a86a6c807e35bcfb</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>ModelEvaluatorBase::InArgs&lt; Scalar &gt;</type>
      <name>getLowerBounds</name>
      <anchorfile>classThyra_1_1StateFuncModelEvaluatorBase.html</anchorfile>
      <anchor>a1a91f1b5fec116801a68e0278563a2fa</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>ModelEvaluatorBase::InArgs&lt; Scalar &gt;</type>
      <name>getUpperBounds</name>
      <anchorfile>classThyra_1_1StateFuncModelEvaluatorBase.html</anchorfile>
      <anchor>a3c30cfa7d03ed08bb1cd9141f5637ee5</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; LinearOpBase&lt; Scalar &gt; &gt;</type>
      <name>create_W_op</name>
      <anchorfile>classThyra_1_1StateFuncModelEvaluatorBase.html</anchorfile>
      <anchor>af2af35b87c38699bb53d20adfac26cc9</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; PreconditionerBase&lt; Scalar &gt; &gt;</type>
      <name>create_W_prec</name>
      <anchorfile>classThyra_1_1StateFuncModelEvaluatorBase.html</anchorfile>
      <anchor>a7c15822f1c2b50b8e44bb5f62daf6b52</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const LinearOpWithSolveFactoryBase&lt; Scalar &gt; &gt;</type>
      <name>get_W_factory</name>
      <anchorfile>classThyra_1_1StateFuncModelEvaluatorBase.html</anchorfile>
      <anchor>a8a4589e0042f2637e7640ece6c4ae937</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>reportFinalPoint</name>
      <anchorfile>classThyra_1_1StateFuncModelEvaluatorBase.html</anchorfile>
      <anchor>ad2cfc0f5aec1972ba49077931c7caa0c</anchor>
      <arglist>(const ModelEvaluatorBase::InArgs&lt; Scalar &gt; &amp;finalPoint, const bool wasSolved)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::TestResultsPrinter</name>
    <filename>classThyra_1_1TestResultsPrinter.html</filename>
    <member kind="function">
      <type></type>
      <name>TestResultsPrinter</name>
      <anchorfile>classThyra_1_1TestResultsPrinter.html</anchorfile>
      <anchor>aa4f91a712ea100d5a29f347f07834d96</anchor>
      <arglist>(const RCP&lt; FancyOStream &gt; &amp;out, const bool show_all_tests)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~TestResultsPrinter</name>
      <anchorfile>classThyra_1_1TestResultsPrinter.html</anchorfile>
      <anchor>a4637ec6daf177455c5bbf09cc7c1824e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; FancyOStream &gt;</type>
      <name>replaceOStream</name>
      <anchorfile>classThyra_1_1TestResultsPrinter.html</anchorfile>
      <anchor>a6dea6583e6e8b74bb08929bc498e6568</anchor>
      <arglist>(const RCP&lt; FancyOStream &gt; &amp;out)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; FancyOStream &gt;</type>
      <name>getTestOStream</name>
      <anchorfile>classThyra_1_1TestResultsPrinter.html</anchorfile>
      <anchor>a45e50dc5dd0d78b8ba540b4d4d918dbc</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>printTestResults</name>
      <anchorfile>classThyra_1_1TestResultsPrinter.html</anchorfile>
      <anchor>ae3dadc3b7eda17193749dd4b07f74021</anchor>
      <arglist>(const bool this_result, const Ptr&lt; bool &gt; &amp;success)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::TpetraLinearOp</name>
    <filename>classThyra_1_1TpetraLinearOp.html</filename>
    <templarg></templarg>
    <templarg></templarg>
    <templarg></templarg>
    <templarg></templarg>
    <base virtualness="virtual">Thyra::LinearOpDefaultBase</base>
    <base virtualness="virtual">Thyra::ScaledLinearOpBase</base>
    <base virtualness="virtual">Thyra::RowStatLinearOpBase</base>
    <member kind="function">
      <type>RCP&lt; TpetraLinearOp&lt; Scalar, LocalOrdinal, GlobalOrdinal, Node &gt; &gt;</type>
      <name>tpetraLinearOp</name>
      <anchorfile>classThyra_1_1TpetraLinearOp.html</anchorfile>
      <anchor>a7ddd712a84e763ceecfe04eeb0b35f9c</anchor>
      <arglist>(const RCP&lt; const VectorSpaceBase&lt; Scalar &gt; &gt; &amp;rangeSpace, const RCP&lt; const VectorSpaceBase&lt; Scalar &gt; &gt; &amp;domainSpace, const RCP&lt; Tpetra::Operator&lt; Scalar, LocalOrdinal, GlobalOrdinal, Node &gt; &gt; &amp;tpetraOperator)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const TpetraLinearOp&lt; Scalar, LocalOrdinal, GlobalOrdinal, Node &gt; &gt;</type>
      <name>constTpetraLinearOp</name>
      <anchorfile>classThyra_1_1TpetraLinearOp.html</anchorfile>
      <anchor>a761c6be41d59c38deffab5b214b17456</anchor>
      <arglist>(const RCP&lt; const VectorSpaceBase&lt; Scalar &gt; &gt; &amp;rangeSpace, const RCP&lt; const VectorSpaceBase&lt; Scalar &gt; &gt; &amp;domainSpace, const RCP&lt; const Tpetra::Operator&lt; Scalar, LocalOrdinal, GlobalOrdinal, Node &gt; &gt; &amp;tpetraOperator)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>TpetraLinearOp</name>
      <anchorfile>classThyra_1_1TpetraLinearOp.html</anchorfile>
      <anchor>a4e4471bcf173eccae7954ce3c1887708</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initialize</name>
      <anchorfile>classThyra_1_1TpetraLinearOp.html</anchorfile>
      <anchor>a78d3a10ed8881358c0a40bab47f0f44f</anchor>
      <arglist>(const RCP&lt; const VectorSpaceBase&lt; Scalar &gt; &gt; &amp;rangeSpace, const RCP&lt; const VectorSpaceBase&lt; Scalar &gt; &gt; &amp;domainSpace, const RCP&lt; Tpetra::Operator&lt; Scalar, LocalOrdinal, GlobalOrdinal, Node &gt; &gt; &amp;tpetraOperator)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>constInitialize</name>
      <anchorfile>classThyra_1_1TpetraLinearOp.html</anchorfile>
      <anchor>a892fe752e6280666ca4680553ad81d9c</anchor>
      <arglist>(const RCP&lt; const VectorSpaceBase&lt; Scalar &gt; &gt; &amp;rangeSpace, const RCP&lt; const VectorSpaceBase&lt; Scalar &gt; &gt; &amp;domainSpace, const RCP&lt; const Tpetra::Operator&lt; Scalar, LocalOrdinal, GlobalOrdinal, Node &gt; &gt; &amp;tpetraOperator)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; Tpetra::Operator&lt; Scalar, LocalOrdinal, GlobalOrdinal, Node &gt; &gt;</type>
      <name>getTpetraOperator</name>
      <anchorfile>classThyra_1_1TpetraLinearOp.html</anchorfile>
      <anchor>ace26c5027b67aec7c049f24345890f8e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const Tpetra::Operator&lt; Scalar, LocalOrdinal, GlobalOrdinal, Node &gt; &gt;</type>
      <name>getConstTpetraOperator</name>
      <anchorfile>classThyra_1_1TpetraLinearOp.html</anchorfile>
      <anchor>a5a91d2679354ca12374013d021f6b28c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const Thyra::VectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>range</name>
      <anchorfile>classThyra_1_1TpetraLinearOp.html</anchorfile>
      <anchor>ab1f2dddd0dfb8cedc8b9a9fcce7c4048</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const Thyra::VectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>domain</name>
      <anchorfile>classThyra_1_1TpetraLinearOp.html</anchorfile>
      <anchor>a16ae721524e45e7650a459506be670e5</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>bool</type>
      <name>opSupportedImpl</name>
      <anchorfile>classThyra_1_1TpetraLinearOp.html</anchorfile>
      <anchor>a1935820393bd710035190b2fd001e8b0</anchor>
      <arglist>(Thyra::EOpTransp M_trans) const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>applyImpl</name>
      <anchorfile>classThyra_1_1TpetraLinearOp.html</anchorfile>
      <anchor>a4ada5895e23ce94f812dfd56d1a93e66</anchor>
      <arglist>(const Thyra::EOpTransp M_trans, const Thyra::MultiVectorBase&lt; Scalar &gt; &amp;X_in, const Teuchos::Ptr&lt; Thyra::MultiVectorBase&lt; Scalar &gt; &gt; &amp;Y_inout, const Scalar alpha, const Scalar beta) const </arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual bool</type>
      <name>supportsScaleLeftImpl</name>
      <anchorfile>classThyra_1_1TpetraLinearOp.html</anchorfile>
      <anchor>a4d895db8ef8c01abbaf65cdae7b0e661</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual bool</type>
      <name>supportsScaleRightImpl</name>
      <anchorfile>classThyra_1_1TpetraLinearOp.html</anchorfile>
      <anchor>a50a3aa99529f26b8478f58dd79a2a2af</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual void</type>
      <name>scaleLeftImpl</name>
      <anchorfile>classThyra_1_1TpetraLinearOp.html</anchorfile>
      <anchor>a61d6c864ce22fdea78d10f7e84b8d524</anchor>
      <arglist>(const VectorBase&lt; Scalar &gt; &amp;row_scaling)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual void</type>
      <name>scaleRightImpl</name>
      <anchorfile>classThyra_1_1TpetraLinearOp.html</anchorfile>
      <anchor>a6b0d10f370efea4de2e81d6950c3307f</anchor>
      <arglist>(const VectorBase&lt; Scalar &gt; &amp;col_scaling)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual bool</type>
      <name>rowStatIsSupportedImpl</name>
      <anchorfile>classThyra_1_1TpetraLinearOp.html</anchorfile>
      <anchor>a3f9fa262a067a3d5881895b4a5ad424d</anchor>
      <arglist>(const RowStatLinearOpBaseUtils::ERowStat rowStat) const </arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual void</type>
      <name>getRowStatImpl</name>
      <anchorfile>classThyra_1_1TpetraLinearOp.html</anchorfile>
      <anchor>a59e644c21c4777f5990b155f38f45a5f</anchor>
      <arglist>(const RowStatLinearOpBaseUtils::ERowStat rowStat, const Ptr&lt; VectorBase&lt; Scalar &gt; &gt; &amp;rowStatVec) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::TpetraMultiVector</name>
    <filename>classThyra_1_1TpetraMultiVector.html</filename>
    <templarg></templarg>
    <templarg></templarg>
    <templarg></templarg>
    <templarg></templarg>
    <base virtualness="virtual">Thyra::SpmdMultiVectorDefaultBase</base>
    <member kind="function">
      <type>RCP&lt; TpetraMultiVector&lt; Scalar, LocalOrdinal, GlobalOrdinal, Node &gt; &gt;</type>
      <name>tpetraMultiVector</name>
      <anchorfile>classThyra_1_1TpetraMultiVector.html</anchorfile>
      <anchor>acc1dbbe544cf59420a7689e27b344289</anchor>
      <arglist>(const RCP&lt; const TpetraVectorSpace&lt; Scalar, LocalOrdinal, GlobalOrdinal, Node &gt; &gt; &amp;tpetraVectorSpace, const RCP&lt; const ScalarProdVectorSpaceBase&lt; Scalar &gt; &gt; &amp;domainSpace, const RCP&lt; Tpetra::MultiVector&lt; Scalar, LocalOrdinal, GlobalOrdinal, Node &gt; &gt; &amp;tpetraMultiVector)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const TpetraMultiVector&lt; Scalar, LocalOrdinal, GlobalOrdinal, Node &gt; &gt;</type>
      <name>constTpetraMultiVector</name>
      <anchorfile>classThyra_1_1TpetraMultiVector.html</anchorfile>
      <anchor>a26d561589ca28ebe420fd43193e3dd5a</anchor>
      <arglist>(const RCP&lt; const TpetraVectorSpace&lt; Scalar, LocalOrdinal, GlobalOrdinal, Node &gt; &gt; &amp;tpetraVectorSpace, const RCP&lt; const ScalarProdVectorSpaceBase&lt; Scalar &gt; &gt; &amp;domainSpace, const RCP&lt; const Tpetra::MultiVector&lt; Scalar, LocalOrdinal, GlobalOrdinal, Node &gt; &gt; &amp;tpetraMultiVector)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>TpetraMultiVector</name>
      <anchorfile>classThyra_1_1TpetraMultiVector.html</anchorfile>
      <anchor>a8f6a3dbe181f5dffccda4d2c4c8653bc</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initialize</name>
      <anchorfile>classThyra_1_1TpetraMultiVector.html</anchorfile>
      <anchor>a123b935ec67e32820db921f455b3ad19</anchor>
      <arglist>(const RCP&lt; const TpetraVectorSpace&lt; Scalar, LocalOrdinal, GlobalOrdinal, Node &gt; &gt; &amp;tpetraVectorSpace, const RCP&lt; const ScalarProdVectorSpaceBase&lt; Scalar &gt; &gt; &amp;domainSpace, const RCP&lt; Tpetra::MultiVector&lt; Scalar, LocalOrdinal, GlobalOrdinal, Node &gt; &gt; &amp;tpetraMultiVector)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>constInitialize</name>
      <anchorfile>classThyra_1_1TpetraMultiVector.html</anchorfile>
      <anchor>a7ea8b003ed9ba6aa692bc3b5108bb493</anchor>
      <arglist>(const RCP&lt; const TpetraVectorSpace&lt; Scalar, LocalOrdinal, GlobalOrdinal, Node &gt; &gt; &amp;tpetraVectorSpace, const RCP&lt; const ScalarProdVectorSpaceBase&lt; Scalar &gt; &gt; &amp;domainSpace, const RCP&lt; const Tpetra::MultiVector&lt; Scalar, LocalOrdinal, GlobalOrdinal, Node &gt; &gt; &amp;tpetraMultiVector)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; Tpetra::MultiVector&lt; Scalar, LocalOrdinal, GlobalOrdinal, Node &gt; &gt;</type>
      <name>getTpetraMultiVector</name>
      <anchorfile>classThyra_1_1TpetraMultiVector.html</anchorfile>
      <anchor>a0b0b89b77bdc67be446e43cfafeaf8e3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const Tpetra::MultiVector&lt; Scalar, LocalOrdinal, GlobalOrdinal, Node &gt; &gt;</type>
      <name>getConstTpetraMultiVector</name>
      <anchorfile>classThyra_1_1TpetraMultiVector.html</anchorfile>
      <anchor>a89644964e022045f985721600cf6b4d8</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const ScalarProdVectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>domainScalarProdVecSpc</name>
      <anchorfile>classThyra_1_1TpetraMultiVector.html</anchorfile>
      <anchor>a38ffc1b0cbaeae26618afb4db3ab78d7</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>assignImpl</name>
      <anchorfile>classThyra_1_1TpetraMultiVector.html</anchorfile>
      <anchor>ad4d1862a9959e8d20932041a406291e2</anchor>
      <arglist>(Scalar alpha)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>RCP&lt; const VectorBase&lt; Scalar &gt; &gt;</type>
      <name>colImpl</name>
      <anchorfile>classThyra_1_1TpetraMultiVector.html</anchorfile>
      <anchor>a32a69b1bafe52f6fb9c481722d6297a3</anchor>
      <arglist>(Ordinal j) const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>RCP&lt; VectorBase&lt; Scalar &gt; &gt;</type>
      <name>nonconstColImpl</name>
      <anchorfile>classThyra_1_1TpetraMultiVector.html</anchorfile>
      <anchor>a9a25ee8a71b6888fab04cd1341efda7c</anchor>
      <arglist>(Ordinal j)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>RCP&lt; const MultiVectorBase&lt; Scalar &gt; &gt;</type>
      <name>contigSubViewImpl</name>
      <anchorfile>classThyra_1_1TpetraMultiVector.html</anchorfile>
      <anchor>a6ce55accd81fe8ad28c8323f2b4cc558</anchor>
      <arglist>(const Range1D &amp;colRng) const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>RCP&lt; MultiVectorBase&lt; Scalar &gt; &gt;</type>
      <name>nonconstContigSubViewImpl</name>
      <anchorfile>classThyra_1_1TpetraMultiVector.html</anchorfile>
      <anchor>a7b953ccbc128f4726e1a861b116e439e</anchor>
      <arglist>(const Range1D &amp;colRng)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>RCP&lt; const SpmdVectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>spmdSpaceImpl</name>
      <anchorfile>classThyra_1_1TpetraMultiVector.html</anchorfile>
      <anchor>a65b5cf8e01be12cd859e2687943b82bd</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>getNonconstLocalMultiVectorDataImpl</name>
      <anchorfile>classThyra_1_1TpetraMultiVector.html</anchorfile>
      <anchor>abefd7e4c7c3feff2927281399ec9b042</anchor>
      <arglist>(const Ptr&lt; ArrayRCP&lt; Scalar &gt; &gt; &amp;localValues, const Ptr&lt; Ordinal &gt; &amp;leadingDim)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>getLocalMultiVectorDataImpl</name>
      <anchorfile>classThyra_1_1TpetraMultiVector.html</anchorfile>
      <anchor>aec6e7359cc8f4bf31d8547c8adfe1ffd</anchor>
      <arglist>(const Ptr&lt; ArrayRCP&lt; const Scalar &gt; &gt; &amp;localValues, const Ptr&lt; Ordinal &gt; &amp;leadingDim) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::TpetraOperatorVectorExtraction</name>
    <filename>classThyra_1_1TpetraOperatorVectorExtraction.html</filename>
    <templarg></templarg>
    <templarg></templarg>
    <templarg></templarg>
    <templarg></templarg>
    <member kind="function" static="yes">
      <type>static RCP&lt; Tpetra::Vector&lt; Scalar, LocalOrdinal, GlobalOrdinal, Node &gt; &gt;</type>
      <name>getTpetraVector</name>
      <anchorfile>classThyra_1_1TpetraOperatorVectorExtraction.html</anchorfile>
      <anchor>ab6e0ecd982e7b25b8490604be5d69cab</anchor>
      <arglist>(const RCP&lt; VectorBase&lt; Scalar &gt; &gt; &amp;v)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static RCP&lt; const Tpetra::Vector&lt; Scalar, LocalOrdinal, GlobalOrdinal, Node &gt; &gt;</type>
      <name>getConstTpetraVector</name>
      <anchorfile>classThyra_1_1TpetraOperatorVectorExtraction.html</anchorfile>
      <anchor>affba912dc3c60403044604fb28df94c1</anchor>
      <arglist>(const RCP&lt; const VectorBase&lt; Scalar &gt; &gt; &amp;v)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static RCP&lt; Tpetra::MultiVector&lt; Scalar, LocalOrdinal, GlobalOrdinal, Node &gt; &gt;</type>
      <name>getTpetraMultiVector</name>
      <anchorfile>classThyra_1_1TpetraOperatorVectorExtraction.html</anchorfile>
      <anchor>abe01c4b3a55f54aace3f418578d3998e</anchor>
      <arglist>(const RCP&lt; MultiVectorBase&lt; Scalar &gt; &gt; &amp;mv)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static RCP&lt; const Tpetra::MultiVector&lt; Scalar, LocalOrdinal, GlobalOrdinal, Node &gt; &gt;</type>
      <name>getConstTpetraMultiVector</name>
      <anchorfile>classThyra_1_1TpetraOperatorVectorExtraction.html</anchorfile>
      <anchor>aae895b63c21b10636b2149e0730e6019</anchor>
      <arglist>(const RCP&lt; const MultiVectorBase&lt; Scalar &gt; &gt; &amp;mv)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static RCP&lt; Tpetra::Operator&lt; Scalar, LocalOrdinal, GlobalOrdinal, Node &gt; &gt;</type>
      <name>getTpetraOperator</name>
      <anchorfile>classThyra_1_1TpetraOperatorVectorExtraction.html</anchorfile>
      <anchor>aa5ba4bec982d42dcf29fbd67803f565d</anchor>
      <arglist>(const RCP&lt; LinearOpBase&lt; Scalar &gt; &gt; &amp;op)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static RCP&lt; const Tpetra::Operator&lt; Scalar, LocalOrdinal, GlobalOrdinal, Node &gt; &gt;</type>
      <name>getConstTpetraOperator</name>
      <anchorfile>classThyra_1_1TpetraOperatorVectorExtraction.html</anchorfile>
      <anchor>a4f5bb3b79a2ceb0dbd284c5c082e23aa</anchor>
      <arglist>(const RCP&lt; const LinearOpBase&lt; Scalar &gt; &gt; &amp;op)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::TpetraVector</name>
    <filename>classThyra_1_1TpetraVector.html</filename>
    <templarg></templarg>
    <templarg></templarg>
    <templarg></templarg>
    <templarg></templarg>
    <base virtualness="virtual">Thyra::SpmdVectorDefaultBase</base>
    <member kind="function">
      <type>RCP&lt; TpetraVector&lt; Scalar, LocalOrdinal, GlobalOrdinal, Node &gt; &gt;</type>
      <name>tpetraVector</name>
      <anchorfile>classThyra_1_1TpetraVector.html</anchorfile>
      <anchor>ac6b03b8ba8ca63698131d92a402d0f62</anchor>
      <arglist>(const RCP&lt; const TpetraVectorSpace&lt; Scalar, LocalOrdinal, GlobalOrdinal, Node &gt; &gt; &amp;tpetraVectorSpace, const RCP&lt; Tpetra::Vector&lt; Scalar, LocalOrdinal, GlobalOrdinal, Node &gt; &gt; &amp;tpetraVector)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const TpetraVector&lt; Scalar, LocalOrdinal, GlobalOrdinal, Node &gt; &gt;</type>
      <name>constTpetraVector</name>
      <anchorfile>classThyra_1_1TpetraVector.html</anchorfile>
      <anchor>a855b4e9a5fcb6edfbf3bc5b3303d6c27</anchor>
      <arglist>(const RCP&lt; const TpetraVectorSpace&lt; Scalar, LocalOrdinal, GlobalOrdinal, Node &gt; &gt; &amp;tpetraVectorSpace, const RCP&lt; const Tpetra::Vector&lt; Scalar, LocalOrdinal, GlobalOrdinal, Node &gt; &gt; &amp;tpetraVector)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>TpetraVector</name>
      <anchorfile>classThyra_1_1TpetraVector.html</anchorfile>
      <anchor>a764eab813d940d2038956341a9d52ac4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initialize</name>
      <anchorfile>classThyra_1_1TpetraVector.html</anchorfile>
      <anchor>af30b970b46be7cb2579a649a182ac6e8</anchor>
      <arglist>(const RCP&lt; const TpetraVectorSpace&lt; Scalar, LocalOrdinal, GlobalOrdinal, Node &gt; &gt; &amp;tpetraVectorSpace, const RCP&lt; Tpetra::Vector&lt; Scalar, LocalOrdinal, GlobalOrdinal, Node &gt; &gt; &amp;tpetraVector)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>constInitialize</name>
      <anchorfile>classThyra_1_1TpetraVector.html</anchorfile>
      <anchor>a8172d0fbfabde2425ad678a74c06b439</anchor>
      <arglist>(const RCP&lt; const TpetraVectorSpace&lt; Scalar, LocalOrdinal, GlobalOrdinal, Node &gt; &gt; &amp;tpetraVectorSpace, const RCP&lt; const Tpetra::Vector&lt; Scalar, LocalOrdinal, GlobalOrdinal, Node &gt; &gt; &amp;tpetraVector)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; Tpetra::Vector&lt; Scalar, LocalOrdinal, GlobalOrdinal, Node &gt; &gt;</type>
      <name>getTpetraVector</name>
      <anchorfile>classThyra_1_1TpetraVector.html</anchorfile>
      <anchor>a174589981aed7aa2f0e1161277c80a24</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const Tpetra::Vector&lt; Scalar, LocalOrdinal, GlobalOrdinal, Node &gt; &gt;</type>
      <name>getConstTpetraVector</name>
      <anchorfile>classThyra_1_1TpetraVector.html</anchorfile>
      <anchor>a744da15c0c5ae18acf0d7714abff7503</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const SpmdVectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>spmdSpaceImpl</name>
      <anchorfile>classThyra_1_1TpetraVector.html</anchorfile>
      <anchor>a6d60e2ec509860295364daeee9c15c50</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>getNonconstLocalVectorDataImpl</name>
      <anchorfile>classThyra_1_1TpetraVector.html</anchorfile>
      <anchor>a710d847433b084d2a03fe6bf98e5ad90</anchor>
      <arglist>(const Ptr&lt; ArrayRCP&lt; Scalar &gt; &gt; &amp;localValues)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>getLocalVectorDataImpl</name>
      <anchorfile>classThyra_1_1TpetraVector.html</anchorfile>
      <anchor>a7a7c559edcbc23a7778026016f3700e6</anchor>
      <arglist>(const Ptr&lt; ArrayRCP&lt; const Scalar &gt; &gt; &amp;localValues) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::TpetraVectorSpace</name>
    <filename>classThyra_1_1TpetraVectorSpace.html</filename>
    <templarg></templarg>
    <templarg></templarg>
    <templarg></templarg>
    <templarg></templarg>
    <base>Thyra::SpmdVectorSpaceDefaultBase</base>
    <member kind="typedef">
      <type>TpetraVectorSpace&lt; Scalar, LocalOrdinal, GlobalOrdinal, Node &gt;</type>
      <name>this_t</name>
      <anchorfile>classThyra_1_1TpetraVectorSpace.html</anchorfile>
      <anchor>a17fb03c06e07550fca257dcc32c9f1ea</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; TpetraVectorSpace&lt; Scalar, LocalOrdinal, GlobalOrdinal, Node &gt; &gt;</type>
      <name>tpetraVectorSpace</name>
      <anchorfile>classThyra_1_1TpetraVectorSpace.html</anchorfile>
      <anchor>a555af9938c09f97f6499d95adf372c46</anchor>
      <arglist>(const RCP&lt; const Tpetra::Map&lt; LocalOrdinal, GlobalOrdinal, Node &gt; &gt; &amp;tpetraMap)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static RCP&lt; TpetraVectorSpace&lt; Scalar, LocalOrdinal, GlobalOrdinal, Node &gt; &gt;</type>
      <name>create</name>
      <anchorfile>classThyra_1_1TpetraVectorSpace.html</anchorfile>
      <anchor>af3f524498645e7a5ba1ca068cd5ba0b1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initialize</name>
      <anchorfile>classThyra_1_1TpetraVectorSpace.html</anchorfile>
      <anchor>a78c2c9c969140b04b0ac428dedbd6174</anchor>
      <arglist>(const RCP&lt; const Tpetra::Map&lt; LocalOrdinal, GlobalOrdinal, Node &gt; &gt; &amp;tpetraMap)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>hasInCoreView</name>
      <anchorfile>classThyra_1_1TpetraVectorSpace.html</anchorfile>
      <anchor>ac111cee7f1e0af1248b6148d80cce6ef</anchor>
      <arglist>(const Range1D &amp;rng, const EViewType viewType, const EStrideType strideType) const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const VectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>clone</name>
      <anchorfile>classThyra_1_1TpetraVectorSpace.html</anchorfile>
      <anchor>a13ba2cc17da465a52052c786d584e629</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>RCP&lt; VectorBase&lt; Scalar &gt; &gt;</type>
      <name>createMember</name>
      <anchorfile>classThyra_1_1TpetraVectorSpace.html</anchorfile>
      <anchor>a25294315dbc68189a2b2a790cec12f4b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>RCP&lt; MultiVectorBase&lt; Scalar &gt; &gt;</type>
      <name>createMembers</name>
      <anchorfile>classThyra_1_1TpetraVectorSpace.html</anchorfile>
      <anchor>ac943d97f51812b10c39507dbf3973a8c</anchor>
      <arglist>(int numMembers) const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>scalarProdsImpl</name>
      <anchorfile>classThyra_1_1TpetraVectorSpace.html</anchorfile>
      <anchor>ad7c3dc6df67fa064c2b3d6e64e6027d4</anchor>
      <arglist>(const MultiVectorBase&lt; Scalar &gt; &amp;X, const MultiVectorBase&lt; Scalar &gt; &amp;Y, const ArrayView&lt; Scalar &gt; &amp;scalarProds_out) const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const Teuchos::Comm&lt; Ordinal &gt; &gt;</type>
      <name>getComm</name>
      <anchorfile>classThyra_1_1TpetraVectorSpace.html</anchorfile>
      <anchor>a44b6917af59c6e170b1354efc3733c36</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Ordinal</type>
      <name>localSubDim</name>
      <anchorfile>classThyra_1_1TpetraVectorSpace.html</anchorfile>
      <anchor>ac38b7a495fdef5fd66c7a0877e2e316f</anchor>
      <arglist>() const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::Exceptions::UnInitialized</name>
    <filename>classThyra_1_1Exceptions_1_1UnInitialized.html</filename>
  </compound>
  <compound kind="class">
    <name>Thyra::UniversalMultiVectorRandomizer</name>
    <filename>classThyra_1_1UniversalMultiVectorRandomizer.html</filename>
    <templarg></templarg>
    <base>Thyra::MultiVectorRandomizerBase</base>
    <member kind="function">
      <type>RCP&lt; UniversalMultiVectorRandomizer&lt; Scalar &gt; &gt;</type>
      <name>universalMultiVectorRandomizer</name>
      <anchorfile>classThyra_1_1UniversalMultiVectorRandomizer.html</anchorfile>
      <anchor>a5e98bb2ff37bea87b865690177c1b9dc</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isCompatible</name>
      <anchorfile>classThyra_1_1UniversalMultiVectorRandomizer.html</anchorfile>
      <anchor>ac4c5b38334004d42713501d93cc5d658</anchor>
      <arglist>(const VectorSpaceBase&lt; Scalar &gt; &amp;space) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::VectorBase</name>
    <filename>classThyra_1_1VectorBase.html</filename>
    <templarg>Scalar</templarg>
    <base virtualness="virtual">Thyra::MultiVectorBase</base>
    <member kind="function">
      <type>void</type>
      <name>applyOp</name>
      <anchorfile>classThyra_1_1VectorBase.html</anchorfile>
      <anchor>a3d90ff0ece8c277f5b65562086b8c0ba</anchor>
      <arglist>(const RTOpPack::RTOpT&lt; Scalar &gt; &amp;op, const ArrayView&lt; const Ptr&lt; const VectorBase&lt; Scalar &gt; &gt; &gt; &amp;vecs, const ArrayView&lt; const Ptr&lt; VectorBase&lt; Scalar &gt; &gt; &gt; &amp;targ_vecs, const Ptr&lt; RTOpPack::ReductTarget &gt; &amp;reduct_obj, const Ordinal global_offset=0)</arglist>
    </member>
    <member kind="function">
      <type>Scalar</type>
      <name>sum</name>
      <anchorfile>classThyra_1_1VectorBase.html</anchorfile>
      <anchor>a1f4af4ce76be95b31610141a9517bd36</anchor>
      <arglist>(const VectorBase&lt; Scalar &gt; &amp;v)</arglist>
    </member>
    <member kind="function">
      <type>Scalar</type>
      <name>scalarProd</name>
      <anchorfile>classThyra_1_1VectorBase.html</anchorfile>
      <anchor>ac6acc49dcec205ff4a166e1809bbd29c</anchor>
      <arglist>(const VectorBase&lt; Scalar &gt; &amp;x, const VectorBase&lt; Scalar &gt; &amp;y)</arglist>
    </member>
    <member kind="function">
      <type>Scalar</type>
      <name>inner</name>
      <anchorfile>classThyra_1_1VectorBase.html</anchorfile>
      <anchor>a5f69037a4fb6a85bce07b9be8f1850e5</anchor>
      <arglist>(const VectorBase&lt; Scalar &gt; &amp;x, const VectorBase&lt; Scalar &gt; &amp;y)</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::ScalarTraits&lt; Scalar &gt;::magnitudeType</type>
      <name>norm</name>
      <anchorfile>classThyra_1_1VectorBase.html</anchorfile>
      <anchor>a641d7338f690b4cabd6961622a07e288</anchor>
      <arglist>(const VectorBase&lt; Scalar &gt; &amp;v)</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::ScalarTraits&lt; Scalar &gt;::magnitudeType</type>
      <name>norm_1</name>
      <anchorfile>classThyra_1_1VectorBase.html</anchorfile>
      <anchor>a9b8a20b964320c8a0675e815fcea3306</anchor>
      <arglist>(const VectorBase&lt; Scalar &gt; &amp;v)</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::ScalarTraits&lt; Scalar &gt;::magnitudeType</type>
      <name>norm_2</name>
      <anchorfile>classThyra_1_1VectorBase.html</anchorfile>
      <anchor>a7beceea842abbf478222f7d8685208a0</anchor>
      <arglist>(const VectorBase&lt; Scalar &gt; &amp;v)</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::ScalarTraits&lt; Scalar &gt;::magnitudeType</type>
      <name>norm_2</name>
      <anchorfile>classThyra_1_1VectorBase.html</anchorfile>
      <anchor>a9a163eae1a9b1df6ebb4ba57aa4fcc7b</anchor>
      <arglist>(const VectorBase&lt; Scalar &gt; &amp;w, const VectorBase&lt; Scalar &gt; &amp;v)</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::ScalarTraits&lt; Scalar &gt;::magnitudeType</type>
      <name>norm_inf</name>
      <anchorfile>classThyra_1_1VectorBase.html</anchorfile>
      <anchor>af9dbd70890ac1878e318f1308cb4ecde</anchor>
      <arglist>(const VectorBase&lt; Scalar &gt; &amp;v_rhs)</arglist>
    </member>
    <member kind="function">
      <type>Scalar</type>
      <name>dot</name>
      <anchorfile>classThyra_1_1VectorBase.html</anchorfile>
      <anchor>a010dd7ce57afce44835805db40efe222</anchor>
      <arglist>(const VectorBase&lt; Scalar &gt; &amp;x, const VectorBase&lt; Scalar &gt; &amp;y)</arglist>
    </member>
    <member kind="function">
      <type>Scalar</type>
      <name>get_ele</name>
      <anchorfile>classThyra_1_1VectorBase.html</anchorfile>
      <anchor>ab65926d75299c3381a022c4982613b1d</anchor>
      <arglist>(const VectorBase&lt; Scalar &gt; &amp;v, Ordinal i)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_ele</name>
      <anchorfile>classThyra_1_1VectorBase.html</anchorfile>
      <anchor>aa5d8a033837606e6a13f3341ae714d81</anchor>
      <arglist>(Ordinal i, Scalar alpha, const Ptr&lt; VectorBase&lt; Scalar &gt; &gt; &amp;v)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>put_scalar</name>
      <anchorfile>classThyra_1_1VectorBase.html</anchorfile>
      <anchor>ac11006b034c7d9f8396b2181600b6f24</anchor>
      <arglist>(const Scalar &amp;alpha, const Ptr&lt; VectorBase&lt; Scalar &gt; &gt; &amp;y)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>copy</name>
      <anchorfile>classThyra_1_1VectorBase.html</anchorfile>
      <anchor>ae4a6fbc498958acf97e118e1d8233f6a</anchor>
      <arglist>(const VectorBase&lt; Scalar &gt; &amp;x, const Ptr&lt; VectorBase&lt; Scalar &gt; &gt; &amp;y)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>add_scalar</name>
      <anchorfile>classThyra_1_1VectorBase.html</anchorfile>
      <anchor>a61a40064c5f17b9f18d47b8a5e9de2f0</anchor>
      <arglist>(const Scalar &amp;alpha, const Ptr&lt; VectorBase&lt; Scalar &gt; &gt; &amp;y)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>scale</name>
      <anchorfile>classThyra_1_1VectorBase.html</anchorfile>
      <anchor>a8cf78f85dc45033d77c552a93981bee1</anchor>
      <arglist>(const Scalar &amp;alpha, const Ptr&lt; VectorBase&lt; Scalar &gt; &gt; &amp;y)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>abs</name>
      <anchorfile>classThyra_1_1VectorBase.html</anchorfile>
      <anchor>ac06f405e45f20ca1024000afc9aef28a</anchor>
      <arglist>(const VectorBase&lt; Scalar &gt; &amp;x, const Ptr&lt; VectorBase&lt; Scalar &gt; &gt; &amp;y)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>reciprocal</name>
      <anchorfile>classThyra_1_1VectorBase.html</anchorfile>
      <anchor>a5c11386afac3e868653ebb0d94b179a5</anchor>
      <arglist>(const VectorBase&lt; Scalar &gt; &amp;x, const Ptr&lt; VectorBase&lt; Scalar &gt; &gt; &amp;y)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>ele_wise_prod</name>
      <anchorfile>classThyra_1_1VectorBase.html</anchorfile>
      <anchor>ada608d98d080d06b69173d0bf59cecc9</anchor>
      <arglist>(const Scalar &amp;alpha, const VectorBase&lt; Scalar &gt; &amp;x, const VectorBase&lt; Scalar &gt; &amp;v, const Ptr&lt; VectorBase&lt; Scalar &gt; &gt; &amp;y)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>ele_wise_conj_prod</name>
      <anchorfile>classThyra_1_1VectorBase.html</anchorfile>
      <anchor>a5ee067d8395a6767598de0784da364d6</anchor>
      <arglist>(const Scalar &amp;alpha, const VectorBase&lt; Scalar &gt; &amp;x, const VectorBase&lt; Scalar &gt; &amp;v, const Ptr&lt; VectorBase&lt; Scalar &gt; &gt; &amp;y)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>ele_wise_scale</name>
      <anchorfile>classThyra_1_1VectorBase.html</anchorfile>
      <anchor>ae29109317a826bd9072d3e6e0a23a10f</anchor>
      <arglist>(const VectorBase&lt; Scalar &gt; &amp;x, const Ptr&lt; VectorBase&lt; Scalar &gt; &gt; &amp;y)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Vp_StVtV</name>
      <anchorfile>classThyra_1_1VectorBase.html</anchorfile>
      <anchor>a9224a5caba00e2bdbf3a1ea295090a96</anchor>
      <arglist>(const Ptr&lt; VectorBase&lt; Scalar &gt; &gt; &amp;y, const Scalar &amp;alpha, const VectorBase&lt; Scalar &gt; &amp;x, const VectorBase&lt; Scalar &gt; &amp;v)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>ele_wise_prod_update</name>
      <anchorfile>classThyra_1_1VectorBase.html</anchorfile>
      <anchor>ad22148a16c7b43e7b93b55110b7e67ea</anchor>
      <arglist>(const Scalar &amp;alpha, const VectorBase&lt; Scalar &gt; &amp;x, const Ptr&lt; VectorBase&lt; Scalar &gt; &gt; &amp;y)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Vt_StV</name>
      <anchorfile>classThyra_1_1VectorBase.html</anchorfile>
      <anchor>ab391b90565a0a3db5658cc8e54abd90d</anchor>
      <arglist>(const Ptr&lt; VectorBase&lt; Scalar &gt; &gt; &amp;y, const Scalar &amp;alpha, const VectorBase&lt; Scalar &gt; &amp;x)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>ele_wise_divide</name>
      <anchorfile>classThyra_1_1VectorBase.html</anchorfile>
      <anchor>aa443516815dbc13b69731b35564f4fe1</anchor>
      <arglist>(const Scalar &amp;alpha, const VectorBase&lt; Scalar &gt; &amp;x, const VectorBase&lt; Scalar &gt; &amp;v, const Ptr&lt; VectorBase&lt; Scalar &gt; &gt; &amp;y)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>linear_combination</name>
      <anchorfile>classThyra_1_1VectorBase.html</anchorfile>
      <anchor>a0fde2645b235f7f7043e9e0a48d0e008</anchor>
      <arglist>(const ArrayView&lt; const Scalar &gt; &amp;alpha, const ArrayView&lt; const Ptr&lt; const VectorBase&lt; Scalar &gt; &gt; &gt; &amp;x, const Scalar &amp;beta, const Ptr&lt; VectorBase&lt; Scalar &gt; &gt; &amp;y)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>seed_randomize</name>
      <anchorfile>classThyra_1_1VectorBase.html</anchorfile>
      <anchor>a35638d515f7a5e937eb64221237c896e</anchor>
      <arglist>(unsigned int s)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>randomize</name>
      <anchorfile>classThyra_1_1VectorBase.html</anchorfile>
      <anchor>a92cc0b48f56715cae7347c728d7e597d</anchor>
      <arglist>(Scalar l, Scalar u, const Ptr&lt; VectorBase&lt; Scalar &gt; &gt; &amp;v)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>assign</name>
      <anchorfile>classThyra_1_1VectorBase.html</anchorfile>
      <anchor>af5ba5adc201b2302fd829a3976d37922</anchor>
      <arglist>(const Ptr&lt; VectorBase&lt; Scalar &gt; &gt; &amp;y, const Scalar &amp;alpha)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>assign</name>
      <anchorfile>classThyra_1_1VectorBase.html</anchorfile>
      <anchor>a83e1f999d9e9245e45a716e13e2ede19</anchor>
      <arglist>(const Ptr&lt; VectorBase&lt; Scalar &gt; &gt; &amp;y, const VectorBase&lt; Scalar &gt; &amp;x)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Vp_S</name>
      <anchorfile>classThyra_1_1VectorBase.html</anchorfile>
      <anchor>a5412d5d9abe16ff358c463cb08d36c8d</anchor>
      <arglist>(const Ptr&lt; VectorBase&lt; Scalar &gt; &gt; &amp;y, const Scalar &amp;alpha)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Vt_S</name>
      <anchorfile>classThyra_1_1VectorBase.html</anchorfile>
      <anchor>a5c7c9108535b24433268dfcc7a30558b</anchor>
      <arglist>(const Ptr&lt; VectorBase&lt; Scalar &gt; &gt; &amp;y, const Scalar &amp;alpha)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>V_StV</name>
      <anchorfile>classThyra_1_1VectorBase.html</anchorfile>
      <anchor>a55456a30ff2407c1834cb9b270e96eee</anchor>
      <arglist>(const Ptr&lt; VectorBase&lt; Scalar &gt; &gt; &amp;y, const Scalar &amp;alpha, const VectorBase&lt; Scalar &gt; &amp;x)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Vp_StV</name>
      <anchorfile>classThyra_1_1VectorBase.html</anchorfile>
      <anchor>a2020ba774954544ec9422e831cbb8cc4</anchor>
      <arglist>(const Ptr&lt; VectorBase&lt; Scalar &gt; &gt; &amp;y, const Scalar &amp;alpha, const VectorBase&lt; Scalar &gt; &amp;x)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Vp_V</name>
      <anchorfile>classThyra_1_1VectorBase.html</anchorfile>
      <anchor>abdad101dcac56f76b2f9b866fe20adce</anchor>
      <arglist>(const Ptr&lt; VectorBase&lt; Scalar &gt; &gt; &amp;y, const VectorBase&lt; Scalar &gt; &amp;x, const Scalar &amp;beta=static_cast&lt; Scalar &gt;(1.0))</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>V_V</name>
      <anchorfile>classThyra_1_1VectorBase.html</anchorfile>
      <anchor>af04f4157f3e9d2575101e22c909278bb</anchor>
      <arglist>(const Ptr&lt; VectorBase&lt; Scalar &gt; &gt; &amp;y, const VectorBase&lt; Scalar &gt; &amp;x)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>V_S</name>
      <anchorfile>classThyra_1_1VectorBase.html</anchorfile>
      <anchor>a6eae8d5302a76d3cc59fc99870261742</anchor>
      <arglist>(const Ptr&lt; VectorBase&lt; Scalar &gt; &gt; &amp;y, const Scalar &amp;alpha)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>V_VpV</name>
      <anchorfile>classThyra_1_1VectorBase.html</anchorfile>
      <anchor>a6f13e17a621ec8d7178c58ded921d632</anchor>
      <arglist>(const Ptr&lt; VectorBase&lt; Scalar &gt; &gt; &amp;z, const VectorBase&lt; Scalar &gt; &amp;x, const VectorBase&lt; Scalar &gt; &amp;y)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>V_VmV</name>
      <anchorfile>classThyra_1_1VectorBase.html</anchorfile>
      <anchor>ad632fcd28fd8876c419b795c0dcc6e2f</anchor>
      <arglist>(const Ptr&lt; VectorBase&lt; Scalar &gt; &gt; &amp;z, const VectorBase&lt; Scalar &gt; &amp;x, const VectorBase&lt; Scalar &gt; &amp;y)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>V_StVpV</name>
      <anchorfile>classThyra_1_1VectorBase.html</anchorfile>
      <anchor>a0a32647155a085e5b85a7ecd36e96810</anchor>
      <arglist>(const Ptr&lt; VectorBase&lt; Scalar &gt; &gt; &amp;z, const Scalar &amp;alpha, const VectorBase&lt; Scalar &gt; &amp;x, const VectorBase&lt; Scalar &gt; &amp;y)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>V_VpStV</name>
      <anchorfile>classThyra_1_1VectorBase.html</anchorfile>
      <anchor>a43c10c8ab0e7059431f9a29826ffde51</anchor>
      <arglist>(const Ptr&lt; VectorBase&lt; Scalar &gt; &gt; &amp;z, const VectorBase&lt; Scalar &gt; &amp;x, const Scalar &amp;alpha, const VectorBase&lt; Scalar &gt; &amp;y)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>V_StVpStV</name>
      <anchorfile>classThyra_1_1VectorBase.html</anchorfile>
      <anchor>acee3b513abf83d6ca658b71b1f35a0a2</anchor>
      <arglist>(const Ptr&lt; VectorBase&lt; Scalar &gt; &gt; &amp;z, const Scalar &amp;alpha, const VectorBase&lt; Scalar &gt; &amp;x, const Scalar &amp;beta, const VectorBase&lt; Scalar &gt; &amp;y)</arglist>
    </member>
    <member kind="function">
      <type>Scalar</type>
      <name>min</name>
      <anchorfile>classThyra_1_1VectorBase.html</anchorfile>
      <anchor>a73685789ad72a21f7699891303eaf79a</anchor>
      <arglist>(const VectorBase&lt; Scalar &gt; &amp;x)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>min</name>
      <anchorfile>classThyra_1_1VectorBase.html</anchorfile>
      <anchor>a250ee66083b556e07bf3525ba11bb3d4</anchor>
      <arglist>(const VectorBase&lt; Scalar &gt; &amp;x, const Ptr&lt; Scalar &gt; &amp;maxEle, const Ptr&lt; Ordinal &gt; &amp;maxIndex)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>minGreaterThanBound</name>
      <anchorfile>classThyra_1_1VectorBase.html</anchorfile>
      <anchor>aaf7c0275d00da7b3a95765909fa808cf</anchor>
      <arglist>(const VectorBase&lt; Scalar &gt; &amp;x, const Scalar &amp;bound, const Ptr&lt; Scalar &gt; &amp;minEle, const Ptr&lt; Ordinal &gt; &amp;minIndex)</arglist>
    </member>
    <member kind="function">
      <type>Scalar</type>
      <name>max</name>
      <anchorfile>classThyra_1_1VectorBase.html</anchorfile>
      <anchor>a95a494b04f219c1869f546ae4aff0791</anchor>
      <arglist>(const VectorBase&lt; Scalar &gt; &amp;x)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>max</name>
      <anchorfile>classThyra_1_1VectorBase.html</anchorfile>
      <anchor>ac6c9d8f36582395913a4be3474d615ac</anchor>
      <arglist>(const VectorBase&lt; Scalar &gt; &amp;x, const Ptr&lt; Scalar &gt; &amp;maxEle, const Ptr&lt; Ordinal &gt; &amp;maxIndex)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>maxLessThanBound</name>
      <anchorfile>classThyra_1_1VectorBase.html</anchorfile>
      <anchor>a0868c972a8a33396069d6dacb21cd511</anchor>
      <arglist>(const VectorBase&lt; Scalar &gt; &amp;x, const Scalar &amp;bound, const Ptr&lt; Scalar &gt; &amp;maxEle, const Ptr&lt; Ordinal &gt; &amp;maxIndex)</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual RCP&lt; const VectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>space</name>
      <anchorfile>classThyra_1_1VectorBase.html</anchorfile>
      <anchor>afce77ff74a310b72be5eb7295ccb7dde</anchor>
      <arglist>() const  =0</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>applyOp</name>
      <anchorfile>classThyra_1_1VectorBase.html</anchorfile>
      <anchor>a39e31528482653eec0d9ed3b10b850e1</anchor>
      <arglist>(const RTOpPack::RTOpT&lt; Scalar &gt; &amp;op, const ArrayView&lt; const Ptr&lt; const VectorBase&lt; Scalar &gt; &gt; &gt; &amp;vecs, const ArrayView&lt; const Ptr&lt; VectorBase&lt; Scalar &gt; &gt; &gt; &amp;targ_vecs, const Ptr&lt; RTOpPack::ReductTarget &gt; &amp;reduct_obj, const Ordinal global_offset) const </arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual RCP&lt; VectorBase&lt; Scalar &gt; &gt;</type>
      <name>clone_v</name>
      <anchorfile>classThyra_1_1VectorBase.html</anchorfile>
      <anchor>aba6103175e8a341ba540146c95cb3626</anchor>
      <arglist>() const  =0</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>acquireDetachedView</name>
      <anchorfile>classThyra_1_1VectorBase.html</anchorfile>
      <anchor>abe2b678ba61b47476ee7c6c03572aee7</anchor>
      <arglist>(const Range1D &amp;rng, RTOpPack::ConstSubVectorView&lt; Scalar &gt; *sub_vec) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>releaseDetachedView</name>
      <anchorfile>classThyra_1_1VectorBase.html</anchorfile>
      <anchor>ac1e5a9c403ce851ed0758daa36071461</anchor>
      <arglist>(RTOpPack::ConstSubVectorView&lt; Scalar &gt; *sub_vec) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>acquireDetachedView</name>
      <anchorfile>classThyra_1_1VectorBase.html</anchorfile>
      <anchor>a3278af0accac807b5673bcb6471e9817</anchor>
      <arglist>(const Range1D &amp;rng, RTOpPack::SubVectorView&lt; Scalar &gt; *sub_vec)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>commitDetachedView</name>
      <anchorfile>classThyra_1_1VectorBase.html</anchorfile>
      <anchor>a844ccd43c1b2718a8b160be4bf6645a2</anchor>
      <arglist>(RTOpPack::SubVectorView&lt; Scalar &gt; *sub_vec)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setSubVector</name>
      <anchorfile>classThyra_1_1VectorBase.html</anchorfile>
      <anchor>a78172d8adcc77967ff528b4d83516a43</anchor>
      <arglist>(const RTOpPack::SparseSubVectorT&lt; Scalar &gt; &amp;sub_vec)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual void</type>
      <name>applyOpImpl</name>
      <anchorfile>classThyra_1_1VectorBase.html</anchorfile>
      <anchor>a096712d68bd9feba5210415e8e17b7a7</anchor>
      <arglist>(const RTOpPack::RTOpT&lt; Scalar &gt; &amp;op, const ArrayView&lt; const Ptr&lt; const VectorBase&lt; Scalar &gt; &gt; &gt; &amp;vecs, const ArrayView&lt; const Ptr&lt; VectorBase&lt; Scalar &gt; &gt; &gt; &amp;targ_vecs, const Ptr&lt; RTOpPack::ReductTarget &gt; &amp;reduct_obj, const Ordinal global_offset) const  =0</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual void</type>
      <name>acquireDetachedVectorViewImpl</name>
      <anchorfile>classThyra_1_1VectorBase.html</anchorfile>
      <anchor>aeb9653ae3d4950f187ac8e68adda77b9</anchor>
      <arglist>(const Range1D &amp;rng, RTOpPack::ConstSubVectorView&lt; Scalar &gt; *sub_vec) const  =0</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual void</type>
      <name>releaseDetachedVectorViewImpl</name>
      <anchorfile>classThyra_1_1VectorBase.html</anchorfile>
      <anchor>aa68d90f99cf78370e89f2bc87371df49</anchor>
      <arglist>(RTOpPack::ConstSubVectorView&lt; Scalar &gt; *sub_vec) const  =0</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual void</type>
      <name>acquireNonconstDetachedVectorViewImpl</name>
      <anchorfile>classThyra_1_1VectorBase.html</anchorfile>
      <anchor>a544d225f423b91a6de3a0f9189299b4b</anchor>
      <arglist>(const Range1D &amp;rng, RTOpPack::SubVectorView&lt; Scalar &gt; *sub_vec)=0</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual void</type>
      <name>commitNonconstDetachedVectorViewImpl</name>
      <anchorfile>classThyra_1_1VectorBase.html</anchorfile>
      <anchor>a17d56f276dd7dc2fd87f4b00d8d60dda</anchor>
      <arglist>(RTOpPack::SubVectorView&lt; Scalar &gt; *sub_vec)=0</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual void</type>
      <name>setSubVectorImpl</name>
      <anchorfile>classThyra_1_1VectorBase.html</anchorfile>
      <anchor>a9acf0d7e5dc1ecd7b6686c9083a1e19b</anchor>
      <arglist>(const RTOpPack::SparseSubVectorT&lt; Scalar &gt; &amp;sub_vec)=0</arglist>
    </member>
    <docanchor file="classThyra_1_1VectorBase" title="Outline">Thyra_VB_outline_sec</docanchor>
    <docanchor file="classThyra_1_1VectorBase" title="Reduction/transformation operator (RTOp) support">Thyra_VB_rtop_sec</docanchor>
    <docanchor file="classThyra_1_1VectorBase" title="Collection of pre-written RTOps and wrapper functions">Thyra_VB_rtop_collection_sec</docanchor>
    <docanchor file="classThyra_1_1VectorBase" title="Explicit vector coefficient access">Thyra_VB_expl_access_sec</docanchor>
    <docanchor file="classThyra_1_1VectorBase" title="Explicit vector coefficient access utilities">Thyra_VB_expl_access_utils_sec</docanchor>
    <docanchor file="classThyra_1_1VectorBase" title="Explicit vector coefficient assignment">Thyra_VB_expl_access_assign_sec</docanchor>
    <docanchor file="classThyra_1_1VectorBase" title="Vector is a MultiVectorBase is a LinearOpBase">Thyra_VB_is_lin_op_sec</docanchor>
    <docanchor file="classThyra_1_1VectorBase" title="Notes for subclass developers">Thyra_VB_dev_notes_sec</docanchor>
  </compound>
  <compound kind="class">
    <name>Thyra::VectorDefaultBase</name>
    <filename>classThyra_1_1VectorDefaultBase.html</filename>
    <templarg></templarg>
    <base virtualness="virtual">Thyra::VectorBase</base>
    <base protection="protected" virtualness="virtual">Thyra::MultiVectorDefaultBase</base>
    <member kind="function" virtualness="virtual">
      <type>virtual std::string</type>
      <name>description</name>
      <anchorfile>classThyra_1_1VectorDefaultBase.html</anchorfile>
      <anchor>a34f728118e28c6918b298d9522d7d2b6</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>describe</name>
      <anchorfile>classThyra_1_1VectorDefaultBase.html</anchorfile>
      <anchor>acf42dbb0b28f77734430bece82d9dca3</anchor>
      <arglist>(Teuchos::FancyOStream &amp;out, const Teuchos::EVerbosityLevel verbLevel) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual RCP&lt; const VectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>range</name>
      <anchorfile>classThyra_1_1VectorDefaultBase.html</anchorfile>
      <anchor>aacfad834276c35f8d34e04912cf17d57</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual RCP&lt; const VectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>domain</name>
      <anchorfile>classThyra_1_1VectorDefaultBase.html</anchorfile>
      <anchor>ad94362edd36ebd47d4a0af921985345e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; MultiVectorBase&lt; Scalar &gt; &gt;</type>
      <name>clone_mv</name>
      <anchorfile>classThyra_1_1VectorDefaultBase.html</anchorfile>
      <anchor>ab0dea4814af15f924b0c8f88564a4ca9</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; VectorBase&lt; Scalar &gt; &gt;</type>
      <name>clone_v</name>
      <anchorfile>classThyra_1_1VectorDefaultBase.html</anchorfile>
      <anchor>a27f3d279087bc2280d63a8e22dcbfdb3</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual RCP&lt; VectorBase&lt; Scalar &gt; &gt;</type>
      <name>nonconstColImpl</name>
      <anchorfile>classThyra_1_1VectorDefaultBase.html</anchorfile>
      <anchor>a7400c4dd3bba11ee2c3c5abed7fae6a5</anchor>
      <arglist>(Ordinal j)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual RCP&lt; const MultiVectorBase&lt; Scalar &gt; &gt;</type>
      <name>contigSubViewImpl</name>
      <anchorfile>classThyra_1_1VectorDefaultBase.html</anchorfile>
      <anchor>ab7029eb7dc0a98682f42247b989831cb</anchor>
      <arglist>(const Range1D &amp;col_rng) const </arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual RCP&lt; MultiVectorBase&lt; Scalar &gt; &gt;</type>
      <name>nonconstContigSubViewImpl</name>
      <anchorfile>classThyra_1_1VectorDefaultBase.html</anchorfile>
      <anchor>ab06a8a06f68a540f7ae15d18df5536f0</anchor>
      <arglist>(const Range1D &amp;col_rng)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual RCP&lt; const MultiVectorBase&lt; Scalar &gt; &gt;</type>
      <name>nonContigSubViewImpl</name>
      <anchorfile>classThyra_1_1VectorDefaultBase.html</anchorfile>
      <anchor>a7c9f962b6f17f879453e3f42275213ae</anchor>
      <arglist>(const ArrayView&lt; const int &gt; &amp;cols) const </arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual RCP&lt; MultiVectorBase&lt; Scalar &gt; &gt;</type>
      <name>nonconstNonContigSubViewImpl</name>
      <anchorfile>classThyra_1_1VectorDefaultBase.html</anchorfile>
      <anchor>ac9f367e22f339357f6c9f88da011a761</anchor>
      <arglist>(const ArrayView&lt; const int &gt; &amp;cols)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual void</type>
      <name>acquireDetachedMultiVectorViewImpl</name>
      <anchorfile>classThyra_1_1VectorDefaultBase.html</anchorfile>
      <anchor>a28862b1139df8696b232d0f617c8548d</anchor>
      <arglist>(const Range1D &amp;rowRng, const Range1D &amp;colRng, RTOpPack::ConstSubMultiVectorView&lt; Scalar &gt; *sub_mv) const </arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual void</type>
      <name>releaseDetachedMultiVectorViewImpl</name>
      <anchorfile>classThyra_1_1VectorDefaultBase.html</anchorfile>
      <anchor>ab71b1c23bc79efbb78ef94b68c3ecd8c</anchor>
      <arglist>(RTOpPack::ConstSubMultiVectorView&lt; Scalar &gt; *sub_mv) const </arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual void</type>
      <name>acquireNonconstDetachedMultiVectorViewImpl</name>
      <anchorfile>classThyra_1_1VectorDefaultBase.html</anchorfile>
      <anchor>a021b026b457cfc2f3f70c5c644729ddd</anchor>
      <arglist>(const Range1D &amp;rowRng, const Range1D &amp;colRng, RTOpPack::SubMultiVectorView&lt; Scalar &gt; *sub_mv)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual void</type>
      <name>commitNonconstDetachedMultiVectorViewImpl</name>
      <anchorfile>classThyra_1_1VectorDefaultBase.html</anchorfile>
      <anchor>ae51db8bef073f0a7cfc84962c630db52</anchor>
      <arglist>(RTOpPack::SubMultiVectorView&lt; Scalar &gt; *sub_mv)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual void</type>
      <name>acquireDetachedVectorViewImpl</name>
      <anchorfile>classThyra_1_1VectorDefaultBase.html</anchorfile>
      <anchor>ae209652d3731aa4f01dbe4f68432c2af</anchor>
      <arglist>(const Range1D &amp;rng, RTOpPack::ConstSubVectorView&lt; Scalar &gt; *sub_vec) const </arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual void</type>
      <name>releaseDetachedVectorViewImpl</name>
      <anchorfile>classThyra_1_1VectorDefaultBase.html</anchorfile>
      <anchor>ad831bc6290966c50e294b81bf1b1ad22</anchor>
      <arglist>(RTOpPack::ConstSubVectorView&lt; Scalar &gt; *sub_vec) const </arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual void</type>
      <name>acquireNonconstDetachedVectorViewImpl</name>
      <anchorfile>classThyra_1_1VectorDefaultBase.html</anchorfile>
      <anchor>a18016d04d08d4ecf1eadd2426b70da1f</anchor>
      <arglist>(const Range1D &amp;rng, RTOpPack::SubVectorView&lt; Scalar &gt; *sub_vec)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual void</type>
      <name>commitNonconstDetachedVectorViewImpl</name>
      <anchorfile>classThyra_1_1VectorDefaultBase.html</anchorfile>
      <anchor>aeb37d12d1ef7f157bd9003314ae3c345</anchor>
      <arglist>(RTOpPack::SubVectorView&lt; Scalar &gt; *sub_vec)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual void</type>
      <name>setSubVectorImpl</name>
      <anchorfile>classThyra_1_1VectorDefaultBase.html</anchorfile>
      <anchor>a9cffcf033ad497b9c3223d5d714582dd</anchor>
      <arglist>(const RTOpPack::SparseSubVectorT&lt; Scalar &gt; &amp;sub_vec)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>bool</type>
      <name>opSupportedImpl</name>
      <anchorfile>classThyra_1_1VectorDefaultBase.html</anchorfile>
      <anchor>a30a49916105086b1dcec847dc5d81454</anchor>
      <arglist>(EOpTransp M_trans) const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>applyImpl</name>
      <anchorfile>classThyra_1_1VectorDefaultBase.html</anchorfile>
      <anchor>ad18b850ff11a7742390731dcb6f0cd29</anchor>
      <arglist>(const EOpTransp M_trans, const MultiVectorBase&lt; Scalar &gt; &amp;X, const Ptr&lt; MultiVectorBase&lt; Scalar &gt; &gt; &amp;Y, const Scalar alpha, const Scalar beta) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::VectorSpaceBase</name>
    <filename>classThyra_1_1VectorSpaceBase.html</filename>
    <templarg>Scalar</templarg>
    <base virtualness="virtual">Teuchos::Describable</base>
    <member kind="function">
      <type>RCP&lt; const VectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>makeHaveOwnership</name>
      <anchorfile>classThyra_1_1VectorSpaceBase.html</anchorfile>
      <anchor>a6b34102e2b19645a613495877337cd91</anchor>
      <arglist>(const RCP&lt; const VectorSpaceBase&lt; Scalar &gt; &gt; &amp;vs)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; VectorBase&lt; Scalar &gt; &gt;</type>
      <name>createMember</name>
      <anchorfile>classThyra_1_1VectorSpaceBase.html</anchorfile>
      <anchor>ab981c5960dfa3cd5bd7ee024ce2bf3ae</anchor>
      <arglist>(const RCP&lt; const VectorSpaceBase&lt; Scalar &gt; &gt; &amp;vs, const std::string &amp;label=&quot;&quot;)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; VectorBase&lt; Scalar &gt; &gt;</type>
      <name>createMember</name>
      <anchorfile>classThyra_1_1VectorSpaceBase.html</anchorfile>
      <anchor>afd4ba88cf0bfa4d1cf62bb03f5f4fb84</anchor>
      <arglist>(const VectorSpaceBase&lt; Scalar &gt; &amp;vs, const std::string &amp;label=&quot;&quot;)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; MultiVectorBase&lt; Scalar &gt; &gt;</type>
      <name>createMembers</name>
      <anchorfile>classThyra_1_1VectorSpaceBase.html</anchorfile>
      <anchor>ae11f3b7f058af2ba55aecec5488ef769</anchor>
      <arglist>(const RCP&lt; const VectorSpaceBase&lt; Scalar &gt; &gt; &amp;vs, int numMembers, const std::string &amp;label=&quot;&quot;)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; MultiVectorBase&lt; Scalar &gt; &gt;</type>
      <name>createMembers</name>
      <anchorfile>classThyra_1_1VectorSpaceBase.html</anchorfile>
      <anchor>adabc1195981cc5c10648d51b067cfcef</anchor>
      <arglist>(const RCP&lt; const VectorSpaceBase&lt; Scalar &gt; &gt; &amp;vs, const RCP&lt; const VectorSpaceBase&lt; Scalar &gt; &gt; &amp;domain, const std::string &amp;label=&quot;&quot;)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; MultiVectorBase&lt; Scalar &gt; &gt;</type>
      <name>createMembers</name>
      <anchorfile>classThyra_1_1VectorSpaceBase.html</anchorfile>
      <anchor>a0aacd609616a9d9857a94cfcb1ce9031</anchor>
      <arglist>(const VectorSpaceBase&lt; Scalar &gt; &amp;vs, int numMembers, const std::string &amp;label=&quot;&quot;)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; VectorBase&lt; Scalar &gt; &gt;</type>
      <name>createMemberView</name>
      <anchorfile>classThyra_1_1VectorSpaceBase.html</anchorfile>
      <anchor>a6f2725e1e99ddb6eb16f71d2d6c48057</anchor>
      <arglist>(const RCP&lt; const VectorSpaceBase&lt; Scalar &gt; &gt; &amp;vs, const RTOpPack::SubVectorView&lt; Scalar &gt; &amp;raw_v, const std::string &amp;label=&quot;&quot;)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; VectorBase&lt; Scalar &gt; &gt;</type>
      <name>createMemberView</name>
      <anchorfile>classThyra_1_1VectorSpaceBase.html</anchorfile>
      <anchor>ab3c10e8a84da1b190959e5bab26a6279</anchor>
      <arglist>(const VectorSpaceBase&lt; Scalar &gt; &amp;vs, const RTOpPack::SubVectorView&lt; Scalar &gt; &amp;raw_v, const std::string &amp;label=&quot;&quot;)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const VectorBase&lt; Scalar &gt; &gt;</type>
      <name>createMemberView</name>
      <anchorfile>classThyra_1_1VectorSpaceBase.html</anchorfile>
      <anchor>a1c4b6017998ec9781f556c071805cd1e</anchor>
      <arglist>(const RCP&lt; const VectorSpaceBase&lt; Scalar &gt; &gt; &amp;vs, const RTOpPack::ConstSubVectorView&lt; Scalar &gt; &amp;raw_v, const std::string &amp;label=&quot;&quot;)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const VectorBase&lt; Scalar &gt; &gt;</type>
      <name>createMemberView</name>
      <anchorfile>classThyra_1_1VectorSpaceBase.html</anchorfile>
      <anchor>a1d77e4cd34e16f563661f2dee2b34dee</anchor>
      <arglist>(const VectorSpaceBase&lt; Scalar &gt; &amp;vs, const RTOpPack::ConstSubVectorView&lt; Scalar &gt; &amp;raw_v, const std::string &amp;label=&quot;&quot;)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; MultiVectorBase&lt; Scalar &gt; &gt;</type>
      <name>createMembersView</name>
      <anchorfile>classThyra_1_1VectorSpaceBase.html</anchorfile>
      <anchor>ab4214b2b4a663bc89519cb64b16a65cb</anchor>
      <arglist>(const RCP&lt; const VectorSpaceBase&lt; Scalar &gt; &gt; &amp;vs, const RTOpPack::SubMultiVectorView&lt; Scalar &gt; &amp;raw_mv, const std::string &amp;label=&quot;&quot;)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; MultiVectorBase&lt; Scalar &gt; &gt;</type>
      <name>createMembersView</name>
      <anchorfile>classThyra_1_1VectorSpaceBase.html</anchorfile>
      <anchor>aa8605245f2753d6f9661ad83f4834693</anchor>
      <arglist>(const VectorSpaceBase&lt; Scalar &gt; &amp;vs, const RTOpPack::SubMultiVectorView&lt; Scalar &gt; &amp;raw_mv, const std::string &amp;label=&quot;&quot;)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const MultiVectorBase&lt; Scalar &gt; &gt;</type>
      <name>createMembersView</name>
      <anchorfile>classThyra_1_1VectorSpaceBase.html</anchorfile>
      <anchor>a2d9c69e1f11f5dc9d10962aef6be6ee1</anchor>
      <arglist>(const RCP&lt; const VectorSpaceBase&lt; Scalar &gt; &gt; &amp;vs, const RTOpPack::ConstSubMultiVectorView&lt; Scalar &gt; &amp;raw_mv, const std::string &amp;label=&quot;&quot;)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const MultiVectorBase&lt; Scalar &gt; &gt;</type>
      <name>createMembersView</name>
      <anchorfile>classThyra_1_1VectorSpaceBase.html</anchorfile>
      <anchor>a2cadc53824c74f9966de53dc6763d924</anchor>
      <arglist>(const VectorSpaceBase&lt; Scalar &gt; &amp;vs, const RTOpPack::ConstSubMultiVectorView&lt; Scalar &gt; &amp;raw_mv, const std::string &amp;label=&quot;&quot;)</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual Ordinal</type>
      <name>dim</name>
      <anchorfile>classThyra_1_1VectorSpaceBase.html</anchorfile>
      <anchor>ac56f4148d69547e28f204fc993545229</anchor>
      <arglist>() const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>isCompatible</name>
      <anchorfile>classThyra_1_1VectorSpaceBase.html</anchorfile>
      <anchor>a71ea7018c6f8611b45bb13108731a3b8</anchor>
      <arglist>(const VectorSpaceBase&lt; Scalar &gt; &amp;vecSpc) const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual RCP&lt; const VectorSpaceFactoryBase&lt; Scalar &gt; &gt;</type>
      <name>smallVecSpcFcty</name>
      <anchorfile>classThyra_1_1VectorSpaceBase.html</anchorfile>
      <anchor>a2d5e95e94d5875394807dc93a8de5d65</anchor>
      <arglist>() const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual Scalar</type>
      <name>scalarProd</name>
      <anchorfile>classThyra_1_1VectorSpaceBase.html</anchorfile>
      <anchor>a84de28cb9c3896566e5b6802f3d69d76</anchor>
      <arglist>(const VectorBase&lt; Scalar &gt; &amp;x, const VectorBase&lt; Scalar &gt; &amp;y) const  =0</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>scalarProds</name>
      <anchorfile>classThyra_1_1VectorSpaceBase.html</anchorfile>
      <anchor>ad65ac0238888546c2c879c8a0658282b</anchor>
      <arglist>(const MultiVectorBase&lt; Scalar &gt; &amp;X, const MultiVectorBase&lt; Scalar &gt; &amp;Y, const ArrayView&lt; Scalar &gt; &amp;scalarProds_out) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>isEuclidean</name>
      <anchorfile>classThyra_1_1VectorSpaceBase.html</anchorfile>
      <anchor>abbf282c3a4dc27f669e3d936c19e8105</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>hasInCoreView</name>
      <anchorfile>classThyra_1_1VectorSpaceBase.html</anchorfile>
      <anchor>a8577861018171033222d90a01949e7c3</anchor>
      <arglist>(const Range1D &amp;rng=Range1D(), const EViewType viewType=VIEW_TYPE_DETACHED, const EStrideType strideType=STRIDE_TYPE_NONUNIT) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual RCP&lt; const VectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>clone</name>
      <anchorfile>classThyra_1_1VectorSpaceBase.html</anchorfile>
      <anchor>a360edffb9307a8977f751688bab80187</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual RCP&lt; VectorBase&lt; Scalar &gt; &gt;</type>
      <name>createMember</name>
      <anchorfile>classThyra_1_1VectorSpaceBase.html</anchorfile>
      <anchor>a7871315cbe29058ec211ff389c4ddf06</anchor>
      <arglist>() const  =0</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual RCP&lt; MultiVectorBase&lt; Scalar &gt; &gt;</type>
      <name>createMembers</name>
      <anchorfile>classThyra_1_1VectorSpaceBase.html</anchorfile>
      <anchor>ad5307945c30cd085338b6731c90a8fc5</anchor>
      <arglist>(int numMembers) const  =0</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual RCP&lt; VectorBase&lt; Scalar &gt; &gt;</type>
      <name>createMemberView</name>
      <anchorfile>classThyra_1_1VectorSpaceBase.html</anchorfile>
      <anchor>a2c6037974d33598227bb7dd3251bbc9b</anchor>
      <arglist>(const RTOpPack::SubVectorView&lt; Scalar &gt; &amp;raw_v) const  =0</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual RCP&lt; const VectorBase&lt; Scalar &gt; &gt;</type>
      <name>createMemberView</name>
      <anchorfile>classThyra_1_1VectorSpaceBase.html</anchorfile>
      <anchor>a6b3cdefd43de8b976598ee46d7261cb3</anchor>
      <arglist>(const RTOpPack::ConstSubVectorView&lt; Scalar &gt; &amp;raw_v) const  =0</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual RCP&lt; MultiVectorBase&lt; Scalar &gt; &gt;</type>
      <name>createMembersView</name>
      <anchorfile>classThyra_1_1VectorSpaceBase.html</anchorfile>
      <anchor>aa66925dbe0b17651b284d17a7c61b1dc</anchor>
      <arglist>(const RTOpPack::SubMultiVectorView&lt; Scalar &gt; &amp;raw_mv) const  =0</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual RCP&lt; const MultiVectorBase&lt; Scalar &gt; &gt;</type>
      <name>createMembersView</name>
      <anchorfile>classThyra_1_1VectorSpaceBase.html</anchorfile>
      <anchor>ac09e25e7af0384a21d355e53bfc3f290</anchor>
      <arglist>(const RTOpPack::ConstSubMultiVectorView&lt; Scalar &gt; &amp;raw_mv) const  =0</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual void</type>
      <name>scalarProdsImpl</name>
      <anchorfile>classThyra_1_1VectorSpaceBase.html</anchorfile>
      <anchor>adf8097fa95069d3bb6be6ebaeab2461b</anchor>
      <arglist>(const MultiVectorBase&lt; Scalar &gt; &amp;X, const MultiVectorBase&lt; Scalar &gt; &amp;Y, const ArrayView&lt; Scalar &gt; &amp;scalarProds) const  =0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::VectorSpaceConverterBase</name>
    <filename>classThyra_1_1VectorSpaceConverterBase.html</filename>
    <templarg></templarg>
    <templarg></templarg>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~VectorSpaceConverterBase</name>
      <anchorfile>classThyra_1_1VectorSpaceConverterBase.html</anchorfile>
      <anchor>a56097f4669cb1340ef025c9831637fd5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual Teuchos::RCP&lt; const VectorSpaceBase&lt; ScalarTo &gt; &gt;</type>
      <name>createVectorSpaceTo</name>
      <anchorfile>classThyra_1_1VectorSpaceConverterBase.html</anchorfile>
      <anchor>a956eb3f140d34928f8bc94dfcbcb0cb4</anchor>
      <arglist>(const VectorSpaceBase&lt; ScalarFrom &gt; &amp;vecSpc) const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual Teuchos::RCP&lt; const VectorSpaceBase&lt; ScalarFrom &gt; &gt;</type>
      <name>createVectorSpaceFrom</name>
      <anchorfile>classThyra_1_1VectorSpaceConverterBase.html</anchorfile>
      <anchor>afdb5819fc69f1c09858a90210db81ee2</anchor>
      <arglist>(const VectorSpaceBase&lt; ScalarTo &gt; &amp;vecSpc) const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>convert</name>
      <anchorfile>classThyra_1_1VectorSpaceConverterBase.html</anchorfile>
      <anchor>a2f75d6c30a263bc4bbcc3172acc9b573</anchor>
      <arglist>(const MultiVectorBase&lt; ScalarFrom &gt; &amp;mv_from, MultiVectorBase&lt; ScalarTo &gt; *mv_to) const  =0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::VectorSpaceDefaultBase</name>
    <filename>classThyra_1_1VectorSpaceDefaultBase.html</filename>
    <templarg></templarg>
    <base virtualness="virtual">Thyra::VectorSpaceBase</base>
    <member kind="function" protection="protected">
      <type>RCP&lt; MultiVectorBase&lt; Scalar &gt; &gt;</type>
      <name>createMembers</name>
      <anchorfile>classThyra_1_1VectorSpaceDefaultBase.html</anchorfile>
      <anchor>a9577f4c6c452f08d624be5050c76b0f2</anchor>
      <arglist>(int numMembers) const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>RCP&lt; VectorBase&lt; Scalar &gt; &gt;</type>
      <name>createMemberView</name>
      <anchorfile>classThyra_1_1VectorSpaceDefaultBase.html</anchorfile>
      <anchor>a57b25258c5243e880278559dee8a70d5</anchor>
      <arglist>(const RTOpPack::SubVectorView&lt; Scalar &gt; &amp;raw_v) const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>RCP&lt; const VectorBase&lt; Scalar &gt; &gt;</type>
      <name>createMemberView</name>
      <anchorfile>classThyra_1_1VectorSpaceDefaultBase.html</anchorfile>
      <anchor>a6ca1b1c80c7b63697da38784a7be4b93</anchor>
      <arglist>(const RTOpPack::ConstSubVectorView&lt; Scalar &gt; &amp;raw_v) const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>RCP&lt; MultiVectorBase&lt; Scalar &gt; &gt;</type>
      <name>createMembersView</name>
      <anchorfile>classThyra_1_1VectorSpaceDefaultBase.html</anchorfile>
      <anchor>aaf152d0b7bd8eef3c2d3b847685f9dcd</anchor>
      <arglist>(const RTOpPack::SubMultiVectorView&lt; Scalar &gt; &amp;raw_mv) const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>RCP&lt; const MultiVectorBase&lt; Scalar &gt; &gt;</type>
      <name>createMembersView</name>
      <anchorfile>classThyra_1_1VectorSpaceDefaultBase.html</anchorfile>
      <anchor>a2f126b059bf140f17c5fd49b0150f535</anchor>
      <arglist>(const RTOpPack::ConstSubMultiVectorView&lt; Scalar &gt; &amp;raw_mv) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::VectorSpaceFactoryBase</name>
    <filename>classThyra_1_1VectorSpaceFactoryBase.html</filename>
    <templarg></templarg>
    <base virtualness="virtual">Teuchos::Describable</base>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~VectorSpaceFactoryBase</name>
      <anchorfile>classThyra_1_1VectorSpaceFactoryBase.html</anchorfile>
      <anchor>a5a2516dc0f9e1fa41ba6c696bc8d9739</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual RCP&lt; const VectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>createVecSpc</name>
      <anchorfile>classThyra_1_1VectorSpaceFactoryBase.html</anchorfile>
      <anchor>a730e240d4e5d6ac6d9c0761110cf8303</anchor>
      <arglist>(int dim) const  =0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::VectorSpaceTester</name>
    <filename>classThyra_1_1VectorSpaceTester.html</filename>
    <templarg>Scalar</templarg>
    <member kind="typedef">
      <type>Teuchos::ScalarTraits&lt; Scalar &gt;::magnitudeType</type>
      <name>ScalarMag</name>
      <anchorfile>classThyra_1_1VectorSpaceTester.html</anchorfile>
      <anchor>a16d7d1b584a9534c878dff8ed3c1e325</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>VectorTester&lt; Scalar &gt; &amp;</type>
      <name>vectorTester</name>
      <anchorfile>classThyra_1_1VectorSpaceTester.html</anchorfile>
      <anchor>a799e08dc9f0c936b574241782b5b36a8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const VectorTester&lt; Scalar &gt; &amp;</type>
      <name>vectorTester</name>
      <anchorfile>classThyra_1_1VectorSpaceTester.html</anchorfile>
      <anchor>a59c70d5e6dea997136e0390f0477c271</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>warning_tol</name>
      <anchorfile>classThyra_1_1VectorSpaceTester.html</anchorfile>
      <anchor>a200e81e9056ac4414fd8a6ca81dc73ce</anchor>
      <arglist>(const ScalarMag &amp;warning_tol)</arglist>
    </member>
    <member kind="function">
      <type>ScalarMag</type>
      <name>warning_tol</name>
      <anchorfile>classThyra_1_1VectorSpaceTester.html</anchorfile>
      <anchor>a6373ebc0fba33022148aa9f87447a289</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>error_tol</name>
      <anchorfile>classThyra_1_1VectorSpaceTester.html</anchorfile>
      <anchor>aabdcfb3c18026e1c7f61edc2b711180b</anchor>
      <arglist>(const ScalarMag &amp;error_tol)</arglist>
    </member>
    <member kind="function">
      <type>ScalarMag</type>
      <name>error_tol</name>
      <anchorfile>classThyra_1_1VectorSpaceTester.html</anchorfile>
      <anchor>a92db4969211245445e9aa952c7478f15</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>num_random_vectors</name>
      <anchorfile>classThyra_1_1VectorSpaceTester.html</anchorfile>
      <anchor>a037eebe5fa381bb6be704d70e223cc83</anchor>
      <arglist>(const int num_random_vectors)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>num_random_vectors</name>
      <anchorfile>classThyra_1_1VectorSpaceTester.html</anchorfile>
      <anchor>a9c39be351595f270f597bdc067130d97</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classThyra_1_1VectorSpaceTester.html</anchorfile>
      <anchor>ab13b33229ac02a0f83faa93f027a405a</anchor>
      <arglist>(int, num_mv_cols)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>show_all_tests</name>
      <anchorfile>classThyra_1_1VectorSpaceTester.html</anchorfile>
      <anchor>a317a71bee4176d1dd6ba17b9b169ceec</anchor>
      <arglist>(const bool show_all_tests)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>show_all_tests</name>
      <anchorfile>classThyra_1_1VectorSpaceTester.html</anchorfile>
      <anchor>a82570462c981b6f1a527fca4c44e0086</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>dump_all</name>
      <anchorfile>classThyra_1_1VectorSpaceTester.html</anchorfile>
      <anchor>abdf2bc83ff52d6a8a85d4c80d725fb9b</anchor>
      <arglist>(const bool dump_all)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>dump_all</name>
      <anchorfile>classThyra_1_1VectorSpaceTester.html</anchorfile>
      <anchor>a8d6d5e7e2f4c275ae6e130da787d116a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>VectorSpaceTester</name>
      <anchorfile>classThyra_1_1VectorSpaceTester.html</anchorfile>
      <anchor>a4be9f68fd7cb0a645301152028c73bcd</anchor>
      <arglist>(const ScalarMag warning_tol=1e-13, const ScalarMag error_tol=1e-10, const int num_random_vectors=1, const int num_mv_cols=4, const bool show_all_tests=false, const bool dump_all=false)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>check</name>
      <anchorfile>classThyra_1_1VectorSpaceTester.html</anchorfile>
      <anchor>a95a9126326b2915d49f27f73784bf833</anchor>
      <arglist>(const VectorSpaceBase&lt; Scalar &gt; &amp;vs, Teuchos::FancyOStream *out) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::VectorStdOpsTester</name>
    <filename>classThyra_1_1VectorStdOpsTester.html</filename>
    <templarg></templarg>
    <member kind="typedef">
      <type>Teuchos::ScalarTraits&lt; Scalar &gt;::magnitudeType</type>
      <name>ScalarMag</name>
      <anchorfile>classThyra_1_1VectorStdOpsTester.html</anchorfile>
      <anchor>aed2bd06ccbb16a8bd7d0bd2cd8ef35c0</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classThyra_1_1VectorStdOpsTester.html</anchorfile>
      <anchor>ac402d396ce39f6d5f8eb41f84fe4b592</anchor>
      <arglist>(ScalarMag, warning_tol)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classThyra_1_1VectorStdOpsTester.html</anchorfile>
      <anchor>aafd71b68e400ba7a74a21c011078ace4</anchor>
      <arglist>(ScalarMag, error_tol)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>VectorStdOpsTester</name>
      <anchorfile>classThyra_1_1VectorStdOpsTester.html</anchorfile>
      <anchor>ad82c85d669e25f90346fbce3f0af676d</anchor>
      <arglist>(const ScalarMag &amp;warning_tol=0, const ScalarMag &amp;error_tol=0)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>checkStdOps</name>
      <anchorfile>classThyra_1_1VectorStdOpsTester.html</anchorfile>
      <anchor>a848bc51db1c0803ca4395a8e0164ff62</anchor>
      <arglist>(const VectorSpaceBase&lt; Scalar &gt; &amp;vecSpc, std::ostream *out=0, const bool &amp;dumpAll=false)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::VectorTester</name>
    <filename>classThyra_1_1VectorTester.html</filename>
    <templarg>Scalar</templarg>
    <member kind="typedef">
      <type>Teuchos::ScalarTraits&lt; Scalar &gt;::magnitudeType</type>
      <name>ScalarMag</name>
      <anchorfile>classThyra_1_1VectorTester.html</anchorfile>
      <anchor>a1b65f9bd698320782a5852c07f005d53</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>MultiVectorTester&lt; Scalar &gt; &amp;</type>
      <name>multiVectorTester</name>
      <anchorfile>classThyra_1_1VectorTester.html</anchorfile>
      <anchor>ae9cbf7f56c138642350ab7161404e4b4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const MultiVectorTester&lt; Scalar &gt; &amp;</type>
      <name>multiVectorTester</name>
      <anchorfile>classThyra_1_1VectorTester.html</anchorfile>
      <anchor>a939ed3cfa00cd4dde6cf6b87104cf690</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>warning_tol</name>
      <anchorfile>classThyra_1_1VectorTester.html</anchorfile>
      <anchor>a178d36a7c4f3965bfd316679ff89f768</anchor>
      <arglist>(const ScalarMag &amp;warning_tol)</arglist>
    </member>
    <member kind="function">
      <type>ScalarMag</type>
      <name>warning_tol</name>
      <anchorfile>classThyra_1_1VectorTester.html</anchorfile>
      <anchor>a97dd94fc6b1d12a75e6441ba8ec7d2c9</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>error_tol</name>
      <anchorfile>classThyra_1_1VectorTester.html</anchorfile>
      <anchor>a4903bf523ad7aeac19663f334325045d</anchor>
      <arglist>(const ScalarMag &amp;error_tol)</arglist>
    </member>
    <member kind="function">
      <type>ScalarMag</type>
      <name>error_tol</name>
      <anchorfile>classThyra_1_1VectorTester.html</anchorfile>
      <anchor>a9699db3824dd14b35cfe5a41e172a687</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>num_random_vectors</name>
      <anchorfile>classThyra_1_1VectorTester.html</anchorfile>
      <anchor>a7b83295da2ee9ded390ebaea87c23931</anchor>
      <arglist>(const int num_random_vectors)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>num_random_vectors</name>
      <anchorfile>classThyra_1_1VectorTester.html</anchorfile>
      <anchor>aee9efcc4ec612cf0ef95f26401705b49</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>show_all_tests</name>
      <anchorfile>classThyra_1_1VectorTester.html</anchorfile>
      <anchor>a86340b423b8a0526ce2360ac7255dc0b</anchor>
      <arglist>(const bool show_all_tests)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>show_all_tests</name>
      <anchorfile>classThyra_1_1VectorTester.html</anchorfile>
      <anchor>a2582aa80fa7391eae1a7fa0eb1595d33</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>dump_all</name>
      <anchorfile>classThyra_1_1VectorTester.html</anchorfile>
      <anchor>a5c5405089f0e5c2ff92ace43c9976ccd</anchor>
      <arglist>(const bool dump_all)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>dump_all</name>
      <anchorfile>classThyra_1_1VectorTester.html</anchorfile>
      <anchor>a71174988e4eb1f018eddbdf7a3da215c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>VectorTester</name>
      <anchorfile>classThyra_1_1VectorTester.html</anchorfile>
      <anchor>a2259e54edf69050630cfcd3ce13a2666</anchor>
      <arglist>(const ScalarMag warning_tol=1e-13, const ScalarMag error_tol=1e-10, const int num_random_vectors=1, const bool show_all_tests=false, const bool dump_all=false)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>check</name>
      <anchorfile>classThyra_1_1VectorTester.html</anchorfile>
      <anchor>a795b7147973d8bbb15b72426d2090135</anchor>
      <arglist>(const VectorBase&lt; Scalar &gt; &amp;v, Teuchos::FancyOStream *out) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Thyra::ZeroLinearOpBase</name>
    <filename>classThyra_1_1ZeroLinearOpBase.html</filename>
    <templarg></templarg>
    <base virtualness="virtual">Thyra::LinearOpBase</base>
  </compound>
  <compound kind="group">
    <name>thyra_faq_grp</name>
    <title>Frequently Asked Questions (FAQ) about Thyra Software</title>
    <filename>group__thyra__faq__grp.html</filename>
    <docanchor file="group__thyra__faq__grp" title="Outline">thyra_faq_outline_sec</docanchor>
    <docanchor file="group__thyra__faq__grp" title="Questions about the smart pointer class Teuchos::RCP">thyra_faq_rcp_sec</docanchor>
    <docanchor file="group__thyra__faq__grp" title="Q: What are RCP objects and why are they important?">thyra_faq_rcp_important_sec</docanchor>
    <docanchor file="group__thyra__faq__grp" title="Q: Should my code use RCP&apos;s everywhere?">thyra_faq_rcp_everywhere_sec</docanchor>
    <docanchor file="group__thyra__faq__grp" title="Questions about Fundamental Thyra Operator/Vector Interfaces">thyra_faq_itfc_sec</docanchor>
    <docanchor file="group__thyra__faq__grp" title="Q: Why is Thyra written with so many non-member helper functions instead of member functions?">thyra_faq_why_helper_funcs_sec</docanchor>
    <docanchor file="group__thyra__faq__grp" title="Q: Where is the Scalar class, and how do I use it to replace my underlying data-type, e.g. double, in my ANA?">thyra_faq_Scalar_sec</docanchor>
    <docanchor file="group__thyra__faq__grp" title="Q: How do I create a Thyra::VectorBase or Thyra::MultiVectorBase object?">thyra_faq_creating_vecs_multivecs_sec</docanchor>
  </compound>
  <compound kind="group">
    <name>Thyra_interfaces_grp</name>
    <title>Thyra interfaces</title>
    <filename>group__Thyra__interfaces__grp.html</filename>
    <subgroup>Thyra_Op_Vec_interfaces_code_grp</subgroup>
    <subgroup>Thyra_Op_Solve_interfaces_code_grp</subgroup>
    <subgroup>Thyra_Nonlinear_interfaces_code_grp</subgroup>
  </compound>
  <compound kind="group">
    <name>Thyra_Op_Vec_interfaces_code_grp</name>
    <title>Thyra operator/vector interfaces</title>
    <filename>group__Thyra__Op__Vec__interfaces__code__grp.html</filename>
    <subgroup>Thyra_Op_Vec_fundamental_interfaces_code_grp</subgroup>
    <subgroup>Thyra_Op_Vec_extended_interfaces_code_grp</subgroup>
    <subgroup>Thyra_Op_Vec_Behavior_Of_Views_grp</subgroup>
  </compound>
  <compound kind="group">
    <name>Thyra_Op_Vec_fundamental_interfaces_code_grp</name>
    <title>Thyra operator/vector fundamental interfaces</title>
    <filename>group__Thyra__Op__Vec__fundamental__interfaces__code__grp.html</filename>
    <class kind="class">Thyra::LinearOpBase</class>
    <class kind="class">Thyra::MultiVectorBase</class>
    <class kind="class">Thyra::Exceptions::UnInitialized</class>
    <class kind="class">Thyra::Exceptions::IncompatibleVectorSpaces</class>
    <class kind="class">Thyra::Exceptions::OpNotSupported</class>
    <class kind="class">Thyra::VectorBase</class>
    <class kind="class">Thyra::VectorSpaceBase</class>
    <class kind="class">Thyra::VectorSpaceFactoryBase</class>
    <member kind="typedef">
      <type>Teuchos::Range1D</type>
      <name>Range1D</name>
      <anchorfile>group__Thyra__Op__Vec__fundamental__interfaces__code__grp.html</anchorfile>
      <anchor>gab418036320641179ea0fcd1671b724d4</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Teuchos::Ordinal</type>
      <name>Ordinal</name>
      <anchorfile>group__Thyra__Op__Vec__fundamental__interfaces__code__grp.html</anchorfile>
      <anchor>ga96575ff06b1d5a036da8c781e4dc21af</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>EConj</name>
      <anchorfile>group__Thyra__Op__Vec__fundamental__interfaces__code__grp.html</anchorfile>
      <anchor>ga214169c51d2772af5fcd155ba5c1e7a6</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>NONCONJ_ELE</name>
      <anchorfile>group__Thyra__Op__Vec__fundamental__interfaces__code__grp.html</anchorfile>
      <anchor>gga214169c51d2772af5fcd155ba5c1e7a6a56211f7d4df732ed33a46273542a33fa</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CONJ_ELE</name>
      <anchorfile>group__Thyra__Op__Vec__fundamental__interfaces__code__grp.html</anchorfile>
      <anchor>gga214169c51d2772af5fcd155ba5c1e7a6a434d383a01cebb51540879cf1d49b11b</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>EOpTransp</name>
      <anchorfile>group__Thyra__Op__Vec__fundamental__interfaces__code__grp.html</anchorfile>
      <anchor>ga959712bcf3ed560543a0264b2bc97929</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>NOTRANS</name>
      <anchorfile>group__Thyra__Op__Vec__fundamental__interfaces__code__grp.html</anchorfile>
      <anchor>gga959712bcf3ed560543a0264b2bc97929a4f033a492ef97f641630e72f0b9e133e</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CONJ</name>
      <anchorfile>group__Thyra__Op__Vec__fundamental__interfaces__code__grp.html</anchorfile>
      <anchor>gga959712bcf3ed560543a0264b2bc97929ac9776b735743202d66846fd1a795c11a</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>TRANS</name>
      <anchorfile>group__Thyra__Op__Vec__fundamental__interfaces__code__grp.html</anchorfile>
      <anchor>gga959712bcf3ed560543a0264b2bc97929a44a8a16e6148e6d179e98bf9ec964001</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CONJTRANS</name>
      <anchorfile>group__Thyra__Op__Vec__fundamental__interfaces__code__grp.html</anchorfile>
      <anchor>gga959712bcf3ed560543a0264b2bc97929a6b0a8644ed2265dab5f2167b120a21dd</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>EViewType</name>
      <anchorfile>group__Thyra__Op__Vec__fundamental__interfaces__code__grp.html</anchorfile>
      <anchor>ga95c4498e9ecb5e6a0a129d497ecba687</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>VIEW_TYPE_DIRECT</name>
      <anchorfile>group__Thyra__Op__Vec__fundamental__interfaces__code__grp.html</anchorfile>
      <anchor>gga95c4498e9ecb5e6a0a129d497ecba687a1f628c78d269297bc917a56ee57f9fb0</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>VIEW_TYPE_DETACHED</name>
      <anchorfile>group__Thyra__Op__Vec__fundamental__interfaces__code__grp.html</anchorfile>
      <anchor>gga95c4498e9ecb5e6a0a129d497ecba687ad0690bf7e1a2a69c8ee561c01876c408</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>EStrideType</name>
      <anchorfile>group__Thyra__Op__Vec__fundamental__interfaces__code__grp.html</anchorfile>
      <anchor>ga70ed6367e1d4feb7c360a5666e4cc082</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>STRIDE_TYPE_UNIT</name>
      <anchorfile>group__Thyra__Op__Vec__fundamental__interfaces__code__grp.html</anchorfile>
      <anchor>gga70ed6367e1d4feb7c360a5666e4cc082a308ad2240e3fd9a37978968b18ed625e</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>STRIDE_TYPE_NONUNIT</name>
      <anchorfile>group__Thyra__Op__Vec__fundamental__interfaces__code__grp.html</anchorfile>
      <anchor>gga70ed6367e1d4feb7c360a5666e4cc082a45c8add8b2090272a6650dadb6ba432f</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>const char *</type>
      <name>toString</name>
      <anchorfile>group__Thyra__Op__Vec__fundamental__interfaces__code__grp.html</anchorfile>
      <anchor>ga9dd0572a449b6688556f6d8262e14578</anchor>
      <arglist>(EConj conj)</arglist>
    </member>
    <member kind="function">
      <type>const char *</type>
      <name>toString</name>
      <anchorfile>group__Thyra__Op__Vec__fundamental__interfaces__code__grp.html</anchorfile>
      <anchor>ga4a6210ba353f2dc0da82f8bb69291a3f</anchor>
      <arglist>(EOpTransp transp)</arglist>
    </member>
    <member kind="function">
      <type>EOpTransp</type>
      <name>real_trans</name>
      <anchorfile>group__Thyra__Op__Vec__fundamental__interfaces__code__grp.html</anchorfile>
      <anchor>gae7d8a1c53cf64f6008b62eceb3b93299</anchor>
      <arglist>(EOpTransp transp)</arglist>
    </member>
    <member kind="function">
      <type>EOpTransp</type>
      <name>not_trans</name>
      <anchorfile>group__Thyra__Op__Vec__fundamental__interfaces__code__grp.html</anchorfile>
      <anchor>gae5699d8d9937fba2e3aeac845d570beb</anchor>
      <arglist>(EOpTransp transp)</arglist>
    </member>
    <member kind="function">
      <type>EOpTransp</type>
      <name>trans_trans</name>
      <anchorfile>group__Thyra__Op__Vec__fundamental__interfaces__code__grp.html</anchorfile>
      <anchor>gaefa1c58514b5ea41be6903925ec94b50</anchor>
      <arglist>(EOpTransp trans1, EOpTransp trans2)</arglist>
    </member>
    <member kind="function">
      <type>EConj</type>
      <name>transToConj</name>
      <anchorfile>group__Thyra__Op__Vec__fundamental__interfaces__code__grp.html</anchorfile>
      <anchor>ga93182d680e03b6e73f393c75ed815cfa</anchor>
      <arglist>(EOpTransp trans)</arglist>
    </member>
    <member kind="function">
      <type>EOpTransp</type>
      <name>applyConjToTrans</name>
      <anchorfile>group__Thyra__Op__Vec__fundamental__interfaces__code__grp.html</anchorfile>
      <anchor>ga97294c774dbaa8e522a78495e1270e87</anchor>
      <arglist>(EConj conj)</arglist>
    </member>
    <member kind="function">
      <type>EOpTransp</type>
      <name>applyTransposeConjToTrans</name>
      <anchorfile>group__Thyra__Op__Vec__fundamental__interfaces__code__grp.html</anchorfile>
      <anchor>ga740b8282c63d8f810cb0a0ba34e3a3b3</anchor>
      <arglist>(EConj conj)</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>Thyra_Op_Vec_extended_interfaces_code_grp</name>
    <title>Thyra operator/vector extended interfaces</title>
    <filename>group__Thyra__Op__Vec__extended__interfaces__code__grp.html</filename>
    <class kind="class">Thyra::AddedLinearOpBase</class>
    <class kind="class">Thyra::BlockedLinearOpBase</class>
    <class kind="class">Thyra::DiagonalLinearOpBase</class>
    <class kind="class">Thyra::IdentityLinearOpBase</class>
    <class kind="class">Thyra::MultipliedLinearOpBase</class>
    <class kind="class">Thyra::MultiVectorFileIOBase</class>
    <class kind="class">Thyra::MultiVectorRandomizerBase</class>
    <class kind="class">Thyra::PhysicallyBlockedLinearOpBase</class>
    <class kind="class">Thyra::ProductMultiVectorBase</class>
    <class kind="class">Thyra::ProductVectorBase</class>
    <class kind="class">Thyra::ProductVectorSpaceBase</class>
    <class kind="class">Thyra::RowStatLinearOpBase</class>
    <class kind="class">Thyra::ScaledAdjointLinearOpBase</class>
    <class kind="class">Thyra::ScaledLinearOpBase</class>
    <class kind="class">Thyra::SpmdMultiVectorBase</class>
    <class kind="class">Thyra::SpmdVectorBase</class>
    <class kind="class">Thyra::SpmdVectorSpaceBase</class>
    <class kind="class">Thyra::VectorSpaceConverterBase</class>
    <class kind="class">Thyra::ZeroLinearOpBase</class>
    <member kind="function">
      <type>void</type>
      <name>unwrap</name>
      <anchorfile>group__Thyra__Op__Vec__extended__interfaces__code__grp.html</anchorfile>
      <anchor>ga77686eb3d518137f32ebff2c0e39a43e</anchor>
      <arglist>(const LinearOpBase&lt; Scalar &gt; &amp;Op, Scalar *scalar, EOpTransp *transp, const LinearOpBase&lt; Scalar &gt; **origOp)</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>Thyra_Op_Vec_Behavior_Of_Views_grp</name>
    <title>State behavior of Thyra views</title>
    <filename>group__Thyra__Op__Vec__Behavior__Of__Views__grp.html</filename>
  </compound>
  <compound kind="group">
    <name>Thyra_Op_Solve_interfaces_code_grp</name>
    <title>Thyra operator solve interfaces</title>
    <filename>group__Thyra__Op__Solve__interfaces__code__grp.html</filename>
    <subgroup>Thyra_Op_Solve_fundamental_interfaces_code_grp</subgroup>
    <subgroup>Thyra_Op_Solve_extended_interfaces_code_grp</subgroup>
  </compound>
  <compound kind="group">
    <name>Thyra_Op_Solve_fundamental_interfaces_code_grp</name>
    <title>Thyra operator solve fundamental interfaces</title>
    <filename>group__Thyra__Op__Solve__fundamental__interfaces__code__grp.html</filename>
    <class kind="class">Thyra::LinearOpSourceBase</class>
    <class kind="class">Thyra::LinearOpWithSolveBase</class>
    <class kind="class">Thyra::LinearOpWithSolveFactoryBase</class>
    <class kind="class">Thyra::PreconditionerBase</class>
    <class kind="class">Thyra::PreconditionerFactoryBase</class>
    <class kind="struct">Thyra::SolveMeasureType</class>
    <class kind="struct">Thyra::SolveCriteria</class>
    <class kind="class">Thyra::CatastrophicSolveFailure</class>
    <class kind="struct">Thyra::SolveStatus</class>
    <member kind="enumeration">
      <type></type>
      <name>ESolveMeasureNormType</name>
      <anchorfile>group__Thyra__Op__Solve__fundamental__interfaces__code__grp.html</anchorfile>
      <anchor>gaa00883ca75e1ab62ec24a5d697251734</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SOLVE_MEASURE_ONE</name>
      <anchorfile>group__Thyra__Op__Solve__fundamental__interfaces__code__grp.html</anchorfile>
      <anchor>ggaa00883ca75e1ab62ec24a5d697251734aee72a4548bf7cd1cd2f430fe44b6e164</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SOLVE_MEASURE_NORM_RESIDUAL</name>
      <anchorfile>group__Thyra__Op__Solve__fundamental__interfaces__code__grp.html</anchorfile>
      <anchor>ggaa00883ca75e1ab62ec24a5d697251734a3db1e489c7fc027a4cd52cc454939d02</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SOLVE_MEASURE_NORM_SOLUTION</name>
      <anchorfile>group__Thyra__Op__Solve__fundamental__interfaces__code__grp.html</anchorfile>
      <anchor>ggaa00883ca75e1ab62ec24a5d697251734a756e0120ddef8839b72eed8ba44166a3</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SOLVE_MEASURE_NORM_INIT_RESIDUAL</name>
      <anchorfile>group__Thyra__Op__Solve__fundamental__interfaces__code__grp.html</anchorfile>
      <anchor>ggaa00883ca75e1ab62ec24a5d697251734a215492c2f1a569476fe7df0fbd2a2f86</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SOLVE_MEASURE_NORM_RHS</name>
      <anchorfile>group__Thyra__Op__Solve__fundamental__interfaces__code__grp.html</anchorfile>
      <anchor>ggaa00883ca75e1ab62ec24a5d697251734a4c133b5e87cce0c384f298be94bed1d2</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>ESolveStatus</name>
      <anchorfile>group__Thyra__Op__Solve__fundamental__interfaces__code__grp.html</anchorfile>
      <anchor>ga9426be3e153f2799ccae5104ba4ba010</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SOLVE_STATUS_CONVERGED</name>
      <anchorfile>group__Thyra__Op__Solve__fundamental__interfaces__code__grp.html</anchorfile>
      <anchor>gga9426be3e153f2799ccae5104ba4ba010a92068373393f99ee3f3decc536bc0dac</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SOLVE_STATUS_UNCONVERGED</name>
      <anchorfile>group__Thyra__Op__Solve__fundamental__interfaces__code__grp.html</anchorfile>
      <anchor>gga9426be3e153f2799ccae5104ba4ba010a70666df00db60bf6cec4f8eefeb74093</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SOLVE_STATUS_UNKNOWN</name>
      <anchorfile>group__Thyra__Op__Solve__fundamental__interfaces__code__grp.html</anchorfile>
      <anchor>gga9426be3e153f2799ccae5104ba4ba010afd9f0fb6770d78aa468ff5fbf9dd7403</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>ESupportSolveUse</name>
      <anchorfile>group__Thyra__Op__Solve__fundamental__interfaces__code__grp.html</anchorfile>
      <anchor>ga76337245b47dc85bc5f24d0cd6e6367d</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SUPPORT_SOLVE_UNSPECIFIED</name>
      <anchorfile>group__Thyra__Op__Solve__fundamental__interfaces__code__grp.html</anchorfile>
      <anchor>gga76337245b47dc85bc5f24d0cd6e6367daa0de3986dd08d509e66ef820f0344279</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SUPPORT_SOLVE_FORWARD_ONLY</name>
      <anchorfile>group__Thyra__Op__Solve__fundamental__interfaces__code__grp.html</anchorfile>
      <anchor>gga76337245b47dc85bc5f24d0cd6e6367da0e16289eb60cfed68f6169f47e01f7ed</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SUPPORT_SOLVE_TRANSPOSE_ONLY</name>
      <anchorfile>group__Thyra__Op__Solve__fundamental__interfaces__code__grp.html</anchorfile>
      <anchor>gga76337245b47dc85bc5f24d0cd6e6367daf54bd5300237b2e94fe82db3a98ad0a7</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SUPPORT_SOLVE_FORWARD_AND_TRANSPOSE</name>
      <anchorfile>group__Thyra__Op__Solve__fundamental__interfaces__code__grp.html</anchorfile>
      <anchor>gga76337245b47dc85bc5f24d0cd6e6367da6df6366fc0440b4a16029f43f4e08dc5</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>EPreconditionerInputType</name>
      <anchorfile>group__Thyra__Op__Solve__fundamental__interfaces__code__grp.html</anchorfile>
      <anchor>ga724d528c0dbe849a982b90b6e6bdcf93</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>PRECONDITIONER_INPUT_TYPE_AS_OPERATOR</name>
      <anchorfile>group__Thyra__Op__Solve__fundamental__interfaces__code__grp.html</anchorfile>
      <anchor>gga724d528c0dbe849a982b90b6e6bdcf93aaaad021fa247bf9a362f95a84fe50c0e</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>PRECONDITIONER_INPUT_TYPE_AS_MATRIX</name>
      <anchorfile>group__Thyra__Op__Solve__fundamental__interfaces__code__grp.html</anchorfile>
      <anchor>gga724d528c0dbe849a982b90b6e6bdcf93a88f68616bc2fe207f28ad0509d5d69d3</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>const std::string</type>
      <name>toString</name>
      <anchorfile>group__Thyra__Op__Solve__fundamental__interfaces__code__grp.html</anchorfile>
      <anchor>gaa36dfdeed6c93a3b79b400d9984186ab</anchor>
      <arglist>(const ESolveMeasureNormType solveMeasureNormType)</arglist>
    </member>
    <member kind="function">
      <type>const std::string</type>
      <name>toString</name>
      <anchorfile>group__Thyra__Op__Solve__fundamental__interfaces__code__grp.html</anchorfile>
      <anchor>gaad3b903c13cfa2be2c27673f16576295</anchor>
      <arglist>(const ESolveStatus solveStatus)</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>Thyra_Op_Solve_extended_interfaces_code_grp</name>
    <title>Thyra operator solve extended interfaces</title>
    <filename>group__Thyra__Op__Solve__extended__interfaces__code__grp.html</filename>
    <class kind="class">Thyra::BlockedLinearOpWithSolveBase</class>
    <class kind="class">Thyra::InverseLinearOpBase</class>
    <class kind="class">Thyra::LinearSolverBuilderBase</class>
    <class kind="class">Thyra::PhysicallyBlockedLinearOpWithSolveBase</class>
  </compound>
  <compound kind="group">
    <name>Thyra_Nonlinear_interfaces_code_grp</name>
    <title>Thyra nonlinear interfaces</title>
    <filename>group__Thyra__Nonlinear__interfaces__code__grp.html</filename>
    <subgroup>Thyra_Nonlinear_model_evaluator_interfaces_code_grp</subgroup>
    <subgroup>Thyra_Nonlinear_solver_interfaces_code_grp</subgroup>
  </compound>
  <compound kind="group">
    <name>Thyra_Nonlinear_model_evaluator_interfaces_code_grp</name>
    <title>Thyra nonlinear model interfaces</title>
    <filename>group__Thyra__Nonlinear__model__evaluator__interfaces__code__grp.html</filename>
    <class kind="class">Thyra::ModelEvaluator</class>
    <class kind="class">Thyra::ModelEvaluatorBase</class>
  </compound>
  <compound kind="group">
    <name>Thyra_Nonlinear_solver_interfaces_code_grp</name>
    <title>Thyra nonlinear solver interfaces</title>
    <filename>group__Thyra__Nonlinear__solver__interfaces__code__grp.html</filename>
    <class kind="class">Thyra::NonlinearSolverBase</class>
  </compound>
  <compound kind="group">
    <name>Thyra_support_grp</name>
    <title>Thyra support</title>
    <filename>group__Thyra__support__grp.html</filename>
    <subgroup>Thyra_Op_Vec_support_grp</subgroup>
    <subgroup>OperatorVectorANASupportSoftware_grp</subgroup>
    <subgroup>Thyra_Nonlin_support_grp</subgroup>
  </compound>
  <compound kind="group">
    <name>Thyra_Op_Vec_support_grp</name>
    <title>Thyra operator/vector support</title>
    <filename>group__Thyra__Op__Vec__support__grp.html</filename>
    <subgroup>Thyra_Op_Vec_ANA_Development_grp</subgroup>
    <subgroup>Thyra_Op_Vec_Adapters_grp</subgroup>
  </compound>
  <compound kind="group">
    <name>Thyra_Op_Vec_ANA_Development_grp</name>
    <title>Development of linear Abstract Numerical Algorithms (ANAs) (Client Support)</title>
    <filename>group__Thyra__Op__Vec__ANA__Development__grp.html</filename>
    <class kind="class">Thyra::DefaultAddedLinearOp</class>
    <class kind="class">Thyra::DefaultBlockedLinearOp</class>
    <class kind="class">Thyra::DefaultDiagonalLinearOp</class>
    <class kind="class">Thyra::DefaultIdentityLinearOp</class>
    <class kind="class">Thyra::DefaultMultipliedLinearOp</class>
    <class kind="class">Thyra::DefaultMultiVectorProductVector</class>
    <class kind="class">Thyra::DefaultMultiVectorProductVectorSpace</class>
    <class kind="class">Thyra::DefaultProductMultiVector</class>
    <class kind="class">Thyra::DefaultProductVector</class>
    <class kind="class">Thyra::DefaultProductVectorSpace</class>
    <class kind="class">Thyra::DefaultScaledAdjointLinearOp</class>
    <class kind="class">Thyra::DefaultZeroLinearOp</class>
    <class kind="class">Thyra::ConstDetachedMultiVectorView</class>
    <class kind="class">Thyra::DetachedMultiVectorView</class>
    <class kind="class">Thyra::ConstDetachedVectorView</class>
    <class kind="class">Thyra::DetachedVectorView</class>
    <class kind="class">Thyra::LinearOpDefaultBase</class>
    <class kind="class">Thyra::LinearOpTester</class>
    <class kind="class">Thyra::ListedMultiVectorRandomizer</class>
    <class kind="class">Thyra::MultiVectorDefaultBase</class>
    <class kind="class">Thyra::MultiVectorTester</class>
    <class kind="class">Thyra::ParameterDrivenMultiVectorInput</class>
    <class kind="class">Thyra::UniversalMultiVectorRandomizer</class>
    <class kind="class">Thyra::VectorDefaultBase</class>
    <class kind="class">Thyra::VectorSpaceDefaultBase</class>
    <class kind="class">Thyra::VectorSpaceTester</class>
    <class kind="class">Thyra::VectorTester</class>
    <class kind="class">Thyra::DefaultBlockedTriangularLinearOpWithSolve</class>
    <class kind="class">Thyra::DefaultInverseLinearOp</class>
    <class kind="class">Thyra::LinearOpWithSolveTester</class>
    <member kind="define">
      <type>#define</type>
      <name>THYRA_ASSERT_LHS_ARG</name>
      <anchorfile>group__Thyra__Op__Vec__ANA__Development__grp.html</anchorfile>
      <anchor>ga2738c6642f071f0ec06017f38f252c9a</anchor>
      <arglist>(FUNC_NAME, LHS_ARG)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>THYRA_ASSERT_VEC_SPACES_NAMES</name>
      <anchorfile>group__Thyra__Op__Vec__ANA__Development__grp.html</anchorfile>
      <anchor>gac42d4757eb5533659ad6d4cfa0081e99</anchor>
      <arglist>(FUNC_NAME, VS1, VS1_NAME, VS2, VS2_NAME)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>THYRA_ASSERT_VEC_SPACES</name>
      <anchorfile>group__Thyra__Op__Vec__ANA__Development__grp.html</anchorfile>
      <anchor>ga192aa1cc23c85f3a43eb2c4257a1edcf</anchor>
      <arglist>(FUNC_NAME, VS1, VS2)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>THYRA_ASSERT_MAT_VEC_SPACES</name>
      <anchorfile>group__Thyra__Op__Vec__ANA__Development__grp.html</anchorfile>
      <anchor>gadeaae545a691d5acf0f3c94aae557e02</anchor>
      <arglist>(FUNC_NAME, M, M_T, M_VS, VS)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>THYRA_ASSERT_LINEAR_OP_VEC_APPLY_SPACES</name>
      <anchorfile>group__Thyra__Op__Vec__ANA__Development__grp.html</anchorfile>
      <anchor>ga7f1763c404e2d45cfbf00a507a1cb541</anchor>
      <arglist>(FUNC_NAME, M, M_T, X, Y)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>THYRA_ASSERT_LINEAR_OP_MULTIVEC_APPLY_SPACES</name>
      <anchorfile>group__Thyra__Op__Vec__ANA__Development__grp.html</anchorfile>
      <anchor>gab7ff6f15288dcf1594be8cf69d20323a</anchor>
      <arglist>(FUNC_NAME, M, M_T, X, Y)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>THYRA_ASSERT_LINEAR_OP_PLUS_LINEAR_OP_SPACES_NAMES</name>
      <anchorfile>group__Thyra__Op__Vec__ANA__Development__grp.html</anchorfile>
      <anchor>gab87d5c3fa854abd0943a7b57e6361044</anchor>
      <arglist>(FUNC_NAME, M1, M1_T, M1_N, M2, M2_T, M2_N)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>THYRA_ASSERT_LINEAR_OP_TIMES_LINEAR_OP_SPACES_NAMES</name>
      <anchorfile>group__Thyra__Op__Vec__ANA__Development__grp.html</anchorfile>
      <anchor>ga49cfded1e4c7584f93d8a1fc0b5b6d07</anchor>
      <arglist>(FUNC_NAME, M1, M1_T, M1_N, M2, M2_T, M2_N)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>THYRA_ASSERT_MAT_MAT_SPACES</name>
      <anchorfile>group__Thyra__Op__Vec__ANA__Development__grp.html</anchorfile>
      <anchor>gae391e7046f3663e7d0bc24d1de90ee02</anchor>
      <arglist>(FUNC_NAME, M1, M1_T, M1_VS, M2, M2_T, M2_VS)</arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>EThrowOnSolveFailure</name>
      <anchorfile>group__Thyra__Op__Vec__ANA__Development__grp.html</anchorfile>
      <anchor>ga4679683fdfcb5bfa366a1fffab3c3239</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>THROW_ON_SOLVE_FAILURE</name>
      <anchorfile>group__Thyra__Op__Vec__ANA__Development__grp.html</anchorfile>
      <anchor>gga4679683fdfcb5bfa366a1fffab3c3239ac5f6f0b1b01c181d90985556f7e90b8f</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IGNORE_SOLVE_FAILURE</name>
      <anchorfile>group__Thyra__Op__Vec__ANA__Development__grp.html</anchorfile>
      <anchor>gga4679683fdfcb5bfa366a1fffab3c3239acdd63ab65e69d88d3553f93dfcf41d84</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>const Thyra::VectorSpaceBase&lt; Scalar &gt; &amp;</type>
      <name>linear_op_op</name>
      <anchorfile>group__Thyra__Op__Vec__ANA__Development__grp.html</anchorfile>
      <anchor>gadd29ab16cfeb7951771da8c63072e840</anchor>
      <arglist>(const Thyra::LinearOpBase&lt; Scalar &gt; &amp;M, Thyra::EOpTransp M_trans, EM_VS M_VS)</arglist>
    </member>
    <member kind="function">
      <type>const std::string</type>
      <name>passfail</name>
      <anchorfile>group__Thyra__Op__Vec__ANA__Development__grp.html</anchorfile>
      <anchor>ga5958c955cd97673de9eb9de60ef7ad64</anchor>
      <arglist>(const bool result)</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::ScalarTraits&lt; Scalar &gt;::magnitudeType</type>
      <name>relErr</name>
      <anchorfile>group__Thyra__Op__Vec__ANA__Development__grp.html</anchorfile>
      <anchor>ga375ba1efd1f535c4c270454c8bd10615</anchor>
      <arglist>(const Scalar &amp;s1, const Scalar &amp;s2)</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::ScalarTraits&lt; Scalar &gt;::magnitudeType</type>
      <name>relVectorErr</name>
      <anchorfile>group__Thyra__Op__Vec__ANA__Development__grp.html</anchorfile>
      <anchor>ga0cd235482eb1f389c7d549c2d6dec9a5</anchor>
      <arglist>(const VectorBase&lt; Scalar &gt; &amp;v1, const VectorBase&lt; Scalar &gt; &amp;v2)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>testRelErrors</name>
      <anchorfile>group__Thyra__Op__Vec__ANA__Development__grp.html</anchorfile>
      <anchor>ga35b152aed20486df7cc8d6ba8cd4e935</anchor>
      <arglist>(const std::string &amp;v1_name, const ArrayView&lt; const Scalar1 &gt; &amp;v1, const std::string &amp;v2_name, const ArrayView&lt; const Scalar2 &gt; &amp;v2, const std::string &amp;maxRelErr_error_name, const ScalarMag &amp;maxRelErr_error, const std::string &amp;maxRelErr_warning_name, const ScalarMag &amp;maxRelErr_warning, const Ptr&lt; std::ostream &gt; &amp;out, const std::string &amp;leadingIndent=std::string(&quot;&quot;))</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>testRelNormDiffErr</name>
      <anchorfile>group__Thyra__Op__Vec__ANA__Development__grp.html</anchorfile>
      <anchor>gadcb3567faa6ff0fe76808f9b0e57d16b</anchor>
      <arglist>(const std::string &amp;v1_name, const VectorBase&lt; Scalar &gt; &amp;v1, const std::string &amp;v2_name, const VectorBase&lt; Scalar &gt; &amp;v2, const std::string &amp;maxRelErr_error_name, const typename Teuchos::ScalarTraits&lt; Scalar &gt;::magnitudeType &amp;maxRelErr_error, const std::string &amp;maxRelErr_warning_name, const typename Teuchos::ScalarTraits&lt; Scalar &gt;::magnitudeType &amp;maxRelErr_warning, std::ostream *out, const Teuchos::EVerbosityLevel verbLevel=Teuchos::VERB_LOW, const std::string &amp;leadingIndent=std::string(&quot;&quot;))</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>testMaxErr</name>
      <anchorfile>group__Thyra__Op__Vec__ANA__Development__grp.html</anchorfile>
      <anchor>gaff2a3761194adbfbc74cd96945d6e8bc</anchor>
      <arglist>(const std::string &amp;error_name, const Scalar &amp;error, const std::string &amp;max_error_name, const typename Teuchos::ScalarTraits&lt; Scalar &gt;::magnitudeType &amp;max_error, const std::string &amp;max_warning_name, const typename Teuchos::ScalarTraits&lt; Scalar &gt;::magnitudeType &amp;max_warning, std::ostream *out, const std::string &amp;leadingIndent=std::string(&quot;&quot;))</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>testMaxErrors</name>
      <anchorfile>group__Thyra__Op__Vec__ANA__Development__grp.html</anchorfile>
      <anchor>gac3c4aa282d9b37e18efd2c6427a1c009</anchor>
      <arglist>(const std::string &amp;error_name, const ArrayView&lt; const typename Teuchos::ScalarTraits&lt; Scalar &gt;::magnitudeType &gt; &amp;errors, const std::string &amp;max_error_name, const typename Teuchos::ScalarTraits&lt; Scalar &gt;::magnitudeType &amp;max_error, const std::string &amp;max_warning_name, const typename Teuchos::ScalarTraits&lt; Scalar &gt;::magnitudeType &amp;max_warning, const Ptr&lt; std::ostream &gt; &amp;out, const std::string &amp;leadingIndent=std::string(&quot;&quot;))</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>testBoolExpr</name>
      <anchorfile>group__Thyra__Op__Vec__ANA__Development__grp.html</anchorfile>
      <anchor>ga79a50c8a6a0be559fdba1c2a7f5a15e0</anchor>
      <arglist>(const std::string &amp;boolExprName, const bool &amp;boolExpr, const bool &amp;boolExpected, const Ptr&lt; std::ostream &gt; &amp;out, const std::string &amp;leadingIndent=std::string(&quot;&quot;))</arglist>
    </member>
    <member kind="function">
      <type>std::ostream &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>group__Thyra__Op__Vec__ANA__Development__grp.html</anchorfile>
      <anchor>ga463e42ab63f4ba766172c8da6d4db08c</anchor>
      <arglist>(std::ostream &amp;o, const VectorBase&lt; Scalar &gt; &amp;v)</arglist>
    </member>
    <member kind="function">
      <type>std::ostream &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>group__Thyra__Op__Vec__ANA__Development__grp.html</anchorfile>
      <anchor>ga21d2b4bfeb0093a17092768fa8808d53</anchor>
      <arglist>(std::ostream &amp;o, const LinearOpBase&lt; Scalar &gt; &amp;M)</arglist>
    </member>
    <docanchor file="group__Thyra__Op__Vec__ANA__Development__grp" title="Overview of Using Thyra Software for Development of ANA Software">Thyra_Op_Vec_ANA_Development_overview_sec</docanchor>
    <docanchor file="group__Thyra__Op__Vec__ANA__Development__grp" title="Examples of Abstract Numerical Algorithms">Thyra_Op_Vec_ANA_Development_examples_sec</docanchor>
    <docanchor file="group__Thyra__Op__Vec__ANA__Development__grp" title="Other Use Cases">Thyra_Op_Vec_ANA_Development_other_sec</docanchor>
  </compound>
  <compound kind="group">
    <name>Thyra_Op_Vec_Adapters_grp</name>
    <title>Development of Concrete Thyra Operator/Vector Subclass Implementations (Adapter Support)</title>
    <filename>group__Thyra__Op__Vec__Adapters__grp.html</filename>
    <subgroup>Thyra_Op_Vec_general_adapter_support_code_grp</subgroup>
    <subgroup>Thyra_Op_Vec_basic_adapter_support_grp</subgroup>
    <subgroup>Thyra_Op_Vec_spmd_adapters_grp</subgroup>
    <docanchor file="group__Thyra__Op__Vec__Adapters__grp" title="Overview of Concrete Thyra Subclass Implementations">Thyra_Op_Vec_Adapters_overview_sec</docanchor>
    <docanchor file="group__Thyra__Op__Vec__Adapters__grp" title="Other Use Cases">Thyra_Op_Vec_Adapters_other_sec</docanchor>
  </compound>
  <compound kind="group">
    <name>Thyra_Op_Vec_general_adapter_support_code_grp</name>
    <title>Miscellaneous Support Code for Developing Thyra Operator/Vector Subclass Implementations</title>
    <filename>group__Thyra__Op__Vec__general__adapter__support__code__grp.html</filename>
    <member kind="function">
      <type>void</type>
      <name>apply_op_validate_input</name>
      <anchorfile>group__Thyra__Op__Vec__general__adapter__support__code__grp.html</anchorfile>
      <anchor>ga471406cf8f510a01a3238ee20e43f730</anchor>
      <arglist>(const std::string &amp;func_name, const VectorSpaceBase&lt; Scalar &gt; &amp;space, const RTOpPack::RTOpT&lt; Scalar &gt; &amp;op, const ArrayView&lt; const Ptr&lt; const VectorBase&lt; Scalar &gt; &gt; &gt; &amp;vecs, const ArrayView&lt; const Ptr&lt; VectorBase&lt; Scalar &gt; &gt; &gt; &amp;targ_vecs, const Ptr&lt; RTOpPack::ReductTarget &gt; &amp;reduct_obj, const Ordinal global_offset)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>apply_op_validate_input</name>
      <anchorfile>group__Thyra__Op__Vec__general__adapter__support__code__grp.html</anchorfile>
      <anchor>ga76c8eb10f3a9d62c0bba92a8dbb241a9</anchor>
      <arglist>(const std::string &amp;func_name, const VectorSpaceBase&lt; Scalar &gt; &amp;domain, const VectorSpaceBase&lt; Scalar &gt; &amp;range, const RTOpPack::RTOpT&lt; Scalar &gt; &amp;primary_op, const ArrayView&lt; const Ptr&lt; const MultiVectorBase&lt; Scalar &gt; &gt; &gt; &amp;multi_vecs, const ArrayView&lt; const Ptr&lt; MultiVectorBase&lt; Scalar &gt; &gt; &gt; &amp;targ_multi_vecs, const ArrayView&lt; const Ptr&lt; RTOpPack::ReductTarget &gt; &gt; &amp;reduct_objs, const Ordinal primary_global_offset)</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>Thyra_Op_Vec_basic_adapter_support_grp</name>
    <title>Basic Support Subclasses Abstracting Application-Specific Scalar Products</title>
    <filename>group__Thyra__Op__Vec__basic__adapter__support__grp.html</filename>
    <class kind="class">Thyra::EuclideanScalarProd</class>
    <class kind="class">Thyra::LinearOpScalarProd</class>
    <class kind="class">Thyra::MultiVectorAdapterBase</class>
    <class kind="class">Thyra::ScalarProdBase</class>
    <class kind="class">Thyra::ScalarProdVectorSpaceBase</class>
  </compound>
  <compound kind="group">
    <name>Thyra_Op_Vec_spmd_adapters_grp</name>
    <title>Thyra Operator/Vector Subclasses for SPMD Distributed-Memory Platforms</title>
    <filename>group__Thyra__Op__Vec__spmd__adapters__grp.html</filename>
    <subgroup>Thyra_Op_Vec_adapters_Spmd_support_grp</subgroup>
    <subgroup>Thyra_Op_Vec_adapters_Spmd_concrete_std_grp</subgroup>
    <subgroup>Thyra_Op_Vec_adapters_spmd_local_data_access_grp</subgroup>
    <class kind="class">Thyra::ConstDetachedSpmdVectorView</class>
    <class kind="class">Thyra::DetachedSpmdVectorView</class>
    <docanchor file="group__Thyra__Op__Vec__spmd__adapters__grp" title="Subclasses for SPMD Thyra Implementations">Thyra_Op_Vec_spmd_adapters_classes_sec</docanchor>
  </compound>
  <compound kind="group">
    <name>Thyra_Op_Vec_adapters_Spmd_support_grp</name>
    <title>Thyra Operator/Vector Base Support Subclasses for SPMD Thyra Implementations</title>
    <filename>group__Thyra__Op__Vec__adapters__Spmd__support__grp.html</filename>
    <class kind="class">Thyra::SerialVectorSpaceConverterBase</class>
    <class kind="class">Thyra::SpmdMultiVectorDefaultBase</class>
    <class kind="class">Thyra::SpmdVectorDefaultBase</class>
    <class kind="class">Thyra::SpmdVectorSpaceDefaultBase</class>
  </compound>
  <compound kind="group">
    <name>Thyra_Op_Vec_adapters_Spmd_concrete_std_grp</name>
    <title>Efficient Generic SPMD Concrete Thyra Operator/Vector Subclass Implementations</title>
    <filename>group__Thyra__Op__Vec__adapters__Spmd__concrete__std__grp.html</filename>
    <class kind="class">Thyra::DefaultClusteredSpmdProductVector</class>
    <class kind="class">Thyra::DefaultClusteredSpmdProductVectorSpace</class>
    <class kind="class">Thyra::DefaultSerialVectorSpaceConverter</class>
    <class kind="class">Thyra::DefaultSpmdMultiVector</class>
    <class kind="class">Thyra::DefaultSpmdMultiVectorFileIO</class>
    <class kind="class">Thyra::DefaultSpmdVector</class>
    <class kind="class">Thyra::DefaultSpmdVectorSpace</class>
    <class kind="class">Thyra::DefaultSpmdVectorSpaceFactory</class>
    <class kind="class">Thyra::SpmdMultiVectorSerializer</class>
    <docanchor file="group__Thyra__Op__Vec__adapters__Spmd__concrete__std__grp" title="Concrete SPMD Subclasses">Thyra_Op_Vec_adapters_Spmd_concrete_std_classes_grp</docanchor>
  </compound>
  <compound kind="group">
    <name>OperatorVectorANASupportSoftware_grp</name>
    <title>Operator/Solve ANA Support Software</title>
    <filename>group__OperatorVectorANASupportSoftware__grp.html</filename>
  </compound>
  <compound kind="group">
    <name>Thyra_Nonlin_support_grp</name>
    <title>Thyra nonlinear support</title>
    <filename>group__Thyra__Nonlin__support__grp.html</filename>
    <subgroup>Thyra_Nonlin_ME_support_grp</subgroup>
    <subgroup>Thyra_Nonlin_ME_solvers_grp</subgroup>
  </compound>
  <compound kind="group">
    <name>Thyra_Nonlin_ME_support_grp</name>
    <title>Thyra nonlinear model-evaluator support</title>
    <filename>group__Thyra__Nonlin__ME__support__grp.html</filename>
    <class kind="class">Thyra::DefaultEvaluationLoggerModelEvaluator</class>
    <class kind="class">Thyra::DefaultFinalPointCaptureModelEvaluator</class>
    <class kind="class">Thyra::DefaultFiniteDifferenceModelEvaluator</class>
    <class kind="class">Thyra::DefaultInverseModelEvaluator</class>
    <class kind="class">Thyra::DefaultLumpedParameterModelEvaluator</class>
    <class kind="class">Thyra::DefaultModelEvaluatorWithSolveFactory</class>
    <class kind="class">Thyra::DefaultMultiPeriodModelEvaluator</class>
    <class kind="class">Thyra::DefaultNominalBoundsOverrideModelEvaluator</class>
    <class kind="class">Thyra::DirectionalFiniteDiffCalculator</class>
    <class kind="class">Thyra::ModelEvaluatorDelegatorBase</class>
    <class kind="class">Thyra::ResponseOnlyModelEvaluatorBase</class>
    <class kind="class">Thyra::ScaledModelEvaluator</class>
    <class kind="class">Thyra::StateFuncModelEvaluatorBase</class>
  </compound>
  <compound kind="group">
    <name>Thyra_Nonlin_ME_solvers_grp</name>
    <title>Thyra nonlinear solver support</title>
    <filename>group__Thyra__Nonlin__ME__solvers__grp.html</filename>
    <class kind="class">Thyra::DampenedNewtonNonlinearSolver</class>
    <class kind="class">Thyra::DefaultNonlinearSolverBuilder</class>
    <class kind="class">Thyra::DefaultStateEliminationModelEvaluator</class>
    <class kind="class">Thyra::LinearNonlinearSolver</class>
  </compound>
  <compound kind="group">
    <name>thyra_adapters_grp</name>
    <title>Thyra adapters</title>
    <filename>group__thyra__adapters__grp.html</filename>
    <subgroup>Epetra_Thyra_Op_Vec_adapters_grp</subgroup>
    <subgroup>Tpetra_Thyra_Op_Vec_adapters_grp</subgroup>
    <subgroup>EpetraExt_Thyra_Op_Vec_adapters_grp</subgroup>
  </compound>
  <compound kind="group">
    <name>Epetra_Thyra_Op_Vec_adapters_grp</name>
    <title>Thyra/Epetra Operator/Vector Adapter Code</title>
    <filename>group__Epetra__Thyra__Op__Vec__adapters__grp.html</filename>
    <class kind="class">Thyra::DiagonalEpetraLinearOpWithSolveFactory</class>
    <class kind="class">Thyra::EpetraLinearOp</class>
    <class kind="class">Thyra::EpetraLinearOpBase</class>
    <class kind="class">Thyra::EpetraOperatorViewExtractorBase</class>
    <class kind="class">Thyra::EpetraOperatorViewExtractorStd</class>
    <class kind="class">Thyra::EpetraOperatorWrapper</class>
    <member kind="enumeration">
      <type></type>
      <name>EAdjointEpetraOp</name>
      <anchorfile>group__Epetra__Thyra__Op__Vec__adapters__grp.html</anchorfile>
      <anchor>gac23b0307c1143c9ecc5d25d42b4295ed</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>EPETRA_OP_ADJOINT_SUPPORTED</name>
      <anchorfile>group__Epetra__Thyra__Op__Vec__adapters__grp.html</anchorfile>
      <anchor>ggac23b0307c1143c9ecc5d25d42b4295edac838b0606e891c9910c6b662ffc5f900</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>EPETRA_OP_ADJOINT_UNSUPPORTED</name>
      <anchorfile>group__Epetra__Thyra__Op__Vec__adapters__grp.html</anchorfile>
      <anchor>ggac23b0307c1143c9ecc5d25d42b4295edab0d6d32ac655f603bcd5099360c1951f</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>EApplyEpetraOpAs</name>
      <anchorfile>group__Epetra__Thyra__Op__Vec__adapters__grp.html</anchorfile>
      <anchor>ga34dceb459f42810d4470c6c5555e4299</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>EPETRA_OP_APPLY_APPLY</name>
      <anchorfile>group__Epetra__Thyra__Op__Vec__adapters__grp.html</anchorfile>
      <anchor>gga34dceb459f42810d4470c6c5555e4299a1c134d6bbe5d5d371192b43afc93a8df</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>EPETRA_OP_APPLY_APPLY_INVERSE</name>
      <anchorfile>group__Epetra__Thyra__Op__Vec__adapters__grp.html</anchorfile>
      <anchor>gga34dceb459f42810d4470c6c5555e4299ac42819b74281b539acf9e98ac159f157</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const Teuchos::Comm&lt; Ordinal &gt; &gt;</type>
      <name>create_Comm</name>
      <anchorfile>group__Epetra__Thyra__Op__Vec__adapters__grp.html</anchorfile>
      <anchor>ga68f1d41c29d1251b5e171dfb8d876435</anchor>
      <arglist>(const RCP&lt; const Epetra_Comm &gt; &amp;epetraComm)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const VectorSpaceBase&lt; double &gt; &gt;</type>
      <name>create_VectorSpace</name>
      <anchorfile>group__Epetra__Thyra__Op__Vec__adapters__grp.html</anchorfile>
      <anchor>ga6f31a91efce616677a66d162c9b03805</anchor>
      <arglist>(const RCP&lt; const Epetra_Map &gt; &amp;epetra_map)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const VectorSpaceBase&lt; double &gt; &gt;</type>
      <name>create_LocallyReplicatedVectorSpace</name>
      <anchorfile>group__Epetra__Thyra__Op__Vec__adapters__grp.html</anchorfile>
      <anchor>gad20c20b3c0c8c14c5236ea7b7e34fdc1</anchor>
      <arglist>(const RCP&lt; const VectorSpaceBase&lt; double &gt; &gt; &amp;parentSpace, const int dim)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; VectorBase&lt; double &gt; &gt;</type>
      <name>create_Vector</name>
      <anchorfile>group__Epetra__Thyra__Op__Vec__adapters__grp.html</anchorfile>
      <anchor>ga1f3b0bf703c3b35237bac513b3ff5e21</anchor>
      <arglist>(const RCP&lt; Epetra_Vector &gt; &amp;epetra_v, const RCP&lt; const VectorSpaceBase&lt; double &gt; &gt; &amp;space)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const VectorBase&lt; double &gt; &gt;</type>
      <name>create_Vector</name>
      <anchorfile>group__Epetra__Thyra__Op__Vec__adapters__grp.html</anchorfile>
      <anchor>ga84d2b4aec5f2c5980b9b8cc207ca5a08</anchor>
      <arglist>(const RCP&lt; const Epetra_Vector &gt; &amp;epetra_v, const RCP&lt; const VectorSpaceBase&lt; double &gt; &gt; &amp;space)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; MultiVectorBase&lt; double &gt; &gt;</type>
      <name>create_MultiVector</name>
      <anchorfile>group__Epetra__Thyra__Op__Vec__adapters__grp.html</anchorfile>
      <anchor>ga35817c2b80660344e4c3e609653805a2</anchor>
      <arglist>(const RCP&lt; Epetra_MultiVector &gt; &amp;epetra_mv, const RCP&lt; const VectorSpaceBase&lt; double &gt; &gt; &amp;range, const RCP&lt; const VectorSpaceBase&lt; double &gt; &gt; &amp;domain=Teuchos::null)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const MultiVectorBase&lt; double &gt; &gt;</type>
      <name>create_MultiVector</name>
      <anchorfile>group__Epetra__Thyra__Op__Vec__adapters__grp.html</anchorfile>
      <anchor>ga231b01e7764cb7f780cc173e2c8a6cb5</anchor>
      <arglist>(const RCP&lt; const Epetra_MultiVector &gt; &amp;epetra_mv, const RCP&lt; const VectorSpaceBase&lt; double &gt; &gt; &amp;range, const RCP&lt; const VectorSpaceBase&lt; double &gt; &gt; &amp;domain=Teuchos::null)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const Epetra_Comm &gt;</type>
      <name>get_Epetra_Comm</name>
      <anchorfile>group__Epetra__Thyra__Op__Vec__adapters__grp.html</anchorfile>
      <anchor>ga3a1a44a4e90cc4eaf7192f46d66c47b0</anchor>
      <arglist>(const Teuchos::Comm&lt; Ordinal &gt; &amp;comm)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const Epetra_Map &gt;</type>
      <name>get_Epetra_Map</name>
      <anchorfile>group__Epetra__Thyra__Op__Vec__adapters__grp.html</anchorfile>
      <anchor>gaa63557fbffcf1b7190761b47deabd04b</anchor>
      <arglist>(const VectorSpaceBase&lt; double &gt; &amp;vs, const RCP&lt; const Epetra_Comm &gt; &amp;comm)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; Epetra_Vector &gt;</type>
      <name>get_Epetra_Vector</name>
      <anchorfile>group__Epetra__Thyra__Op__Vec__adapters__grp.html</anchorfile>
      <anchor>gaa2c3bd82b0b6ea7e646aa08831aa0252</anchor>
      <arglist>(const Epetra_Map &amp;map, const RCP&lt; VectorBase&lt; double &gt; &gt; &amp;v)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const Epetra_Vector &gt;</type>
      <name>get_Epetra_Vector</name>
      <anchorfile>group__Epetra__Thyra__Op__Vec__adapters__grp.html</anchorfile>
      <anchor>gac98405c4e1407b2967e684d1393955c0</anchor>
      <arglist>(const Epetra_Map &amp;map, const RCP&lt; const VectorBase&lt; double &gt; &gt; &amp;v)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; Epetra_MultiVector &gt;</type>
      <name>get_Epetra_MultiVector</name>
      <anchorfile>group__Epetra__Thyra__Op__Vec__adapters__grp.html</anchorfile>
      <anchor>gabe4a8cd77325734357b49733f9f751b0</anchor>
      <arglist>(const Epetra_Map &amp;map, const RCP&lt; MultiVectorBase&lt; double &gt; &gt; &amp;mv)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const Epetra_MultiVector &gt;</type>
      <name>get_Epetra_MultiVector</name>
      <anchorfile>group__Epetra__Thyra__Op__Vec__adapters__grp.html</anchorfile>
      <anchor>ga97677e36ca83f50043c0e3db0ff75022</anchor>
      <arglist>(const Epetra_Map &amp;map, const RCP&lt; const MultiVectorBase&lt; double &gt; &gt; &amp;mv)</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; Epetra_MultiVector &gt;</type>
      <name>get_Epetra_MultiVector</name>
      <anchorfile>group__Epetra__Thyra__Op__Vec__adapters__grp.html</anchorfile>
      <anchor>ga50422b34dc6ead91529aa213478632ec</anchor>
      <arglist>(const Epetra_Map &amp;map, MultiVectorBase&lt; double &gt; &amp;mv)</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Epetra_MultiVector &gt;</type>
      <name>get_Epetra_MultiVector</name>
      <anchorfile>group__Epetra__Thyra__Op__Vec__adapters__grp.html</anchorfile>
      <anchor>gab800f5abe4ff1e7cbd2c9230805cae8c</anchor>
      <arglist>(const Epetra_Map &amp;map, const MultiVectorBase&lt; double &gt; &amp;mv)</arglist>
    </member>
    <member kind="function">
      <type>const std::string</type>
      <name>toString</name>
      <anchorfile>group__Epetra__Thyra__Op__Vec__adapters__grp.html</anchorfile>
      <anchor>ga8a2ed6e204fc73324451e843124200a2</anchor>
      <arglist>(const EAdjointEpetraOp adjointEpetraOp)</arglist>
    </member>
    <member kind="function">
      <type>const std::string</type>
      <name>toString</name>
      <anchorfile>group__Epetra__Thyra__Op__Vec__adapters__grp.html</anchorfile>
      <anchor>gade1f51a7059d915d2b7447a647912165</anchor>
      <arglist>(const EApplyEpetraOpAs applyEpetraOpAs)</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; Epetra_Operator &gt;</type>
      <name>get_Epetra_Operator</name>
      <anchorfile>group__Epetra__Thyra__Op__Vec__adapters__grp.html</anchorfile>
      <anchor>ga2cd2dd4106b5d50dbd0781d29b446d07</anchor>
      <arglist>(LinearOpBase&lt; Scalar &gt; &amp;)</arglist>
    </member>
    <member kind="function">
      <type>Teuchos::RCP&lt; const Epetra_Operator &gt;</type>
      <name>get_Epetra_Operator</name>
      <anchorfile>group__Epetra__Thyra__Op__Vec__adapters__grp.html</anchorfile>
      <anchor>ga3b65fea8d40e7ed797ef0b33fd90bd91</anchor>
      <arglist>(const LinearOpBase&lt; Scalar &gt; &amp;)</arglist>
    </member>
    <docanchor file="group__Epetra__Thyra__Op__Vec__adapters__grp" title="Examples">Epetra_Thyra_Op_Vec_examples_sec</docanchor>
  </compound>
  <compound kind="group">
    <name>Tpetra_Thyra_Op_Vec_adapters_grp</name>
    <title>Thyra/Tpetra Operator/Vector Adapter Code</title>
    <filename>group__Tpetra__Thyra__Op__Vec__adapters__grp.html</filename>
    <class kind="class">Thyra::TpetraLinearOp</class>
    <class kind="class">Thyra::TpetraMultiVector</class>
    <class kind="class">Thyra::TpetraOperatorVectorExtraction</class>
    <class kind="class">Thyra::TpetraVector</class>
    <class kind="class">Thyra::TpetraVectorSpace</class>
    <member kind="function">
      <type>RCP&lt; const Teuchos::Comm&lt; Ordinal &gt; &gt;</type>
      <name>convertTpetraToThyraComm</name>
      <anchorfile>group__Tpetra__Thyra__Op__Vec__adapters__grp.html</anchorfile>
      <anchor>gae07882a38263547a72baac70ebc4c3a8</anchor>
      <arglist>(const RCP&lt; const Teuchos::Comm&lt; int &gt; &gt; &amp;tpetraComm)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const VectorSpaceBase&lt; Scalar &gt; &gt;</type>
      <name>createVectorSpace</name>
      <anchorfile>group__Tpetra__Thyra__Op__Vec__adapters__grp.html</anchorfile>
      <anchor>ga814c55c5754f024a8516f90fc6035c30</anchor>
      <arglist>(const RCP&lt; const Tpetra::Map&lt; LocalOrdinal, GlobalOrdinal, Node &gt; &gt; &amp;tpetraMap)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; VectorBase&lt; Scalar &gt; &gt;</type>
      <name>createVector</name>
      <anchorfile>group__Tpetra__Thyra__Op__Vec__adapters__grp.html</anchorfile>
      <anchor>ga2872f0b6d35ebac0100be381ac79a209</anchor>
      <arglist>(const RCP&lt; Tpetra::Vector&lt; Scalar, LocalOrdinal, GlobalOrdinal, Node &gt; &gt; &amp;tpetraVector, const RCP&lt; const VectorSpaceBase&lt; Scalar &gt; &gt; space=Teuchos::null)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const VectorBase&lt; Scalar &gt; &gt;</type>
      <name>createConstVector</name>
      <anchorfile>group__Tpetra__Thyra__Op__Vec__adapters__grp.html</anchorfile>
      <anchor>gaa8dbb88c6f16fecebfa06768e2eddd34</anchor>
      <arglist>(const RCP&lt; const Tpetra::Vector&lt; Scalar, LocalOrdinal, GlobalOrdinal, Node &gt; &gt; &amp;tpetraVector, const RCP&lt; const VectorSpaceBase&lt; Scalar &gt; &gt; space=Teuchos::null)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; MultiVectorBase&lt; Scalar &gt; &gt;</type>
      <name>createMultiVector</name>
      <anchorfile>group__Tpetra__Thyra__Op__Vec__adapters__grp.html</anchorfile>
      <anchor>ga404afd06973fe34a9293f8bb42d34806</anchor>
      <arglist>(const RCP&lt; Tpetra::MultiVector&lt; Scalar, LocalOrdinal, GlobalOrdinal, Node &gt; &gt; &amp;tpetraMultiVector, const RCP&lt; const VectorSpaceBase&lt; Scalar &gt; &gt; rangeSpace=Teuchos::null, const RCP&lt; const VectorSpaceBase&lt; Scalar &gt; &gt; domainSpace=Teuchos::null)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const MultiVectorBase&lt; Scalar &gt; &gt;</type>
      <name>createConstMultiVector</name>
      <anchorfile>group__Tpetra__Thyra__Op__Vec__adapters__grp.html</anchorfile>
      <anchor>gacf34fb299717be41613ded3aae88cf11</anchor>
      <arglist>(const RCP&lt; const Tpetra::MultiVector&lt; Scalar, LocalOrdinal, GlobalOrdinal, Node &gt; &gt; &amp;tpetraMultiVector, const RCP&lt; const VectorSpaceBase&lt; Scalar &gt; &gt; rangeSpace=Teuchos::null, const RCP&lt; const VectorSpaceBase&lt; Scalar &gt; &gt; domainSpace=Teuchos::null)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; LinearOpBase&lt; Scalar &gt; &gt;</type>
      <name>createLinearOp</name>
      <anchorfile>group__Tpetra__Thyra__Op__Vec__adapters__grp.html</anchorfile>
      <anchor>ga3e890d6d4912a0f18ead9f8275f93b1e</anchor>
      <arglist>(const RCP&lt; Tpetra::Operator&lt; Scalar, LocalOrdinal, GlobalOrdinal, Node &gt; &gt; &amp;tpetraOperator, const RCP&lt; const VectorSpaceBase&lt; Scalar &gt; &gt; rangeSpace=Teuchos::null, const RCP&lt; const VectorSpaceBase&lt; Scalar &gt; &gt; domainSpace=Teuchos::null)</arglist>
    </member>
    <member kind="function">
      <type>RCP&lt; const LinearOpBase&lt; Scalar &gt; &gt;</type>
      <name>createConstLinearOp</name>
      <anchorfile>group__Tpetra__Thyra__Op__Vec__adapters__grp.html</anchorfile>
      <anchor>ga09990c9dc6e84351c6b79ff13e9a658f</anchor>
      <arglist>(const RCP&lt; const Tpetra::Operator&lt; Scalar, LocalOrdinal, GlobalOrdinal, Node &gt; &gt; &amp;tpetraOperator, const RCP&lt; const VectorSpaceBase&lt; Scalar &gt; &gt; rangeSpace=Teuchos::null, const RCP&lt; const VectorSpaceBase&lt; Scalar &gt; &gt; domainSpace=Teuchos::null)</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>EpetraExt_Thyra_Op_Vec_adapters_grp</name>
    <title>Thyra/EpetraExt Adapter Code</title>
    <filename>group__EpetraExt__Thyra__Op__Vec__adapters__grp.html</filename>
    <class kind="class">Thyra::EpetraModelEvaluator</class>
    <class kind="class">Thyra::EpetraExtAddTransformer</class>
    <class kind="class">Thyra::EpetraExtDiagScaledMatProdTransformer</class>
    <class kind="class">Thyra::EpetraExtDiagScalingTransformer</class>
  </compound>
  <compound kind="group">
    <name>Thyra_deprecated_grp</name>
    <title>Thyra deprecated software</title>
    <filename>group__Thyra__deprecated__grp.html</filename>
  </compound>
  <compound kind="group">
    <name>Thyra_Op_Vec_adapters_spmd_local_data_access_grp</name>
    <title>Official utilities for accessing local data in SPMD vectors and multi-vectors.</title>
    <filename>group__Thyra__Op__Vec__adapters__spmd__local__data__access__grp.html</filename>
    <member kind="function">
      <type>RTOpPack::SubVectorView&lt; Scalar &gt;</type>
      <name>getNonconstLocalSubVectorView</name>
      <anchorfile>group__Thyra__Op__Vec__adapters__spmd__local__data__access__grp.html</anchorfile>
      <anchor>gac3aef4b00e7f1030c151338f7b5cd17b</anchor>
      <arglist>(const RCP&lt; VectorBase&lt; Scalar &gt; &gt; &amp;vec)</arglist>
    </member>
    <member kind="function">
      <type>RTOpPack::ConstSubVectorView&lt; Scalar &gt;</type>
      <name>getLocalSubVectorView</name>
      <anchorfile>group__Thyra__Op__Vec__adapters__spmd__local__data__access__grp.html</anchorfile>
      <anchor>gaff875910caa762feb25f312a249afc85</anchor>
      <arglist>(const RCP&lt; const VectorBase&lt; Scalar &gt; &gt; &amp;vec)</arglist>
    </member>
    <member kind="function">
      <type>RTOpPack::SubMultiVectorView&lt; Scalar &gt;</type>
      <name>getNonconstLocalSubMultiVectorView</name>
      <anchorfile>group__Thyra__Op__Vec__adapters__spmd__local__data__access__grp.html</anchorfile>
      <anchor>gafe39a3876c56e57454d7a65a80e17d88</anchor>
      <arglist>(const RCP&lt; MultiVectorBase&lt; Scalar &gt; &gt; &amp;multivec)</arglist>
    </member>
    <member kind="function">
      <type>RTOpPack::ConstSubMultiVectorView&lt; Scalar &gt;</type>
      <name>getLocalSubMultiVectorView</name>
      <anchorfile>group__Thyra__Op__Vec__adapters__spmd__local__data__access__grp.html</anchorfile>
      <anchor>ga0abcd74dd4a7b0097323fc42e25e6a12</anchor>
      <arglist>(const RCP&lt; const MultiVectorBase&lt; Scalar &gt; &gt; &amp;multivec)</arglist>
    </member>
  </compound>
  <compound kind="page">
    <name>index</name>
    <title>Thyra : Interfaces and Support code for Abstract Numerical Algorithms (ANAs)</title>
    <filename>index</filename>
    <docanchor file="index" title="Outline">thyra_outline_sec</docanchor>
    <docanchor file="index" title="Introduction">thyra_intro_sec</docanchor>
    <docanchor file="index" title="Thyra interoperability interfaces">thyra_interfaces_sec</docanchor>
    <docanchor file="index" title="Operator/Vector Interfaces">thyra_interfaces_operator_vector_sec</docanchor>
    <docanchor file="index" title="Operator Solve Interfaces">thyra_interfaces_operator_solve_sec</docanchor>
    <docanchor file="index" title="Nonlinear Interfaces">thyra_interfaces_nonlinear_sec</docanchor>
    <docanchor file="index" title="Thyra support software and examples">thyra_support_sec</docanchor>
    <docanchor file="index" title="Operator/Vector Support">thyra_support_operator_vector_sec</docanchor>
    <docanchor file="index" title="Operator Solve Support">thyra_support_operator_solve_sec</docanchor>
    <docanchor file="index" title="Nonlinear Model Evaluator Support">thyra_support_nonlinear_model_evaluator_sec</docanchor>
    <docanchor file="index" title="Nonlinear Solvers Support">thyra_support_nonlinear_solvers_sec</docanchor>
    <docanchor file="index" title="Thyra adapters to other packages">thyra_adapters_sec</docanchor>
    <docanchor file="index" title="Thyra/Epetra adapters">thyra_adapters_epetra_sec</docanchor>
    <docanchor file="index" title="Thyra/Tpetra adapters">thyra_adapters_tpetra_sec</docanchor>
    <docanchor file="index" title="Thyra/EpetraExt adapters">thyra_adapters_epetraext_sec</docanchor>
    <docanchor file="index" title="Browse all of Thyra as a single doxygen collection">thyra_browse_sec</docanchor>
    <docanchor file="index" title="Some Technicalities about Thyra Software">thyra_software_technicalities_sec</docanchor>
    <docanchor file="index" title="Other Trilinos Packages on which Thyra Depends">thyra_dependencies_sec</docanchor>
    <docanchor file="index" title="Configuration of the Thyra Package">thyra_configuration_sec</docanchor>
    <docanchor file="index" title="Frequently Asked Questions (FAQ)">thyra_faq_sec</docanchor>
    <docanchor file="index" title="Documents Describing or are Related to Thyra">thyra_documents_sec</docanchor>
    <docanchor file="index" title="Contributors to the Thyra Package and Related Software">thyra_contributors_sec</docanchor>
    <docanchor file="index" title="Other Software Related to Thyra">thyra_related_software_sec</docanchor>
    <docanchor file="index" title="Outline">Teuchos_outline</docanchor>
    <docanchor file="index" title="Introduction">Teuchos_intro</docanchor>
    <docanchor file="index" title="Teuchos Contributors">Teuchos_contributors</docanchor>
    <docanchor file="index" title="Summary of Teuchos&apos; Configuration Options">Teuchos_config_options</docanchor>
    <docanchor file="index" title="Overview of Teuchos Subpackages">Teuchos_startup</docanchor>
    <docanchor file="index" title="Teuchos Core Subpackage">TeuchosCore_src</docanchor>
    <docanchor file="index" title="Teuchos ParameterList Subpackage">TeuchosParameterList_src</docanchor>
    <docanchor file="index" title="Teuchos Communication Subpackage">TeuchosComm_src</docanchor>
    <docanchor file="index" title="Teuchos Numerics Subpackage">TeuchosNumerics_src</docanchor>
    <docanchor file="index" title="Teuchos Remainder Subpackage">TeuchosRemainder_src</docanchor>
    <docanchor file="index" title="Browse all of Teuchos">Teuchos_browser</docanchor>
    <docanchor file="index" title="Software">RTOp_interface_software_sec</docanchor>
    <docanchor file="index" title="Links">RTOp_interface_links_sec</docanchor>
    <docanchor file="index" title="Software">RTOp_support_software_sec</docanchor>
    <docanchor file="index" title="Links">RTOp_support_links_sec</docanchor>
    <docanchor file="index" title="Software">RTOp_ops_lib_software_sec</docanchor>
    <docanchor file="index" title="Links">RTOp_ops_lib_links_sec</docanchor>
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
