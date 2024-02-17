#include "Actor.h"
#include "StudentWorld.h"

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp

// MARK: Actor
Actor::Actor(StudentWorld* world, int imageID, double startX, double startY, int dir, double size)
: GraphObject(imageID, startX, startY, dir, size), m_world(world) {
}

void Actor::doSomething() {}


// MARK: WALL
Wall::Wall(StudentWorld* world, double startX, double startY)
: Actor(world, IID_WALL, startX, startY) {
    setVisible(true);
}

//// MARK: AVATAR
//Avatar::Avatar(StudentWorld* world, double startX, double startY, int dir, double size)
//: Actor(world, IID_PLAYER, startX, startY, right, size) {
//    setVisible(true);
//    m_hitpoints = 20;
//    m_peas = 20;
//}
//
//void Avatar::doSomething() {
//    if(m_hitpoints <= 0) {
//        return;
//    }
//
//    int ch;
//    if (getWorld()->getKey(ch)) {
//        switch (ch) {
//            case KEY_PRESS_LEFT:
//                setDirection(left);
//                moveForward();
//                break;
//            case KEY_PRESS_RIGHT:
//                setDirection(right);
//                moveForward();
//                break;
//            case KEY_PRESS_SPACE:
//                // TODO: shoot pea
//                break;
//        }
//    }
//    // TODO: MOVE
//}
