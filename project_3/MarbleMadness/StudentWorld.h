#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "Level.h"
#include <string>
#include <list>
// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class Actor;
class Player;

class StudentWorld : public GameWorld {
public:
    StudentWorld(std::string assetPath);
    ~StudentWorld();
    virtual int init();
    virtual int move();
    virtual void cleanUp();

    void setDisplayText();
    bool moveActor(Actor* actor, double x, double y, int dir) const;
    Actor* actorHere(double x, double y) const;
private:
    Player* m_player;
    std::list<Actor*> m_actors;

    int m_bonus;
};

#endif // STUDENTWORLD_H_
