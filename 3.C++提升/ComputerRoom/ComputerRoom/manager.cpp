#include "manager.h"

// 默认构造
Manager::Manager() {

}

// 有参构造
Manager::Manager(string name, string pwd) {
	this->m_Name = name;
	this->m_Pwd = pwd;
	this->initVector();

	// 获取机房信息
	ifstream ifs(COMPUTER_FILE);
	ComputerRoom c;
	while (ifs >> c.m_ComId && ifs >> c.m_MaxNum)
		vCom.push_back(c);
	// cout << "当前机房数量：" << vCom.size() << endl;
	ifs.close();
}

// 选择菜单
void Manager::openMenu() {
	cout << "欢迎管理员：" << this->m_Name << "登陆！" << endl;
	cout << "\t\t  ------------------------------\n";
	cout << "\t\t|                               |\n";
	cout << "\t\t|         1.添加账号            |\n";
	cout << "\t\t|                               |\n";
	cout << "\t\t|         2.查看账号            |\n";
	cout << "\t\t|                               |\n";
	cout << "\t\t|         3.查看机房            |\n";
	cout << "\t\t|                               |\n";
	cout << "\t\t|         4.清空预约            |\n";
	cout << "\t\t|                               |\n";
	cout << "\t\t|         0.注销登陆            |\n";
	cout << "\t\t|                               |\n";
	cout << "\t\t  ------------------------------\n";
	cout << "请输入您的操作：" << endl;

}

// 添加账号
void Manager::addPerson() {
	cout << "请输入添加账号类型" << endl;
	cout << "1.添加学生" << endl;
	cout << "2.添加老师" << endl;
	string fileName;
	string tip;
	ofstream ofs;

	int select = 0;
	cin >> select;
	bool ret;
	string errorTip; // 重复提示
	if (select == 1) {
		fileName = STUDENT_FILE;
		tip = "请输入学号：";
		errorTip = "学号重复，请重新输入";
	}
	else {
		fileName = TEACHER_FILE;
		tip = "请输入职工编号：";
		errorTip = "职工号重复，请重新输入";
	}
	ofs.open(fileName, ios::out | ios::app);
	int id;
	string name;
	string pwd;
	cout << tip << endl;
	while (1) {
		cin >> id;
		if (select == 1)
			ret = this->checkRepeat(id, 1);
		else
			 ret = this->checkRepeat(id, 2);
		if (ret) {
			cout << errorTip << endl;
		}
		else {
			break;
		}
	}
	
	cout << "请输入姓名：" << endl;
	cin >> name;
	cout << "请输入密码：" << endl;
	cin >> pwd;

	ofs << id << " " << name << " " << pwd << " " << endl;
	cout << "添加成功" << endl;

	system("pause");
	system("cls");
	ofs.close();
	this->initVector();
}


// 初始化容器
void Manager::initVector() {
	ifstream ifs;
	ifs.open(STUDENT_FILE, ios::in);
	if (!ifs.is_open()) {
		cout << "文件读取失败" << endl;
		return;
	}
	vStu.clear();
	vTea.clear();

	Student s;
	while (ifs >> s.m_Id && ifs >> s.m_Name && ifs >> s.m_Pwd) {
		vStu.push_back(s);
	}
	cout << "当前学生数量为：" << vStu.size() << endl;
	ifs.close();

	// 读取老师信息
	ifs.open(TEACHER_FILE, ios::in);
	Teacher t;
	while (ifs >> t.m_EmpId && ifs >> t.m_Name && ifs >> t.m_Pwd) {
		vTea.push_back(t);
	}
	cout << "当前教师数量为：" << vTea.size() << endl;
	ifs.close();

}

// 检测是否有重复
bool Manager::checkRepeat(int id, int type) {
	if (type == 1) {
		for (auto it : vStu) {
			if (id == it.m_Id)
				return true;
		}
	}
	else {
		for (auto it : vTea) {
			if (id == it.m_EmpId)
				return true;
		}
	}
	return false;
}

// 查看账号
void Manager::showPerson() {
	cout << "请选择查看内容" << endl;
	cout << "1.查看所有学生" << endl;
	cout << "2.查看所有老师" << endl;

	int select = 0;
	cin >> select;

	if (select == 1) {
		cout << "所有学生信息入下：" << endl;
		for_each(vStu.begin(), vStu.end(), printStudent);
	}
	else {
		cout << "所有老师信息入下：" << endl;
		for_each(vTea.begin(), vTea.end(), printTeacher);
	}
	system("pause");
	system("cls");
}

// 查看机房信息
void Manager::showComputer() {
	cout << "机房信息入下：" << endl;
	for (auto it : vCom) {
		cout << "机房编号：" << it.m_ComId << " 机房最大容量：" << it.m_MaxNum << endl;
	}
	system("pause");
	system("cls");
}

// 清空预约
void Manager::cleanFile() {
	ofstream ofs(ORDER_FILE, ios::trunc);
	ofs.close();

	cout << "清空成功" << endl;
	system("pause");
	system("cls");
}

void printStudent(Student & s) {
	cout << "学号: " << s.m_Id << "姓名：" << s.m_Name << "密码：" << s.m_Pwd << endl;
}
void printTeacher(Teacher & t) {
	cout << "职工号: " << t.m_EmpId << "姓名：" << t.m_Name << "密码：" << t.m_Pwd << endl;
}