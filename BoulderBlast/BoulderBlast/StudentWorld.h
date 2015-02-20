#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "GameConstants.h"
#include <string>
#include <iostream>
#include "Level.h"
#include "Actor.h"
#include <vector>
#include <sstream>
#include <iomanip>
using namespace std;

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld
{
public:
	StudentWorld(std::string assetDir)
	 : GameWorld(assetDir), m_bonus(1000)
	{}
    
    virtual ~StudentWorld(){cout<<"StudentWorld::destructing"<<endl; cleanUp();}

    virtual int init();

    virtual int move();

    virtual void cleanUp();
    
    int loadLevel();
    
    char getMapCotent(int x, int y) const{return map[x][y];}
    
    Player* getPlayer() const{return pp;}
    
    void setBonus(int howMuch){m_bonus=howMuch;}
    void decBonus(){if(m_bonus>0) m_bonus--;}
    int getBonus() const{return m_bonus;}

private:
    Player* pp;
    vector<Actor*> av;
    char map[15][15];
    int m_bonus;
    void setDisplayText();
    string transform(int score, int level, int bonus, int lives, int health, int ammo);
};

#endif // STUDENTWORLD_H_
