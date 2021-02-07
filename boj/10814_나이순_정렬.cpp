#include <stdio.h>
#include <string>
#include <algorithm>
#include <iostream>
#include <vector>
#include <functional>
using namespace std;


#define ll long long


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	vector<pair<pair<int, int>, string>> v;
	int n;
	cin >> n;
	string str;
	int age;
	for (int i = 0; i < n; i++) {
		cin >> age >> str;
		v.push_back({ { age,i }, str });
	}
	sort(v.begin(), v.end());
	for (int i = 0; i < n; i++) {
		cout << v[i].first.first << " " << v[i].second << '\n';
	}
	return 0;
}