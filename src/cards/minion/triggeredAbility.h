#ifndef TRIGGERED_ABILITY_H
#define TRIGGERED_ABILITY_H

#include <memory>
#include <string>
#include <vector>
#include <iostream>


class Game;
class Minion;
class Ritual;

enum TriggeredAbilityType
{
    START_TURN,
    END_TURN,
    MINION_ENTER,
    MINION_DEATH,
    ENEMY_MINION_ENTER,
    OWN_MINION_ENTER
};

class TriggeredAbility{
    // Description of the ability displayed on the view
    std::string description;
    /* 0 for at the start of the turn
       1 for at the end of the turn
       2 for whenever a minion enters play
       3 for when the minion dies
       4 for when the opponent minion enter the play
       5 for when the self minion enter the play
    */
    TriggeredAbilityType type;

    public:
        // Default constructor
        TriggeredAbility();
        // Constructor
        TriggeredAbility(std::string description, TriggeredAbilityType type);
        // Making effect, called by Game::checkTriggered or Minion::die
        virtual void effect(std::shared_ptr<Game> game, std::shared_ptr<Minion> minion) const;
        // Making effect, called by Ritual::useTrgAbility
        virtual void effect(std::shared_ptr<Game> game, std::shared_ptr<Ritual> ritual) const;

        // Getters
        TriggeredAbilityType getType() const;
        std::string getDescription() const;

        // Destructor
        virtual ~TriggeredAbility();
};

class DieDamage : public TriggeredAbility{

    public:
        DieDamage();
        // Deal damage equal to minion->getAtk() to all opponent minions 
        void effect(std::shared_ptr<Game> game, std::shared_ptr<Minion> minion) const override;
};

class EnterDamage : public TriggeredAbility{

    public:
        EnterDamage();
        // Deal 1 damage to opponent's top Minion on board
        void effect(std::shared_ptr<Game> game, std::shared_ptr<Minion> minion) const override;
};

class EndGainDef : public TriggeredAbility{

    public:
        EndGainDef();
        // All owner's Minions gain +0/+1
        void effect(std::shared_ptr<Game> game, std::shared_ptr<Minion> minion) const override;
};

class StartGainMagic : public TriggeredAbility{

    public:
        StartGainMagic();
        // Owner gain 1 magic
        void effect(std::shared_ptr<Game> game, std::shared_ptr<Ritual> ritual) const override;
};

class EnterGainAtkDef : public TriggeredAbility{

    public:
        EnterGainAtkDef();
        // Owner's top Minion on Board gain +1/+1
        void effect(std::shared_ptr<Game> game, std::shared_ptr<Ritual> ritual) const override;
};

class EnterDestroy : public TriggeredAbility{

    public:
        EnterDestroy();
        // Destroy top Minion on the Board of game->getActivePlayer
        void effect(std::shared_ptr<Game> game, std::shared_ptr<Ritual> ritual) const override;
};

class EndDestroy : public TriggeredAbility {
    public:
        EndDestroy();
        // Destroy top Minion on the Board of game->getActivePlayer
        void effect(std::shared_ptr<Game> game, std::shared_ptr<Ritual> ritual) const override;
};

#endif
