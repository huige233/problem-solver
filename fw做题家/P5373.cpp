#include<cstdio>
#include<algorithm>
#include<cmath>
#include<ctime>
const int N=65536,md=998244353;
typedef long long LL;
inline void upd(int&a){a+=a>>31&md;}
inline int pow(int a,int b){
    int ret=1;
    for(;b;b>>=1,a=(LL)a*a%md)if(b&1)ret=(LL)ret*a%md;
    return ret;
}
int n,m,A[N],B[N],L,g[17][N],lim,rev[N],M,B1[150][N],B2[250][N],R[N];
void init(int n){
    int l=-1;
    for(lim=1;lim<n;lim<<=1)++l;M=l+1;
    for(int i=1;i<lim;++i)
    rev[i]=((rev[i>>1])>>1)|((i&1)<<l);
}
void NTT(int*a,int f){
    for(int i=1;i<lim;++i)if(i<rev[i])std::swap(a[i],a[rev[i]]);
    for(int i=0;i<M;++i){
        const int*G=g[i],c=1<<i;
        for(int j=0;j<lim;j+=c<<1)
        for(int k=0;k<c;++k){
            const int x=a[j+k],y=a[j+k+c]*(LL)G[k]%md;
            upd(a[j+k]+=y-md),upd(a[j+k+c]=x-y);
        }
    }
    if(!f){
        const int iv=pow(lim,md-2);
        for(int i=0;i<lim;++i)a[i]=(LL)a[i]*iv%md;
        std::reverse(a+1,a+lim);
    }
}
void work(){
    B1[0][0]=B2[0][0]=1;
    for(int i=0;i<m;++i)B1[1][i]=B[i];
    NTT(B,1);
    for(int i=2;i<=L;++i){
        int*Bp=B1[i-1],*Bn=B1[i];
        NTT(Bp,1);
        for(int i=0;i<lim;++i)Bn[i]=(LL)B[i]*Bp[i]%md;
        NTT(Bp,0),NTT(Bn,0);
        for(int i=n;i<n<<1;++i)Bn[i]=0;
    }
    for(int i=0;i<n;++i)B2[1][i]=B1[L][i];
    int*bL=B1[L];
    NTT(bL,1);
    for(int i=2;i<L;++i){
        int*Bp=B2[i-1],*Bn=B2[i];
        NTT(Bp,1);
        for(int i=0;i<lim;++i)Bn[i]=(LL)bL[i]*Bp[i]%md;
        NTT(Bp,0),NTT(Bn,0);
        for(int i=n;i<n<<1;++i)Bn[i]=0;
    }
    NTT(bL,0);
}
int main(){
    scanf("%d%d",&n,&m),++n,++m;
    for(int i=0;i<17;++i){
        int*G=g[i];
        G[0]=1;
        const int gi=G[1]=pow(3,(md-1)/(1<<i+1));
        for(int j=2;j<1<<i;++j)G[j]=(LL)G[j-1]*gi%md;
    }
    L=sqrt(n)+1;
    init(n<<1);
    for(int i=0;i<n;++i)scanf("%d",A+i);
    for(int i=0;i<m;++i)scanf("%d",B+i);
    work();
    for(int i=0;i<L;++i){
        static int C[N];
        for(int i=0;i<lim;++i)C[i]=0;
        for(int j=0;j<L;++j){
            const int x=A[i*L+j],*B=B1[j];
            for(int k=0;k<n;++k)
            C[k]=(C[k]+(LL)x*B[k])%md;
        }
        NTT(C,1),NTT(B2[i],1);
        for(int j=0;j<lim;++j)C[j]=(LL)C[j]*B2[i][j]%md;
        NTT(C,0);
        for(int i=0;i<n;++i)upd(R[i]+=C[i]-md);
    }
    for(int i=0;i<n;++i)
    printf("%d ",R[i]);
    return 0;
}