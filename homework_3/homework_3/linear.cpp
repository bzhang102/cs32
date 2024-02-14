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
    if(n <= 0) return -1;
    if(n == 1) return 0;
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
