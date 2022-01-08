#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;
int t[400010]; //如果t[i]不为叶子节点，t[i]为标记，否则t[i]为数值
void down(int k)
{
  if (t[k])
  {
    t[k << 1] ^= 1;
    t[k << 1 | 1] ^= 1;
    t[k] = 0;
  }
}
void change(int k, int l, int r, int x, int y)
{
  if (x <= l && r <= y) //如果当前区间完全被修改区间包含，整体xor
  {
    t[k] ^= 1;
    return;
  }
  down(k); //下传标记
  int mid = (l + r) >> 1;
  if (x <= mid)
    change(k << 1, l, mid, x, y);
  if (mid < y)
    change(k << 1 | 1, mid + 1, r, x, y);
}
int ask(int k, int l, int r, int x)
{
  if (l == r)
    return t[k];
  down(k); //下传标记
  int mid = (l + r) >> 1;
  if (x <= mid)
    return ask(k << 1, l, mid, x);
  else
    return ask(k << 1 | 1, mid + 1, r, x);
}
int main()
{
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= m; i++)
  {
    int k, x, y;
    scanf("%d%d", &k, &x);
    if (k == 1)
    {
      scanf("%d", &y);
      change(1, 1, n, x, y);
    }
    else
      printf("%d\n", ask(1, 1, n, x));
  }
  return 0;
}