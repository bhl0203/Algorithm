#include <stdio.h>
#include <stack>
#include <vector>
using namespace std;
stack<int> s;
int n, m;
void p(int x) {

	if (s.size() == m) {
		stack<int> tmp = s;
		vector<int> v;
		while (!tmp.empty()) {
			v.push_back(tmp.top());
			tmp.pop();
		}
		for (int i = m - 1; i >= 0; i--) printf("%d ", v[i]);
		printf("\n");
		return;
	}
	
	for (int i = s.top(); i <= n; i++) {
		s.push(i);
		p(i);
		s.pop();
	}
}

int main() {

	scanf("%d %d", &n, &m);

	for (int i = 1; i <= n; i++) {
		s.push(i);
		p(i);
		while (!s.empty()) {
			s.pop();
		}
	}
	return 0;
}