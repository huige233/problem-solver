#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
typedef long long ll;
const int N=2e6+5;
int n,C,col[N],out[N],head[N],tot; 
ll ans;
struct Suffix_Automaton{
	int cnt,fail[N],len[N],ch[N][10];
	Suffix_Automaton(){cnt=1;}
	struct node{
		int to,next;
	}a[N];
	void add(int x,int y)
	{
		a[++tot]=(node){y,head[x]};
		head[x]=tot;
	}
	int insert(int x,int c)
	{
		if(ch[x][c])
		{
			int p=x,q=ch[p][c];
			if(len[p]+1==len[q]) return q;
			else
			{
				int now=++cnt;
				len[now]=len[p]+1;
				for(int i=0;i<10;i++)
					ch[now][i]=ch[q][i];
				while(p&&ch[p][c]==q)
				{
					ch[p][c]=now;
					p=fail[p];
				}
				fail[now]=fail[q];
				fail[q]=now;
				return now;
			}
		}
		int now=++cnt,p=x;
		len[now]=len[x]+1;
		while(p&&!ch[p][c])
		{
			ch[p][c]=now;
			p=fail[p];
		}
		if(p)
		{
			int q=ch[p][c];
			if(len[p]+1==len[q]) fail[now]=q;
			else
			{
				len[++cnt]=len[p]+1;
				for(int i=0;i<10;i++)
					ch[cnt][i]=ch[q][i];
				fail[cnt]=fail[q];
				fail[now]=fail[q]=cnt;
				while(p&&ch[p][c]==q)
				{
					ch[p][c]=cnt;
					p=fail[p];
				}
			}
		}
		else fail[now]=1;
		return now;
	}
	void dfs(int x,int fa,int p)
	{
		int nowp=insert(p,col[x]);  //记录x在SAM的位置
		for(int i=head[x];i;i=a[i].next)
		{
			int qwq=a[i].to;
			if(qwq==fa) continue;
			dfs(qwq,x,nowp);
		}
	}
	void solve()
	{
		for(int i=2;i<=cnt;i++)
			ans+=len[i]-len[fail[i]];
		printf("%lld",ans);
	}
}SAM;
int main()
{
	scanf("%d%d",&n,&C);
	for(int i=1;i<=n;i++)
		scanf("%d",&col[i]);
	for(int i=1,x,y;i<n;i++)
	{
		scanf("%d%d",&x,&y);
		SAM.add(x,y); SAM.add(y,x);
		out[x]++; out[y]++;
	}
	for(int i=1;i<=n;i++)
		if(out[i]==1) SAM.dfs(i,0,1);
	SAM.solve();
	return 0;
}