#include <cassert>
#include <iostream>

// Example Implementation
bool somePredicate(double x) {
    return x > 0;
}

// Return true if the somePredicate function returns false for at
// least one of the array elements; return false otherwise.
bool anyFalse(const double a[], int n) {
    return (n <= 0) ? false : (!somePredicate(a[n - 1]) || anyFalse(a, n - 1));
}

// Return the number of elements in the array for which the
// somePredicate function returns false.
int countFalse(const double a[], int n) {
    if(n <= 0) return 0;
    return (!somePredicate(a[n - 1])) ? countFalse(a, n - 1) + 1 : countFalse(a, n - 1);
}

// Return the subscript of the first element in the array for which
// the somePredicate function returns false.  If there is no such
// element, return -1.
int firstFalse(const double a[], int n) {
    if(n <= 0) return -1;
    if(!somePredicate(a[0])) return 0;
    int i = firstFalse(a + 1, n - 1);
    return (i == -1) ? -1 : i + 1;
}

// Return the subscript of the first double in the array that is <=
// all doubles in the array (i.e., return the smallest subscript m such
// that a[m] <= a[k] for all k from 0 to n-1).  If the function is
// told that no doubles are to be considered to be in the array,
// return -1.
int locateMinimum(const double a[], int n) {
    if(n < 0) return -1;
    if(n == 0) return n - 1;
    int minIndex = locateMinimum(a, n - 1);
    return (a[n - 1] <= a[minIndex]) ? n - 1 : minIndex;
}

// If all n2 elements of a2 appear in the n1 element array a1, in
// the same order (though not necessarily consecutively), then
// return true; otherwise (i.e., if the array a1 does not include
// a2 as a not-necessarily-contiguous subsequence), return false.
// (Of course, if a2 is empty (i.e., n2 is 0), return true.)
// For example, if a1 is the 7 element array
//    10 50 40 20 50 40 30
// then the function should return true if a2 is
//    50 20 30
// or
//    50 40 40
// and it should return false if a2 is
//    50 30 20
// or
//    10 20 20
bool includes(const double a1[], int n1, const double a2[], int n2) {
    if(n2 <= 0) return true;
    if(n1 <= 0) return false;
    return (a1[n1 - 1] == a2[n2 - 1]) ? includes(a1, n1 - 1, a2, n2 - 1) : includes(a1, n1 - 1, a2, n2);
}

//int main() {
//    double a[] = {1, 2, 3, 4};
//    double b[] = {};
//    double c[] = {-1, 1, 2, 3};
//    double d[] = {1, -3, -2, -1};
//
//    assert(!anyFalse(a, 4));
//    assert(!anyFalse(b, 0));
//    assert(anyFalse(c, 4));
//    assert(anyFalse(d, 4));
//
//    assert(countFalse(a, 4) == 0);
//    assert(countFalse(b, 0) == 0);
//    assert(countFalse(c, 4) == 1);
//    assert(countFalse(d, 4) == 3);
//
//    assert(firstFalse(a, 4) == -1);
//    assert(firstFalse(b, 0) == -1);
//    assert(firstFalse(c, 4) == 0);
//    assert(firstFalse(d, 4) == 1);
//
//    assert(locateMinimum(a, 4) == 0);
//    assert(locateMinimum(b, 0) == -1);
//    assert(locateMinimum(c, 4) == 0);
//    assert(locateMinimum(d, 4) == 1);
//
//    double e[] = {1, 2, 3};
//    double f[] = {1, 2, 3, 4};
//    double g[] = {1, 2, 3, 5};
//
//    assert(includes(a, 4, e, 3));
//    assert(includes(a, 4, f, 4));
//    assert(!includes(a, 4, g, 4));
//    assert(includes(a, 4, b, 0));

//    // anyFalse
//    double a [] = {0, 1, 1, -2, 4, -5, -10, 10, 0, -1};
//    assert(anyFalse(a, 10) == true);
//    assert(anyFalse(a + 1, 2) == false);
//    assert(anyFalse(a + 3, 7) == true);
//    double b [] = {1, 2, 3, 4, 5};
//    double c [] = {0};
//    assert(anyFalse(b, 5) == false);
//
//    // countFalse
//    assert(countFalse(a, 10) == 6);
//    assert(countFalse(a + 3, 7) == 5);
//    assert(countFalse(b, 5) == 0);
//    assert(countFalse(c, 1) == 1);
//
//    // firstFalse
//    assert(firstFalse(a, 10) == 0);
//    assert(firstFalse(a + 1, 9) == 2);
//    assert(firstFalse(a + 7, 3) == 1);
//    assert(firstFalse(b, 5) == -1);
//    assert(firstFalse(c, 1) == 0);
//
//    // locateMinimum
//    assert(locateMinimum(a, 10) == 6);
//    assert(locateMinimum(a + 3, 7) == 3);
//    assert(locateMinimum(c, 1) == 0);
//    assert(locateMinimum(b, -1) == -1);
//
//    // includes
//    double d [] = {10, 50, 40, 20, 50, 40, 30};
//    double e [] = {50, 20, 30};
//    assert(includes(d, 7, e, 3));
//    e[1] = 40;
//    e[2] = 40;
//    assert(includes(d, 7, e, 3));
//    e[1] = 30;
//    e[2] = 20;
//    assert(!includes(d, 7, e, 3));
//    e[0] = 10;
//    e[1] = 20;
//    e[2] = 20;
//    assert(!includes(d, 7, e, 3));
//
//    std::cerr << "All Test Cases Passed!" << std::endl;
//}
