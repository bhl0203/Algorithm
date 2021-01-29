#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <vector>
using namespace std;


int main() {
	int n;
	scanf("%d",&n);
	vector<int> v(n);
	vector<int> m(8001,0);
	vector<int> mfrq;
	int avg = 0;
	int mid;
	int frq = -4000;
	int range;
	int maxi = -4000;
	int mini = 4000;
	for (int i = 0; i < n; i++) {
		scanf("%d",&v[i]);
		m[v[i] + 4000]++;
		avg += v[i];
		if (v[i] > maxi) maxi = v[i];
		if (v[i] < mini) mini = v[i];
	}
	sort(v.begin(), v.end());

	mid = v[n / 2];//Áß¾Ó°ª

	//ÃÖºó°ª
	for (int i = 0; i < 8001; i++) {
		if (m[i] > frq) {
			frq = m[i];
		}
	}
	for (int i = 0; i < 8001; i++) {
		if (m[i] == frq) {
			mfrq.push_back(i);
		}
	}
	if (mfrq.size() == 1) frq = mfrq[0];
	else if (mfrq.size() > 1) {
		sort(mfrq.begin(), mfrq.end());
		frq = mfrq[1];
	}
	frq -= 4000;
	//¹üÀ§
	range = maxi - mini;
	printf("%1.lf\n%d\n%d\n%d\n",(double)avg/n,mid,frq,range);

	return 0;
}