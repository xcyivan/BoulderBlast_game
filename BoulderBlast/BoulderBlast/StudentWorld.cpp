#include "StudentWorld.h"
using namespace std;

GameWorld* createStudentWorld(string assetDir)
{
	return new StudentWorld(assetDir);
}


/////////////init()///////////////////////////
int StudentWorld:: init(){
    
    ///////reset parameters/////////
    setBonus(1000);
    m_canExit=false;

    
    ////////load level///////////////
    string curLevel = getLevelDat(getLevel());
    Level lev(assetDirectory());
    Level::LoadResult result = lev.loadLevel(curLevel);
    if (result == Level:: load_fail_bad_format)
        return GWSTATUS_LEVEL_ERROR;
    if (result ==Level::load_fail_file_not_found || getLevel()==99)
        return GWSTATUS_PLAYER_WON;
    //already loaded successfully
    //copy the map down
    for(int x=0; x<15; x++){
        for(int y=0; y<15;y++){
            Level:: MazeEntry item = lev.getContentsOf(x, y);
            
            if(item==Level::exit) {
                av.push_back(new Exit(this,x,y));
            }
            else if(item==Level::player) {
                pp = new Player(this, x, y);
            }
            else if(item==Level::horiz_snarlbot) {
                av.push_back(new Snarlbot(this, x, y, Actor::right));
            }
            else if(item==Level::vert_snarlbot) {
                av.push_back(new Snarlbot(this, x, y, Actor::down));
            }
            else if(item==Level::kleptobot_factory) {
                av.push_back(new Factory(this, x, y, 0));
            }
            else if(item==Level::angry_kleptobot_factory) {
                av.push_back(new Factory(this, x, y, 1));
            }
            else if(item==Level::wall) {
                av.push_back(new Wall(this, x,y));
            }
            else if(item==Level::boulder) {
                av.push_back(new Boulder(this,x,y));
            }
            else if(item==Level::hole) {
                av.push_back(new Hole(this,x,y));
            }
            else if(item==Level::jewel) {
                av.push_back(new Jewel(this,x,y));
                m_jewelCount++;
            }
            else if(item==Level::restore_health) {
                av.push_back(new RestoreLifeGoodie(this,x,y));
            }
            else if(item==Level::extra_life) {
                av.push_back(new ExtraLifeGoodie(this,x,y));
            }
            else if(item==Level::ammo) {
                av.push_back(new AmmoGoodie(this,x,y));
            }
        }
    }
    ////////////end of load level //////////////////////////
    return GWSTATUS_CONTINUE_GAME;
}



int StudentWorld:: move(){
    cout<<"move()::==============="<<endl;
    //ask Player to do something
    int ppstatus = pp->doSomething();
    if(ppstatus==-1){
        decLives();
        return GWSTATUS_PLAYER_DIED;
    }
    //if fire a bullet
    else if(ppstatus==Actor::up){
        av.push_back(new Bullet(this, pp->getX(), pp->getY()+1, Actor::up));
    }
    else if(ppstatus==Actor::down){
        av.push_back(new Bullet(this, pp->getX(), pp->getY()-1, Actor::down));
    }
    else if(ppstatus==Actor::left){
        av.push_back(new Bullet(this, pp->getX()-1, pp->getY(), Actor::left));
    }
    else if(ppstatus==Actor::right){
        av.push_back(new Bullet(this, pp->getX()+1, pp->getY(), Actor::right));
    }

    //ask other objects to do something and delete dead objects
    vector<Actor*> :: iterator ap = av.begin();
    int i=0;
    while(ap!=av.end()){
        if((*ap)==nullptr){
            cout<<"oh! I'm nullptr?!!! at av. " << i <<endl;
            break;
        }
        if((*ap)->getName()=="klepto") {cout<<"I'm the       klepto at av"<<i <<endl;}
        if((*ap)->getName()=="angry")  {cout<<"I'm the angry klepto at av"<<i <<endl;}
        int result =(*ap)->doSomething();
        if(result==-1) {
            (*ap)->setVisible(false);
            delete *ap;
            ap = av.erase(ap);
            i--;
        }
        else if(result==-2) return GWSTATUS_FINISHED_LEVEL;
        else {ap++;i++;}
    }
    
    //decrease the bonus
    decBonus();
    
    //expose exit if possible
    if(m_jewelCount==0) {
        m_canExit=true;
        playSound(SOUND_REVEAL_EXIT);
        m_jewelCount--;
        vector<Actor*> :: iterator ap = av.begin();
        while(ap!=av.end()){
            if((*ap)->getName()=="exit") (*ap)->setVisible(true);
            ap++;
        }
    }
    
    //update the game text
    setDisplayText();
    
    return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld:: cleanUp(){
    delete pp;
    vector<Actor*> :: iterator ap = av.begin();
    while(ap!=av.end()){
        delete *ap;
        ap = av.erase(ap);
    }
}

void StudentWorld::setDisplayText(){
    int score = getScore();
    int level = getLevel();
    int bonus = getBonus();
    int lives = getLives();
    int health = pp->getHealth();
    int ammo = pp->getAmmo();
    string s = transform(score, level, bonus, lives, health, ammo);
    setGameStatText(s);
}

string StudentWorld::transform(int score, int level, int bonus, int lives, int health, int ammo){
    int healthPct = 100*health/20;
    ostringstream oss;
    oss.fill('0');
    oss<<"Score: "<<setw(7)<<score<<"  "
	   <<"Level: "<<setw(2)<<level<<"  ";
    oss.fill(' ');
    oss<<"Lives: "<<setw(2)<<lives<<"  "
	   <<"Health: "<<setw(3)<<healthPct<<'%'<<"  "
	   <<"Ammo: "<<setw(3)<<ammo<<"  "
    <<"Bonus: "<<setw(4)<<bonus<<endl;
    
    string s = oss.str();
    return s;
}

vector<Actor*> StudentWorld::getMapAt(int x, int y){
    vector<Actor*> ret;
    if(pp->getX()==x && pp->getY()==y) ret.push_back(pp);
    for(vector<Actor*>::iterator p=av.begin(); p!=av.end(); p++){
        if((*p)->getX()==x && (*p)->getY()==y) ret.push_back(*p);
    }
    return ret;
}

void StudentWorld::addActor(int x, int y, Actor::Direction dir, string name){
    if(name=="bullet") av.push_back(new Bullet(this, x, y, dir));
    else if(name=="klepto") av.push_back(new Kleptobot(this, x, y));
    else if(name=="extra") av.push_back(new ExtraLifeGoodie(this, x, y));
    else if(name=="restore") av.push_back(new RestoreLifeGoodie(this, x, y));
    else if(name=="ammo") av.push_back(new AmmoGoodie(this, x, y));
    else if(name=="angry") av.push_back(new AngryKleptobot(this, x, y));
    
    cout<<"new Actor added, av.size= :"<<av.size()<<endl;
}






