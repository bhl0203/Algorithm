#include <stdio.h>
int main() {
	int c;//number of test case
	scanf("%d",&c);
	int n;//number of students
	double arr[1001];
	double avg = 0;
	double cnt;
	for (int i = 0; i < c ; i++) {
		avg = 0;//reset average
		cnt = 0;//reset student count
		scanf("%d",&n);
		for (int j = 0; j < n; j++) {
			scanf("%lf",&arr[j]);
			avg += arr[j];
		}
		avg = avg / n;
		for (int j = 0; j < n; j++) {
			if (arr[j] > avg) cnt++;
		}
		printf("%.3lf%%\n",100*(cnt/n));
	}
	return 0;
}