#include "Actor.h"
#include "StudentWorld.h"

// Students:  Add code to this file (if you wish), Actor.h, StudentWorld.h, and StudentWorld.cpp
int Player::doSomething(){
    if(isAlive()==false) return -1;
    int ch;
    if (getWorld()->getKey(ch)) {
        // user hit a key this tick! switch (ch)
        if(ch== KEY_PRESS_LEFT) {
            setDirection(left);
            if((getWorld()->getMapAt(getX()-1,getY())).size()==0 ||
               (getWorld()->getMapAt(getX()-1,getY())).at(0)->getName()=="jewel" ||
               (getWorld()->getMapAt(getX()-1,getY())).at(0)->getName()=="extra" ||
               (getWorld()->getMapAt(getX()-1,getY())).at(0)->getName()=="restore" ||
               (getWorld()->getMapAt(getX()-1,getY())).at(0)->getName()=="ammo"){
                moveTo(getX()-1,getY());
            }
        }
        else if(ch== KEY_PRESS_RIGHT) {
            setDirection(right);
            if((getWorld()->getMapAt(getX()+1,getY())).size()==0 ||
               (getWorld()->getMapAt(getX()+1,getY())).at(0)->getName()=="jewel" ||
               (getWorld()->getMapAt(getX()+1,getY())).at(0)->getName()=="extra" ||
               (getWorld()->getMapAt(getX()+1,getY())).at(0)->getName()=="restore" ||
               (getWorld()->getMapAt(getX()+1,getY())).at(0)->getName()=="ammo"){
                moveTo(getX()+1,getY());
            }
        }
        else if(ch== KEY_PRESS_UP) {
            setDirection(up);
            if((getWorld()->getMapAt(getX(),getY()+1)).size()==0 ||
               (getWorld()->getMapAt(getX(),getY()+1)).at(0)->getName()=="jewel" ||
               (getWorld()->getMapAt(getX(),getY()+1)).at(0)->getName()=="extra" ||
               (getWorld()->getMapAt(getX(),getY()+1)).at(0)->getName()=="restore" ||
               (getWorld()->getMapAt(getX(),getY()+1)).at(0)->getName()=="ammo"){
                moveTo(getX(),getY()+1);
            }
        }
        else if(ch== KEY_PRESS_DOWN) {
            setDirection(down);
            if((getWorld()->getMapAt(getX(),getY()-1)).size()==0 ||
               (getWorld()->getMapAt(getX(),getY()-1)).at(0)->getName()=="jewel" ||
               (getWorld()->getMapAt(getX(),getY()-1)).at(0)->getName()=="extra" ||
               (getWorld()->getMapAt(getX(),getY()-1)).at(0)->getName()=="restore" ||
               (getWorld()->getMapAt(getX(),getY()-1)).at(0)->getName()=="ammo"){
                moveTo(getX(),getY()-1);
            }
        }
        else if(ch== KEY_PRESS_SPACE) {
            return getDirection();
            //inform the StudentWorld that a bullet should be created and use this returned value to set the direction
        }
        else if(ch== KEY_PRESS_ESCAPE) {
            m_hitpoints=0;
            setDeath();
            return -1;
        }
    }
    return 0;

}

int Wall::doSomething(){
    return 0;
}

int Bullet::doSomething(){
    if(!isAlive()) return -1;
    //if the bullet is currently hitting something
    if((getWorld()->getMapAt(getX(), getY())).size()!=0){
        vector<Actor*> v = getWorld()->getMapAt(getX(), getY());
        for(int i=0; i<v.size(); i++){
            if(v.at(i)->getName()=="wall") {setDeath(); return -1;}
            else if (v.at(i)->getName()=="boulder"){v.at(i)->damage();setDeath(); return -1;}
        }
    }
    if(getDirection()==up){//if goes up
        moveTo(getX(),getY()+1);
    }
    else if(getDirection()==down){//if goes down
        moveTo(getX(),getY()-1);
    }
    else if(getDirection()==left){//if goes left
        moveTo(getX()-1,getY());
    }
    else if(getDirection()==right){//if goes right
        moveTo(getX()+1,getY());
    }
    
    return 0;
}

int Boulder::doSomething(){
    if(isAlive()==false) return -1;
    return 0;
}

int Hole::doSomething(){
    return 0;
}

int Goodie::doSomething(){
    if(getWorld()->getPlayer()->getX()==getX()&&getWorld()->getPlayer()->getY()==getY()){
        setDeath();
        return -1;
    }
    return 0;
}

int Exit::doSomething(){
    if(getWorld()->canExit() && Goodie::doSomething()==-1){
        cout<<"CONGRATULATIONS! YOU FIND THE EXIT!!"<<endl;
        getWorld()->incLives();
        return -2;
    }
    return 0;
}

int Jewel::doSomething(){
    if(Goodie::doSomething()==-1) {
        getWorld()->increaseScore(50);
        getWorld()->decJewCount();
        return -1;
    }
    return 0;
}

int ExtraLifeGoodie::doSomething(){
    if(Goodie::doSomething()==-1){
        getWorld()->increaseScore(1000);
        getWorld()->incLives();
        return -1;
    }
    return 0;
}

int RestoreLifeGoodie::doSomething(){
    if(Goodie::doSomething()==-1){
        getWorld()->increaseScore(500);
        getWorld()->getPlayer()->restoreHealth();
        return -1;
    }
    return 0;
}

int AmmoGoodie:: doSomething(){
    if(Goodie::doSomething()==-1){
        getWorld()->increaseScore(100);
        getWorld()->getPlayer()->increaseAmmo(20);
        return  -1;
    }
    return 0;
}