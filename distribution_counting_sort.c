#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void quicksort(int *A, int p, int r);
int partition(int *A, int p, int r);

int main(void) {
  int Data[50];
  int N;
  int i;
  char fname[128];
  FILE *fp;

  printf("input filename: ");
  fgets(fname, sizeof(fname), stdin);
  fname[strlen(fname) - 1] = '\0';
  fflush(stdin);

  fp = fopen(fname, "r");
  fscanf(fp, "%d", &N);
  if (N > 50) {
    printf("N is too large, setting N = 50\n");
    N = 50;
  }
  for (i = 0; i < N; i++) {
    fscanf(fp, "%d", &Data[i]);
  }
  fclose(fp);
  for (i = 0; i < N; i++) {
    printf("Data[%d]: %d\n", i, Data[i]);
  }
  for (i = 0; i < N; i++) {
    printf("%d ", Data[i]);
  }
  printf("\n");

  quicksort(Data, 0, N - 1);

  printf("[quicksort]\n");
  for (i = 0; i < N; i++) {
    printf("Data[%d]: %d\n", i, Data[i]);
  }
  for (i = 0; i < N; i++) {
    printf("%d ", Data[i]);
  }
  printf("\n");
}

void quicksort(int *A, int p, int r) {
  int q;

  if (p < r) {
    q = partition(A, p, r);
    quicksort(A, p, q);
    quicksort(A, q + 1, r);
  }
}

int partition(int *A, int p, int r) {
  int x, i, j, tmp, q;

  x = A[p];
  i = p;
  j = r;
  while (i < j) {
    while (A[j] > x) {
      j--;
    }
    while (A[i] < x) {
      i++;
    }
    if (i < j) {
      tmp = A[i];
      A[i] = A[j];
      A[j] = tmp;
      j--;
      i++;
    }
    if (i == j && A[j] > x) {
      j--;
    }
  }
  q = j;
  return q;
}
