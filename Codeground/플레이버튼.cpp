

#include <iostream>
#include <string>

using namespace std;


int main(int argc, char** argv)
{
	int T, test_case;
	int N;
	string Answer;

	cin >> T;
	for (test_case = 0; test_case < T; test_case++)
	{
		Answer = "NONE";
		cin >> N;
		if (N >= 100000) Answer = "SILVER";
		if (N >= 1000000) Answer = "GOLD";
		if (N >= 10000000) Answer = "DIAMOND";


		cout << "Case #" << test_case + 1 << endl;
		cout << Answer << endl;
	}

	return 0;//Your program should return 0 on normal termination.
}
