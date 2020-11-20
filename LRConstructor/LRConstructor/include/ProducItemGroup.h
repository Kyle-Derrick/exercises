#pragma once
#ifndef _LR_CONSTRUCTOR_PRODUC_ITEM_GROUP_
#define _LR_CONSTRUCTOR_PRODUC_ITEM_GROUP_
#include <iostream>
#include <set>
#include <map>
#include "ProducItem.h"

using namespace std;

class ProducItemGroup
{
private:
	set<ProducItem> items;
	map<string, set<size_t>> next_group_nos;

public:
	bool operator==(const ProducItemGroup& group);
};

#endif