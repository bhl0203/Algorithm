#include <stdio.h>
#include <string.h>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;
vector<string> ss;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	string s;
	cin >> s;
	int l = s.size();
	
	for (int i = 0; i < l; i++) {
		ss.push_back(&(s[i]));
	}
	sort(ss.begin(),ss.end());
	for (int i = 0; i < l; i++) cout << ss[i]+"\n";

	return 0;
}