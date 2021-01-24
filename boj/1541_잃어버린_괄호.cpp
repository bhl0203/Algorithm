#include <cstdio>
#include <string>
#include <iostream>

using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	
	string str;
	cin >> str;
	int l = str.length();
	bool flag = false;
	int res = 0;
	int tmp = 0;
	for (int i = 0; i < l; i++) {
		if (str[i] >= '0' && str[i] <= '9') {
			tmp *= 10;
			tmp += (str[i] - '0');
		}
		if (str[i] == '+' || str[i] == '-') {
			if (!flag) {//앞에 - 가 없으면
				res += tmp;
				tmp = 0;
			}
			else if (flag) {//앞에 - 가 있으면
				res -= tmp;
				tmp = 0;
			}
			if (str[i] == '-') flag = true;
		}
	}
	if (!flag) {//앞에 - 가 없으면
		res += tmp;
		tmp = 0;
	}
	else if (flag) {//앞에 - 가 있으면
		res -= tmp;
		tmp = 0;
	}
	printf("%d\n",res);
	return 0;
}