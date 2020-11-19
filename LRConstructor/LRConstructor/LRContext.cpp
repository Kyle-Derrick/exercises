#include "include\LRContext.h"

void LRContext::produc_analyze(
	const string& line, const string& arrow, const string& delim, const vector<string>& terminators,
	const vector<string>& non_terminators, vector<Produc>& producs,
	map<Symbol, vector<Produc>>& produc_map)
{
	if (non_terminators.empty() || terminators.empty())
	{
		cerr << "�����ļ�˳���ʽ���󣡲���ʽ��Ҫ�������ļ������" << endl;
		exit(EXIT_FAILURE);
	}
	vector<Produc> producs_tmp;
	Symbol left = Produc::identify(terminators, non_terminators, producs_tmp, arrow, line, delim);
	vector<Produc>& tmp = produc_map[left];
	tmp.insert(tmp.end(), producs_tmp.begin(), producs_tmp.end());
}

LRContext LRContext::init(string fpath)
{
    ifstream fin(fpath);
	if (!fin.is_open())
	{
		cerr << "���ļ�ʧ�ܣ�" << fpath << endl;
		exit(EXIT_FAILURE);
	}
	string line;
	string arrow;
	string start_symbol;
	string delim;
	//vector<string> symbols;
	vector<string> terminators;
	vector<string> non_terminators;
	vector<Produc> producs;
	map<Symbol, vector<Produc>> produc_map;
	int status = -1;
	while (!fin.eof())
	{
		getline(fin, line);
		kyle::trim(line);
		if (line.empty() || line.at(0) == '#')
		{
			continue;
		}
		else if (line == "[base symbol]")
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
				if (tmp.size() < 2)
				{
					cerr << "�����������ñ�������Ƶ����Ϳ�ʼ���ţ�" << endl;
					exit(EXIT_FAILURE);
				}
				arrow = tmp.at(0);
				start_symbol = tmp.at(1);
				if (tmp.size() > 2)
				{
					delim = tmp.at(2);
				}
				break;
			case 1:
				//symbols.insert(symbols.end(), tmp.begin(), tmp.end());
				terminators.insert(terminators.end(), tmp.begin(), tmp.end());
				kyle::sort_by_len(terminators);
				break;
			case 2:
				//symbols.insert(symbols.end(), tmp.begin(), tmp.end());
				non_terminators.insert(non_terminators.end(), tmp.begin(), tmp.end());
				kyle::sort_by_len(non_terminators);
				break;
			case 3:
				produc_analyze(line, arrow, delim, terminators, non_terminators, producs, produc_map);
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
	context.start_symbol = Symbol(start_symbol, SymbolType::NON_TERMINATOR);
    return context;
}

void LRContext::test()
{
	cout << "> �Ƶ���: " << arrow << endl;
	cout << "> �ս��: " << endl;
	for (string s : terminators)
	{
		cout << s << "\t";
	}
	cout << endl;
	cout << "> ���ս��: " << endl;
	for (string s : non_terminators)
	{
		cout << s << "\t";
	}
	cout << endl;
	cout << "> ����ʽ: " << endl;
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
