#include "Sequence.h"
#include <string>
#include <iostream>
#include <cassert>
using namespace std;

void test()
{
    Sequence s;
    assert(s.insert(0, "lavash"));
    assert(s.insert(0, "tortilla"));
    assert(s.size() == 2);
    ItemType x = "injera";
    assert(s.get(0, x)  &&  x == "tortilla");
    assert(s.get(1, x)  &&  x == "lavash");
}

int main()
{
    test();
    Sequence s2;
    s2.insert("lol");
    cout << s2.empty() << endl;
    s2.erase(0);
    cout << s2.empty() << endl;
    cout << "Passed all tests" << endl;
}
