#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#define ll long long
using namespace std;
const int MAXN = 100005;
ll init() {
    ll rv = 0, fh = 1;
    char c = getchar();
    while(c < '0' || c > '9') {
        if(c == '-') fh = -1;
        c = getchar();
    }
    while(c >= '0' && c <= '9') {
        rv = (rv<<1) + (rv<<3) + c - '0';
        c = getchar();
    }
    return fh * rv;
}
struct edge{
    int to, nxt;
}e[MAXN << 1];
int n, m, head[MAXN], nume, rot, fa[MAXN], id[MAXN];
ll ans, wei[MAXN], mon[MAXN], siz[MAXN], sum[MAXN]; 
void adde(int from, int to) {
    e[++nume].to = to;
    e[nume].nxt = head[from];
    head[from] = nume;
}
struct LT{
    struct node{
        int l, r;
        ll val, dist;
    }a[MAXN];
    int merge(int u, int v) {
        if(!u || !v) return u + v;
        if(a[u].val < a[v].val) swap(u, v);
        int &ur = a[u].r, &ul = a[u].l;
        ur = merge(ur, v);
        if(a[ul].dist < a[ur].dist) swap(ul, ur);
        a[u].dist = a[ur].dist + 1;
        return u;
    }
    void erase(int &u) {
        u = merge(a[u].l, a[u].r);
    }
}lt;
void dfs(int u) {
    id[u] = u;
    siz[u] = 1;
    sum[u] = mon[u];
    lt.a[u].val = mon[u];
    for(int i = head[u]; i; i = e[i].nxt) {
        int v = e[i].to;
        dfs(v);
        sum[u] += sum[v];
        siz[u] += siz[v];
        id[u] = lt.merge(id[u], id[v]);
    }
    while(sum[u] > m && siz[u]) {
        siz[u]--;
        sum[u] -= lt.a[id[u]].val;
        lt.erase(id[u]);
    }
    ans = max(ans, siz[u] * wei[u]);
}
int main() {
    n = init(); m = init();
    for(int i = 1; i <= n; i++) {
        fa[i] = init();
        if(fa[i]) adde(fa[i], i);
        else rot = i;
        mon[i] = init(); wei[i] = init();
    }
    dfs(rot);
    /*for(int i = 1; i <= n; i++) {
        printf("%lld %lld\n", siz[i], sum[i]);
    }*/
    cout << ans << endl;
    return 0;
}