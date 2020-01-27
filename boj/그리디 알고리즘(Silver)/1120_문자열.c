#include <stdio.h>
#include <string.h>

int main() {
	char A[51];
	char B[51];
	scanf("%s", A);
	scanf("%s", B);
	int la = strlen(A);
	int lb = strlen(B);//la<lb
	int cnt = 0;
	int small = 51;
	for (int i = 0; i <= (lb-la); i++) {
		cnt = 0;
		for (int j = 0; j < la; j++) {
			if (A[j] != B[i+j]) cnt++;
		}
		if (cnt < small) small = cnt;
	}
	printf("%d\n",small);
	return 0;
}