#ifndef CARD_H
#define CARD_H
#include <string>

#include "player.h"
#include "ability.h"
#include "subject.h"
#include "decorator.h"

///////////////////////////////////////////////////////////////////////////////////////////////////
class Card
{
private:
    std::string name;
    unsigned int cost; // note: simplified variable name. this is originally costMagic in the UML.
    // A card’s type is one of “minion,” “enchantment,” “ritual,” or “spell.”
    std::string type;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
class Spell : public Card
{
private:
    std::string changeExpression;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
class Minion : public Card, Subject
{
private:
    int atk; // note: simplified variable name. this is different from the UML.
    int def; // note: simplified variable name. this is different from the UML.
    // actions is the number of times it is allowed to attack or use an ability
    // in one turn. this can only be 0 or 1 for now.
    unsigned int actions = 0;
    // Activated abilities cost magic and an action point to use, and work
    // similar to playing a spell card.
    ActivatedAbility actAbility;
    // Triggered abilities are activated for free whenever a certain condition
    // is met.
    TriggeredAbility trgAbility;

public:
    void attack(Player &p);
    void attack(Minion &other);
    void useAbility();
    void restoreAction();
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
class Enchantment : public Card, public Decorator
{
private:
    std::string atkChange; // note: ? why string?
    std::string defChange;
    ActivatedAbility actAbility;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
class Ritual : public Card
{
    unsigned int cost;
    int charges;
    TriggeredAbility trgAbility;
};

///////////////////////////////////////////////////////////////////////////////////////////////////

#endif
