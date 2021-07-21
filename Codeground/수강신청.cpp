/*
You should use the statndard input/output

in order to receive a score properly.

Do not use file input and output

Please be very careful.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

int Answer;

int main(int argc, char** argv)
{
	int T, test_case;

	int l, r;
	cin >> T;
	int N, M;
	vector<int> v;
	int sum;
	for (test_case = 0; test_case < T; test_case++)
	{
		cin >> N >> M;
		Answer = 0;
		sum = 0;
		v.resize(N);
		for (int i = 0; i < N; i++) {
			cin >> v[i];
		}

		sort(v.begin(), v.end(), greater<>());

		for (int i = 0; i < N; i++) {
			sum = v[i];
			if (sum <= M && sum > Answer) Answer = sum;
			for (int j = N - 1; j > i; j--) {
				if (sum + v[j] > M) break;
				sum += v[j];
				if (sum > Answer) {
					Answer = sum;
				}
				
			}

		}


		cout << "Case #" << test_case + 1 << endl;
		cout << Answer << endl;
	}

	return 0;//Your program should return 0 on normal termination.
}
