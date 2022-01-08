#include "stdio.h"
#include "string.h"
#include "vector"
#include "algorithm"
using namespace std;
#define OK printf("\n");
#define exit return 0;
const int N = 1e6 * 2 + 1010;
const int M = 2 * N;
int read()
{
  int f = 1, x = 0;
  char ss = getchar();
  while (ss < '0' || ss > '9')
  {
    if (ss == '-')
      f = -1;
    ss = getchar();
  }
  while (ss >= '0' && ss <= '9')
  {
    x = x * 10 + ss - '0';
    ss = getchar();
  }
  return f * x;
}
int head[N], ver[M], Next[M], tot;
int n, m, num, top, cnt;
int dfn[N], low[N], id[110];
int limit = 0;
int Stack[N], ins[N], c[N];
int s[N];
char str[N];
int X[N], Y[N];
char cx[N], cy[N];

void add(int x, int y)
{
  ver[++tot] = y;
  Next[tot] = head[x];
  head[x] = tot;
}

void tarjan(int x)
{
  dfn[x] = low[x] = ++num;
  Stack[++top] = x;
  ins[x] = 1;
  for (int i = head[x]; i; i = Next[i])
    if (!dfn[ver[i]])
    {
      tarjan(ver[i]);
      low[x] = min(low[x], low[ver[i]]);
    }
    else if (ins[ver[i]])
      low[x] = min(low[x], dfn[ver[i]]);
  if (dfn[x] == low[x])
  {
    cnt++;
    int y;
    do
    {
      y = Stack[top--];
      ins[y] = 0;
      c[y] = cnt;
    } while (x != y);
  }
}

void Build_edge()
{
  for (int i = 1; i <= m; i++)
  {
    if (str[X[i]] == cx[i])
      continue;
    if (str[Y[i]] == cy[i])
    {
      if (cx[i] == 'C' || (cx[i] == 'B' && str[X[i]] == 'C'))
      {
        add(X[i] + n, X[i]); //printf("%d -> %d\n",X[i] + n,X[i]);
      }
      else
      {
        add(X[i], X[i] + n); //printf("%d -> %d\n",X[i],X[i] + n);
      }
      continue;
    }
    int v1 = (cy[i] == 'C' || (cy[i] == 'B' && str[Y[i]] == 'C')) ? 1 : 0;
    int v2 = (cx[i] == 'C' || (cx[i] == 'B' && str[X[i]] == 'C')) ? 1 : 0;
    add(X[i] + n * (v2), Y[i] + n * v1);
    add(Y[i] + n * (v1 ^ 1), X[i] + n * (v2 ^ 1));
    // printf("%d -> %d\n",X[i] + n *(v2),Y[i] + n * v1);
    //  printf("%d -> %d\n",Y[i] + n * (v1 ^ 1),X[i] + n * (v2 ^ 1));
  }
  return;
}
void init()
{
  num = 0;
  memset(ins, 0, sizeof(ins));
  cnt = 0;
  tot = 0;
  top = 0;
  memset(low, 0, sizeof(low));
  memset(c, 0, sizeof(c));
  memset(dfn, 0, sizeof(dfn));
  memset(Stack, 0, sizeof(Stack));
  memset(head, 0, sizeof(head));
}
void solve()
{

  int mark = 1;
  for (int i = 0; i < (1 << limit); i++)
  {
    init();
    mark = 1;
    for (int j = 1; j <= limit; j++)
    {
      str[id[j]] = (i & (1 << (j - 1))) ? 'A' : 'B';
    }
    Build_edge();
    for (int i = 1; i <= n * 2; i++)
    {
      if (!dfn[i])
        tarjan(i);
    }
    for (int i = 1; i <= n; i++)
      if (c[i] == c[i + n])
      {
        mark = 0;
        break;
      }
    if (mark == 0)
      continue;
    for (int i = 1; i <= n; i++)
    {
      if (c[i] < c[i + n])
      {
        if (str[i] == 'A')
          printf("B");
        else
          printf("A");
      }
      else
      {
        if (str[i] == 'C')
          printf("B");
        else
          printf("C");
      }
    }
    return;
  }
  printf("-1");
  return;
}
int main()
{
  int d;
  scanf("%d%d", &n, &d);
  scanf("%s", str + 1);
  for (int i = 1; i <= n; i++)
  {
    if (str[i] == 'x')
      id[++limit] = i;
    else
      str[i] -= 32;
  }
  m = read();
  for (int i = 1; i <= m; i++)
  {
    scanf("%d %c %d %c", &X[i], &cx[i], &Y[i], &cy[i]);
  }
  solve();
  return 0;
}