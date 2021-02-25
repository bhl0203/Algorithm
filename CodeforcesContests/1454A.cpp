#include <stdio.h>
#include <vector>
#include <iostream>
#include <queue>
#include <tuple>
#include <stack>
#include <algorithm>
#include <functional>

using namespace std;


#define ll long long

void solve() {
	int n;

	scanf("%d", &n);
	printf("%d ", n);
	for (int i = 1; i < n; i++) printf("%d ", i);

	printf("\n");

}

int main() {
	int t;
	scanf("%d", &t);
	while (t--) {
		solve();
	}
}