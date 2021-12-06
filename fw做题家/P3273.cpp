#include<iostream>
#include<algorithm>
#include<cstdio>
#include<queue>
#define MAXN 300010
using namespace std;
int n,m,addall=0,root;
struct tree{
	struct node{
		int son[2];
		int v,dis,f,flag;
	}a[MAXN];
	inline void independent(int rt){
		a[rt].son[0]=a[rt].son[1]=a[rt].f=0;
	}
	inline void pushdown(int rt){
		if(a[rt].son[0]){
			a[a[rt].son[0]].v+=a[rt].flag;
			a[a[rt].son[0]].flag+=a[rt].flag;
		}
		if(a[rt].son[1]){
			a[a[rt].son[1]].v+=a[rt].flag;
			a[a[rt].son[1]].flag+=a[rt].flag;
		}
		a[rt].flag=0;
	}
	int merge(int x,int y){
		if(!x)return y;if(!y)return x;
		if(a[x].v<a[y].v)swap(x,y);
		pushdown(x);
		a[x].son[1]=merge(a[x].son[1],y);
		a[a[x].son[1]].f=x;
		if(a[a[x].son[1]].dis>a[a[x].son[0]].dis)swap(a[x].son[0],a[x].son[1]);
		a[x].dis=a[a[x].son[1]].dis+1;
		return x;
	}
	int find(int x){
		while(a[x].f)x=a[x].f;
		return x;
	}
	int sum(int rt){
		int s=0;
		for(int i=a[rt].f;i;i=a[i].f)s+=a[i].flag;
		return s;
	}
	int deletemin(int rt){
		pushdown(rt);
		int x=a[rt].f,y=merge(a[rt].son[0],a[rt].son[1]);
		a[y].f=x;
		if(x)a[x].son[a[x].son[1]==rt]=y;
		while(x){
			if(a[a[x].son[0]].dis<a[a[x].son[1]].dis)swap(a[x].son[0],a[x].son[1]);
			if(a[a[x].son[1]].dis+1==a[x].dis)return root;
			a[x].dis=a[a[x].son[1]].dis+1;
			y=x;
			x=a[x].f;
		}
		return y;
	}
	inline void addtree(int x,int v){
		x=find(x);
		a[x].v+=v;
		a[x].flag+=v;
	}
	int insert(int x,int v){
		int f=find(x);
		if(f==x){
			if(!a[x].son[0]&&!a[x].son[1]){
				a[x].v+=v;
				return x;
			}
			else{
				if(a[x].son[0])f=a[x].son[0];
				else f=a[x].son[1];
			}
		}
		deletemin(x);
		a[x].v+=v+sum(x);
		independent(x);
		return merge(find(f),x);
	}
	int buildtree(){
		queue<int> q;
		for(int i=1;i<=n;i++)q.push(i);
		while(q.size()>1){
			int x,y,z;
			x=q.front();q.pop();
			y=q.front();q.pop();
			z=merge(x,y);
			q.push(z);
		}
		return q.front();
	}
}one,two;
inline int read(){
	int date=0,w=1;char c=0;
	while(c<'0'||c>'9'){if(c=='-')w=-1;c=getchar();}
	while(c>='0'&&c<='9'){date=date*10+c-'0';c=getchar();}
	return date*w;
}
int main(){
	char ch[2];
	int x,y,k;
	n=read();
	one.a[0].dis=two.a[0].dis=-1;
	for(int i=1;i<=n;i++)one.a[i].v=two.a[i].v=read();
	root=two.buildtree();
	m=read();
	while(m--){
		scanf("%s",ch);
		switch(ch[0]){
			case 'U':{
				x=read();y=read();
				x=one.find(x);y=one.find(y);
				if(x!=y){
					k=one.merge(x,y);
					if(k==x)root=two.deletemin(y);
					else root=two.deletemin(x);
				}
				break;
			}
			case 'A':{
				x=read();
				switch(ch[1]){
					case '1':{
						y=read();
						root=two.deletemin(one.find(x));
						k=one.insert(x,y);
						two.a[k].v=one.a[k].v;
						two.independent(k);
						root=two.merge(root,k);
						break;
					}
					case '2':{
						y=read();
						int f=one.find(x);
						root=two.deletemin(f);
						one.a[f].v+=y;
						one.a[f].flag+=y;
						two.a[f].v=one.a[f].v;
						two.independent(f);
						root=two.merge(root,f);
						break;
					}
					case '3':addall+=x;break;
				}
				break;
			}
			case 'F':{
				switch(ch[1]){
					case '1':{
						x=read();
						printf("%d\n",one.a[x].v+addall+one.sum(x));
						break;
					}
					case '2':{
						x=read();
						x=one.find(x);
						printf("%d\n",one.a[x].v+addall);
						break;
					}
					case '3':{
						printf("%d\n",two.a[root].v+addall);
						break;
					}
				}
				break;
			}
		}
	}
	return 0;
}