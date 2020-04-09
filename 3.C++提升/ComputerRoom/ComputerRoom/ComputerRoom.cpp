#include<iostream>
using namespace std;
#include<fstream>
#include "student.h"
#include "teacher.h"
#include "manager.h"

// 创建管理员菜单
void managerMenu(Identity * &manager) {
	while (1) {
		// 管理菜单
		manager->openMenu();

		Manager * man = (Manager*)manager;
		int select = 0;
		cin >> select;
		if (select == 1) // 添加账号
		{
			cout << "添加账号" << endl;
			man->addPerson();
		}
		else if (select == 2) // 查看账号
		{
			cout << "查看账号" << endl;
			man->showPerson();
		}
		else if (select == 3) // 查看机房
		{
			cout << "查看机房" << endl;
			man->showComputer();
		}
		else if (select == 4) // 清空预约
		{
			cout << "清空预约" << endl;
			man->cleanFile();
		}
		else {
			delete manager;
			cout << "注销成功" << endl;
			system("pause");
			system("cls");
			return;
		}

	}
}

// 创建学生菜单
void studentMenu(Identity * &student) {
	while (1) {
		// 管理菜单
		student->openMenu();

		Student * stu = (Student*)student;
		int select = 0;
		cin >> select;
		if (select == 1) // 申请预约
		{
			cout << "申请预约" << endl;
			stu->applyOrder();
		}
		else if (select == 2) // 查看自身预约
		{
			cout << "查看自身预约" << endl;
			stu->showMyOrder();
		}
		else if (select == 3) // 查看所有预约
		{
			cout << "查看所有预约" << endl;
			stu->showAllOrder();
		}
		else if (select == 4) // 取消预约
		{
			cout << "取消预约" << endl;
			stu->cancelOrder();
		}
		else {
			delete student;
			cout << "注销成功" << endl;
			system("pause");
			system("cls");
			return;
		}

	}
}

// 创建教师菜单
void TeacherMenu(Identity * &teacher) {
	while (1) {
		// 管理菜单
		teacher->openMenu();

		Teacher * tea = (Teacher*)teacher;
		int select = 0;
		cin >> select;
		if (select == 1) // 查看所有预约
		{
			cout << "查看所有预约" << endl;
			tea->showAllOrder();
		}
		else if (select == 2) // 审核预约
		{
			cout << "审核预约" << endl;
			tea->validOrder();
		}
		
		else {
			delete teacher;
			cout << "注销成功" << endl;
			system("pause");
			system("cls");
			return;
		}

	}
}

// 登陆功能
void LoginIn(string fileName, int type) {
	Identity * person = NULL;

	// 读文件
	ifstream ifs(fileName);
	// 判断文件是否存在
	if (!ifs.is_open()) {
		cout << "文件不存在" << endl;
		ifs.close();
		return;
	}
	// 准备用户接受信息
	int id = 0;
	string name;
	string pwd;

	// 判断身份
	if (type == 1) {
		cout << "请输入你的学号：" << endl;
		cin >> id;
	}
	else if (type == 2) {
		cout << "请输入你的职工号：" << endl;
		cin >> id;
	}
	cout << "请输入用户名：" << endl;
	cin >> name;
	cout << "请输入密码：" << endl;
	cin >> pwd;

	if (type == 1) {
		int fId;
		string fName;
		string fPwd;
		while (ifs >> fId && ifs >> fName && ifs >> fPwd) {
			// 与用户输入信息对比
			if (fId == id && fName == name && fPwd == pwd) {
				cout << "学生验证登陆成功！" << endl;
				system("pause");
				system("cls");
				person = new Student(id, name, pwd);
				// 进入学生身份子菜单
				studentMenu(person);
				return;
			}
		}
	}
	else if (type == 2) {
		int fId;
		string fName;
		string fPwd;
		while (ifs >> fId && ifs >> fName && ifs >> fPwd) {
			// 与用户输入信息对比
			if (fId == id && fName == name && fPwd == pwd) {
				cout << "教师验证登陆成功！" << endl;
				system("pause");
				system("cls");
				person = new Teacher(id, name, pwd);
				// 进入教师身份子菜单
				TeacherMenu(person);
				return;
			}
		}
	}
	else if (type == 3) {
		string fName;
		string fPwd;
		while (ifs >> fName && ifs >> fPwd) {
			// 与用户输入信息对比
			if (fName == name && fPwd == pwd) {
				cout << "管理员验证登陆成功！" << endl;
				system("pause");
				system("cls");
				person = new Manager(name, pwd);
				// 进入管理员身份子菜单
				managerMenu(person);
				return;
			}
		}

	}
	cout << "验证登陆失败！" << endl;
	system("pause");
	system("cls");
	return;
}



int main() {

	int select;
	while (1) {
		cout << "===================== 欢迎来到机房预约系统 =====================" << endl;
		cout << endl << "请输入你的身份" << endl;
		cout << "\t\t  ------------------------------\n";
		cout << "\t\t|                               |\n";
		cout << "\t\t|         1.学生代表            |\n";
		cout << "\t\t|                               |\n";
		cout << "\t\t|         2.老    师            |\n";
		cout << "\t\t|                               |\n";
		cout << "\t\t|         3.管 理 员            |\n";
		cout << "\t\t|                               |\n";
		cout << "\t\t|         0.退    出            |\n";
		cout << "\t\t|                               |\n";
		cout << "\t\t  ------------------------------\n";
		cout << "请输入您的选择：" << endl;
		cin >> select;
		switch (select)
		{
		case 1: // 学生身份
			LoginIn(STUDENT_FILE, 1);
			break;
		case 2: // 老师身份
			LoginIn(TEACHER_FILE, 2);
			break;
		case 3: // 管理员身份
			LoginIn(ADMIN_FILE, 3);
			break;
		case 0: // 退出系统
			cout << "欢迎下次使用" << endl;
			system("pause");
			return 0;
			break;
		default:
			cout << "输出有误，请重新选择！" << endl;
			system("pause");
			system("cls");
			break;
		}
	}
	
	system("pause");
	return 0;
}