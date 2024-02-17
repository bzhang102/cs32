#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "Level.h"
#include <string>
#include <vector>
// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class Actor;
class Avatar;

class StudentWorld : public GameWorld {
public:
    StudentWorld(std::string assetPath);
    ~StudentWorld();
    virtual int init();
    virtual int move();
    virtual void cleanUp();

    bool isMovable(int x, int y) const;
private:
    int m_bonus;
    Avatar* m_player;
    std::vector<Actor*> m_actors;
};

#endif // STUDENTWORLD_H_
