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

#endif // !_LR_BASE_H_

