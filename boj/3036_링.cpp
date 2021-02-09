#include <stdio.h>
#include <string>
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int solve(int a, int b) {
	int gcd;
	while (1) {
		if (a > b) {
			if (a % b == 0) {
				return b;
			}
			else {
				a = a % b;
			}
		}
		else if (a == b) {
			return a;
		}
		else if (b > a) {
			if (b % a == 0) {
				return a;
			}
			else b = b % a;
		}
	}
	


	return 1;
}


int main() {
	int n;
	scanf("%d",&n);
	int k;
	scanf("%d",&k);
	vector<int> v(n - 1);
	int res;
	for (int i = 0; i < n - 1; i++) {
		scanf("%d", &v[i]);
		res = solve(k, v[i]);
		printf("%d/%d\n",k/res,v[i]/res);
	}

	return 0;
}