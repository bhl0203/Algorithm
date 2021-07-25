
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

int Answer;
int N, M, K;

vector<int> c;
vector<int> p;

int main(int argc, char** argv)
{
	int T, test_case;
	char res;

	cin >> T;
	for (test_case = 0; test_case < T; test_case++)
	{
		Answer = 0;
		cin >> N >> M >> K;


		c.resize(N);
		p.resize(M+1);
		for (int i = 0; i < N; i++) cin >> c[i];
		for (int i = 1; i <= M; i++) cin >> p[i];

		for (int i = 0; i < N; i++) {
			Answer += p[c[i]];
		}
		if (Answer > K) res = 'N';
		else res = 'Y';


		cout << "Case #" << test_case + 1 << endl;
		cout << res << endl;
	}

	return 0;//Your program should return 0 on normal termination.
}
