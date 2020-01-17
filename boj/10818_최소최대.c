#include <stdio.h>

int main() {
	int N;
	int tmp;
	int big = -1000001;
	int small = 1000001;
	scanf("%d",&N);
	while (N--) {
		scanf("%d", &tmp);
		if (tmp > big) big = tmp;
		if (tmp < small) small = tmp;
	}
	printf("%d %d",small,big);

	return 0;
}