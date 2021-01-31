#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

int main() {

	int n;
	vector<pair<int,int>> v;
	scanf("%d",&n);
	v.resize(n);
	for (int i = 0; i < n; i++) {
		scanf("%d %d",&v[i].first,&v[i].second);
	}
	int cnt;
	for (int i = 0; i < n; i++) {
		cnt = 0;
		for (int j = 0; j < n; j++) {
			if (v[i].first < v[j].first && v[i].second < v[j].second) cnt++;
		}
		printf("%d ",++cnt);
	}
	return 0;
}