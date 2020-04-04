# include <iostream>
# include <string>
using namespace std;


int main()
{
	// 输入三只小猪体重，判断谁是最重的

	// 创建小猪体重
	int num1 = 0;
	int num2 = 0;
	int num3 = 0;

	// 输入小猪体重
	cout << "输入小猪A体重" << endl;
	cin >> num1;
	cout << "输入小猪B体重" << endl;
	cin >> num2;
	cout << "输入小猪C体重" << endl;
	cin >> num3;

	cout << "输入小猪A体重" << num1 << endl;
	cout << "输入小猪B体重" << num2 << endl;
	cout << "输入小猪C体重" << num3 << endl;

	// 判断
	if (num1 > num2)
	{
		if (num1 > num3)
		{
			cout << "小猪A最重" << endl;
		}
		else
		{
			cout << "小猪C最重" << endl;
		}
	}
	else
	{
		if (num2 > num3)
		{
			cout << "小猪B最重" << endl;
		}
		else
		{
			cout << "小猪C最重" << endl;
		}
	}

	system("pause");
	return 0;

}