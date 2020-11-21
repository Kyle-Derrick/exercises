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
    //LRContext context = LRContext::init("D:\\LRConstructor.conf");

    LRTableBuilder(&context).start();

}

void constructor(LRContext context)
{
    
}
