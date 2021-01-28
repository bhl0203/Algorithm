#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define ll long long
vector<vector<ll>> nr;


int main() {

	int t;
	scanf("%d",&t);
	ll n, k;
	//ncr 미리 계산
	nr.resize(1001);
	for (int i = 0; i < 1001; i++) {
		nr[i].resize(1001, 0);
	}
	for (int i = 0; i < 1001; i++) {
		nr[i][i] = 1;
		nr[i][0] = 1;
	}
	for (int i = 2; i < 1001; i++) {
		for (int j = 1; j < 1001; j++) {
			nr[i][j] = (nr[i - 1][j - 1] + nr[i - 1][j]) % 1000000007;
		}
	}

	while (t--) {
		scanf("%lld %lld", &n, &k);
		vector<int> v;
		v.resize(n + 1, 0);
		int x;
		for (int i = 0; i < n; i++) {
			scanf("%d",&x);
			v[x]++;
		}
		//v[x]개 만큼 있음
		ll res = 1;
		bool flag = false;
		for (int i = n; i >= 0; i--) {
			if (v[i] == 0) continue;
			if (v[i] >= k) {
				printf("%lld\n",res*(nr[v[i]][k])%1000000007);
				break;
			}
			else {
				//res *= v[i];
				k -= v[i];
			}
		}
	}



	return 0;
}