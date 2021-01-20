#include <stdio.h>
#include <vector>
using namespace std;

vector<int> v;

int main() {

	int n, s;
	scanf("%d %d",&n,&s);
	int l, r;
	l = 0;	r = 0;

	v.resize(n);
	for (int i = 0; i < n; i++) {
		scanf("%d", &v[i]);
	}
	int sum, res;
	sum = 0;
	res = 100001;
	int len;
	while (r < n) {
		if (sum < s) {
			sum += v[r];
			r++;
		}
		if (sum >= s) {
			len = r - l;
			if (len < res) res = len;
			sum -= v[l];
			l++;
		}
	}

	while (sum >= s) {
		len = r - l;
		if (len < res) res = len;
		sum -= v[l];
		l++;
	}
	if (res == 100001) printf("0\n");
	else printf("%d\n",res);


	return 0;
}