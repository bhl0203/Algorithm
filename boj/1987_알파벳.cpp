#include <stdio.h>
#include <iostream>
#include <string>
#include <string.h>
#include <set>
#include <map>
#include <vector>

using namespace std;

int r, c;
int nx[4] = { 1,0,-1,0 };
int ny[4] = { 0,-1,0,1 };
char m[21][21];
int visit[26] = { 0, };
int max_a = 0;

void dfs(int x, int y, int path) {
	if (visit[m[x][y]-'A'] == 1) return;
	visit[m[x][y] - 'A'] = 1;
	if (path > max_a) max_a = path;
	for (int i = 0; i < 4; i++) {
		int nnx = x + nx[i];
		int nny = y + ny[i];
		int flag = 0;
		if (nnx >= 0 && nnx < r && nny >= 0 && nny < c) {//다음 위치가 범위 안에 있고
			if (visit[m[nnx][nny] - 'A'] == 0) {//방문한적 없는 알파벳이면
				dfs(nnx, nny, path + 1);
				visit[m[nnx][nny] - 'A'] = 0;
			}
		}
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin >> r >> c;
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			cin >> m[i][j];
		}
	}
	dfs(0, 0, 1);
	cout << max_a;
	return 0;
}