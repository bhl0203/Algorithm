
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> cnt(4);

int Answer;

int main(int argc, char** argv)
{
	int T, test_case;

	cin >> T;
	string str;
	for (test_case = 0; test_case < T; test_case++)
	{

		Answer = 0;
		cin >> str;
		
		for (int i = 0; i < 4; i++) cnt[i] = 0;
		for (int i = 0; i < str.length(); i++) {
			if (str[i] == 'h') cnt[0]++;
			else if (str[i] == 'e') cnt[1]++;
			else if (str[i] == 'l') cnt[2]++;
			else if (str[i] == 'o') cnt[3]++;
		}
		Answer =
			min(
				cnt[0], min(
					cnt[1], min(
						cnt[2] / 2, cnt[3]
					)
				)
			);
			
		cout << "Case #" << test_case + 1 << endl;
		cout << Answer << endl;
	}

	return 0;//Your program should return 0 on normal termination.
}
