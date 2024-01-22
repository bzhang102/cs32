// Gamer Tests
#include "GamerMap.h"
#include <cassert>
#include <iostream>

using namespace std;

int main() {
    GamerMap m;
    m.addGamer("Rachel");
    m.addGamer("Brandon");
    m.addGamer("Brandon");
    assert(m.numGamers() == 2);
    assert(m.hoursSpent("Brandon") == 0);
    assert(m.play("Brandon", 2.7));
    assert(m.hoursSpent("Brandon") == 2.7);

    cerr << "GamerMap Tests Passed" << endl;
}
