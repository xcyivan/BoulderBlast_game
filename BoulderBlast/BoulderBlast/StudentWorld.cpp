#include "StudentWorld.h"
#include <string>
using namespace std;

GameWorld* createStudentWorld(string assetDir)
{
	return new StudentWorld(assetDir);
}


/////////////init()///////////////////////////
int StudentWorld:: init(){
    
    ////////load level///////////////
    string curLevel = "level02.dat";
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
    //decLives();
    //pp->doSomething();
    if(pp->doSomething()==-1){
        decLives();
        return GWSTATUS_PLAYER_DIED;
    }
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









