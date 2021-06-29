#include <stdio.h>
#define ll long long
void test() {
	
	ll n, x, t;
	ll sum = 0;
	scanf("%lld %lld %lld",&n, &x,&t);
	/*
	for (int i = 1; i < n; i++) {
		sum += tmp;
		if (tmp < (t / x)) tmp++;
	}*/

	ll k = t / x;
	if (k<=n) {
		sum += (k + 1) * k / 2;
		sum += (n - 1 - k) * k;
	}
	else {
		sum += (n-1)*n / 2;
	}
	printf("%lld\n",sum);

}


int main() {

	int n, k, t;
	scanf("%d",&k);

	while (k--) {
		test();
	}


	return 0;
}
