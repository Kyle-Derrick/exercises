#pragma once
#ifndef _LR_CONSTRUCTOR_TABLE_BUILDER_
#define _LR_CONSTRUCTOR_TABLE_BUILDER_
#include <iostream>
#include <vector>
#include <fstream>
#include <stack>
#include "Symbol.h"
#include "LRContext.h"
#include "ProducItem.h"

using namespace std;

class ProducItemGroup
{
private:
	//identical�����ص�==���õ����ж϶ԵȺ��������ݴ���ĺ���ָ���ж�LR������Ŀ���е�Ԫ���Ƿ����
	bool equals(const ProducItemGroup& g, bool(*fun)(ProducItem*, ProducItem*)) const;
public:
	//����LR������е���Ŀ��
	vector<ProducItem*> items;
	//��״̬����һ�����ſɵ����״̬
	map<Symbol, ProducItemGroup*> next_group_nos;
	~ProducItemGroup();
	//��������жϣ�����ȷչ����
	bool operator==(const ProducItemGroup& g) const; 
	//����жϣ���ȷչ����
	bool identical(const ProducItemGroup& g) const;
	//�ϲ�չ������
	void merge(const ProducItemGroup& g);
	//������Ŀ����ֻ����LALR��
	void clear_non_core();
	//��vector�в��ҵ�ǰ����
	vector<ProducItemGroup*>::iterator find_from_vector(vector<ProducItemGroup*>& v);
};

class LRTableBuilder
{
private:
	//�ó���������Ϣ
	LRContext* context;
	//��������е�״̬��
	vector<ProducItemGroup*> groups;
	//������չ����ʽ
	Produc build_expand_produc();
	//����ǰ���Ⱥ��һλ���ţ�����ǰ���Ⱥ��һλ����Ϊ���ս��ʱ�������������Ĳ���ʽ
	void handle(ProducItemGroup* group);
	//������Ŀ���е���Ŀ������һ��״̬
	void next(ProducItemGroup* group);
	//���ݴ���ĵ��ڶ�λ��������չ����
	set<string>& set_prospects(Symbol symbol, set<string>& prospects);
	//��������״̬������LR��
	void generate_table(vector<vector<string>>& action_table, vector<vector<string>>& goto_table);
	//�����ս����ȡaction����б��
	size_t get_action_no(string str);
	//���ݷ��ս����ȡgoto����б��
	size_t get_goto_no(string str);
	//��������
	ostream& out_table(ostream& out, const vector<vector<string>>& action_table, const vector<vector<string>>& goto_table);
	//���÷�������Ԫ
	void set_table_node(vector<vector<string>>& table, size_t row, size_t col, string str);
	//��������LALR��LR״̬��
	void try_lalr();
	//���Դ�ӡ���״̬��
	void test();

public:
	LRTableBuilder(LRContext* context);
	~LRTableBuilder();
	//��ʼ����
	void start(const string& outfile);
};

#endif // !_LALR_CONSTRUCTOR_TABLE_BUILDER_