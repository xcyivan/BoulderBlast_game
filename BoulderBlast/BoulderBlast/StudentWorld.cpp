#include "StudentWorld.h"
using namespace std;

GameWorld* createStudentWorld(string assetDir)
{
	return new StudentWorld(assetDir);
}


/////////////init()///////////////////////////
int StudentWorld:: init(){
    
    ////////load level///////////////
    string curLevel = "level02.dat";
    setBonus(1000);
    Level lev(assetDirectory());
    Level::LoadResult result = lev.loadLevel(curLevel);
    if (result == Level::load_fail_file_not_found || result == Level:: load_fail_bad_format)
        return -1;
    //already loaded successfully
    //copy the map down
    for(int x=0; x<15; x++){
        for(int y=0; y<15;y++){
            Level:: MazeEntry item = lev.getContentsOf(x, y);
            
            if(item==Level:: empty) map[x][y]=' ';
            else if(item==Level::exit) map[x][y]='x';
            else if(item==Level::player) {
                map[x][y]='@';
                pp = new Player(this, x, y);
            }
            else if(item==Level::horiz_snarlbot) map[x][y]='h';
            else if(item==Level::vert_snarlbot) map[x][y]='v';
            else if(item==Level::kleptobot_factory) map[x][y]='1';
            else if(item==Level::angry_kleptobot_factory) map[x][y]='2';
            else if(item==Level::wall) {
                map[x][y]='#';
                av.push_back(new Wall(this, x,y));
            }
            else if(item==Level::boulder) {
                map[x][y]='b';
                av.push_back(new Boulder(this,x,y));
            }
            else if(item==Level::hole) {
                map[x][y]='o';
                av.push_back(new Hole(this,x,y));
            }
            else if(item==Level::jewel) {
                map[x][y]='*';
                av.push_back(new Jewel(this,x,y));
            }
            else if(item==Level::restore_health) {
                map[x][y]='r';
                av.push_back(new RestoreLifeGoodie(this,x,y));
            }
            else if(item==Level::extra_life) {
                map[x][y]='e';
                av.push_back(new ExtraLifeGoodie(this,x,y));
            }
            else if(item==Level::ammo) {
                map[x][y]='a';
                av.push_back(new AmmoGoodie(this,x,y));
            }
            else map[x][y]='?';
        }
    }
    ////////////end of load level //////////////////////////
    return GWSTATUS_CONTINUE_GAME;
}



int StudentWorld:: move(){
    cout<<"move()::==============="<<endl;
    //update the game text
    setDisplayText();
    //ask Player to do something
    if(pp->doSomething()==-1){
        decLives();
        return GWSTATUS_PLAYER_DIED;
    }
    //ask other objects to do something and delete dead objects
    vector<Actor*> :: iterator ap = av.begin();
    while(ap!=av.end()){
        int result =(*ap)->doSomething();
        if(result==-1) {
            (*ap)->setVisible(false);
            delete *ap;
            ap = av.erase(ap);
        }
        else ap++;
    }
    
    //decrease the bonus
    decBonus();
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








