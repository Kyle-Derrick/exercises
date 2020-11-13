#include "..\include\LRAnalyze.h"

void LRAnalyze::stack_push(string symbol, size_t status)
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

string LRAnalyze::reduce(TableUnit& unit, string& symbol)
{
	Produc p = this->context.get_produc(unit.getValue()-1);
	stack_pop(p.getRight().size());
	Node top = *--analyze_stack.end();
	string str = p.getLeft();
	size_t status = this->context.goto_search(str, top.status);
	stack_push(str, status);
	return p.getStr();
}

void LRAnalyze::destory()
{
	vector<Node>().swap(analyze_stack);
	vector<string>().swap(symbols);
}

ostream& LRAnalyze::print_status(ostream& os)
{
	string tmp1;
	for (Node node : analyze_stack)
	{
		tmp1 += to_string(node.status) + "/" + node.symbol + ",";
	}
	tmp1.pop_back();
	os << setw(30) << left << tmp1;

	os << " | ";
	string tmp2;
	for (string symbol : symbols)
	{
		tmp2 += symbol;
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
	vector<string> strs;
	context.analyzestr(strs, str);
	strs.push_back("$");
	this->symbols = strs;
	stack_push("$", 0);
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
		string symbol = symbols.at(0);
		TableUnit unit = this->context.action_search(symbol, top.status);

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
			cerr << endl << context.get_error(unit.getValue()) << ": " << symbol << endl;
			return;
			//接受
		case UnitType::ACC:
			next = false;
			outstr = "Accept";
			break;
		}

		cout << setw(25) << left << outstr;
		cout << endl;
	}
}
