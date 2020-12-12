#ifndef MINION_H
#define MINION_H

#include <memory>
#include <string>

#include "../card.h"
#include "activatedAbility.h"
#include "triggeredAbility.h"

class Player;

///////////////////////////////////////////////////////////////////////////////////////////////////
class Minion : public Card, public std::enable_shared_from_this<Minion> {
    int atk;
    int def;
    // actions is the number of times it is allowed to attack or use an ability in one turn. this can only be 0 or 1 for now.
    unsigned int actions = 0;
    unsigned int actionsCap = 1;

    // Activated abilities cost magic and an action point to use, and work similar to playing a spell card.
    ActivatedAbility actAbility;

    // Triggered abilities are activated for free whenever a certain condition is met.
    TriggeredAbility trgAbility;

public:
    Minion();
    Minion(std::string name, int owner, int cost, int atk, int def);

    int getAtk() const;
    virtual int computeAtk() const;
    void setAtk(int new_atk);
    int getDef() const;
    virtual int computeDef() const;
    void setDef(int new_def);

    void restoreAction();
    virtual ActivatedAbility getActAbility() const;
    virtual TriggeredAbility getTrgAbility() const;
    void setActAbility(ActivatedAbility ability);
    void setTrgAbility(TriggeredAbility ability);

    // checks if minion has triggered ability
    bool hasTrgAbility();

    void attack(std::shared_ptr<Player> player);
    void attack(std::shared_ptr<Minion> minion);
    void useAbility();
    void useAbility(int player, int target);

    std::string digitDisplay() const override;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
class AirElemental : public Minion
{
    public:
        AirElemental(int owner);
};

class EarthElemental : public Minion{
    public:
        EarthElemental(int owner);
};

class Bomb : public Minion{
    public:
        Bomb(int owner);
};

class FireElemental : public Minion{
    public:
        FireElemental(int owner);
};

class PotionSeller : public Minion{
    public:
        PotionSeller(int owner);
};

class NovicePyromancer : public Minion{
    public:
        NovicePyromancer(int owner);
};

class ApprenticeSummoner : public Minion{
    public:
        ApprenticeSummoner(int owner);
};

class MasterSummoner : public Minion{
    public:
        MasterSummoner(int owner);
};

///////////////////////////////////////////////////////////////////////////////////////////////////

#endif
