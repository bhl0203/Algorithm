#include <stdio.h>

int main() {
	int a, b;
	while (1) {
		scanf("%d %d", &a, &b);
		if (a == 0 && b == 0) return 0;
		if (a / b > 0) {//a>b
			if (a % b == 0) {//a is divisible by b
				printf("multiple\n");
			}
			else if (a % b != 0) {//not divisible
				printf("neither\n");
			}
		}
		else if (b / a > 0) {//b > a
			if (b % a == 0) {//b is divisible by a
				printf("factor\n");
			}
			else if (b % a == 0) {
				printf("neither\n");
			}
		}
	}

	return 0;
}