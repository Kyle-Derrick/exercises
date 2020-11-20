#include "include/LRTableBuilder.h"

LRTableBuilder::LRTableBuilder(LRContext* context)
{
	this->context = context;
}

void LRTableBuilder::start()
{
	Produc expand_produc = build_expand_produc();
}

Produc LRTableBuilder::build_expand_produc()
{
	Symbol& start_symbol = context->get_start_symbol();
	string new_start_symbol_str = start_symbol.getStr();
	do
	{
		new_start_symbol_str.push_back('\'');
	} while (context->non_terminators_exist(new_start_symbol_str));
	string str = new_start_symbol_str + context->get_arrow() + start_symbol.getStr();
	Symbol left(new_start_symbol_str, SymbolType::NON_TERMINATOR);
	string arrow = context->get_arrow();
	vector<Symbol> right;
	right.push_back(start_symbol);
	return Produc(str, left, arrow, right);
}