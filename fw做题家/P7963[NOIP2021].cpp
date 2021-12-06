#include<bits/stdc++.h>
#define gc getchar()
#define pc putchar
#define li long long
#define md int mid = (l + r) >> 1
#define ln ls[q],l,mid
#define rn rs[q],mid + 1,r
using namespace std;
inline void file(char *s){
	char c[50];
	sprintf(c,"%s.in",s);
	freopen(c,"r",stdin);
	sprintf(c,"%s.out",s);
	freopen(c,"w",stdout);
}
int t,n,m,q;
int e[4][200010],ans[100010],qz[200010];

struct node{
	int col,lv,x,y,id;
}a[100010],aa[100010];
inline bool operator < (node x,node y){
	return x.lv == y.lv ? x.id < y.id : x.lv < y.lv;
}
char ch[200010];
#define pos(x,y) (((x) - 1) * m + (y))
#define pos2(x,y) (((y) - 1) * n + (x))
#define tox(x) (((x) - 1) / m + 1)
#define toy(x) (((x) - 1) % m + 1)
void mgg(int,int);
struct bcj{
	int f[200010],sz[200010],mx[200010],mn[200010];
	inline int getf(int x){
		return f[x] == x ? x : f[x] = getf(f[x]);
	}
	inline void mg(int u,int v,bool fg = 0){
		u = getf(u),v = getf(v);
		if(u == v) return;
		if(sz[u] > sz[v]) swap(u,v);
		sz[v] += sz[u];f[u] = v;
		mx[v] = max(mx[v],mx[u]);
		mn[v] = min(mn[v],mn[u]);
		if(fg) mgg(u,v);
	}
	inline void init(int p){
		for(int i = 1;i <= p;++i) f[i] = mx[i] = mn[i] = i,sz[i] = 1;
	}
	inline int chksz(int x){return sz[getf(x)];}
	inline int chkmx(int x){return mx[getf(x)];}
	inline int chkmn(int x){return mn[getf(x)];}
}bc[3];
struct xds{
	int rt[200010],ls[8000010],rs[8000010],sz[8000010],cnt;
	inline void init(){
		memset(rt,0,sizeof(rt));
		for(int i = 1;i <= cnt;++i) ls[i] = rs[i] = sz[i] = 0; 
		cnt = 0;
	}
	int ins(int q,int l,int r,int x,int v = 1){
		if(!q) q = ++cnt;
		if(l == r){
			if(v == -1) return 0;
			if(!sz[q]) ++sz[q]; 
			return q;
		}
		md;
		if(mid >= x) ls[q] = ins(ln,x,v);
		else rs[q] = ins(rn,x,v);
		sz[q] = sz[ls[q]] + sz[rs[q]];
		return sz[q] ? q : 0;
	}
	int mg(int p,int q,int l,int r,int op = -1){
		if(!p || !sz[p]) return q;
		if(!q || !sz[q]) return p;
		if(l == r){
			sz[q] = min(1,sz[q] + sz[p]);
			return q;
		}
		md;
		ls[q] = mg(ls[p],ln,op);
		rs[q] = mg(rs[p],rn,op);
		sz[q] = sz[ls[q]] + sz[rs[q]];
		return q;
	}
	int qy(int q,int l,int r,int x){
		if(!q || !x) return 0;
		if(l == r) return sz[q];
		md;
		if(mid >= x) return qy(ln,x);
		return sz[ls[q]] + qy(rn,x);
	}
	int qy2(int q,int l,int r,int x){
		if(!q || !x) return 0;
		if(l == r) return sz[q];
		md;
		if(mid >= x) return qy2(ln,x);
		return qy2(rn,x);
	}
	int cx(int q,int l,int r){
		return qy(rt[q],1,n * m,r) - qy(rt[q],1,n * m,l - 1);
	}
}xd[4];
void mgg(int u,int v){
	xd[0].rt[v] = xd[0].mg(xd[0].rt[u],xd[0].rt[v],1,q);
	xd[1].rt[v] = xd[1].mg(xd[1].rt[u],xd[1].rt[v],1,q);
	xd[2].rt[v] = xd[2].mg(xd[2].rt[u],xd[2].rt[v],1,n * m);
	xd[3].rt[v] = xd[3].mg(xd[3].rt[u],xd[3].rt[v],1,n * m);
}

inline void init(){
	memset(e,0,sizeof(e));
	memset(qz,0,sizeof(qz));
	memset(ans,0,sizeof(ans));
	for(int i = 0;i < 3;++i) bc[i].init(n * m);
	for(int i = 0;i < 4;++i) xd[i].init();
}
int dx[4] = {-1,0,1,0},dy[4] = {0,-1,0,1};
inline bool caneat(int x,int y){
	if(!y || y >= x) return 0;
	node ax = a[x],ay = a[y];
	return ax.col != ay.col && ax.lv >= ay.lv;
}
int main(){
	//file("chess");
	int i,j,k,id,tx,ty,nxt;
	scanf("%d",&t);
	while(t--){
		scanf("%d%d%d",&n,&m,&q);
		init();
		for(i = 1;i <= n;++i){
			scanf("%s",ch + 1);
			for(j = 1;j < m;++j){
				e[1][pos(i,j + 1)] = e[3][pos(i,j)] = ch[j] - '0';
			}  
		}
		for(i = 1;i < n;++i){
			scanf("%s",ch + 1);
			for(j = 1;j <= m;++j){
				e[0][pos(i + 1,j)] = e[2][pos(i,j)] = ch[j] - '0';
			} 
		}
		for(i = 1;i <= q;++i){
			scanf("%d%d%d%d",&a[i].col,&a[i].lv,&a[i].x,&a[i].y);
			a[i].id = i;
		}
		sort(a + 1,a + q + 1);
		for(i = 1;i <= q;++i) a[i].lv = i;
		for(i = 1;i <= q;++i) aa[a[i].id] = a[i];
		for(i = 1;i <= q;++i) a[i] = aa[i];
		for(i = 1;i <= q;++i) qz[pos(a[i].x,a[i].y)] = i;
		for(i = 1;i <= n;++i){
			for(j = 1;j <= m;++j){
				id = pos(i,j);
				for(k = 0;k < 4;++k) if(e[k][id] > 1){
					tx = i + dx[k];ty = j + dy[k];nxt = pos(tx,ty);
					if(!qz[id] && !qz[nxt]) bc[e[k][id] == 3 ? 0 : k % 2 + 1].mg(id,nxt);
				}
			}
		}
		for(i = 1;i <= n;++i){
			for(j = 1;j <= m;++j){
				id = pos(i,j);int iid = bc[0].getf(id);
				xd[2].rt[iid] = xd[2].ins(xd[2].rt[iid],1,n * m,pos2(i,j));
				xd[3].rt[iid] = xd[3].ins(xd[3].rt[iid],1,n * m,id);
				for(k = 0;k < 4;++k) if(e[k][id] == 3){
					tx = i + dx[k];ty = j + dy[k];nxt = pos(tx,ty);
					if(qz[nxt]){
						int tmp = a[qz[nxt]].col;
						xd[tmp].rt[iid] = xd[tmp].ins(xd[tmp].rt[iid],1,q,a[qz[nxt]].lv);
					}
				}
			}
		}
		
		for(i = q;i;--i){
			id = pos(a[i].x,a[i].y);
			int tmp = a[i].col,px = a[i].x,py = a[i].y;
			
			//opt=3
			for(j = 0;j < 4;++j) if(e[j][id] == 3){
				tx = px + dx[j];ty = py + dy[j];nxt = pos(tx,ty);
				nxt = bc[0].getf(nxt);
				xd[tmp].rt[nxt] = xd[tmp].ins(xd[tmp].rt[nxt],1,q,a[i].lv,-1);
			}
			for(j = 0;j < 4;++j) if(e[j][id] == 3){
				tx = px + dx[j];ty = py + dy[j];nxt = pos(tx,ty);
				if(qz[nxt] && qz[nxt] < i) continue;
				bc[0].mg(id,nxt,1);
			}
			int iid = bc[0].getf(id);
			ans[i] = bc[0].chksz(id) + xd[!tmp].qy(xd[!tmp].rt[iid],1,q,a[i].lv);
			
			//opt=2
			for(j = 0;j < 4;++j) if(e[j][id] == 2){
				tx = px + dx[j];ty = py + dy[j];nxt = pos(tx,ty);
				if(qz[nxt] && qz[nxt] < i) continue;
				bc[j % 2 + 1].mg(id,nxt);
			} 
			int mx1 = bc[1].chkmx(id),mx2 = bc[2].chkmx(id);
			int mn1 = bc[1].chkmn(id),mn2 = bc[2].chkmn(id);
			ans[i] += mx2 - mn2 + 1 + (mx1 - mn1) / m + 1;
			
			//all
			int dmx = pos2(tox(mx1),toy(mx1)),dmn = pos2(tox(mn1),toy(mn1));
			ans[i] -= xd[2].cx(iid,dmn,dmx) + xd[3].cx(iid,mn2,mx2);
			if(e[0][mn1] == 2 && caneat(i,qz[mn1 - m])){
				if(!xd[!tmp].qy2(xd[!tmp].rt[iid],1,q,a[qz[mn1 - m]].lv)) ++ans[i];
			} 
			if(e[1][mn2] == 2 && caneat(i,qz[mn2 - 1])){
				if(!xd[!tmp].qy2(xd[!tmp].rt[iid],1,q,a[qz[mn2 - 1]].lv)) ++ans[i];
			} 
			if(e[2][mx1] == 2 && caneat(i,qz[mx1 + m])){
				if(!xd[!tmp].qy2(xd[!tmp].rt[iid],1,q,a[qz[mx1 + m]].lv)) ++ans[i];
			} 
			if(e[3][mx2] == 2 && caneat(i,qz[mx2 + 1])){
				if(!xd[!tmp].qy2(xd[!tmp].rt[iid],1,q,a[qz[mx2 + 1]].lv)) ++ans[i];
			} 
			
			//opt=1
			for(j = 0;j < 4;++j) if(e[j][id] == 1){
				tx = px + dx[j];ty = py + dy[j];nxt = pos(tx,ty);
				if(qz[nxt] && qz[nxt] < i){
					if(caneat(i,qz[nxt]) && !xd[!tmp].qy2(xd[!tmp].rt[iid],1,q,a[qz[nxt]].lv)) ++ans[i];
				}
				else if(bc[0].getf(id) != bc[0].getf(nxt)) ++ans[i];
			}
			--ans[i];
		}
		for(i = 1;i <= q;++i){
			printf("%d\n",ans[i]);
		} 
	}
	return 0;
}