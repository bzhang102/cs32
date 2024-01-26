#include "Map.h"
#include <iostream>
#include <cassert>

//// MARK: REQ 1
//int main() {
//    Map msd;  // KeyType is std::string, ValueType is double
//    msd.insert("ccc", 80);
//    msd.insert("aaa", 40);
//    msd.insert("ddd", 60);
//    msd.insert("bbb", 20);
//    KeyType k = "xxx";
//    ValueType v;
//    assert(!msd.get(4, k, v)  &&  k == "xxx");  // x is unchanged
//    assert(msd.get(1, k, v)  &&  k == "bbb");   // "bbb" is greater than
//                                                // exactly 1 item
//}

//// MARK: REQ 2
//#include <type_traits>
//
//#define CHECKTYPE(c, f, r, a)  \
//{  \
//static_assert(std::is_same<decltype(&c::f), r (c::*)a>::value, \
//"You did not declare " #c "::" #f " as the Project 2 spec does");  \
//auto p = static_cast<r (c::*)a>(&c::f);  \
//(void) p;  \
//}
//#define CHECKTYPENONMEMBER(f, t)  \
//{  \
//static_assert(std::is_same<decltype(f), t>::value, \
//"You did not declare " #f " as the Project 2 spec does");  \
//auto p = static_cast<std::add_pointer<t>::type>(f);  \
//(void) p;  \
//}
//
//static_assert(std::is_default_constructible<Map>::value,
//              "Map must be default-constructible.");
//static_assert(std::is_copy_constructible<Map>::value,
//              "Map must be copy-constructible.");
//static_assert(std::is_copy_assignable<Map>::value,
//              "Map must be assignable.");
//static_assert(std::is_same<decltype(*(Map*)(0) = Map()), Map&>::value,
//              "Map::operator= return type should be Map&");
//
//void thisFunctionWillNeverBeCalled()
//{
//    CHECKTYPE(Map, empty,          bool, () const);
//    CHECKTYPE(Map, size,           int , () const);
//    CHECKTYPE(Map, insert,         bool, (const KeyType&, const ValueType&));
//    CHECKTYPE(Map, update,         bool, (const KeyType&, const ValueType&));
//    CHECKTYPE(Map, insertOrUpdate, bool, (const KeyType&, const ValueType&));
//    CHECKTYPE(Map, erase,          bool, (const KeyType&));
//    CHECKTYPE(Map, contains,       bool, (const KeyType&) const);
//    CHECKTYPE(Map, swap,           void, (Map&));
//
//    CHECKTYPENONMEMBER(merge,    bool(const Map&, const Map&, Map&));
//    CHECKTYPENONMEMBER(reassign, void(const Map&, Map&));
//    { auto p = static_cast<bool (Map::*)(const KeyType&, ValueType&) const>(&Map::get); (void) p; };
//    { auto p = static_cast<bool (Map::*)(int, KeyType&, ValueType&) const>(&Map::get); (void) p; };
//}
//
//int main()
//{}

//// MARK: REQ 3
//using namespace std;
//
//void test()
//{
//    Map m;
//    assert(m.insert("Fred", 123));
//    assert(m.insert("Ethel", 456));
//    assert(m.size() == 2);
//    ValueType v = 42;
//    assert(!m.get("Lucy", v)  &&  v == 42);
//    assert(m.get("Fred", v)  &&  v == 123);
//    v = 42;
//    KeyType x = "Lucy";
//    assert(m.get(0, x, v)  &&  x == "Ethel"  &&  v == 456);
//    KeyType x2 = "Ricky";
//    assert(m.get(1, x2, v)  &&  x2 == "Fred"  &&  v == 123);
//}
//
//int main()
//{
//    test();
//    cout << "Passed all tests" << endl;
//}

// MARK: REQ 4
//using namespace std;
//
//void test()
//{
//    Map m;
//    assert(m.insert(10, "diez"));
//    assert(m.insert(20, "veinte"));
//    assert(m.size() == 2);
//    ValueType v = "cuarenta y dos";
//    assert(!m.get(30, v)  &&  v == "cuarenta y dos");
//    assert(m.get(10, v)  &&  v == "diez");
//    v = "cuarenta y dos";
//    KeyType x = 30;
//    assert(m.get(0, x, v)  &&  x == 10  &&  v == "diez");
//    KeyType x2 = 40;
//    assert(m.get(1, x2, v)  &&  x2 == 20  &&  v == "veinte");
//}
//
//int main()
//{
//    test();
//    cout << "Passed all tests" << endl;
//}

//// MARK: BRANDON'S TEST CASES
int main() {
    Map m;

    // Empty Map Test Cases
    assert(m.size() == 0);
    assert(m.empty());

    // Insert Test Cases
    assert(m.insert("Brandon", 1.1));
    assert(m.insert("Rachel", 2));
    assert(m.insert("Sanjay", 3));
    assert(m.insert("Brayden", 4));
    assert(!m.insert("Brandon", 1.1));
    assert(m.size() == 4);
    m.dump();

    // Update Test Cases
    assert(m.update("Rachel", 2.2));
    assert(!m.update("Jon", 1));
    assert(m.size() == 4);
    m.dump();

    // InsertOrUpdate Test Cases
    assert(m.insertOrUpdate("Brayden", 4.4));
    assert(m.insertOrUpdate("Jon", 5));
    m.dump();

    // Erase Test Cases
    assert(m.erase("Brayden"));
    assert(!m.erase("Andrew"));
    assert(m.size() == 4);
    m.dump();

    // Contains Test Cases
    assert(m.contains("Brandon"));
    assert(!m.contains(""));
    assert(!m.contains("Brayden"));

    // 1st Get Test Cases
    KeyType key1 = "Ellen";
    ValueType value1 = 9.99;
    assert(!m.get(key1, value1));
    assert(value1 == 9.99);
    key1 = "Rachel";
    assert(m.get(key1, value1));
    assert(value1 == 2.2);

    // 2nd Get Test Cases
    KeyType key2 = "Katie";
    ValueType value2 = 9.99;
    assert(!m.get(-1, key2, value2));
    assert(!m.get(m.size(), key2, value2));
    assert(key2 == "Katie" && value2 == 9.99);
    assert(m.get(2, key2, value2));
    assert(key2 == "Rachel" && value2 == 2.2);

    // Swap Test Cases
    Map m1;
    assert(m1.insert("a", 1));
    assert(m1.insert("b", 2));
    Map m2;
    assert(m2.insert("x", 3));
    m1.swap(m2);
    assert(m1.size() == 1 && m2.size() == 2);
    KeyType key3 = "a";
    ValueType value3;
    assert(!m1.get(key3, value3));
    assert(m2.get(key3, value3) && value3 == 1);

    // Merge Test Cases
    Map m3;
    assert(m3.insert("Fred", 123));
    assert(m3.insert("Ethel", 456));
    assert(m3.insert("Lucy", 789));
    Map m4;
    assert(m4.insert("Lucy", 789));
    assert(m4.insert("Ricky", 321));
    Map result;
    assert(result.insert("Your Mother", 69420));
    assert(merge(m3, m4, result));
    assert(result.size() == 4);
    m3.dump();
    m4.dump();
    result.dump();
    Map m5;
    assert(m5.insert("Fred", 321));
    assert(!merge(m3, m5, result));
    assert(result.size() == 2);
    result.dump();

    std::cerr << "All Tests Passed :D" << std::endl;
}
