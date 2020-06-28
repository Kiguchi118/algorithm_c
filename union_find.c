/* ユニオン・ファインドを用いた無向グラフの連結成分分解 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define maxN 50
#define maxM 500

struct edge_data {
  int end1;
  int end2;
};

void make_set(int *p, int *rank, int x);    /* make_set 関数を宣言 */
int find_set(int *p, int x);                /* find_set 関数を宣言 */
void link(int *p, int *rank, int x, int y); /* link 関数を宣言 */

int main(void) {
  int N, M;                    /* 頂点数，辺数 */
  struct edge_data edge[maxM]; /* 辺データを表す変数 */
  int p[maxN], rank[maxN];     /* p[x], rank[x] を格納する変数 */
  int component[maxN]; /* 連結成分番号 component[u] を格納する変数 */
  int number_comp;     /* 連結成分数を表す変数 */
  int u, v;            /* 頂点番号，重みを表す変数 */
  int i;
  char fname[128];
  FILE *fp;

  printf("input filename: ");
  fgets(fname, sizeof(fname), stdin);
  fname[strlen(fname) - 1] = '\0';
  fflush(stdin);

  fp = fopen(fname, "r");
  fscanf(fp, "%d %d", &N, &M);
  for (i = 0; i < M; i++) {
    fscanf(fp, " %d %d", &u, &v);
    edge[i].end1 = u;
    edge[i].end2 = v;
  }
  fclose(fp);

  for (u = 0; u < N; u++) {
    make_set(p, rank, u);
    component[u] = 0;
  }
  for (i = 0; i < M; i++) {
    u = find_set(p, edge[i].end1);
    v = find_set(p, edge[i].end2);
    if (u != v) {
      link(p, rank, u, v);
    }
  }
  number_comp = 0;
  for (u = 0; u < N; u++) {
    v = u;
    while (v != p[v]) {
      v = p[v];
    }
    if (component[v] == 0) {
      number_comp++;
      component[v] = number_comp;
    }
    component[u] = component[v];
  }

  printf("number of components = %d\n", number_comp);
  for (i = 0; i < N; i++) {
    printf("vertex%d component=%d parent=%d rank=%d\n", i, component[i], p[i],
           rank[i]);
  }

  return 0;
}

void make_set(int *p, int *rank, int x) {
  p[x] = x;
  rank[x] = 0;
}

int find_set(int *p, int x) {
  int y = x;
  int z, r;
  while (y != p[y]) {
    y = p[y];
  }
  r = y;
  y = x;
  while (y != r) {
    z = p[y];
    p[y] = r;
    y = z;
  }
  return r;
}

void link(int *p, int *rank, int x, int y) {
  if (rank[x] > rank[y]) {
    p[y] = x;
  } else {
    p[x] = y;
    if (rank[x] == rank[y]) {
      rank[y]++;
    }
  }
}
