#include <stdio.h>
#include <vector>
#include <algorithm>
#include <string>
#include <functional>
#include <stack>
#include <queue>
#include <tuple>

using namespace std;

#define ll long long

void solve() {

	int n;
	scanf("%d",&n);
	vector<int> v(n);
	for (int i = 0; i < n; i++) {
		scanf("%1d",&v[i]);
	}
	//check 1234 123n-1 12n-2n-1 1n-3n-2n-1 n-4n-3n-2n-1
	bool flag = false;
	//check 1234
	if (v[0] == 2) {
		if (v[1] == 0) {
			if (v[2] == 2) {
				if (v[3] == 0) flag = true;
				if (v[n - 1] == 0) flag = true;
			}
			if (v[n - 2] == 2) {
				if (v[n - 1] == 0) flag = true;
			}
		}
		if (v[n - 3] == 0) {
			if (v[n - 2] == 2) {
				if (v[n - 1] == 0) flag = true;
			}
		}
	}
	if (v[n - 4] == 2)
		if (v[n - 3] == 0)
			if (v[n - 2] == 2)
				if (v[n - 1] == 0) flag = true;
	if (flag) printf("yes\n");
	else printf("no\n");




}

int main() {

	int t;
	scanf("%d",&t);
	while (t--)
	{
		solve();
	}

	return 0;
}