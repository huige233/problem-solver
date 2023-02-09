#include<iostream>
#include<cstdio>
#include<cstring>
#include<bitset>
#include<set>
using namespace std;
const int N=600,M=2e6+5e5;
int T,n,m,k;
int d[N],v[N];
bool pd[N];
multiset<pair<int,int> > s;//维护 d_min 和 d_max
void solve()
{
    while(s.size())
    {
        multiset<pair<int,int> >::iterator it=s.begin();
        int minv=(*it).first,minb=(*it).second;
        s.erase(it);//取 d_min
        while(minv>=k)//不断用 d_min 单独构成一个 k
        {
            printf("%d %d\n",minb,k);
            minv-=k;
        }
        if(minv && s.size())//还没解完
        {
            it=s.end();it--;
            int maxv=(*it).first,maxb=(*it).second;
            s.erase(it);//取 d_max
            printf("%d %d %d %d\n",minb,minv,maxb,k-minv);
            maxv-=k-minv;//配对
            if(maxv)
                s.insert(make_pair(maxv,maxb));// d_max 还有剩余
        }
    }
}//贪心处理
void parti()
{
    memset(pd,0,sizeof(pd));
    bitset<2*M+1> f[N];
    memset(f,0,sizeof(f));
    for(int i=1;i<=n;i++)
        v[i]=d[i]-k;
    f[0].set(M);// 0  的位置初始化
    for(int i=1;i<=n;i++)
        if(v[i]>=0)
            f[i]|=f[i-1]<<v[i],f[i]|=f[i-1];
        else
            f[i]|=f[i-1]>>(-v[i]),f[i]|=f[i-1];//正负数分别处理，取或不取
    if(!f[n][M-k])//找不到满足条件的集合，无解
    {
        puts("-1");
        return ;
    }
    int now=M-k;
    s.clear();
    for(int i=n;i;i--)//倒着来，找到一个满足条件的集合
        if(f[i-1][now-v[i]])
        {
            s.insert(make_pair(d[i],i));
            pd[i]=1;now-=v[i];
        }
    solve();s.clear();
    for(int i=1;i<=n;i++)//找另一个集合
        if(!pd[i])
            s.insert(make_pair(d[i],i));
    solve();
}
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d%d",&n,&m,&k);
        for(int i=1;i<=n;i++)
            scanf("%d",&d[i]);
        if(m==n-2)
            parti();
        else
        {
            s.clear();
            for(int i=1;i<=n;i++)
                s.insert(make_pair(d[i],i));
            solve();
        }
    }
    return 0;
}