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