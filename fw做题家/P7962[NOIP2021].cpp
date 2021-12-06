#include <stdio.h>
#include <algorithm>
#include <string.h>
#include <iostream>
#include <assert.h>
using namespace std;

#define re register
#define sf scanf
#define pf printf
#define nl() putchar('\n')
#define ll long long
#define _for(i, a, b) for(re int (i) = (a); (i) < (b); ++(i))
#define _rfor(i, a, b) for(re int (i) = (a); (i) <= (b); ++(i))
#define inf 0x7ffffffffffffffll
#define maxn 10005
#define maxx 500005

int rdnt(){
   re int x = 0, sign = 1;
   re char c = getchar();
   while (c < '0' || c > '9') { if (c == '-') sign = -1; c = getchar(); }
   while (c >= '0' && c <= '9') x = (x<<3) + (x<<1) + (c ^ 48), c = getchar();
   return x * sign;
}

ll  a[maxn], d[maxn], s[maxn], f[maxx];

inline void ud(re ll &x, re ll y){ if (y < x) x = y; }

int main(){
   #ifndef ONLINE_JUDGE
   freopen("variance.in", "r", stdin);
   freopen("variance.out", "w", stdout);
   #endif

   re int n = rdnt(), rg = 0; re ll mx = 0, ma = a[1] = rdnt();
   _rfor(i, 2, n) d[i-1] = (a[i] = rdnt())-a[i-1], ma = max(ma, a[i]);
   _rfor(x, 1, ma*n) f[x] = inf; f[0] = s[0]= 0;
   sort(d+1, d+n);
   _for(i, 1, n){
   	s[i] = s[i-1] + d[i];
   	if (d[i] == 0) continue;
   	for(re int x = mx; x >= 0; --x){
   		if (f[x] == inf) continue;
   		ud(f[x+i*d[i]], f[x] + 2*x*d[i] + i*d[i]*d[i]);
   		ud(f[x+s[i]], f[x] + s[i]*s[i]);
   		mx = max(mx, max(x+i*d[i], x+s[i]));
   		f[x] = inf;
   	}
   }
   re ll ans = inf;
   _rfor(x, 0, mx) if (f[x] < inf) ud(ans, n*f[x] - (ll)x*x);
   pf("%lld\n", ans);

   return 0;
}