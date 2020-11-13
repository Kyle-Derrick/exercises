#pragma once
#ifndef _LR_ANALYZE_H_
#define _LR_ANALYZE_H_

#include <iostream>
#include <iomanip>
#include <vector>
#include "AppContext.h"

using namespace std;

struct Node
{
	size_t status;
	string symbol;
};

class LRAnalyze
{
private:
	//分析程序配置
	AppContext context;
	//分析栈
	vector<Node> analyze_stack;
	//分析的句子
	string str;
	//分析的句子所构成的符号串
	vector<string> symbols;
	//入栈
	void stack_push(string symbol, size_t status);
	//出栈，指定个数
	void stack_pop(size_t size);
	//规约处理
	string reduce(TableUnit& unit, string& symbol);
	//释放内存
	void destory();
	//打印当前分析栈和符号串
	ostream& print_status(ostream& os);
public:
	LRAnalyze(AppContext& context);
	~LRAnalyze();
	//初始化
	LRAnalyze& init(string str);
	//开始分析
	void analyze();
};

#endif