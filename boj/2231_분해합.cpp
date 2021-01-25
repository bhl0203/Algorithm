#include <stdio.h>
int arr[1000001] = { 0, };
int main(){
	int n;
	scanf("%d",&n);
	for (int i = 0; i < n; i++) {
		int tmp = i;
		int m = tmp;
		while (tmp) {
			m += (tmp%10);
			tmp /= 10;
		}//i는 생성자, m이 분해합
		arr[i] = m;
	}
	for (int i = 0; i < n; i++) {
		if (arr[i] == n) {
			printf("%d\n", i);
			return 0;
		}
	}
	printf("0\n");



	return 0;
}