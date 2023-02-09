#include<bits/stdc++.h>
#define ll  long long
 
using namespace std;
ll slv(ll a,ll b,ll p)
{
	if(b==1)return a;
	ll x=slv(a,b/2,p);
	if(b%2)return x*x%p*a%p;
	else return x*x%p;
}
 
int main()
{
	ll b,p,k;
	scanf("%lld%lld%lld",&b,&p,&k);
	printf("%lld^%lld mod %lld=%lld",b,p,k,slv(b,p,k));
	return 0;
    
}