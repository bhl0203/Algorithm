#include <stdio.h>
#include <vector>
using namespace std;

int n;
int T;
int cnt = 0;

vector<vector<int>> com;
vector<int> visit;

void dfs(int a) {
	if (visit[a] == 1) return;
	visit[a] = 1;
	cnt++;
	for (int i = 0; i < com[a].size(); i++) {
		if (visit[com[a][i]] == 0) dfs(com[a][i]);
	}
}


int main() {

	int a, b;

	scanf("%d",&n);
	com.resize(n + 1);
	visit.resize(n + 1,0);

	scanf("%d",&T);
	for (int i = 0; i < T; i++) {
		scanf("%d %d", &a, &b);
		com[a].push_back(b);
		com[b].push_back(a);
	}
	dfs(1);
	printf("%d\n",cnt-1);
	return 0;
}