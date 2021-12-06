#include <cstdio>
#include <algorithm>
#define ls ch[now][0]
#define rs ch[now][1]
#define fa par[now]
#define ll long long
const int N=1e5+10;
const int M=4e4+10;
int n,m,k;
std::pair <int,int > dx[N];
ll sum[M],dat[M],siz[M],ans;int ch[M][2],par[M],root;
int build(int l,int r)
{
    if(l>r) return 0;
    if(l==r) {siz[l]=1;return l;}
    int now=l+r>>1;
    ls=build(l,now-1);
    if(ls) par[ls]=now;
    rs=build(now+1,r);
    if(rs) par[rs]=now;
    siz[now]=siz[ls]+siz[rs]+1;
    return now;
}
void updata(int now)
{
    sum[now]=dat[now]*(siz[ls]+1ll)*(siz[rs]+1ll)+sum[ls]+sum[rs];
    siz[now]=siz[ls]+siz[rs]+1;
}
int identity(int now){return ch[fa][1]==now;}
void connect(int f,int now,int typ){fa=f;ch[f][typ]=now;}
void Rotate(int now)
{
    int p=fa,typ=identity(now);
    if(p==root) root=now;
    connect(p,ch[now][typ^1],typ);
    connect(par[p],now,identity(p));
    connect(now,p,typ^1);
    updata(p),updata(now);
}
int main()
{
    scanf("%d%d%d",&n,&m,&k);
    root=build(1,m);
    for(int i=1;i<=k;i++)
        scanf("%d%d",&dx[i].first,&dx[i].second);
    std::sort(dx+1,dx+1+k);
    int las=1;dat[0]=n+1;
    for(int i=1;i<=k;i++)
    {
        while(las!=dx[i].first)
            ans+=sum[root],++las;
        int now=dx[i].second;
        dat[now]=dx[i].first;
        while(dat[fa]<dat[now])
            Rotate(now);
        while(now) updata(now),now=fa;
    }
    while(las<=n)
        ans+=sum[root],++las;
    printf("%lld\n",ans);
    return 0;
}