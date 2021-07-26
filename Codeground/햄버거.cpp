
#include <iostream>
#include <algorithm>

using namespace std;

int Answer;

int main(int argc, char** argv)
{
	int T, test_case;
	int a, b, c;
	cin >> T;
	for (test_case = 0; test_case < T; test_case++)
	{
		cin >> a >> b >> c;


		Answer = min(a/2,min(b,c/3));




		cout << "Case #" << test_case + 1 << endl;
		cout << Answer << endl;
	}

	return 0;//Your program should return 0 on normal termination.
}
