#pragma once
#ifndef _LALR_CONSTRUCTOR_CONTEXT_
#define _LALR_CONSTRUCTOR_CONTEXT_
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <string>
#include <map>
#include "Produc.h"

using namespace std;
class LRContext
{
private:
	vector<string> terminators;
	vector<string> non_terminators;
	vector<Produc> producs;
	map<Symbol, vector<Symbol>> produc_map;
	string arrow;
	Symbol start_symbol;
	static void produc_analyze(
		const string& line, const string& arrow, const string& delim, const vector<string>& terminators,
		const vector<string>& non_terminators, vector<Produc>& producs,
		map<Symbol, vector<Produc>>& produc_map);
public:
	static LRContext init(string fpath);
	void test();
};

#endif