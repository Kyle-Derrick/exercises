#pragma once
#ifndef _LR_ANALYZE_H_
#define _LR_ANALYZE_H_

#include <iostream>
#include <iomanip>
#include <vector>
#include "AppContext.h"
#include "LexicalAnalysis.h"
#include "InitApp.h"

using namespace std;

struct Node
{
	size_t status;
	Symbol symbol;
};

class LRAnalyze
{
private:
	//������������
	AppContext context;
	//����ջ
	vector<Node> analyze_stack;
	//�����ľ���
	string str;
	//�����ľ��������ɵķ��Ŵ�
	vector<Symbol> symbols;
	//��ջ
	void stack_push(Symbol symbol, size_t status);
	//��ջ��ָ������
	void stack_pop(size_t size);
	//��Լ����
	string reduce(TableUnit& unit, Symbol& symbol);
	//�ͷ��ڴ�
	void destory();
	//��ӡ��ǰ����ջ�ͷ��Ŵ�
	ostream& print_status(ostream& os);
public:
	LRAnalyze(AppContext& context);
	~LRAnalyze();
	//��ʼ��
	LRAnalyze& init(string str);
	//��ʼ����
	void analyze();
};

#endif