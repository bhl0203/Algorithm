/*
You should use the statndard input/output

in order to receive a score properly.

Do not use file input and output

Please be very careful.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#define ll long long
using namespace std;

vector<ll> v;
vector<ll> d;

int Answer;
bool flag = false;

ll gcd(ll a, ll b) {
	ll c;
	while (b != 0) {
		c = a % b;
		a = b;
		b = c;
	}
	return a;
}

int main(int argc, char** argv)
{
	int T, test_case;
	int M;
	ll tmp;

	cin >> T;
	for (test_case = 0; test_case < T; test_case++)
	{
		Answer = 0;
		flag = false;
		cin >> M;
		v.resize(M);
		d.resize(M - 1);
		for (int i = 0; i < M; i++) {
			cin >> v[i];
			if (i) d[i - 1] = v[i] - v[i - 1];
		}
		sort(d.begin(), d.end());
		
		if (d[M - 2] == 0) {//제일 큰게 0이라면 가능한 공차는 0 하나
			Answer = 1;
		}
		else if (d[M-2] != 0 && d[0] == 0) {
			//0이 아닌 차이와 0이 동시에 존재하면 답은 없음
			Answer = 0;
		}
		else {
			if (M == 2) tmp = d[M - 2];
			else tmp = gcd(d[1], d[0]);
			for (int i = 1; i < M - 2; i++) {
				tmp = gcd(d[i + 1], tmp);
			}
			
			ll n = tmp;
			for (ll i = 1; i <= n/2; i++) {
				if (n % i == 0)		Answer++;
			}
			Answer++;
		}
		




		cout << "Case #" << test_case + 1 << endl;
		cout << Answer << endl;
	}

	return 0;//Your program should return 0 on normal termination.
}
