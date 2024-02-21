#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include "StudentWorld.h"

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

void findNewCoordinates(double& x, double& y, int dir, int units);

class Actor : public GraphObject {
public:
    Actor(StudentWorld* world, int imageID, int hp, double startX, double startY, bool opaque = false, int dir = right);
    virtual void doSomething() {}
    virtual void getAttacked() {}
    virtual bool getPushed(int dir) { return false; }

    StudentWorld* world() const { return m_world; }
        int hp() const { return m_hp; }
    void sethp(int newhp) { m_hp = newhp; }

    const bool isOpaque;
private:
    StudentWorld* m_world;
    int m_hp;
};

class Wall : public Actor {
public:
    Wall(StudentWorld* world, double startX, double startY);
private:
};

class Player : public Actor {
public:
    Player(StudentWorld* world, double startX, double startY);
    virtual void doSomething();
    virtual void getAttacked() {
        sethp(hp() - 2);
        if(hp() > 0) world()->playSound(SOUND_PLAYER_IMPACT);
    }
private:
    int m_peas;
    void shoot();
};

class Marble : public Actor {
public:
    Marble(StudentWorld* world, double startX, double startY);
    virtual void getAttacked() { sethp(hp() - 2); }
    virtual bool getPushed(int dir);
};

class Pea : public Actor {
public:
    Pea(StudentWorld* world, double startX, double startY, int dir);
    virtual void doSomething();
};
#endif // ACTOR_H_
