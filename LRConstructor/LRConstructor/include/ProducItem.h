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
	//该项目对应的产生式编号
	size_t produc_no;
public:
	//该项目对应的产生式
	Produc produc;
	//该项目当前进度位置
	size_t cursor;
	//该项目的展望符
	set<string> prospects;
	ProducItem(size_t produc_no, Produc p);
	size_t get_no();
	//返回该项目是否为规约项目
	bool statute();
	//获取当前进度后第二位符号，若无则为$
	Symbol next_prospects();
	//判断相等，精确到展望符
	bool identical(const ProducItem& item)const;
	//判断相等，不精确到展望符
	bool operator==(const ProducItem& item)const;
	ProducItem& operator=(const ProducItem& item);
	//克隆当前项目，并进度+1
	ProducItem* clone_puls();
	//在vector中查找当前对象
	vector<ProducItem*>::iterator find_from_vector(vector<ProducItem*>& v);
};

#endif