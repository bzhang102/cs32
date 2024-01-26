#ifndef Map_h
#define Map_h

#include <string>

using KeyType = std::string;
using ValueType = double;

class Map
{
public:
    Map();
    ~Map();
    Map(const Map& src);
    Map& operator=(const Map& src);

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
    struct Node {
        KeyType key;
        ValueType value;
        Node* next;
        Node* prev;
    };
    Node* head;
    Node* tail;

    int m_size;
};

#endif
