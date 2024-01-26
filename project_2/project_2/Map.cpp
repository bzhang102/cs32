#include "Map.h"
#include <iostream>
#include <cassert>

using namespace std;

// Constructors, Destructor, Assignment Operator
Map::Map(): m_dummy(new Node), m_size(0) {
    // link dummy node to itself
    m_dummy->next = m_dummy;
    m_dummy->prev = m_dummy;
}
Map::~Map() {
    // delete all nodes
    Node* q;
    for(Node* p = m_dummy->next; p != m_dummy;) {
        q = p->next;
        delete p;
        p = q;
    }
    delete m_dummy;
}
Map::Map(const Map& src): m_dummy(new Node()), m_size(src.m_size) {
    // link dummy node to itself
    m_dummy->next = m_dummy;
    m_dummy->prev = m_dummy;

    // iterate through all nodes in src and insert new copies into this map
    for(Node* p = src.m_dummy->next; p != src.m_dummy; p = p->next) {
        insert(p->key, p->value);
    }
}
Map& Map::operator=(const Map& src) {
    // anti-aliasing
    if(this != &src) {
        // make copy of src
        Map temp(src);
        // swap map with copy (current map will get destroyed once out of scope)
        swap(temp);
    }
    return *this;
}

// Trivial Functions
bool Map::empty() const {
    return m_size == 0;
}
int Map::size() const {
    return m_size;
}

// Member Functions
bool Map::insert(const KeyType& key, const ValueType& value) {
    // checks if key already exists
    if(contains(key)) {
        return false;
    }

    // dynamically allocates new node, linking it to correct nodes on either side
    Node* p = new Node(key, value, m_dummy, m_dummy->next);

    // links nodes on either side to new node
    m_dummy->next = p; // m_dummy's next node becomes p
    m_dummy->next->next->prev = p; // second node's prev becomes p

    // increments size counter
    m_size++;

    return true;
}
bool Map::update(const KeyType& key, const ValueType& value) {
    for(Node* p = m_dummy->next; p != m_dummy; p = p->next) {
        // updates value at key if found
        if(p->key == key) {
            p->value = value;
            return true;
        }
    }
    // if all nodes exhausted, return false
    return false;
}
bool Map::insertOrUpdate(const KeyType& key, const ValueType& value) {
    // attempts to update, if failed, inserts instead
    return update(key, value) ? true : insert(key, value);
}
bool Map::erase(const KeyType& key) {
    for(Node* p = m_dummy->next; p != m_dummy; p = p->next) {
        // erases value if found
        if(p->key == key) {
            // links nodes on either side
            p->prev->next = p->next;
            p->next->prev = p->prev;

            // deletes dynamically allocated node
            delete p;

            // decrements size counter
            m_size--;

            return true;
        }
    }
    // if all nodes exhausted, return false
    return false;
}
bool Map::contains(const KeyType& key) const {
    for(Node* p = m_dummy->next; p != m_dummy; p = p->next) {
        // if key found, return true
        if(p->key == key) {
            return true;
        }
    }
    // if all nodes exhausted, return false
    return false;
}
bool Map::get(const KeyType& key, ValueType& value) const {
    for(Node* p = m_dummy->next; p != m_dummy; p = p->next) {
        // if key found, reassign value to stored value
        if(p->key == key) {
            value = p->value;
            return true;
        }
    }
    // if all nodes exhausted, return false
    return false;
}
bool Map::get(int i, KeyType& key, ValueType& value) const {
    // checks for valid i
    if(i >= 0 && i < m_size) {
        // iterate through each node once
        for(Node* p = m_dummy->next; p != m_dummy; p = p->next) {
            int count = 0;
            // compare inner node with outer node
            for(Node* q = m_dummy->next; q != m_dummy; q = q->next) {
                // count number of nodes that contain nodes with a key < outer's key
                if(p->key > q->key) {
                    count++;
                }
            }

            // if key of outer is strictly greater than i keys, return that pair
            if(count == i) {
                key = p->key;
                value = p->value;
                return true;
            }
        }
    }

    // if i is invalid, or not found (impossible), return false
    return false;
}
void Map::swap(Map& other) {
    // swaps dummy node
    Node* tempNode = m_dummy;
    m_dummy = other.m_dummy;
    other.m_dummy = tempNode;

    // swaps size counter
    int tempSize = m_size;
    m_size = other.m_size;
    other.m_size = tempSize;
}
void Map::dump() const {
    Node* p = m_dummy->next;
    for(int i = 0; i < m_size; i++) {
        cerr << p->key << ":" << p->value;
        cerr << " Next:" << p->next->key;
        cerr << " Prev:" << p->prev->key;
        cerr << endl;
        p = p->next;
    }
    cerr << endl;
}

//Non Member Functions
bool merge(const Map& m1, const Map& m2, Map& result) {
    // state bool to track if merge conflict occurs
    bool state = true;

    // call result's assignment operator with m1
    result = m1;

    KeyType key;
    ValueType value;
    // iterate through all elements of m2 using get
    for(int i = 0; i < m2.size(); i++) {
        m2.get(i, key, value);
        //if result already contains key, check for merge conflict
        if(result.contains(key)) {
            ValueType existingValue;
            result.get(key, existingValue);
            // if merge conflict exists, erase node and change state
            if(existingValue != value) {
                result.erase(key);
                state = false;
            }
        } else {
            result.insert(key, value);
        }
    }

    return state;
}
void reassign(const Map& m, Map& result) {
    // copy m into result
    result = Map(m);

    KeyType key;
    ValueType value;
    KeyType firstKey;
    ValueType temp;
    result.get(0, firstKey, value);

    // iterate through all nodes except the first
    for(int i = 1; i < result.size(); i++) {
        result.get(i, key, temp);
        result.update(key, value);
        value = temp;
    }
    // update first node's value to equal last node's value
    result.update(firstKey, value);
}
