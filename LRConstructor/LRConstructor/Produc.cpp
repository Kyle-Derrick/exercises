#include "include\Produc.h"

string Produc::getStr()
{
	return this->str;
}

Symbol Produc::getLeft()
{
	return this->left;
}

string Produc::getArrow()
{
	return this->arrow;
}

vector<Symbol> Produc::getRight()
{
	return this->right;
}

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

vector<Produc> Produc::identify(const vector<string>& terminators,
	const vector<string>& non_terminators, vector<Produc>& producs, const string& arrow, const string& str, const string& delim)
{
	size_t index = str.find(arrow);
	Symbol left(str.substr(0, index), SymbolType::NON_TERMINATOR);

	index += arrow.length();
	vector<string> tmp;
	if (delim.empty())
	{
		tmp.push_back(str.substr(index));
	}
	else
	{
		kyle::split(tmp, str.substr(index), "|");
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
		producs.push_back(Produc(str, left, arrow, right));
	}
	return producs;
}

