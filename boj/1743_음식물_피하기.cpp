#include <stdio.h>


int n, m, k;
int mp[101][101] = { 0, };
int visit[101][101] = { 0, };
int bf = 0;
int max_bf;

int nx[4] = { 1,0,-1,0 };
int ny[4] = { 0,-1,0,1 };



void dfs(int x, int y) {
	if (visit[x][y] == 1) return;
	visit[x][y] = 1;
	for (int i = 0; i < 4; i++) {
		int nnx = x + nx[i];
		int nny = y + ny[i];
		if ((visit[nnx][nny] == 0) && (nnx >= 1) && (nnx <= n) && (nny >= 1) && (nny <= m) && (mp[nnx][nny] == 1)) {
			bf++;
			dfs(nnx, nny);
		}

	}

}


int main() {
	int x, y;

	scanf("%d %d %d",&n,&m,&k);//세로x 가로 y
	for (int i = 0; i < k; i++) {
		scanf("%d %d", &x, &y);
		mp[x][y] = 1;
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			bf = 1;
			if(visit[i][j] == 0 && mp[i][j] == 1) dfs(i, j);
			if (bf > max_bf) max_bf = bf;
		}
	}
	printf("%d\n",max_bf);
	return 0;
}