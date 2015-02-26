#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include "GameConstants.h"
#include <iostream>
#include "GameConstants.h"
#include <cstdlib>
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
    
    virtual bool isAlive(){return m_alive;}
    
    void setDeath(){ m_alive=false;}
    
    string getName(){return m_name;}
    
    virtual void damage(){cout<<"Oh I'm damaged"<<endl;}
    
    virtual bool pushed(Direction dir){return false;}
    
    bool clearToMove();

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
    void decreaseAmmo(){if(m_ammo>0) m_ammo--;}
    
    void restoreHealth(){m_hitpoints=20;cout<<"now the player's hitpoints is "<<m_hitpoints<<endl;}
    int getHealth() const{return m_hitpoints;}
    
    virtual void damage(){cout<<"Oh I'm damaged"<<endl;}
    
    
        
private:
    int m_hitpoints;
    int m_ammo;
};
////////////Snarlbot class//////////////////////
//m_vh=right means horizontal, m_vh=down mean vertical;
class Snarlbot : public Actor{
public:
    Snarlbot(StudentWorld* sw, int startX, int startY, Direction dir)
    :Actor(sw, IID_SNARLBOT, startX, startY, dir, "snarlbot"),
     m_vh(dir), ticksCount(0), m_hitpoints(10){}
    
    virtual ~Snarlbot(){cout<<"The Snarlbot is gone!"<<endl;}
    
    virtual int doSomething();
    bool canMove();
    
    virtual void damage(){m_hitpoints -= 2;}
    
    virtual bool isAlive(){
        if(Actor::isAlive()==false) return false;
        if(m_hitpoints<=0){
            Actor::setDeath();
            return false;
        }
        return true;
    }
    
    bool canFire();

private:
    Direction m_vh;
    int ticksCount;
    int m_hitpoints;
};

////////////factory class////////////////////////
class Factory : public Actor{
public:
    //type: 0 means kleptobot factory, 1 means angry kleptobot factory
    Factory(StudentWorld* sw, int startX, int startY, int type)
    :Actor(sw, IID_ROBOT_FACTORY, startX, startY, none, "factory"), m_type(type),ticksCount(0){}
    virtual ~Factory(){cout<<"the factory is gone"<<endl;}
    
    bool canMove(){
        ticksCount=(ticksCount+1)%100;
        if(ticksCount==0) return true;
        else return false;
    }
    virtual int doSomething();
    
private:
    int m_type;
    int ticksCount;
};

/////////////BaseKlepto class///////////////////
class BaseKlepto : public Actor{
public:
    BaseKlepto(StudentWorld* sw, int startX, int startY, int imageID, Direction dir, string name)
    :Actor(sw, imageID, startX, startY, dir, name), ticksCount(0),stepsCount(0){
        m_step = rand()%6+1;
        cout<<"m_step is "<<m_step<<endl;
    }
    ~BaseKlepto(){cout<<"the BaseKlepto is gone"<<endl;}
    bool canMove();
    
    virtual int doSomething();
    
    void turn();
    
private:
    int ticksCount;
    int m_step;
    int stepsCount;
};

/////////////Kleptobot class////////////////////
class Kleptobot : public BaseKlepto{
public:
    Kleptobot(StudentWorld* sw, int startX, int startY)
    :BaseKlepto(sw, startX, startY, IID_KLEPTOBOT, right, "klepto"),m_hitpoints(5){}
    ~Kleptobot(){cout<<"the Kleptobot is gone"<<endl;}
    virtual void damage(){m_hitpoints -= 2;}
    virtual bool isAlive(){
        if(Actor::isAlive()==false) return false;
        if(m_hitpoints<=0){
            Actor::setDeath();
            return false;
        }
        return true;
    }

    
private:
    int m_hitpoints;
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
    
    virtual void damage(){m_hitpoints -= 2;}
    
    virtual bool isAlive(){
        if(Actor::isAlive()==false) return false;
        if(m_hitpoints==0){
            Actor::setDeath();
            return false;
        }
        return true;
    }
    
    virtual bool pushed(Direction);

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
