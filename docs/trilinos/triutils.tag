<?xml version='1.0' encoding='UTF-8' standalone='yes' ?>
<tagfile>
  <compound kind="file">
    <name>CMakeLists.txt</name>
    <path>/Users/sscoll/dist/trilinos/packages/triutils/src/</path>
    <filename>CMakeLists_8txt</filename>
    <member kind="function">
      <type></type>
      <name>SET</name>
      <anchorfile>CMakeLists_8txt.html</anchorfile>
      <anchor>a460b562451498de6db48546452160c47</anchor>
      <arglist>(HEADERS ${HEADERS}${CMAKE_CURRENT_BINARY_DIR}/${PACKAGE_NAME}_config.h) SET(HEADERS $</arglist>
    </member>
    <member kind="function">
      <type>Trilinos_Util h Trilinos_Util_ReadMatrixMarket2Epetra h Trilinos_Util_CountMatrixMarket h Trilinos_Util_CountTriples h Trilinos_Util_CrsMatrixGallery h Trilinos_Util_CommandLineParser h</type>
      <name>SET</name>
      <anchorfile>CMakeLists_8txt.html</anchorfile>
      <anchor>a27071b3963ab0ebe1a79476b125737bd</anchor>
      <arglist>(SOURCES ${SOURCES}Trilinos_Util_duscr_vbr.cpp Trilinos_Util_dusds_vbr.cpp Trilinos_Util_distrib_vbr_matrix.cpp Trilinos_Util_read_hb.cpp Trilinos_Util_svbrres.cpp Trilinos_Util_dusmm.cpp Trilinos_Util_scscmv.cpp Trilinos_Util_read_vec.cpp Trilinos_Util_write_vec.cpp Trilinos_Util_create_vbr.cpp Trilinos_Util_msr2vbr.cpp Trilinos_Util_scscres.cpp Trilinos_Util_distrib_msr_matrix.cpp Trilinos_Util_read_coo.cpp Trilinos_Util_smsrres.cpp Trilinos_Util_csrcsc.cpp Trilinos_Util_csrmsr.cpp Trilinos_Util_ssrcsr.cpp Trilinos_Util_coocsr.cpp Trilinos_Util_ReadMatrixMarket2Epetra.cpp Trilinos_Util_ReadTriples2Epetra.cpp Trilinos_Util_CountMatrixMarket.cpp Trilinos_Util_CountTriples.cpp Trilinos_Util_ReadHb2Epetra.cpp Trilinos_Util_ReadHpc2Epetra.cpp Trilinos_Util_ReadHb2EpetraVbr.cpp Trilinos_Util_GenerateCrsProblem.cpp Trilinos_Util_GenerateVbrProblem.cpp Trilinos_Util_CommandLineParser.cpp Trilinos_Util_CrsMatrixGallery.cpp) SET(HEADERS $</arglist>
    </member>
    <member kind="function">
      <type>Trilinos_Util_iohb h Trilinos_Util_Version h</type>
      <name>SET</name>
      <anchorfile>CMakeLists_8txt.html</anchorfile>
      <anchor>a11c2f8e869dd354268959783eed236ef</anchor>
      <arglist>(SOURCES ${SOURCES}Trilinos_Util_iohb.cpp) TRIBITS_ADD_LIBRARY(triutils HEADERS $</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Trilinos_Util.h</name>
    <path>/Users/sscoll/dist/trilinos/packages/triutils/src/</path>
    <filename>Trilinos__Util_8h</filename>
    <includes id="Trilinos__Util__ReadMatrixMarket2Epetra_8h" name="Trilinos_Util_ReadMatrixMarket2Epetra.h" local="yes" imported="no">Trilinos_Util_ReadMatrixMarket2Epetra.h</includes>
    <class kind="struct">SPBLASMAT_STRUCT</class>
    <member kind="define">
      <type>#define</type>
      <name>Trilinos_Util_max</name>
      <anchorfile>Trilinos__Util_8h.html</anchorfile>
      <anchor>aaf8eb8857ff4bef74f32078e876914d5</anchor>
      <arglist>(x, y)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>Trilinos_Util_min</name>
      <anchorfile>Trilinos__Util_8h.html</anchorfile>
      <anchor>a9fd67a1c92d5118bb7ca5c8fb36d62b5</anchor>
      <arglist>(x, y)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>MAXNRHS</name>
      <anchorfile>Trilinos__Util_8h.html</anchorfile>
      <anchor>a6d30cb9489ddffb81d231b9c0d1785e5</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct SPBLASMAT_STRUCT</type>
      <name>SPBLASMAT</name>
      <anchorfile>Trilinos__Util_8h.html</anchorfile>
      <anchor>a858e76b1768adc9f0b7b36e686d353e7</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Trilinos_Util_read_hb</name>
      <anchorfile>Trilinos__Util_8h.html</anchorfile>
      <anchor>aac89170bd9da716f6cbfe90ca1c72fc6</anchor>
      <arglist>(const char *data_file, int MyPID, int *N_global, int *n_nonzeros, double **val, int **bindx, double **x, double **b, double **xexact)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Trilinos_Util_read_hb</name>
      <anchorfile>Trilinos__Util_8h.html</anchorfile>
      <anchor>ae07ea7324c18856d0cbed89e6eabddca</anchor>
      <arglist>(const char *data_file, int MyPID, int *N_global, int *n_nonzeros, double **val, int **bindx)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Trilinos_Util_read_coo</name>
      <anchorfile>Trilinos__Util_8h.html</anchorfile>
      <anchor>ad8a9cfbb5cf2f92d7405e473b059c749</anchor>
      <arglist>(const char *data_file, int MyPID, int *N_global, int *n_nonzeros, double **val, int **bindx, double **x, double **b, double **xexact)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Trilinos_Util_ReadHb2Epetra_internal</name>
      <anchorfile>Trilinos__Util_8h.html</anchorfile>
      <anchor>a078e4846a4d74e6735b1e37adb20189a</anchor>
      <arglist>(const char *data_file, const Epetra_Comm &amp;comm, Epetra_Map *&amp;map, Epetra_CrsMatrix *&amp;A, Epetra_Vector *&amp;x, Epetra_Vector *&amp;b, Epetra_Vector *&amp;xexact, bool FakeLongLong)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Trilinos_Util_ReadHb2Epetra</name>
      <anchorfile>Trilinos__Util_8h.html</anchorfile>
      <anchor>ade43470ef7d141fc52ba08f39c9f60b8</anchor>
      <arglist>(const char *data_file, const Epetra_Comm &amp;comm, Epetra_Map *&amp;map, Epetra_CrsMatrix *&amp;A, Epetra_Vector *&amp;x, Epetra_Vector *&amp;b, Epetra_Vector *&amp;xexact)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Trilinos_Util_ReadHb2Epetra64</name>
      <anchorfile>Trilinos__Util_8h.html</anchorfile>
      <anchor>a3f6023f04fa8200248ad6da2194b5643</anchor>
      <arglist>(const char *data_file, const Epetra_Comm &amp;comm, Epetra_Map *&amp;map, Epetra_CrsMatrix *&amp;A, Epetra_Vector *&amp;x, Epetra_Vector *&amp;b, Epetra_Vector *&amp;xexact)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Trilinos_Util_ReadHpc2Epetra</name>
      <anchorfile>Trilinos__Util_8h.html</anchorfile>
      <anchor>a220896792d63ceec784b4c2d4a436012</anchor>
      <arglist>(const char *data_file, const Epetra_Comm &amp;comm, Epetra_Map *&amp;map, Epetra_CrsMatrix *&amp;A, Epetra_Vector *&amp;x, Epetra_Vector *&amp;b, Epetra_Vector *&amp;xexact)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Trilinos_Util_ReadHpc2Epetra64</name>
      <anchorfile>Trilinos__Util_8h.html</anchorfile>
      <anchor>a886661804e2b5c0c35f6cff51786826b</anchor>
      <arglist>(const char *data_file, const Epetra_Comm &amp;comm, Epetra_Map *&amp;map, Epetra_CrsMatrix *&amp;A, Epetra_Vector *&amp;x, Epetra_Vector *&amp;b, Epetra_Vector *&amp;xexact)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Trilinos_Util_ReadHb2EpetraVbr</name>
      <anchorfile>Trilinos__Util_8h.html</anchorfile>
      <anchor>ab33ffd3c8749ed492f66cf5b1b994e36</anchor>
      <arglist>(const char *data_file, const char *partitioning, const Epetra_Comm &amp;comm, Epetra_BlockMap *&amp;map, Epetra_VbrMatrix *&amp;A, Epetra_Vector *&amp;x, Epetra_Vector *&amp;b, Epetra_Vector *&amp;xexact)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Trilinos_Util_distrib_msr_matrix</name>
      <anchorfile>Trilinos__Util_8h.html</anchorfile>
      <anchor>a88ef41ef9b79777da0b6391228032829</anchor>
      <arglist>(const Epetra_Comm &amp;Comm, int *N_global, int *n_nonzeros, int *N_update, int **update, double **val, int **bindx, double **x, double **b, double **xexact)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Trilinos_Util_distrib_msr_matrix</name>
      <anchorfile>Trilinos__Util_8h.html</anchorfile>
      <anchor>a4406c9d4ffff89bf696a3cfdf2b70868</anchor>
      <arglist>(const Epetra_Comm &amp;Comm, int *N_global, int *n_nonzeros, int *N_update, int **update, double **val, int **bindx)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Trilinos_Util_distrib_vbr_matrix</name>
      <anchorfile>Trilinos__Util_8h.html</anchorfile>
      <anchor>a7a7e44685daa573d92cd473d604b9481</anchor>
      <arglist>(const Epetra_Comm &amp;Comm, int *N_global, int *N_blk_global, int *n_nonzeros, int *n_blk_nonzeros, int *N_update, int **update, double **val, int **indx, int **rpntr, int **cpntr, int **bpntr, int **bindx, double **x, double **b, double **xexact)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Trilinos_Util_create_vbr</name>
      <anchorfile>Trilinos__Util_8h.html</anchorfile>
      <anchor>abb19e28e3d33a4fd84ad12f047c4dccc</anchor>
      <arglist>(const Epetra_Comm &amp;Comm, const char *part_file, int *N_global, int *N_blk_global, int *n_nonzeros, int *n_blk_nonzeros, int *N_update, int **update, int *bindx_msr, double *val_msr, double **val, int **indx, int **rpntr, int **cpntr, int **bpntr, int **bindx)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>Trilinos_Util_smsrres</name>
      <anchorfile>Trilinos__Util_8h.html</anchorfile>
      <anchor>a624762f02345f0e68d37787652897764</anchor>
      <arglist>(int m, int n, double *val, int *indx, double *xlocal, double *x, double *b)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>Trilinos_Util_scscres</name>
      <anchorfile>Trilinos__Util_8h.html</anchorfile>
      <anchor>a95949db41f6721a507db3e8563d5d7bc</anchor>
      <arglist>(int isym, int m, int n, double *val, int *indx, int *pntr, double *x, double *b)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Trilinos_Util_scscmv</name>
      <anchorfile>Trilinos__Util_8h.html</anchorfile>
      <anchor>acac9d76342dae3727184c90b9a4fb82b</anchor>
      <arglist>(int isym, int m, int n, double *val, int *indx, int *pntr, double *x, double *b)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>Trilinos_Util_svbrres</name>
      <anchorfile>Trilinos__Util_8h.html</anchorfile>
      <anchor>a397486fc0dd62929b6af2ea464f8519b</anchor>
      <arglist>(int m, int n, int m_blk, double *val, int *indx, int *bindx, int *rpntr, int *cpntr, int *bpntrb, int *bpntre, double *x, double *b)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Trilinos_Util_msr2vbr</name>
      <anchorfile>Trilinos__Util_8h.html</anchorfile>
      <anchor>a92fbb05f81140f28f11be040c105f485</anchor>
      <arglist>(double val[], int indx[], int rnptr[], int cnptr[], int bnptr[], int bindx[], int msr_bindx[], double msr_val[], int total_blk_rows, int total_blk_cols, int blk_space, int nz_space, int blk_type)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Trilinos_Util_find_block_col</name>
      <anchorfile>Trilinos__Util_8h.html</anchorfile>
      <anchor>a6c619c72b29527fbfdd576942f69fa93</anchor>
      <arglist>(int cnptr[], int column, int max_blocks, int blk_size)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Trilinos_Util_find_block_in_row</name>
      <anchorfile>Trilinos__Util_8h.html</anchorfile>
      <anchor>aafd6bdc281bc4da2d506a9934622f011</anchor>
      <arglist>(int bindx[], int bnptr[], int blk_row, int blk_col, int indx[], int no_elements, double val[], int blk_space, int nz_space)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Trilinos_Util_add_new_ele</name>
      <anchorfile>Trilinos__Util_8h.html</anchorfile>
      <anchor>aa55e25501503fd6ca3278368099b5e84</anchor>
      <arglist>(int cnptr[], int col, int blk_row, int bindx[], int bnptr[], int indx[], double val[], int row, double new_ele, int maxcols, int blk_space, int nz_space, int blk_type)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Trilinos_Util_find_closest_not_larger</name>
      <anchorfile>Trilinos__Util_8h.html</anchorfile>
      <anchor>a4816d9a8238ba79169dcfd4032ad2b08</anchor>
      <arglist>(int key, int list[], int length)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Trilinos_Util_convert_values_to_ptrs</name>
      <anchorfile>Trilinos__Util_8h.html</anchorfile>
      <anchor>ae57c427d71925aaeebed1edda2493c03</anchor>
      <arglist>(int array[], int length, int start)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Trilinos_Util_csrcsc</name>
      <anchorfile>Trilinos__Util_8h.html</anchorfile>
      <anchor>afd2ee233bd1fa2ad5350bcaf7c8e09e8</anchor>
      <arglist>(int n, int n2, int job, int ipos, double *a, int *ja, int *ia, double *ao, int *jao, int *iao)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Trilinos_Util_csrmsr</name>
      <anchorfile>Trilinos__Util_8h.html</anchorfile>
      <anchor>a30273b2f224195d6b85bb828d7fc4698</anchor>
      <arglist>(int n, double *a, int *ja, int *ia, double *ao, int *jao, double *wk, int *iwk)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Trilinos_Util_ssrcsr</name>
      <anchorfile>Trilinos__Util_8h.html</anchorfile>
      <anchor>a16bdbd7893e44d70cb98c8415ec70d72</anchor>
      <arglist>(int job, int value2, int nrow, double *a, int *ja, int *ia, int nzmax, double *ao, int *jao, int *iao, int *indu, int *iwk)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Trilinos_Util_coocsr</name>
      <anchorfile>Trilinos__Util_8h.html</anchorfile>
      <anchor>aa509fdaeb5cac1a0de3e84d7e20d0048</anchor>
      <arglist>(int nrow, int nnz, double *a, int *ir, int *jc, double *ao, int *jao, int *iao)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Trilinos_Util_duscr_vbr</name>
      <anchorfile>Trilinos__Util_8h.html</anchorfile>
      <anchor>a45509056f552bfe35e6a2deba68d5aac</anchor>
      <arglist>(int n, double *val, int *indx, int *bindx, int *rpntr, int *cpntr, int *bpntrb, int *bpntre, SPBLASMAT *A)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Trilinos_Util_dusmm</name>
      <anchorfile>Trilinos__Util_8h.html</anchorfile>
      <anchor>a75a68e53cdc748b595ddbe9eb0762ed4</anchor>
      <arglist>(int m, int nrhs, int k, double alpha, SPBLASMAT *A, double *x, int xstride, double beta, double *b, int bstride)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Trilinos_Util_dusds_vbr</name>
      <anchorfile>Trilinos__Util_8h.html</anchorfile>
      <anchor>a4c306b902c7026cc7f3b2ea8cd3526fe</anchor>
      <arglist>(SPBLASMAT *A)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Trilinos_Util_GenerateCrsProblem</name>
      <anchorfile>Trilinos__Util_8h.html</anchorfile>
      <anchor>a30ae9a7e890fbb1146316b56db01a394</anchor>
      <arglist>(int nx, int ny, int npoints, int *xoff, int *yoff, const Epetra_Comm &amp;comm, Epetra_Map *&amp;map, Epetra_CrsMatrix *&amp;A, Epetra_Vector *&amp;x, Epetra_Vector *&amp;b, Epetra_Vector *&amp;xexact, int indexBase=0)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Trilinos_Util_GenerateCrsProblem</name>
      <anchorfile>Trilinos__Util_8h.html</anchorfile>
      <anchor>a3ad8b37c975ddb237bf5e7284a59fa85</anchor>
      <arglist>(int nx, int ny, int npoints, int *xoff, int *yoff, int nrhs, const Epetra_Comm &amp;comm, Epetra_Map *&amp;map, Epetra_CrsMatrix *&amp;A, Epetra_MultiVector *&amp;x, Epetra_MultiVector *&amp;b, Epetra_MultiVector *&amp;xexact, int indexBase=0)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Trilinos_Util_GenerateCrsProblem64</name>
      <anchorfile>Trilinos__Util_8h.html</anchorfile>
      <anchor>a326c08a42aa017e72aeb0da99e630d97</anchor>
      <arglist>(int nx, int ny, int npoints, int *xoff, int *yoff, const Epetra_Comm &amp;comm, Epetra_Map *&amp;map, Epetra_CrsMatrix *&amp;A, Epetra_Vector *&amp;x, Epetra_Vector *&amp;b, Epetra_Vector *&amp;xexact, long long indexBase=0)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Trilinos_Util_GenerateCrsProblem64</name>
      <anchorfile>Trilinos__Util_8h.html</anchorfile>
      <anchor>a43a13b67aa0f40a1763143cdc45ce90c</anchor>
      <arglist>(int nx, int ny, int npoints, int *xoff, int *yoff, int nrhs, const Epetra_Comm &amp;comm, Epetra_Map *&amp;map, Epetra_CrsMatrix *&amp;A, Epetra_MultiVector *&amp;x, Epetra_MultiVector *&amp;b, Epetra_MultiVector *&amp;xexact, long long indexBase=0)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Trilinos_Util_GenerateVbrProblem</name>
      <anchorfile>Trilinos__Util_8h.html</anchorfile>
      <anchor>a98dcb641ece5b682849305903cddaadf</anchor>
      <arglist>(int nx, int ny, int npoints, int *xoff, int *yoff, int nsizes, int *sizes, const Epetra_Comm &amp;comm, Epetra_BlockMap *&amp;map, Epetra_VbrMatrix *&amp;A, Epetra_Vector *&amp;x, Epetra_Vector *&amp;b, Epetra_Vector *&amp;xexact)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Trilinos_Util_GenerateVbrProblem</name>
      <anchorfile>Trilinos__Util_8h.html</anchorfile>
      <anchor>a683e1ea1a40638d9f7b79fde474f189d</anchor>
      <arglist>(int nx, int ny, int npoints, int *xoff, int *yoff, int nsizes, int *sizes, int nrhs, const Epetra_Comm &amp;comm, Epetra_BlockMap *&amp;map, Epetra_VbrMatrix *&amp;A, Epetra_MultiVector *&amp;x, Epetra_MultiVector *&amp;b, Epetra_MultiVector *&amp;xexact)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Trilinos_Util_ReadTriples2Epetra</name>
      <anchorfile>Trilinos__Util_8h.html</anchorfile>
      <anchor>a41c9b00279c7713964e962a624fbd0be</anchor>
      <arglist>(const char *data_file, bool symmetric, const Epetra_Comm &amp;comm, Epetra_Map *&amp;map, Epetra_CrsMatrix *&amp;A, Epetra_Vector *&amp;x, Epetra_Vector *&amp;b, Epetra_Vector *&amp;xexact, bool NonUniformMap=false, bool TimDavisHeader=false, bool ZeroBased=false)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Trilinos_Util_ReadTriples2Epetra64</name>
      <anchorfile>Trilinos__Util_8h.html</anchorfile>
      <anchor>a8602ba1dec9d829bde1f50b5c1be22b1</anchor>
      <arglist>(const char *data_file, bool symmetric, const Epetra_Comm &amp;comm, Epetra_Map *&amp;map, Epetra_CrsMatrix *&amp;A, Epetra_Vector *&amp;x, Epetra_Vector *&amp;b, Epetra_Vector *&amp;xexact, bool NonUniformMap=false, bool TimDavisHeader=false, bool ZeroBased=false)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Trilinos_Util_write_vec</name>
      <anchorfile>Trilinos__Util_8h.html</anchorfile>
      <anchor>a299d431333fb07242a88b745b2b3f541</anchor>
      <arglist>(const char *filename, int n_equations, double *x)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Trilinos_Util_read_vec</name>
      <anchorfile>Trilinos__Util_8h.html</anchorfile>
      <anchor>a65fd8adcd2d88acb9077d3eaf89376f6</anchor>
      <arglist>(const char *filename, int n_equations, double *x)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Trilinos_Util_CommandLineParser.cpp</name>
    <path>/Users/sscoll/dist/trilinos/packages/triutils/src/</path>
    <filename>Trilinos__Util__CommandLineParser_8cpp</filename>
    <includes id="Trilinos__Util_8h" name="Trilinos_Util.h" local="yes" imported="no">Trilinos_Util.h</includes>
    <includes id="Trilinos__Util__CommandLineParser_8h" name="Trilinos_Util_CommandLineParser.h" local="yes" imported="no">Trilinos_Util_CommandLineParser.h</includes>
    <member kind="function">
      <type>ostream &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>Trilinos__Util__CommandLineParser_8cpp.html</anchorfile>
      <anchor>a0dafa8ec3ff8e270f4e8ba439705ba35</anchor>
      <arglist>(ostream &amp;os, const Trilinos_Util_Map &amp;S)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Trilinos_Util_CommandLineParser.h</name>
    <path>/Users/sscoll/dist/trilinos/packages/triutils/src/</path>
    <filename>Trilinos__Util__CommandLineParser_8h</filename>
    <class kind="class">Trilinos_Util_Map</class>
    <class kind="class">Trilinos_Util::CommandLineParser</class>
    <class kind="class">Trilinos_Util::InputFileReader</class>
    <namespace>Trilinos_Util</namespace>
  </compound>
  <compound kind="file">
    <name>Trilinos_Util_coocsr.cpp</name>
    <path>/Users/sscoll/dist/trilinos/packages/triutils/src/</path>
    <filename>Trilinos__Util__coocsr_8cpp</filename>
    <includes id="Trilinos__Util_8h" name="Trilinos_Util.h" local="yes" imported="no">Trilinos_Util.h</includes>
    <member kind="function">
      <type>int</type>
      <name>Trilinos_Util_coocsr</name>
      <anchorfile>Trilinos__Util__coocsr_8cpp.html</anchorfile>
      <anchor>aa509fdaeb5cac1a0de3e84d7e20d0048</anchor>
      <arglist>(int nrow, int nnz, double *a, int *ir, int *jc, double *ao, int *jao, int *iao)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Trilinos_Util_CountMatrixMarket.cpp</name>
    <path>/Users/sscoll/dist/trilinos/packages/triutils/src/</path>
    <filename>Trilinos__Util__CountMatrixMarket_8cpp</filename>
    <member kind="function">
      <type>void</type>
      <name>TTrilinos_Util_CountMatrixMarket</name>
      <anchorfile>Trilinos__Util__CountMatrixMarket_8cpp.html</anchorfile>
      <anchor>a103f934bce7737a7b664c0fb7729f1ca</anchor>
      <arglist>(const char *data_file, std::vector&lt; int &gt; &amp;non_zeros, int_type &amp;N_rows, int_type &amp;nnz, const Epetra_Comm &amp;comm)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Trilinos_Util_CountMatrixMarket</name>
      <anchorfile>Trilinos__Util__CountMatrixMarket_8cpp.html</anchorfile>
      <anchor>a725f022f166a647ae054f2c942e35922</anchor>
      <arglist>(const char *data_file, std::vector&lt; int &gt; &amp;non_zeros, int &amp;N_rows, int &amp;nnz, const Epetra_Comm &amp;comm)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Trilinos_Util_CountMatrixMarket</name>
      <anchorfile>Trilinos__Util__CountMatrixMarket_8cpp.html</anchorfile>
      <anchor>a00c16fec9947016a2ef7c8312a474004</anchor>
      <arglist>(const char *data_file, std::vector&lt; int &gt; &amp;non_zeros, long long &amp;N_rows, long long &amp;nnz, const Epetra_Comm &amp;comm)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Trilinos_Util_CountMatrixMarket.h</name>
    <path>/Users/sscoll/dist/trilinos/packages/triutils/src/</path>
    <filename>Trilinos__Util__CountMatrixMarket_8h</filename>
    <member kind="function">
      <type>void</type>
      <name>Trilinos_Util_CountMatrixMarket</name>
      <anchorfile>Trilinos__Util__CountMatrixMarket_8h.html</anchorfile>
      <anchor>a725f022f166a647ae054f2c942e35922</anchor>
      <arglist>(const char *data_file, std::vector&lt; int &gt; &amp;non_zeros, int &amp;N_rows, int &amp;nnz, const Epetra_Comm &amp;comm)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Trilinos_Util_CountMatrixMarket</name>
      <anchorfile>Trilinos__Util__CountMatrixMarket_8h.html</anchorfile>
      <anchor>a00c16fec9947016a2ef7c8312a474004</anchor>
      <arglist>(const char *data_file, std::vector&lt; int &gt; &amp;non_zeros, long long &amp;N_rows, long long &amp;nnz, const Epetra_Comm &amp;comm)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Trilinos_Util_CountTriples.cpp</name>
    <path>/Users/sscoll/dist/trilinos/packages/triutils/src/</path>
    <filename>Trilinos__Util__CountTriples_8cpp</filename>
    <member kind="function">
      <type>void</type>
      <name>Trilinos_Util_CountTriples_internal</name>
      <anchorfile>Trilinos__Util__CountTriples_8cpp.html</anchorfile>
      <anchor>a72b3c6c53a514e65e4b60588db363598</anchor>
      <arglist>(const char *data_file, bool symmetric, std::vector&lt; int &gt; &amp;non_zeros, int_type &amp;N_rows, int_type &amp;nnz, const Epetra_Comm &amp;comm, bool TimDavisHeader=false, bool ZeroBased=false)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Trilinos_Util_CountTriples</name>
      <anchorfile>Trilinos__Util__CountTriples_8cpp.html</anchorfile>
      <anchor>a41ce1fd9486425b35c84ebef0b4b31b7</anchor>
      <arglist>(const char *data_file, bool symmetric, std::vector&lt; int &gt; &amp;non_zeros, int &amp;N_rows, int &amp;nnz, const Epetra_Comm &amp;comm, bool TimDavisHeader=false, bool ZeroBased=false)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Trilinos_Util_CountTriples</name>
      <anchorfile>Trilinos__Util__CountTriples_8cpp.html</anchorfile>
      <anchor>a0eb229475f649edf7d2022f01807d683</anchor>
      <arglist>(const char *data_file, bool symmetric, std::vector&lt; int &gt; &amp;non_zeros, long long &amp;N_rows, long long &amp;nnz, const Epetra_Comm &amp;comm, bool TimDavisHeader=false, bool ZeroBased=false)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Trilinos_Util_CountTriples.h</name>
    <path>/Users/sscoll/dist/trilinos/packages/triutils/src/</path>
    <filename>Trilinos__Util__CountTriples_8h</filename>
    <member kind="function">
      <type>void</type>
      <name>Trilinos_Util_CountTriples</name>
      <anchorfile>Trilinos__Util__CountTriples_8h.html</anchorfile>
      <anchor>a41ce1fd9486425b35c84ebef0b4b31b7</anchor>
      <arglist>(const char *data_file, bool symmetric, std::vector&lt; int &gt; &amp;non_zeros, int &amp;N_rows, int &amp;nnz, const Epetra_Comm &amp;comm, bool TimDavisHeader=false, bool ZeroBased=false)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Trilinos_Util_CountTriples</name>
      <anchorfile>Trilinos__Util__CountTriples_8h.html</anchorfile>
      <anchor>a0eb229475f649edf7d2022f01807d683</anchor>
      <arglist>(const char *data_file, bool symmetric, std::vector&lt; int &gt; &amp;non_zeros, long long &amp;N_rows, long long &amp;nnz, const Epetra_Comm &amp;comm, bool TimDavisHeader=false, bool ZeroBased=false)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Trilinos_Util_create_vbr.cpp</name>
    <path>/Users/sscoll/dist/trilinos/packages/triutils/src/</path>
    <filename>Trilinos__Util__create__vbr_8cpp</filename>
    <includes id="Trilinos__Util_8h" name="Trilinos_Util.h" local="yes" imported="no">Trilinos_Util.h</includes>
    <member kind="function">
      <type>void</type>
      <name>Trilinos_Util_create_vbr</name>
      <anchorfile>Trilinos__Util__create__vbr_8cpp.html</anchorfile>
      <anchor>a6ffe04c3e454516704d26f7aae41a8f7</anchor>
      <arglist>(const Epetra_Comm &amp;Comm, const char *partition_file, int *N_global, int *N_blk_global, int *n_nonzeros, int *n_blk_nonzeros, int *N_update, int **update, int *bindx_msr, double *val_msr, double **val, int **indx, int **rpntr, int **cpntr, int **bpntr, int **bindx)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Trilinos_Util_CrsMatrixGallery.cpp</name>
    <path>/Users/sscoll/dist/trilinos/packages/triutils/src/</path>
    <filename>Trilinos__Util__CrsMatrixGallery_8cpp</filename>
    <includes id="Trilinos__Util_8h" name="Trilinos_Util.h" local="yes" imported="no">Trilinos_Util.h</includes>
    <includes id="Trilinos__Util__CommandLineParser_8h" name="Trilinos_Util_CommandLineParser.h" local="yes" imported="no">Trilinos_Util_CommandLineParser.h</includes>
    <includes id="Trilinos__Util__CrsMatrixGallery_8h" name="Trilinos_Util_CrsMatrixGallery.h" local="yes" imported="no">Trilinos_Util_CrsMatrixGallery.h</includes>
    <namespace>Trilinos_Util</namespace>
    <member kind="function">
      <type>ostream &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>namespaceTrilinos__Util.html</anchorfile>
      <anchor>abf4c512ffd883d27e3ed3d626673842c</anchor>
      <arglist>(ostream &amp;os, const Trilinos_Util::CrsMatrixGallery &amp;G)</arglist>
    </member>
    <member kind="variable">
      <type>const double</type>
      <name>UNDEF</name>
      <anchorfile>Trilinos__Util__CrsMatrixGallery_8cpp.html</anchorfile>
      <anchor>af63e6c601f26236998fb4c3e1181aeec</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const bool</type>
      <name>Scaling</name>
      <anchorfile>Trilinos__Util__CrsMatrixGallery_8cpp.html</anchorfile>
      <anchor>ad7112761149fcb5f57a8801e3be0541a</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Trilinos_Util_CrsMatrixGallery.h</name>
    <path>/Users/sscoll/dist/trilinos/packages/triutils/src/</path>
    <filename>Trilinos__Util__CrsMatrixGallery_8h</filename>
    <includes id="Trilinos__Util__CommandLineParser_8h" name="Trilinos_Util_CommandLineParser.h" local="yes" imported="no">Trilinos_Util_CommandLineParser.h</includes>
    <class kind="class">Trilinos_Util::CrsMatrixGallery</class>
    <class kind="class">Trilinos_Util::VbrMatrixGallery</class>
    <namespace>Trilinos_Util</namespace>
  </compound>
  <compound kind="file">
    <name>Trilinos_Util_csrcsc.cpp</name>
    <path>/Users/sscoll/dist/trilinos/packages/triutils/src/</path>
    <filename>Trilinos__Util__csrcsc_8cpp</filename>
    <includes id="Trilinos__Util_8h" name="Trilinos_Util.h" local="yes" imported="no">Trilinos_Util.h</includes>
    <member kind="function">
      <type>int</type>
      <name>Trilinos_Util_csrcsc</name>
      <anchorfile>Trilinos__Util__csrcsc_8cpp.html</anchorfile>
      <anchor>afd2ee233bd1fa2ad5350bcaf7c8e09e8</anchor>
      <arglist>(int n, int n2, int job, int ipos, double *a, int *ja, int *ia, double *ao, int *jao, int *iao)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Trilinos_Util_csrmsr.cpp</name>
    <path>/Users/sscoll/dist/trilinos/packages/triutils/src/</path>
    <filename>Trilinos__Util__csrmsr_8cpp</filename>
    <includes id="Trilinos__Util_8h" name="Trilinos_Util.h" local="yes" imported="no">Trilinos_Util.h</includes>
    <member kind="function">
      <type>int</type>
      <name>Trilinos_Util_csrmsr</name>
      <anchorfile>Trilinos__Util__csrmsr_8cpp.html</anchorfile>
      <anchor>a30273b2f224195d6b85bb828d7fc4698</anchor>
      <arglist>(int n, double *a, int *ja, int *ia, double *ao, int *jao, double *wk, int *iwk)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Trilinos_Util_distrib_msr_matrix.cpp</name>
    <path>/Users/sscoll/dist/trilinos/packages/triutils/src/</path>
    <filename>Trilinos__Util__distrib__msr__matrix_8cpp</filename>
    <includes id="Trilinos__Util_8h" name="Trilinos_Util.h" local="yes" imported="no">Trilinos_Util.h</includes>
    <member kind="function">
      <type>void</type>
      <name>Trilinos_Util_distrib_msr_matrix</name>
      <anchorfile>Trilinos__Util__distrib__msr__matrix_8cpp.html</anchorfile>
      <anchor>a88ef41ef9b79777da0b6391228032829</anchor>
      <arglist>(const Epetra_Comm &amp;Comm, int *N_global, int *n_nonzeros, int *N_update, int **update, double **val, int **bindx, double **x, double **b, double **xexact)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Trilinos_Util_distrib_msr_matrix</name>
      <anchorfile>Trilinos__Util__distrib__msr__matrix_8cpp.html</anchorfile>
      <anchor>a4406c9d4ffff89bf696a3cfdf2b70868</anchor>
      <arglist>(const Epetra_Comm &amp;Comm, int *N_global, int *n_nonzeros, int *N_update, int **update, double **val, int **bindx)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Trilinos_Util_distrib_vbr_matrix.cpp</name>
    <path>/Users/sscoll/dist/trilinos/packages/triutils/src/</path>
    <filename>Trilinos__Util__distrib__vbr__matrix_8cpp</filename>
    <includes id="Trilinos__Util_8h" name="Trilinos_Util.h" local="yes" imported="no">Trilinos_Util.h</includes>
    <member kind="function">
      <type>void</type>
      <name>Trilinos_Util_distrib_vbr_matrix</name>
      <anchorfile>Trilinos__Util__distrib__vbr__matrix_8cpp.html</anchorfile>
      <anchor>a7a7e44685daa573d92cd473d604b9481</anchor>
      <arglist>(const Epetra_Comm &amp;Comm, int *N_global, int *N_blk_global, int *n_nonzeros, int *n_blk_nonzeros, int *N_update, int **update, double **val, int **indx, int **rpntr, int **cpntr, int **bpntr, int **bindx, double **x, double **b, double **xexact)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Trilinos_Util_duscr_vbr.cpp</name>
    <path>/Users/sscoll/dist/trilinos/packages/triutils/src/</path>
    <filename>Trilinos__Util__duscr__vbr_8cpp</filename>
    <includes id="Trilinos__Util_8h" name="Trilinos_Util.h" local="yes" imported="no">Trilinos_Util.h</includes>
    <member kind="function">
      <type>void</type>
      <name>Trilinos_Util_duscr_vbr</name>
      <anchorfile>Trilinos__Util__duscr__vbr_8cpp.html</anchorfile>
      <anchor>a45509056f552bfe35e6a2deba68d5aac</anchor>
      <arglist>(int n, double *val, int *indx, int *bindx, int *rpntr, int *cpntr, int *bpntrb, int *bpntre, SPBLASMAT *A)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Trilinos_Util_dusds_vbr.cpp</name>
    <path>/Users/sscoll/dist/trilinos/packages/triutils/src/</path>
    <filename>Trilinos__Util__dusds__vbr_8cpp</filename>
    <includes id="Trilinos__Util_8h" name="Trilinos_Util.h" local="yes" imported="no">Trilinos_Util.h</includes>
    <member kind="function">
      <type>void</type>
      <name>Trilinos_Util_dusds_vbr</name>
      <anchorfile>Trilinos__Util__dusds__vbr_8cpp.html</anchorfile>
      <anchor>a4c306b902c7026cc7f3b2ea8cd3526fe</anchor>
      <arglist>(SPBLASMAT *A)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Trilinos_Util_dusmm.cpp</name>
    <path>/Users/sscoll/dist/trilinos/packages/triutils/src/</path>
    <filename>Trilinos__Util__dusmm_8cpp</filename>
    <includes id="Trilinos__Util_8h" name="Trilinos_Util.h" local="yes" imported="no">Trilinos_Util.h</includes>
    <member kind="function">
      <type>void</type>
      <name>Trilinos_Util_dusmm</name>
      <anchorfile>Trilinos__Util__dusmm_8cpp.html</anchorfile>
      <anchor>a75a68e53cdc748b595ddbe9eb0762ed4</anchor>
      <arglist>(int m, int nrhs, int k, double alpha, SPBLASMAT *A, double *x, int xstride, double beta, double *b, int bstride)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Trilinos_Util_GenerateCrsProblem.cpp</name>
    <path>/Users/sscoll/dist/trilinos/packages/triutils/src/</path>
    <filename>Trilinos__Util__GenerateCrsProblem_8cpp</filename>
    <includes id="Trilinos__Util_8h" name="Trilinos_Util.h" local="yes" imported="no">Trilinos_Util.h</includes>
    <member kind="function">
      <type>void</type>
      <name>Trilinos_Util_GenerateCrsProblem</name>
      <anchorfile>Trilinos__Util__GenerateCrsProblem_8cpp.html</anchorfile>
      <anchor>a8147a6071085d9f9130a2a4158ba5a69</anchor>
      <arglist>(int nx, int ny, int npoints, int *xoff, int *yoff, const Epetra_Comm &amp;comm, Epetra_Map *&amp;map, Epetra_CrsMatrix *&amp;A, Epetra_Vector *&amp;x, Epetra_Vector *&amp;b, Epetra_Vector *&amp;xexact, int indexBase)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Trilinos_Util_GenerateCrsProblem64</name>
      <anchorfile>Trilinos__Util__GenerateCrsProblem_8cpp.html</anchorfile>
      <anchor>a712b490990ed8d99f9aad816deb42560</anchor>
      <arglist>(int nx, int ny, int npoints, int *xoff, int *yoff, const Epetra_Comm &amp;comm, Epetra_Map *&amp;map, Epetra_CrsMatrix *&amp;A, Epetra_Vector *&amp;x, Epetra_Vector *&amp;b, Epetra_Vector *&amp;xexact, long long indexBase)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>TTrilinos_Util_GenerateCrsProblem</name>
      <anchorfile>Trilinos__Util__GenerateCrsProblem_8cpp.html</anchorfile>
      <anchor>a8611c1b368a83c543501a02caa512535</anchor>
      <arglist>(int nx, int ny, int npoints, int *xoff, int *yoff, int nrhs, const Epetra_Comm &amp;comm, Epetra_Map *&amp;map, Epetra_CrsMatrix *&amp;A, Epetra_MultiVector *&amp;x, Epetra_MultiVector *&amp;b, Epetra_MultiVector *&amp;xexact, int_type indexBase)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Trilinos_Util_GenerateCrsProblem</name>
      <anchorfile>Trilinos__Util__GenerateCrsProblem_8cpp.html</anchorfile>
      <anchor>a90b43d1b9febb6de31d173347687f9da</anchor>
      <arglist>(int nx, int ny, int npoints, int *xoff, int *yoff, int nrhs, const Epetra_Comm &amp;comm, Epetra_Map *&amp;map, Epetra_CrsMatrix *&amp;A, Epetra_MultiVector *&amp;x, Epetra_MultiVector *&amp;b, Epetra_MultiVector *&amp;xexact, int indexBase)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Trilinos_Util_GenerateCrsProblem64</name>
      <anchorfile>Trilinos__Util__GenerateCrsProblem_8cpp.html</anchorfile>
      <anchor>a17e893d5aab02cf4f46cb5ef90cf9dda</anchor>
      <arglist>(int nx, int ny, int npoints, int *xoff, int *yoff, int nrhs, const Epetra_Comm &amp;comm, Epetra_Map *&amp;map, Epetra_CrsMatrix *&amp;A, Epetra_MultiVector *&amp;x, Epetra_MultiVector *&amp;b, Epetra_MultiVector *&amp;xexact, long long indexBase)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Trilinos_Util_GenerateVbrProblem.cpp</name>
    <path>/Users/sscoll/dist/trilinos/packages/triutils/src/</path>
    <filename>Trilinos__Util__GenerateVbrProblem_8cpp</filename>
    <includes id="Trilinos__Util_8h" name="Trilinos_Util.h" local="yes" imported="no">Trilinos_Util.h</includes>
    <member kind="function">
      <type>void</type>
      <name>Trilinos_Util_GenerateVbrProblem</name>
      <anchorfile>Trilinos__Util__GenerateVbrProblem_8cpp.html</anchorfile>
      <anchor>a98dcb641ece5b682849305903cddaadf</anchor>
      <arglist>(int nx, int ny, int npoints, int *xoff, int *yoff, int nsizes, int *sizes, const Epetra_Comm &amp;comm, Epetra_BlockMap *&amp;map, Epetra_VbrMatrix *&amp;A, Epetra_Vector *&amp;x, Epetra_Vector *&amp;b, Epetra_Vector *&amp;xexact)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Trilinos_Util_GenerateVbrProblem</name>
      <anchorfile>Trilinos__Util__GenerateVbrProblem_8cpp.html</anchorfile>
      <anchor>a683e1ea1a40638d9f7b79fde474f189d</anchor>
      <arglist>(int nx, int ny, int npoints, int *xoff, int *yoff, int nsizes, int *sizes, int nrhs, const Epetra_Comm &amp;comm, Epetra_BlockMap *&amp;map, Epetra_VbrMatrix *&amp;A, Epetra_MultiVector *&amp;x, Epetra_MultiVector *&amp;b, Epetra_MultiVector *&amp;xexact)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Trilinos_Util_iohb.cpp</name>
    <path>/Users/sscoll/dist/trilinos/packages/triutils/src/</path>
    <filename>Trilinos__Util__iohb_8cpp</filename>
    <includes id="Trilinos__Util__iohb_8h" name="Trilinos_Util_iohb.h" local="yes" imported="no">Trilinos_Util_iohb.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>_SP_base</name>
      <anchorfile>Trilinos__Util__iohb_8cpp.html</anchorfile>
      <anchor>ab0f01139eec5e71bcf0771a630ee20d5</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>char *</type>
      <name>substr</name>
      <anchorfile>Trilinos__Util__iohb_8cpp.html</anchorfile>
      <anchor>ad6dd6a0619796389a696edd656397509</anchor>
      <arglist>(const char *S, const int pos, const int len)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>upcase</name>
      <anchorfile>Trilinos__Util__iohb_8cpp.html</anchorfile>
      <anchor>a7643cbba1c818f74e4b26ed53b6742f3</anchor>
      <arglist>(char *S)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>IOHBTerminate</name>
      <anchorfile>Trilinos__Util__iohb_8cpp.html</anchorfile>
      <anchor>ab76cc2836bbc4e7dda7b67e68d65c899</anchor>
      <arglist>(const char *message)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>readHB_info</name>
      <anchorfile>Trilinos__Util__iohb_8cpp.html</anchorfile>
      <anchor>a47416463d6ed24dc00c36ac840c6a594</anchor>
      <arglist>(const char *filename, int *M, int *N, int *nz, char **Type, int *Nrhs)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>readHB_header</name>
      <anchorfile>Trilinos__Util__iohb_8cpp.html</anchorfile>
      <anchor>a15b780ca5af81919959404c26c9d8160</anchor>
      <arglist>(std::FILE *in_file, char *Title, char *Key, char *Type, int *Nrow, int *Ncol, int *Nnzero, int *Nrhs, char *Ptrfmt, char *Indfmt, char *Valfmt, char *Rhsfmt, int *Ptrcrd, int *Indcrd, int *Valcrd, int *Rhscrd, char *Rhstype)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>readHB_mat_double</name>
      <anchorfile>Trilinos__Util__iohb_8cpp.html</anchorfile>
      <anchor>a88851b95bbb174de15ff2471d5ad5b05</anchor>
      <arglist>(const char *filename, int colptr[], int rowind[], double val[])</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>readHB_newmat_double</name>
      <anchorfile>Trilinos__Util__iohb_8cpp.html</anchorfile>
      <anchor>ac2a7d7d7bd6bb9402e5922b9f8a13d7a</anchor>
      <arglist>(const char *filename, int *M, int *N, int *nonzeros, int **colptr, int **rowind, double **val)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>readHB_aux_double</name>
      <anchorfile>Trilinos__Util__iohb_8cpp.html</anchorfile>
      <anchor>a2d9d6a72375fe17641204aca3aca006e</anchor>
      <arglist>(const char *filename, const char AuxType, double b[])</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>readHB_newaux_double</name>
      <anchorfile>Trilinos__Util__iohb_8cpp.html</anchorfile>
      <anchor>a776c0c58a4583c1b351fd757dcc03e15</anchor>
      <arglist>(const char *filename, const char AuxType, double **b)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>writeHB_mat_double</name>
      <anchorfile>Trilinos__Util__iohb_8cpp.html</anchorfile>
      <anchor>acbadc7e68e733a6f631321c041b9e8f2</anchor>
      <arglist>(const char *filename, int M, int N, int nz, const int colptr[], const int rowind[], const double val[], int Nrhs, const double rhs[], const double guess[], const double exact[], const char *Title, const char *Key, const char *Type, char *Ptrfmt, char *Indfmt, char *Valfmt, char *Rhsfmt, const char *Rhstype)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>readHB_mat_char</name>
      <anchorfile>Trilinos__Util__iohb_8cpp.html</anchorfile>
      <anchor>a78f17cd5dfac983aefd586b3ec2cf6c4</anchor>
      <arglist>(const char *filename, int colptr[], int rowind[], char val[], char *Valfmt)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>readHB_newmat_char</name>
      <anchorfile>Trilinos__Util__iohb_8cpp.html</anchorfile>
      <anchor>ac224fde77d63cab67086317379b8ce04</anchor>
      <arglist>(const char *filename, int *M, int *N, int *nonzeros, int **colptr, int **rowind, char **val, char **Valfmt)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>readHB_aux_char</name>
      <anchorfile>Trilinos__Util__iohb_8cpp.html</anchorfile>
      <anchor>a9590ab0e7d16b150062893fc33786115</anchor>
      <arglist>(const char *filename, const char AuxType, char b[])</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>readHB_newaux_char</name>
      <anchorfile>Trilinos__Util__iohb_8cpp.html</anchorfile>
      <anchor>a25f7828ba0befb468aecec178e670fc1</anchor>
      <arglist>(const char *filename, const char AuxType, char **b, char **Rhsfmt)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>writeHB_mat_char</name>
      <anchorfile>Trilinos__Util__iohb_8cpp.html</anchorfile>
      <anchor>a453f9afbd11f3bea15c087338bfc8fe4</anchor>
      <arglist>(const char *filename, int M, int N, int nz, const int colptr[], const int rowind[], const char val[], int Nrhs, const char rhs[], const char guess[], const char exact[], const char *Title, const char *Key, const char *Type, char *Ptrfmt, char *Indfmt, char *Valfmt, char *Rhsfmt, const char *Rhstype)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ParseIfmt</name>
      <anchorfile>Trilinos__Util__iohb_8cpp.html</anchorfile>
      <anchor>aedcdefc385fa547931686b728942cf8e</anchor>
      <arglist>(char *fmt, int *perline, int *width)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ParseRfmt</name>
      <anchorfile>Trilinos__Util__iohb_8cpp.html</anchorfile>
      <anchor>a11c8b09bf56665a52bbc8a395d5d6175</anchor>
      <arglist>(char *fmt, int *perline, int *width, int *prec, int *flag)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Trilinos_Util_iohb.h</name>
    <path>/Users/sscoll/dist/trilinos/packages/triutils/src/</path>
    <filename>Trilinos__Util__iohb_8h</filename>
    <member kind="function">
      <type>int</type>
      <name>readHB_info</name>
      <anchorfile>Trilinos__Util__iohb_8h.html</anchorfile>
      <anchor>a47416463d6ed24dc00c36ac840c6a594</anchor>
      <arglist>(const char *filename, int *M, int *N, int *nz, char **Type, int *Nrhs)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>readHB_header</name>
      <anchorfile>Trilinos__Util__iohb_8h.html</anchorfile>
      <anchor>a15b780ca5af81919959404c26c9d8160</anchor>
      <arglist>(std::FILE *in_file, char *Title, char *Key, char *Type, int *Nrow, int *Ncol, int *Nnzero, int *Nrhs, char *Ptrfmt, char *Indfmt, char *Valfmt, char *Rhsfmt, int *Ptrcrd, int *Indcrd, int *Valcrd, int *Rhscrd, char *Rhstype)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>readHB_mat_double</name>
      <anchorfile>Trilinos__Util__iohb_8h.html</anchorfile>
      <anchor>a88851b95bbb174de15ff2471d5ad5b05</anchor>
      <arglist>(const char *filename, int colptr[], int rowind[], double val[])</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>readHB_newmat_double</name>
      <anchorfile>Trilinos__Util__iohb_8h.html</anchorfile>
      <anchor>ac2a7d7d7bd6bb9402e5922b9f8a13d7a</anchor>
      <arglist>(const char *filename, int *M, int *N, int *nonzeros, int **colptr, int **rowind, double **val)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>readHB_aux_double</name>
      <anchorfile>Trilinos__Util__iohb_8h.html</anchorfile>
      <anchor>a2d9d6a72375fe17641204aca3aca006e</anchor>
      <arglist>(const char *filename, const char AuxType, double b[])</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>readHB_newaux_double</name>
      <anchorfile>Trilinos__Util__iohb_8h.html</anchorfile>
      <anchor>a776c0c58a4583c1b351fd757dcc03e15</anchor>
      <arglist>(const char *filename, const char AuxType, double **b)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>writeHB_mat_double</name>
      <anchorfile>Trilinos__Util__iohb_8h.html</anchorfile>
      <anchor>acbadc7e68e733a6f631321c041b9e8f2</anchor>
      <arglist>(const char *filename, int M, int N, int nz, const int colptr[], const int rowind[], const double val[], int Nrhs, const double rhs[], const double guess[], const double exact[], const char *Title, const char *Key, const char *Type, char *Ptrfmt, char *Indfmt, char *Valfmt, char *Rhsfmt, const char *Rhstype)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>readHB_mat_char</name>
      <anchorfile>Trilinos__Util__iohb_8h.html</anchorfile>
      <anchor>a78f17cd5dfac983aefd586b3ec2cf6c4</anchor>
      <arglist>(const char *filename, int colptr[], int rowind[], char val[], char *Valfmt)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>readHB_newmat_char</name>
      <anchorfile>Trilinos__Util__iohb_8h.html</anchorfile>
      <anchor>ac224fde77d63cab67086317379b8ce04</anchor>
      <arglist>(const char *filename, int *M, int *N, int *nonzeros, int **colptr, int **rowind, char **val, char **Valfmt)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>readHB_aux_char</name>
      <anchorfile>Trilinos__Util__iohb_8h.html</anchorfile>
      <anchor>a9590ab0e7d16b150062893fc33786115</anchor>
      <arglist>(const char *filename, const char AuxType, char b[])</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>readHB_newaux_char</name>
      <anchorfile>Trilinos__Util__iohb_8h.html</anchorfile>
      <anchor>a25f7828ba0befb468aecec178e670fc1</anchor>
      <arglist>(const char *filename, const char AuxType, char **b, char **Rhsfmt)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>writeHB_mat_char</name>
      <anchorfile>Trilinos__Util__iohb_8h.html</anchorfile>
      <anchor>a453f9afbd11f3bea15c087338bfc8fe4</anchor>
      <arglist>(const char *filename, int M, int N, int nz, const int colptr[], const int rowind[], const char val[], int Nrhs, const char rhs[], const char guess[], const char exact[], const char *Title, const char *Key, const char *Type, char *Ptrfmt, char *Indfmt, char *Valfmt, char *Rhsfmt, const char *Rhstype)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ParseIfmt</name>
      <anchorfile>Trilinos__Util__iohb_8h.html</anchorfile>
      <anchor>aedcdefc385fa547931686b728942cf8e</anchor>
      <arglist>(char *fmt, int *perline, int *width)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ParseRfmt</name>
      <anchorfile>Trilinos__Util__iohb_8h.html</anchorfile>
      <anchor>a11c8b09bf56665a52bbc8a395d5d6175</anchor>
      <arglist>(char *fmt, int *perline, int *width, int *prec, int *flag)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>IOHBTerminate</name>
      <anchorfile>Trilinos__Util__iohb_8h.html</anchorfile>
      <anchor>a88c77ebb1b55ae8b14f5d23130dd00fb</anchor>
      <arglist>(char *message)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Trilinos_Util_msr2vbr.cpp</name>
    <path>/Users/sscoll/dist/trilinos/packages/triutils/src/</path>
    <filename>Trilinos__Util__msr2vbr_8cpp</filename>
    <includes id="Trilinos__Util_8h" name="Trilinos_Util.h" local="yes" imported="no">Trilinos_Util.h</includes>
    <member kind="function">
      <type>void</type>
      <name>Trilinos_Util_msr2vbr</name>
      <anchorfile>Trilinos__Util__msr2vbr_8cpp.html</anchorfile>
      <anchor>a92fbb05f81140f28f11be040c105f485</anchor>
      <arglist>(double val[], int indx[], int rnptr[], int cnptr[], int bnptr[], int bindx[], int msr_bindx[], double msr_val[], int total_blk_rows, int total_blk_cols, int blk_space, int nz_space, int blk_type)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Trilinos_Util_find_block_col</name>
      <anchorfile>Trilinos__Util__msr2vbr_8cpp.html</anchorfile>
      <anchor>a6c619c72b29527fbfdd576942f69fa93</anchor>
      <arglist>(int cnptr[], int column, int max_blocks, int blk_size)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Trilinos_Util_find_block_in_row</name>
      <anchorfile>Trilinos__Util__msr2vbr_8cpp.html</anchorfile>
      <anchor>aafd6bdc281bc4da2d506a9934622f011</anchor>
      <arglist>(int bindx[], int bnptr[], int blk_row, int blk_col, int indx[], int no_elements, double val[], int blk_space, int nz_space)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Trilinos_Util_add_new_ele</name>
      <anchorfile>Trilinos__Util__msr2vbr_8cpp.html</anchorfile>
      <anchor>aa55e25501503fd6ca3278368099b5e84</anchor>
      <arglist>(int cnptr[], int col, int blk_row, int bindx[], int bnptr[], int indx[], double val[], int row, double new_ele, int maxcols, int blk_space, int nz_space, int blk_type)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Trilinos_Util_find_closest_not_larger</name>
      <anchorfile>Trilinos__Util__msr2vbr_8cpp.html</anchorfile>
      <anchor>a4816d9a8238ba79169dcfd4032ad2b08</anchor>
      <arglist>(int key, int list[], int length)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Trilinos_Util_convert_values_to_ptrs</name>
      <anchorfile>Trilinos__Util__msr2vbr_8cpp.html</anchorfile>
      <anchor>ae57c427d71925aaeebed1edda2493c03</anchor>
      <arglist>(int array[], int length, int start)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Trilinos_Util_read_coo.cpp</name>
    <path>/Users/sscoll/dist/trilinos/packages/triutils/src/</path>
    <filename>Trilinos__Util__read__coo_8cpp</filename>
    <includes id="Trilinos__Util_8h" name="Trilinos_Util.h" local="yes" imported="no">Trilinos_Util.h</includes>
    <member kind="function">
      <type>void</type>
      <name>Trilinos_Util_read_coo</name>
      <anchorfile>Trilinos__Util__read__coo_8cpp.html</anchorfile>
      <anchor>ad8a9cfbb5cf2f92d7405e473b059c749</anchor>
      <arglist>(const char *data_file, int MyPID, int *N_global, int *n_nonzeros, double **val, int **bindx, double **x, double **b, double **xexact)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Trilinos_Util_read_hb.cpp</name>
    <path>/Users/sscoll/dist/trilinos/packages/triutils/src/</path>
    <filename>Trilinos__Util__read__hb_8cpp</filename>
    <includes id="Trilinos__Util_8h" name="Trilinos_Util.h" local="yes" imported="no">Trilinos_Util.h</includes>
    <includes id="Trilinos__Util__iohb_8h" name="Trilinos_Util_iohb.h" local="yes" imported="no">Trilinos_Util_iohb.h</includes>
    <member kind="function">
      <type>void</type>
      <name>Trilinos_Util_read_hb</name>
      <anchorfile>Trilinos__Util__read__hb_8cpp.html</anchorfile>
      <anchor>aac89170bd9da716f6cbfe90ca1c72fc6</anchor>
      <arglist>(const char *data_file, int MyPID, int *N_global, int *n_nonzeros, double **val, int **bindx, double **x, double **b, double **xexact)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Trilinos_Util_read_hb</name>
      <anchorfile>Trilinos__Util__read__hb_8cpp.html</anchorfile>
      <anchor>ae07ea7324c18856d0cbed89e6eabddca</anchor>
      <arglist>(const char *data_file, int MyPID, int *N_global, int *n_nonzeros, double **val, int **bindx)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Trilinos_Util_read_vec.cpp</name>
    <path>/Users/sscoll/dist/trilinos/packages/triutils/src/</path>
    <filename>Trilinos__Util__read__vec_8cpp</filename>
    <includes id="Trilinos__Util_8h" name="Trilinos_Util.h" local="yes" imported="no">Trilinos_Util.h</includes>
    <member kind="function">
      <type>void</type>
      <name>Trilinos_Util_read_vec</name>
      <anchorfile>Trilinos__Util__read__vec_8cpp.html</anchorfile>
      <anchor>a65fd8adcd2d88acb9077d3eaf89376f6</anchor>
      <arglist>(const char *filename, int n_equations, double *x)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Trilinos_Util_ReadHb2Epetra.cpp</name>
    <path>/Users/sscoll/dist/trilinos/packages/triutils/src/</path>
    <filename>Trilinos__Util__ReadHb2Epetra_8cpp</filename>
    <includes id="Trilinos__Util_8h" name="Trilinos_Util.h" local="yes" imported="no">Trilinos_Util.h</includes>
    <includes id="Trilinos__Util__iohb_8h" name="Trilinos_Util_iohb.h" local="yes" imported="no">Trilinos_Util_iohb.h</includes>
    <member kind="function">
      <type>void</type>
      <name>Trilinos_Util_ReadHb2Epetra_internal</name>
      <anchorfile>Trilinos__Util__ReadHb2Epetra_8cpp.html</anchorfile>
      <anchor>a078e4846a4d74e6735b1e37adb20189a</anchor>
      <arglist>(const char *data_file, const Epetra_Comm &amp;comm, Epetra_Map *&amp;map, Epetra_CrsMatrix *&amp;A, Epetra_Vector *&amp;x, Epetra_Vector *&amp;b, Epetra_Vector *&amp;xexact, bool FakeLongLong)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Trilinos_Util_ReadHb2Epetra</name>
      <anchorfile>Trilinos__Util__ReadHb2Epetra_8cpp.html</anchorfile>
      <anchor>ade43470ef7d141fc52ba08f39c9f60b8</anchor>
      <arglist>(const char *data_file, const Epetra_Comm &amp;comm, Epetra_Map *&amp;map, Epetra_CrsMatrix *&amp;A, Epetra_Vector *&amp;x, Epetra_Vector *&amp;b, Epetra_Vector *&amp;xexact)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Trilinos_Util_ReadHb2Epetra64</name>
      <anchorfile>Trilinos__Util__ReadHb2Epetra_8cpp.html</anchorfile>
      <anchor>a3f6023f04fa8200248ad6da2194b5643</anchor>
      <arglist>(const char *data_file, const Epetra_Comm &amp;comm, Epetra_Map *&amp;map, Epetra_CrsMatrix *&amp;A, Epetra_Vector *&amp;x, Epetra_Vector *&amp;b, Epetra_Vector *&amp;xexact)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Trilinos_Util_ReadHb2EpetraVbr.cpp</name>
    <path>/Users/sscoll/dist/trilinos/packages/triutils/src/</path>
    <filename>Trilinos__Util__ReadHb2EpetraVbr_8cpp</filename>
    <includes id="Trilinos__Util_8h" name="Trilinos_Util.h" local="yes" imported="no">Trilinos_Util.h</includes>
    <includes id="Trilinos__Util__iohb_8h" name="Trilinos_Util_iohb.h" local="yes" imported="no">Trilinos_Util_iohb.h</includes>
    <member kind="function">
      <type>void</type>
      <name>Trilinos_Util_ReadHb2EpetraVbr</name>
      <anchorfile>Trilinos__Util__ReadHb2EpetraVbr_8cpp.html</anchorfile>
      <anchor>ab33ffd3c8749ed492f66cf5b1b994e36</anchor>
      <arglist>(const char *data_file, const char *partitioning, const Epetra_Comm &amp;comm, Epetra_BlockMap *&amp;map, Epetra_VbrMatrix *&amp;A, Epetra_Vector *&amp;x, Epetra_Vector *&amp;b, Epetra_Vector *&amp;xexact)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Trilinos_Util_ReadHpc2Epetra.cpp</name>
    <path>/Users/sscoll/dist/trilinos/packages/triutils/src/</path>
    <filename>Trilinos__Util__ReadHpc2Epetra_8cpp</filename>
    <includes id="Trilinos__Util_8h" name="Trilinos_Util.h" local="yes" imported="no">Trilinos_Util.h</includes>
    <includes id="Trilinos__Util__iohb_8h" name="Trilinos_Util_iohb.h" local="yes" imported="no">Trilinos_Util_iohb.h</includes>
    <member kind="function">
      <type>void</type>
      <name>Trilinos_Util_ReadHpc2Epetra_internal</name>
      <anchorfile>Trilinos__Util__ReadHpc2Epetra_8cpp.html</anchorfile>
      <anchor>aca8b309e174a158c303b7afb01066ff6</anchor>
      <arglist>(const char *data_file, const Epetra_Comm &amp;comm, Epetra_Map *&amp;map, Epetra_CrsMatrix *&amp;A, Epetra_Vector *&amp;x, Epetra_Vector *&amp;b, Epetra_Vector *&amp;xexact)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Trilinos_Util_ReadHpc2Epetra</name>
      <anchorfile>Trilinos__Util__ReadHpc2Epetra_8cpp.html</anchorfile>
      <anchor>a220896792d63ceec784b4c2d4a436012</anchor>
      <arglist>(const char *data_file, const Epetra_Comm &amp;comm, Epetra_Map *&amp;map, Epetra_CrsMatrix *&amp;A, Epetra_Vector *&amp;x, Epetra_Vector *&amp;b, Epetra_Vector *&amp;xexact)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Trilinos_Util_ReadHpc2Epetra64</name>
      <anchorfile>Trilinos__Util__ReadHpc2Epetra_8cpp.html</anchorfile>
      <anchor>a886661804e2b5c0c35f6cff51786826b</anchor>
      <arglist>(const char *data_file, const Epetra_Comm &amp;comm, Epetra_Map *&amp;map, Epetra_CrsMatrix *&amp;A, Epetra_Vector *&amp;x, Epetra_Vector *&amp;b, Epetra_Vector *&amp;xexact)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Trilinos_Util_ReadMatrixMarket2Epetra.cpp</name>
    <path>/Users/sscoll/dist/trilinos/packages/triutils/src/</path>
    <filename>Trilinos__Util__ReadMatrixMarket2Epetra_8cpp</filename>
    <includes id="Trilinos__Util__CountMatrixMarket_8h" name="Trilinos_Util_CountMatrixMarket.h" local="yes" imported="no">Trilinos_Util_CountMatrixMarket.h</includes>
    <member kind="function">
      <type>int</type>
      <name>Trilinos_Util_ReadMatrixMarket2Epetra_internal</name>
      <anchorfile>Trilinos__Util__ReadMatrixMarket2Epetra_8cpp.html</anchorfile>
      <anchor>ab5d5acec53eed28f598c179fb895fde3</anchor>
      <arglist>(const char *data_file, const Epetra_Comm &amp;comm, Epetra_Map *&amp;map, Epetra_CrsMatrix *&amp;A, Epetra_Vector *&amp;x, Epetra_Vector *&amp;b, Epetra_Vector *&amp;xexact)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Trilinos_Util_ReadMatrixMarket2Epetra</name>
      <anchorfile>Trilinos__Util__ReadMatrixMarket2Epetra_8cpp.html</anchorfile>
      <anchor>afd08bdf81134414038d4749276d838aa</anchor>
      <arglist>(const char *data_file, const Epetra_Comm &amp;comm, Epetra_Map *&amp;map, Epetra_CrsMatrix *&amp;A, Epetra_Vector *&amp;x, Epetra_Vector *&amp;b, Epetra_Vector *&amp;xexact)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Trilinos_Util_ReadMatrixMarket2Epetra64</name>
      <anchorfile>Trilinos__Util__ReadMatrixMarket2Epetra_8cpp.html</anchorfile>
      <anchor>ab20972d8c9bc34c8e58dbef604386076</anchor>
      <arglist>(const char *data_file, const Epetra_Comm &amp;comm, Epetra_Map *&amp;map, Epetra_CrsMatrix *&amp;A, Epetra_Vector *&amp;x, Epetra_Vector *&amp;b, Epetra_Vector *&amp;xexact)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Trilinos_Util_ReadMatrixMarket2Epetra.h</name>
    <path>/Users/sscoll/dist/trilinos/packages/triutils/src/</path>
    <filename>Trilinos__Util__ReadMatrixMarket2Epetra_8h</filename>
    <member kind="function">
      <type>int</type>
      <name>Trilinos_Util_ReadMatrixMarket2Epetra_internal</name>
      <anchorfile>Trilinos__Util__ReadMatrixMarket2Epetra_8h.html</anchorfile>
      <anchor>ab5d5acec53eed28f598c179fb895fde3</anchor>
      <arglist>(const char *data_file, const Epetra_Comm &amp;comm, Epetra_Map *&amp;map, Epetra_CrsMatrix *&amp;A, Epetra_Vector *&amp;x, Epetra_Vector *&amp;b, Epetra_Vector *&amp;xexact)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Trilinos_Util_ReadMatrixMarket2Epetra</name>
      <anchorfile>Trilinos__Util__ReadMatrixMarket2Epetra_8h.html</anchorfile>
      <anchor>afd08bdf81134414038d4749276d838aa</anchor>
      <arglist>(const char *data_file, const Epetra_Comm &amp;comm, Epetra_Map *&amp;map, Epetra_CrsMatrix *&amp;A, Epetra_Vector *&amp;x, Epetra_Vector *&amp;b, Epetra_Vector *&amp;xexact)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Trilinos_Util_ReadMatrixMarket2Epetra64</name>
      <anchorfile>Trilinos__Util__ReadMatrixMarket2Epetra_8h.html</anchorfile>
      <anchor>ab20972d8c9bc34c8e58dbef604386076</anchor>
      <arglist>(const char *data_file, const Epetra_Comm &amp;comm, Epetra_Map *&amp;map, Epetra_CrsMatrix *&amp;A, Epetra_Vector *&amp;x, Epetra_Vector *&amp;b, Epetra_Vector *&amp;xexact)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Trilinos_Util_ReadTriples2Epetra.cpp</name>
    <path>/Users/sscoll/dist/trilinos/packages/triutils/src/</path>
    <filename>Trilinos__Util__ReadTriples2Epetra_8cpp</filename>
    <includes id="Trilinos__Util__CountTriples_8h" name="Trilinos_Util_CountTriples.h" local="yes" imported="no">Trilinos_Util_CountTriples.h</includes>
    <member kind="function">
      <type>int</type>
      <name>Trilinos_Util_ReadTriples2Epetra_internal</name>
      <anchorfile>Trilinos__Util__ReadTriples2Epetra_8cpp.html</anchorfile>
      <anchor>a738120d3b203c9997b16b8c2327e7892</anchor>
      <arglist>(const char *data_file, bool symmetric, const Epetra_Comm &amp;comm, Epetra_Map *&amp;map, Epetra_CrsMatrix *&amp;A, Epetra_Vector *&amp;x, Epetra_Vector *&amp;b, Epetra_Vector *&amp;xexact, bool NonUniformMap=false, bool TimDavisHeader=false, bool ZeroBased=false)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Trilinos_Util_ReadTriples2Epetra</name>
      <anchorfile>Trilinos__Util__ReadTriples2Epetra_8cpp.html</anchorfile>
      <anchor>a41c9b00279c7713964e962a624fbd0be</anchor>
      <arglist>(const char *data_file, bool symmetric, const Epetra_Comm &amp;comm, Epetra_Map *&amp;map, Epetra_CrsMatrix *&amp;A, Epetra_Vector *&amp;x, Epetra_Vector *&amp;b, Epetra_Vector *&amp;xexact, bool NonUniformMap=false, bool TimDavisHeader=false, bool ZeroBased=false)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Trilinos_Util_ReadTriples2Epetra64</name>
      <anchorfile>Trilinos__Util__ReadTriples2Epetra_8cpp.html</anchorfile>
      <anchor>a8602ba1dec9d829bde1f50b5c1be22b1</anchor>
      <arglist>(const char *data_file, bool symmetric, const Epetra_Comm &amp;comm, Epetra_Map *&amp;map, Epetra_CrsMatrix *&amp;A, Epetra_Vector *&amp;x, Epetra_Vector *&amp;b, Epetra_Vector *&amp;xexact, bool NonUniformMap=false, bool TimDavisHeader=false, bool ZeroBased=false)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Trilinos_Util_scscmv.cpp</name>
    <path>/Users/sscoll/dist/trilinos/packages/triutils/src/</path>
    <filename>Trilinos__Util__scscmv_8cpp</filename>
    <includes id="Trilinos__Util_8h" name="Trilinos_Util.h" local="yes" imported="no">Trilinos_Util.h</includes>
    <member kind="function">
      <type>void</type>
      <name>Trilinos_Util_scscmv</name>
      <anchorfile>Trilinos__Util__scscmv_8cpp.html</anchorfile>
      <anchor>a19e8c2b21be7ab02c4fcee86ac6c13f1</anchor>
      <arglist>(int isym, int m, int n, double *val, int *indx, int *pntr, double *x, double *y)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Trilinos_Util_scscres.cpp</name>
    <path>/Users/sscoll/dist/trilinos/packages/triutils/src/</path>
    <filename>Trilinos__Util__scscres_8cpp</filename>
    <includes id="Trilinos__Util_8h" name="Trilinos_Util.h" local="yes" imported="no">Trilinos_Util.h</includes>
    <member kind="function">
      <type>double</type>
      <name>Trilinos_Util_scscres</name>
      <anchorfile>Trilinos__Util__scscres_8cpp.html</anchorfile>
      <anchor>a95949db41f6721a507db3e8563d5d7bc</anchor>
      <arglist>(int isym, int m, int n, double *val, int *indx, int *pntr, double *x, double *b)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Trilinos_Util_smsrres.cpp</name>
    <path>/Users/sscoll/dist/trilinos/packages/triutils/src/</path>
    <filename>Trilinos__Util__smsrres_8cpp</filename>
    <includes id="Trilinos__Util_8h" name="Trilinos_Util.h" local="yes" imported="no">Trilinos_Util.h</includes>
    <member kind="function">
      <type>double</type>
      <name>Trilinos_Util_smsrres</name>
      <anchorfile>Trilinos__Util__smsrres_8cpp.html</anchorfile>
      <anchor>a624762f02345f0e68d37787652897764</anchor>
      <arglist>(int m, int n, double *val, int *indx, double *xlocal, double *x, double *b)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Trilinos_Util_ssrcsr.cpp</name>
    <path>/Users/sscoll/dist/trilinos/packages/triutils/src/</path>
    <filename>Trilinos__Util__ssrcsr_8cpp</filename>
    <includes id="Trilinos__Util_8h" name="Trilinos_Util.h" local="yes" imported="no">Trilinos_Util.h</includes>
    <member kind="function">
      <type>int</type>
      <name>Trilinos_Util_ssrcsr</name>
      <anchorfile>Trilinos__Util__ssrcsr_8cpp.html</anchorfile>
      <anchor>a16bdbd7893e44d70cb98c8415ec70d72</anchor>
      <arglist>(int job, int value2, int nrow, double *a, int *ja, int *ia, int nzmax, double *ao, int *jao, int *iao, int *indu, int *iwk)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Trilinos_Util_svbrres.cpp</name>
    <path>/Users/sscoll/dist/trilinos/packages/triutils/src/</path>
    <filename>Trilinos__Util__svbrres_8cpp</filename>
    <includes id="Trilinos__Util_8h" name="Trilinos_Util.h" local="yes" imported="no">Trilinos_Util.h</includes>
    <member kind="function">
      <type>double</type>
      <name>Trilinos_Util_svbrres</name>
      <anchorfile>Trilinos__Util__svbrres_8cpp.html</anchorfile>
      <anchor>a397486fc0dd62929b6af2ea464f8519b</anchor>
      <arglist>(int m, int n, int m_blk, double *val, int *indx, int *bindx, int *rpntr, int *cpntr, int *bpntrb, int *bpntre, double *x, double *b)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Trilinos_Util_Version.h</name>
    <path>/Users/sscoll/dist/trilinos/packages/triutils/src/</path>
    <filename>Trilinos__Util__Version_8h</filename>
    <includes id="Trilinos__Util_8h" name="Trilinos_Util.h" local="yes" imported="no">Trilinos_Util.h</includes>
    <member kind="function">
      <type>std::string</type>
      <name>Triutils_Version</name>
      <anchorfile>Trilinos__Util__Version_8h.html</anchorfile>
      <anchor>a4f7991ace17a1597450a5819925c070b</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Trilinos_Util_write_vec.cpp</name>
    <path>/Users/sscoll/dist/trilinos/packages/triutils/src/</path>
    <filename>Trilinos__Util__write__vec_8cpp</filename>
    <includes id="Trilinos__Util_8h" name="Trilinos_Util.h" local="yes" imported="no">Trilinos_Util.h</includes>
    <member kind="function">
      <type>void</type>
      <name>Trilinos_Util_write_vec</name>
      <anchorfile>Trilinos__Util__write__vec_8cpp.html</anchorfile>
      <anchor>a299d431333fb07242a88b745b2b3f541</anchor>
      <arglist>(const char *filename, int n_equations, double *x)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Trilinos_Util::CommandLineParser</name>
    <filename>classTrilinos__Util_1_1CommandLineParser.html</filename>
    <base>Trilinos_Util_Map</base>
    <member kind="function">
      <type></type>
      <name>CommandLineParser</name>
      <anchorfile>classTrilinos__Util_1_1CommandLineParser.html</anchorfile>
      <anchor>a290d071ef0b6cb15fbf031510b15d4ee</anchor>
      <arglist>(int argc, char *argv[])</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual std::string</type>
      <name>GetProgramName</name>
      <anchorfile>classTrilinos__Util_1_1CommandLineParser.html</anchorfile>
      <anchor>ab2a1683885e10a7d7b35f37ae315b8d5</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>GetIntShellVariable</name>
      <anchorfile>classTrilinos__Util_1_1CommandLineParser.html</anchorfile>
      <anchor>a6df7ddec5bbb51495f353b3dc830f206</anchor>
      <arglist>(const char *str)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual double</type>
      <name>GetDoubleShellVariable</name>
      <anchorfile>classTrilinos__Util_1_1CommandLineParser.html</anchorfile>
      <anchor>a3fc41c21c1191d492c457fa84e9a768c</anchor>
      <arglist>(const char *str)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual std::string</type>
      <name>GetStringShellVariable</name>
      <anchorfile>classTrilinos__Util_1_1CommandLineParser.html</anchorfile>
      <anchor>aa9b53abec20032b1fb808400efe9e886</anchor>
      <arglist>(const char *str)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>CommandLineParser</name>
      <anchorfile>classTrilinos__Util_1_1CommandLineParser.html</anchorfile>
      <anchor>a290d071ef0b6cb15fbf031510b15d4ee</anchor>
      <arglist>(int argc, char *argv[])</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual std::string</type>
      <name>GetProgramName</name>
      <anchorfile>classTrilinos__Util_1_1CommandLineParser.html</anchorfile>
      <anchor>ab2a1683885e10a7d7b35f37ae315b8d5</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>GetIntShellVariable</name>
      <anchorfile>classTrilinos__Util_1_1CommandLineParser.html</anchorfile>
      <anchor>a6df7ddec5bbb51495f353b3dc830f206</anchor>
      <arglist>(const char *str)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual double</type>
      <name>GetDoubleShellVariable</name>
      <anchorfile>classTrilinos__Util_1_1CommandLineParser.html</anchorfile>
      <anchor>a3fc41c21c1191d492c457fa84e9a768c</anchor>
      <arglist>(const char *str)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual std::string</type>
      <name>GetStringShellVariable</name>
      <anchorfile>classTrilinos__Util_1_1CommandLineParser.html</anchorfile>
      <anchor>aa9b53abec20032b1fb808400efe9e886</anchor>
      <arglist>(const char *str)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Trilinos_Util::CrsMatrixGallery</name>
    <filename>classTrilinos__Util_1_1CrsMatrixGallery.html</filename>
    <member kind="function">
      <type></type>
      <name>CrsMatrixGallery</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>a2aa2bbff00dffa50eaa073b3b466aba2</anchor>
      <arglist>(const std::string name, const Epetra_Comm &amp;comm, bool UseLongLong=false)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>CrsMatrixGallery</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>a66b5b285b1983c9a9e3ae22ec6ad5b7f</anchor>
      <arglist>(const std::string name, const Epetra_Map &amp;map)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~CrsMatrixGallery</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>a07b02e5e0d300f3838c8bc3a2dd28ec5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Set</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>a438b724bfac9dfd60c5cf2f79e376f07</anchor>
      <arglist>(const std::string parameter, const int value)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Set</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>a7c077aa75492f533a3b2f3aee413eee1</anchor>
      <arglist>(const std::string parameter, const std::string value)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Set</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>ad57dad35f9495780f6950fc9c431faec</anchor>
      <arglist>(const std::string parameter, const double value)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Set</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>a440b765f6eb89e03f3c2c3dc499a754d</anchor>
      <arglist>(const std::string parameter, const Epetra_Vector &amp;value)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Set</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>a3ea1e7aacc40a8fabb2be4ea9561fc59</anchor>
      <arglist>(Trilinos_Util::CommandLineParser &amp;CLP)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>int_type *&amp;</type>
      <name>MyGlobalElementsPtr</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>ab817a147e355a2f9b724d98d89a55763</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>std::vector&lt; int_type &gt; &amp;</type>
      <name>MapMapRef</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>a905f39576f706a23d300cab19ce34538</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>long long *&amp;</type>
      <name>MyGlobalElementsPtr</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>a9ddf4bfedacb319cc42de57f8bca205e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>std::vector&lt; long long &gt; &amp;</type>
      <name>MapMapRef</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>ae0fb848eaebe82d2854b989b2af2a84b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>int *&amp;</type>
      <name>MyGlobalElementsPtr</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>a17f9e5fe45585eceef13b9a95a0cfdb8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>std::vector&lt; int &gt; &amp;</type>
      <name>MapMapRef</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>a958ce00b805d9ba1c434dbb9579c7786</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>CreateMap</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>a8f498d31e0f0187314241b1edf63d132</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>TCreateMap</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>a16988d929379d2c6cd433b676b68ec76</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>CreateMatrix</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>a98663e580b8a7f50471b29137a4e3f3a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>TCreateMatrix</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>a0caca69ca828cd7fd8cabbacf2adae34</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>TCreateExactSolution</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>ad01628bc582f563b4677fa479bfcbdf1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>CreateExactSolution</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>a55fdb7b37419904f541ad72ce009f115</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>CreateStartingSolution</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>a6d1eeb0d6e92c68bfc0820242c0b34f2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>TCreateRHS</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>aa2958212ce0ec374454bf102a24af4b3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>CreateRHS</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>ab0b889052fd8dd11887d7bc0777470ad</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>CreateEye</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>a8730e00a42d6f4120dd4ab4d7aaaf154</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>CreateMatrixDiag</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>adbf643888d7da6170b6e5402ab6cbff4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>CreateMatrixTriDiag</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>acda5af0151295bc0433302bada0a6287</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>CreateMatrixLaplace1d</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>a078ea2926820b77188d68a02b7fb833d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>CreateMatrixLaplace1dNeumann</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>acd5b9b87768f3b0e0cb1a1d7f735c0e0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>CreateMatrixCrossStencil2d</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>acda83282cd753cad71394365cfd879b0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>CreateMatrixCrossStencil2dVector</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>a5f9a2bc5138ffcf6e1cee15e5b247515</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>CreateMatrixLaplace2d</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>a483b5e02a9c48ca40155c78ade42abb6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>CreateMatrixLaplace2d_BC</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>a07f91f456ea12fa42b9f4cccfae7f71e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>CreateMatrixLaplace2d_9pt</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>a13ada40d5844f2125ea4ea5385d21704</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>CreateMatrixStretched2d</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>a72640adec23bf3c19ce53573d84eaf8c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>CreateMatrixRecirc2d</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>af3b0ad142a18266cbcba75a925e95fb2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>CreateMatrixRecirc2dDivFree</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>ab1453d1bb6d72b3a11957531930f1103</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>CreateMatrixLaplace2dNeumann</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>a22824a3db05f3fd32c0bec40b2338156</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>CreateMatrixUniFlow2d</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>ae3f185af84e05ff50c1999d400a9dbb3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>CreateMatrixLaplace3d</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>ad7795c09af7e4955472cdff35d76b42d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>CreateMatrixCrossStencil3d</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>afbb584c3e75872437180c973b08fae2f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>CreateMatrixCrossStencil3dVector</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>a8c62a7eae6bb1371d596af69a773e7ee</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>CreateMatrixLehmer</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>a4be3d63e61547a04545041df245fc9b4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>CreateMatrixMinij</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>ab35c9a04c26b0fc4783bc220b2929c22</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>CreateMatrixRis</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>a6c402bb0430323aa9192b57e4f47e595</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>CreateMatrixHilbert</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>a69621b695a447f697aac16182650c81c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>CreateMatrixJordblock</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>a6ea606ff6f17c4cb017a445ed2789ec6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>CreateMatrixCauchy</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>accfbbd18a241671ff9df2f6f7543d380</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>CreateMatrixFiedler</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>a86ddae3ba7dc39e6c56c20fa4f0d9f33</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>CreateMatrixHanowa</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>afb351b419a783e0de8c81897560812fc</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>CreateMatrixKMS</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>ab9352ffd066a1e5afe8f4235a83fe7c2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>CreateMatrixParter</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>af551686972085f71ee2f1e78f706b024</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>CreateMatrixPei</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>a0b112fc34c0c9bcb1a80ed9edd9544db</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>CreateMatrixOnes</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>afc9128a15df9dfd41b9643fb30fe6412</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>CreateMatrixVander</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>ae0e86160becaf821caa3850764ff0fbb</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>TReadMatrix</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>a30c0843e96e79fae72750b9ad76552f7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>GetNeighboursCartesian2d</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>ae308d4ce6bf8abd91a88cdac5aca872e</anchor>
      <arglist>(const int i, const int nx, const int ny, int &amp;left, int &amp;right, int &amp;lower, int &amp;upper)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>GetNeighboursCartesian3d</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>abb165f54d54679e42c94e784abc7ee25</anchor>
      <arglist>(const int i, const int nx, const int ny, const int nz, int &amp;left, int &amp;right, int &amp;lower, int &amp;upper, int &amp;below, int &amp;above)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>TGetCartesianCoordinates</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>a6a6881631ad986b1ea1f07605756dd8b</anchor>
      <arglist>(double *&amp;x, double *&amp;y, double *&amp;z)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>ZeroOutData</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>a7948fa29bb8b74c001e3cff46fb223fc</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>SetupCartesianGrid2D</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>a8dd606fbeb8cecdcd5b72d1bd37e9840</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>SetupCartesianGrid3D</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>a411c0aa5100a166a2885e0bfcd7a60c7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>ExactSolQuadXY</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>a7ee2b5621543d184b9f175639fa2c022</anchor>
      <arglist>(double x, double y, double &amp;u)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>ExactSolQuadXY</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>a53a619c66d8713f8d591135206ba9f42</anchor>
      <arglist>(double x, double y, double &amp;u, double &amp;ux, double &amp;uy, double &amp;uxx, double &amp;uyy)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>const Epetra_Comm *</type>
      <name>comm_</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>a31e8c48949b48fc9b502458aeb8cb727</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>Epetra_CrsMatrix *</type>
      <name>matrix_</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>a7976629a35ef38a1c5f622047a6bcd0f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>Epetra_MultiVector *</type>
      <name>ExactSolution_</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>a0a82589c8b8835dcca824ed1ab4728ab</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>Epetra_MultiVector *</type>
      <name>StartingSolution_</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>a3efd035acb459dacd0b1a2ec2f449d03</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>Epetra_MultiVector *</type>
      <name>rhs_</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>a1f76329a38aeefc3d5524331cd93fc72</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>Epetra_Map *</type>
      <name>map_</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>ae92d2abe19690a0fbabe33f6d1a7ad6b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>Epetra_LinearProblem *</type>
      <name>LinearProblem_</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>a6b8c7c4b49486649f346d7ee282a0521</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>std::string</type>
      <name>name_</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>ae0500fab7e59cc18393f5a4c6ee5f8aa</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>long long</type>
      <name>NumGlobalElements_</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>ab11c33ac1ded612bcf61d23a3746942a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>NumMyElements_</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>a71f9f2e2774572965150acb9a0cf1c6b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int *</type>
      <name>MyGlobalElements_int_</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>af67e749b6e2e8a63902f558050713c4e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>std::vector&lt; int &gt;</type>
      <name>MapMap_int_</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>af56f27775c6a4ff63de677c348ca49b5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>long long *</type>
      <name>MyGlobalElements_LL_</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>aa040ec3ae5a2f9484b64a84e2be7f6a6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>std::vector&lt; long long &gt;</type>
      <name>MapMap_LL_</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>a0639ea4bc9d0f7db63f7f0da78fb744b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>std::string</type>
      <name>MapType_</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>a4bd13f151ea31189350983b4cafb1a4c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>bool</type>
      <name>ContiguousMap_</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>a5dd6e7ce4cc0be6ca967de1100910c1c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>std::string</type>
      <name>ExactSolutionType_</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>adfdf58c6623c02c075c93e0be3d71208</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>std::string</type>
      <name>StartingSolutionType_</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>aea828b43edab51383c6b2d0e23018d88</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>std::string</type>
      <name>ExpandType_</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>acf02511df128615f17480edaeb05bb12</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>std::string</type>
      <name>RhsType_</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>a25303a8936cd614e3d1cd8a3594cfef8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>nx_</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>a4a5c195bdfbcf015e92b3341099e8d34</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>ny_</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>ae92f26e643fa13cdd08f31859edc1018</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>nz_</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>a0ba2686c45936328dc8dbcba09f4688c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>mx_</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>af8747578bd6a4dfaaf6ed1aee3831260</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>my_</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>ac2abfcadf171deb090ebe2b58c7920f1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>mz_</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>a66475431f405aedd12cbb9d9a1684af5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>double</type>
      <name>lx_</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>a8705d22b0ac09af4dd46e1d8e7c6fc92</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>double</type>
      <name>ly_</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>aabe302663e3d0eaffb742fd18b1bc184</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>double</type>
      <name>lz_</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>ac3e58834add01ea1d88647b332837eef</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>NumPDEEqns_</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>a1ec6deaa05be0e43dcee91fb9b819f28</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>NumVectors_</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>aaa044f2a625494382f7548f5e934f018</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>Epetra_Vector *</type>
      <name>VectorA_</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>a6b72ab753077ce1544532a005409c8f3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>Epetra_Vector *</type>
      <name>VectorB_</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>a28227c96cbe8b4116e1f76fac937f3a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>Epetra_Vector *</type>
      <name>VectorC_</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>af85f43291623b94a840ba7cdf0e7101a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>Epetra_Vector *</type>
      <name>VectorD_</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>ab2c7c6c8683b9d8468b9a22e437b64bf</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>Epetra_Vector *</type>
      <name>VectorE_</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>abfbfe4e6df5715b3f89830d19403f101</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>Epetra_Vector *</type>
      <name>VectorF_</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>a18768a08062d82cecddd41d98eaf6aeb</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>Epetra_Vector *</type>
      <name>VectorG_</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>a44ef2796e578ac5d3efb7db023c7bec9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>double</type>
      <name>a_</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>a6db3019990cc55ca33abf2eefa97c22b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>double</type>
      <name>b_</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>a38f3e495fb2e86346cb6bddd3fca0d9d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>double</type>
      <name>c_</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>a07c4326607a39b824d4b98b972ccb7e8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>double</type>
      <name>d_</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>a572c7f9d61aa3bc23ad439860bbabbf2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>double</type>
      <name>e_</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>aba594a79a2e9aee2b5a0cf0257be1818</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>double</type>
      <name>f_</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>a815bc2510a613ef6dd3c0d923273fcbf</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>double</type>
      <name>g_</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>a347d9238ce1e1948a6df969401bf2f53</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>double</type>
      <name>alpha_</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>a7fbac191fc09f7fd3b001b301612bb09</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>double</type>
      <name>beta_</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>a7a206555246472f39da833d8ea9c293e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>double</type>
      <name>gamma_</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>a8395804372542aa081fa6b5293b22c30</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>double</type>
      <name>delta_</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>adc893e255072f3ed9129684b804b2563</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>double</type>
      <name>conv_</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>a6bbbd09e69782dbacebc664cd958d5f5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>double</type>
      <name>diff_</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>afcfc273a12d804ca829eba5fccb53f78</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>double</type>
      <name>source_</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>a522ffbf58155da34ea5d009ebe983efc</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>double</type>
      <name>epsilon_</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>a933ac8bfecf7af81aec07594d90c70ef</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>std::string</type>
      <name>FileName_</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>ab5ebfc3d1261af18a058477a982737f3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>std::string</type>
      <name>ErrorMsg</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>a779bd9b8173277f170ffd8a4a98049af</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>std::string</type>
      <name>OutputMsg</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>a215bfff4aa7e889e95794428d93e52f7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>bool</type>
      <name>verbose_</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>ab15c555db4ba1fa21ed2e3fee2913a3e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>bool</type>
      <name>UseLongLong_</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>ad86eb61219bf6010620d82a73b037ea8</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>CrsMatrixGallery</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>a2aa2bbff00dffa50eaa073b3b466aba2</anchor>
      <arglist>(const std::string name, const Epetra_Comm &amp;comm, bool UseLongLong=false)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>CrsMatrixGallery</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>a66b5b285b1983c9a9e3ae22ec6ad5b7f</anchor>
      <arglist>(const std::string name, const Epetra_Map &amp;map)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~CrsMatrixGallery</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>a07b02e5e0d300f3838c8bc3a2dd28ec5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Set</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>a438b724bfac9dfd60c5cf2f79e376f07</anchor>
      <arglist>(const std::string parameter, const int value)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Set</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>a7c077aa75492f533a3b2f3aee413eee1</anchor>
      <arglist>(const std::string parameter, const std::string value)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Set</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>ad57dad35f9495780f6950fc9c431faec</anchor>
      <arglist>(const std::string parameter, const double value)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Set</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>a440b765f6eb89e03f3c2c3dc499a754d</anchor>
      <arglist>(const std::string parameter, const Epetra_Vector &amp;value)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Set</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>a3ea1e7aacc40a8fabb2be4ea9561fc59</anchor>
      <arglist>(Trilinos_Util::CommandLineParser &amp;CLP)</arglist>
    </member>
    <member kind="function">
      <type>Epetra_CrsMatrix *</type>
      <name>GetMatrix</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>a44b4507aefb2aa7468c5c1f20975e1c6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Epetra_CrsMatrix &amp;</type>
      <name>GetMatrixRef</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>af8f0bd111d6966951a19629af7c9ea4e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Epetra_MultiVector *</type>
      <name>GetExactSolution</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>a5d3c99f834c1f1f0eb52178507f81bf2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Epetra_MultiVector *</type>
      <name>GetStartingSolution</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>aea702ba51c59262aa8e3cee960cd374a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Epetra_MultiVector *</type>
      <name>GetRHS</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>ad5b3896e3cce6b4a3ccf69942ed16e39</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const Epetra_Map *</type>
      <name>GetMap</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>a0b328b686ff6474d3690288403324ba1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const Epetra_Map &amp;</type>
      <name>GetMapRef</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>a85e29cb725233c94e6b7c70384af349e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Epetra_LinearProblem *</type>
      <name>GetLinearProblem</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>a55b811feb3978a875f0499b55cd9cced</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>ComputeResidual</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>a7fe142a0014a49cb6b005fc08624a26a</anchor>
      <arglist>(double *residual)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>ComputeDiffBetweenStartingAndExactSolutions</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>af1e69071ceaba7061bc4de4df3a62606</anchor>
      <arglist>(double *residual)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>PrintMatrixAndVectors</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>a7984fb034b6247c05dbd8cb465fae78c</anchor>
      <arglist>(std::ostream &amp;os)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>PrintMatrixAndVectors</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>a286aa471ce8341748cf6a181f72d907c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>GetCartesianCoordinates</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>a6baf5c6cae0e77d097c575863b2dc4e2</anchor>
      <arglist>(double *&amp;x, double *&amp;y, double *&amp;z)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>WriteMatrix</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>ad925c72936a11ab209f8cd5ea4fb4689</anchor>
      <arglist>(const std::string &amp;FileName, const bool UseSparse=true)</arglist>
    </member>
    <member kind="friend">
      <type>friend std::ostream &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>a679039af5e2c1a6cc2cfca7f521b134f</anchor>
      <arglist>(std::ostream &amp;os, const Trilinos_Util::CrsMatrixGallery &amp;G)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>CreateMap</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>a8f498d31e0f0187314241b1edf63d132</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>TCreateMap</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>a16988d929379d2c6cd433b676b68ec76</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>CreateMatrix</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>a98663e580b8a7f50471b29137a4e3f3a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>TCreateMatrix</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>a0caca69ca828cd7fd8cabbacf2adae34</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>TCreateExactSolution</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>ad01628bc582f563b4677fa479bfcbdf1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>CreateExactSolution</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>a55fdb7b37419904f541ad72ce009f115</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>CreateStartingSolution</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>a6d1eeb0d6e92c68bfc0820242c0b34f2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>TCreateRHS</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>aa2958212ce0ec374454bf102a24af4b3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>CreateRHS</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>ab0b889052fd8dd11887d7bc0777470ad</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>CreateEye</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>a8730e00a42d6f4120dd4ab4d7aaaf154</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>CreateMatrixDiag</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>adbf643888d7da6170b6e5402ab6cbff4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>CreateMatrixTriDiag</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>acda5af0151295bc0433302bada0a6287</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>CreateMatrixLaplace1d</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>a078ea2926820b77188d68a02b7fb833d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>CreateMatrixLaplace1dNeumann</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>acd5b9b87768f3b0e0cb1a1d7f735c0e0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>CreateMatrixCrossStencil2d</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>acda83282cd753cad71394365cfd879b0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>CreateMatrixCrossStencil2dVector</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>a5f9a2bc5138ffcf6e1cee15e5b247515</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>CreateMatrixLaplace2d</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>a483b5e02a9c48ca40155c78ade42abb6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>CreateMatrixLaplace2d_BC</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>a07f91f456ea12fa42b9f4cccfae7f71e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>CreateMatrixLaplace2d_9pt</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>a13ada40d5844f2125ea4ea5385d21704</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>CreateMatrixStretched2d</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>a72640adec23bf3c19ce53573d84eaf8c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>CreateMatrixRecirc2d</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>af3b0ad142a18266cbcba75a925e95fb2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>CreateMatrixRecirc2dDivFree</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>ab1453d1bb6d72b3a11957531930f1103</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>CreateMatrixLaplace2dNeumann</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>a22824a3db05f3fd32c0bec40b2338156</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>CreateMatrixUniFlow2d</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>ae3f185af84e05ff50c1999d400a9dbb3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>CreateMatrixLaplace3d</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>ad7795c09af7e4955472cdff35d76b42d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>CreateMatrixCrossStencil3d</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>afbb584c3e75872437180c973b08fae2f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>CreateMatrixCrossStencil3dVector</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>a8c62a7eae6bb1371d596af69a773e7ee</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>CreateMatrixLehmer</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>a4be3d63e61547a04545041df245fc9b4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>CreateMatrixMinij</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>ab35c9a04c26b0fc4783bc220b2929c22</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>CreateMatrixRis</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>a6c402bb0430323aa9192b57e4f47e595</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>CreateMatrixHilbert</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>a69621b695a447f697aac16182650c81c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>CreateMatrixJordblock</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>a6ea606ff6f17c4cb017a445ed2789ec6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>CreateMatrixCauchy</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>accfbbd18a241671ff9df2f6f7543d380</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>CreateMatrixFiedler</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>a86ddae3ba7dc39e6c56c20fa4f0d9f33</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>CreateMatrixHanowa</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>afb351b419a783e0de8c81897560812fc</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>CreateMatrixKMS</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>ab9352ffd066a1e5afe8f4235a83fe7c2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>CreateMatrixParter</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>af551686972085f71ee2f1e78f706b024</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>CreateMatrixPei</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>a0b112fc34c0c9bcb1a80ed9edd9544db</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>CreateMatrixOnes</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>afc9128a15df9dfd41b9643fb30fe6412</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>CreateMatrixVander</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>ae0e86160becaf821caa3850764ff0fbb</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>TReadMatrix</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>a30c0843e96e79fae72750b9ad76552f7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>GetNeighboursCartesian2d</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>ae308d4ce6bf8abd91a88cdac5aca872e</anchor>
      <arglist>(const int i, const int nx, const int ny, int &amp;left, int &amp;right, int &amp;lower, int &amp;upper)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>GetNeighboursCartesian3d</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>abb165f54d54679e42c94e784abc7ee25</anchor>
      <arglist>(const int i, const int nx, const int ny, const int nz, int &amp;left, int &amp;right, int &amp;lower, int &amp;upper, int &amp;below, int &amp;above)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>TGetCartesianCoordinates</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>a6a6881631ad986b1ea1f07605756dd8b</anchor>
      <arglist>(double *&amp;x, double *&amp;y, double *&amp;z)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>ZeroOutData</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>a7948fa29bb8b74c001e3cff46fb223fc</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>SetupCartesianGrid2D</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>a8dd606fbeb8cecdcd5b72d1bd37e9840</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>SetupCartesianGrid3D</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>a411c0aa5100a166a2885e0bfcd7a60c7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>ExactSolQuadXY</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>a7ee2b5621543d184b9f175639fa2c022</anchor>
      <arglist>(double x, double y, double &amp;u)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>ExactSolQuadXY</name>
      <anchorfile>classTrilinos__Util_1_1CrsMatrixGallery.html</anchorfile>
      <anchor>a53a619c66d8713f8d591135206ba9f42</anchor>
      <arglist>(double x, double y, double &amp;u, double &amp;ux, double &amp;uy, double &amp;uxx, double &amp;uyy)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Trilinos_Util::InputFileReader</name>
    <filename>classTrilinos__Util_1_1InputFileReader.html</filename>
    <base>Trilinos_Util_Map</base>
    <member kind="function">
      <type></type>
      <name>InputFileReader</name>
      <anchorfile>classTrilinos__Util_1_1InputFileReader.html</anchorfile>
      <anchor>a3e929f3452e3c6aeb3e1f6e20b98ef58</anchor>
      <arglist>(const char FileName[])</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~InputFileReader</name>
      <anchorfile>classTrilinos__Util_1_1InputFileReader.html</anchorfile>
      <anchor>abf0ebd9b1f4b35d5e2c22d7255a9581b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual std::string</type>
      <name>GetFileName</name>
      <anchorfile>classTrilinos__Util_1_1InputFileReader.html</anchorfile>
      <anchor>ab34553b5ddfc83b880d7ac4fddcce67a</anchor>
      <arglist>(void) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>SetCommentChars</name>
      <anchorfile>classTrilinos__Util_1_1InputFileReader.html</anchorfile>
      <anchor>ab1253877f86a8d76374e7553e3d6c758</anchor>
      <arglist>(const std::string c)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>SetSeparationChars</name>
      <anchorfile>classTrilinos__Util_1_1InputFileReader.html</anchorfile>
      <anchor>a44f311a71fe27e241b4bf3a997b8593f</anchor>
      <arglist>(const std::string c)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>ReadFile</name>
      <anchorfile>classTrilinos__Util_1_1InputFileReader.html</anchorfile>
      <anchor>a9a4d2bcf6b1ee87f296db38713175837</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>ReadFile</name>
      <anchorfile>classTrilinos__Util_1_1InputFileReader.html</anchorfile>
      <anchor>a134e48308b2b5fa8a5e2a5b3f7b1f814</anchor>
      <arglist>(const char FileName[])</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>SPBLASMAT_STRUCT</name>
    <filename>structSPBLASMAT__STRUCT.html</filename>
    <member kind="variable">
      <type>int</type>
      <name>n</name>
      <anchorfile>structSPBLASMAT__STRUCT.html</anchorfile>
      <anchor>a367622c513a57db896b44581d79534d2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>double *</type>
      <name>val</name>
      <anchorfile>structSPBLASMAT__STRUCT.html</anchorfile>
      <anchor>afde869af1d4ecd62f580b51950d4b861</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int *</type>
      <name>indx</name>
      <anchorfile>structSPBLASMAT__STRUCT.html</anchorfile>
      <anchor>a6d6df26eeb9b698b4df0823714f9ea5e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int *</type>
      <name>bindx</name>
      <anchorfile>structSPBLASMAT__STRUCT.html</anchorfile>
      <anchor>abf948cd49b617b908ec1ba128751c3bf</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int *</type>
      <name>rpntr</name>
      <anchorfile>structSPBLASMAT__STRUCT.html</anchorfile>
      <anchor>a2c8734ce113bc7c490c1f32423e4be4a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int *</type>
      <name>cpntr</name>
      <anchorfile>structSPBLASMAT__STRUCT.html</anchorfile>
      <anchor>a0fef7c85f98d6a0940d02e31950baf16</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int *</type>
      <name>bpntrb</name>
      <anchorfile>structSPBLASMAT__STRUCT.html</anchorfile>
      <anchor>ada39b7519c7834afd177a8f244a657a6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int *</type>
      <name>bpntre</name>
      <anchorfile>structSPBLASMAT__STRUCT.html</anchorfile>
      <anchor>ac2db38934cf98f9896fc470caec2dd96</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>buffersize</name>
      <anchorfile>structSPBLASMAT__STRUCT.html</anchorfile>
      <anchor>aa736b158c4fcc910726d54fb0c8ada4c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>bufferstride</name>
      <anchorfile>structSPBLASMAT__STRUCT.html</anchorfile>
      <anchor>a93adf8c05fe5b5820901cb2dbc534e97</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>double *</type>
      <name>buffer</name>
      <anchorfile>structSPBLASMAT__STRUCT.html</anchorfile>
      <anchor>a5d9ce5be97c4206f8c00689e7659f9ea</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int *</type>
      <name>ncolvec</name>
      <anchorfile>structSPBLASMAT__STRUCT.html</anchorfile>
      <anchor>a9abc468844ad9dd64c50a8b1392da550</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>double</type>
      <name>nops_per_rhs</name>
      <anchorfile>structSPBLASMAT__STRUCT.html</anchorfile>
      <anchor>a3bf93cd4876c93608f303c5479a02164</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>minblocksize</name>
      <anchorfile>structSPBLASMAT__STRUCT.html</anchorfile>
      <anchor>af3e0d0a682cfa1627f4bad3e42685b90</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>maxblocksize</name>
      <anchorfile>structSPBLASMAT__STRUCT.html</anchorfile>
      <anchor>afb583be70da977b4201c62a33da81bc8</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Trilinos_Util_Map</name>
    <filename>classTrilinos__Util__Map.html</filename>
    <member kind="function">
      <type></type>
      <name>Trilinos_Util_Map</name>
      <anchorfile>classTrilinos__Util__Map.html</anchorfile>
      <anchor>a005b9703aaa77d78b5902cef80cf860d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~Trilinos_Util_Map</name>
      <anchorfile>classTrilinos__Util__Map.html</anchorfile>
      <anchor>ac7048c83b359a7736dd3857a5922254d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>Get</name>
      <anchorfile>classTrilinos__Util__Map.html</anchorfile>
      <anchor>a4bb876675e200aeb9f959a95b6367560</anchor>
      <arglist>(const std::string input, const int def_value)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual double</type>
      <name>Get</name>
      <anchorfile>classTrilinos__Util__Map.html</anchorfile>
      <anchor>a061670bb9ebe2e963cd8a46623b7a0e8</anchor>
      <arglist>(const std::string input, const double def_value)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual std::string</type>
      <name>Get</name>
      <anchorfile>classTrilinos__Util__Map.html</anchorfile>
      <anchor>a26619d38214b017d8ebb9f541ba0ef2a</anchor>
      <arglist>(const std::string input, const std::string def_value)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>Set</name>
      <anchorfile>classTrilinos__Util__Map.html</anchorfile>
      <anchor>ad7ae10de515461584e5b5179cba1b62f</anchor>
      <arglist>(const std::string input, const char *value)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>Set</name>
      <anchorfile>classTrilinos__Util__Map.html</anchorfile>
      <anchor>a6e0dcf9104cf003b2346061e2404cfc4</anchor>
      <arglist>(const std::string input, const std::string value)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>Set</name>
      <anchorfile>classTrilinos__Util__Map.html</anchorfile>
      <anchor>ab710d3082e997a6993a9fb9dd6bd2e90</anchor>
      <arglist>(const std::string input, const int value)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>Set</name>
      <anchorfile>classTrilinos__Util__Map.html</anchorfile>
      <anchor>a04335026d810d67da116f2657bf5459c</anchor>
      <arglist>(const std::string input, const double value)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>Add</name>
      <anchorfile>classTrilinos__Util__Map.html</anchorfile>
      <anchor>a69723feeeb63f4596e1f14dfe2e211f0</anchor>
      <arglist>(const std::string input, const std::string value)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>SetLabel</name>
      <anchorfile>classTrilinos__Util__Map.html</anchorfile>
      <anchor>aaa8e612e1285288aa756519da8233423</anchor>
      <arglist>(std::string Label)</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>GetLabel</name>
      <anchorfile>classTrilinos__Util__Map.html</anchorfile>
      <anchor>a03a723d303ade9c5de82025d7f948058</anchor>
      <arglist>(std::string Label)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>Has</name>
      <anchorfile>classTrilinos__Util__Map.html</anchorfile>
      <anchor>a4b5318330d9c578673f4f7b2acc3f621</anchor>
      <arglist>(const std::string input)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>ShowAll</name>
      <anchorfile>classTrilinos__Util__Map.html</anchorfile>
      <anchor>a588712153d0974347c583026b658e352</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>ShowReallyAll</name>
      <anchorfile>classTrilinos__Util__Map.html</anchorfile>
      <anchor>aff52d3f260643e7238c3aa6971839732</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>Reset</name>
      <anchorfile>classTrilinos__Util__Map.html</anchorfile>
      <anchor>a5f08315cdb185f84c6bd3cb017208b36</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="friend">
      <type>friend std::ostream &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>classTrilinos__Util__Map.html</anchorfile>
      <anchor>a4a5a375e2c17601a65fb1522cb66c0ad</anchor>
      <arglist>(std::ostream &amp;os, const Trilinos_Util_Map &amp;S)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>Get</name>
      <anchorfile>classTrilinos__Util__Map.html</anchorfile>
      <anchor>a4bb876675e200aeb9f959a95b6367560</anchor>
      <arglist>(const std::string input, const int def_value)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual double</type>
      <name>Get</name>
      <anchorfile>classTrilinos__Util__Map.html</anchorfile>
      <anchor>a061670bb9ebe2e963cd8a46623b7a0e8</anchor>
      <arglist>(const std::string input, const double def_value)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual std::string</type>
      <name>Get</name>
      <anchorfile>classTrilinos__Util__Map.html</anchorfile>
      <anchor>a26619d38214b017d8ebb9f541ba0ef2a</anchor>
      <arglist>(const std::string input, const std::string def_value)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>Set</name>
      <anchorfile>classTrilinos__Util__Map.html</anchorfile>
      <anchor>ad7ae10de515461584e5b5179cba1b62f</anchor>
      <arglist>(const std::string input, const char *value)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>Set</name>
      <anchorfile>classTrilinos__Util__Map.html</anchorfile>
      <anchor>a6e0dcf9104cf003b2346061e2404cfc4</anchor>
      <arglist>(const std::string input, const std::string value)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>Set</name>
      <anchorfile>classTrilinos__Util__Map.html</anchorfile>
      <anchor>ab710d3082e997a6993a9fb9dd6bd2e90</anchor>
      <arglist>(const std::string input, const int value)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>Set</name>
      <anchorfile>classTrilinos__Util__Map.html</anchorfile>
      <anchor>a04335026d810d67da116f2657bf5459c</anchor>
      <arglist>(const std::string input, const double value)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>Add</name>
      <anchorfile>classTrilinos__Util__Map.html</anchorfile>
      <anchor>a69723feeeb63f4596e1f14dfe2e211f0</anchor>
      <arglist>(const std::string input, const std::string value)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>SetLabel</name>
      <anchorfile>classTrilinos__Util__Map.html</anchorfile>
      <anchor>aaa8e612e1285288aa756519da8233423</anchor>
      <arglist>(std::string Label)</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>GetLabel</name>
      <anchorfile>classTrilinos__Util__Map.html</anchorfile>
      <anchor>a03a723d303ade9c5de82025d7f948058</anchor>
      <arglist>(std::string Label)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>Has</name>
      <anchorfile>classTrilinos__Util__Map.html</anchorfile>
      <anchor>a4b5318330d9c578673f4f7b2acc3f621</anchor>
      <arglist>(const std::string input)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>ShowAll</name>
      <anchorfile>classTrilinos__Util__Map.html</anchorfile>
      <anchor>a588712153d0974347c583026b658e352</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>ShowReallyAll</name>
      <anchorfile>classTrilinos__Util__Map.html</anchorfile>
      <anchor>aff52d3f260643e7238c3aa6971839732</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>Reset</name>
      <anchorfile>classTrilinos__Util__Map.html</anchorfile>
      <anchor>a5f08315cdb185f84c6bd3cb017208b36</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="friend">
      <type>friend std::ostream &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>classTrilinos__Util__Map.html</anchorfile>
      <anchor>a4a5a375e2c17601a65fb1522cb66c0ad</anchor>
      <arglist>(std::ostream &amp;os, const Trilinos_Util_Map &amp;S)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Trilinos_Util::VbrMatrixGallery</name>
    <filename>classTrilinos__Util_1_1VbrMatrixGallery.html</filename>
    <base>Trilinos_Util::CrsMatrixGallery</base>
    <member kind="function">
      <type></type>
      <name>VbrMatrixGallery</name>
      <anchorfile>classTrilinos__Util_1_1VbrMatrixGallery.html</anchorfile>
      <anchor>afe9cf3f0da81cb273a3538efb8a76c6c</anchor>
      <arglist>(const std::string name, const Epetra_Map &amp;map)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>VbrMatrixGallery</name>
      <anchorfile>classTrilinos__Util_1_1VbrMatrixGallery.html</anchorfile>
      <anchor>a778ed3cab3ef72f94a64704ff8bf5182</anchor>
      <arglist>(const std::string name, const Epetra_Comm &amp;Comm, bool UseLongLong=false)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~VbrMatrixGallery</name>
      <anchorfile>classTrilinos__Util_1_1VbrMatrixGallery.html</anchorfile>
      <anchor>aa95de0eaf15209381d9e387b7eaded9c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const Epetra_BlockMap *</type>
      <name>GetBlockMap</name>
      <anchorfile>classTrilinos__Util_1_1VbrMatrixGallery.html</anchorfile>
      <anchor>a897e8d37aee5d7b71676ed404f319631</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const Epetra_BlockMap &amp;</type>
      <name>GetBlockMapRef</name>
      <anchorfile>classTrilinos__Util_1_1VbrMatrixGallery.html</anchorfile>
      <anchor>a0ea88a261f4dda10008a80f9c0943f3a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Epetra_VbrMatrix *</type>
      <name>GetVbrMatrix</name>
      <anchorfile>classTrilinos__Util_1_1VbrMatrixGallery.html</anchorfile>
      <anchor>a78f608af7e93b71ebf65b07e264f5348</anchor>
      <arglist>(const int NumPDEEqns)</arglist>
    </member>
    <member kind="function">
      <type>Epetra_VbrMatrix *</type>
      <name>GetVbrMatrix</name>
      <anchorfile>classTrilinos__Util_1_1VbrMatrixGallery.html</anchorfile>
      <anchor>a0d156957ac4d97682e50ec3f68aae70f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Epetra_VbrMatrix &amp;</type>
      <name>GetVbrMatrixRef</name>
      <anchorfile>classTrilinos__Util_1_1VbrMatrixGallery.html</anchorfile>
      <anchor>afd8c8d72f4af08c2e07141131fad554f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Epetra_MultiVector *</type>
      <name>GetVbrRHS</name>
      <anchorfile>classTrilinos__Util_1_1VbrMatrixGallery.html</anchorfile>
      <anchor>a37ab8b4cce60e92293d157082f870a7c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Epetra_MultiVector *</type>
      <name>GetVbrExactSolution</name>
      <anchorfile>classTrilinos__Util_1_1VbrMatrixGallery.html</anchorfile>
      <anchor>aa08645b3b82fb4b4319be0bbeb41487f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Epetra_MultiVector *</type>
      <name>GetVbrStartingSolution</name>
      <anchorfile>classTrilinos__Util_1_1VbrMatrixGallery.html</anchorfile>
      <anchor>af066aa61785f254b4fcc6d483ce9c5c8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>CreateVbrMatrix</name>
      <anchorfile>classTrilinos__Util_1_1VbrMatrixGallery.html</anchorfile>
      <anchor>ab2a4745a2adb62ab1908d8ae758ea679</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>TCreateVbrMatrix</name>
      <anchorfile>classTrilinos__Util_1_1VbrMatrixGallery.html</anchorfile>
      <anchor>ab5d000bf7c7953525ff8d76ff7dec09a</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>Epetra_LinearProblem *</type>
      <name>GetVbrLinearProblem</name>
      <anchorfile>classTrilinos__Util_1_1VbrMatrixGallery.html</anchorfile>
      <anchor>a33f3949104986f33430523513f503e2f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>ComputeResidualVbr</name>
      <anchorfile>classTrilinos__Util_1_1VbrMatrixGallery.html</anchorfile>
      <anchor>a585bb61540e6795977920d013cb9d1c3</anchor>
      <arglist>(double *residual)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>ComputeDiffBetweenStartingAndExactSolutionsVbr</name>
      <anchorfile>classTrilinos__Util_1_1VbrMatrixGallery.html</anchorfile>
      <anchor>aee3db4708ca0ac678defbe1a76d399c9</anchor>
      <arglist>(double *residual)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>PrintVbrMatrixAndVectors</name>
      <anchorfile>classTrilinos__Util_1_1VbrMatrixGallery.html</anchorfile>
      <anchor>a070a31338f754cc277eaba7a6a0576ce</anchor>
      <arglist>(std::ostream &amp;os)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>PrintVbrMatrixAndVectors</name>
      <anchorfile>classTrilinos__Util_1_1VbrMatrixGallery.html</anchorfile>
      <anchor>a850d0441e977e93bc4e2fe81a87c624a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>CreateBlockMap</name>
      <anchorfile>classTrilinos__Util_1_1VbrMatrixGallery.html</anchorfile>
      <anchor>a3c81cd23b91417debb3bd7631cf41571</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>TCreateBlockMap</name>
      <anchorfile>classTrilinos__Util_1_1VbrMatrixGallery.html</anchorfile>
      <anchor>a14122d2e8f68bd354b802ba86c1f1e27</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>CreateVbrExactSolution</name>
      <anchorfile>classTrilinos__Util_1_1VbrMatrixGallery.html</anchorfile>
      <anchor>a7e3fa534862dce097fcdf3444ba00c3b</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>CreateVbrStartingSolution</name>
      <anchorfile>classTrilinos__Util_1_1VbrMatrixGallery.html</anchorfile>
      <anchor>a36b3d244a0877188e4e3206976ceb876</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>CreateVbrRHS</name>
      <anchorfile>classTrilinos__Util_1_1VbrMatrixGallery.html</anchorfile>
      <anchor>a7f1fd8de6525467aef47b4ed02be5f8e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>Epetra_VbrMatrix *</type>
      <name>VbrMatrix_</name>
      <anchorfile>classTrilinos__Util_1_1VbrMatrixGallery.html</anchorfile>
      <anchor>a8c8032fbf9bdd76c055d04b579cb279b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>Epetra_MultiVector *</type>
      <name>VbrExactSolution_</name>
      <anchorfile>classTrilinos__Util_1_1VbrMatrixGallery.html</anchorfile>
      <anchor>a545a2f5a146726a5c5fdee756fdb5f92</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>Epetra_MultiVector *</type>
      <name>VbrStartingSolution_</name>
      <anchorfile>classTrilinos__Util_1_1VbrMatrixGallery.html</anchorfile>
      <anchor>ab0b6c420ffab686863d6b844579b55f8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>Epetra_MultiVector *</type>
      <name>VbrRhs_</name>
      <anchorfile>classTrilinos__Util_1_1VbrMatrixGallery.html</anchorfile>
      <anchor>acfb89a843149b6fa2948b5897b6652c9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>Epetra_BlockMap *</type>
      <name>BlockMap_</name>
      <anchorfile>classTrilinos__Util_1_1VbrMatrixGallery.html</anchorfile>
      <anchor>a85aa3365ec24af8f8d2bf9c30b9a3a15</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>MaxBlkSize_</name>
      <anchorfile>classTrilinos__Util_1_1VbrMatrixGallery.html</anchorfile>
      <anchor>a431bbd5d68b7489634e9db4cf7c9f693</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>Epetra_LinearProblem *</type>
      <name>VbrLinearProblem_</name>
      <anchorfile>classTrilinos__Util_1_1VbrMatrixGallery.html</anchorfile>
      <anchor>a594bf83abcdad8f59c27c1fb86c211d7</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="namespace">
    <name>Trilinos_Util</name>
    <filename>namespaceTrilinos__Util.html</filename>
    <class kind="class">Trilinos_Util::CommandLineParser</class>
    <class kind="class">Trilinos_Util::CrsMatrixGallery</class>
    <class kind="class">Trilinos_Util::InputFileReader</class>
    <class kind="class">Trilinos_Util::VbrMatrixGallery</class>
    <member kind="function">
      <type>ostream &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>namespaceTrilinos__Util.html</anchorfile>
      <anchor>abf4c512ffd883d27e3ed3d626673842c</anchor>
      <arglist>(ostream &amp;os, const Trilinos_Util::CrsMatrixGallery &amp;G)</arglist>
    </member>
  </compound>
</tagfile>
