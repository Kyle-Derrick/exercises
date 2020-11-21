#pragma once
#ifndef _LR_CONSTRUCTOR_TABLE_BUILDER_
#define _LR_CONSTRUCTOR_TABLE_BUILDER_
#include <iostream>
#include <vector>
#include <stack>
#include "Symbol.h"
#include "LRContext.h"
#include "ProducItem.h"

using namespace std;

class ProducItemGroup
{
public:
	vector<ProducItem> items;
	map<string, set<size_t>> next_group_nos;
};

class LRTableBuilder
{
private:
	LRContext* context;
	vector<ProducItemGroup> groups;
	Produc build_expand_produc();
	void handle(ProducItemGroup& group);
	void next(ProducItemGroup& group);

public:
	LRTableBuilder(LRContext* context);
	void start();
};

#endif // !_LALR_CONSTRUCTOR_TABLE_BUILDER_