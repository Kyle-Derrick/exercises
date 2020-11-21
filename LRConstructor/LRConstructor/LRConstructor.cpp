#include <iostream>
#include <map>
#include "include/LRContext.h"
#include "include/LRTableBuilder.h"

using namespace std;

void constructor(LRContext context);

int main()
{
    cout << "> 读取配置..." << endl;
    LRContext context = LRContext::init("LRConstructor.conf");

    LRTableBuilder(&context).start();

    vector<string> v1;
    vector<string> v2 = v1;
    v1.push_back("aaa");
    cout << v1.size() << endl;
    cout << v2.size() << endl;
}

void constructor(LRContext context)
{
    
}
