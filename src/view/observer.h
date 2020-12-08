#ifndef OBSERVER_H
#define OBSERVER_H

#include "../game/subject.h"

class Observer {
    public:
        // Set this to zero so that there MUST be a derived class to use update()
        virtual void update(Subject & game) = 0; 
};

#endif
