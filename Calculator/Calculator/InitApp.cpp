#include "include/InitApp.h"

Functions InitApp::funs = Functions();
Reduces InitApp::reduces = Reduces();

/*
E→E+T
E→E-T
E→T
T→T*T'
T→T/T'
T→T^T'
T→T%T'
T→T'
T'→-T'
T'→F!
T'→F
F→fun(G)
F→F'
F→num
F'→(E)
F'→|E|
G→G,E
G→E
*/
Reduces& InitApp::load_reduces(Reduces& rs)
{
	rs["E→E+T"] = [](vector<Symbol> symbols) -> Symbol {
		double* v1 = (double*)symbols[0].getValue();
		double* v2 = (double*)symbols[2].getValue();
		*v1 = *v1 + *v2;
		Symbol symbol("E", v1);
		delete v2;
		return symbol;
	};
	rs["E→E-T"] = [](vector<Symbol> symbols) -> Symbol {
		double* v1 = (double*)symbols[0].getValue();
		double* v2 = (double*)symbols[2].getValue();
		*v1 = *v1 - *v2;
		Symbol symbol("E", v1);
		delete v2;
		return symbol;
	};
	rs["E→T"] = [](vector<Symbol> symbols) -> Symbol {
		Symbol symbol("E", symbols[0].getValue());
		return symbol;
	};
	rs["T→T*T'"] = [](vector<Symbol> symbols) -> Symbol {
		double* v1 = (double*)symbols[0].getValue();
		double* v2 = (double*)symbols[2].getValue();
		*v1 = *v1 * *v2;
		Symbol symbol("T", v1);
		delete v2;
		return symbol;
	};
	rs["T→T/T'"] = [](vector<Symbol> symbols) -> Symbol {
		double* v1 = (double*)symbols[0].getValue();
		double* v2 = (double*)symbols[2].getValue();
		*v1 = *v1 / *v2;
		Symbol symbol("T", v1);
		delete v2;
		return symbol;
	};
	rs["T→T^T'"] = [](vector<Symbol> symbols) -> Symbol {
		double* v1 = (double*)symbols[0].getValue();
		double* v2 = (double*)symbols[2].getValue();
		*v1 = pow(*v1, *v2);
		Symbol symbol("T", v1);
		delete v2;
		return symbol;
	};
	rs["T→T%T'"] = [](vector<Symbol> symbols) -> Symbol {
		double* v1 = (double*)symbols[0].getValue();
		double* v2 = (double*)symbols[2].getValue();
		*v1 = fmod(*v1, *v2);
		Symbol symbol("T", v1);
		delete v2;
		return symbol;
	};
	rs["T→T'"] = [](vector<Symbol> symbols) -> Symbol {
		Symbol symbol("T", symbols[0].getValue());
		return symbol;
	};
	rs["T'→-T'"] = [](vector<Symbol> symbols) -> Symbol {
		double* v1 = (double*)symbols[1].getValue();
		*v1 = -*v1;
		Symbol symbol("T'", v1);
		return symbol;
	};
	rs["T'→F!"] = [](vector<Symbol> symbols) -> Symbol {
		double* v1 = (double*)symbols[0].getValue();
		double num = 1;
		size_t v = (int)abs(*v1);
		for (size_t i = 2; i <= v; i++)
		{
			num *= i;
		}
		Symbol symbol("T'", new double(num));
		delete v1;
		return symbol;
	};
	rs["T'→F"] = [](vector<Symbol> symbols) -> Symbol {
		Symbol symbol("T'", symbols[0].getValue());
		return symbol;
	};
	rs["F→fun(G)"] = [](vector<Symbol> symbols) -> Symbol {
		string* v1 = (string*)symbols[0].getValue();
		vector<double>* v2 = (vector<double>*)symbols[2].getValue();
		double(*fun)(vector<double>) = funs[*v1];
		if (!fun)
		{
			throw "没有此函数: " + *v1;
		}
		Symbol symbol("F", new double(fun(*v2)));
		delete v1;
		delete v2;
		return symbol;
	};
	rs["F→F'"] = [](vector<Symbol> symbols) -> Symbol {
		Symbol symbol("F", symbols[0].getValue());
		return symbol;
	};
	rs["F→num"] = [](vector<Symbol> symbols) -> Symbol {
		string* v1 = (string*)symbols[0].getValue();
		Symbol symbol("F", new double(atof(v1->c_str())));
		delete v1;
		return symbol;
	};
	rs["F'→(E)"] = [](vector<Symbol> symbols) -> Symbol {
		Symbol symbol("F'", symbols[1].getValue());
		return symbol;
	};
	rs["F'→|E|"] = [](vector<Symbol> symbols) -> Symbol {
		double* v1 = (double*)symbols[1].getValue();
		*v1 = abs(*v1);
		Symbol symbol("F'", v1);
		return symbol;
	};
	rs["G→G,E"] = [](vector<Symbol> symbols) -> Symbol {
		vector<double>* v1 = (vector<double>*)symbols[0].getValue();
		double* v2 = (double*)symbols[2].getValue();
		v1->push_back(*v2);
		delete v2;
		Symbol symbol("G", v1);
		return symbol;
	};
	rs["G→E"] = [](vector<Symbol> symbols) -> Symbol {
		vector<double>* v = new vector<double>();
		double* v1 = (double*)symbols[0].getValue();
		v->push_back(*v1);
		delete v1;
		Symbol symbol("G", v);
		return symbol;
	};
	return rs;
}

void InitApp::init()
{
	load_funs(funs);
	load_reduces(reduces);
}


void InitApp::check_arg(string fname, size_t args_size, size_t need_size)
{
	if (args_size != need_size)
	{
		cerr << fname << "函数参数不正确，需要" << need_size << "个参数" << endl;
		exit(EXIT_FAILURE);
	}
}

Functions& InitApp::load_funs(Functions& fs)
{
	fs["sin"] = [](vector<double> args) -> double {
		check_arg("sin", args.size(), 1);
		return sin(args[0]);
	};
	fs["cos"] = [](vector<double> args) -> double {
		check_arg("cos", args.size(), 1);
		return cos(args[0]);
	};
	fs["tan"] = [](vector<double> args) -> double {
		check_arg("tan", args.size(), 1);
		return tan(args[0]);
	};
	fs["ceil"] = [](vector<double> args) -> double {
		check_arg("ceil", args.size(), 1);
		return ceil(args[0]);
	};
	fs["floor"] = [](vector<double> args) -> double {
		check_arg("floor", args.size(), 1);
		return floor(args[0]);
	};
	fs["asin"] = [](vector<double> args) -> double {
		check_arg("asin", args.size(), 1);
		return asin(args[0]);
	};
	fs["acos"] = [](vector<double> args) -> double {
		check_arg("acos", args.size(), 1);
		return acos(args[0]);
	};
	fs["atan"] = [](vector<double> args) -> double {
		check_arg("atan", args.size(), 1);
		return atan(args[0]);
	};
	fs["sinh"] = [](vector<double> args) -> double {
		check_arg("sinh", args.size(), 1);
		return sinh(args[0]);
	};
	fs["cosh"] = [](vector<double> args) -> double {
		check_arg("cosh", args.size(), 1);
		return cosh(args[0]);
	};
	fs["tanh"] = [](vector<double> args) -> double {
		check_arg("tanh", args.size(), 1);
		return tanh(args[0]);
	};
	fs["ln"] = [](vector<double> args) -> double {
		check_arg("ln", args.size(), 1);
		return log(args[0]);
	};
	fs["log"] = [](vector<double> args) -> double {
		if (args.size() == 1)
		{
			return log10(args[0]);
		}
		if (args.size() == 2)
		{
			return log(args[0]) / log(args[1]);
		}
		cerr << "log函数参数不正确，需要1或2个参数" << endl;
		exit(EXIT_FAILURE);
	};
	return fs;
}