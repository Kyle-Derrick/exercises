#pragma once
#ifndef _CALCULATOR_LEXICAL_ANALYSIS_H_
#define _CALCULATOR_LEXICAL_ANALYSIS_H_
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include "KyleBase.h"
#include "Symbol.h"

using namespace std;

class LexicalAnalysis
{
public:
	//进行词法解析，简单实现
	static vector<Symbol>& analysis(string str, vector<Symbol>& sequences);
};

#endif // !_CALCULATOR_LEXICAL_ANALYSIS_H_