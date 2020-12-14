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
        void effectWithTarget(int player, int target);
        void effectWithTarget(int player, char ritual);
        std::string getDescription();

        virtual ~Spell();
};

#endif
