#include<bits/stdc++.h>
#define N 205
#define int long long
using namespace std;

int n,m,p,k;
int c[N][N];
struct nd{int a[N][N];}b,t,now;

inline int POW(int a,int b,int ans=1){
    for(;b;b>>=1,a=1ll*a*a%p)
        if(b&1) ans=1ll*ans*a%p;
    return ans;
}
void init()
{
    for(int i=0;i<=m;i++)
        for(int j=0;j<=i;j++)
            c[i][j]=j ? (c[i-1][j-1]+c[i-1][j])%p : 1,now.a[i][j]=1ll*k*c[i][j]%p;
    for(int i=0;i<=m;i++) b.a[i][0]=1;
    now.a[m+1][m+1]=now.a[m+1][m]=1;
}
inline nd mul(nd a,nd b){
    memset(t.a,0,sizeof t.a);
    for(int i=0;i<=m+1;i++)
        for(int k=0;k<=m+1;k++) if(a.a[i][k])
            for(int j=0;j<=m+1;j++) if(b.a[k][j])
                t.a[i][j]=(1ll*a.a[i][k]*b.a[k][j]+t.a[i][j])%p;
    return t;   
}
nd POW(nd a,int b){
    nd ans=a;b--;
    for(;b;b>>=1,a=mul(a,a))
        if(b&1) ans=mul(ans,a);
    return ans;
}
int work(){
    init(); b=mul(POW(now,n-1),b);
    return b.a[m+1][0]+b.a[m][0];
}
int cal(int b,int n){
    if(n==1) return b;
    if(n&1) return 1ll*(cal(b,n-1)+1)*b%p;
    return 1ll*cal(b,n>>1)*(1+POW(b,n>>1))%p;
}
int work2()
{
    int now=0;
    for(int i=1;i<=p;i++)
        now=(now+1ll*POW(i,m)%p*POW(k,i-1))%p;
    now=1ll*now*(cal(POW(k,p),n/p-1)+1)%p;
    for(int i=n-n%p+1;i<=n;i++)
        now=(now+1ll*POW(i,m)%p*POW(k,i-1))%p;
    return now;
}
signed main(){
    cin>>n>>m>>p;k=(m*m-3*m+3)%p;
    int ans=m<=200 ? work() : work2();
    cout<<1ll*ans*POW(2,m)%p*m*(m-1)%p;
}