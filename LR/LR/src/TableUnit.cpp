#include "..\include\TableUnit.h"

TableUnit::TableUnit(UnitType type, size_t value)
{
    this->type = type;
    this->value = value;
}

TableUnit& TableUnit::identify(string str)
{
	transform(str.begin(), str.end(), str.begin(), ::tolower);
	UnitType type;
	size_t value = 0;
	if (str.empty())
	{
		type = UnitType::ERROR;
	}
	else if (str == "acc")
	{
		type = UnitType::ACC;
	}
	else
	{
		try
		{
			value = stoi(str.substr(1));
		}
		catch (const std::exception&)
		{
			cerr << "���������ݸ�ʽ����Ӧ�ڲ�������ָ��һ����ֵ: " << str << endl;
			exit(EXIT_FAILURE);
		}
		switch (str.at(0))
		{
		case 's':
			type = UnitType::SHIFT;
			break;
		case 'r':
			type = UnitType::REDUCE;
			break;
		case 'e':
			type = UnitType::ERROR;
			break;
		default:
			cerr << "�������ʽ����,��ͷӦΪs|r|e: " << str << endl;
			exit(EXIT_FAILURE);
		}
	}
	return *new TableUnit(type, value);
}

UnitType TableUnit::getType()
{
	return this->type;
}

char TableUnit::getTypeStr()
{
	char c = ' ';
	switch (this->type)
	{
	case UnitType::SHIFT:
		c = 's';
		break;
	case UnitType::REDUCE:
		c = 'r';
		break;
	case UnitType::ERROR:
		c = 'e';
		break;
	case UnitType::ACC:
		c = 'a';
		break;
	default:
		break;
	}
	return c;
}

size_t TableUnit::getValue()
{
	return this->value;
}
