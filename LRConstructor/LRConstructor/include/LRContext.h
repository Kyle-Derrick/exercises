#pragma once
#ifndef _LALR_CONSTRUCTOR_CONTEXT_
#define _LALR_CONSTRUCTOR_CONTEXT_
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Produc.h"

using namespace std;
class LRContext
{
private:
	vector<string> terminators;
	vector<string> non_terminators;
	vector<Produc> producs;
	string arrow;
public:
	static LRContext init(string fpath);
	void test();
};

#endif