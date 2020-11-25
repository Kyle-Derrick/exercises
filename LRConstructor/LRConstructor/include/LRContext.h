#pragma once
#ifndef _LR_CONSTRUCTOR_CONTEXT_
#define _LR_CONSTRUCTOR_CONTEXT_
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <string>
#include <map>
#include <set>
#include "Produc.h"

using namespace std;
class LRContext
{
private:
	//�ս���������ڸ����ڲ������ģ���ͬ
	vector<string> terminators;
	//���ս����
	vector<string> non_terminators;
	//����ʽ�б�
	vector<Produc> producs;
	//����ʽӳ�䣬keyֵΪ����ʽ�󲿣�ֵΪ����ʽ�ڲ���ʽ�б��еı��
	map<string, set<size_t>> produc_map;
	//�Ƶ���
	string arrow;
	//�ָ���
	string delim;
	//��ʼ����
	Symbol start_symbol;
	//��������ʽ
	static void produc_analyze(
		const string& line, const string& arrow, const string& delim, const vector<string>& terminators,
		const vector<string>& non_terminators, vector<Produc>& producs,
		map<string, set<size_t>>& produc_map);
public:
	//�ս������������˳�����У���ͬ
	vector<string> terminators_source;
	//���ս��
	vector<string> non_terminators_source;
	//��ʼ������ȡ�����������ļ�
	static LRContext init(string fpath);
	//�������
	void test();
	//���ݱ�Ż�ȡ����ʽ
	Produc get_produc(size_t no);
	//��ȡ�Ƶ���
	string get_arrow();
	string get_delim();
	//��ȡ��ʼ����
	Symbol& get_start_symbol();
	//������չ�ķ�ʱ�����Ĳ���ʽ
	void set_expand_produc(const Produc& p);
	//���ݷ��ս����ȡ�÷��ս�������в���ʽ
	set<size_t>* get_produc_nos(const string& symbol);
	//�ж��ַ����Ƿ��Ƿ��ս�����ж����
	bool non_terminators_exist(const string& symbol);
	//��������б�Ͳ���ʽ�б�
	ostream& output(ostream& out);
};

#endif