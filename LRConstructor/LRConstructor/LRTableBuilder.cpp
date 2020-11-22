#include "include/LRTableBuilder.h"

bool ProducItemGroup::equals(const ProducItemGroup& g, bool(*fun)(ProducItem*, ProducItem*)) const
{
	if (this->items.size() != g.items.size())
	{
		return false;
	}
	for (size_t i = 0; i < this->items.size(); i++)
	{
		ProducItem* tmp = this->items[i];
		if (find_if(g.items.begin(), g.items.end(), [tmp,fun](ProducItem* value) {
			//return tmp->identical(*value);
			//return *tmp == *value;
			return fun(tmp, value);
			}) == g.items.end())
		{
			return false;
		}
	}
	return true;
}

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
	return this->equals(g, [] (ProducItem* v1, ProducItem* v2) {
		return *v1 == *v2;
	});
}

bool ProducItemGroup::identical(const ProducItemGroup& g) const
{
	return this->equals(g, [](ProducItem* v1, ProducItem* v2) {
		return v1->identical(*v2);
		});
}

void ProducItemGroup::merge_and_clear(const ProducItemGroup& g)
{
	for (size_t i = 0; i < this->items.size(); i++)
	{
		ProducItem* tmp = this->items[i];
		if (tmp->cursor == 0 && tmp->get_no()!=0)
		{
			this->items.erase(this->items.begin()+i);
			i--;
		}
		else
		{
			auto iter = find_if(g.items.begin(), g.items.end(), [tmp](ProducItem* value) {
				return *tmp == *value;
				});
			if (iter != g.items.end())
			{
				tmp->prospects.insert((*iter)->prospects.begin(), (*iter)->prospects.end());
			}
		}
	}
}

vector<ProducItemGroup*>::iterator ProducItemGroup::find_from_vector(vector<ProducItemGroup*>& v)
{
	ProducItemGroup* tmp = this;
	return find_if(v.begin(), v.end(), [tmp](ProducItemGroup* value) {
		return tmp->identical(*value);
		});
}

LRTableBuilder::LRTableBuilder(LRContext* context)
{
	this->context = context;
}

void LRTableBuilder::start(const string& outfile)
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

	for (size_t i = 0; i < groups.size(); i++)
	//for (ProducItemGroup* g : groups)
	{
		ProducItemGroup* g = groups[i];

		next(g);

	}

	vector<ProducItemGroup*> tmp = groups;
	cout << "开始尝试LALR..." << endl;
	try_lalr();

	//生成分析表
	vector<vector<string>> action_table;
	vector<vector<string>> goto_table;
	try
	{
		generate_table(action_table, goto_table);
	}
	catch (const string& estr)
	{
		cerr << "尝试转化为LALR时出错: " << estr << endl;
		groups = tmp;
		generate_table(action_table, goto_table);
	}

	//写入文件
	ofstream fout(outfile);
	if (!fout.is_open())
	{
		cerr << "打开输出文件时失败：" << endl;
		exit(EXIT_FAILURE);
	}
	context->output(fout);
	out_table(fout, action_table, goto_table);
	fout.close();

	context->output(cout);
	out_table(cout, action_table, goto_table);

	test();
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
				//set_prospects(item->next_prospects(), (*iter)->prospects);
				delete tmp_item;
				tmp_item = *iter;
			}
			else
			{
				//tmp_item->prospects.insert(item->prospects.begin(), item->prospects.end());
				//set_prospects(item->next_prospects(), tmp_item->prospects);
				group->items.push_back(tmp_item);
			}
			Symbol p_symbol = item->next_prospects();
			if (p_symbol == Symbol::get_end_symbol())
			{
				tmp_item->prospects.insert(item->prospects.begin(), item->prospects.end());
			}
			else
			{
				set_prospects(item->next_prospects(), tmp_item->prospects);
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
		auto iter = group->next_group_nos.find(symbol);
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
			group->next_group_nos[symbol] = tmp_group;
			groups.push_back(tmp_group);
		}
	}
	for (auto& kvpair : group->next_group_nos)
	{
		ProducItemGroup* tmp_group = kvpair.second;
		handle(tmp_group);
		auto tmp_iter = find_if(groups.begin(), groups.end(), [tmp_group](ProducItemGroup* value) {
			return tmp_group->identical(*value) && tmp_group != value;
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
		v.resize(action_width+1);
	}
	for (vector<string>& v : goto_table)
	{
		v.resize(goto_width);
	}

	stack<ProducItemGroup*> tmp_stack;
	tmp_stack.push(groups[0]);
	set<size_t> finish_status;
	while (!tmp_stack.empty())
	{
		ProducItemGroup* group = tmp_stack.top();
		tmp_stack.pop();
		size_t last_no = group->find_from_vector(groups) - groups.begin();
		for (const auto& kvpair : group->next_group_nos)
		{
			ProducItemGroup* item_group = kvpair.second;
			Symbol tmp_symbol = kvpair.first;
			//获取状态编号
			size_t now_no = item_group->find_from_vector(groups) - groups.begin();
			for (ProducItem* item : item_group->items)
			{
				if (item->statute())
				{
					if (item->produc == context->get_produc(0))
					{
						//action_table[now_no][action_width] = "acc";
						set_table_node(action_table, now_no, action_width, "acc");
					}
					else {
						for (string p_symbol : item->prospects)
						{
							//action_table[now_no][get_action_no(p_symbol)] = "r" + to_string(item->get_no());
							set_table_node(action_table, now_no, get_action_no(p_symbol), "r" + to_string(item->get_no()));
						}
					}
				}
				if (tmp_symbol.getType() == SymbolType::NON_TERMINATOR)
				{
					if (!(item->produc.getLeft() == context->get_produc(0).getLeft()))
					{
						//goto_table[last_no][get_goto_no(tmp_symbol.getStr())] = to_string(now_no);
						set_table_node(goto_table, last_no, get_goto_no(tmp_symbol.getStr()), to_string(now_no));
					}
				}
				else if (item->cursor != 0)
				{
					//action_table[last_no][get_action_no(tmp_symbol.getStr())] = "s" + to_string(now_no);
					set_table_node(action_table, last_no, get_action_no(tmp_symbol.getStr()), "s" + to_string(now_no));
				}
			}
			if (finish_status.find(now_no) == finish_status.end())
			{
				tmp_stack.push(kvpair.second);
				finish_status.insert(now_no);
			}
		}
	}
}

size_t LRTableBuilder::get_action_no(string str)
{
	return find(context->terminators_source.begin(), context->terminators_source.end(), str) - context->terminators_source.begin();
}

size_t LRTableBuilder::get_goto_no(string str)
{
	return find(context->non_terminators_source.begin(), context->non_terminators_source.end(), str) - context->non_terminators_source.begin();
}

ostream& LRTableBuilder::out_table(ostream& out, const vector<vector<string>>& action_table, const vector<vector<string>>& goto_table)
{
	for (size_t i = 0; i < action_table.size(); i++)
	{
		string tmp;
		for (size_t j = 0; j < 2; j++)
		{
			for (string str : (j ? goto_table[i] : action_table[i]))
			{
				tmp.insert(tmp.end(), str.begin(), str.end());
				tmp.push_back(',');
			}
		}
		tmp.pop_back();
		out << tmp << endl;
	}

	return out;
}

void LRTableBuilder::set_table_node(vector<vector<string>>& table, size_t row, size_t col, string str)
{

	if (row >= table.size() || col >= table[row].size())
	{
		cerr << "存入表数据时超出表格大小！" << endl;
		exit(EXIT_FAILURE);
	}
	string& s = table[row][col];
	if (!s.empty() && s != str)
	{
		throw "存入表数据时单元格数据不唯一！";
		/*cerr << "存入表数据时单元格数据不唯一！" << endl;
		exit(EXIT_FAILURE);*/
	}
	s = str;
}

void LRTableBuilder::try_lalr()
{
	map<ProducItemGroup*, ProducItemGroup*> change_map;
	for (size_t i = 0; i < groups.size(); i++)
	{
		ProducItemGroup* group = groups[i];
		vector<ProducItemGroup*>::iterator iter;
		while (true)
		{
			iter = find_if(groups.begin() + i + 1, groups.end(), [group](ProducItemGroup* value) {
				return *value == *group;
				});
			if (iter != groups.end())
			{
				change_map[*iter] = group;
				group->merge_and_clear(**iter);
				groups.erase(iter);
			}
			else
			{
				break;
			}
		}

	}

	
	for (ProducItemGroup* group : groups)
	{
		for (pair<Symbol, ProducItemGroup*> kvpair : group->next_group_nos)
		{
			map<ProducItemGroup*, ProducItemGroup*>::iterator iter = change_map.find(kvpair.second);
			if (iter != change_map.end())
			{
				group->next_group_nos[kvpair.first] = (*iter).second;
			}
		}
	}
}

void LRTableBuilder::test()
{
	context->output(cout);

	for (ProducItemGroup* g : groups)
	{
		cout << "-----------------" << endl;
		for (ProducItem* i : g->items)
		{
			cout << i->produc.getStr();
			cout << ',' << i->cursor;
			for (string s : i->prospects)
			{
				cout << ',' << s;
			}
			cout << endl;
		}
	}
}