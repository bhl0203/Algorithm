#include <stdio.h>
int main() {
	int score[5];
	for (int i = 0; i < 5;i++) {
		scanf("%d",&score[i]);
	}
	for (int i = 0; i < 5; i++)
		if (score[i] < 40)
			score[i] = 40;
	int sum = 0;
	for (int i = 0; i < 5; i++)
		sum += score[i];
	printf("%d",sum/5);

	return 0;
}