#include "..\include\Produc.h"

Produc::Produc()
{
}

Produc::Produc(string left, string symbol, string right)
{
	this->left = left;
	this->symbol = symbol;
	this->right = right;
}

string Produc::toString()
{
	return this->left+this->symbol+this->right;
}
