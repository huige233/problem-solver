/*
s[i][j]表示1~i块权值<=j的数
g[i]表示块内离散化后的值
r[i][j]表示第i块离散化后j还原对应值
v[i][j]第i块<=j数个数
F1[k][i][j]第k块离散化后权值<=i位置<=j的权值的个数
F2[k][i][j]第k块离散化后权值<=i与<=j的块构成顺序对的个数
F3[k][i][j]第k块离散化后权值在[i,j]的顺序对数
*/
#include<bits/stdc++.h>
#define Tp template<typename Ty>
#define Ts template<typename Ty,typename... Ar>
#define W while
#define I inline
#define RI register int
#define LL long long
#define Cn const
#define CI Cn int&
#define gc getchar
#define D isdigit(c=gc())
#define pc(c) putchar((c))
#define min(x,y) ((x)<(y)?(x):(y))
#define max(x,y) ((x)>(y)?(x):(y))
using namespace std;
namespace Debug{
    Tp I void _debug(Cn char* f,Ty t){cerr<<f<<'='<<t<<endl;}
    Ts I void _debug(Cn char* f,Ty x,Ar... y){W(*f!=',') cerr<<*f++;cerr<<'='<<x<<",";_debug(f+1,y...);}
    Tp ostream& operator<<(ostream& os,Cn vector<Ty>& V){os<<"[";for(Cn auto& vv:V) os<<vv<<",";os<<"]";return os;}
    #define gdb(...) _debug(#__VA_ARGS__,__VA_ARGS__)
}using namespace Debug;
namespace FastIO{
    Tp I void read(Ty& x){char c;int f=1;x=0;W(!D) f=c^'-'?1:-1;W(x=(x<<3)+(x<<1)+(c&15),D);x*=f;}
    Ts I void read(Ty& x,Ar&... y){read(x),read(y...);}
    Tp I void write(Ty x){x<0&&(pc('-'),x=-x,0),x<10?(pc(x+'0'),0):(write(x/10),pc(x%10+'0'),0);}
    Tp I void writeln(Cn Ty& x){write(x),pc('\n');}
}using namespace FastIO;
Cn int N=1e5+10,M=sqrt(N)+10;
int n,m,S,a[N],bl[N],tot,L[M],R[M],v[M][N],s[M][N],g[N],r[M][M],id,F1[M][M][M],F2[M][M][M],F3[M][M][M];
I void Build(){
    RI i,j,k;S=sqrt(n);for(i=1;i<=n;i++) !((i-1)%S)&&(R[tot]=i-1,L[++tot]=i),bl[i]=tot;R[tot]=n;
    for(j=1;j<=tot;j++){
        for(i=L[j];i<=R[j];i++) v[j][a[i]]=i;
        for(id=0,i=1;i<=n;i++) v[j][i]&&(r[j][g[v[j][i]]=++id]=v[j][i],v[j][i]=1),v[j][i]+=v[j][i-1],s[j][i]=s[j-1][i]+v[j][i];
    }
    for(k=1;k<=tot;k++){
        for(i=L[k];i<=R[k];i++) F1[k][g[i]][i-L[k]+1]=1;
        for(i=1;i<=R[k]-L[k]+1;i++) for(j=1;j<=R[k]-L[k]+1;j++) F1[k][i][j]+=F1[k][i][j-1]+F1[k][i-1][j]-F1[k][i-1][j-1];
        for(i=L[k];i<=R[k];i++) for(j=i+1;j<=R[k];j++) g[i]<g[j]&&(F3[k][g[i]][g[j]]=1);
        for(i=1;i<=R[k]-L[k]+1;i++) for(j=1;j<=R[k]-L[k]+1;j++) F3[k][i][j]+=F3[k][i][j-1]+F3[k][i-1][j]-F3[k][i-1][j-1];
        for(i=L[k];i<=R[k];i++){
            for(j=1;j<k;j++) F2[k][g[i]][j]=s[j][a[i]]-s[j-1][a[i]];
            F2[k][g[i]][k]=F3[k][g[i]][g[i]]-F3[k][g[i]][g[i]-1];
        }for(i=1;i<=R[k]-L[k]+1;i++) for(j=1;j<=tot;j++) F2[k][i][j]+=F2[k][i][j-1]+F2[k][i-1][j]-F2[k][i-1][j-1];
    }
}
#define QS(O,l,r,x,y) (O[r][y]-O[(l)-1][y]-O[r][(x)-1]+O[(l)-1][(x)-1])
I LL Q(CI k,CI l,CI r,RI x,RI y){
    RI i;x=v[k][x-1]+1,y=v[k][y];LL Ans=0;for(i=l;i<=r;i++) if(x<=g[i]&&g[i]<=y) Ans+=QS(F1[k],x,g[i],l-L[k]+1,i-L[k]);
    return Ans;
}
vector<int> A,B;
I LL Q(CI bL,CI bR,CI Ll,CI Lr,CI Rl,CI Rr,CI x,CI y){
    A.clear(),B.clear();RI i,j,Ans=0;for(i=v[bL][x-1]+1;i<=v[bL][y];i++) if(Ll<=r[bL][i]&&r[bL][i]<=Lr) A.push_back(a[r[bL][i]]);
    for(i=v[bR][x-1]+1;i<=v[bR][y];i++) if(Rl<=r[bR][i]&&r[bR][i]<=Rr) B.push_back(a[r[bR][i]]);
    for(i=j=0;j<B.size();j++){W(i<A.size()&&A[i]<=B[j]) i++;Ans+=i;}return Ans;
}
I LL Q(CI l,CI r,CI x,CI y){
    RI i,bL=bl[l],bR=bl[r];if(bL==bR) return Q(bL,l,r,x,y);
    LL Ans=Q(bL,l,R[bL],x,y)+Q(bR,L[bR],r,x,y)+Q(bL,bR,l,R[bL],L[bR],r,x,y);
    for(i=l;i<=R[bL];i++) if(x<=a[i]&&a[i]<=y) Ans+=QS(s,bL+1,bR-1,a[i],y);
    for(i=L[bR];i<=r;i++) if(x<=a[i]&&a[i]<=y) Ans+=QS(s,bL+1,bR-1,x,a[i]);
    for(i=bL+1;i<=bR-1;i++){
        RI X=v[i][x-1]+1,Y=v[i][y];
        Ans+=QS(F2[i],X,Y,bL+1,i)-QS(F3[i],1,X-1,X,Y)-(Y-X+1)*QS(s,bL+1,i-1,1,x-1);
    }return Ans;
}
int main(){
    RI i,l,r,x,y;for(read(n,m),i=1;i<=n;i++) read(a[i]);Build();W(m--) read(l,r,x,y),writeln(Q(l,r,x,y));return 0;
}