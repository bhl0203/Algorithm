#include <stdio.h>

int main() {
	int n;
	scanf("%d",&n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < i; j++) {
			printf(" ");
		}
		for (int j = 2 * i;j<2*n-1;j++) {
			printf("*");
		}
		puts("");
	}
	for (int i = n-1; i > 0; i--) {
		for (int j = i-1; j > 0; j--) {
			printf(" ");
		}
		for (int j = 2*(i-1); j < 2*n-1; j++) {
			printf("*");
		}
		puts("");
	}
	return 0;
}
