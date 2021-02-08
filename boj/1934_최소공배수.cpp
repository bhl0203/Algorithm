#include <stdio.h>
#include <string>
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

void solve() {
	int a, b;
	scanf("%d %d", &a, &b);
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
	printf("%d\n", gcd * (a / gcd) * (b / gcd));

}


int main() {
	int t;
	scanf("%d",&t);
	while (t--)solve();
	return 0;
}