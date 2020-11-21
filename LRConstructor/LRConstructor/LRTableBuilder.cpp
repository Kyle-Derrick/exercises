#include "include/LRTableBuilder.h"

ProducItemGroup::~ProducItemGroup()
{
	while (!items.empty())
	{
		delete items.back();
		items.pop_back();
	}
}

bool ProducItemGroup::operator==(const ProducItemGroup& g) const
{
	if (this->items.size() != g.items.size())
	{
		return false;
	}
	for (size_t i = 0; i < this->items.size(); i++)
	{
		ProducItem* tmp = this->items[i];
		if (find_if(g.items.begin(), g.items.end(), [tmp](ProducItem* value) {
				return tmp->identical(*value);
				//return *tmp == *value;
			}) == g.items.end())
		{
			return false;
		}
	}
	return true;
}

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
		vector<ProducItemGroup*>().swap(groups);
	}

	//构造过程初态
	ProducItemGroup* group = new ProducItemGroup();
	ProducItem* expand_item = new ProducItem(0, context->get_produc(0));
	expand_item->prospects.insert(Symbol::END);
	group->items.push_back(expand_item);
	groups.push_back(group);
	handle(group);

	//for (ProducItem* item:group->items)
	//{
	//	cout << "--------" << endl;
	//	cout << item->get_no() << endl;
	//	for (string s : item->prospects)
	//	{
	//		cout << s << endl;
	//	}
	//}

	for (size_t i = 0; i < groups.size(); i++)
	//for (ProducItemGroup* g : groups)
	{
		ProducItemGroup* g = groups[i];

		next(g);

	}

	//生成分析表

	//写入文件
	//ofstream fout("lr.table");
	//if (!fout.is_open())
	//{
	//	cerr << "打开输出文件时失败：" << endl;
	//	exit(EXIT_FAILURE);
	//}
	//context->output(fout);
	context->output(cout);


	cout << groups.size() << endl;
	for (ProducItemGroup* g : groups)
	{
		cout << "----------------" << endl;
		for (ProducItem* p : g->items)
		{
			cout << p->produc.getStr() << ',' << p->cursor << ',' << p->produc.getRight().size() << endl;
		}
	}
}

LRTableBuilder::~LRTableBuilder()
{
	while (!groups.empty())
	{
		delete groups.back();
		groups.pop_back();
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

void LRTableBuilder::handle(ProducItemGroup* group)
{
	for (size_t i = 0; i < group->items.size(); i++)
	{
		ProducItem* item = group->items[i];
		if (item->statute())
		{
			continue;
		}
		Symbol sy = item->produc.getRight().at(item->cursor);
		if (sy.getType() == SymbolType::TERMINATOR)
		{
			continue;
		}
		set<size_t>* producs = context->get_produc_nos(sy.getStr());
		for (size_t no : *producs)
		{
			ProducItem* tmp_item = new ProducItem(no, context->get_produc(no));
			vector<ProducItem*>::iterator iter = find_if(group->items.begin(), group->items.end(), [tmp_item](ProducItem* value) {
					return *tmp_item == *value; 
				});
			if (iter != group->items.end())
			{
				set_prospects(item->next_prospects(), (*iter)->prospects);
				delete tmp_item;
			}
			else
			{
				tmp_item->prospects.insert(item->prospects.begin(), item->prospects.end());
				set_prospects(item->next_prospects(), tmp_item->prospects);
				group->items.push_back(tmp_item);
			}
		}
	}
}

void LRTableBuilder::next(ProducItemGroup* group)
{
	for (ProducItem* item : group->items)
	{
		if (item->statute())
		{
			continue;
		}
		Symbol symbol = item->produc.getRight().at(item->cursor);
		ProducItemGroup* tmp_group;
		auto iter = group->next_group_nos.find(symbol.getStr());
		bool isnew = true;
		if (iter != group->next_group_nos.end())
		{
			isnew = false;
			tmp_group = (*iter).second;
		}
		else
		{
			tmp_group = new ProducItemGroup();
		}
		ProducItem* tmp_item = item->clone_puls();
		tmp_group->items.push_back(tmp_item);
		if (isnew)
		{
			group->next_group_nos[symbol.getStr()] = tmp_group;
			groups.push_back(tmp_group);
		}
	}
	for (auto& kvpair : group->next_group_nos)
	{
		ProducItemGroup* tmp_group = kvpair.second;
		handle(tmp_group);

		auto tmp_iter = find_if(groups.begin(), groups.end(), [tmp_group](ProducItemGroup* value) {
			return *tmp_group == *value && tmp_group != value;
			});
		if (tmp_iter != groups.end())
		{
			auto tmp = find(groups.begin(), groups.end(), tmp_group);
			groups.erase(tmp);
			
			delete tmp_group;
			kvpair.second = *tmp_iter;
		}
	}
}

set<string>& LRTableBuilder::set_prospects(Symbol symbol, set<string>& prospects)
{
	stack<Symbol> tmp_stack;
	tmp_stack.push(symbol);

	while (!tmp_stack.empty())
	{
		Symbol tmp = tmp_stack.top();
		tmp_stack.pop();
		if (tmp.getType() == SymbolType::NON_TERMINATOR)
		{
			set<size_t>* tmp_set = context->get_produc_nos(tmp.getStr());
			for (size_t i : *tmp_set)
			{
				Produc tmp_p = context->get_produc(i);
				Symbol tmp_s = *tmp_p.getRight().begin();
				if (!(tmp_s == tmp))
				{
					tmp_stack.push(tmp_s);
				}
			}
		}
		else
		{
			prospects.insert(tmp.getStr());
		}
	}
	return prospects;
}

void LRTableBuilder::generate_table(vector<vector<string>>& action_table, vector<vector<string>>& goto_table)
{
	size_t action_width = context->terminators_source.size();
	size_t goto_width = context->non_terminators_source.size();
	size_t col_size = groups.size();
	//初始化表格长宽
	action_table.resize(col_size);
	goto_table.resize(col_size);
	for (vector<string>& v : action_table)
	{
		v.resize(action_width);
	}
	for (vector<string>& v : goto_table)
	{
		v.resize(goto_width);
	}

	stack<size_t> tmp_stack;
	tmp_stack.push(0);
	size_t last_status = 0;
	while (!tmp_stack.empty())
	{
		ProducItemGroup* group = groups[tmp_stack.top()];
		for (const auto& kvpair : group->next_group_nos)
		{
			ProducItemGroup* item_group = kvpair.second;

		}
	}
}
