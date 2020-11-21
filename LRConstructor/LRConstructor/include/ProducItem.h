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
	Produc produc;
	size_t cursor;
	set<string> prospects;
	ProducItem(size_t produc_no, Produc p);
	size_t get_no();
	bool statute();
	Symbol next_prospects();
	bool identical(const ProducItem& item)const;
	bool operator==(const ProducItem& item)const;
	ProducItem& operator=(const ProducItem& item);
	ProducItem* clone_puls();
};

#endif