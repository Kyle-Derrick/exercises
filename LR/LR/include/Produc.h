#pragma once
#ifndef _PRODUC_CLASS_
#define _PRODUC_CLASS_

#include <iostream>
#include <vector>
#include "Base.h"

using namespace std;

//产生式类
class Produc
{
private:
	//产生式字符串
	string str;
	//产生式左侧
	string left;
	//产生式推导符
	string arrow;
	//产生式右侧符号集
	vector<string> right;
public:
	string getStr();
	string getLeft();
	string getArrow();
	vector<string> getRight();
	Produc(string str, string left, string arrow, vector<string> right);
	~Produc();
	//通过解析字符串生成产生式对象
	static Produc identify(vector<string> &symbols, string arrow, string str);
	////通过符号表解析字符串为字符串列表
	//static vector<string> analyzestr(const vector<string>& symbols, vector<string>& strs, string str);
};

#endif