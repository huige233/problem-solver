#include<cstdio>
#include<iostream>
#include<iomanip>
#include<map>
#include<unordered_map>
#include<string>
#include<queue>
#include<stack>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<cstdlib> 
#include<chrono>
#define IOS ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#define endl "\n"
#define int long long
//#define double long double
using namespace std;
	typedef long long ll;
	const int maxn=200005;
	const int inf=0x3f3f3f3f;
    const int mod=1e9+7;
	int n,m,k;
	struct custom_hash {static uint64_t splitmix64(uint64_t x) {x += 0x9e3779b97f4a7c15;x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;x = (x ^ (x >> 27)) * 0x94d049bb133111eb;return x ^ (x >> 31);}size_t operator()(uint64_t x) const {static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();return splitmix64(x + FIXED_RANDOM);}};
	struct left_tree{
        int dis,val;
        int fa,lson,rson;
    }lt[maxn];
    void init(){
        memset(lt,0,sizeof lt);
        lt[0].dis=-1;
        for(int i=0;i<maxn;i++)
            lt[i].fa=i;
        
    }
    inline int find(int x){
        return lt[x].fa==x?x:lt[x].fa=find(lt[x].fa);
    }
    int merge(int x,int y){
        if(!x||!y)  return x+y;
        if(lt[x].val>lt[y].val)   swap(x,y);//保证x<y
        int ls=lt[x].lson,rs=lt[x].rson;
        rs=merge(rs,y);
        if(lt[ls].dis<lt[rs].dis)   swap(ls,rs);
        lt[ls].fa=lt[rs].fa=lt[x].fa=x;
        lt[x].dis=lt[rs].dis+1;
        lt[x].lson=ls,lt[x].rson=rs;
        return x;
    }
    signed main(){
		IOS
		#ifndef ONLINE_JUDGE
		    freopen("IO\\in.txt","r",stdin);
		    freopen("IO\\out.txt","w",stdout);
        #endif
		int tn=1;
		while(cin>>n){
            init();
            for(int i=1;i<=n;i++){
                cin>>lt[i].val;
                lt[i].val*=-1;
            }
            
            cin>>m;
            while(m--){
                int a,b;
                cin>>a>>b;
                a=find(a),b=find(b);
                if(a==b)    cout<<-1<<endl;
                else{
                    int newl,newr,t;
                    lt[a].val/=2;
                    lt[lt[a].lson].fa=lt[lt[a].rson].fa=t=merge(lt[a].lson,lt[a].rson);
                    lt[a].dis=lt[a].lson=lt[a].rson=0;
                    lt[a].fa=lt[t].fa=newl=merge(a,t);
                    lt[b].val/=2;
                    lt[lt[b].lson].fa=lt[lt[b].rson].fa=t=merge(lt[b].lson,lt[b].rson);
                    lt[b].dis=lt[b].lson=lt[b].rson=0;
                    lt[b].fa=lt[t].fa=newr=merge(b,t);
                    lt[newl].fa=lt[newr].fa=t=merge(newl,newr);
                    cout<<-lt[t].val<<endl;
                }
            }
		}
	} 
						
