#pragma once
#ifndef _LR_CONSTRUCTOR_CONTEXT_
#define _LR_CONSTRUCTOR_CONTEXT_
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <string>
#include <map>
#include <set>
#include "Produc.h"

using namespace std;
class LRContext
{
private:
	//终结符集，用于该类内部排序后的，下同
	vector<string> terminators;
	//非终结符集
	vector<string> non_terminators;
	//产生式列表
	vector<Produc> producs;
	//产生式映射，key值为产生式左部，值为产生式在产生式列表中的编号
	map<string, set<size_t>> produc_map;
	//推导符
	string arrow;
	//分隔符
	string delim;
	//开始符号
	Symbol start_symbol;
	//解析产生式
	static void produc_analyze(
		const string& line, const string& arrow, const string& delim, const vector<string>& terminators,
		const vector<string>& non_terminators, vector<Produc>& producs,
		map<string, set<size_t>>& produc_map);
public:
	//终结符集，按读入顺序排列，下同
	vector<string> terminators_source;
	//非终结符
	vector<string> non_terminators_source;
	//初始化，读取并解析配置文件
	static LRContext init(string fpath);
	//测试输出
	void test();
	//根据编号获取产生式
	Produc get_produc(size_t no);
	//获取推导符
	string get_arrow();
	string get_delim();
	//获取开始符号
	Symbol& get_start_symbol();
	//设置扩展文法时产生的产生式
	void set_expand_produc(const Produc& p);
	//根据非终结符获取该非终结符的所有产生式
	set<size_t>* get_produc_nos(const string& symbol);
	//判断字符串是否是非终结符集中定义的
	bool non_terminators_exist(const string& symbol);
	//输出符号列表和产生式列表
	ostream& output(ostream& out);
};

#endif