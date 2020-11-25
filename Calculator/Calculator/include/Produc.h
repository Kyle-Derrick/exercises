#pragma once
#ifndef _PRODUC_CLASS_
#define _PRODUC_CLASS_

#include <iostream>
#include <vector>
#include "KyleBase.h"
#include "Symbol.h"

using namespace std;

//产生式类
class Produc
{
private:
	//产生式字符串
	string str;
	//产生式左侧
	Symbol left;
	//产生式推导符
	string arrow;
	//产生式右侧符号集
	vector<Symbol> right;
public:
	string getStr();
	Symbol getLeft();
	string getArrow();
	vector<Symbol> getRight();
	Produc(string str, Symbol left, string arrow, vector<Symbol> right);
	~Produc();
	//通过解析字符串生成产生式对象
	static Produc identify(vector<string> &symbols, string arrow, string str);
	////通过符号表解析字符串为字符串列表
	//static vector<string> analyzestr(const vector<string>& symbols, vector<string>& strs, string str);
};

#endif