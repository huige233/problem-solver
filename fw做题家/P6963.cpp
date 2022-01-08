#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;
void read(int &x)
{
  char ch;
  bool ok;
  for (ok = 0, ch = getchar(); !isdigit(ch); ch = getchar())
    if (ch == '-')
      ok = 1;
  for (x = 0; isdigit(ch); x = x * 10 + ch - '0', ch = getchar())
    ;
  if (ok)
    x = -x;
}
#define rg register
const int maxn = 1e5 + 1;
int n, m, f[maxn][20], dep[maxn], size[maxn], pre[maxn * 2], nxt[maxn * 2], h[maxn], top[maxn], id[maxn], idd, cnt;
struct oo
{
  int l, r, v, la;
} s[maxn * 4];
struct o
{
  int l, r, v;
} a[maxn];
void add(int x, int y)
{
  pre[++cnt] = y, nxt[cnt] = h[x], h[x] = cnt;
  pre[++cnt] = x, nxt[cnt] = h[y], h[y] = cnt;
}
void build(int x, int l, int r)
{
  s[x].l = l, s[x].r = r;
  if (l == r)
    return;
  int mid = (l + r) >> 1;
  build(x << 1, l, mid), build(x << 1 | 1, mid + 1, r);
}
void dfs(int x)
{
  size[x] = 1;
  for (rg int i = 1; i < 20; i++)
  {
    if (dep[x] < (1 << i))
      break;
    f[x][i] = f[f[x][i - 1]][i - 1];
  }
  for (rg int i = h[x]; i; i = nxt[i])
    if (pre[i] != f[x][0])
      f[pre[i]][0] = x, dep[pre[i]] = dep[x] + 1, dfs(pre[i]), size[x] += size[pre[i]];
}
void dfs1(int x, int f)
{
  top[x] = f, id[x] = ++idd;
  int k = 0;
  for (rg int i = h[x]; i; i = nxt[i])
    if (dep[pre[i]] > dep[x] && size[pre[i]] > size[k])
      k = pre[i];
  if (k)
    dfs1(k, f);
  for (rg int i = h[x]; i; i = nxt[i])
    if (dep[pre[i]] > dep[x] && k != pre[i])
      dfs1(pre[i], pre[i]);
}
int lca(int x, int y)
{
  if (dep[x] > dep[y])
    swap(x, y);
  int poor = dep[y] - dep[x];
  for (rg int i = 19; i >= 0; i--)
    if (poor & (1 << i))
      y = f[y][i];
  for (rg int i = 19; i >= 0; i--)
    if (f[x][i] != f[y][i])
      x = f[x][i], y = f[y][i];
  return x == y ? x : f[x][0];
}
void pushdown(int x)
{
  int l = x << 1, r = x << 1 | 1;
  s[l].la = s[r].la = s[l].v = s[r].v = s[x].la;
  s[x].la = 0;
}
void update(int x) { s[x].v = s[x << 1].v == s[x << 1 | 1].v ? s[x << 1].v : -1; }
int get(int x, int l, int r)
{
  if (l <= s[x].l && r >= s[x].r)
    return s[x].v;
  if (s[x].la)
    pushdown(x);
  int ans = 0, mid = (s[x].l + s[x].r) >> 1;
  if (l > mid)
    return get(x << 1 | 1, l, r);
  else if (r <= mid)
    return get(x << 1, l, r);
  else
  {
    ans = get(x << 1, l, r);
    return ans == get(x << 1 | 1, l, r) ? ans : -1;
  }
  return ans;
}
bool check(int x, int y)
{
  int w = -2;
  while (top[x] != top[y])
  {
    if (dep[top[x]] < dep[top[y]])
      swap(x, y);
    if (w == -2)
      w = get(1, id[top[x]], id[x]);
    else if (w != get(1, id[top[x]], id[x]))
      return 1;
    x = f[top[x]][0];
  }
  if (id[x] > id[y])
    swap(x, y);
  if (w == -2)
    w = get(1, id[x], id[y]);
  else if (w != get(1, id[x], id[y]))
    return 1;
  return w == -1 ? 1 : 0;
}
void change(int x, int l, int r, int v)
{
  if (l <= s[x].l && r >= s[x].r)
  {
    s[x].la = s[x].v = v;
    return;
  }
  if (s[x].la)
    pushdown(x);
  int mid = (s[x].l + s[x].r) >> 1;
  if (l <= mid)
    change(x << 1, l, r, v);
  if (r > mid)
    change(x << 1 | 1, l, r, v);
  update(x);
}
void modify(int x, int y, int v)
{
  while (top[x] != top[y])
  {
    if (dep[top[x]] < dep[top[y]])
      swap(x, y);
    change(1, id[top[x]], id[x], v);
    x = f[top[x]][0];
  }
  if (id[x] > id[y])
    swap(x, y);
  change(1, id[x], id[y], v);
}
bool cmp(o a, o b) { return a.v > b.v; }
int main()
{
  read(n), read(m);
  for (rg int i = 1, x, y; i < n; i++)
    read(x), read(y), add(x, y);
  dfs(1), dfs1(1, 1), build(1, 1, n);
  for (rg int i = 1; i <= m; i++)
    read(a[i].l), read(a[i].r), a[i].v = dep[a[i].l] + dep[a[i].r] - 2 * dep[lca(a[i].l, a[i].r)];
  sort(a + 1, a + m + 1, cmp);
  for (rg int i = 1; i <= m; i++)
  {
    if (check(a[i].l, a[i].r))
    {
      printf("No\n");
      return 0;
    }
    modify(a[i].l, a[i].r, i);
  }
  printf("Yes\n");
}