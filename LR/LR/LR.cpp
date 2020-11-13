#include <iostream>
#include <vector>
#include "include/AppContext.h"
#include "include/LRAnalyze.h"

using namespace std;

int main(int argc, char *argv[])
{
	cout << "LR Grammatical analysis by Kyle Derrick ^_^" << endl;
	cout << "-------------------------------------------" << endl;

	//获取配置文件路径
	string fpath;
	if (argc > 1)
	{
		fpath = argv[1];
	}
	else
	{
		cout << "输入LR配置文件路径:\n> ";
		cin >> fpath;
	}

	//解析配置文件
	AppContext context = AppContext::init(fpath);
	//context.testPrint();
	LRAnalyze lr = LRAnalyze(context);

	string instr;
	while (true)
	{
		cout << "\n输入句子:\n> ";
		cin >> instr;
		if (instr == "exit")
		{
			break;
		}
		try
		{
			lr.init(instr);
			lr.analyze();
		}
		catch (const string& estr)
		{
			cerr << estr << endl;
		}
	}

	system("pause");
}