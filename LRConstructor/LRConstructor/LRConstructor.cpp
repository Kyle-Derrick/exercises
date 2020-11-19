#include <iostream>
#include "include/LRContext.h"

using namespace std;

void constructor(LRContext context);

int main()
{
    cout << "> 读取配置..." << endl;
    LRContext context = LRContext::init("LRConstructor.conf");
    context.test();
}

void constructor(LRContext context)
{

}
