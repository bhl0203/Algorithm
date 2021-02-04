#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;

#define ll long long

bool comp(int x, int y) {
	return x > y;
}

void solve() {
	int n;
	scanf("%d",&n);
	vector<int> v(n);
	int k;
	for (int i = 0; i < n; i++) {
		scanf("%d",&v[i]);
	}
	sort(v.begin(), v.end(), comp);
	ll alice = 0;
	ll bob = 0;
	for (int i = 0; i < n; i++) {
		if (i % 2 == 0) {//Alice
			if(v[i]%2 == 0){//gets score
				alice += v[i];
			}
		}
		if (i % 2 == 1) {//Bob
			if (v[i] % 2 == 1) {//gets score
				bob += v[i];
			}
		}
	}
	if (alice > bob) printf("Alice\n");
	else if (alice == bob) printf("Tie\n");
	else printf("Bob\n");
}

int main() {
	int t;
	scanf("%d",&t);
	while (t--) solve();

	return 0;
}