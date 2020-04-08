#include "workerManager.h"
using namespace std;
#include"worker.h"
#include"boss.h"
#include"employee.h"
#include"manager.h"
#include <sstream>
#include <string>
#include<vector>


WorkerManager::WorkerManager() {

	// 文件不存在或文件为空
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	this->m_FileIsEmpty = true;
	if (ifs.is_open()) {
		char ch;
		ifs >> ch;
		if (!ifs.eof()) {
			this->m_FileIsEmpty = false;
			ifs.close();
		}
	}
	if (this->m_FileIsEmpty){
		if (!ifs.is_open())
			cout << "文件不存在" << endl;
		else
			cout << "文件为空" << endl;
	
		this->m_EmpNum = 0;
		this->m_EmpArray = NULL;
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}
	else {
		int num = this->get_EmpNum();
		cout << "职工人数为： " << num << endl;
		this->m_EmpNum = num;

		// 开辟空间存入数组
		this->m_EmpArray = new Worker*[this->m_EmpNum];
		this->init_Emp();
	}
	
}

// 显示菜单
void WorkerManager::Show_Menu() {
	cout << "********************************************" << endl;
	cout << "*********  欢迎使用职工管理系统！  *********" << endl;
	cout << "*************  0.退出管理程序  *************" << endl;
	cout << "*************  1.增加职工信息  *************" << endl;
	cout << "*************  2.显示职工信息  *************" << endl;
	cout << "*************  3.删除离职信息  *************" << endl;
	cout << "*************  4.修改职工信息  *************" << endl;
	cout << "*************  5.查找职工信息  *************" << endl;
	cout << "*************  6.按照编号排序  *************" << endl;
	cout << "*************  7.清空所有文档  *************" << endl;
	cout << "********************************************" << endl << endl;
}

//退出系统
void WorkerManager::ExitSystem() {
	cout << "欢迎下次使用" << endl;
	system("pause");
	exit(0);
}

// 添加职工
void WorkerManager::Add_Emp() {
	cout << "请输入添加职工数量" << endl;
	int addNum = 0;
	cin >> addNum;
	if (addNum > 0) {
		int newSize = this->m_EmpNum + addNum;
		
		//开辟新空间
		Worker ** newSpace = new Worker*[newSize];

		// 将原来数据拷贝到新空间
		if (this->m_EmpArray != NULL) {
			for (int i = 0; i < this->m_EmpNum; i++) {
				newSpace[i] = this->m_EmpArray[i];
			}
		}

		// 添加新数据
		for (int i = 0; i < addNum; i++) {
			int id;
			string name;
			int dSelect;
			cout << "请输入第 " << i + 1 << " 个新职工编号： " << endl;
			while (1) {
				cin >> id;
				if (this->IsExist(id) == -1)
					break;
				else
					cout << "id重复，请重新输入" << endl;
			}
			cout << "请输入第 " << i + 1 << " 个新职工姓名： " << endl;
			cin >> name;

			cout << "请输入第 " << i + 1 << " 个新职工岗位： " << endl;
			cout << "1.普通职工" << endl;
			cout << "2.经理" << endl;
			cout << "3.老板" << endl;
			while (1) {
				cin >> dSelect;
				if (dSelect == 1 || dSelect == 2 || dSelect == 3)
					break;
				else
					cout << "输入有误，没有该职位，请重新输入" << endl;
			}
			

			Worker * worker = NULL;
			
			switch (dSelect) {
			case 1:
				worker = new Employee(id, name, 1);
				
				break;
			case 2:
				worker = new Manager(id, name, 2);
				break;
			case 3:
				worker = new Boss(id, name, 3);
				break;
			default:
				cout << "输入有误，没有该职位，请重新输入" << endl;
				break;
			}
			// 将创建职工保存到数组
			newSpace[this->m_EmpNum + i] = worker;
			
		}
		// 释放原有空间
		
		delete[] this->m_EmpArray;
		
		//更改新空间指向
		this->m_EmpArray = newSpace;
		//更新人数
		this->m_EmpNum = newSize;
		//提示添加成功
		cout << "成功添加" << addNum << "名新职工!" << endl;
		

		// 保存数据
		this->save();
		this->m_FileIsEmpty = false;
		
	}
	else
		cout << "输入有误" << endl;
	system("pause");
	system("cls");
}

void WorkerManager::save() {
	
	ofstream ofs;
	ofs.open(FILENAME, ios::out);
	//写入
	
	ofs << "职工编号" << "," << "职工名字" << "," << "职工职位" << endl;
	
	for (int i = 0 ; i < this->m_EmpNum; i++) {
		ofs << this->m_EmpArray[i]->m_Id << ","
			<< this->m_EmpArray[i]->m_Name << ","
			<< this->m_EmpArray[i]->getDeptName() << endl;
	}
	ofs.close();
}

int WorkerManager::get_EmpNum()  {
	int num = 0;
	if (!this->m_FileIsEmpty) {
		ifstream ifs;
		ifs.open(FILENAME, ios::in);
		string line;
		
		while (getline(ifs, line)) {
			num++;
		}
		num -= 1;

	}
	return num;
}

 //初始化员工
void WorkerManager::init_Emp() {
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	string line;
	int index = 0;
	while (getline(ifs, line)) {

		istringstream sin(line);
		vector<string> fields;
		string field;
		if (index > 0) {
			while (getline(sin, field, ',')) {
				fields.push_back(field);
			}
			int id = std::stoi(Trim(fields[0]));
			string name = Trim(fields[1]);
			string dId = Trim(fields[2]);
			Worker * worker = NULL;

			if (dId == "员工") {
				worker = new Employee(id, name, 1);
			}
			else if (dId == "经理") {
				worker = new Manager(id, name, 2);
			}
			else if (dId == "总裁") {
				worker = new Boss(id, name, 3);
			}
			this->m_EmpArray[index - 1] = worker;
		}
		index++;
	}
	ifs.close();
}

void WorkerManager::Show_Emp() {
	//判断文件是否有内容
	if (this->m_FileIsEmpty) {
		cout << "文件不存在或为空" << endl;
	}
	else {
		for (int i = 0; i < m_EmpNum; i++) {
			this->m_EmpArray[i]->showInfo();
		}
	}
	system("pause");
	system("cls");
}

// 删除员工
void WorkerManager::Del_Emp() {
	if (this->m_FileIsEmpty) {
		cout << "文件不存在或为空" << endl;

	}
	else {
		// 按id删除
		cout << "输入要删除id" << endl;
		int id = 0;
		cin >> id;
		int index = this->IsExist(id);
		
		if (index != -1) {
			//数据前移
			for (int i = index; i < this->m_EmpNum - 1; i++) {
				this->m_EmpArray[i] = this->m_EmpArray[i + 1];
			}
			this->m_EmpNum--;
			// 同步到文件中
			this->save();
		}
		else
			cout << "未找到该数据，删除失败" << endl;
	}
	system("pause");
	system("cls");
}

// 判断职工是否存在
int WorkerManager::IsExist(int id) {
	int index = -1;
	for (int i = 0; i < this->m_EmpNum; i++) {
		if (this->m_EmpArray[i]->m_Id == id) {
			index = i;
			break;
		}
	}
	return index;
}


// 修改职工
void WorkerManager::Mod_Emp() {
	if (this->m_FileIsEmpty) {
		cout << "文件不存在或为空" << endl;
	}
	else {
		cout << "请输入修改用户编号：" << endl;
		int id;
		cin >> id;
		int ret = this->IsExist(id);
		if (ret != -1) {
			//查找编号员工
			delete this->m_EmpArray[ret];
			int newId = 0;
			string newName = "";
			int dSelect = 0;
			cout << "查到： " << id << "号职工,请输入新职工号：" << endl;
			cin >> newId;
			cout << "请输入新的姓名: " << endl;
			cin >> newName;
			cout << "请输入新的岗位: " << endl;
			cout << "1.普通职工" << endl;
			cout << "2.经理" << endl;
			cout << "3.老板" << endl;
			while (1) {
				cin >> dSelect;
				if (dSelect == 1 || dSelect == 2 || dSelect == 3)
					break;
				else
					cout << "输入有误，没有该职位，请重新输入" << endl;
			}

			Worker * worker = NULL;

			switch (dSelect) {
			case 1:
				worker = new Employee(newId, newName, 1);

				break;
			case 2:
				worker = new Manager(newId, newName, 2);
				break;
			case 3:
				worker = new Boss(newId, newName, 3);
				break;
			default:
				cout << "输入有误，没有该职位，请重新输入" << endl;
				break;
			}
			// 更新到数组中
			this->m_EmpArray[ret] = worker;
			cout << "修改成功" << endl;

			// 保存
			this->save();
			
		}
		else {
			cout << "修改失败，查无此人" << endl;
		}
	}
	system("pause");
	system("cls");
}

//查找员工
void WorkerManager::Find_Emp() {
	if (this->m_FileIsEmpty) {
		cout << "文件不存在或为空" << endl;

	}
	else
	{
		cout << "请输入查找方式" << endl;
		cout << "1.按照职工编号查找" << endl;
		cout << "2.按照职工姓名查找" << endl;
		int select = 0;
		cin >> select;
		if (select == 1) {
			// 按编号查
			int id;
			cout << "请输入用户查找编号 " << endl;
			cin >> id;
			int ret = IsExist(id);
			if (ret != -1) {
				cout << "查找成功！该职工信息如下：" << endl;
				this->m_EmpArray[ret]->showInfo();
			}
			else
				cout << "查无此人" << endl;
		}
		else if (select == 2) {
			// 按名字查
			string name;
			cout << "请输入用户查找姓名 " << endl;
			cin >> name;

			bool flag = false; // 是否有该员工0
			for (int i = 0; i < m_EmpNum; i++) {
				if (this->m_EmpArray[i]->m_Name == name) {
					cout << "查找成功！该职工信息如下：" << endl;
					this->m_EmpArray[i]->showInfo();
					flag = true;
					
				}
				
			}
			if (flag == false)
				cout << "查找失败，查无此人" << endl;
		}
		else {
			cout << "输入选项有误" << endl;
		}
	}
	system("pause");
	system("cls");

}

void WorkerManager::Sort_Emp() {
	if (this->m_FileIsEmpty) {
		cout << "文件不存在或为空" << endl;
		system("pause");
		system("cls");

	}
	else
	{
		cout << "请输入排序方式" << endl;
		cout << "1.按照职工编号升序排序" << endl;
		cout << "2.按照职工编号降序排序" << endl;
		int select = 0;
		cin >> select;

		for (int i = 0; i < m_EmpNum-1; i++) {
			int minOrMax = i;
			for (int j = i + 1; j < m_EmpNum; j++) {
				if (select == 1) {
					if (this->m_EmpArray[minOrMax]->m_Id > this->m_EmpArray[j]->m_Id) {
						minOrMax = j;
					}
					
				}
				else {
					if (this->m_EmpArray[minOrMax]->m_Id < this->m_EmpArray[j]->m_Id) {
						minOrMax = j;
					}
				}
			}
			if (i != minOrMax) {
				Worker * temp = this->m_EmpArray[i];
				this->m_EmpArray[i] = this->m_EmpArray[minOrMax];
				this->m_EmpArray[minOrMax] = temp;
			}
		}
		cout << "排序成功！排序后结果为：" << endl;
		this->save();
		this->Show_Emp();
	}

}

void WorkerManager::Clean_File() {
	cout << "确认清空?" << endl;
	cout << "1.确认!" << endl;
	cout << "2.返回!" << endl;
	int select = 0;
	cin >> select;
	if (select == 1) {
		ofstream ofs(FILENAME, ios::trunc);
		ofs.close();

		if (this->m_EmpArray != NULL) {
			for (int i = 0; i < this->m_EmpNum; i++) {
				delete this->m_EmpArray[i];
				this->m_EmpArray[i] = NULL;
			}
			delete[] this->m_EmpArray;
			this->m_EmpArray = NULL;
			this->m_EmpNum = 0;
			this->m_FileIsEmpty = true;
		}
		cout << "清空成功!!!" << endl;
	}
	system("pause");
	system("cls");
}

WorkerManager::~WorkerManager() {
	if (this->m_EmpArray != NULL) {
		for (int i = 0; i < this->m_EmpNum; i++) {
			delete this->m_EmpArray[i];
			this->m_EmpArray[i] = NULL;
		}
		delete[] this->m_EmpArray;
		this->m_EmpArray = NULL;
	}
}


// 读取csv
string Trim(string& str)
{
	str.erase(0, str.find_first_not_of(" \t\r\n"));
	str.erase(str.find_last_not_of(" \t\r\n") + 1);
	return str;
}
