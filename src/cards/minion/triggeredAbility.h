#ifndef TRIGGERED_ABILITY_H
#define TRIGGERED_ABILITY_H

#include <string>

class TriggeredAbility {
    // Description of the ability displayed on the view
    std::string description;
    /* 1 for at the start of the turn
       2 for at the end of the turn
       3 for whenever a minion enters play
       4 for when the minion dies
    */
    int type;


    public:
        virtual void effect();
        TriggeredAbility();
        TriggeredAbility(std::string description, int type);
        int getType();
        std::string getDescription();
        

};


#endif
