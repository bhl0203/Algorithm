#include <stdio.h>

int main()
{
    int n;
    int res = 0;
    scanf("%d",&n);
    for (int i = 1; i <= n; i++) {
        res += i;
    }
    printf("%d\n",res);
    return 0;
}

