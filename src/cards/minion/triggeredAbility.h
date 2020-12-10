#ifndef TRIGGERED_ABILITY_H
#define TRIGGERED_ABILITY_H

#include <string>
#include "../card.h"
#include "../../game/game.h"
#include "minion.h"

class TriggeredAbility {
    // Description of the ability displayed on the view
    std::string description;
    /* 1 for at the start of the turn
       2 for at the end of the turn
       3 for whenever a minion enters play
       4 for when the minion dies
    */
    int type;
    int owner;
    std::shared_ptr<Minion> minion;



    public:
        TriggeredAbility();
        TriggeredAbility(std::string description, int type, int owner, std::shared_ptr<Minion> minion);
        virtual void effect(Card card) const;
        virtual void effect(Game game) const;
        int getType() const ;
        std::string getDescription() const;
        int getOwner() const;
        std::shared_ptr<Minion> getMinion() const;
        

};

class DieDamage : public TriggeredAbility{
    public:
        DieDamage(int owner, std::shared_ptr<Minion> minion);
        void effect(Card card) const override;
        void effect(Game game) const override;
};

#endif
