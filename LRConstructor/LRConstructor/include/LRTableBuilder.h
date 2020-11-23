#pragma once
#ifndef _LR_CONSTRUCTOR_TABLE_BUILDER_
#define _LR_CONSTRUCTOR_TABLE_BUILDER_
#include <iostream>
#include <vector>
#include <fstream>
#include <stack>
#include "Symbol.h"
#include "LRContext.h"
#include "ProducItem.h"

using namespace std;

class ProducItemGroup
{
private:
	//identical和重载的==所用到的判断对等函数，根据传入的函数指针判断LR构造项目集中的元素是否相等
	bool equals(const ProducItemGroup& g, bool(*fun)(ProducItem*, ProducItem*)) const;
public:
	//构造LR表过程中的项目集
	vector<ProducItem*> items;
	//该状态经过一个符号可到达的状态
	map<Symbol, ProducItemGroup*> next_group_nos;
	~ProducItemGroup();
	//重载相等判断，不精确展望符
	bool operator==(const ProducItemGroup& g) const; 
	//相等判断，精确展望符
	bool identical(const ProducItemGroup& g) const;
	//合并展望符集
	void merge(const ProducItemGroup& g);
	//清理项目集，只保留LALR核
	void clear_non_core();
	//在vector中查找当前对象
	vector<ProducItemGroup*>::iterator find_from_vector(vector<ProducItemGroup*>& v);
};

class LRTableBuilder
{
private:
	//该程序运行信息
	LRContext* context;
	//构造过程中的状态集
	vector<ProducItemGroup*> groups;
	//生成扩展产生式
	Produc build_expand_produc();
	//处理当前进度后第一位符号，当当前进度后第一位符号为非终结符时将继续考虑他的产生式
	void handle(ProducItemGroup* group);
	//根据项目集中的项目生成下一步状态
	void next(ProducItemGroup* group);
	//根据传入的点后第二位符号设置展望符
	set<string>& set_prospects(Symbol symbol, set<string>& prospects);
	//根据最终状态集生成LR表
	void generate_table(vector<vector<string>>& action_table, vector<vector<string>>& goto_table);
	//根据终结符获取action表的列编号
	size_t get_action_no(string str);
	//根据非终结符获取goto表的列编号
	size_t get_goto_no(string str);
	//输出表格到流
	ostream& out_table(ostream& out, const vector<vector<string>>& action_table, const vector<vector<string>>& goto_table);
	//设置分析表表格单元
	void set_table_node(vector<vector<string>>& table, size_t row, size_t col, string str);
	//尝试利用LALR简化LR状态集
	void try_lalr();
	//测试打印输出状态集
	void test();

public:
	LRTableBuilder(LRContext* context);
	~LRTableBuilder();
	//开始构造
	void start(const string& outfile);
};

#endif // !_LALR_CONSTRUCTOR_TABLE_BUILDER_