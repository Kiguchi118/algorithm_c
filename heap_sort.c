#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int parent(int i);
int left(int i);
int right(int i);
void heap_sort(int *A, int n);
void upheap_sort(int *A, int i);
void downheap_sort(int *A, int n);
void build_heap(int *A, int n);
void increase_key(int *A, int i, int a);

int main(void) {
  int Data[50];
  int N;
  int i, a;
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
    printf("%d ", Data[i]);
  }
  printf("\n");

  heap_sort(Data, N);

  printf("ソートが完了しました.\n");
  for (i = 0; i < N; i++) {
    printf("%d ", Data[i]);
  }
  printf("\n");
  return 0;
}

int parent(int i) { return (i - 1) / 2; }

int left(int i) { return (2 * i + 1); }

int right(int i) { return (2 * i + 2); }

void heap_sort(int *A, int n) {
  int i, a, tmp, change;

  build_heap(A, n);
  printf(" build_heap しました.\n");
  for (i = 0; i < n; i++) {
    printf("%d[%d] ", A[i], i);
  }

  printf(
      "\n頂点 i を指定し, H[i]の値を a に変更できます. 変更しますか？\nはい：1 "
      "いいえ：0\n");
  scanf("%d", &change);
  while (change != 0 && change != 1) {
    printf(" 1(はい) か 0(いいえ)を入力してください.\n");
    scanf("%d", &change);
  }

  while (change == 1) {
    printf("頂点 i : ");
    scanf("%d", &i);
    while (i > n - 1 || i < 0) {
      printf("正しい頂点 i を入力してください.\n");
      printf("頂点 i : ");
      scanf("%d", &i);
    }
    printf(" a (a は %d 以上) : ", A[i]);
    scanf("%d", &a);
    while (a < A[i]) {
      printf(" a を %d 以上にしてください.\n", A[i]);
      printf(" a : ");
      scanf("%d", &a);
    }

    increase_key(A, i, a);

    printf("他に変更したい箇所はありますか？\nはい：1 いいえ：0\n");
    scanf("%d", &change);
    while (change != 0 && change != 1) {
      printf(" 1(はい) か 0(いいえ)を入力してください.\n");
      scanf("%d", &change);
    }
  }

  printf("\n");
  for (i = 1; i < n; i++) {
    tmp = A[n - i];
    A[n - i] = A[0];
    A[0] = tmp;
    downheap_sort(A, n - i - 1);
  }
}

void upheap_sort(int *A, int i) {
  int u = i;
  int tmp;

  while (u > 0 && A[parent(u)] < A[u]) {
    tmp = A[u];
    A[u] = A[parent(u)];
    A[parent(u)] = tmp;
    u = parent(u);
  }
}

void downheap_sort(int *A, int i) {
  int u = 0;
  int l, r, tmp;

  while (1) {
    if (left(u) <= i) {
      l = left(u);
    } else {
      l = u;
    }
    if (right(u) <= i) {
      r = right(u);
    } else {
      r = u;
    }
    if (A[l] > A[u] || A[r] > A[u]) {
      if (A[l] < A[r]) {
        tmp = A[u];
        A[u] = A[r];
        A[r] = tmp;
        u = r;
      } else {
        tmp = A[u];
        A[u] = A[l];
        A[l] = tmp;
        u = l;
      }
    } else {
      break;
    }
  }
}

void build_heap(int *A, int n) {
  for (int i = 1; i < n; i++) {
    upheap_sort(A, i);
  }
}

void increase_key(int *A, int i, int a) {
  A[i] = a;
  upheap_sort(A, i);
}
