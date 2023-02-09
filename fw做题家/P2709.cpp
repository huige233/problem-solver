#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

const int N = 5e4 + 10;
int n, m, k, len;
int a[N], bel[N], cnt[N];
long res[N], ans;
struct Query {
  int id, l, r;
} q[N];

void add(int x) {
  ans -= cnt[x] * cnt[x];
  cnt[x]++;
  ans += cnt[x] * cnt[x];
}

void del(int x) {
  ans -= cnt[x] * cnt[x];
  cnt[x]--;
  ans += cnt[x] * cnt[x];
}

int main() {
  scanf("%d%d%d", &n, &m, &k);
  len = sqrt(n);
  for (int i = 1; i <= n; i++) {
    bel[i] = i / len;
    scanf("%d", &a[i]);
  }

  for (int i = 0; i < m; i++) {
    scanf("%d%d", &q[i].l, &q[i].r);
    q[i].id = i;
  }

  sort(q, q + m, [&](Query& q1, Query& q2) {
    int l1 = q1.l, l2 = q2.l;
    if (bel[l1] != bel[l2]) return bel[l1] < bel[l2];
    int r1 = q1.r, r2 = q2.r;
    if (bel[l1] & 1) return r1 < r2;
    else return r1 > r2;
  });

  for (int k = 0, i = 0, j = 1; k < m; k++) {
    int id = q[k].id, l = q[k].l, r = q[k].r;
    while (i < r) add(a[++i]);
    while (i > r) del(a[i--]);
    while (j < l) del(a[j++]);
    while (j > l) add(a[--j]);
    res[id] = ans;
  }

  for (int i = 0; i < m; i++) printf("%ld\n", res[i]);
}