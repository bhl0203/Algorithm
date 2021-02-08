#include <stdio.h>
#include <string>
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
	int n;
	scanf("%d",&n);
	vector<int> v;
	v.resize(n);
	for (int i = 0; i < n; i++) {
		scanf("%d",&v[i]);
	}
	sort(v.begin(), v.end());
	printf("%d",v[0]*v[n-1]);

	return 0;
}