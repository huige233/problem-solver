#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <math.h>
#include <vector>
#include <queue>
#include <stack>
 
using namespace std;
 
vector <int> g[10010];
struct C {int no, num;};
C cut[10010];
int dfs_clock;
int pre[10010];
bool comp(C a, C b)
{
    if(a.num != b.num) return a.num > b.num;
    else return a.no < b.no;
}
int dfs(int u, int fa)
{
    int lowu = pre[u] = ++dfs_clock;
    int child = 0;
    for(int i = 0; i < g[u].size(); i++)
    {
        int v = g[u][i];
        if(!pre[v])
        {
            child++;
            int lowv = dfs(v, u);
            lowu = min(lowu, lowv);
            if(lowv >= pre[u])
            {
                cut[u].num++;
            }
        }
        else if(pre[v] < pre[u] && v != fa)
        {
            lowu = min(lowu, pre[v]);
        }
    }
    if(fa < 0 && child == 1) cut[u].num = 0;
    return lowu;
}
int main()
{
    int n, m;
    while(scanf("%d%d", &n, &m))
    {
        if(n == 0 && m == 0) break;
        for(int i=0; i<10010; i++)
        {
            g[i].clear();
            cut[i].no = i, cut[i].num = 0;
        }
        memset(pre, 0, sizeof(pre));
        int x, y;
        while(scanf("%d%d", &x, &y))
        {
            if(x == -1 && y == -1) break;
            g[x].push_back(y);
            g[y].push_back(x);
        }
        dfs_clock = 0;
        dfs(0, -1);
        sort(cut, cut+n, comp);
        for(int i = 0; i < m; i++)
        {
            printf("%d %d\n", cut[i].no, cut[i].num + 1);
        }
        printf("\n");
    }
    return 0;
}