#include <stdio.h>
#include <iostream>
#include <vector>

using namespace std;

#define ll long long

int main() {

	ll t;
	scanf("%lld",&t);
	ll a, b, k;
	while (t--) {
		scanf("%lld %lld %lld", &a, &b, &k);
		vector<ll> va, vb;
		vector<pair<ll, ll>> vp;
		vector<ll> A, B;
		A.resize(a + 1, 0);
		B.resize(b + 1, 0);
		va.resize(k);
		vb.resize(k);
		for (ll i = 0; i < k; i++) {
			scanf("%lld", &va[i]);
			A[va[i]]++;
		}
		for (ll i = 0; i < k; i++) {
			scanf("%lld", &vb[i]);
			B[vb[i]]++;
		}


		ll res = k * (k - 1);

		for (ll i = 0; i < k; i++) {
			res -= (A[va[i]] - 1 + B[vb[i]] - 1);
		}
		printf("%lld\n",res/2);
	}

	return 0;
}