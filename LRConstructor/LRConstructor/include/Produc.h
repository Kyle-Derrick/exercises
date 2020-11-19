#pragma once
#ifndef _PRODUC_CLASS_
#define _PRODUC_CLASS_

#include <iostream>
#include <vector>
#include <algorithm>
#include "KyleBase.h"
#include "Symbol.h"

using namespace std;

//����ʽ��
class Produc
{
private:
	//����ʽ�ַ���
	string str;
	//����ʽ���
	Symbol left;
	//����ʽ�Ƶ���
	string arrow;
	//����ʽ�Ҳ���ż�
	vector<Symbol> right;
public:
	string getStr();
	Symbol getLeft();
	string getArrow();
	vector<Symbol> getRight();
	Produc(string str, Symbol left, string arrow, vector<Symbol> right);
	~Produc();
	//ͨ�������ַ������ɲ���ʽ����
	static Symbol identify(const vector<string>& terminators,
		const vector<string>& non_terminators, vector<Produc>& producs, 
		const string& arrow, const string& str, const string& delim);
};

#endif