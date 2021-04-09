#include "newSet.h"

Set::Set(int max)
{
    if (max < 0) {
        exit(1);
    }
    m_length = 0;
    m_lim = max;
    m_set = new ItemType[max];
}

Set::Set(const Set& other)
{
    m_length = other.m_length;
    m_lim = other.m_lim;
    m_set = new ItemType[m_lim];

    for (int i = 0; i < m_length; i++) {
        m_set[i] = other.m_set[i];
    }
}

Set& Set::operator=(const Set& rhs)
{
    if (this != &rhs)
    {
        Set temp(rhs);
        swap(temp);
    }

    return *this;
}

Set::~Set()
{
    delete [] m_set;
}

bool Set::empty() const
{
    return m_length == 0;
}

int Set::size() const
{
    return m_length;
}

bool Set::insert(cons

bool Set::erase(const ItemType& value)
{
    for (int i = 0; i != m_length; i++) {
        if (m_set[i] == value) {
            for (int j = i; j != m_length; j++) {
                m_set[j] = m_set[j + 1];
            }
            m_length--;
            return true;
        }
    }
    return false;
}

bool Set::contains(const ItemType& value)
{
    for (int i = 0; i != m_length; i++) {
        if (m_set[i] == value) {
            return true;
        }
    }
    return false;
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


