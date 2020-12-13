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
    virtual void effect(std::shared_ptr<Game> game) const;
    TriggeredAbilityType getType() const;
    std::string getDescription() const;
};

class DieDamage : public TriggeredAbility
{
    std::shared_ptr<Minion> minion;

public:
    explicit DieDamage(std::shared_ptr<Minion> minion);
    void effect(std::shared_ptr<Game> game) const override;
    std::shared_ptr<Minion> getMinion() const;
};

class EnterDamage : public TriggeredAbility
{
    std::shared_ptr<Minion> minion;

public:
    explicit EnterDamage(std::shared_ptr<Minion> minion);
    void effect(std::shared_ptr<Game> game) const override;
    std::shared_ptr<Minion> getMinion() const;
};

class EndGainDef : public TriggeredAbility
{
    std::shared_ptr<Minion> minion;

public:
    explicit EndGainDef(std::shared_ptr<Minion> minion);
    void effect(std::shared_ptr<Game> game) const override;
    std::shared_ptr<Minion> getMinion() const;
};

class StartGainMagic : public TriggeredAbility
{
    std::shared_ptr<Ritual> ritual;

public:
    explicit StartGainMagic(std::shared_ptr<Ritual> ritual);
    void effect(std::shared_ptr<Game> game) const override;
    std::shared_ptr<Ritual> getRitual() const;
};

class EnterGainAtkDef : public TriggeredAbility
{
    std::shared_ptr<Ritual> ritual;

public:
    explicit EnterGainAtkDef(std::shared_ptr<Ritual> ritual);
    void effect(std::shared_ptr<Game> game) const override;
    std::shared_ptr<Ritual> getRitual() const;
};

class EnterDestroy : public TriggeredAbility
{
    std::shared_ptr<Ritual> ritual;

public:
    explicit EnterDestroy(std::shared_ptr<Ritual> ritual);
    void effect(std::shared_ptr<Game> game) const override;
    std::shared_ptr<Ritual> getRitual() const;
};

#endif
