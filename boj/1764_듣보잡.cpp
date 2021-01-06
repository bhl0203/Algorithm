#include <stdio.h>
#include <iostream>
#include <string>
#include <set>
#include <map>
#include <vector>

using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int n, m;
	string s;
	set<string> md, mb;
	int res = 0;
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		cin >> s;
		md.insert(s);
	}
	for (int i = 0; i < m; i++) {
		cin >> s;
		mb.insert(s);
	}
	for (auto it = md.begin(); it != md.end(); it++) {
		if (mb.count(*it)) res++;
	}
	cout << res << '\n';

	for (auto it = md.begin(); it != md.end(); it++) {
		if (mb.count(*it)) cout<<*it<<'\n';
	}


	return 0;
}