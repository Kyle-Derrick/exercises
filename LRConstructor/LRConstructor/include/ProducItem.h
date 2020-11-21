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
public:
	const Produc* produc;
	size_t cursor;
	set<string> prospects;
	ProducItem(size_t produc_no, const Produc* p);
	size_t get_no();
	bool statute();
	bool operator==(const ProducItem& item)const;
};

#endif