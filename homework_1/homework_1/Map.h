#ifndef Map_h
#define Map_h

#include <string>

const int DEFAULT_MAX_ITEMS = 150;
using KeyType = std::string;
using ValueType = double;

class Map {
public:
    Map();
    bool empty() const;
    int size() const;
    bool insert(const KeyType& key, const ValueType& value);
    bool update(const KeyType& key, const ValueType& value);
    bool insertOrUpdate(const KeyType& key, const ValueType& value);
    bool erase(const KeyType& key);
    bool contains(const KeyType& key) const;
    bool get(const KeyType& key, ValueType& value) const;
    bool get(int i, KeyType& key, ValueType& value) const;
    void swap(Map& other);
private:
    struct Item {
        KeyType key;
        ValueType value;
    };
    Item m_items[DEFAULT_MAX_ITEMS];
    int m_numItems;
};
#endif
