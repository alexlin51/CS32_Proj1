#include "Set.h"

Set::Set()
{
    m_length = 0;
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
    if (m_length >= DEFAULT_MAX_ITEMS) {
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


