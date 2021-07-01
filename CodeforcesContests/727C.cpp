#include <iostream>
#include <string>
#include <algorithm>

#define ll long long
using namespace std;

ll arr[200001];
ll gap[200000];
void test() {
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	ll n, k, x;
	cin >> n >> k >> x;

	for (int i = 0; i < n; i++) {
		cin >> arr[i];
	}
	sort(arr, arr + n);
	int cnt = 0;
	for (int i = 0; i < n - 1; i++) {
		if (arr[i + 1] - arr[i] > x) {
			gap[cnt++] = arr[i + 1] - arr[i];
		}
	}
	sort(gap, gap + cnt);
	int res = cnt + 1;
	for (int i = 0; i < cnt; i++) {

		if (gap[i] / x <= k) {
			if (gap[i] % x) {
				k -= gap[i] / x;
				res -= 1;
			}
			else {
				k -= (gap[i] / x - 1);
				res -= 1;
			}
		}
		else if (gap[i] / x == k + 1) {
			if (gap[i] % x == 0) {
				k -= (gap[i] / x - 1);
				res -= 1;
			}
		}
		else break;
	}
	cout << res;

	return 0;
}
