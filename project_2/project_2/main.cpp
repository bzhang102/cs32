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

//// MARK: REQ 4
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

    // Update Test Cases
    assert(m.update("Rachel", 2.2));
    assert(!m.update("Jon", 1));
    assert(m.size() == 4);

    // InsertOrUpdate Test Cases
    assert(m.insertOrUpdate("Brayden", 4.4));
    assert(m.insertOrUpdate("Jon", 5));

    // Erase Test Cases
    assert(m.erase("Brayden"));
    assert(!m.erase("Andrew"));
    assert(m.size() == 4);

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
    Map m5;
    assert(m5.insert("Fred", 321));
    assert(!merge(m3, m5, result));
    assert(result.size() == 2);

    // Reassign Test Cases
    Map dance;
    assert(dance.insert("Fred", 1));
    assert(dance.insert("Ethel", 2));
    assert(dance.insert("Lucy", 3));
    assert(dance.insert("Ricky", 4));
    Map scrambled;
    assert(scrambled.insert("Love", 92523));
    reassign(dance, scrambled);
    ValueType fredNum;
    ValueType ethelNum;
    ValueType lucyNum;
    ValueType rickyNum;
    assert(scrambled.get("Fred", fredNum));
    assert(scrambled.get("Ethel", ethelNum));
    assert(scrambled.get("Lucy", lucyNum));
    assert(scrambled.get("Ricky", rickyNum));
    assert(fredNum != 1 && ethelNum != 2 && lucyNum != 3 && rickyNum != 4);
    assert(fredNum != ethelNum != lucyNum != rickyNum);

    std::cerr << "All Tests Passed :D" << std::endl;
}

//// MARK: RACHEL'S TEST CASES
//using namespace std;
//
//int main () {
//    // MARK: Smallbergs's Test Cases
//    Map msd; // KeyType is std::string, ValueType is double
//    assert(msd.insert("ccc", 80));
//    assert(msd.insert("aaa", 40));
//    assert(msd.insert("ddd", 60));
//    assert(msd.insert("bbb", 20));
//    KeyType k = "xxx";
//    ValueType v;
//    assert(!msd.get(4, k, v)  &&  k == "xxx");  // x is unchanged
//    assert(msd.get(1, k, v)  &&  k == "bbb");   // "bbb" is greater than exactly 1 item
//
//    /** merge()*/
//    Map names;
//    assert(names.insert("Fred", 123));
//    assert(names.insert("Ethel", 456));
//    assert(names.insert("Lucy",789));
//    Map names1;
//    assert(names1.insert("Lucy", 789));
//    assert(names1.insert("Ricky", 321));
//    Map result;
//    assert(merge(names, names1, result));
//    assert(result.size() == 4 && result.get(0, k, v) && k == "Ethel" && v == 456 && result.get(1, k, v) && k == "Fred" && v == 123 && result.get(2, k, v) && k == "Lucy" && v == 789 && result.get(3, k, v) && k == "Ricky" && v == 321);
//    names1.insertOrUpdate("Lucy",654);
//    assert(!merge(names, names1, result));
//    assert(result.size() == 3 && result.get(0, k, v) && k == "Ethel" && v == 456 && result.get(1, k, v) && k == "Fred" && v == 123 && result.get(2, k, v) && k == "Ricky" && v == 321);
//
//    /** reassign() */
//    Map reassignResult;
//    assert(names.insert("Ricky", 321));
//    reassign(names, reassignResult);
//    KeyType k1, k2, k3;
//    ValueType v1, v2, v3;
//    assert(reassignResult.size() == 4 && reassignResult.get(0, k, v) && reassignResult.get(1, k1, v1) && reassignResult.get(2, k2, v2) && reassignResult.get(3, k3, v3) && v != v1 != v2 != v3 && v != 456 && v1 != 123 && v2 != 789 && v3 != 321);
//
//    assert(names.erase("Ricky"));
//    assert(names.insertOrUpdate("Lucy", 456));
//    reassign(names, reassignResult);
//    assert(reassignResult.size() == 3 && reassignResult.get(0, k, v) && reassignResult.get(1, k1, v1) && reassignResult.get(2, k2, v2) && ((v == 123 && v1 == 456 && v2 == 456) || (v == 456 && v1 == 456 && v2 == 123)));
//
//    // MARK: Rachel's Test Cases
//
//    KeyType key = "";
//    ValueType value = -1;
//
//    /** insert() */
//    Map test;
//    assert(test.insert("a", 23));
//    assert(test.insert("b", 46));
//    assert(test.insert("c", 93));
//    assert(!test.insert("c", 1)); // should not insert if the key already exists
//
//    /**Map(const Map& other)**/
//    Map cpy = Map(test);
//
//    /** update() */
//    assert(test.update("c", 7));
//    assert(test.get("c", value));
//    assert(value == 7);
//
//    /** erase() */
//    msd.erase("b"); // erase
//    assert(!msd.get("b", value) && value == 7);
//
//    /** swap() */
//    Map test1; // swap test and test1
//    assert(test1.insert("d", 109));
//    assert(test1.insert("e", 58));
//    test.swap(test1);
//    assert(test.get(0, key, value) && key == "d" && value == 109);
//    assert(test.get(1, key, value) && key == "e" && value == 58);
//    cerr << "Passed all test cases." << endl;
//}


//// BRAYDEN'S TEST CASES
//using namespace std;
//
//int main() {
//    //MARK: Empty/Size
//    Map empty;
//    assert(empty.size() == 0);
//    assert(empty.empty());
//
//    //MARK: Insert, Update, insertOrUpdate
//    Map IU;
//    assert(IU.insert("A", 1));
//    assert(IU.insert("B", 2));
//    assert(IU.update("B", 3));
//    assert(!IU.insert("A", 3));
//    assert(!IU.update("C", 3));
//    assert(IU.insertOrUpdate("C", 3));
//
//    //MARK: Erase, Contains, Get, Get
//    Map ECG;
//    ECG.insert("A", 1);
//    ECG.insert("B", 2);
//    ECG.insert("CCC", 9);
//    assert(ECG.contains("CCC"));
//    assert(!ECG.contains("C"));
//    assert(ECG.erase("CCC"));
//    assert(!ECG.erase("C"));
//    assert(!ECG.contains("CCC"));
//    assert(!ECG.contains("C"));
//    ValueType vECG;
//    assert(ECG.get("A", vECG) && vECG == 1);
//    assert(!ECG.get("AAA", vECG) && vECG == 1);
//    KeyType kECG;
//    assert(ECG.get(1, kECG, vECG) && kECG == "B" && vECG == 2);
//    assert(!ECG.get(2, kECG, vECG) && kECG == "B" && vECG == 2);
//    assert(ECG.get(0, kECG, vECG) && kECG == "A" && vECG == 1);
//
//    //MARK: Swap
//    Map A;
//    Map B;
//    KeyType kS;
//    ValueType vS;
//    A.insert("A", 1);
//    A.swap(B);
//    assert(B.size() == 1 && A.size() == 0);
//    assert(B.get(0, kS, vS) && kS == "A" && vS == 1);
//    A.insert("A", 2);
//    A.insert("B", 3);
//    B.erase("A");
//    B.insert("B", 2);
//    B.swap(A);
//    assert(A.size() == 1 && B.size() == 2);
//    assert(A.get(0, kS, vS) && kS == "B" && vS == 2);
//    assert(B.get(0, kS, vS) && kS == "A" && vS == 2);
//    assert(B.get(1, kS, vS) && kS == "B" && vS == 3);
//    assert(!B.get(2, kS, vS));
//
//    //MARK: Copy, Assignment
//    B.erase("B");
//    B.erase("A");
//    A.erase("B");
//    assert(A.size() == 0 && B.size() == 0);
//
//    Map C = A;
//    B.insert("B", 1);
//    Map D = B;
//    D.insert("D", 2);
//    assert(A.size() == 0 && C.size() == 0 && B.size() == 1 && D.size() == 2);
//    C = D;
//    assert(C.size() == 2);
//    C.insert("C", 5);
//    assert(C.size() == 3 && D.size() == 2);
//
//    //MARK: Merge
//    Map m1;
//    Map m2;
//    Map res;
//    KeyType kM;
//    ValueType vM;
//    assert(m1.empty() && m2.empty() && res.empty());
//    assert(merge(m1, m2, res));
//    assert(m1.empty() && m2.empty() && res.empty());
//    m1.insert("A", 1.0);
//    assert(merge(m1, m2, res));
//    assert(res.size() == 1 && res.get(0, kM, vM) && kM == "A" && vM == 1.0);
//    m2.insert("B", 1.0);
//    res.insert("BBB", 3);
//    assert(merge(m1, m2, res));
//    assert(res.size() == 2 && res.contains("A") && res.contains("B") && !res.contains("C"));
//    m1.insert("B", 2.0);
//    m1.insert("C", 1.0);
//    assert(!merge(m1, m2, res));
//    assert(res.size() == 2 && res.contains("A") && res.contains("C") && !res.contains("B"));
//    m2.insert("C", 1.0);
//    m1.erase("B");
//    assert(merge(m1, m2, res));
//    assert(res.size() == 3 && res.contains("A") && res.contains("C") && res.contains("B"));
//    assert(merge(m1, m1, res));
//    assert(res.size() == 2);
//    assert(res.contains("A"));
//    assert(res.contains("C"));
//
//    //MARK: Reassign
//    Map r1;
//    Map r2;
//    Map r3;
//    KeyType kR;
//    ValueType vR;
//    reassign(r1, r2);
//    assert(r1.size() == 0 && r2.size() == 0);
//    r1.insert("A", 1.0);
//    reassign(r1, r2);
//    assert(r1.size() == 1 && r2.size() == 1);
//    assert(r2.contains("A"));
//    r1.insert("B", 2.0);
//    r1.insert("C", 3.0);
//    reassign(r1, r2);
//    assert(r2.size() == 3);
//    assert(r2.get("A", vR) && vR != 1.0);
//    assert(r2.get("B", vR) && vR != 2.0);
//    assert(r2.get("C", vR) && vR != 3.0);
//    assert(!r2.get("D", vR) && vR != 3.0);
//    reassign(r3, r3);
//    assert(r3.size() == 0);
//    reassign(r1, r1);
//    assert(r1.size() == 3);
//
//    //MARK: Random Cases
//    Map m;
//    assert(m.insert("Fred", 123));
//    assert(m.insert("Ethel", 456));
//    assert(m.size() == 2);
//    assert(m.erase("Ethel"));
//    ValueType v = 3;
//    assert(m.get("Fred", v) && v == 123);
//    assert(m.update("Fred", 333));
//    assert(m.get("Fred", v) && v == 333);
//    assert(m.contains("Fred"));
//    assert(m.size() == 1);
//    assert(m.insert("A", 13));
//    assert(m.insert("B", 12));
//    assert(m.insert("C", 1));
//    assert(m.size() == 4);
//    assert(m.get("C", v) && v == 1);
//    assert(m.update("C", 4));
//    assert(m.erase("B"));
//    assert(m.size() == 3);
//    assert(m.get("C", v) && v == 4);
//    assert(m.get("A", v) && v == 13);
//    Map msd;  // KeyType is std::string, ValueType is double
//
//    msd.insert("aaa", 133);
//    msd.insert("bbb", 20);
//    msd.insert("ccc", 80);
//    msd.insert("ddd", 60);
//
//    KeyType k = "xxx";
//    assert(!msd.get(4, k, v)  &&  k == "xxx");
//    assert(msd.get(1, k, v)  &&  k == "bbb");
//
//    cout << "Passed all test cases!" << endl;
//}

//// MARK: DIVU'S TEST CASES
using namespace std;

//int main() {
//    Map m;
//    assert(m.insert("Fred", 123));
//    assert(m.insert("Ethel", 456));
//    assert(m.size() == 2);
//    ValueType vv = 42;
//    assert(!m.get("Lucy", vv)  &&  vv == 42);
//    assert(m.get("Fred", vv)  &&  vv == 123);
//    vv = 42;
//    KeyType x = "Lucy";
//    assert(m.get(0, x, vv)  &&  x == "Ethel"  &&  vv == 456);
//    KeyType x2 = "Ricky";
//    assert(m.get(1, x2, vv)  &&  x2 == "Fred"  &&  vv == 123);
//
//    Map msd;  // KeyType is std::string, ValueType is double
//    msd.insert("ccc", 80);
//    msd.insert("aaa", 40);
//    msd.insert("ddd", 60);
//    msd.insert("bbb", 20);
//
//    KeyType k = "xxx";
//    ValueType v;
//    assert(msd.get(2, k, v)  &&  k == "ccc");  // x is unchanged
//    assert(msd.get(1, k, v)  &&  k == "bbb");
//    msd.insert("Fred", 1273);
//
//    Map q(msd);
//
//    q.dump();
//    std::cerr <<"\n";
//    //q.erase("Fred");
//
//    Map l;
//    l = q;
//
//    l.dump();
//    std::cerr <<"\n";
//
//    //msd.dump();
//    std::cerr <<"\n";
//    msd.erase("Fred");
//    msd.dump();
//    std::cerr <<"success"<< std:: endl;
//    std::cerr << std::endl;;
//
//    msd.erase("aaa");
//    msd.dump();
//    std::cerr <<"success"<< std:: endl;
//    std::cerr << std::endl;;
//
//    msd.erase("ccc");
//    msd.dump();
//    std::cerr <<"success"<< std:: endl;
//    std::cerr << std::endl;;
//
//    msd.erase("bbb");
//    msd.dump();
//    std::cerr <<"success"<< std:: endl;
//    std::cerr << std::endl;;
//    assert(msd.size() == 1);
//
//
//    msd.erase("ddd");
//    msd.dump();
//    std::cerr <<"success"<< std:: endl;
//    std::cerr << std::endl;;
//
//    std::cerr << msd.erase("Fred");
//    std::cerr <<" success"<< std:: endl;
//
//    msd.dump();
//
//    assert(msd.empty());
//    assert(msd.size() ==0);
//
//    //q.dump();
//    std::cerr <<"\n";
//
//    //l.dump();
//    merge(l, q, l);
//    std::cerr <<"L"<< endl;
//    l.dump();
//    std::cerr <<"\n";
//
//    reassign(l, l);
//    std::cerr <<"L reassigned"<< endl;
//    l.dump();
//    std::cerr <<"\n";
//
//    std::cerr <<"Q"<< endl;
//    q.dump();
//    std::cerr <<"\n";
//
//    l.swap(q);
//    std::cerr <<"L should now look like Q"<< endl;
//
//    l.dump();
//    std::cerr <<"\n";
//    std::cerr <<"Q should now look like previous L"<< endl;
//    q.dump();
//
//    l = q;
//    std::cerr <<"\n";
//    std::cerr <<"L should now look like new Q"<< endl;
//    l.dump();
//
//    q.erase("Fred");
//    std::cerr <<"\n";
//    std::cerr <<"Q should not have Fred"<< endl;
//    q.dump();
//    std::cerr <<"\n";
//    std::cerr <<"L should look the same"<< endl;
//    l.dump();
//
//    cerr << "Passed all tests" << endl;
//}
