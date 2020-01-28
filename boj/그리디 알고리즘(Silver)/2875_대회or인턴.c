#include <stdio.h>

int main() {
	//대회 - N여 M남
	//인턴쉽 K 명
	//필수 - 2여 1남
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