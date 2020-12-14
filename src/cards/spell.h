#ifndef SPELL_H
#define SPELL_H

#include <memory>
#include "card.h"

class Game;

// Spell card
class Spell : public Card {
    std::string description;

    public:
        Spell(std::string description);
        void effect(std::shared_ptr<Game> game);
        void effectWithTarget(std::shared_ptr<Game> game, int player, int target);
        void effectWithTarget(std::shared_ptr<Game> game, int player, char ritual);
        std::string getDescription();

        virtual ~Spell();
};

////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
class Banish : public Spell{
    public:
        explicit Banish(int owner);
};

class Unsummon : public Spell{
    public:
        explicit Unsummon(int owner);
};

class Recharge : public Spell{
    public:
        explicit Recharge(int owner);
};

class Disenchant : public Spell{
    public:
        explicit Disenchant(int owner);
};

class RaiseDead : public Spell{
    public:
        explicit RaiseDead(int owner);
};

class Blizzard : public Spell{
    public: 
        explicit Blizzard(int owner);
};

#endif
