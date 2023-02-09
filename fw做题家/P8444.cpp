#include<bits/stdc++.h>
using namespace std;
const int N=1e6+10;
long long a[N],n,w,t=0,ans=0;//开long long！
inline bool cmp(int x,int y){
	return x>y;//从大到小排序
}
inline bool cmp1(int x,int y){
	return x<y;//从小到大排序
}
int main(){
	scanf("%lld",&n);
	for(int i=1;i<=n;++i)
		scanf("%lld",&a[i]);
	scanf("%lld",&w);
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=n;++i){
		if(t==0)
			if(w-a[i]>=0){
				w-=a[i];//减去最大值
				t=a[i];//标记
				break;//退出循环
			}
	}
	if(t){
		sort(a+1,a+n+1,cmp1);
		for(int i=1;i<=n;++i){
			if(t>=a[i]){
				t-=a[i];
				ans++;//累计答案
			}
		}
	}
	printf("%lld\n",ans);
	return 0;
}