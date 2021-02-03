#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;

#define ll long long

void solve() {
	int n;
	scanf("%d",&n);
	vector<int> v(n+1);
	vector<ll> res(n+1);
	
	for (int i = 1; i <= n; i++) {
		scanf("%d",&v[i]);
		//if (res[i] < v[i]) res[i] = v[i];
		res[i] += v[i];
		if (i + v[i] <= n) {
			if (res[i + v[i]] <= res[i]) res[i + v[i]] = res[i];
		}
	}
	
	ll maxi = 0;
	//최대값 구하기
	for (int i = 1; i <= n; i++) {
		if (res[i] > maxi) maxi = res[i];
	}
	printf("%lld\n",maxi);
}


int main() {

	int t;
	scanf("%d",&t);
	while (t--) solve();
	return 0;
}