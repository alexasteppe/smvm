
#include "quicksort.h"

void swap(int* a, int* b)
{
  int t = *a;
  *a = *b;
  *b = t;
}
void swap_val(double* a, double* b)
{
  double t = *a;
  *a = *b;
  *b = t;
}

void quickSort(int *row, int *col, double *value, int left, int right)
{
  int i = left, j = right;
  int pivot = row[(left + right) / 2];
  int pivot_col = col[(left + right) / 2];

  while(i <= j) {
    while(row[i] < pivot || (row[i] == pivot && col[i] < pivot_col))
      i++;
    while(row[j] > pivot || (row[j] == pivot && col[j] > pivot_col))
      j--;
    if(i <= j) {
      swap(&row[i], &row[j]);
      swap(&col[i], &col[j]);
      swap_val(&value[i], &value[j]);
      i++;
      j--;
    }
  }
  if(left < j)
    quickSort(row, col, value, left, j);
  if (i < right)
    quickSort(row, col, value, i, right);
}
