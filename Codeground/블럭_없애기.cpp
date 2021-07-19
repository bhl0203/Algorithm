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

int Answer;

int main(int argc, char** argv)
{
	int T, test_case;
	int N;
	vector<int> h;
	vector<int> t_left;
	vector<int> t_right;
	vector<int> t;
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

		Answer = 0;
		cin >> N;
		h.resize(N + 2);
		t_left.resize(N + 2);
		t_right.resize(N + 2);
		t.resize(N+1);
		t_left[0] = 0;
		t_left[N + 1] = 0;
		t_right[0] = 0;
		t_right[N + 1] = 0;
		for (int i = 1; i <= N; i++) {
			cin >> h[i];
		}
		//from left to right
		for (int i = 1; i <= N; i++) {
			t_left[i] = min(h[i], t_left[i - 1] + 1);
		}
		//right to left
		for (int i = N; i >= 1; i--) {
			t_right[i] = min(h[i], t_right[i + 1] + 1);
		}

		for (int i = 1; i <= N; i++) {
			t[i] = min(t_right[i], t_left[i]);
		}
		for (int i = 1; i <= N; i++) {
			Answer = max(Answer, t[i]);
		}
		
		/////////////////////////////////////////////////////////////////////////////////////////////
		/*
		   Implement your algorithm here.
		   The answer to the case will be stored in variable Answer.
		 */
		 /////////////////////////////////////////////////////////////////////////////////////////////

		 // Print the answer to standard output(screen).
		cout << "Case #" << test_case + 1 << endl;
		cout << Answer << endl;
	}

	return 0;//Your program should return 0 on normal termination.
}
