#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int main()
{
    int yes = 0, a, b, c, i, j, ab[7], maxLoc = 0;
    for (i = 0; i < 7; i++)
    {
        scanf("%d%d", &a, &b);
        ab[i] = a + b;
    }
    for (i = 0; i < 7; i++)
    {
        if (ab[i] > 8 && ab[i] > ab[maxLoc])
                maxLoc = i;
    }
    if (ab[maxLoc] > 8)
        printf("%d\n", maxLoc + 1);
    else
        printf("0\n");
    return 0;
}