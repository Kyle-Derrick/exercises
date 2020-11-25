#include "include\LexicalAnalysis.h"

vector<Symbol>& LexicalAnalysis::analysis(string str, vector<Symbol>& sequences)
{
	kyle::replace_all(str, " ", "");
	string tmp;
	size_t last_status = 0;
	size_t status = 0;
	for (size_t i = 0; i < str.length(); i++)
	{
		char ch = str[i];
		switch (ch)
		{
		case '+':
		case '-':
		case '*':
		case '/':
		case '^':
		case '%':
		case '!':
		case '(':
		case ')':
		case '|':
		case ',':
			status = 0;
			break;
		default:
			if ('0'<=ch && ch <= '9')
			{
				status = 1;
			}
			else if ('.' == ch)
			{
				status = 2;
			}
			else if (('a' <= ch && 'z' >=ch) || ('A' <= ch && 'Z' >= ch) || '_' == ch)
			{
				status = 3;
			}
			break;
		}
		Symbol word_tmp;
		if (last_status != status)
		{
			bool need_flush = true;
			if (last_status == 1 && status != 2)
			{
				word_tmp = Symbol("num", new string(tmp));
			}
			else if (last_status == 2 && status != 1)
			{
				cerr << "不正确的小数形式: " << str.substr(i) << endl;
				exit(EXIT_FAILURE);
			}
			else if (last_status == 3)
			{
				if (tmp == "pi" || tmp == "PI")
				{
					word_tmp = Symbol("num", new string(to_string(kyle::M_PI)));
				}else if (tmp == "e")
				{
					word_tmp = Symbol("num", new string(to_string(kyle::M_E)));
				}
				else
				{
					word_tmp = Symbol("fun", new string(tmp));
				}
			}
			else
			{
				need_flush = false;
			}
			if (need_flush)
			{
				sequences.push_back(word_tmp);
				tmp = string();
			}
		}
		tmp.push_back(ch);
		if (!status)
		{
			sequences.push_back(Symbol(tmp));
			tmp = string();
		}

		if ((i+1) >= str.length())
		{
			switch (status)
			{
			case 1:
				sequences.push_back(Symbol("num", new string(tmp)));
				break;
			case 3:
				if (tmp == "pi" || tmp == "PI")
				{
					word_tmp = Symbol("num", new string(to_string(kyle::M_PI)));
				}
				else if (tmp == "e")
				{
					word_tmp = Symbol("num", new string(to_string(kyle::M_E)));
				}
				else
				{
					word_tmp = Symbol("fun", new string(tmp));
				}
				sequences.push_back(word_tmp);
				break;
			case 2:
				cerr << "不正确的小数形式: " << str.substr(i) << endl;
				exit(EXIT_FAILURE);
				break;
			}
		}
		last_status = status;
	}

	return sequences;
}