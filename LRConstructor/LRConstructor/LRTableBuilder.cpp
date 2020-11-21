#include "include/LRTableBuilder.h"

LRTableBuilder::LRTableBuilder(LRContext* context)
{
	this->context = context;
}

void LRTableBuilder::start()
{
	Produc expand_produc = build_expand_produc();
	context->set_expand_produc(expand_produc);
	context->test();
	//清空容器
	if (groups.size() > 0)
	{
		vector<ProducItemGroup>().swap(groups);
	}

	//构造过程初态
	ProducItemGroup group;
	group.items.push_back(ProducItem(0, context->get_produc(0)));
	groups.push_back(group);
	handle(group);

	for (ProducItemGroup& g : groups)
	{
		next(g);
	}
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

void LRTableBuilder::handle(ProducItemGroup& group)
{
	for (ProducItem& item : group.items)
	{
		if (item.statute())
		{
			continue;
		}
		const Symbol sy = item.produc->getRight().at(item.cursor);
		if (sy.getType() == SymbolType::TERMINATOR)
		{
			continue;
		}
		set<size_t>* producs = context->get_produc_nos(sy.getStr());
		for (size_t no : *producs)
		{
			ProducItem tmp_item(no, context->get_produc(no));
			/*tmp_item.prospects.insert()
			group.items.push_back();*/
		}
	}
}

void LRTableBuilder::next(ProducItemGroup& group)
{
}
