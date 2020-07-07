#include <stdio.h>

int main() {
	int b[3];
	int low_burger = 9999;
	for (int i = 0; i < 3; i++) {
		scanf("%d", &b[i]);
		if (b[i] < low_burger)
			low_burger = b[i];
	}
	int d[2];
	int low_drink = 9999;
	for (int i = 0; i < 2; i++) {
		scanf("%d", &d[i]);
		if (d[i] < low_drink)
			low_drink = d[i];
	}
	printf("%d\n",low_burger+low_drink-50);
	return 0;
}