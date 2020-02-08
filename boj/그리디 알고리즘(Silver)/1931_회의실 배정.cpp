#include <cstdio>
#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

int main() {
	vector <pair<int, int>> v;
	pair<int, int> tmp;
	int t = 0;
	int temp;
	int cnt = 0;
	v.reserve(100001);
	int N;
	scanf("%d",&N);
	for (int i = 0; i < N; i++) {
		scanf("%d %d",&tmp.first,&tmp.second);
		v.push_back(tmp);
	}
	for (int i = 0; i < N; i++) {
		temp = v[i].first;
		v[i].first = v[i].second;
		v[i].second = temp;
	}
	sort(v.begin(), v.end());
	for (int i = 0; i < N; i++) {
		temp = v[i].first;
		v[i].first = v[i].second;
		v[i].second = temp;
	}
	for (int i = 0; i < v.size(); i++) {
		if (v[i].first >= t) {
			t = v[i].second;
			cnt++;
		}
	}

	printf("%d",cnt);
	return 0;
}