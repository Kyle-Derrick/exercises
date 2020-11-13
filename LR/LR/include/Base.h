#pragma once
#ifndef _LR_BASE_H_
#define _LR_BASE_H_

#include <iostream>
#include <vector>

using namespace std;

//去除首位空格
extern string& trim(string &s);
//按分隔符切分字符串，用vector存储
extern vector<string>& split(vector<string>& list, string& str, string delim);
//通过符号表解析字符串为字符串列表
extern vector<string> str_to_symbols(const vector<string>& symbols, vector<string>& strs, string str);

#endif // !_LR_BASE_H_

