#ifndef Gamer_h
#define Gamer_h

#include "Map.h"

class GamerMap {
public:
    GamerMap();
    bool addGamer(std::string name);
    double hoursSpent(std::string name) const;
    bool play(std::string name, double hours);
    int numGamers() const;
    void print() const;
private:
    Map m_map;
};

#endif
