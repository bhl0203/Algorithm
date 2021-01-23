#include <stdio.h>
#include <vector>
using namespace std;
#define ll long long int

int main() {
	int n;
	scanf("%d",&n);
	vector<ll> price;
	vector<ll> dist;
	ll low = 1000000001;
	dist.resize(n - 1);
	price.resize(n);
	for (int i = 0; i < n - 1; i++) scanf("%d", &dist[i]);
	for (int i = 0; i < n; i++) {
		scanf("%d", &price[i]);
		if (low > price[i]) low = price[i];
	}
	ll sum = 0;
	ll cur = 1000000001;
	for (int i = 0; i < n-1; i++) {
		if (price[i] < cur) cur = price[i];
		sum += dist[i] * cur;
	}

	printf("%lld\n",sum);

	return 0;
}