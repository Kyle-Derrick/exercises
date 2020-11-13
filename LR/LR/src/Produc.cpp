#include "..\include\Produc.h"

string Produc::getStr()
{
	return this->str;
}

string Produc::getLeft()
{
	return this->left;
}

string Produc::getArrow()
{
	return this->arrow;
}

vector<string> Produc::getRight()
{
	return this->right;
}

Produc::Produc(string str, string left, string arrow, vector<string> right)
{
	this->str = str;
	this->left = left;
	this->arrow = arrow;
	this->right = right;
}

Produc::~Produc()
{
	vector<string>().swap(this->right);
}

Produc Produc::identify(vector<string> &symbols, string arrow, string str)
{
	size_t index = str.find(arrow);
	string left = str.substr(0, index);
	vector<string> right;
	index += arrow.length();
	//analyzestr(symbols, right, str.substr(index));
	try
	{
		str_to_symbols(symbols, right, str.substr(index));
	}
	catch (string estr)
	{
		cerr << estr << endl;
		exit(EXIT_FAILURE);
	}
	return Produc(str, left, arrow, right);
}

