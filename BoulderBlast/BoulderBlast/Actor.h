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
    Actor(StudentWorld* sw,int imageID, int startX, int startY, Direction dir = none, string name="actor")
    :GraphObject(imageID, startX, startY, dir), m_sworld(sw), m_alive(true), m_name(name){
        setVisible(true);
    }
    
    virtual ~Actor(){;}
    
    virtual int doSomething(){std::cout<<"Actor::Hi I'm doing something!"<<std::endl; return 0;}
    
    StudentWorld* getWorld() const{return m_sworld;}
    
    bool isAlive(){return m_alive;}
    
    void setDeath(){m_alive=false;}
    
    string getName(){return m_name;}

private:
    StudentWorld* m_sworld;
    bool m_alive;
    string m_name;
};


/////////////Player class ////////////////////////

class Player : public Actor{
public:
    Player(StudentWorld* sw,int startX, int startY)
    :Actor(sw, IID_PLAYER, startX, startY, right, "player"),
    m_hitpoints(20), m_ammo(20){}
    
    virtual ~Player(){cout<<"the Player is gone"<<endl;}
    
    virtual int doSomething();
    
    void increaseAmmo(int howMuch){m_ammo+=howMuch;cout<<"now the ammo is "<<m_ammo<<endl;}
    void resetAmmo(){m_ammo=20;}
    int getAmmo() const{return m_ammo;}
    
    void restoreHealth(){m_hitpoints=20;cout<<"now the player's hitpoints is "<<m_hitpoints<<endl;}
    int getHealth() const{return m_hitpoints;}
    
    
        
private:
    int m_hitpoints;
    int m_ammo;
};


/////////////Wall class//////////////////////////

class Wall : public Actor{
public:
    Wall(StudentWorld* sw, int startX, int startY)
    :Actor(sw, IID_WALL, startX, startY, none, "wall"){}
    
    virtual ~Wall(){cout<<"the Wall is gone"<<endl;}
    
    virtual int doSomething();
};

////////////Bullet class/////////////////////////
class Bullet : public Actor{
public:
    Bullet(StudentWorld* sw, int startX, int startY, Direction dir)
    :Actor(sw, IID_BULLET, startX, startY, dir, "bullet"){}
    virtual ~Bullet(){cout<<"the bullect is goine"<<endl;}
    virtual int doSomething();
};

///////////Boulder class/////////////////////////
class Boulder : public Actor{
public:
    Boulder(StudentWorld* sw, int startX, int startY)
    :Actor(sw, IID_BOULDER, startX, startY, none, "boulder"),m_hitpoints(10){}
    
    virtual ~Boulder(){cout<<"the Boulder is gone"<<endl;}
    
    virtual int doSomething();

private:
    int m_hitpoints;
};

///////////Hole class///////////////////////////
class Hole : public Actor{
public:
    Hole(StudentWorld* sw, int startX, int startY)
    :Actor(sw, IID_HOLE, startX, startY, none, "hole"){}
    
    virtual ~Hole(){cout<<"the Hole is gone"<<endl;}

    virtual int doSomething();
};

////////////Goodie class////////////////////
class Goodie: public Actor{
public:
    Goodie(StudentWorld* sw, int imageID, int startX, int startY, Direction dir=none, string name="goodie")
    :Actor(sw, imageID, startX, startY, dir, name){}

    virtual int doSomething();

};

///////////Exit class/////////////////////
class Exit: public Goodie{
public:
    Exit(StudentWorld* sw, int startX, int startY)
    :Goodie(sw,  IID_EXIT, startX, startY, none, "exit"){
        setVisible(false);
    }
    virtual ~Exit(){cout<<"the Exit is gone"<<endl;}
    
    virtual int doSomething();
};


///////////Jewel class/////////////////////
class Jewel : public Goodie{
public:
    Jewel(StudentWorld* sw, int startX, int startY)
    :Goodie(sw, IID_JEWEL, startX, startY, none, "jewel"){}
    
    virtual ~Jewel(){cout<<"the Jewel is gone"<<endl;}
    
    virtual int doSomething();
};

///////////ExraLifeGoodie class/////////////
class ExtraLifeGoodie: public Goodie{
public:
    ExtraLifeGoodie(StudentWorld* sw, int startX, int startY)
    :Goodie(sw, IID_EXTRA_LIFE, startX, startY, none, "extra"){}
    
    virtual ~ExtraLifeGoodie(){cout<<"the ExtraLifeGoodie is gone"<<endl;}
    
    virtual int doSomething();
};

//////////RestoreLifeGoodie class////////////
class RestoreLifeGoodie : public Goodie{
public:
    RestoreLifeGoodie(StudentWorld* sw,int startX, int startY)
    :Goodie(sw, IID_RESTORE_HEALTH, startX, startY, none, "restore"){}
    
    virtual ~RestoreLifeGoodie(){cout<<"the RestoreLifeGoodie is gone"<<endl;}
    
    virtual int doSomething();
};

//////////AmmoGoodie class//////////////
class AmmoGoodie : public Goodie{
public:
    AmmoGoodie(StudentWorld* sw, int startX, int startY)
    :Goodie(sw, IID_AMMO, startX, startY, none, "ammo"){}
    
    virtual ~AmmoGoodie(){cout<<"the AmmoGoodie is gone"<<endl;}
    
    virtual int doSomething();
};



#endif // ACTOR_H_
