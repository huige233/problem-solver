#include<iostream>
#include<cmath>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#define FOR(i,x,y) for(int i=(x);i<=(y);i++)
#define DOR(i,x,y) for(int i=(x);i>=(y);i--)
#define N 303
typedef long long LL;
using namespace std;
template<const int maxn,const int maxm>struct Linked_list
{
    int head[maxn],to[maxm],nxt[maxm],tot;
    void clear(){memset(head,-1,sizeof(head));tot=0;}
    void add(int u,int v){to[++tot]=v,nxt[tot]=head[u],head[u]=tot;}
    #define EOR(i,G,u) for(int i=G.head[u];~i;i=G.nxt[i])
};
Linked_list<N,N>G;
int dp[N][N],dfn[N],ori[N],sz[N],ord;
int n,m,p[N];

void dfs(int u)
{
    dfn[u]=++ord,ori[ord]=u,sz[u]=1;
    EOR(i,G,u)
    {
        int v=G.to[i];
        dfs(v);
        sz[u]+=sz[v];
    }
}

int main()
{
    while(~scanf("%d%d",&n,&m))
    {
        G.clear();
        memset(dp,0,sizeof(dp));
        FOR(v,1,n)
        {
            int u;
            scanf("%d%d",&u,&p[v]);
            G.add(u,v);
        }
        m++;n++;ord=0;
        dfs(0);
        DOR(i,n,1)
            FOR(j,1,m)
                dp[i][j]=max(dp[i+1][j-1]+p[ori[i]],dp[i+sz[ori[i]]][j]);
        printf("%d\n",dp[1][m]);
    }
    return 0;
}