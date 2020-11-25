#pragma once
#ifndef _CALCULATOR_INIT_APP_H_
#define _CALCULATOR_INIT_APP_H_
#include <iostream>
#include <vector>
#include <map>
#include <math.h>
#include "Symbol.h"

using namespace std;

typedef map<string, double(*)(vector<double>)> Functions;
typedef map<string, Symbol(*)(vector<Symbol>)> Reduces;

class InitApp
{
private:
	static void check_arg(string fname, size_t args_size, size_t need_size);
public:
	//��������֧�ֵļ��㺯�������������
	static Functions funs;
	//����ʽ��Լ����
	static Reduces reduces;

	//���ؼ��㷽����
	static Functions& load_funs(Functions& fs);
	//���ع�Լ������
	static Reduces& load_reduces(Reduces& fs);
	//��ʼ��
	static void init();
};

#endif