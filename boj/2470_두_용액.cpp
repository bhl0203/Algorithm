#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;

int arr[100001];

int main() {
	int n;

	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d", &arr[i]);
	}
	int l = 0;
	int r = n - 1;
	int res = 2000000000;
	int tmp;
	int resl, resr;
	sort(arr, arr + n);
	while (l < r) {
		tmp = arr[l] + arr[r];
		if (abs(tmp) < res) {
			res = abs(tmp);
			resl = l;
			resr = r;
		}
		if (tmp > 0) r--;
		else l++;
	}
	printf("%d %d\n", arr[resl], arr[resr]);
	return 0;
}
