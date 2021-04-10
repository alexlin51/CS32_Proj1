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

bool Set::insert(const ItemType& value)
{
    if (m_length >= m_lim) {
        return false;
    }

    if (m_length == 0) {
        m_set[0] = value;
        m_length = 1;
        return true;
    }

    if (contains(value)) {
        return false;
    }
    else {
        for (int i = 0; i != m_length; i++) {
            if (value > m_set[i]) {
                for (int j = m_length; j != i; j--) {
                    m_set[j] = m_set[j - 1];
                }
                m_set[i] = value;
                m_length++;
                return true;
            }
        }

        m_set[m_length] = value;
        m_length++;
        return true;
    }
}

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
    ItemType* ptr = m_set;
    m_set = other.m_set;
    other.m_set = ptr;

    int tempLen = m_length;
    m_length = other.m_length;
    other.m_length = tempLen;

    int tempLim = m_lim;
    m_lim = other.m_lim;
    other.m_lim = tempLim;
}
