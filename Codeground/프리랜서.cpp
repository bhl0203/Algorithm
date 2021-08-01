
#include <iostream>
#include <vector>


using namespace std;

int Answer;

vector<int> P;
vector<int> Q;
vector<int> d;

int main(int argc, char** argv)
{
	int T, test_case;
	int N;
	int cnt;

	cin >> T;
	for (test_case = 0; test_case < T; test_case++)
	{
		Answer = 0;
		cnt = 0;
		int N;
		cin >> N;
		P.resize(N);
		Q.resize(N);
		d.resize(N);

		for (int i = 0; i < N; i++) cin >> P[i];
		for (int i = 0; i < N; i++) cin >> Q[i];

		d[0] = max(P[0], Q[0]);
		if (N >= 2) {
			d[1] = max(d[0] + P[1], Q[1]);
		}
		if (N >= 3) {
			for (int i = 2; i < N; i++) {
				d[i] = max(d[i - 1] + P[i], d[i - 2] + Q[i]);
			}
		}
		



		cout << "Case #" << test_case + 1 << endl;
		cout << d[N-1] << endl;
	}

	return 0;//Your program should return 0 on normal termination.
}
