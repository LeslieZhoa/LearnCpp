#pragma once
using namespace std;
#include<map>
#include "globalFile.h"
#include <string>
#include <fstream>

class OrderFile {
public:
	// 构造函数
	OrderFile();

	// 更新预约记录
	void updateOrder();

	// 记录容器
	map<int, map<string, string>> m_orderData;

	// 预约记录条数
	int m_Size;
};