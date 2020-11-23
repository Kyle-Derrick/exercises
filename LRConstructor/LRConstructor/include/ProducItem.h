#pragma once
#ifndef _LR_CONSTRUCTOR_PRODUC_ITEM_
#define _LR_CONSTRUCTOR_PRODUC_ITEM_
#include <iostream>
#include <vector>
#include <set>
#include "LrContext.h"
#include "Produc.h"

using namespace std;

class ProducItem
{
private:
	//����Ŀ��Ӧ�Ĳ���ʽ���
	size_t produc_no;
public:
	//����Ŀ��Ӧ�Ĳ���ʽ
	Produc produc;
	//����Ŀ��ǰ����λ��
	size_t cursor;
	//����Ŀ��չ����
	set<string> prospects;
	ProducItem(size_t produc_no, Produc p);
	size_t get_no();
	//���ظ���Ŀ�Ƿ�Ϊ��Լ��Ŀ
	bool statute();
	//��ȡ��ǰ���Ⱥ�ڶ�λ���ţ�������Ϊ$
	Symbol next_prospects();
	//�ж���ȣ���ȷ��չ����
	bool identical(const ProducItem& item)const;
	//�ж���ȣ�����ȷ��չ����
	bool operator==(const ProducItem& item)const;
	ProducItem& operator=(const ProducItem& item);
	//��¡��ǰ��Ŀ��������+1
	ProducItem* clone_puls();
	//��vector�в��ҵ�ǰ����
	vector<ProducItem*>::iterator find_from_vector(vector<ProducItem*>& v);
};

#endif