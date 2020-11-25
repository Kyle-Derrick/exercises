#include "include\LRAnalyze.h"

void LRAnalyze::stack_push(Symbol symbol, size_t status)
{
	Node node;
	node.symbol = symbol;
	node.status = status;
	analyze_stack.push_back(node);
}

void LRAnalyze::stack_pop(size_t size)
{
	for (size_t i = 0; i < size; i++)
	{
		analyze_stack.pop_back();
	}
}

string LRAnalyze::reduce(TableUnit& unit, Symbol& symbol)
{
	Produc p = this->context.get_produc(unit.getValue()-1);
	vector<Symbol> tmp_symbols;
	for (size_t i = 0; i < p.getRight().size(); i++)
	{
		tmp_symbols.insert(tmp_symbols.begin(), this->analyze_stack.back().symbol);
		this->analyze_stack.pop_back();
	}
	Symbol new_top = InitApp::reduces[p.getStr()](tmp_symbols);
	//stack_pop(p.getRight().size());
	Node top = *--analyze_stack.end();
	//string str = p.getLeft().getType();
	size_t status = this->context.goto_search(new_top.getType(), top.status);
	stack_push(new_top, status);
	return p.getStr();
}

void LRAnalyze::destory()
{
	vector<Node>().swap(analyze_stack);
	vector<Symbol>().swap(symbols);
}

ostream& LRAnalyze::print_status(ostream& os)
{
	string tmp1;
	for (Node node : analyze_stack)
	{
		tmp1 += to_string(node.status) + "/" + node.symbol.getType() + ",";
	}
	tmp1.pop_back();
	os << setw(30) << left << tmp1;

	os << " | ";
	string tmp2;
	for (Symbol symbol : symbols)
	{
		tmp2 += symbol.getType();
	}
	os << setw(20) << right << tmp2;
	os << " | ";

	return os;
}

LRAnalyze::~LRAnalyze()
{
	destory();
}

LRAnalyze::LRAnalyze(AppContext &context)
{
	this->context = context;
}

LRAnalyze& LRAnalyze::init(string str)
{
	destory();
	this->str = str;
	vector<Symbol> strs;
	LexicalAnalysis::analysis(str, strs);
	//context.analyzestr(strs, str);
	strs.push_back(Symbol::get_end_symbol());
	this->symbols = strs;
	stack_push(Symbol::get_end_symbol(), 0);
	return *this;
}

void LRAnalyze::analyze()
{
	bool next = true;
	cout << "\n>> 分析句子开始...:\n" << endl;
	cout << left << setw(14) << "" << setw(16) << "栈" << " | ";
	cout << setw(8) << "" << setw(12) << "输入" << " | ";
	cout << setw(3) << "" << setw(22) << "分析动作";
	cout << endl;
	while (next)
	{
		Node top = *--analyze_stack.end();
		Symbol symbol = symbols.at(0);
		TableUnit unit = this->context.action_search(symbol.getType(), top.status);

		print_status(cout);
		string outstr;
		switch (unit.getType())
		{
			//移进
		case UnitType::SHIFT:
			stack_push(symbol, unit.getValue());
			symbols.erase(symbols.begin());
			outstr = "Shift " + to_string(unit.getValue());
			break;
			//规约
		case UnitType::REDUCE:
			outstr = "Reduce by " + reduce(unit, symbol);
			break;
			//错误
		case UnitType::ERROR:
			cerr << endl << context.get_error(unit.getValue()) << ": " << symbol.getType() << endl;
			return;
			//接受
		case UnitType::ACC:
			/*next = false;
			outstr = "Accept";*/
			cout << setw(25) << left << "Accept";
			cout << endl;
			cout << "\n> 计算结果: " << *(double*)top.symbol.getValue() << endl;
			return;
			//break;
		}

		cout << setw(25) << left << outstr;
		cout << endl;
	}
}
