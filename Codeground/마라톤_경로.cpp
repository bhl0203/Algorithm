#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>

using namespace std;

#define ll long long
#define MAX 99999999


vector<vector<vector<int>>> dp;
vector<vector<int>> path;
vector<vector<bool>> water;

int Answer;


int M, N, K;
int tmp;

void ini() {

	Answer = 0;
	cin >> M >> N >> K;
	dp.resize(N + 1);
	path.resize(N + 1);
	water.resize(N + 1);
	for (int i = 0; i <= N; i++) {
		dp[i].resize(M + 1);
		path[i].resize(M + 1);
		water[i].resize(M + 1, false);
	}
	for (int i = 0; i <= N; i++) {
		for (int j = 0; j <= M; j++) {
			dp[i][j].resize(11);
		}
	}

	for (int i = 0; i <= N; i++) {
		for (int j = 0; j <= M; j++) {
			for (int k = 0; k <= 10; k++) {
				dp[i][j][k] = MAX;
			}
		}
	}
	dp[0][0][0] = 0;
	int tmp;
	for (int i = 0; i <= N; i++) {
		for (int j = 0; j <= M; j++) {
			cin >> tmp;
			if (tmp > 0) {//물통이 없을 때
				path[i][j] = tmp;
				if (i == 0 && j != 0) {
					for (int k = 0; k <= 10; k++) {
						if (dp[i][j - 1][k] != MAX) {
							dp[i][j][k] = dp[i][j - 1][k] + abs(path[i][j] - path[i][j - 1]);
						}
					}
				}
				if (j == 0 && i != 0) {
					for (int k = 0; k <= 10; k++) {
						if (dp[i - 1][j][k] != MAX) {
							dp[i][j][k] = dp[i - 1][j][k] + abs(path[i][j] - path[i - 1][j]);
						}
					}
				}
			}
			else {//물통이 있을 때
				path[i][j] = -tmp;
				water[i][j] = true;
				
				if (i == 0 && j != 0) {
					for (int k = 0; k <= 10; k++) {
						if (k < 10) {
							if (dp[i][j - 1][k] != MAX) {
								dp[i][j][k + 1] = dp[i][j - 1][k] + abs(path[i][j] - path[i][j - 1]);
							}
						}
						else if (k == 10) {
							if (dp[i][j - 1][k] != MAX) {
								dp[i][j][k] = dp[i][j - 1][k] + abs(path[i][j] - path[i][j - 1]);
							}
						}
					}
				}
				if (j == 0 && i != 0) {
					for (int k = 0; k <= 10; k++) {
						if (k < 10) {
							if (dp[i - 1][j][k] != MAX) {
								dp[i][j][k + 1] = dp[i - 1][j][k] + abs(path[i][j] - path[i - 1][j]);
							}
						}
						else if (k == 10) {
							if (dp[i - 1][j][k] != MAX) {
								dp[i][j][k] = dp[i - 1][j][k] + abs(path[i][j] - path[i - 1][j]);
							}
						}
					}
				}
				
			}
		}
	}
}

void solve() {

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {

			if (water[i][j] == false) {//물통이 없음
				
				for (int k = 0; k <= 10; k++) {
					dp[i][j][k] = min(
						dp[i - 1][j][k] + abs(path[i][j] - path[i - 1][j]),
						dp[i][j - 1][k] + abs(path[i][j - 1] - path[i][j])
					);
					if (dp[i][j][k] >= MAX) dp[i][j][k] = MAX;
				}

			}
			else {//물통이 있음

				for (int k = 0; k <= 10; k++) {
					if (k < 10) {
						dp[i][j][k + 1] = min(
							dp[i - 1][j][k] + abs(path[i][j] - path[i - 1][j]),
							dp[i][j - 1][k] + abs(path[i][j - 1] - path[i][j])
						);
						if (dp[i][j][k + 1] >= MAX) dp[i][j][k + 1] = MAX;


					}
					else if (k == 10) {
						dp[i][j][k] = min(
							min(dp[i-1][j][9]+abs(path[i][j]-path[i-1][j]),
								dp[i-1][j][10]+abs(path[i][j]-path[i-1][j]))
							,
							min(dp[i][j - 1][9] + abs(path[i][j] - path[i][j - 1]),
								dp[i][j - 1][10] + abs(path[i][j] - path[i][j - 1])
							)
						);
						if (dp[i][j][k] >= MAX) dp[i][j][k] = MAX;


					}
				}



			}
		}
	}



}




int main(int argc, char** argv)
{
	int T, test_case;


	cin >> T;
	for (test_case = 0; test_case < T; test_case++)
	{
		
		ini();
		solve();
		Answer = MAX;
		for (int i = K; i <= 10; i++) {
			Answer = min(Answer, dp[N][M][i]);
		}

		cout << "Case #" << test_case + 1 << endl;
		cout << Answer << endl;
	}

	return 0;//Your program should return 0 on normal termination.
}
