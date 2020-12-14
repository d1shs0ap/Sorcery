#ifndef MINION_H
#define MINION_H

#include <memory>
#include <string>
#include <iostream>

#include "../card.h"

class Player;
class TriggeredAbility;
class ActivatedAbility;
class Enchantment;
class Game;

///////////////////////////////////////////////////////////////////////////////////////////////////
class Minion : public Card, public std::enable_shared_from_this<Minion>{
    int atk;
    int def;
    // actions is the number of times it is allowed to attack or use an ability in one turn. this can only be 0 or 1 for now.

    // Activated abilities cost magic and an action point to use, and work similar to playing a spell card.
    std::shared_ptr<ActivatedAbility> actAbility;

    // Triggered abilities are activated for free whenever a certain condition is met.
    std::shared_ptr<TriggeredAbility> trgAbility;
    protected:
        unsigned int actions = 0;
        unsigned int actionsCap = 1;

    public:
        Minion();
        Minion(std::string name, int owner, int cost, int atk, int def, std::string type = "Minion");

        int getAtk() const;
        virtual int computeAtk() const;
        void setAtk(int new_atk);
        int getDef() const;
        virtual int computeDef() const;
        void setDef(int new_def);

        virtual void restoreAction();

        bool hasActAbility() const;
        std::shared_ptr<ActivatedAbility> getActAbility() const;
        virtual std::shared_ptr<ActivatedAbility> computeActAbility() const;
        void setActAbility(std::shared_ptr<ActivatedAbility> ability);
        // checks if minion has triggered ability
        bool hasTrgAbility() const;
        std::shared_ptr<TriggeredAbility> getTrgAbility() const;
        virtual std::shared_ptr<TriggeredAbility> computeTrgAbility() const;
        void setTrgAbility(std::shared_ptr<TriggeredAbility> ability);

        void attack(std::shared_ptr<Player> player);
        void attack(std::shared_ptr<Minion> minion);
        void useAbility(std::shared_ptr<Game> game);
        void useAbility(std::shared_ptr<Game> game, int player, int target);
        void triggered(std::shared_ptr<Game> game);

        virtual std::shared_ptr<Minion> getAttachedMinion();
        virtual std::vector<std::shared_ptr<Enchantment>> getEnchantmentList();

        virtual ~Minion();
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
class AirElemental : public Minion
{
public:
    explicit AirElemental(int owner);
};

class EarthElemental : public Minion
{
public:
    explicit EarthElemental(int owner);
};

class Bomb : public Minion
{
public:
    explicit Bomb(int owner);
};

class FireElemental : public Minion
{
public:
    explicit FireElemental(int owner);
};

class PotionSeller : public Minion
{
public:
    explicit PotionSeller(int owner);
};

class NovicePyromancer : public Minion
{
public:
    explicit NovicePyromancer(int owner);
};

class ApprenticeSummoner : public Minion
{
public:
    explicit ApprenticeSummoner(int owner);
};

class MasterSummoner : public Minion
{
public:
    explicit MasterSummoner(int owner);
};

///////////////////////////////////////////////////////////////////////////////////////////////////

#endif
