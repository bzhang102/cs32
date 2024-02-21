#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include "StudentWorld.h"

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

class Actor : public GraphObject {
public:
    Actor(StudentWorld* world, int imageID, int hp, double startX, double startY, int opaque = 0, int dir = right);
    virtual void doSomething() {}
    virtual void getAttacked() {}
    virtual bool getPushed(int dir, int pusherOpacity) { return false; }

    void findNewCoordinates(double& x, double& y, int dir, int units);

    StudentWorld* world() const { return m_world; }
    int hp() const { return m_hp; }
    void sethp(int newhp) { m_hp = newhp; }

    /* 
        Opacity:
        0: Transparent and pushable
        1: Opaque and pushable
        2: Transparent not pushable
        3: Opaque and not pushable
     */

    int opacity() const { return m_opacity; }
    void setOpacity(int opacity) { m_opacity = opacity; }
private:
    StudentWorld* m_world;
    int m_hp;
    int m_opacity;
};

struct Wall : public Actor {
    Wall(StudentWorld* world, double startX, double startY);
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

struct Marble : public Actor {
    Marble(StudentWorld* world, double startX, double startY);
    virtual void getAttacked() { sethp(hp() - 2); }
    virtual bool getPushed(int dir, int pusherOpacity);
};

struct Pea : public Actor {
    Pea(StudentWorld* world, double startX, double startY, int dir);
    virtual void doSomething();
};

struct Pit : public Actor {    
    Pit(StudentWorld* world, double startX, double startY);
    virtual void doSomething();
    virtual bool getPushed(int dir, int pusherOpacity);
};
#endif // ACTOR_H_
