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
            moveTo(getX()-1,getY());
        }
        else if(ch== KEY_PRESS_RIGHT) {
            setDirection(right);
            moveTo(getX()+1,getY());
        }
        else if(ch== KEY_PRESS_UP) {
            setDirection(up);
            moveTo(getX(),getY()+1);
        }
        else if(ch== KEY_PRESS_DOWN) {
            setDirection(down);
            moveTo(getX(),getY()-1);
        }
        else if(ch== KEY_PRESS_SPACE) cout<<"space"<<endl;
        else if(ch== KEY_PRESS_ESCAPE) cout<<"escape"<<endl;
    }
    return 0;

}