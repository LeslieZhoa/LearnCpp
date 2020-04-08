#pragma once
#include<iostream>
using namespace std;
#include "worker.h"

#include <fstream>
#define FILENAME "empFile.csv"
class WorkerManager {
public:
	WorkerManager();

	//展示菜单
	void Show_Menu();

	// 退出系统
	void ExitSystem();

	//记录员工人数
	int m_EmpNum;


	//职工数组指针
	Worker ** m_EmpArray;

	//添加职工
	void Add_Emp();

	// 保存文件
	void save();

	// 判断文件是否为空
	bool m_FileIsEmpty;

	// 统计文件中人数
	int get_EmpNum();

	//初始化员工
	void init_Emp();

	// 显示职工
	void Show_Emp();

	// 删除员工
	void Del_Emp();
	
	// 判断职工是否存在
	int IsExist(int id);

	// 修改职工
	void Mod_Emp();

	//查找员工
	void Find_Emp();

	// 排序
	void Sort_Emp();

	//清空文件
	void Clean_File();

	~WorkerManager();
};

//读取csv
string Trim(string& str);