#include <cstdio>
#include <cmath>
#include <map>
#define ll long long
#define orz printf("Orz, I cannot find x!\n")
ll read()
{
  ll ans = 0, s = 1;
  char ch = getchar();
  while (ch > '9' || ch < '0')
  {
    if (ch == '-')
      s = -1;
    ch = getchar();
  }
  while (ch >= '0' && ch <= '9')
    ans = (ans << 3) + (ans << 1) + ch - '0', ch = getchar();
  return s * ans;
}
ll pow_mod(ll y, ll z, ll p)
{
  ll ans = 1, base = y;
  while (z)
  {
    if (z & 1)
      ans = ans * base % p;
    base = base * base % p;
    z >>= 1;
  }
  return ans % p;
}
ll gcd(ll x, ll y)
{
  return y == 0 ? x : gcd(y, x % y);
}
ll exgcd(ll a, ll b, ll &x, ll &y)
{
  if (b == 0)
  {
    x = 1;
    y = 0;
    return a;
  }
  ll ret = exgcd(b, a % b, x, y);
  ll t = x;
  x = y;
  y = t - a / b * y;
  return ret;
}
ll bsgs(ll y, ll z, ll p)
{
  // y^x === z (mod p)
  // set m = sqrt(p) + 1, x = a * m - b
  // y^(a * m - b) === z (mod p)
  // y^(a * m) === z * y^b (mod p)
  // b \in [0, m)   a \in (0, m + 1]

  z %= p;
  if (y == 0)
  {
    if (z == 0)
      return 1;
    else
      return -1;
  }
  std::map<ll, ll> mp;
  ll m = sqrt(p) + 1;
  for (int i = 0; i < m; i++)
  {
    ll val = z * pow_mod(y, i, p) % p;
    if (!mp.count(val))
      mp[val] = i;
  }
  ll giant = pow_mod(y, m, p);
  if (giant == 0)
  {
    if (z == 0)
      return 1;
    else
      return -1;
  }
  for (int i = 0; i <= m; i++)
  {
    ll val = pow_mod(giant, i, p);
    int j = mp.find(val) == mp.end() ? -1 : mp[val];
    if (j >= 0 && i * m - j >= 0)
      return i * m - j;
  }
  return -1;
}
int main()
{
  /*
    ll y = read(), z = read(), p = read();
    printf("%lld\n", pow_mod(y, z, p));
    return 0;
    */
  //freopen("in.txt", "r", stdin);
  int T = read(), K = read();
  while (T--)
  {
    ll y = read(), z = read(), p = read();
    if (K == 1)
      printf("%lld\n", pow_mod(y, z, p));
    else if (K == 2)
    {
      // x * y === z (mod p)
      // let a = y
      // a * x === z (mod p)
      // a * x - p * y = z
      // a * xx - p * yy = gcd(a, p)
      ll xx, yy;
      ll g = exgcd(y, p, xx, yy);
      if (z % g != 0)
        orz;
      else
      {
        ll temp = p / g;
        // x : xx = z : g
        ll x = xx * z / g;
        printf("%lld\n", ((x % temp) + temp) % temp);
      }
    }
    else if (K == 3)
    {
      ll ans = bsgs(y, z, p);
      if (ans == -1)
        orz;
      else
        printf("%lld\n", ans);
    }
  }
  return 0;
}