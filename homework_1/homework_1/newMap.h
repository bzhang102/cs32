#ifndef newMap_h
#define newMap_h

#include <string>

const int DEFAULT_MAX_SIZE = 150;
using KeyType = std::string;
using ValueType = double;

class Map {
public:
    Map();
    Map(int size);
    Map(const Map& other);
    ~Map();
    Map& operator=(const Map& other);

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
    void dump() const;
private:
    struct Item {
        KeyType key;
        ValueType value;
    };
    Item* m_items;
    int m_numItems;
    int m_capacity;
};
#endif
