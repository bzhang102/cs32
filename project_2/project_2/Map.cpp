#include "Map.h"

Map::Map() {
    head = nullptr;
    tail = nullptr;
    m_size = 0;
}
Map::~Map() {
    if(head != nullptr) {

    }
}
Map::Map(const Map& src) {

}
Map& Map::operator=(const Map& src) {
    return *this;
}

bool Map::empty() const {
    return m_size == 0;
}
int Map::size() const {
    return m_size;
}
bool Map::insert(const KeyType& key, const ValueType& value) {
    return false;
}
bool Map::update(const KeyType& key, const ValueType& value) {
    return false;
}
bool Map::insertOrUpdate(const KeyType& key, const ValueType& value) {
    return false;
}
bool Map::erase(const KeyType& key) {
    return false;
}
bool Map::contains(const KeyType& key) const {
    return false;
}
bool Map::get(const KeyType& key, ValueType& value) const {
    return false;
}
bool Map::get(int i, KeyType& key, ValueType& value) const {
    return false;
}
void Map::swap(Map& other) {

}

//Non Member Functions
bool merge(const Map& m1, const Map& m2, Map& result) {
    return false;
}
void reassign(const Map& m, Map& result) {

}
