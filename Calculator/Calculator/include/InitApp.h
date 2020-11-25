#pragma once
#ifndef _CALCULATOR_INIT_APP_H_
#define _CALCULATOR_INIT_APP_H_
#include <iostream>
#include <vector>
#include <map>
#include <math.h>
#include "Symbol.h"

using namespace std;

typedef map<string, double(*)(vector<double>)> Functions;
typedef map<string, Symbol(*)(vector<Symbol>)> Reduces;

class InitApp
{
private:
	static void check_arg(string fname, size_t args_size, size_t need_size);
public:
	//计算器所支持的计算函数，后续可填加
	static Functions funs;
	//产生式规约方法
	static Reduces reduces;

	//加载计算方法集
	static Functions& load_funs(Functions& fs);
	//加载规约方法集
	static Reduces& load_reduces(Reduces& fs);
	//初始化
	static void init();
};

#endif