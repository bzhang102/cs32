#include "Actor.h"
#include "StudentWorld.h"

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp

// MARK: Actor
Actor::Actor(StudentWorld* world, int imageID, int hp, double startX, double startY, int opacity, int dir)
: GraphObject(imageID, startX, startY, dir, 1.0), m_world(world), m_hp(hp), m_opacity(opacity) {}

void Actor::findNewCoordinates(double& x, double& y, int dir, int units) {
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

// MARK: Wall
Wall::Wall(StudentWorld* world, double startX, double startY)
: Actor(world, IID_WALL, 100, startX,  startY, 3) {
    setVisible(true);
}

// MARK: Player
Player::Player(StudentWorld* world, double startX, double startY)
: Actor(world, IID_PLAYER, 20, startX, startY, 3), m_peas(20) {
    setVisible(true);
}

void Player::doSomething() {
    // if dead do nothing
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
                break;
            case KEY_PRESS_SPACE:
                shoot();
            default:
                return;
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

void Player::shoot() {
    if(m_peas > 0) {
        world()->addActor(new Pea(world(), getX(), getY(), getDirection()));
        world()->playSound(SOUND_PLAYER_FIRE);
        m_peas--;
    }
}

// MARK: Marble
Marble::Marble(StudentWorld* world, double startX, double startY)
: Actor(world, IID_MARBLE, 10, startX, startY, 1) {
    setVisible(true);
}

bool Marble::getPushed(int dir, int pusherOpacity) {
    // only pushable by player
    if(pusherOpacity < 3) return false;

    // find target coordinates
    double x = getX();
    double y = getY();
    findNewCoordinates(x, y, dir, 1);

    // square unoccupied
    Actor* actorAtCoords = world()->actorHere(this, x, y);
    if(actorAtCoords == nullptr || actorAtCoords->opacity() == 2) {
        world()->moveActor(this, x, y, dir);
        return true;
    }
    
    // square occupied
    return false;
}

// MARK: Pea
Pea::Pea(StudentWorld* world, double startX, double startY, int dir) 
: Actor(world, IID_PEA, 100, startX, startY, 0, dir) {
    setVisible(true);
}

void Pea::doSomething() {
    // if dead do nothing
    if(hp() <= 0) return;

    double x = getX();
    double y = getY();

    // if square occupied by opaque actor, attack
    Actor* actorOnSquare = world()->actorHere(this, x, y);
    if(actorOnSquare != nullptr && (actorOnSquare->opacity() == 1 || actorOnSquare->opacity() == 3)) {
        actorOnSquare->getAttacked();
        sethp(0);
        return;
    }

    // find new coordinates
    findNewCoordinates(x, y, getDirection(), 1);

    // if non-transparent actor is found on new square
    actorOnSquare = world()->actorHere(this, x, y);
    if(actorOnSquare != nullptr && (actorOnSquare->opacity() == 1 || actorOnSquare->opacity() == 3)) {
        actorOnSquare->getAttacked();
        sethp(0);
        return;
    }

    world()->moveActor(this, x, y, getDirection());
}

// MARK: Pit
Pit::Pit(StudentWorld* world, double startX, double startY)
: Actor(world, IID_PIT, 100, startX, startY, 2) {
    setVisible(true);
}

void Pit::doSomething() {
    // if dead do nothing
    if(hp() <= 0) return;

    // Detect Marble and Swallow
    Actor* actorOnSquare = world()->actorHere(this, getX(), getY());
    if(actorOnSquare != nullptr && actorOnSquare->opacity() == 1) {
        sethp(0);
        actorOnSquare->sethp(0);
    }
}

bool Pit::getPushed(int dir, int pusherOpacity) {
    return (pusherOpacity <= 1) ? true : false;
}
