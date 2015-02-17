#include "StudentWorld.h"
#include <string>
using namespace std;

GameWorld* createStudentWorld(string assetDir)
{
	return new StudentWorld(assetDir);
}

int StudentWorld:: init(){
    
///////////load level///////////////
    string curLevel = "level00.dat";
    Level lev(assetDirectory());
    Level::LoadResult result = lev.loadLevel(curLevel);
    if (result == Level::load_fail_file_not_found || result == Level:: load_fail_bad_format)
        return -1;
    //already loaded successfully
    //copy the map down
    char map[15][15];
    for(int x=0; x<15; x++){
        for(int y=0; y<15;y++){
            Level:: MazeEntry item = lev.getContentsOf(x, y);
            if(item==Level:: empty) map[14-y][x]=' ';
            else if(item==Level::exit) map[14-y][x]='x';
            else if(item==Level::player) {
                map[14-y][x]='@';
                pp = new Player(x, y);
                pp->setVisible(true);
            }
            else if(item==Level::horiz_snarlbot) map[14-y][x]='h';
            else if(item==Level::vert_snarlbot) map[14-y][x]='v';
            else if(item==Level::kleptobot_factory) map[14-y][x]='1';
            else if(item==Level::angry_kleptobot_factory) map[14-y][x]='2';
            else if(item==Level::wall) {
                map[14-y][x]='#';
                av.push_back(new Wall(x,y));
                av.back()->setVisible(true);
            }
            else if(item==Level::boulder) map[14-y][x]='b';
            else if(item==Level::hole) map[14-y][x]='o';
            else if(item==Level::jewel) map[14-y][x]='*';
            else if(item==Level::restore_health) map[14-y][x]='r';
            else if(item==Level::extra_life) map[14-y][x]='e';
            else if(item==Level::ammo) map[14-y][x]='a';
            else map[14-y][x]='?';
        }
    }
    for(int x=0; x<15; x++){
        for(int y=0; y<15; y++){
            cout<<map[x][y];
        }
        cout<<endl;
    }
////////////end of load level //////////////////////////
    return GWSTATUS_CONTINUE_GAME;
}


int StudentWorld:: move(){
    decLives();
    return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld:: cleanUp(){}
