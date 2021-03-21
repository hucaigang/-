#include<iostream>
#include<vector>
#include<Windows.h>
using namespace std;

vector<string> cls = { "万","条","筒" }; vector<string> special = { "东","南","西","北","中","发","白" };
bool judge(vector<vector<int>> count, int k, int num) {//count:现在的牌 k:是否有头 num剩多少牌
	if (num == 0) return true;
	if (k == 0) {//没有头
		for (int j = 0; j < 4; j++) {
			for (int i = 1; i <= 9; i++) {
				if (count[j][i] < 2) continue;
				else {
					vector<vector<int>> tmp = count;
					tmp[j][i] -= 2;
					if (judge(tmp, 1, num - 2)) return true;
				}
			}
		}
	}
	else {//有头
		for (int j = 0; j < 4; j++) {
			for (int i = 1; i <= 9; i++) {//有没有刻子
				if (count[j][i] < 3) continue;
				else {
					vector<vector<int>> tmp = count;
					tmp[j][i] -= 3;
					if (judge(tmp, k, num - 3)) return true;
				}
			}
		}
		for (int j = 0; j < 3; j++) {
			for (int i = 1; i <= 7; i++) {//有没有顺子
				if (count[j][i] && count[j][i + 1] && count[j][i + 2]) {
					vector<vector<int>> tmp = count;
					tmp[j][i] -= 1; tmp[j][i + 1] -= 1; tmp[j][i + 2] -= 1;
					if (judge(tmp, k, num - 3)) return true;
				}
				else continue;
			}
		}
	}
	return false;
}

void husha() {
	system("cls");
	vector<vector<int>> majiang(4, vector<int>(10, 0));
	vector<vector<int>> win;
	for (int j = 0; j < cls.size(); j++) {
		cout << "输入你的" << cls[j] << "字(每i行代表你有几个i" << cls[j] << "牌)" << endl;
		for (int i = 1; i < 10; i++) {
			cout << "你有几个" << i << cls[j] << endl;
			cin >> majiang[j][i];
		}
	}
	for (int i = 0; i < special.size(); i++) {
		cout << "你有几个" << special[i] << endl;
		cin >> majiang[3][i + 1];
	}
	int num = 0;
	for (int i = 0; i < 4; i++) {
		for (int j = 1; j < 10; j++) {
			if (majiang[i][j] > 4) {
				cerr << "你个b就知道藏牌"<<endl;
				return;
			}
			else if (majiang[i][j] < 0) {
				cerr << "你就捣乱吧"<<endl;
				return;
			}
			num += majiang[i][j];
		}
	}
	if (num != 13) cout << "你相公了 自己下去吧" << endl;
	else {
		bool flag = false;
		for (int j = 0; j < 4; j++) {//补上一张牌看是否胡
			for (int i = 1; i <= 9; i++) {
				vector<vector<int>> temp = majiang;
				temp[j][i] ++;
				if (temp[j][i] > 4) continue; //没有那么多牌
				if (judge(temp, 0, 14)) {
					win.push_back({ j,i });
					flag = true;
				}
			}
		}

		if (win.size() != 0) cout << "你胡的牌有：";
		for (vector<int> wait : win) {
			if (wait[0] <= 2) cout << wait[1] << cls[wait[0]] << " ";
			else cout << special[wait[1]];
		}
		cout << endl;
		if (!flag) cout << "听牌你就恍胡 哈要听 听你妈" << endl;
	}
}


int main() {
	while (true) {
		husha();
		cout << "5秒后自动清除屏幕 进行下一次判断";
		Sleep(5000);
	}
	system("pause");
	return 0;
}