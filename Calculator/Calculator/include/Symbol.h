#pragma once
#ifndef _LR_CONSTRUCTOR_SYMBOL_
#define _LR_CONSTRUCTOR_SYMBOL_
#include <iostream>
#include <vector>

using namespace std;
class Symbol
{
private:
	//符号类型
	string type;
	void *value;
public:
	//空串字符
	static const string EPSILON;
	//结束符
	static const string END;
	Symbol();
	Symbol(string type);
	Symbol(string type, void* value);
	~Symbol();
	string getType() const;

	void* getValue() const;

	Symbol& setValue(void *value);
	static Symbol get_end_symbol();
	bool operator==(const Symbol& symbol) const;
	bool operator<(const Symbol& symbol) const;
	bool operator==(const string& symbol) const;
	//根据字符串生成符号类
	static vector<Symbol> str_to_symbols(const vector<string>& symbolstrs,
		vector<Symbol>& symbols, const string& str);
};

#endif // !_LALR_CONSTRUCTOR_SYMBOL_