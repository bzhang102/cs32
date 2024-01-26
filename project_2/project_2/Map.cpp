#include "Map.h"

// Constructors, Destructor, Assignment Operator
Map::Map() {
    // construct dummy node and link it to itself
    m_dummy = new Node(m_dummy, m_dummy);
    m_size = 0;
}
Map::~Map() {
    // delete all nodes
    Node* p = m_dummy;
    Node* q;
    for(int i = 0; i <= m_size; i++) { // <= to delete dummy node as well
        q = p->next;
        delete p;
        p = q;
    }
}
Map::Map(const Map& src) {
    // construct dummy node and link it to itself
    m_dummy = new Node(m_dummy, m_dummy);

    // iterate through all nodes in src and insert new copies into this map
    m_size = src.m_size;
    Node* p = src.m_dummy->next;
    for(int i = 0; i < m_size; i++) {
        insert(p->key, p->value);
    }
}
Map& Map::operator=(const Map& src) {
    // anti-aliasing
    if(this == &src) {
        return *this;
    }

    // delete all nodes except dummy node
    Node* p = m_dummy;
    Node* q;
    for(int i = 0; i < m_size; i++) { // < to NOT delete dummy node
        q = p->next;
        delete p;
        p = q;
    }

    // copy over all nodes from src
    m_size = src.m_size;
    p = src.m_dummy->next;
    for(int i = 0; i < m_size; i++) {
        insert(p->key, p->value);
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
    Node* p = new Node(key, value, m_dummy->prev, m_dummy->next);

    // links nodes on either side to new node
    m_dummy->prev->next = p;
    m_dummy->prev = p;
    
    // increments size counter
    m_size++;

    return true;
}
bool Map::update(const KeyType& key, const ValueType& value) {
    Node* p = m_dummy->next;
    for(int i = 0; i < m_size; i++) {
        // updates value at key if found
        if(p->key == key) {
            p->value = value;
            return true;
        }
        p = p->next;
    }
    // if all nodes exhausted, return false
    return false;
}
bool Map::insertOrUpdate(const KeyType& key, const ValueType& value) {
    Node* p = m_dummy->next;
    for(int i = 0; i < m_size; i++) {
        //updates value at key if found
        if(p->key == key) {
            p->value = value;
            return true;
        }
        p = p->next;
    }
    // if all nodes exhausted, insert new value
    return insert(key, value);
}
bool Map::erase(const KeyType& key) {
    Node* p = m_dummy->next;
    for(int i = 0; i < m_size; i++) {
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
        p = p->next;
    }
    // if all nodes exhausted, return false
    return false;
}
bool Map::contains(const KeyType& key) const {
    Node* p = m_dummy->next;
    for(int i = 0; i < m_size; i++) {
        // if key found, return true
        if(p->key == key) {
            return true;
        }
        p = p->next;
    }
    // if all nodes exhausted, return false
    return false;
}
bool Map::get(const KeyType& key, ValueType& value) const {
    Node* p = m_dummy->next;
    for(int i = 0; i < m_size; i++) {
        // if key found, reassign value to stored value
        if(p->key == key) {
            value = p->value;
            return true;
        }
        p = p->next;
    }
    // if all nodes exhausted, return false
    return false;
}
bool Map::get(int i, KeyType& key, ValueType& value) const {
    // checks for valid i
    if(i >= 0 && i < m_size) {
        // variables declared outside loop to save space
        int count = 0;
        Node* outer = m_dummy->next;
        Node* inner = m_dummy->next;

        // iterate through each node once
        for(int j = 0; j < m_size; j++) {
            // compare inner node with outer node
            for(int k = 0; k < m_size; k++) {
                // count number of nodes that contain nodes with a key < outer's key
                if(outer->key > inner->key) {
                    count++;
                }
                // inner pointer should always return to the dummy node
                inner = inner->next;
            }

            // if key of outer is strictly greater than i keys, return that pair
            if(count == i) {
                key = outer->key;
                value = outer->value;
                return true;
            }

            // increment outer pointer, reset count
            count = 0;
            outer = outer->next;
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

//Non Member Functions
bool merge(const Map& m1, const Map& m2, Map& result) {
    // state bool to track if merge conflict occurs
    bool state = true;

    // copy m1 into result
    result = Map(m1);

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
