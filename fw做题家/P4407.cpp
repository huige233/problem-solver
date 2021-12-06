//minamoto
#include<bits/stdc++.h>
#define rint register int
#define ull unsigned long long
using namespace std;
const int N=25;
int n,m,len,ans,top;char s[N];
ull Base=233,l[N],r[N],bin[N],h[N];
map<ull,ull>a[N],b[N][N],c[N];
int main(){
//  freopen("testdata.in","r",stdin);
    scanf("%d%d",&n,&m);
    bin[0]=1;for(rint i=1;i<25;++i)bin[i]=bin[i-1]*Base;
    while(n--){
        scanf("%s",s+1),len=strlen(s+1);
        for(rint j=0;j<25;++j)l[j]=r[j]=h[j]=0;
        for(rint j=1;j<=len;++j)l[j]=l[j-1]*Base+s[j]-'a'+1;
        for(rint j=len;j;--j)r[j]=r[j+1]+(s[j]-'a'+1)*bin[len-j];
        ++a[len][l[len]];
        for(rint j=1;j<=len;++j)
        h[j]=l[j-1]*bin[len-j]+r[j+1],++b[len-1][j][h[j]];
        sort(h+1,h+1+len);
        for(rint j=1;j<=len;++j)if(h[j]!=h[j-1])++c[len-1][h[j]];
    }
    while(m--){
        scanf("%s",s+1),len=strlen(s+1);
        for(rint j=0;j<25;++j)l[j]=r[j]=h[j]=0;
        for(rint j=1;j<=len;++j)l[j]=l[j-1]*Base+s[j]-'a'+1;
        for(rint j=len;j;--j)r[j]=r[j+1]+(s[j]-'a'+1)*bin[len-j];
        if(a[len][l[len]]){puts("-1");continue;}
        ans=0;
        for(rint j=1;j<=len;++j)h[j]=l[j-1]*bin[len-j]+r[j+1];
        for(rint j=1;j<=len;++j)ans+=b[len-1][j][h[j]];
        sort(h+1,h+1+len);
        for(rint j=1;j<=len;++j)if(h[j]!=h[j-1])ans+=a[len-1][h[j]];
        ans+=c[len][l[len]];printf("%d\n",ans);
    }return 0;
}