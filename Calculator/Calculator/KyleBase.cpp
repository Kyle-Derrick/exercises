#include "include\KyleBase.h"

using namespace std;

string& kyle::trim(string& s)
{
	if (!s.empty())
	{
		s.erase(0, s.find_first_not_of(' '));
		s.erase(s.find_last_not_of(' ') + 1);
	}
	return s;
}

vector<string>& kyle::split(vector<string> &list, const string& str, string delim)
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

vector<string>& kyle::str_to_symbols(const vector<string>& symbols, vector<string>& strs, const string& str)
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

vector<string>& kyle::sort_by_len(vector<string>& strs)
{
	sort(strs.begin(), strs.end(), [](string& s1, string& s2) {
		return s1.length() > s2.length();
		});
	return strs;
}

string& kyle::replace_all(string& str, const string& src, const string& target)
{
	size_t index = 0;
	size_t i;
	while ((i = str.find(src, index)) != string::npos)
	{
		str.replace(i, src.length(), target);
		index = i+target.length();
	}
	return str;
}
