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



