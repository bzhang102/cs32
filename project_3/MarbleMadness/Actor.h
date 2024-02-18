#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include "StudentWorld.h"

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

class Actor : public GraphObject {
public:
    Actor(StudentWorld* world, int imageID, double startX, double startY, bool opaque = false, int dir = 0, double size = 1.0);
    virtual void doSomething() {};

    StudentWorld* getWorld() const { return m_world; }
    const bool isOpaque;
private:
    StudentWorld* m_world;
};

class Attackable : public Actor {
public:
    Attackable(StudentWorld* world, int imageID, int hp, double startX, double startY,  bool opaque = false, int dir = 0, double size = 1.0);

    int hitpoints() const { return m_hp; }
private:
    int m_hp;
};

class Wall : public Actor {
public:
    Wall(StudentWorld* world, double startX, double startY);
private:
};

class Player : public Attackable {
public:
    Player(StudentWorld* world, double startX, double startY);
    virtual void doSomething();
private:
};

#endif // ACTOR_H_
