#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include "StudentWorld.h"

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

class Actor : public GraphObject {
public:
    Actor(StudentWorld* world, int imageID, int hp, double startX, double startY, int opacity = 0, int dir = right)
    : GraphObject(imageID, startX, startY, dir, 1.0), m_world(world), m_hp(hp), m_opacity(opacity) { setVisible(true);
    }
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
    Wall(StudentWorld* world, double startX, double startY)
    : Actor(world, IID_WALL, 100, startX,  startY, 3) {}
};

class Player : public Actor {
public:
    Player(StudentWorld* world, double startX, double startY)
    : Actor(world, IID_PLAYER, 20, startX, startY, 3), m_peas(20) {}
    virtual void doSomething();
    virtual void getAttacked() {
        sethp(hp() - 2);
        if(hp() > 0) world()->playSound(SOUND_PLAYER_IMPACT);
    }
    void incPeas(int n) { m_peas += n; }
private:
    int m_peas;
    void shoot();
};

struct Marble : public Actor {
    Marble(StudentWorld* world, double startX, double startY)
    : Actor(world, IID_MARBLE, 10, startX, startY, 1) {}
    virtual void getAttacked() { sethp(hp() - 2); }
    virtual bool getPushed(int dir, int pusherOpacity);
};

struct Pea : public Actor {
    Pea(StudentWorld* world, double startX, double startY, int dir)
    : Actor(world, IID_PEA, 100, startX, startY, 0, dir) {}
    virtual void doSomething();
};

struct Pit : public Actor {    
    Pit(StudentWorld* world, double startX, double startY)
    : Actor(world, IID_PIT, 100, startX, startY, 2) {}
    virtual void doSomething();
    virtual bool getPushed(int dir, int pusherOpacity);
};

class Pickup : public Actor {
public:
    Pickup(StudentWorld* world, int imageID, double startX, double startY)
    : Actor(world, imageID, 100, startX, startY, 0) {}
    virtual void doSomething();
    virtual bool getPushed(int dir, int pusherOpacity) { return true; }

    bool playerHere();
private:
    virtual void pickUp() = 0;
};

class Crystal : public Pickup {
public:
    Crystal(StudentWorld* world, double startX, double startY)
    : Pickup(world, IID_CRYSTAL, startX, startY) {}
private:
    virtual void pickUp();
};

class Exit : public Pickup {
public:
    Exit(StudentWorld* world, double startX, double startY)
    : Pickup(world, IID_EXIT, startX, startY), m_revealed(false) {}
    virtual void doSomething();
private:
    virtual void pickUp();
    bool m_revealed;
};

class ExtraLife : public Pickup {
public:
    ExtraLife(StudentWorld* world, double startX, double startY)
    : Pickup(world, IID_EXTRA_LIFE, startX, startY) {}
private:
    virtual void pickUp();
};

class RestoreHealth : public Pickup {
public:
    RestoreHealth(StudentWorld* world, double startX, double startY)
    : Pickup(world, IID_RESTORE_HEALTH, startX, startY) {}
private:
    virtual void pickUp();
};

class Ammo : public Pickup {
public:
    Ammo(StudentWorld* world, double startX, double startY)
    : Pickup(world, IID_AMMO, startX, startY) {}
private:
    virtual void pickUp();
};

#endif // ACTOR_H_
