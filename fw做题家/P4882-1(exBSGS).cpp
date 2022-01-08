#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define N1 4000010
#define M1 400010
#define ll long long
#define dd double
#define cll const long long
#define inf 23333333333333333ll
using namespace std;

ll K, M, A;
struct Hsh
{
#define maxn 4000000
  int head[N1], nxt[M1], val[M1], cte;
  ll to[M1];
  void ins(ll x, int w)
  {
    int u = x % maxn;
    ll v;
    for (int j = head[u]; j; j = nxt[j])
    {
      v = to[j];
      if (v == x)
        return;
    }
    cte++;
    to[cte] = x;
    nxt[cte] = head[u];
    val[cte] = w;
    head[u] = cte;
  }
  int find(ll x)
  {
    int u = x % maxn;
    ll v;
    for (int j = head[u]; j; j = nxt[j])
    {
      v = to[j];
      if (v == x)
        return val[j];
    }
    return -1;
  }
} h;

inline ll qmul(ll a, ll b)
{
  return ((((a >> 25) * b % M) << 25) % M + (a & ((1 << 25) - 1)) * b % M) % M;
}
ll qpow(ll x, ll y)
{
  ll ans = 1;
  while (y)
  {
    if (y & 1)
      ans = qmul(ans, x);
    x = qmul(x, x);
    y >>= 1;
  }
  return ans;
}

int main()
{
  scanf("%lld%lld", &K, &M);
  A = (9ll * K + 1) % M;
  ll sq = sqrt(M), i, pw, now, ans;
  for (pw = qpow(10ll, sq), now = 1, i = 1; (i - 1) * sq < M; i++)
  {
    now = qmul(now, pw);
    h.ins(now, i);
  }
  for (now = A, ans = inf, i = 0; i < sq; i++)
  {
    pw = h.find(now);
    if (pw != -1)
      ans = min(ans, pw * sq - i);
    now = qmul(now, 10ll);
  }
  printf("%lld\n", ans);
  return 0;
}