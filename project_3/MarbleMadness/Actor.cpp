#include "Actor.h"
#include "StudentWorld.h"

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp

// MARK: Actor
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

// MARK: Player
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
    // allows actors with opacity less than pit to move over pit
    return (pusherOpacity <= 1) ? true : false;
}

// MARK: Pickup
bool Pickup::playerHere() {
    Player* player = world()->player();
    return (player->getX() == getX() && player->getY() == getY()) ? true : false;
}

void Pickup::doSomething() {
    // if dead do nothing
    if(hp() <= 0) return;

    // perform action if player hits pickup
    if(playerHere()) {
        sethp(0);
        pickUp();
    }
}

// MARK: Crystal
void Crystal::pickUp() {
    world()->increaseScore(50);
    world()->collectCrystal();
    world()->playSound(SOUND_GOT_GOODIE);
}

// MARK: Exit
void Exit::doSomething() {
    // if dead do nothing
    if(hp() <= 0) return;

    // reveal exit if all crystals collected
    if(world()->revealExit() && !m_revealed) {
        world()->playSound(SOUND_REVEAL_EXIT);
        setVisible(true);
        m_revealed = true;
    }

    // perform action if player hits pickup
    if(playerHere() && m_revealed) pickUp();
}

void Exit::pickUp() {
    world()->playSound(SOUND_FINISHED_LEVEL);
    world()->increaseScore(2000);
    world()->exit();
}

// MARK: Extra Life
void ExtraLife::pickUp() {
    world()->increaseScore(1000);
    world()->playSound(SOUND_GOT_GOODIE);
    world()->incLives();
}

// MARK: Restore Health
void RestoreHealth::pickUp() {
    world()->increaseScore(500);
    world()->playSound(SOUND_GOT_GOODIE);
    world()->player()->sethp(20);
}

// MARK: Ammo
void Ammo::pickUp() {
    world()->increaseScore(100);
    world()->playSound(SOUND_GOT_GOODIE);
    world()->player()->incPeas(20);
}

