/* ２分ヒープによる Dijkstra 法 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define maxN 50
#define inf 1000000

struct cell {
  int key;
  int vertex;
};

int parent(int i);
int left(int i);
int right(int i);
void insert(struct cell *H, int *adr, int hsize, int a, int v);
void decrease_key(struct cell *H, int *adr, int i, int a);
int delete_min(struct cell *H, int *adr, int hsize);
void upheap_sort(struct cell *H, int *adr, int i);
void downheap_sort(struct cell *H, int *adr, int n);

int main(void) {
  int N, M;               /* 頂点数，辺数 */
  int len;                /* 辺の長さ */
  int Lmat[maxN][maxN];   /* 重み行列を表す変数 */
  struct cell Heap[maxN]; /* ヒープに用いる配列の宣言 */
  int adr[maxN]; /* ヒープに含まれる頂点のアドレスの配列 */
  int d[maxN], p[maxN]; /* d[u], p[u] を格納する変数 */
  int hsize;            /* ヒープに格納された頂点の数 */
  int v0;               /* 始点を表す変数 */
  int i, u, w, v;
  char fname[128];
  FILE *fp;

  printf("input filename: ");
  fgets(fname, sizeof(fname), stdin);
  fname[strlen(fname) - 1] = '\0';
  fflush(stdin);

  fp = fopen(fname, "r");
  fscanf(fp, "%d %d", &N, &M);
  if (N > 50) {
    printf("N is too large, setting N = 50\n");
    N = 50;
  }
  for (u = 0; u < N; u++) {
    for (v = 0; v < N; v++) {
      Lmat[u][v] = inf;
    }
  }
  for (i = 0; i < M; i++) {
    fscanf(fp, " %d %d %d", &u, &v, &len);
    Lmat[u][v] = Lmat[v][u] = len;
  }
  fscanf(fp, "%d", &v0);
  fclose(fp);

  for (u = 0; u < N; u++) {
    d[u] = inf;
    p[u] = -1;
    adr[u] = -1;
  }

  d[v0] = 0;
  p[v0] = -1;
  hsize = 1;
  insert(Heap, adr, hsize, d[v0], v0);

  while (hsize) {
    v = delete_min(Heap, adr, hsize);
    hsize--;
    for (w = 0; w < N; w++) {
      if (Lmat[v][w] != inf) {
        if (d[w] == inf) {
          d[w] = d[v] + Lmat[v][w];
          p[w] = v;
          hsize++;
          insert(Heap, adr, hsize, d[w], w);
        } else if (d[w] > d[v] + Lmat[v][w]) {
          d[w] = d[v] + Lmat[v][w];
          p[w] = v;
          decrease_key(Heap, adr, adr[w], d[w]);
        }
      }
    }
  }
  for (u = 0; u < N; u++) {
    printf("vertex %d: d[%d] = %d, p[%d] = %d\n", u, u, d[u], u, p[u]);
  }
}

int parent(int i) { return (i - 1) / 2; }

int left(int i) { return 2 * i + 1; }

int right(int i) { return 2 * i + 2; }

void insert(struct cell *H, int *adr, int hsize, int a, int v) {
  H[hsize - 1].key = a;
  H[hsize - 1].vertex = v;
  adr[v] = hsize - 1;
  upheap_sort(H, adr, hsize - 1);
}

void decrease_key(struct cell *H, int *adr, int i, int a) {
  H[i].key = a;
  upheap_sort(H, adr, i);
}

int delete_min(struct cell *H, int *adr, int hsize) {
  int v = H[0].vertex;
  adr[v] = -1;
  if (hsize > 1) {
    H[0].key = H[hsize - 1].key;
    H[0].vertex = H[hsize - 1].vertex;
    adr[H[0].vertex] = 0;
    downheap_sort(H, adr, hsize - 2);
  }
  return v;
}

void downheap_sort(struct cell *H, int *adr, int i) {
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
    if (H[l].key < H[u].key || H[r].key < H[u].key) {
      if (H[l].key > H[r].key) {
        tmp = H[u].key;
        H[u].key = H[r].key;
        H[r].key = tmp;

        tmp = H[u].vertex;
        H[u].vertex = H[r].vertex;
        H[r].vertex = tmp;

        tmp = adr[H[u].vertex];
        adr[H[u].vertex] = adr[H[r].vertex];
        adr[H[r].vertex] = tmp;
        u = r;
      } else {
        tmp = H[u].key;
        H[u].key = H[l].key;
        H[l].key = tmp;

        tmp = H[u].vertex;
        H[u].vertex = H[l].vertex;
        H[l].vertex = tmp;

        tmp = adr[H[u].vertex];
        adr[H[u].vertex] = adr[H[l].vertex];
        adr[H[l].vertex] = tmp;
        u = l;
      }
    } else {
      break;
    }
  }
}

void upheap_sort(struct cell *H, int *adr, int i) {
  int u = i;
  int tmp;

  while (u > 0 && H[parent(u)].key > H[u].key) {
    tmp = H[u].key;
    H[u].key = H[parent(u)].key;
    H[parent(u)].key = tmp;

    tmp = H[u].vertex;
    H[u].vertex = H[parent(u)].vertex;
    H[parent(u)].vertex = tmp;

    tmp = adr[H[u].vertex];
    adr[H[u].vertex] = adr[H[parent(u)].vertex];
    adr[H[parent(u)].vertex] = tmp;

    u = parent(u);
  }
}
