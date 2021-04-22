#include <iostream>
#include <string>
#include <cassert>
#include "Set.h"

using namespace std;

/*
#include <type_traits>

#define CHECKTYPE(f, t) { auto p = static_cast<t>(f); (void)p; }

static_assert(std::is_default_constructible<Set>::value,
    "Set must be default-constructible.");
static_assert(std::is_copy_constructible<Set>::value,
    "Set must be copy-constructible.");
static_assert(std::is_copy_assignable<Set>::value,
    "Set must be assignable.");

void thisFunctionWillNeverBeCalled()
{
    CHECKTYPE(&Set::empty, bool (Set::*)() const);
    CHECKTYPE(&Set::size, int  (Set::*)() const);
    CHECKTYPE(&Set::insert, bool (Set::*)(const ItemType&));
    CHECKTYPE(&Set::erase, bool (Set::*)(const ItemType&));
    CHECKTYPE(&Set::contains, bool (Set::*)(const ItemType&) const);
    CHECKTYPE(&Set::get, bool (Set::*)(int, ItemType&) const);
    CHECKTYPE(&Set::swap, void (Set::*)(Set&));
    CHECKTYPE(unite, void (*)(const Set&, const Set&, Set&));
    CHECKTYPE(difference, void (*)(const Set&, const Set&, Set&));
}
*/

int main() {
    /*
    Set ss;  
    ss.insert("ccc");
    ss.insert("aaa");
    ss.insert("bbb");
    ItemType x = "xxx";
    assert(!ss.get(3, x) && x == "xxx");  // x is unchanged
    assert(ss.get(1, x) && x == "bbb");
    */

    /*
    Set uls;
    assert(uls.insert(10));
    assert(uls.insert(20));
    assert(uls.size() == 2);
    assert(uls.contains(20));
    ItemType x = 30;
    assert(uls.get(0, x) && x == 20);
    assert(uls.get(1, x) && x == 10);
    */

    /*
    Set s1;
    s1.insert(4);
    s1.insert(5);
    cout << s1.size() << endl;
    s1.insert(3);
    cout << s1.size() << endl;
    s1.erase(3);
    cout << s1.size() << endl;
    */

    /*
    Set s1;
    s1.insert(2);
    s1.insert(8);
    s1.insert(3);
    s1.insert(9);
    s1.insert(5);
    Set s2;
    s2.insert(6);
    s2.insert(3);
    s2.insert(8);
    s2.insert(5);
    s2.insert(10);

    Set s3;
    Set s4;
    unite(s1, s2, s3);
    for (int i = 0; i != s3.size(); i++) {
        ItemType temp;
        s3.get(i, temp);
        cout << temp << endl;
    }
    cout << "-------" << endl;

    difference(s1, s2, s4);
    for (int i = 0; i != s4.size(); i++) {
        ItemType temp;
        s4.get(i, temp);
        cout << temp << endl;
    }

    cout << "Passed tests!" << endl;
    */
}