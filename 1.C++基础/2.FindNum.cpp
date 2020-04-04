# include <iostream>
# include <string>
using namespace std;


int main()
{
	// 输入随机数，猜大小

	// 生成随机数
	int num = rand() % 100;
	int val = 0;
	cin >> val;
	while (val != num)
	{
		if (val > num)
		{
			cout << "猜大了" << endl;
		}
		else
		{
			cout << "猜小了" << endl;
		}
		cin >> val;
	}
	cout << "猜对了哟" << endl;

	

	system("pause");
	return 0;

}