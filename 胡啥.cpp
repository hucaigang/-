#include<iostream>
#include<vector>
#include<Windows.h>
using namespace std;

vector<string> cls = { "��","��","Ͳ" }; vector<string> special = { "��","��","��","��","��","��","��" };
bool judge(vector<vector<int>> count, int k, int num) {//count:���ڵ��� k:�Ƿ���ͷ numʣ������
	if (num == 0) return true;
	if (k == 0) {//û��ͷ
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
	else {//��ͷ
		for (int j = 0; j < 4; j++) {
			for (int i = 1; i <= 9; i++) {//��û�п���
				if (count[j][i] < 3) continue;
				else {
					vector<vector<int>> tmp = count;
					tmp[j][i] -= 3;
					if (judge(tmp, k, num - 3)) return true;
				}
			}
		}
		for (int j = 0; j < 3; j++) {
			for (int i = 1; i <= 7; i++) {//��û��˳��
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
		cout << "�������" << cls[j] << "��(ÿi�д������м���i" << cls[j] << "��)" << endl;
		for (int i = 1; i < 10; i++) {
			cout << "���м���" << i << cls[j] << endl;
			cin >> majiang[j][i];
		}
	}
	for (int i = 0; i < special.size(); i++) {
		cout << "���м���" << special[i] << endl;
		cin >> majiang[3][i + 1];
	}
	int num = 0;
	for (int i = 0; i < 4; i++) {
		for (int j = 1; j < 10; j++) {
			if (majiang[i][j] > 4) {
				cerr << "���b��֪������"<<endl;
				return;
			}
			else if (majiang[i][j] < 0) {
				cerr << "��͵��Ұ�"<<endl;
				return;
			}
			num += majiang[i][j];
		}
	}
	if (num != 13) cout << "���๫�� �Լ���ȥ��" << endl;
	else {
		bool flag = false;
		for (int j = 0; j < 4; j++) {//����һ���ƿ��Ƿ��
			for (int i = 1; i <= 9; i++) {
				vector<vector<int>> temp = majiang;
				temp[j][i] ++;
				if (temp[j][i] > 4) continue; //û����ô����
				if (judge(temp, 0, 14)) {
					win.push_back({ j,i });
					flag = true;
				}
			}
		}

		if (win.size() != 0) cout << "��������У�";
		for (vector<int> wait : win) {
			if (wait[0] <= 2) cout << wait[1] << cls[wait[0]] << " ";
			else cout << special[wait[1]];
		}
		cout << endl;
		if (!flag) cout << "������ͻк� ��Ҫ�� ������" << endl;
	}
}


int main() {
	while (true) {
		husha();
		cout << "5����Զ������Ļ ������һ���ж�";
		Sleep(5000);
	}
	system("pause");
	return 0;
}