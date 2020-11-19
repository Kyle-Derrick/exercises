#pragma once
#ifndef _PRODUC_CLASS_
#define _PRODUC_CLASS_

#include <iostream>
#include <vector>
#include <algorithm>
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
	static Symbol identify(const vector<string>& terminators,
		const vector<string>& non_terminators, vector<Produc>& producs, 
		const string& arrow, const string& str, const string& delim);
};

#endif