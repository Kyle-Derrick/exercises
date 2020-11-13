#pragma once
#ifndef _PRODUC_CLASS_
#define _PRODUC_CLASS_

#include <iostream>
#include <vector>
#include "Base.h"

using namespace std;

//����ʽ��
class Produc
{
private:
	//����ʽ�ַ���
	string str;
	//����ʽ���
	string left;
	//����ʽ�Ƶ���
	string arrow;
	//����ʽ�Ҳ���ż�
	vector<string> right;
public:
	string getStr();
	string getLeft();
	string getArrow();
	vector<string> getRight();
	Produc(string str, string left, string arrow, vector<string> right);
	~Produc();
	//ͨ�������ַ������ɲ���ʽ����
	static Produc identify(vector<string> &symbols, string arrow, string str);
	////ͨ�����ű�����ַ���Ϊ�ַ����б�
	//static vector<string> analyzestr(const vector<string>& symbols, vector<string>& strs, string str);
};

#endif