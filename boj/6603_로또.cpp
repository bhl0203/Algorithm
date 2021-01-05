#include <stdio.h>

int n;
int arr[15];
int route[6];

void dfs(int cur, int l) {
    if (l == 6) {
        for (int i = 0; i < 6; i++) {
            printf("%d ",route[i]);
        }
        puts("");
        return;
    }
    for (int i = cur; i < n; i++) {
        route[l] = arr[i];
        dfs(i + 1, l + 1);
    }

}

int main()
{
    while (1) {
        scanf("%d", &n);
        for (int i = 0; i < n; i++) {
            scanf("%d", &arr[i]);
        }
        for (int i = 0; i < n; i++) {
            route[0] = i;
        }
        dfs(0, 0);
        puts("");

        if (n == 0) break;
    }
    return 0;
}
