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
	bool equals(const ProducItemGroup& g, bool(*fun)(ProducItem*, ProducItem*)) const;
public:
	vector<ProducItem*> items;
	map<Symbol, ProducItemGroup*> next_group_nos;
	~ProducItemGroup();
	bool operator==(const ProducItemGroup& g) const; 
		bool identical(const ProducItemGroup& g) const;
	void merge_and_clear(const ProducItemGroup& g);
	vector<ProducItemGroup*>::iterator find_from_vector(vector<ProducItemGroup*>& v);
};

class LRTableBuilder
{
private:
	LRContext* context;
	vector<ProducItemGroup*> groups;
	Produc build_expand_produc();
	void handle(ProducItemGroup* group);
	void next(ProducItemGroup* group);
	set<string>& set_prospects(Symbol symbol, set<string>& prospects);
	void generate_table(vector<vector<string>>& action_table, vector<vector<string>>& goto_table);
	size_t get_action_no(string str);
	size_t get_goto_no(string str);
	ostream& out_table(ostream& out, const vector<vector<string>>& action_table, const vector<vector<string>>& goto_table);
	void set_table_node(vector<vector<string>>& table, size_t row, size_t col, string str);
	void try_lalr();
	void test();

public:
	LRTableBuilder(LRContext* context);
	~LRTableBuilder();
	void start(const string& outfile);
};

#endif // !_LALR_CONSTRUCTOR_TABLE_BUILDER_