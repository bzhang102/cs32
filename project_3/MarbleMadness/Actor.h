#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include "StudentWorld.h"

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

class Actor : public GraphObject {
public:
    // Constructor
    Actor(StudentWorld* world, int imageID, int hp, double startX, double startY, int dir = none)
    : GraphObject(imageID, startX, startY, dir, 1.0), m_world(world), m_hp(hp) { setVisible(true);
    }

    // Required function
    virtual void doSomething() {}

    // Helper functions
    virtual bool takeDamage() { return false; }

    // Getters and Setters
    StudentWorld* world() const { return m_world; }
    int hp() const { return m_hp; }
    void sethp(int newhp) { m_hp = newhp; }

    //Transparency Functions
    virtual bool playerTransparent() const { return false; }
    virtual bool marbleTransparent() const { return false; }
    virtual bool peaTransparent() const { return false; }
    virtual bool robotTransparent() const { return false; }

    //Attribute Functions
    virtual bool pushable() const { return false; }
    virtual bool swallowable() const { return false; }
private:
    StudentWorld* m_world;
    int m_hp;
};

class Wall : public Actor {
public:
    Wall(StudentWorld* world, double startX, double startY)
    : Actor(world, IID_WALL, 100, startX,  startY) {}
};

class Player : public Actor {
public:
    Player(StudentWorld* world, double startX, double startY)
    : Actor(world, IID_PLAYER, 20, startX, startY, right), m_peas(20) {}
    virtual void doSomething();
    virtual bool takeDamage() {
        sethp(hp() - 2);
        if(hp() > 0) {
            world()->playSound(SOUND_PLAYER_IMPACT);
        } else {
            world()->playSound(SOUND_PLAYER_DIE);
        }
        return true;
    }
    void incPeas(int n) { m_peas += n; }
private:
    int m_peas;
    void shoot();
};

class Marble : public Actor {
public:
    Marble(StudentWorld* world, double startX, double startY)
    : Actor(world, IID_MARBLE, 10, startX, startY, 1) {}
    virtual bool takeDamage() { sethp(hp() - 2); return true; }
    virtual bool pushable() const { return true; }
    virtual bool swallowable() const { return true; }
};

class Pea : public Actor {
public:
    Pea(StudentWorld* world, double startX, double startY, int dir)
    : Actor(world, IID_PEA, 100, startX, startY, dir), m_moved(false) {}
    virtual void doSomething();
    virtual bool playerTransparent() const { return true; }
    virtual bool marbleTransparent() const { return true; }
    virtual bool peaTransparent() const { return true; }
    virtual bool robotTransparent() const { return true; }
private:
    bool m_moved;
};

class Pit : public Actor {
public:
    Pit(StudentWorld* world, double startX, double startY)
    : Actor(world, IID_PIT, 100, startX, startY) {}
    virtual void doSomething();
    virtual bool marbleTransparent() const { return true; }
    virtual bool peaTransparent() const { return true; }
};

class RageBot : public Actor {
public:
    RageBot(StudentWorld* world, double startX, double startY, int dir)
    : Actor(world, IID_RAGEBOT, 10, startX, startY, dir) {}
    virtual void doSomething();
    virtual bool takeDamage() {
        sethp(hp() - 2);
        if(hp() > 0) {
            world()->playSound(SOUND_ROBOT_IMPACT);
        } else {
            world()->playSound(SOUND_ROBOT_DIE);
            world()->increaseScore(100);
        }
        return true;
    }
    void shoot();
};
#endif // ACTOR_H_
