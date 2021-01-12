#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <algorithm>
#include <vector>
#include <queue>
#define INF 999999999
using namespace std;

int n, m;
vector<vector<pair<int,int>>> v;
vector<int> dist;
priority_queue<pair<int,int>> pq;

void bfs(int x) {

	pq.push({ x,0 });
	while (!pq.empty()) {
		int idx = pq.top().first;
		int cost = pq.top().second;
		pq.pop();
		if (dist[idx] < cost) continue;
		for (int i = 0; i < v[idx].size(); i++) {
			int nextidx = v[idx][i].first;
			int nextcost = v[idx][i].second;
			if (dist[idx] + nextcost < dist[nextidx]) {
				dist[nextidx] = dist[idx] + nextcost;
				pq.push({nextidx,dist[nextidx]});
			}
		}
	}
}


int main() {
	scanf("%d %d",&n,&m);
	v.resize(n + 1);
	dist.resize(n + 1, INF);
	dist[1] = 0;
	int a, b, c;
	for (int i = 0; i < m; i++) {
		scanf("%d %d %d", &a, &b, &c);
		v[a].push_back({ b,c });
		v[b].push_back({ a,c });
	}
	bfs(1);
	printf("%d\n", dist[n]);
	return 0;
}