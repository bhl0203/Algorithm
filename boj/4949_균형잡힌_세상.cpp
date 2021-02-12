#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
#include <stack>

using namespace std;
#define ll long long

int main() {
	char c;
	stack<char> st;
	bool flag = false;
	bool start = false;
	bool end;
	while (1) {
		while (!st.empty()) st.pop();
		start = false;
		flag = false;
		end = false;
		while (1) {
			scanf("%c",&c);
			if (c == '\n') continue;
			if (!start && c == '.') return 0;
			if (!start) start = true;
			switch (c) {
				case '(':
					st.push(c);
					break;
				case '[':
					st.push(c);
					break;
				case ')':
					if (st.empty() || st.top() != '(') {
						flag = true;
					}
					else if (st.top() == '(') {
						st.pop();
					}
					break;
				case ']':
					if (st.empty() || st.top() != '[') {
						flag = true;
					}
					else if (st.top() == '[') {
 						st.pop();
					}
					break;
				case '.':
					end = true;
					if (flag || !st.empty()) printf("no\n");
					else printf("yes\n");
					break;
				default:
					break;
			}
			if (end) {
				break;
			}

		}
	}
	

	return 0;
}