#include "StudentWorld.h"
#include "GameConstants.h"
#include "Actor.h"
#include <string>
using namespace std;

GameWorld* createStudentWorld(string assetPath) {
	return new StudentWorld(assetPath);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h, and Actor.cpp

StudentWorld::StudentWorld(string assetPath)
: GameWorld(assetPath), m_bonus(1000) {}

StudentWorld::~StudentWorld() {
    cleanUp();
}

int StudentWorld::init() {
    string levelPath = "level00.txt";

    Level lev(assetPath());
    Level::LoadResult result = lev.loadLevel(levelPath);
    if (result == Level::load_fail_file_not_found)
        cerr << "Could not find " + levelPath + " data file" << endl;
    else if (result == Level::load_fail_bad_format)
        cerr << "Your level was improperly formatted" << endl;
    else if (result == Level::load_success)
    {
        for(int x = 0; x < VIEW_WIDTH; x++) {
            for(int y = 0; y < VIEW_HEIGHT; y++) {
                Level::MazeEntry ge = lev.getContentsOf(x,y);
                switch (ge) {
                    case Level::empty:
                        break;
                    case Level::player:
                        m_player = new Avatar(this, x, y);
                        break;
                    case Level::wall:
                        m_actors.push_back(new Wall(this, x, y));
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
//    updateDisplayText();
    for(auto it = m_actors.begin(); it != m_actors.end(); it++) {
        (*it)->doSomething();
        if(m_player->hitpoints() <= 0) return GWSTATUS_PLAYER_DIED;
//            if (thePlayerCompletedTheCurrentLevel()) {
//                increaseScoreAppropriately();
//                return GWSTATUS_FINISHED_LEVEL;
//            }
    }

    m_player->doSomething();

//    removeDeadGameObjects(); // delete dead game objects
    if(m_bonus > 0) m_bonus--;
//    if (thePlayerHasCollectedAllOfTheCrystalsOnTheLevel())
//        exposeTheExitInTheMaze();

    return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp() {
    delete m_player;
    for(auto it = m_actors.begin(); it != m_actors.end(); it++) {
        delete *it;
    }
}


// TODO: FIX
bool StudentWorld::isMovable(int x, int y) const {
    for(auto it = m_actors.begin(); it != m_actors.end(); it++) {
        if((*it)->isOpaque && (*it)->getX() == x && (*it)->getY() == y) {
            return false;
        }
    }

    return true;
}
