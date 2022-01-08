#include <bits/stdc++.h>
#define ts cout << "ok" << endl
#define oo (1e18)
#define int long long
#define LL unsigned long long
#define hh puts("")
using namespace std;
int pr[100005], top = 0, ans[100005], cnt;
bool v[100005];
inline int read()
{
  int ret = 0, ff = 1;
  char ch = getchar();
  while (!isdigit(ch))
  {
    if (ch == '-')
      ff = -ff;
    ch = getchar();
  }
  while (isdigit(ch))
  {
    ret = (ret << 3) + (ret << 1) + (ch ^ 48);
    ch = getchar();
  }
  return ret * ff;
}
inline bool pd(int x)
{
  if (x == 1)
    return 0;
  for (int i = 2; i * i <= x; i++)
    if (x % i == 0)
      return 0;
  return 1;
}
void dfs(int now, int x, int s)
{
  // 还剩多少能够分解  第x个质数  当前是哪个数
  if (now == 1)
  {
    ans[++cnt] = s;
    return;
  }
  if (pd(now - 1) && now > pr[x])
    ans[++cnt] = s * (now - 1);
  for (int i = x; pr[i] * pr[i] <= now; i++)
  {                      //枚举下一个选哪个质数
    int t = pr[i];       //t为次方和的最后一个数
    int sum = pr[i] + 1; //sum为总次方和
    for (; sum <= now; t *= pr[i], sum += t)
      if (now % sum == 0)
        dfs(now / sum, i + 1, s * t);
  }
}
signed main()
{
  memset(v, 1, sizeof(v));
  v[1] = 0;
  for (int i = 2; i <= 100000; i++)
  {
    if (v[i])
      pr[++top] = i;
    for (int j = 1; j <= top && pr[j] * i <= 100000; j++)
    {
      v[i * pr[j]] = 0;
      if (i % pr[j] == 0)
        break;
    }
  }
  int x;
  while (scanf("%lld", &x) != EOF)
  {
    cnt = 0;
    dfs(x, 1, 1);
    sort(ans + 1, ans + cnt + 1);
    printf("%lld\n", cnt);
    for (int i = 1; i <= cnt; i++)
      printf("%lld ", ans[i]);
    if (cnt)
      hh;
  }
  return 0;
}