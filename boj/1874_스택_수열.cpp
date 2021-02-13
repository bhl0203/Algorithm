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
	vector<char> cv;
	int cur = 1;
	for (int i = 0; i < n; i++) {
		scanf("%d",&v[i]);
	}
	for (int i = 0; i < n; i++) {
		if (v[i] >= cur) {
			while (v[i] >= cur) {
				s.push(cur);
				cv.push_back('+');
				cur++;
			}
			s.pop();
			cv.push_back('-');
		}
		else if (v[i] < cur) {
			if (s.top() != v[i]) {
				printf("NO\n");
				return 0;
			}
			else{
				s.pop();
				cv.push_back('-');
			}
		}
	}
	for (int i = 0; i < cv.size(); i++) {
		printf("%c\n",cv[i]);
	}
	return 0;
}