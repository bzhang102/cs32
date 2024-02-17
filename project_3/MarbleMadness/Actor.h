#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include "StudentWorld.h"

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

class Actor : public GraphObject {
public:
    Actor(StudentWorld* world, int imageID, double startX, double startY, int dir = 0, double size = 1.0);
    virtual void doSomething();

    StudentWorld* getWorld() const;
private:
    StudentWorld* m_world;
};

class Wall : public Actor {
public:
    Wall(StudentWorld* world, double startX, double startY);
private:
};

//class Avatar : public Actor {
//public:
//    Avatar(StudentWorld* world, double startX, double startY, int dir, double size);
//    virtual void doSomething();
//
//    int hitpoints() const {
//        return m_hitpoints;
//    }
//private:
//    int m_hitpoints;
//    int m_peas;
//};

#endif // ACTOR_H_
