
#include <iostream>
#include <map>
#include <math.h>
#include "include/KyleBase.h"
#include "include/LexicalAnalysis.h"
#include "include/Appcontext.h"
#include "include/LRAnalyze.h"
#include "include/InitApp.h"

using namespace std;


int main(int argc , char *argv[])
{
	cout << "Calculator by LR Grammatical analysis by Kyle Derrick ^_^" << endl;
	cout << "---------------------------------------------------------" << endl;

	//获取配置文件路径
	string fpath;
	if (argc > 1)
	{
		fpath = argv[1];
	}
	else
	{
		cout << "输入配置文件路径:\n> ";
		cin >> fpath;
	}

	InitApp::init();

	//解析配置文件
	AppContext context = AppContext::init(fpath);
	//context.testPrint();
	LRAnalyze lr = LRAnalyze(context);

	string instr;
	while (true)
	{
		cout << "\n输入式子:\n> ";
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
