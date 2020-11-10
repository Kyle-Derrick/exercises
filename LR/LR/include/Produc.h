#ifndef _PRODUC_CLASS_
#define _PRODUC_CLASS_

#include <iostream>
#include <string>

using namespace std;

class Produc
{
private:
	string left;
	string symbol;
	string right;
public:
	Produc();
	Produc(string left, string symbol, string right);
	string toString();
};

#endif