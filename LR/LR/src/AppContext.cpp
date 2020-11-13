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
    if (symbols.empty())
    {
        cout << "符号列表配置需要在产生式之前！" << endl;
        exit(EXIT_FAILURE);
    }
    string arrow = tmp.at(0);
    for (vector<string>::iterator iter = tmp.begin()+1; iter != tmp.end(); iter++)
    {
        producs.push_back(Produc::identify(symbols, arrow, *iter));
    }
}

void AppContext::analyzeTable(vector<string>& tmp, size_t tsize, size_t psize, size_t asize, size_t gsize, 
    vector<vector<TableUnit>>& atable, vector<vector<int>>& gtable)
{
    if (!psize)
    {
        cout << "产生式列表配置需要在分析表之前！" << endl;
        exit(EXIT_FAILURE);
    }
    if (tmp.size() < (asize+gsize))
    {
        cout << "分析表列数与符号个数不匹配！" << endl;
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
            //判断移进状态是否超过最大状态，状态从0开始，分析表从0开始
            if (unit.getValue() >= tsize)
            {
                cout << "分析表Shift状态超出最大状态: s" << unit.getValue() << ",最大: " << tsize << endl;
                exit(EXIT_FAILURE);
            }
            break;
        case UnitType::REDUCE:
            //判断规约产生式编号是否超过最大个数，编号从0开始，分析表从1开始
            if (unit.getValue() > psize)
            {
                cout << "分析表Reduce编号超出最大编号: r" << unit.getValue() << ",最大: " << psize << endl;
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
    vector<vector<TableUnit>> atable;
    vector<vector<int>> gtable;
    vector<string> errors;
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
            //如果为分析表分析时，先获取表行数。
            if (status == 3)
            {
                tsize = contentLineSize(fs);
            }else if (status == 4)
            {
                errors.push_back("未知错误");
            }
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
                analyzeTable(tmp, tsize, producs.size(), actions.size(), gotos.size(), atable, gtable);
                break;
            case 4:
                analyzeError(tmp, errors);
                break;
            default:
                cout << "配置文件不正确！" << endl;
                exit(EXIT_FAILURE);
                break;
            }
        }
    }

    //创建实例并赋值
    AppContext &context = *new AppContext();
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

void AppContext::testPrint()
{
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
    cout << "-------atable-------" << endl;
    for (vector<TableUnit> v : atable)
    {
        for (TableUnit u : v)
        {
            cout << u.getTypeStr() << u.getValue() << '\t';
        }
        cout << endl;
    }
    cout << "-------gtable-------" << endl;
    for (vector<int> v : gtable)
    {
        for (int i : v)
        {
            cout << i << '\t';
        }
        cout << endl;
    }
    cout << "-------errors-------" << endl;
    for (string s : errors)
    {
        cout << s << endl;
    }
}
