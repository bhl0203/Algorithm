#include <stdio.h>
#include <stack>
#include <vector>
using namespace std;
stack<int> s;
bool c[9] = {false, };
int n, m;
void p(int x) {
	
	if (s.size() == m) {
		stack<int> tmp = s;
		vector<int> v;
		while (!tmp.empty()) {
			v.push_back(tmp.top());
			tmp.pop();
		}
		for (int i = m - 1; i >= 0; i--) printf("%d ",v[i]);
		printf("\n");
		return;
	}
	for (int i = 1; i <= n; i++) {
		if (c[i]) continue;
		else {
			s.push(i);
			c[i] = true;
			p(i);
			c[s.top()] = false;
			s.pop();
		}
	}
}

int main() {

	scanf("%d %d",&n,&m);

	for (int i = 1; i <= n; i++) {
		s.push(i);
		c[i] = true;
		p(i);
		while (!s.empty()) {
			c[s.top()] = false;
			s.pop();
		}
	}
	return 0;
}