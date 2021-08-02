

#include <iostream>
#include <vector>


using namespace std;
#define ll long long
int Answer;

int main(int argc, char** argv)
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int sell = 1000000001;
	int purchase = 1000000001;
	int before;
	int own = -1;
	int T, test_case;
	int N;
	cin >> T;
	int v;
	for (test_case = 0; test_case < T; test_case++)
	{

		Answer = 0;
		sell = 1000000001;
		purchase = 1000000001;
		//before = 1000000001;
		own = -1;//소유하면1, 없으면 -1
		cin >> N;
		for (int i = 0; i < N; i++) {
			cin >> v;
			if (own == 1) {//갖고 있는 주식이 있을때
				if (v <= purchase) {//내가 갖고 있는 주식이 있는데,
									//오늘ㅢ 주가가 내 최근 구매가보다 낮으면
					purchase = v;//오늘 산거라고 치자
					continue;
				}
				if (v > purchase) {//내가 갖고 있는 주식이 있는데, 
									//현재 주가가 내 최근 구매가보다 높으면 팔아야지
					sell = v;//최근 판매가를 v로 갱신
					own = -1;
				}
			}
			else {//갖고 있는 주식이 없을때
				if (v >= sell) {//내가 갖고 있는 주식이 없는데,
								//오늘의 주가가 내 최근 판매액보다 높으면
								//사실 오늘 판거임 (더 큰 이득)
					sell = v;
					continue;
				}
				if (v < sell) {//내가 갖고 있는 주식이 없는데,
								//최근 판매액보다 주가가 낮으면 사야지
					own = 1;
					purchase = v;//최근 구매가를 v로 갱신

				}

			}

			Answer++;
		}

		if (Answer % 2 == 1) Answer--;
		cout << "Case #" << test_case + 1 << '\n';
		cout << Answer << '\n';
	}

	return 0;
}
