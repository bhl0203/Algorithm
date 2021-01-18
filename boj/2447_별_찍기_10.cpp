#include <stdio.h>
#include <string.h>
int n;
char mat[2200][2200];
void rec(int m, int x, int y) {
	if (m == 1) {
		mat[x][y] = '*';
		return;
	}
	int k = m / 3;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (i * j == 1) continue;
			rec(k,x+(k*i),y+(k*j));
		}
	}


}
int main() {
	scanf("%d",&n);
	memset(mat, ' ', sizeof(mat));

	rec(n, 0, 0);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			printf("%c",mat[i][j]);
		}
		printf("\n");
	}
	return 0;
}