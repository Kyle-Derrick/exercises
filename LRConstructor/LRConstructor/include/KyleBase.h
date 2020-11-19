#pragma once
#ifndef _KYLE_BASE_H_
#define _KYLE_BASE_H_

#include <iostream>
#include <vector>
#include <algorithm>

namespace kyle {
	using namespace std;

	//去除首位空格
	extern string& trim(string& s);
	//按分隔符切分字符串，用vector存储
	extern vector<string>& split(vector<string>& list, const string& str, string delim);
	//通过符号表解析字符串为字符串列表
	extern vector<string>& str_to_symbols(const vector<string>& symbols, vector<string>& strs, const string& str);
	//将符号列表从大到小排序
	extern vector<string>& sort_by_len(vector<string>& strs);
}

#endif // !_LR_BASE_H_

