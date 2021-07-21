/*
You should use the statndard input/output

in order to receive a score properly.

Do not use file input and output

Please be very careful.
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define ll long long

int Answer;


int main(int argc, char** argv)
{
	int T, test_case;
	int l = 0;
	int r = 0;
	int N,S;
	vector<ll> v;
	int sum = 0;
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
	for (test_case = 0; test_case < T; test_case++)
	{
		sum = 0;
		Answer = 1000000009;
		l = 0;
		r = 0;
		cin >> N >> S;
		/////////////////////////////////////////////////////////////////////////////////////////////
		/*
		   Implement your algorithm here.
		   The answer to the case will be stored in variable Answer.
		 */
		 /////////////////////////////////////////////////////////////////////////////////////////////

		v.resize(N);
		for (int i = 0; i < N; i++) {
			cin >> v[i];
		}
		while (r <= N && l <= r) {

			if (sum >= S) {
				if (Answer > (r - l)) {
					Answer = r - l;
					if (Answer == 1) break;
				}
				sum -= v[l++];
				continue;
			}
			else {
				if (r >= N) break;
				sum += v[r++];
			}
		}
		if (Answer == 1000000009) Answer = 0;

		 // Print the answer to standard output(screen).
		cout << "#testcase" << test_case + 1 << '\n';
		cout << Answer << '\n';
	}

	return 0;//Your program should return 0 on normal termination.
}
