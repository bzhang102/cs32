#ifndef Map_h
#define Map_h

#include <string>

using KeyType = char;
using ValueType = int;

class Map {
public:
    Map();
    Map(const Map& src);
    ~Map();
    Map& operator=(const Map& src);

    bool empty() const;
    int size() const;
    void dump();

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
        inline
        Node() : prev(nullptr), next(nullptr) {}
        inline
        Node(KeyType k, ValueType v, Node* p, Node* n) : key(k), value(v), prev(p), next(n) {}
        KeyType key;
        ValueType value;
        Node* prev;
        Node* next;
    };
    Node* m_dummy;
    int m_size;
};

bool merge(const Map& m1, const Map& m2, Map& result);
void reassign(const Map& m, Map& result);

#endif
