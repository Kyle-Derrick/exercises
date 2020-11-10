#include <iostream>
#include "include/Produc.h"

int main()
{
    cout << "Hello World!\n" << endl;
    Produc p = Produc("E", "→", "ET");
    cout << p.toString() << endl;
}