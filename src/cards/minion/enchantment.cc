#include "enchantment.h"
#include "activatedAbility.h"
#include "triggeredAbility.h"


///////////////////////////////////////////////////////////////////////////////////////////////////
Enchantment::Enchantment() {}

Enchantment::Enchantment(std::string name, int owner, int cost, std::string atkChange, std::string defChange, std::string description) :
    Minion{name, owner, cost, 0, 0, "Enchantment"}, atkChange{atkChange}, defChange{defChange}, description{description} {}

void Enchantment::attach(std::shared_ptr<Minion> minion) { 
    component = minion;
    setOwner(component->getOwner()); 
    setDef(computeDef());
    setAtk(computeAtk());
    setTrgAbility(computeTrgAbility());
    setActAbility(computeActAbility());
}

std::string Enchantment::getAtkChange() const{ return atkChange; }

std::string Enchantment::getDefChange() const { return defChange; }

std::string Enchantment::getDescription() const {return description; }

std::shared_ptr<Minion> Enchantment::getComponent() const { return component; }

std::shared_ptr<Minion> Enchantment::getAttachedMinion() {
    return component->getAttachedMinion();
}

std::vector<std::shared_ptr<Enchantment>> Enchantment::getEnchantmentList() {
    std::vector<std::shared_ptr<Enchantment>> v = component->getEnchantmentList();
    std::shared_ptr<Enchantment> p = std::static_pointer_cast<Enchantment>(shared_from_this());
    v.push_back(p);
    return v;
}

int Enchantment::computeAtk() const {
    if(atkChange.compare("") == 0){
        return component->getAtk() + getAtk();
    } else{
        if(atkChange.substr(0, 1).compare("+") == 0){
            int magnitude = std::stoi(atkChange.substr(1));
            return component->getAtk() + magnitude + getAtk();
        } else if(atkChange.substr(0, 1).compare("-") == 0){
            int magnitude = std::stoi(atkChange.substr(1));
            return component->getAtk() - magnitude + getAtk();
        } else if(atkChange.substr(0, 1).compare("*") == 0){
            int magnitude = std::stoi(atkChange.substr(1));
            return component->getAtk() * magnitude + getAtk();
        } else{
            int magnitude = std::stoi(atkChange.substr(1));
            return component->getAtk() / magnitude + getAtk();
        }
    }

}

int Enchantment::computeDef() const {
    if(defChange.compare("") == 0){
        return component->getDef() + getDef();
    } else{
        if(defChange.substr(0, 1).compare("+") == 0){
            int magnitude = std::stoi(defChange.substr(1));
            return component->getDef() + magnitude + getDef();
        } else if(defChange.substr(0, 1).compare("-") == 0){
            int magnitude = std::stoi(defChange.substr(1));
            return component->getDef() - magnitude + getDef();
        } else if(defChange.substr(0, 1).compare("*") == 0){
            int magnitude = std::stoi(defChange.substr(1));
            return component->getDef() * magnitude + getDef();
        } else{
            int magnitude = std::stoi(defChange.substr(1));
            return component->getDef() / magnitude + getDef();
        }
    }

}

std::shared_ptr<ActivatedAbility> Enchantment::computeActAbility() const {
    if(getActAbility() != nullptr){ 
        return getActAbility(); 
    } else { return component->computeActAbility(); }
}

std::shared_ptr<TriggeredAbility> Enchantment::computeTrgAbility() const {
    return component->computeTrgAbility();
}

Enchantment::~Enchantment() {}

///////////////////////////////////////////////////////////////////////////////////////////////////
// GiantStrength //////////////////////////////////////////////////////////////////////////////////
GiantStrength::GiantStrength(int owner) :
    Enchantment{"Giant Strength", owner, 1, "+2", "+2", ""} {}


///////////////////////////////////////////////////////////////////////////////////////////////////
// Enrage /////////////////////////////////////////////////////////////////////////////////////////
Enrage::Enrage(int owner) : 
    Enchantment{"Enrage", owner, 2, "*2", "-2", ""} {}

///////////////////////////////////////////////////////////////////////////////////////////////////
// Delay //////////////////////////////////////////////////////////////////////////////////////////
Delay::Delay(int owner) : 
    Enchantment{"Delay", owner, 1, "", "", 
        "Enchanted minion does not gain an action on their next round. This enchantment is automatically destroyed after 1 turn"} {}

int Delay::getRound() const { return round;}

void Delay::restoreAction() {
    actions = 0;
    round += 1;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// MagicFaticue /////////////////////////////////////////////////////////////////////////////////////
MagicFatigue::MagicFatigue(int owner) : 
    Enchantment{"Magic Fatigue", owner, 0, "", "", "Enchanted minion's activated ability costs 2 more"} {}

void MagicFatigue::attach(std::shared_ptr<Minion> minion){
    component = minion;
    setOwner(component->getOwner());
        setDef(computeDef());
    setAtk(computeAtk());
    setTrgAbility(computeTrgAbility());
    setActAbility(std::make_shared<ActivatedAbility>(*component->computeActAbility()));
    getActAbility()->setCost(getActAbility()->getCost() + 2);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// Silence //////////////////////////////////////////////////////////////////////////////////////////
Silence::Silence(int owner) : 
    Enchantment{"Silence", owner, 1, "", "", "Enchanted minion cannot use abilities"} {}

std::shared_ptr<TriggeredAbility> Silence::computeTrgAbility() const {
    return nullptr;
}

std::shared_ptr<ActivatedAbility> Silence::computeActAbility() const {
    return nullptr;
}
