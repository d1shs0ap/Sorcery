#ifndef CARD_H
#define CARD_H
#include <string>

#include "player.h"
#include "card.h"
#include "ability.h"
#include "subject.h"
#include "decorator.h"

class Card
{
private:
    std::string name;
    unsigned int costMagic;
    // A card’s type is one of “minion,” “enchantment,” “ritual,” or “spell.”
    std::string type;
};

class Minion : public Card, Subject
{
private:
    unsigned int atk; // simplified variable name. this is different from the UML.
    unsigned int def; // simplified variable name. this is different from the UML.
    unsigned int action;
    ActivatedAbility actAbility;
    TriggeredAbility trgAbility;

public:
    void attack(Player &p);
    void attack(Minion &m);
    void use();
    void actionResort();
};

class Enchantment : public Card, public Decorator
{
private:
    std::string atkChange; // ? why string?
    std::string defChange;
    ActivatedAbility actAbility;
};

class Ritual : public Card
{
    unsigned int cost;
    int charges;
    TriggeredAbility trgAbility;
};

class Spell : public Card
{
private:
    std::string changeExpression;
};

#endif
