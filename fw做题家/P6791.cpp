#include<bits/stdc++.h>
#define Tp template<typename Ty>
#define Ts template<typename Ty,typename... Ar>
#define Reg register
#define RI Reg int
#define Con const
#define CI Con int&
#define I inline
#define W while
#define SZ 87
#define LL long long
using namespace std;
int p[SZ+5];LL k,n,Fib[SZ+5];
namespace FastIO
{
	#define FS 100000
	#define tc() (FA==FB&&(FB=(FA=FI)+fread(FI,1,FS,stdin),FA==FB)?EOF:*FA++)
	char oc,FI[FS],*FA=FI,*FB=FI;
	Tp I void read(Ty& x) {x=0;W(!isdigit(oc=tc()));W(x=(x<<3)+(x<<1)+(oc&15),isdigit(oc=tc()));}
	Ts I void read(Ty& x,Ar&... y) {read(x),read(y...);}
}using namespace FastIO;
LL f[SZ+5][SZ+5][2];I LL DP(CI x,CI lim,CI lst=0,CI fg=0)//数位DP
{
	if(x<lim) return 1;if(fg&&f[x][lim][lst]) return f[x][lim][lst];//记忆化
	LL t=DP(x-1,lim,0,fg|p[x])+((fg|p[x])&&!lst?DP(x-1,lim,1,fg):0);return fg&&(f[x][lim][lst]=t),t;//填0或填1，不能有连续两个1
}
int main()
{
	RI i,j;for(Fib[1]=1,Fib[2]=2,i=3;i<=SZ;++i) Fib[i]=Fib[i-2]+Fib[i-1];//预处理斐波那契数
	RI Tt;LL x;read(Tt);W(Tt--)
	{
		for(read(k,n),x=n-1,i=SZ;i;--i) p[i]=x>=Fib[i]?(x-=Fib[i],1):0;//将n-1斐波那契分解（给石子数减1输赢转化）
		for(i=1;Fib[i]<=k;++i);printf("%lld\n",n-DP(SZ,i));//找到大于k的最小的斐波那契数去DP，总方案数减非法方案数
	}return 0;
}