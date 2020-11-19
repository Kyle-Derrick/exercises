#include "include\LRContext.h"

LRContext LRContext::init(string fpath)
{
    ifstream fin(fpath);
	if (!fin.is_open())
	{
		cerr << "打开文件失败：" << fpath << endl;
		exit(EXIT_FAILURE);
	}
	string line;
	string arrow;
	string delim;
	vector<Produc> producs;
	//vector<string> symbols;
	vector<string> terminators;
	vector<string> non_terminators;
	int status = -1;
	while (!fin.eof())
	{
		getline(fin, line);
		kyle::trim(line);
		if (line.empty() || line.at(0) == '#')
		{
			continue;
		}
		else if (line == "[arrow and delim]")
		{
			status = 0;
		}
		else if (line == "[terminators]")
		{
			status = 1;
		}
		else if (line == "[non_terminators]")
		{
			status = 2;
		}
		else if (line == "[producs]")
		{
			status = 3;
		}
		else
		{
			vector<string> tmp;
			kyle::split(tmp, line, ",");
			switch (status)
			{
			case 0:
				arrow = tmp.at(0);
				if (tmp.size() > 1)
				{
					delim = tmp.at(1);
				}
				break;
			case 1:
				//symbols.insert(symbols.end(), tmp.begin(), tmp.end());
				terminators.insert(terminators.end(), tmp.begin(), tmp.end());
				break;
			case 2:
				//symbols.insert(symbols.end(), tmp.begin(), tmp.end());
				non_terminators.insert(non_terminators.end(), tmp.begin(), tmp.end());
				break;
			case 3:
				if (non_terminators.empty() || terminators.empty())
				{
					cerr << "配置文件顺序格式错误！产生式需要在配置文件的最后。" << endl;
					exit(EXIT_FAILURE);
				}
				//kyle::sort_by_len(symbols);
				kyle::sort_by_len(terminators);
				kyle::sort_by_len(non_terminators);
				Produc::identify(terminators, non_terminators, producs, arrow, line, delim);
				break;
			default:
				break;
			}
		}
	}

	LRContext context;
	context.arrow = arrow;
	context.terminators = terminators;
	context.non_terminators = non_terminators;
	context.producs = producs;
    return context;
}

void LRContext::test()
{
	cout << "> 推导符: " << arrow << endl;
	cout << "> 终结符: " << endl;
	for (string s : terminators)
	{
		cout << s << "\t";
	}
	cout << endl;
	cout << "> 非终结符: " << endl;
	for (string s : non_terminators)
	{
		cout << s << "\t";
	}
	cout << endl;
	cout << "> 产生式: " << endl;
	for (Produc p : producs)
	{
		cout << p.getLeft().getStr() << p.getArrow();
		for (Symbol s : p.getRight())
		{
			cout << s.getStr();
		}
		cout << endl;
	}
}
