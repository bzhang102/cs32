// MARK: REQ 1
//#include "Map.h"
//#include <iostream>
//#include <cassert>
//
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

// MARK: REQ 2
//#include "Map.h"
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

// MARK: REQ 3
//#include "Map.h"
//#include <iostream>
//#include <cassert>
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
//#include "Map.h"
//#include <iostream>
//#include <cassert>
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

// MARK: TEST CASES
#include "Map.h"
#include <iostream>
#include <cassert>

int main() {
    Map m;

    // Insert Test Cases
    assert(m.insert("Brandon", 1.1));
    assert(m.insert("Rachel", 2));
    assert(m.insert("Sanjay", 3));
    assert(m.insert("Brayden", 1.1));
    assert(!m.insert("Brandon", 1.1));
    assert(m.size() == 4);
}
