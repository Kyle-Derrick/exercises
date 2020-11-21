#include "include/Symbol.h"

const string Symbol::EPSILON("ε");

Symbol::Symbol()
{
	this->str = EPSILON;
	this->type = SymbolType::TERMINATOR;
}

Symbol::Symbol(string str, SymbolType type)
{
	this->str = str;
	this->type = type;
}

string Symbol::getStr() const
{
	return this->str;
}

SymbolType Symbol::getType() const
{
	return this->type;
}

vector<Symbol> Symbol::str_to_symbols(const vector<string>& terminators,
	const vector<string>& non_terminators,
	vector<Symbol>& symbols, const string& str)
{
	size_t index = 0;
	while (true)
	{
		size_t tmp = index;
		const vector<string>* tmplist = &terminators;
		SymbolType type = SymbolType::TERMINATOR;
		for (size_t i = 0; i < 2; i++)
		{
			for (string symbol : *tmplist)
			{
				size_t len = symbol.length();
				if (!str.compare(index, len, symbol))
				{
					symbols.push_back(Symbol(str.substr(index, len), type));
					index += len;
					i = 2;
					break;
				}
			}
			tmplist = &non_terminators;
			type = SymbolType::NON_TERMINATOR;
		}

		if (tmp == index)
		{
			throw ("解析产生式时出现未知符号:" + str.substr(index));
		}
		else if (index >= str.length())
		{
			break;
		}
	}
	return symbols;
}

bool Symbol::operator==(const Symbol& symbol) const
{
	if (this->str == symbol.str && this->type == symbol.type)
	{
		return true;
	}
	return false;
}

bool Symbol::operator==(const string& symbol) const
{
	if (this->str == symbol)
	{
		return true;
	}
	return false;
}