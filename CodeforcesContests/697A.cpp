#include <stdio.h>
#include <iostream>
#include <vector>

using namespace std;

#define ll long long

int main() {

	int t;
	scanf("%d",&t);
	ll n;
	while (t--) {
		int flag = 0;
		scanf("%lld",&n);
		while (n) {
			if (n % 2 == 1) {
				printf("YES\n");
				flag = 1;
				break;
			}
			n /= 2;
			if (n == 1) break;
		}
		if (flag == 1) continue;
		if (flag == 0) {
			printf("NO\n");
		}
	}

	return 0;
}
