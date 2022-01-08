// luogu-judger-enable-o2
#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (ll i = (a); i <= (b); i++)
#define repp(i, a, b) for (ll i = (a); i >= (b); --i)
#define ll long long
#define see(x) (cerr << (#x) << '=' << (x) << endl)
#define inf 0x3f3f3f3f
#define CLR(A, v) memset(A, v, sizeof A)
/////////////////////////////////////
const ll N = 5e6 + 10;
ll n, m, ans[N], xx[N], xxx[N], yy[N], yyy[N], t[N];
int nxx, nyy;
ll maxx[N << 2];
void build(int l, int r, int pos)
{
  if (!maxx[pos])
    return;
  maxx[pos] = 0;
  if (l == r)
    return;
  int m = (l + r) >> 1;
  build(l, m, pos << 1);
  build(m + 1, r, pos << 1 | 1);
}
void upnode(int x, ll v, int l, int r, int pos)
{
  if (l == r)
  {
    maxx[pos] = max(maxx[pos], v);
    return;
  }
  int m = (l + r) >> 1;
  if (x <= m)
    upnode(x, v, l, m, pos << 1);
  else
    upnode(x, v, m + 1, r, pos << 1 | 1);
  maxx[pos] = max(maxx[pos << 1], maxx[pos << 1 | 1]);
}
ll qmax(int L, int R, int l, int r, int pos)
{
  if (L <= l && r <= R)
    return maxx[pos];
  int m = (l + r) >> 1;
  ll ans = 0;
  if (L <= m)
    ans = max(ans, qmax(L, R, l, m, pos << 1));
  if (R > m)
    ans = max(ans, qmax(L, R, m + 1, r, pos << 1 | 1));
  return ans;
}
struct node
{
  ll x1, y1, x2, y2, id;
} s[N], temp[N];
bool cmp(node a, node b) { return a.y1 < b.y1; }
void cdq(ll l, ll r)
{
  if (l == r)
    return;
  ll mid = (l + r) >> 1;
  cdq(l, mid);
  cdq(mid + 1, r);
  rep(i, l, r) temp[i] = s[i];
  sort(temp + l, temp + mid + 1, cmp);
  sort(temp + mid + 1, temp + r + 1, cmp);
  ll j = l;
  build(1, nxx, 1);
  rep(i, mid + 1, r)
  {
    while (j <= mid && temp[j].y1 <= temp[i].y1)
      upnode(temp[j].x2, temp[j].y2, 1, nxx, 1), j++;
    ll t = qmax(temp[i].x2, nxx, 1, nxx, 1);
    if (t >= temp[i].y2)
      ans[temp[i].id] = 1;
  }
}
int main()
{
  cin >> n;
  int tot = 0, tot2;
  rep(i, 1, n)
      scanf("%lld%lld%lld%lld", &s[i].x1, &s[i].y1, &s[i].x2, &s[i].y2),
      xx[++tot] = s[i].x1, xx[++tot] = s[i].x2,
      yy[++tot2] = s[i].y1, yy[++tot2] = s[i].y2, s[i].id = i;

  sort(xx + 1, xx + 1 + tot);
  sort(yy + 1, yy + 1 + tot2);
  nxx = unique(xx + 1, xx + 1 + tot) - xx - 1;
  nyy = unique(yy + 1, yy + 1 + tot2) - yy - 1;

  rep(i, 1, n)
      s[i]
          .x1 = lower_bound(xx + 1, xx + 1 + nxx, s[i].x1) - xx,
      s[i].x2 = lower_bound(xx + 1, xx + 1 + nxx, s[i].x2) - xx,
      s[i].y1 = lower_bound(yy + 1, yy + 1 + nyy, s[i].y1) - yy,
      s[i].y2 = lower_bound(yy + 1, yy + 1 + nyy, s[i].y2) - yy;

  sort(s + 1, s + 1 + n, [](node a, node b)
       { return a.x1 < b.x1; });
  cdq(1, n);
  ll cnt = 0;
  rep(i, 1, n) if (ans[i]) cnt++;
  cout << cnt << endl;
  return 0;
}