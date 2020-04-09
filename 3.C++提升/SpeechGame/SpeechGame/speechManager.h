#pragma once
# include<iostream>
# include<string>
using namespace std;
# include<vector>
# include<map>
# include"speaker.h"
#include <sstream>
# include<fstream>

#define FILENAME "speech.csv"

class SpeechManager {
public:
	//构造
	SpeechManager();

	// 初始化容器和属性
	void initSpeech();

	// 显示菜单
	void showMenu();

	// 退出系统
	void exitSystem();

	//创建选手
	void createSpeaker();

	// 比赛流程控制
	void startSpeech();

	// 抽签
	void speechDraw();

	// 比赛
	void speechContest();

	// 显示得分
	void showScore();

	// 保存分数
	void saveRecord();

	// 判断文件是否为空
	bool is_File();

	// 查看已有几届数据
	int CountNum();

	// 读取记录
	void loadRecord();

	// 查看数据
	void showRecord();

	// 清空记录
	void clearRecord();

	// 存放往届记录容器
	map<string, vector<vector<string>>>m_Record;

	// 成员属性
	// 保存第一轮选手编号、
	vector<int> v1;

	// 第一轮选手晋级编号
	vector<int> v2;

	// 胜出前三名编号
	vector<int>vVictory;

	// 存放编号以及对应选手
	map<int, Speaker> m_Speaker;

	// 存放比赛轮次
	int m_Index;

	//析构
	~SpeechManager();
};

//读取csv
string Trim(string& str);