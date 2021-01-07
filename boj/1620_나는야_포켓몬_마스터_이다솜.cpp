#include <stdio.h>
#include <iostream>
#include <string>
#include <string.h>
#include <set>
#include <map>
#include <vector>

using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	int n, m;

	cin >> n >> m;
	map<string, int> p;
	map<int, string> q;
	string s;
	for (int i = 0; i < n; i++) {
		cin >> s;
		p.insert(make_pair(s, i + 1));
		q.insert(make_pair(i + 1, s));
	}
	for (int i = 0; i < m; i++) {
		cin >> s;
		if (s[0] <= '9' && s[0] >= '0') {
			cout << q.find(atoi(s.c_str()))->second << '\n';
		}
		else {
			cout << p.find(s)->second << '\n';
		}
	}

	return 0;
}