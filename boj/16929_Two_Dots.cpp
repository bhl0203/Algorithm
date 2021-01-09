#include <stdio.h>
#include <iostream>
#include <string>
#include <string.h>
#include <set>
#include <map>
#include <vector>

using namespace std;

int n, m;
char d[51][51];
int dist[51][51];
int dx[4] = { 1,0,-1,0 };
int dy[4] = { 0,-1,0,1 };
bool visit[51][51] = { false, };
bool flag_cycle = false;
int SX, SY;
void dfs(int x, int y, char c, int cnt) {
	if (flag_cycle) return;
	
	if (visit[x][y]) {
		if (cnt - dist[x][y] >= 4) {
			flag_cycle = true;
			return;
		}
		else return;
	}
	visit[x][y] = true;
	dist[x][y] = cnt;

	for (int i = 0; i < 4; i++) {
		int nx = x + dx[i];
		int ny = y + dy[i];
		if (nx >= 0 && nx < n && ny >= 0 && ny < m && d[nx][ny] == c) {
			dfs(nx, ny, c, cnt + 1);
		}
	}
	return;
}


int main() {
	ios_base::sync_with_stdio(false);

	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> d[i][j];
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			memset(visit, false, sizeof(visit));
			memset(dist, 0, sizeof(dist));
			SX = i;
			SY = j;
			dfs(i, j, d[i][j],0);
			if (flag_cycle) {
				cout << "Yes\n";
				return 0;
			}
		}
	}
	cout << "No\n";


	return 0;
}