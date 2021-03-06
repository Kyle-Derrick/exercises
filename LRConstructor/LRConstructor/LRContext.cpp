#include "include\LRContext.h"

void LRContext::produc_analyze(
	const string& line, const string& arrow, const string& delim, const vector<string>& terminators,
	const vector<string>& non_terminators, vector<Produc>& producs,
	map<string, set<size_t>>& produc_map)
{
	if (non_terminators.empty() || terminators.empty())
	{
		cerr << "配置文件顺序格式错误！产生式需要在配置文件的最后。" << endl;
		exit(EXIT_FAILURE);
	}
	size_t i = producs.size();
	Symbol left = Produc::identify(terminators, non_terminators, producs, arrow, line, delim);
	for (; i < producs.size(); i++)
	{
		produc_map[left.getStr()].insert(i);
	}
}

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
	string start_symbol;
	string init_delim = " ";
	string delim;
	vector<string> terminators_source;
	vector<string> non_terminators_source;
	vector<string> terminators;
	vector<string> non_terminators;
	vector<Produc> producs;
	//占位，扩展文法时用到
	producs.push_back(Produc());
	map<string, set<size_t>> produc_map;
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
			kyle::split(tmp, line, init_delim);
			switch (status)
			{
			case 0:
				if (tmp.size() < 2)
				{
					cerr << "基本符号配置必须包含推导符和开始符号！" << endl;
					exit(EXIT_FAILURE);
				}
				arrow = tmp.at(0);
				start_symbol = tmp.at(1);
				if (tmp.size() > 2 && !tmp[2].empty())
				{
					delim = tmp.at(2);
					init_delim = delim;
				}
				break;
			case 1:
				terminators.insert(terminators.end(), tmp.begin(), tmp.end());
				terminators_source.insert(terminators_source.end(), tmp.begin(), tmp.end());
				kyle::sort_by_len(terminators);
				break;
			case 2:
				non_terminators.insert(non_terminators.end(), tmp.begin(), tmp.end());
				non_terminators_source.insert(non_terminators_source.end(), tmp.begin(), tmp.end());
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
	context.delim = delim;
	context.terminators_source = terminators_source;
	context.non_terminators_source = non_terminators_source;
	context.terminators = terminators;
	context.non_terminators = non_terminators;
	context.producs = producs;
	context.start_symbol = Symbol(start_symbol, SymbolType::NON_TERMINATOR);
	context.produc_map = produc_map;
	fin.close();
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
	cout << "> 产生式map: " << endl;
	for (auto& p : produc_map)
	{
		cout << "-: " << p.first << ": ";
		for (size_t s : p.second)
		{
			cout << s << '\t';
		}
		cout << endl;
	}
}

Produc LRContext::get_produc(size_t no)
{
	if (no >= this->producs.size())
	{
		return Produc();
	}
	return this->producs.at(no);
}

string LRContext::get_arrow()
{
	return this->arrow;
}

string LRContext::get_delim()
{
	return this->delim;
}

Symbol& LRContext::get_start_symbol()
{
	return this->start_symbol;
}

void LRContext::set_expand_produc(const Produc& p)
{
	*this->producs.begin() = p;
}

set<size_t>* LRContext::get_produc_nos(const string& symbol)
{
	return &produc_map[symbol];
}

bool LRContext::non_terminators_exist(const string& symbol)
{
	return find(non_terminators.begin(), non_terminators.end(), symbol) != non_terminators.end();
}

ostream& LRContext::output(ostream& out)
{
	out << this->delim << endl;
	out << "[symbol-list]" << endl;
	for (string str : this->terminators_source)
	{
		out << str << this->delim;
	}
	out << Symbol::END;
	for (string str : this->non_terminators_source)
	{
		out << this->delim << str;
	}
	out << endl;
	//输出表达式
	out << "[productor-list]" << endl;
	out << this->arrow;
	vector<Produc>::iterator iter = this->producs.begin();
	while (++iter != producs.end())
	{
		Produc& p = *iter;
		out << this->delim << p.getStr();
	}
	out << endl;
	return out;
}
