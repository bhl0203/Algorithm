#include <stdio.h>

int main() {
	int p;
	scanf("%d",&p);
	int n = 1000 - p;
	int cnt=0;
	while (n >= 500) {
		n = n - 500;
		cnt++;
	}
	while (n >= 100) {
		n = n - 100;
		cnt++;
	}
	while (n >= 50) {
		n = n - 50;
		cnt++;
	}
	while (n >= 10) {
		n = n - 10;
		cnt++;
	}
	while (n >= 5) {
		n = n - 5;
		cnt++;
	}
	while (n >= 1) {
		n = n - 1;
		cnt++;
	}
	printf("%d\n",cnt);
	return 0;
}
