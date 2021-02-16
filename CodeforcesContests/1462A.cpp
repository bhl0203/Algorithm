#include <stdio.h>
#include <vector>
#include <algorithm>
#include <string>
#include <functional>
using namespace std;

void solve() {
	int n;
	scanf("%d",&n);
	vector<int> v(n);
	for (int i = 0; i < n; i++) {
		scanf("%d",&v[i]);
	}
	int l = 0;
	int r = n - 1;
	for (int i = 0; i <= n / 2; i++) {
		if (n % 2 == 0) {
			if (i == n / 2) break;
		}
		printf("%d ",v[i]);
		if (n % 2 == 1) {
			if (i == n / 2) break;
		}
		printf("%d ", v[n - 1 - i]);
	}
	puts("");
}



int main() {
	
	int t;
	scanf("%d",&t);
	while (t--) {
		solve();
	}

	return 0;
}