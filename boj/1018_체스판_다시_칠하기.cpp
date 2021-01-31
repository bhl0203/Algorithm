#include <stdio.h>
#include <vector>
#include <algorithm>
#include <iostream>
#include <string>

using namespace std;
vector<string> v;
vector<vector<int>> mini;

void min_find(int x, int y) {

	int b = 0;//v[x][y]가 검은색일때 바꿔야 하는 칸의 개수
	int w = 0;//v[x][y]가 흰색일때 바꿔야 하는 칸의 개수

	//v[x][y]가 검정일때

	for (int i = x; i < x + 8; i++) {
		for (int j = y; j < y + 8; j++) {
			if ((i + j) % 2 == 0) {
				if (v[i][j] == 'W') b++;
			}
			else if ((i + j) % 2 == 1) {
				if (v[i][j] == 'B') b++;
			}
		}
	}


	//v[x][y]가 흰색일때
	for (int i = x; i < x + 8; i++) {
		for (int j = y; j < y + 8; j++) {
			if ((i + j) % 2 == 0) {
				if (v[i][j] == 'B') w++;
			}
			else if ((i + j) % 2 == 1) {
				if (v[i][j] == 'W') w++;
			}
		}
	}
	mini[x][y] = (b > w ? w : b);

}


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	int n, m;
	cin >> n >> m;
	v.resize(n);
	mini.resize(n - 7);
	for (int i = 0; i < n - 7; i++) {
		mini[i].resize(m - 7);
	}

	for (int i = 0; i < n; i++) {
		cin >> v[i];
	}
	for (int i = 0; i <= n - 8; i++) {
		for (int j = 0; j <= m - 8; j++) {
			min_find(i, j);
		}
	}
	int res = 64;
	for (int i = 0; i <= n - 8; i++) {
		for (int j = 0; j <= m - 8; j++) {
			if (mini[i][j] < res) {
				res = mini[i][j];
			}
		}
	}
	cout << res;
	return 0;
}