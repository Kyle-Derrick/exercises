#pragma once
#ifndef _LR_ANALYZE_H_
#define _LR_ANALYZE_H_

#include <iostream>
#include <stack>
#include "AppContext.h"

class LRAnalyze
{
private:
	AppContext context;
	//stack
public:
	LRAnalyze(AppContext context);
};

#endif