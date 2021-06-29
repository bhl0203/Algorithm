#include <iostream>
#include <string>
#define ll long long
using namespace std;

ll res[100001];
string str;

void test() {
	int l, r;
	cin >> l >> r;
	ll sum = 0;
	l--;
	r--;
	sum = res[r] - res[l] + (str[l] - 'a' + 1);
	cout << sum << '\n';
}

int main() {
	ll n, q;
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> n >> q;
	cin >> str;
	res[0] = str[0]-'a'+1;
	for (int i = 1; i < n; i++) {
		res[i] = res[i - 1] + str[i] - 'a' + 1;
	}
	while (q--) {
		test();
	}

	return 0;
}
