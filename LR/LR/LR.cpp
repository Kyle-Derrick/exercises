#include <iostream>
#include <vector>
#include "include/Base.h"
#include "include/Produc.h"
#include "include/AppContext.h"

using namespace std;

int main(int argc, char *argv[])
{
	AppContext context = AppContext::init("D:\\LR.conf");
	context.testPrint();


}