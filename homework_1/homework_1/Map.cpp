#include "Map.h"

using namespace std;

Map::Map() {
    m_numItems = 0;
}
// Create an empty map (i.e., one whose size() is 0).

bool Map::empty() const {
    return m_numItems == 0;
}
// Return true if the map is empty, otherwise false.

int Map::size() const {
    return m_numItems;
}
// Return the number of key/value pairs in the map.

bool Map::insert(const KeyType& key, const ValueType& value) {
    if(!contains(key) && m_numItems < DEFAULT_MAX_ITEMS) {
        m_items[m_numItems].key = key;
        m_items[m_numItems].value = value;
        m_numItems++;
        return true;
    }
    return false;
}
// If key is not equal to any key currently in the map and if the
// key/value pair can be added to the map, then do so and return true.
// Otherwise, make no change to the map and return false (indicating
// that either the key is already in the map, or the map has a fixed
// capacity and is full).

bool Map::update(const KeyType& key, const ValueType& value) {
    for(int i = 0; i < m_numItems; i++) {
        if(m_items[i].key == key) {
            m_items[i].value = value;
            return true;
        }
    }
    return false;
}
// If key is equal to a key currently in the map, then make that key no
// longer map to the value that it currently maps to, but instead map to
// the value of the second parameter; in this case, return true.
// Otherwise, make no change to the map and return false.

bool Map::insertOrUpdate(const KeyType& key, const ValueType& value) {
    if(update(key, value)) {
        return true;
    }
    return insert(key, value);
}
// If key is equal to a key currently in the map, then make that key no
// longer map to the value that it currently maps to, but instead map to
// the value of the second parameter; in this case, return true.
// If key is not equal to any key currently in the map, and if the
// key/value pair can be added to the map, then do so and return true.
// Otherwise, make no change to the map and return false (indicating
// that the key is not already in the map and the map has a fixed
// capacity and is full).

bool Map::erase(const KeyType& key) {
    for(int i = 0; i < m_numItems; i++) {
        if(m_items[i].key == key) {
            m_items[i] = m_items[m_numItems - 1];
            m_numItems--;
            return true;
        }
    }
    return false;
}
// If key is equal to a key currently in the map, remove the key/value
// pair with that key from the map and return true.  Otherwise, make
// no change to the map and return false.

bool Map::contains(const KeyType& key) const {
    for(int i = 0; i < m_numItems; i++) {
        if(m_items[i].key == key) {
            return true;
        }
    }
    return false;
}
// Return true if key is equal to a key currently in the map, otherwise
// false.

bool Map::get(const KeyType& key, ValueType& value) const {
    for(int i = 0; i < m_numItems; i++) {
        if(m_items[i].key == key) {
            value = m_items[i].value;
            return true;
        }
    }
    return false;
}
// If key is equal to a key currently in the map, set value to the
// value in the map which the key maps to, and return true.  Otherwise,
// make no change to the value parameter of this function and return
// false.

bool Map::get(int i, KeyType& key, ValueType& value) const {
    if(i >= 0 && i < size()) {
        int count = 0;
        for(int j = 0; j < m_numItems; j++) {
            for(int k = 0; k < m_numItems; k++) {
                if(m_items[j].key > m_items[k].key) {
                    count++;
                }
            }
            if(count == i) {
                key = m_items[j].key;
                value = m_items[j].value;
                return true;
            }
            count = 0;
        }
    }

    return false;
}
// If 0 <= i < size(), copy into the key and value parameters the
// key and value of the key/value pair in the map whose key is strictly
// greater than exactly i keys in the map and return true.  Otherwise,
// leave the key and value parameters unchanged and return false.

void Map::swap(Map& other) {
    Map temp = *this;
    *this = other;
    other = temp;
}
// Exchange the contents of this map with the other one.
