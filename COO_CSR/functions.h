
#ifndef functions_h
#define functions_h

#include <stdio.h>

void spmv_coo(int *row, int *col, double *value, int matsize, double *vec, double *coo_res);
void coo_csr(int* rowoff, int* row, int size);
void spmv_csr(int *col, double *value, int rownum, double *vec, double *crs_res, int *rowoffsets);

#endif /* functions_h */
