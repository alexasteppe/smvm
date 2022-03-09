#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include "quicksort.h"
#include "mmio.h"
#include "functions.h"


int main(int argc, const char * argv[]) {
    
    FILE *f = NULL;
    MM_typecode matcode;
    int ret_code;
    int vector, outputsize, rownum, colnum, rowoffsize, *rowoffsets;
    int *row, *col;
    double *value, *crs_res, *coo_res, *vec;
    int matsize;
    clock_t timer_coo, timer_csr;
    
    if (argc < 2) {
        fprintf(stderr, "Usage: %s [martix-market-filename]\n", argv[0]);
        exit(1);
    } else {
        if ((f = fopen(argv[1], "r")) == NULL) exit(1);
    }

    if (mm_read_banner(f, &matcode) != 0) {
        printf("Could not process Matrix Market banner.\n");
        exit(1);
    }

    if (mm_is_complex(matcode) && mm_is_matrix(matcode) &&
        mm_is_sparse(matcode)) {
        printf("Sorry, this application does not support ");
        printf("Market Market type: [%s]\n", mm_typecode_to_str(matcode));
        exit(1);   
    }

    if ((ret_code = mm_read_mtx_crd_size(f, &rownum, &colnum, &matsize)) != 0)
        exit(1);
    
    
    row = (int *)malloc(matsize * sizeof(int));
    assert(row != NULL);
    col = (int *)malloc(matsize * sizeof(int));
    assert(col != NULL);
    value = (double *)malloc(matsize * sizeof(double));
    assert(value != NULL);
    vector = rownum * sizeof(double);
    vec = (double*)malloc(vector);
    assert(vec != NULL);
    rowoffsize = (rownum + 1) * sizeof(int);
    rowoffsets = (int*)malloc(rowoffsize);
    assert(rowoffsets != NULL);
    outputsize = rownum * sizeof(double);
    coo_res = (double*)malloc(outputsize);
    assert(coo_res != NULL);
    crs_res = (double*)malloc(outputsize);
    assert(crs_res != NULL);
    
    
    for (int i = 0; i < matsize; i++) {
        fscanf(f, "%d %d %lg", &row[i], &col[i], &value[i]);
    }
    fclose(f);
    
    srand((int)time(NULL));
    for (int i = 0; i < rownum; i++) {
        vec[i] = rand() / (double)RAND_MAX;
    }
   
    timer_coo = clock();
    spmv_coo(row, col, value, matsize, vec, coo_res);
    timer_coo = clock() - timer_coo;

    /*
 
    for (int i = 0; i < rownum; i++) {
        printf("Result vector element %d = %lf\n\n", i, coo_res[i]);
    }
    */

    double total_coo = (((double)timer_coo)/CLOCKS_PER_SEC);
    printf("# Elapsed time coo (sec): %.6f\n\n", total_coo);
    
    quickSort(row, col, value, 0, matsize - 1);
    coo_csr(rowoffsets, row, matsize);
    
    timer_csr = clock();
    spmv_csr(col, value, rownum, vec, crs_res, rowoffsets);
    timer_csr = clock() - timer_csr;

    /*
    for (int i = 0; i < rownum; i++) {
        printf("Result vector element %d = %lf\n\n", i, crs_res[i]);
    }
    */
    double total_csr = (((double)timer_csr)/CLOCKS_PER_SEC);
    printf("# Elapsed time csr (sec): %.6f\n\n", total_csr);
    
     
    free(col);
    free(row);
    free(value);
    free(vec);
    free(rowoffsets);
    free(crs_res);
    free(coo_res);
    return 0;
    }

