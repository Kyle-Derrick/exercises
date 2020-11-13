#pragma once
#ifndef _TABLE_UNIT_H_
#define _TABLE_UNIT_H_

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

enum class UnitType
{
	SHIFT, REDUCE, ERROR, ACC
};

class TableUnit
{
private:
	//表格单元类型
	UnitType type;
	//表格值
	size_t value;
public:
	TableUnit(UnitType type, size_t value);
	//解析字符串为分析表action表格单元
	static TableUnit& identify(string str);
	UnitType getType();
	char getTypeStr();
	size_t getValue();
};

#endif