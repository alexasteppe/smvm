
#include "functions.h"

void coo_csr(int* rowoff, int* row, int size){
    
    rowoff[0] = 0;
    int prev = 0, accurate = 1, j = 1;

    for (int i = 1; i < size; i++) {
        if (row[i] - row[prev] > 1) {
            for (int k = 0; k < row[i] - row[prev]; k++) {
                rowoff[j++] = accurate;
            }
            prev = i;
        } else if (row[prev] != row[i]) {
            rowoff[j++] = accurate;
            prev = i;
        }
        accurate+=1;
        rowoff[j] = accurate;
        
    }
}

void spmv_coo(int *row, int *col, double *value, int matsize, double *vec, double *coo_res) {
    
    for (int j = 0; j < matsize; j++) {
        coo_res[row[j]] += value[j] * vec[col[j]];
    }
}

void spmv_csr(int *col, double *value, int rownum, double *vec, double *crs_res, int *rowoffsets) {
    
    double temp;
    for (int i = 0; i < rownum; i++) {
        temp = crs_res[i];
        for (int j = rowoffsets[i]; j < rowoffsets[i+1]; j++) {
            temp += value[j] * vec[col[j]];
        }
        crs_res[i] = temp;
    }
}


