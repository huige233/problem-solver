#include <cstdio>

const int maxn = 3000005;

long long l[maxn], r[maxn], size[maxn], fa[maxn], ch[maxn][2];
int tot;
long long n, m, q;
struct Splay
{
  int root;
  int identify(int x)
  {
    return ch[fa[x]][1] == x;
  }
  void connect(int son, int f, int k)
  {
    fa[son] = f;
    ch[f][k] = son;
  }
  void pushup(int x)
  {
    size[x] = size[ch[x][0]] + size[ch[x][1]] + (r[x] - l[x] + 1);
  }
  void rotate(int x)
  {
    int y = fa[x];
    int z = fa[y];
    int yk = identify(x);
    int zk = identify(y);
    int b = ch[x][yk ^ 1];
    connect(b, y, yk);
    connect(y, x, yk ^ 1);
    connect(x, z, zk);
    pushup(y);
    pushup(x);
  }
  void splay(int x, int goal)
  {
    while (fa[x] != goal)
    {
      int y = fa[x];
      int z = fa[y];
      if (z != goal)
        identify(x) == identify(y) ? rotate(y) : rotate(x);
      rotate(x);
    }
    if (goal == 0)
      root = x;
  }
  void insert(long long ll, long long rr)
  {
    int now = root, f = 0;
    while (now)
    {
      f = now;
      now = ch[now][1];
    }
    now = ++tot;
    l[now] = ll, r[now] = rr;
    fa[now] = f;
    if (f)
      ch[f][1] = now;
    splay(now, 0);
  }
  int splitnode(int x, int k) // source[l, l + k - 1], new [l + k, r]
  {
    int y = ++tot;
    l[y] = l[x] + k, r[y] = r[x];
    r[x] = l[x] + k - 1;
    if (ch[x][1] == 0)
    {
      ch[x][1] = y;
      fa[y] = x;
    }
    else
    {
      int t = ch[x][1];
      while (ch[t][0])
        t = ch[t][0];
      ch[t][0] = y;
      fa[y] = t;
      //while(t != x) pushup(t), t = fa[t];
    }
    splay(y, 0);
    return y;
  }
  long long popkth(int k)
  {
    int now = root;
    while (2333)
    {
      int left = ch[now][0];
      if (size[left] + (r[now] - l[now] + 1) < k)
      {
        k -= size[left] + (r[now] - l[now] + 1);
        now = ch[now][1];
      }
      else if (size[left] >= k)
        now = left;
      else
      {
        k -= size[left];
        if (k != (r[now] - l[now] + 1))
          splitnode(now, k);
        if (k != 1)
          now = splitnode(now, k - 1);
        break;
      }
    }
    splay(now, 0);
    fa[ch[now][0]] = fa[ch[now][1]] = 0;
    if (ch[now][0] == 0)
      root = ch[now][1];
    else
    {
      int t = ch[now][0];
      while (ch[t][1])
        t = ch[t][1];
      splay(t, 0);
      ch[t][1] = ch[now][1];
      fa[ch[t][1]] = t;
      pushup(t);
    }
    return l[now];
  }
  void print(int u)
  {
    if (ch[u][0])
      print(ch[u][0]);
    printf("%lld %lld\n", l[u], r[u]);
    if (ch[u][1])
      print(ch[u][1]);
  }
} s[300005];
long long read()
{
  long long ans = 0, s = 1;
  char ch = getchar();
  while (ch > '9' || ch < '0')
  {
    if (ch == '-')
      s = -1;
    ch = getchar();
  }
  while (ch >= '0' && ch <= '9')
  {
    ans = ans * 10 + ch - '0';
    ch = getchar();
  }
  return s * ans;
}
int main()
{
  n = read(), m = read(), q = read();
  for (long long i = 1; i <= n; i++)
  {
    s[i].insert((i - 1) * m + 1, i * m - 1);
    s[0].insert(i * m, i * m);
  }
  /*
    for(int i = 1; i <= n; i++)
    {
        s[i].print(s[i].root);
        printf("\n");
    }
    s[0].print(s[0].root);
    printf("\n");
    return 0;
    */
  while (q--)
  {
    int x = read(), y = read();
    long long pop1 = s[0].popkth(x);
    s[x].insert(pop1, pop1);
    long long pop2 = s[x].popkth(y);
    s[0].insert(pop2, pop2);
    printf("%lld\n", pop2);
  }
  return 0;
}