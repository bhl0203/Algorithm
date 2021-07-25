

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

vector<int> from;
vector<int> to;
vector<int> admin;

int Answer;

int main(int argc, char** argv)
{
	int T, test_case;
	int a, b;

	int N, M;

	cin >> T;
	for (test_case = 0; test_case < T; test_case++)
	{

		Answer = 1;

		cin >> N >> M;

		admin.resize(N+1);
		for (int i = 1; i <= N; i++) {
			admin[i] = 0;
		}
		from.resize(M);
		to.resize(M);


		for (int i = 0; i < M; i++) {
			cin >> from[i] >> to[i];
			admin[to[i]] = 1 - admin[from[i]];
		}
		for (int i = 0; i < M; i++) {
			if (admin[from[i]] == admin[to[i]]) {
				Answer = 0;
				break;
			}
		}



		cout << "Case #" << test_case + 1 << endl;
		cout << Answer << endl;
	}

	return 0;//Your program should return 0 on normal termination.
}
