/* bucket_sort のプログラム */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct cell {
  int key;
  int next;
};

void bucket_sort(int *A, int n, int l, int u, int m);
void insertion_sort(int *A, int n, int m);

int main(void) {
  int Data[50];
  int N, l, u, m;
  int i, j;
  int E, n;
  char fname[128];
  FILE *fp;

  printf("input filename: ");
  fgets(fname, sizeof(fname), stdin);
  fname[strlen(fname) - 1] = '\0';
  fflush(stdin);

  fp = fopen(fname, "r");
  fscanf(fp, "%d %d %d %d", &N, &l, &u, &m);
  if (N > 50) {
    printf("N is too large, setting N = 50\n");
    N = 50;
  }
  printf("RANGE: (%d,%d)\n", l, u);

  n = 0;
  for (i = 0; i < N; i++) {
    fscanf(fp, "%d", &E);
    if (E < l || E > u) {
      printf("ERROR: %d\n", E);
    } else {
      Data[n] = E;
      n++;
    }
  }
  fclose(fp);

  N = n;
  for (i = 0; i < N; i++) {
    printf("Data[%d]: %d\n", i, Data[i]);
  }

  for (i = 0; i < N; i++) {
    printf("%d ", Data[i]);
  }
  printf("\n");

  bucket_sort(Data, N, l, u, m);

  printf("[Bucket-Sort]\n");
  for (i = 0; i < N; i++) {
    printf("Data[%d]: %d\n", i, Data[i]);
  }
  for (i = 0; i < N; i++) {
    printf("%d ", Data[i]);
  }
  printf("\n");
  return 0;
}

void bucket_sort(int *A, int n, int l, int u, int m) {
  struct cell List[50];
  int B[50];
  int i, j, t, d;

  for (i = 0; i < n; i++) {
    List[i].key = A[i];
    List[i].next = -1;
  }
  for (j = 0; j < m; j++) {
    B[j] = -1;
  }
  for (i = 0; i < n; i++) {
    j = (A[i] * m) / (u - l);
    if (B[j] == -1) {
      B[j] = i;
    } else {
      List[i].next = B[j];
      B[j] = i;
    }
  }
  t = d = 0;
  for (j = 0; j < m; j++) {
    i = B[j];
    while (i != -1) {
      A[t] = List[i].key;
      i = List[i].next;
      t++;
    }
    if (t - d > 1) {
      insertion_sort(A, t, d);
    }
    d = t;
  }
}

void insertion_sort(int *A, int n, int m) {
  int a, i, j;

  for (i = m + 1; i < n; i++) {
    a = A[i];
    j = i - 1;
    while (j >= 0 && A[j] > a) {
      A[j + 1] = A[j];
      j = j - 1;
      A[j + 1] = a;
    }
  }
}
