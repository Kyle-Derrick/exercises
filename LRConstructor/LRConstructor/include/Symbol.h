#pragma once
#ifndef _LR_CONSTRUCTOR_SYMBOL_
#define _LR_CONSTRUCTOR_SYMBOL_
#include <iostream>
#include <vector>

enum class SymbolType
{
	TERMINATOR, NON_TERMINATOR
};

using namespace std;
class Symbol
{
private:
	string str;
	SymbolType type;
public:
	Symbol();
	Symbol(string str, SymbolType type);
	string getStr();
	SymbolType getType();
	bool operator==(const Symbol& symbol);
	bool operator==(const string& symbol);
	static vector<Symbol> str_to_symbols(const vector<string>& terminators,
		const vector<string>& non_terminators,
		vector<Symbol>& symbols, const string& str);
};

#endif // !_LALR_CONSTRUCTOR_SYMBOL_