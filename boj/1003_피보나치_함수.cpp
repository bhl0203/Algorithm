#include <stdio.h>

int main() {
	int t;
	scanf("%d",&t);
	int arr[41][2];
	arr[0][0] = 1;
	arr[0][1] = 0;
	arr[1][0] = 0;
	arr[1][1] = 1;
	for (int i = 2; i < 41; i++) {
		arr[i][0] = arr[i - 1][0] + arr[i - 2][0];
		arr[i][1] = arr[i - 1][1] + arr[i - 2][1];
	}
	int n;
	while (t--) {
		scanf("%d",&n);
		printf("%d %d\n",arr[n][0],arr[n][1]);
	}

	return 0;
}