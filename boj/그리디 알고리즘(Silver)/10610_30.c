#include <stdio.h>
#include <string.h>

int main() {
	char n[100001];
	int res[10] = { 0, };
	scanf("%s",n);
	int sum = 0;
	int flag = 0;
	int l = strlen(n);
	for (int i = 0; i < l; i++) {
		res[n[i]-'0']++;
		sum += (n[i]-'0');
		if (n[i] == '0') flag = 1;
	}
	if (flag == 0) {
		printf("-1");
		return 0;
	}
	if (sum % 3 != 0) {
		printf("-1");
		return 0;
	}
	for (int i = 9; i >= 0; i--) {
		while (res[i]--) {
			printf("%d",i);
		}
	}
	return 0;
}