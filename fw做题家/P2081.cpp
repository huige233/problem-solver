#include<bits/stdc++.h>
using namespace std;
#define rep(x,y,z) for (register int x=y; x<=z; x++)
#define downrep(x,y,z) for (register int x=y; x>=z; x--)
#define ms(x,y,z) memset(x,y,sizeof(z))
#define LL long long
#define repedge(x,y) for (register int x=hed[y]; ~x; x=edge[x].nex)
inline int read(){
    int x=0; int w=0; char ch=0;
    while (ch<'0' || ch>'9') w|=ch=='-',ch=getchar();
    while (ch>='0' && ch<='9') x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
    return w? -x:x;
}
const int N=100005;
int nedge,hed[N],n,m,dfn[N],tot,fa[N],pre[N],nex[N],st[N],num,huan[N];
double f[N],g[N],ans,son[N];
map<int,double> e[N];
struct Edge{ int to,nex; double cst; }edge[N<<1];
void addedge(int a,int b,double c){
    edge[nedge].to=b; edge[nedge].nex=hed[a];
    edge[nedge].cst=c; hed[a]=nedge++;
}
void dfs_1(int k){
    dfn[k]=++tot;
    repedge(i,k){
        int v=edge[i].to; if (v==fa[k]) continue;
        if (!dfn[v]) fa[v]=k,dfs_1(v);
        if (dfn[v]<dfn[k]){
            for(int j=k; j!=v; j=fa[j])
            huan[j]=1,st[++num]=j,nex[j]=fa[j];
            huan[v]=1,st[++num]=v,nex[v]=k;
            rep(j,1,num) pre[nex[st[j]]]=st[j];
        }
    }
}
void dfs_2(int k,int pre){
    repedge(i,k){
        int v=edge[i].to; if ((v==pre)||(huan[v])) continue;
        dfs_2(v,k); f[k]+=f[v]+edge[i].cst; son[k]+=1;
    }
    if (son[k]) f[k]/=son[k];
}
void dfs_3(int k,int pre){
    repedge(i,k){
        int v=edge[i].to; if ((v==pre)||(huan[v])) continue; 
        double x=(m==n-1)? ((k==1)? 0:1):(huan[k]? 2:1);
        g[v]=edge[i].cst+((son[k]-1+x)? ((f[k]*son[k]-(f[v]+edge[i].cst)+g[k]*x)/(son[k]-1+x)):0);  
        dfs_3(v,k); 
    }
}
int main(){
    scanf("%d%d",&n,&m); nedge=0; ms(hed,-1,hed);
    rep(i,1,m){ int a,b,c; scanf("%d%d%d",&a,&b,&c);
      addedge(a,b,c); addedge(b,a,c); e[a][b]=e[b][a]=c; }
    dfs_1(1); 
    rep(i,1,num) dfs_2(st[i],st[i]);
    if (!num) dfs_2(1,1);
    rep(i,1,num) {
        double p1=0.5,p2=0.5,s1=0,s2=0;
        for(int j=nex[st[i]]; j!=st[i]; j=nex[j])
        if (nex[j]!=st[i])s1+=e[pre[j]][j],g[st[i]]+=p1*(f[j]+s1)*son[j]/(son[j]+1),p1/=(son[j]+1);
        else s1+=e[pre[j]][j],g[st[i]]+=p1*(f[j]+s1);
		for(int j=pre[st[i]]; j!=st[i]; j=pre[j])
        if (pre[j]!=st[i])s2+=e[nex[j]][j],g[st[i]]+=p2*(f[j]+s2)*son[j]/(son[j]+1),p2/=(son[j]+1);
        else s2+=e[nex[j]][j],g[st[i]]+=p2*(f[j]+s2);
    }
    rep(i,1,num) dfs_3(st[i],st[i]);
    if (!num) dfs_3(1,1);
    if (!num) rep(i,1,n) if (i==1) ans+=f[i]; else ans+=(f[i]*son[i]+g[i])/(son[i]+1);
    if (num>0) rep(i,1,n) if(!huan[i]) ans+=(f[i]*son[i]+g[i])/(son[i]+1);
    else ans+=(f[i]*son[i]+g[i]*2)/(son[i]+2);
    ans/=n; printf("%.5f\n",ans);
    return 0;
}