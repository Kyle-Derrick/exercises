#include "include/ProducItem.h"

ProducItem::ProducItem(size_t produc_no, const Produc* p)
{
	this->produc_no = produc_no;
	this->cursor = 0;
	if (p == nullptr)
	{
		cerr << "ProducItem传入产生式不能为空，产生式编号: " << produc_no << endl;
		exit(EXIT_FAILURE);
	}
	this->produc = p;
}

size_t ProducItem::get_no()
{
	return this->produc_no;
}

bool ProducItem::statute()
{
	return this->cursor >= this->produc->getRight().size();
}

bool ProducItem::operator==(const ProducItem& item) const
{
	if (produc_no == item.produc_no && produc == item.produc && cursor == item.cursor)
	{
		return true;
	}
	return false;
}
