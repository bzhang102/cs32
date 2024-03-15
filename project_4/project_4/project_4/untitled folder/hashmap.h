#ifndef HASHMAP_H
#define HASHMAP_H

#include <vector>
#include <list>
#include <string>

template <typename T>
class HashMap {
public:
    HashMap(double max_load = 0.75);
    ~HashMap() = default;
    int size() const { return m_size; }

    void insert(const std::string& key, const T& value);
    T& operator[](const std::string& key);

    // Const
    const T* find(const std::string& key) const;
    // Nonconst
    T* find(const std::string& key) {
        const auto& hm = *this;
        return const_cast<T*>(hm.find(key));
    }

    // No copying or assigning
    HashMap(const HashMap&) = delete;
    HashMap& operator=(const HashMap&) = delete;
private:
    std::vector<std::list<std::pair<std::string, T>>> m_hashTable;
    int m_size;
    int m_numBuckets;
    double m_maxLoad;

    int hash(const std::string& key) const { return std::hash<std::string>()(key) % m_numBuckets; }
    void rehash();
};

//// MARK: public

// Constructor
template <typename T>
HashMap<T>::HashMap(double max_load)
: m_hashTable(10), m_size(0), m_numBuckets(10) {
    // maxLoad sanity check
    m_maxLoad = (max_load > 0) ? max_load : 0.75;
}

// insert()
template <typename T>
void HashMap<T>::insert(const std::string& key, const T& value) {
    // check for duplicate keys
    for(auto& pair : m_hashTable[hash(key)]) {
        if(pair.first == key) {
            pair.second = value;
            return;
        }
    }
    // resize if oversize
    m_size++;
    if(m_size * 1.0 / m_numBuckets >= m_maxLoad) { rehash(); }
    m_hashTable[hash(key)].push_back(std::make_pair(key, value));
}

// operator[]()
template <typename T>
T& HashMap<T>::operator[](const std::string& key) {
    // if doesn't exist, insert default value
    if(find(key) == nullptr) insert(key, T());
    return *find(key);
}


// find()
template <typename T>
const T* HashMap<T>::find(const std::string& key) const {
    // iterate through corresponding bucket
    for(auto& pair : m_hashTable[hash(key)]) {
        if(pair.first == key) {
            return &pair.second;
        }
    }
    // not found
    return nullptr;
}

//// MARK: private

// rehash()
template <typename T>
void HashMap<T>::rehash() {
    // resize to two
    m_numBuckets *= 2;
    // create new vector of lists with twice the number of buckets
    std::vector<std::list<std::pair<std::string, T>>> newTable(m_numBuckets);
    // move all objects into new vector
    for(auto& bucket : m_hashTable) {
        for(auto& pair : bucket) {
            newTable[hash(pair.first)].push_back(pair);
        }
    }
    // reassign map's vector
    m_hashTable = newTable;
}
#endif
