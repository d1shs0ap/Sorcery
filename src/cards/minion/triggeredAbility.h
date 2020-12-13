#ifndef TRIGGERED_ABILITY_H
#define TRIGGERED_ABILITY_H

#include <memory>
#include <string>
#include <vector>


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

class TriggeredAbility
{
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
    TriggeredAbility();
    TriggeredAbility(std::string description, TriggeredAbilityType type);
    virtual void effect(std::shared_ptr<Game> game, std::shared_ptr<Minion> minion) const;
    virtual void effect(std::shared_ptr<Game> game, std::shared_ptr<Ritual> ritual) const;
    TriggeredAbilityType getType() const;
    std::string getDescription() const;
};

class DieDamage : public TriggeredAbility
{

public:
    explicit DieDamage();
    void effect(std::shared_ptr<Game> game, std::shared_ptr<Minion> minion) const override;
};

class EnterDamage : public TriggeredAbility
{

public:
    explicit EnterDamage();
    void effect(std::shared_ptr<Game> game, std::shared_ptr<Minion> minion) const override;
};

class EndGainDef : public TriggeredAbility
{

public:
    explicit EndGainDef();
    void effect(std::shared_ptr<Game> game, std::shared_ptr<Minion> minion) const override;
    std::shared_ptr<Minion> getMinion() const;
};

class StartGainMagic : public TriggeredAbility
{

public:
    explicit StartGainMagic();
    void effect(std::shared_ptr<Game> game, std::shared_ptr<Ritual> ritual) const override;
};

class EnterGainAtkDef : public TriggeredAbility
{

public:
    explicit EnterGainAtkDef();
    void effect(std::shared_ptr<Game> game, std::shared_ptr<Ritual> ritual) const override;
};

class EnterDestroy : public TriggeredAbility
{

public:
    explicit EnterDestroy();
    void effect(std::shared_ptr<Game> game, std::shared_ptr<Ritual> ritual) const override;
};

#endif
