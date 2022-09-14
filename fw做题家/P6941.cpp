#include<bits/stdc++.h>
#define Tp template<typename Ty>
#define Ts template<typename Ty,typename... Ar>
#define Reg register
#define RI Reg int
#define Con const
#define CI Con int&
#define I inline
#define W while
#define N 500
#define DB double
using namespace std;
int n,d,r;DB f[N+5][N+5],g[N+5][N+5],C[N+5][N+5];
int main()
{
	scanf("%d%d%d",&n,&d,&r);
	RI i,j;for(C[0][0]=i=1;i<=n;++i) for(C[i][0]=j=1;j<=n;++j) C[i][j]=C[i-1][j-1]+C[i-1][j];
	RI k;for(g[0][0]=i=1;i<=n;++i) for(g[i][0]=j=1;j<=d;++j)
		for(k=1;k<=min(i,j);++k) f[i][j]+=C[i][k]*(f[k][j-k]+g[k][j-k]*min(k,r)),g[i][j]+=C[i][k]*g[k][j-k];
	return printf("%.12lf\n",r+f[n][d]/g[n][d]),0;/
}
