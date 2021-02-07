#include <stdio.h>
#include <string>
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {

	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	vector<pair<int, string>> v;
	int n;
	cin >> n;
	string str;
	for (int i = 0; i < n; i++) {
		cin >> str;
		v.push_back({ str.length(), str });
	}
	sort(v.begin(), v.end());
	string tmp;
	for (int i = 0; i < n; i++) {
		if (v[i].second == tmp) continue;
		cout << v[i].second << '\n';
		tmp = v[i].second;
	}
	return 0;
}