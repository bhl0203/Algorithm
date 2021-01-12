#include <stdio.h>

int main() {
	int n;
	scanf("%d",&n);
	int cnt = 0;
	while (n) {
		cnt += n % 2;
		n = n >> 1;
	}
	printf("%d\n",cnt);
	return 0;
}