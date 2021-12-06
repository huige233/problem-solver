#include<bits/stdc++.h>
#define R register int
#define fp(i,a,b) for(R i=a,T=b+1;i<T;++i)
#define fd(i,a,b) for(R i=a,T=b-1;i>T;--i)
using namespace std;
const int P=30011;
int n,m;
struct node{
    int a[105][105];
    node(){memset(a,0,sizeof(a));}
    int *operator [](const R &x){return a[x];}
    node operator *(node &b){
        node res;
        fp(i,1,n)fp(j,1,n)fp(k,1,n)
        res[i][j]=(res[i][j]+a[i][k]*b[k][j])%P;
        return res;
    }
}I,A,B;
node ksm(node x,R y){
    node res;fp(i,1,n)res[i][i]=1;
    for(;y;y>>=1,x=x*x)if(y&1)res=res*x;
    return res;
}
int main(){
//  freopen("testdata.in","r",stdin);
    scanf("%d%d",&n,&m);
    fp(i,1,n)I[i][i]=I[i+n][i]=I[i][i+n]=1;
    fp(i,1,n-1)I[i+1][i]=I[i][i+1]=1;
    n<<=1,A=ksm(I,m-2),B=A*I;
    printf("%d\n",(B[1][n>>1]-A[1][n]+P)%P);
    return 0;
}