#include<stdio.h>
int r,s=1,t;
signed main() {
    scanf("%d",&r),r>>=__builtin_ctz(r); // 排除质因子 2
    for (int i=3; i*i<=r; i+=2)
        if (r%i==0) {
            while (r%i==0) r/=i,++t;
            (i&3)==1&&(s*=(t<<1|1)),t=0;
        }
    r>1&&(r&3)==1&&(s*=3);
    printf("%d\n",s<<2);
    return 0;
}