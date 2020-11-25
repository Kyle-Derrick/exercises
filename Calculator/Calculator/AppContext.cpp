#include "include\AppContext.h"

int AppContext::lineType(string line)
{
    kyle::trim(line);
    int type = 0;
    if (line.empty() || line.at(0) == '#')
    {
        type = -1;
    }
    else if (line == "[symbol-list]")
    {
        type = 1;
        //cout << "\n>> <���������б�>" << endl;
    }
    else if (line == "[productor-list]")
    {
        type = 2;
        //cout << "\n>> <��������ʽ�б�>" << endl;
    }
    else if (line == "[analysis-table]")
    {
        type = 3;
        //cout << "\n>> <����������>" << endl;
    }
    else if (line == "[error-list]")
    {
        type = 4;
        //cout << "\n>> <����������Ϣ�б�>" << endl;
    }
    return type;
}

void AppContext::analyzeSymbol(vector<string>& tmp, vector<string>& symbols, vector<string>& actions, vector<string>& gotos)
{
    vector<string>::iterator res = find(tmp.begin(), tmp.end(), "$");
    symbols.insert(symbols.end(), tmp.begin(), tmp.end());
    res++;
    actions.insert(actions.end(), tmp.begin(), res);
    if (!(res == tmp.end()))
    {
        gotos.insert(gotos.end(), res, tmp.end());
    }
    //�������б�Ӵ�С����
    sort(symbols.begin(), symbols.end(), [](string& s1, string& s2) {
        return s1.length() > s2.length();
        });
}

string AppContext::analyzeProduc(vector<string>& tmp, vector<Produc>& producs, vector<string>& symbols)
{
    if (symbols.empty())
    {
        cout << "�����б�������Ҫ�ڲ���ʽ֮ǰ��" << endl;
        exit(EXIT_FAILURE);
    }
    string arrow = tmp.at(0);
    for (vector<string>::iterator iter = tmp.begin()+1; iter != tmp.end(); iter++)
    {
        producs.push_back(Produc::identify(symbols, arrow, *iter));
    }
    return arrow;
}

void AppContext::analyzeTable(vector<string>& tmp, size_t tsize, size_t psize, size_t asize, size_t gsize, 
    vector<vector<TableUnit>>& atable, vector<vector<int>>& gtable)
{
    if (!psize)
    {
        cout << "����ʽ�б�������Ҫ�ڷ�����֮ǰ��" << endl;
        exit(EXIT_FAILURE);
    }
    if (tmp.size() < (asize+gsize))
    {
        cout << "��������������Ÿ�����ƥ�䣡" << endl;
        exit(EXIT_FAILURE);
    }
    vector<string>::iterator iter = tmp.begin();
    vector<TableUnit> alist;
    vector<int> glist;
    for (size_t i = 0; i < asize; i++)
    {
        TableUnit unit = TableUnit::identify(*iter);
        switch (unit.getType())
        {
        case UnitType::SHIFT:
            //�ж��ƽ�״̬�Ƿ񳬹����״̬��״̬��0��ʼ���������0��ʼ
            if (unit.getValue() >= tsize)
            {
                cout << "������Shift״̬�������״̬: s" << unit.getValue() << ",���: " << tsize << endl;
                exit(EXIT_FAILURE);
            }
            break;
        case UnitType::REDUCE:
            //�жϹ�Լ����ʽ����Ƿ񳬹�����������Ŵ�0��ʼ���������1��ʼ
            if (unit.getValue() > psize)
            {
                cout << "������Reduce��ų��������: r" << unit.getValue() << ",���: " << psize << endl;
                exit(EXIT_FAILURE);
            }
            break;
        default:
            break;
        }
        alist.push_back(unit);
        iter++;
    }
    for (size_t i = 0; i < gsize; i++)
    {
        int va;
        try
        {
            va = stoi(*iter);
        }
        catch (const std::exception&)
        {
            va = -1;
        }
        glist.push_back(va);
        if (iter != tmp.end())
        {
            iter++;
        }
    }
    atable.push_back(alist);
    gtable.push_back(glist);
}

void AppContext::analyzeError(vector<string>& tmp, vector<string>& errors)
{
    errors.insert(errors.end(), tmp.begin(), tmp.end());
}

size_t AppContext::contentLineSize(ifstream& fs)
{
    streampos pos = fs.tellg();
    string line;
    size_t size = 0;
    while (getline(fs, line), !lineType(line))
    {
        size++;
    }
    fs.seekg(pos);
    return size;
}

AppContext::~AppContext()
{
    vector<string>().swap(this->symbols);
    vector<string>().swap(this->actions);
    vector<string>().swap(this->gotos);
    vector<Produc>().swap(this->producs);
    vector<vector<TableUnit>>().swap(this->atable);
    vector<vector<int>>().swap(this->gtable);
    vector<string>().swap(this->errors);
}

AppContext AppContext::init(string f)
{
    cout << ">> ��ʼ�����ļ�..." << endl;

    ifstream fs(f);
    if (!fs.is_open())
    {
        cout << "���ļ�ʧ�ܣ�" << endl;
        exit(EXIT_FAILURE);
    }
    string line;
    int status = -1;
    string delim;
    getline(fs, delim);
    kyle::trim(delim);
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
    size_t tsize = 0;
    while (!fs.eof())
    {
        getline(fs, line);
        int ltype = lineType(line);
        if (ltype < 0)
        {
            continue;
        }
        else if (ltype > 0)
        {
            status = ltype;
            //���Ϊ���������ʱ���Ȼ�ȡ��������
            if (status == 3)
            {
                tsize = contentLineSize(fs);
            }else if (status == 4)
            {
                errors.push_back("δ֪����");
            }
        }
        else
        {
            //cout << line << endl;
            vector<string> tmp;
            kyle::split(tmp, line, delim);
            switch (status)
            {
                //��ȡ�ַ��б�
            case 1:
                analyzeSymbol(tmp, symbols, actions, gotos);
                break;
            case 2:
                arrow = analyzeProduc(tmp, producs, symbols);
                break;
            case 3:
                analyzeTable(tmp, tsize, producs.size(), actions.size(), gotos.size(), atable, gtable);
                break;
            case 4:
                analyzeError(tmp, errors);
                break;
            default:
                cout << "�����ļ�����ȷ��" << endl;
                exit(EXIT_FAILURE);
                break;
            }
        }
    }

    //����ʵ������ֵ
    AppContext context;
    context.symbols = symbols;
    context.actions = actions;
    context.gotos = gotos;
    context.producs = producs;
    context.atable = atable;
    context.gtable = gtable;
    context.errors = errors;
    context.arrow = arrow;
    return context;
}

TableUnit AppContext::action_search(string symbol, size_t status)
{
    vector<string>::iterator iter = find(actions.begin(), actions.end(), symbol);
    return atable.at(status).at(iter - actions.begin());
}

int AppContext::goto_search(string symbol, size_t status)
{
    vector<string>::iterator iter = find(gotos.begin(), gotos.end(), symbol);
    return gtable.at(status).at(iter - gotos.begin());
}

Produc AppContext::get_produc(size_t index)
{
    index = min(this->producs.size() - 1, index);
    return this->producs.at(index);
}

string AppContext::get_error(size_t index)
{
    if ((this->errors.size() - 1) < index)
    {
        index = 0;
    }
    return this->errors.at(index);
}

vector<string> AppContext::analyzestr(vector<string>& strs, string str)
{
    return kyle::str_to_symbols(this->symbols, strs, str);
}