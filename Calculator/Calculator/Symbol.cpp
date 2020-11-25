#include "include/Symbol.h"

const string Symbol::EPSILON("ε");
const string Symbol::END("$");

Symbol::Symbol():Symbol(EPSILON)
{}

Symbol::Symbol(string type)
{
	this->type = type;
	this->value = nullptr;
}

Symbol::Symbol(string type, void *value) :Symbol(type)
{
	this->value = value;
}

Symbol::~Symbol()
{
	if (this->value)
	{
		//delete this->value;
	}
}

void* Symbol::getValue() const
{
	return this->value;
}

string Symbol::getType() const
{
	return this->type;
}

Symbol Symbol::get_end_symbol()
{
	return Symbol(END);
}

Symbol& Symbol::setValue(void* value)
{
	this->value = value;
	return *this;
}

vector<Symbol> Symbol::str_to_symbols(const vector<string>& symbolstrs,
	vector<Symbol>& symbols, const string& str)
{
	size_t index = 0;
	while (true)
	{
		size_t tmp = index;
		for (string symbol : symbolstrs)
		{
			size_t len = symbol.length();
			if (!str.compare(index, len, symbol))
			{
				symbols.push_back(Symbol(str.substr(index, len)));
				index += len;
				break;
			}
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
	if (this->type == symbol.type)
	{
		return true;
	}
	return false;
}

bool Symbol::operator<(const Symbol& symbol) const
{
	return this->type < symbol.type;
}

bool Symbol::operator==(const string& symbol) const
{
	if (this->type == symbol)
	{
		return true;
	}
	return false;
}