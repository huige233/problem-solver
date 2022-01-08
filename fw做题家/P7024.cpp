#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 25;
int n = 0, m;
char s[N];
int id[256];
struct Graph
{
  struct Edge
  {
    int nxt, from, to;
  } e[N << 1];
  int fir[N], size = 0;
  void add(int u, int v) { e[++size] = (Edge){fir[u], u, v}, fir[u] = size; }
} g1, g2;
int bel[N], tot = 0;
int dfn[N], low[N], cnt = 0;
stack<int> h;
bool vis[N];
void tarjan(int u)
{
  dfn[u] = low[u] = ++cnt;
  vis[u] = true, h.push(u);
  for (int i = g1.fir[u]; i; i = g1.e[i].nxt)
  {
    if (!dfn[g1.e[i].to])
    {
      tarjan(g1.e[i].to);
      low[u] = min(low[u], low[g1.e[i].to]);
    }
    else if (vis[g1.e[i].to])
      low[u] = min(low[u], dfn[g1.e[i].to]);
  }
  if (dfn[u] == low[u])
  {
    ++tot;
    while (h.top() != u)
      vis[h.top()] = false, bel[h.top()] = tot, h.pop();
    vis[h.top()] = false, bel[h.top()] = tot, h.pop();
  }
}
int f[1 << N], deg[N];
int gcd(int a, int b) { return b == 0 ? a : gcd(b, a % b); }
signed main()
{
  cin >> m;
  for (int i = 1; i < m; ++i)
  {
    scanf("%s", s + 1), scanf("%s", s + 1), id[(int)s[1]] = ++n;
    scanf("%s", s + 1), scanf("%s", s + 1);
    if ('a' <= s[7] && s[7] <= 'z')
      g1.add(id[(int)s[7]], n);
    scanf("%s", s + 1);
    if ('a' <= s[1] && s[1] <= 'z' && s[1] != 'n')
      g1.add(n, id[(int)s[1]]);
  }
  scanf("%s", s + 1);
  for (int i = 1; i <= n; ++i)
  {
    if (dfn[i])
      continue;
    tarjan(i);
  }
  for (int i = 1; i <= g1.size; ++i)
  {
    if (bel[g1.e[i].from] != bel[g1.e[i].to])
    {
      g2.add(bel[g1.e[i].to], bel[g1.e[i].from]);
    }
  }
  printf("%lld ", tot);
  f[0] = 1;
  for (int now = 0; now < (1 << tot); ++now)
  {
    for (int i = 1; i <= tot; ++i)
    {
      if (now & (1 << (i - 1)))
        continue;
      bool flag = true;
      for (int j = g2.fir[i]; j; j = g2.e[j].nxt)
      {
        flag &= (bool)(now & (1 << (g2.e[j].to - 1)));
      }
      if (!flag)
        continue;
      // printf("%lld %lld %lld %lld\n",now,i,now|(1<<(i-1)),f[now]);
      f[now | (1 << (i - 1))] += f[now];
    }
  }
  int tmp, res = 1;
  for (int i = 1; i <= tot; ++i)
    res *= i;
  tmp = gcd(res, f[(1 << tot) - 1]);
  printf("%lld/%lld\n", f[(1 << tot) - 1] / tmp, res / tmp);
  return 0;
}