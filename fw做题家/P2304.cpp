#include<bits/stdc++.h>
using namespace std;
 
const int N=200010,M=200010;
struct node{
	int x,y,id;
}p[N];
struct edge{
	int y,nex,c;
}s[M<<1];
int first[N],head[N],len=1,qs[N],st,ed,d[N];
int nex[N][3],f[N],ans[N],from[N],op[N],s1,t1,s2,t2,lef[N],rig[N],pos[N];//上,左上,右上
vector<int> V[N],P[N],S;
int sta[N],top=0,mmax=-1e9;
bool tf[N][2];
int n;
 
bool cmp1(const node&a,const node&b){return a.y!=b.y?a.y<b.y:a.x<b.x;}
bool cmp2(const node&a,const node&b){return a.x!=b.x?a.x<b.x:a.y<b.y;}
bool cmp3(const node&a,const node&b){return a.x+a.y!=b.x+b.y?a.x+a.y<b.x+b.y:a.x<b.x;}
bool cmp4(const node&a,const node&b){return a.y-a.x!=b.y-b.x?a.y-a.x<b.y-b.x:a.x<b.x;}
bool cmp5(const node&a,const node&b){return a.id<b.id;}
 
void ins(int x,int y,int a,int b){
	op[x]-=a;op[y]+=a;
	s[++len]=(edge){y,first[x],b-a};first[x]=len;
	s[++len]=(edge){x,first[y],0};first[y]=len;
}
 
void gins(int x,int type){
	if(tf[x][type]) return ;
	if(type==0){
		tf[x][0]=true;
		for(auto i:P[x]) ins(i,x,1,1e9),gins(i,1);
	}
	if(type==1){
		tf[x][1]=true;
		if(top!=mmax){
			sta[++top]=x;
			for(auto i:V[x]) if(i!=x){
				if(pos[i]<pos[x]){
					int now=lef[x];
					while(now!=i) sta[++top]=now,now=lef[now];
					while(lef[now]) now=lef[now];
					while(now!=i) sta[++top]=now,now=rig[now];
					sta[++top]=i;
				}
				else{
					int now=rig[x];
					while(now!=i) sta[++top]=now,now=rig[now];
					while(rig[now]) now=rig[now];
					while(now!=i) sta[++top]=now,now=lef[now];
					sta[++top]=i;
				}
				break;
			}
			else break;
		}
		for(auto i:V[x]) gins(i,0);
	}
}
 
bool bfs(int S,int T){
	for(int i=1;i<=T;i++) d[i]=0,first[i]=head[i];
	d[qs[st=ed=1]=S]=1;
	while(st<=ed){
		int x=qs[st++];
		for(int i=first[x];i;i=s[i].nex) if(s[i].c && !d[s[i].y]){
			d[s[i].y]=d[x]+1;
			qs[++ed]=s[i].y;
		}
	}
	return d[T]!=0;
}
 
int dfs(int x,int T,int t){
	if(x==T) return t;
	int tot=0;
	for(int&i=first[x];i;i=s[i].nex) if(s[i].c && d[s[i].y]==d[x]+1){
		int now=dfs(s[i].y,T,min(t-tot,s[i].c));
		s[i].c-=now;s[i^1].c+=now;tot+=now;
		if(tot==t) break;
	}
	return tot;
}
 
int Dinic(int S,int T){
	int tot=0,dx;
	while(bfs(S,T)){
		dx=dfs(S,T,1e9);
		while(dx) tot+=dx,dx=dfs(S,T,1e9);
	}
	return tot;
}
 
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d %d",&p[i].x,&p[i].y),p[i].id=i;
	n++;p[n]=(node){0,0,n};
	for(int i=1;i<=n;i++) ans[i]=-1e9;ans[n]=0;
	s1=n+1;t1=s1+1;s2=t1+1;t2=s2+1;
	sort(p+1,p+1+n,cmp2);
	for(int i=1;i<n;i++) if(p[i].x==p[i+1].x) 
		nex[p[i].id][0]=p[i+1].id;
	sort(p+1,p+1+n,cmp3);
	for(int i=1;i<n;i++) if(p[i].x+p[i].y==p[i+1].x+p[i+1].y)
		nex[p[i+1].id][1]=p[i].id;
	sort(p+1,p+1+n,cmp4);
	for(int i=1;i<n;i++) if(p[i].y-p[i].x==p[i+1].y-p[i+1].x)
		nex[p[i].id][2]=p[i+1].id;
	sort(p+1,p+1+n,cmp1);
	int now=1;
	while(now<=n){
		int L=now,R=now,mmax=-1e9;S.resize(0);
		while(p[R+1].y==p[R].y) R++;
		for(int i=L;i<=R;i++){
			f[p[i].id]=ans[p[i].id],V[p[i].id].push_back(p[i].id);
			if(i!=L) lef[p[i].id]=p[i-1].id;
			if(i!=R) rig[p[i].id]=p[i+1].id;
			pos[p[i].id]=i;
		}
		for(int i=L;i<=R;i++){
			if(mmax+i-L>ans[p[i].id]) ans[p[i].id]=mmax+i-L,V[p[i].id]=S;
			else if(mmax+i-L==ans[p[i].id]) for(auto j:S) V[p[i].id].push_back(j);
			if(f[p[i].id]>mmax) mmax=f[p[i].id],S.resize(0);
			if(f[p[i].id]==mmax) S.push_back(p[i].id);
		}
		mmax=-1e9;S.resize(0);
		for(int i=R;i>=L;i--){
			if(mmax+R-i>ans[p[i].id]) ans[p[i].id]=mmax+R-i,V[p[i].id]=S;
			else if(mmax+R-i==ans[p[i].id]) for(auto j:S) V[p[i].id].push_back(j);
			if(f[p[i].id]>mmax) mmax=f[p[i].id],S.resize(0);
			if(f[p[i].id]==mmax) S.push_back(p[i].id);
		}
		for(int i=L;i<=R;i++){
			for(int j=0;j<3;j++) if(nex[p[i].id][j]){
				if(ans[nex[p[i].id][j]]<ans[p[i].id]+1) 
					P[nex[p[i].id][j]].resize(0),ans[nex[p[i].id][j]]=ans[p[i].id]+1;
				if(ans[nex[p[i].id][j]]==ans[p[i].id]+1) 
					P[nex[p[i].id][j]].push_back(p[i].id);
			}
		}
		now=R+1;
	}
	sort(p+1,p+1+n,cmp5);
	for(int i=1;i<=n;i++) mmax=max(mmax,ans[i]);
	printf("%d\n",mmax);
	for(int i=1;i<=n;i++) if(ans[i]==mmax) gins(i,1);
	for(int i=mmax;i>=1;i--) printf("%d ",sta[i]);printf("\n");
	for(int i=1;i<=n;i++) ins(s1,i,0,1e9),ins(i,t1,0,1e9);
	for(int i=1;i<=t1;i++) 
		if(op[i]>0) ins(s2,i,0,op[i]);
		else if(op[i]<0) ins(i,t2,0,-op[i]);
	ins(t1,s1,0,1e9);
	for(int i=1;i<=t2;i++) head[i]=first[i];
	Dinic(s2,t2);
	int tot=s[len].c;s[len].c=s[len^1].c=0;
	printf("%d\n",tot-Dinic(t1,s1));
}