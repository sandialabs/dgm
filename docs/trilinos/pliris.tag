<?xml version='1.0' encoding='UTF-8' standalone='yes' ?>
<tagfile>
  <compound kind="file">
    <name>PlirisVersion.cpp</name>
    <path>/Users/sscoll/dist/trilinos/packages/pliris/src/</path>
    <filename>PlirisVersion_8cpp</filename>
  </compound>
  <compound kind="struct">
    <name>pivot_type</name>
    <filename>structpivot__type.html</filename>
  </compound>
  <compound kind="class">
    <name>Pliris</name>
    <filename>classPliris.html</filename>
    <member kind="function">
      <type></type>
      <name>Pliris</name>
      <anchorfile>classPliris.html</anchorfile>
      <anchor>a52e46d36f4930e7b46c0358ef94b26da</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetLHS</name>
      <anchorfile>classPliris.html</anchorfile>
      <anchor>a1c31c2b4d97a5e5049cac5ac57c5fcb0</anchor>
      <arglist>(Epetra_MultiVector *X)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetRHS</name>
      <anchorfile>classPliris.html</anchorfile>
      <anchor>a489b610fa25acaae84abf5ca532b9bf3</anchor>
      <arglist>(Epetra_MultiVector *B)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetMatrix</name>
      <anchorfile>classPliris.html</anchorfile>
      <anchor>a376e729cb6aad13c6a04f0fcc0b9a5e7</anchor>
      <arglist>(Epetra_Vector *A)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetMatrix</name>
      <anchorfile>classPliris.html</anchorfile>
      <anchor>a57f30ede88471509829ecbd6995771a9</anchor>
      <arglist>(Epetra_SerialDenseVector *A)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetDistribution</name>
      <anchorfile>classPliris.html</anchorfile>
      <anchor>ae0b889a8c9ff2eafa2a3eb1907606f45</anchor>
      <arglist>(int *nprocs_row, int *number_of_unknowns, int *nrhs, int *my_rows, int *my_cols, int *my_first_row, int *my_first_col, int *my_rhs, int *my_row, int *my_col)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>FactorSolve</name>
      <anchorfile>classPliris.html</anchorfile>
      <anchor>a4173f651680defed847548458322dd68</anchor>
      <arglist>(Epetra_Vector *A, int my_rows, int my_cols, int *matrix_size, int *num_procsr, int *num_rhs, double *secs)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>FactorSolve</name>
      <anchorfile>classPliris.html</anchorfile>
      <anchor>a5a190f365264d2a23322dd4e1355ee36</anchor>
      <arglist>(Epetra_SerialDenseVector *AA, int my_rows, int my_cols, int *matrix_size, int *num_procsr, int *num_rhs, double *secs)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Factor</name>
      <anchorfile>classPliris.html</anchorfile>
      <anchor>a09897f08850c1325e0f5946f7e335f83</anchor>
      <arglist>(Epetra_Vector *A, int *matrix_size, int *num_procsr, int *permute, double *secs)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Solve</name>
      <anchorfile>classPliris.html</anchorfile>
      <anchor>af2f356125b864942c88824ac501a8fb9</anchor>
      <arglist>(int *permute, int *num_rhs)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~Pliris</name>
      <anchorfile>classPliris.html</anchorfile>
      <anchor>a70d73e9808d6e17708d63f4b515cc3f5</anchor>
      <arglist>(void)</arglist>
    </member>
  </compound>
  <compound kind="page">
    <name>index</name>
    <title>Trilinos/Pliris: Object-Oriented Interface to a Direct Matrix Solve (Dense matrices)</title>
    <filename>index</filename>
    <docanchor file="index" title="Introduction">intro</docanchor>
    <docanchor file="index" title="Overview of Pliris.">startup</docanchor>
    <docanchor file="index" title="Matrix Distribution">dense</docanchor>
    <docanchor file="index" title="Matrix Packing">densep</docanchor>
  </compound>
</tagfile>
