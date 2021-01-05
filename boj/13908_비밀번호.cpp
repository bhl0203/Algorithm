#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

int cnt = 0;
int n, m;
vector<int> code;
int flag = 0;
int tmpflag;

void dfs(int x,string str) {
	if (x == n) {//string�� ���̰� ��й�ȣ�� ���̿� ������ �˻�

		flag = 1;
		for (int i = 0; i < code.size(); i++) {//str�� ���̸�ŭ
			tmpflag = 0;
			for (int j = 0; j < str.size(); j++) {
				if (str[j] - '0' == code[i]) {//�����Ѱ� ������ ���
					tmpflag = 1;
					break;
				}
			}
			if (tmpflag == 0) {
				flag = 0;
				break;
			}
		}
		if (flag) {
			cnt++;
		}
		return;
	}
	for (int i = 0; i < 10; i++) {//string �߰�
		dfs(x + 1, str + (char)(i + '0'));
	}
}


int main() {

	scanf("%d %d", &n, &m);
	int t;

	for (int i = 0; i < m; i++) {
		scanf("%d",&t);
		code.push_back(t);
	}
	dfs(0, "");
	printf("%d\n",cnt);

	return 0;
}