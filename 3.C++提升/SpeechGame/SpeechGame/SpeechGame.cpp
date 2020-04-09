# include<iostream>
# include"speechManager.h"
using namespace std;
# include <string>

int main() {
	// 创建管理类
	SpeechManager sm;

	int choice = 0;
	while (1) {
		
		sm.showMenu();
		cout << "请输入您的选择" << endl;
		cin >> choice;
		switch (choice)
		{
		case 1: //开始比赛
			sm.startSpeech();
			break;
		case 2: //查看往届记录
			sm.showRecord();
			break;
		case 3: // 清空记录
			sm.clearRecord();
			break;
		case 0: // 退出系统
			sm.exitSystem();
			break;
		default:
			system("cls");
			break;
		}
	}
	system("pause");
	return 0;
}