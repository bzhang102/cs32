#include "Actor.h"
#include "StudentWorld.h"

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp

// MARK: Actor
Actor::Actor(StudentWorld* world, int imageID, double startX, double startY, bool opaque, int dir)
: GraphObject(imageID, startX, startY, dir, 1.0), isOpaque(opaque), m_world(world) {}

// MARK: Attackable
Attackable::Attackable(StudentWorld* world, int imageID, int hp, double startX, double startY, bool opaque, int dir)
: Actor(world, imageID, startX, startY, dir, opaque), m_hp(hp) {}

// MARK: Wall

Wall::Wall(StudentWorld* world, double startX, double startY)
: Actor(world, IID_WALL, startX,  startY, true) {
    setVisible(true);
}

// MARK: Player
Player::Player(StudentWorld* world, double startX, double startY)
: Attackable(world, IID_PLAYER, 20, startX, startY, true, right) {
    setVisible(true);
}

void Player::doSomething() {
    int ch;
    if(getWorld()->getKey(ch)) {
        switch (ch) {
            case KEY_PRESS_LEFT:
                setDirection(left);
                if(getWorld()->isMovable(getX() - 1, getY())) moveTo(getX() - 1, getY());
                break;
            case KEY_PRESS_RIGHT:
                setDirection(right);
                if(getWorld()->isMovable(getX() + 1, getY())) moveTo(getX() + 1, getY());
                break;
            case KEY_PRESS_UP:
                setDirection(up);
                if(getWorld()->isMovable(getX(), getY() + 1)) moveTo(getX(), getY() + 1);
                break;
            case KEY_PRESS_DOWN:
                setDirection(down);
                if(getWorld()->isMovable(getX(), getY() - 1)) moveTo(getX(), getY() - 1);
                break;
        }
    }
}
