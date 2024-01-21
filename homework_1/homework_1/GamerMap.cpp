#include <iostream>

#include "GamerMap.h"

using namespace std;

GamerMap::GamerMap() {}
// Create an empty gamer map.

bool GamerMap::addGamer(std::string name){
    return m_map.insert(name, 0);
}
// If a person with the specified name is not currently in the map,
// and there is room in the map, add an entry for that person
// recording that they have spent 0 hours gaming, and return true.
// Otherwise, make no change to the map and return false.

double GamerMap::hoursSpent(std::string name) const {
    double hours;
    if(m_map.get(name, hours)) {
        return hours;
    }
    return -1;
}
// If a person with the specified name is in the map, return how
// many hours they have spent gaming; otherwise, return -1.

bool GamerMap::play(std::string name, double hours) {
    double oldHours;
    if(m_map.get(name, oldHours) && oldHours >= 0) {
        m_map.update(name, oldHours + hours);
        return true;
    }
    return false;
}
// If no person with the specified name is in the map or if hours
// is negative, make no change to the map and return false.
// Otherwise, increase by the hours parameter the number of hours
// the indicated person has spent gaming and return true.

int GamerMap::numGamers() const{
    return m_map.size();
}
// Return the number of people in the GamerMap.

void GamerMap::print() const {
    string name;
    double hours;
    for(int i = 0; i < numGamers(); i++) {
        if(m_map.get(i, name, hours)) {
            cout << name << " " << hours << endl;
        }
    }
}
// Write to cout one line for every person in the map.  Each line
// consists of the person's name, followed by one space, followed by
// the number of hours that person has spent gaming.  Write no other
// text.  The lines need not be in any particular order.
