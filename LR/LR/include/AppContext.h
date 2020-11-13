#pragma once
#ifndef _APPCONTEXT_H_
#define _APPCONTEXT_H_

#include <iostream>
#include <fstream>
#include<algorithm>
#include <string>
#include <vector>
#include "Produc.h"
#include "Base.h"

using namespace std;

class AppContext
{
private:
	vector<string> terminals;
	vector<string> nonterminals;
	vector<string> actions;
	vector<string> gotos;
	Produc **actionTable;
	Produc **gotoTable;
	string arrow;
	static int lineType(string line);
	static void analyzeSymbol(vector<string>& tmp, vector<string>& symbols, vector<string>& actions, vector<string> &gotos);
	static void analyzeProduc(vector<string>& tmp, vector<Produc>& pruducs, vector<string>& symbols);
	static size_t contentLineSize(ifstream& fs);
public:
	static AppContext& init(string f);
};

#endif // !_APPCONTEXT_H_