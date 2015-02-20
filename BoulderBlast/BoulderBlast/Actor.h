#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include "GameConstants.h"
#include <iostream>
#include "GameConstants.h"
using namespace std;

class StudentWorld;

/////////////Actor class ///////////////////////
class Actor : public GraphObject{
public:
    Actor(StudentWorld* sw,int imageID, int startX, int startY, Direction dir = none)
    :GraphObject(imageID, startX, startY, dir), m_sworld(sw), m_alive(true){
        setVisible(true);
    }
    
    virtual ~Actor(){;}
    
    virtual int doSomething(){std::cout<<"Actor::Hi I'm doing something!"<<std::endl; return 0;}
    
    StudentWorld* getWorld() const{return m_sworld;}
    
    bool isAlive(){return m_alive;}
    
    void setDeath(){m_alive=false;}

private:
    StudentWorld* m_sworld;
    bool m_alive;
};


/////////////Player class ////////////////////////

class Player : public Actor{
public:
    Player(StudentWorld* sw,int startX, int startY)
    :Actor(sw, IID_PLAYER, startX, startY, right), m_hitpoints(20), m_ammo(20){}
    
    virtual ~Player(){cout<<"the Player is gone"<<endl;}
    
    virtual int doSomething();
    
private:
    int m_hitpoints;
    int m_ammo;
};


/////////////Wall class//////////////////////////

class Wall : public Actor{
public:
    Wall(StudentWorld* sw, int startX, int startY)
    :Actor(sw, IID_WALL, startX, startY, none){}
    
    virtual ~Wall(){cout<<"the Wall is gone"<<endl;}
    
    virtual int doSomething();
};

///////////Boulder class/////////////////////////
class Boulder : public Actor{
public:
    Boulder(StudentWorld* sw, int startX, int startY)
    :Actor(sw, IID_BOULDER, startX, startY, none),m_hitpoints(10){}
    
    virtual ~Boulder(){cout<<"the Boulder is gone"<<endl;}
    
    virtual int doSomething();

private:
    int m_hitpoints;
};

///////////Hole class///////////////////////////
class Hole : public Actor{
public:
    Hole(StudentWorld* sw, int startX, int startY)
    :Actor(sw, IID_HOLE, startX, startY, none){}
    
    virtual ~Hole(){cout<<"the Hole is gone"<<endl;}

    virtual int doSomething();
};

////////////Goodie class////////////////////
class Goodie: public Actor{
public:
    Goodie(StudentWorld* sw, int imageID, int startX, int startY, Direction dir=none)
    :Actor(sw, imageID, startX, startY, dir){}

    virtual int doSomething();

};


///////////Jewel class/////////////////////
class Jewel : public Goodie{
public:
    Jewel(StudentWorld* sw, int startX, int startY)
    :Goodie(sw, IID_JEWEL, startX, startY, none){}
    
    virtual ~Jewel(){cout<<"the Jewel is gone"<<endl;}
    
    virtual int doSomething();
};

///////////ExraLifeGoodie class/////////////
class ExtraLifeGoodie: public Goodie{
public:
    ExtraLifeGoodie(StudentWorld* sw, int startX, int startY)
    :Goodie(sw, IID_EXTRA_LIFE, startX, startY, none){}
    
    virtual ~ExtraLifeGoodie(){cout<<"the ExtraLifeGoodie is gone"<<endl;}
    
    virtual int doSomething();
};

//////////RestoreLifeGoodie class////////////
class RestoreLifeGoodie : public Goodie{
public:
    RestoreLifeGoodie(StudentWorld* sw,int startX, int startY)
    :Goodie(sw, IID_RESTORE_HEALTH, startX, startY){}
    
    virtual ~RestoreLifeGoodie(){cout<<"the RestoreLifeGoodie is gone"<<endl;}
    
    virtual int doSomething();
};

//////////AmmoGoodie class//////////////
class AmmoGoodie : public Goodie{
public:
    AmmoGoodie(StudentWorld* sw, int startX, int startY)
    :Goodie(sw, IID_AMMO, startX, startY){}
    
    virtual ~AmmoGoodie(){cout<<"the AmmoGoodie is gone"<<endl;}
    
    virtual int doSomething();
};



#endif // ACTOR_H_
