#ifndef TRIGGERED_ABILITY_H
#define TRIGGERED_ABILITY_H

#include <string>
#include "../card.h"
#include "../../game/game.h"
#include "minion.h"

enum TriggeredAbilityType {start, end, enter, death, opponentEnter, selfEnter};

class TriggeredAbility {
    // Description of the ability displayed on the view
    std::string description;
    /* 1 for at the start of the turn
       2 for at the end of the turn
       3 for whenever a minion enters play
       4 for when the minion dies
       5 for when the opponent minion enter the play
       6 for when the self minion enter the play
    */
    int type;
    std::shared_ptr<Minion> minion;



    public:
        TriggeredAbility();
        TriggeredAbility(std::string description, int type, std::shared_ptr<Minion> minion);
        virtual void effect(Game game) const;
        int getType() const ;
        std::string getDescription() const;
        std::shared_ptr<Minion> getMinion() const;
        

};

class DieDamage : public TriggeredAbility{
    public:
        explicit DieDamage(std::shared_ptr<Minion> minion);
        void effect(Game game) const override;
};

class EnterDamage : public TriggeredAbility{
    public:
        explicit EnterDamage(std::shared_ptr<Minion> minion);
        void effect(Game game) const override;
};

class EndGainDef : public TriggeredAbility{
    public:
        explicit EndGainDef(std::shared_ptr<Minion> minion);
        void effect(Game game) const override;

};

#endif
