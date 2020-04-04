# include <iostream>
using namespace std;
# include <string>
# define MAX 1000

//设计联系人结构体
struct Person {
	string m_Name;
	int m_Sex;
	int m_Age;
	string m_Phone;
	string m_Addr;
};

//通讯录结构体
struct  Addressbooks{
	Person personArray[MAX];

	// 通讯录当前人个数
	int m_Size;

};

//添加联系人
void addPerson(Addressbooks * abs) {
	if (abs->m_Size == MAX) {
		cout << "通讯录已满，无法添加！" << endl;
		return;
	}
	else {
		// 添加联系人

		// 添加姓名
		string name;
		cout << "请输入姓名: " << endl;
		cin >> name;
		abs->personArray[abs->m_Size].m_Name = name;

		cout << "请输入性别： " << endl;
		cout << "1---男" << endl;
		cout << "2---女" << endl;

		// 添加性别
		int sex = 0;
		while (1) {
			cin >> sex;
			if (sex == 1 || sex == 2) {
				abs->personArray[abs->m_Size].m_Sex = sex;
				break;
			}
			cout << "输入有误，重新输入" << endl;

		}

		//添加年龄
		cout << "请输入年龄" << endl;
		int age;
		cin >> age;
		abs->personArray[abs->m_Size].m_Age = age;

		//添加电话
		cout << "请输入联系电话: " << endl;
		string phone;
		cin >> phone;
		abs->personArray[abs->m_Size].m_Phone = phone;

		//添加住址
		cout << "请输入家庭住址: " << endl;
		string address;
		cin >> address;
		abs->personArray[abs->m_Size].m_Addr = address;

		//更新通讯录人数
		abs->m_Size++;
		cout << "添加成功" << endl;

		system("pause");
		system("cls"); // 清屏
	
	}
}

// 显示联系人
void showPerson(Addressbooks * abs) {
	if (abs->m_Size == 0) {
		cout << "当前记录为空" << endl;
	}
	else {
		for (int i = 0; i < abs->m_Size; i++) {
			cout << "姓名： " << abs->personArray[i].m_Name << "\t";
			cout << "性别： " << (abs->personArray[i].m_Sex == 1 ? "男" : "女") << "\t";
			cout << "年龄： " << abs->personArray[i].m_Age << "\t";
			cout << "电话： " << abs->personArray[i].m_Phone << "\t";
			cout << "住址： " << abs->personArray[i].m_Addr << endl;
		}
	}
	system("pause");
	system("cls"); // 清屏
}

// 检测联系人是否存在，如果存在返回下标，否则返回-1
int isExist(Addressbooks * abs, string name) {
	for (int i = 0; i < abs->m_Size; i++) {
		if (abs->personArray[i].m_Name == name) {
			return i;
		}
	}
	return -1;
}



// 删除指定联系人
void deletePerson(Addressbooks * abs) {
	cout << "请输入您要删除联系人" << endl;
	string name;
	cin >> name;
	int ret = isExist(abs, name);
	if (ret != -1) {
		for (int i = ret; i < abs->m_Size-1; i++) {
			abs->personArray[i] = abs->personArray[i + 1];
		}
		abs->m_Size--;
		cout << "删除成功" << endl;
	}
	else {
		cout << "查无此人" << endl;
	}
	system("pause");
	system("cls"); // 清屏
}

//查找联系人
void findPerson(Addressbooks * abs) {
	cout << "请输入您要查找联系人" << endl;
	string name;
	cin >> name;
	int ret = isExist(abs, name);

	if (ret != -1) {
		cout << "姓名： " << abs->personArray[ret].m_Name << "\t";
		cout << "性别： " << (abs->personArray[ret].m_Sex == 1 ? "男" : "女") << "\t";
		cout << "年龄： " << abs->personArray[ret].m_Age << "\t";
		cout << "电话： " << abs->personArray[ret].m_Phone << "\t";
		cout << "住址： " << abs->personArray[ret].m_Addr << endl;
	}
	else {
		cout << "查无此人" << endl;
	}
	system("pause");
	system("cls"); // 清屏
}


// 修改联系人
void modifyPerson(Addressbooks * abs) {
	cout << "请输入要修改联系人" << endl;
	string name;
	cin >> name;
	int ret = isExist(abs, name);
	if (ret != -1) {
		// 添加姓名
		string name;
		cout << "请输入姓名: " << endl;
		cin >> name;
		abs->personArray[ret].m_Name = name;

		cout << "请输入性别： " << endl;
		cout << "1---男" << endl;
		cout << "2---女" << endl;

		// 添加性别
		int sex = 0;
		while (1) {
			cin >> sex;
			if (sex == 1 || sex == 2) {
				abs->personArray[ret].m_Sex = sex;
				break;
			}
			cout << "输入有误，重新输入" << endl;

		}

		//添加年龄
		cout << "请输入年龄" << endl;
		int age;
		cin >> age;
		abs->personArray[ret].m_Age = age;

		//添加电话
		cout << "请输入联系电话: " << endl;
		string phone;
		cin >> phone;
		abs->personArray[ret].m_Phone = phone;

		//添加住址
		cout << "请输入家庭住址: " << endl;
		string address;
		cin >> address;
		abs->personArray[ret].m_Addr = address;
	}
	else {
		cout << "查无此人" << endl;
	}
	system("pause");
	system("cls"); // 清屏
}

// 清空联系人
void cleanPerson(Addressbooks * abs) {
	abs->m_Size = 0;
	cout << "通讯录已清空" << endl;
	system("pause");
	system("cls"); // 清屏

}

// 菜单界面
void showMenu() {
	cout << "**************************" << endl;
	cout << "*****  1.添加联系人  *****" << endl;
	cout << "*****  2.显示联系人  *****" << endl;
	cout << "*****  3.删除联系人  *****" << endl;
	cout << "*****  4.查找联系人  *****" << endl;
	cout << "*****  5.修改联系人  *****" << endl;
	cout << "*****  6.清空联系人  *****" << endl;
	cout << "*****  0.退出通讯录  *****" << endl;
	cout << "**************************" << endl;
}

int main() {

	// 创建通讯录结构体变量
	Addressbooks abs;
	abs.m_Size = 0;


	int select = 0; //用户选择输入变量
	while (1) {
		showMenu();

		cin >> select;

		switch (select) {
		case 1:
			addPerson(&abs); //地址传递
			break;
		case 2:
			showPerson(&abs);
			break;
		case 3:
			deletePerson(&abs);
			break;
		case 4:
			findPerson(&abs);
			break;
		case 5:
			modifyPerson(&abs);
			break;
		case 6:
			cleanPerson(&abs);
			break;
		case 0:
			cout << "欢迎下次使用" << endl;
			system("pause");
			return 0;
			break;
		default:
			break;
		}
	}
	
	
	system("pause");
	return 0;
}