#include<bits/stdc++.h>
using namespace std;
#define rep(i, l, r) for(int i = l; i <= r; ++i)
#define dep(i, l, r) for(int i = r; i >= l; --i)
const int N = 250 + 5;
const long long inf = 100000000000000;
int n, m, T, k, u, v, w, c[N];
long long tmp;
struct mat{
    long long g[N][N];
    void clear(){
        rep(i, 1, n) rep(j, 1, n) g[i][j] = -inf;
    }
}tr, dp, f[N];
struct node{
    int t, x, y;
}a[N];
int read(){
    char c; int x = 0, f = 1;
    c = getchar();
    while(c > '9' || c < '0'){ if(c == '-') f = -1; c = getchar();}
    while(c >= '0' && c <= '9') x = x * 10 + c - '0', c = getchar();
    return x * f;
}
int P(int x, int y){
    return 5 * (x - 1) + y;
}
mat mul(mat a, mat b){
    mat c; c.clear();
    rep(k, 1, n) if(a.g[1][k] >= 0){
        rep(j, 1, n) if(b.g[k][j] >= 0) c.g[1][j] = max(c.g[1][j], a.g[1][k] + b.g[k][j]);
    } 
    return c;
}
mat Mul(mat a, mat b){
    mat c; c.clear(); 
    rep(i, 1, n) rep(k, 1, n) if(a.g[i][k] >= 0){
        rep(j, 1, n) if(b.g[k][j] >= 0) c.g[i][j] = max(c.g[i][j], a.g[i][k] + b.g[k][j]);
    } 
    return c;
}
mat Qpow(mat a, int b){
    mat ans = a; --b; // 注意这里
    while(b){
        if(b & 1) ans = Mul(ans, a);
        a = Mul(a, a), b >>= 1;
    }
    return ans;
}
bool cmp(node a, node b){
    return a.t < b.t;
}
void solve(int T, int x, int y){
    dep(i, 0, 29) if(T >= (1 << i)) dp = mul(dp, f[i]), T -= (1 << i);
    if(dp.g[1][P(x, 5)] >= 0) dp.g[1][P(x, 5)] += y; 
}
int main(){
    n = read(), m = read(), T = read(), k = read();
    rep(i, 1, n) c[i] = read();
    rep(i, 1, 5 * n) rep(j, 1, 5 * n) tr.g[i][j] = -inf;
    rep(i, 1, n) rep(j, 1, 4) tr.g[P(i, j)][P(i, j + 1)] = (j == 4 ? c[i] : 0);
    rep(i, 1, m) u = read(), v = read(), w = read(), tr.g[P(u, 5)][P(v, 5 - w + 1)] = (w == 1 ? c[v] : 0);
    rep(i, 1, k) a[i].t = read(), a[i].x = read(), a[i].y = read();
    n = 5 * n, f[0] = tr, a[++k].t = T, a[k].x = 1, a[k].y = 0;
    rep(i, 1, 29) f[i] = Mul(f[i - 1], f[i - 1]);
    sort(a + 1, a + k + 1, cmp);
    rep(i, 1, n) dp.g[1][i] = -inf;
    dp.g[1][5] = c[1];
    rep(i, 1, k) solve(a[i].t - a[i - 1].t, a[i].x, a[i].y);
    printf("%lld", dp.g[1][5] >= 0 ? dp.g[1][5] : -1);
    return 0;
}