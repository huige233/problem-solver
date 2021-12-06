#include<cstdio>
#include<string>
#define R register int
#define N 8005
#define M 20005
#define ll long long
#define inf 0x3f3f3f3f
using namespace std;
struct arr{int to,nxt;}e[M<<2];
int n,m,head[N<<1],dfn[N<<1],low[N<<1],stack[N<<1],top,cnt,tot,db[N<<1],scc[N<<1];
bool bz[N<<1];
int max(int a,int b) {return a>b?a:b;}
int min(int a,int b) {return a<b?a:b;}
void read(int &x)
{
	x=0;int f=1;char ch=getchar();
	while (!isdigit(ch)) {if (ch=='-') f=-1;ch=getchar();}
	while (isdigit(ch)) x=(x<<1)+(x<<3)+(ch^48),ch=getchar();x*=f;
}
void add(int u,int v)
{
	e[++cnt].to=v;e[cnt].nxt=head[u];
	head[u]=cnt;
}
void tarjan(int u)
{
	low[u]=dfn[u]=++cnt;stack[++top]=u;bz[u]=1;
	for (R i=head[u];i;i=e[i].nxt)
	{
		int v=e[i].to;
		if (!dfn[v]) tarjan(v),low[u]=min(low[u],low[v]);
		else if (bz[v]) low[u]=min(low[u],dfn[v]);
	}
	if (low[u]==dfn[u])
	{
		++tot;
		while (stack[top]!=u)
		{
			scc[stack[top]]=tot;bz[stack[top--]]=0;
		}
		scc[stack[top]]=tot;bz[stack[top--]]=0;
	}
}
int main()
{
	read(n);n<<=1;read(m);
	for (R i=1;i<=n;++i)
		if (i&1) db[i]=i+1;else db[i]=i-1;
	for (R x,y,i=1;i<=m;++i)
	{
		read(x);read(y);
		add(x,db[y]);add(y,db[x]);
	}
	cnt=0;
	for (R i=1;i<=n;++i)
		if (!dfn[i]) tarjan(i);
	for (R i=1;i<=n;i+=2)
		if (scc[i]==scc[i+1]) {printf("NIE\n");return 0;}
	for (R i=1;i<=n;i+=2)
		if (scc[i]<scc[i+1]) printf("%d\n",i);else printf("%d\n",i+1);
	printf("\n");
 	return 0;
}