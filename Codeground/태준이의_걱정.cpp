/*
You should use the statndard input/output

in order to receive a score properly.

Do not use file input and output

Please be very careful.
*/

#include <iostream>

using namespace std;

int Answer;

int main(int argc, char** argv)
{
	int T, test_case;
	
	cin >> T;
	int A, B, D;
	int l = 0;
	for (test_case = 0; test_case < T; test_case++)
	{
		cin >> A >> B >> D;
		Answer = 0;
		/////////////////////////////////////////////////////////////////////////////////////////////
		/*
		   Implement your algorithm here.
		   The answer to the case will be stored in variable Answer.
		 */
		 /////////////////////////////////////////////////////////////////////////////////////////////
		int tmp = A - B;
		if ((D - A) % (A - B) != 0) Answer = (D - A) / (A - B) + 2;
		else Answer = (D - A) / (A - B) + 1;

		 // Print the answer to standard output(screen).
		cout << "Case #" << test_case + 1 << endl;
		cout << Answer << endl;
	}

	return 0;//Your program should return 0 on normal termination.
}
