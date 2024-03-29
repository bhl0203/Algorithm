/*
You should use the statndard input/output

in order to receive a score properly.

Do not use file input and output

Please be very careful.
*/

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <functional>

using namespace std;


int Answer;


int main(int argc, char** argv)
{
	int T, test_case;
	int N, M, K;
	int P;
	
	/*
	   The freopen function below opens input.txt file in read only mode, and afterward,
	   the program will read from input.txt file instead of standard(keyboard) input.
	   To test your program, you may save input data in input.txt file,
	   and use freopen function to read from the file when using cin function.
	   You may remove the comment symbols(//) in the below statement and use it.
	   Use #include<cstdio> or #include <stdio.h> to use the function in your program.
	   But before submission, you must remove the freopen function or rewrite comment symbols(//).
	 */

	 // freopen("input.txt", "r", stdin);

	cin >> T;
	int a, b, c;

	for (test_case = 0; test_case < T; test_case++)
	{
		vector<vector<int>> cost;
		cin >> N >> M >> K;
		Answer = 0;
		cost.resize(N + 1);

		for (int i = 1; i <= N; i++) {
			cost[i].resize(N + 1,99999999);
			cost[i][i] = 0;
		}
		for (int i = 1; i <= M; i++) {
			cin >> a >> b >> c;
			cost[a][b] = c;
			cost[b][a] = c;
		}

		for (int k = 1; k <= N; k++) {
			for (int i = 1; i <= N; i++) {
				for (int j = 1; j <= N; j++) {
					if (cost[i][k] + cost[k][j] < cost[i][j]) cost[i][j] = cost[i][k] + cost[k][j];
				}
			}
		}
		cin >> P;
		for (int i = 0; i < P; i++) {
			cin >> a >> b;
			if (cost[a][b] > K) Answer++;
		}

		cout << "Case #" << test_case + 1 << endl;
		cout << Answer << endl;
	}

	return 0;//Your program should return 0 on normal termination.
}
