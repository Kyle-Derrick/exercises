#pragma once
#ifndef _LALR_CONSTRUCTOR_SYMBOL_
#define _LALR_CONSTRUCTOR_SYMBOL_
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
	static vector<Symbol> str_to_symbols(const vector<string>& terminators,
		const vector<string>& non_terminators,
		vector<Symbol>& symbols, const string& str);
};

#endif // !_LALR_CONSTRUCTOR_SYMBOL_