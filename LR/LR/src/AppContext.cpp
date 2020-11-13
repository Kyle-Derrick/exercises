#include "..\include\AppContext.h"

int AppContext::lineType(string line)
{
    trim(line);
    int type = 0;
    if (line.empty() || line.at(0) == '#')
    {
        type = -1;
    }
    else if (line == "[symbol-list]")
    {
        type = 1;
    }
    else if (line == "[productor-list]")
    {
        type = 2;
    }
    else if (line == "[analysis-table]")
    {
        type = 3;
    }
    else if (line == "[error-list]")
    {
        type = 4;
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
    //将符号列表从大到小排序
    sort(symbols.begin(), symbols.end(), [](string& s1, string& s2) {
        return s1.length() > s2.length();
        });
}

void AppContext::analyzeProduc(vector<string>& tmp, vector<Produc>& producs, vector<string>& symbols)
{
    string arrow = tmp.at(0);
    for (vector<string>::iterator iter = tmp.begin()+1; iter != tmp.end(); iter++)
    {
        producs.push_back(Produc::identify(symbols, arrow, *iter));
    }
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

AppContext& AppContext::init(string f)
{
    ifstream fs(f);

    if (!fs.is_open())
    {
        cout << "打开文件失败！" << endl;
        exit(EXIT_FAILURE);
    }
    string line;
    int status = -1;
    vector<string> symbols;
    vector<string> actions;
    vector<string> gotos;
    vector<Produc> producs;
    string arrow;
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
        }
        else
        {
            cout << line << endl;
            vector<string> tmp;
            split(tmp, line, ",");
            switch (status)
            {
                //获取字符列表
            case 1:
                analyzeSymbol(tmp, symbols, actions, gotos);
                break;
            case 2:
                analyzeProduc(tmp, producs, symbols);
                break;
            case 3:
                cout << contentLineSize(fs) << endl;
                cout << contentLineSize(fs) << endl;
                break;
            case 4:
                break;
            default:
                cout << "配置文件不正确！" << endl;
                exit(EXIT_FAILURE);
                break;
            }
        }
    }

    //Test
    cout << "-------symbols-------" << endl;
    for (string s : symbols)
    {
        cout << s << endl;
    }
    cout << "-------actions-------" << endl;
    for (string s : actions)
    {
        cout << s << endl;
    }
    cout << "-------gotos-------" << endl;
    for (string s : gotos)
    {
        cout << s << endl;
    }
    cout << "-------producs-------" << endl;
    for (Produc p : producs)
    {
        cout << "+++" << endl;
        cout << p.getLeft() << endl;
        cout << p.getArrow() << endl;
        for (string s : p.getRight())
        {
            cout << s << endl;
        }
        cout << p.getStr() << endl;
    }

    return *new AppContext();
}
