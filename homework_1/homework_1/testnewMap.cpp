// newMap Tests
#include "newMap.h"
#include <cassert>
#include <iostream>

using namespace std;

int main() {
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
    m1.dump();
    m2.dump();
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
    string k;
    double v;
    assert(gpas.get(1, k, v)  &&  k == "Ethel");
    assert(gpas.get(0, k, v)  &&  k == "");

    cerr << "New Map Tests Passed" << endl;
}
