#include <stdio.h>
#include <string>
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int solve(int a, int b) {
	int ta = a;
	int tb = b;
	int gcd;
	while (1) {
		if (ta > tb) {
			if (ta % tb == 0) {
				gcd = tb;
				break;
			}
			else ta = ta % tb;
		}
		else if (tb == ta) {
			gcd = tb;
			break;
		}
		else if (tb > ta) {
			if (tb % ta == 0) {
				gcd = ta;
				break;
			}
			else tb = (tb % ta);
		}
	}
	
	return gcd;

}

int main() {
	int n;
	scanf("%d",&n);
	vector<int> v(n);

	for (int i = 0; i < n; i++) {
		scanf("%d",&v[i]);
	}
	sort(v.begin(), v.end());
	int gcd = v[1]-v[0];
	for (int i = 2; i < n; i++) {
		gcd = solve(gcd, v[i] - v[i - 1]);
	}
	//gcd = v[1]-v[0]~v[n-1]-v[n-2]의 최대공약수

	vector<int> res;
	for (int i = 2; i * i <= gcd; i++) {
		if (gcd % i == 0) {
			res.push_back(i);
			res.push_back(gcd / i);
		}
	}
	res.push_back(gcd);
	sort(res.begin(), res.end());
	int tmp = 0;
	for (int i = 0; i < res.size(); i++) {
		if (tmp == res[i]) continue;
		printf("%d ",res[i]);
		tmp = res[i];
	}
	return 0;
}