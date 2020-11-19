#pragma once
#ifndef _KYLE_BASE_H_
#define _KYLE_BASE_H_

#include <iostream>
#include <vector>
#include <algorithm>

namespace kyle {
	using namespace std;

	//ȥ����λ�ո�
	extern string& trim(string& s);
	//���ָ����з��ַ�������vector�洢
	extern vector<string>& split(vector<string>& list, const string& str, string delim);
	//ͨ�����ű�����ַ���Ϊ�ַ����б�
	extern vector<string>& str_to_symbols(const vector<string>& symbols, vector<string>& strs, const string& str);
	//�������б�Ӵ�С����
	extern vector<string>& sort_by_len(vector<string>& strs);
}

#endif // !_LR_BASE_H_

