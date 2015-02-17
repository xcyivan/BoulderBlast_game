#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include "GameConstants.h"
#include <iostream>

class Actor : public GraphObject{
public:
    Actor(int imageID, int startX, int startY, Direction dir = none)
    :GraphObject(imageID, startX, startY, dir)
    {}
    
    void doSomething(){std::cout<<"Hi I'm doing something!"<<std::endl;}
};

class Player : public Actor{
public:
    Player(int startX, int startY)
    :Actor(IID_PLAYER, startX, startY, right), m_hitpoints(20), m_ammo(20)
    {}
private:
    int m_hitpoints;
    int m_ammo;
};

class Wall : public Actor{
public:
    Wall(int startX, int startY)
    :Actor(IID_WALL, startX, startY, none)
    {}
};




#endif // ACTOR_H_
