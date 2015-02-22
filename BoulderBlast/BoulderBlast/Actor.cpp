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
            if((getWorld()->getMapContent(getX()-1, getY()))!='#'){
                getWorld()->setMapContent(getX(), getY(), ' ');
                getWorld()->setMapContent(getX()-1, getY(), '@');
                moveTo(getX()-1,getY());
            }
            
        }
        else if(ch== KEY_PRESS_RIGHT) {
            setDirection(right);
            if((getWorld()->getMapContent(getX()+1, getY()))!='#'){
                getWorld()->setMapContent(getX(), getY(), ' ');
                getWorld()->setMapContent(getX()+1, getY(), '@');
                moveTo(getX()+1,getY());
            }
        }
        else if(ch== KEY_PRESS_UP) {
            setDirection(up);
            if((getWorld()->getMapContent(getX(), getY()+1))!='#'){
                getWorld()->setMapContent(getX(), getY(), ' ');
                getWorld()->setMapContent(getX(), getY()+1, '@');
                moveTo(getX(),getY()+1);
            }
        }
        else if(ch== KEY_PRESS_DOWN) {
            setDirection(down);
            if((getWorld()->getMapContent(getX(), getY()-1))!='#'){
                getWorld()->setMapContent(getX(), getY(), ' ');
                getWorld()->setMapContent(getX(), getY()-1, '@');
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
    char m[15][15];
    for(int x=0; x<15; x++){
        for(int y=0; y<15;y++){
            m[x][y]=getWorld()->getMapContent(y, 14-x);
            cout<<m[x][y];
        }
        cout<<endl;
    }
    return 0;

}

int Wall::doSomething(){
    return 0;
}

int Bullet::doSomething(){
    if(!isAlive()) return -1;
    if(getDirection()==up){//if goes up
        if(getWorld()->getMapContent(getX(), getY()+1)==' '){//can move
            getWorld()->setMapContent(getX(), getY(), ' ');
            getWorld()->setMapContent(getX(), getY()+1, '.');
            moveTo(getX(),getY()+1);
        }
    }
    else if(getDirection()==down){//if goes down
        if((getWorld()->getMapContent(getX(), getY()-1))==' '){
            getWorld()->setMapContent(getX(), getY(), ' ');
            getWorld()->setMapContent(getX(), getY()-1, '.');
            moveTo(getX(),getY()-1);
        }
    }
    else if(getDirection()==left){
        if((getWorld()->getMapContent(getX()-1, getY()))==' '){
            getWorld()->setMapContent(getX(), getY(), ' ');
            getWorld()->setMapContent(getX()-1, getY(), '.');
            moveTo(getX()-1,getY());
        }
    }
    else if(getDirection()==right){
        if((getWorld()->getMapContent(getX()+1, getY()))==' '){
            getWorld()->setMapContent(getX(), getY(), ' ');
            getWorld()->setMapContent(getX()+1, getY(), '.');
            moveTo(getX()+1,getY());
        }
    }
    
    return 0;
}

int Boulder::doSomething(){
    return 0;
}

int Hole::doSomething(){
    return 0;
}

int Goodie::doSomething(){
    if(getWorld()->getPlayer()->getX()==getX()&&getWorld()->getPlayer()->getY()==getY()){
        setDeath();
        getWorld()->setMapContent(getX(), getY(), ' ');
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