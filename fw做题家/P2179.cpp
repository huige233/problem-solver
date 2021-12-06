#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
#include<cmath>
#include<map>
#define Redge(u) for (int k = h[u],to; k; k = ed[k].nxt)
#define REP(i,n) for (int i = 1; i <= (n); i++)
#define mp(a,b) make_pair<int,int>(a,b)
#define cls(s) memset(s,0,sizeof(s))
#define cp pair<int,int>
#define LL long long int
using namespace std;
const int maxn = 10005,maxm = 100005;
const double eps = 1e-13,INF = 1e12;
int n;
double E,v1[maxn],v[maxn],s[maxn],k[maxn];
inline double f(int i,double lam){
	return 2 * lam * k[i] * v[i] * v[i] * (v[i] - v1[i]) + 1;
}
inline double cal(double lam){
	REP(i,n){
		double l = max(v1[i],0.0),r = INF;
		while (r - l > eps){
			v[i] = (l + r) / 2.0;
			if (f(i,lam) >= 0) l = v[i];
			else r = v[i];
		}
		v[i] = l;
	}
	double re = 0;
	REP(i,n) re += s[i] * k[i] * (v[i] - v1[i]) * (v[i] - v1[i]);
	return re;
}
int main(){
	scanf("%d%lf",&n,&E);
	REP(i,n) scanf("%lf%lf%lf",&s[i],&k[i],&v1[i]);
	double l = -INF,r = 0,mid;
	while (r - l > eps){
		mid = (l + r) / 2.0;
		if (cal(mid) >= E) r = mid;
		else l = mid;
	}
	cal(l);
	double ans = 0;
	REP(i,n) ans += s[i] / v[i];
	printf("%.10lf\n",ans);
	return 0;
}