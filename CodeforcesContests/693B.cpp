#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define ll long long




void solve() {
	int n;
	scanf("%d",&n);
	int k;
	int c1 = 0;
	int c2 = 0;;
	while (n--) {
		scanf("%d",&k);
		if (k == 1) c1++;
		if (k == 2) c2++;
		if (c1 >= 4) {
			c1 = 2;
			c2++;
		}
	}
	if (c2 % 2 == 0) {
		switch (c1) {
		case 0: printf("YES\n");
			break;
		case 1:printf("NO\n");
			break;
		case 2:printf("YES\n");
			break;
		case 3:printf("NO\n");
			break;
		}
	}
	if (c2 % 2 == 1) {
		switch (c1) {
		case 0:printf("NO\n");
			break;
		case 1:printf("NO\n");
			break;
		case 2:printf("YES\n");
			break;
		case 3:printf("NO\n");
			break;
		}
	}
}



int main() {
	int t;
	scanf("%d",&t);
	while (t--) {
		solve();
	}

	return 0;
}