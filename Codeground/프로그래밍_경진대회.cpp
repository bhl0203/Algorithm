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
bool answer_flag = true;
vector<ll> arr;
vector<ll> comp;
int main(int argc, char** argv)
{
	int T, test_case;
	int N;
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

		Answer = 1;//기본적으로 1명은 존재
		answer_flag = true;
		cin >> N;
		arr.resize(N, 0);
		for (int i = 0; i < N; i++) {
			cin >> arr[i];
		}

		if (N == 1) {

			cout << "Case #" << test_case + 1 << endl;
			cout << Answer << endl;
		}
		else if (N == 2) {

			sort(arr.begin(), arr.end());
			if (arr[0] + 2 >= arr[1] + 1) Answer++;

			cout << "Case #" << test_case + 1 << endl;
			cout << Answer << endl;

		}
		else {

			sort(arr.begin(), arr.end());
			comp = arr;

			comp[N - 1] += 1;
			for (int i = N - 2; i >= 0; i--) {
				if (comp[i] + N >= comp[i + 1]) {
					Answer++;
				}
				if (comp[i] + N - i >= comp[i + 1]) {
					comp[i] += N - i;
				}
				else comp[i] = comp[i + 1];
			}

			/*
			for (int i = N - 2; i >= 0; i--) {
				for (int j = i + 1; j < N; j++) {
					if (arr[i] + N < comp[j]) {
						answer_flag = false;
						break;
					}
				}
				if (!answer_flag) break;
				Answer++;
			}
			*/


			// Print the answer to standard output(screen).
			cout << "Case #" << test_case + 1 << endl;
			cout << Answer << endl;
		}
	}

	return 0;//Your program should return 0 on normal termination.
}
