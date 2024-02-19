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

StudentWorld::StudentWorld(string assetPath)
: GameWorld(assetPath) {}

StudentWorld::~StudentWorld() {
    cleanUp();
}

int StudentWorld::init() {
    // MARK: Current level
    string levelPath = "level00.txt";

    // create level
    Level lev(assetPath());
    Level::LoadResult result = lev.loadLevel(levelPath);

    if (result == Level::load_fail_file_not_found)
        cerr << "Could not find " + levelPath + " data file" << endl;
    else if (result == Level::load_fail_bad_format)
        cerr << "Your level was improperly formatted" << endl;
    else if (result == Level::load_success)
    {
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
    }
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

bool StudentWorld::isMovable(double x, double y) const {
    // out of bounds
    if(x < 0 || x >= VIEW_WIDTH || y < 0 || y >= VIEW_WIDTH) return false;

    // occupied by another opaque entity
    for(auto it = m_actors.begin(); it != m_actors.end(); it++) {
        if((*it)->isOpaque && (*it)->getX() == x && (*it)->getY() == y) {
            return false;
        }
    }

    return true;
}
