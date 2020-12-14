#include "enchantment.h"


///////////////////////////////////////////////////////////////////////////////////////////////////
Enchantment::Enchantment() {}

Enchantment::Enchantment(std::string name, int owner, int cost, std::string atkChange, std::string defChange, std::string description) :
    Minion{name, owner, cost, 0, 0, "Enchantment"}, atkChange{atkChange}, defChange{defChange}, description{description} {}

void Enchantment::attach(std::shared_ptr<Minion> minion) { component = minion; }

std::string Enchantment::getAtkChange() const{ return atkChange; }

std::string Enchantment::getDefChange() const { return defChange; }

std::string Enchantment::getDescription() const {return description; }

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
        return component->computeAtk() + getAtk();
    } else{
        if(atkChange.substr(0, 1).compare("+") == 0){
            int magnitude = std::stoi(atkChange.substr(1));
            return component->computeAtk() + magnitude + getAtk();
        } else if(atkChange.substr(0, 1).compare("-") == 0){
            int magnitude = std::stoi(atkChange.substr(1));
            return component->computeAtk() - magnitude + getAtk();
        } else if(atkChange.substr(0, 1).compare("*") == 0){
            int magnitude = std::stoi(atkChange.substr(1));
            return component->computeAtk() * magnitude + getAtk();
        } else{
            int magnitude = std::stoi(atkChange.substr(1));
            return component->computeAtk() / magnitude + getAtk();
        }
    }

}

int Enchantment::computeDef() const {
    if(defChange.compare("") == 0){
        return component->computeDef() + getDef();
    } else{
        if(defChange.substr(0, 1).compare("+") == 0){
            int magnitude = std::stoi(defChange.substr(1));
            return component->computeDef() + magnitude + getDef();
        } else if(defChange.substr(0, 1).compare("-") == 0){
            int magnitude = std::stoi(defChange.substr(1));
            return component->computeDef() - magnitude + getDef();
        } else if(defChange.substr(0, 1).compare("*") == 0){
            int magnitude = std::stoi(defChange.substr(1));
            return component->computeDef() * magnitude + getDef();
        } else{
            int magnitude = std::stoi(defChange.substr(1));
            return component->computeDef() / magnitude + getDef();
        }
    }

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

