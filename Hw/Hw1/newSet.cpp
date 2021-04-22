#include "newSet.h"
#include <iostream>

using namespace std;

Set::Set()
{
    // Initialize empty set
    m_length = 0;
    head = nullptr;
    tail = nullptr;
}

Set::Set(const Set& other)
{
    m_length = other.m_length;
    
    // Empty Set case
    if (other.m_length == 0) {
        head = nullptr;
        tail = nullptr;
        return;
    }

    // Create new Head
    head = new Node;
    head->prevNode = nullptr;

    Node* temp = head;

    // Creates new nodes for L.L. until tail
    for (Node* T = other.head; T->nextNode != nullptr; T = T->nextNode) {
        Node* newNode = new Node;
        
        temp->m_item = T->m_item;
        temp->nextNode = newNode;
        newNode->prevNode = T;

        temp = newNode;
    }

    // Adds tail to L.L
    temp->m_item = other.tail->m_item;
    temp->nextNode = nullptr;

    // Sets tail
    tail = temp;
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
    // case of empty list, nothing to delete
    if (head == nullptr) {
        return;
    }

    Node* temp = head;
    Node* next;

    // traverse and deletes nodes
    while (temp != nullptr) {
        next = temp->nextNode;
        delete temp;
        temp = next;
    }
}


void Set::dump() const {
    cerr << "------------------------------" << endl;
    cerr << "Set at: " << this << endl;
    if (head == nullptr) {
        cerr << "Head at: nullptr" << endl;
    }
    else {
        cerr << "Head at: " << head << endl;
    }

    if (tail == nullptr) {
        cerr << "Tail at: nullptr" << endl;
    }
    else {
        cerr << "Tail at: " << tail << endl;
    }
    cerr << "n_items: " << m_length << endl << endl;

    // L.L. Insides
    for (Node* cNode = head; cNode != nullptr; cNode = cNode->nextNode) {
        cerr << "Address: " << cNode;
        cerr << "\nm_item: " << cNode->m_item;
        if (cNode->prevNode == nullptr) {
            cerr << "\nprevNode: nullptr";
        }
        else {
            cerr << "\nprevNode: " << cNode->prevNode;
        }

        if (cNode->nextNode == nullptr) {
            cerr << "\nnextNode: nullptr";
        }
        else {
            cerr << "\nnextNode: " << cNode->nextNode;
        }
        cerr << endl << endl;
    }
    cerr << "--------------------" << endl;

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
    if (m_length == 0) {
        Node* newNode = new Node;
        newNode->m_item = value;
        newNode->nextNode = nullptr;
        newNode->prevNode = nullptr;

        head = newNode;
        tail = newNode;
        
        m_length = 1;
        return true;
    }

    if (contains(value)) {
        return false;
    } 
    else {
        Node* newNode = new Node;
        newNode->m_item = value;
        newNode->prevNode = nullptr;
        newNode->nextNode = nullptr;

        if (head->m_item < value) {
            newNode->nextNode = head;
            head->prevNode = newNode;
            head = newNode;
            return true;
        }

        Node* temp = head;

        while (temp->nextNode != nullptr && value < temp->nextNode->m_item) {
            temp = temp->nextNode;
        }
        
        // we are now at the node in which we want to insert after.
        if (temp->nextNode == nullptr) {
            temp->nextNode = newNode;
            newNode->prevNode = temp;
            tail = newNode;
            m_length++;
            return true;
        } 
        else {
            Node* next = temp->nextNode;
            temp->nextNode = newNode;
            newNode->prevNode = temp;
            newNode->nextNode = next;
            next->prevNode = newNode;
            m_length++;
            return true;
        }
    }
}

bool Set::erase(const ItemType& value)
{
    for (Node* temp = head; temp != nullptr; head = head->nextNode) {
        if (temp->m_item == value) {
            // find the node to erase & adjust pointers
            if (temp->prevNode == nullptr) {
                head = head->nextNode;
            }
            else {
                temp->prevNode->nextNode = temp->nextNode;
            }

            if (temp->nextNode == nullptr) {
                tail = temp->prevNode;
            }
            else {
                temp->nextNode->prevNode = temp->prevNode;
            }

            // decrement and delete
            m_length--;
            delete temp;
            return true;
        }
    }
    return false;
}

bool Set::contains(const ItemType& value)
{
    for (Node* temp = head; temp != nullptr; head = head->nextNode) {
        if (temp->m_item == value) {
            // Find the node with same value
            return true;
        }
    }
    return false;
}

bool Set::get(int i, ItemType& value) const
{
    // ensure position is valid
    if (i >= m_length || i < 0) {
        return false;
    }

    // move temp pointer to the correct index
    Node* temp = head;
    for (int j = 0; j != i; j++) {
        temp = temp->nextNode;
    }

    // set value 
    value = temp->m_item;
    return true;
}

void Set::swap(Set& other)
{
    // swap length value
    int tempLen = m_length;
    m_length = other.m_length;
    other.m_length = tempLen;

    // swaps the heads of set
    Node* tempHead = head;
    head = other.head;
    other.head = tempHead;

    // swap the tails of set
    Node* tempTail = tail;
    tail = other.tail;
    other.tail = tempTail;
}

void unite(const Set& s1, const Set& s2, Set& result)
{
}

void difference(const Set& s1, const Set& s2, Set& result)
{
}
