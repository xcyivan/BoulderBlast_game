#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include <iostream>

class Actor : public GraphObject{
public:
    void doSomething(){std::cout<<"Hi I'm doing something!"<<std::endl;}
};




#endif // ACTOR_H_
