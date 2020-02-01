#include <cstdio>
#include <algorithm>
#include <vector>
#include <utility>
using namespace std;
int main() {
	int T, n;
	vector<pair<int, int>> v;
	v.reserve(100001);
	pair<int, int> tmp;
	int cnt;
	int cur_sc;
	int a, b;
	scanf("%d",&T);
	while (T--) {
		cnt = 0;
		cur_sc = 100001;
		v.clear();
		scanf("%d",&n);
		for (int i = 0; i < n; i++) {
			scanf("%d %d",&tmp.first,&tmp.second);
			v.push_back(tmp);
		}
		sort(v.begin(), v.end());
		for (int i = 0; i < v.size(); i++) {
			if (v[i].second < cur_sc) {
				cnt++;
				cur_sc = v[i].second;
			}
		}
		printf("%d\n", cnt);
	}

	return 0;
}