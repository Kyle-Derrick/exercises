#pragma once
#ifndef _APPCONTEXT_H_
#define _APPCONTEXT_H_

#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>
#include "Produc.h"
#include "KyleBase.h"
#include "TableUnit.h"

using namespace std;

class AppContext
{
private:
	//����
	//���ż�
	vector<string> symbols;
	//action��ͷ
	vector<string> actions;
	//goto��ͷ
	vector<string> gotos;
	//����ʽ�б�
	vector<Produc> producs;
	//action��
	vector<vector<TableUnit>> atable;
	//goto��
	vector<vector<int>> gtable;
	//������Ϣ�б�
	vector<string> errors;
	//�Ƶ�����
	string arrow;

	//��ȡ�����ļ���ǰ�����ͣ����л�ע��Ϊ-1������Ϊ0�������б�������ʽ�б�����������������Ϣ���ñ�־�ֱ�Ϊ1��2��3��4
	static int lineType(string line);
	//���������б�
	static void analyzeSymbol(vector<string>& tmp, vector<string>& symbols, vector<string>& actions, vector<string> &gotos);
	//��������ʽ�б�
	static string analyzeProduc(vector<string>& tmp, vector<Produc>& pruducs, vector<string>& symbols);
	//����������
	static void analyzeTable(vector<string>& tmp, size_t tsize, size_t psize, size_t asize, size_t gsize,
		vector<vector<TableUnit>>& atable, vector<vector<int>>& gtable);
	//����������Ϣ�б�
	static void analyzeError(vector<string>& tmp, vector<string>& errors);
	//��ȡ��������������
	static size_t contentLineSize(ifstream& fs);
public:
	~AppContext();
	/**
	��ʼ��
	������������ļ�·��
	*/
	static AppContext init(string f);

	//��ѯaction��
	TableUnit action_search(string symbol, size_t status);
	//��ѯgoto��
	int goto_search(string symbol, size_t status);
	//��ȡ����ʽ
	Produc get_produc(size_t index);
	//��ȡ������Ϣ
	string get_error(size_t index);
	//ͨ�����ű������ַ���Ϊ�ַ����б�
	vector<string> analyzestr(vector<string>& strs, string str);
};

#endif // !_APPCONTEXT_H_