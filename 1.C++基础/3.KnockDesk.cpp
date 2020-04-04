# include <iostream>
# include <string>
using namespace std;


int main()
{
	// 数7

	for (int i = 0; i <= 100; i++)
	{
		if (i % 7 == 0 || i % 10 == 7 || i / 10 == 7)
			cout << "数字为: " << i << "\t就是你" << endl;
	}

	

	system("pause");
	return 0;

}