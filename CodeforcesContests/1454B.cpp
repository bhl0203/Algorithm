#include <stdio.h>
#include <vector>
#include <iostream>
#include <queue>
#include <tuple>
#include <stack>
#include <algorithm>
#include <functional>

using namespace std;


#define ll long long

void solve() {
	int n;

	scanf("%d", &n);
	vector<pair<int, int>> v(n + 1);
	int tmp;
	for (int i = 1; i <= n; i++) {
		scanf("%d", &tmp);
		v[i].first = tmp;
		v[i].second = i;
	}
	sort(v.begin(), v.end());
	int res = -1;
	bool flag = false;
	for (int i = 1; i <= n; i++) {
		if (i == n) {
			if (!flag) {
				res = v[i].second;
				break;
			}
			else break;
		}
		if (v[i].first == v[i + 1].first) {
			flag = true;
			res = -1;
		}
		if (flag && v[i].first != v[i + 1].first) {
			flag = false;
			continue;
		}
		if (!flag && v[i].first != v[i + 1].first) {
			res = v[i].second;
			break;
		}
	}

	printf("%d\n", res);

}

int main() {
	int t;
	scanf("%d", &t);
	while (t--) {
		solve();
	}
}