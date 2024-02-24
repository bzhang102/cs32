#include "Actor.h"
#include "StudentWorld.h"

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp

// MARK: Player
void Player::doSomething() {
    // if dead do nothing
    if(hp() <= 0) return;
    
    // get user input
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
        world()->movePlayer(dir);
    }
}

void Player::shoot() {
    if(m_peas > 0) {
        double x = getX();
        double y = getY();
        world()->targetCoords(x, y, getDirection(), 1);
        world()->addActor(new Pea(world(), x, y, getDirection()));
        world()->playSound(SOUND_PLAYER_FIRE);
        m_peas--;
    }
}

// MARK: Pea
void Pea::doSomething() {
    // if dead do nothing
    if(hp() <= 0) return;
    
    // do not move if just spawned
    if(!m_moved) {
        m_moved = true;
        return;
    }
    // attempt to move pea
    world()->movePea(this, getDirection());
}

// MARK: Pit
void Pit::doSomething() {
    // if dead do nothing
    if(hp() <= 0) return;

    // Detect Marble and Swallow
    Actor* actor = world()->actorAtCoords(this, getX(), getY());
    if(actor != nullptr && actor->swallowable()) {
        sethp(0);
        actor->sethp(0);

        setVisible(false);
        actor->setVisible(false);
    }
}

// MARK: RageBot
void RageBot::doSomething() {
    // if dead do nothing
    if(hp() <= 0) return;

    // calculate number of ticks to wait
    int ticks = (28 - world()->getLevel()) / 4;
    if(ticks < 3) ticks = 3;
    
    if(world()->curTick() % ticks == 0) {
        if(world()->canShootAtPlayer(this, getDirection())) {
            double x = getX();
            double y = getY();
            world()->targetCoords(x, y, getDirection(), 1);
            world()->addActor(new Pea(world(), x, y, getDirection()));
            world()->playSound(SOUND_ENEMY_FIRE);
        } else {
            world()->moveRageBot(this, getDirection());
        }
    }
}

