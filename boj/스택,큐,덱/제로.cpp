#include <cstdio>
#include <stack>
using namespace std;

int main() {
	int sum = 0;
	stack<int> s;
	int n;
	int tmp;
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d",&tmp);
		if (tmp == 0) s.pop();
		else s.push(tmp);
	}
	while (!s.empty()) {
		tmp = s.top();
		s.pop();
		sum += tmp;
	}
	printf("%d",sum);

	return 0;
}