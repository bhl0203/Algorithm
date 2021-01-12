#include <stdio.h>
#include <stdlib.h>

int m[17][17];
int arr[17];

int cnt;
int n;

bool c(int x) {
	for (int i = 0; i < x; i++) {
		if (arr[i] == arr[x] || abs(arr[i] - arr[x]) == abs(i - x)) return false;
	}
	return true;
}

void check(int x) {

	if (x == n) {
		cnt++;
		return;
	}
	for (int i = 0; i < n; i++) {
		arr[x] = i;
		if (c(x)) check(x + 1);
	}
}

int main() {
	scanf("%d", &n);
	check(0);
	printf("%d\n", cnt);
	return 0;
}