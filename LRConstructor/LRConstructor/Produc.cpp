#include "include\Produc.h"

string Produc::getStr() const
{
	return this->str;
}

Symbol Produc::getLeft() const
{
	return this->left;
}

string Produc::getArrow() const
{
	return this->arrow;
}

vector<Symbol> Produc::getRight() const
{
	return this->right;
}

Produc::Produc()
{}

Produc::Produc(string str, Symbol left, string arrow, vector<Symbol> right)
{
	this->str = str;
	this->left = left;
	this->arrow = arrow;
	this->right = right;
}

Produc::~Produc()
{
	vector<Symbol>().swap(this->right);
}

bool Produc::operator==(const Produc& p) const
{
	return this->str == p.str;
}

Symbol Produc::identify(const vector<string>& terminators,
	const vector<string>& non_terminators, vector<Produc>& producs, const string& arrow, const string& str, const string& delim)
{
	size_t index = str.find(arrow);
	Symbol left(str.substr(0, index), SymbolType::NON_TERMINATOR);
	//判断产生式右部符号是否是非终结符列表中的的符号
	if (find(non_terminators.begin(), non_terminators.end(), left.getStr()) == non_terminators.end())
	{
		cerr << "未知符号: " << left.getStr() << endl;
		exit(EXIT_FAILURE);
	}

	index += arrow.length();
	vector<string> tmp;
	if (delim.empty())
	{
		tmp.push_back(str.substr(index));
	}
	else
	{
		kyle::split(tmp, str.substr(index), delim);
	}
	for (string s : tmp) {
		kyle::trim(s);

		vector<Symbol> right;
		try
		{
			Symbol::str_to_symbols(terminators, non_terminators, right, s);
		}
		catch (string estr)
		{
			cerr << estr << endl;
			exit(EXIT_FAILURE);
		}
		producs.push_back(Produc(left.getStr()+arrow+s, left, arrow, right));
	}
	return left;
}

