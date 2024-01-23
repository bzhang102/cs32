#include "newMap.h"
#include <string>
#include <cassert>
#include <iostream>

using namespace std;

int main() {
    Map a(1000);   // a can hold at most 1000 key/value pairs
    Map b(5);      // b can hold at most 5 key/value pairs
    Map c;         // c can hold at most DEFAULT_MAX_ITEMS key/value pairs
    KeyType k[6] = {"a", "b", "c", "d", "e", "f"};
    ValueType v  = 1.1;

    // No failures inserting pairs with 5 distinct keys into b
    for (int n = 0; n < 5; n++)
        assert(b.insert(k[n], v));

    // Failure if we try to insert a pair with a sixth distinct key into b
    assert(!b.insert(k[5], v));

    // When two Maps' contents are swapped, their capacities are swapped
    // as well:
    a.swap(b);
    assert(!a.insert(k[5], v)  &&  b.insert(k[5], v));

    Map mm;
    mm.insert("Little Ricky", 3.206);
    mm.insert("Ethel", 3.538);
    mm.insert("Ricky", 3.350);
    mm.insert("Lucy", 2.956);
    mm.insert("Ethel", 3.538);
    mm.insert("Fred", 2.956);
    mm.insert("Lucy", 2.956);
    assert(mm.size() == 5);  // duplicate "Ethel" and "Lucy" were not added
    string x;
    double y;
    mm.get(0, x, y);
    assert(x == "Ethel");  // "Ethel" is greater than exactly 0 items in mm
    mm.get(4, x, y);
    assert(x == "Ricky");  // "Ricky" is greater than exactly 4 items in mm
    mm.get(2, x, y);
    assert(x == "Little Ricky");  // "Little Ricky" is greater than exactly 2 items in mm
    assert(y == 3.206);  // the value corresponding to the key "Little Ricky"

    Map m1;
    m1.insert("Fred", 2.956);
    Map m2;
    m2.insert("Lucy", 2.956);
    m2.insert("Ethel", 3.538);
    m1.swap(m2);
    assert(m1.size() == 2  &&  m1.contains("Ethel")  &&  m1.contains("Lucy"));

    Map gpas;
    gpas.insert("Fred", 2.956);
    assert(!gpas.contains(""));
    gpas.insert("Ethel", 3.538);
    gpas.insert("", 4.000);
    gpas.insert("Lucy", 2.956);
    assert(gpas.contains(""));
    gpas.erase("Fred");
    assert(gpas.size() == 3  &&  gpas.contains("Lucy")  &&  gpas.contains("Ethel")  &&
           gpas.contains(""));
    string l;
    double m;
    assert(gpas.get(1, l, m)  &&  l == "Ethel");
    assert(gpas.get(0, l, m)  &&  l == "");

    cerr << "New Map Tests Passed" << endl;
}
