/*
You should use the statndard input/output

in order to receive a score properly.

Do not use file input and output

Please be very careful.
*/

#include <iostream>
#include <vector>

using namespace std;

int Answer;
vector<int> arr;
int main(int argc, char** argv)
{
	int T, test_case;
	int N, K;
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
	int a, b;
	int tmp;
	bool pflag = true;
	int pfrog, lim;
	for (test_case = 0; test_case < T; test_case++)
	{
		a = 0;
		Answer = 1;
		cin >> N;
		arr.resize(N, 0);
		pflag = true;
		for (int i = 0; i < N; i++) {
			cin >> arr[i];
		}
		cin >> K;
		for (int i = 0; i < N - 1; i++) {
			if (arr[i + 1] - arr[i] > K) {
				Answer = -1;
				pflag = false;
				break;
			}
		}
		if (pflag) {
			pfrog = 0;
			lim = K;
			for (int i = 0; i < N; i++) {
				if (arr[i] <= lim) {
					pfrog = i;
				}
				else {
					lim = arr[pfrog] + K;
					Answer++;
					pfrog = i;
				}
			}
		}
		/////////////////////////////////////////////////////////////////////////////////////////

		 // Print the answer to standard output(screen).
		cout << "Case #" << test_case + 1 << endl;
		cout << Answer << endl;
	}

	return 0;//Your program should return 0 on normal termination.
}
