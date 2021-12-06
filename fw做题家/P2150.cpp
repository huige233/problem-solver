//状压DP 
#include <cstdio>
#include <algorithm>
#define maxn 1000
#define ll long long
using namespace std;
ll N, P, f[maxn][maxn], g[maxn][maxn], tp[maxn], hp[maxn], mark[maxn], prime[maxn],
    num[maxn], h[maxn][maxn];
bool cmp(ll a, ll b){return hp[a]<hp[b];}
void init()
{
    ll i, j;
    scanf("%lld%lld",&N,&P);
    for(i=2;i<=N;i++)
    {
        if(!mark[i])prime[++prime[0]]=i;
        for(j=1;j<=prime[0] and i*prime[j]<=N;j++)
        {
            mark[i*prime[j]]=1;
            if(i%prime[j]==0)break;
        }
    }
    for(i=2;i<=N;i++)
    {
        for(j=1;prime[j]*prime[j]<=N;j++)if(i%prime[j]==0)tp[i]|=(1<<j-1);
        for(;prime[j]<=i and j<=prime[0];j++)if(i%prime[j]==0)hp[i]=prime[j];
    }
    for(i=2;i<=N;i++)num[i]=i;
    sort(num+2,num+N+1,cmp);
}
void dp()
{
    ll l, r, p, i, j, k, ans=0;
    f[0][0]=1;
    for(l=2;l<=N;l=r+1)
    {
        for(r=l;hp[num[r]]==hp[num[l]] and r<=N;r++);r--;
        if(hp[num[l]]!=0)
        {
            for(i=0;i<256;i++)for(j=0;j<256;j++)g[i][j]=f[i][j];
            for(p=l;p<=r;p++)
            {
                k=tp[num[p]];
                for(i=255;i>=0;i--)
                    for(j=255;j>=0;j--)
                    {
                        if((i&j)or(j&k))continue;
                        g[i|k][j]+=g[i][j];
                    }
            }
            for(i=0;i<256;i++)for(j=0;j<256;j++)f[i][j]=(g[i][j]+g[j][i]-f[i][j])%P;
        }
        else
        {
            for(p=l;p<=r;p++)
            {
                k=tp[num[p]];
                for(i=255;i>=0;i--)
                    for(j=255;j>=0;j--)
                    {
                        if(i&j)continue;
                        f[i][j]%=P;
                        if((j&k)==0)f[i|k][j]+=f[i][j];
                        if((i&k)==0)f[i][j|k]+=f[i][j];
                    }
            }
        }
    }
    for(i=0;i<256;i++)for(j=0;j<256;j++)ans=(ans+f[i][j])%P;
    printf("%lld",((ans%P)+P)%P);
}
int main()
{
    init();
    dp();
    return 0;
}