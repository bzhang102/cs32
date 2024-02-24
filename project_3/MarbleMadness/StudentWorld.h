#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "Level.h"
#include <string>
#include <sstream>
#include <list>
// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class Actor;
class Player;
class Pea;
class RageBot;

class StudentWorld : public GameWorld {
public:
    // Constructor and Destructor
    StudentWorld(std::string assetPath)
    : GameWorld(assetPath), m_player(nullptr), m_curTick(0), m_bonus(1000) {}
    ~StudentWorld() { cleanUp(); }

    // Required implementations
    virtual int init();
    virtual int move();
    virtual void cleanUp();

    // Helper Setters
    void setDisplayText();
    void addActor(Actor* actor) { m_actors.push_back(actor); }

    // Helper Getters
    int curTick() { return m_curTick; }
    void targetCoords(double& x, double& y, int dir, int units) const;
    Actor* actorAtCoords(Actor* caller, double x, double y) const;
    Player* player() const { return m_player; }

    // Helper Functions
    void movePlayer(int dir) const;
    void movePea(Pea* pea, int dir) const;
    void moveRageBot(RageBot* bot, int dir) const;
    bool canShootAtPlayer(RageBot* bot, int dir) const;
private:
    Player* m_player;
    std::list<Actor*> m_actors;

    int m_curTick;
    int m_bonus;
};

#endif // STUDENTWORLD_H_
