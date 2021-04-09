#include "AccountSet.h"
#include <iostream>
#include <cassert>
using namespace std;

int main()
{
    AccountSet myACC;
    assert(myACC.size() == 0);
    ItemType x = 9876543;
    myACC.add(x);
    x++;
    myACC.add(x);
    myACC.print();
    assert(myACC.size() == 2);

    cout << "Passed all tests!" << endl;
}
