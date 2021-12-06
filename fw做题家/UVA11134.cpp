#include<bits/stdc++.h>
 
using namespace std;
int visr[5005];
int visc[5005];
 
struct Car{
	int id,ans;
	int l,r;
	
}r[5005],c[5005];
 
bool cmp2(Car a,Car b){
	if(a.l==b.l)
	return a.r>b.r;
	return a.l>b.l;
}
 
bool cmp1(Car a,Car b){
	return a.id<b.id;
}
 
int main(){
	int n,i,j;
	int a,b,c1,d;
	while(scanf("%d",&n) && n){
	memset(visr,0,sizeof(visr));
	memset(visc,0,sizeof(visc));
	
	for( i=1;i<=n;i++){
		scanf("%d %d %d %d",&a,&b,&c1,&d);
		r[i].l=a;
		r[i].r=c1;
		c[i].l=b;
		c[i].r=d;
		r[i].id=c[i].id=i;		
	}
	sort(r+1,r+n+1,cmp2);
	sort(c+1,c+n+1,cmp2);
	
	for( i=1;i<=n;i++){
	
		for( j=r[i].r;j>=r[i].l;j--)
		if(visr[j]==0){
		visr[j]=1;
		r[i].ans=j;	
		break;
		}
		
	
		if(j<r[i].l)
		break;
	
		
		for( j=c[i].r;j>=c[i].l;j--)
		if(visc[j]==0){
			visc[j]=1;
			c[i].ans=j;
			break;
		}
		
	
		if(j<c[i].l)
		break;
	}
		if(i<=n){
		printf("IMPOSSIBLE\n");continue;
}
		sort(r+1,r+n+1,cmp1);
		sort(c+1,c+n+1,cmp1);
		
		for(int i=1;i<=n;i++){
			printf("%d %d\n",r[i].ans,c[i].ans);
		}
	}	
	
}