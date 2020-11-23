#pragma once
#ifndef _LR_CONSTRUCTOR_SYMBOL_
#define _LR_CONSTRUCTOR_SYMBOL_
#include <iostream>
#include <vector>

enum class SymbolType
{
	//ÖÕ½á·û
	TERMINATOR, 
	//·ÇÖÕ½á·û
	NON_TERMINATOR
};

using namespace std;
class Symbol
{
private:
	//·ûºÅ×Ö·û´®
	string str;
	//·ûºÅÀàÐÍ
	SymbolType type;
public:
	//¿Õ´®×Ö·û
	static const string EPSILON;
	//½áÊø·û
	static const string END;
	Symbol();
	Symbol(string str, SymbolType type);
	string getStr() const;

	SymbolType getType() const;
	static Symbol get_end_symbol();
	bool operator==(const Symbol& symbol) const;
	bool operator<(const Symbol& symbol) const;
	bool operator==(const string& symbol) const;
	//¸ù¾Ý×Ö·û´®Éú³É·ûºÅÀà
	static vector<Symbol> str_to_symbols(const vector<string>& terminators,
		const vector<string>& non_terminators,
		vector<Symbol>& symbols, const string& str);
};

#endif // !_LALR_CONSTRUCTOR_SYMBOL_