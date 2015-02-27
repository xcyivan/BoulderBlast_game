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
	 : GameWorld(assetDir), m_bonus(1000), m_jewelCount(0),m_canExit(false){
         levelArray[0]="level01.dat";
         levelArray[1]="level01.dat";
         levelArray[2]="level02.dat";
         levelArray[3]="level03.dat";
         levelArray[4]="happynewyear.dat";
     }
    
    virtual ~StudentWorld(){cout<<"StudentWorld::destructing"<<endl; cleanUp();}

    virtual int init();

    virtual int move();

    virtual void cleanUp();
    
    int loadLevel();
    
    Player* getPlayer() const{return pp;}
    
    void setBonus(int howMuch){m_bonus=howMuch;}
    void decBonus(){if(m_bonus>0) m_bonus--;}
    int getBonus() const{return m_bonus;}
    
    vector<Actor*> getMapAt(int x, int y);

    
    void decJewCount(){if(m_jewelCount>0) m_jewelCount--;}
    int getJewCount(){return m_jewelCount;}
    bool canExit(){return m_canExit;}
    
    string getLevelDat(int i){return levelArray[i];}
    
    void addActor(int x, int y, Actor::Direction dir, string name);
    

private:
    Player* pp;
    vector<Actor*> av;
    string levelArray[5];
    int m_bonus;
    int m_jewelCount;
    bool m_canExit;
    void setDisplayText();
    string transform(int score, int level, int bonus, int lives, int health, int ammo);
};

#endif // STUDENTWORLD_H_
