#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <algorithm>
#include <vector>
using namespace std;

int n;
int maxi = 0;

int tri[501][501] = { 0, };
int sum[501][501] = { 0, };

int main() {

	scanf("%d", &n);
	
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= i; j++) {
			scanf("%d",&tri[i][j]);

		}
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= i; j++) {
			sum[i][j] = max(tri[i][j] + sum[i - 1][j - 1], tri[i][j] + sum[i - 1][j]);
		}
	}
	for (int i = 1; i <= n; i++) {
		maxi = max(maxi, sum[n][i]);
	}
	printf("%d\n",maxi);

	return 0;
}