#include <stdio.h>

int main() {
	//��ȸ - N�� M��
	//���Ͻ� K ��
	//�ʼ� - 2�� 1��
	int n, m, k;
	scanf("%d %d %d",&n,&m,&k);
	while (k--) {
		if (n >= 2 * m) n--;
		else m--;
	}
	if (n >= 2 * m) printf("%d",m);
	else printf("%d",n/2);
	return 0;
}