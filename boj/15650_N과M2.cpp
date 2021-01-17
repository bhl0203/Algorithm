#include <stdio.h>
#include <stack>
#include <vector>
using namespace std;

int n, m;
stack<int> s;

void stk(int cur) {
	if (cur == n && (s.size() < m)) {
		return;
	}
	if (s.size() == m) {
		vector<int> v;
		stack<int> s2;
		s2 = s;
		while (!s2.empty()) {
			v.push_back(s2.top());
			s2.pop();
		}
		for (int i = m - 1; i >= 0; i--) {
			printf("%d ",v[i]);
		}
		printf("\n");
		return;
	}
	int tmp = s.top();//tmp -> 현재 위치
	int size = s.size();
	for (int i = tmp + 1; i <= n; i++) {
		s.push(i);
		stk(i);
		s.pop();
	}




}

int main() {
	scanf("%d %d",&n,&m);

	for (int i = 1; i <= (n - m + 1); i++) {
		s.push(i);
		stk(i);
		if (!s.empty()) {
			while (!s.empty()) {
				s.pop();
			}
		}
	}

	return 0;
}