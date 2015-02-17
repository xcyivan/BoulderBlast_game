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

    virtual int init();

    virtual int move();

    virtual void cleanUp();
    
    int loadLevel();

private:
    Player* pp;
    vector<Actor*> av;
};

#endif // STUDENTWORLD_H_
