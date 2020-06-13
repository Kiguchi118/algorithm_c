#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
  int key;
  struct node *parent;
  struct node *left;
  struct node *right;
};

/* 関数 tree_search, tree_minimum, tree_insert の宣言 */
struct node *tree_search(struct node *T, int a);
void inorder_tree_walk(struct node *x);
struct node *tree_minimum(struct node *x);
struct node *tree_maximum(struct node *x);
struct node *tree_insert(struct node *T, struct node *x);
struct node *tree_delete(struct node *T, struct node *z);

int main(void) {
  struct node *Tree;      /* ２分探索木を表す変数は Tree */
  struct node *x, *y, *z; /* 挿入，削除等に用いる node 型変数 */
  int N;                  /* 数値の数は N */
  int Data[50];           /* 数値を格納する配列は Data */
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

  Tree = NULL; /* Tree の初期化，最初は空 */

  printf("挿入を始めます.\n");
  for (i = 0; i < N; i++) {
    x = (struct node *)malloc(sizeof(struct node));
    x->key = Data[i];
    x->parent = x->left = x->right = NULL;
    Tree = tree_insert(Tree, x);
    printf("keys in tree:");
    inorder_tree_walk(Tree);
    printf("\nmin = %d, max = %d\n", tree_minimum(Tree)->key,
           tree_maximum(Tree)->key);
  }

  printf("削除を始めます.\n");
  for (i = 0; i < N; i++) {
    a = Data[i];
    z = tree_search(Tree, a);
    Tree = tree_delete(Tree, z);

    printf("keys in tree:");
    inorder_tree_walk(Tree);
    printf("\n");

    if (Tree != NULL) {
      printf("min = %d, max = %d\n", tree_minimum(Tree)->key,
             tree_maximum(Tree)->key);
    } else {
      printf("２分探索木から全ての数値を削除しました.\n終了です.\n");
    }
  }
  return 0;
}

struct node *tree_insert(struct node *T, struct node *x) {
  struct node *r, *y, *z;
  r = T;
  y = NULL;
  z = r;

  while (z != NULL) {
    if (x->key < z->key) {
      y = z;
      z = z->left;
    } else {
      y = z;
      z = z->right;
    }
  }
  x->parent = y;
  if (y == NULL) {
    r = x;
  } else {
    if (x->key < y->key) {
      y->left = x;
    } else {
      y->right = x;
    }
  }
  return r;
}

void inorder_tree_walk(struct node *x) {
  if (x != NULL) {
    inorder_tree_walk(x->left);
    printf(" %d", x->key);
    inorder_tree_walk(x->right);
  }
}

struct node *tree_minimum(struct node *x) {
  while (x->left != NULL) {
    x = x->left;
  }
  return x;
}

struct node *tree_maximum(struct node *x) {
  while (x->right != NULL) {
    x = x->right;
  }
  return x;
}

struct node *tree_search(struct node *x, int a) {
  while (x != NULL && x->key != a) {
    if (a < x->key) {
      x = x->left;
    } else {
      x = x->right;
    }
  }
  return x;
}

struct node *tree_delete(struct node *T, struct node *z) {
  struct node *y, *p, *x;
  if (z->right == NULL || z->left == NULL) {
    y = z;
  } else {
    y = tree_minimum(z->right);
  }
  p = y->parent;
  if (y->right != NULL) {
    x = y->right;
    x->parent = p;
  } else if (y->left != NULL) {
    x = y->left;
    x->parent = p;
  } else {
    x = NULL;
  }
  if (p == NULL) {
    T = x;
  } else {
    if (y->key < p->key) {
      p->left = x;
    } else {
      p->right = x;
    }
  }
  if (y != z) {
    z->key = y->key;
  }
  free(y);
  return T;
}
