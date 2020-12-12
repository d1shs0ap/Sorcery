#ifndef TRIGGERED_ABILITY_H
#define TRIGGERED_ABILITY_H

#include <string>
#include <vector>
#include "../card.h"
#include "../../game/game.h"
#include "minion.h"

enum TriggeredAbilityType {START_TURN, END_TURN, MINION_ENTER, MINION_DEATH, ENEMY_MINION_ENTER, OWN_MINION_ENTER};

class TriggeredAbility {
    // Description of the ability displayed on the view
    std::string description;
    /* 0 for at the start of the turn
       1 for at the end of the turn
       2 for whenever a minion enters play
       3 for when the minion dies
       4 for when the opponent minion enter the play
       5 for when the self minion enter the play
    */
    int type;
    std::shared_ptr<Minion> minion;



    public:
        TriggeredAbility();
        TriggeredAbility(std::string description, int type, std::shared_ptr<Minion> minion);
        virtual void effect(std::shared_ptr<Game> game) const;
        int getType() const ;
        std::string getDescription() const;
        std::shared_ptr<Minion> getMinion() const;
        

};

class DieDamage : public TriggeredAbility{
    public:
        explicit DieDamage(std::shared_ptr<Minion> minion);
        void effect(std::shared_ptr<Game> game) const override;
};

class EnterDamage : public TriggeredAbility{
    public:
        explicit EnterDamage(std::shared_ptr<Minion> minion);
        void effect(std::shared_ptr<Game> game) const override;
};

class EndGainDef : public TriggeredAbility{
    public:
        explicit EndGainDef(std::shared_ptr<Minion> minion);
        void effect(std::shared_ptr<Game> game) const override;

};

#endif
