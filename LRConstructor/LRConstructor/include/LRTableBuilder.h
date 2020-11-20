#pragma once
#ifndef _LR_CONSTRUCTOR_TABLE_BUILDER_
#define _LR_CONSTRUCTOR_TABLE_BUILDER_
#include <iostream>
#include "LRContext.h"

using namespace std;

class LRTableBuilder
{
private:
	LRContext* context;

public:
	LRTableBuilder(LRContext* context);
	void start();
	Produc build_expand_produc();
};

#endif // !_LALR_CONSTRUCTOR_TABLE_BUILDER_