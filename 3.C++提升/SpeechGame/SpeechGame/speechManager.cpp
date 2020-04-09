#include "speechManager.h"
#include<algorithm>
#include<deque>
#include<functional>
#include<numeric>
#include<ctime>
// 构造函数
SpeechManager::SpeechManager() {
	// 初始化容器属性
	this->initSpeech();

	// 创建选手
	this->createSpeaker();

	// 获取往届记录
	this->loadRecord();
}

// 初始化容器和属性
void SpeechManager::initSpeech() {
	// 容器都置空
	this->v1.clear();
	this->v2.clear();
	this->vVictory.clear();
	this->m_Speaker.clear();
	this->m_Record.clear();

	// 初始化比赛轮次
	this->m_Index = 1;
}

// 显示菜单
void SpeechManager::showMenu() {
	cout << "******************************************" << endl;
	cout << "************ 欢迎参加演讲比赛 ************" << endl;
	cout << "************  1.开始演讲比赛  ************" << endl;
	cout << "************  2.查看往届记录  ************" << endl;
	cout << "************  3.清空比赛记录  ************" << endl;
	cout << "************  0.退出比赛程序  ************" << endl;
	cout << "******************************************" << endl;
	cout << endl;
}

// 退出系统
void SpeechManager::exitSystem() {
	cout << "欢迎下次使用" << endl;
	system("pause");
	exit(0);
}

//创建选手
void SpeechManager::createSpeaker() {
	string nameSeed = "ABCDEFGHIJKL";
	for (int i = 0; i < nameSeed.size(); i++) {
		string name = "选手";
		name += nameSeed[i];

		Speaker sp;
		sp.m_Name = name;
		for (int j = 0; j < 2; j++) {
			sp.m_Score[j] = 0;
		}

		// 创建选手编号
		this->v1.push_back(i + 10001);

		// 选手编号对应选手
		this->m_Speaker.insert(make_pair(i + 10001, sp));
	}
}


void SpeechManager::startSpeech() {
	// 第一轮比赛

	// 抽签
	this->speechDraw();

	// 比赛
	this->speechContest();

	// 显示晋级结果
	this->showScore();

	// 第二轮比赛
	this->m_Index++;
	// 抽签
	this->speechDraw();

	// 比赛
	this->speechContest();

	// 显示最终结果
	this->showScore();
	// 保存结果到文件
	this->saveRecord();

	// 重置比赛
	// 初始化容器属性
	this->initSpeech();

	// 创建选手
	this->createSpeaker();

	// 获取往届记录
	this->loadRecord();

	cout << "本届比赛完毕！" << endl;
	system("pause");
	system("cls");
}

// 抽签
void  SpeechManager::speechDraw() {
	srand((unsigned int) time(NULL));
	cout << "第 " << this->m_Index << " 轮比赛选手正在抽签" << endl;
	cout << "---------------------------------------------------------------------------------------" << endl;
	cout << "抽签后演讲顺序如下：" << endl;
	if (this->m_Index == 1) {
		// 第一轮
		random_shuffle(v1.begin(), v1.end());
		for (auto it : v1) {
			cout << it << " ";
		}
		cout << endl;
	}
	else {
		// 第二轮
		random_shuffle(v2.begin(), v2.end());
		for (auto it : v2) {
			cout << it << " ";
		}
		cout << endl;
	}
	cout << "---------------------------------------------------------------------------------------" << endl;
	system("pause");
	cout << endl;
	
}

// 比赛
void SpeechManager::speechContest() {
	srand((unsigned int)time(NULL));
	cout << "----------第 " << this->m_Index << " 轮比赛选手正在抽签----------" << endl;

	// 临时容器存放小组成绩
	multimap<double, int, greater<double>> groupScore;

	int num = 0;// 记录人员个数，6人一组

	vector<int>v_Src; // 比赛选手容器
	if (this->m_Index == 1) {
		v_Src = v1;
	}
	else {
		v_Src = v2;
	}

	// 遍历所有选手进行比赛
	for (auto it : v_Src) {

		num++;
		// 评委打分
		deque<double>d;
		for (int i = 0; i < 10; i++) {
			double score = (rand() % 401 + 600) / 10.f;
			//cout << score << " ";
			d.push_back(score);
		}
		//cout << endl;
		sort(d.begin(), d.end(), greater<double>()); // 降序排序
		d.pop_back(); // 去除最低分
		d.pop_front(); // 去除最高分

		double sum = accumulate(d.begin(), d.end(), 0.f);
		double avg = sum / (double)d.size(); // 求平均分

		// 打印平均分
		// cout << "编号： " << it << "姓名：" << this->m_Speaker[it].m_Name << "得分：" << avg << endl;

		// 将平均分放入map容器中
		this->m_Speaker[it].m_Score[this->m_Index - 1] = avg;

		// 将打分数据放入临时小组容器中
		groupScore.insert(make_pair(avg, it));
		// 每6人取出前三名
		if (num % 6 == 0) {
			cout << "第 " << num / 6 << " 小组比赛名次：" << endl;
			for (auto mt : groupScore) {
				cout << "编号： " << mt.second << "姓名: " << this->m_Speaker[mt.second].m_Name
					<< "成绩：" << this->m_Speaker[mt.second].m_Score[this->m_Index - 1] << endl;
			}
			
			// 取走前三名
			int count = 0;
			for (auto mt : groupScore) {
				if (count < 3) {
					if (this->m_Index == 1) {
						v2.push_back(mt.second);
					}
					else
						vVictory.push_back(mt.second);
					count += 1;
				}
				else
					break;
			}
			// 小组容器清空
			groupScore.clear();
			cout << endl;
		}
	}
	cout << "----------第 " << this->m_Index << " 轮比赛完毕----------" << endl;
	system("pause");
}

// 显示得分
void SpeechManager::showScore() {
	cout << "----------第 " << this->m_Index << " 轮晋级选手信息如下----------" << endl;
	vector<int> v;
	if (this->m_Index == 1)
		v = v2;
	else
		v = vVictory;
	for (auto it : v) {
		cout << "选手编号：" << it << "姓名：" << this->m_Speaker[it].m_Name 
			<< "得分：" << this->m_Speaker[it].m_Score[this->m_Index - 1] << endl;
	}
	cout << endl;
	system("pause");
	system("cls");
	// if (this->m_Index == 1)
	this->showMenu();
}

// 判断文件是否为空
bool SpeechManager::is_File() {
	// 文件不存在或文件为空
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	if (ifs.is_open()) {
		char ch;
		ifs >> ch;
		if (!ifs.eof()) {
			ifs.close();
			return true; // 文件有内容
		}

	}
	ifs.close();
	return false; // 空文件或没内容
}

// 查看已有几届数据
int SpeechManager::CountNum() {
	int num = 0;
	
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	string line;

	while (getline(ifs, line)) {
		num++;
	}
	num -= 1;

	
	return num/3;
}

// 保存分数
void SpeechManager::saveRecord() {
	
	int num = 0;
	ofstream ofs;
	ofs.open("speech.csv", ios::out | ios::app);
	if (!this->is_File()) {
		ofs << " " << "," << "选手编号" << "," << "选手姓名" << "," << "选手分数" << endl;
	}
	else
		num = this->CountNum();
	ofs << "第" << num + 1 << "届";
	int cnt = 0;
	for (auto it : vVictory) {
		if (cnt == 0)
			ofs << "," << it << "," << this->m_Speaker[it].m_Name << "," << this->m_Speaker[it].m_Score[1] << endl;
		else
			ofs << " " << "," << it << "," << this->m_Speaker[it].m_Name << "," << this->m_Speaker[it].m_Score[1] << endl;
		cnt++;
	}
	ofs.close();
	cout << "记录已保存" << endl;
}

// 读取记录
void SpeechManager::loadRecord() {
	if (!this->is_File()) {
		// cout << "文件为空或不存在" << endl;
		return;
	}
	vector<vector<string>>v; // 存放3个选手数据
	vector<string> v1; // 存放每个选手数据
	ifstream ifs(FILENAME);
	string line;
	int index = 0;
	string Num;
	while (getline(ifs, line)) {

		istringstream sin(line);
		vector<string> fields;
		string field;
		if (index > 0) {
			while (getline(sin, field, ',')) {
				fields.push_back(field);
			}
			if ((index-1)%3 == 0)
				Num = Trim(fields[0]);
			
			string id = Trim(fields[1]);
			v1.push_back(id);
			string name = Trim(fields[2]);
			v1.push_back(name);
			string score = Trim(fields[3]);
			v1.push_back(score);
			v.push_back(v1);
			v1.clear();
			if (index % 3 == 0) {
				if (index != 0) {
					m_Record.insert(make_pair(Num, v));
					v.clear();
				}

			}
		}
		index++;
	}
	ifs.close();
}

// 查看数据
void SpeechManager::showRecord() {
	if (!this->is_File()) {
		cout << "文件为空或不存在" << endl;
		system("pause");
		system("cls");
		return;
	}
	for (auto it : this->m_Record) {
		cout << "---------------" << it.first << "---------------" << endl;
		cout << "冠军编号：" << it.second[0][0] << "姓名：" << it.second[0][1] << "得分：" << it.second[0][2] << endl;
		cout << "亚军编号：" << it.second[1][0] << "姓名：" << it.second[1][1] << "得分：" << it.second[1][2] << endl;
		cout << "季军编号：" << it.second[2][0] << "姓名：" << it.second[2][1] << "得分：" << it.second[2][2] << endl;

	}
	system("pause");
	system("cls");
}

void SpeechManager::clearRecord() {
	cout << "确认清空？" << endl;
	cout << "1.确认" << endl;
	cout << "2.返回" << endl;

	int select = 0;
	cin >> select;

	if (select == 1) {
		ofstream ofs(FILENAME, ios::trunc);
		ofs.close();
		this->initSpeech();
		this->createSpeaker();
		this->loadRecord();

		cout << "清空成功" << endl;
	}
	system("pause");
	system("cls");
}

// 析构函数
SpeechManager::~SpeechManager() {

}

// 读取csv
string Trim(string& str)
{
	str.erase(0, str.find_first_not_of(" \t\r\n"));
	str.erase(str.find_last_not_of(" \t\r\n") + 1);
	return str;
}