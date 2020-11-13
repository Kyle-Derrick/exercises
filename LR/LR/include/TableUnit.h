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
	//���Ԫ����
	UnitType type;
	//���ֵ
	size_t value;
public:
	TableUnit(UnitType type, size_t value);
	//�����ַ���Ϊ������action���Ԫ
	static TableUnit& identify(string str);
	UnitType getType();
	char getTypeStr();
	size_t getValue();
};

#endif