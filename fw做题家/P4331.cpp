#include <bits/stdc++.h>

using namespace std;

const int N = 1e6 + 10;

int ls[N], rs[N], value[N], dis[N];

int root[N], sz[N], l[N], r[N], ans[N], n, cnt;

int merge(int x, int y) {
  if (!x || !y) {
    return x | y;
  }
  if (value[x] < value[y]) {
    swap(x, y);
  }
  rs[x] = merge(rs[x], y);
  if (dis[ls[x]] < dis[rs[x]]) {
    swap(ls[x], rs[x]);
  }
  dis[x] = dis[rs[x]] + 1;
  return x;
}

int main() {
  // freopen("in.txt", "r", stdin);
  // freopen("out.txt", "w", stdout);
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d", &value[i]);
    value[i] -= i;
  }
  for (int i = 1; i <= n; i++) {
    cnt++;
    root[cnt] = i, l[cnt] = i, r[cnt] = i, sz[cnt] = 1, ans[cnt] = value[i];
    while (cnt > 1 && ans[cnt - 1] > ans[cnt]) {
      cnt--;
      root[cnt] = merge(root[cnt], root[cnt + 1]);
      sz[cnt] += sz[cnt + 1];
      r[cnt] = r[cnt + 1];
      while (sz[cnt] > (r[cnt] - l[cnt] + 3) / 2) {
        sz[cnt]--;
        root[cnt] = merge(ls[root[cnt]], rs[root[cnt]]);
      }
      ans[cnt] = value[root[cnt]];
    }
  }
  long long res = 0;
  for (int i = 1; i <= cnt; i++) {
    for (int j = l[i]; j <= r[i]; j++) {
      res += abs(value[j] - ans[i]);
    }
  }
  printf("%lld\n", res);
  for (int i = 1; i <= cnt; i++) {
    for (int j = l[i]; j <= r[i]; j++) {
      printf("%d%c", ans[i] + j, j == n ? '\n' : ' ');
    }
  }
  return 0;
}