#include<cstdio>
#include<algorithm>
using namespace std;const int N=1e3+10;typedef long long ll;const ll mod=1e9+7;
inline ll po(ll a,ll p){ll r=1;for(;p;p>>=1,a=a*a%mod)if(p&1)r=r*a%mod;return r;}
int n;int m;char mde[N];
struct cmp//手写复数类 
{
    ll r;ll v;
    friend cmp operator +(cmp a,cmp b){return (cmp){(a.r+b.r)%mod,(a.v+b.v)%mod};}
    friend cmp operator *(cmp a,cmp b){return (cmp){(a.r*b.r+5*a.v*b.v)%mod,(a.r*b.v+a.v*b.r)%mod};}
    friend cmp operator -(cmp a,cmp b){return (cmp){(a.r+mod-b.r)%mod,(a.v+mod-b.v)%mod};}
    friend cmp operator /(cmp a,cmp b)
    {
        ll inv=po((b.r*b.r+mod-5*b.v*b.v%mod)%mod,mod-2);
        return (cmp){(a.r*b.r%mod+mod-5*a.v*b.v%mod)*inv%mod,(a.v*b.r%mod+mod-a.r*b.v%mod)*inv%mod};
    }
}dp[N],mi[N],tmi[N],cst[N];
inline cmp po(cmp a,int p){cmp r=(cmp){1,0};for(;p;p>>=1,a=a*a)if(p&1)r=r*a;return r;}
inline cmp solve(cmp bas)//计算其中的一个幂次 
{
    tmi[0]=mi[0]=(cmp){1,1};tmi[1]=mi[1]=bas;
    for(int i=2;i<=9;i++)tmi[i]=tmi[i-1]*tmi[1];
    for(int i=0;i<=n;i++)cst[i]=(cmp){1,0};dp[0]=(cmp){1,0};
    for(int i=1;i<=n;i++)
    {
        dp[i]=(cmp){0,0};
        for(int j=0;j<i;j++)cst[j]=po(cst[j],10)*tmi[mde[i]-'0'];
        for(int j=0;j<i;j++)dp[i]=dp[i]+dp[j]*cst[j];
    }dp[n]=dp[n]/bas;dp[n]=dp[n]*(cmp){0,400000003};return dp[n];
}
int main()
{
    scanf("%d",&n);scanf("%s",mde+1);//然后直接暴力套通项公式就行了 
    printf("%lld",(solve((cmp){500000004,500000004})-solve((cmp){500000004,500000003})).r);
    return 0;
}