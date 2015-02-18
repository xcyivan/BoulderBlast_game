#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "GameConstants.h"
#include <string>
#include <iostream>
#include "Level.h"
#include "Actor.h"
#include <vector>
using namespace std;

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld
{
public:
	StudentWorld(std::string assetDir)
	 : GameWorld(assetDir)
	{}
    
    virtual ~StudentWorld(){cout<<"StudentWorld::destructing"<<endl; cleanUp();}

    virtual int init();

    virtual int move();

    virtual void cleanUp();
    
    int loadLevel();
    
    char getMapCotent(int x, int y) const{return map[x][y];}

private:
    Player* pp;
    vector<Actor*> av;
    char map[15][15];
};

#endif // STUDENTWORLD_H_
