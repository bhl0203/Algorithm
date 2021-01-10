#include <stdio.h>
#include <string.h>

int m[51][51] = { 0, };
bool v[51][51] = { false, };
int dx[8] = { 1,1,0,-1,-1,-1,0,1 };
int dy[8] = { 0,-1,-1,-1,0,1,1,1 };
int w, h;
int cnt = 0;

void dfs(int x, int y) {
	v[x][y] = true;
	for (int i = 0; i < 8; i++) {
		int nx = x + dx[i];
		int ny = y + dy[i];
		if (nx >= 0 && nx < h && ny >= 0 && ny < w && m[nx][ny] == 1 && !v[nx][ny]) {
			dfs(nx, ny);
		}
	}


}

int main() {
	while (1) {
		scanf("%d %d", &w, &h);
		if (!w && !h) return 0;
		cnt = 0;
		memset(v, false, sizeof(v));
		for (int i = 0; i < h; i++) {
			for (int j = 0; j < w; j++) {
				scanf("%1d", &m[i][j]);
			}
		}
		for (int i = 0; i < h; i++) {
			for (int j = 0; j < w; j++) {
				if (m[i][j] == 1 && !v[i][j]) {
					dfs(i, j);
					cnt++;
				}
			}
		}
		printf("%d\n", cnt);
	}

	return 0;
}