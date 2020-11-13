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

Produc& Produc::identify(vector<string> &symbols, string arrow, string str)
{
	size_t index = str.find(arrow);
	string left = str.substr(0, index);
	vector<string> right;
	index += arrow.length();
	analyzestr(symbols, right, str.substr(index));
	return *new Produc(str, left, arrow, right);
}

vector<string> Produc::analyzestr(const vector<string>& symbols, vector<string>& strs, string str)
{
	size_t index = 0;
	while (true)
	{
		size_t tmp = index;
		for (string symbol : symbols)
		{
			size_t len = symbol.length();
			if (!str.compare(index, len, symbol))
			{
				strs.push_back(str.substr(index, len));
				index += len;
				break;
			}
		}
		if (tmp == index)
		{
			throw ("解析产生式时出现未知符号:" + str.substr(index));
			/*cout << "解析产生式时出现未知符号: " <<
				str.substr(index) << endl;
			exit(EXIT_FAILURE);*/
		}
		else if (index >= str.length())
		{
			break;
		}
	}
	return vector<string>();
}
