#include<cstdio>
#include<cstring>
#define maxn 60
char ans[maxn]="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
int main()
{
    int n,mark=1;
    while(scanf("%d",&n)!=EOF){
        printf("2 %d %d\n",n,n);
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++)
                printf("%c",ans[i]);
            printf("\n");
        }
        printf("\n");
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++)
                printf("%c",ans[j]);
            printf("\n");
        }
    }
    return 0;
}