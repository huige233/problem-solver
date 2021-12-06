#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<map>
#include<set>
#include<vector>
#include<algorithm>
#include<stack>
#include<queue>
using namespace std;
#define INF 1000000000
#define eps 1e-8
#define pii pair<int,int>
#define LL long long int
int m,n,k,T;
int prime[5005],vis[5005];
void getprime()
{
    int num=0;
    for(int i=2;i<5000;i++)
    {
        if(vis[i]==0) prime[num++]=i;
        for(int j=i*i;j<5000;j+=i)
        {
            if(j%i==0) vis[j]=1;
        }
    }
}
int main()
{
    //freopen("in6.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    getprime();
    scanf("%d",&T);
    for(int cas=1;cas<=T;cas++)
    {
        scanf("%d%d",&m,&n);
        k=INF;
        vector<pii>zhi;
        for(int i=0;prime[i]<=m;i++)
        {
            int num=0;
            while(m%prime[i]==0)
            {
                num++;
                m/=prime[i];
            }
            if(num)
            zhi.push_back(make_pair(prime[i],num));
        }
        for(unsigned int i=0;i<zhi.size();i++)
        {
            int t=zhi[i].first,num=0;
            for(int j=n;j>=1;j--)
            {
                int jj=j;
                while(jj%t==0)
                {
                    num++;
                    jj/=t;
                }
            }
            //cout<<'k'<<num<<endl;
            k=min(k,num/(zhi[i].second));
        }
        printf("Case %d:\n",cas);
        if(k)
        printf("%d\n",k);
        else
            printf("Impossible to divide\n");
    }
    //fclose(stdin);
    //fclose(stdout);
    return 0;
}