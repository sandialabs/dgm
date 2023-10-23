<?xml version='1.0' encoding='UTF-8' standalone='yes' ?>
<tagfile>
  <compound kind="file">
    <name>azk_create_linsys.c</name>
    <path>/Users/sscoll/dist/trilinos/packages/komplex/src/</path>
    <filename>azk__create__linsys_8c</filename>
    <includes id="azk__komplex_8h" name="azk_komplex.h" local="yes" imported="no">azk_komplex.h</includes>
    <member kind="function">
      <type>void</type>
      <name>AZK_create_linsys_c2k</name>
      <anchorfile>azk__create__linsys_8c.html</anchorfile>
      <anchor>a0d7ab66940d38b72c8bc6073292d6a91</anchor>
      <arglist>(double *xc, double *bc, int *options, double *params, int *proc_config, AZ_MATRIX *Amat_complex, double **x, double **b, AZ_MATRIX **Amat_komplex)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>AZK_create_linsys_g2k</name>
      <anchorfile>azk__create__linsys_8c.html</anchorfile>
      <anchor>a67745ee9fbf1ef1aacf5a3a8de0290bb</anchor>
      <arglist>(double *xr, double *xi, double *br, double *bi, int *options, double *params, int *proc_config, double c0r, double c0i, AZ_MATRIX *Amat_mat0, double c1r, double c1i, AZ_MATRIX *Amat_mat1, double **x, double **b, AZ_MATRIX **Amat_komplex)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>AZK_create_linsys_ri2k</name>
      <anchorfile>azk__create__linsys_8c.html</anchorfile>
      <anchor>a62c165f02bd064c3cb69559b83247fe9</anchor>
      <arglist>(double *xr, double *xi, double *br, double *bi, int *options, double *params, int *proc_config, AZ_MATRIX *Amat_real, double *val_imag, double **x, double **b, AZ_MATRIX **Amat_komplex)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>azk_create_matrix.c</name>
    <path>/Users/sscoll/dist/trilinos/packages/komplex/src/</path>
    <filename>azk__create__matrix_8c</filename>
    <includes id="azk__komplex_8h" name="azk_komplex.h" local="yes" imported="no">azk_komplex.h</includes>
    <member kind="function">
      <type>void</type>
      <name>AZK_create_matrix_c2k</name>
      <anchorfile>azk__create__matrix_8c.html</anchorfile>
      <anchor>ab10a09223c730d6be4fcc4367acc6b06</anchor>
      <arglist>(int options[], double params[], int proc_config[], AZ_MATRIX *Amat_complex, AZ_MATRIX **Amat_komplex)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>AZK_create_matrix_g2k</name>
      <anchorfile>azk__create__matrix_8c.html</anchorfile>
      <anchor>a13562601950b5d31c04ddd0c3be978fa</anchor>
      <arglist>(int options[], double params[], int proc_config[], double c0r, double c0i, AZ_MATRIX *Amat_mat0, double c1r, double c1i, AZ_MATRIX *Amat_mat1, AZ_MATRIX **Amat_komplex)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>AZK_create_matrix_ri2k</name>
      <anchorfile>azk__create__matrix_8c.html</anchorfile>
      <anchor>a0feb150d7072b9eebc8172c39917e9b4</anchor>
      <arglist>(int options[], double params[], int proc_config[], AZ_MATRIX *Amat_real, double *val_imag, AZ_MATRIX **Amat_komplex)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>azk_create_precon.c</name>
    <path>/Users/sscoll/dist/trilinos/packages/komplex/src/</path>
    <filename>azk__create__precon_8c</filename>
    <includes id="azk__komplex_8h" name="azk_komplex.h" local="yes" imported="no">azk_komplex.h</includes>
    <member kind="function">
      <type>void</type>
      <name>AZK_create_precon</name>
      <anchorfile>azk__create__precon_8c.html</anchorfile>
      <anchor>a7177cbc293fe1e21936b3c8fe6f18983</anchor>
      <arglist>(int *options, double *params, int *proc_config, double *x, double *b, AZ_MATRIX *Amat, AZ_PRECOND **Prec)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>azk_create_vector.c</name>
    <path>/Users/sscoll/dist/trilinos/packages/komplex/src/</path>
    <filename>azk__create__vector_8c</filename>
    <includes id="azk__komplex_8h" name="azk_komplex.h" local="yes" imported="no">azk_komplex.h</includes>
    <member kind="function">
      <type>void</type>
      <name>AZK_create_vector_c2k</name>
      <anchorfile>azk__create__vector_8c.html</anchorfile>
      <anchor>a91ae8163950942c308fbae61a3d61f4e</anchor>
      <arglist>(int *options, double *params, int *proc_config, AZ_MATRIX *Amat_komplex, double *vc, double **vk)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>AZK_create_vector_g2k</name>
      <anchorfile>azk__create__vector_8c.html</anchorfile>
      <anchor>a32bc998ab924bf196567f38e0bbf3a11</anchor>
      <arglist>(int *options, double *params, int *proc_config, AZ_MATRIX *Amat_komplex, double *vr, double *vi, double **vk)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>AZK_create_vector_ri2k</name>
      <anchorfile>azk__create__vector_8c.html</anchorfile>
      <anchor>a068c6f1b45c8ec923cac8085af39849b</anchor>
      <arglist>(int *options, double *params, int *proc_config, AZ_MATRIX *Amat_komplex, double *vr, double *vi, double **vk)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>azk_destroy_linsys.c</name>
    <path>/Users/sscoll/dist/trilinos/packages/komplex/src/</path>
    <filename>azk__destroy__linsys_8c</filename>
    <includes id="azk__komplex_8h" name="azk_komplex.h" local="yes" imported="no">azk_komplex.h</includes>
    <member kind="function">
      <type>void</type>
      <name>AZK_destroy_linsys</name>
      <anchorfile>azk__destroy__linsys_8c.html</anchorfile>
      <anchor>ab7983f9321543d976c9cc8a3dc00a1ae</anchor>
      <arglist>(int *options, double *params, int *proc_config, double **x, double **b, AZ_MATRIX **Amat_komplex)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>azk_destroy_matrix.c</name>
    <path>/Users/sscoll/dist/trilinos/packages/komplex/src/</path>
    <filename>azk__destroy__matrix_8c</filename>
    <includes id="azk__komplex_8h" name="azk_komplex.h" local="yes" imported="no">azk_komplex.h</includes>
    <member kind="function">
      <type>void</type>
      <name>AZK_destroy_matrix</name>
      <anchorfile>azk__destroy__matrix_8c.html</anchorfile>
      <anchor>a2a766a9b1da21093aac794bf60701f21</anchor>
      <arglist>(int options[], double params[], int proc_config[], AZ_MATRIX **Amat_komplex)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>azk_destroy_precon.c</name>
    <path>/Users/sscoll/dist/trilinos/packages/komplex/src/</path>
    <filename>azk__destroy__precon_8c</filename>
    <includes id="azk__komplex_8h" name="azk_komplex.h" local="yes" imported="no">azk_komplex.h</includes>
    <member kind="function">
      <type>void</type>
      <name>AZK_destroy_precon</name>
      <anchorfile>azk__destroy__precon_8c.html</anchorfile>
      <anchor>a1d577a75f5a60a329e569e26f598c8f9</anchor>
      <arglist>(int *options, double *params, int *proc_config, AZ_MATRIX *Amat, AZ_PRECOND **Prec)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>azk_destroy_vector.c</name>
    <path>/Users/sscoll/dist/trilinos/packages/komplex/src/</path>
    <filename>azk__destroy__vector_8c</filename>
    <includes id="azk__komplex_8h" name="azk_komplex.h" local="yes" imported="no">azk_komplex.h</includes>
    <member kind="function">
      <type>void</type>
      <name>AZK_destroy_vector</name>
      <anchorfile>azk__destroy__vector_8c.html</anchorfile>
      <anchor>a86ac90aa33fd33741a8a489af9fbf823</anchor>
      <arglist>(int *options, double *params, int *proc_config, AZ_MATRIX *Amat_komplex, double **vk)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>azk_extract_solution.c</name>
    <path>/Users/sscoll/dist/trilinos/packages/komplex/src/</path>
    <filename>azk__extract__solution_8c</filename>
    <includes id="azk__komplex_8h" name="azk_komplex.h" local="yes" imported="no">azk_komplex.h</includes>
    <member kind="function">
      <type>void</type>
      <name>AZK_extract_solution_k2c</name>
      <anchorfile>azk__extract__solution_8c.html</anchorfile>
      <anchor>a4ae6c9e75cb2bf10b4b4a15adf80115d</anchor>
      <arglist>(int *options, double *params, int *proc_config, AZ_MATRIX *Amat_komplex, AZ_PRECOND *Prec, double *vk, double *vc)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>AZK_extract_solution_k2ri</name>
      <anchorfile>azk__extract__solution_8c.html</anchorfile>
      <anchor>aea811ee8462c5747fd40bf8b873c8554</anchor>
      <arglist>(int *options, double *params, int *proc_config, AZ_MATRIX *Amat_komplex, AZ_PRECOND *Prec, double *vk, double *vr, double *vi)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>azk_komplex.h</name>
    <path>/Users/sscoll/dist/trilinos/packages/komplex/src/</path>
    <filename>azk__komplex_8h</filename>
    <class kind="struct">AZ_KOMPLEX_STRUCT</class>
    <member kind="function">
      <type>void</type>
      <name>AZK_create_linsys_c2k</name>
      <anchorfile>azk__komplex_8h.html</anchorfile>
      <anchor>a0d7ab66940d38b72c8bc6073292d6a91</anchor>
      <arglist>(double *xc, double *bc, int *options, double *params, int *proc_config, AZ_MATRIX *Amat_complex, double **x, double **b, AZ_MATRIX **Amat_komplex)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>AZK_create_linsys_g2k</name>
      <anchorfile>azk__komplex_8h.html</anchorfile>
      <anchor>a67745ee9fbf1ef1aacf5a3a8de0290bb</anchor>
      <arglist>(double *xr, double *xi, double *br, double *bi, int *options, double *params, int *proc_config, double c0r, double c0i, AZ_MATRIX *Amat_mat0, double c1r, double c1i, AZ_MATRIX *Amat_mat1, double **x, double **b, AZ_MATRIX **Amat_komplex)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>AZK_create_linsys_ri2k</name>
      <anchorfile>azk__komplex_8h.html</anchorfile>
      <anchor>a62c165f02bd064c3cb69559b83247fe9</anchor>
      <arglist>(double *xr, double *xi, double *br, double *bi, int *options, double *params, int *proc_config, AZ_MATRIX *Amat_real, double *val_imag, double **x, double **b, AZ_MATRIX **Amat_komplex)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>AZK_create_matrix_g2k</name>
      <anchorfile>azk__komplex_8h.html</anchorfile>
      <anchor>a13562601950b5d31c04ddd0c3be978fa</anchor>
      <arglist>(int options[], double params[], int proc_config[], double c0r, double c0i, AZ_MATRIX *Amat_mat0, double c1r, double c1i, AZ_MATRIX *Amat_mat1, AZ_MATRIX **Amat_komplex)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>AZK_create_matrix_c2k</name>
      <anchorfile>azk__komplex_8h.html</anchorfile>
      <anchor>ab10a09223c730d6be4fcc4367acc6b06</anchor>
      <arglist>(int options[], double params[], int proc_config[], AZ_MATRIX *Amat_complex, AZ_MATRIX **Amat_komplex)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>AZK_create_matrix_ri2k</name>
      <anchorfile>azk__komplex_8h.html</anchorfile>
      <anchor>a0feb150d7072b9eebc8172c39917e9b4</anchor>
      <arglist>(int options[], double params[], int proc_config[], AZ_MATRIX *Amat_real, double *val_imag, AZ_MATRIX **Amat_komplex)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>AZK_create_precon</name>
      <anchorfile>azk__komplex_8h.html</anchorfile>
      <anchor>a7177cbc293fe1e21936b3c8fe6f18983</anchor>
      <arglist>(int *options, double *params, int *proc_config, double *x, double *b, AZ_MATRIX *Amat, AZ_PRECOND **Prec)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>AZK_create_vector_c2k</name>
      <anchorfile>azk__komplex_8h.html</anchorfile>
      <anchor>a91ae8163950942c308fbae61a3d61f4e</anchor>
      <arglist>(int *options, double *params, int *proc_config, AZ_MATRIX *Amat_komplex, double *vc, double **vk)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>AZK_create_vector_g2k</name>
      <anchorfile>azk__komplex_8h.html</anchorfile>
      <anchor>a32bc998ab924bf196567f38e0bbf3a11</anchor>
      <arglist>(int *options, double *params, int *proc_config, AZ_MATRIX *Amat_komplex, double *vr, double *vi, double **vk)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>AZK_create_vector_ri2k</name>
      <anchorfile>azk__komplex_8h.html</anchorfile>
      <anchor>a068c6f1b45c8ec923cac8085af39849b</anchor>
      <arglist>(int *options, double *params, int *proc_config, AZ_MATRIX *Amat_komplex, double *vr, double *vi, double **vk)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>AZK_destroy_linsys</name>
      <anchorfile>azk__komplex_8h.html</anchorfile>
      <anchor>ab7983f9321543d976c9cc8a3dc00a1ae</anchor>
      <arglist>(int *options, double *params, int *proc_config, double **x, double **b, AZ_MATRIX **Amat_komplex)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>AZK_destroy_matrix</name>
      <anchorfile>azk__komplex_8h.html</anchorfile>
      <anchor>a2a766a9b1da21093aac794bf60701f21</anchor>
      <arglist>(int options[], double params[], int proc_config[], AZ_MATRIX **Amat_komplex)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>AZK_destroy_precon</name>
      <anchorfile>azk__komplex_8h.html</anchorfile>
      <anchor>a1d577a75f5a60a329e569e26f598c8f9</anchor>
      <arglist>(int *options, double *params, int *proc_config, AZ_MATRIX *Amat, AZ_PRECOND **Prec)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>AZK_destroy_vector</name>
      <anchorfile>azk__komplex_8h.html</anchorfile>
      <anchor>a86ac90aa33fd33741a8a489af9fbf823</anchor>
      <arglist>(int *options, double *params, int *proc_config, AZ_MATRIX *Amat_komplex, double **vk)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>AZK_extract_solution_k2c</name>
      <anchorfile>azk__komplex_8h.html</anchorfile>
      <anchor>a4ae6c9e75cb2bf10b4b4a15adf80115d</anchor>
      <arglist>(int *options, double *params, int *proc_config, AZ_MATRIX *Amat_komplex, AZ_PRECOND *Prec, double *vk, double *vc)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>AZK_extract_solution_k2ri</name>
      <anchorfile>azk__komplex_8h.html</anchorfile>
      <anchor>aea811ee8462c5747fd40bf8b873c8554</anchor>
      <arglist>(int *options, double *params, int *proc_config, AZ_MATRIX *Amat_komplex, AZ_PRECOND *Prec, double *vk, double *vr, double *vi)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>AZK_permute_ri</name>
      <anchorfile>azk__komplex_8h.html</anchorfile>
      <anchor>a3463fab57f0f3763e143e28483e24d80</anchor>
      <arglist>(int *options, double *params, int *proc_config, double *b, AZ_MATRIX *Amat_komplex)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>azk_permute_ri.c</name>
    <path>/Users/sscoll/dist/trilinos/packages/komplex/src/</path>
    <filename>azk__permute__ri_8c</filename>
    <includes id="azk__komplex_8h" name="azk_komplex.h" local="yes" imported="no">azk_komplex.h</includes>
    <member kind="function">
      <type>void</type>
      <name>AZK_permute_ri</name>
      <anchorfile>azk__permute__ri_8c.html</anchorfile>
      <anchor>a3463fab57f0f3763e143e28483e24d80</anchor>
      <arglist>(int *options, double *params, int *proc_config, double *b, AZ_MATRIX *Amat_komplex)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Komplex_DataAccess.hpp</name>
    <path>/Users/sscoll/dist/trilinos/packages/komplex/src/new/</path>
    <filename>Komplex__DataAccess_8hpp</filename>
    <member kind="enumeration">
      <type></type>
      <name>Komplex_DataAccess</name>
      <anchorfile>Komplex__DataAccess_8hpp.html</anchorfile>
      <anchor>a269ac20f1dd332aee48a82f210f2e69b</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>Copy</name>
      <anchorfile>Komplex__DataAccess_8hpp.html</anchorfile>
      <anchor>a269ac20f1dd332aee48a82f210f2e69baad81934e8f3b9399beea932f0b0e57d8</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>View</name>
      <anchorfile>Komplex__DataAccess_8hpp.html</anchorfile>
      <anchor>a269ac20f1dd332aee48a82f210f2e69ba688fad5d6c4f06f049549c2313e93cba</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>AZ_KOMPLEX_STRUCT</name>
    <filename>structAZ__KOMPLEX__STRUCT.html</filename>
  </compound>
  <compound kind="class">
    <name>Komplex_LinearProblem</name>
    <filename>classKomplex__LinearProblem.html</filename>
    <member kind="function">
      <type></type>
      <name>Komplex_LinearProblem</name>
      <anchorfile>classKomplex__LinearProblem.html</anchorfile>
      <anchor>af15b81cde1b1815f81d629e1b344b031</anchor>
      <arglist>(double c0r, double c0i, const Epetra_RowMatrix &amp;A0, double c1r, double c1i, const Epetra_RowMatrix &amp;A1, const Epetra_MultiVector &amp;Xr, const Epetra_MultiVector &amp;Xi, const Epetra_MultiVector &amp;Br, const Epetra_MultiVector &amp;Bi)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~Komplex_LinearProblem</name>
      <anchorfile>classKomplex__LinearProblem.html</anchorfile>
      <anchor>a4c843acbc8b6d843921a9eb4924c26e0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>UpdateValues</name>
      <anchorfile>classKomplex__LinearProblem.html</anchorfile>
      <anchor>a9e81644d1b60b9dc490c3ad2ea819345</anchor>
      <arglist>(double c0r, double c0i, const Epetra_RowMatrix &amp;A0, double c1r, double c1i, const Epetra_RowMatrix &amp;A1, const Epetra_MultiVector &amp;Xr, const Epetra_MultiVector &amp;Xi, const Epetra_MultiVector &amp;Br, const Epetra_MultiVector &amp;Bi)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ExtractSolution</name>
      <anchorfile>classKomplex__LinearProblem.html</anchorfile>
      <anchor>a7c8e2ffbf7aaa97427df8b31e2fdf33f</anchor>
      <arglist>(Epetra_MultiVector &amp;Xr, Epetra_MultiVector &amp;Xi)</arglist>
    </member>
    <member kind="function">
      <type>Epetra_LinearProblem *</type>
      <name>KomplexProblem</name>
      <anchorfile>classKomplex__LinearProblem.html</anchorfile>
      <anchor>a9796a9f2c2fc638707cec78c88c27375</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Komplex_LinearProblem</name>
      <anchorfile>classKomplex__LinearProblem.html</anchorfile>
      <anchor>af15b81cde1b1815f81d629e1b344b031</anchor>
      <arglist>(double c0r, double c0i, const Epetra_RowMatrix &amp;A0, double c1r, double c1i, const Epetra_RowMatrix &amp;A1, const Epetra_MultiVector &amp;Xr, const Epetra_MultiVector &amp;Xi, const Epetra_MultiVector &amp;Br, const Epetra_MultiVector &amp;Bi)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~Komplex_LinearProblem</name>
      <anchorfile>classKomplex__LinearProblem.html</anchorfile>
      <anchor>a4c843acbc8b6d843921a9eb4924c26e0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>UpdateValues</name>
      <anchorfile>classKomplex__LinearProblem.html</anchorfile>
      <anchor>a9e81644d1b60b9dc490c3ad2ea819345</anchor>
      <arglist>(double c0r, double c0i, const Epetra_RowMatrix &amp;A0, double c1r, double c1i, const Epetra_RowMatrix &amp;A1, const Epetra_MultiVector &amp;Xr, const Epetra_MultiVector &amp;Xi, const Epetra_MultiVector &amp;Br, const Epetra_MultiVector &amp;Bi)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ExtractSolution</name>
      <anchorfile>classKomplex__LinearProblem.html</anchorfile>
      <anchor>a7c8e2ffbf7aaa97427df8b31e2fdf33f</anchor>
      <arglist>(Epetra_MultiVector &amp;Xr, Epetra_MultiVector &amp;Xi)</arglist>
    </member>
    <member kind="function">
      <type>Epetra_LinearProblem *</type>
      <name>KomplexProblem</name>
      <anchorfile>classKomplex__LinearProblem.html</anchorfile>
      <anchor>a9796a9f2c2fc638707cec78c88c27375</anchor>
      <arglist>() const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Komplex_MultiVector</name>
    <filename>classKomplex__MultiVector.html</filename>
    <member kind="function">
      <type>int</type>
      <name>ReplaceMap</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>ace141ba6fb167760198681a4b0a24b04</anchor>
      <arglist>(const Epetra_BlockMap &amp;map)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ReplaceMap</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>ac3de4059f14175d116620b8ae80a8d6a</anchor>
      <arglist>(const Epetra_BlockMap &amp;Map)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Komplex_MultiVector</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>a22daa3dac7bca404d74f4bfd95d1cf19</anchor>
      <arglist>(const Epetra_BlockMap &amp;Map, int NumVectors, bool RHS, bool zeroOut=true, Komplex_KForms KForm=K1)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Komplex_MultiVector</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>ac1f0b74fe9e7007fd0c93291a567ab73</anchor>
      <arglist>(const Komplex_MultiVector &amp;Source)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Komplex_MultiVector</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>a7821877830f2598c7149702ec53b32f1</anchor>
      <arglist>(Epetra_DataAccess CV, const Epetra_BlockMap &amp;Map, double *A, int MyLDA, int NumVectors, bool RHS, Komplex_KForms KForm=K1)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Komplex_MultiVector</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>a0f8974a82db98e08bfdcb4d14ff7081e</anchor>
      <arglist>(Epetra_DataAccess CV, const Epetra_BlockMap &amp;Map, double *Real, double *Imag, int MyLDA, int NumVectors, bool RHS, Komplex_KForms KForm=K1)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Komplex_MultiVector</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>a0796cb6e63f06ae3af1a145fa924222a</anchor>
      <arglist>(Epetra_DataAccess CV, const Epetra_BlockMap &amp;Map, double **ArrayOfPointers, int NumVectors, bool RHS, Komplex_KForms KForm=K1)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Komplex_MultiVector</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>afcc67ccfe8ae3b079d9d40406fd629d9</anchor>
      <arglist>(Epetra_DataAccess CV, const Epetra_BlockMap &amp;Map, double **AOPReal, double **AOPImag, int NumVectors, bool RHS, Komplex_KForms KForm=K1)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Komplex_MultiVector</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>a625e15d4570298db88389463cd9a2759</anchor>
      <arglist>(Epetra_DataAccess CV, const Epetra_MultiVector &amp;Source, int *Indices, int NumVectors, bool RHS, Komplex_KForms KForm=K1)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Komplex_MultiVector</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>ab55059ec102f3e780ec5537cf0f2685a</anchor>
      <arglist>(Epetra_DataAccess CV, const Epetra_MultiVector &amp;Source, int StartIndex, int NumVectors, bool RHS, Komplex_KForms KForm=K1)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Komplex_MultiVector</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>ab1417ac2859fba1f14f406860d4e11ad</anchor>
      <arglist>(Epetra_DataAccess CV, const Epetra_MultiVector &amp;Source, bool RHS, Komplex_KForms KForm=K1)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Komplex_MultiVector</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>a9c58cfed12f0b049aaf1e511a91880ab</anchor>
      <arglist>(Epetra_DataAccess CV, const Epetra_MultiVector &amp;Real, const Epetra_MultiVector &amp;Imag, bool RHS, Komplex_KForms KForm=K1)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~Komplex_MultiVector</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>a3d8d9e6f77eece14c6431b561ef26fe2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ReplaceGlobalValue</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>a4b148634887681f39db7122dd1ed8f55</anchor>
      <arglist>(int GlobalRow, int VectorIndex, double ScalarValue)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SumIntoGlobalValue</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>a2bb528e207317b8c0f2c7eaa1a28c9cf</anchor>
      <arglist>(int GlobalRow, int VectorIndex, double ScalarValue)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ReplaceMyValue</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>a74326b7250660b1ad583373157cbb14b</anchor>
      <arglist>(int MyRow, int VectorIndex, double ScalarValue)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SumIntoMyValue</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>a4290e2bc937cb7594cd49adc32971666</anchor>
      <arglist>(int MyRow, int VectorIndex, double ScalarValue)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>PutScalar</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>aa59f3a9accc0fbfa840cdd1a71a3713a</anchor>
      <arglist>(double ScalarConstant)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Random</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>a5cf468903efe05d0852c3696480ed77c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>CreateOtherMap</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>a0c4318295029f076759e2cff479e5251</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Dot</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>ab0f52856610b2a8c37baa59607427eb9</anchor>
      <arglist>(const Komplex_MultiVector &amp;A, double *Result) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Abs</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>a05d09487d6f44512d69238f08b97795a</anchor>
      <arglist>(const Komplex_MultiVector &amp;A)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Reciprocal</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>ae5afe80425e8590b119b8bcab85396de</anchor>
      <arglist>(const Komplex_MultiVector &amp;A)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Scale</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>abf1ad7e2430cf97d39671cf8115fe364</anchor>
      <arglist>(double ScalarValue)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Scale</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>a2afbf0874d7f1ab47f447e6327679a0f</anchor>
      <arglist>(double ScalarA, const Komplex_MultiVector &amp;A)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Update</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>aabc8d42769452d2cf5708f7e04386b1d</anchor>
      <arglist>(double ScalarA, const Komplex_MultiVector &amp;A, double ScalarThis)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Update</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>a0202b124b8b007f76c59923faca97ce3</anchor>
      <arglist>(double ScalarA, const Komplex_MultiVector &amp;A, double ScalarB, const Komplex_MultiVector &amp;B, double ScalarThis)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Norm1</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>ad8d0a0ca08b2f0d7cd875514a7454f94</anchor>
      <arglist>(double *Result) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ComplexNorm1</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>a7ea59646c2d1e21fdae2b7137fa3694d</anchor>
      <arglist>(double *Result) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Norm2</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>a9e15c4c2ae842187f0ce8af28896347f</anchor>
      <arglist>(double *Result) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ComplexNorm2</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>aebf9a7c43a7efb44443741b6f926fca9</anchor>
      <arglist>(double *Result) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NormInf</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>ad84423c47b390ee8aa2d2984bb78d6ee</anchor>
      <arglist>(double *Result) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ComplexNormInf</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>a91525feb217a050672cebf67f03f5cb3</anchor>
      <arglist>(double *Result) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NormWeighted</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>a84f79f4b45f36c40f1b0f5c4b31819a7</anchor>
      <arglist>(const Epetra_MultiVector &amp;Weights, double *Result) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>MinValue</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>a81cace94ce59c412f8c05fe5ceaf5d0f</anchor>
      <arglist>(double *Result) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>MaxValue</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>a9f19fd4bc6f6f7c66b5fbc400642d7b9</anchor>
      <arglist>(double *Result) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>MeanValue</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>ada608e54dbbf0b53e76fcde784afa28c</anchor>
      <arglist>(double *Result) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetSeed</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>a7dafec9990c9d7881795d3dfff96fc38</anchor>
      <arglist>(unsigned int Seed)</arglist>
    </member>
    <member kind="function">
      <type>unsigned int</type>
      <name>Seed</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>a49bafa3d8daabefda8ffcdb060afd855</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Komplex_MultiVector &amp;</type>
      <name>operator=</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>a969b9b1eb43666a46dd0dbca864e2383</anchor>
      <arglist>(const Komplex_MultiVector &amp;Source)</arglist>
    </member>
    <member kind="function">
      <type>double *&amp;</type>
      <name>operator[]</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>af31b6d4540c0b7828351c9fae4671cc5</anchor>
      <arglist>(int i)</arglist>
    </member>
    <member kind="function">
      <type>double *const &amp;</type>
      <name>operator[]</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>ad1408704dad57ab1bb24a1fff3e37ac0</anchor>
      <arglist>(int i) const </arglist>
    </member>
    <member kind="function">
      <type>Epetra_MultiVector *</type>
      <name>EpetraMultiVector</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>ae62f1355c1dd30cadcda7ee03b06c8d7</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Epetra_MultiVector *</type>
      <name>RealMultiVector</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>ad10502510cdbb5f0a700e4a5d694b4f7</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Epetra_MultiVector *</type>
      <name>ImagMultiVector</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>add9a6fdeb6c04d8129f8a1950cac1171</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Epetra_Vector *</type>
      <name>EpetraVector</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>a98265519f3cdd51110f6c32a98b07611</anchor>
      <arglist>(int index) const </arglist>
    </member>
    <member kind="function">
      <type>Epetra_Vector *</type>
      <name>RealVector</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>a7582b9c169bd54852311a7a114ed1fc1</anchor>
      <arglist>(int index) const </arglist>
    </member>
    <member kind="function">
      <type>Epetra_Vector *</type>
      <name>ImagVector</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>af33bc80d51ffda389663375032128b1f</anchor>
      <arglist>(int index) const </arglist>
    </member>
    <member kind="function">
      <type>double *&amp;</type>
      <name>RealValues</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>a751e2011096a59950d89c23509d36d15</anchor>
      <arglist>(int i) const </arglist>
    </member>
    <member kind="function">
      <type>double *&amp;</type>
      <name>ImagValues</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>abcb41046fec50d1476ea603f837d7f96</anchor>
      <arglist>(int i) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumVectors</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>adbac3772556e84638a666909fb172ddd</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>MyLength</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>aab6002d863a483623b431e08264a3801</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GlobalLength</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>ad52d44d03cc7727c8bf852a722feed7d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Komplex_KForms</type>
      <name>KForm</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>a0e34fa1ea64ad327f4c54c98a28be490</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>RHS</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>a00b6fbc92e0a303b88ada5fcebb24f96</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SwitchKForm</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>a37491109a8d25b5159e27e9e6ce0fe6c</anchor>
      <arglist>(Komplex_KForms NewKForm)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>Print</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>a3fab26673b5a6ad7c849a39185a43737</anchor>
      <arglist>(ostream &amp;os) const </arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Komplex_MultiVector</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>a49f7b73eefa151234e716b672e737b6d</anchor>
      <arglist>(const Epetra_BlockMap &amp;Map, int NumVectors, bool zeroOut=true)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Komplex_MultiVector</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>a2b9fa7b39edd04d9fe08e464b1df403f</anchor>
      <arglist>(const Epetra_BlockMap &amp;MapReal, const Epetra_BlockMap &amp;MapImag, int NumVectors, bool zeroOut=true)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Komplex_MultiVector</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>aeba3979ed83da99dd4b32cffaa7ee20d</anchor>
      <arglist>(const Epetra_BlockMap &amp;Map, const Epetra_MultiVector &amp;Br, const Epetra_MultiVector &amp;Bi)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Komplex_MultiVector</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>a90f4dcda90e99b3bef22426e3f16d58b</anchor>
      <arglist>(const Epetra_BlockMap &amp;MapReal, const Epetra_BlockMap &amp;MapImag, const Epetra_MultiVector &amp;Br, const Epetra_MultiVector &amp;Bi)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Komplex_MultiVector</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>ac1f0b74fe9e7007fd0c93291a567ab73</anchor>
      <arglist>(const Komplex_MultiVector &amp;Source)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Komplex_MultiVector</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>a2e49c7638d9d8669720e3fa47078ee30</anchor>
      <arglist>(Komplex_DataAccess CV, const Komplex_MultiVector &amp;Source, int *Indices, int NumVectors)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Komplex_MultiVector</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>a256445a21d906c9560a09519d5a4e78f</anchor>
      <arglist>(Komplex_DataAccess CV, const Komplex_MultiVector &amp;Source, int StartIndex, int NumVectors)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~Komplex_MultiVector</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>a2dc523c44c9429032ed58506daa40287</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Scale</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>abf1ad7e2430cf97d39671cf8115fe364</anchor>
      <arglist>(double ScalarValue)</arglist>
    </member>
    <member kind="function">
      <type>part separately int</type>
      <name>Scale</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>ae7d21dd77b420988d62c673cf9aa83a8</anchor>
      <arglist>(double ScalarValueReal, double ScalarValueImag)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Scale</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>a2afbf0874d7f1ab47f447e6327679a0f</anchor>
      <arglist>(double ScalarA, const Komplex_MultiVector &amp;A)</arglist>
    </member>
    <member kind="function">
      <type>parts separately int</type>
      <name>Scale</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>ab55c4ec57ec880edde9617b061eaa1ac</anchor>
      <arglist>(double ScalarAReal, double ScalarAImag, const Komplex_MultiVector &amp;A)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Norm1</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>ad8d0a0ca08b2f0d7cd875514a7454f94</anchor>
      <arglist>(double *Result) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Norm2</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>a9e15c4c2ae842187f0ce8af28896347f</anchor>
      <arglist>(double *Result) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NormInf</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>ad84423c47b390ee8aa2d2984bb78d6ee</anchor>
      <arglist>(double *Result) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Multiply</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>a143455637e0007a7351b4ec19a58cbad</anchor>
      <arglist>(char TransA, char TransB, double ScalarAB, const Komplex_MultiVector &amp;A, const Komplex_MultiVector &amp;B, double ScalarThis)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Multiply</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>a5c3ac599f1253657d5074e65846ceaa3</anchor>
      <arglist>(double ScalarAB, const Komplex_MultiVector &amp;A, const Komplex_MultiVector &amp;B, double ScalarThis)</arglist>
    </member>
    <member kind="function">
      <type>Komplex_MultiVector &amp;</type>
      <name>operator=</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>aa92e7001f075b2685f95cc1a0412d6b1</anchor>
      <arglist>(const Komplex_MultiVector &amp;Source)</arglist>
    </member>
    <member kind="function">
      <type>double *&amp;</type>
      <name>operator[]</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>a2729007d44f000a12af2eb9bd69df361</anchor>
      <arglist>(int i)</arglist>
    </member>
    <member kind="function">
      <type>double *const &amp;</type>
      <name>operator[]</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>a1887b2317d68e7f17a4093df2ce21ed9</anchor>
      <arglist>(int i) const </arglist>
    </member>
    <member kind="function">
      <type>Komplex_Vector *&amp;</type>
      <name>operator()</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>aa973b6e2259b2dedb2e961d5325d2aa5</anchor>
      <arglist>(int i)</arglist>
    </member>
    <member kind="function">
      <type>const Komplex_Vector *&amp;</type>
      <name>operator()</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>a86e8f7e56c079f4c4c9f3ab3138591fe</anchor>
      <arglist>(int i) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumVectors</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>adbac3772556e84638a666909fb172ddd</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>MyLength</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>aab6002d863a483623b431e08264a3801</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GlobalLength</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>ad52d44d03cc7727c8bf852a722feed7d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Stride</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>a3232253fd7ba87e8fea63b2922692e6a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>ConstantStride</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>a6eb32b06f1c23248443abe6dc572e137</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Print</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>a3fab26673b5a6ad7c849a39185a43737</anchor>
      <arglist>(ostream &amp;os) const </arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Komplex_MultiVector</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>a22daa3dac7bca404d74f4bfd95d1cf19</anchor>
      <arglist>(const Epetra_BlockMap &amp;Map, int NumVectors, bool RHS, bool zeroOut=true, Komplex_KForms KForm=K1)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Komplex_MultiVector</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>ac1f0b74fe9e7007fd0c93291a567ab73</anchor>
      <arglist>(const Komplex_MultiVector &amp;Source)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Komplex_MultiVector</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>a7821877830f2598c7149702ec53b32f1</anchor>
      <arglist>(Epetra_DataAccess CV, const Epetra_BlockMap &amp;Map, double *A, int MyLDA, int NumVectors, bool RHS, Komplex_KForms KForm=K1)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Komplex_MultiVector</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>a0f8974a82db98e08bfdcb4d14ff7081e</anchor>
      <arglist>(Epetra_DataAccess CV, const Epetra_BlockMap &amp;Map, double *Real, double *Imag, int MyLDA, int NumVectors, bool RHS, Komplex_KForms KForm=K1)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Komplex_MultiVector</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>a0796cb6e63f06ae3af1a145fa924222a</anchor>
      <arglist>(Epetra_DataAccess CV, const Epetra_BlockMap &amp;Map, double **ArrayOfPointers, int NumVectors, bool RHS, Komplex_KForms KForm=K1)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Komplex_MultiVector</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>afcc67ccfe8ae3b079d9d40406fd629d9</anchor>
      <arglist>(Epetra_DataAccess CV, const Epetra_BlockMap &amp;Map, double **AOPReal, double **AOPImag, int NumVectors, bool RHS, Komplex_KForms KForm=K1)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Komplex_MultiVector</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>a625e15d4570298db88389463cd9a2759</anchor>
      <arglist>(Epetra_DataAccess CV, const Epetra_MultiVector &amp;Source, int *Indices, int NumVectors, bool RHS, Komplex_KForms KForm=K1)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Komplex_MultiVector</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>ab55059ec102f3e780ec5537cf0f2685a</anchor>
      <arglist>(Epetra_DataAccess CV, const Epetra_MultiVector &amp;Source, int StartIndex, int NumVectors, bool RHS, Komplex_KForms KForm=K1)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Komplex_MultiVector</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>ab1417ac2859fba1f14f406860d4e11ad</anchor>
      <arglist>(Epetra_DataAccess CV, const Epetra_MultiVector &amp;Source, bool RHS, Komplex_KForms KForm=K1)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Komplex_MultiVector</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>a9c58cfed12f0b049aaf1e511a91880ab</anchor>
      <arglist>(Epetra_DataAccess CV, const Epetra_MultiVector &amp;Real, const Epetra_MultiVector &amp;Imag, bool RHS, Komplex_KForms KForm=K1)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~Komplex_MultiVector</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>a3d8d9e6f77eece14c6431b561ef26fe2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ReplaceGlobalValue</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>a4b148634887681f39db7122dd1ed8f55</anchor>
      <arglist>(int GlobalRow, int VectorIndex, double ScalarValue)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SumIntoGlobalValue</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>a2bb528e207317b8c0f2c7eaa1a28c9cf</anchor>
      <arglist>(int GlobalRow, int VectorIndex, double ScalarValue)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ReplaceMyValue</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>a74326b7250660b1ad583373157cbb14b</anchor>
      <arglist>(int MyRow, int VectorIndex, double ScalarValue)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SumIntoMyValue</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>a4290e2bc937cb7594cd49adc32971666</anchor>
      <arglist>(int MyRow, int VectorIndex, double ScalarValue)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>PutScalar</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>aa59f3a9accc0fbfa840cdd1a71a3713a</anchor>
      <arglist>(double ScalarConstant)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Random</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>a5cf468903efe05d0852c3696480ed77c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>CreateOtherMap</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>a0c4318295029f076759e2cff479e5251</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Dot</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>ab0f52856610b2a8c37baa59607427eb9</anchor>
      <arglist>(const Komplex_MultiVector &amp;A, double *Result) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Abs</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>a05d09487d6f44512d69238f08b97795a</anchor>
      <arglist>(const Komplex_MultiVector &amp;A)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Reciprocal</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>ae5afe80425e8590b119b8bcab85396de</anchor>
      <arglist>(const Komplex_MultiVector &amp;A)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Scale</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>abf1ad7e2430cf97d39671cf8115fe364</anchor>
      <arglist>(double ScalarValue)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Scale</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>a2afbf0874d7f1ab47f447e6327679a0f</anchor>
      <arglist>(double ScalarA, const Komplex_MultiVector &amp;A)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Update</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>aabc8d42769452d2cf5708f7e04386b1d</anchor>
      <arglist>(double ScalarA, const Komplex_MultiVector &amp;A, double ScalarThis)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Update</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>a0202b124b8b007f76c59923faca97ce3</anchor>
      <arglist>(double ScalarA, const Komplex_MultiVector &amp;A, double ScalarB, const Komplex_MultiVector &amp;B, double ScalarThis)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Norm1</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>ad8d0a0ca08b2f0d7cd875514a7454f94</anchor>
      <arglist>(double *Result) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ComplexNorm1</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>a7ea59646c2d1e21fdae2b7137fa3694d</anchor>
      <arglist>(double *Result) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Norm2</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>a9e15c4c2ae842187f0ce8af28896347f</anchor>
      <arglist>(double *Result) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ComplexNorm2</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>aebf9a7c43a7efb44443741b6f926fca9</anchor>
      <arglist>(double *Result) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NormInf</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>ad84423c47b390ee8aa2d2984bb78d6ee</anchor>
      <arglist>(double *Result) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ComplexNormInf</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>a91525feb217a050672cebf67f03f5cb3</anchor>
      <arglist>(double *Result) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NormWeighted</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>a84f79f4b45f36c40f1b0f5c4b31819a7</anchor>
      <arglist>(const Epetra_MultiVector &amp;Weights, double *Result) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>MinValue</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>a81cace94ce59c412f8c05fe5ceaf5d0f</anchor>
      <arglist>(double *Result) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>MaxValue</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>a9f19fd4bc6f6f7c66b5fbc400642d7b9</anchor>
      <arglist>(double *Result) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>MeanValue</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>ada608e54dbbf0b53e76fcde784afa28c</anchor>
      <arglist>(double *Result) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetSeed</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>a7dafec9990c9d7881795d3dfff96fc38</anchor>
      <arglist>(unsigned int Seed)</arglist>
    </member>
    <member kind="function">
      <type>unsigned int</type>
      <name>Seed</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>a49bafa3d8daabefda8ffcdb060afd855</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Komplex_MultiVector &amp;</type>
      <name>operator=</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>a969b9b1eb43666a46dd0dbca864e2383</anchor>
      <arglist>(const Komplex_MultiVector &amp;Source)</arglist>
    </member>
    <member kind="function">
      <type>double *&amp;</type>
      <name>operator[]</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>af31b6d4540c0b7828351c9fae4671cc5</anchor>
      <arglist>(int i)</arglist>
    </member>
    <member kind="function">
      <type>double *const &amp;</type>
      <name>operator[]</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>ad1408704dad57ab1bb24a1fff3e37ac0</anchor>
      <arglist>(int i) const </arglist>
    </member>
    <member kind="function">
      <type>Epetra_MultiVector *</type>
      <name>EpetraMultiVector</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>ae62f1355c1dd30cadcda7ee03b06c8d7</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Epetra_MultiVector *</type>
      <name>RealMultiVector</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>ad10502510cdbb5f0a700e4a5d694b4f7</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Epetra_MultiVector *</type>
      <name>ImagMultiVector</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>add9a6fdeb6c04d8129f8a1950cac1171</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Epetra_Vector *</type>
      <name>EpetraVector</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>a98265519f3cdd51110f6c32a98b07611</anchor>
      <arglist>(int index) const </arglist>
    </member>
    <member kind="function">
      <type>Epetra_Vector *</type>
      <name>RealVector</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>a7582b9c169bd54852311a7a114ed1fc1</anchor>
      <arglist>(int index) const </arglist>
    </member>
    <member kind="function">
      <type>Epetra_Vector *</type>
      <name>ImagVector</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>af33bc80d51ffda389663375032128b1f</anchor>
      <arglist>(int index) const </arglist>
    </member>
    <member kind="function">
      <type>double *&amp;</type>
      <name>RealValues</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>a751e2011096a59950d89c23509d36d15</anchor>
      <arglist>(int i) const </arglist>
    </member>
    <member kind="function">
      <type>double *&amp;</type>
      <name>ImagValues</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>abcb41046fec50d1476ea603f837d7f96</anchor>
      <arglist>(int i) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumVectors</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>adbac3772556e84638a666909fb172ddd</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>MyLength</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>aab6002d863a483623b431e08264a3801</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GlobalLength</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>ad52d44d03cc7727c8bf852a722feed7d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Komplex_KForms</type>
      <name>KForm</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>a0e34fa1ea64ad327f4c54c98a28be490</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>RHS</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>a00b6fbc92e0a303b88ada5fcebb24f96</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SwitchKForm</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>a37491109a8d25b5159e27e9e6ce0fe6c</anchor>
      <arglist>(Komplex_KForms NewKForm)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>Print</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>a3fab26673b5a6ad7c849a39185a43737</anchor>
      <arglist>(ostream &amp;os) const </arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Komplex_MultiVector</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>a49f7b73eefa151234e716b672e737b6d</anchor>
      <arglist>(const Epetra_BlockMap &amp;Map, int NumVectors, bool zeroOut=true)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Komplex_MultiVector</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>a2b9fa7b39edd04d9fe08e464b1df403f</anchor>
      <arglist>(const Epetra_BlockMap &amp;MapReal, const Epetra_BlockMap &amp;MapImag, int NumVectors, bool zeroOut=true)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Komplex_MultiVector</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>aeba3979ed83da99dd4b32cffaa7ee20d</anchor>
      <arglist>(const Epetra_BlockMap &amp;Map, const Epetra_MultiVector &amp;Br, const Epetra_MultiVector &amp;Bi)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Komplex_MultiVector</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>a90f4dcda90e99b3bef22426e3f16d58b</anchor>
      <arglist>(const Epetra_BlockMap &amp;MapReal, const Epetra_BlockMap &amp;MapImag, const Epetra_MultiVector &amp;Br, const Epetra_MultiVector &amp;Bi)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Komplex_MultiVector</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>ac1f0b74fe9e7007fd0c93291a567ab73</anchor>
      <arglist>(const Komplex_MultiVector &amp;Source)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Komplex_MultiVector</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>a2e49c7638d9d8669720e3fa47078ee30</anchor>
      <arglist>(Komplex_DataAccess CV, const Komplex_MultiVector &amp;Source, int *Indices, int NumVectors)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Komplex_MultiVector</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>a256445a21d906c9560a09519d5a4e78f</anchor>
      <arglist>(Komplex_DataAccess CV, const Komplex_MultiVector &amp;Source, int StartIndex, int NumVectors)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~Komplex_MultiVector</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>a2dc523c44c9429032ed58506daa40287</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>with</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>a5540b0de216d5e85454d1ba273b35ba9</anchor>
      <arglist>(ScalarValueReal, ScalarValueImag).int ReplaceGlobalValue(int GlobalRow</arglist>
    </member>
    <member kind="function">
      <type>with ScalarValue int</type>
      <name>ReplaceGlobalValueReal</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>ad74d75c974bd99d0411580aa1f9be8c8</anchor>
      <arglist>(int GlobalRow, int VectorIndex, double ScalarValue)</arglist>
    </member>
    <member kind="function">
      <type>with ScalarValue int</type>
      <name>ReplaceGlobalValueImag</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>aa2e6f8a93e21953cca91581a7df930e9</anchor>
      <arglist>(int GlobalRow, int VectorIndex, double ScalarValue)</arglist>
    </member>
    <member kind="function">
      <type>location</type>
      <name>with</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>aa563b69a193606a3b3e229f89a69574f</anchor>
      <arglist>(ScalarValueReal, ScalarValueImaginary).int ReplaceGlobalValue(int GlobalBlockRow</arglist>
    </member>
    <member kind="function">
      <type>location with ScalarValue int</type>
      <name>ReplaceGlobalValueReal</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>a8aab2ef276fc63467e1c4b2642e2653b</anchor>
      <arglist>(int GlobalBlockRow, int BlockRowOffset, int VectorIndex, double ScalarValue)</arglist>
    </member>
    <member kind="function">
      <type>location with ScalarValue int</type>
      <name>ReplaceGlobalValueImag</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>acc108a788dd3f12dccbcfd11f2c5922f</anchor>
      <arglist>(int GlobalBlockRow, int BlockRowOffset, int VectorIndex, double ScalarValue)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SumIntoGlobalValue</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>a964c4249a518997fb1cd79cc6c82e0a0</anchor>
      <arglist>(int GlobalRow, int VectorIndex, double ScalarValueReal, double ScalarValueImag)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SumIntoGlobalValueReal</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>a5abdc8c5889db6d95cd13cc97202e945</anchor>
      <arglist>(int GlobalRow, int VectorIndex, double ScalarValue)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SumIntoGlobalValueImag</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>af24a4ae62dfdd6e84d9c25a2a9029b38</anchor>
      <arglist>(int GlobalRow, int VectorIndex, double ScalarValue)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SumIntoGlobalValue</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>a2a0541cb9fc1cfc36e187f8a3f93cf57</anchor>
      <arglist>(int GlobalBlockRow, int BlockRowOffset, int VectorIndex, double ScalarValueReal, double ScalarValueImag)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SumIntoGlobalValueReal</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>a44a6d379d11696661743fb74af587860</anchor>
      <arglist>(int GlobalBlockRow, int BlockRowOffset, int VectorIndex, double ScalarValue)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SumIntoGlobalValueImag</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>a07c4b6044e74fa843938fe6ba0b7c46f</anchor>
      <arglist>(int GlobalBlockRow, int BlockRowOffset, int VectorIndex, double ScalarValue)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ReplaceMyValue</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>a34ca07fa887406f1dff5bba7afabee58</anchor>
      <arglist>(int MyRow, int VectorIndex, double ScalarValueReal, double ScalarValueImag)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ReplaceMyValueReal</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>aef5fc29c927b247e0c567c0adabb57b3</anchor>
      <arglist>(int MyRow, int VectorIndex, double ScalarValue)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ReplaceMyValueImag</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>a2eec63c4ca0b7804ff54b7922a4ec340</anchor>
      <arglist>(int MyRow, int VectorIndex, double ScalarValue)</arglist>
    </member>
    <member kind="function">
      <type>ScalarValueImag int</type>
      <name>ReplaceMyValue</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>a2d9fb6e14e2baafbef0b57060303a0c4</anchor>
      <arglist>(int MyBlockRow, int BlockRowOffset, int VectorIndex, double ScalarValueReal, double ScalarValueImag)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ReplaceMyValueReal</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>a8a940631180b1246e119277305e6eb64</anchor>
      <arglist>(int MyBlockRow, int BlockRowOffset, int VectorIndex, double ScalarValue)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ReplaceMyValueImag</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>a98cd45973efb0a701283ad2054e30f1a</anchor>
      <arglist>(int MyBlockRow, int BlockRowOffset, int VectorIndex, double ScalarValue)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SumIntoMyValue</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>ac692b24c29feab927c06b2e41424bd56</anchor>
      <arglist>(int MyRow, int VectorIndex, double ScalarValueReal, double ScalarValueImag)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SumIntoMyValueReal</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>afe8f452c55989c315833a0ae78bdecfc</anchor>
      <arglist>(int MyRow, int VectorIndex, double ScalarValue)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SumIntoMyValueImag</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>a011ff9c9aa1515a377e4280622d44d3e</anchor>
      <arglist>(int MyRow, int VectorIndex, double ScalarValue)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SumIntoMyValue</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>ab515a654b63ebe706846f6124919dd23</anchor>
      <arglist>(int MyBlockRow, int BlockRowOffset, int VectorIndex, double ScalarValueReal, double ScalarValueImag)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SumIntoMyValueReal</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>a185e36e823cf6f77f818d86784b23bd3</anchor>
      <arglist>(int MyBlockRow, int BlockRowOffset, int VectorIndex, double ScalarValue)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SumIntoMyValueImag</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>a0c13527a56fc4c8369e1c257396ca11e</anchor>
      <arglist>(int MyBlockRow, int BlockRowOffset, int VectorIndex, double ScalarValue)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Scale</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>abf1ad7e2430cf97d39671cf8115fe364</anchor>
      <arglist>(double ScalarValue)</arglist>
    </member>
    <member kind="function">
      <type>part separately int</type>
      <name>Scale</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>ae7d21dd77b420988d62c673cf9aa83a8</anchor>
      <arglist>(double ScalarValueReal, double ScalarValueImag)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Scale</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>a2afbf0874d7f1ab47f447e6327679a0f</anchor>
      <arglist>(double ScalarA, const Komplex_MultiVector &amp;A)</arglist>
    </member>
    <member kind="function">
      <type>parts separately int</type>
      <name>Scale</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>ab55c4ec57ec880edde9617b061eaa1ac</anchor>
      <arglist>(double ScalarAReal, double ScalarAImag, const Komplex_MultiVector &amp;A)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Norm1</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>ad8d0a0ca08b2f0d7cd875514a7454f94</anchor>
      <arglist>(double *Result) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Norm2</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>a9e15c4c2ae842187f0ce8af28896347f</anchor>
      <arglist>(double *Result) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NormInf</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>ad84423c47b390ee8aa2d2984bb78d6ee</anchor>
      <arglist>(double *Result) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Multiply</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>a143455637e0007a7351b4ec19a58cbad</anchor>
      <arglist>(char TransA, char TransB, double ScalarAB, const Komplex_MultiVector &amp;A, const Komplex_MultiVector &amp;B, double ScalarThis)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Multiply</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>a5c3ac599f1253657d5074e65846ceaa3</anchor>
      <arglist>(double ScalarAB, const Komplex_MultiVector &amp;A, const Komplex_MultiVector &amp;B, double ScalarThis)</arglist>
    </member>
    <member kind="function">
      <type>Komplex_MultiVector &amp;</type>
      <name>operator=</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>aa92e7001f075b2685f95cc1a0412d6b1</anchor>
      <arglist>(const Komplex_MultiVector &amp;Source)</arglist>
    </member>
    <member kind="function">
      <type>double *&amp;</type>
      <name>operator[]</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>a2729007d44f000a12af2eb9bd69df361</anchor>
      <arglist>(int i)</arglist>
    </member>
    <member kind="function">
      <type>double *const &amp;</type>
      <name>operator[]</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>a1887b2317d68e7f17a4093df2ce21ed9</anchor>
      <arglist>(int i) const </arglist>
    </member>
    <member kind="function">
      <type>Komplex_Vector *&amp;</type>
      <name>operator()</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>aa973b6e2259b2dedb2e961d5325d2aa5</anchor>
      <arglist>(int i)</arglist>
    </member>
    <member kind="function">
      <type>const Komplex_Vector *&amp;</type>
      <name>operator()</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>a86e8f7e56c079f4c4c9f3ab3138591fe</anchor>
      <arglist>(int i) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumVectors</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>adbac3772556e84638a666909fb172ddd</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>MyLength</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>aab6002d863a483623b431e08264a3801</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GlobalLength</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>ad52d44d03cc7727c8bf852a722feed7d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Stride</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>a3232253fd7ba87e8fea63b2922692e6a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>ConstantStride</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>a6eb32b06f1c23248443abe6dc572e137</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Print</name>
      <anchorfile>classKomplex__MultiVector.html</anchorfile>
      <anchor>a3fab26673b5a6ad7c849a39185a43737</anchor>
      <arglist>(ostream &amp;os) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Komplex_Operator</name>
    <filename>classKomplex__Operator.html</filename>
    <base virtualness="virtual">Epetra_Operator</base>
    <member kind="function">
      <type></type>
      <name>Komplex_Operator</name>
      <anchorfile>classKomplex__Operator.html</anchorfile>
      <anchor>a778c6c9ca57c1e5f10e4f8ec76528557</anchor>
      <arglist>(Epetra_DataAccess CV, Epetra_Operator *Operator, Komplex_KForms KForm=K1)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Komplex_Operator</name>
      <anchorfile>classKomplex__Operator.html</anchorfile>
      <anchor>aadf6f5209b7ea379bec5e4ac6edc5809</anchor>
      <arglist>(Epetra_DataAccess CV, Epetra_Operator *Real, Epetra_Operator *Imag, Komplex_KForms KForm=K1)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~Komplex_Operator</name>
      <anchorfile>classKomplex__Operator.html</anchorfile>
      <anchor>ac9c0561d103c5e73c0588d097a37639e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetUseTranspose</name>
      <anchorfile>classKomplex__Operator.html</anchorfile>
      <anchor>a1a5be968ae2b027f75f105700f77c79d</anchor>
      <arglist>(bool UseTranspose)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Apply</name>
      <anchorfile>classKomplex__Operator.html</anchorfile>
      <anchor>a5a3e1f5c5afdf4d940694046ef19ae56</anchor>
      <arglist>(const Epetra_MultiVector &amp;X, Epetra_MultiVector &amp;Y) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ApplyInverse</name>
      <anchorfile>classKomplex__Operator.html</anchorfile>
      <anchor>a7db5d2d3a5f1f4d7112d9aad1fdf4681</anchor>
      <arglist>(const Epetra_MultiVector &amp;X, Epetra_MultiVector &amp;Y) const </arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>NormInf</name>
      <anchorfile>classKomplex__Operator.html</anchorfile>
      <anchor>a74261a767b96a3d41de45ca07bd1d345</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const char *</type>
      <name>Label</name>
      <anchorfile>classKomplex__Operator.html</anchorfile>
      <anchor>a54f0010518bd37bce6d6d05d8063b466</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>UseTranspose</name>
      <anchorfile>classKomplex__Operator.html</anchorfile>
      <anchor>a4f4280cefd9674c9983d27502b733445</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>HasNormInf</name>
      <anchorfile>classKomplex__Operator.html</anchorfile>
      <anchor>a35262b858dffeb0757e77431a23f2493</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_Comm &amp;</type>
      <name>Comm</name>
      <anchorfile>classKomplex__Operator.html</anchorfile>
      <anchor>a3d72ea616b9683f00b46b57af9da2484</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_Map &amp;</type>
      <name>OperatorDomainMap</name>
      <anchorfile>classKomplex__Operator.html</anchorfile>
      <anchor>a992b2caa82f28e37b2070ddfe65be19e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_Map &amp;</type>
      <name>OperatorRangeMap</name>
      <anchorfile>classKomplex__Operator.html</anchorfile>
      <anchor>aacff26205c1e08a269902a65e76f5ecd</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Komplex_Operator</name>
      <anchorfile>classKomplex__Operator.html</anchorfile>
      <anchor>a778c6c9ca57c1e5f10e4f8ec76528557</anchor>
      <arglist>(Epetra_DataAccess CV, Epetra_Operator *Operator, Komplex_KForms KForm=K1)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Komplex_Operator</name>
      <anchorfile>classKomplex__Operator.html</anchorfile>
      <anchor>aadf6f5209b7ea379bec5e4ac6edc5809</anchor>
      <arglist>(Epetra_DataAccess CV, Epetra_Operator *Real, Epetra_Operator *Imag, Komplex_KForms KForm=K1)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~Komplex_Operator</name>
      <anchorfile>classKomplex__Operator.html</anchorfile>
      <anchor>ac9c0561d103c5e73c0588d097a37639e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetUseTranspose</name>
      <anchorfile>classKomplex__Operator.html</anchorfile>
      <anchor>a1a5be968ae2b027f75f105700f77c79d</anchor>
      <arglist>(bool UseTranspose)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Apply</name>
      <anchorfile>classKomplex__Operator.html</anchorfile>
      <anchor>a5a3e1f5c5afdf4d940694046ef19ae56</anchor>
      <arglist>(const Epetra_MultiVector &amp;X, Epetra_MultiVector &amp;Y) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ApplyInverse</name>
      <anchorfile>classKomplex__Operator.html</anchorfile>
      <anchor>a7db5d2d3a5f1f4d7112d9aad1fdf4681</anchor>
      <arglist>(const Epetra_MultiVector &amp;X, Epetra_MultiVector &amp;Y) const </arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>NormInf</name>
      <anchorfile>classKomplex__Operator.html</anchorfile>
      <anchor>a74261a767b96a3d41de45ca07bd1d345</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const char *</type>
      <name>Label</name>
      <anchorfile>classKomplex__Operator.html</anchorfile>
      <anchor>a54f0010518bd37bce6d6d05d8063b466</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>UseTranspose</name>
      <anchorfile>classKomplex__Operator.html</anchorfile>
      <anchor>a4f4280cefd9674c9983d27502b733445</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>HasNormInf</name>
      <anchorfile>classKomplex__Operator.html</anchorfile>
      <anchor>a35262b858dffeb0757e77431a23f2493</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_Comm &amp;</type>
      <name>Comm</name>
      <anchorfile>classKomplex__Operator.html</anchorfile>
      <anchor>a3d72ea616b9683f00b46b57af9da2484</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_Map &amp;</type>
      <name>OperatorDomainMap</name>
      <anchorfile>classKomplex__Operator.html</anchorfile>
      <anchor>a992b2caa82f28e37b2070ddfe65be19e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_Map &amp;</type>
      <name>OperatorRangeMap</name>
      <anchorfile>classKomplex__Operator.html</anchorfile>
      <anchor>aacff26205c1e08a269902a65e76f5ecd</anchor>
      <arglist>() const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Komplex_Ordering</name>
    <filename>classKomplex__Ordering.html</filename>
    <member kind="function">
      <type></type>
      <name>Komplex_Ordering</name>
      <anchorfile>classKomplex__Ordering.html</anchorfile>
      <anchor>a97e9e960ce913621555438ff399a3980</anchor>
      <arglist>(const Epetra_BlockMap &amp;Map, Komplex_KForms KForm, bool IsOneObject)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Komplex_Ordering</name>
      <anchorfile>classKomplex__Ordering.html</anchorfile>
      <anchor>a502da3f69e0c61b0d95db38b89360e92</anchor>
      <arglist>(Komplex_Ordering &amp;Source)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~Komplex_Ordering</name>
      <anchorfile>classKomplex__Ordering.html</anchorfile>
      <anchor>abe72d152a854367d70f1fecb49a4077b</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>Komplex_KForms</type>
      <name>KForm</name>
      <anchorfile>classKomplex__Ordering.html</anchorfile>
      <anchor>a688d26b7fec42434580a7705087ba53e</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SwitchKForm</name>
      <anchorfile>classKomplex__Ordering.html</anchorfile>
      <anchor>a3d8a304dad380f3ea1fd9d6d3c8da07a</anchor>
      <arglist>(Komplex_KForms NewKForm)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>PermutationVector</name>
      <anchorfile>classKomplex__Ordering.html</anchorfile>
      <anchor>ae466b92e5ae99233e15358784b4f3ba4</anchor>
      <arglist>(int *Perms)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ScalingVector</name>
      <anchorfile>classKomplex__Ordering.html</anchorfile>
      <anchor>a8c72e40f80784f2c64ba8bbc87256a4f</anchor>
      <arglist>(double *Scales)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GlobalIndex</name>
      <anchorfile>classKomplex__Ordering.html</anchorfile>
      <anchor>a7ed1fc01eaba7a21d1d6d2be26414453</anchor>
      <arglist>(int GlobalRow, int &amp;Index)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GlobalScaling</name>
      <anchorfile>classKomplex__Ordering.html</anchorfile>
      <anchor>a86867812342f8e73d3f54f6c75061a0b</anchor>
      <arglist>(int GlobalRow, double &amp;Scalar)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>MyIndex</name>
      <anchorfile>classKomplex__Ordering.html</anchorfile>
      <anchor>a129b6701cc954c638a23c6690461585e</anchor>
      <arglist>(int MyRow, int &amp;Index)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>MyScaling</name>
      <anchorfile>classKomplex__Ordering.html</anchorfile>
      <anchor>afb3ae2125ff48fbd9aa51765e6a15884</anchor>
      <arglist>(int MyRow, double &amp;Scalar)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Reset</name>
      <anchorfile>classKomplex__Ordering.html</anchorfile>
      <anchor>aba6970a114a7ec3dd59c5010bfc027ea</anchor>
      <arglist>(Komplex_KForms NewKForm)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Komplex_Ordering</name>
      <anchorfile>classKomplex__Ordering.html</anchorfile>
      <anchor>a97e9e960ce913621555438ff399a3980</anchor>
      <arglist>(const Epetra_BlockMap &amp;Map, Komplex_KForms KForm, bool IsOneObject)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Komplex_Ordering</name>
      <anchorfile>classKomplex__Ordering.html</anchorfile>
      <anchor>a502da3f69e0c61b0d95db38b89360e92</anchor>
      <arglist>(Komplex_Ordering &amp;Source)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~Komplex_Ordering</name>
      <anchorfile>classKomplex__Ordering.html</anchorfile>
      <anchor>abe72d152a854367d70f1fecb49a4077b</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>Komplex_KForms</type>
      <name>KForm</name>
      <anchorfile>classKomplex__Ordering.html</anchorfile>
      <anchor>a688d26b7fec42434580a7705087ba53e</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SwitchKForm</name>
      <anchorfile>classKomplex__Ordering.html</anchorfile>
      <anchor>a3d8a304dad380f3ea1fd9d6d3c8da07a</anchor>
      <arglist>(Komplex_KForms NewKForm)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>PermutationVector</name>
      <anchorfile>classKomplex__Ordering.html</anchorfile>
      <anchor>ae466b92e5ae99233e15358784b4f3ba4</anchor>
      <arglist>(int *Perms)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ScalingVector</name>
      <anchorfile>classKomplex__Ordering.html</anchorfile>
      <anchor>a8c72e40f80784f2c64ba8bbc87256a4f</anchor>
      <arglist>(double *Scales)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GlobalIndex</name>
      <anchorfile>classKomplex__Ordering.html</anchorfile>
      <anchor>a7ed1fc01eaba7a21d1d6d2be26414453</anchor>
      <arglist>(int GlobalRow, int &amp;Index)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GlobalScaling</name>
      <anchorfile>classKomplex__Ordering.html</anchorfile>
      <anchor>a86867812342f8e73d3f54f6c75061a0b</anchor>
      <arglist>(int GlobalRow, double &amp;Scalar)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>MyIndex</name>
      <anchorfile>classKomplex__Ordering.html</anchorfile>
      <anchor>a129b6701cc954c638a23c6690461585e</anchor>
      <arglist>(int MyRow, int &amp;Index)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>MyScaling</name>
      <anchorfile>classKomplex__Ordering.html</anchorfile>
      <anchor>afb3ae2125ff48fbd9aa51765e6a15884</anchor>
      <arglist>(int MyRow, double &amp;Scalar)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Reset</name>
      <anchorfile>classKomplex__Ordering.html</anchorfile>
      <anchor>aba6970a114a7ec3dd59c5010bfc027ea</anchor>
      <arglist>(Komplex_KForms NewKForm)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Komplex_RowMatrix</name>
    <filename>classKomplex__RowMatrix.html</filename>
    <base virtualness="virtual">Epetra_RowMatrix</base>
    <member kind="function">
      <type></type>
      <name>Komplex_RowMatrix</name>
      <anchorfile>classKomplex__RowMatrix.html</anchorfile>
      <anchor>ad0717f72de954f32c81ebb23872cea78</anchor>
      <arglist>(Epetra_DataAccess CV, const Epetra_BlockMap &amp;RowMap, int NumEntriesPerRow, Komplex_KForms KForm=K1)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Komplex_RowMatrix</name>
      <anchorfile>classKomplex__RowMatrix.html</anchorfile>
      <anchor>a7f24fb0f7b694b14ae332784757a7400</anchor>
      <arglist>(Epetra_DataAccess CV, const Epetra_BlockMap &amp;RowMap, int *NumEntriesPerRow, Komplex_KForms KForm=K1)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Komplex_RowMatrix</name>
      <anchorfile>classKomplex__RowMatrix.html</anchorfile>
      <anchor>ad71532fb8332fe138f599a7dac18996a</anchor>
      <arglist>(Epetra_DataAccess CV, const Epetra_BlockMap &amp;RowMap, const Epetra_BlockMap &amp;ColMap, int NumEntriesPerRow, Komplex_KForms KForm=K1)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Komplex_RowMatrix</name>
      <anchorfile>classKomplex__RowMatrix.html</anchorfile>
      <anchor>a09635f1831797aa78022b8868b72b440</anchor>
      <arglist>(Epetra_DataAccess CV, const Epetra_BlockMap &amp;RowMap, const Epetra_BlockMap &amp;ColMap, int *NumEntriesPerRow, Komplex_KForms KForm=K1)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Komplex_RowMatrix</name>
      <anchorfile>classKomplex__RowMatrix.html</anchorfile>
      <anchor>a5a897e8b5c9fcc07048b2faf6bfab7c0</anchor>
      <arglist>(Epetra_DataAccess CV, const Epetra_CrsGraph &amp;Graph, Komplex_KForms KForm=K1)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Komplex_RowMatrix</name>
      <anchorfile>classKomplex__RowMatrix.html</anchorfile>
      <anchor>afc62f12f406057829cc01e2e13d03fa0</anchor>
      <arglist>(double cr, double ci, Epetra_RowMatrix *A, Komplex_KForms KForm=K1)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Komplex_RowMatrix</name>
      <anchorfile>classKomplex__RowMatrix.html</anchorfile>
      <anchor>a88ac6db077c4a0f35a61916348864afb</anchor>
      <arglist>(double c0r, double c0i, Epetra_RowMatrix *A0, double c1r, double c1i, Epetra_RowMatrix *A1, Komplex_KForms KForm=K1)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Komplex_RowMatrix</name>
      <anchorfile>classKomplex__RowMatrix.html</anchorfile>
      <anchor>a3318ea461826dc8cdd3ee23445f7baa1</anchor>
      <arglist>(const Komplex_RowMatrix &amp;Matrix)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~Komplex_RowMatrix</name>
      <anchorfile>classKomplex__RowMatrix.html</anchorfile>
      <anchor>ad452bc383ab440006951a73d550e87e6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>Filled</name>
      <anchorfile>classKomplex__RowMatrix.html</anchorfile>
      <anchor>a8b108263a675cd5970469e7c09711311</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>StorageOptimized</name>
      <anchorfile>classKomplex__RowMatrix.html</anchorfile>
      <anchor>a5f107f6895c57957d7a82485e6cbf2bb</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>IndicesAreGlobal</name>
      <anchorfile>classKomplex__RowMatrix.html</anchorfile>
      <anchor>a5d55cd7e665c9a7e1920a1065fe534a3</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>IndicesAreLocal</name>
      <anchorfile>classKomplex__RowMatrix.html</anchorfile>
      <anchor>abbc781c3aebb9aac6c76e1b71e963773</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>IndicesAreContiguous</name>
      <anchorfile>classKomplex__RowMatrix.html</anchorfile>
      <anchor>a1b52855f857160979840f9985b9ed025</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>NoDiagonal</name>
      <anchorfile>classKomplex__RowMatrix.html</anchorfile>
      <anchor>a02e25218b75580d0263aab348a0830e0</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>IndexBase</name>
      <anchorfile>classKomplex__RowMatrix.html</anchorfile>
      <anchor>a41ae0f79e461d319888deef4cc61577c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_CrsGraph &amp;</type>
      <name>Graph</name>
      <anchorfile>classKomplex__RowMatrix.html</anchorfile>
      <anchor>ab460550d23dfa405aca29e05f17a0879</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_Map &amp;</type>
      <name>RowMap</name>
      <anchorfile>classKomplex__RowMatrix.html</anchorfile>
      <anchor>a100ec44c445473d030deaa00ff0eb1ba</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_Map &amp;</type>
      <name>ColMap</name>
      <anchorfile>classKomplex__RowMatrix.html</anchorfile>
      <anchor>a0780b28d52232399b7132c481253926b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_Map &amp;</type>
      <name>DomainMap</name>
      <anchorfile>classKomplex__RowMatrix.html</anchorfile>
      <anchor>a97ca5594c08ec52fd80b8c3f29ebe7cf</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_Map &amp;</type>
      <name>RangeMap</name>
      <anchorfile>classKomplex__RowMatrix.html</anchorfile>
      <anchor>aa6cbbe33f69f9b37e740acdbf9553971</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_Import *</type>
      <name>Importer</name>
      <anchorfile>classKomplex__RowMatrix.html</anchorfile>
      <anchor>a6a2de0bc2ca53d28ade476131cc555f3</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_Export *</type>
      <name>Exporter</name>
      <anchorfile>classKomplex__RowMatrix.html</anchorfile>
      <anchor>a5af094e461ace918c1d27b945d59c9bf</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_Comm &amp;</type>
      <name>Comm</name>
      <anchorfile>classKomplex__RowMatrix.html</anchorfile>
      <anchor>a8c952303f48ecc0f91d1a23255b1f990</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>PutScalar</name>
      <anchorfile>classKomplex__RowMatrix.html</anchorfile>
      <anchor>aff14a86c68c16f228cb8139c96758b24</anchor>
      <arglist>(double ScalarConstant)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Scale</name>
      <anchorfile>classKomplex__RowMatrix.html</anchorfile>
      <anchor>ae2a79f4bcbaa438496d938e5be1ad21f</anchor>
      <arglist>(double ScalarConstant)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ReplaceDiagonalValues</name>
      <anchorfile>classKomplex__RowMatrix.html</anchorfile>
      <anchor>ae07a3219691bfd82a1c16558290f27ad</anchor>
      <arglist>(const Epetra_Vector &amp;Diagonal)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>FillComplete</name>
      <anchorfile>classKomplex__RowMatrix.html</anchorfile>
      <anchor>a13299cef1d477d85e30b90bbc4c3aa9d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>FillComplete</name>
      <anchorfile>classKomplex__RowMatrix.html</anchorfile>
      <anchor>a4b023c561604c969f41a298676245405</anchor>
      <arglist>(const Epetra_Map &amp;DomainMap, const Epetra_Map &amp;RangeMap)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Multiply</name>
      <anchorfile>classKomplex__RowMatrix.html</anchorfile>
      <anchor>a61f285222c97453cf3ecf3b233cc8678</anchor>
      <arglist>(bool TransA, const Epetra_MultiVector &amp;X, Epetra_MultiVector &amp;Y) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Solve</name>
      <anchorfile>classKomplex__RowMatrix.html</anchorfile>
      <anchor>ac7d5381295dcb0df2a43f687b89d5fb1</anchor>
      <arglist>(bool Upper, bool Trans, bool UnitDiagonal, const Epetra_Vector &amp;x, Epetra_Vector &amp;y) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Solve</name>
      <anchorfile>classKomplex__RowMatrix.html</anchorfile>
      <anchor>a49d9b3496742c1e42740a73f6400c2a7</anchor>
      <arglist>(bool Upper, bool Trans, bool UnitDiagonal, const Epetra_MultiVector &amp;X, Epetra_MultiVector &amp;Y) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>InvRowSums</name>
      <anchorfile>classKomplex__RowMatrix.html</anchorfile>
      <anchor>a9ef762a71a1f78ca3c73ff5683115973</anchor>
      <arglist>(Epetra_Vector &amp;x) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>LeftScale</name>
      <anchorfile>classKomplex__RowMatrix.html</anchorfile>
      <anchor>a881a923381f211baa57d16e1c8ed9424</anchor>
      <arglist>(const Epetra_Vector &amp;x)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>InvColSums</name>
      <anchorfile>classKomplex__RowMatrix.html</anchorfile>
      <anchor>a60b7ce078af9e6bf5080da04f181cfc0</anchor>
      <arglist>(Epetra_Vector &amp;x) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>RightScale</name>
      <anchorfile>classKomplex__RowMatrix.html</anchorfile>
      <anchor>ac160fa1e913f4d2c518c52d54065edc5</anchor>
      <arglist>(const Epetra_Vector &amp;x)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>LowerTriangular</name>
      <anchorfile>classKomplex__RowMatrix.html</anchorfile>
      <anchor>a618320d934fcf41aeed5ac7463a48380</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>UpperTriangular</name>
      <anchorfile>classKomplex__RowMatrix.html</anchorfile>
      <anchor>aece3b47f30b8f683e55e2f5575c99efd</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>NormInf</name>
      <anchorfile>classKomplex__RowMatrix.html</anchorfile>
      <anchor>a7ea9df57e8b09faa19ff0028d037b4b9</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>NormOne</name>
      <anchorfile>classKomplex__RowMatrix.html</anchorfile>
      <anchor>ab5280e0fc8142123a1a1b7b4ba7ffd6a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumMyNonzeros</name>
      <anchorfile>classKomplex__RowMatrix.html</anchorfile>
      <anchor>ad0e8cc244344c9d16689f54667d69f44</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumMyRows</name>
      <anchorfile>classKomplex__RowMatrix.html</anchorfile>
      <anchor>a145912606fe2f08ac43e98786e945d99</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumMyCols</name>
      <anchorfile>classKomplex__RowMatrix.html</anchorfile>
      <anchor>a40354092092eb1f20a2e63483f9dce1e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumGlobalRows</name>
      <anchorfile>classKomplex__RowMatrix.html</anchorfile>
      <anchor>a481cd813aa56665d23ac672f17ff3b62</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumGlobalCols</name>
      <anchorfile>classKomplex__RowMatrix.html</anchorfile>
      <anchor>a4f5b96a361b4a610e142a8af1414abc0</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumGlobalNonzeros</name>
      <anchorfile>classKomplex__RowMatrix.html</anchorfile>
      <anchor>a2fc489603c3bf2abbd153ba47930fef4</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumMyDiagonals</name>
      <anchorfile>classKomplex__RowMatrix.html</anchorfile>
      <anchor>a92f0086a317166e83d8c0d0c041adaa3</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumGlobalDiagonals</name>
      <anchorfile>classKomplex__RowMatrix.html</anchorfile>
      <anchor>a223022a6641aa78b2ac3b146203aa391</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ExtractGlobalRowCopy</name>
      <anchorfile>classKomplex__RowMatrix.html</anchorfile>
      <anchor>aa4cf18e8b679cc7608eafc0ef9307455</anchor>
      <arglist>(int GlobalRow, int Length, int &amp;NumEntries, double *Values, int *Indices) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ExtractGlobalRowCopy</name>
      <anchorfile>classKomplex__RowMatrix.html</anchorfile>
      <anchor>a1233f3d12e08d812c76dc7baa4fd17ba</anchor>
      <arglist>(int GlobalRow, int Length, int &amp;NumEntries, double *Values) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ExtractMyRowCopy</name>
      <anchorfile>classKomplex__RowMatrix.html</anchorfile>
      <anchor>a82936a6e0cb6ab34aaa22904ddce74f7</anchor>
      <arglist>(int MyRow, int Length, int &amp;NumEntries, double *Values, int *Indices) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumMyRowEntries</name>
      <anchorfile>classKomplex__RowMatrix.html</anchorfile>
      <anchor>ad4ebc592d83d6ccc9388dd2d43576a81</anchor>
      <arglist>(int MyRow, int &amp;NumEntries) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ExtractDiagonalCopy</name>
      <anchorfile>classKomplex__RowMatrix.html</anchorfile>
      <anchor>a8b1a50bdca3a6de9628511875616537c</anchor>
      <arglist>(Epetra_Vector &amp;Diagonal) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>MaxNumEntries</name>
      <anchorfile>classKomplex__RowMatrix.html</anchorfile>
      <anchor>a3a1fe623cf58e03e0ce630892696b98e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_Map &amp;</type>
      <name>RowMatrixRowMap</name>
      <anchorfile>classKomplex__RowMatrix.html</anchorfile>
      <anchor>a858d4e8a30021b59160a67c12cd88901</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_Map &amp;</type>
      <name>RowMatrixColMap</name>
      <anchorfile>classKomplex__RowMatrix.html</anchorfile>
      <anchor>a4e50a32e5e08c14f0b19724c03a466a3</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_Import *</type>
      <name>RowMatrixImporter</name>
      <anchorfile>classKomplex__RowMatrix.html</anchorfile>
      <anchor>afbad3072cb2c572ff73f95e88500c44e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Print</name>
      <anchorfile>classKomplex__RowMatrix.html</anchorfile>
      <anchor>a635e0a77a46bb5c7c5c2407d418d5c62</anchor>
      <arglist>(ostream &amp;os) const </arglist>
    </member>
    <member kind="function">
      <type>const char *</type>
      <name>Label</name>
      <anchorfile>classKomplex__RowMatrix.html</anchorfile>
      <anchor>a7534ff2c3c206728acee01f205d90188</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetUseTranspose</name>
      <anchorfile>classKomplex__RowMatrix.html</anchorfile>
      <anchor>a981b0441240e4fd920a54873d2c774ee</anchor>
      <arglist>(bool UseTranspose)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Apply</name>
      <anchorfile>classKomplex__RowMatrix.html</anchorfile>
      <anchor>ab51ae264e5091f7353c01ad8a996e74d</anchor>
      <arglist>(const Epetra_MultiVector &amp;X, Epetra_MultiVector &amp;Y) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ApplyInverse</name>
      <anchorfile>classKomplex__RowMatrix.html</anchorfile>
      <anchor>af6800130a044f2501d2031929a744861</anchor>
      <arglist>(const Epetra_MultiVector &amp;X, Epetra_MultiVector &amp;Y) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>HasNormInf</name>
      <anchorfile>classKomplex__RowMatrix.html</anchorfile>
      <anchor>afaa13759ad6530e0baf1fca4953f318f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>UseTranspose</name>
      <anchorfile>classKomplex__RowMatrix.html</anchorfile>
      <anchor>ac779c43ce0b9d8851751f284726aa714</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_Map &amp;</type>
      <name>OperatorDomainMap</name>
      <anchorfile>classKomplex__RowMatrix.html</anchorfile>
      <anchor>a822fc2746ca2888eff20bb9330811580</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_Map &amp;</type>
      <name>OperatorRangeMap</name>
      <anchorfile>classKomplex__RowMatrix.html</anchorfile>
      <anchor>a13270942e4f350c59c0d77d99345ecac</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Komplex_RowMatrix</name>
      <anchorfile>classKomplex__RowMatrix.html</anchorfile>
      <anchor>ad0717f72de954f32c81ebb23872cea78</anchor>
      <arglist>(Epetra_DataAccess CV, const Epetra_BlockMap &amp;RowMap, int NumEntriesPerRow, Komplex_KForms KForm=K1)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Komplex_RowMatrix</name>
      <anchorfile>classKomplex__RowMatrix.html</anchorfile>
      <anchor>a7f24fb0f7b694b14ae332784757a7400</anchor>
      <arglist>(Epetra_DataAccess CV, const Epetra_BlockMap &amp;RowMap, int *NumEntriesPerRow, Komplex_KForms KForm=K1)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Komplex_RowMatrix</name>
      <anchorfile>classKomplex__RowMatrix.html</anchorfile>
      <anchor>ad71532fb8332fe138f599a7dac18996a</anchor>
      <arglist>(Epetra_DataAccess CV, const Epetra_BlockMap &amp;RowMap, const Epetra_BlockMap &amp;ColMap, int NumEntriesPerRow, Komplex_KForms KForm=K1)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Komplex_RowMatrix</name>
      <anchorfile>classKomplex__RowMatrix.html</anchorfile>
      <anchor>a09635f1831797aa78022b8868b72b440</anchor>
      <arglist>(Epetra_DataAccess CV, const Epetra_BlockMap &amp;RowMap, const Epetra_BlockMap &amp;ColMap, int *NumEntriesPerRow, Komplex_KForms KForm=K1)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Komplex_RowMatrix</name>
      <anchorfile>classKomplex__RowMatrix.html</anchorfile>
      <anchor>a5a897e8b5c9fcc07048b2faf6bfab7c0</anchor>
      <arglist>(Epetra_DataAccess CV, const Epetra_CrsGraph &amp;Graph, Komplex_KForms KForm=K1)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Komplex_RowMatrix</name>
      <anchorfile>classKomplex__RowMatrix.html</anchorfile>
      <anchor>afc62f12f406057829cc01e2e13d03fa0</anchor>
      <arglist>(double cr, double ci, Epetra_RowMatrix *A, Komplex_KForms KForm=K1)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Komplex_RowMatrix</name>
      <anchorfile>classKomplex__RowMatrix.html</anchorfile>
      <anchor>a88ac6db077c4a0f35a61916348864afb</anchor>
      <arglist>(double c0r, double c0i, Epetra_RowMatrix *A0, double c1r, double c1i, Epetra_RowMatrix *A1, Komplex_KForms KForm=K1)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Komplex_RowMatrix</name>
      <anchorfile>classKomplex__RowMatrix.html</anchorfile>
      <anchor>a3318ea461826dc8cdd3ee23445f7baa1</anchor>
      <arglist>(const Komplex_RowMatrix &amp;Matrix)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~Komplex_RowMatrix</name>
      <anchorfile>classKomplex__RowMatrix.html</anchorfile>
      <anchor>ad452bc383ab440006951a73d550e87e6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>Filled</name>
      <anchorfile>classKomplex__RowMatrix.html</anchorfile>
      <anchor>a8b108263a675cd5970469e7c09711311</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>StorageOptimized</name>
      <anchorfile>classKomplex__RowMatrix.html</anchorfile>
      <anchor>a5f107f6895c57957d7a82485e6cbf2bb</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>IndicesAreGlobal</name>
      <anchorfile>classKomplex__RowMatrix.html</anchorfile>
      <anchor>a5d55cd7e665c9a7e1920a1065fe534a3</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>IndicesAreLocal</name>
      <anchorfile>classKomplex__RowMatrix.html</anchorfile>
      <anchor>abbc781c3aebb9aac6c76e1b71e963773</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>IndicesAreContiguous</name>
      <anchorfile>classKomplex__RowMatrix.html</anchorfile>
      <anchor>a1b52855f857160979840f9985b9ed025</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>NoDiagonal</name>
      <anchorfile>classKomplex__RowMatrix.html</anchorfile>
      <anchor>a02e25218b75580d0263aab348a0830e0</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>IndexBase</name>
      <anchorfile>classKomplex__RowMatrix.html</anchorfile>
      <anchor>a41ae0f79e461d319888deef4cc61577c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_CrsGraph &amp;</type>
      <name>Graph</name>
      <anchorfile>classKomplex__RowMatrix.html</anchorfile>
      <anchor>ab460550d23dfa405aca29e05f17a0879</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_Map &amp;</type>
      <name>RowMap</name>
      <anchorfile>classKomplex__RowMatrix.html</anchorfile>
      <anchor>a100ec44c445473d030deaa00ff0eb1ba</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_Map &amp;</type>
      <name>ColMap</name>
      <anchorfile>classKomplex__RowMatrix.html</anchorfile>
      <anchor>a0780b28d52232399b7132c481253926b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_Map &amp;</type>
      <name>DomainMap</name>
      <anchorfile>classKomplex__RowMatrix.html</anchorfile>
      <anchor>a97ca5594c08ec52fd80b8c3f29ebe7cf</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_Map &amp;</type>
      <name>RangeMap</name>
      <anchorfile>classKomplex__RowMatrix.html</anchorfile>
      <anchor>aa6cbbe33f69f9b37e740acdbf9553971</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_Import *</type>
      <name>Importer</name>
      <anchorfile>classKomplex__RowMatrix.html</anchorfile>
      <anchor>a6a2de0bc2ca53d28ade476131cc555f3</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_Export *</type>
      <name>Exporter</name>
      <anchorfile>classKomplex__RowMatrix.html</anchorfile>
      <anchor>a5af094e461ace918c1d27b945d59c9bf</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_Comm &amp;</type>
      <name>Comm</name>
      <anchorfile>classKomplex__RowMatrix.html</anchorfile>
      <anchor>a8c952303f48ecc0f91d1a23255b1f990</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>PutScalar</name>
      <anchorfile>classKomplex__RowMatrix.html</anchorfile>
      <anchor>aff14a86c68c16f228cb8139c96758b24</anchor>
      <arglist>(double ScalarConstant)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Scale</name>
      <anchorfile>classKomplex__RowMatrix.html</anchorfile>
      <anchor>ae2a79f4bcbaa438496d938e5be1ad21f</anchor>
      <arglist>(double ScalarConstant)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ReplaceDiagonalValues</name>
      <anchorfile>classKomplex__RowMatrix.html</anchorfile>
      <anchor>ae07a3219691bfd82a1c16558290f27ad</anchor>
      <arglist>(const Epetra_Vector &amp;Diagonal)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>FillComplete</name>
      <anchorfile>classKomplex__RowMatrix.html</anchorfile>
      <anchor>a13299cef1d477d85e30b90bbc4c3aa9d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>FillComplete</name>
      <anchorfile>classKomplex__RowMatrix.html</anchorfile>
      <anchor>a4b023c561604c969f41a298676245405</anchor>
      <arglist>(const Epetra_Map &amp;DomainMap, const Epetra_Map &amp;RangeMap)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Multiply</name>
      <anchorfile>classKomplex__RowMatrix.html</anchorfile>
      <anchor>a61f285222c97453cf3ecf3b233cc8678</anchor>
      <arglist>(bool TransA, const Epetra_MultiVector &amp;X, Epetra_MultiVector &amp;Y) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Solve</name>
      <anchorfile>classKomplex__RowMatrix.html</anchorfile>
      <anchor>ac7d5381295dcb0df2a43f687b89d5fb1</anchor>
      <arglist>(bool Upper, bool Trans, bool UnitDiagonal, const Epetra_Vector &amp;x, Epetra_Vector &amp;y) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Solve</name>
      <anchorfile>classKomplex__RowMatrix.html</anchorfile>
      <anchor>a49d9b3496742c1e42740a73f6400c2a7</anchor>
      <arglist>(bool Upper, bool Trans, bool UnitDiagonal, const Epetra_MultiVector &amp;X, Epetra_MultiVector &amp;Y) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>InvRowSums</name>
      <anchorfile>classKomplex__RowMatrix.html</anchorfile>
      <anchor>a9ef762a71a1f78ca3c73ff5683115973</anchor>
      <arglist>(Epetra_Vector &amp;x) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>LeftScale</name>
      <anchorfile>classKomplex__RowMatrix.html</anchorfile>
      <anchor>a881a923381f211baa57d16e1c8ed9424</anchor>
      <arglist>(const Epetra_Vector &amp;x)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>InvColSums</name>
      <anchorfile>classKomplex__RowMatrix.html</anchorfile>
      <anchor>a60b7ce078af9e6bf5080da04f181cfc0</anchor>
      <arglist>(Epetra_Vector &amp;x) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>RightScale</name>
      <anchorfile>classKomplex__RowMatrix.html</anchorfile>
      <anchor>ac160fa1e913f4d2c518c52d54065edc5</anchor>
      <arglist>(const Epetra_Vector &amp;x)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>LowerTriangular</name>
      <anchorfile>classKomplex__RowMatrix.html</anchorfile>
      <anchor>a618320d934fcf41aeed5ac7463a48380</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>UpperTriangular</name>
      <anchorfile>classKomplex__RowMatrix.html</anchorfile>
      <anchor>aece3b47f30b8f683e55e2f5575c99efd</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>NormInf</name>
      <anchorfile>classKomplex__RowMatrix.html</anchorfile>
      <anchor>a7ea9df57e8b09faa19ff0028d037b4b9</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>NormOne</name>
      <anchorfile>classKomplex__RowMatrix.html</anchorfile>
      <anchor>ab5280e0fc8142123a1a1b7b4ba7ffd6a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumMyNonzeros</name>
      <anchorfile>classKomplex__RowMatrix.html</anchorfile>
      <anchor>ad0e8cc244344c9d16689f54667d69f44</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumMyRows</name>
      <anchorfile>classKomplex__RowMatrix.html</anchorfile>
      <anchor>a145912606fe2f08ac43e98786e945d99</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumMyCols</name>
      <anchorfile>classKomplex__RowMatrix.html</anchorfile>
      <anchor>a40354092092eb1f20a2e63483f9dce1e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumGlobalRows</name>
      <anchorfile>classKomplex__RowMatrix.html</anchorfile>
      <anchor>a481cd813aa56665d23ac672f17ff3b62</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumGlobalCols</name>
      <anchorfile>classKomplex__RowMatrix.html</anchorfile>
      <anchor>a4f5b96a361b4a610e142a8af1414abc0</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumGlobalNonzeros</name>
      <anchorfile>classKomplex__RowMatrix.html</anchorfile>
      <anchor>a2fc489603c3bf2abbd153ba47930fef4</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumMyDiagonals</name>
      <anchorfile>classKomplex__RowMatrix.html</anchorfile>
      <anchor>a92f0086a317166e83d8c0d0c041adaa3</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumGlobalDiagonals</name>
      <anchorfile>classKomplex__RowMatrix.html</anchorfile>
      <anchor>a223022a6641aa78b2ac3b146203aa391</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ExtractGlobalRowCopy</name>
      <anchorfile>classKomplex__RowMatrix.html</anchorfile>
      <anchor>aa4cf18e8b679cc7608eafc0ef9307455</anchor>
      <arglist>(int GlobalRow, int Length, int &amp;NumEntries, double *Values, int *Indices) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ExtractGlobalRowCopy</name>
      <anchorfile>classKomplex__RowMatrix.html</anchorfile>
      <anchor>a1233f3d12e08d812c76dc7baa4fd17ba</anchor>
      <arglist>(int GlobalRow, int Length, int &amp;NumEntries, double *Values) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ExtractMyRowCopy</name>
      <anchorfile>classKomplex__RowMatrix.html</anchorfile>
      <anchor>a82936a6e0cb6ab34aaa22904ddce74f7</anchor>
      <arglist>(int MyRow, int Length, int &amp;NumEntries, double *Values, int *Indices) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumMyRowEntries</name>
      <anchorfile>classKomplex__RowMatrix.html</anchorfile>
      <anchor>ad4ebc592d83d6ccc9388dd2d43576a81</anchor>
      <arglist>(int MyRow, int &amp;NumEntries) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ExtractDiagonalCopy</name>
      <anchorfile>classKomplex__RowMatrix.html</anchorfile>
      <anchor>a8b1a50bdca3a6de9628511875616537c</anchor>
      <arglist>(Epetra_Vector &amp;Diagonal) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>MaxNumEntries</name>
      <anchorfile>classKomplex__RowMatrix.html</anchorfile>
      <anchor>a3a1fe623cf58e03e0ce630892696b98e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_Map &amp;</type>
      <name>RowMatrixRowMap</name>
      <anchorfile>classKomplex__RowMatrix.html</anchorfile>
      <anchor>a858d4e8a30021b59160a67c12cd88901</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_Map &amp;</type>
      <name>RowMatrixColMap</name>
      <anchorfile>classKomplex__RowMatrix.html</anchorfile>
      <anchor>a4e50a32e5e08c14f0b19724c03a466a3</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_Import *</type>
      <name>RowMatrixImporter</name>
      <anchorfile>classKomplex__RowMatrix.html</anchorfile>
      <anchor>afbad3072cb2c572ff73f95e88500c44e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Print</name>
      <anchorfile>classKomplex__RowMatrix.html</anchorfile>
      <anchor>a635e0a77a46bb5c7c5c2407d418d5c62</anchor>
      <arglist>(ostream &amp;os) const </arglist>
    </member>
    <member kind="function">
      <type>const char *</type>
      <name>Label</name>
      <anchorfile>classKomplex__RowMatrix.html</anchorfile>
      <anchor>a7534ff2c3c206728acee01f205d90188</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetUseTranspose</name>
      <anchorfile>classKomplex__RowMatrix.html</anchorfile>
      <anchor>a981b0441240e4fd920a54873d2c774ee</anchor>
      <arglist>(bool UseTranspose)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Apply</name>
      <anchorfile>classKomplex__RowMatrix.html</anchorfile>
      <anchor>ab51ae264e5091f7353c01ad8a996e74d</anchor>
      <arglist>(const Epetra_MultiVector &amp;X, Epetra_MultiVector &amp;Y) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ApplyInverse</name>
      <anchorfile>classKomplex__RowMatrix.html</anchorfile>
      <anchor>af6800130a044f2501d2031929a744861</anchor>
      <arglist>(const Epetra_MultiVector &amp;X, Epetra_MultiVector &amp;Y) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>HasNormInf</name>
      <anchorfile>classKomplex__RowMatrix.html</anchorfile>
      <anchor>afaa13759ad6530e0baf1fca4953f318f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>UseTranspose</name>
      <anchorfile>classKomplex__RowMatrix.html</anchorfile>
      <anchor>ac779c43ce0b9d8851751f284726aa714</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_Map &amp;</type>
      <name>OperatorDomainMap</name>
      <anchorfile>classKomplex__RowMatrix.html</anchorfile>
      <anchor>a822fc2746ca2888eff20bb9330811580</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Epetra_Map &amp;</type>
      <name>OperatorRangeMap</name>
      <anchorfile>classKomplex__RowMatrix.html</anchorfile>
      <anchor>a13270942e4f350c59c0d77d99345ecac</anchor>
      <arglist>() const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Komplex_Vector</name>
    <filename>classKomplex__Vector.html</filename>
    <base>Komplex_MultiVector</base>
    <base>Komplex_MultiVector</base>
    <member kind="function">
      <type></type>
      <name>Komplex_Vector</name>
      <anchorfile>classKomplex__Vector.html</anchorfile>
      <anchor>ae312e8ef9771f05b02b6ca17a58b26ac</anchor>
      <arglist>(const Epetra_BlockMap &amp;Map, bool zeroOut=true)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Komplex_Vector</name>
      <anchorfile>classKomplex__Vector.html</anchorfile>
      <anchor>a7610d6f35062abb93c4888a3cd408160</anchor>
      <arglist>(const Epetra_BlockMap &amp;Map, const Epetra_Vector &amp;br, const Epetra_Vector &amp;bi)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Komplex_Vector</name>
      <anchorfile>classKomplex__Vector.html</anchorfile>
      <anchor>a288d13b442800af458377fab0bcf6fbc</anchor>
      <arglist>(const Komplex_Vector &amp;Source)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Komplex_Vector</name>
      <anchorfile>classKomplex__Vector.html</anchorfile>
      <anchor>a2a9cf86b700f35e26bfef79978723daa</anchor>
      <arglist>(Epetra_DataAccess CV, const Epetra_BlockMap &amp;Map, const Komplex_MultiVector &amp;Source, int Index)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~Komplex_Vector</name>
      <anchorfile>classKomplex__Vector.html</anchorfile>
      <anchor>a8a30c206e73c7be642c1bdb01751b110</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ReplaceGlobalValues</name>
      <anchorfile>classKomplex__Vector.html</anchorfile>
      <anchor>a0c1ee7bf5f06fe7faaad1e0cd7411563</anchor>
      <arglist>(int NumEntries, double *Values, int *Indices)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ReplaceMyValues</name>
      <anchorfile>classKomplex__Vector.html</anchorfile>
      <anchor>ab252433a3ae42a8034f79ea4daf75216</anchor>
      <arglist>(int NumEntries, double *Values, int *Indices)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SumIntoGlobalValues</name>
      <anchorfile>classKomplex__Vector.html</anchorfile>
      <anchor>aded8fdb3c103122374649553b58b19d5</anchor>
      <arglist>(int NumEntries, double *Values, int *Indices)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SumIntoMyValues</name>
      <anchorfile>classKomplex__Vector.html</anchorfile>
      <anchor>a98526546833a69348de816f0493c3ae6</anchor>
      <arglist>(int NumEntries, double *Values, int *Indices)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ReplaceGlobalValues</name>
      <anchorfile>classKomplex__Vector.html</anchorfile>
      <anchor>ad2be510aaa411e471e208e7b59ef742d</anchor>
      <arglist>(int NumEntries, int BlockOffset, double *Values, int *Indices)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ReplaceMyValues</name>
      <anchorfile>classKomplex__Vector.html</anchorfile>
      <anchor>a0d5d222658a409a3b250cfa406a7ec73</anchor>
      <arglist>(int NumEntries, int BlockOffset, double *Values, int *Indices)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SumIntoGlobalValues</name>
      <anchorfile>classKomplex__Vector.html</anchorfile>
      <anchor>ac36afb26b5480a7c4688edb9d9d0db40</anchor>
      <arglist>(int NumEntries, int BlockOffset, double *Values, int *Indices)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SumIntoMyValues</name>
      <anchorfile>classKomplex__Vector.html</anchorfile>
      <anchor>a20ccbc3ea90160781db9b5ec3cb9929c</anchor>
      <arglist>(int NumEntries, int BlockOffset, double *Values, int *Indices)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Scale</name>
      <anchorfile>classKomplex__Vector.html</anchorfile>
      <anchor>a6c864f09fb15e82fe82b18320f48e1be</anchor>
      <arglist>(double ScalarValue)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Scale</name>
      <anchorfile>classKomplex__Vector.html</anchorfile>
      <anchor>a916ef62b5107df300586f7ab412ccac6</anchor>
      <arglist>(double ScalarA, const Komplex_Vector &amp;A)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Norm1</name>
      <anchorfile>classKomplex__Vector.html</anchorfile>
      <anchor>aee6e1d15971810217760f05d3b5f027e</anchor>
      <arglist>(double &amp;Result) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Norm2</name>
      <anchorfile>classKomplex__Vector.html</anchorfile>
      <anchor>a7029aeb0790759a46d6fc6acf5a06604</anchor>
      <arglist>(double &amp;Result) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NormInf</name>
      <anchorfile>classKomplex__Vector.html</anchorfile>
      <anchor>ac515ce81b823f1a564c91f53e08d4906</anchor>
      <arglist>(double &amp;Result) const </arglist>
    </member>
    <member kind="function">
      <type>Komplex_Vector &amp;</type>
      <name>operator=</name>
      <anchorfile>classKomplex__Vector.html</anchorfile>
      <anchor>ae34ccc5c901296aeda74fe89f5f8be0c</anchor>
      <arglist>(const Komplex_Vector &amp;Source)</arglist>
    </member>
    <member kind="function">
      <type>double &amp;</type>
      <name>operator[]</name>
      <anchorfile>classKomplex__Vector.html</anchorfile>
      <anchor>a1205cad78ff27aa5f81b65bc5a0f5f43</anchor>
      <arglist>(int index)</arglist>
    </member>
    <member kind="function">
      <type>const double &amp;</type>
      <name>operator[]</name>
      <anchorfile>classKomplex__Vector.html</anchorfile>
      <anchor>af689cf6ff83a069c6dd756779d12e73e</anchor>
      <arglist>(int index) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Length</name>
      <anchorfile>classKomplex__Vector.html</anchorfile>
      <anchor>a87233aa73134d28d81274fc473426c5a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ReplaceMap</name>
      <anchorfile>classKomplex__Vector.html</anchorfile>
      <anchor>a5155a992995edf4ca6663b9c205e6eb1</anchor>
      <arglist>(const Epetra_BlockMap &amp;map)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Print</name>
      <anchorfile>classKomplex__Vector.html</anchorfile>
      <anchor>a75e76484c9fb0582f5ed66c7c6b07ffd</anchor>
      <arglist>(ostream &amp;os) const </arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Komplex_Vector</name>
      <anchorfile>classKomplex__Vector.html</anchorfile>
      <anchor>ae312e8ef9771f05b02b6ca17a58b26ac</anchor>
      <arglist>(const Epetra_BlockMap &amp;Map, bool zeroOut=true)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Komplex_Vector</name>
      <anchorfile>classKomplex__Vector.html</anchorfile>
      <anchor>a7610d6f35062abb93c4888a3cd408160</anchor>
      <arglist>(const Epetra_BlockMap &amp;Map, const Epetra_Vector &amp;br, const Epetra_Vector &amp;bi)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Komplex_Vector</name>
      <anchorfile>classKomplex__Vector.html</anchorfile>
      <anchor>a288d13b442800af458377fab0bcf6fbc</anchor>
      <arglist>(const Komplex_Vector &amp;Source)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Komplex_Vector</name>
      <anchorfile>classKomplex__Vector.html</anchorfile>
      <anchor>aebb25b0e061e183844ae110297c15573</anchor>
      <arglist>(Komplex_DataAccess CV, const Epetra_BlockMap &amp;Map, const Komplex_MultiVector &amp;Source, int Index)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~Komplex_Vector</name>
      <anchorfile>classKomplex__Vector.html</anchorfile>
      <anchor>a482c732ddc6d41509bf8dc69b5b17003</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ReplaceGlobalValues</name>
      <anchorfile>classKomplex__Vector.html</anchorfile>
      <anchor>a0c1ee7bf5f06fe7faaad1e0cd7411563</anchor>
      <arglist>(int NumEntries, double *Values, int *Indices)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ReplaceMyValues</name>
      <anchorfile>classKomplex__Vector.html</anchorfile>
      <anchor>ab252433a3ae42a8034f79ea4daf75216</anchor>
      <arglist>(int NumEntries, double *Values, int *Indices)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SumIntoGlobalValues</name>
      <anchorfile>classKomplex__Vector.html</anchorfile>
      <anchor>aded8fdb3c103122374649553b58b19d5</anchor>
      <arglist>(int NumEntries, double *Values, int *Indices)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SumIntoMyValues</name>
      <anchorfile>classKomplex__Vector.html</anchorfile>
      <anchor>a98526546833a69348de816f0493c3ae6</anchor>
      <arglist>(int NumEntries, double *Values, int *Indices)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ReplaceGlobalValues</name>
      <anchorfile>classKomplex__Vector.html</anchorfile>
      <anchor>ad2be510aaa411e471e208e7b59ef742d</anchor>
      <arglist>(int NumEntries, int BlockOffset, double *Values, int *Indices)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ReplaceMyValues</name>
      <anchorfile>classKomplex__Vector.html</anchorfile>
      <anchor>a0d5d222658a409a3b250cfa406a7ec73</anchor>
      <arglist>(int NumEntries, int BlockOffset, double *Values, int *Indices)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SumIntoGlobalValues</name>
      <anchorfile>classKomplex__Vector.html</anchorfile>
      <anchor>ac36afb26b5480a7c4688edb9d9d0db40</anchor>
      <arglist>(int NumEntries, int BlockOffset, double *Values, int *Indices)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SumIntoMyValues</name>
      <anchorfile>classKomplex__Vector.html</anchorfile>
      <anchor>a20ccbc3ea90160781db9b5ec3cb9929c</anchor>
      <arglist>(int NumEntries, int BlockOffset, double *Values, int *Indices)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Scale</name>
      <anchorfile>classKomplex__Vector.html</anchorfile>
      <anchor>a6c864f09fb15e82fe82b18320f48e1be</anchor>
      <arglist>(double ScalarValue)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Scale</name>
      <anchorfile>classKomplex__Vector.html</anchorfile>
      <anchor>a916ef62b5107df300586f7ab412ccac6</anchor>
      <arglist>(double ScalarA, const Komplex_Vector &amp;A)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Norm1</name>
      <anchorfile>classKomplex__Vector.html</anchorfile>
      <anchor>aee6e1d15971810217760f05d3b5f027e</anchor>
      <arglist>(double &amp;Result) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Norm2</name>
      <anchorfile>classKomplex__Vector.html</anchorfile>
      <anchor>a7029aeb0790759a46d6fc6acf5a06604</anchor>
      <arglist>(double &amp;Result) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NormInf</name>
      <anchorfile>classKomplex__Vector.html</anchorfile>
      <anchor>ac515ce81b823f1a564c91f53e08d4906</anchor>
      <arglist>(double &amp;Result) const </arglist>
    </member>
    <member kind="function">
      <type>Komplex_Vector &amp;</type>
      <name>operator=</name>
      <anchorfile>classKomplex__Vector.html</anchorfile>
      <anchor>a9bef6e0b06ddcf23d39f59825b3a716a</anchor>
      <arglist>(const Komplex_Vector &amp;Source)</arglist>
    </member>
    <member kind="function">
      <type>double &amp;</type>
      <name>operator[]</name>
      <anchorfile>classKomplex__Vector.html</anchorfile>
      <anchor>a4201370716520923d400b7f5d4dbff6f</anchor>
      <arglist>(int index)</arglist>
    </member>
    <member kind="function">
      <type>const double &amp;</type>
      <name>operator[]</name>
      <anchorfile>classKomplex__Vector.html</anchorfile>
      <anchor>a1a3e4af7a85cb0e1cfc76b1655d16f93</anchor>
      <arglist>(int index) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Length</name>
      <anchorfile>classKomplex__Vector.html</anchorfile>
      <anchor>a87233aa73134d28d81274fc473426c5a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ReplaceMap</name>
      <anchorfile>classKomplex__Vector.html</anchorfile>
      <anchor>a5155a992995edf4ca6663b9c205e6eb1</anchor>
      <arglist>(const Epetra_BlockMap &amp;map)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Print</name>
      <anchorfile>classKomplex__Vector.html</anchorfile>
      <anchor>a75e76484c9fb0582f5ed66c7c6b07ffd</anchor>
      <arglist>(ostream &amp;os) const </arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Komplex_Vector</name>
      <anchorfile>classKomplex__Vector.html</anchorfile>
      <anchor>ae312e8ef9771f05b02b6ca17a58b26ac</anchor>
      <arglist>(const Epetra_BlockMap &amp;Map, bool zeroOut=true)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Komplex_Vector</name>
      <anchorfile>classKomplex__Vector.html</anchorfile>
      <anchor>a7610d6f35062abb93c4888a3cd408160</anchor>
      <arglist>(const Epetra_BlockMap &amp;Map, const Epetra_Vector &amp;br, const Epetra_Vector &amp;bi)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Komplex_Vector</name>
      <anchorfile>classKomplex__Vector.html</anchorfile>
      <anchor>a288d13b442800af458377fab0bcf6fbc</anchor>
      <arglist>(const Komplex_Vector &amp;Source)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Komplex_Vector</name>
      <anchorfile>classKomplex__Vector.html</anchorfile>
      <anchor>a2a9cf86b700f35e26bfef79978723daa</anchor>
      <arglist>(Epetra_DataAccess CV, const Epetra_BlockMap &amp;Map, const Komplex_MultiVector &amp;Source, int Index)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~Komplex_Vector</name>
      <anchorfile>classKomplex__Vector.html</anchorfile>
      <anchor>a8a30c206e73c7be642c1bdb01751b110</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ReplaceGlobalValues</name>
      <anchorfile>classKomplex__Vector.html</anchorfile>
      <anchor>a0c1ee7bf5f06fe7faaad1e0cd7411563</anchor>
      <arglist>(int NumEntries, double *Values, int *Indices)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ReplaceMyValues</name>
      <anchorfile>classKomplex__Vector.html</anchorfile>
      <anchor>ab252433a3ae42a8034f79ea4daf75216</anchor>
      <arglist>(int NumEntries, double *Values, int *Indices)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SumIntoGlobalValues</name>
      <anchorfile>classKomplex__Vector.html</anchorfile>
      <anchor>aded8fdb3c103122374649553b58b19d5</anchor>
      <arglist>(int NumEntries, double *Values, int *Indices)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SumIntoMyValues</name>
      <anchorfile>classKomplex__Vector.html</anchorfile>
      <anchor>a98526546833a69348de816f0493c3ae6</anchor>
      <arglist>(int NumEntries, double *Values, int *Indices)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ReplaceGlobalValues</name>
      <anchorfile>classKomplex__Vector.html</anchorfile>
      <anchor>ad2be510aaa411e471e208e7b59ef742d</anchor>
      <arglist>(int NumEntries, int BlockOffset, double *Values, int *Indices)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ReplaceMyValues</name>
      <anchorfile>classKomplex__Vector.html</anchorfile>
      <anchor>a0d5d222658a409a3b250cfa406a7ec73</anchor>
      <arglist>(int NumEntries, int BlockOffset, double *Values, int *Indices)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SumIntoGlobalValues</name>
      <anchorfile>classKomplex__Vector.html</anchorfile>
      <anchor>ac36afb26b5480a7c4688edb9d9d0db40</anchor>
      <arglist>(int NumEntries, int BlockOffset, double *Values, int *Indices)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SumIntoMyValues</name>
      <anchorfile>classKomplex__Vector.html</anchorfile>
      <anchor>a20ccbc3ea90160781db9b5ec3cb9929c</anchor>
      <arglist>(int NumEntries, int BlockOffset, double *Values, int *Indices)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Scale</name>
      <anchorfile>classKomplex__Vector.html</anchorfile>
      <anchor>a6c864f09fb15e82fe82b18320f48e1be</anchor>
      <arglist>(double ScalarValue)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Scale</name>
      <anchorfile>classKomplex__Vector.html</anchorfile>
      <anchor>a916ef62b5107df300586f7ab412ccac6</anchor>
      <arglist>(double ScalarA, const Komplex_Vector &amp;A)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Norm1</name>
      <anchorfile>classKomplex__Vector.html</anchorfile>
      <anchor>aee6e1d15971810217760f05d3b5f027e</anchor>
      <arglist>(double &amp;Result) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Norm2</name>
      <anchorfile>classKomplex__Vector.html</anchorfile>
      <anchor>a7029aeb0790759a46d6fc6acf5a06604</anchor>
      <arglist>(double &amp;Result) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NormInf</name>
      <anchorfile>classKomplex__Vector.html</anchorfile>
      <anchor>ac515ce81b823f1a564c91f53e08d4906</anchor>
      <arglist>(double &amp;Result) const </arglist>
    </member>
    <member kind="function">
      <type>Komplex_Vector &amp;</type>
      <name>operator=</name>
      <anchorfile>classKomplex__Vector.html</anchorfile>
      <anchor>ae34ccc5c901296aeda74fe89f5f8be0c</anchor>
      <arglist>(const Komplex_Vector &amp;Source)</arglist>
    </member>
    <member kind="function">
      <type>double &amp;</type>
      <name>operator[]</name>
      <anchorfile>classKomplex__Vector.html</anchorfile>
      <anchor>a1205cad78ff27aa5f81b65bc5a0f5f43</anchor>
      <arglist>(int index)</arglist>
    </member>
    <member kind="function">
      <type>const double &amp;</type>
      <name>operator[]</name>
      <anchorfile>classKomplex__Vector.html</anchorfile>
      <anchor>af689cf6ff83a069c6dd756779d12e73e</anchor>
      <arglist>(int index) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Length</name>
      <anchorfile>classKomplex__Vector.html</anchorfile>
      <anchor>a87233aa73134d28d81274fc473426c5a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ReplaceMap</name>
      <anchorfile>classKomplex__Vector.html</anchorfile>
      <anchor>a5155a992995edf4ca6663b9c205e6eb1</anchor>
      <arglist>(const Epetra_BlockMap &amp;map)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Print</name>
      <anchorfile>classKomplex__Vector.html</anchorfile>
      <anchor>a75e76484c9fb0582f5ed66c7c6b07ffd</anchor>
      <arglist>(ostream &amp;os) const </arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Komplex_Vector</name>
      <anchorfile>classKomplex__Vector.html</anchorfile>
      <anchor>ae312e8ef9771f05b02b6ca17a58b26ac</anchor>
      <arglist>(const Epetra_BlockMap &amp;Map, bool zeroOut=true)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Komplex_Vector</name>
      <anchorfile>classKomplex__Vector.html</anchorfile>
      <anchor>a7610d6f35062abb93c4888a3cd408160</anchor>
      <arglist>(const Epetra_BlockMap &amp;Map, const Epetra_Vector &amp;br, const Epetra_Vector &amp;bi)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Komplex_Vector</name>
      <anchorfile>classKomplex__Vector.html</anchorfile>
      <anchor>a288d13b442800af458377fab0bcf6fbc</anchor>
      <arglist>(const Komplex_Vector &amp;Source)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Komplex_Vector</name>
      <anchorfile>classKomplex__Vector.html</anchorfile>
      <anchor>aebb25b0e061e183844ae110297c15573</anchor>
      <arglist>(Komplex_DataAccess CV, const Epetra_BlockMap &amp;Map, const Komplex_MultiVector &amp;Source, int Index)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~Komplex_Vector</name>
      <anchorfile>classKomplex__Vector.html</anchorfile>
      <anchor>a482c732ddc6d41509bf8dc69b5b17003</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ReplaceGlobalValues</name>
      <anchorfile>classKomplex__Vector.html</anchorfile>
      <anchor>a0c1ee7bf5f06fe7faaad1e0cd7411563</anchor>
      <arglist>(int NumEntries, double *Values, int *Indices)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ReplaceMyValues</name>
      <anchorfile>classKomplex__Vector.html</anchorfile>
      <anchor>ab252433a3ae42a8034f79ea4daf75216</anchor>
      <arglist>(int NumEntries, double *Values, int *Indices)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SumIntoGlobalValues</name>
      <anchorfile>classKomplex__Vector.html</anchorfile>
      <anchor>aded8fdb3c103122374649553b58b19d5</anchor>
      <arglist>(int NumEntries, double *Values, int *Indices)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SumIntoMyValues</name>
      <anchorfile>classKomplex__Vector.html</anchorfile>
      <anchor>a98526546833a69348de816f0493c3ae6</anchor>
      <arglist>(int NumEntries, double *Values, int *Indices)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ReplaceGlobalValues</name>
      <anchorfile>classKomplex__Vector.html</anchorfile>
      <anchor>ad2be510aaa411e471e208e7b59ef742d</anchor>
      <arglist>(int NumEntries, int BlockOffset, double *Values, int *Indices)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ReplaceMyValues</name>
      <anchorfile>classKomplex__Vector.html</anchorfile>
      <anchor>a0d5d222658a409a3b250cfa406a7ec73</anchor>
      <arglist>(int NumEntries, int BlockOffset, double *Values, int *Indices)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SumIntoGlobalValues</name>
      <anchorfile>classKomplex__Vector.html</anchorfile>
      <anchor>ac36afb26b5480a7c4688edb9d9d0db40</anchor>
      <arglist>(int NumEntries, int BlockOffset, double *Values, int *Indices)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SumIntoMyValues</name>
      <anchorfile>classKomplex__Vector.html</anchorfile>
      <anchor>a20ccbc3ea90160781db9b5ec3cb9929c</anchor>
      <arglist>(int NumEntries, int BlockOffset, double *Values, int *Indices)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Scale</name>
      <anchorfile>classKomplex__Vector.html</anchorfile>
      <anchor>a6c864f09fb15e82fe82b18320f48e1be</anchor>
      <arglist>(double ScalarValue)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Scale</name>
      <anchorfile>classKomplex__Vector.html</anchorfile>
      <anchor>a916ef62b5107df300586f7ab412ccac6</anchor>
      <arglist>(double ScalarA, const Komplex_Vector &amp;A)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Norm1</name>
      <anchorfile>classKomplex__Vector.html</anchorfile>
      <anchor>aee6e1d15971810217760f05d3b5f027e</anchor>
      <arglist>(double &amp;Result) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Norm2</name>
      <anchorfile>classKomplex__Vector.html</anchorfile>
      <anchor>a7029aeb0790759a46d6fc6acf5a06604</anchor>
      <arglist>(double &amp;Result) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NormInf</name>
      <anchorfile>classKomplex__Vector.html</anchorfile>
      <anchor>ac515ce81b823f1a564c91f53e08d4906</anchor>
      <arglist>(double &amp;Result) const </arglist>
    </member>
    <member kind="function">
      <type>Komplex_Vector &amp;</type>
      <name>operator=</name>
      <anchorfile>classKomplex__Vector.html</anchorfile>
      <anchor>a9bef6e0b06ddcf23d39f59825b3a716a</anchor>
      <arglist>(const Komplex_Vector &amp;Source)</arglist>
    </member>
    <member kind="function">
      <type>double &amp;</type>
      <name>operator[]</name>
      <anchorfile>classKomplex__Vector.html</anchorfile>
      <anchor>a4201370716520923d400b7f5d4dbff6f</anchor>
      <arglist>(int index)</arglist>
    </member>
    <member kind="function">
      <type>const double &amp;</type>
      <name>operator[]</name>
      <anchorfile>classKomplex__Vector.html</anchorfile>
      <anchor>a1a3e4af7a85cb0e1cfc76b1655d16f93</anchor>
      <arglist>(int index) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Length</name>
      <anchorfile>classKomplex__Vector.html</anchorfile>
      <anchor>a87233aa73134d28d81274fc473426c5a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ReplaceMap</name>
      <anchorfile>classKomplex__Vector.html</anchorfile>
      <anchor>a5155a992995edf4ca6663b9c205e6eb1</anchor>
      <arglist>(const Epetra_BlockMap &amp;map)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Print</name>
      <anchorfile>classKomplex__Vector.html</anchorfile>
      <anchor>a75e76484c9fb0582f5ed66c7c6b07ffd</anchor>
      <arglist>(ostream &amp;os) const </arglist>
    </member>
  </compound>
  <compound kind="page">
    <name>index</name>
    <title>The Komplex Solver Package for solving Complex Linear Systems</title>
    <filename>index</filename>
    <docanchor file="index" title="Introduction">intro</docanchor>
    <docanchor file="index" title="Installation (Aztec 2.1-compatible only)">install</docanchor>
    <docanchor file="index" title="Overview of Using Komplex (Aztec 2.1-compatible version only)">startup</docanchor>
    <docanchor file="index" title="Possible Formulations">formulations</docanchor>
    <docanchor file="index" title="Step-by-step use of Komplex">steps</docanchor>
    <docanchor file="index" title="Calling Komplex to Solve Multiple Related Systems">multicall</docanchor>
    <docanchor file="index" title="Example Codes">example</docanchor>
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
