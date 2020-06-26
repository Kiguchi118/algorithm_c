/* 幅優先探索：隣接行列による */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define maxN 50
#define inf 1000000
#define WHITE 0
#define GRAY 1
#define BLACK 2

int main(void) {
  int N, M;                          /* 頂点数，辺数 */
  int Adj[maxN][maxN];               /* 隣接行列を表す変数 */
  int d[maxN], p[maxN], color[maxN]; /* 配列変数 d, p, color */
  int v0;                            /* 始点の変数 */
  int Q[maxN];                       /* キューを表す変数 */
  int head, tail;                    /* キューの先頭と末尾 */
  int i, u, v, a;
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
    Adj[u][v] = 1;
    Adj[v][u] = 1;
  }
  fscanf(fp, " %d", &v0);
  fclose(fp);

  for (v = 0; v < N; v++) {
    color[v] = WHITE;
    d[v] = inf;
    p[v] = -1;
  }

  head = tail = 0;
  Q[tail] = v0;
  tail++;

  if (tail + 1 == N) {
    tail = 0;
  }
  if (tail == head) {
    printf("ERROR:Overflow\n");
    exit(1);
  }

  color[v0] = GRAY;
  d[v0] = 0;
  p[v0] = -1;

  while (head != tail) {
    if (head == tail) {
      printf("ERROR:Underflow\n");
      exit(1);
    } else {
      a = Q[head];
      head++;
      if (head + 1 == N) {
        head = 0;
      }
    }
    v = a;
    for (u = 0; u < N; u++) {
      if (Adj[v][u] == 1) {
        if (color[u] == WHITE) {
          Q[tail] = u;
          tail++;
          if (tail + 1 == N) {
            tail = 0;
          }
          if (tail == head) {
            printf("ERROR:Overflow\n");
            exit(1);
          }
          color[u] = GRAY;
          d[u] = d[v] + 1;
          p[u] = v;
        }
        color[v] = BLACK;
      }
    }
  }
  // 結果出力
  for (u = 0; u < N; u++) {
    printf("vertex %d: d[%d] = %d, p[%d] = %d\n", u, u, d[u], u, p[u]);
  }
}
