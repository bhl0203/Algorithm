#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	string str;
	cin >> str;
	int l = str.length();
	vector<int> v;
	for (int i = 0; i < l; i++) {
		v.push_back(str[i]-'0');
	}
	sort(v.begin(), v.end(),greater<>());
	for (int i = 0; i < v.size(); i++) printf("%d",v[i]);
	return 0;
}