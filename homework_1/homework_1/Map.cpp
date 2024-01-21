#include <iostream>

#include "Map.h"

using namespace std;

Map::Map() {
    m_size = 0;
}
// Create an empty map (i.e., one whose size() is 0).

bool Map::empty() const {
    return m_size == 0;
}
// Return true if the map is empty, otherwise false.

int Map::size() const {
    return m_size;
}
// Return the number of key/value pairs in the map.

bool Map::insert(const KeyType& key, const ValueType& value) {
    if(!contains(key) && m_size < DEFAULT_MAX_ITEMS) {
        items[m_size].key = key;
        items[m_size].value = value;
        m_size++;
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
    for(int i = 0; i < m_size; i++) {
        if(items[i].key == key) {
            items[i].value = value;
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
    for(int i = 0; i < m_size; i++) {
        if(items[i].key == key) {
            items[i].value = value;
            return true;
        }
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
    for(int i = 0; i < m_size; i++) {
        if(items[i].key == key) {
            items[i] = items[m_size - 1];
            m_size--;
            return true;
        }
    }
    return false;
}
// If key is equal to a key currently in the map, remove the key/value
// pair with that key from the map and return true.  Otherwise, make
// no change to the map and return false.

bool Map::contains(const KeyType& key) const {
    for(int i = 0; i < m_size; i++) {
        if(items[i].key == key) {
            return true;
        }
    }
    return false;
}
// Return true if key is equal to a key currently in the map, otherwise
// false.

bool Map::get(const KeyType& key, ValueType& value) const {
    for(int i = 0; i < m_size; i++) {
        if(items[i].key == key) {
            value = items[i].value;
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
        KeyType curr;
        int count = 0;
        for(int j = 0; j < m_size; j++) {
            curr = items[j].key;
            for(int k = 0; k < m_size; k++) {
                if(curr > items[k].key) {
                    count++;
                }
            }
            if(count == i) {
                key = curr;
                value = items[j].value;
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
//    Item temp;
//    for(int i = 0; i < max(size(), other.size()); i++) {
//        temp = items[i];
//        items[i] = other.items[i];
//        other.items[i] = temp;
//    }
//    int n = numItems;
//    numItems = other.numItems;
//    other.numItems = n;

    // MARK: VALID SOLUTION?
    Map temp = *this;
    *this = other;
    other = temp;
}
// Exchange the contents of this map with the other one.


void Map::dump() const {
    for(int i = 0; i < m_size; i++) {
        cerr << items[i].key << ", " << items[i].value << endl;
    }
}
