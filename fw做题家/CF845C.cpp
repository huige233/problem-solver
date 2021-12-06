#include<bits/stdc++.h>
#define pi pair<int,int>
#define F first
#define S second
#define mp make_pair
#define re register
using namespace std;
priority_queue<pi,vector<pi>,greater<pi> > q;//STL大法好
int main() {
	int n,nwa=-1,nwb=-1;//时间最小是0，所以要把初值设为-1
	cin>>n;
	for(re int i=1; i<=n; i++) {
		int x,y;
		cin>>x>>y;
		q.push(mp(x,y));
	}
	while(q.size()) {
		int l=q.top().F,r=q.top().S;
		q.pop();
		if(nwa<l) nwa=r;//因为不能瞬时切换，所以不能等于
		else {
			if(nwb<l) nwb=r;
			else {
				puts("NO");//要是有一个节目看不了，那就直接输出结束
				return 0;
			}
		}
	}
	puts("YES");
	return 0;
}