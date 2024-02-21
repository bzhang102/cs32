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
                    case Level::crystal:
                        m_actors.push_back(new Crystal(this, x, y));
                        m_crystalsLeft++;
                        break;
                    case Level::exit: {
                        Actor* exit = new Exit(this, x, y);
                        exit->setVisible(false);
                        m_actors.push_back(exit);
                        break;
                    }
                    case Level::extra_life:
                        m_actors.push_back(new ExtraLife(this, x, y));
                        break;
                    case Level::restore_health:
                        m_actors.push_back(new RestoreHealth(this, x, y));
                        break;
                    case Level::ammo:
                        m_actors.push_back(new Ammo(this, x, y));
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

        // check if player exited
        if(m_exited) return GWSTATUS_FINISHED_LEVEL;
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

void StudentWorld::setDisplayText() {
    // TODO: formatting using stringstreams
}

void StudentWorld::moveActor(Actor* actor, double x, double y, int dir) const {
    // check if out of bounds
    if(x < 0 || y < 0 || x >= VIEW_WIDTH || y >= VIEW_HEIGHT) return;
    
    // see if square is occupied
    Actor* actorOnSquare = actorHere(nullptr, x, y);
    if(actorOnSquare != nullptr) {
        // attempt to push
        if(actorOnSquare->getPushed(dir, actor->opacity())) {
            // obstacle pushed
            actor->moveTo(x, y);
        }
        //cannot be pushed
        return;
    }

    // unoccupied square; move
    actor->moveTo(x, y);
}

Actor* StudentWorld::actorHere(Actor* caller, double x, double y) const {
    for(auto it = m_actors.begin(); it != m_actors.end(); it++) {
        if((*it)->getX() == x && (*it)->getY() == y && (*it) != caller) {
            return *it;
        }
    }
    return nullptr;
}
