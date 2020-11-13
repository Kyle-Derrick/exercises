#include <iostream>
#include <vector>
#include "include/Base.h"
#include "include/Produc.h"
#include "include/AppContext.h"

using namespace std;

int main()
{
	AppContext::init("D:\\LR.conf");
	vector<string> list;
	string str = "asa";
	split(list, str, ",");
	for (string s : list)
	{
		cout << s << "\t" << s.empty() << endl;
	}

}