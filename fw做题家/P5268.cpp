#include <cmath>
#include <cstdio>
#include <algorithm>
#define N 50010
using namespace std;
typedef long long ll;
int si , v[N] , cl[N] , cr[N] , tot;
ll ans[N];
struct data
{
    int l , r , flag , id;
    data() {}
    data(int a , int b , int c , int d) {l = min(a , b) , r = max(a , b) , flag = c , id = d;}
    bool operator<(const data &a)const {return (l - 1) / si == (a.l - 1) / si ? r < a.r : (l - 1) / si < (a.l - 1) / si;}
}a[N << 2];
int main()
{
    int n , m , i , x1 , y1 , x2 , y2 , lp = 0 , rp = 0;
    ll now = 0;
    scanf("%d" , &n) , si = (int)sqrt(n);
    for(i = 1 ; i <= n ; i ++ ) scanf("%d" , &v[i]);
    scanf("%d" , &m);
    for(i = 1 ; i <= m ; i ++ )
    {
        scanf("%d%d%d%d" , &x1 , &y1 , &x2 , &y2) , a[++tot] = data(y1 , y2 , 1 , i);
        if(x1 > 1) a[++tot] = data(x1 - 1 , y2 , -1 , i);
        if(x2 > 1) a[++tot] = data(y1 , x2 - 1 , -1 , i);
        if(x1 > 1 && x2 > 1) a[++tot] = data(x1 - 1 , x2 - 1 , 1 , i);
    }
    sort(a + 1 , a + tot + 1);
    for(i = 1 ; i <= tot ; i ++ )
    {
        while(lp < a[i].l) lp ++ , now += cr[v[lp]] , cl[v[lp]] ++ ;
        while(rp < a[i].r) rp ++ , now += cl[v[rp]] , cr[v[rp]] ++ ;
        while(lp > a[i].l) cl[v[lp]] -- , now -= cr[v[lp]] , lp -- ;
        while(rp > a[i].r) cr[v[rp]] -- , now -= cl[v[rp]] , rp -- ;
        ans[a[i].id] += a[i].flag * now;
    }
    for(i = 1 ; i <= m ; i ++ ) printf("%lld\n" , ans[i]);
    return 0;
}