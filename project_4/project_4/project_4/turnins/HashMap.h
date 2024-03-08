#ifndef HASHMAP_H
#define HASHMAP_H

#include <vector>
#include <list>
#include <string>

template <typename T>
class HashMap {
public:
    HashMap(double max_load = 0.75);
    ~HashMap();
    int size() const { return m_size; }

    void insert(const std::string& key, const T& value);
    T& operator[](const std::string& key) { return find(key); }

    // Const
    const T* find(const std::string& key) const;
    // Nonconst
    T* find(const std::string& key) { return const_cast<T*>(this->find(key)); }

    // No copying or assigning
    HashMap(const HashMap&) = delete;
    HashMap& operator=(const HashMap&) = delete;
private:
    struct Pair {
        Pair(const std::string& key, const T& value): m_key(key), m_value(value) {}
        std::string m_key;
        T m_value;
    };

    std::vector<std::list<Pair*>> m_buckets;
    int m_size;
    int m_nBuckets;
    double m_maxLoad;

    int hash(const std::string& key) const;
    void rehash();
};

//// MARK: public

// Constructor
template <typename T>
HashMap<T>::HashMap(double max_load)
: m_buckets(10), m_size(0), m_nBuckets(10) {
    // maxLoad sanity check
    m_maxLoad = (max_load > 0) ? max_load : 0.75;
}

// Destructor
template <typename T>
HashMap<T>::~HashMap() {
    // for each bucket
    for(auto bucket : m_buckets) {
        // for each object in the bucket
        for(auto pair : bucket) {
            delete pair;
        }
    }
}

// insert()
template <typename T>
void HashMap<T>::insert(const std::string& key, const T& value) {
    m_size++;
    // if oversize, rehash
    if(m_size >= m_maxLoad) { rehash(); }

    // add to correct bucket
    m_buckets[hash(key)].push_back(new Pair(key, value));
}

// find()
template <typename T>
const T* HashMap<T>::find(const std::string& key) const {
    // iterate through corresponding bucket
    for(auto obj : *m_buckets[hash(key)]) {
        if(obj->m_key == key) {
            return &obj->m_val;
        }
    }

    // not found
    return nullptr;
}

//// MARK: private

// hash()
template <typename T>
int HashMap<T>::hash(const std::string& key) const {
    return std::hash<std::string>()(key) % m_nBuckets;
}

// rehash()
template <typename T>
void HashMap<T>::rehash() {
    // resize to two
    m_nBuckets *= 2;
    // create new vector of lists with twice the number of buckets
    std::vector<std::list<Pair*>> newBuckets(m_nBuckets);

    // move all objects into new vector
    for(auto bucket : m_buckets) {
        for(auto obj : bucket) {
            newBuckets[hash(obj->m_key)].pushback(obj);
        }
    }

    // reassign map's vector
    m_buckets = newBuckets;
}
#endif
