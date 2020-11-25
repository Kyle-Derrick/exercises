#pragma once
#ifndef _PRODUC_CLASS_
#define _PRODUC_CLASS_

#include <iostream>
#include <vector>
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
	static Produc identify(vector<string> &symbols, string arrow, string str);
	////ͨ�����ű�����ַ���Ϊ�ַ����б�
	//static vector<string> analyzestr(const vector<string>& symbols, vector<string>& strs, string str);
};

#endif