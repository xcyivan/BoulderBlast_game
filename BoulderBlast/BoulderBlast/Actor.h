#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include "GameConstants.h"
#include <iostream>
#include "GameConstants.h"

class StudentWorld;

/////////////Actor class ///////////////////////
class Actor : public GraphObject{
public:
    Actor(StudentWorld* sw,int imageID, int startX, int startY, Direction dir = none)
    :GraphObject(imageID, startX, startY, dir), m_sworld(sw)
    {}
    
    virtual int doSomething(){std::cout<<"Actor::Hi I'm doing something!"<<std::endl; return 0;}
    
    StudentWorld* getWorld() const{return m_sworld;}

private:
    StudentWorld* m_sworld;
};


/////////////Player class ////////////////////////

class Player : public Actor{
public:
    Player(StudentWorld* sw,int startX, int startY)
    :Actor(sw, IID_PLAYER, startX, startY, right), m_hitpoints(20), m_ammo(20), m_alive(true){
        setVisible(true);
    }
    
    virtual int doSomething();
    bool isAlive(){return m_alive;}
    
private:
    int m_hitpoints;
    int m_ammo;
    bool m_alive;
};


/////////////Wall class//////////////////////////

class Wall : public Actor{
public:
    Wall(StudentWorld* sw, int startX, int startY)
    :Actor(sw, IID_WALL, startX, startY, none){
        setVisible(true);
    }
};




#endif // ACTOR_H_
