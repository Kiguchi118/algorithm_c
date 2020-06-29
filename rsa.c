#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int prime_check(unsigned long int p);
unsigned long int gcd(unsigned long int a, unsigned long int b);
unsigned long int modpow(unsigned long int a, unsigned long int b,
                         unsigned long int c);
unsigned long int rho_algorithm(unsigned long int a);

int main(void) {
  unsigned long int p, q;        // 素数
  unsigned long int n, e;        // 公開鍵
  unsigned long int d;           // 秘密鍵
  unsigned long int check;       // 素数の判定に利用
  unsigned long int l;           // オイラー関数
  int plaintext;                 // 平文
  unsigned long int cryptogram;  // 暗号文
  unsigned long int decryption;  // 復号文
  int decry_plaintext;           // 暗号解読による平文
  unsigned long int fake_key;    // 偽物の秘密鍵

  printf("2つの異なる4桁以上の素数を入力してください．\n");
  printf("p = ");
  scanf("%ld", &p);
  check = prime_check(p);
  while (check == 1) {  // 素数pの判定
    printf("%ldは素数ではありません．\n", p);
    printf("p = ");
    scanf("%ld", &p);
    check = prime_check(p);
  }
  printf("q = ");
  scanf("%ld", &q);
  check = prime_check(q);
  while (check == 1) {  // 素数qの判定
    printf("%ldは素数ではありません．\n", q);
    printf("q = ");
    scanf("%ld", &q);
    check = prime_check(q);
  }

  // 公開鍵nを保持
  n = p * q;
  printf("n = %ld\n", n);

  // 公開鍵eを保持
  l = (p - 1) * (q - 1);
  printf("オイラー関数 l = %ld\n", l);
  printf("%ldと互いに素となるような整数e(1 < e < %ld)を入力してください．\n", l,
         n);
  while (1) {  // 互いに素であるか判定
    printf("e = ");
    scanf("%ld", &e);
    if (1 < e && e < n) {
      if (gcd(l, e) == 1)
        break;
      else
        printf("%ldと互いに素となる整数e(1 < e < %ld)を入力してください．\n", l,
               n);
    } else {
      printf("1 < e < %ldの範囲で入力してください.\n", n);
    }
  }

  // 秘密鍵dを保持
  printf("秘密鍵dを保持します．(1 < d < %ld)\n", l);
  d = 2;
  while (d * e % l != 1) d++;
  printf("d = %ld\n", d);

  /* ---------- 鍵の表示 ---------- */
  printf(" ---------- 公開鍵 ----------\n");
  printf(" n = %ld  e = %ld\n", n, e);
  printf(" ---------- 秘密鍵 ----------\n");
  printf(" d = %ld\n", d);
  printf(" ----------------------------\n");
  /* ----------------------------- */

  // 平文の入力
  printf("平文を入力してください:");
  scanf("%d", &plaintext);
  // while (plaintext < 10 || plaintext > 99){
  //     printf("正しい数値を入力してください．\n");
  //     printf("平文を入力してください(2桁の正数):");
  //     scanf("%d", &plaintext);
  // }

  // 暗号化
  cryptogram = modpow(plaintext, e, n);
  printf("暗号文：%ld\n", cryptogram);

  // 復号化
  decryption = modpow(cryptogram, d, n);
  printf("復号文：%ld\n", decryption);

  // 暗号解読
  printf(
      " ----------------------------\n次に公開鍵n，eと受信(盗聴)"
      "した暗号文から暗号を解読し，平文を求めます．\n");

  // 公開鍵nを素因数分解
  p = rho_algorithm(n);
  q = n / p;
  printf("%ld = %ld * %ld\n", n, p, q);

  // 秘密鍵dを作成(偽造)
  l = (p - 1) * (q - 1);
  fake_key = 2;
  while (fake_key * e % l != 1) fake_key++;
  decry_plaintext = modpow(cryptogram, fake_key, n);
  printf("暗号を解読した平文は %d です．\n", decry_plaintext);

  return 0;
}

// 素数の判定
int prime_check(unsigned long int a) {
  if (a < 2)
    return 1;
  else if (a == 2)
    return 0;
  else if (a % 2 == 0)
    return 1;

  double sqrtprime = sqrt(a);  // aが合成数ならば、√a以下の約数を持つ
  for (int i = 3; i <= sqrtprime; i += 2) {
    if (a % i == 0) return 1;  // 奇数で割った余りが0の時は素数ではない
  }
  return 0;  // 素数
}

// 最大公約数を求める(ユークリッドの互除法)
unsigned long int gcd(unsigned long int a, unsigned long int b) {
  if (b == 0)
    return a;
  else
    return gcd(b, a % b);
}

// バイナリ法(冪乗の剰余の計算)
unsigned long int modpow(unsigned long int a, unsigned long int b,
                         unsigned long int c) {
  unsigned long int value = 1;

  while (b > 0) {
    if ((b & 1) == 1) value = (value * a) % c;
    b >>= 1;  // 右にシフト
    a = (a * a) % c;
  }

  return value;
}

// ロー素因数分解法
unsigned long int rho_algorithm(unsigned long int a) {
  unsigned long int x, y;
  unsigned long int num = 1;  // 初期値
  int i, j;
  unsigned long int d;  // 公開鍵 n の非自明な素因数

  for (i = 1;; i++) {
    // i = 1 の時，初期値を代入
    if (i == 1)
      x = y = num;
    else
      x = (x * x + 1) % a;
    // y_i = x_2i に設定
    for (j = 0; j < 2; j++) y = (y * y + 1) % a;

    // |x_i - y_i| と N の最大公約数 d の計算
    d = gcd((int)fabs(((double)x - (double)y)), a);

    // 判定
    if (d == 1)
      continue;  // i を増やして再度実行
    else if (1 < d && d < a)
      return d;  // 成功
    else if (d == a) {
      // i を戻し x の初期値を更新して最初からやり直す
      i = 0;
      num++;
      // 10回繰り返して失敗したなら諦める
      if (num > 10) {
        puts("暗号解読に失敗しました．");
        exit(1);
      }
    }
  }
}