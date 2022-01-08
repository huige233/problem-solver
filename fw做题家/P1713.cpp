#include <bits/stdc++.h>

using pii = std::pair<int, int>;
const int inf = 1e7;

int dx[] = {0, 1, 0, -1};
int dy[] = {1, 0, -1, 0};

int n, m, dis[12][12], ban[12][12];

std::map<std::vector<int>, int> dp[12][12];

std::vector<int> process(std::vector<int> S)
{
  int cnt = 1;
  int vis[30] = {0};
  for (int i = 1; i <= n + 1; ++i)
  {
    if (S[i] == 0 || S[i] == 1)
      continue;
    if (!vis[S[i]])
    {
      vis[S[i]] = ++cnt;
      S[i] = cnt;
    }
    else
      S[i] = vis[S[i]];
  }
  return S;
}
std::vector<int> shift(std::vector<int> S)
{
  for (int i = 1; i <= n; ++i)
    S[i] = S[i + 1];
  S[n + 1] = 0;
  return S;
}
std::vector<int> trans(std::vector<int> S, int i)
{
  std::swap(S[i], S[i + 1]);
  return S;
}
std::vector<int> create(std::vector<int> S, int i)
{
  S[i] = S[i + 1] = 20;
  return process(S);
}
std::vector<int> merge(std::vector<int> S, int i)
{
  int p = S[i], q = S[i + 1], flag = 20;
  if (p == 1 || q == 1)
    flag = 1;
  for (int i = 1; i <= n + 1; ++i)
    if (S[i] == p || S[i] == q)
      S[i] = flag;
  S[i] = S[i + 1] = 0;
  return process(S);
}

int main()
{

  scanf("%d%d", &n, &m);
  for (int i = 1; i <= m; ++i)
  {
    int x, y;
    scanf("%d%d", &x, &y);
    ban[x][y] = 1;
    assert(not((x == 1 && y == n) or (x == n && y == 1)));
  }

  auto bfs = [&]()
  {
    std::memset(dis, -1, sizeof(dis));
    std::queue<pii> q;
    q.push({1, n});
    dis[1][n] = 0;
    while (q.size())
    {
      auto u = q.front();
      q.pop();
      int x = u.first, y = u.second;
      for (int i = 0; i < 4; ++i)
      {
        int x1 = x + dx[i], y1 = y + dy[i];
        if (x1 < 1 || x1 > n || y1 < 1 || y1 > n || dis[x1][y1] != -1 || ban[x1][y1])
          continue;
        dis[x1][y1] = dis[x][y] + 1;
        q.push({x1, y1});
      }
    }
  };
  bfs();

  std::vector<int> v(n + 2);
  v[n + 1] = 1;
  dp[1][n - 1][v] = 1;
  v[n + 1] = 0;
  v[n] = 1;
  dp[1][n - 1][v] = 1;

  for (int i = 1; i <= n; ++i)
  {
    for (int j = n - (i == 1); j >= 1; j--)
    {
      for (auto P : dp[i][j])
      {
        auto S = P.first;
        int v = P.second;
        int p = S[j], q = S[j + 1];
        if (p == 0 && q == 0)
          dp[i][j - 1][S] = std::max(dp[i][j - 1][S], v);
        if (ban[i][j])
          continue;
        if (p == 0 && q == 0)
        {
          auto T = create(S, j);
          dp[i][j - 1][T] = std::max(dp[i][j - 1][T], v + 1);
        }
        if ((p != 0) + (q != 0) == 1)
        {
          dp[i][j - 1][S] = std::max(dp[i][j - 1][S], v + 1);
          auto T = trans(S, j);
          dp[i][j - 1][T] = std::max(dp[i][j - 1][T], v + 1);
        }
        if (p && q && p != q)
        {
          auto T = merge(S, j);
          dp[i][j - 1][T] = std::max(dp[i][j - 1][T], v + 1);
        }
      }
    }
    for (auto P : dp[i][0])
    {
      auto S = P.first;
      int v = P.second;
      if (S[1] == 0)
        dp[i + 1][n][shift(S)] = dp[i][0][S];
    }
  }
  std::vector<int> S1(n + 2), S2(n + 2);
  S1[1] = 1;
  S2[2] = 1;
  printf("%d", std::max(dp[n][1][S1], dp[n][1][S2]) - dis[n][1]);
  return 0;
}