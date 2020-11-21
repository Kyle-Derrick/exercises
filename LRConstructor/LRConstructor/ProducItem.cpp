#include "include/ProducItem.h"

ProducItem::ProducItem(size_t produc_no, Produc p)
{
	this->produc_no = produc_no;
	this->cursor = 0;
	this->produc = p;
}

size_t ProducItem::get_no()
{
	return this->produc_no;
}

bool ProducItem::statute()
{
	return this->cursor >= this->produc.getRight().size();
}

Symbol ProducItem::next_prospects()
{
	vector<Symbol> tmp = produc.getRight();
	if (tmp.size() <= (cursor+1))
	{
		return Symbol::get_end_symbol();
	}
	return tmp.at(cursor+1);
}

bool ProducItem::identical(const ProducItem& item) const
{
	if (!(*this == item) || this->prospects.size() != item.prospects.size())
	{
		return false;
	}
	for (string str : this->prospects)
	{
		if (item.prospects.find(str) == item.prospects.end())
		{
			return false;
		}
	}
	return true;
}

bool ProducItem::operator==(const ProducItem& item) const
{
	if (produc_no == item.produc_no && produc == item.produc && cursor == item.cursor)
	{
		return true;
	}
	return false;
}

ProducItem& ProducItem::operator=(const ProducItem& item)
{
	this->cursor = item.cursor;
	this->produc = item.produc;
	this->prospects = item.prospects;
	this->produc_no = item.produc_no;
	return *this;
}

ProducItem* ProducItem::clone_puls()
{
	ProducItem* tmp_item = new ProducItem(this->produc_no, this->produc);
	tmp_item->cursor = this->cursor + 1;
	tmp_item->prospects.insert(this->prospects.begin(), this->prospects.end());
	return tmp_item;
}
