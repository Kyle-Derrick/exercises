#include "include/ProducItem.h"

ProducItem::ProducItem(size_t produc_no, LRContext* context)
{
	this->produc_no = produc_no;
	this->cursor = 0;
	this->produc = context->get_produc(produc_no);
	this->context = context;
}

bool ProducItem::operator==(const ProducItem& item)
{
	if (produc_no == item.produc_no && produc == item.produc && cursor == item.cursor && prospects == item.prospects)
	{
		return true;
	}
	return false;
}
