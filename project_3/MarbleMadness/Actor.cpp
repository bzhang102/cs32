#include "Actor.h"
#include "StudentWorld.h"

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp

void findNewCoordinates(double& x, double& y, int dir, int units) {
    switch(dir) {
        case GraphObject::up:
            y += units;
            break;
        case GraphObject::down:
            y -= units;
            break;
        case GraphObject::right:
            x += units;
            break;
        case GraphObject::left:
            x -= units;
            break;
    }
}

// MARK: Actor
Actor::Actor(StudentWorld* world, int imageID, int hp, double startX, double startY, bool opaque, int dir)
: GraphObject(imageID, startX, startY, dir, 1.0), m_hp(hp), isOpaque(opaque), m_world(world) {}

// MARK: Wall
Wall::Wall(StudentWorld* world, double startX, double startY)
: Actor(world, IID_WALL, 100, startX,  startY, true) {
    setVisible(true);
}

// MARK: Player
Player::Player(StudentWorld* world, double startX, double startY)
: Actor(world, IID_PLAYER, 20, startX, startY, true) {
    setVisible(true);
}

void Player::doSomething() {
    if(hp() <= 0) return;
    
    int dir;
    if(world()->getKey(dir)) {
        switch(dir) {
            case KEY_PRESS_UP:
                dir = up;
                break;
            case KEY_PRESS_DOWN:
                dir = down;
                break;
            case KEY_PRESS_LEFT:
                dir = left;
                break;
            case KEY_PRESS_RIGHT:
                dir = right;
        }
        setDirection(dir);

        // find target coordinates
        double x = getX();
        double y = getY();
        findNewCoordinates(x, y, dir, 1);

        // attempt to move
        world()->moveActor(this, x, y, dir);
    }
}

// MARK: Marble
Marble::Marble(StudentWorld* world, double startX, double startY)
: Actor(world, IID_MARBLE, 10, startX, startY, true) {
    setVisible(true);
}

bool Marble::getPushed(int dir) {
    // find target coordinates
    double x = getX();
    double y = getY();
    findNewCoordinates(x, y, dir, 1);

    // square unoccupied
    Actor* actorAtCoords = world()->actorHere(x, y);
    if(actorAtCoords == nullptr) {
        world()->moveActor(this, x, y, dir);
        return true;
    }
    
    // square occupied
    return false;
}
