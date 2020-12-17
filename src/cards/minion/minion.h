#ifndef MINION_H
#define MINION_H

#include <memory>
#include <string>
#include <iostream>
#include <map>

#include "../card.h"

class Player;
class TriggeredAbility;
class ActivatedAbility;
class Enchantment;
class Game;

enum MinionSubType{
    ELEMENTAL,
    SUMMONER
};

///////////////////////////////////////////////////////////////////////////////////////////////////
class Minion : public Card, public std::enable_shared_from_this<Minion>{
    int atk;
    int def;

    // Activated abilities cost magic and an action point to use, and work similar to playing a spell card.
    std::shared_ptr<ActivatedAbility> actAbility;

    // Triggered abilities are activated for free whenever a certain condition is met.
    std::shared_ptr<TriggeredAbility> trgAbility;

    protected:
        // actions is the number of times it is allowed to attack or use an ability in one turn. this can only be 0 or 1 for now.
        unsigned int actions = 0;
        unsigned int actionsCap = 1;
        // mapping if minion is corresponding subType
        std::map<MinionSubType, bool> subType;

    public:
        // Default constructor
        Minion();
        // Constructor
        Minion(std::string name, int owner, int cost, int atk, int def, std::string type = "Minion");

        // Getters and Setters
        int getAtk() const;
        void setAtk(int new_atk);
        int getDef() const;
        void setDef(int new_def);

        // Resotre actions to actionsCap
        virtual void restoreAction();

        // check if Minion has Activated ability
        bool hasActAbility() const;
        // checks if minion has triggered ability
        bool hasTrgAbility() const;
        // Getters and Setters
        std::shared_ptr<ActivatedAbility> getActAbility() const;
        void setActAbility(std::shared_ptr<ActivatedAbility> ability);
        std::shared_ptr<TriggeredAbility> getTrgAbility() const;
        void setTrgAbility(std::shared_ptr<TriggeredAbility> ability);

        // A recursive function to compute atk with Enchantments, Called by Enchantment::computeAtk, Enchantment::attach
        virtual int computeAtk() const;
        // A recursive function to compute def with Enchantments, Called by Enchantment::computeDef, Enchantment::attach
        virtual int computeDef() const;
        // A recursive function to compute actAbility with Enchantment, 
        //Called by Enchantment::computeActAbility, Enchantment::attach
        virtual std::shared_ptr<ActivatedAbility> computeActAbility() const;
        // A recursive function to compute trgAbility with Enchantment, 
        //Called by Enchantment::computeTrgAbility, Enchantment::attach
        virtual std::shared_ptr<TriggeredAbility> computeTrgAbility() const;

        // Attack player, play's Life decreases by atk, called by textController::attack
        void attack(std::shared_ptr<Player> player);
        // Attack minion, minion's def decreases by this->atk, this->def decreases by minion's atk
        // called by textController::attack
        void attack(std::shared_ptr<Minion> minion);
        // Use activated ability with no target, called by Player::use
        void useAbility(std::shared_ptr<Game> game);
        // Use activated ability with target, called by Player::use
        void useAbility(std::shared_ptr<Game> game, int player, int target);
        // Check if trgAbility is type of MINION_DIE, if so trigger it by calling trgAbility->effect
        void die(std::shared_ptr<Game> game);

        // Get the attached minion from the Enchantments call chain 
        virtual std::shared_ptr<Minion> getAttachedMinion();
        // Get the Enchantments list that are attached to the minion
        virtual std::vector<std::shared_ptr<Enchantment>> getEnchantmentList();

        // check if minion is type
        bool isSubType(MinionSubType type);

        // Destructor
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

class GrandSummoner : public Minion{
    public:
        explicit GrandSummoner(int owner);
};

///////////////////////////////////////////////////////////////////////////////////////////////////

#endif
