/* 深さ優先探索：隣接行列と再帰による */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define maxN 50
#define inf 1000000
#define WHITE 0
#define GRAY 1
#define BLACK 2

void traverse(int v);

int N, M;                                   /* 頂点数，辺数 */
int Adj[maxN + 1][maxN + 1];                /* 隣接行列を表す変数 */
int d[maxN], f[maxN], p[maxN], color[maxN]; /* 配列変数 d, f, p, color */
int T;                                      /* time を表す変数 T*/

int main(void) {
  int i, u, v;
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
      Adj[u][v] = 0;
    }
  }
  for (i = 0; i < M; i++) {
    fscanf(fp, " %d %d", &u, &v);
    Adj[u][v] = Adj[v][u] = 1;
  }
  fclose(fp);

  for (v = 0; v < N; v++) {
    color[v] = WHITE;
    d[v] = f[v] = inf;
    p[v] = -1;
  }
  T = 0;
  for (v = 0; v < N; v++) {
    if (color[v] == WHITE) {
      traverse(v);
    }
  }
  for (u = 0; u < N; u++) {
    printf("vertex %d: d[%d] = %d, f[%d] = %d, p[%d] = %d\n", u, u, d[u], u,
           f[u], u, p[u]);
  }
}

void traverse(int v) {
  int u;

  color[v] = GRAY;
  T++;
  d[v] = T;
  for (u = 0; u < N; u++) {
    if (Adj[v][u] == 1) {
      if (color[u] == WHITE) {
        p[u] = v;
        traverse(u);
      }
    }
  }
  color[v] = BLACK;
  T++;
  f[v] = T;
}
