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
: GameWorld(assetPath) {}

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
                        // TODO: load avatar
                        break;
                    case Level::wall:
                        m_actors.push_back(new Wall(this, x, y));
                        break;
                    default:
                        // TODO: load other actors
                        break;
                }
            }
        }
    }

    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move() {
    setGameStatText("Game will end when you type q");

    for(auto it = m_actors.begin(); it != m_actors.end(); it++) {
        (*it)->doSomething();
    }

	return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp() {
    for(auto it = m_actors.begin(); it != m_actors.end(); it++) {
        delete *it;
    }
}
