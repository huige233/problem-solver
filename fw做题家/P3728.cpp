#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<vector>
#define ll long long
#define llu unsigned ll
//#define int ll
using namespace std;
const int maxn=1001000;
int nt[maxn][26];
ll sum[maxn],n,k;
char str[maxn];
int main(void)
{
    scanf("%lld%lld",&n,&k);
    scanf("%s",str+1);
    for(int i=n-1;i>=0;i--)
    {
        for(int j=0;j<26;j++)
            nt[i][j]=nt[i+1][j];
        nt[i][str[i+1]-'a']=i+1;
    }
    for(int i=n;i>=0;i--)
    {
        sum[i]=1;
        for(int j=0;j<26;j++)
            if(nt[i][j])
                sum[i]+=sum[nt[i][j]];
        if(sum[i]>k) sum[i]=k;
    }
    int rt=0;
    while(1)
    {
        if(k==0) break;
        for(int i=0;i<26;i++)
        {
            if(nt[rt][i]==0) continue;
            if(k>sum[nt[rt][i]]) k-=sum[nt[rt][i]];
            else
            {
                putchar(i+'a');
                k--;
                rt=nt[rt][i];
                break;
            }
        }
    }
    putchar('\n');
    return 0;
}
