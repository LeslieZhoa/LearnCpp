#pragma once
#include<iostream>
#include<fstream>
#include "globalFile.h"
#include<string>
#include<vector>
#include<algorithm>
#include "computerRoom.h"
#include "orderFile.h"
using namespace std;

// 身份类抽象
class Identity {
public:
	// 操作菜单
	virtual void openMenu() = 0;

	string m_Name; // 用户名
	string m_Pwd; //用户密码
};