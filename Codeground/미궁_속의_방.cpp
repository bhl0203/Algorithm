/*
You should use the statndard input/output

in order to receive a score properly.

Do not use file input and output

Please be very careful.
*/

#include <iostream>
#include <string>

using namespace std;

#define ll long long

ll Answer;

ll cal(int x, int y, int n) {
	int t = x + y;
	if (t <= n + 1) {
		if (t % 2) return (x + y - 1) * (x + y - 2) / 2 + y;
		else return (x + y - 1) * (x + y - 2) / 2 + x;
	}
	else return n * n + 1 - cal(n + 1 - x, n + 1 - y, n);
}


int main(int argc, char** argv)
{
	int T, test_case;
	/*
	   The freopen function below opens input.txt file s read only mode, and afterward,
	   the program will read from input.txt file instead of standard(keyboard) input.
	   To test your program, you may save input data in input.txt file,
	   and use freopen function to read from the file when using cin function.
	   You may remove the comment symbols(//) in the below statement and use it.
	   Use #include<cstdio> or #include <stdio.h> to use the function in your program.
	   But before submission, you must remove the freopen function or rewrite comment symbols(//).
	 */

	 // freopen("input.txt", "r", stdin);
	int N, K;
	cin >> T;
	string s;
	int x, y;
	for (test_case = 0; test_case < T; test_case++)
	{
		Answer = 1;
		x = 1; y = 1;
		cin >> N >> K;
		cin >> s;
		for (int i = 0; i < K; i++) {
			switch(s[i]){
			case 'U':
				y--;
				break;
			case 'D':
				y++;
				break;
			case 'R':
				x++;
				break;
			case 'L':
				x--;
				break;
			}
			Answer += cal(x, y, N);
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
