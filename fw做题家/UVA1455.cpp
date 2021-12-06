#include<cstdio> 
#include<iostream> 
#include<cstdlib> 
#include<cstring> 
#include<queue> 
#include<vector> 
#include<algorithm> 
#define LL long long 
#define CLEAR(xxx) memset(xxx,0,sizeof(xxx)) 
using namespace std; 
const int maxn=100000+5,maxx=2000000+5; 
 
int n,m,x[maxn],y[maxn]; 
int father[maxn],size[maxn],low[maxn],up[maxn];
int state[maxx*4],city[maxx*4],lazy[maxx*4][2];
int maxsz=0,y1,y2,q;
 
inline void _read(int &x){ 
    char ch=getchar(); bool mark=false; 
    for(;!isdigit(ch);ch=getchar())if(ch=='-')mark=true; 
    for(x=0;isdigit(ch);ch=getchar())x=x*10+ch-'0'; 
    if(mark)x=-x; 
}
 
int getfa(int x){
	return x==father[x]? x: getfa(father[x]);
}
void pushdown(int o){
	int ls=o<<1,rs=ls+1;
	if(lazy[o][0]){
		lazy[ls][0]+=lazy[o][0];
		lazy[rs][0]+=lazy[o][0];
		state[ls]+=lazy[o][0];
		state[rs]+=lazy[o][0];
	}
	if(lazy[o][1]){
		lazy[ls][1]+=lazy[o][1];
		lazy[rs][1]+=lazy[o][1];
		city[ls]+=lazy[o][1];
		city[rs]+=lazy[o][1];
	}
	lazy[o][0]=lazy[o][1]=0;
}
void update(int o,int L,int R,int sz,int v){
	if(lazy[o][1]||lazy[o][0]) pushdown(o);
	if(y1<=L&&y2>=R){
		lazy[o][0]+=v;
		lazy[o][1]+=sz;
		state[o]+=v;
		city[o]+=sz;
	}
	else if(R>L){
		int mid=(L+R)>>1;
		if(y1<=mid) update(o<<1,L,mid,sz,v);
		if(y2>mid)  update(o*2+1,mid+1,R,sz,v);
	}
}
int query(int o,int L,int R){
	if(L==R&&L==q) return o;
	if(lazy[o][1]||lazy[o][0]) pushdown(o);
	int mid=(L+R)>>1;
	if(q<=mid) return query(o<<1,L,mid);
	else return query(o*2+1,mid+1,R);
}
 
void Delete(int x){
	y1=low[x]; y2=up[x];
	update(1,0,maxsz,-size[x],-1);
}
 
void merge(int x,int y){  //删除两个小州，建立一个大州 
	x=getfa(x); y=getfa(y);
	if(x==y) return ;
	if(size[x]>1) Delete(x);
	if(size[y]>1) Delete(y);
	father[y]=x;
	size[x]+=size[y];
	y1=low[x]=min(low[x],low[y]);
	y2=up[x]=max(up[x],up[y]);
	update(1,0,maxsz,size[x],1);
}
void init(){
	int i;
	_read(n); 
	maxsz=0;
	for(i=1;i<=n;i++){
		_read(x[i]); _read(y[i]);
		x[i]<<=1; y[i]<<=1;
		maxsz=max(maxsz,y[i]);
	}
	for(i=1;i<=n;i++){
		father[i]=i;
		size[i]=1;
		low[i]=up[i]=y[i];
	}
	CLEAR(lazy); CLEAR(city);
	CLEAR(state);
}
void solve(){
	int i,s,t;
	double temp;
	string cmd;
	_read(m);
	while(m--){
		cin>>cmd;
		if(cmd=="road"){
			_read(s); _read(t);
			s++;t++;     //题目中编号是从0～n-1的 
			merge(s,t);  //合并两个州 
		}
		else {
			scanf("%lf",&temp);
			q=(int)(temp*2+0.5);
			if(q>maxsz) {
				puts("0 0"); continue; 
			}
			int ans=query(1,0,maxsz);
			printf("%d %d\n",state[ans],city[ans]);
		}
	}
}
int main(){
	int T;
	_read(T);
	while(T--){
		init();
		solve();
	}
	return 0;
}