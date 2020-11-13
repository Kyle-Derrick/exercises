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
{}

Produc& Produc::identify(vector<string> &symbols, string arrow, string str)
{
	size_t index = str.find(arrow);
	string left = str.substr(0, index);
	vector<string> right;
	index += arrow.length();
	while (true)
	{
		size_t tmp = index;
		for (string symbol : symbols)
		{
			size_t len = symbol.length();
			if (!str.compare(index, len, symbol))
			{
				right.push_back(str.substr(index, len));
				index += len;
				break;
			}
		}
		if (tmp == index)
		{
			cout << "解析产生式时出现未知符号: " << 
				str.substr(index) << endl;
			exit(EXIT_FAILURE);
		}
		else if (index >= str.length())
		{
			break;
		}
	}
	return *new Produc(str, left, arrow, right);
}
