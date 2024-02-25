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
        world()->movePlayer();
    }
}

void Player::shoot() {
    if(m_peas > 0) {
        double x = getX();
        double y = getY();
        world()->targetCoords(x, y, getDirection());
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
    world()->movePea(this);
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

// MARK: Pickup
void Pickup::doSomething() {
    // if dead or invisible do nothing
    if(hp() <= 0 || !isVisible()) return;

    // if player is on square, get picked up
    if(world()->player()->getX() == getX() && world()->player()->getY() == getY()) {
        sethp(0);
        setVisible(false);
        world()->playSound(SOUND_GOT_GOODIE);
        pickUp();
    }
}

// MARK: Crystal
void Crystal::pickUp() {
    world()->increaseScore(50);
    world()->decCrystals();
}

// MARK: ExtraLife
void ExtraLife::pickUp() {
    world()->increaseScore(1000);
    world()->incLives();
}

// MARK: RestoreHealth
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

// MARK: Exit
void Exit::doSomething() {
    // update visibility
    if(world()->crystalsLeft() == 0) setVisible(true);

    if(isVisible() && world()->player()->getX() == getX() && world()->player()->getY() == getY()) {
        world()->increaseScore(2000);
        world()->playSound(SOUND_FINISHED_LEVEL);
        world()->setComplete(true);
    }
}

// MARK: Bot
bool Bot::takeDamage() {
    sethp(hp() - 2);
    if(hp() > 0) {
        world()->playSound(SOUND_ROBOT_IMPACT);
    } else {
        // if dead
        setVisible(false);
        world()->playSound(SOUND_ROBOT_DIE);
        world()->increaseScore(100);
    }
    return true;
}

void Bot::shoot() {
    double x = getX();
    double y = getY();
    world()->targetCoords(x, y, getDirection());
    world()->addActor(new Pea(world(), x, y, getDirection()));
    world()->playSound(SOUND_ENEMY_FIRE);
}

// MARK: RageBot
void RageBot::doSomething() {
    // if dead do nothing
    if(hp() <= 0) return;

    // calculate number of ticks to wait
    int ticks = (28 - world()->getLevel()) / 4;
    if(ticks < 3) ticks = 3;
    
    if(world()->curTick() % ticks == 0) {
        if(world()->canShootAtPlayer(this)) {
            shoot();
        } else {
            world()->moveRageBot(this);
        }
    }
}

// MARK: ThiefBot
void ThiefBot::doSomething() {
    // if dead do nothing
    if(hp() <= 0) return;

    // calculate number of ticks to wait
    int ticks = (28 - world()->getLevel()) / 4;
    if(ticks < 3) ticks = 3;

    if(world()->curTick() % ticks == 0) {
        Actor* toSteal = world()->canSteal(this);
        if(toSteal != nullptr) {
            steal(toSteal);
        } else {
            world()->moveThiefBot(this);
        }
    }
}

void ThiefBot::steal(Actor* toSteal) {
    if(toSteal != nullptr) {
        if(rand() % 10 == 0) {
            toSteal->setVisible(false);
            m_stolenGoods = toSteal;
            world()->playSound(SOUND_ROBOT_MUNCH);
        }
    }
}

bool ThiefBot::takeDamage() {
    sethp(hp() - 2);
    if(hp() > 0) {
        world()->playSound(SOUND_ROBOT_IMPACT);
    } else {
        // if dead
        setVisible(false);
        world()->playSound(SOUND_ROBOT_DIE);
        world()->increaseScore(10);
        // drop stolen goods
        if(m_stolenGoods != nullptr) {
            m_stolenGoods->moveTo(getX(), getY());
            m_stolenGoods->setVisible(true);
        }
    }
    return true;
}

void ThiefBot::turn() {
    int directions[] = {up, down, left, right};

    double x = getX();
    double y = getY();

    int random = rand() % 4;
    int initialDirection = directions[random];

    // attempt to set random direction
    for(int i = 1; i <= 4; i++) {
        world()->targetCoords(x, y, directions[random]);
        if(world()->botCanMoveHere(x, y)) {
            setDirection(directions[random]);
            moveTo(x, y);
            return;
        }
        directions[random] = directions[4 - i];
        random = rand() % (4 - i);
    }

    // blocked on all sides
    setDirection(initialDirection);
}
