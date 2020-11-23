#include <iostream>
#include <map>
#include "include/LRContext.h"
#include "include/LRTableBuilder.h"

using namespace std;

int main(int argc, char *argv[])
{
    cout << "--- LR1 or LALR constructor by Kyle --- " << endl;
    string infile;
    if (argc < 2)
    {
        while (true)
        {
            cout << "请输入配置文件路径: " << endl;
            cin >> infile;
            if (!infile.empty())
            {
                break;
            }
        }
    }
    else
    {
        infile = argv[1];
    }
    string outfile;
    if (argc < 3)
    {
        outfile = "LR.table.conf";
    }
    else
    {
        outfile = argv[2];
    }

    cout << "> 读取配置..." << endl;
    LRContext context = LRContext::init(infile);
    //LRContext context = LRContext::init("C:\\LRConstructor.conf");

    LRTableBuilder(&context).start(outfile);

}