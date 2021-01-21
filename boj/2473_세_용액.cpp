#include <stdio.h>
#include <vector>
#include <algorithm>
#include <limits.h>
using namespace std;
#define ll long long int
int main() {
	int n;
	vector<ll> v;
	scanf("%d",&n);
	v.resize(n);
	for (int i = 0; i < n; i++) scanf("%lld",&v[i]);
	sort(v.begin(),v.end());
	int l, m, r;
	ll res = LLONG_MAX;
	ll tmp;
	int resl, resm, resr;
	for (int l = 0; l < n - 2; l++) {
		m = l+1; r = n - 1;
		while (m<r) {
			tmp = v[l] + v[m] + v[r];
			if (llabs(tmp) < llabs(res)) {
				res = tmp;
				resl = l; resm = m; resr = r;
			}
			if (tmp >= 0) r--;
			else if (tmp < 0) m++;
		}
	}
	printf("%lld %lld %lld\n",v[resl],v[resm],v[resr]);
	return 0;
}