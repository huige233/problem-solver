#include <bits/stdc++.h>
#include <tr1/unordered_map>
#define int long long
using namespace std;
std::tr1::unordered_map<int, int> M;
int read()
{
  int f = 1, re = 0;
  char ch;
  for (ch = getchar(); !isdigit(ch) && ch != '-'; ch = getchar())
    ;
  if (ch == '-')
  {
    f = -1, ch = getchar();
  }
  for (; isdigit(ch); ch = getchar())
    re = (re << 3) + (re << 1) + ch - '0';
  return re * f;
}
int gcd(int a, int b) { return b ? gcd(b, a % b) : a; }
int ksm(int a, int b, int mod)
{
  int ans = 1;
  while (b)
  {
    if (b & 1)
      ans = ans * a % mod;
    a = a * a % mod;
    b >>= 1;
  }
  return ans;
}
int qmul(int a, int b, int mod)
{
  int ans = 0;
  while (b)
  {
    if (b & 1)
      ans = (ans + a) % mod;
    a = (a + a) % mod;
    b >>= 1;
  }
  return ans;
}
int bsgs(int a, int b, int p, int ad)
{
  M.clear();
  int m = sqrt(p) + 1, s = 1;
  for (int i = 0; i < m; i++, s = qmul(s, a, p))
    M[qmul(s, b, p)] = i;
  for (int i = 0, tmp = s, s = ad; i <= m; i++, s = qmul(s, tmp, p))
    if (M.find(s) != M.end())
      if (i * m - M[s] >= 0)
        return i * m - M[s];
  return -1;
}
int exbsgs(int a, int b, int p)
{
  a %= p, b %= p;
  if (b == 1 || p == 1)
    return 0;
  int d, ad = 1, cnt = 0;
  while ((d = gcd(a, p)) ^ 1)
  {
    if (b % d)
      return -1;
    cnt++, b /= d, p /= d;
    ad = qmul(ad, a / d, p);
    if (ad == b)
      return cnt;
  }
  int ans = bsgs(a, b, p, ad);
  if (ans < 0)
    return -1;
  else
    return ans + cnt;
}
signed main()
{
  int b = read(), p = read();
  b = qmul(b, 9, p) + 1;
  printf("%lld\n", exbsgs(10, b, p));
  return 0;
}