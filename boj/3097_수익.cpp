#include <stdio.h>
#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;

int arr[250001];
int dp[250001];

int max_profit;

int main() {

	int n;
	int k;
	while (1) {
		max_profit = -99999;
		cin >> n;
		if (n == 0) break;
		for (int i = 0; i < n; i++) {
			cin >> arr[i];
			dp[i] = arr[i];
		}
		
		for (int i = 1; i < n; i++) {
			if (dp[i] > dp[i - 1] + dp[i]) continue;
			else dp[i] = dp[i - 1] + dp[i];
		}
		for (int i = 0; i < n; i++) {
			if (dp[i] > max_profit) max_profit = dp[i];
		}
		cout << max_profit << endl;
	}
	


	return 0;
}