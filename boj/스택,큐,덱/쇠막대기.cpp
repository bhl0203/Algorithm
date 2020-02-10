#include <cstdio>
#include <stack>
using namespace std;

int main() {
	stack<char> s;
	char c = 'c';
	char pc;
	int cnt = 0;
	while (1) {
		pc = c;
		scanf("%c",&c);
		if (c == '\n') break;
		if (c == '(') s.push(c);
		if (c == ')') {
			s.pop();
			if (pc == '(') {//lazer
				cnt = cnt + s.size();
			}
			if (pc == ')') {//metal stick
				cnt++;

			}
		}
	}

	
	printf("%d\n",cnt);
	return 0;
}
