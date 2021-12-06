#include <iostream>
#include <vector>
#include <queue>
#include <cstdlib>
#include<algorithm>
using namespace std;
struct Node{
	int u,v;
};
vector<int>e[100001];//相当于一个二维数组
vector<Node>s;
int n,m;
int f1[100001],f2[100001];
int cmp(const Node a,const Node b)
{
	if(a.u==b.u)
	return a.v<b.v;
	else
	return a.u<b.u;
}
void dfs(int x)
{
	f1[x]=1;
	cout <<x<<" ";
	for(int i=0;i<e[x].size();i++)
	{
		int point=s[e[x][i]].v;
		if(f1[point]==0)
		dfs(point);
	}
}
void bfs(int x)
{
	queue<int>q;
	q.push(x);
	cout<<x<<" ";
	f2[x]=1;
	while(!q.empty())
	{
		int fre=q.front();
		for(int i=0;i<e[fre].size();i++)
		{
			int point=s[e[fre][i]].v;
			if(!f2[point])
			{
				q.push(point);
				cout <<point<<" ";
				f2[point]=1;
			}
		}
		q.pop();
	}
}
int main()
{
	cin>>n>>m;
	int uu,vv;
	for(int i=0;i<m;i++)
	{
		cin>>uu>>vv;
		s.push_back((Node){uu,vv});
	}
	sort(s.begin(),s.end(),cmp);
	for(int i=0;i<m;i++)
	{
		e[s[i].u].push_back(i);
	}
	dfs(1);
	cout <<endl;
	bfs(1);
	return 0;
}