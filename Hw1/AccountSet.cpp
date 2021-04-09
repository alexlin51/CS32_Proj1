#include "AccountSet.h"
#include <iostream>
using namespace std;

AccountSet::AccountSet(){}

bool AccountSet::add(ItemType  acctNum)
{
	return m_acc.insert(acctNum);
}

int AccountSet::size() const
{
	return m_acc.size();
}

void AccountSet::print() const
{
	for (int i = 0; i != m_acc.size(); i++) {
		ItemType t;
		m_acc.get(i, t);
		cout << t << endl;
	}
}


bool Set::get(int i, ItemType& value) const
{
    if (i < 0 || i >= m_length) {
        return false;
    }
    
    value = m_set[i];
    return true;
}

void Set::swap(Set& other)
{
    int longest;
    if (other.size() > m_length) {
        longest = other.size();
    }
    else {
        longest = m_length;
    }

    for (int i = 0; i != longest; i++) {
        ItemType temp = other.m_set[i];
        other.m_set[i] = this->m_set[i];
        this->m_set[i] = temp;
    }

    int tempLength = other.m_length;
    other.m_length = this->m_length;
    this->m_length = tempLength;
}


