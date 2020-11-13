#pragma once
#ifndef _APPCONTEXT_H_
#define _APPCONTEXT_H_

#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>
#include "Produc.h"
#include "Base.h"
#include "TableUnit.h"

using namespace std;

class AppContext
{
private:
	//变量
	//符号集
	vector<string> symbols;
	//action表头
	vector<string> actions;
	//goto表头
	vector<string> gotos;
	//产生式列表
	vector<Produc> producs;
	//action表
	vector<vector<TableUnit>> atable;
	//goto表
	vector<vector<int>> gtable;
	//错误信息列表
	vector<string> errors;
	//推导符号
	string arrow;

	//获取配置文件当前行类型，空行或注释为-1，内容为0，符号列表、产生式列表、分析表、错误信息配置标志分别为1、2、3、4
	static int lineType(string line);
	//解析符号列表
	static void analyzeSymbol(vector<string>& tmp, vector<string>& symbols, vector<string>& actions, vector<string> &gotos);
	//解析产生式列表
	static void analyzeProduc(vector<string>& tmp, vector<Produc>& pruducs, vector<string>& symbols);
	//解析分析表
	static void analyzeTable(vector<string>& tmp, size_t tsize, size_t psize, size_t asize, size_t gsize,
		vector<vector<TableUnit>>& atable, vector<vector<int>>& gtable);
	//解析错误信息列表
	static void analyzeError(vector<string>& tmp, vector<string>& errors);
	//获取接下来的内容行
	static size_t contentLineSize(ifstream& fs);
public:
	/**
	初始化
	传入分析配置文件路径
	*/
	static AppContext& init(string f);

	TableUnit action_search(string symbol, size_t status);
	int goto_search(string symbol, size_t status);

	void testPrint();
};

#endif // !_APPCONTEXT_H_