#pragma once
#ifndef _LR_CONSTRUCTOR_PRODUC_ITEM_
#define _LR_CONSTRUCTOR_PRODUC_ITEM_
#include <iostream>
#include <vector>
#include <set>
#include "LrContext.h"
#include "Produc.h"

using namespace std;

class ProducItem
{
private:
	size_t produc_no;
	Produc* produc;
	LRContext* context;
	size_t cursor;
	set<string> prospects;
public:
	ProducItem(size_t produc_no, LRContext* context);

	bool operator==(const ProducItem& item);
};

#endif