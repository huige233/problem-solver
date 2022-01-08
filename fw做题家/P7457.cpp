#include <bits/stdc++.h>
using namespace std;
#define ll long long
map<pair<int, int>, pair<int, int>> mp;
struct nade
{
  int x, y, val;
};
int askx[1000005], asky[1000005], opt[1000005];
int ans[1000005];
vector<nade> v[4000005];
int n, q;
int fa[1000005], dis[2000005];
struct node
{
  int x, y, ds;
};
stack<node> st;
int get(int x)
{
  if (x == fa[x])
    return x;
  else
    return get(fa[x]);
}
void add(int x, int y)
{
  x = get(x), y = get(y);
  if (x == y)
    return;
  if (dis[x] > dis[y])
    swap(x, y);
  fa[x] = y;
  st.push({x, y, dis[y]});
  dis[y] += dis[x];
}
void pop()
{
  int x = st.top().x, y = st.top().y;
  dis[y] = st.top().ds;
  fa[x] = x;
  st.pop();
}
void insert(int k, int l, int r, int x, int y, nade z)
{
  if (l >= x && r <= y)
  {
    v[k].push_back(z);
    return;
  }
  int mid = l + r >> 1;
  if (mid >= x)
    insert(k * 2, l, mid, x, y, z);
  if (mid < y)
    insert(k * 2 + 1, mid + 1, r, x, y, z);
}
void solve(int k, int l, int r, int x)
{
  int ht = st.size();
  for (int i = 0; i < v[k].size(); i++)
    if (v[k][i].val <= x)
      add(v[k][i].x, v[k][i].y);
  if (l == r)
  {
    if (opt[l] == 2 && get(askx[l]) == get(asky[l]) && ans[l] < 0)
      ans[l] = x;
    while (st.size() > ht)
      pop();
    return;
  }
  int mid = l + r >> 1;
  solve(k * 2, l, mid, x);
  solve(k * 2 + 1, mid + 1, r, x);
  while (st.size() > ht)
    pop();
}
int main()
{
  scanf("%d%d", &n, &q);
  for (int i = 1; i <= q; i++)
  {
    int o;
    scanf("%d", &o);
    opt[i] = o;
    int x, y;
    scanf("%d%d", &x, &y);
    if (x > y)
      swap(x, y);
    askx[i] = x, asky[i] = y;
    if (o == 0)
    {
      int val;
      scanf("%d", &val);
      mp[make_pair(x, y)] = make_pair(i, val);
    }
    else if (o == 1)
    {
      insert(1, 1, q, mp[make_pair(x, y)].first, i - 1, (nade){x, y, mp[make_pair(x, y)].second});
      mp.erase(make_pair(x, y));
    }
  }
  for (int i = 1; i <= n; i++)
    fa[i] = i, dis[i] = 1;
  for (map<pair<int, int>, pair<int, int>>::iterator i = mp.begin(); i != mp.end(); i++)
    insert(1, 1, q, (*i).second.first, q, (nade){(*i).first.first, (*i).first.second, (*i).second.second});
  memset(ans, -1, sizeof(ans));
  for (int i = 0; i <= 10; i++)
    solve(1, 1, q, i);
  for (int i = 1; i <= q; i++)
    if (opt[i] == 2)
      printf("%d\n", ans[i]);
  return 0;
}