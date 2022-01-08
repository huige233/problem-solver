#include <iostream>
#include <cstdio>
#include <queue>
#include <cstring>
#include <algorithm>
#define LL long long
#define REP(i, x, y) for (int i = (x); i <= (y); i++)
using namespace std;
int RD()
{
  int out = 0, flag = 1;
  char c = getchar();
  while (c < '0' || c > '9')
  {
    if (c == '-')
      flag = -1;
    c = getchar();
  }
  while (c >= '0' && c <= '9')
  {
    out = out * 10 + c - '0';
    c = getchar();
  }
  return flag * out;
}
const int maxn = (1 << 19), INF = 1e9;
int map[19][19];
int from[19];
int num, nr, leave;
int ans = INF;
bool in[19];
int cnt, lev[19];
int vis[19];
void dfs(int tot, int begin1, int begin2)
{
  if (cnt == num)
  {
    ans = min(ans, tot);
    return;
  }
  if (tot >= ans)
    return;
  REP(i, begin1, cnt)
  {
    int u = vis[i];
    if (lev[u] * leave + tot >= ans)
      return;
    REP(v, begin2, num)
    {
      if (!in[v] && map[u][v] != INF)
      {
        vis[++cnt] = v;
        in[v] = 1, lev[v] = lev[u] + 1;
        leave -= map[from[v]][v];
        dfs(tot + map[u][v] * lev[u], i, v + 1);
        cnt--;
        in[v] = 0, lev[v] = 0;
        leave += map[from[v]][v];
      }
    }
    begin2 = 1;
  }
}
int main()
{
  num = RD(), nr = RD();
  REP(i, 1, num)
  REP(j, 1, num) map[i][j] = INF;
  REP(i, 1, nr)
  {
    int u = RD(), v = RD(), dis = RD();
    map[u][v] = map[v][u] = min(map[u][v], dis);
  }
  REP(i, 1, num)
  {
    int minn = INF;
    REP(j, 1, num)
    {
      if (map[j][i] < minn)
      {
        minn = map[j][i];
        from[i] = j; //找一个最短的来自点作为最优预算
      }
    }
    leave += minn;
  }
  REP(i, 1, num)
  {
    in[i - 1] = 0, lev[i - 1] = 0;
    in[i] = 1, lev[i] = 1;
    leave -= map[from[i]][i];
    vis[cnt = 1] = i;
    dfs(0, 1, 1);
    leave += map[from[i]][i];
  }
  printf("%d\n", ans);
  return 0;
}