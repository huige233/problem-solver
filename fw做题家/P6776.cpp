#include<bits/stdc++.h>
using namespace std ;
#define Next( i, x ) for( register int i = head[x]; i; i = e[i].next )
#define rep( i, s, t ) for( register int i = (s); i <= (t); ++ i )
#define drep( i, s, t ) for( register int i = (t); i >= (s); -- i )
#define re register
#define vi vector<int> 
#define pb push_back
int gi() {
	char cc = getchar() ; int cn = 0, flus = 1 ;
	while( cc < '0' || cc > '9' ) {  if( cc == '-' ) flus = - flus ; cc = getchar() ; }
	while( cc >= '0' && cc <= '9' )  cn = cn * 10 + cc - '0', cc = getchar() ;
	return cn * flus ;
}
const int N = 2e6 + 5 ; 
int n, m ; 
vi L[N], R[N], sz[N], Nw, Id ; 
bool check(vi S, vi nw) {
	if( S.empty() ) return 0 ; 
	vi Lv, Rv, Ls, Rs ;
	vi lv, rv, ls, rs ; int flag = 0 ; 
	for(re int i = 0; i < S.size(); ++ i) {
		int x = S[i], u = nw[i] ; 
		int l = L[x][u], r = R[x][u] ;
		if( !l && !r ) flag = 1 ; 
		if( l && sz[x][r] == 0 ) Lv.pb(x), lv.pb(l) ; 
		if( r && sz[x][l] == 0 ) Rv.pb(x), rv.pb(r) ; 
		if( l && sz[x][r] == 1 ) Ls.pb(x), ls.pb(l) ;
		if( r && sz[x][l] == 1 ) Rs.pb(x), rs.pb(r) ;
	}
	if( flag ) return 1 ; 
	flag = 1 ; 
	flag &= check(Lv, lv),
	flag &= check(Ls, ls),
	flag &= check(Rv, rv),
	flag &= check(Rs, rs) ;
	return flag ; 
}
void Dfs(int id, int x) {
	sz[id][x] = 1 ; int l = L[id][x], r = R[id][x] ; 
	if(l) Dfs(id, l), sz[id][x] += sz[id][l] ; 
	if(r) Dfs(id, r), sz[id][x] += sz[id][r] ; 
}
signed main()
{
	int T = gi() ; 
	while( T-- ) {
		m = gi() ; Id.clear() ; 
		rep( i, 1, m ) {
			n = gi() ; int l, r ; L[i].pb(0), R[i].pb(0), sz[i].pb(0) ;  
			rep( j, 1, n ) l = gi(), r = gi(), L[i].pb(l), R[i].pb(r), sz[i].pb(0) ; 
			Id.pb(i), Dfs(i, 1), Nw.pb(1) ; 
		}
		if( check(Id, Nw) ) puts("Almost Complete") ;
		else puts("No") ;
		rep( i, 1, m ) L[i].clear(), R[i].clear(), sz[i].clear() ;
		Id.clear(), Nw.clear() ; 
	}
	return 0 ;
} 