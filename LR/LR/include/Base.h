#pragma once
#ifndef _LR_BASE_H_
#define _LR_BASE_H_

#include <iostream>
#include <vector>

using namespace std;

//ȥ����λ�ո�
extern string& trim(string &s);
//���ָ����з��ַ�������vector�洢
extern vector<string>& split(vector<string>& list, string& str, string delim);

#endif // !_LR_BASE_H_

