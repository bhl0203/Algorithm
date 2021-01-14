#include <stdio.h>
#include <iostream>
using namespace std;

int coin[21] = { 0, };
int res = 99999;
int n;

void calc(int x) {

	if (x == n) {
		int sum = 0;
		for (int i = 1; i <= (1 << (n - 1)); i *= 2) {
			int cnt = 0;
			for (int j = 0; j < n; j++) {
				if (coin[j] & i) cnt++;
			}
			cnt < n - cnt ? (sum += cnt) : (sum += (n - cnt));
		}
		if (res > sum)res = sum;
	}
	else {
		calc(x + 1);
		coin[x] = ~coin[x];
		calc(x + 1);
	}





}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	char c;
	cin >> n;
	for (int i = 0; i < n; i++) {
		int x = (1 << (n - 1));
		for (int j = 0; j < n; j++) {
			cin >> c;
			//0일때는 별다른 연산 필요 X
			if (c == 'T') {//1_Tail
				coin[i] += x;
			}
			x = x >> 1;
		}
	}
	calc(0);
	
	cout << res << '\n';

	return 0;
}