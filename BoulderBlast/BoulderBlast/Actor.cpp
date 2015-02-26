#include "Actor.h"
#include "StudentWorld.h"

bool Actor::clearToMove(){
    Direction dir = getDirection();
    if(dir==up){
        if((getWorld()->getMapAt(getX(),getY()+1)).size()==0 ||
           (getWorld()->getMapAt(getX(),getY()+1)).at(0)->getName()=="jewel" ||
           (getWorld()->getMapAt(getX(),getY()+1)).at(0)->getName()=="extra" ||
           (getWorld()->getMapAt(getX(),getY()+1)).at(0)->getName()=="restore" ||
           (getWorld()->getMapAt(getX(),getY()+1)).at(0)->getName()=="ammo" ||
           (getWorld()->getMapAt(getX(),getY()+1)).at(0)->getName()=="exit" ||
           (getWorld()->getMapAt(getX(),getY()+1)).at(0)->getName()=="bullet")
                return true;
    }
    else if(dir==down){
        if((getWorld()->getMapAt(getX(),getY()-1)).size()==0 ||
           (getWorld()->getMapAt(getX(),getY()-1)).at(0)->getName()=="jewel" ||
           (getWorld()->getMapAt(getX(),getY()-1)).at(0)->getName()=="extra" ||
           (getWorld()->getMapAt(getX(),getY()-1)).at(0)->getName()=="restore" ||
           (getWorld()->getMapAt(getX(),getY()-1)).at(0)->getName()=="ammo" ||
           (getWorld()->getMapAt(getX(),getY()-1)).at(0)->getName()=="exit" ||
           (getWorld()->getMapAt(getX(),getY()-1)).at(0)->getName()=="bullet")
                return true;
    }
    else if(dir==left){
        if((getWorld()->getMapAt(getX()-1,getY())).size()==0 ||
           (getWorld()->getMapAt(getX()-1,getY())).at(0)->getName()=="jewel" ||
           (getWorld()->getMapAt(getX()-1,getY())).at(0)->getName()=="extra" ||
           (getWorld()->getMapAt(getX()-1,getY())).at(0)->getName()=="restore" ||
           (getWorld()->getMapAt(getX()-1,getY())).at(0)->getName()=="ammo" ||
           (getWorld()->getMapAt(getX()-1,getY())).at(0)->getName()=="exit" ||
           (getWorld()->getMapAt(getX()-1,getY())).at(0)->getName()=="bullet")
                return true;
    }
    else if(dir==right){
        if((getWorld()->getMapAt(getX()+1,getY())).size()==0 ||
           (getWorld()->getMapAt(getX()+1,getY())).at(0)->getName()=="jewel" ||
           (getWorld()->getMapAt(getX()+1,getY())).at(0)->getName()=="extra" ||
           (getWorld()->getMapAt(getX()+1,getY())).at(0)->getName()=="restore" ||
           (getWorld()->getMapAt(getX()+1,getY())).at(0)->getName()=="ammo" ||
           (getWorld()->getMapAt(getX()+1,getY())).at(0)->getName()=="exit" ||
           (getWorld()->getMapAt(getX()+1,getY())).at(0)->getName()=="bullet")
                return true;
    }
    return false;
}



int Player::doSomething(){
    if(isAlive()==false) return -1;
    int ch;
    if (getWorld()->getKey(ch)) {
        // user hit a key this tick! switch (ch)
        if(ch== KEY_PRESS_LEFT) {
            setDirection(left);
            if(clearToMove())   moveTo(getX()-1,getY());
            else if((getWorld()->getMapAt(getX()-1,getY())).at(0)->getName()=="boulder"){
                if((getWorld()->getMapAt(getX()-1,getY())).at(0)->pushed(left))//if can push left
                   moveTo(getX()-1,getY());
            }
        }
        else if(ch== KEY_PRESS_RIGHT) {
            setDirection(right);
            if(clearToMove())   moveTo(getX()+1,getY());
            else if((getWorld()->getMapAt(getX()+1,getY())).at(0)->getName()=="boulder"){
                if((getWorld()->getMapAt(getX()+1,getY())).at(0)->pushed(right))//if can push right
                    moveTo(getX()+1,getY());
            }
        }
        else if(ch== KEY_PRESS_UP) {
            setDirection(up);
            if(clearToMove())   moveTo(getX(),getY()+1);
            else if((getWorld()->getMapAt(getX(),getY()+1)).at(0)->getName()=="boulder"){
                if((getWorld()->getMapAt(getX(),getY()+1)).at(0)->pushed(up))//if can push up
                    moveTo(getX(),getY()+1);
            }
        }
        else if(ch== KEY_PRESS_DOWN) {
            setDirection(down);
            if(clearToMove())   moveTo(getX(),getY()-1);
            else if((getWorld()->getMapAt(getX(),getY()-1)).at(0)->getName()=="boulder"){
                if((getWorld()->getMapAt(getX(),getY()-1)).at(0)->pushed(down))//if can push down
                    moveTo(getX(),getY()-1);
            }
        }
        else if(ch== KEY_PRESS_SPACE) {
            if(getWorld()->getPlayer()->getAmmo()>0){
                getWorld()->getPlayer()->decreaseAmmo();
                return getDirection();
            }
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
bool Snarlbot::canMove(){
    int level = getWorld()->getLevel();
    int ticks = (28-level)/4;
    if (ticks<3) ticks=3;
    ticksCount = (ticksCount+1)%ticks;
    if(ticksCount==0) return true;
    else return false;
}

bool Snarlbot::canFire(){
    bool aline = false;
    bool clear = true;
    if(getDirection()==up){
        aline = getWorld()->getPlayer()->getX()==getX() && getWorld()->getPlayer()->getY()>getY();
        for(int y=getY()+1; y<getWorld()->getPlayer()->getY(); y++){
            vector<Actor*> v=getWorld()->getMapAt(getX(), y);
            for(int i=0; i<v.size(); i++)
                if(v.at(i)->getName()=="wall"||v.at(i)->getName()=="boulder"||v.at(i)->getName()=="snarl"||v.at(i)->getName()=="klepto"||v.at(i)->getName()=="factory")
                    clear=false;
        }
    }
    else if(getDirection()==down){
        aline = getWorld()->getPlayer()->getX()==getX() && getWorld()->getPlayer()->getY()<getY();
        for(int y=getY()-1; y>getWorld()->getPlayer()->getY(); y--){
            vector<Actor*> v=getWorld()->getMapAt(getX(), y);
            for(int i=0; i<v.size(); i++)
                if(v.at(i)->getName()=="wall"||v.at(i)->getName()=="boulder"||v.at(i)->getName()=="snarl"||v.at(i)->getName()=="klepto"||v.at(i)->getName()=="factory")
                    clear=false;
        }
    }
    else if(getDirection()==left){
        aline = getWorld()->getPlayer()->getX()<getX() && getWorld()->getPlayer()->getY()==getY();
        for(int x=getX()-1; x>getWorld()->getPlayer()->getX(); x--){
            vector<Actor*> v=getWorld()->getMapAt(x, getY());
            for(int i=0; i<v.size(); i++)
                if(v.at(i)->getName()=="wall"||v.at(i)->getName()=="boulder"||v.at(i)->getName()=="snarl"||v.at(i)->getName()=="klepto"||v.at(i)->getName()=="factory")
                    clear=false;
        }
    }
    else if(getDirection()==right){
        aline = getWorld()->getPlayer()->getX()>getX() && getWorld()->getPlayer()->getY()==getY();
        for(int x=getX()+1; x<getWorld()->getPlayer()->getX(); x++){
            vector<Actor*> v=getWorld()->getMapAt(x, getY());
            for(int i=0; i<v.size(); i++)
                if(v.at(i)->getName()=="wall"||v.at(i)->getName()=="boulder"||v.at(i)->getName()=="snarl"||v.at(i)->getName()=="klepto"||v.at(i)->getName()=="factory")
                    clear=false;
        }
    }
    bool res = aline && clear;
    return res;
}

int Snarlbot::doSomething(){
    if(!isAlive()) {getWorld()->increaseScore(100);return -1;}
    if(!canMove())return 0;
    
    //if can move
    if(getDirection()==up){
        if (canFire()){
            getWorld()->addActor(getX(), getY()+1, up, "bullet");
            return 0;
        }
        if(clearToMove())   moveTo(getX(),getY()+1);
        else    setDirection(down);
    }
    else if(getDirection()==down){
        if(canFire()){
            getWorld()->addActor(getX(), getY()-1, down, "bullet");
            return 0;
        }
        if(clearToMove())   moveTo(getX(),getY()-1);
        else    setDirection(up);
    }
    else if(getDirection()==left){
        if(canFire()){
            getWorld()->addActor(getX()-1, getY(), left, "bullet");
            return 0;
        }
        if(clearToMove())   moveTo(getX()-1,getY());
        else    setDirection(right);
    }
    else if(getDirection()==right){
        if(canFire()){
            getWorld()->addActor(getX()+1, getY(), right, "bullet");
            return 0;
        }
        if(clearToMove())   moveTo(getX()+1,getY());
        else    setDirection(left);
    }
    return 0;
}

int Factory::doSomething(){
    if(canMove()) {
        getWorld()->addActor(getX(), getY(), right, "klepto");
    }
    return 0;
}

bool BaseKlepto::canMove(){
    int level = getWorld()->getLevel();
    int ticks = (28-level)/4;
    if (ticks<3) ticks=3;
    ticksCount = (ticksCount+1)%ticks;
    if(ticksCount==0) return true;
    else return false;
}

void BaseKlepto::turn(){
    stepsCount=0;
    m_step=rand()%6+1;
    int randdir = rand()%4+1;
    if(randdir==up) setDirection(up);
    else if(randdir==down) setDirection(down);
    else if(randdir==left) setDirection(left);
    else if(randdir==right)setDirection(right);
}

int BaseKlepto::doSomething(){
    if(!isAlive()) return -1;
    if(!canMove()) return 0;
    if(stepsCount<m_step){
        if(getDirection()==up){
            if(clearToMove()){
                moveTo(getX(),getY()+1);
                stepsCount++;
            }
            else turn();
        }
        else if(getDirection()==down){
            if(clearToMove()){
                moveTo(getX(),getY()-1);
                stepsCount++;
            }
            else turn();
        }
        else if(getDirection()==left){
            if(clearToMove()){
                moveTo(getX()-1,getY());
                stepsCount++;
            }
            else turn();
        }
        else if(getDirection()==right){
            if(clearToMove()){
                moveTo(getX()+1,getY());
                stepsCount++;
            }
            else turn();
        }
    }
    else turn();
    
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
            else if (v.at(i)->getName()=="boulder" ||
                     v.at(i)->getName()=="snarlbot" ||
                     v.at(i)->getName()=="klepto"){
                v.at(i)->damage();
                setDeath();
                return -1;
            }
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
    
    //if after the move, the bullet is hitting something
    if((getWorld()->getMapAt(getX(), getY())).size()!=0){
        vector<Actor*> v = getWorld()->getMapAt(getX(), getY());
        for(int i=0; i<v.size(); i++){
            if(v.at(i)->getName()=="wall") {setDeath(); return -1;}
            else if (v.at(i)->getName()=="boulder" ||
                     v.at(i)->getName()=="snarlbot" ||
                     v.at(i)->getName()=="klepto"){
                v.at(i)->damage();
                setDeath();
                return -1;
            }
        }
    }

    
    return 0;
}

bool Boulder::pushed(Direction dir){
    if(dir==up){//if goes up
        if((getWorld()->getMapAt(getX(),getY()+1)).size()==0||
           (getWorld()->getMapAt(getX(),getY()+1)).at(0)->getName()=="hole"){
            moveTo(getX(),getY()+1);
            return true;
        }
        else return false;
    }
    else if(dir==down){//if goes down
        if((getWorld()->getMapAt(getX(),getY()-1)).size()==0 ||
           (getWorld()->getMapAt(getX(),getY()-1)).at(0)->getName()=="hole"){
            moveTo(getX(),getY()-1);
            return true;
        }
        else return false;
    }
    else if(dir==left){//if goes left
        if((getWorld()->getMapAt(getX()-1,getY())).size()==0 ||
           (getWorld()->getMapAt(getX()-1,getY())).at(0)->getName()=="hole"){
            moveTo(getX()-1,getY());
            return true;
        }
        else return false;
    }
    else if(dir==right){//if goes right
        if((getWorld()->getMapAt(getX()+1,getY())).size()==0 ||
           (getWorld()->getMapAt(getX()+1,getY())).at(0)->getName()=="hole"){
            moveTo(getX()+1,getY());
            return true;
        }
        else return false;
    }
    return false;
}

int Boulder::doSomething(){
    if(isAlive()==false) {return -1;}
    return 0;
}

int Hole::doSomething(){
    if(isAlive()==false) return -1;
    vector<Actor*> v = getWorld()->getMapAt(getX(), getY());
    for(int i=0; i<v.size();i++){
        if(v.at(i)->getName()=="boulder"){
            v.at(i)->setDeath();   //I don't know why this line doesn't work
                                   //I know now~~!! pay special attention to the Boulder::isAlive() function which is a virtual one so the normal Actor::setDeath() should be considered in this Boulder::isAlive()
            setDeath();
            return -1;
        }
    }
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