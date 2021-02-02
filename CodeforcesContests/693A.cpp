#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define ll long long


void solve() {

	int w, h, n;
	int cnt = 1;
	scanf("%d %d %d",&w,&h,&n);
	while (w % 2 == 0) {
		w /= 2;
		cnt *= 2;
	}
	while (h % 2 == 0) {
		h /= 2;
		cnt *= 2;
	}
	if (cnt >= n) printf("YES\n");
	else printf("NO\n");
}



int main() {
	int t;
	scanf("%d",&t);
	while (t--) {
		solve();
	}
	return 0;
}