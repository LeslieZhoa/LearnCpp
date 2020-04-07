#pragma once
using namespace std;
#include "worker.h"

class Employee :public Worker {
public:
	//构造函数
	Employee(int id,string name,int dId);

	//显示个人信息
	void showInfo();

	// 获取职称
	string getDeptName();
};
