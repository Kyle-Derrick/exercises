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
	vector<string> terminators;
	vector<string> non_terminators;
	vector<Produc> producs;
	map<string, set<size_t>> produc_map;
	string arrow;
	Symbol start_symbol;
	static void produc_analyze(
		const string& line, const string& arrow, const string& delim, const vector<string>& terminators,
		const vector<string>& non_terminators, vector<Produc>& producs,
		map<string, set<size_t>>& produc_map);
public:
	vector<string> terminators_source;
	vector<string> non_terminators_source;
	static LRContext init(string fpath);
	void test();
	Produc get_produc(size_t no);
	string get_arrow();
	Symbol& get_start_symbol();
	void set_expand_produc(const Produc& p);
	set<size_t>* get_produc_nos(const string& symbol);
	bool non_terminators_exist(const string& symbol);
	ostream& output(ostream& out);
};

#endif