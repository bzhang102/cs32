#include "StudentWorld.h"
#include "GameConstants.h"
#include "Actor.h"
#include <string>
#include <cmath>
using namespace std;

GameWorld* createStudentWorld(string assetPath) {
	return new StudentWorld(assetPath);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h, and Actor.cpp

int StudentWorld::init() {
    // format levelPath string
    string levelPath;
    if(getLevel() < 9)
        levelPath = "level0" + to_string(getLevel()) + ".txt";
    else
        levelPath = "level" + to_string(getLevel()) + ".txt";

    // create level
    Level lev(assetPath());
    Level::LoadResult result = lev.loadLevel(levelPath);

    if (result == Level::load_fail_file_not_found)
        cerr << "Could not find " + levelPath + " data file" << endl;
    else if (result == Level::load_fail_bad_format)
        cerr << "Your level was improperly formatted" << endl;
    else if (result == Level::load_success) {
        // load actors by square
        for(int x = 0; x < VIEW_WIDTH; x++) {
            for(int y = 0; y < VIEW_HEIGHT; y++) {
                Level::MazeEntry ge = lev.getContentsOf(x,y);
                switch (ge) {
                    case Level::empty:
                        break;
                    case Level::player:
                        m_player = new Player(this, x, y);
                        break;
                    case Level::wall:
                        m_actors.push_back(new Wall(this, x, y));
                        break;
                    case Level::marble:
                        m_actors.push_back(new Marble(this, x, y));
                        break;
                    case Level::pit:
                        m_actors.push_back(new Pit(this, x, y));
                        break;
                    case Level::vert_ragebot:
                        m_actors.push_back(new RageBot(this, x, y, GraphObject::up));
                        break;
                    case Level::horiz_ragebot:
                        m_actors.push_back(new RageBot(this, x, y, GraphObject::right));
                        break;
                    default:
                        break;
                }
            }
        }
    }

    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move() {
    // tell player to do something
    m_player->doSomething();

    // tell actors do do something
    for(auto it = m_actors.begin(); it != m_actors.end(); it++) {
        (*it)->doSomething();

        // check if player died
        if(m_player->hp() <= 0) {
            playSound(SOUND_PLAYER_DIE);
            return GWSTATUS_PLAYER_DIED;
        }

        // TODO: check if player exited
    }

    // remove dead actors
    for(auto it = m_actors.begin(); it != m_actors.end();) {
        if((*it)->hp() <= 0) {
            delete(*it);
            it = m_actors.erase(it);
        } else {
            it++;
        }
    }

    // decrement bonus points
    if(m_bonus > 0) m_bonus--;

    // increment current tick
    m_curTick++;

    // update display text
    setDisplayText();

    // remove all dead actors
    return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp() {
    // delete player
    delete m_player;
    m_player = nullptr;
    
    //delete actors
    for(auto it = m_actors.begin(); it != m_actors.end(); it++) {
        delete *it;
        *it = nullptr;
    }
}

// MARK: Helper Functions

void StudentWorld::setDisplayText() {
    // TODO: formatting using stringstreams
}

void StudentWorld::targetCoords(double& x, double& y, int dir, int units) const {
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

void StudentWorld::movePlayer(int dir) const {
    // get target location
    double x = m_player->getX();
    double y = m_player->getY();
    targetCoords(x, y, dir, 1);

    // iterate through all actors
    for(auto it = m_actors.begin(); it != m_actors.end(); it++) {
        // if an actor is here
        if((*it)->getX() == x && (*it)->getY() == y) {
            // if actor is transparent to players
            if((*it)->playerTransparent()) continue;

            // if actor is pushable
            if((*it)->pushable()) {
                // get coords of space to push into
                double nextX = x;
                double nextY = y;
                targetCoords(nextX, nextY, dir, 1);
                Actor* actorAtTarget = actorAtCoords(nullptr, nextX, nextY);
                // if nothing at target coords, or marble transparent at target coords
                if(actorAtTarget == nullptr || actorAtTarget->marbleTransparent()) {
                    (*it)->moveTo(nextX, nextY);
                    m_player->moveTo(x, y);
                }
            }
            return;
        }
    }
    // valid movement, move player
    m_player->moveTo(x, y);
}

void StudentWorld::movePea(Pea* pea, int dir) const {
    // get current location
    double x = pea->getX();
    double y = pea->getY();
    
    if(m_player->getX() == x && m_player->getY() == y) {
        m_player->takeDamage();
        pea->sethp(0);
        pea->setVisible(false);
        return;
    }
    for(auto it = m_actors.begin(); it != m_actors.end(); it++) {
        if((*it)->getX() == x && (*it)->getY() == y) {
            if(!(*it)->peaTransparent()) {
                (*it)->takeDamage();
                pea->sethp(0);
                pea->setVisible(false);
                return;
            }
        }
    }

    targetCoords(x, y, dir, 1);
    pea->moveTo(x, y);

    if(m_player->getX() == x && m_player->getY() == y) {
        m_player->takeDamage();
        pea->sethp(0);
        pea->setVisible(false);
    }
    for(auto it = m_actors.begin(); it != m_actors.end(); it++) {
        if((*it)->getX() == x && (*it)->getY() == y) {
            if(!(*it)->peaTransparent()) {
                (*it)->takeDamage();
                pea->sethp(0);
                pea->setVisible(false);
                return;
            }
        }
    }
}

void StudentWorld::moveRageBot(RageBot* bot, int dir) const {
    double x = bot->getX();
    double y = bot->getY();
    targetCoords(x, y, dir, 1);

    for(auto it = m_actors.begin(); it != m_actors.end(); it++) {
        // if an actor is here
        if((*it)->getX() == x && (*it)->getY() == y) {
            // if actor is transparent to robots
            if((*it)->robotTransparent()) {
                continue;
            } else {
                bot->setDirection((dir + 180) % 360);
                return;
            }
        }
    }
    // valid movement, move bot
    bot->moveTo(x, y);
}

bool StudentWorld::canShootAtPlayer(RageBot* bot, int dir) const {
    double x = bot->getX();
    double y = bot->getY();

    int lower, upper;
    switch(dir) {
        case GraphObject::left:
            lower = m_player->getX();
            upper = x;
            if(y != m_player->getY() || x < lower) return false;
            for(auto it = m_actors.begin(); it != m_actors.end(); it++) {
                if((*it)->getX() > lower && (*it)->getX() < upper && !(*it)->peaTransparent()) {
                    return false;
                }
            }
            break;
        case GraphObject::right:
            lower = x;
            upper = m_player->getX();
            if(y != m_player->getY() || x > upper) return false;
            for(auto it = m_actors.begin(); it != m_actors.end(); it++) {
                if((*it)->getY() == y && (*it)->getX() > lower && (*it)->getX() < upper && !(*it)->peaTransparent()) {
                    return false;
                }
            }
            break;
        case GraphObject::up:
            lower = y;
            upper = m_player->getY();
            if(x != m_player->getX() || y > upper) return false;
            for(auto it = m_actors.begin(); it != m_actors.end(); it++) {
                if((*it)->getY() > lower && (*it)->getY() < upper && !(*it)->peaTransparent()) {
                    return false;
                }
            }
            break;
        case GraphObject::down:
            lower = m_player->getY();
            upper = y;
            if(y != m_player->getY() || y < lower) return false;
            for(auto it = m_actors.begin(); it != m_actors.end(); it++) {
                if((*it)->getY() > lower && (*it)->getY() < upper && !(*it)->peaTransparent()) {
                    return false;
                }
            }
    }
    return true;
}


Actor* StudentWorld::actorAtCoords(Actor* caller, double x, double y) const {
    for(auto it = m_actors.begin(); it != m_actors.end(); it++) {
        if((*it)->getX() == x && (*it)->getY() == y && (*it) != caller) {
            return *it;
        }
    }
    return nullptr;
}
