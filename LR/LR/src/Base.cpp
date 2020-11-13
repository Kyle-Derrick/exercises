#include "..\include\Base.h"

string& trim(string& s)
{
	if (!s.empty())
	{
		s.erase(0, s.find_first_not_of(' '));
		s.erase(s.find_last_not_of(' ') + 1);
	}
	return s;
}

vector<string>& split(vector<string> &list, string& str, string delim)
{
	if (str.empty())
	{
		return list;
	}
	size_t last = 0;
	size_t index;
	while ((index = str.find(delim, last)) != -1)
	{
		list.push_back(str.substr(last, index-last));
		last = index+1;
	}
	list.push_back(str.substr(last));
	return list;
}

vector<string> str_to_symbols(const vector<string>& symbols, vector<string>& strs, string str)
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
		}
		else if (index >= str.length())
		{
			break;
		}
	}
	return strs;
}
