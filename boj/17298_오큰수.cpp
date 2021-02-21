#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
#include <stack>
#include <queue>

using namespace std;
#define ll long long

int main() {
	int n;
	scanf("%d",&n);
	vector<int> v(n);
	stack<int> s;
	for (int i = 0; i < n; i++) {
		scanf("%d",&v[i]);
	}
	int cur;
	vector<int> res(n);
	for (int i = n - 1; i >= 0; i--) {
		cur = v[i];
		while (!s.empty()) {
			if (s.top() > cur) {
				res[i] = s.top();
				s.push(cur);
				break;
			}
			else if (s.top() <= cur) {
				s.pop();
			}
		}
		if (s.empty()) {
			res[i] = -1;
			s.push(cur);
			continue;
		}
	}
	for (int i = 0; i < n; i++) {
		printf("%d ",res[i]);
	}

	return 0;
}