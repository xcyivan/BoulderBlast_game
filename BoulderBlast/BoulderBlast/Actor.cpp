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
            if((getWorld()->getMapCotent(getX()-1, getY()))!='#')
                moveTo(getX()-1,getY());
        }
        else if(ch== KEY_PRESS_RIGHT) {
            setDirection(right);
            if((getWorld()->getMapCotent(getX()+1, getY()))!='#')
                moveTo(getX()+1,getY());
        }
        else if(ch== KEY_PRESS_UP) {
            setDirection(up);
            if((getWorld()->getMapCotent(getX(), getY()+1))!='#')
                moveTo(getX(),getY()+1);
        }
        else if(ch== KEY_PRESS_DOWN) {
            setDirection(down);
            if((getWorld()->getMapCotent(getX(), getY()-1))!='#')
                moveTo(getX(),getY()-1);
        }
        else if(ch== KEY_PRESS_SPACE) cout<<"space"<<endl;
        else if(ch== KEY_PRESS_ESCAPE) {
            m_hitpoints=0;
            m_alive=false;
        }
    }
    return 0;

}
