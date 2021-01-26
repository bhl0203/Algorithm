#include <stdio.h>
#include <iostream>
#include <vector>

using namespace std;

#define ll long long


bool flag = false;

void cal(int x) {
	if (x % 2021 == 0 || x % 2020 == 0) {
		flag = true;
		return;
	}
	while (x > 0) {
		if (x % 10 != 0) {
			x = x - (2021 * (x % 10));
		}

		if (x == 0) {
			flag = true;
			return;
		}
		if (x < 0) return;

		if (x % 10 == 0) {
			if (x % 2020 != 0) {
				x = x - 2021 * 10;
			}
			else if (x % 2020 == 0) {
				flag = true;
				return;
			}
		}
	}
	if (x == 0) {
		flag = true;
		return;
	}
	if (x < 0) return;

	return;
}

int main() {

	int t;

	int n;
	scanf("%d",&t);
	while (t--) {
		scanf("%d",&n);
		flag = false;
		cal(n);
		if (!flag) printf("NO\n");
		if (flag) printf("YES\n");
	}

	return 0;
}