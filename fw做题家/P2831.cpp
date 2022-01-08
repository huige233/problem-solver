#include <cstdio>
#include <cmath>
#include <cstring>
#include <ctype.h>
#define min(a, b) a < b ? a : b
#define lb long double
const lb eps = 1e-12; //极小值(0的近似值
//=============================================================
int T, n, m, all, map[20][20], ans[524288];
lb x[20], y[20]; //横纵坐标
//=============================================================
inline int read()
{
  int s = 1, w = 0;
  char ch = getchar();
  for (; !isdigit(ch); ch = getchar())
    if (ch == '-')
      s = -1;
  for (; isdigit(ch); ch = getchar())
    w = w * 10 + ch - '0';
  return s * w;
}
int gcd(int a, int b) { return b ? gcd(b, a % b) : a; }
void get_ab(int fir, int sec, lb &a, lb &b) //求解 二元一次方程组
{
  lb x1 = x[fir], x12 = x1 * x1, y1 = y[fir], x2 = x[sec], x22 = x2 * x2, y2 = y[sec];                    //初始各系数的值
  x1 *= 100000, x12 *= 100000, y1 *= 100000, x2 *= 100000, x22 *= 100000, y2 *= 100000;                   //将各系数转化为整数
  int t1 = x1, t12 = x12, tt1 = y1, t2 = x2, t22 = x22, tt2 = y2, d = gcd(t12, t22), l = (t12 / d * t22); //赋给整形变量

  t1 *= (l / t12), tt1 *= (l / t12), t2 *= (l / t22), tt2 *= (l / t22), t12 = t22 = l; //进行通分,以进行相减消元

  b = ((tt2 - tt1) * 1.0) / ((t2 - t1) * 1.0); //获得a,b的值
  a = (tt1 * 1.0 - t1 * b) / t12;
}
void prepare()
{
  memset(ans, 127, sizeof(ans));
  ans[0] = 0; //初始化ans为极大值
  memset(map, 0, sizeof(map));

  n = read(), m = read();
  all = (1 << n) - 1;
  for (int i = 0; i < n; i++)
    scanf("%Lf%Lf", &x[i], &y[i]);
  for (int i = 0; i < n; i++)
    map[i][n] = (1 << i);     //只经过一个点的抛物线
  for (int i = 0; i < n; i++) //枚举 抛物线经过的两个点
    for (int j = i + 1; j < n; j++)
    {
      //不合法的点对
      if (x[i] >= x[j] && y[i] > y[j] && y[i] / x[i] >= y[j] / x[j])
        continue;
      if (x[j] >= x[i] && y[j] > y[i] && y[j] / x[j] >= y[i] / x[i])
        continue;

      lb a, b;
      map[i][j] |= (1 << i), map[i][j] |= (1 << j); //加入点集
      get_ab(i, j, a, b);                           //求解a,b
      for (int k = 0; k < n; k++)                   //将被此抛物线经过的 其他点加入点集
        if (fabs(a * x[k] * x[k] + b * x[k] - y[k]) <= eps)
          map[i][j] |= (1 << k);
    }
}
//=============================================================
signed main()
{
  T = read();
  for (; T; T--)
  {
    prepare();
    for (int i = 0; i < all; i++) //枚举点集
      for (int j = 0, sum = 1; sum <= (1 << j); j++, sum <<= 1)
        if (!(i & (1 << j)))               //枚举不在点集中的点
          for (int k = j + 1; k <= n; k++) //构造新的抛物线,并构造新的点集.
            ans[i | map[j][k]] = min(ans[i | map[j][k]], ans[i] + 1);

    printf("%d\n", ans[all]);
  }
}