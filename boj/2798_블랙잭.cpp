#include <stdio.h>
#include <stdlib.h>
#include <vector>

using namespace std;
int main() {
	int n, m;
	vector<int> v;

	scanf("%d %d",&n,&m);
	v.resize(n);
	for (int i = 0; i < n; i++) {
		scanf("%d",&v[i]);
	}
	int tmp1, tmp2, tmp3, res;
	res = 0;
	for (int i = 0; i < n - 2; i++) {
		if (v[i] <= m) tmp1 = v[i];
		else continue;
		for (int j = i + 1; j < n - 1; j++) {
			if (tmp1 + v[j] <= m) {
				tmp2 = tmp1 + v[j];
			}
			else continue;
			for (int k = j + 1; k < n; k++) {
				if (tmp2 + v[k] <= m) {
					tmp3 = tmp2 + v[k];
					if ((m - tmp3) < (m - res)) res = tmp3;
				}
			}
		}
	}
	printf("%d\n",res);
	return 0;
}