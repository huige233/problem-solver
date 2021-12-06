#include<cstdio>
#include<iostream>
#define il inline
#define gc getchar
using namespace std;
typedef long long ll;
il ll read() {
	ll x=0,sign=0;char ch=gc();
	for(;ch>'9'||ch<'0';ch=gc())sign=ch=='-';
	for(;ch<='9'&&ch>='0';ch=gc())x=(x<<3)+(x<<1)+ch-48;
	return sign?-x:x;
}
const int mod=998244353;
const int N=40;
const int M=1e2+10;
int n,m,d;
int v[M];
ll ans=0;
ll C[N][N];
ll f[M][N][N<<1][N];
il ll fastPow(ll base,ll x) {
	ll ret=1;
	while(x) {
		if(x&1) ret=ret*base%mod;
		base=base*base%mod;
		x>>=1;
	}
	return ret;
}
il ll Popcount(int x) {
    ll ret=0;
	while(x) {
		ret+=x&1;
        x>>=1;
	}
    return ret;
}
int main() {
	n=read(),m=read(),d=read();
	for(int i=0;i<=m;i++)
		v[i]=read();
	for(int i=0;i<=n;i++) C[i][0]=C[i][i]=1;
	for(int i=1;i<=n;i++)
		for(int j=1;j<i;j++)
			C[i][j]=(C[i-1][j-1]+C[i-1][j])%mod; // 预处理组合数
	for(int i=0;i<=n;i++)
		f[0][i][i][i&1]=fastPow(v[0],i)*C[n][i]%mod; // i=0时的初值
	for(int i=0;i<m;i++)
		for(int j=0;j<=n;j++)
			for(int k=0;k<=n<<1;k++)
				for(int l=0;l<=d;l++)
					for(int p=0;j+p<=n;p++) {
						if(l+((k>>1+p)&1)>d) continue;
						f[i+1][j+p][(k>>1)+p][l+(((k>>1)+p)&1)]+=f[i][j][k][l]*fastPow(v[i+1],p)%mod*C[n-j][p]%mod;
						f[i+1][j+p][(k>>1)+p][l+(((k>>1)+p)&1)]%=mod; // 转移与取模
					}
	for(int i=0;i<=n<<1;i++)
		for(int j=0;j<=d-Popcount(i>>1);j++)
			ans=(ans+f[m][n][i][j])%mod; // 统计答案
	printf("%lld\n",ans);
	return 0;
}