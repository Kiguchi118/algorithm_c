/* 外部ハッシュ法のプログラム */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define W 10 /* W = 文字列の最大長さ，ここでは 10 に設定 */
#define m 97 /* m = ハッシュ表のサイズ，ここでは 97 に設定 */
#define n 50 /* n = 扱う文字列の最大数，ここでは 50 に設定 */

struct cell {
  char key[W + 1];
  int next;
};

int hash_val(char *a);
int allocate_object(struct cell *L, int *f);
int chained_hash_search(int *A, struct cell *L, char *a);
void free_object(struct cell *L, int *f, int x);
void chained_hash_insert(int *A, struct cell *L, int x);
void chained_hash_delete(int *A, struct cell *L, int x);

int main(void) {
  struct cell List[n];
  int A[m]; /* ハッシュ表を表す配列 */
  int N;
  int freeL; /* 空きアドレスのリストの先頭*/
  int i, h;
  char word[W + 1];
  int x, y, count;
  char fname[128];
  FILE *fp;

  for (i = 0; i < n - 1; i++) {
    List[i].next = i + 1;
  }
  List[n - 1].next = -1;
  freeL = 0;

  for (h = 0; h < m; h++) {
    A[h] = -1;
  }

  printf("input filename: ");
  fgets(fname, sizeof(fname), stdin);
  fname[strlen(fname) - 1] = '\0';
  fflush(stdin);

  fp = fopen(fname, "r");
  fscanf(fp, "%d", &N);
  if (N > n) {
    printf("N is too large, setting N = %d\n", n);
    N = n;
  }

  for (i = 0; i < N; i++) {
    fscanf(fp, "%s", word);
    y = chained_hash_search(A, List, word);
    if (y == -1) {
      x = allocate_object(List, &freeL);
      strcpy(List[x].key, word);
      chained_hash_insert(A, List, x);
    }
  }
  fclose(fp);
  printf("【Insert】\n");
  for (h = 0; h < m; h++) {
    i = A[h];
    count = 0;
    if (i != -1) {
      while (i != -1) {
        count++;
        i = List[i].next;
      }
      printf("A[%d]: %d\n", h, count);
    }
  }

  fp = fopen(fname, "r");
  fscanf(fp, "%d", &N);
  if (N > n) {
    N = n;
  }
  for (i = 0; i < N; i++) {
    fscanf(fp, "%s", word);
    x = chained_hash_search(A, List, word);
    if (x != -1) {
      chained_hash_delete(A, List, x);
      free_object(List, &freeL, x);
    }
  }
  fclose(fp);
  printf("【Delete】\n");
  for (h = 0; h < m; h++) {
    i = A[h];
    count = 0;
    if (i != -1) {
      while (i != -1) {
        count++;
        i = List[i].next;
      }
      printf("A[%d]: %d\n", h, count);
    }
  }
  return 0;
}

int allocate_object(struct cell *L, int *f) {
  int x;
  if (*f == -1) {
    printf("error: out of space\n");
    x = -1;
  } else {
    x = *f;
    *f = L[*f].next;
  }
  return x;
}

void free_object(struct cell *L, int *f, int x) {
  L[x].next = *f;
  *f = x;
}

int chained_hash_search(int *A, struct cell *L, char *a) {
  int x;

  x = A[hash_val(a)];
  while (x != -1 && strcmp(L[x].key, a) != 0) {
    x = L[x].next;
  }
  return x;
}

void chained_hash_insert(int *A, struct cell *L, int x) {
  int h;

  h = hash_val(L[x].key);
  L[x].next = A[h];
  A[h] = x;
}

void chained_hash_delete(int *A, struct cell *L, int x) {
  int z, y;

  z = -1;
  y = A[hash_val(L[x].key)];

  while (y != x) {
    z = y;
    y = L[y].next;
  }
  if (z != -1) {
    L[z].next = L[x].next;
  } else {
    A[hash_val(L[x].key)] = L[x].next;
  }
}

int hash_val(char *a) {
  int h, i;
  h = 0;
  i = 0;
  while (a[i] != 0 && i < W) {
    h = h + (int)a[i];
    i++;
  }
  h = h % m;
  return h;
}
