#include "minion.h"
#include "../../game/player.h"
#include "../../game/game.h"
#include "triggeredAbility.h"
#include "activatedAbility.h"
#include "enchantment.h"
#include "../../cardCollections/board.h"
#include "../../argException.h"

using namespace std;

///////////////////////////////////////////////////////////////////////////////////////////////////
Minion::Minion() {}
Minion::Minion(std::string name, int owner, int cost, int atk, int def, std::string type) : 
Card{name, type, owner, cost}, atk{atk}, def{def} {}

int Minion::getAtk() const { return atk; }
int Minion::computeAtk() const { return getAtk(); }
void Minion::setAtk(int new_atk) { atk = new_atk; }
int Minion::getDef() const { return def; }
int Minion::computeDef() const { return getDef(); }
void Minion::setDef(int new_def) { def = new_def; }

void Minion::restoreAction() { actions = actionsCap; }

std::shared_ptr<ActivatedAbility> Minion::getActAbility() const { return actAbility; }
std::shared_ptr<TriggeredAbility> Minion::getTrgAbility() const { return trgAbility; }
void Minion::setActAbility(std::shared_ptr<ActivatedAbility> ability) { actAbility = ability; }
void Minion::setTrgAbility(std::shared_ptr<TriggeredAbility> ability) { trgAbility = ability; }
bool Minion::hasActAbility() const { return  computeActAbility().get() != nullptr; }
bool Minion::hasTrgAbility() const { return getTrgAbility().get() != nullptr; }
std::shared_ptr<ActivatedAbility> Minion::computeActAbility() const {return getActAbility(); }
std::shared_ptr<TriggeredAbility> Minion::computeTrgAbility() const {return getTrgAbility(); }

void Minion::attack(shared_ptr<Player> other)
{
    if (actions > 0)
    {
        int attack = this->getAtk();
        other->setLife(other->getLife() - attack);
        --actions;
    } else {
        throw ArgException{"Minion " + getAttachedMinion()->getName() + " does not have enough action points to attack."};
    }
}

void Minion::attack(shared_ptr<Minion> other)
{
    if (actions > 0)
    {
        other->setDef(other->getDef() - this->getAtk());
        this->setDef(this->getDef() - other->getAtk());
        --actions;
    } else {
        throw ArgException{"Minion " + getAttachedMinion()->getName() + " does not have enough action points to attack."};
    }
}

std::shared_ptr<Minion> Minion::getAttachedMinion() {
    return shared_from_this();
}

std::vector<std::shared_ptr<Enchantment>> Minion::getEnchantmentList(){
    std::vector<std::shared_ptr<Enchantment>> v;
    return v;
}

void Minion::useAbility(std::shared_ptr<Game> game) { 
    if (actions > 0){
        if(getActAbility() != nullptr){
            getActAbility()->effect(game, shared_from_this()); 
            actions--;
        } else{
            throw ArgException{"Minion " + getAttachedMinion()->getName() + " does not have activated ability."};
        }
    } else {
        throw ArgException{"Minion " + getAttachedMinion()->getName() + " does not have enough action points to use activated ability."};
    }
}

void Minion::useAbility(std::shared_ptr<Game> game, int player, int target) {
    if (actions > 0){
        if(getActAbility() != nullptr){
            std::shared_ptr<Minion> targetMinion = game->getPlayer(player)->getBoard()->getMinion(target);
            actAbility->effect(game, shared_from_this(), targetMinion);
            actions--;
        } else{
            throw ArgException{"Minion " + getAttachedMinion()->getName() + " does not have activated ability."};
        }
    } else {
        throw ArgException{"Minion " + getAttachedMinion()->getName() + " does not have enough action points to use activated ability."};
    }

}

void Minion::die(std::shared_ptr<Game> game) {
    if(getTrgAbility() != nullptr && getTrgAbility()->getType() == MINION_DEATH){
        getTrgAbility()->effect(game, shared_from_this());
    }
}

bool Minion::isSubType(MinionSubType type){
    return subType[type];
}

Minion::~Minion(){}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// AirElemental /////////////////////////////////////////////////////////////////////////////////////////////////////
AirElemental::AirElemental(int owner)
    : Minion{"Air Elemental", owner, 0, 1, 1} {
        subType[ELEMENTAL] = true;
        subType[SUMMONER] = false;
    }

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// EarthElemental /////////////////////////////////////////////////////////////////////////////////////////////////////

EarthElemental::EarthElemental(int owner)
    : Minion{"Earth Elemental", owner, 3, 4, 4} {
        subType[ELEMENTAL] = true;
        subType[SUMMONER] = false;
    }

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Bomb /////////////////////////////////////////////////////////////////////////////////////////////////////

Bomb::Bomb(int owner)
    : Minion{"Bomb", owner, 2, 1, 2}
{
    Minion::setTrgAbility(std::make_shared<DieDamage>());
    subType[ELEMENTAL] = false;
    subType[SUMMONER] = false;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// FireElemental /////////////////////////////////////////////////////////////////////////////////////////////////////

FireElemental::FireElemental(int owner)
    : Minion{"Fire Elemental", owner, 2, 2, 2}
{
    Minion::setTrgAbility(std::make_shared<EnterDamage>());
    subType[ELEMENTAL] = true;
    subType[SUMMONER] = false;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// PotionSeller /////////////////////////////////////////////////////////////////////////////////////////////////////

PotionSeller::PotionSeller(int owner)
    : Minion{"Potion Seller", owner, 2, 1, 3}
{
    Minion::setTrgAbility(std::make_shared<EndGainDef>());
    subType[ELEMENTAL] = false;
    subType[SUMMONER] = false;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// NovicePyromancer /////////////////////////////////////////////////////////////////////////////////////////////////////

NovicePyromancer::NovicePyromancer(int owner)
    : Minion{"Novice Pyromancer", owner, 1, 0, 1}
{
    Minion::setActAbility(std::make_shared<DamageTarget>());
    subType[ELEMENTAL] = false;
    subType[SUMMONER] = false;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// ApprenticeSummoner /////////////////////////////////////////////////////////////////////////////////////////////////////

ApprenticeSummoner::ApprenticeSummoner(int owner)
    : Minion{"Apprentice Summoner", owner, 1, 1, 1}
{
    Minion::setActAbility(std::make_shared<SummonOneAirElemental>());
    subType[ELEMENTAL] = false;
    subType[SUMMONER] = true;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// MasterSummoner /////////////////////////////////////////////////////////////////////////////////////////////////////

MasterSummoner::MasterSummoner(int owner)
    : Minion{"Master Summoner", owner, 3, 2, 3}
{
    Minion::setActAbility(std::make_shared<SummonThreeAirElemental>());
    subType[ELEMENTAL] = false;
    subType[SUMMONER] = true;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// GrandSummoner /////////////////////////////////////////////////////////////////////////////////////////////////////

GrandSummoner::GrandSummoner(int owner) 
    : Minion{"Grand Summoner", owner, 5, 2, 5}
    {
        Minion::setActAbility(std::make_shared<SummonOneFireElemental>());
        subType[ELEMENTAL] = false;
        subType[SUMMONER] = true;
    }