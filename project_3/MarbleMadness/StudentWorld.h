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
    StudentWorld(std::string assetPath)
    : GameWorld(assetPath), m_player(nullptr), m_bonus(1000), m_crystalsLeft(0), m_exited(false) {}
    ~StudentWorld() { cleanUp(); }

    virtual int init();
    virtual int move();
    virtual void cleanUp();

    void setDisplayText();
    void moveActor(Actor* actor, double x, double y, int dir) const;
    Actor* actorHere(Actor* caller, double x, double y) const;

    void addActor(Actor* actor) { m_actors.push_front(actor); }
    void collectCrystal() { m_crystalsLeft--; }
    void exit() {
        m_exited = true;
        increaseScore(m_bonus);
    }
    Player* player() const { return m_player; }
    bool revealExit() const { return m_crystalsLeft == 0; }
private:
    Player* m_player;
    std::list<Actor*> m_actors;

    int m_bonus;
    int m_crystalsLeft;
    bool m_exited;
};

#endif // STUDENTWORLD_H_
